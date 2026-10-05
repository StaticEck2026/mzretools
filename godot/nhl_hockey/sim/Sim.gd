class_name Sim
extends RefCounted
## The simulation: 17 entities stepped at a fixed 60 Hz like sim_tick/sim_update_players of the
## original. What is ported here is the deterministic core: integration, friction, gravity, board
## collisions with rounded corners, skating control (apply_skating & co), animation stepping,
## a simple puck carry/pass/shot and the camera. The 47 AI state handlers, line changes, rules
## (offside, icing, penalties) and the net/goal detection are not ported yet; CPU players stand
## still (see godot/nhl_hockey/README.md).

const STEP_DT := 16                 # position += 16 * velocity per step (dword_e03b2 >> 16)
const GRAVITY := 6 * 16
const RINK_HALF_W := 160            # boards: x = ±160
const RINK_HALF_H := 264            # boards: y = ±264
const CORNER_RADIUS := 64
const GOAL_LINE_Y := 232            # puck beyond ±232 = behind the goal line (predict_puck_goal_line)
const MAX_SPEED := 16000

var entities: Array[Entity] = []
var puck: Entity
var referee: Entity
var puck_carrier: int = -1
var user1_slot: int = -1
var user2_slot: int = -1
var camera_x: int = 0
var camera_y: int = 0
var play_stopped: bool = false
var ends_switched: bool = false
var step_count: int = 0
var sfx_queue: PackedInt32Array = PackedInt32Array()
var rng := RandomNumberGenerator.new()
var pending_pass_dir: int = -1
var pending_shot_dir: int = -1
var shot_power: int = 0

func _init() -> void:
	rng.seed = 0x4e484c
	for i in 17:
		var e := Entity.new()
		e.slot = i
		e.team = 0 if i < 6 else 1
		if i >= 6 and i < 12:
			e.flags |= Entity.F_ATTACK_DOWN
		entities.append(e)
	puck = entities[Entity.Slot.PUCK]
	referee = entities[Entity.Slot.REFEREE]
	puck.half_w = 1
	puck.half_h = 1
	setup_faceoff()

## Default positions for a centre ice faceoff (setup_faceoff is not ported; these are the
## classic positions: C at the dot, wingers at the circle, D at the blue line, G in the crease)
func setup_faceoff() -> void:
	var spots := [[0, 0, 0], [40, 0, 1], [-40, 0, 2], [60, 60, 3], [-60, 60, 4], [0, 215, 0]]
	for t in 2:
		var sign := -1 if t == 0 else 1
		for i in 6:
			var e := entities[t * 6 + i]
			var s: Array = spots[i]
			var yy: int = s[1] + (12 if i == 0 else 0)
			e.set_pos(s[0], sign * yy)
			e.line_slot = 1 + i if i < 5 else 0
			e.heading = (0 if sign == -1 else 4) << 16
			e.vx = 0
			e.vy = 0
			e.z = 0
			e.vz = 0
			e.roster_idx = i if i < 5 else 25
			Anim.set_animation(e, Anim.GOALIE_IDLE if e.line_slot == 0 else Anim.GLIDE)
	puck.set_pos(0, 0)
	puck.z = 0
	puck.vx = 0
	puck.vy = 0
	puck.vz = 0
	puck.line_slot = 1
	referee.set_pos(-30, 0)
	referee.line_slot = 1
	Anim.set_animation(referee, Anim.REF_GLIDE)
	puck_carrier = -1
	camera_x = 0
	camera_y = 0

# --------------------------------------------------------------------------------------------
# main step (sim_tick -> sim_update_players, update_camera)
# --------------------------------------------------------------------------------------------

## control_p1/control_p2: control bytes (bits 0-3 direction, 8 none, 0x10 A, 0x20 B, 0x40 C)
func step(control_p1: int, control_p2: int, pressed_p1: int, pressed_p2: int) -> void:
	step_count += 1
	update_puck_distances()
	for e in entities:
		if not e.on_ice() and e.slot != Entity.Slot.PUCK:
			continue
		e.prev_x = e.x
		e.prev_y = e.y
		e.prev_z = e.z
		Anim.advance(e)
		e.timer_c = maxi(0, e.timer_c - 1)
		e.timer_d = maxi(0, e.timer_d - 1)
		integrate(e)
		if e.slot == user1_slot:
			control_player(e, control_p1, pressed_p1, 0)
		elif e.slot == user2_slot:
			control_player(e, control_p2, pressed_p2, 1)
		elif e.slot == Entity.Slot.PUCK:
			puck_update()
		else:
			ai_placeholder(e)
		e.push_x = 0
		e.push_y = 0
		if e.xi != e.prev_x >> 16 or e.yi != e.prev_y >> 16 or e.slot == Entity.Slot.PUCK:
			move_entity(e)
		e.speed = maxi(0, e.speed - 2)
		e.speed_prev = e.speed
	resolve_puck_carry()
	update_camera()

