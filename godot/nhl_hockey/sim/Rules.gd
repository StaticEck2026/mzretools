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
const INF_NET_OFF := 30           # a skater knocked a net off (net_push_off)

# --------------------------------------------------------------------------------------------
# the infraction queue (infraction_queue, 0xe9a16): 32 entries of two bytes, the event and the
# slot of the player it is about (0x80 once its stoppage started); an event 0 ends the queue
# --------------------------------------------------------------------------------------------

static func inf_type(sim: Sim, i: int) -> int:
	return sim.infq[i * 2] if i >= 0 and i < 32 else 0

static func inf_slot(sim: Sim, i: int) -> int:
	return sim.infq[i * 2 + 1] if i >= 0 and i < 32 else 0

static func inf_set(sim: Sim, i: int, type: int, slot: int) -> void:
	if i >= 0 and i < 32:
		sim.infq[i * 2] = type & 0xff
		sim.infq[i * 2 + 1] = slot & 0xff

## the entries in use (up to the first event 0)
static func inf_count(sim: Sim) -> int:
	var n := 0
	while n < 32 and sim.infq[n * 2] != 0:
		n += 1
	return n

## clear_infractions (0x63d3c)
static func clear_infractions(sim: Sim) -> void:
	sim.infq.fill(0)

static func _is_penalty(type: int) -> int:
	return Entity.to_s8(Tables.infraction_is_penalty[type]) if type >= 0 and type < Tables.infraction_is_penalty.size() else 0

# --------------------------------------------------------------------------------------------
# per step (sim_game_state)
# --------------------------------------------------------------------------------------------

## sim_game_state (0x5c302), the first part of every step: the stoppage machinery, the crowd, the
## end of the period at 0:00; then every 24 steps (not while a penalty is handed out) the CPU's
## goalie pulls, the crowd, the bench energy, the power play and the energy bar of a team that
## is changing lines on the fly
static func sim_game_state(sim: Sim) -> void:
	update_stoppage(sim)
	update_effects(sim)
	if not sim.play_stopped and sim.clock_seconds == 0 and sim.clock_sub == 0:
		sim.play_sfx(0x90)
		hold_camera(sim)
		setup_faceoff(sim)
	if sim.penalty_box_mode:
		return
	sim.tick24 = Entity.to_s8(sim.tick24 - 1)
	if sim.tick24 >= 0:
		return
	sim.tick24 += 0x18
	sim.tick_toggle ^= 1
	Lines.cpu_line_change(sim)
	update_crowd_random(sim)
	Lines.regenerate_energy(sim)
	if not sim.play_stopped:
		update_power_play(sim)
	if not sim.opt_line_changes:
		return
	for t in 2:
		var team := sim.teams[t]
		for i in 6:
			var e := sim.entities[team.first_slot + i]
			if e.line_slot >= 0 and e.next_roster >= 0 and sim.penalty_shot_phase == 0 and (sim.tick_toggle & 1):
				sim.lc_bar[t] = 1
				return
		sim.lc_bar[t] = 0

## hold_camera (0x5cd25): the camera stays where it is
static func hold_camera(sim: Sim) -> void:
	sim.camera_target_x = sim.camera_x
	sim.camera_target_y = sim.camera_y
	sim.action_hold_camera = true

## update_stoppage (0x63bf8): the once a second timers, the infraction queue; during a stoppage the
## scoreboard, the announcement timer (then the whistle may blow again: stop_flags 4) and, once
## the stoppage runs (game_flags 4), its timers or, after them, the penalties handed out
static func update_stoppage(sim: Sim) -> void:
	update_line_timers(sim)
	process_infractions(sim)
	if not sim.play_stopped:
		return
	InfoPanel.update(sim)
	if sim.announce_timer >= 0:
		sim.announce_timer = Entity.to_s16(sim.announce_timer - 1)
		if sim.announce_timer < 0:
			sim.whistle_ready = true
	if not sim.stoppage_countdown:
		return
	if sim.stoppage_timer >= 0:
		stoppage_tick(sim)
	else:
		penalty_box_update(sim)

## update_line_timers (0x63b85): once a second of play (word c90d0, misc_flags 0x40 for that
## step) the zone and power play times and the penalties of both teams
static func update_line_timers(sim: Sim) -> void:
	sim.second_tick = false
	if sim.play_stopped or sim.penalty_shot:
		return
	sim.second_timer = Entity.to_s16(sim.second_timer - 1)
	if sim.second_timer >= 0:
		return
	sim.second_tick = true
	sim.second_timer += 0x18
	zone_time_stats(sim)
	lead_time_stats(sim)
	penalty_timers(sim, sim.teams[0])
	penalty_timers(sim, sim.teams[1])

## stoppage_tick (0x63475): the whistle and the stoppage timers; when the stoppage is over and a
## penalty is among the calls the penalty box sequence starts: no new calls, the puck lies dead
## (PUCK_IDLE) until the referee collected it
static func stoppage_tick(sim: Sim) -> void:
	sim.whistle_timer = Entity.to_s16(sim.whistle_timer - 1)
	if sim.whistle_timer < 0:
		sim.whistle_timer = 0
	sim.stoppage_timer = Entity.to_s16(sim.stoppage_timer - 1)
	if sim.stoppage_timer >= 0:
		return
	sim.delayed_call = false
	sim.whistle_timer = 0
	var i := 0
	while inf_type(sim, i) != 0:
		var type := inf_type(sim, i)
		i += 1
		if _is_penalty(type) == 0:
			continue
		sim.whistle_ready = true
		sim.announce_timer = -1
		sim.penalty_box_mode = true
		sim.puck_carrier = -1
		sim.puck.set_state_reset(Entity.State.PUCK_IDLE)
		sim.faceoff_timer = 0x1c20
		sim.ref_phase = (sim.ref_phase & 0xff) - 0x100
		sim.whistle_timer = 0
		if sim.message_timer == 0:
			sim.message = -1
		return

## process_infractions (0x637b5): every queued event that has not stopped the play yet does it
## (start_stoppage); a penalty on the team without the puck is delayed (the referee's arm goes up,
## game_flags 8) until that team touches it. Each event then sets the stoppage and announcement
## timers once (slot | 0x80).
static func process_infractions(sim: Sim) -> void:
	if sim.action_replay or sim.penalty_box_mode:
		return
	var i := 0
	while inf_type(sim, i) != 0:
		var type := inf_type(sim, i)
		var slot := Entity.to_s8(inf_slot(sim, i))
		if not sim.stoppage_countdown:
			if _is_penalty(type) != 0:
				var c := Entity.to_s8(sim.puck_carrier)
				if c >= 0 and (c < 6) == (slot < 6):
					sim.whistle_timer = 0x28
					if sim.message != -1:
						sim.message_timer = 0x50
					start_stoppage(sim, i)
				else:
					if not sim.delayed_call:
						sim.delayed_call = true
						ref_announce(sim, INF_DELAYED_CALL)
					i += 1
					continue
			else:
				start_stoppage(sim, i)
		var s := inf_slot(sim, i)
		if (s & 0x80) == 0:
			inf_set(sim, i, inf_type(sim, i), s | 0x80)
			var dur := Entity.to_s16(Entity.to_s8(Tables.stoppage_duration[type]) << 5)
			if dur > sim.stoppage_timer:
				sim.stoppage_timer = dur
			if sim.injury_stoppage:
				sim.stoppage_timer = 0x140
			var delay: int
			if sim.penalty_shot_setup and type == INF_PENALTY_SHOT_END:
				delay = Entity.to_s16(Entity.to_s8(Tables.announce_delay[4]) << 5)
				sim.stoppage_timer = Entity.to_s16(Entity.to_s8(Tables.stoppage_duration[13]) << 5)
			else:
				delay = Entity.to_s16(Entity.to_s8(Tables.announce_delay[type]) << 5)
			if delay > sim.announce_timer:
				sim.announce_timer = delay
		i += 1

