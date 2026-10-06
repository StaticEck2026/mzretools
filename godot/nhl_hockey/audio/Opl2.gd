class_name Opl2
extends RefCounted
## A register level model of the Yamaha YM3812 (OPL2) FM chip of the Adlib and Sound Blaster
## cards, the chip the music driver (YM30.BGP / the FM part of SB30.BGP) programs. The driver
## writes registers (write()); render() produces mono samples.
##
## 9 channels of two operators (modulator, carrier). Per operator: 0x20 AM / VIB / EG type / KSR /
## MULT, 0x40 KSL / TL, 0x60 AR / DR, 0x80 SL / RR, 0xE0 waveform. Per channel: 0xA0 / 0xB0 F-number,
## block and key on, 0xC0 feedback / connection. 0x01 bit 5 enables the waveforms, 0xBD bits 7 / 6
## select the tremolo and vibrato depth (the rhythm mode is not used by the game).
##
## The model follows the chip's arithmetic where it matters for the sound: operator outputs of
## +-4084 phase units added to the carrier's 10 bit phase (frequency modulation of up to four
## cycles), feedback (two previous outputs >> (9 - FB)), attenuation in 0.1875 dB steps (envelope
## 0..511, TL << 2, KSL from the F-number table) turned into amplitude as 2^(-att / 32), and the
## documented envelope times (decay 0 -> 96 dB in 39.28 s at rate 4, halving every 4 rates;
## attack 2.83 s at rate 4). The envelope generator runs once per block of EG_BLOCK samples.

const CHIP_RATE := 49716.0
const EG_BLOCK := 16
const MULT_X2 := [1, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 20, 24, 24, 30, 30]
const KSL_ROM := [0, 32, 40, 45, 48, 51, 53, 55, 56, 58, 59, 60, 61, 62, 63, 64]
const KSL_SHIFT := [8, 1, 2, 0]
const SLOT_OF_OFFSET := [0, 2, 4, 1, 3, 5, -1, -1, 6, 8, 10, 7, 9, 11, -1, -1, 12, 14, 16, 13, 15, 17, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1]
const OP_OUT := 4084.0

enum { ST_OFF, ST_ATTACK, ST_DECAY, ST_SUSTAIN, ST_RELEASE }

var sample_rate := 22050.0
var waves: Array = []                 # 4 x PackedFloat32Array(1024)
var amp_table := PackedFloat32Array() # attenuation 0..511 -> amplitude
var wse := false
var am_deep := false
var vib_deep := false
var lfo_time := 0.0
var gain := 0.2

# per operator (slot 2 * channel + 0 modulator / 1 carrier)
var op_am := PackedInt32Array()
var op_vib := PackedInt32Array()
var op_egt := PackedInt32Array()
var op_ksr := PackedInt32Array()
var op_mult := PackedInt32Array()
var op_ksl := PackedInt32Array()
var op_tl := PackedInt32Array()
var op_ar := PackedInt32Array()
var op_dr := PackedInt32Array()
var op_sl := PackedInt32Array()
var op_rr := PackedInt32Array()
var op_ws := PackedInt32Array()
var op_phase := PackedInt32Array()
var op_env := PackedFloat32Array()
var op_stage := PackedInt32Array()
# per channel
var ch_fnum := PackedInt32Array()
var ch_block := PackedInt32Array()
var ch_kon := PackedInt32Array()
var ch_fb := PackedInt32Array()
var ch_cnt := PackedInt32Array()
var ch_fb1 := PackedFloat32Array()
var ch_fb2 := PackedFloat32Array()

