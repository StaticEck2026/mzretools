class_name Rules
## Game rules: the clock, stoppages and the infraction queue, faceoff placement, goals, offside and
## icing. Ports of sim_game_state, update_stoppage, process_infractions, start_stoppage, queue_infraction,
## game_clock_tick, score_goal, setup_faceoff, check_offside, check_icing, faceoff_resolve and the
## positioning part of ai_puck_faceoff2. Penalties are recognised but served as a plain faceoff
## (the penalty box states are not ported).

# infraction / event ids (infraction_queue, infraction_priority, infraction_is_penalty)
const INF_PERIOD_START := 1
const INF_PERIOD_END := 2
const INF_FROZEN := 3            # puck frozen, held or out of play
const INF_GOALIE_HOLD := 4
const INF_PENALTY_SHOT_END := 5
const INF_ICING := 6
const INF_GOAL := 7
const INF_OFFSIDE := 8
const INF_HOOKING := 9           # 9 .. 21: two minute minors, 22 misconduct, 23 .. 25 majors
const INF_INJURY := 10
const INF_CHARGING := 13
const INF_HIGH_STICK := 14
const INF_ELBOWING := 19
const INF_PENALTY_SHOT := 17
const INF_FIGHT := 22
const INF_ROUGHING := 23
const INF_DISALLOWED := 27
const INF_TWO_LINE := 29
const INF_REF_HIT := 30

# --------------------------------------------------------------------------------------------
# per step (sim_game_state)
# --------------------------------------------------------------------------------------------

static func game_state_tick(sim: Sim) -> void:
	update_stoppage(sim)
	update_effects(sim)
	if not sim.play_stopped and sim.clock_seconds == 0 and sim.clock_sub == 0:
		sim.play_sfx(0x90)          # end of period horn
		sim.action_hold_camera = true
		setup_faceoff(sim)
	if not sim.play_stopped:
		game_clock_tick(sim)
		if sim.clock_sub == 0x17:
			penalty_timers(sim)
	Lines.cpu_line_change(sim)
	# the 24 Hz tick of sim_game_state: energy, lead changes
	if sim.step_count % 24 == 0:
		Lines.regenerate_energy(sim)
		if not sim.play_stopped:
			update_lead_change(sim)

## update_stoppage (0x63929): runs the infraction queue and the whistle / stoppage timers
static func update_stoppage(sim: Sim) -> void:
	process_infractions(sim)
	if not sim.play_stopped:
		return
	if sim.announce_timer >= 0:
		sim.announce_timer -= 1
		if sim.announce_timer < 0:
			sim.whistle_ready = true
	if not sim.stoppage_countdown:
		return
	if sim.stoppage_timer < 0:
		stoppage_done(sim)
		return
	sim.whistle_timer = maxi(0, sim.whistle_timer - 1)
	sim.stoppage_timer -= 1
	if sim.stoppage_timer < 0:
		sim.delayed_call = false
		sim.whistle_timer = 0

## penalty_box_update (0x63300), reduced: once the referee has collected the puck and every
## infraction was dealt with, the faceoff is set up
static func stoppage_done(sim: Sim) -> void:
	if sim.ref_phase == 0:
		return
	# penalty_box_update: the penalized players are sent to the box (minors 2, majors 5 minutes)
	while not sim.infractions.is_empty():
		var inf: Array = sim.infractions[sim.infractions.size() - 1]
		if not inf[2]:
			return
		var e: Entity = sim.entities[inf[1]]
		var minutes: int = Tables.infraction_is_penalty[inf[0]]
		if minutes > 0 and e.slot < 12 and e.line_slot > 0 and (e.flags2 & Entity.F2_PENALIZED):
			serve_penalty(sim, e, minutes)
		e.flags2 &= ~Entity.F2_PENALIZED
		sim.infractions.pop_back()
	for t in 2:
		var team := sim.teams[t]
		# a team never plays with fewer than 3 skaters: extra penalties are stacked
		team.skaters_on_ice = clampi(6 - team.penalties.size(), 4, 6)
	sim.stoppage_countdown = false
	var ps := sim.puck.state()
	if ps == Entity.State.PUCK_FACEOFF or ps == Entity.State.PUCK_FACEOFF2:
		return
	sim.puck.set_state(Entity.State.PUCK_FACEOFF)

