class_name Rules
## Game rules: the clock, stoppages and the infraction queue, faceoff placement, goals, offside and
## icing, penalties (box, game misconduct, penalty shot). Ports of sim_game_state, update_stoppage,
## process_infractions, start_stoppage, queue_infraction, maybe_queue_infraction,
## penalty_box_update, game_clock_tick, score_goal, setup_faceoff, check_offside, check_icing,
## faceoff_resolve, the positioning part of ai_puck_faceoff2 and the penalty shot routines
## (breakaway_foul, begin_penalty_shot, start_penalty_shot, end_penalty_shot).

# infraction / event ids (infraction_queue, infraction_priority, infraction_is_penalty). The
# penalty names follow the speech table off_cd354[type - 9] used by record_penalty.
const INF_PERIOD_START := 1
const INF_PERIOD_END := 2
const INF_FROZEN := 3            # puck frozen, held or out of play
const INF_GOALIE_HOLD := 4
const INF_PENALTY_SHOT_END := 5
const INF_ICING := 6
const INF_GOAL := 7
const INF_OFFSIDE := 8
const INF_ROUGHING := 9          # 9, 11 .. 21: two minute minors
const INF_INJURY := 10           # a player is hurt (whistle, no penalty)
const INF_CHARGING := 11
const INF_SLASHING := 12
const INF_ROUGHING_HIT := 13
const INF_CROSS_CHECK := 14
const INF_HOOKING := 15
const INF_TRIPPING := 16
const INF_INTERFERENCE := 17     # also goalie interference (goalie_collision)
const INF_HOLDING := 18
const INF_HIGH_STICK := 19
const INF_BOARDING := 20
const INF_ELBOWING := 21
const INF_ABUSE_OF_OFFICIAL := 22   # game misconduct (infraction_is_penalty -1)
const INF_CHECK_FROM_BEHIND := 23   # 23 .. 25: five minute majors
const INF_BOARDING_MAJOR := 24
const INF_ELBOWING_MAJOR := 25
const INF_PENALTY_SHOT := 26        # a foul on a breakaway
const INF_DISALLOWED := 27
const INF_DELAYED_CALL := 28
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
	if sim.penalty_box_mode:
		return
	Lines.cpu_line_change(sim)
	# the 24 Hz tick of sim_game_state: energy, lead changes
	if sim.step_count % 24 == 0:
		Lines.regenerate_energy(sim)
		if not sim.play_stopped:
			update_power_play(sim)

## update_stoppage (0x63929): runs the infraction queue and the whistle / stoppage timers. While
## the stoppage timer runs the referee keeps following the play; once it expired the queued calls
## are signalled one after another (penalty_box_update).
static func update_stoppage(sim: Sim) -> void:
	process_infractions(sim)
	if not sim.play_stopped:
		return
	InfoPanel.update(sim)
	if sim.announce_timer >= 0:
		sim.announce_timer -= 1
		if sim.announce_timer < 0:
			sim.whistle_ready = true
	if not sim.stoppage_countdown:
		return
	if sim.stoppage_timer < 0:
		penalty_box_update(sim)
		return
	sim.whistle_timer = maxi(0, sim.whistle_timer - 1)
	sim.stoppage_timer -= 1
	if sim.stoppage_timer < 0:
		sim.delayed_call = false
		sim.whistle_timer = 0
		# a penalty among the calls: the penalty box sequence (no new calls, the 24 Hz tick
		# pauses, the puck lies dead until the referee collected it)
		for inf: Array in sim.infractions:
			if Tables.infraction_is_penalty[inf[0]] != 0:
				sim.whistle_ready = true
				sim.announce_timer = -1
				sim.penalty_box_mode = true
				sim.puck_carrier = -1
				sim.puck.set_state_reset(Entity.State.PUCK_IDLE)
				sim.faceoff_timer = 0x1c20
				if sim.ref_phase >= 0:
					sim.ref_phase = (sim.ref_phase & 0xff) - 0x100   # high byte 0xff
				if sim.message_timer == 0:
					sim.message = -1
				break

