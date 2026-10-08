class_name LeagueScreens
extends RefCounted
## The league screens of the front end: New League (new_league_mode 0x32ff4, new_league_dialog
## 0x44dcf), the team grid of the human teams (team_info_screen 0x38b4f, team_grid_draw,
## team_grid_highlight), Open (league_select_screen 0x2b944), Next League Game (league_calendar_screen
## 0x33559, league_calendar_flow 0x36b93) with the calendar (calendar_screen 0x34821,
## calendar_draw_games 0x33ffd) and the League Manager entries. The games and their statistics are
## sim/League.gd.
##
## The calendar's pictures (CALENDAR.QFS) and the small logos (CALLOGO.QFS) are on the CD only: the
## calendar is drawn from its layout tables over EMBNHL.QFS, the logos of SRLOGO.QFS stand in at
## half size with their colours matched to the screen's palette.

var fe: FrontEnd
var scr: Screen8
var ui: Ui

const CELL_X := 0xc895e              # dword_c895e: the x of the 7 week days
const CELL_Y := 0xc897a              # dword_c897a: the y of the 6 weeks
const MONTH_LENGTH := 0xc8445        # unk_c8445: days of the months January .. December
const FIRST_WEEKDAY := 0xc845e       # unk_c845e: the week day of the 1st of the month (the season's year)
const LOGO_NAMES := 0xc57cc
const TEAM_NAMES := 0xc54a9          # off_c54a9: city names

func _init(f: FrontEnd) -> void:
	fe = f
	scr = f.scr
	ui = f.ui

# ---------------------------------------------------------------------------------------------
# helpers: the files of a new league, the stand-in logos, the menus of an open league
# ---------------------------------------------------------------------------------------------

## the seven databases of the installation (.DB) or the original ones (.ORG, choose_db_or_org)
static func sources(use_org: bool) -> Dictionary:
	var out := {}
	for n in League.FILES:
		var d := GameFiles.read_raw(n.to_lower() + (".org" if use_org else ".db"))
		if d.is_empty():
			d = GameFiles.read_raw(n.to_lower() + ".db")
		out[n] = d
	return out

var _logos: Shpi
var _logo_pal := PackedByteArray()
var _remaps := {}

## the logo of a team at half size, its colours matched to the palette `pal` of the screen
func small_logo(team: int, x: int, y: int, pal: PackedByteArray, centered := false) -> void:
	if _logos == null:
		_logos = fe.bank("srlogo")
		var arena := fe.bank("arena")
		_logo_pal = Screen8.shape_palette(arena.find("!pal")) if arena != null else FrontEnd._grey_palette()
	if _logos == null or team < 0 or team > 27:
		return
	var key := pal.hex_encode().md5_text()
	if not _remaps.has(key):
		# the colours of the screen's pictures (the low indices), not the menu colours at the top
		_remaps[key] = Screen8.palette_map(_logo_pal, pal, 0, 0xf0)
	var s := _logos.find(Exe.str_ptr(LOGO_NAMES + team * 4))
	if s == null:
		return
	if centered:
		x -= s.width / 4
		y -= s.height / 4
	scr.drawshape_scaled(s, x, y, _remaps[key], 2)

static func team_name(t: int) -> String:
	var teams := GameFiles.read_raw("teams.db")
	if Session.league != null:
		teams = (Session.league as League).file("TEAMS")
	return Database.cstring(teams, t * 0x2e8 + 0x1a, 13)

static func team_full_name(t: int) -> String:
	if t == 0x18:
		return "Mighty Ducks of Anaheim"
	var teams := GameFiles.read_raw("teams.db")
	return Database.cstring(teams, t * 0x2e8 + 5, 21)

## set_menu_mode / new_league_mode: the File menu of an open league (Export Databases ...,
## Next League Game ..., the League Manager) and the league's name in the statistics menu
func activate_league_menus(on: bool) -> void:
	Menus.at(0xce4cf).cb = "league_select_team" if on else ""
	Menus.at(0xce4ef).cb = "league_calendar_screen" if on else ""
	var mgr := Menus.at(0xce50f)
	mgr.sub = 0xce64f if on else 0
	mgr.n = 13 if on else 0
	var l: League = Session.league
	var nm := l.name if l != null else "WWWWWWWW"
	# set_league_menu_titles: " "NAME" Season", " "NAME" Season Play-Offs"
	Menus.at(0xc6811).text = ' "%s" Season' % nm
	Menus.at(0xc6831).text = ' "%s" Season Play-Offs' % nm
	Menus.at(0xc6811).cb = "stats_source_league_season" if on else ""
	Menus.at(0xc6831).cb = "stats_source_league_season_playoffs" if on else ""

func open_league(l: League) -> void:
	Session.league = l
	Session.league_dir = l.name + ".LP"
	Session.league_name = l.name
	Session.stats_dir = l.dir
	activate_league_menus(true)

# ---------------------------------------------------------------------------------------------
# New League ...
# ---------------------------------------------------------------------------------------------

## new_league_mode (0x32ff4) and new_league_dialog (0x44dcf): the name, the schedule ('93 - '94 or
## random), the databases (current or original), the human teams with their names and passwords,
## the league's settings; then the files are written and the league is open
func new_league_mode() -> int:
	# new_league_mode: settings_league's defaults applied (Rangers - Canucks, every option, 0x7800 the
	# play-off series of 7, the first controller found for player 1 with the Rangers) for the whole
	# dialog (the grid's League settings change them), set_settings_context(0); the exhibition's back
	# at the end
	var keep := Session.save_block()
	Session.mode = 2
	Session.home_team = 12
	Session.away_team = 21
	Session.option_flags = (Session.option_flags | (0x3ff if Session.sound_enabled else 0x2ff)) & 0x83ff | 0x7800
	Session.p1_device = 0x10
	for d in [2, 4, 8, 1]:
		if Session.input_devices & d:
			Session.p1_device = d
			break
	Session.p1_team = 12 if Session.p1_device != 0x10 else -1
	Session.p2_device = 0x10
	Session.p2_team = -2
	Session.p1_side = 0
	Session.p2_side = 1
	fe.settings.context = 0
	var l := await _new_league_dialog()
	Session.apply_block(keep)
	if l != null:
		open_league(l)
	fe.set_dialog_colors(0xf9, 0xfa, 0xf8, 0xfa, 0)
	return 2

## new_league_dialog (0x44dcf): the name, an old league of the name replaced at once, the schedule,
## the databases, the grid; the league made with the settings of the session
func _new_league_dialog() -> League:
	fe.set_dialog_colors(0xf9, 0xfa, 0xf8, 0xfa, 0)
	var name := (await fe.text_entry_dialog("Enter New League Name", 8, 0x30, 5)).to_upper()
	if name == "" or fe.entry_key == 0x1b:
		return null
	if League.list_leagues().has(name):
		var r := await fe.message_dialog_buttons(["There is already a league with that name!",
			"Do you want to replace it with a new league?"], FrontEnd.buttons_at(0xc7733, 2))
		if r != 1:
			return null
		League.delete(name)
	Session.league_dir = name + ".LP"
	Session.league_name = name
	var sched := await fe.message_dialog_buttons(["  Which schedule do you want to use?  "], FrontEnd.buttons_at(0xc77ae, 2))
	if sched < 0:
		return null
	var org := await fe.message_dialog_buttons(["Do you wish to use your", "Current database or the", "Original NHL database?"],
		FrontEnd.buttons_at(0xc74b7, 2))
	if org < 0:
		return null
	var pinfo := League.pinfo_create([])
	var chosen = await team_info_screen(1, "Select human controlled teams", pinfo)
	if chosen == null:
		return null
	var humans: Array = []
	for t in 26:
		if pinfo[0x20 + t * 0x1e + 0x17] == 1:
			humans.append(t)
	var settings := Session.save_block()
	var lines := ["Creating league."]
	await _busy(lines)
	var l := League.create(name, sources(org == 1), humans, sched == 1, settings)
	for t in 26:
		for k in 0x1e:
			l.pinfo[0x20 + t * 0x1e + k] = pinfo[0x20 + t * 0x1e + k]
	l.pinfo.encode_u16(0, humans.size())
	l.pinfo.encode_u16(2, pinfo.decode_u16(2))
	for k in 11:
		l.pinfo[0x15 + k] = pinfo[0x15 + k]
	l.save()
	fe.restore_dialog_background()
	return l

