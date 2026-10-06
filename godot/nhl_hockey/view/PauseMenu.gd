class_name PauseMenu
extends Node2D
## The pause screen of the match (pause_menu 0x1935d): the EA desk picture (EADESK0.QFS while
## paused, EADESK2.QFS after the game) at 640x480 with the menu bar of unk_ceb8f (after the game
## unk_cec4f) in the S1 font: boxes filled with colour 0xf9, light edge 0xfa, dark edge 0xf8
## (draw_menu_items, draw_box), the open entry highlighted (highlight_menu_item). The entries run
## the handlers of the original: Back to Game (sub_1a5a1), Exit (exit_game_dialog), Go To Replay
## (sub_1a817), the goalie choices (sub_1ab0b..sub_1abf1 -> Lines.choose_goalie). The other
## entries open the front end screens of the original (controls, settings, statistics, line
## editor, box scores) and are shown but not active in this port.

signal chosen(action: String)

const BAR_H := 18

# [title, x0, x1, items]; item = [label, action, x1 (width of the list), sub list]
const PAUSE_MENU := [
	["Action", 0, 46, 118, [["Back to Game", "back"], ["Save Game ...", ""], ["Sports Desk", ""], ["Exit", "exit"]]],
	["Game", 47, 90, 169, [["Player 1 Controls ...", ""], ["Player 2 Controls ...", ""], ["-", ""],
		["Home Team Goalie \u0003", "goalie:0"], ["Visiting Team Goalie \u0003", "goalie:1"], ["-", ""], ["Settings ...", ""]]],
	["Statistics", 91, 160, 140, [["Statistics Type \u0003", ""], ["Standings ...", ""], ["Teams Sorted By \u0003", ""],
		["Players Sorted By \u0003", ""], ["Goalies Sorted By \u0003", ""]]],
	["Line Editor", 161, 237, 110, [["Home Team ...", ""], ["Visiting Team ...", ""]]],
	["Instant Replay", 238, 344, 107, [["Go To Replay ...", "replay"]]],
	["Game Summary", 345, 454, 140, [["Game Statistics ...", ""], ["Penalty Summary ...", ""], ["Scoring Summary ...", ""], ["Team Scratches ...", ""]]],
]
const END_MENU := [
	["Action", 0, 46, 118, [["Sports Desk", ""], ["Exit", "exit"]]],
	["Statistics", 47, 116, 140, [["Statistics Type \u0003", ""], ["Standings ...", ""], ["Teams Sorted By \u0003", ""],
		["Players Sorted By \u0003", ""], ["Goalies Sorted By \u0003", ""]]],
	["Game Summary", 117, 225, 140, [["Game Statistics ...", ""], ["Penalty Summary ...", ""], ["Scoring Summary ...", ""], ["Team Scratches ...", ""]]],
]

var sim: Sim
var font: Vfn
var desk: Array = []             # [texture, palette] per EADESK variant
var menu: Array = PAUSE_MENU
var variant := 0                 # 0 paused, 2 after the game
var open_menu := 0
var item := 0
var goalie_team := -1            # the goalie list of this team is open
var goalie_item := 0
var colors: PackedColorArray
var text_cache: Dictionary = {}

func setup(s: Sim, f: Vfn, bank_loader: Callable) -> void:
	sim = s
	font = f
	visible = false
	z_index = 200
	for n in 3:
		var bank: Shpi = bank_loader.call("eadesk%d" % n) if bank_loader.is_valid() else null
		var entry: Array = [null, PackedColorArray()]
		if bank != null:
			var pal := bank.palette()
			var shape := bank.find("desk")
			if shape != null and shape.is_image() and pal.size() >= 256:
				entry = [shape.to_texture(pal), pal]
		desk.append(entry)

## pause_menu(0) while playing, pause_menu(2) after the game
func open(after_game: bool) -> void:
	variant = 2 if after_game else 0
	menu = END_MENU if after_game else PAUSE_MENU
	open_menu = 0
	item = 0
	goalie_team = -1
	colors = desk[variant][1]
	visible = true
	# the 640x480 screen on the 320x200 view (as a VGA monitor shows both modes)
	scale = Vector2(320.0 / 640.0, 200.0 / 480.0)

func close() -> void:
	visible = false

func _col(i: int, fallback: Color) -> Color:
	return colors[i] if colors.size() > i else fallback

func _text(s: String, color: Color) -> Texture2D:
	if font == null:
		return null
	var key := s + "|" + color.to_html()
	if not text_cache.has(key):
		text_cache[key] = ImageTexture.create_from_image(font.render(s, color))
	return text_cache[key]

