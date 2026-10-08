class_name Screen8
extends Node2D
## The 256 colour frame buffer of the EA library (initgraphics(0x280, 0x1e0)) the front end screens
## draw into: fillrect, drawline, putpixel, drawshape (opaque), drawshape_remap (0xff transparent),
## grabshape, printstr with the current font and text colours, setpalette / getpalette and the
## palette fades (fade_palette). The screens keep the original coordinates and colour indices; the
## indices are shown through the palette by a shader (shaders/indexed.gdshader), so a palette
## change or a fade costs nothing.

const W := 640
const H := 480

var img: Image                       # FORMAT_R8: one colour index per pixel
var dac := PackedByteArray()         # 768 bytes, the 6 bit DAC values on screen
var clip := Rect2i(0, 0, W, H)
var font: Vfn
var text_fg := 0xfa                  # settextcolor (dword_d42a8)
var text_bg := 0xff                  # text_bg_colour: 0xff = the glyph cells stay transparent
var text_color := 0xfa               # set_text_colors: dword_c6418 (text)
var text_shadow := 0                 # text_shadow (shadow / outline)
var capture: Array = []              # text_capture_add: [x, y, text] while capturing (Output Current Data)
var capturing := false

var view: Sprite2D
var _tex: ImageTexture
var _pal_img: Image
var _pal_tex: ImageTexture
var _material: ShaderMaterial
var _dirty := true
var _pal_dirty := true
var _shape_cache: Dictionary = {}    # Shpi.Shape -> [Image R8, Image LA8 mask or null]

func _init() -> void:
	img = Image.create(W, H, false, Image.FORMAT_R8)
	dac.resize(768)
	_pal_img = Image.create(256, 1, false, Image.FORMAT_RGB8)

func _ready() -> void:
	_material = ShaderMaterial.new()
	_material.shader = load("res://shaders/indexed.gdshader")
	_tex = ImageTexture.create_from_image(img)
	_pal_tex = ImageTexture.create_from_image(_pal_img)
	_material.set_shader_parameter("palette", _pal_tex)
	view = Sprite2D.new()
	view.centered = false
	view.texture = _tex
	view.material = _material
	view.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	add_child(view)

func _process(_delta: float) -> void:
	flush()

## uploads the changed picture / palette (also called by the screens before awaiting a frame)
func flush() -> void:
	if _dirty and _tex != null:
		_tex.update(img)
		_dirty = false
	if _pal_dirty and _pal_tex != null:
		for i in 256:
			_pal_img.set_pixel(i, 0, Color8(dac[i * 3] * 255 / 63, dac[i * 3 + 1] * 255 / 63, dac[i * 3 + 2] * 255 / 63))
		_pal_tex.update(_pal_img)
		_pal_dirty = false

## a material showing an indexed texture through this screen's palette (the mouse pointer)
func make_material(transparent: int) -> ShaderMaterial:
	var m := ShaderMaterial.new()
	m.shader = _material.shader if _material != null else load("res://shaders/indexed.gdshader")
	m.set_shader_parameter("palette", _pal_tex)
	m.set_shader_parameter("transparent", transparent)
	return m

static func _c(index: int) -> Color:
	return Color8(index & 0xff, 0, 0)

# ---------------------------------------------------------------------------------------------
# drawing
# ---------------------------------------------------------------------------------------------

## setclip / clearclip
func setclip(x0: int, y0: int, x1: int, y1: int) -> void:
	clip = Rect2i(x0, y0, x1 - x0, y1 - y0).intersection(Rect2i(0, 0, W, H))

func clearclip() -> void:
	clip = Rect2i(0, 0, W, H)

func clear(index: int = 0) -> void:
	img.fill(_c(index))
	_dirty = true

## fillrect(x, y, w, h, colour)
func fillrect(x: int, y: int, w: int, h: int, index: int) -> void:
	var r := Rect2i(x, y, w, h).intersection(clip)
	if r.size.x <= 0 or r.size.y <= 0:
		return
	img.fill_rect(r, _c(index))
	_dirty = true

## fillrect2 (0x90f38): the rectangle XORed with the colour (fillrect2_clipped: inside the clip)
func xorrect(x: int, y: int, w: int, h: int, index: int) -> void:
	var r := Rect2i(x, y, w, h).intersection(clip)
	for yy in range(r.position.y, r.end.y):
		for xx in range(r.position.x, r.end.x):
			img.set_pixel(xx, yy, _c(img.get_pixel(xx, yy).r8 ^ (index & 0xff)))
	_dirty = true

