class_name Anim
## Port of set_animation (0x59d9a) and advance_animation (0x5caef) over the `anim_sequences`
## table. An animation id is a word offset into the table; entry[0..7] hold per direction word
## offsets of the (frame, duration) list that starts at entry + 8 words; a negative duration
## marks the last frame; bit 15 of entry[0] means the animation loops.

const GLIDE := 0x289            # one frame per direction: no movement input
const SKATE_CARRIER := 0x2a1    # 4 frame skating cycle of the puck carrier
const SKATE := 0x2e9            # 4 frame skating cycle
const TURN_L := 0x331
const TURN_R := 0x349
const STOP := 0x361             # loops (bit 15 of the entry set)
const SHOT_FOREHAND := 0x3f9
const SHOT_BACKHAND := 0x491
const GLIDE_BACK := 0x529       # skating backwards without input
const SKATE_BACK := 0x541
const BODY_CHECK := 0x621
const HOOK_A := 0x639
const HOOK_B := 0x873
const SKATE_HOOKED := 0x8d3
const FACEOFF := 0x7a1
const GOALIE_IDLE := 0x1f1
# referee: the _ARM variants (arm raised) while the whistle sounds, a call is delayed or the offside
# warning is up during play (Sim.ref_arm_up)
const REF_GLIDE := 0xa5b
const REF_GLIDE_ARM := 0xb4b
const REF_SKATE := 0xa73
const REF_SKATE_ARM := 0xb63
const REF_TURN_L := 0xabb
const REF_TURN_L_ARM := 0xbab
const REF_TURN_R := 0xad3
const REF_TURN_R_ARM := 0xbc3
const REF_STOP := 0xaeb
const REF_STOP_ARM := 0xbdb

static func set_animation(e: Entity, id: int) -> void:
	if id != e.anim:
		e.anim_pos = 0
		e.anim = id
		e.anim_hold = -1

## advance_animation (0x5caef): one step of the animation. The frame shown (+0x12) is the one the
## step starts on, and it changes at most every 5 steps (frame_wait, +0x46); a new frame of the
## skating cycles plays the stride sound (0xb3). A board pin (0x1027..0x1055) that ends leaves the
## player at the left boards facing the bench (0x7a1)
static func advance(e: Entity, sim: Sim = null) -> void:
	if e.anim == 0:
		e.flags &= ~Entity.F_BUSY
		e.flags2 &= ~Entity.F2_TURNING
		return
	var dir := e.facing
	if e.flags4 & Entity.F4_MIRROR:
		dir = (8 - dir) & 7
	var base := e.anim      # word index of the entry
	var head := Tables.anim_word(base)
	var off := (head & 0x7fff) if dir == 0 else Tables.anim_word(base + dir)
	var list := base + off + 8
	var frame := Tables.anim_sword(list + e.anim_pos)
	if e.anim_hold < 0:
		# first visit of a frame: its duration
		e.anim_hold = absi(Tables.anim_sword(list + e.anim_pos + 1))
	else:
		e.anim_hold -= 1
		if e.anim_hold < 0:
			e.anim_pos += 2
			# the duration of the frame left: negative = it was the last one
			if Tables.anim_sword(list + e.anim_pos - 1) < 0:
				e.anim_pos = 0
				e.flags &= ~Entity.F_BUSY
				e.flags2 &= ~Entity.F2_TURNING
				if e.anim > 0x1026 and e.anim < 0x1056:
					e.vx = 0
					e.vy = 0
					e.x = -0xa0 * 0x10000 + (e.x & 0xffff)
					e.facing = 2
					e.flags |= Entity.F_BUSY
					set_animation(e, 0x7a1)
					return
				if (head & 0x8000) == 0:
					e.anim = 0
			e.anim_hold = absi(Tables.anim_sword(list + e.anim_pos + 1))
	e.frame_wait -= 1
	if e.frame_wait >= 0:
		return
	e.frame_wait = 0
	if frame == e.frame:
		return
	e.frame = frame
	if sim != null and stride_frame(frame):
		sim.play_sfx(0xb3)
	e.frame_wait = 4

## the frames of the skating cycles that put a skate down
static func stride_frame(f: int) -> bool:
	if f >= 0x112 and f <= 0x14e and ((f - 0x112) & 3) == 0:
		return true
	if f >= 0x207 and f <= 0x215 and (f & 1) != 0:
		return true
	if f > 0x314 and f < 0x32b and f % 3 == 0:
		return true
	if f > 0x389 and f < 0x3ae and (f - 0x38a) % 5 == 0:
		return true
	return f in [0x36f, 0x373, 0x377, 0x3bf, 0x3c3, 0x3ce, 0x3d1]