## ref_announce (0x62ea2): the referee signals the call (ai_ref_call_penalty) or points at the
## goal (ai_ref_point_goal); the end of a penalty shot and the delayed call (0x1c) are silent
static func ref_announce(sim: Sim, type: int, slot: int = -1) -> void:
	if type == INF_PENALTY_SHOT_END or type == INF_DELAYED_CALL:
		return
	sim.ref_phase = 0
	sim.ref_infraction = type
	sim.ref_infraction_slot = slot
	sim.referee.set_state(Entity.State.REF_POINT_GOAL if type == INF_GOAL else Entity.State.REF_CALL_PENALTY)

## penalty_box_update (0x62ee9): once the stoppage timer expired and the referee is free
## (ref_phase != 0) the last queued call is handled: penalties send the player to the box (an
## injured culprit's penalty is served by a team mate), the call is signalled, and the entry stays
## queued until the player left the ice. With the queue empty the faceoff is prepared.
static func penalty_box_update(sim: Sim) -> void:
	if sim.ref_phase == 0 or sim.speech_busy:
		return
	while true:
		if sim.infractions.is_empty():
			if sim.clip != InfoPanel.CLIP_FAN_ANTHEM and sim.clip != InfoPanel.CLIP_CLAP and sim.panel >= 0:
				return
			for t in 2:
				var team := sim.teams[t]
				# a team never plays with fewer than 3 skaters: extra penalties are stacked
				team.skaters_on_ice = clampi(6 - team.penalties.size(), 4, 6)
			sim.stoppage_countdown = false
			var ps := sim.puck.state()
			if ps == Entity.State.PUCK_FACEOFF or ps == Entity.State.PUCK_FACEOFF2:
				return
			sim.puck.set_state(Entity.State.PUCK_FACEOFF)
			return
		var inf: Array = sim.infractions[sim.infractions.size() - 1]
		var e: Entity = sim.entities[inf[1]]
		if not inf[2]:
			# a delayed call or a player still on his way to the box
			if e.line_slot >= 0:
				return
			e.flags2 &= ~Entity.F2_PENALIZED
			sim.infractions.pop_back()
			return
		inf[2] = false
		var type: int = inf[0]
		if type == INF_PENALTY_SHOT:
			sim.infractions.pop_back()
			e.flags2 &= ~Entity.F2_PENALIZED
			begin_penalty_shot(sim)
			# the referee picks up the puck again: the shooter and the goalie line up, the others
			# wait at the benches (all_goto_positions with the shot phase set)
			all_goto_positions(sim)
			ref_announce(sim, type, e.slot)
			return
		var minutes: int = Tables.infraction_is_penalty[type]
		if minutes < 0:
			sim.infractions.pop_back()
			e.flags2 &= ~Entity.F2_PENALIZED
			game_misconduct(sim, e, sim.infractions.size())
			ref_announce(sim, type, e.slot)
			return
		if minutes > 0:
			if e.slot >= 12 or e.roster_idx < 0:
				sim.infractions.pop_back()
				continue
			var team := sim.team_of(e)
			var server := e
			if team.entity_of[e.roster_idx] == -3 or team.entity_of[e.roster_idx] == -4:
				# the culprit is injured: a skater on the ice serves the penalty
				server = null
				for k in 6:
					var p: Entity = sim.entities[team.index * 6 + k]
					if p.line_slot >= 1 and p.roster_idx >= 0 and team.entity_of[p.roster_idx] == -1 \
							and (p.flags2 & Entity.F2_PENALIZED) == 0:
						server = p
						break
				if server == null:
					return
				inf[1] = server.slot
			sim.infraction_type_served = type
			serve_penalty(sim, e, minutes, server, sim.infractions.size() - 1)
			e.flags2 &= ~Entity.F2_PENALIZED
			ref_announce(sim, type, e.slot)
			return
		sim.infractions.pop_back()
		if not sim.penalty_box_mode or type == INF_GOAL:
			ref_announce(sim, type, e.slot)
			return

