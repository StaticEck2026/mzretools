class_name Hud
extends Node2D
## The 320x32 scoreboard window of the match (draw_clock, draw_score_digits, draw_clock_full,
## draw_line_box, draw_penalty_clocks of HOCKEY.EXE) drawn below the 320x168 ice view, and the
## message box of the stoppages (draw_message_box). Shapes come from SCRBRD1.PPV: 'hlin'/'vlin'
## panels (line energies), 'homp'/'visp' (penalties), the 16x13 score digits "0000".."0009"
## ("000 " blank), the 16x11 clock digits "1000".. and the 8x4 penalty clock digits "2000"..

const HUD_Y := 168
const SCORE_X := [[0x2e, 0x38], [0xff, 0x109]]   # tens / ones per team (draw_score_digits)
const CLOCK_X := [0x8c, 0x95, 0xa1, 0xaa]          # draw_clock_full
const PANEL_X := [64, 184]                         # 'hlin' / 'vlin' home position
const BARS_X := [0x4a, 0xc1]                       # draw_line_box
const ENERGY_X := [0x2b, 0xfc]                     # sub_15707: energy of the current line
const PENALTY_X := [0x48, 0xbf]                    # draw_penalty_clocks

var sim: Sim
var palette: GamePalette
var score_digits: Array = []     # 11 textures (10 = blank)
var clock_digits: Array = []
var small_digits: Array = []
var panels: Dictionary = {}      # name -> Texture2D
var font_big: Vfn                # SCOR3B (message box shadow)
var font_small: Vfn              # SCOR2B (message box face)
var font_hud: Vfn                # HILIGHT
var font_small_hud: Vfn          # WITTLE06
var text_cache: Dictionary = {}
var assets_ok := false

func setup(s: Sim, pal: GamePalette, scrbrd: Shpi, fonts: Dictionary) -> void:
	sim = s
	palette = pal
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
	for t in 2:
		var team := sim.teams[t]
		var penalties := not team.penalties.is_empty()
		var panel: Texture2D = null
		if penalties:
			panel = panels["homp" if t == 0 else "visp"]
		elif team.current_line < 4:
			panel = panels["hlin" if t == 0 else "vlin"]
		elif team.current_line < 6:
			panel = panels["hpp" if t == 0 else "vpp"]
		else:
			panel = panels["hpk" if t == 0 else "vpk"]
		if panel != null:
			draw_texture(panel, Vector2(PANEL_X[t], HUD_Y))
		if penalties:
			_draw_penalty_clocks(team, PENALTY_X[t])
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

## draw_line_box: two bars per line (left and right of the line number), 20 pixels = full energy
## (line_avg_energy / 200), the current line in another colour; the power play and penalty
## killing panels show their two units at the second and third row
func _draw_line_bars(team: Team, x0: int) -> void:
	var first := 0
	var last := 4
	var y := HUD_Y + 8
	if team.current_line >= 4:
		first = 4 if team.current_line < 6 else 6
		last = first + 2
		y = HUD_Y + 14
	for line in range(first, last):
		var energy := Lines.line_avg_energy(sim, team, line)
		var w := clampi(energy / 200, 0, 20)
		var c := palette.colors[0x21] if line == team.current_line else palette.colors[0x67]
		draw_rect(Rect2(x0 + 0x15 - w, y, w, 3), c)
		draw_rect(Rect2(x0 + 0x20, y, w, 3), c)
		y += 6

## draw_energy_bar (sub_15707): the energy of the players on the ice (0..8 pixels)
func _draw_energy(team: Team, x0: int) -> void:
	var w := clampi(Lines.team_avg_energy(sim, team) / 500, 0, 8)
	var c := palette.colors[0x67]
	draw_rect(Rect2(x0 + 9 - w, HUD_Y + 0x1a, w, 3), c)
	draw_rect(Rect2(x0 + 0x10, HUD_Y + 0x1a, w, 3), c)

