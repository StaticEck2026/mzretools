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

## on the ice or on the bench: not in the penalty box (1) and not unavailable (-3)
static func available(team: Team, r: int) -> bool:
	return roster_exists(team, r) and team.entity_of[r] < 1 and team.entity_of[r] > -3

## player_available (0x5bf04): the player is available and not already in the requested lineup;
## registers him at index k
static func player_available(sim: Sim, team: Team, r: int, k: int) -> bool:
	if not available(team, r):
		return false
	for i in 6:
		if i != k and sim.req_roster[i] == r:
			return false
	sim.req_roster[k] = r
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

## line_avg_energy (0x5a30c): average energy of the players of a line (3 forwards, 5 on the power
## play, 4 killing a penalty)
static func line_avg_energy(sim: Sim, team: Team, line: int) -> int:
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
		var r := lt[start + i]
		total += team.energy[r] if r < 28 else 0x1000
	return total / n

## team_avg_energy (0x5a03b): average energy of the skaters on the ice
static func team_avg_energy(sim: Sim, team: Team) -> int:
	var total := 0
	var n := 0
	for i in 6:
		var e := sim.entities[team.first_slot + i]
		if e.line_slot > 0:
			total += team.energy[e.roster_idx]
			n += 1
	return total / n if n > 0 else 0x1000

## assign_line_positions (0x5bc50): fills sim.req_roster / sim.req_slot with the six players of
## the current line (goalie, two defencemen of the pair in use, the three forwards of the line, or
## the extra attacker instead of the goalie when it is pulled); unavailable players are replaced
## from the preference list of their position
static func assign_line_positions(sim: Sim, team: Team) -> void:
	for k in 6:
		sim.req_roster[k] = -1
	var mode := 0
	if team.goalie_pulled():
		mode = 1
	else:
		team.extra_attacker = -1
	var lt := line_table(team)
	var types: Array = Tables.lineup_slot_types[mode]
	for k in range(team.skaters_on_ice - 1, -1, -1):
		var type: int = types[k]
		sim.req_slot[k] = type
		var r := -1
		if type == 0:
			var lists: Array = Tables.line_table_lists[0]
			r = lt[lists[clampi(team.goalie_request & 0xf, 0, lists.size() - 1)]]
		elif type == 6:
			r = lt[0x26]
		else:
			var lists: Array = Tables.line_table_lists[type]
			var idx := team.dpair_counter if (team.current_line < 4 and type < 3) else team.current_line
			r = lt[lists[clampi(idx, 0, lists.size() - 1)]]
		sim.req_roster[k] = r if r < 28 else -1
	for k in range(5, -1, -1):
		var r := sim.req_roster[k]
		if r < 0:
			continue
		var type := sim.req_slot[k]
		if not available(team, r) or not player_available(sim, team, r, k):
			var found := false
			for off in Tables.line_table_lists[type]:
				var cand := lt[off]
				if cand < 28 and player_available(sim, team, cand, k):
					found = true
					break
			if not found:
				for cand in position_class(team, type):
					if player_available(sim, team, cand, k):
						found = true
						break
			if not found:
				for cand in range(24, -1, -1):
					if player_available(sim, team, cand, k):
						found = true
						break
			if not found:
				sim.req_roster[k] = -1
		if type == 6:
			team.extra_attacker = sim.req_roster[k]

## apply_line_change (0x5bef4): gives every entity of the team its next player. Players already
## on the ice keep their entity (maybe with a new position), the others replace the entities whose
## players are not in the new lineup; those skate to the bench (handle_line_change).
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
			if e.roster_idx == r:
				e.next_line_slot = sim.req_slot[k]
				e.next_roster = r
				sim.req_roster[k] = -1
				break
	for k in range(5, -1, -1):
		var r := sim.req_roster[k]
		if r < 0:
			continue
		var target: Entity = null
		var benched: Entity = null
		for i in 6:
			var e := sim.entities[first + i]
			if e.next_roster >= 0 or serving_penalty(e):
				# the original tracks a penalty by roster player and reuses the box entity
				# (release_from_box takes any free entity when the penalty expires); the port keeps the
				# penalized player on his entity until he is back on the ice
				continue
			if e.line_slot < 0:
				benched = e
				continue
			target = e
			break
		if target == null:
			target = benched
		if target == null:
			continue
		if target.line_slot < 0:
			target.set_state(Entity.State.INIT_PERIOD)
			target.line_slot = 5
		target.next_line_slot = sim.req_slot[k]
		target.next_roster = r
		sim.req_roster[k] = -1

