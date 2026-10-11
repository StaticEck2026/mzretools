class_name Logic94
extends RefCounted
## The NHL '94 (Sega Genesis) gameplay rules, the front end's Game > Gameplay Logic: the PC game's own
## logic (the default, every golden test) or the Genesis game's, with each '94 feature on or off. The
## rules come from the bit-exact rebuild of the Genesis ROM (github.com/abdulahmad/NHL94Genesis:
## input94 doinput / passmode / dopass / prepshot / doshot, onetimer94, goalie94, checks94
## asspassrec / assgoaliectrl), applied to the PC game's own players, animations and physics; the PC
## code they replace stays as it was (Sim.control_player, AI.pass_receiver, AI.goalie, PuckLogic.do_shot
## call in here only when the option is on):
##
## - one-timers: the shot button while the user's pass is on its way makes the receiver one-time it
##   only on the attacking half (PuckOnAttackHalf), also when the user already has the receiver
##   (doinput_onetimer); a computer receiver one-times every pass in the attacking zone and one in 8
##   elsewhere on the attacking half (asspassrec). The wind-up and the shot are the PC game's
##   (one_timer_step).
## - the saucer pass: the carrier's third button (tapped, or held 15 steps) lifts the puck to the
##   one-timer spot (OneTimerTarget / OneTimerPass): across the slot from the attacking zone, to the
##   slot from farther out, short to a side for a goalie.
## - top shelf: a shot from in close (aimed high, the goalie down or none) is lifted to clear him
##   (prepshot / puckvzadj).
## - the manual goalie: holding the pass / switch button 17 steps takes the own goalie (a tap still
##   switches, when the button is let go); he skates (kept to his crease), dives with the third button
##   and a direction, saves with the shot button; on screen the computer leaves him alone, off screen
##   it plays him (assgoaliectrl); out of his zone the whistle goes.
##
## The Genesis rink is longer and narrower than the PC game's (side boards +-136 / +-160, end boards
## +-298 / +-264, blue lines +-88 / +-78): its places are scaled to the PC rink (x 160/136, y 264/298),
## its per-step distances (17 a step on the Genesis, 16 here) to the PC game's.

const CFG_PATH := "user://settings.cfg"

# the options (the front end's Gameplay Logic menu)
static var enabled := false             # the Genesis '94 rules (else the PC game's)
static var one_timers := true
static var saucer_passes := true
static var top_shelf := true
static var manual_goalie := true        # OptGoalie 0 Manual Control (1 Auto Control)

static func load_options() -> void:
	var cfg := ConfigFile.new()
	if cfg.load(CFG_PATH) != OK:
		return
	enabled = cfg.get_value("logic94", "enabled", enabled)
	one_timers = cfg.get_value("logic94", "one_timers", one_timers)
	saucer_passes = cfg.get_value("logic94", "saucer_pass", saucer_passes)
	top_shelf = cfg.get_value("logic94", "top_shelf", top_shelf)
	manual_goalie = cfg.get_value("logic94", "manual_goalie", manual_goalie)

static func save_options() -> void:
	var cfg := ConfigFile.new()
	cfg.load(CFG_PATH)
	cfg.set_value("logic94", "enabled", enabled)
	cfg.set_value("logic94", "one_timers", one_timers)
	cfg.set_value("logic94", "saucer_pass", saucer_passes)
	cfg.set_value("logic94", "top_shelf", top_shelf)
	cfg.set_value("logic94", "manual_goalie", manual_goalie)
	cfg.save(CFG_PATH)

## a match's rules from the options
static func apply(sim: Sim) -> void:
	sim.l94_one_timers = enabled and one_timers
	sim.l94_saucer = enabled and saucer_passes
	sim.l94_top_shelf = enabled and top_shelf
	sim.l94_manual_goalie = enabled and manual_goalie
	sim.l94_bhold = [HOLD_STEPS, HOLD_STEPS]
	sim.l94_ahold = [0, 0]

# ---------------------------------------------------------------------------------------------
# helpers
# ---------------------------------------------------------------------------------------------

## the y of e's attack (positive towards the net he shoots at)
static func _attack_y(e: Entity, y: int) -> int:
	return y if (e.flags & Entity.F_ATTACK_UP) else -y

