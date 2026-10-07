class_name FmDriver
extends RefCounted
## The FM driver of HOCKEY.EXE (adlib_drv_* 0x9debe..0x9f225 with the OPL2 layer opl_* 0xa687d..
## 0xa6b86), the driver of the AdLib and of the FM half of the Sound Blaster: it receives the MIDI
## messages of the sequencer (KmsPlayer) and of the sound effects (snd_play_patch) and plays them
## on the 9 voices of the OPL2. tests/golden/fm_driver.json holds the original's registers after
## every tick of four sequences (tools/nhl/golden.py runs the routines in an emulator); the port
## writes the same values.
##
## A program selects a patch record of the bank (FmBank, PCFF001.PAT: +2 the voices it may take,
## +6 how many, +7 transpose, +8 fine tune, +0xa bend range, +0xc priority) whose timbre
## (PCFF000.TIM) holds the 13 register bytes (+2..+0xe: carrier 20/40/60/80/E0, modulator
## 20/40/60/80/E0, C0, A0, B0) and the driver's own modulators, each driving one of the controls of
## adlib_voice_modulate (1 note offset, 2 frequency offset, 3 volume, 5 LFO depth, 7 pitch bend,
## 8 LFO rate, 9 modulator level): an envelope (+0x10 control, +0x12 delay, +0x14 start, +0x16
## attack, +0x18 peak, +0x1a decay, +0x1c sustain, +0x1e release, +0x20 key off release), an LFO
## (+0x22 control, +0x24 first tick, +0x26 last tick, +0x28 depth, +0x2a limit, +0x2c depth by
## the modulation wheel, +0x2e rate) and a step sequence (+0x32 control, +0x34 delay, +0x36 steps,
## +0x37 ticks a step, +0x38 length, +0x3a the values); +0x4a the ticks from the key off to the end.
## Channel 9 plays the drum patch of note + 0x5c at note 60.
##
## Voices: three masks (free, used, released); a note takes a free voice of the patch's mask while
## the channel holds fewer voices than its maximum, else a released one, else the used voice of
## the lowest priority anywhere. The channel's mask, maximum and priority are those of the patch it
## bound last (adlib_voice_patch runs after the choice), and a channel keeps the bit of a voice
## another channel took from it (the original never clears it), as the original does. Levels and
## pitch are 16.16 fixed point products rounded as fixmul16 (0x91fa4) rounds them. Everything
## runs at the 100 Hz of the game's timer (tick()).

const CLASS := 1                      # the driver class of the FM records (+0xf of a patch record)
const OP_OFFSET := [0, 1, 2, 8, 9, 10, 16, 17, 18]                                   # unk_d67a8
const VOICE_REGS := [0x23, 0x43, 0x63, 0x83, 0xe3, 0x20, 0x40, 0x60, 0x80, 0xe0, 0xc0, 0xa0, 0xb0]  # unk_d67b4
# unk_d67f4: the F-numbers of note % 12 + offset (from -12) and, after them, the velocity levels
# (unk_d683c, (velocity & 0x7c) / 4) that offsets past 35 read; unk_d687c: controller 7's gains
const FNUM_LOW := [43, 45, 48, 51, 54, 57, 61, 64, 68, 72, 76, 81]
const FNUM := [86, 91, 96, 102, 108, 114, 121, 128, 136, 144, 153, 162, 171, 182, 192, 204, 216, 229, 242, 257,
	272, 288, 306, 324, 343, 363, 385, 408, 432, 458, 485, 514, 544, 577, 611, 647]
const VEL_GAIN := [10280, 10517, 10750, 10980, 11207, 11431, 11652, 11870, 12085, 12298, 12507, 12714, 12919, 13120,
	13320, 13517, 13712, 13904, 14094, 14282, 14468, 14652, 14833, 15013, 15191, 15367, 15541, 15713, 15883, 16052,
	16219, 16384]
