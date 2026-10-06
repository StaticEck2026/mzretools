class_name Sounds
## Sound effects of the match. play_sfx() hands a sound id to the EA sound driver
## (snd_play_patch 0x8f4c4): the id selects a record of the patch file PCFF001.PAT (FmBank);
## a digital record (type 1) names a timbre of PCFF001.TIM whose 4 byte sample id selects the
## sample of PCFF001.DIG (load_timbre_file), an FM record (type 0) an instrument of PCFF000.TIM that
## MusicPlayer plays (0xab puck drop, 0x94, 0x96). The Sound Blaster driver mixes at 11025 Hz and
## steps through a sample by the note (unity at note 60), so a sample plays at
## 11025 * 2^(transpose / 12) Hz whatever rate its timbre names (the loader overwrites it with
## 11025); the note ends after the record's length (+0xe x 6 ticks, 0xa0 ticks when 0).
## Known ids from the simulation code: 0x7d/0x7e crowd loops (ambient, the volume follows
## crowd_noise), 0x91 period horn (play_sfx turns 0x90 into it), 0x97 one minute warning,
## 0x98/0x99 pass (low/high), 0x9a slap shot, 0x9b puck pick up, 0x9c goal horn, 0x9d/0xa3 puck
## hits a body / stick, 0xa0/0xa1 body check (home/away), 0xa2 stung by the puck, 0xa4 whistle,
## 0xa6 crowd, 0xaa wrist shot, 0xac post, 0xad boards, 0xae glass, 0xb0/0xb2 skates, 0xb1 body
## into the boards.

const CROWD_LOOP := 0x7d
const MIX_RATE := 11025

var effects: Dictionary = {}    # sound id -> AudioStreamWAV
var lengths: Dictionary = {}    # sound id -> note length in seconds
var programs: Dictionary = {}   # digital timbre program -> [PackedFloat32Array -1..1, loop start, loop end] (DacDriver)
var timbre_count: int = 0
var sample_count: int = 0

## Parses PCFF001.PAT / .TIM / .DIG
static func load_bank(pat: PackedByteArray, tim: PackedByteArray, dig: PackedByteArray) -> Sounds:
	if pat.size() < 0x102 or tim.size() < 6 or dig.size() < 6:
		return null
	var s := Sounds.new()
	# the samples by their 4 byte id: n ids from +6, n offsets, the data from 6 + 8 n
	var samples := {}
	var n := dig.decode_u16(4)
	var base := 6 + 8 * n
	for i in n:
		var a := base + dig.decode_u32(6 + 4 * n + 4 * i)
		var b := dig.size() if i + 1 >= n else base + dig.decode_u32(6 + 4 * n + 4 * (i + 1))
		samples[dig.slice(6 + 4 * i, 10 + 4 * i).hex_encode()] = dig.slice(a, b)
	s.sample_count = samples.size()
	# the digital timbres: +2 sample id, +0x14 length, +0x18 / +0x1c loop
	var timbres := {}
	for e in FmBank.parse_tim(tim):
		if e[0] == 1 and e[2].size() >= 0x20:
			timbres[e[1]] = e[2]
	s.timbre_count = timbres.size()
	for prog in timbres:
		var t: PackedByteArray = timbres[prog]
		var key := t.slice(2, 6).hex_encode()
		if not samples.has(key):
			continue
		var raw: PackedByteArray = samples[key]
		var length := t.decode_u32(0x14)
		if length > 0 and length < raw.size():
			raw = raw.slice(0, length)
		var f := PackedFloat32Array()
		f.resize(raw.size())
		for i in raw.size():
			var v := raw[i]
			f[i] = (v - 256 if v >= 128 else v) / 128.0
		var le := t.decode_u32(0x1c)
		s.programs[prog] = [f, t.decode_u32(0x18) if le > 0 else 0, le if le <= raw.size() else 0]
	var bank := FmBank.load_bank(pat, [])
	for id in 256:
		var rec := bank.record(id)
		if rec.is_empty() or rec[0] != 1 or not timbres.has(rec[1]):
			continue
		var t: PackedByteArray = timbres[rec[1]]
		var key := t.slice(2, 6).hex_encode()
		if not samples.has(key):
			continue
		var smp: PackedByteArray = samples[key]
		var length := t.decode_u32(0x14)
		if length > 0 and length < smp.size():
			smp = smp.slice(0, length)
		var transpose := rec[7] - 0x100 if rec[7] >= 0x80 else rec[7]
		var wav := AudioStreamWAV.new()
		wav.format = AudioStreamWAV.FORMAT_8_BITS      # signed, like the sample bank
		wav.stereo = false
		wav.mix_rate = int(round(MIX_RATE * pow(2.0, transpose / 12.0)))
		wav.data = smp
		var loop_start := t.decode_u32(0x18)
		var loop_end := t.decode_u32(0x1c)
		if loop_end > 0 and loop_end <= smp.size():
			wav.loop_mode = AudioStreamWAV.LOOP_FORWARD
			wav.loop_begin = loop_start
			wav.loop_end = loop_end
		s.effects[id] = wav
		s.lengths[id] = (rec[0xe] * 6 if rec[0xe] != 0 else 0xa0) / 100.0
	return s

func has(id: int) -> bool:
	return effects.has(id)

func stream(id: int) -> AudioStreamWAV:
	return effects.get(id, null)

## IFF 8SVX / RIFF WAV samples as read by loadsound() (the screens' music and speech files)
static func load_sample(data: PackedByteArray) -> AudioStreamWAV:
	if data.size() < 12:
		return null
	var tag := data.slice(0, 4).get_string_from_ascii()
	var wav := AudioStreamWAV.new()
	wav.format = AudioStreamWAV.FORMAT_8_BITS
	wav.stereo = false
	if tag == "FORM" and data.slice(8, 12).get_string_from_ascii() == "8SVX":
		var pos := 12
		var rate := 8000
		var body := PackedByteArray()
		while pos + 8 <= data.size():
			var cid := data.slice(pos, pos + 4).get_string_from_ascii()
			var size := _be32(data, pos + 4)
			var payload := data.slice(pos + 8, pos + 8 + size)
			if cid == "VHDR" and payload.size() >= 14:
				rate = (payload[12] << 8) | payload[13]
			elif cid == "BODY":
				body = payload
			pos += 8 + size + (size & 1)
		wav.mix_rate = rate
		wav.data = body
		return wav
	if tag == "RIFF":
		wav.mix_rate = data.decode_u32(24)
		var pcm := data.slice(0x2c)
		for i in pcm.size():
			pcm[i] ^= 0x80       # unsigned WAV -> signed
		wav.data = pcm
		return wav
	return null

static func _be32(d: PackedByteArray, o: int) -> int:
	return (d[o] << 24) | (d[o + 1] << 16) | (d[o + 2] << 8) | d[o + 3]