## start_stoppage (0x63543): the whistle for queued event `idx`; the faceoff spot follows from it:
## centre ice after a goal, the last touch for a frozen puck and a two line pass, else where the
## puck is (an offside outside the blue line moves to the line, an icing to the far end), then
## pulled to a dot (the end zone dots at +-0x60 / +-0xb8; a call on a team in its own end moves the
## faceoff out to the neutral zone dots)
static func start_stoppage(sim: Sim, idx: int) -> void:
	if sim.stubbed("start_stoppage", [idx]):
		return
	var type := inf_type(sim, idx)
	var culprit := Entity.to_s8(inf_slot(sim, idx))
	if not sim.play_stopped:
		sim.play_stopped = true
		sim.faceoff_x = 0
		sim.faceoff_y = 0
		if type != INF_GOAL:
			sim.faceoff_x = sim.last_touch_x
			sim.faceoff_y = sim.last_touch_y
			if type != INF_FROZEN and type != INF_TWO_LINE:
				sim.faceoff_x = Entity.to_s16(sim.puck.xi)
				sim.faceoff_y = Entity.to_s16(sim.puck.yi)
				if type == INF_OFFSIDE:
					if absi(sim.faceoff_y) < 0x4e:
						sim.faceoff_y = -0x4e if sim.faceoff_y < 0 else 0x4e
				elif type == INF_ICING:
					var c := sim.entities[culprit] if culprit >= 0 and culprit < 17 else null
					sim.faceoff_y = -0x258 if (c != null and (c.flags & Entity.F_ATTACK_UP)) else 0x258
		if sim.penalty_shot_setup:
			sim.faceoff_x = sim.penalty_shot_spot.x
			sim.faceoff_y = sim.penalty_shot_spot.y
		if sim.faceoff_x >= 0x60:
			sim.faceoff_x = 0x60
		elif sim.faceoff_x <= -0x60:
			sim.faceoff_x = -0x60
		if sim.faceoff_y >= 0x90:
			sim.faceoff_x = -0x60 if sim.faceoff_x < 0 else 0x60
			sim.faceoff_y = 0xb8
		elif sim.faceoff_y <= -0x90:
			sim.faceoff_x = -0x60 if sim.faceoff_x < 0 else 0x60
			sim.faceoff_y = -0xb8
		var k := 0
		while true:
			var s := Entity.to_s8(inf_slot(sim, k) & 0x7f)
			var c := sim.entities[s] if s >= 0 and s < 17 else null
			if c == null or (c.flags & Entity.F_ATTACK_UP) == 0:
				if sim.faceoff_y <= -0x4e:
					sim.faceoff_y = -0x3d
					sim.faceoff_x = -100 if sim.faceoff_x < 0 else 100
			elif sim.faceoff_y >= 0x4e:
				sim.faceoff_y = 0x3d
				sim.faceoff_x = -100 if sim.faceoff_x < 0 else 100
			k += 1
			if inf_type(sim, k) == 0:
				break
	sim.stoppage_timer = 0
	sim.stoppage_countdown = true
	sim.play_sfx(0xa4)
	ref_announce(sim, INF_PENALTY_SHOT_END)

## ref_announce (0x62ea2): the referee signals the call (ai_ref_call_penalty) or points at the
## goal (ai_ref_point_goal); the end of a penalty shot (5) and the delayed call (0x1c) are silent
static func ref_announce(sim: Sim, type: int) -> void:
	if type == INF_PENALTY_SHOT_END or type == INF_DELAYED_CALL:
		return
	sim.ref_infraction = type
	sim.ref_phase = 0
	sim.referee.set_state(Entity.State.REF_POINT_GOAL if type == INF_GOAL else Entity.State.REF_CALL_PENALTY)

## penalty_box_update (0x62ee9), once the stoppage is over and the referee is free (ref_phase not
## 0, the announcer quiet): the last queued call is handled. A penalty sends the player to the box:
## the team's penalties and minutes, his penalty minutes, the scoreboard entry, record_penalty;
## his entity_of word becomes the penalty time in seconds with the flags 0x2000 (just called), 0x4000
## (a major) and 0x1000 (kept from an earlier penalty: coincidental), his status 5, and he joins
## the box queue (team +0xb6). An injured culprit's penalty is served by a skater on the ice. A
## game misconduct throws him out (status 8, GAME_MISCONDUCT, entity_of -5), a penalty shot is
## called (begin_penalty_shot). A call not handed out yet waits until its player left the ice.
## With the queue empty: the players in the box (not coincidental ones) take skaters off the ice
## (at least 4 stay), the stoppage ends and the puck goes to the faceoff.
static func penalty_box_update(sim: Sim) -> void:
	if sim.ref_phase == 0 or sim.speech_busy:
		return
	while true:
		if inf_type(sim, 0) == 0:
			if sim.clip != 0 and sim.clip != 2 and sim.panel >= 0:
				return
			for t in 2:
				var team := sim.teams[t]
				var n := 6
				for r in range(0x1b, -1, -1):
					var w := team.entity_of[r]
					if w <= 0:
						continue
					w &= ~0x2000
					team.entity_of[r] = w
					if (w & 0x1000) == 0 and n > 4:
						n -= 1
				team.skaters_on_ice = n
			sim.stoppage_countdown = false
			var ps := sim.puck.state()
			if ps == Entity.State.PUCK_FACEOFF or ps == Entity.State.PUCK_FACEOFF2:
				return
			sim.puck.set_state(Entity.State.PUCK_FACEOFF)
			return
		var i := inf_count(sim) - 1
		var s := inf_slot(sim, i)
		if (s & 0x80) == 0:
			var e0 := sim.entities[Entity.to_s8(s)]
			if e0.line_slot >= 0:
				return
			inf_set(sim, i, 0, 0)
			return
		inf_set(sim, i, inf_type(sim, i), s & 0x7f)
		var type := inf_type(sim, i)
		var slot := s & 0x7f
		var e := sim.entities[slot]
		var mm_ss := _elapsed(sim)
		if type == INF_PENALTY_SHOT:
			begin_penalty_shot(sim)
			inf_set(sim, i, 0, 0)
			record_penalty(sim, 1 if e.flags & Entity.F_PLAYER2 else 0, Entity.to_s8(e.roster_idx), type - 9, 0, mm_ss.x, mm_ss.y, 0)
			ref_announce(sim, type)
			return
		var minutes := _is_penalty(type)
		if minutes < 0:
			var team := sim.team_of(e)
			var r := Entity.to_s8(e.roster_idx)
			team.roster_status[r] = 8
			if Lines.entity_word(team, r) > -3:
				e.set_state(Entity.State.GAME_MISCONDUCT)
			team.entity_of[r] = -5
			record_penalty(sim, 1 if e.flags & Entity.F_PLAYER2 else 0, r, type - 9, minutes, mm_ss.x, mm_ss.y, i)
			sim.ref_infraction_slot = Entity.to_s8(inf_slot(sim, i))
			inf_set(sim, i, 0, 0)
			ref_announce(sim, type)
			return
		if minutes == 0:
			sim.ref_infraction_slot = slot
			inf_set(sim, i, 0, 0)
			if not sim.action_replay and not sim.penalty_box_mode:
				ref_announce(sim, type)
				return
			if type != INF_GOAL:
				continue
			ref_announce(sim, type)
			return
		# a penalty
		var team := sim.team_of(e)
		team.penalty_count += 1
		team.penalty_minutes += minutes
		var r := Entity.to_s8(e.roster_idx)
		if r < 0x19:
			team.add_stat(r, Team.ST_PIM, minutes)
		add_penalty_display(sim, 1 if e.flags & Entity.F_PLAYER2 else 0, e.number, minutes)
		record_penalty(sim, 1 if e.flags & Entity.F_PLAYER2 else 0, r, type - 9, minutes, mm_ss.x, mm_ss.y, i)
		var w := minutes * 0x3c
		if w == 0x12c:
			w |= 0x4000
		w |= 0x2000
		var server := e
		var st := Lines.entity_word(team, r)
		if st == -3 or st == -4:
			# the culprit is hurt or out: a skater on the ice serves the penalty
			server = null
			for k in 6:
				var p := sim.entities[team.first_slot + k]
				if p.line_slot > 0 and Lines.entity_word(team, Entity.to_s8(p.roster_idx)) == -1 \
						and (p.flags2 & Entity.F2_PENALIZED) == 0:
					server = p
					break
			if server == null:
				return
			r = Entity.to_s8(server.roster_idx)
			inf_set(sim, i, inf_type(sim, i), (inf_slot(sim, i) & 0x80) | server.slot)
			sim.panel_text[4] = "served by #%d" % server.number
		if team.entity_of[r] >= 0 and (team.entity_of[r] & 0x1000):
			w |= 0x1000
		team.entity_of[r] = w
		team.roster_status[r] = 5
		var q := 0
		while q < 0x1c and team.box_queue[q] >= 0:
			q += 1
		if q < 0x1c:
			team.box_queue[q] = r
			if q + 1 < 0x1c:
				team.box_queue[q + 1] = -1
		server.set_state(Entity.State.PENALTY_BOX)
		sim.ref_infraction_slot = server.slot
		ref_announce(sim, type)
		return

