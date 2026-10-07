class_name MatchSetup
## The start of the match and of its periods, ported literally: reset_game_state (0x14056, run
## before the anthem and again after it by play_match_from_start), reset_match_state (0x5e086:
## game_state_clear, team_state_clear, team_energy_init, the first period), period_cleanup
## (0x5de70, after every period: the next period or the end of the game) with
## period_reset_entities, leave_match_video, period_init (the 17 entities from entity_init,
## the clock, two steps of the simulation) and reset_bench_slots, init_match (0x47cd6, the
## anthem) and setup_demo_faceoff (0x13c79, the lines at the opening faceoff).

## team_energy_init: the entity_of word of a roster player from the status byte of his record
## (unk_ccca8): 0 empty -7, 1 injured -4, 2 scratched -6, otherwise on the bench
const STATUS_ENTITY_OF := [-7, -4, -6, -2, -2, -2, -2, -2, -2]
## init_match: the anthem of the home team's country (unk_cc9cc, in steps)
const ANTHEM_STEPS := 0x708

# --------------------------------------------------------------------------------------------
# the start of the match
# --------------------------------------------------------------------------------------------

## reset_game_state (0x14056): the match globals cleared before the game (the summary events,
## the panel, the referee, the shot, the line change prompts, the penalty shot, the crowd), then
## reset_match_state; the period number is 1, nothing is over. The mouse, the frame timing and
## the summary's event bytes are the main loop's.
static func reset_game_state(sim: Sim) -> void:
	sim.event_rec[0] = 0xff
	sim.goal_call = []
	sim.infraction_events = 0
	sim.panel = -1
	sim.ref_infraction_slot = -1
	sim.ref_phase = -1
	sim.stoppage_timer = -1
	sim.announce_timer = -1
	sim.goalie_pass_mode = 0
	sim.pass_target = 0
	sim.shot_power = 0
	sim.pending_dir = 0
	sim.last_passer = 0
	sim.last_shooter = 0
	sim.penalty_box_mode = false
	sim.ref_infraction = 0
	sim.whistle_timer = 0
	sim.second_timer = 0
	for t in 2:
		sim.lc_bar[t] = 0
		sim.lc_show[t] = 0
		sim.lc_blink[t] = 0
		sim.lc_place[t] = 0
		sim.lc_line[t] = 0
		sim.lc_timer[t] = 0
		sim.teams[t].line_change_ui = false
		sim.line_hotkey[t] = 0
		sim.line_hotkey_req[t] = 0
	sim.message_timer = 0
	sim.injury_stoppage = false
	sim.ref_hits = 0
	sim.message = -1
	sim.clip_frame = -1
	sim.clip = -1
	InfoPanel.set_text(sim, [])
	sim.penalty_shot_phase = 0
	sim.penalty_shot = false
	sim.penalty_shot_setup = false
	sim.defenders_ahead = 0
	sim.breakaway = false
	sim.penalty_shot_slot = -1
	sim.excitement = 0
	Crowd.reset(sim)
	sim.save_clip_shown = false
	sim.last_penalty_team = 0
	sim.excitement_samples = 0
	sim.excitement_peak = 0
	sim.excitement_sum = 0
	reset_match_state(sim)
	sim.period_num = 1
	sim.deferred = false
	sim.period_over = 0
	sim.match_over = false
	sim.hud_acc = 0

## reset_match_state (0x5e086)
static func reset_match_state(sim: Sim) -> void:
	game_state_clear(sim)
	team_state_clear(sim)
	sim.period = 0
	team_energy_init(sim)
	period_cleanup(sim)

## game_state_clear (0x5cd4f): the scratch words, the camera's target, the faceoff, the flag
## bytes, the infractions
static func game_state_clear(sim: Sim) -> void:
	sim.scratch_ac = 0
	sim.scratch_a = 0
	sim.scratch_b = 0
	sim.camera_target_x = 0
	sim.camera_target_y = 0
	sim.camera_offset_y = 0
	sim.faceoff_x = 0
	sim.faceoff_y = 0
	sim.faceoff_dir[0] = 0
	sim.faceoff_dir[1] = 0
	sim.puck_in_net = false
	sim.goalie_pass_mode = 0
	sim.tick_toggle = 0
	sim.tick24 = 0
	sim.crowd_toggle = false
	sim.last_sfx = -1
	# game_flags
	sim.play_stopped = false
	sim.ends_switched = false
	sim.stoppage_countdown = false
	sim.delayed_call = false
	sim.no_stats = false
	sim.game_over = false
	sim.intermission_camera = false
	# action_flags
	sim.action_pass = false
	sim.action_shot = false
	sim.action_hold_camera = false
	sim.action_replay = false
	# stop_flags
	sim.faceoff_pending = false
	sim.whistle_ready = false
	sim.shot_in_flight = false
	sim.power_play = false
	sim.power_play_team = 0
	sim.offside_warning = false
	# misc_flags
	sim.misc_first_touch = false
	sim.half_announce = false
	sim.second_tick = false
	Rules.clear_infractions(sim)

