#!/usr/bin/env python3
#
# Parser for LE/LX ("Linear Executable") binaries, as produced by the Watcom linker for
# 32-bit protected mode DOS programs running under DOS/4G(W), DOS/32A, PMODE/W etc.
#
# The mzretools C++ tools only understand real mode 8086 MZ executables, but a lot of
# later DOS games (1993+) are shipped as an MZ stub (the DOS extender) with a bound LE
# image appended. This module locates the LE header behind the stub(s), reads the object
# table, object page map and fixup records, and can produce a flat, relocated memory image
# of the program that is suitable for 32-bit disassembly.
#
import struct
import sys

# LE/LX object flags
OBJ_READABLE   = 0x0001
OBJ_WRITABLE   = 0x0002
OBJ_EXECUTABLE = 0x0004
OBJ_RESOURCE   = 0x0008
OBJ_DISCARD    = 0x0010
OBJ_SHARED     = 0x0020
OBJ_PRELOAD    = 0x0040
OBJ_INVALID    = 0x0080
OBJ_ZEROFILL   = 0x0100
OBJ_RESIDENT   = 0x0200
OBJ_ALIAS1616  = 0x1000
OBJ_BIG        = 0x2000  # 32-bit default operand/address size
OBJ_CONFORMING = 0x4000
OBJ_IOPL       = 0x8000

# fixup source types (low nibble of the source byte)
SRC_BYTE        = 0x00
SRC_SEL16       = 0x02
SRC_PTR1616     = 0x03
SRC_OFF16       = 0x05
SRC_PTR1632     = 0x06
SRC_OFF32       = 0x07
SRC_REL32       = 0x08
SRC_ALIAS       = 0x10
SRC_LIST        = 0x20
SRC_NAMES = { SRC_BYTE: 'byte', SRC_SEL16: 'sel16', SRC_PTR1616: 'ptr16:16', SRC_OFF16: 'off16',
              SRC_PTR1632: 'ptr16:32', SRC_OFF32: 'off32', SRC_REL32: 'rel32' }
SRC_SIZE = { SRC_BYTE: 1, SRC_SEL16: 2, SRC_PTR1616: 4, SRC_OFF16: 2, SRC_PTR1632: 6, SRC_OFF32: 4, SRC_REL32: 4 }

# fixup target flags
TGT_INTERNAL    = 0x00
TGT_IMPORD      = 0x01
TGT_IMPNAME     = 0x02
TGT_ENTRY       = 0x03
TGT_TYPEMASK    = 0x03
TGT_ADDITIVE    = 0x04
TGT_CHAIN       = 0x08
TGT_OFF32       = 0x10
TGT_ADD32       = 0x20
TGT_OBJ16       = 0x40
TGT_ORD8        = 0x80

HEADER_FIELDS = [
    ('signature', '2s'), ('byte_order', 'B'), ('word_order', 'B'), ('format_level', 'I'),
    ('cpu_type', 'H'), ('os_type', 'H'), ('module_version', 'I'), ('module_flags', 'I'),
    ('num_pages', 'I'), ('eip_object', 'I'), ('eip', 'I'), ('esp_object', 'I'), ('esp', 'I'),
    ('page_size', 'I'), ('last_page_size', 'I'), ('fixup_size', 'I'), ('fixup_checksum', 'I'),
    ('loader_size', 'I'), ('loader_checksum', 'I'), ('object_table', 'I'), ('num_objects', 'I'),
    ('object_page_table', 'I'), ('object_iter_pages', 'I'), ('resource_table', 'I'),
    ('num_resources', 'I'), ('resident_names', 'I'), ('entry_table', 'I'), ('module_directives', 'I'),
    ('num_module_directives', 'I'), ('fixup_page_table', 'I'), ('fixup_record_table', 'I'),
    ('import_modules', 'I'), ('num_import_modules', 'I'), ('import_procs', 'I'),
    ('page_checksums', 'I'), ('data_pages', 'I'), ('num_preload_pages', 'I'),
    ('nonresident_names', 'I'), ('nonresident_names_len', 'I'), ('nonresident_names_checksum', 'I'),
    ('auto_data_object', 'I'), ('debug_info', 'I'), ('debug_info_len', 'I'),
    ('instance_preload', 'I'), ('instance_demand', 'I'), ('heap_size', 'I'),
]
HEADER_FORMAT = '<' + ''.join(f for _, f in HEADER_FIELDS)
HEADER_SIZE = struct.calcsize(HEADER_FORMAT)