## the player goes to the penalty box (penalty_box_update, record_penalty)
## (the culprit's minutes and the panel entry; server is the skater who sits in the box)
static func serve_penalty(sim: Sim, e: Entity, minutes: int, server: Entity = null, queue_index: int = 0) -> void:
	if server == null:
		server = e
	var team := sim.team_of(e)
	for pen in team.penalties:
		if pen[2] == server.slot:
			return
	team.penalties.append([server.roster_idx, minutes * 60, server.slot, minutes == 2])
	if not sim.no_stats:
		team.add_stat(e.roster_idx, Team.ST_PIM, minutes)
	InfoPanel.record_penalty(sim, team.index, e.roster_idx, sim.infraction_type_served, minutes, queue_index)
	if server != e:
		sim.panel_text[4] = "served by #%d" % server.number
	if server.roster_idx >= 0:
		team.entity_of[server.roster_idx] = 1        # in the box
	server.next_line_slot = -1
	server.next_roster = -1
	server.set_state(Entity.State.PENALTY_BOX)
	server.flags2 |= Entity.F2_UNSELECTABLE
	if server.slot == sim.user1_slot:
		sim.switch_to_nearest(server, 0)
	elif server.slot == sim.user2_slot:
		sim.switch_to_nearest(server, 1)
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
## The goal also wipes the queued calls: everything but the majors, the misconducts and the minors
## of the scoring team (all of them when the overtime goal ended the game).
static func goal_ends_penalty(sim: Sim, conceding: Team, scoring: Team) -> void:
	var ended := sim.period == 3 and sim.teams[0].goals != sim.teams[1].goals
	var kept: Array = []
	for inf: Array in sim.infractions:
		var pen: int = Tables.infraction_is_penalty[inf[0]]
		var keep := not ended and (pen == -1 or pen == 5 or (pen == 2 and sim.same_team(inf[1], scoring.first_slot)))
		if keep:
			kept.append(inf)
		elif inf[1] < 12:
			sim.entities[inf[1]].flags2 &= ~Entity.F2_PENALIZED
	sim.infractions = kept
	if sim.infractions.is_empty() and sim.message == 6:
		sim.message = -1
	if conceding.skaters_on_ice >= scoring.skaters_on_ice:
		return
	for i in conceding.penalties.size():
		if conceding.penalties[i][3]:
			penalty_expired(sim, conceding, i)
			return

## process_infractions (0x637b5): the first queued event stops the play; penalties against the
## team that does not have the puck are delayed until it touches it
static func process_infractions(sim: Sim) -> void:
	if sim.penalty_box_mode:
		return
	for i in sim.infractions.size():
		var inf: Array = sim.infractions[i]
		var type: int = inf[0]
		if not sim.stoppage_countdown:
			var penalty := Tables.infraction_is_penalty[type] != 0
			if not penalty:
				start_stoppage(sim, i)
			elif sim.puck_carrier >= 0 and sim.same_team(inf[1], sim.puck_carrier):
				sim.whistle_timer = 0x28
				if sim.message != -1:
					sim.message_timer = 0x50
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
			if sim.injury_stoppage:
				sim.stoppage_timer = 0x140
			var delay := Tables.announce_delay[type]
			if sim.penalty_shot_setup and type == INF_PENALTY_SHOT_END:
				# after the penalty shot (byte_c9111 / byte_c9146)
				sim.stoppage_timer = Tables.stoppage_duration[13] << 5
				delay = Tables.announce_delay[4]
			if sim.announce_timer < delay * 0x20:
				sim.announce_timer = delay * 0x20

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
		if sim.penalty_shot_setup:
			# after a penalty shot the play resumes where the foul happened
			fx = sim.penalty_shot_spot.x
			fy = sim.penalty_shot_spot.y
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
	# ref_announce(5): silent, the calls are signalled by penalty_box_update once the stoppage
	# timer expired

