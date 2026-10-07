class_name Entity
extends RefCounted
## One record of the original `entities` array (re/nhl_hockey/STRUCTURES.md). Field names follow the
## reverse engineered layout; fixed point values keep the original scale so the arithmetic of the
## decompiled routines can be ported literally: x/y/z are 16.16, velocities are 16 bit integers added
## as `pos += 16 * v` per step. The original offset of every field is given in the comments.

enum Slot { HOME0 = 0, AWAY0 = 6, NET_TOP = 12, NET_BOTTOM = 13, PUCK = 14, SHADOW = 15, REFEREE = 16 }

# AI states (index into ai_state_handlers / ai_state_names[state + 1])
enum State {
	NONE = 0, DEF_OFFENSE = 1, DEF_DEFENSE = 2, WING_DEFENSE = 3, WING_OFFENSE = 4,
	CENTER_DEFENSE = 5, CENTER_OFFENSE = 6, CELEBRATE = 7, STANLEY_CUP = 8, EXIT_BENCH = 9,
	EXIT_PENALTY_BOX = 10, BENCH = 11, PENALTY_BOX = 12, DOOR_OPEN = 13, GOALIE = 14,
	GOALIE_GET_PUCK = 15, PUCK_CARRIER = 16, NEAREST = 17, SHOOT = 18, PASS_RECEIVER = 19,
	THREE_STARS = 20, REF_THREE_STARS = 21, FACEOFF_WAIT = 22, FACEOFF = 23, PUCK_NORMAL = 24,
	PUCK_SHADOW = 25, PUCK_IDLE = 26, PUCK_FACEOFF = 27, PUCK_FACEOFF2 = 28, GAME_MISCONDUCT = 29,
	REF_FACEOFF = 30, REF_NORMAL = 31, REF_CALL_PENALTY = 32, REF_PICKUP = 33, REF_GOTO_FACEOFF = 34,
	REF_POINT_GOAL = 35, REF_GET_NEW_PUCK = 36, ANTHEM = 37, REF_ANTHEM = 38, ALL_GOTO_FACEOFF = 39,
	BENCH_WAIT = 40, INIT_PERIOD = 41, GET_CUP = 42, PUCK_GIVE_CUP = 43, REF_PENALTY_SHOT = 44,
	PENALTY_SHOT_WAIT = 45, BREAKAWAY = 46,
}

# flags (+0x44)
const F_HAS_TARGET := 0x01          # set by the pass receiver / bench logic ("committed")
const F_STATE_ENTERED := 0x02
const F_ARRIVED := 0x04             # bench/penalty box: reached the door
const F_USER := 0x08
const F_BACKWARDS := 0x10
const F_BUSY := 0x20
const F_PLAYER2 := 0x40             # away team (user 2 side)
const F_ATTACK_UP := 0x80           # shoots at the net at +y (top of the screen); tables are in this frame
# flags2 (+0x45)
const F2_KNOCKED := 0x01            # lying on the ice
const F2_TURNING := 0x02
const F2_UNSELECTABLE := 0x04
const F2_LINE_CHANGE := 0x08
const F2_PENALIZED := 0x10
const F2_NO_COLLIDE := 0x20
const F2_HOOKED := 0x40
const F2_OFFSIDE := 0x80
# flags3 (+0x48): goalie posture bits (2, 4 = outside the crease area)
# flags4 (+0x55)
const F4_MIRROR := 0x08
const F4_FLIP_Y := 0x80

