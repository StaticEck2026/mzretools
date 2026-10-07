class_name DacDriver
extends RefCounted
## The digital half of the Sound Blaster (sbdac_drv_send_midi 0x9dc9f, sbdac_* 0x9f226..0x9fc94) and
## its software mixer (mix_* 0xa6d84..0xa9c4a), ported from HOCKEY.EXE.
##
## The mixer has four voices that it adds up at 11025 Hz into 8 bit samples for the DMA buffer
## (mix_fill_buffer, mix_to_dma): a voice steps through its signed 8 bit sample by a 16.16 step and
## takes the nearest sample, its volume table (mix_voice_volume) scales a sample by vol / 128 (rounded
## down), the sum is clipped to -128..127. A voice may loop (from the timbre's loop start for its
## loop length); a packed voice holds two 4 bit Fibonacci delta samples a byte (the recordings and
## the speech clips; decoded here up front, the mixer's three speeds 0.5 / 1 / 2 then stepping the
## decoded samples).
##
## The MIDI side gives the voices to the notes: a channel's program selects a digital patch record
## (type 1) whose timbre is the sample, whose voice mask (+2, low 4 bits) says which of the four
## voices it may take, +6 how many at once, +0xc its priority (<< 6, falling by one every tick);
## a note on reuses the voice already playing that note, else takes a free one, else one whose note
## is off, else steals the used one of the lowest priority. The note (with the record's transpose)
## picks the step from the table at 0xd6b00 (2^((note - 60) / 12) in 16.16), the channel's pitch
## bend moves it towards the note + the record's bend range. The velocity does not change the level,
## controller 7 (the channel volume) does. A note off frees the voice for the next note; on voices
## 2 and 3 it also stops the sample (mix_voice_release), on 0 and 1 the sample plays to its end.
## Channel 9 plays the drum patch note + 0x5c at note 60 (notes 0x24..0x63).
##
## Direct samples (playsample, playsample_raw: the speech on voices 0 and 1, the front end's
## recordings on voice 3) take a mixer voice without the MIDI side knowing (mix_play_sample).
##
## The game's patches: the effects use voices 0 / 1 (mask 3), the crowd's roar (0x7d) voice 2 and
## its murmur (0x7e) voice 3 (update_ambient_audio), the stomp of SBROCKU (0x7c) voices 0 / 1.

const MIX_RATE := 11025
const VOICES := 4
const PITCH_TABLE := 0xd6b00          # unk_d6b00: 120 x u32 2^((n - 60) / 12) in 16.16
const CLASS := 4                      # the driver class of the digital records (+0xf of a patch record)

class MixVoice:                       # off_d71f0[i] (0x144 bytes)
	var active := 0                   # +0 1 playing (and looping), 0 stopped
	var volume := 0xff                # +1 (0xff before the first mix_voice_volume)
	var note := 0xff                  # +2
	var data := PackedByteArray()     # signed samples (packed ones decoded)
	var end_pos := 0                  # +0x14 the end, in samples
	var loop_start := 0               # +0xc
	var loop_end := 0                 # +0x10
	var loop_len := 0                 # +4 (0 = no loop)
	var cur_end := 0                  # +0x1c the end of this pass
	var base := 0x10000               # +0x20 sample rate / mix rate (16.16)
	var note_step := 0x10000          # +0x24 / +0x28 the step of the note
	var step := 0x10000               # +0x34 / +0x38 the step with the bend
	var pos := 0                      # +0x2c / +0x30 (16.16, in samples)
	var gain := PackedInt32Array()    # +0x44 the volume table, 256 entries

class Voice:                          # unk_f3454[i] (0x22 bytes) and f34dc[i] (0x16 bytes)
	var bit := 1
	var index := 0
	var priority := 0                 # +6
	var note := 0                     # +8
	var velocity := 0                 # +0xa
	var owner := -1                   # +0xe the channel
	var flag := 0                     # f34e6: 3 started, 1 note off (the bend is applied every tick)
	var bend_range := 0               # f34ec (the record's +0xa)
	var vel_add := 0                  # f34f0 (the record's +0xd)

