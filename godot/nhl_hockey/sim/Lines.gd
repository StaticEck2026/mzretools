class_name Lines
## Line changes, fatigue and goalie pulling (assign_line_positions, apply_line_change,
## handle_line_change, choose_line, request_line_change, cpu_line_change, maybe_pull_goalie,
## cpu_pull_goalie_check, late_game_pull_goalie, dress_line, send_team_to_faceoff, adjust_strategy
## of HOCKEY.EXE). Every function operates on a Sim.
##
## A team always has six entities; a line change assigns a new roster player to an entity
## (`next_roster` / `next_line_slot`). The outgoing player skates to the bench door at
## (-168, -50 home / 65 away), steps off (BENCH state), the entity takes the new player and skates
## back (EXIT_BENCH). Line slots: 0 goalie, 1 LD, 2 RD, 3 LW, 4 C, 5 RW, 6 extra attacker.
## The team's line table (TEAMS.DB +0xbc, 0x30 bytes) holds roster indices: 4 forward lines x 3
## (LW C RW), 3 defence pairs x 2, 2 power play units x 5, 2 penalty killing units x 4, 2 goalies,
## then the extra attackers.

const BENCH_X := -0xa8                  # bench door of the leaving players
const BENCH_Y := [-0x32, 0x41]          # home / away (ai_bench)
const WAIT_Y := [-0x32, 0x46]           # ai_bench_wait
const MSG_RETURN_GOALIE := 0
const MSG_PULL_GOALIE := 1
const MSG_OFFSIDE := 4

## placeholder line table for teams without a database: forward lines 0-2 3-5 6-8 9-11, defence
## pairs 12-13 14-15 16-17, power play 0 1 2 12 13 / 3 4 5 14 15, penalty killing 0 1 12 13 /
## 3 4 14 15, goalies 25 26, extra attackers 2 5
static func default_line_table() -> PackedByteArray:
	var lt := PackedByteArray()
	lt.resize(0x30)
	lt.fill(0x64)
	var vals := [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 0, 1, 2, 12, 13, 3, 4, 5, 14, 15, 0, 1, 12, 13, 3, 4, 14, 15, 25, 26, 2, 5]
	for i in vals.size():
		lt[i] = vals[i]
	return lt

static func line_table(team: Team) -> PackedByteArray:
	if team.info != null and team.info.line_table.size() >= 0x30:
		return team.info.line_table
	return default_line_table()

## the player exists in the roster (0x64 marks an unset line table entry)
static func roster_exists(team: Team, r: int) -> bool:
	if r < 0 or r > 27:
		return false
	if team.info != null:
		return team.info.player(r) != null
	return true

## the word the original reads at team +0x7e + 2 r (entity_of[r]); below the table it reads the
## energy words in front of it, above it the port answers "not available"
static func entity_word(team: Team, r: int) -> int:
	if r >= 0 and r < 28:
		return team.entity_of[r]
	if r < 0 and r >= -28:
		return team.energy[28 + r]
	return 1

## the word at team +0x46 + 2 r (energy[r]) for a line table entry (an unsigned byte); behind the
## energy words come the entity_of words
static func energy_word(team: Team, r: int) -> int:
	if r >= 0 and r < 28:
		return team.energy[r]
	if r >= 28 and r < 56:
		return team.entity_of[r - 28]
	return 0

## player_available (0x5bb9e): roster player r may take lineup position k: neither in the penalty
## box (entity_of > 0) nor out of the game (-3 and below), nor in the lineup at another position;
## he is registered at k
static func player_available(sim: Sim, team: Team, r: int, k: int) -> bool:
	var st := entity_word(team, r)
	if st > 0 or st <= -3:
		return false
	for i in range(5, -1, -1):
		if i != k and sim.req_roster[i] == r:
			return false
	sim.req_roster[k] = Entity.to_s8(r)
	return true

## the skaters of a position class in roster order (the lists at 0xe9d50.. of the original)
static func position_class(team: Team, type: int) -> Array:
	var out := []
	for r in 25:
		if not roster_exists(team, r):
			continue
		var is_d := false
		if team.info != null:
			is_d = team.info.player(r).position == "D"
		else:
			is_d = r >= 12 and r < 18
		if (type == 1 or type == 2) == is_d:
			out.append(r)
	return out

# cd418: the lineup flag of a roster status (build_lines)
const STATUS_FLAGS := [0, 0, 2, 1, 1, 0, 0, 1, 0]

## the 0x14 rating bytes of skater r (player_ratings), zeros for an empty slot
static func skater_ratings(team: Team, r: int) -> PackedByteArray:
	var p: Database.Player = team.info.player(r) if team.info != null else null
	if p != null and p.ratings.size() >= 0x14:
		return p.ratings
	var z := PackedByteArray()
	z.resize(0x14)
	return z

## the position letter of skater r (the byte at +6 of his record in `rosters`)
static func position_letter(team: Team, r: int) -> int:
	var p: Database.Player = team.info.player(r) if team.info != null else null
	if p == null or p.position.is_empty():
		return 0
	return p.position.unicode_at(0)

## shellsort_by_key (0x93541): sorts the keys from the largest down and their indices with them
static func shellsort_desc(keys: PackedInt32Array, idx: PackedInt32Array) -> void:
	var n := keys.size()
	var gap := n >> 1
	while gap > 0:
		for i in range(gap, n):
			var j := i - gap
			while j >= 0 and keys[j] < keys[j + gap]:
				var k := keys[j]
				keys[j] = keys[j + gap]
				keys[j + gap] = k
				k = idx[j]
				idx[j] = idx[j + gap]
				idx[j + gap] = k
				j -= gap
		gap >>= 1

## sort_line_candidates (0x644a8) / sort_line_candidates_skaters (0x6455f): the skaters of a
## position letter (0: all but the defencemen) by a sum of their ratings, -1 after the last
static func sort_line_candidates(team: Team, letter: int, sums: PackedInt32Array) -> PackedInt32Array:
	var keys := PackedInt32Array()
	var idx := PackedInt32Array()
	keys.resize(25)
	idx.resize(25)
	for i in 25:
		idx[i] = i
		var l := position_letter(team, i)
		var match := (l != 0x44) if letter == 0 else (l == letter)
		keys[i] = sums[i] if match else -1
	shellsort_desc(keys, idx)
	var out := PackedInt32Array()
	out.resize(25)
	for i in 25:
		out[i] = idx[i] if keys[i] >= 0 else -1
	return out

## build_lines (0x64614), at the start of a match: for both teams the candidates of each position
## sorted by the offensive sum of their ratings (agility, speed, shot power, defensive and offensive
## awareness, passing, weight, stick handling) and by the defensive one (agility, speed, shot power,
## defensive awareness, passing, awareness, aggressiveness, checking, weight, stick handling);
## players without a record or injured (status 0 / 1) are left out. Then the lineup flags.
static func build_lines(sim: Sim) -> void:
	for t in 2:
		var team := sim.teams[t]
		var off := PackedInt32Array()
		var dfn := PackedInt32Array()
		off.resize(25)
		dfn.resize(25)
		for i in 25:
			var st := team.roster_status[i]
			if st == 0 or st == 1:
				off[i] = -1
				dfn[i] = -1
				continue
			var r := skater_ratings(team, i)
			off[i] = r[1] + r[2] + r[4] + r[6] + r[9] + r[10] + r[3] + r[13]
			dfn[i] = r[1] + r[2] + r[4] + r[6] + r[9] + r[11] + r[5] + r[12] + r[3] + r[13]
		team.pos_lists[Team.PL_D] = sort_line_candidates(team, 0x44, off)
		team.pos_lists[Team.PL_R] = sort_line_candidates(team, 0x52, off)
		team.pos_lists[Team.PL_L] = sort_line_candidates(team, 0x4c, off)
		team.pos_lists[Team.PL_C] = sort_line_candidates(team, 0x43, off)
		team.pos_lists[Team.PL_D_DEF] = sort_line_candidates(team, 0x44, dfn)
		team.pos_lists[Team.PL_R_DEF] = sort_line_candidates(team, 0x52, dfn)
		team.pos_lists[Team.PL_L_DEF] = sort_line_candidates(team, 0x4c, dfn)
		team.pos_lists[Team.PL_C_DEF] = sort_line_candidates(team, 0x43, dfn)
		team.pos_lists[Team.PL_SKATERS] = sort_line_candidates(team, 0, off)
		team.pos_lists[Team.PL_SKATERS_DEF] = sort_line_candidates(team, 0, dfn)
		var flags := PackedInt32Array()
		flags.resize(25)
		for i in 25:
			var st := team.roster_status[i]
			flags[i] = STATUS_FLAGS[st] if st < STATUS_FLAGS.size() else 0
		var lt := line_table(team)
		for i in 0x12:
			var r := Entity.to_s8(lt[i])
			if r >= 0 and r < 25:
				flags[r] = 0
		team.pos_lists[Team.PL_FLAGS] = flags

