extends Node2D
## Match scene: steps the simulation at 60 Hz and draws the rink, the entities and the scoreboard
## like game_loop / draw_sprites / draw_clock of HOCKEY.EXE. The screen is 320x200: the ice view
## (320x168, a window onto the 384x592 rink surface) on top and the 32 pixel scoreboard below.
## With the original game files (GameFiles.game_dir) the real rink, sprites, team colours, HUD
## shapes and sound effects are used, otherwise coloured placeholders.
##
## The match starts with the national anthem (a button skips it) and ends with the three stars and
## the pause screen of the finished game. In-game keys of handle_hotkey: Esc the pause screen
## (pause_menu), R the instant replay (instant_replay), Tab the jersey numbers of every player
## (show_names), S the sound effects, M the music, F1-F8 the lines, F9 / F10 the goalies.
##
## Environment variables for the headless tooling: NHL_HOME / NHL_AWAY (team indices 0..27,
## default Boston against Detroit), NHL_USER1 / NHL_USER2 (the team each user controls: 0 none,
## 1 home, 2 away; default user 1 home, no user 2), NHL_SCREENSHOT=path (save the view after NHL_SCREENSHOT_STEPS
## simulation steps and quit; NHL_SCREENSHOT_MODE=replay / pause shows the instant replay or the
## pause screen first), NHL_FAST_STEPS (simulation steps to run before the first frame),
## NHL_ANTHEM=0/1 (the anthem before the game; off for screenshots unless set).

const VIEW_W := 320
const VIEW_H := 168
const RINK_W := 384
const RINK_H := 592
const WORLD_X := 192          # draw_sprite_world: screen x = world x + 0xc0
const WORLD_Y := 320          # screen y = 0x140 - world y

var sim := Sim.new()
var controls := Controls.new()
var world: Node2D
var rink: Sprite2D
var sprites: Array[Sprite2D] = []
var markers: Array[Sprite2D] = []     # user 1, user 2, puck carrier (draw_sprites)
var overlay: Node2D                   # player numbers (draw_player_number)
var hud: Hud
var placeholders: Array[Polygon2D] = []

var palette: GamePalette
var frames: Dictionary = {}           # frame id -> Shpi.Shape (sprite_frames of load_sprite_banks)
var tex_cache: Dictionary = {}        # "frame|team|mirror" -> ImageTexture
var digit_shapes: Array = []          # NUMSHP "0000".."0009"
var letter_shapes: Dictionary = {}    # line slot -> NUMSHP position letter
var assets_ok := false

var sounds: Sounds
var sfx_players: Array[AudioStreamPlayer] = []
var crowd_player: AudioStreamPlayer
var sfx_on := true                    # option_flags 0x80 (S)
var music_on := true                  # option_flags 0x40 (M)
var show_names := false               # show_names (Tab)

enum Mode { MATCH, REPLAY, PAUSED }
var mode := Mode.MATCH
var panel_view: PanelView
var vcr: VcrView
var pause_menu: PauseMenu
var box_sprites: Array[Sprite2D] = []   # the players sitting in the penalty boxes (frame 0x17e)
var end_boards: Sprite2D              # TRINKND.PPV over the sprites near the bottom end (sub_11136)
var effect_frames: Dictionary = {}    # F000_149.PPV "0000".."0104" (load_effect_frames)
var crowd_sprites: Array[Sprite2D] = []  # draw_nets_and_effects: 18 figures, per bench base / figure / overlay
var tick_acc := 0.0                   # 100 Hz timer ticks of the replay speed
var replay_from_menu := false
var end_shown := false
var anthem := true

var home_team := 0
var away_team := 4
var user1_team := 1                   # user1_team / user2_team: 0 none, 1 home, 2 away
var user2_team := 0
var shot_path := ""
var shot_steps := 900
var steps_done := 0
var shot_taken := false

