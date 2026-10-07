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
	if OS.get_environment("AI_STATE") != "":       # only the AI golden test
		ai_golden()
		print("tests finished, failures: ", failures)
		quit(1 if failures else 0)
		return
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
	# randomrange: the 32 bit LCG of the original from its initial seed 0xabcd4321
	var rsim := Sim.new()
	rsim.seed = 0xabcd4321
	var rolls := []
	for i in 5:
		rolls.append(rsim.random(100))
	if rolls != [64, 55, 7, 45, 74]:
		fail("randomrange sequence " + str(rolls))
	# ai_choose_direction: a skater in front of the top net heading behind it goes to the front of
	# the net first; one beside the net goes down the right side; a path clear of the nets is kept
	var nz := AI.net_zone_flags(0, 150, 0, 240, 0xc5, 0xfc, 0x2c)
	if nz != [true, 4, 0]:
		fail("net_zone_flags " + str(nz))
	var sk := rsim.entities[1]
	sk.line_slot = 1
	sk.set_state(Entity.State.DEF_OFFENSE)
	sk.flags |= Entity.F_ATTACK_UP
	sk.set_pos(0, 150)
	var cd := AI.choose_direction(rsim, sk, 0, 260)
	if cd != Vector2i(0, 0xc4):
		fail("choose_direction in front of the net: " + str(cd))
	sk.set_pos(60, 220)
	cd = AI.choose_direction(rsim, sk, 0, 260)
	if cd != Vector2i(0x36, 260):
		fail("choose_direction beside the net: " + str(cd))
	sk.set_pos(0, 0)
	cd = AI.choose_direction(rsim, sk, 0, 100)
	if cd != Vector2i(0, 100):
		fail("choose_direction clear path: " + str(cd))
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
	if sim.user1_slot < 0 or sim.user1_slot > 5 or centre.line_slot != 4:
		fail("user should control the home centre, has slot %d (line slot %d)" % [sim.user1_slot, centre.line_slot if sim.user1_slot >= 0 else -9])
	if absi(sim.puck.xi) > 4 or absi(sim.puck.yi) > 4:
		fail("puck not at centre ice after the drop: %d,%d" % [sim.puck.xi, sim.puck.yi])
	# play on: everybody stays inside the boards, the CPU players move, the clock runs
	var moved := 0
	var clock0 := sim.clock_seconds
	for i in 600:
		sim.step(8, 8, 0, 0)
		for j in 12:
			var p := sim.entities[j]
			var at_door := p.state() in [Entity.State.BENCH, Entity.State.BENCH_WAIT, Entity.State.EXIT_BENCH,
				Entity.State.PENALTY_BOX, Entity.State.DOOR_OPEN, Entity.State.EXIT_PENALTY_BOX]
			if p.line_slot >= 0 and not at_door and (absi(p.xi) > 160 or absi(p.yi) > 264):
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
	# a shot from the slot into the empty net scores: the shot height is random (a high one goes
	# over the net, as in the original), so a few seeds of randomrange are tried
	var scored := false
	var shooter: Entity = null
	var tries := 0
	for seed_try: int in [0xabcd4321, 1, 2, 3, 4, 5, 6, 7]:
		tries += 1
		sim = Sim.new()
		run_until_play(sim, 1200)
		sim.seed = seed_try
		shooter = sim.entities[sim.user1_slot]
		for i in 6:
			var g := sim.entities[6 + i]
			if g.line_slot == 0:
				g.line_slot = -1        # pull the away goalie: off the ice (the puck checks every
				g.set_pos(-0xc0, 0)     # entity near it in the draw order, like the original)
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
		sim.step(0x20, 8, 0x20, 0)     # B down: start the shot (aimed up the ice, direction 0)
		for i in 40:
			sim.step(0, 8, 0, 0)       # B up: a quick wrist shot
		if sim.puck_carrier == shooter.slot:
			fail("the shot was not released (anim %x pos %d)" % [shooter.anim, shooter.anim_pos])
			break
		for i in 300:
			sim.step(8, 8, 0, 0)
			if sim.teams[0].goals > home_goals:
				scored = true
				break
		if scored:
			break
	if not scored:
		fail("no goal: puck %d,%d v %d,%d carrier %d stopped %s infractions %s" % [sim.puck.xi, sim.puck.yi, sim.puck.vx, sim.puck.vy, sim.puck_carrier, sim.play_stopped, str(sim.infq.slice(0, 8))])
	else:
		print("goal scored, home %d away %d (seed try %d)" % [sim.teams[0].goals, sim.teams[1].goals, tries])
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
	for i in 12000:
		sim.step(8, 8, 0, 0)
		if culprit.state() == Entity.State.DOOR_OPEN and culprit.line_slot < 0:
			in_box = true
		if in_box and sim.faceoff_pending and sim.teams[1].skaters_on_ice == 5:
			short_handed_faceoff = true
		if in_box and culprit.line_slot > 0 and culprit.state() != Entity.State.EXIT_PENALTY_BOX and culprit.state() != Entity.State.DOOR_OPEN:
			back = true
			break
	if not in_box:
		fail("penalized player never reached the box (state %s line %d pos %d,%d penalties %s)" % [Tables.ai_state_names[culprit.state() + 1], culprit.line_slot, culprit.xi, culprit.yi, str(sim.teams[1].box_list())])
	elif not short_handed_faceoff:
		fail("no short handed faceoff (skaters %d)" % sim.teams[1].skaters_on_ice)
	elif not back:
		fail("penalized player did not return (state %s penalties %s clock %d)" % [Tables.ai_state_names[culprit.state() + 1], str(sim.teams[1].penalties), sim.clock_seconds])
	else:
		print("penalty served, player back at %d,%d after %d game seconds" % [culprit.xi, culprit.yi, 300 - sim.clock_seconds])
	# two users: user 2 plays the away team with his own controls; on the same team the second user
	# takes another skater
	sim = Sim.new()
	sim.user2_team = 2
	sim.assign_users()
	if sim.user2_slot < 6 or sim.entities[sim.user2_slot].line_slot != 4:
		fail("user 2 should control the away centre, slot %d" % sim.user2_slot)
	run_until_play(sim, 1200)
	for i in 60:
		sim.step(8, 6, 0, 0)          # user 2 skates left (he follows the puck to other skaters)
	var p2 := sim.entities[sim.user2_slot]
	if p2.vx >= -0x200 or (p2.flags & Entity.F_PLAYER2) == 0:
		fail("user 2 did not skate left: slot %d vx %d" % [p2.slot, p2.vx])
	sim = Sim.new()
	sim.user2_team = 1
	sim.assign_users()
	if sim.user2_slot < 0 or sim.user2_slot == sim.user1_slot or sim.user2_slot >= 6 or (sim.entities[sim.user2_slot].flags & Entity.F_PLAYER2):
		fail("co-op: user 2 slot %d user 1 slot %d" % [sim.user2_slot, sim.user1_slot])
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
	gf.use_data = false
	var dir := OS.get_environment("NHL_GAME_DIR")
	if dir == "" or not DirAccess.dir_exists_absolute(dir):
		dir = GF.repository_game_dir()
	if dir != "":
		gf.set_game_dir(dir, false)
	if not gf.available():
		fail("game files not found (re/nhl_hockey or NHL_GAME_DIR)")
		return
	print("game files: ", gf.game_dir)
	# the executable's tables (the drivers' note tables, the menus ...)
	Exe.load_from(gf.read_raw("hockey.exe"))
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
		var centre := sim.entities[sim.user1_slot]
		if centre.line_slot != 4 or centre.number != 12 or centre.roster_idx != 7 or centre.left_handed != 0 or (centre.flags4 & Entity.F4_MIRROR) == 0:
			fail("Adam Oates should centre the first line: number %d roster %d" % [centre.number, centre.roster_idx])
		var bourque_e: Entity = null
		var dressed := []
		for i in 6:
			dressed.append(sim.entities[i].roster_idx)
			if sim.entities[i].roster_idx == 10:
				bourque_e = sim.entities[i]
		if bourque_e == null or bourque_e.line_slot != 2 or bourque_e.number != 77 or bourque_e.speed_skill != 10 or bourque_e.weight != 10 or bourque_e.shot_skill != 13 or bourque_e.reaction != 7:
			# reaction: rating 13 + 2 home ice (TEAMS.DB +0x2de = 7), stored inverted ((15 ^ 15) + 15) >> 1
			fail("Bourque (RD) ratings: %s reaction %d" % [str(dressed), bourque_e.reaction if bourque_e != null else -1])
		dressed.sort()
		if dressed != [4, 7, 10, 16, 18, 25]:
			fail("Boston's first line is not dressed: %s" % str(dressed))
		if sim.teams[0].entity_of[25] != -1 or sim.teams[0].entity_of[26] != -2 or sim.teams[0].entity_of[22] != -3:
			fail("entity_of bookkeeping: %d %d %d" % [sim.teams[0].entity_of[25], sim.teams[0].entity_of[26], sim.teams[0].entity_of[22]])
		var det_goalie := -1
		for i in range(6, 12):
			if sim.entities[i].line_slot == 0:
				det_goalie = sim.entities[i].roster_idx
		if det_goalie != det.goalie_order[0]:
			fail("Detroit's starting goalie %d not dressed (%d)" % [det.goalie_order[0], det_goalie])
		run_until_play(sim, 1200)
		for i in 3000:
			sim.step(8, 8, 0, 0)
		print("BOS - DET after 3000 steps: %d-%d, clock %d:%02d" % [sim.teams[0].goals, sim.teams[1].goals, sim.clock_seconds / 60, sim.clock_seconds % 60])
		line_change_tests(bos, det)
		match_rules_tests(bos, det)
		ceremony_tests(bos, det)
		replay_tests(bos, det)
		crowd_tests(bos, det)
		save_tests(bos, det)
		speech_tests(bos, det, gf)
	# sound effects: 30 digital samples found by their ids, the goal horn (0x9c) is the 7 second
	# sample; the post (0xac) is the 22050 Hz recording played at 11025 Hz two semitones down
	var snd := Sounds.load_bank(gf.read_raw("pcff001.pat"), gf.read_raw("pcff001.tim"), gf.read_raw("pcff001.dig"))
	if snd == null or snd.sample_count != 30 or snd.timbre_count != 30:
		fail("sound bank")
	else:
		var horn := snd.stream(0x9c)
		if horn == null or horn.data.size() != 77078 or horn.mix_rate != 11025:
			fail("goal horn sample")
		var crowd := snd.stream(0x7d)
		# the timbre's +0x18 is the loop start, +0x1c its length (mix_voice_sample)
		if crowd == null or crowd.loop_mode != AudioStreamWAV.LOOP_FORWARD or crowd.loop_begin != 3856 or crowd.loop_end != 3856 + 9971:
			fail("crowd loop")
		var post := snd.stream(0xac)
		if post == null or post.data.size() != 7040 or post.mix_rate != 9822:
			fail("post sample: %s" % str([post.data.size(), post.mix_rate] if post != null else null))
		if snd.has(0x90) or not snd.has(0x91) or not snd.has(0xa4) or snd.effects.size() != 33 or snd.has(0xab):
			fail("effect ids: %d" % snd.effects.size())
		if absf(snd.lengths.get(0x97, 0.0) - 0.36) > 0.001 or absf(snd.lengths.get(0x7b, 0.0) - 1.6) > 0.001:
			fail("effect note lengths")
		audio_tests(gf, snd)
		sound_card_tests(gf)
		opl2_tests()
		golden_tests(gf)
	league_tests(gf)

## the sound cards (load_sound_config): the Sound Blaster's digital driver and its mixer (the
## effects on voices 0 / 1, the crowd's roar and murmur on 2 / 3), the AdLib's FM effects, the PC
## speaker driver and the MT-32's MIDI stream
func sound_card_tests(gf: Node) -> void:
	var reader := func(n: String) -> PackedByteArray: return gf.read_raw(n)
	var sb := MusicPlayer.new()
	if not sb.setup_card(2, reader) or sb.dac == null or sb.driver == null:
		fail("Sound Blaster setup")
		sb.free()
		return
	# the goal horn: drum note 0x40 on channel 9 plays record 0x9c (voices 0 / 1)
	sb.play_effect(0x9c)
	var m0: DacDriver.MixVoice = sb.dac.mix[0]
	if m0.active != 1 or sb.dac.voices[0].owner != 9 or m0.data.size() != 77078 or m0.step != 0x10000:
		fail("goal horn voice: %s" % str([m0.active, sb.dac.voices[0].owner, m0.data.size(), m0.step]))
	# update_ambient_audio: crowd 0x300 -> roar volume 25 on voice 2, murmur 74 on voice 3 bent to 56
	sb.ambient(0x300, 50, true)
	var m2: DacDriver.MixVoice = sb.dac.mix[2]
	var m3: DacDriver.MixVoice = sb.dac.mix[3]
	if m2.active != 1 or m2.volume != 25 or m3.active != 1 or m3.volume != 74 or sb.dac.channels[7].bend != 56 * 256 - 0x4000:
		fail("crowd voices: %s" % str([m2.active, m2.volume, m3.active, m3.volume, sb.dac.channels[7].bend]))
	if m2.loop_start != 3856 or m2.loop_end != 3856 + 9971:
		fail("roar loop %d..%d" % [m2.loop_start, m2.loop_end])
	var out := sb.render(int(MusicPlayer.RATE))
	var peak := 0.0
	var energy := 0.0
	for x in out:
		peak = maxf(peak, absf(x))
		energy += x * x
	if sqrt(energy / out.size()) < 0.01 or peak > 1.0:
		fail("Sound Blaster output: rms %.3f peak %.3f" % [sqrt(energy / out.size()), peak])
	# the level falls by 30 a tick: the roar stops (voice 2 stops at its note off), the murmur stays
	sb.ambient(0, 1000, true)
	if m2.active != 0 or m3.active != 1 or m3.volume != 10:
		fail("crowd down: %s" % str([m2.active, m3.active, m3.volume]))
	# a speech clip on voice 1 (playsample_raw_loop: the delta coded clip at 11025 Hz)
	var viv := Viv.parse(gf.read_raw("xbruce2.viv"))
	var clip := viv.samples("goalnum.cor")
	sb.play_sample(1, clip[0], clip[1], 0x7f)
	if (sb.dac.mix[1] as DacDriver.MixVoice).active != 1 or sb.sample_done(1):
		fail("speech voice")
	# a recording of the front end on voice 3: the 22050 Hz recording stepped by 2 at 11025 Hz
	var rec := Sounds.load_sample(gf.read_raw("tonights.iff"))
	sb.play_sample(3, rec.data, rec.mix_rate, 0x4c, rec.loop_begin, rec.loop_end - rec.loop_begin)
	var m3r: DacDriver.MixVoice = sb.dac.mix[3]
	if m3r.active != 1 or m3r.step != 0x20000 or m3r.volume != 0x4c or m3r.loop_len == 0:
		fail("recording voice: %s" % str([m3r.active, m3r.step, m3r.volume, m3r.loop_len]))
	sb.free()
	# the AdLib: the horn is an FM timbre of PCFF002.TIM (type 2) on the OPL2, no crowd
	var ad := MusicPlayer.new()
	if not ad.setup_card(4, reader) or ad.dac != null or ad.driver == null:
		fail("AdLib setup")
	else:
		ad.play_effect(0x9c)
		var horn := false
		for v: FmDriver.Voice in ad.driver.voices:
			if v.allocated and v.channel == 9 and v.program == 0x9c:
				horn = true
		if not horn:
			fail("AdLib horn")
		ad.ambient(0x300, 50, true)
		if ad.roar != 0 or ad.murmur != 0:
			fail("AdLib has no crowd")
	ad.free()
	# the PC speaker: one voice, the envelope ends the note; the gate opens with the note's divisor
	var pc := MusicPlayer.new()
	if not pc.setup_card(1, reader) or pc.speaker == null:
		fail("PC speaker setup")
	else:
		pc.play_effect(0x9c)
		var v1: PcSpeaker.Voice = pc.speaker.voices[1]
		if v1.active != 1 or v1.timbre.size() < 0x43:
			fail("speaker voice")
		pc._tick()
		if not pc.speaker.gate or pc.speaker.out_div <= 0:
			fail("speaker gate")
		var t := 0
		while v1.active != 0 and t < 1000:
			pc._tick()
			t += 1
		pc._tick()
		if v1.active != 0 or pc.speaker.gate:
			fail("speaker note did not end (%d ticks)" % t)
	pc.free()
	# the MT-32: MT32HOCK.KMS's system exclusive messages at the start, the horn a rhythm note
	var mt := MusicPlayer.new()
	if not mt.setup_card(8, reader) or mt.mt32 == null:
		fail("MT-32 setup")
	else:
		if mt.mt32.sysex_count < 10:
			fail("MT32HOCK set-up: %d messages" % mt.mt32.sysex_count)
		mt.play_effect(0x9c)
		var st := mt.mt32.stream
		if st.size() < 3 or Array(st.slice(st.size() - 3)) != [0x99, 0x40, 0x7f]:
			fail("MT-32 horn bytes: %s" % str(Array(st.slice(maxi(st.size() - 6, 0)))))
		print("sound cards: SB / AdLib / speaker / MT-32 checked (%d MT-32 set-up messages)" % mt.mt32.sysex_count)
	mt.free()

## the OPL2: the ROM tables, a note's attack and release, the waveforms; the native chip (when its
## library is loaded) against the GDScript one, sample for sample
func opl2_tests() -> void:
	var chip := Opl2.new(22050.0, false)
	if Opl2.logsin[0] != 0x859 or Opl2.logsin[255] != 0 or Opl2.exprom[0] != 0x7fa or Opl2.exprom[255] != 0x400:
		fail("OPL2 ROM tables: %x %x %x %x" % [Opl2.logsin[0], Opl2.logsin[255], Opl2.exprom[0], Opl2.exprom[255]])
	var setup := func(c) -> void:
		c.write(0x01, 0x20)
		c.write(0xbd, 0xc0)
		for r in [[0x20, 0x21, 0xe1], [0x40, 0x1a, 0x00], [0x60, 0xf4, 0x83], [0x80, 0x37, 0x46], [0xe0, 0x01, 0x02]]:
			c.write(r[0], r[1])
			c.write(r[0] + 3, r[2])
		c.write(0xc0, 0x0a)
		c.write(0xa0, 0x58)
		c.write(0xb0, 0x31)
		# a second channel with additive synthesis and vibrato / tremolo
		for r in [[0x21, 0xe2], [0x24, 0xc1], [0x41, 0x05], [0x44, 0x00], [0x61, 0xa5], [0x64, 0xd3], [0x81, 0x28], [0x84, 0x1a]]:
			c.write(r[0], r[1])
		c.write(0xc1, 0x01)
		c.write(0xa1, 0x81)
		c.write(0xb1, 0x2d)
	setup.call(chip)
	var buf := PackedInt32Array()
	buf.resize(4000)
	chip.chip_block(buf)
	var peak := 0
	for v in buf:
		peak = maxi(peak, absi(v))
	if peak < 1000:
		fail("OPL2 note level %d" % peak)
	if chip.s_gen[3] == Opl2.EG_ATTACK:
		fail("OPL2 attack did not end")
	chip.write(0xb0, 0x11)
	chip.write(0xb1, 0x0d)
	var tail := PackedInt32Array()
	tail.resize(200000)
	chip.chip_block(tail)
	if chip.active_channels() != 0:
		fail("OPL2 release did not end")
	if ClassDB.class_exists("Opl2Chip"):
		var nat: RefCounted = ClassDB.instantiate("Opl2Chip")
		var gd := Opl2.new(22050.0, false)
		setup.call(nat)
		setup.call(gd)
		var a: PackedInt32Array = nat.chip_samples(30000)
		var b := PackedInt32Array()
		b.resize(30000)
		gd.chip_block(b)
		nat.write(0xb0, 0x11)
		gd.write(0xb0, 0x11)
		a.append_array(nat.chip_samples(30000))
		var b2 := PackedInt32Array()
		b2.resize(30000)
		gd.chip_block(b2)
		b.append_array(b2)
		var diff := -1
		for i in a.size():
			if a[i] != b[i]:
				diff = i
				break
		if diff >= 0:
			fail("native OPL2 differs at sample %d: %d %d" % [diff, a[diff], b[diff]])
		else:
			print("native OPL2 = GDScript OPL2 for %d samples" % a.size())

