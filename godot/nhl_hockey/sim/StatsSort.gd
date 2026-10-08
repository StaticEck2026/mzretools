class_name StatsSort
## The comparators of the statistics screens, ported literally for the library's qsort
## (Clib.qsort): the elements are numbers of records in the tables the screens load, laid out as in
## the original's memory: the teams' records (dword_dd108, 0x4c bytes each, the season block at
## +0x28, the play-offs' at +0x3a), the skaters' (dword_dd110, 0x2f bytes, +0x12 for the
## play-offs) and the goalies' statistics (dword_dd114, 0x36 bytes, +0x16), and a value per element
## the screen computed (dword_dd118: the shooting, power play and penalty killing percentages, the
## penalty minutes per game). stats_playoffs picks the block.
##
## The returns are the original's: differences of the fields, the elements' numbers on a full tie
## of a team table; the power play and penalty killing ratios answer only 1 or 0 (setg / setl), so
## the order of those tables depends on the exact sort, as in the original.
##
## A team's block: +0 games, +1 wins, +2 losses, +3 ties, +4 goals for, +6 goals against, +8 / +0xa
## power play goals / advantages, +0xc / +0xe short handed goals against / times short handed,
## +0x10 penalty minutes. A skater's: +0 games, +2 goals, +4 assists, +6 points, +8 power play
## goals, +0xa short handed goals, +0xc penalty minutes, +0xe shots, +0x10 plus/minus (signed). A
## goalie's: +0 games, +2 wins, +4 losses, +6 ties, +0xc minutes, +0xe goals against, +0x10 goals
## against average, +0x14 save percentage.

var teams := PackedByteArray()        # dword_dd108
var skaters := PackedByteArray()      # dword_dd110
var goalies := PackedByteArray()      # dword_dd114
var values := PackedInt32Array()      # dword_dd118
var playoffs := false                 # stats_playoffs

func _t(i: int) -> int:
	return i * 0x4c + (0x3a if playoffs else 0x28)

func _s(i: int) -> int:
	return i * 0x2f + (0x12 if playoffs else 0)

func _g(i: int) -> int:
	return i * 0x36 + (0x16 if playoffs else 0)

func _tb(o: int) -> int:
	return teams[o]

func _tw(o: int) -> int:
	return teams.decode_u16(o)

func _sw(o: int) -> int:
	return skaters.decode_u16(o)

func _gw(o: int) -> int:
	return goalies.decode_u16(o)

## the plus/minus: the high word of the dword at +0xe, signed
func _pm(o: int) -> int:
	return skaters.decode_s16(o + 0x10)

static func _s32(v: int) -> int:
	v &= 0xffffffff
	return v - 0x100000000 if v >= 0x80000000 else v

# ---------------------------------------------------------------------------------------------
# the team tables (funcptr_c6ae0, team_stats_screen)
# ---------------------------------------------------------------------------------------------

## the tail of the team comparators: the points (2 a win, 1 a tie), then the wins, then the order
## of the elements
func _team_points_tail(a: int, b: int, ra: int, rb: int) -> int:
	var pb := _tb(rb + 1) * 2 + _tb(rb + 3)
	var pa := _tb(ra + 1) * 2 + _tb(ra + 3)
	if pa != pb:
		return pb - pa
	if _tb(rb + 1) != _tb(ra + 1):
		return _tb(rb + 1) - _tb(ra + 1)
	return a - b

## cmp_team_scoring (0x22f3f): goals for, fewer games, the points, the wins
func cmp_team_scoring(a: int, b: int) -> int:
	var ra := _t(a)
	var rb := _t(b)
	if _tw(rb + 4) != _tw(ra + 4):
		return _tw(rb + 4) - _tw(ra + 4)
	if _tb(rb) != _tb(ra):
		return _tb(ra) - _tb(rb)
	return _team_points_tail(a, b, ra, rb)

