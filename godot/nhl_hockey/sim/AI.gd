class_name AI
## The AI state machine: ports of the `ai_*` handlers dispatched by sim_update_players through
## ai_state_handlers[state]. Every player, the puck, its shadow and the referee run one handler per
## step. States and handlers are listed in re/nhl_hockey/STRUCTURES.md; the mapping below follows
## ai_state_names. The anthem, the goal celebration, the three stars and the cup ceremony are in
## Ceremonies.gd.

static func dispatch(sim: Sim, e: Entity) -> void:
	match e.state():
		Entity.State.DEF_OFFENSE: def_offense(sim, e)
		Entity.State.DEF_DEFENSE: def_defense(sim, e)
		Entity.State.WING_DEFENSE: wing_defense(sim, e)
		Entity.State.WING_OFFENSE: wing_offense(sim, e)
		Entity.State.CENTER_DEFENSE: center_defense(sim, e)
		Entity.State.CENTER_OFFENSE: center_offense(sim, e)
		Entity.State.CELEBRATE: Ceremonies.celebrate(sim, e)
		Entity.State.GOALIE: goalie(sim, e)
		Entity.State.GOALIE_GET_PUCK: goalie_get_puck(sim, e)
		Entity.State.PUCK_CARRIER: puck_carrier(sim, e)
		Entity.State.NEAREST: nearest_to_puck(sim, e)
		Entity.State.SHOOT: shoot(sim, e)
		Entity.State.PASS_RECEIVER: pass_receiver(sim, e)
		Entity.State.FACEOFF_WAIT: faceoff_wait(sim, e)
		Entity.State.FACEOFF: faceoff(sim, e)
		Entity.State.PUCK_NORMAL: puck_normal(sim, e)
		Entity.State.PUCK_SHADOW: puck_shadow(sim, e)
		Entity.State.PUCK_IDLE: PuckLogic.puck_flat(sim, e)
		Entity.State.PUCK_FACEOFF: puck_faceoff(sim, e)
		Entity.State.PUCK_FACEOFF2: puck_faceoff2(sim, e)
		Entity.State.REF_FACEOFF: ref_faceoff(sim, e)
		Entity.State.REF_NORMAL: ref_normal(sim, e)
		Entity.State.REF_CALL_PENALTY: ref_call_penalty(sim, e)
		Entity.State.REF_PICKUP: ref_pickup(sim, e)
		Entity.State.REF_GOTO_FACEOFF: ref_goto_faceoff(sim, e)
		Entity.State.REF_POINT_GOAL: ref_point_goal(sim, e)
		Entity.State.REF_GET_NEW_PUCK: ref_get_new_puck(sim, e)
		Entity.State.ALL_GOTO_FACEOFF: all_goto_faceoff(sim, e)
		Entity.State.BENCH: Lines.bench(sim, e)
		Entity.State.EXIT_BENCH: Lines.exit_bench(sim, e)
		Entity.State.BENCH_WAIT: Lines.bench_wait(sim, e)
		Entity.State.PENALTY_BOX: penalty_box(sim, e)
		Entity.State.DOOR_OPEN: door_open(sim, e)
		Entity.State.EXIT_PENALTY_BOX: exit_penalty_box(sim, e)
		Entity.State.INIT_PERIOD: init_period(sim, e)
		Entity.State.BREAKAWAY: breakaway(sim, e)
		Entity.State.ANTHEM: Ceremonies.anthem(sim, e)
		Entity.State.REF_ANTHEM: Ceremonies.ref_anthem(sim, e)
		Entity.State.THREE_STARS: Ceremonies.three_stars(sim, e)
		Entity.State.REF_THREE_STARS: Ceremonies.ref_three_stars(sim, e)
		Entity.State.STANLEY_CUP: Ceremonies.stanley_cup(sim, e)
		Entity.State.GET_CUP: Ceremonies.get_cup(sim, e)
		Entity.State.PUCK_GIVE_CUP: Ceremonies.puck_give_cup(sim, e)
		Entity.State.REF_PENALTY_SHOT: ref_penalty_shot(sim, e)
		Entity.State.PENALTY_SHOT_WAIT: penalty_shot_wait(sim, e)
		Entity.State.GAME_MISCONDUCT: game_misconduct(sim, e)
		_:
			# states that are not ported: back to the default role
			if e.slot < 12 and e.line_slot >= 0:
				set_default_state(sim, e)

# --------------------------------------------------------------------------------------------
# shared helpers
# --------------------------------------------------------------------------------------------

## set_default_state (0x5a2f8): the positional state of the player's line slot
static func set_default_state(_sim: Sim, e: Entity) -> void:
	if e.line_slot >= 0 and e.line_slot < 7:
		e.set_state(Tables.position_default_state[e.line_slot])

## skate_idle (0x5e9ab)
static func skate_idle(sim: Sim, e: Entity) -> void:
	if (e.flags & (Entity.F_BUSY | Entity.F_USER)) == 0:
		sim.apply_skating(e, 8)

## ai_default_skate (0x4d509): leave the current handler to the one below on the stack
static func default_skate(_sim: Sim, e: Entity) -> void:
	e.push_state()

## the usual preamble of a positional handler; returns false when the handler must stop
static func role_preamble(sim: Sim, e: Entity) -> bool:
	if e.flags & Entity.F_BUSY:
		return false
	if Lines.handle_line_change(sim, e):
		return false
	if sim.play_stopped:
		skate_idle(sim, e)
		return false
	if e.flags & Entity.F_USER:
		return false
	if e.flags & Entity.F_STATE_ENTERED:
		e.flags &= ~Entity.F_STATE_ENTERED
		e.timer_a = 0
		e.want_dir = 8           # (the word +0x28: the direction timer too)
		e.dir_timer = 0
	return true

## net_zone_flags (0x5f04e): outcodes of the player (fe) and his target (ft) against the box
## lo <= y < hi, -hw <= x < hw around a net: 4 below lo, 1 at or above hi, 2 right, 8 left.
## ok is false when both are outside on the same side (the straight line cannot cross the box).
static func net_zone_flags(ex: int, ey: int, tx: int, ty: int, lo: int, hi: int, hw: int) -> Array:
	var fe := 0
	var ft := 0
	if ey < lo:
		fe = 4
		if ty < lo:
			return [false, fe, ft]
	elif ty < lo:
		ft = 4
	if ey < hi:
		if ty >= hi:
			ft = 1
	else:
		fe = 1
		if ty >= hi:
			return [false, fe, ft]
	if ex < hw:
		if tx >= hw:
			ft |= 2
	else:
		fe |= 2
		if tx >= hw:
			return [false, fe, ft]
	if ex < -hw:
		fe |= 8
		if tx < -hw:
			return [false, fe, ft]
	elif tx < -hw:
		ft |= 8
	return [true, fe, ft]

## ai_choose_direction (0x5f151): a skater whose straight path to (tx, ty) would cross a net goes
## around it: the target is replaced by a point beside the post (x = +-(0x2c + m)), in front of the
## net (fy), behind it (by = +-0xfd) or on the goal line. The top net is handled mirrored (y negated,
## outcodes 4 and 1 swapped) so 4 always means behind the net and 1 in front of it. Ported from the
## assembly, including the comparisons of x with the goalie's y (0x5f496, 0x5f611) and the
## asymmetric cases 2/8 and 6/12 of the outcode switch.
static func choose_direction(sim: Sim, e: Entity, tx: int, ty: int) -> Vector2i:
	var goalie_like := e.line_slot == 0 or e.state() == Entity.State.ALL_GOTO_FACEOFF
	var m := -6 if goalie_like else 10
	if sim.play_stopped and e.slot == Entity.Slot.REFEREE:
		if absi(ty) < 0xe8 and (e.yi ^ ty) >= 0:
			return Vector2i(tx, ty)
	var x := e.xi
	var ey := e.yi
	var mtx := tx
	var mty := ty
	var hw := 0x2c + (-8 if goalie_like else 0)
	var near := 6 if goalie_like else 0x23
	var r := net_zone_flags(x, ey, mtx, mty, 0xe8 - near, 0xfc, hw)
	var by: int        # behind the net (edx)
	var fy: int        # in front of the net (eax)
	var gl: int        # goal line
	var goalie_team: Team
	var fe: int
	var ft: int
	var attack_up := (e.flags & Entity.F_ATTACK_UP) != 0
	if r[0]:
		by = 0xfd
		fy = 0xe8 - (7 if goalie_like else 0x24)
		ey = -ey
		mty = -mty
		gl = 0xe8
		goalie_team = sim.opponents_of(e) if attack_up else sim.team_of(e)
		fe = r[1]
		ft = r[2]
		if fe & 5:
			fe ^= 5
		if ft & 5:
			ft ^= 5
	else:
		r = net_zone_flags(x, ey, mtx, mty, -0xfc, near - 0xe8, hw)
		if not r[0]:
			return Vector2i(tx, ty)
		by = -0xfd
		fy = (7 if goalie_like else 0x24) - 0xe8
		gl = -0xe8
		goalie_team = sim.team_of(e) if attack_up else sim.opponents_of(e)
		fe = r[1]
		ft = r[2]
	var gs := goalie_team.goalie_slot
	var g: Entity = sim.entities[gs] if gs >= 0 else null
	var right := m + 0x2c          # A
	var left := -0x2c - m          # B
	var left1 := left + 1
	# results (the original writes the words of the target in place)
	var ox := tx
	var oy := ty
	if ft == 0:
		if ey < -0xe8:
			# behind the goal line, the target inside the box (0x5f4a9)
			if mty < -0xe8:
				return Vector2i(ox, oy)
			if x < left1:
				ox = left
			elif x >= right:
				ox = right
			else:
				oy = by
				if tx >= 0:
					if right > tx:
						ox = right
				elif left1 <= tx:
					ox = left
			if absi(x) > 0x26:
				oy = fy
			return Vector2i(ox, oy)
		if goalie_like:
			if mty < -0xe8:
				return Vector2i(ox, oy)
			oy = fy
			if tx >= 0:
				if right > tx:
					ox = right
			elif left1 <= tx:
				ox = left
			if absi(x) > 0x26:
				oy = by
			return Vector2i(ox, oy)
		if mty >= -0xe8:
			# 0x5f46c
			if g == null:
				return Vector2i(ox, oy)
			if x < tx:
				if x < g.xi:
					oy = fy
			elif x >= g.yi:
				oy = fy
			return Vector2i(ox, oy)
		oy = fy
		return _around_post(x, tx, g, right, left, by, ox, oy, true)
	match fe:
		0:
			if ey < -0xe8:
				# 0x5f643
				if x < left1:
					ox = left
				elif x >= right:
					ox = right
				else:
					oy = by
					if tx >= 0:
						if right > tx:
							ox = right
					elif left1 <= tx:
						ox = left
				return Vector2i(ox, oy)
			if goalie_like:
				if ft & 1:
					return Vector2i(ox, oy)
				oy = fy
				if tx >= 0:
					if right > tx:
						ox = right
				elif left1 <= tx:
					ox = left
				return Vector2i(ox, oy)
			if mty < -0xe8:
				# 0x5f602
				oy = gl
				if g != null:
					ox = left if x < g.yi else right
				elif tx >= 0:
					if right > tx:
						ox = right
				elif left1 <= tx:
					ox = left
				return Vector2i(ox, oy)
			return _around_post(x, tx, g, right, left, by, ox, oy, false)
		1:
			oy = fy
			if ft & 4:
				return Vector2i(ox, oy)
			if tx >= 0:
				if tx < right:
					ox = right
			elif tx >= left1:
				ox = left
		2:
			ox = right
			if (ft & 5) == 0:
				oy = fy
		3:
			if ft == 8:
				oy = fy
			else:
				ox = right
		4:
			oy = by
			if ft & 1:
				if tx >= 0:
					if tx < right:
						ox = right
				elif tx >= left1:
					ox = left
		6:
			if ft != 8:
				ox = right
			else:
				oy = by
		8:
			ox = left
			if ft & 5:
				oy = fy
		9:
			if ft == 2:
				oy = fy
			else:
				ox = left
		12:
			if ft == 2:
				oy = by
	return Vector2i(ox, oy)

## the shared tail of ai_choose_direction (0x5f411..0x5f467, 0x5f5c4..0x5f5fd): pass the post on
## the side away from the goalie, or on the player's side when he is wide of the net. `limit` is
## the 0x5f431 variant, which gives up when the player is already wide of the post.
static func _around_post(x: int, tx: int, g: Entity, right: int, left: int, by: int, ox: int, oy: int, limit: bool) -> Vector2i:
	if g != null and ((tx - g.xi) ^ (x - tx)) < 0:
		ox = left if x < g.xi else right
	elif absi(x) >= right:
		if limit:
			return Vector2i(ox, oy)
	else:
		ox = left if x < 0 else right
	if absi(x) > 0x26:
		oy = by
	return Vector2i(ox, oy)