## a chip that keeps the registers written to it
class RecChip extends Opl2:
	var regs := PackedInt32Array()

	func _init() -> void:
		super(22050.0, false)
		regs.resize(256)

	func write(reg: int, val: int) -> void:
		regs[reg & 0xff] = val & 0xff
		super.write(reg, val)

static func _golden(name: String) -> Dictionary:
	if name == "ai":
		# golden.py write_ai: one file per group
		var merged := {}
		for f in DirAccess.get_files_at("res://tests/golden"):
			if f.begins_with("ai_") and (f.ends_with(".json") or f.ends_with(".json.gz")):
				var part := _golden(f.trim_suffix(".gz").trim_suffix(".json"))
				merged.merge(part)
		return merged
	var text := ""
	var gz := "res://tests/golden/%s.json.gz" % name
	if FileAccess.file_exists(gz):
		var packed := FileAccess.get_file_as_bytes(gz)
		text = packed.decompress_dynamic(-1, FileAccess.COMPRESSION_GZIP).get_string_from_utf8()
	else:
		var f := FileAccess.open("res://tests/golden/%s.json" % name, FileAccess.READ)
		if f == null:
			return {}
		text = f.get_as_text()
	var v = JSON.parse_string(text)
	return v if v is Dictionary else {}

## the port against the original (tools/nhl/golden.py runs HOCKEY.EXE's routines in an emulator on the
## same inputs): randomrange and rand, the AdLib driver's OPL2 registers after every tick, the PC
## speaker driver's PIT divisor and gate
func golden_tests(gf: Node) -> void:
	var rng := _golden("rng")
	if rng.is_empty():
		fail("golden data missing (tests/golden)")
		return
	var sim := Sim.new()
	for c: Dictionary in rng["randomrange"]:
		sim.seed = int(c["seed"])
		for v in c["values"]:
			var got := sim.random(int(c["n"]))
			if got != int(v):
				fail("randomrange(%d) from seed %x: %d, the original %d" % [int(c["n"]), int(c["seed"]), got, int(v)])
				break
		if sim.seed != int(c["final_seed"]):
			fail("randomrange seed %x, the original %x" % [sim.seed, int(c["final_seed"])])
	for c: Dictionary in rng["rand"]:
		League.srand(int(c["seed"]))
		for v in c["values"]:
			if League.rand() != int(v):
				fail("rand from seed %d differs" % int(c["seed"]))
				break
	# the AdLib driver: the registers the original has written by the end of each tick
	var fm := _golden("fm_driver")
	var bank := FmBank.load_bank(gf.read_raw("pcff001.pat"), [gf.read_raw("pcff000.tim")])
	var compared := PackedInt32Array()
	for r in range(0x20, 0xf6):
		if (r & 0x1f) < 0x16 or r >= 0xa0:
			compared.append(r)
	compared.append(0xbd)
	var fm_ok := 0
	for case_name in fm:
		var case: Dictionary = fm[case_name]
		var chip := RecChip.new()
		var drv := FmDriver.new(chip, bank)
		var want := PackedInt32Array()
		want.resize(256)
		var ticks: Array = case["ticks"]
		var bad := ""
		for t in ticks.size():
			for msg: Array in ticks[t]:
				drv.midi(int(msg[0]), int(msg[1]), int(msg[2]) if msg.size() > 2 else 0)
			drv.tick()
			var d: Dictionary = case["regs"][t]
			for k in d:
				want[k.hex_to_int()] = int(d[k])
			for r in compared:
				if (r >= 0xa9 and r <= 0xaf) or (r >= 0xb9 and r <= 0xbc) or (r >= 0xc9 and r <= 0xdf):
					continue
				if chip.regs[r] != want[r]:
					bad = "tick %d register %02x: %02x, the original %02x" % [t, r, chip.regs[r], want[r]]
					break
			if bad != "":
				break
		if bad != "":
			fail("AdLib driver '%s' %s" % [case_name, bad])
		else:
			fm_ok += 1
	# the PC speaker driver: the gate and, while it is open, the divisor
	var pc := _golden("pc_speaker")
	var pbank := FmBank.load_bank(gf.read_raw("pcff003.pat"), [gf.read_raw("pcff003.tim")])
	var pc_ok := 0
	for case_name in pc:
		var case: Dictionary = pc[case_name]
		var spk := PcSpeaker.new(pbank, 22050.0)
		var ticks: Array = case["ticks"]
		var bad := ""
		for t in ticks.size():
			for msg: Array in ticks[t]:
				spk.midi(int(msg[0]), int(msg[1]), int(msg[2]) if msg.size() > 2 else 0)
			spk.tick()
			var st: Array = case["states"][t]
			var gate := 1 if spk.gate else 0
			if gate != int(st[0]) or (gate == 1 and spk.out_div != int(st[1])):
				bad = "tick %d: gate %d divisor %d, the original %d %d" % [t, gate, spk.out_div, int(st[0]), int(st[1])]
				break
		if bad != "":
			fail("PC speaker effect %s %s" % [case_name, bad])
		else:
			pc_ok += 1
	print("golden: randomrange, rand, AdLib driver %d / %d sequences, PC speaker %d / %d effects" % [fm_ok, fm.size(), pc_ok, pc.size()])
	physics_golden()
	ai_golden()

## the AI state handlers (ai_*.json): a random moment of play, one entity in a state, its handler run
func ai_golden() -> void:
	var data := _golden("ai")
	if data.is_empty():
		fail("golden AI data missing")
		return
	var base: Array = data["base"]
	var counts := []
	for group in data:
		if group == "base":
			continue
		if group == "lines" or group == "controls" or group == "rules" or group == "goals" or group == "faceoffs":
			counts.append(_lines_golden(data[group], base, group))
			continue
		var sim := Sim.new()
		sim.stubs = {"play_sfx": true, "queue_infraction": true, "maybe_queue_infraction": true, "injury_check": true,
			"injure_player": true, "bench_cheer": true, "announce_goal": true, "play_speech": true, "load_clip": true,
			"say_goal": true, "goal_milestone_check": true, "put_player_on_ice": true,
			"pick_player_for_position": true, "draw_line_indicator": true}
		var ok := 0
		var bad := 0
		var shown := 0
		var per_state := {}
		var only := OS.get_environment("AI_STATE")      # show only this state's failures
		var index := -1
		for c: Dictionary in data[group]:
			index += 1
			_ai_world_set(sim, c, base)
			var actor: Entity = sim.entities[int(c["actor"])]
			sim.stub_calls.clear()
			AI.dispatch(sim, actor)
			var diff := _ai_world_diff(sim, c, base)
			var st := int(c["state"])
			if not per_state.has(st):
				per_state[st] = [0, 0]
			if diff.is_empty():
				ok += 1
				per_state[st][0] += 1
			else:
				bad += 1
				per_state[st][1] += 1
				if only != "" and Tables.ai_state_names[st + 1] != only:
					failures += 1
				elif shown < 10:
					shown += 1
					fail("AI %s %s slot %d%s: %s" % [group, Tables.ai_state_names[st + 1], actor.slot,
						" (case %d)" % index if only != "" else "", ", ".join(diff.slice(0, 8))])
		var parts := []
		for st in per_state:
			parts.append("%s %d/%d" % [Tables.ai_state_names[st + 1], per_state[st][0], per_state[st][0] + per_state[st][1]])
		counts.append("%s %d / %d (%s)" % [group, ok, ok + bad, ", ".join(parts)])
	print("golden AI: ", "; ".join(counts))

## the line change routines (ai_lines.json): called directly on random teams
func _lines_golden(cases: Array, base: Array, group := "lines") -> String:
	var sim := Sim.new()
	sim.stubs = {"play_sfx": true, "queue_infraction": true, "maybe_queue_infraction": true, "injury_check": true,
		"injure_player": true, "bench_cheer": true, "announce_goal": true, "play_speech": true, "load_clip": true,
		"say_goal": true, "goal_milestone_check": true, "put_player_on_ice": true,
		"pick_player_for_position": true, "draw_line_indicator": true, "record_penalty": true,
		"add_penalty_display": true, "penalty_list_find": true, "update_announcer": true, "update_effects": true,
		"setup_faceoff": true, "announce_one_minute_left": true}
	if group == "rules" or group == "goals":
		sim.stubs.erase("queue_infraction")
		sim.stubs.erase("maybe_queue_infraction")
	if group == "goals" or group == "faceoffs":
		for n in ["setup_faceoff", "injury_check", "update_effects"]:
			sim.stubs.erase(n)
		for n in ["draw_score_digits", "game_over_check"]:
			sim.stubs[n] = true
	if group == "faceoffs":
		sim.stubs.erase("queue_infraction")
		sim.stubs.erase("maybe_queue_infraction")
		for n in ["stop_crowd_loop", "center_mouse", "gsummary_flush", "period_cleanup"]:
			sim.stubs[n] = true
	var per := {}
	var ok := 0
	var shown := 0
	var only := OS.get_environment("AI_STATE")
	var index := -1
	for c: Dictionary in cases:
		index += 1
		_ai_world_set(sim, c, base)
		sim.panel_text[4] = ""
		var li: Dictionary = c.get("lines", {})
		for t in (2 if not li.is_empty() else 0):
			var team: Team = sim.teams[t]
			var info := Database.TeamInfo.new()
			var pos: String = li["positions"][t]
			for i in 25:
				var p := Database.Player.new()
				p.position = pos.substr(i, 1)
				p.ratings = PackedByteArray(_ints(li["ratings"][t][i]))
				p.roster_idx = i
				info.skaters.append(p)
			for i in 3:
				var p := Database.Player.new()
				p.position = "G"
				p.goalie = true
				p.ratings = PackedByteArray()
				p.ratings.resize(0x10)
				p.roster_idx = 25 + i
				info.goalies.append(p)
			info.line_table = PackedByteArray(_ints(li["line_tables"][t]))
			team.info = info
			for k in 11:
				team.pos_lists[k] = PackedInt32Array(_ints(li["pos_lists"][t][k]))
			for i in 3:
				team.goalie_menu[i] = int(li["menu"][t * 3 + i])
		if c.has("pos_lists"):
			for t in 2:
				for k in 11:
					sim.teams[t].pos_lists[k] = PackedInt32Array(_ints(c["pos_lists"][t][k]))
		if c.has("stats"):
			_goal_stats_set(sim, c["stats"])
		if c.has("crowd"):
			_crowd_set(sim, c["crowd"])
		if group == "faceoffs":
			for t in 2:
				sim.teams[t].info = _ratings_info(c["faceoff_ratings"][t]) if c.has("faceoff_ratings") else null
		if not li.is_empty():
			var req: Array = li["req"]
			for i in 6:
				sim.req_roster[i] = int(req[i])
				sim.req_slot[i] = int(req[6 + i])
		var name: String = c["routine"]
		var args: Array = _ints(c["args"])
		var a0: int = args[0] if args.size() > 0 else 0
		var a1: int = args[1] if args.size() > 1 else 0
		sim.stub_calls.clear()
		var ret = null
		match name:
			"build_lines": Lines.build_lines(sim)
			"assign_line_positions": Lines.assign_line_positions(sim, sim.teams[a0])
			"apply_line_change": Lines.apply_line_change(sim, sim.teams[a0])
			"choose_line": Lines.choose_line(sim, sim.teams[1 - a0], sim.teams[a0])
			"line_avg_energy": ret = Lines.line_avg_energy(sim, sim.teams[a0], a1)
			"team_avg_energy": Lines.team_avg_energy(sim, sim.teams[a0])
			"pick_next_line": Lines.pick_next_line(sim, sim.entities[a0])
			"cpu_line_change_select": Lines.cpu_line_change_select(sim, sim.entities[a0])
			"request_line_change": ret = 1 if Lines.request_line_change(sim, sim.entities[a0], a1) else 0
			"maybe_pull_goalie": Lines.maybe_pull_goalie(sim, sim.teams[a0], sim.teams[1 - a0], a1)
			"cpu_pull_goalie_check": Lines.cpu_pull_goalie_check(sim)
			"late_game_pull_goalie": ret = 1 if Lines.late_game_pull_goalie(sim, a0) else 0
			"cpu_line_change": Lines.cpu_line_change(sim)
			"dress_line": Lines.dress_line(sim, sim.teams[a0])
			"send_team_to_faceoff": Lines.send_team_to_faceoff(sim, sim.teams[a0])
			"handle_line_change": ret = 1 if Lines.handle_line_change(sim, sim.entities[a0]) else 0
			"adjust_strategy": Lines.adjust_strategy(sim, a0)
			"hotkey_pull_goalie": Lines.toggle_pull_goalie(sim, a0)
			"controls_goalie_pull_request": Lines.user_goalie_back(sim, a0)
			"choose_goalie": Lines.choose_goalie(sim, a0, a1)
			"control_player": sim.control_player(sim.entities[a0], a1)
			"update_stoppage": Rules.update_stoppage(sim)
			"process_infractions": Rules.process_infractions(sim)
			"start_stoppage": Rules.start_stoppage(sim, a0)
			"penalty_box_update": Rules.penalty_box_update(sim)
			"penalty_timers": Rules.penalty_timers(sim, sim.teams[a0])
			"penalty_expired": Rules.penalty_expired(sim, sim.teams[a0], a1)
			"release_from_box": Rules.release_from_box(sim, sim.teams[a0], a1)
			"goal_ends_penalty": Rules.goal_ends_penalty(sim, a0)
			"update_power_play": Rules.update_power_play(sim)
			"count_penalized": Rules.count_penalized(sim)
			"penalty_time_left": ret = Rules.penalty_time_left(sim)
			"queue_infraction": Rules.queue_infraction(sim, sim.entities[a0], a1)
			"maybe_queue_infraction": Rules.maybe_queue_infraction(sim, sim.entities[a0], a1)
			"ref_announce": Rules.ref_announce(sim, a0)
			"update_line_timers": Rules.update_line_timers(sim)
			"sim_game_state": Rules.sim_game_state(sim)
			"game_clock_tick": Rules.game_clock_tick(sim)
			"time_announcements": Lines.time_announcements(sim)
			"period_strategy_init": Lines.period_strategy_init(sim)
			"clear_infractions": Rules.clear_infractions(sim)
			"score_goal": Rules.score_goal(sim, sim.entities[a0])
			"goal_disallowed_check": ret = 1 if Rules.goal_disallowed_check(sim) else 0
			"setup_faceoff": Rules.setup_faceoff(sim)
			"begin_penalty_shot": Rules.begin_penalty_shot(sim)
			"start_penalty_shot": Rules.start_penalty_shot(sim)
			"end_penalty_shot": Rules.end_penalty_shot(sim)
			"breakaway_foul": ret = 1 if Rules.breakaway_foul(sim, sim.entities[a0]) else 0
			"injury_check": ret = 1 if Rules.injury_check(sim, sim.entities[a0]) else 0
			"update_effects": Rules.update_effects(sim)
			"ai_puck_faceoff": AI.puck_faceoff(sim, sim.puck)
			"ai_puck_faceoff2": AI.puck_faceoff2(sim, sim.puck)
			"end_of_period": Rules.end_of_period(sim)
		var diff := _ai_world_diff(sim, c, base)
		var la: Dictionary = c["lines_after"]
		if la.has("infq"):
			if str(Array(sim.infq)) != str(_ints(la["infq"])):
				diff.append("queue %s (original %s)" % [str(Array(sim.infq.slice(0, 10))), str(la["infq"].slice(0, 10))])
			if str(sim.panel_text[4]) != str(la["panel4"]):
				diff.append("panel line 5 '%s' (original '%s')" % [sim.panel_text[4], la["panel4"]])
		if ret != null:
			var want := int(la["ret"])
			if name == "penalty_time_left":
				want = Entity.to_s16(want)
				ret = Entity.to_s16(int(ret))
			elif name != "line_avg_energy":
				want = 1 if (want & 0xffff) != 0 else 0
			if int(ret) != want:
				diff.append("returns %d (original %d)" % [int(ret), want])
		for t in (2 if la.has("pos_lists") else 0):
			for k in 11:
				if str(Array(sim.teams[t].pos_lists[k])) != str(_ints(la["pos_lists"][t][k])):
					diff.append("team %d list %d %s (original %s)" % [t, k, str(sim.teams[t].pos_lists[k]), str(la["pos_lists"][t][k])])
			for i in 3:
				if sim.teams[t].goalie_menu[i] != int(la["menu"][t * 3 + i]):
					diff.append("team %d goalie menu %s (original %s)" % [t, str(sim.teams[t].goalie_menu), str(la["menu"])])
					break
		if la.has("req"):
			var got_req := []
			for i in 6:
				got_req.append(Entity.to_s8(sim.req_roster[i]))
			for i in 6:
				got_req.append(Entity.to_s8(sim.req_slot[i]))
			if str(got_req) != str(_ints(la["req"])):
				diff.append("lineup request %s (original %s)" % [str(got_req), str(la["req"])])
		if la.has("stats"):
			var got_stats := _goal_stats_get(sim)
			if str(got_stats) != str(la["stats"]):
				for t in 2:
					for r in 25:
						if str(got_stats[t][r]) != str(la["stats"][t][r]):
							diff.append("team %d player %d stats %s (original %s)" % [t, r, str(got_stats[t][r]), str(la["stats"][t][r])])
					for g in 3:
						if str(got_stats[2 + t][g]) != str(la["stats"][2 + t][g]):
							diff.append("team %d goalie %d stats %s (original %s)" % [t, g, str(got_stats[2 + t][g]), str(la["stats"][2 + t][g])])
		if la.has("crowd"):
			var got_crowd := _crowd_get(sim)
			if str(got_crowd) != str(la["crowd"]):
				for i in 20:
					if str(got_crowd[0][i]) != str(la["crowd"][0][i]):
						diff.append("crowd figure %d %s (original %s)" % [i, str(got_crowd[0][i]), str(la["crowd"][0][i])])
				if str(got_crowd[1]) != str(la["crowd"][1]):
					diff.append("crowd spots %s (original %s)" % [str(got_crowd[1]), str(la["crowd"][1])])
		if la.has("scratch_ac") and (sim.scratch_ac & 0xffff) != (int(la["scratch_ac"]) & 0xffff):
			diff.append("scratch e03ac %x (original %x)" % [sim.scratch_ac & 0xffff, int(la["scratch_ac"]) & 0xffff])
		if la.has("scratch"):
			var sc: Array = la["scratch"]
			if Sim._s16(sim.scratch_a) != int(sc[0]) or Sim._s16(sim.scratch_b) != int(sc[1]):
				diff.append("scratch %d %d (original %s)" % [Sim._s16(sim.scratch_a), Sim._s16(sim.scratch_b), str(sc)])
		if c.has("scen"):
			name = str(c["scen"])
		if not per.has(name):
			per[name] = [0, 0]
		if diff.is_empty():
			ok += 1
			per[name][0] += 1
		else:
			per[name][1] += 1
			if only != "" and name != only:
				failures += 1
			elif shown < 10:
				shown += 1
				fail("%s %s %s%s: %s" % [group, name, str(args), " (case %d)" % index if only != "" else "", ", ".join(diff.slice(0, 8))])
	var parts := []
	for n in per:
		parts.append("%s %d/%d" % [n, per[n][0], per[n][0] + per[n][1]])
	return "%s %d / %d (%s)" % [group, ok, cases.size(), ", ".join(parts)]

