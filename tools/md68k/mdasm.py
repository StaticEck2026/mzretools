"""
Emit a Mega Drive ROM disassembly as a SNASM68K / asm68k compatible source
tree from a Mapper result.

Layout of the generated tree (relative to the output directory):

    <name>.asm          main file including everything in ROM order
    inc/genesis.inc     hardware equates
    inc/ram.inc         work RAM equates (one per referenced address)
    inc/macros.inc      helper macros
    src/*.asm           code modules (code with the small data between routines)
    data/*.asm          data modules (tables, text, incbin of large blobs)
    data/bin/*.bin      large binary blobs
    <name>.names        editable symbol names (read back on the next run)
"""

import os
import re
import struct
from collections import defaultdict

from m68k import Decoder, Invalid
from mdmap import Mapper, UNKNOWN, CODE, CODE_CONT, DATA

HW_NAMES = {
    0xA00000: 'Z80_RAM', 0xA01FFF: 'Z80_RAM_END', 0xA02000: 'Z80_RAM_END2',
    0xA04000: 'Z80_YM2612_A0', 0xA04001: 'Z80_YM2612_D0', 0xA04002: 'Z80_YM2612_A1', 0xA04003: 'Z80_YM2612_D1',
    0xA10000: 'IO_BASE', 0xA10001: 'HW_VERSION', 0xA10008: 'IO_CTRL1_L', 0xA1000C: 'IO_CTRL3_W', 0xA10003: 'IO_DATA1', 0xA10005: 'IO_DATA2', 0xA10007: 'IO_DATA3',
    0xA10009: 'IO_CTRL1', 0xA1000B: 'IO_CTRL2', 0xA1000D: 'IO_CTRL3',
    0xA1000F: 'IO_TXDATA1', 0xA10011: 'IO_RXDATA1', 0xA10013: 'IO_SCTRL1',
    0xA10015: 'IO_TXDATA2', 0xA10017: 'IO_RXDATA2', 0xA10019: 'IO_SCTRL2',
    0xA1001B: 'IO_TXDATA3', 0xA1001D: 'IO_RXDATA3', 0xA1001F: 'IO_SCTRL3',
    0xA11000: 'MEM_MODE', 0xA11100: 'Z80_BUSREQ', 0xA11200: 'Z80_RESET',
    0xA14000: 'TMSS_SEGA', 0xA14101: 'TMSS_CART',
    0xC00000: 'VDP_DATA', 0xC00002: 'VDP_DATA2', 0xC00004: 'VDP_CTRL', 0xC00006: 'VDP_CTRL2',
    0xC00008: 'VDP_HVCOUNTER', 0xC0000A: 'VDP_HVCOUNTER2', 0xC00011: 'PSG',
}

HEADER_FIELDS = [
    (0x000, 'VectorTable', 'exception vectors'),
    (0x100, 'Header_Console', 'console name'), (0x110, 'Header_Copyright', 'copyright / release date'),
    (0x120, 'Header_DomesticName', 'domestic name'), (0x150, 'Header_OverseasName', 'overseas name'),
    (0x180, 'Header_Serial', 'serial number'), (0x18E, 'Header_Checksum', 'checksum (over $200-$7FFFF)'),
    (0x190, 'Header_IO', 'I/O support'), (0x1A0, 'Header_RomStart', 'ROM start'), (0x1A4, 'Header_RomEnd', 'ROM end (as declared)'),
    (0x1A8, 'Header_RamStart', 'RAM start'), (0x1AC, 'Header_RamEnd', 'RAM end'), (0x1B0, 'Header_SRAM', 'SRAM info (none)'),
    (0x1BC, 'Header_Modem', 'modem info'), (0x1C8, 'Header_Notes', 'notes'), (0x1F0, 'Header_Region', 'region'),
]

IMM_LABEL_MNEMONICS = ('movea.l', 'pea', 'move.l', 'cmpa.l', 'cmpi.l', 'cmp.l', 'addi.l', 'subi.l', 'adda.l', 'suba.l')


def hexs(v):
    if v < 0:
        return '-$%X' % -v
    return '$%X' % v


