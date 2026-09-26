#!/usr/bin/env python3
#
# ledisasm: recursive traversal disassembler for 32-bit LE/LX executables (DOS/4GW, DOS/32A...)
#
# This is the 32-bit protected mode counterpart of mzmap for executables which the C++ tools
# cannot handle. It follows the same ideas: trace calls and jumps from the entrypoint to find
# routine boundaries, collect variables, and save the result into an editable map file that can
# be fed back in on the next run (renamed routines, annotations and extra entrypoints are kept).
#
# The LE format has a big advantage over real mode MZ executables: every absolute address in the
# program is covered by a fixup record, so pointers to code (callbacks, jump tables, vtables) and
# to data can be identified exactly instead of guessed.
#
# Outputs (all optional):
#   --map      editable routine/variable map in the mzmap format (segment-relative offsets)
#   --asm      annotated assembly listing (split into several files with --split)
#   --json     machine readable description of routines, variables, strings and the call graph
#   --elf      ELF32 file with the relocated image and a symbol table, loadable into Ghidra/IDA/r2
#   --strings  list of strings in the data object together with the routines that reference them
#
import argparse
import bisect
import json
import os
import re
import struct
import sys
from collections import defaultdict

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from le import LEExecutable, LEError, SRC_OFF32, SRC_SIZE  # noqa: E402

try:
    import capstone
    from capstone import x86 as cx86
except ImportError:
    print("ERROR: this tool requires the capstone disassembler module, install with 'pip install capstone'")
    sys.exit(1)

VERSION = '1.0.0'

# instruction kinds
K_OTHER, K_CALL, K_CALLI, K_JMP, K_JMPI, K_JCC, K_RET, K_INT, K_HLT = range(9)

# well known interrupt services, keyed by (interrupt, ah) or (interrupt, ax)
INT_SERVICES = {
    (0x21, 0x02): 'dos_putchar', (0x21, 0x06): 'dos_direct_console_io', (0x21, 0x07): 'dos_getch_noecho',
    (0x21, 0x09): 'dos_print_string', (0x21, 0x0b): 'dos_kbhit', (0x21, 0x0e): 'dos_select_drive',
    (0x21, 0x19): 'dos_get_drive', (0x21, 0x1a): 'dos_set_dta', (0x21, 0x25): 'dos_set_vector',
    (0x21, 0x2a): 'dos_get_date', (0x21, 0x2c): 'dos_get_time', (0x21, 0x30): 'dos_version',
    (0x21, 0x33): 'dos_ctrl_break', (0x21, 0x35): 'dos_get_vector', (0x21, 0x36): 'dos_disk_free',
    (0x21, 0x39): 'dos_mkdir', (0x21, 0x3a): 'dos_rmdir', (0x21, 0x3b): 'dos_chdir', (0x21, 0x3c): 'dos_create',
    (0x21, 0x3d): 'dos_open', (0x21, 0x3e): 'dos_close', (0x21, 0x3f): 'dos_read', (0x21, 0x40): 'dos_write',
    (0x21, 0x41): 'dos_delete', (0x21, 0x42): 'dos_lseek', (0x21, 0x43): 'dos_attrib', (0x21, 0x44): 'dos_ioctl',
    (0x21, 0x47): 'dos_getcwd', (0x21, 0x48): 'dos_alloc', (0x21, 0x49): 'dos_free', (0x21, 0x4a): 'dos_resize',
    (0x21, 0x4b): 'dos_exec', (0x21, 0x4c): 'dos_exit', (0x21, 0x4e): 'dos_findfirst', (0x21, 0x4f): 'dos_findnext',
    (0x21, 0x56): 'dos_rename', (0x21, 0x57): 'dos_filetime', (0x21, 0x59): 'dos_ext_error',
    (0x21, 0x5a): 'dos_tmpfile', (0x21, 0x5b): 'dos_create_new', (0x21, 0x62): 'dos_get_psp',
    (0x31, 0x0000): 'dpmi_alloc_ldt', (0x31, 0x0001): 'dpmi_free_ldt', (0x31, 0x0002): 'dpmi_seg_to_desc',
    (0x31, 0x0003): 'dpmi_sel_inc', (0x31, 0x0006): 'dpmi_get_seg_base', (0x31, 0x0007): 'dpmi_set_seg_base',
    (0x31, 0x0008): 'dpmi_set_seg_limit', (0x31, 0x0009): 'dpmi_set_access', (0x31, 0x000a): 'dpmi_alias_desc',
    (0x31, 0x0100): 'dpmi_dos_alloc', (0x31, 0x0101): 'dpmi_dos_free', (0x31, 0x0102): 'dpmi_dos_resize',
    (0x31, 0x0200): 'dpmi_get_rm_vector', (0x31, 0x0201): 'dpmi_set_rm_vector', (0x31, 0x0202): 'dpmi_get_exc_handler',
    (0x31, 0x0203): 'dpmi_set_exc_handler', (0x31, 0x0204): 'dpmi_get_pm_vector', (0x31, 0x0205): 'dpmi_set_pm_vector',
    (0x31, 0x0300): 'dpmi_sim_rm_int', (0x31, 0x0301): 'dpmi_call_rm_far', (0x31, 0x0302): 'dpmi_call_rm_iret',
    (0x31, 0x0303): 'dpmi_alloc_callback', (0x31, 0x0304): 'dpmi_free_callback', (0x31, 0x0400): 'dpmi_version',
    (0x31, 0x0500): 'dpmi_free_mem_info', (0x31, 0x0501): 'dpmi_alloc_mem', (0x31, 0x0502): 'dpmi_free_mem',
    (0x31, 0x0503): 'dpmi_resize_mem', (0x31, 0x0600): 'dpmi_lock', (0x31, 0x0601): 'dpmi_unlock',
    (0x31, 0x0800): 'dpmi_map_phys', (0x31, 0x0900): 'dpmi_disable_vint', (0x31, 0x0901): 'dpmi_enable_vint',
    (0x10, 0x00): 'bios_set_video_mode', (0x10, 0x02): 'bios_set_cursor', (0x10, 0x0f): 'bios_get_video_mode',
    (0x10, 0x10): 'bios_palette', (0x10, 0x4f): 'vesa_bios', (0x10, 0x4f00): 'vesa_get_info',
    (0x10, 0x4f01): 'vesa_mode_info', (0x10, 0x4f02): 'vesa_set_mode', (0x10, 0x4f03): 'vesa_get_mode',
    (0x10, 0x4f05): 'vesa_bank_switch', (0x16, 0x00): 'bios_getkey', (0x16, 0x01): 'bios_peekkey',
    (0x16, 0x02): 'bios_shift_state', (0x1a, 0x00): 'bios_get_ticks', (0x33, 0x00): 'mouse_reset',
    (0x33, 0x01): 'mouse_show', (0x33, 0x02): 'mouse_hide', (0x33, 0x03): 'mouse_get_state',
    (0x33, 0x04): 'mouse_set_pos', (0x33, 0x07): 'mouse_set_xrange', (0x33, 0x08): 'mouse_set_yrange',
    (0x33, 0x0b): 'mouse_motion', (0x33, 0x0c): 'mouse_set_handler',
}
INT_NAMES = { 0x10: 'video', 0x11: 'equipment', 0x13: 'disk', 0x15: 'system', 0x16: 'keyboard', 0x1a: 'timer',
              0x21: 'dos', 0x2f: 'multiplex', 0x31: 'dpmi', 0x33: 'mouse', 0x3: 'breakpoint', 0x66: 'user66',
              0x67: 'ems', 0x80: 'user80' }

# well known I/O ports, used to tag routines with the hardware they touch
PORT_NAMES = {
    0x20: 'pic1', 0x21: 'pic1_mask', 0xa0: 'pic2', 0xa1: 'pic2_mask', 0x40: 'pit_ch0', 0x42: 'pit_ch2',
    0x43: 'pit_ctrl', 0x60: 'kbd_data', 0x61: 'kbd_ctrl_speaker', 0x64: 'kbd_status', 0x201: 'joystick',
    0x388: 'adlib', 0x389: 'adlib_data', 0x3c0: 'vga_attr', 0x3c4: 'vga_seq', 0x3c5: 'vga_seq_data',
    0x3c6: 'vga_pel_mask', 0x3c7: 'vga_pel_read', 0x3c8: 'vga_pel_write', 0x3c9: 'vga_pel_data',
    0x3ce: 'vga_gc', 0x3cf: 'vga_gc_data', 0x3d4: 'vga_crtc', 0x3d5: 'vga_crtc_data', 0x3da: 'vga_status',
    0x70: 'cmos', 0x71: 'cmos_data', 0x330: 'mpu401_data', 0x331: 'mpu401_ctrl', 0x0: 'dma', 0x8: 'dma',
}

def port_tag(port):
    if port in PORT_NAMES:
        return PORT_NAMES[port]
    if 0x220 <= port <= 0x28f:
        return 'soundblaster'
    if 0x300 <= port <= 0x33f:
        return 'midi/sound'
    if 0x3c0 <= port <= 0x3df:
        return 'vga'
    if 0x80 <= port <= 0x8f or 0xc0 <= port <= 0xdf or port < 0x20:
        return 'dma'
    return None