## ai_skate_towards (0x5e93b): re-evaluates the direction every 12 steps; `mode` adjusts it
## (1 = ai_near_carrier_check, 2 = ai_ref_positioning, 3 = carrier_scan_opponents)
static func skate_towards(sim: Sim, e: Entity, tx: int, ty: int, mode: int = 0) -> void:
	e.dir_timer -= 1
	if e.dir_timer < 0:
		e.dir_timer += 12
		var otx := tx
		var oty := ty
		var t := choose_direction(sim, e, tx, ty)
		var px := e.xi + (e.vx >> 8)
		var py := e.yi + (e.vy >> 8)
		var dx := t.x - px
		var dy := t.y - py
		var dir: int
		if absi(dx) < 0xd and absi(dy) < 0xd and not (absi(otx - px) > 0xc and e.vx == 0) and not (absi(oty - py) > 0xc and e.vy == 0):
			dir = 9
		else:
			dir = Tables.direction8(dx, dy)
		if mode == 1:
			dir = near_carrier_check(sim, e, dir)
		elif mode == 2:
			dir = ref_positioning(sim, e, dir)
		elif mode == 3:
			dir = carrier_scan_opponents(sim, e, dir)
		e.want_dir = dir
		if dir >= 8 and e.vx == 0 and e.vy == 0:
			# standing still: turn to face the puck
			var fdir := Tables.direction8(sim.puck.xi - e.xi, sim.puck.yi - e.yi)
			var diff := (e.facing - fdir) & 7
			if diff != 0:
				e.facing = (e.facing + ((diff & 4) >> 1) - 1) & 7
	sim.apply_skating(e, e.want_dir)

## ai_near_carrier_check (0x5e7fe): a defender close to the carrier moves into his path
static func near_carrier_check(sim: Sim, e: Entity, dir: int) -> int:
	if sim.puck_carrier < 0 or sim.puck_carrier >= 12:
		return dir
	var c := sim.entities[sim.puck_carrier]
	var dx := e.xi - c.xi
	var fx := ((e.vx >> 8) - (c.vx >> 8)) + dx
	if absi(fx) >= 0x29:
		return dir
	var dy := e.yi - c.yi
	var fy := ((e.vy >> 8) - (c.vy >> 8)) + dy
	if absi(fy) >= 0x29:
		return dir
	var out := Tables.direction8(dx, dy)
	if sim.opt_offsides:
		var ry := (e.yi if (e.flags & Entity.F_ATTACK_UP) else -e.yi) - 0x4e
		if ry < 0xb and ry > -0x33:
			# at the blue line: slide along it instead of going offside
			out = 2 if c.xi < e.xi else 6
	return out

## ai_ref_positioning (0x5e4c4): the referee keeps out of everybody's way
static func ref_positioning(sim: Sim, e: Entity, dir: int) -> int:
	if e.flags2 & Entity.F2_NO_COLLIDE:
		return dir
	var ay := absi(e.yi)
	if ay > 0xf2 and absi(e.xi) < 0x32:
		# behind a net: skate out along the boards
		if e.yi <= 0:
			if e.vy < 0:
				return 5 if e.xi < 0 else 3
		elif e.vy > 0:
			return 7 if e.xi < 0 else 1
		return 6 if e.xi < 0 else 2
	var best := 100
	var out := dir
	for i in 15:
		if i == 12 or i == 13:
			continue
		var o := sim.entities[i]
		if i == 14 and best <= 0x50:
			continue
		if o.line_slot < 0:
			continue
		var dx := e.xi - o.xi
		var fx := dx + ((e.vx >> 8) - (o.vx >> 8))
		if absi(fx) >= 0x29:
			continue
		var dy := e.yi - o.yi
		var fy := dy + ((e.vy >> 8) - (o.vy >> 8))
		if absi(fy) >= 0x29 or absi(fx) + absi(fy) >= best:
			continue
		best = absi(fx) + absi(fy)
		out = Tables.direction8(dx, dy)
		if e.xi < -0x82 and out > 4:
			out = 0 if o.vy == 0 else 4
		elif e.xi > 0x82 and out > 0 and out < 4:
			out = 0 if o.vy == 0 else 4
	return out

## ref_skate_to_point (0x5e3a0): the referee glides to a point, around the nets
static func ref_skate_to_point(sim: Sim, e: Entity, tx: int, ty: int) -> void:
	var dx := tx - e.xi
	var dy := ty - e.yi
	if absi(dx) < 8 and absi(dy) < 8:
		e.vx = 0
		e.vy = 0
		e.set_pos(tx, ty)
		return
	if absi(e.xi) < 0x1f and absi(e.yi) > 0xf1 and absi(ty) < 0xf2:
		# behind the net: out along the boards first
		ty = -0xfc if e.yi < 0 else 0xfc
		tx = -0x28 if tx < 0 else 0x28
		if (e.vy > 0) != (e.yi > 0):
			e.vy = 0
	skate_towards(sim, e, tx, ty)
	if absi(dx) < 0x19 and absi(dy) < 0x19:
		if absi(e.vx) > 0x9c4:
			e.vx -= e.vx >> 2
		if absi(e.vy) > 0x9c4:
			e.vy -= e.vy >> 2
	# the last few units are covered at a minimum glide speed so the approach never stalls
	var glide := Anim.REF_GLIDE if e.slot == Entity.Slot.REFEREE else (0x99 if e.line_slot == 0 else Anim.GLIDE)
	var skate := Anim.REF_SKATE if e.slot == Entity.Slot.REFEREE else (Anim.GOALIE_IDLE if e.line_slot == 0 else Anim.SKATE)
	if absi(dx) > 7 and absi(e.vx) < 0x640:
		if (e.vx == 0 and e.anim == glide) or e.vy == 0:
			Anim.set_animation(e, skate if e.vy == 0 else glide)
		e.vx = 0x640 if dx > 0 else -0x640
	if absi(dy) > 7 and absi(e.vy) < 0x640:
		if (e.vx == 0 and e.anim == glide) or e.vy == 0:
			Anim.set_animation(e, skate if e.vx == 0 else glide)
		e.vy = 0x640 if dy > 0 else -0x640

## ai_chase_puck (0x5eb17): skate to where the puck will be, lunge when it is just out of reach
static func chase_puck(sim: Sim, e: Entity) -> void:
	var puck := sim.puck
	var tx := puck.xi + (puck.vx >> 9)
	var ty := puck.yi + (puck.vy >> 9)
	e.dir_timer -= 1
	if e.dir_timer < 0:
		e.dir_timer += 5 if e.line_slot == 0 else 10
		var t := choose_direction(sim, e, tx, ty)
		var dir: int
		if sim.puck_carrier >= 0 or absi(puck.vx) > 300 or absi(puck.vy) > 300 or Sim.approx_distance(t.x - e.xi, t.y - e.yi) > 0x18:
			var o := Tables.frame_offset(e.frame, (e.flags4 & Entity.F4_MIRROR) != 0)
			dir = Tables.direction8(t.x - ((e.vx >> 8) + o.x) - e.xi, t.y - ((e.vy >> 8) + o.y) - e.yi)
		else:
			dir = e.puck_dir
		e.want_dir = dir
		if e.line_slot != 0:
			var from := Tables.direction8(puck.vx, puck.vy) ^ 4
			var fast := absi(puck.vx) >= 4000 or absi(puck.vy) >= 4000
			if not (from == e.facing and fast and sim.random(4) != 0):
				var d2 := Tables.direction8(puck.xi - e.xi, puck.yi - e.yi)
				if d2 == e.facing:
					var dx := puck.xi - e.xi
					var dy := puck.yi - e.yi
					var dist := dx * dx + dy * dy
					if dist > 900 and dist < 0x5a5:
						e.flags |= Entity.F_BUSY
						Anim.set_animation(e, 0x589)   # lunge for the puck
						return
	sim.apply_skating(e, e.want_dir)

## ai_try_check (0x53537): hit or hook a nearby opponent, or try to block a shot
static func try_check(sim: Sim, e: Entity) -> void:
	var k := 0x14 - e.aggression
	if sim.opt_penalties:
		k += k >> 1
	if sim.random(k * 2) >= 9:
		return
	var opp := sim.opponents_of(e)
	for i in 6:
		var o := sim.entities[opp.first_slot + i]
		if o.line_slot == 0 or (o.flags & Entity.F_BUSY) or (o.flags2 & Entity.F2_KNOCKED):
			continue
		var dx := o.xi - e.xi
		if absi(dx) >= 0x1f:
			continue
		var dy := o.yi - e.yi
		if absi(dy) >= 0x1f or Tables.direction8(dx, dy) != e.facing:
			continue
		if sim.random(4) != 0:
			PuckLogic.body_check(sim, e)
		else:
			PuckLogic.start_hook(sim, e, o)
		return
	# try_shot_block: block a shot
	var k2 := 8
	if sim.power_play and sim.power_play_team != e.team:
		k2 = 4
	k2 += 0xf - e.awareness
	if sim.random(maxi(1, k2 / 2)) < 2:
		var r := PuckLogic.try_block_shot(sim, e)
		if r != 0:
			PuckLogic.start_poke_check(sim, e, r)

# --------------------------------------------------------------------------------------------
# positional play (defo defd wingd wingo centd cento)
# --------------------------------------------------------------------------------------------

## ai_defense_offense (0x49cdd): a defenceman on the attack stays at the point
static func def_offense(sim: Sim, e: Entity) -> void:
	if not role_preamble(sim, e):
		return
	e.react_timer -= 1
	if e.react_timer < 0:
		e.react_timer = e.awareness
		if sim.team_of(e).flags & Team.FL_OFFSIDE:
			e.set_state(Entity.State.DEF_DEFENSE)
			return
		var py := sim.puck.yi if (e.flags & Entity.F_ATTACK_UP) else -sim.puck.yi
		if py < 0x53 or (sim.puck_carrier >= 0 and not sim.same_team(sim.puck_carrier, e.slot)):
			e.set_state(Entity.State.DEF_DEFENSE)
			return
	var tx := 100 if e.line_slot == 2 else -100
	var ty := 0x58
	if (e.flags & Entity.F_ATTACK_UP) == 0:
		tx = -tx
		ty = -ty
	if (sim.puck.xi ^ tx) < 0:
		tx += sim.puck.xi >> 1
	else:
		tx = sim.puck.xi
	skate_towards(sim, e, tx, ty, 1)

## ai_defense_defense (0x49e3a): stay between the attackers and the own net
static func def_defense(sim: Sim, e: Entity) -> void:
	if not role_preamble(sim, e):
		return
	e.react_timer -= 1
	if e.react_timer < 0:
		e.react_timer = e.awareness
		var puck := sim.puck
		var py := puck.yi
		var pvy := puck.vy >> 6
		if (e.flags & Entity.F_ATTACK_UP) == 0:
			py = -py
			pvy = -pvy
		pvy = maxi(0, pvy) + py
		if pvy > 0x4d and (sim.team_of(e).flags & Team.FL_OFFSIDE) == 0 and sim.puck_carrier >= 0:
			var short_handed := sim.power_play and sim.power_play_team != e.team
			if not short_handed and sim.same_team(sim.puck_carrier, e.slot):
				e.set_state(Entity.State.DEF_OFFENSE)
				return
		var tx := 0x50 if e.line_slot == 2 else -0x50
		var opp := sim.opponents_of(e)
		var deepest: int
		if (e.flags & Entity.F_ATTACK_UP) == 0:
			deepest = -1000
			for i in 6:
				var o := sim.entities[opp.first_slot + i]
				if o.line_slot >= 0 and (o.flags2 & Entity.F2_UNSELECTABLE) == 0:
					deepest = maxi(deepest, Sim._s16((maxi(0, o.vy) >> 4) + o.yi))
			deepest = Sim._s16(deepest + 0x32)
			if deepest >= 0xaa:
				deepest = 0xc3       # deep in the own zone: the goal line
			tx = -tx
		else:
			deepest = 1000
			for i in 6:
				var o := sim.entities[opp.first_slot + i]
				if o.line_slot >= 0 and (o.flags2 & Entity.F2_UNSELECTABLE) == 0:
					deepest = mini(deepest, Sim._s16((mini(0, o.vy) >> 4) + o.yi))
			deepest = Sim._s16(deepest - 0x32)
			if deepest <= -0xaa:
				deepest = -0xc3
		e.target_x = tx
		e.target_y = deepest
		if (puck.xi ^ tx) < 0:
			e.target_x = 0
			if absi(deepest) == 0xc3:
				e.target_y = -0xb6 if deepest < 0 else 0xb6
	skate_towards(sim, e, e.target_x, e.target_y, 1)
	try_check(sim, e)

## ai_wing_defense (0x4a1a6): the winger covers his side (x 0x78) between the blue line and the
## goal line of his own zone, up with the puck when it is out of the zone, at the puck's x when the
## puck is on his side
static func wing_defense(sim: Sim, e: Entity) -> void:
	if not role_preamble(sim, e):
		return
	e.react_timer -= 1
	if e.react_timer < 0:
		e.react_timer = e.reaction
		if sim.puck_carrier >= 0 and sim.same_team(sim.puck_carrier, e.slot):
			e.set_state(Entity.State.WING_OFFENSE)
			return
	var puck := sim.puck
	var tx := -0x78 if e.line_slot == 5 else 0x78
	var ty := 0x8e
	var offside := (sim.team_of(e).flags & Team.FL_OFFSIDE) != 0
	if e.flags & Entity.F_ATTACK_UP:
		tx = -tx
		ty = -0x8e
		if offside:
			ty = -0x44
		elif puck.yi >= -0x44:
			ty = puck.yi
		elif puck.yi <= -0xe8:
			ty = -0xe8
	else:
		if offside:
			ty = 0x44
		elif puck.yi <= 0x44:
			ty = puck.yi
		elif puck.yi >= 0xe8:
			ty = 0xe8
	if (tx ^ puck.xi) >= 0:
		tx = puck.xi
	skate_towards(sim, e, tx, ty)