func _init(rate: float = 22050.0) -> void:
	sample_rate = rate
	for w in 4:
		var t := PackedFloat32Array()
		t.resize(1024)
		for i in 1024:
			var s := sin(TAU * i / 1024.0)
			match w:
				0: t[i] = s
				1: t[i] = maxf(s, 0.0)
				2: t[i] = absf(s)
				3: t[i] = absf(s) if (i & 0x100) == 0 else 0.0
		waves.append(t)
	amp_table.resize(512)
	for a in 512:
		amp_table[a] = pow(2.0, -a / 32.0) if a < 511 else 0.0
	for arr in [op_am, op_vib, op_egt, op_ksr, op_mult, op_ksl, op_tl, op_ar, op_dr, op_sl, op_rr, op_ws, op_phase, op_stage]:
		arr.resize(18)
	op_env.resize(18)
	op_env.fill(511.0)
	for arr in [ch_fnum, ch_block, ch_kon, ch_fb, ch_cnt]:
		arr.resize(9)
	ch_fb1.resize(9)
	ch_fb2.resize(9)

func reset() -> void:
	for r in range(0x20, 0xf6):
		write(r, 0)
	for s in 18:
		op_env[s] = 511.0
		op_stage[s] = ST_OFF
		op_phase[s] = 0
	wse = false

## a register write of the driver (port 0x388 / 0x389)
func write(reg: int, val: int) -> void:
	reg &= 0xff
	val &= 0xff
	if reg == 0x01:
		wse = (val & 0x20) != 0
		return
	if reg == 0xbd:
		am_deep = (val & 0x80) != 0
		vib_deep = (val & 0x40) != 0
		return
	if reg >= 0xa0 and reg <= 0xa8:
		ch_fnum[reg - 0xa0] = (ch_fnum[reg - 0xa0] & 0x300) | val
		return
	if reg >= 0xb0 and reg <= 0xb8:
		var c := reg - 0xb0
		ch_fnum[c] = (ch_fnum[c] & 0xff) | ((val & 3) << 8)
		ch_block[c] = (val >> 2) & 7
		var kon := (val >> 5) & 1
		if kon != ch_kon[c]:
			ch_kon[c] = kon
			for s in [c * 2, c * 2 + 1]:
				if kon:
					op_stage[s] = ST_ATTACK
					op_phase[s] = 0
				elif op_stage[s] != ST_OFF:
					op_stage[s] = ST_RELEASE
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
			op_am[s] = (val >> 7) & 1
			op_vib[s] = (val >> 6) & 1
			op_egt[s] = (val >> 5) & 1
			op_ksr[s] = (val >> 4) & 1
			op_mult[s] = val & 0xf
		0x40:
			op_ksl[s] = (val >> 6) & 3
			op_tl[s] = val & 0x3f
		0x60:
			op_ar[s] = (val >> 4) & 0xf
			op_dr[s] = val & 0xf
		0x80:
			op_sl[s] = (val >> 4) & 0xf
			op_rr[s] = val & 0xf
		0xe0:
			op_ws[s] = val & 3

## the effective rate 0..63 of a 4 bit rate (key scaling by the octave)
func _rate(s: int, r4: int) -> int:
	if r4 == 0:
		return 0
	var c := s >> 1
	var ksn := (ch_block[c] << 1) | ((ch_fnum[c] >> 9) & 1)
	var rof := ksn if op_ksr[s] else ksn >> 2
	return mini(r4 * 4 + rof, 63)

## attenuation units per second of a decay / release rate
static func decay_speed(r: int) -> float:
	if r < 4:
		return 0.0
	return 13.035 * (1.0 + (r & 3) * 0.25) * pow(2.0, (r >> 2) - 1)

## the attack time constant (1 / s) of a rate
static func attack_lambda(r: int) -> float:
	if r < 4:
		return 0.0
	var t := 2.82624 / ((1.0 + (r & 3) * 0.25) * pow(2.0, (r >> 2) - 1))
	return 4.172 / t

func _eg_step(s: int, dt: float) -> void:
	var st := op_stage[s]
	if st == ST_OFF:
		return
	var env := op_env[s]
	if st == ST_ATTACK:
		var r := _rate(s, op_ar[s])
		if r >= 60:
			env = 0.0
		elif r > 0:
			env = (env + 8.0) * exp(-attack_lambda(r) * dt) - 8.0
		if env <= 0.0:
			env = 0.0
			st = ST_DECAY
	elif st == ST_DECAY:
		var sl := 496.0 if op_sl[s] == 15 else op_sl[s] * 16.0
		env += decay_speed(_rate(s, op_dr[s])) * dt
		if env >= sl:
			env = sl
			st = ST_SUSTAIN
	elif st == ST_SUSTAIN:
		if op_egt[s] == 0:
			env += decay_speed(_rate(s, op_rr[s])) * dt
	else:
		env += decay_speed(_rate(s, op_rr[s])) * dt
	if env >= 511.0:
		env = 511.0
		if st != ST_ATTACK:
			st = ST_OFF
	op_env[s] = env
	op_stage[s] = st

