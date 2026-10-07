class_name Sim
extends RefCounted
## The match simulation: 17 entities stepped at a fixed 60 Hz in the order of sim_tick /
## sim_update_players of the original. This file holds the state, the per step loop, the
## physics (integration, boards, nets, neighbours), the skating controls and the camera.
## The rules (stoppages, faceoffs, clock, goals) are in Rules.gd, the puck handling in PuckLogic.gd
## and the AI state handlers in AI.gd; all of them operate on a Sim instance.
##
## Fixed point conventions of the original are kept: positions 16.16, velocities 16 bit,
## pos += 16 * v per step, world x across the rink (boards at +-160), y along it (boards +-264,
## goal lines +-232, blue lines +-78), the home team starts shooting at the +y net.

const STEP_DT := 16                 # position += 16 * velocity per step (scratch_e03b2 >> 16)
const GRAVITY := 6 * 16
const RINK_HALF_W := 160            # boards: x = +-160 (0xa0)
const RINK_HALF_H := 264            # boards: y = +-264 (0x108)
const CORNER_RADIUS := 64
const GOAL_LINE_Y := 232            # 0xe8
const BLUE_LINE_Y := 78             # 0x4e
const NET_Y := 236                  # net entities sit at y = +-236
const MAX_SPEED := 16000

# option_flags of the original (settings menu): all rules on by default
var opt_penalties := true           # bit 0
var opt_offsides := true            # bit 1
var opt_line_changes := true        # bit 2: line changes and fatigue (Lines.gd)
var opt_two_line_pass := true       # bit 3
var opt_injuries := true            # bit 4 (option_flags starts as 0xff: every option on)
var opt_sound := true               # bit 7: the sound effects (a hotkey toggles them); no crowd clip without
var demo := false                   # dword_cc0ec: a demo game (no crowd clips at the stoppages)

var entities: Array[Entity] = []
var teams: Array[Team] = []
var team_info: Array = [null, null]  # Database.TeamInfo of the home and the away team (null: placeholders)
var team_ids := [0, 1]               # word_c90ca / away_team_id: the numbers of the two teams (the anthem's country)
var puck: Entity
var shadow: Entity
var referee: Entity
var puck_carrier: int = -1          # slot of the carrier, 16 = referee, -1 free
var user1_slot: int = -1
var user2_slot: int = -1
var user1_team: int = 1             # 0 none, 1 home, 2 away (user1_team / user2_team)
var user2_team: int = 0

# game_flags
var play_stopped := false           # bit 0: whistle, players go to the faceoff
var ends_switched := false          # bit 1: teams switched ends (2nd period)
var stoppage_countdown := false     # bit 2: stoppage_timer running
var delayed_call := false           # bit 3: a penalty is pending on the carrier's team
var no_stats := false               # bit 4
var game_over := false              # game_flags 0x40: the final whistle went
# ceremonies (Ceremonies.gd)
var intro := false                   # the anthem before the game (match_sequence) is running
var stars_running := false           # the three stars after the game (three_stars_sequence)
var match_over := false              # word game_over: the game is decided (set_game_over; 0 while the stars run, 1 once presented)
var finished := false                # end_match_from_loop: the three stars are over, the match is finished
var saved_period_num := 1            # three_stars_sequence keeps the period count while it runs
var intermission_pending := false    # end_of_period: a period ended, the front end shows the intermission
var sequence_steps: int = 0          # sequence_steps: steps left of the anthem / three stars
var cup_final := false               # game_over_check: this game decides the Stanley Cup (the harness's stub result)
var cup_series := PackedByteArray()  # dword_dc338 (alloc_cup_banner): the 7 games of the play-off final, empty otherwise
var cup_series_games := 0            # the final's length when the league fixes it (option_flags bits 12..14), else 0
var series_announce := false         # byte_ccca0: the cup was won, the pause menu says the series result
var intermission_camera := false     # game_flags 0x80 (the cup presentation)
var stars: Array = []                # e9af8: up to 3 x [team, roster], the 1st star first
var game_winner := Vector2i(-1, -1)  # e9af0 / e9af4: [team, roster] of the overtime winner
# the scoreboard panel of the stoppages (InfoPanel.gd): panel_state and the clip of panel_clip
var panel: int = -1                  # -1 closed, 0..0xf opening, 0x10 plays the clip, ..0xff open, 0x100 held, 600..0x268 closing
var clip: int = -1                   # the clip on the scoreboard (Tables.announcer_ppv_names), -1 none
var clip_frame: int = -1             # clip_frame: frame of the clip shown
var clip_pos: int = 0                # clip_script_pos high word: position in the clip script
var clip_time: int = 0               # clip_script_pos low word: steps left on this frame
var panel_text: Array = ["", "", "", "", ""]   # panel_title (byte_e02c8), byte_e0250, byte_e028c, byte_e0308, byte_e0344
var event_log: Array = []            # e9b4c: the last 8 goals / penalties / injuries of the period
# the game summary (GSUMMARY.DB, gsummary_append_record): the header (unk_c5423: month, day, home,
# away, the number of records), the records of 11 bytes (1 goal, 2 penalty, 3 injury, 4 the goals
# and shots of a period) and the trailer of the running period (unk_c542e) that always ends the file
var gs_header := PackedByteArray([0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0])
var gs_records: Array = []
var gs_trailer := PackedByteArray([4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0])
var ref_infraction_slot: int = -1    # ref_infraction high word: the entity the call is about
var infraction_type_served: int = 0  # the infraction of the penalty being served (record_penalty)
var goal_flags: int = 1             # goal_flags of the last goal: 1 even, 2 short handed, 4 power play, 8 empty net
var music_queue: Array = []          # play_speech ids: the organ songs and jingles (KMS) of the music driver
var announcer_queue: Array = []      # sentences of the announcer (Speech.gd): clip names of XBRUCE2.VIV
var goal_call: Array = []            # goal_call: [team, scorer, assist 1, assist 2] until the goal is announced
var last_penalty_team := -1          # announce_time (dword_e9aac) >> 16: the team of the last penalty called
var sound_enabled := true            # sound_enabled
var sound_device: int = 8            # sound_card: a digital device (bits 0x2a) plays the fan clip
var half_announce := false           # misc_flags 0x80: the halfway line is still to come (periods 1 and 2)
var announce_time: int = -1          # announce_time (dword_e9aac): clock time of the late game line in the 3rd period
var scorer_jumps: int = 0            # scorer_jumps: the goal scorer's jumps in ai_celebrate_goal
# stop_flags
var faceoff_pending := false        # bit 0: faceoff set up, waiting for the drop
var whistle_ready := false          # bit 2
var shot_in_flight := false         # bit 4: a shot was taken (goalie_save / score bookkeeping)
var power_play := false             # bit 5: the teams have different numbers of skaters (update_power_play)
var power_play_team := 0            # bit 6: the team with more skaters (1 = away)
var offside_warning := false        # bit 7: a team mate is in the attacking zone before the puck (Lines.offside_warning_check)
var misc_first_touch := false       # misc_flags bit 4: first touch after the faceoff

