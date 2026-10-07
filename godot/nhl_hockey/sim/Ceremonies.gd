class_name Ceremonies
## The sequences around the match: the national anthem before the game (init_match,
## match_sequence, ai_anthem, ai_ref_anthem), the end of a period and of the game (setup_faceoff,
## end_of_period), the Stanley Cup presentation (ai_puck_give_cup, ai_get_cup, ai_stanley_cup), the
## goal celebration (ai_celebrate_goal) and the three stars (three_stars_sequence 0x48f0b,
## compute_three_stars, compare_player_stats, ai_ref_three_stars, ai_three_stars). The info panel
## and its clips (InfoPanel) pace the referee like in the original.

const ANTHEM_STEPS := 0x708          # init_match: sequence_steps = 30 seconds
const STARS_STEPS := 12000           # three_stars_sequence

# --------------------------------------------------------------------------------------------
# national anthem
# --------------------------------------------------------------------------------------------

## init_match (0x47cd6), the part after the lines are dressed: the goalies stand in their creases,
## the skaters on their blue lines in a random order, the referee at the boards; the anthem of the
## home team's country (0 Canada, 1 USA) decides how long everybody stands still
static func begin_anthem(sim: Sim) -> void:
	var home_id: int = sim.team_info[0].index if sim.team_info[0] != null else 0
	var country: int = Tables.anthem_country[clampi(home_id, 0, Tables.anthem_country.size() - 1)]
	var length: int = Tables.anthem_length[country]
	sim.intro = true
	sim.sequence_steps = ANTHEM_STEPS
	InfoPanel.reset(sim)
	InfoPanel.load_clip(sim, InfoPanel.CLIP_USA_FLAG if country == 1 else InfoPanel.CLIP_CANADA_FLAG)
	InfoPanel.open(sim)
	InfoPanel.music(sim, 10)           # the anthem
	sim.period_over = false
	sim.user1_slot = -1
	sim.user2_slot = -1
	for i in 12:
		sim.entities[i].flags &= ~Entity.F_USER
	# the away team first, entities from the last to the first (the original walks 11 .. 0)
	for t in [1, 0]:
		var taken := [false, false, false, false, false]
		for k in range(5, -1, -1):
			var e: Entity = sim.entities[t * 6 + k]
			if e.line_slot < 0:
				continue
			var up := (e.flags & Entity.F_ATTACK_UP) != 0
			if e.line_slot == 0:
				var gy := -0xdc if up else 0xdc
				e.set_pos(0, gy)
				e.target_x = 0
				e.target_y = gy
				e.timer_b = -100
				e.vx = 0
				e.vy = 0
				e.facing = 0 if up else 4
				Anim.set_animation(e, 0x99)
			else:
				var spot := sim.random(5)
				while taken[spot]:
					spot = (spot + 1) % 5
				taken[spot] = true
				var x := spot * 0x28 - 0x50 + sim.random(8) - 4
				e.target_x = x
				x += sim.random(2)
				var y := (-0x3a if up else 0x30) + sim.random(4) - 2
				e.set_pos(x, y)
				e.target_y = y
				e.facing = 4
				e.vx = 0
				e.vy = 0
				e.timer_b = length + sim.random(0x28) - 0x14
				Anim.set_animation(e, 0)
				e.frame = 0x171
			e.state_sp = 0
			e.set_state(Entity.State.ANTHEM)
	var puck := sim.puck
	sim.puck_stuck_timer = 0x78
	puck.set_pos(200, -0x12c)
	puck.vx = 0
	puck.vy = 0
	puck.state_sp = 0
	puck.set_state(Entity.State.PUCK_IDLE)
	sim.puck_carrier = -1
	var ref := sim.referee
	ref.timer_a = country
	ref.set_pos(0x8e + sim.random(2), 0)
	ref.target_x = 0x8e
	ref.target_y = 0
	ref.facing = 4
	ref.vx = 0
	ref.vy = 0
	ref.timer_b = length
	Anim.set_animation(ref, 0)
	ref.state_sp = 0
	ref.set_state(Entity.State.REF_ANTHEM)
	sim.ref_phase = 0
	sim.action_hold_camera = true
	sim.camera_x = 0
	sim.camera_y = 0
	sim.camera_target_x = 0
	sim.camera_target_y = 0

