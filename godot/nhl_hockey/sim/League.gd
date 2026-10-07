class_name League
extends RefCounted
## A league of the front end: its directory of databases (NAME.LP with KEY, CAREER, ATT, CARTEAMS,
## TEAMS, SEASON and SCHEDULE .DB, PINFO.DB and GAME.SET), the schedule of 1092 regular season and
## 105 play-off games, the statistical simulation of the games nobody plays and the statistics the
## played games write back. Ports of new_league_dialog's file work (league_copy_files,
## pinfo_db_create, league_db_load), league_play_day / schedule_play_games, the game simulator at
## 0x452c5 (named playoff_setup_screen in the map), season_record_result, the play-off series
## routines (schedule_rank_teams, playoff_make_round1..final, playoff_round1..final_done,
## playoff_advance, schedule_screen, schedule_screen2) and league_update_standings (the end of a
## decided series).
##
## The original lets several people play one league: every human team plays in its own copies of
## the files (NAME.LP\SCHEDULE.07 ...) that the League Manager merges, and only the merge simulates
## the games of the computer teams (league_merge_check -> league_play_day mode 7). Here all human
## teams play in the .DB files themselves and the merge step runs after every played game.
##
## No autoload is used: the tests build leagues from byte arrays.

const FILES := ["KEY", "CAREER", "ATT", "CARTEAMS", "TEAMS", "SEASON", "SCHEDULE"]   # off_c80d7
const SEASON_GAMES := 0x444          # 1092 regular season games
const ALL_GAMES := 0x4ad             # + 15 series x 7 play-off games
const PLAYOFF_OFFSET := 0x199a       # 2 + 0x444 * 6
const TEAM := 0x2e8
const KEY := 0x34
const PINFO_SIZE := 0x32c

const DIVISION_TEAMS := 0xc83c3      # unk_c83c3: 4 divisions x 7 teams (99 = none)
const TEAM_DIVISION := 0xc83df       # unk_c83df: team -> division
const TEAM_DIV_SLOT := 0xc83f9       # unk_c83f9: team -> place in the division
const CONFERENCE_BITS := 0xc5519     # unk_c5519: division bit per team (1, 2 one conference, 4, 8 the other)
const CONF_A := 0xc55e9              # unk_c55e9: the 12 teams of the first conference
const CONF_B := 0xc5619              # unk_c5619: the 14 teams of the second
const MONTH_DAYS := 0xc8444          # unk_c8444: days per month (index 1..12)

var name := ""
var dir := ""
var files := {}                      # "TEAMS" -> PackedByteArray ...
var pinfo := PackedByteArray()
var game_set := PackedByteArray()
var season_over := false             # the play-offs are over (awards_screen)
var option_flags := 0x7bff           # the league's settings (period length, play-off series)

# ---------------------------------------------------------------------------------------------
# the random numbers of the Watcom C library (rand: next = next * 1103515245 + 12345, 15 bits)
# ---------------------------------------------------------------------------------------------

static var _seed := 1

static func srand(s: int) -> void:
	_seed = s & 0xffffffff

static func rand() -> int:
	_seed = (_seed * 1103515245 + 12345) & 0xffffffff
	return (_seed >> 16) & 0x7fff

## rand_below (0x45282)
static func rand_below(n: int) -> int:
	return rand() % n

# ---------------------------------------------------------------------------------------------
# files
# ---------------------------------------------------------------------------------------------

static func root() -> String:
	return "user://leagues"

## the leagues of the directory (scan_league_dirs: the directories NAME.LP)
static func list_leagues() -> PackedStringArray:
	var out := PackedStringArray()
	var d := DirAccess.open(root())
	if d == null:
		return out
	for n in d.get_directories():
		if n.to_upper().ends_with(".LP"):
			out.append(n.get_basename())
	out.sort()
	return out

func file(n: String) -> PackedByteArray:
	return files.get(n, PackedByteArray())

func save() -> void:
	DirAccess.make_dir_recursive_absolute(dir)
	for n in files:
		var f := FileAccess.open(dir.path_join(n + ".DB"), FileAccess.WRITE)
		if f != null:
			f.store_buffer(files[n])
	var p := FileAccess.open(dir.path_join("PINFO.DB"), FileAccess.WRITE)
	if p != null:
		p.store_buffer(pinfo)
	if not game_set.is_empty():
		var g := FileAccess.open(dir.path_join("GAME.SET"), FileAccess.WRITE)
		if g != null:
			g.store_buffer(game_set)

static func open(league_name: String) -> League:
	var l := League.new()
	l.name = league_name.to_upper()
	l.dir = root().path_join(l.name + ".LP")
	if not DirAccess.dir_exists_absolute(l.dir):
		return null
	for n in FILES:
		l.files[n] = FileAccess.get_file_as_bytes(l.dir.path_join(n + ".DB"))
	l.pinfo = FileAccess.get_file_as_bytes(l.dir.path_join("PINFO.DB"))
	l.game_set = FileAccess.get_file_as_bytes(l.dir.path_join("GAME.SET"))
	if l.pinfo.size() < PINFO_SIZE or l.file("SCHEDULE").size() < PLAYOFF_OFFSET + 0x276:
		return null
	if l.game_set.size() >= 0x5d:
		l.option_flags = l.game_set.decode_u32(0x59)
	l.season_over = l.games_played() >= ALL_GAMES
	return l

static func delete(league_name: String) -> void:
	var d := root().path_join(league_name.to_upper() + ".LP")
	var da := DirAccess.open(d)
	if da == null:
		return
	for f in da.get_files():
		da.remove(f)
	DirAccess.remove_absolute(d)

## new_league_dialog: the copies of the seven databases (the installation's .DB or the original
## .ORG files), PINFO.DB with the human teams, GAME.SET, and the schedule (league_db_load: the
## '93 - '94 schedule or one with the teams shuffled inside their divisions)
static func create(league_name: String, sources: Dictionary, humans: Array, random_schedule: bool, settings: PackedByteArray = PackedByteArray()) -> League:
	var l := League.new()
	l.name = league_name.to_upper()
	l.dir = root().path_join(l.name + ".LP")
	for n in FILES:
		l.files[n] = (sources.get(n, PackedByteArray()) as PackedByteArray).duplicate()
	l.pinfo = pinfo_create(humans)
	l.game_set = settings.duplicate()
	if l.game_set.size() >= 0x5d:
		l.option_flags = l.game_set.decode_u32(0x59)
	l.set_games_played(0)
	l.build_schedule(random_schedule)
	return l