var controls_blocked := false       # dword_ccc9c
var period: int = 0                 # period_idx (0 based)
var period_length: int = 300        # seconds on the clock at the start of a period (dword_e9ab6)
var period_lengths := PackedInt32Array([300, 600, 1200, 1200])   # word_cbc4a: by option_flags bits 10-11 (MatchSetup.period_length)
var period_num: int = 1              # _period_num: the period count (1 based, overtimes go on), -1 during the anthem
var clock_seconds: int = 300
var clock_sub: int = 0              # 24 sub ticks per second, decremented every step
var period_over: int = 0            # word period_over: 1 the period is over (end_period_flag), -1 after the intermission
var deferred := false               # dword_c5840: a deferred call is queued (the rest of the frame's steps wait)
var infraction_events := 0          # dword_cc0ac: the goalies (bit 0/1, away << 3) a frozen puck queued an event for
var stoppage_timer: int = -1
var whistle_timer: int = 0
var announce_timer: int = -1        # word_cc0b0
var box_count := [0, 0]            # penalized_count / byte_e9abb: players sitting in each penalty box
var last_sfx := -1                 # crowd_noise low word: the last play_sfx id (recorded by the replay)
var replay_disabled := false       # game_flags 0x10: nothing is recorded
var replay := Replay.new()
var crowd: Array = []              # crowd_figures: Crowd.Record x 20 (the figures around the ice and the benches)
var crowd_busy := PackedByteArray() # crowd_spots_busy: spots in use
var injury_stoppage := false       # injury_stoppage: a player was hurt; the faceoff follows without the referee's walk
var fade_in := false               # cut_to_scene: the view cuts (fades in) to the next scene
var penalty_box_mode := false      # penalty_box_mode (0xcbc44): a penalty is being handed out (no new calls)
var speech_busy := false           # speech_busy(): the announcer is talking (set by the audio layer)
var ref_phase: int = -1             # dword_c90d4: 0 = referee called, 1 = collecting, -1 = ready
var ref_infraction: int = 0         # dword_c90d6
var faceoff_x: int = 0              # dword_c90b2
var faceoff_y: int = 0
var faceoff_ready: Array = [0, 0]   # word_e038e / word_e0394: readiness of the two centres
var faceoff_side: Array = [0x8800, 0xa000]   # dword_e0392 / word_e0396
var faceoff_dir: Array = [-1, -1]   # word_c90b6 / word_c90b8: direction held by the users at the drop
var skip_wait := false              # dword_cc0f0: a user pressed a button during the pre faceoff wait
var infq := PackedByteArray()       # infraction_queue: 32 x [event, slot | 0x80 once its stoppage started] (Rules.inf_*)
var tick24: int = 0                 # byte_cc0d9: the steps to the next 24 step tick of sim_game_state
var tick_toggle: int = 0            # word_cc0d8: flips every 24 steps (the energy bar blinks)
var second_timer: int = 0           # dword_c90d0: the steps to the next second of play (update_line_timers)
var second_tick := false            # misc_flags 0x40: a second of play passed this step
var lc_bar := PackedInt32Array([0, 0])   # word_cbc52: the energy bar of a team changing on the fly blinks
var action_replay := false          # action_flags 0x80: no rule events (the replay)
var excitement_peak: int = 0        # word_e9aa4
var excitement_sum: int = 0         # dword_e009c
var excitement_samples: int = 0     # word_e9aa6
var last_touch_slot: int = -1       # dword_e9ac2
var last_touch_x: int = 0           # word_e9ac6
var last_touch_y: int = 0           # word_e9ac4
var last_passer: int = -1           # dword_c90a2
var last_shooter: int = -1          # word_c90a0
var pass_target: int = -1           # shot_power high word
var shot_power: int = 0             # shot_power low word
var pending_dir: int = 8            # pending_dir
var controller_type := PackedByteArray([8, 8])   # per user: 1 mouse, 2 / 4 joystick, 8 keyboard
# the line change prompt per team (start_line_change_ui, line_change_bench_step): shown (it
# blinks), the blink countdown, the place of the line offered (0..3), that line, the countdown to
# the next offer; team.line_change_ui is line_change_prompt
var lc_show := PackedInt32Array([0, 0])     # word_cbc56
var lc_blink := PackedInt32Array([0, 0])    # word_cbc5a
var lc_place := PackedInt32Array([0, 0])    # word_cbc5e
var lc_line := PackedInt32Array([0, 0])     # word_cbc62
var lc_timer := PackedInt32Array([0, 0])    # word_cbc66
# the scratch words of the original that some routines read as an earlier one left them:
# sim_update_players leaves the entity's vy (or its height step) in e03bc and its friction shift in
# e03ac before the AI handler runs, read_control_p1/p2 the control byte, the pressed and the
# changed buttons; ai_shoot aims with e03bc, ai_nearest_to_puck takes e03ac for a distance
var scratch_a: int = 0              # word e03bc
var scratch_b: int = 0              # word e03c0
var scratch_ac: int = 0xffffffff    # dword e03ac
var action_pass := false            # action_flags bit 2
var action_shot := false            # action_flags bit 3
var action_hold_camera := false     # action_flags bit 6
var one_timer := false              # dword_cc0f4
var breakaway := false              # dword_cc0f8
var defenders_ahead := 0            # dword_cc124
# ai_breakaway's lane (breakaway_pick_lane, breakaway_next_waypoint): the lane x and the y to skate
# to, the y from which the next waypoint is taken (-1: the last, shoot), the next waypoint, the
# side of the lane, the heading when the last waypoint was reached
var breakaway_lane_x := 0           # cc130
var breakaway_target_y := 0         # cc134
var breakaway_trigger_y := 0        # cc138
var breakaway_waypoint := 0         # cc13c
var breakaway_lane_side := 0        # cc140
var breakaway_heading := 0          # cc144
var icing_flags: int = 0            # dword_e9abe byte 2: 1 icing called, 2 direction, 4 candidate
var icing_shooter: int = -1
var goalie_pass_mode: int = 0         # goalie_pass_mode (word_c90aa): opponents near the carrier (carrier_scan_opponents)
var buttons_prev := [0, 0]           # the buttons (0x70) of each user at the last read (read_control_p1 / p2)
var last_controls := [8, 8]          # the control bytes of the last step (the steps of sim_tick outside the main loop)
var lineup_forwards := 0             # word_e9f12: the forwards of the lineup (count_dressed_players, lineup_pick_best)
var lineup_defence := 0              # word_e9f14: the defencemen of the lineup
var lineup_dressed := 0              # word_e9f16: both
var lineup_in_table := PackedInt32Array()   # unk_e9c24: 25 flags, the skaters in the line table (count_dressed_players)
var buttons_changed := 0             # scratch_e03ac: the buttons that went down or up since
var save_clip_shown := false       # dword_e9a9e low word: the SAVED clip was shown this period (no more save credits)
var stubs: Dictionary = {}          # golden tests: the routines replaced by a record of their calls (stubbed)
var stub_calls: Array = []
var goal_prediction: Array = [[0, -1], [0, -1]]   # unk_df812: [x, steps] per goal line (+y, -y)
var camera_x: int = 0
var camera_y: int = 0
var camera_target_x: int = 0
var camera_target_y: int = 0
var camera_offset_y: int = 0
var crowd_noise: int = 300
var excitement: int = 0
var step_count: int = 0
var sfx_queue: PackedInt32Array = PackedInt32Array()
var music_cues: Array = []         # play_sfx 0xaa on sound device 4 (kms_play)
var seed: int = 0xabcd4321           # random_seed: state of randomrange (demo_game reseeds it from rand(), init_match adds the team numbers)
var puck_in_net := false            # byte_c90ba
var bounced := false                # bounced_this_step: a net frame was hit (bounce_off_boards)
var scored_net := -1                # the net of the last score_goal call
var draw_list := PackedInt32Array()  # draw_order_slots: the 17 entities sorted by y (draw_order_list)
var draw_pos := PackedInt32Array()   # draw_order_pos: each entity's place in draw_list
var draw_keys := PackedInt32Array()  # draw_order_keys: the y each entity was last sorted by
# line changes (Lines.gd)
var req_roster: PackedInt32Array = PackedInt32Array([-1, -1, -1, -1, -1, -1])   # lineup_req_roster: lineup being assigned
var req_slot: PackedInt32Array = PackedInt32Array([0, 0, 0, 0, 0, 0])          # lineup_req_slot: its line slots
var line_hotkey_req: PackedInt32Array = PackedInt32Array([0, 0])   # word_e0304: an F1-F4 / F5-F8 request per team
var line_hotkey: PackedInt32Array = PackedInt32Array([0, 0])       # word_e0380: the line it asks for
# message box (word_cbec8 / panel_clip): index into Tables.message_strings, -1 none; the timer
# counts frames down to 0 and clears the message, 0 = stays until cleared
var message: int = -1
var message_timer: int = 0
## the puck's words +0x28 (frozen puck countdown) and +0x26 (the goal line prediction every 5 steps
## in play; before a faceoff the steps to the drop, the original's faceoff_timer 0xdff42)
var puck_stuck_timer: int:
	get: return Entity.to_s16((puck.want_dir & 0xff) | ((puck.dir_timer & 0xff) << 8))
	set(v):
		puck.want_dir = v & 0xff
		puck.dir_timer = Entity.to_s8(v >> 8)
var puck_goal_timer: int:
	get: return puck.timer_a
	set(v): puck.timer_a = Entity.to_s16(v)
var faceoff_timer: int:
	get: return puck.timer_a
	set(v): puck.timer_a = Entity.to_s16(v)
var faceoff_digit: int = 0          # word_e0398 faceoff_countdown_digit: 7, then 8, 9 in the last steps
var penalty_shot := false           # dword_cc128 penalty_shot_active: the shot is under way
var penalty_shot_phase := 0          # dword_cc118: 1 from the call until the shot ends
var penalty_shot_setup := false      # dword_cc11c: from the start of the shot until the next faceoff
var penalty_shot_slot := -1          # dword_cc0fc: the fouled player, who takes the shot
var penalty_shot_team := 0           # dword_cc104: 0 home, 1 away
var penalty_shot_user := -1          # dword_cc108: 1 when user 1 controlled the shooter, else -1
var penalty_shot_roster := -1        # dword_cc100
var penalty_shot_spot := Vector2i()  # dword_cc110 / penalty_shot_spot_y: faceoff spot after the shot
var penalty_shot_clock := 0          # dword_cc120: steps left for the shot (1000)
var penalty_shot_away := 0           # penalty_shot_timer (cc12c): steps the loose puck moved away from the net
var settings2: int = 0x7b           # byte_c5400 (option_flags + 1): bit 1 set = regular season game (normal penalty rate in penalty_odds, a tie after one overtime); clear = playoffs
var crowd_toggle := false            # crowd_hit_toggle: alternates the two crowd hit sounds
var injury_report: Array = []        # [team, roster, out for the game] of the last injury (announce_injury)
var ref_hits := 0                    # word_cbec2: body checks of a user on the referee (3 = game misconduct)
var last_impact := 0                 # word_e9b28: strength of the last collision between opponents

func _init() -> void:
	infq.resize(64)
	seed = 0xabcd4321
	teams.append(Team.new(0))
	teams.append(Team.new(1))
	for i in 17:
		var e := Entity.new()
		var init: Array = Tables.entity_init[i]
		e.slot = i
		e.set_pos(init[0], init[1])
		e.frame = init[3]
		e.side = init[4]
		e.half_w = init[5]
		e.half_h = init[6]
		e.state_stack[0] = init[7]
		e.flags = init[8]
		e.team = 0 if (i < 6 or i >= 12) else 1   # +0x6c / +0x70: the nets, the puck, its shadow and the referee point at the home team first
		if i < 12:
			e.line_slot = -1
			e.roster_idx = -1
		entities.append(e)
	puck = entities[Entity.Slot.PUCK]
	shadow = entities[Entity.Slot.SHADOW]
	referee = entities[Entity.Slot.REFEREE]
	puck.line_slot = 0
	shadow.line_slot = 0
	puck_stuck_timer = 0x78
	# entities_init: the draw order starts as the slots, then sorted
	draw_list.resize(17)
	draw_pos.resize(17)
	draw_keys.resize(17)
	for i in 17:
		draw_list[i] = i
		draw_pos[i] = i
	sort_draw_order()
	# the nets are bodies with a velocity too (a skater may knock one off its pegs, net_push_off)
	entities[Entity.Slot.NET_TOP].line_slot = 0
	entities[Entity.Slot.NET_BOTTOM].line_slot = 0
	teams[0].attacks_up = true
	teams[1].attacks_up = false
	teams[0].goalie_slot = 0
	teams[1].goalie_slot = 6
	new_game()

## begin_game_session (0x1befd) and play_match_from_start (0x13e8f) up to the anthem: the player
## statistics and the summary of a new game, the candidate lists (build_lines) and the line tables
## checked for missing players (count_dressed_players); the match
## globals reset (reset_game_state: the first period set up). With the anthem init_match follows
## (Ceremonies.begin_anthem), the match starts when it is over (MatchSetup.start_match); without it
## the match starts at once
func new_game(anthem: bool = false) -> void:
	period_num = -1
	for t in 2:
		var team := teams[t]
		team.info = team_info[t]
		team.reset_stats()
		team.goalie_menu = PackedByteArray([1, 2, 2])
	summary_init(0, 0)
	Lines.build_lines(self)
	Lines.count_dressed_players(self, 0)
	Lines.count_dressed_players(self, 1)
	period = -1
	crowd_noise = 0
	skip_wait = false
	MatchSetup.reset_game_state(self)
	crowd_noise = 0
	if not anthem:
		MatchSetup.start_match(self)

## the length of the periods for the period setting of option_flags (word_cbc4a; demo_game makes
## its periods a minute long this way)
func set_period_length(seconds: int) -> void:
	period_lengths[(settings2 >> 2) & 3] = seconds

## sim_tick (0x5c1c4) outside the main loop (period_init, init_match, three_stars_sequence): a
## step of the simulation with the controls as they were last read
func sim_tick() -> void:
	Rules.sim_game_state(self)
	sim_update_players(last_controls[0], last_controls[1])
	update_camera()
	replay.record(self)

## gsummary_init (0x1aed0..): a new summary for the date of the game
func summary_init(month: int, day: int) -> void:
	gs_header = PackedByteArray([0, month, day, team_info[0].index if team_info[0] != null else 0,
		team_info[1].index if team_info[1] != null else 1, 1, 0, 0, 0, 0, 0])
	gs_records.clear()
	gs_trailer = PackedByteArray([4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0])

## gsummary_flush (0x61b85, at the faceoff): the events of the stoppage go into the summary (the
## port appends them as they happen; a hook) and the list of the events starts again
func summary_flush() -> void:
	if stubbed("gsummary_flush", []):
		return
	event_log.clear()

## center_mouse (0x50ade, at the faceoff): the mouse pointer back to the centre (a hook)
func center_mouse() -> void:
	stubbed("center_mouse", [])

