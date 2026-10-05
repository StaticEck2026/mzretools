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
	dir8_vectors = t["dir8_vectors"]
	frame_offsets = t["frame_offsets"]
	shot_targets = PackedInt32Array(t["shot_targets"])
	position_default_state = PackedByteArray(t["position_default_state"])
	dir8_lut = PackedByteArray(t["dir8_lut"])
	ai_state_names = PackedStringArray(t["ai_state_names"])
	team_abbrev = PackedStringArray(t["team_abbrev"])
	team_strings = PackedStringArray(t["team_strings"])
	message_strings = PackedStringArray(t["message_strings"])
	turn_table = PackedInt32Array(t["turn_table"])
	max_speed_sq = PackedInt32Array(t["max_speed_sq"])
	loaded = true

## anim_sequences entries are unsigned 16 bit words stored as signed JSON numbers
static func anim_word(index: int) -> int:
	if index < 0 or index >= anim_sequences.size():
		return 0
	return anim_sequences[index] & 0xffff

## signed version of anim_word (durations are signed)
static func anim_sword(index: int) -> int:
	var v := anim_word(index)
	return v - 0x10000 if v >= 0x8000 else v

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
