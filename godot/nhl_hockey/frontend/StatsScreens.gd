class_name StatsScreens
extends RefCounted
## The statistics screens of the front end: the standings (standings_table 0x27080), the team
## tables (team_stats_screen 0x235be), the player and goalie leaders (stats_table 0x25b24), a team's
## roster with its statistics (player_stats_screen 0x244e2), the player and goalie cards
## (player_card_screen 0x21cde, goalie_card_screen 0x22581) and the hubs that run their menus
## (exh_hub_sports_central / exh_hub_playoff_tree / exh_hub_league_calendar / exh_hub_stats: the
## team, player, goalie and standings hubs). The data:
##   CARTEAMS.DB (the '93 - '94 statistics) / TEAMS.DB of a league: team records of 0x4c / 0x2e8
##     bytes: +0 abbreviation, +5 city and name, +0x1a short name, +0x27 division, +0x28 season and
##     +0x3a play-off team statistics of 0x12 bytes: GP, W, L, T, GF (u16), GA, PPG, ADV (power plays),
##     PPGA, TSH (times short handed), PIM
##   KEY.DB: 0x34 byte player records: +0 team, +1 number, +2 position, +3 first name, +0x13 last
##     name, +0x24 ATT.DB offset, +0x28 CAREER.DB offset ('93 - '94), +0x2c SEASON.DB offset (a league),
##     +0x30 portrait id
##   CAREER.DB / SEASON.DB: skaters 0x2f bytes, season and play-offs blocks of 0x12 bytes: GP, G, A,
##     PTS, PPG, SHG, PIM, SOG, +/- (s16); goalies 0x36 bytes, blocks of 0x16: GP, W, L, T, -, -, MIN,
##     GA, GAA x 100, SA, SV% x 1000
##   ATT.DB: the ratings of the player card (14 of the 0x14 bytes, shown as (r + 5) * 5)

var fe: FrontEnd
var scr: Screen8
var ui: Ui

const C_LIGHT := 0x40               # the menu colours of the statistics screens (EMBPAL palette)
const C_FACE := 0x41
const C_DARK := 0x42

var hub_active := false             # stats_hub_active: a statistics hub is up (the entries redraw in it)
var current := Callable()           # stats_current_screen: the screen drawn, redrawn when the source changes
var current_arg := 0                # stats_current_arg
var selected_team := 0              # stats_selected_team: the team picked in the standings
var next_screen := 0                # stats_next_screen: 1 leave, 2 standings, 3 roster, 4 goalie card, 5 player card
var player: PackedByteArray         # card_player_record: the KEY.DB record of the player picked for a card
var roster_order: Array = []        # roster_skater_order (unk_dc6bc) / unk_dc754: the skaters of the roster in the order shown
var goalie_order: Array = []        # roster_goalie_order (unk_dc720) / unk_dc73c
var roster_keys: Array = []         # the KEY.DB records of the roster (25 skaters, 3 goalies)
var _files: Dictionary = {}

func _init(f: FrontEnd) -> void:
	fe = f
	scr = f.scr
	ui = f.ui

# ---------------------------------------------------------------------------------------------
# the data (unk_c65d4: the directory of the statistics shown, stats_league: a league's files,
# stats_playoffs: the play-offs)
# ---------------------------------------------------------------------------------------------

## the file of the statistics source: the installation for the '93 - '94 statistics, the league's
## directory otherwise
func data(name: String) -> PackedByteArray:
	var key := Session.stats_dir + "/" + name
	if not _files.has(key):
		var d := PackedByteArray()
		if Session.stats_league and Session.stats_dir != "":
			d = FileAccess.get_file_as_bytes(Session.stats_dir.path_join(name.to_upper()))
		if d.is_empty():
			d = GameFiles.read_raw(name)
		_files[key] = d
	return _files[key]

func forget_files() -> void:
	_files.clear()

static func u16(d: PackedByteArray, at: int) -> int:
	return d.decode_u16(at) if at >= 0 and at + 2 <= d.size() else 0

static func s16(d: PackedByteArray, at: int) -> int:
	return d.decode_s16(at) if at >= 0 and at + 2 <= d.size() else 0

static func b8(d: PackedByteArray, at: int) -> int:
	return d[at] if at >= 0 and at < d.size() else 0

static func cstr(d: PackedByteArray, at: int, n: int) -> String:
	return Database.cstring(d, at, n) if at >= 0 and at < d.size() else ""

## the team records of the standings: CARTEAMS.DB ('93 - '94) or TEAMS.DB (a league)
func team_file() -> PackedByteArray:
	return data("teams.db" if Session.stats_league else "carteams.db")

func team_stride() -> int:
	return 0x2e8 if Session.stats_league else 0x4c

func team_record(t: int) -> PackedByteArray:
	var d := team_file()
	return d.slice(t * team_stride(), t * team_stride() + 0x4c)

## the team statistics block (+0x28 season, +0x3a play-offs)
func team_block(rec: PackedByteArray) -> int:
	return 0x3a if Session.stats_playoffs else 0x28

func stats_file() -> PackedByteArray:
	return data("season.db" if Session.stats_league else "career.db")

## a KEY.DB record's statistics offset (+0x28 CAREER.DB, +0x2c SEASON.DB)
func stats_offset(key: PackedByteArray) -> int:
	return key.decode_s32(0x2c if Session.stats_league else 0x28)

