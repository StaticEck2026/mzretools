class_name PuckLogic
## Everything that happens between the puck and the players: carrying, picking up, deflections,
## goalie saves, passes, shots, body checks and hooks. Ports of puck_update, update_carrier,
## puck_check_players, puck_player_interaction, goalie_save, puck_hits_player, attach_puck_to_stick,
## do_pass, pass_lead (pass lead), start_shot, shot_control, do_shot, body_check, hook_button and
## the collision resolution of collide_pair (resolve_body_check, knock_down).

# --------------------------------------------------------------------------------------------
# puck state (ai_puck_normal -> puck_update)
# --------------------------------------------------------------------------------------------

static func puck_update(sim: Sim) -> void:
	var puck := sim.puck
	sim.puck_goal_timer -= 1
	if sim.puck_goal_timer < 0:
		sim.puck_goal_timer += 5
		predict_goal_line(sim)
	if sim.puck_carrier >= 0:
		var c := sim.entities[sim.puck_carrier]
		update_carrier(sim, c)
		# the puck eases towards the stick blade of the carrier
		var o := Tables.frame_offset(c.frame, (c.flags4 & Entity.F4_MIRROR) != 0)
		var tx := c.xi + o.x
		var ty := c.yi + o.y
		puck.x = (puck.xi + ((tx - puck.xi) >> 2)) << 16 | (puck.x & 0xffff)
		puck.y = (puck.yi + ((ty - puck.yi) >> 2)) << 16 | (puck.y & 0xffff)
		puck.vx = c.vx
		puck.vy = c.vy
	Rules.check_icing(sim)
	Rules.check_offside(sim)
	Rules.update_offside_flags(sim)
	if not sim.play_stopped:
		if sim.puck_carrier < 0:
			# penalty shot: a loose puck that keeps moving away from the net for 30 steps ends it
			var up := sim.teams[sim.penalty_shot_team].attacks_up
			if sim.penalty_shot and ((up and puck.vy <= 0) or (not up and puck.vy >= 0)):
				sim.penalty_shot_away += 1
				if sim.penalty_shot_away > 0x1d:
					Rules.end_penalty_shot(sim)
					sim.penalty_shot_away = 0
			else:
				sim.penalty_shot_away = 0
			# a puck that does not move for 0x78 steps (behind the net, in a corner) is frozen
			if puck.xi == puck.prev_x >> 16 and puck.yi == puck.prev_y >> 16:
				if not (absi(puck.xi) < 0xa3 and absi(puck.yi) < 0x10e and sim.teams[0].nearest_dist > 0x14 and sim.teams[1].nearest_dist > 0x14):
					sim.puck_stuck_timer -= 1
					if sim.puck_stuck_timer < 0:
						Rules.queue_infraction(sim, puck, Rules.INF_FROZEN)
				else:
					sim.puck_stuck_timer = 0x78
			else:
				sim.puck_stuck_timer = 0x78
		else:
			sim.penalty_shot_away = 0
			sim.puck_stuck_timer = 0x78
	# frame selection: a slow, low puck shows the flat disc, otherwise the rolling frames
	if absi(puck.vz) < 0x100 and puck.timer_c == 0:
		puck_flat(sim, puck)
	puck_check_players(sim)

## predict_puck_goal_line (0x5a3a2): where and when the puck crosses each goal line
static func predict_goal_line(sim: Sim) -> void:
	var puck := sim.puck
	for i in 2:
		var gy := 0xe8 if i == 0 else -0xe8
		var pred: Array = sim.goal_prediction[i]
		if puck.vy == 0:
			pred[1] = -1
			continue
		var steps := ((gy - puck.yi) << 12) / puck.vy
		if steps < 0 or steps > 0xffff:
			pred[1] = -1
			continue
		pred[1] = steps
		var dx := (puck.vx * (gy - puck.yi)) / puck.vy
		if dx > 0xffff:
			pred[1] = -1
			continue
		var px := dx + puck.xi
		if px > 0x9f:
			px = 0x140 - px
		if px < -0x9f:
			px = -0x140 - px
		pred[0] = px

## update_carrier (0x4de14): bookkeeping of who carries the puck, icing and two line pass set up
static func update_carrier(sim: Sim, c: Entity) -> void:
	var in_zone := carrier_in_offensive_zone(sim, c)
	if not in_zone and not sim.play_stopped:
		sim.last_touch_x = c.xi
		sim.last_touch_y = c.yi
		sim.last_touch_slot = c.slot
	var team := sim.team_of(c)
	if team.carrier_history[0] != c.roster_idx:
		team.carrier_history[2] = team.carrier_history[1]
		team.carrier_history[1] = team.carrier_history[0]
		team.carrier_history[0] = c.roster_idx
	if c.line_slot != 0:
		sim.shot_in_flight = false
	if not offside_entry_check(sim, c) and in_zone:
		Rules.maybe_queue_infraction(sim, c, Rules.INF_TWO_LINE)
	# icing candidate: the puck is shot from the own half (dword_e9abe)
	sim.icing_shooter = c.slot
	var own_half := c.yi if (c.flags & Entity.F_ATTACK_UP) else -c.yi
	sim.icing_flags = 2 if (c.flags & Entity.F_ATTACK_UP) else 0
	if own_half < 0:
		var diff := sim.teams[0].skaters_on_ice - sim.teams[1].skaters_on_ice
		if c.flags & Entity.F_PLAYER2:
			diff = -diff
		if diff >= 0:          # no icing for the short handed team
			sim.icing_flags |= 4

## carrier_zone_entry: the carrier entered the offensive zone with team mates already inside
static func carrier_in_offensive_zone(sim: Sim, c: Entity) -> bool:
	if sim.no_stats or not sim.opt_two_line_pass:
		return false
	var puck := sim.puck
	var in_front := (puck.yi > 0) == ((c.flags & Entity.F_ATTACK_UP) != 0)
	if (c.flags2 & Entity.F2_OFFSIDE) == 0 and not in_front:
		return false
	if c.slot == sim.last_touch_slot or not sim.same_team(sim.last_touch_slot, c.slot) or sim.last_touch_slot < 0:
		return false
	if c.flags & Entity.F_ATTACK_UP:
		return sim.last_touch_y < -0x4d and c.yi >= 0
	return sim.last_touch_y > 0x4d and c.yi <= 0

## offside_entry_check: offside when the carrier crosses the blue line with the flag set
static func offside_entry_check(sim: Sim, c: Entity) -> bool:
	if not sim.opt_offsides or sim.penalty_shot:
		return false
	var py := sim.puck.yi if (c.flags & Entity.F_ATTACK_UP) else -sim.puck.yi
	if py > 0x4d and (sim.team_of(c).flags & Team.FL_OFFSIDE) and not sim.no_stats:
		Rules.maybe_queue_infraction(sim, c, Rules.INF_OFFSIDE)
		return true
	return false

## puck_check_players (0x4d94c): the puck against every skater and the referee near its row
static func puck_check_players(sim: Sim) -> void:
	var puck := sim.puck
	if absi(puck.yi) > 400:
		puck.vx = 0
		puck.vy = 0
	if puck.zi > 0x10:
		return      # too high to be played
	for i in 17:
		if i >= 12 and i != Entity.Slot.REFEREE:
			continue
		var e := sim.entities[i]
		if e.line_slot < 0 and i != Entity.Slot.REFEREE:
			continue
		if absi(e.yi - puck.yi) >= 0x29:
			continue
		puck_player_interaction(sim, e)