var slot: int = 0            # +0x6a
var x: int = 0               # +0x00 16.16
var y: int = 0               # +0x04
var z: int = 0               # +0x08
var vx: int = 0              # +0x0c 16 bit
var vy: int = 0              # +0x0e
var vz: int = 0              # +0x10
var frame: int = 0           # +0x12 sprite frame
var hit_by: int = -1         # +0x14 slot of the last body contact
var speed_prev: int = 0      # +0x16 (unused by the port)
var speed: int = 0           # +0x18 the strength of the last body contacts (collide_pair adds it, -2 per step)
var line_slot: int = -1      # +0x1a 0 goalie, 1-5 skaters, <0 bench
var state_sp: int = 0        # +0x1c
var state_stack: PackedByteArray = PackedByteArray([0, 0, 0, 0, 0, 0, 0, 0])   # +0x1e
var timer_a: int = 0         # +0x26 generic state timer (word)
var react_timer: int = 0     # +0x27 reaction countdown (byte, reloaded from `reaction`)
var want_dir: int = 8        # +0x28 direction the AI wants to skate (byte)
var dir_timer: int = 0       # +0x29 steps until the direction is re-evaluated (byte)
var target_x: int = 0        # +0x2a AI target position
var target_y: int = 0        # +0x2c
var timer_b: int = 0         # +0x2e secondary state timer
var push_x: int = 0          # +0x30 board normal a after a bounce
var push_y: int = 0          # +0x32 board normal b
var heading: int = 0         # +0x34 16.16, facing = heading >> 16 & 7
var anim: int = 0            # +0x38
var anim_pos: int = 0        # +0x3a
var anim_hold: int = -1      # +0x3c
var timer_c: int = 0         # +0x3e no-pickup timer after releasing the puck
var timer_d: int = 0         # +0x40
var next_line_slot: int = -1 # +0x42 line change: position to take (-1 none)
var next_roster: int = -1    # +0x43 line change: roster index of the replacement
var flags: int = 0           # +0x44
var flags2: int = 0          # +0x45
var pass_target: int = -1    # +0x46 slot of the chosen pass receiver
var roster_idx: int = 0      # +0x47 (25, 26 goalies)
var flags3: int = 0          # +0x48 goalie posture
var timer_e: int = 0         # +0x4a goalie save cooldown / poke direction
var timer_f: int = 0         # +0x4c shoot state cooldown
var puck_dist: int = 0       # +0x4e octagonal distance to the puck
var puck_dist_sq: int = 0    # +0x50 (dx/4)^2 + (dy/4)^2
var puck_dir: int = 0        # +0x52 direction8 towards the puck
var pass_ok: int = 0         # +0x53 result of the pass lane check
var side: int = 0            # +0x54
var flags4: int = 0          # +0x55
var weight: int = 128        # +0x56
var speed_skill: int = 8     # +0x57 0..15
var stamina: int = 8         # +0x58
var reaction: int = 8        # +0x59 steps between AI decisions
var awareness: int = 8       # +0x5a defensive awareness (ai_defense_*, goalie)
var shot_skill: int = 8      # +0x5b
var shot_accuracy: int = 8   # +0x5c
var pass_skill: int = 8      # +0x5d
var number: int = 0          # +0x5e jersey number
var offense: int = 8         # +0x5f offensive awareness (pass / shot decisions)
var goalie_skill: int = 8    # +0x60
var endurance: int = 8       # +0x61 skaters: energy recovered per fatigue tick (skating_accelerate); goalies: a save rating
var check_skill: int = 8     # +0x62
var save_result: int = 0     # +0x63
var aggression: int = 8      # +0x64
var left_handed: int = 0     # +0x65 (0 = shoots right)
var half_w: int = 8          # +0x66 collision half width
var half_h: int = 4          # +0x68 collision half height
var team: int = 0            # +0x6c -> Team index (0 home, 1 away)
var prev_x: int = 0          # +0x74
var prev_y: int = 0          # +0x78
var prev_z: int = 0          # +0x7c
var energy: int = 0x1000     # team.energy[roster_idx] mirrored here for convenience

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

## set_state (0x11ff4): replaces the current state and marks it as freshly entered
func set_state(s: int) -> void:
	state_stack[state_sp] = s
	flags |= F_STATE_ENTERED

## set_state_reset (0x11fe0): pops the state stack by one and sets the state
func set_state_reset(s: int) -> void:
	state_sp = (state_sp - 1) & 7
	set_state(s)

## ai_default_skate / ai_faceoff_wait: pushes the stack by one (the handler below is re-entered)
func push_state() -> void:
	state_sp = (state_sp + 1) & 7
	flags |= F_STATE_ENTERED

func is_player() -> bool:
	return slot < 12

func is_goalie() -> bool:
	return is_player() and line_slot == 0

func is_skater() -> bool:
	return is_player() and line_slot > 0

func on_ice() -> bool:
	return line_slot >= 0 or slot == Slot.REFEREE

func set_pos(px: int, py: int) -> void:
	x = px << 16
	y = py << 16
	prev_x = x
	prev_y = y

## sign of the attacking direction: +1 when the team shoots at the +y net
func attack_sign() -> int:
	return 1 if flags & F_ATTACK_UP else -1

## own goal line / net y
func own_goal_y() -> int:
	return -Sim.GOAL_LINE_Y if flags & F_ATTACK_UP else Sim.GOAL_LINE_Y

static func to_s8(v: int) -> int:
	v &= 0xff
	return v - 0x100 if v >= 0x80 else v

static func to_s16(v: int) -> int:
	v &= 0xffff
	return v - 0x10000 if v >= 0x8000 else v