## PINFO.DB (pinfo_db_create): +0 u16, +2 u16 the owner's team, +4 u16 a saved game, +6 13 bytes,
## +0x13 u16 status, +0x15 11 bytes the master password, +0x20 26 teams of 0x1e bytes: name and
## password (11 bytes each), +0x16 1, +0x17 1 for a human team, +0x18 2, +0x19 0, +0x1a u32 0
static func pinfo_create(humans: Array) -> PackedByteArray:
	var p := PackedByteArray()
	p.resize(PINFO_SIZE)
	p.encode_u16(0, humans.size())
	p.encode_u16(2, humans[0] if not humans.is_empty() else 0)
	for t in 26:
		var e := 0x20 + t * 0x1e
		p[e + 0x16] = 1
		p[e + 0x17] = 1 if humans.has(t) else 0
		p[e + 0x18] = 2
	return p

func human(team: int) -> bool:
	return team >= 0 and team < 26 and pinfo.size() >= PINFO_SIZE and pinfo[0x20 + team * 0x1e + 0x17] == 1

func humans() -> Array:
	var out: Array = []
	for t in 26:
		if human(t):
			out.append(t)
	return out

# ---------------------------------------------------------------------------------------------
# the schedule: u16 the games played, 1197 records of 6 bytes (month, day, home, away, home
# goals, away goals; 0xff = not played)
# ---------------------------------------------------------------------------------------------

func games_played() -> int:
	var s := file("SCHEDULE")
	return s.decode_u16(0) if s.size() >= 2 else 0

func set_games_played(v: int) -> void:
	files["SCHEDULE"].encode_u16(0, v)

func game(i: int) -> PackedByteArray:
	return file("SCHEDULE").slice(2 + i * 6, 8 + i * 6)

func set_game(i: int, rec: PackedByteArray) -> void:
	var s: PackedByteArray = files["SCHEDULE"]
	for k in 6:
		s[2 + i * 6 + k] = rec[k]

static func played(rec: PackedByteArray) -> bool:
	return rec[4] != 0xff and rec[5] != 0xff

## date_to_day_index (0x41c79): months before September count into the next year
static func day_index(month: int, day: int) -> int:
	return (month + 12 if month < 9 else month) * 0x1f + day

## day_to_month_day (0x41c9b): a day past the month's end moves into the next month
static func normalize_date(month: int, day: int) -> Vector2i:
	while day > Exe.u8(MONTH_DAYS + month):
		day -= Exe.u8(MONTH_DAYS + month)
		month += 1
	return Vector2i(month, day)

## league_db_load (0x42295): the teams of the schedule shuffled inside their divisions (12 swaps
## each), every team's games listed in its record (+0x11c: 84 offsets into SCHEDULE.DB), the
## play-off games cleared
func build_schedule(random: bool) -> void:
	var map := PackedInt32Array()
	map.resize(28)
	for i in 28:
		map[i] = Exe.u8(DIVISION_TEAMS + i)
	if random:
		for dv in 4:
			var n := 7 if dv > 1 else 6
			for k in 12:
				var a := rand() % n + dv * 7
				var b := rand() % n + dv * 7
				var x := map[a]
				map[a] = map[b]
				map[b] = x
	var teams: PackedByteArray = files["TEAMS"]
	var counts := PackedInt32Array()
	counts.resize(26)
	for i in SEASON_GAMES:
		var rec := game(i)
		if random:
			for k in [2, 3]:
				var t: int = rec[k]
				if t < 26:
					rec[k] = map[Exe.u8(TEAM_DIVISION + t) * 7 + Exe.u8(TEAM_DIV_SLOT + t)]
			set_game(i, rec)
		for k in [2, 3]:
			var t: int = rec[k]
			if t < 26 and counts[t] < 84:
				teams.encode_s32(t * TEAM + 0x11c + counts[t] * 4, i * 6 + 2)
				counts[t] += 1
	for i in range(SEASON_GAMES, ALL_GAMES):
		set_game(i, PackedByteArray([0xff, 0xff, 0xff, 0xff, 0xff, 0xff]))

## the next game of a team that is not played yet (the calendar's next game), -1 none
func next_game(team: int) -> int:
	for i in ALL_GAMES:
		var r := game(i)
		if r[0] != 0xff and (r[2] == team or r[3] == team) and not played(r):
			return i
	return -1

# ---------------------------------------------------------------------------------------------
# the record helpers
# ---------------------------------------------------------------------------------------------

func team_rec(t: int) -> int:
	return t * TEAM

## the KEY.DB offset of roster index r (skaters at +0x4c, goalies at +0xb0), -1 none
func key_of(t: int, r: int) -> int:
	var at := team_rec(t) + (0x4c + r * 4 if r < 25 else 0xb0 + (r - 25) * 4)
	var teams: PackedByteArray = files["TEAMS"]
	return teams.decode_s32(at) if at + 4 <= teams.size() else -1

func key_i32(k: int, off: int) -> int:
	var key: PackedByteArray = files["KEY"]
	return key.decode_s32(k + off) if k >= 0 and k + off + 4 <= key.size() else -1

static func _u16(b: PackedByteArray, at: int) -> int:
	return b.decode_u16(at) if at >= 0 and at + 2 <= b.size() else 0

static func _add16(b: PackedByteArray, at: int, v: int) -> void:
	if at >= 0 and at + 2 <= b.size():
		b.encode_u16(at, (b.decode_u16(at) + v) & 0xffff)

static func _add8(b: PackedByteArray, at: int, v: int) -> void:
	if at >= 0 and at < b.size():
		b[at] = (b[at] + v) & 0xff

static func _set16(b: PackedByteArray, at: int, v: int) -> void:
	if at >= 0 and at + 2 <= b.size():
		b.encode_u16(at, v & 0xffff)

# ---------------------------------------------------------------------------------------------
# the game simulation (0x452c5): one minute after another the lines of both teams take penalties
# and shots at the rates of the players' career statistics (scaled to 84 games); the goals follow
# from the shooter's and the opposing goalie's career percentages, the team ahead in skaters gets
# a bonus; the statistics go into the season (or play-off) blocks of SEASON.DB and TEAMS.DB
# ---------------------------------------------------------------------------------------------