# --------------------------------------------------------------------------------------------
# the lineup: a player lost for the game is replaced in the line table (pick_player_for_position),
# the line table checked at the start of a match (count_dressed_players)
# --------------------------------------------------------------------------------------------

## the slots of a line table entry's group in later and earlier lines (unk_cd421: groups of slot
## numbers ending in -1; unk_cd473: the start of the group of each slot)
const LINEUP_GROUPS := [0, 3, 6, 9, -1, 1, 4, 7, 10, -1, 2, 5, 8, 11, -1, 12, 14, 16, -1, 13, 15, 17, -1,
	18, 23, 0, 3, 6, 9, -1, 19, 24, 1, 4, 7, 10, -1, 20, 25, 2, 5, 8, 11, -1, 21, 26, 12, 14, 16, -1,
	22, 27, 13, 15, 17, -1, 28, 32, 0, 3, 6, 9, -1, 29, 33, 1, 4, 7, 10, -1, 30, 34, 12, 14, 16, -1,
	31, 35, 13, 15, 17, -1]
const LINEUP_GROUP_START := [0, 5, 10, 0, 5, 10, 0, 5, 10, 0, 5, 10, 15, 19, 15, 19, 15, 19, 23, 30, 37,
	44, 50, 23, 30, 37, 44, 50, 56, 63, 70, 76, 56, 63, 70, 76]

static func _status_flag(team: Team, p: int) -> int:
	var st := team.roster_status[p] if p >= 0 and p < 28 else 0
	return STATUS_FLAGS[st] if st < STATUS_FLAGS.size() else 0

## lineup_player_ok (0x64a0b): roster player p may take line table slot c of team t: dressed
## (a scratched one only when the lineup holds him as a substitute, flag 2), and not twice in the
## same line or unit; a forward at most in two lines while more than six forwards are dressed, a
## defenceman in two pairs while three or more are; on the power play and killing penalties in
## either unit when the position's players are many enough
static func lineup_player_ok(sim: Sim, t: int, c: int, p: int) -> bool:
	var team := sim.teams[t]
	var lt := line_table(team)
	var flag := _status_flag(team, p)
	if flag == 0:
		return false
	if flag == 2 and team.pos_lists[Team.PL_FLAGS][p] != 2:
		return false
	var pos := position_letter(team, p)
	var lo: int
	var hi: int
	if c < 0xc:
		var n := 0
		for b in 0xc:
			if (b % 3 != c % 3 or b < c) and Entity.to_s8(lt[b]) == p:
				n += 1
		if n >= 2 and sim.lineup_forwards > 6:
			return false
		lo = (c / 3) * 3
		hi = lo + 2
	elif c < 0x12:
		if sim.lineup_defence >= 3:
			var n := 0
			for b in range(0xc, 0x12):
				if (b % 2 != c % 2 or b < c) and Entity.to_s8(lt[b]) == p:
					n += 1
			if n >= 2:
				return false
		lo = c & ~1
		hi = lo + 1
	elif c < 0x1c:
		if (pos == 0x44 and sim.lineup_defence < 4) or (pos != 0x44 and sim.lineup_forwards < 6):
			lo = 0x12 if c < 0x17 else 0x17
			hi = lo + 4
		else:
			lo = 0x12
			hi = 0x1b
	elif pos == 0x44 and sim.lineup_defence < 4:
		lo = 0x1c if c < 0x20 else 0x20
		hi = lo + 3
	else:
		lo = 0x1c
		hi = 0x23
	for b in range(lo, hi + 1):
		if b == c:
			continue
		if c >= 0x1c:
			if b == c + 4:
				continue
		elif c >= 0x12 and b == c + 5:
			continue
		if Entity.to_s8(lt[b]) == p:
			return false
	return true

## lineup_pick_best (0x64ca8): the first player of a candidate list with a lineup flag who may take
## slot si; a substitute (flag 2) only while fewer than 18 are dressed (forwards fewer than 12): he
## is dressed then (status 3, out of the scratches at +0x28..+0x2f, flag 1, counted); -1 for none
static func lineup_pick_best(sim: Sim, list: PackedInt32Array, t: int, si: int) -> int:
	var team := sim.teams[t]
	var flags: PackedInt32Array = team.pos_lists[Team.PL_FLAGS]
	for i in 0x19:
		var p := list[i]
		if p < 0:
			return -1
		if flags[p] == 0 or not lineup_player_ok(sim, t, si, p):
			continue
		if flags[p] == 2:
			if sim.lineup_dressed >= 0x12:
				continue
			if position_letter(team, p) != 0x44 and sim.lineup_forwards >= 0xc:
				continue
			team.roster_status[p] = 3
			var lt := line_table(team)
			for c in range(0x28, 0x30):
				if Entity.to_s8(lt[c]) == p:
					lt[c] = 0x64
			flags[p] = 1
			sim.lineup_dressed += 1
			if position_letter(team, p) == 0x44:
				sim.lineup_defence += 1
			else:
				sim.lineup_forwards += 1
		return p
	return -1

## choose_lineup_player (0x64e60): the player for line table slot si of team t, whose player is
## lost: the one in the same position of a later line or unit; else the best of the candidate
## lists by the lost player's position (defence or the forward positions in their order of
## preference; the offensive lists below slot 28, the defensive ones for penalty killing); else the
## same position of an earlier line; else any skater (defencemen: the defence lists first)
static func choose_lineup_player(sim: Sim, t: int, si: int) -> int:
	var team := sim.teams[t]
	var lt := line_table(team)
	var start: int = LINEUP_GROUP_START[si]
	var c := start
	while true:
		var v: int = LINEUP_GROUPS[c]
		c += 1
		if v == si:
			break
	while LINEUP_GROUPS[c] >= 0:
		var p := Entity.to_s8(lt[LINEUP_GROUPS[c]])
		if lineup_player_ok(sim, t, si, p):
			return p
		c += 1
	var pos := position_letter(team, Entity.to_s8(lt[si]))
	var lists: Array = []
	var offensive := si < 0x1c
	match pos:
		0x44:
			lists = [Team.PL_D if (si >= 0x12 and si < 0x1c) else Team.PL_D_DEF]
		0x43:
			lists = [Team.PL_C if offensive else Team.PL_C_DEF, Team.PL_L if offensive else Team.PL_L_DEF,
				Team.PL_R if offensive else Team.PL_R_DEF]
		0x52:
			lists = [Team.PL_R if offensive else Team.PL_R_DEF, Team.PL_L if offensive else Team.PL_L_DEF,
				Team.PL_C if offensive else Team.PL_C_DEF]
		0x4c:
			lists = [Team.PL_L if offensive else Team.PL_L_DEF, Team.PL_R if offensive else Team.PL_R_DEF,
				Team.PL_C if offensive else Team.PL_C_DEF]
	for k: int in lists:
		var p := lineup_pick_best(sim, team.pos_lists[k], t, si)
		if p >= 0:
			return p
	c = start
	while LINEUP_GROUPS[c] != si:
		var p := Entity.to_s8(lt[LINEUP_GROUPS[c]])
		if lineup_player_ok(sim, t, si, p):
			return p
		c += 1
	# (a defenceman: the defence, then all skaters, by the power play's offensive lists or the
	# defensive ones; a forward: all skaters, then the defence, offensive below slot 28)
	var pp := si >= 0x12 and si < 0x1c
	var order := [Team.PL_D if pp else Team.PL_D_DEF, Team.PL_SKATERS if pp else Team.PL_SKATERS_DEF]
	if pos != 0x44:
		order = [Team.PL_SKATERS if offensive else Team.PL_SKATERS_DEF, Team.PL_D if offensive else Team.PL_D_DEF]
	for k: int in order:
		var list: PackedInt32Array = team.pos_lists[k]
		for i in 0x19:
			var p := list[i]
			if p < 0:
				break
			if lineup_player_ok(sim, t, si, p):
				return p
	return 0

