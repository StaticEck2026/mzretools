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
#                    (collide_net, collide_player_net, net_push_off; score_goal, queue_infraction stubbed)
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
SEED = 0xc9100                                # dword_c9100, the state of randomrange
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
        '''Replaces the routine at addr: fn(eax) is called instead and the routine returns'''
        def hook(uc, address, size, user):
            fn(uc.reg_read(UC_X86_REG_EAX))
            sp = uc.reg_read(UC_X86_REG_ESP)
            uc.reg_write(UC_X86_REG_EIP, struct.unpack('<I', uc.mem_read(sp, 4))[0])
            uc.reg_write(UC_X86_REG_ESP, sp + 4)
        self.uc.hook_add(UC_HOOK_CODE, hook, None, addr, addr)


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
                 ('frame', 0x12, -2), ('speed', 0x18, -2), ('line_slot', 0x1a, -2), ('push_x', 0x30, -2),
                 ('push_y', 0x32, -2), ('heading', 0x34, -4), ('spin', 0x36, 1), ('anim', 0x38, -2),
                 ('anim_pos', 0x3a, -2), ('anim_hold', 0x3c, -2), ('flags', 0x44, 1), ('flags2', 0x45, 1),
                 ('roster', 0x47, 1), ('flags4', 0x55, 1), ('weight', 0x56, 1), ('speed_skill', 0x57, 1),
                 ('stamina', 0x58, 1), ('endurance', 0x61, 1))
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
_FMT = {1: 'B', -1: 'b', 2: 'H', -2: 'h', 4: 'I', -4: 'i'}


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
    emu.stub(PLAY_SFX, lambda eax: sfx.append(eax & 0xffff))
    emu.stub(SCORE_GOAL, lambda eax: goals.append((eax - ENTITIES) // 0x80))
    emu.stub(QUEUE_INFRACTION, lambda eax: infractions.append([(eax - ENTITIES) // 0x80,
                                                               emu.uc.reg_read(UC_X86_REG_EDX) & 0xff]))
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