## the end of match_sequence: the anthem ran out or a user pressed a button; the opening faceoff
## is set up from where everybody stands
static func end_anthem(sim: Sim) -> void:
	sim.intro = false
	sim.sequence_steps = 0
	sim.play_stopped = true
	sim.ref_phase = -1
	sim.action_hold_camera = false
	var puck := sim.puck
	puck.state_sp = 0
	puck.state_stack[0] = Entity.State.PUCK_FACEOFF
	puck.flags |= Entity.F_STATE_ENTERED
	sim.referee.state_sp = 0
	sim.referee.state_stack[0] = Entity.State.REF_FACEOFF
	sim.referee.flags |= Entity.F_STATE_ENTERED
	for i in 12:
		var e: Entity = sim.entities[i]
		if e.line_slot >= 0 and e.state() == Entity.State.ANTHEM:
			e.timer_b = 0
			e.set_state_reset(Entity.State.ALL_GOTO_FACEOFF)
	sim.assign_users()

## ai_anthem (0x4842a): standing on the blue line, now and then a little movement
static func anthem(sim: Sim, e: Entity) -> void:
	if (e.flags & Entity.F_BUSY) or e.timer_b == -100:
		return
	e.timer_b -= 1
	if e.timer_b < 1:
		e.set_state_reset(Entity.State.ALL_GOTO_FACEOFF)
		return
	if sim.random(100) == 0:
		PuckLogic._set_x(e, e.target_x + sim.random(2))
	if (e.flags2 & Entity.F2_TURNING) == 0 and sim.random(0x50) == 0:
		Anim.set_animation(e, Tables.anthem_fidgets[sim.random(9) % 5])
		e.flags2 |= Entity.F2_TURNING

## ai_ref_anthem (0x484da): the referee waits at the boards, then skates to centre ice; when
## everybody stands at the faceoff the sequence ends 10 steps later
static func ref_anthem(sim: Sim, e: Entity) -> void:
	if e.flags & Entity.F_BUSY:
		return
	if e.timer_b == -100:
		if sim.sequence_steps > 10:
			for i in 12:
				if sim.entities[i].timer_b != -100:
					return
			sim.sequence_steps = 10
		return
	if e.timer_b > 0:
		e.timer_b -= 1
		if e.timer_b > 0:
			if sim.random(100) == 0:
				PuckLogic._set_x(e, e.target_x + sim.random(2))
			if e.flags2 & Entity.F2_TURNING:
				return
			if sim.random(0x50) != 0:
				return
			Anim.set_animation(e, 0xdc3 if sim.random(2) == 0 else 0xdab)
			e.flags2 |= Entity.F2_TURNING
			return
	if e.flags & Entity.F_STATE_ENTERED:
		e.flags &= ~Entity.F_STATE_ENTERED
		e.want_dir = 8
		e.timer_a = 0
		e.target_x = -0xf
		e.target_y = 0
		e.flags2 |= Entity.F2_NO_COLLIDE
		e.push_x = 0
		e.push_y = 0
		Anim.set_animation(e, Anim.REF_GLIDE)
		sim.camera_target_y = 0
		sim.ref_phase = 1
		sim.crowd_noise = 800
	var dx := e.xi - e.target_x
	var dy := e.yi - e.target_y
	var d2 := dx * dx + dy * dy
	if d2 < 0x40 and absi(e.vx) < 0x10 and absi(e.vy) < 0x10:
		e.set_pos(e.target_x, e.target_y)
		e.timer_a -= 1
		if e.timer_a >= 0:
			return
		e.timer_a += 8
		Anim.set_animation(e, Anim.REF_GLIDE)
		var want := Tables.direction8(-e.xi, -e.yi)
		if want == e.facing:
			e.vx = 0
			e.vy = 0
			e.timer_b = -100
			Anim.set_animation(e, 0xc57)
			return
		var diff := (want - e.facing) & 7
		e.facing = (e.facing + (1 if diff < 5 else -1)) & 7
		return
	if d2 > 0x90:
		AI.skate_towards(sim, e, e.target_x, e.target_y)
	else:
		AI.ref_skate_to_point(sim, e, e.target_x, e.target_y)