## puck_player_interaction (0x5428a): pick up, deflect or save the puck
static func puck_player_interaction(sim: Sim, e: Entity) -> void:
	var puck := sim.puck
	if e.slot == sim.puck_carrier or (e.slot >= 12 and e.slot != Entity.Slot.REFEREE):
		return
	if (e.flags & Entity.F_ARRIVED) or e.timer_c != 0:
		return
	var mirrored := (e.flags4 & Entity.F4_MIRROR) != 0
	if (e.flags2 & Entity.F2_UNSELECTABLE) == 0 and e.line_slot == 0 and puck.zi <= 5 and puck.vz <= 0x200:
		# goalie: the pads and glove cover an area of 15 around the body
		var o := Tables.frame_offset(e.frame, mirrored)
		var dx := o.x + e.xi - puck.xi
		if absi(dx) < 0xf:
			var dy := o.y + e.yi - puck.yi
			if absi(dy) < 0xf:
				var d2 := dx * dx + dy * dy
				var reach := 0x31 if e.timer_c > 0 else 0xc4
				if d2 <= reach and (e.anim < 0x430 or e.anim > 0x44f or d2 < 0x25):
					goalie_save(sim, e)
					return
	elif (e.flags2 & Entity.F2_UNSELECTABLE) == 0 and e.line_slot > 0 and e.slot != Entity.Slot.REFEREE:
		# skater: the stick reach grows with the stickhandling skill and shrinks with the puck speed
		var skill := stickhandling_skill(e)
		var speed := maxi(1, absi(puck.vx) + absi(puck.vy))
		var reach := clampi((skill * 0x800 - 4000) / speed, 0, 4)
		var so := Tables.stick_offset(e.frame, mirrored)
		var fo := Tables.frame_offset(e.frame, mirrored)
		var sx := so.x - fo.x
		var sy := so.y - fo.y
		var rx := ((absi(sx) << 2) / 3)
		var ry := ((absi(sy) << 2) / 3)
		var limit := absi(sx) + reach
		var dx := fo.x + e.xi - puck.xi
		if absi(dx) < limit:
			var dy := fo.y + e.yi - puck.yi
			if absi(dy) < limit:
				var zlim := maxi(5, rx + absi(sy)) + reach
				var zlow := absi(sy) - rx - reach
				if puck.zi <= zlim and (zlow < 0 or zlow < puck.zi):
					var d2 := dx * dx + dy * dy
					var r2 := limit * limit
					if e.timer_c > 0:
						r2 >>= 2
					if d2 <= r2:
						Rules.two_line_pass_check(sim, e)
						goalie_save(sim, e)   # the shared "player gets the puck" path
						return
	if e.line_slot == 0:
		# a loose puck bumping into the goalie's body
		var dx := e.xi - puck.xi
		if absi(dx) < 0xb:
			var dy := e.yi - puck.yi
			if absi(dy) < 0xb and dx * dx + dy * dy < 0x65:
				Rules.two_line_pass_check(sim, e)
				puck_hits_player(sim, e)
		return
	# body contact with a skater: the puck sticks to the stick when it is low and slow enough,
	# a hard shot knocks the player down
	var is_slow := e.anim >= 0x431 and e.anim <= 0x44f and (e.anim & 1) and puck.zi <= 7
	var low := puck.zi < 9
	var near_x := 8
	var near_d := 0x40
	if e.anim > 0x44f:
		near_x = 0x10
		near_d = 0x100
	var ddx := e.xi - puck.xi
	var ddy := e.yi - puck.yi
	if is_slow:
		var so := Tables.stick_offset(e.frame, mirrored)
		var hx := so.x >> 1
		var hy := so.y >> 1
		var rr := absi(hx)
		var cx := hx + ddx
		var cy := hy + ddy
		if absi(cx) <= rr and absi(cy) <= rr and cx * cx + cy * cy <= rr * rr:
			attach_puck_to_stick(sim, e)
			return
	if absi(ddx) <= near_x and absi(ddy) <= near_x and ddx * ddx + ddy * ddy <= near_d:
		attach_puck_to_stick(sim, e)

## stickhandling_skill (0x5414e): which rating applies to the current animation
static func stickhandling_skill(e: Entity) -> int:
	var a := e.anim
	if a == 0xb1 or a == 0xc9 or a == 0xe1 or a == 0x11d5:
		return e.check_skill if e.left_handed else e.pass_skill
	if a == 0x101 or a == 0x119 or a == 0x121d:
		return e.endurance if e.left_handed else e.offense
	return e.shot_skill

## goalie_save (0x574ba): a player (usually the goalie) gets to the puck; a hard shot may be
## stopped and dropped, otherwise the puck is taken
static func goalie_save(sim: Sim, e: Entity) -> void:
	var puck := sim.puck
	if e.line_slot == 0:
		if sim.no_stats:
			return
		e.save_result = 0
		var save := false
		if sim.shot_in_flight and (e.flags & Entity.F_PLAYER2) == 0 or sim.shot_in_flight:
			if sim.last_shooter >= 0 and not sim.same_team(sim.last_shooter, e.slot):
				var shooter := sim.entities[sim.last_shooter]
				if absi(shooter.yi) > 0x58 and ((e.flags & Entity.F_ATTACK_UP) != 0) != (shooter.yi > 0):
					var vy := absi(puck.vy)
					if vy >= 0x2ee1 or (vy >= 0x1771 and e.anim >= 0x119d and e.anim <= 0x121d):
						save = true
		shot_landed(sim)
		if save:
			e.save_result = 1
	e.flags &= ~Entity.F_HAS_TARGET
	if sim.puck_carrier < 0:
		var v2 := puck.vx * puck.vx + puck.vy * puck.vy
		var hold := 13000
		if not sim.shot_in_flight:
			hold += e.goalie_skill * 700
		var hold2 := hold * hold
		if e.anim < 0x13c5 or e.anim > 0x14ad:
			if v2 <= hold2 or (e.slot == sim.pass_target and sim.random(2) != 0):
				# controlled: the player takes the puck
				puck.vz = 0
				take_puck(sim, e)
				if e.line_slot != 0:
					return
				if puck.zi > 8:
					puck.z = 8 << 16
				puck.vx >>= 2
				puck.vy >>= 2
				return
		# too hot to handle: it rebounds
		e.timer_c = 8
	else:
		# stealing the puck from the carrier
		if e.anim >= 0x13c5 and e.anim <= 0x14ae:
			return
		var c := sim.entities[sim.puck_carrier]
		if (c.flags & Entity.F_PLAYER2) == (e.flags & Entity.F_PLAYER2):
			return
		if c.puck_dist_sq > 0x24:
			return
		if e.line_slot != 0:
			if c.line_slot == 0:
				return
			var cs := (c.energy * c.check_skill >> 12) + 0x20
			var es := (e.energy * e.check_skill >> 12)
			var chance := cs - es
			if (c.flags & Entity.F_USER) and (e.flags & Entity.F_USER) == 0:
				chance += chance >> 3
			if sim.random(maxi(1, chance)) > 2:
				return
		c.timer_c = (c.energy * c.check_skill >> 12) + 0x14
		e.timer_c = (e.energy * e.check_skill >> 12) + 0x14
		sim.last_passer = c.slot
		sim.action_pass = false
		sim.action_shot = false
	sim.play_sfx(0x99)
	update_carrier(sim, e)
	release_puck_random(sim)

## puck_hits_player (0x57268): deflection off a body
static func puck_hits_player(sim: Sim, e: Entity) -> void:
	var puck := sim.puck
	if sim.no_stats:
		return
	var dx := e.xi - puck.xi
	var dy := e.yi - puck.yi
	var from_dir := Tables.direction8(-dx, -dy)
	var rel := (from_dir - e.facing) & 7
	var low := puck.zi < 9
	if (e.anim < 0x206 or e.anim > 0x215) or puck.zi < 5:
		e.save_result = 0
		if sim.shot_in_flight and sim.last_shooter >= 0 and not sim.same_team(sim.last_shooter, e.slot):
			var shooter := sim.entities[sim.last_shooter]
			if absi(shooter.yi) > 0x58 and (shooter.yi > 0) != ((e.flags & Entity.F_ATTACK_UP) != 0):
				var sp := absi(puck.vx) + absi(puck.vy)
				if sp > 17000 or (sp > 6000 and e.anim >= 0x119d and e.anim <= 0x121d):
					e.save_result = 1
		shot_landed(sim)
		update_carrier(sim, e)
		if not sim.play_stopped and absi(puck.vy) > 4000:
			sim.play_sfx(0xa1 if (e.flags & Entity.F_PLAYER2) else 0x7d)
		sim.play_sfx(0xa3 if absi(puck.vy) < 0xbb9 else 0x9d)
		if sim.puck_carrier < 0:
			var limit := (sim.random((((e.shot_skill * 5) >> 2) + 2) * 0x200) + 0x2000)
			if absi(puck.vx) <= limit and absi(puck.vy) <= limit and (e.flags2 & Entity.F2_UNSELECTABLE) == 0:
				puck.vz = 0
				if puck.zi > 8:
					puck.z = 8 << 16
				puck.vx >>= 2
				puck.vy >>= 2
				take_puck(sim, e)
				return
		else:
			var c := sim.entities[sim.puck_carrier]
			sim.puck_carrier = -1
			c.timer_c = 0x14
			sim.last_passer = c.slot
			sim.action_pass = false
			sim.action_shot = false
		puck.vz = 0
		if puck.zi > 10:
			puck.z = 10 << 16
		e.timer_c = 10
		e.timer_b = 4
		var ox := dx
		var oy := dy
		if oy == 0:
			oy = 1
		if ((oy << 16) ^ (puck.vy << 16)) >= 0:
			oy = -oy
		puck.vx = (ox >> 1) << 8 | (puck.vx & 0xff)
		puck.vy = (oy >> 1) << 8 | (puck.vy & 0xff)
		puck_spin(sim, puck, ox)

