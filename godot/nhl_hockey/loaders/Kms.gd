class_name Kms
extends RefCounted
## A song of the music driver (music_load_kms 0x8f13b): NAME.KMS and its NAME.CFG.
##
##   .KMS  +1 u8 tempo (a track advances 128 / (32000 / tempo) steps per 100 Hz timer tick, i.e.
##         0.4 * tempo steps per second: 24 steps a beat), +6 u8 track count, +8 u16 file offsets
##         of the tracks. A track is a list of events, each a delta time (7 bit groups, the high bit
##         continues) and an event byte:
##           < 0xd9  note (low 7 bits, + 24 when sent to the driver), velocity byte (a note byte
##                   below 0x80 uses the running velocity instead), length in steps (7 bit groups)
##           0xd9/0xda end (or return from a call), 0xdb back to the start, 0xdc program, 0xdd tempo,
##           0xdf controller number and value, 0xe2 / 0xe3 loop start (count) / end, 0xe4 running
##           velocity, 0xe5 pitch bend (u16, the high byte is sent), 0xe6 call, 0xe7 text (length
##           byte), 0xe8 system exclusive (length byte, MT-32 only), 0xea marker; the others carry
##           one byte
##   .CFG  per track 16 bytes from +8: u16 mask of the MIDI channels it may use (the first free one
##         is taken), +6 volume (controller 7), +7 pan (controller 10)

var name := ""
var data := PackedByteArray()
var tempo := 120
var tracks: Array = []        # [offset, channel mask, volume, pan, name]

static func parse(kms: PackedByteArray, cfg: PackedByteArray, song_name: String = "") -> Kms:
	if kms.size() < 10:
		return null
	var k := Kms.new()
	k.name = song_name
	k.data = kms
	k.tempo = maxi(kms[1], 1)
	var n := kms[6]
	for t in n:
		if 8 + 2 * t + 2 > kms.size():
			return null
		var off := kms.decode_u16(8 + 2 * t)
		var mask := 0xffff
		var vol := 0x64
		var pan := 0x40
		if cfg.size() >= 8 + 16 * t + 8:
			mask = cfg.decode_u16(8 + 16 * t)
			vol = cfg[8 + 16 * t + 6]
			pan = cfg[8 + 16 * t + 7]
		k.tracks.append([off, mask, vol, pan, _track_name(kms, off)])
	return k

## the text event (0xe7) at the start of a track names it ("left", "right", "kick/snar", ...)
static func _track_name(d: PackedByteArray, off: int) -> String:
	var p := off
	if p >= d.size():
		return ""
	while p < d.size() and d[p] & 0x80:
		p += 1
	p += 1
	if p + 1 < d.size() and d[p] == 0xe7:
		var n := d[p + 1]
		return d.slice(p + 2, p + 2 + n).get_string_from_ascii()
	return ""

## the events of a track as [position, delta, event, args...] (for tools and tests)
func events(track: int) -> Array:
	var out: Array = []
	var p: int = tracks[track][0]
	while p < data.size():
		var ev := read_event(data, p)
		if ev.is_empty():
			break
		out.append(ev)
		p += ev[1]
		if ev[3] == 0xd9 or ev[3] == 0xda or ev[3] == 0xdb:
			break
	return out

## kms_read_event: the event at p as [p, length, delta, event, a, b] (a = velocity / value byte, b =
## note length / word / controller value)
static func read_event(d: PackedByteArray, p: int) -> Array:
	var start := p
	var delta := 0
	while true:
		if p >= d.size():
			return []
		var c := d[p]
		p += 1
		delta = delta * 128 + (c & 0x7f)
		if c & 0x80 == 0:
			break
	if p >= d.size():
		return []
	var ev := d[p]
	p += 1
	var a := 0
	var b := 0
	if ev < 0xd9:
		a = d[p]
		p += 1
		while true:
			var c := d[p]
			p += 1
			b = b * 128 + (c & 0x7f)
			if c & 0x80 == 0:
				break
	elif ev == 0xd9 or ev == 0xda or ev == 0xdb or ev == 0xe3:
		pass
	elif ev == 0xdf:
		a = d[p]
		b = d[p + 1]
		p += 2
	elif ev == 0xe5:
		b = d[p] | (d[p + 1] << 8)
		p += 2
	elif ev == 0xe6:
		a = d[p]
		b = d.decode_u32(p + 1)
		p += 5
	elif ev == 0xe7 or ev == 0xe8:
		a = d[p]
		p += 1 + a
	else:
		a = d[p]
		p += 1
	return [start, p - start, delta, ev, a, b]

## the length in seconds of a song without loops (the longest track)
func duration() -> float:
	var longest := 0
	for t in tracks.size():
		var steps := 0
		var last_end := 0
		for ev in events(t):
			steps += ev[2]
			if ev[3] < 0xd9:
				last_end = maxi(last_end, steps + ev[5])
		longest = maxi(longest, maxi(steps, last_end))
	return longest / (0.4 * tempo)
