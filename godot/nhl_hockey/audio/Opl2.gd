class_name Opl2
extends RefCounted
## The Yamaha YM3812 (OPL2) of the AdLib and Sound Blaster cards, the chip the FM driver (FmDriver,
## adlib_drv_* of HOCKEY.EXE) programs, computed the way the chip does it, sample by sample at its
## own rate of 49716 Hz (14.31818 MHz / 288), after the published analyses of the die (the ROM tables
## and the envelope generator, as Nuked-OPL3 implements them for the OPL2 compatible mode):
##
## - phase: a 19 bit accumulator a slot, F-number << block >> 1 times the multiplier (MULT x 2 table)
##   a sample, the vibrato (8 steps every 1024 samples, depth 7 or 14 cents) added to the F-number;
##   the 10 bit phase of the previous sample is the one the operator uses
## - operator: the quarter wave log-sin ROM (256 x 12 bit: round(-log2(sin((i + 0.5) pi / 512)) 256))
##   plus the attenuation << 3, through the exponent ROM (256 x 10 bit: 2^(i / 256)) and a shift;
##   the four waveforms of register E0 (enabled by bit 5 of register 01); a 13 bit signed output
## - modulation: the modulator's output added to the carrier's phase; feedback (the slot's two last
##   outputs) >> (9 - FB); register C0 bit 0 adds both operators instead
## - envelope: a 9 bit attenuation (0.1875 dB) per slot with the global envelope timer: rates
##   4 R + KSR offset, increments by the timer's low bits (eg_incstep) and shifts, the attack
##   following ~level, key scale level (KSL ROM, shifts 8 / 1 / 2 / 0), total level << 2, tremolo
##   (210 steps of 64 samples, depth 1 or 4.8 dB)
## - output: the channels added and clipped to 16 bits, then the YM3014 DAC's floating point (10 bit
##   mantissa, 3 bit exponent).
##
## The output stream (render) is the chip's samples averaged over each output sample. The rhythm
## mode (register BD bit 5) is not modelled: the game's drivers never set it.
##
## GDScript is too slow for 49716 samples a second of nine channels in real time, so the same
## arithmetic is also compiled as the native class Opl2Chip (native/opl2, a GDExtension); when its
## library is there for the platform the chip runs there, else here (chip_block).

const CHIP_RATE := 49716.0
const MULT_X2 := [1, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 20, 24, 24, 30, 30]
const KSL_ROM := [0, 32, 40, 45, 48, 51, 53, 55, 56, 58, 59, 60, 61, 62, 63, 64]
const KSL_SHIFT := [8, 1, 2, 0]
const EG_INCSTEP := [[0, 0, 0, 0], [1, 0, 0, 0], [1, 0, 1, 0], [1, 1, 1, 0]]
const SLOT_OF_OFFSET := [0, 1, 2, 3, 4, 5, -1, -1, 6, 7, 8, 9, 10, 11, -1, -1, 12, 13, 14, 15, 16, 17, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1]
# the slots of the channels: channel c has the modulator CH_MOD[c] and the carrier CH_MOD[c] + 3
const CH_MOD := [0, 1, 2, 6, 7, 8, 12, 13, 14]

enum { EG_ATTACK, EG_DECAY, EG_SUSTAIN, EG_RELEASE }

static var logsin := PackedInt32Array()
static var exprom := PackedInt32Array()

var sample_rate := 22050.0
var gain := 0.2 / 4084.0             # a channel at full level against the other sources of the port

# registers
var wse := false
var nts := 0
var tremolo_shift := 4
var vib_shift := 1
# per slot (18, in register offset order: 0..5 channels 0..2, 6..11 channels 3..5, 12..17 channels 6..8)
var s_am := PackedInt32Array()
var s_vib := PackedInt32Array()
var s_egt := PackedInt32Array()
var s_ksr := PackedInt32Array()
var s_mult := PackedInt32Array()
var s_ksl := PackedInt32Array()
var s_tl := PackedInt32Array()
var s_ar := PackedInt32Array()
var s_dr := PackedInt32Array()
var s_sl := PackedInt32Array()
var s_rr := PackedInt32Array()
var s_wf := PackedInt32Array()
var s_key := PackedInt32Array()
var s_phase := PackedInt32Array()     # pg_phase
var s_rout := PackedInt32Array()      # eg_rout
var s_gen := PackedInt32Array()       # eg_gen
var s_eksl := PackedInt32Array()      # eg_ksl
var s_out := PackedInt32Array()
var s_prout := PackedInt32Array()
var s_ch := PackedInt32Array()        # the channel of the slot
var s_reset := PackedInt32Array()     # pg_reset: the key on restarts the phase after this sample
# per channel
var ch_fnum := PackedInt32Array()
var ch_block := PackedInt32Array()
var ch_kon := PackedInt32Array()
var ch_fb := PackedInt32Array()
var ch_cnt := PackedInt32Array()
var ch_ksv := PackedInt32Array()
# the chip's timers
var timer := 0
var eg_timer := 0
var eg_state := 0
var eg_add := 0
var eg_timer_lo := 0
var tremolo_pos := 0
var tremolo := 0
var vib_pos := 0
# resampling
var acc := 0.0
var step_ratio := 1.0
var native: RefCounted = null         # Opl2Chip, when the native library is loaded

