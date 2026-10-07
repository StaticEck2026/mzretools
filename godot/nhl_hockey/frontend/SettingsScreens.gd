class_name SettingsScreens
extends RefCounted
## The settings dialogs of the front end, drawn over the desk at (10, 0x13):
##  - the exhibition settings before a game (menu_exhibition_settings 0x7bebb with the routines at
##    0x7bf56..0x7c852: SETTING6.QFS, eight on / off pairs and the period length 5 / 10 / 20)
##  - the settings of the pause screen (game_settings_screen 0x7b3a7: SETTING4.QFS, the same
##    pairs without the period length; SETTING7.QFS shows a league's settings)
##  - the controllers of player 1 and 2 (menu_p1_controls_a .. d: PLAYER.QFS, the team, the device)
##  - the sound card (menu_sound_settings 0x82579, sound_setup_screen: SOUND.QFS)
## The on / off pairs are bits of option_flags: penalties, offsides, line changes, two line pass,
## injuries, (fighting: no pair), music, sound effects, digitized speech.

var fe: FrontEnd
var scr: Screen8
var ui: Ui
var shapes: Shpi                    # SETTINGS.QFS (settings_toggles): On / Off, acpt / canc, pl05 / pl10 / pl20

const DX := 10                      # the dialogs' origin on the screen
const DY := 0x13

func _init(f: FrontEnd) -> void:
	fe = f
	scr = f.scr
	ui = f.ui

func _shape(name: String) -> Shpi.Shape:
	if shapes == null:
		shapes = fe.bank("settings")
	if shapes == null:
		return null
	var s := shapes.find(name)
	if s == null:
		for c in shapes.shapes:
			if c.name.strip_edges().to_lower() == name.strip_edges().to_lower():
				return c
	return s

## the button rectangles of a dialog (relative to the dialog): count x 16 bytes x0, y0, x1, y1
static func rects(addr: int, count: int) -> Array:
	var out: Array = []
	for i in count:
		var a := addr + i * 16
		out.append(Rect2i(Exe.i32(a), Exe.i32(a + 4), Exe.i32(a + 8) - Exe.i32(a), Exe.i32(a + 12) - Exe.i32(a + 4)))
	return out

## the rectangle under the pointer: the tip is 4 pixels in (x - 6 = x + 4 - 10)
static func rect_at(list: Array, x: int, y: int) -> int:
	for i in list.size():
		var r: Rect2i = list[i]
		if r.position.x < 0:
			continue
		if x - 6 >= r.position.x and x - 6 <= r.end.x and y - DY >= r.position.y and y - DY <= r.end.y:
			return i
	return -1

## the grey ramp of the dialogs in colours 0xf7..0xfa (setpalette(0xf7, 4, unk_d16a0))
func _dialog_palette() -> void:
	scr.setpalette(Exe.bytes(0xd16a0, 12), 0xf7, 4)

## draw_settings_title (0x8050f): "Exhibition" / "Playoff" / "League" on top of the dialog
func _title(kind: int) -> void:
	var x := DX + (0x59 if kind == 3 or kind == 5 else 0x51)
	var t := ["Exhibition", "Playoff", "League"]
	var dx := [-0x41, -0x32, -0x2f]
	var m := clampi(Session.mode, 0, 2)
	scr.setfont(fe.font_main)
	scr.settextcolor(0xfa, 0xff)
	scr.printstr_at(t[m], x + dx[m], DY + 0x16)

## the settings bits of the pairs (exhibition_settings_show_options / game_settings_show_options)
func _flags_to_bits(with_length: bool) -> int:
	var f := Session.option_flags
	var bits := f & 0x3f
	if Session.sound_device & 0x10 == 0:
		bits |= f & 0xc0
	if Session.sound_device & 0x22 != 0:
		bits |= f & 0x100
	if with_length:
		match (f >> 10) & 3:
			0:
				bits |= 0x800
			1:
				bits |= 0x400
			_:
				bits |= 0x200
	return bits

## game_settings_draw_buttons / exhibition_settings_draw_buttons: the On / Off picture of each pair at
## its "on" rectangle, the period length picture at the first period rectangle
func _draw_pairs(list: Array, bits: int, with_length: bool) -> void:
	for k in 9:
		if k == 5:
			continue
		var r: Rect2i = list[k * 2]
		scr.drawshape(_shape("On  " if bits & (1 << k) else "Off "), r.position.x + DX, r.position.y + DY)
	if with_length:
		var r: Rect2i = list[0x12]
		var s := ""
		match bits & 0xe00:
			0x200:
				s = "pl20"
			0x400:
				s = "pl10"
			0x800:
				s = "pl05"
		if s != "":
			scr.drawshape(_shape(s), r.position.x + DX, r.position.y + DY)