## ai_wing_offense (0x4a343): find space in the offensive zone: by where the puck is (and is going)
## a zone (0, 4, 8, 12: behind the red line, the neutral zone, the attacking zone, past the goal
## line) whose box of wing_zones gives a random target (one time in 128 a new one in the same zone);
## the left wing mirrors it. A change of state forgets the zone (+0x2f = 0xff).
static func wing_offense(sim: Sim, e: Entity) -> void:
	if (e.flags & Entity.F_STATE_ENTERED) and (e.flags & (Entity.F_BUSY | Entity.F_USER)) == 0 and not sim.play_stopped:
		e.timer_b = Entity.to_s16((e.timer_b & 0xff) | 0xff00)
	if not role_preamble(sim, e):
		return
	e.react_timer -= 1
	if e.react_timer < 0:
		e.react_timer = e.reaction
		if sim.puck_carrier >= 0 and not sim.same_team(sim.puck_carrier, e.slot):
			e.set_state(Entity.State.WING_DEFENSE)
			return
		var puck := sim.puck
		var py := puck.yi
		var lead := Sim._s16(puck.yi + (Sim._s16(puck.vy) >> 6))
		if (e.flags & Entity.F_ATTACK_UP) == 0:
			py = Sim._s16(-py)
			lead = Sim._s16(-lead)
		var zone := 0
		if lead >= -0x4e:
			zone = 4
			if py >= 0x4e and (sim.team_of(e).flags & Team.FL_OFFSIDE) == 0:
				zone = 8
				if lead >= 0xe8:
					zone = 0xc
		if zone != e.timer_b or sim.random(0x80) == 0:
			e.timer_b = zone
			var z: Array = Tables.wing_zones[zone >> 2]
			e.target_x = Sim._s16(z[0] + sim.random(Sim._s16(z[1] * 2)) - z[1] + e.reaction)
			e.target_y = Sim._s16(z[2] + sim.random(Sim._s16(z[3] * 2)) - z[3])
	var tx := e.target_x if e.line_slot == 5 else -e.target_x
	var ty := e.target_y
	if (e.flags & Entity.F_ATTACK_UP) == 0:
		tx = -tx
		ty = -ty
	skate_towards(sim, e, tx, ty, 1)

## ai_center_defense (0x4a53a): the centre stays between the puck (half its x) and his own blue
## line, at -0x71 when the puck is in his zone
static func center_defense(sim: Sim, e: Entity) -> void:
	if not role_preamble(sim, e):
		return
	e.react_timer -= 1
	if e.react_timer < 0:
		e.react_timer = e.reaction
		if sim.puck_carrier >= 0 and sim.same_team(sim.puck_carrier, e.slot):
			e.set_state(Entity.State.CENTER_OFFENSE)
			return
	var puck := sim.puck
	var tx := puck.xi >> 1
	var py := puck.yi if (e.flags & Entity.F_ATTACK_UP) else Sim._s16(-puck.yi)
	var ty := -0x71
	if py >= -0x4e:
		ty = Sim._s16((puck.yi - 0x71) >> 1)
	if (e.flags & Entity.F_ATTACK_UP) == 0:
		ty = Sim._s16(-ty)
	skate_towards(sim, e, tx, ty)

## ai_center_offense (0x4a65c): like the wing (center_zones, the zone by the puck's position alone,
## not mirrored in x)
static func center_offense(sim: Sim, e: Entity) -> void:
	if (e.flags & Entity.F_STATE_ENTERED) and (e.flags & (Entity.F_BUSY | Entity.F_USER)) == 0 and not sim.play_stopped:
		e.timer_b = Entity.to_s16((e.timer_b & 0xff) | 0xff00)
	if not role_preamble(sim, e):
		return
	e.react_timer -= 1
	if e.react_timer < 0:
		e.react_timer = e.reaction
		if sim.puck_carrier >= 0 and not sim.same_team(sim.puck_carrier, e.slot):
			e.set_state(Entity.State.CENTER_DEFENSE)
			return
		var py := sim.puck.yi if (e.flags & Entity.F_ATTACK_UP) else Sim._s16(-sim.puck.yi)
		var zone := 0
		if py >= -0x4e:
			zone = 4
			if py >= 0x4e and (sim.team_of(e).flags & Team.FL_OFFSIDE) == 0:
				zone = 8
				if py >= 0xe8:
					zone = 0xc
		if zone != e.timer_b or sim.random(0x80) == 0:
			e.timer_b = zone
			var z: Array = Tables.center_zones[zone >> 2]
			e.target_x = Sim._s16(sim.random(Sim._s16(z[1] * 2)) - z[1] + z[0])
			e.target_y = Sim._s16(sim.random(Sim._s16(z[3] * 2)) - z[3] + z[2])
	var ty := e.target_y if (e.flags & Entity.F_ATTACK_UP) else Sim._s16(-e.target_y)
	skate_towards(sim, e, e.target_x, ty, 1)

# --------------------------------------------------------------------------------------------
# the puck carrier and the chasers (puckc nearest shoot passrec abreak)
# --------------------------------------------------------------------------------------------

## ai_puck_carrier (0x4c6f3)
static func puck_carrier(sim: Sim, e: Entity) -> void:
	if sim.puck_carrier != e.slot:
		default_skate(sim, e)
		return
	if e.flags & Entity.F_BUSY:
		return
	if sim.play_stopped:
		skate_idle(sim, e)
		return
	if e.flags & Entity.F_USER:
		default_skate(sim, e)
		return
	if e.flags & Entity.F_STATE_ENTERED:
		e.flags &= ~Entity.F_STATE_ENTERED
		e.timer_f = 0
		e.timer_a = 0
		e.want_dir = 8
		e.dir_timer = 0
		e.target_x = sim.random(4)       # which lane to carry the puck along
		sim.goalie_pass_mode = 0
	e.react_timer -= 1
	if e.react_timer < 0:
		e.react_timer = e.reaction
		Lines.offside_warning_check(sim, e)
		if sim.breakaway and absi(e.yi) < 0x70:
			e.set_state(Entity.State.BREAKAWAY)
			return
		if consider_shot(sim, e):
			return
		if offense_decision(sim, e):
			return
		if choose_pass_target(sim, e):
			return
	var idx := e.line_slot - 1 if sim.offside_warning else e.target_x + 6
	var tx: int
	var ty: int
	if idx >= 0:
		tx = Tables.carrier_targets[idx][0]
		ty = Tables.carrier_targets[idx][1]
	else:
		# (an off ice carrier: the original reads the words before the table, the end of
		# goalie_save_anims)
		var g := Tables.goalie_save_anims
		tx = g[g.size() + 2 * idx]
		ty = g[g.size() + 2 * idx + 1]
	if (e.flags & Entity.F_ATTACK_UP) == 0:
		tx = -tx
		ty = -ty
	if absi(e.xi - tx) <= 0xc and absi(e.yi - ty) <= 0xc:
		e.target_x = sim.random(4)
	skate_towards(sim, e, tx, ty, 3)

## carrier_scan_opponents (0x4ca1e), the carrier's ai_skate_towards adjustment: an opponent within
## 0x19 of the puck (both a step ahead) turns him away (one step aside, at random, when the
## opponent is right behind him); goalie_pass_mode counts them. In his own zone near the net he
## keeps away from his own goalie (within 0x14 in x) and from the net.
static func carrier_scan_opponents(sim: Sim, e: Entity, dir: int) -> int:
	dir = Entity.to_s8(dir)
	var puck := sim.puck
	var px := Sim._s16(puck.xi + Entity.to_s8(e.vx >> 8))
	var py := Sim._s16(puck.yi + Entity.to_s8(e.vy >> 8))
	sim.scratch_ac = (sim.scratch_ac & 0xffff0000) | (px & 0xffff)
	sim.goalie_pass_mode = 0
	var first := 6 if e.slot < 6 else 0
	for i in 6:
		var o := sim.entities[first + i]
		if absi(Sim._s16(o.xi + Entity.to_s8(o.vx >> 8) - px)) > 0x19:
			continue
		if absi(Sim._s16(o.yi + Entity.to_s8(o.vy >> 8) - py)) > 0x19:
			continue
		sim.goalie_pass_mode += 1
		dir = Tables.direction8(Sim._s16(e.xi - o.xi), Sim._s16(e.yi - o.yi))
		if dir == (((e.heading >> 16) & 0xffff) ^ 4):
			dir = (sim.random(2) + dir) & 7
	var up := (e.flags & Entity.F_ATTACK_UP) != 0
	if up != (e.yi < 0):
		return dir
	if absi(py) < 0xaa or absi(py) > 0xe8 or absi(px) > 0x50:
		return dir
	var gs := sim.team_of(e).goalie_slot
	if gs >= 0:
		var g := sim.entities[gs]
		var gx := Sim._s16(g.xi + Entity.to_s8(g.vx >> 8) - px)
		if absi(gx) <= 0x14:
			# (the original tests the x distance a second time where the y was meant)
			var gy := Sim._s16(g.yi + Entity.to_s8(g.vy >> 8) - py)
			dir = Tables.direction8(Sim._s16(-gx), Sim._s16(-gy))
	if absi(px) > 0x1e:
		return dir
	var ny := -0xdc if up else 0xdc
	if absi(Sim._s16(ny - py)) > 0x14:
		return dir
	return Tables.direction8(e.xi, Sim._s16(e.yi - ny))

## ai_consider_shot (0x54af9): a tired line in the neutral zone changes on the fly: the carrier
## dumps the puck in and the new line comes on
static func consider_shot(sim: Sim, e: Entity) -> bool:
	if not sim.opt_line_changes or sim.penalty_shot:
		return false
	var py := sim.puck.yi if (e.flags & Entity.F_ATTACK_UP) else -sim.puck.yi
	if py < 0 or py >= 0x4f or sim.random(4) != 0 or (e.flags2 & Entity.F2_LINE_CHANGE):
		return false
	var team := sim.team_of(e)
	var other := sim.opponents_of(e)
	var diff := team.skaters_on_ice - other.skaters_on_ice
	if (team.flags2 & 0x40) == 0:
		var avg := Lines.team_avg_energy(sim, team)
		if sim.clock_seconds <= 0xe or (sim.clock_seconds <= 0x1d and avg > 0x800):
			return false
		var threshold := team.energy_threshold if diff == 0 else 0xf33
		if avg > threshold:
			return false
	elif sim.clock_seconds <= 0xe:
		return false
	if diff != 0 and Rules.penalty_time_left(sim) <= 0xe:
		return false
	Lines.choose_line(sim, other, team)
	Lines.apply_line_change(sim, team)
	desperation_shot(sim, e)
	return true

## ai_offense_decision (0x55804): shoot short handed with an opponent on the puck (one in four),
## or behind in the last seconds; otherwise the odds 0x20 - offense, times 0x10 far from the net
## (beyond 100), doubled for each opponent skater between the puck and the net, 1 at an empty net
## or with the goalie down; a number below 9 shoots from inside the attacking half, not while a
## team mate is offside (on a penalty shot only from 0x74 up)
static func offense_decision(sim: Sim, e: Entity) -> bool:
	var puck := sim.puck
	if not sim.penalty_shot:
		var away := (e.flags & Entity.F_PLAYER2) != 0
		if sim.power_play and away != (sim.power_play_team == 1) and sim.goalie_pass_mode != 0:
			if sim.random(4) == 0:
				desperation_shot(sim, e)
				return true
		if sim.clock_seconds < 4 and sim.team_record(e).goals < sim.opponents_of(e).goals:
			desperation_shot(sim, e)
			return true
	var odds := Sim._s16(0x20 - e.offense)
	var gy := Sim._s16((0xe8 if (e.flags & Entity.F_ATTACK_UP) else -0xe8) - puck.yi)
	var gx := Sim._s16(-puck.xi)
	if (gx * gx + gy * gy) & 0xffffffff > 0x2710:
		odds = Sim._s16(odds << 4)
	elif sim.opponents_of(e).goalie_pulled():
		odds = 1
	else:
		var to_net := Tables.direction8(gx, gy)
		var first := 6 if e.slot < 6 else 0
		for i in 6:
			var o := sim.entities[first + i]
			if o.line_slot == 0:
				if o.flags2 & Entity.F2_TURNING:
					odds = 1
					break
				continue
			if Tables.direction8(Sim._s16(o.xi - puck.xi), Sim._s16(o.yi - puck.yi)) == to_net:
				odds = Sim._s16(odds * 2)
	if Sim._s16(sim.random(odds)) > 8:
		return false
	var py := Sim._s16(puck.yi if (e.flags & Entity.F_ATTACK_UP) else -puck.yi)
	if py < 0 or 0xe8 - py < 0:
		return false
	if sim.penalty_shot and py < 0x74:
		return false
	if sim.offside_warning:
		return false
	desperation_shot(sim, e)
	return true

## ai_desperation_shot (0x55a35): wind up for a shot, the power (+0x28) from the distance to the
## goal line, at most 0x14; the SHOOT state releases it
static func desperation_shot(sim: Sim, e: Entity) -> void:
	var py := Sim._s16(sim.puck.yi if (e.flags & Entity.F_ATTACK_UP) else -sim.puck.yi)
	e.want_dir = mini(0x14, ((0xe8 - py) & 0xffff) >> 3)
	e.dir_timer = 0                 # the word +0x28
	e.set_state(Entity.State.SHOOT)