## PuckOnAttackHalf: the puck on the half of the net e shoots at (the centre line counts)
static func puck_on_attack_half(sim: Sim, e: Entity) -> bool:
	return _attack_y(e, sim.puck.yi) >= 0

## getGoalieSCnum: the goalie of e's team (line slot 0), null when he is pulled
static func own_goalie(sim: Sim, e: Entity) -> Entity:
	var first := 0 if e.slot < 6 else 6
	for i in 6:
		var p := sim.entities[first + i]
		if p.line_slot == 0:
			return p
	return null

static func _opposing_goalie(sim: Sim, e: Entity) -> Entity:
	var first := 6 if e.slot < 6 else 0
	for i in 6:
		var p := sim.entities[first + i]
		if p.line_slot == 0:
			return p
	return null

# ---------------------------------------------------------------------------------------------
# one-timers (doinput .8 / doinput_onetimer, asspassrec)
# ---------------------------------------------------------------------------------------------

## doinput .8: the user's passer (or, doinput_onetimer, the user's receiver) asks for a one-timer:
## the receiver a skater, no one-timer on, the puck on his attacking half
static func can_one_time(sim: Sim, receiver: Entity) -> bool:
	return receiver.line_slot > 0 and not sim.one_timer and puck_on_attack_half(sim, receiver)

## doinput_onetimer: the user is the receiver of a pass on its way from a skater
static func receiver_one_timer(sim: Sim, e: Entity) -> bool:
	if sim.last_passer < 0 or sim.last_passer >= 12 or sim.entities[sim.last_passer].line_slot == 0:
		return false
	if sim.pass_target != e.slot or Entity.to_s8(sim.puck_carrier) >= 0:
		return false
	if not can_one_time(sim, e):
		return false
	sim.one_timer = true
	return true

## asspassrec: a computer receiver (not a goalie) one-times the pass on his attacking half: in the
## attacking zone (between the blue line and the goal line) always, elsewhere one in 8
static func cpu_one_timer(sim: Sim, e: Entity) -> bool:
	if e.line_slot == 0 or sim.one_timer or not puck_on_attack_half(sim, e):
		return false
	var y := _attack_y(e, e.yi)
	if y >= Sim.BLUE_LINE_Y and y <= Sim.GOAL_LINE_Y:
		return true
	return sim.random(8) == 0

# ---------------------------------------------------------------------------------------------
# the saucer pass (doinput_ispc aholdtimer, setpassmode / dopass with sflags5 bit 3, OneTimerTarget,
# OneTimerPass)
# ---------------------------------------------------------------------------------------------

# OneTimerNearTbl / OneTimerFarTbl / OneTimerGoalieTbl, by facing, scaled to the PC rink: (+-0x74,
# 0xc2) -> (+-0x88, 0xac); (-5, 0xab) -> (-6, 0x97); (-5 / +-0x32, -9) -> (-6 / +-0x3b, -8)
const NEAR_X := [0x88, 0x88, 0x88, 0x88, -0x88, -0x88, -0x88, -0x88]
const NEAR_Y := 0xac
const FAR_X := -6
const FAR_Y := 0x97
const FAR_DEEP_Y := 0xe5            # $103: the passer near the goal, in the middle
const GOALIE_X := [-6, 0x3b, 0x3b, 0x3b, -6, -0x3b, -0x3b, -0x3b]
const GOALIE_Y := -8
const MIN_SPREAD := 0x47            # $3c: the spot at least this far to the side of the passer

## the carrier's third button: the saucer pass when it is let go, or after 15 steps held. Returns
## true when the pass went
static func saucer_input(sim: Sim, e: Entity, p: int) -> bool:
	if sim.penalty_shot:
		return false
	if sim.scratch_b & 0x40:
		sim.l94_ahold[p] = 0xf
	if sim.scratch_a & 0x40:
		sim.l94_ahold[p] = maxi(sim.l94_ahold[p] - 1, 0)
		if sim.l94_ahold[p] == 0:
			saucer_pass(sim, e)
			return true
		return false
	if sim.scratch_ac & 0x40:
		saucer_pass(sim, e)
		return true
	return false

