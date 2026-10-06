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

const STEP_DT := 16                 # position += 16 * velocity per step (dword_e03b2 >> 16)
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
var opt_line_changes := false       # bit 2 (line changes are not ported; players never tire out)
var opt_two_line_pass := true       # bit 3
var opt_injuries := false           # bit 4

var entities: Array[Entity] = []
var teams: Array[Team] = []
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
var game_over := false              # bit 7
# stop_flags
var faceoff_pending := false        # bit 0: faceoff set up, waiting for the drop
var whistle_ready := false          # bit 2
var shot_in_flight := false         # bit 4: a shot was taken (goalie_save / score bookkeeping)
var lead_announced := false         # bit 5
var leading_team := 0               # bit 6
var goalie_pulled := false          # bit 7
var misc_first_touch := false       # misc_flags bit 4: first touch after the faceoff

var controls_blocked := false       # dword_ccc9c
var period: int = 0                 # period_idx (0 based)
var period_length: int = 300        # seconds on the clock at the start of a period (dword_e9ab6)
var clock_seconds: int = 300
var clock_sub: int = 0              # 24 sub ticks per second, decremented every step
var period_over := false
var stoppage_timer: int = -1
var whistle_timer: int = 0
var announce_timer: int = -1        # word_cc0b0
var ref_phase: int = -1             # dword_c90d4: 0 = referee called, 1 = collecting, -1 = ready
var ref_infraction: int = 0         # dword_c90d6
var faceoff_x: int = 0              # dword_c90b2
var faceoff_y: int = 0
var faceoff_timer: int = 0          # word_dff42
var faceoff_ready: Array = [0, 0]   # word_e038e / word_e0394: readiness of the two centres
var faceoff_side: Array = [0x8800, 0xa000]   # dword_e0392 / word_e0396
var faceoff_dir: Array = [-1, -1]   # word_c90b6 / word_c90b8: direction held by the users at the drop
var skip_wait := false              # dword_cc0f0: a user pressed a button during the pre faceoff wait
var infractions: Array = []         # infraction_queue: [type, slot, processed]
var last_touch_slot: int = -1       # dword_e9ac2
var last_touch_x: int = 0           # word_e9ac6
var last_touch_y: int = 0           # word_e9ac4
var last_passer: int = -1           # dword_c90a2
var last_shooter: int = -1          # word_c90a0
var pass_target: int = -1           # shot_power high word
var shot_power: int = 0             # shot_power low word
var pending_dir: int = 8            # pending_dir
var action_pass := false            # action_flags bit 2
var action_shot := false            # action_flags bit 3
var action_hold_camera := false     # action_flags bit 6
var one_timer := false              # dword_cc0f4
var breakaway := false              # dword_cc0f8
var defenders_ahead := 0            # dword_cc124
var icing_flags: int = 0            # dword_e9abe byte 2: 1 icing called, 2 direction, 4 candidate
var icing_shooter: int = -1
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
var rng := RandomNumberGenerator.new()
var puck_in_net := false            # byte_c90ba
var puck_stuck_timer: int = 0x78    # puck +0x28 (frozen puck countdown)
var puck_goal_timer: int = 0        # puck +0x26 (goal line prediction every 5 steps)
var penalty_shot := false           # dword_cc128 (not ported, always false)

func _init() -> void:
	rng.seed = 0x4e484c
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
		e.team = 0 if i < 6 else 1
		if i < 12:
			e.line_slot = -1
			e.roster_idx = -1
		entities.append(e)
	puck = entities[Entity.Slot.PUCK]
	shadow = entities[Entity.Slot.SHADOW]
	referee = entities[Entity.Slot.REFEREE]
	puck.line_slot = 0
	shadow.line_slot = 0
	teams[0].attacks_up = true
	teams[1].attacks_up = false
	teams[0].goalie_slot = 0
	teams[1].goalie_slot = 6
	start_period(0)

