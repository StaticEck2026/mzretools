class_name SelectDialog
extends RefCounted
## The selection dialogs of the front end's Open ... (league_select_screen 0x2b944: league_select_buttons
## 0x2b7c3, league_dialog_box 0x2c18f, league_type_menu 0x2bd16, league_name_entry 0x2c801,
## league_name_entry_draw 0x2c461, league_name_prompt 0x2ce29) and of the Central Registry's Load
## Database ... (menu_load_database 0x73703: database_buttons 0x7230b, database_dialog 0x727ee,
## database_type_menu 0x72605, database_select_screen 0x72de7, database_select_draw 0x72ac6,
## database_dbx_check 0x735c3). The dialog at (10, 0x13): three kinds (the buttons on the right,
## the kind shown by a picture), the names of the kind in six rows (scrolled by the arrows and the
## bar when there are more), the name chosen in the field at the top, Open, Delete and Done. The
## places of the dialog are 16 rectangles (slots: 0 / 1 the arrows, 2 Open, 3 Delete, 4 Done, 5..7
## the kinds, 8 the bar, 9 the name, 10..15 the rows; a point is in one when x - 6 and y - 0x13 are),
## the ones that answer a click a bit mask (dword_dd668).
##
## The database dialog's pictures (DB_BUT.QFS, DBDIALOG.QFS) are on the CD only: the league dialog's
## (OPEN_BUT.QFS, DIALOGBX.QFS) stand in for them (its kinds blanked and Current, Original and
## Temporary written on them; its captions and the places of its button row kept).

var fe: FrontEnd
var scr: Screen8
var ui: Ui

var db := false                     # the database dialog (else the league dialog)
var slots: Array = []               # unk_c6f88 / unk_d1084: [x0, y0, x1, y1]
var row_slots: Array = []           # league_slot_at's (the database dialog finds its rows by them too)
var lists: Array = [null, null, null]   # off_c6f7c / off_d1184: {names, sel, first, last}
var kind := -1                      # dword_dd658
var bits := 0                       # dword_dd668
var sh := {}                        # the button pictures
var labels: Array = []              # the kinds' names and places
var buttons_x := 0x20               # the place of the button row's pictures
var standin := false                # the database dialog drawn with the league dialog's pictures

const LEAGUE_SLOTS := 0xc6f88
const DB_SLOTS := 0xd1084
const LEAGUE_LABELS := [["Exhibition", 0xa7, 0x4c], ["Playoffs", 0xab, 0x64], ["League", 0xb0, 0x7c]]
const DB_LABELS := [["Current", 0xb1, 0x4c], ["Original", 0xb1, 0x64], ["Temporary", 0xa7, 0x7c]]

func _init(f: FrontEnd, database: bool) -> void:
	fe = f
	scr = f.scr
	ui = f.ui
	db = database
	for i in 16:
		var a := (DB_SLOTS if db else LEAGUE_SLOTS) + i * 16
		slots.append([Exe.i32(a), Exe.i32(a + 4), Exe.i32(a + 8), Exe.i32(a + 12)])
		var b := LEAGUE_SLOTS + i * 16
		row_slots.append([Exe.i32(b), Exe.i32(b + 4), Exe.i32(b + 8), Exe.i32(b + 12)])
	labels = DB_LABELS if db else LEAGUE_LABELS
	buttons_x = 0x23 if db else 0x20

## a list of names (scan_league_dirs / scan_database_files: sorted by cmp_name_strings, the last
## row the 6th or the last name)
static func make_list(names: Array) -> Dictionary:
	var n := names.duplicate()
	n.sort()
	return {"names": n, "sel": 0, "first": 0, "last": mini(n.size(), 6) - 1}

static func _count(l) -> int:
	return (l["names"] as Array).size() if l != null else 0

# ---------------------------------------------------------------------------------------------
# the pictures and the dialog (league_select_buttons / database_buttons, league_dialog_box /
# database_dialog, league_type_menu / database_type_menu)
# ---------------------------------------------------------------------------------------------

func _load_buttons() -> void:
	var b := fe.bank("db_but") if db else null
	if b == null:
		b = fe.bank("open_but")
		standin = db
		buttons_x = 0x20
	var names := {"none": "none", "del": "del ", "open": "open", "can": "can ", "noar": "noar", "up": "up  ",
		"down": "down", "arro": "arro", "k-": "gtno", "k0": "gtex", "k2": "gtlp", "k1": "gtpo"}
	if db and fe.bank("db_but") != null:
		names.merge({"k-": "dbno", "k0": "dbcu", "k2": "dbtm", "k1": "dbor"}, true)
	for k in names:
		sh[k] = b.find(names[k]) if b != null else null

