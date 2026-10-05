class_name RinkTiles
## rink.til / rink.map renderer (load_rink / load_rink_tiles). Produces the 8 bit index image of
## the rink surface; the game renders it into a 384x592 off-screen window.

static func render(til: PackedByteArray, mapdata: PackedByteArray, pal: PackedColorArray) -> Image:
	if mapdata.size() < 6:
		return null
	var w := mapdata.decode_u16(0)
	var h := mapdata.decode_u16(2)
	var img := Image.create(w * 8, h * 8, false, Image.FORMAT_RGBA8)
	img.fill(Color(0, 0, 0, 0))
	for cy in h:
		for cx in w:
			var c := mapdata.decode_u16(6 + (cy * w + cx) * 2)
			var t := (c & 0x3ff) * 64
			if t + 64 > til.size():
				continue
			for yy in 8:
				var sy := 7 - yy if c & 0x4000 else yy
				for xx in 8:
					var sx := 7 - xx if c & 0x2000 else xx
					var p := til[t + sy * 8 + sx]
					if p != 0xff:
						img.set_pixel(cx * 8 + xx, cy * 8 + yy, pal[p] if p < pal.size() else Color.MAGENTA)
	return img
