class_name Ui
extends Node
## The input side of the EA library's front end: the event queue of the 100 Hz timer
## (ui_timer_callback: ui_poll_mouse, ui_poll_joystick, ui_poll_keyboard every 5 ticks), the mouse
## pointer (POINTER3.QFS "pntr", drawn over the screen at its top left corner) moved by the mouse or by
## the arrow keys / joystick with acceleration (ui_poll_events: 8 << (held / 5) pixels per poll), and
## the menu bar loop shared by frontend_main_menu, pause_menu and run_menu.
##
## Events are dictionaries {type: 1 mouse / 3 keyboard, buttons, x, y, key}; buttons: 1 pressed,
## 2 released (a click, Enter for the keyboard), 4 Esc, 8 Space, 0x20 a typed key (key: its code).

const POLL_TICKS := 5            # ui_timer_callback polls every 5 ticks of the 100 Hz timer
const MAX_X := 0x275             # ui_poll_events: the pointer stays inside (0..0x275, 0..0x1d5)
const MAX_Y := 0x1d5

var scr: Screen8
var pointer_shape: Shpi.Shape
var pointer: Sprite2D
var px := 320
var py := 240
var events: Array = []
var keys: Array = []             # the keyboard buffer getkey reads: ASCII, the scan code << 8 for the others
var active := true
var held := 0                    # arrow_held_polls: polls the arrows have been held (acceleration)
var _tick_acc := 0.0
var _enter_down := false
var _mouse_down := false
var menu_depth := 0              # the menu loops running, nested
var menu_hold := 0               # the loops up to this depth wait (NHL_UI_SCRIPT call: runs a screen outside them)

func setup(screen: Screen8, pointer_bank: Shpi) -> void:
	scr = screen
	if pointer_bank != null:
		pointer_shape = pointer_bank.find("pntr")
		if pointer_shape == null and pointer_bank.shapes.size() > 0:
			pointer_shape = pointer_bank.shapes[0]
	pointer = Sprite2D.new()
	pointer.centered = false
	pointer.z_index = 100
	pointer.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	if pointer_shape != null and pointer_shape.is_image():
		var pix := pointer_shape.pixels.slice(0, pointer_shape.width * pointer_shape.height)
		pointer.texture = ImageTexture.create_from_image(Image.create_from_data(pointer_shape.width, pointer_shape.height, false, Image.FORMAT_R8, pix))
		pointer.material = scr.make_material(0xff)
	scr.add_child(pointer)
	show_pointer(false)

func show_pointer(on: bool) -> void:
	if pointer != null:
		pointer.visible = on and pointer.texture != null
		_place_pointer()

## setmousepos
func set_pointer(x: int, y: int) -> void:
	px = clampi(x, 0, MAX_X)
	py = clampi(y, 0, MAX_Y)
	_place_pointer()
	if active and scr != null and scr.is_inside_tree() and DisplayServer.get_name() != "headless":
		var vp := scr.get_viewport()
		if vp != null:
			vp.warp_mouse(Vector2(px, py))

func _place_pointer() -> void:
	if pointer != null:
		pointer.position = Vector2(px, py)

## event_queue_reset
func reset_events() -> void:
	events.clear()

func push(type: int, buttons: int, key: int = 0) -> void:
	if events.size() < 32:
		events.append({"type": type, "buttons": buttons, "x": px, "y": py, "key": key})

## a key into the keyboard buffer (15 places, like the BIOS)
func push_key(code: int) -> void:
	if keys.size() < 15:
		keys.append(code)

## getkey (0xb39ed): the next key of the buffer, 0 when it is empty
func getkey() -> int:
	return keys.pop_front() if not keys.is_empty() else 0

const SCAN_KEYS := {KEY_ENTER: 0xd, KEY_KP_ENTER: 0xd, KEY_ESCAPE: 0x1b, KEY_BACKSPACE: 8, KEY_TAB: 9,
	KEY_HOME: 0x4700, KEY_UP: 0x4800, KEY_PAGEUP: 0x4900, KEY_LEFT: 0x4b00, KEY_RIGHT: 0x4d00,
	KEY_END: 0x4f00, KEY_DOWN: 0x5000, KEY_PAGEDOWN: 0x5100, KEY_INSERT: 0x5200, KEY_DELETE: 0x5300}

## event_queue_pop + ui_poll_callback: the next event, or {} when the queue is empty
func poll() -> Dictionary:
	if events.is_empty():
		return {}
	return events.pop_front()

## waits for the next event (a frame at a time)
func wait_event() -> Dictionary:
	while events.is_empty():
		await get_tree().process_frame
	return events.pop_front()

