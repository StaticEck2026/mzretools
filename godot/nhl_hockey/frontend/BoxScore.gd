class_name BoxScore
extends RefCounted
## The game summary screens of the front end, drawn from GSUMMARY.DB like the original reads it
## back: boxscore_screen (0x2d35a) with the scoring summary (kind 1), the penalty summary (2), the
## scratches of both teams (4) and the scores around the league (0x20), and the Game Statistics
## of the two teams (team_select_screen2 0x2f5ee). Assets: CTBKGD (background and palette),
## CTLOGO (the logos), CTTITLE1 (def / fowa / scra / tlu / top), CTTITLE2 (summ / ot / per1..3 /
## top), CTTITLE3 (ots / colm / gsta), the INDUS030 font; GAMESUM.IFF plays meanwhile.

var fe: FrontEnd
var scr: Screen8
var ui: Ui

const LOGO_NAMES := 0xc57cc        # off_c57cc: the shape names of the logo banks ("BOS ")
const PENALTY_NAMES := 0xcd304     # off_cd304: the names of the infractions

func _init(f: FrontEnd) -> void:
	fe = f
	scr = f.scr
	ui = f.ui

# ---------------------------------------------------------------------------------------------
# the data: the summary (the running game's or GSUMMARY.DB), the team records, the players
# ---------------------------------------------------------------------------------------------

## the summary bytes: the game on the ice, else the file of the last game
func summary() -> PackedByteArray:
	if fe.game != null:
		return fe.game.sim.summary_bytes()
	return GameFiles.read_raw("gsummary.db")

func _teams_db() -> PackedByteArray:
	return GameFiles.read_raw("teams.db")

func _team_record(t: int) -> PackedByteArray:
	var d := _teams_db()
	return d.slice(t * 0x2e8, (t + 1) * 0x2e8)

## the KEY.DB record of a team's roster index (the skater list at +0x4c, the goalies at +0xb0)
func _player_key(team_rec: PackedByteArray, r: int) -> PackedByteArray:
	var at := 0x4c + r * 4 if r < 25 else 0xb0 + (r - 25) * 4
	if r < 0 or r > 27 or at + 4 > team_rec.size():
		return PackedByteArray()
	var k := team_rec.decode_s32(at)
	var key := GameFiles.read_raw("key.db")
	if k < 0 or k + 0x34 > key.size():
		return PackedByteArray()
	return key.slice(k, k + 0x34)

static func _last_name(key: PackedByteArray) -> String:
	return Database.cstring(key, 0x13, 16) if key.size() >= 0x34 else ""

## format_team_name with the last name only (EDX 0), cut to `width`
func _fit(s: String, width: int) -> String:
	while s.length() > 0 and scr.textwidth(s) > width:
		s = s.left(s.length() - 1)
	return s

## the goals of the season so far (SEASON.DB of the league, KEY +0x2c): the regular season or the
## play-offs block (option_flags 0x200)
func _season_goals(key: PackedByteArray) -> int:
	if key.size() < 0x34 or Session.league_dir == "":
		return 0
	var off := key.decode_s32(0x2c)
	var season := FileAccess.get_file_as_bytes(Session.league_dir.path_join("SEASON.DB"))
	var at := off + (2 if Session.option_flags & 0x200 else 0x14)
	if off < 0 or at + 2 > season.size():
		return 0
	return season.decode_u16(at)

static func ordinal(n: int) -> String:
	if n % 10 == 1 and n % 100 != 11:
		return "st"
	if n % 10 == 2 and n % 100 != 12:
		return "nd"
	if n % 10 == 3 and n % 100 != 13:
		return "rd"
	return "th"

# ---------------------------------------------------------------------------------------------
# the screen
# ---------------------------------------------------------------------------------------------

var _bkgd: Shpi.Shape
var _pal := PackedByteArray()
var _titles: Shpi                  # CTTITLE1 / 2 / 3
var _logos: Array = [null, null]   # dword_dd66c / dword_dd670: the logos of the two teams
var _font: Vfn
var _fh := 0

func _load(kind: int, home: int, away: int) -> void:
	_font = fe.fonts.get("indus030", fe.font_main)
	scr.setfont(_font)
	_fh = scr.font_height()
	var logos := fe.bank("ctlogo")
	for i in 2:
		_logos[i] = logos.find(Exe.str_ptr(LOGO_NAMES + [home, away][i] * 4)) if logos != null else null
	var bg := fe.bank("ctbkgd")
	_bkgd = bg.find("bkgd") if bg != null else null
	_pal = Screen8.shape_palette(bg.find("!pal")) if bg != null else FrontEnd._grey_palette()
	if kind & 3:
		_titles = fe.bank("cttitle2")
	elif kind & 0x1c:
		_titles = fe.bank("cttitle1")
	else:
		_titles = fe.bank("cttitle3")

