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
	fe.set_dialog_colors(0xf9, 0xfa, 0xf8, 0xfa, 0)
	var name := (await fe.text_entry_dialog("Enter New League Name", 8)).to_upper()
	if name == "":
		return 2
	if League.list_leagues().has(name):
		var r := await fe.message_dialog_buttons(["There is already a league with that name!",
			"Do you want to replace it with a new league?"], FrontEnd.buttons_at(0xc7733, 2))
		if r != 1:
			return 2
	var sched := await fe.message_dialog_buttons(["  Which schedule do you want to use?  "], FrontEnd.buttons_at(0xc77ae, 2))
	if sched < 0:
		return 2
	var org := await fe.message_dialog_buttons(["Do you wish to use your", "Current database or the", "Original NHL database?"],
		FrontEnd.buttons_at(0xc74b7, 2))
	if org < 0:
		return 2
	var pinfo := League.pinfo_create([])
	var chosen = await team_info_screen(1, "Select human controlled teams", pinfo)
	if chosen == null:
		return 2
	League.delete(name)
	var humans: Array = []
	for t in 26:
		if pinfo[0x20 + t * 0x1e + 0x17] == 1:
			humans.append(t)
	# new_league_mode: the league's settings: Rangers - Canucks, every option, 0x7800 the play-off
	# series of 7, the first controller for player 1
	var keep := Session.save_block()
	Session.mode = 2
	Session.home_team = 12
	Session.away_team = 21
	Session.option_flags = (Session.option_flags | (0x3ff if Session.sound_enabled else 0x2ff)) & 0x83ff | 0x7800
	Session.league_dir = name + ".LP"
	Session.league_name = name
	var settings := Session.save_block()
	Session.apply_block(keep)
	var lines := ["Creating league."]
	await _busy(lines)
	var l := League.create(name, sources(org == 1), humans, sched == 1, settings)
	for t in 26:
		for k in 0x1e:
			l.pinfo[0x20 + t * 0x1e + k] = pinfo[0x20 + t * 0x1e + k]
	l.pinfo.encode_u16(0, humans.size())
	l.pinfo.encode_u16(2, humans[0] if not humans.is_empty() else 0)
	l.save()
	open_league(l)
	return 2

## a message without buttons while the work is done (restore_dialog_background afterwards)
func _busy(lines: Array) -> void:
	var lh := scr.font_height() + 2
	var w := 0
	for s in lines:
		w = maxi(w, scr.textwidth(s))
	w += 0x10
	var h: int = lines.size() * lh + 0x10
	var x := (640 - w) / 2
	var y := (480 - h) / 2
	fe.draw_dialog_frame(x, y, w, h, fe.dlg_face, fe.dlg_light, fe.dlg_dark)
	scr.set_text_colors(fe.dlg_text, fe.dlg_shadow)
	for i in lines.size():
		scr.print_text_at(x + (w - scr.textwidth(lines[i])) / 2, y + 8 + i * lh, lines[i])
	await ui.frame()
	await ui.frame()

## password_scramble (0x3d3ec): the password XOR "NHLHockey"
static func scramble(s: String) -> PackedByteArray:
	var key := "NHLHockey".to_ascii_buffer()
	var out := PackedByteArray()
	out.resize(11)
	var a := s.to_ascii_buffer()
	for i in mini(a.size(), 10):
		out[i] = a[i] ^ key[i % key.size()]
	return out

# ---------------------------------------------------------------------------------------------
# the team grid (team_info_screen): 1 choose the human teams of a new league, 2 add one,
# 4 remove one, 8 select the team to play
# ---------------------------------------------------------------------------------------------

## team_grid_draw: the logos by division (rows of 6 and 7 teams), the names of the human teams
static func grid_cell(team: int) -> Vector2i:
	for r in 4:
		for c in 7:
			if Exe.u8(League.DIVISION_TEAMS + r * 7 + c) == team:
				return Vector2i(c * 0x55 + (0x40 if r < 2 else 0x16), r * 0x5c + 0x58)
	return Vector2i(-1, -1)

static func grid_team_at(x: int, y: int) -> int:
	for t in 26:
		var p := grid_cell(t)
		if x >= p.x - 2 and x <= p.x + 0x4a and y >= p.y - 2 and y <= p.y + 0x3d:
			return t
	return -1

