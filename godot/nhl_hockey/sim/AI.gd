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

## ai_skate_towards (0x5e93b): re-evaluates the direction every 12 steps: around the nets
## (ai_choose_direction), standing (9) within 0xc of the point unless still short of the real
## target without moving; `mode` adjusts it (1 = ai_near_carrier_check, 2 = ai_ref_positioning,
## 3 = carrier_scan_opponents). Standing still he turns a step towards the puck (the camera target
## while the puck's flags2 bit 0 is set). The scratch words carry the target in and the direction
## (or the turn) and the y out, as in the original.
static func skate_towards(sim: Sim, e: Entity, tx: int, ty: int, mode: int = 0) -> void:
	sim.scratch_a = tx
	sim.scratch_b = ty
	e.dir_timer = Entity.to_s8(e.dir_timer - 1)
	if e.dir_timer < 0:
		e.dir_timer += 12
		var t := choose_direction(sim, e, tx, ty)
		var px := e.xi + Entity.to_s8(e.vx >> 8)
		var py := e.yi + Entity.to_s8(e.vy >> 8)
		var dx := Sim._s16(t.x - px)
		var dy := Sim._s16(t.y - py)
		sim.scratch_a = dx
		sim.scratch_b = dy
		var dir: int
		if absi(dx) <= 0xc and absi(dy) <= 0xc and (absi(tx - px) <= 0xc or e.vx != 0) and (absi(ty - py) <= 0xc or e.vy != 0):
			dir = 9
		else:
			dir = Tables.direction8(dx, dy)
		sim.scratch_a = dir
		if mode == 1:
			dir = near_carrier_check(sim, e, dir)
		elif mode == 2:
			dir = ref_positioning(sim, e, dir)
		elif mode == 3:
			dir = carrier_scan_opponents(sim, e, dir)
		sim.scratch_a = dir
		e.want_dir = dir & 0xff
		if Sim._s16(dir) > 7 and e.vx == 0 and e.vy == 0:
			var fx := sim.puck.xi
			var fy := sim.puck.yi
			if sim.puck.flags2 & 1:
				fx = sim.camera_target_x
				fy = sim.camera_target_y
			var ax := Sim._s16(fx - e.xi)
			var ay := Sim._s16(fy - e.yi)
			sim.scratch_b = ay
			var hw := _heading_word(e)
			var d := Sim._s16(hw - Tables.direction8(ax, ay))
			sim.scratch_a = d
			if d != 0:
				_set_heading_word(e, (hw + ((d & 4) >> 1) - 1) & 7)
	sim.apply_skating(e, Entity.to_s8(e.want_dir))

## ai_near_carrier_check (0x5e7fe): a defender close to the carrier moves into his path
static func near_carrier_check(sim: Sim, e: Entity, dir: int) -> int:
	if sim.puck_carrier < 0:
		return dir
	var c := sim.entities[sim.puck_carrier]
	var dx := Sim._s16(e.xi - c.xi)
	var fx := Sim._s16(Entity.to_s8(e.vx >> 8) - Entity.to_s8(c.vx >> 8) + dx)
	sim.scratch_ac = (sim.scratch_ac & 0xffff0000) | (fx & 0xffff)
	if absi(fx) > 0x28:
		return dir
	var dy := Sim._s16(e.yi - c.yi)
	var fy := Sim._s16(Entity.to_s8(e.vy >> 8) - Entity.to_s8(c.vy >> 8) + dy)
	sim.scratch_b = fy
	if absi(fy) > 0x28:
		return dir
	sim.scratch_b = dy
	var out := Tables.direction8(dx, dy)
	if sim.opt_offsides:
		var ry := Sim._s16((e.yi if (e.flags & Entity.F_ATTACK_UP) else -e.yi) - 0x4e)
		sim.scratch_b = ry
		if ry <= 0xa and ry >= -0x32:
			# at the blue line: slide along it instead of going offside
			sim.scratch_b = e.xi
			out = 2 if e.xi > c.xi else 6
	return out

## ai_ref_positioning (0x5e4c4): the referee keeps out of everybody's way
static func ref_positioning(sim: Sim, e: Entity, dir: int) -> int:
	if e.flags2 & Entity.F2_NO_COLLIDE:
		return dir
	var ay := absi(e.yi)
	if ay > 0xf2 and absi(e.xi) < 0x32:
		# behind a net: skate out along the boards
		if e.yi > 0:
			if e.vy > 0:
				return 7 if e.xi < 0 else 1
		elif e.vy < 0:
			return 5 if e.xi < 0 else 3
		return 6 if e.xi < 0 else 2
	# the nearest player (or the puck, unless a player is within 0x50) within 0x28 a step ahead:
	# out of his way, along the boards near them, never across the play in the middle
	var best := 100
	var out := dir
	for i in 15:
		if i == 12 or i == 13:
			continue
		if i == 14 and best <= 0x50:
			continue
		var o := sim.entities[i]
		var dx := Sim._s16(e.xi - o.xi)
		var afx := absi(Sim._s16(dx + Entity.to_s8(e.vx >> 8) - Entity.to_s8(o.vx >> 8)))
		sim.scratch_ac = (sim.scratch_ac & 0xffff0000) | afx
		if afx > 0x28:
			continue
		var dy := Sim._s16(e.yi - o.yi)
		var afy := absi(Sim._s16(dy + Entity.to_s8(e.vy >> 8) - Entity.to_s8(o.vy >> 8)))
		sim.scratch_b = afy
		if afy > 0x28 or best <= afx + afy:
			continue
		best = afx + afy
		var d := Tables.direction8(dx, dy)
		out = d
		if e.xi < -0x82:
			if d > 4 and d < 8:
				out = 4 if o.vy != 0 else 0
		elif e.xi > 0x82:
			if d > 0 and d < 4:
				out = 4 if o.vy != 0 else 0
		elif e.xi > -0x64 and e.xi < 0:
			if d > 0 and d < 4:
				out = 8 - d
				if out == 6 and o.vy != 0:
					out = 5 if dy < 0 else 4
				else:
					out = 7 if dy > 0 else 0
		elif e.xi >= 0 and e.xi < 0x64:
			if d > 4 and d < 8:
				out = 8 - d
				if out == 2 and o.vy != 0:
					out = 4 if dy >= 0 else 3
				else:
					out = 1 if dy > 0 else 0
	return out