## an entity on its way to, in or leaving the penalty box keeps its player
static func serving_penalty(e: Entity) -> bool:
	var st := e.state()
	return st == Entity.State.PENALTY_BOX or st == Entity.State.DOOR_OPEN or st == Entity.State.EXIT_PENALTY_BOX \
		or (e.flags2 & Entity.F2_PENALIZED) != 0

## dress_line (0x5e03c): puts the assigned players on the ice at once (period start)
static func dress_line(sim: Sim, team: Team) -> void:
	for i in 6:
		var e := sim.entities[team.first_slot + i]
		e.line_slot = e.next_line_slot
		if e.next_line_slot >= 0:
			AI.set_default_state(sim, e)
			if e.line_slot == 4:
				e.set_state_reset(Entity.State.NEAREST)
			team.entity_of[e.next_roster] = -1
			sim.put_player_on_ice(e, e.next_roster)
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
		var old := e.roster_idx
		if old >= 0 and old < 28 and team.entity_of[old] < 1 and team.entity_of[old] > -3:
			team.entity_of[old] = -2
		if (e.next_line_slot == 0) != (e.next_roster < 25):
			e.line_slot = e.next_line_slot
		AI.set_default_state(sim, e)
		if sim.play_stopped:
			e.timer_b = 0
			e.set_state_reset(Entity.State.ALL_GOTO_FACEOFF)
		var nr := e.next_roster
		e.next_roster = -1
		e.next_line_slot = -1
		if nr >= 0:
			sim.put_player_on_ice(e, nr)
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
		e.target_y = BENCH_Y[team.index]
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
			if e.facing != 4:
				e.facing = (e.facing + (1 if e.facing < 4 else -1)) & 7
			e.vy = 0
			e.vx = -0x800
			if dx > 0x10:
				return
			e.vx = 0
			if e.facing != 4:
				return
			e.vx = -0x800
			e.facing = 2
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
		e.flags3 = 0
		var k := e.slot - 6
		if k >= 0:
			k = e.slot - 4
		e.set_pos(-0xa0, k * 0xe)
		e.facing = 2
		e.flags = (e.flags & ~0x30) | Entity.F_BUSY
		Anim.set_animation(e, 0xd15 if e.line_slot == 0 else 0x7a1)
		return
	e.facing = 4
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
	if e.flags & Entity.F_STATE_ENTERED:
		e.flags &= ~Entity.F_STATE_ENTERED
		e.want_dir = 8
		e.target_y = BENCH_Y[team.index] + (2 - sim.random(4)) * 0xf
		e.target_x = BENCH_X
		e.timer_a = 0
		e.timer_b = 0
	if e.timer_a == 100:
		if e.line_slot > 0 and e.facing == 6 and sim.random((team.energy[e.roster_idx] >> 5) + 0x50) == 0:
			Anim.set_animation(e, 0xd97)
			e.flags |= Entity.F_BUSY
			return
		if e.anim == 0:
			Anim.set_animation(e, Anim.GLIDE)
		return
	e.timer_a -= 1
	if e.timer_a < 0:
		e.timer_a += 8
		var dy: int = e.yi - WAIT_Y[team.index]
		var dx := e.xi - e.target_x
		if absi(dy) < 0x27 and dx < 0x20:
			Anim.set_animation(e, 1 if e.line_slot == 0 else Anim.GLIDE)
			e.flags |= Entity.F_ARRIVED
			if e.facing != 6:
				e.facing = (e.facing + (1 if (e.facing > 2 and e.facing < 7) else -1)) & 7
			e.vy = 0
			e.vx = -0x800
			if dx > 0x10:
				return
			e.vx = 0
			if e.facing != 6:
				return
			e.timer_a = 100
			Anim.set_animation(e, Anim.GLIDE)
			return
	if (e.flags & Entity.F_ARRIVED) == 0:
		AI.skate_towards(sim, e, e.target_x, e.target_y)

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
	if team.dpair_counter > 2:
		team.dpair_counter = 0