const VOL_GAIN := [0, 1232, 2463, 3695, 4926, 6158, 7389, 8621, 9852, 10060, 10263, 10462, 10657, 10848, 11035, 11218,
	11398, 11575, 11748, 11918, 12085, 12249, 12411, 12569, 12725, 12879, 13030, 13178, 13325, 13469, 13610, 13750,
	13888, 14023, 14157, 14289, 14419, 14547, 14674, 14799, 14922, 15044, 15164, 15282, 15399, 15515, 15629, 15742,
	15853, 15964, 16072, 16180, 16287, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384]

class Channel:                        # unk_f2f28[ch] (0x1e bytes)
	var mod := 0                      # +4 controller 1 (0..0x4000)
	var vol := 0                      # +6 controller 7 (VOL_GAIN; nothing sets it before the first)
	var pan := 0                      # +8 controller 10 (-0x4000..0x4000, not used)
	var sustain := 0                  # +0xa controller 0x40
	var bend := 0                     # +0xc (-0x4000..0x3ffe)
	var ctl_5a := 0                   # +0xe controller 0x5a (not used)
	var ctl_5b := 0                   # +0xf controller 0x5b (not used)
	var fine := 0                     # +0x11 the patch's fine tune (+8)
	var bend_range := 0               # +0x12 the patch's bend range (+0xa)
	var patch_9 := 0                  # +0x13 (+9, not used)
	var used := 0                     # +0x14 the voices the channel took
	var allowed := 0x1ff              # +0x16 the patch's voices (+2)
	var sustained := 0                # +0x18 the voices whose note off waits for the pedal
	var max_voices := 9               # +0x1a the patch's voice count (+6)
	var program := 0xff               # +0x1b
	var priority := 100               # +0x1c the patch's priority (+0xc) * 16

class Voice:                          # unk_f3148[i] (0x56 bytes; the routines get the state at +8)
	var channel := -1                 # +0 the channel record
	var timbre := PackedByteArray()   # +4
	var regs := PackedByteArray()     # +0xa the 13 register bytes
	var vel_gain := 0                 # +0x18 the velocity's level
	var vol_work := 0                 # +0x1a
	var freq := 0                     # +0x1c F-number | block << 10, with the fine tune
	var freq_work := 0                # +0x1e
	var base_note := 0                # +0x20 the note with the transpose
	var cur_note := 0                 # +0x21
	var bend_up := 0                  # +0x22
	var bend_down := 0                # +0x24
	var key := false                  # +0x26
	var release := 0                  # +0x28 -1 while the key is down, then the ticks left
	var env := 0                      # +0x2a the envelope: value, delay, state
	var env_delay := 0                # +0x2c
	var env_state := 0                # +0x2e 1 delay 2 attack 3 decay 4 sustain 5 release
	var lfo_out := 0                  # +0x30 the LFO: the limited value, the value, the state,
	var lfo_raw := 0                  # +0x32 the tick count, depth, rate and phase
	var lfo_state := 0                # +0x34
	var lfo_count := 0                # +0x36
	var lfo_depth := 0                # +0x38
	var lfo_rate := 0                 # +0x3a
	var lfo_phase := 0                # +0x3c
	var seq := 0                      # +0x3e the step sequence: value, state, delay, length,
	var seq_state := 0                # +0x40 ticks to the next step, index
	var seq_delay := 0                # +0x42
	var seq_len := 0                  # +0x44
	var seq_step := 0                 # +0x46
	var seq_index := -1               # +0x48
	var program := 0xff               # +0x4e
	var note := 0                     # +0x4f the MIDI note
	var patch := PackedByteArray()    # +0x50 the patch record
	var priority := 0                 # +0x54
	var allocated := false            # in the used mask
	var released := false             # in the released mask