CPU_NAMES = { 1: '80286', 2: '80386', 3: '80486', 4: '80586' }
OS_NAMES = { 0: 'unknown', 1: 'OS/2', 2: 'Windows', 3: 'DOS 4.x', 4: 'Windows 386' }

class LEError(Exception):
    pass

class LEObject:
    def __init__(self, index, vsize, base, flags, page_index, num_pages):
        self.index = index          # 1-based object number
        self.vsize = vsize          # virtual size in memory
        self.base = base            # relocation base address (preferred load address)
        self.flags = flags
        self.page_index = page_index  # 1-based index into the object page table
        self.num_pages = num_pages
        self.data = None            # bytearray of vsize bytes after loading

    def is_code(self):
        return bool(self.flags & OBJ_EXECUTABLE)

    def is_32bit(self):
        return bool(self.flags & OBJ_BIG)

    def contains(self, addr):
        return self.base <= addr < self.base + self.vsize

    def flag_str(self):
        names = []
        for bit, name in ((OBJ_READABLE, 'R'), (OBJ_WRITABLE, 'W'), (OBJ_EXECUTABLE, 'X'),
                          (OBJ_RESOURCE, 'rsrc'), (OBJ_DISCARD, 'discard'), (OBJ_SHARED, 'shared'),
                          (OBJ_PRELOAD, 'preload'), (OBJ_ZEROFILL, 'zerofill'), (OBJ_RESIDENT, 'resident'),
                          (OBJ_ALIAS1616, 'alias16:16'), (OBJ_BIG, '32bit'), (OBJ_CONFORMING, 'conforming')):
            if self.flags & bit:
                names.append(name)
        return ' '.join(names)

    def kind(self):
        if self.is_code():
            return 'CODE'
        if self.flags & OBJ_WRITABLE:
            return 'DATA'
        return 'CONST'

    def __str__(self):
        return (f"object {self.index}: base 0x{self.base:x}, size 0x{self.vsize:x}, flags 0x{self.flags:x} "
                f"({self.flag_str()}), pages {self.page_index}-{self.page_index + self.num_pages - 1}")

class Fixup:
    '''A single resolved fixup location'''
    def __init__(self, src_type, src_addr, obj, target, src_flags, tgt_flags, page):
        self.src_type = src_type    # SRC_* constant (without alias/list flags)
        self.src_addr = src_addr    # linear address of the patched location
        self.obj = obj              # target object number (internal fixups)
        self.target = target        # target offset within object (None for pure selector fixups)
        self.src_flags = src_flags
        self.tgt_flags = tgt_flags
        self.page = page            # 1-based page number the record belongs to

    def target_addr(self, objects):
        if self.target is None or self.obj is None:
            return None
        return objects[self.obj - 1].base + self.target

    def __str__(self):
        return f"{SRC_NAMES.get(self.src_type, hex(self.src_type))} @0x{self.src_addr:x} -> obj {self.obj}:0x{(self.target or 0):x}"

