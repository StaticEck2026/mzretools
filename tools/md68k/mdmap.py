"""
Code/data mapping of a Mega Drive ROM.

Recursive descent from the vector table and the entry point, following
branches, calls, jump tables (`jmp xxx(pc,dN.w)` idioms), pointer tables and
address immediates.  Every candidate seed is validated by decoding it to a
terminating instruction so that data that merely looks like a pointer is
not turned into code.
"""

import struct
from collections import defaultdict

from m68k import Decoder, Invalid

UNKNOWN, CODE, CODE_CONT, DATA = 0, 1, 2, 3


class Mapper:
    def __init__(self, rom: bytes, rom_end: int):
        self.rom = rom
        self.rom_end = rom_end            # first byte of trailing padding
        self.dec = Decoder(rom)
        self.kind = bytearray(len(rom))
        self.insns = {}                   # addr -> Instruction
        self.labels = {}                  # addr -> label type ('sub','loc','data','vec','tbl','jmptbl')
        self.xrefs = defaultdict(set)     # target -> set of referencing instruction addresses
        self.func_starts = set()
        self.jump_tables = {}             # table addr -> list of (entry addr, target)
        self.ptr_tables = {}              # table addr -> list of targets
        self.inline_data_calls = {}       # routine -> 'len' | int | None (see inline_kind)
        self.inline_blocks = {}           # start -> (end, routine)
        self.worklist = []
        self.log = []
        self.ram_refs = defaultdict(set)  # ram addr -> set(insn addrs)
        self.hw_refs = defaultdict(set)

    # ------------------------------------------------------------------
    def in_rom(self, a):
        return 0 <= a < self.rom_end

    def w(self, a):
        return (self.rom[a] << 8) | self.rom[a + 1]

    def l(self, a):
        return struct.unpack('>I', self.rom[a:a + 4])[0]

    def is_code(self, a):
        return self.in_rom(a) and self.kind[a] in (CODE, CODE_CONT)

    def free(self, a, n):
        """True if the range is not yet classified."""
        if a < 0 or a + n > self.rom_end:
            return False
        return all(k == UNKNOWN for k in self.kind[a:a + n])

    # ------------------------------------------------------------------
    def validate(self, a, min_insns=2, max_insns=400, allow_known=True):
        """Decode from a until a terminal instruction.  Returns the number of
        instructions or 0 if the stream is not valid code."""
        if a & 1 or not self.in_rom(a) or a < 0x200:
            return 0
        n = 0
        while n < max_insns:
            if self.kind[a] == CODE:
                return n + (1 if allow_known else 0) if (n >= min_insns or allow_known) else 0
            if self.kind[a] != UNKNOWN:
                return 0
            try:
                ins = self.dec.decode(a)
            except Invalid:
                return 0
            if any(self.kind[x] != UNKNOWN for x in range(a, a + ins.size)):
                return 0
            if ins.target is not None and not self.plausible_target(ins):
                return 0
            n += 1
            if ins.is_terminal:
                return n if n >= min_insns else 0
            a += ins.size
            if a >= self.rom_end:
                return 0
        return n

    RARE_FIRST = ('ori', 'eori', 'chk', 'movep', 'trap', 'abcd', 'sbcd', 'nbcd', 'negx', 'tas',
                  'exg', 'rtr', 'stop', 'reset', 'addx', 'subx', 'cmpm', 'illegal', 'trapv',
                  'divs', 'divu', 'rox', 'link', 'unlk', 'rte', 'rts', 'nop', 'move.w\tsr', 'andi.b', 'ori.b')

    def looks_like_entry(self, a, min_insns=3):
        """Stricter validation for seeds that come from data (pointer tables):
        the first instruction must not be an unusual one."""
        if a & 1 or not self.in_rom(a) or self.kind[a] != UNKNOWN:
            return False
        try:
            ins = self.dec.decode(a)
        except Invalid:
            return False
        if ins.text.startswith(self.RARE_FIRST):
            return False
        if ins.mnemonic.startswith('b') and ins.is_branch and not ins.mnemonic.startswith('bra'):
            return False      # function starting with a conditional branch
        return self.validate(a, min_insns=min_insns) > 0

    def build_code_index(self):
        """Prefix sums of code bytes, for fast proximity checks."""
        import itertools
        self._code_prefix = [0]
        self._code_prefix.extend(itertools.accumulate(1 if k == CODE else 0 for k in self.kind[:self.rom_end]))

    def near_code(self, a, dist=0x1000):
        lo = max(0, a - dist)
        hi = min(self.rom_end, a + dist)
        p = self._code_prefix
        return p[hi] - p[lo] > 0

    def plausible_target(self, ins):
        t = ins.target
        if t is None:
            return True
        if t & 1:
            return False
        if ins.mnemonic.startswith(('jmp', 'jsr')) and ins.operands and ins.operands[0].kind in ('absw', 'absl'):
            # jsr to RAM is legal (code copied to RAM) but rare; require ROM or RAM
            return self.in_rom(t) or t >= 0xFF0000
        return self.in_rom(t) and t >= 0x200

    # ------------------------------------------------------------------
    def add_seed(self, a, ltype, ref=None):
        if a & 1 or not self.in_rom(a):
            return
        if ref is not None:
            self.xrefs[a].add(ref)
        if ltype == 'sub':
            self.func_starts.add(a)
        cur = self.labels.get(a)
        if cur is None or (cur == 'loc' and ltype == 'sub'):
            self.labels[a] = ltype
        if self.kind[a] == UNKNOWN:
            self.worklist.append(a)

    def run_worklist(self):
        while self.worklist:
            a = self.worklist.pop()
            if self.kind[a] != UNKNOWN:
                continue
            self.trace(a)

    def trace(self, a):
        """Linear decode from a until a terminal instruction, queueing targets."""
        while True:
            if not self.in_rom(a) or self.kind[a] != UNKNOWN:
                return
            try:
                ins = self.dec.decode(a)
            except Invalid as e:
                self.log.append('decode failure at %06X: %s' % (a, e))
                return
            if any(self.kind[x] != UNKNOWN for x in range(a, a + ins.size)):
                self.log.append('overlap at %06X' % a)
                return
            self.kind[a] = CODE
            for x in range(a + 1, a + ins.size):
                self.kind[x] = CODE_CONT
            self.insns[a] = ins
            self.note_refs(ins)
            if ins.target is not None:
                t = ins.target
                if self.in_rom(t):
                    if ins.is_call:
                        self.add_seed(t, 'sub', a)
                    else:
                        self.add_seed(t, 'loc', a)
            if ins.indirect_jump:
                self.handle_indirect(ins)
            if ins.is_terminal:
                return
            if ins.is_call and ins.target is not None:
                kind = self.inline_kind(ins.target)
                if kind is not None:
                    # the callee consumes data placed after the jsr/bsr and
                    # returns past it
                    self.after_inline_call(ins, kind)
                    return
            a += ins.size

    def note_refs(self, ins):
        for o in ins.operands:
            if o.kind in ('absw', 'absl', 'pcrel', 'pcidx') and o.addr is not None:
                t = o.addr
                if self.in_rom(t):
                    if ins.mnemonic in ('jsr', 'jmp'):
                        continue
                    self.xrefs[t].add(ins.addr)
                    if t not in self.labels:
                        self.labels[t] = 'data'
                elif t >= 0xFF0000 or (t & 0xFFFF0000) == 0xFFFF0000:
                    self.ram_refs[t & 0xFFFFFF].add(ins.addr)
                elif 0xA00000 <= t < 0xC00020:
                    self.hw_refs[t].add(ins.addr)
            elif o.kind == 'imm' and o.imm_size == 4:
                v = o.imm
                if (v & 0xFFFF0000) == 0xFFFF0000 and (v & 0xFFFFFF) >= 0xFF0000:
                    self.ram_refs[v & 0xFFFFFF].add(ins.addr)
                elif 0xA00000 <= v < 0xC00020:
                    self.hw_refs[v].add(ins.addr)

    # ------------------------------------------------------------------
    def handle_indirect(self, ins):
        """jmp/jsr through a register: walk backwards through the preceding
        instructions to find the table the register was loaded from."""
        import re
        o = ins.operands[0]
        if o.kind == 'pcidx':
            self.scan_jump_table(o.addr, ins)
            return
        txt = o.text
        m = re.match(r'(?:-?\$?[0-9A-F]*)?\((a\d|sp)(?:,(d\d|a\d)\.[wl])?\)$', txt)
        if not m:
            return
        reg = m.group(1)
        indexed = m.group(2) is not None
        mode = 'wordtbl' if indexed else 'direct'
        if indexed:
            # jmp (aN,dM.w): dM is usually loaded with move.w (aN,dM.w),dM
            mode = 'wordtbl'
        a = ins.addr
        for _ in range(16):
            prev = self.prev_insn(a)
            if prev is None or prev.is_terminal:
                return
            a = prev.addr
            if len(prev.operands) < 2:
                if prev.is_branch:
                    return
                continue
            dst = prev.operands[-1].text
            src = prev.operands[0]
            mn = prev.mnemonic
            if dst != reg:
                if prev.is_branch:
                    return
                continue
            if mn == 'lea':
                if src.addr is None or not self.in_rom(src.addr):
                    return
                base = src.addr
                if mode == 'wordtbl':
                    self.scan_jump_table(base, ins)
                elif mode == 'longtbl':
                    self.scan_long_table(base, ins)
                elif mode == 'direct':
                    self.add_seed(base, 'sub' if ins.is_call else 'loc', ins.addr)
                    self.scan_branch_table(base, ins)
                return
            if mn == 'movea.l':
                if src.kind == 'imm':
                    if self.in_rom(src.imm):
                        if mode == 'wordtbl':
                            self.scan_jump_table(src.imm, ins)
                        elif mode == 'longtbl':
                            self.scan_long_table(src.imm, ins)
                        else:
                            self.add_seed(src.imm, 'sub' if ins.is_call else 'loc', ins.addr)
                    return
                if src.kind == 'pcidx' and self.in_rom(src.addr):
                    self.scan_long_table(src.addr, ins)
                    return
                mm = re.match(r'(?:-?\$?[0-9A-F]*)?\((a\d|sp),(d\d|a\d)\.[wl]\)$', src.text)
                if mm:
                    reg = mm.group(1)
                    mode = 'longtbl'
                    continue
                return
            if mn == 'adda.w' or mn == 'adda.l':
                mm = re.match(r'(?:-?\$?[0-9A-F]*)?\((a\d|sp),(d\d|a\d)\.[wl]\)$', src.text)
                if mm and mm.group(1) == reg:
                    mode = 'wordtbl'
                    continue
                if src.kind == '' and re.match(r'[da]\d$', src.text):
                    # adda.l dN,aN : the jump lands inside a table of fixed
                    # size code entries (bra.w ...), so the base is code
                    mode = 'direct' if mode == 'direct' else mode
                    continue
                return
            if mn in ('addq.l', 'addq.w', 'subq.l', 'subq.w'):
                continue
            # anything else writing the register: give up
            return

    def scan_branch_table(self, tbl, ins):
        """A table of bra.w instructions reached with a computed offset: every
        4 byte slot is an entry point."""
        a = tbl
        n = 0
        while self.in_rom(a + 4) and self.w(a) == 0x6000 and n < 256:
            try:
                e = self.dec.decode(a)
            except Invalid:
                break
            if e.target is None or not self.plausible_target(e):
                break
            self.add_seed(a, 'loc', ins.addr)
            a += 4
            n += 1

    def scan_long_table(self, tbl, ins):
        """Table of longword code pointers."""
        if tbl in self.ptr_tables or not self.in_rom(tbl) or tbl & 1:
            return
        entries = []
        a = tbl
        while a + 4 <= self.rom_end and self.free(a, 4):
            v = self.l(a)
            if v & 1 or not (0x200 <= v < self.rom_end):
                break
            if not (self.kind[v] == CODE or self.validate(v, min_insns=1)):
                break
            entries.append(v)
            a += 4
            if len(entries) > 1024:
                break
        while entries and any(v <= tbl + 4 * (len(entries) - 1) for v in entries):
            entries.pop()
        if not entries:
            return
        self.ptr_tables[tbl] = entries
        self.labels[tbl] = 'ptrtbl'
        for i, v in enumerate(entries):
            for x in range(tbl + i * 4, tbl + i * 4 + 4):
                self.kind[x] = DATA
            self.add_seed(v, 'sub', ins.addr)

    def prev_insn(self, a):
        """Instruction decoded immediately before address a (linear)."""
        for back in (2, 4, 6, 8, 10):
            p = a - back
            if p >= 0 and self.kind[p] == CODE and self.insns[p].size == back:
                return self.insns[p]
        return None

    def scan_jump_table(self, tbl, ins):
        """Word offset table relative to its own start (jmp tbl(pc,d0.w) idiom)."""
        if tbl in self.jump_tables or not self.in_rom(tbl) or tbl & 1:
            return
        entries = []
        a = tbl
        while self.in_rom(a + 1) and self.kind[a] == UNKNOWN and self.kind[a + 1] == UNKNOWN:
            off = self.w(a)
            off = off - 0x10000 if off & 0x8000 else off
            t = tbl + off
            if t & 1 or not self.in_rom(t) or t < 0x200:
                break
            # the target must look like code
            if not (self.kind[t] == CODE or self.validate(t, min_insns=1)):
                break
            if any(t2 <= a < t2 + 2 for _, t2 in entries) or any(t <= e < t + 2 for e, _ in entries):
                break
            entries.append((a, t))
            a += 2
            if len(entries) > 512:
                break
        # the table cannot overlap its own targets
        while entries and any(t <= entries[-1][0] for _, t in entries):
            entries.pop()
        if len(entries) < 2:
            return
        self.jump_tables[tbl] = entries
        self.labels[tbl] = 'jmptbl'
        for ea, t in entries:
            self.kind[ea] = DATA
            self.kind[ea + 1] = DATA
            self.add_seed(t, 'loc', ins.addr)

    # ------------------------------------------------------------------
    def inline_kind(self, t):
        """Recognise routines that take their arguments inline after the call.
        Returns 'len' (word length prefix, counting itself), an int (fixed
        number of bytes) or None."""
        if t in self.inline_data_calls:
            return self.inline_data_calls[t]
        if not self.in_rom(t + 12):
            return None
        b = self.rom[t:t + 12]
        kind = None
        # move.l a1,-(sp) / movea.l 4(sp),a1 / bsr.w worker / move.l a1,4(sp) / movea.l (sp)+,a1 / rts
        if b[0:6] == b'\x2f\x09\x22\x6f\x00\x04' and b[6:8] == b'\x61\x00':
            kind = 'len'
        # movea.l (sp)+,a1 / bsr.w worker / jmp (a1)
        elif b[0:4] == b'\x22\x5f\x61\x00' and b[6:8] == b'\x4e\xd1':
            kind = 'len'
        # move.l (sp),(xx).w / bsr.w / addq.l #8,(sp) / rts
        elif b[0:2] == b'\x21\xd7' and b[4:6] == b'\x61\x00' and b[8:12] == b'\x50\x97\x4e\x75':
            kind = 8
        self.inline_data_calls[t] = kind
        return kind

    def after_inline_call(self, ins, kind):
        """Mark the inline argument block after a call and continue tracing
        after it."""
        start = ins.addr + ins.size
        if kind == 'len':
            n = self.w(start)
            if n < 2 or n & 1 or not self.in_rom(start + n):
                self.log.append('bad inline length at %06X' % start)
                return
        else:
            n = kind
        end = start + n
        if not self.free(start, n):
            self.log.append('inline block overlaps at %06X' % start)
            return
        for x in range(start, end):
            self.kind[x] = DATA
        self.labels[start] = 'inline'
        self.inline_blocks[start] = (end, ins.target)
        self.worklist.append(end)
        self.labels.setdefault(end, 'loc')

    # ------------------------------------------------------------------
    def scan_pointer_tables(self):
        """Find runs of longwords pointing at valid code in unclassified
        memory and seed them."""
        found = 0
        self.build_code_index()
        a = 0x200
        while a + 4 <= self.rom_end:
            if self.kind[a] != UNKNOWN:
                a += 1
                continue
            if a & 1:
                a += 1
                continue
            run = []
            b = a
            while b + 4 <= self.rom_end and self.free(b, 4):
                v = self.l(b)
                if v & 1 or not (0x200 <= v < self.rom_end):
                    break
                if self.kind[v] == CODE and v in self.labels:
                    run.append((b, v))
                elif self.kind[v] == UNKNOWN and self.looks_like_entry(v, min_insns=3):
                    run.append((b, v))
                else:
                    break
                b += 4
            referenced = a in self.xrefs or self.near_code(a)
            if referenced and (len(run) >= 2 and all(self.kind[v] == CODE for _, v in run) or len(run) >= 3):
                for eb, v in run:
                    self.add_seed(v, 'sub', eb)
                    for x in range(eb, eb + 4):
                        self.kind[x] = DATA
                self.ptr_tables[a] = [v for _, v in run]
                self.labels[a] = 'ptrtbl'
                found += len(run)
                a = b
            else:
                a += 2
        return found

    def scan_immediates(self):
        """move.l #addr / pea addr pointing at valid code."""
        found = 0
        for ins in list(self.insns.values()):
            for o in ins.operands:
                if o.kind == 'imm' and o.imm_size == 4:
                    v = o.imm
                    if 0x200 <= v < self.rom_end and not v & 1 and self.kind[v] == UNKNOWN:
                        if ins.mnemonic.startswith(('movea', 'pea', 'move.l')) and self.looks_like_entry(v, min_insns=3):
                            self.add_seed(v, 'sub', ins.addr)
                            found += 1
                elif o.kind in ('pcrel', 'absl', 'absw') and ins.mnemonic in ('lea', 'pea'):
                    v = o.addr
                    if 0x200 <= v < self.rom_end and not v & 1 and self.kind[v] == UNKNOWN:
                        if self.looks_like_entry(v, min_insns=3):
                            self.add_seed(v, 'sub', ins.addr)
                            found += 1
        return found

    WEIRD = ('ori', 'eori', 'chk', 'movep', 'trap', 'abcd', 'sbcd', 'nbcd', 'negx', 'tas',
             'rtr', 'stop', 'reset', 'addx', 'subx', 'cmpm', 'illegal', 'trapv', 'roxl', 'roxr',
             'link', 'unlk', 'divs', 'divu', 'move.w\tsr', 'andi.b', 'ori.b', 'btst\td')

    def function_quality(self, a, limit, strict=False):
        """Decode a function starting at a that must end (with a terminal
        instruction) before limit.  Returns (end, n_insns, weird_count) or
        None if it is not clean code."""
        x = a
        n = 0
        weird = 0
        targets = []
        while x < limit:
            if self.kind[x] == CODE:
                break                         # flows into known code
            if self.kind[x] != UNKNOWN:
                return None
            try:
                ins = self.dec.decode(x)
            except Invalid:
                return None
            if x + ins.size > limit:
                return None
            if ins.target is not None and not self.plausible_target(ins):
                return None
            if ins.text.startswith(self.WEIRD):
                weird += 1
            # immediate garbage: move.l #huge,-(sp) etc. are fine; but operands
            # referencing far beyond the rom are suspicious
            for o in ins.operands:
                if o.kind in ('absl',) and o.addr is not None:
                    t = o.addr
                    if not (self.in_rom(t) or t >= 0xFF0000 or 0xA00000 <= t < 0xC00020):
                        return None
            if ins.target is not None:
                targets.append((ins.target, ins.is_call))
            n += 1
            x += ins.size
            if ins.is_terminal:
                break
            if n > 2000:
                return None
        else:
            return None
        if strict:
            # every branch must stay inside the function or reach known code;
            # calls may also reach something that itself looks like a function
            for t, call in targets:
                if a <= t < x or self.is_code(t):
                    continue
                if call and self.looks_like_entry(t, min_insns=2):
                    continue
                return None
        return (x, n, weird)

    def scan_gaps(self, sliding=False):
        """Unreferenced functions: start right after a terminal instruction
        (or, when sliding, at any even address) and decode cleanly to a
        terminal instruction with few unusual instructions."""
        found = 0
        if sliding:
            self.build_code_index()
        a = 0x200
        while a < self.rom_end:
            if self.kind[a] != UNKNOWN:
                a += 1
                continue
            b = a
            while b < self.rom_end and self.kind[b] == UNKNOWN:
                b += 1
            x = a + (a & 1)
            while x < b:
                prev = self.prev_insn(x)
                after_terminal = prev is not None and prev.is_terminal
                if not after_terminal and not sliding:
                    break
                if after_terminal:
                    min_n, max_weird = 2, 0.15
                else:
                    if not self.near_code(x, 0x400):
                        x += 2
                        continue
                    min_n, max_weird = 6, 0.0
                q = self.function_quality(x, b, strict=not after_terminal) if self.looks_like_entry(x, min_insns=1) else None
                if q is not None and q[1] >= min_n and q[2] <= q[1] * max_weird:
                    self.add_seed(x, 'sub')
                    self.labels[x] = 'sub'
                    self.run_worklist()
                    found += 1
                    x = q[0]
                    while x < b and self.kind[x] != UNKNOWN:
                        x += 1
                    if x & 1:
                        x += 1
                    continue
                if not sliding:
                    break
                x += 2
            a = b
        return found

    # ------------------------------------------------------------------
    def analyse(self, vectors=True, extra_seeds=()):
        if vectors:
            for i in range(1, 64):
                v = self.l(i * 4)
                if 0x200 <= v < self.rom_end and not v & 1:
                    self.add_seed(v, 'sub', i * 4)
        for s in extra_seeds:
            self.add_seed(s, 'sub')
        self.run_worklist()
        # phase A: evidence from code only
        for rnd in range(8):
            n = self.scan_immediates()
            self.run_worklist()
            n += self.scan_gaps()
            self.run_worklist()
            self.log.append('round A%d: %d new seeds' % (rnd, n))
            if n == 0:
                break
        # phase B: pointer tables in data, strictly validated
        for rnd in range(8):
            n = self.scan_pointer_tables()
            self.run_worklist()
            n += self.scan_immediates()
            self.run_worklist()
            n += self.scan_gaps()
            self.run_worklist()
            self.log.append('round B%d: %d new seeds' % (rnd, n))
            if n == 0:
                break
        # phase C: sliding search for unreferenced functions inside gaps
        for rnd in range(4):
            n = self.scan_gaps(sliding=True)
            self.run_worklist()
            n += self.scan_immediates()
            self.run_worklist()
            self.log.append('round C%d: %d new seeds' % (rnd, n))
            if n == 0:
                break
        self.finish_labels()

    def finish_labels(self):
        # every call target is a function start; branch targets inside code are locs
        for a, t in list(self.labels.items()):
            if t == 'loc' and a in self.func_starts:
                self.labels[a] = 'sub'
        # unknown regions referenced as data
        for a in self.xrefs:
            if self.in_rom(a) and a not in self.labels:
                self.labels[a] = 'data' if self.kind[a] != CODE else 'loc'

    # ------------------------------------------------------------------
    def stats(self):
        ncode = sum(1 for k in self.kind[:self.rom_end] if k in (CODE, CODE_CONT))
        return {'code_bytes': ncode, 'insns': len(self.insns), 'funcs': len(self.func_starts),
                'labels': len(self.labels), 'jump_tables': len(self.jump_tables),
                'ptr_tables': len(self.ptr_tables), 'ram_vars': len(self.ram_refs)}

    def code_ranges(self):
        rng = []
        a = 0
        while a < self.rom_end:
            if self.kind[a] in (CODE, CODE_CONT):
                b = a
                while b < self.rom_end and self.kind[b] in (CODE, CODE_CONT):
                    b += 1
                rng.append((a, b))
                a = b
            else:
                a += 1
        return rng