static func _tables() -> void:
	if logsin.size() == 256:
		return
	logsin.resize(256)
	exprom.resize(256)
	for i in 256:
		logsin[i] = roundi(-log(sin((i + 0.5) * PI / 512.0)) / log(2.0) * 256.0)
		exprom[i] = roundi(pow(2.0, (255 - i) / 256.0) * 1024.0)

func _init(rate: float = 22050.0, allow_native: bool = true) -> void:
	_tables()
	sample_rate = rate
	step_ratio = CHIP_RATE / rate
	for arr in [s_am, s_vib, s_egt, s_ksr, s_mult, s_ksl, s_tl, s_ar, s_dr, s_sl, s_rr, s_wf, s_key, s_phase, s_rout, s_gen, s_eksl, s_out, s_prout, s_ch, s_reset]:
		arr.resize(18)
	for arr in [ch_fnum, ch_block, ch_kon, ch_fb, ch_cnt, ch_ksv]:
		arr.resize(9)
	for c in 9:
		s_ch[CH_MOD[c]] = c
		s_ch[CH_MOD[c] + 3] = c
	if allow_native and ClassDB.class_exists("Opl2Chip") and OS.get_environment("NHL_OPL_SCRIPT") != "1":
		native = ClassDB.instantiate("Opl2Chip")
		native.set_output_rate(rate)
		native.set_gain(gain)
	reset()

func reset() -> void:
	for s in 18:
		s_rout[s] = 0x1ff
		s_gen[s] = EG_RELEASE
		s_key[s] = 0
		s_phase[s] = 0
		s_out[s] = 0
		s_prout[s] = 0
		s_am[s] = 0
		s_vib[s] = 0
		s_egt[s] = 0
		s_ksr[s] = 0
		s_mult[s] = 0
		s_ksl[s] = 0
		s_tl[s] = 0
		s_ar[s] = 0
		s_dr[s] = 0
		s_sl[s] = 0
		s_rr[s] = 0
		s_wf[s] = 0
		s_eksl[s] = 0
	for c in 9:
		ch_fnum[c] = 0
		ch_block[c] = 0
		ch_kon[c] = 0
		ch_fb[c] = 0
		ch_cnt[c] = 0
		ch_ksv[c] = 0
	wse = false
	nts = 0
	tremolo_shift = 4
	vib_shift = 1
	if native != null:
		native.reset()