static var fwd_order := [[0, 1, 2, 3, 0, 1, 2, 0, 1, 0], [0, 1, 2, 3, 0, 1, 2, 0, 1, 0]]   # unk_c900c
static var def_order := [[0, 1, 2], [0, 1, 2]]                                            # unk_c905c
var best_assist := 0                 # the value of the last assist chosen (kept between the goals)

## the career record of a skater scaled to 84 games (GP, G, A, PTS = G + A, PPG, SHG, PIM, SOG)
static func _normalize_career(c: PackedByteArray, at: int) -> void:
	var gp := _u16(c, at)
	if gp == 0:
		return
	for k in [7, 6, 5, 4, 2, 1]:
		_set16(c, at + k * 2, _u16(c, at + k * 2) * 0x54 / gp)
	_set16(c, at + 6, _u16(c, at + 2) + _u16(c, at + 4))
	_set16(c, at, 0x54)

func sim_game(index: int, career: PackedByteArray, forced := -1) -> void:
	var sched_rec := game(index)
	var tid := [sched_rec[2], sched_rec[3]]
	var score := [0, 0]
	var playoffs := index >= SEASON_GAMES
	var teams: PackedByteArray = files["TEAMS"]
	var season: PackedByteArray = files["SEASON"]
	var blk := [team_rec(tid[0]) + (0x3a if playoffs else 0x28), team_rec(tid[1]) + (0x3a if playoffs else 0x28)]
	var pen := [[0, 0, 0, 0, 0], [0, 0, 0, 0, 0]]          # abStack_11c - 0xc: minutes left of the 5 places
	var line_shots := [[0, 0, 0, 0, 0], [0, 0, 0, 0, 0]]   # abStack_11c: shots per forward line
	var pims := [[], []]                                   # abStack_174: penalties of each skater
	var shots := [[], []]                                  # abStack_1dc
	var assists := [[], []]                                # abStack_210
	var goals := [[], []]                                  # abStack_1a8
	var ps := [[], []]                                     # SEASON.DB record of each skater (-1 none)
	var pset := [[], []]                                   # its block (regular season or play-offs)
	var aps := [[], []]                                    # CAREER.DB record
	var gs := [[], []]                                     # goalies: SEASON.DB record
	var gset := [[], []]
	var ags := [[], []]                                    # CAREER.DB record
	var gkey := [[], []]
	var pkey := [[], []]
	var pim_rate := [0, 0]                                 # aiStack_88
	for t in 2:
		for p in 25:
			pims[t].append(0)
			shots[t].append(0)
			assists[t].append(0)
			goals[t].append(0)
			var k := key_of(tid[t], p)
			pkey[t].append(k)
			if k == -1:
				ps[t].append(-1)
				pset[t].append(-1)
				aps[t].append(-1)
				continue
			var c := key_i32(k, 0x28)
			_normalize_career(career, c)
			aps[t].append(c)
			pim_rate[t] += _u16(career, c + 0xc)
			var s := key_i32(k, 0x2c)
			ps[t].append(s)
			pset[t].append(s + (0x12 if playoffs else 0))
		for g in 3:
			var k := key_of(tid[t], 25 + g)
			gkey[t].append(k)
			ags[t].append(key_i32(k, 0x28) if k != -1 else -1)
			var s := key_i32(k, 0x2c) if k != -1 else -1
			gs[t].append(s)
			gset[t].append(s + (0x16 if playoffs else 0) if s != -1 else -1)
	var avail := [5, 5]                                    # local_28: places not in the penalty box
	var goalie := [0, 0]                                   # abStack_3c
	for t in 2:
		pim_rate[t] = pim_rate[t] * 1000 / 0x54
		var tr := team_rec(tid[t])
		goalie[t] = (teams[tr + 0xe1] if rand() % 1000 < 0x137 else teams[tr + 0xe0]) - 0x19
		goalie[t] = clampi(goalie[t], 0, 2)
		_add8(teams, blk[t], 1)
		_add16(season, gset[t][goalie[t]], 1)
		# every skater of the line table played: forwards, defence, power play, penalty killing, extras
		var dressed := {}
		for off in range(0xbc, 0xe4):
			if off == 0xe0 or off == 0xe1:
				continue
			var p: int = teams[tr + off]
			if p < 25:
				dressed[p] = true
		for p: int in dressed:
			_add16(season, pset[t][p], 1)
	var intervals := 15
	if option_flags & 0xc00 == 0x800:
		intervals = 0x3c
	elif option_flags & 0xc00 == 0x400:
		intervals = 0x1e
	var i := 0
	var n := 0
	var ot := 0
	var fl := 0
	var dl := 0
	var bias := [0, 0]
	# values the original keeps between the loops (the chosen player and his value)
	var chosen := 0
	var chosen_p := 0
	var best_shot := 0
	while i < intervals:
		if fl == 0:
			for t in 2:
				for k in 10:
					var j := rand_below(10)
					if j != k:
						var x: int = fwd_order[t][k]
						fwd_order[t][k] = fwd_order[t][j]
						fwd_order[t][j] = x
		if dl == 0:
			for t in 2:
				for k in 3:
					var j := rand_below(3)
					if j != k:
						var x: int = def_order[t][k]
						def_order[t][k] = def_order[t][j]
						def_order[t][j] = x
		var prev := avail.duplicate()
		for t in 2:
			avail[t] = 0
			for k in 5:
				if pen[t][k] != 0:
					pen[t][k] -= 1
				if pen[t][k] == 0:
					avail[t] += 1
			bias[t] = 0
		if prev[0] != avail[0] or prev[1] != avail[1]:
			if avail[1] < avail[0] and prev[0] <= prev[1]:
				_add16(teams, blk[0] + 0xa, 1)
				_add16(teams, blk[1] + 0xe, 1)
			elif avail[1] > avail[0] and prev[0] >= prev[1]:
				_add16(teams, blk[1] + 0xa, 1)
				_add16(teams, blk[0] + 0xe, 1)
		if avail[1] < avail[0]:
			bias[0] = (avail[0] - avail[1]) * 0x5f
			bias[1] = -(avail[0] - avail[1]) * 0x5f
		elif avail[0] < avail[1]:
			bias[1] = (avail[1] - avail[0]) * 0x5f
			bias[0] = -(avail[1] - avail[0]) * 0x5f
		for t in 2:
			var tr := team_rec(tid[t])
			var line: int = fwd_order[t][fl]
			var pair: int = def_order[t][dl]
			var places := [teams[tr + 0xbc + line * 3], teams[tr + 0xbc + line * 3 + 1], teams[tr + 0xbc + line * 3 + 2],
				teams[tr + 0xc8 + pair * 2], teams[tr + 0xc8 + pair * 2 + 1]]
			if rand_below(1000) < pim_rate[t] / 0xb4:
				# a penalty: the player of the five most due for one (career minutes per minute
				# played minus his penalties of the game)
				var slot := -1
				var bestv := 0
				for k in 5:
					var p: int = places[k]
					if p >= 25:
						continue
					var v: int = _u16(career, aps[t][p] + 0xc) * 1000 / 0x13b0 - pims[t][p] * 1000
					if (slot == -1 and k < 3) or v > bestv:
						slot = k
						bestv = v
						chosen_p = p
				if slot >= 0 and pen[t][slot] == 0:
					var minutes := 5 if rand_below(1000) < 0x3c else 2
					pen[t][slot] = minutes + 1
					_add16(season, pset[t][chosen_p] + 0xc, minutes)
					pims[t][chosen_p] += 1
					_add16(teams, blk[t] + 0x10, minutes)
					pim_rate[t] -= 1000
			else:
				var rate := _u16(career, ags[t][goalie[t]] + 0x12) * 1000 / 0x13b0
				for k in 5:
					var p: int = places[k]
					if p < 25:
						rate += _u16(career, aps[t][p] + 0xe) * 1000 / 0x13b0
				if rate * (n + 1) - line_shots[t][line] * 1000 > 1000:
					# a shot by the player of the five most due for one (not in the box)
					var sel := -1
					for k in 5:
						var p: int = places[k]
						if p >= 25:
							continue
						var v: int = _u16(career, aps[t][p] + 0xe) * 1000 / 0x13b0 - shots[t][p] * 1000
						if ((sel == -1 and k < 3) or v > best_shot) and pen[t][k] == 0:
							sel = k
							best_shot = v
							chosen = p
					var shooter := chosen
					line_shots[t][line] += 1
					shots[t][shooter] += 1
					_add16(season, pset[t][shooter] + 0xe, 1)
					# the shot counts for the shooting team's own goalie (as in the original)
					_add16(season, gset[t][goalie[t]] + 0x12, 1)
					var og: int = ags[t ^ 1][goalie[t ^ 1]]
					var gv := _u16(career, og + 0xe) * 1000 / _u16(career, og + 0x12) if _u16(career, og + 0x12) != 0 else rand() % 10 + 1
					var sc: int = aps[t][shooter]
					var sv := _u16(career, sc + 2) * 1000 / _u16(career, sc + 0xe) if _u16(career, sc + 0xe) != 0 else rand() % 10 + 1
					var prob := 1000
					if n < intervals or forced != t:
						prob = (sv + (gv - score[t] * 1000 / 0x21)) / 2 + bias[t] + 0xd
					var r := rand_below(1000)
					if (forced == 0 or forced == 1) and t != forced:
						if score[t ^ 1] - 1 <= score[t] or score[t ^ 1] == 0:
							r = prob + 1
					if r <= prob:
						_goal(t, shooter, places, tid, blk, pset, gset, goalie, score, goals, assists, pen, avail, bias, aps, career, fl, dl)
		for t in 2:
			_add16(season, gset[t][goalie[t]] + 0xc, 1)
		fl = (fl + 1) % 10
		dl = (dl + 1) % 3
		if i == intervals - 1:
			if not playoffs:
				if score[0] == score[1] and ot < 5:
					ot += 1
					i -= 1
			elif score[0] == score[1]:
				i -= 1
		i += 1
		n += 1
	_finish_game(index, tid, score, blk, gs, gset, gkey, pkey, ps, goalie, shots, goals, assists)