## lineup_fill_slots (0x6552e): the lost player in slot si leaves the lineup (flag 0); from his
## line k to the last (count) each slot of the position (step apart) takes the player
## choose_lineup_player picks, who leaves the substitutes when the slot is a line or a pair
static func lineup_fill_slots(sim: Sim, t: int, si: int, k: int, count: int, step: int) -> void:
	var team := sim.teams[t]
	var lt := line_table(team)
	var flags: PackedInt32Array = team.pos_lists[Team.PL_FLAGS]
	var lost := Entity.to_s8(lt[si])
	if lost >= 0 and lost < 25:
		flags[lost] = 0
	while k < count:
		var p := choose_lineup_player(sim, t, si)
		lt[si] = p & 0xff
		if si < 0x12 and p >= 0 and p < 25:
			flags[p] = 0
		k += 1
		si += step

## lineup_set_goalies (0x652d6): a lost starting goalie is replaced by the backup; the backup by
## the first other goalie who is dressed (or, with `call_up`, a scratched one: dressed, out of the
## scratches), else the starter is his own backup
static func lineup_set_goalies(sim: Sim, t: int, slot: int, call_up: int) -> void:
	var team := sim.teams[t]
	var lt := line_table(team)
	if slot == 0x24:
		lt[0x24] = lt[0x25]
	for d in range(0x19, 0x1c):
		if d == Entity.to_s8(lt[0x24]) or d == Entity.to_s8(lt[0x25]):
			continue
		var st := team.roster_status[d]
		if _status_flag(team, d) == 1:
			lt[0x25] = d
			return
		if st == 2 and call_up != 0:
			team.roster_status[d] = 3
			for c in range(0x28, 0x30):
				if Entity.to_s8(lt[c]) == d:
					lt[c] = 0x64
			lt[0x25] = d
			return
	lt[0x25] = lt[0x24]

## lineup_set_backup (0x653be): the extra attackers (slots 0x26 / 0x27): for the first, the second
## if he is dressed, else the first dressed skater; then the second, the first dressed skater who is
## not the first
static func lineup_set_backup(sim: Sim, t: int, slot: int) -> void:
	var team := sim.teams[t]
	var lt := line_table(team)
	var skaters: PackedInt32Array = team.pos_lists[Team.PL_SKATERS]
	if slot == 0x26:
		var second := Entity.to_s8(lt[0x27])
		if _status_flag(team, second) == 1:
			lt[0x26] = second & 0xff
		else:
			for d in 0x19:
				var p := skaters[d]
				if p < 0:
					break
				if _status_flag(team, p) == 1:
					lt[0x26] = p
					break
	for d in 0x19:
		var p := skaters[d]
		if p < 0:
			return
		if _status_flag(team, p) == 1 and p != Entity.to_s8(lt[0x26]):
			lt[0x27] = p
			return

## the dressed players (status flag 1) of a candidate list, up to its end
static func _count_dressed(team: Team, list: PackedInt32Array) -> int:
	var n := 0
	for i in 0x19:
		var p := list[i]
		if p < 0:
			break
		if _status_flag(team, p) == 1:
			n += 1
	return n

## pick_player_for_position (0x655cc): roster player r of team t is lost for the game; the
## dressed players of his kind are counted, and every slot of the line table he holds is filled
## (the forward lines, the defence pairs, the power play and penalty killing units, the goalies, the
## extra attackers)
static func pick_player_for_position(sim: Sim, t: int, r: int) -> void:
	var team := sim.teams[t]
	var lt := line_table(team)
	var pos := position_letter(team, r)
	if pos == 0x44:
		sim.lineup_defence = _count_dressed(team, team.pos_lists[Team.PL_D_DEF])
	elif pos != 0x47:
		sim.lineup_forwards = _count_dressed(team, team.pos_lists[Team.PL_SKATERS])
	var di := 0
	for groups: Array in [[4, 3], [3, 2], [2, 5], [2, 4]]:
		for k in groups[0]:
			for j in groups[1]:
				if Entity.to_s8(lt[di]) == r:
					lineup_fill_slots(sim, t, di, k, groups[0], groups[1])
				di += 1
	for k in 2:
		if Entity.to_s8(lt[di]) == r:
			lineup_set_goalies(sim, t, di, 0)
		di += 1
	for k in 2:
		if Entity.to_s8(lt[di]) == r:
			lineup_set_backup(sim, t, di)
		di += 1

## count_dressed_players (0x658f3), before the match: the dressed defencemen and forwards counted;
## the players of the line table (the extra attackers too) whose place is empty or who are injured
## are replaced (pick_player_for_position), an unavailable starting goalie too (a scratched one may
## be called up); the substitutes' lineup flags (2) are cleared
static func count_dressed_players(sim: Sim, t: int) -> void:
	var team := sim.teams[t]
	var lt := line_table(team)
	sim.lineup_defence = _count_dressed(team, team.pos_lists[Team.PL_D_DEF])
	sim.lineup_forwards = _count_dressed(team, team.pos_lists[Team.PL_SKATERS])
	sim.lineup_dressed = sim.lineup_forwards + sim.lineup_defence
	sim.lineup_in_table.resize(0x19)
	sim.lineup_in_table.fill(0)
	for c in 0x24:
		_mark_in_table(sim, Entity.to_s8(lt[c]))
	_mark_in_table(sim, Entity.to_s8(lt[0x27]))
	_mark_in_table(sim, Entity.to_s8(lt[0x26]))
	for c in 0x19:
		var st := team.roster_status[c]
		if sim.lineup_in_table[c] != 0 and (st == 0 or st == 1):
			pick_player_for_position(sim, t, c)
	var g := Entity.to_s8(lt[0x24])
	var gst := team.roster_status[g] if g >= 0 and g < 28 else 0
	if gst == 0 or gst == 1:
		lineup_set_goalies(sim, t, 0x24, 1)
	var flags: PackedInt32Array = team.pos_lists[Team.PL_FLAGS]
	for c in 0x19:
		flags[c] = 1 if flags[c] == 1 else 0

static func _mark_in_table(sim: Sim, p: int) -> void:
	if p >= 0 and p < 0x19:
		sim.lineup_in_table[p] = 1

## line_avg_energy (0x5a30c): average energy of the players of a line (3 forwards, 5 on the power
## play, 4 killing a penalty); the sum is a 16 bit word
static func line_avg_energy(_sim: Sim, team: Team, line: int) -> int:
	var lt := line_table(team)
	var start: int
	var n: int
	if line < 4:
		start = line * 3
		n = 3
	elif line < 6:
		start = 0x12 + (line - 4) * 5
		n = 5
	else:
		start = 4 + line * 4
		n = 4
	var total := 0
	for i in n:
		total = Entity.to_s16(total + energy_word(team, lt[start + i]))
	return total / n

## team_avg_energy (0x5a03b): average energy of the skaters on the ice (the goalie not counted),
## left in the scratch word e03bc (0 with nobody on the ice)
static func team_avg_energy(sim: Sim, team: Team) -> int:
	var total := 0
	var n := 0
	for i in 6:
		var e := sim.entities[team.first_slot + i]
		if e.line_slot > 0:
			total += energy_word(team, Entity.to_s8(e.roster_idx))
			n += 1
	sim.scratch_a = 0
	if n != 0:
		sim.scratch_a = Entity.to_s16(total / n)
	return sim.scratch_a

## the k-th entry of the preference list of position type `type` (line table offsets), read as
## the original does: past the list's -1 terminator come the next lists
static func _list_offset(type: int, k: int) -> int:
	var i := Tables.line_table_lists_base[type] + k
	return Tables.line_table_lists_raw[i] if i >= 0 and i < Tables.line_table_lists_raw.size() else -1

## a byte of the line table (an offset outside it reads as 0)
static func _lt(lt: PackedByteArray, off: int) -> int:
	return lt[off] if off >= 0 and off < lt.size() else 0