## ref_skate_to_point (0x4e29c): skate to a point at walking pace: on it within 8 (the fractions
## stay); round the net from behind it (0xfc deep, 0x28 out) or from its side (0xdc, 0x28); slowed
## by a quarter within 0x19, at least 0x640 each way while 8 or more off (the skating animation
## from the glide, the glide from none), turned a step towards the point unless the direction
## timer runs (the original takes the point from the scratch words ai_skate_towards left)
static func ref_skate_to_point(sim: Sim, e: Entity, tx: int, ty: int) -> void:
	var a := tx
	var b := ty
	var sdx := Sim._s16(a - e.xi)
	var sdy := Sim._s16(b - e.yi)
	var adx := absi(sdx)
	var ady := absi(sdy)
	if adx < 8 and ady < 8:
		e.vy = 0
		e.vx = 0
		e.x = (a << 16) | (e.x & 0xffff)
		e.y = (b << 16) | (e.y & 0xffff)
		return
	var aex := absi(e.xi)
	var aey := absi(e.yi)
	var ab := absi(b)
	if aex <= 0x1e and aey >= 0xf2 and ab < 0xf2:
		# behind the net: out along the boards first
		b = -0xfc if e.yi < 0 else 0xfc
		a = -0x28 if a < 0 else 0x28
		if (e.vy > 0) != (e.yi > 0):
			e.vy = 0
		sdx = Sim._s16(a - e.xi)
		sdy = Sim._s16(b - e.yi)
		adx = absi(sdx)
		ady = absi(sdy)
	elif aex >= 0x10 and aex <= 0x1e and aey >= 0xe8 and (b ^ e.yi) >= 0 and ab < 0xe8 and ab > 0xe0 and absi(a) < 0x14:
		# beside the net, the point in front of it: round the post
		b = -0xdc if e.yi < 0 else 0xdc
		a = -0x28 if e.xi < 0 else 0x28
		if (e.vx > 0) != (e.xi > 0):
			e.vx = 0
		sdx = Sim._s16(a - e.xi)
		sdy = Sim._s16(b - e.yi)
		adx = absi(sdx)
		ady = absi(sdy)
	skate_towards(sim, e, a, b)
	if adx < 0x19 and ady < 0x19:
		if absi(e.vx) > 0x9c4:
			e.vx = Sim._s16(e.vx - _div_trunc(e.vx, 4))
		if absi(e.vy) > 0x9c4:
			e.vy = Sim._s16(e.vy - _div_trunc(e.vy, 4))
	var glide := 0x289
	var skate := 0x2e9
	if e.slot == Entity.Slot.REFEREE:
		glide = 0xa5b
		skate = 0xa73
	elif e.line_slot == 0:
		glide = 0x99
		skate = 0x1f1
	if adx >= 8 and absi(e.vx) < 0x640:
		if e.vx == 0 and e.anim == glide:
			Anim.set_animation(e, skate)
		elif e.anim == 0:
			Anim.set_animation(e, glide)
		e.vx = 0x640 if sdx > 0 else -0x640
	if ady >= 8 and absi(e.vy) < 0x640:
		if e.vx == 0 and e.anim == glide:
			Anim.set_animation(e, skate)
		elif e.anim == 0:
			Anim.set_animation(e, glide)
		e.vy = 0x640 if sdy > 0 else -0x640
	var hw := _heading_word(e)
	var rel := (Tables.direction8(Sim._s16(sim.scratch_a - e.xi), Sim._s16(sim.scratch_b - e.yi)) - hw) & 7
	if ((rel + 1) & 7) > 2 and e.dir_timer == 0:
		_set_heading_word(e, (hw + (1 if rel < 5 else -1)) & 7)

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

