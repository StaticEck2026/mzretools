class_name Trade
## The league's trades (statistics_menu 0x40183 -> line_editor 0x3ff52 -> team_edit_screen 0x3e390),
## the files' side, ported literally: the two rosters of the trade screen (line_editor_load_roster,
## sorted by cmp_player_names), the swap of each pair of traded players (their KEY.DB records change
## team, the two teams' rosters exchange the records' offsets, the players leave both line tables
## of their old team: lines_remove_player) and the check of the newcomer's jersey number against
## his new team (jersey_number_dialog: a number already worn asks for another, until none is).
## TEAMS.DB and KEY.DB are read and written through file_read / file_write semantics: a negative
## offset reads or writes on from where the file is.

const TEAM := 0x2e8
const KEY := 0x34

## file_read / file_write on a CFile: 0, or 1 short
static func _read(f: StatsSort.CFile, buf: PackedByteArray, off: int, size: int) -> int:
	f.lseek(off)
	return 0 if f.read(buf, size) == size else 1

static func _write(f: StatsSort.CFile, buf: PackedByteArray, off: int, size: int) -> int:
	f.lseek(off)
	return 0 if f.write(buf, size) == size else 1

## line_editor_load_roster (0x3dc2c): the 28 entries of a team (0x16 bytes as the original keeps
## them: position, number, slot, "I. Lastname") as [position ("" empty), number, slot, name, last
## name] for NameSort, in slot order; null when a read failed
static func roster(teams: PackedByteArray, key_db: PackedByteArray, team: int) -> Variant:
	var tf := StatsSort.CFile.new(teams)
	var rec := PackedByteArray()
	rec.resize(TEAM)
	if _read(tf, rec, team * TEAM, TEAM) != 0:
		return null
	var kf := StatsSort.CFile.new(key_db)
	var k := PackedByteArray()
	k.resize(KEY)
	var out := []
	for i in 28:
		var off := rec.decode_s32(0x4c + i * 4)
		if off == -1:
			out.append(["", 0, i, "", ""])
			continue
		if _read(kf, k, off, KEY) != 0:
			return null
		var last := _cstr(k, 0x13)
		var first := char(k[3]) if k[3] != 0 else ""
		out.append([char(k[2]) if k[2] != 0 else "", k[1], i, first + ". " + last, last])
	return out

static func _cstr(b: PackedByteArray, at: int) -> String:
	var s := ""
	var i := at
	while i < b.size() and b[i] != 0:
		s += char(b[i])
		i += 1
	return s

## lines_remove_player (0x8b96d): the roster slot leaves a line table (0x28 bytes at `at`), its places
## become 100: the first of each forward line (4 x 3) and defence pair (3 x 2), the first of the
## places 0x12..0x16, 0x17..0x1b, 0x1c..0x1f and 0x20..0x23, each of 0x24..0x27
static func remove_from_lines(slot: int, t: PackedByteArray, at: int) -> void:
	for l in 4:
		for k in 3:
			if t[at + l * 3 + k] == slot:
				t[at + l * 3 + k] = 0x64
				break
	for l in 3:
		for k in 2:
			if t[at + 0xc + l * 2 + k] == slot:
				t[at + 0xc + l * 2 + k] = 0x64
				break
	for g: Array in [[0x12, 5], [0x17, 5], [0x1c, 4], [0x20, 4]]:
		for k in g[1]:
			if t[at + g[0] + k] == slot:
				t[at + g[0] + k] = 0x64
				break
	for k in range(0x24, 0x28):
		if t[at + k] == slot:
			t[at + k] = 0x64

## the trade's files open (team_edit_screen): TEAMS.DB and KEY.DB with their positions, the two
## teams' records as read
class Files:
	var teams: StatsSort.CFile
	var key: StatsSort.CFile
	var ids := [0, 0]
	var recs := [PackedByteArray(), PackedByteArray()]

## team_edit_screen's start: the files opened and the two teams' records read; null when a read failed
static func open(teams: PackedByteArray, key_db: PackedByteArray, a: int, b: int) -> Files:
	var f := Files.new()
	f.teams = StatsSort.CFile.new(teams)
	f.key = StatsSort.CFile.new(key_db)
	f.ids = [a, b]
	for s in 2:
		var r := PackedByteArray()
		r.resize(TEAM)
		if _read(f.teams, r, f.ids[s] * TEAM, TEAM) != 0:
			return null
		f.recs[s] = r
	return f

