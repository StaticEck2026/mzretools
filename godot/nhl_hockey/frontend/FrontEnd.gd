class_name FrontEnd
extends Node
## The front end of HOCKEY.EXE on the 640x480 screen: main (0x10094) after the intro, the EA SPORTS
## desk (frontend_main_menu 0x31ab5) with its menu bar, and the screens its entries run. Every menu
## callback is a method named like the routine of the original (Menus records name their callback),
## so run_menu dispatches by name. The screens are coroutines translated from the decompiled
## routines: they draw into the Screen8 frame buffer with the original coordinates and colour
## indices and wait for the events of the Ui like the original polls its event queue.
##
## The match runs in the App (view/App.gd): play_game asks it for a match and waits until the game
## is over or left.

signal play_match(setup: Dictionary)

const LIGHT := 0xfa
const FACE := 0xf9
const DARK := 0xf8

var app: Node                        # view/App.gd (play_match_async, quit)
var scr: Screen8
var ui: Ui
var layer: CanvasLayer
var fonts: Dictionary = {}           # s1 (font_main), scor2b, scor3b, kaufm020 (font_kaufm), indus030 ...
var font_main: Vfn
var font_kaufm: Vfn
var loop_player: AudioStreamPlayer   # channel 3 of the original: the recordings of the menu screens (dword_c721d)
var loop_name := ""
var loop_volume := 0x4c
var desk_toggle := false             # fe_desk_toggle: TONIGHTS.IFF and MAINDESK.IFF take turns on the desk
var loading_shown := false           # loading_shown
var db: Database
var games: GameScreens
var stats: StatsScreens
var settings: SettingsScreens
var game: Node = null               # view/Main.gd while a game is on (the pause screen's callbacks use it)
var last_sim: Sim = null            # the simulation of the last game played to its end (the league records it)
var leagues: LeagueScreens
var intro: IntroScreens
var music: MusicPlayer = null        # the FM songs of the front end (the title song of the intro and the credits)
var announcer: Announcer = null      # the announcer's sentences of the screens (XBRUCE2.VIV)
var nhl_intro_pending := true        # dword_c588a: the title's "NHL.INT" not said yet

func _ready() -> void:
	layer = CanvasLayer.new()
	layer.layer = 20
	add_child(layer)
	scr = Screen8.new()
	layer.add_child(scr)
	ui = Ui.new()
	add_child(ui)
	ui.setup(scr, bank("pointer3"))
	if ui.pointer.texture == null:
		_fallback_pointer()
	for n in ["s1", "scor2b", "scor3b", "kaufm020", "indus030", "hilight", "wittle06", "teeny05", "helve025", "minifo05", "insig015", "ftimes24", "camouf39", "easn", "linedit"]:
		var data := GameFiles.read(n + ".vfn")
		if not data.is_empty():
			fonts[n] = Vfn.parse(data)
	font_main = fonts.get("s1", null)
	font_kaufm = fonts.get("kaufm020", font_main)
	scr.setfont(font_main)
	loop_player = AudioStreamPlayer.new()
	add_child(loop_player)
	db = Database.open(GameFiles.read_raw("teams.db"), GameFiles.read_raw("key.db"), GameFiles.read_raw("att.db"))
	games = GameScreens.new(self)
	stats = StatsScreens.new(self)
	settings = SettingsScreens.new(self)
	leagues = LeagueScreens.new(self)
	intro = IntroScreens.new(self)

## the mouse pointer of POINTER3.QFS (on the CD only): without it an arrow of the same size
func _fallback_pointer() -> void:
	var rows := ["X", "XX", "X.X", "X..X", "X...X", "X....X", "X.....X", "X......X", "X.......X", "X........X",
		"X.....XXXXX", "X..X..X", "X.X X..X", "XX  X..X", "X    X..X", "     X..X", "      XX"]
	var img := Image.create(12, 18, false, Image.FORMAT_RGBA8)
	for y in rows.size():
		var r: String = rows[y]
		for x in r.length():
			if r[x] == "X":
				img.set_pixel(x, y, Color.BLACK)
			elif r[x] == ".":
				img.set_pixel(x, y, Color.WHITE)
	ui.pointer.texture = ImageTexture.create_from_image(img)
	ui.pointer.material = null

func show_screen(on: bool) -> void:
	layer.visible = on
	ui.active = on
	if on:
		get_window().content_scale_size = Vector2i(640, 480)

# ---------------------------------------------------------------------------------------------
# assets
# ---------------------------------------------------------------------------------------------

func bank(name: String) -> Shpi:
	var data := GameFiles.read_bank(name)
	return Shpi.parse(data) if not data.is_empty() else null

## loadsound + playsample(.., channel 3, volume): the recording of a menu screen, looped as stored.
## With the Sound Blaster it plays on voice 3 of the digital driver's mixer (the packed 22050 Hz
## recording stepped by 2 at 11025 Hz), else (no card model) on a player of its own
func play_loop(name: String, volume: int = 0x4c) -> void:
	if not Session.sound_enabled:
		return
	if loop_playing() and loop_name == name:
		return
	stop_loop()
	var stream := Sounds.load_sample(GameFiles.read_raw(name + ".iff"))
	loop_name = name
	if stream == null:
		return
	loop_volume = volume
	if Session.option_flags & 0x40 == 0:
		return
	var m := fm_music()
	if m != null and m.digital():
		var looped := stream.loop_mode == AudioStreamWAV.LOOP_FORWARD
		m.play_sample(3, stream.data, stream.mix_rate, volume, stream.loop_begin if looped else 0,
			stream.loop_end - stream.loop_begin if looped else 0)
		return
	loop_player.stream = stream
	loop_player.volume_db = linear_to_db(volume / 127.0)
	loop_player.play()