## ai_goalie (0x4b774). In the crease (flags3 bit 2: the goal mouth, bit 4: the crease) the goalie
## stands (0x99 with the puck); outside it he skates back to it (to +-4, 0xc4); behind the goal line
## he comes out round the post (0xa0). Holding the puck longer than 0x5a steps from 0x9b in is an
## infraction. Every awareness / 3 steps he decides: the puck in the other half: the middle of the
## crease (0xd4); with the puck: cover it when an opponent is within 0x14 (one in four, after
## holding it a little), else pass (ai_choose_pass_target with goalie_pass_mode 1); a loose puck
## close by (0x2d) with opponents near (0x3c): dive (1 in 0x19.6); an opponent carrying it close
## (0x23): poke check (same odds, then 0xf0 steps not). Otherwise he turns towards the puck (never
## to face his own net) and stands on the line from the net to where the puck will be (0xe0 / 0xa0
## steps ahead) 0x12 to 0x1c out (further when the carrier is alone or winds up). A shot predicted
## to reach the goal line (goal_prediction) wide of him makes him move across or, close to it, try
## a save (goalie_save_anims by the side of the puck, high or low); a hard rim around the boards
## behind the net with everybody far makes him go and get it (GOALIE_GET_PUCK). The scratch words
## of the original carry the targets; the original's e03bc stays stale when flags3 bit 2 is set.
static func goalie(sim: Sim, e: Entity) -> void:
	var puck := sim.puck
	var keep := true            # ebp: stand still when within 5 of the target
	var a := sim.scratch_a      # word e03bc: x / direction / save animation
	var b := sim.scratch_b      # word e03c0: y
	var ac := Sim._s16(sim.scratch_ac)   # word e03ac: the y target
	var b0 := 0                 # word e03b0: the goal line offset, then the side of a save
	var b4 := 0                 # word e03b4: the distance out
	if e.timer_e > 0:
		e.timer_e -= 1
	if sim.puck_carrier != e.slot:
		e.save_result = 0
	e.flags3 |= 6
	var x := e.xi
	var ay := absi(e.yi)
	if x >= -0x28 and x < 0x29 and ay >= 0xc5 and ay < 0xe4:
		e.flags3 &= ~4
	if x >= -0x30 and x < 0x31 and ay >= 0xc5:
		e.flags3 &= ~2
	if Lines.handle_line_change(sim, e):
		return
	if e.flags & Entity.F_STATE_ENTERED:
		e.flags &= ~Entity.F_STATE_ENTERED
		e.timer_a = 0
		e.want_dir = 8
		e.dir_timer = 0
		e.target_y = Sim._s16((e.target_y & 0xff) | 0xff00)      # the high byte only
	var up := (e.flags & Entity.F_ATTACK_UP) != 0
	var pred: Array = sim.goal_prediction[1 if up else 0]
	if ay > 0xe4:
		ac = 0
		a = (-0xa0 if e.xi < 0 else 0xa0) if absi(x) <= 0x30 else x
		_goalie_tail(sim, e, a, ac, keep)
		return
	if absi(x) > 0x34 or ay >= 0xef or ay < 0xb3:
		sim.scratch_a = 4 if x >= 0 else -4
		sim.scratch_b = -0xc4 if up else 0xc4
		skate_towards(sim, e, sim.scratch_a, sim.scratch_b)
		return
	if (e.flags2 & Entity.F2_TURNING) == 0 and (e.flags & Entity.F_BUSY) == 0:
		Anim.set_animation(e, 0x99 if sim.puck_carrier == e.slot else 1)
	if sim.play_stopped:
		return
	if e.timer_b >= 0:
		if sim.puck_carrier == e.slot:
			if ay < 0x9b:
				e.timer_b = 0
			e.timer_b = Sim._s16(e.timer_b - 1)
			if e.timer_b < 0:
				Rules.queue_infraction(sim, e, Rules.INF_GOALIE_HOLD)
		else:
			e.timer_b = -1
	if e.flags2 & Entity.F2_TURNING:
		return
	e.timer_a = Sim._s16(e.timer_a - 1)
	if e.timer_a >= 0:
		var d := Entity.to_s8(e.want_dir)
		sim.scratch_ac = (sim.scratch_ac & 0xffff0000) | (d & 0xffff)
		goalie_move_dir(sim, e, d)
		return
	e.timer_a = e.awareness / 3
	var decide := true          # loc_4baf5: the dive and the poke check
	if (e.flags & Entity.F_USER) == 0:
		b = Sim._s16(puck.yi ^ e.yi)
		if b < 0:
			a = 0
			ac = -0xd4 if up else 0xd4
			_goalie_tail(sim, e, a, ac, keep)
			return
		e.target_y = Sim._s16(e.target_y - 1)
		if sim.puck_carrier == e.slot:
			decide = false
			if e.timer_b < 0:
				e.timer_b = 0x5a
			e.target_y = -1
			if e.timer_b < 0x5a and sim.random(4) == 0:
				var first := 6 if e.slot < 6 else 0
				for i in 6:
					var o := sim.entities[first + i]
					if (o.flags2 & Entity.F2_UNSELECTABLE) == 0 and o.line_slot > 0 and o.puck_dist < 0x23 and o.puck_dist < 0x14:
						e.flags |= Entity.F_BUSY
						e.flags2 |= Entity.F2_TURNING
						Anim.set_animation(e, 0x1135)        # cover the puck
						return
				sim.goalie_pass_mode = 1
				if choose_pass_target(sim, e):
					return
	if decide:
		a = Sim._s16(puck.xi - e.xi)
		b = Sim._s16(puck.yi - e.yi)
		if sim.puck_carrier < 0:
			if e.target_y == 0 and e.puck_dist < 0x2d and absi(puck.yi) < 0xe9 \
					and sim.opponents_of(e).nearest_dist < 0x3c and sim.random(0x100) < 0xa:
				_set_heading_word(e, Tables.direction8(a, b))
				e.timer_c = 8
				e.flags |= Entity.F_BUSY
				e.flags2 |= Entity.F2_TURNING
				Anim.set_animation(e, 0x181)                # dive on the loose puck
				e.timer_e = 0x168
				sim.add_crowd(0x96, 0x4b0)
				sim.scratch_a = a
				sim.scratch_b = b
				return
		elif not sim.same_team(sim.puck_carrier, e.slot) and e.timer_e == 0 and sim.random(0x100) < 0xa \
				and e.puck_dist < 0x23 and absi(puck.yi) < 0xe9:
			_set_heading_word(e, Tables.direction8(a, b))
			e.flags |= Entity.F_BUSY
			e.flags2 |= Entity.F2_TURNING
			Anim.set_animation(e, 0x1095)                    # poke check
			e.timer_e = 0xf0
			sim.scratch_a = a
			sim.scratch_b = b
			return
	# positioning (loc_4baab)
	b0 = -0xe4 if up else 0xe4
	b4 = -0xe8 if up else 0xe8
	if absi(e.yi) > 0xe4:
		ac = 0
		a = 0 if absi(e.xi) > 0x30 else (-0xa0 if e.xi < 0 else 0xa0)
		_goalie_tail(sim, e, a, ac, keep)
		return
	var t := _goalie_clamp_target(sim, e, puck.xi, puck.yi, b0)
	a = Tables.direction8(t.x, t.y)
	b = _heading_word(e)
	a = Sim._s16(a - b)
	if a != 0:
		a = (((-a) & 4) >> 1) - 1
		var mask := 1 << (b & 31)
		var nb := Sim._s16(b + a)
		b = nb
		if mask & 0x42:
			var bad := 0x38 if up else 0x83
			if bad & (1 << (b & 31)):
				a = -a
				b = Sim._s16(b + 2 * a)
		b &= 7
		_set_heading_word(e, b)
	a = 0xe0
	if absi(puck.yi) > 0xbb:
		a -= 0x40
	b = a
	a = Sim._s16(puck.xi + ((puck.vx * a) >> 16))
	b = Sim._s16(puck.yi + ((puck.vy * b) >> 16))
	t = _goalie_clamp_target(sim, e, a, b, b0)
	a = t.x
	b = t.y
	var d := Sim.approx_distance(a, b)
	if d >= 0x1e:
		ac = Sim._s16(d + 1)
		if absi(puck.yi) < 0x74 and Rules.count_defenders_ahead(sim):
			b4 = 0x1c if sim.action_shot else 0x14
		else:
			b4 = 0x1a if sim.action_shot else 0x12
		b = Sim._s16(_div_trunc(b * b4, ac))
		b4 += 8
		a = Sim._s16(_div_trunc(a * b4, ac))
	b = Sim._s16(b + b0)
	ac = b
	var ny := (Sim._s16(puck.vy) >> 9) + puck.yi
	if sim.puck_carrier < 0 and absi(puck.yi) < 0xe8 and absi(e.yi) > 0x74 and e.puck_dist < 0x1e and absi(ny) > absi(e.yi):
		keep = false
	var steps: int = int(pred[1]) & 0xffff
	var px: int = Sim._s16(int(pred[0]))
	if keep and steps >= 0x23:
		_goalie_tail(sim, e, a, ac, keep)
		return
	if keep and absi(px) >= 0x19:
		# a puck rimmed hard round the boards behind the net, nobody near: get it
		if sim.puck_carrier >= 0 or (sim.icing_flags & 4) or absi(puck.xi) < 0x44 or absi(puck.vy) < 0x3800 \
				or absi(puck.yi) < 0x98 or (-puck.vy if up else puck.vy) < -0x190 \
				or sim.team_record(e).nearest_dist < 0x132 or sim.opponents_of(e).nearest_dist < 0x132:
			_goalie_tail(sim, e, a, ac, keep)
			return
		e.set_state_reset(Entity.State.GOALIE_GET_PUCK)
		return
	var near := clampi(absi(px - e.xi) - 8, 0, 0x10) >> 2
	if absi(ny) > absi(e.yi):
		near += 4
	if keep and (e.puck_dist > 0x19 or absi(puck.yi) > 0xe8):
		if steps >= near + 0xc or absi(puck.yi) > 0xe9:
			# across to where the shot will cross the line
			a = px
			if absi(puck.yi) > 0xdc:
				a = 0x18 if puck.xi > 0 else -0x18
			_goalie_tail(sim, e, a, ac, keep)
			return
	# a save (loc_4c1ec)
	if sim.puck_carrier == e.slot or absi(puck.xi) >= 0x64 or puck.zi >= 0x14:
		_goalie_tail(sim, e, a, ac, keep)
		return
	e.vx = Sim._s16(e.vx) >> 1
	e.vy = Sim._s16(e.vy) >> 1
	if (e.flags3 & 2) == 0:
		a = Sim._s16((Sim._s16(puck.vx) >> 10) + puck.xi - e.xi)
		b = Sim._s16((Sim._s16(puck.vy) >> 10) + puck.yi - e.yi)
		var dd := Tables.direction8(a, b)
		b0 = 0 if dd == 8 else ((dd - _heading_word(e)) & 7)
	else:
		b0 = (Entity.to_s8(e.puck_dir) - _heading_word(e)) & 7
	if b0 == 4 and absi(puck.vy) + absi(puck.vx) <= 0x1200:
		a = 8
	else:
		if b0 == 0 or b0 == 4:
			var f := _heading_word(e)
			if f == 0:
				b0 = 7 if a < 0 else 1
			elif f == 4:
				b0 = 1 if a < 0 else 7
			elif f == 1 or f == 5:
				b0 = 7 if absi(a) < absi(b) else 1
			elif f == 3 or f == 7:
				b0 = 1 if absi(a) < absi(b) else 7
			else:
				b0 = sim.random(2)
		a = b0 >> 2
		if e.flags4 & Entity.F4_MIRROR:
			a = 1 if a == 0 else 0
		if b0 >= 4:
			b0 = 7 - b0
		if b0 >= 2 and puck.zi < 0xa and puck.vz < 0x800:
			a += 6
		elif puck.zi < 8 and puck.vz < 0x800:
			a += 4
			var hw := _heading_word(e)
			if steps >= 9 and hw != 2 and hw != 6 and sim.puck_carrier >= 0:
				a -= 2
	e.flags |= Entity.F_BUSY
	e.flags2 |= Entity.F2_TURNING
	# (the original reads the word after the index: goalie_save_anims[a + 1])
	Anim.set_animation(e, Tables.goalie_save_anims[a + 1])
	sim.add_crowd(0x96, 0x4b0)
	a = px
	if absi(puck.yi) > 0xdc:
		a = 0x18 if puck.xi > 0 else -0x18
	_goalie_tail(sim, e, a, ac, keep)

