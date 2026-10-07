#!/usr/bin/env python3
#
# golden.py GAMEDIR OUTDIR: runs routines of HOCKEY.EXE in the emulator (tools/leemu.py) on fixed inputs
# and writes what they produce as JSON files, which the Godot port's tests (godot/nhl_hockey/tests,
# "golden" tests) compare with what the port computes from the same inputs:
#
#   rng.json         randomrange (0x8c230) and the C library's rand / srand (0x8eb27 / 0x8eb4b)
#   fm_driver.json   the AdLib driver (adlib_drv_init / send_midi / tick): the OPL2 registers after
#                    every timer tick of a few MIDI sequences, the port I/O caught by a hook
#   pc_speaker.json  the PC speaker driver (pcspk_*): the PIT divisor and the speaker gate every tick
#   physics.json     approx_distance and direction8 on vectors; collide_boards (with collide_corner,
#                    bounce_off_boards, puck_spin) on puck and skater states at the boards: the entity
#                    record after the call, the sound effects asked for (play_sfx stubbed), the seed;
#                    apply_skating (skating_turn, skating_accelerate, stop_skating, brake, goalie_move)
#                    on skater, goalie and referee states with a direction; collide_boards at the nets
#                    (collide_net, collide_player_net, net_push_off; score_goal, queue_infraction stubbed);
#                    move_entity among team mates (the draw order, collide_pair, stepping around);
#                    advance_animation (frames, durations, the frame countdown, the stride sound);
#                    puck_check_players among players, goalies and the referee (goalie_save,
#                    puck_hits_player, attach_puck_to_stick, take_puck, update_carrier, shot_landed;
#                    knock_down and follow_puck_user_switch stubbed, the team records' statistics
#                    pointing at buffers of the emulator); body contacts of both teams (move_entity,
#                    resolve_body_check, knock_down; injury_check, injure_player, bench_cheer and
#                    start_stoppage stubbed); puck_update among all 17 entities (the prediction,
#                    the carried puck, icing, offside, the penalty shot timer, the frozen puck).
#                    The records after a call keep the fields that changed.
#
# The patch bank is put in the emulator's memory the way loadpatches leaves it: the .PAT file at
# snd_patch_bank, each record's +0x10 pointing at its timbre from the .TIM files.
#
#   python3 tools/nhl/golden.py re/nhl_hockey godot/nhl_hockey/tests/golden
#
import json
import os
import random
import struct
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from leemu import LEEmu                       # noqa: E402

from unicorn import UC_HOOK_CODE, UC_HOOK_INSN    # noqa: E402
from unicorn.x86_const import (UC_X86_INS_IN, UC_X86_INS_OUT, UC_X86_REG_GDTR, UC_X86_REG_DS,  # noqa: E402
                               UC_X86_REG_ES, UC_X86_REG_SS, UC_X86_REG_FS, UC_X86_REG_GS,
                               UC_X86_REG_EAX, UC_X86_REG_EDX, UC_X86_REG_ESP, UC_X86_REG_EIP)

RANDOMRANGE = 0x8c230
RAND = 0x8eb27
SRAND = 0x8eb4b
SEED = 0xc9100                                # random_seed, the state of randomrange
SND_PATCH_BANK = 0xede5c
OPL_DELAY = (0xd67a0, 0xd67a4)                # the delay loops of opl_write_reg (opl_calibrate_delay)
ADLIB_INIT = 0x9debe
ADLIB_TICK = 0x9df80
ADLIB_SEND = 0x9e676
PCSPK_INIT = 0x9d698
PCSPK_TICK = 0x9d6f3
PCSPK_SEND = 0x9daac
ENTITIES = 0xdf81c                            # entities[17], 0x80 bytes each
ENTITIES_INIT = 0x5ba89
COLLIDE_BOARDS = 0x582c9
APPROX_DISTANCE = 0xb3d94                     # cdecl (dx, dy)
DIRECTION8 = 0x8c8e8
PLAY_SFX = 0x59884
COLL_HALF_W = 0xc909c
COLL_HALF_H = 0xc909e


class PortEmu(LEEmu):
    '''The emulator with the port I/O recorded (OUT) and answered with 0 (IN)'''

    def __init__(self, exe):
        super().__init__(exe)
        # the sound code reloads DS (push ds / pop ds, empty_func_902a0: mov ds, cs:[0x90048]): a
        # descriptor table with flat 32 bit segments, selector 0x10 for the data, saved where the
        # code reloads it from
        gdt = 0x50000000
        self.uc.mem_map(gdt, 0x1000)
        flat_code = struct.pack('<Q', 0x00cf9a000000ffff)
        flat_data = struct.pack('<Q', 0x00cf92000000ffff)
        self.uc.mem_write(gdt, b'\0' * 8 + flat_code + flat_data)
        self.uc.reg_write(UC_X86_REG_GDTR, (0, gdt, 0x17, 0))
        for r in (UC_X86_REG_DS, UC_X86_REG_ES, UC_X86_REG_SS, UC_X86_REG_FS, UC_X86_REG_GS):
            self.uc.reg_write(r, 0x10)
        self.write(0x90048, struct.pack('<H', 0x10))
        self.outs = []
        self.uc.hook_add(UC_HOOK_INSN, self._out, None, 1, 0, UC_X86_INS_OUT)
        self.uc.hook_add(UC_HOOK_INSN, self._in, None, 1, 0, UC_X86_INS_IN)

    def _out(self, uc, port, size, value, user):
        self.outs.append((port & 0xffff, value & 0xff))

    def _in(self, uc, port, size, user):
        return 0

    def take_outs(self):
        o = self.outs
        self.outs = []
        return o

    def stub(self, addr, fn):
        '''Replaces the routine at addr: fn(eax) is called instead and the routine returns (with
        fn's result in eax unless it is None); returns the hook for unstub'''
        def hook(uc, address, size, user):
            r = fn(uc.reg_read(UC_X86_REG_EAX))
            if r is not None:
                uc.reg_write(UC_X86_REG_EAX, r & 0xffffffff)
            sp = uc.reg_read(UC_X86_REG_ESP)
            uc.reg_write(UC_X86_REG_EIP, struct.unpack('<I', uc.mem_read(sp, 4))[0])
            uc.reg_write(UC_X86_REG_ESP, sp + 4)
        return self.uc.hook_add(UC_HOOK_CODE, hook, None, addr, addr)

    def unstub(self, h):
        self.uc.hook_del(h)


def read(gamedir, name):
    for n in os.listdir(gamedir):
        if n.lower() == name.lower():
            with open(os.path.join(gamedir, n), 'rb') as f:
                return f.read()
    raise FileNotFoundError(name)


def parse_tim(tim):
    '''{(type, program): entry bytes} of a .TIM file'''
    out = {}
    n = struct.unpack_from('<H', tim, 4)[0]
    base = 6 + 8 * n
    offs = [struct.unpack_from('<I', tim, 6 + 4 * n + 4 * k)[0] for k in range(n)]
    for k in range(n):
        key = tim[6 + 4 * k:10 + 4 * k]
        if key[0] != 0x80:
            continue
        start = base + offs[k]
        end = len(tim)
        if k + 1 < n and base + offs[k + 1] > start:
            end = min(base + offs[k + 1], end)
        out[(key[1], (key[2] << 8) | key[3])] = tim[start:end]
    return out


def load_bank(emu, pat, tims):
    '''loadpatches: the .PAT at snd_patch_bank, every record's timbre pointer (+0x10)'''
    timbres = {}
    for t in tims:
        timbres.update(parse_tim(t))
    p = emu.alloc(pat)
    emu.write(SND_PATCH_BANK, struct.pack('<I', p))
    nrec = (len(pat) - 0x102) // 0x14
    for r in range(nrec):
        rec = pat[0x102 + r * 0x14:0x102 + (r + 1) * 0x14]
        t = timbres.get((rec[0], rec[1]))
        if t is None:
            continue
        a = emu.alloc(t)
        emu.write(p + 0x102 + r * 0x14 + 0x10, struct.pack('<I', a))


# ----------------------------------------------------------------------------------------------
# random numbers
# ----------------------------------------------------------------------------------------------

def rng_cases(exe):
    emu = LEEmu(exe)
    out = {'randomrange': [], 'rand': []}
    for seed, n in ((0xabcd4321, 100), (0x12345678, 7), (0x0, 0x1a), (0xffffffff, 0x8000)):
        emu.write(SEED, struct.pack('<I', seed))
        vals = [emu.call(RANDOMRANGE, eax=n) & 0xffff for _ in range(64)]
        out['randomrange'].append({'seed': seed, 'n': n, 'values': vals,
                                   'final_seed': struct.unpack('<I', emu.read(SEED, 4))[0]})
    for seed in (1, 0x1234, 0xdeadbeef):
        emu.call(SRAND, eax=seed)
        out['rand'].append({'seed': seed, 'values': [emu.call(RAND) for _ in range(64)]})
    return out


# ----------------------------------------------------------------------------------------------
# the AdLib driver
# ----------------------------------------------------------------------------------------------

def fm_sequences():
    '''lists of ticks, each a list of MIDI messages as the driver gets them (notes already + 24)'''
    seqs = {}
    # an organ note: program, volume, note on, a bend, the modulation wheel, note off
    t = [[] for _ in range(120)]
    t[0] = [[0xc0, 0x0b], [0xb0, 7, 100], [0xb0, 10, 64], [0x90, 60, 100]]
    t[30] = [[0xe0, 0, 0x50]]
    t[45] = [[0xb0, 1, 90]]
    t[70] = [[0x80, 60, 0]]
    seqs['organ'] = t
    # the drum kit: the kick (FM sweep), a snare, a hat
    t = [[] for _ in range(80)]
    t[0] = [[0xb9, 7, 0x7f], [0x99, 36, 0x7f]]
    t[10] = [[0x99, 38, 100]]
    t[20] = [[0x99, 42, 90]]
    t[30] = [[0x89, 36, 0], [0x89, 38, 0], [0x89, 42, 0]]
    seqs['drums'] = t
    # the FM effects of the match: the puck drop (0xab) and 0x94 as snd_play_patch sends them
    t = [[] for _ in range(60)]
    t[0] = [[0xb9, 7, 0x7f], [0x99, 0xab - 0x74 + 0x18, 0x7f]]
    t[6] = [[0x89, 0xab - 0x74 + 0x18, 0]]
    t[10] = [[0xb9, 7, 0x60], [0x99, 0x94 - 0x74 + 0x18, 0x7f]]
    t[40] = [[0x89, 0x94 - 0x74 + 0x18, 0]]
    seqs['effects'] = t
    # more notes than voices: allocation and stealing, sustain pedal, all notes off
    rnd = random.Random(1994)
    t = [[] for _ in range(200)]
    t[0] = [[0xc0 | c, p] for c, p in ((0, 0x0b), (1, 0x10), (2, 0x20), (3, 0x30))]
    t[0] += [[0xb0 | c, 7, 110] for c in range(4)]
    held = []
    for k in range(1, 180, 3):
        c = rnd.randrange(4)
        n = rnd.randrange(40, 90)
        t[k].append([0x90 | c, n, rnd.randrange(40, 127)])
        held.append((c, n))
        if len(held) > 6:
            oc, on = held.pop(rnd.randrange(len(held)))
            t[k + 1].append([0x80 | oc, on, 0])
        if k == 60:
            t[k].append([0xb1, 0x40, 0x7f])
        if k == 120:
            t[k].append([0xb1, 0x40, 0])
        if k == 150:
            t[k].append([0xb2, 0x7b, 0])
    seqs['voices'] = t
    return seqs