## new period: dress the default lines, everyone to the centre faceoff
func start_period(p: int) -> void:
	period = p
	clock_seconds = period_length
	clock_sub = 0
	period_over = false
	ends_switched = (p & 1) == 1
	for t in 2:
		var team := teams[t]
		var up := (t == 0) != ends_switched     # the home team shoots at +y in the 1st and 3rd period
		team.attacks_up = up
		for i in 6:
			var e := entities[t * 6 + i]
			e.line_slot = i
			e.roster_idx = 25 if i == 0 else i - 1
			e.flags &= ~(Entity.F_ATTACK_UP | Entity.F_USER | Entity.F_BUSY | Entity.F_BACKWARDS)
			if up:
				e.flags |= Entity.F_ATTACK_UP
			e.flags2 = 0
			e.state_sp = 0
			e.state_stack[0] = Entity.State.INIT_PERIOD
			team.entity_of[e.roster_idx] = e.slot
			_default_skills(e)
	play_stopped = true
	faceoff_x = 0
	faceoff_y = 0
	infractions.clear()
	# jump straight to the faceoff set up (the referee ceremony of the original is skipped)
	puck.state_sp = 0
	puck.state_stack[0] = Entity.State.PUCK_FACEOFF
	puck.flags |= Entity.F_STATE_ENTERED
	referee.state_sp = 0
	referee.state_stack[0] = Entity.State.REF_FACEOFF
	stoppage_countdown = false
	stoppage_timer = -1
	ref_phase = -1
	if user1_team != 0:
		user1_slot = (user1_team - 1) * 6 + 4
		entities[user1_slot].flags |= Entity.F_USER
	if user2_team != 0:
		user2_slot = (user2_team - 1) * 6 + 4
		entities[user2_slot].flags |= Entity.F_USER | Entity.F_PLAYER2

## default ratings in the 0..15 scale of the player database (put_player_on_ice would read them)
func _default_skills(e: Entity) -> void:
	e.weight = 128 + (e.slot % 3) * 10
	e.speed_skill = 9 if e.line_slot > 0 else 5
	e.stamina = 8
	e.reaction = 6
	e.awareness = 7
	e.shot_skill = 8
	e.shot_accuracy = 7
	e.pass_skill = 8
	e.offense = 7
	e.goalie_skill = 9
	e.stick_skill = 8
	e.check_skill = 7
	e.aggression = 6
	e.left_handed = 1 if (e.slot % 4) == 1 else 0
	e.flags4 = Entity.F4_MIRROR if e.left_handed else 0
	e.number = 10 + e.slot
	e.energy = 0x1000

func team_of(e: Entity) -> Team:
	return teams[e.team]

func opponents_of(e: Entity) -> Team:
	return teams[1 - e.team]

func same_team(a: int, b: int) -> bool:
	return (a < 6) == (b < 6)

func carrier() -> Entity:
	return entities[puck_carrier] if puck_carrier >= 0 else null

## randomrange (0x8c230): 0 .. n-1 (n <= 0 gives 0)
func random(n: int) -> int:
	if n <= 1:
		return 0
	return rng.randi_range(0, n - 1)

func play_sfx(id: int) -> void:
	sfx_queue.append(id)

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
	Rules.game_state_tick(self)
	# dword_ccc9c: the users cannot move during the whistle / announcement phase of a stoppage
	controls_blocked = play_stopped and (game_over or (not faceoff_pending and stoppage_timer < 0 and infractions.is_empty()))
	update_puck_distances()
	for i in 17:
		var e := entities[i]
		e.prev_x = e.x
		e.prev_y = e.y
		e.prev_z = e.z
		if e.line_slot < 0 and e.slot != Entity.Slot.REFEREE:
			continue
		Anim.advance(e)
		e.timer_c = maxi(0, e.timer_c - 1)
		e.timer_d = maxi(0, e.timer_d - 1)
		integrate(e)
		if e.slot == user1_slot:
			control_player(e, control_p1, pressed_p1, 0)
		elif e.slot == user2_slot:
			control_player(e, control_p2, pressed_p2, 1)
		if e.state() != Entity.State.NONE:
			AI.dispatch(self, e)
		clamp_goalie_to_crease(e)
		e.push_x = 0
		e.push_y = 0
		if e.xi != e.prev_x >> 16 or e.yi != e.prev_y >> 16 or e.slot == Entity.Slot.PUCK:
			move_entity(e)
		e.speed = maxi(0, e.speed - 2)
		e.contact = e.speed
	# the carrier cannot drag the puck through the boards or behind the goal line (end of sim_update_players)
	if puck.zi < 0x18 and absi(puck.xi) > 0xa0 and puck_carrier >= 0:
		puck.x = (-0xa0 if puck.xi < 0 else 0xa0) * 0x10000
		puck.frame = 0x18a
	if puck.zi < 1 and puck_carrier >= 0 and (puck.yi < -0x104 or puck.yi > 0x108):
		puck.y = (-0x104 if puck.yi < 0 else 0x108) * 0x10000
		puck.frame = 0x18a
	update_camera()

