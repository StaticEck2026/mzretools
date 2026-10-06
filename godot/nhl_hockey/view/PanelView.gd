class_name PanelView
extends Node2D
## The info panel of the stoppages (draw_penalty_box_overlay, 0x665ad): a 123x75 box at (12, 12) of
## the ice view that zooms open in 16 steps (and closed after 600), filled with colour 0x10 and a
## dotted colour 9 (sub_65ca8 plots every second pixel of every second row) inside a 4 pixel black
## frame. It shows up to five centred lines of text (InfoPanel texts) in the two halves of the
## dithered score font (SCOR3B in colour 0x25, SCOR2B in 0x27 at the same position), or the frame
## of the running clip (the PPV of Tables.announcer_ppv_names). SAVED draws its frames 0x12..0x14
## over frame 0x15 at y + 0x3c, GUILT its frames above 0x10 over frame 0x1e at (+0x11, +0x1f); the
## fans' clip shows the crowd level as three dotted bars.

const X0 := 0xc
const Y0 := 0xc
const W := 0x7b
const H := 0x4b

var sim: Sim
var palette: GamePalette
var font_a: Vfn                  # SCOR3B
var font_b: Vfn                  # SCOR2B
var clip_frames: Dictionary = {} # clip id -> Array of textures
var loader: Callable             # name -> Shpi (Main._bank)
var text_cache: Dictionary = {}
var dots_cache: Dictionary = {}
## the panel can be fed from a replay or a test instead of the simulation
var source: Object = null

func setup(s: Sim, pal: GamePalette, fonts: Dictionary, bank_loader: Callable) -> void:
	sim = s
	palette = pal
	font_a = fonts.get("scor3b", null)
	font_b = fonts.get("scor2b", null)
	loader = bank_loader
	z_index = 90

func _process(_delta: float) -> void:
	queue_redraw()

func _frames(id: int) -> Array:
	if clip_frames.has(id):
		return clip_frames[id]
	var out: Array = []
	if loader.is_valid() and palette != null and id >= 0 and id < Tables.announcer_ppv_names.size():
		var bank: Shpi = loader.call(Tables.announcer_ppv_names[id])
		if bank != null:
			for sh in bank.shapes:
				out.append(sh.to_texture(palette.colors) if sh.is_image() else null)
	clip_frames[id] = out
	return out

func _draw() -> void:
	if sim == null or palette == null or sim.panel < 0:
		return
	var p := sim.panel
	var di := 0
	if p < 0x10:
		di = p - 0x10
	elif p > 599:
		di = 600 - p
	if di < -0x10:
		return
	var c := palette.colors
	var hw := (di + 0x10) * 0x42 / 0x10
	var hh := (di + 0x10) * 0x2a / 0x10
	var clipped := di < 0
	var clip_rect := Rect2(X0 + 0x3e - hw, Y0 + 0x26 - hh, hw * 2, hh * 2)
	var clip_id := sim.clip
	var showing_clip := not clipped and clip_id >= 0 and sim.clip_frame >= 0
	if di == 0 or hw > 0x3d:
		draw_rect(Rect2(X0 - 4, Y0 - 4, W + 8, 4), Color.BLACK)
		draw_rect(Rect2(X0 - 4, Y0, 4, H), Color.BLACK)
		draw_rect(Rect2(X0 + W, Y0, 4, H), Color.BLACK)
		draw_rect(Rect2(X0 - 4, Y0 + H, W + 8, 4), Color.BLACK)
	if not showing_clip:
		var r := Rect2(X0, Y0, W, H)
		if clipped:
			r = r.intersection(clip_rect)
		if r.size.x > 0 and r.size.y > 0:
			draw_rect(r, c[0x10])
			_dots(r, c[9])
	if clipped:
		return
	if showing_clip:
		_draw_clip(clip_id, sim.clip_frame)
		return
	_draw_text()

## sub_65ca8: every second pixel of every second row (from the second row)
func _dots(r: Rect2, color: Color) -> void:
	var key := "%d|%d|%s" % [int(r.size.x), int(r.size.y), color.to_html()]
	if not dots_cache.has(key):
		var img := Image.create(maxi(int(r.size.x), 1), maxi(int(r.size.y), 1), false, Image.FORMAT_RGBA8)
		for yy in range(1, int(r.size.y), 2):
			for xx in range(0, int(r.size.x), 2):
				img.set_pixel(xx, yy, color)
		dots_cache[key] = ImageTexture.create_from_image(img)
	draw_texture(dots_cache[key], r.position)

func _draw_clip(id: int, frame: int) -> void:
	var frames := _frames(id)
	if frame < 0 or frame >= frames.size() or frames[frame] == null:
		return
	if id == InfoPanel.CLIP_GUILTY and frame > 0x10 and frames.size() > 0x1e and frames[0x1e] != null:
		draw_texture(frames[0x1e], Vector2(X0, Y0))
		draw_texture(frames[frame], Vector2(X0 + 0x11, Y0 + 0x1f))
	elif id == InfoPanel.CLIP_SAVE and frame > 0x11 and frame < 0x15 and frames.size() > 0x15 and frames[0x15] != null:
		draw_texture(frames[0x15], Vector2(X0, Y0))
		draw_texture(frames[frame], Vector2(X0, Y0 + 0x3c))
	else:
		draw_texture(frames[frame], Vector2(X0, Y0))
	if id == InfoPanel.CLIP_FAN_ANTHEM and frame == 2:
		# the crowd meter of the fans' clip
		var y := Y0 + 0x23
		var h := Y0 + 0x4b - y
		var crowd := sim.crowd_noise
		var bars := [[0x2ee, 0x30, 0, 200], [0x3b6, 0x27, 0x28, 200], [0x47e, 0x60, 0x50, 0xd7]]
		for b: Array in bars:
			if crowd > b[0]:
				var w := mini(crowd - b[0], b[3]) / 5
				_dots(Rect2(X0 + b[2], y, w, h), palette.colors[b[1]])

func _draw_text() -> void:
	var lines: Array = sim.panel_text
	var step := 0x12
	var y := Y0
	if lines[4] != "":
		step = 0xd
		y += 8
	elif lines[3] != "":
		step = 0xf
		y += 0xb
	else:
		y += 0xf
	var cx := X0 + 0x3e
	# the title on the first row, the other lines below it without gaps, the fifth one row
	# under the last
	if lines[0] != "":
		_score_text(lines[0], cx, y)
	for i in [1, 2, 3]:
		if lines[i] != "":
			y += step
			_score_text(lines[i], cx, y)
	if lines[4] != "":
		_score_text(lines[4], cx, y + step)

## the dithered score font: SCOR3B (colour 0x25) and SCOR2B (0x27), centred on cx
func _score_text(s: String, cx: int, y: int) -> void:
	var tex := score_texture(s)
	if tex != null:
		draw_texture(tex, Vector2(cx - tex.get_width() / 2, y))

func score_texture(s: String) -> Texture2D:
	if font_a == null or font_b == null or palette == null:
		return null
	if not text_cache.has(s):
		var w := maxi(font_a.text_width(s), 1)
		var img := Image.create(w, maxi(font_a.height, font_b.height), false, Image.FORMAT_RGBA8)
		font_a.draw(img, s, 0, 0, palette.colors[0x25])
		font_b.draw(img, s, 0, 0, palette.colors[0x27])
		text_cache[s] = ImageTexture.create_from_image(img)
	return text_cache[s]