def fm_run(exe, pat, tims, seq):
    emu = PortEmu(exe)
    load_bank(emu, pat, tims)
    for a in OPL_DELAY:
        emu.write(a, struct.pack('<I', 1))
    regs = [0] * 256
    index = [0]

    def apply(outs):
        for port, v in outs:
            if port == 0x388:
                index[0] = v
            elif port == 0x389:
                regs[index[0]] = v

    emu.call(ADLIB_INIT, stack=(0x388,))
    apply(emu.take_outs())
    msgbuf = emu.alloc(16)
    states = []
    for tick in seq:
        for msg in tick:
            emu.write(msgbuf, bytes(msg))
            emu.call(ADLIB_SEND, stack=(len(msg), msgbuf))
        emu.call(ADLIB_TICK)
        apply(emu.take_outs())
        states.append(list(regs))
    return states


def fm_cases(exe, gamedir):
    pat = read(gamedir, 'PCFF001.PAT')
    tims = [read(gamedir, 'PCFF000.TIM')]
    out = {}
    for name, seq in fm_sequences().items():
        states = fm_run(exe, pat, tims, seq)
        # the registers as changes against the tick before (the first tick: every register)
        diffs = []
        prev = None
        for st in states:
            d = {('%02x' % r): v for r, v in enumerate(st) if prev is None or prev[r] != v}
            diffs.append(d)
            prev = st
        out[name] = {'ticks': seq, 'regs': diffs}
    return out


# ----------------------------------------------------------------------------------------------
# the PC speaker driver
# ----------------------------------------------------------------------------------------------

def pc_run(exe, pat, tims, seq):
    emu = PortEmu(exe)
    load_bank(emu, pat, tims)
    emu.call(PCSPK_INIT)
    emu.take_outs()
    div = [0, 0]
    low = [True]
    gate = [0]
    msgbuf = emu.alloc(16)
    states = []
    for tick in seq:
        for msg in tick:
            emu.write(msgbuf, bytes(msg))
            emu.call(PCSPK_SEND, stack=(len(msg), msgbuf))
        emu.call(PCSPK_TICK)
        for port, v in emu.take_outs():
            if port == 0x42:
                if low[0]:
                    div[0] = v
                else:
                    div[1] = v
                low[0] = not low[0]
            elif port == 0x61:
                gate[0] = v & 1
            elif port == 0x43:
                low[0] = True
        states.append([gate[0], div[0] | (div[1] << 8)])
    return states


def pc_cases(exe, gamedir):
    pat = read(gamedir, 'PCFF003.PAT')
    tims = [read(gamedir, 'PCFF003.TIM')]
    out = {}
    ids = [0x9c, 0xa4, 0x9a, 0xad, 0xab, 0x97, 0x7b, 0x95]
    for k, sid in enumerate(ids):
        t = [[] for _ in range(150)]
        if sid >= 0x80:
            t[0] = [[0xb9, 7, 0x7f], [0x99, sid - 0x74 + 0x18, 0x7f]]
            t[40] = [[0x89, sid - 0x74 + 0x18, 0]]
        else:
            t[0] = [[0xcc, sid], [0xbc, 7, 0x7f], [0x9c, 0x24 + 0x18, 0x7f]]
            t[40] = [[0x8c, 0x24 + 0x18, 0]]
        if k % 2 == 0:
            t[20] = [[0x99, 0xa4 - 0x74 + 0x18, 0x7f]]      # a second effect takes the speaker
        out['%02x' % sid] = {'ticks': t, 'states': pc_run(exe, pat, tims, t)}
    return out


# ----------------------------------------------------------------------------------------------
# match physics
# ----------------------------------------------------------------------------------------------

# the fields of an entity record compared (STRUCTURES.md): name, offset, size (negative: signed)
ENTITY_FIELDS = (('x', 0, -4), ('y', 4, -4), ('z', 8, -4), ('vx', 0xc, -2), ('vy', 0xe, -2), ('vz', 0x10, -2),
                 ('frame', 0x12, -2), ('hit_by', 0x14, -2), ('speed', 0x18, -2), ('line_slot', 0x1a, -2),
                 ('want_dir', 0x28, 1), ('target_x', 0x2a, -2), ('target_y', 0x2c, -2), ('push_x', 0x30, -2),
                 ('push_y', 0x32, -2), ('heading', 0x34, -4), ('spin', 0x36, 1), ('anim', 0x38, -2),
                 ('anim_pos', 0x3a, -2), ('anim_hold', 0x3c, -2), ('flags', 0x44, 1), ('flags2', 0x45, 1),
                 ('timer_b', 0x2e, -2), ('timer_c', 0x3e, -2), ('frame_wait', 0x46, -1), ('roster', 0x47, 1),
                 ('flags4', 0x55, 1), ('weight', 0x56, 1), ('speed_skill', 0x57, 1), ('shot_skill', 0x5b, 1),
                 ('pass_skill', 0x5d, 1), ('offense', 0x5f, 1), ('goalie_skill', 0x60, 1), ('check_skill', 0x62, 1),
                 ('save_result', 0x63, 1), ('left_handed', 0x65, 1),
                 ('stamina', 0x58, 1), ('endurance', 0x61, 1), ('aggression', 0x64, 1), ('timer_d', 0x40, -2),
                 ('state_sp', 0x1c, -2), ('stack', 0x1e, 4), ('stack2', 0x22, 4))
APPLY_SKATING = 0x5e16d
PUCK = ENTITIES + 14 * 0x80
GAME_FLAGS = 0xc90bb
STOP_FLAGS = 0xc90be
WHISTLE_TIMER = 0xc90d2
OPTION_FLAGS = 0xc53ff
TEAM_RECORDS = (0xdf614, 0xdf714)             # +0x46: the energy word of each roster player
SCORE_GOAL = 0x5ab36
QUEUE_INFRACTION = 0x62d80                    # (entity, type)
PUCK_IN_NET = 0xc90ba
MOVE_ENTITY = 0x580f5                         # (entity, x, y)
SORT_DRAW_ORDER2 = 0x5dd7c
DRAW_KEYS = 0xe9a58                           # short[17]
DRAW_POS = 0xe9a7a                            # short[17]
DRAW_LIST = 0xe9ade                           # byte[17]
_FMT = {1: 'B', -1: 'b', 2: 'H', -2: 'h', 4: 'I', -4: 'i'}
ADVANCE_ANIMATION = 0x5caef
PUCK_CHECK_PLAYERS = 0x548ac
MAYBE_QUEUE_INFRACTION = 0x62cf9
LAST_SHOOTER = 0xc90a0
SHOT_POWER = 0xc90a6                          # the high word: the pass target
MISC_FLAGS = 0xc90c0
CROWD_NOISE = 0xcc0dc                         # the high word
EXCITEMENT = 0xe9aa6                          # the high word
LAST_TOUCH_SLOT = 0xe9ac2                     # then last_touch_y, last_touch_x
LAST_PASSER = 0xc90a2
KNOCK_DOWN = 0x562db                          # (hitter, victim)
FOLLOW_PUCK_USER_SWITCH = 0x5b1ce             # (slot)
ACTION_FLAGS = 0xc90bc                        # bit 2 pass, bit 3 shot
ICING_STATE = 0xe9abe                         # byte 2: flags, byte 3: the shooter
GOAL_PREDICTION = 0xdf812                     # words +2 / +6: x where the puck crosses the +y / -y goal line
SAVE_CLIP_SHOWN = 0xe9a9e                     # dword_e9a9e low word
GS_TRAILER = 0xc542e                          # the game summary of the running period: +2 / +4 home / away shots
INJURY_CHECK = 0x65b83                        # (entity): may he be lost
INJURE_PLAYER = 0x55e72
BENCH_CHEER = 0x61576                         # (away)
START_STOPPAGE = 0x63543                      # (index in the infraction queue)
RESOLVE_BODY_CHECK = 0x5382c                  # (e, o, strength)
PERIOD_IDX = 0xc90da
SETTINGS2 = 0xc5400
BREAKAWAY_FLAG = 0xcc0f8
DEFENDERS_AHEAD = 0xcc124
PENALTY_SHOT_SLOT = 0xcc0fc
PENALTY_SHOT_USER = 0xcc108
CROWD_HIT_TOGGLE = 0xcc0da
REF_HITS = 0xcbec2
PENALIZED_COUNT = 0xe9aba                     # byte per team: players in the penalty box
LAST_IMPACT = 0xe9b28
PUCK_UPDATE = 0x4d6b4                         # (puck)
PENALTY_SHOT_TIMER = 0xcc12c                  # steps the loose puck moved away from the net
PENALTY_SHOT_TEAM = 0xcc104
PENALTY_SHOT_PHASE = 0xcc118
PENALTY_SHOT_ACTIVE = 0xcc128
PENALTY_SHOT_SETUP = 0xcc11c
PENALTY_SHOT_SPOT = 0xcc110                   # dwords x, y
USER_SLOTS = 0xc90c2                          # user1_slot, user2_slot, user1_team, user2_team
# the team record fields of the pickup cases (+0x30.. the last three carriers, +0x36 skaters, +0x38
# goalie_request) and the default line table of the port (Lines.default_line_table)
TEAM_FIELDS = (('shots', 0, -2), ('pp_shots', 6, -2), ('faceoffs_won', 0x12, -2), ('offensive_faceoffs', 0x14, -2),
               ('passes_completed', 0x28, -2), ('carrier0', 0x30, -2), ('carrier1', 0x32, -2), ('carrier2', 0x34, -2),
               ('skaters', 0x36, -2), ('goalie_request', 0x38, -2), ('flags', 0x44, 1))
DEFAULT_LINE_TABLE = bytes([0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 0, 1, 2, 12, 13, 3, 4, 5, 14, 15,
                            0, 1, 12, 13, 3, 4, 14, 15, 25, 26, 2, 5] + [0x64] * 8)