class Insn:
    __slots__ = ('addr', 'size', 'mnem', 'ops', 'kind', 'target', 'mem', 'imm', 'op0reg', 'op0imm', 'stop')

    def __init__(self, ci):
        self.addr = ci.address
        self.size = ci.size
        self.mnem = ci.mnemonic
        self.ops = ci.op_str
        self.target = None
        self.mem = None       # (segment, base, index, scale, disp, size) of the first memory operand
        self.imm = None       # last immediate operand
        self.op0reg = None
        self.op0imm = None
        self.stop = False     # instruction terminates the program (e.g. int 21h/4Ch)
        groups = set(ci.groups)
        ops = ci.operands
        for n, op in enumerate(ops):
            if op.type == cx86.X86_OP_IMM:
                self.imm = op.imm & 0xffffffff
                if n == 0:
                    self.op0imm = self.imm
            elif op.type == cx86.X86_OP_MEM and self.mem is None:
                m = op.mem
                self.mem = (m.segment, m.base, m.index, m.scale, m.disp & 0xffffffff, op.size)
            elif op.type == cx86.X86_OP_REG and n == 0:
                self.op0reg = op.reg
        m = self.mnem.split()[-1]  # strip prefixes like 'notrack', 'bnd', 'rep'
        if capstone.CS_GRP_CALL in groups:
            if ops and ops[0].type == cx86.X86_OP_IMM:
                self.kind = K_CALL
                self.target = ops[0].imm & 0xffffffff
            else:
                self.kind = K_CALLI
        elif capstone.CS_GRP_JUMP in groups or m in ('loop', 'loope', 'loopne', 'jecxz', 'jcxz'):
            direct = ops and ops[0].type == cx86.X86_OP_IMM
            if m == 'jmp' or m == 'ljmp':
                self.kind = K_JMP if direct else K_JMPI
            else:
                self.kind = K_JCC if direct else K_JMPI
            if direct:
                self.target = ops[0].imm & 0xffffffff
        elif capstone.CS_GRP_RET in groups or capstone.CS_GRP_IRET in groups:
            self.kind = K_RET
        elif m == 'int':
            self.kind = K_INT
        elif m == 'hlt':
            self.kind = K_HLT
        elif m == 'into' or m == 'int3':
            self.kind = K_OTHER
        else:
            self.kind = K_OTHER

    @property
    def end(self):
        return self.addr + self.size

    def flow_ends(self):
        return self.stop or self.kind in (K_JMP, K_JMPI, K_RET, K_HLT)

class Routine:
    def __init__(self, addr, name=None):
        self.addr = addr
        self.name = name or f"sub_{addr:x}"
        self.named = name is not None
        self.insns = []          # addresses of instructions owned
        self.blocks = []         # (start, end) contiguous reachable ranges, end exclusive
        self.extent = (addr, addr)
        self.callers = set()     # routine entry addresses
        self.callees = set()
        self.xref_from = set()   # addresses of call/jmp/fixup sites pointing here
        self.strings = []        # (addr, text)
        self.vars = set()        # data addresses referenced
        self.ints = []           # (intno, service value or None)
        self.ports = set()
        self.annotations = []
        self.comments = []
        self.reasons = set()     # why this was considered a routine: entry, call, fptr, gap, map
        self.noreturn = False
        self.has_ret = False
        self.cleanup_votes = [0, 0]  # call sites followed by 'add esp, N' / not followed
        self.ret_pop = set()          # immediate operands of 'ret N'
        self.convention = None

    @property
    def size(self):
        return sum(e - s for s, e in self.blocks)

class Variable:
    def __init__(self, addr, name=None):
        self.addr = addr
        self.name = name
        self.named = name is not None
        self.size = 0         # access size hint in bytes
        self.kind = None      # 'string', 'ptr', 'code_ptr', None
        self.text = None
        self.xrefs = set()    # routine entry addresses referencing this
        self.comments = []
        self.addr_taken = False  # referenced as an immediate (pointer passed around)