func _ready() -> void:
	_read_settings()
	world = Node2D.new()
	add_child(world)
	rink = Sprite2D.new()
	rink.centered = false
	rink.z_index = -1000
	world.add_child(rink)
	_load_assets()
	if rink.texture == null:
		rink.texture = _placeholder_rink()
	for i in 3:
		var m := Sprite2D.new()
		m.centered = false
		m.visible = false
		world.add_child(m)
		markers.append(m)
	for e in sim.entities:
		var s := Sprite2D.new()
		s.centered = false
		world.add_child(s)
		sprites.append(s)
		var p := _placeholder_node(e)
		world.add_child(p)
		placeholders.append(p)
	overlay = Node2D.new()
	overlay.z_index = 50
	overlay.draw.connect(_draw_numbers)
	world.add_child(overlay)
	for i in 6:
		var b := Sprite2D.new()
		b.centered = false
		b.visible = false
		world.add_child(b)
		box_sprites.append(b)
	for i in 18 + 6:
		var c := Sprite2D.new()
		c.centered = false
		c.visible = false
		c.z_index = -600 + i
		world.add_child(c)
		crowd_sprites.append(c)
	var fx_bank := _bank("f000_149")
	if fx_bank != null:
		for sh in fx_bank.shapes:
			if sh.is_image() and sh.name.strip_edges().is_valid_int():
				effect_frames[int(sh.name)] = sh
	end_boards = Sprite2D.new()
	end_boards.centered = false
	end_boards.visible = false
	end_boards.z_index = 4000
	world.add_child(end_boards)
	var trinknd := _bank("trinknd")
	if trinknd != null and palette != null:
		var shape := trinknd.find("0000")
		if shape != null and shape.is_image():
			end_boards.texture = shape.to_texture(palette.colors)
			end_boards.position = Vector2(0x37 - shape.center_x, 0x225 - shape.center_y)
	var fonts := _fonts()
	# the scoreboard, the info panel and the replay panel are drawn over the sprites
	var ui := CanvasLayer.new()
	ui.layer = 5
	add_child(ui)
	hud = Hud.new()
	ui.add_child(hud)
	hud.setup(sim, palette, _bank("scrbrd1"), fonts, _bank("scrbrd2"), _bank("crests4"))
	panel_view = PanelView.new()
	ui.add_child(panel_view)
	panel_view.setup(sim, palette, fonts, _bank)
	hud.panel_view = panel_view
	vcr = VcrView.new()
	ui.add_child(vcr)
	vcr.setup(sim.replay, _bank("gadget5"), palette)
	var layer := CanvasLayer.new()
	layer.layer = 10
	add_child(layer)
	pause_menu = PauseMenu.new()
	layer.add_child(pause_menu)
	pause_menu.setup(sim, fonts.get("s1", null), _bank)
	pause_menu.chosen.connect(_on_menu)
	if anthem:
		Ceremonies.begin_anthem(sim)
	var fast := int(OS.get_environment("NHL_FAST_STEPS"))
	for i in fast:
		sim.step(8, 8, 0, 0)
	sim.sfx_queue.clear()

func _read_settings() -> void:
	var cfg := ConfigFile.new()
	if cfg.load(GameFiles.SETTINGS_PATH) == OK:
		home_team = cfg.get_value("match", "home", home_team)
		away_team = cfg.get_value("match", "away", away_team)
		user1_team = cfg.get_value("match", "user1", user1_team)
		user2_team = cfg.get_value("match", "user2", user2_team)
	if OS.has_environment("NHL_HOME"):
		home_team = int(OS.get_environment("NHL_HOME"))
	if OS.has_environment("NHL_AWAY"):
		away_team = int(OS.get_environment("NHL_AWAY"))
	if OS.has_environment("NHL_USER1"):
		user1_team = clampi(int(OS.get_environment("NHL_USER1")), 0, 2)
	if OS.has_environment("NHL_USER2"):
		user2_team = clampi(int(OS.get_environment("NHL_USER2")), 0, 2)
	sim.user1_team = user1_team
	sim.user2_team = user2_team
	sim.assign_users()
	shot_path = OS.get_environment("NHL_SCREENSHOT")
	if OS.has_environment("NHL_SCREENSHOT_STEPS"):
		shot_steps = int(OS.get_environment("NHL_SCREENSHOT_STEPS"))
	anthem = shot_path == ""
	if OS.has_environment("NHL_ANTHEM"):
		anthem = OS.get_environment("NHL_ANTHEM") == "1"