## first loop of sim_update_players: distance/direction of every skater to the puck and the nearest
## skater of each team (team.nearest_slot)
func update_puck_distances() -> void:
	teams[0].reset_nearest()
	teams[1].reset_nearest()
	for i in 12:
		var e := entities[i]
		var dx := puck.xi - e.xi
		var dy := puck.yi - e.yi
		e.puck_dist = approx_distance(dx, dy)
		e.puck_dir = Tables.direction8(dx, dy)
		var qx := dx >> 2
		var qy := dy >> 2
		e.puck_dist_sq = qx * qx + qy * qy
		var team := teams[e.team]
		if e.line_slot == 0:
			team.goalie_slot = i
		elif e.line_slot > 0 and (e.flags2 & Entity.F2_UNSELECTABLE) == 0 and (e.flags & Entity.F_BUSY) == 0:
			if e.puck_dist < team.nearest_dist:
				team.nearest_dist = e.puck_dist
				team.nearest_slot = i

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
			if clampi(5 - e.flags3, 0, 99) < 4:
				play_sfx(0xab)   # puck drop
		else:
			e.z = nz

## sim_update_players: a goalie without the puck is kept out of the net posts area
func clamp_goalie_to_crease(e: Entity) -> void:
	if e.slot >= 12 or play_stopped or e.line_slot != 0 or puck_carrier == e.slot or (e.flags3 & 1):
		return
	var px := e.xi
	if px < -0x2b:
		if px > -0x32:
			e.x = -0x2b * 0x10000
			e.vx = 0
	elif px > 0x2b and px < 0x31:
		e.x = 0x2b << 16
		e.vx = 0
	var py := e.yi
	if py < 0:
		if py > -0xc6 and py < -0xc0:
			e.y = -0xc6 * 0x10000
			e.vy = 0
	elif py > 0xc0 and py < 0xc6:
		e.y = 0xc6 << 16
		e.vy = 0

# --------------------------------------------------------------------------------------------
# controls (control_player, apply_skating, skating_turn, skating_accelerate, stop_skating, brake)
# --------------------------------------------------------------------------------------------

## control_player (0x504da) for the player controlled by `player` (0/1); `control` is the sampled
## control byte, `pressed` the buttons that just went down
func control_player(e: Entity, control: int, pressed: int, player: int) -> void:
	e.flags |= Entity.F_USER
	if player == 1:
		e.flags |= Entity.F_PLAYER2
	if play_stopped:
		if faceoff_pending:
			faceoff_control(e, control, pressed)
			return
		if puck.state() == Entity.State.PUCK_FACEOFF2 and (pressed & 0x30):
			skip_wait = true   # a button press shortens the wait before the drop
			return
	if (e.flags & Entity.F_USER) == 0:
		return
	var dir := control & 0xf
	var carrying := puck_carrier == e.slot
	if (e.flags & Entity.F_BUSY) == 0:
		if carrying:
			if e.line_slot == 0 and (e.flags2 & Entity.F2_TURNING):
				return
			if action_pass:
				PuckLogic.pass_button(self, e, control, pressed)
				return
			if action_shot:
				PuckLogic.shot_control(self, e, control, pressed)
				return
			if pressed & 0x10:          # A: pass (released next step, in the pushed direction)
				pending_dir = e.facing
				action_pass = true
				return
			if e.line_slot == 0:
				return
			if pressed & 0x20:          # B: start the shot animation, power builds while it is held
				PuckLogic.start_shot(self, e)
				return
		else:
			if controls_blocked:
				return
			if pressed & 0x40:
				PuckLogic.hook_button(self, e)
				return
			if pressed & 0x10:
				switch_to_nearest(e, player)
				return
			if e.line_slot == 0:
				return
			if e.slot == pass_target:
				if pressed & 0x20:
					PuckLogic.body_check(self, e)
				if one_timer:
					pending_dir = dir
					return
			else:
				if puck_carrier < 0 and (pressed & 0x20) and pass_target >= 0 and same_team(pass_target, e.slot) \
						and (entities[pass_target].flags & Entity.F_USER) == 0 \
						and (entities[pass_target].flags2 & Entity.F2_UNSELECTABLE) == 0:
					# one timer: take over the receiver, he shoots as soon as the pass arrives
					if player == 0:
						user1_slot = find_switch_target(pass_target, user1_slot)
					else:
						user2_slot = find_switch_target(pass_target, user2_slot)
					one_timer = true
					return
				if pressed & 0x20:
					PuckLogic.body_check(self, e)
					return
		apply_skating(e, dir)
	elif not carrying and not controls_blocked:
		if pressed & 0x10:
			switch_to_nearest(e, player)
		elif e.slot == pass_target and one_timer:
			pending_dir = dir

