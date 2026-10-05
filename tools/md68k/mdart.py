#!/usr/bin/env python3
"""
Export the EA tile set graphics of a Mega Drive ROM as PNG files.

    mdart.py rom.bin outdir [--names game.names] [--scale N] [--map-cache map.pkl]

For every tile set (see mdassets.py for the container format) the tool writes

    <name>.png          the picture, rendered through the tile map with its palettes
    <name>_tiles.png    the raw tiles in a grid (32 per row), palette 0
    <name>_pal.png      the four palettes

Sets whose metadata block is a sprite frame table (the player sprites) get

    <name>/frame_NNNN.png   every frame assembled from its hardware sprite pieces
    <name>_sheet.png        a character sheet of all frames with their numbers

Sprite frame format (per frame a list of 8 byte pieces in the layout of the
VDP sprite attribute table): y, size|bank<<12, tile attribute, x.  The tile
index of a piece is bank*2048 + (attribute & $7FF) within the set.

`index.txt` lists every exported set.  Only the standard library is needed.
"""

import argparse
import os
import struct
import sys
import zlib

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from mdassets import find_tilesets
from mdasm import Names


# ----------------------------------------------------------------------
class Image:
    """Minimal RGBA raster with a PNG writer."""

    def __init__(self, w, h, bg=(0, 0, 0, 0)):
        self.w = w
        self.h = h
        self.px = bytearray(bytes(bg) * (w * h))

    def put(self, x, y, c):
        if 0 <= x < self.w and 0 <= y < self.h:
            i = (y * self.w + x) * 4
            self.px[i:i + 4] = c

    def rect(self, x0, y0, w, h, c):
        for y in range(y0, y0 + h):
            for x in range(x0, x0 + w):
                self.put(x, y, c)

    def blit(self, other, x0, y0):
        for y in range(other.h):
            row = other.px[y * other.w * 4:(y + 1) * other.w * 4]
            for x in range(other.w):
                c = row[x * 4:x * 4 + 4]
                if c[3]:
                    self.put(x0 + x, y0 + y, c)

    def scaled(self, n):
        if n == 1:
            return self
        out = Image(self.w * n, self.h * n)
        for y in range(self.h):
            srow = self.px[y * self.w * 4:(y + 1) * self.w * 4]
            line = bytearray()
            for x in range(self.w):
                line += srow[x * 4:x * 4 + 4] * n
            for k in range(n):
                yy = y * n + k
                out.px[yy * out.w * 4:(yy + 1) * out.w * 4] = line
        return out

    def save(self, path):
        raw = b''.join(b'\x00' + bytes(self.px[y * self.w * 4:(y + 1) * self.w * 4]) for y in range(self.h))

        def chunk(t, d):
            return struct.pack('>I', len(d)) + t + d + struct.pack('>I', zlib.crc32(t + d) & 0xFFFFFFFF)
        with open(path, 'wb') as f:
            f.write(b'\x89PNG\r\n\x1a\n')
            f.write(chunk(b'IHDR', struct.pack('>IIBBBBB', self.w, self.h, 8, 6, 0, 0, 0)))
            f.write(chunk(b'IDAT', zlib.compress(raw, 9)))
            f.write(chunk(b'IEND', b''))


# 3x5 digit font for the frame numbers on the sheets
DIGITS = {
    '0': ['111', '101', '101', '101', '111'], '1': ['010', '110', '010', '010', '111'],
    '2': ['111', '001', '111', '100', '111'], '3': ['111', '001', '111', '001', '111'],
    '4': ['101', '101', '111', '001', '001'], '5': ['111', '100', '111', '001', '111'],
    '6': ['111', '100', '111', '101', '111'], '7': ['111', '001', '001', '001', '001'],
    '8': ['111', '101', '111', '101', '111'], '9': ['111', '101', '111', '001', '111'],
}