## gsummary_append_record: an event of the game (the trailer stays the last record)
func summary_append(rec: PackedByteArray) -> void:
	rec.resize(11)
	gs_records.append(rec)

## gsummary_write_final after the intermission: the trailer of the period stays, a new one starts
func summary_close_period() -> void:
	gs_records.append(gs_trailer)
	gs_trailer = PackedByteArray([4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0])

## GSUMMARY.DB as the original writes it: the header, the records, the trailer
func summary_bytes() -> PackedByteArray:
	var n := gs_records.size() + 1
	gs_header[5] = n & 0xff
	gs_header[6] = n >> 8
	var out := gs_header.duplicate()
	for r: PackedByteArray in gs_records:
		out.append_array(r)
	out.append_array(gs_trailer)
	return out

## the records of a summary (GSUMMARY.DB) after its header, the trailer included
static func summary_records(data: PackedByteArray) -> Array:
	var out: Array = []
	var n := data.decode_u16(5) if data.size() >= 11 else 0
	var at := 11
	for i in n:
		if at + 11 > data.size():
			break
		out.append(data.slice(at, at + 11))
		at += 11
	return out

## the users take their skaters for a faceoff (switch_to_nearest from ai_puck_faceoff2): the
## skater nearest to the puck, which is the centre; a second user on the same team takes the
## nearest of the others
func assign_users() -> void:
	user1_slot = -1
	user2_slot = -1
	for i in 12:
		entities[i].flags &= ~Entity.F_USER
	if user1_team != 0:
		user1_slot = find_switch_target(centre_slot(user1_team - 1), -1)
	if user2_team != 0:
		var c := centre_slot(user2_team - 1)
		if c == user1_slot:
			c = nearest_free_skater(user2_team - 1, user1_slot)
		user2_slot = find_switch_target(c, -1)

## the selectable skater of team t nearest to the puck, other than `exclude`
func nearest_free_skater(t: int, exclude: int) -> int:
	var best := -1
	var best_d := 0x7fffffff
	for i in 6:
		var p := entities[teams[t].first_slot + i]
		if p.line_slot <= 0 or p.slot == exclude or (p.flags2 & Entity.F2_UNSELECTABLE) or (p.flags & Entity.F_BUSY):
			continue
		var dx := puck.xi - p.xi
		var dy := puck.yi - p.yi
		var d := dx * dx + dy * dy
		if d <= best_d:
			best_d = d
			best = p.slot
	return best

## the entity of the centre (line slot 4) of a team, or its first skater
func centre_slot(t: int) -> int:
	var first := teams[t].first_slot
	for i in 6:
		if entities[first + i].line_slot == 4:
			return first + i
	for i in 6:
		if entities[first + i].line_slot > 0:
			return first + i
	return first + 1

## 1 home, 2 away: is the team controlled by a user
func is_user_team(t: int) -> bool:
	return user1_team == t + 1 or user2_team == t + 1

## word_cbec8 / panel_clip: shows a message of Tables.message_strings (0 = until cleared)
func show_message(idx: int, frames: int) -> void:
	message = idx
	message_timer = frames

## Selects the teams from the databases (Database.load_team); call before the first step
## the teams of the match (db_load_team_roster): the status byte of each player's record, 3 (to be
## dressed) for the players of the roster, 0 for the empty places, 2 for the players scratched in
## the line editor before the game (`scratches`: per team the roster indices); then a new game
func set_teams(home: Database.TeamInfo, away: Database.TeamInfo, scratches: Dictionary = {}, anthem: bool = false) -> void:
	team_info = [home, away]
	for t in 2:
		var team := teams[t]
		team.info = team_info[t]
		team_ids[t] = team_info[t].index if team_info[t] != null else t
		for r in 28:
			team.roster_status[r] = 3 if Lines.roster_exists(team, r) else 0
		for r in scratches.get(t, []):
			team.roster_status[r] = 2
	new_game(anthem)

## put_player_on_ice (0x5b2c5): the entity takes roster player `roster`. From the bench he skates
## out (EXIT_BENCH), from the box he leaves it (EXIT_PENALTY_BOX); his place is the ice (entity_of
## -1, status byte 4). His number and ratings come from the player records (skaters: player_ratings,
## 0x14 bytes; goalies: 0x10 bytes from +0xe2, the tenth unused, +0x60 kept), adjusted for a skater
## by the team factors of TEAMS.DB (+0x2dc..+0x2df, Database.TeamInfo.factors): short handed and
## power play, at home or away, and 2 late in the game (overtime, or the second half of the third
## period) unless his team leads. Right handed players are drawn mirrored.
func put_player_on_ice(e: Entity, roster: int) -> void:
	if stubbed("put_player_on_ice", [e.slot, roster & 0xffff]):
		return
	e.flags2 &= ~Entity.F2_HOOKED
	var team := teams[1] if e.slot >= 6 else teams[0]
	var r := Entity.to_s16(roster)
	e.roster_idx = Entity.to_s8(r)
	scratch_b = team.entity_of[r]
	if scratch_b >= 0 or scratch_b == -2:
		e.set_state_reset(Entity.State.EXIT_PENALTY_BOX if scratch_b >= 0 else Entity.State.EXIT_BENCH)
		e.flags &= ~Entity.F_BUSY
		e.anim = 0
	team.entity_of[r] = -1
	team.roster_status[r] = 4
	var f := PackedByteArray([7, 7, 7, 3])
	if team.info != null and team.info.factors.size() == 4:
		f = team.info.factors
	var sh := 0
	var home := 0
	var late := 0
	var pp := 0
	var away := (e.flags & Entity.F_PLAYER2) != 0
	if e.line_slot != 0:
		if power_play:
			if away != (power_play_team == 1):
				sh = _factor(f[0]) - 2
			else:
				pp = _factor(f[1])
		home = _factor(f[3]) - 2 if away else _factor(f[2])
		if period > 2 or (period == 2 and clock_seconds < (period_length >> 1)):
			var d := Entity.to_s16(teams[0].goals - teams[1].goals)
			if d == 0 or (d > 0) == away:
				late = 2
	e.pass_target = 0
	e.timer_f = 0
	e.timer_e = 0
	e.pass_ok = 0
	e.energy = team.energy[r] if r >= 0 and r < 28 else 0x1000
	if team.info == null:
		_default_skills(e)
		return
	var p: Database.Player = team.info.player(r)
	var g := PackedByteArray()
	g.resize(0x14)
	if p != null:
		for i in mini(p.ratings.size(), 0x14):
			g[i] = p.ratings[i]
	e.number = p.number if p != null else 0
	e.left_handed = g[0]
	e.flags4 &= ~Entity.F4_MIRROR
	if g[0] == 0:
		e.flags4 |= Entity.F4_MIRROR
	if r < 0x19:
		e.stamina = g[1] - mini(g[1], 3)
		e.speed_skill = g[2] - mini(g[2], 3)
		e.weight = g[3]
		e.shot_skill = g[4]
		e.aggression = _clamp15(g[5] + late)
		e.goalie_skill = _clamp15(g[6] + pp + sh + home)
		e.shot_accuracy = _clamp15(g[7] + pp + sh + home)
		e.pass_skill = _clamp15(g[9] + pp + home)
		e.reaction = ((_clamp15(g[10] + pp + sh + home + late) ^ 0xf) + 0xf) >> 1
		e.awareness = ((_clamp15(g[11] + home) ^ 0xf) + 0xf) >> 1
		e.check_skill = g[12]
		e.endurance = g[13]
		e.offense = _clamp15(g[14] + late + late)
	else:
		e.check_skill = g[1]
		e.pass_skill = g[2]
		e.offense = g[3]
		e.endurance = g[4]
		e.shot_skill = g[5]
		e.stamina = g[6] - mini(g[6], 3)
		e.speed_skill = g[7] - mini(g[7], 3)
		e.weight = g[8]
		e.reaction = ((_clamp15(g[10] + pp + sh + home + late) ^ 0xf) + 0xf) >> 1
		e.awareness = ((_clamp15(g[11] + home) ^ 0xf) + 0xf) >> 1

static func _clamp15(v: int) -> int:
	return clampi(Entity.to_s16(v), 0, 15)

static func _factor(v: int) -> int:
	return 0 if v < 4 else (1 if v < 7 else 2)

## default ratings in the 0..15 scale of the player database (put_player_on_ice would read them)
func _default_skills(e: Entity) -> void:
	e.weight = 8 + (e.slot % 3)
	e.speed_skill = 9 if e.roster_idx < 25 else 5
	e.stamina = 8
	e.reaction = 6
	e.awareness = 7
	e.shot_skill = 8
	e.shot_accuracy = 7
	e.pass_skill = 8
	e.offense = 7
	e.goalie_skill = 9
	e.endurance = 8
	e.check_skill = 7
	e.aggression = 6
	e.left_handed = 1 if (e.slot % 4) == 1 else 0
	e.flags4 = Entity.F4_MIRROR if e.left_handed else 0
	e.number = 10 + e.roster_idx if e.roster_idx >= 0 else 10 + e.slot

## pick_player_for_position (0x655cc, Lines.pick_player_for_position): the line table of a team
## that lost a player for the game (game misconduct, injury) is rebuilt around him
func pick_player_for_position(team: int, roster: int) -> void:
	if stubbed("pick_player_for_position", [team, roster]):
		return
	Lines.pick_player_for_position(self, team, roster)

func team_of(e: Entity) -> Team:
	return teams[e.team]

## the team record an entity points at (+0x6c): the puck, the nets, the shadow and the referee
## point at the home team's
func team_record(e: Entity) -> Team:
	return teams[0] if e.slot >= 12 else teams[e.team]

func opponents_of(e: Entity) -> Team:
	return teams[1 - e.team]

func same_team(a: int, b: int) -> bool:
	return (a < 6) == (b < 6)

func carrier() -> Entity:
	return entities[puck_carrier] if puck_carrier >= 0 else null

## randomrange (0x8c230): seed = seed * 0xBB40E62D + 1 (mod 2^32), computed in 16 bit halves as the
## original does; the result is bits 8..23 of the new seed scaled to 0 .. n-1 (n is a 16 bit word)
func random(n: int) -> int:
	var lo := seed & 0xffff
	var hi := (seed >> 16) & 0xffff
	var mid := (hi * 0xe62d + lo * 0xbb40) & 0xffff
	seed = (lo * 0xe62d + (mid << 16) + 1) & 0xffffffff
	return ((((seed >> 8) & 0xffff) * (n & 0xffff)) >> 16)

## play_sfx (0x59884): remembers the id for the replay; while the announcer talks only the goal
## horn plays; the digital devices 4 and 8 leave out 0xa0 / 0xa1; 0x7d is a cheer of the crowd;
## the end of period horn 0x90 plays sample 0x91 (device 4: both)
func play_sfx(id: int) -> void:
	if stubbed("play_sfx", [id]):
		return
	last_sfx = id
	if speech_busy and not (id == 0x9c and not replay_disabled):
		return
	if (sound_device == 8 or sound_device == 4) and (id == 0xa0 or id == 0xa1):
		return
	if id == 0x7d:
		crowd_noise += 500
		return
	if sound_device == 4 and id == 0xaa:
		music_cues.append(id)
		return
	if id == 0x90:
		if sound_device == 4:
			sfx_queue.append(0x90)
		id = 0x91
	sfx_queue.append(id)

