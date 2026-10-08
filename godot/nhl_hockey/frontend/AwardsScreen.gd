class_name AwardsScreen
extends RefCounted
## The awards after the play-offs (awards_screen 0x13320): the title (AWARDSI.QFS "scrn" and "titl")
## to its fanfare, the awards read from the league's files (Awards.load, load_award_stats), a page
## for each (league_leaders_screen 0x12849: the trophy's picture, the winner and his team, his
## numbers of the season and of the play-offs, two lines on the award) and the summary of the
## eleven (awards_summary 0x13188: AWARDSI "scrn" and "summ"), to the awards song. Escape ends the
## pages and skips the summary; a read that failed shows none of them.
##
## AWARDSI.QFS, the trophies' pictures (HART.QFS .. STAN.QFS) and the recordings AWARDS.IFF and
## AWASONG.IFF are on the CD only. Without a picture EMBSCUP.QFS stands in (its palette, the text in
## its brightest colour); without a recording the songs play (ADAFAN and ADAWARDS, MTAFAN and
## MTAWARDS for the MT-32), as they do in the original without digital sound.

var fe: FrontEnd
var scr: Screen8
var ui: Ui

const TEXT_COLOURS := 0xc513c     # unk_c513c: the text colour of each page (in its picture's palette)
const PICTURES := 0xc5194         # off_c5194: the trophies' pictures
const TITLES := 0xc51c0           # off_c51c0: the awards' names (the summary)
const LINES := 0xc51ec            # off_c51ec: two lines on each award (the second may be missing)
const COLUMNS := 0xc527b          # off_c527b: "Season", "Playoff"
const DUCKS := 0xc03a3            # "Mighty Ducks™ of Anaheim"
const TM_TEAMS := [2, 0x18, 0x19] # the teams whose name takes ™ (the others ®)

func _init(f: FrontEnd) -> void:
	fe = f
	scr = f.scr
	ui = f.ui

## awards_screen with the league's TEAMS.DB, KEY.DB and SEASON.DB
func run(teams: PackedByteArray, key_db: PackedByteArray, season: PackedByteArray) -> void:
	ui.reset_events()
	await fe.leave_screen(0x32)
	var keep_font := scr.font
	scr.setfont(fe.font_kaufm)
	var title := fe.bank("awardsi")
	var pal := _picture(title, ["scrn", "titl"])
	var recorded := Session.sound_enabled and GameFiles.has("awards.iff")
	if recorded:
		fe.play_loop("awards", 0x4c)
	elif Session.sound_device != 1:
		fe.play_song("MTAFAN" if Session.sound_device == 8 else "ADAFAN")
	await scr.fade_in(pal, 16)
	if recorded:
		# the recording to its end or a key
		while fe.loop_playing() and await ui.wait_ticks_or_input(10) == 0:
			pass
		await fe.leave_screen(0x32)
	elif Session.sound_device != 1:
		# sfx_set_volume: the fanfare to its end
		while fe.song_playing():
			await ui.frame()
		await scr.fade_out(16)
		fe.stop_song()
	else:
		await ui.wait_ticks_or_input(0x140)
		await scr.fade_out(16)
	var err := Awards.load(teams, key_db, season)
	recorded = Session.sound_enabled and GameFiles.has("awasong.iff")
	if recorded:
		fe.play_loop("awasong", 0x7f)
	else:
		fe.play_song("MTAWARDS" if Session.sound_device == 8 else "ADAWARDS")
	if err == 0:
		var r := await leaders()
		if r < 3:
			ui.reset_events()
			scr.clearclip()
			pal = summary(title)
			await scr.fade_in(pal, 16)
			await ui.wait_ticks_or_input(0x2328)
			await scr.fade_out(16)
		scr.clearclip()
	if recorded:
		await fe.fade_loop(0x78)
	else:
		fe.stop_song()
	scr.setfont(keep_font)

## a picture of the awards (its shapes drawn where they belong) and its palette, else the stand-in
func _picture(bank: Shpi, shapes: Array) -> PackedByteArray:
	scr.clearclip()
	if bank != null:
		for n: String in shapes:
			scr.drawshape_home(bank.find(n))
		return Screen8.shape_palette(bank.find("!pal"))
	return _stand_in()

