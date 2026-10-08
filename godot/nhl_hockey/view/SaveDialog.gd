class_name SaveDialog
extends Node2D
## The VCR's "Save To Hilights Reel" dialog (replay_save_dialog 0x7f724, drawn by replay_menu
## 0x7f0af) on the 320x200 game surface when both teams are played by people: a band of colour
## 0x14 from y 0x4b, two outlines (colours 9 and 0x10), four rows (0x4e..0xd8, 0x11 apart from
## y 0x50: light edges 0x59, dark 0x10, corner dots 0x13) for the home team, the away team (their
## names, TEAMS.DB +5), "Both Teams" and "Neither Teams", in the HILIGHT font with a shadow (0x10)
## under the text (0x59). The row clicked is drawn pressed (edges swapped). The port adds a
## keyboard selection (up / down, outlined) as the VCR has one.

signal chosen(row: int)

const ROW_X0 := 0x4e
const ROW_X1 := 0xd8

var font: Vfn
var colors: PackedColorArray
var labels := ["", "", "Both Teams", "Neither Teams"]
var pressed := -1
var selected := 0
var text_cache := {}

func open(home_name: String, away_name: String) -> void:
	labels[0] = home_name
	labels[1] = away_name
	pressed = -1
	selected = 0
	visible = true
	queue_redraw()

static func row_y(k: int) -> int:
	return 0x50 + k * 0x11

## replay_menu's test of a click: the row whose box (0x4e..0xd8, 0x50..0x5e, 0x61..0x6f, ...)
## holds the pointer, -1 none
static func row_at(x: int, y: int) -> int:
	if x < ROW_X0 or x > ROW_X1:
		return -1
	for k in 4:
		if y >= row_y(k) and y <= row_y(k) + 0xe:
			return k
	return -1

func press(k: int) -> void:
	pressed = k
	queue_redraw()

func _c(i: int) -> Color:
	return colors[i] if i < colors.size() else Color.WHITE

func _line(x0: int, y0: int, x1: int, y1: int, c: int) -> void:
	draw_rect(Rect2(mini(x0, x1), mini(y0, y1), absi(x1 - x0) + 1, absi(y1 - y0) + 1), _c(c))

## fillbox_corners: a one pixel outline
func _outline(x0: int, y0: int, x1: int, y1: int, c: int) -> void:
	_line(x0, y0, x1, y0, c)
	_line(x0, y0 + 1, x0, y1 - 1, c)
	_line(x1, y0 + 1, x1, y1 - 1, c)
	_line(x0, y1, x1, y1, c)

func _text(s: String, x: int, y: int, c: int) -> void:
	if font == null or s == "":
		return
	var key := "%s|%d" % [s, c]
	if not text_cache.has(key):
		text_cache[key] = ImageTexture.create_from_image(font.render(s, _c(c)))
	draw_texture(text_cache[key], Vector2(x, y))

func _width(s: String) -> int:
	return font.text_width(s) if font != null else s.length() * 6

func _draw() -> void:
	draw_rect(Rect2(0, 0x4b, 0x140, 0x4c), _c(0x14))
	_outline(1, 0x4c, 0x13e, 0x95, 9)
	_outline(2, 0x4d, 0x13d, 0x96, 0x10)
	for k in 4:
		var y := row_y(k)
		var light := 0x10 if k == pressed else 0x59
		var dark := 0x59 if k == pressed else 0x10
		_line(ROW_X0, y, ROW_X0, y + 0xe, light)
		_line(ROW_X0, y, ROW_X1, y, light)
		_line(ROW_X0 + 1, y + 0xe, ROW_X1, y + 0xe, dark)
		_line(ROW_X1, y + 1, ROW_X1, y + 0xe, dark)
		_line(ROW_X1, y, ROW_X1, y, 0x13)
		_line(ROW_X0, y + 0xe, ROW_X0, y + 0xe, 0x13)
	for pass_ in 2:
		var c := 0x10 if pass_ == 0 else 0x59
		var o := 0 if pass_ == 0 else -1
		_text("Save To", 0xe + o, 0x6d + o, c)
		_text("Hilights Reel", 0xdf + o, 0x6d + o, c)
		for k in 4:
			_text(labels[k], (0x85 - _width(labels[k])) / 2 + 0x52 + o, 0x54 + k * 0x11 + o, c)
	if pressed < 0:
		var y := row_y(selected)
		draw_rect(Rect2(ROW_X0 - 1, y - 1, ROW_X1 - ROW_X0 + 3, 0x11), Color(1, 1, 0.4, 0.9), false)