func putpixel(x: int, y: int, index: int) -> void:
	if clip.has_point(Vector2i(x, y)):
		img.set_pixel(x, y, _c(index))
		_dirty = true

func getpixel(x: int, y: int) -> int:
	if x < 0 or y < 0 or x >= W or y >= H:
		return 0
	return img.get_pixel(x, y).r8

## drawline(x0, y0, x1, y1, colour): the library draws horizontal and vertical lines with fills
func drawline(x0: int, y0: int, x1: int, y1: int, index: int) -> void:
	if y0 == y1:
		fillrect(mini(x0, x1), y0, absi(x1 - x0) + 1, 1, index)
		return
	if x0 == x1:
		fillrect(x0, mini(y0, y1), 1, absi(y1 - y0) + 1, index)
		return
	var dx := absi(x1 - x0)
	var dy := -absi(y1 - y0)
	var sx := 1 if x0 < x1 else -1
	var sy := 1 if y0 < y1 else -1
	var err := dx + dy
	while true:
		putpixel(x0, y0, index)
		if x0 == x1 and y0 == y1:
			break
		var e2 := 2 * err
		if e2 >= dy:
			err += dy
			x0 += sx
		if e2 <= dx:
			err += dx
			y0 += sy

## draw_box (0x6b7fc): a filled box, light top and left edges, dark bottom and right edges
func draw_box(x0: int, y0: int, x1: int, y1: int, light: int, face: int, dark: int) -> void:
	fillrect(x0, y0, x1 - x0 + 1, y1 - y0 + 1, face)
	drawline(x0, y0, x1 - 1, y0, light)
	drawline(x0, y0, x0, y1 - 1, light)
	drawline(x1, y0 + 1, x1, y1, dark)
	drawline(x0 + 1, y1, x1, y1, dark)

func _shape_images(s: Shpi.Shape) -> Array:
	if _shape_cache.has(s):
		return _shape_cache[s]
	var pix := s.pixels
	if pix.size() < s.width * s.height:
		pix = pix.duplicate()
		pix.resize(s.width * s.height)
	var r8 := Image.create_from_data(s.width, s.height, false, Image.FORMAT_R8, pix.slice(0, s.width * s.height))
	var mask: Image = null
	if pix.has(0xff):
		var la := PackedByteArray()
		la.resize(s.width * s.height * 2)
		for i in s.width * s.height:
			la[i * 2] = pix[i]
			la[i * 2 + 1] = 0 if pix[i] == 0xff else 255
		mask = Image.create_from_data(s.width, s.height, false, Image.FORMAT_LA8, la)
	var out := [r8, mask]
	_shape_cache[s] = out
	return out

func _blit(src: Image, mask: Image, x: int, y: int) -> void:
	var dst := Rect2i(x, y, src.get_width(), src.get_height()).intersection(clip)
	if dst.size.x <= 0 or dst.size.y <= 0:
		return
	var sr := Rect2i(dst.position - Vector2i(x, y), dst.size)
	if mask != null:
		img.blit_rect_mask(src, mask, sr, dst.position)
	else:
		img.blit_rect(src, sr, dst.position)
	_dirty = true

## drawshape(shape, x, y): the shape's pixels copied to (x, y), clipped
func drawshape(s: Shpi.Shape, x: int, y: int) -> void:
	if s == null or not s.is_image():
		return
	_blit(_shape_images(s)[0], null, x, y)

## drawshape_home: at the position stored in the shape
func drawshape_home(s: Shpi.Shape) -> void:
	if s != null:
		drawshape(s, s.x, s.y)

## drawshape_remap (copy_skip_ff): colour 0xff stays transparent
func drawshape_remap(s: Shpi.Shape, x: int, y: int) -> void:
	if s == null or not s.is_image():
		return
	var im := _shape_images(s)
	_blit(im[0], im[1], x, y)

## a shape drawn through a colour remap table (setremaptable + drawshape_remap)
func drawshape_mapped(s: Shpi.Shape, x: int, y: int, remap: PackedByteArray) -> void:
	if s == null or not s.is_image():
		return
	var pix := s.pixels.slice(0, s.width * s.height)
	for i in pix.size():
		if pix[i] != 0xff:
			pix[i] = remap[pix[i]]
	var r8 := Image.create_from_data(s.width, s.height, false, Image.FORMAT_R8, pix)
	_blit(r8, _shape_images(s)[1], x, y)