## ai_choose_pass_target (0x55493): pick a team mate at random (always while an opponent is on the
## puck, else on 10 in offense + 0x10) and pass when the lane is open. Behind the own net a pass
## goes out only to a mate wide (0x3c) on the puck's side, or across behind the same goal line; a
## pass across the blue line, or back more than 0xf in the own half, needs pass_lane_ok; no two
## line pass to an offside mate. An opponent nearer the receiver's puck point on the same line
## blocks it (the goalie's passes also keep clear of opponents near it). A skater skates on
## after the pass; after the goalie's pass it returns 0 and the carrier code goes on.
static func choose_pass_target(sim: Sim, e: Entity) -> bool:
	var puck := sim.puck
	e.pass_ok = 0
	if sim.goalie_pass_mode == 0 and sim.random(e.offense + 0x10) > 9:
		return false
	var idx := sim.random(6)
	if e.slot >= 6:
		idx += 6
	if idx == e.slot:
		return false
	var t := sim.entities[idx]
	if t.line_slot <= 0 or (t.flags2 & Entity.F2_UNSELECTABLE) or (t.flags & Entity.F_BUSY):
		return false
	var up := (e.flags & Entity.F_ATTACK_UP) != 0
	if e.line_slot != 0 and up != (puck.yi > 0):
		if absi(puck.xi) <= 0x32 and absi(puck.yi) > 0xac:
			if absi(puck.yi) < 0xeb or absi(t.xi) < 0x3c:
				return false
			if (t.xi ^ puck.xi) < 0 and ((absi(t.yi) - 0xe8) ^ (absi(puck.yi) - 0xe8)) < 0:
				return false
	var ty := Sim._s16(t.yi if up else -t.yi)
	var ey := Sim._s16(e.yi if up else -e.yi)
	var v := ty                  # word e03bc: the receiver's y, or how far ahead of the passer
	var check := false
	if sim.opt_offsides and ((ey - 0x4e) ^ (ty - 0x4e)) < 0:
		check = true
	elif ty <= 0x4e:
		v = Sim._s16(ty - ey)
		check = v < -0xf
	if check:
		e.pass_ok = 1 if PuckLogic.pass_lane_ok(sim, e, t) else 0
		if e.pass_ok == 0:
			return false
		e.pass_target = t.slot
	if sim.opt_two_line_pass and (t.flags2 & Entity.F2_OFFSIDE) and ey < -0x4e and v > 0:
		return false
	sim.pending_dir = Entity.to_s8(t.puck_dir ^ 4)
	var lane_d := t.puck_dist
	sim.scratch_ac = lane_d & 0xffffffff
	var first := 6 if e.slot < 6 else 0
	for i in 6:
		var o := sim.entities[first + i]
		var od := o.puck_dist
		if od > lane_d:
			continue
		var rel := (sim.pending_dir - Entity.to_s8(o.puck_dir ^ 4) + 1) & 7
		if rel == 1:
			return false
		if e.line_slot != 0:
			continue
		if od < 0x1e or (rel <= 2 and od < 0x3c) or ((rel == 3 or rel == 7) and od < 0x28):
			return false
	PuckLogic.do_pass(sim, e)
	if e.line_slot == 0:
		return false
	default_skate(sim, e)
	return true

## ai_nearest_to_puck (0x4cd4b): the team mate closest to the puck goes to get it. On its reaction
## tick the role is handed to the carrier of the team, or to the skater whose frame point is nearest
## to where the puck will be (team +0x3a: that distance); the one who keeps it may hold back (+0x2a
## = 300 steps) instead of chasing, the more likely the further the puck, a forward always may (the
## original compares the line slot where a y was meant); while holding back with the puck carried he
## covers the slot between the puck and his net. Line changes only while the play is stopped.
static func nearest_to_puck(sim: Sim, e: Entity) -> void:
	var team := sim.team_record(e)
	if e.flags & Entity.F_STATE_ENTERED:
		e.flags &= ~Entity.F_STATE_ENTERED
		e.timer_a = 0
		e.want_dir = 8
		e.dir_timer = 0
		e.target_x = 0        # the holding back timer in this state
	if sim.puck_carrier == e.slot:
		if e.line_slot == 0:
			goalie(sim, e)
		elif (e.flags & Entity.F_USER) == 0:
			e.set_state_reset(Entity.State.PUCK_CARRIER)
		return
	e.react_timer -= 1
	if e.react_timer < 0:
		e.react_timer = e.reaction
		team.nearest_d2 = 0
		var best := e
		var best_d := sim.scratch_ac & 0xffffffff      # stale while a team mate carries the puck
		var deepest := -1          # (a local the original leaves unset when a team mate has the puck)
		var deepest_y := e.yi
		var handover := false
		if sim.puck_carrier >= 0 and sim.same_team(sim.puck_carrier, e.slot):
			best = sim.entities[sim.puck_carrier]
			handover = true
		else:
			var puck := sim.puck
			var first := 0 if e.slot < 6 else 6
			best_d = 0xffffffff
			deepest = e.slot
			if e.slot != sim.penalty_shot_slot:
				for i in 6:
					var p := sim.entities[first + i]
					if p.line_slot <= 0 or p.timer_c != 0 or (p.flags2 & Entity.F2_UNSELECTABLE) \
							or p.state() == Entity.State.PASS_RECEIVER:
						continue
					var up := (e.flags & Entity.F_ATTACK_UP) != 0
					if absi(p.yi) < 0xe8 and ((up and deepest_y >= p.yi) or (not up and deepest_y <= p.yi)):
						deepest = p.slot
						deepest_y = p.yi
					var o := Tables.frame_offset(p.frame, (p.flags4 & Entity.F4_MIRROR) != 0)
					var dx := Sim._s16(o.x + p.xi - puck.xi - (Sim._s16(puck.vx) >> 6))
					var dy := Sim._s16(o.y + p.yi - puck.yi - (Sim._s16(puck.vy) >> 6))
					var d := (dx * dx + dy * dy) & 0xffffffff
					if d <= best_d:
						best_d = d
						best = p
			sim.scratch_ac = best_d
			if Sim._s32(best_d) >= 0:
				team.nearest_d2 = best_d
				handover = true
		if handover and best != e and not sim.play_stopped and best.line_slot > 0 \
				and (best.flags2 & Entity.F2_UNSELECTABLE) == 0:
			best.flags &= ~Entity.F_HAS_TARGET
			best.set_state_reset(Entity.State.NEAREST)
			default_skate(sim, e)
			return
		if e.flags & Entity.F_BUSY:
			return
		# hold back instead of chasing?
		var level := 2
		var d16 := Sim._s16(best_d)
		var slow := absi(sim.puck.vx) < 0x1f4 and absi(sim.puck.vy) < 0x1f4
		var close := d16 <= 0x190 or (d16 <= 0xe10 and slow)
		var roll := true
		if not close and e.line_slot > 2:
			# (the original compares the line slot with the blue line here)
			if (e.flags & Entity.F_ATTACK_UP) and e.line_slot > 0x4e:
				close = true
			elif (e.flags & Entity.F_ATTACK_UP) == 0 and e.line_slot < -0x4e:
				close = true
		if close:
			level -= 2
			if e.line_slot <= 2:
				if e.slot == deepest:
					roll = false
				else:
					var k := _div_trunc(0x32 - e.check_skill - e.aggression - e.awareness, 2)
					roll = sim.random(Sim._s16(k)) == 0
		if roll:
			if slow:
				level -= 1
			if sim.power_play:
				level -= 2
				if (e.flags & Entity.F_PLAYER2) != 0 != (sim.power_play_team == 1):
					level += 4
			var base := 0x14 - e.aggression
			var n := (base >> -level) if level < 0 else (base << level)
			if (sim.random(Sim._s16(n)) & 0xffff) <= 1:
				e.target_x = 0x12c
	if e.flags & Entity.F_BUSY:
		return
	if sim.play_stopped:
		if not Lines.handle_line_change(sim, e):
			skate_idle(sim, e)
		return
	if e.flags & Entity.F_USER:
		return
	if sim.puck_carrier < 0:
		chase_puck(sim, e)
		try_check(sim, e)
		return
	e.target_x = Sim._s16(e.target_x - 1)
	if e.target_x >= 0:
		chase_puck(sim, e)
		try_check(sim, e)
		return
	e.target_x = 0
	var puck := sim.puck
	var tx := puck.xi + (Entity.to_s8(puck.vx >> 8) >> 1)
	var ty := puck.yi + (Entity.to_s8(puck.vy >> 8) >> 1)
	tx = Sim._s16(_div_trunc(Sim._s16(tx) * 3, 4))
	var own := -0xd4 if (e.flags & Entity.F_ATTACK_UP) else 0xd4
	ty = Sim._s16(((own - ty) >> 1) + ty)
	if absi(ty) > absi(puck.yi) and absi(puck.xi) < 0x41 and absi(ty - puck.yi) > 0x14:
		if absi(tx) < 0x14:
			if absi(ty) > 0xc8:
				ty = -0xc8 if ty < 0 else 0xc8
		elif absi(tx) < 0x28:
			if absi(ty) > 0xd2:
				ty = -0xd2 if ty < 0 else 0xd2
	skate_towards(sim, e, tx, ty)
	try_check(sim, e)

static func _div_trunc(v: int, d: int) -> int:
	return -((-v) / d) if v < 0 else v / d

## ai_shoot (0x4d3f8): wind up and release; a CPU player may fake when a defender is close
static func shoot(sim: Sim, e: Entity) -> void:
	if e.flags & Entity.F_BUSY:
		return
	if e.flags & Entity.F_STATE_ENTERED:
		e.flags &= ~Entity.F_STATE_ENTERED
		PuckLogic.start_shot(sim, e)
		return
	if not sim.action_shot:
		default_skate(sim, e)
		return
	var changed := 0
	var w := Sim._s16((e.want_dir | (e.dir_timer << 8)) - 1)      # the word +0x28: the wind up
	e.want_dir = w & 0xff
	e.dir_timer = Entity.to_s8(w >> 8)
	if w < 0:
		changed = 0x20        # B released: the shot goes
	sim.scratch_ac = (sim.scratch_ac & 0xffff0000) | changed
	e.timer_f = maxi(0, Sim._s16(e.timer_f - 1))
	var ay := absi(e.yi)
	if ay < 0x9e and ay > 0x53 and sim.opponents_of(e).nearest_dist < 0x24 and e.timer_f == 0 and sim.random(0x14) == 0:
		e.timer_f = 300
		sim.scratch_b |= 0x10          # fake shot
	else:
		sim.scratch_b &= 0xffaf
	# the aim: whatever the movement code left in the scratch word (the shooter's vy)
	PuckLogic.shot_control(sim, e, sim.scratch_a, sim.scratch_b, changed)

## ai_pass_receiver (0x50f3f): a CPU receiver waits for the pass (chasing a slow loose puck) and
## may set up a one timer when the pass leaves (not on a team of a user); the user's receiver and a
## one timer run one_timer_step. Done when somebody has the puck or after 6 reaction ticks.
static func pass_receiver(sim: Sim, e: Entity) -> void:
	if e.flags & Entity.F_BUSY:
		return
	if sim.play_stopped:
		sim.one_timer = false
		default_skate(sim, e)
		skate_idle(sim, e)
		return
	e.react_timer -= 1
	if e.flags & Entity.F_USER:
		one_timer_step(sim, e)
		return
	if e.flags & Entity.F_STATE_ENTERED:
		e.flags = (e.flags & ~(Entity.F_STATE_ENTERED | Entity.F_HAS_TARGET)) | Entity.F_HAS_TARGET
		e.want_dir = 8
		e.dir_timer = 0
		var team_no := 2 if (e.flags & Entity.F_PLAYER2) else 1
		sim.scratch_a = team_no
		if sim.puck_carrier < 0 and sim.user1_team != team_no and team_no != sim.user2_team and one_timer_chance(sim, e):
			sim.one_timer = true
	if sim.one_timer:
		sim.scratch_b &= 0xffaf          # no fake
		one_timer_step(sim, e)
		return
	if sim.puck_carrier < 0:
		if absi(sim.puck.vx) < 0x168 and absi(sim.puck.vy) < 0x168:
			chase_puck(sim, e)
		if e.react_timer >= -5:
			return
	e.flags &= ~Entity.F_HAS_TARGET
	default_skate(sim, e)
	sim.one_timer = false
	if sim.puck_carrier == e.slot:
		PuckLogic.pass_completed(sim, e)
	elif sim.puck_carrier >= 0:
		sim.pass_target = -1

## one_timer_chance (0x50e5c): in the attacking zone between the blue line and the goal line, the
## net not empty: sure when the goalie stands more than 0xc to the side (and the receiver not at
## his x), else one in 2 (more than 6) or 3. The goalie is the first opponent with line slot 0 (the
## entity after the six when there is none).
static func one_timer_chance(sim: Sim, e: Entity) -> bool:
	var ay := absi(e.yi)
	if ay <= 0x4e or ay >= 0xde or (e.yi < 0) == ((e.flags & Entity.F_ATTACK_UP) != 0):
		return false
	if sim.opponents_of(e).goalie_pulled():
		return false
	var first := 6 if e.slot < 6 else 0
	var i := 0
	while i < 6 and sim.entities[first + i].line_slot != 0:
		i += 1
	var goalie := sim.entities[first + i]
	var odds := 3
	if e.xi != goalie.xi:
		var gx := absi(goalie.xi)
		if gx > 0xc:
			return true
		if gx > 6:
			odds = 2
	return sim.random(odds) == 0

