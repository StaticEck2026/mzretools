#!/usr/bin/env python3
#
# Runs routines of an LE / LX executable in the Unicorn CPU emulator: the objects are mapped at their
# preferred base addresses with the internal fixups applied (a flat 32 bit model, as under DOS/4GW), so a
# self-contained routine - a decoder, a table builder, a piece of game logic - can be called with its
# register arguments and its results compared with a reimplementation. Interrupts and port I/O are not
# emulated; a routine that needs them stops with an error.
#
#   from leemu import LEEmu
#   emu = LEEmu('HOCKEY.EXE')
#   src = emu.alloc(packed); dst = emu.alloc(size)
#   n = emu.call(0x97740, eax=src, edx=dst, ebx=1)     # Watcom register convention: eax, edx, ebx, ecx
#   out = emu.read(dst, n)
#
#   leemu.py game.exe ADDRESS [--eax N] [--edx N] ... [--stack N ...]   calls a routine, prints eax
#
import argparse
import os
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from le import LEExecutable          # noqa: E402

try:
    from unicorn import Uc, UcError, UC_ARCH_X86, UC_MODE_32, UC_HOOK_INTR
    from unicorn.x86_const import (UC_X86_REG_EAX, UC_X86_REG_EBX, UC_X86_REG_ECX, UC_X86_REG_EDX,
                                   UC_X86_REG_ESI, UC_X86_REG_EDI, UC_X86_REG_EBP, UC_X86_REG_ESP,
                                   UC_X86_REG_EIP)
except ImportError:                    # pragma: no cover
    Uc = None

PAGE = 0x1000
STACK_TOP = 0x7ff00000
STACK_SIZE = 0x100000
HEAP_BASE = 0x40000000
HEAP_SIZE = 0x4000000
RETURN = 0x7fff0000                    # return address of a call: execution stops there

def _align(a, up=False):
    return (a + PAGE - 1) & ~(PAGE - 1) if up else a & ~(PAGE - 1)

class LEEmu:
    def __init__(self, exe):
        if Uc is None:
            raise RuntimeError('the unicorn module is needed (pip install unicorn)')
        self.le = LEExecutable(exe)
        self.le.apply_fixups()
        self.uc = Uc(UC_ARCH_X86, UC_MODE_32)
        for obj in self.le.objects:
            lo = _align(obj.base)
            hi = _align(obj.base + max(len(obj.data), obj.vsize), True)
            self.uc.mem_map(lo, hi - lo)
            self.uc.mem_write(obj.base, bytes(obj.data))
        self.uc.mem_map(STACK_TOP - STACK_SIZE, STACK_SIZE)
        self.uc.mem_map(HEAP_BASE, HEAP_SIZE)
        self.uc.mem_map(RETURN, PAGE)
        self.uc.mem_write(RETURN, b'\xf4')    # hlt
        self.heap = HEAP_BASE
        self.interrupt = None
        self.uc.hook_add(UC_HOOK_INTR, self._on_interrupt)

    def _on_interrupt(self, uc, intno, user):
        self.interrupt = intno
        uc.emu_stop()

    def alloc(self, data_or_size, align=16):
        '''Reserves heap memory, filled with the given bytes (or zeros); returns its address'''
        data = bytes(data_or_size) if not isinstance(data_or_size, int) else bytes(data_or_size)
        addr = self.heap
        self.heap = (self.heap + max(len(data), 1) + align - 1 + 64) & ~(align - 1)
        if self.heap > HEAP_BASE + HEAP_SIZE:
            raise MemoryError('emulator heap exhausted')
        if data:
            self.uc.mem_write(addr, data)
        return addr

    def free_all(self):
        self.heap = HEAP_BASE

    def read(self, addr, size):
        return bytes(self.uc.mem_read(addr, size))

    def write(self, addr, data):
        self.uc.mem_write(addr, bytes(data))

    def u32(self, addr):
        return struct.unpack('<I', self.read(addr, 4))[0]

    def call(self, addr, eax=0, edx=0, ebx=0, ecx=0, stack=(), esi=0, edi=0, ebp=0, max_insns=200_000_000):
        '''Calls the routine at addr and returns eax (the other registers: regs())'''
        sp = STACK_TOP - 0x100
        for v in reversed(list(stack)):
            sp -= 4
            self.uc.mem_write(sp, struct.pack('<I', v & 0xffffffff))
        sp -= 4
        self.uc.mem_write(sp, struct.pack('<I', RETURN))
        for reg, v in ((UC_X86_REG_EAX, eax), (UC_X86_REG_EDX, edx), (UC_X86_REG_EBX, ebx),
                       (UC_X86_REG_ECX, ecx), (UC_X86_REG_ESI, esi), (UC_X86_REG_EDI, edi),
                       (UC_X86_REG_EBP, ebp), (UC_X86_REG_ESP, sp)):
            self.uc.reg_write(reg, v & 0xffffffff)
        self.interrupt = None
        try:
            self.uc.emu_start(addr, RETURN, count=max_insns)
        except UcError as e:
            eip = self.uc.reg_read(UC_X86_REG_EIP)
            raise RuntimeError(f'emulation of 0x{addr:x} failed at 0x{eip:x}: {e}') from None
        eip = self.uc.reg_read(UC_X86_REG_EIP)
        if self.interrupt is not None:
            raise RuntimeError(f'0x{addr:x} raised interrupt 0x{self.interrupt:x} at 0x{eip:x}')
        if eip != RETURN:
            raise RuntimeError(f'0x{addr:x} did not return (stopped at 0x{eip:x})')
        return self.uc.reg_read(UC_X86_REG_EAX)

    def regs(self):
        return {n: self.uc.reg_read(r) for n, r in (('eax', UC_X86_REG_EAX), ('ebx', UC_X86_REG_EBX),
                                                     ('ecx', UC_X86_REG_ECX), ('edx', UC_X86_REG_EDX),
                                                     ('esi', UC_X86_REG_ESI), ('edi', UC_X86_REG_EDI))}

def main():
    ap = argparse.ArgumentParser(description='call a routine of an LE executable in an emulator')
    ap.add_argument('exe')
    ap.add_argument('address', type=lambda s: int(s, 16))
    for r in ('eax', 'edx', 'ebx', 'ecx'):
        ap.add_argument('--' + r, type=lambda s: int(s, 0), default=0)
    ap.add_argument('--stack', type=lambda s: int(s, 0), nargs='*', default=[])
    args = ap.parse_args()
    emu = LEEmu(args.exe)
    r = emu.call(args.address, args.eax, args.edx, args.ebx, args.ecx, args.stack)
    print(f'eax = 0x{r:x}', ' '.join(f'{k}=0x{v:x}' for k, v in emu.regs().items()))

if __name__ == '__main__':
    main()