func _draw() -> void:
	var tex: Texture2D = desk[variant][0] if desk.size() > variant else null
	if tex != null:
		draw_texture(tex, Vector2.ZERO)
	else:
		draw_rect(Rect2(0, 0, 640, 480), Color(0.1, 0.1, 0.15))
	var light := _col(0xfa, Color(0.9, 0.9, 0.9))
	var face := _col(0xf9, Color(0.5, 0.5, 0.55))
	var dark := _col(0xf8, Color(0.2, 0.2, 0.25))
	# the bar, then the free part of the bar up to the right edge
	for m in menu.size():
		var e: Array = menu[m]
		_box(e[1], 0, e[2], BAR_H, light, face, dark)
		if m == open_menu:
			draw_rect(Rect2(e[1] + 1, 1, e[2] - e[1] - 2, BAR_H - 1), dark)
		_label(e[0], e[1] + 3, 2, light)
	var last: Array = menu[menu.size() - 1]
	_box(last[2] + 1, 0, 0x27f, BAR_H, light, face, dark)
	# the open list
	var cur: Array = menu[open_menu]
	var items: Array = cur[4]
	var x0: int = cur[1]
	var w: int = cur[3]
	for i in items.size():
		var y := BAR_H + 1 + i * 18
		var it: Array = items[i]
		_box(x0, y, x0 + w, y + 17, light, face, dark)
		if it[0] == "-":
			draw_line(Vector2(x0 + 4, y + 9), Vector2(x0 + w - 4, y + 9), dark)
			continue
		var active: bool = it[1] != ""
		if i == item and goalie_team < 0 and active:
			draw_rect(Rect2(x0 + 1, y + 1, w - 2, 16), dark)
		_label(it[0], x0 + 3, y + 2, light if active else dark.lerp(face, 0.5))
	if goalie_team >= 0:
		_draw_goalie_list(x0 + w + 1, BAR_H + 1 + item * 18)

func _box(x0: int, y0: int, x1: int, y1: int, light: Color, face: Color, dark: Color) -> void:
	draw_rect(Rect2(x0, y0, x1 - x0 + 1, y1 - y0 + 1), face)
	draw_line(Vector2(x0, y0), Vector2(x1 - 1, y0), light)
	draw_line(Vector2(x0, y0), Vector2(x0, y1 - 1), light)
	draw_line(Vector2(x1, y0 + 1), Vector2(x1, y1), dark)
	draw_line(Vector2(x0 + 1, y1), Vector2(x1, y1), dark)

func _label(s: String, x: int, y: int, color: Color) -> void:
	var t := _text(s, color)
	if t != null:
		draw_texture(t, Vector2(x, y))

## the goalie choice (unk_cee4f / unk_ceeaf): the two goalies of the line table and NONE, the
## current one marked (glyph 1 selected, 2 not)
func goalie_choices(t: int) -> Array:
	var team := sim.teams[t]
	var out: Array = []
	var lt := Lines.line_table(team)
	for g in 2:
		var r: int = lt[0x24 + g] - 25 if lt.size() > 0x25 else -1
		var name := "NONE"
		if team.info != null and r >= 0 and team.info.goalies.size() > r:
			var p: Database.Player = team.info.goalies[r]
			name = "%02d %s. %s" % [p.number, p.first.left(1), p.last]
		out.append(name)
	out.append("NONE")
	return out

func _goalie_selected(t: int) -> int:
	var w := Entity.to_s16(sim.teams[t].goalie_request)
	if w < 0:
		return 2
	return w & 1

func _draw_goalie_list(x0: int, y0: int) -> void:
	var light := _col(0xfa, Color(0.9, 0.9, 0.9))
	var face := _col(0xf9, Color(0.5, 0.5, 0.55))
	var dark := _col(0xf8, Color(0.2, 0.2, 0.25))
	var names := goalie_choices(goalie_team)
	var sel := _goalie_selected(goalie_team)
	for i in names.size():
		var y := y0 + i * 18
		_box(x0, y, x0 + 190, y + 17, light, face, dark)
		if i == goalie_item:
			draw_rect(Rect2(x0 + 1, y + 1, 188, 16), dark)
		var mark := "\u0001" if i == sel else "\u0002"
		_label(mark + " " + names[i], x0 + 3, y + 2, light)

## keyboard / joystick: left and right walk the bar, up and down the list, A selects, B / Esc go
## back (the pause key closes the screen)
func input(dir: int, select: bool, back: bool) -> void:
	if goalie_team >= 0:
		if dir == 0:
			goalie_item = (goalie_item + 2) % 3
		elif dir == 4:
			goalie_item = (goalie_item + 1) % 3
		elif select:
			Lines.choose_goalie(sim, goalie_team, goalie_item if goalie_item < 2 else -1)
			goalie_team = -1
		elif back or dir == 6:
			goalie_team = -1
		queue_redraw()
		return
	var items: Array = menu[open_menu][4]
	if dir == 2:
		open_menu = (open_menu + 1) % menu.size()
		item = 0
	elif dir == 6:
		open_menu = (open_menu + menu.size() - 1) % menu.size()
		item = 0
	elif dir == 4:
		item = (item + 1) % items.size()
	elif dir == 0:
		item = (item + items.size() - 1) % items.size()
	elif select:
		_activate(items[item][1])
	elif back:
		chosen.emit("back" if variant == 0 else "")
	queue_redraw()

func _activate(action: String) -> void:
	if action == "":
		return
	if action.begins_with("goalie:"):
		goalie_team = int(action.substr(7))
		if not sim.is_user_team(goalie_team):
			goalie_team = -1
			return
		goalie_item = _goalie_selected(goalie_team)
		return
	chosen.emit(action)

## mouse: a click on a bar entry opens its list, on a list entry runs it
func click(pos: Vector2) -> void:
	var p := Vector2(pos.x / scale.x, pos.y / scale.y)
	for m in menu.size():
		var e: Array = menu[m]
		if p.y <= BAR_H and p.x >= e[1] and p.x <= e[2]:
			open_menu = m
			item = 0
			goalie_team = -1
			queue_redraw()
			return
	var cur: Array = menu[open_menu]
	var items: Array = cur[4]
	if p.x >= cur[1] and p.x <= cur[1] + cur[3]:
		var i := int((p.y - BAR_H - 1) / 18)
		if i >= 0 and i < items.size():
			item = i
			_activate(items[i][1])
			queue_redraw()