## cmp_team_defense (0x23062): fewer goals against, more games, the points, the wins
func cmp_team_defense(a: int, b: int) -> int:
	var ra := _t(a)
	var rb := _t(b)
	if _tw(rb + 6) != _tw(ra + 6):
		return _tw(ra + 6) - _tw(rb + 6)
	if _tb(rb) != _tb(ra):
		return _tb(rb) - _tb(ra)
	return _team_points_tail(a, b, ra, rb)

## cmp_team_penalty_killing (0x232b8): the value, then the ratio of the goals against short handed
## to the times short handed (1 when b's is the larger, else 0), the times short handed, the
## games, the points, the wins
func cmp_team_penalty_killing(a: int, b: int) -> int:
	if values[b] != values[a]:
		return values[b] - values[a]
	var ra := _t(a)
	var rb := _t(b)
	var d := _s32(_tw(rb + 0xc) * _tw(ra + 0xe) - _tw(ra + 0xc) * _tw(rb + 0xe))
	if d != 0:
		return 1 if d < 0 else 0
	if _tw(rb + 0xe) != _tw(ra + 0xe):
		return _tw(rb + 0xe) - _tw(ra + 0xe)
	if _tb(rb) != _tb(ra):
		return _tb(rb) - _tb(ra)
	return _team_points_tail(a, b, ra, rb)

## cmp_team_power_play (0x2312e): the value, then the ratio of the power play goals to the
## advantages (1 when b's is the larger, else 0), the advantages, the games, the points, the wins
func cmp_team_power_play(a: int, b: int) -> int:
	if values[b] != values[a]:
		return values[b] - values[a]
	var ra := _t(a)
	var rb := _t(b)
	var d := _s32(_tw(rb + 8) * _tw(ra + 0xa) - _tw(ra + 8) * _tw(rb + 0xa))
	if d != 0:
		return 1 if d > 0 else 0
	if _tw(rb + 0xa) != _tw(ra + 0xa):
		return _tw(rb + 0xa) - _tw(ra + 0xa)
	if _tb(rb) != _tb(ra):
		return _tb(rb) - _tb(ra)
	return _team_points_tail(a, b, ra, rb)

## cmp_team_penalties (0x23438): the value (fewer first), the games, fewer penalty minutes, the
## points, the wins
func cmp_team_penalties(a: int, b: int) -> int:
	if values[b] != values[a]:
		return values[a] - values[b]
	var ra := _t(a)
	var rb := _t(b)
	if _tb(rb) != _tb(ra):
		return _tb(rb) - _tb(ra)
	if _tw(rb + 0x10) != _tw(ra + 0x10):
		return _tw(ra + 0x10) - _tw(rb + 0x10)
	return _team_points_tail(a, b, ra, rb)

## cmp_team_standings (0x22df1): the points, fewer games, the wins, goals for, fewer goals against
func cmp_team_standings(a: int, b: int) -> int:
	var ra := _t(a)
	var rb := _t(b)
	var pb := _tb(rb + 1) * 2 + _tb(rb + 3)
	var pa := _tb(ra + 1) * 2 + _tb(ra + 3)
	if pa != pb:
		return pb - pa
	if _tb(rb) != _tb(ra):
		return _tb(ra) - _tb(rb)
	if _tb(rb + 1) != _tb(ra + 1):
		return _tb(rb + 1) - _tb(ra + 1)
	if _tw(rb + 4) != _tw(ra + 4):
		return _tw(rb + 4) - _tw(ra + 4)
	if _tw(rb + 6) != _tw(ra + 6):
		return _tw(ra + 6) - _tw(rb + 6)
	return a - b

## funcptr_c6ae0: the comparator of a team table (0 scoring, 1 defence, 2 penalty killing, 3 power
## play, 4 penalties, 5 the standings)
func team_comparator(kind: int) -> Callable:
	return [cmp_team_scoring, cmp_team_defense, cmp_team_penalty_killing, cmp_team_power_play,
		cmp_team_penalties, cmp_team_standings][kind]

# ---------------------------------------------------------------------------------------------
# the leaders (funcptr_c6be8, stats_table) and a team's roster (player_stats_screen)
# ---------------------------------------------------------------------------------------------

