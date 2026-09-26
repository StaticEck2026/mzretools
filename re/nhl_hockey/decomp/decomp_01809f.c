// Decompiled by Ghidra from hockey.elf (via ledisasm ELF export)
// This is machine generated pseudo-C meant as a reference for porting, it does not compile as is.
#include "prototypes.h"

// ================================================================================================
// sub_1809f @ 0x1809f [__watcall]
// ================================================================================================

undefined8 __watcall sub_1809f(undefined4 param_1,undefined4 unaff_EDX)

{
  undefined4 uVar1;
  
  __CHK(0x20);
  dword_c65b0 = 2;
  if (dword_dc738 != 0) {
    dword_dc6b0 = allocmem(aSfPal1,0x300,0x20);
    getpalette(0,0x100,dword_dc6b0);
    dword_dc6ac = allocmem(aSfPal2,0x300,0x20);
    getpalette(0,0x100,dword_dc6ac);
    fade_palette(1,dword_dc6b0,0x10);
    freemem(dword_dc6b0);
    dword_dc6a8 = sub_235be(2);
    fade_palette(0,dword_dc6ac,0x10);
    freemem(dword_dc6ac);
    return CONCAT44(unaff_EDX,dword_dc6a8);
  }
  uVar1 = (*dword_c65c0)();
  return CONCAT44(unaff_EDX,uVar1);
}


// ================================================================================================
// sub_18182 @ 0x18182 [__watcall]
// ================================================================================================

undefined8 __watcall sub_18182(undefined4 param_1,undefined4 unaff_EDX)

{
  undefined4 uVar1;
  
  __CHK(0x20);
  dword_c65b0 = 3;
  if (dword_dc738 != 0) {
    dword_dc6b0 = allocmem(aSfPal1,0x300,0x20);
    getpalette(0,0x100,dword_dc6b0);
    dword_dc6ac = allocmem(aSfPal2,0x300,0x20);
    getpalette(0,0x100,dword_dc6ac);
    fade_palette(1,dword_dc6b0,0x10);
    freemem(dword_dc6b0);
    dword_dc6a8 = sub_235be(3);
    fade_palette(0,dword_dc6ac,0x10);
    freemem(dword_dc6ac);
    return CONCAT44(unaff_EDX,dword_dc6a8);
  }
  uVar1 = (*dword_c65c0)();
  return CONCAT44(unaff_EDX,uVar1);
}


// ================================================================================================
// sub_18265 @ 0x18265 [__watcall]
// ================================================================================================

undefined8 __watcall sub_18265(undefined4 param_1,undefined4 unaff_EDX)

{
  undefined4 uVar1;
  
  __CHK(0x20);
  dword_c65b0 = 4;
  if (dword_dc738 != 0) {
    dword_dc6b0 = allocmem(aSfPal1,0x300,0x20);
    getpalette(0,0x100,dword_dc6b0);
    dword_dc6ac = allocmem(aSfPal2,0x300,0x20);
    getpalette(0,0x100,dword_dc6ac);
    fade_palette(1,dword_dc6b0,0x10);
    freemem(dword_dc6b0);
    dword_dc6a8 = sub_235be(4);
    fade_palette(0,dword_dc6ac,0x10);
    freemem(dword_dc6ac);
    return CONCAT44(unaff_EDX,dword_dc6a8);
  }
  uVar1 = (*dword_c65c0)();
  return CONCAT44(unaff_EDX,uVar1);
}


// ================================================================================================
// sub_18348 @ 0x18348 [__watcall]
// ================================================================================================

undefined8 __watcall sub_18348(undefined4 param_1,undefined4 unaff_EDX)

{
  undefined4 uVar1;
  
  __CHK(0x20);
  dword_c65b0 = 0;
  if (dword_dc738 != 0) {
    dword_dc6b0 = allocmem(aSfPal1,0x300,0x20);
    getpalette(0,0x100,dword_dc6b0);
    dword_dc6ac = allocmem(aSfPal2,0x300,0x20);
    getpalette(0,0x100,dword_dc6ac);
    fade_palette(1,dword_dc6b0,0x10);
    freemem(dword_dc6b0);
    dword_dc6a8 = sub_25b24(0);
    fade_palette(0,dword_dc6ac,0x10);
    freemem(dword_dc6ac);
    return CONCAT44(unaff_EDX,dword_dc6a8);
  }
  uVar1 = (*dword_c65c4)();
  return CONCAT44(unaff_EDX,uVar1);
}


// ================================================================================================
// sub_18425 @ 0x18425 [__watcall]
// ================================================================================================

undefined8 __watcall sub_18425(undefined4 param_1,undefined4 unaff_EDX)

{
  undefined4 uVar1;
  
  __CHK(0x20);
  dword_c65b0 = 1;
  if (dword_dc738 != 0) {
    dword_dc6b0 = allocmem(aSfPal1,0x300,0x20);
    getpalette(0,0x100,dword_dc6b0);
    dword_dc6ac = allocmem(aSfPal2,0x300,0x20);
    getpalette(0,0x100,dword_dc6ac);
    fade_palette(1,dword_dc6b0,0x10);
    freemem(dword_dc6b0);
    dword_dc6a8 = sub_25b24(1);
    fade_palette(0,dword_dc6ac,0x10);
    freemem(dword_dc6ac);
    return CONCAT44(unaff_EDX,dword_dc6a8);
  }
  uVar1 = (*dword_c65c4)();
  return CONCAT44(unaff_EDX,uVar1);
}


// ================================================================================================
// sub_18508 @ 0x18508 [__watcall]
// ================================================================================================

undefined8 __watcall sub_18508(undefined4 param_1,undefined4 unaff_EDX)

{
  undefined4 uVar1;
  
  __CHK(0x20);
  dword_c65b0 = 2;
  if (dword_dc738 != 0) {
    dword_dc6b0 = allocmem(aSfPal1,0x300,0x20);
    getpalette(0,0x100,dword_dc6b0);
    dword_dc6ac = allocmem(aSfPal2,0x300,0x20);
    getpalette(0,0x100,dword_dc6ac);
    fade_palette(1,dword_dc6b0,0x10);
    freemem(dword_dc6b0);
    dword_dc6a8 = sub_25b24(2);
    fade_palette(0,dword_dc6ac,0x10);
    freemem(dword_dc6ac);
    return CONCAT44(unaff_EDX,dword_dc6a8);
  }
  uVar1 = (*dword_c65c4)();
  return CONCAT44(unaff_EDX,uVar1);
}


// ================================================================================================
// sub_185eb @ 0x185eb [__watcall]
// ================================================================================================

undefined8 __watcall sub_185eb(undefined4 param_1,undefined4 unaff_EDX)

{
  undefined4 uVar1;
  
  __CHK(0x20);
  dword_c65b0 = 3;
  if (dword_dc738 != 0) {
    dword_dc6b0 = allocmem(aSfPal1,0x300,0x20);
    getpalette(0,0x100,dword_dc6b0);
    dword_dc6ac = allocmem(aSfPal2,0x300,0x20);
    getpalette(0,0x100,dword_dc6ac);
    fade_palette(1,dword_dc6b0,0x10);
    freemem(dword_dc6b0);
    dword_dc6a8 = sub_25b24(3);
    fade_palette(0,dword_dc6ac,0x10);
    freemem(dword_dc6ac);
    return CONCAT44(unaff_EDX,dword_dc6a8);
  }
  uVar1 = (*dword_c65c4)();
  return CONCAT44(unaff_EDX,uVar1);
}


// ================================================================================================
// sub_186ce @ 0x186ce [__watcall]
// ================================================================================================

undefined8 __watcall sub_186ce(undefined4 param_1,undefined4 unaff_EDX)

{
  undefined4 uVar1;
  
  __CHK(0x20);
  dword_c65b0 = 4;
  if (dword_dc738 != 0) {
    dword_dc6b0 = allocmem(aSfPal1,0x300,0x20);
    getpalette(0,0x100,dword_dc6b0);
    dword_dc6ac = allocmem(aSfPal2,0x300,0x20);
    getpalette(0,0x100,dword_dc6ac);
    fade_palette(1,dword_dc6b0,0x10);
    freemem(dword_dc6b0);
    dword_dc6a8 = sub_25b24(4);
    fade_palette(0,dword_dc6ac,0x10);
    freemem(dword_dc6ac);
    return CONCAT44(unaff_EDX,dword_dc6a8);
  }
  uVar1 = (*dword_c65c4)();
  return CONCAT44(unaff_EDX,uVar1);
}


// ================================================================================================
// sub_187b1 @ 0x187b1 [__watcall]
// ================================================================================================

undefined8 __watcall sub_187b1(undefined4 param_1,undefined4 unaff_EDX)

{
  undefined4 uVar1;
  
  __CHK(0x20);
  dword_c65b0 = 5;
  if (dword_dc738 != 0) {
    dword_dc6b0 = allocmem(aSfPal1,0x300,0x20);
    getpalette(0,0x100,dword_dc6b0);
    dword_dc6ac = allocmem(aSfPal2,0x300,0x20);
    getpalette(0,0x100,dword_dc6ac);
    fade_palette(1,dword_dc6b0,0x10);
    freemem(dword_dc6b0);
    dword_dc6a8 = sub_25b24(5);
    fade_palette(0,dword_dc6ac,0x10);
    freemem(dword_dc6ac);
    return CONCAT44(unaff_EDX,dword_dc6a8);
  }
  uVar1 = (*dword_c65c4)();
  return CONCAT44(unaff_EDX,uVar1);
}


// ================================================================================================
// sub_18894 @ 0x18894 [__watcall]
// ================================================================================================

undefined8 __watcall sub_18894(undefined4 param_1,undefined4 unaff_EDX)

{
  undefined4 uVar1;
  
  __CHK(0x20);
  dword_c65b0 = 6;
  if (dword_dc738 != 0) {
    dword_dc6b0 = allocmem(aSfPal1,0x300,0x20);
    getpalette(0,0x100,dword_dc6b0);
    dword_dc6ac = allocmem(aSfPal2,0x300,0x20);
    getpalette(0,0x100,dword_dc6ac);
    fade_palette(1,dword_dc6b0,0x10);
    freemem(dword_dc6b0);
    dword_dc6a8 = sub_25b24(6);
    fade_palette(0,dword_dc6ac,0x10);
    freemem(dword_dc6ac);
    return CONCAT44(unaff_EDX,dword_dc6a8);
  }
  uVar1 = (*dword_c65c4)();
  return CONCAT44(unaff_EDX,uVar1);
}


// ================================================================================================
// sub_18977 @ 0x18977 [__watcall]
// ================================================================================================

undefined8 __watcall sub_18977(undefined4 param_1,undefined4 unaff_EDX)

{
  undefined4 uVar1;
  
  __CHK(0x20);
  dword_c65b0 = 7;
  if (dword_dc738 != 0) {
    dword_dc6b0 = allocmem(aSfPal1,0x300,0x20);
    getpalette(0,0x100,dword_dc6b0);
    dword_dc6ac = allocmem(aSfPal2,0x300,0x20);
    getpalette(0,0x100,dword_dc6ac);
    fade_palette(1,dword_dc6b0,0x10);
    freemem(dword_dc6b0);
    dword_dc6a8 = sub_25b24(7);
    fade_palette(0,dword_dc6ac,0x10);
    freemem(dword_dc6ac);
    return CONCAT44(unaff_EDX,dword_dc6a8);
  }
  uVar1 = (*dword_c65c4)();
  return CONCAT44(unaff_EDX,uVar1);
}


// ================================================================================================
// sub_18a5a @ 0x18a5a [__watcall]
// ================================================================================================

undefined8 __watcall sub_18a5a(undefined4 param_1,undefined4 unaff_EDX)

{
  undefined4 uVar1;
  
  __CHK(0x20);
  dword_c65b0 = 8;
  if (dword_dc738 != 0) {
    dword_dc6b0 = allocmem(aSfPal1,0x300,0x20);
    getpalette(0,0x100,dword_dc6b0);
    dword_dc6ac = allocmem(aSfPal2,0x300,0x20);
    getpalette(0,0x100,dword_dc6ac);
    fade_palette(1,dword_dc6b0,0x10);
    freemem(dword_dc6b0);
    dword_dc6a8 = sub_25b24(8);
    fade_palette(0,dword_dc6ac,0x10);
    freemem(dword_dc6ac);
    return CONCAT44(unaff_EDX,dword_dc6a8);
  }
  uVar1 = (*dword_c65c8)();
  return CONCAT44(unaff_EDX,uVar1);
}


// ================================================================================================
// sub_18b3d @ 0x18b3d [__watcall]
// ================================================================================================

undefined8 __watcall sub_18b3d(undefined4 param_1,undefined4 unaff_EDX)

{
  undefined4 uVar1;
  
  __CHK(0x20);
  dword_c65b0 = 9;
  if (dword_dc738 != 0) {
    dword_dc6b0 = allocmem(aSfPal1,0x300,0x20);
    getpalette(0,0x100,dword_dc6b0);
    dword_dc6ac = allocmem(aSfPal2,0x300,0x20);
    getpalette(0,0x100,dword_dc6ac);
    fade_palette(1,dword_dc6b0,0x10);
    freemem(dword_dc6b0);
    dword_dc6a8 = sub_25b24(9);
    fade_palette(0,dword_dc6ac,0x10);
    freemem(dword_dc6ac);
    return CONCAT44(unaff_EDX,dword_dc6a8);
  }
  uVar1 = (*dword_c65c8)();
  return CONCAT44(unaff_EDX,uVar1);
}


// ================================================================================================
// sub_18c20 @ 0x18c20 [__watcall]
// ================================================================================================

undefined8 __watcall sub_18c20(undefined4 param_1,undefined4 unaff_EDX)

{
  undefined4 uVar1;
  
  __CHK(0x20);
  dword_c65b0 = 10;
  if (dword_dc738 != 0) {
    dword_dc6b0 = allocmem(aSfPal1,0x300,0x20);
    getpalette(0,0x100,dword_dc6b0);
    dword_dc6ac = allocmem(aSfPal2,0x300,0x20);
    getpalette(0,0x100,dword_dc6ac);
    fade_palette(1,dword_dc6b0,0x10);
    freemem(dword_dc6b0);
    dword_dc6a8 = sub_25b24(10);
    fade_palette(0,dword_dc6ac,0x10);
    freemem(dword_dc6ac);
    return CONCAT44(unaff_EDX,dword_dc6a8);
  }
  uVar1 = (*dword_c65c8)();
  return CONCAT44(unaff_EDX,uVar1);
}


// ================================================================================================
// sub_18d03 @ 0x18d03 [__watcall]
// ================================================================================================

void __watcall sub_18d03(void)

{
  sub_179eb();
  return;
}


// ================================================================================================
// sub_18d0d @ 0x18d0d [__watcall]
// ================================================================================================

undefined4 __watcall sub_18d0d(void)

{
  __CHK(4);
  dword_c65bc = (byte_dc836 != 'G') + 4;
  return 1;
}


// ================================================================================================
// sub_18d33 @ 0x18d33 [__watcall]
// ================================================================================================

longlong __watcall sub_18d33(undefined4 param_1,uint unaff_EDX)

