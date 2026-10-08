class_name Hud
extends Node2D
## The 320x32 scoreboard window of the match (show_scoreboard, draw_clock, draw_score_digits,
## draw_clock_full, draw_line_box, draw_penalty_clocks of HOCKEY.EXE) drawn below the 320x168 ice
## view, and the message box of the stoppages (draw_message_box). show_scoreboard lays the base:
## 'srb3' of SCRBRD2.PPV, the crests of CRESTS4.PPV at (4, 4) and (0x11c, 4) through the team
## remap tables (with colour 0x43 -> 0x67), the period number in the 8x7 digits "3000".. at
## (0x98, 0x16) / (0xa0, 0x16) ("OT" for 0) and the label of the line on the ice ('lin1'..'PK2')
## at (0x2a, 0x14) / (0xfb, 0x14). Shapes come from SCRBRD1.PPV: 'hlin'/'vlin'
## panels (line energies), 'homp'/'visp' (penalties), the 16x13 score digits "0000".."0009"
## ("000 " blank), the 16x11 clock digits "1000".. and the 8x4 penalty clock digits "2000"..

const HUD_Y := 168
const SCORE_X := [[0x2e, 0x38], [0xff, 0x109]]   # tens / ones per team (draw_score_digits)
const CLOCK_X := [0x8c, 0x95, 0xa1, 0xaa]          # draw_clock_full
const PANEL_X := [64, 184]                         # 'hlin' / 'vlin' home position
const BARS_X := [0x4a, 0xc1]                       # draw_line_box
const ENERGY_X := [0x2b, 0xfc]                     # draw_energy_bar: energy of the current line
const PENALTY_X := [0x48, 0xbf]                    # draw_penalty_clocks

var sim: Sim
var palette: GamePalette
var score_digits: Array = []     # 11 textures (10 = blank)
var clock_digits: Array = []
var small_digits: Array = []
var panels: Dictionary = {}      # name -> Texture2D
var base: Texture2D              # SCRBRD2 'srb3'
var period_digits: Array = []    # SCRBRD2 "3000".."3009", "300 "
var period_ot: Texture2D
var crests: Array = [null, null] # CRESTS4 by team abbreviation
var line_labels: Array = []      # SCRBRD1 lin1 lin2 lin3 lin4 PP1 PP2 PK1 PK2
var font_big: Vfn                # SCOR3B (message box shadow)
var font_small: Vfn              # SCOR2B (message box face)
var font_hud: Vfn                # HILIGHT
var font_small_hud: Vfn          # WITTLE06
var text_cache: Dictionary = {}
var assets_ok := false
var panel_view: PanelView        # the dithered score font

func setup(s: Sim, pal: GamePalette, scrbrd: Shpi, fonts: Dictionary, scrbrd2: Shpi = null, crest_bank: Shpi = null) -> void:
	sim = s
	palette = pal
	if scrbrd2 != null and pal != null:
		base = _tex(scrbrd2.find("srb3"))
		for d in 10:
			period_digits.append(_tex(scrbrd2.find("300%d" % d)))
		period_digits.append(_tex(scrbrd2.find("300 ")))
		period_ot = _tex(scrbrd2.find("OT  "))
	if scrbrd != null and pal != null:
		for n in ["lin1", "lin2", "lin3", "lin4", "PP1 ", "PP2 ", "PK1 ", "PK2 "]:
			line_labels.append(_tex(scrbrd.find(n)))
	load_crests(crest_bank)
	if scrbrd != null and pal != null:
		for set in [["0", score_digits], ["1", clock_digits], ["2", small_digits]]:
			var prefix: String = set[0]
			var out: Array = set[1]
			for d in 10:
				out.append(_tex(scrbrd.find("%s00%d" % [prefix, d])))
			out.append(_tex(scrbrd.find(prefix + "00 ")))
		for n in ["hlin", "vlin", "homp", "visp", "hpp", "vpp", "hpk", "vpk"]:
			panels[n] = _tex(scrbrd.find(n))
		assets_ok = score_digits[0] != null and panels["hlin"] != null
	font_big = fonts.get("scor3b", null)
	font_small = fonts.get("scor2b", null)
	font_hud = fonts.get("hilight", null)
	font_small_hud = fonts.get("wittle06", null)
	z_index = 100

## the crests of the teams on the ice (show_scoreboard: again for the teams of a highlight)
func load_crests(crest_bank: Shpi) -> void:
	crests = [null, null]
	if crest_bank == null or palette == null:
		return
	for t in 2:
		var abbrev := sim.teams[t].abbrev()
		var shape := crest_bank.find(abbrev.rpad(4))
		if shape != null and shape.is_image():
			var remap := palette.table(t, false).duplicate()
			if remap.size() >= 256:
				remap[0x43] = 0x67
				remap[0xff] = 0xff
			crests[t] = shape.to_texture(palette.colors, remap)

func _tex(shape: Shpi.Shape) -> Texture2D:
	if shape == null or not shape.is_image():
		return null
	return shape.to_texture(palette.colors)