## the recording still plays (sound_channel_status of channel 3)
func loop_playing() -> bool:
	if music != null and music.digital():
		return not music.sample_done(3)
	return loop_player.playing

## sound_fade(channel 3, speed) and the wait for the channel (sound_channel_status) before the
## sample is released: the fade takes `ticks` of the 100 Hz timer
func fade_loop(ticks: int = 100) -> void:
	var tw := start_fade_loop(ticks)
	if tw != null:
		await tw.finished

## sound_fade without waiting: the tween of the fade (null when nothing plays)
func start_fade_loop(ticks: int = 100) -> Tween:
	if not loop_playing():
		loop_name = ""
		return null
	var tw := create_tween()
	if music != null and music.digital():
		var m := music
		tw.tween_method(func(v: float) -> void: m.dac.mix_volume(3, int(v)), float(loop_volume), 0.0, ticks / 100.0)
		tw.tween_callback(func() -> void: m.stop_sample(3))
	else:
		tw.tween_property(loop_player, "volume_db", -60.0, ticks / 100.0)
		tw.tween_callback(loop_player.stop)
	loop_name = ""
	return tw

func stop_loop() -> void:
	loop_player.stop()
	if music != null and music.digital():
		music.stop_sample(3)
	loop_name = ""

## the sound card of the front end (load_sound_config with the card of NHL.CFG): the title song of
## the intro and the credits
func fm_music() -> MusicPlayer:
	if music == null:
		music = MusicPlayer.new()
		add_child(music)
		music.setup_card(Session.sound_device, func(n: String) -> PackedByteArray: return GameFiles.read_raw(n))
	return music

## music_load_kms + play_sample_by_ptr: a song (the title song ADTITLE / MTTITLE) when the music is on
func play_song(name: String) -> void:
	if Session.option_flags & 0x40 == 0:
		return
	var m := fm_music()
	if m != null:
		m.play_song(name)

## a page of the awards (NHL_AWARDS_PAGE: 0..10 the awards, 11 the summary) over the game's TEAMS.DB
## and KEY.DB with a season of random numbers and play-off wins (NHL_UI_SCRIPT
## call:awards_preview, for screenshots)
func awards_preview() -> int:
	var rng := RandomNumberGenerator.new()
	rng.seed = 7
	var teams := GameFiles.read_raw("teams.db")
	var key := GameFiles.read_raw("key.db")
	var season := GameFiles.read_raw("season.db")
	for k in key.size() / 0x34:
		var at := key.decode_s32(k * 0x34 + 0x2c)
		var size := 0x36 if key[k * 0x34 + 2] == 0x47 else 0x2f
		if at < 0 or at + size > season.size():
			continue
		for o in range(0, size - 1, 2):
			season.encode_u16(at + o, rng.randi_range(0, 30 if o < 0x24 else 3))
		season.encode_u16(at + 0x10, rng.randi_range(0, 400) if size == 0x36 else rng.randi_range(0, 60))
		season[at + 0x2e] = rng.randi_range(0, 1) if size == 0x2f else season[at + 0x2e]
	for t in 26:
		for o in [0x29, 0x2a, 0x2b, 0x3b]:
			teams[t * 0x2e8 + o] = rng.randi_range(0, 40)
	scr.setfont(font_kaufm)
	var a := AwardsScreen.new(self)
	Awards.load(teams, key, season)
	var n := int(OS.get_environment("NHL_AWARDS_PAGE"))
	var pal := a.page(n) if n < 11 else a.summary(bank("awardsi"))
	await scr.fade_in(pal, 16)
	return 0

## the league's Hilights over a reel made here (NHL_UI_SCRIPT call:highlights_preview, for
## screenshots): Boston - Montreal played for 1500 steps, its replay saved twice to BOS.HI and once
## to MTL.HI in user://hl_preview
func highlights_preview() -> int:
	var d := Database.open(GameFiles.read_raw("teams.db"), GameFiles.read_raw("key.db"), GameFiles.read_raw("att.db"))
	var sim := Sim.new()
	sim.set_teams(d.load_team(0), d.load_team(9))
	for i in 1500:
		sim.step(8, 8, 0, 0)
	DirAccess.make_dir_recursive_absolute("user://hl_preview")
	var rec := HighlightReel.record(sim, 0, 9, 11, 4)
	for n: String in ["BOS", "BOS", "MTL"]:
		var path := "user://hl_preview".path_join(n + ".HI")
		var f := FileAccess.open(path, FileAccess.READ_WRITE) if FileAccess.file_exists(path) else FileAccess.open(path, FileAccess.WRITE)
		f.seek_end()
		f.store_buffer(rec)
		f.close()
	var l := League.new()
	l.dir = "user://hl_preview"
	Session.league = l
	Session.mode = 2
	await leagues.highlights_flow()
	for n in ["BOS.HI", "MTL.HI"]:
		DirAccess.remove_absolute("user://hl_preview".path_join(n))
	return 0

## Trade Players ... of a new league with Boston and Montreal played by people (NHL_UI_SCRIPT
## call:trade_preview, for screenshots); the league is deleted afterwards
func trade_preview() -> int:
	var src := {}
	for n: String in League.FILES:
		src[n] = GameFiles.read_raw(n.to_lower() + ".db")
	var l := League.create("TRADEPV", src, [0, 9], false)
	l.save()
	Session.league = l
	Session.mode = 2
	await leagues.league_trade_players()
	League.delete("TRADEPV")
	Session.league = null
	return 0

## the song still plays (kms_finished)
func song_playing() -> bool:
	return music != null and music.song_playing()

## stop_crowd_loop + kms_unload
func stop_song() -> void:
	if music != null:
		music.stop_song()

