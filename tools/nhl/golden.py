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
#                    the carried puck, icing, offside, the penalty shot timer, the frozen puck);
#                    passes and shots (do_pass, pass_lane_ok, pass_lead, start_shot, shot_control,
#                    do_shot, shot_setup).
#                    The records after a call keep the fields that changed.
#
# The patch bank is put in the emulator's memory the way loadpatches leaves it: the .PAT file at
# snd_patch_bank, each record's +0x10 pointing at its timbre from the .TIM files.
#
#   python3 tools/nhl/golden.py re/nhl_hockey godot/nhl_hockey/tests/golden
#
# The large files are written compressed (.json.gz); tools/nhl/golden_check.py compares two sets.
#
import gzip
import hashlib
import json
import os
import random
import struct
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from leemu import LEEmu, STACK_TOP            # noqa: E402

from unicorn import UC_HOOK_CODE, UC_HOOK_INSN    # noqa: E402
from unicorn.x86_const import (UC_X86_INS_IN, UC_X86_INS_OUT, UC_X86_REG_GDTR, UC_X86_REG_DS,  # noqa: E402
                               UC_X86_REG_ES, UC_X86_REG_SS, UC_X86_REG_FS, UC_X86_REG_GS,
                               UC_X86_REG_EAX, UC_X86_REG_EDX, UC_X86_REG_ESP, UC_X86_REG_EIP, UC_X86_REG_EBX,
                               UC_X86_REG_ECX)

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
SND_PLAY_SFX = 0x8f61d                         # stubbed: the sample to the sound driver
KMS_PLAY = 0x8f270                             # stubbed: the organ (a KMS song) with a wave table card
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

    def stub(self, addr, fn, pop=0):
        '''Replaces the routine at addr: fn(eax) is called instead and the routine returns (with
        fn's result in eax unless it is None; `pop` bytes of stack arguments removed, as a `ret n`
        does); returns the hook for unstub'''
        def hook(uc, address, size, user):
            r = fn(uc.reg_read(UC_X86_REG_EAX))
            if r is not None:
                uc.reg_write(UC_X86_REG_EAX, r & 0xffffffff)
            sp = uc.reg_read(UC_X86_REG_ESP)
            uc.reg_write(UC_X86_REG_EIP, struct.unpack('<I', uc.mem_read(sp, 4))[0])
            uc.reg_write(UC_X86_REG_ESP, sp + 4 + pop)
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
                 ('state_sp', 0x1c, -2), ('stack', 0x1e, 4), ('stack2', 0x22, 4), ('timer_a', 0x26, -2),
                 ('dir_timer', 0x29, -1), ('timer_e', 0x4a, -2), ('timer_f', 0x4c, -2), ('puck_dist', 0x4e, -2),
                 ('puck_dist_sq', 0x50, -2), ('puck_dir', 0x52, 1), ('pass_ok', 0x53, 1), ('side', 0x54, -1),
                 ('reaction', 0x59, 1), ('awareness', 0x5a, 1), ('accuracy', 0x5c, 1), ('number', 0x5e, 1),
                 ('next_line', 0x42, -1), ('next_roster', 0x43, -1), ('w48', 0x48, -2))
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
LINE_TABLES = (0xdc200, 0xdabf0)               # team +0xda: the line tables of the match (TEAMS.DB +0xbc)
PLAYER_RATINGS = 0xdaca0                       # team +0xde: 25 x 0x14 rating bytes per team (+0x1f4 away)
POS_LISTS = 0xe9cec                            # build_lines: 11 lists x 2 teams x 25 bytes
LINEUP_REQ = 0xe0384                           # lineup_req_roster[6], lineup_req_slot[6]
GOALIE_MENU = (0xcdc47, 0xcdc60, 0xcdc79, 0xcdc97, 0xcdcb0, 0xcdcc9)
ROSTERS = 0xdb3a8                              # 2 x 28 player records of 0x27 bytes, a status byte first
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
DO_PASS = 0x54df4
PASS_LANE_OK = 0x54c09                        # (passer, receiver) -> bool
PASS_LEAD = 0x551cf                           # (receiver)
START_SHOT = 0x5786e
SHOT_CONTROL = 0x578fa                        # scratch inputs: e03bc dir, e03c0 pressed, e03ac changed
DO_SHOT = 0x57c0b
SHOT_SETUP = 0x57a98
PENDING_DIR = 0xc90a4
ONE_TIMER = 0xcc0f4
SCRATCH = (0xe03bc, 0xe03c0, 0xe03ac)
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
        # the scratch words as an earlier routine left them (skating_turn and skating_accelerate
        # leave theirs)
        scratch = [(seed >> 3) & 0xffff, (seed >> 11) & 0xffff, (seed >> 7) & 0xffff]
        emu.write(SCRATCH[0], struct.pack('<H', scratch[0]))
        emu.write(SCRATCH[1], struct.pack('<H', scratch[1]))
        emu.write(SCRATCH[2], struct.pack('<I', scratch[2]))
        d = rnd.choice((0, 1, 2, 3, 4, 5, 6, 7, 8, 9))
        before = entity_fields(emu, slot)
        emu.call(APPLY_SKATING, eax=ENTITIES + slot * 0x80, edx=d)
        out.append({'slot': slot, 'dir': d, 'energy': energy, 'carrier': carrier,
                    'puck': [struct.unpack_from('<h', puck, 2)[0], struct.unpack_from('<h', puck, 6)[0],
                             struct.unpack_from('<h', puck, 0xe)[0]],
                    'game_flags': game, 'stop_flags': stop, 'whistle': whistle, 'options': options,
                    'seed': seed, 'before': before, 'after': entity_fields(emu, slot),
                    'energy_after': struct.unpack('<h', emu.read(team + 0x46 + f['roster'] * 2, 2))[0],
                    'final_seed': struct.unpack('<I', emu.read(SEED, 4))[0], 'scratch': scratch,
                    'scratch_after': [struct.unpack('<h', emu.read(SCRATCH[0], 2))[0], struct.unpack('<h', emu.read(SCRATCH[1], 2))[0],
                                      struct.unpack('<I', emu.read(SCRATCH[2], 4))[0]]})
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


SHOOT_GLOBALS = (('pending_dir', PENDING_DIR, -2), ('shot_power', SHOT_POWER, -2), ('pass_target', SHOT_POWER + 2, -2),
                 ('last_passer', LAST_PASSER, -2), ('last_shooter', LAST_SHOOTER, -2), ('action_flags', ACTION_FLAGS, 1),
                 ('stop_flags', STOP_FLAGS, 1), ('one_timer', ONE_TIMER, -4), ('breakaway', BREAKAWAY_FLAG, -4),
                 ('defenders_ahead', DEFENDERS_AHEAD, -4), ('user1_slot', USER_SLOTS, -2), ('user2_slot', USER_SLOTS + 2, -2),
                 ('user1_team', USER_SLOTS + 4, -2), ('user2_team', USER_SLOTS + 6, -2),
                 ('penalty_shot_active', PENALTY_SHOT_ACTIVE, -4))


def shoot_cases(emu, rnd, base, calls):
    """passing and shooting: do_pass (pass_to_entity, pass_lead, pass_lane_ok, the blind pass, the
    goalie's clearance and the users following it), pass_lane_ok and pass_lead called directly,
    start_shot, shot_control (its scratch inputs given), do_shot (shot_setup, the power, the
    scatter, the lift) and shot_setup"""
    frames = list(range(0, 0x284)) + list(range(0x294, 0x2da)) + list(range(0x378, 0x468))
    out = []
    modes = ('pass', 'pass', 'lane', 'lead', 'start', 'control', 'control', 'shot', 'shot', 'shot', 'setup')
    for k in range(1100):
        mode = modes[k % len(modes)]
        emu.write(ENTITIES, base)
        game = rnd.choice((0, 0, 0, 0x10, 2))
        switched = game & 2
        teams = []
        for ti, t in enumerate(TEAM_RECORDS):
            f = {'energy': rnd.choice((0x1000, 0xc00, 0x800)), 'passes': rnd.randrange(20)}
            emu.write(t + 0x46, struct.pack('<28h', *([f['energy']] * 28)))
            emu.write(t + 0x26, struct.pack('<h', f['passes']))
            emu.write(t + 0x7e, struct.pack('<28h', *([-1] * 28)))
            emu.write(t + 0xf6, struct.pack('<I', ENTITIES + ti * 6 * 0x80))
            teams.append(f)
        px = rnd.randrange(-0x90, 0x91)
        py = rnd.randrange(-0xe0, 0xe1)
        shooter = rnd.choice((1, 2, 3, 4, 5, 7, 8, 9, 10, 11, 0, 6))
        for slot in range(12):
            rec = bytearray(emu.read(ENTITIES + slot * 0x80, 0x80))
            near = slot == shooter or rnd.random() < 0.25
            x = px + rnd.randrange(-6, 7) if near else rnd.randrange(-0x90, 0x91)
            y = py + rnd.randrange(-6, 7) if near else rnd.randrange(-0xf0, 0xf1)
            up = (slot < 6) != bool(switched)
            lim = rnd.choice((0x400, 0x1800, 0x3000))
            f = {'x': x << 16 | rnd.randrange(0x10000), 'y': y << 16 | rnd.randrange(0x10000),
                 'vx': rnd.choice((0, rnd.randrange(-lim, lim))), 'vy': rnd.choice((0, rnd.randrange(-lim, lim))),
                 'heading': rnd.randrange(8) << 16 | rnd.randrange(0x10000), 'frame': rnd.choice(frames),
                 'flags4': rnd.choice((0, 8)), 'flags': (0x80 if up else 0) | (0x40 if slot >= 6 else 0) | rnd.choice((0, 0, 8)),
                 'flags2': rnd.choice((0, 0, 0, 4)), 'line_slot': (0 if slot in (0, 6) else rnd.randrange(1, 6)) if rnd.random() < 0.93 else -1,
                 'roster': rnd.randrange(0, 20), 'anim': rnd.choice((0x3f9, 0x491, 0xdd3, 0xe2b, 0x289)),
                 'anim_pos': rnd.randrange(0, 0x10), 'shot_skill': rnd.randrange(16), 'pass_skill': rnd.randrange(16),
                 'save_result': 0, 'speed_skill': rnd.randrange(16)}
            put_fields(rec, f)
            rec[0x5c] = rnd.randrange(16)                    # shot accuracy
            rec[0x53] = rnd.choice((0, 0, 1))                # pass_ok
            struct.pack_into('<h', rec, 0x48, rnd.choice((-1, 2, 3, 8, 9)) if slot != shooter else rnd.choice((2, 3, 4) if slot < 6 else (8, 9, 10)))
            emu.write(ENTITIES + slot * 0x80, rec)
        puck = bytearray(emu.read(PUCK, 0x80))
        put_fields(puck, {'x': px << 16, 'y': py << 16, 'vx': rnd.randrange(-0x800, 0x800), 'vy': rnd.randrange(-0x800, 0x800),
                          'vz': rnd.choice((0, 0x2ff, 0x5ab)), 'z': 0})
        emu.write(PUCK, puck)
        emu.call(SORT_DRAW_ORDER2)
        carrier = shooter if rnd.random() < 0.85 else rnd.choice((-1, 3))
        emu.write(PUCK + 0x42, bytes([carrier & 0xff]))
        g = {'pending_dir': rnd.choice((0, 1, 2, 3, 4, 5, 6, 7, 8)), 'shot_power': rnd.choice((0xf, 0x14, 0x1a, 0x23, 0x2c)),
             'pass_target': rnd.choice((-1, 3)), 'last_passer': rnd.choice((-1, 2)), 'last_shooter': rnd.choice((-1, 9)),
             'action_flags': rnd.choice((0, 4, 8, 0xc)), 'stop_flags': rnd.choice((0, 0x10)), 'one_timer': rnd.choice((0, 1)),
             'breakaway': rnd.choice((0, 0, 1)), 'defenders_ahead': rnd.choice((0, 1)),
             'user1_slot': rnd.choice((-1, shooter, 2)), 'user2_slot': rnd.choice((-1, 8, shooter)),
             'user1_team': rnd.choice((1, 2)), 'user2_team': rnd.choice((0, 2, 1)),
             'penalty_shot_active': rnd.choice((0, 0, 0, 1)), 'game_flags': game,
             'scratch': [rnd.choice((8, 0, 2, 5, 7, 0x22, 0x13)), rnd.choice((0, 0, 0, 0x10, 0x40)), rnd.choice((0, 0x20, 0x20, 0x10))]}
        emu.write(GAME_FLAGS, bytes([game]))
        for n, a, sz in SHOOT_GLOBALS:
            emu.write(a, struct.pack('<' + _FMT[sz], g[n] if sz < 0 else g[n] & ((1 << (8 * sz)) - 1)))
        for a, v in zip(SCRATCH, g['scratch']):
            emu.write(a, struct.pack('<H', v))
        seed = rnd.getrandbits(32)
        emu.write(SEED, struct.pack('<I', seed))
        befores = {str(s_): entity_fields(emu, s_) for s_ in range(17)}
        extra = {str(s_): [emu.read(ENTITIES + s_ * 0x80 + 0x53, 1)[0], emu.read(ENTITIES + s_ * 0x80 + 0x5c, 1)[0],
                           struct.unpack('<h', emu.read(ENTITIES + s_ * 0x80 + 0x48, 2))[0],
                           struct.unpack('<b', emu.read(ENTITIES + s_ * 0x80 + 0x27, 1))[0]] for s_ in range(12)}
        receiver = rnd.choice([s_ for s_ in range(12) if s_ != shooter])
        if mode == 'lane' and rnd.random() < 0.7:
            # inside pass_lane_ok's window: a drop pass in the attacking zone, both skating up the ice
            receiver = rnd.choice([s_ for s_ in (range(1, 6) if shooter < 6 else range(7, 12)) if s_ != shooter])
            up = struct.unpack('<B', emu.read(ENTITIES + shooter * 0x80 + 0x44, 1))[0] & 0x80
            sign = 1 if up else -1
            ey = rnd.randrange(0x52, 0x77)
            ty = rnd.randrange(0x4f, ey)
            ex = rnd.randrange(-0x40, 0x41)
            for slot, x, y in ((shooter, ex, ey), (receiver, ex + rnd.randrange(-0x28, 0x29), ty)):
                rec = bytearray(emu.read(ENTITIES + slot * 0x80, 0x80))
                put_fields(rec, {'x': x << 16, 'y': (sign * y) << 16, 'vy': sign * rnd.randrange(0, 0x600),
                                 'vx': rnd.randrange(-0x600, 0x600), 'line_slot': rnd.randrange(1, 6)})
                emu.write(ENTITIES + slot * 0x80, rec)
            befores = {str(s_): entity_fields(emu, s_) for s_ in range(17)}
        del calls[:]
        e = ENTITIES + shooter * 0x80
        result = 0
        if mode == 'pass':
            emu.call(DO_PASS, eax=e)
        elif mode == 'lane':
            result = emu.call(PASS_LANE_OK, eax=e, edx=ENTITIES + receiver * 0x80) & 0xffff
        elif mode == 'lead':
            emu.call(PASS_LEAD, eax=ENTITIES + receiver * 0x80)
        elif mode == 'start':
            emu.call(START_SHOT, eax=e)
        elif mode == 'control':
            emu.call(SHOT_CONTROL, eax=e)
        elif mode == 'shot':
            emu.call(DO_SHOT, eax=e)
        else:
            emu.call(SHOT_SETUP, eax=e)
        out.append({'mode': mode, 'shooter': shooter, 'receiver': receiver, 'carrier': carrier, 'globals': g, 'teams': teams,
                    'seed': seed, 'before': befores, 'extra': extra,
                    'after': {str(s_): entity_fields(emu, s_) for s_ in range(17)},
                    'extra_after': {str(s_): [emu.read(ENTITIES + s_ * 0x80 + 0x53, 1)[0],
                                              struct.unpack('<b', emu.read(ENTITIES + s_ * 0x80 + 0x27, 1))[0]] for s_ in range(12)},
                    'result': result, 'carrier_after': struct.unpack('<b', emu.read(PUCK + 0x42, 1))[0],
                    'calls': [list(c) for c in calls],
                    'globals_after': {n: struct.unpack('<' + _FMT[sz], emu.read(a, abs(sz)))[0] for n, a, sz in SHOOT_GLOBALS},
                    'passes_after': [struct.unpack('<h', emu.read(t + 0x26, 2))[0] for t in TEAM_RECORDS],
                    'final_seed': struct.unpack('<I', emu.read(SEED, 4))[0]})
        for a, n in ((GAME_FLAGS, 1), (PENALTY_SHOT_ACTIVE, 4), (STOP_FLAGS, 2), (BREAKAWAY_FLAG, 4)):
            emu.write(a, b'\0' * n)
    return out


AI_HANDLERS = 0xc9161                         # ai_state_handlers[state]
CLOCK = 0xc90dc                               # clock_seconds, clock_sub
WHISTLE_TIMER_W = 0xc90d2
CAMERA_TARGET = 0xc90ac
CAMERA_XY = 0xc9098                           # camera x, y
DRAW_LINE_INDICATOR = 0x14afe
BREAKAWAY_LANE = 0xcc130                       # ai_breakaway: lane x, target y, trigger y, waypoint, side, heading
AI_GLOBALS = (('game_flags', GAME_FLAGS, 1), ('stop_flags', STOP_FLAGS, 1), ('misc_flags', MISC_FLAGS, 1),
              ('option_flags', OPTION_FLAGS, 1), ('settings2', SETTINGS2, 1), ('action_flags', ACTION_FLAGS, 1),
              ('user1_slot', USER_SLOTS, -2), ('user2_slot', USER_SLOTS + 2, -2), ('user1_team', USER_SLOTS + 4, -2),
              ('user2_team', USER_SLOTS + 6, -2), ('last_touch_slot', LAST_TOUCH_SLOT, -2),
              ('last_touch_y', LAST_TOUCH_SLOT + 2, -2), ('last_touch_x', LAST_TOUCH_SLOT + 4, -2),
              ('last_passer', LAST_PASSER, -2), ('last_shooter', LAST_SHOOTER, -2), ('pending_dir', PENDING_DIR, -2),
              ('shot_power', SHOT_POWER, -2), ('pass_target', SHOT_POWER + 2, -2), ('crowd', CROWD_NOISE + 2, -2),
              ('excitement', EXCITEMENT + 2, -2), ('breakaway', BREAKAWAY_FLAG, -4), ('defenders_ahead', DEFENDERS_AHEAD, -4),
              ('one_timer', ONE_TIMER, -4), ('penalty_shot_slot', PENALTY_SHOT_SLOT, -4),
              ('penalty_shot_active', PENALTY_SHOT_ACTIVE, -4), ('penalty_shot_setup', PENALTY_SHOT_SETUP, -4),
              ('penalty_shot_phase', PENALTY_SHOT_PHASE, -4), ('penalty_shot_team', PENALTY_SHOT_TEAM, -4),
              ('icing_flags', ICING_STATE + 2, 1), ('icing_shooter', ICING_STATE + 3, 1),
              ('pred0_x', GOAL_PREDICTION + 2, -2), ('pred0_steps', GOAL_PREDICTION + 4, -2),
              ('pred1_x', GOAL_PREDICTION + 6, -2), ('pred1_steps', GOAL_PREDICTION + 8, -2),
              ('period', PERIOD_IDX, -2), ('clock_seconds', CLOCK, -2), ('clock_sub', CLOCK + 2, -2),
              ('whistle_timer', WHISTLE_TIMER_W, -2), ('camera_target_x', CAMERA_TARGET, -2),
              ('camera_target_y', CAMERA_TARGET + 2, -2), ('last_impact', LAST_IMPACT, -2),
              ('crowd_hit_toggle', CROWD_HIT_TOGGLE, -2), ('ref_hits', REF_HITS, -2), ('box_home', PENALIZED_COUNT, 1),
              ('box_away', PENALIZED_COUNT + 1, 1), ('goalie_pass_mode', 0xc90aa, -2),
              ('breakaway_lane_x', BREAKAWAY_LANE, -4), ('breakaway_target_y', BREAKAWAY_LANE + 4, -4),
              ('breakaway_trigger_y', BREAKAWAY_LANE + 8, -4), ('breakaway_waypoint', BREAKAWAY_LANE + 12, -4),
              ('breakaway_lane_side', BREAKAWAY_LANE + 16, -4), ('breakaway_heading', BREAKAWAY_LANE + 20, -4),
              ('faceoff_x', 0xc90b2, -2), ('faceoff_y', 0xc90b4, -2),
              ('faceoff_ready0', 0xe0390, -2), ('faceoff_ready1', 0xe0394, -2), ('penalty_shot_timer', PENALTY_SHOT_TIMER, -4),
              ('injury_stoppage', 0xcbec6, -2), ('clip', 0xcbecc, -2), ('ref_phase', 0xc90d4, -2),
              ('ref_infraction', 0xc90d6, -2), ('ref_infraction_slot', 0xc90d8, -2), ('panel', 0xcbec0, -2),
              ('demo', 0xcc0ec, -4), ('session_mode', 0xc53fb, -4), ('milestone_gate', 0xe024c, 4), ('sound_card', 0xc541f, 1), ('sound_enabled', 0xd2430, 1), ('announce_time', 0xe9aac, -2),
              ('period_length', 0xe9ab8, -2), ('deferred', 0xc5840, -4), ('infraction_events', 0xcc0ac, -4),
              ('save_clip_shown', 0xe9a9e, -2), ('period_over', 0xcbc46, -2), ('goal_call', 0xe9ad3, 1),
              ('goal_team', 0xe9ad4, 1), ('goal_scorer', 0xe9ad5, 1), ('goal_a1', 0xe9ad6, 1), ('goal_a2', 0xe9ad7, 1),
              ('infraction0', 0xe9a16, 1), ('message', 0xcbec8, -2), ('message_timer', 0xcbeca, -2),
              ('lc_show0', 0xcbc56, -2), ('lc_show1', 0xcbc58, -2), ('lc_blink0', 0xcbc5a, -2), ('lc_blink1', 0xcbc5c, -2),
              ('lc_place0', 0xcbc5e, -2), ('lc_place1', 0xcbc60, -2), ('lc_line0', 0xcbc62, -2), ('lc_line1', 0xcbc64, -2),
              ('lc_timer0', 0xcbc66, -2), ('lc_timer1', 0xcbc68, -2), ('lc_prompt0', 0xcbc6a, -2), ('lc_prompt1', 0xcbc6c, -2),
              ('hotkey0', 0xe0304, -2), ('hotkey1', 0xe0306, -2), ('hotkey_line0', 0xe0380, -2), ('hotkey_line1', 0xe0382, -2),
              ('controls_blocked', 0xccc9c, -4), ('skip_wait', 0xcc0f0, -4), ('controller0', 0xc4d1c, 1),
              ('controller1', 0xc4d1d, 1), ('faceoff_dir0', 0xc90b6, -2), ('faceoff_dir1', 0xc90b8, -2),
              ('stoppage_timer', 0xc90ce, -2), ('announce_timer', 0xcc0b0, -2), ('penalty_box_mode', 0xcbc44, -2),
              ('second_timer', 0xc90d0, -2), ('tick24', 0xcc0d9, -1), ('tick_toggle', 0xcc0d8, 1),
              ('excitement_peak', 0xe9aa4, -2), ('excitement_sum', 0xe009c, -4), ('excitement_samples', 0xe9aa6, 2),
              ('lc_bar0', 0xcbc52, -2), ('lc_bar1', 0xcbc54, -2), ('penalty_shot_clock', 0xcc120, -4),
              ('goal_flags', 0xe9ab0, -2), ('puck_in_net', PUCK_IN_NET, 1), ('penalty_shot_roster', 0xcc100, -4),
              ('penalty_shot_spot_x', PENALTY_SHOT_SPOT, -4), ('penalty_shot_spot_y', PENALTY_SHOT_SPOT + 4, -4),
              ('series_announce', 0xccca0, 1), ('camera_x', CAMERA_XY, -2), ('camera_y', CAMERA_XY + 2, -2),
              ('camera_lead', 0xc90b0, -2), ('faceoff_digit', 0xe0398, -2), ('faceoff_side0', 0xe0392, -2),
              ('faceoff_side1', 0xe0396, -2), ('fade_in', 0xcbec4, -2), ('clip_frame', 0xcbece, -2),
              ('scorer_jumps', 0xcca58, -4), ('sequence_steps', 0xe9b04, -4), ('match_over', 0xcbc48, -2),
              ('star0_team', 0xe9af8, -2), ('star0_roster', 0xe9afa, -2), ('star1_team', 0xe9afc, -2),
              ('star1_roster', 0xe9afe, -2), ('star2_team', 0xe9b00, -2), ('star2_roster', 0xe9b02, -2),
              ('buttons_prev0', 0xe9abe, -2), ('buttons_prev1', 0xe9abc, -2), ('clip_time', 0xe9ab2, -2),
              ('clip_pos', 0xe9ab4, -2), ('last_penalty_team', 0xe9aae, -2), ('last_sfx', CROWD_NOISE, -2),
              ('one_minute_said', 0xccc98, -4))
GLOBAL_DEFAULTS = {'last_sfx': -1}            # the globals a case leaves out
SPEECH = {'busy': 0}                           # speech_busy (stubbed): the announcer talking, as the case says
CLIP_SCRIPTS = 0xcc01d                        # off_cc01d: the clips' frame scripts (a count, then the frames)
CLIP_SCRIPT = 0xe0248                         # dword_e0248: the script of the clip loaded


def write_globals(emu, g):
    '''the globals of a case into memory; the loaded clip's script pointer (dword_e0248) goes with
    the clip, its frame counter within the script'''
    clip = g.get('clip', -1)
    ptr = 0
    if 0 <= clip < 11:
        ptr = struct.unpack('<I', emu.read(CLIP_SCRIPTS + 4 * clip, 4))[0]
        n = emu.read(ptr, 1)[0]
        if not 1 <= g.get('clip_pos', 0) <= n:
            g['clip_pos'] = 1 + g.get('clip_pos', 0) % n
    emu.write(CLIP_SCRIPT, struct.pack('<I', ptr))
    emu.write(PERIOD_NUM, struct.pack('<i', g.get('period_num', g['period'] + 1)))
    SPEECH['busy'] = g.get('speech_busy', 0)
    ev = g.get('events')
    if ev is not None:
        emu.write(EVENT_REC, bytes(ev['rec']))
        emu.write(EVENT_BUF, bytes(ev['buf']))
        emu.write(EVENT_COUNT, struct.pack('<i', ev['count']))
    for n_, a, sz in AI_GLOBALS:
        v = g.setdefault(n_, GLOBAL_DEFAULTS.get(n_, 0))
        emu.write(a, struct.pack('<' + _FMT[abs(sz)], v & ((1 << (8 * abs(sz))) - 1)))
    hud_write(emu, g.setdefault('hud', hud_default()))
    emu.write(TEAM_IDS, struct.pack('<hh', *g.setdefault('team_ids', [0, 1])))


HUD_LISTS = (0xc571c, 0xc575c)                 # the penalty lists: 8 x (number, minutes, seconds, hundredths) words
HUD_LINES_ONLY = (0xc5844, 0xc5848)            # the panels show the lines (draw_clock found the list empty)
HUD_CLOCK = 0xc5704                            # the scoreboard's clock: minutes, seconds, hundredths (dwords)
HUD_FRAME = 0xc583c                            # dword_c583c: the hundredths draw_clock counted down
HUD_HUNDREDTHS = 0xdc28c                       # dword_dc28c: the hundredths of the frame (game_loop)


def hud_default():
    '''the scoreboard of a case that leaves it out: no penalties, 5:00 on the clock'''
    return {'lists': [[-1, 0, 0, 0] * 8, [-1, 0, 0, 0] * 8], 'lines_only': [0, 0], 'clock': [5, 0, 0]}


def hud_random(rnd, numbers=None):
    '''a random scoreboard: some penalties (the numbers of `numbers` per team now and then), free
    entries in between at times, the clock anywhere (run out, not set)'''
    lists = []
    for t in range(2):
        n = rnd.choice((0, 0, 1, 2, 3, rnd.randrange(9)))
        es = []
        for i in range(8):
            if i < n:
                num = rnd.choice(numbers[t]) if numbers and numbers[t] and rnd.random() < 0.6 else rnd.randrange(1, 100)
                es.append([num, rnd.choice((0, 0, 1, 2, 4, 9)), rnd.randrange(60), rnd.randrange(100)])
            else:
                es.append([-1, rnd.choice((0, 0, 0, 1)), rnd.choice((0, 0, 30)), rnd.choice((0, 0, 50))])
        if rnd.random() < 0.2:
            rnd.shuffle(es)
        lists.append(sum(es, []))
    return {'lists': lists, 'lines_only': [rnd.choice((0, 0, 1)), rnd.choice((0, 0, 1))],
            'clock': [rnd.choice((0, 0, 1, 5, 19, -1)), rnd.randrange(60), rnd.randrange(100)]}


def hud_write(emu, h):
    for t in range(2):
        emu.write(HUD_LISTS[t], struct.pack('<32h', *h['lists'][t]))
        emu.write(HUD_LINES_ONLY[t], struct.pack('<i', h['lines_only'][t]))
    emu.write(HUD_CLOCK, struct.pack('<3i', *h['clock']))


def hud_read(emu):
    return {'lists': [list(struct.unpack('<32h', emu.read(HUD_LISTS[t], 64))) for t in range(2)],
            'lines_only': [struct.unpack('<i', emu.read(HUD_LINES_ONLY[t], 4))[0] for t in range(2)],
            'clock': list(struct.unpack('<3i', emu.read(HUD_CLOCK, 12)))}


REPLAY_BUFFER = 0xc9078                        # replay_buffer: the ring of frames
REPLAY_SIZE = 0x9600                           # 300 frames of 0x80 bytes
REPLAY_WRITE = 0xe039c                         # replay_write_ptr
REPLAY_HALF = 0xcd4fe                          # replay_half_step
REPLAY_HELD = 0xcd500                          # replay_held_sfx


def replay_setup(emu, rnd, g):
    '''the replay ring of a case: empty, the write position anywhere (the end too: the ring wraps),
    the half step and the sound held from the skipped step; the ring full (action_flags 0x10) or not,
    the last sound effect played (crowd_noise), the last minute line said (dword_ccc98)'''
    buf = struct.unpack('<I', emu.read(REPLAY_BUFFER, 4))[0]
    emu.write(buf, b'\0' * REPLAY_SIZE)
    frame = rnd.choice((0, 0, rnd.randrange(300), 299, 298))
    rp = {'write': frame * 0x80, 'half': rnd.choice((0, 1)), 'held': rnd.choice((-1, -1, 0x7d, 0x9c, rnd.randrange(0xb0)))}
    emu.write(REPLAY_WRITE, struct.pack('<I', buf + rp['write']))
    emu.write(REPLAY_HALF, struct.pack('<h', rp['half']))
    emu.write(REPLAY_HELD, struct.pack('<h', rp['held']))
    g['action_flags'] = (g['action_flags'] & ~0x10) | rnd.choice((0, 0, 0x10))
    g['last_sfx'] = rnd.choice((-1, -1, 0x7d, 0x9c, rnd.randrange(0xb0)))
    g['one_minute_said'] = rnd.choice((0, 0, 0, 1))
    g['sound_card'] = rnd.choice((g['sound_card'], 4, 8))
    return rp