## one_timer_step (0x50b55): until the puck arrives (0x19 reaction ticks at most) the receiver of a
## one timer winds up as it comes near (the stick back from 0x16 ticks before, aimed at the net
## from where the puck will be) and fires when it reaches the blade (onetimer_offsets): the shot
## power from the shooting rating, the crowd up. A user's B (or C) before the stick is back fakes.
static func one_timer_step(sim: Sim, e: Entity) -> void:
	var puck := sim.puck
	if sim.puck_carrier >= 0 or e.react_timer < -0x19:
		if sim.puck_carrier == e.slot:
			PuckLogic.pass_completed(sim, e)
		sim.pass_target = -1
		e.flags &= ~Entity.F_HAS_TARGET
		default_skate(sim, e)
		sim.one_timer = false
		return
	if not sim.one_timer:
		return
	if e.anim == 0xdd3 or e.anim == 0xe2b:
		if e.anim_pos <= 2 and (sim.scratch_b & 0x50):
			sim.action_shot = false
			e.flags |= Entity.F_BUSY
			e.anim = 0x1355 if e.anim == 0xdd3 else 0x138d
			sim.one_timer = false
		e.timer_c = 5
		var f := e.facing
		if e.flags4 & Entity.F4_MIRROR:
			f = (8 - f) & 7
		var o: Array = Tables.onetimer_offsets[f]
		var ox: int = o[0]
		var oy: int = o[1]
		if e.flags4 & Entity.F4_MIRROR:
			ox = -ox
		sim.scratch_a = ox
		sim.scratch_b = oy
		var dx := Sim._s16(e.xi + ox - puck.xi)
		var dy := Sim._s16(e.yi + oy - puck.yi)
		var d2 := dx * dx + dy * dy
		if (e.anim_pos == 0 and (e.react_timer < -4 or d2 < 0x190)) or (e.anim_pos == 2 and d2 < 0x100):
			e.anim_hold = 0
			Anim.advance(e, sim)
		if d2 <= 0x64 or (d2 <= 0x90 and e.react_timer < -0xa):
			if sim.pending_dir > 8:
				sim.pending_dir = 8
			sim.shot_power = e.shot_skill / 2 + 0x1e
			e.anim_pos = 4
			e.anim_hold = 4
			e.frame_wait = 0
			Anim.advance(e, sim)
			sim.team_record(e).one_timers += 1
			sim.crowd_noise = Sim._s16(sim.crowd_noise + 100)
			PuckLogic.update_carrier(sim, e)
			PuckLogic.do_shot(sim, e)
			PuckLogic.pass_completed(sim, e)
			e.flags &= ~Entity.F_HAS_TARGET
			default_skate(sim, e)
			sim.one_timer = false
		return
	if e.react_timer > 0x16 or e.react_timer < -0xa:
		return
	if (e.flags & Entity.F_USER) == 0:
		if (e.flags & Entity.F_ATTACK_UP) and e.yi < 0x46:
			return
		if (e.flags & Entity.F_ATTACK_UP) == 0 and e.yi > -0x46:
			return
	sim.team_record(e).one_timer_tries += 1
	var lead := Sim._s16((e.react_timer + 10) << 4)
	var tx := Sim._s16(-(puck.xi + ((puck.vx * lead) >> 16)))
	var goal_y := 0xe8 if (e.flags & Entity.F_ATTACK_UP) else -0xe8
	var ty := Sim._s16(goal_y - (Sim._s16((lead * puck.vy) >> 16) + puck.yi))
	var dir := Tables.direction8(tx, ty)
	Anim.set_animation(e, 0xe2b if PuckLogic.shot_is_backhand(e, dir) else 0xdd3)

## ai_breakaway (0x4fae8): alone against the goalie the CPU carrier skates in along a lane through
## the breakaway waypoints; past the last one he shoots, at once on a change of heading by more
## than one step (one in 4) or now and then (one in 0x20), aiming low on the side of the lane
static func breakaway(sim: Sim, e: Entity) -> void:
	if sim.puck_carrier != e.slot or (e.flags & Entity.F_USER):
		default_skate(sim, e)
		return
	if e.flags & Entity.F_BUSY:
		return
	if sim.play_stopped:
		Anim.set_animation(e, Anim.GLIDE)
		e.timer_c = 0x3c
		skate_idle(sim, e)
		return
	var up := (e.flags & Entity.F_ATTACK_UP) != 0
	var py := e.yi if up else -e.yi
	if e.flags & Entity.F_STATE_ENTERED:
		e.flags &= ~Entity.F_STATE_ENTERED
		e.timer_a = 0
		e.dir_timer = 0
		e.want_dir = 8
		sim.breakaway_waypoint = 0
		e.target_x = sim.random(4)
		breakaway_pick_lane(sim, e, py)
	if sim.breakaway_trigger_y < 0:
		var d := Sim._s16(e.heading >> 16) - sim.breakaway_heading
		if d != 0:
			d = (d + 1) & 7
			var shoot_now := false
			if d >= 3:
				shoot_now = sim.random(4) == 0
			else:
				shoot_now = sim.random(0x20) == 0
			if shoot_now:
				sim.pending_dir = sim.random(2) + 2 + (3 if sim.breakaway_lane_side < 0 else 0)
				sim.shot_power = 0x14
				sim.scratch_a = Sim._s16(-e.xi)
				sim.scratch_b = Sim._s16((0xe8 if up else -0xe8) - e.yi)
				var dir := Tables.direction8(sim.scratch_a, sim.scratch_b)
				Anim.set_animation(e, 0xdd3 if PuckLogic.shot_is_backhand(e, dir) else 0xe2b)
				Anim.advance(e, sim)
				e.anim_hold = 2
				PuckLogic.do_shot(sim, e)
				return
	elif py >= sim.breakaway_trigger_y:
		breakaway_next_waypoint(sim)
		sim.breakaway_heading = Sim._s16(e.heading >> 16)
	sim.scratch_a = Sim._s16(sim.breakaway_lane_x)
	sim.scratch_b = Sim._s16(sim.breakaway_target_y if up else -sim.breakaway_target_y)
	e.dir_timer = Entity.to_s8(e.dir_timer - 2)
	skate_towards(sim, e, sim.scratch_a, sim.scratch_b)

## breakaway_pick_lane (0x4f9ef): from far out a lane 0x3a to the side, to 0x3c then (waypoint 0);
## from 0x27 on 0x2c to the side (straight in when already wide) to 0x97, then waypoint 2. The side:
## the backhand side of a left handed shooter three times in four, else either
static func breakaway_pick_lane(sim: Sim, e: Entity, py: int) -> void:
	var d := 0x2c if py >= 0x27 else 0x3a
	if py >= 0x27 and absi(e.xi) > 0x14:
		d = 0
	else:
		if sim.random(4) != 0:
			if e.left_handed != 0:
				d = -d
		elif sim.random(0x10) < 8:
			d = -d
		if (e.flags & Entity.F_ATTACK_UP) == 0:
			d = -d
	sim.breakaway_lane_x = d
	sim.breakaway_lane_side = d
	if py >= 0x27:
		sim.breakaway_waypoint = 2
		sim.breakaway_target_y = 0x97
		sim.breakaway_trigger_y = 0x66
	else:
		sim.breakaway_target_y = 0x3c
		sim.breakaway_trigger_y = 0x1e

## breakaway_next_waypoint (0x4f99b): the lane x (on the side of the lane), the y and the trigger y
## of breakaway_waypoints
static func breakaway_next_waypoint(sim: Sim) -> void:
	var wp: Array = Tables.breakaway_waypoints[sim.breakaway_waypoint]
	sim.breakaway_lane_x = -int(wp[0]) if sim.breakaway_lane_side < 0 else int(wp[0])
	sim.breakaway_target_y = wp[1]
	sim.breakaway_trigger_y = wp[2]
	sim.breakaway_waypoint += 1

# --------------------------------------------------------------------------------------------
# goalie (ai_goalie 0x4b774, ai_goalie_get_puck 0x4b5c2)
# --------------------------------------------------------------------------------------------

static func goalie(sim: Sim, e: Entity) -> void:
	var puck := sim.puck
	if e.timer_e > 0:
		e.timer_e -= 1
	if sim.puck_carrier != e.slot:
		e.save_result = 0
	e.flags3 |= 6
	var ax := e.xi
	var ay := absi(e.yi)
	if ax > -0x29 and ax < 0x29 and ay > 0xc4 and ay < 0xe4:
		e.flags3 &= ~4
	if ax > -0x31 and ax < 0x31 and ay > 0xc4:
		e.flags3 &= ~2
	if Lines.handle_line_change(sim, e):
		return
	if e.flags & Entity.F_STATE_ENTERED:
		e.flags &= ~Entity.F_STATE_ENTERED
		e.timer_a = 0
		e.want_dir = 8
		e.target_y = -1
	var up := (e.flags & Entity.F_ATTACK_UP) != 0
	var own_y := -0xe4 if up else 0xe4          # a little in front of the goal line
	if ay >= 0xe5 or absi(ax) > 0x34 or ay > 0xee or ay < 0xb3:
		# out of position: back to the crease
		skate_towards(sim, e, -4 if ax < 0 else 4, own_y)
		return
	if (e.flags2 & Entity.F2_TURNING) == 0 and (e.flags & Entity.F_BUSY) == 0:
		Anim.set_animation(e, 0x99 if sim.puck_carrier == e.slot else 1)
	if sim.play_stopped:
		return
	# holding the puck too long is a stoppage
	if e.timer_b >= 0:
		if sim.puck_carrier == e.slot:
			if ay < 0x9b:
				e.timer_b = 0
			e.timer_b -= 1
			if e.timer_b < 0:
				Rules.queue_infraction(sim, e, Rules.INF_GOALIE_HOLD)
		else:
			e.timer_b = -1
	if e.flags2 & Entity.F2_TURNING:
		return
	e.timer_a -= 1
	if e.timer_a >= 0:
		goalie_move_dir(sim, e, e.want_dir)
		return
	e.timer_a = e.awareness / 3
	if (e.flags & Entity.F_USER) == 0:
		if (puck.yi ^ e.yi) < 0:
			# the puck is in the other half: rest in the middle of the crease
			goalie_move_to(sim, e, 0, -0xd4 if up else 0xd4)
			return
		e.target_y -= 1
		if sim.puck_carrier == e.slot:
			if e.timer_b < 0:
				e.timer_b = 0x5a
			e.target_y = -1
			if e.timer_b < 0x5a and sim.random(4) == 0:
				var opp := sim.opponents_of(e)
				for i in 6:
					var o := sim.entities[opp.first_slot + i]
					if (o.flags2 & Entity.F2_UNSELECTABLE) == 0 and o.line_slot > 0 and o.puck_dist < 0x14:
						e.flags |= Entity.F_BUSY
						e.flags2 |= Entity.F2_TURNING
						Anim.set_animation(e, 0x1135)      # cover the puck
						return
				if choose_pass_target(sim, e):
					return
		else:
			var dx := puck.xi - e.xi
			var dy := puck.yi - e.yi
			if sim.puck_carrier < 0:
				if e.target_y == 0 and e.puck_dist < 0x2d and absi(puck.yi) < 0xe9 and sim.opponents_of(e).nearest_dist < 0x3c and sim.random(0x100) < 10:
					e.facing = Tables.direction8(dx, dy)
					e.timer_c = 8
					e.flags |= Entity.F_BUSY
					e.flags2 |= Entity.F2_TURNING
					Anim.set_animation(e, 0x181)           # dive on the loose puck
					e.timer_e = 0x168
					sim.add_crowd(0x96, 0x4b0)
					return
			elif not sim.same_team(sim.puck_carrier, e.slot) and e.timer_e == 0 and sim.random(0x100) < 10 and e.puck_dist < 0x23 and absi(puck.yi) < 0xe9:
				e.facing = Tables.direction8(dx, dy)
				e.flags |= Entity.F_BUSY
				e.flags2 |= Entity.F2_TURNING
				Anim.set_animation(e, 0x1095)              # poke check
				e.timer_e = 0xf0
				return
	# positioning: on the line between the puck and the net, a few units out
	var pred: Array = sim.goal_prediction[1 if up else 0]
	var tx := puck.xi
	var ty := puck.yi
	if sim.puck_carrier == e.slot:
		tx = 0
	ty = clampi(ty, -0xe3, 0xe3) - own_y
	# face the puck, never straight into the own net
	var fdir := Tables.direction8(tx, ty)
	var fdiff := (fdir - e.facing) & 7
	if fdiff != 0:
		var stepd := ((-fdiff & 4) >> 1) - 1
		var nf := e.facing + stepd
		if (1 << e.facing) & 0x42:
			var bad := 0x83 if not up else 0x38
			if bad & (1 << (nf & 7)):
				nf -= stepd * 2
		e.facing = nf & 7
	var lead := 0xa0 if absi(puck.yi) > 0xbb else 0xe0
	var px := puck.xi + ((puck.vx * lead) >> 16)
	var py := clampi(puck.yi + ((puck.vy * lead) >> 16), -0xe3, 0xe3) - own_y
	if sim.puck_carrier == e.slot:
		px = 0
	var d := Sim.approx_distance(px, py)
	if d > 0x1d:
		var scale := 0x12
		if absi(puck.yi) < 0x74 and Rules.count_defenders_ahead(sim):
			scale = 0x14
		if sim.action_shot:
			scale += 8
		py = (scale * py) / (d + 1)
		px = ((scale + 8) * px) / (d + 1)
	ty = py + own_y
	tx = px
	# a shot on the way: move to where it crosses the line and pick a save
	var pred_steps: int = pred[1]
	var pred_x: int = pred[0]
	var coming := pred_steps >= 0 and pred_steps < 0x23
	if coming or (sim.puck_carrier < 0 and e.puck_dist < 0x1a and absi(puck.yi) < 0xe9):
		if coming and absi(pred_x) <= 0x18:
			tx = pred_x
		if coming and (e.flags & Entity.F_BUSY) == 0 and sim.puck_carrier != e.slot and absi(puck.xi) < 100 and puck.zi < 0x14 \
				and (absi(puck.vx) + absi(puck.vy)) > 0x1200:
			e.vx >>= 1
			e.vy >>= 1
			var rel := (Tables.direction8(puck.xi + (puck.vx >> 10) - e.xi, puck.yi + (puck.vy >> 10) - e.yi) - e.facing) & 7
			var idx := 1
			if rel == 0 or rel == 4:
				idx = 1 if sim.random(2) == 0 else 5
			elif rel < 4:
				idx = 1
			else:
				idx = 5
			if puck.zi >= 8 or puck.vz >= 0x800:
				idx += 2          # glove / blocker high
			elif pred_steps > 8 and e.facing != 2 and e.facing != 6 and sim.puck_carrier >= 0:
				idx += 1
			var anim := Tables.goalie_save_anims[clampi(idx, 1, 9)]
			if anim != 0:
				e.flags |= Entity.F_BUSY
				e.flags2 |= Entity.F2_TURNING
				Anim.set_animation(e, anim)
				sim.add_crowd(0x96, 0x4b0)
				return
	if absi(puck.yi) > 0xdc and sim.puck_carrier != e.slot:
		tx = -0x18 if puck.xi <= 0 else 0x18
	goalie_move_to(sim, e, tx, ty)

