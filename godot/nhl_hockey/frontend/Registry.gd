class_name Registry
extends RefCounted
## The Central Registry (menu_central_registry 0x6be95 -> database_screen 0x6cc20, database_menu
## 0x6e089): the rosters of two teams (or a team and the free agents) side by side, sorted L, C, R,
## D, G and by name (cmp_key_names); a click selects players (dbedit_roster_click), the Edit Roster
## menus move them to the other roster (roster_move_players: the first free place of the team's
## skater or goalie list, a new jersey number when the number is taken) or to the free agents
## (KEY.DB +0 = 0xff), create a free agent (create_player_menu) and edit the team's lines. File:
## Save to Game (the databases written; a league's when a league is open), Temporary Save / Load
## Database (named copies), Return.
##
## A player who leaves a team leaves holes in its line table; the original makes the user fix
## them (dbedit_validate_lines, dbedit_errors_screen) before saving, here they are filled with
## the team's other players of the position.

var fe: FrontEnd
var scr: Screen8
var ui: Ui

const DIV_LISTS := [0xcfbe8, 0xcfcf2, 0xcfe08, 0xcff51]   # the team entries of the four divisions
const COL_X := [0x2d, 0x167]
const SEL_X := [0x23, 0x15e]
const ROW_Y := 0x35

var files := {}                      # KEY, CAREER, ATT, CARTEAMS, TEAMS, SEASON
var column := [12, 21]               # roster_team_column: the team of each roster (0xff the free agents)
var rows := [[], []]                 # the entries: [position, number, KEY offset, "F. Last"]
var selected := [{}, {}]             # editor_selected / dword_d07ae: the rows selected
var scroll := 0                      # editor_scroll: the first free agent shown
var dirty := false                   # editor_dirty: changes not saved
var db_name := "CURRENT"
var _pal := PackedByteArray()

func _init(f: FrontEnd) -> void:
	fe = f
	scr = f.scr
	ui = f.ui

# ---------------------------------------------------------------------------------------------
# the databases (dbedit_load_databases / dbedit_save_databases)
# ---------------------------------------------------------------------------------------------

func _load() -> void:
	files.clear()
	var l: League = Session.league
	for n in ["KEY", "CAREER", "ATT", "CARTEAMS", "TEAMS", "SEASON"]:
		files[n] = l.file(n).duplicate() if l != null else GameFiles.read_raw(n.to_lower() + ".db")
	db_name = l.name if l != null else "CURRENT"

func _save() -> void:
	var l: League = Session.league
	for n in files:
		if l != null:
			l.files[n] = files[n].duplicate()
		else:
			GameFiles.write_data(n.to_lower() + ".db", files[n])
	if l != null:
		l.save()
	else:
		fe.db = Database.open(files["TEAMS"], files["KEY"], files["ATT"])
	fe.stats.forget_files()
	dirty = false

func _key(off: int) -> PackedByteArray:
	return files["KEY"].slice(off, off + 0x34)

static func _entry(key: PackedByteArray, off: int) -> Array:
	var first := Database.cstring(key, 3, 16)
	var last := Database.cstring(key, 0x13, 16)
	return [char(key[2]) if key[2] != 0 else "", key[1], off, (first.left(1) + ". " if first != "" else "") + last, last]

static func _pos_rank(p: String) -> int:
	return {"L": 0, "C": 1, "R": 2, "D": 3, "G": 4}.get(p, 5)

static func _sort(list: Array) -> void:
	list.sort_custom(func(a, b):
		if a[0] != b[0]:
			return _pos_rank(a[0]) < _pos_rank(b[0])
		return a[4] < b[4])

## dbedit_build_team_roster / dbedit_build_free_agent_list
func _build(c: int) -> void:
	var out: Array = []
	var key: PackedByteArray = files["KEY"]
	if column[c] == 0xff:
		for off in range(0, key.size() - 0x33, 0x34):
			if key[off] == 0xff:
				out.append(_entry(key.slice(off, off + 0x34), off))
	else:
		var teams: PackedByteArray = files["TEAMS"]
		var base: int = column[c] * 0x2e8
		for i in 28:
			var at := base + (0x4c + i * 4 if i < 25 else 0xb0 + (i - 25) * 4)
			var off := teams.decode_s32(at)
			if off >= 0 and off + 0x34 <= key.size():
				out.append(_entry(key.slice(off, off + 0x34), off))
	_sort(out)
	rows[c] = out
	selected[c] = {}
	if column[c] == 0xff:
		scroll = 0