## cmp_leaders_points (0x1fb7f): a player without games last, the points, fewer games, the goals,
## the plus/minus
func cmp_leaders_points(a: int, b: int) -> int:
	var ra := _s(a)
	var rb := _s(b)
	if (_sw(rb) == 0) != (_sw(ra) == 0):
		return _sw(rb) - _sw(ra)
	if _sw(rb + 6) != _sw(ra + 6):
		return _sw(rb + 6) - _sw(ra + 6)
	if _sw(ra) != _sw(rb):
		return _sw(ra) - _sw(rb)
	if _sw(rb + 2) != _sw(ra + 2):
		return _sw(rb + 2) - _sw(ra + 2)
	return _pm(rb) - _pm(ra)

## cmp_leaders_goals (0x25144): the goals, fewer games, the points, the plus/minus
func cmp_leaders_goals(a: int, b: int) -> int:
	var ra := _s(a)
	var rb := _s(b)
	if _sw(rb + 2) != _sw(ra + 2):
		return _sw(rb + 2) - _sw(ra + 2)
	if _sw(rb) != _sw(ra):
		return _sw(ra) - _sw(rb)
	if _sw(rb + 6) != _sw(ra + 6):
		return _sw(rb + 6) - _sw(ra + 6)
	return _pm(rb) - _pm(ra)

## cmp_leaders_assists (0x25237): the assists, more games, the points, the plus/minus
func cmp_leaders_assists(a: int, b: int) -> int:
	var ra := _s(a)
	var rb := _s(b)
	if _sw(rb + 4) != _sw(ra + 4):
		return _sw(rb + 4) - _sw(ra + 4)
	if _sw(rb) != _sw(ra):
		return _sw(rb) - _sw(ra)
	if _sw(rb + 6) != _sw(ra + 6):
		return _sw(rb + 6) - _sw(ra + 6)
	return _pm(rb) - _pm(ra)

## the power play / short handed goals / penalty minutes leaders (cmp_leaders_pp_goals 0x25325,
## cmp_leaders_sh_goals 0x25438, cmp_leaders_penalty_minutes 0x25642): the field, fewer games,
## the points, the goals, the plus/minus
func _leaders_field(a: int, b: int, field: int) -> int:
	var ra := _s(a)
	var rb := _s(b)
	if _sw(rb + field) != _sw(ra + field):
		return _sw(rb + field) - _sw(ra + field)
	if _sw(rb) != _sw(ra):
		return _sw(ra) - _sw(rb)
	if _sw(rb + 6) != _sw(ra + 6):
		return _sw(rb + 6) - _sw(ra + 6)
	if _sw(rb + 2) != _sw(ra + 2):
		return _sw(rb + 2) - _sw(ra + 2)
	return _pm(rb) - _pm(ra)

func cmp_leaders_pp_goals(a: int, b: int) -> int:
	return _leaders_field(a, b, 8)

func cmp_leaders_sh_goals(a: int, b: int) -> int:
	return _leaders_field(a, b, 0xa)

func cmp_leaders_penalty_minutes(a: int, b: int) -> int:
	return _leaders_field(a, b, 0xc)

## cmp_leaders_plus_minus (0x2554b): the plus/minus, fewer games, the points, the goals
func cmp_leaders_plus_minus(a: int, b: int) -> int:
	var ra := _s(a)
	var rb := _s(b)
	if _pm(rb) != _pm(ra):
		return _pm(rb) - _pm(ra)
	if _sw(rb) != _sw(ra):
		return _sw(ra) - _sw(rb)
	if _sw(rb + 6) != _sw(ra + 6):
		return _sw(rb + 6) - _sw(ra + 6)
	return _sw(rb + 2) - _sw(ra + 2)

