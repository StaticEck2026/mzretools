class_name LineEditor
extends RefCounted
## The line editor (edit_lines_screen_b 0x767d0 -> draw_lines_screen 0x78500, edit_lines_keys 0x77ff5,
## edit_lines_screen2 0x76af5): the 40 places of a team's line table as shirts with the jersey
## number (four forward lines of three, three defence pairs, two power play units of five, two
## penalty killing units of four, two goaltenders, two extra attackers) and the roster on the right
## (L, C, R, D, G, by last name; "%c %2d %s"). A click on a player picks him (the dressed ones; before
## the game also the scratched ones), a click on a place puts him there when his position fits (a
## forward in a forward line, a defenceman in a pair, a goaltender in the net, any skater in the
## special units); he leaves the other places of that line. A line with an empty place cannot be
## used. The menu: Use These Lines, Use Original Lines, Use Default Lines (TEAMS.DB), Save As Default
## Lines, Cancel; Dress Player / Scratch Player; Show Player Statistics.
##
## The working copy holds jersey numbers like the original (100 = empty, 'd'); the line table of the
## team holds roster indices (0..27) and, before the game, the scratched players in its last 8 bytes.

var fe: FrontEnd
var scr: Screen8
var ui: Ui

const EMPTY := 100
const SLOT_W := 0x3a
const SLOT_H := 0x28

var team_side := 0                 # 0 home, 1 visitors
var team_id := 0
var info: Database.TeamInfo
var work := PackedByteArray()      # acStack_124: 40 jersey numbers
var original := PackedByteArray()  # the line table at the start (unk_dbd1c)
# TEAMS.DB the default lines are saved to (the installation's; the Central Registry its own)
var teams_read: Callable = func() -> PackedByteArray: return GameFiles.read_raw("teams.db")
var teams_write: Callable = func(b: PackedByteArray) -> void:
	GameFiles.write_data("teams.db", b)
	fe.db = Database.open(b, GameFiles.read_raw("key.db"), GameFiles.read_raw("att.db"))
var state := PackedByteArray()     # rosters[team][r]: 0 empty, 1 injured, 2 scratched, 3 dressed
var entries: Array = []            # lineup_entries: [pos, number, roster, name] sorted
var picked := -1                   # local_60: the entry picked in the list
var pre_game := true               # _period_num < 0
var result := false                # the lines were taken
var slots: Array = []              # the places: [x, y]
var font_lines: Vfn
var registry_list: Array = []      # the Central Registry's editor (edit_lines_screen 0x73a18): its list (unk_ea990)
var registry_files: Dictionary = {}   # and its databases (KEY, CAREER, TEAMS)

func _init(f: FrontEnd) -> void:
	fe = f
	scr = f.scr
	ui = f.ui
	font_lines = f.fonts.get("linedit", f.font_main)
	for a in [[0xd1338, 12], [0xd1398, 6], [0xd13c8, 10], [0xd1418, 8], [0xd1458, 2], [0xd1468, 2]]:
		for i in a[1]:
			slots.append([Exe.i32(a[0] + i * 8), Exe.i32(a[0] + i * 8 + 4)])

## the line table of a team as the game has it: the match's (pause screen) or the session's
static func team_lines(side: int, t_info: Database.TeamInfo) -> PackedByteArray:
	if Session.line_override.has(side) and Session.line_override[side].size() >= 0x30:
		return Session.line_override[side]
	return t_info.line_table if t_info != null else PackedByteArray()

## edit_lines_screen_b: the editor for the home (0) or visiting (1) team; true when lines were taken
func edit(side: int, menu_addr: int, menu_count: int, match_team: Team = null) -> bool:
	team_side = side
	team_id = Session.home_team if side == 0 else Session.away_team
	pre_game = match_team == null
	info = match_team.info if match_team != null else fe.db.load_team(team_id)
	if info == null:
		return false
	var lt := info.line_table if match_team != null else team_lines(side, info)
	original = lt.duplicate()
	_load_states(lt, match_team)
	_load_entries()
	work.resize(0x28)
	for i in 0x28:
		var r := lt[i] if i < lt.size() else EMPTY
		work[i] = EMPTY if r == EMPTY or r >= 28 or state[r] == 0 else _number_of(r)
	await fe.leave_screen(50)
	await fe.loading_screen()
	_draw_screen(menu_addr, menu_count)
	_update_menu()
	picked = -1
	result = false
	# (Dress / Scratch Player only once a player is picked)
	for a in [0xcf28f, 0xcf2af, 0xd0558, 0xd0578]:
		Menus.at(a).cb = ""
	await scr.fade_in(_palette(), 16)
	var root := Menus.list(menu_addr, menu_count)
	var handler := func(cb: String):
		return await _callback(cb)
	await ui.run_menu(root, 0xc0, 0xc1, 0xc2, handler, Callable(), [1], Callable(), _click)
	await scr.fade_out(16)
	fe.loading_shown = false
	return result