## the player statistics of both teams (team +0xe6: 25 x goals, assists, penalty minutes, plus /
## minus, power play, short handed and empty net goals, shots) and the goalies' (+0xea: 3 x time,
## shots, goals against), as golden.py goals_cases records them: [home, away, home goalies, away goalies]
static func _goal_stats_set(sim: Sim, st: Array) -> void:
	for t in 2:
		for r in 25:
			sim.teams[t].player_stats[r] = PackedInt32Array(_ints(st[t][r]))
		for g in 3:
			sim.teams[t].goalie_stats[g] = PackedInt32Array(_ints(st[2 + t][g]))

static func _goal_stats_get(sim: Sim) -> Array:
	var out := [[], [], [], []]
	for t in 2:
		for r in 25:
			out[t].append(Array(sim.teams[t].player_stats[r]))
		for g in 3:
			out[2 + t].append(Array(sim.teams[t].goalie_stats[g]))
	return out

## a roster of placeholder players with their faceoff ratings (byte 0x13 of `player_ratings`, all
## faceoff_resolve reads) and three goalies
static func _ratings_info(ratings: Array) -> Database.TeamInfo:
	var info := Database.TeamInfo.new()
	for i in 25:
		var p := Database.Player.new()
		p.ratings = PackedByteArray()
		p.ratings.resize(0x14)
		p.ratings[0x13] = int(ratings[i])
		p.roster_idx = i
		info.skaters.append(p)
	for i in 3:
		var p := Database.Player.new()
		p.goalie = true
		p.ratings = PackedByteArray()
		p.ratings.resize(0x10)
		p.roster_idx = 25 + i
		info.goalies.append(p)
	return info

## the crowd figures (crowd_figures: 20 x [spot, timer, counter, frame, x, y, sequence, count]) and
## the spots in use (the bits of crowd_spots_busy, 9 words)
static func _crowd_set(sim: Sim, cr: Array) -> void:
	if sim.crowd.size() != Crowd.RECORDS:
		sim.crowd = []
		for i in Crowd.RECORDS:
			sim.crowd.append(Crowd.Record.new())
		sim.crowd_busy = PackedByteArray()
		sim.crowd_busy.resize(0xab)
	for i in Crowd.RECORDS:
		var f: Array = cr[0][i]
		var r: Crowd.Record = sim.crowd[i]
		r.id = int(f[0])
		r.timer = int(f[1])
		r.counter = int(f[2])
		r.frame = int(f[3])
		r.x = int(f[4])
		r.y = int(f[5])
		r.seq = int(f[6])
		r.count = int(f[7])
	for id in 0xab:
		sim.crowd_busy[id] = (int(cr[1][id >> 4]) >> (id & 15)) & 1

static func _crowd_get(sim: Sim) -> Array:
	var recs := []
	for i in Crowd.RECORDS:
		var r: Crowd.Record = sim.crowd[i]
		recs.append([r.id, r.timer, r.counter, r.frame, r.x, r.y, r.seq, r.count])
	var bits := []
	for w in 11:
		var v := 0
		for b in 16:
			if w * 16 + b < 0xab and sim.crowd_busy[w * 16 + b] != 0:
				v |= 1 << b
		bits.append(v)
	return [recs, bits]

## update_camera against the original (golden.py camera_cases)
func _camera_golden(cases: Array) -> int:
	var ok := 0
	var shown := 0
	var sim := Sim.new()
	for c: Dictionary in cases:
		var cam: Array = c["cam"]
		var g: Dictionary = c["g"]
		sim.camera_x = int(cam[0])
		sim.camera_y = int(cam[1])
		sim.camera_target_x = int(cam[2])
		sim.camera_target_y = int(cam[3])
		sim.camera_offset_y = int(cam[4])
		var gf := int(g["game_flags"])
		sim.play_stopped = (gf & 1) != 0
		sim.stoppage_countdown = (gf & 4) != 0
		sim.intermission_camera = (gf & 0x80) != 0
		sim.stoppage_timer = int(g["stoppage_timer"])
		sim.ref_phase = int(g["ref_phase"])
		sim.clock_seconds = int(g["clock"][0])
		sim.clock_sub = int(g["clock"][1])
		sim.action_hold_camera = (int(g["action_flags"]) & 0x40) != 0
		sim.faceoff_x = int(g["faceoff"][0])
		sim.faceoff_y = int(g["faceoff"][1])
		sim.puck_carrier = int(c["carrier"])
		var sc: Array = c["scratch"]
		sim.scratch_a = Sim._s16(int(sc[0]))
		sim.scratch_b = Sim._s16(int(sc[1]))
		sim.scratch_ac = int(sc[2])
		var ents: Dictionary = c["ents"]
		for k in ents:
			var f: Dictionary = ents[k]
			var e: Entity = sim.entities[int(k)]
			e.x = int(f["x"])
			e.y = int(f["y"])
			e.vy = int(f["vy"])
			e.flags = int(f["flags"])
			e.target_x = int(f["target_x"])
			e.target_y = int(f["target_y"])
			if f.has("state"):
				e.state_sp = 0
				e.state_stack[0] = int(f["state"])
		sim.update_camera()
		var got := [sim.camera_x, sim.camera_y, sim.camera_target_x, sim.camera_target_y, sim.camera_offset_y,
			Sim._s16(sim.scratch_a), Sim._s16(sim.scratch_b), Sim._s16(sim.scratch_ac & 0xffff)]
		if str(got) == str(_ints(c["after"])):
			ok += 1
		elif shown < 5:
			shown += 1
			fail("update_camera %s: %s (original %s)" % [str(g), str(got), str(c["after"])])
	return ok

static func _full(base_rec: Dictionary, part: Dictionary) -> Dictionary:
	var f := base_rec.duplicate()
	f.merge(part, true)
	return f

static func _ai_world_set(sim: Sim, c: Dictionary, base: Array) -> void:
	var befores: Dictionary = c["before"]
	for i in 17:
		var f := _full(base[i], befores.get(str(i), {}))
		var e: Entity = sim.entities[i]
		_entity_set(e, f)
		e.prev_x = int(f["prev"][0])
		e.prev_y = int(f["prev"][1])
		e.prev_z = int(f["prev"][2])
	var g: Dictionary = c["globals"]
	var gf := int(g["game_flags"])
	sim.play_stopped = (gf & 1) != 0
	sim.ends_switched = (gf & 2) != 0
	sim.stoppage_countdown = (gf & 4) != 0
	sim.delayed_call = (gf & 8) != 0
	sim.no_stats = (gf & 0x10) != 0
	sim.game_over = (gf & 0x40) != 0
	sim.intermission_camera = (gf & 0x80) != 0
	var sf := int(g["stop_flags"])
	sim.faceoff_pending = (sf & 1) != 0
	sim.whistle_ready = (sf & 4) != 0
	sim.shot_in_flight = (sf & 0x10) != 0
	sim.power_play = (sf & 0x20) != 0
	sim.power_play_team = 1 if (sf & 0x40) else 0
	sim.offside_warning = (sf & 0x80) != 0
	sim.misc_first_touch = (int(g["misc_flags"]) & 0x10) != 0
	sim.half_announce = (int(g["misc_flags"]) & 0x80) != 0
	sim.second_tick = (int(g["misc_flags"]) & 0x40) != 0
	var opt := int(g["option_flags"])
	sim.opt_penalties = (opt & 1) != 0
	sim.opt_offsides = (opt & 2) != 0
	sim.opt_line_changes = (opt & 4) != 0
	sim.opt_two_line_pass = (opt & 8) != 0
	sim.opt_injuries = (opt & 0x10) != 0
	sim.settings2 = int(g["settings2"])
	sim.action_pass = (int(g["action_flags"]) & 4) != 0
	sim.action_shot = (int(g["action_flags"]) & 8) != 0
	sim.action_hold_camera = (int(g["action_flags"]) & 0x40) != 0
	sim.action_replay = (int(g["action_flags"]) & 0x80) != 0
	sim.user1_slot = int(g["user1_slot"])
	sim.user2_slot = int(g["user2_slot"])
	sim.user1_team = int(g["user1_team"])
	sim.user2_team = int(g["user2_team"])
	sim.last_touch_slot = int(g["last_touch_slot"])
	sim.last_touch_y = int(g["last_touch_y"])
	sim.last_touch_x = int(g["last_touch_x"])
	sim.last_passer = int(g["last_passer"])
	sim.last_shooter = int(g["last_shooter"])
	sim.pending_dir = int(g["pending_dir"])
	sim.shot_power = int(g["shot_power"])
	sim.pass_target = int(g["pass_target"])
	sim.crowd_noise = int(g["crowd"])
	sim.excitement = int(g["excitement"])
	sim.breakaway = int(g["breakaway"]) != 0
	sim.defenders_ahead = int(g["defenders_ahead"])
	sim.one_timer = int(g["one_timer"]) != 0
	sim.penalty_shot_slot = int(g["penalty_shot_slot"])
	sim.penalty_shot = int(g["penalty_shot_active"]) != 0
	sim.penalty_shot_setup = int(g["penalty_shot_setup"]) != 0
	sim.penalty_shot_phase = int(g["penalty_shot_phase"])
	sim.penalty_shot_team = int(g["penalty_shot_team"])
	sim.icing_flags = int(g["icing_flags"])
	sim.icing_shooter = int(g["icing_shooter"])
	sim.goal_prediction[0][0] = int(g["pred0_x"])
	sim.goal_prediction[0][1] = int(g["pred0_steps"])
	sim.goal_prediction[1][0] = int(g["pred1_x"])
	sim.goal_prediction[1][1] = int(g["pred1_steps"])
	sim.period = int(g["period"])
	sim.clock_seconds = int(g["clock_seconds"])
	sim.clock_sub = int(g["clock_sub"])
	sim.whistle_timer = int(g["whistle_timer"])
	sim.camera_target_x = int(g["camera_target_x"])
	sim.camera_target_y = int(g["camera_target_y"])
	sim.last_impact = int(g["last_impact"])
	sim.crowd_toggle = int(g["crowd_hit_toggle"]) != 0
	sim.ref_hits = int(g["ref_hits"])
	sim.box_count = [int(g["box_home"]), int(g["box_away"])]
	sim.goalie_pass_mode = int(g["goalie_pass_mode"])
	sim.breakaway_lane_x = int(g.get("breakaway_lane_x", 0))
	sim.breakaway_target_y = int(g.get("breakaway_target_y", 0))
	sim.breakaway_trigger_y = int(g.get("breakaway_trigger_y", 0))
	sim.breakaway_waypoint = int(g.get("breakaway_waypoint", 0))
	sim.breakaway_lane_side = int(g.get("breakaway_lane_side", 0))
	sim.breakaway_heading = int(g.get("breakaway_heading", 0))
	sim.faceoff_x = int(g.get("faceoff_x", 0))
	sim.faceoff_y = int(g.get("faceoff_y", 0))
	sim.faceoff_ready = [int(g.get("faceoff_ready0", 0)), int(g.get("faceoff_ready1", 0))]
	sim.penalty_shot_away = int(g.get("penalty_shot_timer", 0))
	sim.injury_stoppage = int(g.get("injury_stoppage", 0)) != 0
	sim.clip = int(g.get("clip", -1))
	sim.ref_phase = int(g.get("ref_phase", -1))
	sim.speech_busy = int(g.get("speech_busy", 0)) != 0
	sim.ref_infraction = int(g.get("ref_infraction", 0))
	sim.ref_infraction_slot = int(g.get("ref_infraction_slot", -1))
	sim.panel = int(g.get("panel", -1))
	sim.demo = int(g.get("demo", 0)) != 0
	sim.sound_device = int(g.get("sound_card", 8))
	sim.sound_enabled = int(g.get("sound_enabled", 1)) != 0
	sim.announce_time = int(g.get("announce_time", -1))
	if g.has("period_length"):
		sim.period_length = int(g["period_length"])
	sim.opt_sound = (int(g["option_flags"]) & 0x80) != 0
	sim.deferred = int(g.get("deferred", 0)) != 0
	sim.infraction_events = int(g.get("infraction_events", 0))
	sim.save_clip_shown = int(g.get("save_clip_shown", 0)) != 0
	sim.period_over = int(g.get("period_over", 0)) != 0
	if int(g.get("goal_call", 0xff)) == 1:
		var gc := []
		for k in ["goal_team", "goal_scorer", "goal_a1", "goal_a2"]:
			gc.append(Entity.to_s8(int(g[k])))
		sim.goal_call = gc
	else:
		sim.goal_call = []
	Rules.clear_infractions(sim)
	if int(g.get("infraction0", 0)) != 0:
		Rules.inf_set(sim, 0, int(g["infraction0"]), 0)
	sim.message = int(g.get("message", -1))
	sim.message_timer = int(g.get("message_timer", 0))
	for t in 2:
		sim.lc_show[t] = int(g.get("lc_show%d" % t, 0))
		sim.lc_blink[t] = int(g.get("lc_blink%d" % t, 0))
		sim.lc_place[t] = int(g.get("lc_place%d" % t, 0))
		sim.lc_line[t] = int(g.get("lc_line%d" % t, 0))
		sim.lc_timer[t] = int(g.get("lc_timer%d" % t, 0))
		sim.line_hotkey_req[t] = int(g.get("hotkey%d" % t, 0))
		sim.line_hotkey[t] = int(g.get("hotkey_line%d" % t, 0))
		sim.controller_type[t] = int(g.get("controller%d" % t, 8))
		sim.faceoff_dir[t] = int(g.get("faceoff_dir%d" % t, -1))
	sim.controls_blocked = int(g.get("controls_blocked", 0)) != 0
	sim.skip_wait = int(g.get("skip_wait", 0)) != 0
	if g.has("stoppage_timer"):
		sim.stoppage_timer = int(g["stoppage_timer"])
		sim.announce_timer = int(g["announce_timer"])
		sim.penalty_box_mode = int(g["penalty_box_mode"]) != 0
		sim.second_timer = int(g["second_timer"])
		sim.tick24 = int(g["tick24"])
		sim.tick_toggle = int(g["tick_toggle"])
		sim.excitement_peak = int(g["excitement_peak"])
		sim.excitement_sum = int(g["excitement_sum"])
		sim.excitement_samples = int(g["excitement_samples"])
		sim.lc_bar[0] = int(g["lc_bar0"])
		sim.lc_bar[1] = int(g["lc_bar1"])
		sim.penalty_shot_clock = int(g["penalty_shot_clock"])
	sim.goal_flags = int(g.get("goal_flags", 1))
	sim.puck_in_net = int(g.get("puck_in_net", 0)) != 0
	sim.penalty_shot_roster = int(g.get("penalty_shot_roster", -1))
	sim.penalty_shot_spot = Vector2i(int(g.get("penalty_shot_spot_x", 0)), int(g.get("penalty_shot_spot_y", 0)))
	sim.series_announce = int(g.get("series_announce", 0)) != 0
	sim.cup_final = int(c.get("cup", 0)) != 0
	sim.camera_x = int(g.get("camera_x", 0))
	sim.camera_y = int(g.get("camera_y", 0))
	sim.camera_offset_y = int(g.get("camera_lead", 0))
	sim.faceoff_digit = int(g.get("faceoff_digit", 7))
	sim.faceoff_side = [int(g.get("faceoff_side0", 0x8800)) & 0xffff, int(g.get("faceoff_side1", 0xa000)) & 0xffff]
	sim.fade_in = int(g.get("fade_in", 0)) != 0
	sim.clip_frame = int(g.get("clip_frame", -1))
	sim.scorer_jumps = int(g.get("scorer_jumps", 0))
	sim.sequence_steps = int(g.get("sequence_steps", 0))
	sim.match_over = int(g.get("match_over", 0)) != 0
	if g.has("star0_team"):
		sim.stars = []
		for k in 3:
			sim.stars.append([int(g["star%d_team" % k]), int(g["star%d_roster" % k])])
	if c.has("infq"):
		var q: Array = c["infq"]
		for i in 64:
			sim.infq[i] = int(q[i])
	var teams: Array = c["teams"]
	for t in 2:
		var team: Team = sim.teams[t]
		var f: Dictionary = teams[t]
		team.reset_stats()
		_team_set(team, f)
		team.attacks_up = (t == 0) != sim.ends_switched
		team.hits = int(f["hits"])
		team.goals = int(f.get("goals", 0))
		team.goalie_slot = int(f.get("goalie_slot", -1))
		team.one_timer_tries = int(f.get("one_timer_tries", 0))
		team.one_timers = int(f.get("one_timers", 0))
		team.breakaways = int(f["breakaways"])
		team.passes = int(f["passes"])
		team.current_line = int(f["current_line"])
		team.nearest_dist = int(f["nearest_dist"])
		team.nearest_d2 = int(f["nearest_d2"])
		team.nearest_slot = int(f["nearest_slot"])
		team.strategy = int(f["strategy"])
		team.strategy2 = int(f["strategy2"])
		team.flags2 = int(f["flags2"])
		team.mode = int(f["mode"])
		team.energy_threshold = int(f["energy_threshold"])
		team.dpair_counter = int(f.get("dpair", 0))
		team.pp_goals = int(f.get("pp_goals", 0))
		team.power_plays = int(f.get("power_plays", 0))
		team.pp_time = int(f.get("pp_time", 0))
		team.penalty_count = int(f.get("penalty_count", 0))
		team.penalty_minutes = int(f.get("penalty_minutes", 0))
		team.zone_time = int(f.get("zone_time", 0))
		team.one_timer_goals = int(f.get("one_timer_goals", 0))
		team.breakaway_goals = int(f.get("breakaway_goals", 0))
		team.penalty_shots = int(f.get("penalty_shots", 0))
		team.penalty_shot_goals = int(f.get("penalty_shot_goals", 0))
		var bq: Array = f.get("box_queue", [])
		for i in 28:
			team.box_queue[i] = int(bq[i]) if i < bq.size() else -1
		team.line_change_ui = int(c["globals"].get("lc_prompt%d" % t, 0)) != 0
		team.extra_attacker = int(f.get("extra_attacker", -1))
		for i in 28:
			team.entity_of[i] = int(f["entity_of"][i])
			team.roster_status[i] = int(f["roster_status"][i])
			if f.has("energies"):
				team.energy[i] = int(f["energies"][i])
	for i in 12:
		var e: Entity = sim.entities[i]
		e.team = 0 if i < 6 else 1
		e.energy = sim.teams[e.team].energy[e.roster_idx] if e.roster_idx >= 0 and e.roster_idx < 28 else 0x1000
	var order: Dictionary = c["order"]
	for i in 17:
		sim.draw_list[i] = int(order["list"][i])
		sim.draw_pos[i] = int(order["pos"][i])
		sim.draw_keys[i] = int(order["keys"][i])
	sim.puck_carrier = int(c["carrier"])
	sim.seed = int(c["seed"])
	sim.scratch_ac = int(c.get("scratch_ac", 0xffffffff))
	var scratch: Array = c.get("scratch", [0, 0])
	sim.scratch_a = Sim._s16(int(scratch[0]))
	sim.scratch_b = int(scratch[1])