## OneTimerTarget: the spot by the passer's facing: from outside the attacking zone (or a goalie's
## table) the deep spot across the slot and a high lob (0x3a), from inside the middle of the slot (or
## by the goal line when he is near the net in the middle) and a low one (0x12); plus 0..9 at random
## each way, the spot moved to at least MIN_SPREAD to the side of a skating passer. [x, y, high]
static func saucer_target(sim: Sim, e: Entity) -> Array:
	var up := (e.flags & Entity.F_ATTACK_UP) != 0
	var facing := e.facing & 7
	if not up:
		facing = (facing + 4) & 7
	var x: int
	var y: int
	var high := false
	if e.line_slot == 0:
		x = GOALIE_X[facing]
		y = GOALIE_Y
	elif _attack_y(e, e.yi) < Sim.BLUE_LINE_Y:
		high = true
		x = NEAR_X[facing]
		y = NEAR_Y
	else:
		x = FAR_X
		y = FAR_Y
		if absi(e.yi) >= 0x7a and absi(e.xi) <= 0x41:
			y = FAR_DEEP_Y
	if not up:
		x = -x
		y = -y
	x += sim.random(0xa)
	y += sim.random(0xa)
	var tx := x
	if e.line_slot != 0:
		var d := x - e.xi
		if d >= 0:
			d -= MIN_SPREAD
			if d < 0:
				tx -= d
		else:
			d += MIN_SPREAD
			if d >= 0:
				tx -= d
	return [tx, y, high]

## isqrt (sroot)
static func isqrt(v: int) -> int:
	if v <= 0:
		return 0
	var r := int(sqrt(float(v)))
	while r * r > v:
		r -= 1
	while (r + 1) * (r + 1) <= v:
		r += 1
	return r

## OneTimerPass: vz for the lob's height h (sqrt(12 h) in 8.8), the puck's flight vz / 3 steps (the
## PC game's gravity and step are the Genesis ones scaled alike, so the formula holds), vx / vy to
## land on the spot; the puck spins
static func saucer_flight(sim: Sim, tx: int, ty: int, h: int) -> void:
	var puck := sim.puck
	var vz := isqrt((12 * h) << 16)
	puck.vz = Sim._s16(vz)
	var t := maxi(vz / 3, 1)
	puck.vx = Sim._s16(clampi(((tx - puck.xi) << 16) / t, -0x8000, 0x7fff))
	puck.vy = Sim._s16(clampi(((ty - puck.yi) << 16) / t, -0x8000, 0x7fff))
	PuckLogic.puck_spin(sim, puck, vz)

## dopass with the saucer flag: the puck leaves the carrier for the spot (no receiver), with the PC
## game's pass animation and sound; a goalie's pass never goes towards his own net
static func saucer_pass(sim: Sim, e: Entity) -> void:
	var puck := sim.puck
	sim.one_timer = false
	sim.action_pass = false
	sim.puck_carrier = -1
	sim.pass_target = -1
	e.timer_c = 0x10
	sim.last_passer = e.slot
	var t := saucer_target(sim, e)
	saucer_flight(sim, t[0], t[1], 0x3a if t[2] else 0x12)
	var a := 0
	if e.line_slot == 0:
		if (puck.vy < 0) != ((e.flags & Entity.F_ATTACK_UP) == 0):
			puck.vy = Sim._s16(-puck.vy)
		a = 0x1b9
		e.flags2 |= Entity.F2_TURNING
	else:
		a = 0x3c1 if PuckLogic.shot_is_backhand(e, Tables.direction8(puck.vx, puck.vy)) else 0x389
	Anim.set_animation(e, a)
	e.flags |= Entity.F_BUSY
	sim.play_sfx(0x99 if Entity.to_s8(puck.vz >> 8) >= 6 else 0x98)

# ---------------------------------------------------------------------------------------------
# top shelf (prepshot / puckvzadj)
# ---------------------------------------------------------------------------------------------

# the PC game's pad stacks (goalie_save_anims for a low, wide save), the Genesis SPAgstackr / l
const PAD_STACKS := [0x121d, 0x11d5]

