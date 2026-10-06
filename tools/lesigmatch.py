#!/usr/bin/env python3
#
# Matches the library signatures of omflib.py against the routines of a disassembled LE executable
# (ledisasm.py's JSON) and prints the routines whose code equals a library routine, the bytes covered by
# relocations ignored. Once a routine of a library module is found, the module's whole code segment is
# aligned with the executable, so the module's other routines (also its static ones) are placed too.
#
#   lesigmatch.py game.exe game.json --libs lib1 [lib2 ...] [--min 12] [--report out.json] [--names out.txt]
#
import argparse
import json
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from le import LEExecutable          # noqa: E402
import omflib                        # noqa: E402

def compile_pattern(hexpat):
    '''hex string with '..' wildcards -> (bytes, mask bytes)'''
    n = len(hexpat) // 2
    data = bytearray(n)
    mask = bytearray(n)
    for i in range(n):
        h = hexpat[2 * i: 2 * i + 2]
        if h != '..':
            data[i] = int(h, 16)
            mask[i] = 1
    return bytes(data), bytes(mask)

def matches(code, data, mask):
    for i in range(len(data)):
        if mask[i] and code[i] != data[i]:
            return False
    return True

def clean(name):
    '''Watcom register convention symbols end in "_", stack convention ones start with "_"'''
    if name.endswith('_') and not name.startswith('__'):
        return name[:-1]
    return name

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('exe')
    ap.add_argument('json')
    ap.add_argument('--libs', nargs='+', required=True, help='OMF libraries')
    ap.add_argument('--min', type=int, default=12, help='fixed bytes a signature needs')
    ap.add_argument('--names', help='write "address name ; library module" lines')
    ap.add_argument('--report', help='write a JSON report')
    args = ap.parse_args()
    le = LEExecutable(args.exe)
    le.apply_fixups()
    routines = json.load(open(args.json))['routines']
    by_addr = {r['addr']: r for r in routines}
    starts = sorted(by_addr)
    # signatures and module code of every library
    sigs = []
    modules = {}
    for path in args.libs:
        lib = os.path.basename(path)
        for mod in omflib.read_modules(open(path, 'rb').read()):
            key = (lib, mod.name)
            modules[key] = mod
            for s in omflib.signatures(mod):
                d, m = compile_pattern(s['pattern'])
                if sum(m) < args.min:
                    continue
                sigs.append((lib, mod.name, s['name'], s['offset'], d, m, s['segment']))
    print(f"{len(sigs)} signatures from {len(modules)} modules", file=sys.stderr)
    # index by the first fixed bytes for speed
    index = {}
    for sg in sigs:
        d, m = sg[4], sg[5]
        k = next((i for i in range(len(m)) if m[i] and i + 1 < len(m) and m[i + 1]), None)
        key = (k, d[k], d[k + 1]) if k is not None else None
        index.setdefault(key, []).append(sg)
    found = {}                                   # addr -> list of (lib, module, name, offset)
    for a in starts:
        code = le.read(a, 4096) or b''
        cands = []
        for key, group in index.items():
            if key is None:
                continue
            k, b0, b1 = key
            if k + 1 >= len(code) or code[k] != b0 or code[k + 1] != b1:
                continue
            for lib, modname, name, off, d, m, seg in group:
                if len(code) >= len(d) and matches(code, d, m):
                    cands.append((lib, modname, name, off, sum(m), seg))
        if cands:
            best = max(c[4] for c in cands)
            found[a] = [c for c in cands if c[4] == best]
    # align whole modules: every public / local symbol of a matched module's segment
    placed = {}
    for a, cands in found.items():
        if len(cands) != 1:
            continue
        lib, modname, name, off, fixed, seg = cands[0]
        base = a - off
        mod = modules[(lib, modname)]
        for sname, d, m in omflib.module_code(mod):
            if sname != seg:
                continue
            code = le.read(base, len(d)) or b''
            if len(code) < len(d) or not matches(code, d, bytes(1 if x == 1 else 0 for x in m)):
                continue
            for pname, sidx, poff, local in mod.pubs:
                if mod.segs[sidx][0] == sname:
                    placed.setdefault(base + poff, set()).add((lib, modname, pname))
            # routines of the executable inside the module without a symbol: static routines
            for r in starts:
                if base <= r < base + len(d):
                    placed.setdefault(r, set()).add((lib, modname, f'{modname}+{r - base:x}'))
    report = []
    for a in starts:
        r = by_addr[a]
        c = found.get(a)
        p = placed.get(a)
        if not c and not p:
            continue
        names = sorted({clean(x[2]) for x in c}) if c else []
        if not names and p:
            names = sorted({clean(x[2]) for x in p})
        mods = sorted({f'{x[0]}:{x[1]}' for x in (c or [])} | {f'{x[0]}:{x[1]}' for x in (p or [])})
        report.append({'addr': a, 'current': r['name'], 'size': r['size'], 'names': names, 'modules': mods,
                       'direct': bool(c), 'fixed': c[0][4] if c else 0})
    hits = [x for x in report]
    named_ok = sum(1 for x in hits if not x['current'].startswith('sub_') and x['current'] in x['names'])
    print(f"{len(hits)} routines matched ({sum(1 for x in hits if x['direct'])} directly), "
          f"{sum(1 for x in hits if x['current'].startswith('sub_'))} of them unnamed, "
          f"{named_ok} named ones confirmed", file=sys.stderr)
    if args.report:
        json.dump(report, open(args.report, 'w'), indent=0)
    if args.names:
        # unnamed routines with one candidate, in the names list format of the map tools
        with open(args.names, 'w') as f:
            for x in report:
                if x['current'].startswith('sub_') and len(x['names']) == 1:
                    f.write(f"{x['addr']:x} {x['names'][0]} ; {' '.join(x['modules'])}\n")
    for x in report:
        print(f"{x['addr']:06x} {x['current']:<28} {'/'.join(x['names'])[:60]:<60} {' '.join(x['modules'])[:80]}"
              + ('' if x['direct'] else ' (module)'))

if __name__ == '__main__':
    main()
