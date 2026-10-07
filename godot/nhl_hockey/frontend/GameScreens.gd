class_name GameScreens
extends RefCounted
## The screens around a game of the front end: the team choice of the locker room
## (locker_room_hub 0x80830, locker_room_screen 0x80aa4, locker_room_menu 0x81c4e, draw_jerseys
## 0x8156f), New Exhibition Game (exhibition_mode 0x32da9) with the scouting report
## (scouting_report_screen 0x29f28) and play_game (0x11d09).

var fe: FrontEnd
var scr: Screen8
var ui: Ui

const TEAM_POS := 0xd20e0          # unk_d20e0: team -> position in the alphabetical list
const POS_TEAM := 0xd2150          # unk_d2150: position -> team
const POS_ABBREV := 0xd21c0        # off_d21c0: position -> abbreviation (ANA BOS BUF ...)
const BOXES := 0xd227c             # unk_d227c: 8 boxes x0, y0, x1, y1 of locker_room_button_at
const CONFERENCE := 0xc5519        # unk_c5519: conference bits per team
const CITY := 0xc54a9              # off_c54a9: BOSTON, BUFFALO ...
const LOGO_NAMES := 0xc57cc        # off_c57cc: the shape names of the logo banks ("BOS ")

func _init(f: FrontEnd) -> void:
	fe = f
	scr = f.scr
	ui = f.ui

static func team_pos(team: int) -> int:
	return Exe.i32(TEAM_POS + team * 4)

static func pos_team(pos: int) -> int:
	return Exe.i32(POS_TEAM + pos * 4)

static func pos_abbrev(pos: int) -> String:
	return Exe.str_ptr(POS_ABBREV + pos * 4)

static func city(team: int) -> String:
	return Exe.str_ptr(CITY + team * 4)

func _box(i: int) -> Rect2i:
	var a := BOXES + i * 16
	return Rect2i(Exe.i32(a), Exe.i32(a + 4), Exe.i32(a + 8) - Exe.i32(a), Exe.i32(a + 12) - Exe.i32(a + 4))

# ---------------------------------------------------------------------------------------------
# the locker room: choosing the two teams
# ---------------------------------------------------------------------------------------------

var _bg_home: Image                # lineup_room_image (dword_ed794) .. dword_ed7a0, dword_ed790: the room behind the jerseys,
var _bg_away: Image                # the team names and the title
var _bg_home_name: Image
var _bg_away_name: Image
var _bg_title: Image
var _pal := PackedByteArray()

## locker_room_hub (0x80830): the room with both jerseys; returns 2 (the desk is drawn again)
func locker_room_hub() -> int:
	await fe.leave_screen(100)
	await fe.loading_screen()
	await locker_room_screen()
	await locker_room_menu()
	return 2

## +5 on the 6 bit components below 0x3b, 0x3f above (the lighter palette of the room)
static func _brighten(src: PackedByteArray, from: int, to: int, into: PackedByteArray, at: int) -> void:
	for i in range(from, to):
		var v := src[i] if i < src.size() else 0
		into[at + i - from] = v + 5 if v < 0x3b else 0x3f

func _jersey_bank(pos: int, away: bool) -> Shpi:
	return fe.bank(("JER%sV" if away else "JER%sH") % pos_abbrev(pos))