## the player goes to the penalty box (penalty_box_update, record_penalty)
static func serve_penalty(sim: Sim, e: Entity, minutes: int) -> void:
	var team := sim.team_of(e)
	for pen in team.penalties:
		if pen[2] == e.slot:
			return
	team.penalties.append([e.roster_idx, minutes * 60, e.slot, minutes == 2])
	if e.roster_idx >= 0:
		team.entity_of[e.roster_idx] = 1        # in the box
	e.next_line_slot = -1
	e.next_roster = -1
	e.set_state(Entity.State.PENALTY_BOX)
	e.flags2 |= Entity.F2_UNSELECTABLE
	if e.slot == sim.user1_slot:
		sim.switch_to_nearest(e, 0)
	elif e.slot == sim.user2_slot:
		sim.switch_to_nearest(e, 1)
	sim.add_crowd(300, 1000)

## penalty_time_left (0x540f5): seconds until the team with more skaters loses its advantage
## (the shortest penalty of the short handed team), 0 at even strength
static func penalty_time_left(sim: Sim) -> int:
	var home := sim.teams[0]
	var away := sim.teams[1]
	if home.skaters_on_ice == away.skaters_on_ice:
		return 0
	var short_team := away if home.skaters_on_ice > away.skaters_on_ice else home
	var left := 0x7fff
	for pen in short_team.penalties:
		left = mini(left, pen[1])
	return left if left != 0x7fff else 0

## penalty_timers (0x63a37): penalties run with the game clock; the first expired one returns
static func penalty_timers(sim: Sim) -> void:
	for t in 2:
		var team := sim.teams[t]
		var i := 0
		while i < team.penalties.size():
			var pen: Array = team.penalties[i]
			pen[1] -= 1
			if pen[1] <= 0:
				penalty_expired(sim, team, i)
			else:
				i += 1

## penalty_expired (0x639f9): the player leaves the box
static func penalty_expired(sim: Sim, team: Team, idx: int) -> void:
	var pen: Array = team.penalties[idx]
	team.penalties.remove_at(idx)
	var e: Entity = sim.entities[pen[2]]
	team.skaters_on_ice = clampi(6 - team.penalties.size(), 4, 6)
	if e.roster_idx >= 0:
		team.entity_of[e.roster_idx] = -1
	if e.line_slot < 0:
		e.line_slot = e.line_slot & 0xff      # DOOR_OPEN only set the high byte
	if e.line_slot <= 0:
		e.line_slot = 5 if e.slot % 6 == 5 else maxi(1, e.slot % 6)
	e.set_state(Entity.State.EXIT_PENALTY_BOX)

## goal_ends_penalty (0x63d69): a power play goal releases the first minor of the conceding team
static func goal_ends_penalty(sim: Sim, conceding: Team, scoring: Team) -> void:
	if conceding.skaters_on_ice >= scoring.skaters_on_ice:
		return
	for i in conceding.penalties.size():
		if conceding.penalties[i][3]:
			penalty_expired(sim, conceding, i)
			return

## process_infractions (0x637b5): the first queued event stops the play; penalties against the
## team that does not have the puck are delayed until it touches it
static func process_infractions(sim: Sim) -> void:
	for i in sim.infractions.size():
		var inf: Array = sim.infractions[i]
		var type: int = inf[0]
		if not sim.stoppage_countdown:
			var penalty := Tables.infraction_is_penalty[type] != 0
			if not penalty:
				start_stoppage(sim, i)
			elif sim.puck_carrier >= 0 and sim.same_team(inf[1], sim.puck_carrier):
				sim.whistle_timer = 0x28
				start_stoppage(sim, i)
			else:
				if not sim.delayed_call:
					sim.delayed_call = true   # the referee's arm goes up (announcement 0x1c)
				continue
		if not inf[2]:
			inf[2] = true
			var dur := Tables.stoppage_duration[type] << 5
			if sim.stoppage_timer < dur:
				sim.stoppage_timer = dur
			var delay := Tables.announce_delay[type] * 0x20
			if sim.announce_timer < delay:
				sim.announce_timer = delay

