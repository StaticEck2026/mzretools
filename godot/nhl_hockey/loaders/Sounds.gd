class_name Sounds
## IFF 8SVX / RIFF WAV samples as read by loadsound(), returned as AudioStreamWAV.
##
## The simulation queues the sample ids of the original (play_sfx -> sound id). Which file holds
## which sample is not recoverable from the executable alone, so the mapping is a user editable
## table: put the sample files of your installation into the game directory and name them here.
## Known ids (from the code that queues them): 0x7d/0xa0 hit (away/home), 0x90 period horn,
## 0x97 one minute warning, 0x98/0x99 pass (low/high), 0x9a slap shot, 0x9b puck pick up,
## 0x9c goal horn, 0x9d/0xa3 puck hits a body/stick, 0xa1 big hit, 0xa2 stung by the puck,
## 0xa4 whistle, 0xa6/0x96 crowd, 0xaa wrist shot, 0xab puck drop/bounce, 0xac post,
## 0xad boards, 0xae glass, 0xb0/0xb2 skates, 0xb1 body into the boards.
const SFX_FILES := {
	0x9c: "goalhorn.snd",
	0xa4: "whistle.snd",
	0xab: "puckdrop.snd",
	0xac: "post.snd",
	0xad: "boards.snd",
	0xaa: "wristshot.snd",
	0x9a: "slapshot.snd",
	0x99: "pass.snd",
	0x90: "horn.snd",
}

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
		wav.data = body          # Godot's 8 bit format is signed, like 8SVX
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
