class_name Shpi
## SHPI shape bank reader (loadshapes / locateshape / getshape / drawshape of HOCKEY.EXE).
## See re/nhl_hockey/FORMATS.md for the layout.

class Shape:
	var name: String
	var code: int
	var width: int
	var height: int
	var center_x: int      # hotspot (+8, +0xa)
	var center_y: int
	var x: int             # position (+0xc, +0xe)
	var y: int
	var pixels: PackedByteArray   # 8 bit indices (code 0x7b)
	var palette: PackedColorArray # for palette entries

	func is_image() -> bool:
		return code == 0x7b and width > 0 and height > 0

	## Converts the indexed pixels to an RGBA8 image with the given palette; index 0 is transparent
	func to_image(pal: PackedColorArray) -> Image:
		var img := Image.create(width, height, false, Image.FORMAT_RGBA8)
		for yy in height:
			for xx in width:
				var p := pixels[yy * width + xx]
				if p == 0:
					img.set_pixel(xx, yy, Color(0, 0, 0, 0))
				else:
					img.set_pixel(xx, yy, pal[p] if p < pal.size() else Color.MAGENTA)
		return img

	func to_texture(pal: PackedColorArray) -> ImageTexture:
		return ImageTexture.create_from_image(to_image(pal))

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
		s.center_x = data.decode_u16(off + 8)
		s.center_y = data.decode_u16(off + 10)
		s.x = data.decode_u16(off + 12) & 0xfff
		s.y = data.decode_u16(off + 14) & 0xfff
		if s.code == 0x7b:
			s.pixels = data.slice(off + 16, off + 16 + s.width * s.height)
		elif s.code in [0x2d, 0x24, 0x2a, 0x29] or name.to_lower().ends_with("pal"):
			s.palette = decode_palette(data.slice(off + 16, off + 16 + 0x400), s.code)
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

## The game sends 0x300 bytes to the VGA DAC: 256 x RGB with 6 bit components
static func decode_palette(raw: PackedByteArray, code: int) -> PackedColorArray:
	var pal := PackedColorArray()
	if code == 0x2a:
		for i in 256:
			if i * 4 + 3 >= raw.size():
				break
			pal.append(Color8(raw[i * 4], raw[i * 4 + 1], raw[i * 4 + 2]))
		return pal
	var maxv := 0
	var n := mini(256, raw.size() / 3)
	for i in n:
		maxv = maxi(maxv, maxi(raw[i * 3], maxi(raw[i * 3 + 1], raw[i * 3 + 2])))
	var scale := 255.0 / 63.0 if maxv <= 63 else 1.0
	for i in n:
		pal.append(Color8(int(raw[i * 3] * scale), int(raw[i * 3 + 1] * scale), int(raw[i * 3 + 2] * scale)))
	return pal