ANIM_SEQUENCES = 0xc921d                      # anim_sequences: words, an animation id is a word index
# animation ids set by the original (its set_animation constants, the port's, the check / save /
# signal tables) and the two board pins
ANIM_IDS = [1, 153, 177, 201, 257, 281, 305, 345, 385, 497, 569, 649, 673, 745, 817, 841, 865, 1017, 1169, 1321, 1345, 1417, 1473, 1497, 1521, 1545, 1569, 1593, 1641, 1841, 1953, 1983, 2013, 2033, 2045, 2081, 2099, 2123, 2163, 2259, 2571, 2651, 2675, 2747, 2771, 2795, 2835, 2891, 2915, 2987, 3011, 3035, 3075, 3099, 3139, 3159, 3171, 3187, 3211, 3227, 3243, 3259, 3275, 3289, 3303, 3317, 3333, 3479, 3715, 3735, 3753, 3765, 3787, 4227, 4245, 4405, 4509, 4565, 4637, 5349, 5369] + [0x1027, 0x1055]


def entity_fields(emu, slot):
    rec = emu.read(ENTITIES + slot * 0x80, 0x80)
    return {n: struct.unpack_from('<' + _FMT[k], rec, o)[0] for n, o, k in ENTITY_FIELDS}


def put_fields(rec, fields):
    for n, o, sz in ENTITY_FIELDS:
        if n in fields:
            v = fields[n]
            struct.pack_into('<' + _FMT[sz], rec, o, v if sz < 0 else v & ((1 << (8 * sz)) - 1))


def skating_cases(emu, rnd, base):
    '''apply_skating (skating_turn, skating_accelerate, stop_skating, brake, goalie_move)'''
    out = []
    anims = (0, 0x289, 0x2a1, 0x2e9, 0x331, 0x349, 0x361, 0x529, 0x541, 0x99, 0xa5b, 0xad3)
    for k in range(400):
        emu.write(ENTITIES, base)
        slot = (2, 3, 8, 10, 0, 6, 16)[k % 7]
        rec = bytearray(emu.read(ENTITIES + slot * 0x80, 0x80))
        line_slot = 0 if slot in (0, 6) else (rnd.randrange(1, 6) if slot < 12 else -1)
        lim = rnd.choice((0x300, 0x1800, 0x3000))
        f = {'x': rnd.randrange(-150, 150) << 16 | rnd.randrange(0x10000),
             'y': rnd.randrange(-250, 250) << 16 | rnd.randrange(0x10000),
             'vx': rnd.randrange(-lim, lim) if rnd.random() < 0.85 else 0,
             'vy': rnd.randrange(-lim, lim) if rnd.random() < 0.85 else 0,
             'line_slot': line_slot, 'heading': rnd.randrange(8) << 16 | rnd.randrange(0x10000),
             'speed': rnd.randrange(0, 21),
             'anim': rnd.choice(anims), 'anim_pos': rnd.randrange(0, 6), 'anim_hold': rnd.randrange(-1, 4),
             'flags': (rnd.choice((0, 0x10)) | rnd.choice((0, 0x80)) | (0x40 if 6 <= slot < 12 else 0)),
             'flags2': rnd.choice((0, 0, 2, 0x40)), 'flags4': rnd.choice((0, 8)),
             'roster': rnd.randrange(0, 20), 'weight': rnd.randrange(140, 230),
             'speed_skill': rnd.randrange(0, 16), 'stamina': rnd.randrange(0, 16),
             'endurance': rnd.randrange(0, 0x40)}
        put_fields(rec, f)
        emu.write(ENTITIES + slot * 0x80, rec)
        energy = rnd.choice((0x1000, rnd.randrange(0, 0x1001), 0xc10, 0xbf0))
        team = TEAM_RECORDS[1 if f['flags'] & 0x40 else 0]
        emu.write(team + 0x46 + f['roster'] * 2, struct.pack('<h', energy))
        puck = bytearray(emu.read(PUCK, 0x80))
        put_fields(puck, {'x': rnd.randrange(-150, 150) << 16, 'y': rnd.randrange(-250, 250) << 16,
                          'vy': rnd.randrange(-0x3000, 0x3000)})
        carrier = rnd.choice((-1, -1, slot, 4 if slot != 4 else 9))
        puck[0x42] = carrier & 0xff
        emu.write(PUCK, puck)
        game = rnd.choice((0, 0, 1, 8))
        stop = rnd.choice((0, 0, 0x80))
        whistle = rnd.choice((0, 0, 0, 5))
        options = rnd.choice((0, 4))
        emu.write(GAME_FLAGS, bytes([game]))
        emu.write(STOP_FLAGS, struct.pack('<H', stop))
        emu.write(WHISTLE_TIMER, struct.pack('<I', whistle))
        emu.write(OPTION_FLAGS, struct.pack('<I', options))
        seed = rnd.getrandbits(32)
        if k >= 300:
            # the next randomrange(0x80) gives 0: the fatigue step of skating_accelerate
            nxt = (rnd.getrandbits(8) | (rnd.randrange(2) << 8)) << 8 | rnd.getrandbits(8) | rnd.getrandbits(8) << 24
            seed = ((nxt - 1) * pow(0xbb40e62d, -1, 1 << 32)) & 0xffffffff
            options = 4
            game = 0
            emu.write(GAME_FLAGS, bytes([game]))
            emu.write(OPTION_FLAGS, struct.pack('<I', options))
        emu.write(SEED, struct.pack('<I', seed))
        d = rnd.choice((0, 1, 2, 3, 4, 5, 6, 7, 8, 9))
        before = entity_fields(emu, slot)
        emu.call(APPLY_SKATING, eax=ENTITIES + slot * 0x80, edx=d)
        out.append({'slot': slot, 'dir': d, 'energy': energy, 'carrier': carrier,
                    'puck': [struct.unpack_from('<h', puck, 2)[0], struct.unpack_from('<h', puck, 6)[0],
                             struct.unpack_from('<h', puck, 0xe)[0]],
                    'game_flags': game, 'stop_flags': stop, 'whistle': whistle, 'options': options,
                    'seed': seed, 'before': before, 'after': entity_fields(emu, slot),
                    'energy_after': struct.unpack('<h', emu.read(team + 0x46 + f['roster'] * 2, 2))[0],
                    'final_seed': struct.unpack('<I', emu.read(SEED, 4))[0]})
        emu.write(GAME_FLAGS, b'\0')
        emu.write(STOP_FLAGS, b'\0\0')
        emu.write(WHISTLE_TIMER, b'\0' * 4)
        emu.write(OPTION_FLAGS, b'\0' * 4)
    return out


