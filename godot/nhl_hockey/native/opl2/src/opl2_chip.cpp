// The YM3812 (OPL2) as a native class; the arithmetic of audio/Opl2.gd (see there).
#include "opl2_chip.h"

#include <godot_cpp/core/class_db.hpp>

#include <cmath>

using namespace godot;

namespace {

const int MULT_X2[16] = { 1, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 20, 24, 24, 30, 30 };
const int KSL_ROM[16] = { 0, 32, 40, 45, 48, 51, 53, 55, 56, 58, 59, 60, 61, 62, 63, 64 };
const int KSL_SHIFT[4] = { 8, 1, 2, 0 };
const int EG_INCSTEP[4][4] = { { 0, 0, 0, 0 }, { 1, 0, 0, 0 }, { 1, 0, 1, 0 }, { 1, 1, 1, 0 } };
const int SLOT_OF_OFFSET[32] = { 0, 1, 2, 3, 4, 5, -1, -1, 6, 7, 8, 9, 10, 11, -1, -1, 12, 13, 14, 15, 16, 17,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
const int CH_MOD[9] = { 0, 1, 2, 6, 7, 8, 12, 13, 14 };
enum { EG_ATTACK, EG_DECAY, EG_SUSTAIN, EG_RELEASE };

int logsin[256];
int exprom[256];
bool tables_ready = false;

void make_tables() {
	if (tables_ready) {
		return;
	}
	for (int i = 0; i < 256; i++) {
		logsin[i] = (int)std::lround(-std::log2(std::sin((i + 0.5) * M_PI / 512.0)) * 256.0);
		exprom[i] = (int)std::lround(std::pow(2.0, (255 - i) / 256.0) * 1024.0);
	}
	tables_ready = true;
}

inline int op_out(int wf, int ph, int att) {
	ph &= 0x3ff;
	int lv = 0;
	bool neg = false;
	switch (wf) {
		case 0:
			neg = (ph & 0x200) != 0;
			lv = (ph & 0x100) ? logsin[(ph & 0xff) ^ 0xff] : logsin[ph & 0xff];
			break;
		case 1:
			lv = (ph & 0x200) ? 0x1000 : ((ph & 0x100) ? logsin[(ph & 0xff) ^ 0xff] : logsin[ph & 0xff]);
			break;
		case 2:
			lv = (ph & 0x100) ? logsin[(ph & 0xff) ^ 0xff] : logsin[ph & 0xff];
			break;
		default:
			lv = (ph & 0x100) ? 0x1000 : logsin[ph & 0xff];
			break;
	}
	lv += att << 3;
	if (lv > 0x1fff) {
		lv = 0x1fff;
	}
	int v = (exprom[lv & 0xff] << 1) >> (lv >> 8);
	return neg ? ~v : v;
}

inline int dac(int x) {
	int a = x < 0 ? -x : x;
	int shift = 0;
	while (shift < 6 && (a >> shift) > 0x1ff) {
		shift++;
	}
	return (x >> shift) << shift;
}

} // namespace

Opl2Chip::Opl2Chip() {
	make_tables();
	for (int c = 0; c < 9; c++) {
		slots[CH_MOD[c]].ch = c;
		slots[CH_MOD[c] + 3].ch = c;
	}
	reset();
}

void Opl2Chip::set_output_rate(double rate) {
	rate_ratio = 49716.0 / rate;
}

void Opl2Chip::set_gain(double g) {
	gain = g;
}

void Opl2Chip::reset() {
	for (int s = 0; s < 18; s++) {
		int ch = slots[s].ch;
		slots[s] = Slot();
		slots[s].ch = ch;
	}
	for (int c = 0; c < 9; c++) {
		channels[c] = Channel();
	}
	wse = false;
	nts = 0;
	tremolo_shift = 4;
	vib_shift = 1;
}

void Opl2Chip::update_ksv(int c) {
	Channel &ch = channels[c];
	ch.ksv = (ch.block << 1) | ((ch.fnum >> (9 - nts)) & 1);
	int ksl = (KSL_ROM[ch.fnum >> 6] << 2) - ((8 - ch.block) << 5);
	if (ksl < 0) {
		ksl = 0;
	}
	slots[CH_MOD[c]].eksl = ksl;
	slots[CH_MOD[c] + 3].eksl = ksl;
}

void Opl2Chip::write(int reg, int val) {
	reg &= 0xff;
	val &= 0xff;
	if (reg == 0x01) {
		wse = (val & 0x20) != 0;
		return;
	}
	if (reg == 0x08) {
		nts = (val >> 6) & 1;
		for (int c = 0; c < 9; c++) {
			update_ksv(c);
		}
		return;
	}
	if (reg == 0xbd) {
		tremolo_shift = (((val >> 7) ^ 1) << 1) + 2;
		vib_shift = ((val >> 6) & 1) ^ 1;
		return;
	}
	if (reg >= 0xa0 && reg <= 0xa8) {
		Channel &ch = channels[reg - 0xa0];
		ch.fnum = (ch.fnum & 0x300) | val;
		update_ksv(reg - 0xa0);
		return;
	}
	if (reg >= 0xb0 && reg <= 0xb8) {
		int c = reg - 0xb0;
		Channel &ch = channels[c];
		ch.fnum = (ch.fnum & 0xff) | ((val & 3) << 8);
		ch.block = (val >> 2) & 7;
		update_ksv(c);
		int kon = (val >> 5) & 1;
		if (kon != ch.kon) {
			ch.kon = kon;
			slots[CH_MOD[c]].key = kon;
			slots[CH_MOD[c] + 3].key = kon;
		}
		return;
	}
	if (reg >= 0xc0 && reg <= 0xc8) {
		channels[reg - 0xc0].fb = (val >> 1) & 7;
		channels[reg - 0xc0].cnt = val & 1;
		return;
	}
	int group = reg & 0xe0;
	if (group < 0x20 || (group > 0x80 && group != 0xe0)) {
		return;
	}
	int si = SLOT_OF_OFFSET[reg & 0x1f];
	if (si < 0) {
		return;
	}
	Slot &s = slots[si];
	switch (group) {
		case 0x20:
			s.am = (val >> 7) & 1;
			s.vib = (val >> 6) & 1;
			s.egt = (val >> 5) & 1;
			s.ksr = (val >> 4) & 1;
			s.mult = val & 0xf;
			break;
		case 0x40:
			s.ksl = (val >> 6) & 3;
			s.tl = val & 0x3f;
			break;
		case 0x60:
			s.ar = (val >> 4) & 0xf;
			s.dr = val & 0xf;
			break;
		case 0x80:
			s.sl = (val >> 4) & 0xf;
			if (s.sl == 0xf) {
				s.sl = 0x1f;
			}
			s.rr = val & 0xf;
			break;
		case 0xe0:
			s.wf = val & 3;
			break;
	}
}

int Opl2Chip::active_channels() const {
	int n = 0;
	for (int c = 0; c < 9; c++) {
		const Slot &m = slots[CH_MOD[c]];
		const Slot &k = slots[CH_MOD[c] + 3];
		if (k.rout < 0x1ff || k.key || (channels[c].cnt == 1 && (m.rout < 0x1ff || m.key))) {
			n++;
		}
	}
	return n;
}

// OPL3_EnvelopeCalc: the attenuation of this sample; the envelope moves on
int Opl2Chip::envelope(Slot &s, bool &reset) {
	int out = s.rout + (s.tl << 2) + (s.eksl >> KSL_SHIFT[s.ksl]) + (s.am ? tremolo : 0);
	if (out > 0x1ff) {
		out = 0x1ff;
	}
	reset = false;
	int reg_rate = 0;
	if (s.key && s.gen == EG_RELEASE) {
		reset = true;
		reg_rate = s.ar;
	} else {
		switch (s.gen) {
			case EG_ATTACK:
				reg_rate = s.ar;
				break;
			case EG_DECAY:
				reg_rate = s.dr;
				break;
			case EG_SUSTAIN:
				if (!s.egt) {
					reg_rate = s.rr;
				}
				break;
			default:
				reg_rate = s.rr;
				break;
		}
	}
	int ks = channels[s.ch].ksv >> ((s.ksr ^ 1) << 1);
	int rate = ks + (reg_rate << 2);
	int rate_hi = rate >> 2;
	int rate_lo = rate & 3;
	if (rate_hi & 0x10) {
		rate_hi = 0xf;
	}
	int eg_shift = rate_hi + eg_add;
	int shift = 0;
	if (reg_rate != 0) {
		if (rate_hi < 12) {
			if (eg_state) {
				switch (eg_shift) {
					case 12:
						shift = 1;
						break;
					case 13:
						shift = (rate_lo >> 1) & 1;
						break;
					case 14:
						shift = rate_lo & 1;
						break;
				}
			}
		} else {
			shift = (rate_hi & 3) + EG_INCSTEP[rate_lo][eg_timer_lo];
			if (shift & 4) {
				shift = 3;
			}
			if (!shift) {
				shift = eg_state;
			}
		}
	}
	int rout = s.rout;
	int inc = 0;
	bool off = (s.rout & 0x1f8) == 0x1f8;
	if (reset && rate_hi == 0xf) {
		rout = 0;
	}
	if (s.gen != EG_ATTACK && !reset && off) {
		rout = 0x1ff;
	}
	switch (s.gen) {
		case EG_ATTACK:
			if (s.rout == 0) {
				s.gen = EG_DECAY;
			} else if (s.key && shift > 0 && rate_hi != 0xf) {
				inc = (~s.rout) >> (4 - shift);
			}
			break;
		case EG_DECAY:
			if ((s.rout >> 4) == s.sl) {
				s.gen = EG_SUSTAIN;
			} else if (!off && !reset && shift > 0) {
				inc = 1 << (shift - 1);
			}
			break;
		default:
			if (!off && !reset && shift > 0) {
				inc = 1 << (shift - 1);
			}
			break;
	}
	s.rout = (rout + inc) & 0x1ff;
	if (reset) {
		s.gen = EG_ATTACK;
	}
	if (!s.key) {
		s.gen = EG_RELEASE;
	}
	return out;
}

// OPL3_PhaseGenerate: the 10 bit phase of the previous sample; the accumulator moves on
int Opl2Chip::phase_out(Slot &s, const Channel &c, bool reset) {
	int f = c.fnum;
	if (s.vib) {
		int r = (f >> 7) & 7;
		if (!(vib_pos & 3)) {
			r = 0;
		} else if (vib_pos & 1) {
			r >>= 1;
		}
		r >>= vib_shift;
		if (vib_pos & 4) {
			r = -r;
		}
		f += r;
	}
	uint32_t basefreq = (uint32_t)((f << c.block) >> 1);
	int phase = (int)((s.phase >> 9) & 0x3ff);
	if (reset) {
		s.phase = 0;
	}
	s.phase = (s.phase + ((basefreq * MULT_X2[s.mult]) >> 1)) & 0x7ffff;
	return phase;
}

void Opl2Chip::timers() {
	if ((timer & 0x3f) == 0x3f) {
		tremolo_pos = (tremolo_pos + 1) % 210;
	}
	tremolo = (tremolo_pos < 105 ? tremolo_pos : 210 - tremolo_pos) >> tremolo_shift;
	if ((timer & 0x3ff) == 0x3ff) {
		vib_pos = (vib_pos + 1) & 7;
	}
	timer++;
	if (eg_state) {
		int shift = 0;
		while (shift < 13 && ((eg_timer >> shift) & 1) == 0) {
			shift++;
		}
		eg_add = shift > 12 ? 0 : shift + 1;
		eg_timer_lo = (int)(eg_timer & 3);
		eg_timer = (eg_timer + 1) & 0xfffffffffULL;
	}
	eg_state ^= 1;
}

int Opl2Chip::sample() {
	int mix = 0;
	for (int c = 0; c < 9; c++) {
		Slot &m = slots[CH_MOD[c]];
		Slot &k = slots[CH_MOD[c] + 3];
		const Channel &ch = channels[c];
		if (!m.key && !k.key && m.rout == 0x1ff && k.rout == 0x1ff) {
			m.out = m.prout = k.out = 0;
			continue;
		}
		int fbmod = ch.fb ? (m.prout + m.out) >> (9 - ch.fb) : 0;
		m.prout = m.out;
		bool reset;
		int att = envelope(m, reset);
		int ph = phase_out(m, ch, reset);
		m.out = op_out(wse ? m.wf : 0, ph + fbmod, att);
		att = envelope(k, reset);
		ph = phase_out(k, ch, reset);
		if (ch.cnt == 0) {
			k.out = op_out(wse ? k.wf : 0, ph + m.out, att);
			mix += k.out;
		} else {
			k.out = op_out(wse ? k.wf : 0, ph, att);
			mix += k.out + m.out;
		}
	}
	timers();
	if (mix > 32767) {
		mix = 32767;
	} else if (mix < -32768) {
		mix = -32768;
	}
	return mix;
}

PackedInt32Array Opl2Chip::chip_samples(int n) {
	PackedInt32Array out;
	out.resize(n);
	for (int i = 0; i < n; i++) {
		out.set(i, sample());
	}
	return out;
}

PackedFloat32Array Opl2Chip::render(int n) {
	PackedFloat32Array out;
	out.resize(n);
	float *w = out.ptrw();
	for (int i = 0; i < n; i++) {
		acc += rate_ratio;
		int k = (int)acc;
		acc -= k;
		int sum = 0;
		for (int j = 0; j < k; j++) {
			sum += dac(sample());
		}
		w[i] = (float)((double)sum / (k > 0 ? k : 1) * gain);
	}
	return out;
}

void Opl2Chip::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_output_rate", "rate"), &Opl2Chip::set_output_rate);
	ClassDB::bind_method(D_METHOD("set_gain", "gain"), &Opl2Chip::set_gain);
	ClassDB::bind_method(D_METHOD("reset"), &Opl2Chip::reset);
	ClassDB::bind_method(D_METHOD("write", "reg", "val"), &Opl2Chip::write);
	ClassDB::bind_method(D_METHOD("render", "n"), &Opl2Chip::render);
	ClassDB::bind_method(D_METHOD("chip_samples", "n"), &Opl2Chip::chip_samples);
	ClassDB::bind_method(D_METHOD("active_channels"), &Opl2Chip::active_channels);
}
