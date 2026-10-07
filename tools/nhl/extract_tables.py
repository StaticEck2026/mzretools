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

def menu_items(le, exe):
    """the menu bars and pull-down lists of the front end (draw_menu_items, draw_menu, run_menu,
    hit_test_menus): 32 byte records x0, y0, x1, y1, text, callback, sub list, sub count. Every record
    of the data object is returned by its address; the callback as the routine name of hockey.json
    when it is next to the executable. The code addresses menus as (first record, count)."""
    names = {}
    j = os.path.join(os.path.dirname(os.path.abspath(exe)), 'hockey.json')
    if os.path.exists(j):
        names = {r['addr']: r['name'] for r in json.load(open(j))['routines']}
    lo, hi = 0xc0000, 0xd8000
    data = le.read(lo, hi - lo)

    def text(a):
        b = le.read(a, 90) or b''
        s = b.split(b'\0')[0]
        return s.decode('latin-1') if len(s) <= 80 else None

    def item(a):
        x0, y0, x1, y1, txt, cb, sub, n = struct.unpack_from('<8i', data, a - lo)
        if not (0 <= x0 <= 640 and 0 <= y0 <= 480 and 0 <= x1 <= 640 and 0 <= y1 <= 480 and y1 > y0):
            return None
        if not lo <= txt < hi or text(txt) is None or not 0 <= n < 64:
            return None
        if (cb and cb not in names and names) or (sub and not lo <= sub < hi) or (sub and n == 0):
            return None
        return [x0, y0, x1, y1, text(txt), names.get(cb, '0x%x' % cb) if cb else '', '%x' % sub if sub else '', n]
    out = {}
    for a in range(lo, hi - 32):
        it = item(a)
        if it is not None:
            out['%x' % a] = it
    return out