def draw_text(img, x, y, text, c=(255, 255, 255, 255)):
    for ch in text:
        glyph = DIGITS.get(ch)
        if glyph:
            for gy, row in enumerate(glyph):
                for gx, bit in enumerate(row):
                    if bit == '1':
                        img.put(x + gx, y + gy, c)
        x += 4


# ----------------------------------------------------------------------
class TileSet:
    def __init__(self, rom, addr, cnt, pal_off, map_off, end, name):
        self.addr = addr
        self.count = cnt
        self.name = name
        self.tiles = rom[addr + 10:addr + 10 + 32 * cnt]
        pal = struct.unpack('>64H', rom[addr + pal_off:addr + pal_off + 128])
        self.palette = [(((c >> 1) & 7) * 36, ((c >> 5) & 7) * 36, ((c >> 9) & 7) * 36, 255) for c in pal]
        self.map_addr = addr + map_off
        self.map_end = end
        self.rom = rom

    def colour(self, pal, idx, transparent):
        if idx == 0 and transparent:
            return None
        return self.palette[pal * 16 + idx]

    def draw_tile(self, img, t, x0, y0, pal, hflip=False, vflip=False, transparent=True):
        if t >= self.count:
            return
        base = t * 32
        for y in range(8):
            sy = 7 - y if vflip else y
            row = self.tiles[base + sy * 4:base + sy * 4 + 4]
            for x in range(8):
                sx = 7 - x if hflip else x
                b = row[sx >> 1]
                idx = (b >> 4) if (sx & 1) == 0 else (b & 15)
                c = self.colour(pal, idx, transparent)
                if c:
                    img.put(x0 + x, y0 + y, c)

    # tiles in a grid
    def tiles_image(self, per_row=32, pal=0):
        rows = (self.count + per_row - 1) // per_row
        img = Image(per_row * 8, rows * 8, (0, 0, 0, 0))
        for t in range(self.count):
            self.draw_tile(img, t, (t % per_row) * 8, (t // per_row) * 8, pal)
        return img

    def palette_image(self):
        img = Image(16 * 8, 4 * 8)
        for p in range(4):
            for i in range(16):
                img.rect(i * 8, p * 8, 8, 8, self.palette[p * 16 + i])
        return img

    # tile map
    def tilemap(self):
        rom = self.rom
        w, h = struct.unpack('>HH', rom[self.map_addr:self.map_addr + 4])
        if not (0 < w <= 128 and 0 < h <= 128) or self.map_addr + 4 + 2 * w * h > len(rom):
            return None
        ents = struct.unpack('>%dH' % (w * h), rom[self.map_addr + 4:self.map_addr + 4 + 2 * w * h])
        if max(ents, default=0) & 0x7FF >= self.count and sum(1 for e in ents if e & 0x7FF >= self.count) > len(ents) // 4:
            return None
        return w, h, ents

    def map_image(self):
        m = self.tilemap()
        if m is None:
            return None
        w, h, ents = m
        img = Image(w * 8, h * 8, (0, 0, 0, 255))
        for i, e in enumerate(ents):
            self.draw_tile(img, e & 0x7FF, (i % w) * 8, (i // w) * 8, (e >> 13) & 3, bool(e & 0x800), bool(e & 0x1000), transparent=False)
        return img

    # sprite frame table
    def frames(self):
        rom = self.rom
        size = self.map_end - self.map_addr
        if size < 4:
            return None
        first = struct.unpack('>H', rom[self.map_addr:self.map_addr + 2])[0]
        n = first // 2
        if first & 1 or n < 2 or n * 2 > size:
            return None
        tbl = struct.unpack('>%dH' % n, rom[self.map_addr:self.map_addr + 2 * n])
        if any(tbl[i] >= tbl[i + 1] or (tbl[i + 1] - tbl[i]) % 8 for i in range(n - 1)):
            return None
        if tbl[-1] + 8 > size:
            return None
        frames = []
        total = good = 0
        for i in range(n):
            o = tbl[i]
            e = tbl[i + 1] if i + 1 < n else min(size, o + 8 * 8)
            pieces = []
            for k in range((e - o) // 8):
                y, sz, attr, x = struct.unpack('>hHHh', rom[self.map_addr + o + 8 * k:self.map_addr + o + 8 * k + 8])
                bank = sz >> 12
                shape = (sz >> 8) & 15
                w = ((shape >> 2) & 3) + 1
                h = (shape & 3) + 1
                tile = bank * 0x800 + (attr & 0x7FF)
                total += 1
                if tile + w * h > self.count or sz & 0xFF or abs(x) > 320 or abs(y) > 320:
                    break
                good += 1
                pieces.append((x, y, w, h, tile, bool(attr & 0x800), bool(attr & 0x1000), (attr >> 13) & 3))
            frames.append(pieces)
        # a real frame table is almost entirely made of valid pieces
        if total == 0 or good < total * 0.95 or good < n:
            return None
        return frames

    def frame_bounds(self, pieces):
        xs = [p[0] for p in pieces] + [p[0] + p[2] * 8 for p in pieces]
        ys = [p[1] for p in pieces] + [p[1] + p[3] * 8 for p in pieces]
        if not xs:
            return 0, 0, 8, 8
        return min(xs), min(ys), max(xs), max(ys)

    def draw_frame(self, img, pieces, ox, oy):
        """ox, oy: position of the frame origin in img."""
        for x, y, w, h, tile, hf, vf, pal in pieces:
            for tx in range(w):
                for ty in range(h):
                    t = tile + tx * h + ty        # hardware layout: column major
                    dtx = (w - 1 - tx) if hf else tx
                    dty = (h - 1 - ty) if vf else ty
                    self.draw_tile(img, t, ox + x + dtx * 8, oy + y + dty * 8, pal, hf, vf)

    def frame_image(self, pieces):
        x0, y0, x1, y1 = self.frame_bounds(pieces)
        img = Image(x1 - x0, y1 - y0)
        self.draw_frame(img, pieces, -x0, -y0)
        return img

    def sheet_image(self, frames, per_row=32, numbers=None, cell=None):
        """Every frame in its own cell, centred on its bounding box.  The cell
        size is the 99th percentile of the frame extents (a few scenes are
        much bigger than the sprites; they are clipped here and get a sheet of
        their own), unless given."""
        bounds = [self.frame_bounds(p) for p in frames]
        if cell is None:
            ws = sorted(b[2] - b[0] for b in bounds)
            hs = sorted(b[3] - b[1] for b in bounds)
            cw = ws[min(len(ws) - 1, int(len(ws) * 0.99))] + 4
            ch = hs[min(len(hs) - 1, int(len(hs) * 0.99))] + 10
        else:
            cw, ch = cell
        rows = (len(frames) + per_row - 1) // per_row
        img = Image(per_row * cw, rows * ch, (48, 48, 48, 255))
        for i, pieces in enumerate(frames):
            cx = (i % per_row) * cw
            cy = (i // per_row) * ch
            x0, y0, x1, y1 = bounds[i]
            img.rect(cx, cy, cw, ch, (40, 40, 40, 255) if (i // per_row + i) & 1 else (56, 56, 56, 255))
            cellimg = Image(cw, ch - 8)
            self.draw_frame(cellimg, pieces, (cw - (x1 - x0)) // 2 - x0, (ch - 10 - (y1 - y0)) // 2 - y0)
            img.blit(cellimg, cx, cy + 8)
            n = numbers[i] if numbers else i
            draw_text(img, cx + 1, cy + 1, str(n), (200, 200, 60, 255))
        return img

    def large_frames(self, frames):
        """Indices of the frames that do not fit the standard sheet cell."""
        bounds = [self.frame_bounds(p) for p in frames]
        ws = sorted(b[2] - b[0] for b in bounds)
        hs = sorted(b[3] - b[1] for b in bounds)
        cw = ws[min(len(ws) - 1, int(len(ws) * 0.99))]
        ch = hs[min(len(hs) - 1, int(len(hs) * 0.99))]
        return [i for i, b in enumerate(bounds) if b[2] - b[0] > cw or b[3] - b[1] > ch]


# ----------------------------------------------------------------------
class RomShim:
    """What mdassets.find_tilesets needs when no mapping result is at hand."""

    def __init__(self, rom):
        self.rom = rom
        self.rom_end = len(rom)
        while self.rom_end > 0 and rom[self.rom_end - 1] == 0xFF:
            self.rom_end -= 1
        self.kind = bytearray(len(rom))


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('rom')
    ap.add_argument('outdir')
    ap.add_argument('--names', help='names file of the disassembly, used for the file names')
    ap.add_argument('--map-cache', help='pickle of the mapping result (optional, speeds up the scan)')
    ap.add_argument('--scale', type=int, default=1, help='integer zoom of the output images')
    ap.add_argument('--no-frames', action='store_true', help='do not write the individual sprite frames')
    args = ap.parse_args()

    rom = open(args.rom, 'rb').read()
    mapper = None
    if args.map_cache and os.path.exists(args.map_cache):
        import pickle
        sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
        mapper = pickle.load(open(args.map_cache, 'rb'))
    if mapper is None:
        mapper = RomShim(rom)
    sets = find_tilesets(mapper)
    names = Names(args.names) if args.names else Names(None)
    os.makedirs(args.outdir, exist_ok=True)
    addrs = sorted(sets)
    index = []
    for i, a in enumerate(addrs):
        cnt, pal_off, map_off, aend = sets[a]
        if aend is None:
            # sprite data: the block runs up to the next set
            aend = addrs[i + 1] if i + 1 < len(addrs) else mapper.rom_end
        name = names.names.get(a, 'art_%06X' % a).lower()
        ts = TileSet(rom, a, cnt, pal_off, map_off, aend, name)
        kind = 'tiles'
        pic = ts.map_image()
        if pic is not None:
            kind = 'map %dx%d' % (pic.w // 8, pic.h // 8)
            pic.scaled(args.scale).save(os.path.join(args.outdir, name + '.png'))
        else:
            frames = ts.frames()
            if frames:
                kind = 'sprites, %d frames' % len(frames)
                ts.sheet_image(frames).scaled(args.scale).save(os.path.join(args.outdir, name + '_sheet.png'))
                large = ts.large_frames(frames)
                if large:
                    big = [frames[i] for i in large]
                    bb = [ts.frame_bounds(p) for p in big]
                    cell = (max(b[2] - b[0] for b in bb) + 4, max(b[3] - b[1] for b in bb) + 10)
                    ts.sheet_image(big, per_row=8, numbers=large, cell=cell).scaled(args.scale).save(
                        os.path.join(args.outdir, name + '_sheet_large.png'))
                    kind += ' (%d large frames on a second sheet)' % len(large)
                if not args.no_frames:
                    fdir = os.path.join(args.outdir, name)
                    os.makedirs(fdir, exist_ok=True)
                    for n, pieces in enumerate(frames):
                        if pieces:
                            ts.frame_image(pieces).scaled(args.scale).save(os.path.join(fdir, 'frame_%04d.png' % n))
        ts.tiles_image().scaled(args.scale).save(os.path.join(args.outdir, name + '_tiles.png'))
        ts.palette_image().scaled(max(args.scale, 2)).save(os.path.join(args.outdir, name + '_pal.png'))
        index.append('%06X %-40s %5d tiles  %s' % (a, name, cnt, kind))
        print(index[-1])
    with open(os.path.join(args.outdir, 'index.txt'), 'w') as f:
        f.write('\n'.join(index) + '\n')


if __name__ == '__main__':
    main()
