class_name PlayerForm
extends RefCounted
## create_player_form (0x6f6d4) of the Central Registry's Create Free Agent: a new skater's CAREER.DB
## record made up from his ratings, with the game's randomrange (golden-verified: tests/golden/registry)

static var seed := 0xabcd4321            # random_seed (the match code's randomrange shares it)
## randomrange (0x8c230), as Sim.random
static func randomrange(n: int) -> int:
	var lo := seed & 0xffff
	var hi := (seed >> 16) & 0xffff
	var mid := (hi * 0xe62d + lo * 0xbb40) & 0xffff
	seed = (lo * 0xe62d + (mid << 16) + 1) & 0xffffffff
	return ((((seed >> 8) & 0xffff) * (n & 0xffff)) >> 16)

## a value stored by fstp dword
static func _f32(x: float) -> float:
	var b := PackedByteArray()
	b.resize(4)
	b.encode_float(0, x)
	return b.decode_float(0)

## fround (0x961d4, the compiler's float to int: frndint with the rounding control "chop") + fistp.
## (The game runs the FPU with __init_8087's control word 0x127f: 53 bit precision, as doubles.)
static func _fround(x: float) -> int:
	return int(x)

## rating_scale (0x6fa64): a rating 0..15 as shown (25..100)
static func rating_scale(b: int) -> float:
	return float((b + 5) * 5)

## create_player_form (0x6f6d4): a new skater's CAREER.DB record made up from the ratings: games
## (64..84) and, scaled by them and by 1 - randomrange(333) / 1000, the goals and assists (by the
## offensive ratings, a defenceman's fewer), the power play goals and some of them short handed,
## the penalty minutes, plus / minus and shots
static func create_player_form(pos: int, att: PackedByteArray) -> PackedByteArray:
	var car := PackedByteArray()
	car.resize(0x28)
	var s1c := rating_scale(att[1])
	var s0c := rating_scale(att[2])
	var s14 := rating_scale(att[4])
	var s2c := rating_scale(att[5])
	var s24 := rating_scale(att[6])
	var s10 := rating_scale(att[7])
	var s20 := rating_scale(att[9])
	var s34 := rating_scale(att[0xa])
	var s18 := rating_scale(att[0xb])
	var s3c := rating_scale(att[0xc])
	var s28 := rating_scale(att[0xd])
	var s44 := rating_scale(att[0xe])
	var s40 := _f32(1.0 - float(randomrange(0x14d)) / 1000.0)
	var g := randomrange(0x15) + 0x40
	car.encode_u16(0, g)
	var s48 := _f32(float(g) / 84.0)
	car.encode_u16(0xe, _fround((s34 + s28 + s44) / 300.0 * 390.0 * s48 * s40) & 0xffff)
	car.encode_u16(0x10, _fround(((s34 + s18) / 200.0 * 100.0 + -50.0) * s48 * s40) & 0xffff)
	var f8 := _f32((s0c + s34 + s24 + s1c + s28) / 500.0)
	var f38: float
	var f30: float
	if pos != 0x44:
		f38 = _f32(s44 / 70.0)
		f30 = _f32((100.0 - s44) / 30.0)
	else:
		f38 = _f32(s44 / 90.0)
		f30 = _f32((100.0 - s44) / 10.0)
	var cx := (_fround(f38 * 58.0) & 0xffff) if 1.0 > f38 else 0x3a
	var dx := (_fround(f30 * 90.0) & 0xffff) if 1.0 > f30 else 0x5a
	var f4 := _f32((s14 + s10) / 200.0 * cx)
	var f0 := _f32(s20 / 100.0 * dx)
	var goals := _fround(f8 * f4 * s48 * s40)
	var assists := _fround(f8 * f0 * s48 * s40)
	var di := goals & 0xffff
	var si := assists & 0xffff
	if di + si > 0x80:
		var by := (di + si) / 128
		goals = di / by
		var by2 := ((goals & 0xffff) + si) / 128
		assists = si / by2
	car.encode_u16(2, goals & 0xffff)
	car.encode_u16(4, assists & 0xffff)
	car.encode_u16(6, (car.decode_u16(2) + assists) & 0xffff)
	car.encode_u16(8, car.decode_u16(2) / 10)
	car.encode_u16(0xa, randomrange(car.decode_u16(8)) & 0xffff)
	s3c = _f32(s3c * 0.9)
	s2c = _f32(s2c * 0.1)
	car.encode_u16(0xc, _fround((s3c + s2c) / 100.0 * 347.0 * s48 * s40) & 0xffff)
	return car