## the time of the period played (period_length - clock_seconds, a started second counting in the
## last minute), as minutes and seconds
static func _elapsed(sim: Sim) -> Vector2i:
	var t := Entity.to_s16(sim.period_length - sim.clock_seconds)
	if sim.clock_seconds < 0x3c and sim.clock_sub != 0:
		t -= 1
	return Vector2i(t / 0x3c, t % 0x3c)

## record_penalty (0x624b9): the call in the event log, the game summary, the scoreboard panel
## (with a clip now and then) and the announcer (InfoPanel); a hook for the golden tests
static func record_penalty(sim: Sim, away: int, roster: int, kind: int, minutes: int, mm: int, ss: int, queue_index: int) -> void:
	if sim.stubbed("record_penalty", [away, roster, kind, minutes, mm, ss, queue_index]):
		return
	InfoPanel.record_penalty(sim, away, roster, kind + 9, minutes, queue_index)

## add_penalty_display (0x14c22): the penalty clock entry on the scoreboard (a hook)
static func add_penalty_display(sim: Sim, away: int, number: int, minutes: int) -> void:
	sim.stubbed("add_penalty_display", [away, number, minutes])

## penalty_list_find (0x14ca0): the penalty clock entry of a player released by a goal (a hook)
static func penalty_list_find(sim: Sim, away: int, number: int) -> void:
	sim.stubbed("penalty_list_find", [away, number])

## count_penalized (0x5df86): the players sitting in each box (penalized_count; not a coincidental
## one whose time is up); everybody else not out of the game is back on the bench (status 3)
static func count_penalized(sim: Sim) -> void:
	for t in 2:
		var team := sim.teams[t]
		var n := 0
		for r in range(0x1b, -1, -1):
			var w := team.entity_of[r]
			if w > 0:
				if (w & 0x1000) == 0 or (w & 0x7ff) != 0:
					n += 1
			elif w > -3:
				team.entity_of[r] = -2
				team.roster_status[r] = 3
		sim.box_count[t] = n & 0xff

## penalty_timers (0x63a37), once a second for a team: the first two penalties of the box queue
## run; one whose time is up (flags aside) is taken out of the queue (status 7, no longer a major).
## Then penalty_expired for the players whose penalties ran (the original looks at the first one
## with one penalty, the first two with two, the second with three, none with more).
static func penalty_timers(sim: Sim, team: Team) -> void:
	var running := 2
	var ran := [-1, -1]
	var n := 0
	var b := 0
	while b < 0x1c:
		var r := team.box_queue[b]
		if r < 0:
			break
		running -= 1
		if running >= 0:
			if n < 2:
				ran[n] = r
			n += 1
			var w := Entity.to_s16(team.entity_of[r] - 1)
			team.entity_of[r] = w
			if (w & 0x3fff) == 0:
				team.roster_status[r] = 7
				team.entity_of[r] = w & ~0x4000
				var k := b
				while k + 1 < 0x1c:
					team.box_queue[k] = team.box_queue[k + 1]
					if team.box_queue[k] < 0:
						break
					k += 1
				b -= 1
		b += 1
	if running == 1:
		penalty_expired(sim, team, ran[0])
	elif running == 0:
		penalty_expired(sim, team, ran[0])
		penalty_expired(sim, team, ran[1])
	elif running == -1:
		penalty_expired(sim, team, ran[1])

## penalty_expired (0x639f9): in the last 5 seconds of a penalty the buzzer counts down; at 0 the
## player comes out (release_from_box)
static func penalty_expired(sim: Sim, team: Team, r: int) -> void:
	var w := Lines.entity_word(team, r)
	if (w & 0x3fff) > 5:
		return
	if w == 0:
		release_from_box(sim, team, r)
	sim.play_sfx(0x97)

## release_from_box (0x6392a): the first entity of the team without a position takes the player
## (put_player_on_ice: out of the box door, EXIT_PENALTY_BOX) at the position the lineup gives a
## team with one more skater; both teams look at their lines again
static func release_from_box(sim: Sim, team: Team, r: int) -> void:
	var e: Entity = null
	for i in range(team.first_slot, 17):
		if sim.entities[i].line_slot < 0:
			e = sim.entities[i]
			break
	team.skaters_on_ice += 1
	sim.teams[0].flags |= 1
	sim.teams[1].flags |= 1
	sim.teams[0].flags2 |= 0x40
	sim.teams[1].flags2 |= 0x40
	if e == null:
		return
	var k := team.skaters_on_ice + (1 if Entity.to_s16(team.goalie_request) < 0 else 0)
	e.line_slot = LINEUP_SLOT_RAW[k] if k >= 0 and k < LINEUP_SLOT_RAW.size() else -1
	AI.set_default_state(sim, e)
	sim.put_player_on_ice(e, r)
	e.flags2 |= Entity.F2_UNSELECTABLE

# unk_cbc36: the byte before lineup_slot_types, then the slot types of mode 0 and the last of mode 1
const LINEUP_SLOT_RAW := [-1, 0, 1, 2, 4, 3, 5, 6]

## goal_ends_penalty (0x63d69), team `t` scored: the goal wipes the queued calls but the
## misconducts, the majors and the minors of the scoring team (all of them when the overtime goal
## ended the game; the original loses a kept call when one follows it in the queue); then a power
## play goal frees the first player of the box queue not serving a major (the scoring team's power
## play goals, both teams look at their lines again)
static func goal_ends_penalty(sim: Sim, t: int) -> void:
	var scoring := sim.teams[t]
	var conceding := sim.teams[1 - t]
	var w := 0
	var i := 0
	while inf_type(sim, i) != 0:
		var type := inf_type(sim, i)
		var keep := false
		if not (sim.period == 3 and sim.teams[0].goals != sim.teams[1].goals):
			var p := _is_penalty(type)
			if p == -1 or p == 5:
				keep = true
			elif p == 2 and ((Entity.to_s8(inf_slot(sim, i)) < 6) != (t != 0)):
				keep = true
		if keep:
			if w != i:
				inf_set(sim, w, type, inf_slot(sim, i))
				w += 1
		else:
			var s := Entity.to_s8(inf_slot(sim, i))
			if s >= 0 and s < 12:
				sim.entities[s].flags2 &= ~Entity.F2_PENALIZED
			inf_set(sim, i, 0, 0)
		i += 1
	if inf_type(sim, 0) == 0 and sim.message == 6:
		sim.message = -1
	if scoring.skaters_on_ice <= conceding.skaters_on_ice:
		return
	var b := 0
	var r := -1
	while b < 0x1c:
		r = conceding.box_queue[b]
		if r < 0:
			return
		if (conceding.entity_of[r] & 0x4000) == 0:
			break
		b += 1
	conceding.entity_of[r] = 0
	conceding.roster_status[r] = 7
	release_from_box(sim, conceding, r)
	var p: Database.Player = conceding.info.player(r) if conceding.info != null else null
	penalty_list_find(sim, 1 if t == 0 else 0, p.number if p != null else 0)
	var k := b
	while k + 1 < 0x1c:
		conceding.box_queue[k] = conceding.box_queue[k + 1]
		if conceding.box_queue[k] < 0:
			break
		k += 1
	scoring.pp_goals += 1
	sim.teams[0].flags |= 1
	sim.teams[1].flags |= 1