## attach_puck_to_stick (0x579c6): the puck meets a skater's body / stick
static func attach_puck_to_stick(sim: Sim, e: Entity) -> void:
	var puck := sim.puck
	var low := puck.zi < 9
	if puck.frame < 0x430 or puck.frame > 0x467:
		if low and (puck.vx & 0xf) != 0:
			return
	elif puck.frame < 0x450 and (puck.frame & 1) and not low:
		return
	if e.slot != Entity.Slot.REFEREE:
		update_carrier(sim, e)
	puck.vz = 0
	e.timer_c = 8
	var vx := puck.vx
	var vy := puck.vy
	# the high bytes of the velocity: the puck's offset from the skater (with none in y the offset
	# of the skater's frame)
	var dx := puck.xi - e.xi
	var dy := puck.yi - e.yi
	if dy == 0:
		var o := Tables.frame_offset(e.frame, (e.flags4 & Entity.F4_MIRROR) != 0)
		dx = o.x
		dy = o.y
	puck.vx = Sim._s16((dx << 8) | (puck.vx & 0xff))
	puck.vy = Sim._s16((dy << 8) | (puck.vy & 0xff))
	puck_spin(sim, puck, dx)
	if low:
		if e.anim != 0x84b:
			sim.play_sfx(0xa3)
		return
	var sfx := 0xa3
	if vx * vx + vy * vy > 9000000 and puck.zi > 0xc:
		sfx = 0xa2
		knock_down(sim, puck, e)
	if e.anim != 0x84b:
		sim.play_sfx(sfx)
	if (e.flags & Entity.F_BUSY) == 0 and e.slot != Entity.Slot.REFEREE:
		e.flags |= Entity.F_BUSY
		Anim.set_animation(e, 0x84b)    # stung by the puck

## take_puck: a player becomes the carrier
static func take_puck(sim: Sim, e: Entity) -> void:
	sim.puck_carrier = e.slot
	var team := sim.team_of(e)
	var opp := sim.opponents_of(e)
	if sim.penalty_shot and e.roster_idx == team.carrier_history[0]:
		# the shooter plays the puck a second time (a rebound): the penalty shot is over
		Rules.end_penalty_shot(sim)
		sim.one_timer = false
		sim.breakaway = false
	opp.carrier_history[1] = -1
	opp.carrier_history[2] = -1
	opp.flags |= 8
	if not sim.misc_first_touch:
		sim.play_sfx(0x9b)
	else:
		sim.misc_first_touch = false
		if not sim.no_stats:
			team.faceoffs_won += 0
		sim.add_crowd(200, 1000)
		if (e.flags & Entity.F_PLAYER2) == 0:
			sim.excitement += 10
	if e.slot == sim.pass_target and not sim.no_stats:
		team.passes_completed += 1
	sim.pass_target = -1
	sim.action_pass = false
	sim.action_shot = false
	if e.line_slot == 0:
		shot_landed(sim)
		Rules.end_penalty_shot(sim)
		e.timer_b = 5 if e.anim == 0x181 else 0x8c   # time until the goalie must play the puck
	# follow_puck_user_switch: the user follows the puck to the new carrier of his team
	if e.slot != sim.user1_slot and e.slot != sim.user2_slot:
		var t := e.team + 1
		if sim.user1_team == t and sim.user1_slot >= 0:
			sim.user1_slot = sim.find_switch_target(e.slot, sim.user1_slot)
		elif sim.user2_team == t and sim.user2_slot >= 0:
			sim.user2_slot = sim.find_switch_target(e.slot, sim.user2_slot)

## shot_landed: a shot reached a player or the net: shot statistics
static func shot_landed(sim: Sim) -> void:
	if not sim.shot_in_flight:
		return
	sim.shot_in_flight = false
	if sim.play_stopped or sim.last_shooter < 0:
		return
	var s := sim.entities[sim.last_shooter]
	if (sim.puck.yi > 0) == ((s.flags & Entity.F_ATTACK_UP) != 0):
		sim.add_crowd(100, 1000)
		sim.excitement += 10
		if not sim.no_stats:
			var team := sim.team_of(s)
			team.shots += 1
			team.add_stat(s.roster_idx, Team.ST_SHOTS)
			var opp := sim.opponents_of(s)
			if sim.power_play and opp.skaters_on_ice < team.skaters_on_ice:
				team.pp_shots += 1
			sim.gs_trailer[2 + team.index * 2] += 1
			var g := opp.goalie_index()
			if g >= 0:
				opp.goalie_stats[g][1] += 1

## release_puck_random: the puck squirts away from a failed take
static func release_puck_random(sim: Sim) -> void:
	sim.puck_carrier = -1
	var puck := sim.puck
	puck.vy = sim.random(0x2000) - 0x1000
	puck.vx = sim.random(0x2000) - 0x1000
	puck.vz = sim.random(0x1000)
	puck_spin(sim, puck, puck.vz)

## puck_spin / puck_flat: puck frame bookkeeping (flat disc vs rolling)
## a: the value in scratch_a of the caller (its low bit flips the spin)
static func puck_spin(sim: Sim, puck: Entity, a: int) -> void:
	# the original adds the two velocity words (+0xc, +0xe) as they are
	if puck.vx + puck.vy < 0x14:
		puck_flat(sim, puck)
		return
	puck.flags3 = ((a & 1) ^ puck.flags3) & 3
	puck.anim_hold = -1
	Anim.set_animation(puck, 0x239)

static func puck_flat(_sim: Sim, puck: Entity) -> void:
	if puck.anim_pos > 3 and puck.anim_pos < 0xc:
		puck.flags3 ^= 2
	puck.flags3 |= 4
	puck.anim_pos = 0
	puck.anim_hold = -1

## net_push_off (0x54990): now and then (1 in 32) a skater hitting the net hard (a velocity word
## over 0x1b58) with the puck near it knocks the net off its pegs: the net takes a quarter of his
## velocity, he stops and the whistle goes (infraction 0x1e)
static func net_push_off(sim: Sim, e: Entity, net: Entity) -> bool:
	if sim.random(0x20) != 0:
		return false
	if absi(Sim._s16(sim.puck.yi - net.yi)) > 0x28:
		return false
	if absi(e.vx) < 0x1b59 and absi(e.vy) < 0x1b59:
		return false
	net.vx = e.vx >> 2
	net.vy = e.vy >> 2
	e.vx = 0
	e.vy = 0
	sim.action_hold_camera = true
	if not sim.play_stopped:
		Rules.queue_infraction(sim, e, Rules.INF_NET_OFF)
	return true

# --------------------------------------------------------------------------------------------
# passing (pass_button, do_pass, pass_to_entity, pass_lead)
# --------------------------------------------------------------------------------------------

## pass_button (0x50a1a): the pass goes out in the direction held when A is released
static func pass_button(sim: Sim, e: Entity, control: int, _pressed: int) -> void:
	if (control & 0x10) == 0:
		if control & 8:
			sim.pending_dir = e.facing
		else:
			sim.pending_dir = control & 7
		do_pass(sim, e)
		return
	# still held: keep aiming
	if (control & 8) == 0:
		sim.pending_dir = control & 7

