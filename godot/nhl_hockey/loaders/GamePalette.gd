class_name GamePalette
## The palette of the match screen as built by load_team_palettes() and the colour remap tables of
## blit_sprite(). RINKPAL.QFS ('!pal') provides the entries 0..0x7f and 0xfb..0xff, HOMEPALS.BIN /
## AWAYPALS.BIN hold 0x1c0 bytes per team: 0xc0 palette bytes (64 jersey colours, placed at 0x80
## for the home and at 0xc0 for the away team) followed by a 256 byte remap table through which
## every sprite pixel of that team is drawn. The away remap gets 0x40 added to its entries
## 0x90..0xff so that it points into the away block.

var colors: PackedColorArray = PackedColorArray()
var remap: Array[PackedByteArray] = []          # [home, away]
var remap_mirrored: Array[PackedByteArray] = [] # the same while a mirrored frame is drawn

static func build(rinkpal: PackedByteArray, homepals: PackedByteArray, awaypals: PackedByteArray, home: int, away: int) -> GamePalette:
	var bank := Shpi.parse(rinkpal)
	if bank == null:
		return null
	var pal_shape := bank.find("!pal")
	if pal_shape == null or pal_shape.raw.size() < 0x300:
		return null
	if homepals.size() < (home + 1) * 0x1c0 or awaypals.size() < (away + 1) * 0x1c0:
		return null
	var p := GamePalette.new()
	var base := pal_shape.raw.slice(0, 0x300)
	var hp := homepals.slice(home * 0x1c0, (home + 1) * 0x1c0)
	var ap := awaypals.slice(away * 0x1c0, (away + 1) * 0x1c0)
	var raw := PackedByteArray(base)
	for i in 0xc0:
		raw[0x180 + i] = hp[i]
		raw[0x240 + i] = ap[i]
	for i in range(0x2f1, 0x300):
		raw[i] = base[i]
	for i in 256:
		p.colors.append(Color8(raw[i * 3] * 255 / 63, raw[i * 3 + 1] * 255 / 63, raw[i * 3 + 2] * 255 / 63))
	var rh := hp.slice(0xc0, 0x1c0)
	var ra := ap.slice(0xc0, 0x1c0)
	for i in range(0x90, 0x100):
		ra[i] = (ra[i] + 0x40) & 0xff
	p.remap = [rh, ra]
	p.remap_mirrored = [mirrored(rh), mirrored(ra)]
	return p

## blit_sprite swaps the remap entries 0xc0 + 16k + {0, 1, 3, 4} ([0] <-> [4], [1] <-> [3]) while
## a mirrored frame is drawn: the shaded side of the jersey changes with the facing
static func mirrored(r: PackedByteArray) -> PackedByteArray:
	var m := PackedByteArray(r)
	for k in 4:
		var b := 0xc0 + 16 * k
		m[b] = r[b + 4]
		m[b + 4] = r[b]
		m[b + 1] = r[b + 3]
		m[b + 3] = r[b + 1]
	return m

## remap table for a team (0 home, 1 away, -1 none) and mirroring
func table(team: int, mirror: bool) -> PackedByteArray:
	if team < 0 or team > 1:
		return PackedByteArray()
	return remap_mirrored[team] if mirror else remap[team]