## locker_room_screen (0x80aa4)
func locker_room_screen() -> void:
	scr.clearclip()
	scr.clear(0)
	var room := fe.bank("lockroom")
	_pal.resize(768)
	_pal.fill(0)
	if room != null:
		var p := room.find("!p01")
		var raw := Screen8.shape_palette(p)
		_brighten(raw, 0, 0x168, _pal, 0)
		for i in range(0x168, 0x180):
			_pal[i] = raw[i]
		_draw_home(room.find("room"))
	fe.set_dialog_colors(0xf9, 0xfa, 0xf8, 0xfa, 0xf7)
	_bevel_c(0, 0x1a7, 0x27f, 0x1e0, true)
	for i in range(2, 8):
		var r := _box(i)
		_bevel_c(r.position.x, r.position.y, r.end.x, r.end.y, false)
	_bg_title = scr.grab(0x2d, 0x11, 0x226, 0x19)
	_bg_home = scr.grab(10, 0x45, 0x140, 0x160)
	_bg_away = scr.grab(0x146, 0x4a, 0x138, 0x15b)
	_bg_home_name = scr.grab(0x85, 0x2c, 0xaa, 0xf)
	_bg_away_name = scr.grab(0x152, 0x2c, 0xaa, 0xf)
	var hp := team_pos(Session.home_team)
	var ap := team_pos(Session.away_team)
	_jersey(hp, false)
	_jersey(ap, true)
	_draw_labels(hp, ap)
	scr.setfont(fe.font_main)
	scr.set_text_colors(0x77, 0x62)
	scr.settextcolor(0x77, 0xff)
	var r6 := _box(6)
	var r7 := _box(7)
	scr.print_text_at(r6.position.x + 0x12, r6.position.y + 3, "Accept")
	scr.print_text_at(r7.position.x + 0x12, r7.position.y + 3, "Cancel")
	var b2 := _box(2)
	var b3 := _box(3)
	var b4 := _box(4)
	var b5 := _box(5)
	scr.print_text_at(((b2.position.x + b3.end.x) >> 1) - (scr.textwidth("Home Team") >> 1) + 2, b2.end.y + 5, "Home Team")
	scr.print_text_at(((b4.position.x + b5.end.x) >> 1) - (scr.textwidth("Visiting Team") >> 1) + 2, b4.end.y + 5, "Visiting Team")
	_draw_title(hp, ap)
	fe.play_loop("jersey")
	await scr.fade_in(_pal, 16)

## draw_bevel_box_c (0x80682): the bevel box of the locker room
func _bevel_c(x0: int, y0: int, x1: int, y1: int, dots: bool) -> void:
	fe.draw_bevel_box(x0, y0, x1, y1, dots)

func _draw_home(s: Shpi.Shape) -> void:
	if s != null:
		scr.drawshape_remap(s, s.x, s.y)

func _jersey(pos: int, away: bool) -> void:
	var b := _jersey_bank(pos, away)
	if b == null:
		return
	var raw := Screen8.shape_palette(b.find("!p01"))
	# the home jersey uses colours 0xc0..0xff (palette bytes 0x240..), the visitors' 0x80..0xbf
	var at := 0x180 if away else 0x240
	var sub := PackedByteArray()
	sub.resize(0xc0)
	_brighten(raw, at, at + 0xc0, sub, 0)
	for i in 0xc0:
		_pal[at + i] = sub[i]
	_draw_home(b.find("0000"))

## the team names in the arrow boxes (the previous / next team of each list) and the two cities
func _draw_labels(hp: int, ap: int) -> void:
	scr.setfont(fe.font_main)
	scr.settextcolor(0x77, 0xff)
	scr.set_text_colors(0x77, 0x62)
	for i in range(2, 6):
		var r := _box(i)
		scr.fillrect(r.position.x + 1, r.position.y + 1, r.size.x - 1, r.size.y - 1, 0x70)
	var n := 0x1a if Session.mode != 0 else 0x1c
	var labels := [_step(hp, ap, -1, n), _step(hp, ap, 1, n), _step(ap, hp, -1, n), _step(ap, hp, 1, n)]
	for k in 4:
		var r := _box(2 + k)
		var t := pos_abbrev(labels[k])
		scr.print_text_at(((r.position.x + r.end.x) >> 1) - (scr.textwidth(t) >> 1) + 2, r.position.y + 3, t)
	var hc := city(pos_team(hp))
	scr.print_outlined(0x12d - scr.textwidth(hc), 0x2c, hc)
	scr.print_outlined(0x13a, 0x2c, "vs")
	scr.print_outlined(0x154, 0x2c, city(pos_team(ap)))