## cmp_leaders_shooting_pct (0x25755): the value, more games, the points, the goals, the
## plus/minus
func cmp_leaders_shooting_pct(a: int, b: int) -> int:
	if values[b] != values[a]:
		return values[b] - values[a]
	var ra := _s(a)
	var rb := _s(b)
	if _sw(rb) != _sw(ra):
		return _sw(rb) - _sw(ra)
	if _sw(rb + 6) != _sw(ra + 6):
		return _sw(rb + 6) - _sw(ra + 6)
	if _sw(rb + 2) != _sw(ra + 2):
		return _sw(rb + 2) - _sw(ra + 2)
	return _pm(rb) - _pm(ra)

## cmp_leaders_gaa (0x1fc8f): a goalie without minutes last, the goals against average (lower
## first), the minutes, the games, fewer goals against, the wins, fewer losses, the save percentage
func cmp_leaders_gaa(a: int, b: int) -> int:
	var ra := _g(a)
	var rb := _g(b)
	if (_gw(rb + 0xc) == 0) != (_gw(ra + 0xc) == 0):
		return _gw(rb + 0xc) - _gw(ra + 0xc)
	if _gw(rb + 0x10) != _gw(ra + 0x10):
		return _gw(ra + 0x10) - _gw(rb + 0x10)
	if _gw(rb + 0xc) != _gw(ra + 0xc):
		return _gw(rb + 0xc) - _gw(ra + 0xc)
	if _gw(rb) != _gw(ra):
		return _gw(rb) - _gw(ra)
	if _gw(rb + 0xe) != _gw(ra + 0xe):
		return _gw(ra + 0xe) - _gw(rb + 0xe)
	if _gw(rb + 2) != _gw(ra + 2):
		return _gw(rb + 2) - _gw(ra + 2)
	if _gw(rb + 4) != _gw(ra + 4):
		return _gw(ra + 4) - _gw(rb + 4)
	return _gw(rb + 0x14) - _gw(ra + 0x14)

## cmp_leaders_wins (0x2586a): the wins, the ties (not in the play-offs), fewer losses, fewer
## games, the minutes, the goals against average (lower first), the save percentage
func cmp_leaders_wins(a: int, b: int) -> int:
	var ra := _g(a)
	var rb := _g(b)
	if _gw(rb + 2) != _gw(ra + 2):
		return _gw(rb + 2) - _gw(ra + 2)
	if not playoffs and _gw(rb + 6) != _gw(ra + 6):
		return _gw(rb + 6) - _gw(ra + 6)
	if _gw(rb + 4) != _gw(ra + 4):
		return _gw(ra + 4) - _gw(rb + 4)
	if _gw(rb) != _gw(ra):
		return _gw(ra) - _gw(rb)
	if _gw(rb + 0xc) != _gw(ra + 0xc):
		return _gw(rb + 0xc) - _gw(ra + 0xc)
	if _gw(rb + 0x10) != _gw(ra + 0x10):
		return _gw(ra + 0x10) - _gw(rb + 0x10)
	return _gw(rb + 0x14) - _gw(ra + 0x14)

## cmp_leaders_save_pct (0x259c0): the save percentage, the minutes, more games, the wins, fewer
## losses, the goals against average (lower first)
func cmp_leaders_save_pct(a: int, b: int) -> int:
	var ra := _g(a)
	var rb := _g(b)
	if _gw(rb + 0x14) != _gw(ra + 0x14):
		return _gw(rb + 0x14) - _gw(ra + 0x14)
	if _gw(rb + 0xc) != _gw(ra + 0xc):
		return _gw(rb + 0xc) - _gw(ra + 0xc)
	if _gw(rb) != _gw(ra):
		return _gw(rb) - _gw(ra)
	if _gw(rb + 2) != _gw(ra + 2):
		return _gw(rb + 2) - _gw(ra + 2)
	if _gw(rb + 4) != _gw(ra + 4):
		return _gw(ra + 4) - _gw(rb + 4)
	return _gw(ra + 0x10) - _gw(rb + 0x10)

