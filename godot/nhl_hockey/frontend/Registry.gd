class_name Registry
extends RefCounted
## The Central Registry (menu_central_registry 0x6be95 -> database_screen 0x6cc20, database_menu
## 0x6e089): the game's current databases (KEY, CAREER, ATT, CARTEAMS, TEAMS, SEASON: never a
## league's) loaded, two rosters side by side: a team's 28 places (dbedit_build_team_list, sorted L,
## C, R, D, G and by name: shellsort_records with cmp_key_names) or the free agents (KEY.DB +0 =
## 0xff: database_build_list, scrolled by two arrows and a bar when there are more than 28). A
## click on a row selects it or not (dbedit_roster_click, XOR 0x80). The menus: File (Save to
## Game, Temporary Save, Load Database, Return), Roster 1 / Roster 2 (the divisions' teams, Free
## Agents, Find Player), Edit Roster 1 / 2 (Move to Free Agent List, Move to Roster 2 / 1, Create
## Free Agent, Edit Team Lines); their entries are switched on and off as the original does (the
## teams shown, one free agent list at a time, the moves only with players selected).
##
## The background PREZ2.QFS ("ea  " with its palette) is on the CD only: EMBNHL with EMBPAL stands in.

var fe: FrontEnd
var scr: Screen8
var ui: Ui

const ROW_Y := 0x35
const COL_X := [0x2d, 0x167]
const SEL_X := [0x23, 0x15e]
const TITLE_X := [0x64, 0x19e]
const MENU := 0xd0450
const FA_ITEM := [0xd01b9, 0xd0279]       # Roster 1 / 2: Free Agents ... (funcptr_d01cd / d028d)
const TO_FA := [0xd031d, 0xd039d]         # Edit Roster 1 / 2: Move to Free Agent List (d0331 / d03b1)
const TO_OTHER := [0xd033d, 0xd03bd]      # Move to Roster 2 / 1 (d0351 / d03d1)
const LINES_ITEM := [0xd037d, 0xd03fd]    # Edit Team Lines ... (d0391 / d0411)
const DIV_ITEMS := [0xd0139, 0xd01f9]     # the divisions of Roster 1 / 2 (their team lists: off_d0151 / d0211)

# an entry of a list (0x1b bytes in the original): +0 the position, +1 the number, +2 the place, +3 3
# (2: a scratched player), +4 the KEY.DB offset, +8 "F. Last"
enum { E_POS, E_NUM, E_SLOT, E_NAME, E_CMP, E_FLAG, E_OFF }

var files := {}                      # dbedit_load_databases: SEASON, CAREER, CARTEAMS, KEY, TEAMS, ATT
static var column := [12, 21]        # roster_team_column (kept from one visit to the next)
static var is_fa := [false, false]   # byte_d07a8 / d07a9: the column shows the free agents
static var fa_count := 0             # dword_d07b2: the free agents counted (a removal adds one)
var lists := [[], []]                # unk_ea990: a team's 28 entries
var selected := [PackedByteArray(), PackedByteArray()]   # editor_selected
var fa := []                         # dword_d07aa: the free agents' entries
var fa_sel := PackedByteArray()      # dword_d07ae
var scroll := 0                      # editor_scroll: the first free agent shown
var has_scroll := false              # dword_d0c20: more than 28 free agents
var bar := {}                        # unk_d0bf0: the scroll bar
var arrows: Array = []               # unk_d0bb8: the arrows above and below it
var dirty := false                   # editor_dirty
var db_name := "Current"             # unk_ec7c0
var leave := false                   # dword_ebea0
var _pal := PackedByteArray()

func _init(f: FrontEnd) -> void:
	fe = f
	scr = f.scr
	ui = f.ui
	arrows = FrontEnd.buttons_at(0xd0bb8, 2)
	bar = {"x": Exe.i32(0xd0bf0), "y": Exe.i32(0xd0bf4), "w": Exe.i32(0xd0bf8), "h": Exe.i32(0xd0bfc),
		"ty": 0, "th": 0, "top": 0, "total": 0, "pressed": false}

# ---------------------------------------------------------------------------------------------
# the databases (dbedit_load_databases / dbedit_save_databases) and their records
# ---------------------------------------------------------------------------------------------

func _load() -> void:
	files.clear()
	for n in ["SEASON", "CAREER", "CARTEAMS", "KEY", "TEAMS", "ATT"]:
		files[n] = GameFiles.read_raw(n.to_lower() + ".db")

func _save() -> void:
	for n in files:
		GameFiles.write_data(n.to_lower() + ".db", files[n])
	fe.db = Database.open(files["TEAMS"], files["KEY"], files["ATT"])
	fe.stats.forget_files()

## dbedit_teams_record: a team's TEAMS.DB record
static func _trec(t: int) -> int:
	return t * 0x2e8

## the KEY.DB offset in place s (0..24 the skaters at +0x4c, 25..27 the goalies at +0xb0)
func _slot_off(t: int, s: int) -> int:
	var teams: PackedByteArray = files["TEAMS"]
	return teams.decode_s32(_trec(t) + 0x4c + s * 4)

func _set_slot_off(t: int, s: int, off: int) -> void:
	var teams: PackedByteArray = files["TEAMS"]
	teams.encode_s32(_trec(t) + 0x4c + s * 4, off)

## a byte of a KEY.DB record by dbedit_key_ptr (an empty place's -1 reads the byte before)
func _kb(off: int, at: int) -> int:
	var key: PackedByteArray = files["KEY"]
	var i := off + at
	return key[i] if i >= 0 and i < key.size() else 0

