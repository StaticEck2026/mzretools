extends Node2D
## Match scene: steps the simulation at 60 Hz and draws the rink, the entities and the scoreboard
## like game_loop / draw_sprites / draw_clock of HOCKEY.EXE. The screen is 320x200: the ice view
## (320x168, a window onto the 384x592 rink surface) on top and the 32 pixel scoreboard below.
## With the original game files (GameFiles.game_dir) the real rink, sprites, team colours, HUD
## shapes and sound effects are used, otherwise coloured placeholders.
##
## Environment variables for the headless tooling: NHL_HOME / NHL_AWAY (team indices 0..27,
## default Boston against Detroit), NHL_SCREENSHOT=path (save the view after NHL_SCREENSHOT_STEPS
## simulation steps and quit), NHL_FAST_STEPS (simulation steps to run before the first frame).

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

var home_team := 0
var away_team := 4
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
	hud = Hud.new()
	add_child(hud)
	hud.setup(sim, palette, _bank("scrbrd1"), _fonts())
	var fast := int(OS.get_environment("NHL_FAST_STEPS"))
	for i in fast:
		sim.step(8, 8, 0, 0)
	sim.sfx_queue.clear()

func _read_settings() -> void:
	var cfg := ConfigFile.new()
	if cfg.load(GameFiles.SETTINGS_PATH) == OK:
		home_team = cfg.get_value("match", "home", home_team)
		away_team = cfg.get_value("match", "away", away_team)
	if OS.has_environment("NHL_HOME"):
		home_team = int(OS.get_environment("NHL_HOME"))
	if OS.has_environment("NHL_AWAY"):
		away_team = int(OS.get_environment("NHL_AWAY"))
	shot_path = OS.get_environment("NHL_SCREENSHOT")
	if OS.has_environment("NHL_SCREENSHOT_STEPS"):
		shot_steps = int(OS.get_environment("NHL_SCREENSHOT_STEPS"))

func _physics_process(_delta: float) -> void:
	if Input.is_action_just_pressed("pause"):
		get_tree().paused = not get_tree().paused
	_hotkeys()
	var c := controls.step()
	sim.step(c[0], c[1], c[2], c[3])
	steps_done += 1
	_play_queued_sfx()
	_update_view()
	if shot_path != "" and steps_done >= shot_steps and not shot_taken:
		shot_taken = true
		_screenshot()

## handle_hotkey: F1-F4 lines of player 1, F5-F8 lines of player 2, F9 / F10 pull the goalie
func _hotkeys() -> void:
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
	if sounds == null:
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
		crowd_player.volume_db = linear_to_db(clampf(0.15 + sim.crowd_noise / 4000.0, 0.0, 1.0))

# --------------------------------------------------------------------------------------------
# view
# --------------------------------------------------------------------------------------------

func _update_view() -> void:
	var origin := sim.view_origin()
	world.position = Vector2(-origin.x, -origin.y)
	for i in sim.entities.size():
		var e := sim.entities[i]
		var visible := e.on_ice() or e.slot == Entity.Slot.PUCK or e.slot == Entity.Slot.NET_TOP or e.slot == Entity.Slot.NET_BOTTOM
		if e.slot == Entity.Slot.SHADOW:
			visible = false
		if e.slot == Entity.Slot.PUCK and (e.zi < 0 or sim.puck_carrier == Entity.Slot.REFEREE):
			visible = false      # in the referee's hand
		var sx := e.xi + WORLD_X
		var sy := WORLD_Y - e.yi - (e.zi * 3) / 2
		var spr := sprites[i]
		var ph := placeholders[i]
		if assets_ok and e.frame >= 0 and frames.has(e.frame):
			var mirrored := (e.flags4 & Entity.F4_MIRROR) != 0 and e.slot < 12
			var team := _remap_team(e)
			var shape: Shpi.Shape = frames[e.frame]
			spr.texture = _texture(e.frame, team, mirrored)
			spr.flip_h = mirrored
			var cx := shape.width - 1 - shape.center_x if mirrored else shape.center_x
			spr.offset = Vector2(-cx, -shape.center_y)
			spr.position = Vector2(sx, sy)
			spr.z_index = WORLD_Y - e.yi
			spr.visible = visible
			ph.visible = false
		else:
			spr.visible = false
			ph.position = Vector2(sx, sy)
			ph.z_index = WORLD_Y - e.yi
			ph.visible = visible and not (assets_ok and e.slot < 12)
	_update_markers()
	overlay.queue_redraw()

## blit_sprite is called with the team of the entity (slot > 5 = away table), -1 for no remap
func _remap_team(e: Entity) -> int:
	if e.slot < 6:
		return 0
	if e.slot < 12:
		return 1
	return -1

## draw_sprites: the frames under the controlled players and the puck carrier
func _update_markers() -> void:
	var slots := [sim.user1_slot, sim.user2_slot, sim.puck_carrier]
	for k in 3:
		var m := markers[k]
		var slot: int = slots[k]
		var frame: int = Tables.marker_frames[k] if Tables.marker_frames.size() > k else -1
		if not assets_ok or slot < 0 or slot >= 12 or sim.controls_blocked or not frames.has(frame):
			m.visible = false
			continue
		var e := sim.entities[slot]
		var shape: Shpi.Shape = frames[frame]
		m.texture = _texture(frame, 0, false)
		m.offset = Vector2(-shape.center_x, -shape.center_y)
		m.position = Vector2(e.xi + WORLD_X, WORLD_Y - e.yi)
		m.z_index = WORLD_Y - e.yi - 1
		m.visible = true

## draw_player_number: the jersey number below the skates in the NUMSHP digits, with the position
## letter for the controlled players and the carrier
func _draw_numbers() -> void:
	if not assets_ok or digit_shapes.size() < 10:
		return
	for i in 12:
		var e := sim.entities[i]
		if e.line_slot < 0 or e.frame < 0:
			continue
		var with_letter := i == sim.user1_slot or i == sim.user2_slot or i == sim.puck_carrier
		var x := e.xi + WORLD_X - (4 if with_letter else 0)
		var y := WORLD_Y - e.yi + (15 if with_letter else 13)
		var number := e.number
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
	for n in ["scor2b", "scor3b", "hilight", "wittle06"]:
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
