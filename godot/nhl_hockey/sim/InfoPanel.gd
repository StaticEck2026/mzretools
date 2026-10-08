class_name InfoPanel
## The scoreboard panel of the stoppages: it opens for a goal, a penalty, an injury or the three
## stars, shows up to five lines of text and may play a short clip of the crowd or the referee
## (GOAL, SIREN, CLAP, HOOK, ... from Tables.announcer_ppv_names). The referee waits for it, which
## is what gives a goal celebration its length. Ports of info_panel_open (open), load_cutscene_clip,
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

## info_panel_open: opens the panel (or starts the clip when it was held open)
static func open(sim: Sim) -> void:
	sim.panel = OPEN if sim.panel == HELD else 0

## the panel starts to close (the stoppage moves on)
static func close(sim: Sim) -> void:
	if sim.panel == HELD:
		sim.panel = CLOSING

static func set_text(sim: Sim, lines: Array) -> void:
	for i in 5:
		sim.panel_text[i] = lines[i] if i < lines.size() else ""

## load_cutscene_clip (0x66497): the clip's frames are loaded (by the view; a hook) and its script
## starts: the first frame, the steps it shows
static func load_clip(sim: Sim, id: int) -> void:
	sim.stubbed("load_clip", [id])
	var script: Array = Tables.clip_scripts[id]
	sim.clip = id
	sim.clip_pos = 1
	sim.clip_time = Tables.clip_frame_steps[id]
	sim.clip_frame = script[1]

## the panel part of update_announcer (0x66e06), run every step while play is stopped
static func update(sim: Sim) -> void:
	if sim.stubbed("update_announcer", []):
		return
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

## the goalie of a team's line table in the net (line table +0x24 + the goalie chosen)
static func _goalie_byte(sim: Sim, t: int) -> int:
	var team := sim.teams[t]
	var lt := Lines.line_table(team)
	var k := 0x24 + (team.goalie_request & 1)
	return lt[k] if k < lt.size() else 0xff

## SCOR2B (font_scor2b): the panel fits the players' names into 124 pixels of it (the view and the
## tests load it; without it a character counts 6 pixels)
static var name_font: Vfn = null

static func text_width(s: String) -> int:
	return name_font.text_width(s) if name_font != null else s.length() * 6

## format_player_name (0x61d48): "#12 First Last" and the suffix in 124 pixels of SCOR2B, else
## "#12 F. Last", else "#12 Last", else the last name cut to what the rest leaves
static func format_player_name(prefix: String, number: int, first: String, last: String, suffix: String) -> String:
	var s := "%s#%d %s %s%s" % [prefix, number, first, last, suffix]
	if text_width(s) <= 0x7c:
		return s
	# (%c of an empty first name writes the string's end)
	s = "%s#%d %s. %s%s" % [prefix, number, first.left(1), last, suffix] if first != "" else "%s#%d " % [prefix, number]
	if text_width(s) <= 0x7c:
		return s
	s = "%s#%d %s%s" % [prefix, number, last, suffix]
	if text_width(s) <= 0x7c:
		return s
	var room := 0x7c - text_width("%s#%d %s" % [prefix, number, suffix])
	var cut := last
	while text_width(cut) > room and cut != "":
		cut = cut.left(cut.length() - 1)
	return "%s#%d %s%s" % [prefix, number, cut, suffix]

## the panel's name of roster player r of team t (his number and names of the player records)
static func player_name(sim: Sim, t: int, r: int, suffix := "") -> String:
	var team := sim.teams[t]
	var first := team.first_names[r] if r >= 0 and r < team.first_names.size() else ""
	var last := team.last_names[r] if r >= 0 and r < team.last_names.size() else ""
	return format_player_name("", Speech.number(sim, t, r & 0xff), first, last, suffix)