## a message without buttons while the work is done (restore_dialog_background afterwards)
func _busy(lines: Array) -> void:
	fe.message_show(lines)
	await ui.frame()
	await ui.frame()

# ---------------------------------------------------------------------------------------------
# the team grid (team_info_screen): 1 choose the human teams of a new league, 2 add one,
# 4 remove one, 8 select a human team, 0x10 two human teams
# ---------------------------------------------------------------------------------------------

var _grid := PackedByteArray()       # the 4 x 7 places of the grid (99 none)
var _grid_pal := PackedByteArray()
var _grid_back: Image = null         # team_grid_save_back: the place of a team under a dialog
var _grid_back_at := Vector2i.ZERO

## team_grid_draw's places: the logo of the place (c, r) at (c * 0x55 + 0x40, r * 0x5c + 0x58), the
## last two divisions 0x2a pixels further left
static func grid_origin(c: int, r: int) -> Vector2i:
	return Vector2i(c * 0x55 + (0x40 if r < 2 else 0x16), r * 0x5c + 0x58)

## the place [c, r] of a team in the grid, [-1, -1] none
func grid_place(team: int) -> Array:
	for r in 4:
		for c in 7:
			if _grid[r * 7 + c] == team:
				return [c, r]
	return [-1, -1]

## team_info_load_stats (0x384b8): the divisions of unk_c83c3, each in the order of its standings in
## TEAMS.DB (exchange sort): more points (2 a win, 1 a tie), fewer games, more wins, more goals for,
## fewer goals against
static func grid_by_standings(teams: PackedByteArray) -> PackedByteArray:
	var grid := Exe.bytes(League.DIVISION_TEAMS, 0x1c)
	var key := func(t: int) -> Array:
		var b := t * League.TEAM + 0x28
		return [teams[b + 1] * 2 + teams[b + 3], teams[b], teams[b + 1], teams.decode_u16(b + 4), teams.decode_u16(b + 6)]
	for r in 4:
		var n := 6 if r < 2 else 7
		for i in n - 1:
			for j in range(i + 1, n):
				var a: Array = key.call(grid[r * 7 + i])
				var b: Array = key.call(grid[r * 7 + j])
				var swap: bool = b[0] > a[0] \
					or (b[0] == a[0] and b[1] < a[1]) \
					or (b[0] == a[0] and b[1] == a[1] and b[2] > a[2]) \
					or (b[0] == a[0] and b[1] == a[1] and b[2] == a[2] and b[3] > a[3]) \
					or (b[0] == a[0] and b[1] == a[1] and b[2] == a[2] and b[3] == a[3] and b[4] < a[4])
				if swap:
					var k := grid[r * 7 + i]
					grid[r * 7 + i] = grid[r * 7 + j]
					grid[r * 7 + j] = k
	return grid

## team_grid_slot_at (0x37b9c): the team whose logo (0x47 x 0x3a from its origin) is at (x, y), -1 none
func grid_team_at(x: int, y: int) -> int:
	for r in 4:
		for c in 7:
			var p := grid_origin(c, r)
			if x >= p.x and x <= p.x + 0x46 and y >= p.y and y <= p.y + 0x39:
				var t := _grid[r * 7 + c]
				return -1 if t == 99 else t
	return -1

## team_grid_draw_name (0x37c53): the name of a team's player under its logo (the background drawn
## again under it first), in the dialog's text colours
func _grid_name(team: int, pinfo: PackedByteArray) -> void:
	var cr := grid_place(team)
	if cr[0] < 0:
		return
	var p := grid_origin(cr[0], cr[1])
	var x := p.x - 7
	var y := p.y + 0x3f
	scr.setclip(x, y, x + 0x4d, y + scr.font_height() + 1)
	var b := fe.bank("embnhl")
	if b != null:
		scr.drawshape_remap(b.find("bkgd"), 0, 0)
	scr.clearclip()
	scr.set_text_colors(fe.dlg_text, fe.dlg_shadow)
	var n := Database.cstring(pinfo, 0x20 + team * 0x1e, 11)
	scr.print_text_at(x + 0x2a - scr.textwidth(n) / 2, y, n)

## team_grid_draw (0x37fba) with the background: the title, the logos (CALLOGO of the CD: the small
## logos of SRLOGO stand in), the names of the human teams' players
func _grid_draw(title: String, pinfo: PackedByteArray) -> void:
	scr.clearclip()
	var b := fe.bank("embnhl")
	if b != null:
		scr.drawshape_remap(b.find("bkgd"), 0, 0)
	scr.setfont(fe.font_main)
	scr.set_text_colors(0x40, 0x43)
	scr.print_centered_shadow(0x28, title)
	for r in 4:
		for c in 7:
			var t := _grid[r * 7 + c]
			if t == 99:
				break
			var p := grid_origin(c, r)
			small_logo(t, p.x + 0x25, p.y + 0x18, _grid_pal, true)
			if pinfo[0x20 + t * 0x1e + 0x17] == 1:
				_grid_name(t, pinfo)

## team_grid_highlight (0x37ea6): two boxes around a logo XORed with 0x80 (`on`), or drawn in colour 0
func _grid_highlight(team: int, on: bool) -> void:
	var cr := grid_place(team)
	if cr[0] < 0:
		return
	var p := grid_origin(cr[0], cr[1])
	var boxes := [[p.x - 2, p.y - 2, p.x + 0x48, p.y + 0x3b], [p.x - 3, p.y - 3, p.x + 0x49, p.y + 0x3c]]
	for bx in boxes:
		var x0: int = bx[0]
		var y0: int = bx[1]
		var x1: int = bx[2]
		var y1: int = bx[3]
		if on:
			scr.xorrect(x0, y0, x1 - x0 + 1, 1, 0x80)
			scr.xorrect(x1, y0 + 1, 1, y1 - y0 - 1, 0x80)
			scr.xorrect(x0, y0 + 1, 1, y1 - y0 - 1, 0x80)
			scr.xorrect(x0, y1, x1 - x0 + 1, 1, 0x80)
		else:
			scr.fillrect(x0, y0, x1 - x0 + 1, 1, 0)
			scr.fillrect(x1, y0 + 1, 1, y1 - y0 - 1, 0)
			scr.fillrect(x0, y0 + 1, 1, y1 - y0 - 1, 0)
			scr.fillrect(x0, y1, x1 - x0 + 1, 1, 0)

## team_grid_save_back (0x37d6a) / team_grid_restore_back (0x37e5b): the 0x4e x 0x41 pixels of a
## team's place, kept while a dialog is over it
func _grid_save_back(team: int) -> void:
	var cr := grid_place(team)
	var p := grid_origin(cr[0], cr[1])
	_grid_back_at = Vector2i(p.x - 4, p.y - 4)
	_grid_back = scr.grab(_grid_back_at.x, _grid_back_at.y, 0x4e, 0x41)

func _grid_restore_back() -> void:
	if _grid_back != null:
		scr.put(_grid_back)
		_grid_back = null

