class_name FmDriver
extends RefCounted
## The FM music driver of the game (YM30.BGP for the Adlib, the FM half of SB30.BGP for the
## Sound Blaster), ported from its 16 bit code: it receives MIDI messages from the sequencer
## (KmsPlayer) and the sound effects (snd_play_patch) and plays them on the 9 voices of the OPL2.
##
## A program selects a patch record of the bank (FmBank, PCFF001.PAT) whose timbre (PCFF000.TIM)
## holds the 13 register bytes (carrier 20/40/60/80/E0, modulator 20/40/60/80/E0, C0, A0, B0) and
## the driver's own modulation: an envelope, an LFO and a step sequence, each driving one of the
## controls of sub_1c6 (1 note offset, 2 frequency offset, 3 volume, 5 LFO depth, 7 pitch bend,
## 8 LFO rate, 9 modulator level). The MIDI note gets the patch's transpose (+7); channel 9 plays
## the drum patch note + 0x5c at note 60. Frequencies: block = note / 12 and the F-number table
## of the driver (note 60 = F-number 86 in block 5), plus the patch's fine tune (+8). Levels: the
## velocity (table at DS:0x15f) times the channel volume (controller 7, table at DS:0x19f) scale
## the carrier's attenuation (63 - (63 - TL) * gain), both operators' with additive synthesis.
## Everything but the chip runs at the 100 Hz of the game's timer (tick()).

const FNUM := [86, 91, 96, 102, 108, 114, 121, 128, 136, 144, 153, 162, 171, 182, 192, 204, 216, 229, 242, 257,
	272, 288, 306, 324, 343, 363, 385, 408, 432, 458, 485, 514, 544, 577, 611, 647]
const VEL_GAIN := [10280, 10517, 10750, 10980, 11207, 11431, 11652, 11870, 12085, 12298, 12507, 12714, 12919, 13120,
	13320, 13517, 13712, 13904, 14094, 14282, 14468, 14652, 14833, 15013, 15191, 15367, 15541, 15713, 15883, 16052,
	16219, 16384]
const VOL_GAIN := [0, 1232, 2463, 3695, 4926, 6158, 7389, 8621, 9852, 10060, 10263, 10462, 10657, 10848, 11035, 11218,
	11398, 11575, 11748, 11918, 12085, 12249, 12411, 12569, 12725, 12879, 13030, 13178, 13325, 13469, 13610, 13750,
	13888, 14023, 14157, 14289, 14419, 14547, 14674, 14799, 14922, 15044, 15164, 15282, 15399, 15515, 15629, 15742,
	15853, 15964, 16072, 16180, 16287, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384]
const OP_REGS := [0x23, 0x43, 0x63, 0x83, 0xe3, 0x20, 0x40, 0x60, 0x80, 0xe0]
const OP_OFFSET := [0, 1, 2, 8, 9, 10, 16, 17, 18]
const CLASS := 1                      # the driver class of the FM records (+0xf of a patch record)

class Channel:
	var program := 0
	var mod := 0                  # controller 1, 0..16384
	var vol := 16384              # controller 7 as gain
	var bend := 0                 # -16384..16384
	var sustain := false
	var sustained: Array = []     # voices whose note off waits for the pedal

class Voice:
	var channel := -1
	var note := -1                # the MIDI note (byte 0x4b)
	var program := 0
	var patch := PackedByteArray()
	var timbre := PackedByteArray()
	var regs := PackedByteArray() # the 13 register bytes
	var key := false
	var release := 0              # -1 while the key is down, then ticks until the voice is freed
	var allocated := false
	var released := false
	var priority := 0
	var base_note := 0            # +0x18 note + transpose
	var cur_note := 0             # +0x19
	var freq := 0                 # +0x14 F-number | block << 10
	var freq_work := 0            # +0x16
	var vel_gain := 0             # +0x10
	var vol_work := 0             # +0x12
	var bend_up := 0              # +0x1a
	var bend_down := 0            # +0x1c
	var env := 0                  # +0x22 value, +0x24 delay, +0x26 state
	var env_delay := 0
	var env_state := 0
	var lfo_out := 0              # +0x28
	var lfo_raw := 0              # +0x2a
	var lfo_state := 0            # +0x2c
	var lfo_count := 0            # +0x2e
	var lfo_depth := 0            # +0x30
	var lfo_rate := 0             # +0x32
	var lfo_phase := 0            # +0x34
	var seq := 0                  # +0x36 value, +0x38 state, +0x3a delay, +0x3c length, +0x3e step, +0x40 index
	var seq_state := 0
	var seq_delay := 0
	var seq_len := 0
	var seq_step := 0
	var seq_index := -1