var chip: Opl2
var bank: FmBank
var channels: Array = []
var voices: Array = []
var free_mask := 0x1ff                # word_f3452
var used_mask := 0                    # word_f3450
var released_mask := 0                # word_f344e
var shadow := PackedByteArray()       # unk_d68fc: the registers as written (opl_flush_regs)

func _init(c: Opl2, b: FmBank) -> void:
	chip = c
	bank = b
	shadow.resize(256)
	for i in 16:
		channels.append(Channel.new())
	for i in 9:
		var v := Voice.new()
		v.regs.resize(13)
		voices.append(v)
	reset()

## adlib_drv_init with opl_reset: every register 0 (1 = 0x20: the waveforms), the release rates 0xe,
## the voices free, the channels' records back to no patch
func reset() -> void:
	chip.reset()
	for r in range(1, 0xf6):
		chip.write(r, 0)
	chip.write(0x01, 0x20)
	shadow.fill(0)
	for r in range(0x80, 0x96):
		_set_reg(r, 0x0e)
	free_mask = 0x1ff
	used_mask = 0
	released_mask = 0
	for c: Channel in channels:
		c.used = 0
		c.sustained = 0
		c.allowed = 0x1ff
		c.max_voices = 9
		c.program = 0xff
		c.priority = 100
	for v: Voice in voices:
		v.program = 0xff
	_sync()

# --------------------------------------------------------------------------------------------
# arithmetic of the original
# --------------------------------------------------------------------------------------------

static func _s8(b: int) -> int:
	b &= 0xff
	return b - 0x100 if b >= 0x80 else b

static func _s16(x: int) -> int:
	x &= 0xffff
	return x - 0x10000 if x >= 0x8000 else x

static func _w(t: PackedByteArray, o: int) -> int:
	return t.decode_s16(o) if o + 2 <= t.size() else 0

static func _uw(t: PackedByteArray, o: int) -> int:
	return t.decode_u16(o) if o + 2 <= t.size() else 0

## fixmul16: a * b / 65536, rounded up from one half less one
static func fixmul16(a: int, b: int) -> int:
	return (a * b + 0x7fff) >> 16

## the word of the F-number table at an index (-12..35, and the level table after it)
static func _fnum(idx: int) -> int:
	if idx >= -12 and idx < 0:
		return FNUM_LOW[idx + 12]
	if idx >= 0 and idx < 36:
		return FNUM[idx]
	if idx >= 36 and idx < 68:
		return VEL_GAIN[idx - 36]
	return Exe.u16(0xd67f4 + idx * 2)

## adlib_note_fnum: the F-number of note % 12 + offset (a byte) | the block (note / 12) << 10
static func note_freq(note: int, offset: int) -> int:
	note &= 0xff
	return _fnum(_s8(note % 12 + offset)) | ((note / 12) << 10)

# --------------------------------------------------------------------------------------------
# the registers (opl_voice_regs, opl_set_reg, opl_flush_regs: written when they change)
# --------------------------------------------------------------------------------------------

func _set_reg(r: int, v: int) -> void:
	v &= 0xff
	if shadow[r] != v:
		shadow[r] = v
		chip.write(r, v)

func _voice_regs(i: int, v: Voice) -> void:
	var off: int = OP_OFFSET[i]
	for k in 10:
		_set_reg(VOICE_REGS[k] + off, v.regs[k])
	for k in range(10, 13):
		_set_reg(VOICE_REGS[k] + i, v.regs[k])

# --------------------------------------------------------------------------------------------
# MIDI input (adlib_drv_send_midi)
# --------------------------------------------------------------------------------------------

func midi(status: int, d1: int, d2: int) -> void:
	var ch := status & 0xf
	match status & 0xf0:
		0x80:
			channel_release(ch, d1)
		0x90:
			if d2 == 0:
				channel_release(ch, d1)
			else:
				note_on(ch, d1, d2)
		0xb0:
			control(ch, d1, d2)
		0xc0:
			channels[ch].program = d1 & 0xff
		0xe0:
			channels[ch].bend = _s16((((d2 & 0xff) << 7) + (d1 & 0xff) - 0x2000) * 2)
	_sync()