## faceoff_control (0x50f8d): the users time the drop; A commits to a direction
func faceoff_control(e: Entity, control: int, pressed: int) -> void:
	if e.state() != Entity.State.FACEOFF:
		return
	if e.flags & Entity.F_ATTACK_UP:
		faceoff_dir[0] = control & 0xf
	else:
		faceoff_dir[1] = control & 0xf
	if e.flags2 & Entity.F2_TURNING:
		return
	if (pressed & 0x10) == 0:
		e.timer_b -= 1
		if e.timer_b < 0:
			Anim.set_animation(e, 0x7f1)      # idle shuffle at the dot
		return
	e.flags2 |= Entity.F2_TURNING
	if faceoff_timer < 0x11:
		e.flags |= Entity.F_BUSY
		Anim.set_animation(e, 0x7dd)          # swing at the drop
	else:
		Anim.set_animation(e, 0xd05)          # too early
	e.timer_b = -1

func apply_skating(e: Entity, dir: int) -> void:
	if e.line_slot == 0:
		goalie_move(e, dir)
		return
	# animation without movement input: glide (one frame per direction)
	var idle_anim := Anim.GLIDE
	if e.flags & Entity.F_BACKWARDS:
		idle_anim = Anim.GLIDE_BACK
	elif e.slot == Entity.Slot.REFEREE:
		idle_anim = Anim.REF_GLIDE if not play_stopped else Anim.REF_GLIDE_STOPPED
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
	skating_turn(e, dir)

## skating_turn (0x5e9bc): facing matches the input, pick the skating cycle and accelerate
func skating_turn(e: Entity, dir: int) -> void:
	var a := Anim.SKATE
	if e.flags & Entity.F_BACKWARDS:
		a = Anim.SKATE_BACK
	elif e.slot == Entity.Slot.REFEREE:
		a = Anim.REF_SKATE if not play_stopped else Anim.REF_SKATE_STOPPED
	elif puck_carrier == e.slot:
		a = Anim.SKATE_CARRIER
	elif e.flags2 & Entity.F2_HOOKED:
		a = Anim.SKATE_HOOKED
	if (e.flags2 & Entity.F2_TURNING) == 0:
		Anim.set_animation(e, a)
	skating_accelerate(e, dir ^ 4 if (e.flags & Entity.F_BACKWARDS) else dir)

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
	var target_dir := dir
	if not play_stopped and puck_carrier != e.slot and e.state() == Entity.State.GOALIE:
		target_dir = e.puck_dir
	var diff := (target_dir - e.facing) & 7
	if diff != 0:
		e.facing = (e.facing + (1 if diff < 4 else -1)) & 7
	Anim.set_animation(e, Anim.GOALIE_IDLE)
	skating_accelerate(e, e.facing)

## switch_to_nearest (0x59e69): the user takes the skater nearest to where the puck is going
func switch_to_nearest(e: Entity, player: int) -> void:
	var team_no := user1_team if player == 0 else user2_team
	if team_no == 0:
		return
	var first := (team_no - 1) * 6
	var other := user2_slot if player == 0 else user1_slot
	var best := e.slot
	var best_d := 0x7fffffff
	for i in 6:
		var p := entities[first + i]
		if p.line_slot <= 0 or (p.flags2 & Entity.F2_UNSELECTABLE) or (p.flags & Entity.F_BUSY):
			continue
		var dx := puck.xi + (puck.vx >> 8) - p.xi
		var dy := puck.yi + (puck.vy >> 8) - p.yi
		var d := dx * dx + dy * dy
		if d <= best_d and p.slot != other:
			best_d = d
			best = p.slot
	var cur := user1_slot if player == 0 else user2_slot
	if cur == best:
		# nobody else: the current player lunges for the puck instead (sub_532a2)
		e.flags |= Entity.F_BUSY
		Anim.set_animation(e, 0x589)
		return
	if player == 0:
		user1_slot = find_switch_target(best, user1_slot)
	else:
		user2_slot = find_switch_target(best, user2_slot)

