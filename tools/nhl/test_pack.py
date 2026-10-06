#!/usr/bin/env python3
#
# Checks the decoders of formats.py for every pack code of unpack(). The game files only use RefPack (10),
# byte pair (46, the .BGP drivers) and the VIV speech code, so the other codes are exercised with the test
# encoders below; with HOCKEY.EXE and the unicorn module the game's own decoders (refpack_decode,
# bitlz_decode, bytepair_decode, delta_decode, pack7a_decode) run in an emulator on the same buffers and
# their output is compared with formats.py. The same for the frame decoder of the CMV movies (no movie is
# part of the installation): synthetic movies through formats.CmvPlayer and the game's cmv_next_frame.
#
#   test_pack.py [GAMEDIR]          (GAMEDIR with HOCKEY.EXE and the data files, default re/nhl_hockey)
#
import os
import random
import struct
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
sys.path.insert(0, os.path.dirname(HERE))
import formats                        # noqa: E402

# ----------------------------------------------------------------------------------------------
# test encoders
# ----------------------------------------------------------------------------------------------

class BitWriter:
    def __init__(self):
        self.bits = []

    def put(self, value, n):
        for i in range(n - 1, -1, -1):
            self.bits.append((value >> i) & 1)

    def gamma(self, v):
        k = 0
        while v > (1 << (k + 3)) - 5:
            k += 1
        self.put(0, k)
        self.put(1, 1)
        self.put(v - (1 << (k + 2)) + 4, k + 2)

    def bytes(self):
        bits = self.bits + [0] * (-len(self.bits) % 8)
        return bytes(int(''.join(map(str, bits[i:i + 8])), 2) for i in range(0, len(bits), 8))