## team_info_screen (0x38b4f): the teams by division (mode 1: unk_c83c3; else each division in the
## order of its standings, team_info_load_stats) with the names of the human teams' players under the
## logos; the menu Select (Done / Cancel) and for modes 1 and 8 Settings (League settings / Show
## League settings). A click selects a team (the first place at the start), a second click on it:
## modes 1 and 2 make a computer team human (the player's name, his password twice), mode 4 takes one
## out (more than one human team, not the controller's: "Do you really want to remove", his password),
## mode 8 chooses a human team, mode 0x10 a first human team and then a second. Done needs a human
## team (modes 1, 2, 4), the selected team human (8), both human (0x10). After Done the screen stays
## (the callers' dialogs come over it): mode 1 asks who controls the league (league_control_dialog),
## team_info_confirm sets the teams' flags, and the teams go into `pinfo` (+0 the number of human
## teams). Returns the team (mode 8), [first, second] (0x10), true (1, 2, 4), null for Cancel.
func team_info_screen(mode: int, title: String, pinfo: PackedByteArray) -> Variant:
	var count := 0 if mode == 1 else pinfo.decode_u16(0)
	if mode & 1:
		_grid = Exe.bytes(League.DIVISION_TEAMS, 0x1c)
	else:
		_grid = grid_by_standings((Session.league as League).file("TEAMS"))
	if mode == 8 and count == 1:
		var only := -1
		for t in 26:
			if pinfo[0x20 + t * 0x1e + 0x17] == 1:
				only = t
		return only
	fe.set_dialog_colors(0x41, 0x40, 0x42, 0x40, 0)
	await fe.leave_screen(100)
	var work := pinfo.duplicate()      # TPI
	var ts := fe.bank("tspal")
	_grid_pal = Screen8.shape_palette(ts.find("!pal")) if ts != null else FrontEnd._grey_palette()
	_grid_draw(title, work)
	Menus.at(0xc8798).sub = 0xc86fc if mode & 1 else (0xc86cc if mode & 8 else 0)
	var root := Menus.list(0xc8778, 2 if mode & 9 else 1)
	ui.draw_menu_items(root, 0x40, 0x41, 0x42)
	var picks := [int(_grid[0]), -1]
	var st := {"cur": 0, "count": count, "cancel": false}
	_grid_highlight(picks[0], true)
	fe.play_loop("leaguetm")
	await scr.fade_in(_grid_pal, 16)
	var handler := func(cb: String):
		match cb:
			"dialog_done":
				var cur: int = st["cur"]
				var human := func(t: int) -> bool:
					return t >= 0 and work[0x20 + t * 0x1e + 0x17] == 1
				if mode & 7 and st["count"] >= 1:
					return 1
				if mode & 8 and human.call(picks[cur]):
					return 1
				if mode & 0x10 and cur == 1 and human.call(picks[0]) and human.call(picks[1]):
					return 1
				return 0
			"dialog_cancel":
				st["cancel"] = true
				return 1
		return await fe.dispatch(cb)
	var outside := func(e: Dictionary):
		var t := grid_team_at(e["x"], e["y"])
		var cur: int = st["cur"]
		if mode == 0x10 and cur == 1 and t == picks[0]:
			t = -1
		if t < 0:
			return 0
		var was: int = picks[cur]
		picks[cur] = t
		if was != t:
			if was >= 0:
				_grid_highlight(was, true)
			_grid_highlight(t, true)
			return 0
		var e0 := 0x20 + t * 0x1e
		if mode & 0x18 and work[e0 + 0x17] == 1:
			# the chosen team keeps its box (drawn, then XORed)
			_grid_highlight(was, false)
			_grid_highlight(t, true)
			if cur == 0 and mode & 0x10:
				st["cur"] = 1
				picks[1] = -1
				return 0
			return 1
		if mode & 4:
			if st["count"] > 1 and work[e0 + 0x19] == 0 and work[e0 + 0x17] == 1:
				_grid_save_back(t)
				_grid_highlight(t, false)
				_grid_highlight(t, true)
				var name := Database.cstring(work, e0, 11)
				var r := await fe.message_dialog_buttons(["Do you really want to remove", name], FrontEnd.buttons_at(0xc7870, 2))
				if r == 0 and await _password_prompt_in(work, t):
					work[e0 + 0x17] = 0
					st["count"] -= 1
					for k in 0x16:
						work[e0 + k] = 0
					_grid_restore_back()
					_grid_name(t, work)
				else:
					_grid_restore_back()
			return 0
		if mode & 3 and work[e0 + 0x17] == 0:
			_grid_save_back(t)
			_grid_highlight(t, false)
			_grid_highlight(t, true)
			if await _make_human(t, work):
				st["count"] += 1
				_grid_restore_back()
				_grid_name(t, work)
			else:
				_grid_restore_back()
			ui.reset_events()
		return 0
	await ui.run_menu(root, 0x40, 0x41, 0x42, handler, Callable(), [1], Callable(), outside)
	ui.show_pointer(false)
	var cur: int = st["cur"]
	if st["cancel"]:
		picks[cur] = -1
		await fe.leave_screen(100)
	pinfo.encode_u16(0, st["count"])
	if picks[cur] < 0:
		return null
	if mode & 8 == 0:
		if mode & 1:
			await league_control_dialog(work, st["count"])
			for k in 0x20:
				pinfo[k] = work[k]
			pinfo.encode_u16(0, st["count"])
		_team_info_confirm(work, pinfo, mode)
		for k in 0x30c:
			pinfo[0x20 + k] = work[0x20 + k]
	if mode == 8:
		return picks[0]
	if mode == 0x10:
		return picks.duplicate()
	return true

## "Who will play the <team>?" (Esc: none), the name kept and compared with the other human teams'
## ("That name has already been used!"), then the password twice (shown as dots; Esc: none), kept
## scrambled with the team
func _make_human(t: int, pinfo: PackedByteArray) -> bool:
	var e := 0x20 + t * 0x1e
	for k in 0x16:
		pinfo[e + k] = 0
	while true:
		var name := await fe.text_entry_dialog("Who will play the %s?" % team_full_name(t), 10, 0x46, 4, true)
		if fe.entry_key == 0x1b:
			return false
		var a := name.to_ascii_buffer()
		for i in 11:
			pinfo[e + i] = a[i] if i < a.size() and i < 10 else 0
		var used := false
		for k in 26:
			if k != t and pinfo[0x20 + k * 0x1e + 0x17] == 1 and Database.cstring(pinfo, 0x20 + k * 0x1e, 11).to_lower() == name.to_lower():
				await fe.message_dialog(["That name has already been used!"])
				used = true
		if not used:
			break
	var name := Database.cstring(pinfo, e, 11)
	var pw := ""
	while true:
		pw = await fe.text_entry_dialog("Enter password for " + name, 10, 0x3c, 6)
		if fe.entry_key == 0x1b:
			return false
		var again := await fe.text_entry_dialog("Verify password for " + name, 10, 0x3c, 6)
		if fe.entry_key == 0x1b:
			return false
		if pw == again:
			break
		await fe.message_dialog(["The password was entered differently", "the second time! Try again."])
	pinfo[e + 0x17] = 1
	League.password_store(pinfo, e + 0xb, t, pw)
	return true

## team_info_confirm (0x38386): the flags of the teams (+0x16, +0x18): 1 for the computer teams; a
## human team new in the league (mode 1: one the controller's dialog left at 2, mode 2: one that was
## not human before) is asked about when there is more than one human team: "Do you want to export
## <name> to a floppy disk?", Yes making it 2 (the team plays on another computer, its databases
## carried on a disk). The disk exchange of the original is not ported: the team stays here (1).
func _team_info_confirm(work: PackedByteArray, old: PackedByteArray, mode: int) -> void:
	for t in 26:
		var e := 0x20 + t * 0x1e
		var fresh := (mode & 1 and work[e + 0x17] == 1 and work[e + 0x18] == 2) \
			or (mode & 2 and work[e + 0x17] == 1 and old[e + 0x17] == 0)
		if fresh or work[e + 0x17] == 0:
			work[e + 0x18] = 1
			work[e + 0x16] = 1

## password_prompt (0x3a395): "Enter password for <name>" (shown as dots; Esc gives up), three tries,
## "Incorrect password!" after a wrong one; true when it was right
func password_prompt(l: League, t: int) -> bool:
	return await _password_prompt_in(l.pinfo, t)

func _password_prompt_in(pinfo: PackedByteArray, t: int) -> bool:
	var e := 0x20 + t * 0x1e
	var name := Database.cstring(pinfo, e, 11)
	for k in 3:
		var pw := await fe.text_entry_dialog("Enter password for " + name, 10, 0x3c, 6)
		if fe.entry_key == 0x1b:
			return false
		if pw == League.password_text(pinfo, e + 0xb, t):
			return true
		await fe.message_dialog(["Incorrect password!"])
	return false

## master_password_prompt (0x3a49e): "<name> enter master password." for the controlling team's
## player (PINFO.DB +2), the master password (+0x15) checked as password_prompt does
func master_password_prompt(l: League) -> bool:
	var t := l.pinfo.decode_u16(2)
	var name := Database.cstring(l.pinfo, 0x20 + t * 0x1e, 11)
	for k in 3:
		var pw := await fe.text_entry_dialog(name + " enter master password.", 10, 0x3c, 6)
		if fe.entry_key == 0x1b:
			return false
		if pw == League.password_text(l.pinfo, 0x15, t):
			return true
		await fe.message_dialog(["Incorrect password!"])
	return false