## start_stoppage (0x63fb2): whistle; the faceoff spot follows from the event
static func start_stoppage(sim: Sim, idx: int) -> void:
	var inf: Array = sim.infractions[idx]
	var type: int = inf[0]
	var culprit: Entity = sim.entities[inf[1]]
	if not sim.play_stopped:
		sim.play_stopped = true
		var fx := 0
		var fy := 0
		if type != INF_GOAL:
			fx = sim.last_touch_x
			fy = sim.last_touch_y
			if type != INF_FROZEN and type != INF_TWO_LINE:
				fx = sim.puck.xi
				fy = sim.puck.yi
				if type == INF_OFFSIDE:
					if absi(fy) < 0x4e:
						fy = -0x4e if fy < 0 else 0x4e
				elif type == INF_ICING:
					fy = -600 if (culprit.flags & Entity.F_ATTACK_UP) else 600
		# snap to the nearest dot: x = +-96, y = +-184 in the end zones, neutral zone dots at +-100/+-61
		fx = clampi(fx, -0x60, 0x60)
		if fy >= 0x90:
			fx = -0x60 if fx < 0 else 0x60
			fy = 0xb8
		elif fy < -0x8f:
			fx = -0x60 if fx < 0 else 0x60
			fy = -0xb8
		for inf2 in sim.infractions:
			var c: Entity = sim.entities[inf2[1]]
			if (c.flags & Entity.F_ATTACK_UP) == 0:
				if fy < -0x4d:
					fy = -0x3d
					fx = -100 if fx < 0 else 100
			elif fy > 0x4d:
				fy = 0x3d
				fx = -100 if fx < 0 else 100
		sim.faceoff_x = fx
		sim.faceoff_y = fy
	sim.stoppage_timer = 0
	sim.stoppage_countdown = true
	sim.play_sfx(0xa4)               # whistle
	# sub_62ea2: the referee announces the call (not for a plain whistle / delayed call)
	if type != INF_PENALTY_SHOT_END and type != 0x1c:
		sim.ref_phase = 0
		sim.ref_infraction = type
		sim.referee.set_state(Entity.State.REF_POINT_GOAL if type == INF_GOAL else Entity.State.REF_CALL_PENALTY)

## queue_infraction (0x52d80)
static func queue_infraction(sim: Sim, e: Entity, type: int) -> void:
	if sim.infractions.size() >= 0x20:
		return
	if type > INF_ICING:
		sim.add_crowd(400, 800)
		if e.flags & Entity.F_PLAYER2:
			sim.excitement += 0x14
			sim.play_sfx(0x7d)
		else:
			sim.play_sfx(0xa0)
	if Tables.infraction_is_penalty[type] != 0:
		if e.flags2 & Entity.F2_PENALIZED:
			return
		e.flags2 |= Entity.F2_PENALIZED
	sim.infractions.append([type, e.slot, false])

## maybe_queue_infraction (0x52cf9): rule events filtered by the option flags
static func maybe_queue_infraction(sim: Sim, e: Entity, type: int) -> void:
	if sim.play_stopped or e.slot == Entity.Slot.REFEREE or sim.penalty_shot:
		return
	if type != INF_ICING:
		if type == INF_OFFSIDE:
			if not sim.opt_offsides:
				return
		elif type == INF_TWO_LINE:
			if not sim.opt_two_line_pass:
				return
		elif not sim.opt_penalties:
			return
	queue_infraction(sim, e, type)

## update_effects (0x615a3): crowd noise decays towards the ambient level
static func update_effects(sim: Sim) -> void:
	if sim.crowd_noise >= 0x2bd:
		sim.crowd_noise -= 2
	elif sim.crowd_noise > 0x15e:
		sim.crowd_noise -= 3
	sim.crowd_noise -= 1
	if sim.crowd_noise < 0:
		sim.crowd_noise = 0
		if sim.random(0x10) == 0:
			sim.crowd_noise = sim.random(0x20)
	if sim.excitement > 0:
		sim.excitement -= 1


## update_lead_change (0x63c9a)
static func update_lead_change(sim: Sim) -> void:
	var diff := sim.teams[0].goals - sim.teams[1].goals
	if diff == 0:
		sim.lead_announced = false
		return
	var leader := 0 if diff > 0 else 1
	if sim.leading_team != leader:
		sim.lead_announced = false
	sim.leading_team = leader
	if not sim.lead_announced:
		sim.lead_announced = true