{
  __CHK(0x1c);
  if (dword_c65ac != 0) {
    freemem(dword_c65ac);
    dword_c65ac = 0;
  }
  if (dword_c65a8 != 0) {
    freemem(dword_c65a8);
    dword_c65a8 = 0;
  }
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// sub_18d7f @ 0x18d7f [__watcall]
// ================================================================================================

longlong __watcall sub_18d7f(undefined4 param_1,uint unaff_EDX)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  char acStack_2c [12];
  undefined4 local_20;
  undefined4 uStack_1c;
  
  __CHK(0x44);
  uVar3 = dword_c71dc;
  uVar2 = dword_c71d8;
  uVar1 = dword_c71d4;
  uStack_1c = dword_c71cc;
  local_20 = dword_c71d0;
  dword_c71cc = 0x41;
  dword_c71d0 = 0x40;
  dword_c71d4 = 0x42;
  dword_c71d8 = 0x40;
  dword_c71dc = 0;
  iVar4 = sub_2fedf(aPleaseEnterOutputFileNam,acStack_2c,8,0x22,0,0,0,0,5);
  if ((iVar4 != 0x1b) && (acStack_2c[0] != '\0')) {
    sub_17816(acStack_2c);
  }
  dword_c71cc = uStack_1c;
  dword_c71d0 = local_20;
  dword_c71d4 = uVar1;
  dword_c71d8 = uVar2;
  dword_c71dc = uVar3;
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// sub_18e43 @ 0x18e43 [__watcall]
// ================================================================================================

void __watcall
sub_18e43(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  __CHK(0x24);
  sub_b4fac(0xe,0x21,0xaf,0x21,0x22,unaff_EDX,unaff_ECX,unaff_EBX);
  sub_b4fac(0xaf,0x21,0xaf,0x86,0x22);
  sub_b4fac(0xe,0x86,0xaf,0x86,0x22);
  sub_b4fac(0xe,0x86,0xe,0x21,0x22);
  sub_b4fac(0xd,0x20,0xb0,0x20,0x21);
  sub_b4fac(0xb0,0x20,0xb0,0x87,0x21);
  sub_b4fac(0xd,0x87,0xb0,0x87,0x21);
  sub_b4fac(0xd,0x87,0xd,0x20,0x21);
  sub_b4fac(0xc,0x1f,0xb1,0x1f,0x20);
  sub_b4fac(0xb1,0x1f,0xb1,0x88,0x20);
  sub_b4fac(0xc,0x88,0xb1,0x88,0x20);
  sub_b4fac(0xc,0x88,0xc,0x1f,0x20);
  return;
}


// ================================================================================================
// sub_18f74 @ 0x18f74 [__watcall]
// ================================================================================================

undefined4 __watcall sub_18f74(void)

{
  __CHK(4);
  return 1;
}


// ================================================================================================
// sub_18f86 @ 0x18f86 [__watcall]
// ================================================================================================

undefined4 __watcall sub_18f86(void)

{
  __CHK(4);
  return 1;
}


// ================================================================================================
// sub_18f8d @ 0x18f8d [__watcall]
// ================================================================================================

undefined8 __watcall sub_18f8d(undefined4 param_1,undefined4 unaff_EDX)

{
  short sVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  uint local_24;
  uint local_20;
  int iStack_1c;
  
  __CHK(0x2c);
  iVar2 = 0;
  do {
    if ((4 < (int)(&unk_dd730)[iVar2]) && ((&unk_dd730)[iVar2] != (&unk_dc868)[iVar2])) {
      dword_c65f4 = dword_c65f4 | 1 << ((byte)iVar2 & 0x1f);
    }
    iVar2 = iVar2 + 1;
  } while (iVar2 < 6);
  if (dword_c65f4 == 0x3f) {
    uVar3 = 0;
  }
  else {
    do {
      sVar1 = randomrange(6);
      iVar2 = (int)sVar1;
      iStack_1c._0_1_ = (byte)sVar1;
      uVar4 = 1 << ((byte)iStack_1c & 0x1f);
      iStack_1c = iVar2;
    } while ((uVar4 & dword_c65f4) != 0);
    dword_c65f4 = dword_c65f4 | uVar4;
    local_24 = (uint)(byte)(&unk_dd788)[iVar2 * 2];
    local_20 = (uint)(byte)(&unk_dd789)[iVar2 * 2];
    iVar5 = (&unk_dd730)[iVar2];
    if (4 < iVar5) {
      iVar5 = 3;
      local_24 = local_24 - 1;
      local_20 = local_20 - 1;
    }
    iVar2 = iVar2 * 2;
    uVar3 = sub_69336((&unk_dd774)[iVar2],(&unk_dd775)[iVar2],&local_24,&local_20,iVar5);
    iVar5 = (&unk_dd730)[iStack_1c];
    if (iVar5 < 5) {
      (&unk_dd788)[iVar2] = (undefined)local_24;
      (&unk_dd789)[iVar2] = (undefined)local_20;
      if (iVar5 == 4) {
        (&unk_dd730)[iStack_1c] = 5;
      }
    }
    iVar2 = 0;
    do {
      (&unk_dc868)[iVar2] = (&unk_dd730)[iVar2];
      iVar2 = iVar2 + 1;
    } while (iVar2 < 6);
  }
  return CONCAT44(unaff_EDX,uVar3);
}


// ================================================================================================
// sub_190be @ 0x190be [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall sub_190be(void)

{
  uint uVar1;
  int iVar2;
  
  __CHK(0x14);
  if (_dword_cbc44 >> 0x10 == -1) {
    sub_47c31();
  }
  else {
    sub_479e9();
    sub_61b85();
    sub_61c22();
    sub_6b410();
    uVar1 = boxscore_screen(1,_dword_d8c84,_dword_d8c84,0);
    sub_6b47c();
    if (dword_c53fb == 0) {
      if ((((dword_c90c8._2_2_ != 0x1a) && (dword_c90c8._2_2_ != 0x1b)) && (_dword_c90cc != 0x1a))
         && (_dword_c90cc != 0x1b)) {
        if (_dword_d8c84 == 1) {
          dword_c65f4 = 0;
          sub_2f2b1((int)dword_c90c8._2_2_,(int)_dword_c90cc);
          iVar2 = 0;
          do {
            (&unk_dc868)[iVar2] = (&unk_dd730)[iVar2];
            iVar2 = iVar2 + 1;
          } while (iVar2 < 6);
        }
        if ((uVar1 & 4) == 0) {
          sub_2f3d7(_dword_d8c84);
          iVar2 = sub_18f8d();
          if (-1 < iVar2) {
            sub_6b410();
            boxscore_screen(0x20,_dword_d8c84,0,0);
            sub_6b47c();
          }
        }
      }
    }
  }
  _dword_cbc44 = CONCAT22(0xffff,dword_cbc44);
  pause_menu(1);
  byte_c542f = 0;
  byte_c5430 = 0;
  byte_c5431 = 0;
  byte_c5432 = 0;
  sub_61c86();
  set_video_mode(0x140,200);
  return;
}


// ================================================================================================
// sub_1920f @ 0x1920f [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall
sub_1920f(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  undefined4 uVar1;
  int iVar2;
  uint extraout_EDX;
  
  __CHK(0x1c);
  getpalette(0,0x100,&unk_df014,unaff_EDX,unaff_ECX,unaff_EBX);
  fade_palette(1,&unk_df014,0x10);
  set_video_mode(0x280,0x1e0);
  sub_1baf3(140000);
  sub_479e9();
  sub_61b85();
  sub_61c22();
  sub_61bbf();
  sub_6b410();
  uVar1 = boxscore_screen(1,1,_dword_d8c84,0);
  sub_6b47c(uVar1,uVar1);
  if ((dword_c53fb == 0) && ((extraout_EDX & 4) == 0)) {
    if ((dword_c90c8._2_2_ != 0x1a) && (dword_c90c8._2_2_ != 0x1b)) {
      if ((_dword_c90cc != 0x1a) && (_dword_c90cc != 0x1b)) {
        sub_2f3d7(_dword_d8c84);
        sub_18f8d();
        set_video_mode(0x280,0x1e0);
        sub_1b982();
        iVar2 = sub_8bc15();
        if (iVar2 != 0) {
          iVar2 = sub_33e6a(10);
        }
        if (iVar2 == 0) {
          sub_479e9();
          sub_6b410();
          boxscore_screen(0x20,_dword_d8c84,0,0);
          sub_6b47c();
        }
      }
    }
  }
  pause_menu(2);
  dword_c53f7 = 1;
  set_video_mode(0x140,200);
  return;
}


// ================================================================================================
// pause_menu @ 0x1935d [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

longlong __watcall pause_menu(int param_1,uint unaff_EDX)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int iVar6;
  undefined4 *puVar7;
  int *piVar8;
  undefined4 extraout_EDX;
  undefined *puVar9;
  int iVar10;
  undefined4 *puVar11;
  undefined4 *puVar12;
  undefined4 *puVar13;
  undefined4 *puVar14;
  byte bVar15;
  undefined8 uVar16;
  ulonglong uVar17;
  undefined auStack_41c [768];
  undefined auStack_11c [64];
  undefined auStack_dc [24];
  int aiStack_c4 [10];
  int local_9c [12];
  int *local_6c [4];
  int local_5c;
  int local_58;
  int local_54;
  int local_50;
  undefined4 local_4c;
  undefined4 local_48;
  uint local_44;
  int local_40;
  int *local_3c;
  int *local_38;
  int local_34;
  int local_30;
  int local_2c;
  undefined4 *local_28;
  int iStack_24;
  int *local_20;
  int iStack_1c;
  
  bVar15 = 0;
  __CHK(0x434);
  iStack_1c = 0;
  local_2c = 0;
  local_30 = 0x5dc;
  sub_805c4(dword_c53fb);
  menu_hub_labels(param_1 + 3);
  uVar16 = sub_12034();
  funcptr_cef23 = (undefined *)((ulonglong)uVar16 >> 0x20);
  if ((int)uVar16 == 0) {
    funcptr_cef23 = sub_1a817;
  }
  getmouse(&local_44,&local_48,&local_4c);
  dword_c4e14 = 0;
  _dword_c4d0c = 0;
  if (param_1 == 0) {
    sub_1baf3(700000);
    getpalette(0,0x100,auStack_41c);
    fade_palette(1,auStack_41c,0x10);
  }
  setdefaultscreen();
  sprintf(&unk_dc890,aEadesk1d,param_1);
  puVar9 = off_d2c6b;
  if ((&unk_ed830)[param_1] != '\x01') {
    puVar9 = (undefined *)0x0;
  }
  make_path(auStack_dc,puVar9,&unk_dc890,0);
  uVar4 = loadshapes(auStack_dc,0);
  uVar5 = locateshape(uVar4,&aDesk);
  drawshape_home(uVar5);
  iVar6 = locateshape(uVar4,&aPal_c097f);
  iVar10 = 0;
  do {
    auStack_41c[iVar10] = *(undefined *)(iVar6 + 0x10 + iVar10);
    iVar10 = iVar10 + 1;
  } while (iVar10 < 0x300);
  freemem(uVar4);
  getfontstate(auStack_11c);
  setfont(dword_dc230);
  if (param_1 == 2) {
    if (0x443 < dword_dc234) {
      sub_59d54();
    }
    local_6c[0] = (int *)&unk_cec4f;
    local_9c[8] = 3;
  }
  else {
    local_6c[0] = (int *)&unk_ceb8f;
    local_9c[8] = 6;
  }
  local_6c[3] = (int *)0x0;
  local_6c[2] = (int *)0x0;
  local_6c[1] = (int *)0x0;
  local_9c[3] = 0;
  local_9c[2] = 0;
  local_9c[1] = 0;
  local_9c[0] = 0;
  local_9c[7] = 0;
  local_9c[6] = 0;
  local_9c[5] = 0;
  local_9c[4] = 0;
  aiStack_c4[3] = 0;
  aiStack_c4[2] = 0;
  puVar7 = (undefined4 *)
           allocmem(aPointer,((*(int *)((int)dword_dc238 + 2) >> 0x10) + 1) *
                             (((int)dword_dc238[1] >> 0x10) + 1) + 0x11,0x20);
  puVar13 = puVar7 + (uint)bVar15 * -2 + 1;
  puVar11 = dword_dc238 + (uint)bVar15 * -2 + 1;
  *puVar7 = *dword_dc238;
  puVar14 = puVar13 + (uint)bVar15 * -2 + 1;
  puVar12 = puVar11 + (uint)bVar15 * -2 + 1;
  *puVar13 = *puVar11;
  *puVar14 = *puVar12;
  puVar14[(uint)bVar15 * -2 + 1] = puVar12[(uint)bVar15 * -2 + 1];
  *(undefined *)(puVar14 + (uint)bVar15 * -2 + 1 + (uint)bVar15 * -2 + 1) =
       *(undefined *)(puVar12 + (uint)bVar15 * -2 + 1 + (uint)bVar15 * -2 + 1);
  *(short *)(puVar7 + 1) = *(short *)(dword_dc238 + 1) + 1;
  *(short *)((int)puVar7 + 6) = *(short *)((int)dword_dc238 + 6) + 1;
  local_28 = puVar7;
  sub_6b5e4(local_6c[0],local_9c[8],0xfa,0xf9,0xf8);
  sub_6b410();
  piVar8 = (int *)((*local_6c[0] + local_6c[0][2]) / 2);
  iVar6 = (local_6c[0][1] + local_6c[0][3]) / 2;
  local_40 = iVar6;
  local_3c = piVar8;
  local_34 = iVar6;
  local_20 = piVar8;
  grabshape(puVar7,piVar8,iVar6);
  drawshape_remap(dword_dc238,piVar8,iVar6);
  if ((byte_d2430 != '\0') && (dword_c721d == 0)) {
    puVar9 = off_d2c6b;
    if (byte_ed9e8 != '\x01') {
      puVar9 = (undefined *)0x0;
    }
    make_path(auStack_dc,puVar9,aPause,&aIff_c098c);
    dword_c721d = loadsound(auStack_dc);
    if ((dword_c721d != 0) && (((byte)dword_c53ff & 0x40) != 0)) {
      playsample(dword_c721d,dword_d2431,3,0x4c);
    }
  }
  piVar8 = (int *)0x10;
  fade_palette(0,auStack_41c,0x10);
  setmouselimits(0,0,0x280,0x1e0);
  setmousepos(local_20,local_34);
  (*(code *)funcptr_d3078)();
  sub_6b3d7();
  if (((param_1 == 1) && (dword_c5403 < 0)) && (dword_c5407 < 0)) {
    local_2c = 1;
  }
  uVar16 = ticks_elapsed();
  if ((param_1 == 2) && (0x443 < dword_dc234)) {
    if (dword_df722._2_2_ < dword_df622._2_2_) {
      iVar6 = CONCAT22(dword_c90c8._2_2_,(undefined2)dword_c90c8);
    }
    else {
      iVar6 = CONCAT22(_dword_c90cc,dword_c90c8._2_2_);
    }
    uVar4 = 0;
    if (3 < _dword_d8c84) {
      uVar4 = 0xffffffff;
    }
    if (*(uint *)(&unk_c5581 + dword_c90c8._2_2_ * 4) == *(uint *)(&unk_c5581 + _dword_c90cc * 4)) {
      piVar8 = (int *)((int)(*(uint *)(&unk_c5581 + dword_c90c8._2_2_ * 4) |
                            *(uint *)(&unk_c5581 + _dword_c90cc * 4)) % 2 + 1);
    }
    else {
      piVar8 = (int *)0x3;
    }
    uVar5 = 1;
    if (0x47b < dword_dc234) {
      uVar5 = 2;
    }
    if (0x497 < dword_dc234) {
      uVar5 = 3;
    }
    uVar16 = sub_59cdd(iVar6 >> 0x10,(dword_dc234 + -0x444) % 7 + 1,piVar8,uVar5,uVar4,
                       (int)ram0x000ccc9d >> 0x18);
    uVar16 = CONCAT44(CONCAT22((short)((ulonglong)uVar16 >> 0x30),
                               (ushort)(byte)((ulonglong)uVar16 >> 0x20)),(int)uVar16);
    ram0x000ccc9d = ram0x000ccc9d & 0xffffff;
  }
  local_38 = (int *)0xb4;
LAB_00019af6:
  piVar2 = local_38;
  if (byte_d2430 != '\0') {
    if (local_38 < (int *)0xb396f) {
      if (0 < (int)local_38) {
        local_38 = (int *)0x0;
      }
    }
    else {
      uVar16 = ticks_elapsed();
      local_38 = (int *)((int)local_38 - (int)uVar16);
    }
    piVar8 = piVar2;
    if (((local_38 == (int *)0x0) && (param_1 == 0)) &&
       ((dword_c53f7 == 0 && ((dword_c53ff._1_1_ & 1) != 0)))) {
      local_38 = (int *)0xffffffff;
      sub_837a8();
      uVar16 = sub_84715();
    }
  }
  if (local_2c != 0) {
    iVar6 = ticks_elapsed((int)uVar16,(int)((ulonglong)uVar16 >> 0x20),piVar8);
    local_30 = local_30 - iVar6;
    if (local_30 < 0) {
      if ((byte_d2430 != '\0') && (dword_c721d != 0)) {
        sound_fade(dword_d2431,3,100);
      }
      dword_c66d4 = 1;
      dword_c66d0 = 1;
      sub_6b3d7();
      sub_6b47c();
      setfontstate(auStack_11c);
      _dword_dd6aa = setmouselimits(0,0,0x280,0x1e0);
      dword_c5840 = 0;
      dword_dd6ac._0_2_ = _dword_dd6aa;
      setmousepos(local_48,local_4c);
      getpalette(0,0x100,auStack_41c);
      fade_palette(1,auStack_41c);
      menu_hub_labels(dword_c53fb);
      freemem(local_28);
      if ((byte_d2430 != '\0') && (dword_c721d != 0)) {
        do {
          iVar6 = sound_channel_status(ram0x000d242c >> 0x18,3);
        } while (iVar6 == 0);
        releasememblock(dword_c721d);
        dword_c721d = 0;
      }
      sub_1a534();
      if (((byte_d2430 != '\0') && (dword_c53f7 == 0)) && ((dword_c53ff._1_1_ & 1) != 0)) {
        sub_837a8();
        sub_84729();
      }
      goto LAB_00019a00;
    }
  }
  local_44 = 0;
  do {
    uVar16 = sub_6b391();
    uVar17 = CONCAT44((int)((ulonglong)uVar16 >> 0x20),local_44);
    if ((int)uVar16 == 0) break;
    piVar8 = &local_40;
    uVar17 = (*dword_ea0dc)();
    local_44 = (uint)uVar17;
  } while ((uVar17 & 2) == 0);
  local_44 = (uint)uVar17;
  uVar16 = CONCAT44((int)(uVar17 >> 0x20),local_40);
  if ((uVar17 & 2) == 0) goto code_r0x00019a4e;
  local_2c = 0;
  iVar6 = sub_6ba4d(local_3c,local_40,local_6c,iStack_1c,local_9c + 8,aiStack_c4 + 2,&local_50,
                    &local_54);
  if (iVar6 == 0) {
    drawshape(local_28,local_20,local_34);
    for (iVar6 = iStack_1c; 0 < iVar6; iVar6 = iVar6 + -1) {
      local_9c[iVar6 + 4] = 0;
      if (local_9c[iVar6] != 0) {
        drawshape(local_9c[iVar6],aiStack_c4[iVar6 * 2 + 2],aiStack_c4[iVar6 * 2 + 3]);
        aiStack_c4[iVar6 * 2 + 3] = 0;
        aiStack_c4[iVar6 * 2 + 2] = 0;
        freemem(local_9c[iVar6]);
      }
    }
    iStack_1c = 0;
    local_6c[3] = (int *)0x0;
    local_6c[2] = (int *)0x0;
    local_6c[1] = (int *)0x0;
    local_9c[3] = 0;
    local_9c[2] = 0;
    local_9c[1] = 0;
    local_9c[0] = 0;
    local_9c[7] = 0;
    local_9c[6] = 0;
    local_9c[5] = 0;
    local_9c[0xb] = 0;
    local_9c[10] = 0;
    local_9c[9] = 0;
  }
  else if (local_6c[local_50][local_54 * 8 + 5] == 0) {
    if (local_6c[local_50][local_54 * 8 + 6] != 0) {
      drawshape(local_28,local_20,local_34);
      iVar6 = iStack_1c;
      if (iStack_1c != local_50) {
        for (; local_50 < iVar6; iVar6 = iVar6 + -1) {
          local_9c[iVar6 + 4] = 0;
          if (local_9c[iVar6] != 0) {
            drawshape(local_9c[iVar6],aiStack_c4[iVar6 * 2 + 2],aiStack_c4[iVar6 * 2 + 3]);
            aiStack_c4[iVar6 * 2 + 3] = 0;
            aiStack_c4[iVar6 * 2 + 2] = 0;
            freemem(local_9c[iVar6]);
            local_9c[iVar6] = 0;
            local_6c[iVar6] = (int *)0x0;
            local_9c[iVar6 + 8] = 0;
          }
        }
        iStack_1c = local_50;
      }
      iVar3 = iStack_1c;
      sub_6b94e(local_6c[iStack_1c] + local_9c[iStack_1c + 4] * 8,aiStack_c4[iStack_1c * 2 + 2],
                aiStack_c4[iStack_1c * 2 + 3],0xfa,0xf9,0xf8);
      iVar6 = local_54;
      local_9c[iVar3 + 4] = local_54;
      sub_6b9eb(local_6c[iVar3] + iVar6 * 8,aiStack_c4[iVar3 * 2 + 2],aiStack_c4[iVar3 * 2 + 3],0xfa
                ,0xf9,0xf8);
      iVar1 = local_50;
      iVar10 = local_54;
      iVar6 = iVar3 + 1;
      iStack_1c = iVar6;
      local_6c[iVar6] = (int *)local_6c[local_50][local_54 * 8 + 6];
      piVar8 = local_6c[iVar1] + iVar10 * 8;
      local_9c[iVar3 + 9] = piVar8[7];
      if (iVar6 == 1) {
        iVar6 = *piVar8;
      }
      else {
        iVar6 = piVar8[2];
      }
      aiStack_c4[iStack_1c * 2 + 2] = iVar6 + aiStack_c4[iStack_1c * 2];
      if (iStack_1c == 1) {
        iVar6 = local_6c[local_50][local_54 * 8 + 3];
      }
      else {
        iVar6 = local_6c[local_50][local_54 * 8 + 1];
      }
      iStack_24 = iStack_1c * 8;
      aiStack_c4[iStack_1c * 2 + 3] = iVar6 + aiStack_c4[iStack_1c * 2 + 1];
      iVar1 = iStack_1c;
      piVar8 = local_6c[iStack_1c];
      local_5c = (piVar8[local_9c[iStack_1c + 8] * 8 + -6] - *piVar8) + 1;
      local_58 = (piVar8[local_9c[iStack_1c + 8] * 8 + -5] - piVar8[1]) + 1;
      puVar7 = (undefined4 *)allocmem(aMenubuff,local_5c * local_58 + 0x11,0x20);
      local_9c[iVar1] = (int)puVar7;
      puVar12 = puVar7 + (uint)bVar15 * -2 + 1;
      puVar11 = dword_dc238 + (uint)bVar15 * -2 + 1;
      *puVar7 = *dword_dc238;
      puVar13 = puVar12 + (uint)bVar15 * -2 + 1;
      puVar7 = puVar11 + (uint)bVar15 * -2 + 1;
      *puVar12 = *puVar11;
      *puVar13 = *puVar7;
      puVar13[(uint)bVar15 * -2 + 1] = puVar7[(uint)bVar15 * -2 + 1];
      *(undefined *)(puVar13 + (uint)bVar15 * -2 + 1 + (uint)bVar15 * -2 + 1) =
           *(undefined *)(puVar7 + (uint)bVar15 * -2 + 1 + (uint)bVar15 * -2 + 1);
      *(short *)(local_9c[iVar1] + 4) = (short)local_5c;
      *(short *)(local_9c[iVar1] + 6) = (short)local_58;
      grabshape(local_9c[iVar1],*(undefined4 *)((int)aiStack_c4 + iStack_24 + 8),
                *(undefined4 *)((int)aiStack_c4 + iStack_24 + 0xc));
      sub_6b684(local_6c[iVar1],local_9c[iVar1 + 8],*(undefined4 *)((int)aiStack_c4 + iStack_24 + 8)
                ,*(undefined4 *)((int)aiStack_c4 + iStack_24 + 0xc),0xfa,0xf9,0xf8);
      local_9c[iVar1 + 4] = 0;
      iVar6 = *(int *)((int)aiStack_c4 + iStack_24 + 0xc);
      iVar10 = *(int *)((int)aiStack_c4 + iStack_24 + 8);
      piVar8 = local_6c[iVar1];
      goto LAB_0001a0c7;
    }
    drawshape(local_28,local_20,local_34);
  }
  else if (local_54 == local_9c[local_50 + 4]) {
    drawshape(local_28,local_20,local_34);
    for (iVar6 = iStack_1c; 0 < iVar6; iVar6 = iVar6 + -1) {
      local_9c[iVar6 + 4] = 0;
      if (local_9c[iVar6] != 0) {
        drawshape(local_9c[iVar6],aiStack_c4[iVar6 * 2 + 2],aiStack_c4[iVar6 * 2 + 3]);
        aiStack_c4[iVar6 * 2 + 3] = 0;
        aiStack_c4[iVar6 * 2 + 2] = 0;
        freemem(local_9c[iVar6]);
      }
    }
    iStack_1c = 0;
    dword_dc88c = local_3c;
    dword_dc888 = local_40;
    local_44 = (*(code *)local_6c[local_50][local_54 * 8 + 5])();
    local_3c = dword_dc88c;
    local_40 = dword_dc888;
    local_6c[3] = (int *)0x0;
    local_6c[2] = (int *)0x0;
    local_6c[1] = (int *)0x0;
    local_9c[3] = 0;
    local_9c[2] = 0;
    local_9c[1] = 0;
    local_9c[0] = 0;
    local_9c[7] = 0;
    local_9c[6] = 0;
    local_9c[5] = 0;
    local_9c[0xb] = 0;
    local_9c[10] = 0;
    local_9c[9] = 0;
    if ((local_44 == 1) || (local_44 == 5)) {
      sub_6b3d7();
      sub_6b47c();
      setfontstate(auStack_11c);
      setmouselimits(0,0,0x280,0x1e0);
      dword_c5840 = 0;
      setmousepos(local_48,local_4c);
      getpalette(0,0x100,auStack_41c);
      if ((byte_d2430 != '\0') && (dword_c721d != 0)) {
        sound_fade(dword_d2431,3,100);
      }
      if (((local_44 == 1) && (byte_d2430 != '\0')) && ((dword_c53ff._1_1_ & 1) != 0)) {
        sub_837a8();
        sub_846f0();
      }
      fade_palette(1,auStack_41c,0x14);
      if (local_44 != 1) {
        dword_c53f7 = 2;
      }
      menu_hub_labels(dword_c53fb);
      if (local_28 != (undefined4 *)0x0) {
        freemem(local_28);
      }
      if ((byte_d2430 != '\0') && (dword_c721d != 0)) {
        do {
          iVar6 = sound_channel_status(ram0x000d242c >> 0x18,3);
        } while (iVar6 == 0);
        releasememblock(dword_c721d);
        dword_c721d = 0;
      }
      if (local_44 == 1) {
        sub_1a534();
      }
      if (((local_44 == 1) && (byte_d2430 != '\0')) && ((dword_c53ff._1_1_ & 1) != 0)) {
        do {
          iVar6 = sub_836e4();
        } while (iVar6 != 0);
        sub_84704();
      }
LAB_00019a00:
      return (ulonglong)unaff_EDX << 0x20;
    }
    if (local_44 == 2) {
      getpalette(0,0x100,auStack_41c);
      fade_palette(1,auStack_41c,0x10);
      sub_1baf3(700000);
      puVar9 = off_d2c6b;
      if ((&unk_ed830)[param_1] != '\x01') {
        puVar9 = (undefined *)0x0;
      }
      make_path(auStack_dc,puVar9,&unk_dc890,0);
      uVar4 = loadshapes(auStack_dc,0);
      uVar5 = locateshape(uVar4,&aDesk);
      drawshape_home(uVar5);
      iVar6 = locateshape(uVar4,&aPal_c097f);
      iVar10 = 0;
      do {
        auStack_41c[iVar10] = *(undefined *)(iVar6 + 0x10 + iVar10);
        iVar10 = iVar10 + 1;
      } while (iVar10 < 0x300);
      freemem(uVar4);
      sub_6b5e4(local_6c[0],local_9c[8],0xfa,0xf9,0xf8);
      fade_palette(0,auStack_41c,0x10);
    }
    setmousepos(local_20,local_34);
    sub_6b3d7();
  }
  else {
    drawshape(local_28,local_20,local_34);
    iVar6 = iStack_1c;
    if (iStack_1c != local_50) {
      for (; local_50 < iVar6; iVar6 = iVar6 + -1) {
        local_9c[iVar6 + 4] = 0;
        if (local_9c[iVar6] != 0) {
          drawshape(local_9c[iVar6],aiStack_c4[iVar6 * 2 + 2],aiStack_c4[iVar6 * 2 + 3]);
          aiStack_c4[iVar6 * 2 + 3] = 0;
          aiStack_c4[iVar6 * 2 + 2] = 0;
          freemem(local_9c[iVar6]);
          local_9c[iVar6] = 0;
          local_6c[iVar6] = (int *)0x0;
          local_9c[iVar6 + 8] = 0;
        }
      }
      iStack_1c = local_50;
    }
    sub_6b94e(local_6c[local_50] + local_9c[local_50 + 4] * 8,aiStack_c4[local_50 * 2 + 2],
              aiStack_c4[local_50 * 2 + 3],0xfa,0xf9,0xf8);
    iVar1 = local_50;
    local_9c[local_50 + 4] = local_54;
    iVar6 = aiStack_c4[iVar1 * 2 + 3];
    iVar10 = aiStack_c4[iVar1 * 2 + 2];
    piVar8 = local_6c[iVar1] + local_9c[iVar1 + 4] * 8;
LAB_0001a0c7:
    sub_6b9eb(piVar8,iVar10,iVar6,0xfa,0xf9,0xf8);
  }
  grabshape(local_28,local_3c,local_40);
  piVar8 = local_3c;
  goto LAB_00019ad2;
code_r0x00019a4e:
  if ((local_3c != local_20) || (local_40 != local_34)) {
    local_2c = 0;
    drawshape(local_28,local_20,local_34);
    piVar8 = local_3c;
    grabshape(local_28,local_3c,local_40);
LAB_00019ad2:
    drawshape_remap(dword_dc238,local_3c,local_40);
    uVar16 = CONCAT44(extraout_EDX,local_40);
    local_20 = local_3c;
    local_34 = local_40;
  }
  goto LAB_00019af6;
}


// ================================================================================================
// sub_1a534 @ 0x1a534 [__watcall]
// ================================================================================================

void __watcall
sub_1a534(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  int iVar1;
  
  __CHK(0x1c);
  if (dword_c90c8._2_2_ < 0x1a) {
    iVar1 = dword_c90c8 >> 0x10;
  }
  else {
    iVar1 = 0xc;
  }
  sub_3377c(iVar1);
  sub_1395f();
  getpalette(0,0x100,&unk_df014,unaff_EDX,unaff_ECX,unaff_EBX);
  fade_palette(1,&unk_df014,0x10);
  dword_c66d4 = 1;
  dword_c66d0 = 1;
  return;
}


// ================================================================================================
// sub_1a5a1 @ 0x1a5a1 [__watcall]
// ================================================================================================

undefined4 __watcall sub_1a5a1(void)

{
  __CHK(4);
  return 1;
}


// ================================================================================================
// sub_1a5b1 @ 0x1a5b1 [__watcall]
// ================================================================================================

undefined8 __watcall sub_1a5b1(undefined4 param_1,undefined4 unaff_EDX)

{
  __CHK(8);
  dword_c66d4 = 1;
  dword_c66d0 = 1;
  return CONCAT44(unaff_EDX,5);
}


// ================================================================================================
// sub_1a5d4 @ 0x1a5d4 [__watcall]
// ================================================================================================

undefined8 __watcall sub_1a5d4(undefined4 param_1,undefined4 unaff_EDX)

{
  int iVar1;
  undefined4 uVar2;
  undefined local_1c [4];
  undefined local_18 [4];
  undefined auStack_14 [4];
  
  __CHK(0x34);
  getmouse(auStack_14,local_18,local_1c);
  if (dword_c53fb == 0) {
    dword_c66a4 = aReturningToSportsCentral;
  }
  else if (dword_c53fb < 2) {
    dword_c66a4 = aReturningToThePlayoffTre;
  }
  else if (dword_c53fb == 2) {
    dword_c66a4 = aReturningOutOfTheGame;
  }
  dword_c66ac = aDoYouWishToReturn;
  sub_30a0c(0xf9,0xfa,0xf8,0xfa,0);
  iVar1 = sub_31013(0xffffffff,0xffffffff,&dword_c66a4,3,&unk_d2b38,2,auStack_14,local_18,0xffffffff
                   );
  if (iVar1 < 1) {
    uVar2 = 0;
  }
  else {
    dword_c66d4 = 1;
    dword_c66d0 = 1;
    uVar2 = 5;
  }
  return CONCAT44(unaff_EDX,uVar2);
}


// ================================================================================================
// sub_1a6a7 @ 0x1a6a7 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

longlong __watcall sub_1a6a7(undefined4 param_1,uint unaff_EDX)

