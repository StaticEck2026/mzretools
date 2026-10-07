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
	# the steps until the puck crosses the goal lines count down; every 5 steps they are predicted
	# again (predict_puck_goal_line; the timer is the puck's +0x26)
	for i in 2:
		sim.goal_prediction[i][1] = Sim._s16(sim.goal_prediction[i][1] - 1)
	sim.puck_goal_timer = Sim._s16(sim.puck_goal_timer - 1)
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
		puck.x = (Sim._s16(puck.xi + ((tx - puck.xi) >> 2)) << 16) | (puck.x & 0xffff)
		puck.y = (Sim._s16(puck.yi + ((ty - puck.yi) >> 2)) << 16) | (puck.y & 0xffff)
		puck.vx = c.vx
		puck.vy = c.vy
	Rules.check_icing(sim)
	Rules.check_offside(sim)
	Rules.update_offside_flags(sim)
	if not sim.play_stopped:
		if sim.puck_carrier >= 0:
			sim.penalty_shot_away = 0
			sim.puck_stuck_timer = 0x78
		else:
			# penalty shot: a loose puck that keeps moving away from the net for 30 steps ends it
			var up := sim.teams[sim.penalty_shot_team].attacks_up
			if sim.penalty_shot and ((up and puck.vy <= 0) or (not up and puck.vy >= 0)):
				sim.penalty_shot_away += 1
				if sim.penalty_shot_away >= 0x1e:
					Rules.end_penalty_shot(sim)
					sim.penalty_shot_away = 0
			else:
				sim.penalty_shot_away = 0
			# a puck that does not move for 0x78 steps (behind the net, in a corner, or with
			# players of both teams near it) is frozen
			if puck.xi != Sim._s16(puck.prev_x >> 16) or puck.yi != Sim._s16(puck.prev_y >> 16) \
					or (absi(puck.xi) < 0xa3 and absi(puck.yi) < 0x10e and sim.teams[0].nearest_dist > 0x14 \
					and sim.teams[1].nearest_dist > 0x14):
				sim.puck_stuck_timer = 0x78
			else:
				sim.puck_stuck_timer = Sim._s16(sim.puck_stuck_timer - 1)
				if sim.puck_stuck_timer < 0:
					Rules.queue_infraction(sim, puck, Rules.INF_FROZEN)
	# a slow puck on the ice shows the flat disc
	if absi(puck.vz) < 0x100 and puck.zi == 0:
		puck_flat(sim, puck)
	puck_check_players(sim)

## predict_puck_goal_line (0x5a341): where (x, reflected off the side boards) and in how many steps
## (16 bit words, 0xffff none) the puck crosses each goal line (+y, then -y)
static func predict_goal_line(sim: Sim) -> void:
	var puck := sim.puck
	for i in 2:
		var gy := 0xe8 if i == 0 else -0xe8
		var pred: Array = sim.goal_prediction[i]
		var dy := Sim._s16(gy - puck.yi)
		var vy := Sim._s16(puck.vy)
		if vy == 0:
			pred[1] = -1
			continue
		var steps := (dy << 12) / vy
		if steps < 0 or steps >= 0x10000:
			pred[1] = -1
			continue
		pred[1] = Sim._s16(steps)
		var dx := (Sim._s16(puck.vx) * dy) / vy
		if dx >= 0x10000:
			pred[1] = -1
			continue
		var px := Sim._s16(dx + puck.xi)
		if px >= 0xa0:
			px = Sim._s16(0x140 - px)
		if px <= -0xa0:
			px = Sim._s16(-0x140 - px)
		pred[0] = px

## update_carrier (0x4de14): a player touches the puck: the place of the touch (last_touch_*, not
## when the touch makes a two line pass), the last three carriers of his team (the scorer and the
## assists of a goal: words +0x30/+0x32/+0x34 of the team record, a high byte of 0xff marks an
## entry that no longer counts), the end of a shot, offside and the two line pass, icing (called
## when a player of the other team, not the goalie, touches the puck first) or a new icing candidate
static func update_carrier(sim: Sim, c: Entity) -> void:
	var zone := carrier_zone_entry(sim, c)
	if not zone and not sim.play_stopped:
		sim.last_touch_x = c.xi
		sim.last_touch_y = c.yi
		sim.last_touch_slot = c.slot
	var team := sim.team_of(c)
	var r := Entity.to_s8(c.roster_idx)
	if r != team.carrier_history[0]:
		if team.flags & 8:
			team.flags &= ~8
		else:
			team.carrier_history[2] = team.carrier_history[1]
			team.carrier_history[1] = team.carrier_history[0]
		team.carrier_history[0] = r
		if r == team.carrier_history[2]:
			team.carrier_history[2] = Entity.to_s16(team.carrier_history[2] | 0xff00)
	elif team.flags & 8:
		team.flags &= ~8
	if c.line_slot != 0:
		sim.shot_in_flight = false
	if not offside_entry_check(sim, c) and zone:
		Rules.maybe_queue_infraction(sim, c, Rules.INF_TWO_LINE)
	# icing_state: byte 2 = flags (1 the puck crossed the goal line, 2 shot by the team attacking
	# +y, 4 a candidate), byte 3 = the shooter
	var ic := sim.icing_flags
	if (ic & 4) and (ic & 1) and c.line_slot != 0 and ((c.flags & Entity.F_ATTACK_UP) != 0) != ((ic & 2) != 0):
		Rules.maybe_queue_infraction(sim, sim.entities[sim.icing_shooter], Rules.INF_ICING)
		return
	sim.icing_flags = 0
	sim.icing_shooter = c.slot
	var a := sim.puck.yi
	if c.flags & Entity.F_ATTACK_UP:
		sim.icing_flags = 2
		a = -a
	if a >= 0:
		# from the own half, unless short handed
		a = sim.teams[0].skaters_on_ice - sim.teams[1].skaters_on_ice
		if c.flags & Entity.F_PLAYER2:
			a = -a
		if a >= 0:
			sim.icing_flags |= 4