## a pair of the trade (team_edit_screen): slot `sa` of the first team for slot `sb` of the second.
## The players' KEY.DB records take their new team (+0), the rosters exchange the offsets, the slots
## leave both line tables (+0xbc, +0xec) of the old teams, the records and the teams are written. 0,
## or 1 when a read or a write failed
static func swap(f: Files, sa: int, sb: int) -> int:
	var ra: PackedByteArray = f.recs[0]
	var rb: PackedByteArray = f.recs[1]
	var off_a := ra.decode_s32(0x4c + sa * 4)
	var ka := PackedByteArray()
	ka.resize(KEY)
	if _read(f.key, ka, off_a, KEY) != 0:
		return 1
	var off_b := rb.decode_s32(0x4c + sb * 4)
	var kb := PackedByteArray()
	kb.resize(KEY)
	if _read(f.key, kb, off_b, KEY) != 0:
		return 1
	ka[0] = f.ids[1] & 0xff
	kb[0] = f.ids[0] & 0xff
	ra.encode_s32(0x4c + sa * 4, off_b)
	rb.encode_s32(0x4c + sb * 4, off_a)
	remove_from_lines(sa, ra, 0xbc)
	remove_from_lines(sa, ra, 0xec)
	remove_from_lines(sb, rb, 0xbc)
	remove_from_lines(sb, rb, 0xec)
	if _write(f.key, ka, off_a, KEY) != 0 or _write(f.key, kb, off_b, KEY) != 0:
		return 1
	if _write(f.teams, ra, f.ids[0] * TEAM, TEAM) != 0 or _write(f.teams, rb, f.ids[1] * TEAM, TEAM) != 0:
		return 1
	return 0

## jersey_number_dialog (0x3e055): the 28 KEY.DB records of the team's roster read (an empty
## slot's -1 reads on from where the file is); [read error (0/1), the records]
static func jersey_read(f: Files, side: int) -> Array:
	var rec: PackedByteArray = f.recs[side]
	var keys := []
	var err := 0
	var i := 0
	while i < 28 and err == 0:
		var k := PackedByteArray()
		k.resize(KEY)
		err = _read(f.key, k, rec.decode_s32(0x4c + i * 4), KEY)
		keys.append(k)
		i += 1
	return [err, keys]

## the slot's player's number is worn by another of the records
static func jersey_conflict(keys: Array, slot: int) -> bool:
	for j in 28:
		if j != slot and (keys[slot] as PackedByteArray)[1] == (keys[j] as PackedByteArray)[1]:
			return true
	return false

## the new number of the slot's player written to KEY.DB (jersey_number_dialog's answer); 0 or 1
static func set_number(f: Files, side: int, slot: int, keys: Array, number: int) -> int:
	var k: PackedByteArray = keys[slot]
	k[1] = number & 0xff
	return _write(f.key, k, (f.recs[side] as PackedByteArray).decode_s32(0x4c + slot * 4), KEY)

## team_edit_screen (0x3e390) up to the line editors: the files opened, each pair of the 4 slots
## (both set) swapped and its two newcomers' numbers checked, the first error ending it. `answer`
## (side, slot, the roster's KEY.DB records) -> the number asked for (the dialogs of
## jersey_number_dialog: "The jersey number %2d is already used on %s!", then "Enter jersey number
## for %s"). Returns [0 or 1, a pair was traded, the Files].
static func edit(teams: PackedByteArray, key_db: PackedByteArray, a: int, b: int, slots: PackedByteArray,
		answer: Callable) -> Array:
	var f := open(teams, key_db, a, b)
	if f == null:
		return [1, false, null]
	var err := 0
	var changed := false
	var k := 0
	while k < 2 and err == 0:
		var sa: int = slots[k]
		var sb: int = slots[k + 2]
		if sa != 0xff and sb != 0xff:
			changed = true
			err = swap(f, sa, sb)
			if err == 0:
				err = await _jersey(f, 0, sa, answer)
			if err == 0:
				err = await _jersey(f, 1, sb, answer)
		k += 1
	return [err, changed, f]

## jersey_number_dialog: until the newcomer's number is his alone, another is asked and written
static func _jersey(f: Files, side: int, slot: int, answer: Callable) -> int:
	var r := jersey_read(f, side)
	if r[0] != 0:
		return r[0]
	var keys: Array = r[1]
	while jersey_conflict(keys, slot):
		var n: int = await answer.call(side, slot, keys)
		var e := set_number(f, side, slot, keys, n)
		if e != 0:
			return e
	return 0