# ---------------------------------------------------------------------------------------------
# common drawing: the background of the source, the PSTATBAR bar, the title
# ---------------------------------------------------------------------------------------------

## the background (EMBNHL / EMBSCUP "bkgd" under the menu bar) and PSTATBAR "pst2" at (0, y)
func _background(bank_name: String, bar_y: int = 0x1c, bar: String = "pst2") -> void:
	scr.clearclip()
	var b := fe.bank(bank_name)
	if b == null:
		b = fe.bank("embnhl")
	if b != null:
		scr.setclip(0, 0x13, 0x280, 0x1e0)
		var s := b.find("bkgd")
		if s != null:
			scr.drawshape_remap(s, s.x, s.y)
		scr.clearclip()
	var ps := fe.bank("pstatbar")
	if ps != null and bar != "":
		scr.drawshape_remap(ps.find(bar), 0, bar_y)

func _source_bank() -> String:
	return "embscup" if Session.stats_playoffs else "embnhl"

## stats_source_title (0x1ff86): "'93 - '94 Season" / "'93 - '94 Play-Offs" / the league's name
## in front of the screen's title
func source_title(suffix: String) -> String:
	var t: String
	if not Session.stats_league:
		t = "'93 - '94 Season" if not Session.stats_playoffs else "'93 - '94 Play-Offs"
	else:
		var name := Session.league_name if Session.league_name != "" else "League"
		t = '"%s" %s' % [name, "Play-Offs" if Session.stats_playoffs else "Season"]
	return t + suffix

func _title(text: String, y: int = 0x31) -> void:
	scr.setfont(fe.font_kaufm)
	scr.set_text_colors(0x40, 0x43)
	scr.print_outlined(300 - (scr.textwidth(text) >> 1), y, text)
	scr.setfont(fe.font_main)

func _p(x: int, y: int, s: String) -> void:
	scr.print_text_at(x, y, s)

## print_textf with the formats of the original (%2d, %3d, %4d, %5d)
func _pf(x: int, y: int, width: int, v: int) -> void:
	scr.print_text_at(x, y, str(v).lpad(width))

## the palette of the statistics screens (EMBPAL.QFS "!pal")
func stats_palette() -> PackedByteArray:
	var b := fe.bank("embpal")
	return Screen8.shape_palette(b.find("!pal")) if b != null else FrontEnd._grey_palette()

## format_team_name (0x29c75): "First Last", "F. Last" when wider than `width`, cut to fit
func format_name(first: String, last: String, width: int) -> String:
	var s := last
	if first != "":
		s = first + " " + last
		if scr.textwidth(s) > width:
			s = first.left(1) + ". " + last
	while s.length() > 0 and scr.textwidth(s) > width:
		s = s.left(s.length() - 1)
	return s

# ---------------------------------------------------------------------------------------------
# the standings (standings_table 0x27080)
# ---------------------------------------------------------------------------------------------

var standings_rows: Array = []      # standings_rows: per team [short name, division, GP, W, L, T, GF, GA, PTS, PCT]
var standings_order: Array = []     # standings_order: teams sorted (division, points, ...)

func standings_table() -> void:
	standings_rows.clear()
	var d := team_file()
	var stride := team_stride()
	for t in 26:
		var r := d.slice(t * stride, t * stride + 0x34)
		var gp := b8(r, 0x28)
		var w := b8(r, 0x29)
		var tie := b8(r, 0x2b)
		var pts := w * 2 + tie
		var pct := (gp + pts * 1000) / (gp * 2) if gp != 0 else 0
		standings_rows.append([cstr(r, 0x1a, 13), b8(r, 0x27), gp, w, b8(r, 0x2a), tie, s16(r, 0x2c), s16(r, 0x2e), pts, pct])
	standings_order = range(26)
	# cmp_standings: division, points, games played (fewer first), wins, goals for, goals against
	standings_order.sort_custom(func(a: int, b: int) -> bool:
		var ra: Array = standings_rows[a]
		var rb: Array = standings_rows[b]
		if ra[1] != rb[1]:
			return ra[1] < rb[1]
		if ra[8] != rb[8]:
			return ra[8] > rb[8]
		if ra[2] != rb[2]:
			return ra[2] < rb[2]
		if ra[3] != rb[3]:
			return ra[3] > rb[3]
		if ra[6] != rb[6]:
			return ra[6] > rb[6]
		if ra[7] != rb[7]:
			return ra[7] < rb[7]
		return a < b)
	_background(_source_bank())
	scr.capture_begin()
	_title(source_title(" Standings"))
	scr.setfont(fe.font_kaufm)
	scr.set_text_colors(0x40, 0x43)
	for side in 2:
		var cx := 0xa0 if side == 0 else 0x1e0
		var word := "Western" if side == 0 else "Eastern"
		_p(cx - (scr.textwidth(word) >> 1), 0x50, word)
		_p(cx - (scr.textwidth("Conference") >> 1), 0x60, "Conference")
	scr.setfont(fe.font_main)
	scr.set_text_colors(0x40, 0x43)
	var div_names := Exe.str_table(0xc68bc, 4)
	var y := 0xa7
	var x := 0
	var div := -1
	for k in 26:
		var row: Array = standings_rows[standings_order[k]]
		if row[1] != div:
			div = row[1] % 4
			x = Exe.i32(0xc6e3a + div * 4)
			y = Exe.i32(0xc6e4a + div * 4)
			_p(x, y, div_names[div])
			y += 0x12
			for c in [[0, "Team"], [100, "GP"], [0x78, " W"], [0x8c, " L"], [0xa0, " T"], [0xb4, " GF"], [0xd2, " GA"], [0xf0, "  P"], [0x10e, "  Pct"]]:
				_p(x + c[0], y, c[1])
			y += 0x25 - 0x12
			div = row[1]
		if Session.stats_league or row[2] != 0:
			_p(x, y, row[0])
			_pf(x + 100, y, 2, row[2])
			_pf(x + 0x78, y, 2, row[3])
			_pf(x + 0x8c, y, 2, row[4])
			_pf(x + 0xa0, y, 2, row[5])
			_pf(x + 0xb4, y, 3, row[6])
			_pf(x + 0xd2, y, 3, row[7])
			_pf(x + 0xf0, y, 3, row[8])
			if row[9] < 1000:
				_p(x + 0x10e, y, ".%03d" % (row[9] % 1000))
			else:
				_p(x + 0x10e, y, "%1d.%03d" % [row[9] / 1000, row[9] % 1000])
			y += 0xd
	scr.capture_stop()

