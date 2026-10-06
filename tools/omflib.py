#!/usr/bin/env python3
#
# Reads OMF object libraries (.lib, as written by Watcom / Microsoft / Borland librarians) and produces
# byte signatures of their public routines: the code bytes of each public symbol up to the next symbol of
# its segment, with the bytes covered by fixups masked out. lesigmatch.py matches them against the routines
# of a disassembled LE executable.
#
#   omflib.py LIB [LIB ...] --json sigs.json      write the signatures
#   omflib.py LIB --list                          list modules and their public symbols
#
import json
import struct
import sys

# record types (the odd numbers are the 32 bit variants)
THEADR, LHEADR, COMENT, MODEND, MODEND32 = 0x80, 0x82, 0x88, 0x8a, 0x8b
EXTDEF, PUBDEF, PUBDEF32, LINNUM, LINNUM32 = 0x8c, 0x90, 0x91, 0x94, 0x95
LNAMES, SEGDEF, SEGDEF32, GRPDEF, FIXUPP, FIXUPP32 = 0x96, 0x98, 0x99, 0x9a, 0x9c, 0x9d
LEDATA, LEDATA32, LIDATA, LIDATA32, COMDEF = 0xa0, 0xa1, 0xa2, 0xa3, 0xb0
LEXTDEF, LEXTDEF32, LPUBDEF, LPUBDEF32, CEXTDEF = 0xb4, 0xb5, 0xb6, 0xb7, 0xbc
COMDAT, COMDAT32 = 0xc2, 0xc3
LIBHDR, LIBEND = 0xf0, 0xf1

class Reader:
    def __init__(self, data, pos=0):
        self.d = data
        self.p = pos

    def u8(self):
        v = self.d[self.p]; self.p += 1
        return v

    def u16(self):
        v = struct.unpack_from('<H', self.d, self.p)[0]; self.p += 2
        return v

    def u32(self):
        v = struct.unpack_from('<I', self.d, self.p)[0]; self.p += 4
        return v

    def index(self):
        b = self.u8()
        if b & 0x80:
            return ((b & 0x7f) << 8) | self.u8()
        return b

    def name(self):
        n = self.u8()
        s = self.d[self.p:self.p + n].decode('latin-1'); self.p += n
        return s

    def off(self, is32):
        return self.u32() if is32 else self.u16()

class Module:
    def __init__(self, name):
        self.name = name
        self.lnames = ['']
        self.segs = [None]          # [name, class, length, bytearray, mask bytearray]
        self.pubs = []              # (name, seg index, offset, local)
        self.externs = ['']