static func _ai_globals_get(sim: Sim) -> Dictionary:
	return {"game_flags": (1 if sim.play_stopped else 0) | (2 if sim.ends_switched else 0) | (4 if sim.stoppage_countdown else 0)
			| (8 if sim.delayed_call else 0) | (0x10 if sim.no_stats else 0) | (0x40 if sim.game_over else 0)
			| (0x80 if sim.intermission_camera else 0),
		"stop_flags": (1 if sim.faceoff_pending else 0) | (4 if sim.whistle_ready else 0) | (0x10 if sim.shot_in_flight else 0)
			| (0x20 if sim.power_play else 0) | (0x40 if sim.power_play_team == 1 else 0) | (0x80 if sim.offside_warning else 0),
		"misc_flags": (0x10 if sim.misc_first_touch else 0) | (0x80 if sim.half_announce else 0) | (0x40 if sim.second_tick else 0),
		"action_flags": (4 if sim.action_pass else 0) | (8 if sim.action_shot else 0) | (0x40 if sim.action_hold_camera else 0)
			| (0x80 if sim.action_replay else 0),
		"user1_slot": sim.user1_slot, "user2_slot": sim.user2_slot, "user1_team": sim.user1_team, "user2_team": sim.user2_team,
		"last_touch_slot": sim.last_touch_slot, "last_touch_y": sim.last_touch_y, "last_touch_x": sim.last_touch_x,
		"last_passer": sim.last_passer, "last_shooter": sim.last_shooter, "pending_dir": sim.pending_dir,
		"shot_power": sim.shot_power, "pass_target": sim.pass_target, "crowd": sim.crowd_noise, "excitement": sim.excitement,
		"breakaway": 1 if sim.breakaway else 0, "defenders_ahead": sim.defenders_ahead, "one_timer": 1 if sim.one_timer else 0,
		"penalty_shot_slot": sim.penalty_shot_slot, "penalty_shot_active": 1 if sim.penalty_shot else 0,
		"penalty_shot_setup": 1 if sim.penalty_shot_setup else 0, "penalty_shot_phase": sim.penalty_shot_phase,
		"penalty_shot_team": sim.penalty_shot_team, "icing_flags": sim.icing_flags, "icing_shooter": sim.icing_shooter & 0xff,
		"pred0_x": sim.goal_prediction[0][0], "pred0_steps": sim.goal_prediction[0][1], "pred1_x": sim.goal_prediction[1][0],
		"pred1_steps": sim.goal_prediction[1][1], "period": sim.period, "clock_seconds": sim.clock_seconds,
		"clock_sub": sim.clock_sub, "whistle_timer": sim.whistle_timer, "camera_target_x": sim.camera_target_x,
		"camera_target_y": sim.camera_target_y, "last_impact": sim.last_impact, "crowd_hit_toggle": 1 if sim.crowd_toggle else 0,
		"ref_hits": sim.ref_hits, "box_home": sim.box_count[0], "box_away": sim.box_count[1],
		"goalie_pass_mode": sim.goalie_pass_mode, "breakaway_lane_x": sim.breakaway_lane_x,
		"breakaway_target_y": sim.breakaway_target_y, "breakaway_trigger_y": sim.breakaway_trigger_y,
		"breakaway_waypoint": sim.breakaway_waypoint, "breakaway_lane_side": sim.breakaway_lane_side,
		"breakaway_heading": sim.breakaway_heading, "faceoff_x": sim.faceoff_x, "faceoff_y": sim.faceoff_y,
		"faceoff_ready0": sim.faceoff_ready[0], "faceoff_ready1": sim.faceoff_ready[1],
		"penalty_shot_timer": sim.penalty_shot_away, "injury_stoppage": 1 if sim.injury_stoppage else 0, "clip": sim.clip,
		"ref_phase": Sim._s16(sim.ref_phase & 0xffff), "ref_infraction": sim.ref_infraction,
		"ref_infraction_slot": sim.ref_infraction_slot, "panel": sim.panel, "demo": 1 if sim.demo else 0,
		"sound_card": sim.sound_device, "sound_enabled": 1 if sim.sound_enabled else 0, "announce_time": sim.announce_time,
		"period_length": sim.period_length, "deferred": 1 if sim.deferred else 0, "infraction_events": sim.infraction_events,
		"save_clip_shown": 1 if sim.save_clip_shown else 0, "period_over": 1 if sim.period_over else 0,
		"goal_call": 0 if sim.goal_call.is_empty() else 1, "infraction0": 0 if Rules.inf_type(sim, 0) == 0 else 1,
		"message": sim.message, "message_timer": sim.message_timer,
		"lc_show0": sim.lc_show[0], "lc_show1": sim.lc_show[1], "lc_blink0": sim.lc_blink[0], "lc_blink1": sim.lc_blink[1],
		"lc_place0": sim.lc_place[0], "lc_place1": sim.lc_place[1], "lc_line0": sim.lc_line[0], "lc_line1": sim.lc_line[1],
		"lc_timer0": sim.lc_timer[0], "lc_timer1": sim.lc_timer[1],
		"lc_prompt0": 1 if sim.teams[0].line_change_ui else 0, "lc_prompt1": 1 if sim.teams[1].line_change_ui else 0,
		"hotkey0": sim.line_hotkey_req[0], "hotkey1": sim.line_hotkey_req[1],
		"hotkey_line0": sim.line_hotkey[0], "hotkey_line1": sim.line_hotkey[1],
		"controls_blocked": 1 if sim.controls_blocked else 0, "skip_wait": 1 if sim.skip_wait else 0,
		"controller0": sim.controller_type[0], "controller1": sim.controller_type[1],
		"faceoff_dir0": sim.faceoff_dir[0], "faceoff_dir1": sim.faceoff_dir[1],
		"stoppage_timer": sim.stoppage_timer, "announce_timer": sim.announce_timer,
		"penalty_box_mode": 1 if sim.penalty_box_mode else 0, "second_timer": sim.second_timer, "tick24": sim.tick24,
		"tick_toggle": sim.tick_toggle, "excitement_peak": sim.excitement_peak, "excitement_sum": sim.excitement_sum,
		"excitement_samples": sim.excitement_samples, "lc_bar0": sim.lc_bar[0], "lc_bar1": sim.lc_bar[1],
		"penalty_shot_clock": sim.penalty_shot_clock, "goal_flags": sim.goal_flags, "puck_in_net": 1 if sim.puck_in_net else 0,
		"penalty_shot_roster": sim.penalty_shot_roster, "penalty_shot_spot_x": sim.penalty_shot_spot.x,
		"penalty_shot_spot_y": sim.penalty_shot_spot.y, "series_announce": 1 if sim.series_announce else 0,
		"camera_x": sim.camera_x, "camera_y": sim.camera_y, "camera_lead": sim.camera_offset_y,
		"faceoff_digit": sim.faceoff_digit, "faceoff_side0": Entity.to_s16(sim.faceoff_side[0]),
		"faceoff_side1": Entity.to_s16(sim.faceoff_side[1]), "fade_in": 1 if sim.fade_in else 0, "clip_frame": sim.clip_frame,
		"scorer_jumps": sim.scorer_jumps, "sequence_steps": sim.sequence_steps, "match_over": 1 if sim.match_over else 0,
		"star0_team": _star(sim, 0, 0), "star0_roster": _star(sim, 0, 1), "star1_team": _star(sim, 1, 0),
		"star1_roster": _star(sim, 1, 1), "star2_team": _star(sim, 2, 0), "star2_roster": _star(sim, 2, 1)}

static func _star(sim: Sim, k: int, f: int) -> int:
	return int(sim.stars[k][f]) if k < sim.stars.size() else 0

static func _ai_world_diff(sim: Sim, c: Dictionary, base: Array) -> Array:
	var diff := []
	var befores: Dictionary = c["before"]
	var after: Dictionary = c["after"]
	for i in 17:
		var b := _full(base[i], befores.get(str(i), {}))
		for d in _entity_diff(sim.entities[i], after.get(str(i), {}), b):
			diff.append("%d: %s" % [i, d])
	var wa: Dictionary = c["world_after"]
	var got := _ai_globals_get(sim)
	var ga: Dictionary = wa["globals"]
	for k in got:
		var w := int(ga[k])
		match k:
			"game_flags": w &= 0xdf
			"stop_flags": w &= 0xf5
			"misc_flags": w &= 0xd0
			"action_flags": w &= 0xcc
			"goal_call": w = 1 if w == 1 else 0
			"infraction0": w = 1 if w != 0 else 0
		if int(got[k]) != w:
			diff.append("%s %d (original %d)" % [k, int(got[k]), w])
	var tas: Array = wa["teams"]
	for t in 2:
		var team: Team = sim.teams[t]
		var want: Dictionary = tas[t]
		var tg := {"hits": team.hits, "breakaways": team.breakaways, "passes": team.passes, "current_line": team.current_line,
			"nearest_dist": team.nearest_dist, "nearest_d2": team.nearest_d2, "nearest_slot": team.nearest_slot, "strategy": team.strategy,
			"strategy2": team.strategy2, "flags2": team.flags2, "mode": team.mode, "energy_threshold": team.energy_threshold,
			"one_timer_tries": team.one_timer_tries, "one_timers": team.one_timers, "goalie_slot": team.goalie_slot,
			"goals": team.goals, "dpair": team.dpair_counter, "extra_attacker": team.extra_attacker,
			"pp_goals": team.pp_goals, "power_plays": team.power_plays, "pp_time": team.pp_time,
			"penalty_count": team.penalty_count, "penalty_minutes": team.penalty_minutes, "zone_time": team.zone_time,
			"one_timer_goals": team.one_timer_goals, "breakaway_goals": team.breakaway_goals, "penalty_shots": team.penalty_shots,
			"penalty_shot_goals": team.penalty_shot_goals}
		for k in tg:
			if int(tg[k]) != int(want[k]):
				diff.append("team %d %s %d (original %d)" % [t, k, int(tg[k]), int(want[k])])
		var w2 := want.duplicate()
		w2["player_shots"] = []
		w2["goalie_shots"] = []
		for d in _team_diff(team, w2, false):
			diff.append("team %d %s" % [t, d])
		for i in 28:
			if team.entity_of[i] != int(want["entity_of"][i]):
				diff.append("team %d entity_of[%d] %d (original %d)" % [t, i, team.entity_of[i], int(want["entity_of"][i])])
				break
		if want.has("box_queue"):
			for i in 28:
				if team.box_queue[i] != int(want["box_queue"][i]):
					diff.append("team %d box queue %s (original %s)" % [t, str(team.box_queue), str(want["box_queue"])])
					break
		for i in 28:
			if team.roster_status[i] != int(want["roster_status"][i]):
				diff.append("team %d roster_status[%d] %d (original %d)" % [t, i, team.roster_status[i], int(want["roster_status"][i])])
				break
	if sim.puck_carrier != int(wa["carrier"]):
		diff.append("carrier %d (original %d)" % [sim.puck_carrier, int(wa["carrier"])])
	if str(sim.stub_calls) != str(_ints(c["calls"])):
		diff.append("calls %s (original %s)" % [str(sim.stub_calls), str(c["calls"])])
	if sim.seed != int(wa["seed"]):
		diff.append("seed")
	return diff

