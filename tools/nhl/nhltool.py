#!/usr/bin/env python3
#
# Command line front end for the NHL Hockey asset readers in formats.py.
#
#   nhltool.py info  FILE...               describe shape banks, fonts, samples, VIV banks
#   nhltool.py shapes BANK OUTDIR [--pal PALFILE[:ENTRY]]
#                                          export every image of a bank as PNG + a JSON sidecar
#   nhltool.py unpack FILE OUT             decompress a RefPack/EA packed file
#   nhltool.py wav FILE OUT.wav            convert an 8SVX sample to WAV
#   nhltool.py font FONT.VFN OUT.png       render the glyph sheet of a 1 bpp font
#   nhltool.py rink RINK.TIL RINK.MAP OUT.png [--pal PALFILE]
#   nhltool.py viv FILE [OUTDIR]           list or extract an announcer speech bank
#   nhltool.py sprites GAMEDIR OUTDIR      export the 1134 player sprite frames (banks 000_049.PPV ...)
#
import argparse
import json
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from formats import (ShapeBank, Font, load_sample, write_wav, read_viv_index, render_tile_map,  # noqa: E402
                     write_png, unpack, pack_code, PackError)

def read(path):
    with open(path, 'rb') as f:
        return f.read()

def load_palette(spec):
    '''PALFILE[:ENTRY] - a shape bank containing a palette entry (default: the first palette found)'''
    if not spec:
        return None
    path, _, entry = spec.partition(':')
    bank = ShapeBank(read(path))
    if entry:
        s = bank.find(entry)
        return s.palette if s else None
    return bank.palette()

GRAY = [(i, i, i) for i in range(256)]

def export_bank(bank, outdir, palette=None, prefix=''):
    os.makedirs(outdir, exist_ok=True)
    pal = palette or bank.palette() or GRAY
    meta = []
    for s in bank.shapes:
        entry = {'name': s.name, 'code': s.code, 'width': s.width, 'height': s.height,
                 'center': [s.center_x, s.center_y], 'pos': [s.x, s.y], 'flags': s.flags}
        if s.pixels is not None and s.width and s.height:
            fn = f"{prefix}{s.name.strip().replace('/', '_') or 'shape'}.png"
            write_png(os.path.join(outdir, fn), s.width, s.height, s.pixels, pal, transparent=0)
            entry['file'] = fn
        elif s.palette:
            entry['palette'] = s.palette
        meta.append(entry)
    with open(os.path.join(outdir, f"{prefix}shapes.json"), 'w') as f:
        json.dump({'dir_id': bank.dir_id, 'shapes': meta}, f, indent=1)
    return meta

def cmd_info(args):
    for path in args.files:
        data = read(path)
        code = pack_code(data)
        try:
            if code is not None:
                print(f"{path}: packed (code 0x{code:02x}), {len(data)} bytes")
                data = unpack(data)
            if data[:4] == b'SHPI':
                bank = ShapeBank(data)
                print(f"{path}: SHPI bank '{bank.dir_id}', {bank.count} entries")
                for s in bank.shapes:
                    print(f"   {s}")
            elif data[:4] in (b'FORM', b'RIFF'):
                smp = load_sample(data)
                print(f"{path}: sample, {smp.rate} Hz, {len(smp.pcm)} bytes")
            elif len(data) > 0x20 and data[3:4].isdigit() and data[4] <= data[5]:
                fnt = Font(data)
                print(f"{path}: font '{fnt.tag}', chars {fnt.first}-{fnt.last}, {fnt.def_width}x{fnt.height}")
            else:
                print(f"{path}: unknown, {len(data)} bytes, head {data[:16].hex()}")
        except (ValueError, PackError, IndexError) as e:
            print(f"{path}: error: {e}")

def cmd_shapes(args):
    bank = ShapeBank(read(args.bank))
    meta = export_bank(bank, args.outdir, load_palette(args.pal))
    print(f"exported {sum(1 for m in meta if 'file' in m)} images to {args.outdir}")

def cmd_unpack(args):
    data = unpack(read(args.file))
    with open(args.out, 'wb') as f:
        f.write(data)
    print(f"wrote {len(data)} bytes")

def cmd_wav(args):
    write_wav(args.out, load_sample(read(args.file)))