## prepshot: in close (past y 0xd8, 0xbf here) a shot aimed high (0, 1, 7) on a goalie down in a
## pad stack, or on an empty net, goes top shelf
static func top_shelf_shot(sim: Sim, e: Entity) -> bool:
	var g := _opposing_goalie(sim, e)
	if g != null and not (g.anim in PAD_STACKS):
		return false
	var aim := sim.pending_dir
	if aim > 1 and aim != 7:
		return false
	return _attack_y(e, sim.puck.yi) >= 0xbf

## puckvzadj: vz for the puck to be 10 pixels up when it reaches the goal line: the steps t to get
## there at its vy, then 10 / t up plus the fall over t (the Genesis' 17 a step is 16 here)
static func puckvzadj(sim: Sim) -> void:
	var puck := sim.puck
	var d := absi(absi(puck.yi) - Sim.GOAL_LINE_Y)
	var vy := absi(Sim._s16(puck.vy))
	if vy == 0:
		return
	var q := (d << 16) / vy
	if q > 0xffff:
		q = 0                       # divu overflow: the dividend's low word, 0
	var t := q / Sim.STEP_DT
	if t == 0:
		t = 1
	var v := 0xa0000 / (t * Sim.STEP_DT)
	var fall := 3 * Sim.STEP_DT * t
	if fall >= 0x7fff:
		fall = 0x7fff
	v = (v + fall) & 0xffff
	if v >= 0x8000:
		v = 0x7fff
	puck.vz = Sim._s16(v)

# ---------------------------------------------------------------------------------------------
# the manual goalie (doinput .12 - .31, .33, doinput_cbut, doinput_chkanim; assgoaliectrl)
# ---------------------------------------------------------------------------------------------

const HOLD_STEPS := 0x11            # bholdtimer
const CREASE_X := 0x2a              # $24
const CREASE_Y := 0xc7              # $e7: 0x21 out from the goal line
const OUT_OF_ZONE_Y := 0x97         # $aa
const SCREEN_X := 0x74              # assgoaliectrl: the goalie on screen (from the view's middle; the
const SCREEN_Y := 0x4b              # Genesis $64 of a 224 line view, the PC view is 168 lines)

## the pass / switch button of a user without the puck (bholdtimer): a tap switches when it is let
## go; held 17 steps it takes the own goalie. Returns true when it switched
static func switch_input(sim: Sim, e: Entity, p: int) -> bool:
	var held := (sim.scratch_a & 0x10) != 0
	var pressed := (sim.scratch_b & 0x10) != 0
	var released := (sim.scratch_ac & 0x10) != 0 and not held
	if held and not pressed:
		if sim.l94_bhold[p] == 0:
			return false
		sim.l94_bhold[p] = maxi(sim.l94_bhold[p] - 1, 0)
		if sim.l94_bhold[p] == 0:
			take_goalie(sim, e, p)
			return true
		return false
	if pressed:
		sim.l94_bhold[p] = HOLD_STEPS
		return false
	if released:
		var old: int = sim.l94_bhold[p]
		sim.l94_bhold[p] = HOLD_STEPS
		if old != 0:
			sim.switch_to_nearest(e, p)
		else:
			take_goalie(sim, e, p)
		return true
	return false

## .31: the user takes his goalie (not when there is none or the other user has him)
static func take_goalie(sim: Sim, e: Entity, p: int) -> void:
	var g := own_goalie(sim, e)
	if g == null or (g.flags & Entity.F_USER) or g == e:
		return
	if p == 0:
		sim.user1_slot = sim.find_switch_target(g.slot, sim.user1_slot)
	else:
		sim.user2_slot = sim.find_switch_target(g.slot, sim.user2_slot)