## game_clock_tick (0x5dc10): 24 sub ticks per second
static func game_clock_tick(sim: Sim) -> void:
	if sim.clock_seconds == 0 and sim.clock_sub == 0:
		return
	if sim.clock_sub - 1 >= 0:
		sim.clock_sub -= 1
		return
	if sim.clock_seconds < 1:
		sim.clock_sub = 0
	else:
		sim.clock_seconds -= 1
		sim.clock_sub += 0x17
	if sim.clock_seconds == 0x3c:
		sim.play_sfx(0x97)   # one minute warning

# --------------------------------------------------------------------------------------------
# goals (score_goal 0x5ab36) and the end of a period (setup_faceoff 0x5d852)
# --------------------------------------------------------------------------------------------

static func score_goal(sim: Sim, net: Entity) -> void:
	var puck := sim.puck
	# the team that shoots at this net scores
	var scorer_team := 0
	for t in 2:
		if sim.teams[t].attacks_up == (net.yi > 0):
			scorer_team = t
	var scoring := sim.teams[scorer_team]
	var conceding := sim.teams[1 - scorer_team]
	var allowed := not sim.play_stopped and not goal_disallowed(sim, scorer_team) and (scoring.flags & Team.FL_OFFSIDE) == 0
	if allowed:
		scoring.goals += 1
		if sim.last_touch_slot >= 0 and sim.same_team(sim.last_touch_slot, scoring.first_slot):
			sim.last_shooter = sim.last_touch_slot
		PuckLogic.shot_landed(sim)
		goal_ends_penalty(sim, conceding, scoring)
		sim.play_sfx(0x9c)        # goal horn
		sim.action_hold_camera = true
		sim.camera_target_x = sim.camera_x
		sim.camera_target_y = sim.camera_y
		if scorer_team == 0:
			sim.crowd_noise = clampi(sim.crowd_noise + 800, 0x708, 2000)
			sim.excitement += 0x1e
		else:
			sim.crowd_noise = maxi(sim.crowd_noise, 800)
			sim.excitement += 10
		# everyone celebrates / skates to the bench
		for i in 6:
			var p := sim.entities[scoring.first_slot + i]
			if p.line_slot > 0 and (p.flags2 & Entity.F2_KNOCKED) == 0:
				p.flags &= ~Entity.F_ARRIVED
				p.set_state_reset(Entity.State.CELEBRATE)
		sim.puck_in_net = false
		puck.x = (-6 if puck.xi < 0 else 6) * 0x10000
		puck.vx = 0
		puck.y = (-0xf0 if puck.yi < 0 else 0xf0) * 0x10000
		puck.vy = 0
		puck.z = 0x600 << 4
		puck.vz = 0
		puck.flags3 |= 4
		puck.set_state(Entity.State.PUCK_IDLE)
		Anim.set_animation(sim.shadow, 0x7fd)
		queue_infraction(sim, sim.entities[conceding.first_slot], INF_GOAL)
		sim.referee.set_state(Entity.State.REF_NORMAL)
	else:
		sim.puck_in_net = false
		puck.x = (puck.xi + (-6 if puck.xi < net.xi else 6)) * 0x10000
		puck.vx = 0
		puck.y = (puck.yi + (-4 if puck.yi < 0 else 4)) * 0x10000
		puck.vy = 0
		puck.z = 0x600 << 4
		puck.vz = 0
		puck.flags3 |= 4
		if not sim.play_stopped:
			puck.set_state(Entity.State.PUCK_IDLE)
			if scoring.flags & Team.FL_OFFSIDE:
				maybe_queue_infraction(sim, sim.entities[scoring.first_slot], INF_OFFSIDE)
			queue_infraction(sim, sim.entities[conceding.first_slot], INF_DISALLOWED)
	sim.one_timer = false
	sim.breakaway = false

## goal_disallowed_check (0x5afc8): a delayed penalty against the scoring team cancels the goal
static func goal_disallowed(sim: Sim, scorer_team: int) -> bool:
	if not sim.delayed_call:
		return false
	for i in 6:
		var p := sim.entities[scorer_team * 6 + i]
		if p.line_slot >= 0 and (p.flags2 & Entity.F2_PENALIZED):
			return true
	return false