## the match physics against the original: approx_distance and direction8; collide_boards (with
## collide_corner, bounce_off_boards, puck_spin) on puck and skater states at the boards
func physics_golden() -> void:
	var ph := _golden("physics")
	if ph.is_empty():
		fail("golden physics data missing")
		return
	# the records before a call keep only the fields that differ from the base records
	var base0: Array = ph["base"]
	for key in ph:
		if not (ph[key] is Array) or key == "base" or key == "distance":
			continue
		for c in ph[key]:
			if not (c is Dictionary) or not c.has("before"):
				continue
			var b: Dictionary = c["before"]
			if c.has("slot") and not b.has("0"):
				var full: Dictionary = base0[int(c["slot"])].duplicate()
				full.merge(b, true)
				c["before"] = full
			else:
				for k in b.keys():
					var full: Dictionary = base0[int(k)].duplicate()
					full.merge(b[k], true)
					b[k] = full
	var dbad := 0
	for c: Array in ph["distance"]:
		var d := Sim.approx_distance(int(c[0]), int(c[1]))
		var r := Tables.direction8(int(c[0]), int(c[1]))
		if d != int(c[2]) or r != int(c[3]):
			dbad += 1
			if dbad <= 3:
				fail("distance %s: %d direction %d" % [str(c), d, r])
	var sim := Sim.new()
	var ok := 0
	var bad := 0
	for c: Dictionary in ph["boards"]:
		var e: Entity = sim.entities[int(c["slot"])]
		var before: Dictionary = c["before"]
		_entity_set(e, before)
		e.half_w = int(c["hw"])
		e.half_h = int(c["hh"])
		e.prev_x = int(c["prev_x"])
		e.prev_y = int(c["prev_y"])
		e.prev_z = e.z
		sim.puck_carrier = int(c["carrier"])
		sim.seed = int(c["seed"])
		sim.sfx_queue.clear()
		sim.play_stopped = false
		sim.collide_boards(e, int(c["px"]), int(c["py"]), e.half_w, e.half_h)
		var diff := _entity_diff(e, c["after"], before)
		var sfx: Array = c["sfx"]
		if sim.sfx_queue.size() != sfx.size() or (sfx.size() > 0 and sim.sfx_queue[0] != int(sfx[0])):
			diff.append("sounds %s (original %s)" % [str(sim.sfx_queue), str(sfx)])
		if sim.seed != int(c["final_seed"]):
			diff.append("seed")
		if diff.is_empty():
			ok += 1
		else:
			bad += 1
			if bad <= 6:
				fail("collide_boards slot %d at %d,%d v %d,%d: %s" % [e.slot, int(c["px"]), int(c["py"]), int(before["vx"]), int(before["vy"]), ", ".join(diff)])
	# apply_skating: turning, accelerating, braking, the goalie's steps, the fatigue
	var sk_ok := 0
	var sk_bad := 0
	for c: Dictionary in ph["skating"]:
		var e: Entity = sim.entities[int(c["slot"])]
		_entity_set(e, c["before"])
		var team: Team = sim.teams[e.team] if e.slot < 12 else null
		if team != null and e.roster_idx >= 0:
			team.energy[e.roster_idx] = int(c["energy"])
		e.energy = int(c["energy"])
		var p: Array = c["puck"]
		sim.puck.x = int(p[0]) << 16
		sim.puck.y = int(p[1]) << 16
		sim.puck.vy = int(p[2])
		sim.puck_carrier = int(c["carrier"])
		var gfl := int(c["game_flags"])
		sim.play_stopped = (gfl & 1) != 0
		sim.delayed_call = (gfl & 8) != 0
		sim.offside_warning = (int(c["stop_flags"]) & 0x80) != 0
		sim.whistle_timer = int(c["whistle"])
		sim.opt_line_changes = (int(c["options"]) & 4) != 0
		sim.seed = int(c["seed"])
		var sc_in: Array = c.get("scratch", [0, 0, 0])
		sim.scratch_a = Sim._s16(int(sc_in[0]))
		sim.scratch_b = Sim._s16(int(sc_in[1]))
		sim.scratch_ac = int(sc_in[2])
		sim.apply_skating(e, int(c["dir"]))
		var diff := _entity_diff(e, c["after"], c["before"])
		if team != null and e.roster_idx >= 0 and e.energy != int(c["energy_after"]):
			diff.append("energy %d (original %d)" % [e.energy, int(c["energy_after"])])
		if c.has("scratch_after"):
			var sca: Array = c["scratch_after"]
			var got_sc := [Sim._s16(sim.scratch_a), Sim._s16(sim.scratch_b), sim.scratch_ac & 0xffffffff]
			if str(got_sc) != str(_ints(sca)):
				diff.append("scratch %s (original %s)" % [str(got_sc), str(sca)])
		if sim.seed != int(c["final_seed"]):
			diff.append("seed")
		if diff.is_empty():
			sk_ok += 1
		else:
			sk_bad += 1
			if sk_bad <= 8:
				fail("apply_skating slot %d line %d dir %d v %d,%d facing %d: %s" % [e.slot, e.line_slot, int(c["dir"]), int(c["before"]["vx"]), int(c["before"]["vy"]), (int(c["before"]["heading"]) >> 16) & 7, ", ".join(diff)])
	sim.play_stopped = false
	sim.delayed_call = false
	sim.offside_warning = false
	sim.whistle_timer = 0
	# at the nets: goals, posts, the roof, the frame, skaters against the frame, nets knocked off
	var n_ok := 0
	var n_bad := 0
	for c: Dictionary in ph["nets"]:
		Rules.reset_nets(sim)
		var e: Entity = sim.entities[int(c["slot"])]
		_entity_set(e, c["before"])
		e.half_w = int(c["hw"])
		e.half_h = int(c["hh"])
		e.prev_x = int(c["prev_x"])
		e.prev_y = int(c["prev_y"])
		e.prev_z = int(c["prev_z"])
		if e.slot != Entity.Slot.PUCK:
			sim.puck.y = int(c["puck_y"]) << 16
		sim.puck_carrier = int(c["carrier"])
		sim.play_stopped = (int(c["game_flags"]) & 1) != 0
		sim.seed = int(c["seed"])
		sim.sfx_queue.clear()
		Rules.clear_infractions(sim)
		sim.penalty_box_mode = false
		sim.puck_in_net = false
		sim.bounced = false
		sim.scored_net = -1
		sim.collide_boards(e, int(c["px"]), int(c["py"]), e.half_w, e.half_h)
		var diff := []
		var goal: Array = c["goal"]
		if not goal.is_empty():
			if sim.scored_net != int(goal[0]):
				diff.append("no goal (the original scores in net %d)" % int(goal[0]))
		else:
			if sim.scored_net >= 0:
				diff.append("a goal in net %d (the original has none)" % sim.scored_net)
			diff.append_array(_entity_diff(e, c["after"], c["before"]))
			var sfx: Array = c["sfx"]
			if sim.sfx_queue.size() != sfx.size() or (sfx.size() > 0 and sim.sfx_queue[0] != int(sfx[0])):
				diff.append("sounds %s (original %s)" % [str(sim.sfx_queue), str(sfx)])
			var infs: Array = c["infractions"]
			var got_infs := []
			for i in Rules.inf_count(sim):
				got_infs.append([Rules.inf_slot(sim, i), Rules.inf_type(sim, i)])
			if str(got_infs) != str(infs.map(func(a): return [int(a[0]), int(a[1])])):
				diff.append("infractions %s (original %s)" % [str(got_infs), str(infs)])
			var nv: Array = c["net_v"]
			var net := sim.entities[Entity.Slot.NET_TOP if int(c["py"]) > 0 else Entity.Slot.NET_BOTTOM]
			if net.vx != int(nv[0]) or net.vy != int(nv[1]):
				diff.append("net velocity %d,%d (original %s)" % [net.vx, net.vy, str(nv)])
			if sim.puck_in_net != (int(c["puck_in_net"]) != 0):
				diff.append("puck_in_net %s" % sim.puck_in_net)
			if sim.puck_carrier != int(c["carrier_after"]):
				diff.append("carrier %d (original %d)" % [sim.puck_carrier, int(c["carrier_after"])])
			if sim.seed != int(c["final_seed"]):
				diff.append("seed")
		if diff.is_empty():
			n_ok += 1
		else:
			n_bad += 1
			if n_bad <= 8:
				fail("at the net: slot %d at %d,%d z %d v %d,%d prev %d,%d: %s" % [e.slot, int(c["px"]), int(c["py"]), int(c["before"]["z"]) >> 16, int(c["before"]["vx"]), int(c["before"]["vy"]), int(c["prev_x"]) >> 16, int(c["prev_y"]) >> 16, ", ".join(diff)])
	Rules.reset_nets(sim)
	sim.play_stopped = false
	Rules.clear_infractions(sim)
	# move_entity among team mates: the draw order, collide_pair, stepping around each other
	var c_ok := 0
	var c_bad := 0
	var base: Array = ph["base"]
	for c: Dictionary in ph["contacts"]:
		for i in 17:
			var b: Entity = sim.entities[i]
			_entity_set(b, base[i])
			b.prev_x = int(base[i]["prev"][0])
			b.prev_y = int(base[i]["prev"][1])
			b.prev_z = int(base[i]["prev"][2])
		var befores: Dictionary = c["before"]
		for k in befores:
			var e: Entity = sim.entities[int(k)]
			_entity_set(e, befores[k])
			e.prev_x = int(befores[k]["prev"][0])
			e.prev_y = int(befores[k]["prev"][1])
			e.prev_z = e.z
			e.energy = 0x1000
			if e.slot < 12 and e.roster_idx >= 0:
				sim.teams[e.team].energy[e.roster_idx] = 0x1000
		var order: Dictionary = c["order"]
		for i in 17:
			sim.draw_list[i] = int(order["list"][i])
			sim.draw_pos[i] = int(order["pos"][i])
			sim.draw_keys[i] = int(order["keys"][i])
		sim.puck_carrier = int(c["carrier"])
		sim.play_stopped = (int(c["game_flags"]) & 1) != 0
		sim.opt_line_changes = (int(c["options"]) & 4) != 0
		sim.seed = int(c["seed"])
		sim.sfx_queue.clear()
		var mover: Entity = sim.entities[int(c["mover"])]
		sim.move_entity(mover)
		var diff := []
		var after: Dictionary = c["after"]
		for k in after:
			for d in _entity_diff(sim.entities[int(k)], after[k], befores[k]):
				diff.append("%s: %s" % [k, d])
		var oa: Dictionary = c["order_after"]
		for i in 17:
			if sim.draw_list[i] != int(oa["list"][i]) or sim.draw_pos[i] != int(oa["pos"][i]) or sim.draw_keys[i] != int(oa["keys"][i]):
				diff.append("draw order %s %s (original %s %s)" % [str(sim.draw_list), str(sim.draw_keys), str(oa["list"]), str(oa["keys"])])
				break
		var sfx: Array = c["sfx"]
		if sim.sfx_queue.size() != sfx.size():
			diff.append("sounds %s (original %s)" % [str(sim.sfx_queue), str(sfx)])
		if sim.puck_in_net != (int(c["puck_in_net"]) != 0):
			diff.append("puck_in_net %s" % sim.puck_in_net)
		if sim.seed != int(c["final_seed"]):
			diff.append("seed")
		if diff.is_empty():
			c_ok += 1
		else:
			c_bad += 1
			if c_bad <= 6:
				fail("move_entity slot %d: %s" % [mover.slot, ", ".join(diff.slice(0, 6))])
	sim.play_stopped = false
	sim.sort_draw_order()
	# advance_animation: frames, durations, the end of an animation, the frame countdown, strides
	var a_ok := 0
	var a_bad := 0
	for c: Dictionary in ph["animation"]:
		var e: Entity = sim.entities[int(c["slot"])]
		_entity_set(e, c["before"])
		sim.sfx_queue.clear()
		sim.speech_busy = false
		Anim.advance(e, sim)
		var diff := _entity_diff(e, c["after"], c["before"])
		var sfx: Array = c["sfx"]
		if sim.sfx_queue.size() != sfx.size():
			diff.append("sounds %s (original %s)" % [str(sim.sfx_queue), str(sfx)])
		if diff.is_empty():
			a_ok += 1
		else:
			a_bad += 1
			if a_bad <= 6:
				fail("advance_animation anim %x pos %d hold %d wait %d: %s" % [int(c["before"]["anim"]), int(c["before"]["anim_pos"]), int(c["before"]["anim_hold"]), int(c["before"]["frame_wait"]), ", ".join(diff)])
	# puck_check_players: the puck against the players next to it in the draw order (goalie_save,
	# puck_hits_player, attach_puck_to_stick, take_puck, update_carrier, shot_landed); the routines
	# the emulator stubs are recorded here too (Sim.stubbed)
	var p_ok := 0
	var p_bad := 0
	sim.stubs = {"play_sfx": true, "queue_infraction": true, "maybe_queue_infraction": true, "knock_down": true,
		"follow_puck_user_switch": true}
	for c: Dictionary in ph["pickup"]:
		for i in 17:
			_entity_set(sim.entities[i], base[i])
		var befores: Dictionary = c["before"]
		for k in befores:
			_entity_set(sim.entities[int(k)], befores[k])
		var teams: Array = c["teams"]
		for t in 2:
			var team: Team = sim.teams[t]
			team.reset_stats()
			_team_set(team, teams[t])
		var order: Dictionary = c["order"]
		for i in 17:
			sim.draw_list[i] = int(order["list"][i])
			sim.draw_pos[i] = int(order["pos"][i])
			sim.draw_keys[i] = int(order["keys"][i])
		var g: Dictionary = c["globals"]
		sim.puck_carrier = int(c["carrier"])
		sim.play_stopped = (int(g["game_flags"]) & 1) != 0
		sim.no_stats = (int(g["game_flags"]) & 0x10) != 0
		sim.shot_in_flight = (int(g["stop_flags"]) & 0x10) != 0
		sim.power_play = (int(g["stop_flags"]) & 0x20) != 0
		sim.last_shooter = int(g["last_shooter"])
		sim.pass_target = int(g["pass_target"])
		sim.misc_first_touch = (int(g["misc_flags"]) & 0x10) != 0
		sim.last_passer = int(g["last_passer"])
		sim.last_touch_slot = int(g["last_touch"][0])
		sim.last_touch_y = int(g["last_touch"][1])
		sim.last_touch_x = int(g["last_touch"][2])
		sim.crowd_noise = int(g["crowd"])
		sim.excitement = int(g["excitement"])
		sim.opt_offsides = (int(g["options"]) & 2) != 0
		sim.opt_two_line_pass = (int(g["options"]) & 8) != 0
		sim.action_pass = (int(g["action_flags"]) & 4) != 0
		sim.action_shot = (int(g["action_flags"]) & 8) != 0
		sim.icing_flags = int(g["icing"][0])
		sim.icing_shooter = int(g["icing"][1])
		sim.goal_prediction[0][0] = int(g["prediction"][0])
		sim.goal_prediction[1][0] = int(g["prediction"][1])
		sim.save_clip_shown = int(g["save_clip_shown"]) != 0
		sim.gs_trailer[2] = int(g["summary_shots"][0])
		sim.gs_trailer[4] = int(g["summary_shots"][1])
		sim.penalty_shot = false
		sim.penalty_shot_setup = false
		sim.seed = int(c["seed"])
		sim.stub_calls.clear()
		PuckLogic.puck_check_players(sim)
		var diff := []
		var after: Dictionary = c["after"]
		for k in after:
			for d in _entity_diff(sim.entities[int(k)], after[k], befores[k]):
				diff.append("%s: %s" % [k, d])
		if sim.puck_carrier != int(c["carrier_after"]):
			diff.append("carrier %d (original %d)" % [sim.puck_carrier, int(c["carrier_after"])])
		var want_calls: Array = c["calls"]
		if str(sim.stub_calls) != str(_ints(want_calls)):
			diff.append("calls %s (original %s)" % [str(sim.stub_calls), str(want_calls)])
		var ga: Dictionary = c["globals_after"]
		var got := {"stop_flags": (0x10 if sim.shot_in_flight else 0) | (0x20 if sim.power_play else 0),
			"last_passer": sim.last_passer, "last_touch": [sim.last_touch_slot, sim.last_touch_y, sim.last_touch_x],
			"pass_target": sim.pass_target, "misc_flags": 0x10 if sim.misc_first_touch else 0,
			"action_flags": (4 if sim.action_pass else 0) | (8 if sim.action_shot else 0), "crowd": sim.crowd_noise,
			"excitement": sim.excitement, "icing": [sim.icing_flags, sim.icing_shooter],
			"summary_shots": [sim.gs_trailer[2], sim.gs_trailer[4]]}
		for k in got:
			var w = _ints(ga[k])
			if k == "action_flags":
				w &= 0xc
			if str(got[k]) != str(w):
				diff.append("%s %s (original %s)" % [k, str(got[k]), str(w)])
		var tas: Array = c["teams_after"]
		for t in 2:
			for d in _team_diff(sim.teams[t], tas[t]):
				diff.append("team %d %s" % [t, d])
		if sim.seed != int(c["final_seed"]):
			diff.append("seed")
		if diff.is_empty():
			p_ok += 1
		else:
			p_bad += 1
			if p_bad <= 8:
				fail("puck_check_players carrier %d puck %d,%d z %d v %d,%d slots %s: %s" % [int(c["carrier"]), int(befores["14"]["x"]) >> 16, int(befores["14"]["y"]) >> 16, int(befores["14"]["z"]) >> 16, int(befores["14"]["vx"]), int(befores["14"]["vy"]), str(befores.keys()), ", ".join(diff.slice(0, 8))])
	sim.stubs = {}
	# body contacts: move_entity among opponents (collide_pair, goalie_collision), resolve_body_check
	# and knock_down called directly
	var b_ok := 0
	var b_bad := 0
	sim.stubs = {"play_sfx": true, "queue_infraction": true, "maybe_queue_infraction": true, "injury_check": true,
		"injure_player": true, "bench_cheer": true, "start_stoppage": true}
	Rules.clear_infractions(sim)
	for c: Dictionary in ph["checks"]:
		for i in 17:
			_entity_set(sim.entities[i], base[i])
			sim.entities[i].prev_x = int(base[i]["prev"][0])
			sim.entities[i].prev_y = int(base[i]["prev"][1])
			sim.entities[i].prev_z = int(base[i]["prev"][2])
		var befores: Dictionary = c["before"]
		for k in befores:
			var e: Entity = sim.entities[int(k)]
			_entity_set(e, befores[k])
			e.prev_x = int(befores[k]["prev"][0])
			e.prev_y = int(befores[k]["prev"][1])
			e.prev_z = e.z
		var teams: Array = c["teams"]
		for t in 2:
			var team: Team = sim.teams[t]
			for i in 28:
				team.energy[i] = int(teams[t]["energy"])
				team.entity_of[i] = int(teams[t]["entity_of"][i])
			team.hits = int(teams[t]["hits"])
			team.skaters_on_ice = int(teams[t]["skaters"])
			team.goalie_request = int(teams[t]["goalie_request"]) & 0xffff
		for i in 12:
			var e: Entity = sim.entities[i]
			e.energy = sim.teams[e.team].energy[e.roster_idx] if e.roster_idx >= 0 and e.roster_idx < 28 else 0x1000
		var order: Dictionary = c["order"]
		for i in 17:
			sim.draw_list[i] = int(order["list"][i])
			sim.draw_pos[i] = int(order["pos"][i])
			sim.draw_keys[i] = int(order["keys"][i])
		var g: Dictionary = c["globals"]
		var gf := int(g["game_flags"])
		sim.play_stopped = (gf & 1) != 0
		sim.delayed_call = (gf & 8) != 0
		sim.no_stats = (gf & 0x10) != 0
		var opt := int(g["options"])
		sim.opt_penalties = (opt & 1) != 0
		sim.opt_offsides = (opt & 2) != 0
		sim.opt_line_changes = (opt & 4) != 0
		sim.opt_two_line_pass = (opt & 8) != 0
		sim.opt_injuries = (opt & 0x10) != 0
		sim.period = int(g["period"])
		sim.settings2 = int(g["settings2"])
		sim.breakaway = int(g["breakaway"]) != 0
		sim.defenders_ahead = int(g["defenders_ahead"])
		sim.penalty_shot_slot = int(g["penalty_shot_slot"])
		sim.penalty_shot_user = int(g["penalty_shot_user"])
		sim.crowd_toggle = int(g["crowd_hit_toggle"]) != 0
		sim.ref_hits = int(g["ref_hits"])
		sim.box_count = [int(g["box_home"]), int(g["box_away"])]
		sim.user1_slot = int(g["user1_slot"])
		sim.crowd_noise = int(g["crowd"])
		sim.excitement = int(g["excitement"])
		sim.last_impact = int(g["last_impact"])
		sim.action_pass = (int(g["action_flags"]) & 4) != 0
		sim.action_shot = (int(g["action_flags"]) & 8) != 0
		sim.puck_in_net = false
		if not befores.has("14"):
			sim.puck.x = int(g["puck"][0]) << 16
			sim.puck.y = int(g["puck"][1]) << 16
		sim.puck_carrier = int(c["carrier"])
		sim.seed = int(c["seed"])
		sim.stub_calls.clear()
		var mover: Entity = sim.entities[int(c["mover"])]
		var other: Entity = sim.entities[int(c["other"])]
		match String(c["mode"]):
			"move":
				sim.move_entity(mover)
			"body":
				PuckLogic.resolve_body_check(sim, mover, other, int(c["strength"]))
			"knock":
				PuckLogic.knock_down(sim, other, mover)
		var diff := []
		var after: Dictionary = c["after"]
		for k in after:
			for d in _entity_diff(sim.entities[int(k)], after[k], befores[k]):
				diff.append("%s: %s" % [k, d])
		if sim.puck_carrier != int(c["carrier_after"]):
			diff.append("carrier %d (original %d)" % [sim.puck_carrier, int(c["carrier_after"])])
		if str(sim.stub_calls) != str(_ints(c["calls"])):
			diff.append("calls %s (original %s)" % [str(sim.stub_calls), str(c["calls"])])
		var gfa := int(c["game_flags_after"])
		if sim.play_stopped != ((gfa & 1) != 0):
			diff.append("play_stopped %s" % sim.play_stopped)
		var ga: Dictionary = c["globals_after"]
		var got := {"period": sim.period, "settings2": sim.settings2, "breakaway": 1 if sim.breakaway else 0,
			"defenders_ahead": sim.defenders_ahead, "penalty_shot_slot": sim.penalty_shot_slot,
			"penalty_shot_user": sim.penalty_shot_user, "crowd_hit_toggle": 1 if sim.crowd_toggle else 0,
			"ref_hits": sim.ref_hits, "box_home": sim.box_count[0], "box_away": sim.box_count[1],
			"user1_slot": sim.user1_slot, "crowd": sim.crowd_noise, "excitement": sim.excitement,
			"last_impact": sim.last_impact, "action_flags": (4 if sim.action_pass else 0) | (8 if sim.action_shot else 0),
			"puck_in_net": 1 if sim.puck_in_net else 0}
		for k in got:
			var w: int = int(ga[k])
			if k == "action_flags":
				w &= 0xc
			if k == "puck_in_net":
				w = 1 if w != 0 else 0
			if got[k] != w:
				diff.append("%s %d (original %d)" % [k, got[k], w])
		for t in 2:
			if sim.teams[t].hits != int(c["hits_after"][t]):
				diff.append("team %d hits %d (original %d)" % [t, sim.teams[t].hits, int(c["hits_after"][t])])
		if sim.seed != int(c["final_seed"]):
			diff.append("seed")
		if diff.is_empty():
			b_ok += 1
		else:
			b_bad += 1
			if b_bad <= 10:
				fail("body contact %s %d/%d anims %x/%x: %s" % [String(c["mode"]), mover.slot, other.slot, int(befores[str(mover.slot)]["anim"]), int(befores[str(other.slot)]["anim"]) if befores.has(str(other.slot)) else 0, ", ".join(diff.slice(0, 8))])
	sim.stubs = {}
	sim.play_stopped = false
	sim.no_stats = false
	sim.delayed_call = false
	sim.penalty_shot_slot = -1
	# puck_update: the goal line prediction, the puck on the carrier's stick, icing, offside, the
	# two line pass flags, the penalty shot timer, the frozen puck, the flat disc, the pickups
	var u_ok := 0
	var u_bad := 0
	sim.stubs = {"play_sfx": true, "queue_infraction": true, "maybe_queue_infraction": true, "injury_check": true,
		"injure_player": true, "bench_cheer": true, "start_stoppage": true}
	for c: Dictionary in ph["update"]:
		var befores: Dictionary = c["before"]
		for k in befores:
			var e: Entity = sim.entities[int(k)]
			_entity_set(e, befores[k])
			e.prev_x = int(befores[k]["prev"][0])
			e.prev_y = int(befores[k]["prev"][1])
			e.prev_z = int(befores[k]["prev"][2])
		var g: Dictionary = c["globals"]
		var gf := int(g["game_flags"])
		sim.play_stopped = (gf & 1) != 0
		sim.ends_switched = (gf & 2) != 0
		sim.no_stats = (gf & 0x10) != 0
		var opt := int(g["options"])
		sim.opt_penalties = (opt & 1) != 0
		sim.opt_offsides = (opt & 2) != 0
		sim.opt_line_changes = (opt & 4) != 0
		sim.opt_two_line_pass = (opt & 8) != 0
		sim.opt_injuries = (opt & 0x10) != 0
		var teams: Array = c["teams"]
		for t in 2:
			var team: Team = sim.teams[t]
			team.reset_stats()
			_team_set(team, teams[t])
			team.breakaways = int(teams[t]["breakaways"])
			team.nearest_dist = int(teams[t]["nearest"])
			team.attacks_up = (t == 0) != sim.ends_switched
			for i in 28:
				team.entity_of[i] = -1
		var order: Dictionary = c["order"]
		for i in 17:
			sim.draw_list[i] = int(order["list"][i])
			sim.draw_pos[i] = int(order["pos"][i])
			sim.draw_keys[i] = int(order["keys"][i])
		sim.crowd_noise = int(g["crowd"])
		sim.excitement = int(g["excitement"])
		sim.breakaway = int(g["breakaway"]) != 0
		sim.defenders_ahead = int(g["defenders_ahead"])
		sim.penalty_shot_slot = int(g["penalty_shot_slot"])
		sim.penalty_shot_away = int(g["penalty_shot_timer"])
		sim.penalty_shot_team = int(g["penalty_shot_team"])
		sim.penalty_shot_phase = int(g["penalty_shot_phase"])
		sim.penalty_shot = int(g["penalty_shot_active"]) != 0
		sim.penalty_shot_setup = int(g["penalty_shot_setup"]) != 0
		sim.penalty_shot_spot = Vector2i(int(g["spot_x"]), int(g["spot_y"]))
		sim.user1_slot = int(g["user1_slot"])
		sim.user2_slot = int(g["user2_slot"])
		sim.user1_team = int(g["user1_team"])
		sim.user2_team = int(g["user2_team"])
		sim.last_touch_slot = int(g["last_touch_slot"])
		sim.last_touch_y = int(g["last_touch_y"])
		sim.last_touch_x = int(g["last_touch_x"])
		sim.icing_flags = int(g["icing_flags"])
		sim.icing_shooter = int(g["icing_shooter"])
		sim.goal_prediction[0][0] = int(g["pred0_x"])
		sim.goal_prediction[0][1] = int(g["pred0_steps"])
		sim.goal_prediction[1][0] = int(g["pred1_x"])
		sim.goal_prediction[1][1] = int(g["pred1_steps"])
		sim.puck_goal_timer = int(g["goal_timer"])
		sim.puck_stuck_timer = int(g["stuck_timer"])
		sim.last_passer = int(g["last_passer"])
		sim.pass_target = int(g["pass_target"])
		sim.last_shooter = int(g["last_shooter"])
		sim.shot_in_flight = (int(g["stop_flags"]) & 0x10) != 0
		sim.power_play = (int(g["stop_flags"]) & 0x20) != 0
		sim.misc_first_touch = (int(g["misc_flags"]) & 0x10) != 0
		sim.action_pass = (int(g["action_flags"]) & 4) != 0
		sim.action_shot = (int(g["action_flags"]) & 8) != 0
		sim.save_clip_shown = false
		sim.puck_carrier = int(c["carrier"])
		sim.seed = int(c["seed"])
		sim.stub_calls.clear()
		PuckLogic.puck_update(sim)
		sim.puck.want_dir = sim.puck_stuck_timer & 0xff     # the puck's +0x28 word is the stuck timer
		sim.puck.dir_timer = Entity.to_s8(sim.puck_stuck_timer >> 8)
		sim.puck.timer_a = sim.puck_goal_timer              # and its +0x26 the prediction timer
		var diff := []
		var after: Dictionary = c["after"]
		for k in after:
			for d in _entity_diff(sim.entities[int(k)], after[k], befores[k]):
				diff.append("%s: %s" % [k, d])
		if sim.puck_carrier != int(c["carrier_after"]):
			diff.append("carrier %d (original %d)" % [sim.puck_carrier, int(c["carrier_after"])])
		if str(sim.stub_calls) != str(_ints(c["calls"])):
			diff.append("calls %s (original %s)" % [str(sim.stub_calls), str(c["calls"])])
		var ga: Dictionary = c["globals_after"]
		var got := {"crowd": sim.crowd_noise, "excitement": sim.excitement, "breakaway": 1 if sim.breakaway else 0,
			"defenders_ahead": sim.defenders_ahead, "penalty_shot_slot": sim.penalty_shot_slot,
			"penalty_shot_timer": sim.penalty_shot_away, "penalty_shot_team": sim.penalty_shot_team,
			"penalty_shot_phase": sim.penalty_shot_phase, "penalty_shot_active": 1 if sim.penalty_shot else 0,
			"penalty_shot_setup": 1 if sim.penalty_shot_setup else 0, "spot_x": sim.penalty_shot_spot.x,
			"spot_y": sim.penalty_shot_spot.y, "user1_slot": sim.user1_slot, "user2_slot": sim.user2_slot,
			"user1_team": sim.user1_team, "user2_team": sim.user2_team, "last_touch_slot": sim.last_touch_slot,
			"last_touch_y": sim.last_touch_y, "last_touch_x": sim.last_touch_x, "icing_flags": sim.icing_flags,
			"icing_shooter": sim.icing_shooter & 0xff, "pred0_x": sim.goal_prediction[0][0],
			"pred0_steps": sim.goal_prediction[0][1], "pred1_x": sim.goal_prediction[1][0],
			"pred1_steps": sim.goal_prediction[1][1], "goal_timer": sim.puck_goal_timer, "stuck_timer": sim.puck_stuck_timer,
			"last_passer": sim.last_passer, "pass_target": sim.pass_target, "last_shooter": sim.last_shooter,
			"stop_flags": (0x10 if sim.shot_in_flight else 0) | (0x20 if sim.power_play else 0),
			"misc_flags": 0x10 if sim.misc_first_touch else 0,
			"action_flags": (4 if sim.action_pass else 0) | (8 if sim.action_shot else 0)}
		for k in got:
			var w: int = int(ga[k])
			if k == "action_flags":
				w &= 0xc
			elif k == "misc_flags":
				w &= 0x10
			elif k == "stop_flags":
				w &= 0x30
			if int(got[k]) != w:
				diff.append("%s %d (original %d)" % [k, int(got[k]), w])
		var tas: Array = c["teams_after"]
		for t in 2:
			var want: Dictionary = tas[t].duplicate()
			want["player_shots"] = []
			want["goalie_shots"] = []
			for d in _team_diff(sim.teams[t], want, false):
				diff.append("team %d %s" % [t, d])
			if sim.teams[t].breakaways != int(tas[t]["breakaways"]):
				diff.append("team %d breakaways %d (original %d)" % [t, sim.teams[t].breakaways, int(tas[t]["breakaways"])])
		if sim.seed != int(c["final_seed"]):
			diff.append("seed")
		if diff.is_empty():
			u_ok += 1
		else:
			u_bad += 1
			if u_bad <= 10:
				fail("puck_update carrier %d puck %d,%d prev %d,%d: %s" % [int(c["carrier"]), int(befores["14"]["x"]) >> 16, int(befores["14"]["y"]) >> 16, int(befores["14"]["prev"][0]) >> 16, int(befores["14"]["prev"][1]) >> 16, ", ".join(diff.slice(0, 8))])
	sim.stubs = {}
	sim.play_stopped = false
	sim.no_stats = false
	sim.ends_switched = false
	sim.penalty_shot = false
	sim.penalty_shot_setup = false
	sim.penalty_shot_slot = -1
	sim.teams[0].attacks_up = true
	sim.teams[1].attacks_up = false
	# passing and shooting: do_pass, pass_lane_ok, pass_lead, start_shot, shot_control, do_shot,
	# shot_setup
	var s_ok := 0
	var s_bad := 0
	sim.stubs = {"play_sfx": true, "queue_infraction": true, "maybe_queue_infraction": true}
	for c: Dictionary in ph["shoot"]:
		var befores: Dictionary = c["before"]
		for k in befores:
			_entity_set(sim.entities[int(k)], befores[k])
		var extra: Dictionary = c["extra"]
		for k in extra:
			var e: Entity = sim.entities[int(k)]
			e.pass_ok = int(extra[k][0])
			e.shot_accuracy = int(extra[k][1])
			e.pass_target = int(extra[k][2])
			e.react_timer = int(extra[k][3])
		var g: Dictionary = c["globals"]
		var gf := int(g["game_flags"])
		sim.play_stopped = (gf & 1) != 0
		sim.ends_switched = (gf & 2) != 0
		sim.no_stats = (gf & 0x10) != 0
		var teams: Array = c["teams"]
		for t in 2:
			var team: Team = sim.teams[t]
			team.attacks_up = (t == 0) != sim.ends_switched
			team.passes = int(teams[t]["passes"])
			for i in 28:
				team.energy[i] = int(teams[t]["energy"])
				team.entity_of[i] = -1
		sim.pending_dir = int(g["pending_dir"])
		sim.shot_power = int(g["shot_power"])
		sim.pass_target = int(g["pass_target"])
		sim.last_passer = int(g["last_passer"])
		sim.last_shooter = int(g["last_shooter"])
		sim.action_pass = (int(g["action_flags"]) & 4) != 0
		sim.action_shot = (int(g["action_flags"]) & 8) != 0
		sim.shot_in_flight = (int(g["stop_flags"]) & 0x10) != 0
		sim.power_play = false
		sim.one_timer = int(g["one_timer"]) != 0
		sim.breakaway = int(g["breakaway"]) != 0
		sim.defenders_ahead = int(g["defenders_ahead"])
		sim.user1_slot = int(g["user1_slot"])
		sim.user2_slot = int(g["user2_slot"])
		sim.user1_team = int(g["user1_team"])
		sim.user2_team = int(g["user2_team"])
		sim.penalty_shot = int(g["penalty_shot_active"]) != 0
		sim.puck_carrier = int(c["carrier"])
		sim.seed = int(c["seed"])
		sim.stub_calls.clear()
		var e: Entity = sim.entities[int(c["shooter"])]
		var r: Entity = sim.entities[int(c["receiver"])]
		var result := 0
		var sc: Array = g["scratch"]
		match String(c["mode"]):
			"pass": PuckLogic.do_pass(sim, e)
			"lane": result = 1 if PuckLogic.pass_lane_ok(sim, e, r) else 0
			"lead": PuckLogic.pass_lead(sim, r)
			"start": PuckLogic.start_shot(sim, e)
			"control": PuckLogic.shot_control(sim, e, int(sc[0]), int(sc[1]) & 0xff, int(sc[2]) & 0xff)
			"shot": PuckLogic.do_shot(sim, e)
			"setup": PuckLogic.shot_setup(sim, e)
		var diff := []
		var after: Dictionary = c["after"]
		for k in after:
			for d in _entity_diff(sim.entities[int(k)], after[k], befores[k]):
				diff.append("%s: %s" % [k, d])
		var xa: Dictionary = c["extra_after"]
		for k in xa:
			var x: Entity = sim.entities[int(k)]
			if x.pass_ok != int(xa[k][0]) or Entity.to_s8(x.react_timer) != int(xa[k][1]):
				diff.append("%s: pass_ok %d react %d (original %s)" % [k, x.pass_ok, x.react_timer, str(xa[k])])
		if result != int(c["result"]):
			diff.append("result %d (original %d)" % [result, int(c["result"])])
		if sim.puck_carrier != int(c["carrier_after"]):
			diff.append("carrier %d (original %d)" % [sim.puck_carrier, int(c["carrier_after"])])
		if str(sim.stub_calls) != str(_ints(c["calls"])):
			diff.append("calls %s (original %s)" % [str(sim.stub_calls), str(c["calls"])])
		var ga: Dictionary = c["globals_after"]
		var got := {"pending_dir": sim.pending_dir, "shot_power": sim.shot_power, "pass_target": sim.pass_target,
			"last_passer": sim.last_passer, "last_shooter": sim.last_shooter,
			"action_flags": (4 if sim.action_pass else 0) | (8 if sim.action_shot else 0),
			"stop_flags": 0x10 if sim.shot_in_flight else 0, "one_timer": 1 if sim.one_timer else 0,
			"breakaway": 1 if sim.breakaway else 0, "defenders_ahead": sim.defenders_ahead,
			"user1_slot": sim.user1_slot, "user2_slot": sim.user2_slot, "user1_team": sim.user1_team,
			"user2_team": sim.user2_team, "penalty_shot_active": 1 if sim.penalty_shot else 0}
		for k in got:
			var w: int = int(ga[k])
			if k == "action_flags":
				w &= 0xc
			elif k == "stop_flags":
				w &= 0x10
			if int(got[k]) != w:
				diff.append("%s %d (original %d)" % [k, int(got[k]), w])
		for t in 2:
			if sim.teams[t].passes != int(c["passes_after"][t]):
				diff.append("team %d passes %d (original %d)" % [t, sim.teams[t].passes, int(c["passes_after"][t])])
		if sim.seed != int(c["final_seed"]):
			diff.append("seed")
		if diff.is_empty():
			s_ok += 1
		else:
			s_bad += 1
			if s_bad <= 12:
				fail("%s by %d (to %d) aim %d power %d: %s" % [String(c["mode"]), e.slot, r.slot, int(g["pending_dir"]), int(g["shot_power"]), ", ".join(diff.slice(0, 8))])
	sim.stubs = {}
	sim.no_stats = false
	sim.ends_switched = false
	sim.penalty_shot = false
	sim.teams[0].attacks_up = true
	sim.teams[1].attacks_up = false
	sim.sort_draw_order()
	var cam_ok := _camera_golden(ph.get("camera", []))
	print("golden physics: %d / %d distances, collide_boards %d / %d, apply_skating %d / %d, at the nets %d / %d, move_entity %d / %d, advance_animation %d / %d, puck_check_players %d / %d, body contacts %d / %d, puck_update %d / %d, passes and shots %d / %d, update_camera %d / %d" % [ph["distance"].size() - dbad, ph["distance"].size(), ok, ph["boards"].size(), sk_ok, ph["skating"].size(), n_ok, ph["nets"].size(), c_ok, ph["contacts"].size(), a_ok, ph["animation"].size(), p_ok, ph["pickup"].size(), b_ok, ph["checks"].size(), u_ok, ph["update"].size(), s_ok, ph["shoot"].size(), cam_ok, ph.get("camera", []).size()])

