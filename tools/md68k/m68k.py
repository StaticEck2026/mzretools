"""
Motorola 68000 instruction decoder producing SNASM68K/asm68k compatible text.

The decoder is deliberately strict: anything that is not a legal 68000
instruction (illegal effective address for the instruction, 68020-only
extension words, reserved bits set, ...) is rejected, so that it can be used
to tell code from data.  Every operand is printed with an explicit size
(`bra.s`/`bra.w`, `(addr).w`/`(addr).l`, `0(a0)`, `addi` instead of `add`...)
so that a non optimising assembler reproduces the original encoding exactly.
"""

from dataclasses import dataclass, field
from typing import List, Optional

RAM_BASE = 0xFF0000

COND = ['t', 'f', 'hi', 'ls', 'cc', 'cs', 'ne', 'eq', 'vc', 'vs', 'pl', 'mi', 'ge', 'lt', 'gt', 'le']
SIZES = {0: 'b', 1: 'w', 2: 'l'}


class Invalid(Exception):
    pass


@dataclass
class Operand:
    text: str
    # absolute address referenced by this operand (abs.w/abs.l/pc-relative), or None
    addr: Optional[int] = None
    kind: str = ''        # 'absw', 'absl', 'pcrel', 'pcidx', 'imm', 'branch', ''
    imm: Optional[int] = None
    imm_size: int = 0     # bytes of the immediate
    # offset of the extension word(s) holding the address inside the instruction
    ext_off: int = 0


@dataclass
class Instruction:
    addr: int
    size: int
    mnemonic: str
    operands: List[Operand] = field(default_factory=list)
    words: List[int] = field(default_factory=list)
    # flow
    is_branch: bool = False       # conditional/unconditional branch or dbcc
    is_call: bool = False         # bsr/jsr
    is_terminal: bool = False     # rts, rte, rtr, jmp, bra, illegal...
    target: Optional[int] = None  # static branch/jump target
    indirect_jump: bool = False   # jmp/jsr through register / pc index

    @property
    def text(self):
        if self.operands:
            return '%s\t%s' % (self.mnemonic, ','.join(o.text for o in self.operands))
        return self.mnemonic

    def refs(self):
        return [o for o in self.operands if o.addr is not None]


def hexs(v, digits=0):
    """Hex formatting in asm68k style ($1234) with sign."""
    if v < 0:
        return '-$%X' % (-v)
    if digits:
        return '$%0*X' % (digits, v)
    return '$%X' % v


def sext8(v):
    v &= 0xFF
    return v - 0x100 if v & 0x80 else v


def sext16(v):
    v &= 0xFFFF
    return v - 0x10000 if v & 0x8000 else v


