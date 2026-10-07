#!/usr/bin/env python3
#
# Readers for the asset formats of EA Sports NHL Hockey (DOS, 1994), derived from the loaders in
# HOCKEY.EXE (see re/nhl_hockey/FORMATS.md for the routine each format was taken from).
#
#   RefPack       EA's LZ77 variant with the 10FB/11FB signature (unpack @0x97eb8, refpack_decode)
#   SHPI          shape banks: .fsh/.qfs/.PPV/.iff screens (loadshapes, locateshape, drawshape)
#   VFN           bitmap fonts (setfont, printstr)
#   8SVX / WAV    sound samples (loadsound)
#   VIV           announcer speech bank index (speech_load_bank)
#   TIL/MAP       rink tiles (load_rink, load_rink_tiles)
#
# No external dependencies; PNG files are written with a small built-in encoder.
#
import struct
import zlib

# ----------------------------------------------------------------------------------------------
# RefPack and the other pack codes handled by unpack()
# ----------------------------------------------------------------------------------------------

class PackError(Exception):
    pass

def pack_code(data):
    '''Pack code of an EA compressed buffer (the first byte with bit 0 cleared) or None'''
    if len(data) < 5 or data[1] != 0xfb:
        return None
    return data[0] & 0xfe

def refpack_decompress(data):
    '''Standard EA RefPack (10FB / 11FB). Returns the decompressed bytes.'''
    if len(data) < 5:
        raise PackError("buffer too short")
    hdr = (data[0] << 8) | data[1]
    pos = 2
    if hdr & 0x100:        # compressed size present
        pos += 3
    size = (data[pos] << 16) | (data[pos + 1] << 8) | data[pos + 2]
    pos += 3
    out = bytearray()
    n = len(data)
    while pos < n:
        b = data[pos]; pos += 1
        if b < 0x80:
            b2 = data[pos]; pos += 1
            lit = b & 3
            copy = ((b & 0x1c) >> 2) + 3
            off = ((b & 0x60) << 3) + b2 + 1
        elif b < 0xc0:
            b2 = data[pos]; b3 = data[pos + 1]; pos += 2
            lit = b2 >> 6
            copy = (b & 0x3f) + 4
            off = ((b2 & 0x3f) << 8) + b3 + 1
        elif b < 0xe0:
            b2 = data[pos]; b3 = data[pos + 1]; b4 = data[pos + 2]; pos += 3
            lit = b & 3
            copy = ((b & 0x0c) << 6) + b4 + 5
            off = ((b & 0x10) << 12) + (b2 << 8) + b3 + 1
        elif b < 0xfc:
            lit = ((b & 0x1f) + 1) * 4
            copy = 0
            off = 0
        else:
            lit = b & 3
            copy = 0
            off = 0
        if lit:
            out += data[pos:pos + lit]
            pos += lit
        if copy:
            if off > len(out):
                raise PackError("bad back reference")
            start = len(out) - off
            for i in range(copy):
                out.append(out[start + i])
        if b >= 0xfc:
            break
    if size and len(out) < size:
        raise PackError(f"size mismatch: header {size}, got {len(out)}")
    if size and len(out) > size:
        # a few banks (EADESK0, the JER*.QFS jerseys...) carry up to three bytes of padding
        # behind the last code; the game's unpack() only ever writes `size` bytes
        del out[size:]
    return bytes(out)

def delta_decompress(data):
    '''Pack codes 0x60/0x62/0x66/0x72: running byte sum ("delta") encoding (delta_decode): the code, 3 more
    bytes after 62FB, 4 after 66FB, the unpacked size (24 bit BE), then one byte per output byte'''
    hdr = (data[0] << 8) | data[1]
    pos = 2
    if hdr == 0x62fb:
        pos = 5
    elif hdr == 0x66fb:
        pos = 6
    size = (data[pos] << 16) | (data[pos + 1] << 8) | data[pos + 2]
    pos += 3
    out = bytearray(size)
    acc = 0
    for i in range(size):
        acc = (acc + data[pos + i]) & 0xff
        out[i] = acc
    return bytes(out)

class _BitReader:
    '''The bit reader of bitlz_decode (bitlz_getbits): most significant bit first from a 32 bit
    buffer that is refilled whenever fewer than 16 bits are left'''
    def __init__(self, data, pos):
        self.d = data
        self.p = pos
        self.buf = 0
        self.count = 0
        self.bits(0)

    def _byte(self):
        b = self.d[self.p] if self.p < len(self.d) else 0
        self.p += 1
        return b

    def bits(self, n):
        if n > 16:
            hi = self.bits(n - 16)
            return (hi << 16) | self.bits(16)
        v = self.buf >> (32 - n) if n else 0
        self.buf = (self.buf << n) & 0xffffffff
        self.count -= n
        if self.count < 16:
            shift = 24 - self.count
            while True:
                self.buf |= self._byte() << shift
                shift -= 8
                self.count += 8
                if shift <= 8:
                    break
        return v

    def gamma(self):
        '''bitlz_getgamma: k zero bits and a one, then k + 2 bits r: r + 2^(k+2) - 4'''
        top, n = 2, 1
        while True:
            top *= 2
            n += 1
            if self.bits(1):
                break
        return self.bits(n) + top - 4