func _stand_in() -> PackedByteArray:
	var b := fe.bank("embscup")
	var pb := fe.bank("embpalp")
	scr.clear(0)
	if b != null:
		scr.drawshape_remap(b.find("bkgd"), 0, 0)
	return Screen8.shape_palette(pb.find("!pal")) if pb != null else FrontEnd._grey_palette()

## the brightest colour of a palette (the text of the stand-in)
static func _brightest(pal: PackedByteArray) -> int:
	var best := 0
	var bv := -1
	for i in pal.size() / 3:
		var v: int = pal[i * 3] + pal[i * 3 + 1] + pal[i * 3 + 2]
		if v > bv:
			bv = v
			best = i
	return best

## the C string at `at` of a record
static func _cstr(b: PackedByteArray, at: int) -> String:
	var s := ""
	var i := at
	while i < b.size() and b[i] != 0:
		s += char(b[i])
		i += 1
	return s

## strnicmp_ascii(s, "ANA", 3)
static func _anaheim(s: String) -> bool:
	return s.length() >= 3 and s.left(3).to_upper() == "ANA"

## the winning team of a team award as the pages show it: the Mighty Ducks by their abbreviation
## (+0), the others by name (+5) with ™ when it starts "Cal" or "Flo", else ®
static func _team_award(rec: PackedByteArray) -> String:
	if _anaheim(_cstr(rec, 0)):
		return Exe.str_at(DUCKS)
	return _named(_cstr(rec, 5))

static func _named(s: String) -> String:
	var tm := s.length() >= 3 and (s.left(3).to_upper() == "CAL" or s.left(3).to_upper() == "FLO")
	return s + (char(7) if tm else char(6))

## the team of a player (KEY +0): its name (db_open_check), the Mighty Ducks' long name, ™ or ®
static func _player_team(team: int) -> String:
	var s := _cstr(Awards.team_names[team], 0) if team < Awards.team_names.size() else ""
	if _anaheim(s):
		return Exe.str_at(DUCKS)
	return s + (char(7) if team in TM_TEAMS else char(6))

## centred on x 0x1fe (the right of the pictures)
func _centre(y: int, s: String) -> void:
	scr.print_text_at(0x1fe - (scr.textwidth(s) >> 1), y, s)

## league_leaders_screen: the eleven pages, ten seconds each, a key the next, Escape (3) the end;
## the last result of wait_ticks_or_input
func leaders() -> int:
	ui.reset_events()
	var r := 0
	var i := 0
	while i < 11 and r != 3:
		var pal := page(i)
		await scr.fade_in(pal, 16)
		r = await ui.wait_ticks_or_input(0x2710)
		await scr.fade_out(16)
		i += 1
	return r

## the page of award i drawn (its palette returned): the picture, the winner centred on x 0x1fe
## at y 0x76 (a team; else the player, his team under him and his numbers), the award's lines
## ending at y 0x1ba
func page(i: int) -> PackedByteArray:
	var bank := fe.bank(Exe.str_ptr(PICTURES + i * 4))
	var pal: PackedByteArray
	if bank != null and bank.shapes.size() > 1:
		scr.clearclip()
		scr.drawshape_home(bank.shapes[1])
		pal = Screen8.shape_palette(bank.find("!pal"))
		scr.set_text_colors(Exe.u32(TEXT_COLOURS + i * 4), 0)
	else:
		pal = _stand_in()
		scr.set_text_colors(_brightest(pal), 0)
	var h := scr.font_height()
	var y := 0x76
	var kind := Awards.kind(i)
	if kind == 2:
		_centre(y, _team_award(Awards.stanley if i == 10 else Awards.presidents))
	else:
		var k: PackedByteArray = Awards.keys[i]
		_centre(y, "%s %s" % [_cstr(k, 3), _cstr(k, 0x13)])
		y += h
		_centre(y, _player_team(k[0]))
		_numbers(i, kind, 0x1a4, y + 0x2c)
	y = 0x1ba
	var second := Exe.str_ptr(LINES + i * 8 + 4)
	if second != "":
		_centre(y, second)
		y -= h
	_centre(y, Exe.str_ptr(LINES + i * 8))
	return pal

