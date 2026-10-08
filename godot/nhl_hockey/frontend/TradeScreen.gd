class_name TradeScreen
extends RefCounted
## The trade screen of a league (line_editor 0x3ff52, team_roster_screen 0x3e9d2, line_editor_screen
## 0x3ef89): the two teams' rosters left and right (line_editor_load_roster, sorted by
## cmp_player_names; "%c %2d %s" in S1, colour 0x40 on 0x41, the chosen one 0x42) and between them
## four shirts, two for each team: a player chosen in a list and then a shirt of his team goes into
## the trade (each player once); a shirt clicked with nothing chosen gives its player back. A goalie
## goes only for a goalie: when exactly one of a pair of shirts (the first team's and the second's at
## the same height) holds a goalie the other is emptied. The menu: Trade (Done: both shirts of a
## pair filled or both empty, else "There must be an equal number of players selected on both
## teams!"; Cancel) and Player Statistics (each team's). Returns the four shirts' roster slots (0xff
## empty), null for Cancel or when a roster cannot be read.
##
## The shirts of LINEDITP.QFS are on the CD only: frames with the jersey numbers stand in, as in the
## line editor; the shirt carried by the pointer over the middle is not drawn.

var fe: FrontEnd
var scr: Screen8
var ui: Ui

const PLACES := 0xc8b7c           # unk_c8b7c: the shirts' x, y
const SHIRT_W := 0x3a
const SHIRT_H := 0x28

var ids := [0, 0]
var lists := [[], []]             # unk_ddd8c / unk_ddff4: the entries, sorted
var chosen := [-1, -1]            # dword_ddd84: the row chosen in each list
var target := [-1, -1]            # dword_ddd74: the row (100 + row) or the shirt clicked
var current := -1                 # dword_de260: the team of the player in hand, -1 none
var shirts := PackedByteArray([0xff, 0xff, 0xff, 0xff])   # the shirts' roster slots
var shirt_entries := []           # the entries copied into the shirts (number 0xff: empty)
var result: Variant = null

func _init(f: FrontEnd) -> void:
	fe = f
	scr = f.scr
	ui = f.ui

static func _place(k: int) -> Vector2i:
	return Vector2i(Exe.i32(PLACES + k * 8), Exe.i32(PLACES + k * 8 + 4))

## line_editor: the rosters, the screen, the menu loop
func run(teams: PackedByteArray, key_db: PackedByteArray, a: int, b: int) -> Variant:
	ids = [a, b]
	await scr.fade_out(16)
	for s in 2:
		var r = Trade.roster(teams, key_db, ids[s])
		if r == null:
			return null
		Clib.qsort(r, NameSort.cmp_player_names_b, 0x16)
		lists[s] = r
	chosen = [-1, -1]
	target = [-1, -1]
	current = -1
	shirts = PackedByteArray([0xff, 0xff, 0xff, 0xff])
	shirt_entries = []
	for k in 4:
		shirt_entries.append(["", 0xff, 0, "", ""])
	var keep_font := scr.font
	scr.setfont(fe.font_main)
	# the Player Statistics menu: "Show <city> Statistics..." for each team, both as wide as the wider
	var names := []
	for s in 2:
		names.append("Show " + Exe.str_ptr(LeagueScreens.TEAM_NAMES + ids[s] * 4) + " Statistics...")
	var w := maxi(scr.textwidth(names[0]), scr.textwidth(names[1])) + 6
	for s in 2:
		# unk_c87b8 / unk_c87d8 (their text and width set by statistics_menu)
		var it := Menus.ensure(0xc87b8 + s * 0x20, 0, s * 0x12, 0xba, 0x11 + s * 0x13, "roster_stats_screen")
		it.text = names[s]
		it.x1 = w
		it.cb = "trade_stats_%d" % s
	var root := Menus.list(0xc885c, 3)
	_draw(root)
	result = null
	var pb := fe.bank("embpal")
	await scr.fade_in(Screen8.shape_palette(pb.find("!pal")) if pb != null else FrontEnd._grey_palette(), 16)
	var handler := func(cb: String):
		return await _callback(cb)
	await ui.run_menu(root, 0x40, 0x41, 0x42, handler, Callable(), [1], Callable(), _click)
	scr.setfont(keep_font)
	return result

## team_roster_screen: EMBNHL, the menu, the two bevelled panels, the shirts, the rosters
func _draw(root: Array) -> void:
	scr.clearclip()
	scr.clear(0)
	var bg := fe.bank("embnhl")
	if bg != null:
		scr.drawshape_remap(bg.find("bkgd"), 0, 0)
	ui.draw_menu_items(root, 0x40, 0x41, 0x42)
	fe.set_dialog_colors(0x41, 0x40, 0x42, 0x40, 0x41)
	fe.draw_bevel_box(0x1c0, 0, 0x27f, 0x1df, true)
	fe.draw_bevel_box(0, 0, 0xbe, 0x1df, true)
	_draw_shirts()
	for s in 2:
		for i in 28:
			if lists[s][i][0] == "":
				break
			_draw_entry(s, i, i == chosen[s])

## line_editor_draw_entry: a row of a roster ("%c %2d %s")
func _draw_entry(s: int, i: int, on: bool) -> void:
	if i < 0:
		return
	var e: Array = lists[s][i]
	scr.settextcolor(0x42 if on else 0x40, 0x41)
	var pos: String = e[0] if e[0] != "" else " "
	scr.printstr_at("%s %2d %s" % [pos, e[1], e[3]], 5 + s * 0x1c0, 0x1d + scr.font_height() * i)