## do_pass (0x54df4): find a receiver in the aimed direction, otherwise a blind pass
static func do_pass(sim: Sim, e: Entity) -> void:
	var puck := sim.puck
	sim.one_timer = false
	sim.action_pass = false
	sim.puck_carrier = -1
	e.timer_c = 0x10
	sim.last_passer = e.slot
	if (e.flags & Entity.F_USER) == 0 and e.pass_ok != 0 and e.pass_target >= 0:
		pass_to_entity(sim, e, sim.entities[e.pass_target])
		return
	var power := (8 if e.line_slot == 0 else e.pass_skill) * 4 + 0xa0
	var best: Entity = null
	var best_d := 0x7fffffff
	var first := sim.team_of(e).first_slot
	for i in 6:
		var p := sim.entities[first + i]
		if p == e or p.line_slot <= 0 or (p.flags2 & Entity.F2_UNSELECTABLE):
			continue
		var dx := p.xi - puck.xi
		var dy := p.yi - puck.yi
		var d := (Tables.direction8(dx, dy) - sim.pending_dir) & 7
		if d < 2 or d == 7:
			var score := dy * dy + dx * dx + (0 if d == 0 else 0x10000)
			if score <= best_d:
				best_d = score
				best = p
	if best == null:
		var v: Array = Tables.dir8_vectors[sim.pending_dir & 7]
		puck.vy = (v[1] * power * 0x400) / 3000 + e.vy
		puck.vx = (v[0] * power * 0x400) / 3000 + e.vx
		puck.vz = sim.random(0x1000)
	else:
		if (e.flags & Entity.F_USER) and pass_lane_ok(sim, e, best):
			pass_to_entity(sim, e, best)
			return
		pass_lead(sim, e, best)
	var a := 0
	if e.line_slot == 0:
		# the goalie clears towards his own blue line
		if (puck.vy < 0) != ((e.flags & Entity.F_ATTACK_UP) == 0):
			puck.vy = -puck.vy
		a = 0x1b9
		e.flags2 |= Entity.F2_TURNING
		if e.flags & Entity.F_USER:
			var player := 0 if e.slot == sim.user1_slot else 1
			if best == null or (best.flags & Entity.F_USER):
				sim.switch_to_nearest(e, player)
			elif player == 0:
				sim.user1_slot = sim.find_switch_target(best.slot, sim.user1_slot)
			else:
				sim.user2_slot = sim.find_switch_target(best.slot, sim.user2_slot)
	else:
		var d := Tables.direction8(puck.vx, puck.vy)
		a = 0x3c1 if shot_is_backhand(e, d) else 0x389
	Anim.set_animation(e, a)
	e.flags |= Entity.F_BUSY
	sim.play_sfx(0x99 if puck.vz > 0x500 else 0x98)

## pass_to_entity (0x5516a): the receiver skates onto a soft pass
static func pass_to_entity(sim: Sim, e: Entity, target: Entity) -> void:
	e.timer_c = 0x28
	if not sim.no_stats:
		sim.team_of(e).passes += 1
	sim.pass_target = target.slot
	e.pass_ok = 0
	target.set_state_reset(Entity.State.PASS_RECEIVER)
	var spread := (0x12 - e.pass_skill) * 0x14
	sim.puck.vz = 0
	sim.puck.vx = sim.random(spread)
	sim.puck.vy = sim.random(spread)

## pass_lead: lead the pass to where the receiver will be
static func pass_lead(sim: Sim, e: Entity, target: Entity) -> void:
	var puck := sim.puck
	if not sim.no_stats:
		sim.team_of(e).passes += 1
	sim.pass_target = target.slot
	target.set_state_reset(Entity.State.PASS_RECEIVER)
	var o := Tables.frame_offset(target.frame, (target.flags4 & Entity.F4_MIRROR) != 0)
	var dx := o.x + target.xi - puck.xi
	var dy := o.y + target.yi - puck.yi
	var tvx := (target.vx * 0xf0) >> 16
	var tvy := (target.vy * 0xf0) >> 16
	var speed := (e.pass_skill * 4 + 0xa0) >> 2
	# solve for the flight time t (in 4 step units) of a pass at `speed` meeting the receiver
	var qx := dx >> 2
	var qy := dy >> 2
	var b := (tvx * qx + tvy * qy) * 2
	var a := (tvx * tvx + tvy * tvy) - speed * speed
	var disc := b * b - 4 * (qx * qx + qy * qy) * a
	var root := Sim.isqrt(disc) if disc > 0 else 0
	a >>= 2
	if a == 0:
		a = 1
	var t := (root - b) / a
	if t < 0:
		t = (-root - b) / a
	t = clampi(t, 1, 0x18)
	var h := mini(t, 12)
	if h > 6:
		h = sim.random(h / 2) + (h + 1) / 2
	puck.vz = h << 8
	target.react_timer = t * 8 - 10
	var lx := ((tvx * t) >> 1) + dx
	var ly := ((tvy * t) >> 1) + dy
	target.target_x = puck.xi + lx
	target.target_y = puck.yi + ly
	var tt := t * 0x78
	puck.vx = (lx << 16) / tt
	puck.vy = (ly << 16) / tt

## pass_lane_ok: is the lane to the receiver open enough for a direct pass
static func pass_lane_ok(sim: Sim, e: Entity, target: Entity) -> bool:
	if e.line_slot == 0:
		return false
	if Rules.count_defenders_ahead(sim):
		return false
	var up := (e.flags & Entity.F_ATTACK_UP) != 0
	var ey := e.yi
	var ty := target.yi
	var line := 0x4e if up else -0x4e
	if (ey > line) != up:
		return false
	if absi(ty) >= absi(ey) or absi(ey) >= 0x77:
		return false
	if up and (target.vy < 0 or e.vy < 0):
		return false
	if not up and (target.vy > 0 or e.vy > 0):
		return false
	if absi(ty - ey) >= 0x3d or absi(e.xi - target.xi) >= 0x29:
		return false
	var tdir := Tables.direction8(target.vx, target.vy)
	if tdir == 8:
		tdir = target.facing
	var rdir := Tables.direction8(e.xi - target.xi, e.yi - target.yi)
	return ((tdir - rdir + 1) & 7) < 3

# --------------------------------------------------------------------------------------------
# shooting (start_shot, shot_control, do_shot, shot_setup)
# --------------------------------------------------------------------------------------------

## start_shot (0x5786e): wind up towards the net; the power grows while B is held
static func start_shot(sim: Sim, e: Entity) -> void:
	sim.pending_dir = 8
	sim.action_shot = true
	var target_y := 0xf0 if (e.flags & Entity.F_ATTACK_UP) else -0xf0
	var dir := Tables.direction8(-e.xi, target_y - e.yi)
	sim.shot_power = 0xf
	# the player is not "busy" during the wind up: shot_control runs every step until the release
	Anim.set_animation(e, Anim.SHOT_BACKHAND if shot_is_backhand(e, dir) else Anim.SHOT_FOREHAND)

## shot_control (0x50a9f): per step while the shot animation plays. A tap releases a quick wrist
## shot, holding B through the wind up makes it a harder slap shot; A or C cancel into a deke.
static func shot_control(sim: Sim, e: Entity, control: int, pressed: int) -> void:
	if e.anim_pos > 0xd:
		do_shot(sim, e)
		return
	if (control & 8) == 0:
		sim.pending_dir = control & 7
	if e.anim_pos < 10:
		if pressed & 0x50:
			# fake: skate on with the puck
			sim.action_shot = false
			e.flags |= Entity.F_BUSY
			match e.anim:
				Anim.SHOT_FOREHAND: e.anim = 0x1265
				Anim.SHOT_BACKHAND: e.anim = 0x12dd
				0xdd3: e.anim = 0x1355
				0xe2b: e.anim = 0x138d
			return
		if e.anim_pos < 8:
			sim.shot_power += 1
			if (control & 0x20) == 0:
				# released early: skip the rest of the wind up
				e.anim_pos = 0xe - e.anim_pos
				e.anim_hold = -1