## assign_line_positions (0x5bbfa): fills sim.req_roster / sim.req_slot with the players of the
## current line from the line table: the goalie (goalie_request), the defence pair in use with the
## forward lines (dpair_counter), the forwards of the line, or the units of the power play and the
## penalty killing (current_line 4..7); with the goalie pulled (goalie_request < 0, not for the
## team defending a penalty shot) the extra attacker instead. A player who is not available is
## replaced from the preference list of the position, then from the candidates build_lines sorted
## (defencemen or all skaters, by the defensive ratings while killing a penalty), then by any
## skater from 24 down to 1. Lineup positions below skaters_on_ice - 2 take an available player
## without the check against the other positions.
static func assign_line_positions(sim: Sim, team: Team) -> void:
	var mode := 0
	var cur := team.current_line
	var lt := line_table(team)
	for k in 6:
		sim.req_roster[k] = -1
	if (sim.penalty_shot_phase == 0 or team.index == sim.penalty_shot_team) and Entity.to_s16(team.goalie_request) < 0:
		mode = 1
	else:
		team.extra_attacker = -1
	for k in range(team.skaters_on_ice - 1, -1, -1):
		var type: int = Tables.lineup_slot_types_raw[mode + k]
		sim.req_slot[k] = type
		var off: int
		if type == 0:
			off = _list_offset(0, Entity.to_s16(team.goalie_request))
		elif type == 6:
			off = 0x26
		elif cur < 4 and type <= 2:
			off = _list_offset(type, team.dpair_counter)
		else:
			off = _list_offset(type, cur)
		sim.req_roster[k] = Entity.to_s8(_lt(lt, off))
	for k in range(5, -1, -1):
		var r := sim.req_roster[k]
		if r < 0:
			continue
		var type := sim.req_slot[k]
		var st := entity_word(team, r)
		if st <= -3 or st > 0 or (k >= team.skaters_on_ice - 2 and not player_available(sim, team, r, k)):
			_replace_player(sim, team, k, type, cur, lt)
		if type == 6:
			team.extra_attacker = sim.req_roster[k]

## the replacement search of assign_line_positions for lineup position k
static func _replace_player(sim: Sim, team: Team, k: int, type: int, cur: int, lt: PackedByteArray) -> void:
	var i := 0
	while true:
		var off := _list_offset(type, i)
		i += 1
		if off < 0:
			break
		if player_available(sim, team, Entity.to_s8(_lt(lt, off)), k):
			return
	var which: int
	var defence := type == 1 or type == 2
	if type == 6 or cur < 6:
		which = Team.PL_D if defence else Team.PL_SKATERS
	else:
		which = Team.PL_D_DEF if defence else Team.PL_SKATERS_DEF
	var cands: PackedInt32Array = team.pos_lists[which]
	i = 0
	while true:
		var cand := cands[i] if i < 25 else -1
		i += 1
		if cand >= 0:
			if player_available(sim, team, cand, k):
				return
			continue
		# the end of the candidates: any skater from 24 down to 1; when one is found the original
		# checks him a second time (the same answer), when none is the position keeps its player
		for c in range(0x18, 0, -1):
			if player_available(sim, team, c, k):
				return
		return

## apply_line_change (0x5bef4): gives the entities of the team their next players (next_roster,
## next_line_slot): a player of the new lineup already on an entity keeps it, the others go to the
## first entity on the ice without a new player, else to the last free one on the bench, which is
## sent out (INIT_PERIOD, line slot 5). The entities whose players are not in the lineup go to the
## bench (handle_line_change).
static func apply_line_change(sim: Sim, team: Team) -> void:
	var first := team.first_slot
	for i in 6:
		sim.entities[first + i].next_line_slot = -1
		sim.entities[first + i].next_roster = -1
	assign_line_positions(sim, team)
	for k in range(5, -1, -1):
		var r := sim.req_roster[k]
		if r < 0:
			continue
		for i in 6:
			var e := sim.entities[first + i]
			if Entity.to_s8(e.roster_idx) == r:
				e.next_line_slot = sim.req_slot[k]
				e.next_roster = r
				sim.req_roster[k] = -1
				break
	var target: Entity = null
	for k in range(5, -1, -1):
		var r := sim.req_roster[k]
		if r < 0:
			continue
		for i in 6:
			var e := sim.entities[first + i]
			if e.next_roster >= 0:
				continue
			target = e
			if e.line_slot >= 0:
				break
		if target == null:
			continue
		if target.line_slot < 0:
			target.set_state(Entity.State.INIT_PERIOD)
			target.line_slot = 5
		target.next_line_slot = sim.req_slot[k]
		target.next_roster = r
		sim.req_roster[k] = -1

## dress_line (0x5e0dd): puts the assigned players on the ice at once (period start): on the ice
## in entity_of and in the roster status (4)
static func dress_line(sim: Sim, team: Team) -> void:
	for i in 6:
		var e := sim.entities[team.first_slot + i]
		e.line_slot = e.next_line_slot
		if e.next_line_slot >= 0:
			AI.set_default_state(sim, e)
			if e.line_slot == 4:
				e.set_state_reset(Entity.State.NEAREST)
			var r := e.next_roster
			if r >= 0 and r < 28:
				team.entity_of[r] = -1
				team.roster_status[r] = 4
			sim.put_player_on_ice(e, r)
		e.next_line_slot = -1
		e.next_roster = -1

## handle_line_change (0x52bb6), called by the positional handlers: an entity whose player is not
## in the lineup any more goes to the bench (BENCH); an entity that keeps its player takes its
## (possibly new) position. Returns true when the handler must stop.
static func handle_line_change(sim: Sim, e: Entity) -> bool:
	if (not sim.play_stopped and (e.flags & Entity.F_USER)) or (e.flags2 & Entity.F2_PENALIZED):
		return false
	if e.next_line_slot < 0 and e.next_roster < 0:
		return false
	var team := sim.team_of(e)
	var at_start := sim.clock_seconds == sim.period_length and sim.clock_sub == 0
	if at_start:
		if e.next_line_slot == e.line_slot and e.next_roster == e.roster_idx and e.state() == Entity.State.ALL_GOTO_FACEOFF:
			return false
		if team.line_change_ui and e.state() == Entity.State.INIT_PERIOD:
			return false
	if e.next_roster != e.roster_idx:
		if e.state() == Entity.State.BENCH or sim.puck_carrier == e.slot:
			return false
		e.flags2 |= Entity.F2_UNSELECTABLE
		e.flags &= ~Entity.F_ARRIVED
		e.timer_a = 0
		if sim.play_stopped:
			e.timer_b = 0
		e.set_state(Entity.State.BENCH)
		return true
	e.flags2 &= ~Entity.F2_UNSELECTABLE
	e.flags &= ~Entity.F_ARRIVED
	if e.next_line_slot >= 0 and ((e.next_line_slot == 0) != (e.roster_idx < 25)):
		e.line_slot = e.next_line_slot
	AI.set_default_state(sim, e)
	if sim.play_stopped and not at_start:
		e.timer_b = 0
		e.set_state_reset(Entity.State.BENCH_WAIT if (e.line_slot > 0 and team.line_change_ui) else Entity.State.ALL_GOTO_FACEOFF)
	e.next_roster = -1
	e.next_line_slot = -1
	return true