## a name of a KEY.DB record (+3 the first, +0x13 the last), as dbedit_key_ptr reads it
func _kname(off: int, at: int) -> String:
	var key: PackedByteArray = files["KEY"]
	var out := ""
	var i := off + at
	while i >= 0 and i < key.size() and key[i] != 0 and out.length() < 0x40:
		out += char(key[i])
		i += 1
	return out

## an entry of a KEY.DB record: "F. Last" (the initial, '.', ' ', strcat of the last name; without a
## first name the last name alone), cmp_key_names compares from +0xb on
func _entry(off: int, slot: int) -> Array:
	var initial := _kb(off, 3)
	var last := _kname(off, 0x13)
	var full := (char(initial) + ". " + last) if initial != 0 else last
	var cmp := full.substr(3) if full.length() > 3 else ""
	var pos := _kb(off, 2)
	return [char(pos) if pos != 0 else "", _kb(off, 1), slot, full, cmp, 3, off]

## dbedit_build_team_list (0x6c043): the 28 places in order (an empty one: no position, number 100),
## the scratched ones (TEAMS +0xe4, 8 places) marked 2
func _team_list(t: int) -> Array:
	var out: Array = []
	for s in 28:
		var off := _slot_off(t, s)
		if off == -1:
			out.append(["", 0x64, 0, "", "", 0, -1])
		else:
			out.append(_entry(off, s))
	var teams: PackedByteArray = files["TEAMS"]
	for k in 8:
		var v := teams[_trec(t) + 0xe4 + k]
		if v != 0x64 and v < 28:
			out[v][E_FLAG] = 2
	return out

## database_build_list (0x6bf4a): the free agents in KEY.DB's order, up to the number counted
func _fa_list() -> Array:
	var key: PackedByteArray = files["KEY"]
	var out: Array = []
	var n := 0
	for off in range(0, key.size() / 0x34 * 0x34, 0x34):
		if n >= fa_count:
			break
		if key[off] == 0xff:
			out.append(_entry(off, n & 0xff))
			n += 1
	return out

## dbedit_find_player_entry (0x6da88): the rows selected in a column
func _count_selected(c: int) -> int:
	var marks: PackedByteArray = fa_sel if is_fa[c] else selected[c]
	var n := 0
	for m in marks:
		if m != 0:
			n += 1
	return n

# ---------------------------------------------------------------------------------------------
# the columns (dbedit_free_lists, dbedit_build_team_roster, dbedit_build_free_agent_list)
# ---------------------------------------------------------------------------------------------

## dbedit_free_lists (0x6de94): a column built again: the free agents counted and listed (the scroll
## bar when more than 28), or the team's places; the move entries switched
func _free_lists(c: int) -> void:
	if is_fa[c]:
		var key: PackedByteArray = files["KEY"]
		fa_count = 0
		for off in range(0, key.size() / 0x34 * 0x34, 0x34):
			if key[off] == 0xff:
				fa_count += 1
		fa = _fa_list()
		Clib.shellsort(fa, NameSort.cmp_key_names)
		fa_sel = PackedByteArray()
		fa_sel.resize(fa_count)
		scroll = 0
		has_scroll = fa_count > 0x1c
		if has_scroll:
			# scrollbar_init: 28 rows of the free agents
			bar["top"] = 0
			bar["ty"] = 0
			bar["total"] = fa_count
			bar["th"] = (bar["h"] - 4) * 0x1c / fa_count
		Menus.at(TO_FA[c]).cb = ""
		Menus.at(TO_OTHER[0]).cb = ""
		Menus.at(TO_OTHER[1]).cb = ""
		return
	lists[c] = _team_list(column[c])
	Clib.shellsort(lists[c], NameSort.cmp_key_names)
	selected[c] = PackedByteArray()
	selected[c].resize(28)
	Menus.at(TO_FA[c]).cb = ""
	Menus.at(TO_OTHER[c]).cb = ""
	if _count_selected(c ^ 1) != 0:
		Menus.at(TO_OTHER[c ^ 1]).cb = "roster_move_players"

## the menu record of a team in the division lists (unk_c5519: the division's bit, unk_c83c3)
static func _team_item(t: int, roster: int) -> Menus.Item:
	var d := Exe.i32(League.CONFERENCE_BITS + t * 4) >> 1
	if d == 4:
		d = 3
	var k := 0
	while k < 7 and Exe.u8(League.DIVISION_TEAMS + d * 7 + k) != t:
		k += 1
	var div := Menus.at(DIV_ITEMS[roster] + d * 0x20)
	return Menus.at(div.sub + k * 0x20) if div != null and div.sub != 0 else null

func _set_team_cb(t: int, cb: String) -> void:
	for r in 2:
		var it := _team_item(t, r)
		if it != null:
			it.cb = cb

# ---------------------------------------------------------------------------------------------
# the screen (player_ratings_card 0x6d2f8: the whole screen drawn again, dbedit_draw_rosters,
# dbedit_draw_team_title, dbedit_draw_roster_column, dbedit_draw_database_title)
# ---------------------------------------------------------------------------------------------

func _draw() -> void:
	scr.clearclip()
	scr.set_text_colors(0x40, 0x43)
	ui.draw_menu_items(Menus.list(MENU, 5), 0x40, 0x41, 0x42)
	scr.setclip(0, 0x13, 0x27f, 0x1df)
	var b := fe.bank("embnhl")
	if b != null:
		scr.drawshape_remap(b.find("bkgd"), 0, 0)
	scr.clearclip()
	scr.setfont(fe.font_main)
	for c in 2:
		_draw_title(c)
		_draw_column(c)
		_draw_db_title()

