class_name RefPack
## EA RefPack decompressor (10FB/11FB) and the pack code dispatcher of the game's unpack()
## (HOCKEY.EXE 0x97eb8 / refpack_decode 0x97ce0). See re/nhl_hockey/FORMATS.md.

static func pack_code(data: PackedByteArray) -> int:
	if data.size() < 5 or data[1] != 0xfb:
		return -1
	return data[0] & 0xfe

## Returns the input unchanged when it is not compressed
static func unpack(data: PackedByteArray) -> PackedByteArray:
	var code := pack_code(data)
	match code:
		-1:
			return data
		0x10:
			return decompress(data)
		0x60, 0x62, 0x66:
			return delta_decode(data)
		0x6a, 0x6e:
			var size := (data[2] << 16) | (data[3] << 8) | data[4]
			return data.slice(5, 5 + size)
		_:
			push_error("pack code 0x%02x is not implemented" % code)
			return PackedByteArray()

static func decompress(data: PackedByteArray) -> PackedByteArray:
	var hdr := (data[0] << 8) | data[1]
	var pos := 2
	if hdr & 0x100:
		pos += 3
	var size := (data[pos] << 16) | (data[pos + 1] << 8) | data[pos + 2]
	pos += 3
	var out := PackedByteArray()
	out.resize(size)
	var o := 0
	var n := data.size()
	while pos < n:
		var b := data[pos]
		pos += 1
		var lit := 0
		var copy := 0
		var off := 0
		if b < 0x80:
			var b2 := data[pos]
			pos += 1
			lit = b & 3
			copy = ((b & 0x1c) >> 2) + 3
			off = ((b & 0x60) << 3) + b2 + 1
		elif b < 0xc0:
			var b2 := data[pos]
			var b3 := data[pos + 1]
			pos += 2
			lit = b2 >> 6
			copy = (b & 0x3f) + 4
			off = ((b2 & 0x3f) << 8) + b3 + 1
		elif b < 0xe0:
			var b2 := data[pos]
			var b3 := data[pos + 1]
			var b4 := data[pos + 2]
			pos += 3
			lit = b & 3
			copy = ((b & 0x0c) << 6) + b4 + 5
			off = ((b & 0x10) << 12) + (b2 << 8) + b3 + 1
		elif b < 0xfc:
			lit = ((b & 0x1f) + 1) * 4
		else:
			lit = b & 3
		if o + lit + copy > size:
			out.resize(o + lit + copy)
		for i in lit:
			out[o] = data[pos + i]
			o += 1
		pos += lit
		if copy > 0:
			var src := o - off
			for i in copy:
				out[o] = out[src + i]
				o += 1
		if b >= 0xfc:
			break
	if o != out.size():
		out.resize(o)
	return out

static func delta_decode(data: PackedByteArray) -> PackedByteArray:
	var hdr := (data[0] << 8) | data[1]
	var pos := 2
	if hdr == 0x62fb:
		pos = 5
	elif hdr == 0x66fb:
		pos = 6
	var size := (data[pos] << 16) | (data[pos + 1] << 8) | data[pos + 2]
	pos += 3
	var out := PackedByteArray()
	out.resize(size)
	var acc := 0
	for i in size:
		acc = (acc + data[pos + i]) & 0xff
		out[i] = acc
	return out