## .33 / doinput_cbut / doinput_chkanim: the user's goalie: the third button with a direction dives
## (the PC game's dive on a loose puck), the shot button saves towards the puck (facing it, the PC
## game's choice of save), else he skates, kept to his crease
static func user_goalie(sim: Sim, e: Entity) -> void:
	var dir := sim.scratch_a & 0xf
	if (sim.scratch_b & 0x40) and dir < 8:
		AI._set_heading_word(e, dir)
		e.timer_c = 8
		e.flags |= Entity.F_BUSY
		e.flags2 |= Entity.F2_TURNING
		Anim.set_animation(e, 0x181)
		sim.add_crowd(0x96, 0x4b0)
		return
	if sim.scratch_b & 0x20:
		var puck := sim.puck
		AI._set_heading_word(e, Tables.direction8(Sim._s16(puck.xi - e.xi), Sim._s16(puck.yi - e.yi)) & 7)
		goalie_save(sim, e)
		return
	if crease_stop(sim, e):
		return
	sim.apply_skating(e, dir)

## doinput_chkanim: out to the side of the crease he stops going farther, in front of it he does not
## skate away from the net
static func crease_stop(_sim: Sim, e: Entity) -> bool:
	var stop := false
	if e.xi > CREASE_X and e.vx > 0:
		stop = true
		e.vx = 0
	if e.xi < -CREASE_X and e.vx < 0:
		stop = true
		e.vx = 0
	if absi(e.yi) < CREASE_Y and e.vy != 0 and (e.yi ^ e.vy) < 0:
		stop = true
		e.vy = 0
	return stop

## goaliesave: the PC game's save (ai_goalie loc_4c1ec) on the puck as it comes: the side by where it
## is against his facing, high or low by its height
static func goalie_save(sim: Sim, e: Entity) -> void:
	var puck := sim.puck
	e.vx = Sim._s16(e.vx) >> 1
	e.vy = Sim._s16(e.vy) >> 1
	var a := Sim._s16((Sim._s16(puck.vx) >> 10) + puck.xi - e.xi)
	var b := Sim._s16((Sim._s16(puck.vy) >> 10) + puck.yi - e.yi)
	var dd := Tables.direction8(a, b)
	var hw := AI._heading_word(e)
	var b0 := 0 if dd == 8 else ((dd - hw) & 7)
	if b0 == 4 and absi(puck.vy) + absi(puck.vx) <= 0x1200:
		a = 8
	else:
		if b0 == 0 or b0 == 4:
			if hw == 0:
				b0 = 7 if a < 0 else 1
			elif hw == 4:
				b0 = 1 if a < 0 else 7
			elif hw == 1 or hw == 5:
				b0 = 7 if absi(a) < absi(b) else 1
			elif hw == 3 or hw == 7:
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
	e.flags |= Entity.F_BUSY
	e.flags2 |= Entity.F2_TURNING
	Anim.set_animation(e, Tables.goalie_save_anims[a + 1])
	sim.add_crowd(0x96, 0x4b0)

## assgoaliectrl: a user's goalie on screen is his alone (the computer does not move him or make his
## saves); out of his zone the whistle goes. False: the computer plays him (off screen, or no user)
static func goalie_ctrl(sim: Sim, e: Entity) -> bool:
	if not sim.l94_manual_goalie or (e.flags & Entity.F_USER) == 0:
		return false
	if absi(e.yi) <= OUT_OF_ZONE_Y and not sim.play_stopped and not _queued(sim, Rules.INF_GOALIE_HOLD):
		Rules.queue_infraction(sim, e, Rules.INF_GOALIE_HOLD)
	if absi(e.xi - sim.camera_x) >= SCREEN_X or absi(e.yi - sim.camera_y) >= SCREEN_Y:
		return false
	if (e.flags2 & Entity.F2_TURNING) == 0 and (e.flags & Entity.F_BUSY) == 0:
		Anim.set_animation(e, 0x99 if sim.puck_carrier == e.slot else 1)
	if sim.play_stopped:
		return true
	# the PC game's hold of the puck (0x5a steps), the user's as the computer's
	if sim.puck_carrier == e.slot:
		if e.timer_b < 0:
			e.timer_b = 0x5a
		e.timer_b = Sim._s16(e.timer_b - 1)
		if e.timer_b < 0 and not _queued(sim, Rules.INF_GOALIE_HOLD):
			Rules.queue_infraction(sim, e, Rules.INF_GOALIE_HOLD)
	else:
		e.timer_b = -1
	return true

static func _queued(sim: Sim, type: int) -> bool:
	for i in 32:
		if Rules.inf_type(sim, i) == type:
			return true
	return false
