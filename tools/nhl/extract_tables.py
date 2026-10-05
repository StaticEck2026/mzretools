#!/usr/bin/env python3
#
# Extracts the static simulation tables of HOCKEY.EXE into a JSON file for the Godot port.
# The tables and their meaning are documented in re/nhl_hockey/STRUCTURES.md.
#
#   extract_tables.py HOCKEY.EXE tables.json
#
import json
import os
import struct
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from le import LEExecutable  # noqa: E402

def cstr(le, addr, maxlen=64):
    out = bytearray()
    while len(out) < maxlen:
        b = le.read(addr + len(out), 1)
        if not b or b == b'\0':
            break
        out += b
    return out.decode('latin-1')

def shorts(le, addr, n):
    return list(struct.unpack('<%dh' % n, le.read(addr, n * 2)))

def main():
    exe, out = sys.argv[1], sys.argv[2]
    le = LEExecutable(exe)
    le.apply_fixups()
    t = {}
    # animation sequences: an animation id is a word offset into this table; entry[0..7] are per
    # direction word offsets to a list of (frame, duration) pairs starting at entry + 8 words; a
    # negative duration marks the last frame, bit 15 of entry[0] means the animation loops
    t['anim_sequences_base'] = 0xc921d
    t['anim_sequences'] = shorts(le, 0xc921d, 10777 // 2)
    t['dir8_vectors'] = [shorts(le, 0xc90e0 + i * 4, 2) for i in range(8)]
    t['frame_offsets'] = [list(struct.unpack('<2b', le.read(0xcc148 + i * 2, 2))) for i in range(0x2db)]
    t['shot_targets'] = shorts(le, 0xccc60, 16)
    t['position_default_state'] = list(le.read(0xccc9e, 8))
    t['dir8_lut'] = list(le.read(0xd2c74, 16))
    t['infraction_priority'] = list(struct.unpack('<31i', le.read(0xcd39c, 124)))
    t['infraction_is_penalty'] = list(le.read(0xc9123, 31))
    t['stoppage_duration'] = list(le.read(0xc9104, 13))
    t['net_y'] = shorts(le, 0xcd2f8, 6)
    # apply_skating: heading change per step for (dir - facing) & 7; skating_accelerate: squared speed
    # limit per energy level
    t['turn_table'] = list(struct.unpack('<8i', le.read(0xccd78, 32)))
    t['max_speed_sq'] = list(struct.unpack('<16i', le.read(0xccd98, 64)))
    t['ai_state_names'] = [cstr(le, le.read_u32(0xcd8c0 + i * 4)) for i in range(50)]
    t['ai_state_handlers'] = ['0x%x' % le.read_u32(0xc9161 + i * 4) for i in range(47)]
    t['team_abbrev'] = [cstr(le, le.read_u32(0xc5439 + i * 4)) for i in range(28)]
    t['message_strings'] = [cstr(le, le.read_u32(0xcd4dc + i * 4), 80) for i in range(7)]
    t['star_names'] = [cstr(le, le.read_u32(0xcca0a + i * 4)) for i in range(3)]
    t['announcer_ppv_names'] = [cstr(le, le.read_u32(0xcbed0 + i * 4)) for i in range(11)]
    # team names and cities (table of 0xba byte records is runtime data; the fixed list of full
    # names follows the abbreviations in the data object)
    names = []
    a = 0xc04d0
    while len(names) < 56:
        s = cstr(le, a)
        if not s:
            break
        names.append(s)
        a += len(s) + 1
    t['team_strings'] = names
    with open(out, 'w') as f:
        json.dump(t, f, indent=1)
    print(f"wrote {out}: {len(t['anim_sequences'])} animation words, {len(t['ai_state_names'])} states")

if __name__ == '__main__':
    main()
