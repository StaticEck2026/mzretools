class_name InfoPanel
## The scoreboard panel of the stoppages: it opens for a goal, a penalty, an injury or the three
## stars, shows up to five lines of text and may play a short clip of the crowd or the referee
## (GOAL, SIREN, CLAP, HOOK, ... from Tables.announcer_ppv_names). The referee waits for it, which
## is what gives a goal celebration its length. Ports of sub_66dda (open), load_cutscene_clip,
## update_announcer (the panel part), show_penalty, announce_goal, record_penalty and
## announce_injury; draw_penalty_box_overlay draws it (view/Hud.gd).

const OPEN := 0x10
const HELD := 0x100
const CLOSING := 600
const CLOSED_AFTER := 0x268

const CLIP_FAN_ANTHEM := 0
const CLIP_GOAL := 1
const CLIP_CLAP := 2
const CLIP_USA_FLAG := 3
const CLIP_CANADA_FLAG := 4
const CLIP_SIREN := 5
const CLIP_ROUGHING := 6
const CLIP_HOOKING := 7
const CLIP_SAVE := 8
const CLIP_CROSS_CHECK := 9
const CLIP_GUILTY := 10

## sub_66dda: opens the panel (or starts the clip when it was held open)
static func open(sim: Sim) -> void:
	sim.panel = OPEN if sim.panel == HELD else 0

## the panel starts to close (the stoppage moves on)
static func close(sim: Sim) -> void:
	if sim.panel == HELD:
		sim.panel = CLOSING

static func set_text(sim: Sim, lines: Array) -> void:
	for i in 5:
		sim.panel_text[i] = lines[i] if i < lines.size() else ""

## load_cutscene_clip (0x66497): the clip's frames are loaded and its script starts
static func load_clip(sim: Sim, id: int) -> void:
	var script: Array = Tables.clip_scripts[id]
	sim.clip = id
	sim.clip_pos = 1
	sim.clip_time = Tables.clip_frame_steps[id]
	sim.clip_frame = script[1]

## the panel part of update_announcer (0x66e06), run every step while play is stopped
static func update(sim: Sim) -> void:
	if sim.panel < 0:
		return
	if not (sim.stoppage_timer < 0x100 or sim.stoppage_timer > 0x140 or sim.game_over):
		return
	if sim.clip == CLIP_FAN_ANTHEM and sim.clip_frame < 5 and sim.crowd_noise < 0x5dc:
		if sim.clip_pos == 1 and sim.crowd_noise < 0x280:
			sim.crowd_noise = 0x280
		var p := sim.clip_pos
		if (p > 0 and p < 5) or (p > 7 and p < 0xd) or p > 0x10:
			sim.crowd_noise += 8
	if sim.panel == OPEN and sim.clip >= 0:
		sim.clip_time -= 1
		if sim.clip_time < 0:
			var script: Array = Tables.clip_scripts[sim.clip]
			if script[0] == sim.clip_pos:
				if Tables.clip_closes[sim.clip] != 0:
					sim.panel = CLOSING
				sim.clip_frame = -1
				sim.clip = -1
			else:
				sim.clip_frame = script[sim.clip_pos + 1]
				sim.clip_pos += 1
				sim.clip_time = Tables.clip_frame_steps[sim.clip]
		return
	if sim.panel < HELD or sim.panel >= CLOSING:
		sim.panel += 1
	if sim.panel > CLOSED_AFTER:
		sim.panel = -1
		set_text(sim, [])

## the stoppage is over (ai_puck_faceoff2, period_init): the panel disappears
static func reset(sim: Sim) -> void:
	sim.panel = -1
	sim.clip = -1
	sim.clip_frame = -1
	set_text(sim, [])

## the time of the event in the period, as the original computes it (minutes, seconds)
static func elapsed(sim: Sim) -> Vector2i:
	var t := sim.period_length - sim.clock_seconds
	if sim.clock_seconds < 0x3c and sim.clock_sub != 0:
		t -= 1
	return Vector2i(t / 60, t % 60)

static func player_name(sim: Sim, t: int, r: int) -> String:
	return Ceremonies.star_caption(sim, t, r)

static func _log(sim: Sim, entry: Array) -> void:
	if sim.no_stats:
		return
	if sim.event_log.size() >= 8:
		sim.event_log[7] = entry
	else:
		sim.event_log.append(entry)

## announce_goal (0x62343) and show_penalty type 1: "12:34 Boston", the scorer (PP / SH), the
## assists; a home goal plays the GOAL or SIREN clip
static func announce_goal(sim: Sim, team: int, scorer: int, assist1: int, assist2: int) -> void:
	var t := elapsed(sim)
	_log(sim, ["goal", team, scorer, assist1, assist2, sim.period, t.x, t.y])
	if team == 0:
		load_clip(sim, CLIP_GOAL if sim.random(0x14) < 10 else CLIP_SIREN)
	var scoring := sim.teams[team]
	var tag := ""
	if sim.goal_flags & 2:
		tag = " SH"
	elif sim.goal_flags & 4:
		tag = " PP"
	var name := scoring.info.name if scoring.info != null else scoring.abbrev()
	var lines := ["%02d:%02d %s" % [t.x, t.y, name], player_name(sim, team, scorer) + tag, "Unassisted", "", ""]
	if assist1 >= 0:
		lines[2] = "Assists:"
		lines[3] = player_name(sim, team, assist1)
		if assist2 >= 0:
			lines[4] = player_name(sim, team, assist2)
	set_text(sim, lines)
	open(sim)