func _physics_process(delta: float) -> void:
	tick_acc += delta * 100.0
	var ticks := int(tick_acc)
	tick_acc -= ticks
	match mode:
		Mode.PAUSED:
			_pause_input()
			return
		Mode.REPLAY:
			_replay_step(ticks)
			return
	if Input.is_action_just_pressed("pause") and not sim.match_over:
		_open_pause(false)
		return
	if Input.is_action_just_pressed("replay") and not sim.intro and not sim.stars_running and sim.replay.frame_count() > 0:
		_start_replay(false)
		return
	_hotkeys()
	var c := controls.step()
	sim.step(c[0], c[1], c[2], c[3])
	steps_done += 1
	_play_queued_sfx()
	_update_view()
	if sim.match_over and not end_shown and shot_path == "":
		# three_stars_sequence is over: the pause screen of the finished game (pause_menu(2))
		end_shown = true
		_open_pause(true)
	if shot_path != "" and steps_done >= shot_steps and not shot_taken:
		shot_taken = true
		match OS.get_environment("NHL_SCREENSHOT_MODE"):
			"replay":
				# the replay, 3 seconds after the oldest frame, following the puck carrier
				_start_replay(false)
				sim.replay.press(Replay.B_PLAY, 1)
				sim.replay.seek(90, false, sim)
				sim.replay.follow = maxi(sim.replay.frame.puck_carrier, -1) if sim.replay.frame.puck_carrier < 12 else -1
				_update_view()
			"pause":
				_open_pause(false)
				pause_menu.open_menu = 1
				pause_menu.queue_redraw()
		_screenshot()

# --------------------------------------------------------------------------------------------
# pause screen (pause_menu) and instant replay (instant_replay)
# --------------------------------------------------------------------------------------------

func _open_pause(after_game: bool) -> void:
	mode = Mode.PAUSED
	pause_menu.open(after_game)
	_stop_sounds()

func _pause_input() -> void:
	var dir := -1
	if Input.is_action_just_pressed("p1_up"):
		dir = 0
	elif Input.is_action_just_pressed("p1_down"):
		dir = 4
	elif Input.is_action_just_pressed("p1_left"):
		dir = 6
	elif Input.is_action_just_pressed("p1_right"):
		dir = 2
	var select := Input.is_action_just_pressed("p1_a") or Input.is_action_just_pressed("ui_accept")
	var back := Input.is_action_just_pressed("pause") or Input.is_action_just_pressed("p1_b")
	if dir >= 0 or select or back:
		pause_menu.input(dir, select, back)

func _on_menu(action: String) -> void:
	match action:
		"back":
			pause_menu.close()
			mode = Mode.MATCH
		"exit":
			get_tree().quit()
		"replay":
			pause_menu.close()
			_start_replay(true)

func _start_replay(from_menu: bool) -> void:
	replay_from_menu = from_menu
	mode = Mode.REPLAY
	_stop_sounds()
	sim.replay.begin_playback()
	vcr.selected = Replay.B_PLAY
	vcr.visible = true
	hud.visible = false
	panel_view.visible = false
	_update_view()

func _end_replay() -> void:
	vcr.visible = false
	hud.visible = true
	panel_view.visible = true
	sim.last_sfx = -1
	sim.replay.held_sfx = -1
	_stop_sounds()
	if replay_from_menu and not end_shown:
		mode = Mode.PAUSED
		pause_menu.visible = true
	elif end_shown:
		mode = Mode.PAUSED
		pause_menu.visible = true
	else:
		mode = Mode.MATCH
	_update_view()

## replay_control_loop: a held button (mouse on the panel, or the keyboard selection with A)
## repeats every frame; a click on the ice picks the camera
func _replay_step(ticks: int) -> void:
	var r := sim.replay
	var button := -1
	if Input.is_action_just_pressed("p1_left"):
		vcr.selected = Replay.BUTTONS[vcr.selected][4]
	elif Input.is_action_just_pressed("p1_right"):
		vcr.selected = Replay.BUTTONS[vcr.selected][5]
	if Input.is_action_pressed("p1_a") or Input.is_action_pressed("ui_accept"):
		button = vcr.selected
	if Input.is_mouse_button_pressed(MOUSE_BUTTON_LEFT):
		var m := get_viewport().get_mouse_position()
		if m.y >= VcrView.Y:
			var b := VcrView.button_at(int(m.x), int(m.y))
			if b >= 0:
				button = b
				vcr.selected = b
	if Input.is_action_just_pressed("pause") or Input.is_action_just_pressed("replay"):
		button = Replay.B_EXIT
	if button == Replay.B_MENU:
		button = -1          # replay_menu (save a highlight) belongs to the front end
	var speed: Variant = r.press(button, ticks)
	if speed == null:
		_end_replay()
		return
	var n := r.advance(int(speed))
	r.seek(n, (r.mode & 0x3f) == Replay.MODE_PLAY, sim)
	_play_queued_sfx()
	_update_view()

