class_name Highlight
## The highlight of another game at an intermission of an exhibition game, ported literally:
## simulate_pending_games (0x18f8d) picks a game of the scores around the league and
## league_highlight_game (0x69336) plays a scene of it in the match itself. The match's state is
## kept in part (the teams, their goalie requests and skaters, the users, the period, the score, the
## players' places, the options, the line tables), the other teams are loaded (load_team_databases
## mode 2), a scene is set up near a net (the players placed by their line slots from unk_cd9a0, the
## puck loose near the dot with a random speed, the clock at 1:00 to 2:59 of the game's period) and
## played by the computer until a stoppage ends it or a button; then the match's state comes back
## (load_team_databases mode 4: the players' status bytes from their places) and the score of the
## highlight goes to the game. What is not kept stays as the highlight left it (the energies, the
## team statistics, the random seed), as in the original.

const POSITIONS := 0xcd9a0          # unk_cd9a0: 2 x 6 (x, y) words, by line slot, the team shooting up first
const STATUS_OF_PLACE := 0xc66b4    # unk_c66b4: the status byte of a player by -entity_of (words)

## the parts of the match league_highlight_game keeps
class Saved:
	var match_over: bool
	var team_ids: Array
	var goalie_request: Array
	var users: Array                # user1_team, user2_team
	var period_num: int
	var period: int
	var skaters_on_ice: Array       # team +0x36
	var goals: Array
	var entity_of: Array
	var options: Array              # option_flags: the five options and settings2
	var infos: Array                # the teams' records (their line tables with the scratches)
	var stop_flags: int

## simulate_pending_games (0x18f8d): the games around the league that finished since they were last
## shown are marked done; a game not done is picked at random (randomrange(6), the match's seed)
## and marked. Returns [game, home goals, away goals, period] for its highlight (a finished game:
## its period 3 and one goal less each, the highlight's score is not kept), or [] when all six are
## done. `finish(game, goals)` takes the highlight's score.
static func pick(sim: Sim) -> Array:
	var games: Array = LeagueScores.games
	for g in games.size():
		if games[g][2] >= 5 and games[g][2] != LeagueScores.shown[g]:
			LeagueScores.done_mask |= 1 << g
	if LeagueScores.done_mask == 0x3f:
		return []
	var g := 0
	while true:
		g = Entity.to_s16(sim.random(6))
		if (LeagueScores.done_mask & (1 << g)) == 0:
			break
	LeagueScores.done_mask |= 1 << g
	var game: Array = games[g]
	var hg: int = game[3]
	var ag: int = game[4]
	var period: int = game[2]
	if period >= 5:
		period = 3
		hg -= 1
		ag -= 1
	return [g, hg, ag, period]

## the end of simulate_pending_games: a game still going takes the highlight's score (one that
## reached its last period, 4, is over now); the statuses shown are noted
static func finish(g: int, goals: Array) -> void:
	var game: Array = LeagueScores.games[g]
	if game[2] <= 4:
		game[3] = goals[0]
		game[4] = goals[1]
		if game[2] == 4:
			game[2] = 5
	for k in LeagueScores.games.size():
		LeagueScores.shown[k] = LeagueScores.games[k][2]

