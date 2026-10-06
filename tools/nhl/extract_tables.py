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
    # do_shot: aim point per pending_dir as (x, z) pairs; the y is the goal line (+-0xe8)
    t['shot_targets'] = shorts(le, 0xccc60, 16)
    # set_default_state: AI state per line_slot (0 goalie .. 6)
    t['position_default_state'] = list(le.read(0xccca1, 7))
    t['dir8_lut'] = list(le.read(0xd2c74, 16))
    t['infraction_priority'] = list(struct.unpack('<31i', le.read(0xcd39c, 124)))
    t['infraction_is_penalty'] = list(struct.unpack('<31b', le.read(0xc9123, 31)))
    # process_infractions: stoppage length (<< 5 steps) and announcement delay per infraction
    t['stoppage_duration'] = list(le.read(0xc9104, 31))
    t['announce_delay'] = list(le.read(0xc9142, 31))
    t['net_y'] = shorts(le, 0xcd2f8, 6)
    # entity init table (17 records): x, y, vx, frame, side, half_w, half_h, state, flags
    t['entity_init'] = [shorts(le, 0xcbd5a + i * 18, 7) + [le.read(0xcbd5a + i * 18 + 14, 1)[0], le.read(0xcbd5a + i * 18 + 16, 1)[0]] for i in range(17)]
    # faceoff: positions relative to the faceoff spot (x, y) and the lineup table
    # lineup[6 - skaters_on_ice][line_slot] -> position index (ai_all_goto_faceoff, ai_puck_faceoff2)
    t['faceoff_spots'] = [shorts(le, 0xcbe8c + i * 4, 2) for i in range(7)]
    t['faceoff_lineup'] = [list(struct.unpack('<8b', le.read(0xcbea8 + i * 8, 8))) for i in range(3)]
    # faceoff_resolve: bonus per centre readiness (ai_faceoff writes 1..6 into word_e038e/e0394)
    t['faceoff_bonus'] = list(struct.unpack('<7b', le.read(0xcca95, 7)))
    # stick position per frame (stick_offsets_lookup): frames 0x196..0x219 (and 0x3ce..0x44f - 0x1b4)
    t['stick_offsets'] = [list(struct.unpack('<2b', le.read(0xcc7a4 + i * 2, 2))) for i in range(0x219 - 0x196 + 1)]
    # one timer stick position per facing (sub_50b55)
    t['onetimer_offsets'] = [list(struct.unpack('<2b', le.read(0xccbba + i * 2, 2))) for i in range(8)]
    # ai_puck_carrier: skating targets (x, y) for the attacking team, index want_dir + 6 (0..9) or
    # line_slot - 1 with the goalie pulled
    t['carrier_targets'] = [shorts(le, 0xcca6e + i * 4, 2) for i in range(10)]
    # ai_wing_offense / ai_center_offense: zones [x, dx, y, dy] per phase (0, 4, 8, 12)
    t['wing_zones'] = [shorts(le, 0xcca18 + i * 8, 4) for i in range(4)]
    t['center_zones'] = [shorts(le, 0xcca38 + i * 8, 4) for i in range(4)]
    # ai_goalie: save animation per direction class (dword_cca58 + 2)
    t['goalie_save_anims'] = shorts(le, 0xcca5a, 10)
    # start_poke_check: velocity vectors per facing
    t['poke_vectors'] = [shorts(le, 0xccc30 + i * 4, 2) for i in range(8)]
    # ai_breakaway: waypoints (x, y, trigger y)
    t['breakaway_waypoints'] = [list(struct.unpack('<3i', le.read(0xccb18 + i * 12, 12))) for i in range(4)]
    # referee: signal direction and animation per infraction (ai_ref_call_penalty)
    t['ref_signal_dir'] = shorts(le, 0xcca9c, 32)
    t['ref_signal_anim'] = shorts(le, 0xccad8, 32)
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
    # load_rink: per team the .TIL/.MAP file name and the tile column/row of the centre ice logo;
    # a second (mirrored, 0x6000) copy is placed at [2], [3] when they are >= 0 (12 byte records)
    t['rink_tile_names'] = [cstr(le, 0xc7298 + i * 12, 4) for i in range(26)]
    t['rink_logo'] = [shorts(le, 0xc7298 + 4 + i * 12, 4) for i in range(26)]
    # draw_sprites: marker frames drawn under the user 1 / user 2 / puck carrier player
    t['marker_frames'] = shorts(le, 0xcc0b2, 3)
    # draw_sprites: off screen arrows per clip direction for user 1 and user 2
    t['arrow_frames'] = [shorts(le, 0xcc0b8 + i * 16, 8) for i in range(2)]
    with open(out, 'w') as f:
        json.dump(t, f, indent=1)
    print(f"wrote {out}: {len(t['anim_sequences'])} animation words, {len(t['ai_state_names'])} states")

if __name__ == '__main__':
    main()
