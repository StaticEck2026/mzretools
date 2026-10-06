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
    '''Pack codes 0x60/0x62/0x66: running byte sum ("delta") encoding (delta_decode)'''
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

def unpack(data):
    '''Mirror of the game's unpack(): returns the decompressed buffer, or the input itself when it
    is not compressed. Pack codes 0x30-0x34 (bit-coded LZ), 0x46 (byte pair) and 0x7a are not
    implemented.'''
    code = pack_code(data)
    if code is None:
        return data
    if code == 0x10:
        return refpack_decompress(data)
    if code in (0x60, 0x62, 0x66):
        return delta_decompress(data)
    if code in (0x6a, 0x6e):
        size = (data[2] << 16) | (data[3] << 8) | data[4]
        return bytes(data[5:5 + size])
    if code in (0x30, 0x32, 0x34, 0x46, 0x7a):
        raise PackError(f"pack code 0x{code:02x} not implemented")
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
    def __init__(self, rate, pcm8_signed):
        self.rate = rate
        self.pcm = pcm8_signed   # bytes, signed 8 bit

def load_sample(data):
    if data[:4] == b'FORM' and data[8:12] == b'8SVX':
        pos = 12
        rate = 8000
        body = b''
        while pos + 8 <= len(data):
            cid = data[pos:pos + 4]
            size, = struct.unpack_from('>I', data, pos + 4)
            payload = data[pos + 8: pos + 8 + size]
            if cid == b'VHDR':
                rate = struct.unpack_from('>H', payload, 12)[0]
            elif cid == b'BODY':
                body = payload
            pos += 8 + size + (size & 1)
        return Sample(rate, body)
    if data[:4] == b'RIFF':
        # the game only handles 8 bit mono PCM with a 0x2c byte header, converting to signed
        rate, = struct.unpack_from('<I', data, 24)
        pcm = bytes(b ^ 0x80 for b in data[0x2c:])
        return Sample(rate, pcm)
    raise ValueError("unknown sample format")

def write_wav(path, sample):
    pcm = bytes(b ^ 0x80 for b in sample.pcm)   # back to unsigned for WAV
    hdr = b'RIFF' + struct.pack('<I', 36 + len(pcm)) + b'WAVEfmt ' + struct.pack('<IHHIIHH', 16, 1, 1, sample.rate, sample.rate, 1, 8)
    with open(path, 'wb') as f:
        f.write(hdr + b'data' + struct.pack('<I', len(pcm)) + pcm)

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
    '''A speech clip as a Sample: raw entries are unsigned 8 bit at 5512 Hz, packed ones (0x47 0xFB)
    unpack to a 5 byte header and a running sum of signed 8 bit samples at 11025 Hz.'''
    raw = data[off:off + size]
    if raw[0:2] == b'\x47\xfb':
        un = bytepair_decode(raw)
        acc = 0
        pcm = bytearray()
        for b in un[5:]:
            acc = (acc + b) & 0xff
            pcm.append(acc)
        return Sample(11025, bytes(pcm))
    return Sample(5512, bytes(b ^ 0x80 for b in raw))

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