## the winner's numbers: the labels down the left, the season's and the play-offs' columns
## (a goalie's ties of the season only; the goals against average in hundredths, the save and the
## shooting percentages in tenths)
func _numbers(i: int, kind: int, x: int, y: int) -> void:
	var h := scr.font_height()
	var labels := ["GP", "Min", "GAA", "W", "L", "T", "SO", "EN", "Shots", "Pct"] if kind == 0 \
		else ["GP", "G", "A", "Pt", "PIM", "+/-", "PPG", "SHG", "Shots", "Pct"]
	for n in labels.size():
		scr.print_text_at(x, y + n * h, labels[n])
	var rec: PackedByteArray = Awards.easn_record() if i == 9 else Awards.stats[i]
	var base := 0
	for c in 2:
		scr.print_text_at(x + 0x34, y - h, Exe.str_ptr(COLUMNS + c * 4))
		x += 0x50
		var w := func(o: int) -> int: return rec.decode_u16(base + o)
		var vals := []
		if kind == 0:
			var gaa: int = w.call(0x10)
			var pct: int = w.call(0x14)
			vals = ["%d" % w.call(0), "%d" % w.call(0xc), "%d.%02d" % [gaa / 100, gaa % 100], "%d" % w.call(2),
				"%d" % w.call(4), "%d" % w.call(6) if c == 0 else "", "%d" % w.call(8), "%d" % w.call(0xa),
				"%d" % w.call(0x12), "%d.%01d" % [pct / 10, pct % 10]]
			base += 0x16
		else:
			var shots: int = w.call(0xe)
			var pct: int = (w.call(2) * 1000 + shots / 2) / shots if shots != 0 else 0
			vals = ["%d" % w.call(0), "%d" % w.call(2), "%d" % w.call(4), "%d" % w.call(6), "%d" % w.call(0xc),
				"%d" % rec.decode_s16(base + 0x10), "%d" % w.call(8), "%d" % w.call(0xa), "%d" % shots,
				"%d.%01d" % [pct / 10, pct % 10]]
			base += 0x12
		for n in vals.size():
			if vals[n] != "":
				scr.print_text_at(x, y + n * h, vals[n])

## awards_summary (0x13188): the eleven awards, their winners (a player's name as format_team_name
## fits it in 0xd2 pixels) and teams. A team award first looks at what the routine's buffer holds
## from the award before (the original's slip: the Mighty Ducks' long name only when that starts
## "ANA", which it never does), then names the team (+5) with ™ for "Cal" and "Flo", else ®.
func summary(bank: Shpi) -> PackedByteArray:
	var pal := _picture(bank, ["scrn", "summ"])
	scr.set_text_colors(1 if bank != null else _brightest(pal), 0)
	var buf := ""
	for i in 11:
		var y := 0x8c + 0x13 * i
		scr.print_text_at(0x14, y, Exe.str_ptr(TITLES + i * 4))
		var s := ""
		if Awards.kind(i) == 2:
			if _anaheim(buf):
				s = Exe.str_at(DUCKS)
			else:
				buf = _named(_cstr(Awards.stanley if i == 10 else Awards.presidents, 5))
				s = buf
		else:
			var k: PackedByteArray = Awards.keys[i]
			buf = _fit_name(_cstr(k, 3), _cstr(k, 0x13), 0xd2)
			scr.print_text_at(0xb4, y, buf)
			buf = _player_team(k[0])
			s = buf
		scr.print_text_at(0x190, y, s)
	return pal

## format_team_name (0x29c75) with a first name: "First Last", "F. Last" when wider than `width`
## (the last name alone for an empty first name), cut to fit
func _fit_name(first: String, last: String, width: int) -> String:
	var s := first + " " + last
	if scr.textwidth(s) > width:
		s = (first.left(1) + ". " if first != "" else "") + last
	while s.length() > 0 and scr.textwidth(s) > width:
		s = s.left(s.length() - 1)
	return s