## setup_faceoff (0x5d852): the clock ran out; next period or end of the game
static func setup_faceoff(sim: Sim) -> void:
	sim.puck.set_state_reset(Entity.State.PUCK_NORMAL)
	var diff := sim.teams[0].goals - sim.teams[1].goals
	if sim.period < 2:
		queue_infraction(sim, sim.puck, INF_PERIOD_END)
		return
	if diff == 0:
		# tie after regulation: overtime (sudden death) when enabled, here always
		queue_infraction(sim, sim.puck, INF_PERIOD_END)
		return
	sim.user1_slot = -1
	sim.user2_slot = -1
	sim.puck_carrier = -1
	sim.game_over = true
	sim.play_stopped = true
	sim.action_hold_camera = true
	var winner := sim.teams[0 if diff > 0 else 1]
	for i in 6:
		var p := sim.entities[winner.first_slot + i]
		if p.line_slot > 0:
			p.set_state_reset(Entity.State.CELEBRATE)
	sim.crowd_noise = maxi(sim.crowd_noise, 800)
	sim.excitement += 0x28
	queue_infraction(sim, sim.puck, INF_PERIOD_END)

## called by the puck faceoff handler when a period ended: advance to the next one
static func next_period(sim: Sim) -> void:
	sim.period_over = true
	if sim.game_over:
		return
	sim.infractions.clear()
	sim.start_period(sim.period + 1)

# --------------------------------------------------------------------------------------------
# offside, icing, breakaway
# --------------------------------------------------------------------------------------------

## check_offside (0x55a9f): attackers inside the zone before the puck set the team's offside flag
static func check_offside(sim: Sim) -> void:
	if not sim.opt_offsides or sim.penalty_shot:
		return
	var puck := sim.puck
	# clear the flag of a team once all its players left the zone
	for t in 2:
		var team := sim.teams[t]
		if team.flags & Team.FL_OFFSIDE:
			var inside := false
			for i in 6:
				var p := sim.entities[t * 6 + i]
				if p.line_slot >= 0:
					var py := p.yi if (p.flags & Entity.F_ATTACK_UP) else -p.yi
					if py > 0x4e:
						inside = true
						break
			if not inside:
				team.flags &= ~Team.FL_OFFSIDE
	var prev_y := puck.prev_y >> 16
	var line := 0
	if puck.yi >= 0x4a:
		if prev_y > 0x49:
			return
		line = 0x4a
	elif puck.yi <= -0x4a:
		if prev_y < -0x49:
			return
		line = -0x4a
	else:
		return
	# the puck just crossed a blue line: the team attacking that zone
	count_defenders_ahead(sim)
	var attacking: Team = sim.teams[0] if sim.teams[0].attacks_up == (line > 0) else sim.teams[1]
	if sim.last_touch_slot >= 0 and sim.same_team(sim.last_touch_slot, attacking.first_slot):
		var limit := line + (10 if line > 0 else -10)
		for i in 6:
			var p := sim.entities[attacking.first_slot + i]
			if p.line_slot >= 0 and ((line > 0 and p.yi > limit) or (line < 0 and p.yi < limit)):
				attacking.flags |= Team.FL_OFFSIDE
		return
	attacking.flags &= ~Team.FL_OFFSIDE

## update_offside_flags (0x4de3f): per player flag for the two line pass rule
static func update_offside_flags(sim: Sim) -> void:
	if not sim.opt_two_line_pass:
		return
	var puck := sim.puck
	var prev_y := puck.prev_y >> 16
	if (puck.yi < 0) == (prev_y < 0):
		return
	for t in 2:
		var team := sim.teams[t]
		var attacks_this_half := team.attacks_up == (puck.yi >= 0)
		for i in 6:
			var p := sim.entities[t * 6 + i]
			if attacks_this_half and p.line_slot >= 0 and ((puck.yi < 0 and p.yi < 0) or (puck.yi >= 0 and p.yi > 0)):
				p.flags2 |= Entity.F2_OFFSIDE
			else:
				p.flags2 &= ~Entity.F2_OFFSIDE