class Channel:                        # unk_f3534[ch] (0x1e bytes, defaults unk_d522e)
	var mask := 0                     # +0 the voices playing its notes
	var sustained := 0                # +2 voices whose note off waits for the pedal
	var allowed := 0xf                # +4 the voices its patch may use
	var max_voices := 4               # +8
	var record := PackedByteArray()   # +0xe the patch record
	var sample := []                  # +0xa the timbre: [data, rate, loop start, loop length]
	var program := 0xffff             # +6
	var volume := 0x7f                # +0x12
	var pan := 0x40                   # +0x13
	var sustain := 0                  # +0x14
	var modulation := 0               # +0x15
	var bend := 0                     # +0x16 -0x4000..0x3f00

var bank: FmBank
var samples: Dictionary = {}          # digital timbre program -> [PackedByteArray signed, rate, loop start, loop length]
var mix: Array = []
var voices: Array = []
var channels: Array = []
var free_mask := 0xf                  # sbdac_free_mask
var used_mask := 0                    # sbdac_used_mask
var released_mask := 0                # sbdac_released_mask
var pitch := PackedInt32Array()
var out_rate := 22050.0
var level := 0.5                      # the DAC's full scale against the FM chip's
var frac := 0.0                       # output samples per mixer sample, accumulated
var last := 0.0                       # the mixer's current output (held between its samples)
var lp := 0.0                         # the card's output filter

func _init(b: FmBank, sample_table: Dictionary, rate: float) -> void:
	bank = b
	samples = sample_table
	out_rate = rate
	pitch.resize(256)
	for n in 256:
		var v := 0
		if n < 120:
			v = Exe.u32(PITCH_TABLE + n * 4)
			if v == 0:
				v = int(pow(2.0, (n - 60) / 12.0) * 65536.0)
		pitch[n] = v
	for i in VOICES:
		var m := MixVoice.new()
		m.gain.resize(256)
		mix.append(m)
		var v := Voice.new()
		v.bit = 1 << i
		v.index = i
		voices.append(v)
	for c in 16:
		channels.append(Channel.new())

# ---------------------------------------------------------------------------------------------
# the mixer (mix_*)
# ---------------------------------------------------------------------------------------------

## mix_voice_volume: the table of vol * s / 128, rounded down
func mix_volume(i: int, vol: int) -> void:
	var m: MixVoice = mix[i]
	vol &= 0xff
	if vol == m.volume:
		return
	m.volume = vol
	var v := vol if vol < 0x80 else vol - 0x100
	for k in 256:
		var s := k if k < 128 else k - 256
		m.gain[k] = (s * v * 2) >> 8

## mix_voice_pitch: the sample's rate against the mixer's
func mix_pitch(i: int, rate: int) -> void:
	var m: MixVoice = mix[i]
	m.base = int(float(rate) * 65536.0 / MIX_RATE)
	m.note_step = m.base
	m.step = m.base

## mix_voice_sample: the sample, its length and loop (in samples)
func mix_sample(i: int, data: PackedByteArray, length: int, loop_start: int, loop_len: int) -> void:
	var m: MixVoice = mix[i]
	m.data = data
	m.end_pos = mini(length, data.size())
	m.loop_start = loop_start
	m.loop_end = mini(loop_start + loop_len, m.end_pos)
	m.loop_len = loop_len if m.loop_end > m.loop_start else 0

## mix_voice_velocity: the step of the note (0xff keeps the step), back to the start, playing
func mix_velocity(i: int, note: int) -> void:
	var m: MixVoice = mix[i]
	m.note = note & 0xff
	if m.note != 0xff:
		var s := (pitch[m.note] * m.base) >> 16
		m.note_step = s
		m.step = s
	m.cur_end = m.loop_end if m.loop_len != 0 else m.end_pos
	m.pos = 0
	m.active = 1

## mix_voice_release / mix_voice_stop: only voices 2 and 3 stop
func mix_stop(i: int) -> void:
	if i > 1:
		var m: MixVoice = mix[i]
		m.cur_end = m.loop_end
		m.active = 0

func mix_free(i: int) -> bool:
	return (mix[i] as MixVoice).active == 0