## league_highlight_game (0x69336) up to its loop: the match kept, the game's teams loaded and the
## scene set up. `infos`: the two teams' records; `goals` home and away; `period` the period count.
static func begin(sim: Sim, infos: Array, goals: Array, period: int) -> Saved:
	var s := Saved.new()
	sim.one_minute_said = false
	s.match_over = sim.match_over
	s.team_ids = sim.team_ids.duplicate()
	s.goalie_request = [sim.teams[0].goalie_request, sim.teams[1].goalie_request]
	s.users = [sim.user1_team, sim.user2_team]
	s.period_num = sim.period_num
	s.period = sim.period
	s.skaters_on_ice = [sim.teams[0].skaters_on_ice, sim.teams[1].skaters_on_ice]
	s.goals = [sim.teams[0].goals, sim.teams[1].goals]
	s.entity_of = [sim.teams[0].entity_of.duplicate(), sim.teams[1].entity_of.duplicate()]
	s.options = [sim.opt_penalties, sim.opt_offsides, sim.opt_line_changes, sim.opt_two_line_pass, sim.opt_injuries, sim.settings2]
	s.infos = [sim.teams[0].info, sim.teams[1].info]
	sim.summary_flush()
	# option_flags &= 0xe4: no penalties, offsides, two line passes or injuries
	sim.opt_penalties = false
	sim.opt_offsides = false
	sim.opt_two_line_pass = false
	sim.opt_injuries = false
	sim.match_over = false
	sim.excitement = 0
	load_teams(sim, infos, 2)
	sim.teams[1].goalie_request = 0
	sim.teams[0].goalie_request = 0
	MatchSetup.team_energy_init(sim)
	sim.user2_slot = -1
	sim.user1_slot = -1
	sim.user2_team = 0
	sim.user1_team = 0
	sim.clock_seconds = Entity.to_s16(sim.random(0x78)) + 0x3c
	sim.clock_sub = 0
	sim.hud_clock[0] = sim.clock_seconds / 60
	sim.hud_clock[1] = sim.clock_seconds % 60
	sim.hud_clock[2] = 0
	sim.period_num = period
	sim.period = period - 1
	sim.teams[0].goals = goals[0]
	sim.teams[1].goals = goals[1]
	sim.teams[0].current_line = Entity.to_s16(sim.random(7)) % 4
	sim.teams[1].current_line = Entity.to_s16(sim.random(7)) % 4
	if not sim.stubbed("show_scoreboard", []):
		Scoreboard.start(sim, false)
	_set_game_flags(sim, 0x10 | (2 if _ends_switched(sim) else 0))
	s.stop_flags = _stop_flags(sim)
	_set_misc_flags(sim, 0)
	_set_stop_flags(sim, 0)
	_set_action_flags(sim, 0)
	_set_stop_flags(sim, 4)
	sim.icing_shooter = 0
	sim.icing_flags = 0
	sim.pass_target = -1
	sim.whistle_timer = 0
	sim.ref_phase = -1
	sim.stoppage_timer = -1
	sim.ref_infraction = 0
	sim.ref_infraction_slot = -1
	sim.panel = -1
	sim.penalty_box_mode = false
	sim.message = -1
	sim.clip_frame = -1
	sim.clip = -1
	sim.message_timer = 0
	sim.injury_stoppage = false
	sim.crowd_noise = 0
	sim.goal_prediction[1][1] = -1
	sim.goal_prediction[0][1] = -1
	MatchSetup.entities_setup(sim)
	sim.sort_draw_order()
	sim.camera_y = 0
	sim.camera_x = 0
	sim.camera_offset_y = 0
	sim.camera_target_y = 0
	sim.camera_target_x = 0
	Rules.count_penalized(sim)
	for t in 2:
		var team: Team = sim.teams[t]
		MatchSetup.reset_team_for_period(sim, team)
		Lines.apply_line_change(sim, team)
		Lines.dress_line(sim, team)
		team.carrier_history = PackedInt32Array([-1, -1, -1])
	Rules.reset_players_for_faceoff(sim)
	# the players around the dot by their line slots, facing the puck
	for i in 12:
		var e: Entity = sim.entities[i]
		var k := (0 if e.flags & Entity.F_ATTACK_UP else 6) + e.line_slot
		var x := Exe.i16(POSITIONS + k * 4) + Entity.to_s16(sim.random(0x14)) - 10
		e.x = (Entity.to_s16(x) << 16) | (e.x & 0xffff)
		var goalie := 1 if e.line_slot == 0 else 0
		var r := Entity.to_s16(sim.random(4 if goalie else 0x14)) - goalie
		var y := Exe.i16(POSITIONS + k * 4 + 2) + (10 if r == 0 else 4)
		e.y = (Entity.to_s16(y) << 16) | (e.y & 0xffff)
		e.vy = 0
		e.vx = 0
		var puck: Entity = sim.entities[Entity.Slot.PUCK]
		var d := Tables.direction8(Entity.to_s16(puck.xi - e.xi), Entity.to_s16(puck.yi - e.yi))
		e.heading = ((d & 0xffff) << 16) | (e.heading & 0xffff)
	# the puck loose near the dot
	var p: Entity = sim.entities[Entity.Slot.PUCK]
	p.want_dir = 0x78
	p.dir_timer = 0
	p.x = (Entity.to_s16(Entity.to_s16(sim.random(0x14)) - 10) << 16) | (p.x & 0xffff)
	p.y = (Entity.to_s16(Entity.to_s16(sim.random(0x14)) - 10) << 16) | (p.y & 0xffff)
	p.z = p.z & 0xffff
	p.vx = Entity.to_s16(Entity.to_s16(sim.random(0x7d0)) - 0x3e8)
	p.vy = Entity.to_s16(Entity.to_s16(sim.random(0x7d0)) - 0x3e8)
	p.frame = 0x18a
	p.side = 0
	p.flags4 = 0
	p.set_state(0x18)
	var sh: Entity = sim.entities[Entity.Slot.SHADOW]
	sh.frame = 0x189
	sh.side = 0
	sh.flags4 = 0
	sh.set_state(0x19)
	var ref: Entity = sim.entities[Entity.Slot.REFEREE]
	ref.x = -0x780000 | (ref.x & 0xffff)
	ref.y = ref.y & 0xffff
	ref.heading = (2 << 16) | (ref.heading & 0xffff)
	ref.vy = 0
	ref.vx = 0
	ref.set_state(0x1f)
	sim.sim_tick()
	sim.sim_tick()
	sim.sort_draw_order()
	sim.hud_acc = 0
	sim.puck_carrier = -1
	sim.period_over = 0
	sim.match_over = false
	sim.fade_in = 2                 # cut_to_scene 2: the first frame fades in with the intro
	return s