## adlib_controller: 1 modulation, 7 volume, 10 pan, 0x40 sustain, 0x5a / 0x5b, 0x7b all notes off
func control(ch: int, num: int, val: int) -> void:
	var c: Channel = channels[ch]
	val &= 0xff
	match num:
		1:
			c.mod = mini((val * 0x82) & 0xffff, 0x4000)
		7:
			c.vol = VOL_GAIN[(val & 0x7e) >> 1]
		10:
			c.pan = _s16(mini((val * 0x82) & 0xffff, 0x4000) * 2 - 0x4000)
		0x40:
			c.sustain = 1 if val & 0x40 else 0
			if c.sustain == 0:
				var held := c.sustained
				c.sustained = 0
				for i in 9:
					if held & (1 << i):
						channel_release(ch, voices[i].note)
		0x5a:
			c.ctl_5a = val
		0x5b:
			c.ctl_5b = val
		0x7b:
			# the voices of the channel's mask, also those another channel has taken since
			var mask := c.used
			for i in 9:
				var b := 1 << i
				if mask & b:
					_voice_off(voices[i], true)
					used_mask &= ~b
					released_mask &= ~b
					free_mask |= b
					c.used &= ~b
					c.sustained &= ~b
	_sync()

## adlib_channel_release: the first voice of the channel playing the note (already released or not)
## waits for the pedal or is released
func channel_release(ch: int, note: int) -> void:
	var c: Channel = channels[ch]
	for i in 9:
		var b := 1 << i
		var v: Voice = voices[i]
		if c.used & b and v.channel == ch and v.note == (note & 0xff):
			if c.sustain != 0:
				c.sustained |= b
			else:
				released_mask |= b
				v.priority >>= 1
				# adlib_voice_release
				if _w(v.timbre, 0x10) != 0:
					v.env_state = 5
				v.key = false
				v.release = _w(v.timbre, 0x4a)
			break
	_sync()

## the note off of the old interface
func note_off(ch: int, note: int) -> void:
	channel_release(ch, note)

## adlib_note_on: the voice of the same note and channel starts again; else a free voice of the
## channel's mask while the channel holds fewer than its maximum, else a released one of the mask,
## else the used voice of the lowest priority; with 8 voices or more on the channel one more voice
## is cut (the original's loop only looks at voice 0)
func note_on(ch: int, note: int, vel: int) -> void:
	var c: Channel = channels[ch]
	note &= 0xff
	var play := note
	if ch == 9:
		if note < 0x24 or note >= 0x64:
			return
		c.program = (note + 0x5c) & 0xff
		play = 0x3c
	# a program without a record or a timbre: the original would play the timbre bound before
	var rec := bank.record(c.program) if bank != null else PackedByteArray()
	if rec.is_empty() or bank.timbre(rec[1], rec[0]).is_empty():
		return
	var lowest := 10000
	var victim := -1
	var mask := c.used
	for i in 9:
		var b := 1 << i
		var v: Voice = voices[i]
		if used_mask & b and v.priority < lowest:
			lowest = v.priority
			victim = i
		if mask & b and v.channel == ch and v.note == note:
			_voice_off(v, true)
			used_mask |= b
			free_mask &= ~b
			released_mask &= ~b
			c.sustained &= ~b
			c.used |= b
			_voice_patch(c, v)
			_load_timbre(v, (v.patch[7] + play) & 0xff, vel)
			_sync()
			return
	var take := -1
	var off := false
	var pick := free_mask & c.allowed
	if _bits(c.used) < c.max_voices and pick != 0:
		take = _lowest_bit(pick)
	else:
		pick = released_mask & c.allowed
		if pick != 0:
			take = _lowest_bit(pick)
		else:
			take = victim
		off = true
	if take < 0:
		return
	var tv: Voice = voices[take]
	if off:
		_voice_off(tv, true)
	var tb := 1 << take
	free_mask &= ~tb
	released_mask &= ~tb
	used_mask |= tb
	c.used |= tb
	c.sustained &= ~tb
	tv.channel = ch
	tv.note = note
	_voice_patch(c, tv)
	_load_timbre(tv, (tv.patch[7] + play) & 0xff, vel)
	if _bits(c.used) + 1 >= 9:
		var cut := victim
		if used_mask & 1 and voices[0].priority < 10000:
			cut = 0
		if cut >= 0:
			var cb := 1 << cut
			_voice_off(voices[cut], false)
			free_mask &= ~cb
			released_mask &= ~cb
			used_mask |= cb
			c.used |= cb
			c.sustained &= ~cb
	_sync()

