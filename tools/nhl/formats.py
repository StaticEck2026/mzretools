#!/usr/bin/env python3
#
# Readers for the asset formats of EA Sports NHL Hockey (DOS, 1994), derived from the loaders in
# HOCKEY.EXE (see re/nhl_hockey/FORMATS.md for the routine each format was taken from).
#
#   RefPack       EA's LZ77 variant with the 10FB/11FB signature (unpack @0x97eb8, sub_97ce0)
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
    if size and len(out) != size:
        raise PackError(f"size mismatch: header {size}, got {len(out)}")
    return bytes(out)

def delta_decompress(data):
    '''Pack codes 0x60/0x62/0x66: running byte sum ("delta") encoding (sub_97bb8)'''
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
        self.raw = data[offset + 16: offset + 16 + max(self.block_size - 16, 0)] if self.block_size else data[offset + 16:]
        self.pixels = None
        self.palette = None
        if self.code == 0x7b:
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
# VIV speech bank index (speech_load_bank @0x83897) - layout partially verified
# ----------------------------------------------------------------------------------------------

def read_viv_index(data):
    '''Header: three big endian u16 values (unknown, entry count, unknown), followed by one entry
    per clip: u32 BE offset, u32 BE size, zero terminated name. Returns [(name, offset, size)].'''
    v0, count, v2 = struct.unpack_from('>3H', data, 0)
    pos = 6
    out = []
    for _ in range(count):
        off, size = struct.unpack_from('>II', data, pos)
        pos += 8
        end = data.index(b'\0', pos)
        name = data[pos:end].decode('latin-1')
        pos = end + 1
        out.append((name, off, size))
    return out

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