## funcptr_c6be8: the comparator of a leaders' table (0 points, 1 goals, 2 assists, 3 power play
## goals, 4 short handed goals, 5 plus/minus, 6 penalty minutes, 7 shooting percentage, 8 goals
## against average, 9 wins, 10 save percentage)
func leader_comparator(kind: int) -> Callable:
	return [cmp_leaders_points, cmp_leaders_goals, cmp_leaders_assists, cmp_leaders_pp_goals,
		cmp_leaders_sh_goals, cmp_leaders_plus_minus, cmp_leaders_penalty_minutes,
		cmp_leaders_shooting_pct, cmp_leaders_gaa, cmp_leaders_wins, cmp_leaders_save_pct][kind]

# ---------------------------------------------------------------------------------------------
# the tables of the screens, gathered as the original does
# ---------------------------------------------------------------------------------------------

## a file as the C library reads it (c_open / lseek / read): a read past the end gives fewer bytes
## and leaves the rest of the buffer as it was; a negative position fails (the position stays)
class CFile:
	var data := PackedByteArray()
	var pos := 0

	func _init(d: PackedByteArray) -> void:
		data = d

	func lseek(off: int) -> void:
		if off >= 0:
			pos = off

	func read(buf: PackedByteArray, n: int) -> int:
		var got := clampi(data.size() - pos, 0, n)
		for i in got:
			buf[i] = data[pos + i]
		pos += got
		return got

	## write: the bytes at the position (the file grows past its end)
	func write(buf: PackedByteArray, n: int) -> int:
		if pos + n > data.size():
			data.resize(pos + n)
		for i in n:
			data[pos + i] = buf[i]
		pos += n
		return n

static func _put(dst: PackedByteArray, at: int, src: PackedByteArray, n: int) -> void:
	for i in n:
		dst[at + i] = src[i]

## stats_table (0x25b24) up to its drawing: the leaders of a kind (funcptr_c6be8) from KEY.DB in
## its order: the players of the 26 teams (skaters for the kinds 0..7, goalies 'G' for 8..10)
## with games played in the block (season or play-offs) of their record in the statistics file
## (CAREER.DB at KEY +0x28, a league's SEASON.DB at +0x2c); the goals against average and the
## save percentage want 30 games in 100 of the team (CARTEAMS / TEAMS block +0x28 / +0x3a), the
## plus/minus and the shooting percentage 80, the wins a win. The first 20 go in as they come;
## after that a player replaces the 20th when the comparator puts him before it; the table is
## sorted again (qsort) after every one taken. Returns the sorter (its tables by slot), "order"
## (the slots in their order), "keys" (the KEY.DB record of each slot).
static func leaders(kind: int, playoffs: bool, league: bool, team_file: PackedByteArray, key_db: PackedByteArray,
		stats_db: PackedByteArray) -> Dictionary:
	var st := StatsSort.new()
	st.playoffs = playoffs
	var goalie := kind >= 8
	var size := 0x36 if goalie else 0x2f
	if goalie:
		st.goalies.resize(21 * 0x36)
	else:
		st.skaters.resize(21 * 0x2f)
	st.values.resize(21)
	var team_gp := []
	team_gp.resize(26)
	team_gp.fill(0)
	if kind in [8, 10, 5, 7]:
		var stride := 0x2e8 if league else 0x4c
		for t in 26:
			var at := t * stride + (0x3a if playoffs else 0x28)
			team_gp[t] = team_file[at] if at < team_file.size() else 0
	var keys := []
	keys.resize(20)
	var order := []
	var cmp := st.leader_comparator(kind)
	var kf := CFile.new(key_db)
	var sf := CFile.new(stats_db)
	var key := PackedByteArray()
	key.resize(0x34)
	var rec := PackedByteArray()
	rec.resize(size)
	var blk := (0x16 if goalie else 0x12) if playoffs else 0
	while kf.read(key, 0x34) == 0x34:
		if key[0] >= 0x1a or (key[2] == 0x47) != goalie:
			continue
		sf.lseek(key.decode_s32(0x2c if league else 0x28))
		sf.read(rec, size)
		var gp := rec.decode_u16(blk)
		if gp == 0:
			continue
		var count := order.size()
		if goalie:
			if kind == 8 or kind == 10:
				var tg: int = team_gp[key[0]]
				if tg == 0 or gp * 100 / tg < 0x1e:
					continue
			elif kind == 9 and rec.decode_u16(blk + 2) == 0:
				continue
			_put(st.goalies, count * 0x36, rec, 0x36)
		else:
			if kind == 5 or kind == 7:
				var tg: int = team_gp[key[0]]
				if tg == 0 or gp * 100 / tg < 0x50:
					continue
			_put(st.skaters, count * 0x2f, rec, 0x2f)
			if kind == 7:
				var shots := rec.decode_u16(blk + 0xe)
				st.values[count] = (rec.decode_u16(blk + 2) * 1000 + (shots >> 1)) / shots if shots != 0 else 0
		if count >= 20 and int(cmp.call(count, order[19])) >= 0:
			continue
		if count < 20:
			keys[count] = key.duplicate()
			order.append(count)
		else:
			var e: int = order[19]
			keys[e] = key.duplicate()
			if goalie:
				_put(st.goalies, e * 0x36, rec, 0x36)
			else:
				_put(st.skaters, e * 0x2f, rec, 0x2f)
				if kind == 7:
					st.values[e] = st.values[20]
		Clib.qsort(order, cmp)
	return {"sorter": st, "order": order, "keys": keys}