class Names:
    """addr -> (name, comment) table, loaded from and saved to a text file."""

    def __init__(self, path):
        self.path = path
        self.names = {}
        self.comments = {}
        self.ram = {}
        self.ram_comments = {}
        if path and os.path.exists(path):
            self.load(path)

    def load(self, path):
        for line in open(path):
            line = line.rstrip('\n')
            if not line.strip() or line.startswith('#'):
                continue
            line = re.sub(r'\s+# \(not a label.*$', '', line)
            parts = line.split(None, 2)
            if len(parts) < 2:
                continue
            kind_addr, name = parts[0], parts[1]
            comment = parts[2] if len(parts) > 2 else ''
            if kind_addr.lower().startswith('ram:'):
                a = int(kind_addr[4:], 16)
                self.ram[a] = name
                if comment:
                    self.ram_comments[a] = comment
            else:
                a = int(kind_addr, 16)
                self.names[a] = name
                if comment:
                    self.comments[a] = comment

    def save(self, path, labels, ram_vars):
        with open(path, 'w') as f:
            f.write('# Symbol names for the disassembly.  Format: <hex addr> <name> [comment]\n')
            f.write('# RAM variables use "ram:<hex addr>".  Edit and re-run the generator.\n')
            # every entry is kept, also for addresses that are not labels in
            # this run (the analysis may change), so nothing is lost
            for a in sorted(self.names):
                n = self.names[a]
                c = self.comments.get(a, '')
                flag = '' if a in labels else '  # (not a label in the last run)'
                f.write('%06X %s%s%s\n' % (a, n, (' ' + c) if c else '', flag))
            f.write('\n')
            for a in sorted(self.ram):
                n = self.ram[a]
                c = self.ram_comments.get(a, '')
                f.write('ram:%06X %s%s\n' % (a, n, (' ' + c) if c else ''))