func _draw_shape(name: String, x: int, y: int) -> void:
	var s: Shpi.Shape = sh.get(name)
	if s != null:
		scr.drawshape_remap(s, x, y)
	if name.begins_with("k"):
		_relabel()

## the stand-in's kinds (the league dialog's pictures) blanked and the database's written on them,
## in the colour the kind has (dimmed without names)
func _relabel() -> void:
	if not standin:
		return
	var keep_fg := scr.text_fg
	var keep_bg := scr.text_bg
	for i in 3:
		var r: Array = row_slots[5 + i]
		scr.fillrect(r[0] + 0xc, r[1] + 0x15, r[2] - r[0] - 3, r[3] - r[1] - 3, 0xf9)
		_text(0xfa if kind < 0 or bits & (0x20 << i) else 0xf8)
		if kind < 0:
			_text(0xf8)
		scr.printstr_at(labels[i][0], labels[i][1], labels[i][2])
	scr.settextcolor(keep_fg, keep_bg)

func _text(fg: int) -> void:
	scr.settextcolor(fg, 0xff)

## a slot's rectangle on the screen (fillrect at x0 + 0xa, y0 + 0x13)
func _fill(i: int, c: int, plus := 1) -> void:
	var s: Array = slots[i]
	scr.fillrect(s[0] + 0xa, s[1] + 0x13, s[2] - s[0] + plus, s[3] - s[1] + plus, c)

func _print_row(k: int, name: String) -> void:
	scr.printstr_at(name, slots[10 + k][0] + 0xa, slots[10 + k][1] + 0x10)

func _print_name(name: String) -> void:
	scr.printstr_at(name, slots[9][0] + 0xd, slots[9][1] + 0x13)

func _clear_name() -> void:
	var s: Array = slots[9]
	scr.fillrect(s[0] + 0xd, s[1] + 0x16, s[2] - s[0] - 5, s[3] - s[1] - 5, 0xf8)

## the rows answering clicks: as many as there are names
func _row_bits(count: int) -> void:
	for i in mini(count, 6):
		bits |= 0x400 << i

## the bar's lines from y0 to y1 (light above and left, dark below and right)
func _bar(y0: int, y1: int) -> void:
	var s: Array = slots[8]
	var x0: int = s[0] + 0xa
	var x1: int = s[2] + 0xa
	var light := 0x7d if db else 0xfa
	var dark := 0x7b if db else 0xf8
	scr.drawline(x0, y0, s[2] + 9, y0, light)
	scr.drawline(x0, y0, x0, y1 - 1, light)
	scr.drawline(x1, y0 + 1, x1, y1, dark)
	scr.drawline(x0 + 1, y1, x1, y1, dark)

## the bar's scale (the league's 80 pixel bar; the database dialog's 142)
func _scale() -> int:
	return 142 if db else 80

## league_dialog_box / database_dialog: DIALOGBX "dbox" (DBDIALOG "pdbx"); the first kind with names
## (the last of League / Playoffs / Exhibition found) and its names
func dialog_box() -> void:
	var b := fe.bank("dbdialog") if db else null
	var box: Shpi.Shape = b.find("pdbx") if b != null else null
	if box == null:
		var d := fe.bank("dialogbx")
		box = d.find("dbox") if d != null else null
	if box != null:
		scr.drawshape_remap(box, 0xa, 0x13)
	_relabel()
	bits = 0x10
	kind = -1
	if _count(lists[2]) != 0:
		bits = 0x90
		kind = 2
	if _count(lists[1]) != 0:
		bits |= 0x40
		kind = 1
	if _count(lists[0]) != 0:
		bits |= 0x20
		kind = 0
	if kind < 0:
		return
	bits |= 0x204 if db else 0x20c
	_text(0xfa)
	var l: Dictionary = lists[kind]
	var names: Array = l["names"]
	_print_name(names[l["sel"]])
	_fill(8, 0xf8)
	var k := 0
	for i in range(l["first"], l["last"] + 1):
		_print_row(k, names[i])
		k += 1
	if names.size() > 6:
		bits |= 0xff03
		_bar(slots[8][1] + 0x13, slots[8][1] + (0x12 if db else 0x11) + 6 * _scale() / names.size())
	else:
		_row_bits(names.size())

