class_name RinkTiles
## TEAM.TIL / TEAM.MAP: the centre ice logo of a team as 8x8 tiles placed onto the rink surface
## (load_rink / load_rink_tiles). The rink itself is the 384x592 'rink' shape of RINK.QFS.

## Renders a tile map on its own (8 bit index image, 0xff transparent)
static func render(til: PackedByteArray, mapdata: PackedByteArray, pal: PackedColorArray) -> Image:
	if mapdata.size() < 6:
		return null
	var w := mapdata.decode_u16(0)
	var h := mapdata.decode_u16(2)
	var surface := PackedByteArray()
	surface.resize(w * 8 * h * 8)
	surface.fill(0xff)
	place(surface, w * 8, til, mapdata, 0, 0, false)
	return Shpi.indexed_to_image(surface, w * 8, h * 8, pal, 0xff)

## load_rink_tiles(): draws the tiles of a map onto an 8 bit surface at tile (col, row); the
## mirrored placement (flag 0x6000 of load_rink) goes right to left / bottom to top with every tile
## flipped and is used for the second half of symmetric logos (EDM, LA, NJ, PIT)
static func place(surface: PackedByteArray, stride: int, til: PackedByteArray, mapdata: PackedByteArray, col: int, row: int, mirror: bool) -> void:
	if mapdata.size() < 6:
		return
	var w := mapdata.decode_u16(0)
	var h := mapdata.decode_u16(2)
	var rows := surface.size() / stride
	for ty in h:
		for tx in w:
			var c := mapdata.decode_u16(6 + (ty * w + tx) * 2)
			var t := (c & 0x3ff) * 64
			if t + 64 > til.size():
				continue
			var fx := ((c & 0x2000) != 0) != mirror
			var fy := ((c & 0x4000) != 0) != mirror
			var cx := col - tx if mirror else col + tx
			var cy := row - ty if mirror else row + ty
			for yy in 8:
				var py := cy * 8 + yy
				if py < 0 or py >= rows:
					continue
				var sy := 7 - yy if fy else yy
				for xx in 8:
					var px := cx * 8 + xx
					if px < 0 or px >= stride:
						continue
					var sx := 7 - xx if fx else xx
					var p := til[t + sy * 8 + sx]
					if p != 0xff:
						surface[py * stride + px] = p

## load_rink(): the rink surface with the centre ice logo of `team` (0..25)
static func compose(rink: Shpi.Shape, til: PackedByteArray, mapdata: PackedByteArray, team: int, pal: PackedColorArray) -> Image:
	var surface := PackedByteArray(rink.pixels)
	if team >= 0 and team < Tables.rink_logo.size() and til.size() > 0 and mapdata.size() >= 6:
		var pos: Array = Tables.rink_logo[team]
		place(surface, rink.width, til, mapdata, pos[0], pos[1], false)
		if pos[2] >= 0:
			place(surface, rink.width, til, mapdata, pos[2], pos[3], true)
	return Shpi.indexed_to_image(surface, rink.width, rink.height, pal, -1)