def cmd_font(args):
    fnt = Font(read(args.file))
    chars = [chr(c) for c in range(fnt.first, fnt.last + 1)]
    cols = 16
    cw, ch = max(fnt.glyph_width(c) for c in chars) + 1, fnt.height + 1
    rows = (len(chars) + cols - 1) // cols
    W, H = cols * cw, rows * ch
    img = bytearray(W * H)
    for i, c in enumerate(chars):
        g = fnt.glyph(c)
        ox, oy = (i % cols) * cw, (i // cols) * ch
        for y, row in enumerate(g):
            for x, v in enumerate(row):
                if v:
                    img[(oy + y) * W + ox + x] = 1
    write_png(args.out, W, H, bytes(img), [(0, 0, 0), (255, 255, 255)])
    print(f"wrote {args.out} ({len(chars)} glyphs)")

def cmd_rink(args):
    W, H, px = render_tile_map(read(args.til), read(args.map))
    write_png(args.out, W, H, px, load_palette(args.pal) or GRAY, transparent=0xff)
    print(f"wrote {args.out} ({W}x{H})")

def cmd_viv(args):
    data = read(args.file)
    entries = read_viv_index(data)
    for name, off, size in entries:
        print(f"{name:16s} offset 0x{off:x} size {size}")
    if args.outdir:
        os.makedirs(args.outdir, exist_ok=True)
        for name, off, size in entries:
            with open(os.path.join(args.outdir, name), 'wb') as f:
                f.write(data[off:off + size])
        print(f"extracted {len(entries)} clips to {args.outdir}")

def cmd_sprites(args):
    '''The player sprite frames 0..1133 live in 23 banks of 50 frames named like the frame range
    they hold (load_player_graphics/sub_1395f: "%d00_%d49" / "%d50_%d99" + .PPV); entries are
    named "%04d" after the frame number.'''
    os.makedirs(args.outdir, exist_ok=True)
    pal = load_palette(args.pal)
    frames = {}
    for i in range(23):
        half = i // 2
        name = (f"{half}00_{half}49" if i % 2 == 0 else f"{half}50_{half}99") + ".PPV"
        path = os.path.join(args.gamedir, name)
        if not os.path.exists(path):
            path = os.path.join(args.gamedir, name.lower())
        if not os.path.exists(path):
            print(f"missing {name}")
            continue
        bank = ShapeBank(read(path))
        for s in bank.shapes:
            if s.pixels is None or not s.name.strip().isdigit():
                continue
            fid = int(s.name)
            fn = f"frame_{fid:04d}.png"
            write_png(os.path.join(args.outdir, fn), s.width, s.height, s.pixels, pal or bank.palette() or GRAY, transparent=0)
            frames[fid] = {'file': fn, 'width': s.width, 'height': s.height, 'center': [s.center_x, s.center_y]}
    with open(os.path.join(args.outdir, 'frames.json'), 'w') as f:
        json.dump(frames, f, indent=1)
    print(f"exported {len(frames)} frames")

def main():
    ap = argparse.ArgumentParser(description='NHL Hockey (DOS) asset tool')
    sub = ap.add_subparsers(dest='cmd', required=True)
    p = sub.add_parser('info'); p.add_argument('files', nargs='+'); p.set_defaults(fn=cmd_info)
    p = sub.add_parser('shapes'); p.add_argument('bank'); p.add_argument('outdir'); p.add_argument('--pal'); p.set_defaults(fn=cmd_shapes)
    p = sub.add_parser('unpack'); p.add_argument('file'); p.add_argument('out'); p.set_defaults(fn=cmd_unpack)
    p = sub.add_parser('wav'); p.add_argument('file'); p.add_argument('out'); p.set_defaults(fn=cmd_wav)
    p = sub.add_parser('font'); p.add_argument('file'); p.add_argument('out'); p.set_defaults(fn=cmd_font)
    p = sub.add_parser('rink'); p.add_argument('til'); p.add_argument('map'); p.add_argument('out'); p.add_argument('--pal'); p.set_defaults(fn=cmd_rink)
    p = sub.add_parser('viv'); p.add_argument('file'); p.add_argument('outdir', nargs='?'); p.set_defaults(fn=cmd_viv)
    p = sub.add_parser('sprites'); p.add_argument('gamedir'); p.add_argument('outdir'); p.add_argument('--pal'); p.set_defaults(fn=cmd_sprites)
    args = ap.parse_args()
    args.fn(args)

if __name__ == '__main__':
    main()