## check_icing (0x56e52): a puck shot from the own half crossing the far goal line untouched
static func check_icing(sim: Sim) -> void:
	if (sim.icing_flags & 4) == 0 or (sim.icing_flags & 1) or sim.puck_carrier >= 0:
		return
	var puck := sim.puck
	if (sim.icing_flags & 2) == 0:
		if puck.yi > -0xe9:
			return
	elif puck.yi < 0xe8:
		return
	if absi(puck.xi) < 0x2d:
		sim.icing_flags &= ~4     # through the goal area: no icing
		return
	sim.icing_flags |= 1
	if sim.icing_shooter >= 0:
		maybe_queue_infraction(sim, sim.entities[sim.icing_shooter], INF_ICING)

## two_line_pass_check (0x55f9e)
static func two_line_pass_check(sim: Sim, receiver: Entity) -> bool:
	if not sim.opt_offsides or sim.no_stats or sim.penalty_shot:
		return false
	var puck := sim.puck
	if absi(puck.yi) >= 0xe9:
		return false
	var pred: Array = sim.goal_prediction[0 if (receiver.flags & Entity.F_ATTACK_UP) else 1]
	if absi(pred[0]) >= 0x2d or (sim.opponents_of(receiver).flags & Team.FL_OFFSIDE) == 0:
		return false
	if sim.last_touch_slot >= 0 and sim.same_team(sim.last_touch_slot, receiver.slot):
		return false
	queue_infraction(sim, sim.entities[maxi(0, sim.last_touch_slot)], INF_OFFSIDE)
	return true

## count_defenders_ahead (0x640c6): true when the carrier has nobody between him and the net
static func count_defenders_ahead(sim: Sim) -> bool:
	sim.defenders_ahead = 0
	if sim.puck_carrier < 0 or sim.puck_carrier >= 12:
		return false
	var c := sim.entities[sim.puck_carrier]
	var cy := c.yi
	var up := (c.flags & Entity.F_ATTACK_UP) != 0
	if up and cy < 0:
		return false
	if not up and cy > 0:
		return false
	var goal_y := 0xe8 if up else -0xe8
	var cd := Sim.approx_distance(cy - goal_y, c.xi)
	var opp := sim.opponents_of(c)
	for i in 6:
		var p := sim.entities[opp.first_slot + i]
		if p.line_slot <= 0:
			continue
		if up:
			if p.yi > cy + 4 or (p.vy >= 0 and Sim.approx_distance(p.yi - 0xe8, p.xi) <= cd):
				return false
		else:
			if p.yi < cy - 4 or (p.vy <= 0 and Sim.approx_distance(p.yi + 0xe8, p.xi) <= cd):
				return false
	sim.defenders_ahead = 1
	return true

## sub_64338: breakaway bookkeeping when the puck crosses the blue line
static func note_breakaway(sim: Sim) -> void:
	count_defenders_ahead(sim)
	sim.breakaway = sim.defenders_ahead != 0
	if sim.breakaway:
		sim.crowd_noise += 100

# --------------------------------------------------------------------------------------------
# faceoffs (ai_puck_faceoff2 positioning, faceoff_resolve)
# --------------------------------------------------------------------------------------------

## position of a player at the faceoff (ai_all_goto_faceoff / ai_puck_faceoff2 share this)
static func faceoff_position(sim: Sim, e: Entity) -> Vector2i:
	var team := sim.team_of(e)
	var row := clampi(6 - team.skaters_on_ice, 0, 2)
	var lineup: Array = Tables.faceoff_lineup[row]
	var idx: int = lineup[clampi(e.line_slot, 0, 7)]
	var spot: Array = Tables.faceoff_spots[idx]
	var sx: int = spot[0]
	var sy: int = spot[1]
	if (e.flags & Entity.F_ATTACK_UP) == 0:
		sx = -sx
		sy = -sy
	var fx := sim.faceoff_x
	var fy := sim.faceoff_y
	if e.line_slot == 0:
		# the goalie stays in the crease, shaded towards the faceoff side
		if absi(fy) > 0x27 and (fy < 0) != ((e.flags & Entity.F_ATTACK_UP) != 0):
			var d := absi(fy - (0x27 if (e.flags & Entity.F_ATTACK_UP) else -0x27))
			sx += (fx * d * 3) >> 12
		return Vector2i(sx, sy)
	if idx < 5:
		# wingers and defence squeeze towards the middle when the dot is off centre
		if (sx ^ fx) < 0:
			sy -= fy >> 3
		sx -= fx >> 2
	return Vector2i(sx + fx, sy + fy)