## the neighbour of a list position: the other list's team is skipped; in an exhibition the all star
## teams (positions 26, 27) only pair with each other
static func _step(pos: int, other: int, d: int, n: int) -> int:
	var p := (pos + d + n) % n
	if n == 0x1c:
		if p > 0x19 and p == other:
			p = (p + d + n) % n
	elif p == other:
		p = (p + d + n) % n
	return p

func _draw_title(hp: int, ap: int) -> void:
	scr.setfont(fe.font_kaufm)
	scr.set_text_colors(0x77, 0x62)
	var t := "Exhibition Game"
	if Session.mode == 1:
		var conf := Exe.i32(CONFERENCE + pos_team(hp) * 4) | Exe.i32(CONFERENCE + pos_team(ap) * 4)
		t = Exe.str_ptr(0xd2230 + 4 * Exe.i32(0xd223c + conf * 4))
	scr.print_outlined((640 - scr.textwidth(t)) / 2, 0x12, t)
	scr.setfont(fe.font_main)

## draw_jerseys (0x8156f): one side again with a new team
func draw_jerseys(away: bool, hp: int, ap: int) -> void:
	if away:
		scr.put(_bg_away)
		scr.put(_bg_away_name)
	else:
		scr.put(_bg_home)
		scr.put(_bg_home_name)
	_jersey(ap if away else hp, away)
	scr.setpalette(_pal.slice(0x180 if away else 0x240, (0x180 if away else 0x240) + 0xc0), 0x80 if away else 0xc0, 0x40)
	if Session.mode == 1:
		scr.put(_bg_title)
		_draw_title(hp, ap)
	_draw_labels(hp, ap)

## locker_room_menu (0x81c4e): a click on a jersey or its right arrow takes the next team, on the
## left arrow the previous one; Accept sets the teams (and the users' teams), Cancel or Esc leave
func locker_room_menu() -> int:
	var hp := team_pos(Session.home_team)
	var ap := team_pos(Session.away_team)
	var n := 0x1a if Session.mode != 0 else 0x1c
	ui.show_pointer(true)
	ui.reset_events()
	while true:
		var e: Dictionary = await ui.wait_event()
		var bt: int = e["buttons"]
		if bt & 4:
			break
		if bt & 2 == 0:
			continue
		var hit := -1
		for i in 8:
			var r := _box(i)
			if e["x"] + 4 >= r.position.x and e["x"] + 4 <= r.end.x and e["y"] >= r.position.y and e["y"] <= r.end.y:
				hit = i
				break
		match hit:
			0, 3:
				hp = _step(hp, ap, 1, n)
				draw_jerseys(false, hp, ap)
			2:
				hp = _step(hp, ap, -1, n)
				draw_jerseys(false, hp, ap)
			1, 5:
				ap = _step(ap, hp, 1, n)
				draw_jerseys(true, hp, ap)
			4:
				ap = _step(ap, hp, -1, n)
				draw_jerseys(true, hp, ap)
			6:
				if Session.home_team != pos_team(hp) or Session.away_team != pos_team(ap):
					Session.line_override.clear()
					Session.scratches.clear()
				Session.home_team = pos_team(hp)
				Session.away_team = pos_team(ap)
				if Session.p1_team >= 0:
					Session.p1_team = Session.home_team if Session.p1_side == 0 else Session.away_team
				if Session.p2_team >= 0:
					Session.p2_team = Session.home_team if Session.p2_side == 0 else Session.away_team
				fe.save_game_set()
				ui.show_pointer(false)
				await fe.leave_screen(100)
				return 0
			7:
				break
		ui.reset_events()
	ui.show_pointer(false)
	await fe.leave_screen(100)
	return 3

# ---------------------------------------------------------------------------------------------
# New Exhibition Game
# ---------------------------------------------------------------------------------------------

## exhibition_mode (0x32da9): the scouting report, then the game; back to the desk (2)
func exhibition_mode() -> int:
	Session.mode = 0
	Session.saved_game = -1
	var r := await scouting_report_screen(Session.home_team, Session.away_team)
	if r != 4:
		await fe.play_game()
	return 2