## do_shot (0x578f0): release the puck towards the aim point
static func do_shot(sim: Sim, e: Entity) -> void:
	var puck := sim.puck
	shot_setup(sim, e)
	sim.last_shooter = e.slot
	sim.action_shot = false
	e.flags |= Entity.F_BUSY
	if sim.puck_carrier != e.slot and e.anim != 0xdd3 and e.anim != 0xe2b:
		sim.play_sfx(0x99)
		return
	sim.shot_in_flight = true
	var power := sim.shot_power
	if e.anim == Anim.SHOT_BACKHAND or e.anim == 0xe2b:
		power -= power >> 2
	var sfx := 0xaa
	var skill := e.shot_skill
	if skill > 0xc and absi(e.xi) + absi(e.yi) < 500:
		skill += 2
	if skill > 0xe:
		skill += 1
	if skill > 0xd:
		skill += 1
	if skill > 10:
		skill += 1
	var eskill := (e.energy * skill) >> 12
	power = (power * (eskill + 0x14) * 0x5249) >> 16
	if sim.breakaway:
		Rules.count_defenders_ahead(sim)
		sim.breakaway = sim.defenders_ahead != 0
	if (power >> 4) >= 3:
		sfx = 0x9a
	sim.puck_carrier = -1
	e.timer_c = 0x10
	sim.last_passer = e.slot
	var goal_y := 0xe8 if (e.flags & Entity.F_ATTACK_UP) else -0xe8
	var aim := sim.pending_dir & 7
	var ax: int = Tables.shot_targets[aim * 2]
	var az: int = Tables.shot_targets[aim * 2 + 1]
	var dx := ax - puck.xi
	var dy := goal_y - puck.yi
	var dist := maxi(1, Sim.approx_distance(dx, dy))
	if not sim.no_stats:
		var acc := e.shot_accuracy
		if acc > 0xe:
			acc += 1
		if acc > 0xd:
			acc += 1
		if dist > 200 or sim.random(e.shot_accuracy + 0x10) < 0xf:
			var spread := (dist * (((power >> 4) - acc) + 0x10) & 0xffff) >> 6
			if dist < 0xfa:
				spread >>= 1
			spread = mini(spread, 0xa0)
			dx += sim.random(spread * 2) - spread
			spread = mini(spread, 0x3c)
			var sy := spread if dy >= 0 else spread >> 1
			dy += sim.random(sy * 2) - sy
			var sz := spread >> 1
			if dist < 0xa0:
				sz = spread / 3
			if dist < 0x50:
				sz = spread >> 2
			az += sim.random(maxi(1, sz))
	puck.vx = (dx * power * 0x3b) / dist
	puck.vy = (dy * power * 0x3b) / dist
	if az != 0:
		var p := maxi(1, power)
		puck.vz = mini(0x1800, (p * 0x44 * az) / dist + (dist * 0xb33) / p)
	sim.play_sfx(sfx)

## shot_setup (0x5471a): the AI aims at the side of the net the goalie leaves open
static func shot_setup(sim: Sim, e: Entity) -> void:
	if e.flags & Entity.F_USER:
		return
	var puck := sim.puck
	var opp := sim.opponents_of(e)
	var goalie: Entity = null
	for i in 6:
		var p := sim.entities[opp.first_slot + i]
		if p.line_slot == 0:
			goalie = p
			break
	if goalie == null:
		sim.pending_dir = 8
		return
	var gx := goalie.xi + (goalie.vx >> 9) - puck.xi
	var gy := goalie.yi + (goalie.vy >> 9) - puck.yi
	var d := maxi(1, Sim.approx_distance(gx, gy))
	var goal_y := 0xe8 if (e.flags & Entity.F_ATTACK_UP) else -0xe8
	var num := gx * (goal_y - puck.yi)
	var side := (num - (0x12 - puck.xi) * gy) / d + (num - (-0x12 - puck.xi) * gy) / d
	if absi(side) < 0x2d:
		if e.flags & Entity.F_ATTACK_UP:
			side = -side
		sim.pending_dir = 6 if side < 0 else 2
	else:
		sim.pending_dir = 0

static func shot_is_backhand(e: Entity, dir: int) -> bool:
	var rel := (e.facing - dir) & 7
	var mask := 0xf0 if (e.flags4 & Entity.F4_MIRROR) else 0x1e
	return ((1 << rel) & mask) != 0

# --------------------------------------------------------------------------------------------
# checking (body_check, hook_button, start_hook, start_poke_check, try_block_shot,
# opponent_in_reach, resolve_body_check, knock_down)
# --------------------------------------------------------------------------------------------

## body_check (0x532bd): velocity burst in the heading direction, costs energy
static func body_check(sim: Sim, e: Entity) -> void:
	var en := e.energy
	if sim.opt_line_changes:
		en = maxi(0, en - 0xcc)
		e.energy = en
	var burst := en >> 7
	var v: Array = Tables.dir8_vectors[e.facing]
	e.vx += v[0] * burst
	e.vy += v[1] * burst
	e.flags |= Entity.F_BUSY
	Anim.set_animation(e, Anim.BODY_CHECK)

## hook_button (0x4fff0): C without the puck: hook, poke check or block depending on the situation
static func hook_button(sim: Sim, e: Entity) -> void:
	e.flags |= Entity.F_BUSY
	if e.speed == 0:
		if opponent_in_reach(sim, e):
			Anim.set_animation(e, Anim.HOOK_B)
			return
		var r := try_block_shot(sim, e)
		if r != 0:
			start_poke_check(sim, e, r)
			return
	var c := sim.carrier()
	start_hook(sim, e, c if c != null else e)

static func opponent_in_reach(sim: Sim, e: Entity) -> bool:
	var opp := sim.opponents_of(e)
	for i in 6:
		var p := sim.entities[opp.first_slot + i]
		var dx := p.xi - e.xi
		var dy := p.yi - e.yi
		var d := Tables.direction8(dx, dy)
		if ((d - e.facing + 2) & 7) < 5 and absi(dx) < 0x1e and absi(dy) < 0x1e:
			return true
	return false

## try_block_shot (0x50068): 0 none, 1..9 poke direction class, 10 drop to block
static func try_block_shot(sim: Sim, e: Entity) -> int:
	var puck := sim.puck
	if sim.puck_carrier >= 0 and sim.same_team(sim.puck_carrier, e.slot):
		return 0
	var ay := absi(puck.yi)
	if ay >= 0xe9 or ay <= 0x4d or e.puck_dist >= 0x51:
		return 0
	var up := (e.flags & Entity.F_ATTACK_UP) != 0
	var own_goal_pred: Array = sim.goal_prediction[1 if up else 0]
	if own_goal_pred[1] <= 9:
		return 0
	var shooter_slot := sim.puck_carrier
	if shooter_slot < 0:
		if (up and puck.vy > 0) or (not up and puck.vy < 0):
			return 0
		if sim.last_shooter < 0 or sim.same_team(sim.last_shooter, e.slot):
			return 0
		shooter_slot = sim.last_shooter
	var shooter := sim.entities[shooter_slot]
	var sa := shooter.anim
	if not (sa == 0x3f9 or sa == 0x491 or sa == 0xdd3 or sa == 0xe2b or sa == 0x1265 or sa == 0x12dd or sa == 0x1355 or sa == 0x138d):
		return 0
	var net := sim.entities[Entity.Slot.NET_BOTTOM if up else Entity.Slot.NET_TOP]
	var pd := Sim.approx_distance(puck.xi - net.xi, puck.yi - net.yi)
	var pdir := Tables.direction8(puck.xi - net.xi, puck.yi - net.yi)
	var between := false
	if up:
		between = e.yi < -0x4e and e.yi > -0xe8 and e.yi < puck.yi
	else:
		between = e.yi > 0x4e and e.yi < 0xe8 and puck.yi < e.yi
	if not between:
		return 0
	var ed := Sim.approx_distance(e.xi - net.xi, e.yi - net.yi)
	var edir := Tables.direction8(e.xi - net.xi, e.yi - net.yi)
	if (e.flags & Entity.F_USER) == 0 and edir != 2 and edir != 6:
		if not (absi(e.yi) > 0x7f and absi(e.xi) < 0x65):
			return 0
	var rel_face := (e.puck_dir - e.facing + 2) & 7
	var rel_dir := (pdir - edir + 2) & 7
	if ((e.puck_dir - pdir + 1) & 7) >= 3:
		return 0
	var ok := false
	if e.flags & Entity.F_USER:
		ok = rel_face < 5 and rel_dir < 5
	else:
		ok = rel_face != 0 and rel_dir != 0 and rel_face < 4 and rel_dir < 4
	if not ok or ed >= pd or ed + e.puck_dist >= pd * 2:
		return 0
	if rel_face == 2 and rel_dir == 2:
		return 10
	e.timer_e = pdir
	return rel_dir + 1