var chip: Opl2
var bank: FmBank
var channels: Array = []
var voices: Array = []
var sine := PackedInt32Array()        # the quarter sine of DS:0x420 (0..16384)

func _init(c: Opl2, b: FmBank) -> void:
	chip = c
	bank = b
	for i in 16:
		channels.append(Channel.new())
	for i in 9:
		var v := Voice.new()
		v.regs.resize(13)
		voices.append(v)
	sine.resize(257)
	for i in 257:
		sine[i] = int(round(16384.0 * sin(PI / 2.0 * i / 256.0)))
	reset()

## sub_1771: all registers cleared, the waveforms enabled, the release rates set
func reset() -> void:
	chip.reset()
	chip.write(0x01, 0x20)
	for r in range(0x80, 0x96):
		chip.write(r, 0x0e)
	for v in voices:
		v.allocated = false
		v.key = false
		v.channel = -1
		v.release = 0
	for c in channels:
		c.sustain = false
		c.sustained.clear()
		c.bend = 0
		c.mod = 0

## sub_199d: the frequency word of a note (+ offset semitones)
static func note_freq(note: int, offset: int) -> int:
	note &= 0xff
	var block := note / 12
	var idx := clampi(note % 12 + offset, 0, FNUM.size() - 1)
	return FNUM[idx] | (block << 10)

static func _mul14(a: int, b: int) -> int:
	return (a * b) >> 14

static func _s8(b: int) -> int:
	return b - 0x100 if b >= 0x80 else b

static func _w(t: PackedByteArray, o: int) -> int:
	var v := t[o] | (t[o + 1] << 8)
	return v - 0x10000 if v >= 0x8000 else v

# --------------------------------------------------------------------------------------------
# MIDI input (sub_11ba)
# --------------------------------------------------------------------------------------------

func midi(status: int, d1: int, d2: int) -> void:
	var ch := status & 0xf
	match status & 0xf0:
		0x80:
			note_off(ch, d1)
		0x90:
			if d2 == 0:
				note_off(ch, d1)
			else:
				note_on(ch, d1, d2)
		0xb0:
			control(ch, d1, d2)
		0xc0:
			channels[ch].program = d1
		0xe0:
			channels[ch].bend = (((d2 - 0x40) << 7) + d1) * 2

## sub_eb0: controllers 1 (modulation), 7 (volume), 10 (pan), 0x40 (sustain), 0x7b (all off)
func control(ch: int, num: int, val: int) -> void:
	var c: Channel = channels[ch]
	match num:
		1:
			c.mod = mini(val * 0x82, 0x4000)
		7:
			c.vol = VOL_GAIN[(val & 0x7e) >> 1]
		0x40:
			c.sustain = (val & 0x40) != 0
			if not c.sustain:
				for v in c.sustained:
					_release(v)
				c.sustained.clear()
		0x7b:
			for v in voices:
				if v.allocated and v.channel == ch and v.key:
					_release(v)

## sub_6d6: a note starts; the voice of the same note is retriggered, else a free voice of the
## patch's voice mask is taken (the oldest released one, else the one of the lowest priority)
func note_on(ch: int, note: int, vel: int) -> void:
	var program: int = channels[ch].program
	var play := note
	if ch == 9:
		if note < 0x24 or note >= 0x64:
			return
		program = note + 0x5c
		play = 0x3c
	var patch := bank.record(program)
	if patch.is_empty() or (patch[0xf] & 0x7f) != CLASS:
		return
	var timbre := bank.timbre(patch[1], patch[0])
	if timbre.is_empty():
		return
	var v: Voice = null
	for cand in voices:
		if cand.allocated and cand.channel == ch and cand.note == note:
			v = cand
			break
	if v == null:
		v = _allocate(ch, patch)
	if v == null:
		return
	var idx := voices.find(v)
	if chip.ch_kon[idx]:
		# 0x953: a sounding voice is keyed off with the fast release before it starts again
		v.regs[0xc] &= 0xdf
		v.regs[3] = (v.regs[3] & 0xf0) | 0x0e | (v.regs[3] & 1)
		v.regs[8] = (v.regs[8] & 0xf0) | 0x0e | (v.regs[8] & 1)
		_write_voice(idx, v)
	v.allocated = true
	v.released = false
	v.channel = ch
	v.note = note
	v.program = program
	v.patch = patch
	v.timbre = timbre
	v.priority = patch[0xc] << 4
	_start(v, _s8(patch[7]) + play, vel)

