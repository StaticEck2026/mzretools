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
	# a hooking minor: the player serves 2 minutes in the box and his team plays short handed
	sim = Sim.new()
	run_until_play(sim, 1200)
	var culprit := sim.entities[7]
	Rules.maybe_queue_infraction(sim, culprit, Rules.INF_HOOKING)
	var in_box := false
	var back := false
	var short_handed_faceoff := false
	for i in 6000:
		sim.step(8, 8, 0, 0)
		if culprit.state() == Entity.State.DOOR_OPEN and culprit.line_slot < 0:
			in_box = true
		if in_box and sim.faceoff_pending and sim.teams[1].skaters_on_ice == 5:
			short_handed_faceoff = true
		if in_box and culprit.line_slot > 0 and culprit.state() != Entity.State.EXIT_PENALTY_BOX and culprit.state() != Entity.State.DOOR_OPEN:
			back = true
			break
	if not in_box:
		fail("penalized player never reached the box (state %s line %d pos %d,%d penalties %s)" % [Tables.ai_state_names[culprit.state() + 1], culprit.line_slot, culprit.xi, culprit.yi, str(sim.teams[1].penalties)])
	elif not short_handed_faceoff:
		fail("no short handed faceoff (skaters %d)" % sim.teams[1].skaters_on_ice)
	elif not back:
		fail("penalized player did not return (state %s penalties %s clock %d)" % [Tables.ai_state_names[culprit.state() + 1], str(sim.teams[1].penalties), sim.clock_seconds])
	else:
		print("penalty served, player back at %d,%d after %d game seconds" % [culprit.xi, culprit.yi, 300 - sim.clock_seconds])
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
	asset_tests()
	print("tests finished, failures: ", failures)
	quit(1 if failures else 0)