## find_switch_target (0x59f1a): moves the user flag from `cur` to `target`, returns the new slot
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

func move_entity(e: Entity) -> void:
	puck_in_net = false
	if e.slot >= 12 and e.slot != Entity.Slot.PUCK and e.slot != Entity.Slot.REFEREE:
		return
	if (e.flags & Entity.F_ARRIVED) == 0 or e.slot == Entity.Slot.PUCK:
		collide_boards(e, e.xi, e.yi, e.half_w, e.half_h)
		if e.vx == 0 and e.vy == 0 and e.slot < 12:
			# standing players also keep their stick inside the rink
			var o := Tables.frame_offset(e.frame, (e.flags4 & Entity.F4_MIRROR) != 0)
			collide_boards(e, e.xi + o.x, e.yi + o.y, 1, 1)
		collide_neighbours(e)
	if puck_in_net and (e.anim < 0xf0f or e.anim > 0x1055):
		e.x = (e.prev_x >> 16) << 16 | (e.x & 0xffff)
		e.y = (e.prev_y >> 16) << 16 | (e.y & 0xffff)

## collide_boards (0x582c9): boards with rounded corners; inside the end zones the nets are checked
func collide_boards(e: Entity, px: int, py: int, hw: int, hh: int) -> void:
	var w := RINK_HALF_W - hw
	var h := RINK_HALF_H - hh
	var cw := w - CORNER_RADIUS
	var ch := h - CORNER_RADIUS
	if absi(py) > ch:
		if absi(px) >= cw:
			var cx := cw if px > 0 else -cw
			var cy := ch if py > 0 else -ch
			var dx := px - cx
			var dy := py - cy
			var dist := approx_distance(dx, dy)
			if dist >= CORNER_RADIUS:
				var a := (dy << 8) / dist
				var b := -((dx << 8) / dist)
				collide_corner(e, a, b)
			return
		else:
			collide_net(e, entities[Entity.Slot.NET_TOP if py > 0 else Entity.Slot.NET_BOTTOM], px, py, hw, hh)
	if e.push_x != 0 or e.push_y != 0:
		return
	var a := 0   # board normal, a = ny * 256, b = -nx * 256 (see bounce_off_boards)
	var b := 0
	if absi(py) >= h:
		a = 0x100 if py > 0 else -0x100
	elif absi(px) >= w:
		b = -0x100 if px > 0 else 0x100
	else:
		return
	collide_corner(e, a, b)

## collide_corner (0x58b96): a hard puck into the end boards can go out of play
func collide_corner(e: Entity, a: int, b: int) -> void:
	if e.slot == Entity.Slot.PUCK:
		var out := false
		if e.zi > 0x1d:
			out = true
		elif e.zi > 0x12:
			out = true
			if e.yi >= 0xf8 and absi(e.xi) > 0x27 and absi(e.xi) < 0x39 and e.vy > 3999 and last_touch_y > 0x25:
				e.vy >>= 1   # into the protective glass behind the net
				play_sfx(0xae)
				add_crowd(0x4b0, 0x5dc)
				excitement += 0xf
		if out:
			# puck over the glass: out of play, a new one is dropped
			action_hold_camera = true
			e.flags |= Entity.F_ARRIVED
			if e.yi < 0:
				e.flags4 |= Entity.F4_FLIP_Y
			if not play_stopped:
				Rules.queue_infraction(self, entities[maxi(0, last_touch_slot)], Rules.INF_FROZEN)
			one_timer = false
			breakaway = false
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
			play_sfx(0xb1)
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
			play_sfx(0xad)
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

