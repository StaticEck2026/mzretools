class_name Viv
## The announcer's speech bank XBRUCE2.VIV (speech_load_bank 0x83897): an EA 0xC0FB archive.
##   +0 u16 BE 0xC0FB, +2 u16 BE size of the index, +4 u16 BE entry count, then per entry a 24 bit
##   BE offset, a 24 bit BE size (read_be32 reads three bytes) and a zero terminated name.
## An entry is either raw unsigned 8 bit PCM played at 5512 Hz (the duration is size * 100 / 5512
## ticks) or packed with code 0x47 0xFB (unpack -> bytepair_decode 0x97a38: an escape byte, a
## table of byte pairs that expand recursively, the escape followed by 0 ends the data); the
## unpacked data skips a 5 byte header and is a running sum (speech_delta_decode) of signed 8 bit samples
## played at 11025 Hz.

const RAW_RATE := 5512
const PACKED_RATE := 11025

var data: PackedByteArray
var entries: Dictionary = {}        # lower case name -> [offset, size] (the 8 .int names stored twice keep the first)
var count := 0
var cache: Dictionary = {}

static func parse(d: PackedByteArray) -> Viv:
	if d.size() < 6 or d[0] != 0xc0 or d[1] != 0xfb:
		return null
	var v := Viv.new()
	v.data = d
	v.count = (d[4] << 8) | d[5]
	var p := 6
	for i in v.count:
		if p + 6 > d.size():
			return null
		var off := (d[p] << 16) | (d[p + 1] << 8) | d[p + 2]
		var size := (d[p + 3] << 16) | (d[p + 4] << 8) | d[p + 5]
		p += 6
		var e := p
		while e < d.size() and d[e] != 0:
			e += 1
		var name := d.slice(p, e).get_string_from_ascii().to_lower()
		p = e + 1
		if not v.entries.has(name):
			v.entries[name] = [off, size]
	return v

func has(name: String) -> bool:
	return entries.has(name.to_lower())

## bytepair_decode: returns the unpacked bytes (the length is in the header)
static func bytepair_decode(src: PackedByteArray) -> PackedByteArray:
	var q := 5 if (src[0] == 0x47 and src[1] == 0xfb) else 2
	var total := (src[q] << 16) | (src[q + 1] << 8) | src[q + 2]
	var flag := PackedByteArray()
	flag.resize(256)
	var left := PackedByteArray()
	left.resize(256)
	var right := PackedByteArray()
	right.resize(256)
	flag[src[q + 3]] = 1                  # the escape byte
	var pairs := src[q + 4]
	var r := q + 5
	for i in pairs:
		var c := src[r]
		left[c] = src[r + 1]
		right[c] = src[r + 2]
		flag[c] = 0xff
		r += 3
	var out := PackedByteArray()
	out.resize(total)
	var n := 0
	var stack := PackedInt32Array()
	while r < src.size() and n < total:
		var b := src[r]
		r += 1
		if flag[b] == 0:
			out[n] = b
			n += 1
			continue
		if flag[b] == 0xff:
			# bytepair_expand: a pair expands into its left and right byte, recursively
			stack.clear()
			stack.append(b)
			while stack.size() > 0 and n < total:
				var c := stack[stack.size() - 1]
				stack.remove_at(stack.size() - 1)
				if flag[c] == 0xff:
					stack.append(right[c])
					stack.append(left[c])
				else:
					out[n] = c
					n += 1
			continue
		var lit := src[r]
		r += 1
		if lit == 0:
			break
		out[n] = lit
		n += 1
	out.resize(n)
	return out

## the clip as signed 8 bit samples and its rate
func samples(name: String) -> Array:
	var key := name.to_lower()
	if not entries.has(key):
		return []
	var e: Array = entries[key]
	var raw := data.slice(e[0], e[0] + e[1])
	if raw.size() > 1 and raw[0] == 0x47 and raw[1] == 0xfb:
		var un := bytepair_decode(raw)
		var pcm := PackedByteArray()
		pcm.resize(maxi(un.size() - 5, 0))
		var acc := 0
		for i in pcm.size():
			acc = (acc + un[i + 5]) & 0xff
			pcm[i] = acc
		return [pcm, PACKED_RATE]
	var s := PackedByteArray()
	s.resize(raw.size())
	for i in raw.size():
		s[i] = raw[i] ^ 0x80
	return [s, RAW_RATE]

## the clip as an AudioStreamWAV (cached), null when the bank has no such clip
func stream(name: String) -> AudioStreamWAV:
	var key := name.to_lower()
	if cache.has(key):
		return cache[key]
	var smp := samples(key)
	if smp.is_empty():
		return null
	var w := AudioStreamWAV.new()
	w.format = AudioStreamWAV.FORMAT_8_BITS
	w.mix_rate = smp[1]
	w.data = smp[0]
	cache[key] = w
	return w

## the duration in ticks of 100 Hz (speech_load_bank: samples * 100 / rate)
func ticks(name: String) -> int:
	var key := name.to_lower()
	if not entries.has(key):
		return 0
	var e: Array = entries[key]
	if data[e[0]] == 0x47 and data[e[0] + 1] == 0xfb:
		var q: int = e[0] + 6
		var n := ((data[q] << 8) | data[q + 1]) - 5
		return roundi(n * 100.0 / PACKED_RATE)
	return roundi(e[1] * 100.0 / RAW_RATE)