## the end of ai_goalie (loc_4c549): skate to (a, ac), standing still within 5 of it (keep)
static func _goalie_tail(sim: Sim, e: Entity, a: int, ac: int, keep: bool) -> void:
	var dx := Sim._s16(a - (e.xi + Entity.to_s8(e.vx >> 8)))
	var dy := Sim._s16(ac - (e.yi + Entity.to_s8(e.vy >> 8)))
	if keep and absi(dx) < 5 and absi(dy) < 5:
		dx = 0
		dy = 0
	var dir := Tables.direction8(dx, dy)
	e.want_dir = dir & 0xff
	sim.scratch_a = dx
	sim.scratch_b = dy
	sim.scratch_ac = (sim.scratch_ac & 0xffff0000) | (Entity.to_s8(dir) & 0xffff)
	goalie_move_dir(sim, e, Entity.to_s8(dir))

## goalie_clamp_target (0x4b6f4): in front of the goal line the point the goalie looks at is held
## inside the goal lines (and on the middle when he has the puck); then relative to the goal line
## offset b0
static func _goalie_clamp_target(sim: Sim, e: Entity, a: int, b: int, b0: int) -> Vector2i:
	if absi(e.yi) < 0xe8:
		if sim.puck_carrier == e.slot:
			a = 0
		b = clampi(b, -0xe3, 0xe3)
	return Vector2i(a, Sim._s16(b - b0))

## the word +0x36: the high word of the heading (the facing, 0..7)
static func _heading_word(e: Entity) -> int:
	return Sim._s16(e.heading >> 16)

static func _set_heading_word(e: Entity, v: int) -> void:
	e.heading = (e.heading & 0xffff) | ((v & 0xffff) << 16)

static func goalie_move_dir(sim: Sim, e: Entity, dir: int) -> void:
	if dir > 7:
		sim.brake(e)
	else:
		sim.skating_accelerate(e, dir)

## ai_goalie_get_puck (0x4b5c2): the goalie skates out for a puck rimmed behind the net until
## somebody has it, it comes back hard (0x800) or an opponent gets near (0x96)
static func goalie_get_puck(sim: Sim, e: Entity) -> void:
	if e.timer_e > 0:
		e.timer_e -= 1
	e.flags3 |= 6
	var x := e.xi
	var ay := absi(e.yi)
	if x >= -0x28 and x < 0x29 and ay >= 0xc5 and ay < 0xe4:
		e.flags3 &= ~4
	if x >= -0x30 and x < 0x31 and ay >= 0xc5:
		e.flags3 &= ~2
	if (e.flags & Entity.F_USER) or sim.play_stopped:
		default_skate(sim, e)
		return
	if Lines.handle_line_change(sim, e):
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
		if ((e.flags & Entity.F_ATTACK_UP) != 0) != (puck.vy < 0) and absi(puck.vy) > 0x800:
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

## ai_faceoff (0x4d528): the centre at the dot. His readiness (1 hunched, 2 and 3 the stick
## down, +3 for a right hander) goes to faceoff_ready for faceoff_resolve; the stick hitting the ice
## clicks. A CPU centre decides once (flags2 bit 2, cleared by the animations) when to move: a
## countdown of 0x28 (the away centre 0x14 + random 10) to the stick down (0x7f1); then with the
## drop close (0x10 steps) or one in 8, the swipe (0x7dd, busy) or, early, the anticipation (0xd05).
static func faceoff(sim: Sim, e: Entity) -> void:
	if e.flags & Entity.F_BUSY:
		return
	if not sim.faceoff_pending:
		e.timer_c = 0x14
		default_skate(sim, e)
		return
	if e.flags & Entity.F_STATE_ENTERED:
		e.flags &= ~Entity.F_STATE_ENTERED
		e.timer_a = 0
		e.frame = 0x167 if _heading_word(e) != 0 else 0x16c
		Anim.set_animation(e, 0)
		e.timer_b = sim.random(10) + 0x14 if (e.flags & Entity.F_PLAYER2) else 0x28
	var side := 1 if (e.flags & Entity.F_PLAYER2) else 0
	var ready := 1
	if e.frame == 0x169 or e.frame == 0x16e:
		ready = 2
	elif e.frame == 0x16a or e.frame == 0x16f:
		if e.anim_hold == 7:
			sim.play_sfx(0x9e + side)
		ready = 3
	if e.left_handed == 0:
		ready += 3
	sim.scratch_a = ready
	sim.faceoff_ready[side] = ready
	if e.flags & Entity.F_USER:
		return
	if e.flags2 & Entity.F2_TURNING:
		return
	e.flags2 |= Entity.F2_TURNING
	if e.timer_b < 0 and ((sim.faceoff_timer & 0xffff) <= 0x10 or sim.random(8) == 0):
		e.timer_b = -1
		if sim.faceoff_timer < 0x11:
			e.flags |= Entity.F_BUSY
			Anim.set_animation(e, 0x7dd)
		else:
			Anim.set_animation(e, 0xd05)
		return
	e.timer_b = Sim._s16(e.timer_b - 1)
	if e.timer_b < 0:
		Anim.set_animation(e, 0x7f1)