func _goal(t: int, scorer: int, places: Array, tid: Array, blk: Array, pset: Array, gset: Array, goalie: Array, score: Array,
		goals: Array, assists: Array, pen: Array, avail: Array, bias: Array, aps: Array, career: PackedByteArray, fl: int, dl: int) -> void:
	var teams: PackedByteArray = files["TEAMS"]
	var season: PackedByteArray = files["SEASON"]
	_add16(season, pset[t][scorer] + 2, 1)
	_add16(season, pset[t][scorer] + 6, 1)
	goals[t][scorer] += 1
	_add16(season, gset[t ^ 1][goalie[t ^ 1]] + 0xe, 1)
	_add16(teams, blk[t] + 4, 1)
	score[t] += 1
	if bias[t] > 0:
		_add16(teams, blk[t] + 8, 1)
		_add16(season, pset[t][scorer] + 8, 1)
		_add16(teams, blk[t ^ 1] + 0xc, 1)
	_add16(teams, blk[t ^ 1] + 6, 1)
	if bias[t] < 0:
		_add16(season, pset[t][scorer] + 0xa, 1)
	# plus / minus of the lines on the ice
	var ot_rec := team_rec(tid[t ^ 1])
	var oline: int = fwd_order[t ^ 1][fl]
	var opair: int = def_order[t ^ 1][dl]
	var others := [teams[ot_rec + 0xbc + oline * 3], teams[ot_rec + 0xbc + oline * 3 + 1], teams[ot_rec + 0xbc + oline * 3 + 2],
		teams[ot_rec + 0xc8 + opair * 2], teams[ot_rec + 0xc8 + opair * 2 + 1]]
	for k in 5:
		if places[k] < 25:
			_add16(season, pset[t][places[k]] + 0x10, 1)
		if others[k] < 25:
			_add16(season, pset[t ^ 1][others[k]] + 0x10, -1)
	# the assists: two of 80 percent, one of 10 when team mates are out of the box
	var r := rand_below(1000)
	var count := 0
	if r < 0x321 and avail[t] > 1:
		count = 2
	elif r < 0x385 and avail[t] != 0:
		count = 1
	var prev := 0xff
	while count > 0:
		var sel := -1
		var who := 0
		for k in 5:
			var p: int = places[k]
			if p >= 25:
				continue
			var v: int = _u16(career, aps[t][p] + 4) * 1000 / 0x13b0 - assists[t][p] * 1000
			if (sel == -1 or v > best_assist) and pen[t][k] == 0 and p != scorer and p != prev:
				sel = k
				best_assist = v
				who = p
		if sel == -1:
			count = 0
		else:
			prev = who
			assists[t][who] += 1
			_add16(season, pset[t][who] + 4, 1)
			_add16(season, pset[t][who] + 6, 1)
			count -= 1