## scouting_report_screen (0x29f28): the scouting report of the two teams in front of ARENA.QFS: the
## logos of SRLOGO.QFS, "<away> at <home>", the nine team ratings of TEAMS.DB (+0x2dc) with the
## better value of each line marked (0xfd), the buttons Away lines / Play / Cancel / Home lines
## (the line buttons only for the teams a user plays). Returns 0 to play, 4 cancelled.
func scouting_report_screen(home: int, away: int) -> int:
	await fe.leave_screen(100)
	var teams_db := GameFiles.read_raw("teams.db")
	var rec := [teams_db.slice(home * 0x2e8, (home + 1) * 0x2e8), teams_db.slice(away * 0x2e8, (away + 1) * 0x2e8)]
	fe.set_dialog_colors(0xf9, 0xfa, 0xf8, 0xfa, 0xf7)
	scr.clearclip()
	scr.clear(0)
	var arena := fe.bank("arena")
	var pal := PackedByteArray()
	pal.resize(768)
	if arena != null:
		pal = Screen8.shape_palette(arena.find("!pal"))
		scr.drawshape_home(arena.find("rink"))
	var logos := fe.bank("srlogo")
	if logos != null:
		var la := logos.find(Exe.str_ptr(LOGO_NAMES + away * 4))
		var lh := logos.find(Exe.str_ptr(LOGO_NAMES + home * 4))
		if la != null:
			scr.drawshape_remap(la, 0x3c, 0x6d)
		if lh != null:
			scr.drawshape_remap(lh, 0x1e5, 0x6d)
	scr.setfont(fe.font_kaufm)
	scr.set_text_colors(0xfa, 0xf7)
	var title := "%s at %s" % [Database.cstring(rec[1], 0x1a, 13), Database.cstring(rec[0], 0x1a, 13)]
	scr.print_outlined((640 - scr.textwidth(title)) / 2, 0x93, title)
	scr.fillrect(0x6e, 0xcf, 0x1ae, 5, fe.dlg_face)
	scr.drawline(0x6e, 0xcf, 0x21c, 0xcf, fe.dlg_light)
	scr.drawline(0x6e, 0xd3, 0x21c, 0xd3, fe.dlg_dark)
	var fh := scr.font_height()
	var labels := Exe.str_table(0xc6f48, 9)
	for i in 9:
		var y := (fh + 3) * i + 0xda
		if i == 8:
			y = (fh + 3) * i + 0xdf
			scr.fillrect(0x6e, y, 0x1ae, 5, fe.dlg_face)
			scr.drawline(0x6e, y, 0x21c, y, fe.dlg_light)
			scr.drawline(0x6e, (fh + 3) * i + 0xe3, 0x21c, (fh + 3) * i + 0xe3, fe.dlg_dark)
			y = (fh + 3) * i + 0xe8
		scr.print_outlined((640 - scr.textwidth(labels[i])) / 2, y, labels[i])
	for i in 9:
		var k := Exe.u8(0xc6f6c + i)
		var hv: int = rec[0][0x2dc + k] if rec[0].size() > 0x2dc + k else 0
		var av: int = rec[1][0x2dc + k] if rec[1].size() > 0x2dc + k else 0
		var y := (fh + 3) * i + (0xe6 if i == 8 else 0xda)
		scr.set_text_colors(0xfd if av > hv else 0xfa, 0xf7)
		scr.print_outlined(0x6e, y, str(av))
		scr.set_text_colors(0xfd if hv > av else 0xfa, 0xf7)
		scr.print_outlined(0x212, y, str(hv))
	scr.set_text_colors(0xfa, 0xf7)
	scr.setfont(fe.font_main)
	# the buttons: Away lines only when a user plays the visitors, Home lines for the home team
	var away_user := Session.p1_team == away or Session.p2_team == away
	var home_user := Session.p1_team == home or Session.p2_team == home
	var list: Array
	var first := 0
	if home_user and away_user:
		list = FrontEnd.buttons_at(0xc6e7e, 4)
	elif away_user:
		list = FrontEnd.buttons_at(0xc6e7e, 3)
	elif home_user:
		list = FrontEnd.buttons_at(0xc6e9a, 3)
		first = 1
	else:
		list = FrontEnd.buttons_at(0xc6e9a, 2)
		first = 1
	fe.draw_bevel_box(0, 0x1ae, 0x26b, 0x1df, true)
	fe.buttons_draw_all(list)
	fe.play_loop("scouting")
	await scr.fade_in(pal, 16)
	var result := 0
	ui.show_pointer(true)
	ui.reset_events()
	while true:
		var e: Dictionary = await ui.wait_event()
		var bt: int = e["buttons"]
		if bt & 4:
			result = 4
			break
		if bt & 3 == 0:
			continue
		var k := fe.button_at(list, e["x"], e["y"], bt)
		if k < 0:
			continue
		match k + first:
			0:
				await fe.edit_lines_for(away, pal)
			1:
				result = 0
				break
			2:
				result = 4
				break
			3:
				await fe.edit_lines_for(home, pal)
		ui.reset_events()
	ui.show_pointer(false)
	await fe.leave_screen(100)
	if result < 2:
		# tonight's line-ups (lineups_screen); Esc there cancels the game
		if await BoxScore.new(fe).lineups_screen(home, away) == 3:
			result = 4
	return result