func _shape(name: String) -> Shpi.Shape:
	return _titles.find(name) if _titles != null else null

func _home(name: String) -> void:
	var s := _shape(name)
	if s != null:
		scr.drawshape_remap(s, s.x, s.y)

## draw_team_logo_parts (0x7df4e): the title shapes of a page: 4 the scratches (top, tlu, scra),
## 8 / 0x10 the forwards / defence (fowa / def), 0x20 the scores around the league (colm, ots), the
## summaries (top, summ and the period: per1..per3, ot)
func draw_title_parts(kind: int, period: int) -> void:
	match kind:
		4:
			_home("top")
			_home("tlu ")
			_home("scra")
		8:
			_home("top")
			_home("tlu ")
			_home("fowa")
		0x10:
			_home("top")
			_home("tlu ")
			_home("def ")
		0x20:
			_home("colm")
			_home("ots ")
		_:
			_home("top")
			_home("summ")
			_home(["ot  ", "per1", "per2", "per3"][period] if period < 4 else "ot  ")

## drawshape_remap_centered (0x913d0): at (x, y) minus the hotspot
func _centered(s: Shpi.Shape, x: int, y: int) -> void:
	if s != null:
		scr.drawshape_remap(s, x - s.center_x, y - s.center_y)

func _page(kind: int, period: int, logos: bool) -> void:
	scr.clearclip()
	if _bkgd != null:
		scr.drawshape_remap(_bkgd, _bkgd.x, _bkgd.y)
	draw_title_parts(kind, period)
	if logos:
		_centered(_logos[0], 0x3d, 0x50)
		_centered(_logos[1], 0x221, 0x50)

## the rows of a page are cleared by drawing the background into the clip (0x80, 0x8c)..
func _clear_rows() -> void:
	scr.setclip(0x80, 0x8c, 0x280, 0x1e0)
	if _bkgd != null:
		scr.drawshape_remap(_bkgd, _bkgd.x, _bkgd.y)
	scr.clearclip()

## boxscore_screen (0x2d35a): kind 1 scoring, 2 penalties (3 both) of the periods from..to, 4 the
## scratches, 0x20 the scores around the league. Returns 4 when Esc ended it (the scores around
## the league are skipped then).
func boxscore_screen(kind: int, from_period: int, to_period: int) -> int:
	await fe.fade_loop(100)
	ui.reset_events()
	var data := summary()
	var recs := Sim.summary_records(data)
	var home := data[3] if data.size() > 4 else Session.home_team
	var away := data[4] if data.size() > 4 else Session.away_team
	if fe.game != null:
		home = fe.game.sim.teams[0].info.index if fe.game.sim.teams[0].info != null else Session.home_team
		away = fe.game.sim.teams[1].info.index if fe.game.sim.teams[1].info != null else Session.away_team
	_load(kind, home, away)
	var r := 0
	scr.set_text_colors(0x40, 0)
	if kind & 0x20 == 0:
		fe.play_loop("gamesum")
	if kind & 3:
		r = await _summary_pages(kind, from_period, to_period, recs, [_team_record(home), _team_record(away)])
	elif kind & 4:
		r = await _scratch_pages([_team_record(home), _team_record(away)])
	elif kind & 0x20:
		r = await league_scores_pages()
	await fe.leave_screen(100)
	scr.setfont(fe.font_main)
	return 4 if r == 3 else 0

