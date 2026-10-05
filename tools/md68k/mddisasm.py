#!/usr/bin/env python3
"""
Disassemble a Mega Drive ROM into a SNASM68K compatible source tree.

    mddisasm.py rom.bin outdir --name nhl98 [--names nhl98.names] [--segments segments.txt]
"""
import argparse
import os
import pickle
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from mdmap import Mapper, CODE, CODE_CONT, UNKNOWN
from mdasm import Emitter, Names


def rom_end(rom):
    i = len(rom)
    while i > 0 and rom[i - 1] == 0xFF:
        i -= 1
    return i + (i & 1)


def auto_segments(m, min_gap=0x1000, max_code=0x10000):
    """Split the ROM into code and data segments."""
    rngs = m.code_ranges()
    clusters = []
    for a, b in rngs:
        if clusters and a - clusters[-1][1] < min_gap:
            clusters[-1][1] = b
        else:
            clusters.append([a, b])
    segs = []
    pos = 0
    for a, b in clusters:
        if a - pos >= min_gap:
            # data before the cluster
            if pos == 0:
                a0 = 0
            segs.append((pos, a, 'data'))
            pos = a
        # extend the cluster end to the next data start (small trailing data stays with code)
        segs.append((pos, b, 'code'))
        pos = b
    if pos < m.rom_end:
        segs.append((pos, m.rom_end, 'data'))
    # merge the header into the first segment, split long code segments
    out = []
    for a, b, kind in segs:
        if kind == 'code' and b - a > max_code:
            x = a
            while b - x > max_code:
                # find a function start near x + max_code
                target = x + max_code
                cands = [l for l, k in m.labels.items() if k == 'sub' and target - 0x2000 <= l <= target + 0x2000]
                cut = min(cands, key=lambda l: abs(l - target)) if cands else target
                out.append((x, cut, kind))
                x = cut
            out.append((x, b, kind))
        else:
            out.append((a, b, kind))
    return out


def load_segment_names(path):
    """Optional file: <start hex> <relative path> <title>"""
    d = {}
    if path and os.path.exists(path):
        for line in open(path):
            line = line.strip()
            if not line or line.startswith('#'):
                continue
            parts = line.split(None, 2)
            d[int(parts[0], 16)] = (parts[1], parts[2] if len(parts) > 2 else parts[1])
    return d


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('rom')
    ap.add_argument('outdir')
    ap.add_argument('--name', default='rom')
    ap.add_argument('--names', help='symbol names file (default: <outdir>/<name>.names)')
    ap.add_argument('--segments', help='segment naming file')
    ap.add_argument('--blob-min', type=lambda x: int(x, 0), default=0x200)
    ap.add_argument('--imm-macros', action='store_true')
    ap.add_argument('--map-cache', help='pickle file to cache the mapping result')
    ap.add_argument('--ea', action='store_true', help='recognise EA tile sets and roster records')
    ap.add_argument('--max-code', type=lambda x: int(x, 0), default=0x10000, help='split code segments longer than this')
    args = ap.parse_args()

    rom = open(args.rom, 'rb').read()
    end = rom_end(rom)
    m = None
    if args.map_cache and os.path.exists(args.map_cache):
        m = pickle.load(open(args.map_cache, 'rb'))
    if m is None:
        m = Mapper(rom, end)
        m.analyse()
        if args.map_cache:
            pickle.dump(m, open(args.map_cache, 'wb'))
    print('map:', m.stats(), file=sys.stderr)

    names_path = args.names or os.path.join(args.outdir, args.name + '.names')
    names = Names(names_path)
    segnames = load_segment_names(args.segments)
    segs = []
    auto = auto_segments(m, max_code=args.max_code)
    # addresses listed in the segments file are forced boundaries
    for cut in sorted(segnames):
        for i, (a, b, kind) in enumerate(auto):
            if a < cut < b:
                auto[i:i + 1] = [(a, cut, kind), (cut, b, kind)]
                break
    for a, b, kind in auto:
        if a in segnames:
            path, title = segnames[a]
        else:
            if kind == 'code':
                path = 'src/code_%06X.asm' % a
                title = 'Code $%06X-$%06X' % (a, b - 1)
            else:
                path = 'data/data_%06X.asm' % a
                title = 'Data $%06X-$%06X' % (a, b - 1)
        segs.append((a, b, path, title))
    em = Emitter(m, names, args.outdir, args.name, blob_min=args.blob_min, imm_macros=args.imm_macros)
    if args.ea:
        from mdassets import find_tilesets, find_teams, ident
        em.tilesets = find_tilesets(m)
        ptrs, teams = find_teams(m)
        used = set(names.names.values())
        cities = [t[1] for t in teams.values()]
        for p, (e, city, nick, arena) in teams.items():
            em.text_regions.add(p)
            if p not in names.names:
                n = 'Roster_' + ident(city) if city else 'Roster_%06X' % p
                if city and cities.count(city) > 1 and nick:
                    n = 'Roster_' + ident(city) + ident(nick)
                if n in used:
                    n += '_%06X' % p
                names.names[p] = n
                used.add(n)
            if city:
                names.comments.setdefault(p, 'roster: %s %s (%s)' % (city, nick, arena))
        print('tile sets: %d, teams: %d' % (len(em.tilesets), len(teams)), file=sys.stderr)
    em.emit(segs)
    for a, b, path, title in segs:
        print('%06X-%06X %s' % (a, b, path), file=sys.stderr)


if __name__ == '__main__':
    main()