def main():
    exe, out = sys.argv[1], sys.argv[2]
    le = LEExecutable(exe)
    le.apply_fixups()
    t = {}
    # animation sequences: an animation id is a word offset into this table; entry[0..7] are per
    # direction word offsets to a list of (frame, duration) pairs starting at entry + 8 words; a
    # negative duration marks the last frame, bit 15 of entry[0] means the animation loops
    t['anim_sequences_base'] = 0xc921d
    t['anim_sequences'] = shorts(le, 0xc921d, 10778 // 2)     # the last duration (of a referee signal) ends at 0xcbc36
    t['dir8_vectors'] = [shorts(le, 0xc90e0 + i * 4, 2) for i in range(8)]
    # frame_offsets_lookup: frames 0..0x283, 0x378..0x3cd (- 0xf4) and 0x3ce..0x467 (- 0x13a), 814 pairs
    # up to stick_offsets
    t['frame_offsets'] = [list(struct.unpack('<2b', le.read(0xcc148 + i * 2, 2))) for i in range(0x32e)]
    # do_shot: aim point per pending_dir as (x, z) pairs; the y is the goal line (+-0xe8)
    t['shot_targets'] = shorts(le, 0xccc60, 18)          # 9 aim points (x, height): 8 directions and the middle
    # set_default_state: AI state per line_slot (0 goalie .. 6)
    t['position_default_state'] = list(le.read(0xccca1, 7))
    t['dir8_lut'] = list(le.read(0xd2c74, 16))
    # vector_octant: the angle (0x80 = 45 degrees) of the ratio i / 256; sin_lookup / cos_lookup: the
    # 16.16 quarter sine (257 values, 0x100 = 90 degrees)
    t['atan_table'] = list(le.read(0xd6074, 257))
    t['sine_table'] = list(struct.unpack('<257i', le.read(0xd6178, 257 * 4)))
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
    # stick position per frame (stick_offsets_lookup): frames 0x196..0x219 and 0x3ce..0x44f (- 0x1b4)
    t['stick_offsets'] = [list(struct.unpack('<2b', le.read(0xcc7a4 + i * 2, 2))) for i in range(0x44f - 0x1b4 - 0x196 + 1)]
    # one timer stick position per facing (one_timer_step)
    t['onetimer_offsets'] = [list(struct.unpack('<2b', le.read(0xccbba + i * 2, 2))) for i in range(8)]
    # ai_puck_carrier: skating targets (x, y) for the attacking team, index want_dir + 6 (0..9) or
    # line_slot - 1 with the goalie pulled
    t['carrier_targets'] = [shorts(le, 0xcca6e + i * 4, 2) for i in range(10)]
    # ai_wing_offense / ai_center_offense: zones [x, dx, y, dy] per phase (0, 4, 8, 12)
    t['wing_zones'] = [shorts(le, 0xcca18 + i * 8, 4) for i in range(4)]
    t['center_zones'] = [shorts(le, 0xcca38 + i * 8, 4) for i in range(4)]
    # ai_goalie: save animation per direction class (0xcca5a, the table after scorer_jumps)
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
    t['message_strings'] = [cstr(le, le.read_u32(0xcd4dc + i * 4), 80) for i in range(8)]
    # resolve_body_check: the checker's follow-through animation per direction of the victim
    t['check_anims'] = shorts(le, 0xccc50, 8)
    # knock_down / knockdown_position: positions against the boards per facing (x for the side
    # boards at +0xccbcc right / +0xccbdc left and +0xccc0c / +0xccc1c alternates, y for the end
    # boards at +0xccbec top / +0xccbfc bottom)
    t['knockdown_right_x'] = shorts(le, 0xccbcc, 8)
    t['knockdown_left_x'] = shorts(le, 0xccbdc, 8)
    t['knockdown_top_y'] = shorts(le, 0xccbec, 8)
    t['knockdown_bottom_y'] = shorts(le, 0xccbfc, 8)
    t['knockdown_right2_x'] = shorts(le, 0xccc0c, 8)
    t['knockdown_left2_x'] = shorts(le, 0xccc1c, 8)
    # init_match / ai_anthem: national anthem per home team (0 Canada, 1 USA), its length in steps
    # per country and the idle animations of the players standing on the blue line
    t['anthem_country'] = list(le.read(0xcc9b0, 28))
    t['anthem_length'] = shorts(le, 0xcc9cc, 2)
    t['anthem_fidgets'] = shorts(le, 0xcc9d0, 5)
    # compute_three_stars: shots a goalie must face for a shutout star / a save percentage star,
    # per period length setting (option_flags bits 10-11)
    t['star_shutout_shots'] = list(le.read(0xcc9e4, 3))
    t['star_save_shots'] = list(le.read(0xcc9e7, 3))
    # ai_three_stars: the lap of honour, 4 points per team (home, away)
    t['star_laps'] = [[shorts(le, 0xcc9ea + team * 16 + k * 4, 2) for k in range(4)] for team in range(2)]
    # load_cutscene_clip / update_announcer: the scoreboard clips (announcer_ppv_names): the frame
    # script (count, then frame indices), the steps per frame and whether the panel closes after it
    t['clip_scripts'] = []
    for i in range(11):
        sp = le.read_u32(0xcc01d + i * 4)
        n = le.read(sp, 1)[0]
        t['clip_scripts'].append(list(le.read(sp, n + 1)))
    t['clip_frame_steps'] = [shorts(le, 0xcc054 + i * 4, 1)[0] for i in range(11)]
    t['clip_closes'] = list(le.read(0xcc049, 11))
    # show_penalty: the penalty names of the panel (off_cd304[type - 9])
    t['penalty_names'] = [cstr(le, le.read_u32(0xcd304 + i * 4)) for i in range(18)]
    t['star_names'] = [cstr(le, le.read_u32(0xcca0a + i * 4)) for i in range(3)]
    t['announcer_ppv_names'] = [cstr(le, le.read_u32(0xcbed0 + i * 4)) for i in range(11)]
    # draw_nets_and_effects / update_effects: the animated crowd figures and the benches. Per
    # figure (aGgG + 2) the position on the rink surface and the offset of its frame sequence in
    # unk_cce00 ([n, frame, ...], n < 0: the last frames repeat at random); frames of F000_149.PPV
    t['crowd_spots'] = [shorts(le, 0xccef8 + i * 6, 3) for i in range(0xab)]
    t['crowd_sequences'] = list(struct.unpack('<248b', le.read(0xcce00, 248)))   # runs into 'ggG' (aGgG is data)
    t['bench_y'] = [shorts(le, 0xcd2f8 + i * 4 + 2, 1)[0] for i in range(2)]
    # load_music_banks / play_speech: the organ songs (KMS) of the match. music_team_songs: per home
    # team (> 25 uses row 13) the song of the cues 0..5 (-1 none: a random one), music_pool the
    # candidates of the three random songs (cues 6..8), anthem_songs per anthem_country
    t['music_songs'] = [cstr(le, le.read_u32(0xd1b0b + i * 4)) for i in range(54)]
    t['music_team_songs'] = [list(struct.unpack('<6b', le.read(0xd1be3 + 6 * i, 6))) for i in range(26)]
    t['music_pool'] = list(struct.unpack('<18i', le.read(0xd1c8b, 72)))
    t['anthem_songs'] = [cstr(le, le.read_u32(0xd1cde + i * 4)) for i in range(2)]
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
    # line changes (assign_line_positions, choose_line, pick_next_line):
    # lineup_slot_types[mode][k]: position type of the k-th player of the lineup (mode 0 with a
    # goalie: G LD RD C LW RW, mode 1 goalie pulled: LD RD C LW RW extra attacker)
    t['lineup_slot_types'] = [list(le.read(0xcbc37 + i, 6)) for i in range(2)]
    # line_table_lists: per position type the preference list of line table offsets (TEAMS.DB +0xbc)
    # indexed by line 0..7 first, then the other positions, -1 terminated
    bases = struct.unpack('<8h', le.read(0xcccb8, 16))[1:]
    lists = []
    for b in bases:
        l = []
        a = 0xcccc8 + b
        while True:
            v = le.read(a, 1)[0]
            if v == 0xff or len(l) > 40:
                break
            l.append(v)
            a += 1
        lists.append(l)
    t['line_table_lists'] = lists
    # the same lists as the original indexes them: line_table_lists_raw[line_table_lists_base[type] + k]
    # (signed bytes; an index past a list's end reads the next one)
    t['line_table_lists_base'] = list(bases)
    t['line_table_lists_raw'] = list(struct.unpack('<256b', le.read(0xcccc8, 256)))
    # line_preference[mode][line]: 4 candidate lines tried by choose_line (-1 = end), indexed by the
    # coaching mode (team +0xd5); 8 rows each, as the original reads them (mode 1 adds 4 to the
    # line with flags2 & 0x80; past a mode's own rows it reads the next mode's)
    t['line_preference'] = [[list(struct.unpack('<4b', le.read(le.read_u32(0xcbd2e + 4 * i) + 4 * j, 4))) for j in range(8)] for i in range(11)]
    # line_rotation[group][line]: the lines offered by the line change prompt (pick_next_line)
    t['line_rotation'] = [list(struct.unpack('<4b', le.read(0xccb5a + 4 * i, 4))) for i in range(24)]
    # and as raw signed bytes from 0x20 before the table to 0x60 after it (pick_next_line indexes
    # it with the prompt's place plus 4 x the current line)
    t['line_rotation_raw'] = list(struct.unpack('<224b', le.read(0xccb5a - 0x20, 224)))
    t['menu_items'] = menu_items(le, exe)
    with open(out, 'w') as f:
        json.dump(t, f, indent=1)
    print(f"wrote {out}: {len(t['anim_sequences'])} animation words, {len(t['ai_state_names'])} states")

if __name__ == '__main__':
    main()
