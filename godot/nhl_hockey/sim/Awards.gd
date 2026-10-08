class_name Awards
## The season's awards of a league (load_award_stats 0x1205d), ported literally: TEAMS.DB, KEY.DB
## and SEASON.DB of the league are read team by team; the teams' records give the Presidents'
## Trophy (points, then the winning percentage of the decided games, then the wins) and the
## Stanley Cup (the play-off wins); each skater's season record (KEY +0x2c) with games played the
## Hart (goals), the Art Ross (points), the Norris (a defenceman's points), the Selke (a forward's
## plus/minus), the Calder (a rookie's points, the record's last byte), the Conn Smythe (play-off
## points); each goalie's the Vezina (wins, then the save percentage) and the Jennings (the goals
## against average, 25 games); a player of either the EASN award (the sum of the record's three
## last words). A tie goes to the one with fewer games (more minutes for the Jennings); the first
## found keeps an exact tie. A goalie who takes the EASN award is recorded with the key of the last
## skater read (the original copies the skater's key buffer). A read past the end of a file stops
## the reading (the error is returned and the awards are not shown); a negative offset other than -1
## reads on from where the file is.
##
## The original keeps the winners in static memory: an award nobody wins this time shows the last
## winner (zeros at first). So does this class (static), until reset() for the tests.

const NAMES := ["hart", "ross", "norr", "selk", "vezi", "jenn", "cald", "pres", "conn", "easn", "stan"]
const KIND := [1, 1, 1, 1, 0, 0, 1, 2, 1, 1, 2]       # unk_c5244: 1 a skater, 0 a goalie, 2 a team

static var keys: Array = []          # unk_d9558: the KEY.DB record of each award's player (0x34 apart)
static var stats: Array = []         # off_c524f: the season record of each (0x2f a skater, 0x36 a goalie)
static var easn_skater := true       # byte_c524d: the EASN award's record is a skater's (else a goalie's)
static var easn_records := [PackedByteArray(), PackedByteArray()]   # unk_d98c3 (skater), unk_d9794 (goalie)
static var presidents := PackedByteArray()   # unk_d9270: the team record of the Presidents' Trophy
static var stanley := PackedByteArray()      # unk_d8f88: the team record of the Stanley Cup
static var team_names: Array = []            # unk_ddac4: the 26 teams' names (0x15 bytes each)

static func reset() -> void:
	keys = []
	stats = []
	for i in 11:
		var k := PackedByteArray()
		k.resize(0x34)
		keys.append(k)
		var s := PackedByteArray()
		s.resize(0x36 if KIND[i] == 0 else 0x2f)
		stats.append(s)
	easn_skater = true
	easn_records = [PackedByteArray(), PackedByteArray()]
	easn_records[0].resize(0x2f)
	easn_records[1].resize(0x36)
	stats[9] = easn_records[0]
	presidents = PackedByteArray()
	presidents.resize(0x2e8)
	stanley = PackedByteArray()
	stanley.resize(0x2e8)
	team_names = []
	for t in 26:
		var n := PackedByteArray()
		n.resize(0x15)
		team_names.append(n)

## the kind of an award (unk_c5244): 1 a skater's, 0 a goalie's, 2 a team's; the EASN award's is
## byte_c524d, the next byte of the table
static func kind(i: int) -> int:
	if i == 9:
		return 1 if easn_skater else 0
	return KIND[i]

## the record of the EASN award as the screen reads it (off_c5273)
static func easn_record() -> PackedByteArray:
	return easn_records[0] if easn_skater else easn_records[1]

## file_read (0x145a2): seeks to `off` unless it is negative (then it reads on from where the file
## is), reads `size` bytes into the buffer (a short read leaves the rest as it was); 0, or 1 short
static func _read(f: StatsSort.CFile, buf: PackedByteArray, off: int, size: int) -> int:
	f.lseek(off)
	return 0 if f.read(buf, size) == size else 1

static func _u16(b: PackedByteArray, o: int) -> int:
	return b.decode_u16(o)