def huff_decompress(data):
    '''Pack codes 0x30/0x32/0x34 (bitlz_decode 0x97740): EA's canonical Huffman code with an escape symbol.
    The code (31FB etc. with 3 more bytes), then a bit stream: 24 bits the unpacked size, 8 bits the escape
    byte; per code length 1, 2, ... a gamma coded number of codes until the code space is full; the symbols
    in code order, each as a gamma coded step to the next unused byte value. The data: a symbol is output
    unless it is the escape, which is followed by a gamma coded run length (the last byte repeated) or 0,
    then 1 bit: 0 = an 8 bit literal follows, 1 = the end. 32FB stores the result as a running sum, 34FB as
    a running sum of a running sum.'''
    hdr = (data[0] << 8) | data[1]
    pos = 5 if hdr & 0x100 else 2
    hdr &= ~0x100
    br = _BitReader(data, pos)
    size = br.bits(24)
    esc = br.bits(8)
    base = [0] * 18
    limit = [0] * 18
    code = 0
    nsym = 0
    length = 0
    shift = 15
    while True:
        length += 1
        if length > 16:
            raise PackError('bad Huffman table')
        code *= 2
        base[length] = code - nsym
        n = br.gamma()
        nsym += n
        code += n
        lim = (code << shift) & 0xffff if n else 0
        limit[length] = lim
        shift -= 1
        if n != 0 and lim == 0:
            break
    maxlen = length
    used = [False] * 256
    syms = []
    v = 0xff
    for _ in range(nsym):
        k = br.gamma() + 1
        while k:
            v = (v + 1) & 0xff
            if not used[v]:
                k -= 1
        used[v] = True
        syms.append(v)
    out = bytearray()
    while True:
        top = br.buf >> 16
        length = 1
        while length < maxlen and top >= limit[length]:
            length += 1
        sym = syms[br.bits(length) - base[length]]
        if sym != esc:
            out.append(sym)
            continue
        run = br.gamma()
        if run:
            out += bytes([out[-1]]) * run
            continue
        if br.bits(1):
            break
        out.append(br.bits(8))
    del out[size:]
    if hdr == 0x32fb:
        acc = 0
        for i in range(len(out)):
            acc = (acc + out[i]) & 0xff
            out[i] = acc
    elif hdr == 0x34fb:
        a = b = 0
        for i in range(len(out)):
            a = (a + out[i]) & 0xff
            b = (b + a) & 0xff
            out[i] = b
    return bytes(out)

def rle7a_decompress(data):
    '''Pack code 0x7a (pack7a_decode 0x97c2c): run length code of fixed size units. The code (7BFB with 3
    more bytes), the unpacked size (24 bit BE), the unit size in bytes, the size of a count (1..4 bytes,
    big endian, signed); then counts: n > 0 repeats the next unit n + 1 times, n < 0 copies -n units,
    0 ends.'''
    pos = 5 if data[0] & 1 else 2
    size = int.from_bytes(data[pos:pos + 3], 'big')
    unit = data[pos + 3]
    nbytes = data[pos + 4]
    pos += 5
    out = bytearray()
    while True:
        n = int.from_bytes(data[pos:pos + nbytes], 'big', signed=True)
        pos += nbytes
        if n < 0:
            out += data[pos:pos - n * unit]
            pos += -n * unit
        elif n > 0:
            out += data[pos:pos + unit] * (n + 1)
            pos += unit
        else:
            break
    return bytes(out[:size]) if len(out) > size else bytes(out)

def skip_copyright(data):
    '''skip_copyright: a buffer may start with a "Copyright..." C string before its pack code'''
    if data[:9] == b'Copyright':
        return data.index(b'\0') + 1
    return 0

def unpack(data):
    '''Mirror of the game's unpack(): returns the decompressed buffer, or the input itself when it is not
    compressed'''
    skip = skip_copyright(data)
    if skip:
        data = data[skip:]
    code = pack_code(data)
    if code is None:
        return data
    if code == 0x10:
        return refpack_decompress(data)
    if code in (0x30, 0x32, 0x34):
        return huff_decompress(data)
    if code == 0x46:
        return bytepair_decode(data)
    if code in (0x60, 0x62, 0x66, 0x72):
        return delta_decompress(data)
    if code in (0x6a, 0x6e):
        size = (data[2] << 16) | (data[3] << 8) | data[4]
        return bytes(data[5:5 + size])
    if code == 0x7a:
        return rle7a_decompress(data)
    return data

# ----------------------------------------------------------------------------------------------
# SHPI shape banks
# ----------------------------------------------------------------------------------------------

def rle_decode(raw, count):
    '''Pixel stream of the sprite frames (blit_sprite -> blit_rle_frame): a count byte c followed by
    c > 0: one colour byte repeated c times (0xff = c transparent pixels, the blitter skips them),
    c >= 0x80 (negative): -c literal colour bytes, c == 0: end of the frame.'''
    out = bytearray()
    i = 0
    n = len(raw)
    while i < n and len(out) < count:
        c = raw[i]
        i += 1
        if c == 0:
            break
        if c < 0x80:
            out += bytes([raw[i]]) * c
            i += 1
        else:
            k = 0x100 - c
            out += raw[i:i + k]
            i += k
    if len(out) < count:
        out += b'\xff' * (count - len(out))
    return bytes(out[:count])

class Shape:
    '''One entry of an SHPI bank.
    code: EA image code (0x7b = 8 bpp indexed, 0x2d/0x2a/0x24 = palettes, others unsupported)
    width/height, center (hotspot) and pos as stored in the header, pixels = bytes for 8 bpp'''
    def __init__(self, name, data, offset):
        self.name = name
        self.offset = offset
        hdr = data[offset:offset + 16]
        self.code = hdr[0]
        self.block_size = hdr[1] | (hdr[2] << 8) | (hdr[3] << 16)
        (self.width, self.height, self.center_x, self.center_y,
         xpos, ypos) = struct.unpack_from('<6H', hdr, 4)
        self.x = xpos & 0x0fff
        self.y = ypos & 0x0fff
        self.flags = (xpos >> 12) | ((ypos >> 12) << 4)
        self.transparent = 0
        if self.code & 0x80:
            # sprite frames (.PPV, codes 0xfb/0x80/0x81): run length coded pixels, see rle_decode();
            # the three bytes after the code are not a block size for these
            self.block_size = 0
        self.raw = data[offset + 16: offset + 16 + max(self.block_size - 16, 0)] if self.block_size else data[offset + 16:]
        self.pixels = None
        self.palette = None
        if self.code & 0x80:
            self.pixels = rle_decode(self.raw, self.width * self.height)
            self.transparent = 0xff
        elif self.code == 0x7b:
            self.pixels = self.raw[:self.width * self.height]
        elif self.code in (0x2d, 0x2a, 0x24, 0x29, 0x22, 0x2f) or self.name.lower().endswith('pal'):
            self.palette = decode_palette(self.raw, self.code, self.width or 256)

    def __repr__(self):
        return f"Shape({self.name!r}, code=0x{self.code:02x}, {self.width}x{self.height}, center=({self.center_x},{self.center_y}), pos=({self.x},{self.y}))"