## carrier_zone_entry (0x4dd51): a two line pass: with the puck in his own half (or flagged offside)
## the receiver is past the red line and the last touch was a team mate's in their own zone (the
## original takes any slot below 6, -1 included, for the home team)
static func carrier_zone_entry(sim: Sim, c: Entity) -> bool:
	if sim.no_stats or not sim.opt_two_line_pass:
		return false
	var up := (c.flags & Entity.F_ATTACK_UP) != 0
	if (c.flags2 & Entity.F2_OFFSIDE) == 0 and (sim.puck.yi > 0) == up:
		return false
	var lts := sim.last_touch_slot
	if c.slot == lts or (c.slot < 6) != (lts < 6):
		return false
	if up:
		return sim.last_touch_y <= -0x4e and c.yi >= 0
	return sim.last_touch_y >= 0x4e and c.yi <= 0

## offside_entry_check (0x4dcdd): the puck carried into the attacking zone (past y 0x4e) while the
## team is flagged offside (check_offside)
static func offside_entry_check(sim: Sim, c: Entity) -> bool:
	if not sim.opt_offsides or sim.penalty_shot or sim.penalty_shot_setup:
		return false
	var py := sim.puck.yi if (c.flags & Entity.F_ATTACK_UP) else -sim.puck.yi
	if py < 0x4e or (sim.team_of(c).flags & Team.FL_OFFSIDE) == 0 or sim.no_stats:
		return false
	Rules.maybe_queue_infraction(sim, c, Rules.INF_OFFSIDE)
	return true

## puck_check_players (0x548ac): the puck against the entities next to it in the draw order (sorted
## by y): upwards, then downwards, while their y is within 0x28 of the puck's
static func puck_check_players(sim: Sim) -> void:
	var puck := sim.puck
	if absi(puck.yi) > 0x190:
		puck.vy = 0
		puck.vx = 0
	if puck.zi > 0x10:
		return      # too high to be played
	var k := sim.draw_pos[puck.slot]
	while k != 0x10:
		var s := sim.draw_list[k + 1]
		if sim.draw_keys[s] - puck.yi > 0x28:
			break
		puck_player_interaction(sim, puck, s)
		k += 1
	k = sim.draw_pos[puck.slot]
	while k != 0:
		var s := sim.draw_list[k - 1]
		if puck.yi - sim.draw_keys[s] > 0x28:
			return
		puck_player_interaction(sim, puck, s)
		k -= 1

## puck_player_interaction (0x5428a): the puck against one player (or the referee):
##  - the goalie reaches it with his stick: the reach (stick_offset_from_frame) grows with the
##    rating of his animation (stickhandling_skill) and shrinks with the speed of the puck, the
##    height of the blade limits the height of the puck -> goalie_save; then also, like a puck
##    against his body (within 10) -> puck_hits_player
##  - a skater within 14 of the point his frame stands on (0xc4, 0x31 while the puck's timer_c
##    runs; 0x24 in the frames 0x430-0x44f) gets it (goalie_save, the shared "gets the puck")
##  - otherwise a skater or the referee near the blade of a stick handling frame (0x431-0x44f,
##    odd) with the puck low, or near his body (8, 0x10 in frames past 0x44f) -> attach_puck_to_stick
## The squared distance (and for puck_hits_player the offsets) are the scratch values the
## original leaves for the routine it calls.
static func puck_player_interaction(sim: Sim, puck: Entity, slot: int) -> void:
	if slot == sim.puck_carrier:
		return
	if slot > 0xb and slot != Entity.Slot.REFEREE:
		return
	var e := sim.entities[slot]
	if (e.flags & Entity.F_ARRIVED) or e.timer_c != 0:
		return
	var mirrored := (e.flags4 & Entity.F4_MIRROR) != 0
	if (e.flags2 & Entity.F2_UNSELECTABLE) == 0 and e.line_slot == 0:
		var skill := stickhandling_skill(e)
		var sum := absi(Sim._s16(puck.vx)) + absi(Sim._s16(puck.vy))
		var speed := Sim._s16(sum) if (sum & 0xffff) != 0 else 1
		var reach := Sim._s16(((skill << 11) - 0xfa0) / speed)
		if reach < 0:
			reach = 0
		if reach > 4:
			reach = 4
		var so := Tables.stick_offset(e.frame, mirrored)
		var fo := Tables.frame_offset(e.frame, mirrored)
		var sa := Sim._s16(so.x - fo.x)
		var sb := absi(Sim._s16(so.y - fo.y))
		var sa43 := Sim._s16((absi(sa) << 2) / 3)
		var c := Sim._s16(absi(sa) + reach)
		var a := absi(Sim._s16(fo.x + e.xi - puck.xi))
		if a < c:
			var b := absi(Sim._s16(fo.y + e.yi - puck.yi))
			if b < c:
				var top := Sim._s16(sa43 + sb)
				if top <= 5:
					top = 5
				var low := Sim._s16(sb - sa43 - reach)
				if Sim._s16(top + reach) >= puck.zi and (low < 0 or low < puck.zi):
					var d2 := a * a + b * b
					var r2 := c * c
					if puck.timer_c > 0:
						r2 >>= 2
					if Sim._s16(r2) >= Sim._s16(d2):
						Rules.two_line_pass_check(sim, e)
						goalie_save(sim, puck, e, d2)
	elif (e.flags2 & Entity.F2_UNSELECTABLE) == 0 and e.line_slot >= 0 and slot != Entity.Slot.REFEREE \
			and puck.zi <= 5 and puck.vz <= 0x200:
		var fo := Tables.frame_offset(e.frame, mirrored)
		var a := Sim._s16(fo.x + e.xi - puck.xi)
		if absi(a) <= 0xe:
			var b := Sim._s16(fo.y + e.yi - puck.yi)
			if absi(b) <= 0xe:
				var d2 := a * a + b * b
				var r2 := 0x31 if puck.timer_c > 0 else 0xc4
				if d2 <= r2 and (e.frame < 0x430 or e.frame > 0x44f or d2 <= 0x24):
					goalie_save(sim, puck, e, d2)
					return
	if e.line_slot == 0:
		# a loose puck against the goalie's body
		var a := Sim._s16(e.xi - puck.xi)
		if absi(a) > 0xa:
			return
		var b := Sim._s16(e.yi - puck.yi)
		if absi(b) > 0xa or a * a + b * b > 0x64:
			return
		Rules.two_line_pass_check(sim, e)
		puck_hits_player(sim, puck, e, a, b)
		return
	var f := e.frame
	if f >= 0x431 and f <= 0x44f and (f & 1) and puck.zi < 8:
		# the blade of the stick, at half the offset of stick_offsets
		var so := Tables.stick_offset(f, mirrored)
		var sa := so.x >> 1
		var sb := so.y >> 1
		var r := absi(sa)
		var a := Sim._s16(sa + e.xi - puck.xi)
		if absi(a) <= r:
			var b := Sim._s16(sb + e.yi - puck.yi)
			if absi(b) <= r:
				var d2 := a * a + b * b
				if r * r >= d2:
					attach_puck_to_stick(sim, puck, e, d2)
					return
	var near := 8
	var near2 := 0x40
	if f > 0x44f:
		near = 0x10
		near2 = 0x100
	var a := Sim._s16(e.xi - puck.xi)
	if absi(a) > near:
		return
	var b := Sim._s16(e.yi - puck.yi)
	if absi(b) > near:
		return
	var d2 := a * a + b * b
	if d2 > near2:
		return
	attach_puck_to_stick(sim, puck, e, d2)