## ai_all_goto_faceoff (0x52720): after a whistle every player skates to his place at the next
## faceoff (Rules.faceoff_position; the penalty shooter just inside his half at centre ice), turns
## to the dot step by step every 8 steps and stands (timer_b = -100: arrived, all_players_arrived);
## once there he goes back to the state below (and out of a celebration or a bench wait). A player
## off the ice goes through the door.
static func all_goto_faceoff(sim: Sim, e: Entity) -> void:
	if e.line_slot < 0:
		e.set_state(Entity.State.DOOR_OPEN)
		e.timer_b = -100
		e.flags2 |= Entity.F2_UNSELECTABLE
	if e.flags & Entity.F_BUSY:
		return
	if Lines.handle_line_change(sim, e):
		return
	if e.timer_b == -100:
		default_skate(sim, e)
		var s := e.state()
		if s == Entity.State.CELEBRATE or s == Entity.State.BENCH_WAIT:
			default_skate(sim, e)
		return
	if e.flags & Entity.F_STATE_ENTERED:
		e.flags &= ~Entity.F_STATE_ENTERED
		e.want_dir = 8
		e.dir_timer = 0
		e.timer_a = 0
		var pos := Rules.faceoff_position(sim, e)
		if sim.penalty_shot_phase != 0 and e.slot == sim.penalty_shot_slot:
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
		# on the spot (the fractions of the position stay)
		e.x = (e.target_x << 16) | (e.x & 0xffff)
		e.y = (e.target_y << 16) | (e.y & 0xffff)
		e.timer_a = Sim._s16(e.timer_a - 1)
		if e.timer_a >= 0:
			return
		e.timer_a += 8
		Anim.set_animation(e, 0x99 if e.line_slot == 0 else Anim.GLIDE)
		var want := Tables.direction8(Sim._s16(sim.faceoff_x - e.xi), Sim._s16(sim.faceoff_y - e.yi))
		if e.line_slot == 0:
			if want == 2:
				want = 1 if (e.flags & Entity.F_ATTACK_UP) else 3
			elif want == 6:
				want = 7 if (e.flags & Entity.F_ATTACK_UP) else 5
		sim.scratch_ac = want
		var hw := _heading_word(e)
		if want != hw:
			var rel := (want - hw) & 7
			sim.scratch_ac = rel
			_set_heading_word(e, (hw + (1 if rel < 5 else -1)) & 7)
			return
		e.vy = 0
		e.vx = 0
		e.timer_b = -100
		return
	sim.scratch_a = e.target_x
	sim.scratch_b = e.target_y
	if d2 < 0x190:
		ref_skate_to_point(sim, e, e.target_x, e.target_y)
	else:
		skate_towards(sim, e, e.target_x, e.target_y)

## ai_init_period (0x526ed): the players wait off the ice until handle_line_change puts them on
## (then 100 steps to come on)
static func init_period(sim: Sim, e: Entity) -> void:
	if e.flags & Entity.F_BUSY:
		return
	e.frame = -1
	if Lines.handle_line_change(sim, e):
		e.timer_a = 0x64
		e.timer_b = 0

## ai_puck_normal (0x4d8c7)
static func puck_normal(sim: Sim, e: Entity) -> void:
	if e.flags & Entity.F_STATE_ENTERED:
		e.flags &= ~Entity.F_STATE_ENTERED
		sim.puck_goal_timer = 0
		sim.puck_stuck_timer = 0x78
		sim.penalty_shot_away = 0
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
					if sim.line_hotkey_req[t] != 0:
						var slot := sim.user1_slot if sim.user1_team == t + 1 else sim.user2_slot
						if slot >= 0:
							Lines.request_line_change(sim, sim.entities[slot], sim.line_hotkey[t])
						sim.line_hotkey_req[t] = 0
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
			sim.faceoff_digit = 10 - t

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

## ai_game_misconduct (0x4ab87): the player is thrown out: he skates to the bench door, turns to
## it and steps off; the lines are rebuilt without him (pick_player_for_position)
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
			sim.switch_to_nearest(e, 0 if e.slot == sim.user1_slot else 2)
		e.want_dir = 8
		e.dir_timer = 0
		e.target_y = 0x24 if (e.flags & Entity.F_PLAYER2) else -0x1c
		e.target_x = -0xa8
		e.timer_a = 0
		e.flags2 |= Entity.F2_NO_COLLIDE
		e.push_x = 0
		e.push_y = 0
	e.timer_a = Entity.to_s16(e.timer_a - 1)
	if e.timer_a < 0:
		e.timer_a += 8
		var dy := Entity.to_s16(e.yi - e.target_y)
		sim.scratch_a = Entity.to_s16(e.xi - e.target_x)
		if absi(dy) <= 0x14 and sim.scratch_a <= 0x20:
			sim.scratch_b = 1 if e.line_slot == 0 else Anim.GLIDE
			Anim.set_animation(e, sim.scratch_b)
			e.flags |= Entity.F_ARRIVED
			if e.facing != 4:
				e.facing = (e.facing + (1 if e.facing < 4 else -1)) & 7
			e.vy = 0
			e.vx = -0x800
			if sim.scratch_a > 0x10:
				return
			e.vx = 0
			if e.facing != 4:
				return
			e.vx = -0x800
			e.facing = 2
			Anim.set_animation(e, 0xd2d if e.line_slot == 0 else 0x7bf)
			e.flags |= Entity.F_BUSY
			e.timer_a = 100
			if sim.period < 4 and not sim.game_over:
				sim.pick_player_for_position(1 if e.flags & Entity.F_PLAYER2 else 0, e.roster_idx)
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
	if e.flags & Entity.F_STATE_ENTERED:
		e.flags &= ~Entity.F_STATE_ENTERED
		e.flags2 |= Entity.F2_UNSELECTABLE
		if e.flags & Entity.F_USER:
			# the user takes the team mate nearest to the puck
			sim.switch_to_nearest(e, 0 if e.slot == sim.user1_slot else 2)
		e.want_dir = 8
		e.dir_timer = 0
		# the next free seat: the players already sitting in the box (penalized_count)
		var away := (e.flags & Entity.F_PLAYER2) != 0
		var seat := Entity.to_s8(sim.box_count[1 if away else 0]) & 0xf
		if seat > 2:
			seat = 2
		e.target_y = Sim._s16((seat + 3) * (0xb if away else -0xb))
		e.target_x = 0xa0
		e.timer_a = 0
		e.flags2 |= Entity.F2_NO_COLLIDE
		e.push_x = 0
		e.push_y = 0
	var dx := Sim._s16(e.xi - e.target_x)
	if absi(Sim._s16(e.yi - e.target_y)) > 0xc or dx < -0x18:
		skate_towards(sim, e, e.target_x, e.target_y)
		return
	e.timer_a = Sim._s16(e.timer_a - 1)
	if e.timer_a >= 0:
		return
	e.timer_a += 8
	e.flags |= Entity.F_ARRIVED
	Anim.set_animation(e, Anim.GLIDE)
	var cmp := 4
	var hw := _heading_word(e)
	if cmp != hw:
		cmp = (cmp - hw) & 7
		_set_heading_word(e, (hw + (1 if cmp < 5 else -1)) & 7)
	sim.scratch_ac = cmp
	e.vy = 0
	e.vx = 0x1000
	if dx < -8:
		return
	e.vx = 0
	if cmp != _heading_word(e):
		return
	# over the boards into the box
	e.flags |= Entity.F_BUSY
	_set_heading_word(e, 2)
	Anim.set_animation(e, 0x7a1)
	e.flags2 &= ~Entity.F2_PENALIZED
	var team := sim.team_record(e)
	if team.skaters_on_ice > 4:
		team.skaters_on_ice -= 1
	e.set_state(Entity.State.DOOR_OPEN)