{
  int iVar1;
  int local_20;
  undefined local_1c [4];
  undefined auStack_18 [4];
  
  __CHK(0x38);
  if ((byte_d2430 != '\0') && (dword_c721d != 0)) {
    sound_fade(dword_d2431,3,100);
  }
  getmouse(auStack_18,local_1c,&local_20);
  dword_c66a4 = aExitingTheGame;
  dword_c66ac = aDoYouWishToExit;
  sub_30a0c(0xf9,0xfa,0xf8,0xfa,0);
  local_20 = sub_31013(0xffffffff,0xffffffff,&dword_c66a4,3,&unk_d2b38,2,auStack_18,local_1c,
                       0xffffffff);
  if (0 < local_20) {
    getpalette(0,0x100,&unk_df014);
    fade_palette(1,&unk_df014,0x10);
    setdefaultscreen();
    clearclip(0);
    if ((byte_d2430 != '\0') && (dword_c721d != 0)) {
      do {
        iVar1 = sound_channel_status(ram0x000d242c >> 0x18,3);
      } while (iVar1 == 0);
      releasememblock(dword_c721d);
      dword_c721d = 0;
    }
    sub_479e9();
    sub_1b982();
    sub_16f9a();
    getpalette(0,0x100,&unk_df014);
    fade_palette(1,&unk_df014,0x10);
    settextmode();
    (*(code *)funcptr_d41f0)();
  }
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// sub_1a817 @ 0x1a817 [__watcall]
// ================================================================================================

undefined8 __watcall
sub_1a817(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  int iVar1;
  
  __CHK(0x1c);
  if (dword_c90c8._2_2_ < 0x1a) {
    iVar1 = dword_c90c8 >> 0x10;
  }
  else {
    iVar1 = 0xc;
  }
  sub_3377c(iVar1);
  sub_1395f();
  getpalette(0,0x100,&unk_df014,unaff_EDX,unaff_ECX,unaff_EBX);
  fade_palette_to(1,&unk_df014,0x10);
  set_video_mode(0x140,200);
  instant_replay(0);
  setfont(dword_dc230);
  dword_c66d4 = 1;
  dword_c66d0 = 1;
  return CONCAT44(unaff_EDX,2);
}


// ================================================================================================
// sub_1a8aa @ 0x1a8aa [__watcall]
// ================================================================================================

undefined8 __watcall
sub_1a8aa(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  __CHK(0x1c);
  getpalette(0,0x100,&unk_df014,unaff_EDX,unaff_ECX,unaff_EBX);
  fade_palette(1,&unk_df014,0x10);
  sub_767d0(0,&unk_dc200,&unk_cf2ef,2);
  getpalette(0,0x100,&unk_df014);
  fade_palette(1,&unk_df014,0x10);
  return CONCAT44(unaff_EDX,2);
}


// ================================================================================================
// sub_1a922 @ 0x1a922 [__watcall]
// ================================================================================================

undefined8 __watcall
sub_1a922(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  __CHK(0x1c);
  getpalette(0,0x100,&unk_df014,unaff_EDX,unaff_ECX,unaff_EBX);
  fade_palette(1,&unk_df014,0x10);
  sub_767d0(1,&unk_dabf0,&unk_cf2ef,2);
  getpalette(0,0x100,&unk_df014);
  fade_palette(1,&unk_df014,0x10);
  return CONCAT44(unaff_EDX,2);
}


// ================================================================================================
// sub_1a96d @ 0x1a96d [__watcall]
// ================================================================================================

undefined8 __watcall
sub_1a96d(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  __CHK(0x1c);
  getpalette(0,0x100,&unk_df014,unaff_EDX,unaff_ECX,unaff_EBX);
  fade_palette(1,&unk_df014,0x10);
  sub_2f5ee();
  return CONCAT44(unaff_EDX,2);
}


// ================================================================================================
// sub_1a9ac @ 0x1a9ac [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 __watcall sub_1a9ac(undefined4 param_1,undefined4 unaff_EDX)

{
  int iVar1;
  
  __CHK(0x20);
  getpalette(0,0x100,&unk_df014);
  if ((byte_d2430 != '\0') && (dword_c721d != 0)) {
    sound_fade(dword_d2431,3,100);
  }
  fade_palette(1,&unk_df014,0x10);
  if ((byte_d2430 != '\0') && (dword_c721d != 0)) {
    do {
      iVar1 = sound_channel_status(ram0x000d242c >> 0x18,3);
    } while (iVar1 == 0);
    releasememblock(dword_c721d);
    dword_c721d = 0;
  }
  sub_479e9();
  boxscore_screen(2,1,_dword_d8c84,0);
  return CONCAT44(unaff_EDX,2);
}


// ================================================================================================
// sub_1aa6d @ 0x1aa6d [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 __watcall
sub_1aa6d(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  __CHK(0x1c);
  getpalette(0,0x100,&unk_df014,unaff_EDX,unaff_ECX,unaff_EBX);
  fade_palette(1,&unk_df014,0x10);
  sub_479e9();
  boxscore_screen(1,1,_dword_d8c84,0);
  return CONCAT44(unaff_EDX,2);
}


// ================================================================================================
// sub_1aac4 @ 0x1aac4 [__watcall]
// ================================================================================================

undefined8 __watcall
sub_1aac4(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  __CHK(0x1c);
  getpalette(0,0x100,&unk_df014,unaff_EDX,unaff_ECX,unaff_EBX);
  fade_palette(1,&unk_df014);
  sub_479e9();
  boxscore_screen(4,0,0,0);
  return CONCAT44(unaff_EDX,2);
}


// ================================================================================================
// sub_1ab0b @ 0x1ab0b [__watcall]
// ================================================================================================

longlong __watcall sub_1ab0b(undefined4 param_1,uint unaff_EDX)

{
  __CHK(8);
  sub_672f9(0,0);
  *off_cee5f = 1;
  *off_cee7f = 2;
  *off_cee9f = 2;
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// sub_1ab39 @ 0x1ab39 [__watcall]
// ================================================================================================

longlong __watcall sub_1ab39(undefined4 param_1,uint unaff_EDX)

{
  __CHK(8);
  sub_672f9(0,1);
  *off_cee5f = 2;
  *off_cee7f = 1;
  *off_cee9f = 2;
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// sub_1ab62 @ 0x1ab62 [__watcall]
// ================================================================================================

longlong __watcall sub_1ab62(undefined4 param_1,uint unaff_EDX)

{
  __CHK(8);
  sub_672f9(0,0xffffffff);
  *off_cee5f = 2;
  *off_cee7f = 2;
  *off_cee9f = 1;
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// sub_1ab95 @ 0x1ab95 [__watcall]
// ================================================================================================

longlong __watcall sub_1ab95(undefined4 param_1,uint unaff_EDX)

{
  __CHK(8);
  sub_672f9(1,0);
  *off_ceebf = 1;
  *off_ceedf = 2;
  *off_ceeff = 2;
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// sub_1abc8 @ 0x1abc8 [__watcall]
// ================================================================================================

longlong __watcall sub_1abc8(undefined4 param_1,uint unaff_EDX)

{
  __CHK(8);
  sub_672f9(1);
  *off_ceebf = 2;
  *off_ceedf = 1;
  *off_ceeff = 2;
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// sub_1abf1 @ 0x1abf1 [__watcall]
// ================================================================================================

longlong __watcall sub_1abf1(undefined4 param_1,uint unaff_EDX)

{
  __CHK(8);
  sub_672f9(1,0xffffffff);
  *off_ceebf = 2;
  *off_ceedf = 2;
  *off_ceeff = 1;
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// sub_1ac25 @ 0x1ac25 [__watcall]
// ================================================================================================

void __watcall sub_1ac25(void)

{
  undefined4 *puVar1;
  
  __CHK(0x1c);
  puVar1 = (undefined4 *)sub_8ccc4();
  if (puVar1 != (undefined4 *)0x0) {
    *puVar1 = 0;
    puVar1[1] = 0;
    puVar1[2] = 0;
    puVar1[3] = 0;
    puVar1[4] = 0;
    puVar1[5] = 0;
    puVar1[6] = 0;
    puVar1[7] = 0;
    puVar1[8] = 0;
    puVar1[9] = 0;
    puVar1[10] = 0;
  }
  return;
}


// ================================================================================================
// sub_1ac9a @ 0x1ac9a [__watcall]
// ================================================================================================

void __watcall sub_1ac9a(int param_1)

{
  __CHK(0x1c);
  if (*(int *)(param_1 + 0x1c) != 0) {
    freemem(*(int *)(param_1 + 0x1c));
  }
  if (*(int *)(param_1 + 0x20) != 0) {
    sub_9132c(*(int *)(param_1 + 0x20));
  }
  if (*(int *)(param_1 + 0x24) != 0) {
    sub_9132c(*(int *)(param_1 + 0x24));
  }
  if (*(int *)(param_1 + 0x28) != 0) {
    sub_9132c(*(int *)(param_1 + 0x28));
  }
  return;
}


// ================================================================================================
// sub_1acf1 @ 0x1acf1 [__watcall]
// ================================================================================================

void __watcall sub_1acf1(int param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  undefined4 extraout_EDX;
  
  __CHK(0x14);
  if (param_1 != 0) {
    sub_1ac9a(param_1,param_1,unaff_EBX,unaff_ECX,unaff_EDX,unaff_ECX,unaff_EBX);
    freemem(extraout_EDX);
  }
  return;
}


// ================================================================================================
// sub_1ad16 @ 0x1ad16 [__watcall]
// ================================================================================================

void __watcall sub_1ad16(uint *param_1,int unaff_EDX)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  byte *pbVar5;
  
  __CHK(0x28);
  sub_1ac9a();
  *param_1 = (uint)*(byte *)(unaff_EDX + 10);
  *param_1 = *param_1 + (uint)*(byte *)(unaff_EDX + 0xb) * 0x100;
  param_1[1] = (uint)*(byte *)(unaff_EDX + 0xc);
  param_1[1] = param_1[1] + (uint)*(byte *)(unaff_EDX + 0xd) * 0x100;
  param_1[2] = (uint)*(byte *)(unaff_EDX + 0xe);
  param_1[2] = param_1[2] + (uint)*(byte *)(unaff_EDX + 0xf) * 0x100;
  param_1[4] = (uint)*(byte *)(unaff_EDX + 0x10);
  param_1[4] = param_1[4] + (uint)*(byte *)(unaff_EDX + 0x11) * 0x100;
  param_1[3] = (uint)*(byte *)(unaff_EDX + 0x12);
  param_1[3] = param_1[3] + (uint)*(byte *)(unaff_EDX + 0x13) * 0x100;
  param_1[5] = (uint)*(byte *)(unaff_EDX + 0x14);
  param_1[5] = param_1[5] + (uint)*(byte *)(unaff_EDX + 0x15) * 0x100;
  param_1[6] = (uint)*(byte *)(unaff_EDX + 0x16);
  pbVar5 = (byte *)(unaff_EDX + 0x18);
  uVar4 = param_1[6] + (uint)*(byte *)(unaff_EDX + 0x17) * 0x100;
  param_1[6] = uVar4;
  iVar2 = uVar4 * 3;
  uVar4 = allocmem(aCmvPalette,iVar2,0);
  param_1[7] = uVar4;
  for (iVar3 = 0; iVar3 < iVar2; iVar3 = iVar3 + 1) {
    bVar1 = *pbVar5;
    pbVar5 = pbVar5 + 1;
    *(char *)(param_1[7] + iVar3) = (char)((int)(uint)bVar1 >> 2);
  }
  uVar4 = windowdefp(param_1[1],param_1[2],0);
  param_1[8] = uVar4;
  uVar4 = windowdefp(param_1[1],param_1[2],0);
  param_1[9] = uVar4;
  uVar4 = windowdefp(param_1[1],param_1[2],0);
  param_1[10] = uVar4;
  iVar2 = *(int *)(param_1[8] + 0x20);
  uVar4 = 0;
  do {
    param_1[uVar4 + 0xb] = ((uVar4 & 0xf) - 7) + (((int)uVar4 >> 4 & 0xfU) - 7) * iVar2;
    uVar4 = uVar4 + 1;
  } while ((int)uVar4 < 0x100);
  return;
}


// ================================================================================================
// sub_1ae6b @ 0x1ae6b [__watcall]
// ================================================================================================

void __watcall sub_1ae6b(int param_1,byte *unaff_EDX,byte *unaff_EBX)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  byte *pbVar11;
  undefined4 *puVar12;
  undefined4 *puVar13;
  undefined4 *puVar14;
  int local_3c;
  int local_1c;
  
  __CHK(0x4c);
  iVar1 = *(int *)(param_1 + 0x20);
  iVar2 = *(int *)(iVar1 + 0x2c);
  iVar3 = *(int *)(*(int *)(param_1 + 0x24) + 0x2c);
  iVar4 = *(int *)(*(int *)(param_1 + 0x28) + 0x2c);
  iVar5 = *(int *)(iVar1 + 0x20);
  iVar6 = *(int *)(param_1 + 4);
  iVar7 = iVar6 * 2;
  iVar8 = iVar6 * 3;
  puVar9 = (undefined4 *)(iVar2 + **(int **)(iVar1 + 0x28));
  for (local_3c = *(int *)(param_1 + 8); local_1c = iVar6, 0 < local_3c; local_3c = local_3c + -4) {
    for (; 0 < local_1c; local_1c = local_1c + -4) {
      puVar12 = (undefined4 *)(iVar8 + (int)puVar9);
      puVar14 = (undefined4 *)(iVar7 + (int)puVar9);
      puVar13 = (undefined4 *)(iVar6 + (int)puVar9);
      if (*unaff_EDX == 0xff) {
        pbVar11 = unaff_EBX + 1;
        if (*unaff_EBX == 0xff) {
          *puVar9 = *(undefined4 *)pbVar11;
          *puVar13 = *(undefined4 *)(unaff_EBX + 5);
          *puVar14 = *(undefined4 *)(unaff_EBX + 9);
          *puVar12 = *(undefined4 *)(unaff_EBX + 0xd);
          pbVar11 = unaff_EBX + 0x11;
        }
        else {
          puVar10 = (undefined4 *)
                    ((int)puVar9 + *(int *)((uint)*unaff_EBX * 4 + param_1 + 0x2c) + (iVar4 - iVar2)
                    );
          *puVar9 = *puVar10;
          *puVar13 = *(undefined4 *)((int)puVar10 + iVar6);
          *puVar14 = *(undefined4 *)((int)puVar10 + iVar7);
          *puVar12 = *(undefined4 *)((int)puVar10 + iVar8);
        }
      }
      else {
        puVar10 = (undefined4 *)
                  ((int)puVar9 + *(int *)(param_1 + 0x2c + (uint)*unaff_EDX * 4) + (iVar3 - iVar2));
        *puVar9 = *puVar10;
        *puVar13 = *(undefined4 *)((int)puVar10 + iVar6);
        *puVar14 = *(undefined4 *)((int)puVar10 + iVar7);
        *puVar12 = *(undefined4 *)((int)puVar10 + iVar8);
        pbVar11 = unaff_EBX;
      }
      puVar9 = puVar9 + 1;
      unaff_EDX = unaff_EDX + 1;
      unaff_EBX = pbVar11;
    }
    puVar9 = (undefined4 *)((int)puVar9 + iVar5 * 3);
  }
  return;
}


// ================================================================================================
// sub_1b002 @ 0x1b002 [__watcall]
// ================================================================================================

undefined4 __watcall sub_1b002(int param_1,int unaff_EDX)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  __CHK(0x24);
  iVar4 = *(int *)(param_1 + 4);
  iVar2 = *(int *)(param_1 + 8);
  if (unaff_EDX == 0) {
    iVar4 = *(int *)(param_1 + 0x20);
  }
  else {
    iVar3 = *(int *)(param_1 + 0x28);
    *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x24);
    *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_1 + 0x20);
    *(int *)(param_1 + 0x20) = iVar3;
    iVar1 = unaff_EDX + 10;
    if (*(short *)(unaff_EDX + 8) == 0) {
      sub_b3abc(iVar1,*(int *)(iVar3 + 0x2c) + 0x10,iVar4 * iVar2);
    }
    else {
      sub_1ae6b(param_1,iVar1,
                iVar1 + ((int)((iVar2 + (iVar2 >> 0x1f) * -4) - (uint)((iVar2 >> 0x1f) << 1 < 0)) >>
                        2) * ((int)((iVar4 + (iVar4 >> 0x1f) * -4) -
                                   (uint)((iVar4 >> 0x1f) << 1 < 0)) >> 2));
    }
    iVar4 = *(int *)(param_1 + 0x20);
  }
  return *(undefined4 *)(iVar4 + 0x2c);
}


// ================================================================================================
// sub_1b092 @ 0x1b092 [__watcall]
// ================================================================================================

undefined4 __watcall sub_1b092(undefined4 *param_1)

{
  __CHK(4);
  return *param_1;
}


// ================================================================================================
// sub_1b09f @ 0x1b09f [__watcall]
// ================================================================================================

undefined4 __watcall sub_1b09f(int param_1)

{
  __CHK(4);
  return *(undefined4 *)(param_1 + 4);
}


// ================================================================================================
// sub_1b0ad @ 0x1b0ad [__watcall]
// ================================================================================================

undefined4 __watcall sub_1b0ad(int param_1)

{
  __CHK(4);
  return *(undefined4 *)(param_1 + 8);
}


// ================================================================================================
// sub_1b0bb @ 0x1b0bb [__watcall]
// ================================================================================================

undefined4 __watcall sub_1b0bb(int param_1)

{
  __CHK(4);
  return *(undefined4 *)(param_1 + 0xc);
}


// ================================================================================================
// sub_1b0c9 @ 0x1b0c9 [__watcall]
// ================================================================================================

undefined4 __watcall sub_1b0c9(int param_1)

{
  __CHK(4);
  return *(undefined4 *)(param_1 + 0x14);
}


// ================================================================================================
// sub_1b0d7 @ 0x1b0d7 [__watcall]
// ================================================================================================

undefined4 __watcall sub_1b0d7(int param_1)

{
  __CHK(4);
  return *(undefined4 *)(param_1 + 0x18);
}


// ================================================================================================
// sub_1b0e5 @ 0x1b0e5 [__watcall]
// ================================================================================================

undefined4 __watcall sub_1b0e5(int param_1)

{
  __CHK(4);
  return *(undefined4 *)(param_1 + 0x1c);
}


// ================================================================================================
// sub_1b0f3 @ 0x1b0f3 [__cdecl]
// ================================================================================================

undefined4 * sub_1b0f3(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  
  __CHK(0x14);
  puVar1 = (undefined4 *)allocmem(aCDSTREAM,param_1 + 0x54,param_3);
  puVar1[8] = param_1;
  *puVar1 = puVar1 + 0x15;
  puVar1[1] = param_1 + (int)(puVar1 + 0x15);
  uVar2 = *puVar1;
  puVar1[5] = uVar2;
  puVar1[4] = uVar2;
  puVar1[2] = uVar2;
  puVar1[3] = uVar2;
  puVar1[9] = param_2;
  puVar1[6] = 0;
  dword_dc8a0 = puVar1;
  dword_dc8c8 = puVar1;
  puVar1[7] = 7;
  uVar2 = sub_91fa4(param_2,dword_c66b0);
  puVar1[0x14] = uVar2;
  puVar1[0x13] = 0;
  addtimer(sub_1b818);
  return puVar1;
}


// ================================================================================================
// sub_1b18b @ 0x1b18b [__cdecl]
// ================================================================================================

void sub_1b18b(int param_1)

{
  __CHK(0xc);
  removetimer(sub_1b818);
  if (*(int *)(param_1 + 0x18) != 0) {
    closehandle(*(int *)(param_1 + 0x18));
  }
  freemem(param_1);
  return;
}


// ================================================================================================
// sub_1b1c2 @ 0x1b1c2 [__cdecl]
// ================================================================================================

void sub_1b1c2(int param_1,undefined4 param_2)

{
  __CHK(4);
  *(undefined4 *)(param_1 + 0x48) = param_2;
  *(undefined4 *)(param_1 + 0x1c) = 1;
  return;
}


// ================================================================================================
// sub_1b1df @ 0x1b1df [__watcall]
// ================================================================================================

void __watcall sub_1b1df(void)

{
  int in_stack_00000004;
  int in_stack_00000008;
  
  __CHK(4);
  *(int *)(in_stack_00000004 + 0x44) = *(int *)(in_stack_00000004 + 0x34) + in_stack_00000008;
  *(undefined4 *)(in_stack_00000004 + 0x1c) = 2;
  return;
}


// ================================================================================================
// sub_1b201 @ 0x1b201 [__watcall]
// ================================================================================================

void __watcall sub_1b201(void)

{
  int iVar1;
  int *piVar2;
  int in_stack_00000004;
  int in_stack_00000008;
  undefined4 in_stack_0000000c;
  
  __CHK(0x10);
  if ((in_stack_00000004 < 0) || (9 < in_stack_00000004)) {
    fatalerror(aIllegalSecondaryStreamNu);
  }
  piVar2 = (int *)allocmem(aSECCDSTREAM,in_stack_00000008 + 0x54,in_stack_0000000c);
  piVar2[8] = in_stack_00000008;
  *piVar2 = (int)(piVar2 + 0x15);
  piVar2[1] = in_stack_00000008 + (int)(piVar2 + 0x15);
  iVar1 = *piVar2;
  piVar2[5] = iVar1;
  piVar2[4] = iVar1;
  piVar2[2] = iVar1;
  piVar2[3] = iVar1;
  piVar2[9] = 0;
  piVar2[0x10] = 0;
  piVar2[0xe] = 1;
  (&dword_dc8a0)[in_stack_00000004] = piVar2;
  return;
}


// ================================================================================================
// sub_1b2a7 @ 0x1b2a7 [__watcall]
// ================================================================================================

void __watcall sub_1b2a7(void)

{
  int *piVar1;
  int iVar2;
  undefined8 uVar3;
  
  __CHK(0x20);
  do {
    if (0 < dword_dc8a0[0x13]) {
      return;
    }
    switch(dword_dc8a0[7]) {
    case 1:
      if (dword_dc8a0[6] != 0) {
        closehandle(dword_dc8a0[6]);
      }
      sub_b3b5a(dword_dc8a0[0x12],dword_dc8a0 + 6,dword_dc8a0 + 0xd,dword_dc8a0 + 0xf);
      dword_dc8a0[0x11] = dword_dc8a0[0xd];
      dword_dc8a0[0xe] = dword_dc8a0[0xd] + dword_dc8a0[0xf];
      dword_dc8a0[7] = 2;
switchD_0001b2cd_caseD_2:
      uVar3 = sub_1b82b(dword_dc8a0);
      if ((int)uVar3 < *(int *)((int)((ulonglong)uVar3 >> 0x20) + 0x24)) {
        return;
      }
      dword_dc8a0[7] = 3;
      dword_dc8a0[2] = dword_dc8a0[3];
      dword_dc8a0[0x10] = dword_dc8a0[0x11];
      seekhandle(dword_dc8a0[6],dword_dc8a0[0x10]);
      dword_dc8a0[0xc] = 0;
      iVar2 = sub_91fa4(dword_dc8a0[9],dword_c66b0);
      dword_dc8a0[0x13] = iVar2;
      return;
    case 2:
      goto switchD_0001b2cd_caseD_2;
    case 3:
      if ((uint)dword_dc8a0[0xc] < 8) {
        uVar3 = sub_1b82b(dword_dc8a0);
        if ((int)uVar3 < *(int *)((int)((ulonglong)uVar3 >> 0x20) + 0x24)) {
          return;
        }
        iVar2 = dword_dc8a0[0x13];
        sub_b3c74(dword_dc8a0[6],dword_dc8a0[2],dword_dc8a0[9]);
        dword_dc8a0[0x13] = iVar2;
        iVar2 = sub_91fa4(dword_dc8a0[9],dword_c66b0);
        dword_dc8a0[0x13] = iVar2;
        dword_dc8a0[2] = dword_dc8a0[2] + dword_dc8a0[9];
        dword_dc8a0[0x10] = dword_dc8a0[0x10] + dword_dc8a0[9];
        dword_dc8a0[0xc] = dword_dc8a0[0xc] + dword_dc8a0[9];
      }
      dword_dc8a0[0xb] = *(int *)(dword_dc8a0[3] + 4);
      dword_dc8a0[10] = dword_dc8a0[0xb] - dword_dc8a0[0xc];
      iVar2 = *(char *)dword_dc8a0[3] + -0x30;
      dword_dc8c8 = dword_dc8a0;
      if ((0 < iVar2) && (iVar2 < 9)) {
        dword_dc8c8 = (&dword_dc8a0)[iVar2];
      }
      if (dword_dc8c8 == (int *)0x0) {
        dword_dc8c8 = dword_dc8a0;
      }
      if (((uint)dword_dc8a0[0xb] < 8) || (dword_dc8c8[8] < dword_dc8a0[0xb])) {
        fatalerror(aIllegalChunkSizeDBuffers,dword_dc8a0[0xb],dword_dc8c8[8]);
      }
    case 4:
      if (dword_dc8c8 != dword_dc8a0) {
        dword_dc8a0[7] = 4;
        uVar3 = sub_1b82b(dword_dc8c8,dword_dc8a0[9] + 8);
        if ((uint)uVar3 < (uint)((ulonglong)uVar3 >> 0x20)) {
          return;
        }
        uVar3 = sub_1b871(dword_dc8c8,dword_dc8a0[0xb] + dword_dc8a0[9]);
        if ((uint)uVar3 < (int)((ulonglong)uVar3 >> 0x20) + 8U) {
          *(undefined4 *)dword_dc8c8[3] = 0xffffffff;
          iVar2 = *dword_dc8c8;
          dword_dc8c8[3] = iVar2;
          dword_dc8c8[2] = iVar2;
          break;
        }
        if (dword_dc8a0[10] < 0) {
          sub_b3abc(dword_dc8a0[3],dword_dc8c8[3],dword_dc8a0[0xb]);
          dword_dc8c8[2] = dword_dc8c8[3] + dword_dc8a0[0xb];
          dword_dc8a0[0xc] = -dword_dc8a0[10];
          sub_b3abc(dword_dc8a0[0xb] + dword_dc8a0[3],dword_dc8a0[3],dword_dc8a0[0xc]);
          dword_dc8a0[2] = dword_dc8a0[2] - dword_dc8a0[0xb];
        }
        else {
          sub_b3abc(dword_dc8a0[3],dword_dc8c8[3],dword_dc8a0[0xc]);
          dword_dc8c8[2] = dword_dc8c8[3] + dword_dc8a0[0xc];
          dword_dc8a0[2] = dword_dc8a0[3];
          dword_dc8a0[0xc] = 0;
        }
      }
switchD_0001b2cd_caseD_5:
      if ((0 < dword_dc8a0[10]) &&
         (uVar3 = sub_1b871(dword_dc8c8,dword_dc8a0[10] + dword_dc8a0[9]),
         (uint)uVar3 < (int)((ulonglong)uVar3 >> 0x20) + 8U)) {
        dword_dc8a0[7] = 5;
        uVar3 = sub_1b88a(dword_dc8c8,dword_dc8a0);
        if ((int)uVar3 < *(int *)((int)((ulonglong)uVar3 >> 0x20) + 0x30)) {
          return;
        }
        sub_b3abc(dword_dc8c8[3],*dword_dc8c8,dword_dc8a0[0xc]);
        *(undefined4 *)dword_dc8c8[3] = 0xffffffff;
        dword_dc8c8[2] = *dword_dc8c8 + dword_dc8a0[0xc];
        dword_dc8c8[3] = *dword_dc8c8;
      }
switchD_0001b2cd_caseD_6:
      dword_dc8a0[7] = 6;
      if (0 < dword_dc8a0[10]) {
        uVar3 = sub_1b82b(dword_dc8c8);
        if ((int)uVar3 < *(int *)((int)((ulonglong)uVar3 >> 0x20) + 0x24)) {
          return;
        }
        iVar2 = dword_dc8a0[0x13];
        sub_b3c74(dword_dc8a0[6],dword_dc8c8[2],dword_dc8a0[9]);
        dword_dc8a0[0x13] = iVar2;
        piVar1 = dword_dc8a0;
        iVar2 = sub_91fa4(dword_dc8a0[9],dword_c66b0);
        piVar1[0x13] = piVar1[0x13] + iVar2;
        dword_dc8a0[0x10] = dword_dc8a0[0x10] + dword_dc8a0[9];
        dword_dc8c8[2] = dword_dc8c8[2] + dword_dc8a0[9];
        dword_dc8a0[10] = dword_dc8a0[10] - dword_dc8a0[9];
        return;
      }
      dword_dc8c8[3] = dword_dc8c8[3] + dword_dc8a0[0xb];
      if (dword_dc8c8 == dword_dc8a0) {
        dword_dc8a0[0xc] = dword_dc8c8[2] - dword_dc8c8[3];
      }
      else if (dword_dc8a0[0xc] == 0) {
        dword_dc8a0[0xc] = dword_dc8c8[2] - dword_dc8c8[3];
        sub_b3abc(dword_dc8c8[3],dword_dc8a0[3],dword_dc8a0[0xc]);
        dword_dc8c8[2] = dword_dc8c8[3];
        dword_dc8a0[2] = dword_dc8a0[3] + dword_dc8a0[0xc];
      }
switchD_0001b2cd_caseD_9:
      if (dword_dc8a0[0x10] - dword_dc8a0[0xc] < dword_dc8a0[0xe]) {
        dword_dc8a0[7] = 3;
      }
      else {
        dword_dc8a0[7] = 9;
        uVar3 = sub_1b82b(dword_dc8a0);
        if ((uint)((int)uVar3 + *(int *)((int)((ulonglong)uVar3 >> 0x20) + 0x30)) < 8) {
          return;
        }
        *(undefined4 *)dword_dc8a0[3] = 0xfffffffd;
        *(undefined4 *)(dword_dc8a0[3] + 4) = 8;
        dword_dc8a0[3] = dword_dc8a0[3] + 8;
        dword_dc8a0[2] = dword_dc8a0[3];
        dword_dc8a0[7] = 7;
      }
      break;
    case 5:
      goto switchD_0001b2cd_caseD_5;
    case 6:
      goto switchD_0001b2cd_caseD_6;
    case 7:
      dword_dc8a0[0x13] = 0;
      return;
    case 9:
      goto switchD_0001b2cd_caseD_9;
    }
  } while( true );
}


// ================================================================================================
// sub_1b818 @ 0x1b818 [__watcall]
// ================================================================================================

void __watcall sub_1b818(void)

{
  __CHK(4);
  *(int *)(dword_dc8a0 + 0x4c) = *(int *)(dword_dc8a0 + 0x4c) + -1;
  return;
}


// ================================================================================================
// sub_1b82b @ 0x1b82b [__watcall]
// ================================================================================================

undefined8 __watcall sub_1b82b(int *param_1,undefined4 unaff_EDX)

{
  int *piVar1;
  uint uVar2;
  int iVar3;
  
  __CHK(0x14);
  piVar1 = (int *)param_1[5];
  if (piVar1 != (int *)param_1[4]) {
    if (*piVar1 == -2) {
      iVar3 = (int)piVar1 + piVar1[1];
    }
    else {
      if (*piVar1 != -1) goto LAB_0001b859;
      iVar3 = *param_1;
    }
    param_1[5] = iVar3;
  }
LAB_0001b859:
  uVar2 = param_1[5];
  if (uVar2 <= (uint)param_1[2]) {
    uVar2 = param_1[1];
  }
  return CONCAT44(unaff_EDX,uVar2 - param_1[2]);
}


// ================================================================================================
// sub_1b871 @ 0x1b871 [__watcall]
// ================================================================================================

undefined8 __watcall sub_1b871(int param_1,undefined4 unaff_EDX)

{
  __CHK(0xc);
  return CONCAT44(unaff_EDX,*(int *)(param_1 + 4) - *(int *)(param_1 + 8));
}


// ================================================================================================
// sub_1b88a @ 0x1b88a [__watcall]
// ================================================================================================

longlong __watcall sub_1b88a(int *param_1,uint unaff_EDX)

{
  __CHK(0xc);
  if ((uint)param_1[5] <= (uint)param_1[2]) {
    return CONCAT44(unaff_EDX,param_1[5] - *param_1);
  }
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// sub_1b8ac @ 0x1b8ac [__watcall]
// ================================================================================================

int * __watcall sub_1b8ac(void)

{
  int iVar1;
  uint uVar2;
  int *piVar3;
  uint uVar4;
  undefined4 *in_stack_00000004;
  
  __CHK(0xc);
  sub_1b2a7();
  piVar3 = (int *)in_stack_00000004[4];
  if ((int *)in_stack_00000004[3] == piVar3) {
    return (int *)((uint)in_stack_00000004[3] ^ (uint)piVar3);
  }
  if (*piVar3 == -1) {
    in_stack_00000004[4] = *in_stack_00000004;
    if (in_stack_00000004[3] == in_stack_00000004[4]) {
      return (int *)(in_stack_00000004[3] ^ in_stack_00000004[4]);
    }
  }
  uVar2 = in_stack_00000004[4];
  uVar4 = in_stack_00000004[3];
  if (uVar4 < uVar2) {
    uVar4 = in_stack_00000004[1];
  }
  if (*(int *)(uVar2 + 4) <= (int)(uVar4 - uVar2)) {
    piVar3 = (int *)in_stack_00000004[4];
    iVar1 = (int)piVar3 + *(int *)(uVar2 + 4);
    in_stack_00000004[4] = iVar1;
    if (*piVar3 == -3) {
      if (piVar3 == (int *)in_stack_00000004[5]) {
        in_stack_00000004[5] = iVar1;
      }
      else {
        *piVar3 = -2;
      }
      piVar3 = (int *)0xffffffff;
    }
    return piVar3;
  }
  return (int *)0x0;
}


// ================================================================================================
// sub_1b92e @ 0x1b92e [__cdecl]
// ================================================================================================

void sub_1b92e(undefined4 *param_1,int *param_2)

{
  __CHK(8);
  *param_2 = -2;
  if (param_2 == (int *)param_1[5]) {
    while (param_1[5] != param_1[3]) {
      if (*param_2 == -2) {
        param_1[5] = param_1[5] + param_2[1];
      }
      else {
        if (*param_2 != -1) {
          return;
        }
        if (param_1[5] == param_1[4]) {
          param_1[4] = *param_1;
        }
        param_1[5] = *param_1;
      }
      if (param_2[1] == 0) {
        return;
      }
      param_2 = (int *)param_1[5];
    }
  }
  return;
}


// ================================================================================================
// sub_1b982 @ 0x1b982 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall sub_1b982(void)

{
  __CHK(0x20);
  sub_59748();
  sub_5dd9e();
  if ((dword_cbeca >> 0x10 != -1) && (dword_e0244 != 0)) {
    freemem(dword_e0244);
    dword_e0244 = 0;
  }
  sub_1bab1();
  if (dword_d8c68 != 0) {
    freemem(dword_d8c68);
    dword_d8c68 = 0;
  }
  if (dword_d8c80 != 0) {
    freemem(dword_d8c80);
    dword_d8c80 = 0;
  }
  if (dword_dc2f0 != 0) {
    freemem(dword_dc2f0);
    dword_dc2f0 = 0;
  }
  if (dword_ed700 != 0) {
    freemem(dword_ed700);
    dword_ed700 = 0;
  }
  sub_7dec8();
  if (dword_dc338 != 0) {
    freemem(dword_dc338);
    dword_dc338 = 0;
  }
  _dword_c4d0c = 0;
  flush_key_events();
  setfont(dword_dc230);
  dword_c7290 = 0x50;
  sub_33727();
  return;
}


// ================================================================================================
// sub_1ba85 @ 0x1ba85 [__watcall]
// ================================================================================================

void __watcall
sub_1ba85(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  __CHK(0x14);
  if (dword_cc0e0 != 0) {
    freemem(dword_cc0e0,unaff_EDX,unaff_ECX,unaff_EBX);
  }
  dword_cc0e0 = 0;
  return;
}


// ================================================================================================
// sub_1bab1 @ 0x1bab1 [__watcall]
// ================================================================================================

void __watcall sub_1bab1(void)

{
  int iVar1;
  
  __CHK(0x1c);
  sub_1ba85();
  for (iVar1 = 0x16; -1 < iVar1; iVar1 = iVar1 + -1) {
    if ((&unk_d9980)[iVar1] != 0) {
      freemem((&unk_d9980)[iVar1]);
      (&unk_d9980)[iVar1] = 0;
    }
  }
  return;
}


// ================================================================================================
// sub_1baf3 @ 0x1baf3 [__watcall]
// ================================================================================================

undefined8 __watcall sub_1baf3(int param_1,undefined4 unaff_EDX)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  __CHK(0x20);
  iVar1 = sub_8dab8();
  if (iVar1 < param_1) {
    if (dword_c73d4 != 0) {
      freemem(dword_c73d4);
      dword_c73d4 = 0;
    }
    iVar1 = sub_8dab8();
    if (iVar1 < param_1) {
      sub_33727();
      iVar1 = sub_8dab8();
      if (iVar1 < param_1) {
        if ((dword_cbeca >> 0x10 != -1) && (dword_e0244 != 0)) {
          freemem(dword_e0244);
          dword_e0244 = 0;
        }
        iVar1 = sub_8dab8();
        if (iVar1 < param_1) {
          sub_1ba85();
          for (iVar1 = 0x16; -1 < iVar1; iVar1 = iVar1 + -1) {
            iVar3 = sub_8dab8();
            if (param_1 <= iVar3) goto LAB_0001bb0e;
            if ((&unk_d9980)[iVar1] != 0) {
              freemem((&unk_d9980)[iVar1]);
              (&unk_d9980)[iVar1] = 0;
            }
          }
          iVar1 = sub_8dab8();
          if (iVar1 < param_1) {
            uVar2 = 0;
            goto LAB_0001ba7e;
          }
        }
      }
    }
  }
LAB_0001bb0e:
  uVar2 = 1;
LAB_0001ba7e:
  return CONCAT44(unaff_EDX,uVar2);
}


// ================================================================================================
// sub_1bbcc @ 0x1bbcc [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall sub_1bbcc(uint param_1)

{
  int iVar1;
  __off_t _Var2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  byte bVar5;
  char local_48 [32];
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  int iStack_18;
  
  bVar5 = 0;
  __CHK(0x88);
  sprintf(local_48,&byte_dd750,aTeams);
  iVar1 = _dos_findfirst(local_48,0);
  if (iVar1 != 0) {
    fatalerror(&a1);
  }
  iVar1 = file_open_read(local_48,&iStack_18);
  if (iVar1 != 0) {
    fatalerror(&a2_c0a20);
  }
  _Var2 = lseek(iStack_18,0,0);
  if (_Var2 != 0) {
    fatalerror(&a3);
  }
  _Var2 = lseek(iStack_18,dword_c90c8._2_2_ * 0x2e8,0);
  if (_Var2 < 0) {
    fatalerror(&a4);
  }
  iVar1 = file_read(iStack_18,&unk_dbc30,0xffffffff,0x2e8);
  if (iVar1 != 0) {
    fatalerror(&a5);
  }
  file_close(&iStack_18);
  sprintf(local_48,&byte_dd710,aTeams);
  iVar1 = _dos_findfirst(local_48,0);
  if (iVar1 != 0) {
    fatalerror(&a1);
  }
  iVar1 = file_open_read(local_48,&iStack_18);
  if (iVar1 != 0) {
    fatalerror(&a2_c0a20);
  }
  _Var2 = lseek(iStack_18,0,0);
  if (_Var2 != 0) {
    fatalerror(&a3);
  }
  _Var2 = lseek(iStack_18,_dword_c90cc * 0x2e8,0);
  if (_Var2 < 0) {
    fatalerror(&a7);
  }
  iVar1 = file_read(iStack_18,&unk_dbf18,0xffffffff,0x2e8);
  if (iVar1 != 0) {
    fatalerror(&a8);
  }
  file_close(&iStack_18);
  sub_1c26c(param_1,&iStack_18,&local_1c,&local_20,&local_24,&byte_dd750,&local_28);
  sub_1c3f6(param_1,iStack_18,local_1c,local_20,local_24,local_28,0);
  file_close(&iStack_18);
  file_close(&local_1c);
  file_close(&local_20);
  if ((param_1 & 6) == 0) {
    file_close(&local_24);
  }
  sub_1c26c(param_1,&iStack_18,&local_1c,&local_20,&local_24,&byte_dd710,&local_28);
  sub_1c3f6(param_1,iStack_18,local_1c,local_20,local_24,local_28,1);
  file_close(&iStack_18);
  file_close(&local_1c);
  file_close(&local_20);
  if ((param_1 & 6) == 0) {
    file_close(&local_24);
  }
  if ((param_1 == 0) || (param_1 == 2)) {
    puVar3 = &unk_dbcec;
    puVar4 = &unk_dc200;
    for (iVar1 = 0xc; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar4 = *puVar3;
      puVar3 = puVar3 + (uint)bVar5 * -2 + 1;
      puVar4 = puVar4 + (uint)bVar5 * -2 + 1;
    }
    puVar3 = &unk_dbfd4;
    puVar4 = (undefined4 *)&unk_dabf0;
    for (iVar1 = 0xc; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar4 = *puVar3;
      puVar3 = puVar3 + (uint)bVar5 * -2 + 1;
      puVar4 = puVar4 + (uint)bVar5 * -2 + 1;
    }
  }
  iVar1 = 0;
  do {
    if ((&unk_dc228)[iVar1] != 100) {
      (&unk_db3a8)[(uint)(byte)(&unk_dc228)[iVar1] * 0x27] = 2;
    }
    if ((&unk_dac18)[iVar1] != 'd') {
      (&unk_db7ec)[(uint)(byte)(&unk_dac18)[iVar1] * 0x27] = 2;
    }
    iVar1 = iVar1 + 1;
  } while (iVar1 < 8);
  return;
}


// ================================================================================================
// sub_1befd @ 0x1befd [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall sub_1befd(undefined param_1,undefined unaff_DL)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  byte bVar5;
  undefined4 uStack_14;
  
  bVar5 = 0;
  __CHK(0x1c);
  _dword_d8c84 = 0xffffffff;
  byte_c5426 = dword_c90c8._2_1_;
  byte_c5427 = dword_c90cc;
  word_c5428 = 1;
  byte_c542f = 0;
  byte_c5430 = 0;
  byte_c5431 = 0;
  byte_c5432 = 0;
  byte_c5424 = param_1;
  byte_c5425 = unaff_DL;
  byte_dc267 = unaff_DL;
  byte_dc268 = param_1;
  if ((dword_c53ff._1_1_ & 2) == 0) {
    sub_15b76();
  }
  sub_1c807();
  iVar2 = sub_14566(&byte_dac20,&uStack_14);
  if (iVar2 != 0) {
    fatalerror(&aB1);
  }
  iVar2 = file_write(uStack_14,&unk_c5423,0xffffffff,0xb);
  if (iVar2 != 0) {
    fatalerror(&aB5);
  }
  iVar2 = file_write(uStack_14,&unk_c542e);
  if (iVar2 != 0) {
    fatalerror(&aB8);
  }
  file_close(&uStack_14);
  sub_1bbcc(0);
  word_db094._2_2_ = 0;
  word_db094._0_2_ = 0;
  word_db090._2_2_ = 0;
  word_db090._0_2_ = 0;
  word_db08c._2_2_ = 0;
  word_db08c._0_2_ = 0;
  word_db088 = 0;
  iVar2 = 0;
  do {
    iVar3 = 0;
    do {
      puVar1 = &word_db088 + iVar3 * 4 + iVar2 * 100;
      puVar4 = puVar1 + (uint)bVar5 * -2 + 1;
      *puVar1 = word_db088;
      *puVar4 = (&word_db08c)[(uint)bVar5 * -2];
      puVar4[(uint)bVar5 * -2 + 1] = (&word_db090)[(uint)bVar5 * -2 + (uint)bVar5 * -2];
      (puVar4 + (uint)bVar5 * -2 + 1)[(uint)bVar5 * -2 + 1] =
           (&word_db090 + (uint)bVar5 * -2 + (uint)bVar5 * -2)[(uint)bVar5 * -2 + 1];
      iVar3 = iVar3 + 1;
    } while (iVar3 < 0x19);
    iVar2 = iVar2 + 1;
  } while (iVar2 < 2);
  word_dc244 = 0;
  word_dc240 = 0;
  iVar2 = 0;
  do {
    iVar3 = 0;
    do {
      puVar1 = (undefined4 *)((int)&word_dc240 + iVar3 * 6 + iVar2 * 0x12);
      *puVar1 = word_dc240;
      *(undefined2 *)(puVar1 + (uint)bVar5 * -2 + 1) = (&word_dc244)[(uint)bVar5 * -4];
      iVar3 = iVar3 + 1;
    } while (iVar3 < 3);
    iVar2 = iVar2 + 1;
  } while (iVar2 < 2);
  return;
}


// ================================================================================================
// sub_1c0af @ 0x1c0af [__watcall]
// ================================================================================================

int __watcall
sub_1c0af(int param_1,int param_2,int param_3,int param_4,__off_t param_5,int param_6,
         undefined4 param_7,undefined4 param_8,undefined4 param_9,undefined4 param_10,
         undefined4 param_11,int param_12)

{
  __off_t _Var1;
  int iVar2;
  int local_14;
  
  __CHK(0x1c);
  _Var1 = lseek(param_1,0,0);
  if (_Var1 != 0) {
    fatalerror(&aD);
  }
  _Var1 = lseek(param_1,param_5,0);
  if (_Var1 < 0) {
    fatalerror(&aE);
  }
  iVar2 = file_read(param_1,param_6,0xffffffff,0x34);
  if (iVar2 != 0) {
    fatalerror(&aF);
  }
  _Var1 = lseek(param_2,0,0);
  if (_Var1 != 0) {
    fatalerror(&aG_c0a3b);
  }
  _Var1 = lseek(param_2,*(__off_t *)(param_6 + 0x24),0);
  if (_Var1 < 0) {
    fatalerror(&aH);
  }
  iVar2 = file_read(param_2,param_7,0xffffffff,param_8);
  if (iVar2 != 0) {
    fatalerror(&aI);
  }
  _Var1 = lseek(param_3,0,0);
  if (_Var1 != 0) {
    fatalerror(&aL_c0a41);
  }
  _Var1 = lseek(param_3,*(__off_t *)(param_6 + 0x2c),0);
  if (_Var1 < 0) {
    fatalerror(&aM);
  }
  iVar2 = file_read(param_3,param_9,0xffffffff,param_10);
  if (iVar2 != 0) {
    fatalerror(&aN);
  }
  if (param_12 == 0) {
    local_14 = param_12;
  }
  else {
    _Var1 = lseek(param_4,0,0);
    if (_Var1 != 0) {
      fatalerror(&aO);
    }
    _Var1 = lseek(param_4,*(__off_t *)(param_6 + 0x28),0);
    if (_Var1 < 0) {
      fatalerror(&aP);
    }
    iVar2 = file_read(param_4,param_11,0xffffffff,param_12);
    if (iVar2 != 0) {
      fatalerror(&aQ);
    }
  }
  return local_14;
}


// ================================================================================================
// sub_1c26c @ 0x1c26c [__watcall]
// ================================================================================================

void __watcall
sub_1c26c(uint param_1,undefined4 param_2,undefined4 unaff_EBX,undefined4 unaff_ECX,
         undefined4 param_5,char *param_6,undefined4 *param_7)

{
  int iVar1;
  undefined auStack_58 [44];
  char acStack_2c [32];
  
  __CHK(0x6c);
  sprintf(acStack_2c,param_6,&aKey);
  iVar1 = _dos_findfirst(acStack_2c,0,auStack_58);
  if (iVar1 != 0) {
    fatalerror(&a9);
  }
  iVar1 = file_open_read(acStack_2c,param_2);
  if (iVar1 != 0) {
    fatalerror(&aA_c0a53);
  }
  sprintf(acStack_2c,param_6,&aAtt);
  iVar1 = _dos_findfirst(acStack_2c,0,auStack_58);
  if (iVar1 != 0) {
    fatalerror(&aB);
  }
  iVar1 = file_open_read(acStack_2c,unaff_EBX);
  if (iVar1 != 0) {
    fatalerror(&aC);
  }
  sprintf(acStack_2c,param_6,aSeason_c0a5d);
  iVar1 = _dos_findfirst(acStack_2c,0,auStack_58);
  if (iVar1 != 0) {
    fatalerror(&aJ);
  }
  iVar1 = file_open_read(acStack_2c,unaff_ECX);
  if (iVar1 != 0) {
    fatalerror(&aK);
  }
  if ((param_1 & 6) == 0) {
    sprintf(acStack_2c,param_6,aCareer);
    iVar1 = _dos_findfirst(acStack_2c,0,auStack_58);
    if (iVar1 != 0) {
      fatalerror(&aL_c0a41);
    }
    iVar1 = file_open_read(acStack_2c,param_5);
    if (iVar1 != 0) {
      fatalerror(&aM);
    }
    *param_7 = 0x28;
  }
  else {
    *param_7 = 0;
  }
  return;
}


// ================================================================================================
// sub_1c3f6 @ 0x1c3f6 [__watcall]
// ================================================================================================

void __watcall
sub_1c3f6(uint param_1,undefined4 param_2,undefined4 unaff_EBX,undefined4 unaff_ECX,
         undefined4 param_5,undefined4 param_6,int param_7)

{
  undefined4 *puVar1;
  ushort uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined auStack_fc [46];
  byte bStack_ce;
  byte bStack_cd;
  undefined uStack_c4;
  undefined uStack_c3;
  undefined uStack_c2;
  char acStack_c1 [16];
  char acStack_b1 [33];
  undefined auStack_90 [2];
  ushort local_8e;
  ushort uStack_8c;
  ushort uStack_7c;
  ushort uStack_7a;
  byte bStack_6a;
  byte bStack_69;
  undefined local_60 [36];
  ushort local_3c;
  ushort uStack_3a;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 local_18;
  int local_14;
  int iStack_10;
  
  __CHK(0x130);
  iVar6 = 0;
  do {
    iStack_10 = iVar6 * 0x27;
    iVar7 = iStack_10 + param_7 * 0x444;
    if (*(int *)(&unk_dbc7c + iVar6 * 4 + param_7 * 0x2e8) < 0) {
      (&unk_db3a8)[iVar7] = 0;
    }
    else {
      sub_1c0af(param_2,unaff_EBX,unaff_ECX,param_5,
                *(int *)(&unk_dbc7c + iVar6 * 4 + param_7 * 0x2e8),&uStack_c4,&local_38,0x14,
                auStack_90,0x2f,local_60,param_6);
      (&unk_db3ad)[iVar7] = uStack_c3;
      (&unk_db3ae)[iVar7] = uStack_c2;
      iVar3 = iStack_10 + param_7 * 0x444;
      strcpy(&unk_db3a8 + iVar3 + 7,acStack_c1);
      strcpy(&unk_db3a8 + iVar3 + 0x17,acStack_b1);
      if ((param_1 == 0) || (param_1 == 2)) {
        iVar7 = iVar6 * 0x27 + param_7 * 0x444;
        if ((byte_dc268 < bStack_6a) || ((byte_dc268 <= bStack_6a && (byte_dc267 < bStack_69)))) {
          (&unk_db3a8)[iVar7] = 1;
        }
        else {
          (&unk_db3a8)[iVar7] = 3;
        }
      }
      else if (*(int *)(&unk_df690 + param_7 * 0x80 + iVar6) >> 0x10 < 1) {
        (&unk_db3a8)[iVar7] =
             (&unk_c66b4)[(*(int *)(&unk_df690 + param_7 * 0x80 + iVar6) >> 0x10) * -2];
      }
      else {
        (&unk_db3a8)[iVar7] = 5;
      }
      puVar1 = (undefined4 *)(&unk_daca0 + iVar6 * 0x14 + param_7 * 500);
      *puVar1 = local_38;
      puVar1[1] = local_34;
      puVar1[2] = uStack_30;
      puVar1[3] = uStack_2c;
      puVar1[4] = uStack_28;
      if ((param_1 & 6) == 0) {
        iVar7 = param_7 * 400 + iVar6 * 0x10;
        if ((dword_c53ff._1_1_ & 2) == 0) {
          *(undefined4 *)(&unk_deb74 + iVar7) = 0;
          *(undefined4 *)(&unk_deb78 + iVar7) = 0;
          uVar4 = (uint)uStack_7c;
          *(uint *)(&unk_deb7c + iVar7) = uVar4;
          uVar2 = uStack_7a;
        }
        else {
          *(uint *)(&unk_deb74 + iVar7) = (uint)local_3c;
          *(uint *)(&unk_deb78 + iVar7) = (uint)uStack_3a + (uint)local_3c;
          uVar4 = (uint)local_8e;
          *(uint *)(&unk_deb7c + iVar7) = uVar4;
          uVar2 = uStack_8c;
        }
        *(uint *)(&unk_deb80 + iVar7) = uVar2 + uVar4;
      }
    }
    iVar6 = iVar6 + 1;
  } while (iVar6 < 0x19);
  iVar6 = 0;
  do {
    iVar5 = iVar6 * 4 + param_7 * 0x2e8;
    local_14 = param_7 * 0x444;
    iVar3 = (iVar6 + 0x19) * 0x27;
    iVar7 = local_14 + iVar3;
    if (*(int *)(&unk_dbce0 + iVar5) < 0) {
      (&unk_db3a8)[iVar7] = 0;
    }
    else {
      sub_1c0af(param_2,unaff_EBX,unaff_ECX,0,*(undefined4 *)(&unk_dbce0 + iVar5),&uStack_c4,
                &uStack_24,0x10,auStack_fc,0x36,0,0);
      (&unk_db3ad)[iVar7] = uStack_c3;
      (&unk_db3ae)[iVar7] = uStack_c2;
      iVar3 = iVar3 + local_14;
      strcpy(&unk_db3a8 + iVar3 + 7,acStack_c1);
      strcpy(&unk_db3a8 + iVar3 + 0x17,acStack_b1);
      if ((param_1 == 0) || (param_1 == 2)) {
        iVar7 = param_7 * 0x444 + (iVar6 + 0x19) * 0x27;
        if ((byte_dc268 < bStack_ce) || ((byte_dc268 <= bStack_ce && (byte_dc267 < bStack_cd)))) {
          (&unk_db3a8)[iVar7] = 1;
        }
        else {
          (&unk_db3a8)[iVar7] = 3;
        }
      }
      else if (*(int *)(&unk_df6c2 + iVar6 * 2 + param_7 * 0x100) >> 0x10 < 1) {
        (&unk_db3a8)[iVar7] =
             (&unk_c66b4)[(*(int *)(&unk_df6c2 + iVar6 * 2 + param_7 * 0x100) >> 0x10) * -2];
      }
      else {
        (&unk_db3a8)[iVar7] = 5;
      }
      puVar1 = (undefined4 *)(&unk_dac40 + param_7 * 0x30 + iVar6 * 0x10);
      *puVar1 = uStack_24;
      puVar1[1] = uStack_20;
      puVar1[2] = uStack_1c;
      puVar1[3] = local_18;
    }
    iVar6 = iVar6 + 1;
  } while (iVar6 < 3);
  return;
}


// ================================================================================================
// sub_1c807 @ 0x1c807 [__watcall]
// ================================================================================================

void __watcall sub_1c807(void)

{
  __CHK(8);
  byte_dac20 = 0;
  if (byte_c8451 != '\0') {
    strcpy(&byte_dac20,&byte_c8451);
    strcat(&byte_dac20,&unk_c0a6f);
  }
  strcat(&byte_dac20,aGsummaryDb_c0a71);
  return;
}


// ================================================================================================
// sub_1c852 @ 0x1c852 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall sub_1c852(void)

{
  int iVar1;
  undefined *puVar2;
  char cStack_30;
  char local_2f;
  char cStack_2e;
  char cStack_2d;
  undefined uStack_2b;
  char acStack_28 [24];
  
  __CHK(0x38);
  iVar1 = (uint)byte_dc224 * 0x27;
  strcpy(&cStack_30,off_cee5f);
  if ((byte)(&unk_db3ad)[iVar1] < 10) {
    cStack_2e = local_2f;
  }
  else {
    cStack_2e = cStack_2e + (byte)(&unk_db3ad)[iVar1] / 10;
  }
  cStack_2d = cStack_2d + (byte)(&unk_db3ad)[iVar1] % 10;
  uStack_2b = (&DAT_000db3af)[iVar1];
  strncpy(acStack_28,(char *)(iVar1 + 0xdb3bf),0x10);
  iVar1 = textwidth(&cStack_30);
  DAT_000cee57 = iVar1 + 5;
  strcpy(off_cee5f,&cStack_30);
  iVar1 = (uint)byte_dc225 * 0x27;
  strcpy(&cStack_30,off_cee7f);
  if ((byte)(&unk_db3ad)[iVar1] < 10) {
    cStack_2e = local_2f;
  }
  else {
    cStack_2e = cStack_2e + (byte)(&unk_db3ad)[iVar1] / 10;
  }
  cStack_2d = cStack_2d + (byte)(&unk_db3ad)[iVar1] % 10;
  uStack_2b = (&DAT_000db3af)[iVar1];
  strncpy(acStack_28,(char *)(iVar1 + 0xdb3bf),0x10);
  iVar1 = textwidth(&cStack_30);
  DAT_000cee77 = iVar1 + 5;
  strcpy(off_cee7f,&cStack_30);
  if (DAT_000cee77 < DAT_000cee57) {
    DAT_000cee97 = DAT_000cee57;
  }
  else {
    DAT_000cee97 = DAT_000cee77;
  }
  puVar2 = off_cee9f;
  if (-1 < ram0x000df64a) {
    puVar2 = (&off_cee5f)[(ram0x000df64a >> 0x10) * 8];
  }
  DAT_000cee57 = DAT_000cee97;
  DAT_000cee77 = DAT_000cee97;
  *puVar2 = 1;
  iVar1 = (uint)DAT_000dac13._1_1_ * 0x27;
  strcpy(&cStack_30,off_ceebf);
  if ((byte)(&unk_db7f1)[iVar1] < 10) {
    cStack_2e = local_2f;
  }
  else {
    cStack_2e = cStack_2e + (byte)(&unk_db7f1)[iVar1] / 10;
  }
  cStack_2d = cStack_2d + (byte)(&unk_db7f1)[iVar1] % 10;
  uStack_2b = (&DAT_000db7f3)[iVar1];
  strncpy(acStack_28,(char *)(iVar1 + 0xdb803),0x10);
  iVar1 = textwidth(&cStack_30);
  DAT_000ceeb7 = iVar1 + 5;
  strcpy(off_ceebf,&cStack_30);
  iVar1 = (uint)DAT_000dac13._2_1_ * 0x27;
  strcpy(&cStack_30,off_ceedf);
  if ((byte)(&unk_db7f1)[iVar1] < 10) {
    cStack_2e = local_2f;
  }
  else {
    cStack_2e = cStack_2e + (byte)(&unk_db7f1)[iVar1] / 10;
  }
  cStack_2d = cStack_2d + (byte)(&unk_db7f1)[iVar1] % 10;
  uStack_2b = (&DAT_000db7f3)[iVar1];
  strncpy(acStack_28,(char *)(iVar1 + 0xdb803),0x10);
  iVar1 = textwidth(&cStack_30);
  DAT_000ceed7 = iVar1 + 5;
  strcpy(off_ceedf,&cStack_30);
  if (DAT_000ceed7 < DAT_000ceeb7) {
    DAT_000ceef7 = DAT_000ceeb7;
  }
  else {
    DAT_000ceef7 = DAT_000ceed7;
  }
  puVar2 = off_ceeff;
  if (-1 < ram0x000df74a) {
    puVar2 = (&off_ceebf)[(ram0x000df74a >> 0x10) * 8];
  }
  DAT_000ceeb7 = DAT_000ceef7;
  DAT_000ceed7 = DAT_000ceef7;
  *puVar2 = 1;
  return;
}


// ================================================================================================
// sub_1cb7f @ 0x1cb7f [__watcall]
// ================================================================================================

void __watcall sub_1cb7f(void)

{
  __CHK(8);
  strcpy(off_cee5f,&unk_cdcd0);
  strcpy(off_cee7f,&unk_cdcd0);
  *off_cee9f = 2;
  strcpy(off_ceebf,&unk_cdcd0);
  strcpy(off_ceedf,&unk_cdcd0);
  *off_ceeff = 2;
  return;
}


// ================================================================================================
// sub_1cbd8 @ 0x1cbd8 [__watcall]
// ================================================================================================

void __watcall sub_1cbd8(void)

{
  int iVar1;
  
  __CHK(0x10);
  iVar1 = 0;
  do {
    (&word_c575c)[iVar1 * 4] = 0xffff;
    (&word_c571c)[iVar1 * 4] = 0xffff;
    (&unk_c5762)[iVar1 * 4] = 0;
    (&unk_c5722)[iVar1 * 4] = 0;
    (&unk_c5760)[iVar1 * 4] = 0;
    (&unk_c5720)[iVar1 * 4] = 0;
    (&unk_c575e)[iVar1 * 4] = 0;
    (&unk_c571e)[iVar1 * 4] = 0;
    iVar1 = iVar1 + 1;
  } while (iVar1 < 8);
  sub_1cc3d();
  return;
}


// ================================================================================================
// sub_1cc3d @ 0x1cc3d [__watcall]
// ================================================================================================

void __watcall sub_1cc3d(void)

{
  undefined *puVar1;
  undefined auStack_28 [16];
  
  __CHK(0x38);
  puVar1 = off_d2c6b;
  if (byte_ed938 != '\x01') {
    puVar1 = (undefined *)0x0;
  }
  make_path(auStack_28,puVar1,aScrbrd1,&aPPV);
  dword_dc2f0 = loadfile(auStack_28,0x20);
  sub_90b80(dword_dc2f0,a000000010002000300040005,&unk_dc2c4);
  sub_90b80(dword_dc2f0,a100010011002100310041005,&unk_dc30c);
  sub_90b80(dword_dc2f0,a200020012002200320042005,&unk_dc290);
  sub_90b80(dword_dc2f0,aVlinvppVpk,&unk_dc300);
  sub_90b80(dword_dc2f0,aHlinhppHpk,&unk_dc2f4);
  dword_dc2c0 = locateshape(dword_dc2f0,&aVisp);
  dword_dc2bc = locateshape(dword_dc2f0,&aHomp);
  sub_90b80(dword_dc2f0,aLin1lin2lin3lin4PP1PP2PK,&unk_dc26c);
  return;
}


// ================================================================================================
// sub_1cd73 @ 0x1cd73 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall
sub_1cd73(undefined4 *param_1,short unaff_DX,short unaff_BX,short unaff_CX,short param_5)

{
  undefined uVar1;
  undefined uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined1 *puVar6;
  short local_1c;
  short local_18;
  
  __CHK(0x3c);
  local_1c = 0;
  if (unaff_CX == 0) {
    local_18 = unaff_DX - *(short *)(param_1 + 2);
  }
  else {
    local_18 = (unaff_DX - *(short *)(param_1 + 1)) + *(short *)(param_1 + 2) + 1;
  }
  unaff_BX = unaff_BX - *(short *)((int)param_1 + 10);
  if ((((local_18 < _dword_d30b4) &&
       (iVar3 = (int)(short)(local_18 + *(short *)(param_1 + 1) + -1), dword_d30ac <= iVar3)) &&
      (iVar4 = (int)unaff_BX, iVar4 < dword_d30b8)) &&
     (iVar5 = (int)(short)(unaff_BX + *(short *)((int)param_1 + 6)), dword_d30b0 < iVar5)) {
    if (((local_18 < dword_d30ac) || (_dword_d30b4 <= iVar3)) ||
       ((iVar4 < dword_d30b0 || (dword_d30b8 <= iVar5)))) {
      local_1c = 1;
    }
    if (unaff_CX != 0) {
      local_1c = local_1c + 4;
    }
    if (-1 < param_5) {
      iVar3 = (int)param_5 + unaff_CX * 2;
      if (iVar3 != dword_c6718) {
        if (unaff_CX != 0) {
          if (param_5 == 0) {
            puVar6 = &unk_dca98;
          }
          else {
            puVar6 = &unk_dc998;
          }
          iVar5 = 0;
          do {
            uVar1 = puVar6[iVar5 + 1];
            uVar2 = puVar6[iVar5];
            puVar6[iVar5] = puVar6[iVar5 + 4];
            puVar6[iVar5 + 1] = puVar6[iVar5 + 3];
            puVar6[iVar5 + 3] = uVar1;
            puVar6[iVar5 + 4] = uVar2;
            iVar5 = iVar5 + 0x10;
          } while (iVar5 < 0x40);
        }
        if (param_5 == 0) {
          puVar6 = &unk_dc9d8;
        }
        else {
          puVar6 = &unk_dc8d8;
        }
        setremaptable(puVar6);
        dword_c6718 = iVar3;
        if (unaff_CX != 0) {
          if (param_5 == 0) {
            puVar6 = &unk_dca98;
          }
          else {
            puVar6 = &unk_dc998;
          }
          iVar3 = 0;
          do {
            uVar1 = puVar6[iVar3 + 1];
            uVar2 = puVar6[iVar3];
            puVar6[iVar3] = puVar6[iVar3 + 4];
            puVar6[iVar3 + 1] = puVar6[iVar3 + 3];
            puVar6[iVar3 + 3] = uVar1;
            puVar6[iVar3 + 4] = uVar2;
            iVar3 = iVar3 + 0x10;
          } while (iVar3 < 0x40);
        }
      }
      local_1c = local_1c + 2;
    }
    iVar3 = dword_d8c40;
    if ((char)*param_1 != '\0') {
      local_1c = local_1c + 8;
    }
    iVar5 = (int)local_18;
    dword_d8c40 = dword_d8c40 + 1;
    sub_6ab7c(iVar3,iVar5,iVar4,(*(int *)((int)param_1 + 2) >> 0x10) + iVar5,
              ((int)param_1[1] >> 0x10) + iVar4);
    switch(local_1c) {
    case 8:
      sub_b4cd8(param_1,iVar5,iVar4);
      break;
    case 9:
      sub_b500c(param_1,iVar5,iVar4);
      break;
    case 10:
      sub_b4e50(param_1,iVar5,iVar4);
      break;
    case 0xb:
      sub_b52b4();
      break;
    case 0xc:
      sub_b5584();
      break;
    case 0xd:
      sub_b56b8();
      break;
    case 0xe:
      sub_b5974();
      break;
    case 0xf:
      sub_b5ac8();
    }
  }
  return;
}


// ================================================================================================
// sub_1d019 @ 0x1d019 [__watcall]
// ================================================================================================

void __watcall sub_1d019(void)

{
  __CHK(4);
  return;
}


// ================================================================================================
// sub_1d024 @ 0x1d024 [__watcall]
// ================================================================================================

void __watcall sub_1d024(void)

{
  __CHK(4);
  return;
}


// ================================================================================================
// sub_1d02f @ 0x1d02f [__watcall]
// ================================================================================================

void __watcall sub_1d02f(short param_1,short unaff_DX,short unaff_BX,short unaff_CX)

{
  int iVar1;
  
  __CHK(0xc);
  *(uint *)(*(int *)(&unk_dc8d0 + (uint)(dword_eda04 == 0) * 4) + 8) =
       (((uint)((int)unaff_BX + (int)param_1) >> 2) - ((uint)(int)param_1 >> 2)) + 1;
  *(int *)(*(int *)(&unk_dc8d0 + (uint)(dword_eda04 == 0) * 4) + 0xc) = (int)unaff_CX;
  **(uint **)(&unk_dc8d0 + (uint)(dword_eda04 == 0) * 4) = (uint)(int)param_1 >> 2;
  *(int *)(*(int *)(&unk_dc8d0 + (uint)(dword_eda04 == 0) * 4) + 4) = (int)unaff_DX;
  iVar1 = dword_eda04;
  *(int *)(&unk_c66c8 + (uint)(dword_eda04 == 0) * 4) =
       *(int *)(&unk_c66c8 + (uint)(dword_eda04 == 0) * 4) + 1;
  *(int *)(&unk_dc8d0 + (uint)(iVar1 == 0) * 4) =
       *(int *)(&unk_dc8d0 + (uint)(iVar1 == 0) * 4) + 0x10;
  return;
}


// ================================================================================================
// sub_1d100 @ 0x1d100 [__watcall]
// ================================================================================================

void __watcall sub_1d100(int param_1,undefined4 param_2,undefined4 param_3,int unaff_ECX)

{
  char cVar1;
  char *__src;
  int iVar2;
  int iVar3;
  
  __CHK(0x1c);
  cVar1 = byte_c671c;
  if ((param_1 == 0) && ((byte_c5311 == '\0' || (byte_c5386 == '\0')))) {
    if (byte_c5311 == '\0') {
      if (byte_c5386 == '\0') {
        param_1 = 1;
      }
      else {
        param_1 = 3;
      }
    }
    else {
      param_1 = 2;
    }
  }
  switch(param_1) {
  case 0:
    funcptr_c6825 = sub_17be7;
    funcptr_c6845 = sub_17ce0;
    funcptr_c6885 = sub_17d6e;
    off_c6821 = &byte_c6745;
    off_c6841 = &byte_c6759;
    off_c6881 = &byte_c6777;
    if (byte_c6745 == '\x01') {
      byte_c6759 = '\x02';
      if (dword_c6956 != 0) {
        dword_c65b4 = 0;
      }
      dword_c6956 = 0;
LAB_0001d3c0:
      byte_c6777 = '\x02';
      __src = &byte_c5386;
LAB_0001d469:
      dword_c695a = 1;
      byte_c672f = '\x02';
      byte_c671c = '\x02';
      strncpy(&unk_c65d4,__src,0x1f);
    }
    else {
      if (byte_c6759 == '\x01') {
        byte_c6745 = '\x02';
        if (dword_c6956 == 0) {
          dword_c65b4 = dword_c6956;
        }
        dword_c6956 = 1;
        goto LAB_0001d3c0;
      }
      if (byte_c6777 == '\x01') {
        byte_c6759 = '\x02';
        byte_c6745 = '\x02';
        if (dword_c6956 == 0) {
          dword_c65b4 = dword_c6956;
        }
        dword_c6956 = 1;
        __src = &byte_c5311;
        goto LAB_0001d469;
      }
    }
    unaff_ECX = 7;
    break;
  case 1:
    if ((byte_c671c == '\x02') && (byte_c672f == '\x02')) {
      byte_c671c = '\x01';
      byte_c6777 = cVar1;
      byte_c6759 = cVar1;
      byte_c6745 = cVar1;
      byte_c672f = cVar1;
      dword_c695a = 0;
      if (dword_c6956 != 0) {
        dword_c65b4 = 0;
      }
      dword_c6956 = 0;
      strncpy(&unk_c65d4,&unk_c529c,0x1f);
    }
    unaff_ECX = 2;
    break;
  case 2:
    funcptr_c6825 = sub_17d6e;
    off_c6821 = &byte_c6777;
    if (((byte_c6745 == '\x01') || (byte_c6759 == '\x01')) || (byte_c6777 == '\x01')) {
      byte_c6777 = '\x01';
      byte_c6759 = '\x02';
      byte_c6745 = '\x02';
      byte_c672f = '\x02';
      byte_c671c = '\x02';
      dword_c695a = 1;
      if (dword_c6956 == 0) {
        dword_c65b4 = dword_c6956;
      }
      dword_c6956 = 1;
      strncpy(&unk_c65d4,&byte_c5311,0x1f);
    }
    unaff_ECX = 4;
    break;
  case 3:
    funcptr_c6825 = sub_17be7;
    funcptr_c6845 = sub_17ce0;
    off_c6821 = &byte_c6745;
    off_c6841 = &byte_c6759;
    if ((byte_c6777 == '\x01') || (byte_c6745 == '\x01')) {
      byte_c6745 = '\x01';
      byte_c6759 = '\x02';
      if (dword_c6956 != 0) {
        dword_c65b4 = 0;
      }
      dword_c6956 = 0;
LAB_0001d223:
      dword_c695a = 1;
      byte_c6777 = '\x02';
      byte_c672f = '\x02';
      byte_c671c = '\x02';
      strncpy(&unk_c65d4,&byte_c5386,0x1f);
    }
    else if (byte_c6759 == '\x01') {
      byte_c6745 = '\x02';
      if (dword_c6956 == 0) {
        dword_c65b4 = dword_c6956;
      }
      dword_c6956 = 1;
      goto LAB_0001d223;
    }
    unaff_ECX = 5;
  }
  if (unaff_ECX == 4) {
    dword_c67b9 = 0xc5;
    unk_c678e[0x1b] = '\0';
  }
  else {
    dword_c67b9 = 0xf7;
    unk_c678e[0x1b] = '-';
  }
  iVar3 = 0x11;
  for (iVar2 = 0; iVar2 < unaff_ECX; iVar2 = iVar2 + 1) {
    (&unk_c67bd)[iVar2 * 8] = iVar3;
    (&dword_c67b9)[iVar2 * 8] = dword_c67b9;
    iVar3 = iVar3 + 0x12;
  }
  dword_c891e = unaff_ECX;
  dword_ce8eb = unaff_ECX;
  dword_cf00b = unaff_ECX;
  dword_cf4cb = unaff_ECX;
  dword_cf5ab = unaff_ECX;
  dword_cf70b = unaff_ECX;
  dword_cf7cb = unaff_ECX;
  dword_cf84b = unaff_ECX;
  dword_cf8cb = unaff_ECX;
  dword_cfa4b = unaff_ECX;
  *(int *)(unk_c678e + unaff_ECX * 0x20 + 0xf) = *(int *)(unk_c678e + unaff_ECX * 0x20 + 0xf) + 1;
  return;
}


// ================================================================================================
// sub_1d518 @ 0x1d518 [__watcall]
// ================================================================================================

void __watcall sub_1d518(void)

{
  int iVar1;
  
  __CHK(0x10);
  if (byte_c5311 != '\0') {
    iVar1 = sub_1d5d5(&byte_c5311);
    (&byte_c5311)[iVar1] = 0;
    strcpy(s__WWWWWWWW__Play_Offs_000c6778 + 2,&byte_c5311);
    strcpy(s__WWWWWWWW__Play_Offs_000c6778 + iVar1 + 2,aPlayOffs);
    (&byte_c5311)[iVar1] = 0x2e;
  }
  if (byte_c5386 != '\0') {
    iVar1 = sub_1d5d5(&byte_c5386);
    (&byte_c5386)[iVar1] = 0;
    strcpy(s__WWWWWWWW__Season_000c6746 + 2,&byte_c5386);
    strcpy(s__WWWWWWWW__Season_Play_Offs_000c675a + 2,&byte_c5386);
    strcpy(s__WWWWWWWW__Season_000c6746 + iVar1 + 2,aSeason_c6891);
    strcpy(s__WWWWWWWW__Season_Play_Offs_000c675a + iVar1 + 2,aSeasonPlayOffs);
    (&byte_c5386)[iVar1] = 0x2e;
  }
  return;
}


// ================================================================================================
// sub_1d5d5 @ 0x1d5d5 [__watcall]
// ================================================================================================

undefined8 __watcall sub_1d5d5(char *param_1,undefined4 unaff_EDX)

{
  int iVar1;
  
  __CHK(0xc);
  iVar1 = 0;
  for (; (*param_1 != '\0' && (*param_1 != '.')); param_1 = param_1 + 1) {
    iVar1 = iVar1 + 1;
  }
  return CONCAT44(unaff_EDX,iVar1);
}


// ================================================================================================
// menu_hub_labels @ 0x1d610 [__watcall]
// ================================================================================================

void __watcall menu_hub_labels(undefined4 param_1,int unaff_EDX,char *unaff_EBX)

{
  __CHK(0xc);
  switch(param_1) {
  case 0:
    unaff_EBX = aSportsCentral_ce20b;
    unaff_EDX = 0x67;
    break;
  case 1:
    unaff_EBX = aPlayoffTree_ce22a;
    unaff_EDX = 0x59;
    break;
  case 2:
    unaff_EBX = aLeagueCalendar;
    unaff_EDX = 0x76;
    break;
  case 3:
    unaff_EBX = aBroadcastBooth;
    unaff_EDX = 0x73;
    break;
  case 4:
    unaff_EBX = aIntermissionDesk;
    unaff_EDX = 0x7e;
    break;
  case 5:
    unaff_EBX = aRinkSide;
    unaff_EDX = 0x41;
  }
  off_cf67f = unaff_EBX;
  off_cf61f = unaff_EBX;
  off_cf5df = unaff_EBX;
  off_cf51f = unaff_EBX;
  dword_cf5d7 = unaff_EDX;
  dword_cf517 = unaff_EDX;
  if (unaff_EDX < 0x7e) {
    unaff_EDX = 0x7d;
  }
  dword_cf677 = unaff_EDX;
  dword_cf657 = unaff_EDX;
  dword_cf637 = unaff_EDX;
  dword_cf617 = unaff_EDX;
  dword_cf5f7 = unaff_EDX;
  return;
}


// ================================================================================================
// sub_1d6be @ 0x1d6be [__watcall]
// ================================================================================================

undefined4 __watcall sub_1d6be(char *param_1,char *unaff_EDX)

{
  __CHK(8);
  for (; (*param_1 != '\0' && (*unaff_EDX != '\0')); unaff_EDX = unaff_EDX + 1) {
    if (*param_1 != *unaff_EDX) {
      return 1;
    }
    param_1 = param_1 + 1;
  }
  return 0;
}


// ================================================================================================
// sub_1d6e8 @ 0x1d6e8 [__watcall]
// ================================================================================================

undefined4 __watcall
sub_1d6e8(int *param_1,undefined4 param_2,undefined4 unaff_EBX,undefined4 unaff_ECX,
         undefined4 param_5)

{
  ulonglong uVar1;
  int iVar2;
  undefined4 ****ppppuVar3;
  int iVar4;
  undefined4 *****pppppuVar5;
  undefined4 *puVar6;
  int *piVar7;
  undefined4 uVar8;
  undefined4 extraout_EDX;
  int iVar9;
  undefined4 *****pppppuVar10;
  int iVar11;
  undefined4 *****pppppuVar12;
  undefined4 *****pppppuVar13;
  undefined4 *puVar14;
  byte bVar15;
  ulonglong uVar16;
  undefined8 uVar17;
  int local_98 [8];
  int local_78 [4];
  int *local_68 [4];
  int local_58 [4];
  int local_38;
  int local_34;
  undefined4 ****local_30;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  undefined4 ****local_1c;
  int local_18;
  undefined4 ****local_14;
  int local_10;
  
  bVar15 = 0;
  __CHK(0xb4);
  local_10 = 0;
  local_68[3] = (int *)0x0;
  local_68[2] = (int *)0x0;
  local_68[1] = (int *)0x0;
  local_58[3] = 0;
  local_58[2] = 0;
  local_58[1] = 0;
  local_58[0] = 0;
  local_78[3] = 0;
  local_78[2] = 0;
  local_78[1] = 0;
  local_78[0] = 0;
  local_98[1] = 0;
  local_98[0] = 0;
  local_68[0] = param_1;
  local_1c = (undefined4 ****)
             allocmem(aPointer_c0b54,
                      ((*(int *)((int)dword_dc238 + 2) >> 0x10) + 1) *
                      (((int)dword_dc238[1] >> 0x10) + 1) + 0x11,0x20);
  pppppuVar12 = (undefined4 *****)local_1c + (uint)bVar15 * -2 + 1;
  pppppuVar10 = dword_dc238 + (uint)bVar15 * -2 + 1;
  *local_1c = *dword_dc238;
  pppppuVar13 = pppppuVar12 + (uint)bVar15 * -2 + 1;
  pppppuVar5 = pppppuVar10 + (uint)bVar15 * -2 + 1;
  *pppppuVar12 = *pppppuVar10;
  *pppppuVar13 = *pppppuVar5;
  pppppuVar13[(uint)bVar15 * -2 + 1] = pppppuVar5[(uint)bVar15 * -2 + 1];
  *(undefined *)(pppppuVar13 + (uint)bVar15 * -2 + 1 + (uint)bVar15 * -2 + 1) =
       *(undefined *)(pppppuVar5 + (uint)bVar15 * -2 + 1 + (uint)bVar15 * -2 + 1);
  *(short *)((undefined4 *****)local_1c + 1) = *(short *)(dword_dc238 + 1) + 1;
  *(short *)((int)local_1c + 6) = *(short *)((int)dword_dc238 + 6) + 1;
  iVar4 = (*local_68[0] + local_68[0][2]) / 2;
  pppppuVar5 = (undefined4 *****)((local_68[0][1] + local_68[0][3]) / 2);
  local_30 = pppppuVar5;
  local_2c = iVar4;
  local_18 = iVar4;
  local_14 = pppppuVar5;
  grabshape(local_1c,iVar4,pppppuVar5);
  pppppuVar10 = dword_dc238;
  drawshape_remap(dword_dc238,iVar4,pppppuVar5);
  setmouselimits(0,0,0x280,0x1e0);
  setmousepos(iVar4,pppppuVar5);
  (*(code *)funcptr_d3078)();
  uVar16 = sub_6b3d7();
LAB_0001d83a:
  uVar8 = 0;
  do {
    uVar17 = sub_6b391((int)uVar16,(int)(uVar16 >> 0x20),pppppuVar10);
    uVar1 = CONCAT44((int)((ulonglong)uVar17 >> 0x20),uVar8);
    if ((int)uVar17 == 0) break;
    pppppuVar10 = &local_30;
    uVar16 = (*dword_ea0dc)();
    uVar8 = (undefined4)uVar16;
    uVar1 = uVar16;
  } while ((uVar16 & 2) == 0);
  ppppuVar3 = local_1c;
  uVar16 = CONCAT44((int)(uVar1 >> 0x20),local_30);
  if ((uVar1 & 2) == 0) goto code_r0x0001d862;
  iVar4 = sub_6ba4d(local_2c,local_30,local_68,local_10,&stack0xffffffb8,local_98,&local_34,
                    &local_38);
  if (iVar4 == 0) {
    drawshape(local_1c,local_18,local_14);
    for (iVar4 = 3; -1 < iVar4; iVar4 = iVar4 + -1) {
      if (local_58[iVar4] != 0) {
        drawshape(local_58[iVar4],local_98[iVar4 * 2],local_98[iVar4 * 2 + 1]);
        local_98[iVar4 * 2 + 1] = 0;
        local_98[iVar4 * 2] = 0;
        freemem(local_58[iVar4]);
      }
    }
    local_10 = 0;
    local_68[3] = (int *)0x0;
    local_68[2] = (int *)0x0;
    local_68[1] = (int *)0x0;
    local_58[3] = 0;
    local_58[2] = 0;
    local_58[1] = 0;
    local_58[0] = 0;
    local_78[3] = 0;
    local_78[2] = 0;
    local_78[1] = 0;
  }
  else {
    if (local_68[local_34][local_38 * 8 + 5] == 0) {
      if (local_68[local_34][local_38 * 8 + 6] == 0) {
        drawshape(local_1c,local_18,local_14);
        sub_6b94e(local_68[local_34] + local_78[local_34] * 8,local_98[local_34 * 2],
                  local_98[local_34 * 2 + 1],unaff_EBX,unaff_ECX,param_5);
        iVar2 = local_34;
        iVar11 = local_38;
        local_78[local_34] = local_38;
        iVar4 = local_98[iVar2 * 2 + 1];
        iVar9 = local_98[iVar2 * 2];
        piVar7 = local_68[iVar2] + iVar11 * 8;
      }
      else {
        drawshape(local_1c,local_18,local_14);
        iVar4 = local_10;
        if (local_10 != local_34) {
          for (; local_34 < iVar4; iVar4 = iVar4 + -1) {
            local_78[iVar4] = 0;
            if (local_58[iVar4] != 0) {
              drawshape(local_58[iVar4],local_98[iVar4 * 2],local_98[iVar4 * 2 + 1]);
              local_98[iVar4 * 2 + 1] = 0;
              local_98[iVar4 * 2] = 0;
              freemem(local_58[iVar4]);
              local_58[iVar4] = 0;
              local_68[iVar4] = (int *)0x0;
              *(undefined4 *)(&stack0xffffffb8 + iVar4 * 4) = 0;
            }
          }
          local_10 = local_34;
        }
        iVar11 = local_10;
        sub_6b94e(local_68[local_10] + local_78[local_10] * 8,local_98[local_10 * 2],
                  local_98[local_10 * 2 + 1],unaff_EBX,unaff_ECX,param_5);
        iVar4 = local_38;
        local_78[iVar11] = local_38;
        sub_6b9eb(local_68[iVar11] + iVar4 * 8,local_98[iVar11 * 2],local_98[iVar11 * 2 + 1],
                  unaff_EBX,unaff_ECX,param_5);
        iVar9 = local_34;
        iVar4 = local_38;
        iVar11 = iVar11 + 1;
        local_10 = iVar11;
        local_68[iVar11] = (int *)local_68[local_34][local_38 * 8 + 6];
        piVar7 = local_68[iVar9] + iVar4 * 8;
        *(int *)(&stack0xffffffb8 + iVar11 * 4) = piVar7[7];
        if (iVar11 == 1) {
          iVar4 = *piVar7;
        }
        else {
          iVar4 = piVar7[2];
        }
        local_98[local_10 * 2] = iVar4 + local_98[local_10 * 2 + -2];
        if (local_10 == 1) {
          iVar4 = local_68[local_34][local_38 * 8 + 3];
        }
        else {
          iVar4 = local_68[local_34][local_38 * 8 + 1];
        }
        local_20 = local_10 * 8;
        local_98[local_10 * 2 + 1] = iVar4 + local_98[local_10 * 2 + -1];
        iVar11 = local_10;
        piVar7 = local_68[local_10];
        local_24 = (piVar7[*(int *)(&stack0xffffffb8 + local_10 * 4) * 8 + -6] - *piVar7) + 1;
        local_28 = (piVar7[*(int *)(&stack0xffffffb8 + local_10 * 4) * 8 + -5] - piVar7[1]) + 1;
        puVar6 = (undefined4 *)allocmem(aMenubuff_c0b5c,local_24 * local_28 + 0x11,0x20);
        local_58[iVar11] = (int)puVar6;
        puVar14 = puVar6 + (uint)bVar15 * -2 + 1;
        pppppuVar10 = dword_dc238 + (uint)bVar15 * -2 + 1;
        *puVar6 = *dword_dc238;
        puVar6 = puVar14 + (uint)bVar15 * -2 + 1;
        pppppuVar5 = pppppuVar10 + (uint)bVar15 * -2 + 1;
        *puVar14 = *pppppuVar10;
        *puVar6 = *pppppuVar5;
        puVar6[(uint)bVar15 * -2 + 1] = pppppuVar5[(uint)bVar15 * -2 + 1];
        *(undefined *)(puVar6 + (uint)bVar15 * -2 + 1 + (uint)bVar15 * -2 + 1) =
             *(undefined *)(pppppuVar5 + (uint)bVar15 * -2 + 1 + (uint)bVar15 * -2 + 1);
        *(short *)(local_58[iVar11] + 4) = (short)local_24;
        *(short *)(local_58[iVar11] + 6) = (short)local_28;
        grabshape(local_58[iVar11],*(undefined4 *)((int)local_98 + local_20),
                  *(undefined4 *)((int)local_98 + local_20 + 4));
        sub_6b684(local_68[iVar11],*(undefined4 *)(&stack0xffffffb8 + iVar11 * 4),
                  *(undefined4 *)((int)local_98 + local_20),
                  *(undefined4 *)((int)local_98 + local_20 + 4),unaff_EBX,unaff_ECX,param_5);
        local_78[iVar11] = 0;
        iVar4 = *(int *)((int)local_98 + local_20 + 4);
        iVar9 = *(int *)((int)local_98 + local_20);
        piVar7 = local_68[iVar11];
      }
    }
    else {
      if (local_38 == local_78[local_34]) {
        drawshape(local_1c,local_18,local_14);
        for (iVar4 = 3; -1 < iVar4; iVar4 = iVar4 + -1) {
          if (local_58[iVar4] != 0) {
            drawshape(local_58[iVar4],local_98[iVar4 * 2],local_98[iVar4 * 2 + 1]);
            local_98[iVar4 * 2 + 1] = 0;
            local_98[iVar4 * 2] = 0;
            freemem(local_58[iVar4]);
          }
        }
        local_10 = 0;
        iVar4 = (*(code *)local_68[local_34][local_38 * 8 + 5])();
        local_68[3] = (int *)0x0;
        local_68[2] = (int *)0x0;
        local_68[1] = (int *)0x0;
        local_58[3] = 0;
        local_58[2] = 0;
        local_58[1] = 0;
        local_58[0] = 0;
        local_78[3] = 0;
        local_78[2] = 0;
        local_78[1] = 0;
        if (iVar4 == 1) {
          freemem(local_1c);
          return 0;
        }
        setmousepos(local_18,local_14);
        local_2c = local_18;
        local_30 = local_14;
        sub_6b3d7();
        goto LAB_0001de8d;
      }
      drawshape(local_1c,local_18,local_14);
      sub_6b94e(local_68[local_34] + local_78[local_34] * 8,local_98[local_34 * 2],
                local_98[local_34 * 2 + 1],unaff_EBX,unaff_ECX,param_5);
      iVar11 = local_34;
      local_78[local_34] = local_38;
      iVar4 = local_98[iVar11 * 2 + 1];
      iVar9 = local_98[iVar11 * 2];
      piVar7 = local_68[iVar11] + local_78[iVar11] * 8;
    }
    sub_6b9eb(piVar7,iVar9,iVar4,unaff_EBX,unaff_ECX,param_5);
  }
LAB_0001de8d:
  grabshape(local_1c,local_18,local_14);
  pppppuVar10 = (undefined4 *****)local_1c;
  drawshape(local_1c,local_18,local_14);
  grabshape(local_1c,local_2c,local_30);
  goto LAB_0001d8c0;
code_r0x0001d862:
  if ((local_2c != local_18) || (local_30 != local_14)) {
    drawshape(local_1c,local_18,local_14);
    grabshape(ppppuVar3,local_2c,local_30);
    pppppuVar10 = (undefined4 *****)local_30;
LAB_0001d8c0:
    drawshape_remap(dword_dc238,local_2c,local_30);
    uVar16 = CONCAT44(extraout_EDX,local_30);
    local_18 = local_2c;
    local_14 = local_30;
  }
  goto LAB_0001d83a;
}


// ================================================================================================
// sub_1df03 @ 0x1df03 [__watcall]
// ================================================================================================

undefined4 __watcall
sub_1df03(int *param_1,undefined4 param_2,undefined4 unaff_EBX,undefined4 unaff_ECX,
         undefined4 param_5)

{
  undefined4 ****ppppuVar1;
  undefined4 ****ppppuVar2;
  int iVar3;
  int *piVar4;
  undefined4 *puVar5;
  int iVar6;
  uint uVar7;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 uVar8;
  undefined4 *****pppppuVar9;
  int iVar10;
  undefined4 *****pppppuVar11;
  undefined4 *****pppppuVar12;
  undefined4 *puVar13;
  byte bVar14;
  ulonglong uVar15;
  undefined8 uVar16;
  undefined4 *****pppppuVar17;
  int local_a4 [8];
  int local_74 [8];
  int *local_54 [4];
  int local_44;
  undefined4 ****local_40;
  int local_3c;
  int local_38;
  undefined4 ****local_34;
  int local_30;
  int local_2c;
  int local_28;
  int local_24;
  undefined4 ****local_20;
  int local_1c;
  undefined4 ****local_18;
  undefined4 ****local_14;
  undefined4 local_10;
  
  bVar14 = 0;
  __CHK(0xc4);
  local_38 = 0;
  local_3c = 0;
  local_14 = (undefined4 *****)0x0;
  local_54[3] = (int *)0x0;
  local_54[2] = (int *)0x0;
  local_54[1] = (int *)0x0;
  local_74[7] = 0;
  local_74[6] = 0;
  local_74[5] = 0;
  local_74[4] = 0;
  local_74[3] = 0;
  local_74[2] = 0;
  local_74[1] = 0;
  local_74[0] = 0;
  local_a4[1] = 0;
  local_a4[0] = 0;
  local_54[0] = param_1;
  local_20 = (undefined4 ****)
             allocmem(aPointer_c0b54,
                      (((int)dword_dc238[1] >> 0x10) + 1) *
                      ((*(int *)((int)dword_dc238 + 2) >> 0x10) + 1) + 0x11,0x20);
  pppppuVar11 = (undefined4 *****)local_20 + (uint)bVar14 * -2 + 1;
  pppppuVar9 = dword_dc238 + (uint)bVar14 * -2 + 1;
  *local_20 = *dword_dc238;
  pppppuVar12 = pppppuVar11 + (uint)bVar14 * -2 + 1;
  pppppuVar17 = pppppuVar9 + (uint)bVar14 * -2 + 1;
  *pppppuVar11 = *pppppuVar9;
  *pppppuVar12 = *pppppuVar17;
  pppppuVar12[(uint)bVar14 * -2 + 1] = pppppuVar17[(uint)bVar14 * -2 + 1];
  *(undefined *)(pppppuVar12 + (uint)bVar14 * -2 + 1 + (uint)bVar14 * -2 + 1) =
       *(undefined *)(pppppuVar17 + (uint)bVar14 * -2 + 1 + (uint)bVar14 * -2 + 1);
  *(short *)((undefined4 *****)local_20 + 1) = *(short *)(dword_dc238 + 1) + 1;
  *(short *)((int)local_20 + 6) = *(short *)((int)dword_dc238 + 6) + 1;
  local_30 = (*local_54[0] + local_54[0][2]) / 2;
  local_34 = (undefined4 ****)((local_54[0][1] + local_54[0][3]) / 2);
  local_1c = local_30;
  local_18 = local_34;
  if (dword_c6956 == 0) {
    iVar10 = 0;
    do {
      if (dword_c65b4 == (&unk_dc640)[iVar10]) {
        local_3c = iVar10;
      }
      iVar10 = iVar10 + 1;
    } while (iVar10 < 0x1a);
    if ((uint)*(byte *)(dword_dd10c + 0xd + (&unk_dc640)[local_3c] * 0x1a) % 2 == 0) {
      iVar10 = 0xa5;
    }
    else {
      iVar10 = 0x14a;
    }
    if (*(byte *)(dword_dd10c + 0xd + (&unk_dc640)[local_3c] * 0x1a) < 2) {
      uVar8 = 0;
    }
    else {
      uVar8 = 0x140;
    }
    if (local_3c < 0xc) {
      iVar6 = 6;
      iVar3 = local_3c;
    }
    else {
      iVar3 = local_3c + -0xc;
      iVar6 = 7;
    }
    fillrect2(uVar8,iVar10 + (iVar3 % iVar6) * 0xd,0x140,0xd,0x80);
  }
  else {
    local_3c = dword_c65b4;
    if ((&dword_dc7b8)[dword_c65b4] != 0x1a) {
      sub_27bc3(&local_3c,0);
    }
  }
  ppppuVar1 = local_18;
  iVar10 = local_1c;
  grabshape(local_20,local_1c,local_18);
  pppppuVar9 = dword_dc238;
  drawshape_remap(dword_dc238,iVar10,ppppuVar1);
  setmouselimits(0,0,0x280,0x1e0);
  setmousepos(iVar10,ppppuVar1);
  (*(code *)funcptr_d3078)();
  uVar15 = sub_6b3d7();
LAB_0001e287:
  uVar7 = 0;
  do {
    iVar10 = sub_6b391((int)uVar15,(int)(uVar15 >> 0x20),pppppuVar9);
    if (iVar10 == 0) break;
    pppppuVar9 = &local_34;
    uVar15 = (*dword_ea0dc)();
    uVar7 = (uint)uVar15;
  } while ((uVar15 & 2) == 0);
  ppppuVar1 = local_20;
  if ((uVar7 & 2) == 0) goto code_r0x0001e2ab;
  iVar3 = sub_6ba4d(local_30,local_34,local_54,local_14,&stack0xffffff7c,local_a4,&local_40,
                    &local_44);
  ppppuVar1 = local_18;
  iVar10 = local_1c;
  if (iVar3 != 0) {
    if (local_54[(int)local_40][local_44 * 8 + 5] == 0) {
      if (local_54[(int)local_40][local_44 * 8 + 6] == 0) {
        drawshape(local_20,local_1c,local_18);
        sub_6b94e(local_54[(int)local_40] + local_74[(int)local_40] * 8,local_a4[(int)local_40 * 2],
                  local_a4[(int)local_40 * 2 + 1],unaff_EBX,unaff_ECX,param_5);
        ppppuVar1 = local_40;
        iVar6 = local_44;
        local_74[(int)local_40] = local_44;
        iVar10 = local_a4[(int)ppppuVar1 * 2 + 1];
        iVar3 = local_a4[(int)ppppuVar1 * 2];
        piVar4 = local_54[(int)ppppuVar1] + iVar6 * 8;
        uVar8 = unaff_ECX;
      }
      else {
        drawshape(local_20,local_1c,local_18);
        pppppuVar9 = (undefined4 *****)local_14;
        if (local_14 != local_40) {
          for (; (int)local_40 < (int)pppppuVar9;
              pppppuVar9 = (undefined4 *****)((int)pppppuVar9 + -1)) {
            local_74[(int)pppppuVar9] = 0;
            if (local_74[(int)(pppppuVar9 + 1)] != 0) {
              drawshape(local_74[(int)(pppppuVar9 + 1)],local_a4[(int)pppppuVar9 * 2],
                        local_a4[(int)pppppuVar9 * 2 + 1]);
              local_a4[(int)pppppuVar9 * 2 + 1] = 0;
              local_a4[(int)pppppuVar9 * 2] = 0;
              freemem(local_74[(int)(pppppuVar9 + 1)]);
              local_74[(int)(pppppuVar9 + 1)] = 0;
              local_54[(int)pppppuVar9] = (int *)0x0;
              local_74[(int)(pppppuVar9 + -1)] = 0;
            }
          }
          local_14 = local_40;
        }
        ppppuVar2 = local_14;
        sub_6b94e(local_54[(int)local_14] + local_74[(int)local_14] * 8,local_a4[(int)local_14 * 2],
                  local_a4[(int)local_14 * 2 + 1],unaff_EBX,unaff_ECX,param_5);
        iVar10 = local_44;
        local_74[(int)ppppuVar2] = local_44;
        sub_6b9eb(local_54[(int)ppppuVar2] + iVar10 * 8,local_a4[(int)ppppuVar2 * 2],
                  local_a4[(int)ppppuVar2 * 2 + 1],unaff_EBX,unaff_ECX,param_5);
        ppppuVar1 = local_40;
        iVar10 = local_44;
        pppppuVar9 = (undefined4 *****)((int)ppppuVar2 + 1);
        local_14 = pppppuVar9;
        local_54[(int)pppppuVar9] = (int *)local_54[(int)local_40][local_44 * 8 + 6];
        piVar4 = local_54[(int)ppppuVar1] + iVar10 * 8;
        local_74[(int)(pppppuVar9 + -1)] = piVar4[7];
        if (pppppuVar9 == (undefined4 *****)0x1) {
          iVar10 = *piVar4;
        }
        else {
          iVar10 = piVar4[2];
        }
        local_a4[(int)local_14 * 2] = iVar10 + local_a4[(int)local_14 * 2 + -2];
        if ((undefined4 *****)local_14 == (undefined4 *****)0x1) {
          iVar10 = local_54[(int)local_40][local_44 * 8 + 3];
        }
        else {
          iVar10 = local_54[(int)local_40][local_44 * 8 + 1];
        }
        local_24 = (int)local_14 * 8;
        local_a4[(int)local_14 * 2 + 1] = iVar10 + local_a4[(int)local_14 * 2 + -1];
        ppppuVar1 = local_14;
        piVar4 = local_54[(int)local_14];
        local_28 = (piVar4[local_74[(int)(local_14 + -1)] * 8 + -6] - *piVar4) + 1;
        local_2c = (piVar4[local_74[(int)(local_14 + -1)] * 8 + -5] - piVar4[1]) + 1;
        puVar5 = (undefined4 *)allocmem(aMenubuff_c0b5c,local_28 * local_2c + 0x11,0x20);
        local_74[(int)(ppppuVar1 + 1)] = (int)puVar5;
        puVar13 = puVar5 + (uint)bVar14 * -2 + 1;
        pppppuVar9 = dword_dc238 + (uint)bVar14 * -2 + 1;
        *puVar5 = *dword_dc238;
        puVar5 = puVar13 + (uint)bVar14 * -2 + 1;
        pppppuVar17 = pppppuVar9 + (uint)bVar14 * -2 + 1;
        *puVar13 = *pppppuVar9;
        *puVar5 = *pppppuVar17;
        puVar5[(uint)bVar14 * -2 + 1] = pppppuVar17[(uint)bVar14 * -2 + 1];
        *(undefined *)(puVar5 + (uint)bVar14 * -2 + 1 + (uint)bVar14 * -2 + 1) =
             *(undefined *)(pppppuVar17 + (uint)bVar14 * -2 + 1 + (uint)bVar14 * -2 + 1);
        *(short *)(local_74[(int)(ppppuVar1 + 1)] + 4) = (short)local_28;
        *(short *)(local_74[(int)(ppppuVar1 + 1)] + 6) = (short)local_2c;
        grabshape(local_74[(int)(ppppuVar1 + 1)],*(undefined4 *)((int)local_a4 + local_24),
                  *(undefined4 *)((int)local_a4 + local_24 + 4));
        uVar8 = unaff_ECX;
        sub_6b684(local_54[(int)ppppuVar1],local_74[(int)(ppppuVar1 + -1)],
                  *(undefined4 *)((int)local_a4 + local_24),
                  *(undefined4 *)((int)local_a4 + local_24 + 4),unaff_EBX,unaff_ECX,param_5);
        local_74[(int)ppppuVar1] = 0;
        iVar10 = *(int *)((int)local_a4 + local_24 + 4);
        iVar3 = *(int *)((int)local_a4 + local_24);
        piVar4 = local_54[(int)ppppuVar1];
      }
    }
    else {
      if (local_44 == local_74[(int)local_40]) {
        drawshape(local_20,local_1c,local_18);
        for (iVar10 = 3; -1 < iVar10; iVar10 = iVar10 + -1) {
          if (local_74[iVar10 + 4] != 0) {
            drawshape(local_74[iVar10 + 4],local_a4[iVar10 * 2],local_a4[iVar10 * 2 + 1]);
            local_a4[iVar10 * 2 + 1] = 0;
            local_a4[iVar10 * 2] = 0;
            freemem(local_74[iVar10 + 4]);
          }
        }
        local_14 = (undefined4 *****)0x0;
        if (dword_c6956 == 0) {
          dword_c65b0 = (&unk_dc640)[local_3c];
          local_38 = dword_c65b0;
          if ((uint)*(byte *)(dword_dd10c + 0xd + (&unk_dc640)[local_3c] * 0x1a) % 2 == 0) {
            iVar10 = 0xa5;
          }
          else {
            iVar10 = 0x14a;
          }
          if (*(byte *)(dword_dd10c + 0xd + (&unk_dc640)[local_3c] * 0x1a) < 2) {
            uVar8 = 0;
          }
          else {
            uVar8 = 0x140;
          }
          if (local_3c < 0xc) {
            iVar6 = 6;
            iVar3 = local_3c;
          }
          else {
            iVar3 = local_3c + -0xc;
            iVar6 = 7;
          }
          dword_c65b4 = dword_c65b0;
          fillrect2(uVar8,iVar10 + (iVar3 % iVar6) * 0xd,0x140,0xd,0x80);
        }
        else {
          dword_c65b0 = (&dword_dc7b8)[local_3c];
          dword_c65b4 = local_3c;
          if ((&dword_dc7b8)[local_3c] != 0x1a) {
            sub_27bc3(&local_3c,0);
          }
        }
        iVar10 = (*(code *)local_54[(int)local_40][local_44 * 8 + 5])();
        local_54[3] = (int *)0x0;
        local_54[2] = (int *)0x0;
        local_54[1] = (int *)0x0;
        local_74[6] = 0;
        local_74[5] = 0;
        local_74[4] = 0;
        local_74[3] = 0;
        local_74[2] = 0;
        local_74[1] = 0;
        if (iVar10 != 1) {
          if (dword_c6956 == 0) {
            iVar10 = 0;
            do {
              if (local_38 == (&unk_dc640)[iVar10]) {
                local_3c = iVar10;
              }
              iVar10 = iVar10 + 1;
            } while (iVar10 < 0x1a);
            if ((uint)*(byte *)(dword_dd10c + 0xd + (&unk_dc640)[local_3c] * 0x1a) % 2 == 0) {
              iVar10 = 0xa5;
            }
            else {
              iVar10 = 0x14a;
            }
            if (*(byte *)((&unk_dc640)[local_3c] * 0x1a + 0xd + dword_dd10c) < 2) {
              uVar8 = 0;
            }
            else {
              uVar8 = 0x140;
            }
            if (local_3c < 0xc) {
              iVar6 = 6;
              iVar3 = local_3c;
            }
            else {
              iVar3 = local_3c + -0xc;
              iVar6 = 7;
            }
            fillrect2(uVar8,iVar10 + (iVar3 % iVar6) * 0xd,0x140,0xd,0x80);
          }
          else {
            local_3c = dword_c65b4;
            if ((&dword_dc7b8)[dword_c65b4] != 0x1a) {
              sub_27bc3(&local_3c,0);
            }
          }
          ppppuVar1 = local_18;
          iVar10 = local_1c;
          setmousepos(local_1c,local_18);
          local_30 = iVar10;
          local_34 = ppppuVar1;
          sub_6b3d7();
          pppppuVar17 = (undefined4 *****)local_20;
          goto LAB_0001e24d;
        }
        goto LAB_0001defd;
      }
      drawshape(local_20,local_1c,local_18);
      sub_6b94e(local_54[(int)local_40] + local_74[(int)local_40] * 8,local_a4[(int)local_40 * 2],
                local_a4[(int)local_40 * 2 + 1],unaff_EBX,unaff_ECX,param_5);
      ppppuVar1 = local_40;
      local_74[(int)local_40] = local_44;
      iVar10 = local_a4[(int)ppppuVar1 * 2 + 1];
      iVar3 = local_a4[(int)ppppuVar1 * 2];
      piVar4 = local_54[(int)ppppuVar1] + local_74[(int)ppppuVar1] * 8;
      uVar8 = unaff_ECX;
    }
    sub_6b9eb(piVar4,iVar3,iVar10,unaff_EBX,unaff_ECX,param_5);
    pppppuVar17 = (undefined4 *****)local_20;
    unaff_ECX = uVar8;
    goto LAB_0001e24d;
  }
  drawshape(local_20,local_1c,local_18);
  iVar3 = sub_26b5a(local_30,local_34,&local_38);
  if (iVar3 == 0) {
    drawshape(local_20,iVar10,ppppuVar1);
    for (iVar10 = 3; -1 < iVar10; iVar10 = iVar10 + -1) {
      if (local_74[iVar10 + 4] != 0) {
        drawshape(local_74[iVar10 + 4],local_a4[iVar10 * 2],local_a4[iVar10 * 2 + 1]);
        local_a4[iVar10 * 2 + 1] = 0;
        local_a4[iVar10 * 2] = 0;
        freemem(local_74[iVar10 + 4]);
      }
    }
    local_14 = (undefined4 *****)0x0;
    local_54[3] = (int *)0x0;
    local_54[2] = (int *)0x0;
    local_54[1] = (int *)0x0;
    local_74[6] = 0;
    local_74[5] = 0;
    local_74[4] = 0;
    local_74[3] = 0;
    local_74[2] = 0;
    local_74[1] = 0;
    pppppuVar17 = (undefined4 *****)local_20;
  }
  else {
    pppppuVar17 = (undefined4 *****)local_20;
    if (local_3c == local_38) {
      if ((dword_c6956 == 0) || ((&dword_dc7b8)[local_3c] != 0x1a)) {
        for (iVar10 = 3; -1 < iVar10; iVar10 = iVar10 + -1) {
          if (local_74[iVar10 + 4] != 0) {
            drawshape(local_74[iVar10 + 4],local_a4[iVar10 * 2],local_a4[iVar10 * 2 + 1]);
            local_a4[iVar10 * 2 + 1] = 0;
            local_a4[iVar10 * 2] = 0;
            freemem(local_74[iVar10 + 4]);
          }
        }
        if (dword_c6956 == 0) {
          dword_c65b0 = (&unk_dc640)[local_3c];
          dword_c65b4 = dword_c65b0;
          local_38 = dword_c65b0;
        }
        else {
          dword_c65b0 = (&dword_dc7b8)[local_3c];
          dword_c65b4 = local_3c;
        }
        sub_18d03();
        local_74[7] = 0;
LAB_0001defd:
        local_54[3] = (int *)0x0;
        local_54[2] = (int *)0x0;
        local_54[1] = (int *)0x0;
        local_74[6] = 0;
        local_74[5] = 0;
        local_74[4] = 0;
        local_74[3] = 0;
        local_74[2] = 0;
        local_74[1] = 0;
        freemem(local_20);
        return 0;
      }
    }
    else if (dword_c6956 == 0) {
      if ((uint)*(byte *)(dword_dd10c + 0xd + (&unk_dc640)[local_3c] * 0x1a) % 2 == 0) {
        iVar10 = 0xa5;
      }
      else {
        iVar10 = 0x14a;
      }
      if (*(byte *)((&unk_dc640)[local_3c] * 0x1a + 0xd + dword_dd10c) < 2) {
        uVar8 = 0;
      }
      else {
        uVar8 = 0x140;
      }
      if (local_3c < 0xc) {
        iVar6 = 6;
        iVar3 = local_3c;
      }
      else {
        iVar3 = local_3c + -0xc;
        iVar6 = 7;
      }
      fillrect2(uVar8,iVar10 + (iVar3 % iVar6) * 0xd,0x140,0xd,0x80);
      local_3c = local_38;
      if ((uint)*(byte *)(dword_dd10c + 0xd + (&unk_dc640)[local_38] * 0x1a) % 2 == 0) {
        iVar10 = 0xa5;
      }
      else {
        iVar10 = 0x14a;
      }
      if (*(byte *)(dword_dd10c + 0xd + (&unk_dc640)[local_38] * 0x1a) < 2) {
        uVar8 = 0;
      }
      else {
        uVar8 = 0x140;
      }
      if (local_38 < 0xc) {
        iVar6 = 6;
        iVar3 = local_38;
      }
      else {
        iVar3 = local_38 + -0xc;
        iVar6 = 7;
      }
      fillrect2(uVar8,iVar10 + (iVar3 % iVar6) * 0xd,0x140,0xd,0x80);
      pppppuVar17 = (undefined4 *****)local_20;
    }
    else if (((&dword_dc7b8)[local_38] != 0x1a) && ((&dword_dc7b8)[local_3c] != 0x1a)) {
      sub_27bc3(&local_3c,&local_38);
      pppppuVar17 = (undefined4 *****)local_20;
    }
  }
  goto LAB_0001e24d;
code_r0x0001e2ab:
  uVar8 = 0;
  local_10 = 0;
  if (dword_c6956 == 1) {
    uVar16 = sub_29681(local_30,&local_3c,local_20,local_1c,local_18);
    ppppuVar2 = local_14;
    uVar8 = (undefined4)((ulonglong)uVar16 >> 0x20);
    local_10 = (int)uVar16;
    pppppuVar9 = (undefined4 *****)ppppuVar1;
    if ((short)uVar16 != 0) {
      pppppuVar9 = (undefined4 *****)local_14;
      if ((undefined4 *****)local_14 != (undefined4 *****)0x0) {
        for (; -1 < (int)pppppuVar9; pppppuVar9 = (undefined4 *****)((int)pppppuVar9 + -1)) {
          if (local_74[(int)(pppppuVar9 + 1)] != 0) {
            drawshape(local_74[(int)(pppppuVar9 + 1)],local_a4[(int)pppppuVar9 * 2],
                      local_a4[(int)pppppuVar9 * 2 + 1]);
            local_a4[(int)pppppuVar9 * 2 + 1] = 0;
            local_a4[(int)pppppuVar9 * 2] = 0;
            freemem(local_74[(int)(pppppuVar9 + 1)]);
            local_74[(int)(pppppuVar9 + 1)] = 0;
            local_54[(int)pppppuVar9] = (int *)0x0;
            local_74[(int)(pppppuVar9 + -1)] = 0;
          }
        }
        local_14 = (undefined4 *****)0x0;
      }
      sub_27f9c();
      if ((&dword_dc7b8)[local_3c] != 0x1a) {
        sub_27bc3(&local_3c,0);
      }
      grabshape(local_20,local_1c,local_18);
      uVar8 = extraout_EDX;
      pppppuVar9 = (undefined4 *****)ppppuVar2;
    }
  }
  pppppuVar17 = (undefined4 *****)local_20;
  uVar15 = CONCAT44(uVar8,local_34);
  if (((local_30 == local_1c) && (local_34 == local_18)) && ((short)local_10 == 0))
  goto LAB_0001e287;
  drawshape(local_20,local_1c,local_18);
LAB_0001e24d:
  grabshape(pppppuVar17,local_30,local_34);
  pppppuVar9 = (undefined4 *****)local_34;
  drawshape_remap(dword_dc238,local_30,local_34);
  uVar15 = CONCAT44(extraout_EDX_00,local_34);
  local_1c = local_30;
  local_18 = local_34;
  goto LAB_0001e287;
}


// ================================================================================================
// sub_1ed96 @ 0x1ed96 [__watcall]
// ================================================================================================

undefined4 __watcall
sub_1ed96(int *param_1,undefined4 param_2,undefined4 unaff_EBX,undefined4 unaff_ECX,
         undefined4 param_5)

{
  ulonglong uVar1;
  undefined4 ****ppppuVar2;
  undefined4 ****ppppuVar3;
  int iVar4;
  int *piVar5;
  undefined4 *puVar6;
  undefined4 uVar7;
  int iVar8;
  undefined4 extraout_EDX;
  int extraout_EDX_00;
  undefined4 *****pppppuVar9;
  int iVar10;
  undefined4 *puVar11;
  undefined4 *puVar12;
  undefined4 *puVar13;
  byte bVar14;
  ulonglong uVar15;
  undefined8 uVar16;
  int local_a0 [8];
  int *local_80;
  int local_7c;
  int local_78;
  int local_74;
  int local_60 [9];
  int local_3c;
  int local_38;
  undefined4 ****local_34;
  undefined4 ****local_30;
  int local_2c;
  int local_28;
  int local_24;
  undefined4 *local_20;
  undefined4 ****local_1c;
  undefined4 ****local_18;
  int local_14;
  int local_10;
  
  bVar14 = 0;
  __CHK(0xc0);
  local_38 = 0;
  local_14 = 0;
  local_10 = 0;
  local_74 = 0;
  local_78 = 0;
  local_7c = 0;
  local_60[3] = 0;
  local_60[2] = 0;
  local_60[1] = 0;
  local_60[0] = 0;
  local_60[7] = 0;
  local_60[6] = 0;
  local_60[5] = 0;
  local_60[4] = 0;
  local_a0[1] = 0;
  local_a0[0] = 0;
  pppppuVar9 = (undefined4 *****)(*(int *)((int)dword_dc238 + 2) >> 0x10);
  local_80 = param_1;
  local_20 = (undefined4 *)
             allocmem(aPointer_c0b54,
                      ((int)pppppuVar9 + 1) * (((int)dword_dc238[1] >> 0x10) + 1) + 0x11,0x20);
  puVar11 = local_20 + (uint)bVar14 * -2 + 1;
  puVar6 = dword_dc238 + (uint)bVar14 * -2 + 1;
  *local_20 = *dword_dc238;
  puVar12 = puVar11 + (uint)bVar14 * -2 + 1;
  puVar13 = puVar6 + (uint)bVar14 * -2 + 1;
  *puVar11 = *puVar6;
  *puVar12 = *puVar13;
  puVar12[(uint)bVar14 * -2 + 1] = puVar13[(uint)bVar14 * -2 + 1];
  *(undefined *)(puVar12 + (uint)bVar14 * -2 + 1 + (uint)bVar14 * -2 + 1) =
       *(undefined *)(puVar13 + (uint)bVar14 * -2 + 1 + (uint)bVar14 * -2 + 1);
  *(short *)(local_20 + 1) = *(short *)(dword_dc238 + 1) + 1;
  *(short *)((int)local_20 + 6) = *(short *)((int)dword_dc238 + 6) + 1;
  local_30 = (undefined4 ****)((*local_80 + local_80[2]) / 2);
  local_34 = (undefined4 ****)((local_80[1] + local_80[3]) / 2);
  local_1c = local_30;
  local_18 = local_34;
  if ((byte_dc836 == 'G') || (byte_dc836 == 'g')) {
    for (iVar10 = 0; iVar8 = local_14, iVar10 < dword_dc6b8; iVar10 = iVar10 + 1) {
      pppppuVar9 = (undefined4 *****)(*(int *)(&unk_dc73c + (&unk_dc720)[iVar10] * 4) * 0x34);
      iVar8 = sub_1d6be(&unk_dc837,(int)pppppuVar9 + dword_dd11c + 3);
      if ((iVar8 == 0) &&
         (iVar8 = sub_1d6be(&unk_dc847,(int)pppppuVar9 + dword_dd11c + 0x13), iVar8 == 0)) {
        iVar8 = dword_dc750 + iVar10;
        break;
      }
    }
  }
  else {
    iVar8 = local_14;
    if (byte_dc836 != '\0') {
      for (iVar10 = 0; iVar8 = local_14, iVar10 < dword_dc750; iVar10 = iVar10 + 1) {
        pppppuVar9 = (undefined4 *****)(*(int *)(&unk_dc754 + (&unk_dc6bc)[iVar10] * 4) * 0x34);
        iVar8 = sub_1d6be(&unk_dc837,(int)pppppuVar9 + dword_dd11c + 3);
        if ((iVar8 == 0) &&
           (iVar4 = sub_1d6be(&unk_dc847,(int)pppppuVar9 + dword_dd11c + 0x13), iVar8 = iVar10,
           iVar4 == 0)) break;
      }
    }
  }
  local_14 = iVar8;
  if (local_14 < dword_dc750) {
    iVar10 = local_14 * 0xd + 0x43;
  }
  else {
    iVar10 = (local_14 - dword_dc750) * 0xd + 0x1a8;
  }
  fillrect2(0,iVar10,0x280,0xd,0x80);
  ppppuVar2 = local_1c;
  grabshape(local_20,local_1c,local_18);
  ppppuVar3 = local_18;
  drawshape_remap(dword_dc238,ppppuVar2,local_18);
  setmouselimits(0,0,0x280,0x1e0);
  setmousepos(ppppuVar2,ppppuVar3);
  (*(code *)funcptr_d3078)();
  uVar15 = sub_6b3d7();
LAB_0001f03d:
  uVar7 = 0;
  do {
    uVar16 = sub_6b391((int)uVar15,(int)(uVar15 >> 0x20),pppppuVar9);
    uVar1 = CONCAT44((int)((ulonglong)uVar16 >> 0x20),uVar7);
    if ((int)uVar16 == 0) break;
    pppppuVar9 = &local_34;
    uVar15 = (*dword_ea0dc)();
    uVar7 = (undefined4)uVar15;
    uVar1 = uVar15;
  } while ((uVar15 & 2) == 0);
  puVar6 = local_20;
  uVar15 = CONCAT44((int)(uVar1 >> 0x20),local_34);
  if ((uVar1 & 2) == 0) goto code_r0x0001f065;
  iVar10 = sub_6ba4d(local_30,local_34,&local_80,local_10,&stack0xffffff90,local_a0,&local_3c,
                     local_60 + 8);
  ppppuVar3 = local_18;
  ppppuVar2 = local_1c;
  puVar6 = local_20;
  if (iVar10 == 0) {
    drawshape(local_20,local_1c,local_18);
    iVar10 = sub_24453(local_30,local_34,&local_38);
    if (iVar10 == 0) {
      drawshape(puVar6,ppppuVar2,ppppuVar3);
      for (iVar10 = 3; -1 < iVar10; iVar10 = iVar10 + -1) {
        if (local_60[iVar10] != 0) {
          drawshape(local_60[iVar10],local_a0[iVar10 * 2],local_a0[iVar10 * 2 + 1]);
          local_a0[iVar10 * 2 + 1] = 0;
          local_a0[iVar10 * 2] = 0;
          freemem(local_60[iVar10]);
        }
      }
      local_10 = 0;
      local_74 = 0;
      local_78 = 0;
      local_7c = 0;
      local_60[3] = 0;
      local_60[2] = 0;
      local_60[1] = 0;
      local_60[0] = 0;
      local_60[7] = 0;
      local_60[6] = 0;
      local_60[5] = 0;
    }
    else {
      for (iVar10 = 3; -1 < iVar10; iVar10 = iVar10 + -1) {
        if (local_60[iVar10] != 0) {
          drawshape(local_60[iVar10],local_a0[iVar10 * 2],local_a0[iVar10 * 2 + 1]);
          local_a0[iVar10 * 2 + 1] = 0;
          local_a0[iVar10 * 2] = 0;
          freemem(local_60[iVar10]);
        }
      }
      local_10 = 0;
      local_74 = 0;
      local_78 = 0;
      local_7c = 0;
      local_60[3] = 0;
      local_60[2] = 0;
      local_60[1] = 0;
      local_60[0] = 0;
      local_60[7] = 0;
      local_60[6] = 0;
      local_60[5] = 0;
      if (local_14 == local_38) {
        for (iVar10 = 3; -1 < iVar10; iVar10 = iVar10 + -1) {
          if (local_60[iVar10] != 0) {
            drawshape(local_60[iVar10],local_a0[iVar10 * 2],local_a0[iVar10 * 2 + 1]);
            local_a0[iVar10 * 2 + 1] = 0;
            local_a0[iVar10 * 2] = 0;
            freemem(local_60[iVar10]);
          }
        }
        if (local_38 < dword_dc750) {
          iVar10 = *(int *)(&unk_dc754 + (&unk_dc6bc)[local_38] * 4);
        }
        else {
          iVar10 = *(int *)(&unk_dc73c + (&unk_dc720)[local_38 - dword_dc750] * 4);
        }
        puVar6 = (undefined4 *)(dword_dd11c + iVar10 * 0x34);
        puVar13 = (undefined4 *)&unk_dc834;
        for (iVar8 = 0xd; iVar8 != 0; iVar8 = iVar8 + -1) {
          *puVar13 = *puVar6;
          puVar6 = puVar6 + (uint)bVar14 * -2 + 1;
          puVar13 = puVar13 + (uint)bVar14 * -2 + 1;
        }
        dword_c6a60 = 0;
        dword_dd120 = 0;
        sub_18d0d();
        local_60[7] = extraout_EDX_00;
LAB_0001defd:
        local_7c = local_60[7];
        local_78 = local_60[7];
        local_74 = local_60[7];
        local_60[0] = local_60[7];
        local_60[1] = local_60[7];
        local_60[2] = local_60[7];
        local_60[3] = local_60[7];
        local_60[5] = local_60[7];
        local_60[6] = local_60[7];
        freemem(local_20);
        return 0;
      }
      if (local_14 < dword_dc750) {
        iVar10 = local_14 * 0xd + 0x43;
      }
      else {
        iVar10 = (local_14 - dword_dc750) * 0xd + 0x1a8;
      }
      fillrect2(0,iVar10,0x280,0xd,0x80);
      local_14 = local_38;
      if (local_38 < dword_dc750) {
        iVar10 = local_38 * 0xd + 0x43;
      }
      else {
        iVar10 = (local_38 - dword_dc750) * 0xd + 0x1a8;
      }
      fillrect2(0,iVar10,0x280,0xd,0x80);
    }
  }
  else {
    if ((&local_80)[local_3c][local_60[8] * 8 + 5] == 0) {
      if ((&local_80)[local_3c][local_60[8] * 8 + 6] == 0) {
        drawshape(local_20,local_1c,local_18);
        sub_6b94e((&local_80)[local_3c] + local_60[local_3c + 4] * 8,local_a0[local_3c * 2],
                  local_a0[local_3c * 2 + 1],unaff_EBX,unaff_ECX,param_5);
        iVar10 = local_3c;
        local_60[local_3c + 4] = local_60[8];
        uVar7 = unaff_ECX;
        goto LAB_0001f482;
      }
      drawshape(local_20,local_1c,local_18);
      iVar10 = local_10;
      uVar7 = unaff_ECX;
      if (local_10 != local_3c) {
        for (; local_3c < iVar10; iVar10 = iVar10 + -1) {
          local_60[iVar10 + 4] = 0;
          if (local_60[iVar10] != 0) {
            drawshape(local_60[iVar10],local_a0[iVar10 * 2],local_a0[iVar10 * 2 + 1]);
            local_a0[iVar10 * 2 + 1] = 0;
            local_a0[iVar10 * 2] = 0;
            freemem(local_60[iVar10]);
            local_60[iVar10] = 0;
            (&local_80)[iVar10] = (int *)0x0;
            *(undefined4 *)(&stack0xffffff90 + iVar10 * 4) = 0;
          }
        }
        local_10 = local_3c;
        uVar7 = unaff_ECX;
      }
      iVar10 = local_10;
      sub_6b94e((&local_80)[local_10] + local_60[local_10 + 4] * 8,local_a0[local_10 * 2],
                local_a0[local_10 * 2 + 1],unaff_EBX,uVar7,param_5);
      iVar8 = local_60[8];
      local_60[iVar10 + 4] = local_60[8];
      sub_6b9eb((&local_80)[iVar10] + iVar8 * 8,local_a0[iVar10 * 2],local_a0[iVar10 * 2 + 1],
                unaff_EBX,uVar7,param_5);
      iVar4 = local_3c;
      iVar8 = local_60[8];
      iVar10 = iVar10 + 1;
      local_10 = iVar10;
      (&local_80)[iVar10] = (int *)(&local_80)[local_3c][local_60[8] * 8 + 6];
      piVar5 = (&local_80)[iVar4] + iVar8 * 8;
      *(int *)(&stack0xffffff90 + iVar10 * 4) = piVar5[7];
      if (iVar10 == 1) {
        iVar10 = *piVar5;
      }
      else {
        iVar10 = piVar5[2];
      }
      local_a0[local_10 * 2] = iVar10 + local_a0[local_10 * 2 + -2];
      if (local_10 == 1) {
        iVar10 = (&local_80)[local_3c][local_60[8] * 8 + 3];
      }
      else {
        iVar10 = (&local_80)[local_3c][local_60[8] * 8 + 1];
      }
      local_24 = local_10 * 8;
      local_a0[local_10 * 2 + 1] = iVar10 + local_a0[local_10 * 2 + -1];
      iVar10 = local_10;
      piVar5 = (&local_80)[local_10];
      local_28 = (piVar5[*(int *)(&stack0xffffff90 + local_10 * 4) * 8 + -6] - *piVar5) + 1;
      local_2c = (piVar5[*(int *)(&stack0xffffff90 + local_10 * 4) * 8 + -5] - piVar5[1]) + 1;
      puVar6 = (undefined4 *)allocmem(aMenubuff_c0b5c,local_28 * local_2c + 0x11,0x20);
      local_60[iVar10] = (int)puVar6;
      puVar11 = puVar6 + (uint)bVar14 * -2 + 1;
      puVar13 = dword_dc238 + (uint)bVar14 * -2 + 1;
      *puVar6 = *dword_dc238;
      puVar12 = puVar11 + (uint)bVar14 * -2 + 1;
      puVar6 = puVar13 + (uint)bVar14 * -2 + 1;
      *puVar11 = *puVar13;
      *puVar12 = *puVar6;
      puVar12[(uint)bVar14 * -2 + 1] = puVar6[(uint)bVar14 * -2 + 1];
      *(undefined *)(puVar12 + (uint)bVar14 * -2 + 1 + (uint)bVar14 * -2 + 1) =
           *(undefined *)(puVar6 + (uint)bVar14 * -2 + 1 + (uint)bVar14 * -2 + 1);
      *(short *)(local_60[iVar10] + 4) = (short)local_28;
      *(short *)(local_60[iVar10] + 6) = (short)local_2c;
      grabshape(local_60[iVar10],*(undefined4 *)((int)local_a0 + local_24),
                *(undefined4 *)((int)local_a0 + local_24 + 4));
      unaff_ECX = uVar7;
      sub_6b684((&local_80)[iVar10],*(undefined4 *)(&stack0xffffff90 + iVar10 * 4),
                *(undefined4 *)((int)local_a0 + local_24),
                *(undefined4 *)((int)local_a0 + local_24 + 4),unaff_EBX,uVar7,param_5);
      local_60[iVar10 + 4] = 0;
      iVar8 = *(int *)((int)local_a0 + local_24 + 4);
      iVar4 = *(int *)((int)local_a0 + local_24);
      piVar5 = (&local_80)[iVar10];
    }
    else {
      if (local_60[8] == local_60[local_3c + 4]) {
        drawshape(local_20,local_1c,local_18);
        for (iVar10 = 3; -1 < iVar10; iVar10 = iVar10 + -1) {
          if (local_60[iVar10] != 0) {
            drawshape(local_60[iVar10],local_a0[iVar10 * 2],local_a0[iVar10 * 2 + 1]);
            local_a0[iVar10 * 2 + 1] = 0;
            local_a0[iVar10 * 2] = 0;
            freemem(local_60[iVar10]);
          }
        }
        local_10 = 0;
        if (local_38 < dword_dc750) {
          iVar10 = *(int *)(&unk_dc754 + (&unk_dc6bc)[local_38] * 4);
        }
        else {
          iVar10 = *(int *)(&unk_dc73c + (&unk_dc720)[local_38 - dword_dc750] * 4);
        }
        puVar6 = (undefined4 *)(dword_dd11c + iVar10 * 0x34);
        puVar13 = (undefined4 *)&unk_dc834;
        for (iVar8 = 0xd; iVar8 != 0; iVar8 = iVar8 + -1) {
          *puVar13 = *puVar6;
          puVar6 = puVar6 + (uint)bVar14 * -2 + 1;
          puVar13 = puVar13 + (uint)bVar14 * -2 + 1;
        }
        if (local_14 < dword_dc750) {
          iVar10 = local_14 * 0xd + 0x43;
        }
        else {
          iVar10 = (local_14 - dword_dc750) * 0xd + 0x1a8;
        }
        fillrect2(0,iVar10,0x280,0xd,0x80);
        iVar10 = (*(code *)(&local_80)[local_3c][local_60[8] * 8 + 5])();
        local_74 = 0;
        local_78 = 0;
        local_7c = 0;
        local_60[3] = 0;
        local_60[2] = 0;
        local_60[1] = 0;
        local_60[0] = 0;
        local_60[7] = 0;
        local_60[6] = 0;
        local_60[5] = 0;
        if (iVar10 != 1) {
          if (byte_dc836 == 'G') {
            for (iVar8 = 0; iVar10 = local_14, iVar8 < dword_dc6b8; iVar8 = iVar8 + 1) {
              iVar10 = *(int *)(&unk_dc73c + (&unk_dc720)[iVar8] * 4);
              iVar4 = sub_1d6be(&unk_dc837,dword_dd11c + iVar10 * 0x34 + 3);
              if ((iVar4 == 0) &&
                 (iVar10 = sub_1d6be(&unk_dc847,dword_dd11c + iVar10 * 0x34 + 0x13), iVar10 == 0)) {
                iVar10 = dword_dc750 + iVar8;
                break;
              }
            }
          }
          else {
            iVar10 = local_14;
            if (byte_dc836 != '\0') {
              for (iVar8 = 0; iVar10 = local_14, iVar8 < dword_dc750; iVar8 = iVar8 + 1) {
                iVar10 = *(int *)(&unk_dc754 + (&unk_dc6bc)[iVar8] * 4);
                iVar4 = sub_1d6be(&unk_dc837,dword_dd11c + iVar10 * 0x34 + 3);
                if ((iVar4 == 0) &&
                   (iVar4 = sub_1d6be(&unk_dc847,dword_dd11c + iVar10 * 0x34 + 0x13), iVar10 = iVar8
                   , iVar4 == 0)) break;
              }
            }
          }
          local_14 = iVar10;
          if (local_14 < dword_dc750) {
            iVar10 = local_14 * 0xd + 0x43;
          }
          else {
            iVar10 = (local_14 - dword_dc750) * 0xd + 0x1a8;
          }
          fillrect2(0,iVar10,0x280,0xd,0x80);
          ppppuVar2 = local_1c;
          setmousepos(local_1c,local_18);
          local_30 = ppppuVar2;
          local_34 = local_18;
          sub_6b3d7();
          goto LAB_0001fa6c;
        }
        goto LAB_0001defd;
      }
      drawshape(local_20,local_1c,local_18);
      sub_6b94e((&local_80)[local_3c] + local_60[local_3c + 4] * 8,local_a0[local_3c * 2],
                local_a0[local_3c * 2 + 1],unaff_EBX,unaff_ECX,param_5);
      iVar10 = local_3c;
      local_60[local_3c + 4] = local_60[8];
      uVar7 = unaff_ECX;
LAB_0001f482:
      iVar8 = local_a0[iVar10 * 2 + 1];
      iVar4 = local_a0[iVar10 * 2];
      piVar5 = (&local_80)[iVar10] + local_60[iVar10 + 4] * 8;
      unaff_ECX = uVar7;
    }
    sub_6b9eb(piVar5,iVar4,iVar8,unaff_EBX,uVar7,param_5);
  }
LAB_0001fa6c:
  grabshape(local_20,local_30,local_34);
  pppppuVar9 = (undefined4 *****)local_30;
  goto LAB_0001f0c3;
code_r0x0001f065:
  if ((local_30 != local_1c) || (local_34 != local_18)) {
    drawshape(local_20,local_1c,local_18);
    grabshape(puVar6,local_30,local_34);
    pppppuVar9 = (undefined4 *****)local_34;
LAB_0001f0c3:
    drawshape_remap(dword_dc238,local_30,local_34);
    uVar15 = CONCAT44(extraout_EDX,local_34);
    local_1c = local_30;
    local_18 = local_34;
  }
  goto LAB_0001f03d;
}


// ================================================================================================
// sub_1faa7 @ 0x1faa7 [__watcall]
// ================================================================================================

void __watcall sub_1faa7(int param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  int iVar1;
  
  __CHK(0x14);
  if (param_1 == 0) {
    _memset_fill(&unk_dcfd8,0,unaff_EBX,0x15,unaff_EDX,unaff_ECX,unaff_EBX);
    iVar1 = 0x15;
    do {
      (&unk_dcfd8)[iVar1] = (char)iVar1 + -0x15;
      iVar1 = iVar1 + 1;
    } while (iVar1 < 0x40);
    iVar1 = 0x40;
    do {
      (&unk_dcfd8)[iVar1] = (char)iVar1;
      iVar1 = iVar1 + 1;
    } while (iVar1 < 0x100);
  }
  else {
    iVar1 = 0;
    do {
      (&unk_dcfd8)[iVar1] = (char)iVar1;
      (&unk_dd058)[iVar1] = (char)iVar1;
      iVar1 = iVar1 + 1;
    } while (iVar1 < 0x80);
  }
  setremaptable(&unk_dcfd8);
  return;
}


// ================================================================================================
// sub_1fb1c @ 0x1fb1c [__watcall]
// ================================================================================================

void __watcall sub_1fb1c(undefined4 param_1,undefined4 param_2,char *unaff_EBX,undefined4 unaff_ECX)

{
  undefined4 extraout_EDX;
  
  __CHK(0x14);
  sprintf((char *)&unk_dd0d8,unaff_EBX,unaff_ECX);
  printstr_at(&unk_dd0d8,param_1,extraout_EDX);
  return;
}


// ================================================================================================
// sub_1fb49 @ 0x1fb49 [__watcall]
// ================================================================================================

void __watcall
sub_1fb49(undefined4 param_1,undefined4 param_2,char *unaff_EBX,undefined4 unaff_ECX,
         undefined4 param_5)

{
  undefined4 extraout_EDX;
  
  __CHK(0x1c);
  sprintf((char *)&unk_dd0d8,unaff_EBX,unaff_ECX,param_5);
  printstr_at(&unk_dd0d8,param_1,extraout_EDX);
  return;
}


// ================================================================================================
// sub_1fb7f @ 0x1fb7f [__watcall]
// ================================================================================================

int __watcall sub_1fb7f(int *param_1,int *unaff_EDX)

{
  ushort uVar1;
  ushort uVar2;
  ushort uVar3;
  ushort *puVar4;
  uint uVar6;
  ushort *puVar7;
  uint uVar5;
  
  __CHK(0x14);
  if (dword_c6956 == 0) {
    puVar4 = (ushort *)(dword_dd110 + *param_1 * 0x2f);
    puVar7 = (ushort *)(dword_dd110 + *unaff_EDX * 0x2f);
  }
  else {
    puVar4 = (ushort *)(*param_1 * 0x2f + dword_dd110 + 0x12);
    puVar7 = (ushort *)(dword_dd110 + *unaff_EDX * 0x2f + 0x12);
  }
  uVar1 = *puVar4;
  if ((uVar1 == 0) == (*puVar7 == 0)) {
    uVar2 = puVar7[3];
    uVar3 = puVar4[3];
    if (uVar2 == puVar4[3]) {
      if (uVar1 != *puVar7) {
        return (uint)uVar1 - (uint)*puVar7;
      }
      uVar2 = puVar7[1];
      uVar3 = puVar4[1];
      if (uVar2 == uVar3) {
        uVar6 = *(int *)(puVar7 + 7) >> 0x10;
        uVar5 = *(int *)(puVar4 + 7) >> 0x10;
        goto LAB_0001fc86;
      }
    }
  }
  else {
    uVar2 = *puVar7;
    uVar3 = uVar1;
  }
  uVar6 = (uint)uVar2;
  uVar5 = (uint)uVar3;
LAB_0001fc86:
  return uVar6 - uVar5;
}


// ================================================================================================
// sub_1fc8f @ 0x1fc8f [__watcall]
// ================================================================================================

int __watcall sub_1fc8f(int *param_1,int *unaff_EDX)

{
  ushort uVar1;
  ushort *puVar2;
  uint uVar3;
  ushort *puVar4;
  ushort uVar5;
  
  __CHK(0x14);
  if (dword_c6956 == 0) {
    puVar2 = (ushort *)(*param_1 * 0x36 + dword_dd114);
    puVar4 = (ushort *)(dword_dd114 + *unaff_EDX * 0x36);
  }
  else {
    puVar2 = (ushort *)(*param_1 * 0x36 + dword_dd114 + 0x16);
    puVar4 = (ushort *)(dword_dd114 + *unaff_EDX * 0x36 + 0x16);
  }
  uVar5 = puVar2[6];
  if ((uVar5 == 0) == (puVar4[6] == 0)) {
    uVar1 = puVar2[8];
    if (puVar4[8] != uVar1) {
      uVar5 = puVar4[8];
LAB_0001fd5d:
      return (uint)uVar1 - (uint)uVar5;
    }
    uVar1 = puVar4[6];
    if (uVar1 == uVar5) {
      uVar1 = *puVar4;
      uVar5 = *puVar2;
      if (uVar1 == uVar5) {
        if (puVar4[7] != puVar2[7]) {
          return (uint)puVar2[7] - (uint)puVar4[7];
        }
        uVar3 = (uint)puVar4[1];
        uVar5 = puVar2[1];
        if (puVar4[1] == uVar5) {
          uVar1 = puVar2[2];
          if (puVar4[2] != uVar1) {
            uVar5 = puVar4[2];
            goto LAB_0001fd5d;
          }
          uVar3 = (uint)puVar4[10];
          uVar5 = puVar2[10];
        }
        goto LAB_0001fdf0;
      }
    }
  }
  else {
    uVar1 = puVar4[6];
  }
  uVar3 = (uint)uVar1;
LAB_0001fdf0:
  return uVar3 - uVar5;
}


// ================================================================================================
// sub_1fdfe @ 0x1fdfe [__watcall]
// ================================================================================================

undefined4 __watcall sub_1fdfe(undefined4 param_1,undefined4 unaff_EDX)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int unaff_EDI;
  undefined auStack_40 [4];
  short sStack_3c;
  short sStack_3a;
  undefined local_2c [4];
  undefined4 local_28;
  uint local_24;
  int local_20;
  undefined4 local_1c;
  int iStack_18;
  
  __CHK(0x54);
  local_28 = 0xffffffff;
  iVar3 = 0;
  local_1c = 0;
  iStack_18 = file_open_read(param_1,&local_28);
  if (iStack_18 == 0) {
    iStack_18 = file_read(local_28,&local_24,4,2);
    local_24 = local_24 & 0xffff;
  }
  if (iStack_18 == 0) {
    iVar4 = local_24 << 3;
    iVar3 = allocmem(&aSfh,iVar4,0x20);
    iStack_18 = file_read(local_28,iVar3,6,iVar4);
  }
  if (iStack_18 == 0) {
    local_20 = iStack_18;
    iVar4 = 0;
    while ((iVar4 < (int)local_24 && (local_20 == 0))) {
      memcpy(local_2c,(void *)(iVar4 * 4 + iVar3),4);
      iVar1 = sub_91fbc(local_2c,unaff_EDX,4);
      if (iVar1 == 0) {
        local_20 = -1;
        unaff_EDI = local_24 * 8 + 6 + *(int *)(iVar4 * 4 + local_24 * 4 + iVar3);
        iStack_18 = file_read(local_28,auStack_40,unaff_EDI,0x11);
      }
      iVar4 = iVar4 + 1;
    }
  }
  if (iVar3 != 0) {
    freemem(iVar3);
  }
  if ((iStack_18 == 0) && (local_20 != 0)) {
    iVar3 = (int)sStack_3a * (int)sStack_3c + 0x11;
    uVar2 = allocmem(aShape,iVar3,0x20);
    local_1c = uVar2;
    iVar3 = file_read(local_28,uVar2,unaff_EDI,iVar3);
    if (iVar3 < 0) {
      freemem(uVar2);
      local_1c = 0;
    }
  }
  file_close(&local_28);
  return local_1c;
}


