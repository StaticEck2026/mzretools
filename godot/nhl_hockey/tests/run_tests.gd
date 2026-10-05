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

func run_tests() -> void:
	var failures := 0
	# RefPack: literal run, back reference, stop code
	var packed := PackedByteArray([0x10, 0xfb, 0, 0, 8, 0xe0, 0x41, 0x42, 0x43, 0x44, 0x00, 0x03, 0xfd, 0x5a])
	var out := RefPack.decompress(packed)
	if out.get_string_from_ascii() != "ABCDABCZ":
		print("FAIL refpack: ", out)
		failures += 1
	# tables
	if not Tables.loaded or Tables.anim_sequences.size() < 5000:
		print("FAIL tables not loaded")
		quit(2)
		return
	if Tables.direction8(0, 10) != 0 or Tables.direction8(10, 0) != 2 or Tables.direction8(0, -10) != 4 or Tables.direction8(-10, 0) != 6 or Tables.direction8(0, 0) != 8:
		print("FAIL direction8: ", Tables.direction8(0, 10), Tables.direction8(10, 0), Tables.direction8(0, -10), Tables.direction8(-10, 0))
		failures += 1
	# animation stepping: the 4 frame skating cycle (0x2e9, frames 41..44 facing up) re-triggered
	# every step like apply_skating does; the glide pose (0x289) is a single frame per direction
	var e := Entity.new()
	var frames := {}
	for i in 200:
		Anim.set_animation(e, Anim.SKATE)
		Anim.advance(e)
		frames[e.frame] = true
	if frames.size() != 4 or not frames.has(41) or not frames.has(44):
		print("FAIL anim: frames ", frames.keys(), " anim ", e.anim)
		failures += 1
	e = Entity.new()
	e.facing = 2
	Anim.set_animation(e, Anim.GLIDE)
	Anim.advance(e)
	if e.frame != 10:
		print("FAIL glide frame for facing 2: ", e.frame)
		failures += 1
	# simulation: skate the controlled player up-right for 600 steps, it must stay inside the boards
	var sim := Sim.new()
	sim.user1_slot = 1
	var maxx := 0
	var maxy := 0
	for i in 600:
		sim.step(1, 8, 0, 0)
		var p := sim.entities[1]
		maxx = maxi(maxx, absi(p.xi))
		maxy = maxi(maxy, absi(p.yi))
		if absi(p.xi) > 160 or absi(p.yi) > 264:
			print("FAIL player left the rink: ", p.xi, ",", p.yi, " at step ", i)
			failures += 1
			break
	if maxx < 50 or maxy < 50:
		print("FAIL player did not move far enough: ", maxx, ",", maxy)
		failures += 1
	# puck pickup, pass and shot
	sim = Sim.new()
	sim.user1_slot = 1
	sim.entities[1].set_pos(0, -12)
	for i in 30:
		sim.step(0, 8, 0, 0)
	if sim.puck_carrier != 1:
		print("FAIL puck not picked up, carrier ", sim.puck_carrier, " puck ", sim.puck.xi, ",", sim.puck.yi, " player ", sim.entities[1].xi, ",", sim.entities[1].yi)
		failures += 1
	sim.step(0, 8, 0x20, 0)   # shoot
	if sim.puck_carrier != -1 or sim.puck.vy <= 0:
		print("FAIL shot: carrier ", sim.puck_carrier, " vy ", sim.puck.vy)
		failures += 1
	for i in 400:
		sim.step(8, 8, 0, 0)
	if absi(sim.puck.xi) > 162 or absi(sim.puck.yi) > 266:
		print("FAIL puck left the rink: ", sim.puck.xi, ",", sim.puck.yi)
		failures += 1
	print("tests finished, failures: ", failures, " (puck ended at ", sim.puck.xi, ",", sim.puck.yi, ")")
	quit(1 if failures else 0)
