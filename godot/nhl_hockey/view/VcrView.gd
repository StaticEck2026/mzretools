class_name VcrView
extends Node2D
## The control panel of the instant replay (instant_replay 0x7e0fa, replay_control_loop 0x7e9ac):
## 'gad1' of GADGET5.PPV (GADGET6.PPV without the highlight menu) in place of the scoreboard, the
## buttons of the running mode framed (replay_draw_button: top and left edge colour 0x10, bottom and right
## 0x15) and the keyboard selection outlined.

const Y := 168

var replay: Replay
var palette: GamePalette
var panel_tex: Texture2D
var pal_colors: PackedColorArray
var selected := Replay.B_PLAY
var menu_enabled := false

func setup(r: Replay, bank: Shpi, pal: GamePalette) -> void:
	replay = r
	palette = pal
	z_index = 110
	visible = false
	if bank == null:
		return
	# the panel shares the VGA palette of the match (the bank's own '!pal' is not loaded)
	var colors := pal.colors if pal != null else PackedColorArray()
	pal_colors = colors
	var g := bank.find("gad1")
	if g != null and g.is_image() and colors.size() >= 256:
		panel_tex = g.to_texture(colors)

func _process(_delta: float) -> void:
	if visible:
		queue_redraw()

## the buttons lit for the mode (dword_ed754 bits)
func _lit(i: int) -> bool:
	return (replay.mode & (1 << i)) != 0

func _draw() -> void:
	draw_rect(Rect2(0, Y, 320, 32), Color.BLACK)
	if panel_tex != null:
		draw_texture(panel_tex, Vector2(0, Y))
	var light := pal_colors[0x10] if pal_colors.size() > 0x15 else Color.WHITE
	var dark := pal_colors[0x15] if pal_colors.size() > 0x15 else Color.DIM_GRAY
	for i in Replay.BUTTONS.size():
		var b: Array = Replay.BUTTONS[i]
		if _lit(i):
			draw_line(Vector2(b[0], b[1]), Vector2(b[2], b[1]), light)
			draw_line(Vector2(b[0], b[1]), Vector2(b[0], b[3]), light)
			draw_line(Vector2(b[2], b[1]), Vector2(b[2], b[3]), dark)
			draw_line(Vector2(b[0], b[3]), Vector2(b[2], b[3]), dark)
	var s: Array = Replay.BUTTONS[selected]
	draw_rect(Rect2(s[0] - 1, s[1] - 1, s[2] - s[0] + 3, s[3] - s[1] + 3), Color(1, 1, 0.4, 0.9), false)

## replay_button_at: the button under a screen position
static func button_at(x: int, y: int) -> int:
	for i in Replay.BUTTONS.size():
		var b: Array = Replay.BUTTONS[i]
		if x + 5 >= b[0] and x + 5 <= b[2] and y >= b[1] and y <= b[3]:
			return i
	return -1