## league_type_menu / database_type_menu: the kinds without names written over (dimmed), the arrows
## (the league's), the kind's picture; without names Open, Delete and the kinds dimmed
func type_menu() -> void:
	_text(0xf8)
	if kind < 0:
		var league_row := not db or standin
		scr.printstr_at("Open", 0x2a if league_row else 0x2d, 0xc0)
		scr.printstr_at("Delete", 0x6b if league_row else 0x6e, 0xc0)
		_text(0xfa)
		scr.printstr_at("Done", 0xb8 if league_row else 0xb5, 0xc0)
		_text(0xf8)
		for t in labels:
			scr.printstr_at(t[0], t[1], t[2])
		_draw_shape("noar", 0x18, 0x46)
		if not db:
			_draw_shape("k-", 0xa3, 0x4b)
		return
	for i in [2, 1, 0]:
		if not (bits & (0x20 << i)):
			scr.printstr_at(labels[i][0], labels[i][1], labels[i][2])
	if not db:
		_draw_shape("noar" if _count(lists[kind]) <= 6 else "arro", 0x18, 0x46)
	_draw_shape("k%d" % kind, 0xa3, 0x4b)
	if db:
		if kind == 2:
			_text(0xfa)
		scr.printstr_at("Delete", 0x6b if standin else 0x6e, 0xc0)
		_text(0xf8)

## league_name_entry_draw / database_select_draw: the rows, the name chosen, its row marked, the
## bar or the rows that answer clicks, the arrows (the league's) and the kind's picture
func draw(l) -> void:
	_text(0xfa)
	for i in 6:
		_fill(10 + i, 0xf9)
	if l == null:
		if not db:
			_clear_name()
		return
	var names: Array = l["names"]
	if names.size() <= 6:
		for i in names.size():
			_print_row(i, names[i])
	else:
		for i in 6:
			_print_row(i, names[l["first"] + i])
	if names.size() > 0:
		_clear_name()
		_print_name(names[l["sel"]])
	if l["sel"] >= l["first"] and l["sel"] <= l["last"]:
		var k: int = l["sel"] - l["first"]
		_fill(10 + k, 0xf8, 0)
		_print_row(k, names[l["first"] + k])
	_fill(8, 0xf9)
	if names.size() <= 6:
		bits &= 0x6fc
		_row_bits(names.size())
	else:
		bits |= 0xf903
		var top: int = slots[8][1] + 0x13
		if db:
			_bar(top + l["first"] * 142 / names.size(), top + (l["last"] + 1) * 142 / names.size())
		else:
			_bar(top + l["first"] * 80 / names.size(), slots[8][1] + 0x12 + (l["last"] + 1) * 80 / names.size())
	if not db:
		_draw_shape("noar" if _count(lists[kind]) <= 6 else "arro", 0x18, 0x46)
	if kind >= 0:
		_draw_shape("k%d" % kind, 0xa3, 0x4b)

# ---------------------------------------------------------------------------------------------
# the loop (league_name_entry / database_select_screen)
# ---------------------------------------------------------------------------------------------

## league_slot_at / database_slot_at: the slot under (x, y), -1 none
static func slot_at(table: Array, x: int, y: int) -> int:
	for i in 16:
		var s: Array = table[i]
		if x - 6 >= s[0] and x - 6 <= s[2] and y - 0x13 >= s[1] and y - 0x13 <= s[3]:
			return i
	return -1