var _grid_pal := PackedByteArray()

func _grid_name(team: int, pinfo: PackedByteArray) -> void:
	var p := grid_cell(team)
	var n := Database.cstring(pinfo, 0x20 + team * 0x1e, 11)
	if pinfo[0x20 + team * 0x1e + 0x17] != 1:
		return
	if n == "":
		n = "Human"
	scr.set_text_colors(0x40, 0x43)
	scr.print_text_at(p.x + (0x4a - scr.textwidth(n)) / 2, p.y + 0x31, n)

func _grid_draw(title: String, pinfo: PackedByteArray) -> void:
	scr.clearclip()
	var b := fe.bank("embnhl")
	if b != null:
		scr.drawshape_remap(b.find("bkgd"), 0, 0)
	scr.setfont(fe.font_main)
	scr.set_text_colors(0x40, 0x43)
	scr.print_text_at((640 - scr.textwidth(title)) / 2, 0x28, title)
	for t in 26:
		var p := grid_cell(t)
		small_logo(t, p.x + 0x25, p.y + 0x18, _grid_pal, true)
		_grid_name(t, pinfo)

## team_grid_highlight: two boxes of xor 0x80 around a logo
func _grid_highlight(team: int) -> void:
	if team < 0:
		return
	var p := grid_cell(team)
	for k in 2:
		var x0 := p.x - 2 - k
		var y0 := p.y - 2 - k
		var x1 := p.x + 0x48 + k
		var y1 := p.y + 0x3d + k
		for x in range(x0, x1 + 1):
			scr.putpixel(x, y0, scr.getpixel(x, y0) ^ 0x80)
			scr.putpixel(x, y1, scr.getpixel(x, y1) ^ 0x80)
		for y in range(y0 + 1, y1):
			scr.putpixel(x0, y, scr.getpixel(x0, y) ^ 0x80)
			scr.putpixel(x1, y, scr.getpixel(x1, y) ^ 0x80)

## returns the team chosen (mode 8), true when done (modes 1, 2, 4), null when cancelled
func team_info_screen(mode: int, title: String, pinfo: PackedByteArray):
	await fe.leave_screen(100)
	var ts := fe.bank("tspal")
	_grid_pal = Screen8.shape_palette(ts.find("!pal")) if ts != null else FrontEnd._grey_palette()
	_grid_draw(title, pinfo)
	var root := Menus.list(0xc8778, 2 if mode & 9 else 1)
	ui.draw_menu_items(root, 0x40, 0x41, 0x42)
	fe.play_loop("leaguetm")
	await scr.fade_in(_grid_pal, 16)
	var state := {"sel": -1, "result": null}
	var handler := func(cb: String):
		match cb:
			"dialog_done":
				state["result"] = true if mode != 8 else state["sel"]
				return 1
			"dialog_cancel":
				state["result"] = null
				return 1
		return await fe.dispatch(cb)
	var outside := func(e: Dictionary):
		var t := grid_team_at(e["x"], e["y"])
		if t < 0:
			return 0
		var human: bool = pinfo[0x20 + t * 0x1e + 0x17] == 1
		if t != state["sel"]:
			_grid_highlight(state["sel"])
			state["sel"] = t
			_grid_highlight(t)
			return 0
		# the selected team again
		if mode == 8:
			if human:
				state["result"] = t
				return 1
			return 0
		if not human and mode & 3:
			if await _make_human(t, pinfo):
				_grid_draw(title, pinfo)
				ui.draw_menu_items(root, 0x40, 0x41, 0x42)
				_grid_highlight(t)
		elif human and (mode & 5):
			pinfo[0x20 + t * 0x1e + 0x17] = 0
			for k in 0x16:
				pinfo[0x20 + t * 0x1e + k] = 0
			_grid_draw(title, pinfo)
			ui.draw_menu_items(root, 0x40, 0x41, 0x42)
			_grid_highlight(t)
		return 0
	var code := await ui.run_menu(root, 0x40, 0x41, 0x42, handler, Callable(), [1], Callable(), outside)
	ui.show_pointer(false)
	await fe.leave_screen(100)
	return state["result"]