## the summary pages: the goals ("BOS  Neely (12th) PP  05:12" and the assists below) and the
## penalties ("BOS  Neely  05:12", "2 min : Roughing" below) of each period, a new page when the
## rows reach y 0x177; the shots on goal of the period and of the game at the bottom
func _summary_pages(kind: int, from_period: int, to_period: int, recs: Array, teams: Array) -> int:
	# the rows of each period in the order of the records; a goal carries the scorer's goals of the
	# game up to it (unk_6d0)
	var counts := {}
	var rows := {}
	var prds: Array = []
	for rec: PackedByteArray in recs:
		match rec[0]:
			1:
				var k := rec[1] * 0x100 + rec[2]
				counts[k] = counts.get(k, 0) + 1
				if kind & 1:
					rows[rec[6]] = rows.get(rec[6], []) + [[rec, counts[k]]]
			2:
				if kind & 2:
					rows[rec[5]] = rows.get(rec[5], []) + [[rec, 0]]
			4:
				prds.append(rec)
	var r := 0
	var first := true
	for p in range(from_period, to_period + 1):
		# the pages of the period: rows of two lines from y 0xa0 until 0x177 - the font height
		var pages: Array = [[]]
		var y := 0xa0
		for row: Array in rows.get(p, []):
			if y >= 0x177 - _fh:
				pages.append([])
				y = 0xa0
			pages[-1].append(row)
			y += _fh * 2
		for pi in pages.size():
			if pi == 0:
				if not first:
					await scr.fade_out(16)
				_page(kind, p, true)
			else:
				_clear_rows()
			y = 0xa0
			var any_goal := false
			var any_penalty := false
			for row: Array in pages[pi]:
				var rec: PackedByteArray = row[0]
				if rec[0] == 1:
					_goal_row(rec, teams, y, row[1])
					any_goal = true
				else:
					_penalty_row(rec, teams, y)
					any_penalty = true
				y += _fh * 2
			if kind & 1:
				_shots_on_goal(prds, p, teams)
			if not any_goal and kind & 1:
				scr.print_text_at((500 - scr.textwidth("No Scoring.")) / 2 + 0x8c, 0x10b, "No Scoring.")
			if not any_penalty and kind & 2:
				scr.print_text_at((500 - scr.textwidth("No Penalties.")) / 2 + 0x8c, 0x10b, "No Penalties.")
			if pi == 0:
				await scr.fade_in(_pal, 16)
			first = false
			r = await ui.wait_ticks_or_input(1000)
			if r >= 2:
				return r
	return r

func _team_abbrev(rec: PackedByteArray) -> String:
	return Database.cstring(rec, 0, 5)

func _goal_row(rec: PackedByteArray, teams: Array, y: int, game_goals: int) -> void:
	var team: PackedByteArray = teams[rec[1] & 1]
	scr.print_text_at(0x96, y, _team_abbrev(team))
	var key := _player_key(team, rec[2])
	var n := game_goals + _season_goals(key)
	var s := _fit(_last_name(key), 200) + " (%d" % n + ordinal(n) + ")"
	if rec[5] & 2:
		s += " SH"
	elif rec[5] & 4:
		s += " PP"
	scr.print_text_at(0xe6, y, s)
	scr.print_text_at(0x20d, y, "%02d:%02d" % [rec[7], rec[8]])
	if rec[3] != 0xff:
		var a := "(" + _fit(_last_name(_player_key(team, rec[3])), 200)
		if rec[4] != 0xff:
			a += ", " + _fit(_last_name(_player_key(team, rec[4])), 200)
		scr.print_text_at(0xe6, y + _fh, a + ")")

func _penalty_row(rec: PackedByteArray, teams: Array, y: int) -> void:
	var team: PackedByteArray = teams[rec[1] & 1]
	scr.print_text_at(0x91, y, _team_abbrev(team))
	scr.print_text_at(0xdc, y, _last_name(_player_key(team, rec[2])))
	scr.print_text_at(0x229, y, "%02d:%02d" % [rec[6], rec[7]])
	var name := Exe.str_ptr(PENALTY_NAMES + rec[3] * 4) if rec[3] < 0x20 else ""
	var line := name if rec[4] == 0xff else "%d min : %s" % [rec[4], name]
	scr.print_text_at(0xdc, y + _fh, line)

## "Shots on goal": the period's and the game's shots of each team ("Boston 12/30")
func _shots_on_goal(prds: Array, p: int, teams: Array) -> void:
	var total := [0, 0]
	var last := [0, 0]
	for k in mini(p, prds.size()):
		var pr: PackedByteArray = prds[k]
		total[0] += pr[2]
		total[1] += pr[4]
		last = [pr[2], pr[4]]
	var t := "Shots on goal"
	scr.print_text_at((500 - scr.textwidth(t)) / 2 + 0x86, 400, t)
	var hs := "%s %d/%d" % [Database.cstring(teams[0], 0x1a, 13), last[0], total[0]]
	scr.print_text_at(0x161 - scr.textwidth(hs), 400 + _fh, hs)
	scr.print_text_at(0x1a5, 400 + _fh, "%s %d/%d" % [Database.cstring(teams[1], 0x1a, 13), last[1], total[1]])

