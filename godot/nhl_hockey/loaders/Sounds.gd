class_name Sounds
## Sound effects of the match. play_sfx() hands a sound id to the EA sound driver
## (sub_8f4c4): the id selects a record of the patch file PCFF001.PAT, digital records name a
## timbre of PCFF001.TIM whose sample lives in PCFF001.DIG (see re/nhl_hockey/FORMATS.md).
## Ids that are FM instruments only (0x90 period horn, 0xab puck drop, 0x96 crowd) fall back to a
## similar sample. Known ids from the simulation code: 0x7d/0x7e crowd loops (ambient, the
## volume follows crowd_noise), 0x90 period horn, 0x97 one minute warning, 0x98/0x99 pass
## (low/high), 0x9a slap shot, 0x9b puck pick up, 0x9c goal horn, 0x9d/0xa3 puck hits a body /
## stick, 0xa0/0xa1 body check (home/away), 0xa2 stung by the puck, 0xa4 whistle, 0xa6 crowd,
## 0xaa wrist shot, 0xab puck drop, 0xac post, 0xad boards, 0xae glass, 0xb0/0xb2 skates,
## 0xb1 body into the boards.

const FM_FALLBACK := {0x90: 0x9c, 0xab: 0x9b, 0x96: 0xa6}
const CROWD_LOOP := 0x7d

var effects: Dictionary = {}    # sound id -> AudioStreamWAV
var timbre_count: int = 0
var sample_count: int = 0

## Parses PCFF001.PAT / .TIM / .DIG
static func load_bank(pat: PackedByteArray, tim: PackedByteArray, dig: PackedByteArray) -> Sounds:
	if pat.size() < 0x102 or tim.size() < 0x106 or dig.size() < 0xf6:
		return null
	var s := Sounds.new()
	# timbres: 32 byte records from +0x106: +0xa rate, +0xc length, +0x10/+0x14 loop
	var count := tim.decode_u16(4)
	var timbres := []
	for k in count - 1:
		var o := 0x106 + k * 32
		if o + 32 > tim.size():
			break
		timbres.append([tim.decode_u16(o + 10), tim.decode_u32(o + 12), tim.decode_u32(o + 16), tim.decode_u32(o + 20)])
	s.timbre_count = timbres.size()
	# samples: u16 count at +4, start offsets of samples 1..n-1 at +0x82, data from +0xf6
	var n := dig.decode_u16(4)
	var starts := [0]
	for i in n - 1:
		starts.append(dig.decode_u32(0x82 + 4 * i))
	var samples := []
	var by_length := {}
	for i in n:
		var a: int = starts[i]
		var b: int = starts[i + 1] if i + 1 < n else dig.size() - 0xf6
		var smp := dig.slice(0xf6 + a, 0xf6 + b)
		if not by_length.has(smp.size()):
			by_length[smp.size()] = i
		samples.append(smp)
	s.sample_count = samples.size()
	# patch records: +2 id -> record map, 0x14 byte records from +0x102
	for id in 256:
		var rec := pat[2 + id]
		if rec == 0 and id != 0:
			continue
		var o := 0x102 + rec * 0x14
		if o + 0x14 > pat.size() or pat[o] != 1:
			continue
		var k := pat[o + 1] - 1
		if k < 0 or k >= timbres.size():
			continue
		var t: Array = timbres[k]
		if not by_length.has(t[1]):
			continue
		var smp: PackedByteArray = samples[by_length[t[1]]]
		var transpose := pat[o + 7]
		if transpose >= 0x80:
			transpose -= 0x100
		var wav := AudioStreamWAV.new()
		wav.format = AudioStreamWAV.FORMAT_8_BITS      # signed, like the sample bank
		wav.stereo = false
		wav.mix_rate = int(round(t[0] * pow(2.0, transpose / 12.0)))
		wav.data = smp
		if t[3] > 0 and t[3] <= smp.size():
			wav.loop_mode = AudioStreamWAV.LOOP_FORWARD
			wav.loop_begin = t[2]
			wav.loop_end = t[3]
		s.effects[id] = wav
	for id in FM_FALLBACK:
		if not s.effects.has(id) and s.effects.has(FM_FALLBACK[id]):
			s.effects[id] = s.effects[FM_FALLBACK[id]]
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
