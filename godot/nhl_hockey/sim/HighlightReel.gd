class_name HighlightReel
## The highlights reel of a league or play-off series: each team's TEAM.HI in the league's directory
## holds the replays saved from the VCR's menu (replay_save_highlight 0x7fa10), one record of
## 0x9652 bytes after another, the newest last. A record is the block at byte_e03c4: a header of
## 0x52 bytes and the replay ring (unk_e0416, 0x9600 bytes) as it was:
##   0x00  month, day of the game (byte_dc268 / byte_dc267: the schedule record's first bytes)
##   0x02  the home team (dword_c90ca), 0x03 its 28 jersey numbers (unk_db3ad, 0x27 apart)
##   0x1f  the away team, 0x20 its 28 jersey numbers (unk_db7f1)
##   0x3c  period_num, 0x40 / 0x44 / 0x48 the scoreboard's clock (minutes, seconds, tenths): dwords
##   0x4c  action_flags (word), 0x4e the ring's write offset (dword)
## highlights_play (0x8011c) puts them back and runs the VCR on the ring.

const RECORD := 0x9652
const HEADER := 0x52
const CITY_NAMES := 0xc54a9       # off_c54a9: the teams' city names (the lists and descriptions)
const TEAM_ABBREV := 0xc5439      # team_abbrev: the 26 abbreviations (the files' names)

## replay_save_highlight: the record of the replay ring of `sim` (its teams `home` / `away` as the
## game knows them); the action flags the port keeps (2 pass, 3 shot, 4 the ring is full, 6 the
## camera held, 7 the replay) and nothing of the others
static func record(sim: Sim, home: int, away: int, month: int, day: int) -> PackedByteArray:
	var r := PackedByteArray()
	r.resize(RECORD)
	r[0] = month & 0xff
	r[1] = day & 0xff
	r[2] = home & 0xff
	r[0x1f] = away & 0xff
	for i in 28:
		r[3 + i] = _number(sim, 0, i)
		r[0x20 + i] = _number(sim, 1, i)
	r.encode_s32(0x3c, sim.period_num)
	r.encode_s32(0x40, sim.hud_clock[0])
	r.encode_s32(0x44, sim.hud_clock[1])
	r.encode_s32(0x48, sim.hud_clock[2])
	r.encode_u16(0x4c, action_flags(sim))
	r.encode_s32(0x4e, sim.replay.write)
	for i in Replay.SIZE:
		r[HEADER + i] = sim.replay.buf[i]
	return r

static func _number(sim: Sim, t: int, i: int) -> int:
	var n: PackedByteArray = sim.teams[t].numbers
	return n[i] if i < n.size() else 0

static func action_flags(sim: Sim) -> int:
	var f := 0
	if sim.action_pass:
		f |= 4
	if sim.action_shot:
		f |= 8
	if sim.replay.wrapped:
		f |= 0x10
	if sim.action_hold_camera:
		f |= 0x40
	if sim.action_replay:
		f |= 0x80
	return f

## highlights_play: the record put back into `sim` (period, clock, flags, jersey numbers, the ring);
## [home, away] of the record
static func restore(rec: PackedByteArray, sim: Sim) -> Array:
	sim.period_num = rec.decode_s32(0x3c)
	sim.hud_clock[0] = rec.decode_s32(0x40)
	sim.hud_clock[1] = rec.decode_s32(0x44)
	sim.hud_clock[2] = rec.decode_s32(0x48)
	var f := rec.decode_u16(0x4c)
	sim.action_pass = f & 4 != 0
	sim.action_shot = f & 8 != 0
	sim.replay.wrapped = f & 0x10 != 0
	sim.action_hold_camera = f & 0x40 != 0
	sim.action_replay = f & 0x80 != 0
	sim.replay.write = rec.decode_s32(0x4e)
	for i in Replay.SIZE:
		sim.replay.buf[i] = rec[HEADER + i]
	for t in 2:
		var n: PackedByteArray = sim.teams[t].numbers
		if n.size() < 28:
			n.resize(28)
		for i in 28:
			n[i] = rec[(3 if t == 0 else 0x20) + i]
		sim.teams[t].numbers = n
	return [rec[2], rec[0x1f]]

## format_save_description (0x7fca2): "month day, Home vs Away, Period p, Time mm:ss." from a
## record's header (the first 0x4c bytes)
static func describe(h: PackedByteArray) -> String:
	return "%d %d, %s vs %s, Period %d, Time %02d:%02d." % [h[0], h[1], Exe.str_ptr(CITY_NAMES + h[2] * 4),
		Exe.str_ptr(CITY_NAMES + h[0x1f] * 4), h.decode_s32(0x3c), h.decode_s32(0x40), h.decode_s32(0x44)]

## team_abbrev_index (0x7fc5c): the team whose abbreviation a file's name has before its '.'
## (case ignored), -1 for none
static func team_of_file(name: String) -> int:
	var base := name.get_file()
	var dot := base.find(".")
	if dot >= 0:
		base = base.left(dot)
	var found := -1
	for t in 26:
		if Exe.str_ptr(TEAM_ABBREV + t * 4).to_upper() == base.to_upper():
			found = t
	return found

## the team's abbreviation (the file's name)
static func abbrev(team: int) -> String:
	return Exe.str_ptr(TEAM_ABBREV + team * 4)