## the scratches of the two teams (kind 4): up to 8 entries of the line table (+0x28), "Injured"
## for a player hurt for the game; the team's logo on the left
func _scratch_pages(teams: Array) -> int:
	var r := 0
	for t in 2:
		if t != 0:
			await scr.fade_out(16)
		_page(4, 0, false)
		_centered(_logos[t], 0x3d, 0x50)
		var lt := _line_table(t, teams[t])
		var y := _fh + 0x78
		for k in 8:
			var idx := lt[0x28 + k] if lt.size() > 0x28 + k else 0xff
			if idx >= 100:
				continue
			scr.print_text_at(0xb4, y, _fit(_last_name(_player_key(teams[t], idx)), 200))
			if _injured_for_game(t, idx):
				scr.print_text_at(0x226, y, "Injured")
			y += _fh + 0xe
		await scr.fade_in(_pal, 16)
		r = await ui.wait_ticks_or_input(1000)
		if r >= 2:
			break
	return r

func _line_table(side: int, rec: PackedByteArray) -> PackedByteArray:
	if fe.game != null:
		return Lines.line_table(fe.game.sim.teams[side])
	if Session.line_override.has(side):
		return Session.line_override[side]
	return rec.slice(0xbc, 0xec)

func _injured_for_game(side: int, idx: int) -> bool:
	if fe.game == null:
		return false
	var team: Team = fe.game.sim.teams[side]
	return idx >= 0 and idx < team.entity_of.size() and team.entity_of[idx] == -4

# ---------------------------------------------------------------------------------------------
# the scores around the league (league_scores_init 0x2f2b1, league_scores_advance 0x2f3d7,
# simulate_pending_games 0x18f8d, boxscore_screen 0x20)
# ---------------------------------------------------------------------------------------------

const TEAM_RATING := 0xc8922       # unk_c8922: a strength per team (the order of the games' finish)

static var games: Array = []       # unk_dd774 / dd775 / dd730 / dd788 / dd789: 6 x [a, b, status, score a, score b]
static var shown: Array = [0, 0, 0, 0, 0, 0]   # unk_dc868: the status last shown
static var done_mask := 0          # dword_c65f4: the games already simulated to the end

## league_scores_init: six other games of the night, between teams not stronger than the home team
static func league_scores_init(home: int, away: int) -> void:
	games.clear()
	done_mask = 0
	var limit := Exe.u8(TEAM_RATING + home)
	var used := [home, away]
	for g in 6:
		var a := 0
		while true:
			a = randi() % 0x1a
			if a == home or a == away or Exe.u8(TEAM_RATING + a) > limit or a in used:
				continue
			break
		used.append(a)
		var b := 0
		while true:
			b = randi() % 0x1a
			if b == a or b == home or b == away or b in used:
				continue
			break
		used.append(b)
		games.append([a, b, 0, 0, 0])
	for g in 6:
		shown[g] = 0

## league_scores_advance: each game moves on as far as the game on the ice (shifted by the
## difference of the teams' strengths): 0..2 goals for each side per period, a tie after the
## third goes to overtime (status 4) where 71 of 100 games end in a tie, else one side wins (5);
## 6 the game is over after regulation
static func league_scores_advance(period: int, home: int) -> void:
	for g in games.size():
		var game: Array = games[g]
		var target := Exe.u8(TEAM_RATING + home) - Exe.u8(TEAM_RATING + game[0]) + period
		var st: int = game[2]
		while st <= target:
			if st == 4:
				if game[3] == game[4]:
					game[2] = 4
					if randi() % 100 < 0x47:
						if randi() % 100 > 0x46:
							game[2] = 5
							game[4] += 1
					else:
						game[2] = 5
						game[3] += 1
				else:
					game[2] = 6
			elif st == 5 and game[2] == 4:
				game[2] = 5
			elif game[2] < 3 and st != game[2]:
				game[2] = st
				game[3] += randi() % 3
				game[4] += randi() % 3
			st += 1

## simulate_pending_games: one game that finished since it was last shown is played to its end by
## the off screen simulation (Season.gd); -1 when every game was shown already
static func simulate_pending_games() -> int:
	for g in games.size():
		if games[g][2] > 4 and games[g][2] != shown[g]:
			done_mask |= 1 << g
	if done_mask == 0x3f:
		return -1
	var free: Array = []
	for g in games.size():
		if done_mask & (1 << g) == 0:
			free.append(g)
	if free.is_empty():
		return -1
	var g: int = free[randi() % free.size()]
	done_mask |= 1 << g
	for k in games.size():
		shown[k] = games[k][2]
	return g

