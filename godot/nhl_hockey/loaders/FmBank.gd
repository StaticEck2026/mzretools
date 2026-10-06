class_name FmBank
extends RefCounted
## The patch bank of the sound driver (loadpatches 0x8ecc0): the .SCN file of the sound card
## names a patch file and its timbre files, `%.3sFF%03d.PAT/.TIM` (SBDAC.SCN: PCFF001.PAT with
## PCFF000.TIM for the FM instruments and PCFF001.TIM for the digital ones).
##
##   .PAT  +0 u16, +2 u8[256] sound / program id -> record index (0 = none, except id 0),
##         records of 0x14 bytes from +0x102: +0 type (0 FM timbre, 1 digital timbre), +1 timbre
##         program, +2 u16 voice mask, +6 voices at most, +7 s8 transpose, +8 s8 fine tune,
##         +0xa pitch bend range (semitones), +0xc priority, +0xe note length of a sound effect
##         (x 6 ticks, 0 = 0xa0 ticks), +0xf driver class (bind_patch_timbres turns it into the driver index)
##   .TIM  +0 u32 file size, +4 u16 n, n x 4 byte keys (0x80, type, 0, program; the last one
##         0xffffffff), n x u32 offsets relative to the data at 6 + 8 n. FM timbres are 80 bytes
##         (+2..+0xe the 13 register bytes of FmDriver), digital ones 32 bytes (+0 type 6, +2 the
##         4 byte id of the sample in the .DIG file, +0x14 u32 length, +0x18 / +0x1c loop).

var pat := PackedByteArray()
var timbres: Dictionary = {}          # type << 8 | program -> PackedByteArray

static func load_bank(pat_data: PackedByteArray, tim_files: Array) -> FmBank:
	if pat_data.size() < 0x102:
		return null
	var b := FmBank.new()
	b.pat = pat_data
	for tim in tim_files:
		b.add_timbres(tim)
	return b

## the timbres of a .TIM file by their key
func add_timbres(tim: PackedByteArray) -> void:
	for e in parse_tim(tim):
		timbres[(e[0] << 8) | e[1]] = e[2]

## [type, program, record bytes] of each timbre of a .TIM file
static func parse_tim(tim: PackedByteArray) -> Array:
	var out: Array = []
	if tim.size() < 6:
		return out
	var n := tim.decode_u16(4)
	var base := 6 + 8 * n
	for k in n:
		var key := 6 + 4 * k
		if tim[key] != 0x80:
			continue
		var start := base + tim.decode_u32(6 + 4 * n + 4 * k)
		var end := tim.size()
		if k + 1 < n:
			var nxt := base + tim.decode_u32(6 + 4 * n + 4 * (k + 1))
			if nxt > start:
				end = mini(nxt, end)
		if start >= tim.size():
			continue
		out.append([tim[key + 1], (tim[key + 2] << 8) | tim[key + 3], tim.slice(start, end)])
	return out

## snd_patch_record: the record of a sound / program id, empty when there is none
func record(id: int) -> PackedByteArray:
	if id < 0 or id > 0xff:
		return PackedByteArray()
	var r := pat[2 + id]
	if r == 0 and id != 0:
		return PackedByteArray()
	var o := 0x102 + r * 0x14
	if o + 0x14 > pat.size():
		return PackedByteArray()
	return pat.slice(o, o + 0x14)

## the FM timbre of a program (type 0)
func timbre(program: int, type: int = 0) -> PackedByteArray:
	return timbres.get((type << 8) | program, PackedByteArray())