func _unhandled_input(event: InputEvent) -> void:
	if event is InputEventMouseButton and event.pressed and event.button_index == MOUSE_BUTTON_LEFT:
		var pos: Vector2 = get_viewport().get_mouse_position()
		if mode == Mode.PAUSED:
			pause_menu.click(pos)
		elif mode == Mode.REPLAY and pos.y < VcrView.Y:
			# the rink: follow the sprite there or look at the spot
			var origin := _view_origin()
			sim.replay.click(int(pos.x) + origin.x - WORLD_X, WORLD_Y - (int(pos.y) + origin.y))

func _stop_sounds() -> void:
	for p in sfx_players:
		p.stop()
	sim.sfx_queue.clear()

## handle_hotkey: F1-F4 lines of player 1, F5-F8 lines of player 2, F9 / F10 pull the goalie,
## Tab the numbers of every player, S the sound effects, M the music (the crowd loop)
func _hotkeys() -> void:
	if Input.is_action_just_pressed("toggle_names"):
		show_names = not show_names
	if Input.is_action_just_pressed("toggle_sfx"):
		sfx_on = not sfx_on
		if not sfx_on:
			_stop_sounds()
	if Input.is_action_just_pressed("toggle_music"):
		music_on = not music_on
		if crowd_player != null:
			crowd_player.stream_paused = not music_on
	for p in 2:
		var team := (sim.user1_team if p == 0 else sim.user2_team) - 1
		if team < 0:
			continue
		for k in 4:
			if Input.is_action_just_pressed("p%d_line%d" % [p + 1, k + 1]):
				sim.line_hotkey[team] = k
		if Input.is_action_just_pressed("p%d_pull_goalie" % (p + 1)):
			Lines.toggle_pull_goalie(sim, team)

func _screenshot() -> void:
	await RenderingServer.frame_post_draw
	var img := get_viewport().get_texture().get_image()
	var err := img.save_png(shot_path)
	print("screenshot %s: %s" % [shot_path, error_string(err)])
	get_tree().quit()

# --------------------------------------------------------------------------------------------
# sound
# --------------------------------------------------------------------------------------------

## play_sfx of the original queues sound ids; update_ambient_audio keeps the crowd loop running
func _play_queued_sfx() -> void:
	if sounds == null or not sfx_on:
		sim.sfx_queue.clear()
		return
	for id in sim.sfx_queue:
		var stream := sounds.stream(id)
		if stream == null:
			continue
		var p: AudioStreamPlayer = null
		for cand in sfx_players:
			if not cand.playing:
				p = cand
				break
		if p == null and sfx_players.size() < 8:
			p = AudioStreamPlayer.new()
			add_child(p)
			sfx_players.append(p)
		if p != null:
			p.stream = stream
			p.play()
	sim.sfx_queue.clear()
	if crowd_player != null:
		var crowd := sim.crowd_noise
		if mode == Mode.REPLAY and sim.replay.frame != null:
			crowd = sim.replay.frame.crowd
		crowd_player.volume_db = linear_to_db(clampf(0.15 + crowd / 4000.0, 0.0, 1.0))

# --------------------------------------------------------------------------------------------
# view
# --------------------------------------------------------------------------------------------

## the drawn scene: the simulation, or the frame of the replay
func _scene() -> Dictionary:
	if mode == Mode.REPLAY and sim.replay.frame != null:
		var f: ReplayFrame = sim.replay.frame
		return {"entities": f.entities, "u1": f.user1_slot, "u2": f.user2_slot, "carrier": f.puck_carrier,
			"blocked": false, "box": f.box_count, "follow": sim.replay.follow}
	return {"entities": sim.entities, "u1": sim.user1_slot, "u2": sim.user2_slot, "carrier": sim.puck_carrier,
		"blocked": sim.controls_blocked, "box": sim.box_count, "follow": -1}