func _allocate(ch: int, patch: PackedByteArray) -> Voice:
	var mask := (patch[2] | (patch[3] << 8)) & 0x1ff
	var max_voices: int = patch[6]
	var own := 0
	for v in voices:
		if v.allocated and v.channel == ch:
			own += 1
	var best: Voice = null
	if own < max_voices:
		for i in 9:
			if mask & (1 << i) and not voices[i].allocated:
				return voices[i]
		for i in 9:
			var v: Voice = voices[i]
			if mask & (1 << i) and v.released and (best == null or v.priority < best.priority):
				best = v
		if best != null:
			return best
	for i in 9:
		var v: Voice = voices[i]
		if not (mask & (1 << i)):
			continue
		if own >= max_voices and v.channel != ch:
			continue
		if best == null or (v.released and not best.released) or (v.released == best.released and v.priority < best.priority):
			best = v
	return best

## sub_10 and the end of the note on: the timbre's registers and modulators, the note's frequency
## and the velocity
func _start(v: Voice, note: int, vel: int) -> void:
	var t := v.timbre
	for i in 13:
		v.regs[i] = t[2 + i]
	if _w(t, 0x10) != 0:
		v.env = _w(t, 0x14)
		v.env_delay = _w(t, 0x12)
		v.env_state = 1 if _w(t, 0x12) != 0 else 2
	if _w(t, 0x22) != 0:
		v.lfo_phase = 0
		v.lfo_count = 0
		v.lfo_raw = 0
		v.lfo_out = 0
		v.lfo_depth = _w(t, 0x28)
		v.lfo_rate = _w(t, 0x2e)
		v.lfo_state = 1
	if _w(t, 0x32) != 0:
		v.seq = 0
		v.seq_len = _w(t, 0x38)
		v.seq_step = t[0x37]
		v.seq_index = -1
		v.seq_delay = _w(t, 0x34)
		if v.seq_delay != 0:
			v.seq_state = 1
		else:
			v.seq_state = 2
			_seq_tick(v)
	v.bend_up = 0
	v.bend_down = 0
	v.key = false
	v.base_note = note & 0xff
	v.cur_note = note & 0xff
	v.freq = note_freq(note, 0) + _s8(v.patch[8])
	v.vel_gain = VEL_GAIN[(vel & 0x7c) >> 2]
	v.key = true
	v.release = -1

## the note off (sub_11ba 0x80): the key is released, the envelope enters its release, the voice
## is freed after the timbre's hold time (+0x4a ticks)
func note_off(ch: int, note: int) -> void:
	for v in voices:
		if v.allocated and v.channel == ch and v.note == note and v.key:
			if channels[ch].sustain:
				if not channels[ch].sustained.has(v):
					channels[ch].sustained.append(v)
			else:
				_release(v)

func _release(v: Voice) -> void:
	v.released = true
	v.priority >>= 1
	if _w(v.timbre, 0x10) != 0:
		v.env_state = 5
	v.key = false
	v.release = _w(v.timbre, 0x4a)

## stops everything at once (sound_stopall / a new song): key off with the fast release
func all_off() -> void:
	for v in voices:
		if v.allocated:
			_free(v)

func _free(v: Voice) -> void:
	v.allocated = false
	v.released = false
	v.key = false
	v.channel = -1
	v.note = -1
	v.env_state = 0
	v.lfo_state = 0
	v.seq_state = 0
	v.regs[0xc] &= 0xdf
	v.regs[3] = (v.regs[3] & 0xf0) | 0x0e | (v.regs[3] & 1)
	v.regs[8] = (v.regs[8] & 0xf0) | 0x0e | (v.regs[8] & 1)
	_write_voice(voices.find(v), v)

# --------------------------------------------------------------------------------------------
# the 100 Hz update (sub_3da -> sub_150a)
# --------------------------------------------------------------------------------------------

func tick() -> void:
	for i in 9:
		var v: Voice = voices[i]
		if not v.allocated:
			continue
		if v.release == 0:
			_free(v)
			continue
		if v.priority >= 1:
			v.priority -= 1
		else:
			v.priority = 0
		_update(v)
		_output(i, v)
		if v.release > 0:
			v.release -= 1

