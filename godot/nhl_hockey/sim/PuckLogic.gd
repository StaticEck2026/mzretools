class_name PuckLogic
## Everything that happens between the puck and the players: carrying, picking up, deflections,
## goalie saves, passes, shots, body checks and hooks. Ports of puck_update, update_carrier,
## puck_check_players, puck_player_interaction, goalie_save, puck_hits_player, attach_puck_to_stick,
## do_pass, sub_551cf (pass lead), start_shot, shot_control, do_shot, body_check, hook_button and
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

## sub_4dd51: the carrier entered the offensive zone with team mates already inside
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

## sub_4dcdd: offside when the carrier crosses the blue line with the flag set
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
		puck_spin(sim, puck)

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
	puck.vx = ((e.xi - puck.xi) << 8) | (puck.vx & 0xff)
	puck.vy = ((e.yi - puck.yi) << 8) | (puck.vy & 0xff)
	puck_spin(sim, puck)
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

## sub_56f5a: a player becomes the carrier
static func take_puck(sim: Sim, e: Entity) -> void:
	sim.puck_carrier = e.slot
	var team := sim.team_of(e)
	var opp := sim.opponents_of(e)
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
		e.timer_b = 5 if e.anim == 0x181 else 0x8c   # time until the goalie must play the puck
	# sub_5b1ce: the user follows the puck to the new carrier of his team
	if e.slot != sim.user1_slot and e.slot != sim.user2_slot:
		var t := e.team + 1
		if sim.user1_team == t and sim.user1_slot >= 0:
			sim.user1_slot = sim.find_switch_target(e.slot, sim.user1_slot)
		elif sim.user2_team == t and sim.user2_slot >= 0:
			sim.user2_slot = sim.find_switch_target(e.slot, sim.user2_slot)

## sub_55d28: a shot reached a player or the net: shot statistics
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
			sim.team_of(s).shots += 1

## sub_57a3e: the puck squirts away from a failed take
static func release_puck_random(sim: Sim) -> void:
	sim.puck_carrier = -1
	var puck := sim.puck
	puck.vy = sim.random(0x2000) - 0x1000
	puck.vx = sim.random(0x2000) - 0x1000
	puck.vz = sim.random(0x1000)
	puck_spin(sim, puck)

## sub_4dfa4 / sub_4d907: puck frame bookkeeping (flat disc vs rolling)
static func puck_spin(sim: Sim, puck: Entity) -> void:
	if ((puck.vx >> 16) + (puck.vy >> 16)) < 0x14 and absi(puck.vx) + absi(puck.vy) < 0x1400:
		puck_flat(sim, puck)
		return
	puck.flags3 = ((sim.random(2) & 1) ^ puck.flags3) & 3
	puck.anim_hold = -1
	Anim.set_animation(puck, 0x239)

static func puck_flat(_sim: Sim, puck: Entity) -> void:
	if puck.anim_pos > 3 and puck.anim_pos < 0xc:
		puck.flags3 ^= 2
	puck.flags3 |= 4
	puck.anim_pos = 0
	puck.anim_hold = -1

## sub_54990: a player in front of the net is pushed off the goalie
static func net_pushed_off(sim: Sim, e: Entity) -> bool:
	if sim.random(0x20) != 0:
		return false
	var puck := sim.puck
	if absi(puck.yi - e.yi) >= 0x29:
		return false
	if absi(e.vx) < 0x1b59 and absi(e.vy) < 0x1b59:
		return false
	e.vx >>= 2
	e.vy >>= 2
	return true

# --------------------------------------------------------------------------------------------
# passing (pass_button, do_pass, pass_to_entity, sub_551cf)
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

## sub_551cf: lead the pass to where the receiver will be
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

## sub_54c09: is the lane to the receiver open enough for a direct pass
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

