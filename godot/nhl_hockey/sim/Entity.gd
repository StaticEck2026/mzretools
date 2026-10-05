class_name Entity
extends RefCounted
## One record of the original `entities` array (re/nhl_hockey/STRUCTURES.md). Field names follow the
## reverse engineered layout; fixed point values keep the original scale so the arithmetic of the
## decompiled routines can be ported literally: x/y/z are 16.16, velocities are 16 bit integers added
## as `pos += 16 * v` per step.

enum Slot { HOME0 = 0, AWAY0 = 6, NET_TOP = 12, NET_BOTTOM = 13, PUCK = 14, SHADOW = 15, REFEREE = 16 }

# flags (+0x44)
const F_STATE_ENTERED := 0x02
const F_USER := 0x08
const F_BACKWARDS := 0x10
const F_BUSY := 0x20
const F_PLAYER2 := 0x40
const F_ATTACK_DOWN := 0x80
# flags2 (+0x45)
const F2_TURNING := 0x02
const F2_UNSELECTABLE := 0x04
const F2_LINE_CHANGE := 0x08
const F2_NO_COLLIDE := 0x20
const F2_HOOKED := 0x40
const F2_OFFSIDE := 0x80
# flags4 (+0x55)
const F4_MIRROR := 0x08

var slot: int = 0
var x: int = 0            # 16.16
var y: int = 0
var z: int = 0
var vx: int = 0           # 16 bit
var vy: int = 0
var vz: int = 0
var frame: int = 0
var speed: int = 0
var speed_prev: int = 0
var line_slot: int = -1   # 0 goalie, 1-5 skaters, <0 bench
var state_stack: PackedByteArray = PackedByteArray([0, 0, 0, 0, 0, 0, 0, 0])
var state_sp: int = 0
var timer_a: int = 0
var react_timer: int = 0
var want_dir: int = 8
var timer_b: int = 0
var push_x: int = 0       # +0x30 (board normal a after a bounce)
var push_y: int = 0       # +0x32 (board normal b)
var heading: int = 0      # 16.16, facing = heading >> 16 & 7
var anim: int = 0
var anim_pos: int = 0
var anim_hold: int = -1
var timer_c: int = 0
var timer_d: int = 0
var flags: int = 0
var flags2: int = 0
var flags3: int = 0
var flags4: int = 0
var stride_sfx_timer: int = 0
var roster_idx: int = 0
var timer_e: int = 0
var puck_dist: int = 0
var puck_dist_sq: int = 0
var puck_dir: int = 0
var weight: int = 128
var speed_skill: int = 50
var stamina: int = 60       # +0x58
var reaction: int = 4
var shot_skill: int = 50
var pass_skill: int = 50
var check_skill: int = 50
var half_w: int = 6         # +0x66 collision half width
var half_h: int = 4         # +0x68 collision half height
var team: int = 0           # 0 home, 1 away
var prev_x: int = 0
var prev_y: int = 0
var prev_z: int = 0
var energy: int = 0x1000    # team.energy[roster_idx]

var xi: int:
	get: return x >> 16
var yi: int:
	get: return y >> 16
var zi: int:
	get: return z >> 16
var facing: int:
	get: return (heading >> 16) & 7
	set(v): heading = (heading & 0xffff) | ((v & 7) << 16)

func state() -> int:
	return state_stack[state_sp]

func set_state(s: int) -> void:
	state_stack[state_sp] = s
	flags |= F_STATE_ENTERED

func is_player() -> bool:
	return slot < 12

func is_goalie() -> bool:
	return is_player() and line_slot == 0

func on_ice() -> bool:
	return line_slot >= 0 or slot == Slot.REFEREE

func set_pos(px: int, py: int) -> void:
	x = px << 16
	y = py << 16
	prev_x = x
	prev_y = y

static func to_s16(v: int) -> int:
	v &= 0xffff
	return v - 0x10000 if v >= 0x8000 else v