## the block of ai_puck_faceoff2 that snaps everybody into place before the drop
static func place_faceoff(sim: Sim) -> void:
	sim.faceoff_pending = true
	sim.whistle_ready = true
	sim.play_stopped = true
	sim.stoppage_countdown = false
	sim.stoppage_timer = -1
	sim.announce_timer = -1
	sim.delayed_call = false
	sim.infractions.clear()
	sim.shot_in_flight = false
	sim.pass_target = -1
	sim.icing_flags = 0
	sim.whistle_timer = 0
	sim.action_hold_camera = false
	sim.camera_target_x = clampi(sim.faceoff_x, -0x20, 0x20)
	sim.camera_target_y = clampi(sim.faceoff_y, -0xbc, 0xec)
	sim.camera_x = sim.camera_target_x
	sim.camera_y = sim.camera_target_y
	sim.camera_offset_y = 0
	var puck := sim.puck
	puck.set_pos(sim.faceoff_x, sim.faceoff_y)
	puck.z = -100 * 0x10000      # in the referee's hand
	puck.vx = 0
	puck.vy = 0
	puck.vz = 0
	puck.flags3 = 0
	sim.puck_carrier = -1
	sim.last_touch_x = sim.faceoff_x
	sim.last_touch_y = sim.faceoff_y
	sim.last_touch_slot = -1
	sim.last_passer = -1
	sim.last_shooter = -1
	Lines.flush_pending(sim)
	for i in 12:
		var e := sim.entities[i]
		e.flags2 &= ~Entity.F2_OFFSIDE
		if e.line_slot < 0 or e.state() == Entity.State.PENALTY_BOX or e.state() == Entity.State.DOOR_OPEN:
			continue
		# sub_5e0dd: a player coming onto the ice gets his role on the stack (and NEAREST for the centre)
		if e.state() == Entity.State.INIT_PERIOD or e.state() == Entity.State.ALL_GOTO_FACEOFF:
			AI.set_default_state(sim, e)
			if e.line_slot == 4:
				e.set_state_reset(Entity.State.NEAREST)
		if e.line_slot != 0:
			if e.line_slot == 4:
				var team := sim.team_of(e)
				team.carrier_history = PackedInt32Array([e.roster_idx, -1, -1])
				e.set_state_reset(Entity.State.FACEOFF)
			else:
				e.set_state_reset(Entity.State.FACEOFF_WAIT)
		var pos := faceoff_position(sim, e)
		e.set_pos(pos.x, pos.y)
		e.vx = 0
		e.vy = 0
		e.facing = Tables.direction8(sim.faceoff_x - pos.x, sim.faceoff_y - pos.y)
		var a := Anim.GLIDE
		if e.line_slot == 0:
			var f := (8 - e.facing) & 7 if e.left_handed == 0 else e.facing
			e.frame = f * 3 + 0x196
			a = 1
			if e.facing == 2:
				e.facing = 3 if (e.flags & Entity.F_ATTACK_UP) == 0 else 1
			elif e.facing == 6:
				e.facing = 5 if (e.flags & Entity.F_ATTACK_UP) == 0 else 7
		elif e.line_slot == 4:
			e.frame = 0x16c if e.facing == 0 else 0x167
			a = 0
		else:
			var f := (8 - e.facing) & 7 if e.left_handed == 0 else e.facing
			e.frame = f * 5
		e.flags2 &= ~Entity.F2_UNSELECTABLE
		e.flags &= ~Entity.F_BUSY
		Anim.set_animation(e, a)
	var ref := sim.referee
	var rside := 2 if sim.faceoff_x <= 0 else 6
	ref.set_pos(sim.faceoff_x + (-0xf if sim.faceoff_x <= 0 else 0xf), sim.faceoff_y)
	ref.facing = rside
	ref.frame = 0x2bf if rside < 4 else 0x2c7
	ref.set_state_reset(Entity.State.REF_FACEOFF)
	ref.vx = 0
	ref.vy = 0
	ref.flags2 &= ~Entity.F2_NO_COLLIDE
	Anim.set_animation(ref, 0xc57)
	sim.user1_slot = -1
	sim.user2_slot = -1
	if sim.user1_team != 0:
		sim.user1_slot = sim.find_switch_target(sim.centre_slot(sim.user1_team - 1), -1)
	if sim.user2_team != 0:
		sim.user2_slot = sim.find_switch_target(sim.centre_slot(sim.user2_team - 1), -1)
		sim.entities[sim.user2_slot].flags |= Entity.F_PLAYER2
	sim.faceoff_ready = [1, 4]
	sim.faceoff_side = [0x8800 if not sim.ends_switched else 0x8000, 0xa000 if not sim.ends_switched else 0xa800]
	sim.faceoff_dir = [-1, -1]
	sim.faceoff_timer = 7
	puck.timer_a = sim.random(0x78) + 0xb4