## say_goodnight (0x59c3e): the announcer's GOODNITE.INT
func say_goodnight() -> void:
	say_clip("goodnite.int")

## a clip of the announcer (speech_say_clip) with sound and speech on (option_flags 0x100)
func say_clip(clip: String) -> void:
	say(PackedStringArray([clip]))

## a sentence of the announcer (speech_play_sentence) with sound and speech on: its clips one
## after the other, a new sentence interrupts the last (Speech.gd builds them)
func say(clips: PackedStringArray) -> void:
	if not Session.sound_enabled or Session.option_flags & 0x100 == 0:
		return
	if announcer == null:
		announcer = Announcer.new()
		add_child(announcer)
		announcer.setup(null, Viv.parse(GameFiles.read_raw("xbruce2.viv")))
	announcer.say(clips)

## speech_stop: the sentence being said ends
func speech_stop() -> void:
	if announcer != null:
		announcer.stop()


## the screen fades to black with the recording (the usual way out of a screen)
func leave_screen(ticks: int = 100) -> void:
	var tw := start_fade_loop(ticks)
	await scr.fade_out(16)
	if tw != null and tw.is_running():
		await tw.finished

# ---------------------------------------------------------------------------------------------
# main (0x10094) and the desk
# ---------------------------------------------------------------------------------------------

## main after initgraphics: the settings of GAME.SET (or the defaults of the executable), the
## loading screen, the desk; credits_screen on the way out
func run() -> void:
	show_screen(true)
	scr.black()
	load_nhl_cfg()
	if IntroScreens.intro_wanted():
		await intro.intro_sequence()
	var set_file := FileAccess.get_file_as_bytes("user://GAME.SET")
	Session.apply_block(set_file if set_file.size() >= Session.SETTINGS_SIZE else Session.default_block())
	League.srand_clock()
	if set_file.size() < Session.SETTINGS_SIZE:
		# main without GAME.SET: player 1 gets the best controller and the home team
		Session.p1_device = 8
		Session.p2_device = 0x10
		Session.p1_side = 0
		Session.p2_side = 1
		Session.p1_team = Session.home_team
		Session.p2_team = -2
	await loading_screen()
	await frontend_main_menu()
	await leave_screen(100)
	await quit_program()

## the end of main (and of exit_game_dialog): the loading screen, credits_screen, back to DOS
func quit_program() -> void:
	loading_shown = false
	await loading_screen()
	await intro.credits_screen()
	app.quit()

## loading_screen (0x47a9c..): LOAD.QFS "load" at (100, 75), its palette brought up from black
## while three rotated copies of colours 1..0x8f cycle every 4 ticks (loading_screen_timer)
func loading_screen(min_ticks: int = 60) -> void:
	if loading_shown:
		return
	await scr.fade_out(8)
	scr.clearclip()
	scr.clear(0)
	var b := bank("load")
	if b == null:
		return
	var pal := Screen8.shape_palette(b.find("!pal"))
	var pals: Array = [pal, pal.duplicate(), pal.duplicate()]
	for i in range(1, 0x90):
		var j := i + 0x2f if i < 0x60 else i - 0x5f
		var k := i + 0x60 if i < 0x30 else i - 0x2f
		for c in 3:
			pals[1][i * 3 + c] = pal[j * 3 + c]
			pals[2][i * 3 + c] = pal[k * 3 + c]
	scr.drawshape(b.find("load"), 100, 0x4b)
	scr.black()
	# the three palettes (unk_de26c) rise together by one step every 2 ticks; the timer shows
	# one of them after the other every 4 ticks
	var shown: Array = []
	for k in 3:
		var z := PackedByteArray()
		z.resize(768)
		shown.append(z)
	var t := 0.0
	var done := false
	while not done or t * 100.0 < min_ticks:
		done = true
		for k in 3:
			var cur: PackedByteArray = pals[k]
			var sh: PackedByteArray = shown[k]
			for i in 768:
				if sh[i] < cur[i]:
					sh[i] += 1
					done = false
			shown[k] = sh
		var phase := int(t * 25.0) % 3
		scr.setpalette(shown[phase])
		await get_tree().process_frame
		t += get_process_delta_time()
	loading_shown = true

## frontend_main_menu (0x31ab5): EASNDESK.QFS, the menu bar of 0xce3af, TONIGHTS.IFF and
## MAINDESK.IFF in turns; a callback returning 2 draws the desk again, 1 leaves (Exit)
func frontend_main_menu() -> void:
	set_hub_title(0)
	Menus.at(0xce7ef).text = _game_label()
	await draw_desk()
	await ui.run_menu(Menus.list(0xce3af, 3), LIGHT, FACE, DARK, dispatch, draw_desk)
	ui.show_pointer(false)

## the desk drawn again after a screen (the recording changes)
func draw_desk() -> void:
	loading_shown = false
	if loop_playing():
		await fade_loop(70)
	desk_toggle = not desk_toggle
	play_loop("tonights" if desk_toggle else "maindesk")
	scr.clearclip()
	var b := bank("easndesk")
	scr.black()
	if b != null:
		scr.drawshape_home(b.find("desk"))
	scr.setfont(font_main)
	ui.draw_menu_items(Menus.list(0xce3af, 3), LIGHT, FACE, DARK)
	Menus.at(0xce7ef).text = _game_label()
	await scr.fade_in(Screen8.shape_palette(b.find("!pal")) if b != null else _grey_palette(), 16)

static func _grey_palette() -> PackedByteArray:
	var p := PackedByteArray()
	p.resize(768)
	for i in 256:
		for c in 3:
			p[i * 3 + c] = i >> 2
	return p