# --------------------------------------------------------------------------------------------
# the end of a period and of the game
# --------------------------------------------------------------------------------------------

## regular season game (option byte 2 bit 1): a tie after one overtime period; playoffs: sudden
## death until a goal
static func regular_season(sim: Sim) -> bool:
	return (sim.settings2 & 2) != 0

## game_over_check (0x15c30): does a win by this score decide the Stanley Cup? In the play-off
## final (sim.cup_series, the 7 games of the final series as the schedule file keeps them, 6 bytes
## each: home, away, then the scores at +4 / +5, 0xff while unplayed) the score goes into the
## first unplayed game and the series is decided (series_winner); the game is taken out again.
static func game_over_check(sim: Sim, home: int, away: int) -> bool:
	if sim.stubbed("game_over_check", [home, away]):
		return sim.cup_final
	if sim.cup_series.size() < 42:
		return false
	var po := sim.cup_series.duplicate()
	var k := 0
	while k < 6 and po[k * 6 + 4] != 0xff:
		k += 1
	po[k * 6 + 4] = home & 0xff
	po[k * 6 + 5] = away & 0xff
	var n := League.series_count(po, 0) if sim.cup_series_games <= 0 else sim.cup_series_games
	return League.series_winner(po, 0, n) >= 0

## end_of_period (0x5dea6): the next period, the overtime (playoffs: as long as needed, the teams
## change ends every time; regular season: once, without changing ends) or the three stars
static func next_period(sim: Sim) -> void:
	sim.period_over = true
	if sim.game_over:
		if not sim.stars_running and not sim.match_over:
			begin_three_stars(sim)
		return
	var p := sim.period + 1
	var switch := true
	if p == 3 and regular_season(sim):
		switch = false
	elif p > 3:
		p = 3
	Rules.clear_infractions(sim)
	if not sim.no_stats:
		sim.summary_close_period()
	sim.start_period(p, switch)
	sim.intermission_pending = true
	# game_loop: the scoreboard of the intermission with the organ
	InfoPanel.music(sim, 0)

# --------------------------------------------------------------------------------------------
# goal celebration and the Stanley Cup
# --------------------------------------------------------------------------------------------

## ai_celebrate_goal (0x4a90f): the scorers skate towards the camera side and raise their sticks;
## the goal scorer jumps up to three times in a row
static func celebrate(sim: Sim, e: Entity) -> void:
	if sim.puck_carrier == e.slot:
		sim.puck_carrier = -1
		if sim.puck.state() == Entity.State.PUCK_NORMAL:
			sim.puck.set_state(Entity.State.PUCK_IDLE)
	if e.flags & Entity.F_BUSY:
		return
	if Lines.handle_line_change(sim, e):
		return
	if e.flags & Entity.F_STATE_ENTERED:
		e.flags &= ~Entity.F_STATE_ENTERED
		e.timer_a = sim.random(0x78)
		e.want_dir = 8
		if not sim.intermission_camera:
			e.target_x = -100 if sim.camera_x < 0 else 100
			e.target_y = sim.camera_y - (0x37 if sim.camera_x < 0 else 0)
		else:
			e.target_x = -0x50
			e.target_y = 0
		if e.slot == sim.last_shooter:
			sim.scorer_jumps = 0
	e.timer_a -= 1
	if e.timer_a < 0:
		e.flags |= Entity.F_BUSY
		var anim := 0x731
		e.timer_a = sim.random(0x78)
		if e.slot == sim.last_shooter:
			anim = 0x769
			if sim.scorer_jumps == 0 or (sim.scorer_jumps < 3 and sim.random(2) == 0):
				e.timer_a = 0
				sim.scorer_jumps += 1
			else:
				sim.scorer_jumps = 0
				if e.timer_a < 0x1f:
					e.timer_a = 0x1e
		Anim.set_animation(e, anim)
		return
	if e.flags & Entity.F_USER:
		return
	AI.skate_towards(sim, e, e.target_x, e.target_y)

