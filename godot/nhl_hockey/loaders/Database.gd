class_name Database
## The team and player databases as read by the roster loader of HOCKEY.EXE (db_open_files /
## db_load_team_roster / db_read_player, see re/nhl_hockey/FORMATS.md):
##  TEAMS.DB  28 records of 0x2e8 bytes: +0 abbreviation (5), +5 city (21), +0x1a name (13),
##            +0x4c 25 x i32 skater keys, +0xb0 3 x i32 goalie keys (-1 = empty), +0xbc lines:
##            4 forward lines x 3 (LW C RW), 3 defence pairs x 2, 2 power play units x 5,
##            2 penalty killing units x 4, 2 goalies, 6 extra slots (roster indices, 0x64 = unset)
##  KEY.DB    player records of 0x34 bytes at the key offset: +1 jersey number, +2 position
##            letter, +3 first name (16), +0x13 last name (16), +0x24 i32 offset into ATT.DB,
##            +0x28 into CAREER.DB, +0x2c into SEASON.DB
##  ATT.DB    ratings: 0x14 bytes per skater, 0x10 per goalie (see Sim.dress_player)

class Player:
	var first: String
	var last: String
	var number: int
	var position: String        # C L R D G
	var ratings: PackedByteArray
	var goalie: bool
	var roster_idx: int         # 0..24 skaters, 25..27 goalies
	var key: int = -1           # the record's offset in KEY.DB

	func full_name() -> String:
		return first + " " + last

class TeamInfo:
	var index: int
	var abbrev: String
	var city: String
	var name: String
	var skaters: Array = []     # 25 x Player (null when the slot is empty)
	var goalies: Array = []     # 3 x Player
	var forwards: Array = []    # 4 x [LW, C, RW] roster indices
	var defense: Array = []     # 3 x [LD, RD]
	var power_play: Array = []  # 2 x 5
	var penalty_kill: Array = []# 2 x 4
	var goalie_order: Array = []# 2 roster indices (25..27)
	var line_table: PackedByteArray = PackedByteArray()   # the raw 0x30 bytes at +0xbc (line_energy / assign_line_positions index it by offset)
	# +0x2dc..+0x2df rating adjustments of put_player_on_ice: trailing, leading, at home, away
	# (each mapped to 0 below 4, 1 below 7, else 2; the trailing and away values minus 2)
	var factors: PackedByteArray = PackedByteArray([7, 7, 7, 3])

	func player(roster_idx: int) -> Player:
		if roster_idx >= 25:
			return goalies[roster_idx - 25] if roster_idx - 25 < goalies.size() else null
		return skaters[roster_idx] if roster_idx >= 0 and roster_idx < skaters.size() else null

const TEAM_RECORD := 0x2e8
const KEY_RECORD := 0x34

var teams_db: PackedByteArray
var key_db: PackedByteArray
var att_db: PackedByteArray

static func open(teams: PackedByteArray, key: PackedByteArray, att: PackedByteArray) -> Database:
	if teams.size() < TEAM_RECORD or key.size() < KEY_RECORD:
		return null
	var db := Database.new()
	db.teams_db = teams
	db.key_db = key
	db.att_db = att
	return db

func team_count() -> int:
	return teams_db.size() / TEAM_RECORD

static func cstring(data: PackedByteArray, pos: int, maxlen: int) -> String:
	var end := pos
	while end < pos + maxlen and end < data.size() and data[end] != 0:
		end += 1
	return data.slice(pos, end).get_string_from_ascii()

func load_team(idx: int) -> TeamInfo:
	if idx < 0 or idx >= team_count():
		return null
	var base := idx * TEAM_RECORD
	var t := TeamInfo.new()
	t.index = idx
	t.abbrev = cstring(teams_db, base, 5)
	t.city = cstring(teams_db, base + 5, 21)
	t.name = cstring(teams_db, base + 0x1a, 13)
	for i in 25:
		t.skaters.append(read_player(teams_db.decode_s32(base + 0x4c + i * 4), false, i))
	for i in 3:
		t.goalies.append(read_player(teams_db.decode_s32(base + 0xb0 + i * 4), true, 25 + i))
	t.line_table = teams_db.slice(base + 0xbc, base + 0xec)
	t.factors = teams_db.slice(base + 0x2dc, base + 0x2e0)
	var p := base + 0xbc
	for i in 4:
		t.forwards.append([teams_db[p], teams_db[p + 1], teams_db[p + 2]])
		p += 3
	for i in 3:
		t.defense.append([teams_db[p], teams_db[p + 1]])
		p += 2
	for i in 2:
		t.power_play.append([teams_db[p], teams_db[p + 1], teams_db[p + 2], teams_db[p + 3], teams_db[p + 4]])
		p += 5
	for i in 2:
		t.penalty_kill.append([teams_db[p], teams_db[p + 1], teams_db[p + 2], teams_db[p + 3]])
		p += 4
	t.goalie_order = [teams_db[p], teams_db[p + 1]]
	return t

func read_player(key: int, goalie: bool, roster_idx: int) -> Player:
	if key < 0 or key + KEY_RECORD > key_db.size():
		return null
	var p := Player.new()
	p.number = key_db[key + 1]
	p.position = char(key_db[key + 2])
	p.first = cstring(key_db, key + 3, 16)
	p.last = cstring(key_db, key + 0x13, 16)
	p.goalie = goalie
	p.roster_idx = roster_idx
	p.key = key
	var att := key_db.decode_s32(key + 0x24)
	var n := 0x10 if goalie else 0x14
	if att >= 0 and att + n <= att_db.size():
		p.ratings = att_db.slice(att, att + n)
	else:
		p.ratings = PackedByteArray()
		p.ratings.resize(n)
		p.ratings.fill(8)
	return p