## team_state_clear (0x5b881): both team records zeroed (the statistics, the lines in use, the
## energies, the roster places, the penalty box, the coaching); no extra attacker, an empty box
static func team_state_clear(sim: Sim) -> void:
	for team: Team in sim.teams:
		team.shots = 0
		team.pp_goals = 0
		team.power_plays = 0
		team.pp_shots = 0
		team.pp_time = 0
		team.penalty_count = 0
		team.penalty_minutes = 0
		team.zone_time = 0
		team.goals = 0
		team.faceoffs_won = 0
		team.offensive_faceoffs = 0
		team.one_timer_tries = 0
		team.one_timers = 0
		team.one_timer_goals = 0
		team.breakaways = 0
		team.breakaway_goals = 0
		team.penalty_shots = 0
		team.penalty_shot_goals = 0
		team.hits = 0
		team.passes = 0
		team.passes_completed = 0
		team.current_line = 0
		team.dpair_counter = 0
		team.extra_attacker = -1
		team.carrier_history = PackedInt32Array([0, 0, 0])
		team.skaters_on_ice = 0
		team.goalie_request = 0
		team.nearest_d2 = 0
		team.nearest_dist = 0
		team.nearest_slot = 0
		team.flags = 0
		team.energy.fill(0)
		team.entity_of.fill(0)
		team.box_queue.fill(0)
		team.box_queue[0] = -1
		team.strategy = 0
		team.strategy2 = 0
		team.flags2 = 0
		team.mode = 0
		team.energy_threshold = 0
		team.goalie_slot = 0

## team_energy_init (0x5b97a): six players dressed, the roster places from the status bytes of
## the players' records
static func team_energy_init(sim: Sim) -> void:
	for team: Team in sim.teams:
		team.skaters_on_ice = 6
		for r in 0x1c:
			var s := team.roster_status[r]
			team.entity_of[r] = STATUS_ENTITY_OF[s] if s < STATUS_ENTITY_OF.size() else -2

## init_match (0x47cd6): the anthem. The anthem of the home team's country, its flag on the
## scoreboard; the period number is -1 (the anthem), the lines dressed; the goalies in their
## creases, the skaters on their blue lines in a random order (away team first, from the last
## entity), the puck at the boards, the referee at the boards across; two steps of the simulation
static func init_match(sim: Sim) -> void:
	InfoPanel.music(sim, 10)
	var home_id: int = sim.team_ids[0]
	var away_id: int = sim.team_ids[1]
	var country: int = Tables.anthem_country[clampi(home_id, 0, Tables.anthem_country.size() - 1)]
	var length: int = Tables.anthem_length[country]
	InfoPanel.load_clip(sim, 4 if country != 1 else 3)
	InfoPanel.set_text(sim, [])
	sim.period_num = -1
	sim.faceoff_y = 0
	sim.faceoff_x = 0
	sim.seed = (sim.seed + (home_id << 16) + away_id) & 0xffffffff
	sim.sequence_steps = ANTHEM_STEPS
	sim.period_over = 0
	sim.user2_slot = -1
	sim.user1_slot = -1
	for t in 2:
		var team := sim.teams[t]
		reset_team_for_period(sim, team)
		Lines.apply_line_change(sim, team)
		Lines.dress_line(sim, team)
	Rules.reset_players_for_faceoff(sim)
	for t in 2:
		var taken := [false, false, false, false, false]
		for i in 6:
			var e: Entity = sim.entities[11 - t * 6 - i]
			var up := (e.flags & Entity.F_ATTACK_UP) != 0
			if e.line_slot == 0:
				e.x &= 0xffff
				e.target_x = 0
				var gy := -0xdc if up else 0xdc
				e.y = (gy << 16) | (e.y & 0xffff)
				e.target_y = gy
				e.timer_b = -100
				e.vy = 0
				e.vx = 0
				e.heading = ((0 if up else 4) << 16) | (e.heading & 0xffff)
				Anim.set_animation(e, 0x99)
			else:
				var k := sim.random(5)
				while taken[k]:
					k = (k + 1) % 5
				taken[k] = true
				var x := k * 0x28 - 0x50 + sim.random(8) - 4
				e.target_x = x
				e.x = (Entity.to_s16(x + sim.random(2)) << 16) | (e.x & 0xffff)
				var y := (-0x3a if up else 0x30) + sim.random(4) - 2
				e.y = (y << 16) | (e.y & 0xffff)
				e.target_y = y
				e.heading = (4 << 16) | (e.heading & 0xffff)
				e.vy = 0
				e.vx = 0
				e.timer_b = Entity.to_s16(length + sim.random(0x28) - 0x14)
				Anim.set_animation(e, 0)
				e.frame = 0x171
			e.set_state(Entity.State.ANTHEM)
	var puck := sim.puck
	sim.puck_stuck_timer = 0x78
	puck.x = (200 << 16) | (puck.x & 0xffff)
	puck.y = (puck.y & 0xffff) - (0x12c << 16)
	puck.vx = 0
	puck.vy = 0
	puck.set_state(Entity.State.PUCK_IDLE)
	var ref := sim.referee
	ref.timer_a = country
	ref.x = (0x8e << 16) | (ref.x & 0xffff)
	ref.target_x = 0x8e
	ref.x = (Entity.to_s16(ref.xi + sim.random(2)) << 16) | (ref.x & 0xffff)
	ref.y &= 0xffff
	ref.target_y = 0
	ref.heading = (4 << 16) | (ref.heading & 0xffff)
	ref.vy = 0
	ref.vx = 0
	ref.timer_b = length
	Anim.set_animation(ref, 0)
	ref.frame = 0x289
	ref.set_state(Entity.State.REF_ANTHEM)
	sim.ref_phase = 0
	sim.action_hold_camera = true
	sim.sim_tick()
	sim.sim_tick()
	sim.sort_draw_order()
	sim.puck_carrier = -1
	sim.camera_x = 0
	sim.camera_target_x = 0
	sim.camera_y = 0
	sim.camera_target_y = 0
	if sim.clip != -1:
		InfoPanel.open(sim)
	sim.lc_show[1] = 0
	sim.lc_show[0] = 0
	sim.lc_bar[1] = 0
	sim.lc_bar[0] = 0

