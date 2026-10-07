class_name KmsPlayer
extends RefCounted
## The music sequencer and sound effect notes of the game's sound layer, ported from the timer
## routine sound_timer_tick (100 Hz): the tracks of the playing songs (kms_track_tick, up to 24 tracks), the
## note table of 32 sounding notes with their remaining length (snd_note_on note on, snd_note_off
## note off) and snd_play_patch (0x8f4c4) for the FM sound effects. Everything sent to the driver
## passes drv_send_midi, which adds 24 to the note of note on / off messages.

const NOTES := 32
const TRACKS := 24

class Track:
	var id := 0
	var song: Kms
	var handle := 0
	var pos := 0                  # +0xa, 0 = ended
	var start := 0                # +0x32 the first event (0xdb jumps back)
	var delta := 0                # +0xe
	var acc := 0                  # +0x4a
	var div := 266                # +0x4c 32000 / tempo
	var channel := 0              # +0x50
	var program := 0              # +0x4f
	var velocity := 0x64          # +0x52 running velocity
	var marker := 0               # +0x4e
	var loop_pos: Array = []      # +0x18 / +0x12
	var loop_count: Array = []
	var calls: Array = []         # +0x32.. return addresses (+0x31 depth)
	var cls := 1                  # +0x51 the driver of its messages (the class of its program's record)

class Note:
	var handle := 0               # 0 = free; the song (or 0xff for an effect)
	var note := 0
	var track := 0                # 0xff for an effect
	var channel := 0
	var length := 0
	var cls := 1                  # +7 the driver

var driver: FmDriver
var dac: DacDriver = null         # the digital instruments of the Sound Blaster driver
var extra: Array = []             # the other drivers of the card (PcSpeaker, Mt32): anything with midi()
var bank: FmBank                  # the card's patch records (snd_patch_record)
var music_class := 1              # the driver of the songs (the FM driver; the MT-32's, the speaker's)
var tracks: Array = []
var notes: Array = []
var channel_used := PackedInt32Array()
var next_handle := 0x200
var sfx_channel := 0
var music_enabled := true
var song_volume := 0x7f           # +0x11 of the song record
var song_pan := 0x3f              # +0x12
var song_transpose := 0           # +0x13

func _init(d: FmDriver, b: FmBank = null) -> void:
	driver = d
	bank = b if b != null else (d.bank if d != null else null)
	for i in NOTES:
		notes.append(Note.new())
	channel_used.resize(16)

## the driver of a class (+0xf of a patch record): 1 FM, 4 digital, 3 MPU-401, 5 speaker
func driver_of(cls: int):
	if driver != null and cls == FmDriver.CLASS:
		return driver
	if dac != null and cls == DacDriver.CLASS:
		return dac
	for e in extra:
		if e.CLASS == cls:
			return e
	return null

## the class of a program's record: a record of a driver the card has, else none (0x7f: muted,
## like a record bind_patch_timbres did not bind)
func class_of(program: int) -> int:
	var rec := bank.record(program & 0xff) if bank != null else PackedByteArray()
	if rec.is_empty():
		return 0x7f
	var cls := rec[0xf] & 0x7f
	return cls if driver_of(cls) != null else 0x7f

## drv_send_midi: a message to one driver; note on / off get 24 added to the note
func _send_to(cls: int, status: int, d1: int, d2: int) -> void:
	var s := status & 0xf0
	if s == 0x80 or s == 0x90:
		d1 = (d1 + 0x18) & 0xff
		if d1 >= 0x80:
			return
	var d = driver_of(cls)
	if d != null:
		d.midi(status, d1, d2)

## a message to every driver of the card (the end of a song)
func _send(status: int, d1: int, d2: int) -> void:
	for cls in [FmDriver.CLASS, DacDriver.CLASS, 3, 5]:
		_send_to(cls, status, d1, d2)

# --------------------------------------------------------------------------------------------
# songs (kms_start start, snd_stop_handle stop)
# --------------------------------------------------------------------------------------------

