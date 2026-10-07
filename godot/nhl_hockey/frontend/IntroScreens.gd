class_name IntroScreens
extends RefCounted
## The beginning and the end of the program: intro_sequence (0x1672a) with the PIONEER PRODUCTIONS
## logo, the EA SPORTS screen (EAOPEN), the title (ea_sports_intro 0x15fe9) and the demo games
## between them (demo_game 0x15d6b), and credits_screen (0x16f9a) on the way out.
##
## The logos, the title video (TITLE.CMV), the background of the credits (CREDITS.QFS) and the
## photographs of the credits (CREDIT00..19.QFS) are on the CD only. What is missing is skipped: the
## loading screen with the title song stands in for the title, and the credits are drawn over the
## NHL emblem (EMBNHL) centred on the screen. The texts of the credits are in the executable.

var fe: FrontEnd
var scr: Screen8
var ui: Ui

const CREDIT_PAGES := 0xc6399        # off_c6399: the 0x1d pages of the credits
const CREDIT_PAGE_COUNT := 0x1d
const CREDIT_END := 0xc638c          # unk_c638c: the last page, empty
const DEMO_PAIRS := 0xc5861          # dword_c5860 + 1: 17 matchups (home, away) of the demo games
const DEMO_PERIOD := 0x3c            # word_cbc4a during demo_game: a period of 60 seconds

static var demo_kind := 0            # demo_kind: 0 two teams at random, 1 a matchup, 2 the all-stars

func _init(f: FrontEnd) -> void:
	fe = f
	scr = f.scr
	ui = f.ui

## NHL_NO_INTRO=1 skips the intro; NHL_UI_SCRIPT runs start at the desk unless NHL_INTRO=1
static func intro_wanted() -> bool:
	if OS.has_environment("NHL_UI_SCRIPT"):
		return OS.get_environment("NHL_INTRO") == "1"
	return OS.get_environment("NHL_NO_INTRO") != "1"

# ---------------------------------------------------------------------------------------------
# intro_sequence (0x1672a)
# ---------------------------------------------------------------------------------------------

## the PIONEER PRODUCTIONS logo, then until a key: EAOPEN, the title and a demo game
func intro_sequence() -> void:
	ui.show_pointer(false)
	await _pioneer()
	League.srand_clock()
	while true:
		await _ea_open()
		if await ea_sports_intro():
			break
		if await demo_game():
			break
	scr.clearclip()
	scr.clear(0)

## PIONEER1.QFS "bkgd" faded in with "!pl1", the five frames "fla%d", "pion" and the palette of
## "!pio" (PIONEER2.QFS), with PIONEER2/3/4.IFF: only when the files are there
func _pioneer() -> void:
	var b1 := fe.bank("pioneer1")
	var b2 := fe.bank("pioneer2")
	if b1 == null or b2 == null:
		return
	scr.clearclip()
	scr.black()
	var bg := b1.find("bkgd")
	if bg != null:
		scr.drawshape_home(bg)
	fe.play_loop("pioneer2", 0x7f)
	var pl1 := Screen8.shape_palette(b1.find("!pl1"))
	await scr.fade_in(pl1, 0x5a / 6)
	for i in 5:
		var f := b2.find("fla%d" % i)
		if f != null:
			scr.drawshape_remap(f, f.x, f.y)
			await ui.wait_ticks_or_input(5)
	var pion := b2.find("pion")
	if pion != null:
		scr.drawshape_home(pion)
	var pio := b2.find("!pio")
	if pio != null:
		await scr.fade_in(Screen8.shape_palette(pio), 16)
	await ui.wait_ticks_or_input(200)
	await fe.fade_loop(100)
	await scr.fade_out(16)

## EAOPEN.QFS "scrn" with its "!pal" and EASPORTS.IFF for 200 ticks: only when the file is there
func _ea_open() -> void:
	var b := fe.bank("eaopen")
	if b == null:
		return
	scr.clearclip()
	scr.black()
	scr.drawshape_remap(b.find("scrn"), 0, 0)
	fe.play_loop("easports", 0x4c)
	await scr.fade_in(Screen8.shape_palette(b.find("!pal")), 16)
	await ui.wait_ticks_or_input(200)
	await fe.fade_loop(100)
	await scr.fade_out(16)

## ea_sports_intro (0x15fe9): EASCRN "scrn" and TITLE.CMV with the title song (ADTITLE, MTTITLE
## for the MT-32) until the video has run twice or a key is pressed (intro_skip_pressed after 0x23
## frames); true when a key ended it. Without the CD the loading screen stands in for the title
## (eight seconds).
func ea_sports_intro() -> bool:
	scr.clearclip()
	fe.loading_shown = false
	fe.play_song("MTTITLE" if Session.sound_device == 8 else "ADTITLE")
	await fe.loading_screen(0)
	var r: int = await ui.wait_ticks_or_input(800)
	fe.stop_song()
	await scr.fade_out(16)
	fe.loading_shown = false
	return r != 0