## dbedit_draw_team_title: CARTEAMS' name of the team (cut to 0x91 pixels) or "Free Agents"
func _draw_title(c: int) -> void:
	var t := "Free Agents"
	if not is_fa[c]:
		t = Database.cstring(files["CARTEAMS"], column[c] * 0x4c + 0x1a, 0x20)
		while t.length() > 0 and scr.textwidth(t) > 0x91:
			t = t.left(t.length() - 1)
	scr.print_text_at(TITLE_X[c], 0x25, t)

## dbedit_draw_roster_column: "%2d", "%c" and the name (format_team_name: cut to 0x91 pixels) of
## each row in the text colour, a selected row XORed with 0x80; the free agents from the scroll
## position with the arrows and the bar
func _draw_column(c: int) -> void:
	var h := scr.font_height()
	var x: int = COL_X[c]
	if not is_fa[c]:
		for k in 0x1c:
			var e: Array = lists[c][k]
			if e[E_POS] == "":
				break
			_draw_row(x, ROW_Y + h * k, e)
			if selected[c][k] != 0:
				scr.xorrect(SEL_X[c], ROW_Y + h * k, 0xf0, h, 0x80)
		return
	var i := scroll
	var k := 0
	while k < 0x1c and i < fa_count:
		if i >= 0 and i < fa.size():
			_draw_row(x, ROW_Y + h * k, fa[i])
			if fa_sel[i] != 0:
				scr.xorrect(SEL_X[c], ROW_Y + h * k, 0xf0, h, 0x80)
		i += 1
		k += 1
	if has_scroll:
		fe.buttons_draw_all(arrows)
		bar["top"] = scroll
		bar["ty"] = (bar["h"] - 4) * scroll / fa_count
		fe._scrollbar_draw(bar)

func _draw_row(x: int, y: int, e: Array) -> void:
	scr.settextcolor(scr.text_color, 0xff)
	scr.printstr_at("%2d" % e[E_NUM], x, y)
	scr.printstr_at(e[E_POS], x + 0x28, y)
	var n: String = e[E_NAME]
	while n.length() > 0 and scr.textwidth(n) > 0x91:
		n = n.left(n.length() - 1)
	scr.printstr_at(n, x + 0x50, y)

## dbedit_draw_database_title: "DATABASE : " and the name in capitals
func _draw_db_title() -> void:
	scr.print_centered_shadow(0x18, "DATABASE : " + db_name.to_upper())

# ---------------------------------------------------------------------------------------------
# the loop (database_screen / database_menu)
# ---------------------------------------------------------------------------------------------

func run() -> int:
	var dc := [fe.dlg_face, fe.dlg_light, fe.dlg_dark, fe.dlg_text, fe.dlg_shadow]
	fe.set_dialog_colors(0x41, 0x40, 0x42, 0x40, 0x42)
	leave = false
	await fe.leave_screen(0x32)
	db_name = "Current"
	scr.setfont(fe.font_main)
	_load()
	dirty = false
	_free_lists(0)
	_free_lists(1)
	_draw()
	var pb := fe.bank("embpal")
	_pal = Screen8.shape_palette(pb.find("!pal")) if pb != null else FrontEnd._grey_palette()
	await scr.fade_in(_pal, 16)
	var handler := func(cb: String):
		await _callback(cb)
		if leave:
			# dbedit_return: unsaved changes are asked about (No / Yes)
			if dirty:
				var r := await fe.message_dialog_buttons(["The database has not been saved.", "Are you sure you want to exit?"],
					FrontEnd.buttons_at(0xc7733, 2))
				if r <= 0:
					leave = false
		return 1 if leave else 0
	var outside := func(e: Dictionary):
		_roster_click(e["x"], e["y"])
		return 0
	var each := func(e: Dictionary):
		_scroll_event(e)
	await ui.run_menu(Menus.list(MENU, 5), 0x40, 0x41, 0x42, handler, Callable(), [1], Callable(), outside, each)
	ui.show_pointer(false)
	await fe.leave_screen(0x32)
	fe.set_dialog_colors(dc[0], dc[1], dc[2], dc[3], dc[4])
	return 2

## database_menu: with more than 28 free agents shown, the arrows move them by one row (button_at)
## and the bar puts the row it points at on top (scrollbar_at)
func _scroll_event(e: Dictionary) -> void:
	if not has_scroll or not (is_fa[0] or is_fa[1]):
		return
	var k := fe.button_at(arrows, e["x"], e["y"], e["buttons"])
	if k == 0 and scroll > 0:
		scroll -= 1
		_draw()
	elif k == 1 and fa_count - 0x1c > scroll:
		scroll += 1
		_draw()
	if fe._scrollbar_at(bar, e["x"], e["y"], e["buttons"]) and scroll != bar["top"]:
		scroll = bar["top"]
		_draw()

## dbedit_roster_click (0x6dac3): a row of a column selected or not (XOR 0x80); the move entries
## of the column follow its selection
func _roster_click(x: int, y: int) -> void:
	var c := -1
	if x >= 0x23 and x <= 0x113:
		c = 0
	elif x >= 0x15e and x <= 0x24e:
		c = 1
	if c < 0:
		return
	var h := scr.font_height()
	if y >= ROW_Y and y < ROW_Y + h * 0x1c:
		var k := (y - ROW_Y) / h
		var ry := k * h + ROW_Y
		if is_fa[c]:
			if scroll + k < fa_count:
				scr.xorrect(SEL_X[c], ry, 0xf0, h, 0x80)
				var i := k + scroll
				if i >= 0 and i < fa_sel.size():
					fa_sel[i] = ~fa_sel[i] & 0xff
		elif lists[c][k][E_POS] != "":
			scr.xorrect(SEL_X[c], ry, 0xf0, h, 0x80)
			selected[c][k] = ~selected[c][k] & 0xff
	_move_menus(c)