## "Game: LA  at MTL ..." (aGameLAAtMTL, apply_settings / locker_room_menu): the two abbreviations
func _game_label() -> String:
	var away := Tables.team_abbrev[Session.away_team] if Session.away_team < Tables.team_abbrev.size() else "?"
	var home := Tables.team_abbrev[Session.home_team] if Session.home_team < Tables.team_abbrev.size() else "?"
	return "Game: %s at %s ..." % [away.rpad(3), home.rpad(3)]

## set_hub_title (0x1d610): the "Return To" entries of the statistics screens name the screen
## that opened them
func set_hub_title(which: int) -> void:
	var titles := ["Sports Central", "Playoff Tree", "League Calendar", "Broadcast Booth", "Intermission Desk", "Rink Side"]
	var widths := [0x67, 0x59, 0x76, 0x73, 0x7e, 0x41]
	var t: String = titles[clampi(which, 0, 5)]
	var w: int = widths[clampi(which, 0, 5)]
	for a in [0xcf50f, 0xcf5cf, 0xcf60f, 0xcf66f]:
		var it := Menus.at(a)
		if it != null:
			it.text = t
	for a in [0xcf50f, 0xcf5cf]:
		var it := Menus.at(a)
		if it != null:
			it.x1 = w
	for a in [0xcf5ef, 0xcf60f, 0xcf62f, 0xcf64f, 0xcf66f]:
		var it := Menus.at(a)
		if it != null:
			it.x1 = maxi(w, 0x7d)

## run_menu's callback: the method of the same name (1 leaves the menu, 2 redraws the screen)
func dispatch(cb: String):
	for target in [self, games, stats, settings, leagues, intro]:
		if target != null and target.has_method(cb):
			var r = await target.call(cb)
			return r if r is int else 0
	await message_dialog(["This part of the front end", "(%s)" % cb, "is not available yet."], ["OK"])
	return 0

## menu_exit (0x3270b)
func menu_exit() -> int:
	return 1

# ---------------------------------------------------------------------------------------------
# dialogs (message_dialog 0x31013, dialog_pointer_loop 0x31250, button_draw 0x30b16)
# ---------------------------------------------------------------------------------------------

var dlg_face := 0xf9                 # set_dialog_colors: dword_c71cc face, c71d0 light, c71d4 dark,
var dlg_light := 0xfa                # c71d8 text, c71dc text shadow
var dlg_dark := 0xf8
var dlg_text := 0xfa
var dlg_shadow := 0xf7

func set_dialog_colors(face: int, light: int, dark: int, text: int, shadow: int) -> void:
	dlg_face = face
	dlg_light = light
	dlg_dark = dark
	dlg_text = text
	dlg_shadow = shadow

## draw_dialog_frame (0x2fe49): filled, light top and left edges, dark bottom and right
func draw_dialog_frame(x: int, y: int, w: int, h: int, face: int, light: int, dark: int) -> void:
	scr.fillrect(x, y, w, h, face)
	scr.drawline(x, y, x, y + h - 1, light)
	scr.drawline(x, y, x + w - 1, y, light)
	scr.drawline(x, y + h - 1, x + w - 1, y + h - 1, dark)
	scr.drawline(x + w - 1, y, x + w - 1, y + h - 1, dark)

## draw_bevel_box (0x29d00): the dialog colours, corners with dots when `dots`
func draw_bevel_box(x0: int, y0: int, x1: int, y1: int, dots: bool) -> void:
	scr.fillrect(x0, y0, x1 - x0 + 1, y1 - y0 + 1, dlg_face)
	scr.drawline(x0, y0, x1, y0, dlg_light)
	scr.drawline(x0, y0, x0, y1, dlg_light)
	scr.drawline(x1, y0, x1, y1, dlg_dark)
	scr.drawline(x0, y1, x1, y1, dlg_dark)
	if dots:
		for c in [[x0 + 2, y0 + 2], [x0 + 2, y1 - 3], [x1 - 3, y0 + 2], [x1 - 3, y1 - 3]]:
			scr.putpixel(c[0], c[1], dlg_light)
			scr.putpixel(c[0] + 1, c[1] + 1, dlg_light)
			scr.putpixel(c[0] + 1, c[1], dlg_dark)
			scr.putpixel(c[0], c[1] + 1, dlg_dark)

## a button record (0x1c bytes): x, y, w, h, pressed, flags (1: x from the left edge, 4: y from the
## top edge of the dialog), text
class UiButton:
	var x: int
	var y: int
	var w: int
	var h: int
	var pressed := false
	var flags := 5
	var text: String
	func _init(bx: int, by: int, bw: int, bh: int, t: String, f: int = 5) -> void:
		x = bx
		y = by
		w = bw
		h = bh
		text = t
		flags = f

## the button records of the executable: count records of 0x1c bytes at addr
static func buttons_at(addr: int, count: int) -> Array:
	var out: Array = []
	for i in count:
		var a := addr + i * 0x1c
		out.append(UiButton.new(Exe.i32(a), Exe.i32(a + 4), Exe.i32(a + 8), Exe.i32(a + 12), Exe.str_ptr(a + 0x18), Exe.i32(a + 0x14)))
	return out

## button_draw (0x30b16): a frame (light and dark swapped while pressed), the text centred
func button_draw(b: UiButton) -> void:
	var light := dlg_dark if b.pressed else dlg_light
	var dark := dlg_light if b.pressed else dlg_dark
	draw_dialog_frame(b.x, b.y, b.w, b.h, dlg_face, light, dark)
	if b.text != "":
		scr.set_text_colors(dlg_text, dlg_shadow)
		scr.print_text_at((b.w - scr.textwidth(b.text)) / 2 + b.x, b.y + (b.h - scr.font_height()) / 2, b.text)

func buttons_draw_all(list: Array) -> void:
	for b: UiButton in list:
		b.pressed = false
		button_draw(b)