class Emitter:
    def __init__(self, m: Mapper, names: Names, outdir: str, name: str = 'rom',
                 blob_min=0x200, imm_macros=False):
        self.m = m
        self.rom = m.rom
        self.names = names
        self.outdir = outdir
        self.name = name
        self.blob_min = blob_min
        self.imm_macros = imm_macros
        self.rom_end = m.rom_end
        self.label_at = {}            # addr -> label name
        self.label_kind = {}          # addr -> kind
        self.extra_refs = set()       # addresses referenced inside items -> label+off
        self.ram_vars = {}            # addr -> name
        self.hw_vars = {}
        self.files = []               # (path, title)
        self.jmptbl_base = {}         # continuation of a split jump table -> table start
        self.tilesets = {}            # addr -> (count, pal_off, map_off, end)
        self.art_part = {}            # addr -> (base addr, 'tiles'|'pal'|'map')
        self.text_regions = set()     # label addrs whose data is text with binary fields (rosters)
        self.region_desc = {}         # addr -> comment line

    # ------------------------------------------------------------------
    # labels
    def collect_refs(self):
        """All ROM addresses referenced by operands, pointer tables, etc."""
        refs = set()
        for ins in self.m.insns.values():
            for o in ins.operands:
                if o.addr is not None and 0 <= o.addr < 0x200000:
                    refs.add(o.addr)
                if o.kind == 'imm' and o.imm_size == 4 and ins.mnemonic in IMM_LABEL_MNEMONICS:
                    v = o.imm
                    if not (0x200 <= v < self.rom_end):
                        continue
                    to_areg = ins.operands[-1].text.startswith(('a', 'sp'))
                    if v in self.m.labels or self.m.kind[v] == CODE:
                        refs.add(v)
                    elif ins.mnemonic in ('movea.l', 'pea', 'cmpa.l') or (to_areg and ins.mnemonic in ('adda.l', 'suba.l')):
                        refs.add(v)              # used as an address
                    elif ins.mnemonic in ('move.l', 'cmpi.l', 'cmp.l') and v >= 0x1000 and not v & 1 and self.m.kind[v] == UNKNOWN:
                        refs.add(v)              # pointer stored or compared
        for tbl, ents in self.m.jump_tables.items():
            refs.add(tbl)
            for _, t in ents:
                refs.add(t)
        for tbl, ents in self.m.ptr_tables.items():
            refs.add(tbl)
            refs.update(ents)
        for i in range(1, 64):
            v = struct.unpack('>I', self.rom[i * 4:i * 4 + 4])[0]
            if 0x200 <= v < self.rom_end:
                refs.add(v)
        return refs

    def item_start(self, a):
        """Start address of the instruction containing a, or a itself."""
        k = self.m.kind[a]
        if k == CODE_CONT:
            x = a
            while self.m.kind[x] != CODE:
                x -= 1
            return x
        return a

    def build_labels(self):
        m = self.m
        # RAM addresses used with absolute addressing: certainly variables
        self.ram_direct = set()
        for ins in m.insns.values():
            for o in ins.operands:
                if o.kind in ('absw', 'absl') and o.addr is not None and (o.addr & 0xFFFFFF) >= 0xFF0000:
                    self.ram_direct.add(o.addr & 0xFFFFFF)
        refs = self.collect_refs()
        for a in list(m.labels):
            refs.add(a)
        for a in sorted(refs):
            if not (0x200 <= a < 0x200000):
                continue
            if a >= self.rom_end:
                continue
            s = self.item_start(a)
            if s != a:
                self.extra_refs.add(a)
                a = s
            kind = m.labels.get(a)
            if kind is None:
                kind = 'loc' if m.kind[a] == CODE else 'data'
            if a in m.func_starts:
                kind = 'sub'
            self.label_kind[a] = kind
        # tile sets: header, tiles, palette and map get labels
        for a, (cnt, offA, offB, aend) in self.tilesets.items():
            self.label_kind[a] = 'art'
            for off, part in ((8, 'tiles'), (offA, 'pal'), (offB, 'map')):
                self.label_kind[a + off] = 'artpart'
                self.art_part[a + off] = (a, part)
            if aend is not None and aend < self.rom_end and aend not in self.label_kind and m.kind[aend] == UNKNOWN:
                # whatever follows the map is separate data
                self.label_kind[aend] = 'data'
        # data pointer tables inside data regions: found while emitting, but
        # their targets need labels now; do a pre-pass
        self.data_ptr_runs = {}
        self.find_data_pointer_runs()
        for a, kind in self.label_kind.items():
            self.label_at[a] = self.make_name(a, kind)
        self.label_at[self.rom_end] = 'ROM_Padding'
        self.label_kind[self.rom_end] = 'pad'

    def find_data_pointer_runs(self):
        """Runs of >= 3 longwords pointing inside the ROM in data regions."""
        m = self.m
        a = 0x200
        kind = m.kind
        rom = self.rom
        end = self.rom_end
        while a + 4 <= end:
            if kind[a] != UNKNOWN or a & 1:
                a += 1 if a & 1 else 2
                continue
            run = []
            b = a
            while b + 4 <= end and kind[b] == UNKNOWN and kind[b + 1] == UNKNOWN and kind[b + 2] == UNKNOWN and kind[b + 3] == UNKNOWN:
                v = struct.unpack('>I', rom[b:b + 4])[0]
                if not (0x100 <= v < end):
                    break
                if v in self.label_kind or v in m.labels:
                    run.append(v)
                elif v & 1 == 0 and b > a and len(run) >= 1:
                    run.append(v)
                elif v & 1 == 0:
                    run.append(v)
                else:
                    break
                b += 4
            # a run where the entries are already labels is good with 2,
            # otherwise 3 are needed, the table itself must be referenced by
            # code and most entries must point at something known
            run = [v for v in run if v >= 0x200]
            labelled = sum(1 for v in run if v in self.label_kind)
            # entries pointing into the middle of code are not pointers
            if any(m.kind[v] in (CODE, CODE_CONT) and v not in self.label_kind for v in run):
                run = []
            if (len(run) >= 3 and a in self.label_kind) or (len(run) >= 2 and labelled == len(run)):
                self.data_ptr_runs[a] = run
                for v in run:
                    s = self.item_start(v)
                    if s != v:
                        self.extra_refs.add(v)
                        v = s
                    if v not in self.label_kind:
                        self.label_kind[v] = 'loc' if m.kind[v] == CODE else 'data'
                a = b
            else:
                a += 2

    def make_name(self, a, kind):
        n = self.names.names.get(a)
        if n:
            return n
        if kind == 'sub':
            return 'sub_%06X' % a
        if kind == 'loc':
            return 'loc_%06X' % a
        if kind == 'jmptbl':
            return 'jmptbl_%06X' % a
        if kind == 'ptrtbl':
            return 'ptrtbl_%06X' % a
        if kind == 'inline':
            return 'inl_%06X' % a
        if kind == 'str':
            return 'str_%06X' % a
        if kind == 'art':
            return 'Art_%06X' % a
        if kind == 'artpart':
            base, part = self.art_part[a]
            return '%s_%s' % (self.make_name(base, 'art'), part.capitalize())
        if a in self.data_ptr_runs:
            return 'ptrs_%06X' % a
        return 'dat_%06X' % a

    def ram_name(self, a):
        a &= 0xFFFFFF
        n = self.names.ram.get(a)
        if not n:
            n = 'ram_%04X' % (a & 0xFFFF)
        self.ram_vars[a] = n
        return n

    def hw_name(self, a):
        n = HW_NAMES.get(a)
        if n is None and 0xA00000 < a < 0xA02000:
            self.hw_vars[0xA00000] = HW_NAMES[0xA00000]
            return 'Z80_RAM+$%X' % (a - 0xA00000)
        if n is None and 0xA04000 <= a < 0xA04004:
            n = HW_NAMES[0xA04000 + (a & 3)]
        if n is None:
            n = 'HW_%06X' % a
        self.hw_vars[a] = n
        return n

    def rom_ref(self, a):
        """Symbolic expression for ROM address a."""
        if a < 0x200:
            base = max(f for f in HEADER_FIELDS if f[0] <= a)
            return base[1] if base[0] == a else '%s+%d' % (base[1], a - base[0])
        if a in self.label_at:
            return self.label_at[a]
        if a >= self.rom_end:
            return 'ROM_Padding+%s' % hexs(a - self.rom_end) if a != self.rom_end else 'ROM_Padding'
        s = self.item_start(a)
        if s in self.label_at and s != a:
            return '%s+%d' % (self.label_at[s], a - s)
        return hexs(a)

    def addr_expr(self, a):
        """Symbol for any 32-bit address."""
        a &= 0xFFFFFFFF
        if a < 0x200000:
            return self.rom_ref(a)
        if (a & 0xFF000000) == 0xFF000000 and (a & 0xFFFFFF) >= 0xFF0000:
            return self.ram_name(a)
        if 0xFF0000 <= a <= 0xFFFFFF:
            return self.ram_name(a)
        if 0xA00000 <= a < 0xC00020:
            return self.hw_name(a)
        return hexs(a)

    # ------------------------------------------------------------------
    def render_operand(self, ins, o):
        if o.kind == 'absw':
            return '(%s).w' % self.addr_expr(o.addr)
        if o.kind == 'absl':
            return '(%s).l' % self.addr_expr(o.addr)
        if o.kind == 'pcrel':
            return '%s(pc)' % self.rom_ref(o.addr)
        if o.kind == 'pcidx':
            m = re.match(r'.*\(pc,(.*)\)$', o.text)
            return '%s(pc,%s)' % (self.rom_ref(o.addr), m.group(1))
        if o.kind == 'branch':
            return self.rom_ref(o.addr)
        if o.kind == 'imm' and o.imm_size == 4:
            v = o.imm
            if ins.mnemonic in IMM_LABEL_MNEMONICS:
                to_areg = ins.operands[-1].text.startswith(('a', 'sp'))
                if 0x200 <= v < self.rom_end and v in self.label_at:
                    return '#%s' % self.label_at[v]
                if (v & 0xFF000000) == 0xFF000000 and (v & 0xFFFFFF) >= 0xFF0000:
                    if to_areg or (v & 0xFFFFFF) in self.ram_direct:
                        return '#%s' % self.ram_name(v)
                if 0xA00000 <= v < 0xC00020 and (to_areg or v in HW_NAMES or ins.mnemonic == 'pea'):
                    return '#%s' % self.hw_name(v)
            return o.text
        return o.text

    def render_insn(self, ins):
        if ins.unassemblable and self.imm_macros:
            # cmp.w #imm,dN in the CMP <ea>,Dn form -> macro producing the exact words
            src, dst = ins.operands
            name, sz = ins.mnemonic.split('.')
            return '\t%s_imm.%s\t%s,%s' % (name, sz, src.text[1:], dst.text)
        ops = ','.join(self.render_operand(ins, o) for o in ins.operands)
        if ops:
            return '\t%s\t%s' % (ins.mnemonic, ops)
        return '\t%s' % ins.mnemonic

    # ------------------------------------------------------------------
    # data rendering
    def data_lines(self, a, b, out):
        """Render the data region [a,b) which contains no labels except at a.
        Tables that extend beyond b are split and the rest is emitted when the
        next label is reached."""
        rom = self.rom
        m = self.m
        if a in m.jump_tables:
            tbl = self.jmptbl_base.get(a, a)
            ents = m.jump_tables[a]
            n = min(len(ents), (b - a) // 2)
            for ea, t in ents[:n]:
                out.append('\tdc.w\t%s-%s' % (self.rom_ref(t), self.label_at[tbl]))
            if n < len(ents):
                m.jump_tables[a + 2 * n] = ents[n:]
                self.jmptbl_base[a + 2 * n] = tbl
            a += 2 * n
        elif a in m.ptr_tables:
            ents = m.ptr_tables[a]
            n = min(len(ents), (b - a) // 4)
            for t in ents[:n]:
                out.append('\tdc.l\t%s' % self.rom_ref(t))
            if n < len(ents):
                m.ptr_tables[a + 4 * n] = ents[n:]
            a += 4 * n
        elif a in m.inline_blocks:
            end, routine = m.inline_blocks[a]
            n = (rom[a] << 8) | rom[a + 1]
            if n == end - a and self.m.inline_data_calls.get(routine) == 'len' and a + 2 <= b:
                out.append('\tdc.w\t%s-%s' % (self.rom_ref(end), self.label_at[a]))
                self.bytes_lines(a + 2, min(end, b), out)
            else:
                self.bytes_lines(a, min(end, b), out)
            a = min(end, b)
        elif a in self.data_ptr_runs:
            ents = self.data_ptr_runs[a]
            n = min(len(ents), (b - a) // 4)
            for v in ents[:n]:
                out.append('\tdc.l\t%s' % self.rom_ref(v))
            if n < len(ents):
                self.data_ptr_runs[a + 4 * n] = ents[n:]
            a += 4 * n
        elif a in self.tilesets and b - a >= 8:
            cnt, offA, offB, aend = self.tilesets[a]
            base = self.label_at[a]
            out.append('\tdc.l\t%s-%s' % (self.label_at[a + offA], base))
            out.append('\tdc.l\t%s-%s' % (self.label_at[a + offB], base))
            a += 8
        elif a in self.art_part:
            base, part = self.art_part[a]
            cnt, offA, offB, aend = self.tilesets[base]
            if part in ('tiles', 'tiles_cont') and b <= base + offA:
                # a foreign label inside the tile data splits the incbin
                if part == 'tiles':
                    out.append('\tdc.w\t%d\t; tile count' % cnt)
                    a += 2
                    fname = 'data/art/%s.bin' % self.label_at[base].lower()
                else:
                    fname = 'data/art/%s_%06X.bin' % (self.label_at[base].lower(), a)
                path = os.path.join(self.outdir, fname)
                os.makedirs(os.path.dirname(path), exist_ok=True)
                with open(path, 'wb') as f:
                    f.write(rom[a:b])
                if part == 'tiles':
                    note = '%d tiles, 8x8 4bpp' % cnt + ('' if b == base + offA else ' (split by a label below)')
                else:
                    note = 'tile data continued'
                out.append('\tincbin\t"%s"\t; %s' % (fname, note))
                if b < base + offA:
                    self.art_part[b] = (base, 'tiles_cont')
                a = b
            elif part == 'pal' and b - a >= 128:
                for i in range(4):
                    ws = struct.unpack('>16H', rom[a + i * 32:a + i * 32 + 32])
                    out.append('\tdc.w\t%s' % ','.join('$%04X' % w for w in ws))
                a += 128
            elif part == 'map' and aend is not None and b >= aend:
                w, h = struct.unpack('>HH', rom[a:a + 4])
                out.append('\tdc.w\t%d,%d\t; width, height' % (w, h))
                x = a + 4
                for row in range(h):
                    ws = struct.unpack('>%dH' % w, rom[x:x + 2 * w])
                    for i in range(0, w, 16):
                        out.append('\tdc.w\t%s' % ','.join('$%04X' % v for v in ws[i:i + 16]))
                    x += 2 * w
                a = x
        if a >= b:
            return
        if a in self.text_regions or (b - a < 0x40 and any(x in self.text_regions for x in range(a - 0x400, a))):
            self.bytes_lines(a, b, out, strings=True)
            return
        texty = self.texty(a, b)
        if b - a >= self.blob_min and not texty:
            self.blob(a, b, out)
            return
        self.bytes_lines(a, b, out, strings=texty)

    def texty(self, a, b):
        d = self.rom[a:b]
        if len(d) < 4:
            return False
        n = sum(1 for c in d if 32 <= c < 127 or c in (10, 13, 0))
        letters = sum(1 for c in d if 65 <= c < 91 or 97 <= c < 123 or c == 32)
        return n > len(d) * 0.75 and letters > len(d) * 0.3

    def blob(self, a, b, out):
        fname = 'data/bin/%s.bin' % self.blob_name(a)
        path = os.path.join(self.outdir, fname)
        os.makedirs(os.path.dirname(path), exist_ok=True)
        with open(path, 'wb') as f:
            f.write(self.rom[a:b])
        out.append('\tincbin\t"%s"\t; %d bytes' % (fname, b - a))

    def blob_name(self, a):
        n = self.names.names.get(a)
        if n and not n.startswith('dat_'):
            return n
        return 'data_%06X' % a

    def bytes_lines(self, a, b, out, strings=True):
        """dc.b / dc.w lines with strings pulled out."""
        rom = self.rom
        x = a
        while x < b:
            # printable run?
            run = x
            while strings and run < b and 32 <= rom[run] < 127:
                run += 1
            if run - x >= 4:
                s = rom[x:run].decode('ascii')
                # include a terminating zero
                term = ''
                if run < b and rom[run] == 0:
                    term = ',0'
                    run += 1
                for i in range(0, len(s), 60):
                    chunk = s[i:i + 60]
                    chunk = chunk.replace('"', '",$22,"')
                    last = i + 60 >= len(s)
                    out.append('\tdc.b\t"%s"%s' % (chunk, term if last else ''))
                x = run
                continue
            # plain bytes until next printable run of >= 4 or end
            y = x
            while y < b:
                if strings and 32 <= rom[y] < 127:
                    r = y
                    while r < b and 32 <= rom[r] < 127:
                        r += 1
                    if r - y >= 4:
                        break
                    y = r
                else:
                    y += 1
            chunk = rom[x:y]
            if (x & 1) == 0 and len(chunk) % 2 == 0 and len(chunk) >= 2 and not self.bytes_like(chunk):
                for i in range(0, len(chunk), 16):
                    ws = struct.unpack('>%dH' % (min(16, len(chunk) - i) // 2), chunk[i:i + 16])
                    out.append('\tdc.w\t%s' % ','.join('$%04X' % w for w in ws))
            else:
                for i in range(0, len(chunk), 16):
                    out.append('\tdc.b\t%s' % ','.join('$%02X' % c for c in chunk[i:i + 16]))
            x = y

    def bytes_like(self, chunk):
        """Heuristic: byte oriented data (many bytes identical high/low)."""
        if len(chunk) < 8:
            return True
        hi = chunk[0::2]
        lo = chunk[1::2]
        # word tables have low entropy in the high byte
        return len(set(hi)) > len(set(lo)) * 1.5 and len(set(hi)) > 8

    # ------------------------------------------------------------------
    def emit(self, segments):
        """segments: list of (start, end, relative path, title)."""
        os.makedirs(self.outdir, exist_ok=True)
        for d in ('inc', 'src', 'data', 'data/bin'):
            os.makedirs(os.path.join(self.outdir, d), exist_ok=True)
        self.build_labels()
        main = []
        main.append('; %s - Sega Mega Drive / Genesis\n; Disassembly, reassembles byte-exact with SNASM68K / asm68k (and vasm -m68000 -no-opt -Fbin).\n' % self.name.upper())
        main.append('\tinclude\t"inc/genesis.inc"')
        main.append('\tinclude\t"inc/ram.inc"')
        main.append('\tinclude\t"inc/macros.inc"')
        main.append('')
        main.append('\torg\t0')
        main.append('ROM_Start:')
        self.hw_vars = {}
        for start, end, path, title in segments:
            lines = ['; ' + '=' * 76, '; %s' % title, '; ROM range $%06X-$%06X' % (start, end - 1), '; ' + '=' * 76, '']
            self.emit_range(start, end, lines)
            full = os.path.join(self.outdir, path)
            os.makedirs(os.path.dirname(full), exist_ok=True)
            with open(full, 'w') as f:
                f.write('\n'.join(lines) + '\n')
            main.append('\tinclude\t"%s"\t; %s' % (path, title))
        main.append('')
        main.append('ROM_Padding:')
        main.append('\tdcb.b\t$%X-ROM_Padding,$FF' % len(self.rom))
        main.append('ROM_End:')
        main.append('\tend')
        with open(os.path.join(self.outdir, self.name + '.asm'), 'w') as f:
            f.write('\n'.join(main) + '\n')
        self.write_includes()
        self.names.save(os.path.join(self.outdir, self.name + '.names'), self.label_at, self.ram_vars)
        self.write_symbols()

    def emit_range(self, start, end, out):
        m = self.m
        rom = self.rom
        a = start
        if start == 0:
            self.emit_header(out)
            a = 0x200
        label_addrs = sorted(x for x in self.label_at if start <= x < end)
        import bisect
        while a < end:
            if a in self.label_at:
                self.emit_label(a, out)
            k = m.kind[a]
            if k == CODE:
                ins = m.insns[a]
                out.append(self.render_insn(ins) + self.insn_comment(ins))
                a += ins.size
                if ins.is_terminal and (a not in self.label_at or self.label_kind.get(a) == 'sub'):
                    out.append('')
                continue
            if k == CODE_CONT:
                raise RuntimeError('mid instruction at %06X' % a)
            # data: up to the next label or end
            i = bisect.bisect_right(label_addrs, a)
            b = label_addrs[i] if i < len(label_addrs) else end
            b = min(b, end)
            self.data_lines(a, b, out)
            a = b
            if b in self.label_at and self.label_kind.get(b) == 'sub':
                out.append('')

    def emit_label(self, a, out):
        kind = self.label_kind.get(a)
        name = self.label_at[a]
        if kind == 'sub':
            callers = sorted(self.m.xrefs.get(a, ()))
            out.append('')
            out.append('; ' + '-' * 70)
            c = self.names.comments.get(a)
            if c:
                out.append('; %s' % c)
            if callers:
                shown = ', '.join('$%06X' % x for x in callers[:8])
                more = '' if len(callers) <= 8 else ' (+%d more)' % (len(callers) - 8)
                out.append('; called from %s%s' % (shown, more))
            out.append('%s:' % name)
        elif kind in ('jmptbl', 'ptrtbl', 'art') or a in self.data_ptr_runs:
            out.append('')
            c = self.names.comments.get(a)
            if c:
                out.append('; %s' % c)
            if kind == 'art':
                cnt, offA, offB, aend = self.tilesets[a]
                out.append('; tile set: %d tiles, 4 palettes, %s' % (cnt, ('%dx%d tile map' % struct.unpack('>HH', self.rom[a + offB:a + offB + 4])) if aend else 'sprite data'))
            out.append('%s:' % name)
        elif a in self.region_desc:
            out.append('')
            out.append('; %s' % self.region_desc[a])
            out.append('%s:' % name)
        else:
            c = self.names.comments.get(a)
            if c:
                out.append('; %s' % c)
            out.append('%s:' % name)

    def insn_comment(self, ins):
        # show the raw encoding of general form immediates, which depend on the assembler
        if ins.unassemblable and not self.imm_macros:
            return '\t; general form'
        return ''

    # ------------------------------------------------------------------
    def emit_header(self, out):
        rom = self.rom
        out.append('; 68000 exception vectors')
        out.append('VectorTable:')
        vec_names = ['initial stack pointer', 'entry point', 'bus error', 'address error', 'illegal instruction',
                     'zero divide', 'CHK', 'TRAPV', 'privilege violation', 'trace', 'line 1010 emulator',
                     'line 1111 emulator', 'reserved', 'reserved', 'reserved', 'uninitialised interrupt',
                     'reserved', 'reserved', 'reserved', 'reserved', 'reserved', 'reserved', 'reserved', 'reserved',
                     'spurious interrupt', 'IRQ level 1', 'IRQ level 2 (external)', 'IRQ level 3',
                     'IRQ level 4 (horizontal interrupt)', 'IRQ level 5', 'IRQ level 6 (vertical interrupt)', 'IRQ level 7']
        for i in range(64):
            v = struct.unpack('>I', rom[i * 4:i * 4 + 4])[0]
            if i == 0:
                expr = '$%08X' % v
            elif 0x200 <= v < self.rom_end:
                expr = self.rom_ref(v)
            else:
                expr = '$%08X' % v
            if i < 32:
                desc = vec_names[i]
            elif i < 48:
                desc = 'TRAP #%d' % (i - 32)
            else:
                desc = 'reserved'
            out.append('\tdc.l\t%s\t; %2d: %s' % (expr, i, desc))
        out.append('')
        out.append('; ROM header')
        out.append('Header:')
        fields = HEADER_FIELDS[1:] + [(0x200, None, None)]
        for (a, label, desc), (b, _, _) in zip(fields, fields[1:]):
            out.append('%s:' % label)
            if a == 0x18E:
                out.append('\tdc.w\t$%04X\t; %s' % (struct.unpack('>H', rom[a:a + 2])[0], desc))
            elif b - a == 4:
                out.append('\tdc.l\t$%08X\t; %s' % (struct.unpack('>I', rom[a:a + 4])[0], desc))
            else:
                txt = rom[a:b].decode('latin-1')
                out.append('\tdc.b\t"%s"\t; %s' % (txt.replace('"', '",$22,"'), desc))
        out.append('')

    # ------------------------------------------------------------------
    def write_includes(self):
        with open(os.path.join(self.outdir, 'inc/genesis.inc'), 'w') as f:
            f.write('; Mega Drive hardware addresses\n\n')
            for a in sorted(self.hw_vars):
                f.write('%s\tequ\t$%06X\n' % (self.hw_vars[a], a))

        with open(os.path.join(self.outdir, 'inc/ram.inc'), 'w') as f:
            f.write('; 68000 work RAM ($FF0000-$FFFFFF).  Values are sign extended so that\n')
            f.write('; both (name).w and (name).l addressing assemble like the original.\n\n')
            for a in sorted(self.ram_vars):
                c = self.names.ram_comments.get(a)
                f.write('%s\tequ\t$%08X%s\n' % (self.ram_vars[a], a | 0xFF000000, ('\t; ' + c) if c else ''))
        with open(os.path.join(self.outdir, 'inc/macros.inc'), 'w') as f:
            f.write(MACROS)

    def write_symbols(self):
        with open(os.path.join(self.outdir, self.name + '.sym'), 'w') as f:
            for a in sorted(self.label_at):
                f.write('%06X\t%s\t%s\n' % (a, self.label_kind.get(a, ''), self.label_at[a]))
            for a in sorted(self.ram_vars):
                f.write('%06X\tram\t%s\n' % (a, self.ram_vars[a]))


MACROS = '''; Helper macros.
;
; The C compiled parts of the game use the "general" encodings of
; CMP/ADD/SUB/AND/OR with an immediate source and a data register destination
; (opcode $B07C etc.) instead of CMPI/ADDI/SUBI/ANDI/ORI.  SNASM68K and vasm
; keep "cmp.w #n,d0" in that general form, which is what the main source
; uses.  Should an assembler fold them into the I-forms, regenerate the
; source with --imm-macros to use the macros below, which emit the exact
; words.

REGNO_d0\tequ\t0
REGNO_d1\tequ\t1
REGNO_d2\tequ\t2
REGNO_d3\tequ\t3
REGNO_d4\tequ\t4
REGNO_d5\tequ\t5
REGNO_d6\tequ\t6
REGNO_d7\tequ\t7

cmp_imm\tmacro
\tif "\\0"="l"
\tdc.w\t$B0BC|(REGNO_\\2<<9)
\tdc.l\t\\1
\telseif "\\0"="w"
\tdc.w\t$B07C|(REGNO_\\2<<9),\\1
\telse
\tdc.w\t$B03C|(REGNO_\\2<<9),\\1
\tendif
\tendm

add_imm\tmacro
\tif "\\0"="l"
\tdc.w\t$D0BC|(REGNO_\\2<<9)
\tdc.l\t\\1
\telseif "\\0"="w"
\tdc.w\t$D07C|(REGNO_\\2<<9),\\1
\telse
\tdc.w\t$D03C|(REGNO_\\2<<9),\\1
\tendif
\tendm

sub_imm\tmacro
\tif "\\0"="l"
\tdc.w\t$90BC|(REGNO_\\2<<9)
\tdc.l\t\\1
\telseif "\\0"="w"
\tdc.w\t$907C|(REGNO_\\2<<9),\\1
\telse
\tdc.w\t$903C|(REGNO_\\2<<9),\\1
\tendif
\tendm

and_imm\tmacro
\tif "\\0"="l"
\tdc.w\t$C0BC|(REGNO_\\2<<9)
\tdc.l\t\\1
\telseif "\\0"="w"
\tdc.w\t$C07C|(REGNO_\\2<<9),\\1
\telse
\tdc.w\t$C03C|(REGNO_\\2<<9),\\1
\tendif
\tendm

or_imm\tmacro
\tif "\\0"="l"
\tdc.w\t$80BC|(REGNO_\\2<<9)
\tdc.l\t\\1
\telseif "\\0"="w"
\tdc.w\t$807C|(REGNO_\\2<<9),\\1
\telse
\tdc.w\t$803C|(REGNO_\\2<<9),\\1
\tendif
\tendm
'''