## "Who will play the <team>?" (a name not used yet), the password twice
func _make_human(t: int, pinfo: PackedByteArray) -> bool:
	fe.set_dialog_colors(0x41, 0x40, 0x42, 0x40, 0)
	var name := ""
	while true:
		name = await fe.text_entry_dialog("Who will play the %s?" % team_full_name(t), 10)
		if name == "":
			return false
		var used := false
		for k in 26:
			if k != t and pinfo[0x20 + k * 0x1e + 0x17] == 1 and Database.cstring(pinfo, 0x20 + k * 0x1e, 11).to_lower() == name.to_lower():
				used = true
		if not used:
			break
		await fe.message_dialog(["That name has already been used!"])
	var pw := ""
	while true:
		pw = await fe.text_entry_dialog("Enter password for " + name, 10)
		var again := await fe.text_entry_dialog("Verify password for " + name, 10)
		if pw == again:
			break
		await fe.message_dialog(["The password was entered differently", "the second time! Try again."])
	var e := 0x20 + t * 0x1e
	var a := name.to_ascii_buffer()
	for i in 11:
		pinfo[e + i] = a[i] if i < a.size() and i < 10 else 0
	var s := scramble(pw)
	for i in 11:
		pinfo[e + 0xb + i] = s[i]
	pinfo[e + 0x17] = 1
	return true

## password_prompt (0x3d2a7): the password of a human team (none asked when it is empty)
func password_prompt(l: League, t: int) -> bool:
	var e := 0x20 + t * 0x1e + 0xb
	var stored := l.pinfo.slice(e, e + 11)
	if stored == scramble(""):
		return true
	var name := Database.cstring(l.pinfo, 0x20 + t * 0x1e, 11)
	var pw := await fe.text_entry_dialog("Enter password for " + name, 10)
	return scramble(pw) == stored

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
	var team: int = humans[0]
	if humans.size() > 1:
		var t = await team_info_screen(8, "Select a team to play.", l.pinfo)
		if t == null:
			return 2
		team = t
	if not await password_prompt(l, team):
		return 2
	Session.league_team = team
	var keep := Session.save_block()
	if l.game_set.size() >= Session.SETTINGS_SIZE:
		Session.apply_block(l.game_set)
	Session.mode = 2
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
# the awards after the play-offs (awards_screen 0x13320)
# ---------------------------------------------------------------------------------------------

## the Stanley Cup winner and the season's leaders of the league
func awards_screen() -> void:
	var l: League = Session.league
	await fe.leave_screen(100)
	var b := fe.bank("embscup")
	var pb := fe.bank("embpalp")
	var pal := Screen8.shape_palette(pb.find("!pal")) if pb != null else FrontEnd._grey_palette()
	scr.clearclip()
	if b != null:
		scr.drawshape_remap(b.find("bkgd"), 0, 0)
	var po := l.file("SCHEDULE").slice(League.PLAYOFF_OFFSET, League.PLAYOFF_OFFSET + 0x276)
	var champ := League.series_winner(po, 14, League.series_count(po, 14))
	scr.setfont(fe.font_kaufm)
	scr.set_text_colors(0x40, 0x43)
	var lines := ["Stanley Cup Champions", team_name(champ) if champ >= 0 else "", ""]
	var season := l.file("SEASON")
	var best := [-1, -1, -1]
	var bestv := [-1, -1, -1]
	for t in 26:
		for p in 25:
			var k := l.key_of(t, p)
			if k < 0:
				continue
			var s := l.key_i32(k, 0x2c)
			var vals := [season.decode_u16(s + 6), season.decode_u16(s + 2), season.decode_u16(s + 4)]
			for i in 3:
				if vals[i] > bestv[i]:
					bestv[i] = vals[i]
					best[i] = k
	var key := l.file("KEY")
	var what := ["Points", "Goals", "Assists"]
	for i in 3:
		if best[i] >= 0:
			lines.append("%s: %s %s %d" % [what[i], Database.cstring(key, best[i] + 3, 16), Database.cstring(key, best[i] + 0x13, 16), bestv[i]])
	var y := 0x60
	for i in lines.size():
		if i == 3:
			scr.setfont(fe.font_main)
		scr.print_outlined((640 - scr.textwidth(lines[i])) / 2, y, lines[i])
		y += 0x22 if i < 3 else 0x18
	scr.setfont(fe.font_main)
	fe.play_loop("leaguetm")
	await scr.fade_in(pal, 16)
	await ui.wait_ticks_or_input(3000)
	await fe.leave_screen(100)

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