## ai_puck_give_cup (0x49bc2), run by the puck shadow: once the camera reached the bench door the
## Stanley Cup is carried in (0xe97) and waits there (frame 0x365)
static func puck_give_cup(sim: Sim, e: Entity) -> void:
	if e.flags & Entity.F_STATE_ENTERED:
		AI.puck_shadow(sim, e)
		if sim.panel == InfoPanel.HELD:
			sim.panel = InfoPanel.CLOSING
		if sim.camera_x > -0x20 or absi(sim.camera_y) > 0x14:
			return
		e.flags &= ~Entity.F_STATE_ENTERED
		e.frame_wait = 0
		e.set_pos(-0xbe, 3)
		e.timer_a = 0
		e.vx = 0
		e.vy = 0
		e.pass_target = 0
		e.frame = 0x362
		Anim.set_animation(e, 0xe97)
	if e.timer_a < 100:
		if e.anim == 0:
			e.timer_a = 100
			return
		if e.anim_pos > 3 and e.anim_hold < 0xc:
			PuckLogic._set_x(e, -0xaf)
	elif e.timer_a == 200 and e.frame == 0x365 and e.anim == 0 and sim.random(0x28) == 0:
		Anim.set_animation(e, 0xeb5)

## ai_get_cup (0x499d8): the captain skates to the bench door and takes the cup from the shadow
static func get_cup(sim: Sim, e: Entity) -> void:
	sim.stoppage_timer = 300
	if e.flags & Entity.F_BUSY:
		return
	if e.flags & Entity.F_STATE_ENTERED:
		e.flags &= ~Entity.F_STATE_ENTERED
		e.frame_wait = 0
		e.want_dir = 8
		e.target_y = 6
		e.target_x = -0x91
		e.timer_a = 0
		e.timer_b = 0
	if e.timer_a == 100:
		var cup := sim.shadow
		if cup.timer_a == 100:
			cup.timer_a = 200
			cup.pass_ok = 0
			cup.flags |= Entity.F_BUSY
			Anim.set_animation(cup, 0xea9)
			e.flags4 &= ~Entity.F4_MIRROR
			e.frame = 0x165
			e.facing = 2
			e.pass_target = 0
			e.flags |= Entity.F_BUSY
			Anim.set_animation(e, 0xe83)
			Crowd.bench_cheer(sim, e.team)
			if e.roster_idx >= 0 and e.roster_idx < 28:
				sim.team_of(e).energy[e.roster_idx] = 0x800
			AI.default_skate(sim, e)
		return
	e.timer_a -= 1
	if e.timer_a < 0:
		e.timer_a += 8
		var dy := e.yi - e.target_y
		var dx := e.xi - e.target_x
		if absi(dy) < 5 and dx < 5:
			e.set_pos(e.target_x, e.target_y)
			e.vx = 0
			e.vy = 0
			Anim.set_animation(e, Anim.GLIDE)
			e.flags |= Entity.F_ARRIVED
			if e.facing != 6:
				e.facing = (e.facing + (1 if (e.facing < 7 and e.facing > 2) else -1)) & 7
			if e.facing == 6:
				e.timer_a = 100
			return
	if (e.flags & Entity.F_ARRIVED) == 0:
		AI.ref_skate_to_point(sim, e, e.target_x, e.target_y)

## ai_stanley_cup (0x4a832): the captain skates around with the cup over his head
static func stanley_cup(sim: Sim, e: Entity) -> void:
	if e.flags & Entity.F_BUSY:
		return
	if e.flags & Entity.F_STATE_ENTERED:
		e.flags &= ~Entity.F_STATE_ENTERED
		e.frame_wait = 0
		e.target_x = -0x50
		e.target_y = 0
		e.timer_a = 0
		e.pass_target = 0
		Anim.set_animation(e, 0xecb)
		sim.stoppage_timer = 0x100
	if e.anim == 0:
		if e.roster_idx >= 0 and e.roster_idx < 28:
			sim.team_of(e).energy[e.roster_idx] = 0x300
		Anim.set_animation(e, 0x833)
	var dir := Tables.direction8(e.target_x - e.xi, e.target_y - e.yi)
	if dir < 8:
		e.timer_a -= 1
		if e.timer_a < 0:
			e.timer_a += 0xc
			if e.facing != dir:
				e.facing = (e.facing + 1) & 7
		sim.skating_accelerate(e, dir)

