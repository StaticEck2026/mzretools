class_name Menus
## The menu records of HOCKEY.EXE (Tables.menu_items, extracted by tools/nhl/extract_tables.py):
## 32 bytes each, x0, y0, x1, y1, the text, the callback (+0x14), the sub list (+0x18) and its count
## (+0x1c). The code addresses a menu as its first record and a count, and changes records while it
## runs (set_menu_mode, set_hub_title, set_pause_menu_labels, the goalie names, enabling "Next League
## Game ..." when a league is open), so the records are loaded once into mutable objects addressed
## like the original: Menus.at(0xce4ef).cb = "league_calendar_screen".

class Item:
	var addr: int
	var x0: int
	var y0: int
	var x1: int
	var y1: int
	var text: String
	var cb: String           # routine name of the callback, "" none
	var sub: int             # address of the sub list, 0 none
	var n: int               # records in the sub list

	func enabled() -> bool:
		return cb != "" or sub != 0

static var _items: Dictionary = {}
static var _extra: Dictionary = {}          # the port's own records after a list's: list address -> [Item]

static func _load() -> void:
	if not _items.is_empty():
		return
	for k in Tables.menu_items:
		var r: Array = Tables.menu_items[k]
		var it := Item.new()
		it.addr = k.hex_to_int()
		it.x0 = int(r[0])
		it.y0 = int(r[1])
		it.x1 = int(r[2])
		it.y1 = int(r[3])
		it.text = r[4]
		it.cb = r[5]
		it.sub = (r[6] as String).hex_to_int() if r[6] != "" else 0
		it.n = int(r[7])
		_items[it.addr] = it

## the record at addr (null when the data has none there)
static func at(addr: int) -> Item:
	_load()
	return _items.get(addr, null)

## the record at addr, made when the data has none there (the records whose text the code sets: the
## trade screen's "Show <team> Statistics...")
static func ensure(addr: int, x0: int, y0: int, x1: int, y1: int, cb: String) -> Item:
	_load()
	if not _items.has(addr):
		var it := Item.new()
		it.addr = addr
		it.x0 = x0
		it.y0 = y0
		it.x1 = x1
		it.y1 = y1
		it.cb = cb
		_items[addr] = it
	return _items[addr]

## count records from addr
static func list(addr: int, count: int) -> Array:
	_load()
	var out: Array = []
	for i in count:
		var it: Item = _items.get(addr + i * 32, null)
		if it == null:
			break
		out.append(it)
	if out.size() == count:
		out.append_array(_extra.get(addr, []))
	return out

## a record of the port's own after the list at list_addr (count records of the game's): the Game
## menu's Gameplay Logic
static func append(list_addr: int, count: int, text: String, cb: String) -> Item:
	_load()
	var l: Array = _extra.get(list_addr, [])
	for it: Item in l:
		if it.cb == cb:
			return it
	var last: Item = _items[list_addr + (count - 1) * 32]
	var it := Item.new()
	it.addr = 0x1000000 + _extra.size() * 0x1000 + l.size() * 32
	it.x0 = last.x0
	it.x1 = last.x1
	it.y0 = last.y1
	it.y1 = last.y1 + (last.y1 - last.y0)
	it.text = text
	it.cb = cb
	l.append(it)
	_extra[list_addr] = l
	return it

## the sub list of a record
static func sub_list(it: Item) -> Array:
	return list(it.sub, it.n) if it != null and it.sub != 0 else []

## restores every record (a new session)
static func reset() -> void:
	_items.clear()
	_load()