## the row of a team in the standings (menu_page_a: the XOR bar of fillrect2)
func _standings_row_rect(k: int) -> Rect2i:
	var row: Array = standings_rows[standings_order[k]]
	var div: int = row[1]
	var y := 0xa5 if div % 2 == 0 else 0x14a
	var x := 0 if div < 2 else 0x140
	var i := k if k < 0xc else k - 0xc
	var n := 6 if k < 0xc else 7
	return Rect2i(x, y + (i % n) * 0xd, 0x140, 0xd)

func _xor_rect(r: Rect2i, v: int) -> void:
	for yy in range(r.position.y, r.end.y):
		for xx in range(r.position.x, r.end.x):
			scr.img.set_pixel(xx, yy, Color8(scr.getpixel(xx, yy) ^ v, 0, 0))
	scr.flush()

# ---------------------------------------------------------------------------------------------
# the team tables (team_stats_screen 0x235be)
# ---------------------------------------------------------------------------------------------

## kind: 0 scoring, 1 defense, 2 penalty killing, 3 power play, 4 penalties, 5 standings by conference
func team_stats_screen(kind: int) -> void:
	# the teams, their records and values, sorted as the original gathers them (StatsSort)
	var sched := PackedByteArray()
	if Session.stats_playoffs:
		sched = data("schedule.db" if Session.stats_league else "lssched.db")
	var table := StatsSort.team_table(kind, Session.stats_playoffs, Session.stats_league, team_file(), sched)
	var st: StatsSort = table["sorter"]
	var teams: Array = table["teams"]
	var recs: Array = []
	var value: Array = []
	for e in teams.size():
		recs.append(st.teams.slice(e * 0x4c, e * 0x4c + 0x4c))
		value.append(st.values[e])
	var order: Array = table["order"]
	var blk := team_block(PackedByteArray())
	_background(_source_bank())
	scr.capture_begin()
	var titles := Exe.str_table(0xc6b70, 6)
	_title(source_title(titles[kind]))
	scr.setfont(fe.font_main)
	scr.set_text_colors(0x40, 0x43)
	if recs.is_empty():
		scr.setfont(fe.font_kaufm)
		scr.print_centered_shadow(0xeb, "Stats Unavailable")
		scr.setfont(fe.font_main)
		scr.capture_stop()
		return
	var heads := Exe.str_table(0xc6b88, 24)
	var y := 0x5c
	if kind == 5:
		_p(0xa0 - (scr.textwidth("Western Conference") >> 1), y, "Western Conference")
		_p(0x1e0 - (scr.textwidth("Eastern Conference") >> 1), y, "Eastern Conference")
		y = 0x73
		_p(0xec, y, "GP")
		_p(0x21c, y, "GP")
		var col: String = heads[kind * 4 + (1 if Session.stats_playoffs else 0)]
		_p(0x114, y, col)
		_p(0x244, y, col)
	else:
		_p(0x154, y, "GP")
		_p(0x186, y, heads[kind * 4])
		_p(0x1b8, y, heads[kind * 4 + 1])
		if not Session.stats_playoffs or kind > 1:
			_p(0x1ea, y, heads[kind * 4 + 2])
		_p(0x21c, y, heads[kind * 4 + 3])
	y += 0x10
	if kind == 5:
		_conference_table(recs, teams, table, y)
	else:
		var rank := 1
		for k in order:
			var r: PackedByteArray = recs[k]
			if not Session.stats_league and b8(r, blk) == 0:
				continue
			_pf(0x50, y, 2, rank)
			rank += 1
			_p(0x6e, y, _team_name(r))
			_pf(0x154, y, 2, b8(r, blk))
			match kind:
				0, 1:
					_pf(0x186, y, 2, b8(r, blk + 1))
					_pf(0x1b8, y, 2, b8(r, blk + 2))
					if not Session.stats_playoffs:
						_pf(0x1ea, y, 2, b8(r, blk + 3))
					_pf(0x21c, y, 3, u16(r, blk + (4 if kind == 0 else 6)))
				2:
					_pf(0x186, y, 3, u16(r, blk + 0xe))
					_pf(0x1b8, y, 4, u16(r, blk + 0xc))
					_p(0x1ea, y, "%3d.%1d" % [value[k] / 10, value[k] % 10])
				3:
					_pf(0x186, y, 3, u16(r, blk + 0xa))
					_pf(0x1b8, y, 3, u16(r, blk + 8))
					_p(0x1ea, y, "%3d.%1d" % [value[k] / 10, value[k] % 10])
				4:
					_pf(0x186, y, 3, u16(r, blk + 0x10))
					_p(0x1b8, y, "%3d.%1d" % [value[k] / 10, value[k] % 10])
			y += 0xd
	scr.capture_stop()