static func _bits(m: int) -> int:
	var n := 0
	m &= 0xffff
	while m != 0:
		m &= m - 1
		n += 1
	return n

static func _lowest_bit(m: int) -> int:
	for i in 16:
		if m & (1 << i):
			return i
	return -1

## adlib_voice_patch: the record of the channel's program bound to the voice and the channel
func _voice_patch(c: Channel, v: Voice) -> void:
	var rec := bank.record(c.program)
	if rec.is_empty():
		return
	v.program = c.program
	v.timbre = bank.timbre(rec[1], rec[0])
	v.patch = rec
	c.max_voices = rec[6]
	c.allowed = (rec[2] | (rec[3] << 8)) & 0x1ff
	c.priority = rec[0xc] << 4
	v.priority = c.priority
	c.fine = rec[8]
	c.patch_9 = rec[9]
	c.bend_range = rec[0xa]

## adlib_voice_load_timbre: the 13 register bytes, the modulators, the note and the velocity
func _load_timbre(v: Voice, note: int, vel: int) -> void:
	var t := v.timbre
	for i in 13:
		v.regs[i] = t[2 + i]
	if _w(t, 0x10) != 0:
		v.env = _w(t, 0x14)
		v.env_delay = _w(t, 0x12)
		v.env_state = 2 if v.env_delay == 0 else 1
	if _w(t, 0x22) != 0:
		# adlib_env_init (the LFO)
		v.lfo_phase = 0
		v.lfo_count = 0
		v.lfo_raw = 0
		v.lfo_out = 0
		v.lfo_depth = _w(t, 0x28)
		v.lfo_rate = _w(t, 0x2e)
		v.lfo_state = 1
	if _w(t, 0x32) != 0:
		# adlib_lfo_init (the sequence)
		v.seq = 0
		v.seq_len = _w(t, 0x38)
		v.seq_step = t[0x37]
		v.seq_index = -1
		v.seq_delay = _w(t, 0x34)
		if v.seq_delay != 0:
			v.seq_state = 1
		else:
			v.seq_state = 2
			_seq_step(v)
	v.bend_up = 0
	v.bend_down = 0
	v.key = false
	v.base_note = note
	v.cur_note = note
	v.freq = _s16(note_freq(note, 0) + _s8(channels[v.channel].fine))
	v.vel_gain = VEL_GAIN[(vel & 0x7c) >> 2]
	v.key = true
	v.release = -1

## adlib_voice_off: the modulators stopped; with write the key off and the fastest release written
func _voice_off(v: Voice, write: bool) -> void:
	var t := v.timbre
	if _w(t, 0x10) != 0:
		v.env_state = 0
	v.env = 0
	if _w(t, 0x22) != 0:
		v.lfo_state = 0
		v.lfo_raw = 0
		v.lfo_out = 0
	if _w(t, 0x32) != 0:
		v.seq_state = 0
	v.seq = 0
	v.key = false
	v.release = 0
	if write:
		v.regs[0xc] &= 0xdf
		v.regs[3] = (v.regs[3] & 0xf0) | 0x0e
		v.regs[8] = (v.regs[8] & 0xf0) | 0x0e
		_voice_regs(voices.find(v), v)