static func goalie_move_to(sim: Sim, e: Entity, tx: int, ty: int) -> void:
	var dx := tx - ((e.vx >> 8) + e.xi)
	var dy := ty - (e.yi + (e.vy >> 8))
	var dir := 8
	if absi(dx) >= 5 or absi(dy) >= 5:
		dir = Tables.direction8(dx, dy)
	e.want_dir = dir
	goalie_move_dir(sim, e, dir)

static func goalie_move_dir(sim: Sim, e: Entity, dir: int) -> void:
	if dir < 8:
		sim.skating_accelerate(e, dir)
	else:
		sim.brake(e)

## ai_goalie_get_puck (0x4b5c2): the goalie leaves the crease for a loose puck behind the net
static func goalie_get_puck(sim: Sim, e: Entity) -> void:
	if e.timer_e > 0:
		e.timer_e -= 1
	e.flags3 |= 6
	if (e.flags & Entity.F_USER) or sim.play_stopped:
		default_skate(sim, e)
		return
	if e.flags & Entity.F_STATE_ENTERED:
		e.flags &= ~Entity.F_STATE_ENTERED
		e.timer_a = 0
	e.react_timer -= 1
	if e.react_timer < 0:
		e.react_timer = e.awareness >> 2
		if sim.puck_carrier >= 0:
			default_skate(sim, e)
			return
		var puck := sim.puck
		if (puck.vy < 0) != ((e.flags & Entity.F_ATTACK_UP) != 0) and absi(puck.vy) > 0x800:
			default_skate(sim, e)
			return
		if sim.opponents_of(e).nearest_dist < 0x96:
			default_skate(sim, e)
			return
	chase_puck(sim, e)

# --------------------------------------------------------------------------------------------
# faceoffs (fowait faceoff agotofo initper pface pface2)
# --------------------------------------------------------------------------------------------

## ai_faceoff_wait (0x4d4f0): wait for the drop, then fall back to the role
static func faceoff_wait(sim: Sim, e: Entity) -> void:
	if (e.flags & Entity.F_BUSY) == 0 and not sim.faceoff_pending:
		e.push_state()

## ai_faceoff (0x4d528): the centre at the dot; CPU centres time the drop by skill
static func faceoff(sim: Sim, e: Entity) -> void:
	if e.flags & Entity.F_BUSY:
		return
	if not sim.faceoff_pending:
		e.timer_c = 0x14
		e.push_state()
		return
	if e.flags & Entity.F_STATE_ENTERED:
		e.flags &= ~Entity.F_STATE_ENTERED
		e.timer_a = 0
		e.frame = 0x16c if e.facing == 0 else 0x167
		Anim.set_animation(e, 0)
		e.timer_b = 0x28 if (e.flags & Entity.F_PLAYER2) == 0 else sim.random(10) + 0x14
	var side := 1 if (e.flags & Entity.F_PLAYER2) else 0
	var ready := 1
	if e.frame == 0x169 or e.frame == 0x16e:
		ready = 2
	elif e.frame == 0x16a or e.frame == 0x16f:
		ready = 3
		if e.anim_hold == 7:
			sim.play_sfx(0x9e + side)
	if e.left_handed == 0:
		ready += 3
	sim.faceoff_ready[side] = ready
	if e.flags & Entity.F_USER:
		return
	if e.flags2 & Entity.F2_TURNING:
		return
	e.flags2 |= Entity.F2_TURNING
	if e.timer_b < 0 and (sim.faceoff_timer < 0x11 or sim.random(8) == 0):
		e.timer_b = -1
		if sim.faceoff_timer < 0x11:
			e.flags |= Entity.F_BUSY
			Anim.set_animation(e, 0x7dd)
		else:
			Anim.set_animation(e, 0xd05)
		return
	e.timer_b -= 1
	if e.timer_b >= 0:
		e.flags2 &= ~Entity.F2_TURNING
		return
	Anim.set_animation(e, 0x7f1)
	e.flags2 &= ~Entity.F2_TURNING

## ai_all_goto_faceoff (0x52720): skate to the faceoff position after a whistle
static func all_goto_faceoff(sim: Sim, e: Entity) -> void:
	if e.line_slot < 0:
		e.set_state(Entity.State.DOOR_OPEN)
		e.timer_b = -100
		e.flags2 |= Entity.F2_UNSELECTABLE
		return
	if e.flags & Entity.F_BUSY:
		return
	if e.timer_b == -100:
		# arrived: back to the role (and out of a celebration / bench wait) until the faceoff is set up
		default_skate(sim, e)
		var s := e.state()
		if s == Entity.State.CELEBRATE or s == Entity.State.BENCH_WAIT:
			default_skate(sim, e)
		return
	if e.flags & Entity.F_STATE_ENTERED:
		e.flags &= ~Entity.F_STATE_ENTERED
		e.want_dir = 8
		e.timer_a = 0
		var pos := Rules.faceoff_position(sim, e)
		if sim.penalty_shot_phase != 0 and e.slot == sim.penalty_shot_slot:
			# the shooter waits just inside his own half at centre ice
			pos = Vector2i(0, -10 if (e.flags & Entity.F_ATTACK_UP) else 10)
		e.target_x = pos.x
		e.target_y = pos.y
		e.flags2 |= Entity.F2_NO_COLLIDE
		e.push_x = 0
		e.push_y = 0
		Anim.set_animation(e, 0x99 if e.line_slot == 0 else Anim.GLIDE)
	var dx := e.xi - e.target_x
	var dy := e.yi - e.target_y
	var d2 := dx * dx + dy * dy
	if d2 < 0x40 and absi(e.vx) < 0x10 and absi(e.vy) < 0x10:
		e.set_pos(e.target_x, e.target_y)
		e.timer_a -= 1
		if e.timer_a >= 0:
			return
		e.timer_a += 8
		Anim.set_animation(e, 0x99 if e.line_slot == 0 else Anim.GLIDE)
		var want := Tables.direction8(sim.faceoff_x - e.xi, sim.faceoff_y - e.yi)
		if e.line_slot == 0:
			if want == 2:
				want = 3 if (e.flags & Entity.F_ATTACK_UP) == 0 else 1
			elif want == 6:
				want = 5 if (e.flags & Entity.F_ATTACK_UP) == 0 else 7
		if want != e.facing:
			var diff := (want - e.facing) & 7
			e.facing = (e.facing + (1 if diff < 5 else -1)) & 7
			return
		e.vx = 0
		e.vy = 0
		e.timer_b = -100
		return
	if d2 < 400:
		ref_skate_to_point(sim, e, e.target_x, e.target_y)
	else:
		skate_towards(sim, e, e.target_x, e.target_y)

## ai_init_period (0x526ed): the players wait on the bench until the faceoff is set up
static func init_period(_sim: Sim, e: Entity) -> void:
	if e.flags & Entity.F_BUSY:
		return
	e.frame = -1
	e.timer_b = -100

## ai_puck_normal (0x4d8c7)
static func puck_normal(sim: Sim, e: Entity) -> void:
	if e.flags & Entity.F_STATE_ENTERED:
		e.flags &= ~Entity.F_STATE_ENTERED
		sim.puck_goal_timer = 0
		sim.puck_stuck_timer = 0x78
	PuckLogic.puck_update(sim)

## ai_puck_shadow (0x56ecf): the shadow sits under the puck (slot 15)
static func puck_shadow(sim: Sim, e: Entity) -> void:
	var puck := sim.puck
	if puck.frame != 0x189:
		if e.timer_d != -1 and e.anim == 0x7fd:
			e.set_pos(0, 0x122 if puck.yi >= 0 else -0x10a)
			e.vx = 0xe if puck.yi >= 0 else 0xd
		return
	e.set_pos(puck.xi, puck.yi)
	e.vx = 0
	e.y += 1 << 16

## ai_puck_faceoff (0x516e1): the stoppage is over, prepare the faceoff
static func puck_faceoff(sim: Sim, e: Entity) -> void:
	if e.flags & Entity.F_STATE_ENTERED:
		if sim.puck_carrier != Entity.Slot.REFEREE and sim.puck_carrier >= 0:
			sim.entities[sim.puck_carrier].timer_c = 0x78
		sim.puck_carrier = -1
		e.flags &= ~Entity.F_STATE_ENTERED
		if (sim.clock_seconds == 0 and sim.clock_sub == 0) or sim.game_over:
			Rules.next_period(sim)
			if sim.game_over:
				return
			return
		if sim.delayed_call:
			# a penalty was pending: it is called now (served as a faceoff)
			sim.delayed_call = false
		sim.skip_wait = false
		if sim.penalty_shot_phase != 0:
			# the penalty shot: nobody changes (apply_line_change keeps the players on the ice
			# here and send_team_to_faceoff does nothing during the shot)
			e.set_state(Entity.State.PUCK_FACEOFF2)
			e.timer_b = 1000
			return
		# line changes at the stoppage: a goalie pulled by the CPU comes back, the CPU coaches pick
		# their lines (choose_line), the users keep theirs unless a hotkey request is pending
		# (the line change prompt of the original times out to the same line)
		Lines.cpu_pull_goalie_check(sim)
		for i in 12:
			sim.entities[i].flags2 &= ~Entity.F2_LINE_CHANGE
		if sim.opt_line_changes and (sim.user1_team != 0 or sim.user2_team != 0) and sim.penalty_box_mode:
			# the users get their line change prompt: the penalty box sequence ends here
			sim.action_hold_camera = true
			sim.sort_draw_order()
			sim.penalty_box_mode = false
		for t in 2:
			var team := sim.teams[t]
			var other := sim.teams[1 - t]
			if sim.opt_line_changes:
				if sim.is_user_team(t):
					if sim.line_hotkey[t] >= 0:
						var slot := sim.user1_slot if sim.user1_team == t + 1 else sim.user2_slot
						if slot >= 0:
							Lines.request_line_change(sim, sim.entities[slot], sim.line_hotkey[t])
						sim.line_hotkey[t] = -1
					else:
						Lines.apply_line_change(sim, team)
				else:
					Lines.choose_line(sim, other, team)
					Lines.apply_line_change(sim, team)
			else:
				Lines.apply_line_change(sim, team)
			Lines.send_team_to_faceoff(sim, team)
	e.set_state(Entity.State.PUCK_FACEOFF2)
	e.timer_b = 1000

## ai_puck_faceoff2 (0x51bdb): wait for everybody, line up, count down and drop
static func puck_faceoff2(sim: Sim, e: Entity) -> void:
	if e.flags & Entity.F_STATE_ENTERED:
		e.timer_b -= 1
		var at_start := sim.period == 0 and sim.clock_sub == 0 and sim.clock_seconds == sim.period_length
		var wait := e.timer_b > 0 and not sim.skip_wait and not sim.injury_stoppage and not at_start
		if wait:
			if sim.ref_phase >= 0:
				return
			var all := true
			for i in 12:
				var p := sim.entities[i]
				if p.line_slot >= 0 and p.timer_b != -100:
					all = false
					break
			if not all:
				return
		e.flags &= ~Entity.F_STATE_ENTERED
		# a cut to the faceoff when the wait was skipped or after an injury
		sim.fade_in = sim.skip_wait or sim.injury_stoppage
		sim.skip_wait = false
		sim.injury_stoppage = false
		sim.ref_phase = -1
		sim.whistle_timer = 0
		sim.penalty_box_mode = false
		sim.infractions.clear()
		sim.penalty_shot_setup = false
		InfoPanel.reset(sim)
		if sim.penalty_shot_phase != 0:
			InfoPanel.stop_music(sim)
			penalty_shot_go(sim, e)
			return
		Rules.place_faceoff(sim)
		return
	e.timer_a -= 1
	if e.timer_a < 0:
		Rules.faceoff_resolve(sim)
		return
	if e.timer_a == 0x11:
		Anim.set_animation(sim.referee, 0xc43)      # the drop
	if e.timer_a != 0:
		var t := (e.timer_a + 6) >> 3
		if t <= 2:
			sim.faceoff_timer = 10 - t