func _finish_game(index: int, tid: Array, score: Array, blk: Array, gs: Array, gset: Array, gkey: Array, pkey: Array, ps: Array,
		goalie: Array, shots: Array, goals: Array, assists: Array) -> void:
	var teams: PackedByteArray = files["TEAMS"]
	var season: PackedByteArray = files["SEASON"]
	if score[0] == score[1]:
		_add8(teams, blk[0] + 3, 1)
		_add8(teams, blk[1] + 3, 1)
		_add16(season, gset[0][goalie[0]] + 6, 1)
		_add16(season, gset[1][goalie[1]] + 6, 1)
	else:
		var w := 0 if score[0] > score[1] else 1
		_add8(teams, blk[w] + 1, 1)
		_add8(teams, blk[w ^ 1] + 2, 1)
		_add16(season, gset[w][goalie[w]] + 2, 1)
		_add16(season, gset[w ^ 1][goalie[w ^ 1]] + 4, 1)
	# the three stars: a shutout's goalie, then (the original keeps the first entries of 0xff,
	# so the shutout star is lost and the later ones move up) the last skater with shots, goals
	# or assists, the last scorer, the last one with an assist
	var stars := [[0xff, 0xff], [0xff, 0xff], [0xff, 0xff], [0xff, 0xff]]
	var count := 0
	if score[0] == 0:
		_add16(season, gset[1][goalie[1]] + 8, 1)
		count = mini(count + 1, 4)
	if score[1] == 0:
		_add16(season, gset[0][goalie[0]] + 8, 1)
		count = mini(count + 1, 4)
	for pass_ in 3:
		var sel := [0, 0]
		for t in 2:
			for p in 25:
				var v: int
				match pass_:
					0:
						v = shots[t][p] + assists[t][p] + goals[t][p] * 2
					1:
						v = goals[t][p]
					_:
						v = assists[t][p]
				if v > 0:
					sel = [t, p]
		if count < 4:
			stars[count] = sel
			count += 1
	for k in 3:
		var st: Array = stars[k]
		if st[0] == 0xff or st[1] == 0xff:
			continue
		var t: int = st[0]
		var p: int = st[1]
		var key: PackedByteArray = files["KEY"]
		var k_off: int = pkey[t][p] if p < 25 else gkey[t][p - 25]
		if k_off < 0:
			continue
		if key[k_off + 2] == 0x47:
			_add16(season, gs[t][p - 25 if p >= 25 else 0] + 0x30 + k * 2, 1)
		elif p < 25:
			_add16(season, ps[t][p] + 0x28 + k * 2, 1)
	for t in 2:
		_goalie_averages(season, gset[t][goalie[t]])
	var rec := game(index)
	rec[4] = score[0]
	rec[5] = score[1]
	set_game(index, rec)

## the goals against average (x100, per game) and the save percentage (x1000) of a goalie block
static func _goalie_averages(season: PackedByteArray, b: int) -> void:
	if b < 0:
		return
	var gp := _u16(season, b)
	_set16(season, b + 0x10, _u16(season, b + 0xe) * 100 / gp if gp != 0 else 0)
	var sa := _u16(season, b + 0x12)
	_set16(season, b + 0x14, ((sa - _u16(season, b + 0xe)) * 1000 + sa / 2) / sa if sa != 0 else 0)

# ---------------------------------------------------------------------------------------------
# a day of the league (league_play_day 0x41cc4, schedule_play_games 0x42631)
# ---------------------------------------------------------------------------------------------

## the games up to the date of game index - 1 that nobody played: mode 1 those of two human
## teams, 2 of one, 4 of none (7 all); team limits it to one team's games. With mode 7 and no
## human game left after the date the rest of the season is simulated and the play-offs begin;
## in the play-offs the rounds move on (schedule_screen2)
func play_day(index: int, team: int, mode: int) -> void:
	if index <= 0:
		return
	var career: PackedByteArray = file("CAREER").duplicate()
	if index < 0x445 and not (index == SEASON_GAMES and game(SEASON_GAMES)[2] != 0xff and game(SEASON_GAMES)[3] != 0xff):
		_schedule_play_games(index, team, mode, career)
	else:
		_playoff_progress(team, mode, career)

func _schedule_play_games(index: int, team: int, mode: int, career: PackedByteArray) -> void:
	var target := game(index - 1)
	var day := day_index(target[0], target[1])
	var stop := false
	var last := 0
	var i := 0
	while i < SEASON_GAMES and not stop:
		var r := game(i)
		if day_index(r[0], r[1]) > day:
			if r[2] != 0xff and r[3] != 0xff and (human(r[2]) or human(r[3])):
				stop = true
		else:
			last = i
			var hc := (1 if human(r[2]) else 0) + (1 if human(r[3]) else 0)
			if not played(r) and (team == -1 or r[2] == team or r[3] == team) \
					and ((mode & 1 and hc == 2) or (mode & 4 and hc == 0) or (mode & 2 and hc == 1)):
				sim_game(i, career)
		i += 1
	if mode == 7 and not stop and last < SEASON_GAMES:
		set_games_played(SEASON_GAMES)
		for k in range(last, SEASON_GAMES):
			if not played(game(k)):
				sim_game(k, career)
		_season_end(career)

# ---------------------------------------------------------------------------------------------
# the play-offs: 16 teams (8 of each conference by points), series 0..7 the first round
# (0x444 + series * 7 + game), 8..11 the second, 12, 13 the conference finals, 14 the final
# ---------------------------------------------------------------------------------------------

func series_length() -> int:
	return (option_flags >> 12) & 7

func _team_points(t: int) -> Array:
	var teams: PackedByteArray = files["TEAMS"]
	var b := team_rec(t) + 0x28
	return [teams[b + 1] * 2 + teams[b + 3], teams[b + 1], _u16(teams, b + 4), _u16(teams, b + 6)]

## sort_teams_by_points (0x42daa): points, wins, goals for, then fewer goals against, then the
## higher team number first
func _sort_by_points(list: Array) -> void:
	for a in list.size() - 1:
		for b in range(a + 1, list.size()):
			var pa := _team_points(list[a])
			var pb := _team_points(list[b])
			var swap := false
			if pa[0] != pb[0]:
				swap = pa[0] < pb[0]
			elif pa[1] != pb[1]:
				swap = pa[1] < pb[1]
			elif pa[2] != pb[2]:
				swap = pa[2] < pb[2]
			elif pa[3] != pb[3]:
				swap = pb[3] < pa[3]
			else:
				swap = list[a] < list[b]
			if swap:
				var x: int = list[a]
				list[a] = list[b]
				list[b] = x

