class_name MusicPlayer
extends Node
## The sound card of the port, as load_sound_config (0x82d7a) sets it up: the card's .SCN file names
## its patch file and timbre files (FmBank) and the drivers that play them, the sequencer
## (KmsPlayer: the songs, the notes of the effects, the 100 Hz timer of sound_timer_tick) sends its
## messages to them, and everything streams through one AudioStreamGenerator.
##
##   card 2 Sound Blaster  SBDAC.SCN   PCFF001.PAT, PCFF000.TIM (FM) + PCFF001.TIM / .DIG (digital):
##                         the FM driver on the OPL2 (Opl2, FmDriver) and the digital driver with
##                         its 4 voice mixer (DacDriver), which also takes the effects, the crowd,
##                         the speech and the recordings
##   card 4 AdLib          ADLIB.SCN   PCFF004.PAT, PCFF000.TIM + PCFF002.TIM: everything on the OPL2,
##                         the effects too (FM timbres of type 2); no crowd, no speech
##   card 1 PC speaker     PCBEEP.SCN  PCFF003.PAT / .TIM: the effects on the speaker (PcSpeaker)
##   card 8 MT-32          MT32.SCN    PCFF002.PAT: the MIDI stream of the MPU-401 (Mt32, a stand-in
##                         synthesiser), the crowd on its channels 7 and 8
##   card 0x20 UltraSound  SBDAC.SCN with the GUS drivers: modelled as the Sound Blaster
##   card 0x10 none
##
## The 100 Hz timer of the original is kept in samples: every RATE / 100 samples the drivers update
## their voices and the sequencer advances the songs and the effect notes.

const RATE := 22050.0
const TICK := RATE / 100.0
const SCN := {1: "pcbeep", 2: "sbdac", 4: "adlib", 8: "mt32", 0x20: "sbdac"}

var card := 2
var chip: Opl2 = null
var driver: FmDriver = null
var seq: KmsPlayer
var bank: FmBank
var dac: DacDriver = null
var speaker: PcSpeaker = null
var mt32: Mt32 = null
var song_handle := 0              # crowd_loop_channel
var song_name := ""
var songs: Dictionary = {}
var music_enabled := true         # option_flags 0x40 (music_enable / music_disable)
var until_tick := 0.0
var player: AudioStreamPlayer
var playback: AudioStreamGeneratorPlayback
var read_file: Callable           # name -> PackedByteArray
var dc_in := 0.0                  # the output's coupling capacitor: a DC blocking high pass
var dc_out := 0.0
# update_ambient_audio: the crowd on channels 8 (the roar, 0x7d) and 7 (the murmur, 0x7e)
var crowd_level := 0              # dword_ccc88
var roar := 0                     # dword_ccc8c
var murmur := 0                   # dword_ccc90
var rng := RandomNumberGenerator.new()

## the Sound Blaster's FM bank and digital programs (the setup the tests and older callers use)
func setup(b: FmBank, file_reader: Callable, digital: Dictionary = {}) -> void:
	card = 2
	bank = b
	read_file = file_reader
	chip = Opl2.new(RATE)
	driver = FmDriver.new(chip, bank)
	seq = KmsPlayer.new(driver, bank)
	if not digital.is_empty():
		dac = DacDriver.new(bank, digital, RATE)
		seq.dac = dac
	_start_output()