func _process(_delta: float) -> void:
	queue_redraw()

func _draw() -> void:
	draw_rect(Rect2(0, HUD_Y, 320, 32), Color.BLACK)
	if sim == null:
		return
	if not assets_ok:
		_draw_fallback()
		return
	if base != null:
		draw_texture(base, Vector2(0, HUD_Y))
	for t in 2:
		if crests[t] != null:
			draw_texture(crests[t], Vector2(4 if t == 0 else 0x11c, HUD_Y + 4))
		var line := sim.teams[t].current_line
		if line >= 0 and line < line_labels.size() and line_labels[line] != null:
			draw_texture(line_labels[line], Vector2(0x2a if t == 0 else 0xfb, HUD_Y + 0x14))
	for t in 2:
		var team := sim.teams[t]
		# draw_clock: the penalty clocks unless the line change prompt is open, the list was found
		# empty or no statistics are kept (Scoreboard.draw_clock)
		var penalties: bool = sim.hud_penalties[t]
		var shown := _box_line(team)
		var panel: Texture2D = null
		if penalties:
			panel = panels["homp" if t == 0 else "visp"]
		elif shown < 4:
			panel = panels["hlin" if t == 0 else "vlin"]
		elif shown < 6:
			panel = panels["hpp" if t == 0 else "vpp"]
		else:
			panel = panels["hpk" if t == 0 else "vpk"]
		if panel != null:
			draw_texture(panel, Vector2(PANEL_X[t], HUD_Y))
		if penalties:
			_draw_penalty_clocks(t, PENALTY_X[t])
		else:
			_draw_line_bars(team, BARS_X[t])
		_draw_energy(team, ENERGY_X[t])
		var goals := team.goals
		var tens: Texture2D = score_digits[(goals / 10) % 10] if goals >= 10 else score_digits[10]
		draw_texture(tens, Vector2(SCORE_X[t][0], HUD_Y + 4))
		draw_texture(score_digits[goals % 10], Vector2(SCORE_X[t][1], HUD_Y + 4))
	_draw_clock()
	_draw_period()
	_draw_message()

## the line whose panel draw_line_box shows: the line picked at the open line change prompt
## (lc_line), else the current one
func _box_line(team: Team) -> int:
	return sim.lc_line[team.index] if team.line_change_ui else team.current_line

## draw_line_box: two bars per line (left and right of the line number), 20 pixels = full energy
## (line_avg_energy / 200), the rest of the 20 pixels in the background colour; the current line in
## another colour; at the line change prompt the line picked blinks (lc_show) on a light ground.
## The power play and penalty killing panels show their two units at the second and third row.
func _draw_line_bars(team: Team, x0: int) -> void:
	var shown := _box_line(team)
	var first := 0
	var last := 4
	var y := HUD_Y + 8
	if shown >= 4:
		first = 4 if shown < 6 else 6
		last = first + 2
		y = HUD_Y + 14
	for line in range(first, last):
		var energy := Lines.line_avg_energy(sim, team, line)
		var w := clampi(energy / 200, 0, 20)
		var c: Color = palette.colors[0x67]
		var ground: Color = palette.colors[0]
		if line == shown and sim.lc_show[team.index] != 0:
			c = palette.colors[0x61]
			ground = palette.colors[7]
		elif line == team.current_line:
			c = palette.colors[0x21]
		draw_rect(Rect2(x0 + 0x15 - w, y, w, 3), c)
		draw_rect(Rect2(x0 + 0x20, y, w, 3), c)
		draw_rect(Rect2(x0 + 1, y, 0x14 - w, 3), ground)
		draw_rect(Rect2(x0 + 0x20 + w, y, 0x14 - w, 3), ground)
		y += 6

## draw_energy_bar: the energy of the players on the ice (0..8 pixels)
func _draw_energy(team: Team, x0: int) -> void:
	var w := clampi(Lines.team_avg_energy(sim, team) / 500, 0, 8)
	var c := palette.colors[0x67]
	draw_rect(Rect2(x0 + 9 - w, HUD_Y + 0x1a, w, 3), c)
	draw_rect(Rect2(x0 + 0x10, HUD_Y + 0x1a, w, 3), c)

## draw_penalty_clocks: the first four entries of the team's penalty list (Scoreboard): number,
## minutes and seconds in the small digits (the tens of the number and of the minutes blank below
## 10), a free entry blank
func _draw_penalty_clocks(t: int, x0: int) -> void:
	var l: Array = sim.penalty_lists[t]
	var xs := [10, 0x10, 0x1b, 0x21, 0x2a, 0x30]
	for i in 4:
		var y := HUD_Y + 9 + 5 * i
		var number: int = l[i * 4]
		if number < 0:
			for dx in xs:
				draw_texture(small_digits[10], Vector2(x0 + dx, y))
			continue
		var minutes: int = l[i * 4 + 1]
		var seconds: int = l[i * 4 + 2]
		var values := [number / 10, number, minutes / 10, minutes, seconds / 10, seconds]
		for k in 6:
			var tex: Texture2D = small_digits[posmod(values[k], 10)]
			if (k == 0 and number < 10) or (k == 2 and minutes < 10):
				tex = small_digits[10]
			draw_texture(tex, Vector2(x0 + xs[k], y))

