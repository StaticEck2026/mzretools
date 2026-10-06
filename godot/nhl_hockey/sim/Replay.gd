class_name Replay
## The instant replay: replay_record_frame (0x675d6) packs the scene into a 0x80 byte frame every
## second simulation step and writes it into a 0x9600 byte ring (300 frames); while the play is
## stopped after the whistle it keeps overwriting the newest frame. replay_seek_frames (0x67900)
## moves the read position (bounded by the oldest and the newest frame), plays the recorded sound
## effects when running forward at normal speed and unpacks the frame for replay_draw_frame.
## instant_replay (0x7e0fa) / replay_control_loop (0x7e9ac) are the VCR: rewind (4x back), step
## back, pause, step forward, play, fast forward (4x), camera reset, menu, exit; a click on the
## rink makes the camera follow the nearest sprite or look at that spot.
##
## Frame layout (offsets in bytes):
##   0x00  17 dwords, entities 0..16: x & 0x3ff | (y & 0x3ff) << 10 | (frame & 0x7ff) << 20 |
##         mirror (+0x55 bit 3) << 31; frame 0x7ff = none
##   0x44  12 jersey numbers
##   0x50  6 bytes: line slots of the player pairs (low nibble even, high nibble odd, 0xf = off)
##   0x56  puck z, shadow z (signed bytes)
##   0x58  2 sound effect ids (the previous and this step, 0xff = none)
##   0x5a  user2_slot << 4 | user1_slot, puck carrier, byte_e9abb << 4 | penalized_count
##   0x5d  camera x (signed byte), camera y (word), crowd level (word)
##   0x62  10 bytes: effect frame nibbles, 0x6c 20 bytes: effect ids (0xff = none)

const FRAME := 0x80
const SIZE := 0x9600
const FRAMES := SIZE / FRAME

# VCR modes (dword_ed754, low 6 bits) and the camera flag
const MODE_REWIND := 1
const MODE_STEP_BACK := 6
const MODE_PAUSE := 4
const MODE_STEP := 0xc
const MODE_PLAY := 0x10
const MODE_FAST := 0x20
const MODE_RECORDED_CAMERA := 0x40

# buttons of the panel (unk_d1dc8: x0, y0, x1, y1 on the 320x200 screen, left / right neighbours)
const BUTTONS := [
	[159, 172, 170, 180, 8, 1],   # rewind
	[179, 172, 190, 180, 0, 2],   # step back
	[198, 172, 209, 180, 1, 3],   # pause
	[217, 172, 228, 180, 2, 4],   # step forward
	[236, 172, 247, 180, 3, 5],   # play
	[255, 172, 266, 180, 4, 6],   # fast forward
	[159, 185, 190, 193, 5, 7],   # camera
	[198, 185, 229, 193, 6, 8],   # menu (save a highlight)
	[236, 185, 267, 193, 7, 0],   # exit
]
const B_REWIND := 0
const B_STEP_BACK := 1
const B_PAUSE := 2
const B_STEP := 3
const B_PLAY := 4
const B_FAST := 5
const B_CAMERA := 6
const B_MENU := 7
const B_EXIT := 8

var buf := PackedByteArray()
var write := 0               # replay_write_ptr (offset)
var wrapped := false         # action_flags 0x10: the ring is full
var half := 0                # word_cd4fe: frames are recorded every second step
var held_sfx := -1           # word_cd500: the sound of the skipped step

# playback (instant_replay)
var read := 0                # dword_e03a4
var mode := MODE_PAUSE
var speed_acc := 0           # word_ed758
var step_acc := 0            # dword_ed6e8
var follow := -1             # dword_cd4fa >> 16: the followed sprite, -1 recorded camera
var free_camera := false     # dword_ed70c
var free_x := 0
var free_y := 0
var frame: ReplayFrame = null

func _init() -> void:
	buf.resize(SIZE)

func reset() -> void:
	write = 0
	wrapped = false
	half = 0
	held_sfx = -1

## replay_buffer_start (0x675a0): the newest frame (where a stopped play keeps recording)
func buffer_start() -> int:
	if write != 0:
		return write - FRAME
	if wrapped:
		return SIZE - FRAME
	return 0

## number of frames that can be played
func frame_count() -> int:
	return FRAMES if wrapped else write / FRAME

