extends Node
## Access to the original game files. The port does not ship any asset of the game; it reads the
## files of an installation of NHL Hockey (the directory with HOCKEY.EXE and the .PPV banks).
## The directory is taken from user://settings.cfg (key files/game_dir), the NHL_GAME_DIR
## environment variable, or re/nhl_hockey of this repository when the project runs from a checkout.
## Lookups are case insensitive because DOS file names were upper case and most dumps are not.

const SETTINGS_PATH := "user://settings.cfg"

var game_dir: String = ""
var _index: Dictionary = {}   # lower case name -> real path

func _ready() -> void:
	var cfg := ConfigFile.new()
	if cfg.load(SETTINGS_PATH) == OK:
		game_dir = cfg.get_value("files", "game_dir", "")
	if game_dir == "" or not DirAccess.dir_exists_absolute(game_dir):
		game_dir = OS.get_environment("NHL_GAME_DIR")
	if game_dir == "" or not DirAccess.dir_exists_absolute(game_dir):
		game_dir = repository_game_dir()
	if game_dir != "":
		set_game_dir(game_dir, false)

## re/nhl_hockey next to the Godot project (the game directory committed to the repository)
static func repository_game_dir() -> String:
	var p := ProjectSettings.globalize_path("res://").path_join("../../re/nhl_hockey").simplify_path()
	if FileAccess.file_exists(p.path_join("RINK.QFS")) or FileAccess.file_exists(p.path_join("rink.qfs")):
		return p
	return ""

func set_game_dir(path: String, save: bool = true) -> void:
	game_dir = path
	_index.clear()
	var d := DirAccess.open(path)
	if d == null:
		push_warning("game directory not found: " + path)
		return
	d.list_dir_begin()
	var n := d.get_next()
	while n != "":
		if not d.current_is_dir():
			_index[n.to_lower()] = path.path_join(n)
		n = d.get_next()
	d.list_dir_end()
	if save:
		var cfg := ConfigFile.new()
		cfg.set_value("files", "game_dir", path)
		cfg.save(SETTINGS_PATH)

func available() -> bool:
	return not _index.is_empty()

func has(name: String) -> bool:
	return _index.has(name.to_lower())

func path_of(name: String) -> String:
	return _index.get(name.to_lower(), "")

## Reads a game file (unpacking it when it is compressed), empty array when missing
func read(name: String) -> PackedByteArray:
	var p := path_of(name)
	if p == "":
		return PackedByteArray()
	var data := FileAccess.get_file_as_bytes(p)
	return RefPack.unpack(data)

## Reads a file without unpacking it (databases, palettes, tiles)
func read_raw(name: String) -> PackedByteArray:
	var p := path_of(name)
	if p == "":
		return PackedByteArray()
	return FileAccess.get_file_as_bytes(p)

## loadfile_auto(): tries the .fsh/.qfs/.vsh/.qvs variants of a shape bank name
func read_bank(base: String) -> PackedByteArray:
	for ext in ["", ".fsh", ".qfs", ".vsh", ".qvs", ".PPV", ".ppv", ".iff", ".IFF"]:
		if has(base + ext):
			return read(base + ext)
	return PackedByteArray()

## load_sprite_banks(): file name of sprite bank i (0..22); from bank 20 on the DOS 8.3 limit drops
## the underscore ("10001049.PPV")
static func sprite_bank_name(i: int) -> String:
	var half := i / 2
	if i < 20:
		return ("%d00_%d49" if i % 2 == 0 else "%d50_%d99") % [half, half]
	return ("%d00%d49" if i % 2 == 0 else "%d50%d99") % [half, half]