class LEExecutable:
    def __init__(self, path):
        self.path = path
        with open(path, 'rb') as f:
            self.raw = f.read()
        self.le_offset, self.stub_offset = self._locate()
        vals = struct.unpack_from(HEADER_FORMAT, self.raw, self.le_offset)
        self.header = dict(zip((n for n, _ in HEADER_FIELDS), vals))
        self.format = self.header['signature'].decode()
        self.objects = []
        self.page_map = []   # list of (page number, flags) per logical page
        self.fixups = []
        self.fixup_errors = 0
        self._read_objects()
        self._read_page_map()
        self._load_objects()
        self._read_fixups()
        self.image_applied = False

    # --- locating the LE header ---------------------------------------------------------------
    def _locate(self):
        '''Find the LE/LX header and the MZ stub it belongs to.
        Returns (le_offset, stub_offset). Offsets inside the LE header which the format
        defines as "relative to the start of the file" (data pages, non-resident names) are in
        reality relative to the MZ stub whose e_lfanew points at the LE header. When the program
        is bound with a DOS extender (e.g. 4GWBIND), the extender is prepended, so the owning
        stub is not at file offset 0.'''
        raw = self.raw
        if raw[:2] not in (b'MZ', b'ZM'):
            raise LEError(f"{self.path} is not an MZ executable")
        # collect all MZ candidates whose e_lfanew points at an LE/LX signature
        candidates = []
        pos = 0
        while True:
            pos = raw.find(b'MZ', pos)
            if pos < 0 or pos + 0x40 > len(raw):
                break
            lfanew = struct.unpack_from('<I', raw, pos + 0x3c)[0]
            le = pos + lfanew
            if 0 < lfanew and le + 4 <= len(raw) and raw[le:le + 2] in (b'LE', b'LX') and raw[le + 2:le + 4] == b'\0\0':
                candidates.append((le, pos))
            pos += 2
        if candidates:
            # prefer the last one, the outer stubs of bound executables never point at the LE
            return candidates[-1]
        # fallback: brute force search for a plausible LE header, assume offsets relative to 0
        pos = 0
        while True:
            pos = raw.find(b'LE\0\0', pos)
            if pos < 0:
                break
            cpu, os_ = struct.unpack_from('<HH', raw, pos + 8)
            if cpu in CPU_NAMES and os_ in OS_NAMES:
                return pos, 0
            pos += 2
        raise LEError(f"unable to locate LE/LX header in {self.path}")

    def hdr(self, name):
        return self.header[name]

    # --- object table and page map ---------------------------------------------------------------
    def _read_objects(self):
        off = self.le_offset + self.hdr('object_table')
        for i in range(self.hdr('num_objects')):
            vsize, base, flags, pidx, npages, _ = struct.unpack_from('<6I', self.raw, off + i * 24)
            self.objects.append(LEObject(i + 1, vsize, base, flags, pidx, npages))

    def _read_page_map(self):
        off = self.le_offset + self.hdr('object_page_table')
        for i in range(self.hdr('num_pages')):
            e = self.raw[off + i * 4: off + i * 4 + 4]
            if self.format == 'LE':
                # LE: 24 bit big-endian page number followed by a flags byte
                num = (e[0] << 16) | (e[1] << 8) | e[2]
                flags = e[3]
                self.page_map.append((num, flags, None))
            else:
                # LX: 32 bit page data offset (shifted), 16 bit data size, 16 bit flags
                poff, psize, pflags = struct.unpack_from('<IHH', self.raw, off + i * 8)
                self.page_map.append((poff, pflags, psize))

    def page_file_offset(self, logical_page):
        '''File offset and size of a 1-based logical page's data'''
        num, flags, size = self.page_map[logical_page - 1]
        psize = self.hdr('page_size')
        base = self.stub_offset + self.hdr('data_pages')
        if self.format == 'LE':
            if flags not in (0, ):  # 0 = legal physical page
                return None, 0
            fofs = base + (num - 1) * psize
            if logical_page == self.hdr('num_pages'):
                return fofs, self.hdr('last_page_size')
            return fofs, psize
        else:
            shift = self.hdr('last_page_size')  # LX: page offset shift
            if flags not in (0, ):
                return None, 0
            return base + (num << shift), size

    def _load_objects(self):
        psize = self.hdr('page_size')
        for obj in self.objects:
            data = bytearray(obj.vsize if obj.vsize else obj.num_pages * psize)
            for i in range(obj.num_pages):
                lp = obj.page_index + i
                fofs, size = self.page_file_offset(lp)
                if fofs is None:
                    continue
                chunk = self.raw[fofs:fofs + size]
                dst = i * psize
                if dst >= len(data):
                    break
                chunk = chunk[:len(data) - dst]
                data[dst:dst + len(chunk)] = chunk
            obj.data = data

    # --- fixups -----------------------------------------------------------------------------
    def _read_fixups(self):
        raw = self.raw
        le = self.le_offset
        fpt = le + self.hdr('fixup_page_table')
        frt = le + self.hdr('fixup_record_table')
        psize = self.hdr('page_size')
        # map logical page -> (object, page index within object)
        page_owner = {}
        for obj in self.objects:
            for i in range(obj.num_pages):
                page_owner[obj.page_index + i] = (obj, i)
        for page in range(1, self.hdr('num_pages') + 1):
            start, end = struct.unpack_from('<II', raw, fpt + (page - 1) * 4)
            owner = page_owner.get(page)
            if owner is None:
                continue
            obj, pidx = owner
            page_base = obj.base + pidx * psize
            pos = frt + start
            stop = frt + end
            while pos < stop:
                src = raw[pos]; flags = raw[pos + 1]; pos += 2
                stype = src & 0x0f
                if src & SRC_LIST:
                    count = raw[pos]; pos += 1
                    srcoffs = None
                else:
                    srcoff = struct.unpack_from('<h', raw, pos)[0]; pos += 2
                    srcoffs = [srcoff]
                ttype = flags & TGT_TYPEMASK
                tobj = None; toff = None
                if ttype == TGT_INTERNAL:
                    if flags & TGT_OBJ16:
                        tobj = struct.unpack_from('<H', raw, pos)[0]; pos += 2
                    else:
                        tobj = raw[pos]; pos += 1
                    if stype != SRC_SEL16:
                        if flags & TGT_OFF32:
                            toff = struct.unpack_from('<I', raw, pos)[0]; pos += 4
                        else:
                            toff = struct.unpack_from('<H', raw, pos)[0]; pos += 2
                elif ttype in (TGT_IMPORD, TGT_IMPNAME):
                    # module ordinal
                    pos += 2 if flags & TGT_OBJ16 else 1
                    if ttype == TGT_IMPORD:
                        if flags & TGT_ORD8:
                            pos += 1
                        elif flags & TGT_OFF32:
                            pos += 4
                        else:
                            pos += 2
                    else:
                        pos += 4 if flags & TGT_OFF32 else 2
                    self.fixup_errors += 1  # imports not supported in DOS executables
                elif ttype == TGT_ENTRY:
                    pos += 2 if flags & TGT_OBJ16 else 1
                    self.fixup_errors += 1
                if flags & TGT_ADDITIVE:
                    add = struct.unpack_from('<I' if flags & TGT_ADD32 else '<H', raw, pos)[0]
                    pos += 4 if flags & TGT_ADD32 else 2
                    if toff is not None:
                        toff += add
                if srcoffs is None:
                    srcoffs = [struct.unpack_from('<h', raw, pos + 2 * k)[0] for k in range(count)]
                    pos += 2 * count
                if ttype != TGT_INTERNAL:
                    continue
                for so in srcoffs:
                    self.fixups.append(Fixup(stype, page_base + so, tobj, toff, src, flags, page))
        # a fixup straddling a page boundary is listed for both pages, dedup by address
        seen = {}
        for fx in self.fixups:
            seen[(fx.src_addr, fx.src_type)] = fx
        self.fixups = sorted(seen.values(), key=lambda f: f.src_addr)

    # --- flat image ---------------------------------------------------------------------------
    def apply_fixups(self, selectors=None):
        '''Patch the loaded object data so that all internal offset fixups contain the target linear
        address (object base + offset), as if loaded at the preferred base addresses in a flat model.
        Selector fixups are patched with a synthetic selector value (default: object number * 8).'''
        if self.image_applied:
            return
        for fx in self.fixups:
            obj = self.object_at(fx.src_addr)
            if obj is None:
                continue
            o = fx.src_addr - obj.base
            tgt = fx.target_addr(self.objects)
            sel = selectors[fx.obj] if selectors else (fx.obj or 0) * 8
            size = SRC_SIZE.get(fx.src_type, 0)
            if o < 0 or o + size > len(obj.data):
                continue
            if fx.src_type == SRC_OFF32 and tgt is not None:
                struct.pack_into('<I', obj.data, o, tgt & 0xffffffff)
            elif fx.src_type == SRC_REL32 and tgt is not None:
                struct.pack_into('<I', obj.data, o, (tgt - (fx.src_addr + 4)) & 0xffffffff)
            elif fx.src_type == SRC_OFF16 and tgt is not None:
                struct.pack_into('<H', obj.data, o, tgt & 0xffff)
            elif fx.src_type == SRC_SEL16:
                struct.pack_into('<H', obj.data, o, sel & 0xffff)
            elif fx.src_type == SRC_PTR1632 and tgt is not None:
                struct.pack_into('<IH', obj.data, o, tgt & 0xffffffff, sel & 0xffff)
            elif fx.src_type == SRC_PTR1616 and tgt is not None:
                struct.pack_into('<HH', obj.data, o, tgt & 0xffff, sel & 0xffff)
            elif fx.src_type == SRC_BYTE and tgt is not None:
                obj.data[o] = tgt & 0xff
        self.image_applied = True

    def object_at(self, addr):
        for obj in self.objects:
            if obj.contains(addr):
                return obj
        return None

    def read(self, addr, size):
        obj = self.object_at(addr)
        if obj is None:
            return None
        o = addr - obj.base
        return bytes(obj.data[o:o + size])

    def read_u32(self, addr):
        b = self.read(addr, 4)
        if b is None or len(b) < 4:
            return None
        return struct.unpack('<I', b)[0]

    def entry_point(self):
        obj = self.objects[self.hdr('eip_object') - 1]
        return obj.base + self.hdr('eip')

    def initial_stack(self):
        obj = self.objects[self.hdr('esp_object') - 1]
        return obj.base + self.hdr('esp')

    def names(self, which='resident'):
        '''Read the resident or non-resident name table as a list of (name, ordinal)'''
        if which == 'resident':
            off = self.le_offset + self.hdr('resident_names')
        else:
            if not self.hdr('nonresident_names'):
                return []
            off = self.stub_offset + self.hdr('nonresident_names')
        out = []
        while off < len(self.raw):
            n = self.raw[off]
            if n == 0:
                break
            name = self.raw[off + 1: off + 1 + n].decode('latin-1')
            ordinal = struct.unpack_from('<H', self.raw, off + 1 + n)[0]
            out.append((name, ordinal))
            off += 3 + n
        return out

    def dump(self, out=sys.stdout, fixups=False):
        h = self.header
        p = lambda s: print(s, file=out)
        p(f"--- {self.path}: {self.format} executable")
        p(f"\tLE header at file offset 0x{self.le_offset:x}, owning MZ stub at 0x{self.stub_offset:x}")
        p(f"\tcpu = {CPU_NAMES.get(h['cpu_type'], hex(h['cpu_type']))}, os = {OS_NAMES.get(h['os_type'], hex(h['os_type']))}, module flags = 0x{h['module_flags']:x}")
        p(f"\tpages = {h['num_pages']} x 0x{h['page_size']:x}, last page size = 0x{h['last_page_size']:x}")
        p(f"\tdata pages at file offset 0x{self.stub_offset + h['data_pages']:x}")
        p(f"\tentry (cs:eip) = object {h['eip_object']}:0x{h['eip']:x} -> linear 0x{self.entry_point():x}")
        p(f"\tstack (ss:esp) = object {h['esp_object']}:0x{h['esp']:x} -> linear 0x{self.initial_stack():x}")
        p(f"\tauto data object = {h['auto_data_object']}")
        p(f"\tfixup section size = 0x{h['fixup_size']:x}, loader section size = 0x{h['loader_size']:x}")
        for n, o in self.names('resident'):
            p(f"\tresident name: '{n}' (ordinal {o})")
        for n, o in self.names('nonresident'):
            p(f"\tnon-resident name: '{n}' (ordinal {o})")
        p("--- objects:")
        for obj in self.objects:
            p(f"\t{obj} [{obj.kind()}]")
        counts = {}
        for fx in self.fixups:
            key = (SRC_NAMES.get(fx.src_type, hex(fx.src_type)), fx.obj)
            counts[key] = counts.get(key, 0) + 1
        p(f"--- fixups: {len(self.fixups)} internal" + (f", {self.fixup_errors} unsupported (import/entry)" if self.fixup_errors else ''))
        for (t, o), c in sorted(counts.items(), key=lambda x: (x[0][0], x[0][1] or 0)):
            p(f"\t{t} -> object {o}: {c}")
        if fixups:
            for fx in self.fixups:
                p(f"\t{fx}")

def main():
    import argparse
    ap = argparse.ArgumentParser(description='Show information about an LE/LX executable (DOS/4GW, DOS/32A, ...)')
    ap.add_argument('exe')
    ap.add_argument('--fixups', action='store_true', help='list all fixup records')
    ap.add_argument('--extract', metavar='PREFIX', help='write relocated object images to PREFIX.objN.bin')
    ap.add_argument('--raw', action='store_true', help='with --extract, do not apply fixups')
    args = ap.parse_args()
    try:
        le = LEExecutable(args.exe)
    except LEError as e:
        print(f"ERROR: {e}")
        sys.exit(1)
    le.dump(fixups=args.fixups)
    if args.extract:
        if not args.raw:
            le.apply_fixups()
        for obj in le.objects:
            path = f"{args.extract}.obj{obj.index}.bin"
            with open(path, 'wb') as f:
                f.write(obj.data)
            print(f"Wrote object {obj.index} (base 0x{obj.base:x}, 0x{len(obj.data):x} bytes) to {path}")

if __name__ == '__main__':
    main()