## play_match_from_start (0x13e8f) after match_sequence: the first period set up again, the lines
## dressed at the centre faceoff (setup_demo_faceoff) unless the faceoff wait was skipped without
## line changes
static func start_match(sim: Sim) -> void:
	if sim.skip_wait:
		sim.fade_in = true
	sim.period = 0
	reset_game_state(sim)
	if sim.opt_line_changes or not sim.skip_wait:
		setup_demo_faceoff(sim)
	if not sim.demo and not sim.skip_wait:
		sim.fade_in = false

## setup_demo_faceoff (0x13c79): the current lines dressed (dress_current_lines), everybody at his
## place of the centre faceoff (faceoff_spots by line slot and number of skaters), standing towards
## the puck, waiting for the drop (FACEOFF_WAIT, the centres FACEOFF); none of it in a demo
static func setup_demo_faceoff(sim: Sim) -> void:
	if sim.demo:
		return
	dress_current_lines(sim)
	sim.faceoff_y = 0
	sim.faceoff_x = 0
	var puck := sim.puck
	puck.y &= 0xffff
	puck.x &= 0xffff
	for i in 12:
		var e: Entity = sim.entities[i]
		e.timer_b = -100
		var ls := e.line_slot
		sim.scratch_b = ls
		e.set_state_reset(Entity.State.FACEOFF if ls == 4 else Entity.State.FACEOFF_WAIT)
		if sim.scratch_b < 0:
			continue
		var team := sim.team_of(e)
		var place: int = Tables.faceoff_lineup[6 - team.skaters_on_ice][ls]
		var spot: Array = Tables.faceoff_spots[place]
		var sx: int = spot[0]
		var sy: int = spot[1]
		if (e.flags & Entity.F_ATTACK_UP) == 0:
			sx = -sx
			sy = -sy
		sim.scratch_a = sx
		sim.scratch_b = sy
		e.x = (Entity.to_s16(sx) << 16) | (e.x & 0xffff)
		e.y = (Entity.to_s16(sy) << 16) | (e.y & 0xffff)
		e.vy = 0
		e.vx = 0
		e.heading = (Tables.direction8(Entity.to_s16(puck.xi - sx), Entity.to_s16(puck.yi - sy)) << 16) | (e.heading & 0xffff)
		var dir := e.facing if e.left_handed != 0 else (8 - e.facing) & 7
		if e.line_slot == 0:
			e.frame = dir * 3 + 0x196
			sim.scratch_b = 1
		else:
			e.frame = dir * 5
			sim.scratch_b = 0x289
		e.flags2 &= ~Entity.F2_UNSELECTABLE
		e.flags &= ~Entity.F_BUSY
		e.anim_pos = 0
		e.anim = sim.scratch_b
		e.anim_hold = -1
	sim.scratch_ac = (sim.scratch_ac & ~0xffff)