# ---------------------------------------------------------------------------------------------
# the screen (dbedit_draw_rosters, dbedit_draw_team_title, dbedit_draw_roster_column)
# ---------------------------------------------------------------------------------------------

func _draw() -> void:
	scr.clearclip()
	var b := fe.bank("embnhl")
	if b != null:
		scr.drawshape_remap(b.find("bkgd"), 0, 0)
	scr.setfont(fe.font_main)
	scr.set_text_colors(0x40, 0x43)
	var t := "DATABASE : " + db_name.to_upper()
	scr.print_text_at((640 - scr.textwidth(t)) / 2, 0x18, t)
	var fh := scr.font_height()
	for c in 2:
		var title := "Free Agents" if column[c] == 0xff else Database.cstring(files["TEAMS"], column[c] * 0x2e8 + 0x1a, 13)
		scr.print_text_at([100, 0x19e][c], 0x25, title)
		var first := scroll if column[c] == 0xff else 0
		for k in 0x1c:
			var i := first + k
			if i >= rows[c].size():
				break
			var e: Array = rows[c][i]
			var y := ROW_Y + k * fh
			scr.print_text_at(COL_X[c], y, "%2d" % e[1])
			scr.print_text_at(COL_X[c] + 0x28, y, e[0])
			var n: String = e[3]
			while n.length() > 0 and scr.textwidth(n) > 0x91:
				n = n.left(n.length() - 1)
			scr.print_text_at(COL_X[c] + 0x50, y, n)
			if selected[c].has(i):
				_xor_row(c, k)
		if column[c] == 0xff and rows[c].size() > 0x1c:
			fe.buttons_draw_all(FrontEnd.buttons_at(0xd0bb8, 2))
	ui.draw_menu_items(Menus.list(0xd0450, 5), 0x40, 0x41, 0x42)

func _xor_row(c: int, k: int) -> void:
	var fh := scr.font_height()
	var y := ROW_Y + k * fh
	for yy in range(y, y + fh):
		for x in range(SEL_X[c], SEL_X[c] + 0xf0):
			scr.putpixel(x, yy, scr.getpixel(x, yy) ^ 0x80)

## the menu entries that can be used: the teams shown are not offered again, the moves need a
## selection, a full roster takes no more players
func _update_menus() -> void:
	for c in 2:
		for d in 4:
			var n := 6 if d < 2 else 7
			for k in n:
				var team := Exe.u8(League.DIVISION_TEAMS + d * 7 + k)
				Menus.at(DIV_LISTS[d] + k * 0x20).cb = "" if column.has(team) else "dbedit_select_team"
	Menus.at(0xd01b9).cb = "" if column[0] == 0xff else "dbedit_free_agents"
	Menus.at(0xd0279).cb = "" if column[1] == 0xff else "dbedit_free_agents"
	for c in 2:
		var any: bool = not selected[c].is_empty()
		var to_free := 0xd031d if c == 0 else 0xd039d
		var to_other := 0xd033d if c == 0 else 0xd03bd
		Menus.at(to_free).cb = "dbedit_to_free_agents" if any and column[c] != 0xff else ""
		Menus.at(to_other).cb = "dbedit_to_other_roster" if any and column[c ^ 1] != 0xff else ""
		Menus.at(0xd035d if c == 0 else 0xd03dd).cb = "create_player_menu"
		Menus.at(0xd037d if c == 0 else 0xd03fd).cb = "dbedit_edit_team_lines" if column[c] != 0xff else ""

# ---------------------------------------------------------------------------------------------
# the loop (database_menu)
# ---------------------------------------------------------------------------------------------

func run() -> int:
	await fe.leave_screen(100)
	fe.set_dialog_colors(0x41, 0x40, 0x42, 0x40, 0x42)
	_load()
	column = [Session.home_team if Session.home_team < 26 else 12, Session.away_team if Session.away_team < 26 else 21]
	if column[0] == column[1]:
		column[1] = (column[0] + 1) % 26
	_build(0)
	_build(1)
	dirty = false
	var pb := fe.bank("embpal")
	_pal = Screen8.shape_palette(pb.find("!pal")) if pb != null else FrontEnd._grey_palette()
	_update_menus()
	_draw()
	await scr.fade_in(_pal, 16)
	var state := {"done": false}
	var handler := func(cb: String):
		var r = await _callback(cb)
		_update_menus()
		_draw()
		return r
	var outside := func(e: Dictionary):
		_click(e["x"], e["y"])
		_update_menus()
		ui.draw_menu_items(Menus.list(0xd0450, 5), 0x40, 0x41, 0x42)
		return 0
	await ui.run_menu(Menus.list(0xd0450, 5), 0x40, 0x41, 0x42, handler, Callable(), [1], Callable(), outside)
	ui.show_pointer(false)
	await fe.leave_screen(100)
	return 2