def replay_read(emu):
    '''the replay after a case: the write position, the half step, the held sound, a hash of the ring
    and the frame written last (in full)'''
    buf = struct.unpack('<I', emu.read(REPLAY_BUFFER, 4))[0]
    w = struct.unpack('<I', emu.read(REPLAY_WRITE, 4))[0] - buf
    data = emu.read(buf, REPLAY_SIZE)
    last = (w - 0x80) % REPLAY_SIZE
    return {'write': w, 'half': struct.unpack('<h', emu.read(REPLAY_HALF, 2))[0],
            'held': struct.unpack('<h', emu.read(REPLAY_HELD, 2))[0],
            'hash': hashlib.sha256(bytes(data)).hexdigest()[:16], 'last': bytes(data[last:last + 0x80]).hex()}


FORMAT_PLAYER_NAME = 0x61d48                   # a player's name for the panel, shortened to 124 pixels of SCOR2B; ret 8
SPEECH_ENABLED = 0xd27bb                       # speech_enabled: the speech bank is loaded
SPEECH_DRIVER = (0xed7ac, 0xed7b0)             # the speech driver's records (the sentences write their flags there)
SPEECH_AVAILABLE = 0x83711                     # stubbed: 1, a voice is free
SPEECH_BEGIN = 0x83520                         # stubbed: a sentence begins (recorded)
SPEECH_RESET = 0x833fa                         # stubbed
SPEECH_QUEUE_CLIP = 0x83faf                    # stubbed: a clip loaded
SPEECH_PLAY_SENTENCE = 0x8426f                 # stubbed
SPEECH_RELEASE_CLIP = 0x84418                  # stubbed: the clip appended to the playback list (recorded)
GOAL_MILESTONE_CHECK = 0x62807                 # the milestones of a goal (a deferred call, empty in this build; the panel shut)
RECORD_PENALTY = 0x624b9                       # (team, roster, kind, minutes) + mm, ss, queue index; ret 0xc
SHOW_PENALTY = 0x61e99                         # the panel's lines for the event record (sprintf, the names)
FONT_SCOR2B = 0xd8b70                          # font_scor2b: SCOR2B.VFN in memory (format_player_name measures the names with it)
FONT_CURRENT_DEFAULT = 0xdc230                 # font_current_default: the font format_player_name sets back
TEAM_NAMES = 0xdbc30                           # team_names: the TEAMS.DB records (0x2e8 bytes) of the two teams: +0 abbreviation, +0x1a name
SEASON_RECORDS = 0xdeb74                       # unk_deb74: 25 x 0x10 bytes per team: career goals, career points, season goals, season points (dwords)
# the season records of the worlds: values around the milestones goal_milestone_check looks for
SEASON_POOLS = ((0, 0, 0, 97, 98, 99, 199, 299), (0, 0, 96, 97, 98, 99, 198, 299),
                (0, 0, 1, 8, 9, 18, 19, 47, 48, 49, 98, 99), (0, 0, 17, 18, 19, 39, 96, 97, 98, 99))
PANEL_LINES = (0xe02c8, 0xe0250, 0xe028c, 0xe0308, 0xe0344)   # panel_title and the four lines below it
ROSTER_DB = {}                                 # (ai_cases) the TEAMS.DB records and the names of their players (KEY.DB)