## stickhandling_skill (0x5414e): the rating that goes with the animation (by the hand he shoots
## with): +0x5d / +0x62 for 0xb1, 0xc9, 0xe1, 0x11d5, +0x5f / +0x61 for 0x101, 0x119, 0x121d,
## otherwise +0x5b
static func stickhandling_skill(e: Entity) -> int:
	var a := e.anim
	var lh := e.left_handed != 0
	if a == 0xb1:
		return e.pass_skill if lh else e.check_skill
	if a == 0xc9 or a == 0xe1 or a == 0x11d5:
		return e.check_skill if lh else e.pass_skill
	if a == 0x119:
		return e.offense if lh else e.endurance
	if a == 0x101 or a == 0x121d:
		return e.endurance if lh else e.offense
	return e.shot_skill

## the energy of a player (team record +0x46, by roster index)
static func _team_energy(sim: Sim, e: Entity) -> int:
	var r := Entity.to_s8(e.roster_idx)
	if r < 0 or r >= 28:
		return 0x1000
	return Entity.to_s16(sim.team_of(e).energy[r])

## goalie_save (0x57483): a player gets to the puck (d2: the squared distance the caller measured).
## A goalie first ends the shot (shot_landed) and is credited a save worth the SAVED clip (once a
## period: save_clip_shown) when the home goalie stops a hard shot from the far zone. A loose puck
## is taken (take_puck) unless faster than the hold speed (13000 + 700 x +0x60, without the bonus
## while a shot is on its way) — the pass receiver takes it one time in two anyway — else it
## rebounds off him. With a carrier it is a stick check: the puck comes loose (release_puck_random)
## when he is within 6 of an opponent and wins the roll of the +0x60 ratings and energies.
static func goalie_save(sim: Sim, puck: Entity, e: Entity, d2: int) -> void:
	var save := 0
	if e.line_slot == 0:
		if sim.no_stats:
			return
		e.save_result = 0
		if not sim.save_clip_shown and (e.flags & Entity.F_PLAYER2) == 0 and sim.shot_in_flight \
				and (e.slot < 6) != (sim.last_shooter < 6):
			var sh := sim.entities[sim.last_shooter]
			if absi(sh.yi) > 0x58 and (sh.yi > 0) != ((e.flags & Entity.F_ATTACK_UP) != 0):
				var vy := absi(Sim._s16(puck.vy))
				if vy > 0x2ee0 or (vy > 0x1770 and e.anim >= 0x119d and e.anim <= 0x121d):
					save = 1
		shot_landed(sim)
	e.flags &= ~Entity.F_HAS_TARGET
	if sim.puck_carrier >= 0:
		if e.anim >= 0x13c5 and e.anim <= 0x14ad:
			return
		var c := sim.entities[sim.puck_carrier]
		if ((e.flags ^ c.flags) & Entity.F_PLAYER2) == 0:
			return
		if d2 > 0x24:
			return
		if e.line_slot != 0:
			if c.line_slot == 0:
				return
			var cs := Sim._s16((_team_energy(sim, c) * c.goalie_skill) >> 12)
			var es := Sim._s16((_team_energy(sim, e) * e.goalie_skill) >> 12)
			var odds := Sim._s16(cs + 0x20 - es)
			if (c.flags & Entity.F_USER) and (e.flags & Entity.F_USER) == 0:
				odds = Sim._s16(odds + _div_trunc(odds, 8))
			if Sim._s16(sim.random(odds)) > 2:
				return
		c.timer_c = Sim._s16(Sim._s16((_team_energy(sim, c) * c.goalie_skill) >> 12) + 0x14)
		e.timer_c = Sim._s16(Sim._s16((_team_energy(sim, e) * e.goalie_skill) >> 12) + 0x14)
		sim.last_passer = c.slot
		sim.action_pass = false
		sim.action_shot = false
	else:
		if e.line_slot == 0 and d2 > 0x40:
			return
		var vx := Sim._s16(puck.vx)
		var vy := Sim._s16(puck.vy)
		var v2 := vx * vx + vy * vy
		var hold := 0
		if not sim.shot_in_flight:
			hold = (e.goalie_skill * 0x2bc) & 0xffff
		hold = Sim._s16(hold + 0x32c8)
		if e.anim < 0x13c5 or e.anim > 0x14ad:
			if v2 <= hold * hold or (e.slot == sim.pass_target and sim.random(2) != 0):
				puck.vz = 0
				take_puck(sim, e)
				if e.line_slot != 0:
					return
				if puck.zi > 8:
					puck.z = (8 << 16) | (puck.z & 0xffff)
				puck.vx = Sim._s16(puck.vx) >> 2
				puck.vy = Sim._s16(puck.vy) >> 2
				e.save_result = save
				return
		e.timer_c = 8
	sim.play_sfx(0x99)
	update_carrier(sim, e)
	release_puck_random(sim)