## queue_infraction (0x52d80)
static func queue_infraction(sim: Sim, e: Entity, type: int) -> void:
	if sim.infractions.size() >= 0x20 or sim.penalty_box_mode:
		return
	# the message box shows the most important call (infraction_priority = message id); the
	# PENALTY message stays until the penalty is handed out
	var prio: int = Tables.infraction_priority[type]
	if not sim.penalty_shot_setup and sim.message < prio:
		sim.message = prio
		if prio != -1 and prio != 6:
			sim.message_timer = 0x50
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
		else:
			if not sim.opt_penalties:
				return
			# penalized_count > 7, and the team must keep enough players of the culprit's position
			if e.slot < 12 and sim.team_of(e).penalties.size() > 7:
				return
			if e.slot < 12 and not injury_check(sim, e):
				return
	queue_infraction(sim, e, type)

## injury_check (0x65b83): may the player be lost (penalty, injury)? A defenceman only while more
## than 2 defencemen, a forward only while more than 4 forwards of the team are still available.
static func injury_check(sim: Sim, e: Entity) -> bool:
	if e.slot >= 12:
		return true
	var team := sim.team_of(e)
	var defence := Lines.position_class(team, 1)
	var group: Array = defence
	var need := 2
	if not defence.has(e.roster_idx):
		group = Lines.position_class(team, 0)
		need = 4
	var count := 0
	for r: int in group:
		if team.entity_of[r] == -1 or team.entity_of[r] == -2:
			count += 1
	return count > need

# --------------------------------------------------------------------------------------------
# penalty shot (breakaway_foul 0x6427f, begin_penalty_shot 0x64398, start_penalty_shot 0x63f72, end_penalty_shot 0x64439)
# --------------------------------------------------------------------------------------------

## breakaway_foul (0x6427f): is a foul on `victim` a foul on a breakaway? He carries the puck towards the net
## (moving and facing that way), nobody is between him and the net, he is not deeper than the
## goal line area and the goalie is in.
static func breakaway_foul(sim: Sim, victim: Entity) -> bool:
	if sim.no_stats or not sim.opt_penalties or sim.puck_carrier != victim.slot or not sim.breakaway:
		return false
	if (victim.flags & Entity.F_ATTACK_UP) == 0:
		if victim.vy > 0 or victim.facing < 3 or victim.facing > 5:
			return false
	elif victim.vy < 0 or (victim.facing > 1 and victim.facing < 7):
		return false
	count_defenders_ahead(sim)
	sim.breakaway = sim.defenders_ahead != 0
	if not sim.breakaway:
		return false
	return absi(victim.yi) <= 0xe4 and not sim.opponents_of(victim).goalie_pulled()

## the fouls on a breakaway (resolve_body_check, resolve_dive_hit, resolve_hook_hold): the fouled
## player will take the shot; the culprit gets infraction 0x1a. False when a shot is already set.
static func award_penalty_shot(sim: Sim, victim: Entity, culprit: Entity) -> bool:
	if sim.penalty_shot_slot >= 0:
		return false
	sim.penalty_shot_slot = victim.slot
	sim.penalty_shot_user = 1 if victim.slot == sim.user1_slot else -1
	maybe_queue_infraction(sim, culprit, INF_PENALTY_SHOT)
	return true

## begin_penalty_shot (0x64398, from penalty_box_update for infraction 0x1a): the shot is called. The faceoff spot of the
## stoppage is kept for afterwards and the puck goes to centre ice.
static func begin_penalty_shot(sim: Sim) -> void:
	if sim.penalty_shot_phase != 0 or sim.penalty_shot_slot < 0:
		return
	sim.penalty_shot_team = 1 if sim.penalty_shot_slot > 5 else 0
	sim.teams[sim.penalty_shot_team].penalty_shots += 1
	sim.penalty_shot_roster = sim.entities[sim.penalty_shot_slot].roster_idx
	sim.penalty_shot_phase = 1
	sim.penalty_shot_spot = Vector2i(sim.faceoff_x, sim.faceoff_y)
	sim.faceoff_x = 0
	sim.faceoff_y = 0
	sim.show_message(7, 0x100)          # PENALTY SHOT
	InfoPanel.record_penalty(sim, 1 - sim.penalty_shot_team, -1, INF_PENALTY_SHOT, 0)