## draw_penalty_clocks: number, minutes and seconds of up to four penalties in the small digits
func _draw_penalty_clocks(team: Team, x0: int) -> void:
	for i in 4:
		var y := HUD_Y + 9 + 5 * i
		if i >= team.penalties.size():
			for dx in [10, 0x10, 0x1b, 0x21, 0x2a, 0x30]:
				draw_texture(small_digits[10], Vector2(x0 + dx, y))
			continue
		var pen: Array = team.penalties[i]
		var number := 0
		if team.info != null and team.info.player(pen[0]) != null:
			number = team.info.player(pen[0]).number
		elif pen[2] >= 0:
			number = sim.entities[pen[2]].number
		var seconds: int = pen[1]
		var values := [number / 10, number % 10, seconds / 60 / 10, (seconds / 60) % 10, (seconds % 60) / 10, seconds % 10]
		var xs := [10, 0x10, 0x1b, 0x21, 0x2a, 0x30]
		for k in 6:
			var v: int = values[k]
			var tex: Texture2D = small_digits[v % 10]
			if (k == 0 and number < 10) or (k == 2 and seconds < 600):
				tex = small_digits[10]
			draw_texture(tex, Vector2(x0 + xs[k], y))

## draw_clock_full: mm:ss, or ss.hh during the last minute
func _draw_clock() -> void:
	var y := HUD_Y + 3
	var minutes := sim.clock_seconds / 60
	var seconds := sim.clock_seconds % 60
	if minutes == 0:
		var hundredths := (0x17 - sim.clock_sub) * 100 / 0x18
		draw_texture(clock_digits[10], Vector2(CLOCK_X[3], y))
		draw_texture(clock_digits[seconds / 10] if seconds >= 10 else clock_digits[10], Vector2(CLOCK_X[0], y))
		draw_texture(clock_digits[seconds % 10], Vector2(CLOCK_X[1], y))
		draw_texture(clock_digits[(hundredths / 10) % 10], Vector2(CLOCK_X[2], y))
	else:
		draw_texture(clock_digits[minutes / 10] if minutes >= 10 else clock_digits[10], Vector2(CLOCK_X[0], y))
		draw_texture(clock_digits[minutes % 10], Vector2(CLOCK_X[1], y))
		draw_texture(clock_digits[seconds / 10], Vector2(CLOCK_X[2], y))
		draw_texture(clock_digits[seconds % 10], Vector2(CLOCK_X[3], y))

## the period is not part of the original scoreboard (it is shown on the pause screen); it goes
## into the free space under the clock in the small font
func _draw_period() -> void:
	var names := ["1ST", "2ND", "3RD", "OT"]
	var label: String = names[mini(sim.period, 3)]
	if sim.game_over:
		label = "FINAL"
	var tex := _text(font_small_hud, label, palette.colors[0x67])
	if tex != null:
		draw_texture(tex, Vector2(160 - tex.get_width() / 2, HUD_Y + 19))

## draw_message_box: box with the message of the stoppage at (12, 149) of the view
func _draw_message() -> void:
	if sim.game_over:
		return
	var msg := sim.message       # PULL GOALIE / RETURN GOALIE / the OFFSIDE warning
	if msg < 0 and sim.play_stopped:
		match sim.ref_infraction:
			Rules.INF_ICING: msg = 5
			Rules.INF_OFFSIDE: msg = 4
			Rules.INF_TWO_LINE: msg = 3
			_:
				if sim.ref_infraction >= 9 and sim.ref_infraction <= 25:
					msg = 6
				elif sim.faceoff_pending:
					msg = 2
	if msg < 0 or msg >= Tables.message_strings.size():
		return
	var text := Tables.message_strings[msg]
	# the original prints with SCOR3B (shadow) and SCOR2B (face); their glyph encoding is not
	# decoded yet (see FORMATS.md), so the 6 pixel WITTLE06 font stands in
	var face := _text(font_small_hud, text, palette.colors[0x27])
	if face == null:
		return
	var w := face.get_width() + 4
	var x := 12
	var y := 149
	draw_rect(Rect2(x - 4, y - 4, w + 8, 9 + 8), Color.BLACK)
	draw_rect(Rect2(x, y, w, 9), palette.colors[0x10])
	draw_rect(Rect2(x, y, w, 9), palette.colors[9], false)
	draw_texture(face, Vector2(x + 2, y + 2))

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