## a signed division truncated towards zero, like the original's shift with the sign correction
static func _div_trunc(v: int, d: int) -> int:
	return -((-v) / d) if v < 0 else v / d

## puck_hits_player (0x57096): a loose puck against a goalie's body (a, b: the goalie's offset from
## the puck). It ends a shot, may count as a save (as in goalie_save, the speed is |vx| + |vy|);
## slow enough for his rating (+0x5b) he takes it (take_puck), otherwise it is knocked loose from a
## carrier and bounces off him (half the offset of the puck, in the direction opposite his motion)
static func puck_hits_player(sim: Sim, puck: Entity, e: Entity, a: int, b: int) -> void:
	var save := 0
	if sim.no_stats:
		return
	# the side of the body that is hit (kept in scratch_e03ac, not used further): a straight hit
	# draws a random number
	var rel := (Tables.direction8(Sim._s16(-a), Sim._s16(-b)) - ((e.heading >> 16) & 0xffff)) & 7
	if (rel & 3) == 0:
		sim.random(0x100)
	if e.frame >= 0x206 and e.frame < 0x216 and puck.zi >= 5:
		return
	e.save_result = 0
	if not sim.save_clip_shown and (e.flags & Entity.F_PLAYER2) == 0 and sim.shot_in_flight \
			and (e.slot < 6) != (sim.last_shooter < 6):
		var sh := sim.entities[sim.last_shooter]
		if absi(sh.yi) > 0x58 and (sh.yi > 0) != ((e.flags & Entity.F_ATTACK_UP) != 0):
			var s := Sim._s16(absi(Sim._s16(puck.vy)) + absi(Sim._s16(puck.vx)))
			if s > 0x4268 or (s > 0x1770 and e.anim >= 0x119d and e.anim <= 0x121d):
				save = 1
	shot_landed(sim)
	update_carrier(sim, e)
	if not sim.play_stopped and absi(Sim._s16(puck.vy)) > 0xfa0:
		sim.play_sfx(0xa1 if (e.flags & Entity.F_PLAYER2) else 0x7d)
	sim.play_sfx(0x9d if absi(Sim._s16(puck.vy)) > 0xbb8 else 0xa3)
	if sim.puck_carrier < 0:
		var lim := Sim._s16(sim.random(Sim._s16(((((e.shot_skill * 5) >> 2) + 2) << 9))) + 0x2000)
		if absi(Sim._s16(puck.vx)) <= lim and absi(Sim._s16(puck.vy)) <= lim and (e.flags2 & Entity.F2_UNSELECTABLE) == 0:
			puck.vz = 0
			if puck.zi > 8:
				puck.z = (8 << 16) | (puck.z & 0xffff)
			puck.vx = Sim._s16(puck.vx) >> 2
			puck.vy = Sim._s16(puck.vy) >> 2
			take_puck(sim, e)
			e.save_result = save
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
		puck.z = (10 << 16) | (puck.z & 0xffff)
	e.timer_c = 10
	e.target_y = 4
	var pa := Sim._s16(puck.xi - e.xi)
	var pb := Sim._s16(puck.yi - e.yi)
	if pb == 0:
		var fo := Tables.frame_offset(e.frame, (e.flags4 & Entity.F4_MIRROR) != 0)
		pa = fo.x
		pb = fo.y
	if pb == 0:
		pb = 1
	if (pb ^ Sim._s16(e.vy)) >= 0:
		pb = Sim._s16(-pb)
	puck.vx = Sim._s16(((Entity.to_s8(pa) >> 1) << 8) | (puck.vx & 0xff))
	puck.vy = Sim._s16(((Entity.to_s8(pb) >> 1) << 8) | (puck.vy & 0xff))
	puck_spin(sim, puck, pa)

## attach_puck_to_stick (0x56d06): the puck meets a skater's stick or body (d2: the squared distance
## the caller measured; a low puck in another frame than the rolling ones needs its low 4 bits clear,
## a rolling one at stick height is too high). He becomes the carrier (update_carrier, not the
## referee): the high bytes of the puck's velocity hold its offset from him (that of his frame when
## level with him). A puck in the air hurts: hard enough (speed over 3000) and high (over 12) it
## knocks him down, otherwise he is stung (animation 0x84b).
static func attach_puck_to_stick(sim: Sim, puck: Entity, e: Entity, d2: int) -> void:
	var f := puck.frame
	if f >= 0x430 and f <= 0x467:
		if f <= 0x44f and (f & 1) and puck.zi > 8:
			return
	elif puck.zi <= 8 and (d2 & 0xf) != 0:
		return
	if e.slot != Entity.Slot.REFEREE:
		update_carrier(sim, e)
	puck.vz = 0
	e.timer_c = 8
	var a := Sim._s16(puck.xi - e.xi)
	var b := Sim._s16(puck.yi - e.yi)
	if b == 0:
		var fo := Tables.frame_offset(e.frame, (e.flags4 & Entity.F4_MIRROR) != 0)
		a = fo.x
		b = fo.y
	var vx := Sim._s16(puck.vx)
	var vy := Sim._s16(puck.vy)
	puck.vx = Sim._s16(((a & 0xff) << 8) | (puck.vx & 0xff))
	puck.vy = Sim._s16(((b & 0xff) << 8) | (puck.vy & 0xff))
	puck_spin(sim, puck, a)
	if puck.zi <= 8:
		if e.anim != 0x84b:
			sim.play_sfx(0xa3)
		return
	var sfx := 0xa3
	if vx * vx + vy * vy > 0x895440 and puck.zi > 0xc:
		sfx = 0xa2
		knock_down(sim, puck, e)
	if e.anim != 0x84b:
		sim.play_sfx(sfx)
	if (e.flags & Entity.F_BUSY) == 0 and e.slot != Entity.Slot.REFEREE:
		e.flags |= Entity.F_BUSY
		Anim.set_animation(e, 0x84b)    # stung by the puck

