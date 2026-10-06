class_name Crowd
## The animated figures around the ice and on the benches (start_crowd_sound 0x614c2,
## play_crowd_chant 0x61576, the record part of update_effects 0x615a2, drawn by
## draw_nets_and_effects 0x61862). Twenty records (unk_dee94, 12 bytes each): 0..16 random fans and
## photographers of the 0x85 spots, 17 the same (or one of the two figures 0x85 / 0x86 that come
## out during a stoppage), 18 / 19 the home and away bench (0x89.. / 0x9a.. at random, 0x87 / 0x88
## when they cheer a goal, a big hit, the win or the cup). A record plays the frame sequence of its
## spot (Tables.crowd_sequences: n, then n frames of F000_149.PPV, a frame every 12 steps); when
## n is negative the last frames go on at random. Then the spot is free again and the record
## waits a while, the shorter the louder the crowd.

const RECORDS := 20
const FIGURES := 0x85
const HOME_BENCH := 0x12
const AWAY_BENCH := 0x13

## one record of unk_dee94
class Record:
	var id := -1         # +0 the spot (Tables.crowd_spots), -1 idle
	var timer := 0       # +2 steps to the next frame (or to the next figure)
	var counter := 0     # +3 frames shown
	var frame := 0       # +4 frame of F000_149.PPV
	var x := 0           # +5 position on the rink surface
	var y := 0           # +7
	var seq := 0         # +9 offset of the sequence
	var count := 0       # +0xb frames in the sequence (< 0: repeating)

## reset_game_state: everybody idle, the first figures come within 60..99 steps
static func reset(sim: Sim) -> void:
	sim.crowd = []
	for i in RECORDS:
		var r := Record.new()
		r.timer = 60 + sim.random(0x28)
		sim.crowd.append(r)
	sim.crowd_busy = PackedByteArray()
	sim.crowd_busy.resize(0xab)

## start_crowd_sound (0x614c2): record `index` shows the figure of spot `id`
static func start(sim: Sim, index: int, id: int) -> void:
	var r: Record = sim.crowd[index]
	var spot: Array = Tables.crowd_spots[id]
	r.id = id
	sim.crowd_busy[id] = 1
	r.x = spot[0]
	r.y = spot[1]
	r.seq = spot[2]
	r.count = Tables.crowd_sequences[r.seq]
	r.frame = Tables.crowd_sequences[r.seq + 1]
	r.timer = 0xc
	r.counter = 1

## play_crowd_chant (0x61576): the bench of team t cheers
static func bench_cheer(sim: Sim, t: int) -> void:
	if t == 0:
		start(sim, HOME_BENCH, 0x87)
	else:
		start(sim, AWAY_BENCH, 0x88)

## the record part of update_effects, every step
static func update(sim: Sim) -> void:
	for i in RECORDS:
		var r: Record = sim.crowd[i]
		r.timer -= 1
		if r.timer >= 0:
			continue
		if r.id < 0:
			var id := 0
			if i == HOME_BENCH:
				id = sim.random(0x11) + 0x89
			elif i == AWAY_BENCH:
				id = sim.random(0x11) + 0x9a
			else:
				var picked := false
				if i == 0x11 and sim.play_stopped:
					var k := sim.random(4)
					if k < 2:
						id = k + 0x85
						picked = true
				if not picked:
					id = sim.random(FIGURES)
					while sim.crowd_busy[id] != 0:
						id += 1
						if id > FIGURES - 1:
							id = 0
			start(sim, i, id)
			continue
		if r.counter < absi(r.count):
			r.timer = 0xc
			r.counter += 1
			r.frame = Tables.crowd_sequences[r.seq + r.counter]
			continue
		if r.count < 0 and sim.random(2) != 0:
			# a repeating figure goes on
			r.frame = Tables.crowd_sequences[r.seq + 1]
			r.timer = 0xc
			r.counter = 1
			continue
		sim.crowd_busy[r.id] = 0
		r.id = -1
		var wait := (1000 - sim.crowd_noise) / 8
		if wait < 0x14:
			wait = 0x14
		if i > 0x11 and wait < 100:
			wait = 100
		if i == 0x11 and sim.play_stopped:
			r.timer = 0x78
		else:
			r.timer = sim.random(wait)

## the effect bytes of a replay frame: the frame counters (two per byte, the odd record in the
## low nibble) and the spot ids (0xff idle)
static func record_bytes(sim: Sim) -> PackedByteArray:
	var out := PackedByteArray()
	out.resize(30)
	for i in 10:
		var a: Record = sim.crowd[i * 2]
		var b: Record = sim.crowd[i * 2 + 1]
		out[i] = ((a.counter & 0xf) << 4) | (b.counter & 0xf)
	for i in 20:
		var r: Record = sim.crowd[i]
		out[10 + i] = r.id & 0xff
	return out

## the frame of a record from its spot and counter (replay_draw_frame)
static func frame_of(id: int, counter: int) -> int:
	if id < 0 or id >= Tables.crowd_spots.size():
		return -1
	var seq: int = Tables.crowd_spots[id][2]
	return Tables.crowd_sequences[clampi(seq + counter, 0, Tables.crowd_sequences.size() - 1)]