# --------------------------------------------------------------------------------------------
# the three stars
# --------------------------------------------------------------------------------------------

## three_stars_sequence (0x48f0b, called start_period in older maps): after the game everybody
## leaves the ice and the referee presents the three stars
static func begin_three_stars(sim: Sim) -> void:
	compute_three_stars(sim)
	sim.stars_running = true
	sim.match_over = false
	InfoPanel.set_text(sim, ["", "", "", "", ""])
	sim.message = -1
	sim.ref_infraction = 0
	sim.whistle_timer = 0
	sim.penalty_box_mode = false
	sim.box_count = [0, 0]
	Rules.clear_infractions(sim)
	sim.period_over = false
	sim.intermission_camera = false
	sim.play_stopped = true
	sim.sequence_steps = STARS_STEPS
	sim.user1_slot = -1
	sim.user2_slot = -1
	for i in 12:
		var e: Entity = sim.entities[i]
		e.set_pos(-200, 0)
		e.target_x = -200
		e.target_y = 0
		e.timer_b = -100
		e.vx = 0
		e.vy = 0
		e.frame = -1
		e.next_line_slot = -1
		e.next_roster = -1
		Anim.set_animation(e, 0)
		e.state_sp = 0
		e.set_state(Entity.State.NONE)
		e.flags &= ~(Entity.F_BUSY | Entity.F_USER)
		e.flags2 |= Entity.F2_UNSELECTABLE
	sim.puck_stuck_timer = 0x78
	sim.puck.set_pos(200, -0x12c)
	sim.puck.vx = 0
	sim.puck.vy = 0
	sim.puck.state_sp = 0
	sim.puck.set_state(Entity.State.PUCK_IDLE)
	sim.shadow.set_pos(200, -0x12c)
	sim.shadow.vx = 0
	sim.shadow.vy = 0
	sim.shadow.state_sp = 0
	sim.shadow.set_state(Entity.State.PUCK_SHADOW)
	var ref := sim.referee
	ref.timer_a = 0
	ref.set_pos(-200, 0)
	ref.target_x = -200
	ref.target_y = 0
	ref.vx = 0
	ref.vy = 0
	Anim.set_animation(ref, 0)
	ref.frame = -1
	ref.state_sp = 0
	ref.set_state(Entity.State.REF_THREE_STARS)
	sim.ref_phase = 0
	sim.action_hold_camera = true
	sim.puck_carrier = -1
	sim.camera_x = -0x20
	sim.camera_target_x = -0x20
	sim.camera_y = 0
	sim.camera_target_y = 0
	sim.panel = -1
	InfoPanel.open(sim)
	sim.sort_draw_order()

## the period length setting (option_flags bits 10-11): 0 short, 1 medium, 2 long periods
static func period_setting(sim: Sim) -> int:
	if sim.period_length >= 1200:
		return 2
	if sim.period_length >= 600:
		return 1
	return 0