## take_puck (0x56f5a): a player becomes the carrier. A penalty shooter playing the puck again ends
## the penalty shot; the other team's history of carriers no longer gives assists; the first touch
## after a faceoff wins it (an offensive zone faceoff past y 0x4e), the crowd stirs; a completed
## pass; a goalie ends the shot and gets 140 steps (5 after a poke check) to play the puck; the
## user follows the puck to the new carrier of his team
static func take_puck(sim: Sim, e: Entity) -> void:
	sim.puck_carrier = e.slot
	var team := sim.team_of(e)
	var opp := sim.opponents_of(e)
	if sim.penalty_shot and Entity.to_s8(e.roster_idx) == team.carrier_history[0]:
		Rules.end_penalty_shot(sim)
		sim.one_timer = false
		sim.breakaway = false
	opp.carrier_history[1] = Entity.to_s16(opp.carrier_history[1] | 0xff00)
	opp.carrier_history[2] = Entity.to_s16(opp.carrier_history[2] | 0xff00)
	opp.flags |= 8
	if sim.misc_first_touch:
		sim.misc_first_touch = false
		if not sim.no_stats:
			team.faceoffs_won += 1
			var up := (e.flags & Entity.F_ATTACK_UP) != 0
			if (sim.puck.yi > 0x4e and up) or (sim.puck.yi < -0x4e and not up):
				team.offensive_faceoffs += 1
		sim.add_crowd(200, 1000)
		if (e.flags & Entity.F_PLAYER2) == 0:
			sim.excitement += 10
	else:
		sim.play_sfx(0x9b)
	pass_completed(sim, e)
	sim.action_pass = false
	sim.action_shot = false
	if e.line_slot == 0:
		shot_landed(sim)
		Rules.end_penalty_shot(sim)
		e.timer_b = 5 if e.anim == 0x181 else 0x8c   # time until the goalie must play the puck
	follow_puck_user_switch(sim, e.slot)

## pass_completed (0x50afe): a pass to a team mate (the pass target, shot_power's high word) counts
## for the team
static func pass_completed(sim: Sim, e: Entity) -> void:
	if sim.pass_target >= 0 and (sim.pass_target < 6) == (e.slot < 6) and not sim.no_stats:
		sim.team_of(e).passes_completed += 1
	sim.pass_target = -1

## follow_puck_user_switch (0x5b1ce): a user follows the puck to the new carrier of his team (the
## second user first when he made the pass)
static func follow_puck_user_switch(sim: Sim, slot: int) -> void:
	if sim.stubbed("follow_puck_user_switch", [slot]):
		return
	if slot == sim.user1_slot or slot == sim.user2_slot:
		return
	var t := 2 if slot >= 6 else 1
	if sim.user2_slot == sim.last_passer:
		if sim.user2_team == t:
			sim.user2_slot = sim.find_switch_target(slot, sim.user2_slot)
			return
		if t != sim.user1_team:
			return
	elif sim.user1_team != t:
		if t != sim.user2_team:
			return
		sim.user2_slot = sim.find_switch_target(slot, sim.user2_slot)
		return
	sim.user1_slot = sim.find_switch_target(slot, sim.user1_slot)

## shot_landed (0x55d28): the shot in flight (stop_flags 0x10) reached a player or the net: with the
## puck in the shooter's attacking half a shot on goal (the crowd, the excitement, the team's
## shots and power play shots, the game summary, the shooter's shots, the goalie's shots against)
static func shot_landed(sim: Sim) -> void:
	if not sim.shot_in_flight:
		return
	sim.shot_in_flight = false
	if sim.play_stopped or sim.last_shooter < 0:
		return
	var s := sim.entities[sim.last_shooter]
	if ((s.flags & Entity.F_ATTACK_UP) != 0) != (sim.puck.yi > 0):
		return
	sim.add_crowd(100, 1000)
	sim.excitement += 10
	if sim.no_stats:
		return
	var team := sim.team_of(s)
	var opp := sim.opponents_of(s)
	team.shots += 1
	if sim.power_play and team.skaters_on_ice > opp.skaters_on_ice:
		team.pp_shots += 1
	sim.gs_trailer[4 if (s.flags & Entity.F_PLAYER2) else 2] += 1
	var r := Entity.to_s8(s.roster_idx)
	if r < 0x19:
		team.add_stat(r, Team.ST_SHOTS)
	var gr := Entity.to_s16(opp.goalie_request)
	var lt := Lines.line_table(opp)
	if gr >= 0 and 0x24 + gr < lt.size():
		var g := lt[0x24 + gr] - 0x19
		if g >= 0 and g < 3:
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