class Analyzer:
    def __init__(self, le, verbose=False):
        self.le = le
        self.verbose = verbose
        le.apply_fixups()
        self.md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
        self.md.detail = True
        self.md.skipdata = False
        self.code_objs = [o for o in le.objects if o.is_code()]
        self.data_objs = [o for o in le.objects if not o.is_code()]
        self.insns = {}             # addr -> Insn
        self.insn_starts = []       # sorted list of instruction addresses (built after decoding)
        self.cov = {o.index: bytearray(o.vsize) for o in self.code_objs}  # 1: insn start, 2: insn body, 3: data
        self.labels = {}            # code addr -> label kind (loc/jpt)
        self.func_starts = {}       # addr -> set(reasons)
        self.routines = {}          # addr -> Routine
        self.owner = {}             # insn addr -> routine addr
        self.vars = {}              # addr -> Variable
        self.code_data = {}         # addr -> size, data embedded in code (jump tables etc.)
        self.jump_tables = {}       # jmp insn addr -> [targets]
        self.code_refs = {}         # addr -> access size, data inside code objects accessed through memory operands
        self.bad = set()            # addresses where decoding failed
        self.conflicts = []         # (addr, existing insn addr) overlapping decodes
        self.names = {}             # addr -> user supplied name (routines)
        self.var_names = {}
        self.map_annotations = defaultdict(list)
        self.map_comments = defaultdict(list)
        # fixup lookup tables
        self.fix_by_src = {}
        for fx in le.fixups:
            tgt = fx.target_addr(le.objects)
            self.fix_by_src[fx.src_addr] = (fx, tgt)
        self.fix_srcs = sorted(self.fix_by_src)

    # --- helpers -------------------------------------------------------------------------------
    def in_code(self, addr):
        return any(o.contains(addr) for o in self.code_objs)

    def in_data(self, addr):
        return any(o.contains(addr) for o in self.data_objs)

    def obj_of(self, addr):
        return self.le.object_at(addr)

    def fixups_in(self, start, end):
        i = bisect.bisect_left(self.fix_srcs, start)
        out = []
        while i < len(self.fix_srcs) and self.fix_srcs[i] < end:
            out.append(self.fix_by_src[self.fix_srcs[i]])
            i += 1
        return out

    def code_ptr_at(self, addr):
        '''If addr is the source of a 32-bit fixup pointing into code, return the target'''
        e = self.fix_by_src.get(addr)
        if e and e[0].src_type == SRC_OFF32 and e[1] is not None and self.in_code(e[1]):
            return e[1]
        return None

    def decode(self, addr):
        obj = self.obj_of(addr)
        if obj is None:
            return None
        o = addr - obj.base
        chunk = bytes(obj.data[o:o + 16])
        for ci in self.md.disasm(chunk, addr, 1):
            return Insn(ci)
        return None

    def add_func(self, addr, reason):
        if not self.in_code(addr):
            return False
        new = addr not in self.func_starts
        self.func_starts.setdefault(addr, set()).add(reason)
        return new

    # --- pass 1: recursive traversal ----------------------------------------------------------
    def cov_get(self, addr):
        obj = self.obj_of(addr)
        return self.cov[obj.index][addr - obj.base] if obj is not None and obj.index in self.cov else 0

    def overlaps(self, addr, end):
        '''True if [addr, end) would overlap with an already decoded instruction or embedded data'''
        obj = self.obj_of(addr)
        cov = self.cov[obj.index]
        o = addr - obj.base
        if cov[o] != 0:
            return True
        for i in range(o + 1, min(end - obj.base, len(cov))):
            if cov[i] != 0:
                return True
        return False

    def mark(self, addr, end, start_val=1, rest_val=2):
        obj = self.obj_of(addr)
        cov = self.cov[obj.index]
        o = addr - obj.base
        cov[o] = start_val
        for i in range(o + 1, min(end - obj.base, len(cov))):
            cov[i] = rest_val

    def next_covered(self, addr, maxlen=0x10000):
        obj = self.obj_of(addr)
        cov = self.cov[obj.index]
        o = addr - obj.base
        end = min(len(cov), o + maxlen)
        while o < end and cov[o] == 0:
            o += 1
        return obj.base + o

    def trace(self, seeds, noreturn=frozenset(), fptr_seeds=()):
        '''Recursive traversal. Code reached through calls and jumps is decoded before targets of code
        pointers, which have a higher chance of being something else (strings or tables in the code
        object), so that a wrong guess can not displace real code: instructions may never overlap.'''
        queue = list(seeds)
        fptrs = list(fptr_seeds)
        while queue or fptrs:
            if queue:
                addr = queue.pop()
            else:
                addr = fptrs.pop(0)
                if addr in self.insns or addr in self.bad:
                    continue
                txt = self.read_cstring(addr)
                is_text = txt is not None and len(txt) >= 3 and all(0x20 <= ord(c) < 0x7f or c in '\t\r\n' for c in txt)
                if is_text or not self.speculative(addr, self.next_covered(addr)):
                    # text or a table stored in the code object and passed around by address
                    self.code_refs.setdefault(addr, 1)
                    reasons = self.func_starts.get(addr)
                    if reasons is not None and reasons <= {'fptr'}:
                        del self.func_starts[addr]
                    continue
            while True:
                if addr in self.insns or addr in self.bad or not self.in_code(addr):
                    break
                if addr in self.code_data:
                    break
                insn = self.decode(addr)
                if insn is None or self.overlaps(addr, insn.end):
                    self.bad.add(addr)
                    break
                if insn.mnem == 'add' and insn.ops == 'byte ptr [eax], al':
                    # 00 00 never occurs in compiled code: zeroed data behind a call which does not
                    # return or which reads inline data from its return address
                    self.bad.add(addr)
                    break
                # sanity: a fixup must not straddle the end of an instruction
                broken = False
                for fx, tgt in self.fixups_in(addr - 5, insn.end):
                    size = SRC_SIZE.get(fx.src_type, 4)
                    if fx.src_addr < insn.end < fx.src_addr + size or fx.src_addr < addr < fx.src_addr + size:
                        broken = True
                        break
                if broken:
                    self.bad.add(addr)
                    break
                self.insns[addr] = insn
                self.mark(addr, insn.end)
                k = insn.kind
                if k == K_INT and insn.imm == 0x21 and self.int_service(insn) == 0x4c:
                    insn.stop = True
                if k == K_CALL:
                    if self.in_code(insn.target):
                        if self.add_func(insn.target, 'call') or insn.target not in self.insns:
                            queue.append(insn.target)
                elif k == K_JMP or k == K_JCC:
                    if self.in_code(insn.target):
                        self.labels.setdefault(insn.target, 'loc')
                        queue.append(insn.target)
                elif k == K_JMPI or k == K_CALLI:
                    targets = self.resolve_table(insn)
                    if targets:
                        if k == K_JMPI:
                            self.jump_tables[addr] = targets
                            for t in targets:
                                self.labels[t] = 'case'
                                queue.append(t)
                        else:
                            for t in targets:
                                if self.add_func(t, 'fptr'):
                                    fptrs.append(t)
                # code pointers loaded as immediates (callbacks, interrupt handlers)
                for fx, tgt in self.fixups_in(addr, insn.end):
                    if tgt is not None and self.in_code(tgt) and fx.src_type == SRC_OFF32:
                        if insn.mem and insn.mem[4] == tgt:
                            # memory operand: a table or constant stored in the code object
                            if k not in (K_JMPI, K_CALLI):
                                self.code_refs[tgt] = max(self.code_refs.get(tgt, 0), insn.mem[5])
                            continue
                        if self.add_func(tgt, 'fptr'):
                            fptrs.append(tgt)
                if insn.flow_ends():
                    break
                if k == K_CALL and insn.target in noreturn:
                    break
                addr = insn.end

    def resolve_table(self, insn):
        '''Try to resolve an indirect jmp/call through a table of 32-bit code pointers.'''
        if not insn.mem:
            return None
        seg, base, index, scale, disp, size = insn.mem
        if size != 4 or not (index or base):
            return None
        if disp not in self.fix_by_src and not (self.in_code(disp) or self.in_data(disp)):
            return None
        # bound from a preceding "cmp reg, N" if one can be found nearby
        limit = None
        a = insn.addr
        for _ in range(6):
            prev = self.prev_insn(a)
            if prev is None:
                break
            if prev.mnem == 'cmp' and prev.imm is not None and prev.imm < 0x1000:
                limit = prev.imm + 1
                break
            a = prev.addr
        targets = []
        pos = disp
        zeros = []
        while True:
            t = self.code_ptr_at(pos)
            if t is None:
                # unused cases of a switch are sometimes left as null entries
                v = self.le.read_u32(pos)
                if v == 0 and pos not in self.fix_by_src and len(zeros) < 8 and (limit is None or len(targets) + len(zeros) < limit):
                    zeros.append(pos)
                    pos += 4
                    continue
                break
            for z in zeros:
                if self.in_code(z):
                    self.code_data[z] = 4
                    self.mark(z, z + 4, 3, 3)
            zeros = []
            targets.append(t)
            if self.in_code(pos):
                self.code_data[pos] = 4
                self.mark(pos, pos + 4, 3, 3)
            pos += 4
            if limit is not None and len(targets) >= limit:
                break
            if len(targets) > 4096:
                break
        return targets

    def prev_insn(self, addr):
        # linear scan backwards for an already decoded instruction ending at addr
        for back in range(1, 16):
            p = self.insns.get(addr - back)
            if p is not None and p.end == addr:
                return p
        return None

    def seed_from_fixups(self):
        '''Code pointers stored in data or in code tables which were not attributed to jump tables.
        Returns (function pointer targets, targets of pointer tables inside the code object)'''
        new = []
        cases = []
        jt_srcs = set()
        for jaddr, tg in self.jump_tables.items():
            insn = self.insns[jaddr]
            disp = insn.mem[4]
            for k in range(len(tg)):
                jt_srcs.add(disp + 4 * k)
        # sources covered by decoded instructions
        for src, (fx, tgt) in self.fix_by_src.items():
            if tgt is None or not self.in_code(tgt) or fx.src_type != SRC_OFF32:
                continue
            if src in jt_srcs or tgt in self.code_refs:
                continue
            if self.in_code(src) and self.insn_covering(src) is not None:
                continue  # handled while tracing
            if self.in_code(src):
                # pointer table inside code which no decoded jump referenced (yet); could be a
                # jump table reached through a register, add a label for the target. A single pointer
                # is more likely the operand of an instruction which has not been decoded yet.
                if self.code_ptr_at(src - 4) is None and self.code_ptr_at(src + 4) is None:
                    continue
                # (it is only marked as data once tracing is complete, it could also be the
                # operand of an instruction in code which has not been reached yet)
                if tgt not in self.func_starts and tgt not in self.insns and tgt not in self.bad:
                    self.labels.setdefault(tgt, 'case')
                    cases.append(tgt)
                continue
            if self.add_func(tgt, 'fptr'):
                new.append(tgt)
        return new, cases

    def insn_covering(self, addr):
        for back in range(0, 16):
            p = self.insns.get(addr - back)
            if p is not None and p.addr <= addr < p.end:
                return p
        return None

    # --- pass 2: partition into routines -------------------------------------------------------
    def successors(self, insn, noreturn):
        out = []
        k = insn.kind
        if k == K_JMP or k == K_JCC:
            if insn.target in self.insns:
                out.append((insn.target, 'jmp'))
        elif k == K_JMPI and insn.addr in self.jump_tables:
            for t in self.jump_tables[insn.addr]:
                if t in self.insns:
                    out.append((t, 'jmp'))
        if not insn.flow_ends():
            if not (k == K_CALL and insn.target in noreturn):
                if insn.end in self.insns:
                    out.append((insn.end, 'fall'))
        return out

    def partition(self, noreturn=frozenset()):
        '''Assign decoded instructions to routines. Watcom does not split functions, so a routine only
        follows jumps which stay between its entrypoint and the next routine entrypoint; a jump leaving
        that region is a tail call (or a jump into shared code of another routine).'''
        self.owner = {}
        self.routines = {}
        start_set = set(self.func_starts)
        sorted_starts = sorted(start_set)

        def region_end(s):
            i = bisect.bisect_right(sorted_starts, s)
            return sorted_starts[i] if i < len(sorted_starts) else 1 << 32

        def claim(s, host=None, reason=None):
            owner = host if host is not None else s
            if host is None:
                r = Routine(s, self.names.get(s))
                r.reasons = set(self.func_starts[s]) or {'map'}
                self.routines[s] = r
            else:
                self.routines[host].reasons.add(reason)
            lo = owner
            hi = region_end(owner) if host is None else region_end(s)
            stack = [s]
            while stack:
                a = stack.pop()
                if a in self.owner:
                    continue
                if a != s and a in start_set:
                    continue
                self.owner[a] = owner
                for t, how in self.successors(self.insns[a], noreturn):
                    if t in start_set or t in self.owner:
                        continue   # tail call, fallthrough into the next routine or already claimed
                    if how == 'jmp' and not (lo <= t < hi) and not (host is not None and s <= t < hi):
                        continue   # leaves the routine's region
                    stack.append(t)

        for s in sorted_starts:
            if s in self.insns:
                claim(s)
        # instructions not reached from any routine entrypoint within its region
        added = 0
        for a in sorted(self.insns):
            if a in self.owner:
                continue
            i = bisect.bisect_right(sorted_starts, a) - 1
            if self.labels.get(a) == 'case' and i >= 0 and sorted_starts[i] in self.routines:
                # cases of a switch whose dispatch could not be resolved, attach to the routine
                # the code is located in
                claim(a, sorted_starts[i], 'chunks')
                continue
            # only reached through a jump from another routine: a tail called routine
            self.func_starts.setdefault(a, set()).add('tail' if a in self.labels else 'orphan')
            start_set.add(a)
            bisect.insort(sorted_starts, a)
            claim(a)
            added += 1
        return added

    def finalize_routines(self, noreturn=frozenset()):
        per = defaultdict(list)
        for a, s in self.owner.items():
            per[s].append(a)
        for s, r in self.routines.items():
            addrs = sorted(per[s])
            r.insns = addrs
            blocks = []
            for a in addrs:
                e = self.insns[a].end
                if blocks and blocks[-1][1] == a:
                    blocks[-1][1] = e
                elif blocks and self.only_code_data_between(blocks[-1][1], a):
                    # embedded jump table between two parts of the routine
                    blocks[-1][1] = e
                else:
                    blocks.append([a, e])
            r.blocks = [tuple(b) for b in blocks]
            r.extent = r.blocks[0] if r.blocks else (s, s)
            for a in addrs:
                insn = self.insns[a]
                if insn.kind == K_RET:
                    r.has_ret = True

    def only_code_data_between(self, start, end):
        a = start
        while a < end:
            sz = self.code_data.get(a)
            if not sz:
                return False
            a += sz
        return a == end

    def routine_exits(self, r, noreturn=frozenset()):
        '''Returns (returns, tails): whether the routine can return by itself (ret, indirect jump,
        branch into undecoded code), and the set of other routines it can continue into
        (tail jumps, conditional jumps or falling through into a following routine)'''
        returns = False
        tails = set()
        s = r.addr
        for a in r.insns:
            insn = self.insns[a]
            k = insn.kind
            if k == K_RET or k == K_JMPI and a not in self.jump_tables:
                returns = True
            if k in (K_JMP, K_JCC):
                t = insn.target
                if t not in self.insns:
                    returns = True
                elif t != s and self.owner.get(t) != s:
                    tails.add(self.owner.get(t, t))
            if not insn.flow_ends() and not (k == K_CALL and insn.target in noreturn):
                n = insn.end
                if n not in self.insns:
                    if k != K_CALL:
                        returns = True
                elif self.owner.get(n) != s:
                    tails.add(self.owner.get(n, n))
        return returns, tails

    def find_noreturn(self, noreturn=frozenset()):
        '''Routines which never return: greatest fixpoint of routines that have no way of returning
        by themselves, and only continue into other routines which never return either'''
        info = {s: self.routine_exits(r, noreturn) for s, r in self.routines.items() if r.insns}
        cand = set(s for s, (ret, tails) in info.items() if not ret)
        changed = True
        while changed:
            changed = False
            for s in list(cand):
                if any(t not in cand for t in info[s][1]):
                    cand.discard(s)
                    changed = True
        return cand

    # --- pass 3: gaps --------------------------------------------------------------------------
    def gaps(self):
        '''Ranges in code objects not covered by decoded instructions or known embedded data'''
        covered = []
        for a, insn in self.insns.items():
            covered.append((a, insn.end))
        for a, sz in self.code_data.items():
            covered.append((a, a + sz))
        covered.sort()
        out = []
        for obj in self.code_objs:
            pos = obj.base
            end = obj.base + obj.vsize
            for s, e in covered:
                if e <= pos or not obj.contains(s):
                    continue
                if s > pos:
                    out.append((pos, s))
                pos = max(pos, e)
            if pos < end:
                out.append((pos, end))
        return out

    def is_padding(self, data):
        data = bytes(data)
        return self.skip_nops(data, 0) >= len(data)

    SUSPICIOUS = frozenset(('arpl', 'bound', 'into', 'aaa', 'aas', 'daa', 'das', 'aam', 'aad', 'salc', 'hlt',
                            'insb', 'insw', 'insd', 'outsb', 'outsw', 'outsd', 'icebp', 'int1', 'ljmp', 'lcall',
                            'retf', 'into', 'wait', 'cmc', 'lock'))

    def speculative(self, start, limit):
        '''Try to decode a routine at start without leaving [start, limit) except for branches into
        known code or calls to the start of other unexplored areas. Returns True if it looks like
        plausible code ending with ret/jmp.'''
        seen = {}
        queue = [start]
        ended = False
        while queue:
            a = queue.pop()
            while a not in seen:
                if a in self.insns:
                    ended = True  # flows into known code at an instruction boundary (shared epilogue)
                    break
                if not (start <= a < limit):
                    return False
                insn = self.decode(a)
                if insn is None or insn.end > limit or self.overlaps(a, insn.end):
                    return False
                if insn.mnem.split()[-1] in self.SUSPICIOUS or insn.mnem.startswith(('rep', 'lock')) and insn.kind != K_OTHER:
                    return False
                if insn.mnem == 'add' and insn.ops == 'byte ptr [eax], al':
                    return False  # 00 00, zero filled data
                # a fixup must line up with an operand of the instruction
                for fx, tgt in self.fixups_in(a - 3, insn.end):
                    size = SRC_SIZE.get(fx.src_type, 4)
                    if fx.src_addr < a < fx.src_addr + size or fx.src_addr + size > insn.end:
                        return False
                seen[a] = insn
                if insn.kind in (K_JMP, K_JCC, K_CALL):
                    t = insn.target
                    if not self.in_code(t):
                        return False
                    if insn.kind != K_CALL and start <= t < limit:
                        queue.append(t)
                    elif not (start <= t < limit) and t not in self.insns and self.insn_covering(t) is not None:
                        return False  # into the middle of a known instruction
                if insn.kind == K_RET or insn.kind == K_JMP or insn.kind == K_JMPI:
                    ended = True
                    break
                a = insn.end
        return ended and len(seen) >= 2

    PROLOGUE_BYTES = frozenset((0x50, 0x51, 0x52, 0x53, 0x55, 0x56, 0x57, 0x60, 0x68, 0x6a, 0x83, 0x81, 0x8b,
                                0x89, 0xb8, 0xa1, 0x31, 0x66, 0xfb, 0xfa, 0x1e, 0x06, 0x0f))
    # alignment fillers emitted by the Watcom compiler/linker and assemblers
    NOPS = (b'\x8d\x80\x00\x00\x00\x00', b'\x8d\x74\x26\x00', b'\x8d\x40\x00', b'\x8d\x76\x00',
            b'\x8d\x49\x00', b'\x8b\xc0', b'\x89\xc0', b'\x8b\xff', b'\x90', b'\x00', b'\xcc')

    def skip_nops(self, data, i):
        while i < len(data):
            for n in self.NOPS:
                if data.startswith(n, i):
                    i += len(n)
                    break
            else:
                break
        return i

    def scan_gaps(self, noreturn=frozenset()):
        '''Look for unreferenced routines in unexplored areas of the code objects: try the start of each
        gap (after alignment padding), and positions following a return instruction inside the gap'''
        found = []
        for s, e in self.gaps():
            obj = self.obj_of(s)
            data = bytes(obj.data[s - obj.base:e - obj.base])
            if self.is_padding(data):
                continue
            cands = [s + self.skip_nops(data, 0)]
            for i in range(1, len(data)):
                if data[i - 1] in (0xc3, 0xcf) or (i >= 3 and data[i - 3] == 0xc2 and data[i - 1] == 0):
                    j = self.skip_nops(data, i)
                    if j < len(data) and data[j] in self.PROLOGUE_BYTES:
                        cands.append(s + j)
            for c in cands:
                if c >= e or c in self.code_refs or c in self.bad or self.cov_get(c) != 0:
                    continue
                if self.speculative(c, self.next_covered(c)):
                    found.append(c)
                    self.add_func(c, 'gap')
                    self.trace([c], noreturn)
        return found

    # --- full analysis --------------------------------------------------------------------------
    def reset(self):
        self.insns = {}
        self.labels = {}
        self.func_starts = {}
        self.code_data = {}
        self.jump_tables = {}
        self.code_refs = {}
        self.bad = set()
        self.cov = {o.index: bytearray(o.vsize) for o in self.code_objs}

    def analyze(self, extra_seeds, noreturn):
        self.reset()
        entry = self.le.entry_point()
        self.add_func(entry, 'entry')
        self.trace([entry], noreturn)
        self.explore(noreturn)
        # entrypoints from the map which the analysis did not find by itself
        missing = [s for s in extra_seeds if self.in_code(s) and s not in self.func_starts]
        if missing:
            for s in missing:
                self.add_func(s, 'map')
            self.trace([s for s in missing if s not in self.insns], noreturn)
            self.explore(noreturn)
        # pointers stored in code objects outside of instructions (tables)
        for src, (fx, tgt) in self.fix_by_src.items():
            if self.in_code(src) and src not in self.code_data and fx.src_type == SRC_OFF32 \
                    and not self.overlaps(src, src + 4):
                self.code_data[src] = 4
                self.mark(src, src + 4, 3, 3)
        self.partition(noreturn)
        self.finalize_routines(noreturn)

    def explore(self, noreturn):
        '''Follow code pointers found in fixups and look for routines in unexplored areas until nothing
        new turns up'''
        for it in range(20):
            new, cases = self.seed_from_fixups()
            self.trace(cases, noreturn, new)
            gap = self.scan_gaps(noreturn)
            if not new and not cases and not gap:
                break

    def run(self, extra_seeds=()):
        # Code following a call to a routine which never returns (exit, abort, error handlers) is
        # often not code at all, so the analysis is repeated until the set of noreturn routines is stable.
        noret = frozenset()
        for _ in range(5):
            self.analyze(extra_seeds, noret)
            nr = frozenset(self.find_noreturn(noret)) | noret
            if nr == noret:
                break
            noret = nr
        self.noreturn = noret
        for s in noret:
            if s in self.routines:
                self.routines[s].noreturn = True
        self.insn_starts = sorted(self.insns)
        self.collect_refs()

    # --- references, variables, strings ----------------------------------------------------------
    def read_cstring(self, addr, maxlen=512, minlen=2):
        obj = self.obj_of(addr)
        if obj is None:
            return None
        o = addr - obj.base
        data = obj.data
        out = bytearray()
        while o < len(data) and len(out) < maxlen:
            b = data[o]
            if b == 0:
                break
            if not (0x20 <= b < 0x7f or b in (0x09, 0x0a, 0x0d) or 0x80 <= b < 0xff):
                return None
            out.append(b)
            o += 1
        if o >= len(data) or data[o] != 0:
            return None
        if len(out) < minlen:
            return None
        printable = sum(1 for b in out if 0x20 <= b < 0x7f or b in (0x0a, 0x0d, 0x09))
        if printable < len(out) * 0.85:
            return None
        alpha = sum(1 for b in out if chr(b).isalnum() or b == 0x20)
        if alpha < len(out) * 0.5:
            return None
        return out.decode('latin-1')

    def int_service(self, insn):
        '''Find the value of ah/ax loaded before an int instruction in the same block'''
        a = insn.addr
        intno = insn.imm
        for _ in range(12):
            p = self.prev_insn(a)
            if p is None or p.flow_ends() or p.kind in (K_CALL, K_CALLI, K_JCC):
                break
            if p.mnem == 'mov' and p.op0reg is not None and p.imm is not None and ',' in p.ops:
                reg = p.ops.split(',')[0].strip()
                if reg == 'ah':
                    return p.imm & 0xff
                if reg in ('ax', 'eax'):
                    v = p.imm & 0xffff
                    if intno in (0x31,) or (intno == 0x10 and (v >> 8) == 0x4f):
                        return v
                    return v >> 8 if intno in (0x21, 0x10, 0x16, 0x1a) else v
            if p.mnem == 'xor' and p.ops in ('eax, eax', 'ax, ax'):
                return 0
            a = p.addr
        return None

    def port_of(self, insn):
        '''Port number of an in/out instruction, either immediate or dx loaded in the same block'''
        ops = [o.strip() for o in insn.ops.split(',')]
        if insn.mnem == 'out' and ops and ops[0] not in ('dx',):
            try:
                return int(ops[0], 16) if ops[0].startswith('0x') else int(ops[0])
            except ValueError:
                return None
        if insn.mnem == 'in' and len(ops) > 1 and ops[1] != 'dx':
            try:
                return int(ops[1], 16) if ops[1].startswith('0x') else int(ops[1])
            except ValueError:
                return None
        a = insn.addr
        for _ in range(12):
            p = self.prev_insn(a)
            if p is None or p.flow_ends() or p.kind in (K_CALL, K_CALLI):
                break
            if p.mnem == 'mov' and p.ops.startswith(('dx,', 'edx,')) and p.imm is not None:
                return p.imm & 0xffff
            if p.mnem in ('inc', 'dec', 'add', 'sub') and p.ops.startswith(('dx', 'edx')):
                return None
            a = p.addr
        return None

    def collect_refs(self):
        # every fixup target in data objects is a variable
        for src, (fx, tgt) in self.fix_by_src.items():
            if tgt is None or not (self.in_data(tgt) or tgt in self.code_refs) or tgt in self.routines:
                continue
            v = self.vars.get(tgt)
            if v is None:
                v = self.vars[tgt] = Variable(tgt, self.var_names.get(tgt))
        for s, r in self.routines.items():
            for a in r.insns:
                insn = self.insns[a]
                if insn.kind in (K_CALL, K_JMP) and insn.target in self.routines and insn.target != s:
                    if insn.kind == K_CALL or insn.target in self.func_starts:
                        r.callees.add(insn.target)
                        callee = self.routines[insn.target]
                        callee.callers.add(s)
                        callee.xref_from.add(a)
                for fx, tgt in self.fixups_in(a, insn.end):
                    if tgt is None:
                        continue
                    if tgt in self.vars:
                        v = self.vars[tgt]
                        v.xrefs.add(s)
                        r.vars.add(tgt)
                        if insn.mem and insn.mem[4] == tgt and not insn.mem[2] and not insn.mem[1]:
                            v.size = max(v.size, insn.mem[5])
                        elif not (insn.mem and insn.mem[4] == tgt):
                            v.addr_taken = True
                    elif tgt in self.routines and tgt != s:
                        self.routines[tgt].xref_from.add(a)
                        if insn.kind != K_JMPI:
                            r.callees.add(tgt)
                            self.routines[tgt].callers.add(s)
                if insn.kind == K_CALL and insn.target in self.routines:
                    nxt = self.insns.get(insn.end)
                    callee = self.routines[insn.target]
                    if nxt is not None and nxt.mnem == 'add' and nxt.ops.startswith('esp, '):
                        callee.cleanup_votes[0] += 1
                    else:
                        callee.cleanup_votes[1] += 1
                if insn.kind == K_RET:
                    r.ret_pop.add(insn.imm or 0)
                if insn.kind == K_INT:
                    r.ints.append((insn.imm, self.int_service(insn)))
                elif insn.mnem in ('in', 'out'):
                    p = self.port_of(insn)
                    if p is not None:
                        r.ports.add(p)
        # classify variables
        for addr, v in self.vars.items():
            if addr in self.fix_by_src:
                fx, tgt = self.fix_by_src[addr]
                v.kind = 'code_ptr' if tgt is not None and self.in_code(tgt) else 'ptr'
                v.size = max(v.size, 4)
                continue
            text = self.read_cstring(addr, minlen=1 if v.addr_taken else 2)
            if text is not None and v.size in (0, 1):
                v.kind = 'string'
                v.text = text
                v.size = len(text.encode('latin-1')) + 1
        for s, r in self.routines.items():
            for va in sorted(r.vars):
                v = self.vars[va]
                if v.kind == 'string':
                    r.strings.append((va, v.text))
        for s, r in self.routines.items():
            r.convention = self.guess_convention(r)
        self.assign_var_names()

    def guess_convention(self, r):
        '''Watcom C uses a register calling convention by default (arguments in eax, edx, ebx, ecx,
        the rest on the stack, removed by the callee), but code built with __cdecl/-ecc or written in
        assembly takes all arguments on the stack and leaves the cleanup to the caller.'''
        for ann in self.map_annotations.get(r.addr, []):
            if ann.startswith('conv:'):
                return ann[5:]
        cdecl, reg = r.cleanup_votes
        if any(n > 0 for n in r.ret_pop):
            return '__watcall'
        if cdecl > reg:
            return '__cdecl'
        if cdecl + reg == 0:
            # no direct callers: look for stack argument access before anything is pushed
            for a in r.insns[:8]:
                insn = self.insns[a]
                if insn.mem and insn.mem[1] == cx86.X86_REG_ESP and insn.mem[4] in (4, 8, 12, 16):
                    return '__cdecl'
                if insn.mnem in ('push', 'sub', 'call', 'enter') or insn.flow_ends():
                    break
        return '__watcall'

    def assign_var_names(self):
        used = set(r.name for r in self.routines.values())
        for addr in sorted(self.vars):
            v = self.vars[addr]
            if v.named:
                used.add(v.name)
                continue
            if v.kind == 'string':
                words = re.findall(r'[A-Za-z0-9]+', v.text)
                base = 'a' + ''.join(w[:1].upper() + w[1:] for w in words)[:24] if words else 'asc'
                name = base
                if name in used:
                    name = f"{base}_{addr:x}"
            else:
                prefix = { 1: 'byte', 2: 'word', 4: 'dword', 6: 'fword', 8: 'qword', 10: 'tbyte' }.get(v.size, 'unk')
                if v.kind == 'code_ptr':
                    prefix = 'funcptr'
                elif v.kind == 'ptr':
                    prefix = 'off'
                name = f"{prefix}_{addr:x}"
            used.add(name)
            v.name = name

    # --- symbols -------------------------------------------------------------------------------
    def build_symbols(self):
        self.sym = {}
        for a, r in self.routines.items():
            self.sym[a] = r.name
        for a, v in self.vars.items():
            self.sym.setdefault(a, v.name)
        for a, kind in self.labels.items():
            if a not in self.sym:
                self.sym[a] = f"loc_{a:x}"
        for jaddr in self.jump_tables:
            disp = self.insns[jaddr].mem[4]
            if disp not in self.sym:
                self.sym[disp] = f"jpt_{disp:x}"
        self.sym_addrs = sorted(self.sym)

    def symbolize(self, value):
        if value in self.sym:
            return self.sym[value]
        return None

    def format_insn(self, insn):
        text = insn.ops
        repl = {}
        if insn.target is not None and insn.kind in (K_CALL, K_JMP, K_JCC):
            s = self.symbolize(insn.target)
            if s:
                repl[insn.target] = s
        for fx, tgt in self.fixups_in(insn.addr, insn.end):
            if tgt is not None:
                s = self.symbolize(tgt)
                if s:
                    repl[tgt] = s
        if repl:
            def sub(m):
                v = int(m.group(0), 16)
                return repl.get(v, m.group(0))
            text = re.sub(r'0x[0-9a-f]+', sub, text)
        return f"{insn.mnem} {text}".rstrip()

    def insn_comment(self, insn):
        parts = []
        for fx, tgt in self.fixups_in(insn.addr, insn.end):
            v = self.vars.get(tgt)
            if v is not None and v.kind == 'string':
                t = v.text if len(v.text) < 60 else v.text[:57] + '...'
                parts.append(json.dumps(t))
        if insn.kind == K_INT:
            svc = self.int_service(insn)
            name = INT_SERVICES.get((insn.imm, svc)) if svc is not None else None
            if name is None and insn.imm == 0x10 and svc is not None:
                name = INT_SERVICES.get((0x10, svc >> 8)) if svc > 0xff else None
            desc = INT_NAMES.get(insn.imm, '')
            parts.append(f"{desc} " + (name or (f"service 0x{svc:x}" if svc is not None else '')).strip())
        elif insn.mnem in ('in', 'out'):
            p = self.port_of(insn)
            if p is not None:
                tag = port_tag(p)
                parts.append(f"port 0x{p:x}" + (f" ({tag})" if tag else ''))
        if insn.kind == K_CALL and insn.target in self.routines and self.routines[insn.target].noreturn:
            parts.append('noreturn')
        return '; ' + ', '.join(p for p in parts if p) if parts else ''

    # --- tagging -------------------------------------------------------------------------------
    def routine_tags(self, r):
        tags = set()
        for intno, svc in r.ints:
            name = INT_SERVICES.get((intno, svc)) if svc is not None else None
            if name:
                tags.add(name)
            else:
                tags.add(f"int{intno:x}h")
        for p in r.ports:
            t = port_tag(p)
            tags.add(t or f"port{p:x}")
        if r.noreturn:
            tags.add('noreturn')
        if 'gap' in r.reasons and not r.callers:
            tags.add('unreferenced')
        return sorted(tags)

    # --- map file ------------------------------------------------------------------------------
    def seg_name(self, obj):
        return f"{obj.kind().lower()}{obj.index}"

    # names generated by assign_var_names(), these are not treated as user supplied
    AUTO_VAR_NAME = r'^((byte|word|dword|qword|fword|tbyte|unk|off|funcptr)_[0-9a-f]+|a[A-Z0-9][A-Za-z0-9]*(_[0-9a-f]+)?|asc(_[0-9a-f]+)?)$'

    def load_map(self, path):
        '''Read names, annotations and comments from a previously saved (and possibly edited) map.
        Returns extra routine entrypoints which should be used as seeds.'''
        segs = {}
        seeds = []
        pending_comments = []
        rx_seg = re.compile(r'^(\w+)\s+(CODE|DATA|CONST|STACK)\s+([0-9a-fA-F]+)')
        rx_rtn = re.compile(r'^([\w@$?.]+):\s+(\w+)\s+(NEAR|FAR)\s+([0-9a-fA-F]+)-([0-9a-fA-F]+)(.*)$')
        rx_var = re.compile(r'^([\w@$?.]+):\s+(\w+)\s+VAR\s+([0-9a-fA-F]+)(.*)$')
        with open(path) as f:
            for line in f:
                line = line.rstrip('\n')
                if not line.strip():
                    continue
                if line.startswith('#'):
                    c = line[1:].strip()
                    if c.startswith('@'):
                        pending_comments.append(c[1:].strip())
                    continue
                m = rx_seg.match(line)
                if m:
                    segs[m.group(1)] = int(m.group(3), 16)
                    continue
                m = rx_rtn.match(line)
                if m:
                    name, seg, _, start, _, rest = m.groups()
                    if seg not in segs:
                        continue
                    addr = segs[seg] + int(start, 16)
                    curated = False
                    if not name.startswith('sub_'):
                        self.names[addr] = name
                        curated = True
                    for tok in rest.split():
                        if not re.match(r'^[RU][0-9a-fA-F]+-[0-9a-fA-F]+$', tok) and tok not in ('noreturn', 'unreferenced'):
                            self.map_annotations[addr].append(tok)
                            curated = True
                    if pending_comments:
                        self.map_comments[addr].extend(pending_comments)
                        pending_comments = []
                        curated = True
                    # routines the analysis produced itself are found again, only the ones somebody
                    # named, annotated or commented (or added by hand) are used as additional entrypoints
                    if curated:
                        seeds.append(addr)
                    continue
                m = rx_var.match(line)
                if m:
                    name, seg, off, rest = m.groups()
                    if seg not in segs:
                        continue
                    addr = segs[seg] + int(off, 16)
                    if not re.match(self.AUTO_VAR_NAME, name):
                        self.var_names[addr] = name
                    pending_comments = []
        return seeds

    def save_map(self, path):
        objs = self.le.objects
        default = self.le.hdr('auto_data_object')
        with open(path, 'w') as f:
            w = f.write
            w(f"# Generated by ledisasm v{VERSION} from {os.path.basename(self.le.path)}\n")
            w("#\n# Size of the executable's image covered by the map (sum of object sizes)\n#\n")
            w(f"Size {sum(o.vsize for o in objs):x}\n")
            w("#\n# LE objects, one per line, syntax is \"SegmentName Type(CODE/DATA) LinearBaseAddress [default]\"\n")
            w("# All offsets below are relative to the base of the object they belong to; linear address = base + offset\n#\n")
            for o in objs:
                w(f"{self.seg_name(o)} {'CODE' if o.is_code() else 'DATA'} {o.base:x}" + (" default" if o.index == default else '') + "\n")
            w("#\n# Discovered routines, one per line, syntax is \"RoutineName: Segment NEAR Extents [R/U]Block1 [R/U]Block2... [annotation1] [annotation2]...\"\n")
            w("# Rename a routine by editing its name, it will be preserved on the next run with --map. Lines starting with '#@'\n")
            w("# directly above a routine are kept as comments and are shown in the assembly listing.\n")
            w("# Annotations (besides the mzmap ones: ignore complete external detached assembly duplicate):\n")
            w("# noreturn - routine never returns, unreferenced - found by scanning gaps, no references,\n")
            w("# conv:NAME - override the guessed calling convention (__watcall, __cdecl, __regsafe) for exports\n#\n")
            for a in sorted(self.routines):
                r = self.routines[a]
                o = self.obj_of(a)
                b = o.base
                for c in self.map_comments.get(a, []):
                    w(f"#@ {c}\n")
                ext = r.extent
                line = f"{r.name}: {self.seg_name(o)} NEAR {ext[0] - b:x}-{ext[1] - 1 - b:x}"
                for s, e in r.blocks:
                    line += f" R{s - b:x}-{e - 1 - b:x}"
                ann = list(self.map_annotations.get(a, []))
                if r.noreturn and 'noreturn' not in ann:
                    ann.append('noreturn')
                if 'gap' in r.reasons and not r.callers and 'unreferenced' not in ann:
                    ann.append('unreferenced')
                if ann:
                    line += ' ' + ' '.join(ann)
                w(line + "\n")
            w("#\n# Discovered variables, one per line, syntax is \"VariableName: Segment VAR OffsetWithinSegment\"\n#\n")
            for a in sorted(self.vars):
                v = self.vars[a]
                o = self.obj_of(a)
                w(f"{v.name}: {self.seg_name(o)} VAR {a - o.base:x}\n")

    # --- listing -------------------------------------------------------------------------------
    def routine_header(self, r):
        lines = []
        lines.append('')
        lines.append(f"; {'=' * 100}")
        tags = self.routine_tags(r)
        lines.append(f"; {r.name}  [0x{r.addr:x}, {r.size} bytes, {len(r.insns)} instructions]" + (f"  <{' '.join(tags)}>" if tags else ''))
        for c in self.map_comments.get(r.addr, []):
            lines.append(f"; {c}")
        if self.map_annotations.get(r.addr):
            lines.append(f"; annotations: {' '.join(self.map_annotations[r.addr])}")
        if r.callers:
            names = [self.routines[c].name for c in sorted(r.callers)]
            more = f" (+{len(names) - 12} more)" if len(names) > 12 else ''
            lines.append(f"; called by: {', '.join(names[:12])}{more}")
        elif r.xref_from:
            lines.append(f"; referenced from: {', '.join(f'0x{x:x}' for x in sorted(r.xref_from)[:8])}")
        else:
            if 'entry' in r.reasons:
                lines.append("; program entrypoint")
            elif 'fptr' in r.reasons:
                lines.append("; address taken (function pointer)")
            else:
                lines.append("; no references found")
        if r.strings:
            for sa, st in r.strings[:10]:
                t = st if len(st) < 70 else st[:67] + '...'
                lines.append(f";   uses string {json.dumps(t)}")
            if len(r.strings) > 10:
                lines.append(f";   ... and {len(r.strings) - 10} more strings")
        if len(r.blocks) > 1:
            lines.append(f"; blocks: {' '.join(f'{s:x}-{e - 1:x}' for s, e in r.blocks)}")
        lines.append(f"; {'=' * 100}")
        return lines

    def code_lines(self, obj, start, end):
        '''Listing lines for the part [start, end) of a code object'''
        out = []
        a = start
        raw = obj.data
        jt_starts = {self.insns[j].mem[4]: j for j in self.jump_tables}
        cur = None
        while a < end:
            if a in self.routines:
                out.extend(self.routine_header(self.routines[a]))
                out.append(f"{self.routines[a].name}:")
            elif a in self.sym and (a in self.labels or a in jt_starts or a in self.vars):
                out.append(f"{self.sym[a]}:")
            insn = self.insns.get(a)
            if insn is not None and a in self.owner:
                own = self.owner[a]
                if a in self.routines:
                    cur = a
                elif own != cur and cur is not None:
                    # code physically located here but reached from another routine
                    out.append(f"    ; ---- chunk of {self.routines[own].name}")
                    cur = own
                txt = self.format_insn(insn)
                cmt = self.insn_comment(insn)
                hexb = raw[a - obj.base:min(insn.end, a + 8) - obj.base].hex() + ('..' if insn.size > 8 else '')
                out.append(f"    {txt:<44} ; {a:06x} {hexb:<18}{cmt[2:] if cmt else ''}".rstrip())
                if insn.kind == K_JMPI and a in self.jump_tables:
                    out.append(f"    ; switch jump, {len(self.jump_tables[a])} cases")
                if insn.kind in (K_RET, K_JMP, K_JMPI):
                    out.append('')
                a = insn.end
                continue
            if a in self.code_data:
                if a in self.fix_by_src:
                    fx, tgt = self.fix_by_src[a]
                    s = self.symbolize(tgt) or f"0x{tgt:x}"
                else:
                    s = f"0x{self.le.read_u32(a):x}"
                out.append(f"    dd {s:<41} ; {a:06x}")
                a += 4
                continue
            # unexplored bytes up to the next known item
            nxt = a + 1
            while nxt < end and nxt not in self.owner and nxt not in self.code_data and nxt not in self.routines and nxt not in self.vars:
                nxt += 1
            chunk = bytes(raw[a - obj.base:nxt - obj.base])
            out.extend(self.data_bytes_compact(a, chunk, '(unexplored)'))
            a = nxt
        return out

    def data_lines(self, obj):
        out = []
        base = obj.base
        end = base + obj.vsize
        # initialized size: all pages present in the file
        init_end = base + min(obj.vsize, obj.num_pages * self.le.hdr('page_size'))
        # last non-zero byte to allow compressing the zero tail
        stops = sorted(set([a for a in self.vars if obj.contains(a)] +
                           [a for a in self.fix_srcs if obj.contains(a)] + [end]))
        a = base
        idx = 0
        out.append(f"\n; {'=' * 100}\n; object {obj.index} ({obj.kind()}), base 0x{base:x}, size 0x{obj.vsize:x}, "
                   f"initialized 0x{init_end - base:x} bytes\n; {'=' * 100}")
        out.append(f"section {self.seg_name(obj)} vstart=0x{base:x}")
        while a < end:
            v = self.vars.get(a)
            if v is not None:
                xr = ', '.join(self.routines[x].name for x in sorted(v.xrefs)[:6] if x in self.routines)
                more = f" +{len(v.xrefs) - 6}" if len(v.xrefs) > 6 else ''
                out.append(f"{v.name}:" + (f"{' ' * max(1, 48 - len(v.name))}; xref {xr}{more}" if xr else ''))
            if a in self.fix_by_src:
                fx, tgt = self.fix_by_src[a]
                s = self.symbolize(tgt) or (f"0x{tgt:x}" if tgt is not None else '?')
                out.append(f"    dd {s:<41} ; {a:06x}")
                a += 4
                continue
            if v is not None and v.kind == 'string':
                raw = obj.data[a - base:a - base + v.size]
                out.append(f"    db {self.asm_string(raw[:-1])}, 0 ; {a:06x}")
                a += v.size
                continue
            while idx < len(stops) and stops[idx] <= a:
                idx += 1
            nxt = stops[idx] if idx < len(stops) else end
            chunk = bytes(obj.data[a - base:nxt - base])
            if a >= init_end:
                out.append(f"    resb {nxt - a:<39} ; {a:06x} (bss)")
            else:
                out.extend(self.data_bytes_compact(a, chunk))
            a = nxt
        return out

    def data_bytes_compact(self, addr, chunk, note=''):
        out = []
        if note and chunk and self.is_padding(chunk):
            note = '(padding)'
        pos = 0
        n = len(chunk)
        while pos < n:
            # zero runs
            z = pos
            while z < n and chunk[z] == 0:
                z += 1
            if z - pos >= 16 or (z - pos >= 2 and z == n and note):
                out.append(f"    times {z - pos} db 0 ; {addr + pos:06x}" + (f" {note}" if note else ''))
                pos = z
                continue
            # printable string runs terminated with 0
            s = pos
            while s < n and (0x20 <= chunk[s] < 0x7f):
                s += 1
            if s - pos >= 4 and s < n and chunk[s] == 0:
                out.append(f"    db {self.asm_string(chunk[pos:s])}, 0 ; {addr + pos:06x}")
                pos = s + 1
                continue
            line = chunk[pos:pos + 16]
            # stop the line at a zero run
            zz = line.find(b'\0' * 16)
            if zz > 0:
                line = line[:zz]
            asc = ''.join(chr(b) if 0x20 <= b < 0x7f else '.' for b in line)
            vals = ', '.join(f"0x{b:02x}" for b in line)
            out.append(f"    db {vals} ; {addr + pos:06x} |{asc}|" + (f" {note}" if note else ''))
            pos += len(line)
        return out

    @staticmethod
    def asm_string(raw):
        parts = []
        cur = ''
        for b in raw:
            if 0x20 <= b < 0x7f and b != 0x27:
                cur += chr(b)
            else:
                if cur:
                    parts.append(f"'{cur}'")
                    cur = ''
                parts.append(f"0x{b:02x}")
        if cur:
            parts.append(f"'{cur}'")
        return ', '.join(parts) if parts else "''"

    def listing_header(self):
        le = self.le
        lines = [f"; Disassembly of {os.path.basename(le.path)} generated by ledisasm v{VERSION}",
                 f"; {le.format} executable, LE header at file offset 0x{le.le_offset:x}, stub at 0x{le.stub_offset:x}",
                 f"; entrypoint 0x{le.entry_point():x}, initial stack 0x{le.initial_stack():x}",
                 "; objects:"]
        for o in le.objects:
            lines.append(f";   {o}")
        lines.append(f"; {len(self.routines)} routines, {len(self.insns)} instructions, {len(self.vars)} variables")
        lines.append("; syntax: Intel (capstone), addresses are linear; memory operands referencing relocated")
        lines.append("; addresses are replaced with symbol names. Comments: address and instruction bytes.")
        return lines

    def write_listing(self, path, split=0):
        '''Write the full listing, optionally split into files of roughly `split` bytes of code each'''
        files = []
        header = self.listing_header()
        code_parts = []
        for obj in self.code_objs:
            starts = sorted(a for a in self.routines if obj.contains(a))
            bounds = [obj.base]
            if split:
                last = obj.base
                for s in starts:
                    if s - last >= split:
                        bounds.append(s)
                        last = s
            bounds.append(obj.base + obj.vsize)
            for i in range(len(bounds) - 1):
                code_parts.append((obj, bounds[i], bounds[i + 1]))
        if not split:
            with open(path, 'w') as f:
                f.write('\n'.join(header) + '\n')
                for obj, s, e in code_parts:
                    if s == obj.base:
                        f.write(f"\n; {'=' * 100}\n; object {obj.index} ({obj.kind()}), base 0x{obj.base:x}, size 0x{obj.vsize:x}\n; {'=' * 100}\n")
                        f.write(f"section {self.seg_name(obj)} vstart=0x{obj.base:x}\n")
                    f.write('\n'.join(self.code_lines(obj, s, e)) + '\n')
                for obj in self.data_objs:
                    f.write('\n'.join(self.data_lines(obj)) + '\n')
            return [path]
        root, ext = os.path.splitext(path)
        for obj, s, e in code_parts:
            p = f"{root}_{s:06x}{ext}"
            with open(p, 'w') as f:
                f.write('\n'.join(header) + '\n')
                f.write(f"; this file: {self.seg_name(obj)} 0x{s:x}-0x{e - 1:x}\n")
                f.write(f"section {self.seg_name(obj)} vstart=0x{s:x}\n")
                f.write('\n'.join(self.code_lines(obj, s, e)) + '\n')
            files.append(p)
        for obj in self.data_objs:
            p = f"{root}_{self.seg_name(obj)}{ext}"
            with open(p, 'w') as f:
                f.write('\n'.join(header) + '\n')
                f.write('\n'.join(self.data_lines(obj)) + '\n')
            files.append(p)
        return files

    # --- other outputs ------------------------------------------------------------------------
    def to_json(self):
        le = self.le
        routines = []
        for a in sorted(self.routines):
            r = self.routines[a]
            routines.append({
                'name': r.name, 'addr': a, 'size': r.size,
                'blocks': [[s, e] for s, e in r.blocks],
                'instructions': len(r.insns),
                'callers': [self.routines[c].name for c in sorted(r.callers)],
                'callees': [self.routines[c].name for c in sorted(r.callees)],
                'strings': [t for _, t in r.strings],
                'vars': [self.vars[v].name for v in sorted(r.vars)],
                'interrupts': [[i, s] for i, s in r.ints],
                'ports': sorted(r.ports),
                'tags': self.routine_tags(r),
                'annotations': self.map_annotations.get(a, []),
                'comments': self.map_comments.get(a, []),
                'reasons': sorted(r.reasons),
                'convention': r.convention,
                'noreturn': r.noreturn,
            })
        variables = []
        for a in sorted(self.vars):
            v = self.vars[a]
            d = {'name': v.name, 'addr': a, 'size': v.size, 'kind': v.kind,
                 'xrefs': [self.routines[x].name for x in sorted(v.xrefs) if x in self.routines]}
            if v.text is not None:
                d['text'] = v.text
            variables.append(d)
        return {
            'file': os.path.basename(le.path), 'tool': f"ledisasm {VERSION}", 'format': le.format,
            'entry': le.entry_point(), 'stack': le.initial_stack(),
            'objects': [{'index': o.index, 'base': o.base, 'size': o.vsize, 'flags': o.flags, 'kind': o.kind(),
                         'name': self.seg_name(o)} for o in le.objects],
            'routines': routines, 'variables': variables,
        }

    def write_strings(self, path):
        with open(path, 'w') as f:
            f.write("# address  length  referenced-by  text\n")
            for a in sorted(self.vars):
                v = self.vars[a]
                if v.kind != 'string':
                    continue
                refs = ','.join(self.routines[x].name for x in sorted(v.xrefs) if x in self.routines) or '-'
                f.write(f"{a:08x} {v.size - 1:5d}  {refs:<40} {json.dumps(v.text)}\n")

    def write_symbols(self, path):
        '''Tab separated symbol list for importing into other tools (see tools/ghidra/LEDecompile.java):
        address, kind (func/data), name, size, calling convention or data kind'''
        with open(path, 'w') as f:
            for a in sorted(self.routines):
                r = self.routines[a]
                f.write(f"{a:08x}\tfunc\t{r.name}\t{r.extent[1] - r.extent[0]}\t{r.convention}" + ("\tnoreturn" if r.noreturn else '') + "\n")
            for a in sorted(self.vars):
                v = self.vars[a]
                f.write(f"{a:08x}\tdata\t{v.name}\t{v.size}\t{v.kind or ''}\n")

    def write_elf(self, path):
        '''Write the relocated image as a static ELF32 i386 executable with a symbol table, so that
        standard tools (Ghidra, IDA, radare2, objdump, gdb) can load it with all names applied.'''
        objs = self.le.objects
        psize = self.le.hdr('page_size')
        shstr = bytearray(b'\0')
        def shname(n):
            off = len(shstr)
            shstr.extend(n.encode() + b'\0')
            return off
        strtab = bytearray(b'\0')
        def strname(n):
            off = len(strtab)
            strtab.extend(n.encode() + b'\0')
            return off
        sections = []  # (name, type, flags, addr, data or None, size)
        for o in objs:
            init = min(o.vsize, o.num_pages * psize)
            if o.is_code():
                sections.append((f".text{o.index}" if len(self.code_objs) > 1 else '.text', 1, 0x6, o.base, bytes(o.data[:o.vsize]), o.vsize, o))
            else:
                # trim trailing zeros of the initialized part into bss
                data = bytes(o.data[:init])
                sections.append((f".data{o.index}" if len(self.data_objs) > 1 else '.data', 1, 0x3, o.base, data, len(data), o))
                if o.vsize > init:
                    sections.append((f".bss{o.index}" if len(self.data_objs) > 1 else '.bss', 8, 0x3, o.base + init, None, o.vsize - init, o))
        # layout: ehdr, phdrs, section data, symtab, strtab, shstrtab, shdrs
        nph = len(objs)
        off = 52 + 32 * nph
        blobs = []
        placed = []
        for sec in sections:
            name, stype, flags, addr, data, size, o = sec
            # keep file offset congruent to address modulo page size for loaders
            align = 0x1000
            pad = (addr - off) % align
            off += pad
            placed.append((sec, off if data is not None else off))
            if data is not None:
                blobs.append((off, data))
                off += len(data)
        # symbols
        syms = [struct.pack('<IIIBBH', 0, 0, 0, 0, 0, 0)]
        secidx = {}
        for i, (sec, _) in enumerate(placed):
            secidx[i] = i + 1
        def section_of(addr):
            for i, (sec, _) in enumerate(placed):
                name, stype, flags, saddr, data, size, o = sec
                if saddr <= addr < saddr + size:
                    return i + 1
            return 0xfff1  # SHN_ABS
        for a in sorted(self.routines):
            r = self.routines[a]
            size = r.extent[1] - r.extent[0]
            syms.append(struct.pack('<IIIBBH', strname(r.name), a, size, (1 << 4) | 2, 0, section_of(a)))
        for a in sorted(self.vars):
            v = self.vars[a]
            syms.append(struct.pack('<IIIBBH', strname(v.name), a, v.size, (1 << 4) | 1, 0, section_of(a)))
        symtab = b''.join(syms)
        off = (off + 3) & ~3
        symtab_off = off
        off += len(symtab)
        strtab_off = off
        off += len(strtab)
        # section header names
        names = [shname(sec[0]) for sec, _ in placed]
        n_symtab = shname('.symtab')
        n_strtab = shname('.strtab')
        n_shstr = shname('.shstrtab')
        shstr_off = off
        off += len(shstr)
        off = (off + 3) & ~3
        shoff = off
        nsec = 1 + len(placed) + 3
        entry = self.le.entry_point()
        ehdr = struct.pack('<16sHHIIIIIHHHHHH', b'\x7fELF\x01\x01\x01' + b'\0' * 9, 2, 3, 1, entry, 52, shoff, 0,
                           52, 32, nph, 40, nsec, nsec - 1)
        phdrs = b''
        for o in objs:
            secs = [(s, p) for s, p in placed if s[6] is o]
            first = secs[0]
            fsize = sum(len(s[4]) for s, _ in secs if s[4] is not None)
            flags = (4 if o.flags & 1 else 0) | (2 if o.flags & 2 else 0) | (1 if o.flags & 4 else 0)
            phdrs += struct.pack('<IIIIIIII', 1, first[1], o.base, o.base, fsize, o.vsize, flags, 0x1000)
        shdrs = struct.pack('<10I', *([0] * 10))
        for i, (sec, foff) in enumerate(placed):
            name, stype, flags, addr, data, size, o = sec
            shdrs += struct.pack('<10I', names[i], stype, flags, addr, foff, size, 0, 0, 16 if flags & 4 else 4, 0)
        nloc = 1
        shdrs += struct.pack('<10I', n_symtab, 2, 0, 0, symtab_off, len(symtab), len(placed) + 2, nloc, 4, 16)
        shdrs += struct.pack('<10I', n_strtab, 3, 0, 0, strtab_off, len(strtab), 0, 0, 1, 0)
        shdrs += struct.pack('<10I', n_shstr, 3, 0, 0, shstr_off, len(shstr), 0, 0, 1, 0)
        out = bytearray(shoff + len(shdrs))
        out[0:52] = ehdr
        out[52:52 + len(phdrs)] = phdrs
        for o_, data in blobs:
            out[o_:o_ + len(data)] = data
        out[symtab_off:symtab_off + len(symtab)] = symtab
        out[strtab_off:strtab_off + len(strtab)] = strtab
        out[shstr_off:shstr_off + len(shstr)] = shstr
        out[shoff:shoff + len(shdrs)] = shdrs
        with open(path, 'wb') as f:
            f.write(out)

    def summary(self):
        code_size = sum(o.vsize for o in self.code_objs)
        insn_bytes = sum(i.size for i in self.insns.values())
        cdata = sum(self.code_data.values())
        reasons = defaultdict(int)
        for r in self.routines.values():
            for x in r.reasons:
                reasons[x] += 1
        gaps = self.gaps()
        gap_bytes = sum(e - s for s, e in gaps)
        pad = 0
        for s, e in gaps:
            o = self.obj_of(s)
            if self.is_padding(o.data[s - o.base:e - o.base]):
                pad += e - s
        lines = [
            "--- Summary",
            f"Routines: {len(self.routines)} ({', '.join(f'{k}: {v}' for k, v in sorted(reasons.items()))})",
            f"Noreturn routines: {len(self.noreturn)}",
            f"Instructions: {len(self.insns)}, {insn_bytes} bytes ({100.0 * insn_bytes / code_size:.1f}% of code objects)",
            f"Embedded data in code (jump tables): {cdata} bytes, {len(self.jump_tables)} switch jumps",
            f"Unexplored code object bytes: {gap_bytes} in {len(gaps)} gaps, of which {pad} bytes are padding",
            f"Variables: {len(self.vars)}, strings: {sum(1 for v in self.vars.values() if v.kind == 'string')}",
            f"Decode failures: {len(self.bad)}",
        ]
        return '\n'.join(lines)