## the nearest colour of `dst` (indices first .. first + count - 1) for every colour of `src`
static func palette_map(src: PackedByteArray, dst: PackedByteArray, first: int = 0, count: int = 256) -> PackedByteArray:
	var out := PackedByteArray()
	out.resize(256)
	for i in 256:
		var best := first
		var bd := 1 << 30
		for j in range(first, first + count):
			var d := 0
			for c in 3:
				var e: int = src[i * 3 + c] - dst[j * 3 + c]
				d += e * e
			if d < bd:
				bd = d
				best = j
		out[i] = best
	return out

## a shape of another screen's palette drawn through a palette_map, every `div`-th pixel (the
## small logos of the CD are missing: the large ones of the installation stand in)
func drawshape_scaled(s: Shpi.Shape, x: int, y: int, remap: PackedByteArray, div: int = 2) -> void:
	if s == null or not s.is_image():
		return
	var w := s.width / div
	var h := s.height / div
	if w <= 0 or h <= 0:
		return
	var pix := PackedByteArray()
	pix.resize(w * h)
	var la := PackedByteArray()
	la.resize(w * h * 2)
	for yy in h:
		for xx in w:
			var v: int = s.pixels[(yy * div) * s.width + xx * div]
			var k := yy * w + xx
			pix[k] = remap[v] if v != 0xff else 0
			la[k * 2] = pix[k]
			la[k * 2 + 1] = 0 if v == 0xff else 255
	_blit(Image.create_from_data(w, h, false, Image.FORMAT_R8, pix), Image.create_from_data(w, h, false, Image.FORMAT_LA8, la), x, y)

## grabshape: a copy of the screen rectangle (restored with put())
func grab(x: int, y: int, w: int, h: int) -> Image:
	var r := Rect2i(x, y, w, h).intersection(Rect2i(0, 0, W, H))
	if r.size.x <= 0 or r.size.y <= 0:
		return null
	var g := img.get_region(r)
	g.set_meta("pos", r.position)
	return g

## drawshape of a grabbed rectangle: back where it was taken
func put(g: Image) -> void:
	if g == null:
		return
	var p: Vector2i = g.get_meta("pos", Vector2i.ZERO)
	img.blit_rect(g, Rect2i(Vector2i.ZERO, g.get_size()), p)
	_dirty = true

## the whole screen (the picture behind a dialog)
func snapshot() -> Image:
	return img.duplicate()

func restore(i: Image) -> void:
	if i != null:
		img.blit_rect(i, Rect2i(0, 0, W, H), Vector2i.ZERO)
		_dirty = true

# ---------------------------------------------------------------------------------------------
# text
# ---------------------------------------------------------------------------------------------

func setfont(f: Vfn) -> void:
	if f != null:
		font = f

## settextpos (0x... settextcolor): glyph colour and cell colour (0xff transparent)
func settextcolor(fg: int, bg: int = 0xff) -> void:
	text_fg = fg
	text_bg = bg

## set_text_colors (0x174c2): the colour of print_text_at / print_outlined and its shadow
func set_text_colors(color: int, shadow: int) -> void:
	text_color = color
	text_shadow = shadow

func textwidth(s: String) -> int:
	return font.text_width(s) if font != null else s.length() * 8

func font_height() -> int:
	return font.height if font != null else 8

## printstr at (x, y) in text_fg
func printstr_at(s: String, x: int, y: int) -> void:
	if font == null:
		return
	var f := font
	var data := f.data
	for ci in s.length():
		var c := s.unicode_at(ci)
		if c < f.first or c > f.last:
			x += f.def_width
			continue
		var i := c - f.first
		var w := f.glyph_width(c)
		var h := f.glyph_height(c)
		if text_bg != 0xff:
			fillrect(x, y, f.advance(c), f.height, text_bg)
		var off := f.glyph_base + data.decode_u32(0x20 + i * 4)
		var stride := (w + 7) >> 3
		var gx := x + (data[f.xoff_tab + i] if f.xoff_tab != 0 else 0)
		var gy := y + (data[f.yoff_tab + i] if f.yoff_tab != 0 else 0)
		var col := _c(text_fg)
		for yy in h:
			var py := gy + yy
			if py < clip.position.y or py >= clip.end.y:
				continue
			for xx in w:
				var b := off + yy * stride + (xx >> 3)
				if b < data.size() and (data[b] >> (7 - (xx & 7))) & 1:
					var pxx := gx + xx
					if pxx >= clip.position.x and pxx < clip.end.x:
						img.set_pixel(pxx, py, col)
		x += f.advance(c)
	_dirty = true