## collide_net (0x584aa): the puck against a net; players are pushed around it (sub_53ce5)
func collide_net(e: Entity, net: Entity, px: int, py: int, hw: int, hh: int) -> void:
	if e.zi > 0xd:
		return      # over the net
	if e.slot != Entity.Slot.PUCK:
		collide_player_net(e, net, px, py)
		return
	var dx := px - net.xi
	if absi(dx) > hw + 0x10:
		return
	var dy := py - net.yi
	if absi(dy) > hh + 2:
		return
	puck_in_net = true
	e.flags &= ~Entity.F_ATTACK_UP
	if puck_carrier >= 0:
		var c := entities[puck_carrier]
		puck_carrier = -1
		c.timer_c = 8
		var ty := puck.yi if (c.flags & Entity.F_ATTACK_UP) else -puck.yi
		if ty < 0:
			e.flags |= Entity.F_ATTACK_UP
	# the goal line is crossed between the posts: a goal (score_goal) unless the puck comes from
	# behind the net or hits the frame
	var dir_y := (e.y - e.prev_y) >> 8
	if dir_y != 0:
		var post_w := hw + 0x10
		var depth := hh + 2
		if dir_y > 0:
			depth = -depth
		var dxp := ((e.x - e.prev_x) >> 8) * (depth + dy) / dir_y
		if dxp > -0x10000 and dxp < 0x10000:
			var cx := dx - dxp
			if absi(cx) <= post_w:
				var toward_front := (py ^ (0x100 if dir_y > 0 else -0x100)) >= 0
				if toward_front and (e.flags & Entity.F_ATTACK_UP) == 0:
					if e.zi != 0xd and absi(cx) <= post_w - 1:
						Rules.score_goal(self, net)
						return
					# off the post / crossbar
					shot_in_flight = false
					add_crowd(500, 0x4b0)
					excitement += 0x28
					play_sfx(0xac)
					var r := random(0x1000)
					e.vy = -r if e.yi >= 0 else r
					e.vx = random(0x2000) - 0x1000
					e.vz = random(0x2000) - 0x1000
					PuckLogic.puck_spin(self, e)
					one_timer = false
					breakaway = false
					return
	# bounce off the frame
	var a := 0x100 if dir_y > 0 else -0x100
	if dir_y == 0:
		a = 0
	var b := 0x100 if (px - (e.prev_x >> 16)) < 0 else -0x100
	bounce_off_boards(e, a, b)

## sub_53ce5: a skater or the referee bumps into the net frame
func collide_player_net(e: Entity, net: Entity, px: int, py: int) -> void:
	if e.slot >= 12 and e.slot != Entity.Slot.REFEREE:
		return
	var dy := py - net.yi
	var dx := px - net.xi
	if net.slot == Entity.Slot.NET_TOP:
		if e.half_h + dy < -0x22:
			return
	elif dy - e.half_h > 0x21:
		return
	if absi(dx) - e.half_w >= 0x40:
		return
	var q := (dx * dx) >> 2
	if q > 0x100 or dy * dy * 2 + q > 0x100:
		return
	if e.slot != Entity.Slot.REFEREE and PuckLogic.net_pushed_off(self, e):
		return
	var dist := approx_distance(dx, dy) + 1
	var a := clampi((-dy << 8) / dist, -0xff, 0xff)
	var b := clampi((dx << 8) / dist, -0xff, 0xff)
	bounce_off_boards(e, a, b)

## collide_neighbours / collide_pair: body contact between skaters (and the referee)
func collide_neighbours(e: Entity) -> void:
	if e.flags2 & Entity.F2_NO_COLLIDE:
		return
	if e.slot >= 12 and e.slot != Entity.Slot.REFEREE:
		return
	for i in 17:
		if i == e.slot or (i >= 12 and i != Entity.Slot.REFEREE):
			continue
		var o := entities[i]
		if o.line_slot < 0 and o.slot != Entity.Slot.REFEREE:
			continue
		if absi(o.yi - e.yi) > 0x10:
			continue
		collide_pair(e, o)