func update_puck_distances() -> void:
	for i in 12:
		var e := entities[i]
		var dx := puck.xi - e.xi
		var dy := puck.yi - e.yi
		e.puck_dist = approx_distance(dx, dy)
		e.puck_dir = Tables.direction8(dx, dy)
		var qx := dx >> 2
		var qy := dy >> 2
		e.puck_dist_sq = qx * qx + qy * qy

## friction, speed clamp, gravity and the position update of sim_update_players
func integrate(e: Entity) -> void:
	if e.anim == 0xa0b or (e.anim >= 0xf0f and e.anim <= 0x1055):
		return    # falling / lying animations move the entity through frame_offsets instead
	if e.zi == 0:
		var shift := 9 if (e.flags & 1) else 6
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
	if e.zi >= 0 and (e.zi != 0 or e.vz != 0):
		e.vz -= GRAVITY
		var nz := e.z + STEP_DT * e.vz
		if nz < 0:
			e.z = 0
			e.vz = (-e.vz) >> 1
			if 5 - e.flags3 < 4:
				sfx_queue.append(0xab)   # puck drop
		else:
			e.z = nz

## stand-in for the AI state handlers: CPU players glide and slowly stop
func ai_placeholder(e: Entity) -> void:
	if e.slot >= 12 and e.slot != Entity.Slot.REFEREE:
		return
	if e.anim == 0:
		Anim.set_animation(e, Anim.GOALIE_IDLE if e.is_goalie() else Anim.GLIDE)

# --------------------------------------------------------------------------------------------
# controls (control_player, apply_skating, skating_turn, skating_accelerate, stop_skating, brake)
# --------------------------------------------------------------------------------------------

func control_player(e: Entity, control: int, pressed: int, player: int) -> void:
	e.flags |= Entity.F_USER
	if player == 1:
		e.flags |= Entity.F_PLAYER2
	var carrying := puck_carrier == e.slot
	if pressed & 0x10:
		if carrying:
			pending_pass_dir = control & 0xf
			do_pass(e)
		else:
			switch_to_nearest(player)
			return
	elif pressed & 0x20:
		if carrying:
			start_shot(e)
		else:
			body_check(e)
	if e.flags & Entity.F_BUSY:
		return
	apply_skating(e, control & 0xf)

func apply_skating(e: Entity, dir: int) -> void:
	# animation without movement input: glide (one frame per direction)
	var idle_anim := Anim.GLIDE
	if e.flags & Entity.F_BACKWARDS:
		idle_anim = Anim.GLIDE_BACK
	elif e.slot == Entity.Slot.REFEREE:
		idle_anim = Anim.REF_GLIDE
	if dir >= 8:
		if dir == 9 and (e.vx != 0 or e.vy != 0):
			stop_skating(e)
			return
		if (e.flags2 & Entity.F2_TURNING) == 0:
			Anim.set_animation(e, idle_anim)
		return
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
				Anim.set_animation(e, Anim.REF_TURN_R if right else Anim.REF_TURN_L)
			else:
				Anim.set_animation(e, Anim.TURN_R if right else Anim.TURN_L)
			e.flags2 |= Entity.F2_TURNING
		else:
			Anim.set_animation(e, idle_anim)
		if sp > 2:
			skating_accelerate(e, e.facing)
		return
	skating_turn(e, turn, e.facing)

func skating_turn(e: Entity, turn: int, heading_dir: int) -> void:
	if turn != 0:
		# only reached with a non zero turn whose table entry is 0 (never in the data)
		stop_skating(e)
		return
	var a := Anim.SKATE
	if e.flags & Entity.F_BACKWARDS:
		a = Anim.SKATE_BACK
	elif e.slot == Entity.Slot.REFEREE:
		a = Anim.REF_SKATE
	elif puck_carrier == e.slot:
		a = Anim.SKATE_CARRIER
	elif e.flags2 & Entity.F2_HOOKED:
		a = Anim.SKATE_HOOKED
	if (e.flags2 & Entity.F2_TURNING) == 0:
		Anim.set_animation(e, a)
	skating_accelerate(e, heading_dir)

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
	var level: int
	if e.slot == Entity.Slot.REFEREE:
		level = 15
	else:
		level = (e.stamina * e.energy) >> 12
	level = clampi(level, 0, 15)
	var limit := Tables.max_speed_sq[level]
	if e.flags2 & Entity.F2_HOOKED:
		limit >>= 3
	if sp2 <= limit:
		e.vx = nvx
		e.vy = nvy
	e.speed = 20