## team_stats_screen (0x235be) up to its drawing: the teams of a table (funcptr_c6ae0): the 26 (the
## season) or the 16 of the play-offs' first round (LSSCHED.DB, a league's schedule: the home and
## away team of each of the 8 series at +0x199c, none when the first is 0xff); each team's record
## (CARTEAMS 0x4c / TEAMS 0x2e8 apart); the value of each (the penalty killing and power play per
## mille, the times short handed / the advantages raised to the goals; the penalty minutes per
## game in tenths; the team's conference byte +0x27), sorted. The standings by conference (kind 5): the '93 - '94 lists of unk_c6af8 / unk_c6b30 as
## they are; in a league sorted and split by conference (unk_c5581 3: the west), a team of the
## other division of the first moved up to second when the first two are of one; in the play-offs
## sorted and split. Returns the sorter (the records by element), "teams" (the team of each
## element), "order", "west" and "east" (kind 5), "count" (the rows: 14 or 8 for kind 5).
static func team_table(kind: int, playoffs: bool, league: bool, team_file: PackedByteArray, sched: PackedByteArray) -> Dictionary:
	var st := StatsSort.new()
	st.playoffs = playoffs
	var teams := []
	if not playoffs:
		teams = range(26)
	else:
		for k in 8:
			var at := 0x199c + k * 0x2a
			teams.append(sched[at] if at < sched.size() else 0)
			teams.append(sched[at + 1] if at + 1 < sched.size() else 0)
		if teams[0] == 0xff:
			teams = []
	var n := teams.size()
	st.teams.resize(maxi(n, 1) * 0x4c)
	st.values.resize(maxi(n, 1))
	var stride := 0x2e8 if league else 0x4c
	var f := CFile.new(team_file)
	var rec := PackedByteArray()
	rec.resize(0x4c)
	var order := []
	for i in n:
		order.append(i)
		f.lseek(stride * teams[i])
		f.read(rec, 0x4c)
		_put(st.teams, i * 0x4c, rec, 0x4c)
		var b := i * 0x4c + (0x3a if playoffs else 0x28)
		match kind:
			2, 3:
				# (the read buffer's times short handed / advantages raised to the goals: the
				# record in the table keeps its own)
				var g := (0x3a if playoffs else 0x28) + (0xc if kind == 2 else 8)
				var t := g + 2
				if rec.decode_u16(g) > rec.decode_u16(t):
					rec.encode_u16(t, rec.decode_u16(g))
				var d := rec.decode_u16(t)
				var v := 0
				if d != 0:
					v = (rec.decode_u16(g) * 1000 + (d >> 1)) / d
					if kind == 2:
						v = 1000 - v
				st.values[i] = v
			4:
				var gp: int = st.teams[b]
				st.values[i] = (st.teams.decode_u16(b + 0x10) * 10 + (gp >> 1)) / gp if gp != 0 else 0
			5:
				st.values[i] = st.teams[i * 0x4c + 0x27]
	var out := {"sorter": st, "teams": teams, "order": order, "west": [], "east": [], "count": n}
	if n == 0:
		return out
	if kind != 5:
		Clib.qsort(order, st.team_comparator(kind))
		return out
	var west := []
	var east := []
	if not playoffs and not league:
		for i in 14:
			west.append(Exe.i32(0xc6af8 + i * 4))
			east.append(Exe.i32(0xc6b30 + i * 4))
		out["count"] = 14
	else:
		Clib.qsort(order, st.team_comparator(kind))
		for e in order:
			if Exe.i32(0xc5581 + teams[e] * 4) == 3:
				west.append(e)
			else:
				east.append(e)
		if not playoffs:
			_division_leaders(west, 3)
			_division_leaders(east, 0xc)
			out["count"] = 14
		else:
			out["count"] = 8
	out["west"] = west
	out["east"] = east
	return out