## league_control_dialog (0x380e9): who controls the league (the human players by name in a list
## when there is more than one human team), his team's flags (+0x18, +0x19), the master password
## entered twice (shown as dots, no Esc) and kept scrambled with his team (+0x15); PINFO.DB +2 the
## controlling team, +4, +6 and +0x13 cleared
func league_control_dialog(pinfo: PackedByteArray, count: int) -> void:
	var teams := []
	var names := []
	for t in 26:
		var e := 0x20 + t * 0x1e
		if pinfo[e + 0x17] == 1:
			teams.append(t)
			names.append(Database.cstring(pinfo, e, 11))
	if teams.is_empty():
		return
	var k := 0
	if count > 1:
		k = await fe.listbox_dialog(names, "Who will control the league?", 0)
	var t: int = teams[k]
	var e := 0x20 + t * 0x1e
	pinfo[e + 0x18] = 1
	pinfo[e + 0x19] = 1
	pinfo.encode_u16(2, t)
	var pw := ""
	while true:
		pw = await fe.text_entry_dialog("Enter master controller password for " + names[k], 10, 0x3c, 2)
		var again := await fe.text_entry_dialog("Verify master controller password for " + names[k], 10, 0x3c, 2)
		if pw == again:
			break
		await fe.message_dialog(["The password was entered differently", "the second time! Try again."])
	League.password_store(pinfo, 0x15, t, pw)
	pinfo.encode_u16(0x13, 0)
	pinfo.encode_u16(4, 0)
	pinfo[6] = 0

# ---------------------------------------------------------------------------------------------
# Open ... (league_select_screen): the leagues of the directory
# ---------------------------------------------------------------------------------------------

func league_select_screen() -> int:
	var names := League.list_leagues()
	for n in League.list_leagues(".PO"):
		names.append(n + " (Play-Offs)")
	for n in SaveGame.list_saves():
		names.append(n + " (Saved Game)")
	if names.is_empty():
		await fe.message_dialog(["There is nothing to open."])
		return 0
	var lines: Array = ["Open which league or game?"]
	var labels: Array = []
	for n in names.slice(0, 6):
		labels.append(n)
	labels.append("Cancel")
	var list: Array = []
	var x := 16
	var y := 0x20
	for i in labels.size():
		var w := maxi(scr.textwidth(labels[i]) + 16, 80)
		if i == labels.size() - 1:
			list.append(FrontEnd.UiButton.new(-16, -8, w, 20, labels[i], 2))
		else:
			list.append(FrontEnd.UiButton.new(16, y, 160, 20, labels[i], 5))
			y += 24
	lines.append_array(["", ""])
	for i in labels.size() - 1:
		lines.append("")
	fe.set_dialog_colors(0xf9, 0xfa, 0xf8, 0xfa, 0)
	var r := await fe.message_dialog_buttons(lines, list)
	if r < 0 or r >= labels.size() - 1:
		return 0
	if labels[r].ends_with(" (Saved Game)"):
		var path := SaveGame.saves_dir().path_join(labels[r].trim_suffix(" (Saved Game)") + ".NHL")
		var data := SaveGame.read(path)
		if data.is_empty():
			await fe.message_dialog(["Error while reading the saved game!"])
			return 0
		DirAccess.remove_absolute(path)
		var keep := Session.save_block()
		await fe.games.continue_saved(data)
		Session.apply_block(keep)
		return 2
	var series: bool = labels[r].ends_with(" (Play-Offs)")
	var l := League.open(labels[r].trim_suffix(" (Play-Offs)"), ".PO" if series else ".LP")
	if l == null:
		await fe.message_dialog(["Error while reading the league!"])
		return 0
	if series:
		open_series(l)
	else:
		open_league(l)
	return 2

## Export Databases ... (league_select_team: a team's files for its player on another computer)
func league_select_team() -> int:
	await fe.message_dialog(["All human teams of this league", "play on this computer."])
	return 0

# ---------------------------------------------------------------------------------------------
# Next League Game ... (league_calendar_screen / league_calendar_flow)
# ---------------------------------------------------------------------------------------------

## the team to play (the only human team, else the grid), its password; then the calendar until
## Return: the game chosen is played and recorded, the other games of its date simulated
func league_calendar_screen() -> int:
	var l: League = Session.league
	if l == null:
		return 0
	var humans := l.humans()
	if humans.is_empty():
		await fe.message_dialog(["This league has no human teams."])
		return 2
	# league_calendar_screen: the league's settings (settings_league), set_settings_context(1): the
	# grid's Show League settings looks at them
	var keep := Session.save_block()
	if l.game_set.size() >= Session.SETTINGS_SIZE:
		Session.apply_block(l.game_set)
	Session.mode = 2
	fe.settings.context = 1
	var team: int = humans[0]
	if humans.size() > 1:
		var t = await team_info_screen(8, "Select a team to play.", l.pinfo)
		if t == null:
			Session.apply_block(keep)
			return 2
		team = t
	if not await password_prompt(l, team):
		Session.apply_block(keep)
		return 2
	Session.league_team = team
	fe.set_hub_title(2)
	await _continue_saved(l)
	while true:
		var index := await calendar_screen(team)
		if index < 0:
			break
		var rec := l.game(index)
		Session.home_team = rec[2]
		Session.away_team = rec[3]
		Session.game_number = index
		if index < League.SEASON_GAMES:
			Session.option_flags |= 0x200
		else:
			Session.option_flags &= ~0x200
		var side := 0 if rec[2] == team else 1
		Session.p1_team = team
		Session.p1_side = side
		var db := Database.open(l.file("TEAMS"), l.file("KEY"), l.file("ATT"))
		var r := await fe.games.scouting_report_screen(rec[2], rec[3])
		if r == 4:
			continue
		var played := await fe.play_game(db)
		if played == 1 and fe.last_sim != null:
			await _busy(["Updating schedule."])
			l.game_played(index, fe.last_sim)
			l.save()
			fe.stats.forget_files()
			if l.season_over:
				await awards_screen()
		fe.last_sim = null
	l.game_set = Session.save_block()
	l.save()
	Session.apply_block(keep)
	Session.mode = 0
	fe.set_hub_title(0)
	return 2

## GAME.SAV of the league (league_calendar_screen: a saved game is continued first)
func _continue_saved(l: League) -> void:
	var path := l.dir.path_join("GAME.SAV")
	if not FileAccess.file_exists(path):
		return
	var data := SaveGame.read(path)
	DirAccess.remove_absolute(path)
	if data.is_empty():
		return
	var index: int = data.get("index", -1)
	var keep := Session.save_block()
	var db := Database.open(l.file("TEAMS"), l.file("KEY"), l.file("ATT"))
	var played := await fe.games.continue_saved(data, db)
	Session.apply_block(keep)
	if played == 1 and fe.last_sim != null and index >= 0:
		l.game_played(index, fe.last_sim)
		l.save()
		fe.stats.forget_files()
		if l.season_over:
			await awards_screen()
	fe.last_sim = null

# ---------------------------------------------------------------------------------------------
# the calendar (calendar_screen, calendar_draw_games)
# ---------------------------------------------------------------------------------------------

var _cal_month := 0                  # calendar_month: the month shown (0 January)
var _cal_game := -1                  # calendar_game: the game chosen
var _cal_games: Array = []           # the team's scheduled games: [index, record]
var _cal_pal := PackedByteArray()
var _cal_team := -1

static func month_name(m: int) -> String:
	return ["January", "February", "March", "April", "May", "June", "July", "August", "September",
		"October", "November", "December"][m]

## the cell of a day of the month shown
func _cell(day: int) -> Vector2i:
	var k := Exe.u8(FIRST_WEEKDAY + _cal_month) + day - 1
	return Vector2i(Exe.i32(CELL_X + (k % 7) * 4), Exe.i32(CELL_Y + (k / 7) * 4))

