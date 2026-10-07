class_name Announcer
extends Node
## Plays the announcer's sentences of the simulation (Sim.announcer_queue, built by Speech.gd)
## from XBRUCE2.VIV like the timer routine speech_timer: the clips follow each other, the next one
## starts 0x1a ticks (100 Hz) before the current one ends, and after the last one the announcer
## stays busy another 0x1a ticks. A new sentence interrupts the running one (speech_reset). While
## busy, Sim.speech_busy holds the stoppage (penalty_box_update) and the cup presentation.
## The clips play on the digital driver's mixer, voices 0 and 1 in turn at 11025 Hz and full
## volume (playsample_raw / playsample_raw_loop), where the effects also take their voices.

const TRIM_TICKS := 0x1a

var sim: Sim
var viv: Viv
var player: AudioStreamPlayer
var clips: PackedStringArray
var index := 0
var wait := 0.0          # seconds until the next clip
var cooldown := 0.0
var playing := false
var enabled := true
var music: MusicPlayer = null      # the sound card (its digital driver plays the clips)
var voice := 0                     # dword_d27b2

func setup(s: Sim, bank: Viv) -> void:
	sim = s
	viv = bank
	player = AudioStreamPlayer.new()
	add_child(player)

func _process(delta: float) -> void:
	if sim == null:
		return
	if not sim.announcer_queue.is_empty():
		var sentence: PackedStringArray = sim.announcer_queue[sim.announcer_queue.size() - 1]
		sim.announcer_queue.clear()
		if viv != null and enabled:
			_start(sentence)
	if playing:
		wait -= delta
		while playing and wait <= 0.0:
			_next()
	elif cooldown > 0.0:
		cooldown -= delta
	sim.speech_busy = playing or cooldown > 0.0

func _start(sentence: PackedStringArray) -> void:
	clips = sentence
	index = 0
	playing = true
	wait = 0.0
	cooldown = 0.0

func _next() -> void:
	while index < clips.size() and not viv.has(clips[index]):
		index += 1          # a clip the bank does not have (a number above 99) is left out
	if index >= clips.size():
		playing = false
		cooldown = TRIM_TICKS / 100.0
		return
	var name := clips[index]
	index += 1
	if music != null and music.digital():
		var smp := viv.samples(name)
		voice = (voice + 1) & 1
		music.play_sample(voice, smp[0], smp[1], 0x7f)
	else:
		player.stream = viv.stream(name)
		player.play()
	wait += maxi(viv.ticks(name) - TRIM_TICKS, 1) / 100.0

func stop() -> void:
	player.stop()
	playing = false
	cooldown = 0.0
	sim.announcer_queue.clear()
	sim.speech_busy = false