func _team_name(r: PackedByteArray) -> String:
	if cstr(r, 0, 5).to_upper().begins_with("ANA"):
		return "Mighty Ducks of Anaheim"
	return cstr(r, 5, 21)

func _pts(r: PackedByteArray, blk: int) -> int:
	return b8(r, blk + 1) * 2 + b8(r, blk + 3)

## Team Standings by conference: the teams of each conference (the order of the '93 - '94
## standings comes from unk_c6af8 / unk_c6b30; a league's and the play-offs' are sorted, in a
## league a team of the other division moved up to second: StatsSort.team_table)
func _conference_table(recs: Array, teams: Array, table: Dictionary, y0: int) -> void:
	var blk := team_block(PackedByteArray())
	var west: Array = []
	var east: Array = []
	# the '93 - '94 lists name teams (99 none); a league's and the play-offs' name elements
	if not Session.stats_playoffs and not Session.stats_league:
		for t in table["west"]:
			west.append(teams.find(t) if t < 26 else -1)
		for t in table["east"]:
			east.append(teams.find(t) if t < 26 else -1)
	else:
		west = table["west"]
		east = table["east"]
	for side in 2:
		var list: Array = west if side == 0 else east
		var x0 := 0 if side == 0 else 0x140
		var y := y0
		var rank := 1
		for k in list:
			if k < 0:
				continue
			var r: PackedByteArray = recs[k]
			if not Session.stats_league and b8(r, blk) == 0:
				continue
			_pf(x0 + 0x1e, y, 2, rank)
			_p(x0 + 0x3c, y, _team_name(r))
			_pf(x0 + (0xec if side == 0 else 0xdc), y, 2, b8(r, blk))
			if not Session.stats_playoffs:
				_pf(x0 + (0x114 if side == 0 else 0x104), y, 3, _pts(r, blk))
			else:
				_pf(x0 + (0x114 if side == 0 else 0x104), y, 2, b8(r, blk + 1))
			rank += 1
			if rank == 9 and not Session.stats_playoffs:
				y += 0xd
				_p(x0 + 0x1e, y, "-".repeat(36))
			y += 0xd

# ---------------------------------------------------------------------------------------------
# the leaders (stats_table 0x25b24)
# ---------------------------------------------------------------------------------------------

## kind: 0 points, 1 goals, 2 assists, 3 power play goals, 4 short handed goals, 5 plus/minus,
## 6 penalty minutes, 7 shooting percentage, 8 goals against average, 9 wins, 10 save percentage
func stats_table(kind: int) -> void:
	# the 20 leaders as the original gathers them (StatsSort.leaders): [key record, stats block, value]
	var goalie := kind >= 8
	var res := StatsSort.leaders(kind, Session.stats_playoffs, Session.stats_league, team_file(), data("key.db"), stats_file())
	var st: StatsSort = res["sorter"]
	var size := 0x36 if goalie else 0x2f
	var blk := (0x16 if goalie else 0x12) if Session.stats_playoffs else 0
	var table := st.goalies if goalie else st.skaters
	var td := team_file()
	var stride := team_stride()
	var rows: Array = []
	for e: int in res["order"]:
		var full := table.slice(e * size, e * size + size)
		rows.append([res["keys"][e], full.slice(blk, blk + (0x16 if goalie else 0x12)), st.values[e]])
	_background(_source_bank())
	scr.capture_begin()
	_title(source_title(Exe.str_ptr(0xc6c14 + kind * 4)))
	scr.setfont(fe.font_main)
	scr.set_text_colors(0x40, 0x43)
	if rows.is_empty():
		scr.setfont(fe.font_kaufm)
		scr.print_centered_shadow(0xeb, "Stats Unavailable")
		scr.setfont(fe.font_main)
		scr.capture_stop()
		return
	var y := 0x5c
	_p(10, y, "POS")
	_p(0x32, y, "NO")
	_p(0x50, y, "PLAYER")
	_p(0xfa, y, "TEAM")
	_p(0x172, y, "GP")
	var heads := []
	for i in 5:
		heads.append(Exe.str_ptr(0xc6c40 + (kind * 5 + i) * 4))
	_p(0x19a, y, heads[0])
	_p(0x1cc, y, heads[1])
	_p(500, y, heads[2])
	if kind != 9 or not Session.stats_playoffs:
		_p(0x21c, y, heads[3])
	_p(0x24e, y, heads[4])
	y += 0x10
	for row: Array in rows:
		var k: PackedByteArray = row[0]
		var r: PackedByteArray = row[1]
		_p(10, y, char(k[2]))
		if k[1] < 100:
			_pf(0x32, y, 2, k[1])
		_p(0x50, y, format_name(cstr(k, 3, 16), cstr(k, 0x13, 16), 0xa6))
		_p(0xfa, y, cstr(td, k[0] * stride + 0x1a, 13))
		_pf(0x172, y, 2, s16(r, 0))
		if not goalie:
			_pf(0x19a, y, 3, u16(r, 2))
			_pf(0x1cc, y, 3, u16(r, 4))
			_pf(500, y, 3, u16(r, 6))
			match kind:
				3:
					_pf(0x21c, y, 2, u16(r, 8))
				4:
					_pf(0x21c, y, 3, u16(r, 0xa))
				5:
					_pf(0x21c, y, 4, s16(r, 0x10))
				6:
					_pf(0x21c, y, 3, u16(r, 0xc))
				7:
					_pf(0x21c, y, 5, u16(r, 0xe))
					_p(0x24e, y, "%3d.%1d" % [row[2] / 10, row[2] % 10])
		else:
			_pf(0x19a, y, 4, u16(r, 0xc))
			match kind:
				8:
					_pf(0x1cc, y, 3, u16(r, 0xe))
					_p(500, y, "%2d.%02d" % [u16(r, 0x10) / 100, u16(r, 0x10) % 100])
				9:
					_pf(0x1cc, y, 2, u16(r, 2))
					_pf(500, y, 2, u16(r, 4))
					if not Session.stats_playoffs:
						_pf(0x21c, y, 2, u16(r, 6))
				10:
					_pf(0x1cc, y, 3, u16(r, 0xe))
					_pf(500, y, 4, u16(r, 0x12))
					var pct := u16(r, 0x14)
					_p(0x21c, y, ("%1d.%03d" % [pct / 1000, pct % 1000]) if pct > 999 else (".%03d" % pct))
		y += 0xd
	scr.capture_stop()