## resolve_body_check (0x5387b), reduced: a body check or a hook on contact knocks the other down
## or slows him; penalties are called with the original odds
static func resolve_body_check(sim: Sim, e: Entity, o: Entity, strength: int) -> void:
	for pair in [[e, o], [o, e]]:
		var a: Entity = pair[0]
		var b: Entity = pair[1]
		if b.anim == Anim.HOOK_A or b.anim == Anim.HOOK_B:
			# hook: the carrier is slowed, hooking penalty with the aggression odds
			if sim.puck_carrier == a.slot and (a.flags2 & Entity.F2_HOOKED) == 0:
				a.flags2 |= Entity.F2_HOOKED
				a.timer_d = 0x3c
				if sim.random(0x20 - b.aggression) < 4:
					Rules.maybe_queue_infraction(sim, b, Rules.INF_HOOKING)
			continue
		if b.anim == 0x589 and sim.puck_carrier == a.slot and sim.random(3) == 0:
			# poke / lunge: steals the puck
			a.timer_c = 0x14
			sim.puck_carrier = -1
			sim.last_passer = a.slot
			release_puck_random(sim)
			continue
		if a.anim != Anim.BODY_CHECK:
			continue
		if sim.play_stopped:
			a.vx = 0
			a.vy = 0
			continue
		var dir := Tables.direction8(b.xi - a.xi, b.yi - a.yi)
		var rel := (dir - a.facing) & 7
		if a.flags4 & Entity.F4_MIRROR:
			rel = (8 - rel) & 7
		a.flags |= Entity.F_BUSY
		if b.line_slot == 0 or strength <= 0x13:
			continue
		var base := 0xa0 if (a.flags & Entity.F_USER) else 100
		if ((b.flags & Entity.F_USER) != 0) != (base == 0xa0):
			base = 0x78
		var odds := ((base - a.weight + b.weight) >> 1) - b.contact
		if odds > 0 and sim.random(odds) > a.awareness:
			continue
		if b.slot == Entity.Slot.REFEREE:
			continue
		if not sim.no_stats:
			if b.contact < 0x24 or ((dir - a.facing + 1) & 7) > 2:
				var pen := -1
				if sim.random(0x14 - a.check_skill) > 3:
					pen = -1
				elif b.contact < 0x24 or sim.random(4) != 0:
					pen = Rules.INF_CHARGING if sim.random(10) < 7 else 21
				else:
					pen = 25
				if pen >= 0:
					Rules.maybe_queue_infraction(sim, a, pen)
		knock_down(sim, a, b)

## knock_down (0x561c5): the victim falls (or stumbles if the hit was light)
static func knock_down(sim: Sim, hitter: Entity, victim: Entity) -> void:
	if (victim.slot >= 12 and victim.slot != Entity.Slot.REFEREE) or (victim.flags2 & Entity.F2_KNOCKED):
		return
	var a := victim.anim
	if a == 0xa0b or a == 0x8d3 or a == 0x681 or a == 0x6d9 or a == 0x993 or a == 0x13c5 or a == 0x141d:
		return
	if victim.slot == Entity.Slot.REFEREE:
		if a == 0xb13:
			return
		victim.flags |= Entity.F_BUSY
		Anim.set_animation(victim, 0xb13)
		sim.add_crowd(500, 1000)
		sim.excitement += 0xf
		return
	var falls := victim.speed >= 0xc or sim.random(0x10) + 0x10 <= victim.contact
	var anim := 0x8d3
	if falls:
		if hitter.line_slot != 0 and not sim.no_stats and not sim.play_stopped:
			sim.team_of(hitter).hits += 1
		victim.timer_c = 0x78
		var dir := Tables.direction8(hitter.xi - victim.xi, hitter.yi - victim.yi)
		var rel := (dir - victim.facing + 1) & 7
		if rel < 3:
			anim = 0x6d9           # falls backwards
		elif hitter.slot == Entity.Slot.PUCK and (rel == 3 or rel == 7):
			anim = 0x6d9
		elif (victim.facing & 3) == 0 and hitter.aggression > 9 and hitter.slot < 12:
			anim = 0x993           # big hit
		else:
			anim = 0x681           # stumbles sideways
	else:
		victim.timer_d = 0x3c
	victim.flags |= Entity.F_BUSY
	Anim.set_animation(victim, anim)
	if victim.state() == Entity.State.SHOOT:
		victim.push_state()
	sim.add_crowd(500, 1000)
	sim.excitement += 0xf
	if sim.puck_carrier == victim.slot:
		sim.puck_carrier = -1
		victim.timer_c = maxi(victim.timer_c, 0x14)
		sim.last_passer = victim.slot
		release_puck_random(sim)
	sim.play_sfx(0x7d if (victim.flags & Entity.F_PLAYER2) else 0xa0)