## the numbers of a JSON value as ints (arrays too, strings kept)
static func _ints(v: Variant) -> Variant:
	if v is Array:
		return v.map(func(x): return _ints(x))
	if v is float:
		return int(v)
	return v

## the team record fields of the pickup cases (TEAM_FIELDS of golden.py), the shots of the players
## (+0xe6 records +0xe) and the goalies' shots against (+0xea)
static func _team_set(t: Team, f: Dictionary) -> void:
	for i in 28:
		t.energy[i] = int(f["energy"])
	t.shots = int(f["shots"])
	t.pp_shots = int(f["pp_shots"])
	t.faceoffs_won = int(f["faceoffs_won"])
	t.offensive_faceoffs = int(f["offensive_faceoffs"])
	t.passes_completed = int(f["passes_completed"])
	t.carrier_history = PackedInt32Array([int(f["carrier0"]), int(f["carrier1"]), int(f["carrier2"])])
	t.skaters_on_ice = int(f["skaters"])
	t.goalie_request = int(f["goalie_request"]) & 0xffff
	t.flags = int(f["flags"])

static func _team_diff(t: Team, want: Dictionary, stats := true) -> Array:
	var got := {"shots": t.shots, "pp_shots": t.pp_shots, "faceoffs_won": t.faceoffs_won,
		"offensive_faceoffs": t.offensive_faceoffs, "passes_completed": t.passes_completed,
		"carrier0": t.carrier_history[0], "carrier1": t.carrier_history[1], "carrier2": t.carrier_history[2],
		"skaters": t.skaters_on_ice, "goalie_request": Entity.to_s16(t.goalie_request), "flags": t.flags}
	var diff := []
	for k in got:
		if int(got[k]) != int(want[k]):
			diff.append("%s %d (original %d)" % [k, got[k], int(want[k])])
	if not stats:
		return diff
	var shots := []
	for r in 28:
		shots.append(t.stat(r, Team.ST_SHOTS))
	var want_shots: Array = want["player_shots"]
	if str(shots) != str(_ints(want_shots)):
		diff.append("player shots %s (original %s)" % [str(shots), str(want_shots)])
	var gshots := []
	for g in 3:
		gshots.append(t.goalie_stats[g][1])
	var want_g: Array = want["goalie_shots"]
	if str(gshots) != str(_ints(want_g)):
		diff.append("goalie shots %s (original %s)" % [str(gshots), str(want_g)])
	return diff

## the fields of physics.json (ENTITY_FIELDS of golden.py) to and from an entity of the port (+0x36,
## spin: the puck's spin bits, the others' facing, both in heading)
static func _entity_set(e: Entity, f: Dictionary) -> void:
	e.x = int(f["x"])
	e.y = int(f["y"])
	e.z = int(f["z"])
	e.vx = int(f["vx"])
	e.vy = int(f["vy"])
	e.vz = int(f["vz"])
	e.frame = int(f["frame"])
	e.hit_by = int(f["hit_by"])
	e.speed = int(f["speed"])
	e.line_slot = int(f["line_slot"])
	e.want_dir = int(f["want_dir"])
	e.target_x = int(f["target_x"])
	e.target_y = int(f["target_y"])
	e.push_x = int(f["push_x"])
	e.push_y = int(f["push_y"])
	e.heading = int(f["heading"]) & 0xffffffff
	e.anim = int(f["anim"])
	e.anim_pos = int(f["anim_pos"])
	e.anim_hold = int(f["anim_hold"])
	e.flags = int(f["flags"])
	e.flags2 = int(f["flags2"])
	e.frame_wait = int(f["frame_wait"])
	e.roster_idx = int(f["roster"]) if int(f["roster"]) < 0x80 else -1
	e.flags4 = int(f["flags4"])
	e.weight = int(f["weight"])
	e.speed_skill = int(f["speed_skill"])
	e.stamina = int(f["stamina"])
	e.endurance = int(f["endurance"])
	e.timer_b = int(f["timer_b"])
	e.timer_c = int(f["timer_c"])
	e.shot_skill = int(f["shot_skill"])
	e.pass_skill = int(f["pass_skill"])
	e.offense = int(f["offense"])
	e.goalie_skill = int(f["goalie_skill"])
	e.check_skill = int(f["check_skill"])
	e.save_result = int(f["save_result"])
	e.left_handed = int(f["left_handed"])
	e.aggression = int(f["aggression"])
	e.timer_d = int(f["timer_d"])
	e.state_sp = int(f["state_sp"])
	var st := int(f["stack"]) | (int(f["stack2"]) << 32)
	for i in 8:
		e.state_stack[i] = (st >> (8 * i)) & 0xff
	e.timer_a = int(f["timer_a"])
	e.dir_timer = int(f["dir_timer"])
	e.timer_e = int(f["timer_e"])
	e.timer_f = int(f["timer_f"])
	e.puck_dist = int(f["puck_dist"])
	e.puck_dist_sq = int(f["puck_dist_sq"])
	e.puck_dir = int(f["puck_dir"])
	e.pass_ok = int(f["pass_ok"])
	e.side = int(f["side"])
	e.reaction = int(f["reaction"])
	e.awareness = int(f["awareness"])
	e.shot_accuracy = int(f["accuracy"])
	e.number = int(f["number"])
	e.next_line_slot = int(f["next_line"])
	e.next_roster = int(f["next_roster"])
	e.pass_target = int(f["w48"])          # (flags3 is its low byte)

static func _entity_get(e: Entity) -> Dictionary:
	return {"x": e.x, "y": e.y, "z": e.z, "vx": e.vx, "vy": e.vy, "vz": e.vz, "frame": e.frame, "hit_by": e.hit_by,
		"speed": e.speed, "line_slot": e.line_slot, "want_dir": e.want_dir & 0xff, "target_x": e.target_x,
		"target_y": e.target_y, "push_x": e.push_x, "push_y": e.push_y,
		"heading": e.heading, "spin": e.spin,
		"anim": e.anim, "anim_pos": e.anim_pos, "anim_hold": e.anim_hold, "flags": e.flags, "flags2": e.flags2,
		"frame_wait": e.frame_wait, "roster": e.roster_idx & 0xff, "flags4": e.flags4, "weight": e.weight, "speed_skill": e.speed_skill,
		"stamina": e.stamina, "endurance": e.endurance, "timer_b": e.timer_b, "timer_c": e.timer_c,
		"shot_skill": e.shot_skill, "pass_skill": e.pass_skill, "offense": e.offense, "goalie_skill": e.goalie_skill,
		"check_skill": e.check_skill, "save_result": e.save_result, "left_handed": e.left_handed,
		"aggression": e.aggression, "timer_d": e.timer_d, "state_sp": e.state_sp,
		"stack": e.state_stack[0] | (e.state_stack[1] << 8) | (e.state_stack[2] << 16) | (e.state_stack[3] << 24),
		"stack2": e.state_stack[4] | (e.state_stack[5] << 8) | (e.state_stack[6] << 16) | (e.state_stack[7] << 24),
		"timer_a": Entity.to_s16(e.timer_a), "dir_timer": Entity.to_s8(e.dir_timer), "timer_e": e.timer_e, "timer_f": e.timer_f,
		"puck_dist": e.puck_dist, "puck_dist_sq": e.puck_dist_sq, "puck_dir": e.puck_dir & 0xff, "pass_ok": e.pass_ok,
		"side": e.side, "reaction": e.reaction, "awareness": e.awareness, "accuracy": e.shot_accuracy, "number": e.number,
		"next_line": Entity.to_s8(e.next_line_slot), "next_roster": Entity.to_s8(e.next_roster),
		"w48": e.pass_target}

## the fields of an entity that differ from the original's (heading: the 32 bit word); the golden
## data keeps only the fields the routine changed (after), the others are as before the call
static func _entity_diff(e: Entity, after: Dictionary, before: Dictionary) -> Array:
	var want := before.duplicate()
	want.merge(after, true)
	want.erase("prev")
	var got := _entity_get(e)
	var diff := []
	for k in want:
		if k == "next_line" and e.slot == Entity.Slot.PUCK:
			continue         # the puck's +0x42 is the carrier (Sim.puck_carrier, compared on its own)
		var w := int(want[k])
		if k == "heading":
			w &= 0xffffffff
		if int(got[k]) != w:
			diff.append("%s %d (original %d)" % [k, got[k], w])
	return diff