## the move entries of column c: Move to Free Agent List when its players are a team's and fewer
## than 30 free agents are counted, Move to the other roster when that is a team
func _move_menus(c: int) -> void:
	if _count_selected(c) > 0:
		if not is_fa[c] and fa_count < 0x1e:
			Menus.at(TO_FA[c]).cb = "free_agent_move_dialog"
		if not is_fa[c ^ 1]:
			Menus.at(TO_OTHER[c]).cb = "roster_move_players"
	else:
		Menus.at(TO_FA[c]).cb = ""
		Menus.at(TO_OTHER[c]).cb = ""

## the column of a callback: Roster 1 / Edit Roster 1 (the first and third bar entries) is 0
func _menu_column() -> int:
	return 0 if ui.menu_root_index == 1 or ui.menu_root_index == 3 else 1

func _callback(cb: String) -> void:
	match cb:
		"dbedit_return":
			leave = true
		"dbedit_select_team":
			await _select_team(_menu_column(), ui.menu_item)
		"dbedit_free_agents":
			_free_agents(_menu_column())
		"roster_move_players":
			await _roster_move_players(_menu_column())
		"free_agent_move_dialog":
			await _free_agent_move_dialog(_menu_column())
		"roster_edit_screen":
			await _roster_edit_screen(_menu_column())
		"create_player_menu":
			await _create_player()
			for c in 2:
				if is_fa[c]:
					_free_lists(c)
			_draw()
		"dbedit_edit_team_lines":
			await _edit_lines(_menu_column())
		"menu_save_to_game":
			await _save_to_game()
		"new_database_dialog":
			var name := (await fe.text_entry_dialog("Enter a new database name:", 8, 0x30, 5)).to_upper()
			if name != "" and fe.entry_key != 0x1b:
				var d := "user://databases".path_join(name)
				DirAccess.make_dir_recursive_absolute(d)
				for n in files:
					var f := FileAccess.open(d.path_join(n + ".DB"), FileAccess.WRITE)
					if f != null:
						f.store_buffer(files[n])
				db_name = name
			_draw()
		"menu_load_database":
			await _load_named()
			_draw()
		_:
			await fe.dispatch(cb)

## dbedit_select_team (0x6d5d0): the team of the entry chosen in column c; the team shown before
## can be chosen again, the free agents again when they were shown
func _select_team(c: int, it: Menus.Item) -> void:
	var team := -1
	for d in 4:
		var div := Menus.at(DIV_ITEMS[c] + d * 0x20)
		for k in (6 if d < 2 else 7):
			if it != null and div != null and it.addr == div.sub + k * 0x20:
				team = Exe.u8(League.DIVISION_TEAMS + d * 7 + k)
	if team < 0:
		return
	var old: int = column[c]
	column[c] = team
	if old == 0xff:
		Menus.at(FA_ITEM[0]).cb = "dbedit_free_agents"
		Menus.at(FA_ITEM[1]).cb = "dbedit_free_agents"
	else:
		_set_team_cb(old, "dbedit_select_team")
	_set_team_cb(team, "")
	Menus.at(LINES_ITEM[c]).cb = "dbedit_edit_team_lines"
	is_fa[c] = false
	_free_lists(c)
	_draw()

## dbedit_free_agents (0x6d6db): the free agents in column c (no other column may show them; no
## team lines)
func _free_agents(c: int) -> void:
	if column[c] != 0xff:
		_set_team_cb(column[c], "dbedit_select_team")
	Menus.at(FA_ITEM[0]).cb = ""
	Menus.at(FA_ITEM[1]).cb = ""
	Menus.at(LINES_ITEM[c]).cb = ""
	column[c] = 0xff
	is_fa[c] = true
	_free_lists(c)
	_draw()

# ---------------------------------------------------------------------------------------------
# moving players (roster_move_players 0x6f29c, free_agent_move_dialog 0x70e8d,
# dbedit_team_scan_players 0x71043, jersey_number_prompt 0x6dcbe)
# ---------------------------------------------------------------------------------------------

## roster_move_players: the selected players of column c into the first free place of the other
## team (a goalie among the 3 goalies, a skater among the 25): KEY.DB +0 the new team, out of the
## old team (dbedit_team_scan_players); a number taken in the new team asks for another
func _roster_move_players(c: int) -> void:
	var t := c ^ 1
	var target: int = column[t]
	var wanted := 0
	var moved := 0
	var changed := false
	var key: PackedByteArray = files["KEY"]
	var rows: Array = fa if is_fa[c] else lists[c]
	var marks: PackedByteArray = fa_sel if is_fa[c] else selected[c]
	var n: int = fa_count if is_fa[c] else 0x1c
	for i in n:
		if i >= marks.size() or marks[i] == 0:
			continue
		wanted += 1
		var off: int = rows[i][E_OFF]
		var place := -1
		if rows[i][E_POS] == "G":
			for k in 3:
				if place < 0 and _slot_off(target, 25 + k) == -1:
					place = 25 + k
		else:
			for k in 25:
				if place < 0 and _slot_off(target, k) == -1:
					place = k
		if place < 0:
			continue
		changed = true
		key[off] = target
		moved += 1
		_set_slot_off(target, place, off)
		if place < lists[t].size():
			lists[t][place][E_FLAG] = 2
		if not is_fa[c]:
			_team_scan_players(column[c], off)
		for k in 28:
			if _kb(off, 1) == _kb(_slot_off(target, k), 1):
				var e := 0x1c - moved
				lists[t][e][E_NUM] = _kb(off, 1)
				lists[t][e][E_SLOT] = place
				await _jersey_number_prompt(t, e)
	if moved != wanted:
		if wanted == 1:
			await fe.message_dialog(["There is no space to add", "the selected player"])
		else:
			await fe.message_dialog(["There is not enough space to", "add all selected players"])
	if changed:
		dirty = true
		_free_lists(0)
		_free_lists(1)
		_draw()