## dbedit_roster_click: a row of a roster selected or not; the arrows scroll the free agents
func _click(x: int, y: int) -> void:
	var c := -1
	if x >= 0x23 and x <= 0x113:
		c = 0
	elif x > 0x15d and x < 0x24f:
		c = 1
	var fh := scr.font_height()
	if x >= 314 and x < 326 and (column[0] == 0xff or column[1] == 0xff):
		var fa := 0 if column[0] == 0xff else 1
		if y >= 36 and y < 46:
			scroll = maxi(scroll - 0x1c, 0)
			_draw()
			return
		if y >= 466 and y < 476:
			scroll = mini(scroll + 0x1c, maxi(rows[fa].size() - 0x1c, 0))
			_draw()
			return
	if c < 0 or y < ROW_Y or y >= ROW_Y + 0x1c * fh:
		return
	var k := (y - ROW_Y) / fh
	var i := k + (scroll if column[c] == 0xff else 0)
	if i >= rows[c].size():
		return
	if selected[c].has(i):
		selected[c].erase(i)
	else:
		selected[c][i] = true
	_xor_row(c, k)

func _callback(cb: String):
	match cb:
		"dbedit_return":
			if dirty:
				var r := await fe.message_dialog_buttons(["The database has not been saved.", "Are you sure you want to exit?"],
					FrontEnd.buttons_at(0xc7733, 2))
				if r != 1:
					return 0
			return 1
		"dbedit_select_team":
			var it := ui.menu_item
			var c := 0 if ui.menu_root_index == 1 else 1
			for d in 4:
				var n := 6 if d < 2 else 7
				for k in n:
					if it != null and it.addr == DIV_LISTS[d] + k * 0x20:
						column[c] = Exe.u8(League.DIVISION_TEAMS + d * 7 + k)
			_build(c)
			return 0
		"dbedit_free_agents":
			var c := 0 if ui.menu_root_index == 1 else 1
			column[c] = 0xff
			_build(c)
			return 0
		"dbedit_to_free_agents":
			await _move(0 if ui.menu_root_index == 3 else 1, true)
			return 0
		"dbedit_to_other_roster":
			await _move(0 if ui.menu_root_index == 3 else 1, false)
			return 0
		"create_player_menu":
			await _create_player()
			return 0
		"dbedit_edit_team_lines":
			await _edit_lines(0 if ui.menu_root_index == 3 else 1)
			return 0
		"menu_save_to_game":
			var r := await fe.message_dialog_buttons(["Save as game databases?"], FrontEnd.buttons_at(0xd0c24, 2))
			if r == 1:
				_repair_all_lines()
				_save()
				await fe.message_dialog(["The databases are saved."])
			return 0
		"new_database_dialog":
			var name := (await fe.text_entry_dialog("Enter a name for the database", 8)).to_upper()
			if name != "":
				var d := "user://databases".path_join(name)
				DirAccess.make_dir_recursive_absolute(d)
				for n in files:
					var f := FileAccess.open(d.path_join(n + ".DB"), FileAccess.WRITE)
					if f != null:
						f.store_buffer(files[n])
				db_name = name
			return 0
		"menu_load_database":
			await _load_named()
			return 0
		"roster_edit_screen":
			await _find_player(0 if ui.menu_root_index == 1 else 1)
			return 0
	return await fe.dispatch(cb)

## roster_move_players / free_agent_move_dialog: the selected players of roster c to the other
## roster or to the free agents
func _move(c: int, to_free: bool) -> void:
	var key: PackedByteArray = files["KEY"]
	var teams: PackedByteArray = files["TEAMS"]
	var target: int = 0xff if to_free else column[c ^ 1]
	var moved := 0
	var wanted: int = selected[c].size()
	for i in selected[c].keys():
		var e: Array = rows[c][i]
		var off: int = e[2]
		var goalie: bool = e[0] == "G"
		if target != 0xff:
			var base := target * 0x2e8
			var place := -1
			for k in (3 if goalie else 25):
				var at := base + (0xb0 if goalie else 0x4c) + k * 4
				if teams.decode_s32(at) == -1:
					place = at
					break
			if place < 0:
				continue
			teams.encode_s32(place, off)
		# out of the old team's lists
		if column[c] != 0xff:
			var ob: int = column[c] * 0x2e8
			for k in 28:
				var at := ob + (0x4c + k * 4 if k < 25 else 0xb0 + (k - 25) * 4)
				if teams.decode_s32(at) == off:
					teams.encode_s32(at, -1)
		key[off] = target
		moved += 1
		if target != 0xff:
			await _jersey_number(target, off)
	if moved != wanted:
		if wanted == 1:
			await fe.message_dialog(["There is no space to add", "the selected player"])
		else:
			await fe.message_dialog(["There is not enough space to", "add all selected players"])
	if moved > 0:
		dirty = true
		for t in column:
			if t != 0xff:
				_repair_lines(t)
	_build(0)
	_build(1)