## update_power_play (0x63c73): the skaters on the ice differ: a power play (stop_flags 0x20, 0x40
## for the away team's) starts once, counting for the team; at even strength it ends
static func update_power_play(sim: Sim) -> void:
	var d := Entity.to_s16(sim.teams[0].skaters_on_ice - sim.teams[1].skaters_on_ice)
	if d == 0:
		sim.power_play = false
		return
	var team := sim.teams[1]
	if d > 0:
		team = sim.teams[0]
		if sim.power_play_team == 1:
			sim.power_play = false
			sim.power_play_team = 0
	elif sim.power_play_team != 1:
		sim.power_play = false
		sim.power_play_team = 1
	if sim.power_play:
		return
	sim.power_play = true
	team.power_plays += 1
	if sim.play_stopped and not InfoPanel.speech_on(sim):
		InfoPanel.music(sim, 1 if team.index == 0 else 4)

## penalty_time_left (0x54a53): the original's sum over the penalties of the short handed team
## (seconds left, the flags masked), less the first penalty of the other team when it has one
static func penalty_time_left(sim: Sim) -> int:
	var d := Entity.to_s16(sim.teams[0].skaters_on_ice - sim.teams[1].skaters_on_ice)
	if d == 0:
		return 0
	var more := sim.teams[0] if d > 0 else sim.teams[1]
	var short := sim.teams[1] if d > 0 else sim.teams[0]
	var prev := 0
	var total := 0
	for b in 0x1c:
		var r := short.box_queue[b]
		if r < 0:
			break
		var w := Entity.to_s16(short.entity_of[r])
		if w < 0:
			continue
		var s := w & 0x3fff
		var a := s - prev
		total += a
		prev = a
	if more.skaters_on_ice == 6:
		return total
	total -= prev
	for b in 0x1c:
		var r := more.box_queue[b]
		if r < 0:
			return total
		var w := Entity.to_s16(more.entity_of[r])
		if w < 0:
			continue
		if Entity.to_s16(total) < (w & 0x3fff):
			return total
		return total + prev
	return total

## zone_time_stats (0x639a4): a second with the puck beyond a blue line counts for the team
## attacking that end (the ends switch with game_flags 2)
static func zone_time_stats(sim: Sim) -> void:
	if sim.no_stats:
		return
	var y := Entity.to_s16(sim.puck.yi)
	var t: int
	if y > 0x4e:
		t = 0
	elif y < -0x4e:
		t = 1
	else:
		return
	if sim.ends_switched:
		t ^= 1
	sim.teams[1 if t > 0 else 0].zone_time += 1

## lead_time_stats (0x63b57): a second of the power play for the team with more skaters
static func lead_time_stats(sim: Sim) -> void:
	if sim.power_play:
		sim.teams[sim.power_play_team].pp_time += 1

## queue_infraction (0x62d80): a rule event is queued (not while a penalty is handed out or in a
## replay): the message box shows the most important call (infraction_priority; the PENALTY
## message stays until the penalty is handed out), the crowd and a sound for the hits; a player
## already called for a penalty is not called again
static func queue_infraction(sim: Sim, e: Entity, type: int) -> void:
	if sim.stubbed("queue_infraction", [e.slot, type]):
		return
	if sim.action_replay or sim.penalty_box_mode:
		return
	if not sim.penalty_shot_setup:
		var prio := Entity.to_s16(Tables.infraction_priority[type])
		if sim.message < prio:
			sim.message = prio
			if sim.message != -1 and sim.message != 6:
				sim.message_timer = 0x50
	if type >= 7:
		sim.add_crowd(0x190, 0x320)
		if e.flags & Entity.F_PLAYER2:
			sim.excitement += 0x14
			sim.play_sfx(0x7d)
		else:
			sim.play_sfx(0xa0)
	for i in 32:
		if inf_type(sim, i) != 0:
			continue
		inf_set(sim, i, type, e.slot)
		if _is_penalty(type) == 0:
			return
		if e.flags2 & Entity.F2_PENALIZED:
			inf_set(sim, i, 0, 0)
			return
		e.flags2 |= Entity.F2_PENALIZED
		return

## maybe_queue_infraction (0x62cf9): rule events filtered by the options: icing always, offside
## and the two line pass when on, penalties when on for a team with fewer than 8 in the box and a
## player who may be lost (injury_check); never during a stoppage, for the referee or a penalty shot
static func maybe_queue_infraction(sim: Sim, e: Entity, type: int) -> void:
	if sim.stubbed("maybe_queue_infraction", [e.slot, type]):
		return
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
			if Entity.to_s8(sim.box_count[1 if e.flags & Entity.F_PLAYER2 else 0]) >= 8:
				return
			if not injury_check(sim, e):
				return
	queue_infraction(sim, e, type)

## update_crowd_random (0x5c248), every 24 steps: the excitement's peak and running sum, its
## decay; during a loud stoppage a cheer (0xa6) or a whistle (0x96) now and then
static func update_crowd_random(sim: Sim) -> void:
	if sim.excitement > sim.excitement_peak:
		sim.excitement_peak = sim.excitement
	sim.excitement_sum += sim.excitement
	sim.excitement_samples = (sim.excitement_samples + 1) & 0xffff
	sim.excitement = Entity.to_s16(sim.excitement - 1)
	if sim.excitement < 0:
		sim.excitement = 0
	if not sim.play_stopped or sim.crowd_noise <= 0x258:
		return
	var n := (1000 - sim.crowd_noise) / 4
	if n < 0x19:
		n = 0x19
	var r := Entity.to_s16(sim.random(n))
	if r == 0:
		sim.play_sfx(0xa6)
	elif r == 1:
		sim.play_sfx(0x96)

## injury_check (0x65b83): may the player be lost (a penalty, an injury)? A defenceman (in his
## team's defence list, Team.PL_D_DEF) while more than 2 of the defencemen, anyone else while more
## than 4 of the skaters (PL_SKATERS) are on the bench or on the ice (roster status 3 or 4)
static func injury_check(sim: Sim, e: Entity) -> bool:
	if sim.stubbed("injury_check", [e.slot]):
		return true
	var t := 1 if e.flags & Entity.F_PLAYER2 else 0
	var team := sim.teams[t]
	var found := false
	var count := 0
	var list: PackedInt32Array = team.pos_lists[Team.PL_D_DEF]
	for i in 0x19:
		var r := list[i]
		if r < 0:
			break
		if r == Entity.to_s8(e.roster_idx):
			found = true
		var st := team.roster_status[r]
		if st == 4 or st == 3:
			count += 1
	if found:
		return count > 2
	count = 0
	list = team.pos_lists[Team.PL_SKATERS]
	for i in 0x19:
		var r := list[i]
		if r < 0:
			break
		var st := team.roster_status[r]
		if st == 4 or st == 3:
			count += 1
	return count > 4

# --------------------------------------------------------------------------------------------
# penalty shot (breakaway_foul 0x6427f, begin_penalty_shot 0x64398, start_penalty_shot 0x63f72, end_penalty_shot 0x64439)
# --------------------------------------------------------------------------------------------

## breakaway_foul (0x6427f): is a foul on `victim` a foul on a breakaway? He carries the puck towards the net
## (moving and facing that way), nobody is between him and the net, he is not deeper than the
## goal line area and the goalie is in.
static func breakaway_foul(sim: Sim, victim: Entity) -> bool:
	if sim.no_stats or not sim.opt_penalties or sim.puck_carrier != victim.slot or not sim.breakaway:
		return false
	var h := Entity.to_s16(victim.heading >> 16)
	if victim.flags & Entity.F_ATTACK_UP:
		if victim.vy < 0 or (h >= 2 and h <= 6):
			return false
	elif victim.vy > 0 or h <= 2 or h >= 6:
		return false
	count_defenders_ahead(sim)
	sim.breakaway = sim.defenders_ahead != 0
	if not sim.breakaway:
		return false
	return absi(victim.yi) <= 0xe4 and Entity.to_s16(sim.opponents_of(victim).goalie_request) >= 0

## the fouls on a breakaway (resolve_body_check, resolve_dive_hit, resolve_hook_hold): the fouled
## player will take the shot; the culprit gets infraction 0x1a. False when a shot is already set.
static func award_penalty_shot(sim: Sim, victim: Entity, culprit: Entity) -> bool:
	if sim.penalty_shot_slot >= 0:
		return false
	sim.penalty_shot_slot = victim.slot
	sim.penalty_shot_user = 1 if victim.slot == sim.user1_slot else -1
	maybe_queue_infraction(sim, culprit, INF_PENALTY_SHOT)
	return true