## compute_three_stars (0x48ac8): the overtime winner of a cup final, goalies with a shutout,
## skaters with two points or more (best first, see compare_player_stats), goalies with a save
## percentage above .924, then the best of the rest
static func compute_three_stars(sim: Sim) -> void:
	sim.stars = []
	sim.game_winner = Vector2i(-1, -1)
	var count := 0
	var home := sim.teams[0]
	var away := sim.teams[1]
	if sim.period > 2 and home.goals != away.goals:
		var win := 1 if away.goals > home.goals else 0
		if (sim.last_touch_slot < 6) != (win == 1):
			sim.game_winner = Vector2i(win, sim.teams[win].carrier_history[0])
			if game_over_check(sim, home.goals, away.goals):
				count += _add_star(sim, count, win, sim.game_winner.y)
	var setting := period_setting(sim)
	for t in 2:
		if sim.teams[1 - t].goals == 0:
			var gs: Array = sim.teams[t].goalie_stats
			var g := 1 if gs[0][1] < gs[1][1] else 0
			if gs[0][1] < gs[2][1] and gs[1][1] < gs[2][1]:
				g = 2
			if Tables.star_shutout_shots[setting] < gs[g][1]:
				count += _add_star(sim, count, t, 25 + g)
	var list := []
	for i in 50:
		var t := i / 25
		var r := i % 25
		var team := sim.teams[t]
		if not Lines.roster_exists(team, r):
			continue
		var s: PackedInt32Array = team.player_stats[r]
		var played := s[Team.ST_GOALS] != 0 or s[Team.ST_ASSISTS] != 0 or s[Team.ST_PIM] != 0 \
			or s[Team.ST_PLUS_MINUS] != 0 or s[Team.ST_SHOTS] != 0
		if team.entity_of[r] == -4 and not played:
			continue            # roster status 1: out for the game without a statistic
		list.append(i)
	list.sort_custom(func(a: int, b: int) -> bool: return compare_player_stats(sim, a, b) < 0)
	var k := 0
	var exhausted := false
	while true:
		if k >= list.size():
			exhausted = true
			break
		var t: int = list[k] / 25
		var r: int = list[k] % 25
		var s: PackedInt32Array = sim.teams[t].player_stats[r]
		if s[Team.ST_GOALS] + s[Team.ST_ASSISTS] < 2:
			break
		count += _add_star(sim, count, t, r)
		if count > 2:
			return
		k += 1
	if not exhausted:
		for g6 in 6:
			var t := g6 / 3
			var g := g6 % 3
			var gs: PackedInt32Array = sim.teams[t].goalie_stats[g]
			if Tables.star_save_shots[setting] <= gs[1] and (gs[2] * 1000 + gs[1] / 2) / gs[1] < 0x4c:
				count += _add_star(sim, count, t, 25 + g)
				if count > 2:
					return
	while k < list.size():
		count += _add_star(sim, count, list[k] / 25, list[k] % 25)
		if count > 2:
			return
		k += 1

## three_stars_add_unique: adds a star unless he already is one; returns 1 when added
static func _add_star(sim: Sim, count: int, team: int, roster: int) -> int:
	for i in count:
		var s: Array = sim.stars[i]
		if s[0] == team and s[1] == roster:
			return 0
	if count < sim.stars.size():
		sim.stars[count] = [team, roster]
	else:
		sim.stars.append([team, roster])
	return 1

## compare_player_stats (0x4883b): > 0 when b ranks before a. Points (2 extra for the overtime
## winner), goals, the winning team (only a home win counts, as in the original), shots, then the
## plus/minus, or for two players without a plus the one on the ice and the better ratings.
static func compare_player_stats(sim: Sim, a: int, b: int) -> int:
	var ta := a / 25
	var ra := a % 25
	var tb := b / 25
	var rb := b % 25
	var sa: PackedInt32Array = sim.teams[ta].player_stats[ra]
	var sb: PackedInt32Array = sim.teams[tb].player_stats[rb]
	var pa := sa[Team.ST_GOALS] + sa[Team.ST_ASSISTS]
	if ta == sim.game_winner.x and ra == sim.game_winner.y:
		pa += 2
	var pb := sb[Team.ST_GOALS] + sb[Team.ST_ASSISTS]
	if tb == sim.game_winner.x and rb == sim.game_winner.y:
		pb += 2
	if pa != pb:
		return pb - pa
	if sb[Team.ST_GOALS] != sa[Team.ST_GOALS]:
		return sb[Team.ST_GOALS] - sa[Team.ST_GOALS]
	if pa > 0 and ta != tb:
		var d := sim.teams[tb].goals - sim.teams[ta].goals
		if d != 0 and int(d > 0) != tb:
			return d
	if sb[Team.ST_SHOTS] != sa[Team.ST_SHOTS]:
		return sb[Team.ST_SHOTS] - sa[Team.ST_SHOTS]
	if sb[Team.ST_PLUS_MINUS] < 1 and sa[Team.ST_PLUS_MINUS] < 1:
		var ia := _on_ice(sim, ta, ra)
		var ib := _on_ice(sim, tb, rb)
		if ia != ib:
			return 1 if ib else -1
		return _rating_sum(sim, tb, rb) - _rating_sum(sim, ta, ra)
	return sb[Team.ST_PLUS_MINUS] - sa[Team.ST_PLUS_MINUS]