## ai_door_open (0x4affb): in the box: off the ice until the penalty expires
static func door_open(sim: Sim, e: Entity) -> void:
	if e.flags & Entity.F_BUSY:
		return
	# counted among the players in the box (penalty_box_update counts them afresh every step)
	var t := 1 if (e.flags & Entity.F_PLAYER2) else 0
	sim.box_count[t] = (sim.box_count[t] + 1) & 0xff
	e.line_slot = (e.line_slot & 0xff) | ~0xff      # high byte 0xff: hidden, still a skater slot
	e.frame = -1

## ai_exit_penalty_box (0x4b02d): steps back onto the ice next to the box
static func exit_penalty_box(sim: Sim, e: Entity) -> void:
	if e.flags & Entity.F_BUSY:
		return
	if e.flags & Entity.F_STATE_ENTERED:
		e.flags = (e.flags | Entity.F_ARRIVED) & ~(Entity.F_STATE_ENTERED | Entity.F_BACKWARDS)
		e.flags2 |= Entity.F2_UNSELECTABLE
		# stands up at his seat in the box (the count of the players still sitting there)
		var t := 1 if (e.flags & Entity.F_PLAYER2) else 0
		sim.box_count[t] = (sim.box_count[t] - 1) & 0xff
		var seat := Entity.to_s8(sim.box_count[t])
		if seat > 2:
			seat = 2
		e.y = ((0x21 + 11 * seat if t == 1 else -0x21 - 11 * seat) << 16) | (e.y & 0xffff)
		e.vx = 0
		e.vy = 0
		e.x = (0x9e << 16) | (e.x & 0xffff)
		_set_heading_word(e, 2)
		e.flags |= Entity.F_BUSY
		Anim.set_animation(e, 0x7bf)
		sim.sort_draw_order()
		return
	_set_heading_word(e, 4)
	e.next_roster = -1
	e.next_line_slot = -1
	e.flags &= ~(Entity.F_ARRIVED | Entity.F_USER)
	e.flags2 &= ~(Entity.F2_UNSELECTABLE | Entity.F2_NO_COLLIDE)
	e.vx = -0x1000
	default_skate(sim, e)

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

## ai_ref_call_penalty (0x4eb04): for a call with a signal the referee skates to the side (0xa0, 0),
## turns step by step to the signal's direction and signals it (busy); a goal (7) is announced
## (announce_goal: the team the puck is in the net of, the last three carriers); then REF_PICKUP.
## (After a turn the original compares the size of the turn with the new heading, so now and then
## the signal comes a step early.)
static func ref_call_penalty(sim: Sim, e: Entity) -> void:
	if e.flags & Entity.F_BUSY:
		return
	var inf := sim.ref_infraction
	if e.flags & Entity.F_STATE_ENTERED:
		e.flags &= ~Entity.F_STATE_ENTERED
		if Tables.ref_signal_dir[inf] < 0:
			if inf == Rules.INF_GOAL:
				var t := 1 if (sim.puck.yi < 0) != sim.ends_switched else 0
				var team := sim.teams[t]
				var a1: int = team.carrier_history[1] if team.carrier_history[1] >= 0 else -1
				var a2: int = team.carrier_history[2] if team.carrier_history[2] >= 0 else -1
				InfoPanel.announce_goal(sim, t, team.carrier_history[0], a1, a2)
			e.set_state(Entity.State.REF_PICKUP)
			return
		e.want_dir = 8
		e.dir_timer = 0
		e.target_y = 0
		e.target_x = 0xa0
		e.timer_a = 0
		e.flags2 |= Entity.F2_NO_COLLIDE
		e.push_x = 0
		e.push_y = 0
	if absi(Sim._s16(e.yi - e.target_y)) > 0xc or Sim._s16(e.xi - e.target_x) < -0x14:
		ref_skate_to_point(sim, e, e.target_x, e.target_y)
		return
	e.timer_a = Sim._s16(e.timer_a - 1)
	if e.timer_a >= 0:
		return
	e.timer_a += 8
	Anim.set_animation(e, Anim.REF_GLIDE)
	var cmp: int = Tables.ref_signal_dir[inf]
	var hw := _heading_word(e)
	if cmp != hw:
		cmp = (cmp - hw) & 7
		_set_heading_word(e, (hw + (1 if cmp < 5 else -1)) & 7)
	sim.scratch_ac = (sim.scratch_ac & 0xffff0000) | (cmp & 0xffff)
	e.vy = 0
	e.vx = 0
	if cmp != _heading_word(e):
		return
	e.flags |= Entity.F_BUSY
	# (the original reads a dword and keeps its high word: the entry after the call's)
	Anim.set_animation(e, Tables.ref_signal_anim[inf + 1])
	e.set_state(Entity.State.REF_PICKUP)