func _load_states(lt: PackedByteArray, match_team: Team) -> void:
	state.resize(28)
	for r in 28:
		state[r] = 3 if info.player(r) != null else 0
	if match_team != null:
		for r in 28:
			if state[r] != 0 and match_team.entity_of[r] == -3:
				state[r] = 1
	elif lt.size() >= 0x30:
		for k in 8:
			var r := lt[0x28 + k]
			if r < 28 and state[r] != 0:
				state[r] = 2
	if Session.scratches.has(team_side) and match_team == null and registry_list.is_empty():
		for r in Session.scratches[team_side]:
			if state[r] != 0:
				state[r] = 2

func _number_of(r: int) -> int:
	var p := info.player(r)
	return p.number if p != null else EMPTY

func _roster_of(number: int) -> int:
	for r in 28:
		if state[r] != 0 and info.player(r) != null and info.player(r).number == number:
			return r
	return -1

## edit_lines_keys: the 28 entries of the roster (an empty slot without a position), sorted by
## qsort with cmp_player_names_b; the empty ones, last, are left out
func _load_entries() -> void:
	entries.clear()
	if not registry_list.is_empty():
		# the registry's list as it is (sorted by cmp_key_names, the empty places last)
		for e: Array in registry_list:
			if e[0] != "":
				entries.append([e[0], e[1], e[2], e[3], e[4]])
		return
	var all := []
	for r in 28:
		var p := info.player(r)
		if p == null:
			all.append(["", EMPTY, r, "", ""])
			continue
		all.append([p.position, p.number, r, "%s. %s" % [p.first.left(1), p.last], p.last])
	Clib.qsort(all, NameSort.cmp_player_names_b, 0x16)
	for e: Array in all:
		if e[0] != "":
			entries.append(e)

## EMBPAL with the team's colours in 0x80..0xff (load_homepals) and the LELOGO colours
func _palette() -> PackedByteArray:
	var b := fe.bank("embpal")
	var pal := Screen8.shape_palette(b.find("!pal")) if b != null else FrontEnd._grey_palette()
	var logo := fe.bank("lelogo")
	if logo != null:
		var lp := Screen8.shape_palette(logo.find("!pal"))
		for i in 0x93:
			pal[0x25e + i] = lp[0x25e + i]
	return pal