# ---------------------------------------------------------------------------------------------
# a team's roster (player_stats_screen 0x244e2)
# ---------------------------------------------------------------------------------------------

## the roster of a team of TEAMS.DB with the statistics of the source: skaters by points, goalies
## by goals against average
func player_stats_screen(team: int) -> void:
	var teams := data("teams.db")
	var rec := teams.slice(team * 0x2e8, (team + 1) * 0x2e8)
	# the roster as the original gathers and sorts it (StatsSort.roster): [roster index, key, block]
	var res := StatsSort.roster(rec, Session.stats_playoffs, Session.stats_league, data("key.db"), stats_file())
	var sorter: StatsSort = res["sorter"]
	roster_keys.clear()
	for i in 28:
		roster_keys.append(res["keys"][i] if res["keys"][i] != null else PackedByteArray())
	var skaters: Array = []
	var goalies: Array = []
	for g in 2:
		var size := 0x36 if g == 1 else 0x2f
		var blk := ((0x16 if g == 1 else 0x12) if Session.stats_playoffs else 0)
		var table := sorter.goalies if g == 1 else sorter.skaters
		var slots: Array = res["goalie_roster" if g == 1 else "skater_roster"]
		for e: int in res["goalies" if g == 1 else "skaters"]:
			var full := table.slice(e * size, e * size + size)
			var i: int = slots[e]
			(goalies if g == 1 else skaters).append([i, roster_keys[i], full.slice(blk, blk + (0x16 if g == 1 else 0x12))])
	roster_order = skaters
	goalie_order = goalies
	var abbrev := cstr(rec, 0, 5)
	var bg := fe.bank("emb" + abbrev)
	_background("emb" + abbrev if bg != null else _source_bank(), 6)
	scr.capture_begin()
	scr.setfont(fe.font_kaufm)
	scr.set_text_colors(0x40, 0x43)
	var title := "Mighty Ducks of Anaheim" if team == 0x18 else cstr(rec, 5, 21)
	scr.print_outlined(300 - (scr.textwidth(title) >> 1), 0x1b, title)
	scr.setfont(fe.font_main)
	scr.set_text_colors(0x40, 0x43)
	var y := 0x30
	for c in [[0x14, "Pos"], [0x42, "No"], [0x60, "Name"], [0x10e, "GP"], [0x136, " G"], [0x15e, " A"], [0x186, "PT"], [0x1ae, "Shots"], [0x1e8, "PIM"], [0x210, "+/-"]]:
		_p(c[0], y, c[1])
	y = 0x40
	for row: Array in skaters:
		var k: PackedByteArray = row[1]
		var r: PackedByteArray = row[2]
		_p(0x14, y, char(k[2]))
		if k[1] < 100:
			_pf(0x42, y, 2, k[1])
		_p(0x60, y, format_name(cstr(k, 3, 16), cstr(k, 0x13, 16), 0xa6))
		_pf(0x10e, y, 2, s16(r, 0))
		_pf(0x136, y, 3, u16(r, 2))
		_pf(0x15e, y, 3, u16(r, 4))
		_pf(0x186, y, 3, u16(r, 6))
		_pf(0x1ae, y, 5, u16(r, 0xe))
		_pf(0x1e8, y, 3, u16(r, 0xc))
		_pf(0x210, y, 4, s16(r, 0x10))
		y += 0xd
	y = 0x195
	for c in [[0x14, "Pos"], [0x42, "No"], [0x60, "Name"], [0x10e, "GP"], [0x136, "Min"], [0x15e, "GAA"], [400, " W"], [0x1ae, " L"], [0x1ea, "GA"], [0x20e, " SA"], [0x240, "PCT"]]:
		_p(c[0], y, c[1])
	if not Session.stats_playoffs:
		_p(0x1cc, y, " T")
	y += 0x10
	for row: Array in goalies:
		var k: PackedByteArray = row[1]
		var r: PackedByteArray = row[2]
		_p(0x14, y, char(k[2]))
		if k[1] < 100:
			_pf(0x42, y, 2, k[1])
		_p(0x60, y, format_name(cstr(k, 3, 16), cstr(k, 0x13, 16), 0xa6))
		_pf(0x10e, y, 2, s16(r, 0))
		_pf(0x136, y, 4, u16(r, 0xc))
		_p(0x15e, y, "%2d.%02d" % [u16(r, 0x10) / 100, u16(r, 0x10) % 100])
		_pf(400, y, 2, u16(r, 2))
		_pf(0x1ae, y, 2, u16(r, 4))
		if not Session.stats_playoffs:
			_pf(0x1cc, y, 2, u16(r, 6))
		_pf(0x1ea, y, 3, u16(r, 0xe))
		_pf(0x20e, y, 4, u16(r, 0x12))
		var pct := u16(r, 0x14)
		_p(0x240, y, ("%1d.%03d" % [pct / 1000, pct % 1000]) if pct > 999 else (".%03d" % pct))
		y += 0xd
	scr.capture_stop()