## show_penalty (0x61e99): the panel's lines for the event record (dword_e9ac8). A goal: "12:34
## Boston", the scorer (" SH" / " PP", in a league game with statistics his goals of the season so
## far, " (12)"), "Unassisted" or "Assists:" and the assists; a penalty: "12:34 BOS Penalty", the
## player, the penalty, "2 minutes" / "game misconduct", or "Penalty shot to be taken by" the
## shooter; an injury: "12:34 BOS Injury", the player, "gone for the game" / "gone for 1 period"
## (another record: the lines cleared)
static func show_penalty(sim: Sim) -> void:
	if sim.stubbed("show_penalty", []):
		return
	var r := sim.event_rec
	var lines := ["", "", "", "", ""]
	match r[0]:
		1:
			var t: int = r[1]
			var p: int = r[2]
			lines[0] = "%02d:%02d %s" % [r[7], r[8], sim.teams[t].title_name]
			var tag := " SH" if r[5] & 2 else (" PP" if r[5] & 4 else "")
			if sim.league_game and not sim.no_stats and p < 0x19:
				tag += " (%d)" % (sim.teams[t].player_stats[p][Team.ST_GOALS] + sim.teams[t].season_goals[p])
			lines[1] = player_name(sim, t, p, tag)
			if r[3] == 0xff:
				lines[2] = "Unassisted"
			else:
				lines[2] = "Assists:"
				lines[3] = player_name(sim, t, r[3])
			if r[4] != 0xff:
				lines[4] = player_name(sim, t, r[4])
		2:
			var t: int = r[1]
			if r[3] == 0x11:
				var st := sim.penalty_shot_team
				lines[0] = "%02d:%02d %s" % [r[6], r[7], sim.teams[st].title_abbrev]
				lines[1] = "Penalty shot"
				lines[2] = "to be taken by"
				lines[3] = player_name(sim, st, sim.penalty_shot_roster)
			else:
				lines[0] = "%02d:%02d %s Penalty" % [r[6], r[7], sim.teams[t].title_abbrev]
				lines[1] = player_name(sim, t, r[2])
				lines[2] = Tables.penalty_names[clampi(r[3], 0, Tables.penalty_names.size() - 1)]
				lines[3] = "game misconduct" if r[4] == 0xff else "%d minutes" % r[4]
		3:
			var t: int = r[1]
			lines[0] = "%02d:%02d %s Injury" % [r[5], r[6], sim.teams[t].title_abbrev]
			lines[1] = player_name(sim, t, r[2])
			lines[2] = "gone for the game" if Entity.to_s8(r[3]) > 0 else "gone for 1 period"
	set_text(sim, lines)

## the event record (dword_e9ac8) into the events of the stoppage (unk_e9b4c, at most eight: a
## ninth replaces the last), which gsummary_flush writes into the game summary
static func _buffer_event(sim: Sim) -> void:
	sim.events[sim.event_count] = sim.event_rec.duplicate()
	sim.event_count += 1
	if sim.event_count >= 8:
		sim.event_count = 7


## announce_goal (0x62343) and show_penalty type 1: the record (1, team, scorer, assists or -1,
## the goal flags, the period count, the time, both goalies), the stoppage's events and the
## period's goals unless nothing is recorded; a home goal plays the GOAL or SIREN clip; "12:34
## Boston", the scorer (PP / SH), the assists; the call of the goal waits for the panel
static func announce_goal(sim: Sim, team: int, scorer: int, assist1: int, assist2: int) -> void:
	var t := elapsed(sim)
	var r := sim.event_rec
	r[0] = 1
	r[1] = team & 0xff
	r[2] = scorer & 0xff
	r[3] = assist1 & 0xff
	r[4] = assist2 & 0xff
	r[5] = sim.goal_flags & 0xff
	r[6] = sim.period_num & 0xff
	r[7] = t.x & 0xff
	r[8] = t.y & 0xff
	r[9] = _goalie_byte(sim, team)
	r[10] = _goalie_byte(sim, team ^ 1)
	if not sim.no_stats:
		_buffer_event(sim)
		sim.gs_trailer[1 + team * 2] += 1
	if team == 0:
		load_clip(sim, CLIP_GOAL if sim.random(0x14) < 10 else CLIP_SIREN)
	show_penalty(sim)
	open(sim)
	sim.goal_call = [team, Entity.to_s8(scorer), Entity.to_s8(assist1), Entity.to_s8(assist2)]