## load_award_stats (0x1205d): 0, or 1 when a read failed (the awards are not shown). The team names
## (db_open_check, 0x15 bytes at +5 of each team's record) go to team_names first.
static func load(teams: PackedByteArray, key_db: PackedByteArray, season: PackedByteArray) -> int:
	if keys.is_empty():
		reset()
	var err := 0
	var nf := StatsSort.CFile.new(teams)
	for t in 26:
		var name: PackedByteArray = team_names[t]
		err = _read(nf, name, t * 0x2e8 + 5, 0x15)
		if err != 0:
			return err
	var tf := StatsSort.CFile.new(teams)
	var kf := StatsSort.CFile.new(key_db)
	var sf := StatsSort.CFile.new(season)
	var found := PackedByteArray()
	found.resize(11)
	var best_pts := 0
	var best_pct := 0
	var best_cup := 0
	# the routine's buffers on the stack (zeroed here) keep what a short read left
	var team := PackedByteArray()
	team.resize(0x2e8)
	var skey := PackedByteArray()        # [esp+0x354]: the last skater's key (the EASN bug)
	skey.resize(0x34)
	var srec := PackedByteArray()
	srec.resize(0x2f)
	var gkey := PackedByteArray()
	gkey.resize(0x34)
	var grec := PackedByteArray()
	grec.resize(0x36)
	var t := 0
	while t < 26 and err == 0:
		err = _read(tf, team, t * 0x2e8, 0x2e8)
		# (the team's awards are decided even when the read failed)
		# the Presidents' Trophy: points, the percentage of the decided games won, the wins
		var w: int = team[0x29]
		var l: int = team[0x2a]
		var pts: int = w * 2 + team[0x2b]
		var pct := 0
		if w != 0 or l != 0:
			pct = w * 100 / (w + l)
		if found[7] == 0 or pts > best_pts or (pts == best_pts and (pct > best_pct
				or (pct == best_pct and w > presidents[0x29]))):
			presidents = team.duplicate()
			best_pts = pts
			best_pct = pct
			found[7] = 1
		# the Stanley Cup: the play-off wins
		if found[10] == 0 or team[0x3b] > best_cup:
			stanley = team.duplicate()
			best_cup = team[0x3b]
			found[10] = 1
		var i := 0
		while i < 25 and err == 0:
			var off: int = team.decode_s32(0x4c + i * 4)
			i += 1
			if off == -1:
				continue
			err = _read(kf, skey, off, 0x34)
			if err == 0:
				err = _read(sf, srec, skey.decode_s32(0x2c), 0x2f)
			if err != 0:
				continue
			var gp := _u16(srec, 0)
			if gp == 0:
				continue
			var k := skey
			var rec := srec
			var pos: int = k[2]
			_take_if(found, 0, k, rec, _u16(rec, 2) > _u16(stats[0], 2) or (_u16(rec, 2) == _u16(stats[0], 2) and gp < _u16(stats[0], 0)))
			_take_if(found, 1, k, rec, _u16(rec, 6) > _u16(stats[1], 6) or (_u16(rec, 6) == _u16(stats[1], 6) and gp < _u16(stats[1], 0)))
			if pos == 0x44:
				_take_if(found, 2, k, rec, _u16(rec, 6) > _u16(stats[2], 6) or (_u16(rec, 6) == _u16(stats[2], 6) and gp < _u16(stats[2], 0)))
			if pos == 0x4c or pos == 0x52 or pos == 0x43:
				var pm: int = rec.decode_s16(0x10)
				var bpm: int = (stats[3] as PackedByteArray).decode_s16(0x10)
				_take_if(found, 3, k, rec, pm > bpm or (pm == bpm and gp < _u16(stats[3], 0)))
			if pos != 0x47 and rec[0x2e] != 0:
				_take_if(found, 6, k, rec, _u16(rec, 6) > _u16(stats[6], 6) or (_u16(rec, 6) == _u16(stats[6], 6) and gp < _u16(stats[6], 0)))
			_take_if(found, 8, k, rec, _u16(rec, 0x18) > _u16(stats[8], 0x18)
				or (_u16(rec, 0x18) == _u16(stats[8], 0x18) and _u16(rec, 0x12) < _u16(stats[8], 0x12)))
			_easn(found, rec, k, 0x28, true)
		i = 0
		while i < 3 and err == 0:
			var off: int = team.decode_s32(0xb0 + i * 4)
			i += 1
			if off == -1:
				continue
			err = _read(kf, gkey, off, 0x34)
			if err == 0:
				err = _read(sf, grec, gkey.decode_s32(0x2c), 0x36)
			if err != 0:
				continue
			var gp := _u16(grec, 0)
			if gp == 0:
				continue
			var rec := grec
			_take_if(found, 4, gkey, rec, _u16(rec, 2) > _u16(stats[4], 2)
				or (_u16(rec, 2) == _u16(stats[4], 2) and _u16(rec, 0x14) > _u16(stats[4], 0x14)))
			if gp >= 0x19:
				_take_if(found, 5, gkey, rec, _u16(rec, 0x10) < _u16(stats[5], 0x10)
					or (_u16(rec, 0x10) == _u16(stats[5], 0x10) and _u16(rec, 0xc) > _u16(stats[5], 0xc)))
			_easn(found, rec, skey, 0x30, false)
		t += 1
	return err

## an award taken when nobody has it yet or the condition holds: the key and the record copied
static func _take_if(found: PackedByteArray, a: int, k: PackedByteArray, rec: PackedByteArray, better: bool) -> void:
	if found[a] != 0 and not better:
		return
	keys[a] = k.duplicate()
	stats[a] = rec.duplicate()
	found[a] = 1

## the EASN award: the sum of three words (+0x28 of a skater's record, +0x30 of a goalie's) against
## the holder's; a tie goes to fewer games
static func _easn(found: PackedByteArray, rec: PackedByteArray, k: PackedByteArray, at: int, skater: bool) -> void:
	var cur := easn_record()
	var b := 0x28 if easn_skater else 0x30
	var best := _u16(cur, b) + _u16(cur, b + 2) + _u16(cur, b + 4)
	var sum := _u16(rec, at) + _u16(rec, at + 2) + _u16(rec, at + 4)
	if found[9] != 0 and not (sum > best or (sum == best and _u16(cur, 0) > _u16(rec, 0))):
		return
	keys[9] = k.duplicate()
	easn_records[0 if skater else 1] = rec.duplicate()
	easn_skater = skater
	stats[9] = easn_record()
	found[9] = 1