## starts a song on the free MIDI channels its tracks may use; returns its handle (0 = failed)
func play(song: Kms) -> int:
	if song == null:
		return 0
	next_handle += 1
	var handle := next_handle
	for t in song.tracks.size():
		if tracks.size() >= TRACKS:
			break
		var tr := Track.new()
		tr.id = t
		tr.song = song
		tr.handle = handle
		tr.pos = song.tracks[t][0]
		tr.start = tr.pos
		tr.div = 32000 / song.tempo
		var ch := _free_channel(song.tracks[t][1])
		if ch < 0:
			stop(handle)
			return 0
		tr.channel = ch
		tr.cls = music_class
		tracks.append(tr)
		_send_to(tr.cls, 0xc0 | ch, 0, 0)
		_controller(tr, 1, 0)
		_controller(tr, 7, song.tracks[t][2])
		_controller(tr, 10, song.tracks[t][3])
		_send_to(tr.cls, 0xe0 | ch, 0, 0x40)
	return handle

## kms_track_channel: the first channel of the mask not reserved (the sound effects' 9 and 12..15 are
## shared, as in the original)
func _free_channel(mask: int) -> int:
	for c in 16:
		if mask & (1 << c):
			return c
	return -1

## snd_stop_handle: the song's notes off, its channels silenced (all notes off, volume 0)
func stop(handle: int) -> void:
	for n in notes:
		if n.handle == handle:
			_note_off(n)
	var keep: Array = []
	for tr in tracks:
		if tr.handle == handle:
			_send_to(tr.cls, 0xb0 | tr.channel, 0x7b, 0)
			_send_to(tr.cls, 0xb0 | tr.channel, 7, 0)
		else:
			keep.append(tr)
	tracks = keep
	_send(0xb9, 7, 0x7f)

func stop_all() -> void:
	var handles := {}
	for tr in tracks:
		handles[tr.handle] = true
	for h in handles:
		stop(h)

## kms_finished: the song still has a running track
func playing(handle: int) -> bool:
	for tr in tracks:
		if tr.handle == handle and tr.pos != 0:
			return true
	return false

# --------------------------------------------------------------------------------------------
# the 100 Hz timer (sound_timer_tick)
# --------------------------------------------------------------------------------------------

func tick() -> void:
	for tr in tracks:
		if tr.pos != 0:
			_track_tick(tr)
	var keep: Array = []
	for tr in tracks:
		if tr.pos != 0:
			keep.append(tr)
	tracks = keep
	# the notes of the sound effects count down in timer ticks
	for n in notes:
		if n.handle != 0 and n.track == 0xff:
			n.length -= 1
			if n.length == 0:
				_note_off(n)

## kms_track_tick
func _track_tick(tr: Track) -> void:
	tr.acc += 0x80
	while tr.acc >= tr.div and tr.pos != 0:
		for n in notes:
			if n.handle == tr.handle and n.track == tr.id:
				n.length -= 1
				if n.length == 0:
					_note_off(n)
		if tr.delta == 0:
			while tr.delta == 0 and tr.pos != 0:
				_event(tr)
				if tr.pos != 0:
					var nx := Kms.read_event(tr.song.data, tr.pos)
					if nx.is_empty():
						tr.pos = 0
					else:
						tr.delta = nx[2]
			tr.delta -= 1
		else:
			tr.delta -= 1
		tr.acc -= tr.div