## waits for a click (or Enter / Esc / Space): the event
func wait_click() -> Dictionary:
	while true:
		var e: Dictionary = await wait_event()
		if e["buttons"] & 0x2e:
			return e
	return {}

## wait_ticks_or_input: n ticks of the 100 Hz timer or a button; true when a button ended it
func wait_ticks(ticks: int, interruptible: bool = true) -> bool:
	var t := 0.0
	reset_events()
	while t * 100.0 < ticks:
		await get_tree().process_frame
		t += get_process_delta_time()
		if interruptible:
			var e := poll()
			if not e.is_empty() and e["buttons"] & 0x2e:
				return true
	return false

## wait_ticks_or_input (0x33e6a) with its result: 0 the time ran out, 1 a click, 2 a double click
## (a second click within 0x14 ticks), 3 Esc
func wait_ticks_or_input(ticks: int) -> int:
	var t := 0.0
	var clicks := 0
	var first := 0.0
	while t * 100.0 < ticks:
		await get_tree().process_frame
		t += get_process_delta_time()
		var e := poll()
		if not e.is_empty():
			if e["buttons"] & 4:
				return 3
			if e["buttons"] & 2:
				if clicks == 0:
					first = t
				else:
					return 2
				clicks += 1
		if clicks != 0 and (t - first) * 100.0 > 0x14:
			return clicks
	return clicks

func frame() -> void:
	await get_tree().process_frame

func _process(delta: float) -> void:
	if not active:
		return
	_tick_acc += delta * 100.0
	while _tick_acc >= POLL_TICKS:
		_tick_acc -= POLL_TICKS
		_poll_keyboard()

## ui_poll_keyboard + ui_poll_events: the arrows (and the keypad diagonals) move the pointer
func _poll_keyboard() -> void:
	var dir := 0
	if Input.is_physical_key_pressed(KEY_UP) or Input.is_physical_key_pressed(KEY_KP_8):
		dir |= 1
	if Input.is_physical_key_pressed(KEY_DOWN) or Input.is_physical_key_pressed(KEY_KP_2):
		dir |= 2
	if Input.is_physical_key_pressed(KEY_RIGHT) or Input.is_physical_key_pressed(KEY_KP_6):
		dir |= 4
	if Input.is_physical_key_pressed(KEY_LEFT) or Input.is_physical_key_pressed(KEY_KP_4):
		dir |= 8
	if Input.is_physical_key_pressed(KEY_KP_7):
		dir |= 9
	if Input.is_physical_key_pressed(KEY_KP_9):
		dir |= 5
	if Input.is_physical_key_pressed(KEY_KP_1):
		dir |= 10
	if Input.is_physical_key_pressed(KEY_KP_3):
		dir |= 6
	for j in Input.get_connected_joypads():
		var ax := Input.get_joy_axis(j, JOY_AXIS_LEFT_X)
		var ay := Input.get_joy_axis(j, JOY_AXIS_LEFT_Y)
		if ay < -0.5 or Input.is_joy_button_pressed(j, JOY_BUTTON_DPAD_UP):
			dir |= 1
		if ay > 0.5 or Input.is_joy_button_pressed(j, JOY_BUTTON_DPAD_DOWN):
			dir |= 2
		if ax > 0.5 or Input.is_joy_button_pressed(j, JOY_BUTTON_DPAD_RIGHT):
			dir |= 4
		if ax < -0.5 or Input.is_joy_button_pressed(j, JOY_BUTTON_DPAD_LEFT):
			dir |= 8
	if dir == 0:
		held = 0
		return
	held = mini(held + 1, 0x1d)
	var step := 8 << (held / 5)
	if dir & 8:
		px -= step
	if dir & 4:
		px += step
	if dir & 1:
		py -= step
	if dir & 2:
		py += step
	set_pointer(px, py)
	push(3, 0)