func _cal_draw() -> void:
	scr.clearclip()
	var b := fe.bank("embnhl")
	if b != null:
		scr.drawshape_remap(b.find("bkgd"), 0, 0)
	scr.setfont(fe.font_kaufm)
	scr.set_text_colors(0x40, 0x43)
	var title := "%s %d" % [month_name(_cal_month), 1994 if _cal_month < 9 else 1993]
	scr.print_outlined((640 - scr.textwidth(title)) / 2, 0x16, title)
	scr.setfont(fe.font_main)
	small_logo(_cal_team, 0x26, 0x3f, _cal_pal, true)
	# the week day cells of the month with their numbers
	for d in range(1, Exe.u8(MONTH_LENGTH + _cal_month) + 1):
		var c := _cell(d)
		fe.draw_dialog_frame(c.x - 1, c.y - 1, 0x4e, 0x40, 0x41, 0x40, 0x42)
		scr.set_text_colors(0x40, 0x43)
		scr.print_text_at(c.x + 3, c.y, str(d))
	# the legend: Home / Away in the first free cell
	var lx := Exe.i32(CELL_X + 6 * 4)
	var ly := Exe.i32(CELL_Y + 5 * 4)
	if Exe.u8(FIRST_WEEKDAY + _cal_month) != 0:
		lx = Exe.i32(CELL_X)
		ly = Exe.i32(CELL_Y)
	scr.fillrect(lx + 2, ly + 5, 4, 8, _home_colour())
	scr.fillrect(lx + 2, ly + 0x11, 4, 8, _away_colour())
	scr.print_text_at(lx + 9, ly + 5, "Home")
	scr.print_text_at(lx + 9, ly + 0x11, "Away")
	for g: Array in _cal_games:
		var rec: PackedByteArray = g[1]
		if rec[0] != _cal_month + 1:
			continue
		var c := _cell(rec[1])
		var home: bool = rec[2] == _cal_team
		var opp: int = rec[3] if home else rec[2]
		scr.fillrect(c.x + 1, c.y + 0x0d, 0x4a, 3, _home_colour() if home else _away_colour())
		small_logo(opp, c.x + 0x26, c.y + 0x22, _cal_pal, true)
		if League.played(rec):
			var mine: int = rec[4] if home else rec[5]
			var theirs: int = rec[5] if home else rec[4]
			var wlt := "W" if mine > theirs else ("L" if mine < theirs else "T")
			var s := "%s:%d-%d" % [wlt, maxi(mine, theirs), mini(mine, theirs)]
			scr.set_text_colors(0x40, 0x43)
			scr.print_text_at(c.x + 0x26 - (scr.textwidth(s) >> 1), c.y + 0x30, s)
		if g[0] == _cal_game:
			_cal_frame(c, 0x40)

func _home_colour() -> int:
	return _nearest(Color(1.0, 0.15, 0.15))

func _away_colour() -> int:
	return _nearest(Color(0.2, 0.35, 1.0))

func _nearest(c: Color) -> int:
	var best := 0
	var bd := 1 << 30
	for i in 0xf0:
		var d := 0
		var v := [int(c.r * 63), int(c.g * 63), int(c.b * 63)]
		for k in 3:
			var e: int = _cal_pal[i * 3 + k] - v[k]
			d += e * e
		if d < bd:
			bd = d
			best = i
	return best

## the frame around the game chosen (the lines of colour 0xbb in the calendar's palette)
func _cal_frame(c: Vector2i, colour: int) -> void:
	var x0 := c.x - 1
	var y0 := c.y - 1
	var x1 := c.x + 0x4c
	var y1 := c.y + 0x3e
	for k in 2:
		scr.drawline(x0 + k, y0 + k, x1 - k, y0 + k, colour)
		scr.drawline(x0 + k, y1 - k, x1 - k, y1 - k, colour)
		scr.drawline(x0 + k, y0 + k, x0 + k, y1 - k, colour)
		scr.drawline(x1 - k, y0 + k, x1 - k, y1 - k, colour)

## calendar_screen: the month of the next game, its games (the other months with Next / Previous
## month); a click on an open game chooses it (in the play-offs only the next one), a second click
## plays it. Returns the game's index, -1 for Return to Sports Central.
func calendar_screen(team: int) -> int:
	var l: League = Session.league
	_cal_team = team
	_cal_games.clear()
	_cal_game = -1
	var month := -1
	for i in League.ALL_GAMES:
		var rec := l.game(i)
		if (rec[2] == team or rec[3] == team) and rec[0] != 0xff and rec[1] != 0xff:
			_cal_games.append([i, rec])
			if not League.played(rec) and _cal_game < 0:
				_cal_game = i
				month = rec[0] - 1
	if month < 0:
		var last := l.game(maxi(l.games_played() - 1, 0))
		month = (last[0] - 1) if last[0] != 0xff else 3
	_cal_month = month
	await fe.leave_screen(100)
	var b := fe.bank("embpal")
	_cal_pal = Screen8.shape_palette(b.find("!pal")) if b != null else FrontEnd._grey_palette()
	_cal_draw()
	var root := Menus.list(0xc8657, 3)
	_cal_menu_state()
	ui.draw_menu_items(root, 0x40, 0x41, 0x42)
	fe.play_loop("calendar")
	await scr.fade_in(_cal_pal, 16)
	var state := {"result": -1}
	var redraw := func() -> void:
		await scr.fade_out(16)
		_cal_draw()
		_cal_menu_state()
		ui.draw_menu_items(root, 0x40, 0x41, 0x42)
		await scr.fade_in(_cal_pal, 16)
	var handler := func(cb: String):
		match cb:
			"calendar_next_month":
				_cal_month = mini(_cal_month + 1, 11) if _cal_month != 5 else 5
				_cal_draw()
				_cal_menu_state()
				ui.draw_menu_items(root, 0x40, 0x41, 0x42)
				return 0
			"calendar_prev_month":
				_cal_month = maxi(_cal_month - 1, 0) if _cal_month != 9 else 9
				_cal_draw()
				_cal_menu_state()
				ui.draw_menu_items(root, 0x40, 0x41, 0x42)
				return 0
			"calendar_return":
				state["result"] = -1
				return 1
		return await fe.dispatch(cb)
	var outside := func(e: Dictionary):
		var x: int = e["x"]
		var y: int = e["y"]
		if x <= 0x51 or x >= 0x25f or y <= 0x43 or y >= 0x1b2:
			return 0
		for g: Array in _cal_games:
			var rec: PackedByteArray = g[1]
			if rec[0] != _cal_month + 1 or League.played(rec):
				continue
			var c := _cell(rec[1])
			if x < c.x or x > c.x + 0x4c or y < c.y or y > c.y + 0x3e:
				continue
			if g[0] == _cal_game:
				state["result"] = _cal_game
				return 4
			# another open game: in the play-offs only the next one can be chosen
			if g[0] < League.SEASON_GAMES:
				_cal_game = g[0]
				_cal_draw()
				ui.draw_menu_items(root, 0x40, 0x41, 0x42)
			return 0
		return 0
	var code := await ui.run_menu(root, 0x40, 0x41, 0x42, handler, redraw, [1, 4], Callable(), outside)
	ui.show_pointer(false)
	await fe.leave_screen(100)
	return state["result"] if code == 4 else -1

## Next month stops at June, Previous month at October
func _cal_menu_state() -> void:
	Menus.at(0xc85e2).cb = "" if _cal_month == 5 else "calendar_next_month"
	Menus.at(0xc8602).cb = "" if _cal_month == 9 else "calendar_prev_month"

# ---------------------------------------------------------------------------------------------
# the awards after the play-offs (awards_screen 0x13320, AwardsScreen.gd)
# ---------------------------------------------------------------------------------------------

func awards_screen() -> void:
	var l: League = Session.league
	await AwardsScreen.new(fe).run(l.file("TEAMS"), l.file("KEY"), l.file("SEASON"))

# ---------------------------------------------------------------------------------------------
# the League Manager (unk_ce64f)
# ---------------------------------------------------------------------------------------------