## begin_penalty_shot (0x64398, from penalty_box_update for infraction 0x1a): the shot is called.
## Both teams are down to one player in the count of skaters, the faceoff spot of the stoppage is
## kept for afterwards and the puck goes to centre ice.
static func begin_penalty_shot(sim: Sim) -> void:
	if sim.penalty_shot_phase != 0:
		return
	sim.penalty_shot_team = 1 if sim.penalty_shot_slot > 5 else 0
	sim.teams[sim.penalty_shot_team].penalty_shots += 1
	sim.teams[0].skaters_on_ice = 1
	sim.teams[1].skaters_on_ice = 1
	# with no shooter set (-1) the original reads the byte before the records (the away team's
	# box queue entry 25)
	var ps := sim.penalty_shot_slot
	sim.penalty_shot_roster = Entity.to_s8(sim.entities[ps].roster_idx) if ps >= 0 and ps < 17 else sim.teams[1].box_queue[25]
	sim.penalty_shot_phase = 1
	sim.penalty_shot_spot = Vector2i(sim.faceoff_x, sim.faceoff_y)
	sim.faceoff_x = 0
	sim.faceoff_y = 0

## start_penalty_shot (0x63f72), from ai_puck_faceoff2 once the shooter and the goalie are set:
## the puck lies at centre ice, the shooter has it and plays the breakaway state; a user of the
## defending team controls nobody (his goalie plays by himself)
static func start_penalty_shot(sim: Sim) -> void:
	var puck := sim.puck
	puck.vz = 0
	puck.vy = 0
	puck.vx = 0
	puck.z &= 0xffff
	puck.y &= 0xffff
	puck.x &= 0xffff
	puck.set_state(Entity.State.PUCK_NORMAL)
	var shooter := sim.entities[sim.penalty_shot_slot]
	shooter.flags2 &= 0xdb
	shooter.flags &= ~Entity.F_ARRIVED
	for i in 8:
		shooter.set_state_reset(Entity.State.BREAKAWAY)
	var defending := (1 if sim.penalty_shot_team == 0 else 0) + 1
	if sim.user1_team == defending and sim.user1_slot != -1:
		sim.user1_slot = sim.find_switch_target(-1, sim.user1_slot)
	if sim.user2_team == defending and sim.user2_slot != -1:
		sim.user2_slot = sim.find_switch_target(-1, sim.user2_slot)
	sim.team_of(shooter).carrier_history = PackedInt32Array([-1, -1, -1])
	sim.crowd_noise = Entity.to_s16(sim.crowd_noise + 0x64)
	sim.puck_carrier = Entity.to_s8(sim.penalty_shot_slot)
	sim.penalty_shot = true
	sim.penalty_shot_setup = true
	sim.penalty_shot_clock = 1000
	clear_infractions(sim)

## end_penalty_shot (0x64439): goal, save, miss, timeout: back to the faceoff spot of the foul
static func end_penalty_shot(sim: Sim) -> void:
	if not sim.penalty_shot or sim.penalty_shot_phase == 0:
		return
	sim.penalty_shot_phase = 0
	sim.penalty_shot = false
	sim.penalty_shot_slot = -1
	queue_infraction(sim, sim.puck, INF_PENALTY_SHOT_END)
	sim.last_touch_x = Entity.to_s16(sim.penalty_shot_spot.x)
	sim.last_touch_y = Entity.to_s16(sim.penalty_shot_spot.y)
	sim.referee.set_state(Entity.State.REF_PICKUP)

## update_effects (0x615a3): crowd noise decays towards the ambient level
static func update_effects(sim: Sim) -> void:
	if sim.stubbed("update_effects", []):
		return
	if sim.crowd_noise >= 0x2bd:
		sim.crowd_noise -= 2
	elif sim.crowd_noise > 0x15e:
		sim.crowd_noise -= 3
	sim.crowd_noise -= 1
	if sim.crowd_noise < 0:
		sim.crowd_noise = 0
		if sim.random(0x10) == 0:
			sim.crowd_noise = sim.random(0x20)
	Crowd.update(sim)


## game_clock_tick (0x5dc10), every step of play: 24 sub ticks per second; at 61 and 60 seconds
## left the tone (or with the announcer on, his last minute line); the CPU coaches' reviews at
## the full minutes of the 2nd and 3rd period (time_announcements). During a penalty shot the
## clock stands and the shot must be over within 1000 steps.
static func game_clock_tick(sim: Sim) -> void:
	if sim.penalty_shot:
		sim.penalty_shot_clock -= 1
		if sim.penalty_shot_clock <= 0:
			end_penalty_shot(sim)
		return
	if sim.clock_seconds == 0 and sim.clock_sub == 0:
		return
	sim.clock_sub = Entity.to_s16(sim.clock_sub - 1)
	if sim.clock_sub >= 0:
		return
	if sim.clock_seconds > 0:
		sim.clock_seconds -= 1
		sim.clock_sub += 0x18
	else:
		sim.clock_sub = 0
	if sim.clock_seconds == 0x3d or sim.clock_seconds == 0x3c:
		if not InfoPanel.speech_on(sim):
			sim.play_sfx(0x97)
		elif sim.clock_seconds == 0x3c:
			announce_one_minute_left(sim)
	if sim.clock_seconds % 0x3c != 0:
		return
	var pn := sim.period + 1
	var c := sim.clock_seconds
	if (pn == 3 and (c == 0x3c or c == 0x78 or c == 0xb4 or c == 0x12c or c == 0x258)) or (pn == 2 and c == 0x258):
		Lines.time_announcements(sim)

## announce_one_minute_left (0x6280a): the announcer's last minute line (a hook)
static func announce_one_minute_left(sim: Sim) -> void:
	if sim.stubbed("announce_one_minute_left", []):
		return
	Speech.say(sim, Speech.one_minute())

# --------------------------------------------------------------------------------------------
# goals (score_goal 0x5ab36) and the end of a period (setup_faceoff 0x5d852)
# --------------------------------------------------------------------------------------------

