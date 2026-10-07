class_name PcSpeaker
extends RefCounted
## The PC speaker driver of HOCKEY.EXE (pcspk_drv_* 0x9d698..0x9daac, pcspk_note_on / note_off /
## program / update_voices, and the hardware side pcspk_hw_* 0xa65e8..0xa677b), with PCBEEP.SCN's
## patches (PCFF003.PAT: the 27 sound effects, type 3, driver class 5) and their timbres
## (PCFF003.TIM, 70 bytes: +0xc playable, +0x10 s8 note offset, +0x11 s8 fine tune, +0x12 bend
## range, +0x19 2 = the envelope moves the pitch, +0x1c start, +0x1e peak, +0x20 attack step,
## +0x22 decay step, +0x24 sustain, +0x26 release step, +0x28 2 = the LFO moves the pitch, +0x29
## ticks a step, +0x2a delay, +0x2c steps (0x7fff for ever), +0x2e depth, +0x30 step, +0x34 its
## directions (1 up, 2 down, 3 both), +0x35 1 = a note sequence, +0x36 delay, +0x38 length,
## +0x3a ticks a step, +0x3b the eight note offsets).
##
## The driver keeps 16 voice records but timbre_env_sign (0x9da99) gives every note voice 1, so the
## speaker plays one note at a time, the last one; pcspk_note_off never moves past voice 0, so a
## note ends by its envelope (sustain 0 -> release) or by the next note (both as in the original).
## Every 100 Hz tick the envelope, the LFO and the sequence of the voice move the PIT divisor of the
## note (table 0xd6608) and pcspk_hw_update programs PIT channel 2 with it: a square wave of
## 1193182 / divisor Hz while the voice sounds, silence otherwise.

const PIT_HZ := 1193182.0
const DIV_TABLE := 0xd6608           # unk_d6608: the PIT divisor of each note (120)
const CLASS := 5                     # the driver class of the speaker records
const VOICES := 16

class Voice:                         # unk_f24d8[i] (0x30 bytes)
	var channel := 0                 # +0
	var active := 0                  # +1 (1 sounding, 2 note off)
	var note := 0                    # +3 (with the timbre's offset)
	var div := 0                     # +4 the divisor of the note
	var cur := 0                     # +6 the divisor played
	var ticks := 0                   # +8
	var timbre := PackedByteArray()  # +0x10
	var env := 0                     # +0x14
	var state := 0                   # +0x16 1 attack 2 decay 3 sustain 4 release
	var lfo_delay := 0               # +0x18
	var lfo_count := 0               # +0x1a
	var lfo := 0                     # +0x1c
	var seq_delay := 0               # +0x1e
	var seq_len := 0                 # +0x20
	var seq_val := 0                 # +0x22
	var lfo_step := 0                # +0x24
	var lfo_dir := 0                 # +0x26
	var lfo_tick := 0                # +0x27
	var seq_tick := 0                # +0x28
	var seq_idx := 0                 # +0x29
	var hw := 0                      # +0x2e

class Channel:                       # unk_f27d8[ch] (0x4e bytes)
	var timbre := PackedByteArray()  # +0x1e
	var sustain := 0                 # +0x25
	var bend := 0                    # +0x26 (no message sets it)
	var count := 0                   # +0x16

var bank: FmBank
var voices: Array = []
var channels: Array = []
var divs := PackedInt32Array()
var hw_active := PackedInt32Array()  # byte_d6774[0..4]
var hw_div := PackedInt32Array()     # word_d677b[0..4]
var hw_enabled := PackedInt32Array() # byte_d6785..d6789
var gate := false                    # port 0x61 bit 0: the PIT drives the speaker
var out_div := 0                     # PIT channel 2's divisor
var tick_count := 0                  # byte_d679a
var out_rate := 22050.0
var phase := 0.0
var level := 0.25
var lp := 0.0

func _init(b: FmBank, rate: float) -> void:
	bank = b
	out_rate = rate
	divs.resize(128)
	for n in 120:
		var d := Exe.u16(DIV_TABLE + n * 2)
		if d == 0 and n >= 2:
			d = int(PIT_HZ / (523.251 * pow(2.0, (n - 60) / 12.0)))
		divs[n] = d
	for i in VOICES:
		voices.append(Voice.new())
	for c in 16:
		channels.append(Channel.new())
	hw_active.resize(5)
	hw_div.resize(5)
	hw_enabled.resize(5)
	hw_enabled.fill(0x7f)