## the row under (x, y) of the roster screen: [true, key record] or []
func _roster_row_at(y: int) -> PackedByteArray:
	if y >= 0x40 and y < 0x40 + roster_order.size() * 0xd:
		return roster_order[(y - 0x40) / 0xd][1]
	var gy := 0x195 + 0x10
	if y >= gy and y < gy + goalie_order.size() * 0xd:
		return goalie_order[(y - gy) / 0xd][1]
	return PackedByteArray()

# ---------------------------------------------------------------------------------------------
# the player and goalie cards (player_card_screen 0x21cde, goalie_card_screen 0x22581)
# ---------------------------------------------------------------------------------------------

func player_card_screen(goalie: bool) -> void:
	var k := player
	var off := stats_offset(k)
	var n := 0x36 if goalie else 0x28
	var st := stats_file().slice(off, off + n) if off >= 0 else PackedByteArray()
	st.resize(0x36)
	var att_off := k.decode_s32(0x24)
	var att := data("att.db").slice(att_off, att_off + 0x14)
	att.resize(0x14)
	var team := k[0]
	var abbrev := cstr(data("carteams.db"), team * 0x4c, 5)
	var bg := fe.bank("emb" + abbrev)
	_background("emb" + abbrev if bg != null else _source_bank(), 0, "")
	# the portrait (PORTRnnnn.QFS of the CD) is not part of the installation: the stats bar
	var ps := fe.bank("pstatbar")
	if ps != null:
		var bar := ps.find("pst2")
		if bar != null:
			scr.drawshape_remap(bar, bar.x, bar.y)
	scr.setfont(fe.font_kaufm)
	scr.set_text_colors(0x40, 0x43)
	scr.print_outlined(0x140 - (scr.textwidth("Player Stats") >> 1), 0x52, "Player Stats")
	scr.capture_begin()
	scr.set_text_colors(0x40, 0x43)
	scr.print_centered_shadow(0x98, "%s %s" % [cstr(k, 3, 16), cstr(k, 0x13, 16)])
	var line := str(k[1])
	match k[2]:
		0x43:
			line += " Center"
		0x44:
			line += " Defense"
		0x4c:
			line += " Left Wing"
		0x52:
			line += " Right Wing"
		0x47:
			line += " Goaltender"
	scr.print_centered_shadow(0xb2, line)
	scr.setfont(fe.font_main)
	var labels := Exe.str_table(0xc68cc, 2)
	var y := 0xf3
	if not goalie:
		for c in [[0x82, "GP"], [0xaa, " G"], [0xd2, " A"], [0xfa, "Pt"], [0x122, "PIM"], [0x14a, "+/-"], [0x186, "PPG"], [0x1ae, "SHG"], [0x1d6, "Shots"], [0x212, " Pct"]]:
			_p(c[0], y, c[1])
		y = 0x103
		for blk in [0, 0x12]:
			_p(0x32, y, labels[blk / 0x12])
			_pf(0x82, y, 2, s16(st, blk))
			_pf(0xaa, y, 3, u16(st, blk + 2))
			_pf(0xd2, y, 3, u16(st, blk + 4))
			_pf(0xfa, y, 3, u16(st, blk + 6))
			_pf(0x122, y, 3, u16(st, blk + 0xc))
			_pf(0x14a, y, 4, s16(st, blk + 0x10))
			_pf(0x186, y, 3, u16(st, blk + 8))
			_pf(0x1ae, y, 3, u16(st, blk + 0xa))
			_pf(0x1d6, y, 5, u16(st, blk + 0xe))
			var shots := u16(st, blk + 0xe)
			var pct := (u16(st, blk + 2) * 1000 + shots / 2) / shots if shots != 0 else 0
			_p(0x212, y, "%3d.%1d" % [pct / 10, pct % 10])
			y += 0xd
	else:
		for c in [[0x82, "GP"], [0xaa, "Min"], [0xe6, "GAA"], [0x118, " W"], [0x136, " L"], [0x154, " T"], [0x172, "GA"], [0x19a, " SA"], [0x1cc, "PCT"]]:
			_p(c[0], y, c[1])
		y = 0x103
		for blk in [0, 0x16]:
			_p(0x32, y, labels[blk / 0x16])
			_pf(0x82, y, 2, s16(st, blk))
			_pf(0xaa, y, 4, u16(st, blk + 0xc))
			_p(0xe6, y, "%2d.%02d" % [u16(st, blk + 0x10) / 100, u16(st, blk + 0x10) % 100])
			_pf(0x118, y, 2, u16(st, blk + 2))
			_pf(0x136, y, 2, u16(st, blk + 4))
			if blk == 0:
				_pf(0x154, y, 2, u16(st, blk + 6))
			_pf(0x172, y, 3, u16(st, blk + 0xe))
			_pf(0x19a, y, 4, u16(st, blk + 0x12))
			var pct := u16(st, blk + 0x14)
			_p(0x1cc, y, ("%1d.%03d" % [pct / 1000, pct % 1000]) if pct > 999 else (".%03d" % pct))
			y += 0xd
	y = 0x131
	scr.print_centered_shadow(y, "Ratings")
	y = 0x143
	_p(0x1e, y, "Shoots" if not goalie else "Glove")
	_p(0x10e, y, "R" if att[0] == 0 else "L")
	y += 0xd
	var names := Exe.str_table(0xc6a64, 14)
	var idx := Exe.bytes(0xc6a9c, 14)
	var x := 0
	for i in 14:
		if i == 7:
			x = 0x136
			y -= 0x68
		_p(x + 0x1e, y, names[i])
		_pf(x + 0x10e, y, 3, (att[idx[i]] + 5) * 5 if idx[i] < att.size() else 0)
		y += 0xd
	scr.capture_stop()