## player_entity_dressed: the player is on the ice at the end (not as the extra attacker)
static func _on_ice(sim: Sim, t: int, r: int) -> bool:
	if sim.teams[t].entity_of[r] < -1:
		return false
	for i in 6:
		var e: Entity = sim.entities[t * 6 + i]
		if e.roster_idx == r:
			return e.line_slot != 6
	return false

static func _rating_sum(sim: Sim, t: int, r: int) -> int:
	var team := sim.teams[t]
	if team.info == null:
		return 0
	var p: Database.Player = team.info.player(r)
	if p == null or p.ratings.size() < 14:
		return 0
	var sum := 0
	for i: int in [1, 2, 3, 4, 5, 6, 9, 10, 11, 13]:
		sum += p.ratings[i]
	return sum

## the caption of a star: "#77 Ray Bourque", shortened like format_player_name when it is long
static func star_caption(sim: Sim, t: int, r: int) -> String:
	var team := sim.teams[t]
	var p: Database.Player = team.info.player(r) if team.info != null else null
	if p == null:
		return "%s #%d" % [team.abbrev(), r]
	var s := "#%d %s %s" % [p.number, p.first, p.last]
	if s.length() > 20:
		s = "#%d %s. %s" % [p.number, p.first.left(1), p.last]
	if s.length() > 20:
		s = "#%d %s" % [p.number, p.last]
	return s

static func _announce_star(sim: Sim, index: int) -> void:
	sim.panel_text[1] = "%s Star" % Tables.star_names[index]
	var st: Array = sim.stars[index] if index < sim.stars.size() else [0, 0]
	sim.panel_text[2] = star_caption(sim, st[0], st[1])
	Speech.say(sim, Speech.star(index + 1, Speech.abbrev(sim, st[0]), Speech.number(sim, st[0], st[1])))

## ai_ref_three_stars (0x495b8), the hidden referee runs the presentation: the 3rd, 2nd and 1st
## star in turn come out of the bench (entity 5 for the home team, 6 for the away team), skate a
## lap and leave; then the game is over. It waits while the panel opens or closes.
static func ref_three_stars(sim: Sim, e: Entity) -> void:
	if not (sim.panel == -1 or (sim.panel > 0xf and (sim.panel < InfoPanel.CLOSING or sim.panel > 0x267))):
		return
	if e.flags & Entity.F_STATE_ENTERED:
		e.flags &= ~Entity.F_STATE_ENTERED
		InfoPanel.set_text(sim, ["EA Sports", "", "", "", ""])
		e.timer_a = mini(2, sim.stars.size() - 1)        # the star to present (2 = 3rd)
		e.timer_b = sim.random(0x14) + 0x14            # +0x28 in the original
		e.target_x = -1                                # the entity of the star on the ice
		if e.timer_a >= 0:
			_announce_star(sim, e.timer_a)
	e.timer_b -= 1
	if e.timer_b >= 1:
		return
	if e.timer_a < 0:
		sim.sequence_steps = 0
		sim.period_over = true
		sim.stars_running = false
		sim.match_over = true
		return
	var star: Entity = sim.entities[e.target_x] if e.target_x >= 0 else null
	if star == null or star.timer_a != 100 or star.frame != -1:
		if e.timer_b >= 0:
			var st: Array = sim.stars[e.timer_a]
			var slot := 6 if st[0] != 0 else 5
			e.target_x = slot
			var p: Entity = sim.entities[slot]
			sim.crowd_noise = 700 if (p.flags & Entity.F_PLAYER2) else 0x5dc
			var roster: int = st[1]
			p.roster_idx = roster
			p.line_slot = 4 if roster < 25 else 0
			p.timer_a = 0
			p.next_roster = -1
			p.next_line_slot = -1
			var team := sim.teams[st[0]]
			team.energy[roster] = 0x300
			e.flags2 &= ~Entity.F2_UNSELECTABLE
			sim.put_player_on_ice(p, roster)
			p.flags2 &= ~Entity.F2_UNSELECTABLE
			p.state_sp = 0
			p.set_state(Entity.State.NONE)
			p.set_state_reset(Entity.State.GAME_MISCONDUCT)
			p.set_state_reset(Entity.State.THREE_STARS)
			p.set_state_reset(Entity.State.EXIT_BENCH)
		return
	e.timer_b = sim.random(0x1e) + 0x14
	e.target_x = -1
	e.timer_a -= 1
	if e.timer_a >= 0:
		_announce_star(sim, e.timer_a)
	else:
		sim.panel = InfoPanel.CLOSING