## the merges of the original bring the results of the human teams' copies together and simulate
## the games of the computer teams; here the results are in the league's files already: the
## games up to the last one played are simulated
func _update() -> int:
	var l: League = Session.league
	if l == null:
		return 0
	fe.set_dialog_colors(0xf9, 0xfa, 0xf8, 0xfa, 0)
	var keep := scr.snapshot()
	await _busy(["Updating schedule."])
	l.play_day(l.games_played(), -1, 7)
	l.save()
	fe.stats.forget_files()
	scr.restore(keep)
	if l.season_over:
		await awards_screen()
		return 2
	return 0

func league_merge_files() -> int:
	return await _update()

func league_merge_update_teams() -> int:
	return await _update()

func league_update_team_databases() -> int:
	return await _update()

func league_rebuild_databases() -> int:
	return await _update()

## Add Team to League (select_human_team_dialog 0x408f9): "All the teams are already human" when
## they are, else the grid (mode 2); PINFO.DB written when the number of human teams changed
func league_add_team() -> int:
	var l: League = Session.league
	if l == null:
		return 0
	var count := l.pinfo.decode_u16(0)
	if count >= 26:
		fe.set_dialog_colors(0xf9, 0xfa, 0xf8, 0xfa, 0)
		await fe.message_dialog(["All the teams are already human"])
		return 0
	var p := l.pinfo.duplicate()
	if await team_info_screen(2, "Select new human controlled team", p) != null and p.decode_u16(0) != count:
		l.pinfo = p
		l.save()
	return 2

## Remove Team From League (select_human_control_dialog 0x40c29): "There is only one human controlled
## team!" for one, else the grid (mode 4); PINFO.DB written when the number changed
func league_remove_team() -> int:
	var l: League = Session.league
	if l == null:
		return 0
	var count := l.pinfo.decode_u16(0)
	if count <= 1:
		fe.set_dialog_colors(0xf9, 0xfa, 0xf8, 0xfa, 0)
		await fe.message_dialog(["There is only one human", "controlled team!"])
		return 0
	var p := l.pinfo.duplicate()
	if await team_info_screen(4, "Select human controlled team to remove", p) != null and p.decode_u16(0) != count:
		l.pinfo = p
		l.save()
	return 2

## Change League Play Settings (league_change_play_settings 0x332f8): the league's settings applied,
## the master password (league_settings_flow 0x40f4e), the settings dialog of a league
## (league_play_settings_screen: Accept writes the league's GAME.SET), the exhibition's back
func league_change_play_settings() -> int:
	var l: League = Session.league
	if l == null:
		return 0
	var keep := Session.save_block()
	if l.game_set.size() >= Session.SETTINGS_SIZE:
		Session.apply_block(l.game_set)
	fe.set_dialog_colors(0xf9, 0xfa, 0xf8, 0xfa, 0)
	if await master_password_prompt(l):
		await fe.settings.league_play_settings_screen()
	Session.apply_block(keep)
	return 0

## Show League Settings ... of the calendar (settings_screen_a: SETTING5, to look at)
func settings_screen_a() -> int:
	return await fe.settings.settings_screen_a()

## the grid's Settings: League settings of a new league (editable), Show League settings of the team
## to play (to look at)
func menu_league_settings() -> int:
	return await fe.settings.menu_league_settings()

func menu_show_league_settings() -> int:
	return await fe.settings.menu_show_league_settings()

## Play-Off Settings ... of the desk with a series open (league_settings_screen 0x7a29c): the series'
## settings in the dialog of a league, kept in its GAME.SET
func league_settings_screen() -> int:
	var l: League = Session.league
	if l == null:
		return 0
	fe.settings.series_game = series_game(l)
	l.game_set = await fe.settings.league_settings_screen(l.game_set)
	if l.game_set.size() >= Session.SETTINGS_SIZE:
		l.option_flags = l.game_set.decode_u32(0x59)
	l.save()
	return 0

## dword_d29fb: the game of the series to be played next (the play-off games played, modulo 7)
static func series_game(l: League) -> int:
	return maxi(l.games_played() - League.SEASON_GAMES, 0) % 7

## Trade Players ... (league_trade_players 0x33523 -> statistics_menu 0x40183): no saved game waiting,
## before the trading deadline (the next game's date: March 22nd; April on; the play-offs), more than
## one human team; two of them chosen (team_info_screen), their passwords, the trade screen
## (TradeScreen), the trade written (team_edit_screen: Trade.edit, the number dialogs) and both teams'
## line editors. (The original also wants the league's databases merged; here there is one copy.)
func league_trade_players() -> int:
	var l: League = Session.league
	if l == null:
		return 0
	fe.set_dialog_colors(0xf9, 0xfa, 0xf8, 0xfa, 0xf7)
	if FileAccess.file_exists(l.dir.path_join("GAME.SAV")):
		await fe.message_dialog(["There is a saved game in the league", l.name, "which must be played first!"])
		return 0
	var gp := l.games_played()
	var deadline := gp >= 0x444
	if gp < 0x4ad:
		var g := l.game(gp)
		deadline = (g[0] == 3 and g[1] >= 0x16) or (g[0] > 3 and g[0] < 10) or gp >= 0x444
	if deadline:
		await fe.message_dialog(["The trading deadline has passed!", "No more trading is allowed!"])
		return 0
	if l.humans().size() == 1:
		await fe.message_dialog(["There is only one human", "controlled team!"])
		return 0
	var picks = await team_info_screen(0x10, "Select two teams for trading players", l.pinfo)
	if picks == null or picks[0] < 0 or picks[1] < 0:
		return 0
	if not await password_prompt(l, picks[0]) or not await password_prompt(l, picks[1]):
		return 0
	var shirts = await TradeScreen.new(fe).run(l.file("TEAMS"), l.file("KEY"), picks[0], picks[1])
	if shirts == null:
		return 0
	var err := await _trade(l, picks[0], picks[1], shirts)
	if err != 0:
		await fe.message_dialog(["Error while trading players!"])
	return 0

## team_edit_screen: the trade into the league's files (the number dialogs asked), then the line
## editors of both teams (Save These Lines into the league's TEAMS.DB)
func _trade(l: League, a: int, b: int, shirts: PackedByteArray) -> int:
	var answer := func(side: int, slot: int, keys: Array) -> int:
		var k: PackedByteArray = keys[slot]
		var team := (l.file("TEAMS") as PackedByteArray).slice((a if side == 0 else b) * Trade.TEAM + 0x1a, (a if side == 0 else b) * Trade.TEAM + 0x1a + 0x10)
		await fe.message_dialog(["The jersey number %2d is already used on %s!" % [k[1], Trade._cstr(team, 0)]])
		return await fe.number_entry_dialog("Enter jersey number for %s %s" % [Trade._cstr(k, 3), Trade._cstr(k, 0x13)], 2, 0x16, 1, 99)
	var r: Array = await Trade.edit(l.file("TEAMS").duplicate(), l.file("KEY").duplicate(), a, b, shirts, answer)
	var f: Trade.Files = r[2]
	if f != null:
		l.files["TEAMS"] = f.teams.data
		l.files["KEY"] = f.key.data
		l.save()
		fe.stats.forget_files()
	if r[0] != 0 or not r[1]:
		return r[0]
	# the line editors of the two teams on the league's databases
	var keep_db := fe.db
	var keep := [Session.home_team, Session.away_team]
	var keep_lines: Dictionary = Session.line_override.duplicate()
	fe.db = Database.open(l.file("TEAMS"), l.file("KEY"), l.file("ATT"))
	Session.home_team = a
	Session.away_team = b
	Session.line_override.clear()
	for side in 2:
		var ed := LineEditor.new(fe)
		ed.teams_read = func() -> PackedByteArray: return l.file("TEAMS")
		ed.teams_write = func(t: PackedByteArray) -> void:
			l.files["TEAMS"] = t
			l.save()
			fe.db = Database.open(t, l.file("KEY"), l.file("ATT"))
		await ed.edit(side, 0xcf3cf, 3)
	fe.db = keep_db
	Session.home_team = keep[0]
	Session.away_team = keep[1]
	Session.line_override = keep_lines
	return 0

## Central Registry ... (menu_central_registry: the database editor; a league's databases when a
## league is open)
func menu_central_registry() -> int:
	return await Registry.new(fe).run()

func league_hilights() -> int:
	return await highlights_flow()

