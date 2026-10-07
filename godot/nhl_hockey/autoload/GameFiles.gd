extends Node
## Access to the original game files. The port does not ship any asset of the game; it reads the
## files of an installation of NHL Hockey (the directory with HOCKEY.EXE and the .PPV banks).
## The directory is taken from user://settings.cfg (key files/game_dir), the NHL_GAME_DIR
## environment variable, or re/nhl_hockey of this repository when the project runs from a checkout.
## Lookups are case insensitive because DOS file names were upper case and most dumps are not.

const SETTINGS_PATH := "user://settings.cfg"
const DATA_DIR := "user://data"

var game_dir: String = ""
var use_data := true          # read the copies of user://data first (the tests read the installation)
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

## Reads a file without unpacking it (databases, palettes, tiles); a copy the port wrote into
## user://data (the databases the front end changes) comes first
func read_raw(name: String) -> PackedByteArray:
	var u := DATA_DIR.path_join(name.to_lower())
	if use_data and FileAccess.file_exists(u):
		return FileAccess.get_file_as_bytes(u)
	var p := path_of(name)
	if p == "":
		return PackedByteArray()
	return FileAccess.get_file_as_bytes(p)

## the original file, never the copy in user://data
func read_original(name: String) -> PackedByteArray:
	var p := path_of(name)
	return FileAccess.get_file_as_bytes(p) if p != "" else PackedByteArray()

## writes a database of the installation: the port keeps its changes in user://data (the game
## directory stays as installed)
func write_data(name: String, data: PackedByteArray) -> bool:
	DirAccess.make_dir_recursive_absolute(DATA_DIR)
	var f := FileAccess.open(DATA_DIR.path_join(name.to_lower()), FileAccess.WRITE)
	if f == null:
		return false
	f.store_buffer(data)
	return true

## the copies of user://data are dropped (the databases as installed again)
func reset_data(name: String = "") -> void:
	if name != "":
		DirAccess.remove_absolute(DATA_DIR.path_join(name.to_lower()))
		return
	var d := DirAccess.open(DATA_DIR)
	if d != null:
		for f in d.get_files():
			d.remove(f)

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