## dress_current_lines (0x5e0b0)
static func dress_current_lines(sim: Sim) -> void:
	for t in 2:
		Lines.apply_line_change(sim, sim.teams[t])
		Lines.dress_line(sim, sim.teams[t])

# --------------------------------------------------------------------------------------------
# the periods
# --------------------------------------------------------------------------------------------

## period_cleanup (0x5de70): after the last period the game is over (set_game_over: the three
## stars follow); otherwise the next period: everybody to the bench and rested, the intermission
## (leave_match_video), the period set up (period_init) and the places of the penalized players
## kept off the ice (reset_bench_slots)
static func period_cleanup(sim: Sim) -> void:
	if sim.stubbed("period_cleanup", []):
		return
	if sim.period == 4:
		set_game_over(sim)
		return
	period_reset_entities(sim)
	if sim.period > 0:
		leave_match_video(sim)
	period_init(sim)
	reset_bench_slots(sim)

## set_game_over (0x5dd9e)
static func set_game_over(sim: Sim) -> void:
	if not sim.match_over:
		sim.match_over = true

## period_reset_entities (0x5de42): period_start_reset; every entity at x 0 (the fraction stays)
static func period_reset_entities(sim: Sim) -> void:
	period_start_reset(sim)
	for e: Entity in sim.entities:
		e.x &= 0xffff

## period_start_reset (0x5ddda): the players in the boxes counted, everybody else on the bench;
## both teams rested; the first line, or with line changes the power play (4) / penalty killing
## (6) unit when the numbers differ
static func period_start_reset(sim: Sim) -> void:
	Rules.count_penalized(sim)
	for t in 2:
		var team := sim.teams[t]
		var other := sim.teams[1 - t]
		reset_team_for_period(sim, team)
		team.current_line = 0
		if sim.opt_line_changes:
			var d := Entity.to_s16(team.skaters_on_ice - other.skaters_on_ice)
			if d != 0:
				team.current_line = 4 if d > 0 else 6

## reset_team_for_period (0x5b826): everybody rested; the players hurt for the period back on the
## bench
static func reset_team_for_period(sim: Sim, team: Team) -> void:
	for r in 0x1c:
		team.energy[r] = 0x1000
		if team.entity_of[r] == -3:
			team.entity_of[r] = -2
			team.roster_status[r] = 3
	for i in 6:
		var e: Entity = sim.entities[team.first_slot + i]
		if e.roster_idx >= 0 and e.roster_idx < 0x1c:
			e.energy = team.energy[e.roster_idx]

## leave_match_video (0x10f6d): the intermission. The match's video mode, fades and sounds stop
## (unless period_over is -1, as a demo or a highlight sets it), end_match_from_period shows the
## box score, the scores around the league and the pause menu, writes the summary's period and
## leaves period_over at -1; the period count goes on
static func leave_match_video(sim: Sim) -> void:
	if not sim.stubbed("leave_match_video", []):
		if sim.period_over != -1:
			InfoPanel.stop_music(sim)
			sim.summary_flush()
		if not sim.no_stats:
			sim.summary_close_period()
		sim.intermission_pending = true
	sim.period_over = -1
	sim.period_num += 1

## period_init (0x5c010): the strategy of the period, the entities set up, the clock; the users
## take the centres' wings (slot 2 home, 8 away, a second user of the same team the next one);
## no message, no panel, no penalty shot; the puck waits for the faceoff (PUCK_FACEOFF); a quiet
## crowd after the first period, the whistle ready, no camera hold; the replay starts again;
## two steps of the simulation; the halfway announcement in the first two periods; the camera
## at the centre, cutting to the scene
static func period_init(sim: Sim) -> void:
	sim.line_hotkey_req[1] = 0
	sim.line_hotkey_req[0] = 0
	Lines.period_strategy_init(sim)
	sim.save_clip_shown = false
	entities_setup(sim)
	period_clock_init(sim)
	if sim.user1_team == 1:
		sim.user1_slot = 2
	elif sim.user1_team == 2:
		sim.user1_slot = 8
	if sim.user2_team != 0:
		if sim.user2_team == sim.user1_team:
			sim.user2_slot = Entity.to_s16(sim.user1_slot - 1)
		elif sim.user2_team == 1:
			sim.user2_slot = 2
		elif sim.user2_team == 2:
			sim.user2_slot = 8
	sim.goal_call = []
	sim.message = -1
	sim.message_timer = 0
	sim.panel = -1
	sim.penalty_shot_phase = 0
	sim.penalty_shot = false
	sim.penalty_shot_setup = false
	sim.defenders_ahead = 0
	sim.breakaway = false
	sim.penalty_shot_slot = -1
	sim.faceoff_x = 0
	sim.faceoff_y = 0
	sim.puck.set_state(Entity.State.PUCK_FACEOFF)
	if sim.period != 0:
		sim.crowd_noise = 0
	sim.whistle_ready = true
	sim.action_hold_camera = false
	sim.replay.reset()
	sim.last_sfx = -1
	sim.sim_tick()
	sim.sim_tick()
	sim.excitement = 0x10
	if sim.period < 2:
		sim.half_announce = true
	sim.puck_carrier = -1
	sim.camera_y = 0
	sim.camera_x = 0
	sim.camera_offset_y = 0
	sim.camera_target_y = 0
	sim.camera_target_x = 0
	sim.fade_in = true