## score_goal (0x5ab36, from collide_net): the puck crossed the goal line of `net`. The team the
## puck went in for ((puck y < 0) xor the ends switched) scores, unless play is already stopped,
## a delayed penalty cancels it (goal_disallowed_check) or the team is offside: then the puck
## drops in front of the net, the whistle goes (0x1b, and 8 for the offside). During a penalty
## shot only the shooting team's goal counts (the other ends the shot). A goal: the statistics
## (unless no_stats), the score, the scorers celebrate (the penalty shot shooter's team mates come
## off the bench), the puck rests in the net, the infraction 7, the CPU coaches' review of their
## tactics and goalies.
static func score_goal(sim: Sim, net: Entity) -> void:
	sim.scored_net = net.slot
	var puck := sim.puck
	var scorer := (1 if puck.yi < 0 else 0) ^ (1 if sim.ends_switched else 0)
	var scoring := sim.teams[scorer]
	var conceding := sim.teams[1 - scorer]
	if sim.play_stopped or goal_disallowed_check(sim) or (scoring.flags & Team.FL_OFFSIDE):
		sim.puck_in_net = false
		puck.vx = 0
		puck.x = ((net.xi + (-6 if puck.xi < net.xi else 6)) << 16) | (puck.x & 0xffff)
		puck.vy = 0
		puck.y = ((net.yi + (-4 if net.yi < 0 else 4)) << 16) | (puck.y & 0xffff)
		puck.vz = 0x600
		puck.z = puck.z & 0xffff
		_no_prediction(sim)
		puck.flags |= 4
		if not sim.play_stopped:
			puck.set_state(Entity.State.PUCK_IDLE)
			if scoring.flags & Team.FL_OFFSIDE:
				maybe_queue_infraction(sim, sim.entities[scoring.first_slot], INF_OFFSIDE)
			queue_infraction(sim, sim.entities[conceding.first_slot], INF_DISALLOWED)
		return
	if sim.penalty_shot and scorer != sim.penalty_shot_team:
		end_penalty_shot(sim)
		return
	scoring.goals += 1
	if (1 if sim.last_touch_slot < 6 else 0) ^ scorer:
		sim.shot_in_flight = true
		sim.last_shooter = sim.last_touch_slot
	PuckLogic.shot_landed(sim)
	sim.play_sfx(0x9c)
	hold_camera(sim)
	if scorer == 0:
		sim.crowd_noise = Entity.to_s16(sim.crowd_noise + 0x320)
		if sim.crowd_noise > 0x7d0:
			sim.crowd_noise = 0x7d0
		if sim.crowd_noise < 0x708:
			sim.crowd_noise = 0x708
	elif sim.crowd_noise < 0x320:
		sim.crowd_noise = 0x320
	Crowd.bench_cheer(sim, scorer)
	if scorer == 0 and not InfoPanel.speech_on(sim):
		InfoPanel.music(sim, 3)
	sim.excitement = Entity.to_s16(sim.excitement + (0xa if scorer == 1 else 0x1e))
	if scoring.skaters_on_ice < conceding.skaters_on_ice:
		sim.goal_flags = 2
	elif scoring.skaters_on_ice > conceding.skaters_on_ice:
		sim.goal_flags = 4
	else:
		sim.goal_flags = 1
	if Entity.to_s16(conceding.goalie_request) < 0:
		sim.goal_flags |= 8
	if not sim.no_stats:
		var r := scoring.carrier_history[0] & 0xff
		if r < 0x19:
			scoring.add_stat(r, Team.ST_GOALS)
		if scoring.skaters_on_ice > conceding.skaters_on_ice:
			scoring.add_stat(r, Team.ST_PPG)
		elif scoring.skaters_on_ice < conceding.skaters_on_ice:
			scoring.add_stat(r, Team.ST_SHG)
		if Entity.to_s16(conceding.goalie_request) < 0:
			scoring.add_stat(r, Team.ST_ENG)
		if sim.penalty_shot_phase != 0:
			scoring.penalty_shot_goals += 1
		elif sim.breakaway:
			scoring.breakaway_goals += 1
		if ((1 if sim.one_timer else 0) >> scorer) & 1:
			scoring.one_timer_goals += 1
		var a1 := Entity.to_s16(scoring.carrier_history[1])
		if a1 >= 0:
			if a1 < 0x19:
				scoring.add_stat(a1, Team.ST_ASSISTS)
			var a2 := Entity.to_s16(scoring.carrier_history[2])
			if a2 >= 0 and a2 < 0x19:
				scoring.add_stat(a2, Team.ST_ASSISTS)
		var gr := Entity.to_s16(conceding.goalie_request)
		if gr >= 0:
			var g := Entity.to_s16(Lines.line_table(conceding)[gr + 0x24] - 0x19)
			if g >= 0 and g < 3:
				conceding.goalie_stats[g][2] += 1
		if not sim.penalty_shot:
			if conceding.skaters_on_ice >= scoring.skaters_on_ice:
				for i in 6:
					var p := sim.entities[scoring.first_slot + i]
					if p.line_slot > 0:
						scoring.add_stat(Entity.to_s8(p.roster_idx), Team.ST_PLUS_MINUS, 1)
					var q := sim.entities[conceding.first_slot + i]
					if q.line_slot > 0:
						conceding.add_stat(Entity.to_s8(q.roster_idx), Team.ST_PLUS_MINUS, -1)
			goal_ends_penalty(sim, scorer)
		else:
			sim.last_touch_y = 0
			sim.last_touch_x = 0
			sim.faceoff_y = 0
			sim.faceoff_x = 0
		sim.breakaway = false
		sim.one_timer = false
	draw_score_digits(sim, scorer, scoring.goals)
	for i in 6:
		var p := sim.entities[scoring.first_slot + i]
		if p.line_slot <= 0 or (p.flags2 & Entity.F2_KNOCKED):
			continue
		p.flags &= ~Entity.F_ARRIVED
		if p.state() == Entity.State.PENALTY_SHOT_WAIT:
			puck.timer_b = 0
			p.set_state_reset(Entity.State.BENCH_WAIT)
			p.set_state_reset(Entity.State.CELEBRATE)
			p.set_state_reset(Entity.State.EXIT_BENCH)
		else:
			p.set_state_reset(Entity.State.CELEBRATE)
	sim.puck_in_net = false
	puck.vx = 0
	puck.x = ((-6 if puck.xi < 0 else 6) << 16) | (puck.x & 0xffff)
	puck.vy = 0
	puck.y = ((-0xf0 if puck.yi < 0 else 0xf0) << 16) | (puck.y & 0xffff)
	puck.vz = 0x600
	puck.z = puck.z & 0xffff
	_no_prediction(sim)
	puck.flags |= 4
	puck.set_state(Entity.State.PUCK_IDLE)
	Anim.set_animation(sim.shadow, 0x7fd)
	queue_infraction(sim, sim.entities[conceding.first_slot], INF_GOAL)
	if sim.no_stats:
		return
	end_penalty_shot(sim)
	sim.referee.set_state(Entity.State.REF_NORMAL)
	sim.penalty_shot_spot = Vector2i.ZERO
	# the CPU coaches: a team down by 4 changes its goalie, a trailing team its tactics
	var home := sim.teams[0]
	var away := sim.teams[1]
	var d := Entity.to_s16(home.goals - away.goals)
	if d < -3 and home.strategy > 1 and sim.user1_team != 1 and sim.user2_team != 1 and (home.goalie_request & 1) == 0:
		home.goalie_request ^= 1
	if d < -1 and home.strategy > 1:
		home.strategy -= 1
	if d < 1 and home.strategy2 > 1:
		home.strategy2 -= 1
	if d > 3 and away.strategy > 1 and sim.user1_team != 2 and sim.user2_team != 2 and (away.goalie_request & 1) == 0:
		away.goalie_request ^= 1
	if d > 1 and away.strategy > 1:
		away.strategy -= 1
	if d > -1 and away.strategy2 > 1:
		away.strategy2 -= 1
	Lines.time_announcements(sim)

## the goal line predictions of ai_goalie are dropped (the high bytes of their step counts)
static func _no_prediction(sim: Sim) -> void:
	for k in 2:
		sim.goal_prediction[k][1] = Entity.to_s16((sim.goal_prediction[k][1] & 0xff) | 0xff00)

## draw_score_digits (0x14a20): the scoreboard's score of team t (a hook; the HUD draws team.goals)
static func draw_score_digits(sim: Sim, t: int, goals: int) -> void:
	sim.stubbed("draw_score_digits", [t, goals])

## goal_disallowed_check (0x5aaae): with a delayed penalty pending, a goal of the team that touched
## the puck last does not count while one of its players on the ice is penalized
static func goal_disallowed_check(sim: Sim) -> bool:
	if not sim.delayed_call:
		return false
	var t := (1 if sim.puck.yi < 0 else 0) ^ (1 if sim.ends_switched else 0)
	if ((1 if sim.last_touch_slot < 6 else 0) ^ t) == 0:
		return false
	for i in 6:
		var p := sim.entities[t * 6 + i]
		if p.line_slot >= 0 and (p.flags2 & Entity.F2_PENALIZED):
			return true
	return false