## a register write of the driver (port 0x388 / 0x389)
func write(reg: int, val: int) -> void:
	reg &= 0xff
	val &= 0xff
	if native != null:
		native.write(reg, val)
	match reg:
		0x01:
			wse = (val & 0x20) != 0
			return
		0x08:
			nts = (val >> 6) & 1
			for c in 9:
				_update_ksv(c)
			return
		0xbd:
			tremolo_shift = (((val >> 7) ^ 1) << 1) + 2
			vib_shift = ((val >> 6) & 1) ^ 1
			return
	if reg >= 0xa0 and reg <= 0xa8:
		var c := reg - 0xa0
		ch_fnum[c] = (ch_fnum[c] & 0x300) | val
		_update_ksv(c)
		return
	if reg >= 0xb0 and reg <= 0xb8:
		var c := reg - 0xb0
		ch_fnum[c] = (ch_fnum[c] & 0xff) | ((val & 3) << 8)
		ch_block[c] = (val >> 2) & 7
		_update_ksv(c)
		var kon := (val >> 5) & 1
		if kon != ch_kon[c]:
			ch_kon[c] = kon
			for s in [CH_MOD[c], CH_MOD[c] + 3]:
				s_key[s] = kon
		return
	if reg >= 0xc0 and reg <= 0xc8:
		ch_fb[reg - 0xc0] = (val >> 1) & 7
		ch_cnt[reg - 0xc0] = val & 1
		return
	var group := reg & 0xe0
	if group < 0x20 or (group > 0x80 and group != 0xe0):
		return
	var s: int = SLOT_OF_OFFSET[reg & 0x1f]
	if s < 0:
		return
	match group:
		0x20:
			s_am[s] = (val >> 7) & 1
			s_vib[s] = (val >> 6) & 1
			s_egt[s] = (val >> 5) & 1
			s_ksr[s] = (val >> 4) & 1
			s_mult[s] = val & 0xf
		0x40:
			s_ksl[s] = (val >> 6) & 3
			s_tl[s] = val & 0x3f
		0x60:
			s_ar[s] = (val >> 4) & 0xf
			s_dr[s] = val & 0xf
		0x80:
			s_sl[s] = (val >> 4) & 0xf
			if s_sl[s] == 0xf:
				s_sl[s] = 0x1f
			s_rr[s] = val & 0xf
		0xe0:
			s_wf[s] = val & 3

## the key scale value and the key scale level of a channel's slots
func _update_ksv(c: int) -> void:
	ch_ksv[c] = (ch_block[c] << 1) | ((ch_fnum[c] >> (9 - nts)) & 1)
	var ksl: int = (KSL_ROM[ch_fnum[c] >> 6] << 2) - ((8 - ch_block[c]) << 5)
	if ksl < 0:
		ksl = 0
	s_eksl[CH_MOD[c]] = ksl
	s_eksl[CH_MOD[c] + 3] = ksl

func active_channels() -> int:
	if native != null:
		return native.active_channels()
	var n := 0
	for c in 9:
		var car: int = CH_MOD[c] + 3
		if s_rout[car] < 0x1ff or s_key[car] != 0 or (ch_cnt[c] == 1 and (s_rout[CH_MOD[c]] < 0x1ff or s_key[CH_MOD[c]] != 0)):
			n += 1
	return n

## one sample of the chip
func _sample() -> int:
	var mix := 0
	for c in 9:
		var m: int = CH_MOD[c]
		var k: int = m + 3
		# a channel whose slots are silent keeps silent (no phase or envelope moves that matter)
		if s_key[m] == 0 and s_key[k] == 0 and s_rout[m] == 0x1ff and s_rout[k] == 0x1ff:
			s_out[m] = 0
			s_prout[m] = 0
			s_out[k] = 0
			continue
		# the modulator: feedback from its last two outputs
		var fbmod := 0
		if ch_fb[c] != 0:
			fbmod = (s_prout[m] + s_out[m]) >> (9 - ch_fb[c])
		s_prout[m] = s_out[m]
		var eo_m := _envelope(m)
		var ph_m := _phase(m)
		s_out[m] = _operator(m, ph_m + fbmod, eo_m)
		# the carrier: modulated by the modulator's new output, or added to it
		var eo_k := _envelope(k)
		var ph_k := _phase(k)
		if ch_cnt[c] == 0:
			s_out[k] = _operator(k, ph_k + s_out[m], eo_k)
			mix += s_out[k]
		else:
			s_out[k] = _operator(k, ph_k, eo_k)
			mix += s_out[k] + s_out[m]
	_timers()
	return clampi(mix, -32768, 32767)

## the chip's timers after the slots (OPL3_Generate): the LFOs (tremolo 210 steps of 64 samples,
## vibrato 8 steps of 1024) and the envelope timer, eg_add one more than its lowest set bit (on
## every other sample)
func _timers() -> void:
	if timer & 0x3f == 0x3f:
		tremolo_pos = (tremolo_pos + 1) % 210
	tremolo = (tremolo_pos if tremolo_pos < 105 else 210 - tremolo_pos) >> tremolo_shift
	if timer & 0x3ff == 0x3ff:
		vib_pos = (vib_pos + 1) & 7
	timer = (timer + 1) & 0xffff
	if eg_state:
		var shift := 0
		while shift < 13 and ((eg_timer >> shift) & 1) == 0:
			shift += 1
		eg_add = 0 if shift > 12 else shift + 1
		eg_timer_lo = eg_timer & 3
		eg_timer = (eg_timer + 1) & 0xfffffffff
	eg_state ^= 1