func stop_skating(e: Entity) -> void:
	if absi(e.vx) > 0x1000 or absi(e.vy) > 0x1000:
		if (e.flags & Entity.F_BACKWARDS) == 0:
			e.flags2 |= Entity.F2_TURNING
			Anim.set_animation(e, Anim.REF_STOP if e.slot == Entity.Slot.REFEREE else Anim.STOP)
		else:
			Anim.set_animation(e, Anim.REF_GLIDE if e.slot == Entity.Slot.REFEREE else Anim.GLIDE)
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

func switch_to_nearest(player: int) -> void:
	var team := 0 if player == 0 else 1
	var best := -1
	var best_d := 0x7fffffff
	var cur := user1_slot if player == 0 else user2_slot
	for i in 6:
		var e := entities[team * 6 + i]
		if e.line_slot <= 0 or e.slot == cur:
			continue
		var dx := puck.xi + (puck.vx >> 8) - e.xi
		var dy := puck.yi + (puck.vy >> 8) - e.yi
		var d := dx * dx + dy * dy
		if d < best_d:
			best_d = d
			best = e.slot
	if best >= 0:
		if cur >= 0:
			entities[cur].flags &= ~(Entity.F_USER | Entity.F_PLAYER2)
		if player == 0:
			user1_slot = best
		else:
			user2_slot = best

# --------------------------------------------------------------------------------------------
# puck (simplified: carry, pass, shot, pickup)
# --------------------------------------------------------------------------------------------

func puck_update() -> void:
	if puck_carrier >= 0:
		var c := entities[puck_carrier]
		var fo: Array = Tables.frame_offsets[c.frame] if c.frame < Tables.frame_offsets.size() else [0, 0]
		var ox: int = fo[0]
		if c.flags4 & Entity.F4_MIRROR:
			ox = -ox
		# update_carrier: the puck eases towards the stick position
		var tx := c.xi + ox
		var oy: int = fo[1]
		var ty: int = c.yi + oy
		puck.x = (puck.xi + ((tx - puck.xi) >> 2)) << 16
		puck.y = (puck.yi + ((ty - puck.yi) >> 2)) << 16
		puck.vx = c.vx
		puck.vy = c.vy
		puck.z = 0
		puck.vz = 0

func resolve_puck_carry() -> void:
	if puck_carrier >= 0:
		return
	if puck.zi > 3:
		return
	for i in 12:
		var e := entities[i]
		if e.line_slot < 0 or e.timer_c > 0:
			continue
		var dx := puck.xi - e.xi
		var dy := puck.yi - e.yi
		if absi(dx) < 8 and absi(dy) < 8:
			puck_carrier = e.slot
			return

func do_pass(e: Entity) -> void:
	# do_pass: receiver search is simplified to "pass in the pushed direction"
	var dir := pending_pass_dir if pending_pass_dir < 8 else e.facing
	var power := e.pass_skill * 4 + 0xa0
	var v: Array = Tables.dir8_vectors[dir]
	puck_carrier = -1
	e.timer_c = 0x10
	puck.vx = (v[0] * power * 0x400) / 3000 + e.vx
	puck.vy = (v[1] * power * 0x400) / 3000 + e.vy
	e.flags |= Entity.F_BUSY
	Anim.set_animation(e, 0x4e9)
	pending_pass_dir = -1

func start_shot(e: Entity) -> void:
	# start_shot/do_shot: aim at the opponent's net, power from the shooting skill
	var target_y := 0xf0 if (e.flags & Entity.F_ATTACK_DOWN) == 0 else -0xf0
	var dir := Tables.direction8(-e.xi, target_y - e.yi)
	var backhand := shot_is_backhand(e, dir)
	Anim.set_animation(e, Anim.SHOT_BACKHAND if backhand else Anim.SHOT_FOREHAND)
	e.flags |= Entity.F_BUSY
	var power := 0xaa + (e.shot_skill << 3)
	if backhand:
		power -= power >> 2
	var dx := -e.xi
	var dy := target_y - e.yi
	var d := maxi(1, approx_distance(dx, dy))
	puck_carrier = -1
	e.timer_c = 0x10
	puck.vx = dx * power * 16 / d
	puck.vy = dy * power * 16 / d
	puck.vz = rng.randi_range(0, 0x300)
	sfx_queue.append(0x9a)

func shot_is_backhand(e: Entity, dir: int) -> bool:
	var rel := (e.facing - dir) & 7
	var mask := 0xf0 if (e.flags4 & Entity.F4_MIRROR) else 0x1e
	return ((1 << rel) & mask) != 0