## the crowd figures for the replay frame (10 frame counter bytes, 20 spot bytes)
func effect_record_bytes() -> PackedByteArray:
	if crowd.size() < Crowd.RECORDS:
		Crowd.reset(self)
	return Crowd.record_bytes(self)

## golden tests (tests/run_tests.gd): the routines the emulator replaces by a record of their calls
## (tools/nhl/golden.py stubs) do the same here: stubbed(name, args) records the call and is true
func stubbed(name: String, args: Array) -> bool:
	if not stubs.has(name):
		return false
	stub_calls.append([name] + args)
	return true

func add_crowd(amount: int, cap: int) -> void:
	if crowd_noise < cap + 1:
		crowd_noise = mini(crowd_noise + amount, cap)

# --------------------------------------------------------------------------------------------
# main step (sim_tick -> sim_game_state, sim_update_players, update_camera)
# --------------------------------------------------------------------------------------------

## control_p1/control_p2: control bytes (bits 0-3 direction, 8 none, 9 stop, 0x10 A, 0x20 B, 0x40 C)
## pressed_p1/pressed_p2: the button bits that went down with this sample
func step(control_p1: int, control_p2: int, pressed_p1: int, pressed_p2: int) -> void:
	step_count += 1
	last_controls = [control_p1, control_p2]
	deferred = false            # game_loop ran the deferred calls (empty ones in this build)
	# match_sequence / three_stars_sequence: sequence_loop runs the steps of the sequence until
	# sequence_steps ran out (a button skips the anthem); then the match starts or is finished
	if intro or stars_running:
		if intro and ((pressed_p1 | pressed_p2) & 0x30) != 0:
			sequence_steps = 0
		if sequence_steps == 0:
			if intro:
				Ceremonies.end_anthem(self)
			else:
				Ceremonies.end_three_stars(self)
				return
		else:
			run_sim_step(control_p1, control_p2)
			replay.record(self)
			sequence_steps = maxi(0, sequence_steps - 1)
			return
	if finished:
		return
	run_sim_step(control_p1, control_p2)
	replay.record(self)
	# game_loop: a period over (end_period_flag, ai_ref_pickup_puck) ends after this frame
	# (end_of_period: the intermission, the next period); then the line hotkeys and the period flag
	# are cleared, and a game over starts the three stars (three_stars_sequence)
	if period_over != 0 and not stars_running and not finished:
		Rules.end_of_period(self)
		line_hotkey_req[1] = 0
		line_hotkey_req[0] = 0
		deferred = false
		period_over = 0
		if match_over:
			summary_flush()
			Ceremonies.begin_three_stars(self)
			if not stars_running:
				finished = true
		else:
			InfoPanel.music(self, 0)

## a step of run_sim_steps (0x1149a): the clock while play is on (game_clock_tick), then sim_tick
## (0x5c1c4): sim_game_state, sim_update_players and update_camera (the replay frame is recorded
## by the caller); the controls are the bytes read_control_p1 / read_control_p2 read
func run_sim_step(control_p1: int, control_p2: int) -> void:
	if not play_stopped:
		Rules.game_clock_tick(self)
	Rules.sim_game_state(self)
	sim_update_players(control_p1, control_p2)
	update_camera()

## draw_sprites (0x5ce12), every drawn frame: the message box counts its frames down and closes
func message_frame() -> void:
	if message != -1 and message_timer > 0:
		message_timer -= 1
		if message_timer <= 0:
			message_timer = 0
			message = -1

## sim_update_players (0x5c40f), every step after sim_game_state: whether the users may move
## (controls_blocked), the distances to the puck, then for every record on the ice (the referee
## always): the previous position, the animation, the pick-up and second timers, the goalie's
## time on the ice, friction, gravity and the move, the user's controls (control_player), the AI
## state, the goalie kept out of the posts, the collisions (move_entity) and the hit strength
## fading; finally the carried puck is kept inside the boards and in front of the end boards
func sim_update_players(control_p1: int = 8, control_p2: int = 8) -> void:
	var rstate := referee.state()
	var blocked := false
	if play_stopped:
		if intermission_camera:
			blocked = true
		elif not faceoff_pending and stoppage_timer < 0 and Rules.inf_type(self, 0) == 0 \
				and rstate != Entity.State.REF_CALL_PENALTY and rstate != Entity.State.REF_POINT_GOAL:
			blocked = clip == 2 or clip == 0 or panel < 0 or panel >= 0x100
	controls_blocked = blocked
	update_puck_distances()
	for i in 17:
		var e := entities[i]
		e.prev_x = e.x
		e.prev_y = e.y
		e.prev_z = e.z
		if e.line_slot < 0 and e.slot != Entity.Slot.REFEREE:
			e.speed_prev = e.speed
			continue
		var team: Team = teams[e.team] if e.slot < 12 else null
		if team != null and e.roster_idx >= 0 and e.roster_idx < 28:
			e.energy = team.energy[e.roster_idx]      # the energy lives in the team record (+0x46)
		Anim.advance(e, self)
		e.timer_c = Entity.to_s16(e.timer_c - 1)
		if e.timer_c < 0:
			e.timer_c = 0
		e.timer_d = Entity.to_s16(e.timer_d - 1)
		if e.timer_d < 0:
			e.timer_d = 0
		# the goalie's time on the ice (the second tick of sim_game_state)
		var r := Entity.to_s8(e.roster_idx)
		if e.slot != Entity.Slot.REFEREE and second_tick and r >= 0 and e.line_slot == 0 and r >= 0x19 and r < 0x1c \
				and not no_stats:
			teams[e.team].goalie_stats[r - 0x19][0] += 1
		integrate(e)
		if e.slot == user1_slot:
			buttons_changed = (control_p1 & 0x70) ^ buttons_prev[0]    # read_control_p1
			buttons_prev[0] = control_p1 & 0x70
			_read_control_scratch(control_p1)
			control_player(e, 0)
		elif e.slot == user2_slot:
			buttons_changed = (control_p2 & 0x70) ^ buttons_prev[1]
			buttons_prev[1] = control_p2 & 0x70
			_read_control_scratch(control_p2)
			control_player(e, 2)
		if e.state() != Entity.State.NONE:
			AI.dispatch(self, e)
		clamp_goalie_to_crease(e)
		e.push_x = 0
		e.push_y = 0
		if e.xi != e.prev_x >> 16 or e.yi != e.prev_y >> 16 or e.slot == Entity.Slot.PUCK:
			move_entity(e)
		e.speed = Entity.to_s16(e.speed - 2)
		if e.speed < 0:
			e.speed = 0
		e.speed_prev = e.speed
		if team != null and e.roster_idx >= 0 and e.roster_idx < 28:
			team.energy[e.roster_idx] = e.energy
	# the carrier cannot drag the puck through the boards or behind the goal line
	if puck.zi < 0x18 and absi(puck.xi) > 0xa0 and puck_carrier >= 0:
		puck.x = ((-0xa0 if puck.xi < 0 else 0xa0) << 16) | (puck.x & 0xffff)
		puck.frame = 0x18a
	if puck.zi <= 0 and puck_carrier >= 0 and (puck.yi < -0x104 or puck.yi > 0x108):
		puck.y = ((-0x104 if puck.yi < 0 else 0x108) << 16) | (puck.y & 0xffff)
		puck.frame = 0x18a

## the first loop of sim_update_players: distance, direction and squared quarter distance of
## every player to the puck; the goalie on the ice and the skater nearest to the puck (by the
## squared distance, not busy or unselectable) of each team
func update_puck_distances() -> void:
	for t in 2:
		teams[t].goalie_slot = -1        # word_df70e / word_df80e: no goalie until one is found
		teams[t].nearest_dist = 0xffff
		teams[t].nearest_slot = -1
	for i in 12:
		var e := entities[i]
		var dx := puck.xi - e.xi
		var dy := puck.yi - e.yi
		e.puck_dist = approx_distance(dx, dy)
		e.puck_dir = Tables.direction8(Entity.to_s16(dx), Entity.to_s16(dy))
		var qx := dx >> 2
		var qy := dy >> 2
		e.puck_dist_sq = Entity.to_s16(qx * qx + qy * qy)
		var team := teams[e.team]
		if e.line_slot == 0:
			team.goalie_slot = i
		elif e.line_slot > 0 and (e.flags2 & Entity.F2_UNSELECTABLE) == 0 and (e.flags & Entity.F_BUSY) == 0:
			if e.puck_dist_sq < team.nearest_dist:
				team.nearest_dist = e.puck_dist_sq
				team.nearest_slot = i

## friction, speed clamp, gravity and the position update of sim_update_players
func integrate(e: Entity) -> void:
	if e.anim == 0xa0b or (e.anim >= 0xf0f and e.anim <= 0x1055):
		return    # falling / lying animations move the entity through frame_offsets instead
	if e.zi == 0:
		var shift := 9 if (e.flags & 1) else 6
		scratch_ac = shift
		if e.vx != 0:
			var d := e.vx >> shift
			if d == 0:
				d = 1 if e.vx > 0 else -1
			e.vx -= d
			if e.slot < 12 and absi(e.vx) > MAX_SPEED:
				e.vx = MAX_SPEED if e.vx > 0 else -MAX_SPEED
		if e.vy != 0:
			var d := e.vy >> shift
			if d == 0:
				d = 1 if e.vy > 0 else -1
			e.vy -= d
			if e.slot < 12 and absi(e.vy) > MAX_SPEED:
				e.vy = MAX_SPEED if e.vy > 0 else -MAX_SPEED
	if e.vx != 0:
		e.x += STEP_DT * e.vx
	if e.vy != 0:
		e.y += STEP_DT * e.vy
	scratch_a = _s16(e.vy)
	if e.zi >= 0 and (e.zi != 0 or e.vz != 0):
		e.vz = _s16(e.vz - GRAVITY)
		scratch_a = _s16(STEP_DT * e.vz)
		var nz := e.z + STEP_DT * e.vz
		if nz < 0:
			e.z = 0
			e.vz = _s16(-e.vz) >> 1
			scratch_a = maxi(0, 5 - Entity.to_s8(e.vz >> 8))
			if scratch_a <= 3:
				play_sfx(0xab)   # the bounce of a dropping puck
		else:
			e.z = nz

## what read_control_p1/p2 leave in the scratch words: the control byte, the buttons that went
## down, the buttons that changed
func _read_control_scratch(control: int) -> void:
	scratch_a = control & 0xff
	scratch_b = control & 0x70 & buttons_changed
	scratch_ac = (scratch_ac & 0xffff0000) | buttons_changed