## a league of computer teams: the schedule, a whole season of simulated games, the play-offs
func league_tests(gf: Node) -> void:
	Exe.load_from(gf.read_raw("hockey.exe"))
	var src := {}
	for n in League.FILES:
		src[n] = gf.read_raw(n.to_lower() + ".db")
	League.srand(12345)
	var l := League.create("TESTLG", src, [], false)
	var g0 := l.game(0)
	if g0[0] != 10 or g0[2] >= 26 or g0[3] >= 26 or League.played(g0) or l.games_played() != 0:
		fail("league schedule: first game %s" % g0.hex_encode())
		return
	l.play_day(1, -1, 7)
	var teams := l.file("TEAMS")
	var gp_ok := true
	var goals := 0
	var against := 0
	for t in 26:
		var b := t * League.TEAM + 0x28
		if teams[b] != 84 or teams[b + 1] + teams[b + 2] + teams[b + 3] != 84:
			gp_ok = false
		goals += teams.decode_u16(b + 4)
		against += teams.decode_u16(b + 6)
	var unplayed := 0
	for i in League.SEASON_GAMES:
		if not League.played(l.game(i)):
			unplayed += 1
	if not gp_ok or goals != against or unplayed != 0:
		fail("league season: 84 games each %s, goals %d / %d, unplayed %d" % [gp_ok, goals, against, unplayed])
	var po := l.file("SCHEDULE").slice(League.PLAYOFF_OFFSET, League.PLAYOFF_OFFSET + 0x276)
	var champ := League.series_winner(po, 14, League.series_count(po, 14))
	if not l.season_over or l.games_played() != League.ALL_GAMES or champ < 0:
		fail("league play-offs: over %s, games %x, champion %d" % [l.season_over, l.games_played(), champ])
	else:
		print("league: %d goals in 1092 games, champion %s" % [goals, Database.cstring(teams, champ * League.TEAM, 5)])
	# the scorers of the season: a leader with a plausible number of points
	var key := l.file("KEY")
	var season := l.file("SEASON")
	var best := 0
	for t in 26:
		for p in 25:
			var k := l.key_of(t, p)
			if k >= 0:
				best = maxi(best, season.decode_u16(l.key_i32(k, 0x2c) + 6))
	if best < 40 or best > 250:
		fail("league scoring leader with %d points" % best)
	else:
		print("league: scoring leader %d points" % best)
	# a human team: its first game played by the match simulation and recorded, the computer
	# games up to that date simulated, nothing after it
	var h := League.create("TESTLG2", src, [12], false)
	var gi := h.next_game(12)
	var rec := h.game(gi)
	var db := Database.open(h.file("TEAMS"), h.file("KEY"), h.file("ATT"))
	var sim := Sim.new()
	sim.user1_team = 0
	sim.user2_team = 0
	sim.period_length = 20
	sim.set_teams(db.load_team(rec[2]), db.load_team(rec[3]))
	sim.assign_users()
	var steps := 0
	while not sim.match_over and steps < 60000:
		sim.step(8, 8, 0, 0)
		sim.intermission_pending = false
		steps += 1
	h.game_played(gi, sim)
	var hrec := h.game(gi)
	var tb := 12 * League.TEAM + 0x28
	var after := 0
	var before := 0
	var day := League.day_index(rec[0], rec[1])
	for i in League.SEASON_GAMES:
		var r := h.game(i)
		if League.played(r):
			if League.day_index(r[0], r[1]) > day:
				after += 1
		elif League.day_index(r[0], r[1]) <= day:
			before += 1
	var ht := h.file("TEAMS")
	if not sim.match_over or hrec[4] != sim.teams[0].goals or hrec[5] != sim.teams[1].goals or ht[tb] != 1 \
			or ht[tb + 1] + ht[tb + 2] + ht[tb + 3] != 1 or after != 0 or before != 0 or h.games_played() != gi + 1:
		fail("league game played: over %s, %s, GP %d, after %d, unplayed before %d, games %d" % [sim.match_over, hrec.hex_encode(), ht[tb], after, before, h.games_played()])
	else:
		print("league: game %d played %d-%d after %d steps" % [gi, hrec[4], hrec[5], steps])
	# play-off series: Rangers - Canucks meet in the final, Rangers - Bruins in the first round
	var ps := League.create_series("TESTPO", src, PackedByteArray(), 12, 21)
	var br := ps.bracket()
	var fin: Array = br[14]
	if not ((fin[0] == 12 and fin[1] == 21) or (fin[0] == 21 and fin[1] == 12)) or fin[2] != 0 or fin[3] != 0 or ps.games_played() != 0x4a6:
		fail("play-off series final: %s, games %x" % [str(fin), ps.games_played()])
	var ps2 := League.create_series("TESTPO2", src, PackedByteArray(), 12, 0)
	var met := false
	for s in 8:
		var sr: Array = ps2.bracket()[s]
		if (sr[0] == 12 and sr[1] == 0) or (sr[0] == 0 and sr[1] == 12):
			met = true
	if not met:
		fail("play-off series: Rangers and Bruins should meet in the first round")

## a saved game (SaveGame.gd): the state restored into a new simulation goes on exactly the same
func save_tests(bos: Database.TeamInfo, det: Database.TeamInfo) -> void:
	var a := Sim.new()
	a.user1_team = 0
	a.user2_team = 0
	a.set_teams(bos, det)
	a.assign_users()
	for i in 3000:
		a.step(8, 8, 0, 0)
	var data := var_to_bytes(SaveGame.capture(a))
	var b := Sim.new()
	b.user1_team = 0
	b.user2_team = 0
	b.set_teams(bos, det)
	SaveGame.restore(b, bytes_to_var(data))
	var same := true
	for i in 2000:
		a.step(8, 8, 0, 0)
		b.step(8, 8, 0, 0)
		for k in 17:
			if a.entities[k].x != b.entities[k].x or a.entities[k].y != b.entities[k].y:
				same = false
		if not same:
			fail("saved game diverges after %d steps" % i)
			return
	if a.clock_seconds != b.clock_seconds or a.teams[0].shots != b.teams[0].shots:
		fail("saved game: clock %d / %d" % [a.clock_seconds, b.clock_seconds])
	else:
		print("saved game: identical for 2000 steps after the restore")

## line changes, fatigue and goalie pulling (Lines.gd)
func line_change_tests(bos: Database.TeamInfo, det: Database.TeamInfo) -> void:
	# the user asks for the second line with F2: the first line skates to the bench and Boston's
	# second forward line (Hughes 18, Smolinski 20, Murray 44) and second pair come on
	var sim := Sim.new()
	sim.set_teams(bos, det)
	run_until_play(sim, 1200)
	var before := _dressed(sim, 0)
	sim.line_hotkey[0] = 1
	sim.line_hotkey_req[0] = 1
	var changed := false
	for i in 1500:
		sim.step(8, 8, 0, 0)
		var now := _dressed(sim, 0)
		if now.has(8) and now.has(1) and now.has(3) and not now.has(7) and not now.has(18):
			changed = true
			break
	if not changed:
		fail("F2 line change did not bring the second line on: before %s after %s (line %d)" % [str(before), str(_dressed(sim, 0)), sim.teams[0].current_line])
	elif sim.teams[0].current_line != 1 or sim.teams[0].dpair_counter != 1:
		fail("line bookkeeping after F2: line %d pair %d" % [sim.teams[0].current_line, sim.teams[0].dpair_counter])
	else:
		print("line change: second line on the ice after F2, dressed %s" % str(_dressed(sim, 0)))
	# everybody who left is on the bench, nobody is dressed twice (a player sent off on his way to
	# the box is in it already)
	var home := sim.teams[0]
	for i in 6:
		var e := sim.entities[i]
		var boxed := e.state() == Entity.State.PENALTY_BOX or e.state() == Entity.State.DOOR_OPEN
		if e.line_slot >= 0 and home.entity_of[e.roster_idx] != (1 if boxed else -1):
			fail("player %d on the ice but entity_of = %d" % [e.roster_idx, home.entity_of[e.roster_idx]])
	# the CPU coach: a tired line is replaced at the next faceoff
	sim = Sim.new()
	sim.set_teams(bos, det)
	run_until_play(sim, 1200)
	var away := sim.teams[1]
	for i in 6:
		var e := sim.entities[6 + i]
		if e.line_slot > 0:
			away.energy[e.roster_idx] = 0x400
	var cpu_before := _dressed(sim, 1)
	var cpu_changed := false
	Rules.maybe_queue_infraction(sim, sim.entities[1], Rules.INF_ICING)
	for i in 3000:
		sim.step(8, 8, 0, 0)
		if away.current_line != 0:
			cpu_changed = true
	run_until_play(sim, 2400)
	var cpu_after := _dressed(sim, 1)
	if not cpu_changed or cpu_after == cpu_before:
		fail("the CPU did not change its tired line: line %d before %s after %s" % [away.current_line, str(cpu_before), str(cpu_after)])
	else:
		print("CPU line change: line %d, dressed %s" % [away.current_line, str(cpu_after)])
	# fatigue: skaters lose energy during play, benched players recover
	for i in 120:
		sim.step(8, 8, 0, 0)
	var tired := false
	for r in 25:
		if away.entity_of[r] == -1 and away.energy[r] < 0x1000:
			tired = true
	var e_bench := -1
	for r in 25:
		if away.entity_of[r] == -2 and cpu_before.has(r):
			e_bench = away.energy[r]
	if not tired:
		fail("no skater lost energy")
	if e_bench >= 0 and e_bench <= 0x400:
		fail("benched players do not recover energy: %d" % e_bench)
	# pulling the goalie: six skaters, the goalie entity takes the extra attacker; F9 again returns him
	sim = Sim.new()
	sim.set_teams(bos, det)
	run_until_play(sim, 1200)
	Lines.toggle_pull_goalie(sim, 0)
	if sim.message != Lines.MSG_PULL_GOALIE:
		fail("PULL GOALIE message not shown (%d)" % sim.message)
	var pulled := false
	for i in 1500:
		sim.step(8, 8, 0, 0)
		var goalies := 0
		var skaters := 0
		for k in 6:
			var e := sim.entities[k]
			if e.line_slot == 0:
				goalies += 1
			elif e.line_slot > 0:
				skaters += 1
		if goalies == 0 and skaters == 6:
			pulled = true
			break
	if not pulled:
		fail("the goalie was not pulled (dressed %s request %x)" % [str(_dressed(sim, 0)), sim.teams[0].goalie_request])
	elif sim.teams[0].extra_attacker < 0 or sim.teams[0].entity_of[25] != -2:
		fail("extra attacker %d, goalie entity_of %d" % [sim.teams[0].extra_attacker, sim.teams[0].entity_of[25]])
	else:
		print("goalie pulled: extra attacker roster %d" % sim.teams[0].extra_attacker)
		Lines.toggle_pull_goalie(sim, 0)
		var back := false
		for i in 1500:
			sim.step(8, 8, 0, 0)
			for k in 6:
				if sim.entities[k].line_slot == 0 and sim.entities[k].roster_idx == 25:
					back = true
			if back:
				break
		if not back:
			fail("the goalie did not return")
	# a delayed penalty against Detroit: Boston pulls the goalie by itself while it has the puck
	sim = Sim.new()
	sim.set_teams(bos, det)
	sim.user1_team = 0
	sim.new_game()
	run_until_play(sim, 1200)
	var carrier := sim.entities[sim.centre_slot(0)]
	sim.puck_carrier = carrier.slot
	sim.puck.set_pos(carrier.xi, carrier.yi)
	sim.delayed_call = true
	var auto_pull := false
	for i in 20:
		sim.step(8, 8, 0, 0)
		if sim.teams[0].goalie_pulled():
			auto_pull = true
			break
	if not auto_pull:
		fail("no extra attacker on the delayed call")

## penalty shot, game misconduct, injuries, board knockdowns (Rules.gd, PuckLogic.gd)
func match_rules_tests(bos: Database.TeamInfo, det: Database.TeamInfo) -> void:
	# a foul on a breakaway: a penalty shot. Both teams are CPU controlled so the shooter skates.
	var sim := Sim.new()
	sim.set_teams(bos, det)
	run_until_play(sim, 1200)
	# (not in the first tick of the game: the faceoff wait is skipped while the clock shows 5:00)
	for i in 30:
		sim.step(8, 8, 0, 0)
	var victim := sim.entities[sim.user1_slot]
	sim.user1_slot = sim.find_switch_target(-1, sim.user1_slot)
	sim.user1_team = 0
	var culprit := sim.entities[7]
	victim.set_pos(0, 60)
	victim.facing = 0
	victim.vy = 0x200
	sim.puck_carrier = victim.slot
	sim.breakaway = true
	if not Rules.breakaway_foul(sim, victim):
		fail("a foul on the breakaway carrier should give a penalty shot")
		return
	Rules.award_penalty_shot(sim, victim, culprit)
	var spot := Vector2i(-1000, -1000)
	var started := -1
	var lined_up := true
	var ended := -1
	var goals := sim.teams[0].goals
	for i in 4000:
		sim.step(8, 8, 0, 0)
		if spot.x == -1000 and sim.penalty_shot_phase != 0:
			spot = sim.penalty_shot_spot
		if started < 0 and sim.penalty_shot:
			started = i
			# the shooter has the puck at centre ice, everybody else but the defending goalie is off
			if sim.puck_carrier != victim.slot or absi(victim.xi) > 2 or absi(victim.yi) > 12 or victim.state() != Entity.State.BREAKAWAY:
				lined_up = false
			for k in 12:
				var p := sim.entities[k]
				if p == victim or (p.team == 1 and p.line_slot == 0):
					continue
				if p.line_slot >= 0 and p.frame != -1:
					lined_up = false
		if started >= 0 and ended < 0 and not sim.penalty_shot:
			ended = i
		if ended >= 0 and not sim.play_stopped and sim.penalty_shot_phase == 0 and not sim.penalty_shot_setup:
			break
	if started < 0:
		fail("the penalty shot did not start (phase %d ref %s)" % [sim.penalty_shot_phase, Tables.ai_state_names[sim.referee.state() + 1]])
	elif not lined_up:
		var off := []
		for k in 12:
			var p := sim.entities[k]
			if p.line_slot >= 0 and p.frame != -1:
				off.append([k, p.line_slot, Tables.ai_state_names[p.state() + 1], p.xi, p.yi])
		fail("penalty shot line up: shooter %d at %d,%d carrier %d state %s, on the ice %s" % [victim.slot, victim.xi, victim.yi, sim.puck_carrier, Tables.ai_state_names[victim.state() + 1], str(off)])
	elif ended < 0 or sim.play_stopped:
		fail("the penalty shot did not end (clock %d)" % sim.penalty_shot_clock)
	else:
		var scored := sim.teams[0].goals > goals
		var want := Vector2i.ZERO if scored else spot
		if not scored and (sim.faceoff_x != want.x or sim.faceoff_y != want.y):
			fail("faceoff after the penalty shot at %d,%d, expected %d,%d" % [sim.faceoff_x, sim.faceoff_y, want.x, want.y])
		else:
			print("penalty shot: started after %d steps, over after %d more, %s" % [started, ended - started, "goal" if scored else "no goal"])
	# three body checks on the referee by a user: abuse of official, the player is thrown out
	sim = Sim.new()
	sim.set_teams(bos, det)
	run_until_play(sim, 1200)
	var bully := sim.entities[sim.user1_slot]
	var roster := bully.roster_idx
	for k in 3:
		sim.referee.speed = 0x200        # the impact: he cannot stay on his feet
		sim.referee.anim = 0
		bully.anim = Anim.BODY_CHECK
		PuckLogic.check_hit(sim, bully, sim.referee, 0x30)
	var queued := false
	for i in Rules.inf_count(sim):
		if Rules.inf_type(sim, i) == Rules.INF_ABUSE_OF_OFFICIAL:
			queued = true
	if not queued:
		fail("three hits on the referee should be a game misconduct (hits %d)" % sim.ref_hits)
	else:
		var gone := false
		for i in 3000:
			sim.step(8, 8, 0, 0)
			if sim.teams[0].entity_of[roster] == -5 and not sim.play_stopped:
				gone = true
				break
		if not gone or _dressed(sim, 0).has(roster):
			fail("the thrown out player is still dressed (status %d)" % sim.teams[0].entity_of[roster])
		else:
			print("game misconduct: roster %d out, dressed %s" % [roster, str(_dressed(sim, 0))])
	# the message box: ICING for 0x50 frames, a penalty's PENALTY until it is handed out
	sim = Sim.new()
	sim.set_teams(bos, det)
	run_until_play(sim, 1200)
	Rules.maybe_queue_infraction(sim, sim.entities[2], Rules.INF_ICING)
	if sim.message != 5 or sim.message_timer != 0x50:
		fail("icing message %d / %d" % [sim.message, sim.message_timer])
	# an injury: out for the period (or the game), back in the next period
	sim = Sim.new()
	sim.set_teams(bos, det)
	run_until_play(sim, 1200)
	var hurt := sim.entities[2]
	sim.last_impact = 5
	PuckLogic.injure_player(sim, hurt)
	Rules.queue_infraction(sim, sim.entities[8], Rules.INF_INJURY)
	if sim.teams[0].entity_of[hurt.roster_idx] != -3 or (hurt.flags2 & Entity.F2_UNSELECTABLE) == 0:
		fail("a light injury keeps the player out for the period (status %d)" % sim.teams[0].entity_of[hurt.roster_idx])
	else:
		# the whistle: a 0x140 step stoppage, then a cut to the faceoff without the referee's walk
		sim.step(8, 8, 0, 0)
		if sim.stoppage_timer < 0x13e or not sim.injury_stoppage:
			fail("injury stoppage timer %d" % sim.stoppage_timer)
		var cut := false
		# (the user's line change prompt at the faceoff runs its 0x258 steps without a button)
		for i in 2400:
			sim.step(8, 8, 0, 0)
			if sim.fade_in:
				cut = true
			if not sim.play_stopped:
				break
		if not cut or sim.play_stopped or sim.injury_stoppage:
			fail("no cut to the faceoff after the injury (stopped %s)" % sim.play_stopped)
		var hr := hurt.roster_idx
		sim.start_period(1)
		if sim.teams[0].entity_of[hr] == -3:
			fail("the injured player should be back for the next period")
	# a check against the right boards pins the victim to them (board animation, x from the table)
	sim = Sim.new()
	sim.set_teams(bos, det)
	run_until_play(sim, 1200)
	var pinned := sim.entities[8]
	var hitter := sim.entities[3]
	pinned.set_pos(0x90, 0)
	hitter.set_pos(0x80, 0)
	pinned.goalie_skill = 0
	pinned.anim = 0
	pinned.flags2 &= ~Entity.F2_KNOCKED
	PuckLogic.knock_down(sim, hitter, pinned)
	var f := pinned.facing
	if pinned.anim == 0xf9b:
		if pinned.xi != Tables.knockdown_right_x[f]:
			fail("board knockdown x %d" % pinned.xi)
	elif pinned.anim == 0xfe1:
		if pinned.xi != -Tables.knockdown_left_x[(8 - f) & 7]:
			fail("board knockdown x %d (mirrored)" % pinned.xi)
	else:
		fail("a hit against the boards should use a board animation, got %x" % pinned.anim)