## load_sound_config: the card's banks and drivers; false when the card's files are missing
func setup_card(c: int, file_reader: Callable) -> bool:
	card = c
	read_file = file_reader
	var scn_name: String = SCN.get(c, "")
	if scn_name == "":
		seq = KmsPlayer.new(null, null)
		_start_output()
		return true
	var scn: PackedByteArray = read_file.call(scn_name + ".scn")
	if scn.size() < 4:
		seq = KmsPlayer.new(null, null)
		_start_output()
		return false
	var tims: Array = []
	for k in scn[3]:
		if 0x14 + k < scn.size():
			tims.append(read_file.call("pcff%03d.tim" % scn[0x14 + k]))
	bank = FmBank.load_bank(read_file.call("pcff%03d.pat" % scn[1]), tims)
	if bank == null:
		seq = KmsPlayer.new(null, null)
		_start_output()
		return false
	if c == 2 or c == 4 or c == 0x20:
		chip = Opl2.new(RATE)
		driver = FmDriver.new(chip, bank)
	seq = KmsPlayer.new(driver, bank)
	seq.music_class = {1: PcSpeaker.CLASS, 8: Mt32.CLASS}.get(c, FmDriver.CLASS)
	if c == 2 or c == 0x20:
		var digital := Sounds.load_bank(read_file.call("pcff001.pat"), read_file.call("pcff001.tim"), read_file.call("pcff001.dig"))
		if digital != null:
			dac = DacDriver.new(bank, digital.programs, RATE)
			seq.dac = dac
	if c == 1:
		speaker = PcSpeaker.new(bank, RATE)
		seq.extra.append(speaker)
	if c == 8:
		mt32 = Mt32.new(bank, RATE)
		seq.extra.append(mt32)
		# load_sound_config plays MT32HOCK.KMS once: the MT-32's timbres, patches and rhythm setup
		var init := load_song("MT32HOCK")
		if init != null:
			var h := seq.play(init)
			var guard := 0
			while seq.playing(h) and guard < 2000:
				seq.tick()
				guard += 1
			seq.stop(h)
	_start_output()
	return true

func _start_output() -> void:
	if DisplayServer.get_name() == "headless" or player != null:
		return
	var gen := AudioStreamGenerator.new()
	gen.mix_rate = RATE
	gen.buffer_length = 0.2
	player = AudioStreamPlayer.new()
	player.stream = gen
	add_child(player)
	player.play()
	playback = player.get_stream_playback()

## the card plays digitised sound (sound_enabled: the Sound Blaster and the UltraSound)
func digital() -> bool:
	return dac != null

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
	return not r.is_empty() and (r[0xf] & 0x7f) == FmDriver.CLASS and not bank.timbre(r[1], r[0]).is_empty()

## snd_play_patch: any effect of the card's bank (FM, digital, speaker, MT-32)
func play_effect(id: int, volume: int = 0x7f) -> int:
	if seq == null or bank == null or bank.record(id).is_empty():
		return -1
	return seq.play_effect(id, volume)

## playsample / playsample_raw: a sample straight on a voice of the digital driver
func play_sample(voice: int, data: PackedByteArray, rate: int, volume: int, loop_start := 0, loop_len := 0, packed := false) -> void:
	if dac != null:
		dac.play_sample(voice, data, rate, volume, loop_start, loop_len, packed)

## sound_channel_status: the voice has ended
func sample_done(voice: int) -> bool:
	return dac == null or dac.mix_free(voice)

func stop_sample(voice: int) -> void:
	if dac != null:
		dac.play_sample(voice, PackedByteArray(), 0, 0)

# ---------------------------------------------------------------------------------------------
# the crowd (update_ambient_audio 0x594cd, sound_pause_all 0x59748, sound_resume_all 0x59863)
# ---------------------------------------------------------------------------------------------

## the driver of the crowd (byte_d2439): the digital one of the Sound Blaster, the MT-32
func _crowd_send(status: int, d1: int, d2: int) -> void:
	var s := status & 0xf0
	if s == 0x80 or s == 0x90:
		d1 = (d1 + 0x18) & 0xff
	if dac != null:
		dac.midi(status, d1, d2)
	elif mt32 != null:
		mt32.midi(status, d1, d2)

func _crowd_card() -> bool:
	return card & 0x2a != 0 and (dac != null or mt32 != null)