## sim_update_players: a goalie without the puck is kept out of the net posts area
func clamp_goalie_to_crease(e: Entity) -> void:
	if e.slot >= 12 or play_stopped or e.line_slot != 0 or puck_carrier == e.slot or (e.flags3 & 1):
		return
	var px := e.xi
	if px < -0x2b:
		if px > -0x32:
			e.x = (e.x & 0xffff) - (0x2b << 16)
			e.vx = 0
	elif px > 0x2b and px < 0x31:
		e.x = (0x2b << 16) | (e.x & 0xffff)
		e.vx = 0
	var py := e.yi
	if py < 0:
		if py > -0xc6 and py < -0xc0:
			e.y = (e.y & 0xffff) - (0xc6 << 16)
			e.vy = 0
	elif py > 0xc0 and py < 0xc6:
		e.y = (0xc6 << 16) | (e.y & 0xffff)
		e.vy = 0

# --------------------------------------------------------------------------------------------
# controls (control_player, apply_skating, skating_turn, skating_accelerate, stop_skating, brake)
# --------------------------------------------------------------------------------------------

## control_player (0x504da): the user's player `e` (user `player`, 0 / 1) for one step. The inputs
## are in the scratch words as read_control leaves them: e03bc the control byte (direction 0-7, 8
## none, buttons 0x10 A, 0x20 B, 0x40 C), e03c0 the buttons pressed this step, e03ac the buttons
## that changed. A line hotkey (F1-F8) changes lines (with both users on one team user 1's only);
## at a faceoff the user times the drop; with the line change prompt open the prompt runs; while
## the puck waits to be dropped a button skips the wait. A busy player can still switch (A) or aim
## a one timer; the carrier passes (A, released or aimed), shoots (B), opens the prompt (C); without
## the puck A switches, B checks or takes over a pass on its way for a one timer, C hooks.
func control_player(e: Entity, player: int) -> void:
	var t := 1 if e.flags & Entity.F_PLAYER2 else 0
	if (penalty_shot_phase != 0 or penalty_shot) and play_stopped:
		return
	if line_hotkey_req[t] != 0 and not penalty_shot and (user1_team != user2_team or e.slot == user1_slot):
		if not play_stopped or (e.flags2 & Entity.F2_LINE_CHANGE):
			if Lines.request_line_change(self, e, line_hotkey[t]):
				lc_show[t] = 0
				teams[t].line_change_ui = false
		line_hotkey_req[t] = 0
	if faceoff_pending:
		faceoff_control(e)
		return
	if e.flags2 & Entity.F2_LINE_CHANGE:
		Lines.line_change_bench_step(self, e)
		return
	if puck.state() == Entity.State.PUCK_FACEOFF2 and penalty_shot_phase == 0:
		if scratch_b & 0x30:
			skip_wait = true
		return
	if (e.flags & Entity.F_USER) == 0:
		return
	if e.flags & Entity.F_BUSY:
		if Entity.to_s8(puck_carrier) == e.slot or controls_blocked:
			return
		if scratch_b & 0x10:
			switch_to_nearest(e, player)
			return
		if pass_target == e.slot:
			if one_timer:
				pending_dir = scratch_a & 0xf
			return
		if Entity.to_s8(puck_carrier) >= 0 or (scratch_b & 0x20) == 0 or pass_target < 0:
			return
		var pt := entities[pass_target]
		if pt.line_slot <= 0:
			return
		_take_one_timer(e, pt)
		return
	if Entity.to_s8(puck_carrier) == e.slot:
		Lines.offside_warning_check(self, e)
		if e.line_slot == 0 and (e.flags2 & Entity.F2_TURNING):
			return
		if action_pass:
			PuckLogic.pass_button(self, e)
			return
		if action_shot:
			PuckLogic.shot_control(self, e, scratch_a, scratch_b, scratch_ac & 0xffff)
			return
		if scratch_b & 0x10:
			# shoot_button (0x551af): the pass is aimed where he faces until A is released
			pending_dir = e.facing & 7
			action_pass = true
			return
		if (scratch_b & 0x40) and not penalty_shot:
			Lines.request_line_change_button(self, e)
			return
		if e.line_slot == 0:
			return
		if scratch_b & 0x20:
			PuckLogic.start_shot(self, e)
			return
		apply_skating(e, scratch_a)
		return
	if controls_blocked:
		return
	if scratch_b & 0x40:
		PuckLogic.hook_button(self, e, player)
		return
	if scratch_b & 0x10:
		switch_to_nearest(e, player)
		return
	if e.line_slot == 0:
		return
	if e.slot == pass_target:
		if scratch_b & 0x20:
			PuckLogic.body_check(self, e)
		if one_timer:
			pending_dir = scratch_a & 0xf
			return
		if scratch_b & 0x10:
			switch_to_nearest(e, player)
			return
		if controls_blocked:
			return
		apply_skating(e, scratch_a)
		return
	if Entity.to_s8(puck_carrier) < 0 and (scratch_b & 0x20) and pass_target >= 0:
		if _take_one_timer(e, entities[pass_target]):
			return
	if scratch_b & 0x20:
		PuckLogic.body_check(self, e)
		return
	if controls_blocked:
		return
	apply_skating(e, scratch_a)

## the one timer of control_player: the user takes over the team mate the pass goes to (not
## another user's, nor one who cannot be selected); he shoots as soon as it arrives
func _take_one_timer(e: Entity, pt: Entity) -> bool:
	if (e.slot < 6) != (pt.slot < 6) or (pt.flags & Entity.F_USER) or (pt.flags2 & Entity.F2_UNSELECTABLE):
		return false
	if e.slot == user1_slot:
		if pt.slot != user1_slot:
			user1_slot = find_switch_target(pt.slot, user1_slot)
	elif pt.slot != user2_slot:
		user2_slot = find_switch_target(pt.slot, user2_slot)
	one_timer = true
	return true

## faceoff_control (0x4ff0d): at the dot the users time the drop: the direction they hold is kept
## for faceoff_resolve (the attacking-up side's in the second word); A commits: too early (before
## 0x11 steps of the countdown are left) he swings and misses
func faceoff_control(e: Entity) -> void:
	if e.state() != Entity.State.FACEOFF:
		return
	if e.flags & Entity.F_ATTACK_UP:
		faceoff_dir[1] = Entity.to_s16(scratch_a)
	else:
		faceoff_dir[0] = Entity.to_s16(scratch_a)
	if e.flags2 & Entity.F2_TURNING:
		return
	if (scratch_b & 0x10) == 0:
		e.timer_b = Entity.to_s16(e.timer_b - 1)
		if e.timer_b < 0:
			Anim.set_animation(e, 0x7f1)
		return
	e.flags2 |= Entity.F2_TURNING
	if faceoff_timer < 0x11:
		e.flags |= Entity.F_BUSY
		Anim.set_animation(e, 0x7dd)
	else:
		Anim.set_animation(e, 0xd05)
	e.timer_b = -1

func apply_skating(e: Entity, dir: int) -> void:
	if e.line_slot == 0:
		goalie_move(e, dir)
		return
	dir &= 0xf
	# animation without movement input: glide (one frame per direction)
	var idle_anim := Anim.GLIDE
	if e.flags & Entity.F_BACKWARDS:
		idle_anim = Anim.GLIDE_BACK
	elif e.slot == Entity.Slot.REFEREE:
		idle_anim = Anim.REF_GLIDE_ARM if ref_arm_up() else Anim.REF_GLIDE
	if dir >= 8:
		if dir == 9 and (e.vx != 0 or e.vy != 0):
			stop_skating(e)
			return
		if (e.flags2 & Entity.F2_TURNING) == 0:
			Anim.set_animation(e, idle_anim)
		return
	# skating backwards: a defender facing the carrier keeps his facing and skates away
	if puck_carrier != e.slot:
		var dx := puck.xi - e.xi
		var dy := puck.yi + (puck.vy >> 8) - e.yi
		var d := dir
		var py := e.yi
		if (e.flags & Entity.F_ATTACK_UP) == 0:
			dx = -dx
			dy = -dy
			py = -py
			d ^= 4
		var toward_puck := Tables.direction8(dx, dy)
		var cond_a := (e.flags & Entity.F_BACKWARDS) != 0 or (py < 0 and d == 4 and ((toward_puck + 1) & 7) < 3)
		var cond_b := (e.flags & Entity.F_BACKWARDS) == 0 or ((((d - 3) & 7) < 3) and ((toward_puck + 2) & 7) < 5)
		if cond_a and cond_b:
			if (e.flags & Entity.F_BACKWARDS) == 0 and e.slot != Entity.Slot.REFEREE and not play_stopped:
				var moving := (e.vx != 0 or e.vy != 0)
				var vdir := Tables.direction8(e.vx, e.vy)
				if not moving or ((vdir - dir + 1) & 7) < 3:
					e.flags |= Entity.F_BACKWARDS
		else:
			e.flags &= ~Entity.F_BACKWARDS
	else:
		e.flags &= ~Entity.F_BACKWARDS
	var turn := (dir - e.facing) & 7
	var tt := Tables.turn_table[turn]
	if tt != 0:
		var sp := (e.vx * e.vx + e.vy * e.vy) >> 16
		var rate := 0x300 - sp
		if rate < 0x180:
			rate = 0x180
		var dh := rate * tt
		if e.flags & Entity.F_BACKWARDS:
			dh = -dh
		e.heading += dh
		e.heading &= 0x7ffff
		if sp > 0x14:
			var right := ((e.flags4 & Entity.F4_MIRROR) != 0) == (tt < 0)
			if e.slot == Entity.Slot.REFEREE:
				if ref_arm_up():
					Anim.set_animation(e, Anim.REF_TURN_R_ARM if right else Anim.REF_TURN_L_ARM)
				else:
					Anim.set_animation(e, Anim.REF_TURN_R if right else Anim.REF_TURN_L)
			else:
				Anim.set_animation(e, Anim.TURN_R if right else Anim.TURN_L)
			e.flags2 |= Entity.F2_TURNING
		else:
			Anim.set_animation(e, idle_anim)
		if sp > 2:
			var accel_dir := e.facing ^ 4 if (e.flags & Entity.F_BACKWARDS) else e.facing
			skating_accelerate(e, accel_dir)
		return
	skating_turn(e, turn)

## skating_turn (0x5f98a): turn is the input direction relative to the facing (0 or 4 here, the
## other turns steer in apply_skating). Facing the input (or facing away from it when skating
## backwards) the skater accelerates; otherwise he brakes while still moving towards his facing
## and then turns around one step at a time.
func skating_turn(e: Entity, turn: int) -> void:
	var back := (e.flags & Entity.F_BACKWARDS) != 0
	var k := 2
	if back:
		turn ^= 4
		k = 6
	if turn != 0:
		var vdir := Tables.direction8(e.vx, e.vy)     # 8 when standing
		scratch_a = vdir
		if (vdir & 8) == 0:
			scratch_a = (vdir - (heading_word(e)) + k) & 7
			if scratch_a < 4:
				stop_skating(e)
				return
		if (e.flags4 & Entity.F4_MIRROR) == 0:
			e.facing = e.facing + 1
		else:
			e.facing = e.facing - 1
		var g := Anim.GLIDE
		if back:
			g = Anim.GLIDE_BACK
		elif e.slot == Entity.Slot.REFEREE:
			g = Anim.REF_GLIDE_ARM if ref_arm_up() else Anim.REF_GLIDE
		Anim.set_animation(e, g)
		return
	var a := Anim.SKATE
	if back:
		a = Anim.SKATE_BACK
	elif e.slot == Entity.Slot.REFEREE:
		a = Anim.REF_SKATE_ARM if ref_arm_up() else Anim.REF_SKATE
	elif puck_carrier == e.slot:
		a = Anim.SKATE_CARRIER
	elif e.flags2 & Entity.F2_HOOKED:
		a = Anim.SKATE_HOOKED
	if (e.flags2 & Entity.F2_TURNING) == 0:
		Anim.set_animation(e, a)
	skating_accelerate(e, e.facing ^ 4 if back else e.facing)