## free_agent_move_dialog: each selected player of a team asked about ("Move <name> to Free Agent
## List?" No / Yes) while fewer than 30 free agents are counted
func _free_agent_move_dialog(c: int) -> void:
	var wanted := 0
	var asked := 0
	var moved := false
	var key: PackedByteArray = files["KEY"]
	for i in 0x1c:
		if selected[c][i] == 0:
			continue
		wanted += 1
		if fa_count >= 0x1e:
			continue
		asked += 1
		var off: int = lists[c][i][E_OFF]
		var name := _kname(off, 3) + " " + _kname(off, 0x13)
		var r := await fe.message_dialog_buttons(["Move", name, "to Free Agent List?"], FrontEnd.buttons_at(0xc7733, 2))
		if r != 1:
			continue
		moved = true
		if column[c] < 0x1a:
			key[off] = 0xff
			_team_scan_players(column[c], off)
	if wanted != asked:
		await fe.message_dialog(["There is not enough space", "in the free agent list", "for all selected players"])
	if moved:
		dirty = true
		_free_lists(c)
		if is_fa[c ^ 1]:
			_free_lists(c ^ 1)
		_draw()

## dbedit_team_scan_players: the place of the player (the same ATT / CAREER / SEASON pointers at
## +0x24..+0x2c) emptied (one more free agent counted) and taken out of the line table
func _team_scan_players(team: int, off: int) -> void:
	var found := -1
	for s in 28:
		if found >= 0:
			break
		var o := _slot_off(team, s)
		var same := true
		for at in [0x24, 0x28, 0x2c]:
			if _kb(o, at) | _kb(o, at + 1) << 8 | _kb(o, at + 2) << 16 | _kb(o, at + 3) << 24 \
					!= _kb(off, at) | _kb(off, at + 1) << 8 | _kb(off, at + 2) << 16 | _kb(off, at + 3) << 24:
				same = false
		if same:
			fa_count += 1
			_set_slot_off(team, s, -1)
			found = s
	if found < 0:
		return
	var teams: PackedByteArray = files["TEAMS"]
	for k in 0x30:
		if teams[_trec(team) + 0xbc + k] == found:
			teams[_trec(team) + 0xbc + k] = 0x64

## jersey_number_prompt: while another entry of the team's list has the number of entry e, "The
## jersey number %2d is already used!" asks for a new one (database_dialog_box, 0..99)
func _jersey_number_prompt(t: int, e: int) -> void:
	var off := _slot_off(column[t], lists[t][e][E_SLOT])
	var key: PackedByteArray = files["KEY"]
	while true:
		var taken := false
		for k in 0x1c:
			if k != e and lists[t][e][E_NUM] == lists[t][k][E_NUM]:
				taken = true
				break
		if not taken:
			return
		var name := _kname(off, 3) + " " + _kname(off, 0x13)
		var r: Array = await _dialog_box(["The jersey number %2d is already used!" % _kb(off, 1),
			"Please enter a new jersey number for", name], "", 2, 0x16, true, 0, 0x63, true)
		if off >= 0:
			key[off + 1] = r[1] & 0xff
		lists[t][e][E_NUM] = _kb(off, 1)

## database_dialog_box (0x71f0c): a bevelled box with the lines and a black field under them
## (`width` + 8 pixels), the text typed into it: a number (digits, Esc allowed) asked again until it
## is in lo..hi, or a text (letters and the space; `keep` refuses an empty one and gives the old text
## back for Esc); spaces cut off both ends. Returns [text, number or 1, -1 for Esc]
func _dialog_box(lines: Array, initial: String, maxlen: int, width: int, numeric: bool, lo: int, hi: int, keep: bool) -> Array:
	var lh := scr.font_height() + 2
	var w := 0
	var h := 0
	for l in lines:
		w = maxi(w, scr.textwidth(l))
		h += lh
	var fw := width + 8
	w = maxi(w, fw) + 0x10
	h += 0x1f
	var x := (640 - w) / 2
	var y := (480 - h) / 2
	var behind := scr.snapshot()
	fe.draw_bevel_box_b(x, y, x + w - 1, y + h - 1, false)
	var ty := y + 8
	for l in lines:
		scr.print_text_at(x + (w - scr.textwidth(l)) / 2, ty, l)
		ty += lh
	var fx := x + (w - fw) / 2
	fe.draw_bevel_box_b(fx, ty, fx + fw - 1, ty + 0x11, false, [0, 0x42, 0x40, 0x41, 0x40, 0x42])
	var keep_fg := scr.text_fg
	var keep_bg := scr.text_bg
	scr.settextcolor(scr.text_color, 0)
	var buf := PackedByteArray()
	buf.resize(maxlen + 2)
	var a := initial.to_ascii_buffer()
	for i in mini(a.size(), maxlen):
		buf[i] = a[i]
	var value := -1
	ui.keys.clear()
	if numeric:
		while true:
			var k: int = await fe._entry_loop(buf, maxlen, fw - 8, fx + 2, ty + 2, 0xc)
			if k == 0x1b and not keep:
				break
			if k != 0x1b:
				value = -1
				if not (keep and buf[0] == 0):
					for i in maxlen:
						if buf[i] >= 0x30 and buf[i] <= 0x39:
							value = FrontEnd.atoi(FrontEnd.cstring_of(buf))
						else:
							break
			if value >= lo and value <= hi:
				break
	else:
		var old := buf.duplicate()
		var done := false
		while not done:
			var k: int = await fe._entry_loop(buf, maxlen, fw - 8, fx + 2, ty + 2, 0x14)
			if k != 0x1b:
				done = not (keep and buf[0] == 0)
				if done:
					value = 1
			elif keep:
				buf = old.duplicate()
			else:
				done = true
	ui.reset_events()
	scr.restore(behind)
	scr.settextcolor(keep_fg, keep_bg)
	return [FrontEnd.cstring_of(buf).strip_edges(), value]