func _view_origin() -> Vector2i:
	if mode == Mode.REPLAY and sim.replay.frame != null:
		var cam := sim.replay.camera()
		return Vector2i(clampi(cam.x + 0x20, 0, 0x40), clampi(0xec - cam.y, 0, 0x1a8))
	return sim.view_origin()

func _update_view() -> void:
	var scene := _scene()
	var ents: Array = scene["entities"]
	var carrier: int = scene["carrier"]
	var origin := _view_origin()
	world.position = Vector2(-origin.x, -origin.y)
	for i in ents.size():
		var e = ents[i]
		var visible: bool = e.on_ice() or e.slot == Entity.Slot.PUCK or e.slot == Entity.Slot.NET_TOP or e.slot == Entity.Slot.NET_BOTTOM
		var z: int = WORLD_Y - e.yi
		var force_mirror := false
		if e.slot == Entity.Slot.SHADOW:
			# draw_sprites: the shadow entity shows the puck's shadow (0x189) while the puck is up,
			# frames 0x22a..0x237 (over the end boards behind the bottom goal line), 0x284..0x288
			# mirrored on the left; draw_nets_and_effects draws the Stanley Cup (frames > 0x361)
			var f: int = e.frame
			var puck_e = ents[Entity.Slot.PUCK]
			visible = false
			if f >= 0x284 and f <= 0x288:
				visible = true
				force_mirror = e.xi < 0
			elif f == 0x189 and puck_e.zi >= 0 and carrier != Entity.Slot.REFEREE:
				visible = true
			elif f > 0x229 and f < 0x238:
				visible = true
				if e.yi < 0:
					z = 4100
			elif f > 0x361 and mode != Mode.REPLAY and sim.intermission_camera:
				visible = true
				z = -550
		if e.slot == Entity.Slot.PUCK:
			if e.zi < 0 or carrier == Entity.Slot.REFEREE:
				visible = false      # in the referee's hand
			elif carrier >= 0 or e.zi <= 0xc:
				z = -400             # under the players (drawn before them); in the air it is sorted in
			if carrier < 0 and e.yi < -0x108 and e.zi >= 0:
				z = 4100             # behind the bottom goal line: over the end boards
		var sx: int = e.xi + WORLD_X
		var sy: int = WORLD_Y - e.yi - (e.zi * 3) / 2
		var spr := sprites[i]
		var ph := placeholders[i]
		if assets_ok and e.frame >= 0 and frames.has(e.frame):
			var mirrored: bool = ((e.flags4 & Entity.F4_MIRROR) != 0 and e.slot < 12) or force_mirror
			var team := _remap_team(e.slot)
			var shape: Shpi.Shape = frames[e.frame]
			spr.texture = _texture(e.frame, team, mirrored)
			spr.flip_h = mirrored
			var cx := shape.width - 1 - shape.center_x if mirrored else shape.center_x
			spr.offset = Vector2(-cx, -shape.center_y)
			spr.position = Vector2(sx, sy)
			spr.z_index = z
			spr.visible = visible
			ph.visible = false
		else:
			spr.visible = false
			ph.position = Vector2(sx, sy)
			ph.z_index = WORLD_Y - e.yi
			ph.visible = visible and not (assets_ok and e.slot < 12)
	_update_box(scene["box"])
	_update_crowd()
	# draw_sprites: the near end boards cover the sprites when the camera is at the bottom end
	var cam_y := sim.camera_y
	if mode == Mode.REPLAY and sim.replay.frame != null:
		cam_y = sim.replay.camera().y
	end_boards.visible = end_boards.texture != null and cam_y < -0x90
	_update_markers(scene)
	overlay.queue_redraw()