func body_check(e: Entity) -> void:
	# body_check: velocity burst in the heading direction, costs energy, animation 0x621
	var en := e.energy
	en = maxi(0, en - 0xcc)
	e.energy = en
	var burst := en >> 7
	var v: Array = Tables.dir8_vectors[e.facing]
	e.vx += v[0] * burst
	e.vy += v[1] * burst
	e.flags |= Entity.F_BUSY
	Anim.set_animation(e, Anim.BODY_CHECK)

# --------------------------------------------------------------------------------------------
# boards (move_entity -> collide_boards -> collide_corner -> bounce_off_boards)
# --------------------------------------------------------------------------------------------

func move_entity(e: Entity) -> void:
	if e.slot >= 12 and e.slot != Entity.Slot.PUCK and e.slot != Entity.Slot.REFEREE:
		return
	collide_boards(e, e.xi, e.yi)

func collide_boards(e: Entity, px: int, py: int) -> void:
	var w := RINK_HALF_W - e.half_w
	var h := RINK_HALF_H - e.half_h
	var cw := w - CORNER_RADIUS
	var ch := h - CORNER_RADIUS
	var a := 0   # board normal, a = ny * 256, b = -nx * 256 (see bounce_off_boards)
	var b := 0
	if absi(py) >= ch:
		if absi(px) >= cw:
			# corner: push away from the corner centre when outside the rounded corner
			var cx := cw if px > 0 else -cw
			var cy := ch if py > 0 else -ch
			var dx := px - cx
			var dy := py - cy
			var dist := approx_distance(dx, dy)
			if dist >= CORNER_RADIUS:
				a = (dy << 8) / dist
				b = -((dx << 8) / dist)
				bounce_off_boards(e, a, b)
			return
	if absi(py) >= h:
		a = 0x100 if py > 0 else -0x100
		b = 0
	elif absi(px) >= w:
		a = 0
		b = -0x100 if px > 0 else 0x100
	else:
		return
	bounce_off_boards(e, a, b)

## a, b: rotated frame of the board normal; vn = -(a*vy - b*vx) >> 8 is negative when moving into the board
func bounce_off_boards(e: Entity, a: int, b: int) -> void:
	e.push_x = a
	e.push_y = b
	var vn := -((a * e.vy - e.vx * b) >> 8)
	var vt := (b * e.vy + e.vx * a) >> 8
	if e.slot != Entity.Slot.PUCK:
		if vn > 1000:
			return
		if vn < -0xfff and e.speed > 9:
			sfx_queue.append(0xb1)
		vn >>= 2
		if vn > -0x385:
			vn = -1000
		e.vx = (a * vt - vn * b) >> 8
		e.vy = (vn * a + b * vt) >> 8
	else:
		if vn >= 0:
			return
		vn >>= 2
		if vn < -0x3ff:
			sfx_queue.append(0xad)
		vt = vt - (vt >> 6) - (vt >> 7)
		e.vx = (a * vt - vn * b) >> 8
		e.vy = (vt * b + a * vn) >> 8
	if e.vz > 0:
		e.vz = 0
	# keep the entity inside the boards after the bounce
	var w := RINK_HALF_W - e.half_w
	var h := RINK_HALF_H - e.half_h
	e.x = clampi(e.xi, -w, w) << 16 | (e.x & 0xffff)
	e.y = clampi(e.yi, -h, h) << 16 | (e.y & 0xffff)

# --------------------------------------------------------------------------------------------
# camera (game_loop / update_camera, simplified: follows the puck)
# --------------------------------------------------------------------------------------------

func update_camera() -> void:
	var target := puck
	if puck_carrier >= 0:
		target = entities[puck_carrier]
	var tx := target.xi
	var ty := target.yi + (target.vy >> 7)
	camera_x += clampi(tx - camera_x, -0x20, 0x20) >> 2
	camera_y += clampi(ty - camera_y, -0x20, 0x20) >> 2

## scroll position of the 320x168 view over the 384x592 rink surface (game_loop)
func view_origin() -> Vector2i:
	return Vector2i(clampi(camera_x + 0x20, 0, 0x40), clampi(0xec - camera_y, 0, 0x1a8))

# --------------------------------------------------------------------------------------------
# helpers
# --------------------------------------------------------------------------------------------

## approx_distance (0xb3d94): octagonal approximation good enough for the AI decisions
static func approx_distance(dx: int, dy: int) -> int:
	var ax := absi(dx)
	var ay := absi(dy)
	var mx := maxi(ax, ay)
	var mn := mini(ax, ay)
	return mx + ((mn * 3) >> 3)

static func _div_trunc(a: int, b: int) -> int:
	# C division truncates towards zero; GDScript's / on ints does too, but keep it explicit
	var q := absi(a) / b
	return -q if a < 0 else q