# ---------------------------------------------------------------------------------------------
# Save to Game (menu_save_to_game 0x6c2f9, dbedit_validate_lines 0x6ef84, check_lines 0x6ed8f,
# dbedit_errors_screen 0x6ec95, dbedit_show_errors 0x6ed39, dbedit_error_dialog_loop 0x6eab5)
# ---------------------------------------------------------------------------------------------

const ERROR_TEXTS := {1: "The forward lines are not complete on ", 2: "The defence lines are not complete on ",
	4: "The power play lines are not complete on ", 8: "The penalty killing lines are not complete on ",
	0x10: "The goalie lines are not complete on ", 0x20: "The extra attacker lines are not complete on ",
	0x40: "There are not enough players on ", 0x80: "There are not enough goalies on ",
	0x100: "There are not enough forwards on ", 0x200: "There are not enough defence on "}

var _err_lines := 0                  # the line of the errors page
var _err_page := true                # a new page is drawn before the next message
var _err_header := true              # "Errors found in databases!" not shown yet

## menu_save_to_game: "Save as game databases?"; the lines checked; without errors the databases
## written as the game's ("Saving databases.", the name Current)
func _save_to_game() -> void:
	var r := await fe.message_dialog_buttons(["Save as game databases?"], FrontEnd.buttons_at(0xd0c24, 2))
	if r != 1:
		return
	var ok := await _validate_lines()
	_draw()
	if not ok:
		return
	db_name = "Current"
	fe.message_show(["Saving databases."])
	await ui.frame()
	_save()
	fe.restore_dialog_background()
	_draw()

## the errors of a team: 1 / 2 / 4 / 8 / 0x10 / 0x20 an empty place in the forward lines, the
## defence pairs, the power play, the penalty killing, the goalies, the extra attackers; fewer than
## 5 skaters (0x40), 2 goalies (0x80), 3 forwards (0x100), 2 defencemen (0x200)
func _line_errors(t: int) -> int:
	var teams: PackedByteArray = files["TEAMS"]
	var r := _trec(t)
	var skaters := 0
	var d := 0
	var fwd := 0
	var goalies := 0
	for s in 25:
		var off := _slot_off(t, s)
		if off != -1:
			skaters += 1
			if _kb(off, 2) == 0x44:
				d += 1
			else:
				fwd += 1
	for s in 3:
		if _slot_off(t, 25 + s) != -1:
			goalies += 1
	var bits := 0
	for g in [[0xbc, 12, 1], [0xc8, 6, 2], [0xce, 10, 4], [0xd8, 8, 8], [0xe0, 2, 0x10], [0xe2, 2, 0x20]]:
		for i in g[1]:
			if teams[r + g[0] + i] == 0x64:
				bits |= g[2]
	if skaters < 5:
		bits |= 0x40
	if fwd < 3:
		bits |= 0x100
	if d < 2:
		bits |= 0x200
	if goalies < 2:
		bits |= 0x80
	return bits

## dbedit_validate_lines: the 28 teams' errors listed on pages of 30 lines (Continue goes on, Stop or
## Esc ends the list); true when no team has one
func _validate_lines() -> bool:
	_err_lines = 0
	_err_page = true
	_err_header = true
	var ok := true
	for t in 0x1c:
		var bits := _line_errors(t)
		var r := -2
		if bits != 0:
			ok = false
			r = await _check_lines(t, bits)
			if _err_lines != 0:
				_err_lines += 1
		if r == -2 and (_err_lines >= 0x1e or (_err_lines > 0 and t == 0x1b)):
			r = await _show_errors()
		if r == -1 or r == 1:
			break
	return ok

## check_lines: each error of the team a line ("... on " and TEAMS' name of the team), the page
## shown when it is full
func _check_lines(t: int, bits: int) -> int:
	var r := -2
	var i := 0
	while i < 10 and r != 1 and r != -1:
		r = -2
		if _err_page:
			_errors_screen()
		var b := Exe.i32(0xd0cda + i * 4)
		if bits & b:
			var msg: String = ERROR_TEXTS.get(b, "") + Database.cstring(files["TEAMS"], _trec(t) + 0x1a, 0x20)
			scr.print_centered_shadow(_err_lines * 13 + 0x1f, msg)
			_err_lines += 1
			if _err_lines >= 0x1e:
				r = await _show_errors()
		i += 1
	return r