## button_at (0x30a39): the button under (x, y) for a release (2) / press (1); -1 none
func button_at(list: Array, x: int, y: int, buttons: int) -> int:
	var hit := -1
	for i in list.size():
		var b: UiButton = list[i]
		var inside: bool = x >= b.x and x < b.x + b.w and y >= b.y and y < b.y + b.h
		if inside:
			if not b.pressed and buttons & 1:
				b.pressed = true
				button_draw(b)
			if buttons & 2:
				hit = i
				b.pressed = false
				button_draw(b)
		elif b.pressed:
			b.pressed = false
			button_draw(b)
	return hit

## dialog_pointer_loop (0x31250): waits for a click on a button (its index), Esc gives -1; without
## buttons any button or key ends it
func dialog_pointer_loop(list: Array) -> int:
	ui.show_pointer(true)
	ui.reset_events()
	while true:
		var e: Dictionary = await ui.wait_event()
		var bt: int = e["buttons"]
		if bt & 0x2f == 0:
			continue
		if list.is_empty():
			if bt & 0x2e:
				return 4 if bt & 4 else -1
			continue
		if bt & 4:
			return -1
		var k := button_at(list, e["x"], e["y"], bt)
		if k >= 0:
			return k
	return -1

## message_dialog (0x31013) with simple buttons: labels laid out from the left (the last one from
## the right edge) like the button records of the original dialogs
func message_dialog(lines: Array, labels: Array = ["OK"], x: int = -1, y: int = -1) -> int:
	var list: Array = []
	var lh := scr.font_height() + 2
	var by := lines.size() * lh + 0x10
	var bx := 16
	for i in labels.size():
		var w := maxi(scr.textwidth(labels[i]) + 16, 40)
		if i == labels.size() - 1 and labels.size() > 1:
			list.append(UiButton.new(-16, by, w, 20, labels[i], 6))
		else:
			list.append(UiButton.new(bx, by, w, 20, labels[i], 5))
			bx += w + 16
	return await message_dialog_buttons(lines, list, x, y)

## message_dialog (0x31013): the lines centred in a box sized to them and to the buttons
## (dialog_measure_line, dialog_buttons_layout); a button record's x counts from the left edge of
## the box with flag 1 (else from the right edge), its y from the top with flag 4 (else from the
## bottom). Returns the button chosen (-1 Esc); the screen behind is restored.
func message_dialog_buttons(lines: Array, list: Array, x: int = -1, y: int = -1) -> int:
	var lh := scr.font_height() + 2
	var w := 0
	var h := 0
	for l in lines:
		w = maxi(w, scr.textwidth(l))
		h += lh
	w += 0x10
	h += 0x10
	var acc := 0
	for b: UiButton in list:
		acc += (b.x + b.w if b.flags & 1 else b.w - b.x) + 8
		w = maxi(w, acc)
		h = maxi(h, (b.y + b.h if b.flags & 4 else b.h - b.y) + 8)
	if x < 0:
		x = (640 - w) / 2
	if y < 0:
		y = (480 - h) / 2
	var behind := scr.snapshot()
	draw_dialog_frame(x, y, w, h, dlg_face, dlg_light, dlg_dark)
	scr.set_text_colors(dlg_text, dlg_shadow)
	var ty := y + 8
	for l in lines:
		scr.print_text_at((w - scr.textwidth(l)) / 2 + x, ty, l)
		ty += lh
	var placed: Array = []
	for b: UiButton in list:
		var p := UiButton.new(b.x + x if b.flags & 1 else b.x + x + w - b.w, b.y + y if b.flags & 4 else b.y + y + h - b.h, b.w, b.h, b.text, b.flags)
		placed.append(p)
	buttons_draw_all(placed)
	var r := await dialog_pointer_loop(placed)
	scr.restore(behind)
	ui.show_pointer(false)
	return r

## listbox_dialog (0x303fb): the items in a box under the title, up to 20 rows (a scroll bar on the
## right for more: scrollbar_init / scrollbar_draw / scrollbar_at), each row filled with the text
## shadow colour (the chosen one with the text colour, a marked one of a multiple choice with the
## face colour) and its text left (0), right (1) or centred (2). A click chooses a row (the first
## is chosen at the start, none with `multi`), a click on the chosen row again ends it (with
## `multi` it marks and unmarks rows in `marks`, and ends on a marked one). Returns the row.
func listbox_dialog(items: Array, title: String, align: int, multi: bool = false,
		marks: PackedByteArray = PackedByteArray()) -> int:
	var count := items.size()
	var rows := mini(count, 0x14)
	var tw := scr.textwidth(title)
	var w := tw
	for t: String in items:
		w = maxi(w, scr.textwidth(t))
	w += 9
	var lh := (scr.font_height() + 2) * rows + 4
	var x := (0x280 - w - 0x10) / 2
	var y := (0x1e0 - lh - 0x20) / 2
	var bw := w + 0x10
	var bh := lh + 0x20
	var lx := x + 8
	var ly := y + 0x18
	var bar := {}
	var behind := scr.snapshot()
	if count > rows:
		lx -= 10
		x -= 10
		bar = {"x": x + bw, "y": y, "w": 10, "h": bh, "ty": 0, "th": (bh - 4) * rows / count, "top": 0,
			"total": count, "pressed": false}
		_scrollbar_draw(bar)
	draw_dialog_frame(x, y, bw, bh, dlg_face, dlg_light, dlg_dark)
	scr.set_text_colors(dlg_text, dlg_shadow)
	scr.print_text_at((bw - tw) / 2 + x, y + 6, title)
	draw_dialog_frame(lx, ly, w, lh, dlg_shadow, dlg_dark, dlg_light)
	var sel := -1 if multi else 0
	var top := 0
	for i in rows:
		_listbox_draw_item(items, lx, ly, w, top, top + i, sel, align, multi, marks)
	ui.show_pointer(true)
	ui.reset_events()
	var done := false
	while not done:
		var e: Dictionary = await ui.wait_event()
		var bt: int = e["buttons"]
		if bt == 0:
			continue
		if bt & 2:
			var row := _listbox_item_at(e["x"], e["y"], lx, ly, w, rows)
			if row >= 0:
				var prev := sel
				sel = top + row
				if multi and (sel != prev or marks[sel] == 0):
					marks[sel] = ~marks[sel] & 0xff
				if prev >= 0 and prev >= top and prev < top + rows:
					_listbox_draw_item(items, lx, ly, w, top, prev, sel, align, multi, marks)
				_listbox_draw_item(items, lx, ly, w, top, sel, sel, align, multi, marks)
				if sel == prev and (not multi or marks[sel] != 0):
					done = true
		if not bar.is_empty() and _scrollbar_at(bar, e["x"], e["y"], bt) and top != bar["top"]:
			top = bar["top"]
			for i in rows:
				_listbox_draw_item(items, lx, ly, w, top, top + i, sel, align, multi, marks)
	scr.restore(behind)
	ui.show_pointer(false)
	return sel

