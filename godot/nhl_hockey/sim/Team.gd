class_name Team
extends RefCounted
## One of the two team records (0xdf614 home, 0xdf714 away, 0x100 bytes each). Only the fields the
## simulation uses are kept; statistics are reduced to the few counters the rules touch.
## Offsets refer to re/nhl_hockey/STRUCTURES.md.

const FL_LINE_CHANGE_UI := 0x02      # +0x44 bit 1: line change menu open
const FL_OFFSIDE := 0x10             # +0x44 bit 4: an attacker is offside (check_offside)
const FL_PULLED_GOALIE := 0x80       # players[0].flags & 0x80 is the attack direction, this is ours

var index: int = 0                   # 0 home, 1 away
var goals: int = 0                   # +0x10
var shots: int = 0                   # +0x12
var faceoffs_won: int = 0            # +0x14
var hits: int = 0                    # +0x24
var passes: int = 0                  # +0x26
var passes_completed: int = 0        # +0x28
var current_line: int = 0            # +0x2a
var carrier_history: PackedInt32Array = PackedInt32Array([-1, -1, -1])   # +0x30/+0x32/+0x34 roster idx
var skaters_on_ice: int = 6          # +0x36 (goalie included)
var line_request: int = -1           # +0x38
var nearest_dist: int = 0xffff       # +0x3e distance of the nearest skater to the puck
var nearest_slot: int = -1           # +0x42
var flags: int = 0                   # +0x44
var energy: PackedInt32Array = PackedInt32Array()      # +0x46, 27 x 0..0x1000
var entity_of: PackedInt32Array = PackedInt32Array()   # +0x7e, 27 x entity slot or -2 (bench)
var goalie_slot: int = -1            # +0xfa
var first_slot: int = 0              # index of players[0] in Sim.entities
var attacks_up: bool = false         # the goal this team shoots at is at +y (flags & 0x80 of its players)

func _init(idx: int = 0) -> void:
	index = idx
	first_slot = idx * 6
	energy.resize(27)
	entity_of.resize(27)
	for i in 27:
		energy[i] = 0x1000
		entity_of[i] = -2

func reset_nearest() -> void:
	nearest_dist = 0xffff
	nearest_slot = -1