## dbedit_errors_screen: a page: the menu bar, the face colour, Continue and Stop, the heading once
func _errors_screen() -> void:
	scr.clearclip()
	ui.draw_menu_items(Menus.list(MENU, 5), 0x40, 0x41, 0x42)
	scr.fillrect(0, 0x13, 0x280, 0x1cd, 0x41)
	fe.buttons_draw_all(FrontEnd.buttons_at(0xd0ca2, 2))
	_err_page = false
	if _err_header:
		scr.print_centered_shadow(_err_lines * 13 + 0x1f, "Errors found in databases!")
		_err_lines += 2
		_err_header = false

## dbedit_show_errors / dbedit_error_dialog_loop: the page until Continue (0), Stop (1) or Esc (-1)
func _show_errors() -> int:
	_err_page = true
	_err_lines = 0
	var list := FrontEnd.buttons_at(0xd0ca2, 2)
	ui.show_pointer(true)
	ui.reset_events()
	while true:
		var e: Dictionary = await ui.wait_event()
		if e["buttons"] & 4:
			return -1
		if e["buttons"] & 3:
			var k := fe.button_at(list, e["x"], e["y"], e["buttons"])
			if k >= 0:
				return k
	return -1

# ---------------------------------------------------------------------------------------------
# Find Player ... (roster_edit_screen 0x71961, player_name_normalize 0x6f159,
# dbedit_find_player_by_name 0x71690, dbedit_setup_team_menu 0x7183d)
# ---------------------------------------------------------------------------------------------

## player_name_normalize: the first two words of letters (up to 15 letters each)
static func normalize(s: String) -> Array:
	var letter := func(ch: int) -> bool:
		return (ch >= 0x41 and ch <= 0x5a) or (ch >= 0x61 and ch <= 0x7a)
	var b := s.to_ascii_buffer()
	b.append(0)
	var n := b.size() - 1
	var i := 0
	var words := ["", ""]
	for w in 2:
		while i < n and not letter.call(b[i]):
			i += 1
		var out := ""
		while i < n and out.length() < 0xf:
			if letter.call(b[i]):
				out += char(b[i])
				i += 1
			else:
				i += 1
				break
		words[w] = out
		if out.length() == 0xf:
			while i < n and letter.call(b[i]):
				i += 1
	return words

## the names as roster_edit_screen compares them: both words the first and last names, or one word
## the last name
static func _matches(first: String, last: String, kfirst: String, klast: String) -> bool:
	if Clib.strcmp(first, kfirst) == 0 and Clib.strcmp(last, klast) == 0:
		return true
	return last == "" and Clib.strcmp(klast, first) == 0

## roster_edit_screen: "Enter name of player to find:"; the teams (one entry each) and the free
## agents with a player of that name; more than one: "Choose which team to display"; that team (or
## the free agents) into column c ("... is already displayed on Roster 2 / 1": the other column
## shows it), its players of that name selected
func _roster_edit_screen(c: int) -> void:
	var o := c ^ 1
	var r: Array = await _dialog_box(["Enter name of player to find:"], "", 0x1f, 0xba, false, 0, 0, false)
	var query: String = (r[0] as String).to_lower()
	var w := normalize(query)
	var first: String = w[0]
	var last: String = w[1]
	if last == "" and first == "":
		return
	var found: Array = []
	for t in 26:
		for s in 28:
			var off := _slot_off(t, s)
			if _matches(first, last, _kname(off, 3).to_lower(), _kname(off, 0x13).to_lower()):
				found.append(t)
				break
	var key: PackedByteArray = files["KEY"]
	for off in range(0, key.size() / 0x34 * 0x34, 0x34):
		if key[off] == 0xff and _matches(first, last, _kname(off, 3).to_lower(), _kname(off, 0x13).to_lower()):
			found.append(0x64)
			break
	if found.is_empty():
		await fe.message_dialog([query, "does not exist!"])
		_draw()
		return
	var pick: int = found[0]
	if found.size() > 1:
		var names: Array = []
		for t in found:
			names.append("Free Agent List" if t == 0x64 else Exe.str_ptr(LeagueScreens.TEAM_NAMES + t * 4))
		pick = found[await fe.listbox_dialog(names, "Choose which team to display", 0)]
	if pick == 0x64:
		if is_fa[o]:
			await fe.message_dialog([query, "is already displayed on", "Roster 2" if c == 0 else "Roster 1"])
		elif not is_fa[c]:
			_setup_team_menu(c, 0x64)
			is_fa[c] = true
			_free_lists(c)
			column[c] = 0xff
	elif column[o] == pick:
		await fe.message_dialog([query, "is already displayed on", "Roster 2" if c == 0 else "Roster 1"])
		c = o
	elif column[c] != pick:
		_setup_team_menu(c, pick)
		is_fa[c] = false
		column[c] = pick
		_free_lists(c)
	_find_player_by_name(first, last, c)
	_draw()
	_move_menus(c)

## dbedit_setup_team_menu: the team shown before can be chosen again (or the free agents), the new
## one (or the free agents) not; team lines for a team
func _setup_team_menu(c: int, team: int) -> void:
	if column[c] == 0xff:
		Menus.at(FA_ITEM[0]).cb = "dbedit_free_agents"
		Menus.at(FA_ITEM[1]).cb = "dbedit_free_agents"
	else:
		_set_team_cb(column[c], "dbedit_select_team")
	if team == 0x64:
		Menus.at(LINES_ITEM[c]).cb = ""
		Menus.at(FA_ITEM[0]).cb = ""
		Menus.at(FA_ITEM[1]).cb = ""
		return
	_set_team_cb(team, "")
	Menus.at(LINES_ITEM[c]).cb = "dbedit_edit_team_lines"

