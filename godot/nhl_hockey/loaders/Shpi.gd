class_name Shpi
## SHPI shape bank reader (loadshapes / locateshape / getshape / drawshape / blit_sprite of
## HOCKEY.EXE). See re/nhl_hockey/FORMATS.md for the layout.

class Shape:
	var name: String
	var code: int
	var width: int
	var height: int
	var center_x: int      # hotspot (+8, +0xa); blit_sprite draws the frame at (x - center_x, y - center_y)
	var center_y: int
	var x: int             # position (+0xc, +0xe) used by drawshape_home / blit_rle_frame_home
	var y: int
	var pixels: PackedByteArray   # 8 bit indices
	var transparent: int = 0      # 0 for plain shapes (drawshape), 0xff for the run length frames
	var raw: PackedByteArray      # first 0x400 bytes of a palette entry
	var palette: PackedColorArray # decoded palette entries

	func is_image() -> bool:
		return width > 0 and height > 0 and pixels.size() >= width * height

	## Converts the indexed pixels to an RGBA8 image. `remap` (256 bytes) is the colour remap table
	## of blit_sprite (team colours); the transparent index becomes alpha 0.
	func to_image(pal: PackedColorArray, remap: PackedByteArray = PackedByteArray()) -> Image:
		return Shpi.indexed_to_image(pixels, width, height, pal, transparent, remap)

	func to_texture(pal: PackedColorArray, remap: PackedByteArray = PackedByteArray()) -> ImageTexture:
		return ImageTexture.create_from_image(to_image(pal, remap))

var dir_id: String
var shapes: Array[Shape] = []
var _by_name: Dictionary = {}

static func parse(data: PackedByteArray) -> Shpi:
	data = RefPack.unpack(data)
	if data.size() < 16 or data.slice(0, 4).get_string_from_ascii() != "SHPI":
		return null
	var bank := Shpi.new()
	bank.dir_id = data.slice(12, 16).get_string_from_ascii()
	var count := data.decode_u32(8)
	for i in count:
		var name := data.slice(16 + i * 8, 20 + i * 8).get_string_from_ascii()
		var off := data.decode_u32(20 + i * 8)
		if off + 16 > data.size():
			continue
		var s := Shape.new()
		s.name = name
		s.code = data[off]
		s.width = data.decode_u16(off + 4)
		s.height = data.decode_u16(off + 6)
		s.center_x = data.decode_s16(off + 8)
		s.center_y = data.decode_s16(off + 10)
		s.x = data.decode_u16(off + 12) & 0xfff
		s.y = data.decode_u16(off + 14) & 0xfff
		if s.code & 0x80:
			# sprite frames (.PPV banks, codes 0xfb / 0x80 / 0x81): run length coded, 0xff = transparent
			s.pixels = rle_decode(data, off + 16, s.width * s.height)
			s.transparent = 0xff
		elif s.code == 0x7b:
			s.pixels = data.slice(off + 16, off + 16 + s.width * s.height)
		elif s.code in [0x2d, 0x24, 0x2a, 0x29, 0x22, 0x2f] or (s.code != 0 and name.to_lower().ends_with("pal")):
			s.raw = data.slice(off + 16, off + 16 + 0x400)
			s.palette = decode_palette(s.raw, s.code)
		bank.shapes.append(s)
		if not bank._by_name.has(name):
			bank._by_name[name] = s
	return bank

## locateshape(): entry by its 4 character tag
func find(name: String) -> Shape:
	return _by_name.get((name + "    ").substr(0, 4), null)

func palette() -> PackedColorArray:
	for s in shapes:
		if s.palette.size() > 0:
			return s.palette
	return PackedColorArray()

## Pixel stream of the sprite frames (blit_sprite -> blit_rle_frame): a count byte c followed by
## c in 1..0x7f: one colour byte repeated c times (colour 0xff = c transparent pixels, the blitter
## skips them), c >= 0x80: 0x100 - c literal colour bytes, c == 0: end of the frame.
static func rle_decode(data: PackedByteArray, pos: int, count: int) -> PackedByteArray:
	var out := PackedByteArray()
	out.resize(count)
	out.fill(0xff)
	var n := 0
	var size := data.size()
	while pos < size and n < count:
		var c := data[pos]
		pos += 1
		if c == 0:
			break
		if c < 0x80:
			if pos >= size:
				break
			var v := data[pos]
			pos += 1
			var run := mini(c, count - n)
			for i in run:
				out[n + i] = v
			n += run
		else:
			var k := mini(0x100 - c, count - n)
			for i in k:
				if pos + i < size:
					out[n + i] = data[pos + i]
			pos += 0x100 - c
			n += k
	return out

## Indexed pixels -> RGBA8 image (transparent < 0: every pixel opaque)
static func indexed_to_image(pixels: PackedByteArray, w: int, h: int, pal: PackedColorArray, transparent: int, remap: PackedByteArray = PackedByteArray()) -> Image:
	var buf := PackedByteArray()
	buf.resize(w * h * 4)
	var use_remap := remap.size() >= 256
	var npal := pal.size()
	for i in w * h:
		var p := pixels[i]
		if p == transparent:
			continue
		if use_remap:
			p = remap[p]
		var o := i * 4
		if p < npal:
			var c := pal[p]
			buf[o] = c.r8
			buf[o + 1] = c.g8
			buf[o + 2] = c.b8
		else:
			buf[o] = 255
			buf[o + 2] = 255
		buf[o + 3] = 255
	return Image.create_from_data(w, h, false, Image.FORMAT_RGBA8, buf)

## The game sends 0x300 bytes to the VGA DAC: 256 x RGB with 6 bit components
static func decode_palette(raw: PackedByteArray, code: int) -> PackedColorArray:
	var pal := PackedColorArray()
	if code == 0x2a:
		for i in 256:
			if i * 4 + 3 >= raw.size():
				break
			pal.append(Color8(raw[i * 4], raw[i * 4 + 1], raw[i * 4 + 2]))
		return pal
	if code == 0x29:
		for i in 256:
			if i * 2 + 1 >= raw.size():
				break
			var v := raw[i * 2] | (raw[i * 2 + 1] << 8)
			pal.append(Color8(((v >> 11) & 31) * 255 / 31, ((v >> 5) & 63) * 255 / 63, (v & 31) * 255 / 31))
		return pal
	var maxv := 0
	var n := mini(256, raw.size() / 3)
	for i in n:
		maxv = maxi(maxv, maxi(raw[i * 3], maxi(raw[i * 3 + 1], raw[i * 3 + 2])))
	var scale := 255.0 / 63.0 if maxv <= 63 else 1.0
	for i in n:
		pal.append(Color8(int(raw[i * 3] * scale), int(raw[i * 3 + 1] * scale), int(raw[i * 3 + 2] * scale)))
	return pal