## draw_lines_screen (0x78500)
func _draw_screen(menu_addr: int, menu_count: int) -> void:
	scr.clearclip()
	scr.clear(0)
	var abbrev := info.abbrev
	var bg := fe.bank("emb" + abbrev)
	if bg == null:
		bg = fe.bank("embnhl")
	if bg != null:
		var s := bg.find("bkgd")
		if s != null:
			scr.drawshape_remap(s, -0x4c, 0)
	ui.draw_menu_items(Menus.list(menu_addr, menu_count), 0xc0, 0xc1, 0xc2)
	fe.set_dialog_colors(0xc1, 0xc0, 0xc2, 0xc0, 0xc1)
	scr.setfont(fe.font_main)
	scr.settextcolor(0xc0, 0xc1)
	_bevel(500, 0x13, 0x27f, 0x1df)
	var logo := fe.bank("lelogo")
	if logo != null:
		scr.drawshape_remap(logo.find(Exe.str_ptr(GameScreens.LOGO_NAMES + team_id * 4)), 0x218, 0x191)
	var boxes := [[5, 0x2c, 0x45, 0x54, "Forward", 0xc, 0x33, "Line 1", 0x13, 0x40], [5, 0x5d, 0x45, 0x85, "Forward", 0xc, 100, "Line 2", 0x13, 0x71],
		[5, 0x8e, 0x45, 0xb6, "Forward", 0xc, 0x95, "Line 3", 0x13, 0xa2], [5, 0xbf, 0x45, 0xe7, "Forward", 0xc, 0xc6, "Line 4", 0x13, 0xd3],
		[5, 0xfa, 0x45, 0x122, "Power", 0x10, 0x101, "Play 1", 0x11, 0x10e], [5, 299, 0x45, 0x153, "Power", 0x10, 0x132, "Play 2", 0x11, 0x13f],
		[5, 0x166, 0x45, 0x18e, "Penalty", 0xc, 0x16d, "Kill 1", 0x13, 0x17a], [5, 0x197, 0x45, 0x1bf, "Penalty", 0xc, 0x19e, "Kill 2", 0x13, 0x1ab],
		[0x114, 0x2c, 0x154, 0x54, "Defense", 0x11b, 0x33, "Line 1", 0x120, 0x40], [0x114, 0x5d, 0x154, 0x85, "Defense", 0x11b, 100, "Line 2", 0x120, 0x71],
		[0x114, 0x8e, 0x154, 0xb6, "Defense", 0x11b, 0x95, "Line 3", 0x120, 0xa2], [0x186, 200, 0x1e4, 0xf0, "Goaltenders", 399, 0xd5, "", 0, 0],
		[0x173, 0x166, 0x1c7, 0x18e, "Extra", 0x189, 0x16d, "Attackers", 0x17d, 0x17a]]
	for bx in boxes:
		_bevel(bx[0], bx[1], bx[2], bx[3])
		scr.printstr_at(bx[4], bx[5], bx[6])
		if bx[7] != "":
			scr.printstr_at(bx[7], bx[8], bx[9])
	_draw_slots()
	_draw_list()

## draw_bevel_box_b (0x78be7): the line editor's bevel box with the corner dots
func _bevel(x0: int, y0: int, x1: int, y1: int) -> void:
	fe.draw_bevel_box(x0, y0, x1, y1, true)

## the shirt of a place (LINEDITP "shrt" of the CD: here a frame) with the jersey number
func _draw_slot(i: int) -> void:
	var x: int = slots[i][0]
	var y: int = slots[i][1]
	scr.fillrect(x, y, SLOT_W - 4, SLOT_H - 4, 0xc1)
	scr.drawline(x, y, x + SLOT_W - 5, y, 0xc0)
	scr.drawline(x, y, x, y + SLOT_H - 5, 0xc0)
	scr.drawline(x + SLOT_W - 5, y, x + SLOT_W - 5, y + SLOT_H - 5, 0xc2)
	scr.drawline(x, y + SLOT_H - 5, x + SLOT_W - 5, y + SLOT_H - 5, 0xc2)
	var n := work[i]
	if n == EMPTY:
		return
	scr.setfont(font_lines)
	scr.settextcolor(0xc0, 0xff)
	var t := str(n)
	scr.printstr_at(t, x + (SLOT_W - 4 - scr.textwidth(t)) / 2, y + (SLOT_H - 4 - scr.font_height()) / 2)
	scr.setfont(fe.font_main)

func _draw_slots() -> void:
	for i in 0x28:
		_draw_slot(i)

## lines_draw_list: the roster in the colours of the states (dressed 0xc3, scratched before the
## game 0xfc, the others 0xc2), the picked one in 0xc0 (scratched 0xfd)
func _draw_list() -> void:
	scr.setfont(fe.font_main)
	for k in entries.size():
		var e: Array = entries[k]
		var st := state[e[2]]
		var col := 0xc2
		if st == 3 or st == 4:
			col = 0xc3
		elif st == 2 and pre_game:
			col = 0xfc
		if k == picked:
			col = 0xfd if st == 2 else 0xc0
		_print_field(0x1fa, k * 0xd + 0x16, "%s %2d %s" % [e[0], e[1], e[3]], col)

## print_field (0x76771): the text over the cell colour, cut to the panel
func _print_field(x: int, y: int, t: String, col: int) -> void:
	scr.fillrect(x, y, 0x27e - x, 0xd, 0xc1)
	scr.settextcolor(col, 0xff)
	while t.length() > 0 and scr.textwidth(t) > 0x27c - x:
		t = t.left(t.length() - 1)
	scr.printstr_at(t, x, y)

