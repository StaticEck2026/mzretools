class_name Speech
## The announcer's sentences (say_goal 0x8531f, say_penalty 0x84f7b, say_penalty_shot 0x8511e,
## say_star 0x85213, say_time_remaining 0x84ddd, the one minute call say_one_minute_left, say_game_intro
## 0x84b0d). A sentence is a list of clip names of XBRUCE2.VIV in the order speech_release_clip
## appends them to the playback list (speech_queue_clip only loads them, without duplicates):
## numbers are "<n>.num" ("<nn>.num" with a leading zero for the seconds after the minutes), the
## teams "<abbrev>.tea" (after the star "<abbrev>.frm"), the arenas "<abbrev>.rnk", the penalties
## "<name>.pen", the phrases ".cor", ".bar" and ".int". The audio layer plays the clips back to
## back, each ending 0.26 s (0x1a ticks of 100 Hz) before its end.

const PENALTY_CLIPS := ["roughing", "", "charging", "slashing", "roughing", "xcheck", "hooking", "tripping",
	"interfer", "holding", "histick", "boarding", "elbowing", "abuse", "checkbnd", "boarding", "elbowing", "penshot"]

static func _num(n: int) -> String:
	return "%d.num" % n

## say_goal: "Boston goal ... number 12, assisted by number 77 and number 8"
static func goal(abbrev: String, scorer: int, assists: Array) -> PackedStringArray:
	var out := PackedStringArray([abbrev + ".tea", "goalnum.cor", _num(scorer)])
	if assists.size() > 0:
		out.append_array(["pause.cor", "asstnum.cor", _num(assists[0])])
	if assists.size() > 1:
		out.append_array(["pause.cor", "andnum.cor", _num(assists[1])])
	return out

## say_time_remaining / release_time_remaining_clips: "at 12 minutes" / "at 12 05" / "at 1 minute"
## / "at 30 seconds" / "at 1 second" (minutes and seconds of the period played)
static func time(minutes: int, seconds: int) -> PackedStringArray:
	var out := PackedStringArray(["at.cor", "pause.cor"])
	if minutes != 0:
		if seconds == 0:
			if minutes == 1:
				out.append("1minute.cor")
			else:
				out.append_array([_num(minutes), "minutes.cor"])
		else:
			out.append(_num(minutes))
	if seconds == 1:
		out.append("1second.cor" if minutes == 0 else "01.num")
	elif seconds > 1:
		if minutes == 0:
			out.append_array([_num(seconds), "seconds.cor"])
		else:
			out.append("%02d.num" % seconds)
	return out

## speech_minutes_clip: 2 or 5 minutes, the game misconduct
static func minutes_clip(minutes: int) -> String:
	if minutes == -1:
		return "gamemisc.cor"
	return "5min.cor" if minutes == 5 else "2min.cor"

## say_penalty: "Boston, penalty on number 12, 2 minutes, roughing, at ..."; the next penalty of
## the same team in a row says "and number"; "penalties on" when more of them are queued; the
## time only after the last one
static func penalty(abbrev: String, number: int, minutes: int, type: int, mm: int, ss: int,
		first: bool, count: int, with_time: bool) -> PackedStringArray:
	var out := PackedStringArray()
	if first:
		out.append(abbrev + ".tea")
		out.append("pennum.cor" if count < 2 else "pensnum.cor")
	else:
		out.append("andnum.cor")
	out.append_array([_num(number), "pause.cor", minutes_clip(minutes)])
	var idx := clampi(type - 9, 0, PENALTY_CLIPS.size() - 1)
	out.append_array([PENALTY_CLIPS[idx] + ".pen", "pause.cor"])
	if with_time:
		out.append_array(time(mm, ss))
	return out

## say_penalty_shot: "Boston, penalty shot, number 12, at ..."
static func penalty_shot(abbrev: String, number: int, mm: int, ss: int) -> PackedStringArray:
	var out := PackedStringArray([abbrev + ".tea", "penshot.cor", _num(number), "pause.cor"])
	out.append_array(time(mm, ss))
	return out

## say_star: "the third star, from Boston, number 12" (index 1..3)
static func star(index: int, abbrev: String, number: int) -> PackedStringArray:
	var names := ["", "1ststar.cor", "2ndstar.cor", "3rdstar.cor"]
	return PackedStringArray([names[clampi(index, 1, 3)], abbrev + ".frm", "pause.cor", "number.cor", _num(number)])

## say_one_minute_left: one minute left in the period
static func one_minute() -> PackedStringArray:
	return PackedStringArray(["oneleft.cor"])