## the four shirts with the numbers of their players
func _draw_shirts() -> void:
	for k in 4:
		var p := _place(k)
		scr.fillrect(p.x, p.y, SHIRT_W - 4, SHIRT_H - 4, 0x41)
		scr.drawline(p.x, p.y, p.x + SHIRT_W - 5, p.y, 0x40)
		scr.drawline(p.x, p.y, p.x, p.y + SHIRT_H - 5, 0x40)
		scr.drawline(p.x + SHIRT_W - 5, p.y, p.x + SHIRT_W - 5, p.y + SHIRT_H - 5, 0x42)
		scr.drawline(p.x, p.y + SHIRT_H - 5, p.x + SHIRT_W - 5, p.y + SHIRT_H - 5, 0x42)
		var n: int = shirt_entries[k][1]
		if n == 0xff:
			continue
		scr.settextcolor(0x40, 0xff)
		var t := str(n)
		scr.printstr_at(t, p.x + (SHIRT_W - 4 - scr.textwidth(t)) / 2, p.y + (SHIRT_H - 4 - scr.font_height()) / 2)

## line_editor_hit_test: a shirt (target: 0..3; with nothing in hand the shirt's team, `from_shirt`)
## or a row of a list (target: 100 + row); [hit, from_shirt]
func _hit(x: int, y: int) -> Array:
	var xx := x + 4
	if xx > 0xbe and xx < 0x1c0:
		var hit := false
		var flag := false
		for k in 4:
			var p := _place(k)
			if xx >= p.x and xx < p.x + SHIRT_W and y >= p.y and y < p.y + SHIRT_H:
				if current >= 0:
					target[current] = k
				else:
					current = k / 2
					target[current] = k
					flag = true
				hit = true
		return [hit, flag]
	var h := scr.font_height()
	if y >= 0x1d and y < 0x1d + h * 28:
		current = 1 if xx >= 0xbe else 0
		target[current] = (y - 0x1d) / h + 100
		return [true, false]
	return [false, false]

## line_editor_find_number: the row of a roster slot, -1 none
func _row_of(s: int, slot: int) -> int:
	for i in 28:
		if lists[s][i][2] == slot:
			return i
	return -1

## a click outside the menus (line_editor_screen)
func _click(e: Dictionary):
	var hit := _hit(e["x"], e["y"])
	if not hit[0]:
		return 0
	var t := current
	if target[t] >= 100:
		var row: int = target[t] - 100
		target[t] = row
		if lists[t][row][0] == "":
			return 0
		if chosen[t] == row:
			_draw_entry(t, row, false)
			chosen[t] = -1
			current = -1
			return 0
		if chosen[t] != -1:
			_draw_entry(t, chosen[t], false)
		chosen[t] = row
		_draw_entry(t, row, true)
		return 0
	if chosen[t] == -1 and not hit[1]:
		return 0
	var k: int = target[t]
	if hit[1]:
		# a shirt with nothing in hand: its player back into the list, chosen
		var n := shirts[k]
		if n == 0xff:
			current = -1
			return 0
		if chosen[t] != -1 and n != chosen[t]:
			_draw_entry(t, chosen[t], false)
		chosen[t] = _row_of(t, n)
		_draw_entry(t, chosen[t], true)
		shirts[k] = 0xff
		shirt_entries[k][1] = 0xff
		_draw_shirts()
		return 0
	var en: Array = lists[t][chosen[t]]
	var mine := 0 if k < 2 else 1
	if current != mine:
		return 0
	var first := mine * 2
	if shirts[first] == en[2] or shirts[first + 1] == en[2]:
		return 0
	shirts[k] = en[2]
	shirt_entries[k] = en.duplicate()
	# a goalie only for a goalie: the other team's shirt at the same height
	var p := k + 2 if k < 2 else k - 2
	if (shirt_entries[k][0] == "G") != (shirt_entries[p][0] == "G"):
		shirts[p] = 0xff
		shirt_entries[p][1] = 0xff
	_draw_entry(t, chosen[t], false)
	chosen[t] = -1
	current = -1
	_draw_shirts()
	return 0

func _callback(cb: String):
	match cb:
		"line_editor_done":
			# line_editor_done: both shirts of a pair filled or both empty
			for k in 2:
				if (shirts[k] == 0xff) != (shirts[k + 2] == 0xff):
					await fe.message_dialog(["There must be an equal", "number of players selected", "on both teams!"])
					return 0
			result = shirts
			return 1
		"line_editor_cancel":
			result = null
			return 1
		"trade_stats_0", "trade_stats_1":
			await _roster_stats(ids[int(cb.right(1))])
			return 0
	return await fe.dispatch(cb)

## roster_stats_screen (0x3de05): the team's statistics (player_stats_screen) with the menu Return To
## (Trade) / Statistics Type (the source of the statistics, the screen drawn again), then the trade
## screen again
func _roster_stats(team: int) -> void:
	await scr.fade_out(16)
	scr.clearclip()
	var st := fe.stats
	st.hub_active = true
	st.current = st.player_stats_screen
	st.current_arg = team
	st.update_source_marks()
	await st.player_stats_screen(team)
	var menu := Menus.list(0xc88e2, 2)
	ui.draw_menu_items(menu, 0x40, 0x41, 0x42)
	await scr.fade_in(st.stats_palette(), 16)
	await ui.run_menu(menu, 0x40, 0x41, 0x42, fe.dispatch)
	st.hub_active = false
	st.current = Callable()
	await scr.fade_out(16)
	scr.setfont(fe.font_main)
	_draw(Menus.list(0xc885c, 3))
	var pb := fe.bank("embpal")
	await scr.fade_in(Screen8.shape_palette(pb.find("!pal")) if pb != null else FrontEnd._grey_palette(), 16)
