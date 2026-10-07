class_name SaveGame
## A game saved from the pause screen (Save Game ...: broadcast_booth_screen 0x85924, save_game
## 0x5fb03, savegame_io 0x60612). The original writes the settings block, the game summary, the
## scores around the league and its match state (the 17 entities, the two team records, the line
## tables, the clock ...) into NAME.NHL (an exhibition) or the league's GAME.SAV, and continues the
## game from it later. Here the match state is every script variable of the simulation, its
## entities, team records and crowd figures, by name (the instant replay starts empty again).

const MAGIC := "NHLSAVE1"
const SKIP := {"team_info": true, "puck": true, "shadow": true, "referee": true, "replay": true, "info": true}

## the script variables of an object (nested objects as dictionaries)
static func capture(o: Object) -> Dictionary:
	var out := {}
	for p in o.get_property_list():
		if p["usage"] & PROPERTY_USAGE_SCRIPT_VARIABLE == 0:
			continue
		var n: String = p["name"]
		if SKIP.has(n):
			continue
		out[n] = _encode(o.get(n))
	return out

static func _encode(v):
	if v is Object:
		return {"__obj": capture(v)} if v != null else null
	if v is Array:
		var a: Array = []
		for x in v:
			a.append(_encode(x))
		return a
	if v is Dictionary:
		var d := {}
		for k in v:
			d[k] = _encode(v[k])
		return d
	return v

## the variables back into an object; nested objects and arrays of objects are restored in place
static func restore(o: Object, d: Dictionary) -> void:
	for n in d:
		var v = d[n]
		var cur = o.get(n)
		if v is Dictionary and v.has("__obj"):
			if cur is Object and cur != null:
				restore(cur, v["__obj"])
			continue
		if v is Array and cur is Array:
			var has_obj := false
			for x in v:
				if x is Dictionary and x.has("__obj"):
					has_obj = true
			if has_obj:
				for i in mini(v.size(), cur.size()):
					if v[i] is Dictionary and v[i].has("__obj") and cur[i] is Object:
						restore(cur[i], v[i]["__obj"])
				continue
			cur.clear()
			cur.append_array(v)
			continue
		o.set(n, v)

static func write(path: String, data: Dictionary) -> bool:
	DirAccess.make_dir_recursive_absolute(path.get_base_dir())
	var f := FileAccess.open(path, FileAccess.WRITE)
	if f == null:
		return false
	f.store_buffer(MAGIC.to_ascii_buffer())
	f.store_buffer(var_to_bytes(data))
	return true

static func read(path: String) -> Dictionary:
	var b := FileAccess.get_file_as_bytes(path)
	if b.size() < 8 or b.slice(0, 8).get_string_from_ascii() != MAGIC:
		return {}
	var v = bytes_to_var(b.slice(8))
	return v if v is Dictionary else {}

static func saves_dir() -> String:
	return "user://saves"

## the saved exhibitions (NAME.NHL)
static func list_saves() -> PackedStringArray:
	var out := PackedStringArray()
	var d := DirAccess.open(saves_dir())
	if d == null:
		return out
	for f in d.get_files():
		if f.to_upper().ends_with(".NHL"):
			out.append(f.get_basename())
	out.sort()
	return out