## jersey_number_prompt: a number taken in the new team asks for another one
func _jersey_number(team: int, off: int) -> void:
	var key: PackedByteArray = files["KEY"]
	var teams: PackedByteArray = files["TEAMS"]
	while true:
		var taken := false
		for k in 28:
			var at := team * 0x2e8 + (0x4c + k * 4 if k < 25 else 0xb0 + (k - 25) * 4)
			var o := teams.decode_s32(at)
			if o >= 0 and o != off and key[o + 1] == key[off + 1]:
				taken = true
		if not taken:
			return
		var name := Database.cstring(key, off + 3, 16) + " " + Database.cstring(key, off + 0x13, 16)
		var s := await fe.text_entry_dialog("The jersey number %d is already used. New number for %s:" % [key[off + 1], name], 2)
		if s.is_valid_int() and int(s) >= 0 and int(s) <= 99:
			key[off + 1] = int(s)

## the line table without holes: a place whose player left takes another of the team's players
## of the position (forwards and defencemen as the original's lines, any skater in the units)
func _repair_lines(team: int) -> void:
	var teams: PackedByteArray = files["TEAMS"]
	var key: PackedByteArray = files["KEY"]
	var base := team * 0x2e8
	var present := {}
	var pos := {}
	for r in 28:
		var at := base + (0x4c + r * 4 if r < 25 else 0xb0 + (r - 25) * 4)
		var o := teams.decode_s32(at)
		if o >= 0:
			present[r] = true
			pos[r] = char(key[o + 2])
	var lt := base + 0xbc
	for i in 0x28:
		var r: int = teams[lt + i]
		if r >= 28 or present.has(r):
			continue
		var want: Array
		if i < 12:
			want = [["L", "C", "R"][i % 3]]
		elif i < 18:
			want = ["D"]
		elif i < 0x24 or i >= 0x26:
			want = ["C", "L", "R", "D"]
		else:
			want = ["G"]
		var used := {}
		for j in 0x28:
			used[teams[lt + j]] = true
		var pick := -1
		for cand in present.keys():
			if want.has(pos[cand]) and not used.has(cand):
				pick = cand
				break
		if pick < 0:
			for cand in present.keys():
				if want.has(pos[cand]):
					pick = cand
					break
		teams[lt + i] = pick if pick >= 0 else 0x64

func _repair_all_lines() -> void:
	for t in 26:
		_repair_lines(t)

## create_player_menu / create_player_form: a new free agent: names, number, position; the
## ratings of an average player, empty statistics
func _create_player() -> void:
	var first := await fe.text_entry_dialog("First name of the new player", 15)
	if first == "":
		return
	var last := await fe.text_entry_dialog("Last name of the new player", 15)
	if last == "":
		return
	var num := await fe.text_entry_dialog("Jersey number", 2)
	var pos := (await fe.text_entry_dialog("Position (C, L, R, D or G)", 1)).to_upper()
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
	for c in 2:
		if column[c] == 0xff:
			_build(c)

## Find Player ...: the roster of the team of a player found by his last name
func _find_player(c: int) -> void:
	var name := (await fe.text_entry_dialog("Last name of the player to find", 15)).to_lower()
	if name == "":
		return
	var key: PackedByteArray = files["KEY"]
	for off in range(0, key.size() - 0x33, 0x34):
		if Database.cstring(key, off + 0x13, 16).to_lower().begins_with(name):
			var team: int = key[off]
			if team != 0xff and team >= 26:
				continue
			column[c] = team
			_build(c)
			for i in rows[c].size():
				if rows[c][i][2] == off:
					selected[c][i] = true
					if team == 0xff:
						scroll = maxi(i - 5, 0)
			return
	await fe.message_dialog(["No player of that name was found."])

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
	_build(0)
	_build(1)