def reg_list(mask, reverse=False):
    if mask == 0:
        raise Invalid('empty movem list')
    regs = []
    for i in range(16):
        bit = (15 - i) if reverse else i
        if mask & (1 << bit):
            regs.append(i)
    # group into ranges, separately for d and a
    parts = []
    i = 0
    while i < len(regs):
        j = i
        while j + 1 < len(regs) and regs[j + 1] == regs[j] + 1 and (regs[j + 1] // 8) == (regs[i] // 8):
            j += 1
        def rn(r):
            return 'd%d' % r if r < 8 else 'a%d' % (r - 8)
        if j == i:
            parts.append(rn(regs[i]))
        elif j == i + 1:
            parts.append(rn(regs[i]))
            parts.append(rn(regs[j]))
        else:
            parts.append('%s-%s' % (rn(regs[i]), rn(regs[j])))
        i = j + 1
    return '/'.join(parts)


class Decoder:
    def __init__(self, rom: bytes, base: int = 0):
        self.rom = rom
        self.base = base

    def word(self, addr):
        off = addr - self.base
        if off < 0 or off + 2 > len(self.rom):
            raise Invalid('out of range')
        return (self.rom[off] << 8) | self.rom[off + 1]

    def long(self, addr):
        return (self.word(addr) << 16) | self.word(addr + 2)

    # ------------------------------------------------------------------
    def decode(self, addr) -> Instruction:
        if addr & 1:
            raise Invalid('odd address')
        op = self.word(addr)
        self.pc = addr + 2          # points to next extension word
        self.start = addr
        ins = Instruction(addr, 0, '?', words=[op])
        self.ins = ins
        group = op >> 12
        handler = getattr(self, 'grp_%x' % group)
        handler(op, ins)
        ins.size = self.pc - addr
        ins.words = [self.word(addr + i) for i in range(0, ins.size, 2)]
        return ins

    # ------------------------------------------------------------------
    # effective address decoding
    def fetch_w(self):
        v = self.word(self.pc)
        self.pc += 2
        return v

    def fetch_l(self):
        v = self.long(self.pc)
        self.pc += 4
        return v

    def ea(self, mode, reg, size, allowed='all') -> Operand:
        """
        size: 1,2,4 (bytes) for immediate operands.
        allowed: string of allowed categories:
           'd' data register, 'a' address register, 'm' memory (modes 2..6, abs),
           'i' immediate, 'p' pc-relative, 'post' (an)+, 'pre' -(an)
        """
        def chk(c):
            if allowed != 'all' and c not in allowed:
                raise Invalid('ea mode not allowed')
        if mode == 0:
            chk('d')
            return Operand('d%d' % reg)
        if mode == 1:
            chk('a')
            return Operand(an(reg))
        if mode == 2:
            chk('m')
            return Operand('(%s)' % an(reg))
        if mode == 3:
            chk('+')
            return Operand('(%s)+' % an(reg))
        if mode == 4:
            chk('-')
            return Operand('-(%s)' % an(reg))
        if mode == 5:
            chk('m')
            d = sext16(self.fetch_w())
            return Operand('%s(%s)' % (hexs(d), an(reg)))
        if mode == 6:
            chk('m')
            ext = self.fetch_w()
            if ext & 0x0700:            # full format / scale -> 68020
                raise Invalid('68020 extension word')
            d = sext8(ext)
            ireg = (ext >> 12) & 7
            isz = 'l' if ext & 0x800 else 'w'
            iname = ('a%d' % ireg) if ext & 0x8000 else ('d%d' % ireg)
            return Operand('%s(%s,%s.%s)' % (hexs(d), an(reg), iname, isz))
        if mode == 7:
            if reg == 0:
                chk('m')
                eo = self.pc - self.start
                a = sext16(self.fetch_w()) & 0xFFFFFFFF
                return Operand('(%s).w' % hexs(a), addr=a, kind='absw', ext_off=eo)
            if reg == 1:
                chk('m')
                eo = self.pc - self.start
                a = self.fetch_l()
                return Operand('(%s).l' % hexs(a), addr=a, kind='absl', ext_off=eo)
            if reg == 2:
                chk('p')
                eo = self.pc - self.start
                base = self.pc
                d = sext16(self.fetch_w())
                a = (base + d) & 0xFFFFFFFF
                return Operand('%s(pc)' % hexs(a), addr=a, kind='pcrel', ext_off=eo)
            if reg == 3:
                chk('p')
                eo = self.pc - self.start
                base = self.pc
                ext = self.fetch_w()
                if ext & 0x0700:
                    raise Invalid('68020 extension word')
                d = sext8(ext)
                ireg = (ext >> 12) & 7
                isz = 'l' if ext & 0x800 else 'w'
                iname = ('a%d' % ireg) if ext & 0x8000 else ('d%d' % ireg)
                a = (base + d) & 0xFFFFFFFF
                return Operand('%s(pc,%s.%s)' % (hexs(a), iname, isz), addr=a, kind='pcidx', ext_off=eo)
            if reg == 4:
                chk('i')
                eo = self.pc - self.start
                if size == 1:
                    w = self.fetch_w()
                    if w & 0xFF00:
                        raise Invalid('byte immediate with high byte set')
                    return Operand('#%s' % hexs(w & 0xFF), kind='imm', imm=w & 0xFF, imm_size=1, ext_off=eo)
                if size == 2:
                    w = self.fetch_w()
                    return Operand('#%s' % hexs(w), kind='imm', imm=w, imm_size=2, ext_off=eo)
                if size == 4:
                    l = self.fetch_l()
                    return Operand('#%s' % hexs(l), kind='imm', imm=l, imm_size=4, ext_off=eo)
                raise Invalid('bad immediate size')
        raise Invalid('bad ea')

    # ------------------------------------------------------------------
    def grp_0(self, op, ins):
        if op & 0x0100:
            # dynamic bit ops or movep
            mode = (op >> 3) & 7
            reg = op & 7
            dn = (op >> 9) & 7
            if mode == 1:
                # movep
                opmode = (op >> 6) & 7
                d = sext16(self.fetch_w())
                mem = '%s(%s)' % (hexs(d), an(reg))
                sz = 'w' if opmode in (4, 6) else 'l'
                ins.mnemonic = 'movep.%s' % sz
                if opmode in (4, 5):
                    ins.operands = [Operand(mem), Operand('d%d' % dn)]
                else:
                    ins.operands = [Operand('d%d' % dn), Operand(mem)]
                return
            bop = ['btst', 'bchg', 'bclr', 'bset'][(op >> 6) & 3]
            # BTST Dn,#<data> is the one bit instruction with an immediate destination
            allowed = 'dm+-pi' if bop == 'btst' else 'dm+-'
            dst = self.ea(mode, reg, 1, allowed)
            ins.mnemonic = bop
            ins.operands = [Operand('d%d' % dn), dst]
            return
        kind = (op >> 9) & 7
        sz = (op >> 6) & 3
        mode = (op >> 3) & 7
        reg = op & 7
        if kind == 4:
            # static bit ops
            bop = ['btst', 'bchg', 'bclr', 'bset'][sz]
            ext = self.fetch_w()
            if ext & 0xFF00:
                raise Invalid('bit number high byte')
            allowed = 'dm+-p' if bop == 'btst' else 'dm+-'
            if mode == 7 and reg == 4:
                raise Invalid('bit op on immediate')
            dst = self.ea(mode, reg, 1, allowed)
            ins.mnemonic = bop
            ins.operands = [Operand('#%d' % (ext & 0xFF)), dst]
            return
        name = ['ori', 'andi', 'subi', 'addi', None, 'eori', 'cmpi', None][kind]
        if name is None or sz == 3:
            raise Invalid('group 0')
        if mode == 7 and reg == 4:
            # to ccr / sr
            if name in ('ori', 'andi', 'eori'):
                if sz == 0:
                    imm = self.fetch_w()
                    if imm & 0xFF00:
                        raise Invalid('ccr imm')
                    ins.mnemonic = name
                    ins.operands = [Operand('#%s' % hexs(imm), kind='imm', imm=imm, imm_size=1, ext_off=2), Operand('ccr')]
                    return
                if sz == 1:
                    imm = self.fetch_w()
                    ins.mnemonic = name
                    ins.operands = [Operand('#%s' % hexs(imm), kind='imm', imm=imm, imm_size=2, ext_off=2), Operand('sr')]
                    return
            raise Invalid('imm destination')
        isz = [1, 2, 4][sz]
        src = self.ea(7, 4, isz, 'i')
        if name == 'cmpi':
            dst = self.ea(mode, reg, isz, 'dm+-')   # 68000: no pc-rel destination
        else:
            dst = self.ea(mode, reg, isz, 'dm+-')
        ins.mnemonic = '%s.%s' % (name, SIZES[sz])
        ins.operands = [src, dst]

    def _move(self, op, ins, sz, isz):
        smode = (op >> 3) & 7
        sreg = op & 7
        dmode = (op >> 6) & 7
        dreg = (op >> 9) & 7
        if sz == 'b' and smode == 1:
            raise Invalid('move.b an')
        src = self.ea(smode, sreg, isz, 'all')
        if dmode == 1:
            if sz == 'b':
                raise Invalid('movea.b')
            dst = self.ea(dmode, dreg, isz, 'a')
            ins.mnemonic = 'movea.%s' % sz
        else:
            dst = self.ea(dmode, dreg, isz, 'dm+-')
            ins.mnemonic = 'move.%s' % sz
        ins.operands = [src, dst]

    def grp_1(self, op, ins):
        self._move(op, ins, 'b', 1)

    def grp_2(self, op, ins):
        self._move(op, ins, 'l', 4)

    def grp_3(self, op, ins):
        self._move(op, ins, 'w', 2)

    def grp_4(self, op, ins):
        mode = (op >> 3) & 7
        reg = op & 7
        if op & 0x0100:
            if (op >> 6) & 7 == 7:
                # lea
                an_ = (op >> 9) & 7
                src = self.ea(mode, reg, 0, 'mp')
                if mode in (3, 4):
                    raise Invalid('lea (an)+')
                ins.mnemonic = 'lea'
                ins.operands = [src, Operand(an(an_))]
                return
            if (op >> 6) & 7 in (4, 6):
                # chk (only .w on 68000: opmode 110)
                if (op >> 6) & 7 != 6:
                    raise Invalid('chk.l 68020')
                dn = (op >> 9) & 7
                src = self.ea(mode, reg, 2, 'dm+-ip')
                ins.mnemonic = 'chk.w'
                ins.operands = [src, Operand('d%d' % dn)]
                return
            raise Invalid('group 4 bit 8')
        sub = (op >> 9) & 7
        sz = (op >> 6) & 3
        if sub == 0:
            if sz == 3:
                dst = self.ea(mode, reg, 2, 'dm+-')
                ins.mnemonic = 'move.w'
                ins.operands = [Operand('sr'), dst]
                return
            dst = self.ea(mode, reg, 0, 'dm+-')
            ins.mnemonic = 'negx.%s' % SIZES[sz]
            ins.operands = [dst]
            return
        if sub == 1:
            if sz == 3:
                raise Invalid('move from ccr 68010')
            dst = self.ea(mode, reg, 0, 'dm+-')
            ins.mnemonic = 'clr.%s' % SIZES[sz]
            ins.operands = [dst]
            return
        if sub == 2:
            if sz == 3:
                src = self.ea(mode, reg, 2, 'dm+-ip')
                ins.mnemonic = 'move.w'
                ins.operands = [src, Operand('ccr')]
                return
            dst = self.ea(mode, reg, 0, 'dm+-')
            ins.mnemonic = 'neg.%s' % SIZES[sz]
            ins.operands = [dst]
            return
        if sub == 3:
            if sz == 3:
                src = self.ea(mode, reg, 2, 'dm+-ip')
                ins.mnemonic = 'move.w'
                ins.operands = [src, Operand('sr')]
                return
            dst = self.ea(mode, reg, 0, 'dm+-')
            ins.mnemonic = 'not.%s' % SIZES[sz]
            ins.operands = [dst]
            return
        if sub == 4:
            if sz == 0:
                dst = self.ea(mode, reg, 0, 'dm+-')
                ins.mnemonic = 'nbcd'
                ins.operands = [dst]
                return
            if sz == 1:
                if mode == 0:
                    ins.mnemonic = 'swap'
                    ins.operands = [Operand('d%d' % reg)]
                    return
                if mode in (3, 4):
                    raise Invalid('pea (an)+')
                src = self.ea(mode, reg, 0, 'mp')
                ins.mnemonic = 'pea'
                ins.operands = [src]
                return
            # ext / movem reg->mem
            if mode == 0:
                ins.mnemonic = 'ext.%s' % ('w' if sz == 2 else 'l')
                ins.operands = [Operand('d%d' % reg)]
                return
            mask = self.fetch_w()
            if mode == 3:
                raise Invalid('movem to (an)+')
            dst = self.ea(mode, reg, 0, 'm-')
            if mode == 4:
                lst = reg_list(mask, reverse=True)
            else:
                lst = reg_list(mask)
            ins.mnemonic = 'movem.%s' % ('w' if sz == 2 else 'l')
            ins.operands = [Operand(lst), dst]
            return
        if sub == 5:
            if sz == 3:
                if mode == 7 and reg == 4:
                    ins.mnemonic = 'illegal'
                    ins.is_terminal = True
                    return
                dst = self.ea(mode, reg, 0, 'dm+-')
                ins.mnemonic = 'tas'
                ins.operands = [dst]
                return
            # tst: 68000 only data alterable
            dst = self.ea(mode, reg, 0, 'dm+-')
            ins.mnemonic = 'tst.%s' % SIZES[sz]
            ins.operands = [dst]
            return
        if sub == 6:
            # movem mem->reg
            if sz < 2:
                raise Invalid('group 4 sub 6')
            mask = self.fetch_w()
            if mode == 4:
                raise Invalid('movem from -(an)')
            src = self.ea(mode, reg, 0, 'm+p')
            ins.mnemonic = 'movem.%s' % ('w' if sz == 2 else 'l')
            ins.operands = [src, Operand(reg_list(mask))]
            return
        # sub == 7
        if sz == 1:
            # misc
            if mode in (0, 1):
                ins.mnemonic = 'trap'
                ins.operands = [Operand('#%d' % (op & 15))]
                return
            if mode == 2:
                d = sext16(self.fetch_w())
                ins.mnemonic = 'link'
                ins.operands = [Operand(an(reg)), Operand('#%s' % hexs(d))]
                return
            if mode == 3:
                ins.mnemonic = 'unlk'
                ins.operands = [Operand(an(reg))]
                return
            if mode == 4:
                ins.mnemonic = 'move.l'
                ins.operands = [Operand(an(reg)), Operand('usp')]
                return
            if mode == 5:
                ins.mnemonic = 'move.l'
                ins.operands = [Operand('usp'), Operand(an(reg))]
                return
            if mode == 6:
                if reg == 0:
                    ins.mnemonic = 'reset'
                    return
                if reg == 1:
                    ins.mnemonic = 'nop'
                    return
                if reg == 2:
                    imm = self.fetch_w()
                    ins.mnemonic = 'stop'
                    ins.operands = [Operand('#%s' % hexs(imm))]
                    return
                if reg == 3:
                    ins.mnemonic = 'rte'
                    ins.is_terminal = True
                    return
                if reg == 5:
                    ins.mnemonic = 'rts'
                    ins.is_terminal = True
                    return
                if reg == 6:
                    ins.mnemonic = 'trapv'
                    return
                if reg == 7:
                    ins.mnemonic = 'rtr'
                    ins.is_terminal = True
                    return
            raise Invalid('group 4 misc')
        if sz in (2, 3):
            if mode in (0, 1, 3, 4):
                raise Invalid('jmp/jsr mode')
            src = self.ea(mode, reg, 0, 'mp')
            ins.mnemonic = 'jsr' if sz == 2 else 'jmp'
            ins.operands = [src]
            if sz == 2:
                ins.is_call = True
            else:
                ins.is_terminal = True
            if src.kind in ('absw', 'absl', 'pcrel'):
                ins.target = src.addr
            else:
                ins.indirect_jump = True
            return
        raise Invalid('group 4')

    def grp_5(self, op, ins):
        mode = (op >> 3) & 7
        reg = op & 7
        sz = (op >> 6) & 3
        if sz == 3:
            cond = (op >> 8) & 15
            if mode == 1:
                d = sext16(self.fetch_w())
                target = (self.start + 2 + d) & 0xFFFFFFFF
                cname = COND[cond]
                if cname == 'f':
                    cname = 'ra'
                ins.mnemonic = 'db%s' % cname
                ins.operands = [Operand('d%d' % reg), Operand(hexs(target), addr=target, kind='branch', ext_off=2)]
                ins.is_branch = True
                ins.target = target
                return
            dst = self.ea(mode, reg, 0, 'dm+-')
            ins.mnemonic = 's%s' % COND[cond]
            ins.operands = [dst]
            return
        data = (op >> 9) & 7
        if data == 0:
            data = 8
        if mode == 1 and sz == 0:
            raise Invalid('addq.b an')
        dst = self.ea(mode, reg, 0, 'dam+-')
        ins.mnemonic = '%s.%s' % ('subq' if op & 0x100 else 'addq', SIZES[sz])
        ins.operands = [Operand('#%d' % data), dst]

    def grp_6(self, op, ins):
        cond = (op >> 8) & 15
        d8 = op & 0xFF
        if d8 == 0:
            d = sext16(self.fetch_w())
            suffix = 'w'
            eo = 2
        elif d8 == 0xFF:
            raise Invalid('bcc.l 68020')
        else:
            d = sext8(d8)
            suffix = 's'
            eo = 0
        target = (self.start + 2 + d) & 0xFFFFFFFF
        if cond == 0:
            name = 'bra'
            ins.is_terminal = True
        elif cond == 1:
            name = 'bsr'
            ins.is_call = True
        else:
            name = 'b%s' % COND[cond]
        ins.mnemonic = '%s.%s' % (name, suffix)
        ins.operands = [Operand(hexs(target), addr=target, kind='branch', ext_off=eo)]
        ins.is_branch = cond != 1
        ins.target = target

    def grp_7(self, op, ins):
        if op & 0x100:
            raise Invalid('moveq bit 8')
        v = sext8(op & 0xFF)
        ins.mnemonic = 'moveq'
        ins.operands = [Operand('#%s' % hexs(v), kind='imm', imm=v, imm_size=1), Operand('d%d' % ((op >> 9) & 7))]

    def _arith(self, op, ins, name):
        """or/and/sub/add/cmp/eor family (groups 8,9,B,C,D)."""
        mode = (op >> 3) & 7
        reg = op & 7
        dn = (op >> 9) & 7
        opmode = (op >> 6) & 7
        if opmode in (3, 7):
            # divu/divs, mulu/muls (for or/and), or suba/adda/cmpa
            if name in ('or', 'and'):
                if name == 'or':
                    m = 'divu.w' if opmode == 3 else 'divs.w'
                else:
                    m = 'mulu.w' if opmode == 3 else 'muls.w'
                src = self.ea(mode, reg, 2, 'dm+-ip')
                ins.mnemonic = m
                ins.operands = [src, Operand('d%d' % dn)]
                return
            sz = 'w' if opmode == 3 else 'l'
            isz = 2 if opmode == 3 else 4
            src = self.ea(mode, reg, isz, 'all')
            ins.mnemonic = '%sa.%s' % (name, sz)
            ins.operands = [src, Operand(an(dn))]
            return
        sz = opmode & 3
        isz = [1, 2, 4][sz]
        if opmode < 4:
            # <ea> op Dn -> Dn
            if sz == 0 and mode == 1:
                raise Invalid('byte op on an')
            if name == 'eor':
                raise Invalid('eor ea,dn')   # that's cmp
            if mode == 7 and reg == 4:
                # the "<ea>=#imm,Dn" encoding of ADD/SUB/AND/OR/CMP: assemblers
                # emit the ADDI/... form for the mnemonic, so this cannot be
                # written back faithfully.  Mark it so the caller can emit dc.w.
                src = self.ea(mode, reg, isz, 'i')
                ins.mnemonic = '%s.%s' % (name, SIZES[sz])
                ins.operands = [src, Operand('d%d' % dn)]
                ins.unassemblable = True
                return
            src = self.ea(mode, reg, isz, 'dm+-ip' if name in ('or', 'and') else 'all')
            ins.mnemonic = '%s.%s' % (name, SIZES[sz])
            ins.operands = [src, Operand('d%d' % dn)]
            return
        # Dn op <ea> -> <ea>   (opmode 4..6)
        if mode in (0, 1):
            # addx/subx/abcd/sbcd/exg/cmpm
            if name == 'add' or name == 'sub':
                rx = dn
                ry = reg
                m = 'addx' if name == 'add' else 'subx'
                if mode == 0:
                    ins.mnemonic = '%s.%s' % (m, SIZES[sz])
                    ins.operands = [Operand('d%d' % ry), Operand('d%d' % rx)]
                else:
                    ins.mnemonic = '%s.%s' % (m, SIZES[sz])
                    ins.operands = [Operand('-(%s)' % an(ry)), Operand('-(%s)' % an(rx))]
                return
            if name in ('or', 'and'):
                if sz == 0 and name == 'or':
                    ins.mnemonic = 'sbcd'
                elif sz == 0 and name == 'and':
                    ins.mnemonic = 'abcd'
                elif name == 'and':
                    # exg
                    if opmode == 5 and mode == 0:
                        ins.mnemonic = 'exg'
                        ins.operands = [Operand('d%d' % dn), Operand('d%d' % reg)]
                        return
                    if opmode == 5 and mode == 1:
                        ins.mnemonic = 'exg'
                        ins.operands = [Operand(an(dn)), Operand(an(reg))]
                        return
                    if opmode == 6 and mode == 1:
                        ins.mnemonic = 'exg'
                        ins.operands = [Operand('d%d' % dn), Operand(an(reg))]
                        return
                    raise Invalid('exg')
                else:
                    raise Invalid('or dn,dn')
                if mode == 0:
                    ins.operands = [Operand('d%d' % reg), Operand('d%d' % dn)]
                else:
                    ins.operands = [Operand('-(%s)' % an(reg)), Operand('-(%s)' % an(dn))]
                return
            if name == 'eor':
                if mode == 1:
                    # cmpm
                    ins.mnemonic = 'cmpm.%s' % SIZES[sz]
                    ins.operands = [Operand('(%s)+' % an(reg)), Operand('(%s)+' % an(dn))]
                    return
                dst = self.ea(mode, reg, 0, 'd')
                ins.mnemonic = 'eor.%s' % SIZES[sz]
                ins.operands = [Operand('d%d' % dn), dst]
                return
            raise Invalid('arith dn,dn')
        dst = self.ea(mode, reg, isz, 'm+-')
        ins.mnemonic = '%s.%s' % (name, SIZES[sz])
        ins.operands = [Operand('d%d' % dn), dst]

    def grp_8(self, op, ins):
        self._arith(op, ins, 'or')

    def grp_9(self, op, ins):
        self._arith(op, ins, 'sub')

    def grp_a(self, op, ins):
        raise Invalid('line A')

    def grp_b(self, op, ins):
        opmode = (op >> 6) & 7
        if opmode in (3, 7) or opmode < 4:
            self._arith(op, ins, 'cmp')
        else:
            self._arith(op, ins, 'eor')

    def grp_c(self, op, ins):
        self._arith(op, ins, 'and')

    def grp_d(self, op, ins):
        self._arith(op, ins, 'add')

    def grp_e(self, op, ins):
        mode = (op >> 3) & 7
        reg = op & 7
        sz = (op >> 6) & 3
        dr = 'l' if op & 0x100 else 'r'
        if sz == 3:
            # memory shift
            kind = (op >> 9) & 3
            if op & 0x800:
                raise Invalid('68020 bitfield')
            name = ['as', 'ls', 'rox', 'ro'][kind]
            dst = self.ea(mode, reg, 0, 'm+-')
            ins.mnemonic = '%s%s.w' % (name, dr)
            ins.operands = [dst]
            return
        kind = (op >> 3) & 3
        name = ['as', 'ls', 'rox', 'ro'][kind]
        cnt = (op >> 9) & 7
        ins.mnemonic = '%s%s.%s' % (name, dr, SIZES[sz])
        if op & 0x20:
            ins.operands = [Operand('d%d' % cnt), Operand('d%d' % reg)]
        else:
            if cnt == 0:
                cnt = 8
            ins.operands = [Operand('#%d' % cnt), Operand('d%d' % reg)]

    def grp_f(self, op, ins):
        raise Invalid('line F')


def an(n):
    return 'sp' if n == 7 else 'a%d' % n


Instruction.unassemblable = False