## faceoff_resolve (0x4db2b): the drop; the winner is decided by the centres' readiness and skill
static func faceoff_resolve(sim: Sim) -> void:
	sim.play_sfx(0xab)
	sim.faceoff_pending = false
	sim.whistle_ready = false
	sim.play_stopped = false
	sim.puck.flags2 &= ~Entity.F2_KNOCKED
	sim.misc_first_touch = true
	var home_c := -1
	var away_c := -1
	for i in 6:
		if sim.entities[i].line_slot == 4:
			home_c = i
		if sim.entities[6 + i].line_slot == 4:
			away_c = 6 + i
	var r0: int = clampi(sim.faceoff_ready[0], 0, 6)
	var r1: int = clampi(sim.faceoff_ready[1], 0, 6)
	var chance := (0x10 - Tables.faceoff_bonus[r0]) + Tables.faceoff_bonus[r1]
	if home_c >= 0 and away_c >= 0:
		chance += sim.entities[away_c].offense - sim.entities[home_c].offense
	var home_wins := sim.random(0x21) >= chance
	var winner := home_c if home_wins else away_c
	var side: int = sim.faceoff_side[0 if home_wins else 1]
	sim.last_touch_slot = winner
	var dir := 8
	var vy_bias := 0x800 if (side & 0x800) == 0 else -0x800
	var held: int = sim.faceoff_dir[0 if (side & 0x800) == 0 else 1]
	if held >= 0 and held < 8 and (held & 8) == 0:
		dir = held
		if sim.random(4) == 0:
			dir = (dir + sim.random(5) - 2) & 7
	else:
		dir = (sim.random(5) - 2) & 7
		if vy_bias < 0:
			dir ^= 4
	var v: Array = Tables.dir8_vectors[dir]
	var puck := sim.puck
	puck.vx = v[0] << 5
	puck.vy = (v[1] << 5) + vy_bias
	puck.vz = sim.random(0x800)
	puck.z = 0
	puck.flags &= ~Entity.F_ARRIVED
	puck.set_state(Entity.State.PUCK_NORMAL)
	sim.referee.set_state(Entity.State.REF_NORMAL)
	sim.referee.vx = -0x500 if sim.referee.xi > 0 else 0x500
	if winner >= 0:
		sim.team_of(sim.entities[winner]).faceoffs_won += 1

## all_goto_positions (0x512c1): after the whistle everybody skates to the faceoff spot
static func all_goto_positions(sim: Sim) -> void:
	for i in 12:
		var e := sim.entities[i]
		if e.line_slot < 0:
			continue
		e.timer_b = 0
		var s := e.state()
		if s == Entity.State.PENALTY_BOX or s == Entity.State.DOOR_OPEN or s == Entity.State.EXIT_PENALTY_BOX:
			continue
		if s == Entity.State.BENCH or s == Entity.State.EXIT_BENCH or s == Entity.State.BENCH_WAIT or e.next_roster >= 0:
			continue      # changing: handle_line_change / ai_bench take him to the faceoff afterwards
		if s != Entity.State.INIT_PERIOD and s != Entity.State.ALL_GOTO_FACEOFF:
			e.set_state_reset(Entity.State.ALL_GOTO_FACEOFF)