## start_penalty_shot (0x63f72), from ai_puck_faceoff2 once the shooter and the goalie are set:
## the puck lies at centre ice, the shooter has it and plays the breakaway state
static func start_penalty_shot(sim: Sim) -> void:
	var puck := sim.puck
	puck.set_pos(0, 0)
	puck.z = 0
	puck.vx = 0
	puck.vy = 0
	puck.vz = 0
	puck.set_state(Entity.State.PUCK_NORMAL)
	var shooter := sim.entities[sim.penalty_shot_slot]
	shooter.flags2 &= ~(Entity.F2_UNSELECTABLE | Entity.F2_NO_COLLIDE)
	shooter.flags &= ~Entity.F_ARRIVED
	for i in 8:
		shooter.set_state_reset(Entity.State.BREAKAWAY)
	# the defending user controls nobody (find_switch_target(-1)): his goalie plays by himself
	var defending := 1 - sim.penalty_shot_team
	if sim.user1_team == defending + 1 and sim.user1_slot != -1:
		sim.user1_slot = sim.find_switch_target(-1, sim.user1_slot)
	if sim.user2_team == defending + 1 and sim.user2_slot != -1:
		sim.user2_slot = sim.find_switch_target(-1, sim.user2_slot)
	sim.teams[sim.penalty_shot_team].carrier_history = PackedInt32Array([-1, -1, -1])
	sim.crowd_noise += 100
	sim.puck_carrier = sim.penalty_shot_slot
	sim.penalty_shot = true
	sim.penalty_shot_setup = true
	sim.penalty_shot_clock = 1000
	sim.infractions.clear()

## the goalie of the team defending against the penalty shot
static func defending_goalie(sim: Sim) -> int:
	var defending := 1 - sim.penalty_shot_team
	for i in 6:
		var e := sim.entities[sim.teams[defending].first_slot + i]
		if e.line_slot == 0:
			return e.slot
	return -1

## end_penalty_shot (0x64439): goal, save, miss, timeout: back to the faceoff spot of the foul
static func end_penalty_shot(sim: Sim) -> void:
	if not sim.penalty_shot or sim.penalty_shot_phase == 0:
		return
	sim.penalty_shot_phase = 0
	sim.penalty_shot = false
	sim.penalty_shot_slot = -1
	queue_infraction(sim, sim.puck, INF_PENALTY_SHOT_END)
	sim.last_touch_x = sim.penalty_shot_spot.x
	sim.last_touch_y = sim.penalty_shot_spot.y
	sim.referee.set_state(Entity.State.REF_PICKUP)

## the game misconduct of penalty_box_update (infraction_is_penalty -1): the player is out for the
## game and skates off (ai_game_misconduct), no one serves time in the box
static func game_misconduct(sim: Sim, e: Entity, queue_index: int = 0) -> void:
	if e.slot >= 12 or e.roster_idx < 0:
		return
	var team := sim.team_of(e)
	if team.entity_of[e.roster_idx] > -3:
		e.next_line_slot = -1
		e.next_roster = -1
		e.set_state(Entity.State.GAME_MISCONDUCT)
	team.entity_of[e.roster_idx] = -5
	sim.show_message(6, 0x100)          # PENALTY
	InfoPanel.record_penalty(sim, team.index, e.roster_idx, INF_ABUSE_OF_OFFICIAL, -1, queue_index)


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
	Crowd.update(sim)


## update_power_play (0x63c73): the skaters on the ice (team +0x36) differ: a power play starts,
## counted for the team with more skaters (team +4); the organ plays its song (cue 1 home, 4 away)
## when the announcer is off and play is stopped (never at the only call, which runs while the
## puck is in play)
static func update_power_play(sim: Sim) -> void:
	var diff := sim.teams[0].skaters_on_ice - sim.teams[1].skaters_on_ice
	if diff == 0:
		sim.power_play = false
		return
	var team := 0 if diff > 0 else 1
	if sim.power_play_team != team:
		sim.power_play = false
	sim.power_play_team = team
	if not sim.power_play:
		sim.power_play = true
		sim.teams[team].power_plays += 1
		if sim.play_stopped and not InfoPanel.speech_on(sim):
			InfoPanel.music(sim, 1 if team == 0 else 4)