## do_pass (0x54df4): the carrier lets the puck go. A computer player with a lane picked
## (ai_choose_pass_target: pass_ok, the target in +0x48) passes to him directly; otherwise the
## shot power is the passing rating (8 for a goalie) x 4 + 0xa0 and the receiver is the team mate
## nearest to the puck in the aimed direction (pending_dir, one step either side counting 0x10000
## more): a user with an open lane passes directly, else the pass leads him (pass_lead); with nobody
## there the puck goes the aimed way at that power (a blind pass). A goalie clears it up the ice
## (and the users follow the puck), a skater passes fore or backhand.
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
	sim.shot_power = (8 if e.line_slot == 0 else e.pass_skill) * 4 + 0xa0
	var best: Entity = null
	var best_d := 0xffffffff
	var first := 0 if e.slot < 6 else 6
	for i in 6:
		var p := sim.entities[first + i]
		if p == e or p.line_slot <= 0 or (p.flags2 & Entity.F2_UNSELECTABLE):
			continue
		var dx := Sim._s16(p.xi - puck.xi)
		var dy := Sim._s16(p.yi - puck.yi)
		var d := (Tables.direction8(dx, dy) - sim.pending_dir) & 7
		if d <= 1 or d == 7:
			var score := (dy * dy + dx * dx + (0 if d == 0 else 0x10000)) & 0xffffffff
			if score <= best_d:
				best_d = score
				best = p
	if best == null:
		# (no direction, 8: the original reads past the table into random_seed, which follows it)
		var v: Array = Tables.dir8_vectors[sim.pending_dir] if sim.pending_dir < 8 \
			else [Sim._s16(sim.seed), Sim._s16(sim.seed >> 16)]
		puck.vy = Sim._s16(_div_trunc(Sim._s32((v[1] * sim.shot_power) << 10), 3000) + e.vy)
		puck.vx = Sim._s16(_div_trunc(Sim._s32((v[0] * sim.shot_power) << 10), 3000) + e.vx)
		puck.vz = sim.random(0x1000)
	else:
		if (e.flags & Entity.F_USER) and pass_lane_ok(sim, e, best):
			pass_to_entity(sim, e, best)
			return
		pass_lead(sim, best)
	var a := 0
	if e.line_slot == 0:
		# the goalie clears towards his own blue line
		if (puck.vy < 0) != ((e.flags & Entity.F_ATTACK_UP) == 0):
			puck.vy = Sim._s16(-puck.vy)
		a = 0x1b9
		e.flags2 |= Entity.F2_TURNING
		if e.flags & Entity.F_USER:
			if best != null and (best.flags & Entity.F_USER) == 0:
				if e.slot == sim.user1_slot:
					if sim.user1_slot != best.slot:
						sim.user1_slot = sim.find_switch_target(best.slot, sim.user1_slot)
				elif best.slot != sim.user2_slot:
					sim.user2_slot = sim.find_switch_target(best.slot, sim.user2_slot)
			else:
				sim.switch_to_nearest(e, 0 if e.slot == sim.user1_slot else 1)
	else:
		var d := Tables.direction8(puck.vx, puck.vy)
		a = 0x3c1 if shot_is_backhand(e, d) else 0x389
	Anim.set_animation(e, a)
	e.flags |= Entity.F_BUSY
	# a lifted pass (the high byte of vz 6 or more) sounds different
	sim.play_sfx(0x99 if Entity.to_s8(puck.vz >> 8) >= 6 else 0x98)

## pass_to_entity (0x54d63): a direct pass: the receiver (PASS_RECEIVER) skates onto a soft puck
## (a random speed, less for a better passer); the puck's pickup timer is cleared
static func pass_to_entity(sim: Sim, e: Entity, target: Entity) -> void:
	e.timer_c = 0x28
	if not sim.no_stats:
		sim.team_record(e).passes += 1
	sim.pass_target = target.slot
	e.pass_ok = 0
	target.set_state_reset(Entity.State.PASS_RECEIVER)
	sim.puck.vz = 0
	var spread := Sim._s16((0x12 - e.pass_skill) * 0x14)
	sim.puck.vx = Sim._s16(sim.random(spread))
	sim.puck.vy = Sim._s16(sim.random(spread))
	sim.puck.timer_c = 0

## pass_lead (0x551cf): the pass is led to where the receiver (PASS_RECEIVER) will be: the flight
## time t (in units of 4 steps, 1..0x18) solves |q + v t| = speed t for his offset q (from the point
## his frame stands on, /4) and velocity v (x 0xf0 / 0x10000) at a quarter of the shot power, in the
## original's 16 bit words; the puck is lifted up to 12 (random above 6), the receiver waits t x 8 - 10
## steps (a byte) and skates to the meeting point; the puck's pickup timer runs 6 steps less
static func pass_lead(sim: Sim, target: Entity) -> void:
	var puck := sim.puck
	if not sim.no_stats:
		sim.team_record(target).passes += 1
	sim.pass_target = target.slot
	target.set_state_reset(Entity.State.PASS_RECEIVER)
	var o := Tables.frame_offset(target.frame, (target.flags4 & Entity.F4_MIRROR) != 0)
	var dx := Sim._s16(o.x + target.xi - puck.xi)
	var dy := Sim._s16(o.y + target.yi - puck.yi)
	var qx := dx >> 2
	var qy := dy >> 2
	var tvx := Sim._s16((Sim._s16(target.vx) * 0xf0) >> 16)
	var tvy := Sim._s16((Sim._s16(target.vy) * 0xf0) >> 16)
	var b := Sim._s16((tvx * qx + tvy * qy) * 2)
	var speed := sim.shot_power >> 2
	var a := Sim._s16(tvx * tvx + tvy * tvy - Sim._s16(speed) * Sim._s16(speed))
	var disc := Sim._s32(b * b - Sim._s32(Sim._s32((qx * qx + qy * qy) * a) << 2))
	var root := Sim.isqrt32(disc) if disc > 0 else 0
	a = a >> 2
	if a == 0:
		a = 1
	var t := 0
	var r := Sim._s16(root)
	for k in 2:
		t = Sim._s16(_div_trunc(r - b, a))
		if t >= 0:
			break
		r = Sim._s16(-root)
	if t <= 0:
		t = 1
	if t > 0x18:
		t = 0x18
	var h := t if t < 0xc else 0xc
	if h > 6:
		h = sim.random(h >> 1) + ((h + 1) >> 1)
	puck.vz = Sim._s16(((h & 0xff) << 8) | (puck.vz & 0xff))
	target.react_timer = Entity.to_s8((t << 3) - 10)
	# the puck's +0x3e (word_dff5a): while it runs, the puck is harder to pick up (puck_player_interaction)
	puck.timer_c = target.react_timer - 6
	var lx := ((tvx * t) >> 1) + dx
	var ly := ((tvy * t) >> 1) + dy
	target.target_x = Sim._s16(puck.xi + lx)
	target.target_y = Sim._s16(puck.yi + ly)
	var tt := Sim._s16(t * 0x78)
	puck.vx = Sim._s16(_div_trunc(Sim._s32(lx << 16), tt))
	puck.vy = Sim._s16(_div_trunc(Sim._s32(ly << 16), tt))