def roster_db_load(gamedir):
    '''the 28 TEAMS.DB records and the first and last names (KEY.DB +3, +0x13) of their 28 players
    (25 skater keys at +0x4c, 3 goalie keys at +0xb0; -1 no player: empty names)'''
    with open(os.path.join(gamedir, 'TEAMS.DB'), 'rb') as f:
        teams = f.read()
    with open(os.path.join(gamedir, 'KEY.DB'), 'rb') as f:
        key = f.read()
    ROSTER_DB['teams'] = [teams[k * 0x2e8:(k + 1) * 0x2e8] for k in range(len(teams) // 0x2e8)]
    ROSTER_DB['names'] = []
    for rec in ROSTER_DB['teams']:
        names = []
        for i in range(28):
            kk = struct.unpack_from('<i', rec, 0x4c + i * 4 if i < 25 else 0xb0 + (i - 25) * 4)[0]
            if kk < 0:
                names.append((b'', b''))
            else:
                names.append((key[kk + 3:kk + 0x13].split(b'\0')[0], key[kk + 0x13:kk + 0x23].split(b'\0')[0]))
        ROSTER_DB['names'].append(names)


def panel_read(emu):
    return [emu.read(a, 0x3a).split(b'\0')[0].decode('latin-1') for a in PANEL_LINES]
EVENT_REC = 0xe9ac8                            # dword_e9ac8: the record of the last event (11 bytes)
EVENT_BUF = 0xe9b4c                            # unk_e9b4c: the stoppage's events, 8 x 11 bytes
EVENT_COUNT = 0xcd34c                          # dword_cd34c
ADD_PENALTY_DISPLAY = 0x14c22                  # the scoreboard's penalty clock entry
PENALTY_LIST_FIND = 0x14ca0                    # the entry of a player released by a goal
UPDATE_ANNOUNCER = 0x66e06                     # the scoreboard panel and its clips
UPDATE_EFFECTS = 0x615a2                       # stubbed: the crowd noise and figures
SETUP_FACEOFF = 0x5d852                        # stubbed for now: the end of a period
ANNOUNCE_ONE_MINUTE = 0x6280a                  # the announcer's last minute line (with sound, speech and statistics)
SPEECH_STOP_CHANNELS = 0x837a8                 # stubbed: the voices stop
PICK_PLAYER_FOR_POSITION = 0x655cc             # stubbed: the line table rebuilt around a lost player; (team, roster)
PUT_PLAYER_ON_ICE = 0x5b2c5                    # stubbed: the ratings copy (no roster data here); (entity, roster)
PLAY_SPEECH = 0x59a11                          # stubbed: the announcer (a sample)
LOAD_CUTSCENE_CLIP = 0x66497                   # stubbed: the clip's frames from its PPV file (the clip and its script set as loaded)
ANNOUNCE_GOAL = 0x62343                        # (team, scorer, assist, assist) + flags, mm, ss
SPEECH_BUSY = 0x59aad                          # stubbed: the announcer talking (a case input)
AI_TEAM_FIELDS = TEAM_FIELDS + (('goals', 0x10, -2), ('hits', 0x24, -2), ('breakaways', 0x1c, -2), ('passes', 0x26, -2),
                                ('current_line', 0x2a, -2), ('nearest_d2', 0x3a, 4), ('nearest_dist', 0x3e, -4), ('nearest_slot', 0x42, -2),
                                ('strategy', 0xd2, 1), ('strategy2', 0xd3, 1), ('flags2', 0xd4, 1), ('mode', 0xd5, 1),
                                ('energy_threshold', 0xd6, -2), ('one_timer_tries', 0x16, -2), ('one_timers', 0x18, -2),
                                ('goalie_slot', 0xfa, -2), ('dpair', 0x2c, -2), ('extra_attacker', 0x2e, -2),
                                ('pp_goals', 2, -2), ('power_plays', 4, -2), ('pp_time', 8, -2), ('penalty_count', 0xa, -2),
                                ('penalty_minutes', 0xc, -2), ('zone_time', 0xe, -2), ('one_timer_goals', 0x1a, -2),
                                ('breakaway_goals', 0x1e, -2), ('penalty_shots', 0x20, -2), ('penalty_shot_goals', 0x22, -2))
DEFAULT_STATES = (14, 2, 2, 3, 5, 3, 5)


WORLDS = {'n': 0}                              # the random worlds made so far


def ai_world(emu, rnd, base, tables):
    """A random moment of play: both teams on the ice (line slots, ratings, the state stacks with the
    positional states, the AI timers), the puck loose or carried, the referee, the team records and
    the globals the handlers read"""
    emu.write(ENTITIES, base)
    game = rnd.choice((0, 0, 0, 0, 0, 2, 2, 1, 8, 0x10, 0x40))
    switched = game & 2
    teams = []
    frames = list(range(0, 0x284)) + list(range(0x294, 0x2da)) + list(range(0x378, 0x468))
    for ti, t in enumerate(TEAM_RECORDS):
        f = {n: 0 for n, _, _ in AI_TEAM_FIELDS}
        f.update({'carrier0': rnd.choice((-1, rnd.randrange(20))), 'carrier1': -1, 'carrier2': -1,
                  'skaters': rnd.choice((6, 6, 6, 5)), 'goalie_request': rnd.choice((0, 0, 0, 1)), 'flags': rnd.choice((0, 0, 0x10, 8)),
                  'nearest_dist': rnd.choice((0x10, 0x30, 0x80, 0xffff)), 'nearest_slot': rnd.choice((-1, ti * 6 + rnd.randrange(1, 6))),
                  'strategy': rnd.randrange(4), 'strategy2': rnd.randrange(4), 'flags2': rnd.choice((0, 1)),
                  'mode': rnd.randrange(3), 'energy_threshold': 0xccc, 'current_line': rnd.randrange(4), 'goals': rnd.randrange(3)})
        f['energy'] = rnd.choice((0x1000, 0xc00, 0x800))
        f['entity_of'] = [-2] * 28
        f['box_queue'] = [-1] * 28
        emu.write(t + 0xb6, b'\xff' * 28)
        # the status bytes of the players' records in `rosters`: 3 on the bench, now and then one
        # the line editor called on (7, bench_player_slot)
        f['roster_status'] = [3] * 28
        if rnd.random() < 0.4:
            f['roster_status'][rnd.randrange(28)] = 7
        for i, st in enumerate(f['roster_status']):
            emu.write(ROSTERS + ti * 0x444 + i * 0x27, bytes([st]))
        # the jersey numbers of the records (byte 5: the announcer, the penalty clocks), varied
        # from case to case without drawing on the random numbers
        WORLDS['n'] += 1
        f['numbers'] = [(WORLDS['n'] * 37 + ti * 53 + i * 11) % 99 + 1 for i in range(28)]
        for i, num in enumerate(f['numbers']):
            emu.write(ROSTERS + ti * 0x444 + i * 0x27 + 5, bytes([num]))
        # the names of the players of a team of the databases (the records' +7, +0x17) and the
        # names of its TEAMS.DB record in team_names (only those: assign_line_positions of a pulled
        # goalie's team defending a penalty shot reads the home team's line table out of bounds, in
        # front of it, into the end of the away team's record; the port reads 0 there), the goals of
        # the season so far (the panel's " (12)" in a league game), no statistics of the game yet
        f['db_team'] = (WORLDS['n'] * 5) % len(ROSTER_DB['teams'])
        emu.write(TEAM_NAMES + ti * 0x2e8, ROSTER_DB['teams'][f['db_team']][:0x27])
        for i, (first, last) in enumerate(ROSTER_DB['names'][f['db_team']]):
            emu.write(ROSTERS + ti * 0x444 + i * 0x27 + 7, first.ljust(16, b'\0') + last.ljust(16, b'\0'))
        n = WORLDS['n']
        for k, name in enumerate(('career_goals', 'career_points', 'season_goals', 'season_points')):
            pool = SEASON_POOLS[k]
            f[name] = [pool[(n * 7 + i * (3 + k) + k * 5) % len(pool)] for i in range(25)]
        for i in range(25):
            emu.write(SEASON_RECORDS + ti * 0x190 + i * 0x10,
                      struct.pack('<4i', f['career_goals'][i], f['career_points'][i], f['season_goals'][i], f['season_points'][i]))
        # the goals and assists of the game so far, in every third world (the hat tricks)
        raw = bytearray(25 * 0x10)
        if n % 3 == 0:
            f['game_goals'] = [(n + i * 5) % 7 % 4 for i in range(25)]
            f['game_assists'] = [(n * 3 + i * 2) % 5 for i in range(25)]
            for i in range(25):
                struct.pack_into('<hh', raw, i * 0x10, f['game_goals'][i], f['game_assists'][i])
        emu.write(tables[ti][0], bytes(raw))
        for n, o, sz in AI_TEAM_FIELDS:
            emu.write(t + o, struct.pack('<' + _FMT[sz], f[n] if sz < 0 else f[n] & ((1 << (8 * sz)) - 1)))
        emu.write(t + 0x46, struct.pack('<28h', *([f['energy']] * 28)))
        emu.write(t + 0xf6, struct.pack('<I', ENTITIES + ti * 6 * 0x80))
        teams.append(f)
    puck_x, puck_y = rnd.randrange(-0x90, 0x91), rnd.randrange(-0xf0, 0xf1)
    for slot in range(12):
        ti = 0 if slot < 6 else 1
        rec = bytearray(emu.read(ENTITIES + slot * 0x80, 0x80))
        line = 0 if slot % 6 == 0 else slot % 6
        if rnd.random() < 0.04:
            line = -1
        roster = (slot % 6) * 2 + ti
        if line >= 0:
            teams[ti]['entity_of'][roster] = -1
        near = rnd.random() < 0.3
        x = puck_x + rnd.randrange(-20, 21) if near else rnd.randrange(-0x98, 0x99)
        y = puck_y + rnd.randrange(-20, 21) if near else rnd.randrange(-0x100, 0x101)
        if line == 0:
            gy = 0xd8 if ((slot < 6) == bool(switched)) else -0xd8
            x, y = rnd.randrange(-0x20, 0x21), gy + rnd.randrange(-0x18, 0x19)
        up = (slot < 6) != bool(switched)
        sp = rnd.randrange(8)
        stack = [DEFAULT_STATES[line] if line >= 0 else 11] * 8
        lim = rnd.choice((0, 0x800, 0x1800, 0x3000))
        f = {'x': x << 16 | rnd.randrange(0x10000), 'y': y << 16 | rnd.randrange(0x10000),
             'vx': rnd.randrange(-lim, lim + 1), 'vy': rnd.randrange(-lim, lim + 1),
             'heading': rnd.randrange(8) << 16 | rnd.randrange(0x10000), 'frame': rnd.choice(frames),
             'flags4': rnd.choice((0, 8)), 'flags': (0x80 if up else 0) | (0x40 if slot >= 6 else 0) | rnd.choice((0, 0, 0, 0, 0x20, 1)),
             'flags2': rnd.choice((0, 0, 0, 0, 0x80, 2, 4)), 'line_slot': line, 'roster': roster,
             'anim': rnd.choice((0x289, 0x289, 0x2e9, 0x331, 0x349)), 'anim_pos': rnd.randrange(6), 'anim_hold': rnd.randrange(-1, 3),
             'state_sp': sp, 'stack': struct.unpack('<I', bytes(stack[:4]))[0], 'stack2': struct.unpack('<I', bytes(stack[4:]))[0],
             'timer_a': rnd.choice((0, rnd.randrange(-0x200, 0x800))), 'want_dir': rnd.randrange(9), 'dir_timer': rnd.randrange(-2, 12),
             'target_x': rnd.randrange(-0x90, 0x91), 'target_y': rnd.randrange(-0xf0, 0xf1), 'timer_b': rnd.choice((0, rnd.randrange(0x200))),
             'timer_c': rnd.choice((0, 0, 0, 5)), 'timer_d': rnd.choice((0, 0, 3)), 'timer_e': rnd.choice((0, rnd.randrange(100))),
             'timer_f': rnd.choice((0, rnd.randrange(300))), 'speed': rnd.randrange(0x20),
             'weight': rnd.randrange(150, 230), 'speed_skill': rnd.randrange(16), 'stamina': rnd.randrange(16),
             'reaction': rnd.randrange(2, 12), 'awareness': rnd.randrange(16), 'shot_skill': rnd.randrange(16),
             'accuracy': rnd.randrange(16), 'pass_skill': rnd.randrange(16), 'offense': rnd.randrange(16),
             'goalie_skill': rnd.randrange(16), 'endurance': rnd.randrange(16), 'check_skill': rnd.randrange(16),
             'aggression': rnd.randrange(16), 'left_handed': rnd.choice((0, 1)), 'number': rnd.randrange(1, 99),
             'pass_ok': rnd.choice((0, 0, 1)), 'side': rnd.choice((0, 1, -1)), 'w48': rnd.choice((-1, 0, 2, 9)),
             'next_line': -1, 'next_roster': -1, 'save_result': 0}
        dx, dy = (puck_x - x), (puck_y - y)
        f['puck_dist'] = min(0x7fff, abs(dx) + abs(dy))
        f['puck_dist_sq'] = min(0x7fff, (dx // 4) ** 2 + (dy // 4) ** 2)
        f['puck_dir'] = rnd.randrange(8)
        put_fields(rec, f)
        struct.pack_into('<ii', rec, 0x74, f['x'], f['y'])
        emu.write(ENTITIES + slot * 0x80, rec)
    for ti, t in enumerate(TEAM_RECORDS):
        emu.write(t + 0x7e, struct.pack('<28h', *teams[ti]['entity_of']))
        # the goalie on the ice, as sim_update_players leaves it (+0xfa)
        line = struct.unpack('<h', emu.read(ENTITIES + ti * 6 * 0x80 + 0x1a, 2))[0]
        teams[ti]['goalie_slot'] = ti * 6 if line == 0 else -1
        emu.write(t + 0xfa, struct.pack('<h', teams[ti]['goalie_slot']))
    carrier = rnd.choice((-1, -1, rnd.randrange(12)))
    puck = bytearray(emu.read(PUCK, 0x80))
    put_fields(puck, {'x': puck_x << 16 | rnd.randrange(0x10000), 'y': puck_y << 16 | rnd.randrange(0x10000),
                      'vx': rnd.randrange(-0x1800, 0x1801), 'vy': rnd.randrange(-0x1800, 0x1801), 'z': 0,
                      'state_sp': 0, 'stack': 0x18181818, 'stack2': 0x18181818})
    emu.write(PUCK, puck)
    if carrier >= 0:
        c = bytearray(emu.read(ENTITIES + carrier * 0x80, 0x80))
        put_fields(c, {'x': puck_x << 16, 'y': puck_y << 16})
        emu.write(ENTITIES + carrier * 0x80, c)
    emu.write(PUCK + 0x42, bytes([carrier & 0xff]))
    ref = bytearray(emu.read(ENTITIES + 16 * 0x80, 0x80))
    put_fields(ref, {'x': rnd.randrange(-0x80, 0x81) << 16 | rnd.randrange(0x10000),
                     'y': rnd.randrange(-0xe0, 0xe1) << 16 | rnd.randrange(0x10000), 'state_sp': 0,
                     'stack': 0x1f1f1f1f, 'stack2': 0x1f1f1f1f, 'anim': 0xa5b})
    emu.write(ENTITIES + 16 * 0x80, ref)
    emu.call(SORT_DRAW_ORDER2)
    g = {'game_flags': game, 'stop_flags': rnd.choice((0, 0, 0x10, 0x20, 0x80)), 'misc_flags': rnd.choice((0, 0x10)),
         'option_flags': rnd.choice((0x1f, 0x9f, 0x1b, 0x8e)), 'settings2': rnd.choice((0, 2)),
         'action_flags': rnd.choice((0, 0, 4, 8)), 'user1_slot': rnd.choice((-1, -1, 2, 4)), 'user2_slot': rnd.choice((-1, -1, 9)),
         'user1_team': rnd.choice((0, 1)), 'user2_team': rnd.choice((0, 2)),
         'last_touch_slot': rnd.choice((-1, 2, 9)), 'last_touch_y': rnd.randrange(-0xe0, 0xe1), 'last_touch_x': rnd.randrange(-0x90, 0x91),
         'last_passer': rnd.choice((-1, 3, 8)), 'last_shooter': rnd.choice((-1, 2, 9)), 'pending_dir': rnd.randrange(9),
         'shot_power': rnd.choice((0xf, 0xc0)), 'pass_target': rnd.choice((-1, -1, 3, 9)), 'crowd': rnd.randrange(1000),
         'excitement': rnd.randrange(100), 'breakaway': rnd.choice((0, 0, 1)), 'defenders_ahead': rnd.choice((0, 1)),
         'one_timer': rnd.choice((0, 0, 1)), 'penalty_shot_slot': -1, 'penalty_shot_active': 0, 'penalty_shot_setup': 0,
         'penalty_shot_phase': 0, 'penalty_shot_team': 0, 'icing_flags': rnd.choice((0, 4, 5)), 'icing_shooter': rnd.choice((2, 9)),
         'pred0_x': rnd.randrange(-0x50, 0x51), 'pred0_steps': rnd.choice((-1, 20, 60)), 'pred1_x': rnd.randrange(-0x50, 0x51),
         'pred1_steps': rnd.choice((-1, 20, 60)), 'period': rnd.choice((0, 1, 2, 2, 3, 4)), 'clock_seconds': rnd.randrange(1, 300),
         'clock_sub': rnd.randrange(24), 'whistle_timer': rnd.choice((0, 0, 0x14)), 'camera_target_x': rnd.randrange(-0x20, 0x21),
         'camera_target_y': rnd.randrange(-0xbc, 0xec), 'last_impact': rnd.randrange(0x20), 'crowd_hit_toggle': rnd.choice((0, 1)),
         'ref_hits': rnd.randrange(3), 'box_home': rnd.choice((0, 0, 1)), 'box_away': rnd.choice((0, 0, 1)),
         'goalie_pass_mode': rnd.randrange(3)}
    w = rnd.randrange(4)
    side = rnd.choice((-1, 1))
    g.update({'breakaway_waypoint': w, 'breakaway_lane_side': side * rnd.choice((0x2c, 0x3a)),
              'breakaway_lane_x': side * rnd.choice((0x28, 0x16, 0x2c, 0x3a)), 'breakaway_target_y': rnd.choice((0x3c, 0x78, 0x97, 0xc0, 0xc3)),
              'breakaway_trigger_y': rnd.choice((0x1e, 0x3e, 0x66, 0x91, -1, -1)), 'breakaway_heading': rnd.randrange(8)})
    spot = rnd.choice(((0, 0), (-0x50, 0x9a), (0x50, 0x9a), (-0x50, -0x9a), (0x50, -0x9a), (-0x50, 0x56), (0x50, -0x56)))
    g.update({'faceoff_x': spot[0], 'faceoff_y': spot[1],
              'faceoff_ready0': rnd.randrange(7), 'faceoff_ready1': rnd.randrange(7), 'penalty_shot_timer': rnd.choice((0, 0, 5, 0x40)),
              'injury_stoppage': rnd.choice((0, 0, 0, 1)), 'clip': rnd.choice((-1, -1, -1, 2, 8)), 'ref_phase': rnd.choice((-1, -1, 0, 1)),
              'speech_busy': rnd.choice((0, 0, 1)), 'ref_infraction': rnd.choice((7, 7, 1, 2, 3, 5, 6, 8, 9, 0x10, 0x1b)),
              'ref_infraction_slot': rnd.randrange(-1, 12), 'panel': rnd.choice((-1, -1, -1, 0x100, 0x20)),
              'demo': rnd.choice((0, 0, 0, 1)), 'sound_card': rnd.choice((0x10, 0x10, 2, 0)), 'sound_enabled': rnd.choice((0, 1, 1)),
              'announce_time': rnd.choice((-1, 0x1e, 0x100)), 'period_length': rnd.choice((300, 600, 1200)),
              'deferred': 0, 'infraction_events': rnd.choice((0, 0, 1, 8, 0x3f)), 'save_clip_shown': rnd.choice((0, 0, 1)),
              'period_over': 0, 'goal_call': rnd.choice((0xff, 0xff, 1)), 'goal_team': rnd.randrange(2),
              'goal_scorer': rnd.randrange(20), 'goal_a1': rnd.choice((0xff, rnd.randrange(20))),
              'goal_a2': rnd.choice((0xff, rnd.randrange(20))), 'infraction0': rnd.choice((0, 0, 0, 0, 3)),
              'message': rnd.choice((-1, -1, 0, 1, 4, 5)), 'message_timer': rnd.choice((0, 0, 0x20))})
    for t in range(2):
        g.update({'lc_show%d' % t: rnd.choice((0, 1)), 'lc_blink%d' % t: rnd.choice((0, 3, 0xc)),
                  'lc_place%d' % t: rnd.randrange(4), 'lc_line%d' % t: rnd.randrange(8), 'lc_timer%d' % t: rnd.choice((0, 5, 0x3c)),
                  'lc_prompt%d' % t: rnd.choice((0, 0, 1)), 'hotkey%d' % t: 0, 'hotkey_line%d' % t: rnd.randrange(4),
                  'controller%d' % t: rnd.choice((8, 8, 2, 1)), 'faceoff_dir%d' % t: rnd.choice((-1, 8, 3, 0x13))})
    g.update({'controls_blocked': 0, 'skip_wait': 0, 'stoppage_timer': rnd.choice((-1, -1, 0, 5, 0x40)),
              'announce_timer': rnd.choice((-1, -1, 0, 3)), 'penalty_box_mode': 0, 'second_timer': rnd.randrange(0x18),
              'tick24': rnd.randrange(-1, 0x18), 'tick_toggle': rnd.randrange(2), 'excitement_peak': rnd.randrange(200),
              'excitement_sum': rnd.randrange(100000), 'excitement_samples': rnd.randrange(1000), 'lc_bar0': 0, 'lc_bar1': 0,
              'penalty_shot_clock': rnd.choice((0, 1, 1000)), 'goal_flags': 1, 'puck_in_net': 0, 'penalty_shot_roster': -1,
              'penalty_shot_spot_x': 0, 'penalty_shot_spot_y': 0, 'series_announce': 0, 'camera_x': 0, 'camera_y': 0,
              'camera_lead': 0, 'faceoff_digit': 7, 'faceoff_side0': 0x8800 - 0x10000, 'faceoff_side1': 0xa000 - 0x10000, 'fade_in': 0,
              'clip_frame': -1, 'clip_time': rnd.choice((0, 1, 3, 8)), 'clip_pos': rnd.randrange(1, 12), 'last_penalty_team': -1,
              'events': {'rec': [rnd.randrange(256) for _ in range(11)], 'buf': [0] * 88, 'count': rnd.choice((0, 0, 1, 6, 7))},
              'scorer_jumps': 0, 'sequence_steps': 0, 'match_over': 0, 'star0_team': 0, 'star0_roster': 0,
              'star1_team': 0, 'star1_roster': 0, 'star2_team': 0, 'star2_roster': 0, 'buttons_prev0': 0, 'buttons_prev1': 0})
    if g['stop_flags'] & 0x10 and g['last_shooter'] < 0:
        g['last_shooter'] = 2                  # (a shot in flight has a shooter: shot_landed credits him)
    g['settings2'] |= (WORLDS['n'] >> 1) & 1   # the announcer on in every other world (option byte 2 bit 0)
    g['session_mode'] = (0, 2, 1, 2)[(WORLDS['n'] >> 2) & 3]   # exhibition, league, play-off series
    # the bytes that stop goal_milestone_check for a team when both are set (nothing sets them in the
    # game but reset_game_state and the saved games)
    g['milestone_gate'] = (0, 0, 0, 0, 0x0101, 0x01010000, 0x0001, 0x01000100)[(WORLDS['n'] >> 4) & 7]
    write_globals(emu, g)
    for a in PANEL_LINES:
        emu.write(a, b'\0' * 0x3a)
    emu.write(OPTION_FLAGS, struct.pack('<I', (g['option_flags'] & 0xff) | (g['settings2'] << 8)))
    return g, teams, carrier


def events_read(emu):
    return {'rec': list(emu.read(EVENT_REC, 11)), 'buf': list(emu.read(EVENT_BUF, 88)),
            'count': struct.unpack('<i', emu.read(EVENT_COUNT, 4))[0]}


def ai_record(emu):
    return {'globals': {n: struct.unpack('<' + _FMT[sz], emu.read(a, abs(sz)))[0] for n, a, sz in AI_GLOBALS},
            'events': events_read(emu), 'hud': hud_read(emu), 'panel': panel_read(emu),
            'teams': [dict({n: struct.unpack('<' + _FMT[sz], emu.read(t + o, abs(sz)))[0] for n, o, sz in AI_TEAM_FIELDS},
                           entity_of=list(struct.unpack('<28h', emu.read(t + 0x7e, 56))),
                           roster_status=[emu.read(ROSTERS + ti * 0x444 + i * 0x27, 1)[0] for i in range(28)],
                           box_queue=list(struct.unpack('<28b', emu.read(t + 0xb6, 28))))
                      for ti, t in enumerate(TEAM_RECORDS)],
            'carrier': struct.unpack('<b', emu.read(PUCK + 0x42, 1))[0], 'seed': struct.unpack('<I', emu.read(SEED, 4))[0]}


SKATERS = (1, 2, 3, 4, 5, 7, 8, 9, 10, 11)
AI_GROUPS = {
    # the positional states of the skaters (the role of the line slot, offense and defense)
    'positional': ((1, (1, 2, 7, 8)), (2, (1, 2, 7, 8)), (3, (3, 5, 9, 11)), (4, (3, 5, 9, 11)), (5, (4, 10)), (6, (4, 10))),
    # the puck: chasing it, carrying it, shooting, receiving a pass, the breakaway
    'puck': ((17, SKATERS), (16, SKATERS), (18, SKATERS), (19, SKATERS), (46, SKATERS)),
    # the goalies: in the crease, out for a rimmed puck
    'goalie': ((14, (0, 6)), (14, (0, 6)), (14, (0, 6)), (14, (0, 6)), (14, (0, 6)), (15, (0, 6))),
    # the faceoff: waiting, the centres at the dot, going to the faceoff, the start of a period
    'faceoff': ((22, tuple(range(12))), (23, (4, 10)), (23, (4, 10)), (39, tuple(range(12))), (39, tuple(range(12))), (41, tuple(range(12)))),
    # the puck and its shadow
    'pucks': ((24, (14,)), (25, (15,)), (26, (14,))),
    # the referee: at the faceoff, following the play, to the faceoff dot, pointing at the goal
    'referee': ((30, (16,)), (31, (16,)), (34, (16,)), (34, (16,)), (35, (16,))),
    # the bench and the penalty box: to the bench, waiting there, into the box, sitting in it, back on
    'bench': ((11, SKATERS + (0, 6)), (11, SKATERS + (0, 6)), (40, SKATERS), (12, SKATERS), (13, SKATERS),
              (9, SKATERS), (10, SKATERS), (29, SKATERS)),
    # the referee's calls: signalling, the new puck, picking up the puck
    'refcalls': ((32, (16,)), (32, (16,)), (36, (16,)), (36, (16,)), (33, (16,)), (33, (16,)), (33, (16,)), (33, (16,))),
    # the penalty shot (the referee with the puck, everybody else off), the goal celebration, the
    # Stanley Cup (the shadow brings it, the captain fetches it and skates with it)
    'ceremony': ((44, (16,)), (44, (16,)), (45, SKATERS + (0, 6)), (45, SKATERS + (0, 6)), (7, SKATERS), (7, SKATERS),
                 (8, SKATERS), (42, SKATERS), (42, SKATERS), (43, (15,))),
    # the national anthem (the players at the blue lines, the referee to centre ice) and the three
    # stars (the referee presenting them, a star's lap of honour)
    'anthem': ((37, tuple(range(12))), (38, (16,)), (38, (16,)), (20, SKATERS + (0, 6)), (20, SKATERS + (0, 6)), (21, (16,)),
               (21, (16,)), (21, (16,))),
}


def ai_prepare(emu, rnd, state, actor, g):
    '''the world around the actor for its state: the carrier for the carrier, shooting and breakaway
    states, the pass on its way for the receiver'''
    rec = bytearray(emu.read(ENTITIES + actor * 0x80, 0x80))
    puck = bytearray(emu.read(PUCK, 0x80))
    carrier = struct.unpack('<b', bytes([puck[0x42]]))[0]
    if state == 16:
        put_fields(rec, {'target_x': rnd.randrange(4)})     # the lane (carrier_targets 6..9)
    if state in (16, 18, 46) and rnd.random() < 0.85:
        carrier = actor
        struct.pack_into('<ii', puck, 0, struct.unpack_from('<i', rec, 0)[0], struct.unpack_from('<i', rec, 4)[0])
        put_fields(rec, {'timer_c': 0})
    if state == 18:
        put_fields(rec, {'anim': rnd.choice((0x3f9, 0x491)), 'anim_pos': rnd.randrange(0, 0xe)})
        g['action_flags'] |= 8 if rnd.random() < 0.85 else 0
    if state == 19:
        carrier = rnd.choice((-1, -1, -1, actor ^ 1 if actor != 1 else 2))
        g['pass_target'] = actor if rnd.random() < 0.8 else -1
        g['one_timer'] = rnd.choice((0, 0, 1))
        put_fields(puck, {'vx': rnd.randrange(-0x1000, 0x1001), 'vy': rnd.randrange(-0x1000, 0x1001)})
    if state == 46:
        g['breakaway'] = 1
    if state in (22, 23, 39, 41):
        # mostly a faceoff set up (stop flag 1); the centres in their faceoff frames
        if rnd.random() < 0.75:
            g['stop_flags'] |= 1
        # the steps to the drop: the puck's +0x26 (faceoff_timer 0xdff42)
        put_fields(puck, {'timer_a': rnd.choice((-1, 0, 0x10, 0x11, 0x30))})
        if state == 23:
            put_fields(rec, {'frame': rnd.choice((0x167, 0x168, 0x169, 0x16a, 0x16c, 0x16d, 0x16e, 0x16f)),
                             'anim_hold': rnd.choice((0, 3, 7)), 'timer_b': rnd.choice((-1, 0, 1, 0x14)),
                             'flags2': rnd.choice((0, 0, 0, 2))})
        if state == 39:
            fx, fy = g['faceoff_x'], g['faceoff_y']
            if rnd.random() < 0.5:
                put_fields(rec, {'x': (fx + rnd.randrange(-0x30, 0x31)) << 16, 'y': (fy + rnd.randrange(-0x30, 0x31)) << 16})
    if state == 36:
        if rnd.random() < 0.6:
            put_fields(rec, {'x': rnd.randrange(0x90, 0xb0) << 16 | rnd.randrange(0x10000),
                             'y': rnd.randrange(-0xa, 0xb) << 16 | rnd.randrange(0x10000), 'target_x': 0xa0, 'target_y': 0,
                             'timer_a': rnd.choice((-1, 0, 0, 3)), 'heading': rnd.randrange(8) << 16 | rnd.randrange(0x10000)})
        g['ref_infraction'] = rnd.choice((0x1d, 0x1e, 3, 4, 8, 6, 6, 1))
        if rnd.random() < 0.5:
            rec[0x44] |= 2                           # the entry: the announcements
            g['panel'] = rnd.choice((-1, -1, -1, 0x100))
    if state in (9, 10, 11, 12, 13, 29, 40):
        # near the bench door or the penalty box, a change pending (the next roster and line slot)
        away = actor >= 6 and actor < 12
        r = rnd.random()
        if state in (11, 40, 9, 29) and r < 0.7:
            by = (0x41 if away else -0x32) + rnd.randrange(-0x30, 0x31)
            if state == 29:
                by = (0x24 if away else -0x1c) + rnd.randrange(-0x18, 0x19)
            put_fields(rec, {'x': (-0xa8 + rnd.randrange(-0x10, 0x30)) << 16 | rnd.randrange(0x10000),
                             'y': by << 16 | rnd.randrange(0x10000)})
        elif state in (12, 13, 10) and r < 0.7:
            put_fields(rec, {'x': (0xa0 + rnd.randrange(-0x20, 0x10)) << 16 | rnd.randrange(0x10000),
                             'y': ((0xb if away else -0xb) * rnd.randrange(2, 6) + rnd.randrange(-6, 7)) << 16 | rnd.randrange(0x10000)})
        roster = struct.unpack_from('<B', rec, 0x47)[0]
        put_fields(rec, {'next_roster': rnd.choice((roster, rnd.randrange(28), -1)), 'next_line': rnd.choice((-1, rnd.randrange(6))),
                         'timer_a': rnd.choice((-1, 0, 3, 100) + ((0, 0x5a) if state == 40 else ())), 'timer_b': rnd.choice((0, 0, 5, -100)),
                         'flags2': rnd.choice((0, 0, 4, 0x10, 0x20)), 'vx': rnd.choice((0, 0, 0x800)), 'vy': rnd.choice((0, 0, -0x400))})
        if rnd.random() < 0.3:
            rec[0x44] |= 4                             # arrived at the door
        if state in (40, 29) and rnd.random() < 0.5:
            # turned (or turning) towards the bench
            h = 6 if state == 40 else 4
            put_fields(rec, {'heading': rnd.choice((h - 1, h, h, h + 1)) << 16 | rnd.randrange(0x10000)})
            if rnd.random() < 0.6:
                # at the door, about to step off (or let a called on player come)
                wy = ((0x46 if away else -0x32) if state == 40 else (0x24 if away else -0x1c))
                put_fields(rec, {'x': (-0xa8 + rnd.randrange(-4, 0x14)) << 16 | rnd.randrange(0x10000),
                                 'y': (wy + rnd.randrange(-0x12, 0x13)) << 16 | rnd.randrange(0x10000),
                                 'target_x': -0xa8, 'target_y': wy, 'timer_a': rnd.choice((0, 0, 1))})
                if state == 40 and rnd.random() < 0.6:
                    emu.write(ROSTERS + (0x444 if away else 0) + rnd.randrange(25) * 0x27, b'\x07')
    if state == 33:
        # the puck loose near the referee, in a net, out of the rink; the panel up with a clip, a goal
        # to say; a frozen puck by a goalie who made a save
        r = rnd.random()
        if r < 0.15:
            px, py = rnd.choice((-6, 6)), rnd.choice((-0xf0, 0xf0))
        elif r < 0.2:
            px, py = rnd.choice((-0xb0, 0xb0)), rnd.randrange(-0x100, 0x101)
        else:
            px, py = rnd.randrange(-0x90, 0x91), rnd.randrange(-0x100, 0x101)
        put_fields(puck, {'x': px << 16 | rnd.randrange(0x10000), 'y': py << 16 | rnd.randrange(0x10000),
                          'vx': rnd.choice((0, rnd.randrange(-0x2000, 0x2001))), 'vy': rnd.choice((0, rnd.randrange(-0x2000, 0x2001)))})
        if rnd.random() < 0.5:
            put_fields(rec, {'x': (px + rnd.randrange(-0x10, 0x11)) << 16 | rnd.randrange(0x10000),
                             'y': (py + rnd.randrange(-0x10, 0x11)) << 16 | rnd.randrange(0x10000)})
        put_fields(rec, {'timer_a': rnd.choice((-1, 0, 0, 3)), 'timer_b': rnd.choice((0, 0x100, 0x258, 0x259)),
                         'heading': rnd.randrange(8) << 16 | rnd.randrange(0x10000), 'vx': rnd.choice((0, 0x600)), 'vy': 0})
        g['panel'] = rnd.choice((-1, -1, -1, 0x20, 0xf0, 0x100))
        g['clip'] = rnd.choice((-1, -1, 0, 2, 8))
        g['ref_infraction'] = rnd.choice((4, 4, 7, 7, 3, 6, 0x1d))
        if g['ref_infraction'] == 4:
            gs = rnd.choice((0, 6))
            g['ref_infraction_slot'] = gs
            grec = bytearray(emu.read(ENTITIES + gs * 0x80, 0x80))
            put_fields(grec, {'save_result': rnd.choice((0, 1))})
            emu.write(ENTITIES + gs * 0x80, grec)
        if rnd.random() < 0.5:
            rec[0x44] |= 2
        if rnd.random() < 0.3:
            carrier = rnd.choice((-1, 16, 3))
    if state == 32 and rnd.random() < 0.3:
        rec[0x44] |= 2                               # the entry: a goal announced
        g['ref_infraction'] = 7
    if state == 32 and rnd.random() < 0.6:
        # near the side where the call is signalled
        put_fields(rec, {'x': rnd.randrange(0x8a, 0xb0) << 16 | rnd.randrange(0x10000),
                         'y': rnd.randrange(-0x10, 0x11) << 16 | rnd.randrange(0x10000), 'target_x': 0xa0, 'target_y': 0,
                         'timer_a': rnd.choice((-1, 0, 0, 3)), 'heading': rnd.randrange(8) << 16 | rnd.randrange(0x10000)})
    if state in (30, 31, 34, 35):
        # the referee moving or near the faceoff dot, the faceoff set up or not
        if rnd.random() < 0.5:
            g['stop_flags'] |= 1
        f = {'vx': rnd.choice((0, 0, rnd.randrange(-0x800, 0x801))), 'vy': rnd.choice((0, 0, rnd.randrange(-0x800, 0x801))),
             'heading': rnd.randrange(8) << 16 | rnd.randrange(0x10000), 'timer_a': rnd.choice((-1, 0, 0, 3)),
             'target_x': rnd.randrange(-0x90, 0x91), 'target_y': rnd.randrange(-0xf0, 0xf1), 'dir_timer': rnd.randrange(-1, 12)}
        if state == 34 and rnd.random() < 0.6:
            fx = g['faceoff_x'] + (-0xf if g['faceoff_x'] <= 0 else 0xf)
            f.update({'x': (fx + rnd.randrange(-6, 7)) << 16 | rnd.randrange(0x10000),
                      'y': (g['faceoff_y'] + rnd.randrange(-6, 7)) << 16 | rnd.randrange(0x10000),
                      'target_x': fx, 'target_y': g['faceoff_y']})
            if rnd.random() < 0.6:
                f.update({'vx': 0, 'vy': 0})
        put_fields(rec, f)
    if state in (24, 25, 26):
        # the puck (or its shadow over it) loose, in the air or carried
        f = {'z': rnd.choice((0, 0, 0, 4, 0x10)) << 16, 'vz': rnd.choice((0, 0, 0x300, -0x200))}
        put_fields(puck, f)
        if actor == 14:
            put_fields(rec, f)
    if state in (14, 15):
        # the goalie in, out of or behind his crease; the puck mostly near his net, shot, carried
        # by him or an opponent; a shot predicted to the goal line
        own = -1 if rec[0x44] & 0x80 else 1
        r = rnd.random()
        if r < 0.7:
            gx, gy = rnd.randrange(-0x30, 0x31), own * rnd.randrange(0xb4, 0xef)
        elif r < 0.85:
            gx, gy = rnd.randrange(-0x50, 0x51), own * rnd.randrange(0x90, 0xf8)
        else:
            gx, gy = rnd.randrange(-0x40, 0x41), own * rnd.randrange(0xe5, 0xf8)
        put_fields(rec, {'x': gx << 16 | rnd.randrange(0x10000), 'y': gy << 16 | rnd.randrange(0x10000),
                         'w48': rnd.choice((0, 2, 4, 6)), 'timer_b': rnd.choice((-1, -1, 0, 0x10, 0x59, 0x5a, 0x100)),
                         'target_y': rnd.choice((-1, 0, 0, 1, 0x105)), 'timer_a': rnd.choice((-1, -1, 0, 3)),
                         'timer_e': rnd.choice((0, 0, 0, 1, 5)), 'puck_dist': rnd.choice((0x10, 0x18, 0x1d, 0x22, 0x2c, 0x40, 0x100)),
                         'flags2': rnd.choice((0, 0, 0, 2, 4))})
        if rnd.random() < 0.7:
            px, py = rnd.randrange(-0x70, 0x71), own * rnd.randrange(0x60, 0xf5)
            hard = rnd.choice((0x1000, 0x2000, 0x4000))
            put_fields(puck, {'x': px << 16 | rnd.randrange(0x10000), 'y': py << 16 | rnd.randrange(0x10000),
                              'vx': rnd.randrange(-hard, hard + 1), 'vy': rnd.randrange(-hard, hard + 1),
                              'z': rnd.choice((0, 0, 0, 6, 9, 12, 0x18)) << 16, 'vz': rnd.choice((0, 0, 0x400, 0x900))})
        r = rnd.random()
        if r < 0.2:
            carrier = actor
            struct.pack_into('<ii', puck, 0, struct.unpack_from('<i', rec, 0)[0], struct.unpack_from('<i', rec, 4)[0])
        elif r < 0.45:
            carrier = rnd.randrange(1, 6) + (0 if actor >= 6 else 6)
        elif r < 0.55:
            carrier = rnd.randrange(1, 6) + (6 if actor >= 6 else 0)
        else:
            carrier = -1
        for k in ('pred0', 'pred1'):
            g[k + '_x'] = rnd.randrange(-0x30, 0x31)
            g[k + '_steps'] = rnd.choice((-1, -1, 2, 5, 8, 12, 20, 0x22, 0x30))
        if state == 14 and rnd.random() < 0.35:
            # a shot on its way to the net, close to the goalie
            px, py = gx + rnd.randrange(-0x28, 0x29), gy - own * rnd.randrange(0x8, 0x40)
            put_fields(puck, {'x': px << 16, 'y': py << 16, 'vx': rnd.randrange(-0x1800, 0x1801),
                              'vy': own * rnd.randrange(0x800, 0x4000), 'z': rnd.choice((0, 0, 4, 9, 0x10)) << 16,
                              'vz': rnd.choice((0, 0, 0x400, 0x900))})
            put_fields(rec, {'puck_dist': rnd.randrange(0x8, 0x30), 'w48': rnd.choice((0, 0, 2, 4, 6))})
            carrier = -1
            g['pred0_steps' if own > 0 else 'pred1_steps'] = rnd.randrange(1, 0x24)
            g['pred0_x' if own > 0 else 'pred1_x'] = gx + rnd.randrange(-0x20, 0x21)
    if state == 44:
        # the referee with the puck to centre ice, putting it down, waiting at the side
        g['penalty_shot_slot'] = rnd.choice((-1, rnd.randrange(12), rnd.randrange(12), rnd.randrange(12)))
        g['penalty_shot_team'] = 1 if g['penalty_shot_slot'] > 5 else 0
        g['penalty_shot_phase'] = 1
        g['clip'] = rnd.choice((-1, -1, 2))
        tb = rnd.choice((0, 0, 1, 2, 2, 100))
        tx, ty = (0, 0) if tb == 0 else (0x96, rnd.choice((10, -10)))
        f = {'timer_b': tb, 'target_x': tx, 'target_y': ty,
             'timer_a': (rnd.randrange(8) << 8) | rnd.choice((0, 1, 5, 0xff)),
             'heading': rnd.randrange(8) << 16 | rnd.randrange(0x10000),
             'vx': rnd.choice((0, 0, 0x20, -0x300)), 'vy': rnd.choice((0, 0, 0x8))}
        if rnd.random() < 0.6:
            f.update({'x': (tx + rnd.randrange(-6, 7)) << 16 | rnd.randrange(0x10000),
                      'y': (ty + rnd.randrange(-6, 7)) << 16 | rnd.randrange(0x10000)})
        put_fields(rec, f)
        if rnd.random() < 0.5:
            for s_ in range(12):
                o = bytearray(emu.read(ENTITIES + s_ * 0x80, 0x80))
                struct.pack_into('<h', o, 0x2e, -100)
                emu.write(ENTITIES + s_ * 0x80, o)
            rec = bytearray(emu.read(ENTITIES + actor * 0x80, 0x80)) if actor < 12 else rec
    if state == 45:
        # off to the bench for the penalty shot
        g['penalty_shot_phase'] = rnd.choice((1, 1, 1, 0))
        away = actor >= 6
        ty = (0x41 if away else -0x32) + rnd.choice((-0x1e, -0xf, 0, 0xf))
        f = {'timer_a': rnd.choice((0x64, 0, 0, 1, 5, -1)), 'target_x': -0xa8, 'target_y': ty,
             'heading': rnd.randrange(8) << 16 | rnd.randrange(0x10000)}
        if rnd.random() < 0.5:
            f.update({'x': (-0xa8 + rnd.randrange(-4, 0x24)) << 16 | rnd.randrange(0x10000),
                      'y': (ty + rnd.randrange(-0x2c, 0x2d)) << 16 | rnd.randrange(0x10000)})
        put_fields(rec, f)
        if rnd.random() < 0.3:
            rec[0x44] |= 4
    if state == 7:
        # the scorers celebrate (the scorer jumps up to three times)
        if rnd.random() < 0.2:
            carrier = actor
        if rnd.random() < 0.4:
            g['last_shooter'] = actor
        g['scorer_jumps'] = rnd.randrange(4)
        if rnd.random() < 0.3:
            g['game_flags'] |= 0x80
        g['camera_x'] = rnd.randrange(-0x20, 0x21)
        g['camera_y'] = rnd.randrange(-0xbc, 0xed)
        put_fields(rec, {'timer_a': rnd.choice((-1, 0, 0, 1, 30)), 'target_x': rnd.choice((-100, 100, -0x50)),
                         'target_y': rnd.randrange(-0xbc, 0xed)})
    if state == 8:
        # the captain skating with the cup
        put_fields(rec, {'anim': rnd.choice((0, 0xecb, 0x833)), 'target_x': -0x50, 'target_y': 0,
                         'timer_a': rnd.choice((-1, 0, 0, 5))})
    if state in (42, 43):
        cup = bytearray(emu.read(ENTITIES + 15 * 0x80, 0x80))
        put_fields(cup, {'timer_a': rnd.choice((100, 100, 0, 200))})
        emu.write(ENTITIES + 15 * 0x80, cup)
    if state == 42:
        # the captain to the bench door for the cup
        f = {'timer_a': rnd.choice((100, 100, 0, 1, -1)), 'target_x': -0x91, 'target_y': 6,
             'heading': rnd.randrange(8) << 16 | rnd.randrange(0x10000)}
        if rnd.random() < 0.6:
            f.update({'x': (-0x91 + rnd.randrange(-6, 7)) << 16 | rnd.randrange(0x10000),
                      'y': (6 + rnd.randrange(-6, 7)) << 16 | rnd.randrange(0x10000)})
        put_fields(rec, f)
        if rnd.random() < 0.3:
            rec[0x44] |= 4
    if state == 43:
        # the shadow brings the cup in once the camera is at the bench door
        g['camera_x'] = rnd.choice((-0x20, -0x21, -0x40, 0))
        g['camera_y'] = rnd.choice((0, 0x14, 0x15, -0x14))
        g['panel'] = rnd.choice((-1, 0x100, 0x100))
        put_fields(rec, {'timer_a': rnd.choice((0, 50, 100, 200, 200)), 'frame': rnd.choice((0x365, 0x365, 0x362)),
                         'anim': rnd.choice((0, 0, 0xe97)), 'anim_pos': rnd.randrange(8), 'anim_hold': rnd.randrange(-1, 0xe)})
    if state == 37:
        put_fields(rec, {'timer_b': rnd.choice((-100, 0, 1, 2, 50)), 'target_x': rnd.randrange(-0x40, 0x41),
                         'flags2': rnd.choice((0, 0, 2))})
    if state == 38:
        # the referee waiting at the boards, skating to centre ice, turned to the players
        g['sequence_steps'] = rnd.choice((5, 10, 11, 100))
        f = {'timer_b': rnd.choice((-100, -100, 0, 1, 2, 50)), 'target_x': -0xf, 'target_y': 0,
             'timer_a': rnd.choice((-1, 0, 0, 3)), 'heading': rnd.randrange(8) << 16 | rnd.randrange(0x10000),
             'vx': rnd.choice((0, 0, 0x20, 0x400)), 'vy': rnd.choice((0, 0, -0x10)), 'flags2': rnd.choice((0, 0, 2))}
        if rnd.random() < 0.5:
            f.update({'x': (-0xf + rnd.randrange(-0xc, 0xd)) << 16 | rnd.randrange(0x10000),
                      'y': rnd.randrange(-0xc, 0xd) << 16 | rnd.randrange(0x10000)})
        put_fields(rec, f)
        if rnd.random() < 0.5:
            for s_ in range(12):
                o = bytearray(emu.read(ENTITIES + s_ * 0x80, 0x80))
                struct.pack_into('<h', o, 0x2e, -100)
                emu.write(ENTITIES + s_ * 0x80, o)
    if state == 20:
        # a star on his lap of honour
        tx, ty = rnd.randrange(-0x80, 0x81), rnd.randrange(-0xc0, 0xc1)
        f = {'timer_b': rnd.randrange(4), 'timer_a': rnd.choice((-1, 0, 1, 2, 3)), 'target_x': tx, 'target_y': ty,
             'dir_timer': rnd.randrange(-1, 12), 'want_dir': rnd.choice((0, 3, 8, 9)),
             'heading': rnd.randrange(8) << 16 | rnd.randrange(0x10000)}
        if rnd.random() < 0.4:
            f.update({'x': (tx + rnd.randrange(-0x20, 0x21)) << 16 | rnd.randrange(0x10000),
                      'y': (ty + rnd.randrange(-0x20, 0x21)) << 16 | rnd.randrange(0x10000)})
        if rnd.random() < 0.3:
            f.update({'vx': 0, 'vy': 0})
        put_fields(rec, f)
    if state == 21:
        # the referee presenting the stars
        g['panel'] = rnd.choice((-1, -1, 5, 0x10, 0x100, 0x258, 0x260, 0x268))
        for k in range(3):
            g['star%d_team' % k] = rnd.randrange(2)
            g['star%d_roster' % k] = rnd.choice((rnd.randrange(25), rnd.randrange(25, 28)))
        star = rnd.choice((-1, 5, 6))
        put_fields(rec, {'timer_a': rnd.choice((2, 1, 0, -1)), 'want_dir': rnd.choice((1, 2, 0, 0xff, 0xfb)),
                         'dir_timer': rnd.choice((0, 0, -1)), 'target_x': star})
        for s_ in (5, 6):
            o = bytearray(emu.read(ENTITIES + s_ * 0x80, 0x80))
            put_fields(o, {'timer_a': rnd.choice((100, 0)), 'frame': rnd.choice((-1, -1, 0x30))})
            emu.write(ENTITIES + s_ * 0x80, o)
    puck[0x42] = carrier & 0xff
    emu.write(PUCK, puck)
    emu.write(ENTITIES + actor * 0x80, rec)
    write_globals(emu, g)
    return carrier


def ai_cases(exe):
    """The AI state handlers (ai_state_handlers): a random moment of play, one entity in the state,
    its handler called; everything the handler may change recorded"""
    emu = PortEmu(exe)
    rnd = random.Random(2593)
    WORLDS['n'] = 0
    calls = []

    def on_infraction(name):
        def f(eax):
            calls.append([name, ((eax & 0xffffffff) - ENTITIES) // 0x80, emu.uc.reg_read(UC_X86_REG_EDX) & 0xff])
        return f
    # play_sfx runs: the sample goes to the sound driver (snd_play_sfx), the organ to the music
    emu.stub(SND_PLAY_SFX, lambda eax: calls.append(['snd_play_sfx', eax & 0xffff]))
    emu.stub(KMS_PLAY, lambda eax: calls.append(['kms_play']))
    # the instant replay's ring (allocated at the start of a match)
    emu.write(REPLAY_BUFFER, struct.pack('<I', emu.alloc(b'\0' * REPLAY_SIZE)))
    queue_stubs = [emu.stub(QUEUE_INFRACTION, on_infraction('queue_infraction')),
                   emu.stub(MAYBE_QUEUE_INFRACTION, on_infraction('maybe_queue_infraction'))]
    fixed_stubs = [emu.stub(INJURY_CHECK, lambda eax: (calls.append(['injury_check', ((eax & 0xffffffff) - ENTITIES) // 0x80]), 1)[1])]
    injure_stub = emu.stub(INJURE_PLAYER, lambda eax: calls.append(['injure_player', ((eax & 0xffffffff) - ENTITIES) // 0x80]))

    def reg(r):
        v = emu.uc.reg_read(r)
        return v - (1 << 32) if v & 0x80000000 else v

    # the announcer's sentences run (say_goal, say_penalty, say_penalty_shot, say_star,
    # say_one_minute_left with their wrappers): the speech driver is replaced, speech_begin starts a
    # sentence and speech_release_clip appends each clip to it, as it does to the playback list
    emu.write(SPEECH_ENABLED, struct.pack('<i', 1))
    for a in SPEECH_DRIVER:
        emu.write(a, struct.pack('<I', emu.alloc(b'\0' * 0x4000)))
    emu.stub(SPEECH_AVAILABLE, lambda eax: 1)
    emu.stub(SPEECH_BEGIN, lambda eax: calls.append(['say', []]))
    for a in (SPEECH_RESET, SPEECH_QUEUE_CLIP, SPEECH_PLAY_SENTENCE):
        emu.stub(a, lambda eax: None)

    def on_release(eax):
        name = bytes(emu.read(eax & 0xffffffff, 16)).split(b'\0')[0].decode('latin-1')
        if calls and calls[-1][0] == 'say':
            calls[-1][1].append(name)
        else:
            calls.append(['say_release', name])
    emu.stub(SPEECH_RELEASE_CLIP, on_release)
    emu.stub(FREEMEM, lambda eax: None)
    fixed_stubs += [emu.stub(UPDATE_EFFECTS, lambda eax: calls.append(['update_effects'])),
                    emu.stub(SETUP_FACEOFF, lambda eax: calls.append(['setup_faceoff']))]
    emu.stub(SPEECH_STOP_CHANNELS, lambda eax: None)
    emu.stub(DRAW_LINE_INDICATOR, lambda eax: calls.append(['draw_line_indicator', eax & 0xffff,
                                                           struct.unpack('<i', struct.pack('<I', emu.uc.reg_read(UC_X86_REG_EDX)))[0]]))
    speech = SPEECH
    emu.stub(SPEECH_BUSY, lambda eax: speech['busy'])

    def s32(v):
        return v - (1 << 32) if v & 0x80000000 else v
    emu.stub(PLAY_SPEECH, lambda eax: calls.append(['play_speech', s32(eax & 0xffffffff)]))

    def on_clip(eax):
        # (the frames from the clip's PPV file, then the script as load_cutscene_clip sets it)
        clip = struct.unpack('<h', struct.pack('<H', eax & 0xffff))[0]
        calls.append(['load_clip', s32(eax & 0xffffffff)])
        emu.write(0xcbecc, struct.pack('<h', clip))
        ptr = struct.unpack('<I', emu.read(CLIP_SCRIPTS + 4 * clip, 4))[0]
        emu.write(CLIP_SCRIPT, struct.pack('<I', ptr))
        emu.write(0xe9ab2, emu.read(0xcc054 + 4 * clip, 2))
        emu.write(0xe9ab4, struct.pack('<h', 1))
        emu.write(0xcbece, struct.pack('<h', struct.unpack('<b', emu.read(ptr + 1, 1))[0]))
    emu.stub(LOAD_CUTSCENE_CLIP, on_clip)
    ppi_stub = emu.stub(PUT_PLAYER_ON_ICE, lambda eax: calls.append(['put_player_on_ice', ((eax & 0xffffffff) - ENTITIES) // 0x80,
                                                                    s32(emu.uc.reg_read(UC_X86_REG_EDX)) & 0xffff]))
    pp4p_stub = emu.stub(PICK_PLAYER_FOR_POSITION, lambda eax: calls.append(['pick_player_for_position', s32(eax & 0xffffffff),
                                                                             s32(emu.uc.reg_read(UC_X86_REG_EDX))]))
    # the panel's names measured with SCOR2B as the game loads it
    with open(os.path.join(os.path.dirname(exe), 'SCOR2B.VFN'), 'rb') as f:
        font = emu.alloc(f.read())
    emu.write(FONT_SCOR2B, struct.pack('<I', font))
    emu.write(FONT_CURRENT_DEFAULT, struct.pack('<I', font))
    roster_db_load(os.path.dirname(exe))
    emu.call(ENTITIES_INIT)
    tables = []
    for ti, t in enumerate(TEAM_RECORDS):
        # the line tables, the player records (`rosters`, a status byte first) and the ratings
        # where entities_init points the team records
        emu.write(LINE_TABLES[ti], bytes(DEFAULT_LINE_TABLE))
        emu.write(t + 0xda, struct.pack('<I', LINE_TABLES[ti]))
        emu.write(t + 0xde, struct.pack('<I', PLAYER_RATINGS + ti * 0x1f4))
        emu.write(t + 0xee, struct.pack('<I', ROSTERS + ti * 0x444))
        ps = PLAYER_STATS[ti]                    # (show_penalty reads the scorer's goals there)
        gs = emu.alloc(b'\0' * 3 * 6)
        emu.write(t + 0xe6, struct.pack('<I', ps))
        emu.write(t + 0xea, struct.pack('<I', gs))
        emu.write(t + 0xf2, struct.pack('<I', emu.alloc(b'\0' * 0x400)))
        tables.append((ps, gs))
    base = emu.read(ENTITIES, 17 * 0x80)
    out = {'base': [dict(entity_fields(emu, i), prev=list(struct.unpack('<iii', emu.read(ENTITIES + i * 0x80 + 0x74, 12))))
                    for i in range(17)]}
    for group, choices in AI_GROUPS.items():
        cases = []
        for k in range(100 * len(choices)):
            state, actors = choices[k % len(choices)]
            g, teams, carrier = ai_world(emu, rnd, base, tables)
            actor = rnd.choice(actors)
            carrier = ai_prepare(emu, rnd, state, actor, g)
            for ti in range(2):
                teams[ti]['roster_status'] = [emu.read(ROSTERS + ti * 0x444 + i * 0x27, 1)[0] for i in range(28)]
            speech['busy'] = g['speech_busy']
            rec = bytearray(emu.read(ENTITIES + actor * 0x80, 0x80))
            sp = struct.unpack_from('<h', rec, 0x1c)[0] & 7
            rec[0x1e + sp] = state
            if rnd.random() < 0.3:
                rec[0x44] |= 2                       # the state just entered
            emu.write(ENTITIES + actor * 0x80, rec)
            seed = rnd.getrandbits(32)
            emu.write(SEED, struct.pack('<I', seed))
            # the scratch dword e03ac as an earlier routine left it (ai_nearest_to_puck reads it
            # when the puck is carried by a team mate)
            scratch_ac = (0xffffffff, (seed >> 4) & 0x1ff, (seed >> 4) & 0xfff, (seed >> 4) & 0xffff)[seed & 3]
            emu.write(SCRATCH[2], struct.pack('<I', scratch_ac))
            # e03bc / e03c0 too (ai_shoot aims with e03bc)
            scratch = [(seed >> 7) & 0xffff, (seed >> 13) & 0xffff]
            emu.write(SCRATCH[0], struct.pack('<H', scratch[0]))
            emu.write(SCRATCH[1], struct.pack('<H', scratch[1]))
            # the stack below the call as garbage no slot number matches (ai_nearest_to_puck reads a
            # local it sets only when no team mate carries the puck)
            emu.write(STACK_TOP - 0x2100, b'\xcc' * 0x2000)
            befores = {str(s_): dict(entity_fields(emu, s_), prev=list(struct.unpack('<iii', emu.read(ENTITIES + s_ * 0x80 + 0x74, 12))))
                       for s_ in range(17)}
            order = draw_order(emu)
            handler = struct.unpack('<I', emu.read(AI_HANDLERS + 4 * state, 4))[0]
            del calls[:]
            emu.call(handler, eax=ENTITIES + actor * 0x80)
            after = ai_record(emu)
            cases.append({'state': state, 'actor': actor, 'globals': g, 'teams': teams, 'carrier': carrier, 'seed': seed,
                          'scratch_ac': scratch_ac, 'scratch': scratch,
                          'before': befores, 'order': order, 'calls': [list(c) for c in calls],
                          'after': {str(s_): {k_: v for k_, v in entity_fields(emu, s_).items() if befores[str(s_)].get(k_) != v}
                                    for s_ in range(17)},
                          'world_after': after})
            for a, n in ((GAME_FLAGS, 1), (OPTION_FLAGS, 4), (STOP_FLAGS, 2), (MISC_FLAGS, 4), (BREAKAWAY_FLAG, 4),
                         (PENALTY_SHOT_ACTIVE, 4), (PENALTY_SHOT_SETUP, 4), (PENALTY_SHOT_PHASE, 4)):
                emu.write(a, b'\0' * n)
        for c in cases:
            c['before'] = {s_: {k_: v for k_, v in b.items() if out['base'][int(s_)].get(k_) != v} for s_, b in c['before'].items()}
            c['after'] = {s_: a for s_, a in c['after'].items() if a}
        out[group] = cases
    out['lines'] = lines_cases(emu, rnd, base, tables, calls, out['base'], os.path.join(os.path.dirname(exe), 'TEAMS.DB'))
    out['controls'] = controls_cases(emu, rnd, base, tables, calls, out['base'])
    for h in queue_stubs:
        emu.uc.hook_del(h)
    out['rules'] = rules_cases(emu, rnd, base, tables, calls, out['base'], speech)
    for h in fixed_stubs:
        emu.uc.hook_del(h)
    out['goals'] = goals_cases(emu, rnd, base, tables, calls, out['base'], speech)
    out['faceoffs'] = pface_cases(emu, rnd, base, tables, calls, out['base'], speech)
    out['steps'] = steps_cases(emu, rnd, base, tables, calls, out['base'], speech)
    out['runs'] = steps_cases(emu, rnd, base, tables, calls, out['base'], speech, 150, (50, 100, 200, 400))
    out['periods'] = periods_cases(emu, rnd, base, tables, calls, out['base'], speech)
    emu.uc.hook_del(ppi_stub)
    out['dress'] = dress_cases(emu, rnd, base, tables, calls, out['base'])
    emu.uc.hook_del(pp4p_stub)
    emu.uc.hook_del(injure_stub)
    out['lineup'] = lineup_cases(emu, rnd, base, tables, calls, out['base'], os.path.join(os.path.dirname(exe), 'TEAMS.DB'))
    out['hud'] = hud_cases(emu, rnd, calls)
    out['cup'] = cup_cases(emu, rnd)
    return out


CUP_SERIES = 0xdc338                           # dword_dc338 (alloc_cup_banner): the play-off final's 7 games, 6 bytes each
SESSION_MODE = 0xc53fb                         # dword_c53fb: 0 exhibition, 1 a play-off series alone, 2 a league


def cup_cases(emu, rnd, count=300):
    '''game_over_check called directly: does a win by this score end the play-off final? Random
    series of 4 to 7 scheduled games between two teams (home ice changing as in the play-offs), some
    of them played, the score of the game, a league, a play-off series alone (its length from the
    options) or no final at all'''
    buf = emu.alloc(b'\xff' * 64)
    cases = []
    for k in range(count):
        mode = rnd.choice((0, 1, 2, 2))
        has = rnd.random() < 0.9
        teams = rnd.sample(range(26), 2)
        scheduled = rnd.choice((4, 5, 6, 7, 7))
        played = rnd.randrange(min(scheduled, 7))
        rec = bytearray(b'\xff' * 42)
        for g_ in range(scheduled):
            home, away = teams if g_ in (0, 1, 4, 6) else teams[::-1]
            rec[g_ * 6:g_ * 6 + 4] = bytes([g_, 0, home, away])
            if g_ < played:
                a = rnd.randrange(8)
                b = rnd.choice([x for x in range(8) if x != a])
                rec[g_ * 6 + 4:g_ * 6 + 6] = bytes([a, b])
        settings2 = rnd.randrange(256)
        hg = rnd.randrange(10)
        ag = rnd.choice([x for x in range(10) if x != hg] + [hg] * (rnd.random() < 0.05))
        emu.write(buf, bytes(rec))
        emu.write(CUP_SERIES, struct.pack('<I', buf if has else 0))
        emu.write(SESSION_MODE, struct.pack('<i', mode))
        emu.write(OPTION_FLAGS, struct.pack('<I', rnd.randrange(256) | (settings2 << 8)))
        ret = emu.call(GAME_OVER_CHECK, eax=hg, edx=ag)
        cases.append({'routine': 'game_over_check', 'args': [hg, ag], 'series': list(rec) if has else [], 'mode': mode,
                      'settings2': settings2, 'after': {'ret': ret, 'series': list(emu.read(buf, 42)) if has else []}})
    emu.write(CUP_SERIES, b'\0' * 4)
    emu.write(SESSION_MODE, b'\0' * 4)
    emu.write(OPTION_FLAGS, b'\0' * 4)
    return cases


HUD_ROUTINES = {'add_penalty_display': ADD_PENALTY_DISPLAY, 'penalty_list_find': PENALTY_LIST_FIND,
                'penalty_lists_reset': 0x1cbd8, 'draw_clock': 0x14cf1, 'hud_clock_count_down': 0x15374,
                'penalty_clocks_count_down': 0x15655}
LC_PROMPTS = (0xcbc6a, 0xcbc6c)                # line_change_prompt, word_cbc6c


def hud_cases(emu, rnd, calls, count=100):
    '''the scoreboard's clock and penalty lists: add_penalty_display, penalty_list_find,
    penalty_lists_reset, draw_clock (its drawing stubbed: the count down and the panels' choice),
    hud_clock_count_down and penalty_clocks_count_down called on random scoreboards'''
    stubs = [emu.stub(a, lambda eax: None, pop=p) for a, p in
             ((0x8c1c2, 0), (0x14bef, 0), (0x1540a, 0), (0x15707, 0), (0x157bd, 4), (0xb4cf2, 0), (0x15995, 0), (0x1cc3d, 0))]
    cases = []
    for k in range(count * len(HUD_ROUTINES)):
        name = list(HUD_ROUTINES)[k % len(HUD_ROUTINES)]
        h = hud_random(rnd)
        hud_write(emu, h)
        no_stats = rnd.choice((0, 0, 0, 1))
        prompts = [rnd.choice((0, 0, 0, 1)), rnd.choice((0, 0, 0, 1))]
        frame = rnd.choice((0, 4, 5, 100, rnd.randrange(200), rnd.randrange(130000)))
        emu.write(GAME_FLAGS, bytes([no_stats << 4]))
        for t in range(2):
            emu.write(LC_PROMPTS[t], struct.pack('<h', prompts[t]))
        emu.write(HUD_HUNDREDTHS, struct.pack('<i', frame))
        emu.write(HUD_FRAME, struct.pack('<i', 0))
        args = []
        regs = {}
        if name in ('add_penalty_display', 'penalty_list_find'):
            t = rnd.choice((0, 1, 1, 0x100))
            nums = [x for x in h['lists'][1 if t & 0xffff else 0][::4] if x >= 0]
            number = rnd.choice(nums) if nums and rnd.random() < 0.7 else rnd.randrange(1, 100)
            args = [t, number]
            regs = {'eax': t, 'edx': number}
            if name == 'add_penalty_display':
                args.append(rnd.choice((2, 4, 5, 10)))
                regs['ebx'] = args[2]
        elif name == 'hud_clock_count_down':
            args = [frame]
            regs = {'eax': frame}
        elif name == 'penalty_clocks_count_down':
            t = rnd.randrange(2)
            args = [t, frame]
            regs = {'eax': HUD_LISTS[t], 'edx': frame}
        del calls[:]
        ret = emu.call(HUD_ROUTINES[name], **regs)
        cases.append({'routine': name, 'args': args, 'hud': h, 'no_stats': no_stats, 'prompts': prompts, 'frame': frame,
                      'after': dict(hud_read(emu), ret=s32(ret) if name == 'hud_clock_count_down' else 0,
                                    frame=struct.unpack('<i', emu.read(HUD_HUNDREDTHS, 4))[0],
                                    counted=struct.unpack('<i', emu.read(HUD_FRAME, 4))[0])})
    emu.write(GAME_FLAGS, b'\0')
    for t in range(2):
        emu.write(LC_PROMPTS[t], b'\0\0')
    for h_ in stubs:
        emu.uc.hook_del(h_)
    return cases


RULE_ROUTINES = {'update_stoppage': 0x63bf8, 'process_infractions': 0x637b5, 'start_stoppage': 0x63543,
                 'penalty_box_update': 0x62ee9, 'penalty_timers': 0x63a37, 'penalty_expired': 0x639f9,
                 'release_from_box': 0x6392a, 'goal_ends_penalty': 0x63d69, 'update_power_play': 0x63c73,
                 'count_penalized': 0x5df86, 'penalty_time_left': 0x54a53, 'queue_infraction': 0x62d80,
                 'maybe_queue_infraction': 0x62cf9, 'ref_announce': 0x62ea2, 'update_line_timers': 0x63b85,
                 'sim_game_state': 0x5c302, 'game_clock_tick': 0x5dc10, 'time_announcements': 0x5a77c,
                 'period_strategy_init': 0x5a669, 'clear_infractions': 0x63d3c, 'record_penalty': 0x624b9,
                 'announce_goal': 0x62343}
INFRACTION_QUEUE = 0xe9a16
PANEL_LINE4 = 0xe0344                          # byte_e0344: the panel's fifth line ("served by #%d")
INF_TYPES = (3, 4, 6, 7, 8, 9, 11, 12, 13, 15, 16, 18, 21, 22, 23, 24, 26, 0x1d, 5, 0x1c)


def random_boxes(emu, rnd, teams):
    '''players in the penalty boxes: their penalty times with the flags (just called, major,
    coincidental), the box queues, statuses; now and then players out (injured, misconduct); the
    count of skaters'''
    for ti, t in enumerate(TEAM_RECORDS):
        ent = list(teams[ti]['entity_of'])
        status = list(teams[ti].get('roster_status', [3] * 28))
        bq = []
        for r in rnd.sample(range(1, 25), rnd.choice((0, 0, 1, 1, 2, 3))):
            secs = rnd.choice((0, 1, 2, 5, 6, 30, 120, 300))
            ent[r] = secs | rnd.choice((0, 0, 0x2000, 0x4000, 0x1000, 0x6000))
            status[r] = 5
            bq.append(r)
        for r in range(28):
            if ent[r] == -2 and rnd.random() < 0.08:
                ent[r] = rnd.choice((-3, -4, -5))
        bq += [-1] * (28 - len(bq))
        emu.write(t + 0x7e, struct.pack('<28h', *ent))
        emu.write(t + 0xb6, struct.pack('<28b', *bq))
        for i in range(28):
            emu.write(ROSTERS + ti * 0x444 + i * 0x27, bytes([status[i] & 0xff]))
        sk = rnd.choice((6, 6, 5, 4))
        emu.write(t + 0x36, struct.pack('<h', sk))
        teams[ti].update({'entity_of': ent, 'box_queue': bq, 'roster_status': status, 'skaters': sk})


def rules_cases(emu, rnd, base, tables, calls, base_fields, speech):
    '''the rules and the stoppages called directly: the infraction queue (calls, penalties, delayed
    calls, stoppages started or not), players in the box (penalty times with their flags, the box
    queue, majors, coincidental ones, injured culprits), the stoppage, whistle and announcement
    timers, the power play, the clock near the full minutes and at 0:00, the scores'''
    names = list(RULE_ROUTINES)
    cases = []
    for k in range(100 * len(names)):
        name = names[k % len(names)]
        g, teams, carrier = ai_world(emu, rnd, base, tables)
        g['game_flags'] = (g['game_flags'] & ~0x0d) | rnd.choice((0, 1, 5, 5, 1, 9, 0xd, 8))
        g['stop_flags'] = rnd.choice((0, 0, 0x20, 0x60, 0x24, 0x80, 1))
        g['penalty_box_mode'] = rnd.choice((0, 0, 0, 1))
        g['ref_phase'] = rnd.choice((-1, -1, 0, 1))
        g['action_flags'] = rnd.choice((0, 0, 0, 0x80, 4))
        g['clip'] = rnd.choice((-1, -1, 0, 2, 5))
        g['panel'] = rnd.choice((-1, -1, -1, 0x20, 0x100))
        g['speech_busy'] = rnd.choice((0, 0, 0, 1))
        speech['busy'] = g['speech_busy']
        g['penalty_shot_setup'] = rnd.choice((0, 0, 0, 1))
        g['penalty_shot_active'] = rnd.choice((0, 0, 0, 0, 1))
        g['injury_stoppage'] = rnd.choice((0, 0, 0, 1))
        g['clock_seconds'] = rnd.choice((0, 0x3c, 0x3d, 0x78, 0xb4, 0x12c, 0x258, 0x259, rnd.randrange(0x300)))
        g['clock_sub'] = rnd.choice((0, 0, 1, 0x17))
        g['period'] = rnd.choice((0, 1, 1, 2, 2, 3))
        if name in ('game_clock_tick', 'sim_game_state', 'time_announcements', 'ref_announce'):
            g['settings2'] |= rnd.choice((0, 1, 1))   # the announcer on (option byte 2 bit 0)
        if name == 'game_clock_tick' and rnd.random() < 0.3:
            g['clock_seconds'], g['clock_sub'] = 0x3d, 0  # the last minute starts (announce_one_minute_left)
        if rnd.random() < 0.5:
            g['crowd'] = rnd.choice((0x100, 0x300, 0x3e0))
        # the queue
        q = []
        for _ in range(rnd.choice((0, 1, 1, 2, 3, 4))):
            q.append([rnd.choice(INF_TYPES), rnd.randrange(12) | rnd.choice((0, 0, 0x80))])
        raw = bytearray(64)
        for i, (t_, s_) in enumerate(q):
            raw[2 * i] = t_
            raw[2 * i + 1] = s_
        emu.write(INFRACTION_QUEUE, bytes(raw))
        g['infraction0'] = raw[0]
        random_boxes(emu, rnd, teams)
        # the scoreboard's penalty lists (the numbers of the players in the box now and then)
        g['hud'] = hud_random(rnd, [[emu.read(ROSTERS + ti * 0x444 + r * 0x27 + 5, 1)[0] for r in teams[ti]['box_queue'] if r >= 0]
                                    for ti in range(2)])
        write_globals(emu, g)
        emu.write(OPTION_FLAGS, struct.pack('<I', (g['option_flags'] & 0xff) | (g['settings2'] << 8)))
        emu.write(PERIOD_NUM, struct.pack('<h', g['period'] + 1))
        emu.write(PANEL_LINE4, b'\0' * 0x20)
        emu.write(PUCK + 0x42, bytes([carrier & 0xff]))
        seed = rnd.getrandbits(32)
        emu.write(SEED, struct.pack('<I', seed))
        scratch_ac = rnd.getrandbits(32)
        scratch = [rnd.getrandbits(16), rnd.getrandbits(16)]
        emu.write(SCRATCH[2], struct.pack('<I', scratch_ac))
        emu.write(SCRATCH[0], struct.pack('<H', scratch[0]))
        emu.write(SCRATCH[1], struct.pack('<H', scratch[1]))
        befores = {str(s_): dict(entity_fields(emu, s_), prev=list(struct.unpack('<iii', emu.read(ENTITIES + s_ * 0x80 + 0x74, 12))))
                   for s_ in range(17)}
        order = draw_order(emu)
        t = rnd.randrange(2)
        regs = {}
        args = []
        if name in ('penalty_timers', 'count_penalized'):
            if name == 'penalty_timers':
                args = [t]
                regs = {'eax': TEAM_RECORDS[t]}
        elif name in ('penalty_expired', 'release_from_box'):
            r = rnd.choice([x for x in teams[t]['box_queue'] if x >= 0] or [rnd.randrange(25)])
            args = [t, r]
            regs = {'eax': TEAM_RECORDS[t], 'edx': r}
        elif name == 'goal_ends_penalty':
            args = [t]
            regs = {'eax': t}
        elif name == 'start_stoppage':
            args = [rnd.randrange(max(1, len(q)))]
            regs = {'eax': args[0]}
        elif name in ('queue_infraction', 'maybe_queue_infraction'):
            slot = rnd.randrange(12) if rnd.random() < 0.9 else rnd.choice((14, 16))
            args = [slot, rnd.choice(INF_TYPES)]
            regs = {'eax': ENTITIES + slot * 0x80, 'edx': args[1]}
        elif name == 'ref_announce':
            args = [rnd.choice(INF_TYPES)]
            regs = {'eax': args[0]}
        elif name == 'record_penalty':
            # (team, player, the penalty (0x11 the penalty shot), minutes) + the time, the queue index
            args = [t, rnd.randrange(28), rnd.choice((rnd.randrange(0x12), 0x11, 4, 5, 6)), rnd.choice((2, 2, 4, 5, 10)),
                    rnd.randrange(20), rnd.randrange(60), rnd.choice((0, 0, 1, 2, 3))]
            regs = {'eax': args[0], 'edx': args[1], 'ebx': args[2], 'ecx': args[3], 'stack': args[4:]}
            g['panel'] = rnd.choice((-1, -1, 0x20))
        elif name == 'announce_goal':
            # (team, scorer, assists or -1) + the goal flags and the time as ai_ref_call_penalty passes them
            el = g['period_length'] - g['clock_seconds']
            if g['clock_seconds'] < 0x3c and g['clock_sub'] != 0:
                el -= 1
            mm = int(el / 60)
            ss = el - mm * 60
            args = [t, rnd.randrange(25), rnd.choice((-1, rnd.randrange(25))), rnd.choice((-1, rnd.randrange(25)))]
            regs = {'eax': args[0], 'edx': args[1], 'ebx': args[2], 'ecx': args[3], 'stack': (g['goal_flags'], mm, ss)}
        if name in ('record_penalty', 'announce_goal'):
            g['last_penalty_team'] = rnd.choice((-1, -1, 0, 1))
            g['game_flags'] = g['game_flags'] | rnd.choice((0, 0, 0, 0x10))
            write_globals(emu, g)
        del calls[:]
        ret = emu.call(RULE_ROUTINES[name], **regs)
        after = ai_record(emu)
        cases.append({'routine': name, 'args': args, 'globals': g, 'teams': teams, 'carrier': carrier, 'seed': seed,
                      'scratch_ac': scratch_ac, 'scratch': scratch, 'infq': list(raw),
                      'before': befores, 'order': order, 'calls': [list(c) for c in calls],
                      'after': {str(s_): {k_: v for k_, v in entity_fields(emu, s_).items() if befores[str(s_)].get(k_) != v}
                                for s_ in range(17)},
                      'world_after': after,
                      'lines_after': {'infq': list(emu.read(INFRACTION_QUEUE, 64)),
                                      'panel4': emu.read(PANEL_LINE4, 0x20).split(b'\0')[0].decode('latin-1'),
                                      'ret': struct.unpack('<i', struct.pack('<I', ret))[0]}})
        for a, n_ in ((GAME_FLAGS, 1), (OPTION_FLAGS, 4), (STOP_FLAGS, 2), (MISC_FLAGS, 4), (BREAKAWAY_FLAG, 4),
                      (PENALTY_SHOT_ACTIVE, 4), (PENALTY_SHOT_SETUP, 4), (PENALTY_SHOT_PHASE, 4)):
            emu.write(a, b'\0' * n_)
        emu.write(INFRACTION_QUEUE, b'\0' * 64)
        for t_ in TEAM_RECORDS:
            emu.write(t_ + 0x44, b'\0')
    for c in cases:
        c['before'] = {s_: {k_: v for k_, v in b.items() if base_fields[int(s_)].get(k_) != v} for s_, b in c['before'].items()}
        c['after'] = {s_: a for s_, a in c['after'].items() if a}
    return cases


GOAL_ROUTINES = {'score_goal': 0x5ab36, 'goal_disallowed_check': 0x5aaae, 'setup_faceoff': 0x5d852,
                 'begin_penalty_shot': 0x64398, 'start_penalty_shot': 0x63f72, 'end_penalty_shot': 0x64439,
                 'breakaway_foul': 0x6427f, 'injury_check': 0x65b83, 'update_effects': 0x615a2,
                 'goal_milestone_check': 0x62807}
DRAW_SCORE_DIGITS = 0x14a20                    # stubbed: the scoreboard digits; (team, goals)
GAME_OVER_CHECK = 0x15c30                      # does the game decide the Stanley Cup; (home goals, away goals); stubbed in the match groups (a case input)
START_CROWD_FIGURE = 0x614c2
CROWD_FIGURES = 0xdee94                        # 20 x 12 bytes
CROWD_BUSY = 0xe9b2c                           # the spots in use: 11 words of bits
CROWD_SEQUENCES = 0xcce00


def s32(v):
    return v - (1 << 32) if v & 0x80000000 else v


def crowd_read(emu):
    recs = []
    for i in range(20):
        b = emu.read(CROWD_FIGURES + i * 12, 12)
        recs.append([struct.unpack_from('<h', b, 0)[0], struct.unpack_from('<b', b, 2)[0], struct.unpack_from('<b', b, 3)[0], b[4],
                     struct.unpack_from('<h', b, 5)[0], struct.unpack_from('<h', b, 7)[0], struct.unpack_from('<h', b, 9)[0],
                     struct.unpack_from('<b', b, 11)[0]])
    return [recs, list(struct.unpack('<11H', emu.read(CROWD_BUSY, 22)))]


def stats_read(emu, tables):
    out = [[], [], [], []]
    for t, (ps, gs) in enumerate(tables):
        raw = emu.read(ps, 25 * 0x10)
        out[t] = [list(struct.unpack_from('<8h', raw, r * 0x10)) for r in range(25)]
        raw = emu.read(gs, 18)
        out[2 + t] = [list(struct.unpack_from('<3h', raw, g * 6)) for g in range(3)]
    return out


def goals_cases(emu, rnd, base, tables, calls, base_fields, speech):
    '''the goals, the penalty shots and the end of a period called directly: goals for either team
    (stopped play, a delayed penalty, offside, a penalty shot under way, power play, short handed
    and empty net goals, the scorers' statistics, the box released, the CPU coaches' reviews), the
    final whistle (ties, overtime, the winners out of the box, the Stanley Cup), a penalty shot
    called, started and over, fouls on a breakaway, the players a team may lose, the crowd'''
    names = list(GOAL_ROUTINES)
    cup = {'v': 0}
    stubs = [emu.stub(DRAW_SCORE_DIGITS, lambda eax: calls.append(['draw_score_digits', s32(eax & 0xffffffff),
                                                                   s32(emu.uc.reg_read(UC_X86_REG_EDX))])),
             emu.stub(GAME_OVER_CHECK, lambda eax: (calls.append(['game_over_check', s32(eax & 0xffffffff),
                                                                  s32(emu.uc.reg_read(UC_X86_REG_EDX))]), cup['v'])[1])]
    cases = []
    for k in range(100 * len(names)):
        name = names[k % len(names)]
        g, teams, carrier = ai_world(emu, rnd, base, tables)
        g['game_flags'] = rnd.choice((0, 0, 0, 2, 8, 0x10, 1, 0x12, 9, 0xa))
        g['stop_flags'] = rnd.choice((0, 0, 0x10, 0x20, 0x60))
        g['settings2'] = rnd.choice((0, 2, 1, 3))
        g['user1_team'] = rnd.choice((0, 1, 2))
        g['user2_team'] = rnd.choice((0, 0, 1, 2))
        g['last_touch_slot'] = rnd.randrange(-1, 12)
        g['period'] = rnd.choice((0, 1, 2, 2, 3, 3))
        g['clock_seconds'] = rnd.choice((0, 0x3c, 0x78, 0x258, rnd.randrange(0x300)))
        g['crowd'] = rnd.choice((0, 0x100, 0x15e, 0x15f, 0x2bc, 0x2bd, 0x320, 0x4b0, 0x5dc, 0x708, 0x7d0, rnd.randrange(2000)))
        g['excitement'] = rnd.randrange(200)
        g['penalty_shot_active'] = rnd.choice((0, 0, 0, 1))
        g['penalty_shot_phase'] = rnd.choice((0, 0, 1)) if not g['penalty_shot_active'] else rnd.choice((1, 1, 0))
        g['penalty_shot_slot'] = rnd.choice((-1, rnd.randrange(12)))
        g['penalty_shot_team'] = rnd.randrange(2)
        g['penalty_shot_spot_x'] = rnd.choice((0, -0x50, 0x50))
        g['penalty_shot_spot_y'] = rnd.choice((0, -0x9a, 0x9a, 0x56))
        g['penalty_shot_roster'] = rnd.choice((-1, 3))
        g['goal_flags'] = rnd.choice((1, 2, 4))
        g['puck_in_net'] = rnd.choice((0, 1))
        g['speech_busy'] = 0
        speech['busy'] = 0
        cup['v'] = rnd.choice((0, 0, 1))
        for ti, t in enumerate(TEAM_RECORDS):
            f = teams[ti]
            f['goals'] = rnd.randrange(7)
            f['carrier0'] = rnd.randrange(25)
            f['carrier1'] = rnd.choice((-1, rnd.randrange(28)))
            f['carrier2'] = rnd.choice((-1, rnd.randrange(28)))
            f['goalie_request'] = rnd.choice((0, 0, 1, -256, -16))
            f['strategy'] = rnd.randrange(4)
            f['strategy2'] = rnd.randrange(4)
            for n_ in ('one_timer_goals', 'breakaway_goals', 'penalty_shots', 'penalty_shot_goals'):
                f[n_] = rnd.randrange(3)
            if rnd.random() < 0.2:
                f['flags'] |= 0x10
            for n_, o, sz in AI_TEAM_FIELDS:
                emu.write(t + o, struct.pack('<' + _FMT[sz], f[n_] if sz < 0 else f[n_] & ((1 << (8 * sz)) - 1)))
        random_boxes(emu, rnd, teams)
        # the statistics
        for t, (ps, gs) in enumerate(tables):
            raw = bytearray(25 * 0x10)
            for r in range(25):
                struct.pack_into('<8h', raw, r * 0x10, rnd.randrange(5), rnd.randrange(5), rnd.randrange(10), rnd.randrange(-5, 6),
                                 rnd.randrange(3), rnd.randrange(2), rnd.randrange(2), rnd.randrange(10))
            emu.write(ps, bytes(raw))
            emu.write(gs, struct.pack('<9h', *[rnd.randrange(30) for _ in range(9)]))
        # the players: penalized (a delayed call), knocked down, waiting on the bench for the penalty
        # shot, off the ice
        for slot in range(12):
            rec = bytearray(emu.read(ENTITIES + slot * 0x80, 0x80))
            fl2 = rec[0x45]
            if rnd.random() < 0.15:
                fl2 |= 0x10
            if rnd.random() < 0.1:
                fl2 |= 1
            rec[0x45] = fl2
            sp = struct.unpack_from('<h', rec, 0x1c)[0] & 7
            if rnd.random() < 0.1:
                rec[0x1e + sp] = 0x2d
            line = struct.unpack_from('<h', rec, 0x1a)[0]
            if name == 'setup_faceoff' and line > 0 and rnd.random() < 0.15:
                struct.pack_into('<h', rec, 0x1a, -1)
            emu.write(ENTITIES + slot * 0x80, rec)
        args = []
        regs = {}
        if name == 'score_goal':
            net = rnd.choice((12, 13))
            nrec = emu.read(ENTITIES + net * 0x80, 0x80)
            nx, ny = struct.unpack_from('<h', nrec, 2)[0], struct.unpack_from('<h', nrec, 6)[0]
            puck = bytearray(emu.read(PUCK, 0x80))
            put_fields(puck, {'x': (nx + rnd.randrange(-12, 13)) << 16 | rnd.randrange(0x10000),
                              'y': (ny + rnd.randrange(-6, 7)) << 16 | rnd.randrange(0x10000), 'z': rnd.randrange(0x40000)})
            emu.write(PUCK, puck)
            # shot_landed takes the shooter's record as it is (no shooter: the bytes before the records)
            g['last_touch_slot'] = rnd.randrange(12)
            g['last_shooter'] = rnd.randrange(12)
            args = [net]
            regs = {'eax': ENTITIES + net * 0x80}
        elif name == 'goal_milestone_check':
            # the net the puck is in (the team that scored), the scorer and the assists of the team
            # records (the scorer's low byte; assists unset with the high byte set)
            puck = bytearray(emu.read(PUCK, 0x80))
            put_fields(puck, {'y': rnd.choice((-1, 1)) * rnd.randrange(0xc0, 0xf0) << 16})
            emu.write(PUCK, puck)
            for ti, t in enumerate(TEAM_RECORDS):
                hist = [rnd.choice((rnd.randrange(25), rnd.randrange(25), rnd.randrange(25) - 0x100, 25, 30))] + \
                       [rnd.choice((rnd.randrange(25), rnd.randrange(25), rnd.randrange(25) - 0x100, -1, 26)) for _ in range(2)]
                emu.write(t + 0x30, struct.pack('<3h', *hist))
                # the records of the scorer and the assists set to land on a milestone now and then
                # (a first career goal, the 50th goal, the 100th point, the 100th career goal or
                # point, the play-offs' 10th goal or 20th point)
                f = teams[ti]
                for k, r in enumerate(hist):
                    r = r & 0xff if k == 0 else r
                    if not 0 <= r < 25:
                        continue
                    gl, ast = struct.unpack('<hh', emu.read(tables[ti][0] + r * 0x10, 4))
                    target = rnd.choice(('none', 'first', 'g50', 'p100', 'cg100', 'cp100', 'g10', 'p20'))
                    if target == 'first' and k == 0:
                        gl = 1
                        emu.write(tables[ti][0] + r * 0x10, struct.pack('<h', 1))
                        f['career_goals'][r] = f['season_goals'][r] = 0
                    elif target in ('g50', 'g10'):
                        f['season_goals'][r] = (50 if target == 'g50' else 10) * rnd.randrange(1, 3) - gl
                    elif target in ('p100', 'p20'):
                        f['season_points'][r] = (100 if target == 'p100' else 20) * rnd.randrange(1, 3) - gl - ast
                    elif target == 'cg100':
                        f['career_goals'][r] = 100 * rnd.randrange(1, 4) - gl - f['season_goals'][r]
                    elif target == 'cp100':
                        f['career_points'][r] = 100 * rnd.randrange(1, 4) - gl - ast - f['season_points'][r]
                    emu.write(SEASON_RECORDS + ti * 0x190 + r * 0x10,
                              struct.pack('<4i', f['career_goals'][r], f['career_points'][r], f['season_goals'][r], f['season_points'][r]))
        elif name == 'goal_disallowed_check':
            g['game_flags'] |= rnd.choice((8, 8, 0))
            puck = bytearray(emu.read(PUCK, 0x80))
            put_fields(puck, {'y': rnd.choice((-0xf0, 0xf0, rnd.randrange(-0x100, 0x100))) << 16})
            emu.write(PUCK, puck)
        elif name in ('begin_penalty_shot', 'start_penalty_shot'):
            g['penalty_shot_slot'] = rnd.randrange(12) if name == 'start_penalty_shot' or rnd.random() < 0.9 else -1
            g['penalty_shot_team'] = 1 if g['penalty_shot_slot'] > 5 else 0
            if name == 'start_penalty_shot':
                d = (1 if g['penalty_shot_team'] == 0 else 0)
                g['user1_slot'] = rnd.choice((-1, d * 6 + rnd.randrange(6), rnd.randrange(12)))
                g['user2_slot'] = rnd.choice((-1, d * 6 + rnd.randrange(6), rnd.randrange(12)))
                g['user1_team'] = rnd.choice((0, 1, 2, d + 1))
                g['user2_team'] = rnd.choice((0, 1, 2, d + 1))
        elif name == 'breakaway_foul':
            victim = rnd.choice(SKATERS)
            if rnd.random() < 0.8:
                carrier = victim
                emu.write(PUCK + 0x42, bytes([carrier]))
            g['breakaway'] = rnd.choice((0, 1, 1))
            vrec = bytearray(emu.read(ENTITIES + victim * 0x80, 0x80))
            put_fields(vrec, {'vy': rnd.randrange(-0x800, 0x801), 'y': rnd.randrange(-0x100, 0x101) << 16 | rnd.randrange(0x10000),
                              'heading': rnd.randrange(8) << 16 | rnd.randrange(0x10000)})
            emu.write(ENTITIES + victim * 0x80, vrec)
            args = [victim]
            regs = {'eax': ENTITIES + victim * 0x80}
        elif name == 'injury_check':
            victim = rnd.choice(tuple(range(12)) + (1, 2, 7, 8))
            vr = struct.unpack('<b', emu.read(ENTITIES + victim * 0x80 + 0x47, 1))[0]
            lists = []
            for ti in range(2):
                tl = [[-1] * 25 for _ in range(11)]
                d = rnd.sample(range(25), rnd.randrange(2, 9))
                if rnd.random() < 0.5 and 0 <= vr < 25 and (victim < 6) == (ti == 0) and vr not in d:
                    d[rnd.randrange(len(d))] = vr
                sk = rnd.sample(range(25), rnd.randrange(3, 20))
                tl[4][:len(d)] = d
                tl[7][:len(sk)] = sk
                status = [rnd.choice((3, 3, 4, 4, 0, 1, 2, 5, 7, 8)) for _ in range(28)]
                for i in range(28):
                    emu.write(ROSTERS + ti * 0x444 + i * 0x27, bytes([status[i]]))
                teams[ti]['roster_status'] = status
                lists.append(tl)
            for ti in range(2):
                for kk in range(11):
                    emu.write(POS_LISTS + kk * 0x32 + ti * 0x19, struct.pack('<25b', *lists[ti][kk]))
            args = [victim]
            regs = {'eax': ENTITIES + victim * 0x80}
        elif name == 'update_effects':
            for i in range(20):
                emu.write(CROWD_FIGURES + i * 12, struct.pack('<hbbbhhhb', -1, rnd.choice((0, 0, 1, 30)), 0, 0, 0, 0, 0, 0))
            emu.write(CROWD_BUSY, b'\0' * 22)
            free = list(range(0x85))
            rnd.shuffle(free)
            for i in rnd.sample(range(20), rnd.randrange(0, 15)):
                if i == 18:
                    spot = rnd.choice((0x87, 0x89 + rnd.randrange(0x11)))
                elif i == 19:
                    spot = rnd.choice((0x88, 0x9a + rnd.randrange(0x11)))
                elif i == 17 and rnd.random() < 0.3:
                    spot = rnd.choice((0x85, 0x86))
                else:
                    spot = free.pop()
                emu.call(START_CROWD_FIGURE, eax=i, edx=spot)
                b = bytearray(emu.read(CROWD_FIGURES + i * 12, 12))
                seq = struct.unpack_from('<h', b, 9)[0]
                n_ = abs(struct.unpack_from('<b', b, 11)[0])
                c_ = rnd.randrange(1, n_ + 1) if n_ > 0 else 1
                b[3] = c_
                b[4] = emu.read(CROWD_SEQUENCES + seq + c_, 1)[0]
                b[2] = rnd.choice((0, 0, 1, 5, 12))
                emu.write(CROWD_FIGURES + i * 12, bytes(b))
            # the spots the free figures left behind may still be marked
            if rnd.random() < 0.3:
                w = bytearray(emu.read(CROWD_BUSY, 22))
                for _ in range(rnd.randrange(1, 6)):
                    sp_ = rnd.randrange(0x85)
                    w[(sp_ >> 4) * 2 + ((sp_ & 15) >> 3)] |= 1 << (sp_ & 7)
                emu.write(CROWD_BUSY, bytes(w))
        q = []
        for _ in range(rnd.choice((0, 0, 1, 2))):
            q.append([rnd.choice(INF_TYPES), rnd.randrange(12) | rnd.choice((0, 0, 0x80))])
        raw = bytearray(64)
        for i, (t_, s_) in enumerate(q):
            raw[2 * i] = t_
            raw[2 * i + 1] = s_
        emu.write(INFRACTION_QUEUE, bytes(raw))
        g['infraction0'] = raw[0]
        write_globals(emu, g)
        emu.write(OPTION_FLAGS, struct.pack('<I', (g['option_flags'] & 0xff) | (g['settings2'] << 8)))
        emu.write(PERIOD_NUM, struct.pack('<h', g['period'] + 1))
        emu.write(PANEL_LINE4, b'\0' * 0x20)
        seed = rnd.getrandbits(32)
        emu.write(SEED, struct.pack('<I', seed))
        scratch_ac = rnd.getrandbits(32)
        scratch = [rnd.getrandbits(16), rnd.getrandbits(16)]
        emu.write(SCRATCH[2], struct.pack('<I', scratch_ac))
        emu.write(SCRATCH[0], struct.pack('<H', scratch[0]))
        emu.write(SCRATCH[1], struct.pack('<H', scratch[1]))
        befores = {str(s_): dict(entity_fields(emu, s_), prev=list(struct.unpack('<iii', emu.read(ENTITIES + s_ * 0x80 + 0x74, 12))))
                   for s_ in range(17)}
        for ti, t in enumerate(TEAM_RECORDS):
            teams[ti].update({n_: struct.unpack('<' + _FMT[sz], emu.read(t + o, abs(sz)))[0] for n_, o, sz in AI_TEAM_FIELDS})
        order = draw_order(emu)
        case = {'routine': name, 'args': args, 'globals': g, 'teams': teams, 'carrier': carrier, 'seed': seed,
                'scratch_ac': scratch_ac, 'scratch': scratch, 'infq': list(raw), 'cup': cup['v'], 'order': order}
        if name in ('score_goal', 'setup_faceoff', 'goal_milestone_check'):
            case['stats'] = stats_read(emu, tables)
        if name == 'injury_check':
            case['pos_lists'] = [[lists[ti][kk] for kk in range(11)] for ti in range(2)]
        if name == 'update_effects':
            case['crowd'] = crowd_read(emu)
        del calls[:]
        ret = emu.call(GOAL_ROUTINES[name], **regs)
        after = ai_record(emu)
        la = {'infq': list(emu.read(INFRACTION_QUEUE, 64)),
              'panel4': emu.read(PANEL_LINE4, 0x20).split(b'\0')[0].decode('latin-1'),
              'ret': struct.unpack('<i', struct.pack('<I', ret))[0],
              'scratch': list(struct.unpack('<hh', emu.read(SCRATCH[0], 2) + emu.read(SCRATCH[1], 2))),
              'scratch_ac': struct.unpack('<I', emu.read(SCRATCH[2], 4))[0]}
        if 'stats' in case:
            la['stats'] = stats_read(emu, tables)
        if 'crowd' in case:
            la['crowd'] = crowd_read(emu)
        case.update({'before': befores, 'calls': [list(c) for c in calls],
                     'after': {str(s_): {k_: v for k_, v in entity_fields(emu, s_).items() if befores[str(s_)].get(k_) != v}
                               for s_ in range(17)},
                     'world_after': after, 'lines_after': la})
        cases.append(case)
        for a, n_ in ((GAME_FLAGS, 1), (OPTION_FLAGS, 4), (STOP_FLAGS, 2), (MISC_FLAGS, 4), (BREAKAWAY_FLAG, 4),
                      (PENALTY_SHOT_ACTIVE, 4), (PENALTY_SHOT_SETUP, 4), (PENALTY_SHOT_PHASE, 4)):
            emu.write(a, b'\0' * n_)
        emu.write(INFRACTION_QUEUE, b'\0' * 64)
        emu.write(POS_LISTS, b'\xff' * (11 * 0x32))
        for t_ in TEAM_RECORDS:
            emu.write(t_ + 0x44, b'\0')
    for h in stubs:
        emu.uc.hook_del(h)
    for c in cases:
        c['before'] = {s_: {k_: v for k_, v in b.items() if base_fields[int(s_)].get(k_) != v} for s_, b in c['before'].items()}
        c['after'] = {s_: a for s_, a in c['after'].items() if a}
    return cases


PFACE_ROUTINES = {'ai_puck_faceoff': 0x516e1, 'ai_puck_faceoff2': 0x51bdb, 'end_of_period': 0x5dea6}
STOP_CROWD_LOOP = 0x59981                      # stubbed: the organ stops
CENTER_MOUSE = 0x50ade                         # stubbed
GSUMMARY_FLUSH = 0x61b85                       # stubbed: the stoppage's events into the game summary
PERIOD_CLEANUP = 0x5de70                       # stubbed: the next period or the end of the game
FREEMEM = 0x8d2d8                              # stubbed: the scoreboard clip's memory


def pface_cases(emu, rnd, base, tables, calls, base_fields, speech):
    '''the faceoff after a stoppage: ai_puck_faceoff (the end of a period or of the game, an
    overtime goal, a delayed penalty called, a penalty shot, the users back on the ice after one,
    the line change prompts and their countdowns, the CPU coaches' lines) and ai_puck_faceoff2
    (the wait for the referee, the panel and the players, skipped, after an injury, at the opening
    faceoff; the players placed at the dot by their line slots, the goalies shaded, a penalty shot
    started; the countdown and the drop); end_of_period (the next period, overtime, the end)'''
    names = list(PFACE_ROUTINES)
    weights = {'ai_puck_faceoff': 5, 'ai_puck_faceoff2': 6, 'end_of_period': 2}
    cup = {'v': 0}
    stubs = [emu.stub(GAME_OVER_CHECK, lambda eax: (calls.append(['game_over_check', s32(eax & 0xffffffff),
                                                                  s32(emu.uc.reg_read(UC_X86_REG_EDX))]), cup['v'])[1]),
             emu.stub(STOP_CROWD_LOOP, lambda eax: calls.append(['stop_crowd_loop'])),
             emu.stub(CENTER_MOUSE, lambda eax: calls.append(['center_mouse'])),
             emu.stub(GSUMMARY_FLUSH, lambda eax: calls.append(['gsummary_flush'])),
             emu.stub(PERIOD_CLEANUP, lambda eax: calls.append(['period_cleanup']))]
    order_names = [n for n in names for _ in range(weights[n])]
    cases = []
    for k in range(100 * len(order_names)):
        name = order_names[k % len(order_names)]
        g, teams, carrier = ai_world(emu, rnd, base, tables)
        g['speech_busy'] = 0
        speech['busy'] = 0
        cup['v'] = rnd.choice((0, 0, 1))
        g['user1_team'] = rnd.choice((0, 1, 1, 2))
        g['user2_team'] = rnd.choice((0, 0, 1, 2))
        for u in (1, 2):
            t_ = g['user%d_team' % u]
            g['user%d_slot' % u] = rnd.choice((-1, (t_ - 1) * 6 + rnd.randrange(6))) if t_ else -1
        g['penalty_box_mode'] = rnd.choice((0, 0, 1))
        g['penalty_shot_phase'] = rnd.choice((0, 0, 0, 1))
        g['penalty_shot_setup'] = rnd.choice((0, 0, 1))
        g['penalty_shot_slot'] = rnd.randrange(12)
        g['penalty_shot_team'] = 1 if g['penalty_shot_slot'] > 5 else 0
        g['clip'] = -1
        for ti, t in enumerate(TEAM_RECORDS):
            f = teams[ti]
            f['goals'] = rnd.randrange(4)
            f['skaters'] = rnd.choice((6, 6, 5, 4))
            f['goalie_request'] = rnd.choice((0, 0, 1, -256, -16))
            f['flags'] = rnd.choice((0, 0, 2, 0x10, 8))
            for n_, o, sz in AI_TEAM_FIELDS:
                emu.write(t + o, struct.pack('<' + _FMT[sz], f[n_] if sz < 0 else f[n_] & ((1 << (8 * sz)) - 1)))
        # players: line change requests, arrived at the faceoff (timer_b -100)
        arrived = rnd.random() < 0.6
        for slot in range(12):
            rec = bytearray(emu.read(ENTITIES + slot * 0x80, 0x80))
            if rnd.random() < 0.15:
                rec[0x45] |= 8
            if arrived or rnd.random() < 0.7:
                struct.pack_into('<h', rec, 0x2e, -100)
            emu.write(ENTITIES + slot * 0x80, rec)
        args = []
        regs = {}
        puck = bytearray(emu.read(PUCK, 0x80))
        if name == 'ai_puck_faceoff':
            g['game_flags'] = (g['game_flags'] & ~0x49) | rnd.choice((1, 1, 1, 1, 0x41, 9))
            g['period'] = rnd.choice((0, 1, 2, 3, 3))
            if rnd.random() < 0.15:
                g['clock_seconds'] = 0
                g['clock_sub'] = 0
            carrier = rnd.choice((-1, 16, rnd.randrange(12)))
            entered = rnd.random() < 0.7
            put_fields(puck, {'state_sp': 0, 'stack': 0x1b1b1b1b, 'stack2': 0x1b1b1b1b,
                              'flags': (puck[0x44] & ~2) | (2 if entered else 0),
                              'timer_a': rnd.choice((-1, -0x100, 0, 1, 3, 0x258)), 'target_x': rnd.randrange(12),
                              'target_y': rnd.randrange(12), 'want_dir': rnd.choice((0, 1, 3, 0x78)),
                              'dir_timer': rnd.choice((-1, -1, 0, 1))})
            regs = {'eax': PUCK}
        elif name == 'ai_puck_faceoff2':
            g['game_flags'] = (g['game_flags'] & ~0x49) | 1
            g['period'] = rnd.choice((0, 0, 1, 2, 3))
            if rnd.random() < 0.15:
                g['clock_seconds'] = g['period_length']
                g['clock_sub'] = 0
            g['demo'] = rnd.choice((0, 0, 0, 1))
            g['skip_wait'] = rnd.choice((0, 0, 0, 1))
            g['injury_stoppage'] = rnd.choice((0, 0, 0, 1))
            g['ref_phase'] = rnd.choice((-1, -1, -1, 0))
            g['panel'] = rnd.choice((-1, -1, -1, 0x20))
            g['clip'] = rnd.choice((-1, -1, 2))
            entered = rnd.random() < 0.6
            put_fields(puck, {'state_sp': 0, 'stack': 0x1c1c1c1c, 'stack2': 0x1c1c1c1c,
                              'flags': (puck[0x44] & ~2) | (2 if entered else 0),
                              'timer_a': rnd.choice((-1, 0, 1, 2, 0x11, 0x12, 0x16, rnd.randrange(300))),
                              'timer_b': rnd.choice((1, 2, 500))})
            regs = {'eax': PUCK}
        else:
            g['period'] = rnd.choice((0, 1, 2, 2, 3, 3))
            g['period_over'] = 1
            g['settings2'] = rnd.choice((0, 2))
        emu.write(PUCK, puck)
        emu.write(PUCK + 0x42, bytes([carrier & 0xff]))
        g['infraction0'] = 0
        write_globals(emu, g)
        emu.write(OPTION_FLAGS, struct.pack('<I', (g['option_flags'] & 0xff) | (g['settings2'] << 8)))
        emu.write(PERIOD_NUM, struct.pack('<h', g['period'] + 1))
        emu.write(PANEL_LINE4, b'\0' * 0x20)
        emu.write(INFRACTION_QUEUE, b'\0' * 64)
        seed = rnd.getrandbits(32)
        emu.write(SEED, struct.pack('<I', seed))
        scratch_ac = rnd.getrandbits(32)
        scratch = [rnd.getrandbits(16), rnd.getrandbits(16)]
        emu.write(SCRATCH[2], struct.pack('<I', scratch_ac))
        emu.write(SCRATCH[0], struct.pack('<H', scratch[0]))
        emu.write(SCRATCH[1], struct.pack('<H', scratch[1]))
        befores = {str(s_): dict(entity_fields(emu, s_), prev=list(struct.unpack('<iii', emu.read(ENTITIES + s_ * 0x80 + 0x74, 12))))
                   for s_ in range(17)}
        for ti, t in enumerate(TEAM_RECORDS):
            teams[ti].update({n_: struct.unpack('<' + _FMT[sz], emu.read(t + o, abs(sz)))[0] for n_, o, sz in AI_TEAM_FIELDS})
        order = draw_order(emu)
        case = {'routine': name, 'args': args, 'globals': g, 'teams': teams, 'carrier': carrier, 'seed': seed,
                'scratch_ac': scratch_ac, 'scratch': scratch, 'infq': [0] * 64, 'cup': cup['v'], 'order': order}
        if name == 'ai_puck_faceoff2':
            # the ratings of the players (faceoff_resolve: the centres' faceoff rating, byte 0x13)
            ratings = [[[rnd.randrange(10) for _ in range(20)] for _ in range(25)] for _ in range(2)]
            for ti in range(2):
                emu.write(PLAYER_RATINGS + ti * 0x1f4, bytes(sum(ratings[ti], [])))
            case['faceoff_ratings'] = [[ratings[ti][r][0x13] for r in range(25)] for ti in range(2)]
        del calls[:]
        emu.call(PFACE_ROUTINES[name], **regs)
        after = ai_record(emu)
        la = {'infq': list(emu.read(INFRACTION_QUEUE, 64)),
              'panel4': emu.read(PANEL_LINE4, 0x20).split(b'\0')[0].decode('latin-1'),
              'scratch': list(struct.unpack('<hh', emu.read(SCRATCH[0], 2) + emu.read(SCRATCH[1], 2))),
              'scratch_ac': struct.unpack('<I', emu.read(SCRATCH[2], 4))[0]}
        case.update({'before': befores, 'calls': [list(c) for c in calls],
                     'after': {str(s_): {k_: v for k_, v in entity_fields(emu, s_).items() if befores[str(s_)].get(k_) != v}
                               for s_ in range(17)},
                     'world_after': after, 'lines_after': la})
        cases.append(case)
        for a, n_ in ((GAME_FLAGS, 1), (OPTION_FLAGS, 4), (STOP_FLAGS, 2), (MISC_FLAGS, 4), (BREAKAWAY_FLAG, 4),
                      (PENALTY_SHOT_ACTIVE, 4), (PENALTY_SHOT_SETUP, 4), (PENALTY_SHOT_PHASE, 4)):
            emu.write(a, b'\0' * n_)
        emu.write(INFRACTION_QUEUE, b'\0' * 64)
        for t_ in TEAM_RECORDS:
            emu.write(t_ + 0x44, b'\0')
    for h in stubs:
        emu.uc.hook_del(h)
    for c in cases:
        c['before'] = {s_: {k_: v for k_, v in b.items() if base_fields[int(s_)].get(k_) != v} for s_, b in c['before'].items()}
        c['after'] = {s_: a for s_, a in c['after'].items() if a}
    return cases


SIM_TICK = 0x5c1c4                             # sim_game_state, sim_update_players, update_camera, the replay
GAME_CLOCK_TICK = 0x5dc10
REPLAY_RECORD = 0x675d6                        # the replay frame
CONTROL_ENTRY = 0xc4e18                        # the key event the controls are read from (p1, p2 bytes)


def steps_cases(emu, rnd, base, tables, calls, base_fields, speech, count=1000, lengths=(1, 1, 1, 2, 4, 10)):
    '''whole steps of the simulation as run_sim_steps runs them (the clock while play is on, then
    sim_tick: sim_game_state, sim_update_players with the users' controls, update_camera), one or
    a run of them, from random moments of play, of stoppages and of faceoffs'''
    cup = {'v': 0}
    stubs = [emu.stub(GAME_OVER_CHECK, lambda eax: (calls.append(['game_over_check', s32(eax & 0xffffffff),
                                                                  s32(emu.uc.reg_read(UC_X86_REG_EDX))]), cup['v'])[1]),
             emu.stub(DRAW_SCORE_DIGITS, lambda eax: calls.append(['draw_score_digits', s32(eax & 0xffffffff),
                                                                   s32(emu.uc.reg_read(UC_X86_REG_EDX))])),
             emu.stub(STOP_CROWD_LOOP, lambda eax: calls.append(['stop_crowd_loop'])),
             emu.stub(CENTER_MOUSE, lambda eax: calls.append(['center_mouse'])),
             emu.stub(GSUMMARY_FLUSH, lambda eax: calls.append(['gsummary_flush']))]
    event = emu.alloc(b'\0' * 4)
    emu.write(CONTROL_ENTRY, struct.pack('<I', event))
    cases = []
    for k in range(count):
        g, teams, carrier = ai_world(emu, rnd, base, tables)
        g['speech_busy'] = 0
        speech['busy'] = 0
        cup['v'] = 0
        g['clip'] = -1
        g['panel'] = rnd.choice((-1, -1, -1, 0x100))
        g['user1_team'] = rnd.choice((0, 1, 1, 2))
        g['user2_team'] = rnd.choice((0, 0, 1, 2))
        for u in (1, 2):
            t_ = g['user%d_team' % u]
            g['user%d_slot' % u] = rnd.choice((-1, (t_ - 1) * 6 + rnd.randrange(1, 6))) if t_ else -1
        # the players dressed: those on the ice (a consistent count, nobody in the box yet)
        for ti, t in enumerate(TEAM_RECORDS):
            sk = sum(1 for s_ in range(ti * 6, ti * 6 + 6)
                     if struct.unpack('<h', emu.read(ENTITIES + s_ * 0x80 + 0x1a, 2))[0] >= 0)
            emu.write(t + 0x36, struct.pack('<h', sk))
            teams[ti]['skaters'] = sk
        # the candidate lists of injury_check
        for ti in range(2):
            for kk in range(11):
                emu.write(POS_LISTS + kk * 0x32 + ti * 0x19, b'\xff' * 25)
            emu.write(POS_LISTS + 4 * 0x32 + ti * 0x19, struct.pack('<25b', *([ti + 2 * i for i in range(4)] + [-1] * 21)))
            emu.write(POS_LISTS + 7 * 0x32 + ti * 0x19, struct.pack('<25b', *([ti + 2 * i for i in range(10)] + [-1] * 15)))
        # the crowd: everybody idle
        for i in range(20):
            emu.write(CROWD_FIGURES + i * 12, struct.pack('<hbbbhhhb', -1, rnd.choice((5, 30, 60)), 0, 0, 0, 0, 0, 0))
        emu.write(CROWD_BUSY, b'\0' * 22)
        g['infraction0'] = 0
        if g['last_touch_slot'] < 0 and not g['game_flags'] & 1:
            g['last_touch_slot'] = 2           # (in play somebody touched the puck: a goal credits him)
        rp = replay_setup(emu, rnd, g)
        # the players' faceoff ratings (faceoff_resolve: byte 0x13 of `player_ratings`, the rest 0)
        faceoff_ratings = [[rnd.randrange(10) for _ in range(25)] for _ in range(2)]
        for ti in range(2):
            emu.write(PLAYER_RATINGS + ti * 0x1f4, bytes(sum(([0] * 0x13 + [f] for f in faceoff_ratings[ti]), [])))
        write_globals(emu, g)
        emu.write(OPTION_FLAGS, struct.pack('<I', (g['option_flags'] & 0xff) | (g['settings2'] << 8)))
        emu.write(PERIOD_NUM, struct.pack('<h', g['period'] + 1))
        emu.write(PANEL_LINE4, b'\0' * 0x20)
        emu.write(INFRACTION_QUEUE, b'\0' * 64)
        seed = rnd.getrandbits(32)
        emu.write(SEED, struct.pack('<I', seed))
        scratch_ac = rnd.getrandbits(32)
        scratch = [rnd.getrandbits(16), rnd.getrandbits(16)]
        emu.write(SCRATCH[2], struct.pack('<I', scratch_ac))
        emu.write(SCRATCH[0], struct.pack('<H', scratch[0]))
        emu.write(SCRATCH[1], struct.pack('<H', scratch[1]))
        befores = {str(s_): dict(entity_fields(emu, s_), prev=list(struct.unpack('<iii', emu.read(ENTITIES + s_ * 0x80 + 0x74, 12))))
                   for s_ in range(17)}
        for ti, t in enumerate(TEAM_RECORDS):
            teams[ti].update({n_: struct.unpack('<' + _FMT[sz], emu.read(t + o, abs(sz)))[0] for n_, o, sz in AI_TEAM_FIELDS})
        order = draw_order(emu)
        n = rnd.choice(lengths)
        controls = []
        for _ in range(n):
            controls.append([rnd.choice((8, 8, 8, rnd.randrange(8), rnd.randrange(8) | rnd.choice((0x10, 0x20, 0x40)))),
                             rnd.choice((8, 8, rnd.randrange(8)))])
        case = {'routine': 'sim_steps', 'args': [], 'controls': controls, 'globals': g, 'teams': teams, 'carrier': carrier,
                'seed': seed, 'scratch_ac': scratch_ac, 'scratch': scratch, 'infq': [0] * 64, 'cup': 0, 'order': order,
                'stats': stats_read(emu, tables), 'crowd': crowd_read(emu), 'replay': rp, 'faceoff_ratings': faceoff_ratings,
                'pos_lists': [[list(struct.unpack('<25b', emu.read(POS_LISTS + kk * 0x32 + ti * 0x19, 25))) for kk in range(11)]
                              for ti in range(2)]}
        del calls[:]
        for c1, c2 in controls:
            emu.write(event, bytes([c1, c2, 0, 0]))
            if not emu.read(GAME_FLAGS, 1)[0] & 1:
                emu.call(GAME_CLOCK_TICK)
            emu.call(SIM_TICK)
        after = ai_record(emu)
        la = {'infq': list(emu.read(INFRACTION_QUEUE, 64)),
              'panel4': emu.read(PANEL_LINE4, 0x20).split(b'\0')[0].decode('latin-1'),
              'scratch': list(struct.unpack('<hh', emu.read(SCRATCH[0], 2) + emu.read(SCRATCH[1], 2))),
              'scratch_ac': struct.unpack('<I', emu.read(SCRATCH[2], 4))[0],
              'stats': stats_read(emu, tables), 'crowd': crowd_read(emu), 'replay': replay_read(emu)}
        case.update({'before': befores, 'calls': [list(c) for c in calls],
                     'after': {str(s_): {k_: v for k_, v in entity_fields(emu, s_).items() if befores[str(s_)].get(k_) != v}
                               for s_ in range(17)},
                     'world_after': after, 'lines_after': la})
        cases.append(case)
        for a, n_ in ((GAME_FLAGS, 1), (OPTION_FLAGS, 4), (STOP_FLAGS, 2), (MISC_FLAGS, 4), (BREAKAWAY_FLAG, 4),
                      (PENALTY_SHOT_ACTIVE, 4), (PENALTY_SHOT_SETUP, 4), (PENALTY_SHOT_PHASE, 4)):
            emu.write(a, b'\0' * n_)
        emu.write(INFRACTION_QUEUE, b'\0' * 64)
        for t_ in TEAM_RECORDS:
            emu.write(t_ + 0x44, b'\0')
    emu.write(CONTROL_ENTRY, b'\0' * 4)
    for h in stubs:
        emu.uc.hook_del(h)
    for c in cases:
        c['before'] = {s_: {k_: v for k_, v in b.items() if base_fields[int(s_)].get(k_) != v} for s_, b in c['before'].items()}
        c['after'] = {s_: a for s_, a in c['after'].items() if a}
    return cases


PERIOD_ROUTINES = {'period_cleanup': 0x5de70, 'end_of_period': 0x5dea6, 'reset_game_state': 0x14056, 'init_match': 0x47cd6,
                   'setup_demo_faceoff': 0x13c79, 'three_stars_sequence': 0x48f0b}
LEAVE_MATCH_VIDEO = 0x10f6d                    # stubbed: the intermission screens; period_over -1, the period count on
FLUSH_KEY_EVENTS = 0x4fd47
SELECT_GAME_SURFACE = 0x8c1c2
DRAW_CLOCK = 0x14cf1
GETPALETTE = 0x8ffb0                           # (cdecl)
FADE_PALETTE_TO = 0x11598
SEQUENCE_LOOP = 0x48333                        # stubbed: the anthem / three stars loop (run by the port's step)
FADE_AMBIENT_AUDIO = 0x597e3
SOUND_STOPALL = 0x8f633
SETMOUSEPOS = 0xb2db4                          # (cdecl)
TEAM_IDS = 0xc90ca                             # home_team_id, away_team_id
PLAYER_STATS = (0xdb088, 0xdb218)              # word_db088: 25 x 8 words per team (team +0xe6)
GOALIE_STATS = (0xdc240, 0xdc252)              # word_dc240: 3 x [time, shots against, goals against] (team +0xea)


def periods_cases(emu, rnd, base, tables, calls, base_fields, speech):
    """the start of the match and of its periods: period_cleanup (the next period: everybody to the
    bench and rested, the entities from entity_init, the clock, the users' skaters, two steps of the
    simulation, the penalized players' places kept; the end of the game), end_of_period with it,
    reset_game_state (the whole match reset: the globals, the team records, the first period),
    init_match (the anthem), setup_demo_faceoff (the lines at the opening faceoff) and
    three_stars_sequence (after the game), from random moments of play"""
    names = list(PERIOD_ROUTINES)
    weights = {'period_cleanup': 4, 'end_of_period': 2, 'reset_game_state': 2, 'init_match': 2, 'setup_demo_faceoff': 2,
               'three_stars_sequence': 2}
    cup = {'v': 0}

    def on_leave(eax):
        calls.append(['leave_match_video'])
        emu.write(0xcbc46, struct.pack('<h', -1))
        n = struct.unpack('<i', emu.read(PERIOD_NUM, 4))[0]
        emu.write(PERIOD_NUM, struct.pack('<i', n + 1))
    stubs = [emu.stub(GAME_OVER_CHECK, lambda eax: (calls.append(['game_over_check', s32(eax & 0xffffffff),
                                                                  s32(emu.uc.reg_read(UC_X86_REG_EDX))]), cup['v'])[1]),
             emu.stub(DRAW_SCORE_DIGITS, lambda eax: calls.append(['draw_score_digits', s32(eax & 0xffffffff),
                                                                   s32(emu.uc.reg_read(UC_X86_REG_EDX))])),
             emu.stub(STOP_CROWD_LOOP, lambda eax: calls.append(['stop_crowd_loop'])),
             emu.stub(CENTER_MOUSE, lambda eax: calls.append(['center_mouse'])),
             emu.stub(GSUMMARY_FLUSH, lambda eax: calls.append(['gsummary_flush'])),
             emu.stub(LEAVE_MATCH_VIDEO, on_leave),
             emu.stub(FLUSH_KEY_EVENTS, lambda eax: None),
             emu.stub(SELECT_GAME_SURFACE, lambda eax: None),
             emu.stub(DRAW_CLOCK, lambda eax: None),
             emu.stub(GETPALETTE, lambda eax: None),
             emu.stub(FADE_PALETTE_TO, lambda eax: None),
             emu.stub(SEQUENCE_LOOP, lambda eax: 0),
             emu.stub(FADE_AMBIENT_AUDIO, lambda eax: None),
             emu.stub(SOUND_STOPALL, lambda eax: None),
             emu.stub(SETMOUSEPOS, lambda eax: None)]
    event = emu.alloc(b'\x08\x08\0\0')
    emu.write(CONTROL_ENTRY, struct.pack('<I', event))
    # the team records' pointers (team_state_clear sets the game's own) are put back after each case
    pointers = [emu.read(t + 0xda, 0x20) for t in TEAM_RECORDS]
    order_names = [n for n in names for _ in range(weights[n])]
    cases = []
    for k in range(50 * len(order_names)):
        name = order_names[k % len(order_names)]
        g, teams, carrier = ai_world(emu, rnd, base, tables)
        g['speech_busy'] = 0
        speech['busy'] = 0
        cup['v'] = rnd.choice((0, 0, 1))
        g['clip'] = rnd.choice((-1, -1, 2))
        g['panel'] = rnd.choice((-1, -1, 0x100, 0x20))
        g['settings2'] = rnd.choice((0, 2, 4, 6, 8, 0xa))
        g['option_flags'] = rnd.choice((0x1f, 0x9f, 0x1b, 0x8e))
        g['user1_team'] = rnd.choice((0, 1, 1, 2))
        g['user2_team'] = rnd.choice((0, 0, 1, 2))
        for u in (1, 2):
            t_ = g['user%d_team' % u]
            g['user%d_slot' % u] = rnd.choice((-1, (t_ - 1) * 6 + rnd.randrange(1, 6))) if t_ else -1
        g['controller0'] = 8
        g['controller1'] = 8
        g['demo'] = rnd.choice((0, 0, 0, 1)) if name in ('setup_demo_faceoff', 'three_stars_sequence') else 0
        period_num = g['period'] + 1
        if name == 'period_cleanup':
            g['period'] = rnd.choice((0, 1, 1, 2, 2, 3, 3, 4))
            g['period_over'] = rnd.choice((1, -1))
            period_num = g['period'] if g['period'] else rnd.choice((-1, 1, 3))
        elif name == 'end_of_period':
            g['period'] = rnd.choice((0, 1, 2, 2, 3, 3))
            g['period_over'] = rnd.choice((1, 1, 1, -1))
            period_num = g['period'] + 1
        elif name == 'reset_game_state':
            g['period'] = rnd.choice((-1, 0))
            period_num = rnd.choice((-1, 1, 3))
        elif name == 'init_match':
            period_num = 1
        elif name == 'three_stars_sequence':
            g['period'] = 4
            g['match_over'] = 1
        for ti, t in enumerate(TEAM_RECORDS):
            f = teams[ti]
            f['goals'] = rnd.randrange(5)
            f['goalie_request'] = rnd.choice((0, 0, 1, -256, -16))
            for n_, o, sz in AI_TEAM_FIELDS:
                emu.write(t + o, struct.pack('<' + _FMT[sz], f[n_] if sz < 0 else f[n_] & ((1 << (8 * sz)) - 1)))
        if name == 'init_match':
            # (as reset_game_state left the teams: nobody in the box, the goalies dressed; the
            # anthem's line up has five places for the skaters)
            for ti, t in enumerate(TEAM_RECORDS):
                teams[ti]['goalie_request'] = 0
                emu.write(t + 0x38, b'\0\0')
        else:
            random_boxes(emu, rnd, teams)
        # the status bytes of the players (empty places, injured, scratched) and some hurt for the period
        for ti, t in enumerate(TEAM_RECORDS):
            ent = teams[ti]['entity_of']
            status = teams[ti]['roster_status']
            for r in range(28 if name != 'init_match' else 25):
                if status[r] == 3 and rnd.random() < 0.08:
                    status[r] = rnd.choice((0, 1, 2, 7))
                if ent[r] == -2 and rnd.random() < 0.06:
                    ent[r] = -3
                emu.write(ROSTERS + ti * 0x444 + r * 0x27, bytes([status[r]]))
            emu.write(t + 0x7e, struct.pack('<28h', *ent))
            energies = [rnd.choice((0x1000, rnd.randrange(0x400, 0x1001))) for _ in range(28)]
            emu.write(t + 0x46, struct.pack('<28h', *energies))
            teams[ti]['energies'] = energies
        if name == 'three_stars_sequence':
            # the statistics (compute_three_stars reads the game's own tables, the team records point
            # the generator's copies)
            for t, (ps, gs) in enumerate(tables):
                raw = bytearray(25 * 0x10)
                for r in range(25):
                    struct.pack_into('<8h', raw, r * 0x10, rnd.randrange(5), rnd.randrange(5), rnd.randrange(10), rnd.randrange(-5, 6),
                                     rnd.randrange(3), rnd.randrange(2), rnd.randrange(2), rnd.randrange(10))
                gsr = struct.pack('<9h', *sum(([rnd.choice((0, rnd.randrange(3600))), rnd.randrange(60), rnd.randrange(8)]
                                               for _ in range(3)), []))
                emu.write(ps, bytes(raw))
                emu.write(gs, gsr)
                emu.write(PLAYER_STATS[t], bytes(raw[:25 * 0x10]))
                emu.write(GOALIE_STATS[t], gsr)
            # the ratings (compare_player_stats: the sum of ten of them breaks a tie)
            ratings = [[[rnd.randrange(1, 4) for _ in range(0x14)] for _ in range(25)] for _ in range(2)]
            for ti in range(2):
                emu.write(PLAYER_RATINGS + ti * 0x1f4, bytes(sum(ratings[ti], [])))
        # the crowd: everybody idle
        for i in range(20):
            emu.write(CROWD_FIGURES + i * 12, struct.pack('<hbbbhhhb', -1, rnd.choice((5, 30, 60)), 0, 0, 0, 0, 0, 0))
        emu.write(CROWD_BUSY, b'\0' * 22)
        team_ids = [rnd.randrange(26), rnd.randrange(26)]
        g['team_ids'] = team_ids
        g['infraction0'] = 0
        rp = replay_setup(emu, rnd, g)
        write_globals(emu, g)
        emu.write(OPTION_FLAGS, struct.pack('<I', (g['option_flags'] & 0xff) | (g['settings2'] << 8)))
        emu.write(PERIOD_NUM, struct.pack('<i', period_num))
        emu.write(PANEL_LINE4, b'\0' * 0x20)
        emu.write(INFRACTION_QUEUE, b'\0' * 64)
        emu.write(event, b'\x08\x08\0\0')
        seed = rnd.getrandbits(32)
        emu.write(SEED, struct.pack('<I', seed))
        scratch_ac = rnd.getrandbits(32)
        scratch = [rnd.getrandbits(16), rnd.getrandbits(16)]
        emu.write(SCRATCH[2], struct.pack('<I', scratch_ac))
        emu.write(SCRATCH[0], struct.pack('<H', scratch[0]))
        emu.write(SCRATCH[1], struct.pack('<H', scratch[1]))
        befores = {str(s_): dict(entity_fields(emu, s_), prev=list(struct.unpack('<iii', emu.read(ENTITIES + s_ * 0x80 + 0x74, 12))))
                   for s_ in range(17)}
        for ti, t in enumerate(TEAM_RECORDS):
            teams[ti].update({n_: struct.unpack('<' + _FMT[sz], emu.read(t + o, abs(sz)))[0] for n_, o, sz in AI_TEAM_FIELDS})
        order = draw_order(emu)
        case = {'routine': name, 'args': [], 'globals': g, 'teams': teams, 'carrier': carrier, 'seed': seed,
                'scratch_ac': scratch_ac, 'scratch': scratch, 'infq': [0] * 64, 'cup': cup['v'], 'order': order,
                'period_num': period_num, 'team_ids': team_ids, 'crowd': crowd_read(emu), 'replay': rp,
                'pos_lists': [[list(struct.unpack('<25b', emu.read(POS_LISTS + kk * 0x32 + ti * 0x19, 25))) for kk in range(11)]
                              for ti in range(2)]}
        if name == 'three_stars_sequence':
            case['stats'] = stats_read(emu, tables)
            case['ratings'] = ratings
        del calls[:]
        emu.call(PERIOD_ROUTINES[name])
        after = ai_record(emu)
        la = {'infq': list(emu.read(INFRACTION_QUEUE, 64)),
              'panel4': emu.read(PANEL_LINE4, 0x20).split(b'\0')[0].decode('latin-1'),
              'scratch': list(struct.unpack('<hh', emu.read(SCRATCH[0], 2) + emu.read(SCRATCH[1], 2))),
              'scratch_ac': struct.unpack('<I', emu.read(SCRATCH[2], 4))[0], 'crowd': crowd_read(emu),
              'period_num': struct.unpack('<i', emu.read(PERIOD_NUM, 4))[0],
              'energies': [list(struct.unpack('<28h', emu.read(t + 0x46, 56))) for t in TEAM_RECORDS],
              'order': draw_order(emu), 'replay': replay_read(emu)}
        case.update({'before': befores, 'calls': [list(c) for c in calls],
                     'after': {str(s_): {k_: v for k_, v in entity_fields(emu, s_).items() if befores[str(s_)].get(k_) != v}
                               for s_ in range(17)},
                     'world_after': after, 'lines_after': la})
        for s_ in range(17):
            prev = list(struct.unpack('<iii', emu.read(ENTITIES + s_ * 0x80 + 0x74, 12)))
            if prev != befores[str(s_)]['prev']:
                case['after'].setdefault(str(s_), {})['prev'] = prev
        cases.append(case)
        for a, n_ in ((GAME_FLAGS, 1), (OPTION_FLAGS, 4), (STOP_FLAGS, 2), (MISC_FLAGS, 4), (BREAKAWAY_FLAG, 4),
                      (PENALTY_SHOT_ACTIVE, 4), (PENALTY_SHOT_SETUP, 4), (PENALTY_SHOT_PHASE, 4)):
            emu.write(a, b'\0' * n_)
        emu.write(INFRACTION_QUEUE, b'\0' * 64)
        for t_, ptr in zip(TEAM_RECORDS, pointers):
            emu.write(t_ + 0x44, b'\0')
            emu.write(t_ + 0xda, ptr)
    emu.write(CONTROL_ENTRY, b'\0' * 4)
    for h in stubs:
        emu.uc.hook_del(h)
    for c in cases:
        c['before'] = {s_: {k_: v for k_, v in b.items() if base_fields[int(s_)].get(k_) != v} for s_, b in c['before'].items()}
        c['after'] = {s_: a for s_, a in c['after'].items() if a}
    return cases


GOALIE_RATINGS = (0xdac40, 0xdac70)            # team +0xe2: 3 x 0x10 rating bytes of the goalies
DRESS_ROUTINES = {'put_player_on_ice': 0x5b2c5}


def dress_cases(emu, rnd, base, tables, calls, base_fields):
    """put_player_on_ice called directly: a roster player (skater or goalie, from the bench, the
    box, the ice or out) onto an entity of either team, his number and ratings from random player
    records, adjusted by random team factors (short handed, power play, home, away) and late in
    the game for a tied or trailing team"""
    names = list(DRESS_ROUTINES)
    team_recs = [struct.unpack('<I', emu.read(t + 0xf2, 4))[0] for t in TEAM_RECORDS]
    cases = []
    for k in range(400):
        name = names[k % len(names)]
        g, teams, carrier = ai_world(emu, rnd, base, tables)
        g['period'] = rnd.choice((0, 1, 2, 2, 2, 3))
        g['clock_seconds'] = rnd.randrange(1, 300)
        g['period_length'] = rnd.choice((300, 600, 1200))
        g['stop_flags'] = rnd.choice((0, 0, 0x20, 0x60))
        dress = {'numbers': [], 'ratings': [], 'goalie_ratings': [], 'factors': []}
        for ti, t in enumerate(TEAM_RECORDS):
            f = teams[ti]
            f['goals'] = rnd.randrange(4)
            emu.write(t + 0x10, struct.pack('<h', f['goals']))
            emu.write(t + 0xe2, struct.pack('<I', GOALIE_RATINGS[ti]))
            numbers = [rnd.randrange(1, 100) for _ in range(28)]
            for i in range(28):
                emu.write(ROSTERS + ti * 0x444 + i * 0x27 + 5, bytes([numbers[i]]))
            ratings = [[rnd.randrange(0, 16) for _ in range(0x14)] for _ in range(25)]
            for i in range(25):
                ratings[i][0] = rnd.choice((0, 1))
            emu.write(PLAYER_RATINGS + ti * 0x1f4, bytes(sum(ratings, [])))
            gr = [[rnd.randrange(0, 16) for _ in range(0x10)] for _ in range(3)]
            for i in range(3):
                gr[i][0] = rnd.choice((0, 1))
            emu.write(GOALIE_RATINGS[ti], bytes(sum(gr, [])))
            factors = [rnd.randrange(0, 10) for _ in range(4)]
            emu.write(team_recs[ti] + 0x2dc, bytes(factors))
            ent = list(f['entity_of'])
            for i in range(28):
                if rnd.random() < 0.2:
                    ent[i] = rnd.choice((-3, -4, 1, 0x2005, 0, -1))
            emu.write(t + 0x7e, struct.pack('<28h', *ent))
            f['entity_of'] = ent
            dress['numbers'].append(numbers)
            dress['ratings'].append(ratings)
            dress['goalie_ratings'].append(gr)
            dress['factors'].append(factors)
        write_globals(emu, g)
        emu.write(OPTION_FLAGS, struct.pack('<I', (g['option_flags'] & 0xff) | (g['settings2'] << 8)))
        emu.write(PERIOD_NUM, struct.pack('<h', g['period'] + 1))
        slot = rnd.randrange(12)
        rec = bytearray(emu.read(ENTITIES + slot * 0x80, 0x80))
        put_fields(rec, {'line_slot': rnd.choice((0, 1, 2, 3, 4, 5, -1)), 'w48': rnd.choice((-1, 0x1234, 3))})
        emu.write(ENTITIES + slot * 0x80, rec)
        roster = rnd.choice((rnd.randrange(25), rnd.randrange(25), rnd.randrange(25, 28)))
        seed = rnd.getrandbits(32)
        emu.write(SEED, struct.pack('<I', seed))
        scratch_ac = rnd.getrandbits(32)
        scratch = [rnd.getrandbits(16), rnd.getrandbits(16)]
        emu.write(SCRATCH[2], struct.pack('<I', scratch_ac))
        emu.write(SCRATCH[0], struct.pack('<H', scratch[0]))
        emu.write(SCRATCH[1], struct.pack('<H', scratch[1]))
        for ti in range(2):
            teams[ti]['roster_status'] = [emu.read(ROSTERS + ti * 0x444 + i * 0x27, 1)[0] for i in range(28)]
        befores = {str(s_): dict(entity_fields(emu, s_), prev=list(struct.unpack('<iii', emu.read(ENTITIES + s_ * 0x80 + 0x74, 12))))
                   for s_ in range(17)}
        for ti, t in enumerate(TEAM_RECORDS):
            teams[ti].update({n_: struct.unpack('<' + _FMT[sz], emu.read(t + o, abs(sz)))[0] for n_, o, sz in AI_TEAM_FIELDS})
        order = draw_order(emu)
        args = [slot, roster]
        del calls[:]
        emu.call(DRESS_ROUTINES[name], eax=ENTITIES + slot * 0x80, edx=roster)
        after = ai_record(emu)
        cases.append({'routine': name, 'args': args, 'globals': g, 'teams': teams, 'carrier': carrier, 'seed': seed,
                      'scratch_ac': scratch_ac, 'scratch': scratch, 'dress': dress,
                      'before': befores, 'order': order, 'calls': [list(c) for c in calls],
                      'after': {str(s_): {k_: v for k_, v in entity_fields(emu, s_).items() if befores[str(s_)].get(k_) != v}
                                for s_ in range(17)},
                      'world_after': after,
                      'lines_after': {'scratch': list(struct.unpack('<hh', emu.read(SCRATCH[0], 2) + emu.read(SCRATCH[1], 2)))}})
        for a, n_ in ((GAME_FLAGS, 1), (OPTION_FLAGS, 4), (STOP_FLAGS, 2), (MISC_FLAGS, 4), (BREAKAWAY_FLAG, 4),
                      (PENALTY_SHOT_ACTIVE, 4), (PENALTY_SHOT_SETUP, 4), (PENALTY_SHOT_PHASE, 4)):
            emu.write(a, b'\0' * n_)
    for c in cases:
        c['before'] = {s_: {k_: v for k_, v in b.items() if base_fields[int(s_)].get(k_) != v} for s_, b in c['before'].items()}
        c['after'] = {s_: a for s_, a in c['after'].items() if a}
    return cases


LINEUP_ROUTINES = {'pick_player_for_position': 0x655cc, 'count_dressed_players': 0x658f3, 'choose_lineup_player': 0x64e60,
                   'lineup_player_ok': 0x64a0b, 'lineup_set_goalies': 0x652d6, 'lineup_set_backup': 0x653be,
                   'injure_player': 0x55e72}
ANNOUNCE_INJURY = 0x62764                      # (team, roster, game, minutes) + seconds, 0, 0
LINEUP_COUNTS = 0xe9f12                        # word_e9f12 forwards, e9f14 defencemen, e9f16 both
LINEUP_IN_TABLE = 0xe9c24                      # 25 dwords: in the line table (count_dressed_players)


def lineup_cases(emu, rnd, base, tables, calls, base_fields, teams_path):
    """the lineup routines called directly on random teams (line tables of TEAMS.DB, rosters with
    positions, ratings and statuses: empty, injured, scratched, called up), the candidate lists of
    build_lines, substitutes in the lineup flags, the counts of the dressed players"""
    with open(teams_path, 'rb') as f:
        teams_db = f.read()
    nteams = len(teams_db) // 0x2e8
    names = list(LINEUP_ROUTINES)
    weights = {'pick_player_for_position': 4, 'count_dressed_players': 2, 'choose_lineup_player': 2, 'lineup_player_ok': 2,
               'lineup_set_goalies': 1, 'lineup_set_backup': 1, 'injure_player': 2}
    order_names = [n for n in names for _ in range(weights[n])]

    stubs = []
    cases = []
    for k in range(50 * len(order_names)):
        name = order_names[k % len(order_names)]
        g, teams, carrier = ai_world(emu, rnd, base, tables)
        lines_in = {'positions': [], 'ratings': [], 'line_tables': []}
        for ti, t in enumerate(TEAM_RECORDS):
            n = rnd.randrange(nteams)
            lt = bytearray(teams_db[n * 0x2e8 + 0xbc:n * 0x2e8 + 0xec])
            for _ in range(rnd.choice((0, 0, 0, 1, 3))):
                lt[rnd.randrange(0x26)] = rnd.randrange(25)
            lt += bytes([0x64]) * 0x10
            # the scratches at +0x28..+0x2f
            for c in range(0x28, 0x30):
                if rnd.random() < 0.3:
                    lt[c] = rnd.randrange(28)
            emu.write(LINE_TABLES[ti], bytes(lt[:0x30]))   # (font_current_default follows the home team's)
            lines_in['line_tables'].append(list(lt))
            pos = [rnd.choice('CCLLRRDDD') for _ in range(25)] + ['G'] * 3
            ratings = [[rnd.randrange(1, 7) for _ in range(0x14)] for _ in range(25)]
            status = [rnd.choice((3, 3, 3, 3, 3, 3, 0, 1, 2, 2, 7)) for _ in range(25)] + \
                     [rnd.choice((3, 3, 0, 1, 2)) for _ in range(3)]
            for i in range(28):
                emu.write(ROSTERS + ti * 0x444 + i * 0x27, bytes([status[i]]))
                emu.write(ROSTERS + ti * 0x444 + i * 0x27 + 6, pos[i].encode())
            for i in range(25):
                emu.write(PLAYER_RATINGS + ti * 0x1f4 + i * 0x14, bytes(ratings[i]))
            lines_in['positions'].append(''.join(pos))
            lines_in['ratings'].append(ratings)
            teams[ti]['roster_status'] = status
        write_globals(emu, g)
        emu.write(OPTION_FLAGS, struct.pack('<I', (g['option_flags'] & 0xff) | (g['settings2'] << 8)))
        emu.write(PERIOD_NUM, struct.pack('<h', g['period'] + 1))
        emu.call(LINE_ROUTINES['build_lines'])
        # substitutes (flag 2) among the lineup flags, the counts
        for ti in range(2):
            for i in range(25):
                if rnd.random() < 0.15:
                    emu.write(POS_LISTS + 6 * 0x32 + ti * 0x19 + i, bytes([rnd.choice((0, 1, 2))]))
        counts = [rnd.randrange(4, 15), rnd.randrange(2, 9)]
        counts.append(counts[0] + counts[1] + rnd.choice((0, 0, 3)))
        emu.write(LINEUP_COUNTS, struct.pack('<3h', *counts))
        emu.write(LINEUP_IN_TABLE, b'\0' * 100)
        seed = rnd.getrandbits(32)
        emu.write(SEED, struct.pack('<I', seed))
        scratch_ac = rnd.getrandbits(32)
        scratch = [rnd.getrandbits(16), rnd.getrandbits(16)]
        emu.write(SCRATCH[2], struct.pack('<I', scratch_ac))
        emu.write(SCRATCH[0], struct.pack('<H', scratch[0]))
        emu.write(SCRATCH[1], struct.pack('<H', scratch[1]))
        lines_in.update(lines_read(emu))
        lines_in['counts'] = counts
        for ti in range(2):
            teams[ti]['roster_status'] = [emu.read(ROSTERS + ti * 0x444 + i * 0x27, 1)[0] for i in range(28)]
        befores = {str(s_): dict(entity_fields(emu, s_), prev=list(struct.unpack('<iii', emu.read(ENTITIES + s_ * 0x80 + 0x74, 12))))
                   for s_ in range(17)}
        t = rnd.randrange(2)
        regs = {'eax': t}
        args = [t]
        if name == 'pick_player_for_position':
            lt = lines_in['line_tables'][t]
            r = rnd.choice([lt[rnd.randrange(0x28)] for _ in range(3)] + [rnd.randrange(28)])
            r = r if r < 28 else rnd.randrange(28)
            args = [t, r]
            regs['edx'] = r
        elif name in ('choose_lineup_player',):
            args = [t, rnd.randrange(0x24)]
            regs['edx'] = args[1]
        elif name == 'lineup_player_ok':
            args = [t, rnd.randrange(0x24), rnd.randrange(25)]
            regs.update({'edx': args[1], 'ebx': args[2]})
        elif name == 'lineup_set_goalies':
            args = [t, rnd.choice((0x24, 0x25)), rnd.choice((0, 1))]
            regs.update({'edx': args[1], 'ebx': args[2]})
        elif name == 'lineup_set_backup':
            args = [t, rnd.choice((0x26, 0x27))]
            regs['edx'] = args[1]
        elif name == 'injure_player':
            slot = t * 6 + rnd.randrange(1, 6)
            args = [slot]
            regs = {'eax': ENTITIES + slot * 0x80}
            emu.write(LAST_IMPACT, struct.pack('<h', rnd.choice((0x10, 0x2d, 0x2e, 0x40))))
            emu.write(CROWD_NOISE + 2, struct.pack('<h', rnd.choice((0, 600, 900, 1000, 1200))))
            emu.write(CAMERA_XY, struct.pack('<h', rnd.randrange(-0x60, 0x61)))
            g['period_length'] = rnd.choice((300, 600))
            g['clock_seconds'] = rnd.randrange(0, 300)
            g['clock_sub'] = rnd.choice((0, 5))
            emu.write(0xe9ab8, struct.pack('<h', g['period_length']))
            emu.write(CLOCK, struct.pack('<hh', g['clock_seconds'], g['clock_sub']))
            for n_ in ('last_impact', 'crowd', 'camera_x'):
                g[n_] = struct.unpack('<h', emu.read({'last_impact': LAST_IMPACT, 'crowd': CROWD_NOISE + 2,
                                                      'camera_x': CAMERA_XY}[n_], 2))[0]
        del calls[:]
        ret = emu.call(LINEUP_ROUTINES[name], **regs)
        after = ai_record(emu)
        la = dict(lines_read(emu), ret=struct.unpack('<i', struct.pack('<I', ret))[0],
                  line_tables=[list(emu.read(a, 0x30)) for a in LINE_TABLES],
                  counts=list(struct.unpack('<3h', emu.read(LINEUP_COUNTS, 6))),
                  in_table=list(struct.unpack('<25i', emu.read(LINEUP_IN_TABLE, 100))))
        cases.append({'routine': name, 'args': args, 'globals': g, 'teams': teams, 'carrier': carrier, 'seed': seed,
                      'scratch_ac': scratch_ac, 'scratch': scratch, 'lines': lines_in,
                      'before': befores, 'order': draw_order(emu), 'calls': [list(c) for c in calls],
                      'after': {str(s_): {k_: v for k_, v in entity_fields(emu, s_).items() if befores[str(s_)].get(k_) != v}
                                for s_ in range(17)},
                      'world_after': after, 'lines_after': la})
        for a, n_ in ((GAME_FLAGS, 1), (OPTION_FLAGS, 4), (STOP_FLAGS, 2), (MISC_FLAGS, 4), (BREAKAWAY_FLAG, 4),
                      (PENALTY_SHOT_ACTIVE, 4), (PENALTY_SHOT_SETUP, 4), (PENALTY_SHOT_PHASE, 4)):
            emu.write(a, b'\0' * n_)
        emu.write(LINE_TABLES[0], bytes(DEFAULT_LINE_TABLE))
        emu.write(LINE_TABLES[1], bytes(DEFAULT_LINE_TABLE))
    for h in stubs:
        emu.uc.hook_del(h)
    for c in cases:
        c['before'] = {s_: {k_: v for k_, v in b.items() if base_fields[int(s_)].get(k_) != v} for s_, b in c['before'].items()}
        c['after'] = {s_: a for s_, a in c['after'].items() if a}
    return cases


CONTROL_PLAYER = 0x504da
SHOOT_ANIMS = (0x3f9, 0x491, 0xdd3, 0xe2b, 0x1265, 0x12dd, 0x1355, 0x138d)


def controls_cases(emu, rnd, base, tables, calls, base_fields):
    '''control_player for a user's player: at the faceoff dot, with the line change prompt open,
    while the puck waits to be dropped, as the carrier (passing, shooting, the prompt), without the
    puck (switching, checking, hooking, poke checks and blocks on shots at his net, taking over a
    pass for a one timer), busy, with line hotkeys, blocked controls, penalty shots'''
    cases = []
    for k in range(1500):
        g, teams, carrier = ai_world(emu, rnd, base, tables)
        t = rnd.randrange(2)
        player = rnd.choice((0, 2))
        actor = t * 6 + rnd.choice((1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 0))
        rec = bytearray(emu.read(ENTITIES + actor * 0x80, 0x80))
        g['user1_slot' if player == 0 else 'user2_slot'] = actor
        g['user1_team' if player == 0 else 'user2_team'] = t + 1 if rnd.random() < 0.9 else rnd.choice((0, 2 - t))
        other = rnd.choice((-1, -1, (1 - t) * 6 + rnd.randrange(1, 6), t * 6 + rnd.randrange(1, 6)))
        if other != actor:
            g['user2_slot' if player == 0 else 'user1_slot'] = other
            g['user2_team' if player == 0 else 'user1_team'] = (other // 6) + 1 if other >= 0 else 0
        f = {'flags': (rec[0x44] & ~0x28) | (8 if rnd.random() < 0.9 else 0) | (0x20 if rnd.random() < 0.2 else 0),
             'flags2': rnd.choice((0, 0, 0, 2, 4, 1)), 'speed': rnd.choice((0, 0, 3, 0x10)),
             'hit_by': rnd.choice((-1, rnd.randrange(12), rnd.randrange(12))), 'timer_b': rnd.choice((-1, 0, 3))}
        r = rnd.random()
        scen = ('faceoff' if r < 0.12 else 'prompt' if r < 0.27 else 'drop' if r < 0.32 else
                'carrier' if r < 0.52 else 'block' if r < 0.64 else 'free')
        if scen == 'faceoff':
            g['stop_flags'] |= 1
            if rnd.random() < 0.8:
                sp = rec[0x1c] & 7
                rec[0x1e + sp] = 23
            puck = bytearray(emu.read(PUCK, 0x80))
            put_fields(puck, {'timer_a': rnd.choice((0, 5, 0x10, 0x11, 0x20))})
            emu.write(PUCK, puck)
        elif scen == 'prompt':
            f['flags2'] |= 8
            emu.write(TEAM_RECORDS[t] + 0x44, bytes([emu.read(TEAM_RECORDS[t] + 0x44, 1)[0] | rnd.choice((0, 0, 1))]))
        elif scen == 'drop':
            puck = bytearray(emu.read(PUCK, 0x80))
            put_fields(puck, {'stack': 0x1c1c1c1c, 'stack2': 0x1c1c1c1c})
            emu.write(PUCK, puck)
            g['game_flags'] |= 1
        elif scen == 'carrier':
            carrier = actor
            g['action_flags'] = rnd.choice((0, 0, 4, 8))
            if g['action_flags'] & 8:
                f.update({'anim': rnd.choice(SHOOT_ANIMS), 'anim_pos': rnd.randrange(0x10)})
        elif scen == 'block':
            # a shot on his net: he stands between the puck and the net, C pressed, no opponent
            # within reach (the original measures x only)
            up = rec[0x44] & 0x80
            sgn = -1 if up else 1
            ex, ey = rnd.randrange(-0x40, 0x41), sgn * rnd.randrange(0x80, 0xd0)
            px, py = ex + rnd.randrange(-0x18, 0x19), ey - sgn * rnd.randrange(0x8, 0x40)
            pdir = emu.call(DIRECTION8, eax=(px - ex) & 0xffffffff, edx=(py - ey) & 0xffffffff) & 0xffff
            f.update({'x': ex << 16, 'y': ey << 16, 'speed': 0, 'puck_dist': rnd.randrange(0x8, 0x50),
                      'puck_dir': rnd.choice((pdir, pdir, (pdir + 1) & 7, (pdir - 1) & 7, rnd.randrange(8))),
                      'heading': rnd.choice((pdir, pdir, (pdir + 1) & 7, (pdir + 2) & 7, rnd.randrange(8))) << 16})
            f['flags'] &= ~0x20
            puck = bytearray(emu.read(PUCK, 0x80))
            put_fields(puck, {'x': px << 16, 'y': py << 16, 'vy': sgn * rnd.randrange(0, 0x2000), 'z': rnd.choice((0, 0, 5)) << 16,
                              'vz': rnd.choice((0, 0x900))})
            emu.write(PUCK, puck)
            shooter = (1 - t) * 6 + rnd.randrange(1, 6)
            for o in range((1 - t) * 6, (1 - t) * 6 + 6):
                orec = bytearray(emu.read(ENTITIES + o * 0x80, 0x80))
                put_fields(orec, {'x': (ex + rnd.choice((-1, 1)) * rnd.randrange(0x20, 0x40)) << 16})
                if o == shooter:
                    put_fields(orec, {'anim': rnd.choice(SHOOT_ANIMS + SHOOT_ANIMS + (0x289,))})
                emu.write(ENTITIES + o * 0x80, orec)
            carrier = rnd.choice((-1, -1, shooter))
            g['last_shooter'] = shooter
            g['pred0_steps'] = rnd.choice((5, 20, 60, 60))
            g['pred1_steps'] = rnd.choice((5, 20, 60, 60))
        else:
            carrier = rnd.choice((-1, -1, (1 - t) * 6 + rnd.randrange(6), t * 6 + rnd.randrange(6)))
            if carrier == actor:
                carrier = -1
            if rnd.random() < 0.4:
                g['pass_target'] = rnd.choice((actor, t * 6 + rnd.randrange(1, 6)))
                g['one_timer'] = rnd.choice((0, 1))
            if rnd.random() < 0.4:
                # a shot on his own net: the puck between him and the net, the shooter winding up
                up = rec[0x44] & 0x80
                sgn = -1 if up else 1
                ny = sgn * rnd.randrange(0x90, 0xe0)
                f.update({'x': rnd.randrange(-0x50, 0x51) << 16, 'y': (ny + sgn * rnd.randrange(0, 0x30)) << 16,
                          'puck_dist': rnd.randrange(0x10, 0x60), 'puck_dir': rnd.randrange(8)})
                puck = bytearray(emu.read(PUCK, 0x80))
                put_fields(puck, {'x': rnd.randrange(-0x40, 0x41) << 16, 'y': (ny - sgn * rnd.randrange(0, 0x30)) << 16,
                                  'vy': sgn * rnd.randrange(0, 0x2000), 'z': rnd.choice((0, 0, 5)) << 16, 'vz': rnd.choice((0, 0x900))})
                emu.write(PUCK, puck)
                shooter = (1 - t) * 6 + rnd.randrange(1, 6)
                srec = bytearray(emu.read(ENTITIES + shooter * 0x80, 0x80))
                put_fields(srec, {'anim': rnd.choice(SHOOT_ANIMS + (0x289,))})
                emu.write(ENTITIES + shooter * 0x80, srec)
                g['last_shooter'] = shooter
                g['pred0_steps'] = rnd.choice((5, 20, 60))
                g['pred1_steps'] = rnd.choice((5, 20, 60))
                if rnd.random() < 0.5:
                    carrier = -1
            if rnd.random() < 0.3:
                # an opponent close in front
                o = (1 - t) * 6 + rnd.randrange(6)
                orec = bytearray(emu.read(ENTITIES + o * 0x80, 0x80))
                put_fields(orec, {'x': ((struct.unpack_from('<i', rec, 0)[0] >> 16) + rnd.randrange(-0x28, 0x29)) << 16,
                                  'y': ((struct.unpack_from('<i', rec, 4)[0] >> 16) + rnd.randrange(-0x28, 0x29)) << 16})
                emu.write(ENTITIES + o * 0x80, orec)
        put_fields(rec, f)
        emu.write(ENTITIES + actor * 0x80, rec)
        emu.write(PUCK + 0x42, bytes([carrier & 0xff]))
        if rnd.random() < 0.2:
            g['hotkey%d' % t] = 1
            g['hotkey_line%d' % t] = rnd.randrange(5)
        if rnd.random() < 0.12:
            g['controls_blocked'] = 1
        if rnd.random() < 0.05:
            g['penalty_shot_phase'] = 1
            g['penalty_shot_active'] = rnd.choice((0, 1))
        write_globals(emu, g)
        emu.write(OPTION_FLAGS, struct.pack('<I', (g['option_flags'] & 0xff) | (g['settings2'] << 8)))
        seed = rnd.getrandbits(32)
        emu.write(SEED, struct.pack('<I', seed))
        control = rnd.choice((0, 1, 2, 3, 4, 5, 6, 7, 8, 8, 9)) | rnd.choice((0, 0, 0x10, 0x20, 0x40, 0x30))
        changed = rnd.choice((0, 0x10, 0x20, 0x40, 0x70, control & 0x70))
        if scen == 'block':
            control |= 0x40
            changed |= 0x40
        pressed = control & 0x70 & changed
        scratch_ac = rnd.getrandbits(16) << 16 | changed
        scratch = [control, pressed]
        emu.write(SCRATCH[2], struct.pack('<I', scratch_ac))
        emu.write(SCRATCH[0], struct.pack('<H', scratch[0]))
        emu.write(SCRATCH[1], struct.pack('<H', scratch[1]))
        for ti in range(2):
            teams[ti]['flags'] = emu.read(TEAM_RECORDS[ti] + 0x44, 1)[0]
        befores = {str(s_): dict(entity_fields(emu, s_), prev=list(struct.unpack('<iii', emu.read(ENTITIES + s_ * 0x80 + 0x74, 12))))
                   for s_ in range(17)}
        order = draw_order(emu)
        del calls[:]
        emu.call(CONTROL_PLAYER, eax=ENTITIES + actor * 0x80, edx=player)
        after = ai_record(emu)
        cases.append({'routine': 'control_player', 'args': [actor, player], 'scen': scen, 'globals': g, 'teams': teams,
                      'carrier': carrier, 'seed': seed, 'scratch_ac': scratch_ac, 'scratch': scratch,
                      'before': befores, 'order': order, 'calls': [list(c) for c in calls],
                      'after': {str(s_): {k_: v for k_, v in entity_fields(emu, s_).items() if befores[str(s_)].get(k_) != v}
                                for s_ in range(17)},
                      'world_after': after, 'lines_after': {'scratch': list(struct.unpack('<hh', emu.read(SCRATCH[0], 2) + emu.read(SCRATCH[1], 2))),
                                                            'scratch_ac': struct.unpack('<I', emu.read(SCRATCH[2], 4))[0]}})
        for a, n_ in ((GAME_FLAGS, 1), (OPTION_FLAGS, 4), (STOP_FLAGS, 2), (MISC_FLAGS, 4), (BREAKAWAY_FLAG, 4),
                      (PENALTY_SHOT_ACTIVE, 4), (PENALTY_SHOT_SETUP, 4), (PENALTY_SHOT_PHASE, 4)):
            emu.write(a, b'\0' * n_)
        emu.write(TEAM_RECORDS[0] + 0x44, b'\0')
        emu.write(TEAM_RECORDS[1] + 0x44, b'\0')
    for c in cases:
        c['before'] = {s_: {k_: v for k_, v in b.items() if base_fields[int(s_)].get(k_) != v} for s_, b in c['before'].items()}
        c['after'] = {s_: a for s_, a in c['after'].items() if a}
    return cases


# the line changes: the routines called directly (with their register arguments)
LINE_ROUTINES = {'build_lines': 0x64614, 'assign_line_positions': 0x5bbfa, 'apply_line_change': 0x5bef4,
                 'choose_line': 0x5a0a3, 'line_avg_energy': 0x5a30c, 'team_avg_energy': 0x5a03b,
                 'pick_next_line': 0x50908, 'cpu_line_change_select': 0x50975, 'request_line_change': 0x50434,
                 'maybe_pull_goalie': 0x591c7, 'cpu_pull_goalie_check': 0x59352, 'late_game_pull_goalie': 0x593f5,
                 'cpu_line_change': 0x59265, 'dress_line': 0x5e0dd, 'send_team_to_faceoff': 0x511b4,
                 'handle_line_change': 0x52bb6, 'adjust_strategy': 0x5a581, 'hotkey_pull_goalie': 0x671e8,
                 'controls_goalie_pull_request': 0x7cbb3, 'choose_goalie': 0x672f9}
PERIOD_NUM = 0xd8c84


def lines_read(emu):
    '''the line change state outside the team records: the candidate lists of build_lines, the
    lineup request, the goalie menu's radio buttons, the scratch words'''
    raw = emu.read(POS_LISTS, 11 * 0x32)
    lists = [[[struct.unpack_from('<b', raw, k * 0x32 + t * 0x19 + i)[0] for i in range(25)] for k in range(11)] for t in range(2)]
    req = list(struct.unpack('<12b', emu.read(LINEUP_REQ, 12)))
    return {'pos_lists': lists, 'req': req, 'menu': [emu.read(a, 1)[0] for a in GOALIE_MENU],
            'scratch': list(struct.unpack('<hh', emu.read(SCRATCH[0], 2) + emu.read(SCRATCH[1], 2)))}


def lines_cases(emu, rnd, base, tables, calls, base_fields, teams_path):
    '''the line change routines on random teams: line tables of TEAMS.DB (now and then edited),
    rosters with positions, ratings, statuses (empty, injured, scratched), energies, players out or
    in the penalty box, the coaching fields, the goalie pulled or requested, special teams, the
    end of the third period'''
    with open(teams_path, 'rb') as f:
        teams_db = f.read()
    nteams = len(teams_db) // 0x2e8
    names = list(LINE_ROUTINES)
    cases = []
    for k in range(100 * len(names)):
        name = names[k % len(names)]
        g, teams, carrier = ai_world(emu, rnd, base, tables)
        lines_in = {'positions': [], 'ratings': [], 'line_tables': []}
        if rnd.random() < 0.5:
            g['period'] = 2
            g['clock_seconds'] = rnd.randrange(0, 0x50)
        for ti, t in enumerate(TEAM_RECORDS):
            n = rnd.randrange(nteams)
            lt = bytearray(teams_db[n * 0x2e8 + 0xbc:n * 0x2e8 + 0xec])
            for _ in range(rnd.choice((0, 0, 0, 1, 3))):
                lt[rnd.randrange(0x26)] = rnd.randrange(25)
            lt += bytes([0x64]) * 0x10
            emu.write(LINE_TABLES[ti], bytes(lt[:0x30]))   # (font_current_default follows the home team's)
            lines_in['line_tables'].append(list(lt))
            pos = [rnd.choice('CCLLRRDDD') for _ in range(25)] + ['G'] * 3
            ratings = [[rnd.randrange(1, 7) for _ in range(0x14)] for _ in range(25)]
            status = [rnd.choice((3, 3, 3, 3, 3, 3, 3, 0, 1, 2)) for _ in range(25)] + [3, 3, rnd.choice((0, 3))]
            if rnd.random() < 0.3:
                status[rnd.randrange(25)] = 7
            for i in range(28):
                emu.write(ROSTERS + ti * 0x444 + i * 0x27, bytes([status[i]]))
                emu.write(ROSTERS + ti * 0x444 + i * 0x27 + 6, pos[i].encode())
            for i in range(25):
                emu.write(PLAYER_RATINGS + ti * 0x1f4 + i * 0x14, bytes(ratings[i]))
            lines_in['positions'].append(''.join(pos))
            lines_in['ratings'].append(ratings)
            teams[ti]['roster_status'] = status
            energies = [rnd.choice((0x1000, 0x1000, rnd.randrange(0x400, 0x1001))) for _ in range(28)]
            emu.write(t + 0x46, struct.pack('<28h', *energies))
            teams[ti]['energies'] = energies
            ent = list(teams[ti]['entity_of'])
            for i in range(28):
                if ent[i] == -2 and rnd.random() < 0.15:
                    ent[i] = rnd.choice((-3, -3, 1, -4))
            emu.write(t + 0x7e, struct.pack('<28h', *ent))
            teams[ti]['entity_of'] = ent
            f = {'goalie_request': rnd.choice((0, 0, 1, 0xff00, 0xfff0, 0xff01, 0x10)), 'current_line': rnd.randrange(8),
                 'dpair': rnd.randrange(3), 'extra_attacker': rnd.choice((-1, 2, 5)), 'mode': rnd.choice((0, 1, 1, 4, 5, 6, 8)),
                 'flags2': rnd.choice((0, 1, 1, 0x41, 0x81, 0xc1, 0x40)), 'energy_threshold': rnd.choice((0xccc, 0xd9a, 0x800)),
                 'skaters': rnd.choice((6, 6, 6, 5, 4)), 'goals': rnd.randrange(5), 'flags': rnd.choice((0, 0, 2))}
            for n_, o, sz in AI_TEAM_FIELDS:
                if n_ in f:
                    emu.write(t + o, struct.pack('<' + _FMT[abs(sz)], f[n_] & ((1 << (8 * abs(sz))) - 1)))
            teams[ti].update({n_: struct.unpack('<' + _FMT[sz], emu.read(t + o, abs(sz)))[0] for n_, o, sz in AI_TEAM_FIELDS if n_ in f})
        # some players with a change pending (handle_line_change, dress_line, send_team_to_faceoff)
        for slot in range(12):
            if rnd.random() < 0.3:
                rec = bytearray(emu.read(ENTITIES + slot * 0x80, 0x80))
                roster = struct.unpack_from('<b', rec, 0x47)[0]
                put_fields(rec, {'next_roster': rnd.choice((roster, rnd.randrange(28))), 'next_line': rnd.randrange(-1, 7),
                                 'timer_b': rnd.choice((0, 0, -100))})
                emu.write(ENTITIES + slot * 0x80, rec)
        write_globals(emu, g)
        emu.write(OPTION_FLAGS, struct.pack('<I', (g['option_flags'] & 0xff) | (g['settings2'] << 8)))
        emu.write(PERIOD_NUM, struct.pack('<h', g['period'] + 1))
        emu.call(LINE_ROUTINES['build_lines'])
        if name == 'build_lines':
            emu.write(POS_LISTS, bytes(rnd.choice((0xff, 0, 1, 7)) for _ in range(11 * 0x32)))
        for a in GOALIE_MENU:
            emu.write(a, bytes([rnd.choice((1, 2))]))
        emu.write(LINEUP_REQ, bytes([rnd.randrange(-1, 28) & 0xff for _ in range(6)] + [rnd.randrange(7) for _ in range(6)]))
        seed = rnd.getrandbits(32)
        emu.write(SEED, struct.pack('<I', seed))
        scratch_ac = rnd.choice((0, 1, 2, 3, 0xffff, 0x10002))
        # (e03bc: the place of the line change prompt for pick_next_line, else a stale word)
        scratch = [rnd.choice((0, 1, 2, 3) + (() if name == 'pick_next_line' else (0x800, 0x1000))), rnd.randrange(0x10000)]
        emu.write(SCRATCH[2], struct.pack('<I', scratch_ac))
        emu.write(SCRATCH[0], struct.pack('<H', scratch[0]))
        emu.write(SCRATCH[1], struct.pack('<H', scratch[1]))
        lines_in.update(lines_read(emu))
        befores = {str(s_): dict(entity_fields(emu, s_), prev=list(struct.unpack('<iii', emu.read(ENTITIES + s_ * 0x80 + 0x74, 12))))
                   for s_ in range(17)}
        t = rnd.randrange(2)
        slot = t * 6 + rnd.randrange(6)
        args = []
        regs = {}
        if name in ('assign_line_positions', 'apply_line_change', 'team_avg_energy', 'dress_line'):
            args = [t]
            regs = {'eax': TEAM_RECORDS[t]}
        elif name == 'choose_line':
            args = [t]
            regs = {'eax': TEAM_RECORDS[1 - t], 'edx': TEAM_RECORDS[t]}
        elif name == 'line_avg_energy':
            args = [t, rnd.randrange(8)]
            regs = {'eax': TEAM_RECORDS[t], 'edx': args[1]}
        elif name in ('pick_next_line', 'cpu_line_change_select', 'handle_line_change'):
            args = [slot]
            regs = {'eax': ENTITIES + slot * 0x80}
        elif name == 'request_line_change':
            args = [slot, rnd.randrange(5)]
            regs = {'eax': ENTITIES + slot * 0x80, 'edx': args[1]}
        elif name == 'maybe_pull_goalie':
            args = [t, rnd.randrange(-0x100, 0x101)]
            regs = {'eax': TEAM_RECORDS[t], 'edx': TEAM_RECORDS[1 - t], 'ebx': args[1]}
        elif name in ('late_game_pull_goalie', 'send_team_to_faceoff', 'adjust_strategy', 'hotkey_pull_goalie',
                      'controls_goalie_pull_request'):
            args = [t]
            regs = {'eax': t}
        elif name == 'choose_goalie':
            args = [t, rnd.choice((0, 1, -1))]
            regs = {'eax': t, 'edx': args[1]}
        del calls[:]
        ret = emu.call(LINE_ROUTINES[name], **regs)
        after = ai_record(emu)
        cases.append({'routine': name, 'args': args, 'globals': g, 'teams': teams, 'carrier': carrier, 'seed': seed,
                      'scratch_ac': scratch_ac, 'scratch': scratch, 'lines': lines_in,
                      'before': befores, 'order': draw_order(emu), 'calls': [list(c) for c in calls],
                      'after': {str(s_): {k_: v for k_, v in entity_fields(emu, s_).items() if befores[str(s_)].get(k_) != v}
                                for s_ in range(17)},
                      'world_after': after, 'lines_after': dict(lines_read(emu), ret=struct.unpack('<i', struct.pack('<I', ret))[0])})
        for a, n_ in ((GAME_FLAGS, 1), (OPTION_FLAGS, 4), (STOP_FLAGS, 2), (MISC_FLAGS, 4), (BREAKAWAY_FLAG, 4),
                      (PENALTY_SHOT_ACTIVE, 4), (PENALTY_SHOT_SETUP, 4), (PENALTY_SHOT_PHASE, 4)):
            emu.write(a, b'\0' * n_)
        emu.write(LINE_TABLES[0], bytes(DEFAULT_LINE_TABLE))
        emu.write(LINE_TABLES[1], bytes(DEFAULT_LINE_TABLE))
    for c in cases:
        c['before'] = {s_: {k_: v for k_, v in b.items() if base_fields[int(s_)].get(k_) != v} for s_, b in c['before'].items()}
        c['after'] = {s_: a for s_, a in c['after'].items() if a}
    return cases


UPDATE_CAMERA = 0x65d01
CAMERA = 0xc9098                              # x, y; then the target x, y at 0xc90ac and the lead 0xc90b0
STOPPAGE_TIMER = 0xc90ce
REF_PHASE = 0xc90d4


def camera_cases(emu, rnd, base):
    """update_camera: the carrier or the puck with the lead, the referee during a stoppage and the
    faceoff dot, the clock at 0:00, the held camera, the cup presentation (game_flags 0x80)"""
    out = []
    for k in range(600):
        emu.write(ENTITIES, base)
        cam = [rnd.randrange(-0x20, 0x21), rnd.randrange(-0xbc, 0xed), rnd.randrange(-0x90, 0x91),
               rnd.randrange(-0xf0, 0xf1), rnd.randrange(-0x32, 0x33)]
        g = {'game_flags': rnd.choice((0, 0, 0, 1, 4, 5, 0x80, 0x81)), 'stoppage_timer': rnd.choice((-1, -1, 0, 5)),
             'ref_phase': rnd.choice((-1, -1, 0, 1, 2)), 'clock': rnd.choice(((0, 0), (0, 3), (1, 0), (200, 7), (59, 0))),
             'action_flags': rnd.choice((0, 0, 0x40)), 'faceoff': rnd.choice(((0, 0), (-0x50, 0x9a), (0x50, -0x56)))}
        carrier = rnd.choice((-1, -1, rnd.randrange(12), rnd.randrange(12), 16))
        scratch = [rnd.randrange(0x10000), rnd.randrange(0x10000), rnd.randrange(0x10000)]
        ents = {}
        for slot in (14, 16) + ((carrier,) if carrier >= 0 else ()):
            rec = bytearray(emu.read(ENTITIES + slot * 0x80, 0x80))
            near = slot == 16 and rnd.random() < 0.4
            fx, fy = g['faceoff']
            f = {'x': ((fx + rnd.randrange(-0x30, 0x31)) if near else rnd.randrange(-0x90, 0x91)) << 16,
                 'y': ((fy + rnd.randrange(-0x30, 0x31)) if near else rnd.randrange(-0xf0, 0xf1)) << 16,
                 'vy': rnd.randrange(-0x1800, 0x1801), 'flags': rnd.choice((0, 0x80)),
                 'target_x': rnd.randrange(-0x90, 0x91), 'target_y': rnd.randrange(-0xf0, 0xf1)}
            if slot == 16:
                f['state_sp'] = 0
                st = rnd.choice((0x22, 0x2c, 0x1f, 0x22))
                f['stack'] = st | st << 8 | st << 16 | st << 24
            put_fields(rec, f)
            emu.write(ENTITIES + slot * 0x80, rec)
            ents[str(slot)] = {n: f[n] for n in ('x', 'y', 'vy', 'flags', 'target_x', 'target_y')}
            if slot == 16:
                ents['16']['state'] = st
        emu.write(PUCK + 0x42, bytes([carrier & 0xff]))
        emu.write(CAMERA, struct.pack('<hh', cam[0], cam[1]))
        emu.write(CAMERA + 0x14, struct.pack('<hhh', cam[2], cam[3], cam[4]))
        emu.write(0xc90b2, struct.pack('<hh', *g['faceoff']))
        emu.write(GAME_FLAGS, bytes([g['game_flags']]))
        emu.write(STOPPAGE_TIMER, struct.pack('<h', g['stoppage_timer']))
        emu.write(REF_PHASE, struct.pack('<h', g['ref_phase']))
        emu.write(CLOCK, struct.pack('<hh', *g['clock']))
        emu.write(ACTION_FLAGS, bytes([g['action_flags']]))
        emu.write(SCRATCH[0], struct.pack('<H', scratch[0]))
        emu.write(SCRATCH[1], struct.pack('<H', scratch[1]))
        emu.write(SCRATCH[2], struct.pack('<H', scratch[2]))
        emu.call(UPDATE_CAMERA)
        after = list(struct.unpack('<hh', emu.read(CAMERA, 4))) + list(struct.unpack('<hhh', emu.read(CAMERA + 0x14, 6)))
        after += [struct.unpack('<h', emu.read(a, 2))[0] for a in SCRATCH]
        out.append({'cam': cam, 'g': g, 'carrier': carrier, 'scratch': scratch, 'ents': ents, 'after': after})
    emu.write(GAME_FLAGS, b'\0')
    emu.write(ACTION_FLAGS, b'\0')
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
    out['shoot'] = shoot_cases(emu, rnd, base, calls)
    out['camera'] = camera_cases(emu, rnd, base)
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


def write_golden(outdir, name, data):
    text = (json.dumps(data, separators=(',', ':'), sort_keys=True) + '\n').encode()
    if len(text) > 1 << 20:
        # the large ones compressed (the test reads both; tools/nhl/golden_check.py compares the
        # contents, so that another zlib cannot make a difference)
        path = os.path.join(outdir, name + '.json.gz')
        with open(path, 'wb') as f:
            f.write(gzip.compress(text, compresslevel=9, mtime=0))
        if os.path.exists(path[:-3]):
            os.remove(path[:-3])
    else:
        path = os.path.join(outdir, name + '.json')
        with open(path, 'wb') as f:
            f.write(text)
        if os.path.exists(path + '.gz'):
            os.remove(path + '.gz')
    print('wrote', path)


def write_ai(outdir, data):
    '''the AI cases one file per group (ai_GROUP.json[.gz], the base records in ai_base): a change
    to one group leaves the others' files as they are'''
    for group, cases in data.items():
        write_golden(outdir, 'ai_' + group, {group: cases})
    for n in ('ai.json', 'ai.json.gz'):
        if os.path.exists(os.path.join(outdir, n)):
            os.remove(os.path.join(outdir, n))


LEAGUE_SIM_GAME = 0x452c5                      # (dir, ext, game index, record) + TEAMS file, CARTEAMS file, forced winner
FILE_READ = 0x145a2                            # stubbed: (file, buffer, offset, size) from the files of the case
FILE_WRITE = 0x145f9                           # stubbed: into them
ALLOCMEM = 0x8cca8                             # stubbed (cdecl): a buffer of the pool
RAND_STATE = 0x8eb21                           # the C library's rand() state
LEAGUE_BUFFERS = (('SEASON', 0xd07bb), ('CAREER', 0xd07bf), ('KEY', 0xd07c7))   # the databases league_play_day loads
FORWARD_LINE_ORDER = 0xc900c                   # 2 x 10 dwords: the forward lines in their order of the game
DEFENCE_PAIR_ORDER = 0xc905c                   # 2 x 3 dwords
LEAGUE_FILES = ('KEY', 'CAREER', 'CARTEAMS', 'TEAMS', 'SEASON')


def byte_diff(a, b):
    """the runs of bytes of b that differ from a: [offset, hex]"""
    out = []
    i = 0
    while i < len(b):
        if a[i] != b[i]:
            j = i
            while j < len(b) and (a[j] != b[j] or (j + 1 < len(b) and a[j + 1] != b[j + 1])):
                j += 1
            out.append([i, bytes(b[i:j]).hex()])
            i = j
        else:
            i += 1
    return out


def league_cases(exe, gamedir, count=400):
    """league_sim_game called directly: the statistical game of two computer teams of the league
    files the game ships (TEAMS, CARTEAMS, KEY, CAREER, SEASON .DB), regular season and play-off games,
    a winner forced or not, the three period lengths, the C library's rand() from a random seed and
    the forward lines and defence pairs in a random order"""
    emu = PortEmu(exe)
    rnd = random.Random(1092)
    base = {n: read(gamedir, n + '.DB') for n in LEAGUE_FILES}
    bufs = {n: emu.alloc(len(base[n]) + 0x100) for n, _ in LEAGUE_BUFFERS}
    for n, a in LEAGUE_BUFFERS:
        emu.write(a, struct.pack('<I', bufs[n]))
    pool = [emu.alloc(0x400) for _ in range(32)]
    used = {'n': 0}
    files = {}
    handles = {1: 'TEAMS', 2: 'CARTEAMS'}   # (league_sim_game reads the team's CARTEAMS record and does not use it)

    def reg(r):
        return emu.uc.reg_read(r) & 0xffffffff

    def on_alloc(eax):
        p_ = pool[used['n']]
        used['n'] += 1
        emu.write(p_, b'\0' * 0x400)
        return p_

    def on_read(eax):
        f = files[handles[eax & 0xffffffff]]
        buf, off, size = reg(UC_X86_REG_EDX), reg(UC_X86_REG_EBX), reg(UC_X86_REG_ECX)
        if off + size > len(f):
            return 1
        emu.write(buf, bytes(f[off:off + size]))
        return 0

    def on_write(eax):
        f = files[handles[eax & 0xffffffff]]
        buf, off, size = reg(UC_X86_REG_EDX), reg(UC_X86_REG_EBX), reg(UC_X86_REG_ECX)
        if off + size > len(f):
            return 1
        f[off:off + size] = emu.read(buf, size)
        return 0
    emu.stub(ALLOCMEM, on_alloc)
    emu.stub(FREEMEM, lambda eax: None)
    emu.stub(FILE_READ, on_read)
    emu.stub(FILE_WRITE, on_write)
    names = emu.alloc(b'\0' * 16)
    recbuf = emu.alloc(b'\0' * 8)
    cases = []
    for k in range(count):
        playoffs = rnd.random() < 0.3
        index = rnd.randrange(0x444, 0x4ad) if playoffs else rnd.randrange(0x444)
        teams = rnd.sample(range(26), 2)
        forced = rnd.choice((-1, -1, -1, 0, 1, 2))
        option_flags = (rnd.randrange(0x10000) & ~0xc00) | rnd.choice((0, 0x400, 0x800, 0xc00))
        seed = rnd.getrandbits(32)
        fwd = []
        for t in range(2):
            o = [0, 1, 2, 3, 0, 1, 2, 0, 1, 0]
            rnd.shuffle(o)
            fwd.append(o)
        dfn = [rnd.sample(range(3), 3) for _ in range(2)]
        rec = [rnd.randrange(1, 13), rnd.randrange(1, 29), teams[0], teams[1], 0xff, 0xff]
        for n, _ in LEAGUE_BUFFERS:
            emu.write(bufs[n], base[n])
        files = {'TEAMS': bytearray(base['TEAMS']), 'CARTEAMS': bytearray(base['CARTEAMS'])}
        emu.write(recbuf, bytes(rec))
        emu.write(OPTION_FLAGS, struct.pack('<I', option_flags))
        for t in range(2):
            emu.write(FORWARD_LINE_ORDER + t * 40, struct.pack('<10i', *fwd[t]))
            emu.write(DEFENCE_PAIR_ORDER + t * 12, struct.pack('<3i', *dfn[t]))
        emu.call(SRAND, eax=seed)
        used['n'] = 0
        ret = emu.call(LEAGUE_SIM_GAME, eax=names, edx=names, ebx=index, ecx=recbuf, stack=(1, 2, forced))
        after = {n: byte_diff(base[n], emu.read(bufs[n], len(base[n]))) for n, _ in LEAGUE_BUFFERS}
        after.update({n: byte_diff(base[n], files[n]) for n in ('TEAMS', 'CARTEAMS')})
        state = struct.unpack('<I', emu.read(emu.call(RAND_STATE) & 0xffffffff, 4))[0]
        cases.append({'index': index, 'record': rec, 'forced': forced, 'option_flags': option_flags, 'seed': seed,
                      'fwd': fwd, 'def': dfn,
                      'after': dict(after, record=list(emu.read(recbuf, 6)), ret=s32(ret), rand=state,
                                    fwd=[list(struct.unpack('<10i', emu.read(FORWARD_LINE_ORDER + t * 40, 40))) for t in range(2)],
                                    dfn=[list(struct.unpack('<3i', emu.read(DEFENCE_PAIR_ORDER + t * 12, 12))) for t in range(2)])})
    emu.write(OPTION_FLAGS, b'\0' * 4)
    return cases


LEAGUE_SCORES_INIT = 0x2f2b1                   # (home, away): six other games of the night
LEAGUE_SCORES_ADVANCE = 0x2f3d7                # (period): their scores up to the period of the game on the ice
SCORES_GAMES = 0xdd774                         # calendar_games: 6 x (team a, team b)
SCORES_STATUS = 0xdd730                        # 6 dwords: 0..2 the period, 4 overtime, 5 over, 6 over in regulation
SCORES_GOALS = 0xdd788                         # 6 x (goals a, goals b)


def scores_cases(exe, count=200):
    '''the scores around the league: league_scores_init for a game of two random teams, then
    league_scores_advance after each period (and overtime) as the end of a period calls it, with
    the C library's rand() from a random seed'''
    emu = PortEmu(exe)
    rnd = random.Random(26)

    def state():
        return {'games': [list(emu.read(SCORES_GAMES + 2 * g, 2)) for g in range(6)],
                'status': list(struct.unpack('<6i', emu.read(SCORES_STATUS, 24))),
                'goals': [list(emu.read(SCORES_GOALS + 2 * g, 2)) for g in range(6)],
                'rand': struct.unpack('<I', emu.read(emu.call(RAND_STATE) & 0xffffffff, 4))[0]}
    cases = []
    for k in range(count):
        home, away = rnd.sample(range(26), 2)
        seed = rnd.getrandbits(32)
        emu.call(SRAND, eax=seed)
        emu.write(TEAM_IDS, struct.pack('<hh', home, away))
        emu.call(LEAGUE_SCORES_INIT, eax=home, edx=away)
        steps = [state()]
        periods = list(range(rnd.choice((3, 4, 5))))
        for p_ in periods:
            emu.call(LEAGUE_SCORES_ADVANCE, eax=p_)
            steps.append(state())
        cases.append({'home': home, 'away': away, 'seed': seed, 'periods': periods, 'steps': steps})
    return cases


SCHEDULE_RANK_TEAMS = 0x42bba                  # (order list, -, TEAMS file): each conference by points
PLAYOFF_MAKE_ROUND1 = 0x42fed                  # (order, play-off games, TEAMS file, series length) + the human teams


def playoff_cases(exe, gamedir, count=200):
    """the play-off seeding: schedule_rank_teams (with sort_teams_by_points) on random standings of
    the league files' teams (equal points, wins and goals now and then), then playoff_make_round1
    (with playoff_set_series) for series of 1, 3, 5 or 7 games and some human teams, whose records
    list their play-off games"""
    emu = PortEmu(exe)
    rnd = random.Random(16)
    base = read(gamedir, 'TEAMS.DB')
    files = {}

    def reg(r):
        return emu.uc.reg_read(r) & 0xffffffff

    def on_read(eax):
        f = files['TEAMS']
        buf, off, size = reg(UC_X86_REG_EDX), reg(UC_X86_REG_EBX), reg(UC_X86_REG_ECX)
        if off + size > len(f):
            return 1
        emu.write(buf, bytes(f[off:off + size]))
        return 0

    def on_write(eax):
        f = files['TEAMS']
        buf, off, size = reg(UC_X86_REG_EDX), reg(UC_X86_REG_EBX), reg(UC_X86_REG_ECX)
        if off + size > len(f):
            return 1
        f[off:off + size] = emu.read(buf, size)
        return 0
    emu.stub(FILE_READ, on_read)
    emu.stub(FILE_WRITE, on_write)
    order_buf = emu.alloc(b'\0' * 0x80)
    po = emu.alloc(b'\xff' * 15 * 42)
    pinfo = emu.alloc(b'\0' * 0x400)
    cases = []
    for k in range(count):
        teams = bytearray(base)
        stand = []
        for t in range(26):
            v = [rnd.randrange(15, 50), rnd.randrange(16), rnd.randrange(150, 350), rnd.randrange(150, 350)]
            if stand and rnd.random() < 0.35:
                other = rnd.choice(stand)
                keep = rnd.randrange(1, 5)
                v = other[:keep] + v[keep:]
                if keep == 1:             # the same points from other wins and ties
                    pts = other[0] * 2 + other[1]
                    v[0] = rnd.randrange(max(0, (pts - 15 + 1) // 2), pts // 2 + 1)
                    v[1] = pts - 2 * v[0]
            stand.append(v)
            teams[t * 0x2e8 + 0x29] = v[0]
            teams[t * 0x2e8 + 0x2b] = v[1]
            struct.pack_into('<HH', teams, t * 0x2e8 + 0x2c, v[2], v[3])
        files['TEAMS'] = teams
        before = bytes(teams)
        emu.write(order_buf, b'\xff' * 0x80)
        emu.call(SCHEDULE_RANK_TEAMS, eax=order_buf, ebx=1)
        order = list(struct.unpack('<28i', emu.read(order_buf, 0x70)))
        n = rnd.choice((1, 3, 5, 7, 7))
        humans = sorted(rnd.sample(range(26), rnd.choice((0, 1, 1, 2, 4))))
        emu.write(pinfo, b'\0' * 0x400)
        for t in humans:
            emu.write(pinfo + 0x20 + t * 30 + 0x17, b'\x01')
        emu.write(po, b'\xff' * 15 * 42)
        ret = emu.call(PLAYOFF_MAKE_ROUND1, eax=order_buf, edx=po, ebx=1, ecx=n, stack=(pinfo + 0x20,))
        cases.append({'standings': stand, 'n': n, 'humans': humans, 'order': order,
                      'after': {'ret': s32(ret), 'po': emu.read(po, 15 * 42).hex(), 'TEAMS': byte_diff(before, files['TEAMS'])}})
    return cases


PLAYOFF_ROUND1_DONE = 0x43644                  # (play-off games, TEAMS file, CARTEAMS file, dir) + ext: the round's games nobody played
PLAYOFF_CHAIN = (('make_round2', 0x43757), ('round2_done', 0x43e40), ('make_round3', 0x43f4b),
                 ('round3_done', 0x443b6), ('make_final', 0x444c9), ('final_done', 0x447a6))


def round_cases(exe, gamedir, count=60):
    """playoff_round1_done: the first round seeded (schedule_rank_teams, playoff_make_round1 on
    random standings), some games of each series played (random scores, up to a decided series),
    the rest simulated by league_sim_game, the games a decided series did not need taken out"""
    emu = PortEmu(exe)
    rnd = random.Random(1190)
    base = {n: read(gamedir, n + '.DB') for n in LEAGUE_FILES}
    bufs = {n: emu.alloc(len(base[n]) + 0x100) for n, _ in LEAGUE_BUFFERS}
    for n, a in LEAGUE_BUFFERS:
        emu.write(a, struct.pack('<I', bufs[n]))
    pool = [emu.alloc(0x400) for _ in range(32)]
    used = {'n': 0}
    files = {}
    handles = {1: 'TEAMS', 2: 'CARTEAMS'}   # (league_sim_game reads the team's CARTEAMS record and does not use it)

    def reg(r):
        return emu.uc.reg_read(r) & 0xffffffff

    def on_alloc(eax):
        p_ = pool[used['n'] % 32]
        used['n'] += 1
        emu.write(p_, b'\0' * 0x400)
        return p_

    def on_read(eax):
        f = files[handles[eax & 0xffffffff]]
        buf, off, size = reg(UC_X86_REG_EDX), reg(UC_X86_REG_EBX), reg(UC_X86_REG_ECX)
        if off + size > len(f):
            return 1
        emu.write(buf, bytes(f[off:off + size]))
        return 0

    def on_write(eax):
        f = files[handles[eax & 0xffffffff]]
        buf, off, size = reg(UC_X86_REG_EDX), reg(UC_X86_REG_EBX), reg(UC_X86_REG_ECX)
        if off + size > len(f):
            return 1
        f[off:off + size] = emu.read(buf, size)
        return 0
    emu.stub(ALLOCMEM, on_alloc)
    emu.stub(FREEMEM, lambda eax: None)
    emu.stub(FILE_READ, on_read)
    emu.stub(FILE_WRITE, on_write)
    names = emu.alloc(b'\0' * 16)
    order_buf = emu.alloc(b'\0' * 0x80)
    po = emu.alloc(b'\xff' * 15 * 42)
    pinfo = emu.alloc(b'\0' * 0x400)
    cases = []
    for k in range(count):
        teams = bytearray(base['TEAMS'])
        stand = []
        for t in range(26):
            v = [rnd.randrange(15, 50), rnd.randrange(16), rnd.randrange(150, 350), rnd.randrange(150, 350)]
            stand.append(v)
            teams[t * 0x2e8 + 0x29] = v[0]
            teams[t * 0x2e8 + 0x2b] = v[1]
            struct.pack_into('<HH', teams, t * 0x2e8 + 0x2c, v[2], v[3])
        for n_, _ in LEAGUE_BUFFERS:
            emu.write(bufs[n_], base[n_])
        files = {'TEAMS': teams, 'CARTEAMS': bytearray(base['CARTEAMS'])}
        before = {'TEAMS': bytes(teams)}
        n = rnd.choice((3, 5, 7, 7))
        emu.call(SCHEDULE_RANK_TEAMS, eax=order_buf, ebx=1)
        emu.write(pinfo, b'\0' * 0x400)
        emu.write(po, b'\xff' * 15 * 42)
        emu.call(PLAYOFF_MAKE_ROUND1, eax=order_buf, edx=po, ebx=1, ecx=n, stack=(pinfo + 0x20,))
        # some games played already
        played = []
        raw = bytearray(emu.read(po, 15 * 42))
        for s_ in range(8):
            wins = {}
            for g in range(rnd.randrange(n + 1)):
                b_ = s_ * 42 + g * 6
                if max(wins.values(), default=0) == n // 2 + 1:
                    break
                ha = rnd.randrange(8)
                aa = rnd.choice([x for x in range(8) if x != ha])
                raw[b_ + 4], raw[b_ + 5] = ha, aa
                w = raw[b_ + 2] if ha > aa else raw[b_ + 3]
                wins[w] = wins.get(w, 0) + 1
                played.append([s_, g, ha, aa])
        emu.write(po, bytes(raw))
        before['po'] = bytes(raw)
        seed = rnd.getrandbits(32)
        fwd = []
        for t in range(2):
            o = [0, 1, 2, 3, 0, 1, 2, 0, 1, 0]
            rnd.shuffle(o)
            fwd.append(o)
        dfn = [rnd.sample(range(3), 3) for _ in range(2)]
        for t in range(2):
            emu.write(FORWARD_LINE_ORDER + t * 40, struct.pack('<10i', *fwd[t]))
            emu.write(DEFENCE_PAIR_ORDER + t * 12, struct.pack('<3i', *dfn[t]))
        option_flags = rnd.choice((0, 0x400, 0x800, 0xc00)) | (n << 12)
        emu.write(OPTION_FLAGS, struct.pack('<I', option_flags))
        emu.call(SRAND, eax=seed)
        used['n'] = 0
        ret = emu.call(PLAYOFF_ROUND1_DONE, eax=po, edx=1, ebx=2, ecx=names, stack=(names,))
        # the rounds after it: each made from the winners, then played out
        steps = [emu.read(po, 15 * 42).hex()]
        flag = emu.alloc(b'\0' * 8)
        for name, addr in PLAYOFF_CHAIN:
            if name.startswith('make'):
                extra = (3,) if name == 'make_final' else ()
                if name == 'make_final':
                    # (it sorts the finalists by records it reads only for human teams: a computer
                    # team's is whatever the stack holds, zeros here)
                    emu.write(STACK_TOP - 0x2100, b'\0' * 0x2000)
                r_ = emu.call(addr, eax=po, edx=n, ebx=1, ecx=pinfo + 0x20, stack=extra + (flag,))
            else:
                r_ = emu.call(addr, eax=po, edx=1, ebx=2, ecx=names, stack=(names,))
            steps.append(emu.read(po, 15 * 42).hex())
            if r_ & 0xffffffff:
                break
        after = {n_: byte_diff(base[n_], emu.read(bufs[n_], len(base[n_]))) for n_, _ in LEAGUE_BUFFERS}
        after['TEAMS'] = byte_diff(before['TEAMS'], files['TEAMS'])
        after['CARTEAMS'] = byte_diff(base['CARTEAMS'], files['CARTEAMS'])
        cases.append({'standings': stand, 'n': n, 'played': played, 'seed': seed, 'fwd': fwd, 'def': dfn,
                      'option_flags': option_flags,
                      'after': dict(after, ret=s32(ret), po=emu.read(po, 15 * 42).hex(), steps=steps,
                                    rand=struct.unpack('<I', emu.read(emu.call(RAND_STATE) & 0xffffffff, 4))[0])})
    emu.write(OPTION_FLAGS, b'\0' * 4)
    return cases


SEASON_RECORD_RESULT = 0x3626d                 # a human team's game into the league: (dir, ext, team, side; game index, summary dir)
FILE_OPEN_READ = 0x14525                       # stubbed: (path, handle pointer) from the files of the case
FILE_OPEN_RW = 0x14552                         # stubbed
FILE_CLOSE = 0x1457c                           # stubbed: (handle pointer)
STARS = 0xe9af8                                # e9af8: the three stars, (team, roster) words


def record_cases(exe, gamedir, count=200):
    """season_record_result called directly: the game of a human team into TEAMS.DB (its season or
    play-off block), SEASON.DB (the stars, the skaters who dressed, the goalies who played with the
    goalie of record from GSUMMARY.DB, the goals against average and save percentage); the league
    files the game ships with the team's block and its players' records now and then random, the
    match (the score, the power plays, the penalty minutes, the line tables with scratches and
    goalies, the statistics, the stars) and a game summary of its goals (now and then missing some)"""
    emu = PortEmu(exe)
    rnd = random.Random(1097)
    base = {n: read(gamedir, n + '.DB') for n in ('TEAMS', 'KEY', 'SEASON')}
    files = {}
    handles = {}
    pos = {}

    def reg(r):
        return emu.uc.reg_read(r) & 0xffffffff

    def on_open(eax):
        path = bytes(emu.read(eax & 0xffffffff, 64)).split(b'\0')[0].decode('latin-1')
        name = path.replace('/', '\\').split('\\')[-1].split('.')[0].upper()
        h = 5 + len(handles)
        handles[h] = name
        pos[h] = 0
        emu.write(reg(UC_X86_REG_EDX), struct.pack('<i', h))
        return 0

    def on_close(eax):
        emu.write(eax & 0xffffffff, struct.pack('<i', -1))
        return 0

    def on_read(eax):
        h = eax & 0xffffffff
        f = files[handles[h]]
        buf, off, size = reg(UC_X86_REG_EDX), reg(UC_X86_REG_EBX), reg(UC_X86_REG_ECX)
        if off & 0x80000000:
            off = pos[h]
        if off + size > len(f):
            return 1
        emu.write(buf, bytes(f[off:off + size]))
        pos[h] = off + size
        return 0

    def on_write(eax):
        h = eax & 0xffffffff
        f = files[handles[h]]
        buf, off, size = reg(UC_X86_REG_EDX), reg(UC_X86_REG_EBX), reg(UC_X86_REG_ECX)
        if off & 0x80000000:
            off = pos[h]
        if off + size > len(f):
            return 1
        f[off:off + size] = emu.read(buf, size)
        pos[h] = off + size
        return 0
    emu.stub(FILE_OPEN_READ, on_open)
    emu.stub(FILE_OPEN_RW, on_open)
    emu.stub(FILE_CLOSE, on_close)
    emu.stub(FILE_READ, on_read)
    emu.stub(FILE_WRITE, on_write)
    strings = emu.alloc(b'L\0\0\0.DB\0G\0\0\0')
    teams_db, key_db = base['TEAMS'], base['KEY']
    cases = []
    for k in range(count):
        team = rnd.randrange(26)
        side = rnd.randrange(2)
        other = rnd.choice([x for x in range(26) if x != team])
        playoffs = rnd.random() < 0.3
        index = rnd.randrange(0x444, 0x4ad) if playoffs else rnd.randrange(0x444)
        tm = bytearray(base['TEAMS'])
        se = bytearray(base['SEASON'])
        rec = team * 0x2e8
        if rnd.random() < 0.3:
            b = rec + (0x3a if playoffs else 0x28)
            tm[b:b + 4] = bytes(rnd.choice((0, 0xff, rnd.randrange(256))) for _ in range(4))
            tm[b + 4:b + 0x12] = bytes(rnd.randrange(256) for _ in range(14))
        keys = [struct.unpack_from('<i', tm, rec + (0x4c + r * 4 if r < 25 else 0xb0 + (r - 25) * 4))[0] for r in range(28)]
        for r in range(28):
            if keys[r] < 0 or rnd.random() > 0.3:
                continue
            so = struct.unpack_from('<i', key_db, keys[r] + 0x2c)[0]
            n = 0x36 if key_db[keys[r] + 2] == 0x47 else 0x2f
            for w in range(0, n - 1, 2):
                struct.pack_into('<H', se, so + w, rnd.choice((0, 0, rnd.randrange(100), rnd.randrange(0x10000))))
        # the match
        hg = rnd.randrange(8)
        ag = rnd.choice((hg, rnd.randrange(8)))
        goals = (hg, ag)
        f = []
        for ti, t in enumerate(TEAM_RECORDS):
            tid = team if ti == side else other
            lt = bytearray(teams_db[tid * 0x2e8 + 0xbc:tid * 0x2e8 + 0xec])
            for c in range(0x28, 0x30):
                lt[c] = rnd.choice((0x64, 0x64, rnd.randrange(28), rnd.randrange(256)))
            for c in (0x24, 0x25):
                lt[c] = rnd.choice((lt[c], 25, 26, 27, rnd.randrange(25), 0x64))
            emu.write(LINE_TABLES[ti], bytes(lt))
            emu.write(t + 0xda, struct.pack('<I', LINE_TABLES[ti]))
            fi = {'goals': goals[ti], 'pp_goals': rnd.randrange(4), 'power_plays': rnd.randrange(8),
                  'penalty_minutes': rnd.randrange(40), 'goalie_request': rnd.choice((0, 1, 0xff00, 0xff01, 0x10)),
                  'line_table': list(lt)}
            emu.write(t + 0x10, struct.pack('<h', fi['goals']))
            emu.write(t + 2, struct.pack('<hh', fi['pp_goals'], fi['power_plays']))
            emu.write(t + 0xc, struct.pack('<h', fi['penalty_minutes']))
            emu.write(t + 0x38, struct.pack('<H', fi['goalie_request']))
            fi['stats'] = [[rnd.randrange(5), rnd.randrange(5), rnd.randrange(20), rnd.randrange(-4, 5), rnd.randrange(3),
                            rnd.randrange(2), rnd.randrange(2), rnd.randrange(11)] for _ in range(25)]
            emu.write(PLAYER_STATS[ti], b''.join(struct.pack('<8h', *st) for st in fi['stats']))
            fi['goalie_stats'] = [[rnd.choice((0, rnd.randrange(1, 4000))), rnd.randrange(50), rnd.randrange(9)] for _ in range(3)]
            emu.write(GOALIE_STATS[ti], b''.join(struct.pack('<3h', *gs) for gs in fi['goalie_stats']))
            f.append(fi)
        with_key = [r for r in range(28) if keys[r] >= 0]
        stars = [[rnd.randrange(2), rnd.choice(with_key)] for _ in range(3)]
        emu.write(STARS, b''.join(struct.pack('<hh', *st) for st in stars))
        # the game summary: the goals in some order (now and then one missing), penalties, injuries,
        # the periods' trailers, the goalies in the nets
        events = []
        for ti in range(2):
            for _ in range(goals[ti]):
                if rnd.random() < 0.05:
                    continue
                events.append([1, ti, rnd.randrange(25), 0xff, 0xff, rnd.choice((0, 2, 4)), rnd.randrange(4), rnd.randrange(20),
                               rnd.randrange(60), rnd.choice((25, 25, 26, 27, 0xff, rnd.randrange(256))),
                               rnd.choice((25, 25, 26, 27, 0xff, rnd.randrange(256)))])
        for _ in range(rnd.randrange(4)):
            events.append([rnd.choice((2, 3)), rnd.randrange(2)] + [rnd.randrange(256) for _ in range(9)])
        rnd.shuffle(events)
        for _ in range(rnd.randrange(3)):
            events.insert(rnd.randrange(len(events) + 1), [4] + [rnd.randrange(10) for _ in range(10)])
        events.append([4] + [rnd.randrange(10) for _ in range(10)])
        n = len(events)
        header = [0, rnd.randrange(1, 13), rnd.randrange(1, 29), 0, 1, n & 0xff, n >> 8, 0, 0, 0, 0]
        files = {'TEAMS': tm, 'KEY': bytearray(key_db), 'SEASON': se, 'GSUMMARY': bytearray(bytes(header) + b''.join(bytes(e) for e in events))}
        handles.clear()
        before = {'TEAMS': byte_diff(base['TEAMS'], tm), 'SEASON': byte_diff(base['SEASON'], se)}
        ret = emu.call(SEASON_RECORD_RESULT, eax=strings, edx=strings + 4, ebx=team, ecx=side, stack=(index, strings + 8))
        cases.append({'team': team, 'side': side, 'index': index, 'teams': f, 'stars': stars, 'summary': events,
                      'before': before,
                      'after': {'ret': s32(ret), 'TEAMS': byte_diff(base['TEAMS'], files['TEAMS']),
                                'SEASON': byte_diff(base['SEASON'], files['SEASON'])}})
    return cases


LEAGUE_PLAY_DAY = 0x41cc4                      # (dir, ext, game index, PINFO teams) + team (-1 all), mode: the league's games up to a date
PLAYOFF_TRIM_SERIES = 0x41f64                  # (SCHEDULE file, TEAMS file, game index): a decided series' games off the schedule
LOADFILE = 0x8e8a0                             # stubbed (cdecl): (path, flags) the file in memory
FILESIZE = 0x92de0                             # stubbed (cdecl): (path)
SAVEFILE = 0x932d0                             # stubbed (cdecl): (path, buffer, size)
AWARDS_SCREEN = 0x13320                        # stubbed: the season's awards (counted)
LEAGUE_DB_LOAD = 0x42295                       # (dir, random schedule): the new league's schedule, its teams' game lists
MESSAGE_DIALOG = 0x31013                       # stubbed: ("Shuffling the schedule"); 5 stack arguments
RESTORE_DIALOG_BACKGROUND = 0x30f12            # stubbed
DAY_FILES = ('TEAMS', 'CARTEAMS', 'KEY', 'CAREER', 'SEASON', 'SCHEDULE')


def file_hash(b):
    return hashlib.sha1(bytes(b)).hexdigest()


def day_cases(exe, gamedir):
    """whole seasons of a league: league_play_day (schedule_play_games with league_sim_game and
    schedule_write_record, schedule_screen with schedule_rank_teams and the play-off rounds,
    schedule_screen2 and playoff_advance) and playoff_trim_series called as league_calendar_flow
    and league_merge_check call them: each game of a human team gets a score, the games played or
    the decided series' games are updated, the day is played for its team (mode 2) and then for
    everybody (mode 7); with no human game left the league plays on to the end. The league files
    the game ships, one, two or no human teams, the play-off series lengths; after every call the
    TEAMS, SEASON and SCHEDULE files (SHA-1), the rand() state, the line orders and the awards"""
    emu = PortEmu(exe)
    rnd = random.Random(1101)
    base = {n: read(gamedir, n + '.DB') for n in DAY_FILES}
    files = {}
    handles = {}
    awards = {'n': 0}
    loaded = {n: emu.alloc(len(base[n]) + 0x100) for n in DAY_FILES}
    free = {}

    def reg(r):
        return emu.uc.reg_read(r) & 0xffffffff

    def arg(i):
        return struct.unpack('<I', emu.read(reg(UC_X86_REG_ESP) + 4 + 4 * i, 4))[0]

    def name_of(path):
        p_ = bytes(emu.read(path, 64)).split(b'\0')[0].decode('latin-1')
        return p_.replace('/', '\\').split('\\')[-1].split('.')[0].upper()

    def on_open(eax):
        h = 5 + len(handles)
        handles[h] = name_of(eax & 0xffffffff)
        emu.write(reg(UC_X86_REG_EDX), struct.pack('<i', h))
        return 0

    def on_close(eax):
        emu.write(eax & 0xffffffff, struct.pack('<i', -1))
        return 0

    def on_read(eax):
        f = files[handles[eax & 0xffffffff]]
        buf, off, size = reg(UC_X86_REG_EDX), reg(UC_X86_REG_EBX), reg(UC_X86_REG_ECX)
        if off + size > len(f):
            return 1
        emu.write(buf, bytes(f[off:off + size]))
        return 0

    def on_write(eax):
        f = files[handles[eax & 0xffffffff]]
        buf, off, size = reg(UC_X86_REG_EDX), reg(UC_X86_REG_EBX), reg(UC_X86_REG_ECX)
        if off + size > len(f):
            return 1
        f[off:off + size] = emu.read(buf, size)
        return 0

    def on_load(eax):
        n_ = name_of(arg(0))
        emu.write(loaded[n_], bytes(files[n_]))
        return loaded[n_]

    def on_size(eax):
        return len(files[name_of(arg(0))])

    def on_save(eax):
        n_ = name_of(arg(0))
        files[n_] = bytearray(emu.read(arg(1), arg(2)))
        return 0

    def on_alloc(eax):
        size = max(arg(1), 0x400)
        for p_, sz in list(free.items()):
            if sz >= size:
                del free[p_]
                emu.write(p_, b'\0' * sz)
                used[p_] = sz
                return p_
        p_ = emu.alloc(b'\0' * size)
        used[p_] = size
        return p_

    def on_free(eax):
        p_ = arg(0)
        if p_ in used:
            free[p_] = used.pop(p_)
        return 0
    used = {}
    emu.stub(FILE_OPEN_READ, on_open)
    emu.stub(FILE_OPEN_RW, on_open)
    emu.stub(FILE_CLOSE, on_close)
    emu.stub(FILE_READ, on_read)
    emu.stub(FILE_WRITE, on_write)
    emu.stub(LOADFILE, on_load)
    emu.stub(FILESIZE, on_size)
    emu.stub(SAVEFILE, on_save)
    emu.stub(ALLOCMEM, on_alloc)
    emu.stub(FREEMEM, on_free)
    emu.stub(AWARDS_SCREEN, lambda eax: awards.__setitem__('n', awards['n'] + 1))
    emu.stub(MESSAGE_DIALOG, lambda eax: 0, pop=0x14)
    emu.stub(RESTORE_DIALOG_BACKGROUND, lambda eax: 0)

    # playoff_make_final sorts the finalists by the records it reads only for human teams; a
    # computer team's is whatever the stack holds (heap pointers and frames of earlier calls in the
    # game): zeros here, as the port takes them
    def on_make_final(uc, address, size, user):
        esp = uc.reg_read(UC_X86_REG_ESP)
        uc.mem_write(esp + 4, b'\0' * 0x5d0)
    emu.uc.hook_add(UC_HOOK_CODE, on_make_final, None, 0x444dd, 0x444dd)
    strings = emu.alloc(b'L\0\0\0.DB\0\0')
    pinfo = emu.alloc(b'\0' * 28 * 0x1e)
    chains = []
    # (the human teams, the series length, a random schedule, the play-off rounds the human teams
    # win after winning every regular season game; None: random scores all along)
    for humans, length, random_schedule, rounds_won in (([5], 7, 1, None), ([3, 17], 5, 0, None), ([], 7, 1, None),
                                                         ([12], 3, 1, 4), ([0, 25], 7, 0, None), ([8], 7, 1, 0),
                                                         ([20, 21], 5, 0, 1), ([14], 7, 0, 2)):
        files = {n: bytearray(base[n]) for n in DAY_FILES}
        handles = {1: 'SCHEDULE', 2: 'TEAMS'}
        emu.write(pinfo, bytes(sum(([0] * 0x17 + [1 if t in humans else 0] + [0] * 6 for t in range(28)), [])))
        option_flags = (rnd.randrange(0x10000) & ~0x7000) | (length << 12)
        emu.write(OPTION_FLAGS, struct.pack('<I', option_flags))
        seed = rnd.getrandbits(32)
        emu.call(SRAND, eax=seed)
        # the new league (league_db_load: the play-off games cleared, a random schedule shuffled)
        ret = emu.call(LEAGUE_DB_LOAD, eax=strings, edx=random_schedule)
        assert ret == 0
        fwd = []
        for t in range(2):
            o = [0, 1, 2, 3, 0, 1, 2, 0, 1, 0]
            rnd.shuffle(o)
            fwd.append(o)
        dfn = [rnd.sample(range(3), 3) for _ in range(2)]
        for t in range(2):
            emu.write(FORWARD_LINE_ORDER + t * 40, struct.pack('<10i', *fwd[t]))
            emu.write(DEFENCE_PAIR_ORDER + t * 12, struct.pack('<3i', *dfn[t]))
        steps = []

        def game(i):
            return files['SCHEDULE'][2 + i * 6:8 + i * 6]

        def call(index, team, mode):
            awards['n'] = 0
            ret = emu.call(LEAGUE_PLAY_DAY, eax=strings, edx=strings + 4, ebx=index, ecx=pinfo, stack=(team, mode))
            return [index, team, mode, s32(ret), awards['n']]
        for _ in range(400):
            gp = struct.unpack_from('<H', files['SCHEDULE'], 0)[0]
            nxt = -1
            for i in range(0x4ad):
                r = game(i)
                if r[2] != 0xff and r[3] != 0xff and (r[2] in humans or r[3] in humans) and r[0] != 0xff \
                        and (r[4] == 0xff or r[5] == 0xff) and (i < 0x444 or r[1] != 0xff):
                    nxt = i
                    break
            step = {'pre': [], 'gp': -1, 'trim': -1, 'calls': []}
            if nxt >= 0:
                r = bytearray(game(nxt))
                a = rnd.randrange(8)
                b = rnd.choice([x for x in range(8) if x != a]) if nxt >= 0x444 else rnd.randrange(8)
                if rounds_won is not None:
                    rnd_ = 0 if nxt < 0x47c else 1 if nxt < 0x498 else 2 if nxt < 0x4a6 else 3
                    win = nxt < 0x444 or rnd_ < rounds_won
                    a, b = sorted((rnd.randrange(1, 8), rnd.randrange(8)), reverse=True)
                    if a == b:
                        a += 1
                    if (r[2] in humans) != win:
                        a, b = b, a
                r[4], r[5] = a, b
                files['SCHEDULE'][2 + nxt * 6:8 + nxt * 6] = r
                step['pre'] = [nxt, list(r)]
                if nxt < 0x444:
                    if gp < nxt + 1:
                        struct.pack_into('<H', files['SCHEDULE'], 0, nxt + 1)
                        step['gp'] = nxt + 1
                else:
                    step['trim'] = nxt
                    emu.call(PLAYOFF_TRIM_SERIES, eax=1, edx=2, ebx=nxt)
                team = r[2] if r[2] in humans else r[3]
                step['calls'].append(call(nxt if nxt < 0x444 else nxt - 1, team, 2))
                # the human teams' standings as season_record_result counts the game (golden-verified
                # on its own): games, wins / losses / ties, goals for and against
                step['standings'] = []
                for side_, t_ in ((0, r[2]), (1, r[3])):
                    if t_ in humans:
                        tm = files['TEAMS']
                        b_ = t_ * 0x2e8 + (0x3a if nxt >= 0x444 else 0x28)
                        mine, other = (a, b) if side_ == 0 else (b, a)
                        k_ = 1 if mine > other else 2 if mine < other else 3
                        tm[b_] = (tm[b_] + 1) & 0xff
                        tm[b_ + k_] = (tm[b_ + k_] + 1) & 0xff
                        g4, g6 = struct.unpack_from('<HH', tm, b_ + 4)
                        struct.pack_into('<HH', tm, b_ + 4, (g4 + mine) & 0xffff, (g6 + other) & 0xffff)
                        step['standings'].append([b_, bytes(tm[b_:b_ + 8]).hex()])
                gp = struct.unpack_from('<H', files['SCHEDULE'], 0)[0]
                step['calls'].append(call(gp if nxt < 0x444 else nxt, -1, 7))
            else:
                before = file_hash(files['SCHEDULE'])
                step['calls'].append(call(gp if gp else 1, -1, 7))
                if file_hash(files['SCHEDULE']) == before:
                    steps.append(dict(step, after=None))
                    break
            step['after'] = {'TEAMS': file_hash(files['TEAMS']), 'SEASON': file_hash(files['SEASON']),
                             'SCHEDULE': file_hash(files['SCHEDULE']),
                             'rand': struct.unpack('<I', emu.read(emu.call(RAND_STATE) & 0xffffffff, 4))[0],
                             'fwd': [list(struct.unpack('<10i', emu.read(FORWARD_LINE_ORDER + t * 40, 40))) for t in range(2)],
                             'dfn': [list(struct.unpack('<3i', emu.read(DEFENCE_PAIR_ORDER + t * 12, 12))) for t in range(2)]}
            steps.append(step)
        chains.append({'humans': humans, 'option_flags': option_flags, 'seed': seed, 'random': random_schedule, 'rounds_won': rounds_won,
                       'fwd': fwd, 'def': dfn, 'steps': steps,
                       'final': {n: byte_diff(base[n], files[n]) for n in ('TEAMS', 'SCHEDULE')}})
    emu.write(OPTION_FLAGS, b'\0' * 4)
    return chains


def main():
    if len(sys.argv) != 3:
        print(__doc__ or 'golden.py GAMEDIR OUTDIR')
        sys.exit(2)
    gamedir, outdir = sys.argv[1], sys.argv[2]
    exe = os.path.join(gamedir, 'HOCKEY.EXE')
    os.makedirs(outdir, exist_ok=True)
    for name, data in (('rng', rng_cases(exe)), ('fm_driver', fm_cases(exe, gamedir)),
                       ('pc_speaker', pc_cases(exe, gamedir)), ('physics', physics_cases(exe)),
                       ('league', {'league': league_cases(exe, gamedir), 'scores': scores_cases(exe),
                                   'playoffs': playoff_cases(exe, gamedir), 'rounds': round_cases(exe, gamedir),
                                   'records': record_cases(exe, gamedir), 'days': day_cases(exe, gamedir)})):
        write_golden(outdir, name, data)
    write_ai(outdir, ai_cases(exe))


if __name__ == '__main__':
    main()
