extends SceneTree
## Statistics of a 12000 step CPU vs CPU game (shots, stoppages, AI state histogram) for tuning
## the port: godot --headless --path godot/nhl_hockey --script tests/stats.gd
func _initialize() -> void:
	var sim := Sim.new()
	sim.user1_team = 0      # nobody controls a player: CPU vs CPU
	sim.user1_slot = -1
	var states := {}
	var shots := 0
	var was_shot := false
	var stoppages := {}
	var was_stopped := true
	var carriers := [0, 0, 0]
	var maxv := 0
	for i in 12000:
		sim.step(8, 8, 0, 0)
		if sim.shot_in_flight and not was_shot:
			shots += 1
		was_shot = sim.shot_in_flight
		if sim.play_stopped and not was_stopped:
			var key := str(sim.infractions)
			stoppages[key] = stoppages.get(key, 0) + 1
		was_stopped = sim.play_stopped
		if sim.puck_carrier >= 0 and sim.puck_carrier < 12:
			carriers[sim.puck_carrier / 6] += 1
		elif sim.puck_carrier == 16:
			carriers[2] += 1
		for j in 12:
			var e := sim.entities[j]
			var k := "%d:%s" % [j, Tables.ai_state_names[e.state() + 1]]
			states[k] = states.get(k, 0) + 1
			maxv = maxi(maxv, absi(e.vx))
		if i % 2000 == 1999:
			var e := sim.entities[7]
			print("step %d puck %d,%d z %d v %d,%d carrier %d stopped %s clock %d:%02d score %d-%d  p7 %d,%d state %s target %d,%d want %d" % [i + 1, sim.puck.xi, sim.puck.yi, sim.puck.zi, sim.puck.vx, sim.puck.vy, sim.puck_carrier, sim.play_stopped, sim.clock_seconds / 60, sim.clock_seconds % 60, sim.teams[0].goals, sim.teams[1].goals, e.xi, e.yi, Tables.ai_state_names[e.state() + 1], e.target_x, e.target_y, e.want_dir])
	print("shots ", shots, " carriers home/away/ref ", carriers, " maxv ", maxv, " penalties home ", sim.teams[0].penalties, " away ", sim.teams[1].penalties)
	print("final: stopped %s period %d clock %d puck state %s ref state %s phase %d countdown %s timer %d inf %s game_over %s faceoff %d,%d" % [sim.play_stopped, sim.period, sim.clock_seconds, Tables.ai_state_names[sim.puck.state() + 1], Tables.ai_state_names[sim.referee.state() + 1], sim.ref_phase, sim.stoppage_countdown, sim.stoppage_timer, str(sim.infractions), sim.game_over, sim.faceoff_x, sim.faceoff_y])
	print("ref %d,%d target %d,%d busy %d anim %x puck %d,%d z %d carrier %d" % [sim.referee.xi, sim.referee.yi, sim.referee.target_x, sim.referee.target_y, sim.referee.flags & 0x20, sim.referee.anim, sim.puck.xi, sim.puck.yi, sim.puck.zi, sim.puck_carrier])
	print("stoppages ", stoppages)
	var keys := states.keys()
	keys.sort()
	for k in keys:
		if states[k] > 300:
			print("  ", k, " ", states[k])
	quit(0)