## pass_lane_ok (0x54c09): may a user pass directly (pass_to_entity) to a team mate: not a goalie,
## no breakaway, from his own side of his blue line, back towards his own net, both skating that
## way, the receiver (a step ahead) on the passer's side of the line 0x4e, within 0x3c and 0x28, and
## the passer in the direction the receiver is skating
static func pass_lane_ok(sim: Sim, e: Entity, target: Entity) -> bool:
	var up := (e.flags & Entity.F_ATTACK_UP) != 0
	if e.line_slot == 0:
		return false
	if Rules.count_defenders_ahead(sim):
		return false
	var ty := target.yi
	var ey := e.yi
	var line := 0x4e if up else -0x4e
	if (ey > line) != up:
		return false
	if absi(ey) <= absi(ty) or absi(ey) > 0x76:
		return false
	if up and (target.vy < 0 or e.vy < 0):
		return false
	if not up and (target.vy > 0 or e.vy > 0):
		return false
	if ((Entity.to_s8(target.vy >> 8) + ty - 0x4e) ^ (ey - 0x4e)) < 0:
		return false
	if absi(ty - ey) > 0x3c or absi(e.xi - target.xi) > 0x28:
		return false
	var tdir := Tables.direction8(target.vx, target.vy)
	if tdir == 8:
		tdir = (target.heading >> 16) & 0xffff
	var rdir := Tables.direction8(e.xi - target.xi, e.yi - target.yi)
	return ((tdir - rdir + 1) & 7) < 3

# --------------------------------------------------------------------------------------------
# shooting (start_shot, shot_control, do_shot, shot_setup)
# --------------------------------------------------------------------------------------------

## start_shot (0x5786e): the wind up towards the middle of the net line (y 0xf0), fore or backhand;
## the shot power starts at 0xf
static func start_shot(sim: Sim, e: Entity) -> void:
	sim.pending_dir = 8
	sim.action_shot = true
	var target_y := 0xf0 if (e.flags & Entity.F_ATTACK_UP) else -0xf0
	var dir := Tables.direction8(Sim._s16(-e.xi), Sim._s16(target_y - e.yi))
	sim.shot_power = 0xf
	# the player is not "busy" during the wind up: shot_control runs every step until the release
	Anim.set_animation(e, Anim.SHOT_BACKHAND if shot_is_backhand(e, dir) else Anim.SHOT_FOREHAND)

## shot_control (0x578fa): every step of the wind up (the original's scratch inputs: dir the
## control word, 8 none; pressed the buttons that went down; changed those that went down or up).
## At frame 0xe the shot goes (do_shot). The direction held aims it. Before frame 0xa, A or C fake
## it (the deke animations); before frame 8 the power grows, and B let go (or, for a shooter rated
## below 10, frame 5) jumps to the release.
static func shot_control(sim: Sim, e: Entity, dir: int, pressed: int, changed: int) -> void:
	if e.anim_pos >= 0xe:
		do_shot(sim, e)
		return
	if (dir & 8) == 0:
		sim.pending_dir = dir & 7
		sim.scratch_a = dir & 7
	if e.anim_pos >= 0xa:
		return
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
	if e.anim_pos >= 8:
		return
	sim.shot_power = Sim._s16(sim.shot_power + 1)
	if (e.shot_skill < 0xa and e.anim_pos > 4) or (changed & 0x20):
		e.anim_pos = Sim._s16(0xe - e.anim_pos)