## the referee raises his arm: the whistle, or during play a delayed call or the offside warning
func ref_arm_up() -> bool:
	return whistle_timer != 0 or (not play_stopped and (offside_warning or delayed_call))

## the word +0x36: the high word of the heading
static func heading_word(e: Entity) -> int:
	return _s16(e.heading >> 16)

func skating_accelerate(e: Entity, dir: int) -> void:
	var k := e.speed_skill + 0x30
	var v: Array = Tables.dir8_vectors[dir & 7]
	var ax := _div_trunc(v[0] * k, 64)
	var ay := _div_trunc(v[1] * k, 64)
	# no acceleration into the boards just touched (push_x/push_y hold the board normal)
	if e.push_y != 0 and ((e.push_y ^ ax) < 0):
		ax = 0
	if e.push_x != 0 and ((e.push_x ^ ay) >= 0):
		ay = 0
	var factor := e.speed_skill + (0x20 - (e.weight >> 3))
	if e.line_slot == 0:
		factor += e.speed_skill + 0x14
	var nvx := e.vx + ((ax * factor) >> 5)
	var nvy := e.vy + ((ay * factor) >> 5)
	var sp2 := nvx * nvx + nvy * nvy
	scratch_a = _s16(nvx)
	scratch_b = _s16(nvy)
	var level: int
	if e.slot == Entity.Slot.REFEREE:
		# slower while the play is stopped away from the centre
		level = 0xc if (play_stopped and absi(e.yi) >= 0x74) else 0xf
	else:
		level = (e.stamina * e.energy) >> 12
	level = clampi(level, 0, 15)
	var limit := Tables.max_speed_sq[level]
	if e.flags2 & Entity.F2_HOOKED:
		limit >>= 3
	scratch_ac = limit & 0xffffffff
	if sp2 <= limit:
		e.vx = nvx
		e.vy = nvy
	# fatigue (end of skating_accelerate): now and then a skater loses 0x28 energy; a fresh one
	# (>= 0xc00 left) gets his endurance rating back
	if e.slot < 12 and opt_line_changes and not play_stopped and e.line_slot != 0:
		scratch_a = random(0x80)
		if scratch_a == 0:
			var en := _s16(e.energy - 0x28)
			if en < 0xc00:
				scratch_a = en
				e.energy = maxi(en, 0)
			else:
				scratch_a = mini(en + e.endurance, 0x1000)
				e.energy = maxi(scratch_a, 0)

func stop_skating(e: Entity) -> void:
	if absi(e.vx) > 0x1000 or absi(e.vy) > 0x1000:
		if (e.flags & Entity.F_BACKWARDS) == 0:
			e.flags2 |= Entity.F2_TURNING
			if e.slot == Entity.Slot.REFEREE:
				Anim.set_animation(e, Anim.REF_STOP_ARM if ref_arm_up() else Anim.REF_STOP)
			else:
				Anim.set_animation(e, Anim.STOP)
		elif e.slot == Entity.Slot.REFEREE:
			Anim.set_animation(e, Anim.REF_GLIDE_ARM if ref_arm_up() else Anim.REF_GLIDE)
		else:
			Anim.set_animation(e, Anim.GLIDE)
	brake(e)

func brake(e: Entity) -> void:
	var dec := e.speed_skill + 200
	if e.line_slot == 0:
		dec += e.speed_skill * 2
	if e.vx < 0:
		e.vx = mini(0, e.vx + dec)
	else:
		e.vx = maxi(0, e.vx - dec)
	if e.vy < 0:
		e.vy = mini(0, e.vy + dec)
	else:
		e.vy = maxi(0, e.vy - dec)

## goalie_move (0x5f8b2): the goalie turns in steps of one and always uses the goalie animations
func goalie_move(e: Entity, dir: int) -> void:
	dir &= 0xf
	if dir >= 8:
		if dir == 9 and (e.vx != 0 or e.vy != 0):
			brake(e)
			return
		if e.flags2 & Entity.F2_TURNING:
			return
		Anim.set_animation(e, 1)
		return
	# while he goes for the puck (GOALIE_GET_PUCK) he turns towards it, else towards the input;
	# one step a call, the shorter way (clockwise when it is behind him)
	var target_dir := dir
	if not play_stopped and puck_carrier != e.slot and e.state() == Entity.State.GOALIE_GET_PUCK:
		target_dir = e.puck_dir
	if target_dir != e.facing:
		e.facing = (e.facing + (1 if ((e.facing - target_dir) & 4) != 0 else -1)) & 7
	Anim.set_animation(e, Anim.GOALIE_IDLE)
	skating_accelerate(e, e.facing)

## switch_to_nearest (0x59e69): the user takes the skater of his team nearest to where the puck
## is going (its position plus 1/256 of its velocity), not one who is busy, cannot be selected or is
## the other user's; when that is himself he lunges for the puck (lunge_for_puck). (A user without a
## team, 0, gets the away team's skaters, as in the original.)
func switch_to_nearest(e: Entity, player: int) -> void:
	var px := Entity.to_s16(puck.xi + (puck.vx >> 8))
	var py := Entity.to_s16(puck.yi + (puck.vy >> 8))
	var team_no := user2_team if player != 0 else user1_team
	var first := 0 if team_no == 1 else 6
	var other := user1_slot if player != 0 else user2_slot
	var best := e.slot
	var best_d := 0xffffffff
	for i in 6:
		var p := entities[first + i]
		if p.line_slot <= 0 or (p.flags2 & Entity.F2_UNSELECTABLE) or (p.flags & Entity.F_BUSY):
			continue
		var dx := px - p.xi
		var dy := py - p.yi
		var d := (dx * dx + dy * dy) & 0xffffffff
		if d > best_d or p.slot == other:
			continue
		best_d = d
		best = p.slot
	var cur := user2_slot if player != 0 else user1_slot
	if cur == best:
		PuckLogic.lunge_for_puck(self, e)
		return
	if player == 0:
		if best != user1_slot:
			user1_slot = find_switch_target(best, user1_slot)
	elif best != user2_slot:
		user2_slot = find_switch_target(best, user2_slot)

## find_switch_target (0x59fe1): moves the user flag from `cur` to `target`, returns the new slot
func find_switch_target(target: int, cur: int) -> int:
	if cur >= 0 and cur < 12:
		var c := entities[cur]
		if c.flags2 & Entity.F2_LINE_CHANGE:
			return cur
		c.flags = (c.flags & ~(Entity.F_USER | Entity.F_STATE_ENTERED)) | Entity.F_STATE_ENTERED
	if target >= 0 and target < 12:
		entities[target].flags |= Entity.F_USER
	return target

# --------------------------------------------------------------------------------------------
# movement and collisions (move_entity -> collide_boards -> collide_corner / collide_net ->
# bounce_off_boards; collide_neighbours -> collide_pair)
# --------------------------------------------------------------------------------------------

## move_entity (0x580f5): boards and nets for the body (then, when it did not bounce, for the stick
## of a player at the frame's offset), body contacts with the neighbours in the draw order, and the
## entity's new place in the draw order (sorted by y); after a contact that sent the puck in / an
## exchange of momentum (puck_in_net) the entity goes back to its last position instead
func move_entity(e: Entity) -> void:
	bounced = false
	puck_in_net = false
	var x := e.xi
	var y := e.yi
	if (e.flags & Entity.F_ARRIVED) == 0:
		collide_boards(e, e.xi, e.yi, e.half_w, e.half_h)
		if e.push_y == 0 and e.push_x == 0 and e.slot < 12:
			var o := Tables.frame_offset(e.frame, (e.flags4 & Entity.F4_MIRROR) != 0)
			collide_boards(e, _s16(e.xi + o.x), _s16(e.yi + o.y), 1, 1)
		collide_neighbours(e, x, y)
	if not puck_in_net:
		_draw_order_move(e.slot, y)
	elif e.anim < 0xf0f or e.anim > 0x1055:
		e.x = (e.prev_x & ~0xffff) | (e.x & 0xffff)
		e.y = (e.prev_y & ~0xffff) | (e.y & 0xffff)

## sort_draw_order (0x5dd6b): every entity's y as its key, bubble sorted (stable)
func sort_draw_order() -> void:
	for i in 17:
		draw_keys[i] = entities[i].yi
	var swapped := true
	while swapped:
		swapped = false
		for k in 16:
			var a := draw_list[k]
			var b := draw_list[k + 1]
			if draw_keys[b] < draw_keys[a]:
				draw_list[k] = b
				draw_list[k + 1] = a
				draw_pos[a] = k + 1
				draw_pos[b] = k
				swapped = true

## the end of move_entity: the entity moves up or down the draw order to its new y
func _draw_order_move(slot: int, y: int) -> void:
	var k := draw_pos[slot]
	while k != 16:
		var o := draw_list[k + 1]
		if y <= draw_keys[o]:
			break
		draw_list[k] = o
		draw_list[k + 1] = slot
		draw_pos[slot] += 1
		draw_pos[o] -= 1
		k += 1
	k = draw_pos[slot]
	while k != 0:
		var o := draw_list[k - 1]
		if draw_keys[o] <= y:
			break
		draw_list[k] = o
		draw_list[k - 1] = slot
		draw_pos[slot] -= 1
		draw_pos[o] += 1
		k -= 1
	draw_keys[slot] = y

## collide_boards (0x582c9): boards with rounded corners (radius 64); between the corners at the
## ends the nets are checked first. a, b (scratch_a / scratch_b) are the board's direction,
## (ny, -nx) * 256
func collide_boards(e: Entity, px: int, py: int, hw: int, hh: int) -> void:
	var w := RINK_HALF_W - hw
	var h := RINK_HALF_H - hh
	var cw := w - CORNER_RADIUS
	var ch := h - CORNER_RADIUS
	if py <= -ch or py >= ch:
		if px < -cw or px > cw:
			var dy := py - (-ch if py <= -ch else ch)
			var dx := px - (-cw if px < -cw else cw)
			scratch_b = _s16(dx)
			scratch_a = _s16(dy)
			# the original passes (dy, dx)
			var dist := _s16(approx_distance(dy, dx))
			scratch_b = _s16(-scratch_b)
			if dist > CORNER_RADIUS - 1:
				scratch_a = _s16((dy << 8) / dist)
				scratch_b = _s16((-dx << 8) / dist)
				collide_corner(e, scratch_a, scratch_b)
		else:
			collide_net(e, entities[Entity.Slot.NET_BOTTOM if py <= -ch else Entity.Slot.NET_TOP], px, py, hw, hh)
	# the boards: the normal (scratch_a, scratch_b) of the side hit
	var push := (e.push_x | e.push_y) & 0xffff
	if push != 0:
		scratch_a = _s16(push)
		return
	scratch_a = 0x100
	scratch_b = 0
	if py < h:
		scratch_a = -0x100
		if py > -h:
			scratch_a = 0
			scratch_b = -0x100
			if px < w:
				scratch_b = 0x100
				if px > -w:
					return
	collide_corner(e, scratch_a, scratch_b)

