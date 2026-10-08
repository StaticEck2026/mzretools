extends Node
## The program: the front end (frontend/FrontEnd.gd) on the 640x480 screen and the match
## (view/Main.tscn) on the 320x200 one, like main / play_game / game_loop of HOCKEY.EXE switch the
## video mode (set_video_mode). The front end asks for a match with play_match_async; the match
## comes back here for the pause screen, the intermissions and its end, which the front end draws.
##
## NHL_HOME / NHL_AWAY / NHL_SCREENSHOT (see view/Main.gd) start a match directly without the front
## end, like the port did before the front end existed.

const MATCH_SCENE := preload("res://view/Main.tscn")

var front: FrontEnd
var match_node: Node = null
var _match_done := false
var _match_result := 0

func _ready() -> void:
	var direct := OS.has_environment("NHL_HOME") or OS.has_environment("NHL_AWAY") or OS.has_environment("NHL_SCREENSHOT")
	if direct and not OS.has_environment("NHL_FRONTEND"):
		match_node = MATCH_SCENE.instantiate()
		add_child(match_node)
		return
	front = FrontEnd.new()
	front.app = self
	add_child(front)
	front.run()
	if OS.has_environment("NHL_UI_SCRIPT"):
		_run_script(OS.get_environment("NHL_UI_SCRIPT"))

## NHL_UI_SCRIPT: scripted input for screenshots of the front end, commands separated by ";":
## wait:FRAMES, click:X,Y (a click of the mouse at X,Y of the 640x480 screen), key:enter|esc,
## press:ACTION (an input action of the match, e.g. pause), shot:PATH (the window as PNG),
## simgame:PERIODS[,SECONDS] (the session's teams play that many periods without a view; the
## front end's screens then see it as the game on the ice), call:CALLBACK (a menu callback run
## like run_menu does, without waiting for it), scores:PERIOD (the scores around the league),
## type:TEXT (keys and Enter for a text entry), quit
func _run_script(script: String) -> void:
	for cmd in script.split(";", false):
		var parts := cmd.strip_edges().split(":", true, 1)
		var arg := parts[1] if parts.size() > 1 else ""
		match parts[0]:
			"wait":
				for i in int(arg):
					await get_tree().process_frame
			"click":
				var xy := arg.split(",")
				var ui := front.ui
				ui.set_pointer(int(xy[0]), int(xy[1]))
				ui.push(1, 1)
				await get_tree().process_frame
				ui.push(1, 2)
				await get_tree().process_frame
			"key":
				var ui := front.ui
				if arg == "esc":
					ui.push(3, 4)
				else:
					ui.push(3, 1)
					ui.push(3, 2)
				await get_tree().process_frame
			"press":
				Input.action_press(arg)
				await get_tree().physics_frame
				await get_tree().physics_frame
				Input.action_release(arg)
			"shot":
				await RenderingServer.frame_post_draw
				var img := get_viewport().get_texture().get_image()
				print("screenshot %s: %s" % [arg, error_string(img.save_png(arg))])
			"simgame":
				var pa := arg.split(",")
				front.game = _sim_game(int(pa[0]), int(pa[1]) if pa.size() > 1 else 30)
			"call":
				_call_held(arg)
				await get_tree().process_frame
			"type":
				# text for a text entry dialog, then Enter
				for ch in arg:
					front.ui.push(3, 0x20, ch.unicode_at(0))
				front.ui.push(3, 2)
				await get_tree().process_frame
			"scores":
				# the scores around the league after period ARG (end_match_from_period)
				LeagueScores.init(Session.home_team, Session.away_team)
				for p in range(1, int(arg) + 1):
					LeagueScores.advance(p, Session.home_team)
				front.games.boxscore_screen(0x20, int(arg), 0)
				await get_tree().process_frame
			"quit":
				get_tree().quit()

## a callback of call: with the menu loops held, so its own screens get the input
func _call_held(cb: String) -> void:
	front.ui.menu_hold += 1
	await front.dispatch(cb)
	front.ui.menu_hold -= 1

func _sim_game(periods: int, seconds: int) -> Node:
	var holder: Node = load("res://view/SimHolder.gd").new()
	add_child(holder)
	var sim := Sim.new()
	holder.sim = sim
	sim.user1_team = 0
	sim.user2_team = 0
	sim.set_period_length(seconds)
	sim.set_teams(front.db.load_team(Session.home_team), front.db.load_team(Session.away_team))
	sim.assign_users()
	var steps := 0
	while steps < 200000 and not sim.finished and sim.period < periods:
		sim.step(8, 8, 0, 0)
		steps += 1
		if sim.intermission_pending:
			sim.intermission_pending = false
	print("simgame: %d steps, period %d, %d:%d, %d summary records" % [steps, sim.period, sim.teams[0].goals,
		sim.teams[1].goals, sim.gs_records.size()])
	return holder

func quit() -> void:
	get_tree().quit()

func _screen_match() -> void:
	get_window().content_scale_size = Vector2i(320, 200)

## play_game: a match with the front end's settings; waits until it is over (or left from the
## pause screen) and returns dword_c53f7 (1 finished, 2 left)
func play_match_async(setup: Dictionary) -> int:
	_match_done = false
	_match_result = 0
	front.show_screen(false)
	_screen_match()
	match_node = MATCH_SCENE.instantiate()
	match_node.config = setup
	match_node.front = front
	match_node.app = self
	add_child(match_node)
	while not _match_done:
		await get_tree().process_frame
	match_node.queue_free()
	match_node = null
	front.show_screen(true)
	return _match_result

## the match ended (Main.gd): 1 the game was played to the end, 2 it was left from the pause screen
func match_finished(result: int) -> void:
	_match_result = result
	_match_done = true

## the 640x480 screen over the match for its pause screen and intermissions; back to the match
func front_over_match(on: bool) -> void:
	if on:
		front.show_screen(true)
	else:
		front.show_screen(false)
		_screen_match()