## entities_setup (0x5d80a): the entities from entity_init, the players turned round when the
## teams changed ends; the high bytes of the user slots set (no user before period_init picks one)
static func entities_setup(sim: Sim) -> void:
	sim.camera_x = 0
	sim.camera_y = 0
	entities_init(sim)
	if sim.ends_switched:
		for i in 12:
			sim.entities[i].flags ^= Entity.F_ATTACK_UP
	for t in 2:
		sim.teams[t].attacks_up = (t == 0) != sim.ends_switched
	sim.user1_slot = Entity.to_s16(0xff00 | (sim.user1_slot & 0xff))
	sim.user2_slot = Entity.to_s16(0xff00 | (sim.user2_slot & 0xff))

## entities_init (0x5ba89): every entity cleared and placed from entity_init (the players in a row
## at the bench, the nets, the puck, its shadow, the referee), its team by the away flag; the draw
## order from the slots, then sorted; the referee's skills
static func entities_init(sim: Sim) -> void:
	for e: Entity in sim.entities:
		e.clear()
	for i in 17:
		var e: Entity = sim.entities[i]
		var init: Array = Tables.entity_init[i]
		e.slot = i
		e.roster_idx = -1
		e.next_line_slot = -1
		e.next_roster = -1
		e.x = int(init[0]) << 16
		e.y = int(init[1]) << 16
		e.z = int(init[2]) << 16
		e.frame = init[3]
		e.side = init[4]
		e.half_w = init[5]
		e.half_h = init[6]
		e.state_stack[0] = init[7]
		e.flags = init[8]
		e.team = 1 if (e.flags & Entity.F_PLAYER2) != 0 else 0
		e.timer_b = 0
		sim.draw_list[i] = i
		sim.draw_pos[i] = i
	var ref := sim.referee
	ref.heading = (2 << 16) | (ref.heading & 0xffff)
	ref.line_slot = -1
	ref.weight = 7
	ref.speed_skill = 0xf
	ref.stamina = 0xf
	sim.ref_phase = -1
	sim.sort_draw_order()

## period_clock_init (0x5ba07): the period's length on the clock (period_length), the late game
## announcement at a random time of the second half, play stopped
static func period_clock_init(sim: Sim) -> void:
	var t := period_length(sim)
	sim.clock_seconds = t
	sim.clock_sub = 0
	sim.period_length = t
	sim.announce_time = Entity.to_s16(t - sim.random(Entity.to_s16(t) >> 1))
	sim.play_stopped = true

## period_length (0x5b9d1): word_cbc4a by option_flags bits 10-11 (settings2 bits 2-3); the
## overtime of a regular season game (settings2 bit 1, after the 3rd period) is the first entry
static func period_length(sim: Sim) -> int:
	var t: int = sim.period_lengths[(sim.settings2 >> 2) & 3]
	if (sim.settings2 & 2) != 0 and sim.period_num > 3:
		t = sim.period_lengths[0]
	return t

## reset_bench_slots (0x510a9): the box's players keep their places off the ice: from the last
## roster player on, each one with time in the box (entity_of > 0) takes one of the last entities
## (no more than two), which stays on the bench (line slot -1, waiting); the team plays with the rest
static func reset_bench_slots(sim: Sim) -> void:
	for t in 2:
		var team := sim.teams[t]
		var n := 6
		for r in range(0x1b, -1, -1):
			if team.entity_of[r] > 0 and n > 4:
				n -= 1
				var e: Entity = sim.entities[t * 6 + n]
				e.line_slot = -1
				e.timer_b = -100
		team.skaters_on_ice = n
