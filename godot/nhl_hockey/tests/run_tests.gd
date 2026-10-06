extends SceneTree
## Headless self test: godot --headless --path godot/nhl_hockey --script tests/run_tests.gd

var finished := false

## Autoloads are added to the tree after _init(), so the tests run from _initialize().
func _initialize() -> void:
	run_tests()
	finished = true

## Safety net: a script error inside run_tests() would otherwise leave the process running.
func _process(_delta: float) -> bool:
	if not finished:
		print("tests aborted by a script error")
		quit(3)
	return true

func fail(msg: String) -> void:
	print("FAIL ", msg)
	failures += 1

var failures := 0

## steps the simulation until the puck is dropped (play on) or the limit is reached
func run_until_play(sim: Sim, limit: int) -> int:
	for i in limit:
		sim.step(8, 8, 0, 0)
		if not sim.play_stopped:
			return i
	return -1

func run_tests() -> void:
	# RefPack: literal run, back reference, stop code
	var packed := PackedByteArray([0x10, 0xfb, 0, 0, 8, 0xe0, 0x41, 0x42, 0x43, 0x44, 0x00, 0x03, 0xfd, 0x5a])
	var out := RefPack.decompress(packed)
	if out.get_string_from_ascii() != "ABCDABCZ":
		fail("refpack: " + str(out))
	# tables
	if not Tables.loaded or Tables.anim_sequences.size() < 5000:
		print("FAIL tables not loaded")
		quit(2)
		return
	if Tables.direction8(0, 10) != 0 or Tables.direction8(10, 0) != 2 or Tables.direction8(0, -10) != 4 or Tables.direction8(-10, 0) != 6 or Tables.direction8(0, 0) != 8:
		fail("direction8")
	if Tables.position_default_state.size() != 7 or Tables.position_default_state[0] != 14 or Tables.position_default_state[4] != 5:
		fail("position_default_state " + str(Tables.position_default_state))
	# animation stepping: the 4 frame skating cycle (0x2e9, frames 41..44 facing up) re-triggered
	# every step like apply_skating does; the glide pose (0x289) is a single frame per direction
	var e := Entity.new()
	var frames := {}
	for i in 200:
		Anim.set_animation(e, Anim.SKATE)
		Anim.advance(e)
		frames[e.frame] = true
	if frames.size() != 4 or not frames.has(41) or not frames.has(44):
		fail("anim: frames " + str(frames.keys()))
	e = Entity.new()
	e.facing = 2
	Anim.set_animation(e, Anim.GLIDE)
	Anim.advance(e)
	if e.frame != 10:
		fail("glide frame for facing 2: " + str(e.frame))
	# a new game lines up for the opening faceoff and drops the puck within a few seconds
	var sim := Sim.new()
	if not sim.play_stopped:
		fail("game should start with a stoppage")
	var dropped := run_until_play(sim, 1200)
	if dropped < 0:
		fail("no faceoff within 1200 steps (puck state %d ref state %d)" % [sim.puck.state(), sim.referee.state()])
	else:
		print("faceoff after ", dropped, " steps")
	var centre := sim.entities[sim.user1_slot]
	if sim.user1_slot != 4 or centre.line_slot != 4:
		fail("user should control the home centre, has slot %d" % sim.user1_slot)
	if absi(sim.puck.xi) > 4 or absi(sim.puck.yi) > 4:
		fail("puck not at centre ice after the drop: %d,%d" % [sim.puck.xi, sim.puck.yi])
	# play on: everybody stays inside the boards, the CPU players move, the clock runs
	var moved := 0
	var clock0 := sim.clock_seconds
	for i in 600:
		sim.step(8, 8, 0, 0)
		for j in 12:
			var p := sim.entities[j]
			if p.line_slot >= 0 and (absi(p.xi) > 160 or absi(p.yi) > 264):
				fail("player %d left the rink: %d,%d at step %d" % [j, p.xi, p.yi, i])
				break
		if absi(sim.puck.xi) > 170 or absi(sim.puck.yi) > 270:
			fail("puck left the rink: %d,%d" % [sim.puck.xi, sim.puck.yi])
			break
	for j in 12:
		var p := sim.entities[j]
		var pos := Rules.faceoff_position(sim, p)
		if absi(p.xi - pos.x) + absi(p.yi - pos.y) > 10:
			moved += 1
	if moved < 6 and not sim.play_stopped:
		fail("only %d CPU players moved" % moved)
	if sim.clock_seconds == clock0 and not sim.play_stopped:
		fail("the clock does not run")
	print("after 600 steps: carrier %d puck %d,%d clock %d:%02d stopped %s" % [sim.puck_carrier, sim.puck.xi, sim.puck.yi, sim.clock_seconds / 60, sim.clock_seconds % 60, sim.play_stopped])
	# skating control: the user skates up-right and must stay inside the boards
	sim = Sim.new()
	run_until_play(sim, 1200)
	var p1 := sim.entities[sim.user1_slot]
	var maxx := 0
	var maxy := 0
	for i in 400:
		sim.step(1, 8, 0, 0)
		maxx = maxi(maxx, absi(p1.xi))
		maxy = maxi(maxy, absi(p1.yi))
	if maxx < 40 or maxy < 40:
		fail("user did not skate far enough: %d,%d" % [maxx, maxy])
	# a shot from the slot into the empty net scores
	sim = Sim.new()
	run_until_play(sim, 1200)
	var shooter := sim.entities[sim.user1_slot]
	for i in 6:
		var g := sim.entities[6 + i]
		if g.line_slot == 0:
			g.line_slot = -1        # pull the away goalie
	shooter.set_pos(0, 150)
	shooter.vx = 0
	shooter.vy = 0
	shooter.heading = 0
	sim.puck.set_pos(0, 158)
	sim.puck.vx = 0
	sim.puck.vy = 0
	sim.puck_carrier = shooter.slot
	shooter.set_state(Entity.State.NEAREST)
	var home_goals := sim.teams[0].goals
	sim.step(0, 8, 0x20, 0)        # B: start the shot
	for i in 40:
		sim.step(0, 8, 0, 0)
	if sim.puck_carrier == shooter.slot:
		fail("the shot was not released (anim %x pos %d)" % [shooter.anim, shooter.anim_pos])
	var scored := false
	for i in 300:
		sim.step(8, 8, 0, 0)
		if sim.teams[0].goals > home_goals:
			scored = true
			break
	if not scored:
		fail("no goal: puck %d,%d v %d,%d carrier %d stopped %s infractions %s" % [sim.puck.xi, sim.puck.yi, sim.puck.vx, sim.puck.vy, sim.puck_carrier, sim.play_stopped, str(sim.infractions)])
	else:
		print("goal scored, home %d away %d" % [sim.teams[0].goals, sim.teams[1].goals])
		# after the goal the play stops and a new faceoff follows at centre ice
		var again := run_until_play(sim, 2400)
		if again < 0:
			fail("no faceoff after the goal (puck state %d ref state %d phase %d)" % [sim.puck.state(), sim.referee.state(), sim.ref_phase])
		elif absi(sim.faceoff_x) > 0 or absi(sim.faceoff_y) > 0:
			fail("faceoff after a goal should be at centre ice, is at %d,%d" % [sim.faceoff_x, sim.faceoff_y])
	# a short period ends, the teams switch ends and the next period starts with a faceoff
	sim = Sim.new()
	sim.period_length = 5
	sim.clock_seconds = 5
	var period_steps := -1
	for i in 6000:
		sim.step(8, 8, 0, 0)
		if sim.period == 1 and not sim.play_stopped:
			period_steps = i
			break
	if period_steps < 0:
		fail("the second period did not start (period %d clock %d stopped %s puck %s ref %s)" % [sim.period, sim.clock_seconds, sim.play_stopped, Tables.ai_state_names[sim.puck.state() + 1], Tables.ai_state_names[sim.referee.state() + 1]])
	elif not sim.ends_switched or (sim.entities[0].flags & Entity.F_ATTACK_UP) != 0 or (sim.entities[6].flags & Entity.F_ATTACK_UP) == 0:
		fail("ends not switched in the second period")
	else:
		print("second period after ", period_steps, " steps")
	# a long simulation must not throw and must keep everybody on the rink
	sim = Sim.new()
	var stoppages := 0
	var was_stopped := sim.play_stopped
	for i in 6000:
		var c := 8
		if i % 7 == 0:
			c = (i / 7) & 7
		sim.step(c, 8, 0x20 if i % 97 == 0 else 0, 0)
		if sim.play_stopped and not was_stopped:
			stoppages += 1
		was_stopped = sim.play_stopped
	print("6000 steps: %d stoppages, score %d-%d, clock %d:%02d, period %d" % [stoppages, sim.teams[0].goals, sim.teams[1].goals, sim.clock_seconds / 60, sim.clock_seconds % 60, sim.period])
	print("tests finished, failures: ", failures)
	quit(1 if failures else 0)