## setup_faceoff (0x5d852, from sim_game_state when the period clock ran out): the puck plays on;
## the 1st and 2nd period end (infraction 1). Later a tie goes on into overtime (1) except after a
## regular season overtime (the game ends tied: 2); otherwise the game is over: nobody is
## controlled, the winners' bench cheers, the winners celebrate, the players of their box queue
## come out (line slots 5, 3) to join them, and when the game decides the Stanley Cup
## (game_over_check) the skater nearest to the bench door fetches it. The infraction 2 goes to the
## record after the winners' (entities[6] or the top net).
static func setup_faceoff(sim: Sim) -> void:
	if sim.stubbed("setup_faceoff", []):
		return
	var puck := sim.puck
	puck.set_state_reset(Entity.State.PUCK_NORMAL)
	if sim.period < 2:
		queue_infraction(sim, puck, INF_PERIOD_START)
		return
	sim.scratch_a = 7
	if Ceremonies.game_over_check(sim, sim.teams[0].goals, sim.teams[1].goals):
		sim.scratch_a = 8
	var diff := Entity.to_s16(sim.teams[0].goals - sim.teams[1].goals)
	sim.scratch_b = diff
	if diff == 0:
		if sim.period == 3 and Ceremonies.regular_season(sim):
			clear_infractions(sim)
			if sim.crowd_noise <= 0x4b0:
				sim.crowd_noise = mini(sim.crowd_noise + 0x384, 0x4b0)
			sim.play_stopped = true
			sim.game_over = true
			sim.excitement = Entity.to_s16(sim.excitement + 0x28)
			for i in 12:
				sim.entities[i].flags &= ~Entity.F_USER
			sim.scratch_ac = (sim.scratch_ac & ~0xffff) | 12
			queue_infraction(sim, sim.entities[0], INF_PERIOD_END)
		else:
			queue_infraction(sim, sim.entities[0], INF_PERIOD_START)
		return
	sim.user2_slot = -1
	sim.user1_slot = -1
	sim.puck_carrier = -1
	if puck.state() == Entity.State.PUCK_NORMAL:
		puck.set_state(Entity.State.PUCK_IDLE)
	for i in 12:
		sim.entities[i].flags &= ~Entity.F_USER
	var winner := 1 if diff < 0 else 0
	var first := winner * 6
	Crowd.bench_cheer(sim, winner)
	var taker := first
	if sim.scratch_a == 8:
		sim.series_announce = true
		sim.intermission_camera = true
		sim.shadow.set_state_reset(Entity.State.PUCK_GIVE_CUP)
		var best := 0x9c40
		for i in 6:
			var p := sim.entities[first + i]
			if p.line_slot > 0:
				var d := (p.xi + 0x91) * (p.xi + 0x91) + (p.yi - 6) * (p.yi - 6)
				if d <= best:
					best = d
					taker = p.slot
	sim.last_shooter = -1
	sim.scratch_b = 0
	for i in 6:
		var p := sim.entities[first + i]
		if p.line_slot > 0:
			if sim.scratch_a == 8 and taker == p.slot:
				p.set_state_reset(Entity.State.STANLEY_CUP)
				p.set_state_reset(Entity.State.GET_CUP)
			else:
				p.set_state_reset(Entity.State.CELEBRATE)
		elif p.line_slot < 0:
			var team := sim.team_of(p)
			var r := team.box_queue[0]
			if r >= 0:
				p.line_slot = 3 if sim.scratch_b != 0 else 5
				sim.scratch_b += 1
				p.set_state_reset(Entity.State.CELEBRATE)
				sim.put_player_on_ice(p, r)
				var k := 1
				while true:
					var v := team.box_queue[k] if k < 28 else -1
					team.box_queue[k - 1] = v
					if v < 0:
						break
					k += 1
	sim.scratch_ac = (sim.scratch_ac & ~0xffff)
	clear_infractions(sim)
	if sim.teams[0].goals > sim.teams[1].goals:
		if sim.crowd_noise <= 0x5dc:
			sim.crowd_noise = mini(sim.crowd_noise + 0x3e8, 0x5dc)
		if sim.scratch_a == 8:
			sim.crowd_noise = Entity.to_s16(sim.crowd_noise + 0x320)
	elif sim.crowd_noise < 0x320:
		sim.crowd_noise = 0x320
	sim.play_stopped = true
	sim.game_over = true
	sim.excitement = Entity.to_s16(sim.excitement + 0x28)
	queue_infraction(sim, sim.entities[first + 6], INF_PERIOD_END)

## end_period_flag (0x5ddbc, from ai_puck_faceoff when the clock ran out or the game is over):
## game_loop ends the period after this step (end_of_period)
static func end_period_flag(sim: Sim) -> void:
	if not sim.period_over:
		sim.period_over = true

## end_of_period (0x5dea6, from game_loop after the intermission): the line change prompts and
## bars are gone; the teams change ends and the next period begins. After the third period a tie
## goes into overtime (period 3: in the play-offs as often as needed, ends changed each time; a
## regular season game once, without changing ends); otherwise, or after an overtime, the game is
## over (period 4). Then period_cleanup.
static func end_of_period(sim: Sim) -> void:
	sim.lc_bar[1] = 0
	sim.lc_bar[0] = 0
	sim.lc_show[1] = 0
	sim.lc_show[0] = 0
	sim.lc_line[1] = -1
	sim.lc_line[0] = -1
	sim.teams[1].line_change_ui = false
	sim.teams[0].line_change_ui = false
	sim.ends_switched = not sim.ends_switched
	sim.period += 1
	if sim.period >= 3:
		if sim.period > 3:
			sim.period = 3
			if Ceremonies.regular_season(sim):
				sim.period = 4
		elif Ceremonies.regular_season(sim):
			sim.ends_switched = not sim.ends_switched
		sim.scratch_a = Entity.to_s16(sim.teams[0].goals - sim.teams[1].goals)
		if sim.scratch_a != 0:
			sim.period = 4
	Ceremonies.period_cleanup(sim)

## reset_players_for_faceoff (0x5e01a): nobody is offside; the players on the ice stand (the
## glide animation), with no pick-up delay or hit strength, and keep only their side and attack
## direction flags (and the state just entered)
static func reset_players_for_faceoff(sim: Sim) -> void:
	for t in 2:
		var team := sim.teams[t]
		team.flags &= ~Team.FL_OFFSIDE
		for i in 6:
			var p := sim.entities[team.first_slot + i]
			p.flags2 = 0
			if p.line_slot >= 0:
				Anim.set_animation(p, 0x289)
				p.timer_c = 0
				p.speed = 0
				p.flags &= 0xc2

# --------------------------------------------------------------------------------------------
# offside, icing, breakaway
# --------------------------------------------------------------------------------------------

## check_offside (0x55a9f): a team flagged offside (+0x44 bit 4) is cleared once none of its players
## is in the attacking zone (past y 0x4e); when the puck crosses a blue line (0x4a) into a zone
## (note_breakaway) the team attacking it is flagged if one of its players is already 10 past the
## line, unless the other team touched the puck last (the original takes any slot below 6, -1
## included, for the home team)
static func check_offside(sim: Sim) -> void:
	if not sim.opt_offsides or sim.penalty_shot or sim.penalty_shot_setup:
		return
	var puck := sim.puck
	for t in 2:
		var team := sim.teams[t]
		if team.flags & Team.FL_OFFSIDE:
			var inside := false
			for i in 6:
				var p := sim.entities[t * 6 + i]
				if p.line_slot >= 0:
					var py := p.yi if (p.flags & Entity.F_ATTACK_UP) else Sim._s16(-p.yi)
					if py > 0x4e:
						inside = true
						break
			if not inside:
				team.flags &= ~Team.FL_OFFSIDE
	var prev_y := Sim._s16(puck.prev_y >> 16)
	var line := 0
	if puck.yi >= 0x4a:
		if prev_y >= 0x4a:
			return
		line = 0x4a
	else:
		if puck.yi > -0x4a or prev_y <= -0x4a:
			return
		line = -0x4a
	note_breakaway(sim)
	# the team attacking that zone: at +y the home team unless the ends are switched
	var attacking: Team = sim.teams[0] if sim.teams[0].attacks_up == (line > 0) else sim.teams[1]
	if (attacking.first_slot < 6) != (sim.last_touch_slot < 6):
		attacking.flags &= ~Team.FL_OFFSIDE
		return
	var limit := line + (10 if line > 0 else -10)
	for i in 6:
		var p := sim.entities[attacking.first_slot + i]
		if p.line_slot >= 0 and ((line > 0 and p.yi > limit) or (line < 0 and p.yi < limit)):
			attacking.flags |= Team.FL_OFFSIDE

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
	sim.icing_flags |= 1          # called when a player of the other team touches it (update_carrier)