## record_penalty (0x624b9) and show_penalty type 2: "12:34 BOS Penalty", the player, the
## penalty, "2 minutes" / "game misconduct"; or the penalty shot. A clip of the crowd (GUILTY for
## an away penalty now and then) or of the foul when the panel is free.
static func record_penalty(sim: Sim, team: int, roster: int, type: int, minutes: int) -> void:
	var t := elapsed(sim)
	_log(sim, ["penalty", team, roster, type, sim.period, t.x, t.y])
	var idx := type - 9
	if sim.panel == -1 and idx != 0x11:
		var clip := -1
		if team == 0 or sim.random(4) != 0:
			if idx == 4:
				if sim.random(3) == 0:
					clip = CLIP_ROUGHING
			elif idx == 6:
				if sim.random(3) == 0:
					clip = CLIP_HOOKING
			elif idx == 5 and sim.random(3) == 0:
				clip = CLIP_CROSS_CHECK
		else:
			clip = CLIP_GUILTY
		if clip >= 0:
			load_clip(sim, clip)
	var abbrev := sim.teams[team].abbrev()
	if idx == 0x11:
		var shooter_team := sim.penalty_shot_team
		set_text(sim, ["%02d:%02d %s" % [t.x, t.y, sim.teams[shooter_team].abbrev()], "Penalty shot", "to be taken by",
			player_name(sim, shooter_team, sim.penalty_shot_roster), ""])
	else:
		var what := "game misconduct" if minutes < 0 else "%d minutes" % minutes
		set_text(sim, ["%02d:%02d %s Penalty" % [t.x, t.y, abbrev], player_name(sim, team, roster),
			Tables.penalty_names[clampi(idx, 0, Tables.penalty_names.size() - 1)], what, ""])
	open(sim)
	if sim.crowd_noise > 400:
		sim.crowd_noise = 400

## announce_injury (0x62764) and show_penalty type 3
static func announce_injury(sim: Sim, team: int, roster: int, for_game: bool) -> void:
	var t := elapsed(sim)
	_log(sim, ["injury", team, roster, for_game, sim.period, t.x, t.y])
	if sim.no_stats:
		return
	set_text(sim, ["%02d:%02d %s Injury" % [t.x, t.y, sim.teams[team].abbrev()], player_name(sim, team, roster),
		"gone for the game" if for_game else "gone for 1 period", "", ""])
	open(sim)

## play_speech: the announcer line is queued for the audio layer (XBRUCE2.VIV)
static func speech(sim: Sim, id: int) -> void:
	sim.speech_queue.append(id)

## the announcer and crowd clips are on: option byte 2 bit 0 and sound
static func speech_on(sim: Sim) -> bool:
	return (sim.settings2 & 1) != 0 and sim.sound_enabled

## ref_check_announcements (0x4e6ef), when the referee picks up the puck after a routine stoppage
## (frozen puck, goalie hold, icing, offside, two line pass, a hit on the referee): halfway and
## late game lines, the power play, or a crowd clip (the fans, the clapping crowd). True when a
## clip started: the referee waits for it.
static func ref_announcements(sim: Sim) -> bool:
	if sim.no_stats or sim.panel != -1:
		return false
	var inf := sim.ref_infraction
	if inf != Rules.INF_TWO_LINE and inf != Rules.INF_REF_HIT and inf != Rules.INF_FROZEN and inf != Rules.INF_GOALIE_HOLD \
			and inf != Rules.INF_OFFSIDE and inf != Rules.INF_ICING:
		return false
	if sim.clock_seconds < sim.period_length / 2 and sim.clock_seconds > 0x3b and sim.half_announce:
		sim.half_announce = false
		speech(sim, 2)
		return false
	if sim.period == 2 and sim.clock_seconds <= sim.announce_time:
		sim.announce_time = -1
		speech(sim, 5)
		return false
	var d := sim.teams[1].skaters_on_ice - sim.teams[0].skaters_on_ice
	if speech_on(sim) and d != 0 and sim.random(4) == 0:
		speech(sim, 1 if d < 1 else 4)
		return false
	var r := sim.random(8)
	if r == 0:
		if (sim.sound_device & 0x2a) != 0 and sim.crowd_noise < 0x2bd:
			load_clip(sim, CLIP_FAN_ANTHEM)
			open(sim)
			return true
	elif r == 1:
		load_clip(sim, CLIP_CLAP)
		speech(sim, 9)
		open(sim)
		return true
	elif r < 5:
		speech(sim, r + 4)
	elif r == 5:
		speech(sim, 0xb)
	return false
