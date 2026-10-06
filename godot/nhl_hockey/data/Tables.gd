class_name Tables
## Static tables extracted from HOCKEY.EXE (tools/nhl/extract_tables.py -> data/tables.json).
## See re/nhl_hockey/STRUCTURES.md for what each table means. Everything is static and loaded on
## first use, so the tables work from any script (also headless --script runs without autoloads).

static var anim_sequences: PackedInt32Array      # u16 words, an animation id is a word offset into this
static var dir8_vectors: Array = []               # 8 x [dx, dy] * 200 (0 up, 1 up-right, 2 right ...)
static var frame_offsets: Array = []              # [dx, dy] per frame id (movement animations)
static var shot_targets: PackedInt32Array
static var position_default_state: PackedByteArray
static var dir8_lut: PackedByteArray
static var ai_state_names: PackedStringArray
static var team_abbrev: PackedStringArray
static var team_strings: PackedStringArray
static var message_strings: PackedStringArray
static var turn_table: PackedInt32Array           # heading change per step by (dir - facing) & 7
static var max_speed_sq: PackedInt32Array         # squared speed limit per energy level
static var infraction_priority: PackedInt32Array
static var infraction_is_penalty: PackedInt32Array
static var stoppage_duration: PackedInt32Array    # << 5 steps per infraction type
static var announce_delay: PackedInt32Array
static var entity_init: Array = []                # 17 x [x, y, vx, frame, side, half_w, half_h, state, flags]
static var faceoff_spots: Array = []              # 7 x [x, y] relative to the faceoff dot
static var faceoff_lineup: Array = []             # [6 - skaters_on_ice][line_slot] -> spot index
static var faceoff_bonus: PackedInt32Array
static var stick_offsets: Array = []              # [dx, dy] for frames 0x196..0x219
static var onetimer_offsets: Array = []           # [dx, dy] per facing
static var carrier_targets: Array = []            # 10 x [x, y]
static var wing_zones: Array = []                 # 4 x [x, dx, y, dy]
static var center_zones: Array = []
static var goalie_save_anims: PackedInt32Array
static var poke_vectors: Array = []               # 8 x [vx, vy]
static var breakaway_waypoints: Array = []        # 4 x [x, y, trigger]
static var ref_signal_dir: PackedInt32Array
static var ref_signal_anim: PackedInt32Array
static var loaded := false

static func _static_init() -> void:
	load_tables()

static func load_tables() -> void:
	var f := FileAccess.open("res://data/tables.json", FileAccess.READ)
	if f == null:
		push_error("data/tables.json missing, run tools/nhl/extract_tables.py")
		return
	var t: Dictionary = JSON.parse_string(f.get_as_text())
	anim_sequences = PackedInt32Array(t["anim_sequences"])
	dir8_vectors = _ints(t["dir8_vectors"])
	frame_offsets = _ints(t["frame_offsets"])
	shot_targets = PackedInt32Array(t["shot_targets"])
	position_default_state = PackedByteArray(t["position_default_state"])
	dir8_lut = PackedByteArray(t["dir8_lut"])
	ai_state_names = PackedStringArray(t["ai_state_names"])
	team_abbrev = PackedStringArray(t["team_abbrev"])
	team_strings = PackedStringArray(t["team_strings"])
	message_strings = PackedStringArray(t["message_strings"])
	turn_table = PackedInt32Array(t["turn_table"])
	max_speed_sq = PackedInt32Array(t["max_speed_sq"])
	infraction_priority = PackedInt32Array(t["infraction_priority"])
	infraction_is_penalty = PackedInt32Array(t["infraction_is_penalty"])
	stoppage_duration = PackedInt32Array(t["stoppage_duration"])
	announce_delay = PackedInt32Array(t["announce_delay"])
	entity_init = _ints(t["entity_init"])
	faceoff_spots = _ints(t["faceoff_spots"])
	faceoff_lineup = _ints(t["faceoff_lineup"])
	faceoff_bonus = PackedInt32Array(t["faceoff_bonus"])
	stick_offsets = _ints(t["stick_offsets"])
	onetimer_offsets = _ints(t["onetimer_offsets"])
	carrier_targets = _ints(t["carrier_targets"])
	wing_zones = _ints(t["wing_zones"])
	center_zones = _ints(t["center_zones"])
	goalie_save_anims = PackedInt32Array(t["goalie_save_anims"])
	poke_vectors = _ints(t["poke_vectors"])
	breakaway_waypoints = _ints(t["breakaway_waypoints"])
	ref_signal_dir = PackedInt32Array(t["ref_signal_dir"])
	ref_signal_anim = PackedInt32Array(t["ref_signal_anim"])
	loaded = true

## JSON numbers come back as floats: convert nested arrays of numbers to ints
static func _ints(a: Array) -> Array:
	var out := []
	for v in a:
		if v is Array:
			out.append(_ints(v))
		else:
			out.append(int(v))
	return out

## anim_sequences entries are unsigned 16 bit words stored as signed JSON numbers
static func anim_word(index: int) -> int:
	if index < 0 or index >= anim_sequences.size():
		return 0
	return anim_sequences[index] & 0xffff

## signed version of anim_word (durations are signed)
static func anim_sword(index: int) -> int:
	var v := anim_word(index)
	return v - 0x10000 if v >= 0x8000 else v

## frame_offsets_lookup (0x5f0ae): displacement of the stick/feet for a frame, mirrored for F4_MIRROR
static func frame_offset(frame: int, mirrored: bool) -> Vector2i:
	if frame < 0 or frame >= 0x468:
		return Vector2i.ZERO
	var f := frame
	if f >= 0x378:
		f -= 0xf4
	elif f > 0x283:
		return Vector2i.ZERO
	if f >= 0x2da:
		f -= 0x46
	elif f > 0x293:
		return Vector2i.ZERO
	if f >= frame_offsets.size():
		return Vector2i.ZERO
	var o: Array = frame_offsets[f]
	return Vector2i(-o[0] if mirrored else o[0], o[1])

## stick_offsets_lookup (0x5f110): stick blade position for the carrying/skating frames
static func stick_offset(frame: int, mirrored: bool) -> Vector2i:
	if frame < 0:
		return Vector2i.ZERO
	var f := frame
	if f > 0x3cd and f < 0x450:
		f -= 0x1b4
	if f <= 0x195 or f > 0x219:
		return Vector2i.ZERO
	var o: Array = stick_offsets[f - 0x196]
	return Vector2i(-o[0] if mirrored else o[0], o[1])

## direction8(dx, dy): 0-7 like the original (direction8 @0x8c8e8), 8 when both are zero
static func direction8(dx: int, dy: int) -> int:
	if dx == 0 and dy == 0:
		return 8
	var idx := 0
	if dx < 0:
		dx = -dx
		idx |= 1
	if dy < 0:
		dy = -dy
		idx |= 2
	if dx <= (dy << 1) & 0xffff:
		idx |= 4
	if dy <= (dx << 1) & 0xffff:
		idx |= 8
	return dir8_lut[idx]