## ai_bench (0x4b12c): skate to the bench door, step off, the replacement steps on
static func bench(sim: Sim, e: Entity) -> void:
	if e.flags & Entity.F_BUSY:
		return
	var team := sim.team_of(e)
	if e.timer_a == 100:
		e.frame = -1
		var old := Entity.to_s8(e.roster_idx)
		var st := entity_word(team, old)
		if st <= 0 and st >= -2 and old >= 0 and old < 28:
			team.entity_of[old] = -2
			team.roster_status[old] = 3
		if (e.next_line_slot == 0) != (e.next_roster < 25):
			e.line_slot = e.next_line_slot
		AI.set_default_state(sim, e)
		if sim.play_stopped:
			e.timer_b = 0
			e.set_state_reset(Entity.State.ALL_GOTO_FACEOFF)
		var nr := e.next_roster
		e.next_roster = -1
		e.next_line_slot = -1
		sim.put_player_on_ice(e, nr)        # (also with no player to come: -1)
		return
	if handle_line_change(sim, e):
		return
	if (e.flags2 & Entity.F2_PENALIZED) or sim.faceoff_pending:
		AI.skate_idle(sim, e)
		return
	if sim.play_stopped and e.line_slot == 0 and (team.goalie_request & 0xfff0) == 0xff00 and not late_game_pull_goalie(sim, team.index):
		# the situation does not warrant the extra attacker any more: the goalie stays
		e.next_line_slot = -1
		e.next_roster = -1
		e.set_state(Entity.State.ALL_GOTO_FACEOFF)
		return
	if e.flags & Entity.F_STATE_ENTERED:
		e.flags &= ~Entity.F_STATE_ENTERED
		e.want_dir = 8
		e.dir_timer = 0
		e.target_y = BENCH_Y[1 if (e.flags & Entity.F_PLAYER2) else 0]
		e.target_x = BENCH_X
		e.timer_a = 0
	if e.next_roster == e.roster_idx:
		e.flags2 &= ~Entity.F2_UNSELECTABLE
		if (e.next_line_slot == 0) != (e.next_roster < 25):
			e.line_slot = e.next_line_slot
		AI.set_default_state(sim, e)
		e.next_roster = -1
		e.next_line_slot = -1
		return
	if e.line_slot == 0:
		e.flags3 |= 3
	e.timer_a -= 1
	if e.timer_a < 0:
		e.timer_a += 8
		var dy := e.yi - e.target_y
		var dx := e.xi - e.target_x
		if absi(dy) < 0x29 and dx < 0x21:
			Anim.set_animation(e, 1 if e.line_slot == 0 else Anim.GLIDE)
			e.flags |= Entity.F_ARRIVED
			var hw := AI._heading_word(e)
			if hw != 4:
				AI._set_heading_word(e, (hw + (1 if hw < 4 else -1)) & 7)
			e.vy = 0
			e.vx = -0x800
			if dx > 0x10:
				return
			e.vx = 0
			if AI._heading_word(e) != 4:
				return
			e.vx = -0x800
			AI._set_heading_word(e, 2)
			Anim.set_animation(e, 0xd2d if e.line_slot == 0 else 0x7bf)
			e.flags |= Entity.F_BUSY
			e.timer_a = 100
			return
	if (e.flags & Entity.F_ARRIVED) == 0:
		AI.skate_towards(sim, e, e.target_x, e.target_y, 1 if (not sim.play_stopped and e.line_slot != 0) else 0)

## ai_exit_bench (0x4aac2): the replacement appears at the boards and steps onto the ice
static func exit_bench(sim: Sim, e: Entity) -> void:
	if e.flags & Entity.F_BUSY:
		return
	if e.flags & Entity.F_STATE_ENTERED:
		e.flags &= ~Entity.F_STATE_ENTERED
		e.vx = 0
		e.vy = 0
		e.pass_target = 0                # the word +0x48
		var k := e.slot - 6
		if k >= 0:
			k = e.slot - 4
		# at the bench door (the fractions of the position stay)
		e.y = (Sim._s16(k * 0xe) << 16) | (e.y & 0xffff)
		e.x = (-0xa0 * 0x10000) | (e.x & 0xffff)
		AI._set_heading_word(e, 2)
		e.flags = (e.flags & ~0x30) | Entity.F_BUSY
		Anim.set_animation(e, 0xd15 if e.line_slot == 0 else 0x7a1)
		return
	AI._set_heading_word(e, 4)
	e.flags &= ~Entity.F_ARRIVED
	e.flags2 &= ~(Entity.F2_UNSELECTABLE | Entity.F2_NO_COLLIDE)
	e.anim = 0
	e.vx = 0x1000
	AI.default_skate(sim, e)

## ai_bench_wait (0x5147d): during a stoppage a player leaving with the line change prompt open
## waits at the bench until the new line is confirmed
static func bench_wait(sim: Sim, e: Entity) -> void:
	if e.flags & Entity.F_BUSY:
		return
	if handle_line_change(sim, e):
		return
	var team := sim.team_of(e)
	var away := 1 if e.flags & Entity.F_PLAYER2 else 0
	if e.flags & Entity.F_STATE_ENTERED:
		e.flags &= ~Entity.F_STATE_ENTERED
		e.want_dir = 8
		e.dir_timer = 0
		e.target_y = Entity.to_s16(BENCH_Y[away] + (2 - sim.random(4)) * 0xf)
		e.target_x = BENCH_X
		e.timer_a = 0
		e.timer_b = 0
	if e.timer_a == 0x5a:
		# a player called on from the bench (bench_player_slot) takes this one's place
		e.set_state_reset(Entity.State.BENCH_WAIT)
		sim.put_player_on_ice(e, e.timer_b)
		e.frame = -1
		e.timer_b = 0
		e.timer_a = 0
		return
	if e.timer_a == 100:
		if e.line_slot > 0 and e.facing == 6 \
				and Entity.to_s16(sim.random(Entity.to_s16(team.energy[e.roster_idx] / 32 + 0x50))) == 0:
			Anim.set_animation(e, 0xd97)
			e.flags |= Entity.F_BUSY
			return
		if e.anim == 0:
			Anim.set_animation(e, Anim.GLIDE)
		return
	e.timer_a = Entity.to_s16(e.timer_a - 1)
	if e.timer_a < 0:
		e.timer_a += 8
		var dy := Entity.to_s16(e.yi - WAIT_Y[away])
		sim.scratch_a = Entity.to_s16(e.xi - e.target_x)
		if absi(dy) <= 0x26 and sim.scratch_a <= 0x1f:
			sim.scratch_b = 1 if e.line_slot == 0 else Anim.GLIDE
			Anim.set_animation(e, sim.scratch_b)
			e.flags |= Entity.F_ARRIVED
			if e.facing != 6:
				e.facing = (e.facing + (1 if (e.facing > 2 and e.facing < 7) else -1)) & 7
			e.vy = 0
			e.vx = -0x800
			if sim.scratch_a > 0x10:
				return
			e.vx = 0
			if e.facing != 6:
				return
			e.timer_a = 100
			Anim.set_animation(e, Anim.GLIDE)
			bench_player_slot(sim, e)
			return
	if (e.flags & Entity.F_ARRIVED) == 0:
		AI.skate_towards(sim, e, e.target_x, e.target_y)

## bench_player_slot (0x51115): a player at the bench door lets the first skater the line editor
## called on (roster status 7) come on: he turns to the bench and the change is made after 0x5a
## steps of the animation (timer_b keeps the roster index)
static func bench_player_slot(sim: Sim, e: Entity) -> void:
	var team: Team = sim.teams[1 if e.flags & Entity.F_PLAYER2 else 0]
	for idx in 25:
		if team.roster_status[idx] != 7:
			continue
		e.facing = 4
		Anim.set_animation(e, 0x7bf)
		e.flags |= Entity.F_BUSY
		e.timer_a = 0x5a
		e.timer_b = idx
		team.roster_status[idx] = 3
		team.entity_of[idx] = -2
		return

## safety net of the port before the puck is placed: a change that did not complete at the bench
## in time (the original waits for every player) is applied at once
static func flush_pending(sim: Sim) -> void:
	for i in 12:
		var e := sim.entities[i]
		if e.next_roster < 0:
			continue
		var team := sim.team_of(e)
		if e.next_roster != e.roster_idx:
			var old := e.roster_idx
			if old >= 0 and old < 28 and team.entity_of[old] == -1:
				team.entity_of[old] = -2
			if e.next_line_slot >= 0:
				e.line_slot = e.next_line_slot
			var nr := e.next_roster
			e.next_roster = -1
			e.next_line_slot = -1
			team.entity_of[nr] = -1
			sim.put_player_on_ice(e, nr)
		else:
			if e.next_line_slot >= 0 and ((e.next_line_slot == 0) != (e.roster_idx < 25)):
				e.line_slot = e.next_line_slot
			e.next_roster = -1
			e.next_line_slot = -1
		e.flags2 &= ~Entity.F2_UNSELECTABLE
		e.flags &= ~(Entity.F_BUSY | Entity.F_ARRIVED)
		e.state_sp = 0
		e.state_stack[0] = Entity.State.INIT_PERIOD

