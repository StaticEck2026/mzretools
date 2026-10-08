class_name Team
extends RefCounted
## One of the two team records (0xdf614 home, 0xdf714 away, 0x100 bytes each). Only the fields the
## simulation uses are kept; the team statistics are the counters of the Game Statistics screen
## (game_statistics_screen) and of the league files.
## Offsets refer to re/nhl_hockey/STRUCTURES.md.

const FL_LINE_CHANGE_UI := 0x02      # +0x44 bit 1: line change menu open
const FL_OFFSIDE := 0x10             # +0x44 bit 4: an attacker is offside (check_offside)
const FL_PULLED_GOALIE := 0x80       # players[0].flags & 0x80 is the attack direction, this is ours

var index: int = 0                   # 0 home, 1 away
var shots: int = 0                   # +0x00 shots on goal (shot_landed)
var pp_goals: int = 0                # +0x02 power play goals (goal_ends_penalty)
var power_plays: int = 0             # +0x04 power plays (update_power_play)
var pp_shots: int = 0                # +0x06 shots on a power play
var pp_time: int = 0                 # +0x08 seconds on a power play (lead_time_stats)
var penalty_count: int = 0           # +0x0a penalties (penalty_box_update)
var penalty_minutes: int = 0         # +0x0c
var zone_time: int = 0               # +0x0e seconds with the puck in the attacking zone (zone_time_stats)
var goals: int = 0                   # +0x10
var faceoffs_won: int = 0            # +0x12
var offensive_faceoffs: int = 0      # +0x14 faceoffs won in the attacking zone
var one_timer_tries: int = 0         # +0x16 one timers set up (one_timer_step)
var one_timers: int = 0              # +0x18 one timer shots
var one_timer_goals: int = 0         # +0x1a
var breakaways: int = 0              # +0x1c breakaways (note_breakaway)
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
var line_change_ui: bool = false     # line_change_prompt: the line change prompt is open
var nearest_d2: int = 0               # +0x3a the squared distance of the skater nearest to the puck (ai_nearest_to_puck)
var nearest_dist: int = 0xffff       # +0x3e distance of the nearest skater to the puck
var nearest_slot: int = -1           # +0x42
var flags: int = 0                   # +0x44
var energy: PackedInt32Array = PackedInt32Array()      # +0x46, 28 x 0..0x1000
var entity_of: PackedInt32Array = PackedInt32Array()   # +0x7e, 28 x: -1 on the ice, -2 on the bench, -3 not available, 1 in the penalty box
var numbers := PackedByteArray()      # byte 5 of the 28 player records of `rosters` (unk_db3ad): the jersey numbers the announcer and the penalty clocks use
var first_names := PackedStringArray() # +7 of the player records: the panel's names (format_player_name)
var last_names := PackedStringArray()  # +0x17
var season_goals := PackedInt32Array() # unk_deb7c (db_load_team_roster): a skater's goals of the season before the game, in a league
var title_abbrev := ""                 # team_names +0: "BOS"
var title_name := ""                   # team_names +0x1a: "Boston"
var strategy: int = 0                # +0xd2 index into Tables.line_preference (coaching strategy)
var strategy2: int = 0               # +0xd3
var flags2: int = 0                  # +0xd4: 0x01 the CPU picks its own lines (else it mirrors the opponent), 0x40 line just changed, 0x80 alternate
var mode: int = 0                    # +0xd5 adjust_strategy mode
var energy_threshold: int = 0xccc    # +0xd6 a line below this average energy is changed
var goalie_slot: int = -1            # +0xfa
# the candidate lists build_lines sorts by ratings at the start of the match (25 roster indices,
# best first, -1 after the last), 0x32 bytes apart from 0xe9cec (+0x19 for the away team): by
# position letter and for all skaters but defencemen, by the offensive and the defensive sums of
# the ratings; entry 6 (0xe9e18) holds the lineup flags of the players (cd418 of the roster status,
# 0 for the players in the line table's forward lines and defence pairs)
const PL_C := 0
const PL_R_DEF := 1
const PL_D := 2
const PL_C_DEF := 3
const PL_D_DEF := 4
const PL_L := 5
const PL_FLAGS := 6
const PL_SKATERS := 7
const PL_L_DEF := 8
const PL_R := 9
const PL_SKATERS_DEF := 10
var pos_lists: Array = []
# the attribute bytes of the pause menu's goalie choice (goalie 1, goalie 2, none; 1 = checked)
var goalie_menu: PackedByteArray = PackedByteArray([2, 2, 2])
# the status byte of each player's record in the global `rosters` (0xdb3a8, 0x27 bytes a player,
# 28 a team): 3 on the bench, 4 on the ice, 7 called on by the line editor (bench_player_slot)
var roster_status: PackedByteArray = PackedByteArray()
var box_queue: PackedInt32Array = PackedInt32Array()   # +0xb6: 28 roster indices of the box, in order, -1 after the last
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
	roster_status.resize(28)
	roster_status.fill(3)
	numbers.resize(28)
	first_names.resize(28)
	last_names.resize(28)
	season_goals.resize(25)
	box_queue.resize(28)
	box_queue.fill(-1)
	for k in 11:
		var l := PackedInt32Array()
		l.resize(25)
		l.fill(-1)
		pos_lists.append(l)
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
	pp_goals = 0
	power_plays = 0
	pp_shots = 0
	pp_time = 0
	penalty_count = 0
	penalty_minutes = 0
	zone_time = 0
	faceoffs_won = 0
	offensive_faceoffs = 0
	one_timer_tries = 0
	one_timers = 0
	hits = 0
	passes = 0
	passes_completed = 0
	one_timer_goals = 0
	breakaways = 0
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

## the players in the box in the order of the queue: [roster index, seconds left] (the scoreboard)
func box_list() -> Array:
	var out := []
	for r in box_queue:
		if r < 0:
			break
		if r < 28 and entity_of[r] > 0:
			out.append([r, entity_of[r] & 0x7ff])
	return out