## listbox_draw_item (0x302b9)
func _listbox_draw_item(items: Array, lx: int, ly: int, w: int, top: int, index: int, sel: int, align: int,
		multi: bool, marks: PackedByteArray) -> void:
	var h := scr.font_height()
	var iy := ly + (index - top) * (h + 2) + 2
	var ix := lx + 2
	var iw := w - 4
	var col := dlg_shadow
	if multi and marks[index] != 0:
		col = dlg_face
	elif index == sel:
		col = dlg_text
	scr.fillrect(ix, iy, iw, h + 2, col)
	var text: String = items[index]
	text = text.left(0x4f)
	if align == 1:
		ix += iw - scr.textwidth(text) - 4
	elif align == 2:
		ix += (iw - scr.textwidth(text)) / 2
	scr.print_text_at(ix, iy + 1, text)

## listbox_item_at (0x3023e): the row under (x, y), -1 none (a row's last line is the next one's first)
func _listbox_item_at(x: int, y: int, lx: int, ly: int, w: int, rows: int) -> int:
	var h := scr.font_height()
	for i in rows:
		var t := (h + 2) * i + ly + 2
		if x >= lx + 2 and x <= lx + w - 2 and y >= t and y <= t + h + 2:
			return i
	return -1

## scrollbar_draw (0x30c3d): the track, the thumb (pressed: its edges swapped)
func _scrollbar_draw(b: Dictionary) -> void:
	draw_dialog_frame(b["x"], b["y"], b["w"], b["h"], dlg_face, dlg_light, dlg_dark)
	var light := dlg_dark if b["pressed"] else dlg_light
	var dark := dlg_light if b["pressed"] else dlg_dark
	draw_dialog_frame(b["x"] + 2, b["y"] + b["ty"] + 2, b["w"] - 4, b["th"], dlg_face, light, dark)

## scrollbar_at (0x30d0e): a press or a release on the bar puts the thumb's middle at the pointer
## (kept inside the track) and the first row where it points; true when the pointer is on the bar
func _scrollbar_at(b: Dictionary, x: int, y: int, buttons: int) -> bool:
	if x >= b["x"] and x < b["x"] + b["w"] and y >= b["y"] and y < b["y"] + b["h"]:
		var prev: int = b["ty"]
		if buttons & 1 and not b["pressed"]:
			b["pressed"] = true
			prev = -1
		if buttons & 2:
			b["pressed"] = false
			prev = -1
		var ty: int = y - b["y"] - b["th"] / 2
		if ty < 0:
			ty = 0
		elif ty > b["h"] - b["th"] - 4:
			ty = b["h"] - b["th"] - 4
		b["ty"] = ty
		b["top"] = ty * b["total"] / (b["h"] - 4)
		if prev != ty:
			_scrollbar_draw(b)
		return true
	if b["pressed"]:
		b["pressed"] = false
		_scrollbar_draw(b)
	return false

## the NO / YES buttons of the confirmation dialogs (unk_d2b38)
func yes_no_dialog(lines: Array) -> bool:
	set_dialog_colors(0xf9, 0xfa, 0xf8, 0xfa, 0)
	return await message_dialog_buttons(lines, buttons_at(0xd2b38, 2)) > 0

# ---------------------------------------------------------------------------------------------
# a game: play_game and the screens the match comes back for
# ---------------------------------------------------------------------------------------------

## GAME.SET: the settings block (save_settings) written when the settings change
func save_game_set() -> void:
	var f := FileAccess.open("user://GAME.SET", FileAccess.WRITE)
	if f != null:
		f.store_buffer(Session.save_block())

## play_game (0x11d09): the match with the teams, users and options of the session
func play_game(db_override: Database = null, restore: Dictionary = {}) -> int:
	await leave_screen(100)
	last_sim = null
	var setup := {
		"db": db_override,
		"restore": restore,
		"home": Session.home_team, "away": Session.away_team,
		"user1": Session.user_side(0), "user2": Session.user_side(1),
		"option_flags": Session.option_flags,
		"period_length": Session.period_seconds(1),
		"anthem": true,
		"lines": Session.line_override.duplicate(),
		"scratches": Session.scratches.duplicate(),
		"cup_series": _cup_series(),
		"series_mode": Session.mode == 1,
		"league_game": Session.mode != 0,
		"season_db": _league_db("SEASON"),
		"career_db": _league_db("CAREER"),
	}
	var r: int = await app.play_match_async(setup)
	game = null
	return r