## lines_slot_at (0x77f6f): a place (0..39) or a list entry (100 + k)
func _slot_at(x: int, y: int) -> int:
	x += 4
	if x < 500:
		for i in 0x28:
			var sx: int = slots[i][0]
			var sy: int = slots[i][1]
			if x >= sx and x < sx + SLOT_W and y >= sy and y < sy + SLOT_H:
				return i
	elif y > 0x15 and y < 0x182:
		return (y - 0x16) / 0xd + 100
	return -1

## a click that is not on the menus (edit_lines_screen2)
func _click(e: Dictionary) -> void:
	var s := _slot_at(e["x"], e["y"])
	if s < 0:
		return
	if s >= 100:
		var k := s - 100
		if k >= entries.size():
			return
		var st := state[entries[k][2]]
		if st == 3 or st == 4 or (st == 2 and pre_game):
			picked = k
			_draw_list()
			if registry_list.is_empty():
				Menus.at(0xcf28f).cb = "lines_dress_player_b"
				Menus.at(0xcf2af).cb = "lines_scratch_player_b"
			else:
				Menus.at(0xd0558).cb = "lines_dress_player"
				Menus.at(0xd0578).cb = "lines_scratch_player"
		return
	if picked < 0 or state[entries[picked][2]] == 2:
		return
	var pos: String = entries[picked][0]
	var num: int = entries[picked][1]
	var first := 0
	var size := 0
	if s < 0xc:
		if not pos in ["C", "L", "R"]:
			return
		first = (s / 3) * 3
		size = 3
	elif s < 0x12:
		if pos != "D":
			return
		first = 0xc + ((s - 0xc) / 2) * 2
		size = 2
	elif s < 0x1c:
		if pos == "G":
			return
		first = 0x12 + ((s - 0x12) / 5) * 5
		size = 5
	elif s < 0x24:
		if pos == "G":
			return
		first = 0x1c + ((s - 0x1c) / 4) * 4
		size = 4
	elif s < 0x26:
		if pos != "G":
			return
		first = 0x24
		size = 2
	else:
		if pos == "G":
			return
		first = 0x26
		size = 2
	for i in range(first, first + size):
		if work[i] == num:
			work[i] = EMPTY
	work[s] = num
	for i in range(first, first + size):
		_draw_slot(i)
	_update_menu()

## the entries that take the lines are only there when every place is filled
func _update_menu() -> void:
	var full := not work.has(EMPTY)
	for a in [0xcf20f, 0xcf34f]:
		Menus.at(a).cb = "lines_use_these" if full else ""
	for a in [0xcf26f, 0xcf3af]:
		Menus.at(a).cb = "lines_teams_a" if full else ""

## the working copy as a line table (lines_use_these): roster indices, before the game the
## scratched players in the last 8 bytes
func _table() -> PackedByteArray:
	var lt := original.duplicate()
	lt.resize(0x30)
	for i in 0x28:
		var r := _roster_of(work[i]) if work[i] != EMPTY else -1
		lt[i] = r if r >= 0 else EMPTY
	if pre_game:
		for k in 8:
			lt[0x28 + k] = EMPTY
		var n := 0
		for r in 28:
			if state[r] != 0 and state[r] != 3 and n < 8:
				lt[0x28 + n] = r
				n += 1
	return lt

## roster_dress_table: a roster has to dress enough players
func _dressed_ok() -> bool:
	var skaters := 0
	var goalies := 0
	for r in 28:
		if state[r] == 3 or state[r] == 4:
			if r >= 25:
				goalies += 1
			else:
				skaters += 1
	if skaters < 12 or goalies < 1:
		await fe.message_dialog(["Your Roster is incomplete."], ["OK"])
		return false
	return true