func _input(event: InputEvent) -> void:
	if not active:
		return
	if event is InputEventMouseMotion:
		var p: Vector2 = event.position
		px = clampi(int(p.x), 0, MAX_X)
		py = clampi(int(p.y), 0, MAX_Y)
		_place_pointer()
		push(1, 1 if _mouse_down else 0)
	elif event is InputEventMouseButton:
		var p: Vector2 = event.position
		px = clampi(int(p.x), 0, MAX_X)
		py = clampi(int(p.y), 0, MAX_Y)
		_place_pointer()
		if event.button_index == MOUSE_BUTTON_LEFT:
			if event.pressed:
				_mouse_down = true
				push(1, 1)
			elif _mouse_down:
				_mouse_down = false
				push(1, 2)
		elif event.button_index == MOUSE_BUTTON_RIGHT and event.pressed:
			push(3, 4)
	elif event is InputEventKey:
		var k: InputEventKey = event
		if k.pressed:
			# the keyboard buffer (with the typematic repeats)
			if SCAN_KEYS.has(k.keycode):
				push_key(SCAN_KEYS[k.keycode])
			elif k.unicode >= 0x20 and k.unicode < 0x7f:
				push_key(k.unicode)
		if k.echo and k.keycode != KEY_BACKSPACE:
			return
		match k.keycode:
			KEY_ENTER, KEY_KP_ENTER:
				if k.pressed:
					_enter_down = true
					push(3, 1)
				elif _enter_down:
					_enter_down = false
					push(3, 2)
			KEY_ESCAPE:
				if k.pressed:
					push(3, 4)
			KEY_SPACE:
				if k.pressed:
					push(3, 8 | 0x20, 0x20)
			_:
				if k.pressed and (k.unicode >= 0x20 and k.unicode < 0x7f or k.keycode == KEY_BACKSPACE):
					push(3, 0x20, KEY_BACKSPACE if k.keycode == KEY_BACKSPACE else k.unicode)

func is_click(e: Dictionary) -> bool:
	return not e.is_empty() and (e["buttons"] & 2) != 0

# ---------------------------------------------------------------------------------------------
# the menu bar (frontend_main_menu, pause_menu, run_menu)
# ---------------------------------------------------------------------------------------------

## draw_menu_items (0x6b5e4): the bar, every entry boxed, the text with its shadow, then the free part
## of the bar up to the right edge
func draw_menu_items(items: Array, light: int, face: int, dark: int) -> void:
	scr.settextcolor(light, 0xff)
	scr.set_text_colors(light, 0)
	for it: Menus.Item in items:
		scr.draw_box(it.x0, 0, it.x1, it.y1, light, face, dark)
		scr.print_text_at(it.x0 + 3, 2, it.text)
	var last: Menus.Item = items[items.size() - 1]
	scr.draw_box(last.x1 + 1, 0, 0x27f, last.y1, light, face, dark)

## draw_menu (0x6b684): a pull-down list in one box; entries without callback or sub list dimmed
func draw_menu(items: Array, ox: int, oy: int, light: int, face: int, dark: int) -> void:
	var first: Menus.Item = items[0]
	var last: Menus.Item = items[items.size() - 1]
	scr.draw_box(first.x0 + ox, first.y0 + oy, last.x1 + ox, last.y1 + oy, light, face, dark)
	for i in items.size():
		var it: Menus.Item = items[i]
		var y := it.y0 + (2 if i == 0 else 1) + oy
		if it.enabled():
			scr.settextcolor(light, 0xff)
			scr.set_text_colors(light, 0)
			scr.print_text_at(it.x0 + 3 + ox, y, it.text)
		else:
			scr.settextcolor(dark, 0xff)
			scr.printstr_at(it.text, it.x0 + 3 + ox, y)

## menu_item_draw_normal (0x6b94e) with fill = face draws an entry in its normal state,
## menu_item_draw_selected (0x6b9eb) with fill = dark selected
func draw_menu_entry(it: Menus.Item, ox: int, oy: int, text_color: int, fill: int) -> void:
	if not it.enabled():
		return
	var x := ox + it.x0 + 1
	var y := oy + it.y0 + (1 if it.y0 == 0 else 0)
	scr.fillrect(x, y, it.x1 - it.x0 - 2, it.y1 - it.y0 - (1 if it.y0 == 0 else 0), fill)
	scr.settextcolor(text_color, 0xff)
	scr.set_text_colors(text_color, 0)
	scr.print_text_at(x + 2, y + 1, it.text)

var menu_item: Menus.Item = null      # the entry whose callback runs (the callbacks of the original get its record)
var menu_root_index := 0             # and the bar entry it is under

## run_menu (0x1d6e8): the bar `root` (records of Menus) with pull-down lists. A click on a bar entry
## or on an entry with a sub list opens it (below the bar, to the right of a list), the first click on
## an entry with a callback selects it, a second click runs it: handler.call(name) -> code. Code 1
## (or a code in `exit_codes`) leaves the loop and is returned; after code 2 `redraw` draws the screen
## again. A click outside closes the lists and goes to `outside` (the event). `idle` runs every frame
## (a code in exit_codes from it leaves too).
func run_menu(root: Array, light: int, face: int, dark: int, handler: Callable, redraw: Callable = Callable(), exit_codes: Array = [1], idle: Callable = Callable(), outside: Callable = Callable(), each: Callable = Callable()) -> int:
	menu_depth += 1
	var r: int = await _run_menu(menu_depth, root, light, face, dark, handler, redraw, exit_codes, idle, outside, each)
	menu_depth -= 1
	return r