## draw_nets_and_effects: the 18 figures at their spots (mirrored at the bottom end), then the
## away and the home bench: the base picture 0x60 under overlay frames (> 100) or when nobody
## stands up, the bench frame in the team colours, and frame 100 over the home bench
func _update_crowd() -> void:
	var ids: Array = []
	var counters: Array = []
	if mode == Mode.REPLAY and sim.replay.frame != null:
		ids = sim.replay.frame.effect_ids
		counters = sim.replay.frame.effect_frames
	else:
		for r: Crowd.Record in sim.crowd:
			ids.append(r.id)
			counters.append(r.counter)
	for c in crowd_sprites:
		c.visible = false
	if not assets_ok or effect_frames.is_empty() or ids.size() < 20:
		return
	for i in 18:
		var id: int = ids[i]
		if id < 0:
			continue
		var spot: Array = Tables.crowd_spots[id]
		_effect(crowd_sprites[i], Crowd.frame_of(id, counters[i]), spot[0], spot[1], spot[1] > 0xc0, -1)
	var k := 18
	for team in [1, 0]:
		var rec: int = 0x13 if team == 1 else 0x12
		var id: int = ids[rec]
		var f := -1 if id < 0 else Crowd.frame_of(id, counters[rec])
		if f > 100 or id < 0:
			_effect(crowd_sprites[k], 0x60, 4, Tables.bench_y[team], false, team)
		k += 1
		if f >= 0:
			var spot: Array = Tables.crowd_spots[id]
			_effect(crowd_sprites[k], f, spot[0], spot[1], false, team)
		k += 1
		if team == 0:
			_effect(crowd_sprites[k], 100, 4, Tables.bench_y[0], false, -1)
		k += 1

func _effect(spr: Sprite2D, frame: int, x: int, y: int, mirror: bool, team: int) -> void:
	if not effect_frames.has(frame):
		spr.visible = false
		return
	var shape: Shpi.Shape = effect_frames[frame]
	var key := "fx%d|%d|%d" % [frame, team, 1 if mirror else 0]
	if not tex_cache.has(key):
		tex_cache[key] = shape.to_texture(palette.colors, palette.table(team, mirror) if team >= 0 else PackedByteArray())
	spr.texture = tex_cache[key]
	spr.flip_h = mirror
	var cx := shape.width - 1 - shape.center_x if mirror else shape.center_x
	spr.offset = Vector2(-cx, -shape.center_y)
	spr.position = Vector2(x, y)
	spr.visible = true

## draw_sprites: the players sitting in the boxes, frame 0x17e at (0xb3, -(n + 3) * 0xb) for the
## home team and (0xb3, (n + 3) * 0xb) for the visitors, up to three each
func _update_box(counts: Array) -> void:
	for t in 2:
		for n in 3:
			var b := box_sprites[t * 3 + n]
			if not assets_ok or n >= counts[t] or not frames.has(0x17e):
				b.visible = false
				continue
			var shape: Shpi.Shape = frames[0x17e]
			var y := (n + 3) * 0xb * (1 if t == 1 else -1)
			b.texture = _texture(0x17e, t, false)
			b.offset = Vector2(-shape.center_x, -shape.center_y)
			b.position = Vector2(0xb3 + WORLD_X, WORLD_Y - y)
			b.z_index = WORLD_Y - y
			b.visible = true

## blit_sprite is called with the team of the entity (slot > 5 = away table), -1 for no remap
func _remap_team(slot: int) -> int:
	if slot < 6:
		return 0
	if slot < 12:
		return 1
	return -1

## draw_sprites: the frames under the controlled players (389 / 390) and the puck carrier (391);
## a controlled player outside the view gets an arrow at the edge instead (arrow_frames by the
## direction of sub_b340b, mirrored on the left side)
const ARROW_DIR := [0, 1, 5, 0, 3, 2, 4, 3, 7, 8, 6, 7, 0, 1, 5, 0]    # unk_d41b7: edge flags -> direction

func _update_markers(scene: Dictionary) -> void:
	var ents: Array = scene["entities"]
	var slots := [scene["u1"], scene["u2"], scene["carrier"]]
	var origin := _view_origin()
	for k in 3:
		var m := markers[k]
		var slot: int = slots[k]
		if not assets_ok or slot < 0 or slot >= 12 or (k < 2 and scene["blocked"]):
			m.visible = false
			continue
		var e = ents[slot]
		if e.frame < 0:
			m.visible = false
			continue
		var frame: int = Tables.marker_frames[k]
		var x: int = e.xi
		var y: int = e.yi
		var mirror := false
		if k < 2:
			var flags := 0
			if y < 0x140 - (origin.y + 0xa8):
				flags = 2
				y = 0x140 - (origin.y + 0xa8)
			elif y >= 0x140 - origin.y:
				flags = 1
				y = 0x141 - origin.y
			var right := origin.x + 0x80
			if flags == 0:
				if x >= right:
					x = right - 1
					flags = 4
				elif x < origin.x - 0xc0:
					x = origin.x - 0xc0
					flags = 8
			else:
				if x >= origin.x + 0x74:
					x = right - 0xd
					flags |= 4
				elif x < origin.x - 0xb4:
					x = origin.x - 0xb4
					flags |= 8
			if flags != 0:
				var dir: int = ARROW_DIR[flags & 0xf]
				frame = Tables.arrow_frames[k][dir - 1] if dir >= 1 and dir <= 8 else frame
				mirror = (flags & 8) != 0
		if not frames.has(frame):
			m.visible = false
			continue
		var shape: Shpi.Shape = frames[frame]
		m.texture = _texture(frame, 0, mirror)
		m.flip_h = mirror
		var cx := shape.width - 1 - shape.center_x if mirror else shape.center_x
		m.offset = Vector2(-cx, -shape.center_y)
		m.position = Vector2(x + WORLD_X, WORLD_Y - y)
		m.z_index = WORLD_Y - y - 1
		m.visible = true