func _callback(cb: String):
	match cb:
		"lines_use_these":
			if not await _dressed_ok():
				return 0
			_apply(_table())
			result = true
			return 1
		"lines_cancel":
			return 1
		"roster_dress_done":
			if not await _roster_dress_screen():
				return 0
			_registry_done()
			result = true
			return 1
		"lines_use_original", "lines_use_default":
			var lt := original if cb == "lines_use_original" else fe.db.load_team(team_id).line_table
			_load_states(lt, null if pre_game else fe.game.sim.teams[team_side])
			for i in 0x28:
				var r := lt[i] if i < lt.size() else EMPTY
				work[i] = EMPTY if r >= 28 or state[r] == 0 else _number_of(r)
			picked = -1
			_draw_slots()
			_draw_list()
			_update_menu()
			return 0
		"lines_teams_a", "lines_teams_b":
			if not await _dressed_ok():
				return 0
			var lt := _table()
			var teams: PackedByteArray = teams_read.call()
			var at := team_id * 0x2e8 + 0xbc
			if teams.size() >= at + 0x30:
				for i in 0x30:
					teams[at + i] = lt[i]
				teams_write.call(teams)
			original = lt.duplicate()
			return 0
		"lines_dress_player_b", "lines_dress_player":
			if picked >= 0:
				state[entries[picked][2]] = 3
				_draw_list()
			return 0
		"lines_scratch_player_b", "lines_scratch_player":
			if picked >= 0:
				var num: int = entries[picked][1]
				for i in 0x28:
					if work[i] == num:
						work[i] = EMPTY
				state[entries[picked][2]] = 2
				_draw_slots()
				_draw_list()
				_update_menu()
			return 0
		"roster_screen":
			await _roster_screen()
			return 0
		"roster_stats_table":
			var keep := scr.snapshot()
			var pal := scr.getpalette()
			await scr.fade_out(16)
			fe.stats.player_stats_screen(team_id)
			await scr.fade_in(fe.stats.stats_palette(), 16)
			await ui.wait_click()
			await scr.fade_out(16)
			scr.restore(keep)
			await scr.fade_in(pal, 16)
			return 0
	return await fe.dispatch(cb)

## roster_dress_screen (0x751fe): the registry's team has to dress 18 skaters and 2 goaltenders:
## "Your Roster is incomplete." and "Dress / Scratch %2d Player(s)." / "... Goalie(s)."
func _roster_dress_screen() -> bool:
	var skaters := 0
	var goalies := 0
	for e: Array in entries:
		if state[e[2]] == 3:
			if e[0] == "G":
				goalies += 1
			else:
				skaters += 1
	if skaters == 18 and goalies == 2:
		return true
	var line := func(n: int, want: int, what: String) -> String:
		var d := want - n if n < want else n - want
		return "%s %2d %s%s" % ["Dress" if n < want else "Scratch", d, what, "." if d == 1 else "s."]
	var lines := ["Your Roster is incomplete."]
	if skaters != 18:
		lines.append(line.call(skaters, 18, "Player"))
	if goalies != 2:
		lines.append(line.call(goalies, 2, "Goalie"))
	await fe.message_dialog(lines)
	return false

## roster_dress_done (0x75456): the places as roster slots (the dressed entry with the number), the
## scratched ones in the list's order in the last 8 bytes; the 0x30 bytes go to the team's TEAMS.DB
## record at +0xbc and are copied to +0xec
func _registry_done() -> void:
	var lt := PackedByteArray()
	lt.resize(0x30)
	lt.fill(EMPTY)
	for i in 0x28:
		if work[i] == EMPTY:
			continue
		for e: Array in entries:
			if state[e[2]] != 0 and e[1] == work[i]:
				lt[i] = e[2]
				break
	var n := 0
	for e: Array in entries:
		if state[e[2]] != 0 and state[e[2]] != 3 and n < 8:
			lt[0x28 + n] = e[2]
			n += 1
	var teams: PackedByteArray = teams_read.call()
	var at := team_id * 0x2e8 + 0xbc
	if teams.size() >= at + 0x60:
		for i in 0x30:
			teams[at + i] = lt[i]
			teams[at + 0x30 + i] = lt[i]
		teams_write.call(teams)

## roster_screen (0x7556e): the registry's roster table (Player Statistics: Return To Line Editor;
## Display ...: Regular Season / Play-Off Statistics), then the editor drawn again
func _roster_screen() -> void:
	var keep := scr.snapshot()
	_roster_table()
	var handler := func(cb: String) -> int:
		match cb:
			"menu_return_one":
				return 1
			"roster_regular_season_stats", "roster_playoff_stats":
				Session.stats_playoffs = cb == "roster_playoff_stats"
				_roster_table()
		return 0
	await ui.run_menu(Menus.list(0xd075e, 2), 0xc0, 0xc1, 0xc2, handler)
	scr.restore(keep)