# ---------------------------------------------------------------------------------------------
# the highlights reels (league_highlights_flow 0x80075, highlights_screen 0x7fcf8)
# ---------------------------------------------------------------------------------------------

## league_highlights_flow: a team with a reel, one of its highlights, read and replayed
## (highlights_play); -1 when there is none or the read fails
func highlights_flow() -> int:
	fe.set_dialog_colors(0xf9, 0xfa, 0xf8, 0xfa, 0)
	var l: League = Session.league
	if l == null:
		return -1
	var pick := await highlights_screen(l.dir)
	if pick.is_empty():
		return -1
	var f := FileAccess.open(pick[0], FileAccess.READ)
	if f == null:
		return -1
	f.seek(pick[1] * HighlightReel.RECORD)
	var rec := f.get_buffer(HighlightReel.RECORD)
	f.close()
	if rec.size() != HighlightReel.RECORD:
		return -1
	await fe.play_saved_highlight(rec)
	return 0

## highlights_screen: the teams that have a reel (TEAM.HI in the league's directory; their order by
## team, qsort with cmp_ints) by city in a list, "There are no hilights!" without one; then the
## chosen team's highlights by date, teams, period and time (format_save_description). Returns
## [the reel's path, the highlight], [] when there is none.
func highlights_screen(dir: String) -> Array:
	var teams := []
	var d := DirAccess.open(dir)
	if d != null:
		for n in d.get_files():
			if n.to_upper().ends_with(".HI"):
				teams.append(HighlightReel.team_of_file(n))
	if teams.is_empty():
		await fe.message_dialog(["There are no hilights!"], [])
		return []
	Clib.qsort(teams, func(a: int, b: int) -> int: return 1 if a > b else (-1 if a < b else 0))
	var names := teams.map(func(t: int) -> String: return Exe.str_ptr(HighlightReel.CITY_NAMES + t * 4))
	var k := await fe.listbox_dialog(names, "Select a team", 2)
	if k < 0:
		return []
	var path := dir.path_join(HighlightReel.abbrev(teams[k]) + ".HI")
	var f := FileAccess.open(path, FileAccess.READ)
	if f == null:
		return []
	var n := f.get_length() / HighlightReel.RECORD
	var descs := []
	for i in n:
		f.seek(i * HighlightReel.RECORD)
		var h := f.get_buffer(0x4c)
		if h.size() != 0x4c:
			break
		descs.append(HighlightReel.describe(h))
	f.close()
	if descs.is_empty():
		return []
	var h := await fe.listbox_dialog(descs, "Select a hilight", 2)
	return [path, h] if h >= 0 else []

func league_import_databases() -> int:
	await fe.message_dialog(["All human teams of this league", "play on this computer."])
	return 0

# ---------------------------------------------------------------------------------------------
# New Play-Off Series ... (stanley_cup_tree_screen) and Next Play-Off Game ... (playoff_tree_screen
# with the bracket of playoff_bracket_screen 0x8a652)
# ---------------------------------------------------------------------------------------------

## stanley_cup_tree_screen (0x8669e): over EMBSCUP the name (NAME.PO), then settings_playoff's
## defaults (a play-off series, Rangers - Canucks, every rule, the first controller found for player 1
## with the Rangers), an old series of the name replaced, the databases (current or original), the
## locker room; EMBSCUP again with "Please Wait. Setting Up Play-Offs." while the bracket is seeded
## (cup_tree_seed_bracket) and the files are written; the series is open. The screen fades out, the
## exhibition's settings and the dialog colours come back.
func stanley_cup_tree_screen() -> int:
	var dc := [fe.dlg_face, fe.dlg_light, fe.dlg_dark, fe.dlg_text, fe.dlg_shadow]
	var keep := Session.save_block()
	fe.set_dialog_colors(0x41, 0x40, 0x42, 0x40, 0x43)
	await _cup_backdrop()
	# colour 3 white for the cursor of the name (0x40 XOR 0x43)
	scr.settextcolor(0x40, 0x41)
	var c3 := scr.getpalette().slice(9, 12)
	scr.setpalette(PackedByteArray([0x3f, 0x3f, 0x3f]), 3, 1)
	var name := (await fe.text_entry_dialog("Please Enter New Play-Off Name", 8, 0x36, 5)).to_upper()
	scr.setpalette(c3, 3, 1)
	var l: League = null
	if fe.entry_key != 0x1b and name != "":
		Session.mode = 1
		Session.home_team = 0xc
		Session.away_team = 0x15
		Session.option_flags = (Session.option_flags & 0x8000) | 0x79ff
		Session.p1_device = 0x10
		for d in [2, 4, 8, 1]:
			if Session.input_devices & d:
				Session.p1_device = d
				break
		Session.p1_team = 0xc if Session.p1_device != 0x10 else -1
		Session.p2_device = 0x10
		Session.p2_team = -2
		Session.p1_side = 0
		Session.p2_side = 1
		var go := true
		if League.list_leagues(".PO").has(name):
			var r := await fe.message_dialog_buttons(["There is already a Play-Off with that name!",
				"Do you want to replace it with a new Play-Off?"], FrontEnd.buttons_at(0xc7733, 2))
			go = r != 0
			if go:
				League.delete(name, ".PO")
		var org := -1
		if go:
			org = await fe.message_dialog_buttons(["Do you wish to use your", "Current database or the", "Original NHL database?"],
				FrontEnd.buttons_at(0xc74b7, 2))
		if go and org >= 0 and await fe.games.locker_room_hub() != 3:
			Session.league_dir = name + ".PO"
			Session.league_name = name
			var settings := Session.save_block()
			await _cup_backdrop()
			fe.message_show(["Please Wait.", "Setting Up Play-Offs."])
			await ui.frame()
			l = League.create_series(name, sources(org == 1), settings, Session.home_team, Session.away_team)
			l.save()
			fe.restore_dialog_background()
	await scr.fade_out(16)
	Session.apply_block(keep)
	if l != null:
		open_series(l)
	fe.set_dialog_colors(dc[0], dc[1], dc[2], dc[3], dc[4])
	return 2

## EMBSCUP faded in with EMBPAL
func _cup_backdrop() -> void:
	await scr.fade_out(16)
	scr.clearclip()
	var bg := fe.bank("embscup")
	if bg != null:
		scr.drawshape_remap(bg.find("bkgd"), 0, 0)
	var pb := fe.bank("embpal")
	await scr.fade_in(Screen8.shape_palette(pb.find("!pal")) if pb != null else FrontEnd._grey_palette(), 16)

func open_series(l: League) -> void:
	Session.league = l
	Session.league_dir = l.name + ".PO"
	Session.league_name = l.name
	Session.stats_dir = l.dir
	Menus.at(0xce56f).cb = "playoff_tree_screen"
	Menus.at(0xce58f).cb = "league_settings_screen"
	Menus.at(0xce5af).cb = "playoff_highlights"

## the tree of the series (File: Play Next Game / Return; Settings; Statistics): the next game
## of the two teams is played and recorded, the other series move on
func playoff_tree_screen() -> int:
	var l: League = Session.league
	if l == null:
		return 0
	var keep := Session.save_block()
	if l.game_set.size() >= Session.SETTINGS_SIZE:
		Session.apply_block(l.game_set)
	Session.mode = 1
	fe.set_hub_title(1)
	await _continue_saved(l)
	while true:
		var code := await _tree_menu(l)
		if code != 4:
			break
		var index := _next_human_game(l)
		if index < 0:
			await fe.message_dialog(["The play-offs are over."])
			continue
		var rec := l.game(index)
		Session.home_team = rec[2]
		Session.away_team = rec[3]
		Session.game_number = index
		Session.option_flags &= ~0x200
		var db := Database.open(l.file("TEAMS"), l.file("KEY"), l.file("ATT"))
		if await fe.games.scouting_report_screen(rec[2], rec[3]) == 4:
			continue
		var played := await fe.play_game(db)
		if played == 1 and fe.last_sim != null:
			l.game_played(index, fe.last_sim)
			l.save()
			fe.stats.forget_files()
			if l.season_over:
				await awards_screen()
		fe.last_sim = null
	l.game_set = Session.save_block()
	l.save()
	Session.apply_block(keep)
	Session.mode = 0
	fe.set_hub_title(0)
	return 2