func _event(tr: Track) -> void:
	var d := tr.song.data
	var ev := Kms.read_event(d, tr.pos)
	if ev.is_empty():
		tr.pos = 0
		return
	var after: int = tr.pos + ev[1]
	tr.pos = after
	var code: int = ev[3]
	var a: int = ev[4]
	var b: int = ev[5]
	if code < 0xd9:
		var vel := a if code >= 0x80 else tr.velocity
		var note := code & 0x7f
		if tr.channel != 9:
			note = (note + song_transpose) & 0xff
		if music_enabled:
			# the drums' driver is the one of the note's record (note + 0x5c)
			var cls := class_of(note + 0x5c) if tr.channel == 9 else tr.cls
			_note_on(note, vel, b, tr.channel, tr.id, tr.handle, cls)
		return
	match code:
		0xd9, 0xda:
			if tr.calls.is_empty():
				tr.pos = 0
			else:
				tr.pos = tr.calls.pop_back()
		0xdb:
			tr.calls.clear()
			tr.loop_pos.clear()
			tr.loop_count.clear()
			tr.pos = tr.start
		0xdc:
			# the program's record decides the driver of the track's messages from now on
			tr.program = a
			if bank != null and not bank.record(a).is_empty():
				tr.cls = class_of(a)
			_send_to(tr.cls, 0xc0 | tr.channel, a, 0)
		0xdd:
			for o in tracks:
				if o.handle == tr.handle:
					o.div = 32000 / maxi(a, 1)
		0xdf:
			_controller(tr, a, b & 0xff)
		0xe2:
			tr.loop_pos.append(after)
			tr.loop_count.append((a - 1) & 0xff)
		0xe3:
			if not tr.loop_pos.is_empty():
				tr.pos = tr.loop_pos.back()
				var c: int = tr.loop_count.back()
				tr.loop_count[tr.loop_count.size() - 1] = (c - 1) & 0xff
				if c == 0:
					tr.loop_pos.pop_back()
					tr.loop_count.pop_back()
		0xe4:
			tr.velocity = a
		0xe5:
			_send_to(tr.cls, 0xe0 | tr.channel, 0, (b >> 8) & 0x7f)
		0xe8:
			# system exclusive (MT32HOCK.KMS sets up the MT-32): to the drivers that take it
			var data := d.slice(after - a, after)
			for e in extra:
				if e.has_method("sysex"):
					e.sysex(data)
		0xea:
			tr.marker = a

## kms_controller: a controller of a track; the volume scaled by the song's volume, the pan by its pan
func _controller(tr: Track, num: int, val: int) -> void:
	if num == 7:
		val = mini(song_volume * val / 0x7f, 0x7f)
	elif num == 10:
		if song_pan < 0x40:
			val = val - (0x3f - song_pan) * val / 0x3f
		else:
			val = val + (0x7f - val) * (song_pan - 0x3f) / 0x3f
	_send_to(tr.cls, 0xb0 | tr.channel, num, val)

## snd_note_on: a free entry of the note table, the note on
func _note_on(note: int, vel: int, length: int, channel: int, track: int, handle: int, cls: int) -> int:
	for i in NOTES:
		var n: Note = notes[i]
		if n.handle == 0:
			n.handle = handle
			n.note = note
			n.track = track
			n.channel = channel
			n.cls = cls
			n.length = length if length != 0 else 1
			_send_to(cls, 0x90 | channel, note, vel)
			return i
	return -1

## snd_note_off
func _note_off(n: Note) -> void:
	_send_to(n.cls, 0x80 | n.channel, n.note, 0)
	n.handle = 0

# --------------------------------------------------------------------------------------------
# sound effects (snd_play_patch 0x8f4c4) of the FM type
# --------------------------------------------------------------------------------------------

## an FM sound effect: ids >= 0x80 are drum notes on channel 9 (note id - 0x74, the driver plays
## patch id), the others a program on one of the channels 12..15 at note 0x24; the length comes
## from the patch record (+0xe x 6 ticks, 0xa0 when 0)
func play_effect(id: int, volume: int = 0x7f) -> int:
	if bank == null:
		return -1
	var rec := bank.record(id)
	if rec.is_empty():
		return -1
	var length: int = rec[0xe] * 6 if rec[0xe] != 0 else 0xa0
	var cls := class_of(id)
	if id < 0x80:
		var ch := 12 + sfx_channel
		sfx_channel = (sfx_channel + 1) & 3
		_send_to(cls, 0xc0 | ch, id, 0)
		_send_to(cls, 0xb0 | ch, 7, volume)
		return _note_on(0x24, 0x7f, length, ch, 0xff, 0xff, cls)
	_send_to(cls, 0xb9, 7, volume)
	return _note_on((id - 0x74) & 0xff, 0x7f, length, 9, 0xff, 0xff, cls)