# ---------------------------------------------------------------------------------------------
# the callbacks of the pause screen (pause_menu, unk_ceb8f / unk_cec4f)
# ---------------------------------------------------------------------------------------------

## menu_back_to_game (0x1a5a1)
func menu_back_to_game() -> int:
	return 1

## pause_sports_desk (0x1a5b1): after the game, straight back
func pause_sports_desk() -> int:
	return 5

## pause_sports_desk_confirm (0x1a5d4): leaving a game that is not over
func pause_sports_desk_confirm() -> int:
	var first := "Returning to sports central"
	if Session.mode == 1:
		first = "Returning to the playoff tree"
	elif Session.mode == 2:
		first = "Returning out of the game"
	if await fe.yes_no_dialog([first, "may lose this game's data.", "Do you wish to return?"]):
		return 5
	return 0

## exit_game_dialog (0x1a6a7): the program ends (credits_screen, back to DOS)
func exit_game_dialog() -> int:
	await fe.fade_loop(100)
	if await fe.yes_no_dialog(["Exiting the game", "may lose this game's data.", "Do you wish to exit?"]):
		await scr.fade_out(16)
		await fe.quit_program()
	return 0

## menu_go_to_replay (0x1a817): the instant replay of the match, then the pause screen again
func menu_go_to_replay() -> int:
	return 7

## set_goalie_menu_labels (0x1c852): the two goalies of each team's line table (" 00 X. NAME") and
## the mark of the one in the net (glyph 1 selected, 2 not), only for a team a user plays
func set_goalie_menu_labels() -> void:
	var m: Node = fe.game
	for t in 2:
		var base := 0xcee4f if t == 0 else 0xceeaf
		var parent := Menus.at(0xcedcf if t == 0 else 0xcedef)
		if m == null:
			parent.sub = 0
			continue
		var sim: Sim = m.sim
		parent.sub = base if sim.is_user_team(t) else 0
		var team := sim.teams[t]
		var lt := Lines.line_table(team)
		var sel := 2 if Entity.to_s16(team.goalie_request) < 0 else team.goalie_request & 1
		for g in 3:
			var it := Menus.at(base + g * 32)
			var name := "NONE"
			if g < 2:
				var r: int = lt[0x24 + g] - 25 if lt.size() > 0x25 else -1
				if team.info != null and r >= 0 and r < team.info.goalies.size() and team.info.goalies[r] != null:
					var p: Database.Player = team.info.goalies[r]
					name = "%02d %s. %s" % [p.number, p.first.left(1), p.last]
			it.text = ("\u0001 " if g == sel else "\u0002 ") + name
			it.x1 = maxi(scr.textwidth(it.text) + 8, 0x50)

func _goalie(team: int, which: int) -> int:
	if fe.game != null:
		Lines.choose_goalie(fe.game.sim, team, which)
		set_goalie_menu_labels()
	return 0