## draw_clock_full: mm:ss, or ss.hh during the last minute
func _draw_clock() -> void:
	var y := HUD_Y + 3
	# (the scoreboard's own clock, Scoreboard)
	var minutes: int = maxi(sim.hud_clock[0], 0)
	var seconds: int = posmod(sim.hud_clock[1], 60)
	if minutes == 0:
		var hundredths: int = posmod(sim.hud_clock[2], 100)
		draw_texture(clock_digits[10], Vector2(CLOCK_X[3], y))
		draw_texture(clock_digits[seconds / 10] if seconds >= 10 else clock_digits[10], Vector2(CLOCK_X[0], y))
		draw_texture(clock_digits[seconds % 10], Vector2(CLOCK_X[1], y))
		draw_texture(clock_digits[(hundredths / 10) % 10], Vector2(CLOCK_X[2], y))
	else:
		draw_texture(clock_digits[minutes / 10] if minutes >= 10 else clock_digits[10], Vector2(CLOCK_X[0], y))
		draw_texture(clock_digits[minutes % 10], Vector2(CLOCK_X[1], y))
		draw_texture(clock_digits[seconds / 10], Vector2(CLOCK_X[2], y))
		draw_texture(clock_digits[seconds % 10], Vector2(CLOCK_X[3], y))

## show_scoreboard: the period (_period_num, 1 in the first period) in two 8x7 digits, "OT" for 0;
## after the game nothing changes
func _draw_period() -> void:
	var n := sim.period + 1
	if period_digits.size() < 10:
		var tex := _text(font_small_hud, "P%d" % n, palette.colors[0x67])
		if tex != null:
			draw_texture(tex, Vector2(0x98, HUD_Y + 0x16))
		return
	if n == 0:
		if period_ot != null:
			draw_texture(period_ot, Vector2(0x98, HUD_Y + 0x16))
		return
	n %= 100
	if period_digits[n / 10] != null:
		draw_texture(period_digits[n / 10], Vector2(0x98, HUD_Y + 0x16))
	if period_digits[n % 10] != null:
		draw_texture(period_digits[n % 10], Vector2(0xa0, HUD_Y + 0x16))

## draw_message_box (0x66fe2): the message (word_cbec8, set by queue_infraction from
## infraction_priority, the goalie hotkeys and the offside warning) in a box at (12, 149) of the
## view: colour 0x10 with the dotted colour 9, a 4 pixel black frame, the dithered score font
func _draw_message() -> void:
	var msg := sim.message
	if msg < 0 or msg >= Tables.message_strings.size():
		return
	var text := Tables.message_strings[msg]
	var tex: Texture2D = panel_view.score_texture(text) if panel_view != null else null
	if tex == null:
		tex = _text(font_small_hud, text, palette.colors[0x27])
	if tex == null:
		return
	var x := 0xc
	var y := 0x95
	var w := tex.get_width() + 4
	var h := 0x9e - 0x95
	draw_rect(Rect2(x, y, w, h), palette.colors[0x10])
	for yy in range(y + 1, y + h, 2):
		for xx in range(x, x + w, 2):
			draw_rect(Rect2(xx, yy, 1, 1), palette.colors[9])
	draw_rect(Rect2(x - 4, y - 4, w + 8, 4), Color.BLACK)
	draw_rect(Rect2(x - 4, y, 4, 9), Color.BLACK)
	draw_rect(Rect2(x + w, y, 4, 9), Color.BLACK)
	draw_rect(Rect2(x - 4, y + h, w + 8, 4), Color.BLACK)
	draw_texture(tex, Vector2(x + 2, y + 1))

func _text(font: Vfn, s: String, color: Color) -> Texture2D:
	if font == null:
		return null
	var key := "%s|%s|%s" % [font.get_instance_id(), s, color.to_html()]
	if not text_cache.has(key):
		text_cache[key] = ImageTexture.create_from_image(font.render(s, color))
	return text_cache[key]

func _draw_fallback() -> void:
	var state := ""
	if sim.game_over:
		state = "  FINAL"
	elif sim.faceoff_pending:
		state = "  faceoff"
	elif sim.play_stopped:
		state = "  whistle"
	var text := "%s %d - %d %s   P%d %d:%02d%s" % [sim.teams[0].abbrev(), sim.teams[0].goals, sim.teams[1].goals,
		sim.teams[1].abbrev(), sim.period + 1, sim.clock_seconds / 60, sim.clock_seconds % 60, state]
	draw_string(ThemeDB.fallback_font, Vector2(4, HUD_Y + 14), text, HORIZONTAL_ALIGNMENT_LEFT, -1, 8, Color.WHITE)
	draw_string(ThemeDB.fallback_font, Vector2(4, HUD_Y + 26), "(game files not found: set NHL_GAME_DIR)", HORIZONTAL_ALIGNMENT_LEFT, -1, 8, Color.GRAY)