## the pages of the scores (kind 0x20): "Boston 3" over "Buffalo 2" and the period or "Final"
func league_scores_pages() -> int:
	var r := 0
	var first := true
	for g in games.size():
		var game: Array = games[g]
		var ra := _team_record(game[0])
		var rb := _team_record(game[1])
		if first:
			_page(0x20, 0, false)
		else:
			scr.setclip(0x72, 0x8c, 0x280, 0x1e0)
			if _bkgd != null:
				scr.drawshape_remap(_bkgd, _bkgd.x, _bkgd.y)
			draw_title_parts(0x20, 0)
			scr.clearclip()
		scr.print_text_at(0x74, 0xd2, Database.cstring(rb, 0x1a, 13))
		scr.print_text_at(0x118, 0xd2, str(game[4]))
		scr.print_text_at(0x74, 0x114, Database.cstring(ra, 0x1a, 13))
		scr.print_text_at(0x118, 0x114, str(game[3]))
		var st: int = game[2]
		var t: String = ["Final", "1st", "2nd", "3rd", "OT", "Final (OT)", "Final"][clampi(st, 0, 6)]
		if st > 0 and st < 4:
			t += " period"
		scr.print_text_at(400, 0xf3, t)
		if first:
			await scr.fade_in(_pal, 16)
			first = false
		r = await ui.wait_ticks_or_input(1000)
		if r >= 2:
			break
	return r

# ---------------------------------------------------------------------------------------------
# Game Statistics (team_select_screen2 0x2f5ee)
# ---------------------------------------------------------------------------------------------

const STAT_LABELS := 0xc719c       # off_c719c: Score, Shots, One Timers, ...

## the statistics of the two teams of the game: the labels of CTTITLE3 "colm" and "gsta" in the
## middle, the values of each team under its logo; 20 seconds or a click
func game_statistics() -> void:
	var sim: Sim = fe.game.sim if fe.game != null else null
	scr.black()
	scr.clearclip()
	var bg := fe.bank("ctbkgd")
	var pal := Screen8.shape_palette(bg.find("!pal")) if bg != null else FrontEnd._grey_palette()
	if bg != null:
		scr.drawshape_remap(bg.find("bkgd"), 0, 0)
	var t3 := fe.bank("cttitle3")
	if t3 != null:
		for n in ["colm", "gsta"]:
			var s := t3.find(n)
			scr.drawshape_remap(s, s.x, s.y)
	var logos := fe.bank("ctlogo")
	scr.setfont(fe.font_kaufm)
	scr.set_text_colors(0x40, 0)
	var labels := Exe.str_table(STAT_LABELS, 12)
	for i in 12:
		scr.print_text_at((0x26c - scr.textwidth(labels[i])) / 2, 0xb0 + i * 0x18, labels[i])
	for t in 2:
		var tid := Session.home_team if t == 0 else Session.away_team
		if sim != null and sim.teams[t].info != null:
			tid = sim.teams[t].info.index
		if logos != null:
			_centered(logos.find(Exe.str_ptr(LOGO_NAMES + tid * 4)), 0x40 if t == 0 else 0x212, 0x4e)
		var cx := t * 0x1c7 + 0x49
		var name := Database.cstring(_team_record(tid), 0x1a, 13)
		scr.print_text_at(cx - (scr.textwidth(name) >> 1), 0x8a, name)
		var vals := team_values(sim.teams[t] if sim != null else null)
		for i in vals.size():
			scr.print_text_at(cx - (scr.textwidth(vals[i]) >> 1), 0xb0 + i * 0x18, vals[i])
	fe.play_loop("leaguetm", 0x7f)
	await scr.fade_in(pal, 16)
	await ui.wait_ticks_or_input(2000)
	await fe.leave_screen(100)
	scr.setfont(fe.font_main)

static func _mmss(s: int) -> String:
	return "%d:%02d" % [s / 60, s % 60]

## the twelve values of a team (the team record +0x10, +0x00, +0x18, +0x02/+0x04, +0x08, +0x06,
## +0x0a/+0x0c, +0x12, +0x14, +0x24, +0x0e, +0x28/+0x26)
static func team_values(t: Team) -> Array:
	if t == null:
		return ["0", "0", "0", "0/0", "0:00", "0", "0/0", "0", "0", "0", "0:00", "0/0 (0%)"]
	var pct := t.passes_completed * 100 / t.passes if t.passes != 0 else 0
	return [str(t.goals), str(t.shots), str(t.one_timers), "%d/%d" % [t.pp_goals, t.power_plays], _mmss(t.pp_time),
		str(t.pp_shots), "%d/%d" % [t.penalty_count, t.penalty_minutes], str(t.faceoffs_won), str(t.offensive_faceoffs),
		str(t.hits), _mmss(t.zone_time), "%d/%d (%d%%)" % [t.passes_completed, t.passes, pct]]