func menu_home_goalie1() -> int:
	return _goalie(0, 0)

func menu_home_goalie2() -> int:
	return _goalie(0, 1)

func menu_home_no_goalie() -> int:
	return _goalie(0, -1)

func menu_away_goalie1() -> int:
	return _goalie(1, 0)

func menu_away_goalie2() -> int:
	return _goalie(1, 1)

func menu_away_no_goalie() -> int:
	return _goalie(1, -1)

## menu_edit_lines_home / menu_edit_lines_away (0x1a8aa / 0x1a922): the line editor of the pause
## screen (unk_cf2ef) for a team of the match
func menu_edit_lines_home() -> int:
	return await _edit_lines(0)

func menu_edit_lines_away() -> int:
	return await _edit_lines(1)

func _edit_lines(side: int) -> int:
	if fe.game == null:
		return 0
	var ed := LineEditor.new(fe)
	await ed.edit(side, 0xcf2ef, 2, fe.game.sim.teams[side])
	return 2

## the box score between the periods and after the game (boxscore_screen 0x2d35a, BoxScore.gd)
func boxscore_screen(kind: int, from_period: int, to_period: int) -> int:
	return await BoxScore.new(fe).boxscore_screen(kind, from_period, to_period)

## the period of the game on the ice (_period_num, 1 based)
func _period_num() -> int:
	return fe.game.sim.period + 1 if fe.game != null else 3

## menu_game_statistics (0x1a96d): the statistics of the two teams (game_statistics_screen)
func menu_game_statistics() -> int:
	await fe.leave_screen(100)
	await BoxScore.new(fe).game_statistics()
	return 2

## menu_penalty_summary (0x1a9ac): the penalties of the game so far
func menu_penalty_summary() -> int:
	await fe.leave_screen(100)
	await boxscore_screen(2, 1, _period_num())
	return 2

## menu_scoring_summary (0x1aa6d): the goals of the game so far
func menu_scoring_summary() -> int:
	await fe.leave_screen(100)
	await boxscore_screen(1, 1, _period_num())
	return 2

## menu_team_scratches (0x1aac4): the players scratched by both teams
func menu_team_scratches() -> int:
	await fe.leave_screen(100)
	await boxscore_screen(4, 0, 0)
	return 2

## Save Game ... of the pause screen (broadcast_booth_screen 0x85924): an exhibition under a name
## (save_game_dialog: NAME.NHL), a league or play-off game as the league's GAME.SAV; the game is
## left and goes on from there later
func broadcast_booth_screen() -> int:
	if fe.game == null:
		return 0
	var sim: Sim = fe.game.sim
	var data := {
		"settings": Session.save_block(),
		"summary": sim.summary_bytes(),
		"scores": BoxScore.games.duplicate(true),
		"index": Session.game_number,
		"lines": Session.line_override.duplicate(),
		"scratches": Session.scratches.duplicate(),
		"sim": SaveGame.capture(sim),
	}
	fe.set_dialog_colors(0xf9, 0xfa, 0xf8, 0xfa, 0)
	var path := ""
	if Session.mode == 0 or Session.league == null:
		var name := (await fe.text_entry_dialog("Enter a name for the saved game", 8)).to_upper()
		if name == "":
			return 0
		path = SaveGame.saves_dir().path_join(name + ".NHL")
	else:
		path = (Session.league as League).dir.path_join("GAME.SAV")
	if not SaveGame.write(path, data):
		await fe.message_dialog(["Error while saving the game!"])
		return 0
	await fe.message_dialog(["The game is saved."])
	return 5

## a saved game continued: its settings, then the match from the saved state; true when it was
## played to the end
func continue_saved(data: Dictionary, db: Database = null) -> int:
	Session.apply_block(data.get("settings", Session.save_block()))
	Session.line_override = data.get("lines", {})
	Session.scratches = data.get("scratches", {})
	BoxScore.games = data.get("scores", [])
	return await fe.play_game(db, data.get("sim", {}))