// ================================================================================================
// sub_1ff86 @ 0x1ff86 [__watcall]
// ================================================================================================

void __watcall sub_1ff86(char *param_1,char *unaff_EDX,int unaff_EBX,char *unaff_ECX)

{
  size_t sVar1;
  
  __CHK(0x18);
  if (byte_c671c == '\x01') {
    unaff_ECX = s__93____94_Season_000c671d;
LAB_0001ffa7:
    unaff_ECX = unaff_ECX + 1;
    unaff_EBX = 0;
  }
  else {
    if (byte_c672f == '\x01') {
      unaff_ECX = s__93____94_Play_Offs_000c6730 + 1;
    }
    else {
      if (byte_c6745 == '\x01') {
        unaff_ECX = s__WWWWWWWW__Season_000c6746;
        goto LAB_0001ffa7;
      }
      if (byte_c6759 == '\x01') {
        unaff_ECX = s__WWWWWWWW__Season_Play_Offs_000c675a + 1;
      }
      else {
        if (byte_c6777 != '\x01') goto LAB_0001ffee;
        unaff_ECX = s__WWWWWWWW__Play_Offs_000c6778 + 1;
      }
    }
    unaff_EBX = 1;
  }
LAB_0001ffee:
  sVar1 = strlen(unaff_ECX);
  strncpy(param_1,unaff_ECX,sVar1 - unaff_EBX);
  param_1[sVar1 - unaff_EBX] = '\0';
  strcat(param_1,unaff_EDX);
  return;
}