## OPL3_EnvelopeCalc: the attenuation of a slot this sample (returned) and its next value
func _envelope(s: int) -> int:
	var out: int = s_rout[s] + (s_tl[s] << 2) + (s_eksl[s] >> KSL_SHIFT[s_ksl[s]]) + (tremolo if s_am[s] else 0)
	if out > 0x1ff:
		out = 0x1ff
	var key := s_key[s]
	var gen := s_gen[s]
	var reset := 0
	var reg_rate := 0
	if key and gen == EG_RELEASE:
		reset = 1
		reg_rate = s_ar[s]
	else:
		match gen:
			EG_ATTACK:
				reg_rate = s_ar[s]
			EG_DECAY:
				reg_rate = s_dr[s]
			EG_SUSTAIN:
				if s_egt[s] == 0:
					reg_rate = s_rr[s]
			EG_RELEASE:
				reg_rate = s_rr[s]
	var c: int = s_ch[s]
	var ks: int = ch_ksv[c] >> ((s_ksr[s] ^ 1) << 1)
	var rate := ks + (reg_rate << 2)
	var rate_hi := rate >> 2
	var rate_lo := rate & 3
	if rate_hi & 0x10:
		rate_hi = 0xf
	var eg_shift := rate_hi + eg_add
	var shift := 0
	if reg_rate != 0:
		if rate_hi < 12:
			if eg_state:
				match eg_shift:
					12:
						shift = 1
					13:
						shift = (rate_lo >> 1) & 1
					14:
						shift = rate_lo & 1
		else:
			shift = (rate_hi & 3) + EG_INCSTEP[rate_lo][eg_timer_lo]
			if shift & 4:
				shift = 3
			if shift == 0:
				shift = eg_state
	var rout: int = s_rout[s]
	var inc := 0
	var off := false
	if reset and rate_hi == 0xf:
		rout = 0
	if (s_rout[s] & 0x1f8) == 0x1f8:
		off = true
	if gen != EG_ATTACK and not reset and off:
		rout = 0x1ff
	match gen:
		EG_ATTACK:
			if s_rout[s] == 0:
				s_gen[s] = EG_DECAY
			elif key and shift > 0 and rate_hi != 0xf:
				inc = (~s_rout[s]) >> (4 - shift)
		EG_DECAY:
			if (s_rout[s] >> 4) == s_sl[s]:
				s_gen[s] = EG_SUSTAIN
			elif not off and not reset and shift > 0:
				inc = 1 << (shift - 1)
		_:
			if not off and not reset and shift > 0:
				inc = 1 << (shift - 1)
	s_rout[s] = (rout + inc) & 0x1ff
	s_reset[s] = reset
	if reset:
		s_gen[s] = EG_ATTACK
	if not key:
		s_gen[s] = EG_RELEASE
	return out

## OPL3_PhaseGenerate: the 10 bit phase of the previous sample; the accumulator moves on
func _phase(s: int) -> int:
	var c: int = s_ch[s]
	var f: int = ch_fnum[c]
	if s_vib[s]:
		var r := (f >> 7) & 7
		if vib_pos & 3 == 0:
			r = 0
		elif vib_pos & 1:
			r >>= 1
		r >>= vib_shift
		if vib_pos & 4:
			r = -r
		f += r
	var basefreq := (f << ch_block[c]) >> 1
	var phase := (s_phase[s] >> 9) & 0x3ff
	if s_reset[s]:
		s_phase[s] = 0
	s_phase[s] = (s_phase[s] + ((basefreq * MULT_X2[s_mult[s]]) >> 1)) & 0x7ffff
	return phase

## the operator: log-sin of the phase's quarter wave, the attenuation, the exponent ROM
func _operator(s: int, phase: int, env: int) -> int:
	phase &= 0x3ff
	var wf: int = s_wf[s] if wse else 0
	var level := 0
	var neg := false
	match wf:
		0:
			neg = (phase & 0x200) != 0
			level = logsin[(phase & 0xff) ^ 0xff] if phase & 0x100 else logsin[phase & 0xff]
		1:
			if phase & 0x200:
				level = 0x1000
			else:
				level = logsin[(phase & 0xff) ^ 0xff] if phase & 0x100 else logsin[phase & 0xff]
		2:
			level = logsin[(phase & 0xff) ^ 0xff] if phase & 0x100 else logsin[phase & 0xff]
		3:
			level = 0x1000 if phase & 0x100 else logsin[phase & 0xff]
	level += env << 3
	if level > 0x1fff:
		level = 0x1fff
	var v: int = (exprom[level & 0xff] << 1) >> (level >> 8)
	return ~v if neg else v