## stops everything at once (a new song, the end of the match): every used voice off
func all_off() -> void:
	for i in 9:
		var b := 1 << i
		if used_mask & b:
			var v: Voice = voices[i]
			_voice_off(v, true)
			used_mask &= ~b
			released_mask &= ~b
			free_mask |= b
			if v.channel >= 0:
				channels[v.channel].used &= ~b
				channels[v.channel].sustained &= ~b
	for c: Channel in channels:
		c.used = 0
		c.sustained = 0
	_sync()

func _sync() -> void:
	for i in 9:
		voices[i].allocated = used_mask & (1 << i) != 0
		voices[i].released = released_mask & (1 << i) != 0

# --------------------------------------------------------------------------------------------
# the 100 Hz update (adlib_drv_tick)
# --------------------------------------------------------------------------------------------

func tick() -> void:
	for i in 9:
		var b := 1 << i
		if used_mask & b == 0:
			continue
		var v: Voice = voices[i]
		if v.release == 0:
			_voice_off(v, true)
			used_mask &= ~b
			released_mask &= ~b
			free_mask |= b
			channels[v.channel].used &= ~b
			channels[v.channel].sustained &= ~b
			continue
		v.priority = 0 if v.priority < 1 else v.priority - 1
		_output(i, v)
	_sync()

## adlib_voice_update: the working frequency and level through the controls
func _update(v: Voice) -> void:
	var t := v.timbre
	var c: Channel = channels[v.channel]
	v.freq_work = v.freq
	v.vol_work = v.vel_gain
	if _w(t, 0x32) != 0:
		_seq_step(v)
		_modulate(v, _uw(t, 0x32), v.seq)
	_modulate(v, 7, c.bend)
	if _w(t, 0x10) != 0:
		_env_step(v, t)
		_modulate(v, _uw(t, 0x10), v.env)
	if _w(t, 0x22) != 0:
		_lfo_step(v, t)
		_modulate(v, _uw(t, 0x22), v.lfo_out)
	_modulate(v, 5, c.mod)
	_modulate(v, 3, c.vol)

## adlib_env_step (0x9e428): delay, attack to the peak, decay to the sustain, release to 0
func _env_step(v: Voice, t: PackedByteArray) -> void:
	match v.env_state:
		1:
			v.env_delay = _s16(v.env_delay - 1)
			if v.env_delay <= 0:
				v.env_state = 2
		2:
			v.env = _s16(v.env + _w(t, 0x16))
			if v.env >= _w(t, 0x18):
				v.env = _w(t, 0x18)
				v.env_state = 3
		3:
			v.env = _s16(v.env - _w(t, 0x1a))
			if v.env <= _w(t, 0x1c):
				v.env = _w(t, 0x1c)
				v.env_state = 4
		4, 5:
			v.env = _s16(v.env - _w(t, 0x1e if v.env_state == 4 else 0x20))
			if v.env <= 0:
				v.env = 0
				v.env_state = 0

## adlib_env_update (0x9e5c9, the LFO): from tick +0x24 to +0x26 the sine of the phase times the
## depth, limited to +0x2a
func _lfo_step(v: Voice, t: PackedByteArray) -> void:
	var run := false
	if v.lfo_state == 1:
		if v.lfo_count >= _w(t, 0x24):
			if v.lfo_count < _w(t, 0x26):
				v.lfo_state = 2
				run = true
			else:
				v.lfo_state = 0
	elif v.lfo_state == 2:
		run = true
	if run:
		if v.lfo_count >= _w(t, 0x26):
			v.lfo_state = 0
		else:
			v.lfo_phase = (v.lfo_phase + v.lfo_rate) & 0xffff
			v.lfo_raw = _s16(fixmul16(v.lfo_depth << 2, Tables.sin16(v.lfo_phase >> 6)))
	var lim := _w(t, 0x2a)
	if v.lfo_raw > lim:
		v.lfo_out = lim
	elif v.lfo_raw < -lim:
		v.lfo_out = _s16(-lim)
	else:
		v.lfo_out = v.lfo_raw
	v.lfo_count = _s16(v.lfo_count + 1)