def net_cases(emu, rnd, base, sfx, goals, infractions):
    '''collide_boards in front of and behind the nets: collide_net (goals, posts, the roof, the
    frame), collide_player_net and net_push_off; score_goal and queue_infraction stubbed'''
    out = []
    for k in range(400):
        emu.write(ENTITIES, base)
        slot = 14 if k % 2 == 0 else (3, 8, 16)[(k // 2) % 3]
        rec = bytearray(emu.read(ENTITIES + slot * 0x80, 0x80))
        hw = struct.unpack_from('<h', rec, 0x66)[0]
        hh = struct.unpack_from('<h', rec, 0x68)[0]
        top = rnd.random() < 0.5
        ny = 236 if top else -236
        if slot == 14:
            x = rnd.randrange(-26, 27)
            y = ny + rnd.randrange(-9, 10)
            lim = 0x4000
        else:
            x = rnd.randrange(-40, 41)
            y = ny + rnd.randrange(-24, 25)
            lim = 0x2400
        vx = rnd.randrange(-lim, lim) if rnd.random() < 0.8 else 0
        vy = rnd.randrange(-lim, lim)
        z = 0 if slot != 14 or rnd.random() < 0.6 else rnd.randrange(0, 0x14)
        f = {'x': (x << 16) | rnd.randrange(0x10000), 'y': (y << 16) | rnd.randrange(0x10000), 'z': z << 16,
             'vx': vx, 'vy': vy, 'vz': rnd.randrange(-0x400, 0x400) if z else 0, 'speed': rnd.randrange(0, 21),
             'flags': rnd.choice((0, 0x80)) | (0x40 if 6 <= slot < 12 else 0) | (1 if slot == 14 else 0),
             'anim_pos': rnd.randrange(0, 14)}
        put_fields(rec, f)
        prev_x = f['x'] - vx * 16
        prev_y = f['y'] - vy * 16
        prev_z = f['z'] if rnd.random() < 0.8 else rnd.randrange(0, 0x14) << 16
        struct.pack_into('<iii', rec, 0x74, prev_x, prev_y, prev_z)
        emu.write(ENTITIES + slot * 0x80, rec)
        carrier = -1 if slot == 14 and rnd.random() < 0.7 else rnd.choice((2, 9))
        puck = bytearray(emu.read(PUCK, 0x80))
        if slot != 14:
            put_fields(puck, {'y': (ny + rnd.randrange(-50, 51)) << 16})
            emu.write(PUCK, puck)
        emu.write(PUCK + 0x42, bytes([carrier & 0xff]))
        game = rnd.choice((0, 0, 0, 1))
        emu.write(GAME_FLAGS, bytes([game]))
        seed = rnd.getrandbits(32)
        if slot != 14 and k % 4 == 1:
            # the next randomrange(0x20) gives 0: net_push_off looks at the speed
            nxt = rnd.getrandbits(11) << 8 | rnd.getrandbits(8) | rnd.getrandbits(8) << 24
            seed = ((nxt - 1) * pow(0xbb40e62d, -1, 1 << 32)) & 0xffffffff
        emu.write(SEED, struct.pack('<I', seed))
        emu.write(COLL_HALF_W, struct.pack('<hh', hw, hh))
        emu.write(PUCK_IN_NET, b'\0')
        del sfx[:]
        del goals[:]
        del infractions[:]
        before = entity_fields(emu, slot)
        emu.call(COLLIDE_BOARDS, eax=ENTITIES + slot * 0x80, edx=x & 0xffffffff, ebx=y & 0xffffffff)
        net = 12 if top else 13
        out.append({'slot': slot, 'carrier': carrier, 'seed': seed, 'px': x, 'py': y, 'hw': hw, 'hh': hh,
                    'prev_x': prev_x, 'prev_y': prev_y, 'prev_z': prev_z, 'game_flags': game,
                    'puck_y': struct.unpack_from('<h', puck, 6)[0], 'before': before,
                    'after': entity_fields(emu, slot), 'sfx': list(sfx), 'goal': list(goals),
                    'infractions': list(infractions), 'puck_in_net': emu.read(PUCK_IN_NET, 1)[0],
                    'net_v': list(struct.unpack('<hh', emu.read(ENTITIES + net * 0x80 + 0xc, 4))),
                    'carrier_after': struct.unpack('<b', emu.read(PUCK + 0x42, 1))[0],
                    'final_seed': struct.unpack('<I', emu.read(SEED, 4))[0]})
        emu.write(GAME_FLAGS, b'\0')
    return out


def draw_order(emu):
    return {'list': list(emu.read(DRAW_LIST, 17)),
            'pos': list(struct.unpack('<17h', emu.read(DRAW_POS, 34))),
            'keys': list(struct.unpack('<17h', emu.read(DRAW_KEYS, 34)))}


def contact_cases(emu, rnd, base, sfx):
    '''move_entity among team mates: boards and the stick, the neighbours in the draw order,
    collide_pair's exchange of momentum, team mates stepping around each other (apply_skating)'''
    out = []
    frames = list(range(0, 0x284)) + list(range(0x294, 0x2da)) + list(range(0x378, 0x468))
    for k in range(300):
        emu.write(ENTITIES, base)
        for t in TEAM_RECORDS:
            emu.write(t + 0x46, struct.pack('<28h', *([0x1000] * 28)))
        cx = rnd.randrange(-150, 151)
        cy = rnd.randrange(-250, 251)
        cluster = [s_ for s_ in range(6) if rnd.random() < 0.75] or [1, 2]
        if rnd.random() < 0.5:
            cluster.append(14)
        befores = {}
        for slot in cluster:
            rec = bytearray(emu.read(ENTITIES + slot * 0x80, 0x80))
            x = cx + rnd.randrange(-14, 15)
            y = cy + rnd.randrange(-14, 15)
            lim = rnd.choice((0x400, 0x1800, 0x3000))
            f = {'x': x << 16 | rnd.randrange(0x10000), 'y': y << 16 | rnd.randrange(0x10000),
                 'vx': rnd.randrange(-lim, lim), 'vy': rnd.randrange(-lim, lim),
                 'speed': rnd.randrange(0, 21), 'heading': rnd.randrange(8) << 16 | rnd.randrange(0x10000),
                 'want_dir': rnd.randrange(9), 'target_x': rnd.randrange(-150, 151), 'target_y': rnd.randrange(-250, 251)}
            if slot != 14:
                f.update({'line_slot': 0 if slot == 0 else rnd.randrange(1, 6),
                          'frame': rnd.choice(frames), 'flags4': rnd.choice((0, 8)),
                          'flags': rnd.choice((0, 0, 0, 0x08, 0x10)) | rnd.choice((0, 0x80)) | (0x04 if rnd.random() < 0.05 else 0),
                          'flags2': (0x20 if rnd.random() < 0.05 else 0) | rnd.choice((0, 0, 2)),
                          'roster': rnd.randrange(0, 20), 'weight': rnd.randrange(140, 230),
                          'speed_skill': rnd.randrange(0, 16), 'stamina': rnd.randrange(0, 16),
                          'anim': rnd.choice((0, 0x289, 0x2a1, 0x331, 0x529)), 'anim_pos': rnd.randrange(0, 6),
                          'anim_hold': rnd.randrange(-1, 4), 'hit_by': rnd.choice((0, 3, -1))})
            put_fields(rec, f)
            struct.pack_into('<ii', rec, 0x74, f['x'], f['y'])
            emu.write(ENTITIES + slot * 0x80, rec)
        emu.call(SORT_DRAW_ORDER2)
        # the mover takes its step; another entity may have moved since the keys were taken
        mover = rnd.choice([s_ for s_ in cluster if s_ != 14])
        for slot in cluster:
            rec = bytearray(emu.read(ENTITIES + slot * 0x80, 0x80))
            if slot == mover or rnd.random() < 0.2:
                x0, y0 = struct.unpack_from('<ii', rec, 0)
                vx, vy = struct.unpack_from('<hh', rec, 0xc)
                struct.pack_into('<ii', rec, 0x74, x0, y0)
                struct.pack_into('<ii', rec, 0, x0 + vx * 16, y0 + vy * 16)
                emu.write(ENTITIES + slot * 0x80, rec)
            befores[slot] = entity_fields(emu, slot)
            befores[slot]['prev'] = list(struct.unpack_from('<ii', rec, 0x74))
        carrier = rnd.choice((-1, -1, mover, cluster[0]))
        emu.write(PUCK + 0x42, bytes([carrier & 0xff]))
        game = rnd.choice((0, 0, 0, 1))
        emu.write(GAME_FLAGS, bytes([game]))
        options = rnd.choice((0, 4))
        emu.write(OPTION_FLAGS, struct.pack('<I', options))
        seed = rnd.getrandbits(32)
        emu.write(SEED, struct.pack('<I', seed))
        emu.write(PUCK_IN_NET, b'\0')
        order = draw_order(emu)
        del sfx[:]
        x = struct.unpack('<h', emu.read(ENTITIES + mover * 0x80 + 2, 2))[0]
        y = struct.unpack('<h', emu.read(ENTITIES + mover * 0x80 + 6, 2))[0]
        emu.call(MOVE_ENTITY, eax=ENTITIES + mover * 0x80, edx=x & 0xffffffff, ebx=y & 0xffffffff)
        out.append({'mover': mover, 'carrier': carrier, 'game_flags': game, 'options': options, 'seed': seed,
                    'before': {str(s_): v for s_, v in befores.items()}, 'order': order,
                    'after': {str(s_): entity_fields(emu, s_) for s_ in cluster}, 'order_after': draw_order(emu),
                    'sfx': list(sfx), 'puck_in_net': emu.read(PUCK_IN_NET, 1)[0],
                    'final_seed': struct.unpack('<I', emu.read(SEED, 4))[0]})
        emu.write(GAME_FLAGS, b'\0')
        emu.write(OPTION_FLAGS, b'\0' * 4)
    return out


def team_put(emu, t, f):
    for n, o, sz in TEAM_FIELDS:
        emu.write(t + o, struct.pack('<' + _FMT[sz], f[n] if sz < 0 else f[n] & ((1 << (8 * sz)) - 1)))


def team_get(emu, t):
    return {n: struct.unpack('<' + _FMT[sz], emu.read(t + o, abs(sz)))[0] for n, o, sz in TEAM_FIELDS}


def anim_word(emu, i):
    return struct.unpack('<h', emu.read(ANIM_SEQUENCES + i * 2, 2))[0]


def animation_cases(emu, rnd, base, sfx):
    '''advance_animation: the frames, their durations, the end of an animation, the frame shown at
    most every 5 steps and the stride sound'''
    def stride(f):
        return ((0x112 <= f <= 0x14e and (f - 0x112) & 3 == 0) or (0x207 <= f <= 0x215 and f & 1)
                or (0x314 < f < 0x32b and f % 3 == 0) or (0x389 < f < 0x3ae and (f - 0x38a) % 5 == 0)
                or f in (0x36f, 0x373, 0x377, 0x3bf, 0x3c3, 0x3ce, 0x3d1))
    # the animations with frames that play the stride sound
    stride_ids = []
    for a in ANIM_IDS:
        head = anim_word(emu, a) & 0xffff
        for d in range(8):
            lst = a + ((head & 0x7fff) if d == 0 else anim_word(emu, a + d) & 0xffff) + 8
            if any(stride(anim_word(emu, lst + 2 * i)) for i in range(12)):
                stride_ids.append(a)
                break
    out = []
    for k in range(500):
        emu.write(ENTITIES, base)
        slot = (2, 9, 0, 16, 14)[k % 5]
        anim = rnd.choice(ANIM_IDS) if rnd.random() < 0.96 else 0
        if k % 3 == 1:
            anim = rnd.choice(stride_ids)
        facing = rnd.randrange(8)
        mirror = rnd.choice((0, 8))
        d = (8 - facing) & 7 if mirror else facing
        head = anim_word(emu, anim) & 0xffff
        off = (head & 0x7fff) if d == 0 else anim_word(emu, anim + d) & 0xffff
        lst = anim + off + 8
        frames = []
        while len(frames) < 40:
            fr, du = anim_word(emu, lst + 2 * len(frames)), anim_word(emu, lst + 2 * len(frames) + 1)
            frames.append((fr, du))
            if du < 0:
                break
        pos = rnd.randrange(len(frames)) if rnd.random() < 0.7 else len(frames) - 1
        dur = abs(frames[pos][1])
        f = {'anim': anim, 'anim_pos': 2 * pos, 'anim_hold': rnd.choice((-1, 0, 0, rnd.randrange(0, dur + 1))),
             'heading': facing << 16 | rnd.randrange(0x10000), 'flags4': mirror,
             'frame': frames[pos][0] if rnd.random() < 0.3 else rnd.choice((frames[0][0], -1, rnd.randrange(0, 0x468))),
             'frame_wait': rnd.choice((-1, 0, 0, 0, 1, 4)) if k % 3 != 1 else 0, 'flags': rnd.choice((0, 0x20, 0x22)),
             'flags2': rnd.choice((0, 2)), 'x': rnd.randrange(-150, 150) << 16 | rnd.randrange(0x10000),
             'vx': rnd.randrange(-0x800, 0x800), 'vy': rnd.randrange(-0x800, 0x800)}
        rec = bytearray(emu.read(ENTITIES + slot * 0x80, 0x80))
        put_fields(rec, f)
        emu.write(ENTITIES + slot * 0x80, rec)
        del sfx[:]
        before = entity_fields(emu, slot)
        emu.call(ADVANCE_ANIMATION, eax=ENTITIES + slot * 0x80)
        out.append({'slot': slot, 'before': before, 'after': entity_fields(emu, slot), 'sfx': list(sfx)})
    return out


def pickup_cases(emu, rnd, base, calls):
    """puck_check_players: the puck against the players near it in the draw order (the goalies'
    reach, the skaters' bodies and sticks, goalie_save, puck_hits_player, attach_puck_to_stick,
    take_puck, update_carrier, shot_landed); play_sfx, the infraction queue, knock_down and
    follow_puck_user_switch stubbed (calls: their calls in order)"""
    hooks = [emu.stub(KNOCK_DOWN, lambda eax: calls.append(['knock_down', (eax - ENTITIES) // 0x80,
                                                            ((emu.uc.reg_read(UC_X86_REG_EDX) & 0xffffffff) - ENTITIES) // 0x80])),
             emu.stub(FOLLOW_PUCK_USER_SWITCH, lambda eax: calls.append(['follow_puck_user_switch',
                                                                         struct.unpack('<h', struct.pack('<H', eax & 0xffff))[0]]))]
    # the statistics the team records point at: the line table (the goalie in the net: +0x24 +
    # goalie_request), the players' 0x10 byte records and the goalies' 3 words
    tables = []
    for t in TEAM_RECORDS:
        lt = emu.alloc(bytes(DEFAULT_LINE_TABLE))
        ps = emu.alloc(b'\0' * 28 * 0x10)
        gs = emu.alloc(b'\0' * 3 * 6)
        emu.write(t + 0xda, struct.pack('<I', lt))
        emu.write(t + 0xe6, struct.pack('<I', ps))
        emu.write(t + 0xea, struct.pack('<I', gs))
        tables.append((ps, gs))
    out = []
    anims = (0, 0, 0x289, 0x2e9, 0xb1, 0xc9, 0xe1, 0x101, 0x119, 0x11d5, 0x121d, 0x13c5, 0x14ad, 0x84b,
             0x181, 0x206, 0x215, 0x119d, 0x1f1, 0x3f9, 0x491)
    for k in range(800):
        emu.write(ENTITIES, base)
        teams = []
        for ti, t in enumerate(TEAM_RECORDS):
            energy = rnd.choice((0x1000, 0xc00, 0x800))
            emu.write(t + 0x46, struct.pack('<28h', *([energy] * 28)))
            f = {'energy': energy, 'shots': rnd.randrange(30), 'pp_shots': rnd.randrange(5), 'faceoffs_won': rnd.randrange(20),
                 'offensive_faceoffs': rnd.randrange(10), 'passes_completed': rnd.randrange(40),
                 'carrier0': rnd.choice((-1, rnd.randrange(20))), 'carrier1': rnd.choice((-1, rnd.randrange(20), -0xfb)),
                 'carrier2': rnd.choice((-1, rnd.randrange(20))), 'skaters': rnd.choice((6, 6, 5, 4)),
                 'goalie_request': rnd.choice((0, 0, 1, -0x100)), 'flags': rnd.choice((0, 8, 0x10, 0x18))}
            team_put(emu, t, f)
            ps, gs = tables[ti]
            emu.write(ps, b'\0' * 28 * 0x10)
            emu.write(gs, b'\0' * 3 * 6)
            teams.append(f)
        px = rnd.randrange(-140, 141)
        py = rnd.randrange(-240, 241)
        lim = rnd.choice((0x400, 0x1800, 0x4000))
        puck = bytearray(emu.read(PUCK, 0x80))
        put_fields(puck, {'x': px << 16 | rnd.randrange(0x10000), 'y': py << 16 | rnd.randrange(0x10000),
                          'z': rnd.choice((0, 0, 0, rnd.randrange(0, 0x14))) << 16 | rnd.randrange(0x10000),
                          'vx': rnd.randrange(-lim, lim), 'vy': rnd.randrange(-lim, lim),
                          'vz': rnd.choice((0, rnd.randrange(-0x400, 0x400))),
                          'frame': rnd.choice((0x430, 0x438, 0x450, 0x460, 0x18a, rnd.randrange(0x430, 0x468))),
                          'timer_c': rnd.choice((0, 0, 0, 4)), 'anim_pos': rnd.randrange(0, 14)})
        emu.write(PUCK, puck)
        cluster = [s_ for s_ in (0, 2, 3, 6, 8, 9, 16) if rnd.random() < 0.4] or [2]
        near = rnd.choice((16, 16, 10, 6))
        for slot in cluster:
            rec = bytearray(emu.read(ENTITIES + slot * 0x80, 0x80))
            f = {'x': (px + rnd.randrange(-near, near + 1)) << 16 | rnd.randrange(0x10000),
                 'y': (py + rnd.randrange(-near, near + 1)) << 16 | rnd.randrange(0x10000),
                 'vx': rnd.randrange(-0x1000, 0x1000), 'vy': rnd.randrange(-0x1000, 0x1000),
                 'heading': rnd.randrange(8) << 16, 'anim': rnd.choice(anims), 'anim_pos': rnd.choice((0, 2, 4)),
                 'anim_hold': rnd.randrange(-1, 4), 'frame_wait': rnd.choice((0, 0, 3)),
                 'frame': rnd.choice((rnd.randrange(0x196, 0x21a), rnd.randrange(0x430, 0x450), rnd.randrange(0x3ce, 0x430),
                                      rnd.randrange(0, 0x196), 0x206 + rnd.randrange(16), rnd.randrange(0x450, 0x468))),
                 'flags': rnd.choice((0, 0x80)) | (0x40 if 6 <= slot < 12 else 0) | rnd.choice((0, 0, 8, 1, 0x20)),
                 'flags2': rnd.choice((0, 0, 0, 4, 0x80)), 'flags4': rnd.choice((0, 8)),
                 'timer_c': rnd.choice((0, 0, 0, 0, 3)), 'timer_b': rnd.randrange(0, 10),
                 'line_slot': -1 if slot == 16 else (0 if slot in (0, 6) else rnd.randrange(1, 6)),
                 'roster': rnd.randrange(0, 20), 'shot_skill': rnd.randrange(16), 'pass_skill': rnd.randrange(16),
                 'offense': rnd.randrange(16), 'goalie_skill': rnd.randrange(16), 'check_skill': rnd.randrange(16),
                 'endurance': rnd.randrange(16), 'left_handed': rnd.choice((0, 1)), 'save_result': rnd.choice((0, 1)),
                 'speed_skill': rnd.randrange(16), 'stamina': rnd.randrange(16)}
            put_fields(rec, f)
            emu.write(ENTITIES + slot * 0x80, rec)
        emu.call(SORT_DRAW_ORDER2)
        carrier = rnd.choice((-1, -1, -1, rnd.choice(cluster)))
        emu.write(PUCK + 0x42, bytes([carrier & 0xff]))
        stop = rnd.choice((0, 0x10, 0x10, 0x30, 0x20))
        g = {'game_flags': rnd.choice((0, 0, 0, 0, 0, 1, 0x10)), 'stop_flags': stop,
             'last_shooter': rnd.choice((2, 9, 3, 8)) if stop & 0x10 else rnd.choice((-1, 2, 9)),
             'pass_target': rnd.choice((-1, rnd.choice(cluster), 4)),
             'misc_flags': rnd.choice((0, 0x10)), 'last_passer': rnd.choice((-1, 3)),
             'last_touch': [rnd.choice((2, 8, 3, 9)), rnd.randrange(-200, 200), rnd.randrange(-100, 100)],
             'crowd': rnd.randrange(0, 1200), 'excitement': rnd.randrange(0, 100),
             'options': rnd.choice((0, 2, 8, 10)), 'action_flags': rnd.choice((0, 4, 8, 0xc)),
             'icing': [rnd.choice((0, 4, 5, 7, 1, 6)), rnd.choice((2, 9))],
             'prediction': [rnd.randrange(-60, 60), rnd.randrange(-60, 60)], 'save_clip_shown': rnd.choice((0, 0, 0, 1)),
             'summary_shots': [rnd.randrange(20), rnd.randrange(20)]}
        emu.write(GAME_FLAGS, bytes([g['game_flags']]))
        emu.write(STOP_FLAGS, struct.pack('<H', g['stop_flags']))
        emu.write(LAST_SHOOTER, struct.pack('<h', g['last_shooter']))
        emu.write(SHOT_POWER + 2, struct.pack('<h', g['pass_target']))
        emu.write(MISC_FLAGS, struct.pack('<I', g['misc_flags']))
        emu.write(LAST_PASSER, struct.pack('<h', g['last_passer']))
        emu.write(LAST_TOUCH_SLOT, struct.pack('<hhh', *g['last_touch']))
        emu.write(CROWD_NOISE + 2, struct.pack('<h', g['crowd']))
        emu.write(EXCITEMENT + 2, struct.pack('<h', g['excitement']))
        emu.write(OPTION_FLAGS, struct.pack('<I', g['options']))
        emu.write(ACTION_FLAGS, bytes([g['action_flags']]))
        emu.write(ICING_STATE + 2, bytes(g['icing']))
        emu.write(GOAL_PREDICTION + 2, struct.pack('<h', g['prediction'][0]))
        emu.write(GOAL_PREDICTION + 6, struct.pack('<h', g['prediction'][1]))
        emu.write(SAVE_CLIP_SHOWN, struct.pack('<H', g['save_clip_shown']))
        emu.write(GS_TRAILER + 2, bytes([g['summary_shots'][0]]))
        emu.write(GS_TRAILER + 4, bytes([g['summary_shots'][1]]))
        seed = rnd.getrandbits(32)
        emu.write(SEED, struct.pack('<I', seed))
        order = draw_order(emu)
        befores = {str(s_): entity_fields(emu, s_) for s_ in cluster + [14]}
        del calls[:]
        emu.call(PUCK_CHECK_PLAYERS, eax=PUCK)
        out.append({'carrier': carrier, 'globals': g, 'seed': seed, 'order': order, 'before': befores, 'teams': teams,
                    'after': {str(s_): entity_fields(emu, s_) for s_ in cluster + [14]},
                    'carrier_after': struct.unpack('<b', emu.read(PUCK + 0x42, 1))[0], 'calls': [list(c) for c in calls],
                    'globals_after': {
                        'stop_flags': struct.unpack('<H', emu.read(STOP_FLAGS, 2))[0],
                        'last_passer': struct.unpack('<h', emu.read(LAST_PASSER, 2))[0],
                        'last_touch': list(struct.unpack('<hhh', emu.read(LAST_TOUCH_SLOT, 6))),
                        'pass_target': struct.unpack('<h', emu.read(SHOT_POWER + 2, 2))[0],
                        'misc_flags': emu.read(MISC_FLAGS, 1)[0], 'action_flags': emu.read(ACTION_FLAGS, 1)[0],
                        'crowd': struct.unpack('<h', emu.read(CROWD_NOISE + 2, 2))[0],
                        'excitement': struct.unpack('<h', emu.read(EXCITEMENT + 2, 2))[0],
                        'icing': list(emu.read(ICING_STATE + 2, 2)),
                        'summary_shots': [emu.read(GS_TRAILER + 2, 1)[0], emu.read(GS_TRAILER + 4, 1)[0]]},
                    'teams_after': [dict(team_get(emu, t),
                                         player_shots=[struct.unpack('<h', emu.read(tables[ti][0] + r * 0x10 + 0xe, 2))[0]
                                                       for r in range(28)],
                                         goalie_shots=[struct.unpack('<h', emu.read(tables[ti][1] + gi * 6 + 2, 2))[0] for gi in range(3)])
                                    for ti, t in enumerate(TEAM_RECORDS)],
                    'final_seed': struct.unpack('<I', emu.read(SEED, 4))[0]})
        for a, n in ((GAME_FLAGS, 1), (STOP_FLAGS, 2), (MISC_FLAGS, 4), (OPTION_FLAGS, 4)):
            emu.write(a, b'\0' * n)
    for h in hooks:
        emu.unstub(h)
    return out


CHECK_GLOBALS = (('period', PERIOD_IDX, -2), ('settings2', SETTINGS2, 1), ('breakaway', BREAKAWAY_FLAG, -4),
                 ('defenders_ahead', DEFENDERS_AHEAD, -4), ('penalty_shot_slot', PENALTY_SHOT_SLOT, -4),
                 ('penalty_shot_user', PENALTY_SHOT_USER, -4), ('crowd_hit_toggle', CROWD_HIT_TOGGLE, -2),
                 ('ref_hits', REF_HITS, -2), ('box_home', PENALIZED_COUNT, 1), ('box_away', PENALIZED_COUNT + 1, 1),
                 ('user1_slot', MISC_FLAGS + 2, -2), ('crowd', CROWD_NOISE + 2, -2), ('excitement', EXCITEMENT + 2, -2),
                 ('last_impact', LAST_IMPACT, -2), ('action_flags', ACTION_FLAGS, 1), ('puck_in_net', PUCK_IN_NET, 1))


def check_cases(emu, rnd, base, calls):
    '''body contacts among players of both teams, goalies, the referee and the puck: move_entity
    (collide_pair, goalie_collision), resolve_body_check (resolve_hook_hold, resolve_dive_hit,
    penalty_odds, breakaway_foul, facing_boards) and knock_down (knockdown_position at the
    boards) called directly, a third each; injury_check (answering yes), injure_player,
    bench_cheer and start_stoppage stubbed'''
    def slot_of(eax):
        return ((eax & 0xffffffff) - ENTITIES) // 0x80

    def s16(v):
        return struct.unpack('<h', struct.pack('<H', v & 0xffff))[0]
    hooks = [emu.stub(INJURY_CHECK, lambda eax: (calls.append(['injury_check', slot_of(eax)]), 1)[1]),
             emu.stub(INJURE_PLAYER, lambda eax: calls.append(['injure_player', slot_of(eax)])),
             emu.stub(BENCH_CHEER, lambda eax: calls.append(['bench_cheer', eax & 0xffffffff])),
             emu.stub(START_STOPPAGE, lambda eax: calls.append(['start_stoppage', s16(eax)]))]
    out = []
    frames = list(range(0, 0x284)) + list(range(0x294, 0x2da)) + list(range(0x378, 0x468))
    anims = (0x621, 0x621, 0x621, 0x621, 0, 0x289, 0x639, 0x873, 0x589, 0x589, 0xed7, 0x6d9, 0x13c5, 0x529)
    for k in range(1800):
        mode = ('move', 'body', 'knock')[k % 3]
        emu.write(ENTITIES, base)
        teams = []
        for t in TEAM_RECORDS:
            energy = rnd.choice((0x1000, 0xc00))
            emu.write(t + 0x46, struct.pack('<28h', *([energy] * 28)))
            ent = [rnd.choice((-1, -1, -1, -2, -3)) for _ in range(28)]
            emu.write(t + 0x7e, struct.pack('<28h', *ent))
            f = {'energy': energy, 'entity_of': ent, 'hits': rnd.randrange(20), 'skaters': rnd.choice((6, 6, 5, 4)),
                 'goalie_request': rnd.choice((0, 0, 0, 1, -0x100))}
            emu.write(t + 0x24, struct.pack('<h', f['hits']))
            emu.write(t + 0x36, struct.pack('<hh', f['skaters'], f['goalie_request']))
            teams.append(f)
        region = rnd.randrange(4)
        if region == 0:          # open ice
            cx, cy = rnd.randrange(-110, 111), rnd.randrange(-200, 201)
        elif region == 1:        # the side boards
            cx, cy = rnd.choice((-1, 1)) * rnd.randrange(0x78, 0x98), rnd.randrange(-0xe0, 0xe0)
        elif region == 2:        # the corners
            cx, cy = rnd.choice((-1, 1)) * rnd.randrange(0x50, 0x90), rnd.choice((-1, 1)) * rnd.randrange(0xc0, 0xf8)
        else:                    # the end boards and the nets
            cx, cy = rnd.randrange(-0x70, 0x71), rnd.choice((-1, 1)) * rnd.randrange(0xa0, 0xfc)
        pool = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 16]
        cluster = rnd.sample(pool, rnd.choice((2, 2, 3, 4)))
        if rnd.random() < (0.6 if mode == 'knock' else 0.3):
            cluster.append(14)
        befores = {}
        mover = rnd.choice([s_ for s_ in cluster if s_ != 14])
        for slot in cluster:
            rec = bytearray(emu.read(ENTITIES + slot * 0x80, 0x80))
            x = cx + rnd.randrange(-7, 8)
            y = cy + rnd.randrange(-7, 8)
            lim = rnd.choice((0x800, 0x1800, 0x3000))
            vx, vy = rnd.randrange(-lim, lim), rnd.randrange(-lim, lim)
            if slot == mover and rnd.random() < 0.7:
                # skating at the centre of the cluster: a contact
                vx = max(-0x7fff, min(0x7fff, (cx - x) * rnd.randrange(0x100, 0x600) or rnd.randrange(-lim, lim)))
                vy = max(-0x7fff, min(0x7fff, (cy - y) * rnd.randrange(0x100, 0x600) or rnd.randrange(-lim, lim)))
            f = {'x': x << 16 | rnd.randrange(0x10000), 'y': y << 16 | rnd.randrange(0x10000),
                 'vx': vx, 'vy': vy,
                 'speed': rnd.choice((rnd.randrange(0, 0x40), rnd.randrange(0, 8))), 'heading': rnd.randrange(8) << 16 | rnd.randrange(0x10000),
                 'want_dir': rnd.randrange(9), 'target_x': rnd.randrange(-150, 151), 'target_y': rnd.randrange(-250, 251)}
            if slot == 14:
                f['frame'] = rnd.choice((0x430, 0x44f, 0x450, 0x467))
            else:
                f.update({'line_slot': -1 if slot == 16 else (0 if slot in (0, 6) else rnd.randrange(1, 6)),
                          'frame': rnd.choice(frames), 'flags4': rnd.choice((0, 8)),
                          'flags': (0x40 if 6 <= slot < 12 else 0) | rnd.choice((0, 0, 0, 0x08, 0x10, 0x20)) |
                          rnd.choice((0, 0x80)) | (0x04 if rnd.random() < 0.03 else 0),
                          'flags2': rnd.choice((0, 0, 0, 0, 1, 0x10, 2)) | (0x20 if rnd.random() < 0.03 else 0),
                          'roster': rnd.randrange(0, 20), 'weight': rnd.randrange(140, 230),
                          'speed_skill': rnd.randrange(0, 16), 'stamina': rnd.randrange(0, 16),
                          'check_skill': rnd.randrange(0, 16), 'aggression': rnd.randrange(0, 16),
                          'goalie_skill': rnd.randrange(0, 16), 'anim': rnd.choice(anims), 'anim_pos': rnd.randrange(0, 6),
                          'anim_hold': rnd.randrange(-1, 4), 'hit_by': rnd.choice((0, 3, -1)),
                          'state_sp': rnd.randrange(8), 'stack': rnd.choice((0, 0x12121212, 0x01020304)),
                          'stack2': rnd.choice((0, 0x12121212)), 'timer_d': rnd.randrange(0, 4)})
            put_fields(rec, f)
            struct.pack_into('<ii', rec, 0x74, f['x'], f['y'])
            emu.write(ENTITIES + slot * 0x80, rec)
        emu.call(SORT_DRAW_ORDER2)
        for slot in cluster:
            rec = bytearray(emu.read(ENTITIES + slot * 0x80, 0x80))
            if slot == mover or rnd.random() < 0.2:
                x0, y0 = struct.unpack_from('<ii', rec, 0)
                vx, vy = struct.unpack_from('<hh', rec, 0xc)
                struct.pack_into('<ii', rec, 0x74, x0, y0)
                struct.pack_into('<ii', rec, 0, x0 + vx * 16, y0 + vy * 16)
                emu.write(ENTITIES + slot * 0x80, rec)
            befores[slot] = entity_fields(emu, slot)
            befores[slot]['prev'] = list(struct.unpack_from('<ii', rec, 0x74))
        carrier = rnd.choice((-1, -1, mover, rnd.choice(cluster)))
        emu.write(PUCK + 0x42, bytes([carrier & 0xff]))
        g = {'game_flags': rnd.choice((0, 0, 0, 0, 1, 0x10, 8)), 'options': rnd.choice((0x1f, 0x1f, 0x1b, 0x0e, 0x11)),
             'period': rnd.choice((0, 1, 2, 3)), 'settings2': rnd.choice((0, 2)), 'breakaway': rnd.choice((0, 0, 1)),
             'defenders_ahead': rnd.choice((0, 1)), 'penalty_shot_slot': rnd.choice((-1, -1, -1, 3)),
             'penalty_shot_user': rnd.choice((0, -1)), 'crowd_hit_toggle': rnd.choice((0, 1)), 'ref_hits': rnd.randrange(3),
             'box_home': rnd.choice((0, 1, 8)), 'box_away': rnd.choice((0, 2, 8)),
             'user1_slot': rnd.choice((-1, mover, rnd.choice(cluster))), 'crowd': rnd.randrange(0, 1100),
             'excitement': rnd.randrange(0, 100), 'last_impact': rnd.randrange(0, 0x30), 'action_flags': rnd.choice((0, 0xc)),
             'puck_in_net': 0, 'puck': [rnd.randrange(-150, 151), rnd.randrange(-250, 251)]}
        emu.write(GAME_FLAGS, bytes([g['game_flags']]))
        emu.write(OPTION_FLAGS, struct.pack('<I', g['options']))
        for n, a, sz in CHECK_GLOBALS:
            emu.write(a, struct.pack('<' + _FMT[sz], g[n] if sz < 0 else g[n] & ((1 << (8 * sz)) - 1)))
        if 14 not in cluster:
            puck = bytearray(emu.read(PUCK, 0x80))
            put_fields(puck, {'x': g['puck'][0] << 16, 'y': g['puck'][1] << 16})
            emu.write(PUCK, puck)
        seed = rnd.getrandbits(32)
        emu.write(SEED, struct.pack('<I', seed))
        order = draw_order(emu)
        del calls[:]
        other = rnd.choice([s_ for s_ in cluster if s_ != mover])
        strength = rnd.randrange(0, 0x30)
        if mode == 'move':
            x = struct.unpack('<h', emu.read(ENTITIES + mover * 0x80 + 2, 2))[0]
            y = struct.unpack('<h', emu.read(ENTITIES + mover * 0x80 + 6, 2))[0]
            emu.call(MOVE_ENTITY, eax=ENTITIES + mover * 0x80, edx=x & 0xffffffff, ebx=y & 0xffffffff)
        elif mode == 'body':
            if other == 14:
                other = mover
                mode = 'none'
            else:
                emu.call(RESOLVE_BODY_CHECK, eax=ENTITIES + mover * 0x80, edx=ENTITIES + other * 0x80, ebx=strength)
        else:
            emu.call(KNOCK_DOWN, eax=ENTITIES + other * 0x80, edx=ENTITIES + mover * 0x80)
        out.append({'mode': mode, 'mover': mover, 'other': other, 'strength': strength,
                    'carrier': carrier, 'globals': g, 'teams': teams, 'seed': seed,
                    'before': {str(s_): v for s_, v in befores.items()}, 'order': order,
                    'after': {str(s_): entity_fields(emu, s_) for s_ in cluster}, 'order_after': draw_order(emu),
                    'calls': [list(c) for c in calls], 'carrier_after': struct.unpack('<b', emu.read(PUCK + 0x42, 1))[0],
                    'game_flags_after': emu.read(GAME_FLAGS, 1)[0],
                    'globals_after': {n: struct.unpack('<' + _FMT[sz], emu.read(a, abs(sz)))[0] for n, a, sz in CHECK_GLOBALS},
                    'hits_after': [struct.unpack('<h', emu.read(t + 0x24, 2))[0] for t in TEAM_RECORDS],
                    'final_seed': struct.unpack('<I', emu.read(SEED, 4))[0]})
        for a, n in ((GAME_FLAGS, 1), (OPTION_FLAGS, 4), (PENALTY_SHOT_SLOT, 4), (BREAKAWAY_FLAG, 4), (MISC_FLAGS, 4)):
            emu.write(a, b'\0' * n)
        emu.write(PENALTY_SHOT_SLOT, struct.pack('<i', -1))
    for h in hooks:
        emu.unstub(h)
    return out


UPDATE_GLOBALS = (('crowd', CROWD_NOISE + 2, -2), ('excitement', EXCITEMENT + 2, -2), ('breakaway', BREAKAWAY_FLAG, -4),
                  ('defenders_ahead', DEFENDERS_AHEAD, -4), ('penalty_shot_slot', PENALTY_SHOT_SLOT, -4),
                  ('penalty_shot_timer', PENALTY_SHOT_TIMER, -4), ('penalty_shot_team', PENALTY_SHOT_TEAM, -4),
                  ('penalty_shot_phase', PENALTY_SHOT_PHASE, -4), ('penalty_shot_active', PENALTY_SHOT_ACTIVE, -4),
                  ('penalty_shot_setup', PENALTY_SHOT_SETUP, -4), ('spot_x', PENALTY_SHOT_SPOT, -2),
                  ('spot_y', PENALTY_SHOT_SPOT + 4, -2), ('user1_slot', USER_SLOTS, -2), ('user2_slot', USER_SLOTS + 2, -2),
                  ('user1_team', USER_SLOTS + 4, -2), ('user2_team', USER_SLOTS + 6, -2),
                  ('last_touch_slot', LAST_TOUCH_SLOT, -2), ('last_touch_y', LAST_TOUCH_SLOT + 2, -2),
                  ('last_touch_x', LAST_TOUCH_SLOT + 4, -2), ('icing_flags', ICING_STATE + 2, 1), ('icing_shooter', ICING_STATE + 3, 1),
                  ('pred0_x', GOAL_PREDICTION + 2, -2), ('pred0_steps', GOAL_PREDICTION + 4, -2),
                  ('pred1_x', GOAL_PREDICTION + 6, -2), ('pred1_steps', GOAL_PREDICTION + 8, -2),
                  ('goal_timer', PUCK + 0x26, -2), ('stuck_timer', PUCK + 0x28, -2), ('last_passer', LAST_PASSER, -2),
                  ('pass_target', SHOT_POWER + 2, -2), ('last_shooter', LAST_SHOOTER, -2), ('stop_flags', STOP_FLAGS, 2),
                  ('misc_flags', MISC_FLAGS, 1), ('action_flags', ACTION_FLAGS, 1))


def update_cases(emu, rnd, base, calls):
    """puck_update: the goal line prediction, the puck on the carrier's stick (update_carrier),
    check_icing, check_offside (note_breakaway, count_defenders_ahead), update_offside_flags, the
    penalty shot timer (end_penalty_shot), the frozen puck, the flat disc and puck_check_players,
    among the players of both teams all over the rink"""
    def slot_of(eax):
        return ((eax & 0xffffffff) - ENTITIES) // 0x80
    hooks = [emu.stub(INJURY_CHECK, lambda eax: (calls.append(['injury_check', slot_of(eax)]), 1)[1]),
             emu.stub(INJURE_PLAYER, lambda eax: calls.append(['injure_player', slot_of(eax)])),
             emu.stub(BENCH_CHEER, lambda eax: calls.append(['bench_cheer', eax & 0xffffffff])),
             emu.stub(START_STOPPAGE, lambda eax: calls.append(['start_stoppage',
                                                                struct.unpack('<h', struct.pack('<H', eax & 0xffff))[0]]))]
    frames = list(range(0, 0x284)) + list(range(0x294, 0x2da)) + list(range(0x378, 0x468))
    out = []
    for k in range(800):
        emu.write(ENTITIES, base)
        game = rnd.choice((0, 0, 0, 0, 1, 2, 2, 3, 0x10))
        switched = game & 2
        teams = []
        for ti, t in enumerate(TEAM_RECORDS):
            f = {'flags': rnd.choice((0, 0, 0x10, 8, 0x18)), 'nearest': rnd.choice((0x10, 0x30, 0xffff)),
                 'breakaways': rnd.randrange(5), 'skaters': rnd.choice((6, 6, 5)), 'goalie_request': rnd.choice((0, 0, -0x100)),
                 'shots': rnd.randrange(20), 'carrier0': rnd.choice((-1, rnd.randrange(20))), 'carrier1': -1, 'carrier2': -1,
                 'faceoffs_won': 0, 'offensive_faceoffs': 0, 'pp_shots': 0, 'passes_completed': rnd.randrange(9),
                 'energy': rnd.choice((0x1000, 0xc00))}
            team_put(emu, t, f)
            emu.write(t + 0x1c, struct.pack('<h', f['breakaways']))
            emu.write(t + 0x3e, struct.pack('<i', f['nearest']))
            emu.write(t + 0x46, struct.pack('<28h', *([f['energy']] * 28)))
            emu.write(t + 0x7e, struct.pack('<28h', *([-1] * 28)))
            emu.write(t + 0xf6, struct.pack('<I', ENTITIES + ti * 6 * 0x80))     # the team's first player
            teams.append(f)
        # the puck: crossing a blue line or the red line, standing still, or anywhere
        mode = rnd.choice(('blue', 'blue', 'red', 'still', 'any'))
        if mode == 'blue':
            line = rnd.choice((0x4a, -0x4a))
            py = line + rnd.choice((0, 1, 2, -1)) * (1 if line > 0 else -1)
            pprev = line - rnd.randrange(1, 6) * (1 if line > 0 else -1)
        elif mode == 'red':
            py = rnd.choice((0, 1, -1, 2))
            pprev = -py + rnd.choice((-1, 1)) * rnd.randrange(1, 5)
        else:
            py = rnd.randrange(-0x110, 0x111)
            pprev = py if mode == 'still' else py + rnd.randrange(-4, 5)
        px = rnd.randrange(-0xb0, 0xb1)
        pxprev = px if mode == 'still' else px + rnd.randrange(-4, 5)
        puck = bytearray(emu.read(PUCK, 0x80))
        put_fields(puck, {'x': px << 16 | rnd.randrange(0x10000), 'y': py << 16 | rnd.randrange(0x10000),
                          'z': rnd.choice((0, 0, 0, rnd.randrange(1, 0x14))) << 16,
                          'vx': rnd.choice((0, rnd.randrange(-0x3000, 0x3000))), 'vy': rnd.choice((0, rnd.randrange(-0x3000, 0x3000))),
                          'vz': rnd.choice((0, rnd.randrange(-0x300, 0x300))), 'frame': rnd.choice((0x430, 0x438, 0x450, 0x460)),
                          'timer_c': rnd.choice((0, 0, 4)), 'anim_pos': rnd.randrange(0, 14), 'spin': rnd.randrange(8)})
        struct.pack_into('<ii', puck, 0x74, pxprev << 16, pprev << 16)
        emu.write(PUCK, puck)
        for slot in range(12):
            rec = bytearray(emu.read(ENTITIES + slot * 0x80, 0x80))
            near = rnd.random() < 0.3
            x = px + rnd.randrange(-12, 13) if near else rnd.randrange(-0x90, 0x91)
            y = py + rnd.randrange(-12, 13) if near else (rnd.choice((1, -1)) * rnd.randrange(0x40, 0x60) if rnd.random() < 0.4
                                                         else rnd.randrange(-0xf0, 0xf1))
            up = (slot < 6) != bool(switched)
            f = {'x': x << 16 | rnd.randrange(0x10000), 'y': y << 16 | rnd.randrange(0x10000),
                 'vx': rnd.randrange(-0x1800, 0x1800), 'vy': rnd.randrange(-0x1800, 0x1800),
                 'heading': rnd.randrange(8) << 16, 'frame': rnd.choice(frames), 'flags4': rnd.choice((0, 8)),
                 'flags': (0x80 if up else 0) | (0x40 if slot >= 6 else 0) | rnd.choice((0, 0, 8, 0x20)),
                 'flags2': rnd.choice((0, 0, 0, 0x80, 4, 0x10)),
                 'line_slot': (0 if slot in (0, 6) else rnd.randrange(1, 6)) if rnd.random() < 0.92 else -1,
                 'roster': rnd.randrange(0, 20), 'anim': rnd.choice((0, 0, 0x289, 0x621, 0xb1, 0x84b)),
                 'timer_c': rnd.choice((0, 0, 0, 3)), 'weight': rnd.randrange(140, 230),
                 'shot_skill': rnd.randrange(16), 'pass_skill': rnd.randrange(16), 'check_skill': rnd.randrange(16),
                 'goalie_skill': rnd.randrange(16), 'aggression': rnd.randrange(16), 'speed': rnd.randrange(0x30)}
            put_fields(rec, f)
            struct.pack_into('<ii', rec, 0x74, f['x'], f['y'])
            emu.write(ENTITIES + slot * 0x80, rec)
        emu.call(SORT_DRAW_ORDER2)
        carrier = -1
        if rnd.random() < 0.3:
            carrier = rnd.choice([s_ for s_ in range(12)])
        emu.write(PUCK + 0x42, bytes([carrier & 0xff]))
        active = rnd.random() < 0.2
        g = {'crowd': rnd.randrange(0, 1100), 'excitement': rnd.randrange(100), 'breakaway': rnd.choice((0, 1)),
             'defenders_ahead': rnd.choice((0, 1)), 'penalty_shot_slot': rnd.choice((-1, 3)) if active else -1,
             'penalty_shot_timer': rnd.choice((0, 0x1c, 0x1d, 5)), 'penalty_shot_team': rnd.choice((0, 1)),
             'penalty_shot_phase': rnd.choice((0, 1)) if active else 0, 'penalty_shot_active': 1 if active else 0,
             'penalty_shot_setup': 1 if active and rnd.random() < 0.5 else 0, 'spot_x': rnd.randrange(-0x60, 0x61),
             'spot_y': rnd.randrange(-0xb8, 0xb9), 'user1_slot': rnd.choice((-1, 2, 4)), 'user2_slot': rnd.choice((-1, 8)),
             'user1_team': rnd.choice((0, 1)), 'user2_team': rnd.choice((0, 2)),
             'last_touch_slot': rnd.choice((-1, 2, 3, 8, 9)), 'last_touch_y': rnd.randrange(-0xe0, 0xe1),
             'last_touch_x': rnd.randrange(-0x90, 0x91), 'icing_flags': rnd.choice((0, 4, 5, 6, 7)), 'icing_shooter': rnd.choice((2, 9)),
             'pred0_x': rnd.randrange(-0x50, 0x51), 'pred0_steps': rnd.choice((-1, 30, 0)), 'pred1_x': rnd.randrange(-0x50, 0x51),
             'pred1_steps': rnd.choice((-1, 7)), 'goal_timer': rnd.choice((0, 0, 3, -1)), 'stuck_timer': rnd.choice((0x78, 1, 0, 0x30)),
             'last_passer': rnd.choice((-1, 3)), 'pass_target': rnd.choice((-1, 4, 9)), 'last_shooter': rnd.choice((2, 9)),
             'stop_flags': rnd.choice((0, 0x10, 0x20)), 'misc_flags': rnd.choice((0, 0x10)), 'action_flags': rnd.choice((0, 0xc)),
             'game_flags': game, 'options': rnd.choice((0, 2, 8, 0xa, 0x1f, 0x1b))}
        if g['last_touch_slot'] < 0:
            # (two_line_pass_check would queue the infraction against entities[-1]; the port takes 0)
            g['pred0_x'] = g['pred1_x'] = 0x50
        emu.write(GAME_FLAGS, bytes([game]))
        emu.write(OPTION_FLAGS, struct.pack('<I', g['options']))
        for n, a, sz in UPDATE_GLOBALS:
            emu.write(a, struct.pack('<' + _FMT[sz], g[n] if sz < 0 else g[n] & ((1 << (8 * sz)) - 1)))
        seed = rnd.getrandbits(32)
        emu.write(SEED, struct.pack('<I', seed))
        order = draw_order(emu)
        befores = {str(s_): entity_fields(emu, s_) for s_ in range(17)}
        for s_ in range(17):
            befores[str(s_)]['prev'] = list(struct.unpack('<iii', emu.read(ENTITIES + s_ * 0x80 + 0x74, 12)))
        del calls[:]
        emu.call(PUCK_UPDATE, eax=PUCK)
        out.append({'carrier': carrier, 'globals': g, 'teams': teams, 'seed': seed, 'order': order, 'before': befores,
                    'after': {str(s_): entity_fields(emu, s_) for s_ in range(17)},
                    'carrier_after': struct.unpack('<b', emu.read(PUCK + 0x42, 1))[0], 'calls': [list(c) for c in calls],
                    'globals_after': {n: struct.unpack('<' + _FMT[sz], emu.read(a, abs(sz)))[0] for n, a, sz in UPDATE_GLOBALS},
                    'teams_after': [dict(team_get(emu, t), breakaways=struct.unpack('<h', emu.read(t + 0x1c, 2))[0])
                                    for t in TEAM_RECORDS],
                    'final_seed': struct.unpack('<I', emu.read(SEED, 4))[0]})
        for a, n in ((GAME_FLAGS, 1), (OPTION_FLAGS, 4), (PENALTY_SHOT_ACTIVE, 4), (PENALTY_SHOT_SETUP, 4),
                     (PENALTY_SHOT_PHASE, 4), (STOP_FLAGS, 2), (MISC_FLAGS, 4), (BREAKAWAY_FLAG, 4)):
            emu.write(a, b'\0' * n)
        emu.write(PENALTY_SHOT_SLOT, struct.pack('<i', -1))
    for h in hooks:
        emu.unstub(h)
    return out


def physics_cases(exe):
    emu = PortEmu(exe)
    rnd = random.Random(1993)
    out = {'distance': [], 'boards': []}
    for _ in range(200):
        dx = rnd.randrange(-400, 401)
        dy = rnd.randrange(-600, 601)
        if rnd.random() < 0.1:
            dx = 0
        out['distance'].append([dx, dy, emu.call(APPROX_DISTANCE, stack=(dx & 0xffffffff, dy & 0xffffffff)) & 0xffff,
                                emu.call(DIRECTION8, eax=dx & 0xffffffff, edx=dy & 0xffffffff) & 0xff])
    sfx = []
    goals = []
    infractions = []
    calls = []

    def on_sfx(eax):
        sfx.append(eax & 0xffff)
        calls.append(['play_sfx', eax & 0xffff])

    def on_infraction(name):
        def f(eax):
            e, t = (eax - ENTITIES) // 0x80, emu.uc.reg_read(UC_X86_REG_EDX) & 0xff
            infractions.append([e, t])
            calls.append([name, e, t])
        return f
    emu.stub(PLAY_SFX, on_sfx)
    emu.stub(SCORE_GOAL, lambda eax: goals.append((eax - ENTITIES) // 0x80))
    emu.stub(QUEUE_INFRACTION, on_infraction('queue_infraction'))
    emu.stub(MAYBE_QUEUE_INFRACTION, on_infraction('maybe_queue_infraction'))
    emu.call(ENTITIES_INIT)
    base = emu.read(ENTITIES, 17 * 0x80)
    for k in range(300):
        emu.write(ENTITIES, base)
        slot = 14 if k % 2 == 0 else (3 if k % 4 == 1 else 8)
        rec = bytearray(emu.read(ENTITIES + slot * 0x80, 0x80))
        hw = struct.unpack_from('<h', rec, 0x66)[0]
        hh = struct.unpack_from('<h', rec, 0x68)[0]
        w, h = 0xa0 - hw, 0x108 - hh
        region = rnd.randrange(3)
        if region == 0:          # the side boards
            x = rnd.choice((-1, 1)) * rnd.randrange(w - 6, w + 8)
            y = rnd.randrange(-(h - 70), h - 70)
        elif region == 1:        # the corners
            x = rnd.choice((-1, 1)) * rnd.randrange(w - 70, w + 4)
            y = rnd.choice((-1, 1)) * rnd.randrange(h - 70, h + 4)
        else:                    # the end boards, away from the nets
            x = rnd.choice((-1, 1)) * rnd.randrange(0x48, w - 60)
            y = rnd.choice((-1, 1)) * rnd.randrange(h - 6, h + 6)
        lim = 0x3000 if slot == 14 else 0x1800
        vx = rnd.randrange(-lim, lim)
        vy = rnd.randrange(-lim, lim)
        z = 0 if slot != 14 or rnd.random() < 0.6 else rnd.randrange(0, 0x12)
        fields = {'x': (x << 16) | rnd.randrange(0x10000), 'y': (y << 16) | rnd.randrange(0x10000), 'z': z << 16,
                  'vx': vx, 'vy': vy, 'vz': rnd.randrange(-0x400, 0x400) if z else 0,
                  'speed': rnd.randrange(0, 21), 'anim_pos': rnd.randrange(0, 14)}
        fields['prev_x'] = fields['x'] - vx * 16
        fields['prev_y'] = fields['y'] - vy * 16
        for n, o, sz in ENTITY_FIELDS:
            if n in fields:
                struct.pack_into('<' + _FMT[sz].lower() if sz < 0 else '<' + _FMT[sz], rec, o,
                                 fields[n] if sz < 0 else fields[n] & ((1 << (8 * sz)) - 1))
        struct.pack_into('<i', rec, 0x74, fields['prev_x'])
        struct.pack_into('<i', rec, 0x78, fields['prev_y'])
        struct.pack_into('<i', rec, 0x7c, fields['z'])
        emu.write(ENTITIES + slot * 0x80, rec)
        carrier = rnd.choice((-1, -1, 3, 8))
        emu.write(ENTITIES + 14 * 0x80 + 0x42, bytes([carrier & 0xff]))
        seed = rnd.getrandbits(32)
        emu.write(SEED, struct.pack('<I', seed))
        emu.write(COLL_HALF_W, struct.pack('<hh', hw, hh))
        del sfx[:]
        before = entity_fields(emu, slot)
        emu.call(COLLIDE_BOARDS, eax=ENTITIES + slot * 0x80, edx=x & 0xffffffff, ebx=y & 0xffffffff)
        out['boards'].append({'slot': slot, 'carrier': carrier, 'seed': seed, 'px': x, 'py': y, 'hw': hw, 'hh': hh,
                              'prev_x': fields['prev_x'], 'prev_y': fields['prev_y'], 'before': before,
                              'after': entity_fields(emu, slot), 'sfx': list(sfx),
                              'final_seed': struct.unpack('<I', emu.read(SEED, 4))[0]})
    out['skating'] = skating_cases(emu, rnd, base)
    out['nets'] = net_cases(emu, rnd, base, sfx, goals, infractions)
    out['contacts'] = contact_cases(emu, rnd, base, sfx)
    out['animation'] = animation_cases(emu, rnd, base, sfx)
    out['pickup'] = pickup_cases(emu, rnd, base, calls)
    out['checks'] = check_cases(emu, rnd, base, calls)
    out['update'] = update_cases(emu, rnd, base, calls)
    # the records after the call keep only the fields that changed (the test merges them over the
    # records before the call)
    for cases in out.values():
        for c in cases if isinstance(cases, list) else ():
            if isinstance(c, dict) and 'after' in c and 'before' in c:
                if 'x' in c['after']:
                    c['after'] = {k: v for k, v in c['after'].items() if c['before'].get(k) != v}
                else:
                    c['after'] = {s_: {k: v for k, v in a.items() if c['before'][s_].get(k) != v}
                                  for s_, a in c['after'].items()}
    # the entities as entities_init leaves them (every case starts from these); the records before
    # a call keep only the fields that differ from them (the test fills in the others)
    emu.write(ENTITIES, base)
    out['base'] = [dict(entity_fields(emu, i), prev=list(struct.unpack('<iii', emu.read(ENTITIES + i * 0x80 + 0x74, 12))))
                   for i in range(17)]

    def from_base(rec, slot):
        return {k: v for k, v in rec.items() if out['base'][slot].get(k) != v}
    for cases in out.values():
        for c in cases if isinstance(cases, list) else ():
            if isinstance(c, dict) and 'before' in c:
                if 'x' in c['before']:
                    c['before'] = from_base(c['before'], c['slot'])
                else:
                    c['before'] = {s_: from_base(b, int(s_)) for s_, b in c['before'].items()}
    return out


def main():
    if len(sys.argv) != 3:
        print(__doc__ or 'golden.py GAMEDIR OUTDIR')
        sys.exit(2)
    gamedir, outdir = sys.argv[1], sys.argv[2]
    exe = os.path.join(gamedir, 'HOCKEY.EXE')
    os.makedirs(outdir, exist_ok=True)
    for name, data in (('rng', rng_cases(exe)), ('fm_driver', fm_cases(exe, gamedir)),
                       ('pc_speaker', pc_cases(exe, gamedir)), ('physics', physics_cases(exe))):
        path = os.path.join(outdir, name + '.json')
        with open(path, 'w') as f:
            json.dump(data, f, separators=(',', ':'), sort_keys=True)
            f.write('\n')
        print('wrote', path)


if __name__ == '__main__':
    main()