## Add Team to League / Remove Team From League: the human teams in the grid
func league_add_team() -> int:
	var l: League = Session.league
	if l == null:
		return 0
	var p := l.pinfo.duplicate()
	if await team_info_screen(2, "Select human controlled teams", p) != null:
		l.pinfo = p
		l.save()
	return 2

func league_remove_team() -> int:
	var l: League = Session.league
	if l == null:
		return 0
	var p := l.pinfo.duplicate()
	if await team_info_screen(4, "Select human controlled team to remove", p) != null:
		l.pinfo = p
		l.save()
	return 2

## Change League Play Settings: the settings dialog with the league's block
func league_change_play_settings() -> int:
	var l: League = Session.league
	if l == null:
		return 0
	var keep := Session.save_block()
	if l.game_set.size() >= Session.SETTINGS_SIZE:
		Session.apply_block(l.game_set)
	var r: int = await fe.settings.menu_exhibition_settings()
	l.game_set = Session.save_block()
	l.option_flags = Session.option_flags
	l.save()
	Session.apply_block(keep)
	return r

## Show League Settings ... of the calendar (settings_screen_a), League settings of the grid
func settings_screen_a() -> int:
	return await fe.settings.menu_exhibition_settings()

func menu_league_settings() -> int:
	return await fe.settings.menu_exhibition_settings()

func menu_show_league_settings() -> int:
	return await fe.settings.menu_exhibition_settings()

func league_trade_players() -> int:
	return await menu_central_registry()

## Central Registry ... (menu_central_registry: the database editor; a league's databases when a
## league is open)
func menu_central_registry() -> int:
	return await Registry.new(fe).run()

func league_hilights() -> int:
	await fe.message_dialog(["No highlights have been saved", "in this league."])
	return 0

func league_import_databases() -> int:
	await fe.message_dialog(["All human teams of this league", "play on this computer."])
	return 0

# ---------------------------------------------------------------------------------------------
# New Play-Off Series ... (stanley_cup_tree_screen) and Next Play-Off Game ... (playoff_tree_screen
# with the bracket of playoff_bracket_screen 0x8a652)
# ---------------------------------------------------------------------------------------------

## the name (NAME.PO), the databases, the two teams of the locker room; the bracket is seeded
## and the series is open
func stanley_cup_tree_screen() -> int:
	fe.set_dialog_colors(0x41, 0x40, 0x42, 0x40, 0x43)
	var name := (await fe.text_entry_dialog("Please Enter New Play-Off Name", 8)).to_upper()
	if name == "":
		return 2
	if League.list_leagues(".PO").has(name):
		var r := await fe.message_dialog_buttons(["There is already a Play-Off with that name!",
			"Do you want to replace it with a new Play-Off?"], FrontEnd.buttons_at(0xc7733, 2))
		if r != 1:
			return 2
	var org := await fe.message_dialog_buttons(["Do you wish to use your", "Current database or the", "Original NHL database?"],
		FrontEnd.buttons_at(0xc74b7, 2))
	if org < 0:
		return 2
	var keep := Session.save_block()
	Session.mode = 1
	if await fe.games.locker_room_hub() == 3:
		Session.apply_block(keep)
		return 2
	# settings_playoff: the teams chosen, every rule, the play-off overtime
	Session.option_flags = (Session.option_flags >> 8 & 0x80) << 8 | 0x79ff
	Session.league_dir = name + ".PO"
	Session.league_name = name
	var settings := Session.save_block()
	var home := Session.home_team
	var away := Session.away_team
	Session.apply_block(keep)
	await _busy(["Seeding the play-offs."])
	League.delete(name, ".PO")
	var l := League.create_series(name, sources(org == 1), settings, home, away)
	l.save()
	open_series(l)
	return 2

func open_series(l: League) -> void:
	Session.league = l
	Session.league_dir = l.name + ".PO"
	Session.league_name = l.name
	Session.stats_dir = l.dir
	Menus.at(0xce56f).cb = "playoff_tree_screen"
	Menus.at(0xce58f).cb = "menu_playoff_settings"
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

func menu_playoff_settings() -> int:
	return await fe.settings.menu_exhibition_settings()

func playoff_highlights() -> int:
	await fe.message_dialog(["No highlights have been saved", "in these play-offs."])
	return 0

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