## do_shot (0x57c0b): the release. The shot power (less a quarter on the backhand) grows with the
## shooting rating (more for a good shooter near the net, then +1 for each of 10, 13, 14 passed) and
## the energy, x 0x5249 / 0x10000; a weak shot (power / 16 below 3) sounds different. The puck goes
## to the aim point of shot_targets in pending_dir (shot_setup aims a computer player) on the goal
## line, scattered unless the shooter is accurate and close; it is lifted by the target's height.
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
	var sfx := 0xaa
	if e.anim == Anim.SHOT_BACKHAND or e.anim == 0xe2b:
		sim.shot_power = Sim._s16(sim.shot_power - (sim.shot_power >> 2))
	var skill := e.shot_skill
	if skill > 0xc and absi(e.xi) + absi(e.yi) < 0x1f4:
		skill += 2
	if skill > 0xe:
		skill += 1
	if skill > 0xd:
		skill += 1
	if skill > 0xa:
		skill += 1
	var es := Sim._s16((_team_energy(sim, e) * Sim._s16(skill)) >> 12)
	sim.shot_power = Sim._s16(sim.shot_power * (es + 0x14))
	sim.shot_power = Sim._s16(((sim.shot_power * 0x5249) & 0xffffffff) >> 16)
	if sim.breakaway:
		Rules.count_defenders_ahead(sim)
		sim.breakaway = sim.defenders_ahead != 0
	if Sim._s16(3 - (sim.shot_power >> 4)) > 0:
		sfx = 0x9a
	sim.puck_carrier = -1
	e.timer_c = 0x10
	sim.last_passer = e.slot
	var goal_y := 0xe8 if (e.flags & Entity.F_ATTACK_UP) else -0xe8
	var aim := sim.pending_dir
	var dx := Sim._s16(Tables.shot_targets[aim * 2] - puck.xi)
	var dy := Sim._s16(goal_y - puck.yi)
	var az := Sim._s16(Tables.shot_targets[aim * 2 + 1])
	var dist := Sim.approx_distance(dx, dy)
	if dist == 0:
		dist = 1
	if not sim.no_stats:
		var acc := e.shot_accuracy
		if acc > 0xe:
			acc += 1
		if acc > 0xd:
			acc += 1
		if dist > 0xc8 or Sim._s16(sim.random(e.shot_accuracy + 0x10)) <= 0xe:
			var spread := ((dist * ((sim.shot_power >> 4) - acc + 0x10)) & 0xffff) >> 6
			if dist < 0xfa:
				spread >>= 1
			if spread > 0xa0:
				spread = 0xa0
			dx = Sim._s16(dx + sim.random(Sim._s16(spread * 2)) - spread)
			if spread > 0x3c:
				spread = 0x3c
			var sy := spread if dy >= 0 else spread >> 1
			dy = Sim._s16(dy + sim.random(Sim._s16(sy * 2)) - sy)
			var sz := spread >> 1
			if dist < 0xa0:
				sz = _div_trunc(spread, 3)
			if dist < 0x50:
				sz = spread >> 2
			az = Sim._s16(az + sim.random(Sim._s16(sz)))
	var k := sim.shot_power * 0x3b
	puck.vx = Sim._s16(_div_trunc(Sim._s32(dx * k), dist))
	puck.vy = Sim._s16(_div_trunc(Sim._s32(dy * k), dist))
	if sim.penalty_shot:
		# on a penalty shot the puck is at least as fast as the shooter, plus 0x1f4
		if (e.vx ^ puck.vx) >= 0 and absi(puck.vx) < absi(e.vx):
			puck.vx = Sim._s16(e.vx + 0x1f4)
		if (e.vy ^ puck.vy) >= 0 and absi(puck.vy) < absi(e.vy):
			puck.vy = Sim._s16(e.vy + 0x1f4)
	if az != 0:
		# unsigned 32 bit divisions, like the original's
		var lift := (((sim.shot_power * 0x44 * az) & 0xffffffff) / dist) & 0xffffffff
		lift = (lift + ((dist * 0xb33) & 0xffffffff) / (sim.shot_power & 0xffffffff)) & 0xffff
		if lift > 0x1800:
			lift = 0x1800
		puck.vz = Sim._s16(lift)
	sim.play_sfx(sfx)
	if sim.penalty_shot:
		e.set_state(Entity.State.NEAREST)

## shot_setup (0x57a98): a computer shooter aims at the side of the net (0x12 either side of the
## middle) the goalie leaves open (his position and a part of his velocity), or the middle
static func shot_setup(sim: Sim, e: Entity) -> void:
	if e.flags & Entity.F_USER:
		return
	var puck := sim.puck
	var goalie: Entity = null
	var first := 6 if e.slot < 6 else 0
	for i in 6:
		var p := sim.entities[first + i]
		if p.line_slot == 0:
			goalie = p
			break
	if goalie == null:
		sim.pending_dir = 8
		return
	var gx := Sim._s16(goalie.xi + (Sim._s16(goalie.vx) >> 9) - puck.xi)
	var gy := Sim._s16(goalie.yi + (Sim._s16(goalie.vy) >> 9) - puck.yi)
	var d := Sim.approx_distance(gx, gy)
	if d == 0:
		d = 1
	var goal_y := 0xe8 if (e.flags & Entity.F_ATTACK_UP) else -0xe8
	var num := gx * (goal_y - puck.yi)
	var side := Sim._s16(_div_trunc(num - (0x12 - puck.xi) * gy, d) + _div_trunc(num - (-0x12 - puck.xi) * gy, d))
	if absi(side) > 0x2c:
		sim.pending_dir = 0
		return
	if e.flags & Entity.F_ATTACK_UP:
		side = -side
	sim.pending_dir = 2 if side >= 0 else 6

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
					# (and the goalie's y with bit 2 clear, as the original tests it)
					if sim.random(0x14 - p.check_skill) < 3 and not sim.no_stats and (g.yi & 4) == 0:
						Rules.maybe_queue_infraction(sim, p, Rules.INF_INTERFERENCE)
		var t := p
		p = g
		g = t

## knock_down (0x562db): `victim` falls (or only stumbles: 0x8d3). Against the boards he is put
## into a board animation (knockdown_position) and boarding may be called; a fall can injure him
## (injure_player). The hitter can be a player, the referee or the puck.
static func knock_down(sim: Sim, hitter: Entity, victim: Entity) -> void:
	if sim.stubbed("knock_down", [hitter.slot, victim.slot]):
		return
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
	# the puck and the nets have line slot 0 (like a goalie), the referee -1
	var hitter_slot := hitter.line_slot
	var anim: int
	if victim.goalie_skill >= 0xc and sim.random(0x10) + 0x10 > victim.speed:
		victim.timer_d = 0x3c
		anim = 0x8d3
	else:
		if hitter_slot != 0 and not sim.no_stats and not sim.play_stopped:
			sim.team_record(hitter).hits += 1
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
			if hitter_slot == 0 or not sim.opt_penalties or sim.box_count[1 if (hitter.flags & Entity.F_PLAYER2) else 0] >= 8 \
					or not Rules.injury_check(sim, hitter):
				Rules.queue_infraction(sim, hitter, Rules.INF_INJURY)
			else:
				# the hit that injured him is called: from behind (a major) or roughing, and the
				# play stops at once (start_stoppage from the first free entry of the queue on)
				var d := Tables.direction8(victim.xi - hitter.xi, victim.yi - hitter.yi)
				var hf := hitter.facing
				var behind := ((d - hf + 1) & 7) < 3 and ((victim.facing - hf + 1) & 7) < 3
				Rules.queue_infraction(sim, hitter, Rules.INF_CHECK_FROM_BEHIND if behind else Rules.INF_ROUGHING)
				for i in 0x20:
					if i >= sim.infractions.size():
						Rules.start_stoppage(sim, i - 1)
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
	if sim.stubbed("injure_player", [e.slot]):
		return
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