## the anthem, the goal panel, the end of the game, the three stars, overtime and the cup
func ceremony_tests(bos: Database.TeamInfo, det: Database.TeamInfo) -> void:
	# the anthem: blue lines, the US flag clip for Boston, then the opening faceoff
	var sim := Sim.new()
	sim.set_teams(bos, det)
	Ceremonies.begin_anthem(sim)
	var ok := sim.intro and sim.clip == InfoPanel.CLIP_USA_FLAG
	for i in 12:
		var e := sim.entities[i]
		if e.line_slot == 0 and absi(e.yi) != 0xdc:
			ok = false
		if e.line_slot > 0 and (absi(e.yi) < 0x2e or absi(e.yi) > 0x3c or e.state() != Entity.State.ANTHEM):
			ok = false
	if not ok:
		fail("anthem line up (intro %s clip %d)" % [sim.intro, sim.clip])
	var steps := 0
	while sim.intro and steps < 3000:
		sim.step(8, 8, 0, 0)
		steps += 1
	var drop := run_until_play(sim, 2000)
	if sim.intro or drop < 0:
		fail("the anthem did not end in a faceoff (steps %d, intro %s)" % [steps, sim.intro])
	else:
		print("anthem: %d steps, faceoff %d steps later" % [steps, drop])
	sim = Sim.new()
	sim.set_teams(bos, det)
	Ceremonies.begin_anthem(sim)
	sim.step(8, 8, 0x20, 0)
	if sim.intro:
		fail("a button should skip the anthem")
	# a goal: the panel opens with the scorer and the assists and the referee waits for it
	sim = Sim.new()
	sim.set_teams(bos, det)
	run_until_play(sim, 1200)
	var home := sim.teams[0]
	home.carrier_history = PackedInt32Array([7, 10, -1])
	sim.last_touch_slot = 4
	Rules.score_goal(sim, sim.entities[Entity.Slot.NET_TOP] if home.attacks_up else sim.entities[Entity.Slot.NET_BOTTOM])
	var opened := -1
	var shown := ""
	for i in 1500:
		sim.step(8, 8, 0, 0)
		if opened < 0 and sim.panel >= 0:
			opened = i
			shown = "%s | %s | %s | %s" % sim.panel_text.slice(0, 4)
		if opened >= 0 and not sim.play_stopped:
			break
	if opened < 0 or not shown.contains("Boston") or not shown.contains("Assists:") or home.stat(7, Team.ST_GOALS) != 1 or home.stat(10, Team.ST_ASSISTS) != 1:
		fail("goal panel: '%s' goals %d assists %d" % [shown, home.stat(7, Team.ST_GOALS), home.stat(10, Team.ST_ASSISTS)])
	else:
		print("goal panel: ", shown)
	# the game summary: the goal record (team, scorer, assists, period 1) and the trailer's goal
	var gs := sim.summary_bytes()
	var recs := Sim.summary_records(gs)
	var goal_rec: PackedByteArray = recs[0] if recs.size() > 0 else PackedByteArray()
	if gs.size() != 11 * (recs.size() + 1) or recs.size() != 2 or goal_rec[0] != 1 or goal_rec[1] != 0 or goal_rec[2] != 7 \
			or goal_rec[3] != 10 or goal_rec[4] != 0xff or goal_rec[6] != 1 or recs[-1][0] != 4 or recs[-1][1] != 1:
		fail("game summary after a goal: %s" % gs.hex_encode())
	sim.summary_close_period()
	if Sim.summary_records(sim.summary_bytes()).size() != 3:
		fail("the period record should stay when a period is closed")
	# the final whistle, the three stars (two goals, two assists, one goal) and the end of the game
	sim = Sim.new()
	sim.set_teams(bos, det)
	sim.user1_team = 0
	sim.assign_users()
	run_until_play(sim, 1200)
	sim.period = 2
	sim.clock_seconds = 2
	sim.teams[0].goals = 2
	sim.teams[0].player_stats[7][Team.ST_GOALS] = 2
	sim.teams[0].player_stats[10][Team.ST_ASSISTS] = 2
	sim.teams[1].goals = 1
	sim.teams[1].player_stats[3][Team.ST_GOALS] = 1
	# (the game ends in period 4: the last home carrier, 9 when the clock runs out, is credited
	# with the game winner, 2 points more in the order of the stars)
	var star_lines := []
	for i in 16000:
		sim.step(8, 8, 0, 0)
		if sim.stars_running and sim.panel_text[1] != "" and not star_lines.has(sim.panel_text[1]):
			star_lines.append(sim.panel_text[1])
		if sim.match_over:
			break
	if not sim.match_over or str(sim.stars) != "[[0, 7], [0, 9], [0, 10]]" or star_lines != ["3rd Star", "2nd Star", "1st Star"]:
		fail("three stars: over %s stars %s shown %s" % [sim.match_over, str(sim.stars), str(star_lines)])
	else:
		print("three stars: ", str(sim.stars))
	# a regular season game tied after the overtime ends tied; in the playoffs the overtime goes on
	sim = Sim.new()
	sim.set_teams(bos, det)
	run_until_play(sim, 1200)
	sim.period = 3
	sim.clock_seconds = 1
	for i in 600:
		sim.step(8, 8, 0, 0)
		if sim.game_over:
			break
	if not sim.game_over or sim.teams[0].goals != sim.teams[1].goals:
		fail("a regular season game should end tied after the overtime")
	sim = Sim.new()
	sim.set_teams(bos, det)
	sim.settings2 &= ~2
	run_until_play(sim, 1200)
	sim.period = 2
	sim.clock_seconds = 1
	var switched := sim.ends_switched
	for i in 1200:
		sim.step(8, 8, 0, 0)
		if sim.period == 3:
			break
	if sim.period != 3 or sim.game_over or sim.ends_switched == switched:
		fail("playoff overtime: period %d over %s" % [sim.period, sim.game_over])
	# a cup final: the captain fetches the Stanley Cup
	sim = Sim.new()
	sim.set_teams(bos, det)
	# the final series (game_over_check): the home team won the first three games, a win now
	# decides it
	var po := PackedByteArray()
	for g in 7:
		po.append_array(PackedByteArray([0, 0, 1, 2, 3 if g < 3 else 0xff, 1 if g < 3 else 0xff]))
	sim.cup_series = po
	sim.user1_team = 0
	sim.assign_users()
	run_until_play(sim, 1200)
	sim.period = 2
	sim.clock_seconds = 1
	sim.teams[0].goals = 1
	var got_cup := false
	for i in 4000:
		sim.step(8, 8, 0, 0)
		for k in 6:
			if sim.entities[k].state() == Entity.State.STANLEY_CUP:
				got_cup = true
		if got_cup:
			break
	if not got_cup:
		fail("the Stanley Cup was not handed over (shadow %s)" % Tables.ai_state_names[sim.shadow.state() + 1])

func _dressed(sim: Sim, t: int) -> Array:
	var out := []
	for i in 6:
		var e := sim.entities[t * 6 + i]
		if e.line_slot >= 0:
			out.append(e.roster_idx)
	out.sort()
	return out

## the instant replay: a frame every second step into the 300 frame ring, the newest frame
## matches the simulation, seeking stops at both ends, sounds come back when playing forward
func replay_tests(bos: Database.TeamInfo, det: Database.TeamInfo) -> void:
	var sim := Sim.new()
	sim.set_teams(bos, det)
	run_until_play(sim, 2400)
	var r := sim.replay
	# (the ring filled up during the line change prompt of the opening faceoff)
	r.reset()
	var before := r.frame_count()
	for i in 40:
		sim.step(8, 8, 0, 0)
	if sim.play_stopped:
		print("replay test: the play stopped early")
	var grown := r.frame_count() - before
	if grown < 15 or grown > 21:
		fail("replay: %d frames for 40 steps" % grown)
	if r.half != 0:
		sim.step(8, 8, 0, 0)      # the frame is written on every second step
	var f := r.decode(r.buffer_start())
	for i in 17:
		var e: Entity = sim.entities[i]
		var g: ReplayFrame.Sprite = f.entities[i]
		if g.xi != e.xi or g.yi != e.yi or g.frame != (e.frame if e.frame >= 0 else -1):
			fail("replay frame of entity %d: %d,%d frame %d, sim %d,%d frame %d" % [i, g.xi, g.yi, g.frame, e.xi, e.yi, e.frame])
			break
	if f.camera_y != sim.camera_y or f.user1_slot != sim.user1_slot or f.entities[3].number != sim.entities[3].number:
		fail("replay frame header: camera %d user %d" % [f.camera_y, f.user1_slot])
	# a sound effect is recorded and played again when the replay runs forward
	sim.play_sfx(0x9c)
	sim.step(8, 8, 0, 0)
	sim.step(8, 8, 0, 0)
	r.begin_playback()
	sim.sfx_queue.clear()
	var n := 0
	while r.seek(1, true, sim) != -1 and n < 400:
		n += 1
	if not sim.sfx_queue.has(0x9c):
		fail("replay: the goal horn was not replayed (%s)" % str(sim.sfx_queue))
	if r.seek(-1000, false, sim) != -1 or r.read != 0:
		fail("replay: seeking back stops at the oldest frame (%d)" % r.read)
	# VCR: play advances 0.3 frames per tick, rewind four times as fast
	r.press(Replay.B_PLAY, 10)
	if r.advance(10) != 3:
		fail("replay speed")
	# the ring wraps after 300 frames
	for i in 700:
		sim.step(8, 8, 0, 0)
	if not r.wrapped and sim.play_stopped == false:
		fail("replay: the ring did not wrap")
	if r.wrapped and r.frame_count() != Replay.FRAMES:
		fail("replay: %d frames in a full ring" % r.frame_count())
	print("replay: %d frames, wrapped %s" % [r.frame_count(), r.wrapped])

## the crowd figures: idle at the start, distinct spots, sequences of F000_149 frames, the bench
## cheers a goal
func crowd_tests(bos: Database.TeamInfo, det: Database.TeamInfo) -> void:
	var sim := Sim.new()
	sim.set_teams(bos, det)
	for r: Crowd.Record in sim.crowd:
		if r.id != -1 or r.timer < 60 or r.timer > 99:
			fail("crowd record at the start: id %d timer %d" % [r.id, r.timer])
			break
	for i in 300:
		sim.step(8, 8, 0, 0)
	var seen := {}
	var active := 0
	for i in 18:
		var r: Crowd.Record = sim.crowd[i]
		if r.id < 0:
			continue
		active += 1
		if seen.has(r.id):
			fail("crowd spot %d used twice" % r.id)
		seen[r.id] = true
		if r.frame != Crowd.frame_of(r.id, r.counter) or r.frame < 0 or r.frame > 104:
			fail("crowd frame %d of spot %d counter %d" % [r.frame, r.id, r.counter])
	if active < 5:
		fail("only %d crowd figures after 300 steps" % active)
	Crowd.bench_cheer(sim, 1)
	var bench: Crowd.Record = sim.crowd[Crowd.AWAY_BENCH]
	if bench.id != 0x88 or bench.y != Tables.bench_y[1]:
		fail("away bench cheer: spot %d at y %d" % [bench.id, bench.y])
	print("crowd: %d figures after 300 steps" % active)

## the announcer: XBRUCE2.VIV clips (4 bit delta coded and byte pair packed, both 11025 Hz) and the sentences
func speech_tests(bos: Database.TeamInfo, det: Database.TeamInfo, gf: Node) -> void:
	var viv := Viv.parse(gf.read_raw("xbruce2.viv"))
	if viv == null or viv.count != 344 or viv.entries.size() != 336:
		fail("XBRUCE2.VIV index")
		return
	var raw := viv.samples("goalnum.cor")
	var packed := viv.samples("la.rnk")
	if raw.is_empty() or raw[1] != 11025 or raw[0].size() != 16384:
		fail("delta coded speech clip")
	else:
		# decoded, the clip never wraps the accumulator (as 8 bit PCM it would be noise)
		var lo := 0
		var hi := 0
		for b in raw[0]:
			var v: int = b - 256 if b >= 128 else b
			lo = mini(lo, v)
			hi = maxi(hi, v)
		if lo < -120 or hi > 120:
			fail("delta coded speech clip range %d..%d" % [lo, hi])
	if packed.is_empty() or packed[1] != 11025 or packed[0].size() != 23768 or packed[0][11] != 0xff:
		fail("packed speech clip: %s" % str(packed[0].size() if not packed.is_empty() else -1))
	# every clip a sentence can name exists in the bank
	var sentences := [
		Speech.goal("BOS", 12, [77, 8]),
		Speech.penalty("DET", 19, 2, Rules.INF_HOOKING, 12, 5, true, 1, true),
		Speech.penalty("DET", 5, -1, Rules.INF_ABUSE_OF_OFFICIAL, 0, 30, false, 2, true),
		Speech.penalty_shot("BOS", 12, 1, 0),
		Speech.star(1, "BOS", 77),
		Speech.one_minute(),
		Speech.game_intro("BOS", "DET"),
	]
	for snt: PackedStringArray in sentences:
		for c in snt:
			if not viv.has(c):
				fail("speech clip %s is not in the bank" % c)
	for t in 28:
		var a: String = Tables.team_abbrev[t]
		if not viv.has(a + ".tea") or not viv.has(a + ".frm"):
			fail("team clips of " + a)
	for idx in Speech.PENALTY_CLIPS.size():
		var n: String = Speech.PENALTY_CLIPS[idx]
		if n != "" and n != "penshot" and not viv.has(n + ".pen"):
			fail("penalty clip " + n)
	if str(Speech.time(0, 1)) != str(PackedStringArray(["at.cor", "pause.cor", "1second.cor"])) \
			or str(Speech.time(12, 5)) != str(PackedStringArray(["at.cor", "pause.cor", "12.num", "05.num"])):
		fail("time of the period: %s / %s" % [Speech.time(0, 1), Speech.time(12, 5)])
	# a goal is announced once the panel is up
	var sim := Sim.new()
	sim.set_teams(bos, det)
	run_until_play(sim, 1200)
	sim.announcer_queue.clear()
	InfoPanel.announce_goal(sim, 0, 3, 10, -1)
	sim.play_stopped = true
	sim.panel = 0xf0
	sim.referee.set_state(Entity.State.REF_PICKUP)
	AI.ref_pickup(sim, sim.referee)
	if sim.announcer_queue.size() != 1 or sim.announcer_queue[0][0] != "bos.tea" or not sim.goal_call.is_empty():
		fail("goal sentence: %s" % str(sim.announcer_queue))
	else:
		print("speech: ", " ".join(sim.announcer_queue[0]))

## the music: the patch bank, the KMS songs, the sequencer, the FM driver and chip, the cues
func audio_tests(gf: Node, snd: Sounds) -> void:
	# the menu recordings: packed 8SVX bodies, two samples per byte (fibdelta_decode)
	var pause := Sounds.load_sample(gf.read_raw("pause.iff"))
	if pause == null or pause.data.size() != 70656 or pause.mix_rate != 22050 or pause.loop_mode != AudioStreamWAV.LOOP_DISABLED:
		fail("PAUSE.IFF: %s" % str([pause.data.size(), pause.mix_rate] if pause != null else null))
	elif Array(pause.data.slice(30000, 30006)) != [47, 39, 44, 42, 21, 0]:
		fail("PAUSE.IFF samples: %s" % str(Array(pause.data.slice(30000, 30006))))
	var desk := Sounds.load_sample(gf.read_raw("maindesk.iff"))
	if desk == null or desk.data.size() != 624640 or desk.loop_mode != AudioStreamWAV.LOOP_FORWARD or desk.loop_begin != 24960 or desk.loop_end != 624639:
		fail("MAINDESK.IFF loop")
	elif Array(desk.data.slice(30000, 30006)) != [8, 251, 253, 245, 232, 240]:
		fail("MAINDESK.IFF samples")
	var bank := FmBank.load_bank(gf.read_raw("pcff001.pat"), [gf.read_raw("pcff000.tim")])
	if bank == null or bank.timbres.size() != 144:
		fail("FM timbres: %d" % (bank.timbres.size() if bank != null else -1))
		return
	var organ := bank.record(0x0b)
	if organ.is_empty() or organ[0] != 0 or organ[1] != 0x65 or organ[7] != 0xf4 or bank.timbre(0x65).size() != 80:
		fail("program 0x0b patch")
	if not bank.record(0x90).is_empty() or bank.record(0xab)[0] != 0 or bank.record(0x9c)[0] != 1:
		fail("effect patch types")
	# the driver's frequencies: note 60 = F-number 86 in block 5
	if FmDriver.note_freq(60, 0) != (86 | 5 << 10) or FmDriver.note_freq(39, 0) != (102 | 3 << 10) or FmDriver.note_freq(60, 12) != (171 | 5 << 10):
		fail("note frequencies")
	# every song of the tables parses (CGY2 is listed but not on the disks)
	var missing := []
	for n in Tables.music_songs:
		var k := Kms.parse(gf.read_raw(n + ".kms"), gf.read_raw(n + ".cfg"), n)
		if k == null or k.tracks.is_empty():
			missing.append(n)
	if missing != ["CGY2"]:
		fail("songs: " + str(missing))
	var bos1 := Kms.parse(gf.read_raw("bos1.kms"), gf.read_raw("bos1.cfg"), "BOS1")
	if bos1.tempo != 96 or bos1.tracks.size() != 2 or bos1.tracks[0][4] != "left" or bos1.tracks[1][1] != 4 or absf(bos1.duration() - 18.26) > 0.01:
		fail("BOS1: %s %s" % [bos1.tempo, bos1.tracks])
	# the sequencer: program 0x0b on channel 1, the first note 27 + 24 on the organ with its
	# transpose of -12 (driver note 39: F-number 102 in block 3) and fine tune of -1
	var mp := MusicPlayer.new()
	mp.setup(bank, func(n: String) -> PackedByteArray: return gf.read_raw(n), snd.programs)
	if not mp.play_song("BOS1"):
		fail("BOS1 does not start")
	# the first step comes after 3 timer ticks (128 a tick towards 32000 / 96)
	var v0: FmDriver.Voice = null
	var ticks := 0
	while v0 == null and ticks < 6:
		mp.driver.tick()
		mp.seq.tick()
		ticks += 1
		for v: FmDriver.Voice in mp.driver.voices:
			if v.allocated and v.channel == 1:
				v0 = v
	if ticks != 3:
		fail("BOS1 starts after %d ticks" % ticks)
	if v0 == null or v0.note != 51 or v0.program != 0x0b or v0.base_note != 39 or v0.freq != FmDriver.note_freq(39, 0) - 1:
		fail("BOS1 first note: %s" % (str([v0.note, v0.program, v0.base_note, v0.freq]) if v0 != null else "none"))
	var s := mp.render(int(MusicPlayer.RATE * 2))
	var peak := 0.0
	var energy := 0.0
	for x in s:
		peak = maxf(peak, absf(x))
		energy += x * x
	var rms := sqrt(energy / s.size())
	if rms < 0.01 or peak >= 1.0:
		fail("BOS1 level: rms %.3f peak %.3f" % [rms, peak])
	# the drum kit: channel 9 note 36 plays patch 0x80, the FM kick (timbre 0x83, transpose -48)
	# whose envelope drives the note offset: it starts 48 semitones up and falls 3 a tick
	mp.stop_all()
	mp.driver.midi(0x99, 36, 0x7f)
	var kick: FmDriver.Voice = null
	for v: FmDriver.Voice in mp.driver.voices:
		if v.allocated and v.channel == 9:
			kick = v
	if kick == null or kick.program != 0x80 or kick.base_note != 12:
		fail("kick drum voice")
	else:
		mp.driver.tick()
		var n1 := kick.cur_note
		mp.driver.tick()
		if n1 != 60 or kick.cur_note != 57:
			fail("kick drum sweep %d %d" % [n1, kick.cur_note])
	mp.stop_all()
	# FM effects: the puck drop is an FM instrument (0xab, timbre 0x5c, 6 ticks)
	if not mp.has_effect(0xab) or mp.has_effect(0x9c) or mp.has_effect(0x90):
		fail("FM effect ids")
	mp.play_effect(0xab)
	mp.driver.tick()
	var drop := false
	for v: FmDriver.Voice in mp.driver.voices:
		if v.allocated and v.channel == 9 and v.program == 0xab:
			drop = v.key
	if not drop:
		fail("puck drop voice")
	for i in 7:
		mp.seq.tick()
		mp.driver.tick()
	for v: FmDriver.Voice in mp.driver.voices:
		if v.allocated and v.program == 0xab and v.key:
			fail("puck drop note did not end")
	# SBROCKU: the stomp is the digital sample of program 0x7c played by the DAC driver
	mp.stop_all()
	mp.play_song("SBROCKU")
	var s2 := mp.render(int(MusicPlayer.RATE * 3))
	var e2 := 0.0
	for x in s2:
		e2 += x * x
	if sqrt(e2 / s2.size()) < 0.01:
		fail("SBROCKU is silent")
	mp.free()
	# the cues of a Boston home game: the team's songs, three random ones, the US anthem
	var cues := MusicCues.new(func(n: String) -> bool: return gf.has(n + ".kms"))
	cues.setup(0)
	if cues.team_songs != ["BOS2", "BOS1", "BOS3", "", "PITTS2", "BOS2"] or cues.song_for(1) != "BOS1" or cues.song_for(10) != "USA" \
			or cues.song_for(9) != "SBROCKU" or cues.song_for(11) != "ROCKDITI":
		fail("Boston cues " + str(cues.team_songs))
	var pool_names := []
	for i in Tables.music_pool:
		pool_names.append(Tables.music_songs[i])
	for k in 3:
		var r: String = cues.random_songs[k]
		if not pool_names.has(r) or cues.team_songs.has(r) or cues.random_songs.count(r) != 1:
			fail("random song " + r)
	if not cues.random_songs.has(cues.song_for(3)):
		fail("cue 3 of Boston is a random song")
	cues.setup(9)
	if cues.anthem != "CANADA" or cues.song_for(5) != "MON1":
		fail("Montreal cues")
	# the simulation's cues: the power play (team +0x36 skaters), the puck drop stops the song,
	# a home goal without the announcer plays cue 3
	var sim := Sim.new()
	sim.teams[0].skaters_on_ice = 6
	sim.teams[1].skaters_on_ice = 5
	Rules.update_power_play(sim)
	Rules.update_power_play(sim)
	if not sim.power_play or sim.power_play_team != 0 or sim.teams[0].power_plays != 1 or sim.teams[1].power_plays != 0:
		fail("power play")
	sim.teams[1].skaters_on_ice = 6
	Rules.update_power_play(sim)
	if sim.power_play:
		fail("power play over")
	sim.music_queue.clear()
	Rules.faceoff_resolve(sim)
	if sim.music_queue != [-1]:
		fail("puck drop music " + str(sim.music_queue))