## replay_record_frame (0x675d6), called at the end of every sim_tick
func record(sim: Sim) -> void:
	if sim.replay_disabled:
		return
	if half < 1:
		held_sfx = -1 if sim.whistle_ready else sim.last_sfx
		sim.last_sfx = -1
		half += 1
		return
	half -= 1
	if sim.whistle_ready:
		write = buffer_start()
	var p := write
	for i in 17:
		var e: Entity = sim.entities[i]
		var f := e.frame & 0x7ff
		var v := (e.xi & 0x3ff) | ((e.yi & 0x3ff) << 10) | (f << 20)
		if e.flags4 & Entity.F4_MIRROR:
			v |= 1 << 31
		buf.encode_u32(p, v & 0xffffffff)
		p += 4
	for i in 12:
		buf[p] = sim.entities[i].number & 0xff
		p += 1
	for k in 6:
		var a: int = sim.entities[k * 2].line_slot
		var b: int = sim.entities[k * 2 + 1].line_slot
		var v := 0xf if a < 0 else a & 0xf
		v |= 0xf0 if b < 0 else (b & 0xf) << 4
		buf[p] = v
		p += 1
	buf[p] = sim.puck.zi & 0xff
	buf[p + 1] = sim.shadow.zi & 0xff
	buf[p + 2] = held_sfx & 0xff
	buf[p + 3] = sim.last_sfx & 0xff
	sim.last_sfx = -1
	held_sfx = -1
	buf[p + 4] = ((sim.user2_slot & 0xf) << 4) | (sim.user1_slot & 0xf)
	buf[p + 5] = sim.puck_carrier & 0xff
	buf[p + 6] = ((sim.box_count[1] & 0xf) << 4) | (sim.box_count[0] & 0xf)
	buf[p + 7] = sim.camera_x & 0xff
	buf.encode_s16(p + 8, sim.camera_y)
	buf.encode_s16(p + 10, clampi(sim.crowd_noise, -0x8000, 0x7fff))
	p += 12
	var fx := sim.effect_record_bytes()
	for i in 30:
		buf[p + i] = fx[i]
	write += FRAME
	if write >= SIZE:
		wrapped = true
		write = 0

# --------------------------------------------------------------------------------------------
# playback
# --------------------------------------------------------------------------------------------

## instant_replay: start at the oldest frame (sub_67581), paused
func begin_playback() -> void:
	read = write if wrapped else 0
	mode = MODE_PAUSE
	speed_acc = 0
	step_acc = 0
	follow = -1
	free_camera = false
	frame = null
	seek(0, false, null)

## replay_seek_frames (0x67900): moves by n frames; returns n, or -1 at either end. With sound
## the effects of the frames passed while going forward are played (sim.play_sfx).
func seek(n: int, with_sound: bool, sim: Sim) -> int:
	if frame_count() == 0:
		frame = ReplayFrame.new()
		return -1
	var start := read
	var result := n
	if n < 0:
		while n < 0:
			if read == 0:
				if not wrapped:
					result = -1
					break
				read = SIZE
			if read == write:
				result = -1
				break
			read -= FRAME
			n += 1
	else:
		while n > 0:
			n -= 1
			var nxt := read + FRAME
			if nxt == SIZE:
				if not wrapped:
					result = -1
					break
				nxt = 0
			read = nxt
			if read == write:
				result = -1
				read -= FRAME
				if read < 0:
					read += SIZE
				break
			if with_sound and sim != null and start != read:
				for k in 2:
					var id := buf[read + 0x58 + k]
					if id != 0xff:
						sim.play_sfx(id)
	frame = decode(read)
	return result

## unpacks the frame at offset p
func decode(p: int) -> ReplayFrame:
	var f := ReplayFrame.new()
	for i in 17:
		var v := buf.decode_u32(p + i * 4)
		var e := ReplayFrame.Sprite.new()
		e.slot = i
		e.xi = _s10(v & 0x3ff)
		e.yi = _s10((v >> 10) & 0x3ff)
		var fr := (v >> 20) & 0x7ff
		e.frame = -1 if fr == 0x7ff else fr
		e.flags4 = Entity.F4_MIRROR if (v >> 31) & 1 else 0
		f.entities.append(e)
	for i in 12:
		f.entities[i].number = buf[p + 0x44 + i]
	for k in 6:
		var b := buf[p + 0x50 + k]
		var lo := b & 0xf
		var hi := (b >> 4) & 0xf
		f.entities[k * 2].line_slot = -1 if lo == 0xf else lo
		f.entities[k * 2 + 1].line_slot = -1 if hi == 0xf else hi
	f.entities[Entity.Slot.REFEREE].line_slot = 0
	f.entities[Entity.Slot.PUCK].zi = Entity.to_s8(buf[p + 0x56])
	f.entities[Entity.Slot.SHADOW].zi = Entity.to_s8(buf[p + 0x57])
	var users := buf[p + 0x5a]
	f.user1_slot = -1 if (users & 0xf) == 0xf else users & 0xf
	f.user2_slot = -1 if (users >> 4) == 0xf else users >> 4
	f.puck_carrier = Entity.to_s8(buf[p + 0x5b])
	f.box_count = [buf[p + 0x5c] & 0xf, buf[p + 0x5c] >> 4]
	f.camera_x = Entity.to_s8(buf[p + 0x5d])
	f.camera_y = buf.decode_s16(p + 0x5e)
	f.crowd = buf.decode_s16(p + 0x60)
	for i in 10:
		var b := buf[p + 0x62 + i]
		f.effect_frames.append(b >> 4)
		f.effect_frames.append(b & 0xf)
	for i in 20:
		var id := buf[p + 0x6c + i]
		f.effect_ids.append(-1 if id == 0xff else id)
	return f