## ai_ref_pickup_puck (0x4ed7c): the referee picks the puck up after the whistle. While the
## panel opens with a clip (not the fans' or the clapping) he waits, and once it is up says the
## goal; with more calls queued he signals them (ref_phase -1); a puck out of the rink: a new one
## (REF_GET_NEW_PUCK). On entering: after an injury, at 0:00 or a decided overtime straight to the
## faceoff; else everybody to the faceoff (all_goto_positions) and, by the call: a goalie's frozen
## puck queues its event or shows the SAVED clip, a goal checks the milestones, the others bring the
## announcements. Then he skates to the puck (leading it, stopping short of the goal line in
## front of a net, at the net's mouth for a puck in the net), turns to it and picks it up (carrier
## 16, held up out of sight); after 0x258 steps he takes a new one.
static func ref_pickup(sim: Sim, e: Entity) -> void:
	if e.flags & Entity.F_BUSY:
		return
	var puck := sim.puck
	if sim.clip != InfoPanel.CLIP_CLAP and sim.clip != InfoPanel.CLIP_FAN_ANTHEM and sim.panel >= 0 and sim.panel < InfoPanel.HELD:
		Anim.set_animation(e, Anim.REF_GLIDE)
		if sim.panel < 0xec or sim.goal_call.is_empty():
			return
		var g: Array = sim.goal_call
		if not sim.stubbed("say_goal", [int(g[0]) & 0xff, int(g[1]) & 0xff, int(g[2]) & 0xff, int(g[3]) & 0xff]):
			var assists: Array = []
			for k in [2, 3]:
				if g[k] >= 0:
					assists.append(Speech.number(sim, g[0], g[k]))
			Speech.say(sim, Speech.goal(Speech.abbrev(sim, g[0]), Speech.number(sim, g[0], g[1]), assists))
		sim.goal_call = []
		if sim.period >= 3:
			sim.panel = 0x38
		return
	if not sim.infractions.is_empty():
		Anim.set_animation(e, Anim.REF_GLIDE)
		sim.ref_phase = -1
		return
	if absi(puck.xi) > 0xa0 or absi(puck.yi) > 0x112:
		e.set_state(Entity.State.REF_GET_NEW_PUCK)
		return
	if e.flags & Entity.F_STATE_ENTERED:
		if sim.injury_stoppage or (sim.clock_seconds == 0 and sim.clock_sub == 0) \
				or (sim.period == 3 and sim.teams[0].goals != sim.teams[1].goals):
			sim.ref_phase = -1
			if sim.panel == InfoPanel.HELD:
				sim.panel = InfoPanel.CLOSING
			puck.set_state(Entity.State.PUCK_FACEOFF)
			e.set_state(Entity.State.REF_FACEOFF)
			return
		sim.ref_phase = 1
		e.flags &= ~Entity.F_STATE_ENTERED
		Rules.all_goto_positions(sim)
		e.want_dir = 8
		e.dir_timer = 0
		e.timer_a = 0
		e.timer_b = 0
		e.flags2 |= Entity.F2_NO_COLLIDE
		e.push_x = 0
		e.push_y = 0
		Anim.set_animation(e, Anim.REF_GLIDE)
		var inf := sim.ref_infraction
		var announce := true
		if inf == Rules.INF_GOALIE_HOLD:
			if Rules.ref_queue_infraction_event(sim):
				announce = false
			elif sim.ref_infraction_slot >= 0 and sim.entities[sim.ref_infraction_slot].save_result != 0 and not sim.save_clip_shown:
				sim.entities[sim.ref_infraction_slot].save_result = 0
				announce = false
				InfoPanel.load_clip(sim, InfoPanel.CLIP_SAVE)
				if sim.clip != -1:
					sim.save_clip_shown = true      # once a period
					InfoPanel.open(sim)
					return
		elif inf == Rules.INF_GOAL:
			if sim.no_stats:
				sim.period_over = true
				return
			Rules.goal_milestone_check(sim)
			announce = false
		if announce and InfoPanel.ref_announcements(sim):
			return
		if sim.panel == InfoPanel.HELD:
			sim.panel = InfoPanel.CLOSING
	if sim.deferred:
		return
	if sim.puck_carrier >= 0:
		sim.puck_carrier = -1
		puck.set_state(Entity.State.PUCK_IDLE)
	if e.timer_b > 0x258:
		# took too long: a new puck
		sim.puck_carrier = Entity.Slot.REFEREE
		puck.vx = 0
		puck.vy = 0
		puck.vz = 0
		puck.z = (100 << 16) | (puck.z & 0xffff)
		e.set_state(Entity.State.REF_GOTO_FACEOFF)
		return
	var a: int
	var b: int
	var in_net := absi(puck.xi) == 6 and absi(puck.yi) == 0xf0
	if in_net:
		e.target_x = puck.xi
		e.target_y = -0xe3 if puck.yi < 0 else 0xe3
		a = Sim._s16(e.xi - e.target_x)
		b = Sim._s16(e.yi - (-0xee if puck.yi < 0 else 0xee))
	else:
		e.target_x = Sim._s16(puck.xi + (Sim._s16(puck.vx) >> 7))
		e.target_y = Sim._s16(puck.yi + (Sim._s16(puck.vy) >> 7))
		var dv := Tables.direction8(Sim._s16(puck.vx), Sim._s16(puck.vy))
		var dp := Tables.direction8(Sim._s16(e.xi - puck.xi), Sim._s16(e.yi - puck.yi))
		if dv > 7 or dp > 7 or dp == dv:
			e.target_x = puck.xi
			e.target_y = puck.yi
		# not across a goal line: where the way to the lead crosses it, stay with the puck
		for gl: int in [0xe8, -0xe8]:
			var ty := e.target_y
			if ((ty - gl) ^ (puck.yi - gl)) < 0:
				var c: int = (gl - puck.yi) * (e.target_x - puck.xi)
				if ty - puck.yi != 0:
					c = _div_trunc(c, ty - puck.yi)
				if absi(Sim._s16(puck.xi + c)) < 0x19:
					e.target_x = puck.xi
					e.target_y = puck.yi
		a = Sim._s16(e.xi - puck.xi)
		b = Sim._s16(e.yi - puck.yi)
	sim.scratch_b = b
	var close := absi(a) <= 0xc and absi(b) <= 0xc and not (in_net and absi(e.yi) > 0xe8)
	if close:
		e.timer_a = Sim._s16(e.timer_a - 1)
		if e.timer_a >= 0:
			return
		e.timer_a += 8
		Anim.set_animation(e, Anim.REF_GLIDE)
		var want := Tables.direction8(Sim._s16(puck.xi - e.xi), Sim._s16(puck.yi - e.yi))
		sim.scratch_ac = want
		var hw := _heading_word(e)
		if want >= 8 or ((want - hw + 1) & 7) <= 2:
			e.vy = 0
			e.vx = 0
			sim.puck_carrier = Entity.Slot.REFEREE
			puck.vx = 0
			puck.vy = 0
			puck.vz = 0
			puck.z = (-100 * 0x10000) | (puck.z & 0xffff)
			if want < 8:
				_set_heading_word(e, want)
			e.flags |= Entity.F_BUSY
			Anim.set_animation(e, 0xc03)        # picks the puck up
			e.set_state(Entity.State.REF_GOTO_FACEOFF)
			return
		var rel := (want - hw) & 7
		sim.scratch_ac = rel
		_set_heading_word(e, (hw + (1 if rel < 5 else -1)) & 7)
	e.timer_b = Sim._s16(e.timer_b + 1)
	ref_skate_to_point(sim, e, e.target_x, e.target_y)