static func _u16(b: PackedByteArray, at: int) -> int:
	return b.decode_u16(at)

## cmp_roster_skaters (0x75931): the ones with games first, by points, fewer games, goals, plus / minus
static func cmp_roster_skaters(a: Array, b: Array) -> int:
	var ra: PackedByteArray = a[1]
	var rb: PackedByteArray = b[1]
	if (_u16(rb, 0) == 0) != (_u16(ra, 0) == 0):
		return _u16(rb, 0) - _u16(ra, 0)
	if _u16(rb, 6) != _u16(ra, 6):
		return _u16(rb, 6) - _u16(ra, 6)
	if _u16(ra, 0) != _u16(rb, 0):
		return _u16(ra, 0) - _u16(rb, 0)
	if _u16(rb, 2) != _u16(ra, 2):
		return _u16(rb, 2) - _u16(ra, 2)
	return rb.decode_s16(0x10) - ra.decode_s16(0x10)

## cmp_roster_goalies (0x75a37): the ones with minutes first, by goals against average, minutes,
## games, fewer goals against, wins, fewer losses, save percentage
static func cmp_roster_goalies(a: Array, b: Array) -> int:
	var ra: PackedByteArray = a[1]
	var rb: PackedByteArray = b[1]
	if (_u16(rb, 0xc) == 0) != (_u16(ra, 0xc) == 0):
		return _u16(rb, 0xc) - _u16(ra, 0xc)
	if _u16(rb, 0x10) != _u16(ra, 0x10):
		return _u16(ra, 0x10) - _u16(rb, 0x10)
	if _u16(rb, 0xc) != _u16(ra, 0xc):
		return _u16(rb, 0xc) - _u16(ra, 0xc)
	if _u16(rb, 0) != _u16(ra, 0):
		return _u16(rb, 0) - _u16(ra, 0)
	if _u16(rb, 0xe) != _u16(ra, 0xe):
		return _u16(ra, 0xe) - _u16(rb, 0xe)
	if _u16(rb, 2) != _u16(ra, 2):
		return _u16(rb, 2) - _u16(ra, 2)
	if _u16(rb, 4) != _u16(ra, 4):
		return _u16(ra, 4) - _u16(rb, 4)
	return _u16(rb, 0x14) - _u16(ra, 0x14)