## game_clock_tick (0x5dc10): 24 sub ticks per second
static func game_clock_tick(sim: Sim) -> void:
	if sim.penalty_shot:
		# the game clock stands still; the shot must be over within 1000 steps
		sim.penalty_shot_clock -= 1
		if sim.penalty_shot_clock <= 0:
			end_penalty_shot(sim)
		return
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
	# one minute left: the tone (on 61 and 60 seconds) or the announcer
	if sim.clock_seconds == 0x3d or sim.clock_seconds == 0x3c:
		if not InfoPanel.speech_on(sim):
			sim.play_sfx(0x97)
		elif sim.clock_seconds == 0x3c:
			Speech.say(sim, Speech.one_minute())

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
		Crowd.bench_cheer(sim, scorer_team)
		# the organ celebrates a home goal when the announcer does not
		if scorer_team == 0 and not InfoPanel.speech_on(sim):
			InfoPanel.music(sim, 3)
		# everyone celebrates / skates to the bench
		for i in 6:
			var p := sim.entities[scoring.first_slot + i]
			if p.line_slot > 0 and (p.flags2 & Entity.F2_KNOCKED) == 0:
				p.flags &= ~Entity.F_ARRIVED
				if p.state() == Entity.State.PENALTY_SHOT_WAIT:
					# the team mates waiting at the bench come out to celebrate the penalty shot goal
					p.set_state_reset(Entity.State.BENCH_WAIT)
					p.set_state_reset(Entity.State.CELEBRATE)
					p.set_state_reset(Entity.State.EXIT_BENCH)
				else:
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
		# word_e9ab0: 1 even strength, 2 short handed, 4 power play, | 8 into an empty net
		sim.goal_flags = 2 if scoring.skaters_on_ice < conceding.skaters_on_ice else (4 if conceding.skaters_on_ice < scoring.skaters_on_ice else 1)
		if conceding.goalie_pulled():
			sim.goal_flags |= 8
		if not sim.no_stats:
			goal_statistics(sim, scoring, conceding)
		queue_infraction(sim, sim.entities[conceding.first_slot], INF_GOAL)
		if not sim.no_stats:
			end_penalty_shot(sim)
			sim.penalty_shot_spot = Vector2i.ZERO
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

## setup_faceoff (0x5d852) and end_of_period (0x5dea6): see Ceremonies.period_end / next_period
static func setup_faceoff(sim: Sim) -> void:
	Ceremonies.period_end(sim)

## called by the puck faceoff handler when a period ended: advance to the next one
static func next_period(sim: Sim) -> void:
	Ceremonies.next_period(sim)

## the statistics part of score_goal: the scorer (the last carrier of the scoring team), power
## play / short handed / empty net goals, the two assists, the goalie's goals against and the
## plus/minus of the skaters on the ice (not on a power play goal or a penalty shot)
static func goal_statistics(sim: Sim, scoring: Team, conceding: Team) -> void:
	var scorer: int = scoring.carrier_history[0]
	scoring.add_stat(scorer, Team.ST_GOALS)
	if conceding.skaters_on_ice < scoring.skaters_on_ice:
		scoring.add_stat(scorer, Team.ST_PPG)
	elif scoring.skaters_on_ice < conceding.skaters_on_ice:
		scoring.add_stat(scorer, Team.ST_SHG)
	if conceding.goalie_pulled():
		scoring.add_stat(scorer, Team.ST_ENG)
	if sim.penalty_shot_phase == 0:
		if sim.breakaway:
			scoring.breakaway_goals += 1
	else:
		scoring.penalty_shot_goals += 1
	if sim.one_timer:
		scoring.one_timer_goals += 1
	if scoring.carrier_history[1] >= 0:
		scoring.add_stat(scoring.carrier_history[1], Team.ST_ASSISTS)
		scoring.add_stat(scoring.carrier_history[2], Team.ST_ASSISTS)
	var g := conceding.goalie_index()
	if g >= 0:
		conceding.goalie_stats[g][2] += 1
	if not sim.penalty_shot and scoring.skaters_on_ice <= conceding.skaters_on_ice:
		for i in 6:
			var p := sim.entities[scoring.first_slot + i]
			if p.line_slot > 0:
				scoring.add_stat(p.roster_idx, Team.ST_PLUS_MINUS, 1)
			var q := sim.entities[conceding.first_slot + i]
			if q.line_slot > 0:
				conceding.add_stat(q.roster_idx, Team.ST_PLUS_MINUS, -1)

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
	sim.assign_users()
	sim.faceoff_ready = [1, 4]
	sim.faceoff_side = [0x8800 if not sim.ends_switched else 0x8000, 0xa000 if not sim.ends_switched else 0xa800]
	sim.faceoff_dir = [-1, -1]
	sim.faceoff_timer = 7
	puck.timer_a = sim.random(0x78) + 0xb4