## the labels of the pairs that cannot change: no sound card (music, sound), no digital sound
## (digitized speech)
func _dim_labels() -> void:
	scr.settextcolor(0xf8, 0xff)
	if Session.sound_device == 0x10:
		scr.printstr_at("Music", 0x60, 0xaa)
		scr.printstr_at("Sound", 0x60, 0xc0)
	if not Session.sound_enabled:
		scr.printstr_at("Digitized Speech", 0x60, 0xd6)

## the settings dialog: SETTING6 with the period length (exhibition, before a game) or SETTING4
## (pause screen). Accept writes option_flags; a league's settings (SETTING7) can only be looked at.
func _settings(with_length: bool) -> int:
	var behind := scr.snapshot()
	var pal := scr.getpalette()
	_dialog_palette()
	var bank_name := "setting6" if with_length else ("setting7" if Session.mode == 2 else "setting4")
	var b := fe.bank(bank_name)
	if b != null:
		scr.drawshape_remap(b.find("dbox"), DX, DY)
	_dim_labels()
	_title(6 if with_length else 4)
	var list := rects(0xd17ec if with_length else 0xd16ac, 23 if with_length else 20)
	var bits := _flags_to_bits(with_length)
	_draw_pairs(list, bits, with_length)
	var accept := 0x15 if with_length else 0x12
	var ay := 0x120 if with_length else 0xf8
	ui.show_pointer(true)
	ui.reset_events()
	var done := false
	while not done:
		var e: Dictionary = await ui.wait_event()
		var bt: int = e["buttons"]
		if bt & 4:
			scr.drawshape(_shape("canc"), 0x81, ay)
			break
		if bt & 2 == 0:
			continue
		var k := rect_at(list, e["x"], e["y"])
		if k < 0 or k == 10 or k == 11:
			continue
		if k >= 0xc and k < 0x10 and Session.sound_device == 0x10:
			continue
		if (k == 0x10 or k == 0x11) and not Session.sound_enabled:
			continue
		if Session.mode == 2 and not with_length and k < accept:
			continue
		if k < 0x12:
			if k % 2 == 0:
				bits |= 1 << (k / 2)
			else:
				bits &= ~(1 << (k / 2))
			_draw_pairs(list, bits, with_length)
		elif with_length and k < 0x15:
			bits = (bits & 0xf1ff) | (1 << (k - 9))
			_draw_pairs(list, bits, with_length)
		elif k == accept:
			scr.drawshape(_shape("acpt"), 0x37, ay)
			var f := Session.option_flags & ~0x3f
			f |= bits & 0x3f
			if Session.sound_device != 0x10:
				f = (f & ~0xc0) | (bits & 0xc0)
			if Session.sound_device & 0x22 != 0:
				f = (f & ~0x100) | (bits & 0x100)
			if with_length:
				f &= ~0xc00
				match bits & 0xe00:
					0x200:
						f |= 0x800
					0x400:
						f |= 0x400
			Session.option_flags = f
			if f & 0x40:
				if not fe.loop_playing() and fe.loop_name != "":
					fe.play_loop(fe.loop_name)
			else:
				fe.stop_loop()
			fe.save_game_set()
			_apply_to_match()
			done = true
		else:
			scr.drawshape(_shape("canc"), 0x81, ay)
			done = true
	ui.show_pointer(false)
	await fe.ui.wait_ticks(15, false)
	scr.restore(behind)
	scr.setpalette(pal)
	return 0

## the options of a game on: the rules of the simulation and the sound (game_settings_screen:
## without line changes everybody is rested)
func _apply_to_match() -> void:
	var m: Node = fe.game
	if m == null:
		return
	var f := Session.option_flags
	var sim: Sim = m.sim
	sim.opt_penalties = f & 1 != 0
	sim.opt_offsides = f & 2 != 0
	sim.opt_line_changes = f & 4 != 0
	sim.opt_two_line_pass = f & 8 != 0
	sim.opt_injuries = f & 0x10 != 0
	if not sim.opt_line_changes:
		for t in sim.teams:
			for i in 28:
				t.energy[i] = 0x1000
	m.sfx_on = f & 0x80 != 0
	m.music_on = f & 0x40 != 0
	if m.music != null:
		m.music.set_music_enabled(m.music_on)

## Exhibition Settings ... (menu_exhibition_settings)
func menu_exhibition_settings() -> int:
	return await _settings(true)

## "Exhibition / Playoff / Show League Settings ..." of the pause screen (game_settings_screen)
func game_settings_screen() -> int:
	return await _settings(false)