static func _s10(v: int) -> int:
	return v - 0x400 if v & 0x200 else v

## sub_7e93e: the sprite under a rink position (players, puck, referee), -1 for none
func sprite_at(x: int, y: int) -> int:
	if frame == null:
		return -1
	var best := -1
	var best_d := 0x7fffffff
	for e: ReplayFrame.Sprite in frame.entities:
		if e.frame < 0 or e.slot == Entity.Slot.SHADOW or e.slot == Entity.Slot.NET_TOP or e.slot == Entity.Slot.NET_BOTTOM:
			continue
		var dx := e.xi - x
		var dy := e.yi + 0xc - y
		if absi(dx) > 0xc or absi(dy) > 0x14:
			continue
		var d := dx * dx + dy * dy
		if d < best_d:
			best_d = d
			best = e.slot
	return best

## replay_control_loop: a button press (or held button) with the elapsed ticks; returns the number
## of frames to move, or null to leave the replay
func press(button: int, ticks: int) -> Variant:
	match button:
		B_REWIND:
			mode = (mode & 0x54) | MODE_REWIND
			return -ticks * 4
		B_STEP_BACK:
			var n := 0
			if (mode & 2) == 0:
				step_acc = 0
				n = -1
				speed_acc = -0xe
			else:
				step_acc += ticks
				if step_acc >= 5:
					n = -1
					step_acc -= 5
			mode = (mode & MODE_RECORDED_CAMERA) | MODE_STEP_BACK
			return n
		B_PAUSE:
			mode = (mode & MODE_RECORDED_CAMERA) | MODE_PAUSE
			return 0
		B_STEP:
			var n := 0
			if (mode & 8) == 0:
				step_acc = 0
				n = 1
				speed_acc = 0xe
			else:
				step_acc += ticks
				if step_acc >= 5:
					n = 1
					step_acc -= 5
			mode = (mode & MODE_RECORDED_CAMERA) | MODE_STEP
			return n
		B_PLAY:
			if (mode & 0x3f) != MODE_PLAY:
				speed_acc = 0
			mode = (mode & MODE_RECORDED_CAMERA) | MODE_PLAY
			return ticks
		B_FAST:
			mode = (mode & 0x54) | MODE_FAST
			return ticks * 4
		B_CAMERA:
			mode |= MODE_RECORDED_CAMERA
			free_camera = false
			follow = -1
			return 0
		B_EXIT:
			return null
	# no button: the running mode continues (play, rewind, fast forward)
	match mode & 0x3f:
		MODE_PLAY:
			return ticks
		MODE_REWIND:
			return -ticks * 4
		MODE_FAST:
			return ticks * 4
	mode &= 0x54
	return 0

## the frames to move for a speed value (instant_replay: 6 / 20 per tick)
func advance(speed: int) -> int:
	speed_acc += speed * 6
	var n := speed_acc / 20
	speed_acc -= n * 20
	return n

## a click on the rink: follow the sprite there or look at the spot (free camera)
func click(x: int, y: int) -> void:
	var s := sprite_at(x, y)
	mode &= 0x14
	if s == -1:
		free_camera = true
		follow = -1
		free_x = clampi(x, -0x20, 0x20)
		free_y = clampi(y, -0xbc, 0xec)
	else:
		free_camera = false
		follow = s

## the camera for the current frame (instant_replay): the free spot, the followed sprite or the
## recorded camera
func camera() -> Vector2i:
	if frame == null:
		return Vector2i.ZERO
	if free_camera:
		return Vector2i(free_x, free_y)
	if follow >= 0:
		var e: ReplayFrame.Sprite = frame.entities[follow]
		return Vector2i(clampi(e.xi, -0x20, 0x20), clampi(e.yi, -0xbc, 0xec))
	return Vector2i(frame.camera_x, frame.camera_y)