## the YM3014B DAC: a 10 bit mantissa shifted by a 3 bit exponent
static func dac(x: int) -> int:
	var a := absi(x)
	var shift := 0
	while shift < 6 and (a >> shift) > 0x1ff:
		shift += 1
	return (x >> shift) << shift

## renders n samples (-1..1 for a channel at full level times gain), added to out from offset:
## the chip samples of each output sample averaged
func render(out: PackedFloat32Array, offset: int, n: int) -> void:
	if native != null:
		var r: PackedFloat32Array = native.render(n)
		for i in n:
			out[offset + i] += r[i]
		return
	var counts := PackedInt32Array()
	counts.resize(n)
	var total := 0
	for i in n:
		acc += step_ratio
		var k := int(acc)
		acc -= k
		counts[i] = k
		total += k
	var buf := PackedInt32Array()
	buf.resize(total)
	chip_block(buf)
	var j := 0
	for i in n:
		var k := counts[i]
		var sum := 0
		for q in k:
			sum += dac(clampi(buf[j], -32768, 32767))
			j += 1
		out[offset + i] += (float(sum) / maxi(k, 1)) * gain

## the chip for buf.size() samples: the sum of the channels of each sample in buf. The same
## arithmetic as _sample(), with the timers of the block computed first and each channel's two slots
## worked through the block one after the other (the channels do not depend on each other)
func chip_block(buf: PackedInt32Array) -> void:
	var nk := buf.size()
	buf.fill(0)
	# the timers as each sample's slots see them
	var g_trem := PackedInt32Array()
	var g_vib := PackedInt32Array()
	var g_add := PackedInt32Array()
	var g_state := PackedInt32Array()
	var g_lo := PackedInt32Array()
	for arr in [g_trem, g_vib, g_add, g_state, g_lo]:
		arr.resize(nk)
	for i in nk:
		g_trem[i] = tremolo
		g_vib[i] = vib_pos
		g_add[i] = eg_add
		g_state[i] = eg_state
		g_lo[i] = eg_timer_lo
		_timers()
	for c in 9:
		var m: int = CH_MOD[c]
		var kk: int = m + 3
		if s_key[m] == 0 and s_key[kk] == 0 and s_rout[m] == 0x1ff and s_rout[kk] == 0x1ff:
			s_out[m] = 0
			s_prout[m] = 0
			s_out[kk] = 0
			continue
		_channel_block(c, m, kk, buf, g_trem, g_vib, g_add, g_state, g_lo)

## the envelope rates of a slot by state (attack, decay, sustain, release, and 4: a key on in
## release, which restarts the attack): [rate_hi x 5, rate_lo x 5, the register's rate x 5]
func _rates(s: int, ks: int) -> PackedInt32Array:
	var r := PackedInt32Array()
	r.resize(15)
	var regs := [s_ar[s], s_dr[s], s_rr[s] if s_egt[s] == 0 else 0, s_rr[s], s_ar[s]]
	for i in 5:
		var rr: int = regs[i]
		var rate: int = ks + (rr << 2)
		var hi := rate >> 2
		if hi & 0x10:
			hi = 0xf
		r[i] = hi
		r[i + 5] = rate & 3
		r[i + 10] = rr
	return r

## the phase increment of a slot for each of the 8 vibrato positions
func _incs(s: int, c: int) -> PackedInt32Array:
	var r := PackedInt32Array()
	r.resize(8)
	for vp in 8:
		var f: int = ch_fnum[c]
		if s_vib[s]:
			var rr := (f >> 7) & 7
			if vp & 3 == 0:
				rr = 0
			elif vp & 1:
				rr >>= 1
			rr >>= vib_shift
			if vp & 4:
				rr = -rr
			f += rr
		r[vp] = (((f << ch_block[c]) >> 1) * MULT_X2[s_mult[s]]) >> 1
	return r