## Tests against the original game files (re/nhl_hockey of the repository or NHL_GAME_DIR)
func asset_tests() -> void:
	# the autoload is not a global identifier in --script mode: instantiate the script directly
	var GF := load("res://autoload/GameFiles.gd")
	var gf: Node = GF.new()
	var dir := OS.get_environment("NHL_GAME_DIR")
	if dir == "" or not DirAccess.dir_exists_absolute(dir):
		dir = GF.repository_game_dir()
	if dir != "":
		gf.set_game_dir(dir, false)
	if not gf.available():
		fail("game files not found (re/nhl_hockey or NHL_GAME_DIR)")
		return
	print("game files: ", gf.game_dir)
	# sprite banks: 1134 run length coded frames; frame 0 is 16x32 with the hotspot (8, 25)
	var frames := {}
	for i in 23:
		var data: PackedByteArray = gf.read_bank(GF.sprite_bank_name(i))
		var bank := Shpi.parse(data)
		if bank == null:
			fail("sprite bank %s missing or unreadable" % GF.sprite_bank_name(i))
			continue
		for s in bank.shapes:
			if s.is_image() and s.name.is_valid_int():
				frames[int(s.name)] = s
	if frames.size() != 1134:
		fail("expected 1134 sprite frames, got %d" % frames.size())
	else:
		var f0: Shpi.Shape = frames[0]
		if f0.width != 16 or f0.height != 32 or f0.center_x != 8 or f0.center_y != 25 or f0.transparent != 0xff:
			fail("frame 0: %dx%d hotspot %d,%d" % [f0.width, f0.height, f0.center_x, f0.center_y])
		var opaque := 0
		for p in f0.pixels:
			if p != 0xff:
				opaque += 1
		if opaque < 100 or opaque > 400:
			fail("frame 0 has %d opaque pixels" % opaque)
		var net: Shpi.Shape = frames[404]
		if net.width != 50 or net.height != 36:
			fail("net frame 404 is %dx%d" % [net.width, net.height])
	# palette: RINKPAL plus the jersey blocks, remap tables of blit_sprite
	var pal := GamePalette.build(gf.read_raw("rinkpal.qfs"), gf.read_raw("homepals.bin"), gf.read_raw("awaypals.bin"), 0, 4)
	if pal == null or pal.colors.size() != 256:
		fail("palette not built")
	else:
		# the jersey indices 0x85..0xc4 of the frames go to the home block 0x80..0xbf / away block 0xc0..0xff
		if pal.colors[0] != Color.BLACK or pal.remap[0][0x90] < 0x80 or pal.remap[0][0x90] > 0xbf or pal.remap[1][0x90] < 0xc0:
			fail("palette/remap values: %s %d %d" % [pal.colors[0], pal.remap[0][0x90], pal.remap[1][0x90]])
		if pal.remap_mirrored[0][0xc0] != pal.remap[0][0xc4]:
			fail("mirrored remap swap")
	# rink surface with the Boston logo at the centre
	var rink_bank := Shpi.parse(gf.read_bank("rink"))
	var rink_shape := rink_bank.find("rink") if rink_bank != null else null
	if rink_shape == null or rink_shape.width != 384 or rink_shape.height != 592 or rink_shape.code != 0x7b:
		fail("rink shape missing")
	elif pal != null:
		var img := RinkTiles.compose(rink_shape, gf.read_raw("bos.til"), gf.read_raw("bos.map"), 0, pal.colors)
		if img == null or img.get_width() != 384:
			fail("rink composition")
		else:
			var centre := img.get_pixel(192, 320)
			var ice := img.get_pixel(192, 200)
			if centre == ice:
				fail("centre ice logo not drawn (centre %s ice %s)" % [centre, ice])
	# HUD shapes and fonts
	var scrbrd := Shpi.parse(gf.read_bank("scrbrd1"))
	if scrbrd == null or scrbrd.find("0000") == null or scrbrd.find("hlin") == null or scrbrd.find("1009") == null:
		fail("scoreboard shapes")
	var font := Vfn.parse(gf.read("hilight.vfn"))
	if font == null or font.text_width("A") != 10 or font.render("A", Color.WHITE).get_pixel(4, 0).a < 0.5:
		fail("HILIGHT font glyphs")
	# databases: Boston's roster, lines and ratings
	var db := Database.open(gf.read_raw("teams.db"), gf.read_raw("key.db"), gf.read_raw("att.db"))
	if db == null or db.team_count() != 28:
		fail("databases")
	else:
		var bos := db.load_team(0)
		var det := db.load_team(4)
		if bos.abbrev != "BOS" or bos.city != "Boston Bruins" or bos.name != "Boston" or det.abbrev != "DET":
			fail("team names: %s / %s / %s" % [bos.abbrev, bos.city, bos.name])
		var bourque: Database.Player = bos.skaters[10]
		if bourque == null or bourque.full_name() != "Ray Bourque" or bourque.number != 77 or bourque.position != "D" or bourque.ratings.size() != 0x14 or bourque.ratings[0] != 1:
			fail("Ray Bourque not found in the Boston roster")
		var casey: Database.Player = bos.goalies[0]
		if casey == null or casey.last != "Casey" or casey.number != 30 or not casey.goalie or casey.ratings.size() != 0x10:
			fail("Jon Casey not found")
		if bos.forwards[0] != [18, 7, 16] or bos.defense[0] != [4, 10] or bos.goalie_order[0] != 25:
			fail("Boston lines: %s %s %s" % [bos.forwards[0], bos.defense[0], bos.goalie_order])
		# a game between the two teams: the first lines are dressed with their ratings
		var sim := Sim.new()
		sim.set_teams(bos, det)
		var centre := sim.entities[4]
		if centre.number != 12 or centre.roster_idx != 7 or centre.left_handed != 0 or (centre.flags4 & Entity.F4_MIRROR) == 0:
			fail("Adam Oates should centre the first line: number %d roster %d" % [centre.number, centre.roster_idx])
		var bourque_e := sim.entities[2]
		if bourque_e.number != 77 or bourque_e.speed_skill != 10 or bourque_e.weight != 10 or bourque_e.shot_skill != 13 or bourque_e.reaction != 8:
			fail("Bourque ratings: speed %d weight %d shot %d reaction %d" % [bourque_e.speed_skill, bourque_e.weight, bourque_e.shot_skill, bourque_e.reaction])
		if sim.entities[0].number != 30 or sim.entities[6].line_slot != 0:
			fail("goalies not dressed")
		run_until_play(sim, 1200)
		for i in 3000:
			sim.step(8, 8, 0, 0)
		print("BOS - DET after 3000 steps: %d-%d, clock %d:%02d" % [sim.teams[0].goals, sim.teams[1].goals, sim.clock_seconds / 60, sim.clock_seconds % 60])
	# sound effects: 30 digital samples, the goal horn (0x9c) is the 7 second sample
	var snd := Sounds.load_bank(gf.read_raw("pcff001.pat"), gf.read_raw("pcff001.tim"), gf.read_raw("pcff001.dig"))
	if snd == null or snd.sample_count != 30 or snd.timbre_count != 30:
		fail("sound bank")
	else:
		var horn := snd.stream(0x9c)
		if horn == null or horn.data.size() != 77078 or horn.mix_rate != 11025:
			fail("goal horn sample")
		var crowd := snd.stream(0x7d)
		if crowd == null or crowd.loop_mode != AudioStreamWAV.LOOP_FORWARD or crowd.loop_end != 9971:
			fail("crowd loop")
		if not snd.has(0x90) or not snd.has(0xa4) or snd.effects.size() < 30:
			fail("effect ids: %d" % snd.effects.size())