## two_line_pass_check (0x541ca): offside on a pass: a player of the team flagged offside receives
## a puck headed for his own goal line within 0x2c of the middle, last touched by the other team
static func two_line_pass_check(sim: Sim, receiver: Entity) -> bool:
	if not sim.opt_offsides or sim.no_stats or sim.penalty_shot or sim.penalty_shot_setup:
		return false
	var puck := sim.puck
	if absi(puck.yi) > 0xe8:
		return false
	# where the puck crosses the own goal line (goal_prediction +2 / +6)
	var pred: Array = sim.goal_prediction[1 if (receiver.flags & Entity.F_ATTACK_UP) else 0]
	if absi(pred[0]) > 0x2c or (sim.opponents_of(receiver).flags & Team.FL_OFFSIDE) == 0:
		return false
	# the last touch by a team mate (the original takes any slot below 6, -1 included, as home)
	if (receiver.slot < 6) == (sim.last_touch_slot < 6):
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

## note_breakaway: breakaway bookkeeping when the puck crosses the blue line
static func note_breakaway(sim: Sim) -> bool:
	count_defenders_ahead(sim)
	sim.breakaway = sim.defenders_ahead != 0
	if not sim.breakaway:
		return false
	sim.crowd_noise += 100
	if sim.penalty_shot_phase != 0:
		return false
	# the breakaways of the carrier's team (+0x1c)
	sim.teams[1 if sim.puck_carrier > 5 else 0].breakaways += 1
	return true

# --------------------------------------------------------------------------------------------
# faceoffs (ai_puck_faceoff2 positioning, faceoff_resolve)
# --------------------------------------------------------------------------------------------

## position of a player at the faceoff (ai_all_goto_faceoff / ai_puck_faceoff2 share this)
static func faceoff_position(sim: Sim, e: Entity) -> Vector2i:
	var team := sim.team_record(e)
	# the row: 6 - skaters on the ice, one more when short handed with the goalie pulled; the
	# table is read flat (row * 8 + line slot) as the original does
	var row := -team.skaters_on_ice
	if row > -6 and team.goalie_pulled():
		row -= 1
	var flat := (row + 6) * 8 + e.line_slot
	var idx := 0
	if flat >= 0 and flat < Tables.faceoff_lineup.size() * 8:
		idx = Tables.faceoff_lineup[flat >> 3][flat & 7]
	var spot: Array = Tables.faceoff_spots[idx] if idx >= 0 and idx < Tables.faceoff_spots.size() else [0, 0]
	var sx: int = spot[0]
	var sy: int = spot[1]
	var up := (e.flags & Entity.F_ATTACK_UP) != 0
	if not up:
		sx = -sx
		sy = -sy
	var fx := sim.faceoff_x
	var fy := sim.faceoff_y
	if e.line_slot == 0:
		# the goalie in his crease, shaded towards the dot when the faceoff is in his end
		if absi(fy) > 0x27 and (fy < 0) == up:
			var d := absi(Sim._s16(fy - (-0x27 if up else 0x27)))
			sx = Sim._s16(sx + AI._div_trunc(fx * d * 3, 0x1000))
		return Vector2i(sx, sy)
	if idx <= 2:
		# the defencemen squeeze towards the middle when the dot is off centre
		if (sx ^ fx) < 0:
			sy = Sim._s16(sy - (fy >> 3))
		sx = Sim._s16(sx - (fx >> 2))
	return Vector2i(Sim._s16(sx + fx), Sim._s16(sy + fy))

## the block of ai_puck_faceoff2 that snaps everybody into place before the drop
## ai_puck_faceoff2: the nets back on their pegs at y +-0xec, still
static func reset_nets(sim: Sim) -> void:
	for n in [Entity.Slot.NET_TOP, Entity.Slot.NET_BOTTOM]:
		var net := sim.entities[n]
		net.x = net.x & 0xffff
		net.y = ((0xec if n == Entity.Slot.NET_TOP else -0xec) << 16) | (net.y & 0xffff)
		net.vx = 0
		net.vy = 0

## faceoff_resolve (0x4da7b, from ai_puck_faceoff2 when the countdown ran out): the drop. The organ
## stops, play is on. The home centre wins when randomrange(0x21) reaches 0x10 less the home
## readiness bonus plus the away one plus the away centre's faceoff rating less the home one (the
## rating byte 0x13 of `player_ratings`; the first player of each team in line slot 4 is the
## centre); the winner touched the puck last. The puck goes the way the winner's user holds (now and
## then, or without a direction held, a random one of the five towards the winner's end), a little
## up the ice, and bounces off the stick; the referee skates off to his side.
static func faceoff_resolve(sim: Sim) -> void:
	var e := sim.puck
	InfoPanel.stop_music(sim)
	sim.play_sfx(0xab)
	sim.faceoff_pending = false
	sim.whistle_ready = false
	sim.play_stopped = false
	e.flags2 &= ~Entity.F2_KNOCKED
	sim.misc_first_touch = true
	var chance := 0x10 - Tables.faceoff_bonus[sim.faceoff_ready[0]] + Tables.faceoff_bonus[sim.faceoff_ready[1]]
	var hc := 0
	while hc < 6 and sim.entities[hc].line_slot != 4:
		hc += 1
	var ac := 6
	while ac < 12 and sim.entities[ac].line_slot != 4:
		ac += 1
	var ra := Entity.to_s8(sim.entities[ac].roster_idx)
	var rh := Entity.to_s8(sim.entities[hc].roster_idx)
	chance = Entity.to_s16(chance + _player_rating(sim, 1, ra, 0x13) - _player_rating(sim, 0, rh, 0x13))
	sim.scratch_ac = (sim.scratch_ac & ~0xffff) | (chance & 0xffff)
	var side: int
	if Entity.to_s16(sim.random(0x21)) < chance:
		side = sim.faceoff_side[1]
		sim.last_touch_slot = ac
	else:
		side = sim.faceoff_side[0]
		sim.last_touch_slot = hc
	var held: int
	var bias: int
	if side & 0x800:
		held = sim.faceoff_dir[1]
		bias = -0x800
	else:
		held = sim.faceoff_dir[0]
		bias = 0x800
	sim.scratch_a = Entity.to_s16(held)
	var random_dir := true
	if (sim.scratch_a & 8) == 0:
		sim.scratch_a = held & 7
		random_dir = sim.random(4) == 0
	if random_dir:
		sim.scratch_a = (sim.random(5) - 2) & 7
		if bias < 0:
			sim.scratch_a ^= 4
	var v: Array = Tables.dir8_vectors[sim.scratch_a]
	sim.scratch_a *= 2
	e.vx = Entity.to_s16(v[0] << 5)
	e.vy = Entity.to_s16((v[1] << 5) + bias)
	e.vz = sim.random(0x800)
	e.z &= 0xffff
	e.flags &= ~Entity.F_ARRIVED
	e.set_state(Entity.State.PUCK_NORMAL)
	var ref := sim.referee
	ref.set_state(Entity.State.REF_NORMAL)
	ref.vx = 0x500 if ref.xi > 0 else -0x500

## byte k of the ratings of roster player r of team t, read from `player_ratings` as the original
## does (0x14 bytes a skater, 0x1f4 a team: a roster index of -1 reads the other table's end)
static func _player_rating(sim: Sim, t: int, r: int, k: int) -> int:
	var flat := t * 0x1f4 + r * 0x14 + k
	if flat < 0 or flat >= 2 * 0x1f4:
		return 0
	return Lines.skater_ratings(sim.teams[flat / 0x1f4], (flat % 0x1f4) / 0x14)[flat % 0x14]

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

## ref_queue_infraction_event (0x62c37): the first frozen puck of each goalie (bit 1 << goalie
## number, the away team's << 3) queues a deferred call (an empty one in this build: return_one)
## and so ends the frame's steps; true when it did
static func ref_queue_infraction_event(sim: Sim) -> bool:
	if sim.infraction_events == 0x3f or sim.ref_infraction_slot < 0:
		return false
	var e := sim.entities[sim.ref_infraction_slot]
	var away := (e.flags & Entity.F_PLAYER2) != 0
	var bit := 1 << (sim.team_record(e).goalie_request & 31)
	if away:
		bit <<= 3
	if sim.infraction_events & bit:
		return false
	sim.infraction_events |= bit
	sim.deferred = true
	return true

## goal_milestone_check (0x62807): a milestone of the scorer (a hat trick, a record of the season)
## queues a deferred call; in this build an empty one (return_one), so only the frame's steps end
static func goal_milestone_check(sim: Sim) -> void:
	if sim.stubbed("goal_milestone_check", []):
		return
