class_name Vfn
## 1 bpp VFN bitmap fonts (setfont / printstr). Draws text into an Image.

var data: PackedByteArray
var first: int
var last: int
var def_width: int
var height: int
var spacing: int
var width_tab: int
var height_tab: int
var adv_tab: int
var xoff_tab: int
var yoff_tab: int
var glyph_base: int

static func parse(d: PackedByteArray) -> Vfn:
	if d.size() < 0x24:
		return null
	var f := Vfn.new()
	f.data = d
	f.first = d[4]
	f.last = d[5]
	f.def_width = d[6]
	f.height = d[7]
	f.spacing = d[8]
	f.width_tab = d.decode_u16(0x12)
	f.height_tab = d.decode_u16(0x14)
	f.adv_tab = d.decode_u16(0x16)
	f.xoff_tab = d.decode_u16(0x18)
	f.yoff_tab = d.decode_u16(0x1a)
	f.glyph_base = d.decode_u32(0x1c)
	if f.glyph_base >= d.size():
		f.glyph_base = 0      # +0x1c holds a tag ('FNTX', 'FNED'): the glyph offsets at +0x20 are absolute
	return f

func glyph_width(c: int) -> int:
	return data[width_tab + c - first] if width_tab != 0 else def_width

func glyph_height(c: int) -> int:
	return data[height_tab + c - first] if height_tab != 0 else height

func advance(c: int) -> int:
	return data[adv_tab + c - first] if adv_tab != 0 else glyph_width(c) + spacing

## the character codes of the text (Latin-1: the fonts have glyphs above 0x7f, e.g. 0xa8 and 0xa9)
static func codes(s: String) -> PackedInt32Array:
	var out := PackedInt32Array()
	out.resize(s.length())
	for i in s.length():
		out[i] = s.unicode_at(i)
	return out

func text_width(s: String) -> int:
	var w := 0
	for c in codes(s):
		if c >= first and c <= last:
			w += advance(c)
	return w

## Renders `s` into a new transparent image
func render(s: String, color: Color) -> Image:
	var w := maxi(text_width(s), 1)
	var img := Image.create(w, height, false, Image.FORMAT_RGBA8)
	draw(img, s, 0, 0, color)
	return img

## Draws `s` into `img` at (x, y) with `color`
func draw(img: Image, s: String, x: int, y: int, color: Color) -> void:
	for c in codes(s):
		if c < first or c > last:
			continue
		var i := c - first
		var off := glyph_base + data.decode_u32(0x20 + i * 4)
		var w := glyph_width(c)
		var h := glyph_height(c)
		var stride := (w + 7) >> 3
		var gx := x + (data[xoff_tab + i] if xoff_tab != 0 else 0)
		var gy := y + (data[yoff_tab + i] if yoff_tab != 0 else 0)
		for yy in h:
			for xx in w:
				var b := off + yy * stride + (xx >> 3)
				if b < data.size() and (data[b] >> (7 - (xx & 7))) & 1:
					var px := gx + xx
					var py := gy + yy
					if px >= 0 and py >= 0 and px < img.get_width() and py < img.get_height():
						img.set_pixel(px, py, color)
		x += advance(c)