## say_game_intro (0x84b14): "tonight at <arena>, an EA Sports game between <away> and <home>"
## (the arena: the home team's, Madison Square Garden for the all star game)
static func game_intro(home: String, away: String, arena: String = "") -> PackedStringArray:
	return PackedStringArray(["tonight.bar", (arena if arena != "" else home) + ".rnk", "easports.bar",
		"gamebtwn.bar", away + ".awa", "and.bar", home + ".hom"])

## speech_playoff_round2 / speech_playoff_round (0x84396 / 0x8430d): the clip of a play-off round
## said rising in the sentence ("u") or at its end ("d"): the quarter, semi and conference final of
## the east (conference 1) or the west (2), the Stanley Cup final (3); none for other values (the
## original leaves its buffer as it was)
static func playoff_round(conf: int, round: int, up: bool) -> String:
	var s := "u" if up else "d"
	if conf == 3:
		return "stanley%s.bar" % s
	if (conf == 1 or conf == 2) and round >= 1 and round <= 3:
		return "%s%s%s.bar" % ["east" if conf == 1 else "west", ["qua", "sem", "fin"][round - 1], s]
	return ""

## the conference of a play-off game for the announcer (unk_c5581: 12 east, 3 west): 1 east, 2 west,
## 3 the teams of the two conferences (the Stanley Cup final)
static func playoff_conference(home: int, away: int) -> int:
	var a := Exe.i32(0xc5581 + home * 4)
	var b := Exe.i32(0xc5581 + away * 4)
	if a != b:
		return 3
	return (a | b) % 2 + 1

## the round of a play-off game by its league game number: 1 from 0x444, 2 from 0x47c, 3 from 0x498
static func playoff_game_round(game_number: int) -> int:
	if game_number >= 0x498:
		return 3
	return 2 if game_number >= 0x47c else 1

## say_playoff_game_intro (0x84c41): "tonight at <arena>, an EA Sports game <n> of the <round>
## between <away> and <home>"
static func playoff_game_intro(home: String, away: String, game: int, conf: int, round: int) -> PackedStringArray:
	return PackedStringArray(["tonight.bar", home + ".rnk", "easports.bar", "gamenum%d.bar" % game, "of.bar",
		playoff_round(conf, round, true), "between.bar", away + ".awa", "and.bar", home + ".hom"])

## say_series_result (0x8491c): "(in overtime) <team> have won (game <n> of) the <round>"; the
## game number is left out when the cup was won (byte_ccca0)
static func series_result(team: String, game: int, conf: int, round: int, overtime: bool, cup_won: bool) -> PackedStringArray:
	var out := PackedStringArray()
	if overtime:
		out.append("overtime.bar")
	out.append_array([team + ".awa", "havewon.bar"])
	if not cup_won:
		out.append_array(["gamenum.bar", "gamenum%d.bar" % game, "of.bar"])
	out.append(playoff_round(conf, round, false))
	return out

## say_period_score_bar (0x84a7e): the score after a period: the game's ("thegame.bar"), after the
## 1st to 3rd period, after the 1st to 3rd overtime of a play-off game or after an overtime
## ("scortotp.bar"); "" for none
static func period_score(period: int, overtime: bool, game: bool) -> String:
	if game:
		return "thegame.bar"
	if overtime:
		return "scor%dotp.bar" % period if period >= 1 and period <= 3 else "scortotp.bar"
	return "scor%dper.bar" % period if period >= 1 and period <= 3 else ""

## say_highlight_intro (0x847da): "let's take you now to the highlight of the game between <away>
## and <home>" (the arena of the home team)
static func highlight_intro(home: String, away: String) -> PackedStringArray:
	return PackedStringArray(["takeynow.bar", home + ".rnk", "highlite.bar", "of.bar", "gamebtwn.bar",
		away + ".awa", "and.bar", home + ".hom"])

## a sentence for the audio layer (the wrappers' speech_stop_channels: it replaces the one being
## said); nothing is said with the speech option off (option byte 2 bit 0) or without sound
static func say(sim: Sim, clips: PackedStringArray) -> void:
	if not InfoPanel.speech_on(sim):
		return
	if sim.stubbed("say", [Array(clips)]):
		return
	sim.announcer_queue.append(clips)

## team_abbrev of the team's id (team_ids: the clip names)
static func abbrev(sim: Sim, t: int) -> String:
	var id: int = sim.team_ids[t] if t >= 0 and t < 2 else t
	return Tables.team_abbrev[clampi(id, 0, Tables.team_abbrev.size() - 1)]

## the jersey number of roster player r of team t (byte 5 of the player's record)
static func number(sim: Sim, t: int, r: int) -> int:
	var team := sim.teams[t]
	if r >= 0 and r < team.numbers.size():
		return team.numbers[r]
	return 0
