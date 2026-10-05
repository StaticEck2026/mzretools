#!/usr/bin/env python3
"""
Extract every graphic asset of an EA Mega Drive ROM and convert it to PNG.

    mdextract.py rom.bin outdir [--names game.names] [--scale N] [--no-frames]

Creates two folders:

    outdir/extracted/   the raw assets as found in the ROM
        <name>.bin          the whole tile set container (header, tiles, palettes, map)
        <name>.tiles.bin    the 8x8 4bpp tiles only (32 bytes per tile)
        <name>.pal.bin      the 4 palettes (64 colour words, Mega Drive format)
        <name>.map.bin      the tile map / sprite frame table block
    outdir/png/         everything converted
        <name>.png          the picture rendered through its tile map
        <name>_tiles.png    the raw tiles in a grid
        <name>_pal.png      the palettes
        <name>_sheet.png    character sheet of a sprite set, <name>/frame_NNNN.png its frames

    outdir/manifest.txt    one line per asset: ROM address, name, tile count, sizes

Names come from the disassembly's names file when given (--names), otherwise
the assets are called art_<ROM address>.  Pure Python, no dependencies.
"""

import argparse
import os
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from mdassets import find_tilesets
from mdart import TileSet, RomShim, Names


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('rom')
    ap.add_argument('outdir')
    ap.add_argument('--names', help='names file of the disassembly (re/nhl98_md/nhl98.names)')
    ap.add_argument('--scale', type=int, default=1, help='integer zoom of the PNG files')
    ap.add_argument('--no-frames', action='store_true', help='do not write the individual sprite frames')
    args = ap.parse_args()

    rom = open(args.rom, 'rb').read()
    shim = RomShim(rom)
    sets = find_tilesets(shim)
    names = Names(args.names) if args.names else Names(None)
    raw_dir = os.path.join(args.outdir, 'extracted')
    png_dir = os.path.join(args.outdir, 'png')
    os.makedirs(raw_dir, exist_ok=True)
    os.makedirs(png_dir, exist_ok=True)

    addrs = sorted(sets)
    manifest = ['%-6s %-40s %6s %8s %8s %8s  %s' % ('addr', 'name', 'tiles', 'size', 'tiles_b', 'map_b', 'kind')]
    for i, a in enumerate(addrs):
        cnt, pal_off, map_off, aend = sets[a]
        if aend is None:
            aend = addrs[i + 1] if i + 1 < len(addrs) else shim.rom_end
        name = names.names.get(a, 'art_%06X' % a).lower()

        # --- raw files
        with open(os.path.join(raw_dir, name + '.bin'), 'wb') as f:
            f.write(rom[a:aend])
        with open(os.path.join(raw_dir, name + '.tiles.bin'), 'wb') as f:
            f.write(rom[a + 10:a + 10 + 32 * cnt])
        with open(os.path.join(raw_dir, name + '.pal.bin'), 'wb') as f:
            f.write(rom[a + pal_off:a + pal_off + 128])
        with open(os.path.join(raw_dir, name + '.map.bin'), 'wb') as f:
            f.write(rom[a + map_off:aend])

        # --- png files
        ts = TileSet(rom, a, cnt, pal_off, map_off, aend, name)
        kind = 'tiles only'
        pic = ts.map_image()
        if pic is not None:
            kind = 'picture %dx%d tiles' % (pic.w // 8, pic.h // 8)
            pic.scaled(args.scale).save(os.path.join(png_dir, name + '.png'))
        else:
            frames = ts.frames()
            if frames:
                kind = 'sprites, %d frames' % len(frames)
                ts.sheet_image(frames).scaled(args.scale).save(os.path.join(png_dir, name + '_sheet.png'))
                large = ts.large_frames(frames)
                if large:
                    big = [frames[k] for k in large]
                    bb = [ts.frame_bounds(p) for p in big]
                    cell = (max(b[2] - b[0] for b in bb) + 4, max(b[3] - b[1] for b in bb) + 10)
                    ts.sheet_image(big, per_row=8, numbers=large, cell=cell).scaled(args.scale).save(
                        os.path.join(png_dir, name + '_sheet_large.png'))
                if not args.no_frames:
                    fdir = os.path.join(png_dir, name)
                    os.makedirs(fdir, exist_ok=True)
                    for n, pieces in enumerate(frames):
                        if pieces:
                            ts.frame_image(pieces).scaled(args.scale).save(os.path.join(fdir, 'frame_%04d.png' % n))
        ts.tiles_image().scaled(args.scale).save(os.path.join(png_dir, name + '_tiles.png'))
        ts.palette_image().scaled(max(args.scale, 2)).save(os.path.join(png_dir, name + '_pal.png'))

        line = '%06X %-40s %6d %8d %8d %8d  %s' % (a, name, cnt, aend - a, 32 * cnt, aend - a - map_off, kind)
        manifest.append(line)
        print(line)

    with open(os.path.join(args.outdir, 'manifest.txt'), 'w') as f:
        f.write('\n'.join(manifest) + '\n')
    print('%d assets -> %s' % (len(addrs), args.outdir))


if __name__ == '__main__':
    main()
