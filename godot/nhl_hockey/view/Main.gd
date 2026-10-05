extends Node2D
## Match scene: steps the simulation at 60 Hz and draws the rink, the entities and a minimal HUD.
## With the original game files available (GameFiles.game_dir) the real rink and player sprites
## are used, otherwise coloured placeholders.

const VIEW_W := 320
const VIEW_H := 168
const RINK_W := 384
const RINK_H := 592

var sim := Sim.new()
var controls := Controls.new()
var sprites: Array[Node2D] = []
var rink: Sprite2D
var hud: Label
var world: Node2D
var frame_textures: Dictionary = {}     # frame id -> ImageTexture
var frame_centers: Dictionary = {}      # frame id -> Vector2i hotspot
var palette: PackedColorArray
var assets_ok := false

func _ready() -> void:
	world = Node2D.new()
	add_child(world)
	rink = Sprite2D.new()
	rink.centered = false
	world.add_child(rink)
	_load_assets()
	if rink.texture == null:
		rink.texture = _placeholder_rink()
	for e in sim.entities:
		var n := _make_entity_node(e)
		world.add_child(n)
		sprites.append(n)
	hud = Label.new()
	hud.position = Vector2(4, VIEW_H + 4)
	hud.add_theme_font_size_override("font_size", 8)
	add_child(hud)
	sim.user1_slot = 1   # control the home centre
	sim.entities[1].flags |= Entity.F_USER

func _physics_process(_delta: float) -> void:
	if Input.is_action_just_pressed("pause"):
		get_tree().paused = not get_tree().paused
	var c := controls.step()
	sim.step(c[0], c[1], c[2], c[3])
	_update_view()

func _update_view() -> void:
	var origin := sim.view_origin()
	world.position = Vector2(-origin.x, -origin.y)
	for i in sim.entities.size():
		var e := sim.entities[i]
		var n := sprites[i]
		n.visible = e.on_ice() or e.slot == Entity.Slot.PUCK
		# draw_sprite_world: screen = (x + 192, 320 - y); the height lifts the sprite
		var sx := e.xi + 192
		var sy := 320 - e.yi - (e.zi * 3) / 2
		n.position = Vector2(sx, sy)
		n.z_index = 320 - e.yi
		if n is Sprite2D:
			var s := n as Sprite2D
			if frame_textures.has(e.frame):
				s.texture = frame_textures[e.frame]
				var c: Vector2i = frame_centers[e.frame]
				s.offset = Vector2(-c.x, -c.y)
				s.flip_h = (e.flags4 & Entity.F4_MIRROR) != 0
	var carrier := "-" if sim.puck_carrier < 0 else str(sim.puck_carrier)
	hud.text = "puck %d,%d  carrier %s  step %d%s" % [sim.puck.xi, sim.puck.yi, carrier, sim.step_count,
		"" if assets_ok else "  (no game files: set NHL_GAME_DIR)"]

func _make_entity_node(e: Entity) -> Node2D:
	if assets_ok and e.slot < 12 or e.slot == Entity.Slot.REFEREE:
		var s := Sprite2D.new()
		s.centered = false
		return s
	var p := Polygon2D.new()
	match e.slot:
		Entity.Slot.PUCK:
			p.polygon = PackedVector2Array([Vector2(-2, -1), Vector2(2, -1), Vector2(2, 1), Vector2(-2, 1)])
			p.color = Color.BLACK
		Entity.Slot.REFEREE:
			p.polygon = PackedVector2Array([Vector2(-3, -12), Vector2(3, -12), Vector2(3, 0), Vector2(-3, 0)])
			p.color = Color.WHITE
		_:
			p.polygon = PackedVector2Array([Vector2(-4, -14), Vector2(4, -14), Vector2(4, 0), Vector2(-4, 0)])
			p.color = Color(0.9, 0.2, 0.2) if e.team == 0 else Color(0.2, 0.4, 0.9)
			if e.slot >= 12:
				p.visible = false
	return p

# --------------------------------------------------------------------------------------------
# assets
# --------------------------------------------------------------------------------------------

func _load_assets() -> void:
	if not GameFiles.available():
		return
	# rink: the 'rink' bank holds the backdrop shape and the palette (load_rink)
	var rink_bank := Shpi.parse(GameFiles.read_bank("rink"))
	if rink_bank != null:
		palette = rink_bank.palette()
		var shape := rink_bank.find("rink")
		if shape != null and shape.is_image():
			rink.texture = shape.to_texture(palette)
	if palette.is_empty():
		return
	# player sprites: 23 banks of 50 frames (load_sprite_banks)
	for i in 23:
		var half := i / 2
		var name := ("%d00_%d49" if i % 2 == 0 else "%d50_%d99") % [half, half]
		var data := GameFiles.read_bank(name)
		if data.is_empty():
			continue
		var bank := Shpi.parse(data)
		if bank == null:
			continue
		for s in bank.shapes:
			if s.is_image() and s.name.strip_edges().is_valid_int():
				var fid := int(s.name)
				frame_textures[fid] = s.to_texture(palette)
				frame_centers[fid] = Vector2i(s.center_x, s.center_y)
	assets_ok = not frame_textures.is_empty()

func _placeholder_rink() -> Texture2D:
	var img := Image.create(RINK_W, RINK_H, false, Image.FORMAT_RGBA8)
	img.fill(Color(0.15, 0.2, 0.3))
	# ice 320x528 with rounded corners, blue lines at y = ±74, goal lines at ±232, centre line
	for yy in RINK_H:
		for xx in RINK_W:
			var wx := xx - 192
			var wy := 320 - yy
			var inside := absi(wx) <= 160 and absi(wy) <= 264
			if inside and absi(wx) > 96 and absi(wy) > 200:
				var dx := absi(wx) - 96
				var dy := absi(wy) - 200
				inside = dx * dx + dy * dy <= 64 * 64
			if inside:
				var c := Color(0.92, 0.95, 1.0)
				if absi(absi(wy) - 74) <= 2:
					c = Color(0.2, 0.3, 0.9)
				elif absi(wy) <= 1:
					c = Color(0.9, 0.2, 0.2)
				elif absi(absi(wy) - 232) <= 1 and absi(wx) < 150:
					c = Color(0.9, 0.2, 0.2)
				img.set_pixel(xx, yy, c)
	return ImageTexture.create_from_image(img)