## draw_player_number: the jersey number below the skates in the NUMSHP digits with the position
## letter for the controlled players and the carrier (in a replay also the followed player); the
## others only with show_names (Tab), without the letter
func _draw_numbers() -> void:
	if not assets_ok or digit_shapes.size() < 10:
		return
	var scene := _scene()
	var ents: Array = scene["entities"]
	for i in 12:
		var e = ents[i]
		if e.line_slot < 0 or e.frame < 0:
			continue
		var with_letter: bool = i == scene["u1"] or i == scene["u2"] or i == scene["carrier"] or i == scene["follow"]
		if not with_letter and not show_names:
			continue
		var x: int = e.xi + WORLD_X - (4 if with_letter else 0)
		var y: int = WORLD_Y - e.yi + (15 if with_letter else 13)
		var number: int = e.number
		if number >= 10:
			_draw_digit(digit_shapes[(number / 10) % 10], x - 3, y)
			x += 4
			number %= 10
		_draw_digit(digit_shapes[number], x, y)
		if with_letter and letter_shapes.has(e.line_slot):
			_draw_digit(letter_shapes[e.line_slot], x + 8, y)

func _draw_digit(tex: Texture2D, x: int, y: int) -> void:
	if tex != null:
		overlay.draw_texture(tex, Vector2(x - 4, y - 4))   # NUMSHP hotspots are (4, 4)

## sprite frame as texture, drawn through the remap table of the team (blit_sprite)
func _texture(frame: int, team: int, mirrored: bool) -> ImageTexture:
	var key := "%d|%d|%d" % [frame, team, 1 if mirrored else 0]
	if tex_cache.has(key):
		return tex_cache[key]
	var shape: Shpi.Shape = frames[frame]
	var remap := palette.table(team, mirrored)
	var tex := shape.to_texture(palette.colors, remap)
	tex_cache[key] = tex
	return tex

func _placeholder_node(e: Entity) -> Polygon2D:
	var p := Polygon2D.new()
	match e.slot:
		Entity.Slot.PUCK:
			p.polygon = PackedVector2Array([Vector2(-2, -1), Vector2(2, -1), Vector2(2, 1), Vector2(-2, 1)])
			p.color = Color.BLACK
		Entity.Slot.REFEREE:
			p.polygon = PackedVector2Array([Vector2(-3, -12), Vector2(3, -12), Vector2(3, 0), Vector2(-3, 0)])
			p.color = Color.WHITE
		Entity.Slot.NET_TOP, Entity.Slot.NET_BOTTOM:
			p.polygon = PackedVector2Array([Vector2(-20, -6), Vector2(20, -6), Vector2(20, 6), Vector2(-20, 6)])
			p.color = Color(0.85, 0.2, 0.2, 0.6)
		Entity.Slot.SHADOW:
			p.visible = false
		_:
			p.polygon = PackedVector2Array([Vector2(-4, -14), Vector2(4, -14), Vector2(4, 0), Vector2(-4, 0)])
			p.color = Color(0.9, 0.2, 0.2) if e.team == 0 else Color(0.2, 0.4, 0.9)
	p.visible = false
	return p

# --------------------------------------------------------------------------------------------
# assets
# --------------------------------------------------------------------------------------------

func _bank(name: String) -> Shpi:
	var data := GameFiles.read_bank(name)
	return Shpi.parse(data) if not data.is_empty() else null