## ai_three_stars (0x49460): a lap of honour along four points; a star of the winning home team
## raises his stick at one of them; after the lap the state below (ai_game_misconduct) takes him
## off the ice
static func three_stars(sim: Sim, e: Entity) -> void:
	if e.flags & Entity.F_BUSY:
		return
	var side := 1 if (e.flags & Entity.F_PLAYER2) else 0
	if e.flags & Entity.F_STATE_ENTERED:
		e.flags &= ~Entity.F_STATE_ENTERED
		e.timer_b = 0
		e.want_dir = 8
		if e.line_slot == 0 or side != 0 or sim.teams[0].goals <= sim.teams[1].goals:
			e.timer_a = -1
		else:
			e.timer_a = sim.random(8)
		var wp: Array = Tables.star_laps[side][0]
		e.target_x = wp[0]
		e.target_y = wp[1]
	var dx := e.xi - e.target_x
	var dy := e.yi - e.target_y
	if dx * dx + dy * dy < 900:
		e.timer_b += 1
		if e.timer_b > 3:
			AI.default_skate(sim, e)
			return
		var wp: Array = Tables.star_laps[side][e.timer_b]
		e.target_x = wp[0]
		e.target_y = wp[1]
		if e.timer_a == e.timer_b:
			e.flags |= Entity.F_BUSY
			Anim.set_animation(e, 0x731)
			return
	_steer(sim, e)

## three_stars_skate_to_spot: re-aims every 12 steps at the target (ahead of the own momentum); stops near it and
## turns to face it
static func _steer(sim: Sim, e: Entity) -> void:
	e.dir_timer -= 1
	if e.dir_timer < 0:
		e.dir_timer += 0xc
		var tx := e.target_x - Entity.to_s8(e.vx >> 8) - e.xi
		var ty := e.target_y - Entity.to_s8(e.vy >> 8) - e.yi
		var dir := 9
		if absi(tx) >= 0xd or absi(ty) >= 0xd:
			dir = Tables.direction8(tx, ty)
		e.want_dir = dir
		if dir > 7 and e.vx == 0 and e.vy == 0:
			var d := Tables.direction8(e.target_x - e.xi, e.target_y - e.yi)
			var diff := e.facing - d
			if diff != 0:
				e.facing = (e.facing + (((diff & 7) & 4) >> 1) - 1) & 7
	_skate(sim, e, e.want_dir)

## three_stars_skate_dir: skate in a direction (one facing step per call), brake on 9, glide otherwise
static func _skate(sim: Sim, e: Entity, dir: int) -> void:
	if e.line_slot == 0:
		sim.goalie_move(e, dir)
		return
	dir &= 0xf
	if dir < 8:
		var diff := dir - e.facing
		if diff != 0:
			e.facing = (e.facing + ((((-diff) & 7) & 4) >> 1) - 1) & 7
		Anim.set_animation(e, Anim.SKATE)
		sim.skating_accelerate(e, e.facing)
	elif dir == 9 and (e.vx != 0 or e.vy != 0):
		sim.brake(e)
	elif (e.flags2 & Entity.F2_TURNING) == 0:
		Anim.set_animation(e, Anim.GLIDE)