def decode_palette(raw, code, count=256):
    '''Returns a list of (r, g, b) 8-bit tuples. The game copies 0x300 bytes from the entry data and
    sends them straight to the VGA DAC (setpalette), so the stored values are 6 bit per channel.'''
    pal = []
    if code == 0x2a:          # 32 bit RGBA
        for i in range(count):
            r, g, b, a = raw[i * 4: i * 4 + 4]
            pal.append((r, g, b))
        return pal
    if code == 0x29:          # 16 bit 565
        for i in range(count):
            v = raw[i * 2] | (raw[i * 2 + 1] << 8)
            pal.append((((v >> 11) & 31) * 255 // 31, ((v >> 5) & 63) * 255 // 63, (v & 31) * 255 // 31))
        return pal
    # 24 bit (0x2d / 0x24 and the '!pal' entries used by the game)
    for i in range(count):
        if i * 3 + 2 >= len(raw):
            break
        pal.append(tuple(raw[i * 3: i * 3 + 3]))
    if pal and max(max(c) for c in pal) <= 63:
        pal = [(r * 255 // 63, g * 255 // 63, b * 255 // 63) for r, g, b in pal]
    return pal

class ShapeBank:
    '''An SHPI directory: 'SHPI', u32 file size, u32 entry count, 4 char directory id, then
    (4 char name, u32 offset) entries from 0x10 (shapecount/getshape/locateshape).'''
    def __init__(self, data):
        data = unpack(bytes(data))
        if data[:4] != b'SHPI':
            raise ValueError("not an SHPI bank")
        self.data = data
        self.size, self.count = struct.unpack_from('<II', data, 4)
        self.dir_id = data[12:16].decode('latin-1')
        self.entries = []
        for i in range(self.count):
            name = data[16 + i * 8: 20 + i * 8].decode('latin-1')
            off, = struct.unpack_from('<I', data, 20 + i * 8)
            self.entries.append((name, off))
        self.shapes = [Shape(n, data, o) for n, o in self.entries]

    def find(self, name):
        '''locateshape(): first entry whose 4 character tag matches (case sensitive, padded)'''
        name = (name + '    ')[:4]
        for s in self.shapes:
            if s.name == name:
                return s
        return None

    def palette(self):
        for s in self.shapes:
            if s.palette:
                return s.palette
        return None

# ----------------------------------------------------------------------------------------------
# Game palette and jersey colours (load_team_palettes, blit_sprite)
# ----------------------------------------------------------------------------------------------

def game_palette(gamedir, home, away):
    '''Palette of the match screen as built by load_team_palettes(): RINKPAL.QFS '!pal' gives
    entries 0..0x7f and 0xfb..0xff, HOMEPALS.BIN[home] the 64 home jersey colours at 0x80..0xbf and
    AWAYPALS.BIN[away] the away colours at 0xc0..0xff (0x1c0 bytes per team: 0xc0 palette bytes
    followed by a 256 byte colour remap table). Returns (palette as (r, g, b) tuples, remap_home,
    remap_away); the away remap adds 0x40 to its entries 0x90..0xff so both tables point into their
    own block. blit_sprite() pushes every sprite pixel through the remap table of the team.'''
    import os
    def rd(name):
        for n in (name, name.lower()):
            p = os.path.join(gamedir, n)
            if os.path.exists(p):
                with open(p, 'rb') as f:
                    return f.read()
        raise FileNotFoundError(name)
    rp = ShapeBank(rd('RINKPAL.QFS')).find('!pal').raw[:0x300]
    hp = rd('HOMEPALS.BIN')[home * 0x1c0:(home + 1) * 0x1c0]
    ap = rd('AWAYPALS.BIN')[away * 0x1c0:(away + 1) * 0x1c0]
    pal = bytearray(rp)
    pal[0x180:0x240] = hp[:0xc0]
    pal[0x240:0x300] = ap[:0xc0]
    pal[0x2f1:0x300] = rp[0x2f1:0x300]
    remap_home = bytearray(hp[0xc0:0x1c0])
    remap_away = bytearray(ap[0xc0:0x1c0])
    for i in range(0x90, 0x100):
        remap_away[i] = (remap_away[i] + 0x40) & 0xff
    colors = [(pal[i * 3] * 255 // 63, pal[i * 3 + 1] * 255 // 63, pal[i * 3 + 2] * 255 // 63) for i in range(256)]
    return colors, bytes(remap_home), bytes(remap_away)

def mirrored_remap(remap):
    '''blit_sprite() swaps the entries 0xc0 + 16k + {0, 1, 3, 4} of the remap table ([0] <-> [4],
    [1] <-> [3]) while a mirrored frame is drawn (the shading of the left/right side of the jersey).'''
    r = bytearray(remap)
    for k in range(4):
        b = 0xc0 + 16 * k
        r[b], r[b + 4] = r[b + 4], r[b]
        r[b + 1], r[b + 3] = r[b + 3], r[b + 1]
    return bytes(r)

# ----------------------------------------------------------------------------------------------
# Sound effects of the digital driver (PCFF001.PAT / .TIM / .DIG)
# ----------------------------------------------------------------------------------------------

def read_ea_bank(data):
    '''The keyed bank layout of the .TIM and .DIG files: u32 file size (.TIM) or u16 0x7ff1 / u16 4
    (.DIG), u16 n at +4, n 4 byte keys from +6, n u32 offsets relative to the data at 6 + 8 n.
    Returns [(key bytes, data bytes)] (the last key of a .TIM is 0xffffffff).'''
    n = struct.unpack_from('<H', data, 4)[0]
    base = 6 + 8 * n
    offs = [struct.unpack_from('<I', data, 6 + 4 * n + 4 * k)[0] for k in range(n)]
    out = []
    for k in range(n):
        start = base + offs[k]
        end = base + offs[k + 1] if k + 1 < n and offs[k + 1] > offs[k] else len(data)
        out.append((data[6 + 4 * k: 10 + 4 * k], data[start:end]))
    return out

class SoundBank:
    '''The sound effects played by play_sfx() -> snd_play_patch (0x8f4c4): the sound id selects a
    record of the patch file (PCFF001.PAT: +2 a 256 byte id -> record map, records of 0x14 bytes
    from +0x102). Record: +0 type (1 digital, 0 FM instrument), +1 timbre program, +7 s8 transpose,
    +0xe note length (x 6 ticks of 100 Hz, 0 = 0xa0 ticks). The timbres (PCFF001.TIM, read_ea_bank,
    keys 0x80 type 0 program) of the digital type are 32 bytes: +0 6, +2 the 4 byte id of the
    sample in PCFF001.DIG (whose keys are those ids), +0x14 u32 length, +0x18 / +0x1c loop start /
    end (0 = none). The Sound Blaster driver mixes at 11025 Hz and steps through a sample by the
    note (unity at note 60): a sample plays at 11025 * 2^(transpose / 12) Hz, whatever rate its
    timbre names (load_timbre_file overwrites +0x12 with 11025).'''
    PAT_RECORDS = 0x102
    MIX_RATE = 11025

    def __init__(self, pat, tim, dig):
        self.pat = pat
        self.samples = {key: smp for key, smp in read_ea_bank(dig)}
        self.timbres = {}
        for key, rec in read_ea_bank(tim):
            if key[0] == 0x80 and key[1] == 1 and len(rec) >= 0x20:
                length, loop_start, loop_end = struct.unpack_from('<III', rec, 0x14)
                self.timbres[(key[2] << 8) | key[3]] = {'id': rec[2:6], 'length': length, 'loop': (loop_start, loop_end)}

    def record(self, sound_id):
        idx = self.pat[2 + sound_id]
        if idx == 0 and sound_id != 0:
            return None
        return self.pat[self.PAT_RECORDS + idx * 0x14: self.PAT_RECORDS + (idx + 1) * 0x14]

    def effect(self, sound_id):
        '''Returns dict(pcm (signed 8 bit), rate, loop, length) for a digital sound id, None for
        the FM ones'''
        r = self.record(sound_id)
        if not r or r[0] != 1 or r[1] not in self.timbres:
            return None
        t = self.timbres[r[1]]
        pcm = self.samples.get(t['id'])
        if pcm is None:
            return None
        if 0 < t['length'] < len(pcm):
            pcm = pcm[:t['length']]
        transpose = struct.unpack('b', bytes([r[7]]))[0]
        rate = int(round(self.MIX_RATE * 2 ** (transpose / 12.0)))
        return {'pcm': pcm, 'rate': rate, 'loop': t['loop'] if t['loop'][1] else None,
                'timbre': r[1], 'sample': t['id'].hex(), 'transpose': transpose,
                'length': (r[14] * 6 if r[14] else 0xa0) / 100.0}

    def effect_ids(self):
        return [i for i in range(256) if self.effect(i)]

def read_kms(kms, cfg=b''):
    '''A song of the music driver (music_load_kms): +1 tempo (0.4 * tempo steps a second), +6 track
    count, +8 u16 track offsets; per track the CFG holds 16 bytes from +8 (u16 MIDI channel mask,
    +6 volume, +7 pan). Returns dict(tempo, tracks=[dict(offset, mask, volume, pan, events)]) with
    events (delta, code, a, b): code < 0xd9 a note (low 7 bits, + 24 at the driver; a velocity,
    b length in steps), 0xdc program a, 0xdd tempo a, 0xdf controller a value b, 0xe5 pitch bend b,
    0xe7 text, 0xd9 end, 0xdb loop to the start.'''
    tempo, n = kms[1], kms[6]
    tracks = []
    for t in range(n):
        off = struct.unpack_from('<H', kms, 8 + 2 * t)[0]
        mask, vol, pan = 0xffff, 0x64, 0x40
        if len(cfg) >= 8 + 16 * t + 8:
            mask = struct.unpack_from('<H', cfg, 8 + 16 * t)[0]
            vol, pan = cfg[8 + 16 * t + 6], cfg[8 + 16 * t + 7]
        events = []
        p = off
        while p < len(kms):
            delta = 0
            while True:
                c = kms[p]; p += 1
                delta = delta * 128 + (c & 0x7f)
                if not c & 0x80:
                    break
            code = kms[p]; p += 1
            a = b = 0
            if code < 0xd9:
                a = kms[p]; p += 1
                while True:
                    c = kms[p]; p += 1
                    b = b * 128 + (c & 0x7f)
                    if not c & 0x80:
                        break
            elif code in (0xd9, 0xda, 0xdb, 0xe3):
                pass
            elif code == 0xdf:
                a, b = kms[p], kms[p + 1]; p += 2
            elif code == 0xe5:
                b = struct.unpack_from('<H', kms, p)[0]; p += 2
            elif code == 0xe6:
                a = kms[p]; b = struct.unpack_from('<I', kms, p + 1)[0]; p += 5
            elif code in (0xe7, 0xe8):
                a = kms[p]; b = bytes(kms[p + 1: p + 1 + a]); p += 1 + a
            else:
                a = kms[p]; p += 1
            events.append((delta, code, a, b))
            if code in (0xd9, 0xda, 0xdb):
                break
        tracks.append({'offset': off, 'mask': mask, 'volume': vol, 'pan': pan, 'events': events})
    return {'tempo': tempo, 'tracks': tracks}

def write_wav_pcm8(path, pcm_signed, rate):
    '''Writes signed 8 bit mono PCM as an (unsigned) 8 bit WAV file'''
    data = bytes((b + 0x80) & 0xff for b in pcm_signed)
    with open(path, 'wb') as f:
        f.write(b'RIFF' + struct.pack('<I', 36 + len(data)) + b'WAVEfmt ' +
                struct.pack('<IHHIIHH', 16, 1, 1, rate, rate, 1, 8) + b'data' + struct.pack('<I', len(data)) + data)

# ----------------------------------------------------------------------------------------------
# VFN fonts
# ----------------------------------------------------------------------------------------------

class Font:
    '''Bitmap font as read by setfont()/printstr():
      +0   4 byte tag, tag[3] is an ASCII digit giving the bits per pixel ('1' is the only one
           handled by this reader); the tag 'MTNF' marks a font whose glyphs are shapes
      +4   first char, +5 last char, +6 default glyph width, +7 glyph height, +8 extra advance
      +0x12 u16 offset of the per character width table (0 = use the default width)
      +0x14 u16 offset of the per character height table, +0x16 advance table
      +0x18 u16 x offset table, +0x1a y offset table
      +0x1c u32 offset of the glyph bitmaps
      +0x20 u32 per character offsets of the glyph bitmaps (relative to +0x1c), 1 bpp rows'''
    def __init__(self, data):
        self.data = data
        self.tag = data[:4].decode('latin-1')
        self.bpp = int(self.tag[3]) if self.tag[3].isdigit() else None
        self.first, self.last, self.def_width, self.height, self.spacing = struct.unpack_from('<5B', data, 4)
        self.width_tab, = struct.unpack_from('<H', data, 0x12)
        self.height_tab, self.adv_tab, self.xoff_tab, self.yoff_tab = struct.unpack_from('<4H', data, 0x14)
        self.glyph_base, = struct.unpack_from('<I', data, 0x1c)
        if self.glyph_base >= len(data):    # +0x1c holds a tag ('FNTX', 'FNED'): the offsets are absolute
            self.glyph_base = 0
        n = self.last - self.first + 1
        self.glyph_offsets = struct.unpack_from(f'<{n}I', data, 0x20)

    def glyph_width(self, ch):
        i = ord(ch) - self.first
        if self.width_tab:
            return self.data[self.width_tab + i]
        return self.def_width

    def glyph_height(self, ch):
        i = ord(ch) - self.first
        if self.height_tab:
            return self.data[self.height_tab + i]
        return self.height

    def advance(self, ch):
        i = ord(ch) - self.first
        if self.adv_tab:
            return self.data[self.adv_tab + i]
        return self.glyph_width(ch) + self.spacing

    def glyph(self, ch):
        '''Returns the glyph as a list of rows of 0/1 values (1 bpp fonts only)'''
        if self.bpp != 1:
            raise ValueError("only 1 bpp fonts are supported")
        i = ord(ch) - self.first
        if not (0 <= i <= self.last - self.first):
            return []
        off = self.glyph_base + self.glyph_offsets[i]
        w, h = self.glyph_width(ch), self.glyph_height(ch)
        stride = (w + 7) >> 3
        rows = []
        for y in range(h):
            row = self.data[off + y * stride: off + (y + 1) * stride]
            rows.append([(row[x >> 3] >> (7 - (x & 7))) & 1 if (x >> 3) < len(row) else 0 for x in range(w)])
        return rows

# ----------------------------------------------------------------------------------------------
# Sound: IFF 8SVX and RIFF WAV (loadsound)
# ----------------------------------------------------------------------------------------------

class Sample:
    def __init__(self, rate, pcm8_signed, loop_start=None, loop_end=None):
        self.rate = rate
        self.pcm = pcm8_signed   # bytes, signed 8 bit
        self.loop_start = loop_start    # sample positions of the repeated part (None: plays once)
        self.loop_end = loop_end

# The menu loops (MAINDESK.IFF, PAUSE.IFF, TONIGHTS.IFF, GAMESUM.IFF, SCOUTING.IFF) store their 8SVX BODY in a
# 4 bit delta code: every byte holds two codes, the low nibble first, each adding one of these steps to an
# 8 bit accumulator that starts at 0 (signed samples). It is the Fibonacci delta code of 8SVX without the
# zero step, so silence is +1 / -1 (0x78). playsample hands every loadsound sample to the driver with the
# packed flag and half of each length; the software mixer of the Sound Blaster driver expands two samples
# per byte through the table at 0xd7414 (mix_fill_buffer, mix_play_sample), the GUS driver the same way.
FIB_DELTA = (-34, -21, -13, -8, -5, -3, -2, -1, 1, 2, 3, 5, 8, 13, 21, 34)

def fibdelta_decode(packed, acc=0):
    '''4 bit delta code of the menu loops -> signed 8 bit samples (two per byte, low nibble first)'''
    out = bytearray(2 * len(packed))
    i = 0
    for b in packed:
        acc = (acc + FIB_DELTA[b & 15]) & 0xff
        out[i] = acc
        acc = (acc + FIB_DELTA[b >> 4]) & 0xff
        out[i + 1] = acc
        i += 2
    return bytes(out)

def load_sample(data, packed=None):
    '''A sound file as loadsound reads it. 8SVX: VHDR +0 one shot samples, +4 repeat samples, +12 rate;
    the BODY holds the samples (signed 8 bit) or, packed, half as many bytes in the 4 bit delta code
    (packed=None: decided by the VHDR sample count being twice the stored body).'''
    if data[:4] == b'FORM' and data[8:12] == b'8SVX':
        pos = 12
        rate = 8000
        oneshot = repeat = 0
        body = b''
        while pos + 8 <= len(data):
            cid = data[pos:pos + 4]
            size, = struct.unpack_from('>I', data, pos + 4)
            payload = data[pos + 8: pos + 8 + size]
            if cid == b'VHDR':
                oneshot, repeat = struct.unpack_from('>II', payload, 0)
                rate = struct.unpack_from('>H', payload, 12)[0]
            elif cid == b'BODY':
                body = payload
            pos += 8 + size + (size & 1)
        total = oneshot + repeat
        if packed is None:
            packed = total > 0 and abs(total - 2 * len(body)) <= 2
        pcm = fibdelta_decode(body) if packed else body
        if repeat:
            return Sample(rate, pcm, oneshot, min(total, len(pcm)))
        return Sample(rate, pcm)
    if data[:4] == b'RIFF':
        # the game only handles 8 bit mono PCM with a 0x2c byte header, converting to signed
        rate, = struct.unpack_from('<I', data, 24)
        pcm = bytes(b ^ 0x80 for b in data[0x2c:])
        return Sample(rate, pcm)
    raise ValueError("unknown sample format")

def write_wav(path, sample):
    '''8 bit WAV; the loop of a repeated sample goes into a "smpl" chunk'''
    pcm = bytes(b ^ 0x80 for b in sample.pcm)   # back to unsigned for WAV
    body = b'WAVEfmt ' + struct.pack('<IHHIIHH', 16, 1, 1, sample.rate, sample.rate, 1, 8)
    body += b'data' + struct.pack('<I', len(pcm)) + pcm + (b'\0' if len(pcm) & 1 else b'')
    if getattr(sample, 'loop_start', None) is not None:
        smpl = struct.pack('<9I', 0, 0, 1000000000 // sample.rate, 60, 0, 0, 0, 1, 0)
        smpl += struct.pack('<6I', 0, 0, sample.loop_start, sample.loop_end - 1, 0, 0)
        body += b'smpl' + struct.pack('<I', len(smpl)) + smpl
    with open(path, 'wb') as f:
        f.write(b'RIFF' + struct.pack('<I', len(body)) + body)

# ----------------------------------------------------------------------------------------------
# VIV speech bank (speech_load_bank @0x83897, speech_delta_decode, bytepair_decode @0x97a38) - verified
# ----------------------------------------------------------------------------------------------

def read_viv_index(data):
    '''EA 0xC0FB archive: u16 BE 0xC0FB, u16 BE index size, u16 BE entry count, then per entry a
    24 bit BE offset, a 24 bit BE size (read_be32 reads three bytes) and a zero terminated name.
    Returns [(name, offset, size)] (XBRUCE2.VIV stores 8 of its .int names twice).'''
    magic, hsize, count = struct.unpack_from('>3H', data, 0)
    if magic != 0xc0fb:
        raise ValueError('not a C0FB archive')
    pos = 6
    out = []
    for _ in range(count):
        off = int.from_bytes(data[pos:pos + 3], 'big')
        size = int.from_bytes(data[pos + 3:pos + 6], 'big')
        pos += 6
        end = data.index(b'\0', pos)
        out.append((data[pos:end].decode('latin-1'), off, size))
        pos = end + 1
    return out

def bytepair_decode(src):
    '''Pack code 0x46/0x47 (unpack -> bytepair_decode): 0x47 0xFB, 3 bytes, the unpacked size (24 bit
    BE), the escape byte, the number of pairs, the pairs (code, left, right); then the data: a
    pair code expands recursively, the escape byte is followed by a literal (0 ends the data).'''
    q = 5 if src[0:2] == b'\x47\xfb' else 2
    total = int.from_bytes(src[q:q + 3], 'big')
    flag = [0] * 256
    left = [0] * 256
    right = [0] * 256
    flag[src[q + 3]] = 1
    r = q + 5
    for _ in range(src[q + 4]):
        c = src[r]
        left[c], right[c], flag[c] = src[r + 1], src[r + 2], 0xff
        r += 3
    out = bytearray()
    while r < len(src) and len(out) < total:
        b = src[r]
        r += 1
        if flag[b] == 0:
            out.append(b)
        elif flag[b] == 0xff:
            stack = [b]
            while stack:
                c = stack.pop()
                if flag[c] == 0xff:
                    stack += [right[c], left[c]]
                else:
                    out.append(c)
        else:
            lit = src[r]
            r += 1
            if lit == 0:
                break
            out.append(lit)
    return bytes(out)

def viv_clip(data, off, size):
    '''A speech clip as a Sample at 11025 Hz: the entries without a pack code hold the 4 bit
    Fibonacci delta code of the menu recordings (two samples a byte; speech_timer plays them with the
    mixer's packed flag), packed ones (0x47 0xFB) unpack to a 5 byte header and a running sum of
    signed 8 bit samples.'''
    raw = data[off:off + size]
    if raw[0:2] == b'\x47\xfb':
        un = bytepair_decode(raw)
        acc = 0
        pcm = bytearray()
        for b in un[5:]:
            acc = (acc + b) & 0xff
            pcm.append(acc)
        return Sample(11025, bytes(pcm))
    return Sample(11025, fibdelta_decode(raw))

# ----------------------------------------------------------------------------------------------
# Rink tiles (.til) and tile map (.map)
# ----------------------------------------------------------------------------------------------

def render_tile_map(til, mapdata):
    '''til: 64 byte 8x8 tiles, 0xff = transparent. mapdata: u16 width, u16 height, u16 reserved,
    then width*height u16 cells: bits 0-9 tile index, 0x2000 flip x, 0x4000 flip y.
    Returns (width_px, height_px, pixels) with 0xff where nothing was drawn.'''
    w, h = struct.unpack_from('<2H', mapdata, 0)
    cells = struct.unpack_from(f'<{w * h}H', mapdata, 6)
    W, H = w * 8, h * 8
    img = bytearray(b'\xff' * (W * H))
    for cy in range(h):
        for cx in range(w):
            c = cells[cy * w + cx]
            t = (c & 0x3ff) * 64
            tile = til[t:t + 64]
            if len(tile) < 64:
                continue
            for y in range(8):
                sy = 7 - y if c & 0x4000 else y
                for x in range(8):
                    sx = 7 - x if c & 0x2000 else x
                    p = tile[sy * 8 + sx]
                    if p != 0xff:
                        img[(cy * 8 + y) * W + cx * 8 + x] = p
    return W, H, bytes(img)

# ----------------------------------------------------------------------------------------------
# PNG output
# ----------------------------------------------------------------------------------------------

def place_tile_map(surface, width, til, mapdata, col, row, mirrored=False):
    '''load_rink_tiles(): draws the 8x8 tiles of a .MAP onto an 8 bit surface at tile (col, row);
    with mirrored=True the map is placed right to left / bottom to top with every tile flipped
    (the 0x6000 placement of the second logo half of some teams).'''
    w, h = struct.unpack_from('<HH', mapdata, 0)
    for ty in range(h):
        for tx in range(w):
            c, = struct.unpack_from('<H', mapdata, 6 + (ty * w + tx) * 2)
            t = (c & 0x3ff) * 64
            fx = bool(c & 0x2000) ^ mirrored
            fy = bool(c & 0x4000) ^ mirrored
            cx = col - tx if mirrored else col + tx
            cy = row - ty if mirrored else row + ty
            for yy in range(8):
                for xx in range(8):
                    p = til[t + (7 - yy if fy else yy) * 8 + (7 - xx if fx else xx)]
                    if p != 0xff:
                        surface[(cy * 8 + yy) * width + cx * 8 + xx] = p

def write_png(path, width, height, pixels, palette=None, transparent=None):
    '''Writes an 8 bit indexed PNG (palette = list of (r,g,b)) or an RGB PNG when palette is None
    and pixels holds 3 bytes per pixel. transparent = palette index to make fully transparent.'''
    def chunk(tag, payload):
        c = tag + payload
        return struct.pack('>I', len(payload)) + c + struct.pack('>I', zlib.crc32(c) & 0xffffffff)
    if palette is not None:
        color_type, bpp = 3, 1
        pal = palette + [(0, 0, 0)] * (256 - len(palette))
        plte = b''.join(bytes(c[:3]) for c in pal[:256])
        extra = chunk(b'PLTE', plte)
        if transparent is not None:
            trns = bytearray(b'\xff' * 256)
            trns[transparent] = 0
            extra += chunk(b'tRNS', bytes(trns))
    else:
        color_type, bpp = 2, 3
        extra = b''
    raw = bytearray()
    stride = width * bpp
    for y in range(height):
        raw.append(0)
        raw += pixels[y * stride:(y + 1) * stride]
    ihdr = struct.pack('>IIBBBBB', width, height, 8, color_type, 0, 0, 0)
    with open(path, 'wb') as f:
        f.write(b'\x89PNG\r\n\x1a\n' + chunk(b'IHDR', ihdr) + extra + chunk(b'IDAT', zlib.compress(bytes(raw), 9)) + chunk(b'IEND', b''))

# ----------------------------------------------------------------------------------------------
# League files: schedule, game summary, configuration (verified against SCHEDULE.DB, LSSCHED.DB,
# GSUMMARY.DB and NHL.CFG of the installation)
# ----------------------------------------------------------------------------------------------

def team_abbreviations(teams_db):
    '''the abbreviations of the 28 records of TEAMS.DB (0x2e8 bytes each, +0 five characters)'''
    return [teams_db[i:i + 5].split(b'\0')[0].decode('latin-1').strip()
            for i in range(0, len(teams_db) - 0x2e7, 0x2e8)]

SCHEDULE_GAMES = 1092          # 26 teams x 84 games / 2 (league_calendar_flow plays games 0..0x443)
SCHEDULE_PLAYOFF_GAMES = 105    # the play-off slots from offset 0x199a (schedule_screen, playoff_make_*)

def read_schedule(data):
    '''schedule.db / LSSCHED.DB: u16 the number of games played (league_calendar_flow), then 6 byte
    games (db_read_record2, schedule_write_record): month, day, home team, away team, home goals, away
    goals (0xff = not played). Records 0..1091 are the season, 1092.. the play-offs: 15 series of 7 game
    slots (8 first round series, 4, 2, the final), all 0xff for the games a series did not need
    (LSSCHED.DB holds the 90 games of the '93-'94 play-offs).'''
    played = struct.unpack_from('<H', data, 0)[0]
    games = [tuple(data[p:p + 6]) for p in range(2, len(data) - 5, 6)]
    return played, games

GSUMMARY_GOAL, GSUMMARY_PENALTY, GSUMMARY_INJURY = 1, 2, 3

def read_gsummary(data):
    '''gsummary.db, the events of the game being played (begin_game_session, gsummary_*): an 11 byte
    header (+1 month, +2 day of a league game, 0 otherwise, +3 home team, +4 away team, +5 u16 records
    written), 11 byte events, and an 11 byte trailer
    rewritten behind each new event (+1 home goals, +2 home shots, +3 away goals, +4 away shots).
    Events (announce_goal, record_penalty, announce_injury):
      1 goal:    team, scorer, assist 1, assist 2 (0xff none), flags (2 short-handed, 4 power play),
                 period, minutes, seconds, the goalie in the scorer's net, the goalie beaten
      2 penalty: team, player, infraction (0 = first of the penalty names), severity, period, minutes, seconds
      3 injury:  team, player, injury, period, minutes, seconds
    Players are roster indices of the team (0..27), times are elapsed in the period.'''
    if len(data) < 22:
        raise ValueError('gsummary.db too short')
    head = data[:11]
    header = {'month': head[1], 'day': head[2], 'home': head[3], 'away': head[4],
              'records': struct.unpack_from('<H', head, 5)[0]}
    tail = data[-11:]
    trailer = {'state': tail[0], 'home_goals': tail[1], 'home_shots': tail[2], 'away_goals': tail[3],
               'away_shots': tail[4]}
    events = []
    for p in range(11, len(data) - 11, 11):
        r = data[p:p + 11]
        if r[0] == GSUMMARY_GOAL:
            events.append({'type': 'goal', 'team': r[1], 'scorer': r[2],
                           'assists': [a for a in (r[3], r[4]) if a != 0xff],
                           'short_handed': bool(r[5] & 2), 'power_play': bool(r[5] & 4),
                           'period': r[6], 'time': (r[7], r[8]), 'goalies': (r[9], r[10])})
        elif r[0] == GSUMMARY_PENALTY:
            events.append({'type': 'penalty', 'team': r[1], 'player': r[2], 'infraction': r[3],
                           'severity': r[4], 'period': r[5], 'time': (r[6], r[7])})
        elif r[0] == GSUMMARY_INJURY:
            events.append({'type': 'injury', 'team': r[1], 'player': r[2], 'injury': r[3],
                           'period': r[4], 'time': (r[5], r[6])})
        else:
            events.append({'type': r[0], 'raw': bytes(r)})
    return header, events, trailer

SOUND_CARDS = ('none', 'PC speaker', 'AdLib', 'Sound Blaster', 'Roland MT-32', 'Gravis UltraSound')

def read_nhl_cfg(text):
    '''NHL.CFG (load_nhl_cfg, load_cfg_palette, load_sound_config): line 1 the sound card ("%04x", an
    index into the table at 0xd243a: none, PC speaker, AdLib, Sound Blaster, MT-32, UltraSound; the game
    rewrites it when the card changes), line 2 the CD drive letter (ALLFILES.TXT is read from there), then
    the files installed on the hard disk; every other file of ALLFILES.TXT is read from the CD.'''
    lines = [l.strip() for l in text.splitlines() if l.strip()]
    card = int(lines[0], 16)
    return {'sound_card': card, 'sound_card_name': SOUND_CARDS[card] if card < len(SOUND_CARDS) else '?',
            'cd_drive': lines[1] if len(lines) > 1 else '', 'installed': lines[2:]}

# ----------------------------------------------------------------------------------------------
# CMV movies (TITLE.CMV, the coach clips clipNNNN.cmv): ea_sports_intro, cmv_play, cmv_* and the
# chunk streamer iff_parse; no movie is part of the installation, the frame decoder is checked against
# the game's cmv_decode_frame in an emulator (tools/nhl/test_pack.py)
# ----------------------------------------------------------------------------------------------

def read_cmv_chunks(data):
    '''the chunks of a movie: 4 character tag, u32 LE size including the 8 byte header (iff_parse; a tag
    starting with a digit 1..8 goes to a secondary stream). Returns [(tag, chunk bytes)]'''
    out = []
    pos = 0
    while pos + 8 <= len(data):
        tag = data[pos:pos + 4]
        size = struct.unpack_from('<I', data, pos + 4)[0]
        if size < 8:
            break
        out.append((tag.decode('latin-1'), data[pos:pos + size]))
        pos += size
    return out

def read_cmv_header(chunk):
    '''MVIh (cmv_load_palette; the field names are those of the library's mvi_print_info): +10 frames,
    +12 width, +14 height, +16 block size, +18 frame rate (frames per second), +20 first colour, +22
    colours, +24 the palette (8 bit RGB, shifted to 6 bits for the DAC)'''
    f = struct.unpack_from('<7H', chunk, 10)
    n = f[6]
    return {'frames': f[0], 'width': f[1], 'height': f[2], 'block': f[3], 'rate': f[4], 'first_colour': f[5],
            'colours': n, 'palette': [tuple(chunk[24 + 3 * i: 27 + 3 * i]) for i in range(n)]}

def cmv_decode_frame(ops, data, prev, prev2, width, height):
    '''cmv_decode_frame: one op byte per 4x4 block (row by row): op != 0xff copies the block of the previous
    frame displaced by ((op & 15) - 7, (op >> 4) - 7); 0xff takes the next byte b of the data stream: b !=
    0xff copies from the frame before the previous one displaced the same way, 0xff is followed by 16
    literal pixels (4 rows of 4)'''
    cur = bytearray(width * height)

    def block(src, a):
        # 4 bytes from a; the game reads past the frame there (a vector pointing outside), here zeros
        if 0 <= a and a + 4 <= len(src):
            return src[a:a + 4]
        return bytes(src[i] if 0 <= i < len(src) else 0 for i in range(a, a + 4))
    d = 0
    k = 0
    for by in range(0, height, 4):
        for bx in range(0, width, 4):
            op = ops[k]
            k += 1
            if op != 0xff:
                src, mv = prev, op
            else:
                b = data[d]
                d += 1
                if b == 0xff:
                    for r in range(4):
                        o = (by + r) * width + bx
                        cur[o:o + 4] = block(data, d)
                        d += 4
                    continue
                src, mv = prev2, b
            off = ((mv & 15) - 7) + ((mv >> 4) - 7) * width
            for r in range(4):
                o = (by + r) * width + bx
                cur[o:o + 4] = block(src, o + off)
    return bytes(cur), d

class CmvPlayer:
    '''decodes the frames of a movie: MVIh header (palette, size; starts a segment), MVIf frames (+8 u16 0 =
    raw pixels from +10, else the ops of the blocks from +10 followed by the data stream), MVIe end of a
    segment; three frames rotate (cmv_next_frame). The players stop at another tag; chunks of the secondary
    streams (tag "1".."8") never reach them'''
    def __init__(self, data):
        self.chunks = read_cmv_chunks(data)
        self.header = None
        self.frames = []
        self.segments = 0

    def decode(self):
        prev = prev2 = None
        for tag, c in self.chunks:
            if '1' <= tag[0] <= '8':
                continue
            if tag == 'MVIh':
                self.header = read_cmv_header(c)
                w, h = self.header['width'], self.header['height']
                prev = prev2 = bytes(w * h)
            elif tag == 'MVIf' and self.header:
                w, h = self.header['width'], self.header['height']
                if struct.unpack_from('<H', c, 8)[0] == 0:
                    cur = bytes(c[10:10 + w * h])
                else:
                    nops = (w // 4) * (h // 4)
                    cur, _ = cmv_decode_frame(c[10:10 + nops], c[10 + nops:], prev, prev2, w, h)
                prev2, prev = prev, cur
                self.frames.append(cur)
            elif tag == 'MVIe':
                self.segments += 1
            else:
                break
        return self.frames