def read_modules(data):
    '''Yields the modules of an OMF library or object file'''
    p = 0
    page = 16
    if data and data[0] == LIBHDR:
        page = struct.unpack_from('<H', data, 1)[0] + 3
        p = page
    mod = None
    last_data = None                # (seg, offset, is32) of the last LEDATA for its FIXUPP
    while p + 3 <= len(data):
        rtype = data[p]
        rlen = struct.unpack_from('<H', data, p + 1)[0]
        body = data[p + 3: p + 3 + rlen - 1]
        rec_start = p
        p += 3 + rlen
        if rtype == LIBEND:
            break
        if rtype in (THEADR, LHEADR):
            mod = Module(Reader(body).name())
            last_data = None
            continue
        if mod is None:
            continue
        r = Reader(body)
        is32 = rtype & 1
        if rtype == LNAMES:
            while r.p < len(body):
                mod.lnames.append(r.name())
        elif rtype in (SEGDEF, SEGDEF32):
            attr = r.u8()
            if (attr >> 5) == 0:
                r.u16(); r.u8()     # absolute frame
            length = r.off(is32)
            name = r.index(); cls = r.index(); r.index()
            if attr & 2:            # big: 64K / 4G
                length = 0x10000 if not is32 else 0x100000000
            length = min(length, 0x100000)
            mod.segs.append([mod.lnames[name], mod.lnames[cls], length, bytearray(length), bytearray(length)])
        elif rtype in (EXTDEF, LEXTDEF, LEXTDEF32, CEXTDEF):
            while r.p < len(body):
                if rtype == CEXTDEF:
                    mod.externs.append(mod.lnames[r.index()]); r.index()
                else:
                    mod.externs.append(r.name()); r.index()
        elif rtype in (PUBDEF, PUBDEF32, LPUBDEF, LPUBDEF32):
            r.index()                # group
            seg = r.index()
            if seg == 0:
                r.u16()
            while r.p < len(body):
                n = r.name(); off = r.off(is32); r.index()
                mod.pubs.append((n, seg, off, rtype in (LPUBDEF, LPUBDEF32)))
        elif rtype in (LEDATA, LEDATA32):
            seg = r.index(); off = r.off(is32)
            chunk = body[r.p:]
            s = mod.segs[seg]
            if off + len(chunk) > len(s[3]):
                s[3].extend(bytes(off + len(chunk) - len(s[3])))
                s[4].extend(bytes(off + len(chunk) - len(s[4])))
            s[3][off:off + len(chunk)] = chunk
            for i in range(off, off + len(chunk)):
                s[4][i] = 1
            last_data = (seg, off, is32)
        elif rtype in (LIDATA, LIDATA32):
            last_data = None         # iterated data: not code, ignored
        elif rtype in (FIXUPP, FIXUPP32):
            while r.p < len(body):
                b = r.u8()
                if not b & 0x80:
                    # THREAD subrecord: methods 0..2 carry an index, 3 a frame number
                    method = (b >> 2) & 7
                    if (b & 0x40) == 0:
                        method &= 3
                    if method < 3:
                        r.index()
                    elif method == 3:
                        r.u16()
                    continue
                locat = ((b << 8) | r.u8())
                loc_type = (locat >> 10) & 0xf
                data_off = locat & 0x3ff
                fixdat = r.u8()
                if not fixdat & 0x80:     # frame given explicitly
                    if ((fixdat >> 4) & 7) < 3:
                        r.index()
                if not fixdat & 0x08:     # target given explicitly
                    r.index()
                if not fixdat & 0x04:     # displacement present
                    r.off(is32)
                size = {0: 1, 1: 2, 2: 2, 3: 4, 4: 1, 5: 2, 9: 4, 11: 6, 13: 4}.get(loc_type, 2)
                if last_data:
                    seg, off, _ = last_data
                    s = mod.segs[seg]
                    for i in range(size):
                        k = off + data_off + i
                        if k < len(s[4]):
                            s[4][k] = 2       # masked
        elif rtype in (COMDAT, COMDAT32):
            pass                     # not used by the Watcom 386 libraries
        elif rtype in (MODEND, MODEND32):
            yield mod
            mod = None
            last_data = None
            if page > 16 or (data and data[0] == LIBHDR):
                # modules of a library start on a page boundary
                p = (p + page - 1) // page * page

def signatures(mod, min_len=4):
    '''Signatures of the public code symbols of a module: dict(name, module, offset, bytes hex with
    '..' for masked bytes, length)'''
    out = []
    by_seg = {}
    for name, seg, off, local in mod.pubs:
        if 0 < seg < len(mod.segs):
            by_seg.setdefault(seg, []).append((off, name, local))
    for seg, syms in by_seg.items():
        sname, cls, length, data, mask = mod.segs[seg]
        if 'CODE' not in cls.upper():
            continue
        syms.sort()
        end_all = len(data)
        while end_all > 0 and mask[end_all - 1] == 0:
            end_all -= 1
        for k, (off, name, local) in enumerate(syms):
            end = syms[k + 1][0] if k + 1 < len(syms) else end_all
            if end - off < min_len:
                continue
            pat = []
            for i in range(off, end):
                pat.append('..' if mask[i] != 1 else '%02x' % data[i])
            out.append({'name': name, 'module': mod.name, 'segment': sname, 'offset': off,
                        'length': end - off, 'pattern': ''.join(pat), 'local': local,
                        'module_offset': off, 'module_code': end_all})
    return out

def module_code(mod):
    '''The code segments of a module as [(segment name, bytes, mask)]'''
    return [(s[0], bytes(s[3]), bytes(s[4])) for s in mod.segs[1:] if s and 'CODE' in s[1].upper()]

def main():
    import argparse
    ap = argparse.ArgumentParser(description='OMF library signatures')
    ap.add_argument('libs', nargs='+')
    ap.add_argument('--json')
    ap.add_argument('--list', action='store_true')
    args = ap.parse_args()
    sigs = []
    for path in args.libs:
        data = open(path, 'rb').read()
        for mod in read_modules(data):
            ss = signatures(mod)
            if args.list:
                print(f"{path}: {mod.name}: " + ', '.join(f"{s['name']}@{s['offset']:x}/{s['length']}" for s in ss))
            for s in ss:
                s['library'] = path.split('/')[-1]
            sigs.extend(ss)
    if args.json:
        with open(args.json, 'w') as f:
            json.dump(sigs, f, indent=0)
        print(f"{len(sigs)} signatures written to {args.json}", file=sys.stderr)

if __name__ == '__main__':
    main()