## highlights_play (0x8011c): a record of a highlights reel replayed on the ice of its teams (their
## colours, the home team's rink, the league's rosters), the VCR on it until its exit
func play_saved_highlight(rec: PackedByteArray) -> void:
	await leave_screen(100)
	var lg = Session.league
	var db: Database = null
	if lg != null:
		db = Database.open((lg as League).file("TEAMS"), (lg as League).file("KEY"), (lg as League).file("ATT"))
	var setup := {
		"db": db, "home": rec[2], "away": rec[0x1f], "user1": 0, "user2": 0,
		"option_flags": Session.option_flags, "anthem": false,
		"series_mode": Session.mode == 1, "league_game": Session.mode != 0,
		"saved_highlight": rec,
	}
	await app.play_match_async(setup)
	game = null

## SEASON.DB / CAREER.DB of the game's databases (the league's, else the game's own): the records
## before the game the goal panel and the milestones read (db_load_team_roster)
func _league_db(n: String) -> PackedByteArray:
	var lg = Session.league
	if lg != null:
		var d: PackedByteArray = (lg as League).file(n)
		if not d.is_empty():
			return d
	return GameFiles.read_raw(n.to_lower() + ".db")

## alloc_cup_banner (0x15b76): a game of the play-off final keeps the final's 7 games of the
## schedule (game_over_check: does this game win the Stanley Cup)
func _cup_series() -> PackedByteArray:
	var lg = Session.league
	if lg == null or Session.game_number < League.SEASON_GAMES + 14 * 7 or Session.game_number >= League.ALL_GAMES:
		return PackedByteArray()
	return (lg as League)._playoffs().slice(14 * 42, 15 * 42)

## pause_menu (0x1935d): EADESK%d.QFS (0 paused, 1 intermission, 2 after the game) with the menu
## bar of 0xceb8f (after the game 0xcec4f). 1 back to the game, 2 the game is left (Sports Desk),
## 7 the instant replay (menu_go_to_replay)
func pause_menu(variant: int, m: Node) -> int:
	game = m
	set_pause_menu_labels(Session.mode)
	set_hub_title(variant + 3)
	Menus.at(0xcef0f).cb = "menu_go_to_replay" if m != null and m.sim.replay.frame_count() > 0 else ""
	games.set_goalie_menu_labels()
	var desk := bank("eadesk%d" % variant)
	var pal := Screen8.shape_palette(desk.find("!pal")) if desk != null else _grey_palette()
	await scr.fade_out(16)
	scr.clearclip()
	if desk != null:
		scr.drawshape_home(desk.find("desk"))
	scr.setfont(font_main)
	var root := Menus.list(0xcec4f, 3) if variant == 2 else Menus.list(0xceb8f, 6)
	ui.draw_menu_items(root, LIGHT, FACE, DARK)
	play_loop("pause")
	await scr.fade_in(pal, 16)
	if variant == 2 and Session.game_number >= League.SEASON_GAMES and m != null:
		# say_series_result: the winner of the game (the visitors on a tie), the series' game
		var sim: Sim = m.sim
		var h: int = sim.team_ids[0]
		var a: int = sim.team_ids[1]
		var winner := h if sim.teams[0].goals > sim.teams[1].goals else a
		say(Speech.series_result(Tables.team_abbrev[winner], (Session.game_number - League.SEASON_GAMES) % 7 + 1,
			Speech.playoff_conference(h, a), Speech.playoff_game_round(Session.game_number), sim.period_num > 3, sim.series_announce))
		sim.series_announce = false
	var redraw := func() -> void:
		await scr.fade_out(16)
		if desk != null:
			scr.drawshape_home(desk.find("desk"))
		ui.draw_menu_items(root, LIGHT, FACE, DARK)
		await scr.fade_in(pal, 16)
	# an intermission of a game without users goes on by itself after 15 seconds (0x5dc ticks)
	var auto := variant == 1 and Session.p1_team < 0 and Session.p2_team < 0
	var t0 := Time.get_ticks_msec()
	var idle := func():
		if auto and Time.get_ticks_msec() - t0 > 15000:
			return 1
		return 0
	var code := await ui.run_menu(root, LIGHT, FACE, DARK, dispatch, redraw, [1, 5, 7], idle)
	ui.show_pointer(false)
	await leave_screen(100)
	if code == 5:
		return 2
	return code

## set_pause_menu_labels (0x805c4): "Exhibition Settings ...", "Playoff Settings ..." or "Show League
## Settings ..."; the Sports Desk entries name the screen they return to
func set_pause_menu_labels(m: int) -> void:
	var it := Menus.at(0xcee2f)
	var desk1 := Menus.at(0xcecef)
	var desk2 := Menus.at(0xced2f)
	match m:
		0:
			it.text = "Exhibition Settings ..."
			desk1.text = "Sports Central"
			desk2.text = "Sports Central"
		1:
			it.text = "Playoff Settings ..."
			desk1.text = "Playoff Tree"
			desk2.text = "Playoff Tree"
		2:
			it.text = "Show League Settings ..."
			desk1.text = "Return"
			desk2.text = "Return"

## the game summary of the game on the ice written to GSUMMARY.DB (gsummary_flush,
## gsummary_write_header)
func write_summary(m: Node) -> void:
	if m != null and not m.sim.no_stats:
		GameFiles.write_data("gsummary.db", m.sim.summary_bytes())

## the scores around the league are followed in exhibitions without the all star teams
func _league_scores_on(m: Node) -> bool:
	if Session.mode != 0 or m == null:
		return false
	for t in 2:
		var info: Database.TeamInfo = m.sim.teams[t].info
		if info != null and info.index >= 0x1a:
			return false
	return true