## a 32 bit signed value (the original's registers wrap)
static func _s32(v: int) -> int:
	v &= 0xffffffff
	return v - 0x100000000 if v >= 0x80000000 else v

static func _s16(v: int) -> int:
	v &= 0xffff
	return v - 0x10000 if v >= 0x8000 else v

## collide_corner (0x58b7f): a high puck at the boards goes out of play (over the glass behind the
## top net it hits the protective glass first), anything else bounces
func collide_corner(e: Entity, a: int, b: int) -> void:
	if e.slot == Entity.Slot.PUCK:
		var out := false
		if e.zi > 0x1d:
			out = true
		elif (e.zi & 0xffff) > 0x12:
			if e.yi < 0xf8:
				out = true
			elif absi(e.xi) > 0x27 and absi(e.xi) < 0x39 and e.vy > 3999 and last_touch_y > 0x25:
				# into the protective glass behind the net: the glass shakes (the shadow entity
				# plays animation 0x821 there)
				e.vy >>= 1
				Anim.set_animation(shadow, 0x821)
				shadow.x = ((-0x40 if e.xi < 0 else 0x3f) << 16) | (shadow.x & 0xffff)
				shadow.y = (0x10b << 16) | (shadow.y & 0xffff)
				play_sfx(0xae)
				add_crowd(0x4b0, 0x5dc)
				excitement += 0xf
				out = true
		if out:
			# over the glass: out of play, a new puck is dropped
			action_hold_camera = true
			e.flags |= Entity.F_ARRIVED
			if e.yi < 0:
				e.flags4 |= Entity.F4_FLIP_Y
			shadow.frame = -1
			if not play_stopped:
				Rules.queue_infraction(self, entities[maxi(0, last_touch_slot)], Rules.INF_FROZEN)
			Rules.end_penalty_shot(self)
			one_timer = false
			breakaway = false
			return
	bounce_off_boards(e, a, b)

## bounce_off_boards (0x587d3): the velocity in the board's frame, vn = -(a vy - b vx) / 256 (into
## the board when negative) and vt along it; a skater keeps a quarter of vn (at least 1000 back),
## the puck a quarter and loses 1/64 + 1/128 of vt, a hard puck jumps and spins. After a net frame
## (bounced) a skater does not cross the posts' line
func bounce_off_boards(e: Entity, a: int, b: int) -> void:
	scratch_a = _s16(a)
	scratch_b = _s16(b)
	e.push_x = a
	e.push_y = b
	var vn := -_s16((a * e.vy - e.vx * b) >> 8)
	var vt := _s16((b * e.vy + e.vx * a) >> 8)
	scratch_ac = (scratch_ac & ~0xffff) | (vn & 0xffff)
	if e.slot != Entity.Slot.PUCK:
		if vn > 1000:
			bounced = false
			return
		if vn < -0xfff and e.speed > 9 and not bounced:
			play_sfx(0xb1)
		vn >>= 2
		if vn > -0x385:
			vn = -1000
		scratch_ac = (scratch_ac & ~0xffff) | (vn & 0xffff)
		e.vx = _s16((a * vt - vn * b) >> 8)
		e.vy = _s16((vn * a + b * vt) >> 8)
		if bounced:
			var pxi := e.prev_x >> 16
			if (pxi < -0x17 and e.vx > 0) or (_s16(pxi) > 0x17 and e.vx < 0):
				e.vx = 0
				e.x = (e.prev_x & ~0xffff) | (e.x & 0xffff)
			var pyi := e.prev_y >> 16
			var sy := -0xec if pyi < 0 else 0xec
			if (pyi > sy + 10 and e.vy < 0) or (pyi < sy - 6 and e.vy > 0):
				e.vy = 0
				e.y = (e.prev_y & ~0xffff) | (e.y & 0xffff)
	else:
		shot_in_flight = false
		pass_target = -1
		if vn >= 0:
			bounced = false
			return
		vn >>= 2
		scratch_ac = (scratch_ac & ~0xffff) | (vn & 0xffff)
		if vn < -0x3ff:
			e.vz = _s16(-random(0x800))
			PuckLogic.puck_spin(self, e, a)
			if not bounced:
				var sfx := -1
				if (e.zi & 0xffff) < 0xb:
					if puck_carrier < 0:
						var hard := maxi(0, (vn >> 10) + 4)
						sfx = [0xad, 0x7b, 0x95][hard % 3]
				else:
					sfx = [0xaf, 0xa5, 0xa7][random(3)]
				if sfx >= 0:
					play_sfx(sfx)
		vt = _s16(vt - (vt >> 6) - (vt >> 7))
		e.vx = _s16((a * vt - vn * b) >> 8)
		e.vy = _s16((vt * b + a * vn) >> 8)
		if puck_carrier < 0 or absi(puck.yi) > 0xe8:
			Rules.end_penalty_shot(self)
		one_timer = false
		breakaway = false
	bounced = false
	if e.vz > 0:
		e.vz = 0

## collide_net (0x584aa): the puck against a net (hw, hh: the half size of the moving entity);
## players are pushed around it (collide_player_net). Coming down onto the roof the puck stays on
## top; else the goal line is crossed between the posts (the crossing point from the step's motion)
## a goal (score_goal) unless the puck comes from behind the net or hits a post, otherwise it
## bounces off the frame
func collide_net(e: Entity, net: Entity, px: int, py: int, hw: int, hh: int) -> void:
	if e.zi > 0xd:
		return      # over the net
	if e.slot != Entity.Slot.PUCK:
		collide_player_net(e, net, px, py, hw, hh)
		return
	var dx := _s16(px - net.xi)
	var w := hw + 0x10
	if dx > w or dx < -w:
		return
	var dy := _s16(py - net.yi)
	var h := hh + 2
	if dy > h or dy < -h:
		return
	if _s16(e.prev_z >> 16) >= 0xd:
		# it came down onto the roof of the net: it stays at its height and bounces up
		e.z = (e.prev_z & ~0xffff) | (e.z & 0xffff)
		if e.vz < 0:
			e.vz = _s16(-e.vz) >> 1
		return
	puck_in_net = true
	e.flags &= ~Entity.F_ATTACK_UP
	if puck_carrier >= 0:
		var c := entities[puck_carrier]
		puck_carrier = -1
		c.timer_c = 8
		var ty := puck.yi if (c.flags & Entity.F_ATTACK_UP) else -puck.yi
		if _s16(ty) < 0:
			e.flags |= Entity.F_ATTACK_UP
	var a := -0x100
	var b := 0
	var dyv := (e.y - e.prev_y) >> 8
	scratch_a = a
	scratch_b = _s16(dyv)
	if dyv != 0:
		var depth := -h
		if dyv > 0:
			a = 0x100
			depth = h
		depth = _s16(depth + dy)
		var dxv := _s16((e.x - e.prev_x) >> 8)
		var div := _s16(dyv)
		# where the step crossed the front of the net (an unsigned 16 bit quotient in the original)
		var q := _div_trunc(dxv * depth, div) if div != 0 else -1
		if q >= 0 and q < 0x10000:
			var cx := _s16(dx - q)
			if cx >= -w and cx <= w:
				if _s16(e.yi ^ a) >= 0:
					a = -a
					scratch_a = a
					scratch_b = 0
					if (e.flags & Entity.F_ATTACK_UP) == 0:
						if e.zi != 0xd and cx <= w - 1 and cx >= -(w - 1):
							Rules.score_goal(self, net)
							return
						# off the post / crossbar
						shot_in_flight = false
						if not play_stopped:
							add_crowd(500, 0x4b0)
							excitement += 0x28
						play_sfx(0xac)
						var r := random(0x1000)
						e.vy = -r if e.yi >= 0 else r
						scratch_a = e.vy
						e.vx = random(0x2000) - 0x1000
						e.vz = random(0x2000) - 0x1000
						PuckLogic.puck_spin(self, e, e.vy)
						Rules.end_penalty_shot(self)
						one_timer = false
						breakaway = false
						return
				bounced = true
				bounce_off_boards(e, a, b)
				return
	# off the side of the frame
	a = 0
	b = 0x100 if _s16(e.xi - (e.prev_x >> 16)) < 0 else -0x100
	bounced = true
	bounce_off_boards(e, a, b)

## collide_player_net (0x53ce5): a skater or the referee bumps into the net frame (an elliptic
## body); a skater going fast enough may knock the net off instead (net_push_off)
func collide_player_net(e: Entity, net: Entity, px: int, py: int, hw: int, hh: int) -> void:
	if e.slot >= 12 and e.slot != Entity.Slot.REFEREE:
		return
	var dy := _s16(py - net.yi)
	var dx := _s16(px - net.xi)
	if net.slot == Entity.Slot.NET_TOP:
		if hh + dy < -0x22:
			return
	elif dy - hh > 0x21:
		return
	if absi(dx) - hw >= 0x40:
		return
	scratch_a = _s16(-dy)
	scratch_b = dx
	var q := (dx * dx) >> 2
	if q > 0x100 or dy * dy * 2 + q > 0x100:
		return
	if e.slot != Entity.Slot.REFEREE and PuckLogic.net_push_off(self, e, net):
		return
	var dist := (approx_distance(dx, dy) + 1) & 0xffff
	var a := clampi(_s16(_div_trunc(-dy << 8, dist)), -0xff, 0xff)
	var b := clampi(_s16(_div_trunc(dx << 8, dist)), -0xff, 0xff)
	bounced = true
	bounce_off_boards(e, a, b)

## collide_neighbours (0x58ce2): the entities next to this one in the draw order, up to 16 apart in
## y (by the keys of their last moves), upwards then downwards
func collide_neighbours(e: Entity, x: int, y: int) -> void:
	if e.flags2 & Entity.F2_NO_COLLIDE:
		return
	if e.slot >= 12 and e.slot != Entity.Slot.REFEREE:
		return
	var k := draw_pos[e.slot]
	while k != 16:
		var o := draw_list[k + 1]
		var d := _s16(draw_keys[o] - y)
		if d > 0x10:
			break
		collide_pair(e, x, d, entities[o])
		k += 1
	k = draw_pos[e.slot]
	while k != 0:
		var o := draw_list[k - 1]
		var d := _s16(y - draw_keys[o])
		if d > 0x10:
			return
		collide_pair(e, x, d, entities[o])
		k -= 1

