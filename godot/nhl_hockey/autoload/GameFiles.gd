extends Node
## Access to the original game files. The port does not ship any asset of the game: point
## `game_dir` at an installation of NHL Hockey (the directory with HOCKEY.EXE and the .PPV files).
## Lookups are case insensitive because DOS file names were upper case and most dumps are not.

const SETTINGS_PATH := "user://settings.cfg"

var game_dir: String = ""
var _index: Dictionary = {}   # lower case name -> real path

func _ready() -> void:
	var cfg := ConfigFile.new()
	if cfg.load(SETTINGS_PATH) == OK:
		game_dir = cfg.get_value("files", "game_dir", "")
	if game_dir == "":
		game_dir = OS.get_environment("NHL_GAME_DIR")
	if game_dir != "":
		set_game_dir(game_dir)

func set_game_dir(path: String) -> void:
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

## loadfile_auto(): tries the .fsh/.qfs/.vsh/.qvs variants of a shape bank name
func read_bank(base: String) -> PackedByteArray:
	for ext in ["", ".fsh", ".qfs", ".vsh", ".qvs", ".PPV", ".ppv", ".iff", ".IFF"]:
		if has(base + ext):
			return read(base + ext)
	return PackedByteArray()