## the penalty shot branch of ai_puck_faceoff2 (0x51fc6..0x5214d): the user of the shooter's team
## takes the shooter, the defending goalie is reset, play resumes and start_penalty_shot hands the
## puck to the shooter
static func penalty_shot_go(sim: Sim, e: Entity) -> void:
	sim.faceoff_pending = false
	sim.stoppage_countdown = false
	sim.stoppage_timer = -1
	sim.announce_timer = -1
	sim.delayed_call = false
	sim.pass_target = -1
	sim.icing_flags = 0
	sim.action_hold_camera = false
	sim.camera_target_x = 0
	sim.camera_target_y = 0
	Rules.reset_nets(sim)
	sim.sort_draw_order()
	sim.last_touch_x = 0
	sim.last_touch_y = 0
	sim.last_touch_slot = -1
	sim.last_passer = -1
	sim.last_shooter = -1
	var shot := sim.penalty_shot_slot
	if sim.user1_slot != shot and sim.user2_slot != shot:
		if sim.user1_team == sim.penalty_shot_team + 1:
			sim.user1_slot = sim.find_switch_target(shot, sim.user1_slot)
		elif sim.user2_team == sim.penalty_shot_team + 1:
			sim.user2_slot = sim.find_switch_target(shot, sim.user2_slot)
	var g := Rules.defending_goalie(sim)
	if g >= 0:
		var goalie := sim.entities[g]
		goalie.flags3 = 0
		goalie.timer_e = 0
		goalie.timer_f = 0
		goalie.pass_ok = 0
		goalie.flags2 &= ~(Entity.F2_UNSELECTABLE | Entity.F2_NO_COLLIDE)
		goalie.flags &= ~Entity.F_ARRIVED
	sim.play_stopped = false
	sim.misc_first_touch = true         # misc_flags 0x10, as after a faceoff
	e.flags &= ~Entity.F_ARRIVED
	e.set_state(Entity.State.PUCK_NORMAL)
	Rules.start_penalty_shot(sim)

## ai_ref_penalty_shot (0x52fb0): the referee carries the puck to centre ice, puts it down, skates
## to the side and whistles once the shooter and the goalie are ready
static func ref_penalty_shot(sim: Sim, e: Entity) -> void:
	if e.flags & Entity.F_BUSY:
		return
	var puck := sim.puck
	if e.flags & Entity.F_STATE_ENTERED:
		e.flags &= ~Entity.F_STATE_ENTERED
		e.want_dir = 8
		e.timer_a = 0
		e.react_timer = Tables.direction8(-e.xi, -e.yi)     # +0x27: facing towards centre ice
		e.target_x = 0
		e.target_y = 0
		e.timer_b = 0
		e.flags2 |= Entity.F2_NO_COLLIDE
		e.push_x = 0
		e.push_y = 0
		sim.puck_carrier = Entity.Slot.REFEREE
		puck.vx = 0
		puck.vy = 0
		puck.vz = 0
		puck.z = -100 * 0x10000
		Anim.set_animation(e, Anim.REF_GLIDE)
	if sim.penalty_shot_slot == -1:
		e.set_state(Entity.State.REF_PICKUP)
		return
	if e.timer_b == 100:
		return
	if e.timer_b == 1:
		# the puck is put down at centre ice
		sim.puck_carrier = -1
		puck.set_pos(0, 0)
		puck.z = 0
		puck.vx = 0
		puck.vy = 0
		puck.vz = 0
		e.timer_b += 1
	var dx := e.xi - e.target_x
	var dy := e.yi - e.target_y
	if dx * dx + dy * dy < 0x40 and absi(e.vx) < 0x10 and absi(e.vy) < 0x10:
		var want := e.react_timer
		if e.timer_b != 0:
			e.set_pos(e.target_x, e.target_y)
			want = 6
		e.timer_a -= 1
		if e.timer_a >= 0:
			return
		e.timer_a += 8
		Anim.set_animation(e, Anim.REF_GLIDE)
		if want != e.facing:
			var diff := (want - e.facing) & 7
			e.facing = (e.facing + (1 if diff < 5 else -1)) & 7
			return
		e.vx = 0
		e.vy = 0
		if e.timer_b != 0:
			if not Rules.all_players_arrived(sim):
				return
			sim.ref_phase = -1
			sim.play_sfx(0xa4)          # whistle: the shot may start
			e.timer_b = 100
			return
		# at centre ice: puts the puck down and moves to the side
		e.flags |= Entity.F_BUSY
		Anim.set_animation(e, 0xc03)
		e.target_x = 0x96
		e.target_y = 10 if (0 if sim.ends_switched else 1) == sim.penalty_shot_team else -10
		e.timer_b += 1
		sim.ref_phase = 0
		sim.action_hold_camera = false
		return
	ref_skate_to_point(sim, e, e.target_x, e.target_y)

## ai_all_penalty_shot_wait (0x52db0): everybody but the shooter and the goalie skates to his
## bench and steps off the ice until the shot is over
static func penalty_shot_wait(sim: Sim, e: Entity) -> void:
	if e.flags & Entity.F_BUSY:
		return
	if e.timer_a == 100:
		e.frame = -1
		PuckLogic._set_x(e, -0xa8)
		return
	if sim.penalty_shot_phase == 0:
		return
	if e.flags & Entity.F_STATE_ENTERED:
		e.flags &= ~Entity.F_STATE_ENTERED
		e.want_dir = 8
		e.target_y = (0x41 if (e.flags & Entity.F_PLAYER2) else -0x32) + (2 - sim.random(4)) * 0xf
		e.target_x = -0xa8
		e.timer_a = 0
		e.timer_b = 0
		e.next_line_slot = -1
		e.next_roster = -1
	e.timer_a -= 1
	if e.timer_a < 0:
		e.timer_a += 8
		var dy := e.yi - e.target_y
		var dx := e.xi - e.target_x
		if absi(dy) < 0x29 and dx < 0x21:
			if _leave_at_bench(sim, e, dx):
				e.flags2 |= Entity.F2_UNSELECTABLE
				e.timer_b = -100
				e.timer_a = 100
			return
	if (e.flags & Entity.F_ARRIVED) == 0:
		skate_towards(sim, e, e.target_x, e.target_y, 1 if (not sim.play_stopped and e.line_slot != 0) else 0)

## the common end of ai_all_penalty_shot_wait / ai_game_misconduct: at the boards the player turns
## towards the bench door (facing 4) and steps off (0x7bf, goalies 0xd2d). True once he is off.
static func _leave_at_bench(_sim: Sim, e: Entity, dx: int) -> bool:
	Anim.set_animation(e, 1 if e.line_slot == 0 else Anim.GLIDE)
	e.flags |= Entity.F_ARRIVED
	if e.facing != 4:
		e.facing = (e.facing + (1 if e.facing < 4 else -1)) & 7
	e.vy = 0
	e.vx = -0x800
	if dx > 0x10:
		return false
	e.vx = 0
	if e.facing != 4:
		return false
	e.vx = -0x800
	e.facing = 2
	Anim.set_animation(e, 0xd2d if e.line_slot == 0 else 0x7bf)
	e.flags |= Entity.F_BUSY
	return true

## ai_game_misconduct (0x4ab87): the player is thrown out: he skates to the bench door and leaves;
## his place is taken at the next faceoff (pick_player_for_position, done by assign_line_positions)
static func game_misconduct(sim: Sim, e: Entity) -> void:
	if e.flags & Entity.F_BUSY:
		return
	if e.timer_a == 100:
		e.flags2 &= ~Entity.F2_PENALIZED
		e.frame = -1
		e.set_state(Entity.State.INIT_PERIOD)
		return
	if e.flags & Entity.F_STATE_ENTERED:
		e.flags &= ~Entity.F_STATE_ENTERED
		e.flags2 |= Entity.F2_UNSELECTABLE
		if e.flags & Entity.F_USER:
			sim.switch_to_nearest(e, 0 if e.slot == sim.user1_slot else 1)
		e.want_dir = 8
		e.target_y = 0x24 if (e.flags & Entity.F_PLAYER2) else -0x1c
		e.target_x = -0xa8
		e.timer_a = 0
		e.flags2 |= Entity.F2_NO_COLLIDE
		e.push_x = 0
		e.push_y = 0
	e.timer_a -= 1
	if e.timer_a < 0:
		e.timer_a += 8
		var dy := e.yi - e.target_y
		var dx := e.xi - e.target_x
		if absi(dy) < 0x15 and dx < 0x21:
			if _leave_at_bench(sim, e, dx):
				e.timer_a = 100
			return
	if (e.flags & Entity.F_ARRIVED) == 0:
		skate_towards(sim, e, e.target_x, e.target_y)

# --------------------------------------------------------------------------------------------
# penalty box (pen dopen expen)
# --------------------------------------------------------------------------------------------

## ai_penalty_box (0x4adab): skate to the box at the boards (x = 0xa0, one seat per penalty)
static func penalty_box(sim: Sim, e: Entity) -> void:
	if e.flags & Entity.F_BUSY:
		return
	var team := sim.team_of(e)
	if e.flags & Entity.F_STATE_ENTERED:
		e.flags &= ~Entity.F_STATE_ENTERED
		e.flags2 |= Entity.F2_UNSELECTABLE
		e.want_dir = 8
		# the next free seat: the players already sitting in the box (penalized_count)
		var seat := mini(sim.box_count[team.index] & 0xf, 2)
		var side := 0xb if (e.flags & Entity.F_PLAYER2) else -0xb
		e.target_y = (seat + 3) * side
		e.target_x = 0xa0
		e.timer_a = 0
		e.flags2 |= Entity.F2_NO_COLLIDE
		e.push_x = 0
		e.push_y = 0
	var dx := e.xi - e.target_x
	var dy := e.yi - e.target_y
	if absi(dy) >= 0xd or dx <= -0x19:
		skate_towards(sim, e, e.target_x, e.target_y)
		return
	e.timer_a -= 1
	if e.timer_a >= 0:
		return
	e.timer_a += 8
	e.flags |= Entity.F_ARRIVED
	Anim.set_animation(e, Anim.GLIDE)
	if e.facing != 4:
		var diff := (4 - e.facing) & 7
		e.facing = (e.facing + (1 if diff < 5 else -1)) & 7
	e.vy = 0
	e.vx = 0x1000
	if dx > -9:
		e.vx = 0
		if e.facing == 4:
			# over the boards into the box
			e.flags |= Entity.F_BUSY
			e.facing = 2
			Anim.set_animation(e, Anim.FACEOFF)
			e.flags2 &= ~Entity.F2_PENALIZED
			if team.skaters_on_ice > 4:
				team.skaters_on_ice -= 1
			e.set_state(Entity.State.DOOR_OPEN)

## ai_door_open (0x4affb): in the box: off the ice until the penalty expires
static func door_open(sim: Sim, e: Entity) -> void:
	if e.flags & Entity.F_BUSY:
		return
	if e.line_slot >= 0:
		sim.box_count[e.team] += 1          # sits down (drawn as frame 0x17e in the box)
		e.line_slot = (e.line_slot & 0xff) | ~0xff      # high byte 0xff: hidden, still a skater slot
		e.frame = -1
		e.vx = 0
		e.vy = 0

## ai_exit_penalty_box (0x4b02d): steps back onto the ice next to the box
static func exit_penalty_box(sim: Sim, e: Entity) -> void:
	if e.flags & Entity.F_BUSY:
		return
	if e.flags & Entity.F_STATE_ENTERED:
		e.flags = (e.flags & ~(Entity.F_STATE_ENTERED | Entity.F_USER)) | Entity.F_ARRIVED
		e.flags2 |= Entity.F2_UNSELECTABLE
		sim.box_count[e.team] = maxi(0, sim.box_count[e.team] - 1)
		var seat := mini(sim.box_count[e.team], 2)
		var side := 0xb if (e.flags & Entity.F_PLAYER2) else -0xb
		e.set_pos(0x9e, (seat + 3) * side)
		e.vx = 0
		e.vy = 0
		e.facing = 2
		e.flags |= Entity.F_BUSY
		Anim.set_animation(e, 0x7bf)
		sim.sort_draw_order()
		return
	e.facing = 4
	e.next_line_slot = -1
	e.next_roster = -1
	e.flags &= ~(Entity.F_ARRIVED | Entity.F_USER)
	e.flags2 &= ~(Entity.F2_UNSELECTABLE | Entity.F2_NO_COLLIDE)
	e.vx = -0x1000
	e.frame = 0
	set_default_state(sim, e)

# --------------------------------------------------------------------------------------------
# referee (rfaceoff rnorm rcallpen rpickup rgotofo rpointgoal rgetnew)
# --------------------------------------------------------------------------------------------

## ai_ref_faceoff (0x4dff7): stands at the dot facing the centres
static func ref_faceoff(sim: Sim, e: Entity) -> void:
	if e.flags & Entity.F_BUSY or sim.injury_stoppage or (sim.clock_seconds == 0 and sim.clock_sub == 0):
		return
	if e.flags & Entity.F_STATE_ENTERED:
		e.flags &= ~Entity.F_STATE_ENTERED
		e.facing = 2 if sim.faceoff_x <= 0 else 6
		Anim.set_animation(e, 0xc57)
		e.flags &= ~Entity.F_ARRIVED
		e.flags2 &= ~Entity.F2_NO_COLLIDE
	if not sim.faceoff_pending:
		e.set_pos(sim.faceoff_x + (-0xf if sim.faceoff_x <= 0 else 0xf), sim.faceoff_y)
		e.vx = 0
		e.vy = 0