## end_match_from_period (0x190be): the box score of the period, a highlight of another game and the
## scores around the league (started after the 1st period), then the intermission desk
func intermission(m: Node, period_done: int) -> int:
	game = m
	write_summary(m)
	var period := period_done + 1
	var r := await games.boxscore_screen(1, period, period)
	if _league_scores_on(m):
		if period == 1:
			LeagueScores.init(m.sim.teams[0].info.index, m.sim.teams[1].info.index)
		if r & 4 == 0:
			LeagueScores.advance(period, m.sim.teams[0].info.index)
			if await simulate_pending(m) >= 0:
				await games.boxscore_screen(0x20, period, 0)
	return await pause_menu(1, m)

## simulate_pending_games (0x18f8d): a game around the league not shown to its end is picked
## (Highlight.pick) and a scene of it played on the ice (league_highlight_game, Main.play_highlight);
## its score goes to the scores around the league. -1 when the pause key ended the scene (the
## intermission skips the scores), 0 otherwise (also when every game was shown already)
func simulate_pending(m: Node) -> int:
	if LeagueScores.games.is_empty():
		return 0
	var pick := Highlight.pick(m.sim)
	if pick.is_empty():
		return 0
	var game: Array = LeagueScores.games[pick[0]]
	var res: Array = await m.play_highlight(game[0], game[1], [pick[1], pick[2]], pick[3])
	Highlight.finish(pick[0], res[1])
	return res[0]

## end_match_from_loop (0x1920f): the box score of the game, a highlight of another game and the
## final scores around the league (the coach's clip of the CD is missing), then pause_menu(2)
func game_end(m: Node) -> void:
	game = m
	last_sim = m.sim
	write_summary(m)
	var period: int = m.sim.period + 1
	var r := await games.boxscore_screen(1, 1, period)
	if _league_scores_on(m) and r & 4 == 0 and not LeagueScores.games.is_empty():
		LeagueScores.advance(period, m.sim.teams[0].info.index)
		await simulate_pending(m)
		await games.boxscore_screen(0x20, period, 0)
	var code := await pause_menu(2, m)
	game = null

## the line editor of a team before the game (the scouting report's buttons: edit_lines_screen_b
## with the menu of unk_cf1af), then the screen it came from again
func edit_lines_for(team: int, pal: PackedByteArray) -> void:
	var keep := scr.snapshot()
	var ed := LineEditor.new(self)
	await ed.edit(0 if team == Session.home_team else 1, 0xcf1af, 3)
	scr.restore(keep)
	await scr.fade_in(pal, 16)

## text_entry_dialog (0x2fedf): a prompt over a field of `maxlen` characters; Enter takes the text,
## Esc gives "" (the original returns 0x1b)
func text_entry_dialog(prompt: String, maxlen: int, initial: String = "") -> String:
	var lh := scr.font_height()
	var w := maxi(scr.textwidth(prompt), scr.textwidth("W".repeat(maxlen))) + 0x20
	var h := lh * 2 + 0x20
	var x := (640 - w) / 2
	var y := (480 - h) / 2
	var behind := scr.snapshot()
	draw_dialog_frame(x, y, w, h, dlg_face, dlg_light, dlg_dark)
	scr.set_text_colors(dlg_text, dlg_shadow)
	scr.print_text_at(x + (w - scr.textwidth(prompt)) / 2, y + 8, prompt)
	var fx := x + 0x10
	var fy := y + lh + 0x10
	var text := initial
	ui.reset_events()
	var done := false
	var ok := true
	while not done:
		draw_dialog_frame(fx - 2, fy - 2, w - 0x1c, lh + 4, dlg_face, dlg_dark, dlg_light)
		scr.set_text_colors(dlg_text, dlg_shadow)
		scr.print_text_at(fx, fy, text + "_")
		var e: Dictionary = await ui.wait_event()
		var bt: int = e["buttons"]
		if bt & 4:
			ok = false
			done = true
		elif bt & 2 and e["type"] == 3:
			done = true
		elif bt & 0x20:
			var k: int = e["key"]
			if k == KEY_BACKSPACE:
				text = text.left(maxi(text.length() - 1, 0))
			elif text.length() < maxlen and k > 0x20 and k < 0x7f:
				text += char(k)
	scr.restore(behind)
	return text if ok else ""

## load_nhl_cfg (0x8baaf): NHL.CFG (the copy of the port in user:// when the card was changed): the
## sound card as an index into the table at 0xd243a, the CD drive, the installed files
func load_nhl_cfg() -> void:
	var text := FileAccess.get_file_as_string("user://NHL.CFG")
	if text == "":
		text = GameFiles.read_raw("nhl.cfg").get_string_from_ascii()
	var lines := text.split("\n", false)
	if lines.size() > 0 and lines[0].strip_edges().is_valid_hex_number():
		var idx := lines[0].strip_edges().hex_to_int()
		var card := Exe.u8(0xd243a + idx) if idx >= 0 and idx < 6 else 2
		Session.sound_device = card if card != 0 else 2
	if lines.size() > 1:
		Session.cd_drive = lines[1].strip_edges()
	var inst := PackedStringArray()
	for i in range(2, lines.size()):
		inst.append(lines[i].strip_edges())
	Session.installed = inst
	Session.sound_enabled = Session.sound_device & 0x22 != 0

## NHL.CFG written again with the card chosen (sound_setup_screen)
func save_nhl_cfg() -> void:
	var idx := 3
	for i in 6:
		if Exe.u8(0xd243a + i) == Session.sound_device:
			idx = i
	var out := "%04x\n%s\n" % [idx, Session.cd_drive] + "\n".join(Session.installed) + "\n"
	var f := FileAccess.open("user://NHL.CFG", FileAccess.WRITE)
	if f != null:
		f.store_string(out)
