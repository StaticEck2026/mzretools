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
			break
		for i in 300:
			sim.step(8, 8, 0, 0)
			if sim.teams[0].goals > home_goals:
				scored = true
				break
		if scored:
			break
	if not scored:
		fail("no goal: puck %d,%d v %d,%d carrier %d stopped %s infractions %s" % [sim.puck.xi, sim.puck.yi, sim.puck.vx, sim.puck.vy, sim.puck_carrier, sim.play_stopped, str(sim.infractions)])
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

## line changes, fatigue and goalie pulling (Lines.gd)
func line_change_tests(bos: Database.TeamInfo, det: Database.TeamInfo) -> void:
	# the user asks for the second line with F2: the first line skates to the bench and Boston's
	# second forward line (Hughes 18, Smolinski 20, Murray 44) and second pair come on
	var sim := Sim.new()
	sim.set_teams(bos, det)
	run_until_play(sim, 1200)
	var before := _dressed(sim, 0)
	sim.line_hotkey[0] = 1
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
	# everybody who left is on the bench, nobody is dressed twice
	var home := sim.teams[0]
	for i in 6:
		var e := sim.entities[i]
		if e.line_slot >= 0 and home.entity_of[e.roster_idx] != -1:
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
	for inf: Array in sim.infractions:
		if inf[0] == Rules.INF_ABUSE_OF_OFFICIAL:
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
		for i in 1200:
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
	var star_lines := []
	for i in 16000:
		sim.step(8, 8, 0, 0)
		if sim.stars_running and sim.panel_text[1] != "" and not star_lines.has(sim.panel_text[1]):
			star_lines.append(sim.panel_text[1])
		if sim.match_over:
			break
	if not sim.match_over or str(sim.stars) != "[[0, 7], [0, 10], [1, 3]]" or star_lines != ["3rd Star", "2nd Star", "1st Star"]:
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
	sim.cup_final = true
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
	run_until_play(sim, 1200)
	var r := sim.replay
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