## collide_pair (0x58dc7): x is the mover's x before its move, dy the neighbour's key against its y.
## Closing in, opponents (or the referee) hit each other (the impact, a byte of the closing speed,
## at least 5, adds to both +0x18 words; goalie_collision, resolve_body_check); then unless the puck
## went in the momentum is exchanged along the contact by the weights, and team mates step around
## each other
func collide_pair(e: Entity, x: int, dyk: int, o: Entity) -> void:
	if (o.flags & Entity.F_ARRIVED) or (o.flags2 & Entity.F2_NO_COLLIDE):
		return
	if o.slot >= 12 and o.slot != Entity.Slot.REFEREE:
		return
	var dx := _s16(o.xi - x)
	if absi(dx) > 0x10:
		return
	scratch_a = _s16(dx * dx + dyk * dyk)
	if dx * dx + dyk * dyk > 0x100:
		return
	var rvx := _s16(e.vx - o.vx)
	var dxr := _s16(o.xi - e.xi)
	var dyr := _s16(o.yi - e.yi)
	var rvy := _s16(e.vy - o.vy)
	var closing := dyr * rvy + rvx * dxr
	scratch_b = _s16(closing)
	if closing < 0:
		return
	var strength := _s16(closing >> 4)
	scratch_b = strength
	if e.slot == Entity.Slot.REFEREE or o.slot == Entity.Slot.REFEREE or ((o.flags ^ e.flags) & Entity.F_PLAYER2) != 0:
		var s := ((closing >> 4) >> 8) & 0xff
		if s >= 0x80:
			s -= 0x100
		if s < 6:
			s = 5
		last_impact = s
		e.speed = _s16(e.speed + s)
		o.speed = _s16(o.speed + s)
		if (o.flags2 & Entity.F2_KNOCKED) == 0:
			o.hit_by = e.slot
		if (e.flags2 & Entity.F2_KNOCKED) == 0:
			e.hit_by = o.slot
		if s > 0x13 and (puck_carrier == e.slot or puck_carrier == o.slot):
			PuckLogic.crowd_reaction_sfx(self, 0)
		PuckLogic.goalie_collision(self, e, o)
		PuckLogic.resolve_body_check(self, e, o, s)
	if puck_in_net:
		return
	var tang := _s16((dyr * rvx - rvy * dxr) >> 4)
	var me := e.weight + 0x8c
	var total := _s16(o.weight + 0x8c + me)
	var give := _div_trunc(me * strength, total)
	scratch_a = _s16(give)
	scratch_b = _s16(give)
	e.vx = _s16(o.vx + _s16((give * dxr + tang * dyr) >> 4))
	e.vy = _s16(o.vy + _s16((give * dyr - tang * dxr) >> 4))
	o.vx = _s16(o.vx + _s16((dxr * give) >> 4))
	o.vy = _s16(o.vy + _s16((dyr * give) >> 4))
	puck_in_net = true   # byte_c90ba: the mover goes back to its last position
	if not play_stopped and ((o.flags ^ e.flags) & Entity.F_PLAYER2) == 0:
		# team mates step around each other
		var away := Tables.direction8(dxr, dyr)
		if (e.flags & Entity.F_USER) == 0:
			var want := Tables.direction8(_s16(e.target_x - e.xi), _s16(e.target_y - e.yi))
			if want == away or (e.vx == 0 and e.vy == 0 and away == e.facing):
				e.want_dir = (away + 2) & 7
				apply_skating(e, e.want_dir)
		if (o.flags & Entity.F_USER) == 0:
			var back := (away + 4) & 7
			var want_o := Tables.direction8(_s16(o.target_x - o.xi), _s16(o.target_y - o.yi))
			if want_o == back or (e.vx == 0 and e.vy == 0 and back == o.facing):
				o.want_dir = (back + 2) & 7
				apply_skating(o, o.want_dir)

# --------------------------------------------------------------------------------------------
# camera (update_camera 0x65d8d)
# --------------------------------------------------------------------------------------------

## update_camera (0x65d01): the camera (the view's centre) follows its target with a dead zone of
## 0xa up and down and 0x28 sideways, moving 1/16 (1/8 when the carrier skates fast towards the
## edge of the view) of the way per step, at most 2 (0x20 >> 4) while the play is stopped. The
## target: the carrier (or the loose puck) and a lead of up to 0x32 in his direction of play (the
## referee's when he has the puck); while the referee works a stoppage the referee, the side of his
## way the camera already is on, then the faceoff dot once he is close to it; nothing at 0:00 or
## while the camera is held. For the cup presentation (game_flags 0x80) it looks at the bench
## door (-100, 0xf).
func update_camera() -> void:
	var dzx := 0x28
	var dzy := 0xa
	var fast := false
	var ac := camera_target_y
	var b0 := camera_target_x
	var a: int
	var b := scratch_b
	if intermission_camera:
		camera_target_x = -100
		b0 = -100
		camera_target_y = 0xf
		ac = 0xf
		a = _s16(0xf - camera_y)
		if a < -5:
			b = 0x14
		elif a > 5:
			b = 0xa
		if absi(a) > 5:
			b = clampi(_s16(b - camera_y), -0x20, 0x20)
			if b != 0:
				b >>= 5
				if b == 0:
					b = 1
				camera_y = _s16(camera_y + b)
		_camera_x_step(b0, dzx, 5, b, ac)
		return
	if clock_seconds != 0 or clock_sub != 0:
		var rp := _s16(ref_phase & 0xffff)
		if (stoppage_countdown and stoppage_timer < 0) or rp > 0:
			var r := referee
			camera_target_x = r.xi
			camera_target_y = r.yi
			var d1 := _s16(camera_target_x - camera_x)
			var d2 := _s16(r.target_x - camera_x)
			if (d1 ^ d2) < 0:
				camera_target_x = camera_x
			elif absi(d1) > absi(d2):
				camera_target_x = r.target_x
			d1 = _s16(camera_target_y - camera_y)
			d2 = _s16(r.target_y - camera_y)
			if (d1 ^ d2) < 0:
				camera_target_y = camera_y
			elif absi(d1) > absi(d2):
				camera_target_y = r.target_y
			ac = camera_target_y
			b0 = camera_target_x
			var rs := r.state()
			if rs == Entity.State.REF_GOTO_FACEOFF or rs == Entity.State.REF_PENALTY_SHOT:
				var fx := r.xi - faceoff_x
				var fy := r.yi - faceoff_y
				if fx * fx + fy * fy < 0x640:
					camera_target_y = faceoff_y
					ac = faceoff_y
					camera_target_x = faceoff_x
					b0 = faceoff_x
					dzy = 0
					dzx = 0
		elif not action_hold_camera:
			var t := puck
			if puck_carrier >= 0:
				t = entities[puck_carrier]
				if t.slot == Entity.Slot.REFEREE:
					camera_offset_y = _s16(-Entity.to_s8(t.vy >> 8))
				elif t.flags & Entity.F_ATTACK_UP:
					fast = t.vy < -0x64
					camera_offset_y = mini(_s16(camera_offset_y + 2), 0x32)
				else:
					fast = t.vy > 0x64
					camera_offset_y = _s16(camera_offset_y - 2)
					if camera_offset_y <= -0x32:
						camera_offset_y = -0x32
			ac = _s16(camera_offset_y + t.yi + Entity.to_s8(t.vy >> 8))
			camera_target_y = ac
			b0 = t.xi
			camera_target_x = b0
	a = _s16(ac - camera_y)
	var move := true
	if a < -dzy:
		b = maxi(_s16(ac + dzy), -0xbc)
	elif dzy < a:
		b = mini(ac if fast else _s16(ac - dzy), 0xec)
	else:
		move = false
	if move and absi(a) > dzy:
		b = _s16(b - camera_y)
		if play_stopped:
			b = clampi(b, -0x20, 0x20)
		if b != 0:
			b >>= 3 if fast else 4
			if b == 0:
				b = 1
			camera_y = _s16(camera_y + b)
	_camera_x_step(b0, dzx, 4, b, ac)

## the sideways part of update_camera: towards the target outside the dead zone, within +-0x20;
## the scratch words keep what the original leaves in them
func _camera_x_step(b0: int, dzx: int, shift: int, b: int, ac: int) -> void:
	scratch_ac = (scratch_ac & 0xffff0000) | (ac & 0xffff)
	var a := _s16(b0 - camera_x)
	scratch_a = a
	scratch_b = b
	if a < -dzx:
		b = maxi(_s16(b0 + dzx), -0x20)
	elif dzx < a:
		b = mini(_s16(b0 - dzx), 0x20)
	else:
		return
	b = clampi(_s16(b - camera_x), -0x20, 0x20)
	if b != 0:
		b >>= shift
		if b == 0:
			b = 1
		camera_x = _s16(camera_x + b)
	scratch_b = b

## scroll position of the 320x168 view over the 384x592 rink surface (game_loop)
func view_origin() -> Vector2i:
	return Vector2i(clampi(camera_x + 0x20, 0, 0x40), clampi(0xec - camera_y, 0, 0x1a8))

# --------------------------------------------------------------------------------------------
# helpers
# --------------------------------------------------------------------------------------------

## approx_distance (0xb3d94): octagonal approximation good enough for the AI decisions
## approx_distance (0xb3d94): |dx| / cos or |dy| / sin of the vector's angle (vector_octant), so
## within a few per mille of the euclidean length
static func approx_distance(dx: int, dy: int) -> int:
	var a := absi(Tables.vector_angle(dx, dy))
	if a > 0x100:
		a = 0x200 - a
	if a <= 0x80:
		return ((absi(dx) << 16) & 0xffffffff) / Tables.cos16(a)
	return ((absi(dy) << 16) & 0xffffffff) / Tables.sin16(a)

static func _div_trunc(a: int, b: int) -> int:
	# C division truncates towards zero; GDScript's / on ints does too, but keep it explicit
	var q := absi(a) / b
	return -q if a < 0 else q

## isqrt32: integer square root
## isqrt32 (0x93470): the original's square root of an unsigned 32 bit number: a subtraction of odd
## numbers below 0x931, below 0x10000 two Newton steps from a guess of the high byte, otherwise four
## Newton steps of 16 bit divisions (the original faults on numbers so large that a quotient
## exceeds 16 bits; they do not occur)
static func isqrt32(v: int) -> int:
	v &= 0xffffffff
	if v < 0x10000:
		if v <= 0x930:
			var d := v >> 1
			if d == 0:
				return v
			var a := -6
			while true:
				a += 0x10
				d -= a
				if d < 0:
					break
			d += a
			a = (a - 6) >> 2
			for i in 3:
				d -= a
				if d < 0:
					return a
				a += 1
			return a
		var bl := (v >> 8) + 0x30
		if bl >= 0x100:
			var bx := (v >> 9) + 0x80
			return ((v / bx) + bx) >> 1
		bl = (bl + v / bl) >> 1
		return ((v / bl) + bl) >> 1
	var b := ((v >> 16) + 0x800) & 0xffff
	for i in 3:
		b = ((b + v / b) & 0xffff) >> 1
	return ((v / b + b) & 0xffff) >> 1

static func isqrt(v: int) -> int:
	if v <= 0:
		return 0
	var r := int(sqrt(float(v)))
	while r * r > v:
		r -= 1
	while (r + 1) * (r + 1) <= v:
		r += 1
	return r