## start_poke_check (0x533be)
static func start_poke_check(sim: Sim, e: Entity, kind: int) -> void:
	e.flags |= Entity.F_BUSY
	e.facing = e.puck_dir
	if kind == 10 or kind == 3:
		Anim.set_animation(e, 0x14ad if (sim.puck.zi < 3 and sim.puck.vz < 2000) else 0x1475)
		return
	e.facing = e.timer_e
	var v: Array = Tables.poke_vectors[e.timer_e & 7]
	var py: int = v[1]
	var px: int = v[0]
	if kind < 3:
		py = -py
		px = -px
	if (py ^ e.vy) < 0 or absi(e.vy) <= absi(py):
		e.vy >>= 3
	else:
		e.vy >>= 1
	e.vy += py
	if (px ^ e.vx) < 0 or absi(e.vx) <= absi(px):
		e.vx >>= 3
	else:
		e.vx >>= 1
	e.vx += px
	Anim.set_animation(e, 0x141d if (kind < 3) == (e.left_handed == 0) else 0x13c5)

## start_hook (0x4ffa4)
static func start_hook(sim: Sim, e: Entity, target: Entity) -> void:
	e.flags |= Entity.F_BUSY
	if e.speed != 0:
		var dy := e.yi - target.yi
		if e.flags & Entity.F_ATTACK_UP:
			dy = -dy
		if dy >= 0:
			Anim.set_animation(e, Anim.HOOK_A)
			return
	Anim.set_animation(e, Anim.HOOK_B)

## resolve_body_check (0x5382c): contact between two opponents (or a player and the referee),
## looked at both ways round: `b` hooks `a` with his stick (0x639 / 0x873, resolve_hook_hold),
## `b` dives at `a` (0x589, resolve_dive_hit) or `a` body checks `b` (0x621)
static func resolve_body_check(sim: Sim, e: Entity, o: Entity, strength: int) -> void:
	var a := e
	var b := o
	for k in 2:
		if b.anim == Anim.HOOK_A or b.anim == Anim.HOOK_B:
			resolve_hook(sim, a, b)
		elif b.anim == 0x589:
			resolve_dive(sim, a, b)
		elif a.anim == Anim.BODY_CHECK:
			check_hit(sim, a, b, strength)
		var t := a
		a = b
		b = t

## the body check part of resolve_body_check: the checker's follow through, then whether the
## victim goes down (weight, speed and the checker's aggression) and the penalty, if any
static func check_hit(sim: Sim, a: Entity, b: Entity, strength: int) -> void:
	if sim.play_stopped:
		a.speed = 0x100
		b.speed = 0x100
	var dir := Tables.direction8(b.xi - a.xi, b.yi - a.yi)
	var rel := (dir - a.facing) & 7
	if a.flags4 & Entity.F4_MIRROR:
		rel = (8 - rel) & 7
	a.flags |= Entity.F_BUSY
	# near the boards or in front of his own net the checker is more likely to lay a big hit
	var odds_range := 0x1e
	if absi(b.xi) > 0x90:
		odds_range = 0x14
	elif (a.yi > 0) != ((a.flags & Entity.F_ATTACK_UP) != 0) and absi(b.yi) - 0xe8 < 0x3c and absi(b.xi) < 0x50:
		odds_range = 0x14
	var anim: int = Tables.check_anims[rel]
	if b.slot != Entity.Slot.REFEREE and sim.random(odds_range) < a.check_skill and ((rel + 1) & 7) <= 2 \
			and absi(a.xi - b.xi) < 0x14 and absi(a.yi - b.yi) < 0x14:
		if absi(b.vx) < 500 and absi(b.vy) < 500:
			anim = 0xed7
		elif ((Tables.direction8(b.vx, b.vy) - a.facing + 2) & 3) != 0:
			anim = 0xed7
	Anim.set_animation(a, anim)
	if b.line_slot == 0 or strength < 0x14:
		return
	var base := 0xa0 if (a.flags & Entity.F_USER) else 100
	if ((b.flags & Entity.F_USER) != 0) != (base == 0xa0):
		base = 0x78
	var odds := Entity.to_s16(((base - a.weight + b.weight) >> 1) - b.speed)
	var down := odds <= 0
	if not down and not sim.no_stats and Rules.breakaway_foul(sim, b) and sim.penalty_shot_slot < 0:
		down = true
	if not down and sim.random(odds) <= a.aggression:
		down = true
	if not down:
		# he stays on his feet; the check may still be called (charging or slashing)
		if b.slot == Entity.Slot.REFEREE or penalty_odds(sim, a) > 4 or sim.no_stats:
			return
		Rules.maybe_queue_infraction(sim, a, Rules.INF_SLASHING if sim.random(2) != 0 else Rules.INF_CHARGING)
		return
	if b.slot == Entity.Slot.REFEREE:
		# a user who flattens the referee three times is thrown out (abuse of official)
		if (a.flags & Entity.F_USER) == 0:
			return
		sim.ref_hits += 1
		if sim.ref_hits >= 3:
			sim.ref_hits = 0
			Rules.maybe_queue_infraction(sim, a, Rules.INF_ABUSE_OF_OFFICIAL)
		knock_down(sim, a, b)
		return
	if not sim.no_stats:
		if Rules.breakaway_foul(sim, b):
			if sim.penalty_shot_slot < 0:
				Rules.award_penalty_shot(sim, b, a)
		else:
			var type := -1
			if b.speed > 0x23 and ((dir - a.facing + 1) & 7) <= 2 and ((b.facing - a.facing + 1) & 7) <= 2 \
					and facing_boards(b) and penalty_odds(sim, a) < 0x14:
				type = Rules.INF_CHECK_FROM_BEHIND
			elif penalty_odds(sim, a) <= 3:
				if a.anim == 0xed7:
					type = Rules.INF_HIGH_STICK if sim.random(10) > 8 else Rules.INF_CROSS_CHECK
				elif b.speed > 0x23 and sim.random(4) == 0:
					type = Rules.INF_ELBOWING_MAJOR
				else:
					type = Rules.INF_ELBOWING if sim.random(10) > 6 else Rules.INF_ROUGHING_HIT
			if type >= 0:
				Rules.maybe_queue_infraction(sim, a, type)
	knock_down(sim, a, b)

## facing_boards (0x5378d): the player faces the boards or the end boards close by (a check from behind
## would put him into them)
static func facing_boards(e: Entity) -> bool:
	var y := e.yi
	var f := e.facing
	if e.xi < -0x78:
		if f == 6 or (y > 0xe8 and f == 7):
			return true
		return y < -0xe8 and f == 5
	if e.xi < 0x79:
		if y > 0xf2 and f == 0:
			return true
		return y < -0xf2 and f == 4
	if f == 2 or (y > 0xe8 and f == 1):
		return true
	return y < -0xe8 and f == 3

## penalty_odds (0x5369f): a random number; the smaller, the likelier the referee calls the foul.
## Good checkers, fouls away from the puck, the third period, a team already short handed and a
## delayed call against the other team all make a call less likely.
static func penalty_odds(sim: Sim, e: Entity) -> int:
	var odds := (0x14 - e.check_skill) * (0x20 if (e.flags & Entity.F_USER) else 0x10)
	if absi(e.xi - sim.puck.xi) < 0x29 and absi(e.yi - sim.puck.yi) < 0x29:
		odds = (Entity.to_s16(odds) >> 1) & 0xffff
	if sim.period > 2:
		odds <<= 3
	if (sim.settings2 & 2) == 0:
		odds *= 2
	var short := sim.opponents_of(e).skaters_on_ice - sim.team_of(e).skaters_on_ice
	if short > 0:
		odds <<= 2
	if short > 1:
		odds <<= 2
	var o16 := Entity.to_s16(odds)
	if sim.delayed_call and sim.puck_carrier >= 0 and (sim.puck_carrier < 6) != (e.slot < 6):
		o16 = Entity.to_s16(odds << 2)
	return sim.random(Entity.to_s16((o16 >> 1) + o16))