## print_text_at (0x175e2): the text with its shadow one pixel down and right
func print_text_at(x: int, y: int, s: String) -> void:
	var fg := text_fg
	text_fg = text_shadow
	printstr_at(s, x + 1, y + 1)
	text_fg = text_color
	printstr_at(s, x, y)
	text_fg = fg
	_capture(x, y, s)

## print_outlined (0x17636): the outline colour around the text (left, right, up, down)
func print_outlined(x: int, y: int, s: String) -> void:
	var fg := text_fg
	text_fg = text_shadow
	for o in [Vector2i(-1, 0), Vector2i(1, 0), Vector2i(0, -1), Vector2i(0, 1)]:
		printstr_at(s, x + o.x, y + o.y)
	text_fg = text_color
	printstr_at(s, x, y)
	text_fg = fg
	_capture(x, y, s)

## print_centered_shadow (0x17573): centred on the 640 pixel screen, with the shadow
func print_centered_shadow(y: int, s: String) -> void:
	print_text_at((W - textwidth(s)) / 2, y, s)

func _capture(x: int, y: int, s: String) -> void:
	if capturing:
		capture.append([x, y, s])

## text_capture_begin / text_capture_stop: collects the text drawn for "Output Current Data"
func capture_begin() -> void:
	capture.clear()
	capturing = true

func capture_stop() -> void:
	capturing = false

## the captured text as lines (sorted by row, then column)
func capture_text() -> String:
	var rows: Dictionary = {}
	for c in capture:
		var y: int = c[1] / 4
		if not rows.has(y):
			rows[y] = []
		rows[y].append(c)
	var keys := rows.keys()
	keys.sort()
	var out := PackedStringArray()
	for k in keys:
		var cells: Array = rows[k]
		cells.sort_custom(func(a, b): return a[0] < b[0])
		var line := ""
		for c in cells:
			var col: int = c[0] / 8
			while line.length() < col:
				line += " "
			if line != "" and not line.ends_with(" "):
				line += " "
			line += c[2]
		out.append(line)
	return "\n".join(out)

# ---------------------------------------------------------------------------------------------
# palette
# ---------------------------------------------------------------------------------------------

## setpalette(first, count, values): 6 bit RGB triples
func setpalette(pal: PackedByteArray, first: int = 0, count: int = 256) -> void:
	for i in count * 3:
		if first * 3 + i < 768 and i < pal.size():
			dac[first * 3 + i] = mini(pal[i], 63)
	_pal_dirty = true

func getpalette() -> PackedByteArray:
	return dac.duplicate()

## the 0x300 byte palette of a "!pal" / "pal " shape (6 bit values; 8 bit ones are shifted down)
static func shape_palette(s: Shpi.Shape) -> PackedByteArray:
	var out := PackedByteArray()
	out.resize(768)
	if s == null:
		return out
	var raw := s.raw if s.raw.size() >= 768 else s.pixels
	if raw.size() < 768:
		return out
	var maxv := 0
	for i in 768:
		maxv = maxi(maxv, raw[i])
	for i in 768:
		out[i] = raw[i] >> 2 if maxv > 63 else raw[i]
	return out

## fade_palette(1, pal, steps): from the palette on screen to black; fade_palette(0, pal, steps):
## from black up to pal. A step per frame of the 70 Hz VGA (fade_palette_steps)
func fade_out(steps: int = 16) -> void:
	var start := dac.duplicate()
	for k in range(steps - 1, -1, -1):
		for i in 768:
			dac[i] = start[i] * k / steps
		_pal_dirty = true
		await get_tree().process_frame
	_pal_dirty = true

func fade_in(pal: PackedByteArray, steps: int = 16) -> void:
	for k in range(1, steps + 1):
		for i in 768:
			dac[i] = (pal[i] if i < pal.size() else 0) * k / steps
		_pal_dirty = true
		await get_tree().process_frame

func black() -> void:
	dac.fill(0)
	_pal_dirty = true