## faceoff_resolve (0x4db2b): the drop; the winner is decided by the centres' readiness and skill
static func faceoff_resolve(sim: Sim) -> void:
	InfoPanel.stop_music(sim)
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

## all_players_arrived (0x51440): every player on the ice stands at his faceoff place (timer_b -100)
static func all_players_arrived(sim: Sim) -> bool:
	for i in 12:
		var p := sim.entities[i]
		if p.line_slot >= 0 and p.timer_b != -100:
			return false
	return true

## all_goto_positions (0x512c1), called when the referee starts to pick up the puck:
##  - a normal stoppage: the goalies go to the faceoff, the skaters to the bench area to wait for
##    the line change (BENCH_WAIT) when line changes are on, else straight to the faceoff;
##  - a penalty shot (phase set): the shooter and the defending goalie line up, everybody else
##    waits at the benches (PENALTY_SHOT_WAIT);
##  - the stoppage after a penalty shot (setup set): the waiting players come back.
## Players in the penalty box keep their state (the port keeps the penalty on the entity).
static func all_goto_positions(sim: Sim) -> void:
	for i in 12:
		var e := sim.entities[i]
		var s := e.state()
		if s == Entity.State.PENALTY_BOX or s == Entity.State.DOOR_OPEN or s == Entity.State.EXIT_PENALTY_BOX:
			continue
		if sim.penalty_shot_phase != 0:
			if e.line_slot > 0:
				e.timer_b = 0
				if i == sim.penalty_shot_slot:
					e.set_state_reset(Entity.State.ALL_GOTO_FACEOFF)
				elif s != Entity.State.INIT_PERIOD and s != Entity.State.GAME_MISCONDUCT:
					e.set_state_reset(Entity.State.PENALTY_SHOT_WAIT)
			if e.line_slot == 0:
				e.timer_b = 0
				if e.team == sim.penalty_shot_team:
					e.set_state_reset(Entity.State.PENALTY_SHOT_WAIT)
				else:
					e.next_line_slot = -1
					e.next_roster = -1
					e.set_state_reset(Entity.State.ALL_GOTO_FACEOFF)
			continue
		if not sim.penalty_shot_setup:
			if e.line_slot == 0:
				e.timer_b = 0
				if s != Entity.State.INIT_PERIOD:
					e.set_state_reset(Entity.State.ALL_GOTO_FACEOFF)
			elif e.line_slot > 0:
				e.timer_b = 0
				if s != Entity.State.INIT_PERIOD and s != Entity.State.GAME_MISCONDUCT:
					e.set_state_reset(Entity.State.BENCH_WAIT if sim.opt_line_changes else Entity.State.ALL_GOTO_FACEOFF)
			continue
		if s == Entity.State.PENALTY_SHOT_WAIT:
			if not sim.opt_line_changes:
				e.set_state_reset(Entity.State.ALL_GOTO_FACEOFF)
				e.set_state_reset(Entity.State.EXIT_BENCH)
		elif e.line_slot < 1:
			if e.line_slot == 0 and s != Entity.State.INIT_PERIOD:
				e.set_state_reset(Entity.State.ALL_GOTO_FACEOFF)
		else:
			e.next_line_slot = -1
			e.next_roster = -1
			e.set_state_reset(Entity.State.BENCH_WAIT)
