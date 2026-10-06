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
#   nhltool.py viv FILE [OUTDIR]           list an announcer speech bank or export its clips as WAV
#   nhltool.py sprites GAMEDIR OUTDIR      export the 1134 player sprite frames (banks 000_049.PPV ...)
#                                          --home/--away team indices, --team 0|1 jersey colours, --mirrored
#   nhltool.py rinkfull GAMEDIR OUT.png    the rink surface with the home team's centre ice logo
#   nhltool.py dig GAMEDIR OUTDIR          the digital sound effects (PCFF001.DIG) as WAV files
#   nhltool.py kms FILE.KMS [--events]     the tracks (and events) of a song of the music driver
#
import argparse
import json
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from formats import (ShapeBank, Font, load_sample, write_wav, read_viv_index, viv_clip, render_tile_map, read_kms,  # noqa: E402
                     write_png, unpack, pack_code, PackError, game_palette, mirrored_remap, SoundBank,
                     write_wav_pcm8, place_tile_map, team_abbreviations, read_schedule, read_gsummary,
                     read_nhl_cfg, SCHEDULE_GAMES)

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

def export_bank(bank, outdir, palette=None, prefix='', remap=None):
    os.makedirs(outdir, exist_ok=True)
    pal = palette or bank.palette() or GRAY
    meta = []
    for s in bank.shapes:
        entry = {'name': s.name, 'code': s.code, 'width': s.width, 'height': s.height,
                 'center': [s.center_x, s.center_y], 'pos': [s.x, s.y], 'flags': s.flags}
        if s.pixels is not None and s.width and s.height:
            fn = f"{prefix}{s.name.strip().replace('/', '_') or 'shape'}.png"
            px = s.pixels
            if remap:
                px = bytes(p if p == s.transparent else remap[p] for p in px)
            write_png(os.path.join(outdir, fn), s.width, s.height, px, pal, transparent=s.transparent)
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
    pal, remap = load_palette(args.pal), None
    if args.home >= 0:
        pal, remap = team_palette(args)
    meta = export_bank(bank, args.outdir, pal, remap=remap)
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
            write_wav(os.path.join(args.outdir, name.lower() + '.wav'), viv_clip(data, off, size))
        print(f"extracted {len(entries)} clips to {args.outdir} as WAV")

def team_palette(args):
    '''--gamedir/--home/--away: the match palette with the jersey colours of the two teams'''
    gamedir = getattr(args, 'gamedir', None) or os.path.dirname(os.path.abspath(args.bank if hasattr(args, 'bank') else args.file))
    pal, rh, ra = game_palette(gamedir, args.home, args.away)
    return pal, (ra if getattr(args, 'team', 0) == 1 else rh)

def cmd_sprites(args):
    '''The player sprite frames 0..1133 live in 23 banks of 50 frames named like the frame range
    they hold (load_player_graphics/load_sprite_banks: "%d00_%d49" / "%d50_%d99" + .PPV, without
    the underscore from bank 20 on); entries are named "%04d" after the frame number. Frames are
    drawn through the colour remap table of the team (--team 0 home, 1 away).'''
    os.makedirs(args.outdir, exist_ok=True)
    pal, remap = (load_palette(args.pal), None) if args.pal else team_palette(args)
    if args.mirrored and remap:
        remap = mirrored_remap(remap)
    frames = {}
    for i in range(23):
        half = i // 2
        fmt = ("{0}00_{0}49" if i % 2 == 0 else "{0}50_{0}99") if i < 20 else ("{0}00{0}49" if i % 2 == 0 else "{0}50{0}99")
        name = fmt.format(half) + ".PPV"
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
            px = bytes(p if p == s.transparent else remap[p] for p in s.pixels) if remap else s.pixels
            write_png(os.path.join(args.outdir, fn), s.width, s.height, px, pal or GRAY, transparent=s.transparent)
            frames[fid] = {'file': fn, 'width': s.width, 'height': s.height, 'center': [s.center_x, s.center_y]}
    with open(os.path.join(args.outdir, 'frames.json'), 'w') as f:
        json.dump(frames, f, indent=1)
    print(f"exported {len(frames)} frames")

RINK_TILE_NAMES = ['BOS', 'BUF', 'CGY', 'CHI', 'DET', 'EDM', 'HFD', 'LA', 'MIN', 'MTL', 'NJ', 'NYI', 'NYR',
                   'OTT', 'PHI', 'PIT', 'QUE', 'STL', 'SJ', 'TB', 'TOR', 'VAN', 'WSH', 'WPG', 'ANH', 'FLO']
