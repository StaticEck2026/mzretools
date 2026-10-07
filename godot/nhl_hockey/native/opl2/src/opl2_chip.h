// The YM3812 (OPL2) of the port's sound card as a native class: the same arithmetic as
// audio/Opl2.gd (chip_block), sample by sample at 49716 Hz, for the speed GDScript does not have.
// See audio/Opl2.gd for the description of the chip.
#pragma once

#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/variant/packed_float32_array.hpp>
#include <godot_cpp/variant/packed_int32_array.hpp>

#include <cstdint>

namespace godot {

class Opl2Chip : public RefCounted {
	GDCLASS(Opl2Chip, RefCounted)

public:
	Opl2Chip();

	void set_output_rate(double rate);
	void set_gain(double g);
	void reset();
	void write(int reg, int val);
	PackedFloat32Array render(int n);
	PackedInt32Array chip_samples(int n);
	int active_channels() const;

protected:
	static void _bind_methods();

private:
	struct Slot {
		int am = 0, vib = 0, egt = 0, ksr = 0, mult = 0, ksl = 0, tl = 0;
		int ar = 0, dr = 0, sl = 0, rr = 0, wf = 0;
		int key = 0;
		uint32_t phase = 0;
		int rout = 0x1ff;
		int gen = 3;
		int eksl = 0;
		int out = 0, prout = 0;
		int ch = 0;
	};
	struct Channel {
		int fnum = 0, block = 0, kon = 0, fb = 0, cnt = 0, ksv = 0;
	};

	Slot slots[18];
	Channel channels[9];
	bool wse = false;
	int nts = 0;
	int tremolo_shift = 4;
	int vib_shift = 1;
	uint32_t timer = 0;
	uint64_t eg_timer = 0;
	int eg_state = 0;
	int eg_add = 0;
	int eg_timer_lo = 0;
	int tremolo_pos = 0;
	int tremolo = 0;
	int vib_pos = 0;
	double rate_ratio = 49716.0 / 22050.0;
	double acc = 0.0;
	double gain = 0.2 / 4084.0;

	void update_ksv(int c);
	int envelope(Slot &s, bool &reset);
	int phase_out(Slot &s, const Channel &c, bool reset);
	int sample();
	void timers();
};

} // namespace godot