def _huffman_lengths(freq, maxlen=16):
    '''code lengths of a complete Huffman code (at most maxlen bits)'''
    import heapq
    f = dict(freq)
    while True:
        heap = [(n, i, (s,)) for i, (s, n) in enumerate(sorted(f.items()))]
        heapq.heapify(heap)
        depth = {s: 0 for s in f}
        uid = len(heap)
        while len(heap) > 1:
            n1, _, a = heapq.heappop(heap)
            n2, _, b = heapq.heappop(heap)
            for s in a + b:
                depth[s] += 1
            heapq.heappush(heap, (n1 + n2, uid, a + b))
            uid += 1
        if max(depth.values()) <= maxlen:
            return depth
        f = {s: n // 2 + 1 for s, n in f.items()}

def huff_compress(data, code=0x30, run_min=3):
    '''an encoder for bitlz_decode: pack codes 30/31 plain, 32 running sum, 34 double running sum'''
    if code & 0xfe == 0x32:
        stored, prev = bytearray(), 0
        for b in data:
            stored.append((b - prev) & 0xff)
            prev = b
    elif code & 0xfe == 0x34:
        stored, pb, pa = bytearray(), 0, 0
        for b in data:
            a = (b - pb) & 0xff
            stored.append((a - pa) & 0xff)
            pb, pa = b, a
    else:
        stored = bytearray(data)
    counts = [0] * 256
    for b in stored:
        counts[b] += 1
    esc = min(range(256), key=lambda v: (counts[v], v))
    tokens = []
    i = 0
    while i < len(stored):
        b = stored[i]
        if b == esc:
            tokens.append(('lit', b))
            i += 1
            continue
        tokens.append(('sym', b))
        j = i + 1
        while j < len(stored) and stored[j] == b:
            j += 1
        if j - i - 1 >= run_min:
            tokens.append(('run', j - i - 1))
            i = j
        else:
            i += 1
    freq = {}
    for t, v in tokens:
        if t == 'sym':
            freq[v] = freq.get(v, 0) + 1
    freq[esc] = sum(1 for t, _ in tokens if t != 'sym') + 1
    if len(freq) == 1:
        freq[(esc + 1) & 0xff] = 1
    length = _huffman_lengths(freq)
    order = sorted(freq, key=lambda s: (length[s], s))
    maxlen = max(length.values())
    codes = {}
    c = 0
    count = [0] * (maxlen + 1)
    for s in order:
        count[length[s]] += 1
    k = 0
    for L in range(1, maxlen + 1):
        c <<= 1
        for _ in range(count[L]):
            codes[order[k]] = (c, L)
            c += 1
            k += 1
    bw = BitWriter()
    bw.put(len(data), 24)
    bw.put(esc, 8)
    for L in range(1, maxlen + 1):
        bw.gamma(count[L])
    used = [False] * 256
    v = 0xff
    for s in order:
        n = 0
        while True:
            v = (v + 1) & 0xff
            if not used[v]:
                n += 1
            if v == s:
                break
        used[s] = True
        bw.gamma(n - 1)

    def sym(s):
        cv, L = codes[s]
        bw.put(cv, L)
    for t, val in tokens:
        if t == 'sym':
            sym(val)
        elif t == 'run':
            sym(esc)
            bw.gamma(val)
        else:
            sym(esc)
            bw.gamma(0)
            bw.put(0, 1)
            bw.put(val, 8)
    sym(esc)
    bw.gamma(0)
    bw.put(1, 1)
    body = bw.bytes()
    head = bytes([code, 0xfb])
    if code & 1:
        head += (len(body) + 5).to_bytes(3, 'big')
    return head + body + bytes(4)

def rle7a_compress(data, unit=1, nbytes=1, code=0x7a):
    '''an encoder for pack7a_decode'''
    if len(data) % unit:
        data = data + bytes(unit - len(data) % unit)
    units = [data[i:i + unit] for i in range(0, len(data), unit)]
    pmax = (1 << (8 * nbytes - 1)) - 1
    out = bytearray([code, 0xfb])
    if code & 1:
        out += bytes(3)
    out += len(data).to_bytes(3, 'big') + bytes([unit, nbytes])
    lits = []

    def flush():
        while lits:
            chunk = lits[:pmax + 1]
            del lits[:pmax + 1]
            out.extend((-len(chunk)).to_bytes(nbytes, 'big', signed=True))
            for u in chunk:
                out.extend(u)
    i = 0
    while i < len(units):
        j = i + 1
        while j < len(units) and units[j] == units[i] and j - i <= pmax:
            j += 1
        if j - i >= 2:
            flush()
            out.extend((j - i - 1).to_bytes(nbytes, 'big', signed=True))
            out.extend(units[i])
            i = j
        else:
            lits.append(units[i])
            i += 1
    flush()
    out.extend(bytes(nbytes))
    return bytes(out)

def delta_compress(data, code=0x60):
    out = bytearray([code, 0xfb]) + bytes({0x62: 3, 0x66: 4}.get(code, 0)) + len(data).to_bytes(3, 'big')
    prev = 0
    for b in data:
        out.append((b - prev) & 0xff)
        prev = b
    return bytes(out)

def cmv_movie(width, height, frames, rate=15, palette=()):
    '''a CMV movie: MVIh, the frames (raw pixels or (ops, data) of cmv_decode_frame), MVIe'''
    def chunk(tag, body):
        return tag + struct.pack('<I', len(body) + 8) + body
    out = chunk(b'MVIh', bytes(2) + struct.pack('<7H', len(frames), width, height, 4, rate, 0, len(palette)) +
                bytes(c for rgb in palette for c in rgb))
    for f in frames:
        if isinstance(f, tuple):
            out += chunk(b'MVIf', struct.pack('<H', 1) + f[0] + f[1])
        else:
            out += chunk(b'MVIf', struct.pack('<H', 0) + f)
    return out + chunk(b'MVIe', b'')

def cmv_random_frame(rnd, width, height):
    '''ops and data of a frame with every kind of block; the vectors stay inside the frame'''
    ops, data = bytearray(), bytearray()

    def vector(o):
        while True:
            mv = rnd.randrange(255)
            off = ((mv & 15) - 7) + ((mv >> 4) - 7) * width
            if 0 <= o + off and o + off + 3 * width + 4 <= width * height:
                return mv
    for by in range(0, height, 4):
        for bx in range(0, width, 4):
            o = by * width + bx
            kind = rnd.randrange(3)
            if kind == 0:
                ops.append(vector(o))
            elif kind == 1:
                ops.append(0xff)
                data.append(vector(o))
            else:
                ops.append(0xff)
                data += bytes([0xff] + [rnd.randrange(256) for _ in range(16)])
    return bytes(ops), bytes(data)

# ----------------------------------------------------------------------------------------------

def samples(gamedir):
    rnd = random.Random(1994)
    yield 'empty', b''
    yield 'one byte', b'A'
    yield 'run', b'\x00' * 3000
    yield 'text', open(os.path.join(HERE, 'formats.py'), 'rb').read()[:20000]
    yield 'random', bytes(rnd.randrange(256) for _ in range(5000))
    yield 'skewed', bytes(min(255, int(rnd.expovariate(0.05))) for _ in range(8000))
    yield 'ramp', bytes((i * 3) & 0xff for i in range(6000))
    yield 'wave', bytes(int(128 + 100 * __import__('math').sin(i / 9.0)) & 0xff for i in range(6000))
    if gamedir:
        for n in ('TEAMS.DB', 'RINK.PAL', 'PAUSE.IFF'):
            p = os.path.join(gamedir, n)
            if os.path.exists(p):
                yield n, open(p, 'rb').read()[:30000]

def main():
    gamedir = sys.argv[1] if len(sys.argv) > 1 else os.path.join(HERE, '..', '..', 're', 'nhl_hockey')
    exe = os.path.join(gamedir, 'HOCKEY.EXE')
    emu = None
    try:
        from leemu import LEEmu
        if os.path.exists(exe):
            emu = LEEmu(exe)
    except RuntimeError as e:
        print('no emulator:', e)
    J = None
    if emu:
        import json
        J = {r['name']: r['addr'] for r in json.load(open(os.path.join(gamedir, 'hockey.json')))['routines']}
    failures = 0

    def game_decode(routine, packed, size, flag=None):
        emu.free_all()
        src = emu.alloc(packed + bytes(16))
        dst = emu.alloc(size + 64)
        kw = {'ebx': flag} if flag is not None else {}
        emu.call(J[routine], eax=src, edx=dst, **kw)
        return emu.read(dst, size)

    def check(name, packed, data, routine=None, flag=None):
        nonlocal failures
        got = formats.unpack(packed)
        ok = got == data
        game = ''
        if emu and routine:
            g = game_decode(routine, packed, len(data), flag)
            game = ' game decoder ' + ('agrees' if g == data else 'DIFFERS')
            ok = ok and g == data
        if not ok:
            failures += 1
        print(f'{"ok  " if ok else "FAIL"} {name}: {len(data)} -> {len(packed)} bytes{game}')

    for label, data in samples(gamedir):
        for code in (0x30, 0x31, 0x32, 0x34):
            if not data and code != 0x30:
                continue
            check(f'huff {code:02x} {label}', huff_compress(data, code), data, 'bitlz_decode', 1)
        for unit, nb in ((1, 1), (2, 1), (1, 2), (4, 3)):
            if len(data) % unit:
                continue
            check(f'7a unit {unit} count {nb} {label}', rle7a_compress(data, unit, nb), data, 'pack7a_decode')
        check(f'delta {label}', delta_compress(data), data, 'delta_decode')
        check(f'delta 66 {label}', delta_compress(data, 0x66), data, 'delta_decode')
    # the game files: RefPack banks and the byte pair coded drivers
    if gamedir:
        for n in ('RINK.QFS', 'EADESK0.QFS', 'SCRBRD2.QFS', 'SB30.BGP', 'YM30.BGP', 'MT30.BGP', 'PC30.BGP'):
            p = os.path.join(gamedir, n)
            if not os.path.exists(p):
                continue
            packed = open(p, 'rb').read()
            data = formats.unpack(packed)
            routine = 'bytepair_decode' if packed[0] & 0xfe == 0x46 else 'refpack_decode'
            if emu:
                g = game_decode(routine, packed, len(data), 1 if routine == 'refpack_decode' else None)
                ok = g == data
            else:
                ok = len(data) > 0
            failures += not ok
            print(f'{"ok  " if ok else "FAIL"} {n}: {len(packed)} -> {len(data)} bytes' +
                  (f' ({routine} agrees)' if emu and ok else ''))
    # CMV movies: formats.CmvPlayer and the game's cmv_next_frame / cmv_decode_frame on the same frames
    rnd = random.Random(1995)
    for w, h, n in ((32, 24, 8), (64, 48, 6), (228, 176, 3)):
        frames = [bytes(rnd.randrange(256) for _ in range(w * h))]
        frames += [cmv_random_frame(rnd, w, h) for _ in range(n - 1)]
        frames.insert(3, bytes(rnd.randrange(256) for _ in range(w * h)))
        movie = cmv_movie(w, h, frames)
        player = formats.CmvPlayer(movie)
        got = player.decode()
        ok = len(got) == len(frames) and player.header['width'] == w
        game = ''
        if emu:
            emu.free_all()
            # the cmv object of cmv_load_palette with three windows of windowdefp: +0x20 stride,
            # +0x28 the row offsets (row 0 at +0x10 of the shape), +0x2c the shape
            rows = emu.alloc(struct.pack('<I', 0x10))
            wins = []
            for _ in range(3):
                shape = emu.alloc(0x10 + w * h)
                win = emu.alloc(0x40)
                emu.write(win + 0x20, struct.pack('<I', w))
                emu.write(win + 0x28, struct.pack('<II', rows, shape))
                wins.append(win)
            table = [((i & 15) - 7) + ((i >> 4) - 7) * w for i in range(256)]
            cmv = emu.alloc(struct.pack('<11I', len(frames), w, h, 15, 4, 0, 0, 0, *wins) +
                            struct.pack('<256i', *table))
            agree = True
            for (tag, c), mine in zip([x for x in formats.read_cmv_chunks(movie) if x[0] == 'MVIf'], got):
                addr = emu.alloc(c + bytes(32))
                shape = emu.call(J['cmv_next_frame'], eax=cmv, edx=addr)
                agree = agree and emu.read(shape + 0x10, w * h) == mine
            game = ' cmv_next_frame ' + ('agrees' if agree else 'DIFFERS')
            ok = ok and agree
        failures += not ok
        print(f'{"ok  " if ok else "FAIL"} cmv {w}x{h}: {len(frames)} frames, {len(movie)} bytes{game}')
    print(f'{failures} failures' + ('' if emu else ' (without the emulator check)'))
    return 1 if failures else 0

if __name__ == '__main__':
    sys.exit(main())