# ---------------------------------------------------------------------------------------------
# the controllers (menu_p1_controls_* / menu_p2_controls_*: controller_dialog,
# controller_select_dialog, controller_menu)
# ---------------------------------------------------------------------------------------------

## the boxes (unk_d195c): 0 home team, 1 visitors, 2 mouse, 3 joystick one, 4 joystick two,
## 5 keyboard, 6 none, 7 Accept, 8 Cancel; bit k of the state for box k
func _box_lines(r: Rect2i, on: bool, stats_colours: bool) -> void:
	var light := 0x40 if stats_colours else 0xfa
	var dark := 0x42 if stats_colours else 0xf8
	var a := dark if on else light
	var b := light if on else dark
	scr.drawline(r.position.x + 10, r.end.y + 0x12, r.position.x + 10, r.position.y + 0x13, a)
	scr.drawline(r.position.x + 10, r.position.y + 0x13, r.end.x + 9, r.position.y + 0x13, a)
	scr.drawline(r.end.x + 10, r.position.y + 0x14, r.end.x + 10, r.end.y + 0x13, b)
	scr.drawline(r.end.x + 10, r.end.y + 0x13, r.position.x + 0xb, r.end.y + 0x13, b)

func _controls(player: int, stats_colours: bool) -> int:
	var behind := scr.snapshot()
	var b := fe.bank("player")
	if b != null:
		scr.drawshape_remap(b.find("dbox"), DX, DY)
	var list := rects(0xd195c, 9)
	var fg := 0x40 if stats_colours else 0xfa
	scr.setfont(fe.font_main)
	scr.settextcolor(fg, 0xff)
	for t in 2:
		var r: Rect2i = list[t]
		var y := r.position.y + 0x14
		scr.fillrect(r.position.x + 0xb, y, r.end.x + 10 - (r.position.x + 0xb), r.end.y + 0x13 - y, 0x43 if stats_colours else 0xf9)
		scr.printstr_at(GameScreens.city(Session.home_team if t == 0 else Session.away_team), r.position.x + 0xe, y)
	scr.printstr_at("One's" if player == 0 else "Two's", 0x4a, 0x20)
	var other_dev := Session.p2_device if player == 0 else Session.p1_device
	var enabled := 0x1c3 | ((Session.input_devices & 1) << 2) | ((Session.input_devices >> 1 & 1) << 3) | ((Session.input_devices >> 2 & 1) << 4) | ((Session.input_devices >> 3 & 1) << 5)
	if other_dev != 0x10:
		enabled &= ~(other_dev << 2)
	var team := Session.p1_team if player == 0 else Session.p2_team
	var side := Session.p1_side if player == 0 else Session.p2_side
	var dev := Session.p1_device if player == 0 else Session.p2_device
	var state := 0
	if team < 0:
		state = 0x41 if team == -1 else 0x42
	else:
		state = (1 if side != 0 else 0) + 1
		if enabled & (dev << 2):
			state |= dev << 2
	for k in 9:
		_box_lines(list[k], state & (1 << k) != 0, stats_colours)
	scr.settextcolor(0x42 if stats_colours else 0xf8, 0xff)
	var names := ["The Mouse", "Joystick One", "Joystick Two", "The Keyboard"]
	var dx := [0x19, 0x12, 0x11, 0xf]
	for i in 4:
		if enabled & (4 << i) == 0:
			var r: Rect2i = list[2 + i]
			scr.printstr_at(names[i], r.position.x + dx[i], r.position.y + 0x14)
	ui.show_pointer(true)
	ui.reset_events()
	while true:
		var e: Dictionary = await ui.wait_event()
		var bt: int = e["buttons"]
		if bt & 4:
			break
		if bt & 2 == 0:
			continue
		var k := -1
		for i in 9:
			var r: Rect2i = list[i]
			if e["x"] - 6 >= r.position.x and e["x"] - 6 <= r.end.x and e["y"] - DY >= r.position.y and e["y"] - DY <= r.end.y:
				k = i
				break
		if k < 0:
			continue
		var bit := 1 << k
		if state & bit or enabled & bit == 0:
			continue
		if k < 2:
			state = (state & ~3) | bit
		elif k < 7:
			state = (state & ~0x7c) | bit
		elif k == 7:
			_box_lines(list[7], true, stats_colours)
			_accept_controls(player, state)
			break
		else:
			_box_lines(list[8], true, stats_colours)
			break
		for i in 7:
			_box_lines(list[i], state & (1 << i) != 0, stats_colours)
	ui.show_pointer(false)
	await ui.wait_ticks(12, false)
	scr.restore(behind)
	return 0