## resolve_hook_hold (0x56b79): `b` hooks or holds `a` with his stick (0x639 / 0x873). Both are tied
## up at their common speed; holding (0x651) or hooking (0x88b) may be called, on a breakaway it
## is a penalty shot and the puck is lost.
static func resolve_hook(sim: Sim, a: Entity, b: Entity) -> void:
	if (a.flags & Entity.F_BUSY) or a.slot == Entity.Slot.REFEREE or a.line_slot == 0 or (a.flags2 & Entity.F2_KNOCKED):
		return
	var dir := Tables.direction8(a.xi - b.xi, a.yi - b.yi)
	if ((dir - b.facing + 1) & 7) >= 3:
		return
	if sim.puck_carrier == a.slot:
		sim.action_shot = false
	var vx := (b.vx + a.vx) >> 1
	a.vx = vx
	b.vx = vx
	var vy := (b.vy + a.vy) >> 1
	a.vy = vy
	b.vy = vy
	a.flags |= Entity.F_BUSY
	Anim.set_animation(a, 0x669)
	b.flags |= Entity.F_BUSY
	Anim.set_animation(b, 0x651 if b.anim == Anim.HOOK_A else 0x88b)
	if not Rules.breakaway_foul(sim, a):
		if penalty_odds(sim, b) < 7:
			Rules.maybe_queue_infraction(sim, b, Rules.INF_HOLDING if b.anim == 0x651 else Rules.INF_HOOKING)
	elif Rules.award_penalty_shot(sim, a, b):
		sim.puck_carrier = -1
		b.timer_c = 0x20
	sim.puck_in_net = true

## resolve_dive_hit (0x56a54): `b` dives at `a` (0x589) and trips him: tripping, or a penalty
## shot on a breakaway. Without the penalty option a user's dive often misses.
static func resolve_dive(sim: Sim, a: Entity, b: Entity) -> void:
	if (a.flags & Entity.F_BUSY) or a.slot == Entity.Slot.REFEREE or a.line_slot == 0 or (a.flags2 & Entity.F2_KNOCKED):
		return
	if not sim.opt_penalties and (b.flags & Entity.F_USER) and sim.random((b.aggression + 0x10) - a.speed_skill) < 0xc:
		return
	var dir := Tables.direction8(a.xi - b.xi, a.yi - b.yi)
	if ((dir - b.facing + 1) & 7) > 2:
		return
	knock_down(sim, b, a)
	if not Rules.breakaway_foul(sim, a):
		if penalty_odds(sim, b) <= 4:
			Rules.maybe_queue_infraction(sim, b, Rules.INF_TRIPPING)
	else:
		Rules.award_penalty_shot(sim, a, b)
	sim.puck_in_net = true

## goalie_collision (0x53e6a): a skater who crashes into a goalie (with
## the puck or at speed) falls; a hard hit on a goalie outside his crease may be called as
## interference
static func goalie_collision(sim: Sim, e: Entity, o: Entity) -> void:
	var p := e
	var g := o
	for k in 2:
		if g.line_slot == 0 and not sim.play_stopped and (sim.puck_carrier == p.slot or p.speed > 0x19) and p.speed > 2:
			knock_down(sim, g, p)
			if sim.last_impact > 7 and (sim.puck_carrier != p.slot or sim.last_impact > 9):
				if absi(g.yi) > 0x9f and p.slot != Entity.Slot.REFEREE and p.slot < 12 and p.roster_idx >= 0 \
						and sim.team_of(p).entity_of[p.roster_idx] > -3 and g.speed > 0x1e and (p.flags2 & Entity.F2_PENALIZED) == 0:
					if sim.random(0x14 - p.check_skill) < 3 and not sim.no_stats:
						Rules.maybe_queue_infraction(sim, p, Rules.INF_INTERFERENCE)
		var t := p
		p = g
		g = t

## knock_down (0x562db): `victim` falls (or only stumbles: 0x8d3). Against the boards he is put
## into a board animation (knockdown_position) and boarding may be called; a fall can injure him
## (injure_player). The hitter can be a player, the referee or the puck.
static func knock_down(sim: Sim, hitter: Entity, victim: Entity) -> void:
	if (victim.slot >= 12 and victim.slot != Entity.Slot.REFEREE) or (victim.flags2 & Entity.F2_KNOCKED):
		return
	var va := victim.anim
	if va == 0xa0b or va == 0x8d3 or va == 0x681 or va == 0x6d9 or va == 0x993 or va == 0x13c5 or va == 0x141d:
		return
	if victim.slot == Entity.Slot.REFEREE:
		if va == 0xb13:
			return
		victim.flags |= Entity.F_BUSY
		Anim.set_animation(victim, 0xb13)
		sim.add_crowd(500, 1000)
		sim.excitement += 0xf
		crowd_reaction_sfx(sim, 1)
		sim.play_sfx(0x7d)
		return
	# the puck and the nets have no line slot in the original (0, like a goalie)
	var hitter_slot := hitter.line_slot if hitter.slot < 12 else 0
	var anim: int
	if victim.goalie_skill >= 0xc and sim.random(0x10) + 0x10 > victim.speed:
		victim.timer_d = 0x3c
		anim = 0x8d3
	else:
		if hitter_slot != 0 and not sim.no_stats and not sim.play_stopped:
			sim.team_of(hitter).hits += 1
		victim.timer_c = 0x78
		var dir := Tables.direction8(hitter.xi - victim.xi, hitter.yi - victim.yi)
		anim = victim.anim
		if hitter_slot != 0 and (hitter.slot < 6) != (victim.slot < 6):
			anim = board_knockdown(sim, victim, dir)
		if anim == victim.anim:
			var rel := (dir - victim.facing + 1) & 7
			if rel < 3:
				anim = 0x6d9               # falls backwards
			elif hitter.slot == Entity.Slot.PUCK and (rel == 3 or rel == 7):
				anim = 0x6d9               # hit by the puck
				if hitter.frame < 0x450 and sim.penalty_shot_slot < 0 and not sim.play_stopped and not sim.no_stats \
						and sim.opt_injuries and (victim.facing & 3) == 0 and (victim.flags2 & Entity.F2_PENALIZED) == 0:
					var r := sim.random(200 if (victim.flags & Entity.F_USER) else 0xa0)
					if r < 0x15 and Rules.injury_check(sim, victim):
						sim.add_crowd(500, 1000)
						sim.excitement += 0xf
						victim.flags |= Entity.F_BUSY
						Anim.set_animation(victim, 0xa0b)
						injure_player(sim, victim)
						Rules.queue_infraction(sim, hitter, Rules.INF_INJURY)
						return
			elif (victim.facing & 3) == 0 and hitter.aggression > 9 and hitter.slot < 12:
				anim = 0x993               # a big hit: the hitter's bench cheers
				Crowd.bench_cheer(sim, hitter.team)
			else:
				anim = 0x681               # spins down sideways
		else:
			sim.crowd_noise += 100
			if sim.puck_carrier != victim.slot and penalty_odds(sim, hitter) < 4 and anim > 0xf0e and anim < 0xfe2:
				Rules.maybe_queue_infraction(sim, hitter, Rules.INF_BOARDING if victim.speed < 0x24 else Rules.INF_BOARDING_MAJOR)
	victim.flags |= Entity.F_BUSY
	Anim.set_animation(victim, anim)
	if victim.state() == Entity.State.SHOOT:
		AI.default_skate(sim, victim)
	sim.add_crowd(500, 1000)
	sim.excitement += 0xf
	if sim.puck_carrier < 0 or sim.puck_carrier != victim.slot:
		crowd_reaction_sfx(sim, 1 if (anim < 0xf0f or anim > 0x1055) else 2)
		return
	sim.puck_carrier = -1
	if sim.penalty_shot_slot < 0 and not sim.no_stats and sim.opt_injuries and victim.anim == 0x6d9 \
			and (victim.facing & 3) == 0 and (victim.flags2 & Entity.F2_PENALIZED) == 0:
		var r := sim.random(200 if (victim.flags & Entity.F_USER) else 0xa0)
		if r <= victim.speed and not sim.play_stopped and Rules.injury_check(sim, victim):
			victim.flags |= Entity.F_BUSY
			Anim.set_animation(victim, 0xa0b)
			injure_player(sim, victim)
			if hitter_slot == 0 or not sim.opt_penalties or (hitter.slot < 12 and sim.team_of(hitter).penalties.size() > 7) \
					or not Rules.injury_check(sim, hitter):
				Rules.queue_infraction(sim, hitter, Rules.INF_INJURY)
			else:
				# the hit that injured him is called: from behind (a major) or roughing
				var d := Tables.direction8(victim.xi - hitter.xi, victim.yi - hitter.yi)
				var hf := hitter.facing
				var behind := ((d - hf + 1) & 7) < 3 and ((victim.facing - hf + 1) & 7) < 3
				Rules.queue_infraction(sim, hitter, Rules.INF_CHECK_FROM_BEHIND if behind else Rules.INF_ROUGHING)
	sim.play_sfx(0x7d if (victim.flags & Entity.F_PLAYER2) else 0xa0)