static func _s8(v: int) -> int:
	return v - 256 if v >= 128 else v

static func _s16(t: PackedByteArray, at: int) -> int:
	return t.decode_s16(at) if at + 2 <= t.size() else 0

## snd_patch_timbre for a speaker record
func _timbre(prog: int) -> PackedByteArray:
	var rec := bank.record(prog & 0xff) if bank != null else PackedByteArray()
	if rec.is_empty() or (rec[0xf] & 0x7f) != CLASS:
		return PackedByteArray()
	return bank.timbre(rec[1], rec[0])

## pcspk_drv_send_midi: note off, note on, program change
func midi(status: int, d1: int, d2: int) -> void:
	var ch := status & 0xf
	match status & 0xf0:
		0x80:
			note_off(ch, d1)
		0x90:
			if d2 == 0:
				note_off(ch, d1)
			else:
				note_on(ch, d1)
		0xc0:
			channels[ch].timbre = _timbre(d1)

## pcspk_note_on: voice 1 (timbre_env_sign) takes the note
func note_on(ch: int, note: int) -> void:
	var t: PackedByteArray = channels[ch].timbre
	if ch == 9:
		t = _timbre(note + 0x5c)
		note = 0x3c
	if t.size() < 0x43:
		return
	if _s16(t, 0xc) == 0:
		return
	var v: Voice = voices[1]
	v.timbre = t
	v.channel = ch
	v.active = 1
	v.state = 1
	v.env = _s16(t, 0x1c)
	v.ticks = 0
	v.lfo_delay = _s16(t, 0x2a)
	v.lfo_count = _s16(t, 0x2c)
	v.lfo_step = _s16(t, 0x30)
	v.lfo = 0
	v.lfo_dir = t[0x34]
	v.lfo_tick = 0
	v.seq_delay = _s16(t, 0x36)
	v.seq_len = _s16(t, 0x38)
	v.seq_tick = 0
	v.seq_val = 0
	v.seq_idx = 0
	v.hw = 1
	# pcspk_hw_voice_on
	v.note = (note + _s8(t[0x10])) & 0xff
	if v.note != 0xff:
		v.div = divs[v.note & 0x7f]
		v.cur = v.div
	hw_active[1] = 0xff

## pcspk_note_off: the search stays on voice 0 (the loop only counts)
func note_off(ch: int, note: int) -> void:
	var v: Voice = voices[0]
	if v.active == 0 or v.note != note or v.channel != ch:
		return
	v.active = 2
	v.state = 3 if channels[v.channel].sustain != 0 else 4

## pcspk_drv_tick -> pcspk_update_voices -> pcspk_hw_update
func tick() -> void:
	for v: Voice in voices:
		if v.active == 0:
			continue
		v.ticks += 1
		var t := v.timbre
		var peak := _s16(t, 0x1e)
		var sustain := _s16(t, 0x24)
		if v.state == 1:
			v.env = _wrap16(v.env + _s16(t, 0x20))
			if v.env >= peak:
				v.env = peak
				v.state = 2 if sustain < peak else 3
		if v.state == 2:
			v.env = _wrap16(v.env - _s16(t, 0x22))
			if v.env <= sustain:
				v.state = 3
				v.env = sustain
		if v.state == 3 and sustain == 0:
			v.state = 4
		if v.state == 4:
			v.env = _wrap16(v.env - _s16(t, 0x26))
			if v.env < 1:
				v.env = 0
				v.state = 0
				v.active = 0
				hw_active[v.hw] = 0
		if t[0x28] != 0:
			_lfo(v, t)
		if t[0x35] != 0:
			_sequence(v, t)
		_pitch(v, t)
	_hw_update()

static func _wrap16(x: int) -> int:
	x &= 0xffff
	return x - 0x10000 if x >= 0x8000 else x