## demo_game (0x15d6b): a game of the computer against itself with periods of 60 seconds, the
## teams chosen in turn: two at random, one of 17 matchups, the two all-star teams. A key ends it
## (true: the intro is over); the end of the first period starts the intro again (false).
func demo_game() -> bool:
	demo_kind = (demo_kind + 1) % 3
	var home := 0
	var away := 0
	match demo_kind:
		2:
			home = 0x1b
			away = 0x1a
		1:
			var k := randi() % 0x11
			home = Exe.u8(DEMO_PAIRS + k * 2)
			away = Exe.u8(DEMO_PAIRS + k * 2 + 1)
		_:
			home = randi() % 0x1a
			away = (home + 1 + randi() % 0x19) % 0x1a
	if home >= fe.db.team_count() or away >= fe.db.team_count():
		home = 0x0c
		away = 0x15
	fe.loading_shown = false
	await fe.loading_screen()
	var flags := 0xff | (0x100 if Session.sound_enabled else 0) | 0x200
	var setup := {
		"home": home, "away": away, "user1": 0, "user2": 0,
		"option_flags": flags, "period_length": DEMO_PERIOD,
		"anthem": true, "demo": true,
	}
	var r: int = await fe.app.play_match_async(setup)
	fe.game = null
	fe.loading_shown = false
	return r == 2

# ---------------------------------------------------------------------------------------------
# credits_screen (0x16f9a)
# ---------------------------------------------------------------------------------------------

## a page of off_c6399: +0 the line count, +1 the ticks it is shown, +5 the photograph's file
## name, +9 the lines
static func credit_page(i: int) -> Dictionary:
	var p := Exe.u32(CREDIT_PAGES + i * 4)
	var n := Exe.i8(p)
	var lines := PackedStringArray()
	for k in maxi(n, 0):
		lines.append(Exe.str_ptr(p + 9 + k * 4))
	return {"addr": p, "ticks": Exe.u32(p + 1), "photo": Exe.str_ptr(p + 5) if p != CREDIT_END else "", "lines": lines}

## the background (CREDITS.QFS "bkgd" with "!pal") and the panel of the text (0x135 x 0x14e at
## 0x14a, 0x3f) kept to clear it for the next page; the lines are centred on x 0x1ea around y 0xda,
## the photograph "shp0" of CREDITnn.QFS at (0x85 + rand % 8, 0x6a + rand % 8). Each page shows
## for its ticks and 0x62 more; from the eighth on the font is KAUFM020. A key or a click ends the
## credits. The music is CREDITS.IFF, or the title song without digitised sound.
func credits_screen() -> void:
	ui.show_pointer(false)
	scr.clearclip()
	scr.black()
	var bg := fe.bank("credits")
	var pal: PackedByteArray
	var cx := 0x1ea
	var cy := 0xda
	var panel_at := Vector2i(0x14a, 0x3f)
	var panel_size := Vector2i(0x135, 0x14e)
	var colours := Vector2i(0x7f, 0)
	if bg != null:
		pal = Screen8.shape_palette(bg.find("!pal"))
		scr.drawshape_home(bg.find("bkgd"))
	else:
		# without the CD: the NHL emblem of the statistics screens, the lines in the middle
		var emb := fe.bank("embnhl")
		var ep := fe.bank("embpal")
		pal = Screen8.shape_palette(ep.find("!pal")) if ep != null else FrontEnd._grey_palette()
		scr.clear(0)
		if emb != null:
			scr.drawshape_remap(emb.find("bkgd"), 0, 0)
		cx = 0x140
		cy = 0xf0
		panel_at = Vector2i(0, 0)
		panel_size = Vector2i(0x280, 0x1e0)
		colours = Vector2i(0x40, 0x43)
	var panel := scr.grab(panel_at.x, panel_at.y, panel_size.x, panel_size.y)
	scr.setfont(fe.font_main)
	scr.set_text_colors(colours.x, colours.y)
	if Session.sound_enabled and GameFiles.has("credits.iff"):
		fe.play_loop("credits", 0x4c)
	else:
		fe.play_song("MTTITLE" if Session.sound_device == 8 else "ADTITLE")
	await scr.fade_in(pal, 16)
	fe.say_goodnight()
	for i in CREDIT_PAGE_COUNT:
		if i == 7:
			scr.setfont(fe.font_kaufm)
		var page := credit_page(i)
		ui.reset_events()
		if i != 0 and await ui.wait_ticks_or_input(0x62) != 0:
			break
		if page["addr"] == CREDIT_END:
			continue
		scr.put(panel)
		var photo := fe.bank(page["photo"]) if page["photo"] != "" else null
		if photo != null:
			scr.drawshape_remap(photo.find("shp0"), 0x85 + randi() % 8, 0x6a + randi() % 8)
		var lines: PackedStringArray = page["lines"]
		var h := scr.font_height()
		var y := cy - (h * lines.size() >> 1)
		for s in lines:
			scr.print_text_at(cx - (scr.textwidth(s) >> 1), y, s)
			y += h
		ui.reset_events()
		if await ui.wait_ticks_or_input(page["ticks"]) != 0:
			break
	scr.put(panel)
	await fe.fade_loop(100)
	await scr.fade_out(16)
	fe.stop_song()
	scr.setfont(fe.font_main)
	scr.clearclip()
	scr.clear(0)