## request_line_change (0x50434): the user asks for forward line `line` (0..3); on special teams
## the request selects a power play (0..1) or penalty killing (0..1) unit instead
static func request_line_change(sim: Sim, e: Entity, line: int) -> bool:
	if not sim.opt_line_changes:
		return false
	var team := sim.team_of(e)
	var other := sim.opponents_of(e)
	var mine := team.skaters_on_ice
	var theirs := other.skaters_on_ice
	if not ((theirs == mine or line < 2) and (theirs != mine or line < 4)):
		return false
	if theirs < mine:
		line += 4
	elif theirs > mine:
		line += 6
	e.flags2 &= ~Entity.F2_LINE_CHANGE
	e.flags |= Entity.F_USER
	team.flags &= ~Team.FL_LINE_CHANGE_UI
	team.line_change_ui = false
	if team.current_line != line:
		team.current_line = line
		if line < 4:
			rotate_defence(team)
		apply_line_change(sim, team)
	return true

## pick_next_line (0x4dc6b) / cpu_line_change_select: the next line of the rotation table for
## the team of `e` (k = 0 keeps the current line, 1 the next one)
static func next_line(sim: Sim, e: Entity, k: int) -> int:
	var team := sim.team_of(e)
	var other := sim.opponents_of(e)
	var group := 0
	if team.skaters_on_ice != other.skaters_on_ice:
		group = 16 if other.skaters_on_ice > team.skaters_on_ice else 8
	var row: Array = Tables.line_rotation[clampi(group + team.current_line, 0, Tables.line_rotation.size() - 1)]
	var line: int = row[k]
	return line if line >= 0 else team.current_line

## cpu_line_change_select (0x50975): applies `line` (0..7) for the team of `e`
static func select_line(sim: Sim, e: Entity, line: int) -> void:
	var team := sim.team_of(e)
	e.flags2 &= ~Entity.F2_LINE_CHANGE
	e.flags |= Entity.F_USER
	team.flags &= ~Team.FL_LINE_CHANGE_UI
	team.line_change_ui = false
	if line != team.current_line:
		team.current_line = line
		if line < 4:
			rotate_defence(team)
		apply_line_change(sim, team)

## choose_line (0x5a0a3): the CPU coach picks the next line for `team` playing against `other`:
## on special teams the fresher of the two units, otherwise the first line of the strategy's
## preference order whose energy is above the threshold (or the best one), unless the players
## on the ice are still fresh enough
static func choose_line(sim: Sim, other: Team, team: Team) -> void:
	var line: int
	if other.skaters_on_ice == team.skaters_on_ice:
		if (team.flags2 & 1) == 0:
			line = other.current_line
			if line >= 6:
				line -= 6
			elif line >= 4:
				line -= 4
		else:
			line = team.current_line
			if not sim.play_stopped and line < 4 and (team.flags2 & 0x40) == 0:
				if team.energy_threshold < team_avg_energy(sim, team):
					return
			if line > 3:
				line = 3
			if team.mode == 6 and (line < 4 or line > 5):
				line = 3
		if team.mode == 1 and (team.flags2 & 0x80):
			line += 4
		var row := clampi(team.strategy * 4 + line, 0, Tables.line_preference.size() * 4 - 1)
		var cands: Array = Tables.line_preference[row / 4][row % 4]
		var best := team.current_line
		var best_e := line_avg_energy(sim, team, best)
		var chosen := -1
		for c in cands:
			if c < 0:
				break
			var en := line_avg_energy(sim, team, c)
			if en > team.energy_threshold:
				chosen = c
				break
			if en > best_e:
				best = c
				best_e = en
		if chosen < 0:
			chosen = best
		if chosen != team.current_line:
			team.current_line = chosen
			if team.mode == 1 and chosen == 2:
				team.flags2 ^= 0x80
			if chosen < 4:
				rotate_defence(team)
	else:
		line = 6 if team.skaters_on_ice < other.skaters_on_ice else 4
		var e0 := line_avg_energy(sim, team, line)
		if e0 < 0xf33 and line_avg_energy(sim, team, line + 1) > e0:
			line += 1
		team.current_line = line
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