## the end of league_highlight_game: [home, away] goals of the highlight; the match's state back
static func end(sim: Sim, s: Saved) -> Array:
	sim.message = -1
	sim.clip_frame = -1
	sim.clip = -1
	sim.one_minute_said = false
	sim.crowd_noise = 0
	sim.period_over = -1
	sim.match_over = s.match_over
	sim.team_ids = s.team_ids.duplicate()
	for t in 2:
		sim.teams[t].goalie_request = s.goalie_request[t]
	sim.user1_team = s.users[0]
	sim.user2_team = s.users[1]
	sim.period_num = s.period_num
	sim.period = s.period
	for t in 2:
		sim.teams[t].skaters_on_ice = s.skaters_on_ice[t]
	var goals := [sim.teams[0].goals, sim.teams[1].goals]
	for t in 2:
		sim.teams[t].goals = s.goals[t]
		sim.teams[t].entity_of = (s.entity_of[t] as PackedInt32Array).duplicate()
	sim.opt_penalties = s.options[0]
	sim.opt_offsides = s.options[1]
	sim.opt_line_changes = s.options[2]
	sim.opt_two_line_pass = s.options[3]
	sim.opt_injuries = s.options[4]
	sim.settings2 = s.options[5]
	load_teams(sim, s.infos, 4)
	MatchSetup.period_reset_entities(sim)
	_set_game_flags(sim, 1 | (2 if _ends_switched(sim) else 0))
	_set_misc_flags(sim, 0)
	_set_stop_flags(sim, 0)
	_set_action_flags(sim, 0)
	_set_stop_flags(sim, s.stop_flags)
	sim.puck_carrier = -1
	sim.panel = -1
	sim.camera_x = 0
	sim.camera_y = 0
	sim.lc_bar[1] = 0
	sim.lc_bar[0] = 0
	sim.lc_show[1] = 0
	sim.lc_show[0] = 0
	sim.lc_line[1] = -1
	sim.lc_line[0] = -1
	sim.teams[1].line_change_ui = false
	sim.teams[0].line_change_ui = false
	sim.fade_in = 1
	sim.hud_acc = 0
	sim.whistle_timer = 0
	sim.ref_phase = -1
	sim.entities[Entity.Slot.REFEREE].set_state(0x1e)
	Rules.clear_infractions(sim)
	sim.stoppage_timer = -1
	return goals