## ai_ref_goto_faceoff (0x4f5bf): the referee takes the puck (carrier 16, held up out of sight)
## to the faceoff dot, stands beside it (0xf towards the middle) and turns to face it every 8
## steps; once the announcer is quiet and no clip plays he drops it (ref_phase -1, REF_FACEOFF).
## During a penalty shot: REF_PENALTY_SHOT.
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
		e.dir_timer = 0
		e.timer_a = 0
		e.target_x = Sim._s16(sim.faceoff_x + (-0xf if sim.faceoff_x <= 0 else 0xf))
		e.target_y = sim.faceoff_y
		e.flags2 |= Entity.F2_NO_COLLIDE
		e.push_x = 0
		e.push_y = 0
		sim.puck_carrier = Entity.Slot.REFEREE
		puck.vx = 0
		puck.vy = 0
		puck.vz = 0
		puck.z = (-100 * 0x10000) | (puck.z & 0xffff)
		Anim.set_animation(e, Anim.REF_GLIDE)
	var dx := e.xi - e.target_x
	var dy := e.yi - e.target_y
	if dx * dx + dy * dy < 0x40 and absi(e.vx) < 0x10 and absi(e.vy) < 0x10:
		e.x = (e.target_x << 16) | (e.x & 0xffff)
		e.y = (e.target_y << 16) | (e.y & 0xffff)
		e.timer_a = Sim._s16(e.timer_a - 1)
		if e.timer_a >= 0:
			return
		e.timer_a += 8
		Anim.set_animation(e, Anim.REF_GLIDE)
		var want := 2 if sim.faceoff_x <= 0 else 6
		sim.scratch_ac = want
		var hw := _heading_word(e)
		if want != hw:
			var rel := (want - hw) & 7
			sim.scratch_ac = rel
			_set_heading_word(e, (hw + (1 if rel < 5 else -1)) & 7)
			return
		e.vy = 0
		e.vx = 0
		if sim.speech_busy or sim.clip != -1:
			return
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
		e.dir_timer = 0
		e.timer_a = 0
		e.target_y = -0xe6 if sim.puck.yi <= 0 else 0xe6
		e.target_x = -0x32 if e.xi <= 0 else 0x32
		e.flags2 |= Entity.F2_NO_COLLIDE
		e.push_x = 0
		e.push_y = 0
	if absi(Sim._s16(e.yi - e.target_y)) <= 0xc and absi(e.yi) <= absi(e.target_y) and absi(Sim._s16(e.xi - e.target_x)) <= 0xc:
		e.timer_a = Sim._s16(e.timer_a - 1)
		if e.timer_a >= 0:
			return
		e.timer_a += 8
		Anim.set_animation(e, Anim.REF_GLIDE)
		var want := Tables.direction8(Sim._s16(-e.xi), Sim._s16(e.target_y - e.yi))
		sim.scratch_ac = want
		var hw := _heading_word(e)
		if want != hw:
			var rel := (want - hw) & 7
			sim.scratch_ac = rel
			_set_heading_word(e, (hw + (1 if rel < 5 else -1)) & 7)
			return
		e.vx = 0
		e.vy = 0
		e.flags |= Entity.F_BUSY
		Anim.set_animation(e, 0xc1b)       # points at the goal
		e.set_state(Entity.State.REF_CALL_PENALTY)
		return
	ref_skate_to_point(sim, e, e.target_x, e.target_y)

## ai_ref_get_new_puck (0x4e8ef): after a routine stoppage the referee sends everybody to their
## places (all_goto_positions), skates to the side (0xa0, 0) for a new puck, faces it and holds
## it up (busy), then REF_GOTO_FACEOFF; the stoppage may bring an announcement or a crowd clip
## (ref_check_announcements). After an injury, at 0:00 or once overtime is decided the faceoff
## follows at once (the open panel starts to close).
static func ref_get_new_puck(sim: Sim, e: Entity) -> void:
	if e.flags & Entity.F_BUSY:
		return
	if e.flags & Entity.F_STATE_ENTERED:
		if sim.injury_stoppage or (sim.clock_seconds == 0 and sim.clock_sub == 0) \
				or (sim.period == 3 and sim.teams[0].goals != sim.teams[1].goals):
			sim.ref_phase = -1
			if sim.panel == InfoPanel.HELD:
				sim.panel = InfoPanel.CLOSING
			sim.puck.set_state(Entity.State.PUCK_FACEOFF)
			e.set_state(Entity.State.REF_FACEOFF)
			return
		sim.ref_phase = 1
		e.flags &= ~Entity.F_STATE_ENTERED
		Rules.all_goto_positions(sim)
		e.want_dir = 8
		e.dir_timer = 0
		e.target_y = 0
		e.target_x = 0xa0
		e.timer_a = 0
		e.flags2 |= Entity.F2_NO_COLLIDE
		e.push_x = 0
		e.push_y = 0
		Anim.set_animation(e, Anim.REF_GLIDE)
		if InfoPanel.ref_announcements(sim):
			return
		if sim.panel == InfoPanel.HELD:
			sim.panel = InfoPanel.CLOSING
	if absi(Sim._s16(e.yi - e.target_y)) > 6 or Sim._s16(e.xi - e.target_x) < -0xa:
		ref_skate_to_point(sim, e, e.target_x, e.target_y)
		return
	e.timer_a = Sim._s16(e.timer_a - 1)
	if e.timer_a >= 0:
		return
	e.timer_a += 8
	Anim.set_animation(e, Anim.REF_GLIDE)
	var cmp := 2
	var hw := _heading_word(e)
	if cmp != hw:
		cmp = (cmp - hw) & 7
		_set_heading_word(e, (hw + (1 if cmp < 5 else -1)) & 7)
	sim.scratch_ac = cmp
	e.vy = 0
	e.vx = 0
	if cmp != _heading_word(e):
		return
	e.flags |= Entity.F_BUSY
	Anim.set_animation(e, 0xc1b)
	e.set_state(Entity.State.REF_GOTO_FACEOFF)
