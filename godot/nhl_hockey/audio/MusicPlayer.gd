class_name MusicPlayer
extends Node
## The FM sound of the port: the OPL2 model (Opl2), the music driver (FmDriver) and the sequencer
## (KmsPlayer) run together and stream through an AudioStreamGenerator. The 100 Hz timer of the
## original is kept in samples: every RATE / 100 samples the driver updates its voices and the
## sequencer advances the songs and the effect notes. Plays the organ songs (play_song) and the
## sound effects whose patch is an FM instrument (0xab puck drop, 0x94, 0x96, the drum kit).

const RATE := 22050.0
const TICK := RATE / 100.0

var chip: Opl2
var driver: FmDriver
var seq: KmsPlayer
var bank: FmBank
var dac: DacDriver = null
var song_handle := 0              # crowd_loop_channel
var song_name := ""
var songs: Dictionary = {}
var music_enabled := true         # option_flags 0x40 (music_enable / music_disable)
var until_tick := 0.0
var player: AudioStreamPlayer
var playback: AudioStreamGeneratorPlayback
var mix := PackedFloat32Array()
var read_file: Callable           # name -> PackedByteArray
var dc_in := 0.0                  # the output's coupling capacitor: a DC blocking high pass
var dc_out := 0.0

func setup(b: FmBank, file_reader: Callable, digital: Dictionary = {}) -> void:
	bank = b
	read_file = file_reader
	chip = Opl2.new(RATE)
	driver = FmDriver.new(chip, bank)
	seq = KmsPlayer.new(driver)
	if not digital.is_empty():
		dac = DacDriver.new(bank, digital, RATE)
		seq.dac = dac
	if DisplayServer.get_name() == "headless":
		return
	var gen := AudioStreamGenerator.new()
	gen.mix_rate = RATE
	gen.buffer_length = 0.2
	player = AudioStreamPlayer.new()
	player.stream = gen
	add_child(player)
	player.play()
	playback = player.get_stream_playback()

## music_load_kms: NAME.KMS and NAME.CFG (cached)
func load_song(name: String) -> Kms:
	var key := name.to_lower()
	if songs.has(key):
		return songs[key]
	var k: Kms = null
	if read_file.is_valid():
		var d: PackedByteArray = read_file.call(key + ".kms")
		if not d.is_empty():
			k = Kms.parse(d, read_file.call(key + ".cfg"), name.to_upper())
	songs[key] = k
	return k

## play_sample_by_ptr: stops the running song and starts another
func play_song(name: String) -> bool:
	stop_song()
	if not music_enabled or name == "":
		return false
	var k := load_song(name)
	if k == null:
		return false
	song_handle = seq.play(k)
	song_name = name
	return song_handle != 0

## stop_crowd_loop
func stop_song() -> void:
	if song_handle != 0:
		if seq.playing(song_handle):
			seq.stop(song_handle)
		song_handle = 0
		song_name = ""

func song_playing() -> bool:
	return song_handle != 0 and seq.playing(song_handle)

func set_music_enabled(on: bool) -> void:
	music_enabled = on
	seq.music_enabled = on
	if not on:
		stop_song()

## the effect's patch is an FM instrument
func has_effect(id: int) -> bool:
	if bank == null:
		return false
	var r := bank.record(id)
	return not r.is_empty() and r[0] == 0 and not bank.timbre(r[1]).is_empty()

func play_effect(id: int) -> void:
	if has_effect(id):
		seq.play_effect(id)

func stop_all() -> void:
	stop_song()
	seq.stop_all()
	driver.all_off()
	if dac != null:
		dac.all_off()

## n mono samples of the FM sound, the timers included
func render(n: int) -> PackedFloat32Array:
	var out := PackedFloat32Array()
	out.resize(n)
	var done := 0
	while done < n:
		if until_tick <= 0.0:
			driver.tick()
			seq.tick()
			until_tick += TICK
		var len := mini(n - done, int(ceil(until_tick)))
		chip.render(out, done, len)
		if dac != null:
			dac.render(out, done, len)
		until_tick -= len
		done += len
	# the half and absolute sine waveforms leave a DC offset that the card's output stage removes
	var x1 := dc_in
	var y1 := dc_out
	for i in n:
		var x := out[i]
		y1 = x - x1 + 0.995 * y1
		x1 = x
		out[i] = y1
	dc_in = x1
	dc_out = y1
	return out

func _process(delta: float) -> void:
	if playback == null:
		# no audio output (headless): the timers still run
		_advance(int(delta * RATE))
		return
	var n := mini(playback.get_frames_available(), int(RATE * 0.1))
	if n <= 0:
		return
	if driver.active_voices() == 0 and chip.active_channels() == 0 and seq.tracks.is_empty() and (dac == null or dac.active() == 0):
		# nothing sounds: keep the timers going without the chip
		var silence := PackedVector2Array()
		silence.resize(n)
		playback.push_buffer(silence)
		_advance(n)
		return
	var s := render(n)
	var frames := PackedVector2Array()
	frames.resize(n)
	for i in n:
		var v := clampf(s[i], -1.0, 1.0)
		frames[i] = Vector2(v, v)
	playback.push_buffer(frames)

## the 100 Hz timers for n samples without the chip
func _advance(n: int) -> void:
	var t := n
	while t > 0:
		if until_tick <= 0.0:
			driver.tick()
			seq.tick()
			until_tick += TICK
		var step := mini(t, int(ceil(until_tick)))
		until_tick -= step
		t -= step