func _channel_block(c: int, m: int, kk: int, buf: PackedInt32Array, g_trem: PackedInt32Array, g_vib: PackedInt32Array,
		g_add: PackedInt32Array, g_state: PackedInt32Array, g_lo: PackedInt32Array) -> void:
	var ls := logsin
	var ex := exprom
	var fb: int = ch_fb[c]
	var fbs := 9 - fb
	var cnt: int = ch_cnt[c]
	var ksv: int = ch_ksv[c]
	# the modulator
	var m_inc := _incs(m, c)
	var m_tl: int = (s_tl[m] << 2) + (s_eksl[m] >> KSL_SHIFT[s_ksl[m]])
	var m_am: int = s_am[m]
	var m_ks: int = ksv >> ((s_ksr[m] ^ 1) << 1)
	var m_ar: int = s_ar[m]
	var m_dr: int = s_dr[m]
	var m_rr: int = s_rr[m]
	var m_sl: int = s_sl[m]
	var m_egt: int = s_egt[m]
	var m_wf: int = s_wf[m] if wse else 0
	var m_key: int = s_key[m]
	var m_gen: int = s_gen[m]
	var m_rout: int = s_rout[m]
	var m_ph: int = s_phase[m]
	var m_rst: int = s_reset[m]
	var m_out: int = s_out[m]
	var m_rt := _rates(m, m_ks)
	var m_prout: int = s_prout[m]
	# the carrier
	var k_inc := _incs(kk, c)
	var k_tl: int = (s_tl[kk] << 2) + (s_eksl[kk] >> KSL_SHIFT[s_ksl[kk]])
	var k_am: int = s_am[kk]
	var k_ks: int = ksv >> ((s_ksr[kk] ^ 1) << 1)
	var k_ar: int = s_ar[kk]
	var k_dr: int = s_dr[kk]
	var k_rr: int = s_rr[kk]
	var k_sl: int = s_sl[kk]
	var k_egt: int = s_egt[kk]
	var k_wf: int = s_wf[kk] if wse else 0
	var k_key: int = s_key[kk]
	var k_gen: int = s_gen[kk]
	var k_rout: int = s_rout[kk]
	var k_ph: int = s_phase[kk]
	var k_rst: int = s_reset[kk]
	var k_out: int = s_out[kk]
	var k_rt := _rates(kk, k_ks)
	for i in buf.size():
		var trem: int = g_trem[i]
		var eadd: int = g_add[i]
		var est: int = g_state[i]
		var elo: int = g_lo[i]
		var vp: int = g_vib[i]
		# ---- modulator: feedback
		var fbmod := 0
		if fb != 0:
			fbmod = (m_prout + m_out) >> fbs
		m_prout = m_out
		# ---- modulator: envelope (OPL3_EnvelopeCalc)
		var att: int = m_rout + m_tl + (trem if m_am else 0)
		if att > 0x1ff:
			att = 0x1ff
		var reset := 0
		var ri: int = m_gen
		if m_key and m_gen == EG_RELEASE:
			reset = 1
			ri = 4
		var rhi: int = m_rt[ri]
		var rlo: int = m_rt[ri + 5]
		var sh := 0
		if m_rt[ri + 10] != 0:
			if rhi < 12:
				if est:
					var es: int = rhi + eadd
					if es == 12:
						sh = 1
					elif es == 13:
						sh = (rlo >> 1) & 1
					elif es == 14:
						sh = rlo & 1
			else:
				sh = (rhi & 3) + EG_INCSTEP[rlo][elo]
				if sh & 4:
					sh = 3
				if sh == 0:
					sh = est
		var ro: int = m_rout
		var inc := 0
		var off: bool = (m_rout & 0x1f8) == 0x1f8
		if reset and rhi == 0xf:
			ro = 0
		if m_gen != EG_ATTACK and not reset and off:
			ro = 0x1ff
		if m_gen == EG_ATTACK:
			if m_rout == 0:
				m_gen = EG_DECAY
			elif m_key and sh > 0 and rhi != 0xf:
				inc = (~m_rout) >> (4 - sh)
		elif m_gen == EG_DECAY:
			if (m_rout >> 4) == m_sl:
				m_gen = EG_SUSTAIN
			elif not off and not reset and sh > 0:
				inc = 1 << (sh - 1)
		elif not off and not reset and sh > 0:
			inc = 1 << (sh - 1)
		m_rout = (ro + inc) & 0x1ff
		if reset:
			m_gen = EG_ATTACK
		if not m_key:
			m_gen = EG_RELEASE
		# ---- modulator: phase and output
		var ph: int = ((m_ph >> 9) + fbmod) & 0x3ff
		if reset:
			m_ph = 0
		m_ph = (m_ph + m_inc[vp]) & 0x7ffff
		var lv := 0
		var ng := false
		if m_wf == 0:
			ng = (ph & 0x200) != 0
			lv = ls[(ph & 0xff) ^ 0xff] if ph & 0x100 else ls[ph & 0xff]
		elif m_wf == 1:
			lv = 0x1000 if ph & 0x200 else (ls[(ph & 0xff) ^ 0xff] if ph & 0x100 else ls[ph & 0xff])
		elif m_wf == 2:
			lv = ls[(ph & 0xff) ^ 0xff] if ph & 0x100 else ls[ph & 0xff]
		else:
			lv = 0x1000 if ph & 0x100 else ls[ph & 0xff]
		lv += att << 3
		if lv > 0x1fff:
			lv = 0x1fff
		var v: int = (ex[lv & 0xff] << 1) >> (lv >> 8)
		m_out = ~v if ng else v
		m_rst = reset
		# ---- carrier: envelope
		att = k_rout + k_tl + (trem if k_am else 0)
		if att > 0x1ff:
			att = 0x1ff
		reset = 0
		ri = k_gen
		if k_key and k_gen == EG_RELEASE:
			reset = 1
			ri = 4
		rhi = k_rt[ri]
		rlo = k_rt[ri + 5]
		sh = 0
		if k_rt[ri + 10] != 0:
			if rhi < 12:
				if est:
					var es2: int = rhi + eadd
					if es2 == 12:
						sh = 1
					elif es2 == 13:
						sh = (rlo >> 1) & 1
					elif es2 == 14:
						sh = rlo & 1
			else:
				sh = (rhi & 3) + EG_INCSTEP[rlo][elo]
				if sh & 4:
					sh = 3
				if sh == 0:
					sh = est
		ro = k_rout
		inc = 0
		off = (k_rout & 0x1f8) == 0x1f8
		if reset and rhi == 0xf:
			ro = 0
		if k_gen != EG_ATTACK and not reset and off:
			ro = 0x1ff
		if k_gen == EG_ATTACK:
			if k_rout == 0:
				k_gen = EG_DECAY
			elif k_key and sh > 0 and rhi != 0xf:
				inc = (~k_rout) >> (4 - sh)
		elif k_gen == EG_DECAY:
			if (k_rout >> 4) == k_sl:
				k_gen = EG_SUSTAIN
			elif not off and not reset and sh > 0:
				inc = 1 << (sh - 1)
		elif not off and not reset and sh > 0:
			inc = 1 << (sh - 1)
		k_rout = (ro + inc) & 0x1ff
		if reset:
			k_gen = EG_ATTACK
		if not k_key:
			k_gen = EG_RELEASE
		# ---- carrier: phase (modulated unless the channel adds) and output
		ph = (k_ph >> 9) & 0x3ff
		if cnt == 0:
			ph = (ph + m_out) & 0x3ff
		if reset:
			k_ph = 0
		k_ph = (k_ph + k_inc[vp]) & 0x7ffff
		ng = false
		if k_wf == 0:
			ng = (ph & 0x200) != 0
			lv = ls[(ph & 0xff) ^ 0xff] if ph & 0x100 else ls[ph & 0xff]
		elif k_wf == 1:
			lv = 0x1000 if ph & 0x200 else (ls[(ph & 0xff) ^ 0xff] if ph & 0x100 else ls[ph & 0xff])
		elif k_wf == 2:
			lv = ls[(ph & 0xff) ^ 0xff] if ph & 0x100 else ls[ph & 0xff]
		else:
			lv = 0x1000 if ph & 0x100 else ls[ph & 0xff]
		lv += att << 3
		if lv > 0x1fff:
			lv = 0x1fff
		v = (ex[lv & 0xff] << 1) >> (lv >> 8)
		k_out = ~v if ng else v
		k_rst = reset
		buf[i] += k_out + (m_out if cnt == 1 else 0)
	s_gen[m] = m_gen
	s_rout[m] = m_rout
	s_phase[m] = m_ph
	s_reset[m] = m_rst
	s_out[m] = m_out
	s_prout[m] = m_prout
	s_gen[kk] = k_gen
	s_rout[kk] = k_rout
	s_phase[kk] = k_ph
	s_reset[kk] = k_rst
	s_out[kk] = k_out
	s_prout[kk] = k_out