## load_team_databases (0x1bbe7) for the teams' records: mode 2 the players' status bytes from the
## records (3 a player, 0 an empty place; the injury dates of a league are not kept here), mode 4
## from the places of the players (entity_of: in the box 5, else unk_c66b4 by -entity_of)
static func load_teams(sim: Sim, infos: Array, mode: int) -> void:
	if sim.stubbed("load_team_databases", [mode]):
		return
	for t in 2:
		var team: Team = sim.teams[t]
		var info: Database.TeamInfo = infos[t]
		team.info = info
		sim.team_info[t] = info
		sim.team_ids[t] = info.index if info != null else t
		team.title_abbrev = info.abbrev if info != null else ""
		team.title_name = info.name if info != null else ""
		for r in 28:
			var pl: Database.Player = info.player(r) if info != null else null
			team.numbers[r] = pl.number if pl != null else 0
			team.first_names[r] = pl.first if pl != null else ""
			team.last_names[r] = pl.last if pl != null else ""
			if pl == null:
				team.roster_status[r] = 0
			elif mode == 4:
				var w: int = team.entity_of[r]
				team.roster_status[r] = 5 if w > 0 else Exe.u8(STATUS_OF_PLACE + (-w) * 2)
			else:
				team.roster_status[r] = 3

## game_flags 2 in the highlight and after it: the odd periods, but not the overtime of a regular
## season game (settings2 bit 1)
static func _ends_switched(sim: Sim) -> bool:
	return (sim.period & 1) != 0 and not (sim.period == 3 and (sim.settings2 & 2) != 0)

static func _set_game_flags(sim: Sim, v: int) -> void:
	sim.play_stopped = (v & 1) != 0
	sim.ends_switched = (v & 2) != 0
	sim.stoppage_countdown = (v & 4) != 0
	sim.delayed_call = (v & 8) != 0
	sim.no_stats = (v & 0x10) != 0
	sim.game_over = (v & 0x40) != 0
	sim.intermission_camera = (v & 0x80) != 0

static func _stop_flags(sim: Sim) -> int:
	return (1 if sim.faceoff_pending else 0) | (4 if sim.whistle_ready else 0) | (0x10 if sim.shot_in_flight else 0) \
		| (0x20 if sim.power_play else 0) | (0x40 if sim.power_play_team == 1 else 0) | (0x80 if sim.offside_warning else 0)

static func _set_stop_flags(sim: Sim, v: int) -> void:
	sim.faceoff_pending = (v & 1) != 0
	sim.whistle_ready = (v & 4) != 0
	sim.shot_in_flight = (v & 0x10) != 0
	sim.power_play = (v & 0x20) != 0
	sim.power_play_team = 1 if (v & 0x40) != 0 else 0
	sim.offside_warning = (v & 0x80) != 0

static func _set_misc_flags(sim: Sim, v: int) -> void:
	sim.misc_first_touch = (v & 0x10) != 0
	sim.second_tick = (v & 0x40) != 0
	sim.half_announce = (v & 0x80) != 0

static func _set_action_flags(sim: Sim, v: int) -> void:
	sim.action_pass = (v & 4) != 0
	sim.action_shot = (v & 8) != 0
	sim.replay.wrapped = (v & 0x10) != 0
	sim.action_hold_camera = (v & 0x40) != 0
	sim.action_replay = (v & 0x80) != 0
