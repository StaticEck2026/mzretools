class_name Scoreboard
## The state behind the scoreboard below the ice (draw_clock 0x14cf1 and the routines around it):
## its own clock and the penalty clocks of the two teams.
##
## The clock of the scoreboard is not the game clock: show_scoreboard (0x150c6) sets it to the
## period length at the start of the match and of each period; run_sim_steps adds 100 to
## dword_d8c78 for every step played (not during a penalty shot); game_loop turns that into
## hundredths for the frame (24 steps a second, the rest kept, dword_dc28c), and a period over with
## the game clock at 0 runs the whole rest out; draw_clock counts the clock down by them
## (hud_clock_count_down) and, unless the clock ran out or statistics are not kept, the first two
## penalties of each list (penalty_clocks_count_down).
##
## The penalty list of a team (word_c571c home, word_c575c away): 8 entries of 4 words, the player's
## number (-1 a free entry), minutes, seconds, hundredths. add_penalty_display (0x14c22) fills the
## first free entry, penalty_list_find (0x14ca0) ends the penalty of a player a goal released, the
## count down drops the entries run out and moves the rest up. The panel of a team shows the penalty
## clocks unless its line change prompt is open, its "lines" flag (dword_c5844 / dword_c5848) is set
## (draw_clock sets it when the list is empty, a new penalty clears it) or statistics are not kept.

const ENTRIES := 8

## penalty_lists_reset (0x1cbd8, from load_player_graphics at the start of a match)
static func reset_lists(sim: Sim) -> void:
	for t in 2:
		var l: Array = sim.penalty_lists[t]
		for i in ENTRIES:
			l[i * 4] = -1
			l[i * 4 + 1] = 0
			l[i * 4 + 2] = 0
			l[i * 4 + 3] = 0

## show_scoreboard (0x150c6) apart from its drawing: with `new_period` the clock is set to the
## period length (MatchSetup.period_length: the overtime's); the panels' flags are cleared
static func start(sim: Sim, new_period: bool) -> void:
	if new_period:
		var s := Entity.to_s16(MatchSetup.period_length(sim))
		sim.hud_clock[0] = _quot(s, 60)
		sim.hud_clock[1] = s - _quot(s, 60) * 60
		sim.hud_clock[2] = 0
	sim.hud_frame = 0
	sim.hud_lines_only[1] = false
	sim.hud_lines_only[0] = false

## add_penalty_display (0x14c22): the penalty into the first free entry of the team's list (none
## free: nothing); its "lines" flag cleared
static func add_penalty_display(sim: Sim, away: int, number: int, minutes: int) -> void:
	if sim.stubbed("add_penalty_display", [away, number, minutes]):
		return
	var t := 1 if (away & 0xffff) != 0 else 0
	var l: Array = sim.penalty_lists[t]
	for i in ENTRIES:
		if l[i * 4] == -1:
			l[i * 4] = Entity.to_s16(number)
			l[i * 4 + 1] = Entity.to_s16(minutes)
			l[i * 4 + 3] = 0
			l[i * 4 + 2] = 0
			sim.hud_lines_only[t] = false
			return

## penalty_list_find (0x14ca0): the first entry of the player's number runs out (0:00.00; the count
## down drops it)
static func penalty_list_find(sim: Sim, away: int, number: int) -> void:
	if sim.stubbed("penalty_list_find", [away, number]):
		return
	var l: Array = sim.penalty_lists[1 if (away & 0xffff) != 0 else 0]
	for i in ENTRIES:
		if l[i * 4] == Entity.to_s16(number):
			l[i * 4 + 3] = 0
			l[i * 4 + 2] = 0
			l[i * 4 + 1] = 0
			return

## run_sim_steps (0x1149a): a step played adds to the scoreboard's hundredths (not during a
## penalty shot)
static func step_played(sim: Sim) -> void:
	if not sim.penalty_shot:
		sim.hud_acc += 100