func _update(v: Voice) -> void:
	var t := v.timbre
	var c: Channel = channels[v.channel]
	v.freq_work = v.freq
	v.vol_work = v.vel_gain
	if _w(t, 0x32) != 0:
		if v.seq_state == 1:
			v.seq_delay -= 1
			if v.seq_delay <= 0:
				v.seq_state = 2
				_seq_tick(v)
		elif v.seq_state == 2:
			_seq_tick(v)
		_control(v, _w(t, 0x32), v.seq)
	_control(v, 7, c.bend)
	if _w(t, 0x10) != 0:
		match v.env_state:
			1:
				v.env_delay -= 1
				if v.env_delay <= 0:
					v.env_state = 2
			2:
				v.env += _w(t, 0x16)
				if v.env >= _w(t, 0x18):
					v.env = _w(t, 0x18)
					v.env_state = 3
			3:
				v.env -= _w(t, 0x1a)
				if v.env <= _w(t, 0x1c):
					v.env = _w(t, 0x1c)
					v.env_state = 4
			4, 5:
				v.env -= _w(t, 0x1e) if v.env_state == 4 else _w(t, 0x20)
				if v.env <= 0:
					v.env = 0
					v.env_state = 0
		_control(v, _w(t, 0x10), v.env)
	if _w(t, 0x22) != 0:
		if v.lfo_state == 1:
			if v.lfo_count >= _w(t, 0x24):
				v.lfo_state = 2 if _w(t, 0x26) > v.lfo_count else 0
		if v.lfo_state == 2:
			if _w(t, 0x26) <= v.lfo_count:
				v.lfo_state = 0
			else:
				v.lfo_phase = (v.lfo_phase + v.lfo_rate) & 0xffff
				v.lfo_raw = _mul14(_sine(v.lfo_phase >> 6), v.lfo_depth)
		var lim := _w(t, 0x2a)
		v.lfo_out = clampi(v.lfo_raw, -lim, lim)
		v.lfo_count += 1
		_control(v, _w(t, 0x22), v.lfo_out)
	_control(v, 5, c.mod)
	_control(v, 3, c.vol)

## sub_1418: the step sequence of the timbre (+0x34 delay, +0x36 steps, +0x37 ticks per step,
## +0x38 length, +0x3a values)
func _seq_tick(v: Voice) -> void:
	var t := v.timbre
	v.seq_len -= 1
	if v.seq_len <= 0:
		v.seq_state = 0
		v.seq_index = 0
		v.seq = 0
		return
	v.seq_step -= 1
	if v.seq_step <= 0:
		v.seq_step = t[0x37]
		v.seq_index += 1
		if t[0x36] <= v.seq_index:
			v.seq_index = 0
		v.seq = _w(t, 0x3a + v.seq_index * 2)

## sub_1a28: a sine of a 10 bit phase (quarter table)
func _sine(p: int) -> int:
	var q := (p >> 8) & 3
	var i := p & 0xff
	match q:
		0: return sine[i]
		1: return sine[256 - i]
		2: return -sine[i]
	return -sine[256 - i]

## sub_1c6: a control applied to the working values of the voice
func _control(v: Voice, ctrl: int, value: int) -> void:
	match ctrl:
		1:
			v.cur_note = (value + v.base_note) & 0xff
			v.freq_work = note_freq(v.cur_note, 0)
		2:
			v.freq_work += value
		3:
			v.vol_work = _mul14(absi(value), v.vol_work)
		5:
			v.lfo_depth = _mul14(value, _w(v.timbre, 0x2c)) + _w(v.timbre, 0x28)
		7:
			var range_: int = v.patch[0xa]
			if value > 0:
				if v.bend_up == 0:
					v.bend_up = note_freq(v.cur_note, range_) - v.freq_work
				v.freq_work += _mul14(value, v.bend_up)
			elif value < 0:
				if v.bend_down == 0:
					v.bend_down = -(note_freq(v.cur_note, -range_) - v.freq_work)
				v.freq_work += _mul14(value, v.bend_down)
		8:
			v.lfo_rate = _mul14(value, _w(v.timbre, 0x2e))
		9:
			var lvl := (63 - _mul14(value, 0x3f)) & 0x3f
			v.regs[6] = (v.regs[6] & 0xc0) | lvl

## the register output of a voice (0x4d8..0x5a4): the levels from the working volume, the
## frequency, the key
func _output(i: int, v: Voice) -> void:
	var t := v.timbre
	if v.regs[10] & 1:
		var tl_m := 0x3f - (t[8] & 0x3f)
		v.regs[6] = (v.regs[6] & 0xc0) | ((0x3f - _mul14(v.vol_work, tl_m)) & 0x3f)
	var tl_c := 0x3f - (t[3] & 0x3f)
	v.regs[1] = (v.regs[1] & 0xc0) | ((0x3f - _mul14(v.vol_work, tl_c)) & 0x3f)
	var f := v.freq_work & 0xffff
	v.regs[11] = f & 0xff
	v.regs[12] = (f >> 8) & 0x1f
	if v.key:
		v.regs[12] |= 0x20
	_write_voice(i, v)

## sub_185c: the 13 register bytes of a voice
func _write_voice(i: int, v: Voice) -> void:
	var off: int = OP_OFFSET[i]
	for k in 10:
		chip.write(OP_REGS[k] + off, v.regs[k])
	chip.write(0xc0 + i, v.regs[10])
	chip.write(0xa0 + i, v.regs[11])
	chip.write(0xb0 + i, v.regs[12])

func active_voices() -> int:
	var n := 0
	for v in voices:
		if v.allocated:
			n += 1
	return n