func collide_pair(e: Entity, o: Entity) -> void:
	if (o.flags & Entity.F_ARRIVED) or (o.flags2 & Entity.F2_NO_COLLIDE):
		return
	var dx := o.xi - e.xi
	var dy := o.yi - e.yi
	if absi(dx) > 0x10:
		return
	var d2 := dx * dx + dy * dy
	if d2 > 0x100:
		return
	var rvx := e.vx - o.vx
	var rvy := e.vy - o.vy
	var closing := dy * rvy + dx * rvx
	if closing < 0:
		return
	var strength := closing >> 4
	if e.slot == Entity.Slot.REFEREE or o.slot == Entity.Slot.REFEREE or e.team != o.team:
		var s := maxi(5, strength >> 8)
		e.contact += s
		o.contact += s
		if (o.flags2 & Entity.F2_KNOCKED) == 0:
			o.hit_by = e.slot
		if (e.flags2 & Entity.F2_KNOCKED) == 0:
			e.hit_by = o.slot
		if s > 0x13 and (puck_carrier == e.slot or puck_carrier == o.slot):
			play_sfx(0xb0 if (step_count & 1) else 0xb2)
		PuckLogic.resolve_body_check(self, e, o, s)
	if puck_in_net:
		return
	# exchange momentum along the contact normal, weighted by the masses
	var tang := (dy * rvx - rvy * dx) >> 4
	var me := e.weight + 0x8c
	var total := o.weight + 0x8c + me
	var give := (me * strength) / total
	e.vx = o.vx + ((give * dx + tang * dy) >> 4)
	e.vy = o.vy + ((give * dy - tang * dx) >> 4)
	o.vx += (dx * give) >> 4
	o.vy += (dy * give) >> 4
	puck_in_net = true   # the original marks the frame as "position reverted" with byte_c90ba
	if not play_stopped and e.team == o.team:
		# team mates step around each other
		var away := Tables.direction8(dx, dy)
		if (e.flags & Entity.F_USER) == 0:
			var want := Tables.direction8(e.target_x - e.xi, e.target_y - e.yi)
			if want == away or (e.vx == 0 and e.vy == 0 and away == e.facing):
				e.want_dir = (away + 2) & 7
				apply_skating(e, e.want_dir)
		if (o.flags & Entity.F_USER) == 0:
			var back := (away + 4) & 7
			var want_o := Tables.direction8(o.target_x - o.xi, o.target_y - o.yi)
			if want_o == back or (e.vx == 0 and e.vy == 0 and back == o.puck_dir):
				o.want_dir = (back + 2) & 7
				apply_skating(o, o.want_dir)

# --------------------------------------------------------------------------------------------
# camera (update_camera 0x65d8d)
# --------------------------------------------------------------------------------------------

func update_camera() -> void:
	var limit := 0x28
	var ease := 10
	var tx := camera_target_x
	var ty := camera_target_y
	if game_over:
		tx = -100
		ty = 0xf
	elif clock_seconds != 0 or clock_sub != 0:
		if (not stoppage_countdown or stoppage_timer >= 0) and ref_phase < 1:
			if not action_hold_camera:
				var target := puck
				if puck_carrier >= 0:
					target = entities[puck_carrier]
					if puck_carrier == Entity.Slot.REFEREE:
						camera_offset_y = -(target.vy >> 8)
					elif (target.flags & Entity.F_ATTACK_UP) == 0:
						camera_offset_y = maxi(camera_offset_y - 2, -0x32)
					else:
						camera_offset_y = mini(camera_offset_y + 2, 0x32)
				ty = camera_offset_y + target.yi + (target.vy >> 8)
				tx = target.xi
		else:
			# during the stoppage the camera follows the referee, then the faceoff spot
			tx = referee.xi
			ty = referee.yi
			var rs := referee.state()
			if (rs == Entity.State.REF_GOTO_FACEOFF or rs == Entity.State.REF_PENALTY_SHOT) \
					and (referee.xi - faceoff_x) ** 2 + (referee.yi - faceoff_y) ** 2 < 0x640:
				tx = faceoff_x
				ty = faceoff_y
				limit = 0
				ease = 0
	camera_target_x = tx
	camera_target_y = ty
	var dy := ty - camera_y
	if dy > limit:
		camera_y += maxi(1, (mini(dy - limit, 0x20)) >> 2) if ease > 0 else dy
	elif dy < -limit:
		camera_y -= maxi(1, (mini(-dy - limit, 0x20)) >> 2) if ease > 0 else -dy
	camera_y = clampi(camera_y, -0xbc, 0xec)
	var dx := tx - camera_x
	if dx > ease:
		camera_x += maxi(1, mini(dx - ease, 0x20) >> 2)
	elif dx < -ease:
		camera_x -= maxi(1, mini(-dx - ease, 0x20) >> 2)
	camera_x = clampi(camera_x, -0x20, 0x20)

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

## sub_93470: integer square root
static func isqrt(v: int) -> int:
	if v <= 0:
		return 0
	var r := int(sqrt(float(v)))
	while r * r > v:
		r -= 1
	while (r + 1) * (r + 1) <= v:
		r += 1
	return r