## the frame of game_loop (0x11693) after the steps: the hundredths of the frame (none during a
## penalty shot; all of the clock left at the end of a period), then draw_clock
static func frame(sim: Sim) -> void:
	if sim.penalty_shot:
		sim.hud_hundredths = 0
	else:
		sim.hud_hundredths = _quot(sim.hud_acc, 24)
		sim.hud_acc -= sim.hud_hundredths * 24
		if sim.period_over != 0 and sim.clock_seconds == 0 and sim.clock_sub == 0:
			sim.hud_hundredths = (sim.hud_clock[0] * 60 + sim.hud_clock[1]) * 100 + sim.hud_clock[2]
	draw_clock(sim)

## draw_clock (0x14cf1) apart from its drawing: the count down of the clock and the penalty clocks,
## then which panel each team shows (hud_penalties); nothing while the clock is not set (minutes
## below 0)
static func draw_clock(sim: Sim) -> void:
	if sim.hud_clock[0] < 0:
		return
	sim.hud_frame = sim.hud_hundredths
	sim.hud_hundredths = 0
	if clock_count_down(sim, sim.hud_frame) and not sim.no_stats:
		penalty_clocks_count_down(sim.penalty_lists[0], sim.hud_frame)
		penalty_clocks_count_down(sim.penalty_lists[1], sim.hud_frame)
	for t in 2:
		sim.hud_penalties[t] = false
		if sim.teams[t].line_change_ui or sim.hud_lines_only[t] or sim.no_stats:
			continue
		if sim.penalty_lists[t][0] < 0:
			sim.hud_lines_only[t] = true
			continue
		sim.hud_penalties[t] = true

## hud_clock_count_down (0x15374): the clock less the hundredths (one borrow of each digit at most);
## false when it ran out (all 0)
static func clock_count_down(sim: Sim, hundredths: int) -> bool:
	var c: PackedInt32Array = sim.hud_clock
	c[2] = _i32(c[2] - hundredths)
	if c[2] < 0:
		c[2] = _i32(c[2] + 100)
		c[1] = _i32(c[1] - 1)
		if c[1] < 0:
			c[1] = 0x3b
			c[0] = _i32(c[0] - 1)
			if c[0] < 0:
				c[2] = 0
				c[1] = 0
				c[0] = 0
				sim.hud_clock = c
				return false
	sim.hud_clock = c
	return true

## penalty_clocks_count_down (0x15655): the first two entries less the hundredths (word
## arithmetic, one borrow; an entry run out is freed), then the entries in use moved up over the
## free ones
static func penalty_clocks_count_down(l: Array, hundredths: int) -> void:
	for i in 2:
		var o := i * 4
		l[o + 3] = Entity.to_s16(l[o + 3] - hundredths)
		if l[o + 3] >= 0:
			continue
		l[o + 3] = Entity.to_s16(l[o + 3] + 100)
		l[o + 2] = Entity.to_s16(l[o + 2] - 1)
		if l[o + 2] >= 0:
			continue
		l[o + 2] = 0x3b
		l[o + 1] = Entity.to_s16(l[o + 1] - 1)
		if l[o + 1] >= 0:
			continue
		l[o + 1] = 0
		l[o + 2] = 0
		l[o + 3] = 0
		l[o] = -1
	for i in ENTRIES - 1:
		if l[i * 4] >= 0:
			continue
		var to := i
		for k in range(i + 1, ENTRIES):
			if l[k * 4] < 0:
				continue
			for w in 4:
				l[to * 4 + w] = l[k * 4 + w]
			l[k * 4] = -1
			to += 1

## C division of signed integers (truncated)
static func _quot(a: int, b: int) -> int:
	var q := absi(a) / absi(b)
	return q if (a < 0) == (b < 0) else -q

static func _i32(v: int) -> int:
	v &= 0xffffffff
	return v - 0x100000000 if v & 0x80000000 else v