# load_rink: tile column/row of the centre ice logo and of the mirrored second half (-1 = none)
RINK_LOGO = [(21, 38, -1, -1), (22, 36, -1, -1), (22, 37, -1, -1), (22, 37, -1, -1), (21, 37, -1, -1),
             (22, 44, 25, 35), (22, 37, -1, -1), (32, 45, 15, 34), (21, 37, -1, -1), (22, 37, -1, -1),
             (30, 45, 17, 34), (22, 38, -1, -1), (22, 36, -1, -1), (21, 38, -1, -1), (22, 37, -1, -1),
             (13, 31, 34, 48), (22, 36, -1, -1), (21, 36, -1, -1), (21, 38, -1, -1), (22, 38, -1, -1),
             (22, 38, -1, -1), (21, 36, -1, -1), (22, 37, -1, -1), (21, 38, -1, -1), (21, 37, -1, -1),
             (21, 37, -1, -1)]

def cmd_rinkfull(args):
    '''load_rink(): the 384x592 rink surface (RINK.QFS 'rink') with the centre ice logo of the home
    team (TEAM.TIL/.MAP) drawn with the match palette'''
    pal, _, _ = game_palette(args.gamedir, args.home, args.away)
    rink = ShapeBank(read(os.path.join(args.gamedir, 'RINK.QFS'))).find('rink')
    px = bytearray(rink.pixels)
    name = RINK_TILE_NAMES[args.home]
    til = read(os.path.join(args.gamedir, name + '.TIL'))
    mp = read(os.path.join(args.gamedir, name + '.MAP'))
    col, row, col2, row2 = RINK_LOGO[args.home]
    place_tile_map(px, rink.width, til, mp, col, row)
    if col2 >= 0:
        place_tile_map(px, rink.width, til, mp, col2, row2, mirrored=True)
    write_png(args.out, rink.width, rink.height, bytes(px), pal)
    print(f"wrote {args.out} ({rink.width}x{rink.height})")

def cmd_dig(args):
    '''Exports the digital sound effects as WAV files named after the sound id of play_sfx()'''
    bank = SoundBank(read(os.path.join(args.gamedir, 'PCFF001.PAT')), read(os.path.join(args.gamedir, 'PCFF001.TIM')),
                     read(os.path.join(args.gamedir, 'PCFF001.DIG')))
    os.makedirs(args.outdir, exist_ok=True)
    n = 0
    for sid in bank.effect_ids():
        e = bank.effect(sid)
        write_wav_pcm8(os.path.join(args.outdir, f"sfx_{sid:02x}.wav"), e['pcm'], e['rate'])
        print(f"id 0x{sid:02x}: timbre {e['timbre']} sample {e['sample']} {len(e['pcm'])} bytes {e['rate']} Hz"
              f" note {e['length']:.2f} s" + (f" loop {e['loop']}" if e['loop'] else ''))
        n += 1
    print(f"exported {n} sound effects to {args.outdir}")

def cmd_kms(args):
    '''Lists the tracks and events of a song (NAME.KMS with NAME.CFG)'''
    base = os.path.splitext(args.file)[0]
    cfg_path = next((base + e for e in ('.CFG', '.cfg') if os.path.exists(base + e)), None)
    song = read_kms(read(args.file), read(cfg_path) if cfg_path else b'')
    print(f"tempo {song['tempo']} ({0.4 * song['tempo']:.1f} steps/s), {len(song['tracks'])} tracks")
    for i, t in enumerate(song['tracks']):
        name = next((ev[3].split(b'\0')[0].decode('latin-1') for ev in t['events'] if ev[1] == 0xe7), '')
        notes = [ev for ev in t['events'] if ev[1] < 0xd9]
        print(f"track {i} '{name}': channels 0x{t['mask']:04x} volume {t['volume']} pan {t['pan']}, {len(notes)} notes")
        if args.events:
            step = 0
            for d, code, a, b in t['events']:
                step += d
                if code < 0xd9:
                    print(f"  {step:6d} note {(code & 0x7f) + 24:3d} vel {a if code >= 0x80 else '-':>3} len {b}")
                elif code != 0xe7:
                    print(f"  {step:6d} 0x{code:02x} {a} {b}")

def _teams_near(path):
    d = os.path.dirname(os.path.abspath(path))
    for n in ('TEAMS.DB', 'teams.db'):
        if os.path.exists(os.path.join(d, n)):
            return team_abbreviations(read(os.path.join(d, n)))
    return [str(i) for i in range(28)]