# ---------------------------------------------------------------------------------------------
# the hubs: the screens with their menus
# ---------------------------------------------------------------------------------------------

## the source of the statistics changes: the screen is drawn again (stats_source_9394_season ...)
func _redraw_current() -> void:
	if not hub_active or not current.is_valid():
		return
	await scr.fade_out(16)
	await current.call(current_arg)
	await scr.fade_in(stats_palette(), 16)

func _set_source(playoffs: bool, league: bool) -> int:
	if Session.stats_playoffs == playoffs and Session.stats_league == league:
		return 0
	Session.stats_playoffs = playoffs
	Session.stats_league = league
	update_source_marks()
	forget_files()
	await _redraw_current()
	return 0

## the marks of the Statistics Type list (glyph 1 the source shown, 2 the others)
func update_source_marks() -> void:
	var marks := [not Session.stats_league and not Session.stats_playoffs, not Session.stats_league and Session.stats_playoffs,
		false, Session.stats_league and not Session.stats_playoffs, false, false, Session.stats_league and Session.stats_playoffs]
	for i in 7:
		var it := Menus.at(0xc67b1 + i * 32)
		if it == null or it.text.begins_with("-"):
			continue
		var body := it.text.substr(1)
		if Session.league_name != "":
			body = body.replace("WWWWWWWW", Session.league_name)
		it.text = ("\u0001" if marks[i] else "\u0002") + body

func stats_source_9394_season() -> int:
	return await _set_source(false, false)

func stats_source_9394_playoffs() -> int:
	return await _set_source(true, false)

func stats_source_league_season() -> int:
	return await _set_source(false, true)

func stats_source_league_playoffs() -> int:
	return await _set_source(true, true)

func stats_source_league_season_playoffs() -> int:
	return await _set_source(true, true)

## a hub (exh_hub_sports_central / _playoff_tree / _league_calendar): the screen, its menu bar,
## the palette of EMBPAL; Return To leaves (back to the desk, 2)
func _hub(screen: Callable, arg: int, menu_addr: int) -> int:
	hub_active = true
	current = screen
	current_arg = arg
	update_source_marks()
	await fe.leave_screen(70)
	await screen.call(arg)
	var root := Menus.list(menu_addr, 4)
	ui.draw_menu_items(root, C_LIGHT, C_FACE, C_DARK)
	await scr.fade_in(stats_palette(), 16)
	await ui.run_menu(root, C_LIGHT, C_FACE, C_DARK, fe.dispatch)
	await scr.fade_out(16)
	hub_active = false
	current = Callable()
	return 2

func _team_screen(kind: int) -> int:
	if hub_active and current == team_stats_screen:
		current_arg = kind
		await _redraw_current()
		return 0
	if hub_active:
		current = team_stats_screen
		current_arg = kind
		await _redraw_current()
		return 0
	return await _hub(team_stats_screen, kind, 0xcf78f)

func _leaders(kind: int) -> int:
	if hub_active:
		current = stats_table
		current_arg = kind
		await _redraw_current()
		return 0
	return await _hub(stats_table, kind, 0xcf80f if kind < 8 else 0xcf88f)

func team_stats_standings() -> int:
	return await _team_screen(5)

func team_stats_scoring() -> int:
	return await _team_screen(0)

func team_stats_defense() -> int:
	return await _team_screen(1)

func team_stats_penalty_killing() -> int:
	return await _team_screen(2)

func team_stats_power_play() -> int:
	return await _team_screen(3)

func team_stats_penalties() -> int:
	return await _team_screen(4)

func leaders_points() -> int:
	return await _leaders(0)