## roster_table (0x75bf7): the team's skaters (places 0..24) and goaltenders (25..27) with their
## CAREER.DB statistics (the play-offs' from +0x12 / +0x16 with stats_playoffs), sorted by
## cmp_roster_skaters / cmp_roster_goalies, over the team's EMB "bkgd"
func _roster_table() -> void:
	var teams: PackedByteArray = registry_files["TEAMS"]
	var key: PackedByteArray = registry_files["KEY"]
	var career: PackedByteArray = registry_files["CAREER"]
	var rec := team_id * 0x2e8
	var rows: Array = [[], []]
	for s in 28:
		var off := teams.decode_s32(rec + 0x4c + s * 4)
		if off == -1:
			continue
		var g := 1 if s >= 25 else 0
		var k := key.slice(off, off + 0x34)
		var c := k.decode_s32(0x28)
		var blk := ((0x16 if g else 0x12) if Session.stats_playoffs else 0)
		rows[g].append([k, career.slice(c + blk, c + (0x2c if g else 0x28))])
	Clib.qsort(rows[0], cmp_roster_skaters)
	Clib.qsort(rows[1], cmp_roster_goalies)
	scr.clearclip()
	var b := fe.bank("emb" + Database.cstring(teams, rec, 5))
	if b == null:
		b = fe.bank("embnhl")         # (the teams' EMB banks are on the CD only)
	if b != null:
		scr.setclip(0, 0x13, 0x280, 0x1e0)
		var bk := b.find("bkgd")
		scr.drawshape_remap(bk, bk.x, bk.y)
		scr.clearclip()
	scr.setfont(fe.font_main)
	ui.draw_menu_items(Menus.list(0xd075e, 2), 0xc0, 0xc1, 0xc2)
	scr.set_text_colors(0xc0, 0xc3)
	var p := func(x: int, y: int, t: String) -> void:
		scr.print_text_at(x, y, t)
	scr.print_centered_shadow(0x19, "%s Roster:" % Database.cstring(teams, rec + 5, 0x20))
	for h in [[0x14, "Pos"], [0x42, "No"], [0x60, "Name"], [0x10e, "GP"], [0x136, "  G"], [0x15e, "  A"], [0x186, " PT"], [0x1ae, "Shots"], [0x1e8, "PIM"], [0x210, " +/-"]]:
		p.call(h[0], 0x30, h[1])
	var y := 0x40
	for row: Array in rows[0]:
		var k: PackedByteArray = row[0]
		var r: PackedByteArray = row[1]
		p.call(0x14, y, char(k[2]))
		if k[1] < 0x64:
			p.call(0x42, y, "%2d" % k[1])
		p.call(0x60, y, fe.stats.format_name(Database.cstring(k, 3, 16), Database.cstring(k, 0x13, 17), 0xa6))
		p.call(0x10e, y, "%2d" % _u16(r, 0))
		p.call(0x136, y, "%3d" % _u16(r, 2))
		p.call(0x15e, y, "%3d" % _u16(r, 4))
		p.call(0x186, y, "%3d" % _u16(r, 6))
		p.call(0x1ae, y, "%4d" % _u16(r, 0xe))
		p.call(0x1e8, y, "%3d" % _u16(r, 0xc))
		p.call(0x210, y, "%4d" % r.decode_s16(0x10))
		y += 0xd
	y = 0x195
	for h in [[0x14, "Pos"], [0x42, "No"], [0x60, "Name"], [0x10e, "GP"], [0x136, " Min"], [0x15e, "  GAA"], [0x190, " W"], [0x1ae, " L"], [0x1ea, " GA"], [0x20e, "  SA"], [0x240, "  PCT"]]:
		p.call(h[0], y, h[1])
	if not Session.stats_playoffs:
		p.call(0x1cc, y, " T")
	y += 0x10
	for row: Array in rows[1]:
		var k: PackedByteArray = row[0]
		var r: PackedByteArray = row[1]
		p.call(0x14, y, char(k[2]))
		if k[1] < 0x64:
			p.call(0x42, y, "%2d" % k[1])
		p.call(0x60, y, fe.stats.format_name(Database.cstring(k, 3, 16), Database.cstring(k, 0x13, 17), 0xa6))
		p.call(0x10e, y, "%2d" % _u16(r, 0))
		p.call(0x136, y, "%4d" % _u16(r, 0xc))
		p.call(0x15e, y, "%2d.%02d" % [_u16(r, 0x10) / 100, _u16(r, 0x10) % 100])
		p.call(0x190, y, "%2d" % _u16(r, 2))
		p.call(0x1ae, y, "%2d" % _u16(r, 4))
		if not Session.stats_playoffs:
			p.call(0x1cc, y, "%2d" % _u16(r, 6))
		p.call(0x1ea, y, "%3d" % _u16(r, 0xe))
		p.call(0x20e, y, "%4d" % _u16(r, 0x12))
		p.call(0x240, y, "%3d.%1d" % [_u16(r, 0x14) / 10, _u16(r, 0x14) % 10])
		y += 0xd

## the lines go to the match (the team's line table) or to the next game of the session
func _apply(lt: PackedByteArray) -> void:
	var m: Node = fe.game
	if m != null and not pre_game:
		var team: Team = m.sim.teams[team_side]
		team.info.line_table = lt
		# (a scratched player's place as team_energy_init gives it from his status byte)
		for r in 28:
			if state[r] == 2 and team.entity_of[r] == -2:
				team.entity_of[r] = MatchSetup.STATUS_ENTITY_OF[2]
				team.roster_status[r] = 2
			elif state[r] == 3 and team.entity_of[r] == MatchSetup.STATUS_ENTITY_OF[2]:
				team.entity_of[r] = -2
				team.roster_status[r] = 3
	else:
		Session.line_override[team_side] = lt
		var sc: Array = []
		for r in 28:
			if state[r] == 2:
				sc.append(r)
		Session.scratches[team_side] = sc