## update_ambient_audio(step): the crowd level follows crowd_noise by 30 a timer tick at most; above
## 0x200 the roar (program 0x7d on channel 8) sounds, its volume rising with the level (a random bend
## when it is at its loudest); the murmur (0x7e on channel 7) always sounds, louder and higher with
## the level (the MT-32's levels start higher)
func ambient(crowd_noise: int, step: int, sfx_on: bool) -> void:
	if not sfx_on or not _crowd_card():
		return
	var mt := card & 8 != 0
	var diff := crowd_noise - crowd_level
	if absi(diff) > step * 30:
		crowd_level += step * 30 if diff > 0 else -step * 30
	else:
		crowd_level = crowd_noise
	var v8 := 0
	if crowd_level < 0x200:
		v8 = 0
	elif crowd_level < 0x390:
		v8 = (crowd_level - 0x200) / 10 + (0x20 if mt else 0)
	else:
		v8 = ((crowd_level - 0x390) >> 2) + (0x48 if mt else 0x28)
	v8 = mini(v8, 0x7f)
	var v7 := crowd_level / 12 + (0x3c if mt else 10)
	v7 = clampi(v7, 10, 0x7f)
	if roar > 0 and v8 == 0:
		_crowd_send(0xb8, 7, 0)
		_crowd_send(0x88, 0x24, 0)
	elif roar == 0 and v8 > 0:
		_crowd_send(0xc8, 0x7d, 0)
		_crowd_send(0x98, 0x24, 0x7f)
		_crowd_send(0xe8, 0, 0x40)
	if v8 > 0:
		_crowd_send(0xb8, 7, v8)
		if v8 > 0x7e or roar > 0x7e:
			var r := 0 if v8 < 0x7f else rng.randi_range(0, 5)
			_crowd_send(0xe8, 0, 0x40 - r)
	roar = v8
	if murmur == 0 and v7 > 0:
		_crowd_send(0xc7, 0x7e, 0)
		_crowd_send(0x97, 0x24, 0x7f)
	_crowd_send(0xb7, 7, v7)
	var bend := v7 / 3 + 0x20
	if v7 == (0x32 if mt else 0) + 10:
		bend += rng.randi_range(0, 5)
	_crowd_send(0xe7, 0, bend & 0x7f)
	murmur = v7

## sound_pause_all: the crowd's channels silent and their notes off
func ambient_pause() -> void:
	if not _crowd_card():
		return
	if roar > 0:
		_crowd_send(0xb8, 7, 0)
		_crowd_send(0x88, 0x24, 0)
		roar = 0
	if murmur > 0:
		_crowd_send(0xb7, 7, 0)
		_crowd_send(0x87, 0x24, 0)
		murmur = 0

## sound_resume_all
func ambient_resume() -> void:
	crowd_level = 0
	roar = 0
	murmur = 0

# ---------------------------------------------------------------------------------------------
# output
# ---------------------------------------------------------------------------------------------

func stop_all() -> void:
	stop_song()
	seq.stop_all()
	# the crowd's notes are gone with the voices (sound_pause_all)
	roar = 0
	murmur = 0
	if driver != null:
		driver.all_off()
	if dac != null:
		dac.all_off()
	if speaker != null:
		speaker.all_off()
	if mt32 != null:
		mt32.all_off()

func _tick() -> void:
	if driver != null:
		driver.tick()
	seq.tick()
	if dac != null:
		dac.tick()
	if speaker != null:
		speaker.tick()
	if mt32 != null:
		mt32.tick()

## n mono samples of the card, the timers included
func render(n: int) -> PackedFloat32Array:
	var out := PackedFloat32Array()
	out.resize(n)
	var done := 0
	while done < n:
		if until_tick <= 0.0:
			_tick()
			until_tick += TICK
		var len := mini(n - done, int(ceil(until_tick)))
		if chip != null:
			chip.render(out, done, len)
		if dac != null:
			dac.render(out, done, len)
		if speaker != null:
			speaker.render(out, done, len)
		if mt32 != null:
			mt32.render(out, done, len)
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

func _silent() -> bool:
	if not seq.tracks.is_empty():
		return false
	if driver != null and (driver.active_voices() != 0 or chip.active_channels() != 0):
		return false
	if dac != null and dac.active() != 0:
		return false
	if speaker != null and (speaker.active() != 0 or absf(speaker.lp) > 1e-4):
		return false
	if mt32 != null and mt32.active() != 0:
		return false
	return true

func _process(delta: float) -> void:
	if seq == null:
		return
	if playback == null:
		# no audio output (headless): the timers still run
		_advance(int(delta * RATE))
		return
	var n := mini(playback.get_frames_available(), int(RATE * 0.1))
	if n <= 0:
		return
	if _silent():
		# nothing sounds: keep the timers going without the chips
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

## the 100 Hz timers for n samples without the chips
func _advance(n: int) -> void:
	var t := n
	while t > 0:
		if until_tick <= 0.0:
			_tick()
			until_tick += TICK
		var step := mini(t, int(ceil(until_tick)))
		until_tick -= step
		t -= step