## the total attenuation (envelope, total level, key scale level, tremolo) as amplitude
func _amplitude(s: int, am_units: float) -> float:
	var c := s >> 1
	var ksl: int = (KSL_ROM[ch_fnum[c] >> 6] << 2) - ((8 - ch_block[c]) << 5)
	if ksl < 0:
		ksl = 0
	var att: float = op_env[s] + (op_tl[s] << 2) + (ksl >> KSL_SHIFT[op_ksl[s]])
	if op_am[s]:
		att += am_units
	if att >= 511.0:
		return 0.0
	return amp_table[int(att)]

func active_channels() -> int:
	var n := 0
	for c in 9:
		if op_stage[c * 2 + 1] != ST_OFF or (ch_cnt[c] == 1 and op_stage[c * 2] != ST_OFF):
			n += 1
	return n

## renders n mono samples (-1..1), added to out from offset
func render(out: PackedFloat32Array, offset: int, n: int) -> void:
	var done := 0
	var dt := EG_BLOCK / sample_rate
	while done < n:
		var len := mini(EG_BLOCK, n - done)
		lfo_time += len / sample_rate
		var am_units := (5.33 if not am_deep else 25.6) * (0.5 + 0.5 * sin(TAU * 3.7 * lfo_time))
		var vib := (0.00405 if not vib_deep else 0.0081) * sin(TAU * 6.07 * lfo_time)
		for c in 9:
			var sm := c * 2
			var sc := sm + 1
			_eg_step(sm, dt * len / EG_BLOCK)
			_eg_step(sc, dt * len / EG_BLOCK)
			var car_on := op_stage[sc] != ST_OFF
			var mod_on := op_stage[sm] != ST_OFF
			if not car_on and not (ch_cnt[c] == 1 and mod_on):
				continue
			var am_m := _amplitude(sm, am_units) if mod_on else 0.0
			var am_c := _amplitude(sc, am_units) if car_on else 0.0
			if am_m == 0.0 and am_c == 0.0:
				continue
			var base := float(ch_fnum[c] << ch_block[c]) * CHIP_RATE / sample_rate * 0.5
			var inc_m := int(base * MULT_X2[op_mult[sm]] * (1.0 + vib if op_vib[sm] else 1.0))
			var inc_c := int(base * MULT_X2[op_mult[sc]] * (1.0 + vib if op_vib[sc] else 1.0))
			var wm: PackedFloat32Array = waves[op_ws[sm] if wse else 0]
			var wc: PackedFloat32Array = waves[op_ws[sc] if wse else 0]
			var fbk := 0.0 if ch_fb[c] == 0 else OP_OUT / float(1 << (9 - ch_fb[c]))
			var pm := op_phase[sm]
			var pc := op_phase[sc]
			var f1 := ch_fb1[c]
			var f2 := ch_fb2[c]
			var additive := ch_cnt[c] == 1
			var mod_k := am_m * OP_OUT
			var p := offset + done
			for i in len:
				pm += inc_m
				var om := wm[((pm >> 10) + int((f1 + f2) * fbk)) & 1023]
				f2 = f1
				f1 = om * am_m
				pc += inc_c
				if additive:
					out[p + i] += (wc[(pc >> 10) & 1023] * am_c + f1) * gain
				else:
					out[p + i] += wc[((pc >> 10) + int(om * mod_k)) & 1023] * am_c * gain
			op_phase[sm] = pm & 0x3fffffff
			op_phase[sc] = pc & 0x3fffffff
			ch_fb1[c] = f1
			ch_fb2[c] = f2
		done += len