## schedule_rank_teams (0x42bba): each conference sorted, a division winner second if the first
## two are of the same division
func rank_teams() -> Array:
	var out: Array = []
	for c in 2:
		var n := 12 if c == 0 else 14
		var bits := 3 if c == 0 else 0xc
		var list: Array = []
		for i in n:
			list.append(Exe.i32((CONF_A if c == 0 else CONF_B) + i * 4))
		_sort_by_points(list)
		if Exe.i32(CONFERENCE_BITS + list[0] * 4) | Exe.i32(CONFERENCE_BITS + list[1] * 4) != bits:
			var k := 2
			while k < n and Exe.i32(CONFERENCE_BITS + list[0] * 4) | Exe.i32(CONFERENCE_BITS + list[k] * 4) != bits:
				k += 1
			if k < n:
				var x: int = list[k]
				list.remove_at(k)
				list.insert(1, x)
		out.append_array(list)
		if c == 0:
			out.append_array([-1, -1])
	return out

## playoff_set_series (0x42f42): home and away of the games of a series, the better team A
## (best of 7: 2-2-1-1-1, or 2-3-2 for two teams of the two divisions of a conference)
static func set_series(po: PackedByteArray, series: int, a: int, b: int, n: int) -> void:
	var base := series * 7 * 6
	var pattern: Array
	if n == 7:
		var same := Exe.i32(CONFERENCE_BITS + a * 4) | Exe.i32(CONFERENCE_BITS + b * 4) == 3
		pattern = [0, 0, 1, 1, 1, 0, 0] if same else [0, 0, 1, 1, 0, 1, 0]
	elif n == 5:
		pattern = [0, 0, 1, 1, 0]
	elif n == 3:
		pattern = [0, 1, 0]
	else:
		pattern = [0]
	for g in pattern.size():
		po[base + g * 6 + 2] = a if pattern[g] == 0 else b
		po[base + g * 6 + 3] = b if pattern[g] == 0 else a

func _playoffs() -> PackedByteArray:
	return file("SCHEDULE").slice(PLAYOFF_OFFSET, PLAYOFF_OFFSET + 0x276)

func _store_playoffs(po: PackedByteArray) -> void:
	var s: PackedByteArray = files["SCHEDULE"]
	for k in 0x276:
		s[PLAYOFF_OFFSET + k] = po[k]

## series_winner (0x87760): the team that won n / 2 + 1 games, -1 while undecided
static func series_winner(po: PackedByteArray, series: int, n: int) -> int:
	var need := n / 2 + 1
	var base := series * 42
	var a: int = po[base + 2]
	var b: int = po[base + 3]
	var wa := 0
	var wb := 0
	var g := 0
	while wa < need and wb < need:
		if g >= 7 or po[base + g * 6 + 4] == 0xff:
			return -1
		var home: int = po[base + g * 6 + 2]
		var hg: int = po[base + g * 6 + 4]
		var ag: int = po[base + g * 6 + 5]
		if (home == a) == (hg > ag):
			wa += 1
		else:
			wb += 1
		g += 1
	return a if wa > wb else b

## playoff_series_count (0x42221): the length of a series from its scheduled games
static func series_count(po: PackedByteArray, series: int) -> int:
	var k := 0
	while k < 7 and po[series * 42 + k * 6] != 0xff:
		k += 1
	match k:
		1:
			return 1
		2:
			return 3
		3:
			return 5 if series_winner(po, series, 5) >= 0 else 3
		4, 5:
			return 7 if series_winner(po, series, 7) >= 0 else 5
	return 7

## the human teams' play-off games in their records (+0x26c: 4 rounds x 7 offsets)
func _list_playoff_games(t: int, round_base: int, first_series_game: int, n: int, reset := false) -> void:
	if not human(t):
		return
	var teams: PackedByteArray = files["TEAMS"]
	var at := team_rec(t) + 0x26c
	if reset:
		for k in 28:
			teams.encode_s32(at + k * 4, -1)
	for g in n:
		teams.encode_s32(at + (round_base + g) * 4, (first_series_game + g) * 6 + 2)

## playoff_make_round1 (0x42fed): 1st - 8th, 2nd - 7th ... of each conference in April
func make_round1(order: Array, po: PackedByteArray, n: int) -> bool:
	for s in 8:
		_list_playoff_games(order[s], 0, 0, 0, true)
		_list_playoff_games(order[s + 14], 0, 0, 0, true)
	for s in 4:
		for t in [order[s], order[7 - s]]:
			_list_playoff_games(t, 0, SEASON_GAMES + s * 7, n)
		for t in [order[s + 14], order[21 - s]]:
			_list_playoff_games(t, 0, SEASON_GAMES + 0x1c + s * 7, n)
	for s in 4:
		set_series(po, s, order[s], order[7 - s], n)
		set_series(po, 4 + s, order[14 + s], order[21 - s], n)
	for g in n:
		for s in 8:
			po[(s * 7 + g) * 6] = 4
			po[(s * 7 + g) * 6 + 1] = 0x11 + g * 2 if s < 4 else 0x10 + g * 2
	var any := false
	for t in order:
		if t >= 0 and human(t):
			any = true
	return any

## playoff_round1_done .. playoff_final_done: the games of a round nobody plays are simulated, the
## games a decided series did not need are taken out
func round_done(po: PackedByteArray, first_series: int, count: int, career: PackedByteArray) -> void:
	for s in range(first_series, first_series + count):
		var n := series_count(po, s)
		var wins := {}
		for g in n:
			var base := (s * 7 + g) * 6
			var a: int = po[s * 42 + 2]
			var b: int = po[s * 42 + 3]
			if wins.get(a, 0) == n / 2 + 1 or wins.get(b, 0) == n / 2 + 1:
				for k in 4:
					po[base + k] = 0xff
				continue
			if po[base + 4] == 0xff:
				_store_playoffs(po)
				sim_game(SEASON_GAMES + s * 7 + g, career)
				var rec := game(SEASON_GAMES + s * 7 + g)
				po[base + 4] = rec[4]
				po[base + 5] = rec[5]
			var w: int = po[base + 2] if po[base + 4] > po[base + 5] else po[base + 3]
			wins[w] = wins.get(w, 0) + 1