## ai_ref_normal (0x4e0bd): keeps up with the play along the boards
static func ref_normal(sim: Sim, e: Entity) -> void:
	if e.flags & Entity.F_BUSY:
		return
	if sim.clock_seconds == 0 and sim.clock_sub == 0:
		sim.apply_skating(e, 8)
		return
	if e.flags & Entity.F_STATE_ENTERED:
		e.flags &= ~Entity.F_STATE_ENTERED
		Anim.set_animation(e, Anim.REF_GLIDE)
	var puck := sim.puck
	var side := -1 if e.xi <= 0 else 1
	if absi(puck.xi) < 0x32 and absi(puck.yi) >= 0xad and absi(puck.yi) <= 0xe7:
		e.target_x = side * 0x46
		e.target_y = -0xed if puck.yi <= 0 else 0xed
	elif absi(puck.yi) < 99 or (sim.puck_carrier >= 0 and sim.puck_carrier < 12 and (puck.yi < 0) == ((sim.entities[sim.puck_carrier].flags & Entity.F_ATTACK_UP) != 0)):
		e.target_x = side * 0x90
		if absi(e.yi - sim.camera_y) >= 0x33:
			e.target_y = sim.camera_y
	else:
		e.target_x = side * 0x78
		e.target_y = -0xe8 if puck.yi <= 0 else 0xe8
	skate_towards(sim, e, e.target_x, e.target_y, 2)

## ai_ref_call_penalty (0x4eb04): skates to the side, signals the call, then collects the puck
static func ref_call_penalty(sim: Sim, e: Entity) -> void:
	if e.flags & Entity.F_BUSY:
		return
	if e.flags & Entity.F_STATE_ENTERED:
		e.flags &= ~Entity.F_STATE_ENTERED
		var inf := clampi(sim.ref_infraction, 0, 31)
		if Tables.ref_signal_dir[inf] < 0:
			if inf == Rules.INF_GOAL:
				# the goal is announced on the panel (announce_goal)
				var t := 0
				for k in 2:
					if sim.teams[k].attacks_up == (sim.puck.yi > 0):
						t = k
				var team := sim.teams[t]
				var a1: int = team.carrier_history[1] if team.carrier_history[1] >= 0 else -1
				var a2: int = team.carrier_history[2] if team.carrier_history[2] >= 0 else -1
				if a1 < 0:
					a2 = -1
				InfoPanel.announce_goal(sim, t, team.carrier_history[0], a1, a2)
			e.set_state(Entity.State.REF_PICKUP)
			return
		e.want_dir = 8
		e.target_y = 0
		e.target_x = 0xa0
		e.timer_a = 0
		e.flags2 |= Entity.F2_NO_COLLIDE
	if absi(e.yi - e.target_y) > 0xc or e.xi - e.target_x < -0x14:
		ref_skate_to_point(sim, e, e.target_x, e.target_y)
		return
	e.timer_a -= 1
	if e.timer_a >= 0:
		return
	e.timer_a += 8
	Anim.set_animation(e, Anim.REF_GLIDE)
	var want: int = Tables.ref_signal_dir[clampi(sim.ref_infraction, 0, 31)]
	if want != e.facing:
		var diff := (want - e.facing) & 7
		e.facing = (e.facing + (1 if diff < 5 else -1)) & 7
	e.vx = 0
	e.vy = 0
	if want != e.facing:
		return
	e.flags |= Entity.F_BUSY
	var anim: int = Tables.ref_signal_anim[clampi(sim.ref_infraction, 0, 31)]
	if anim > 0:
		Anim.set_animation(e, anim)
	e.set_state(Entity.State.REF_PICKUP)

## ai_ref_pickup_puck (0x4ed7c): everybody to the dot, the referee fetches the puck
static func ref_pickup(sim: Sim, e: Entity) -> void:
	if e.flags & Entity.F_BUSY:
		return
	# the referee waits while the panel opens and plays its clip (not for the fans or the clapping)
	if sim.clip != InfoPanel.CLIP_CLAP and sim.clip != InfoPanel.CLIP_FAN_ANTHEM and sim.panel >= 0 and sim.panel < InfoPanel.HELD:
		Anim.set_animation(e, Anim.REF_GLIDE)
		# the goal is announced once the panel was up for a while (say_goal_wrapper); after an
		# overtime goal the panel opens again
		if sim.panel >= 0xec and not sim.goal_call.is_empty():
			var g: Array = sim.goal_call
			var assists: Array = []
			for k in [2, 3]:
				if g[k] >= 0:
					assists.append(Speech.number(sim, g[0], g[k]))
			Speech.say(sim, Speech.goal(Speech.abbrev(sim, g[0]), Speech.number(sim, g[0], g[1]), assists))
			sim.goal_call = []
			if sim.period >= 3:
				sim.panel = 0x38
		return
	var puck := sim.puck
	if not sim.infractions.is_empty():
		# more calls to signal (penalty_box_update runs again with ref_phase -1)
		Anim.set_animation(e, Anim.REF_GLIDE)
		sim.ref_phase = -1
		return
	if absi(puck.xi) >= 0xa1 or absi(puck.yi) >= 0x113:
		e.set_state(Entity.State.REF_GET_NEW_PUCK)
		return
	if e.flags & Entity.F_STATE_ENTERED:
		if sim.injury_stoppage or (sim.clock_seconds == 0 and sim.clock_sub == 0) or sim.game_over:
			sim.ref_phase = -1
			sim.puck.set_state(Entity.State.PUCK_FACEOFF)
			e.set_state(Entity.State.REF_FACEOFF)
			return
		sim.ref_phase = 1
		e.flags &= ~Entity.F_STATE_ENTERED
		Rules.all_goto_positions(sim)
		e.want_dir = 8
		e.timer_a = 0
		e.timer_b = 0
		e.flags2 |= Entity.F2_NO_COLLIDE
		e.push_x = 0
		e.push_y = 0
		Anim.set_animation(e, Anim.REF_GLIDE)
		# a goalie who made the save that froze the puck gets the SAVED clip (once a period); after routine
		# stoppages the announcer or the crowd (ref_check_announcements)
		if sim.ref_infraction == Rules.INF_GOALIE_HOLD and sim.ref_infraction_slot >= 0 and sim.ref_infraction_slot < 12 \
				and sim.entities[sim.ref_infraction_slot].save_result != 0 and not sim.save_clip_shown:
			sim.entities[sim.ref_infraction_slot].save_result = 0
			InfoPanel.load_clip(sim, InfoPanel.CLIP_SAVE)
			sim.save_clip_shown = true      # once a period
			InfoPanel.open(sim)
			return
		if sim.ref_infraction != Rules.INF_GOAL and InfoPanel.ref_announcements(sim):
			return
		InfoPanel.close(sim)
	if sim.puck_carrier >= 0 and sim.puck_carrier != Entity.Slot.REFEREE:
		sim.puck_carrier = -1
		puck.set_state(Entity.State.PUCK_IDLE)
	if e.timer_b >= 0x259:
		# took too long: a new puck
		sim.puck_carrier = Entity.Slot.REFEREE
		puck.vx = 0
		puck.vy = 0
		puck.vz = 0
		puck.z = 100 << 16
		e.set_state(Entity.State.REF_GOTO_FACEOFF)
		return
	var in_net := absi(puck.xi) == 6 and absi(puck.yi) == 0xf0
	if in_net:
		e.target_x = puck.xi
		e.target_y = -0xe3 if puck.yi < 0 else 0xe3
	else:
		e.target_x = puck.xi + (puck.vx >> 7)
		e.target_y = puck.yi + (puck.vy >> 7)
	var dx := e.xi - puck.xi
	var dy := e.yi - (( -0xee if puck.yi < 0 else 0xee) if in_net else puck.yi)
	if absi(dx) > 0xc or absi(dy) > 0xc:
		e.timer_b += 1
		ref_skate_to_point(sim, e, e.target_x, e.target_y)
		return
	e.timer_a -= 1
	if e.timer_a >= 0:
		return
	e.timer_a += 8
	Anim.set_animation(e, Anim.REF_GLIDE)
	var want := Tables.direction8(puck.xi - e.xi, puck.yi - e.yi)
	if want < 8 and ((want - e.facing + 1) & 7) > 2:
		var diff := (want - e.facing) & 7
		e.facing = (e.facing + (1 if diff < 5 else -1)) & 7
		e.timer_b += 1
		ref_skate_to_point(sim, e, e.target_x, e.target_y)
		return
	e.vx = 0
	e.vy = 0
	sim.puck_carrier = Entity.Slot.REFEREE
	puck.vx = 0
	puck.vy = 0
	puck.vz = 0
	puck.z = -100 * 0x10000
	if want < 8:
		e.facing = want
	e.flags |= Entity.F_BUSY
	Anim.set_animation(e, 0xc03)        # picks the puck up
	e.set_state(Entity.State.REF_GOTO_FACEOFF)

## ai_ref_goto_faceoff (0x4f5bf): carries the puck to the dot
static func ref_goto_faceoff(sim: Sim, e: Entity) -> void:
	if sim.penalty_shot_phase != 0:
		e.set_state(Entity.State.REF_PENALTY_SHOT)
		return
	if e.flags & Entity.F_BUSY:
		return
	var puck := sim.puck
	if e.flags & Entity.F_STATE_ENTERED:
		e.flags &= ~Entity.F_STATE_ENTERED
		e.want_dir = 8
		e.timer_a = 0
		e.target_x = sim.faceoff_x + (-0xf if sim.faceoff_x <= 0 else 0xf)
		e.target_y = sim.faceoff_y
		e.flags2 |= Entity.F2_NO_COLLIDE
		e.push_x = 0
		e.push_y = 0
		sim.puck_carrier = Entity.Slot.REFEREE
		puck.vx = 0
		puck.vy = 0
		puck.vz = 0
		puck.z = -100 * 0x10000
		Anim.set_animation(e, Anim.REF_GLIDE)
	puck.set_pos(e.xi, e.yi)
	var dx := e.xi - e.target_x
	var dy := e.yi - e.target_y
	if dx * dx + dy * dy < 0x40 and absi(e.vx) < 0x10 and absi(e.vy) < 0x10:
		e.set_pos(e.target_x, e.target_y)
		e.timer_a -= 1
		if e.timer_a >= 0:
			return
		e.timer_a += 8
		Anim.set_animation(e, Anim.REF_GLIDE)
		var want := 2 if sim.faceoff_x <= 0 else 6
		if want != e.facing:
			var diff := (want - e.facing) & 7
			e.facing = (e.facing + (1 if diff < 5 else -1)) & 7
			return
		e.vx = 0
		e.vy = 0
		sim.ref_phase = -1
		e.set_state(Entity.State.REF_FACEOFF)
		return
	ref_skate_to_point(sim, e, e.target_x, e.target_y)

## ai_ref_point_goal (0x4f7d0): after a goal the referee points at the net
static func ref_point_goal(sim: Sim, e: Entity) -> void:
	if e.flags & Entity.F_BUSY:
		return
	if e.flags & Entity.F_STATE_ENTERED:
		e.flags &= ~Entity.F_STATE_ENTERED
		e.want_dir = 8
		e.timer_a = 0
		e.target_y = -0xe6 if sim.puck.yi <= 0 else 0xe6
		e.target_x = -0x32 if e.xi <= 0 else 0x32
		e.flags2 |= Entity.F2_NO_COLLIDE
		e.push_x = 0
		e.push_y = 0
	if absi(e.yi - e.target_y) < 0xd and absi(e.yi) <= absi(e.target_y) and absi(e.xi - e.target_x) < 0xd:
		e.timer_a -= 1
		if e.timer_a >= 0:
			return
		e.timer_a += 8
		Anim.set_animation(e, Anim.REF_GLIDE)
		var want := Tables.direction8(-e.xi, e.target_y - e.yi)
		if want != e.facing:
			var diff := (want - e.facing) & 7
			e.facing = (e.facing + (1 if diff < 5 else -1)) & 7
			return
		e.vx = 0
		e.vy = 0
		e.flags |= Entity.F_BUSY
		Anim.set_animation(e, 0xc1b)       # points at the goal
		e.set_state(Entity.State.REF_CALL_PENALTY)
		return
	ref_skate_to_point(sim, e, e.target_x, e.target_y)

## ai_ref_get_new_puck (0x4e8ef): the puck left the rink; the referee gets a new one at the boards
static func ref_get_new_puck(sim: Sim, e: Entity) -> void:
	if e.flags & Entity.F_BUSY:
		return
	if e.flags & Entity.F_STATE_ENTERED:
		if sim.injury_stoppage or (sim.clock_seconds == 0 and sim.clock_sub == 0) or sim.game_over:
			sim.ref_phase = -1
			sim.puck.set_state(Entity.State.PUCK_FACEOFF)
			e.set_state(Entity.State.REF_FACEOFF)
			return
		sim.ref_phase = 1
		e.flags &= ~Entity.F_STATE_ENTERED
		Rules.all_goto_positions(sim)
		e.want_dir = 8
		e.target_y = 0
		e.target_x = 0xa0
		e.timer_a = 0
		e.flags2 |= Entity.F2_NO_COLLIDE
		Anim.set_animation(e, Anim.REF_GLIDE)
	if absi(e.yi - e.target_y) > 6 or e.xi - e.target_x < -10:
		ref_skate_to_point(sim, e, e.target_x, e.target_y)
		return
	e.timer_a -= 1
	if e.timer_a >= 0:
		return
	e.timer_a += 8
	Anim.set_animation(e, Anim.REF_GLIDE)
	if e.facing != 2:
		var diff := (2 - e.facing) & 7
		e.facing = (e.facing + (1 if diff < 5 else -1)) & 7
	e.vx = 0
	e.vy = 0
	if e.facing != 2:
		return
	e.flags |= Entity.F_BUSY
	Anim.set_animation(e, 0xc1b)
	sim.puck.flags &= ~Entity.F_ARRIVED
	e.set_state(Entity.State.REF_GOTO_FACEOFF)