def cmd_schedule(args):
    '''Lists the games of schedule.db / LSSCHED.DB'''
    teams = _teams_near(args.file)
    played, games = read_schedule(read(args.file))
    print(f"{played} games played, {len(games)} records")
    for i, (m, d, h, a, hg, ag) in enumerate(games):
        if (m == 0 or m == 0xff) and not args.all:
            continue
        if h >= len(teams) or a >= len(teams):
            print(f"{i:4d} (empty)")
            continue
        k = i - SCHEDULE_GAMES
        part = f'series {k // 7 + 1:2d} game {k % 7 + 1}' if k >= 0 else 'season'
        score = f"{hg}-{ag}" if hg != 0xff else '-'
        print(f"{i:4d} {part:17s} {m:2d}/{d:02d} {teams[h]:>4s} - {teams[a]:<4s} {score}")

def cmd_gsummary(args):
    '''Lists the events of gsummary.db'''
    teams = _teams_near(args.file)
    header, events, trailer = read_gsummary(read(args.file))
    print(f"{teams[header['home']]} - {teams[header['away']]} ({header['month']}/{header['day']}), "
          f"{header['records']} records; goals {trailer['home_goals']}-{trailer['away_goals']}, "
          f"shots {trailer['home_shots']}-{trailer['away_shots']}")
    for e in events:
        print(' ', e)

def cmd_cfg(args):
    '''Shows NHL.CFG'''
    c = read_nhl_cfg(read(args.file).decode('latin-1'))
    print(f"sound card {c['sound_card']} ({c['sound_card_name']}), CD drive {c['cd_drive']}, "
          f"{len(c['installed'])} files installed")

def main():
    ap = argparse.ArgumentParser(description='NHL Hockey (DOS) asset tool')
    sub = ap.add_subparsers(dest='cmd', required=True)
    p = sub.add_parser('info'); p.add_argument('files', nargs='+'); p.set_defaults(fn=cmd_info)
    p = sub.add_parser('shapes'); p.add_argument('bank'); p.add_argument('outdir'); p.add_argument('--pal')
    p.add_argument('--gamedir'); p.add_argument('--home', type=int, default=-1); p.add_argument('--away', type=int, default=4)
    p.add_argument('--team', type=int, default=0); p.set_defaults(fn=cmd_shapes)
    p = sub.add_parser('unpack'); p.add_argument('file'); p.add_argument('out'); p.set_defaults(fn=cmd_unpack)
    p = sub.add_parser('wav'); p.add_argument('file'); p.add_argument('out'); p.set_defaults(fn=cmd_wav)
    p = sub.add_parser('font'); p.add_argument('file'); p.add_argument('out'); p.set_defaults(fn=cmd_font)
    p = sub.add_parser('rink'); p.add_argument('til'); p.add_argument('map'); p.add_argument('out'); p.add_argument('--pal'); p.set_defaults(fn=cmd_rink)
    p = sub.add_parser('viv'); p.add_argument('file'); p.add_argument('outdir', nargs='?'); p.set_defaults(fn=cmd_viv)
    p = sub.add_parser('sprites'); p.add_argument('gamedir'); p.add_argument('outdir'); p.add_argument('--pal')
    p.add_argument('--home', type=int, default=0); p.add_argument('--away', type=int, default=4)
    p.add_argument('--team', type=int, default=0); p.add_argument('--mirrored', action='store_true'); p.set_defaults(fn=cmd_sprites)
    p = sub.add_parser('rinkfull'); p.add_argument('gamedir'); p.add_argument('out'); p.add_argument('--home', type=int, default=0)
    p.add_argument('--away', type=int, default=4); p.set_defaults(fn=cmd_rinkfull)
    p = sub.add_parser('dig'); p.add_argument('gamedir'); p.add_argument('outdir'); p.set_defaults(fn=cmd_dig)
    p = sub.add_parser('kms'); p.add_argument('file'); p.add_argument('--events', action='store_true'); p.set_defaults(fn=cmd_kms)
    p = sub.add_parser('schedule'); p.add_argument('file'); p.add_argument('--all', action='store_true'); p.set_defaults(fn=cmd_schedule)
    p = sub.add_parser('gsummary'); p.add_argument('file'); p.set_defaults(fn=cmd_gsummary)
    p = sub.add_parser('cfg'); p.add_argument('file'); p.set_defaults(fn=cmd_cfg)
    args = ap.parse_args()
    args.fn(args)

if __name__ == '__main__':
    main()