## the dialog: the buttons, the box, the kinds; then the clicks until Done (0), Open (the caller's
## answer: on_open) or the right button / Esc (0). on_delete removes the name chosen
func run(on_open: Callable, on_delete: Callable) -> int:
	_load_buttons()
	dialog_box()
	type_menu()
	var l = lists[kind] if kind >= 0 else null
	var dragging := false              # [esp+0x18]: a held button on the bar
	var slow := false                  # ebp: moves too small to scroll gather from an anchor
	var anchor := 0                    # [esp+0x20]
	var px := ui.px
	var py := ui.py
	ui.reset_events()
	ui.show_pointer(true)
	var result := 0
	while true:
		var e: Dictionary = await ui.wait_event()
		var b: int = e["buttons"]
		var x: int = e["x"]
		var y: int = e["y"]
		if b == 0:
			px = x
			py = y
			continue
		if b & 1 and bits & 0x100:
			if x != px or y != py:
				var s := slot_at(slots, x, y)
				if s != 8:
					dragging = false
				elif not dragging:
					dragging = true
				else:
					await _drag(l, py, y, [slow, anchor])
			px = x
			py = y
			continue
		px = x
		py = y
		if b & 2:
			dragging = false
			var s := slot_at(slots, x, y)
			if s < 0 or not (bits & (1 << s)):
				continue
			var bit := 1 << s
			match bit:
				0x10:
					_draw_shape("can", buttons_x, 0xbf)
					result = 0
					break
				0x01:
					_draw_shape("up", 0x18, 0x46)
					if l["first"] != 0:
						l["first"] -= 1
						l["last"] -= 1
						draw(l)
					if db:
						_draw_shape("noar", 0x18, 0x46)
				0x02:
					_draw_shape("down", 0x18, 0x46)
					if l["last"] + 1 < _count(l):
						l["first"] += 1
						l["last"] += 1
						draw(l)
					if db:
						_draw_shape("noar", 0x18, 0x46)
				0x100:
					var n := _count(l)
					var pos: int = (y - 0x13 - slots[8][1]) * n
					pos = (pos >> 5) if db else pos / 0x50
					if db and pos < 0:
						pos = -((-(y - 0x13 - slots[8][1]) * n) >> 5)
					if pos < l["first"]:
						if pos < 3:
							l["first"] = 0
							l["last"] = 5
						else:
							l["first"] = pos - 3
							l["last"] = pos + 2
						draw(l)
					elif pos > l["last"]:
						if pos + 3 > n:
							l["first"] = n - 6
							l["last"] = n - 1
						else:
							l["first"] = pos - 3
							l["last"] = pos + 2
						draw(l)
				0x20, 0x40, 0x80:
					kind = {0x20: 0, 0x40: 1, 0x80: 2}[bit]
					if db:
						if kind == 2:
							bits |= 8
						else:
							bits &= ~8
						type_menu()
					l = lists[kind]
					draw(l)
				0x04:
					_draw_shape("open", buttons_x, 0xbf)
					ui.show_pointer(false)
					result = await on_open.call(kind, l["names"][l["sel"]])
					break
				0x08:
					_draw_shape("del", buttons_x, 0xbf)
					ui.show_pointer(false)
					await _delete(l, on_delete)
					ui.show_pointer(true)
					l = lists[kind] if kind >= 0 else null
					draw(l)
					_draw_shape("none", buttons_x, 0xbf)
				_:
					var r := slot_at(row_slots, x, y)
					if r > 9:
						l["sel"] = l["first"] + r - 10
					draw(l)
		elif b & 4:
			result = 0
			break
	ui.show_pointer(false)
	ui.reset_events()
	return result

## a held button moved on the bar: the rows scrolled by the move (the league's: moves too small
## for a row gathered from an anchor)
func _drag(l: Dictionary, prev_y: int, y: int, st: Array) -> void:
	var n := _count(l)
	var div := 0x20 if db else 0x50
	var pos: int = (prev_y - 0x13 - slots[8][1]) * n / div
	var last: int = l["last"]
	if prev_y == y or pos < l["first"] or pos > last:
		return
	var base := prev_y
	if not db and st[0]:
		base = st[1]
	var d := 0
	if base < y:
		d = (y - base) * n / div
	elif base > y:
		d = -((base - y) * n / div)
	else:
		return
	if not db:
		if d == 0:
			if not st[0]:
				st[1] = prev_y
			st[0] = true
		else:
			st[0] = false
	if base < y:
		if l["last"] + d < n:
			l["first"] += d
			l["last"] += d
		else:
			l["last"] = n - 1
			l["first"] = n - 6
	else:
		if l["first"] + d >= 0:
			l["first"] += d
			l["last"] += d
		else:
			l["first"] = 0
			l["last"] = 5
	if last != l["last"]:
		draw(l)

## league_name_prompt / database_dbx_check: the name deleted when the caller confirms it (on_delete
## answers true), taken out of its list; without names left the kind goes (the first kind with
## names chosen) and the kinds drawn again
func _delete(l: Dictionary, on_delete: Callable) -> void:
	var names: Array = l["names"]
	if not await on_delete.call(kind, names[l["sel"]]):
		return
	names.remove_at(l["sel"])
	var n := names.size()
	if n == 0:
		if db:
			bits &= ~0x88
			if _count(lists[0]) != 0:
				kind = 0
			elif _count(lists[1]) != 0:
				kind = 1
			else:
				kind = -1
				bits = 0x10
		else:
			bits &= ~(0x20 << kind)
			kind = -1
			for k in 3:
				if _count(lists[k]) != 0:
					kind = k
					break
			if kind < 0:
				bits = 0x10
		type_menu()
		return
	if n < 6:
		l["last"] = n - 1
		l["first"] = 0
	elif n == l["last"]:
		l["first"] -= 1
		l["last"] -= 1
	if l["sel"] == n:
		l["sel"] -= 1