func _run_menu(depth: int, root: Array, light: int, face: int, dark: int, handler: Callable, redraw: Callable, exit_codes: Array, idle: Callable, outside: Callable, each: Callable = Callable()) -> int:
	var lists: Array = [root, [], [], []]
	var origins: Array = [Vector2i.ZERO, Vector2i.ZERO, Vector2i.ZERO, Vector2i.ZERO]
	var current: Array = [0, 0, 0, 0]
	var saved: Array = [null, null, null, null]
	var top := 0
	var first: Menus.Item = root[0]
	set_pointer((first.x0 + first.x1) / 2, (first.y0 + first.y1) / 2)
	show_pointer(true)
	reset_events()
	while true:
		if depth <= menu_hold:
			await get_tree().process_frame
			continue
		if idle.is_valid():
			var r = await idle.call()
			if r is int and r in exit_codes:
				show_pointer(false)
				return r
		var e := poll()
		if e.is_empty():
			await get_tree().process_frame
			continue
		if each.is_valid() and e["buttons"] != 0:
			# every event with a button (database_menu: the scroll arrows and bar)
			await each.call(e)
		if not is_click(e):
			continue
		var hit := _hit_test(lists, top, origins, e["x"], e["y"])
		if hit.x < 0:
			# outside: close every list (menu_page_a / menu_page_b: then a team or a player there)
			for k in range(top, 0, -1):
				scr.put(saved[k])
				saved[k] = null
				lists[k] = []
				current[k] = 0
			top = 0
			if outside.is_valid():
				var oc = await outside.call(e)
				if oc is int and oc in exit_codes:
					show_pointer(false)
					return oc
			continue
		var level := hit.x
		var it: Menus.Item = lists[level][hit.y]
		if it.cb == "":
			if it.sub == 0:
				# a disabled entry: only the selection moves
				draw_menu_entry(lists[level][current[level]], origins[level].x, origins[level].y, light, face)
				current[level] = hit.y
				draw_menu_entry(it, origins[level].x, origins[level].y, light, dark)
				continue
			# open its list (closing the deeper ones)
			for k in range(top, level, -1):
				scr.put(saved[k])
				saved[k] = null
				lists[k] = []
				current[k] = 0
			top = level
			draw_menu_entry(lists[level][current[level]], origins[level].x, origins[level].y, light, face)
			current[level] = hit.y
			draw_menu_entry(it, origins[level].x, origins[level].y, light, dark)
			var sub := Menus.sub_list(it)
			if sub.is_empty():
				continue
			top = level + 1
			lists[top] = sub
			var o: Vector2i = origins[level]
			origins[top] = Vector2i((it.x0 if top == 1 else it.x1) + o.x, (it.y1 if top == 1 else it.y0) + o.y)
			var s0: Menus.Item = sub[0]
			var s1: Menus.Item = sub[sub.size() - 1]
			saved[top] = scr.grab(origins[top].x + s0.x0, origins[top].y + s0.y0, s1.x1 - s0.x0 + 1, s1.y1 - s0.y0 + 1)
			draw_menu(sub, origins[top].x, origins[top].y, light, face, dark)
			current[top] = 0
			draw_menu_entry(sub[0], origins[top].x, origins[top].y, light, dark)
			continue
		if hit.y != current[level]:
			draw_menu_entry(lists[level][current[level]], origins[level].x, origins[level].y, light, face)
			current[level] = hit.y
			draw_menu_entry(it, origins[level].x, origins[level].y, light, dark)
			continue
		# the selected entry again: close the lists and run it
		for k in range(top, 0, -1):
			scr.put(saved[k])
			saved[k] = null
			lists[k] = []
			current[k] = 0
		top = 0
		var keep := Vector2i(px, py)
		show_pointer(false)
		menu_item = it
		menu_root_index = current[0]
		var code = await handler.call(it.cb)
		if not (code is int):
			code = 0
		if code in exit_codes:
			return code
		if code == 2 and redraw.is_valid():
			await redraw.call()
		set_pointer(keep.x, keep.y)
		show_pointer(true)
		reset_events()
	return 0

## hit_test_menus (0x6ba4d): the deepest open list first; the pointer's tip is 4 pixels in
func _hit_test(lists: Array, top: int, origins: Array, x: int, y: int) -> Vector2i:
	for level in range(top, -1, -1):
		var l: Array = lists[level]
		var o: Vector2i = origins[level]
		for i in l.size():
			var it: Menus.Item = l[i]
			if o.x + it.x0 <= x + 4 and x + 4 <= o.x + it.x1 and o.y + it.y0 <= y and y <= o.y + it.y1:
				return Vector2i(level, i)
	return Vector2i(-1, -1)
