class_name Sounds
## IFF 8SVX / RIFF WAV samples as read by loadsound(), returned as AudioStreamWAV.

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
