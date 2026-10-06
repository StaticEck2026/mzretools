class_name Team
extends RefCounted
## One of the two team records (0xdf614 home, 0xdf714 away, 0x100 bytes each). Only the fields the
## simulation uses are kept; statistics are reduced to the few counters the rules touch.
## Offsets refer to re/nhl_hockey/STRUCTURES.md.

const FL_LINE_CHANGE_UI := 0x02      # +0x44 bit 1: line change menu open
const FL_OFFSIDE := 0x10             # +0x44 bit 4: an attacker is offside (check_offside)
const FL_PULLED_GOALIE := 0x80       # players[0].flags & 0x80 is the attack direction, this is ours

var index: int = 0                   # 0 home, 1 away
var power_plays: int = 0             # +0x04 power plays (update_power_play)
var goals: int = 0                   # +0x10
var shots: int = 0                   # +0x12
var faceoffs_won: int = 0            # +0x14
var one_timer_goals: int = 0         # +0x1a
var breakaway_goals: int = 0         # +0x1e
var penalty_shots: int = 0           # +0x20 penalty shots awarded
var penalty_shot_goals: int = 0      # +0x22
var hits: int = 0                    # +0x24
var passes: int = 0                  # +0x26
var passes_completed: int = 0        # +0x28
var current_line: int = 0            # +0x2a 0..3 forward lines, 4..5 power play units, 6..7 penalty killing units
var dpair_counter: int = 0           # +0x2c defence pair in use with the forward lines (rotates 0, 1, 2)
var extra_attacker: int = -1         # +0x2e roster index of the extra attacker while the goalie is pulled
var carrier_history: PackedInt32Array = PackedInt32Array([-1, -1, -1])   # +0x30/+0x32/+0x34 roster idx
var skaters_on_ice: int = 6          # +0x36 players dressed (goalie included)
var goalie_request: int = 0          # +0x38 word: low nibble = goalie 0/1, 0xff00 = pulled by the CPU (reverts at the next faceoff), 0xfff0 = pulled by the user
var line_change_ui: bool = false     # word_cbc6a: the line change prompt is open
var nearest_dist: int = 0xffff       # +0x3e distance of the nearest skater to the puck
var nearest_slot: int = -1           # +0x42
var flags: int = 0                   # +0x44
var energy: PackedInt32Array = PackedInt32Array()      # +0x46, 28 x 0..0x1000
var entity_of: PackedInt32Array = PackedInt32Array()   # +0x7e, 28 x: -1 on the ice, -2 on the bench, -3 not available, 1 in the penalty box
var strategy: int = 0                # +0xd2 index into Tables.line_preference (coaching strategy)
var strategy2: int = 0               # +0xd3
var flags2: int = 0                  # +0xd4: 0x01 the CPU picks its own lines (else it mirrors the opponent), 0x40 line just changed, 0x80 alternate
var mode: int = 0                    # +0xd5 adjust_strategy mode
var energy_threshold: int = 0xccc    # +0xd6 a line below this average energy is changed
var goalie_slot: int = -1            # +0xfa
var injured: Array = []              # roster indices hurt for the rest of the period (entity_of -3)
var penalties: Array = []            # +0xb6 list: [roster_idx, seconds left, entity slot, minor]
var first_slot: int = 0              # index of players[0] in Sim.entities
var attacks_up: bool = false         # the goal this team shoots at is at +y (flags & 0x80 of its players)
# per player game statistics (the 0x10 byte records at team +0xe6): goals, assists, penalty
# minutes, plus/minus, power play goals, short handed goals, empty net goals, shots
const ST_GOALS := 0
const ST_ASSISTS := 1
const ST_PIM := 2
const ST_PLUS_MINUS := 3
const ST_PPG := 4
const ST_SHG := 5
const ST_ENG := 6
const ST_SHOTS := 7
var player_stats: Array = []         # 25 x PackedInt32Array(8)
var goalie_stats: Array = []         # team +0xea: 3 x [time, shots against, goals against]
var info: Database.TeamInfo = null   # roster from the databases (null: placeholder players)

func _init(idx: int = 0) -> void:
	index = idx
	first_slot = idx * 6
	energy.resize(28)
	entity_of.resize(28)
	for i in 28:
		energy[i] = 0x1000
		entity_of[i] = -2
	reset_stats()

func reset_stats() -> void:
	player_stats.clear()
	for i in 25:
		player_stats.append(PackedInt32Array([0, 0, 0, 0, 0, 0, 0, 0]))
	goalie_stats.clear()
	for i in 3:
		goalie_stats.append(PackedInt32Array([0, 0, 0]))
	goals = 0
	shots = 0
	hits = 0
	one_timer_goals = 0
	breakaway_goals = 0
	penalty_shots = 0
	penalty_shot_goals = 0

## adds to a player's statistic (skaters 0..24 only, like the original's table)
func add_stat(roster: int, field: int, amount: int = 1) -> void:
	if roster >= 0 and roster < 25:
		player_stats[roster][field] += amount

func stat(roster: int, field: int) -> int:
	return player_stats[roster][field] if roster >= 0 and roster < 25 else 0

## the goalie in the net (line table +0x24 + goalie_request), as 0..2, or -1 when pulled
func goalie_index() -> int:
	if goalie_pulled():
		return -1
	var lt := Lines.line_table(self)
	var k := 0x24 + (goalie_request & 0xff)
	if k >= lt.size():
		return -1
	var g := lt[k] - 25
	return g if g >= 0 and g < 3 else -1

## the goalie is off for an extra attacker (goalie_request < 0 as a 16 bit word)
func goalie_pulled() -> bool:
	return (goalie_request & 0x8000) != 0

func reset_nearest() -> void:
	nearest_dist = 0xffff
	nearest_slot = -1

func abbrev() -> String:
	if info != null:
		return info.abbrev
	return "HOME" if index == 0 else "AWAY"