## adlib_lfo_step (0x9e511, the step sequence): after the delay a value every +0x37 ticks, for
## +0x38 ticks
func _seq_step(v: Voice) -> void:
	var t := v.timbre
	if v.seq_state == 1:
		v.seq_delay = _s16(v.seq_delay - 1)
		if v.seq_delay > 0:
			return
		v.seq_state = 2
	if v.seq_state != 2:
		return
	v.seq_len = _s16(v.seq_len - 1)
	if v.seq_len <= 0:
		v.seq_state = 0
		v.seq_index = 0
		v.seq = 0
		return
	v.seq_step = _s16(v.seq_step - 1)
	if v.seq_step > 0:
		return
	v.seq_step = t[0x37]
	v.seq_index = _s16(v.seq_index + 1)
	if t[0x36] <= v.seq_index:
		v.seq_index = 0
	v.seq = _w(t, 0x3a + v.seq_index * 2)

## adlib_voice_modulate: a control applied to the working values of the voice
func _modulate(v: Voice, ctrl: int, value: int) -> void:
	value = _s16(value)
	match ctrl:
		1:
			v.cur_note = (v.base_note + value) & 0xff
			v.freq_work = _s16(note_freq(v.cur_note, 0))
		2:
			v.freq_work = _s16(v.freq_work + value)
		3:
			v.vol_work = _s16(fixmul16(v.vol_work << 2, _s16(absi(value))))
		5:
			v.lfo_depth = _s16(_w(v.timbre, 0x28) + fixmul16(value, _w(v.timbre, 0x2c)))
		7:
			var range_: int = channels[v.channel].bend_range
			if value > 0:
				if v.bend_up == 0:
					v.bend_up = _s16(note_freq(v.cur_note, _s8(range_)) - v.freq_work)
				v.freq_work = _s16(v.freq_work + fixmul16(value << 2, v.bend_up & 0xffff))
			elif value < 0:
				if v.bend_down == 0:
					v.bend_down = _s16(v.freq_work - note_freq(v.cur_note, _s8(-range_)))
				v.freq_work = _s16(v.freq_work + fixmul16(value << 2, v.bend_down & 0xffff))
		8:
			v.lfo_rate = _s16(fixmul16(value, _uw(v.timbre, 0x2e)))
		9:
			var lvl := (0x3f - (fixmul16(value, 0x3f) & 0xff)) & 0x3f
			v.regs[6] = (v.regs[6] & 0xc0) | lvl

## adlib_voice_output: the levels from the working volume (the modulator's too with additive
## synthesis), the frequency, the key; then the release count
func _output(i: int, v: Voice) -> void:
	_update(v)
	var t := v.timbre
	if v.regs[10] & 1:
		var m := fixmul16(v.vol_work << 2, 0x3f - (t[8] & 0x3f)) & 0xff
		v.regs[6] = (v.regs[6] & 0xc0) | ((0x3f - m) & 0x3f)
	var cl := fixmul16(v.vol_work << 2, 0x3f - (t[3] & 0x3f)) & 0xff
	v.regs[1] = (v.regs[1] & 0xc0) | ((0x3f - cl) & 0x3f)
	var f := v.freq_work & 0xffff
	v.regs[11] = f & 0xff
	v.regs[12] = (f >> 8) & 0xdf
	if v.key:
		v.regs[12] |= 0x20
	_voice_regs(i, v)
	if v.release > 0:
		v.release -= 1

func active_voices() -> int:
	return _bits(used_mask)
