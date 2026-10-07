class_name Mt32
extends RefCounted
## The Roland MT-32 on an MPU-401 (MT32.SCN; mpu_drv_send_midi 0x9ffa0 writes every byte of a message
## to the MPU's data port, nothing else). What the game sends is reproduced exactly: the MT32HOCK.KMS
## set-up (system exclusive messages that load the timbres "Dist. Gtr1", "Goal Post", "Wind", "Slap
## Shot", "Puck Ice", "PuckBoard", "GlassBreak", "Glass Hit" ... into the timbre memory and set the
## patch and rhythm memory), the MT* songs and the effects of PCFF002.PAT (driver class 3: a program
## change on channels 12..15 at note 0x24, or a note of the rhythm part on channel 9). The bytes are
## kept in `stream` (the last 4096).
##
## The sound itself is the MT-32's: LA synthesis and the PCM samples of its ROMs, which are not part
## of the game. The port renders the messages with a small stand-in instead: per program family a
## waveform (saw, square, sine) with an envelope, the rhythm part as noise and pitch-swept bursts,
## the channel volume, the velocity and the pitch bend (+-12 semitones, the patches' bender range).
## It is an approximation of what an MT-32 plays, not an emulation.

const CLASS := 3
const MAX_VOICES := 24

class Voice:
	var channel := 0
	var note := 0
	var vel := 0
	var phase := 0.0
	var freq := 0.0
	var wave := 0                    # 0 saw 1 square 2 sine 3 noise
	var env := 0.0
	var attack := 0.0                # per second
	var decay := 0.0                 # per second down to sustain
	var sustain := 0.0
	var release := 0.0
	var releasing := false
	var sweep := 0.0                 # pitch fall a second (the rhythm's toms and kick)
	var stage := 0                   # 0 attack, 1 decay to the sustain level
	var lp := 0.0

var bank: FmBank
var voices: Array = []
var programs := PackedInt32Array()
var volumes := PackedInt32Array()
var bends := PackedInt32Array()
var sustain := PackedInt32Array()
var stream := PackedByteArray()      # the bytes the MPU received
var sysex_count := 0
var out_rate := 22050.0
var level := 0.18
var rng := 0x1234

func _init(b: FmBank, rate: float) -> void:
	bank = b
	out_rate = rate
	programs.resize(16)
	volumes.resize(16)
	volumes.fill(100)
	bends.resize(16)
	sustain.resize(16)

func _log(bytes: PackedByteArray) -> void:
	stream.append_array(bytes)
	if stream.size() > 4096:
		stream = stream.slice(stream.size() - 4096)

## a message as the MPU gets it
func midi(status: int, d1: int, d2: int) -> void:
	var ch := status & 0xf
	var kind := status & 0xf0
	_log(PackedByteArray([status, d1]) if kind == 0xc0 or kind == 0xd0 else PackedByteArray([status, d1, d2]))
	match kind:
		0x80:
			note_off(ch, d1)
		0x90:
			if d2 == 0:
				note_off(ch, d1)
			else:
				note_on(ch, d1, d2)
		0xb0:
			match d1:
				7:
					volumes[ch] = d2
				0x40:
					sustain[ch] = d2
					if d2 == 0:
						for v: Voice in voices:
							if v.channel == ch and v.releasing:
								v.release = maxf(v.release, 4.0)
				0x7b:
					for v: Voice in voices:
						if v.channel == ch:
							v.releasing = true
		0xc0:
			programs[ch] = d1
		0xe0:
			bends[ch] = ((d2 << 7) | d1) - 0x2000

func sysex(data: PackedByteArray) -> void:
	_log(data)
	sysex_count += 1

func _freq(ch: int, note: int) -> float:
	return 440.0 * pow(2.0, (note - 69 + bends[ch] / 8192.0 * 12.0) / 12.0)

func note_on(ch: int, note: int, vel: int) -> void:
	if voices.size() >= MAX_VOICES:
		voices.pop_front()
	var v := Voice.new()
	v.channel = ch
	v.note = note
	v.vel = vel
	v.freq = _freq(ch, note)
	if ch == 9:
		# the rhythm part: low keys drums with a falling pitch, the others noise
		v.decay = 6.0
		v.sustain = 0.0
		v.release = 8.0
		v.attack = 2000.0
		if note < 37 or (note >= 41 and note <= 50):
			v.wave = 2
			v.freq = 60.0 + (note - 35) * 12.0
			v.sweep = 0.6
		else:
			v.wave = 3
			v.decay = 3.0 if note < 49 else 1.2
	else:
		var p := programs[ch]
		if p < 8:                    # pianos
			v.wave = 0
			v.attack = 400.0
			v.decay = 1.2
			v.sustain = 0.25
			v.release = 4.0
		elif p < 24:                 # organs and keyboards
			v.wave = 1
			v.attack = 200.0
			v.decay = 0.5
			v.sustain = 0.8
			v.release = 8.0
		elif p < 64:                 # strings, brass, winds
			v.wave = 0
			v.attack = 8.0
			v.decay = 0.4
			v.sustain = 0.7
			v.release = 3.0
		elif p < 96:                 # basses and guitars
			v.wave = 1 if p < 80 else 0
			v.attack = 300.0
			v.decay = 2.0
			v.sustain = 0.3
			v.release = 6.0
		else:                        # effects
			v.wave = 3
			v.attack = 50.0
			v.decay = 1.0
			v.sustain = 0.4
			v.release = 2.0
	voices.append(v)

func note_off(ch: int, note: int) -> void:
	if sustain[ch] != 0:
		return
	for v: Voice in voices:
		if v.channel == ch and v.note == note and not v.releasing:
			v.releasing = true
			return

func tick() -> void:
	for v: Voice in voices:
		if v.channel != 9:
			v.freq = _freq(v.channel, v.note)

func active() -> int:
	return voices.size()

func all_off() -> void:
	voices.clear()

func render(out: PackedFloat32Array, offset: int, n: int) -> void:
	if voices.is_empty():
		return
	var dt := 1.0 / out_rate
	var keep: Array = []
	for v: Voice in voices:
		var gain := level * v.vel / 127.0 * volumes[v.channel] / 127.0
		for i in n:
			if v.releasing:
				v.env -= v.release * dt
			elif v.stage == 0:
				v.env += v.attack * dt
				if v.env >= 1.0:
					v.env = 1.0
					v.stage = 1
			else:
				v.env = maxf(v.env - v.decay * dt, v.sustain)
			if v.env <= 0.0 and (v.releasing or v.stage == 1):
				v.env = 0.0
				break
			if v.sweep > 0.0:
				v.freq = maxf(v.freq * (1.0 - v.sweep * dt * 4.0), 30.0)
			v.phase += v.freq * dt
			v.phase -= floorf(v.phase)
			var s := 0.0
			match v.wave:
				0:
					s = v.phase * 2.0 - 1.0
				1:
					s = 1.0 if v.phase < 0.5 else -1.0
				2:
					s = sin(TAU * v.phase)
				_:
					rng = (rng * 1103515245 + 12345) & 0x7fffffff
					v.lp += (((rng >> 16) & 0xff) / 127.5 - 1.0 - v.lp) * 0.35
					s = v.lp
			out[offset + i] += s * v.env * gain
		if v.env > 0.0:
			keep.append(v)
	voices = keep