func _fonts() -> Dictionary:
	var out := {}
	for n in ["scor2b", "scor3b", "hilight", "wittle06", "s1"]:
		var data := GameFiles.read(n + ".vfn")
		if not data.is_empty():
			out[n] = Vfn.parse(data)
	return out

func _load_assets() -> void:
	if not GameFiles.available():
		return
	# rosters, lines and ratings (sub_1c26c / sub_1c3f6)
	var db := Database.open(GameFiles.read_raw("teams.db"), GameFiles.read_raw("key.db"), GameFiles.read_raw("att.db"))
	if db != null:
		home_team = clampi(home_team, 0, db.team_count() - 1)
		away_team = clampi(away_team, 0, db.team_count() - 1)
		sim.set_teams(db.load_team(home_team), db.load_team(away_team))
	# palette with the jersey colours (load_team_palettes)
	palette = GamePalette.build(GameFiles.read_raw("rinkpal.qfs"), GameFiles.read_raw("homepals.bin"), GameFiles.read_raw("awaypals.bin"), mini(home_team, 25), mini(away_team, 25))
	if palette == null:
		return
	# rink surface with the centre ice logo (load_rink)
	var rink_bank := _bank("rink")
	if rink_bank != null:
		var shape := rink_bank.find("rink")
		if shape != null and shape.is_image():
			var logo := mini(home_team, Tables.rink_tile_names.size() - 1)
			var base := Tables.rink_tile_names[logo].strip_edges()
			var img := RinkTiles.compose(shape, GameFiles.read_raw(base + ".til"), GameFiles.read_raw(base + ".map"), logo, palette.colors)
			rink.texture = ImageTexture.create_from_image(img)
	# the 1134 sprite frames in 23 banks (load_sprite_banks)
	for i in 23:
		var bank := _bank(GameFiles.sprite_bank_name(i))
		if bank == null:
			continue
		for s in bank.shapes:
			if s.is_image() and s.name.strip_edges().is_valid_int():
				frames[int(s.name)] = s
	assets_ok = frames.size() > 1000
	# HUD digits and position letters (load_player_graphics)
	var numshp := _bank("numshp")
	if numshp != null:
		for d in 10:
			var s := numshp.find("%04d" % d)
			digit_shapes.append(s.to_texture(palette.colors, palette.table(0, false)) if s != null else null)
		var letters := ["000G", "000D", "000D", "000L", "000C", "000R", "000X"]
		for k in letters.size():
			var s := numshp.find(letters[k])
			if s != null:
				letter_shapes[k] = s.to_texture(palette.colors, palette.table(0, false))
	# sound effects (PCFF001.PAT / .TIM / .DIG)
	sounds = Sounds.load_bank(GameFiles.read_raw("pcff001.pat"), GameFiles.read_raw("pcff001.tim"), GameFiles.read_raw("pcff001.dig"))
	if sounds != null and sounds.has(Sounds.CROWD_LOOP):
		crowd_player = AudioStreamPlayer.new()
		crowd_player.stream = sounds.stream(Sounds.CROWD_LOOP)
		crowd_player.volume_db = linear_to_db(0.15)
		add_child(crowd_player)
		crowd_player.play()

func _placeholder_rink() -> Texture2D:
	var img := Image.create(RINK_W, RINK_H, false, Image.FORMAT_RGBA8)
	img.fill(Color(0.15, 0.2, 0.3))
	# ice 320x528 with rounded corners, blue lines at y = ±78, goal lines at ±232, centre line
	for yy in RINK_H:
		for xx in RINK_W:
			var wx := xx - WORLD_X
			var wy := WORLD_Y - yy
			var inside := absi(wx) <= 160 and absi(wy) <= 264
			if inside and absi(wx) > 96 and absi(wy) > 200:
				var dx := absi(wx) - 96
				var dy := absi(wy) - 200
				inside = dx * dx + dy * dy <= 64 * 64
			if inside:
				var c := Color(0.92, 0.95, 1.0)
				if absi(absi(wy) - 78) <= 2:
					c = Color(0.2, 0.3, 0.9)
				elif absi(wy) <= 1:
					c = Color(0.9, 0.2, 0.2)
				elif absi(absi(wy) - 232) <= 1 and absi(wx) < 150:
					c = Color(0.9, 0.2, 0.2)
				img.set_pixel(xx, yy, c)
	return ImageTexture.create_from_image(img)