## controller_menu's Accept: the device and the team of the player; the other player gives way
func _accept_controls(player: int, state: int) -> void:
	var o := 1 - player
	var teams := [Session.p1_team, Session.p2_team]
	var sides := [Session.p1_side, Session.p2_side]
	var devs := [Session.p1_device, Session.p2_device]
	devs[player] = state >> 2
	if state == 0x41:
		teams[player] = -1
		sides[player] = 0
		if teams[o] == -1:
			teams[o] = -2
			sides[o] = 1
		elif sides[o] == 0:
			teams[o] = Session.away_team
			sides[o] = 1
	elif state == 0x42:
		teams[player] = -2
		sides[player] = 1
		if teams[o] == -2:
			teams[o] = -1
			sides[o] = 0
		elif sides[o] == 1:
			teams[o] = Session.home_team
			sides[o] = 0
	elif state & 1 == 0:
		teams[player] = Session.away_team
		sides[player] = 1
		if teams[o] == -2:
			teams[o] = -1
			sides[o] = 0
	else:
		teams[player] = Session.home_team
		sides[player] = 0
		if teams[o] == -1:
			teams[o] = -2
			sides[o] = 1
	Session.p1_team = teams[0]
	Session.p2_team = teams[1]
	Session.p1_side = sides[0]
	Session.p2_side = sides[1]
	Session.p1_device = devs[0]
	Session.p2_device = devs[1]
	fe.save_game_set()
	# a game on: the users change sides (menu_p1_controls_c)
	var m: Node = fe.game
	if m != null:
		var sim: Sim = m.sim
		sim.user1_team = Session.user_side(0)
		sim.user2_team = Session.user_side(1)
		sim.assign_users()
		fe.games.set_goalie_menu_labels()

func menu_p1_controls_a() -> int:
	return await _controls(0, Session.mode == 2)

func menu_p2_controls_a() -> int:
	return await _controls(1, Session.mode == 2)

func menu_p1_controls_b() -> int:
	return await _controls(0, false)

func menu_p2_controls_b() -> int:
	return await _controls(1, false)

func menu_p1_controls_c() -> int:
	return await _controls(0, false)

func menu_p2_controls_c() -> int:
	return await _controls(1, false)

func menu_p1_controls_d() -> int:
	return await _controls(0, true)

func menu_p2_controls_d() -> int:
	return await _controls(1, true)

# ---------------------------------------------------------------------------------------------
# the sound card (menu_sound_settings 0x82579, sound_setup_screen 0x8291e)
# ---------------------------------------------------------------------------------------------

## the cards of the boxes (unk_d23a3): 0 PC speaker (1), 1 Sound Blaster (2), 2 AdLib (4), 3 MT-32 (8),
## 4 none (0x10), 5 UltraSound (0x20), 6 Accept, 7 Cancel
func menu_sound_settings() -> int:
	var behind := scr.snapshot()
	var b := fe.bank("sound")
	if b != null:
		scr.drawshape_remap(b.find("dbx2"), DX, DY)
	var list := rects(0xd23a3, 8)
	var state := Session.sound_device
	var draw := func() -> void:
		for k in 8:
			_box_lines(list[k], state & (1 << k) != 0, false)
		scr.settextcolor(0xf8, 0xff)
		var avail := Session.sound_cards
		var labels := [[1, "PC Speaker", 0, 0x18], [2, "Sound Blaster", 1, 0xe], [4, "AD Lib", 2, 0x29], [8, "MT-32", 3, 0x28], [0x20, "UltraSound", 5, 0x18]]
		for l in labels:
			if avail & l[0] == 0:
				var r: Rect2i = list[l[2]]
				scr.printstr_at(l[1], r.position.x + l[3], r.position.y + 0x13)
	draw.call()
	ui.show_pointer(true)
	ui.reset_events()
	while true:
		var e: Dictionary = await ui.wait_event()
		var bt: int = e["buttons"]
		if bt & 4:
			break
		if bt & 2 == 0:
			continue
		var k := rect_at(list, e["x"], e["y"])
		if k < 0:
			continue
		var bit := 1 << k
		if k < 6:
			if state & bit == 0 and Session.sound_cards & bit:
				state = bit
				draw.call()
		elif k == 6:
			_box_lines(list[6], true, false)
			if state != Session.sound_device:
				Session.sound_device = state
				Session.sound_enabled = state & 0x22 != 0
				if Session.sound_enabled:
					Session.option_flags |= 0x100
				else:
					Session.option_flags &= ~0x100
				fe.save_nhl_cfg()
			break
		else:
			_box_lines(list[7], true, false)
			break
	ui.show_pointer(false)
	await ui.wait_ticks(12, false)
	scr.restore(behind)
	return 0