## dbedit_find_player_by_name: the rows of column c with the name selected (a free agent's name is
## its entry's "F. Last": the first word must be the initial); the free agents scroll to the first
func _find_player_by_name(first: String, last: String, c: int) -> void:
	if not is_fa[c]:
		for k in 0x1c:
			selected[c][k] = 0
		for k in 0x1c:
			var off: int = lists[c][k][E_OFF]
			if _matches(first, last, _kname(off, 3).to_lower(), _kname(off, 0x13).to_lower()):
				selected[c][k] = ~selected[c][k] & 0xff
		return
	for k in fa_sel.size():
		fa_sel[k] = 0
	if has_scroll:
		scroll = -1
	for k in fa.size():
		var n := normalize(fa[k][E_NAME])
		if _matches(first, last, (n[0] as String).to_lower(), (n[1] as String).to_lower()):
			fa_sel[k] = ~fa_sel[k] & 0xff
			if has_scroll and scroll == -1:
				scroll = k
	# (the original goes on with -1 when none matched, reading before the list)
	scroll = maxi(scroll, 0)

# ---------------------------------------------------------------------------------------------
# not yet ported literally: Create Free Agent, the line editor, the databases by name
# ---------------------------------------------------------------------------------------------

## create_player_menu / create_player_form: a new free agent: names, number, position; the
## ratings of an average player, empty statistics
func _create_player() -> void:
	var first := await fe.text_entry_dialog("First name of the new player", 15, 0, 4)
	if first == "" or fe.entry_key == 0x1b:
		return
	var last := await fe.text_entry_dialog("Last name of the new player", 15, 0, 4)
	if last == "" or fe.entry_key == 0x1b:
		return
	var num := await fe.text_entry_dialog("Jersey number", 2, 0x16, 8)
	var pos := (await fe.text_entry_dialog("Position (C, L, R, D or G)", 1, 0, 0x10)).to_upper()
	if not ["C", "L", "R", "D", "G"].has(pos):
		pos = "C"
	var goalie := pos == "G"
	var key: PackedByteArray = files["KEY"]
	var att: PackedByteArray = files["ATT"]
	var career: PackedByteArray = files["CAREER"]
	var season: PackedByteArray = files["SEASON"]
	var rec := PackedByteArray()
	rec.resize(0x34)
	rec[0] = 0xff
	rec[1] = clampi(int(num) if num.is_valid_int() else 0, 0, 99)
	rec[2] = pos.unicode_at(0)
	var fa := first.to_ascii_buffer()
	var la := last.to_ascii_buffer()
	for i in 15:
		rec[3 + i] = fa[i] if i < fa.size() else 0
		rec[0x13 + i] = la[i] if i < la.size() else 0
	rec.encode_s32(0x24, att.size())
	rec.encode_s32(0x28, career.size())
	rec.encode_s32(0x2c, season.size())
	rec[0x30] = 0x30
	rec[0x31] = 0x30
	rec[0x32] = 0x30
	rec[0x33] = 0x30
	var ratings := PackedByteArray()
	ratings.resize(0x10 if goalie else 0x14)
	ratings.fill(8)
	ratings[0] = 0
	att.append_array(ratings)
	var cz := PackedByteArray()
	cz.resize(0x28)
	career.append_array(cz)
	var sz := PackedByteArray()
	sz.resize(0x36 if goalie else 0x2f)
	season.append_array(sz)
	key.append_array(rec)
	dirty = true

## dbedit_edit_team_lines: the line editor on the registry's databases
func _edit_lines(c: int) -> void:
	var keep_db := fe.db
	var keep_home := Session.home_team
	var keep_lines: Dictionary = Session.line_override.duplicate()
	fe.db = Database.open(files["TEAMS"], files["KEY"], files["ATT"])
	Session.home_team = column[c]
	Session.line_override.clear()
	var ed := LineEditor.new(fe)
	ed.teams_read = func() -> PackedByteArray: return files["TEAMS"]
	ed.teams_write = func(b: PackedByteArray) -> void:
		files["TEAMS"] = b
		dirty = true
	await ed.edit(0, 0xcf1af, 3)
	fe.db = keep_db
	Session.home_team = keep_home
	Session.line_override = keep_lines
	if is_fa[c ^ 1]:
		_free_lists(c ^ 1)
	_draw()
	await scr.fade_in(_pal, 16)

## Load Database ...: a copy saved with Temporary Save
func _load_named() -> void:
	var d := DirAccess.open("user://databases")
	if d == null or d.get_directories().is_empty():
		await fe.message_dialog(["No databases have been saved."])
		return
	var names: Array = Array(d.get_directories()).slice(0, 6)
	var list: Array = []
	var y := 0x20
	for n in names:
		list.append(FrontEnd.UiButton.new(16, y, 160, 20, n, 5))
		y += 24
	list.append(FrontEnd.UiButton.new(-16, -8, 80, 20, "Cancel", 2))
	var lines: Array = ["Load which database?", ""]
	for n in names:
		lines.append("")
	var r := await fe.message_dialog_buttons(lines, list)
	if r < 0 or r >= names.size():
		return
	var dir := "user://databases".path_join(names[r])
	for n in files:
		var b := FileAccess.get_file_as_bytes(dir.path_join(n + ".DB"))
		if not b.is_empty():
			files[n] = b
	db_name = names[r]
	dirty = true
	_free_lists(0)
	_free_lists(1)