## send_team_to_faceoff (0x511b4): every player without a pending change lines up for the
## faceoff; nothing during a penalty shot, and after one the players who waited at the bench are
## taken off (INIT_PERIOD) to be dressed again at the faceoff
static func send_team_to_faceoff(sim: Sim, team: Team) -> void:
	if sim.penalty_shot_phase != 0:
		return
	for i in 6:
		var e := sim.entities[team.first_slot + i]
		if sim.penalty_shot_setup and e.state() == Entity.State.PENALTY_SHOT_WAIT:
			e.timer_b = 0
			e.set_state(Entity.State.INIT_PERIOD)
		elif e.line_slot >= 0 and e.next_line_slot == -1 and e.next_roster == -1 and e.timer_b != -100 and e.state() != Entity.State.ALL_GOTO_FACEOFF:
			e.set_state_reset(Entity.State.ALL_GOTO_FACEOFF)

## the defence pair rotates with every forward line change (0, 1, 2, 0, ...)
static func rotate_defence(team: Team) -> void:
	team.dpair_counter += 1
	if team.dpair_counter >= 3:
		team.dpair_counter -= 3

## draw_line_indicator (0x14afe): the line number on the scoreboard (the port's HUD draws
## team.current_line); a hook for the golden tests
static func draw_line_indicator(sim: Sim, t: int, line: int) -> void:
	sim.stubbed("draw_line_indicator", [t, line])

## request_line_change (0x50434): the user asks for forward line `line` (0..3); on special teams
## the request selects a power play (0..1) or penalty killing (0..1) unit instead
static func request_line_change(sim: Sim, e: Entity, line: int) -> bool:
	if not sim.opt_line_changes:
		return false
	var team := sim.team_of(e)
	var other := sim.opponents_of(e)
	var d := Entity.to_s16(other.skaters_on_ice - team.skaters_on_ice)
	if d != 0 and line > 1:
		return false
	if d == 0 and line > 3:
		return false
	if d < 0:
		line += 4
	elif d > 0:
		line += 6
	e.flags2 &= ~Entity.F2_LINE_CHANGE
	e.flags |= Entity.F_USER
	team.flags &= ~Team.FL_LINE_CHANGE_UI
	if team.current_line == line:
		return true
	team.current_line = line
	if line < 4:
		rotate_defence(team)
	draw_line_indicator(sim, 1 if e.flags & Entity.F_PLAYER2 else 0, line)
	apply_line_change(sim, team)
	return true

## pick_next_line (0x50908): the line the line change prompt offers in place k (scratch word
## e03bc, 0..3) for the team of `e`: the row of line_rotation for the current line (power play
## +8 rows, penalty killing +16); the line is left in e03bc (-1 for none), the current line in e03c0
static func pick_next_line(sim: Sim, e: Entity) -> void:
	var team := sim.team_of(e)
	var other := sim.opponents_of(e)
	var d := Entity.to_s16(other.skaters_on_ice - team.skaters_on_ice)
	if d != 0:
		sim.scratch_a = Entity.to_s16(sim.scratch_a + 0x20)
		if d > 0:
			sim.scratch_a = Entity.to_s16(sim.scratch_a + 0x20)
	sim.scratch_b = team.current_line
	var i := Entity.to_s16(sim.scratch_a + team.current_line * 4) + 0x20
	sim.scratch_a = Tables.line_rotation_raw[i] if i >= 0 and i < Tables.line_rotation_raw.size() else -1

# unk_ccb4a: the line the prompt offers next (forward lines 0-3 in turn, the two units of each
# special team in turn)
const LINE_CYCLE := [1, 2, 3, 0, 5, 4, 7, 6]

## request_line_change_button (0x4d9fc): C with the puck (or the stoppage's prompt): with line
## changes on and the prompt not open yet the prompt opens (no pass or shot under way any more)
static func request_line_change_button(sim: Sim, e: Entity) -> void:
	if not sim.opt_line_changes:
		return
	var team := sim.team_of(e)
	if team.flags & Team.FL_LINE_CHANGE_UI:
		return
	team.flags |= Team.FL_LINE_CHANGE_UI
	sim.action_pass = false
	sim.action_shot = false
	e.flags2 |= Entity.F2_LINE_CHANGE
	start_line_change_ui(sim, e)

## start_line_change_ui (0x4d938): the prompt opens on the first line of the rotation after the
## current one (place 1; none: the current line, place 0)
static func start_line_change_ui(sim: Sim, e: Entity) -> void:
	var t := 1 if e.flags & Entity.F_PLAYER2 else 0
	sim.scratch_a = 1
	pick_next_line(sim, e)
	if sim.scratch_a < 0:
		sim.lc_place[t] = 0
		sim.lc_line[t] = sim.teams[t].current_line
	else:
		sim.lc_place[t] = 1
		sim.lc_line[t] = sim.scratch_a
	sim.lc_timer[t] = 0x3c
	sim.lc_show[t] = 1
	sim.lc_blink[t] = 0xc
	sim.teams[t].line_change_ui = true

## line_change_bench_step (0x4fd8e), control_player while the prompt is open: (re)opened when the
## team asks (team flags & 1); C (changed) takes the line offered; every 0x3c steps the next line is
## offered (4 places, 2 on special teams), the prompt blinks every 0xc steps; he can still skate
static func line_change_bench_step(sim: Sim, e: Entity) -> void:
	var team := sim.team_of(e)
	if team.flags & 1:
		team.flags &= ~1
		start_line_change_ui(sim, e)
	var t := 1 if e.flags & Entity.F_PLAYER2 else 0
	if sim.scratch_ac & 0x40:
		sim.scratch_ac = (sim.scratch_ac & ~0xffff) | (sim.lc_place[t] & 0xffff)
		cpu_line_change_select(sim, e)
		sim.lc_show[t] = 0
		sim.teams[t].line_change_ui = false
		return
	var old := sim.lc_timer[t]
	sim.lc_timer[t] = Entity.to_s16(old - 1)
	if old == 0:
		sim.lc_timer[t] += 0x3c
		var n := 2 if sim.lc_line[t] > 3 else 4
		sim.lc_place[t] = (sim.lc_place[t] + 1) % n
		var l := sim.lc_line[t]
		sim.lc_line[t] = LINE_CYCLE[l] if l >= 0 and l < 8 else 0
		sim.lc_show[t] = 1
		sim.lc_blink[t] = 0xc
	old = sim.lc_blink[t]
	sim.lc_blink[t] = Entity.to_s16(old - 1)
	if old == 0:
		sim.lc_blink[t] += 0xc
		sim.lc_show[t] = 1 if sim.lc_show[t] == 0 else 0
	if (e.flags & Entity.F_USER) and not sim.controls_blocked and (e.flags & Entity.F_BUSY) == 0 \
			and (e.flags2 & Entity.F2_KNOCKED) == 0:
		sim.apply_skating(e, sim.scratch_a)

## user_line_change_prompt (0x4da37), at a stoppage for each user: the prompt opens; it closes by
## itself after 0x258 steps (home, timer_a of the puck) or 0x168 (away, word +0x28), the user's slot
## kept in target_x / target_y
static func user_line_change_prompt(sim: Sim, puck: Entity, e: Entity) -> void:
	e.flags2 &= ~Entity.F2_LINE_CHANGE
	request_line_change_button(sim, e)
	if (e.flags2 & Entity.F2_LINE_CHANGE) == 0:
		return
	if e.flags & Entity.F_PLAYER2:
		sim.puck_stuck_timer = 0x168
		puck.target_y = e.slot
	else:
		puck.timer_a = 0x258
		puck.target_x = e.slot

## dress_line_if_start (0x5125f): at the opening faceoff of the game (not in a demo) the line of
## team t is dressed at once
static func dress_line_if_start(sim: Sim, t: int) -> void:
	if not sim.demo and sim.period == 0 and sim.clock_seconds == sim.period_length and sim.clock_sub == 0:
		dress_line(sim, sim.teams[t])

## cpu_line_change_select (0x50975): the line chosen at the prompt (place scratch_ac) for the team
## of `e`: the player is the user's again, the prompt closes and the line comes on
static func cpu_line_change_select(sim: Sim, e: Entity) -> void:
	var team := sim.team_of(e)
	sim.scratch_a = Entity.to_s16(sim.scratch_ac)
	pick_next_line(sim, e)
	if sim.scratch_a < 0:
		return
	e.flags2 &= ~Entity.F2_LINE_CHANGE
	e.flags |= Entity.F_USER
	team.flags &= ~Team.FL_LINE_CHANGE_UI
	if sim.scratch_a == team.current_line:
		return
	team.current_line = sim.scratch_a
	if sim.scratch_a < 4:
		rotate_defence(team)
	draw_line_indicator(sim, 1 if e.flags & Entity.F_PLAYER2 else 0, sim.scratch_a)
	apply_line_change(sim, team)