## the board part of knock_down (0x56441..0x566ad): a player hit against the side or end boards is
## pinned to them (the 0xf0f..0x1055 board animations); returns the victim's current animation
## when he falls on open ice
static func board_knockdown(sim: Sim, v: Entity, dir: int) -> int:
	var x := v.xi
	var y := v.yi
	var f := v.facing
	var mirror := (v.flags4 & Entity.F4_MIRROR) != 0
	if absi(x) > 0x5f and absi(y) > 0xc9:
		var a := knockdown_position(sim, v, dir)
		if a != v.anim:
			return a
	if x >= 0x80:
		# right boards
		if y < 0xd1 and y > -0xd7:
			if dir > 4:
				v.vx = 0
				if mirror:
					_set_x(v, -Tables.knockdown_left_x[(8 - f) & 7])
					return 0xfe1
				_set_x(v, Tables.knockdown_right_x[f])
				return 0xf9b
			return v.anim
		return knockdown_position(sim, v, dir)
	if x < -0x7f:
		# left boards
		if y > 0xd0 or y < -0xd6:
			return knockdown_position(sim, v, dir)
		if dir == 0 or dir > 3:
			return v.anim
		v.vx = 0
		if (y < -0x54 or y > -0xb) and (y < 0x27 or y > 0x74):
			if mirror:
				_set_x(v, -Tables.knockdown_right_x[(8 - f) & 7])
				return 0xf9b
			_set_x(v, Tables.knockdown_left_x[f])
			return 0xfe1
		# in front of a bench door
		if not mirror:
			_set_x(v, Tables.knockdown_left2_x[f])
			return 0x1055
		_set_x(v, -Tables.knockdown_right2_x[(8 - f) & 7])
		return 0x1027
	if y >= 0xee:
		# top end boards
		if x > 0x68 or x < -0x68:
			return knockdown_position(sim, v, dir)
		if ((dir + 2) & 7) > 4:
			_set_y(v, Tables.knockdown_top_y[f])
			v.vy = 0
			return 0xf0f
		return v.anim
	if y < -0xf1:
		# bottom end boards
		if x > 0x68 or x < -0x68:
			return knockdown_position(sim, v, dir)
		if ((dir + 1) & 7) < 3:
			_set_y(v, Tables.knockdown_bottom_y[f])
			v.vy = 0
			return 0xf55
	return v.anim

static func _set_x(e: Entity, x: int) -> void:
	e.x = (x << 16) | (e.x & 0xffff)

static func _set_y(e: Entity, y: int) -> void:
	e.y = (y << 16) | (e.y & 0xffff)

## knockdown_position (0x5601d): in a corner the player is pinned to the rounded boards: moved onto
## the corner circle (centre +-0x60, +-0xca) and given the side (0xf9b / 0xfe1) or end (0xf0f /
## 0xf55) board animation that faces the hit; returns his current animation otherwise
static func knockdown_position(_sim: Sim, e: Entity, dir: int) -> int:
	var cx := -0x60 if e.xi < 0 else 0x60
	var cy := -0xca if e.yi < 0 else 0xca
	var dx := e.xi - cx
	var dy := e.yi - cy
	var d := Sim.approx_distance(dx, dy)
	var mirror := (e.flags4 & Entity.F4_MIRROR) != 0
	var f := e.facing
	if d <= 0x17:
		return e.anim
	var ux := ((dx * 0x100) / d) >> 2
	var uy := ((dy * 0x100) / d) >> 2
	if absi(uy) < absi(ux):
		if cx < 0:
			if dir != 0 and dir - 1 < 3:
				_set_x(e, cx + ux + 6)
				_set_y(e, uy + cy + (0 if cy < 1 else -10))
				e.vx = 0
				e.vy = 0
				if not mirror:
					_set_x(e, e.xi + Tables.knockdown_left_x[f] + 0x9a)
					return 0xfe1
				_set_x(e, e.xi - (Tables.knockdown_right_x[(8 - f) & 7] - 0x9a))
				return 0xf9b
		elif dir > 4:
			_set_x(e, cx + ux - 6)
			_set_y(e, uy + cy + (0 if cy < 1 else -10))
			e.vx = 0
			e.vy = 0
			if not mirror:
				_set_x(e, e.xi + Tables.knockdown_right_x[f] - 0x9a)
				return 0xf9b
			_set_x(e, e.xi - (Tables.knockdown_left_x[(8 - f) & 7] + 0x9a))
			return 0xfe1
	elif cy < 0:
		if ((dir + 1) & 7) < 3:
			_set_x(e, cx + ux)
			_set_y(e, uy + cy)
			e.vx = 0
			e.vy = 0
			_set_y(e, e.yi + Tables.knockdown_bottom_y[f] + 0x108)
			return 0xf55
	elif ((dir + 2) & 7) > 4:
		_set_x(e, cx + ux)
		if cx < 0 and not mirror:
			_set_x(e, e.xi + 6)
		if cx > 0 and mirror:
			_set_x(e, e.xi - 6)
		_set_y(e, uy + cy - 8)
		e.vx = 0
		e.vy = 0
		_set_y(e, e.yi + Tables.knockdown_top_y[f] - 0x108)
		return 0xf0f
	return e.anim

## injure_player (0x55e72): the player is hurt: out for the period (-3) or, after a heavy hit and
## with bad luck (rating 15 of the player), for the game (-4). The camera looks at him.
static func injure_player(sim: Sim, e: Entity) -> void:
	e.flags2 |= Entity.F2_UNSELECTABLE
	sim.add_crowd(300, 1000)
	sim.excitement += 0x1e
	sim.play_sfx(0xa1)
	sim.camera_target_x = e.xi
	sim.camera_target_y = e.yi + (0x32 if e.xi < sim.camera_x else 0)
	sim.action_hold_camera = true
	var team := sim.team_of(e)
	var proneness := 8
	if team.info != null and e.roster_idx >= 0:
		var p: Database.Player = team.info.player(e.roster_idx)
		if p != null and p.ratings.size() > 15:
			proneness = p.ratings[15]
	var r := sim.random(proneness + 8)
	var for_game := r > 6 and sim.last_impact >= 0x2e
	if e.roster_idx >= 0 and e.roster_idx < 28:
		team.entity_of[e.roster_idx] = -4 if for_game else -3
		if not for_game:
			team.injured.append(e.roster_idx)
	sim.injury_stoppage = true
	sim.injury_report = [team.index, e.roster_idx, for_game]
	InfoPanel.announce_injury(sim, team.index, e.roster_idx, for_game)

## crowd_reaction_sfx (0x58084): 0 a hit, 1 a fall, 2 a fall against the boards (glass)
static func crowd_reaction_sfx(sim: Sim, kind: int) -> void:
	if kind == 2:
		sim.play_sfx(0xb1)
	if kind != 0 and sim.last_impact > 0x20 and sim.random(2) == 0:
		sim.play_sfx(0x93)
		return
	sim.crowd_toggle = not sim.crowd_toggle
	sim.play_sfx(0xb0 if sim.crowd_toggle else 0xb2)