// ================================================================================================
// sub_20016 @ 0x20016 [__watcall]
// ================================================================================================

undefined8 __watcall sub_20016(undefined4 param_1,undefined4 unaff_EDX)

{
  undefined *puVar1;
  undefined auStack_320 [768];
  undefined auStack_20 [16];
  
  __CHK(0x330);
  dword_dc738 = 1;
  dword_c65b8 = sub_235be;
  dword_c65b0 = param_1;
  getpalette(0,0x100,auStack_320);
  fade_palette(1,auStack_320,0x10);
  setdefaultscreen();
  sub_1faa7(1);
  sub_235be(param_1);
  sub_6b5e4(&unk_cf78f,4,0x40,0x41,0x42);
  puVar1 = off_d2c6b;
  if (byte_ed85a != '\x01') {
    puVar1 = (undefined *)0x0;
  }
  make_path(auStack_20,puVar1,aEmbpal,0);
  dword_dd104 = loadshapes(auStack_20,0);
  dword_dd100 = locateshape(dword_dd104,&aPal_c0c3b);
  memcpy(auStack_320,(void *)(dword_dd100 + 0x10),0x300);
  freemem(dword_dd104);
  fade_palette(0,auStack_320,0x10);
  sub_1d6e8(&unk_cf78f,4,0x40,0x41,0x42);
  getpalette(0,0x100,auStack_320);
  fade_palette(1,auStack_320,0x10);
  dword_dc738 = 0;
  dword_c65b8 = (code *)0x0;
  return CONCAT44(unaff_EDX,2);
}