## choose_line (0x5a0a3): the CPU coach picks the next line for `team` playing against `other`.
## On special teams the fresher of the two units (the first unless it is below 0xf33). At even
## strength a coach who picks his own lines (flags2 & 1) keeps a fresh line on at a stoppage (the
## average energy on the ice above the threshold) and otherwise starts from his current line, the
## others from the line the opponent has on; then the first of the four candidates of the coaching
## mode's preference row above the threshold, or the freshest of them and the current line.
static func choose_line(sim: Sim, other: Team, team: Team) -> void:
	var d := Entity.to_s16(team.skaters_on_ice - other.skaters_on_ice)
	var t := 1 if team.index == 1 else 0
	var line: int
	if d != 0:
		line = 4 if d >= 0 else 6
		var e0 := Entity.to_s16(line_avg_energy(sim, team, line))
		if e0 < 0xf33 and e0 < Entity.to_s16(line_avg_energy(sim, team, line + 1)):
			line += 1
		team.current_line = line
		draw_line_indicator(sim, t, line)
		team.flags2 &= ~0x40
		return
	if team.flags2 & 1:
		line = team.current_line
		if sim.play_stopped and line < 4 and (team.flags2 & 0x40) == 0:
			team_avg_energy(sim, team)
			var thr := team.energy_threshold if team.skaters_on_ice == other.skaters_on_ice else 0xf33
			if (sim.scratch_a & 0xffff) > thr:
				return
		if line > 3:
			line = 3
		if Entity.to_s8(team.mode) == 6 and (line < 4 or line > 5):
			line = 3
	else:
		line = other.current_line
		if line >= 6:
			line -= 6
		elif line >= 4:
			line -= 4
	if Entity.to_s8(team.mode) == 1 and (team.flags2 & 0x80):
		line += 4
	var cands: Array = Tables.line_preference[Entity.to_s8(team.mode)][line]
	var best := team.current_line
	var best_e := Entity.to_s16(line_avg_energy(sim, team, best))
	var c := -1
	for k in 4:
		c = int(cands[k])
		if c < 0:
			break
		var en := Entity.to_s16(line_avg_energy(sim, team, c))
		if (en & 0xffffffff) > team.energy_threshold:
			break
		if en > best_e:
			best_e = en
			best = c
		c = -1
	if c < 0:
		c = best
	if c != team.current_line:
		team.current_line = c
		if Entity.to_s8(team.mode) == 1 and c == 2:
			team.flags2 ^= 0x80
		if c < 4:
			rotate_defence(team)
	draw_line_indicator(sim, t, c)
	team.flags2 &= ~0x40

## adjust_strategy (0x5a581): the CPU coaching mode from the score (game start, 10:00 of the 2nd)
static func adjust_strategy(sim: Sim, t: int) -> void:
	var team := sim.teams[t]
	var diff := sim.teams[0].goals - sim.teams[1].goals
	if t != 0:
		if diff > 1:
			team.flags2 |= 1
			team.mode = 8
			return
		if diff < -3:
			team.energy_threshold = 0xd9a
			team.strategy = 3
			team.strategy2 = 2
		else:
			team.energy_threshold = 0xccc
		team.flags2 |= 1
		team.mode = 1
		return
	team.flags2 &= ~1
	if diff < -1:
		team.mode = 5
		return
	if diff > 3:
		team.energy_threshold = 0xd9a
		team.mode = 4
		team.strategy = 3
		team.strategy2 = 2
		return
	team.energy_threshold = 0xccc
	team.mode = 0

## the radio buttons of the pause menu's goalie choice (the attribute bytes of the menu items:
## goalie 1, goalie 2, none; 1 is the checked one)
static func set_goalie_menu(team: Team, pulled: bool) -> void:
	var g := (team.goalie_request & 0xff) & 0xf
	if pulled:
		team.goalie_menu[g] = 2
		team.goalie_menu[2] = 1
	else:
		team.goalie_menu[2] = 2
		team.goalie_menu[g] = 1

## period_strategy_init (0x5a6a0), at the start of a period: the coaching of both teams (an
## overtime: the home team plays mode 2, the away team mode 8 and picks its own lines; the third
## period from the score; the first two: modes 0 and 1, the away team picks its own lines,
## alternating), the first forward line and defence pair; with line changes the CPU teams start
## with their third pair (the away team also with its fourth line)
static func period_strategy_init(sim: Sim) -> void:
	var home := sim.teams[0]
	var away := sim.teams[1]
	home.flags2 = 0
	away.flags2 = 0
	home.strategy = 3
	home.strategy2 = 2
	away.strategy = 3
	away.strategy2 = 2
	var pn := sim.period_num
	if pn > 3:
		home.energy_threshold = 0xd9a
		home.mode = 2
		away.energy_threshold = 0xd9a
		away.flags2 = 1
		away.mode = 8
	elif pn == 3:
		adjust_strategy(sim, 0)
		adjust_strategy(sim, 1)
	else:
		home.energy_threshold = 0xccc
		home.mode = 0
		away.energy_threshold = 0xccc
		away.flags2 = 0x81
		away.mode = 1
	away.dpair_counter = 0
	away.current_line = 0
	home.dpair_counter = 0
	home.current_line = 0
	if not sim.opt_line_changes:
		return
	if sim.user1_team != 1 and sim.user2_team != 1:
		home.dpair_counter = 2
	if sim.user1_team != 2 and sim.user2_team != 2:
		away.current_line = 3
		away.dpair_counter = 2

## time_announcements (0x5a77c), at full minutes of the 2nd and 3rd period (game_clock_tick): the
## CPU coaches review their strategy. In the 2nd period from 10:00 on adjust_strategy (at 10:00 a
## team behind by two or more also raises its strategy and lowers its second one). In the 3rd
## period a trailing team goes for it (modes 6 / 7 with a high threshold in the last 1 / 3 minutes,
## mode 0xa from 10:00 when two behind), a leading home team plays mode 3, a leading away team
## modes 8 / 9; before 10:00 adjust_strategy. A changed mode makes the team change lines (flags2 0x40).
static func time_announcements(sim: Sim) -> void:
	if sim.no_stats:
		return
	var home := sim.teams[0]
	var away := sim.teams[1]
	var d := Entity.to_s16(home.goals - away.goals)
	var pn := sim.period_num
	var c := sim.clock_seconds
	if pn == 2 and c <= 0x258:
		var m0 := home.mode
		adjust_strategy(sim, 0)
		if m0 != home.mode:
			home.flags2 |= 0x40
		var m1 := away.mode
		adjust_strategy(sim, 1)
		if m1 != away.mode:
			away.flags2 |= 0x40
		if c != 0x258:
			return
		if d < -1:
			if home.strategy < 4:
				home.strategy += 1
			if home.strategy2 > 1:
				home.strategy2 -= 1
		if d <= 1:
			return
		if away.strategy < 4:
			away.strategy += 1
		if away.strategy2 > 1:
			away.strategy2 -= 1
		return
	if pn != 3:
		return
	var m := home.mode
	if (c <= 0x3c and d <= -1) or (c <= 0x78 and d < -1):
		_go_for_it(home, 6)
	elif (c <= 0xb4 and d <= -1) or (c <= 0x12c and d < -1):
		_go_for_it(home, 7)
	elif c <= 0x258:
		if d < -1:
			_go_for_it(home, 0xa)
		else:
			home.energy_threshold = 0xccc if d > 2 else 0xd9a
			home.flags2 &= ~1
			home.mode = 3
			home.strategy = 3
			home.strategy2 = 2
	else:
		adjust_strategy(sim, 0)
	if m != home.mode:
		home.flags2 |= 0x40
	m = away.mode
	if (c <= 0x3c and d >= 1) or (c <= 0x78 and d > 1):
		_go_for_it(away, 6)
	elif (c <= 0xb4 and d > 1) or (c <= 0x12c and d > 1):
		_go_for_it(away, 7)
	elif c <= 0x258:
		if d > 1:
			_go_for_it(away, 0xa)
		else:
			if d < -2:
				away.energy_threshold = 0xccc
				away.mode = 9
			else:
				away.energy_threshold = 0xd9a
				away.mode = 8
			away.flags2 |= 1
			away.strategy = 3
			away.strategy2 = 2
	else:
		adjust_strategy(sim, 1)
	if m != away.mode:
		away.flags2 |= 0x40