## the day after the last game of a round
func _round_start(po: PackedByteArray, first_series: int, count: int) -> Vector2i:
	var best := Vector2i(4, 1)
	for s in range(first_series, first_series + count):
		for g in 7:
			var base := (s * 7 + g) * 6
			if po[base] != 0xff and po[base + 4] != 0xff:
				if day_index(po[base], po[base + 1]) > day_index(best.x, best.y):
					best = Vector2i(po[base], po[base + 1])
	return Vector2i(best.x, best.y + 1)

## the winners of two series in the seeding order: a better seed that won keeps its place
func _winners(po: PackedByteArray, series: Array, n: int) -> Array:
	var slots := []
	slots.resize(series.size() * 2)
	slots.fill(-1)
	for k in series.size():
		var s: int = series[k]
		var w := series_winner(po, s, series_count(po, s))
		if w == po[s * 42 + 2]:
			slots[k] = w
		else:
			slots[slots.size() - 1 - k] = w
	var out: Array = []
	for w in slots:
		if w >= 0 and w < 26:
			out.append(w)
	return out

## playoff_make_round2 / round3 / final: the next round's series, dates after the last game
func make_next_round(po: PackedByteArray, round_index: int) -> bool:
	var n := series_length()
	var any := false
	match round_index:
		1:
			var d := _round_start(po, 0, 8)
			for g in n:
				for s in [10, 11]:
					var dt := normalize_date(d.x, d.y)
					po[(s * 7 + g) * 6] = dt.x
					po[(s * 7 + g) * 6 + 1] = dt.y
				for s in [8, 9]:
					var dt := normalize_date(d.x, d.y + 1)
					po[(s * 7 + g) * 6] = dt.x
					po[(s * 7 + g) * 6 + 1] = dt.y
				d.y += 2
			for c in 2:
				var w := _winners(po, [c * 4, c * 4 + 1, c * 4 + 2, c * 4 + 3], n)
				if w.size() < 4:
					continue
				set_series(po, 8 + c * 2, w[0], w[3], n)
				set_series(po, 9 + c * 2, w[1], w[2], n)
				for k in 4:
					var s := 8 + c * 2 + (0 if k == 0 or k == 3 else 1)
					_list_playoff_games(w[k], 7, SEASON_GAMES + s * 7, n)
					any = any or human(w[k])
		2:
			var d := _round_start(po, 8, 4)
			for g in n:
				for s in [12, 13]:
					var dt := normalize_date(d.x, d.y + (0 if s == 13 else 1))
					po[(s * 7 + g) * 6] = dt.x
					po[(s * 7 + g) * 6 + 1] = dt.y
				d.y += 2
			for c in 2:
				var w := _winners(po, [8 + c * 2, 9 + c * 2], n)
				if w.size() < 2:
					continue
				set_series(po, 12 + c, w[0], w[1], n)
				for t in w:
					_list_playoff_games(t, 14, SEASON_GAMES + (12 + c) * 7, n)
					any = any or human(t)
		3:
			var d := _round_start(po, 12, 2)
			d.y -= 1
			for g in n:
				d.y += 2
				var dt := normalize_date(d.x, d.y)
				d = dt
				po[(14 * 7 + g) * 6] = dt.x
				po[(14 * 7 + g) * 6 + 1] = dt.y
			var f: Array = [series_winner(po, 12, series_count(po, 12)), series_winner(po, 13, series_count(po, 13))]
			if f[0] >= 0 and f[1] >= 0:
				_sort_by_points(f)
				set_series(po, 14, f[0], f[1], n)
				for t in f:
					_list_playoff_games(t, 21, SEASON_GAMES + 14 * 7, n)
					any = any or human(t)
	return any

const ROUND_SERIES := [[0, 8], [8, 4], [12, 2], [14, 1]]

## playoff_advance (0x44899): the rounds from `round_index` played to the end; the awards
func _advance(po: PackedByteArray, round_index: int, career: PackedByteArray) -> void:
	for r in range(round_index, 4):
		round_done(po, ROUND_SERIES[r][0], ROUND_SERIES[r][1], career)
		if r < 3:
			make_next_round(po, r + 1)
		_store_playoffs(po)
	set_games_played(ALL_GAMES)
	season_over = true

## schedule_screen (0x428ab): the regular season is over: the first round, all of the play-offs
## when no human team is in them
func _season_end(career: PackedByteArray) -> void:
	var order := rank_teams()
	var po := _playoffs()
	for k in po.size():
		po[k] = 0xff
	var humans_in := make_round1(order, po, series_length())
	_store_playoffs(po)
	if not humans_in:
		_advance(po, 0, career)

## schedule_screen2 (0x44a41): when no human team has a play-off game left in the round, the
## round is finished and the next one made (all the rest when no human team is in it)
func _playoff_progress(team: int, mode: int, career: PackedByteArray) -> void:
	var po := _playoffs()
	for s in 15:
		for g in 7:
			var base := (s * 7 + g) * 6
			if po[base + 2] != 0xff and po[base + 3] != 0xff and (human(po[base + 2]) or human(po[base + 3])) \
					and po[base] != 0xff and po[base + 1] != 0xff and (po[base + 4] == 0xff or po[base + 5] == 0xff):
				return
	if mode != 7 or team != -1:
		return
	var h := games_played()
	var r := 0
	if h < 0x47c:
		r = 0
	elif h < 0x498:
		r = 1
	elif h < 0x4a6:
		r = 2
	elif h < ALL_GAMES:
		r = 3
	else:
		return
	round_done(po, ROUND_SERIES[r][0], ROUND_SERIES[r][1], career)
	_store_playoffs(po)
	if r == 3:
		set_games_played(ALL_GAMES)
		season_over = true
		return
	var humans_next := make_next_round(po, r + 1)
	_store_playoffs(po)
	set_games_played([0x47c, 0x498, 0x4a6][r])
	if not humans_next:
		_advance(po, r + 1, career)