## maybe_pull_goalie (0x591c7): a CPU team trailing by one or two in the last minute of the third
## period pulls its goalie while the puck is in the attacking half (y in world coordinates)
static func maybe_pull_goalie(sim: Sim, team: Team, other: Team, y: int) -> void:
	if sim.penalty_shot or sim.period != 2:
		return
	var diff := other.goals - team.goals
	if diff <= 0 or diff >= 3 or sim.clock_seconds >= 0x3d:
		return
	if not team.attacks_up:
		y = -y
	if y >= 0:
		team.goalie_request = (team.goalie_request & 0xff) | 0xff00
		apply_line_change(sim, team)

## cpu_pull_goalie_check (0x59352), at every faceoff: a goalie pulled by the CPU comes back
## (the user's request stays), then the CPU reconsiders for the faceoff spot
static func cpu_pull_goalie_check(sim: Sim) -> void:
	for t in 2:
		var team := sim.teams[t]
		var other := sim.teams[1 - t]
		if (team.goalie_request & 0xf0) == 0:
			team.goalie_request &= 0xff
			if not sim.is_user_team(t):
				maybe_pull_goalie(sim, team, other, sim.faceoff_y)

## late_game_pull_goalie (0x593f5): true while a trailing team should keep its goalie off
static func late_game_pull_goalie(sim: Sim, t: int) -> bool:
	if sim.period != 2 or sim.clock_seconds >= 0x3d or sim.user2_team == t + 1:
		return false
	var team := sim.teams[t]
	var diff := sim.teams[1 - t].goals - team.goals
	if diff < 1 or diff > 2:
		return false
	var y := sim.faceoff_y
	if not team.attacks_up:
		y = -y
	return y >= 0

## cpu_line_change (0x59265), every step: with a delayed penalty call the team in possession
## pulls its goalie for the extra attacker; a trailing CPU team may pull it late in the game
static func cpu_line_change(sim: Sim) -> void:
	if sim.play_stopped or sim.puck_carrier < 0 or sim.puck_carrier >= 12:
		return
	var t := 0 if sim.puck_carrier < 6 else 1
	var team := sim.teams[t]
	if team.goalie_pulled():
		return
	if not sim.delayed_call:
		if not sim.is_user_team(t):
			maybe_pull_goalie(sim, team, sim.teams[1 - t], sim.puck.yi)
	else:
		team.goalie_request = (team.goalie_request & 0xff) | 0xff00
		apply_line_change(sim, team)

## sub_671e8 (F9 / F10): the user pulls the goalie or sends him back
static func toggle_pull_goalie(sim: Sim, t: int) -> void:
	if not sim.is_user_team(t):
		return
	var team := sim.teams[t]
	var w := team.goalie_request
	if (w & 0xfff0) == 0xff00:
		return      # pulled by the CPU logic (delayed penalty): not the user's call
	sim.show_message(MSG_RETURN_GOALIE if team.goalie_pulled() else MSG_PULL_GOALIE, 0x50)
	if team.goalie_pulled():
		team.goalie_request = w & 0xf
	else:
		team.goalie_request = (w | 0xfff0) & 0xffff
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
	if not sim.opt_offsides or sim.penalty_shot:
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