## the first two of a conference's list from one division (unk_c5519 bits): the first team of the
## other division from the third on moves up to second
static func _division_leaders(list: Array, both: int) -> void:
	var bits := func(e: int) -> int: return Exe.i32(0xc5519 + e * 4)
	if list.size() < 2 or (bits.call(list[0]) | bits.call(list[1])) == both:
		return
	var k := 2
	while k < 12 and k < list.size() and (bits.call(list[0]) | bits.call(list[k])) != both:
		k += 1
	if k >= list.size():
		return
	var e: int = list[k]
	list.remove_at(k)
	list.insert(1, e)

## player_stats_screen (0x244e2) up to its drawing: a team's roster (its TEAMS.DB record, the KEY.DB
## offsets of the 25 skaters at +0x4c and the 3 goalies at +0xb0, -1 none) with their records of
## the statistics file in roster order, the skaters by points (cmp_leaders_points), the goalies by
## goals against average (cmp_leaders_gaa). Returns the sorter, "skaters" / "goalies" (the slots
## in their order), "skater_roster" / "goalie_roster" (the roster index of each slot), "keys" (the
## KEY.DB record of each roster index).
static func roster(team_rec: PackedByteArray, playoffs: bool, league: bool, key_db: PackedByteArray,
		stats_db: PackedByteArray) -> Dictionary:
	var st := StatsSort.new()
	st.playoffs = playoffs
	st.skaters.resize(25 * 0x2f)
	st.goalies.resize(3 * 0x36)
	var kf := CFile.new(key_db)
	var sf := CFile.new(stats_db)
	var key := PackedByteArray()
	key.resize(0x34)
	var keys := []
	keys.resize(28)
	var out := {"sorter": st, "skaters": [], "goalies": [], "skater_roster": [], "goalie_roster": [], "keys": keys}
	for g in 2:
		var size := 0x36 if g == 1 else 0x2f
		var rec := PackedByteArray()
		rec.resize(size)
		for i in (3 if g == 1 else 25):
			var off := team_rec.decode_s32((0xb0 if g == 1 else 0x4c) + i * 4)
			if off == -1:
				continue
			kf.lseek(off)
			kf.read(key, 0x34)
			keys[i + 25 * g] = key.duplicate()
			sf.lseek(key.decode_s32(0x2c if league else 0x28))
			sf.read(rec, size)
			var list: Array = out["goalies" if g == 1 else "skaters"]
			_put(st.goalies if g == 1 else st.skaters, list.size() * size, rec, size)
			(out["goalie_roster" if g == 1 else "skater_roster"] as Array).append(i + 25 * g)
			list.append(list.size())
	Clib.qsort(out["skaters"], st.cmp_leaders_points)
	Clib.qsort(out["goalies"], st.cmp_leaders_gaa)
	return out