## league_update_standings (0x41f64): a decided series does not need its remaining games
func trim_series(index: int) -> void:
	if index < SEASON_GAMES:
		return
	var series_first := index - (index - SEASON_GAMES) % 7
	var round_base := 0 if index < 0x47c else (7 if index < 0x498 else (14 if index < 0x4a6 else 21))
	var count := 0
	var first := game(series_first)
	for g in 7:
		var r := game(series_first + g)
		if r[2] != 0xff and r[3] != 0xff:
			count += 1
	var need := (count + 1) / 2
	var wins := {}
	var teams: PackedByteArray = files["TEAMS"]
	for g in count:
		var r := game(series_first + g)
		if wins.get(first[2], 0) == need or wins.get(first[3], 0) == need:
			r[0] = 0xff
			r[1] = 0xff
			r[4] = 0xff
			r[5] = 0xff
			set_game(series_first + g, r)
			for t in [first[2], first[3]]:
				if human(t):
					teams.encode_s32(team_rec(t) + 0x26c + (round_base + g) * 4, -1)
		elif played(r):
			var w: int = r[2] if r[4] > r[5] else r[3]
			wins[w] = wins.get(w, 0) + 1

# ---------------------------------------------------------------------------------------------
# the result of a played game (season_record_result 0x3626d)
# ---------------------------------------------------------------------------------------------

## the team record's season (or play-off) block, the three stars, the skaters who dressed (the
## line table without its 8 scratches) and the goalies who played (the goalie of record is the
## one in the net at the winning goal, from the game summary)
func record_result(team: int, side: int, index: int, sim: Sim) -> void:
	var teams: PackedByteArray = files["TEAMS"]
	var season: PackedByteArray = files["SEASON"]
	var key: PackedByteArray = files["KEY"]
	var playoffs := index >= SEASON_GAMES
	var b := team_rec(team) + (0x3a if playoffs else 0x28)
	var mine: Team = sim.teams[side]
	var other: Team = sim.teams[side ^ 1]
	var hg: int = sim.teams[0].goals
	var ag: int = sim.teams[1].goals
	_add8(teams, b, 1)
	var winner := -1
	var gwg := 0
	if hg > ag:
		winner = 0
		gwg = ag + 1
		_add8(teams, b + (1 if side == 0 else 2), 1)
	elif ag > hg:
		winner = 1
		gwg = hg + 1
		_add8(teams, b + (2 if side == 0 else 1), 1)
	else:
		_add8(teams, b + 3, 1)
	_add16(teams, b + 4, mine.goals)
	_add16(teams, b + 6, other.goals)
	_add16(teams, b + 0xa, mine.power_plays)
	_add16(teams, b + 8, mine.pp_goals)
	_add16(teams, b + 0xe, other.power_plays)
	_add16(teams, b + 0xc, other.pp_goals)
	# the penalty minutes of the other team's record (+0xc), as the original adds them
	_add16(teams, b + 0x10, other.penalty_minutes)
	# the stars
	for k in mini(sim.stars.size(), 3):
		var st: Array = sim.stars[k]
		if st[0] != side:
			continue
		var kk := key_of(team, st[1])
		if kk < 0:
			continue
		var s := key_i32(kk, 0x2c)
		if key[kk + 2] == 0x47:
			_add16(season, s + 0x30 + k * 2, 1)
		else:
			_add16(season, s + 0x28 + k * 2, 1)
	# the goalies of record: in the nets at the winning goal (a tie: at the end)
	var lt := Lines.line_table(mine)
	var in_net := [InfoPanel._goalie_byte(sim, 0), InfoPanel._goalie_byte(sim, 1)]
	if winner >= 0:
		var n := [0, 0]
		for r: PackedByteArray in sim.gs_records:
			if r[0] == 1:
				n[r[1]] += 1
				if r[1] == winner and n[winner] == gwg:
					in_net[winner] = r[9]
					in_net[winner ^ 1] = r[10]
	var of_record: int = in_net[side]
	# the skaters: all but the scratches
	var scratched := {}
	for k in 8:
		if lt.size() > 0x28 + k and lt[0x28 + k] < 25:
			scratched[lt[0x28 + k]] = true
	for p in 25:
		var kk := key_of(team, p)
		if kk < 0 or scratched.has(p):
			continue
		var s := key_i32(kk, 0x2c) + (0x12 if playoffs else 0)
		var st: PackedInt32Array = mine.player_stats[p]
		_add16(season, s, 1)
		_add16(season, s + 2, st[Team.ST_GOALS])
		_add16(season, s + 4, st[Team.ST_ASSISTS])
		_add16(season, s + 6, st[Team.ST_GOALS] + st[Team.ST_ASSISTS])
		_add16(season, s + 0xc, st[Team.ST_PIM])
		_add16(season, s + 0x10, st[Team.ST_PLUS_MINUS])
		_add16(season, s + 8, st[Team.ST_PPG])
		_add16(season, s + 0xa, st[Team.ST_SHG])
		_add16(season, s + 0xe, st[Team.ST_SHOTS])
	# the goalies dressed (line table +0x24, +0x25) who played
	var dressed := {}
	for k in 2:
		if lt.size() > 0x24 + k and lt[0x24 + k] >= 25 and lt[0x24 + k] < 28:
			dressed[lt[0x24 + k] - 25] = true
	for g in 3:
		var kk := key_of(team, 25 + g)
		if kk < 0 or not dressed.has(g):
			continue
		var gst: PackedInt32Array = mine.goalie_stats[g]
		if gst[0] == 0:
			continue
		var s := key_i32(kk, 0x2c) + (0x16 if playoffs else 0)
		_add16(season, s, 1)
		_add16(season, s + 0xc, gst[0] / 60)
		_add16(season, s + 0x12, gst[1])
		_add16(season, s + 0xe, gst[2])
		if of_record == g + 0x19:
			if winner < 0:
				_add16(season, s + 6, 1)
			elif winner == side:
				_add16(season, s + 2, 1)
			else:
				_add16(season, s + 4, 1)
			if other.goals == 0:
				_add16(season, s + 8, 1)
		_goalie_averages(season, s)

## after a game of a human team (league_calendar_flow): its score in the schedule, the games
## played, the end of a decided series; its statistics, then the games up to its date
## (league_play_day mode 2 for the skipped games of the team, mode 7 for everybody's, the merge)
func game_played(index: int, sim: Sim) -> void:
	var rec := game(index)
	rec[4] = sim.teams[0].goals
	rec[5] = sim.teams[1].goals
	set_game(index, rec)
	if index < SEASON_GAMES:
		if games_played() < index + 1:
			set_games_played(index + 1)
	else:
		trim_series(index)
	for side in 2:
		if human(rec[2 + side]):
			record_result(rec[2 + side], side, index, sim)
	play_day(index if index < SEASON_GAMES else index - 1, rec[2] if human(rec[2]) else rec[3], 2)
	play_day(games_played() if index < SEASON_GAMES else index, -1, 7)