func _lfo(v: Voice, t: PackedByteArray) -> void:
	if v.lfo_delay != 0:
		v.lfo_delay = _wrap16(v.lfo_delay - 1)
		return
	if v.lfo_count == 0:
		return
	if v.lfo_count != 0x7fff:
		v.lfo_count = _wrap16(v.lfo_count - 1)
	if v.lfo_tick != 0:
		v.lfo_tick -= 1
		return
	v.lfo_tick = t[0x29]
	var depth := _s16(t, 0x2e)
	if v.lfo_dir == 2:
		v.lfo = _wrap16(v.lfo - v.lfo_step)
		if absi(v.lfo) >= depth:
			if t[0x34] & 1 == 0:
				v.lfo = 0
			else:
				v.lfo_dir = 1
	else:
		v.lfo = _wrap16(v.lfo + v.lfo_step)
		if absi(v.lfo) >= depth:
			if t[0x34] & 2 == 0:
				v.lfo = 0
			else:
				v.lfo_dir = 2

func _sequence(v: Voice, t: PackedByteArray) -> void:
	if v.seq_delay != 0:
		v.seq_delay = _wrap16(v.seq_delay - 1)
		return
	if v.seq_len == 0:
		return
	v.seq_len = _wrap16(v.seq_len - 1)
	if v.seq_tick != 0:
		v.seq_tick -= 1
		return
	v.seq_tick = t[0x3a]
	var idx := v.seq_idx & 7
	v.seq_idx = idx + 1
	v.seq_val = _s8(t[0x3b + idx])

## pcspk_hw_voice_pitch: the divisor with the fine tune, the bend, the LFO and the envelope
func _pitch(v: Voice, t: PackedByteArray) -> void:
	if v.active == 0:
		return
	var note := v.note
	var d := v.div
	if t[0x35] == 1:
		note = (v.seq_val + v.note) & 0xff
		d = divs[note & 0x7f]
	d -= _s8(t[0x11])
	var bend: int = channels[v.channel].bend
	if bend > 0:
		d -= ((d - divs[(note + t[0x12]) & 0x7f]) * bend) / 0x1f80
	elif bend < 0:
		d += ((divs[(note - t[0x12]) & 0x7f] - d) * -bend) / 0x1f80
	if t[0x28] == 2:
		d += v.lfo
	if t[0x19] == 2:
		d += v.env
	hw_div[v.hw] = d & 0xffff
	v.cur = d

## pcspk_hw_update: voice 0 holds the speaker; else voices 1 / 2 (taking turns every two ticks
## with 3 / 4 when those sound too), else 3 / 4
func _hw_update() -> void:
	var on := PackedInt32Array([hw_active[0], 0, 0, 0, 0])
	for i in range(1, 5):
		on[i] = 0 if hw_enabled[i] == 0 else hw_active[i]
	if on[0] == 0:
		var d := -1
		if (on[3] == 0 and on[4] == 0) or (tick_count & 2 != 0 and (on[1] != 0 or on[2] != 0)):
			if on[1] != 0:
				d = hw_div[1]
			elif on[2] != 0:
				d = hw_div[2]
		else:
			d = hw_div[3] if on[3] != 0 else hw_div[4]
		if d < 0:
			gate = false
		else:
			out_div = d
			gate = true
	tick_count = (tick_count + 1) & 0xff

func active() -> int:
	return 1 if gate else 0

func all_off() -> void:
	for v: Voice in voices:
		v.active = 0
	hw_active.fill(0)
	gate = false

## the speaker: a square wave of the PIT's frequency while the gate is open (each output sample the
## average of the wave over its time, four sub-samples), through a one pole low pass
func render(out: PackedFloat32Array, offset: int, n: int) -> void:
	if not gate and absf(lp) < 1e-4:
		return
	var f := PIT_HZ / float(out_div if out_div > 0 else 0x10000)
	var inc := f / out_rate / 4.0
	for i in n:
		var acc := 0.0
		if gate:
			for k in 4:
				phase += inc
				if phase >= 1.0:
					phase -= floorf(phase)
				acc += 1.0 if phase < 0.5 else -1.0
			acc *= 0.25 * level
		lp += (acc - lp) * 0.5
		out[offset + i] += lp