## mix_voice_position: the step of the note moved by the bend towards the note + range
func mix_position(i: int, bend: int, bend_range: int) -> void:
	var m: MixVoice = mix[i]
	var s := m.note_step
	if bend != 0:
		var target := (pitch[(m.note + bend_range) & 0xff] * m.base) >> 16
		var diff := target - s
		if bend < 0:
			s -= (diff * -bend) >> 14
		else:
			s += (diff * bend) >> 14
	m.step = s

## mix_play_sample (drv_play_sample): a sample straight on a voice; rate 0 releases it
func play_sample(i: int, data: PackedByteArray, rate: int, volume: int, loop_start: int = 0, loop_len: int = 0, packed: bool = false) -> void:
	if i < 0 or i >= VOICES:
		return
	if rate == 0:
		mix_stop(i)
		return
	var d := Sounds.fibdelta_decode(data) if packed else data
	var k := 2 if packed else 1
	mix_pitch(i, rate)
	mix_volume(i, volume)
	mix_sample(i, d, d.size(), loop_start * k, loop_len * k)
	mix_velocity(i, 0xff)

## one sample of the mixer (-128..127)
func _mix_one() -> int:
	var sum := 0
	for m: MixVoice in mix:
		if m.active == 0:
			continue
		var k := m.pos >> 16
		if k >= m.cur_end:
			if m.active == 1 and m.loop_len != 0:
				m.pos -= (m.loop_end - m.loop_start) << 16
				m.cur_end = m.loop_end
				k = m.pos >> 16
			else:
				m.active = 0
				continue
		sum += m.gain[m.data[k]]
		m.pos += m.step
	return clampi(sum, -128, 127)

func active() -> int:
	var n := 0
	for m: MixVoice in mix:
		if m.active != 0:
			n += 1
	return n

## n output samples added to out: the mixer at 11025 Hz held for each output sample, through a
## one pole low pass for the card's output stage
func render(out: PackedFloat32Array, offset: int, n: int) -> void:
	var ratio := MIX_RATE / out_rate
	var a := 0.6
	for i in n:
		frac += ratio
		while frac >= 1.0:
			frac -= 1.0
			last = _mix_one() / 128.0 * level
		lp += (last - lp) * a
		out[offset + i] += lp

func all_off() -> void:
	for i in VOICES:
		(mix[i] as MixVoice).active = 0
		_voice_free(voices[i])

# ---------------------------------------------------------------------------------------------
# the driver (sbdac_*)
# ---------------------------------------------------------------------------------------------

## sbdac_drv_send_midi: one message (the notes already moved by drv_send_midi)
func midi(status: int, d1: int, d2: int) -> void:
	var ch := status & 0xf
	match status & 0xf0:
		0x80:
			notes_off(ch, d1)
		0x90:
			if d2 == 0:
				notes_off(ch, d1)
			else:
				note_on(ch, d1, d2)
		0xb0:
			controller(ch, d1, d2)
		0xc0:
			program(ch, d1)
		0xe0:
			channels[ch].bend = d2 * 0x100 - 0x4000

## sbdac_program: the patch record (a digital one; the FM driver takes the others)
func program(ch: int, prog: int) -> void:
	var c: Channel = channels[ch]
	var rec := bank.record(prog & 0xff) if bank != null else PackedByteArray()
	if rec.is_empty() or (rec[0xf] & 0x7f) != CLASS:
		c.record = PackedByteArray()
		c.sample = []
		c.allowed = 0
		return
	c.record = rec
	c.sample = samples.get(rec[1], [])
	c.max_voices = 4 if ch == 9 else rec[6]
	c.allowed = (rec[2] | (rec[3] << 8)) & 0xf
	c.program = prog

static func _s8(v: int) -> int:
	return v - 256 if v >= 128 else v