func leaders_goals() -> int:
	return await _leaders(1)

func leaders_assists() -> int:
	return await _leaders(2)

func leaders_pp_goals() -> int:
	return await _leaders(3)

func leaders_sh_goals() -> int:
	return await _leaders(4)

func leaders_plus_minus() -> int:
	return await _leaders(5)

func leaders_penalty_minutes() -> int:
	return await _leaders(6)

func leaders_shooting_pct() -> int:
	return await _leaders(7)

func leaders_gaa() -> int:
	return await _leaders(8)

func leaders_wins() -> int:
	return await _leaders(9)

func leaders_save_pct() -> int:
	return await _leaders(10)

## hub_sports_desk (0x179b6): Return To Sports Desk
func hub_sports_desk() -> int:
	next_screen = 1
	return 1

## hub_overall_standings (0x179d0)
func hub_overall_standings() -> int:
	next_screen = 2
	return 1

## hub_team_roster (0x179eb) / menu_show_team_roster (0x18d03)
func hub_team_roster() -> int:
	next_screen = 3
	return 1

func menu_show_team_roster() -> int:
	return hub_team_roster()

## menu_show_player_stats (0x18d0d): the card of the player picked on the roster
func menu_show_player_stats() -> int:
	if player.size() < 3:
		return 0
	next_screen = 4 if player[2] == 0x47 else 5
	return 1

## the Standings ... entry: exh_hub_stats (0x2051a) / hub_stats (0x20eb7): the standings, then the
## roster of the team picked, then a player's card, until Return To Sports Desk
func exh_hub_stats() -> int:
	return await _standings_hub()

func hub_stats() -> int:
	return await _standings_hub()

func cal_hub_stats() -> int:
	return await _standings_hub()

func _standings_hub() -> int:
	hub_active = true
	update_source_marks()
	await fe.leave_screen(70)
	next_screen = 2
	var pal := stats_palette()
	while next_screen != 1:
		match next_screen:
			2:
				current = func(_a): standings_table()
				standings_table()
				var root := Menus.list(0xcf54f, 4)
				ui.draw_menu_items(root, C_LIGHT, C_FACE, C_DARK)
				await scr.fade_in(pal, 16)
				next_screen = 1
				await _menu_with_picker(root, true)
			3:
				current = func(_a): player_stats_screen(selected_team)
				player_stats_screen(selected_team)
				var root := Menus.list(0xcf6af, 4)
				ui.draw_menu_items(root, C_LIGHT, C_FACE, C_DARK)
				await scr.fade_in(pal, 16)
				next_screen = 1
				await _menu_with_picker(root, false)
			4, 5:
				var g := next_screen == 4
				current = func(_a): player_card_screen(g)
				player_card_screen(g)
				var root := Menus.list(0xcf74f, 2)
				ui.draw_menu_items(root, C_LIGHT, C_FACE, C_DARK)
				await scr.fade_in(pal, 16)
				next_screen = 1
				await ui.run_menu(root, C_LIGHT, C_FACE, C_DARK, fe.dispatch)
		await scr.fade_out(16)
	hub_active = false
	current = Callable()
	return 2

## menu_page_a / menu_page_b: run_menu where a click outside the menus picks a team of the
## standings (the bar under the selected one) or a player of the roster
func _menu_with_picker(root: Array, standings: bool) -> void:
	var sel := -1
	if standings:
		sel = standings_order.find(selected_team)
		if sel >= 0:
			_xor_rect(_standings_row_rect(sel), 0x80)
	var picker := func(e: Dictionary) -> void:
		if standings:
			for k in 26:
				if _standings_row_rect(k).has_point(Vector2i(e["x"], e["y"])):
					if sel >= 0:
						_xor_rect(_standings_row_rect(sel), 0x80)
					sel = k
					selected_team = standings_order[k]
					_xor_rect(_standings_row_rect(sel), 0x80)
					return
		else:
			var k := _roster_row_at(e["y"])
			if k.size() >= 3:
				player = k
	await ui.run_menu(root, C_LIGHT, C_FACE, C_DARK, fe.dispatch, Callable(), [1], Callable(), picker)

## menu_output_current_data (0x18d7f): the text of the screen into NAME.OUT (export_stats_dialog)
func menu_output_current_data() -> int:
	var dc := [fe.dlg_face, fe.dlg_light, fe.dlg_dark, fe.dlg_text, fe.dlg_shadow]
	fe.set_dialog_colors(0x41, 0x40, 0x42, 0x40, 0)
	var name: String = await fe.text_entry_dialog("Please enter output file name", 8)
	if name != "":
		var path := "user://" + name.to_upper() + ".OUT"
		var ok := true
		if FileAccess.file_exists(path):
			ok = await fe.message_dialog_buttons(["The file you specified already exists!", "Do you want to overwrite the old file?"], FrontEnd.buttons_at(0xc6499 - 0x1c, 2)) == 1
		if ok:
			var f := FileAccess.open(path, FileAccess.WRITE)
			if f != null:
				f.store_string(scr.capture_text() + "\n")
				f = null
				await fe.message_dialog(["The stats were successfully written"], ["OK"])
			else:
				await fe.message_dialog(["ERROR : Output file was not successfully written"], ["OK"])
	fe.set_dialog_colors(dc[0], dc[1], dc[2], dc[3], dc[4])
	return 0