## record_penalty (0x624b9) and show_penalty type 2, unless nothing is recorded: the record (2,
## team, player, the penalty, minutes, the period count, the time) into the stoppage's events; with
## the panel free a clip now and then (GUILTY for an away penalty, else the foul's: ROUGHING,
## HOOKING, CROSS CHECK); "12:34 BOS Penalty", the player, the penalty, "2 minutes" / "game
## misconduct", or the penalty shot; a quiet crowd; the announcer: "and number" for the next
## penalty of the same team, "penalties on" when another one of the team is queued
static func record_penalty(sim: Sim, team: int, roster: int, kind: int, minutes: int, mm: int, ss: int, queue_index: int) -> void:
	if sim.no_stats:
		return
	var r := sim.event_rec
	r[0] = 2
	r[1] = team & 0xff
	r[2] = roster & 0xff
	r[3] = kind & 0xff
	r[4] = minutes & 0xff
	r[5] = sim.period_num & 0xff
	r[6] = mm & 0xff
	r[7] = ss & 0xff
	_buffer_event(sim)
	if sim.panel == -1 and kind != 0x11:
		var clip := -1
		if team != 0 and sim.random(4) == 0:
			clip = CLIP_GUILTY
		elif kind == 4:
			if sim.random(3) == 0:
				clip = CLIP_ROUGHING
		elif kind == 6:
			if sim.random(3) == 0:
				clip = CLIP_HOOKING
		elif kind == 5 and sim.random(3) == 0:
			clip = CLIP_CROSS_CHECK
		if clip >= 0:
			load_clip(sim, clip)
	show_penalty(sim)
	open(sim)
	if sim.crowd_noise > 400:
		sim.crowd_noise = 400
	if kind == 0x11:
		var st := sim.penalty_shot_team
		var num := Speech.number(sim, st, sim.penalty_shot_roster)
		Speech.say(sim, Speech.penalty_shot(Speech.abbrev(sim, st), num, mm, ss))
		return
	var mode := 2
	if sim.last_penalty_team != team:
		mode = 1
		sim.last_penalty_team = team
	var count := mode
	if queue_index > 0:
		var nxt := Rules.inf_slot(sim, queue_index - 1) & 0x1f
		if (1 if nxt >= 6 else 0) == team:
			count += 1
	var last := queue_index == 0
	var number := Speech.number(sim, team, roster)
	Speech.say(sim, Speech.penalty(Speech.abbrev(sim, team), number, minutes, kind + 9, mm, ss, mode == 1, count, last))
	if last:
		sim.last_penalty_team = -1

## announce_injury (0x62764) and show_penalty type 3, unless nothing is recorded: the record (3,
## team, player, 1 out for the game / -1 for the period, the period count, the time) into the
## stoppage's events; "12:34 BOS Injury", the player, "gone for the game" / "gone for 1 period"
static func announce_injury(sim: Sim, team: int, roster: int, for_game: bool) -> void:
	if sim.no_stats:
		return
	var t := elapsed(sim)
	var r := sim.event_rec
	r[0] = 3
	r[1] = team & 0xff
	r[2] = roster & 0xff
	r[3] = 1 if for_game else 0xff
	r[4] = sim.period_num & 0xff
	r[5] = t.x & 0xff
	r[6] = t.y & 0xff
	_buffer_event(sim)
	show_penalty(sim)
	open(sim)

## play_speech (0x59a11): a song of the music driver (the organ: 0..5 the home team's, 6..8
## random ones, 9 the stomp to the clapping, 10 the anthem, 11 ROCKDITI), queued for the audio
## layer (MusicCues picks the song)
static func music(sim: Sim, id: int) -> void:
	if sim.stubbed("play_speech", [id]):
		return
	sim.music_queue.append(id)

## stop_crowd_loop (0x59981): the running song stops (the puck drop, a penalty shot)
static func stop_music(sim: Sim) -> void:
	if sim.stubbed("stop_crowd_loop", []):
		return
	sim.music_queue.append(-1)

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
	if inf != Rules.INF_TWO_LINE and inf != Rules.INF_NET_OFF and inf != Rules.INF_FROZEN and inf != Rules.INF_GOALIE_HOLD \
			and inf != Rules.INF_OFFSIDE and inf != Rules.INF_ICING:
		return false
	if (sim.period_length >> 1) > sim.clock_seconds and sim.clock_seconds >= 0x3c and sim.half_announce:
		sim.half_announce = false
		music(sim, 2)
		return false
	if sim.period == 2 and sim.clock_seconds <= sim.announce_time:
		sim.announce_time = -1
		music(sim, 5)
		return false
	var d := sim.teams[1].skaters_on_ice - sim.teams[0].skaters_on_ice
	if speech_on(sim) and d != 0 and sim.random(4) == 0:
		music(sim, 4 if d > 0 else 1)
		return false
	var r := sim.random(8)
	if not sim.demo and r == 0:
		if sim.opt_sound and (sim.sound_device & 0x2a) != 0 and sim.crowd_noise <= 0x2bc:
			load_clip(sim, CLIP_FAN_ANTHEM)
			if sim.clip != -1:
				open(sim)
				return true
		return false
	if not sim.demo and r == 1:
		load_clip(sim, CLIP_CLAP)
		if sim.clip == -1:
			return false
		music(sim, 9)
		open(sim)
		return true
	if r < 5:
		music(sim, r + 4)
	elif r == 5:
		music(sim, 0xb)
	return false