## sbdac_note_on: a voice for the note
func note_on(ch: int, note: int, vel: int) -> void:
	var c: Channel = channels[ch]
	var play := note
	if ch == 9:
		if note < 0x24 or note > 99:
			return
		program(9, note + 0x5c)
		play = 0x3c
	if c.allowed == 0 or c.max_voices == 0 or c.sample.is_empty():
		return
	var lowest := 32000
	var steal: Voice = voices[0]
	for v: Voice in voices:
		if used_mask & v.bit & c.allowed != 0 and v.priority < lowest:
			lowest = v.priority
			steal = v
		if v.bit & c.mask & c.allowed != 0 and v.owner == ch and v.note == note:
			_voice_start(play, note, vel, ch, v)
			return
	var count := 0
	for v: Voice in voices:
		if c.mask & v.bit:
			count += 1
	var pick: Voice = null
	if count < c.max_voices and free_mask & c.allowed != 0:
		pick = _lowest(free_mask & c.allowed)
	elif released_mask & c.allowed != 0:
		pick = _lowest(released_mask & c.allowed)
	else:
		pick = steal
	_voice_start(play, note, vel, ch, pick)

func _lowest(mask: int) -> Voice:
	for v: Voice in voices:
		if mask & v.bit:
			return v
	return voices[0]

## sbdac_voice_start + sbdac_voice_setup + sbdac_voice_volume
func _voice_start(play: int, note: int, vel: int, ch: int, v: Voice) -> void:
	var c: Channel = channels[ch]
	v.flag = 0
	mix_stop(v.index)
	if v.owner >= 0:
		var old: Channel = channels[v.owner]
		old.mask &= ~v.bit
		old.sustained &= ~v.bit
	v.owner = ch
	var rec := c.record
	v.priority = rec[0xc] << 6
	v.bend_range = _s8(rec[0xa])
	v.vel_add = rec[0xd]
	var s: Array = c.sample
	mix_pitch(v.index, s[1])
	mix_sample(v.index, s[0], (s[0] as PackedByteArray).size(), s[2], s[3])
	v.note = note
	v.velocity = vel
	free_mask &= ~v.bit
	used_mask |= v.bit
	released_mask &= ~v.bit
	c.mask |= v.bit
	c.sustained &= ~v.bit
	v.flag = 3
	mix_velocity(v.index, _s8(rec[7]) + play)
	mix_volume(v.index, c.volume)

## sbdac_channel_notes_off
func notes_off(ch: int, note: int) -> void:
	var c: Channel = channels[ch]
	for v: Voice in voices:
		if c.mask & v.bit and v.owner == ch and v.note == note:
			if c.sustain != 0:
				c.sustained |= v.bit
				return
			released_mask |= v.bit
			v.priority >>= 1
			v.flag = 1
			mix_stop(v.index)
			return

## sbdac_voice_free
func _voice_free(v: Voice) -> void:
	v.flag = 0
	mix_stop(v.index)
	v.priority = 0
	free_mask |= v.bit
	used_mask &= ~v.bit
	released_mask &= ~v.bit
	if v.owner >= 0:
		var c: Channel = channels[v.owner]
		c.mask &= ~v.bit
		c.sustained &= ~v.bit

## sbdac_controller: 1 modulation, 7 volume, 10 pan, 0x40 sustain, 0x7b all notes off
func controller(ch: int, num: int, val: int) -> void:
	var c: Channel = channels[ch]
	match num:
		1:
			c.modulation = val
		7:
			c.volume = val
		10:
			c.pan = val
		0x40:
			c.sustain = val
			if val == 0:
				var held := c.sustained
				c.sustained = 0
				for v: Voice in voices:
					if held & v.bit:
						notes_off(ch, v.note)
		0x7b:
			for v: Voice in voices:
				if c.mask & v.bit:
					_voice_free(v)
	if num == 7:
		for v: Voice in voices:
			if c.mask & v.bit:
				mix_volume(v.index, val)

## sbdac_drv_tick (100 Hz): voices whose note is off and whose sample ended are free again, the
## priorities fall, the bend is applied
func tick() -> void:
	for v: Voice in voices:
		if released_mask & v.bit and mix_free(v.index):
			_voice_free(v)
		v.priority = maxi(v.priority - 1, 0)
	for v: Voice in voices:
		if v.flag != 0 and v.owner >= 0:
			mix_position(v.index, (channels[v.owner] as Channel).bend, v.bend_range)