func _next_human_game(l: League) -> int:
	for i in range(League.SEASON_GAMES, League.ALL_GAMES):
		var r := l.game(i)
		if r[0] != 0xff and r[2] != 0xff and r[3] != 0xff and not League.played(r) and (l.human(r[2]) or l.human(r[3])):
			return i
	return -1

func _tree_menu(l: League) -> int:
	await fe.leave_screen(100)
	var pal := draw_bracket(l)
	var root := Menus.list(0xcf90f, 3)
	ui.draw_menu_items(root, 0x40, 0x41, 0x42)
	fe.play_loop("leaguetm")
	await scr.fade_in(pal, 16)
	var redraw := func() -> void:
		await scr.fade_out(16)
		draw_bracket(l)
		ui.draw_menu_items(root, 0x40, 0x41, 0x42)
		await scr.fade_in(pal, 16)
	var code := await ui.run_menu(root, 0x40, 0x41, 0x42, fe.dispatch, redraw, [1, 4])
	ui.show_pointer(false)
	await fe.leave_screen(100)
	return code

## the play-off tree's Settings (menu_playoff_settings 0x7a1fc): the series' settings (applied by the
## tree) in the dialog of a league in the colours of EMBPAL
func menu_playoff_settings() -> int:
	var l: League = Session.league
	if l != null:
		fe.settings.series_game = series_game(l)
	return await fe.settings.menu_playoff_settings()

## Play-Off Hilights ...: the series' reels (league_highlights_flow)
func playoff_highlights() -> int:
	return await highlights_flow()

const BRACKET_X := [20, 183, 348, 510]   # unk_c6e22

## playoff_bracket_screen: EMBSCUP, the bars of PSTATBAR, the arrows of SCUPARRW; the western
## conference from the top (first round, second round, final), the eastern one from the bottom,
## the final in the middle; the seed of each team (the font's badges 0x91..) and its wins, a
## winner in colour 0x44. Returns the palette.
func draw_bracket(l: League) -> PackedByteArray:
	scr.clearclip()
	var bg := fe.bank("embscup")
	if bg != null:
		scr.setclip(0, 0x13, 0x280, 0x1e0)
		scr.drawshape_remap(bg.find("bkgd"), 0, 0)
		scr.clearclip()
	var pb := fe.bank("embpal")
	var pal := Screen8.shape_palette(pb.find("!pal")) if pb != null else FrontEnd._grey_palette()
	var br := l.bracket()
	scr.setfont(fe.font_main)
	scr.set_text_colors(0x40, 0x43)
	if (br[0] as Array)[0] < 0:
		var t := "Playoffs have not been seeded yet"
		scr.print_text_at((640 - scr.textwidth(t)) / 2, 0xe8, t)
		return pal
	var bars := fe.bank("pstatbar")
	if bars != null:
		scr.drawshape_remap(bars.find("rst1"), 0, 0x1a)
		scr.drawshape_remap(bars.find("rst2"), 0xf, 0x192)
	var arrows := fe.bank("scuparrw")
	var title := '"%s" Play-Offs' % l.name
	scr.print_text_at((640 - scr.textwidth(title)) / 2, 0x16, title)
	scr.setfont(fe.font_kaufm)
	scr.print_outlined(0x140 - (scr.textwidth("Western Conference") >> 1), 0x2f, "Western Conference")
	scr.print_outlined(0x140 - (scr.textwidth("Eastern Conference") >> 1), 0x1a7, "Eastern Conference")
	scr.setfont(fe.font_main)
	var seeds := {}
	for s in 8:
		var sr: Array = br[s]
		seeds[sr[0]] = s % 4
		seeds[sr[1]] = 7 - s % 4
	var next_round := func(s: int) -> int:
		return 8 + s / 2 if s < 8 else (12 + (s - 8) / 2 if s < 12 else (14 if s < 14 else -1))
	var row := func(s: int, k: int, x: int, wx: int, y: int) -> void:
		var sr: Array = br[s]
		var t: int = sr[k]
		if t < 0:
			return
		scr.set_text_colors(0x40, 0x43)
		scr.print_text_at(x, y, "%c %s" % [0x91 + seeds.get(t, 0), Database.cstring(l.file("TEAMS"), t * 0x2e8 + 0x1a, 13)])
		var adv := false
		var nr: int = next_round.call(s)
		if nr >= 0:
			var nx: Array = br[nr]
			adv = nx[0] == t or nx[1] == t
		else:
			var need := l.series_length() / 2 + 1
			adv = sr[2 + k] >= need
		scr.set_text_colors(0x44 if adv else 0x40, 0x43)
		scr.print_text_at(wx, y, str(sr[2 + k]))
	var all_set := func(list: Array) -> bool:
		for s in list:
			if (br[s] as Array)[0] < 0 or (br[s] as Array)[1] < 0:
				return false
		return true
	# the west: first round, second round, conference final
	for k in 4:
		row.call(k, 0, BRACKET_X[k], BRACKET_X[k] + 0x6a, 0x48)
		row.call(k, 1, BRACKET_X[k], BRACKET_X[k] + 0x6a, 0x58)
	if all_set.call([8, 9]):
		if arrows != null:
			scr.drawshape_remap(arrows.find("aup1"), 18, 102)
		for k in 2:
			var x: int = [48, 220][k]
			row.call(8 + k, 0, x, x + 0x6a, 0x97)
			row.call(8 + k, 1, x, x + 0x6a, 0xa7)
		if all_set.call([12]):
			if arrows != null:
				scr.drawshape_remap(arrows.find("aup2"), 45, 186)
			row.call(12, 0, 0x48, 0xb2, 0xe3)
			row.call(12, 1, 0x48, 0xb2, 0xf3)
	# the east: from the bottom
	for k in 4:
		row.call(4 + k, 0, BRACKET_X[k], BRACKET_X[k] + 0x6a, 0x17e)
		row.call(4 + k, 1, BRACKET_X[k], BRACKET_X[k] + 0x6a, 0x18e)
	if all_set.call([10, 11]):
		if arrows != null:
			scr.drawshape_remap(arrows.find("adn1"), 17, 334)
		for k in 2:
			var x: int = [320, 492][k]
			row.call(10 + k, 0, x, x + 0x6a, 0x131)
			row.call(10 + k, 1, x, x + 0x6a, 0x141)
		if all_set.call([13]):
			if arrows != null:
				scr.drawshape_remap(arrows.find("adn2"), 318, 264)
			row.call(13, 0, 0x1c6, 0x230, 0xe3)
			row.call(13, 1, 0x1c6, 0x230, 0xf3)
	# the final in the middle
	var fin: Array = br[14]
	if fin[0] >= 0 or fin[1] >= 0:
		if arrows != null:
			scr.drawshape_remap(arrows.find("aup3"), 185, 226)
			scr.drawshape_remap(arrows.find("adn3"), 378, 226)
			scr.drawshape_remap(arrows.find("midl"), 262, 211)
		row.call(14, 0, 0x102, 0x16c, 0xe0)
		row.call(14, 1, 0x102, 0x16c, 0xf0)
	return pal

# ---------------------------------------------------------------------------------------------
# the small callbacks of the league menus
# ---------------------------------------------------------------------------------------------

## menu_play_next_game (0x86627): the tree's File menu plays the next game (code 4)
func menu_play_next_game() -> int:
	return 4

## menu_return_to_central (0x86637), menu_return_one (0x79dd1): back
func menu_return_to_central() -> int:
	return 1

func menu_return_one() -> int:
	return 1

## line_editor_done / line_editor_cancel (0x3edaa / 0x3ef27) of the league's line editor menu
func line_editor_done() -> int:
	return 1

func line_editor_cancel() -> int:
	return 1

## roster_dress_done (0x75456): the dressing of a roster is over
func roster_dress_done() -> int:
	return 1

## roster_regular_season_stats / roster_playoff_stats (0x75baa / 0x75bde): the roster's statistics
## of the regular season or the play-offs (stats_playoffs)
func roster_regular_season_stats() -> int:
	Session.stats_playoffs = false
	fe.stats.forget_files()
	return 2

func roster_playoff_stats() -> int:
	Session.stats_playoffs = true
	fe.stats.forget_files()
	return 2
