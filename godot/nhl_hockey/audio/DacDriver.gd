class_name DacDriver
extends RefCounted
## The digital half of the Sound Blaster driver (SB30.BGP) for the music: a note whose patch
## record is digital (type 1) plays the sample of its timbre (PCFF001.TIM / .DIG, see Sounds).
## The driver mixes in software at 11025 Hz (DSP time constant for 0x2b11) and steps through a
## sample by the note: the step table at DS:0x1f6 holds 2^((note - 60) / 12) as 4.12 fixed point
## (note 60 plays the sample as recorded at 11025 Hz). The note gets the patch's transpose (+7)
## like the FM driver's; the velocity and the channel volume scale the level. Used by SBROCKU, the
## stomp to the clapping crowd.

const DAC_RATE := 11025.0

class Voice:
	var channel := -1
	var note := -1
	var data := PackedFloat32Array()
	var pos := 0.0
	var step := 1.0
	var loop_start := 0
	var loop_end := 0
	var gain := 1.0
	var vel := 127

var bank: FmBank
var samples: Dictionary = {}      # timbre program -> [PackedFloat32Array, loop start, loop end]
var programs := PackedInt32Array()
var volumes := PackedInt32Array()
var voices: Array = []
var out_rate := 22050.0
var level := 0.5

func _init(b: FmBank, sample_table: Dictionary, rate: float) -> void:
	bank = b
	samples = sample_table
	out_rate = rate
	programs.resize(16)
	volumes.resize(16)
	volumes.fill(0x7f)

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
			if d1 == 7:
				volumes[ch] = d2
				for v in voices:
					if v.channel == ch:
						v.gain = _gain(v.vel, d2)
			elif d1 == 0x7b:
				for v in voices:
					if v.channel == ch:
						v.channel = -1
		0xc0:
			programs[ch] = d1

func _gain(vel: int, vol: int) -> float:
	return level * vel / 127.0 * vol / 127.0

func note_on(ch: int, note: int, vel: int) -> void:
	var program := programs[ch]
	var play := note
	if ch == 9:
		program = note + 0x5c
		play = 0x3c
	var rec := bank.record(program & 0xff)
	if rec.is_empty() or rec[0] != 1 or not samples.has(rec[1]):
		return
	var s: Array = samples[rec[1]]
	var transpose: int = rec[7] - 0x100 if rec[7] >= 0x80 else rec[7]
	var v := Voice.new()
	v.channel = ch
	v.note = note
	v.data = s[0]
	v.loop_start = s[1]
	v.loop_end = s[2]
	v.step = pow(2.0, (play + transpose - 60) / 12.0) * DAC_RATE / out_rate
	v.vel = vel
	v.gain = _gain(vel, volumes[ch])
	voices.append(v)

func note_off(ch: int, note: int) -> void:
	for v in voices:
		if v.channel == ch and v.note == note:
			v.channel = -1
			break

func all_off() -> void:
	voices.clear()

func active() -> int:
	var n := 0
	for v in voices:
		if v.channel >= 0:
			n += 1
	return n

func render(out: PackedFloat32Array, offset: int, n: int) -> void:
	var keep: Array = []
	for item in voices:
		var v: Voice = item
		if v.channel < 0:
			continue
		var d: PackedFloat32Array = v.data
		var size := d.size()
		var pos := v.pos
		var looped := v.loop_end > v.loop_start
		for i in n:
			var k := int(pos)
			if k >= size or (looped and k >= v.loop_end):
				if looped:
					pos -= v.loop_end - v.loop_start
					k = int(pos)
				else:
					v.channel = -1
					break
			out[offset + i] += d[k] * v.gain
			pos += v.step
		v.pos = pos
		if v.channel >= 0:
			keep.append(v)
	voices = keep