static func _go_for_it(team: Team, mode: int) -> void:
	team.energy_threshold = 0xb33
	team.flags2 |= 1
	team.mode = mode
	team.strategy = 4
	team.strategy2 = 1

## maybe_pull_goalie (0x591c7): a CPU team trailing by one or two in the last minute of the third
## period pulls its goalie while the puck (or the faceoff spot) is in its attacking half
static func maybe_pull_goalie(sim: Sim, team: Team, other: Team, y: int) -> void:
	if sim.penalty_shot_phase != 0 or sim.period != 2:
		return
	var diff := Entity.to_s16(other.goals - team.goals)
	if diff <= 0 or diff > sim.period or sim.clock_seconds > 0x3c:
		return
	if (sim.entities[team.first_slot].flags & Entity.F_ATTACK_UP) == 0:
		y = -y
	if Entity.to_s16(y) < 0:
		return
	team.goalie_request = (team.goalie_request & 0xff) | 0xff00
	set_goalie_menu(team, true)
	apply_line_change(sim, team)

## cpu_pull_goalie_check (0x59352), at every faceoff: a goalie pulled by the CPU comes back
## (the user's request stays), then the CPU teams reconsider for the faceoff spot
static func cpu_pull_goalie_check(sim: Sim) -> void:
	for t in 2:
		var team := sim.teams[t]
		if (team.goalie_request & 0xf0) != 0:
			continue
		team.goalie_request &= 0xff
		set_goalie_menu(team, false)
		if sim.user1_team != t + 1 and sim.user2_team != t + 1:
			maybe_pull_goalie(sim, team, sim.teams[1 - t], sim.faceoff_y)

## late_game_pull_goalie (0x593f5): true while a trailing team should keep its goalie off (the
## original checks only user 1's team)
static func late_game_pull_goalie(sim: Sim, t: int) -> bool:
	if sim.period != 2 or sim.clock_seconds > 0x3c or sim.user1_team == t + 1:
		return false
	var team := sim.teams[t]
	var diff := sim.teams[1 - t].goals - team.goals
	if diff <= 0 or diff > 2:
		return false
	var y := sim.faceoff_y
	if (sim.entities[team.first_slot].flags & Entity.F_ATTACK_UP) == 0:
		y = -y
	return y >= 0

## cpu_line_change (0x59265), every step of play: with a delayed penalty call the team in
## possession pulls its goalie for the extra attacker; a trailing CPU team may pull it late in the
## game (the referee holding the puck counts as the away team's)
static func cpu_line_change(sim: Sim) -> void:
	if sim.play_stopped:
		return
	for t in 2:
		var team := sim.teams[t]
		if Entity.to_s16(team.goalie_request) < 0:
			continue
		var c := Entity.to_s8(sim.puck_carrier)
		if c < 0 or (c < 6) != (t == 0):
			continue
		if sim.delayed_call:
			team.goalie_request = (team.goalie_request & 0xff) | 0xff00
			set_goalie_menu(team, true)
			apply_line_change(sim, team)
		elif sim.user1_team != t + 1 and sim.user2_team != t + 1:
			maybe_pull_goalie(sim, team, sim.teams[1 - t], sim.puck.yi)

## hotkey_pull_goalie (0x671e8, F9 / F10): the user pulls the goalie or sends him back (not one the
## CPU pulled for a delayed call): the PULL GOALIE / RETURN GOALIE message (unless a higher one is
## showing), the menu's radio buttons, the new lineup
static func toggle_pull_goalie(sim: Sim, t: int) -> void:
	if not sim.is_user_team(t):
		return
	var team := sim.teams[t]
	var w := Entity.to_s16(team.goalie_request)
	if (w & 0xfff0) == 0xff00:
		return
	var msg := MSG_PULL_GOALIE if w >= 0 else MSG_RETURN_GOALIE
	if msg > sim.message or sim.message < 2:
		sim.show_message(msg, 0x50)
	if w < 0:
		team.goalie_menu[2] = 2
		team.goalie_request = w & 0xf
		team.goalie_menu[team.goalie_request] = 1
	else:
		team.goalie_menu[w & 0xf] = 2
		team.goalie_request = (team.goalie_request | 0xfff0) & 0xffff
		team.goalie_menu[2] = 1
	apply_line_change(sim, team)

## controls_goalie_pull_request (0x7cbb3): a team the users left (the controls changed during the
## game) gets its goalie back from a pull the user asked for, unless the CPU would pull him now
## (trailing by one or two in the last minute of the third, or a delayed call with the puck)
static func user_goalie_back(sim: Sim, t: int) -> void:
	var team := sim.teams[t]
	if Entity.to_s16(team.goalie_request) >= 0 or (team.goalie_request & 0xf0) == 0:
		return
	team.goalie_request &= 0xff0f
	var diff := Entity.to_s16(sim.teams[1 - t].goals - team.goals)
	if diff > 0 and diff <= 2 and sim.period == 2 and sim.clock_seconds <= 0x3c:
		return
	var c := Entity.to_s8(sim.puck_carrier)
	if not sim.play_stopped and c >= 0 and (c < 6) == (t == 0) and sim.delayed_call:
		return
	team.goalie_request &= 0xff
	team.goalie_menu[2] = 2
	team.goalie_menu[team.goalie_request & 0xf] = 1
	apply_line_change(sim, team)

## choose_goalie, the goalie choice of the pause menu (Home / Visiting Team Goalie): goalie 0 or 1 of
## the line table, or -1 for none (the extra attacker). A goalie change during a delayed call
## against the other team (game_flags 8, play running) gives the extra attacker at once.
static func choose_goalie(sim: Sim, t: int, choice: int) -> void:
	if not sim.is_user_team(t):
		return
	var team := sim.teams[t]
	var before := team.goalie_request
	if choice < 0:
		team.goalie_request = (team.goalie_request | 0xfff0) & 0xffff
	else:
		team.goalie_request = choice
		if not sim.play_stopped and sim.delayed_call and sim.puck_carrier >= 0 and (1 if sim.puck_carrier < 6 else 0) != t:
			team.goalie_request = (team.goalie_request & 0xff) | 0xff00
	if (Entity.to_s16(team.goalie_request) >= 0 or Entity.to_s16(before) >= 0) and before != team.goalie_request:
		apply_line_change(sim, team)

## regenerate_energy (0x5bd36 in sim_game_state): players on the bench recover 8 per tick
static func regenerate_energy(sim: Sim) -> void:
	if not sim.opt_line_changes:
		return
	for team in sim.teams:
		for i in 28:
			if team.entity_of[i] == -2:
				team.energy[i] = mini(0x1000, team.energy[i] + 8)

## pull_goalie_logic (0x53f8c), for the puck carrier: the OFFSIDE warning while a team mate is in
## the attacking zone before the puck; the carrier then prefers passing (stop_flags & 0x80)
static func offside_warning_check(sim: Sim, e: Entity) -> void:
	if not sim.opt_offsides or sim.penalty_shot or sim.penalty_shot_setup:
		return
	var team := sim.team_of(e)
	var warn := false
	var margin := 0
	var puck := sim.puck
	if (e.flags & Entity.F_ATTACK_UP) == 0:
		if e.yi > -0x52 and e.vy <= 0:
			margin = 4
		if puck.yi >= -(0x4e + margin):
			for i in 6:
				var p := sim.entities[team.first_slot + i]
				if p.line_slot >= 0 and p.yi < -(0x4e + margin):
					warn = true
					break
	else:
		if e.yi < 0x52 and e.vy >= 0:
			margin = 4
		if puck.yi <= 0x4e + margin:
			for i in 6:
				var p := sim.entities[team.first_slot + i]
				if p.line_slot >= 0 and p.yi > 0x4e + margin:
					warn = true
					break
	if warn:
		if not sim.offside_warning:
			sim.offside_warning = true
			if sim.message < MSG_OFFSIDE and (puck.yi < 0) != ((e.flags & Entity.F_ATTACK_UP) != 0):
				sim.show_message(MSG_OFFSIDE, 0)
	elif sim.offside_warning:
		sim.offside_warning = false
		if sim.message == MSG_OFFSIDE and sim.message_timer == 0:
			sim.message = -1