def main():
    ap = argparse.ArgumentParser(description='Disassemble a 32-bit LE/LX (DOS/4GW) executable, find routines and variables')
    ap.add_argument('exe')
    ap.add_argument('--map', help='editable map file; read (if it exists) for names/annotations, then updated')
    ap.add_argument('--readonly-map', action='store_true', help='do not update the map file passed with --map')
    ap.add_argument('--asm', help='write assembly listing to this file')
    ap.add_argument('--split', type=lambda x: int(x, 0), default=0,
                    help='split the code listing into files covering roughly this many bytes each')
    ap.add_argument('--json', help='write routines/variables/call graph as JSON')
    ap.add_argument('--elf', help='write relocated image with symbols as an ELF32 file')
    ap.add_argument('--strings', help='write string table with references')
    ap.add_argument('--symbols', help='write tab separated symbol list (address, kind, name, size, convention)')
    ap.add_argument('--seed', action='append', default=[], type=lambda x: int(x, 16),
                    help='additional routine entrypoint (hex linear address), can be repeated')
    ap.add_argument('--verbose', action='store_true')
    args = ap.parse_args()
    try:
        le = LEExecutable(args.exe)
    except (LEError, OSError) as e:
        print(f"ERROR: {e}")
        sys.exit(1)
    an = Analyzer(le, args.verbose)
    seeds = list(args.seed)
    if args.map and os.path.exists(args.map):
        seeds += an.load_map(args.map)
        print(f"Loaded map {args.map}: {len(an.names)} named routines, {len(an.var_names)} named variables")
    print(f"Analyzing {args.exe}: entrypoint 0x{le.entry_point():x}, {len(le.fixups)} fixups")
    an.run(seeds)
    an.build_symbols()
    print(an.summary())
    if args.map and not args.readonly_map:
        an.save_map(args.map)
        print(f"Saved map to {args.map}")
    if args.asm:
        files = an.write_listing(args.asm, args.split)
        print(f"Wrote listing to {len(files)} file(s): {', '.join(files[:3])}{' ...' if len(files) > 3 else ''}")
    if args.json:
        with open(args.json, 'w') as f:
            json.dump(an.to_json(), f, indent=1)
        print(f"Wrote JSON to {args.json}")
    if args.strings:
        an.write_strings(args.strings)
        print(f"Wrote strings to {args.strings}")
    if args.symbols:
        an.write_symbols(args.symbols)
        print(f"Wrote symbols to {args.symbols}")
    if args.elf:
        an.write_elf(args.elf)
        print(f"Wrote ELF image to {args.elf}")

if __name__ == '__main__':
    main()
