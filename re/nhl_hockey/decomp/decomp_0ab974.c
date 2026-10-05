// Decompiled by Ghidra from hockey.elf (via ledisasm ELF export)
// This is machine generated pseudo-C meant as a reference for porting, it does not compile as is.
#include "prototypes.h"

// ================================================================================================
// sub_ab974 @ 0xab974 [__watcall]
// ================================================================================================

longlong __watcall sub_ab974(undefined4 param_1,uint unaff_EDX)

{
  byte bVar1;
  uint uVar2;
  byte bVar3;
  int *piVar4;
  uint uVar5;
  
  piVar4 = &unk_f5bf8;
  for (uVar5 = 0; uVar5 < word_f79a0; uVar5 = uVar5 + 1) {
    if (((*(byte *)((int)piVar4 + 0x13) & 1) != 0) &&
       ((*(char *)(*piVar4 + 0x47) != '\0' ||
        ((&unk_f5a01)[(uint)*(byte *)((int)piVar4 + 0x1d) * 0x10] != '\0')))) {
      uVar2 = ((uint)*(byte *)((int)piVar4 + 0x17) * (*(int *)((int)piVar4 + 10) >> 0x10)) /
              (uint)*(byte *)((int)piVar4 + 0x1a);
      switch(*(undefined *)((int)piVar4 + 0x19)) {
      case 1:
        uVar2 = (*(int *)((int)piVar4 + 10) >> 0x10) - uVar2;
        break;
      case 2:
        uVar2 = -uVar2;
        break;
      case 3:
        uVar2 = -((*(int *)((int)piVar4 + 10) >> 0x10) - uVar2);
      }
      if ((*(char *)(piVar4 + 6) != '\0') && (bVar3 = *(byte *)(*piVar4 + 0x45), bVar3 != 0)) {
        bVar1 = *(byte *)(piVar4 + 6);
        *(byte *)(piVar4 + 6) = bVar1 - 1;
        uVar2 = (int)(uVar2 * ((uint)bVar3 - (uint)bVar1)) / (int)(uint)*(byte *)(*piVar4 + 0x45);
      }
      sub_aa200(word_d8770,uVar5);
      sub_aa200(word_d8772,1);
      sub_b19c7(word_d8774,(*(ushort *)((int)piVar4 + 10) + uVar2) * 2);
      bVar3 = *(char *)((int)piVar4 + 0x17) + 1;
      *(byte *)((int)piVar4 + 0x17) = bVar3;
      if (*(byte *)((int)piVar4 + 0x1a) <= bVar3) {
        *(undefined *)((int)piVar4 + 0x17) = 0;
        *(char *)((int)piVar4 + 0x19) = (char)((*(byte *)((int)piVar4 + 0x19) + 1) % 4);
      }
    }
    piVar4 = (int *)((int)piVar4 + 0x21);
  }
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// sub_abab0 @ 0xabab0 [__watcall]
// ================================================================================================

void __watcall
sub_abab0(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  sub_b1a04(sub_ab974,0xbb,unaff_EBX,unaff_ECX,unaff_EDX);
  return;
}


// ================================================================================================
// sub_abacc @ 0xabacc [__watcall]
// ================================================================================================

void __watcall sub_abacc(void)

{
  sub_b1bf8();
  return;
}


// ================================================================================================
// sub_abad8 @ 0xabad8 [__watcall]
// ================================================================================================

void __watcall sub_abad8(int param_1,int unaff_EDX,int unaff_EBX)

{
  uint uVar1;
  byte bVar2;
  undefined uVar3;
  ulonglong uVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  
  unaff_EBX = unaff_EBX * 0x10;
  param_1 = param_1 * 0x21;
  uVar7 = (uint)(byte)(&unk_f5a01)[unaff_EBX];
  iVar6 = *(int *)((int)&unk_f5bf8 + param_1);
  if (uVar7 == 0) {
    uVar7 = (uint)*(byte *)(iVar6 + 0x47);
    uVar3 = *(undefined *)(iVar6 + 0x45);
    bVar2 = *(byte *)(iVar6 + 0x46);
  }
  else {
    bVar2 = (&DAT_000f5a02)[unaff_EBX];
    uVar3 = (&DAT_000f5a03)[unaff_EBX];
  }
  uVar5 = ((uint)bVar2 * 0x91e + 5000) / 100;
  uVar1 = uVar5 * 4;
  (&DAT_000f5c12)[param_1] = (char)(0xb0e9 / (ulonglong)uVar1);
  (&DAT_000f5c12)[param_1] =
       (&DAT_000f5c12)[param_1] + (uVar5 * 2 < (uint)(0xb0e9 % (ulonglong)uVar1));
  if ((&DAT_000f5c12)[param_1] == '\0') {
    (&DAT_000f5c12)[param_1] = 1;
  }
  uVar4 = (ulonglong)uVar7 / 0x15;
  uVar1 = (int)uVar4 + 1;
  iVar6 = *(int *)(&unk_d7abc + (int)(uVar4 % 0xc) * 4) << (sbyte)(uVar4 / 0xc);
  *(short *)(&DAT_000f5c04 + param_1) =
       (short)(((uint)*(ushort *)((int)&DAT_000f5c02 + param_1) *
                ((((*(int *)(&unk_d7abc + (uVar1 % 0xc) * 4) << (sbyte)(uVar1 / 0xc)) - iVar6) *
                 (uVar7 % 0x15)) / 0x15 + iVar6) >> 10) -
               (uint)*(ushort *)((int)&DAT_000f5c02 + param_1) >> 1);
  if (unaff_EDX != 0) {
    (&DAT_000f5c0f)[param_1] = 0;
    (&DAT_000f5c11)[param_1] = 0;
    (&DAT_000f5c10)[param_1] = uVar3;
  }
  return;
}


// ================================================================================================
// sub_abc38 @ 0xabc38 [__watcall]
// ================================================================================================

void __watcall sub_abc38(int param_1,int unaff_EDX)

{
  int iVar1;
  byte bVar2;
  byte bVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  undefined local_18;
  
  param_1 = param_1 * 0x21;
  uVar7 = (uint)(byte)(&unk_f5a04)[unaff_EDX * 0x10];
  if (uVar7 == 0) {
    iVar1 = *(int *)((int)&unk_f5bf8 + param_1);
    uVar7 = (uint)*(byte *)(iVar1 + 0x44);
    bVar3 = *(byte *)(iVar1 + 0x43);
  }
  else {
    bVar3 = (&DAT_000f5a05)[unaff_EDX * 0x10];
  }
  uVar4 = ((uint)*(byte *)(*(int *)((int)&unk_f5bf8 + param_1) + 0x3e) *
          (uint)*(ushort *)((int)&DAT_000f5c09 + param_1)) / 0xff;
  uVar5 = uVar7 + 1 >> 3;
  uVar7 = uVar7 + 1 >> 4;
  if (uVar4 - uVar7 < 5) {
    uVar4 = uVar7 + 5;
  }
  uVar6 = uVar5 & 1;
  if (0xfb < uVar4 + uVar7 + uVar6) {
    uVar4 = (0xfb - uVar7) - uVar6;
  }
  (&DAT_000f5c06)[param_1] = (char)uVar4 - (char)uVar7;
  local_18 = (undefined)uVar5;
  uVar7 = CONCAT11(local_18,(char)uVar4 + (char)uVar7) & 0xffff01ff;
  bVar2 = (char)uVar7 + (char)(uVar7 >> 8);
  (&DAT_000f5c07)[param_1] = bVar2;
  uVar7 = 0;
  uVar5 = (int)(5000000 / (ulonglong)((uint)bVar3 * 0x91e + 5000)) * 100000;
  for (uVar4 = (uint)word_f79a0 * 0x10 * ((uint)bVar2 - (uint)(byte)(&DAT_000f5c06)[param_1]) * 0x10
      ; (uVar7 < 4 && (uVar4 <= uVar5)); uVar4 = uVar4 << 3) {
    uVar7 = uVar7 + 1;
  }
  if (3 < uVar7) {
    uVar7 = 3;
  }
  bVar3 = (byte)(((uVar5 >> 1) + uVar4) / uVar5);
  (&DAT_000f5c08)[param_1] = bVar3;
  if (0x3f < bVar3) {
    (&DAT_000f5c08)[param_1] = 0x3f;
  }
  (&DAT_000f5c08)[param_1] = (&DAT_000f5c08)[param_1] | (char)uVar7 << 6;
  return;
}


// ================================================================================================
// sub_abd60 @ 0xabd60 [__watcall]
// ================================================================================================

uint __watcall sub_abd60(uint param_1,uint unaff_EDX,int unaff_EBX)

{
  uint uVar1;
  uint uVar2;
  int extraout_EDX;
  byte in_CF;
  byte in_PF;
  byte in_AF;
  byte in_ZF;
  byte in_SF;
  byte in_TF;
  byte in_IF;
  byte in_OF;
  byte in_NT;
  ushort uVar3;
  
  uVar3 = (ushort)(in_NT & 1) * 0x4000 | (ushort)(in_OF & 1) * 0x800 | (ushort)(in_IF & 1) * 0x200 |
          (ushort)(in_TF & 1) * 0x100 | (ushort)(in_SF & 1) * 0x80 | (ushort)(in_ZF & 1) * 0x40 |
          (ushort)(in_AF & 1) * 0x10 | (ushort)(in_PF & 1) * 4 | (ushort)(in_CF & 1);
  sub_b122f();
  uVar1 = (param_1 >> 1) + ((uint)((extraout_EDX >> 1) + unaff_EBX * 0x200) / unaff_EDX) * 0x200;
  uVar2 = uVar1 / param_1;
  sub_b1256(uVar2,uVar1 % param_1,uVar2,unaff_EDX,uVar3);
  return uVar2;
}


// ================================================================================================
// sub_abda0 @ 0xabda0 [__watcall]
// ================================================================================================

int __watcall sub_abda0(int param_1,int unaff_EDX)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  
  uVar2 = (unaff_EDX - (uint)*(ushort *)(param_1 + 0x18)) * (uint)*(ushort *)(param_1 + 0x1c);
  iVar3 = ((int)uVar2 >> 10) + (uint)*(ushort *)(param_1 + 0x18);
  uVar2 = uVar2 & 0x3ff;
  if (iVar3 < 0) {
    iVar3 = 0;
  }
  iVar1 = dword_d89d8;
  if (iVar3 < 0x80) {
    iVar1 = (&unk_d87dc)[iVar3];
    if (0x5e < iVar3) {
      return ((iVar1 >> 5) + ((int)(((&unk_d87e0)[iVar3] - (iVar1 >> 5)) * uVar2) >> 10)) * 0x20;
    }
    iVar1 = iVar1 + ((int)(uVar2 * ((&unk_d87e0)[iVar3] - iVar1)) >> 10);
  }
  return iVar1;
}


// ================================================================================================
// sub_abe18 @ 0xabe18 [__watcall]
// ================================================================================================

void __watcall
sub_abe18(undefined4 param_1,undefined4 param_2,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  byte bVar1;
  int iVar2;
  undefined2 uVar3;
  uint uVar4;
  int extraout_EDX;
  byte in_CF;
  byte in_PF;
  byte in_AF;
  byte in_ZF;
  byte in_SF;
  byte in_TF;
  byte in_IF;
  byte in_OF;
  byte in_NT;
  
  sub_b122f(param_1,param_1,unaff_EBX,unaff_ECX,
            (ushort)(in_NT & 1) * 0x4000 | (ushort)(in_OF & 1) * 0x800 | (ushort)(in_IF & 1) * 0x200
            | (ushort)(in_TF & 1) * 0x100 | (ushort)(in_SF & 1) * 0x80 | (ushort)(in_ZF & 1) * 0x40
            | (ushort)(in_AF & 1) * 0x10 | (ushort)(in_PF & 1) * 4 | (ushort)(in_CF & 1));
  iVar2 = extraout_EDX * 0x21;
  bVar1 = (&unk_f5c0b)[iVar2];
  if ((bVar1 & 1) != 0) {
    (&unk_f5c0b)[iVar2] = bVar1 & 0xf1;
    uVar3 = word_d8770;
    (&unk_f5c0b)[iVar2] = bVar1 & 0xf1 | 0xc;
    sub_aa200(uVar3);
    sub_aa200(word_d8772,0xd);
    sub_aa200(word_d8776,3);
    sub_b13a1();
    sub_aa200(word_d8776,3);
    sub_aa200(word_d8772,0x89);
    uVar4 = sub_b1951(word_d8774);
    uVar3 = word_d8772;
    if (5 < uVar4 >> 8) {
      (&DAT_000f5c0d)[iVar2] = 0x40;
      sub_aa200(uVar3,7);
      sub_aa200(word_d8776,5);
      sub_aa200(word_d8772,6);
      sub_aa200(word_d8776,0x3f);
      sub_aa200(word_d8772,0xd);
      sub_aa200(word_d8776,(&DAT_000f5c0d)[iVar2]);
      sub_b13a1();
      sub_aa200(word_d8776,(&DAT_000f5c0d)[iVar2]);
    }
  }
  sub_b1256();
  return;
}


// ================================================================================================
// sub_abf5c @ 0xabf5c [__watcall]
// ================================================================================================

void __watcall sub_abf5c(int param_1)

{
  int iVar1;
  uint uVar2;
  int *piVar3;
  undefined extraout_DL;
  uint extraout_EDX;
  byte in_CF;
  byte in_PF;
  byte in_AF;
  byte in_ZF;
  byte in_SF;
  byte in_TF;
  byte in_IF;
  byte in_OF;
  byte in_NT;
  ushort uVar4;
  
  uVar4 = (ushort)(in_NT & 1) * 0x4000 | (ushort)(in_OF & 1) * 0x800 | (ushort)(in_IF & 1) * 0x200 |
          (ushort)(in_TF & 1) * 0x100 | (ushort)(in_SF & 1) * 0x80 | (ushort)(in_ZF & 1) * 0x40 |
          (ushort)(in_AF & 1) * 0x10 | (ushort)(in_PF & 1) * 4 | (ushort)(in_CF & 1);
  sub_b122f();
  iVar1 = param_1 * 0x21;
  piVar3 = (int *)((int)&unk_f5bf8 + iVar1);
  if (((&unk_f5c0b)[iVar1] & 1) != 0) {
    sub_aa200(word_d8770,param_1,param_1,piVar3,uVar4);
    do {
      sub_aa200(word_d8772,0x8d,param_1,piVar3,uVar4);
      uVar2 = sub_b128c(word_d8776);
    } while ((uVar2 & 3) == 0);
    sub_aa200(word_d8772,0);
    sub_aa200(word_d8776,3);
    sub_b13a1();
    sub_aa200(word_d8776,3);
    (&unk_f5c0b)[iVar1] = 0;
    (&DAT_000f5c0e)[iVar1] = 0;
    sub_b1e2c(param_1,extraout_EDX & 0xffffff00);
    (&unk_f5978)[param_1 * 4] = extraout_DL;
    (&unk_f5979)[param_1 * 4] = extraout_DL;
    if ((*(char *)(*piVar3 + 0x47) != '\0') ||
       ((&unk_f5a01)[(uint)(byte)(&DAT_000f5c15)[iVar1] * 0x10] != '\0')) {
      word_f611a = word_f611a + -1;
      if (word_f611a == 0) {
        sub_abacc();
      }
    }
  }
  sub_b1256();
  return;
}


// ================================================================================================
// sub_ac050 @ 0xac050 [__watcall]
// ================================================================================================

void __watcall sub_ac050(int param_1)

{
  int iVar1;
  int extraout_EDX;
  int extraout_EDX_00;
  int iVar2;
  
  sub_b122f();
  iVar1 = 0;
  do {
    if (*(int *)(&unk_f6016 + param_1 * 8 + iVar1 * 2) >> 0x10 != -1) {
      sub_abe18();
      iVar1 = extraout_EDX;
    }
    iVar1 = iVar1 + 1;
  } while (iVar1 < 4);
  iVar1 = 0;
  do {
    iVar2 = *(int *)(&unk_f6016 + param_1 * 8 + iVar1 * 2) >> 0x10;
    if ((iVar2 != -1) && (((&unk_f5c0b)[iVar2 * 0x21] & 1) != 0)) {
      sub_abf5c(iVar2);
      iVar1 = extraout_EDX_00;
    }
    iVar1 = iVar1 + 1;
  } while (iVar1 < 4);
  sub_b1256();
  return;
}


// ================================================================================================
// sub_ac0cc @ 0xac0cc [__watcall]
// ================================================================================================

void __watcall sub_ac0cc(uint param_1,undefined4 unaff_EDX,int unaff_EBX,int unaff_ECX,uint param_5)

{
  undefined uVar1;
  char cVar2;
  undefined2 uVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  short sVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  uint uVar11;
  int iVar12;
  int *piVar13;
  byte in_AF;
  bool bVar14;
  byte in_TF;
  byte in_IF;
  byte in_NT;
  ushort uVar15;
  int local_44 [4];
  uint local_34;
  int local_1c;
  
  if (unaff_ECX == 0) {
    sub_ac6e8(unaff_EBX,param_5);
  }
  else {
    iVar4 = param_5 * 0x10;
    if (param_1 == 0) {
      param_1 = (&unk_f59fc)[param_5 * 4];
    }
    if (param_1 != 0) {
      uVar15 = (ushort)(in_NT & 1) * 0x4000 | (ushort)(in_IF & 1) * 0x200 |
               (ushort)(in_TF & 1) * 0x100 | (ushort)((int)param_1 < 0) * 0x80 |
               (ushort)(param_1 == 0) * 0x40 | (ushort)(in_AF & 1) * 0x10 |
               (ushort)((POPCOUNT(param_1 & 0xff) & 1U) == 0) * 4;
      sub_b122f();
      uVar10 = 0xffffffff;
      piVar6 = (int *)0x0;
      iVar5 = *(int *)(param_1 - 2) >> 0x10;
      local_44[0] = -1;
      local_1c = 0;
      if (iVar5 < 1) {
        iVar4 = 0;
      }
      else {
        do {
          local_44[local_1c] = -1;
          piVar13 = *(int **)(param_1 + 2 + local_1c * 4);
          if (*(short *)(piVar13 + 7) == 0x400) {
            uVar10 = (&unk_d87dc)[unaff_EBX];
          }
          else {
            uVar10 = sub_abda0(piVar13,unaff_EBX,uVar10,piVar6,uVar15);
          }
          if (*(short *)(param_1 + 0x1a) != 0x400) {
            piVar6 = (int *)0x0;
            uVar11 = uVar10;
            if (0x7ffff < (int)uVar10) {
              uVar11 = (int)uVar10 >> 4;
              piVar6 = (int *)0x1;
              if (0x7ffff < (int)uVar11) {
                piVar6 = (int *)0x2;
                uVar11 = (int)uVar10 >> 8;
              }
            }
            uVar10 = uVar11 * *(ushort *)(param_1 + 0x1a) + 0x200 >> 10;
            if (piVar6 != (int *)0x0) {
              uVar10 = uVar10 << 4;
              piVar6 = (int *)((int)piVar6 + -1);
            }
            if (piVar6 != (int *)0x0) {
              uVar10 = uVar10 << 4;
            }
          }
          iVar12 = *(int *)(param_1 + 0x10 + local_1c * 2) >> 0x10;
          iVar8 = 0;
          while ((iVar8 < iVar12 &&
                 (((piVar6 = (int *)((int)piVar13 + 0x49), piVar13[3] < (int)uVar10 ||
                   ((int)uVar10 < piVar13[2])) ||
                  ((iVar8 < iVar12 + -1 &&
                   (((int)uVar10 <= *(int *)((int)piVar13 + 0x55) &&
                    (*(int *)((int)piVar13 + 0x51) <= (int)uVar10))))))))) {
            iVar8 = iVar8 + 1;
            piVar13 = piVar6;
          }
          if ((iVar8 != iVar12) && (iVar12 = sub_b1cbc(unaff_EDX,sub_ac050), iVar12 != -1)) {
            local_44[local_1c] = iVar12;
            (&unk_f5979)[iVar12 * 4] = (char)unaff_EBX;
            (&unk_f5978)[iVar12 * 4] = 0;
            (&unk_f597a)[iVar12 * 4] = (undefined)param_5;
            iVar8 = iVar12 * 0x21;
            piVar6 = (int *)((int)&unk_f5bf8 + iVar8);
            (&DAT_000f5c15)[iVar8] = (undefined)param_5;
            cVar2 = byte_d7aec;
            if (unaff_ECX < 1) {
              unaff_ECX = 1;
            }
            else if (0x7f < unaff_ECX) {
              unaff_ECX = 0x7f;
            }
            (&DAT_000f5c14)[iVar8] = (char)unaff_ECX;
            if (cVar2 == '\0') {
              iVar9 = ((byte)(&unk_f59f9)[iVar4] + 0x80) *
                      (unaff_ECX + 0x80) * ((dword_f6116 >> 0x10) + 0x40);
            }
            else {
              local_34 = (uint)(byte)(&unk_f59f9)[iVar4];
              iVar9 = (uint)(byte)(&unk_d7a3c)[unaff_ECX] * ((dword_f6116 >> 0x10) + 0x40) *
                      (uint)(byte)(&unk_d7a3c)[local_34];
            }
            *(short *)((int)&DAT_000f5c09 + iVar8) = (short)(iVar9 / 0xbe41);
            *piVar6 = (int)piVar13;
            uVar3 = sub_abd60(*(undefined2 *)((int)piVar13 + 0x2e),piVar13[4]);
            *(undefined2 *)((int)&DAT_000f5c00 + iVar8) = uVar3;
            if ((&unk_f59fa)[param_5 * 8] == 0x400) {
              uVar3 = *(undefined2 *)((int)&DAT_000f5c00 + iVar8);
            }
            else {
              uVar3 = (undefined2)
                      ((uint)*(ushort *)((int)&DAT_000f5c00 + iVar8) *
                       (uint)(ushort)(&unk_f59fa)[param_5 * 8] >> 10);
            }
            *(undefined2 *)((int)&DAT_000f5c02 + iVar8) = uVar3;
            sub_aa200(word_d8770,iVar12);
            sub_aa200(word_d8772,1);
            sub_b19c7(word_d8774,(uint)*(ushort *)((int)&DAT_000f5c02 + iVar8) * 2);
            sub_aa200(word_d8772,0xc);
            if ((&unk_f5a00)[iVar4] == '\x10') {
              uVar1 = *(undefined *)((int)piVar13 + 0x35);
            }
            else {
              uVar1 = (&unk_f5a00)[iVar4];
            }
            sub_aa200(word_d8776,uVar1);
            (&DAT_000f5c0c)[iVar8] = 0;
            (&DAT_000f5c0d)[iVar8] = 0;
            if ((*(byte *)(piVar13 + 0x12) & 4) != 0) {
              (&DAT_000f5c0c)[iVar8] = (&DAT_000f5c0c)[iVar8] | 8;
            }
            if ((*(byte *)(piVar13 + 0x12) & 1) != 0) {
              (&DAT_000f5c0c)[iVar8] = (&DAT_000f5c0c)[iVar8] | 4;
            }
            if ((*(byte *)(piVar13 + 0x12) & 8) != 0) {
              (&DAT_000f5c0c)[iVar8] = (&DAT_000f5c0c)[iVar8] | 0x10;
            }
            uVar3 = word_d8772;
            if ((*(byte *)(piVar13 + 0x12) & 0x10) == 0) {
              sub_aa200(word_d8772,0xb);
              sub_b19c7(word_d8774,*(undefined2 *)((int)piVar13 + 0x1e));
              sub_aa200(word_d8772,10);
              uVar3 = *(undefined2 *)(piVar13 + 8);
            }
            else {
              (&DAT_000f5c0c)[iVar8] = (&DAT_000f5c0c)[iVar8] | 0x40;
              sub_aa200(uVar3,0xb);
              sub_b19c7(word_d8774,*(undefined2 *)((int)piVar13 + 0x2a));
              sub_aa200(word_d8772,10);
              uVar3 = *(undefined2 *)(piVar13 + 0xb);
            }
            sub_b19c7(word_d8774,uVar3);
            sub_aa200(word_d8772,3);
            sub_b19c7(word_d8774,*(undefined2 *)((int)piVar13 + 0x22));
            sub_aa200(word_d8772,2);
            sub_b19c7(word_d8774,*(undefined2 *)(piVar13 + 9));
            sub_aa200(word_d8772,5);
            sub_b19c7(word_d8774,*(undefined2 *)((int)piVar13 + 0x26));
            sub_aa200(word_d8772,4);
            sub_b19c7(word_d8774,*(undefined2 *)(piVar13 + 10));
            uVar3 = word_d8772;
            (&DAT_000f5c13)[iVar8] = 0;
            sub_aa200(uVar3,6);
            sub_aa200(word_d8776,*(undefined *)((int)piVar13 + 0x36));
            sub_aa200(word_d8772,7);
            sub_aa200(word_d8776,5);
            sub_aa200(word_d8772,8);
            uVar10 = ((uint)*(ushort *)((int)&DAT_000f5c09 + iVar8) * (uint)*(byte *)(piVar13 + 0xf)
                     ) / 0xff;
            if (uVar10 < 5) {
              uVar10 = 5;
            }
            (&DAT_000f5c16)[iVar8] = 0;
            (&DAT_000f5c18)[iVar8] = 0;
            uVar3 = word_d8776;
            (&DAT_000f5c17)[iVar8] = (char)uVar10;
            sub_aa200(uVar3);
            (&DAT_000f5c0d)[iVar8] = (&DAT_000f5c0d)[iVar8] | 0x20;
            if ((*(char *)((int)piVar13 + 0x47) != '\0') ||
               (uVar10 = 0xff, (&unk_f5a01)[iVar4] != '\0')) {
              sub_abad8(iVar12,1);
              sVar7 = word_f611a + 1;
              bVar14 = word_f611a == 0;
              uVar10 = param_5;
              word_f611a = sVar7;
              if (bVar14) {
                sub_abab0();
              }
            }
            if ((*(char *)(piVar13 + 0x11) != '\0') || ((&unk_f5a04)[iVar4] != '\0')) {
              sub_abc38(iVar12,param_5);
            }
            (&unk_f5c0b)[iVar8] = 1;
            uVar3 = word_d8772;
            (&DAT_000f5c0e)[iVar8] = 0;
            sub_aa200(uVar3,0xd);
            sub_aa200(word_d8776,(&DAT_000f5c0d)[iVar8]);
            sub_b13a1();
            sub_aa200(word_d8776,(&DAT_000f5c0d)[iVar8]);
            sub_aa200(word_d8772,0);
            sub_aa200(word_d8776,(&DAT_000f5c0c)[iVar8]);
            sub_b13a1();
            sub_aa200(word_d8776,(&DAT_000f5c0c)[iVar8]);
          }
          local_1c = local_1c + 1;
        } while (local_1c < iVar5);
        iVar4 = 0;
      }
      for (; iVar4 < iVar5; iVar4 = iVar4 + 1) {
        if (local_44[iVar4] != -1) {
          for (iVar12 = 0; iVar12 < iVar5; iVar12 = iVar12 + 1) {
            *(undefined2 *)(&unk_f6018 + local_44[iVar4] * 8 + iVar12 * 2) =
                 *(undefined2 *)(local_44 + iVar12);
          }
          for (; iVar12 < 4; iVar12 = iVar12 + 1) {
            *(undefined2 *)(&unk_f6018 + local_44[iVar4] * 8 + iVar12 * 2) = 0xffff;
          }
        }
      }
      sub_b1256();
    }
  }
  return;
}


// ================================================================================================
// sub_ac6e8 @ 0xac6e8 [__watcall]
// ================================================================================================

void __watcall sub_ac6e8(undefined4 param_1)

{
  byte bVar1;
  int iVar2;
  ushort uVar3;
  ushort uVar4;
  undefined2 uVar5;
  ushort extraout_var;
  uint uVar6;
  int iVar7;
  int iVar8;
  int extraout_EDX;
  uint uVar9;
  int *piVar10;
  int iVar11;
  byte in_AF;
  byte in_TF;
  byte in_IF;
  byte in_NT;
  ushort uVar12;
  undefined4 local_20;
  uint local_1c;
  ushort local_18;
  
  uVar12 = (ushort)(in_NT & 1) * 0x4000 | (ushort)SBORROW4((int)&stack0xffffffec,0xc) * 0x800 |
           (ushort)(in_IF & 1) * 0x200 | (ushort)(in_TF & 1) * 0x100 |
           (ushort)((int)&local_20 < 0) * 0x80 |
           (ushort)(&stack0x00000000 == (undefined *)0x20) * 0x40 | (ushort)(in_AF & 1) * 0x10 |
           (ushort)((POPCOUNT((uint)&local_20 & 0xff) & 1U) == 0) * 4 |
           (ushort)(&stack0xffffffec < (undefined *)0xc);
  local_20 = param_1;
  sub_b122f();
  if (((&unk_f59f8)[extraout_EDX * 0x10] & 1) == 0) {
    iVar7 = 0;
    do {
      if (((char)local_20 == (&unk_f5979)[iVar7 * 4]) &&
         ((char)extraout_EDX == (&unk_f597a)[iVar7 * 4])) break;
      iVar7 = iVar7 + 1;
    } while (iVar7 < 0x20);
    if (iVar7 != 0x20) {
      iVar11 = 0;
      do {
        iVar8 = *(int *)(&unk_f6016 + iVar7 * 8 + iVar11 * 2) >> 0x10;
        if (iVar8 != -1) {
          iVar2 = iVar8 * 0x21;
          piVar10 = (int *)((int)&unk_f5bf8 + iVar2);
          sub_b1e64(iVar8,0x20,piVar10,iVar8,uVar12);
          if ((((&unk_f5c0b)[iVar2] & 1) != 0) && (((&unk_f5c0b)[iVar2] & 4) == 0)) {
            (&unk_f5979)[iVar8 * 4] = 0;
            (&unk_f5978)[iVar8 * 4] = (&unk_f5978)[iVar8 * 4] & 0xfe;
            bVar1 = (&unk_f5c0b)[iVar2];
            (&unk_f5c0b)[iVar2] = bVar1 & 0xf9;
            (&unk_f5c0b)[iVar2] = bVar1 & 0xf9 | 4;
            if ((*(byte *)(*piVar10 + 0x48) & 0x40) == 0) {
              sub_aa200(word_d8770,iVar8);
              bVar1 = (&DAT_000f5c0c)[iVar2];
              (&DAT_000f5c0c)[iVar2] = bVar1 & 0xd7;
              (&DAT_000f5c0c)[iVar2] = bVar1 & 0xd7 | 0x20;
              if ((*(byte *)(*piVar10 + 0x48) & 0x10) == 0) {
                sub_aa200(word_d8772,5);
                local_1c = (uint)*(ushort *)(*piVar10 + 0x2a);
                sub_b19c7(word_d8774,local_1c);
                sub_aa200(word_d8772,4);
                uVar3 = *(ushort *)(*piVar10 + 0x2c);
              }
              else {
                sub_aa200(word_d8772,3);
                local_1c = (uint)*(ushort *)(*piVar10 + 0x1e);
                sub_b19c7(word_d8774,local_1c);
                sub_aa200(word_d8772,2);
                uVar3 = *(ushort *)(*piVar10 + 0x20);
              }
              local_1c = (uint)uVar3;
              sub_b19c7(word_d8774,local_1c);
              sub_aa200(word_d8772,0);
              sub_aa200(word_d8776,(&DAT_000f5c0c)[iVar2]);
              sub_b13a1();
              sub_aa200(word_d8776,(&DAT_000f5c0c)[iVar2]);
            }
            bVar1 = *(byte *)(*piVar10 + 0x48);
            if (((bVar1 & 0x40) == 0) || ((bVar1 & 0x80) != 0)) {
              sub_aa200(word_d8772,0xd);
              sub_aa200(word_d8776,3);
              sub_b13a1();
              sub_aa200(word_d8776,3);
              bVar1 = (&DAT_000f5c0d)[iVar2];
              (&DAT_000f5c13)[iVar2] = 5;
              uVar5 = word_d8772;
              (&DAT_000f5c0d)[iVar2] = bVar1 | 0x60;
              (&DAT_000f5c0d)[iVar2] = bVar1 & 0xe7 | 0x60;
              sub_aa200(uVar5,0x89);
              sub_b1951(word_d8774);
              if ((&DAT_000f5c16)[iVar2] == '\0') {
                local_1c = (uint)*(ushort *)((int)&DAT_000f5c09 + iVar2);
                (&DAT_000f5c16)[iVar2] = (char)(((uint)(extraout_var & 0xff) * 0xff) / local_1c);
              }
              local_18._0_1_ = (byte)extraout_var;
              (&DAT_000f5c18)[iVar2] = (byte)local_18;
              uVar5 = word_d8772;
              (&DAT_000f5c17)[iVar2] = 5;
              local_18 = extraout_var & 0xff;
              sub_aa200(uVar5,6);
              sub_aa200(word_d8776,*(undefined *)(*piVar10 + 0x3b));
              sub_aa200(word_d8772,7);
              uVar9 = 5;
              uVar5 = word_d8776;
            }
            else {
              if ((bVar1 & 0x20) == 0) goto LAB_000acc20;
              sub_aa200(word_d8770,iVar8);
              sub_aa200(word_d8772,0xd);
              sub_aa200(word_d8776,3);
              sub_b13a1();
              sub_aa200(word_d8776,3);
              if ((byte)(&DAT_000f5c13)[iVar2] < 3) {
                (&DAT_000f5c13)[iVar2] = 3;
              }
              bVar1 = (&DAT_000f5c0d)[iVar2];
              (&DAT_000f5c0d)[iVar2] = bVar1 | 0x20;
              uVar5 = word_d8772;
              (&DAT_000f5c0d)[iVar2] = bVar1 & 0xe7 | 0x20;
              sub_aa200(uVar5,6);
              sub_aa200(word_d8776,*(undefined *)(*piVar10 + 0x39));
              sub_aa200(word_d8772,0x89);
              uVar3 = sub_b1951(word_d8774);
              uVar4 = uVar3 >> 8;
              if ((&DAT_000f5c16)[iVar2] == '\0') {
                local_1c = (uint)*(ushort *)((int)&DAT_000f5c09 + iVar2);
                (&DAT_000f5c16)[iVar2] = (char)(((uint)uVar4 * 0xff) / local_1c);
              }
              local_18._0_1_ = (byte)(uVar3 >> 8);
              (&DAT_000f5c18)[iVar2] = (byte)local_18;
              uVar5 = word_d8772;
              local_18 = uVar4;
              if ((byte)local_18 < *(byte *)(*piVar10 + 0x3f)) {
                (&DAT_000f5c0d)[iVar2] = (&DAT_000f5c0d)[iVar2] & 0xbf;
                sub_aa200(uVar5,7);
                sub_aa200(word_d8776,local_18);
                sub_aa200(word_d8772,8);
                uVar5 = word_d8776;
                uVar6 = ((uint)*(byte *)(*piVar10 + 0x3f) *
                        (uint)*(ushort *)((int)&DAT_000f5c09 + iVar2)) / 0xff;
                if (uVar6 < 5) {
                  uVar6 = 5;
                }
                uVar9 = uVar6 & 0xff;
                (&DAT_000f5c17)[iVar2] = (char)uVar6;
              }
              else {
                (&DAT_000f5c0d)[iVar2] = (&DAT_000f5c0d)[iVar2] | 0x40;
                sub_aa200(uVar5,7);
                uVar5 = word_d8776;
                uVar9 = ((uint)*(ushort *)((int)&DAT_000f5c09 + iVar2) *
                        (uint)*(byte *)(*piVar10 + 0x3f)) / 0xff;
                if (uVar9 < 5) {
                  uVar9 = 5;
                }
                (&DAT_000f5c17)[iVar2] = (char)uVar9;
                sub_aa200(uVar5,uVar9 & 0xff);
                sub_aa200(word_d8772,8);
                uVar9 = (uint)local_18;
                uVar5 = word_d8776;
              }
            }
            sub_aa200(uVar5,uVar9);
            sub_aa200(word_d8772,0xd);
            sub_aa200(word_d8776,(&DAT_000f5c0d)[iVar2]);
            sub_b13a1();
            sub_aa200(word_d8776,(&DAT_000f5c0d)[iVar2]);
          }
        }
LAB_000acc20:
        iVar11 = iVar11 + 1;
      } while (iVar11 < 4);
    }
  }
  else {
    iVar7 = 0;
    do {
      iVar11 = iVar7 * 4;
      if (((char)local_20 == (&unk_f5979)[iVar11]) && ((char)extraout_EDX == (&unk_f597a)[iVar11]))
      {
        (&unk_f5978)[iVar11] = (&unk_f5978)[iVar11] | 1;
      }
      iVar7 = iVar7 + 1;
    } while (iVar7 < 0x20);
  }
  sub_b1256();
  return;
}


// ================================================================================================
// sub_acc3c @ 0xacc3c [__watcall]
// ================================================================================================

void __watcall sub_acc3c(uint param_1)

{
  int iVar1;
  int extraout_EDX;
  uint uVar2;
  byte in_CF;
  byte in_PF;
  byte in_AF;
  byte in_ZF;
  byte in_SF;
  byte in_TF;
  byte in_IF;
  byte in_OF;
  byte in_NT;
  ushort uVar3;
  
  uVar3 = (ushort)(in_NT & 1) * 0x4000 | (ushort)(in_OF & 1) * 0x800 | (ushort)(in_IF & 1) * 0x200 |
          (ushort)(in_TF & 1) * 0x100 | (ushort)(in_SF & 1) * 0x80 | (ushort)(in_ZF & 1) * 0x40 |
          (ushort)(in_AF & 1) * 0x10 | (ushort)(in_PF & 1) * 4 | (ushort)(in_CF & 1);
  sub_b122f();
  iVar1 = param_1 * 0x10;
  if (extraout_EDX == 0) {
    (&unk_f59f8)[iVar1] = (&unk_f59f8)[iVar1] & 0xfe;
    for (uVar2 = 0; uVar2 < word_f79a0; uVar2 = uVar2 + 1) {
      iVar1 = uVar2 * 4;
      if ((((char)param_1 == (&unk_f597a)[iVar1]) && (((&unk_f5978)[iVar1] & 1) != 0)) &&
         ((&unk_f5979)[iVar1] != '\0')) {
        sub_ac6e8((&unk_f5979)[iVar1],param_1 & 0xff,uVar2,param_1,uVar3);
      }
    }
  }
  else {
    (&unk_f59f8)[iVar1] = (&unk_f59f8)[iVar1] | 1;
  }
  sub_b1256();
  return;
}


// ================================================================================================
// sub_accc0 @ 0xaccc0 [__watcall]
// ================================================================================================

undefined8 __watcall sub_accc0(int param_1,undefined4 unaff_EDX)

{
  int iVar1;
  undefined2 uVar2;
  undefined4 uVar3;
  
  uVar2 = word_d8770;
  iVar1 = param_1 * 0x21;
  if (((&unk_f5c0b)[iVar1] & 1) == 0) {
    uVar3 = 0;
  }
  else {
    (&DAT_000f5c0c)[iVar1] = (&DAT_000f5c0c)[iVar1] & 0x5f;
    sub_aa200(uVar2,param_1);
    sub_aa200(word_d8772,0);
    sub_aa200(word_d8776,(&DAT_000f5c0c)[iVar1]);
    sub_b13a1();
    sub_aa200(word_d8776,(&DAT_000f5c0c)[iVar1]);
    if ((((&unk_f5c0b)[iVar1] & 8) != 0) && ((&DAT_000f5c13)[iVar1] != '\0')) {
      sub_abe18(param_1);
      sub_abf5c(param_1);
    }
    uVar3 = 1;
  }
  return CONCAT44(unaff_EDX,uVar3);
}


// ================================================================================================
// sub_acd58 @ 0xacd58 [__watcall]
// ================================================================================================

longlong __watcall sub_acd58(int param_1,uint unaff_EDX)

{
  byte bVar1;
  byte bVar2;
  undefined2 uVar3;
  int iVar4;
  byte extraout_AH;
  uint uVar5;
  undefined4 uVar6;
  int *piVar7;
  bool bVar8;
  ushort local_20;
  
  uVar3 = word_d8770;
  iVar4 = param_1 * 0x21;
  piVar7 = (int *)((int)&unk_f5bf8 + iVar4);
  if (((&unk_f5c0b)[iVar4] & 1) == 0) {
    return (ulonglong)unaff_EDX << 0x20;
  }
  (&DAT_000f5c0d)[iVar4] = (&DAT_000f5c0d)[iVar4] & 0x5f;
  sub_aa200(uVar3,param_1);
  sub_aa200(word_d8772,0xd);
  sub_aa200(word_d8776,3);
  sub_b13a1();
  sub_aa200(word_d8776,3);
  sub_aa200(word_d8772,0x89);
  sub_b1951(word_d8774);
  bVar8 = (&DAT_000f5c0e)[iVar4] == '\0';
  if (bVar8) {
    (&DAT_000f5c13)[iVar4] = (&DAT_000f5c13)[iVar4] + '\x01';
  }
  else {
    (&DAT_000f5c13)[iVar4] = (&DAT_000f5c0e)[iVar4] + -1;
    (&DAT_000f5c0e)[iVar4] = 0;
  }
  uVar3 = word_d8772;
  uVar5 = (uint)(byte)(&DAT_000f5c13)[iVar4];
  if ((byte)(&DAT_000f5c13)[iVar4] < 6) {
    if (((uVar5 == 3) && ((*(byte *)(*piVar7 + 0x48) & 0x20) != 0)) &&
       (((&unk_f5c0b)[iVar4] & 4) == 0)) {
      (&unk_f5c0b)[iVar4] = (&unk_f5c0b)[iVar4] | 2;
      if (bVar8) {
        (&DAT_000f5c18)[iVar4] = (&DAT_000f5c17)[iVar4];
      }
      (&DAT_000f5c16)[iVar4] = *(undefined *)(*piVar7 + 0x3e);
      if ((*(char *)(*piVar7 + 0x44) != '\0') ||
         ((&unk_f5a04)[(uint)(byte)(&DAT_000f5c15)[iVar4] * 0x10] != '\0')) {
        sub_aa200(word_d8772,0x89);
        uVar5 = sub_b1951(word_d8774);
        if ((uint)(byte)(&DAT_000f5c06)[iVar4] < (uint)((int)(uVar5 & 0xffff) >> 4)) {
          (&DAT_000f5c0d)[iVar4] = (&DAT_000f5c0d)[iVar4] | 0x40;
        }
        else {
          (&DAT_000f5c0d)[iVar4] = (&DAT_000f5c0d)[iVar4] & 0xbf;
        }
        sub_aa200(word_d8772,6);
        sub_aa200(word_d8776,(&DAT_000f5c08)[iVar4]);
        sub_aa200(word_d8772,7);
        sub_aa200(word_d8776,(&DAT_000f5c06)[iVar4]);
        sub_aa200(word_d8772,8);
        sub_aa200(word_d8776,(&DAT_000f5c07)[iVar4]);
        (&DAT_000f5c0d)[iVar4] = (&DAT_000f5c0d)[iVar4] | 0x18;
      }
      goto LAB_000ad10a;
    }
    (&DAT_000f5c0d)[iVar4] = (&DAT_000f5c0d)[iVar4] | 0x20;
    sub_aa200(uVar3,6);
    sub_aa200(word_d8776,*(undefined *)(uVar5 + 0x36 + *piVar7));
    if (bVar8) {
      (&DAT_000f5c18)[iVar4] = (&DAT_000f5c17)[iVar4];
      local_20 = (ushort)((ulonglong)
                          ((uint)*(byte *)(uVar5 + 0x3c + *piVar7) *
                          (uint)*(ushort *)((int)&DAT_000f5c09 + iVar4)) / 0xff);
      if (local_20 < 5) {
        local_20 = 5;
      }
      (&DAT_000f5c17)[iVar4] = (undefined)local_20;
    }
    else {
      local_20 = (ushort)(byte)(&DAT_000f5c17)[iVar4];
    }
    uVar3 = word_d8772;
    if (extraout_AH < local_20) {
      uVar6 = 8;
      (&DAT_000f5c0d)[iVar4] = (&DAT_000f5c0d)[iVar4] & 0xbf;
    }
    else {
      uVar6 = 7;
      (&DAT_000f5c0d)[iVar4] = (&DAT_000f5c0d)[iVar4] | 0x40;
    }
    sub_aa200(uVar3,uVar6);
  }
  else {
    if (bVar8) {
      (&DAT_000f5c18)[iVar4] = (&DAT_000f5c17)[iVar4];
    }
    bVar1 = (&unk_f5c0b)[iVar4];
    bVar2 = (&DAT_000f5c0c)[iVar4];
    (&unk_f5c0b)[iVar4] = bVar1 & 0xf1;
    (&DAT_000f5c0c)[iVar4] = bVar2 & 0xd7;
    (&DAT_000f5c0c)[iVar4] = bVar2 & 0xd7 | 0x20;
    (&unk_f5c0b)[iVar4] = bVar1 & 0xf1 | 0xc;
    if ((*(byte *)(*piVar7 + 0x48) & 0x10) == 0) {
      sub_aa200(word_d8772,5);
      sub_b19c7(word_d8774,*(undefined2 *)(*piVar7 + 0x2a));
      sub_aa200(word_d8772,4);
      uVar3 = *(undefined2 *)(*piVar7 + 0x2c);
    }
    else {
      sub_aa200(word_d8772,3);
      sub_b19c7(word_d8774,*(undefined2 *)(*piVar7 + 0x1e));
      sub_aa200(word_d8772,2);
      uVar3 = *(undefined2 *)(*piVar7 + 0x20);
    }
    sub_b19c7(word_d8774,uVar3);
    sub_aa200(word_d8772,0);
    sub_aa200(word_d8776,(&DAT_000f5c0c)[iVar4]);
    sub_b13a1();
    local_20._0_1_ = (&DAT_000f5c0c)[iVar4];
  }
  sub_aa200(word_d8776,(undefined)local_20);
LAB_000ad10a:
  sub_aa200(word_d8772,0xd);
  sub_aa200(word_d8776,(&DAT_000f5c0d)[iVar4]);
  sub_b13a1();
  sub_aa200(word_d8776,(&DAT_000f5c0d)[iVar4]);
  return CONCAT44(unaff_EDX,1);
}


// ================================================================================================
// sub_ad160 @ 0xad160 [__watcall]
// ================================================================================================

void __watcall
sub_ad160(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 unaff_ECX)

{
  int iVar1;
  int *piVar2;
  int extraout_EDX;
  int extraout_EDX_00;
  int extraout_EDX_01;
  int iVar3;
  uint uVar4;
  int iVar5;
  byte in_AF;
  byte in_TF;
  byte in_IF;
  byte in_NT;
  int local_2c;
  int local_28;
  int local_24;
  int *local_20;
  int local_1c;
  
  sub_b122f(param_1,param_1,&unk_f5bf8,unaff_ECX,
            (ushort)(in_NT & 1) * 0x4000 | (ushort)SBORROW4((int)&stack0xffffffe8,0x14) * 0x800 |
            (ushort)(in_IF & 1) * 0x200 | (ushort)(in_TF & 1) * 0x100 |
            (ushort)((int)&local_2c < 0) * 0x80 | (ushort)(&stack0x00000000 == &DAT_0000002c) * 0x40
            | (ushort)(in_AF & 1) * 0x10 |
            (ushort)((POPCOUNT((uint)&local_2c & 0xff) & 1U) == 0) * 4 |
            (ushort)(&stack0xffffffe8 < (undefined *)0x14));
  local_20 = &unk_f5bf8;
  iVar3 = extraout_EDX;
  for (uVar4 = 0; uVar4 < word_f79a0; uVar4 = uVar4 + 1) {
    if ((*(byte *)((int)local_20 + 0x13) & 1) != 0) {
      local_2c = *(int *)(iVar3 + -2) >> 0x10;
      for (iVar1 = 0; iVar1 < local_2c; iVar1 = iVar1 + 1) {
        iVar5 = *(int *)(iVar3 + 0x10 + iVar1 * 2) >> 0x10;
        for (local_24 = *(int *)(iVar3 + 2 + iVar1 * 4); (iVar5 != 0 && (local_24 != *local_20));
            local_24 = local_24 + 0x49) {
          iVar5 = iVar5 + -1;
        }
        if (iVar5 != 0) break;
      }
      if (iVar1 != local_2c) {
        sub_abe18(uVar4);
        iVar3 = extraout_EDX_00;
      }
    }
    local_20 = (int *)((int)local_20 + 0x21);
  }
  piVar2 = &unk_f5bf8;
  uVar4 = 0;
  do {
    if (word_f79a0 <= uVar4) {
      sub_b1256();
      return;
    }
    if ((*(byte *)((int)piVar2 + 0x13) & 1) != 0) {
      local_28 = *(int *)(iVar3 + -2) >> 0x10;
      for (iVar1 = 0; iVar1 < local_28; iVar1 = iVar1 + 1) {
        local_1c = *(int *)(iVar3 + 0x10 + iVar1 * 2) >> 0x10;
        for (iVar5 = *(int *)(iVar3 + 2 + iVar1 * 4); (local_1c != 0 && (iVar5 != *piVar2));
            iVar5 = iVar5 + 0x49) {
          local_1c = local_1c + -1;
        }
        if (local_1c != 0) break;
      }
      if (iVar1 != local_28) {
        sub_abf5c(uVar4);
        iVar3 = extraout_EDX_01;
      }
    }
    uVar4 = uVar4 + 1;
    piVar2 = (int *)((int)piVar2 + 0x21);
  } while( true );
}


// ================================================================================================
// sub_ad260 @ 0xad260 [__watcall]
// ================================================================================================

/* WARNING: Removing unreachable block (ram,0x000ad273) */

void __watcall sub_ad260(int param_1)

{
  undefined1 *puVar1;
  int iVar2;
  
  puVar1 = &unk_f59f8;
  iVar2 = 0;
  do {
    if (param_1 == *(int *)(puVar1 + 4)) {
      *(undefined4 *)(puVar1 + 4) = 0;
    }
    iVar2 = iVar2 + 1;
    puVar1 = puVar1 + 0x10;
  } while (iVar2 < 0x20);
  return;
}


// ================================================================================================
// sub_ad298 @ 0xad298 [__watcall]
// ================================================================================================

void __watcall sub_ad298(undefined4 param_1,int unaff_EDX)

{
  (&unk_f59fc)[unaff_EDX * 4] = param_1;
  return;
}


// ================================================================================================
// sub_ad2a8 @ 0xad2a8 [__watcall]
// ================================================================================================

void __watcall sub_ad2a8(int param_1,int unaff_EDX)

{
  uint uVar1;
  undefined4 *puVar2;
  byte in_AF;
  byte in_TF;
  byte in_IF;
  byte in_NT;
  ushort uVar3;
  
  if (param_1 == -1) {
    (&unk_f5a00)[unaff_EDX * 0x10] = 0x10;
  }
  else {
    puVar2 = &unk_f5bf8;
    param_1 = param_1 >> 3;
    (&unk_f5a00)[unaff_EDX * 0x10] = (char)param_1;
    uVar3 = (ushort)(in_NT & 1) * 0x4000 | (ushort)(in_IF & 1) * 0x200 | (ushort)(in_TF & 1) * 0x100
            | 0x40 | (ushort)(in_AF & 1) * 0x10 | 4;
    sub_b122f();
    for (uVar1 = 0; uVar1 < word_f79a0; uVar1 = uVar1 + 1) {
      if (((*(byte *)((int)puVar2 + 0x13) & 1) != 0) &&
         ((char)unaff_EDX == *(char *)((int)puVar2 + 0x1d))) {
        sub_aa200(word_d8770,uVar1,param_1,uVar1,uVar3);
        sub_aa200(word_d8772,0xc);
        sub_aa200(word_d8776,param_1);
      }
      puVar2 = (undefined4 *)((int)puVar2 + 0x21);
    }
    sub_b1256();
  }
  return;
}


// ================================================================================================
// sub_ad344 @ 0xad344 [__watcall]
// ================================================================================================

void __watcall sub_ad344(char param_1)

{
  uint uVar1;
  uint extraout_EDX;
  uint extraout_EDX_00;
  undefined4 *puVar2;
  
  sub_b122f();
  puVar2 = &unk_f5bf8;
  for (uVar1 = 0; uVar1 < word_f79a0; uVar1 = uVar1 + 1) {
    if (((*(byte *)((int)puVar2 + 0x13) & 1) != 0) && (param_1 == *(char *)((int)puVar2 + 0x1d))) {
      sub_abe18(uVar1);
      uVar1 = extraout_EDX;
    }
    puVar2 = (undefined4 *)((int)puVar2 + 0x21);
  }
  puVar2 = &unk_f5bf8;
  for (uVar1 = 0; uVar1 < word_f79a0; uVar1 = uVar1 + 1) {
    if (((*(byte *)((int)puVar2 + 0x13) & 1) != 0) && (param_1 == *(char *)((int)puVar2 + 0x1d))) {
      sub_abf5c(uVar1);
      uVar1 = extraout_EDX_00;
    }
    puVar2 = (undefined4 *)((int)puVar2 + 0x21);
  }
  sub_b1256();
  return;
}


// ================================================================================================
// sub_ad3c0 @ 0xad3c0 [__watcall]
// ================================================================================================

void __watcall sub_ad3c0(int param_1)

{
  uint uVar1;
  undefined *extraout_EDX;
  undefined *puVar2;
  byte in_CF;
  byte in_PF;
  byte in_AF;
  byte in_ZF;
  byte in_SF;
  byte in_TF;
  byte in_IF;
  byte in_OF;
  byte in_NT;
  ushort uVar3;
  
  uVar3 = (ushort)(in_NT & 1) * 0x4000 | (ushort)(in_OF & 1) * 0x800 | (ushort)(in_IF & 1) * 0x200 |
          (ushort)(in_TF & 1) * 0x100 | (ushort)(in_SF & 1) * 0x80 | (ushort)(in_ZF & 1) * 0x40 |
          (ushort)(in_AF & 1) * 0x10 | (ushort)(in_PF & 1) * 4 | (ushort)(in_CF & 1);
  sub_b122f();
  uVar1 = 0;
  puVar2 = extraout_EDX;
  while (uVar1 < 0xf) {
    uVar1 = uVar1 + 1;
    sub_b1f1c(param_1,*puVar2,param_1 + 1,uVar1,uVar3);
    param_1 = param_1 + 1;
    puVar2 = puVar2 + 1;
  }
  sub_b1256();
  return;
}


// ================================================================================================
// sub_ad3fc @ 0xad3fc [__watcall]
// ================================================================================================

void __watcall sub_ad3fc(int param_1)

{
  undefined uVar1;
  undefined *puVar2;
  undefined *extraout_EDX;
  uint uVar3;
  int extraout_EDX_00;
  
  sub_b122f();
  uVar3 = 0;
  puVar2 = extraout_EDX;
  while (uVar3 < 0xf) {
    uVar1 = sub_b1ea0(param_1);
    param_1 = param_1 + 1;
    *puVar2 = uVar1;
    puVar2 = puVar2 + 1;
    uVar3 = extraout_EDX_00 + 1;
  }
  sub_b1256();
  return;
}


// ================================================================================================
// sub_ad434 @ 0xad434 [__watcall]
// ================================================================================================

undefined8 __watcall sub_ad434(undefined4 param_1,undefined4 unaff_EDX)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 extraout_EDX;
  int iVar3;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined2 local_18;
  undefined local_16;
  
  byte_d89e0 = 1;
  iVar3 = 0;
  word_f6128 = 0;
  do {
    cVar1 = sub_b2074(iVar3 << 0x12);
    if (cVar1 != '\0') {
      local_20 = 0xffffffff;
      local_1c = 0xffffffff;
      word_f6128 = word_f6128 | (ushort)(1 << ((byte)iVar3 & 0x1f));
      local_18 = 0;
      local_24 = 0x40000;
      local_16 = 0;
      sub_ad3c0(extraout_EDX,&local_24);
    }
    iVar3 = iVar3 + 1;
  } while (iVar3 < 4);
  if (word_f6128 == 0) {
    uVar2 = 6;
  }
  else {
    sub_b1f1c(0x1e,0);
    sub_b1f1c(0x1f,0);
    uVar2 = 0;
  }
  return CONCAT44(unaff_EDX,uVar2);
}


// ================================================================================================
// sub_ad4dc @ 0xad4dc [__watcall]
// ================================================================================================

undefined8 __watcall sub_ad4dc(int param_1,undefined4 unaff_EDX)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  byte in_AF;
  byte in_TF;
  byte in_IF;
  byte in_NT;
  ushort uVar5;
  uint local_3c;
  int local_38;
  byte local_2e;
  uint local_2c;
  int local_28;
  int local_24;
  undefined2 local_20;
  undefined local_1e;
  uint local_1c;
  
  uVar5 = (ushort)(in_NT & 1) * 0x4000 | (ushort)SBORROW4((int)&stack0xffffffe8,0x24) * 0x800 |
          (ushort)(in_IF & 1) * 0x200 | (ushort)(in_TF & 1) * 0x100 |
          (ushort)((int)&local_3c < 0) * 0x80 |
          (ushort)(&stack0x00000000 == (undefined *)0x3c) * 0x40 | (ushort)(in_AF & 1) * 0x10 |
          (ushort)((POPCOUNT((uint)&local_3c & 0xff) & 1U) == 0) * 4 |
          (ushort)(&stack0xffffffe8 < (undefined *)0x24);
  sub_b122f();
  local_1c = 0;
  uVar4 = (param_1 + 0x1fU & 0xffffe0) + 0x20;
  do {
    if (((uint)word_f6128 & 1 << ((byte)local_1c & 0x1f)) != 0) {
      uVar3 = local_1c & 0xff;
      iVar1 = local_1c << 0x12;
      while (iVar2 = iVar1, iVar2 != -1) {
        sub_ad3fc(iVar2,&local_3c,iVar2,uVar3,uVar5);
        iVar1 = local_38;
        if (((local_2e & 1) == 0) && (uVar3 = local_3c, uVar4 <= local_3c)) {
          local_2e = local_2e | 1;
          local_2c = local_3c - uVar4;
          if (0x3f < local_2c) {
            local_28 = local_38;
            local_20 = 0;
            local_38 = iVar2 + uVar4;
            local_1e = 0;
            local_3c = uVar4;
            local_24 = iVar2;
            sub_ad3c0(iVar2,&local_3c);
            sub_ad3c0(local_38,&local_2c);
            iVar1 = local_28;
            if (local_28 != -1) {
              sub_ad3fc(local_28,&local_2c);
              local_24 = local_38;
              sub_ad3c0(iVar1,&local_2c);
            }
            sub_b1256();
            return CONCAT44(unaff_EDX,iVar2 + 0x20);
          }
          sub_ad3c0(iVar2,&local_3c);
          sub_b1256();
          iVar2 = iVar2 + 0x20;
          goto LAB_000ad603;
        }
      }
    }
    local_1c = local_1c + 1;
    if (3 < (int)local_1c) {
      sub_b1256();
      iVar2 = 0;
LAB_000ad603:
      return CONCAT44(unaff_EDX,iVar2);
    }
  } while( true );
}


// ================================================================================================
// sub_ad610 @ 0xad610 [__watcall]
// ================================================================================================

void __watcall sub_ad610(int param_1,undefined4 param_2,undefined4 param_3,undefined4 unaff_ECX)

{
  int iVar1;
  byte in_AF;
  byte in_TF;
  byte in_IF;
  byte in_NT;
  int local_44;
  int local_40;
  byte local_36;
  int local_34;
  int local_30;
  int local_2c;
  byte local_26;
  int local_24;
  int local_20;
  int local_1c;
  byte local_16;
  
  iVar1 = param_1 + -0x20;
  sub_b122f(param_1,&local_24,iVar1,unaff_ECX,
            (ushort)(in_NT & 1) * 0x4000 | (ushort)SBORROW4((int)&stack0xffffffec,0x30) * 0x800 |
            (ushort)(in_IF & 1) * 0x200 | (ushort)(in_TF & 1) * 0x100 |
            (ushort)((int)&local_44 < 0) * 0x80 |
            (ushort)(&stack0x00000000 == (undefined *)0x44) * 0x40 | (ushort)(in_AF & 1) * 0x10 |
            (ushort)((POPCOUNT((uint)&local_44 & 0xff) & 1U) == 0) * 4 |
            (ushort)(&stack0xffffffec < (undefined *)0x30));
  sub_ad3fc(iVar1);
  if (local_1c != -1) {
    sub_ad3fc(local_1c,&local_44);
    if ((local_36 & 1) == 0) {
      local_44 = local_44 + local_24;
      local_40 = local_20;
      if (local_20 != -1) {
        sub_ad3fc(local_20,&local_34);
        local_2c = local_1c;
        sub_ad3c0(local_40,&local_34);
      }
      sub_ad3c0(local_1c,&local_44);
      sub_ad3fc(local_1c,&local_24);
      iVar1 = local_1c;
    }
  }
  if (local_20 != -1) {
    sub_ad3fc(local_20,&local_34);
    if ((local_26 & 1) == 0) {
      local_24 = local_24 + local_34;
      local_20 = local_30;
      if (local_30 != -1) {
        sub_ad3fc(local_30,&local_34);
        local_2c = iVar1;
        sub_ad3c0(local_20,&local_34);
      }
    }
  }
  local_16 = local_16 & 0xfe;
  sub_ad3c0(iVar1,&local_24);
  sub_b1256();
  return;
}


// ================================================================================================
// sub_ad6f4 @ 0xad6f4 [__watcall]
// ================================================================================================

undefined8 __watcall sub_ad6f4(undefined4 param_1,undefined4 unaff_EDX)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  byte in_AF;
  byte in_TF;
  byte in_IF;
  byte in_NT;
  ushort uVar4;
  int local_24;
  int local_20;
  byte local_16;
  
  uVar4 = (ushort)(in_NT & 1) * 0x4000 | (ushort)SBORROW4((int)&stack0xffffffec,0x10) * 0x800 |
          (ushort)(in_IF & 1) * 0x200 | (ushort)(in_TF & 1) * 0x100 |
          (ushort)((int)&local_24 < 0) * 0x80 |
          (ushort)(&stack0x00000000 == (undefined *)0x24) * 0x40 | (ushort)(in_AF & 1) * 0x10 |
          (ushort)((POPCOUNT((uint)&local_24 & 0xff) & 1U) == 0) * 4 |
          (ushort)(&stack0xffffffec < (undefined *)0x10);
  sub_b122f();
  iVar3 = 0;
  uVar2 = 0;
  do {
    if (((uint)word_f6128 & 1 << ((byte)uVar2 & 0x1f)) != 0) {
      iVar1 = uVar2 << 0x12;
      while (iVar1 != -1) {
        sub_ad3fc(iVar1,&local_24,uVar2,uVar2 & 0xff,uVar4);
        iVar1 = local_20;
        if ((local_16 & 1) == 0) {
          iVar3 = iVar3 + local_24;
        }
      }
    }
    uVar2 = uVar2 + 1;
  } while ((int)uVar2 < 4);
  sub_b1256();
  return CONCAT44(unaff_EDX,iVar3);
}


// ================================================================================================
// sub_ad758 @ 0xad758 [__watcall]
// ================================================================================================

undefined8 __watcall sub_ad758(undefined4 param_1,undefined4 unaff_EDX)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  byte in_AF;
  byte in_TF;
  byte in_IF;
  byte in_NT;
  ushort uVar4;
  uint local_24;
  int local_20;
  byte local_16;
  
  uVar4 = (ushort)(in_NT & 1) * 0x4000 | (ushort)SBORROW4((int)&stack0xffffffec,0x10) * 0x800 |
          (ushort)(in_IF & 1) * 0x200 | (ushort)(in_TF & 1) * 0x100 |
          (ushort)((int)&local_24 < 0) * 0x80 |
          (ushort)(&stack0x00000000 == (undefined *)0x24) * 0x40 | (ushort)(in_AF & 1) * 0x10 |
          (ushort)((POPCOUNT((uint)&local_24 & 0xff) & 1U) == 0) * 4 |
          (ushort)(&stack0xffffffec < (undefined *)0x10);
  sub_b122f();
  uVar3 = 0;
  uVar2 = 0;
  do {
    if (((uint)word_f6128 & 1 << ((byte)uVar2 & 0x1f)) != 0) {
      iVar1 = uVar2 << 0x12;
      while (iVar1 != -1) {
        sub_ad3fc(iVar1,&local_24,uVar2,uVar2 & 0xff,uVar4);
        iVar1 = local_20;
        if (((local_16 & 1) == 0) && (uVar3 < local_24)) {
          uVar3 = local_24;
        }
      }
    }
    uVar2 = uVar2 + 1;
  } while ((int)uVar2 < 4);
  sub_b1256();
  if (uVar3 < 0x21) {
    iVar1 = 0;
  }
  else {
    iVar1 = uVar3 - 0x20;
  }
  return CONCAT44(unaff_EDX,iVar1);
}


// ================================================================================================
// sub_ad7cc @ 0xad7cc [__cdecl]
// ================================================================================================

void sub_ad7cc(short *param_1)

{
  uint in_EAX;
  uint in_ECX;
  uint uVar1;
  uint uVar2;
  uint in_EDX;
  int unaff_EBX;
  byte *unaff_ESI;
  byte *pbVar3;
  int unaff_EDI;
  bool bVar4;
  uint local_8;
  
  local_8 = in_EAX;
  if (0x3f < in_EAX) {
    do {
      *param_1 = *param_1 + *(short *)(unaff_EBX + (uint)*unaff_ESI * 2);
      pbVar3 = unaff_ESI + (uint)CARRY4(in_ECX,in_EDX) + unaff_EDI;
      param_1[1] = param_1[1] + *(short *)(unaff_EBX + (uint)*pbVar3 * 2);
      uVar1 = in_ECX + in_EDX + in_EDX;
      pbVar3 = pbVar3 + (uint)CARRY4(in_ECX + in_EDX,in_EDX) + unaff_EDI;
      param_1[2] = param_1[2] + *(short *)(unaff_EBX + (uint)*pbVar3 * 2);
      uVar2 = uVar1 + in_EDX;
      pbVar3 = pbVar3 + (uint)CARRY4(uVar1,in_EDX) + unaff_EDI;
      param_1[3] = param_1[3] + *(short *)(unaff_EBX + (uint)*pbVar3 * 2);
      uVar1 = uVar2 + in_EDX;
      pbVar3 = pbVar3 + (uint)CARRY4(uVar2,in_EDX) + unaff_EDI;
      param_1[4] = param_1[4] + *(short *)(unaff_EBX + (uint)*pbVar3 * 2);
      uVar2 = uVar1 + in_EDX;
      pbVar3 = pbVar3 + (uint)CARRY4(uVar1,in_EDX) + unaff_EDI;
      param_1[5] = param_1[5] + *(short *)(unaff_EBX + (uint)*pbVar3 * 2);
      uVar1 = uVar2 + in_EDX;
      pbVar3 = pbVar3 + (uint)CARRY4(uVar2,in_EDX) + unaff_EDI;
      param_1[6] = param_1[6] + *(short *)(unaff_EBX + (uint)*pbVar3 * 2);
      uVar2 = uVar1 + in_EDX;
      pbVar3 = pbVar3 + (uint)CARRY4(uVar1,in_EDX) + unaff_EDI;
      param_1[7] = param_1[7] + *(short *)(unaff_EBX + (uint)*pbVar3 * 2);
      uVar1 = uVar2 + in_EDX;
      pbVar3 = pbVar3 + (uint)CARRY4(uVar2,in_EDX) + unaff_EDI;
      param_1[8] = param_1[8] + *(short *)(unaff_EBX + (uint)*pbVar3 * 2);
      uVar2 = uVar1 + in_EDX;
      pbVar3 = pbVar3 + (uint)CARRY4(uVar1,in_EDX) + unaff_EDI;
      param_1[9] = param_1[9] + *(short *)(unaff_EBX + (uint)*pbVar3 * 2);
      uVar1 = uVar2 + in_EDX;
      pbVar3 = pbVar3 + (uint)CARRY4(uVar2,in_EDX) + unaff_EDI;
      param_1[10] = param_1[10] + *(short *)(unaff_EBX + (uint)*pbVar3 * 2);
      uVar2 = uVar1 + in_EDX;
      pbVar3 = pbVar3 + (uint)CARRY4(uVar1,in_EDX) + unaff_EDI;
      param_1[0xb] = param_1[0xb] + *(short *)(unaff_EBX + (uint)*pbVar3 * 2);
      uVar1 = uVar2 + in_EDX;
      pbVar3 = pbVar3 + (uint)CARRY4(uVar2,in_EDX) + unaff_EDI;
      param_1[0xc] = param_1[0xc] + *(short *)(unaff_EBX + (uint)*pbVar3 * 2);
      uVar2 = uVar1 + in_EDX;
      pbVar3 = pbVar3 + (uint)CARRY4(uVar1,in_EDX) + unaff_EDI;
      param_1[0xd] = param_1[0xd] + *(short *)(unaff_EBX + (uint)*pbVar3 * 2);
      uVar1 = uVar2 + in_EDX;
      pbVar3 = pbVar3 + (uint)CARRY4(uVar2,in_EDX) + unaff_EDI;
      param_1[0xe] = param_1[0xe] + *(short *)(unaff_EBX + (uint)*pbVar3 * 2);
      uVar2 = uVar1 + in_EDX;
      pbVar3 = pbVar3 + (uint)CARRY4(uVar1,in_EDX) + unaff_EDI;
      param_1[0xf] = param_1[0xf] + *(short *)(unaff_EBX + (uint)*pbVar3 * 2);
      uVar1 = uVar2 + in_EDX;
      pbVar3 = pbVar3 + (uint)CARRY4(uVar2,in_EDX) + unaff_EDI;
      param_1[0x10] = param_1[0x10] + *(short *)(unaff_EBX + (uint)*pbVar3 * 2);
      uVar2 = uVar1 + in_EDX;
      pbVar3 = pbVar3 + (uint)CARRY4(uVar1,in_EDX) + unaff_EDI;
      param_1[0x11] = param_1[0x11] + *(short *)(unaff_EBX + (uint)*pbVar3 * 2);
      uVar1 = uVar2 + in_EDX;
      pbVar3 = pbVar3 + (uint)CARRY4(uVar2,in_EDX) + unaff_EDI;
      param_1[0x12] = param_1[0x12] + *(short *)(unaff_EBX + (uint)*pbVar3 * 2);
      uVar2 = uVar1 + in_EDX;
      pbVar3 = pbVar3 + (uint)CARRY4(uVar1,in_EDX) + unaff_EDI;
      param_1[0x13] = param_1[0x13] + *(short *)(unaff_EBX + (uint)*pbVar3 * 2);
      uVar1 = uVar2 + in_EDX;
      pbVar3 = pbVar3 + (uint)CARRY4(uVar2,in_EDX) + unaff_EDI;
      param_1[0x14] = param_1[0x14] + *(short *)(unaff_EBX + (uint)*pbVar3 * 2);
      uVar2 = uVar1 + in_EDX;
      pbVar3 = pbVar3 + (uint)CARRY4(uVar1,in_EDX) + unaff_EDI;
      param_1[0x15] = param_1[0x15] + *(short *)(unaff_EBX + (uint)*pbVar3 * 2);
      uVar1 = uVar2 + in_EDX;
      pbVar3 = pbVar3 + (uint)CARRY4(uVar2,in_EDX) + unaff_EDI;
      param_1[0x16] = param_1[0x16] + *(short *)(unaff_EBX + (uint)*pbVar3 * 2);
      uVar2 = uVar1 + in_EDX;
      pbVar3 = pbVar3 + (uint)CARRY4(uVar1,in_EDX) + unaff_EDI;
      param_1[0x17] = param_1[0x17] + *(short *)(unaff_EBX + (uint)*pbVar3 * 2);
      uVar1 = uVar2 + in_EDX;
      pbVar3 = pbVar3 + (uint)CARRY4(uVar2,in_EDX) + unaff_EDI;
      param_1[0x18] = param_1[0x18] + *(short *)(unaff_EBX + (uint)*pbVar3 * 2);
      uVar2 = uVar1 + in_EDX;
      pbVar3 = pbVar3 + (uint)CARRY4(uVar1,in_EDX) + unaff_EDI;
      param_1[0x19] = param_1[0x19] + *(short *)(unaff_EBX + (uint)*pbVar3 * 2);
      uVar1 = uVar2 + in_EDX;
      pbVar3 = pbVar3 + (uint)CARRY4(uVar2,in_EDX) + unaff_EDI;
      param_1[0x1a] = param_1[0x1a] + *(short *)(unaff_EBX + (uint)*pbVar3 * 2);
      uVar2 = uVar1 + in_EDX;
      pbVar3 = pbVar3 + (uint)CARRY4(uVar1,in_EDX) + unaff_EDI;
      param_1[0x1b] = param_1[0x1b] + *(short *)(unaff_EBX + (uint)*pbVar3 * 2);
      uVar1 = uVar2 + in_EDX;
      pbVar3 = pbVar3 + (uint)CARRY4(uVar2,in_EDX) + unaff_EDI;
      param_1[0x1c] = param_1[0x1c] + *(short *)(unaff_EBX + (uint)*pbVar3 * 2);
      uVar2 = uVar1 + in_EDX;
      pbVar3 = pbVar3 + (uint)CARRY4(uVar1,in_EDX) + unaff_EDI;
      param_1[0x1d] = param_1[0x1d] + *(short *)(unaff_EBX + (uint)*pbVar3 * 2);
      uVar1 = uVar2 + in_EDX;
      pbVar3 = pbVar3 + (uint)CARRY4(uVar2,in_EDX) + unaff_EDI;
      param_1[0x1e] = param_1[0x1e] + *(short *)(unaff_EBX + (uint)*pbVar3 * 2);
      uVar2 = uVar1 + in_EDX;
      pbVar3 = pbVar3 + (uint)CARRY4(uVar1,in_EDX) + unaff_EDI;
      param_1[0x1f] = param_1[0x1f] + *(short *)(unaff_EBX + (uint)*pbVar3 * 2);
      uVar1 = uVar2 + in_EDX;
      pbVar3 = pbVar3 + (uint)CARRY4(uVar2,in_EDX) + unaff_EDI;
      param_1[0x20] = param_1[0x20] + *(short *)(unaff_EBX + (uint)*pbVar3 * 2);
      uVar2 = uVar1 + in_EDX;
      pbVar3 = pbVar3 + (uint)CARRY4(uVar1,in_EDX) + unaff_EDI;
      param_1[0x21] = param_1[0x21] + *(short *)(unaff_EBX + (uint)*pbVar3 * 2);
      uVar1 = uVar2 + in_EDX;
      pbVar3 = pbVar3 + (uint)CARRY4(uVar2,in_EDX) + unaff_EDI;
      param_1[0x22] = param_1[0x22] + *(short *)(unaff_EBX + (uint)*pbVar3 * 2);
      uVar2 = uVar1 + in_EDX;
      pbVar3 = pbVar3 + (uint)CARRY4(uVar1,in_EDX) + unaff_EDI;
      param_1[0x23] = param_1[0x23] + *(short *)(unaff_EBX + (uint)*pbVar3 * 2);
      uVar1 = uVar2 + in_EDX;
      pbVar3 = pbVar3 + (uint)CARRY4(uVar2,in_EDX) + unaff_EDI;
      param_1[0x24] = param_1[0x24] + *(short *)(unaff_EBX + (uint)*pbVar3 * 2);
      uVar2 = uVar1 + in_EDX;
      pbVar3 = pbVar3 + (uint)CARRY4(uVar1,in_EDX) + unaff_EDI;
      param_1[0x25] = param_1[0x25] + *(short *)(unaff_EBX + (uint)*pbVar3 * 2);
      uVar1 = uVar2 + in_EDX;
      pbVar3 = pbVar3 + (uint)CARRY4(uVar2,in_EDX) + unaff_EDI;
      param_1[0x26] = param_1[0x26] + *(short *)(unaff_EBX + (uint)*pbVar3 * 2);
      uVar2 = uVar1 + in_EDX;
      pbVar3 = pbVar3 + (uint)CARRY4(uVar1,in_EDX) + unaff_EDI;
      param_1[0x27] = param_1[0x27] + *(short *)(unaff_EBX + (uint)*pbVar3 * 2);
      uVar1 = uVar2 + in_EDX;
      pbVar3 = pbVar3 + (uint)CARRY4(uVar2,in_EDX) + unaff_EDI;
      param_1[0x28] = param_1[0x28] + *(short *)(unaff_EBX + (uint)*pbVar3 * 2);
      uVar2 = uVar1 + in_EDX;
      pbVar3 = pbVar3 + (uint)CARRY4(uVar1,in_EDX) + unaff_EDI;
      param_1[0x29] = param_1[0x29] + *(short *)(unaff_EBX + (uint)*pbVar3 * 2);
      uVar1 = uVar2 + in_EDX;
      pbVar3 = pbVar3 + (uint)CARRY4(uVar2,in_EDX) + unaff_EDI;
      param_1[0x2a] = param_1[0x2a] + *(short *)(unaff_EBX + (uint)*pbVar3 * 2);
      uVar2 = uVar1 + in_EDX;
      pbVar3 = pbVar3 + (uint)CARRY4(uVar1,in_EDX) + unaff_EDI;
      param_1[0x2b] = param_1[0x2b] + *(short *)(unaff_EBX + (uint)*pbVar3 * 2);
      uVar1 = uVar2 + in_EDX;
      pbVar3 = pbVar3 + (uint)CARRY4(uVar2,in_EDX) + unaff_EDI;
      param_1[0x2c] = param_1[0x2c] + *(short *)(unaff_EBX + (uint)*pbVar3 * 2);
      uVar2 = uVar1 + in_EDX;
      pbVar3 = pbVar3 + (uint)CARRY4(uVar1,in_EDX) + unaff_EDI;
      param_1[0x2d] = param_1[0x2d] + *(short *)(unaff_EBX + (uint)*pbVar3 * 2);
      uVar1 = uVar2 + in_EDX;
      pbVar3 = pbVar3 + (uint)CARRY4(uVar2,in_EDX) + unaff_EDI;
      param_1[0x2e] = param_1[0x2e] + *(short *)(unaff_EBX + (uint)*pbVar3 * 2);
      uVar2 = uVar1 + in_EDX;
      pbVar3 = pbVar3 + (uint)CARRY4(uVar1,in_EDX) + unaff_EDI;
      param_1[0x2f] = param_1[0x2f] + *(short *)(unaff_EBX + (uint)*pbVar3 * 2);
      uVar1 = uVar2 + in_EDX;
      pbVar3 = pbVar3 + (uint)CARRY4(uVar2,in_EDX) + unaff_EDI;
      param_1[0x30] = param_1[0x30] + *(short *)(unaff_EBX + (uint)*pbVar3 * 2);
      uVar2 = uVar1 + in_EDX;
      pbVar3 = pbVar3 + (uint)CARRY4(uVar1,in_EDX) + unaff_EDI;
      param_1[0x31] = param_1[0x31] + *(short *)(unaff_EBX + (uint)*pbVar3 * 2);
      uVar1 = uVar2 + in_EDX;
      pbVar3 = pbVar3 + (uint)CARRY4(uVar2,in_EDX) + unaff_EDI;
      param_1[0x32] = param_1[0x32] + *(short *)(unaff_EBX + (uint)*pbVar3 * 2);
      uVar2 = uVar1 + in_EDX;
      pbVar3 = pbVar3 + (uint)CARRY4(uVar1,in_EDX) + unaff_EDI;
      param_1[0x33] = param_1[0x33] + *(short *)(unaff_EBX + (uint)*pbVar3 * 2);
      uVar1 = uVar2 + in_EDX;
      pbVar3 = pbVar3 + (uint)CARRY4(uVar2,in_EDX) + unaff_EDI;
      param_1[0x34] = param_1[0x34] + *(short *)(unaff_EBX + (uint)*pbVar3 * 2);
      uVar2 = uVar1 + in_EDX;
      pbVar3 = pbVar3 + (uint)CARRY4(uVar1,in_EDX) + unaff_EDI;
      param_1[0x35] = param_1[0x35] + *(short *)(unaff_EBX + (uint)*pbVar3 * 2);
      uVar1 = uVar2 + in_EDX;
      pbVar3 = pbVar3 + (uint)CARRY4(uVar2,in_EDX) + unaff_EDI;
      param_1[0x36] = param_1[0x36] + *(short *)(unaff_EBX + (uint)*pbVar3 * 2);
      uVar2 = uVar1 + in_EDX;
      pbVar3 = pbVar3 + (uint)CARRY4(uVar1,in_EDX) + unaff_EDI;
      param_1[0x37] = param_1[0x37] + *(short *)(unaff_EBX + (uint)*pbVar3 * 2);
      uVar1 = uVar2 + in_EDX;
      pbVar3 = pbVar3 + (uint)CARRY4(uVar2,in_EDX) + unaff_EDI;
      param_1[0x38] = param_1[0x38] + *(short *)(unaff_EBX + (uint)*pbVar3 * 2);
      uVar2 = uVar1 + in_EDX;
      pbVar3 = pbVar3 + (uint)CARRY4(uVar1,in_EDX) + unaff_EDI;
      param_1[0x39] = param_1[0x39] + *(short *)(unaff_EBX + (uint)*pbVar3 * 2);
      uVar1 = uVar2 + in_EDX;
      pbVar3 = pbVar3 + (uint)CARRY4(uVar2,in_EDX) + unaff_EDI;
      param_1[0x3a] = param_1[0x3a] + *(short *)(unaff_EBX + (uint)*pbVar3 * 2);
      uVar2 = uVar1 + in_EDX;
      pbVar3 = pbVar3 + (uint)CARRY4(uVar1,in_EDX) + unaff_EDI;
      param_1[0x3b] = param_1[0x3b] + *(short *)(unaff_EBX + (uint)*pbVar3 * 2);
      uVar1 = uVar2 + in_EDX;
      pbVar3 = pbVar3 + (uint)CARRY4(uVar2,in_EDX) + unaff_EDI;
      param_1[0x3c] = param_1[0x3c] + *(short *)(unaff_EBX + (uint)*pbVar3 * 2);
      uVar2 = uVar1 + in_EDX;
      pbVar3 = pbVar3 + (uint)CARRY4(uVar1,in_EDX) + unaff_EDI;
      param_1[0x3d] = param_1[0x3d] + *(short *)(unaff_EBX + (uint)*pbVar3 * 2);
      uVar1 = uVar2 + in_EDX;
      pbVar3 = pbVar3 + (uint)CARRY4(uVar2,in_EDX) + unaff_EDI;
      param_1[0x3e] = param_1[0x3e] + *(short *)(unaff_EBX + (uint)*pbVar3 * 2);
      uVar2 = uVar1 + in_EDX;
      param_1[0x3f] =
           param_1[0x3f] +
           *(short *)(unaff_EBX + (uint)pbVar3[(uint)CARRY4(uVar1,in_EDX) + unaff_EDI] * 2);
      in_ECX = uVar2 + in_EDX;
      unaff_ESI = pbVar3 + (uint)CARRY4(uVar1,in_EDX) + unaff_EDI +
                  (uint)CARRY4(uVar2,in_EDX) + unaff_EDI;
      param_1 = param_1 + 0x40;
      local_8 = local_8 - 0x40;
    } while (0x3f < local_8);
  }
  for (; local_8 != 0; local_8 = local_8 - 1) {
    *param_1 = *param_1 + *(short *)(unaff_EBX + (uint)*unaff_ESI * 2);
    bVar4 = CARRY4(in_ECX,in_EDX);
    in_ECX = in_ECX + in_EDX;
    unaff_ESI = unaff_ESI + (uint)bVar4 + unaff_EDI;
    param_1 = param_1 + 1;
  }
  return;
}


// ================================================================================================
// sub_adc96 @ 0xadc96 [__watcall]
// ================================================================================================

void __watcall sub_adc96(undefined4 param_1,undefined4 param_2,undefined4 *unaff_EBX,uint unaff_ECX)

{
  undefined4 *puVar1;
  undefined4 *unaff_EDI;
  
  if (0xff < unaff_ECX) {
    param_1 = 0;
    puVar1 = unaff_EBX + 1;
    unaff_EDI = unaff_EBX;
    do {
      *unaff_EDI = 0;
      *puVar1 = 0;
      unaff_EDI[2] = 0;
      puVar1[2] = 0;
      unaff_EDI[4] = 0;
      puVar1[4] = 0;
      unaff_EDI[6] = 0;
      puVar1[6] = 0;
      unaff_EDI[8] = 0;
      puVar1[8] = 0;
      unaff_EDI[10] = 0;
      puVar1[10] = 0;
      unaff_EDI[0xc] = 0;
      puVar1[0xc] = 0;
      unaff_EDI[0xe] = 0;
      puVar1[0xe] = 0;
      unaff_EDI[0x10] = 0;
      puVar1[0x10] = 0;
      unaff_EDI[0x12] = 0;
      puVar1[0x12] = 0;
      unaff_EDI[0x14] = 0;
      puVar1[0x14] = 0;
      unaff_EDI[0x16] = 0;
      puVar1[0x16] = 0;
      unaff_EDI[0x18] = 0;
      puVar1[0x18] = 0;
      unaff_EDI[0x1a] = 0;
      puVar1[0x1a] = 0;
      unaff_EDI[0x1c] = 0;
      puVar1[0x1c] = 0;
      unaff_EDI[0x1e] = 0;
      puVar1[0x1e] = 0;
      unaff_EDI[0x20] = 0;
      puVar1[0x20] = 0;
      unaff_EDI[0x22] = 0;
      puVar1[0x22] = 0;
      unaff_EDI[0x24] = 0;
      puVar1[0x24] = 0;
      unaff_EDI[0x26] = 0;
      puVar1[0x26] = 0;
      unaff_EDI[0x28] = 0;
      puVar1[0x28] = 0;
      unaff_EDI[0x2a] = 0;
      puVar1[0x2a] = 0;
      unaff_EDI[0x2c] = 0;
      puVar1[0x2c] = 0;
      unaff_EDI[0x2e] = 0;
      puVar1[0x2e] = 0;
      unaff_EDI[0x30] = 0;
      puVar1[0x30] = 0;
      unaff_EDI[0x32] = 0;
      puVar1[0x32] = 0;
      unaff_EDI[0x34] = 0;
      puVar1[0x34] = 0;
      unaff_EDI[0x36] = 0;
      puVar1[0x36] = 0;
      unaff_EDI[0x38] = 0;
      puVar1[0x38] = 0;
      unaff_EDI[0x3a] = 0;
      puVar1[0x3a] = 0;
      unaff_EDI[0x3c] = 0;
      puVar1[0x3c] = 0;
      unaff_EDI[0x3e] = 0;
      puVar1[0x3e] = 0;
      unaff_EDI[0x40] = 0;
      puVar1[0x40] = 0;
      unaff_EDI[0x42] = 0;
      puVar1[0x42] = 0;
      unaff_EDI[0x44] = 0;
      puVar1[0x44] = 0;
      unaff_EDI[0x46] = 0;
      puVar1[0x46] = 0;
      unaff_EDI[0x48] = 0;
      puVar1[0x48] = 0;
      unaff_EDI[0x4a] = 0;
      puVar1[0x4a] = 0;
      unaff_EDI[0x4c] = 0;
      puVar1[0x4c] = 0;
      unaff_EDI[0x4e] = 0;
      puVar1[0x4e] = 0;
      unaff_EDI[0x50] = 0;
      puVar1[0x50] = 0;
      unaff_EDI[0x52] = 0;
      puVar1[0x52] = 0;
      unaff_EDI[0x54] = 0;
      puVar1[0x54] = 0;
      unaff_EDI[0x56] = 0;
      puVar1[0x56] = 0;
      unaff_EDI[0x58] = 0;
      puVar1[0x58] = 0;
      unaff_EDI[0x5a] = 0;
      puVar1[0x5a] = 0;
      unaff_EDI[0x5c] = 0;
      puVar1[0x5c] = 0;
      unaff_EDI[0x5e] = 0;
      puVar1[0x5e] = 0;
      unaff_EDI[0x60] = 0;
      puVar1[0x60] = 0;
      unaff_EDI[0x62] = 0;
      puVar1[0x62] = 0;
      unaff_EDI[100] = 0;
      puVar1[100] = 0;
      unaff_EDI[0x66] = 0;
      puVar1[0x66] = 0;
      unaff_EDI[0x68] = 0;
      puVar1[0x68] = 0;
      unaff_EDI[0x6a] = 0;
      puVar1[0x6a] = 0;
      unaff_EDI[0x6c] = 0;
      puVar1[0x6c] = 0;
      unaff_EDI[0x6e] = 0;
      puVar1[0x6e] = 0;
      unaff_EDI[0x70] = 0;
      puVar1[0x70] = 0;
      unaff_EDI[0x72] = 0;
      puVar1[0x72] = 0;
      unaff_EDI[0x74] = 0;
      puVar1[0x74] = 0;
      unaff_EDI[0x76] = 0;
      puVar1[0x76] = 0;
      unaff_EDI[0x78] = 0;
      puVar1[0x78] = 0;
      unaff_EDI[0x7a] = 0;
      puVar1[0x7a] = 0;
      unaff_EDI[0x7c] = 0;
      puVar1[0x7c] = 0;
      unaff_EDI[0x7e] = 0;
      puVar1[0x7e] = 0;
      unaff_EDI = unaff_EDI + 0x80;
      puVar1 = puVar1 + 0x80;
      unaff_ECX = unaff_ECX - 0x100;
    } while (0xff < unaff_ECX);
  }
  if (unaff_ECX == 0) {
    return;
  }
  puVar1 = unaff_EDI;
  if ((unaff_ECX & 3) != 0) {
    if ((unaff_ECX & 1) != 0) {
      puVar1 = (undefined4 *)((int)unaff_EDI + 1);
      *(char *)unaff_EDI = (char)param_1;
      unaff_EDI = puVar1;
      if ((unaff_ECX & 2) == 0) goto LAB_000adee0;
    }
    puVar1 = (undefined4 *)((int)unaff_EDI + 2);
    *(short *)unaff_EDI = (short)param_1;
  }
LAB_000adee0:
  for (unaff_ECX = unaff_ECX >> 2; unaff_ECX != 0; unaff_ECX = unaff_ECX - 1) {
    *puVar1 = param_1;
    puVar1 = puVar1 + 1;
  }
  return;
}


// ================================================================================================
// sub_adee8 @ 0xadee8 [__watcall]
// ================================================================================================

void __watcall sub_adee8(void)

{
  return;
}


// ================================================================================================
// sub_adee9 @ 0xadee9 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall sub_adee9(int param_1,undefined4 unaff_EDX,undefined4 unaff_EBX)

{
  ushort uVar1;
  undefined2 uVar2;
  short sVar3;
  byte *pbVar4;
  undefined *puVar5;
  undefined *puVar6;
  uint extraout_ECX;
  uint extraout_ECX_00;
  uint extraout_ECX_01;
  uint extraout_ECX_02;
  uint uVar7;
  uint uVar8;
  int iVar9;
  byte bVar10;
  undefined4 uVar11;
  byte *pbVar12;
  bool bVar13;
  ulonglong uVar14;
  byte *local_14;
  byte *local_8;
  
  if (param_1 == 0) {
    dword_d8494 = dword_d7af4;
    if (dword_d8498 == 0) {
      if (dword_d7af8 == 0) {
        dword_d8494 = dword_d7af4;
        return;
      }
      dword_d7af8 = dword_d7af8 + -1;
    }
    else {
      dword_d7af8 = 2;
    }
  }
  else {
    dword_d8494 = dword_d7b00;
    if (dword_d8498 == 0) {
      if (dword_d7b04 == 0) {
        dword_d8494 = dword_d7b00;
        return;
      }
      dword_d7af8 = dword_d7af8 + -1;
    }
    else {
      dword_d7b04 = 2;
    }
  }
  uVar14 = sub_adc96(dword_d8494,unaff_EDX,dword_d8494,dword_d8484,unaff_EBX);
  puVar5 = dword_d8494;
  pbVar12 = dword_d7b44;
  if ((char)dword_d7b0c != '\0') {
    if (byte_d7b18 == '\0') {
      bVar10 = (byte)dword_d8490 & 0x1f;
      if (dword_d7b44 +
          (uint)CARRY4(dword_d7b50 << ((byte)dword_d8490 & 0x1f),dword_d7b48) +
          (dword_d7b4c << bVar10 | dword_d7b50 >> 0x20 - bVar10) < dword_d7b34) {
        local_14 = dword_d7b44;
        uVar14 = sub_ad7cc(dword_d8494);
        uVar7 = extraout_ECX;
LAB_000adfe7:
        dword_d7b44 = dword_d7b44 + ((int)pbVar12 - (int)local_14);
        dword_d7b48 = uVar7;
      }
      else {
        local_8 = (byte *)0x0;
        do {
          uVar8 = dword_d7b50;
          iVar9 = dword_d7b4c;
          pbVar4 = dword_d7b34;
          local_14 = dword_d7b44;
          uVar7 = dword_d7b48;
          pbVar12 = dword_d7b44;
          while( true ) {
            uVar1 = *(ushort *)(&unk_d7b64 + (uint)*pbVar12 * 2);
            *(ushort *)(dword_d8494 + (int)local_8 * 2) =
                 *(short *)(dword_d8494 + (int)local_8 * 2) + uVar1;
            uVar14 = CONCAT44(uVar8,dword_d8484);
            local_8 = (byte *)((int)local_8 + 1);
            bVar13 = CARRY4(uVar7,uVar8);
            uVar7 = uVar7 + uVar8;
            pbVar12 = pbVar12 + (uint)bVar13 + iVar9;
            if (pbVar4 <= pbVar12) break;
            if ((byte *)dword_d8484 == local_8) goto LAB_000adfe7;
          }
          if ((dword_d7b0c != 1) || (dword_d7b1c == 0)) {
            dword_d7b0c = 0;
            uVar14 = CONCAT44(uVar8,(uint)uVar1);
            break;
          }
          dword_d7b44 = dword_d7b30;
          dword_d7b48 = uVar7;
        } while (local_8 != (byte *)dword_d8484);
      }
    }
    else {
      uVar8 = (int)dword_d7b34 - (int)dword_d7b44;
      if (dword_d7b60 < (uint)((int)dword_d7b34 - (int)dword_d7b44)) {
        uVar8 = dword_d7b60;
      }
      local_8 = dword_d7b44 + uVar8;
      iVar9 = 0;
      while( true ) {
        uVar8 = (uint)byte_d7b58;
        puVar6 = dword_d7b38;
        if (dword_d7b38 == &DAT_00010000) {
          do {
            uVar2 = *(undefined2 *)(&unk_d7414 + (uint)*pbVar12 * 2);
            bVar10 = (char)uVar8 + (char)uVar2;
            *(short *)(puVar5 + iVar9 * 2) =
                 *(short *)(puVar5 + iVar9 * 2) + *(short *)(&unk_d7b64 + (uint)bVar10 * 2);
            uVar8 = (uint)(byte)(bVar10 + (char)((ushort)uVar2 >> 8));
            puVar6 = (undefined *)
                     CONCAT22((short)((uint)puVar6 >> 0x10),*(short *)(&unk_d7b64 + uVar8 * 2));
            *(short *)(puVar5 + (iVar9 + 1) * 2) =
                 *(short *)(puVar5 + (iVar9 + 1) * 2) + *(short *)(&unk_d7b64 + uVar8 * 2);
            iVar9 = iVar9 + 2;
            pbVar12 = pbVar12 + 1;
          } while (pbVar12 < local_8);
        }
        else {
          do {
            uVar2 = *(undefined2 *)(&unk_d7414 + (uint)*pbVar12 * 2);
            bVar10 = (char)uVar8 + (char)uVar2;
            sVar3 = *(short *)(&unk_d7b64 + (uint)bVar10 * 2);
            *(short *)(puVar5 + iVar9 * 2) = *(short *)(puVar5 + iVar9 * 2) + sVar3;
            *(short *)(puVar5 + (iVar9 + 1) * 2) = *(short *)(puVar5 + (iVar9 + 1) * 2) + sVar3;
            uVar8 = (uint)(byte)(bVar10 + (char)((ushort)uVar2 >> 8));
            sVar3 = *(short *)(&unk_d7b64 + uVar8 * 2);
            puVar6 = (undefined *)CONCAT22((short)((uint)puVar6 >> 0x10),sVar3);
            *(short *)(puVar5 + (iVar9 + 2) * 2) = *(short *)(puVar5 + (iVar9 + 2) * 2) + sVar3;
            *(short *)(puVar5 + (iVar9 + 3) * 2) = *(short *)(puVar5 + (iVar9 + 3) * 2) + sVar3;
            iVar9 = iVar9 + 4;
            pbVar12 = pbVar12 + 1;
          } while (pbVar12 < local_8);
        }
        uVar14 = CONCAT44(uVar8,puVar6);
        if (pbVar12 != dword_d7b34) {
          byte_d7b58 = (byte)uVar8;
          dword_d7b44 = pbVar12;
          uVar14 = CONCAT44(uVar8,puVar6);
          goto LAB_000ae1b7;
        }
        if ((dword_d7b0c != 1) || (dword_d7b1c == 0)) {
          dword_d7b0c = 0;
          goto LAB_000ae1b7;
        }
        byte_d7b58 = byte_d7b5c;
        uVar14 = (ulonglong)CONCAT14(byte_d7b5c,dword_d7b30);
        if (dword_d7b44 + (dword_d7b60 - (int)pbVar12) == (byte *)0x0) break;
        local_8 = dword_d7b30 + (int)(dword_d7b44 + (dword_d7b60 - (int)pbVar12));
        pbVar12 = dword_d7b30;
      }
      dword_d7b44 = dword_d7b30;
    }
  }
LAB_000ae1b7:
  puVar5 = dword_d8494;
  pbVar12 = dword_d7d9c;
  if (dword_d7d64 != '\0') {
    if (byte_d7d70 == '\0') {
      bVar10 = (byte)dword_d8490 & 0x1f;
      if (dword_d7d9c +
          (uint)CARRY4(dword_d7da8 << ((byte)dword_d8490 & 0x1f),dword_d7da0) +
          (dword_d7da4 << bVar10 | dword_d7da8 >> 0x20 - bVar10) < dword_d7d8c) {
        local_14 = dword_d7d9c;
        uVar14 = sub_ad7cc(dword_d8494);
        uVar7 = extraout_ECX_00;
LAB_000ae22f:
        dword_d7d9c = dword_d7d9c + ((int)pbVar12 - (int)local_14);
        dword_d7da0 = uVar7;
      }
      else {
        local_8 = (byte *)0x0;
        do {
          uVar8 = dword_d7da8;
          iVar9 = dword_d7da4;
          pbVar4 = dword_d7d8c;
          local_14 = dword_d7d9c;
          uVar7 = dword_d7da0;
          pbVar12 = dword_d7d9c;
          while( true ) {
            uVar1 = *(ushort *)(&unk_d7dbc + (uint)*pbVar12 * 2);
            *(ushort *)(dword_d8494 + (int)local_8 * 2) =
                 *(short *)(dword_d8494 + (int)local_8 * 2) + uVar1;
            uVar14 = CONCAT44(uVar8,dword_d8484);
            local_8 = (byte *)((int)local_8 + 1);
            bVar13 = CARRY4(uVar7,uVar8);
            uVar7 = uVar7 + uVar8;
            pbVar12 = pbVar12 + (uint)bVar13 + iVar9;
            if (pbVar4 <= pbVar12) break;
            if ((byte *)dword_d8484 == local_8) goto LAB_000ae22f;
          }
          if ((_dword_d7d64 != 1) || (dword_d7d74 == 0)) {
            _dword_d7d64 = 0;
            uVar14 = CONCAT44(uVar8,(uint)uVar1);
            break;
          }
          dword_d7d9c = dword_d7d88;
          dword_d7da0 = uVar7;
        } while (local_8 != (byte *)dword_d8484);
      }
    }
    else {
      uVar8 = (int)dword_d7d8c - (int)dword_d7d9c;
      if (dword_d7db8 < (uint)((int)dword_d7d8c - (int)dword_d7d9c)) {
        uVar8 = dword_d7db8;
      }
      local_8 = dword_d7d9c + uVar8;
      iVar9 = 0;
      while( true ) {
        uVar8 = (uint)byte_d7db0;
        puVar6 = dword_d7d90;
        if (dword_d7d90 == &DAT_00010000) {
          do {
            uVar2 = *(undefined2 *)(&unk_d7414 + (uint)*pbVar12 * 2);
            bVar10 = (char)uVar8 + (char)uVar2;
            *(short *)(puVar5 + iVar9 * 2) =
                 *(short *)(puVar5 + iVar9 * 2) + *(short *)(&unk_d7dbc + (uint)bVar10 * 2);
            uVar8 = (uint)(byte)(bVar10 + (char)((ushort)uVar2 >> 8));
            puVar6 = (undefined *)
                     CONCAT22((short)((uint)puVar6 >> 0x10),*(short *)(&unk_d7dbc + uVar8 * 2));
            *(short *)(puVar5 + (iVar9 + 1) * 2) =
                 *(short *)(puVar5 + (iVar9 + 1) * 2) + *(short *)(&unk_d7dbc + uVar8 * 2);
            iVar9 = iVar9 + 2;
            pbVar12 = pbVar12 + 1;
          } while (pbVar12 < local_8);
        }
        else {
          do {
            uVar2 = *(undefined2 *)(&unk_d7414 + (uint)*pbVar12 * 2);
            bVar10 = (char)uVar8 + (char)uVar2;
            sVar3 = *(short *)(&unk_d7dbc + (uint)bVar10 * 2);
            *(short *)(puVar5 + iVar9 * 2) = *(short *)(puVar5 + iVar9 * 2) + sVar3;
            *(short *)(puVar5 + (iVar9 + 1) * 2) = *(short *)(puVar5 + (iVar9 + 1) * 2) + sVar3;
            uVar8 = (uint)(byte)(bVar10 + (char)((ushort)uVar2 >> 8));
            sVar3 = *(short *)(&unk_d7dbc + uVar8 * 2);
            puVar6 = (undefined *)CONCAT22((short)((uint)puVar6 >> 0x10),sVar3);
            *(short *)(puVar5 + (iVar9 + 2) * 2) = *(short *)(puVar5 + (iVar9 + 2) * 2) + sVar3;
            *(short *)(puVar5 + (iVar9 + 3) * 2) = *(short *)(puVar5 + (iVar9 + 3) * 2) + sVar3;
            iVar9 = iVar9 + 4;
            pbVar12 = pbVar12 + 1;
          } while (pbVar12 < local_8);
        }
        uVar14 = CONCAT44(uVar8,puVar6);
        if (pbVar12 != dword_d7d8c) {
          byte_d7db0 = (byte)uVar8;
          dword_d7d9c = pbVar12;
          uVar14 = CONCAT44(uVar8,puVar6);
          goto LAB_000ae3ff;
        }
        if ((_dword_d7d64 != 1) || (dword_d7d74 == 0)) {
          _dword_d7d64 = 0;
          goto LAB_000ae3ff;
        }
        byte_d7db0 = byte_d7db4;
        uVar14 = (ulonglong)CONCAT14(byte_d7db4,dword_d7d88);
        if (dword_d7d9c + (dword_d7db8 - (int)pbVar12) == (byte *)0x0) break;
        local_8 = dword_d7d88 + (int)(dword_d7d9c + (dword_d7db8 - (int)pbVar12));
        pbVar12 = dword_d7d88;
      }
      dword_d7d9c = dword_d7d88;
    }
  }
LAB_000ae3ff:
  puVar5 = dword_d8494;
  pbVar12 = dword_d7ff4;
  if (dword_d7fbc != '\0') {
    if (byte_d7fc8 == '\0') {
      bVar10 = (byte)dword_d8490 & 0x1f;
      if (dword_d7ff4 +
          (uint)CARRY4(dword_d8000 << ((byte)dword_d8490 & 0x1f),dword_d7ff8) +
          (dword_d7ffc << bVar10 | dword_d8000 >> 0x20 - bVar10) < dword_d7fe4) {
        local_14 = dword_d7ff4;
        uVar14 = sub_ad7cc(dword_d8494);
        uVar7 = extraout_ECX_01;
LAB_000ae477:
        dword_d7ff4 = dword_d7ff4 + ((int)pbVar12 - (int)local_14);
        dword_d7ff8 = uVar7;
      }
      else {
        local_8 = (byte *)0x0;
        do {
          uVar8 = dword_d8000;
          iVar9 = dword_d7ffc;
          pbVar4 = dword_d7fe4;
          local_14 = dword_d7ff4;
          uVar7 = dword_d7ff8;
          pbVar12 = dword_d7ff4;
          while( true ) {
            uVar1 = *(ushort *)(&unk_d8014 + (uint)*pbVar12 * 2);
            *(ushort *)(dword_d8494 + (int)local_8 * 2) =
                 *(short *)(dword_d8494 + (int)local_8 * 2) + uVar1;
            uVar14 = CONCAT44(uVar8,dword_d8484);
            local_8 = (byte *)((int)local_8 + 1);
            bVar13 = CARRY4(uVar7,uVar8);
            uVar7 = uVar7 + uVar8;
            pbVar12 = pbVar12 + (uint)bVar13 + iVar9;
            if (pbVar4 <= pbVar12) break;
            if ((byte *)dword_d8484 == local_8) goto LAB_000ae477;
          }
          if ((_dword_d7fbc != 1) || (dword_d7fcc == 0)) {
            _dword_d7fbc = 0;
            uVar14 = CONCAT44(uVar8,(uint)uVar1);
            break;
          }
          dword_d7ff4 = dword_d7fe0;
          dword_d7ff8 = uVar7;
        } while (local_8 != (byte *)dword_d8484);
      }
    }
    else {
      uVar8 = (int)dword_d7fe4 - (int)dword_d7ff4;
      if (dword_d8010 < (uint)((int)dword_d7fe4 - (int)dword_d7ff4)) {
        uVar8 = dword_d8010;
      }
      local_8 = dword_d7ff4 + uVar8;
      iVar9 = 0;
      while( true ) {
        uVar8 = (uint)byte_d8008;
        puVar6 = dword_d7fe8;
        if (dword_d7fe8 == &DAT_00010000) {
          do {
            uVar2 = *(undefined2 *)(&unk_d7414 + (uint)*pbVar12 * 2);
            bVar10 = (char)uVar8 + (char)uVar2;
            *(short *)(puVar5 + iVar9 * 2) =
                 *(short *)(puVar5 + iVar9 * 2) + *(short *)(&unk_d8014 + (uint)bVar10 * 2);
            uVar8 = (uint)(byte)(bVar10 + (char)((ushort)uVar2 >> 8));
            puVar6 = (undefined *)
                     CONCAT22((short)((uint)puVar6 >> 0x10),*(short *)(&unk_d8014 + uVar8 * 2));
            *(short *)(puVar5 + (iVar9 + 1) * 2) =
                 *(short *)(puVar5 + (iVar9 + 1) * 2) + *(short *)(&unk_d8014 + uVar8 * 2);
            iVar9 = iVar9 + 2;
            pbVar12 = pbVar12 + 1;
          } while (pbVar12 < local_8);
        }
        else {
          do {
            uVar2 = *(undefined2 *)(&unk_d7414 + (uint)*pbVar12 * 2);
            bVar10 = (char)uVar8 + (char)uVar2;
            sVar3 = *(short *)(&unk_d8014 + (uint)bVar10 * 2);
            *(short *)(puVar5 + iVar9 * 2) = *(short *)(puVar5 + iVar9 * 2) + sVar3;
            *(short *)(puVar5 + (iVar9 + 1) * 2) = *(short *)(puVar5 + (iVar9 + 1) * 2) + sVar3;
            uVar8 = (uint)(byte)(bVar10 + (char)((ushort)uVar2 >> 8));
            sVar3 = *(short *)(&unk_d8014 + uVar8 * 2);
            puVar6 = (undefined *)CONCAT22((short)((uint)puVar6 >> 0x10),sVar3);
            *(short *)(puVar5 + (iVar9 + 2) * 2) = *(short *)(puVar5 + (iVar9 + 2) * 2) + sVar3;
            *(short *)(puVar5 + (iVar9 + 3) * 2) = *(short *)(puVar5 + (iVar9 + 3) * 2) + sVar3;
            iVar9 = iVar9 + 4;
            pbVar12 = pbVar12 + 1;
          } while (pbVar12 < local_8);
        }
        uVar14 = CONCAT44(uVar8,puVar6);
        if (pbVar12 != dword_d7fe4) {
          byte_d8008 = (byte)uVar8;
          dword_d7ff4 = pbVar12;
          uVar14 = CONCAT44(uVar8,puVar6);
          goto LAB_000ae647;
        }
        if ((_dword_d7fbc != 1) || (dword_d7fcc == 0)) {
          _dword_d7fbc = 0;
          goto LAB_000ae647;
        }
        byte_d8008 = byte_d800c;
        uVar14 = (ulonglong)CONCAT14(byte_d800c,dword_d7fe0);
        if (dword_d7ff4 + (dword_d8010 - (int)pbVar12) == (byte *)0x0) break;
        local_8 = dword_d7fe0 + (int)(dword_d7ff4 + (dword_d8010 - (int)pbVar12));
        pbVar12 = dword_d7fe0;
      }
      dword_d7ff4 = dword_d7fe0;
    }
  }
LAB_000ae647:
  puVar5 = dword_d8494;
  pbVar12 = dword_d824c;
  if (dword_d8214 != '\0') {
    if (byte_d8220 == '\0') {
      bVar10 = (byte)dword_d8490 & 0x1f;
      if (dword_d824c +
          (uint)CARRY4(dword_d8258 << ((byte)dword_d8490 & 0x1f),dword_d8250) +
          (dword_d8254 << bVar10 | dword_d8258 >> 0x20 - bVar10) < dword_d823c) {
        local_14 = dword_d824c;
        uVar14 = sub_ad7cc(dword_d8494);
        uVar7 = extraout_ECX_02;
LAB_000ae6bf:
        dword_d824c = dword_d824c + ((int)pbVar12 - (int)local_14);
        dword_d8250 = uVar7;
      }
      else {
        local_8 = (byte *)0x0;
        do {
          uVar8 = dword_d8258;
          iVar9 = dword_d8254;
          pbVar4 = dword_d823c;
          local_14 = dword_d824c;
          uVar7 = dword_d8250;
          pbVar12 = dword_d824c;
          while( true ) {
            uVar1 = *(ushort *)(&unk_d826c + (uint)*pbVar12 * 2);
            *(ushort *)(dword_d8494 + (int)local_8 * 2) =
                 *(short *)(dword_d8494 + (int)local_8 * 2) + uVar1;
            uVar14 = CONCAT44(uVar8,dword_d8484);
            local_8 = (byte *)((int)local_8 + 1);
            bVar13 = CARRY4(uVar7,uVar8);
            uVar7 = uVar7 + uVar8;
            pbVar12 = pbVar12 + (uint)bVar13 + iVar9;
            if (pbVar4 <= pbVar12) break;
            if ((byte *)dword_d8484 == local_8) goto LAB_000ae6bf;
          }
          if ((_dword_d8214 != 1) || (dword_d8224 == 0)) {
            _dword_d8214 = 0;
            uVar14 = CONCAT44(uVar8,(uint)uVar1);
            break;
          }
          dword_d824c = dword_d8238;
          dword_d8250 = uVar7;
        } while (local_8 != (byte *)dword_d8484);
      }
    }
    else {
      uVar8 = (int)dword_d823c - (int)dword_d824c;
      if (dword_d8268 < (uint)((int)dword_d823c - (int)dword_d824c)) {
        uVar8 = dword_d8268;
      }
      local_8 = dword_d824c + uVar8;
      iVar9 = 0;
      while( true ) {
        uVar8 = (uint)byte_d8260;
        puVar6 = dword_d8240;
        if (dword_d8240 == &DAT_00010000) {
          do {
            uVar2 = *(undefined2 *)(&unk_d7414 + (uint)*pbVar12 * 2);
            bVar10 = (char)uVar8 + (char)uVar2;
            *(short *)(puVar5 + iVar9 * 2) =
                 *(short *)(puVar5 + iVar9 * 2) + *(short *)(&unk_d826c + (uint)bVar10 * 2);
            uVar8 = (uint)(byte)(bVar10 + (char)((ushort)uVar2 >> 8));
            puVar6 = (undefined *)
                     CONCAT22((short)((uint)puVar6 >> 0x10),*(short *)(&unk_d826c + uVar8 * 2));
            *(short *)(puVar5 + (iVar9 + 1) * 2) =
                 *(short *)(puVar5 + (iVar9 + 1) * 2) + *(short *)(&unk_d826c + uVar8 * 2);
            iVar9 = iVar9 + 2;
            pbVar12 = pbVar12 + 1;
          } while (pbVar12 < local_8);
        }
        else {
          do {
            uVar2 = *(undefined2 *)(&unk_d7414 + (uint)*pbVar12 * 2);
            bVar10 = (char)uVar8 + (char)uVar2;
            sVar3 = *(short *)(&unk_d826c + (uint)bVar10 * 2);
            *(short *)(puVar5 + iVar9 * 2) = *(short *)(puVar5 + iVar9 * 2) + sVar3;
            *(short *)(puVar5 + (iVar9 + 1) * 2) = *(short *)(puVar5 + (iVar9 + 1) * 2) + sVar3;
            uVar8 = (uint)(byte)(bVar10 + (char)((ushort)uVar2 >> 8));
            sVar3 = *(short *)(&unk_d826c + uVar8 * 2);
            puVar6 = (undefined *)CONCAT22((short)((uint)puVar6 >> 0x10),sVar3);
            *(short *)(puVar5 + (iVar9 + 2) * 2) = *(short *)(puVar5 + (iVar9 + 2) * 2) + sVar3;
            *(short *)(puVar5 + (iVar9 + 3) * 2) = *(short *)(puVar5 + (iVar9 + 3) * 2) + sVar3;
            iVar9 = iVar9 + 4;
            pbVar12 = pbVar12 + 1;
          } while (pbVar12 < local_8);
        }
        uVar14 = CONCAT44(uVar8,puVar6);
        if (pbVar12 != dword_d823c) {
          byte_d8260 = (byte)uVar8;
          dword_d824c = pbVar12;
          uVar14 = CONCAT44(uVar8,puVar6);
          goto LAB_000ae88f;
        }
        if ((_dword_d8214 != 1) || (dword_d8224 == 0)) {
          _dword_d8214 = 0;
          goto LAB_000ae88f;
        }
        byte_d8260 = byte_d8264;
        uVar14 = (ulonglong)CONCAT14(byte_d8264,dword_d8238);
        if (dword_d824c + (dword_d8268 - (int)pbVar12) == (byte *)0x0) break;
        local_8 = dword_d8238 + (int)(dword_d824c + (dword_d8268 - (int)pbVar12));
        pbVar12 = dword_d8238;
      }
      dword_d824c = dword_d8238;
    }
  }
LAB_000ae88f:
  sub_adee8((int)uVar14,(int)(uVar14 >> 0x20),dword_d8494,dword_d8484);
  puVar5 = dword_d8494;
  dword_d84a8 = dword_d8494;
  dword_d84ac = dword_d8494;
  uVar11 = dword_d84b4;
  if (dword_d8494 == dword_d7af4) {
    sub_b1f1c(dword_d84b8,*dword_d8494);
    sub_b1f1c(dword_d84b8 + 1,puVar5[1]);
    uVar11 = dword_d84b0;
  }
  sub_b0d6c(&dword_d84a8,dword_d8480,uVar11,0x41,1);
  return;
}


// ================================================================================================
// sub_ae903 @ 0xae903 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int6 __watcall sub_ae903(int param_1,ushort unaff_DX)

{
  undefined2 *puVar1;
  undefined2 uVar2;
  undefined2 in_SS;
  undefined auStack_8 [8];
  
  if (dword_d7af0 != 0) {
    if (param_1 == _dword_d849c) {
      out(word_d8770,dword_d84a0);
      out(word_d8772,0xb);
      out(word_d8774,dword_d84bc);
      out(word_d8772,10);
      out(word_d8774,word_d84be);
      out(word_d8772,0);
      out(word_d8776,0x24);
      in(word_d8778);
      in(word_d8778);
      in(word_d8778);
      in(word_d8778);
      in(word_d8778);
      in(word_d8778);
      in(word_d8778);
      puVar1 = (undefined2 *)segment(in_SS,(short)auStack_8);
      uVar2 = *puVar1;
      puVar1 = (undefined2 *)segment(in_SS,(short)auStack_8 + 2);
      out(uVar2,(char)*puVar1);
      dword_d7b08 = 1;
    }
    else {
      if (param_1 != _dword_d84a0) goto LAB_000ae9e8;
      out(word_d8770,dword_d84a0);
      out(word_d8772,0);
      out(word_d8776,3);
      in(word_d8778);
      in(word_d8778);
      in(word_d8778);
      in(word_d8778);
      in(word_d8778);
      in(word_d8778);
      in(word_d8778);
      puVar1 = (undefined2 *)segment(in_SS,(short)auStack_8);
      uVar2 = *puVar1;
      puVar1 = (undefined2 *)segment(in_SS,(short)auStack_8 + 2);
      out(uVar2,(char)*puVar1);
      dword_d7afc = 1;
    }
    return CONCAT24(uVar2,1);
  }
LAB_000ae9e8:
  return (uint6)unaff_DX << 0x20;
}


// ================================================================================================
// sub_ae9eb @ 0xae9eb [__watcall]
// ================================================================================================

void __watcall sub_ae9eb(void)

{
  if (dword_d7afc != 0) {
    sub_adee9(0);
    dword_d7afc = 0;
  }
  if (dword_d7b08 != 0) {
    sub_adee9(1);
    dword_d7b08 = 0;
  }
  return;
}


// ================================================================================================
// sub_aea23 @ 0xaea23 [__cdecl]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 sub_aea23(int *param_1,uint param_2,uint param_3)

{
  undefined *puVar1;
  undefined2 *puVar2;
  undefined2 *puVar3;
  undefined2 uVar4;
  uint uVar5;
  undefined2 uVar6;
  int iVar7;
  undefined2 extraout_var;
  short sVar8;
  int iVar9;
  int iVar10;
  undefined2 in_SS;
  byte in_CF;
  byte bVar11;
  byte in_PF;
  byte bVar12;
  byte in_AF;
  byte in_ZF;
  byte bVar13;
  byte in_SF;
  byte bVar14;
  byte in_TF;
  byte in_IF;
  byte bVar15;
  byte in_OF;
  byte bVar16;
  byte in_NT;
  byte in_AC;
  byte in_VIF;
  byte in_VIP;
  byte in_ID;
  undefined4 uStack_18;
  uint uStack_14;
  
  uStack_14 = (uint)(in_NT & 1) * 0x4000 | (uint)(in_OF & 1) * 0x800 | (uint)(in_IF & 1) * 0x200 |
              (uint)(in_TF & 1) * 0x100 | (uint)(in_SF & 1) * 0x80 | (uint)(in_ZF & 1) * 0x40 |
              (uint)(in_AF & 1) * 0x10 | (uint)(in_PF & 1) * 4 | (uint)(in_CF & 1) |
              (uint)(in_ID & 1) * 0x200000 | (uint)(in_VIP & 1) * 0x100000 |
              (uint)(in_VIF & 1) * 0x80000 | (uint)(in_AC & 1) * 0x40000;
  bVar15 = 0;
  iVar7 = 4;
  iVar10 = 0;
  do {
    puVar1 = (&off_d846c)[iVar10];
    *(undefined4 *)(puVar1 + 4) = 0xff;
    iVar10 = iVar10 + 1;
    iVar7 = iVar7 + -1;
  } while (iVar7 != 0);
  dword_d847c = param_3;
  dword_d8480 = param_3 >> 1;
  param_3 = param_3 >> 2;
  uVar5 = 1;
  dword_d8490 = 0;
  do {
    iVar7 = dword_d8490;
    uVar5 = uVar5 << 1;
    dword_d8490 = dword_d8490 + 1;
  } while (uVar5 < param_3);
  dword_d848c = iVar7 + 2;
  dword_d8488 = iVar7 + 3;
  dword_d7af4 = param_1;
  iVar7 = (int)param_1 + dword_d8480;
  dword_d7b00 = iVar7;
  dword_d8484 = param_3;
  for (; param_3 != 0; param_3 = param_3 - 1) {
    *param_1 = iVar7;
    param_1 = param_1 + 1;
  }
  dword_d84b0 = param_2;
  _dword_d84bc = ((param_2 & 0x3fff) >> 1 | param_2 & 0xfffc000) << 9;
  dword_d84b4 = param_2 + dword_d8480;
  _dword_d84c0 = ((dword_d84b4 & 0x3fff) >> 1 | dword_d84b4 & 0xfffc000) << 9;
  dword_d84b8 = param_2 + dword_d847c;
  _dword_d84c4 = ((dword_d84b8 & 0x3fff) >> 1 | dword_d84b8 & 0xfffc000) << 9;
  dword_d8498 = 0;
  dword_d7af8 = 1;
  dword_d7b04 = 1;
  do {
    uStack_18 = 0xaeb4e;
    sub_b1f1c(param_2,0,puVar1);
    param_2 = param_2 + 1;
  } while (param_2 <= dword_d84b8);
  uStack_18 = 0xaeb60;
  sub_b1f1c(param_2,0,puVar1);
  uStack_18 = 0xaeb6a;
  sub_b14e4(sub_ae903);
  uStack_18 = 0xaeb73;
  _dword_d849c = sub_b1cbc(0,0);
  bVar11 = 0;
  bVar16 = 0;
  bVar14 = 0;
  bVar13 = 1;
  bVar12 = 1;
  uStack_18 = 0xaeb81;
  _dword_d84a0 = sub_b1cbc(0);
  out(word_d8770,dword_d849c);
  out(word_d8772,1);
  uVar6 = (undefined2)((uint)_dword_d84a0 >> 0x10);
  out(word_d8774,0x400);
  out(word_d8772,3);
  out(word_d8774,dword_d84bc);
  out(word_d8772,2);
  out(word_d8774,word_d84be);
  out(word_d8772,0xb);
  out(word_d8774,dword_d84bc);
  out(word_d8772,10);
  out(word_d8774,word_d84be);
  out(word_d8772,5);
  out(word_d8774,dword_d84c4);
  out(word_d8772,4);
  out(word_d8774,word_d84c6);
  out(word_d8772,0);
  out(word_d8776,0x2c);
  in(word_d8778);
  in(word_d8778);
  in(word_d8778);
  in(word_d8778);
  in(word_d8778);
  in(word_d8778);
  in(word_d8778);
  sVar8 = (short)&uStack_18;
  puVar2 = (undefined2 *)segment(in_SS,sVar8);
  puVar3 = (undefined2 *)segment(in_SS,sVar8 + 2);
  iVar9 = CONCAT22((short)((uint)&uStack_18 >> 0x10),sVar8 + 4);
  out(*puVar2,(char)*puVar3);
  out(word_d8772,9);
  out(word_d8774,0xffff);
  out(word_d8772,0xc);
  out(word_d8776,7);
  out(word_d8770,dword_d84a0);
  out(word_d8772,1);
  out(word_d8774,0x400);
  out(word_d8772,9);
  out(word_d8774,0);
  out(word_d8772,3);
  out(word_d8774,dword_d84bc);
  out(word_d8772,2);
  out(word_d8774,word_d84be);
  out(word_d8772,5);
  out(word_d8774,dword_d84c0);
  out(word_d8772,4);
  out(word_d8774,word_d84c2);
  *(uint *)(iVar9 + -4) =
       (uint)(in_NT & 1) * 0x4000 | (uint)(bVar16 & 1) * 0x800 | (uint)(bVar15 & 1) * 0x200 |
       (uint)(in_TF & 1) * 0x100 | (uint)(bVar14 & 1) * 0x80 | (uint)(bVar13 & 1) * 0x40 |
       (uint)(in_AF & 1) * 0x10 | (uint)(bVar12 & 1) * 4 | (uint)(bVar11 & 1) |
       (uint)(in_ID & 1) * 0x200000 | (uint)(in_VIP & 1) * 0x100000 | (uint)(in_VIF & 1) * 0x80000 |
       (uint)(in_AC & 1) * 0x40000;
  uVar4 = word_d8776;
  out(word_d8770,dword_d84a0);
  out(word_d8772,0xb);
  out(word_d8774,dword_d84bc);
  out(word_d8772,10);
  out(word_d8774,word_d84be);
  out(word_d8772,0);
  out(word_d8776,0x24);
  *(short *)(iVar9 + -6) = (short)CONCAT31((int3)(CONCAT22(uVar6,word_d84be) >> 8),0x24);
  *(undefined2 *)(iVar9 + -8) = uVar4;
  in(word_d8778);
  in(word_d8778);
  in(word_d8778);
  in(word_d8778);
  in(word_d8778);
  in(word_d8778);
  in(word_d8778);
  puVar2 = (undefined2 *)segment(in_SS,(short)(iVar9 + -8));
  puVar3 = (undefined2 *)segment(in_SS,(short)(iVar9 + -8) + 2);
  out(*puVar2,(char)*puVar3);
  dword_d8498 = 0xf;
  dword_d7af0 = 1;
  return CONCAT44(CONCAT22(extraout_var,*puVar2),CONCAT22(uVar6,*puVar3));
}


// ================================================================================================
// sub_aedbc @ 0xaedbc [__watcall]
// ================================================================================================

undefined2 __watcall sub_aedbc(undefined2 param_1)

{
  undefined2 *puVar1;
  undefined2 *puVar2;
  undefined2 uVar3;
  short sVar4;
  undefined2 *puVar5;
  undefined2 in_SS;
  undefined auStack_c [12];
  
  uVar3 = word_d8776;
  if (dword_d7af0 != 0) {
    dword_d8498 = 0;
    out(word_d8770,dword_d84a0);
    out(word_d8772,0);
    out(word_d8776,3);
    in(word_d8778);
    in(word_d8778);
    in(word_d8778);
    in(word_d8778);
    in(word_d8778);
    in(word_d8778);
    in(word_d8778);
    sVar4 = (short)auStack_c;
    puVar1 = (undefined2 *)segment(in_SS,sVar4);
    puVar2 = (undefined2 *)segment(in_SS,sVar4 + 2);
    puVar5 = (undefined2 *)CONCAT22((short)((uint)auStack_c >> 0x10),sVar4 + 4);
    out(*puVar1,(char)*puVar2);
    out(word_d8770,dword_d849c);
    out(word_d8772,0);
    out(word_d8776,3);
    puVar5[1] = CONCAT11((char)((ushort)*puVar2 >> 8),3);
    *puVar5 = uVar3;
    in(word_d8778);
    in(word_d8778);
    in(word_d8778);
    in(word_d8778);
    in(word_d8778);
    in(word_d8778);
    in(word_d8778);
    puVar1 = (undefined2 *)segment(in_SS,sVar4 + 4);
    puVar2 = (undefined2 *)segment(in_SS,sVar4 + 6);
    param_1 = *puVar2;
    out(*puVar1,(char)param_1);
    dword_d7af0 = 0;
  }
  return param_1;
}


// ================================================================================================
// sub_aee54 @ 0xaee54 [__cdecl]
// ================================================================================================

uint sub_aee54(uint param_1,byte *param_2,undefined4 param_3,uint param_4,undefined4 param_5,
              int param_6,undefined4 param_7,int param_8)

{
  byte bVar1;
  undefined *puVar2;
  uint in_EAX;
  uint uVar3;
  char cVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  byte in_CF;
  byte in_PF;
  byte in_AF;
  byte in_ZF;
  byte in_SF;
  byte in_TF;
  byte in_IF;
  byte in_OF;
  byte in_NT;
  byte in_AC;
  byte in_VIF;
  byte in_VIP;
  byte in_ID;
  uint uStack_1c;
  uint uStack_18;
  uint uStack_14;
  
  uStack_14 = (uint)(in_NT & 1) * 0x4000 | (uint)(in_OF & 1) * 0x800 | (uint)(in_IF & 1) * 0x200 |
              (uint)(in_TF & 1) * 0x100 | (uint)(in_SF & 1) * 0x80 | (uint)(in_ZF & 1) * 0x40 |
              (uint)(in_AF & 1) * 0x10 | (uint)(in_PF & 1) * 4 | (uint)(in_CF & 1) |
              (uint)(in_ID & 1) * 0x200000 | (uint)(in_VIP & 1) * 0x100000 |
              (uint)(in_VIF & 1) * 0x80000 | (uint)(in_AC & 1) * 0x40000;
  if (param_1 < 4) {
    puVar2 = (&off_d846c)[param_1];
    if (param_6 == 0) {
      uStack_18 = param_1;
      uStack_1c = 0xaee7f;
      sub_aefa2();
      return uStack_18;
    }
    uStack_18 = param_6;
    uStack_1c = param_1;
    sub_af076();
    iVar5 = CONCAT22((short)((uint)&uStack_1c >> 0x10),(short)&uStack_1c + 8);
    *(undefined4 *)(iVar5 + -4) = param_7;
    *(uint *)(iVar5 + -8) = param_1;
    *(undefined4 *)(iVar5 + -0xc) = 0xaeea0;
    sub_aefea();
    iVar6 = CONCAT22((short)((uint)(iVar5 + -8) >> 0x10),(short)(iVar5 + -8) + 8);
    *(undefined4 *)(iVar6 + -4) = param_5;
    *(uint *)(iVar6 + -8) = param_4;
    *(undefined4 *)(iVar6 + -0xc) = param_3;
    *(byte **)(iVar6 + -0x10) = param_2;
    *(uint *)(iVar6 + -0x14) = param_1;
    *(undefined4 *)(iVar6 + -0x18) = 0xaeeb8;
    sub_af0d5();
    iVar7 = CONCAT22((short)((uint)(iVar6 + -0x14) >> 0x10),(short)(iVar6 + -0x14) + 0x14);
    puVar2[0x4c] = 0;
    puVar2[0x50] = 0;
    puVar2[0xc] = (char)param_8;
    if ((param_8 != 0) && (param_4 != 0)) {
      cVar4 = '\0';
      uVar3 = 0;
      do {
        bVar1 = *param_2;
        param_2 = param_2 + 1;
        cVar4 = cVar4 + (char)*(undefined2 *)(&unk_d7414 + (uint)bVar1 * 2) +
                (char)((ushort)*(undefined2 *)(&unk_d7414 + (uint)bVar1 * 2) >> 8);
        uVar3 = uVar3 + 1;
      } while (uVar3 < param_4);
      puVar2[0x50] = cVar4;
    }
    *(undefined4 *)(iVar7 + -4) = 0x7f;
    *(undefined4 *)(iVar7 + -8) = 0xff;
    *(uint *)(iVar7 + -0xc) = param_1;
    *(undefined4 *)(iVar7 + -0x10) = 0xaef04;
    in_EAX = sub_aef33();
  }
  return in_EAX;
}


// ================================================================================================
// sub_aef0e @ 0xaef0e [__cdecl]
// ================================================================================================

undefined4 sub_aef0e(uint param_1)

{
  if ((param_1 < 4) && (*(int *)(&off_d846c)[param_1] != 0)) {
    return 0;
  }
  return 1;
}


// ================================================================================================
// sub_aef33 @ 0xaef33 [__watcall]
// ================================================================================================

undefined4 __watcall sub_aef33(void)

{
  undefined4 *puVar1;
  ulonglong uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  uint in_stack_00000004;
  byte in_stack_00000008;
  undefined4 in_stack_0000000c;
  
  if (in_stack_00000004 < 4) {
    puVar1 = (undefined4 *)(&off_d846c)[in_stack_00000004];
    puVar1[2] = (uint)in_stack_00000008;
    if (in_stack_00000008 != 0xff) {
      uVar2 = (ulonglong)*(uint *)(&unk_d6b00 + (uint)in_stack_00000008 * 4) *
              (ulonglong)(uint)puVar1[0xb] & 0xffffffff0000;
      uVar3 = (undefined4)uVar2;
      uVar4 = (undefined4)(uVar2 >> 0x20);
      puVar1[0x10] = uVar4;
      puVar1[0x11] = uVar3;
      puVar1[0xc] = uVar4;
      puVar1[0xd] = uVar3;
    }
    puVar1[9] = puVar1[6];
    uVar3 = puVar1[7];
    if (puVar1[4] == 0) {
      uVar3 = puVar1[8];
    }
    puVar1[10] = uVar3;
    in_stack_0000000c = puVar1[5];
    puVar1[0xe] = in_stack_0000000c;
    puVar1[0xf] = 0;
    *puVar1 = 1;
  }
  return in_stack_0000000c;
}


// ================================================================================================
// sub_aefa2 @ 0xaefa2 [__watcall]
// ================================================================================================

void __watcall sub_aefa2(void)

{
  undefined4 *puVar1;
  uint in_stack_00000004;
  
  if ((in_stack_00000004 < 4) && (1 < (int)in_stack_00000004)) {
    puVar1 = (undefined4 *)(&off_d846c)[in_stack_00000004];
    puVar1[10] = puVar1[7];
    *puVar1 = 0;
  }
  return;
}


// ================================================================================================
// sub_aefc9 @ 0xaefc9 [__cdecl]
// ================================================================================================

void sub_aefc9(uint param_1)

{
  if ((param_1 < 4) && (1 < (int)param_1)) {
    *(undefined4 *)(&off_d846c)[param_1] = 0;
  }
  return;
}


// ================================================================================================
// sub_aefea @ 0xaefea [__cdecl]
// ================================================================================================

void sub_aefea(uint param_1,int param_2)

{
  undefined *puVar1;
  undefined2 *puVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  
  if (param_1 < 4) {
    puVar1 = (&off_d846c)[param_1];
    if ((char)param_2 != puVar1[4]) {
      puVar1[4] = (char)param_2;
      uVar3 = 0;
      uVar5 = param_2 * -0x100;
      *(undefined2 *)(puVar1 + 0x58) = 0;
      *(short *)(puVar1 + 0x158) = (short)(uVar5 >> 1);
      iVar4 = 0x7f;
      puVar2 = (undefined2 *)(puVar1 + 0x58);
      do {
        uVar3 = uVar3 + (byte)((char)param_2 << 1);
        puVar2[1] = (short)(uVar3 >> 1);
        uVar5 = uVar5 + (byte)((char)param_2 << 1);
        puVar2[0x81] = (short)(uVar5 >> 1);
        iVar4 = iVar4 + -1;
        puVar2 = puVar2 + 1;
      } while (iVar4 != 0);
    }
  }
  return;
}


// ================================================================================================
// sub_af058 @ 0xaf058 [__watcall]
// ================================================================================================

void __watcall sub_af058(void)

{
  ushort in_stack_00000004;
  short in_stack_00000008;
  
  if (in_stack_00000004 < 4) {
    *(int *)((&off_d846c)[in_stack_00000004] + 0x48) = (int)in_stack_00000008;
  }
  return;
}


// ================================================================================================
// sub_af076 @ 0xaf076 [__watcall]
// ================================================================================================

void __watcall sub_af076(void)

{
  undefined *puVar1;
  uint uVar2;
  uint uVar3;
  uint in_stack_00000004;
  uint in_stack_00000008;
  
  if (in_stack_00000004 < 4) {
    puVar1 = (&off_d846c)[in_stack_00000004];
    uVar2 = in_stack_00000008 / 0x5622;
    *(uint *)(puVar1 + 0x40) = uVar2;
    *(uint *)(puVar1 + 0x30) = uVar2;
    uVar3 = (uint)(((ulonglong)in_stack_00000008 % 0x5622 << 0x20) / 0x5622);
    *(uint *)(puVar1 + 0x44) = uVar3;
    *(uint *)(puVar1 + 0x34) = uVar3;
    *(uint *)(puVar1 + 0x2c) = (uVar3 & 0xffff0000 | uVar2) >> 0x10 | uVar2 << 0x10;
    if (*(int *)(puVar1 + 0x2c) == 0x10000) {
      uVar2 = dword_d8484 >> 1;
    }
    else {
      uVar2 = dword_d8484 >> 2;
    }
    *(uint *)(puVar1 + 0x54) = uVar2;
  }
  return;
}


// ================================================================================================
// sub_af0d5 @ 0xaf0d5 [__watcall]
// ================================================================================================

void __watcall sub_af0d5(void)

{
  undefined *puVar1;
  uint param_5;
  int in_stack_00000008;
  int in_stack_0000000c;
  int in_stack_00000010;
  int in_stack_00000014;
  
  if (param_5 < 4) {
    puVar1 = (&off_d846c)[param_5];
    puVar1[0xc] = 0;
    *(int *)(puVar1 + 0x14) = in_stack_00000008;
    *(int *)(puVar1 + 0x20) = in_stack_0000000c + in_stack_00000008;
    *(int *)(puVar1 + 0x18) = in_stack_00000010 + in_stack_00000008;
    *(int *)(puVar1 + 0x1c) = in_stack_00000010 + in_stack_00000008 + in_stack_00000014;
    *(int *)(puVar1 + 0x10) = in_stack_00000014;
  }
  return;
}


// ================================================================================================
// sub_af112 @ 0xaf112 [__cdecl]
// ================================================================================================

uint sub_af112(uint param_1,uint param_2,int param_3,uint param_4,char param_5)

{
  undefined *puVar1;
  longlong lVar2;
  uint uVar3;
  uint uVar4;
  
  if (param_1 < 4) {
    puVar1 = (&off_d846c)[param_1];
    uVar4 = ((*(uint *)(puVar1 + 0x34) | *(uint *)(puVar1 + 0x30)) >> 0x10 |
            (*(uint *)(puVar1 + 0x34) | *(uint *)(puVar1 + 0x30)) << 0x10) + param_3;
    if (param_4 != 0) {
      uVar3 = ((uint)((ulonglong)
                      *(uint *)(&unk_d6b00 +
                               (uint)(byte)((char)*(undefined4 *)(puVar1 + 8) + param_5) * 4) *
                     (ulonglong)*(uint *)(puVar1 + 0x2c)) >> 0x10 |
              (int)((ulonglong)
                    *(uint *)(&unk_d6b00 +
                             (uint)(byte)((char)*(undefined4 *)(puVar1 + 8) + param_5) * 4) *
                    (ulonglong)*(uint *)(puVar1 + 0x2c) >> 0x20) << 0x10) - uVar4;
      if (((int)param_4 < 1) && ((int)param_4 < 0)) {
        lVar2 = (ulonglong)uVar3 * (ulonglong)-param_4;
        param_2 = (uint)lVar2 >> 0xe | (int)((ulonglong)lVar2 >> 0x20) << 0x12;
        uVar4 = uVar4 - param_2;
      }
      else {
        lVar2 = (ulonglong)uVar3 * (ulonglong)param_4;
        param_2 = (uint)lVar2 >> 0xe | (int)((ulonglong)lVar2 >> 0x20) << 0x12;
        uVar4 = uVar4 + param_2;
      }
    }
    *(uint *)(puVar1 + 0x44) = uVar4 << 0x10;
    *(uint *)(puVar1 + 0x40) = uVar4 >> 0x10;
  }
  return param_2;
}


// ================================================================================================
// sub_af198 @ 0xaf198 [__watcall]
// ================================================================================================

uint __watcall sub_af198(void)

{
  return dword_d7afc | dword_d7b08;
}


// ================================================================================================
// sub_af1a4 @ 0xaf1a4 [__cdecl]
// ================================================================================================

undefined sub_af1a4(uint param_1)

{
  if (param_1 < 4) {
    return (&off_d846c)[param_1][4];
  }
  return 0;
}


// ================================================================================================
// sub_af1d0 @ 0xaf1d0 [__watcall]
// ================================================================================================

undefined8 __watcall
sub_af1d0(int param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  undefined uVar1;
  undefined2 uVar2;
  char *pcVar3;
  
  pcVar3 = (char *)sub_a6b87(off_d84cc);
  dword_f612c = pcVar3;
  if (pcVar3 != (char *)0x0) {
    uVar2 = sub_a6d24(pcVar3,&dword_f612c,0x10,param_1,unaff_EDX,unaff_ECX,unaff_EBX);
    *(undefined2 *)(param_1 + 2) = uVar2;
    if (*dword_f612c == ',') {
      dword_f612c = dword_f612c + 1;
    }
    uVar1 = sub_a6d24(dword_f612c,&dword_f612c,10,param_1,unaff_EDX,unaff_ECX,unaff_EBX);
    *(undefined *)(param_1 + 7) = uVar1;
    if (*dword_f612c == ',') {
      dword_f612c = dword_f612c + 1;
    }
    uVar1 = sub_a6d24(dword_f612c,&dword_f612c,10,param_1,unaff_EDX,unaff_ECX,unaff_EBX);
    *(undefined *)(param_1 + 6) = uVar1;
    if (*dword_f612c == ',') {
      dword_f612c = dword_f612c + 1;
    }
    uVar1 = sub_a6d24(dword_f612c,&dword_f612c,10,param_1,unaff_EDX,unaff_ECX,unaff_EBX);
    *(undefined *)(param_1 + 4) = uVar1;
    if (*dword_f612c == ',') {
      dword_f612c = dword_f612c + 1;
    }
    uVar1 = sub_a6d24(dword_f612c,&dword_f612c,10);
    *(undefined *)(param_1 + 5) = uVar1;
    if ((((*(short *)(param_1 + 2) == 0) || (*(char *)(param_1 + 6) == '\0')) ||
        (*(char *)(param_1 + 7) == '\0')) ||
       ((*(char *)(param_1 + 4) == '\0' || (*(char *)(param_1 + 5) == '\0')))) {
      pcVar3 = (char *)0x0;
    }
    else {
      pcVar3 = (char *)0x1;
    }
  }
  return CONCAT44(unaff_EDX,pcVar3);
}


// ================================================================================================
// sub_af2e0 @ 0xaf2e0 [__watcall]
// ================================================================================================

undefined8 __watcall sub_af2e0(short param_1,undefined4 unaff_EDX)

{
  int iVar1;
  undefined4 uVar2;
  
  sub_aa200(param_1 + 8,0xaa);
  iVar1 = sub_b128c(param_1 + 10);
  if (iVar1 == 0xaa) {
    sub_aa200(param_1 + 8,0x55);
    iVar1 = sub_b128c(param_1 + 10);
    if (iVar1 == 0x55) {
      uVar2 = 1;
      goto LAB_000af337;
    }
  }
  uVar2 = 0;
LAB_000af337:
  return CONCAT44(unaff_EDX,uVar2);
}


// ================================================================================================
// sub_af340 @ 0xaf340 [__watcall]
// ================================================================================================

void __watcall sub_af340(int param_1,int unaff_EDX,int unaff_EBX)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  bool bVar4;
  
  if (*(int *)(&unk_d84d0 + param_1 * 4) == 0) {
    iVar3 = 0x400;
  }
  else {
    iVar1 = (unaff_EDX + unaff_EBX * 0x80 + -0x2000) * *(int *)(&unk_d84d0 + param_1 * 4);
    bVar4 = iVar1 < 0;
    if (bVar4) {
      iVar1 = -iVar1;
    }
    uVar2 = iVar1 >> 0xd;
    iVar3 = *(int *)(&unk_d7abc + (uVar2 % 0xc) * 4) << ((byte)(uVar2 / 0xc) & 0x1f);
    iVar3 = iVar3 + ((uint)(((*(int *)(&unk_d7abc + ((uVar2 + 1) % 0xc) * 4) <<
                             ((byte)((uVar2 + 1) / 0xc) & 0x1f)) - iVar3) * (iVar1 % 0x2000)) >> 0xd
                    );
    if (bVar4) {
      iVar3 = (int)(0x100000 / (longlong)iVar3);
    }
  }
  sub_ab6d0(param_1,iVar3);
  return;
}


// ================================================================================================
// sub_af428 @ 0xaf428 [__watcall]
// ================================================================================================

void __watcall sub_af428(int param_1,uint unaff_EDX,int unaff_EBX)

{
  int iVar1;
  
  if (unaff_EDX < 0x2b) {
    if (unaff_EDX < 10) {
      if (unaff_EDX < 6) {
        if (unaff_EDX == 1) {
          sub_ab80c(param_1,unaff_EBX);
          return;
        }
      }
      else {
        if (6 < unaff_EDX) {
          if (unaff_EDX != 7) {
            return;
          }
          *(int *)(&unk_d85d0 + param_1 * 4) = unaff_EBX;
          sub_ab658(param_1,(*(int *)(&unk_d8610 + param_1 * 4) * unaff_EBX) / 0x7f);
          return;
        }
        if ((*(int *)(&unk_d8550 + param_1 * 4) == 0) && (*(int *)(&unk_d8590 + param_1 * 4) == 0))
        {
          if (0x18 < unaff_EBX) {
            unaff_EBX = 0x18;
          }
          *(int *)(&unk_d84d0 + param_1 * 4) = unaff_EBX;
          return;
        }
      }
    }
    else {
      if (unaff_EDX < 0xb) {
        sub_ad2a8(unaff_EBX,param_1);
        return;
      }
      if (unaff_EDX < 0x26) {
        if (unaff_EDX != 0xb) {
          return;
        }
        *(int *)(&unk_d8610 + param_1 * 4) = unaff_EBX;
        sub_ab658(param_1,(*(int *)(&unk_d85d0 + param_1 * 4) * unaff_EBX) / 0x7f);
        return;
      }
      if (unaff_EDX < 0x27) {
        if ((*(int *)(&unk_d8550 + param_1 * 4) == 0) && (*(int *)(&unk_d8590 + param_1 * 4) == 0))
        {
          *(int *)(&unk_d8510 + param_1 * 4) = unaff_EBX;
          return;
        }
      }
      else if (unaff_EDX != 0x27) {
        return;
      }
    }
  }
  else if (0x2b < unaff_EDX) {
    iVar1 = param_1 * 4;
    if (unaff_EDX < 100) {
      if (unaff_EDX < 0x60) {
        if (unaff_EDX != 0x40) {
          return;
        }
        sub_acc3c(param_1,0x17 < unaff_EBX);
        return;
      }
      if (unaff_EDX < 0x61) {
        if ((*(int *)(&unk_d8550 + iVar1) == 0) && (*(int *)(&unk_d8590 + iVar1) == 0)) {
          *(int *)(&unk_d8510 + iVar1) = *(int *)(&unk_d8510 + iVar1) + unaff_EBX;
          return;
        }
      }
      else {
        if (unaff_EDX != 0x61) {
          return;
        }
        if ((*(int *)(&unk_d8550 + iVar1) == 0) && (*(int *)(&unk_d8590 + iVar1) == 0)) {
          *(int *)(&unk_d8510 + iVar1) = *(int *)(&unk_d8510 + iVar1) - unaff_EBX;
          return;
        }
      }
    }
    else {
      if (unaff_EDX < 0x65) {
        *(int *)(&unk_d8590 + iVar1) = unaff_EBX;
        return;
      }
      if (unaff_EDX < 0x78) {
        if (unaff_EDX == 0x65) {
          *(int *)(&unk_d8550 + iVar1) = unaff_EBX;
          return;
        }
      }
      else {
        if (0x78 < unaff_EDX) {
          if (unaff_EDX < 0x7a) {
            sub_acc3c(param_1,0);
            sub_ab80c(param_1,0);
            sub_ab6d0(param_1,0x400);
            *(undefined4 *)(&unk_d85d0 + iVar1) = 100;
            *(undefined4 *)(&unk_d8610 + iVar1) = 0x7f;
            sub_ab658(param_1,100);
            sub_ad2a8(param_1,0xffffffff);
            return;
          }
          if (unaff_EDX < 0x7b) {
            return;
          }
          if (0x7f < unaff_EDX) {
            return;
          }
        }
        sub_ad344(param_1);
      }
    }
  }
  return;
}


// ================================================================================================
// sub_af6d3 @ 0xaf6d3 [__watcall]
// ================================================================================================

void __watcall sub_af6d3(void)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  char *pcVar4;
  int iVar5;
  size_t __n;
  undefined8 uVar6;
  
  pcVar4 = dword_d4d09;
  if (dword_d5444 == 0) {
    iVar5 = 0;
    pcVar3 = dword_d4d09;
    while (*pcVar3 != '\0') {
      do {
        cVar1 = *pcVar3;
        pcVar3 = pcVar3 + 1;
      } while (cVar1 != '\0');
      iVar5 = iVar5 + 1;
    }
    iVar2 = (int)pcVar3 - (int)dword_d4d09;
    if (iVar2 == 0) {
      iVar2 = 1;
    }
    pcVar3 = (char *)sub_91984(iVar2);
    if (pcVar3 != (char *)0x0) {
      uVar6 = sub_91984(iVar5 * 5 + 4,pcVar3);
      if ((int)uVar6 == 0) {
        sub_91a67((int)((ulonglong)uVar6 >> 0x20));
      }
      else {
        __n = 0;
        iVar5 = 0;
        dword_d5444 = (int)uVar6;
        while (iVar2 = dword_d5444, *pcVar4 != '\0') {
          *(char **)(iVar5 + dword_d5444) = pcVar3;
          do {
            cVar1 = *pcVar4;
            pcVar4 = pcVar4 + 1;
            *pcVar3 = cVar1;
            pcVar3 = pcVar3 + 1;
          } while (cVar1 != '\0');
          iVar5 = iVar5 + 4;
          __n = __n + 1;
        }
        *(undefined4 *)(iVar5 + dword_d5444) = 0;
        dword_d5448 = (void *)(iVar2 + iVar5 + 4);
        memset(dword_d5448,0,__n);
      }
    }
  }
  return;
}


// ================================================================================================
// sub_af7a7 @ 0xaf7a7 [__watcall]
// ================================================================================================

void __watcall sub_af7a7(char *param_1,char *unaff_EDX)

{
  char cVar1;
  
  for (; cVar1 = *unaff_EDX, *param_1 = cVar1, cVar1 != '\0'; unaff_EDX = unaff_EDX + 1) {
    param_1 = param_1 + 1;
  }
  return;
}


// ================================================================================================
// sub_af7b6 @ 0xaf7b6 [__watcall]
// ================================================================================================

uint __watcall
sub_af7b6(int *param_1,int *param_2,undefined4 *param_3,undefined4 *unaff_ECX,undefined4 *param_5,
         undefined4 *param_6,int param_7)

{
  undefined4 uVar1;
  size_t sVar2;
  undefined *puVar3;
  int *piVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  
  if (param_2 == (int *)0x0) {
    param_2 = dword_d5444;
  }
  iVar6 = 0;
  piVar4 = param_2;
  if (param_2 != (int *)0x0) {
    for (; *piVar4 != 0; piVar4 = piVar4 + 1) {
      sVar2 = strlen((char *)*piVar4);
      iVar6 = iVar6 + sVar2 + 1;
    }
  }
  iVar6 = iVar6 + 1;
  if (param_7 != 0) {
    sVar2 = strlen((char *)*param_1);
    iVar6 = iVar6 + sVar2 + 3;
  }
  uVar1 = dword_d5674;
  uVar7 = iVar6 + 0xf;
  dword_d5674 = 0x10;
  puVar3 = (undefined *)sub_91984(uVar7);
  if ((puVar3 == (undefined *)0x0) &&
     (puVar3 = (undefined *)sub_91984(uVar7), puVar3 == (undefined *)0x0)) {
    sub_9878a(5);
    sub_987ad(8);
    dword_d5674 = uVar1;
  }
  else {
    dword_d5674 = uVar1;
    *param_3 = puVar3;
    *param_5 = 0;
    *unaff_ECX = puVar3;
    if (param_2 != (int *)0x0) {
      for (; *param_2 != 0; param_2 = param_2 + 1) {
        iVar6 = sub_af7a7(puVar3,*param_2);
        puVar3 = (undefined *)(iVar6 + 1);
      }
    }
    *puVar3 = 0;
    if (param_7 != 0) {
      strcpy(puVar3 + 3,(char *)*param_1);
    }
    uVar5 = 0;
    if (*param_1 != 0) {
      for (param_1 = param_1 + 1; (char *)*param_1 != (char *)0x0; param_1 = param_1 + 1) {
        if (uVar5 != 0) {
          uVar5 = uVar5 + 1;
        }
        sVar2 = strlen((char *)*param_1);
        uVar5 = uVar5 + sVar2;
      }
    }
    if (uVar5 < 0x7f) {
      *param_6 = 0x90;
      return uVar7 >> 4;
    }
    sub_9878a(2);
    sub_987ad(10);
    sub_91a67(*param_3);
  }
  return 0xffffffff;
}


// ================================================================================================
// sub_af8ee @ 0xaf8ee [__watcall]
// ================================================================================================

void __watcall sub_af8ee(undefined4 param_1,int *unaff_EDX,char *unaff_EBX,int unaff_ECX)

{
  char *pcVar1;
  char *pcVar2;
  
  pcVar2 = unaff_EBX;
  if (unaff_ECX == 0) {
    pcVar2 = unaff_EBX + 1;
  }
  pcVar1 = pcVar2;
  if ((*unaff_EDX != 0) && (unaff_EDX = unaff_EDX + 1, *unaff_EDX != 0)) {
    while( true ) {
      pcVar1 = (char *)sub_af7a7(pcVar2,*unaff_EDX);
      unaff_EDX = unaff_EDX + 1;
      if (*unaff_EDX == 0) break;
      pcVar2 = pcVar1 + 1;
      *pcVar1 = ' ';
    }
  }
  if (unaff_ECX != 0) {
    *pcVar1 = '\0';
    return;
  }
  *pcVar1 = '\r';
  *unaff_EBX = ((char)pcVar1 - (char)unaff_EBX) + -1;
  return;
}


// ================================================================================================
// sub_af943 @ 0xaf943 [__cdecl]
// ================================================================================================

void sub_af943(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  code *pcVar1;
  undefined *puVar2;
  undefined2 uVar3;
  undefined *puVar4;
  undefined2 in_SS;
  byte bVar5;
  undefined auStack_2c [8];
  undefined *puStack_24;
  
  puStack_24 = &stack0xfffffffc;
  dword_d8690 = param_4;
  dword_d869c = 0;
  dword_d86a2 = 0;
  word_d86a0 = 0;
  word_d86a6 = 0;
  dword_d86a8 = 0;
  dword_d86ac = 0;
  dword_d8696 = param_3;
  dword_d86b0 = auStack_2c;
  bVar5 = 0;
  pcVar1 = (code *)swi(0x21);
  word_d8694 = in_SS;
  word_d869a = in_SS;
  word_d86b4 = in_SS;
  word_d86b6 = in_SS;
  (*pcVar1)();
  dword_d4d00 = 1;
  pcVar1 = (code *)swi(0x21);
  uVar3 = (*pcVar1)();
  puVar2 = dword_d86b0;
  dword_d4d00 = 0;
  puVar4 = dword_d86b0 + 0xc;
  if (!(bool)bVar5) {
    pcVar1 = (code *)swi(0x21);
    uVar3 = (*pcVar1)();
    puVar4 = puVar2 + 0x10;
  }
  *(undefined4 *)(puVar4 + -4) = 0xafa08;
  sub_9a730(uVar3,-(uint)bVar5,&dword_d8690);
  return;
}


// ================================================================================================
// sub_afa11 @ 0xafa11 [__watcall]
// ================================================================================================

undefined4 * __watcall
sub_afa11(undefined4 *param_1,undefined4 *unaff_EDX,undefined4 *unaff_EBX,int unaff_ECX)

{
  uint uVar1;
  uint uVar2;
  undefined4 *puVar3;
  
  if (param_1 == (undefined4 *)0x0) {
    return unaff_EDX;
  }
  uVar2 = unaff_ECX - (int)unaff_EBX;
  *param_1 = unaff_EDX;
  if (0x92 < uVar2) {
    uVar2 = 0x92;
  }
  puVar3 = unaff_EDX;
  for (uVar1 = uVar2 >> 2; uVar1 != 0; uVar1 = uVar1 - 1) {
    *puVar3 = *unaff_EBX;
    unaff_EBX = unaff_EBX + 1;
    puVar3 = puVar3 + 1;
  }
  for (uVar1 = uVar2 & 3; uVar1 != 0; uVar1 = uVar1 - 1) {
    *(undefined *)puVar3 = *(undefined *)unaff_EBX;
    unaff_EBX = (undefined4 *)((int)unaff_EBX + 1);
    puVar3 = (undefined4 *)((int)puVar3 + 1);
  }
  *(undefined *)((int)unaff_EDX + uVar2) = 0;
  return (undefined4 *)((undefined *)((int)unaff_EDX + uVar2) + 1);
}


// ================================================================================================
// sub_afa55 @ 0xafa55 [__watcall]
// ================================================================================================

void __watcall
sub_afa55(char *param_1,char *param_2,undefined4 *unaff_EBX,undefined4 unaff_ECX,undefined4 param_5,
         undefined4 param_6)

{
  char cVar1;
  undefined4 uVar2;
  char *pcVar3;
  char *pcVar4;
  char *pcVar5;
  
  if ((*param_1 == '\0') || (param_1[1] != ':')) {
    if (unaff_EBX != (undefined4 *)0x0) {
      *unaff_EBX = param_2;
      *param_2 = '\0';
    }
  }
  else {
    if (unaff_EBX != (undefined4 *)0x0) {
      *unaff_EBX = param_2;
      cVar1 = *param_1;
      param_2[1] = ':';
      param_2[2] = '\0';
      *param_2 = cVar1;
    }
    param_1 = param_1 + 2;
  }
  do {
    pcVar3 = param_1;
    param_1 = pcVar3;
    pcVar5 = (char *)0x0;
    do {
      while( true ) {
        pcVar4 = param_1;
        cVar1 = *pcVar4;
        if (cVar1 == '\0') {
          uVar2 = sub_afa11(unaff_ECX);
          if (pcVar5 == (char *)0x0) {
            pcVar5 = pcVar4;
          }
          uVar2 = sub_afa11(param_5,uVar2,pcVar3,pcVar5);
          sub_afa11(param_6,uVar2,pcVar5,pcVar4);
          return;
        }
        if (cVar1 != '.') break;
        param_1 = pcVar4 + 1;
        pcVar5 = pcVar4;
      }
      param_1 = pcVar4 + 1;
    } while ((cVar1 != '\\') && (cVar1 != '/'));
  } while( true );
}


// ================================================================================================
// sub_afae0 @ 0xafae0 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall sub_afae0(void)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  int *piVar7;
  int *piVar8;
  int *piVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  uint uVar15;
  int iVar16;
  int iVar17;
  uint uVar18;
  bool bVar19;
  int in_stack_00000004;
  int in_stack_00000008;
  int *in_stack_0000000c;
  uint local_6c;
  int local_58;
  int local_54;
  int local_50;
  int local_4c;
  uint local_48;
  uint local_44;
  int local_40;
  int local_3c;
  int local_30;
  int local_2c;
  int local_28;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  
  iVar11 = *(int *)(in_stack_00000004 + 2) >> 0x10;
  sub_b72d4(in_stack_00000004 + 0x10,&unk_f6138);
  uVar15 = 0;
  uVar18 = 0;
  iVar17 = in_stack_0000000c[1];
  local_58 = *in_stack_0000000c;
  uVar2 = 1;
  piVar6 = in_stack_0000000c;
  local_3c = local_58;
  local_1c = iVar17;
  do {
    piVar7 = piVar6 + 2;
    iVar3 = piVar6[3];
    if (local_1c < iVar3) {
      local_58 = *piVar7;
      uVar15 = uVar2;
      local_1c = iVar3;
    }
    else if (iVar3 < iVar17) {
      local_3c = *piVar7;
      iVar17 = iVar3;
      uVar18 = uVar2;
    }
    uVar2 = uVar2 + 1;
    piVar6 = piVar7;
  } while ((int)uVar2 < 3);
  iVar3 = local_58 - local_3c;
  iVar4 = local_1c - iVar17;
  if (iVar4 == 0) {
    return;
  }
  iVar5 = 3 - (uVar18 | uVar15);
  iVar10 = (in_stack_0000000c + iVar5 * 2)[1];
  iVar1 = in_stack_0000000c[iVar5 * 2];
  iVar13 = iVar1 - (((iVar10 - iVar17) * iVar3) / iVar4 + local_3c);
  bVar19 = iVar13 < 0;
  if (bVar19) {
    iVar13 = -iVar13;
  }
  local_6c = (uint)bVar19;
  if (iVar13 == 0) {
    return;
  }
  if (0x5ff < iVar13) {
    return;
  }
  iVar13 = iVar13 + 2;
  piVar6 = (int *)(in_stack_00000008 + iVar5 * 8);
  piVar7 = (int *)(in_stack_00000008 + uVar18 * 8);
  piVar8 = (int *)(in_stack_00000008 + uVar15 * 8);
  local_50 = ((*piVar6 - (*piVar8 + ((*piVar7 - *piVar8) * (local_1c - iVar10)) / iVar4)) * 0x10000)
             / iVar13;
  local_54 = ((piVar6[1] - (piVar8[1] + ((piVar7[1] - piVar8[1]) * (local_1c - iVar10)) / iVar4)) *
             0x10000) / iVar13;
  if (local_6c != 0) {
    local_50 = -local_50;
    local_54 = -local_54;
  }
  piVar9 = &unk_f6138;
  iVar5 = 0x8000;
  iVar16 = 0x8000;
  while (iVar13 = iVar13 + -1, iVar13 != -1) {
    *piVar9 = (iVar16 >> 0x10) * iVar11 + (iVar5 >> 0x10);
    piVar9 = piVar9 + 1;
    iVar5 = iVar5 + local_50;
    iVar16 = iVar16 + local_54;
  }
  local_14 = local_3c * 0x10000 + 0x8000;
  iVar13 = local_3c * 0x10000 + 0x10000;
  iVar5 = *piVar7 * 0x10000 + 0x8000;
  local_18 = piVar7[1] * 0x10000 + 0x8000;
  local_30 = 0;
  local_2c = 0;
  if (local_6c == 0) {
    iVar16 = iVar17 - local_1c;
    if (iVar16 == 0) goto LAB_000afdc5;
    local_2c = ((*piVar7 - *piVar8) * 0x10000) / iVar16;
    iVar12 = piVar7[1] - piVar8[1];
  }
  else {
    iVar16 = iVar17 - iVar10;
    if (iVar16 == 0) goto LAB_000afdc5;
    local_2c = ((*piVar7 - *piVar6) * 0x10000) / iVar16;
    iVar12 = piVar7[1] - piVar6[1];
  }
  local_30 = (iVar12 * 0x10000) / iVar16;
LAB_000afdc5:
  local_4c = 0;
  local_40 = 0;
  if (iVar17 != iVar10) {
    iVar16 = iVar17 - iVar10;
    iVar12 = (local_3c - iVar1) * 0x10000;
    if (local_6c == 0) {
      if (iVar16 != 0) {
        local_40 = iVar12 / iVar16;
        local_4c = (iVar3 * 0x10000) / iVar4;
      }
    }
    else if (iVar16 != 0) {
      local_4c = iVar12 / iVar16;
      local_40 = (iVar3 * 0x10000) / iVar4;
    }
    iVar13 = iVar13 + local_40 / 2;
    if (iVar17 < iVar10) {
      local_20 = iVar17 * 4;
      do {
        if (dword_d30b8 <= iVar17) {
          return;
        }
        iVar14 = local_14 >> 0x10;
        iVar16 = ((iVar13 >> 0x10) - iVar14) + 1;
        iVar12 = (iVar14 + iVar16) - _dword_d30b4;
        if (0 < iVar12) {
          iVar16 = iVar16 - iVar12;
        }
        iVar12 = dword_d30ac - iVar14;
        if (iVar12 < 1) {
          iVar12 = 0;
        }
        else {
          iVar16 = iVar16 - iVar12;
          iVar14 = iVar14 + iVar12;
          if (0x600 < iVar12) {
            return;
          }
        }
        if ((0 < iVar16) && (dword_d30b0 < iVar17)) {
          sub_b7420(iVar14 + *(int *)(off_d30cc + local_20),
                    (iVar5 >> 0x10) + iVar11 * (local_18 >> 0x10) + (&unk_f6138)[iVar12],iVar16);
        }
        iVar5 = iVar5 + local_2c;
        local_18 = local_18 + local_30;
        local_14 = local_14 + local_4c;
        iVar13 = iVar13 + local_40;
        local_20 = local_20 + 4;
        iVar17 = iVar17 + 1;
      } while (iVar17 < iVar10);
    }
  }
  if (iVar17 != local_1c) {
    iVar10 = iVar10 - local_1c;
    iVar16 = (iVar1 - local_58) * 0x10000;
    if (local_6c == 0) {
      local_44 = local_6c;
      local_48 = local_6c;
      if (iVar10 != 0) {
        local_48 = iVar16 / iVar10;
        local_44 = (iVar3 * 0x10000) / iVar4;
        iVar13 = iVar1 * 0x10000 + 0x100;
      }
    }
    else {
      local_30 = 0;
      local_2c = 0;
      local_44 = 0;
      local_48 = 0;
      if (iVar10 != 0) {
        local_44 = iVar16 / iVar10;
        local_48 = (iVar3 * 0x10000) / iVar4;
        local_14 = iVar1 * 0x10000 + 0x8000;
        iVar5 = *piVar6 * 0x10000 + 0x8000;
        local_18 = piVar6[1] * 0x10000 + 0x8000;
        local_2c = ((*piVar6 - *piVar8) * 0x10000) / iVar10;
        local_30 = ((piVar6[1] - piVar8[1]) * 0x10000) / iVar10;
      }
    }
    local_28 = iVar17 * 4;
    for (; (iVar17 < local_1c && (iVar17 < dword_d30b8)); iVar17 = iVar17 + 1) {
      iVar4 = local_14 >> 0x10;
      iVar3 = ((iVar13 >> 0x10) - iVar4) + 1;
      iVar10 = (iVar4 + iVar3) - _dword_d30b4;
      if (0 < iVar10) {
        iVar3 = iVar3 - iVar10;
      }
      iVar10 = dword_d30ac - iVar4;
      if (iVar10 < 1) {
        iVar10 = 0;
      }
      else {
        iVar3 = iVar3 - iVar10;
        iVar4 = iVar4 + iVar10;
        if (0x600 < iVar10) {
          return;
        }
      }
      if ((0 < iVar3) && (dword_d30b0 <= iVar17)) {
        sub_b7420(iVar4 + *(int *)(off_d30cc + local_28),
                  (iVar5 >> 0x10) + iVar11 * (local_18 >> 0x10) + (&unk_f6138)[iVar10],iVar3);
      }
      iVar5 = iVar5 + local_2c;
      local_18 = local_18 + local_30;
      local_14 = local_14 + local_44;
      iVar13 = iVar13 + local_48;
      local_28 = local_28 + 4;
    }
  }
  return;
}


// ================================================================================================
// sub_b00e4 @ 0xb00e4 [__watcall]
// ================================================================================================

char * __watcall sub_b00e4(char *param_1,char unaff_DL)

{
  char cVar1;
  char *pcVar2;
  
  pcVar2 = (char *)0x0;
  do {
    if (unaff_DL == *param_1) {
      pcVar2 = param_1;
    }
    cVar1 = *param_1;
    param_1 = param_1 + 1;
  } while (cVar1 != '\0');
  return pcVar2;
}


// ================================================================================================
// sub_b0100 @ 0xb0100 [__watcall]
// ================================================================================================

int __watcall sub_b0100(void)

{
  byte bVar1;
  byte bVar2;
  int iVar3;
  byte *in_stack_00000004;
  int in_stack_00000008;
  
  iVar3 = 0;
  bVar2 = 0;
  while (in_stack_00000008 = in_stack_00000008 + -1, in_stack_00000008 != -1) {
    bVar1 = *in_stack_00000004;
    in_stack_00000004 = in_stack_00000004 + 1;
    iVar3 = iVar3 + ((uint)bVar1 << (bVar2 & 0x1f));
    bVar2 = bVar2 + 8;
  }
  return iVar3;
}


// ================================================================================================
// sub_b0128 @ 0xb0128 [__cdecl]
// ================================================================================================

int sub_b0128(byte *param_1,int param_2)

{
  byte bVar1;
  int iVar2;
  
  iVar2 = 0;
  while (param_2 = param_2 + -1, param_2 != -1) {
    bVar1 = *param_1;
    param_1 = param_1 + 1;
    iVar2 = iVar2 * 0x100 + (uint)bVar1;
  }
  return iVar2;
}


// ================================================================================================
// sub_b0148 @ 0xb0148 [__cdecl]
// ================================================================================================

void sub_b0148(undefined *param_1,uint param_2,int param_3)

{
  undefined local_4;
  
  if (param_3 != 0) {
    do {
      local_4 = (undefined)param_2;
      *param_1 = local_4;
      param_2 = param_2 >> 8;
      param_1 = param_1 + 1;
      param_3 = param_3 + -1;
    } while (param_3 != 0);
  }
  return;
}


// ================================================================================================
// sub_b0170 @ 0xb0170 [__watcall]
// ================================================================================================

undefined * __watcall sub_b0170(void)

{
  undefined *in_stack_00000004;
  int in_stack_00000008;
  int in_stack_0000000c;
  undefined local_4;
  
  in_stack_00000008 = in_stack_00000008 << (('\x04' - (char)in_stack_0000000c) * '\b' & 0x1fU);
  if (in_stack_0000000c != 0) {
    do {
      local_4 = (undefined)((uint)in_stack_00000008 >> 0x18);
      *in_stack_00000004 = local_4;
      in_stack_00000008 = in_stack_00000008 << 8;
      in_stack_00000004 = in_stack_00000004 + 1;
      in_stack_0000000c = in_stack_0000000c + -1;
    } while (in_stack_0000000c != 0);
  }
  return in_stack_00000004;
}


// ================================================================================================
// sub_b01b0 @ 0xb01b0 [__watcall]
// ================================================================================================

void __watcall sub_b01b0(void)

{
  byte bVar1;
  byte *in_stack_00000004;
  byte *in_stack_00000008;
  int in_stack_0000000c;
  
  while (in_stack_0000000c = in_stack_0000000c + -1, in_stack_0000000c != -1) {
    bVar1 = *in_stack_00000004;
    in_stack_00000004 = in_stack_00000004 + 1;
    if (bVar1 == 0xff) {
      in_stack_00000008 = in_stack_00000008 + 1;
    }
    else {
      if (bVar1 == 0xfe) {
        bVar1 = *(byte *)((int)&unk_d89e4 + (uint)*in_stack_00000008);
      }
      *in_stack_00000008 = bVar1;
      in_stack_00000008 = in_stack_00000008 + 1;
    }
  }
  return;
}


// ================================================================================================
// sub_b01e4 @ 0xb01e4 [__cdecl]
// ================================================================================================

void sub_b01e4(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  if (dword_d30c8 == 0) {
    sub_b77f4(param_1,param_2,param_3);
    return;
  }
  funcptr_d43e4 = sub_b01b0;
  drawshape2(param_1,param_2,param_3);
  funcptr_d43e4 = sub_b3abc;
  return;
}


// ================================================================================================
// sub_b0228 @ 0xb0228 [__cdecl]
// ================================================================================================

void sub_b0228(int param_1)

{
  sub_b01e4(param_1,*(int *)(param_1 + 10) >> 0x10,*(int *)(param_1 + 0xc) >> 0x10);
  return;
}


// ================================================================================================
// sub_b0244 @ 0xb0244 [__cdecl]
// ================================================================================================

void sub_b0244(int param_1,int param_2,int param_3)

{
  sub_b01e4(param_1,param_2 - (*(int *)(param_1 + 6) >> 0x10),
            param_3 - (*(int *)(param_1 + 8) >> 0x10));
  return;
}


// ================================================================================================
// sub_b026c @ 0xb026c [__cdecl]
// ================================================================================================

byte sub_b026c(byte *param_1,int param_2,int param_3)

{
  byte bVar1;
  
  bVar1 = 0;
  if (param_3 != 0) {
    do {
      bVar1 = *(byte *)(param_2 + (uint)*param_1);
      *param_1 = bVar1;
      param_3 = param_3 + -1;
      param_1 = param_1 + 1;
    } while (param_3 != 0);
  }
  return bVar1;
}


// ================================================================================================
// sub_b0288 @ 0xb0288 [__watcall]
// ================================================================================================

void __watcall sub_b0288(undefined4 param_1)

{
  dword_d86c0 = param_1;
  return;
}


// ================================================================================================
// sub_b028e @ 0xb028e [__watcall]
// ================================================================================================

int __watcall sub_b028e(char *param_1,int unaff_EDX,int unaff_EBX,int unaff_ECX)

{
  int iVar1;
  int iVar2;
  int iVar3;
  char local_10;
  
  if (unaff_EDX < 0) {
    unaff_EDX = -unaff_EDX;
    local_10 = '-';
  }
  else {
    local_10 = '+';
  }
  iVar2 = 100;
  iVar1 = 3;
  if (unaff_EDX < 100) {
    iVar2 = 10;
    iVar1 = 2;
    if (unaff_EDX < 10) {
      iVar1 = 1;
      iVar2 = 1;
    }
  }
  if ((unaff_EBX == 0) && (unaff_EBX = 2, iVar1 == 3)) {
    unaff_EBX = 3;
  }
  iVar3 = unaff_EBX + 1;
  if (iVar3 <= unaff_ECX) {
    if (unaff_EBX < iVar1) {
      iVar3 = iVar1 + 1;
    }
    else {
      *param_1 = local_10;
      for (; param_1 = param_1 + 1, iVar1 < unaff_EBX; unaff_EBX = unaff_EBX + -1) {
        *param_1 = '0';
      }
      do {
        *param_1 = (char)(unaff_EDX / iVar2) + '0';
        unaff_EDX = unaff_EDX % iVar2;
        iVar2 = iVar2 / 10;
        param_1 = param_1 + 1;
      } while (iVar2 != 0);
    }
  }
  return iVar3;
}


// ================================================================================================
// sub_b0335 @ 0xb0335 [__watcall]
// ================================================================================================

char * __watcall sub_b0335(char *param_1,char *unaff_EDX,int unaff_EBX,int unaff_ECX)

{
  char cVar1;
  
  if ((unaff_ECX == 0) && (unaff_EBX < 1)) {
    *param_1 = '0';
    param_1[1] = '.';
    return param_1 + 2;
  }
  for (; (0 < unaff_EBX && (*unaff_EDX != '\0')); unaff_EDX = unaff_EDX + 1) {
    unaff_EBX = unaff_EBX + -1;
    *param_1 = *unaff_EDX;
    param_1 = param_1 + 1;
  }
  for (; 0 < unaff_EBX; unaff_EBX = unaff_EBX + -1) {
    *param_1 = '0';
    param_1 = param_1 + 1;
  }
  *param_1 = '.';
  param_1 = param_1 + 1;
  if (0 < unaff_ECX) {
    do {
      if (unaff_EBX == 0) break;
      unaff_EBX = unaff_EBX + 1;
      *param_1 = '0';
      param_1 = param_1 + 1;
      unaff_ECX = unaff_ECX + -1;
    } while (unaff_ECX != 0);
  }
  if (0 < unaff_ECX) {
    do {
      cVar1 = *unaff_EDX;
      if (cVar1 == '\0') break;
      unaff_EDX = unaff_EDX + 1;
      *param_1 = cVar1;
      param_1 = param_1 + 1;
      unaff_ECX = unaff_ECX + -1;
    } while (unaff_ECX != 0);
    for (; unaff_ECX != 0; unaff_ECX = unaff_ECX + -1) {
      *param_1 = '0';
      param_1 = param_1 + 1;
    }
  }
  return param_1;
}


// ================================================================================================
// sub_b0398 @ 0xb0398 [__watcall]
// ================================================================================================

void __watcall sub_b0398(char *param_1,size_t unaff_EDX,size_t unaff_EBX)

{
  char cVar1;
  char cVar2;
  char *pcVar3;
  char *pcVar4;
  size_t sVar5;
  
  if (unaff_EDX != unaff_EBX) {
    cVar1 = param_1[1];
    pcVar4 = param_1 + unaff_EBX;
    pcVar3 = param_1 + unaff_EDX;
    do {
      sVar5 = unaff_EBX;
      pcVar3 = pcVar3 + -1;
      pcVar4 = pcVar4 + -1;
      *pcVar4 = *pcVar3;
      unaff_EBX = sVar5 - 1;
    } while (pcVar3 != param_1);
    cVar2 = *param_1;
    if (cVar2 == '.') {
      unaff_EBX = sVar5 - 2;
      param_1[unaff_EBX] = '0';
    }
    else if (((cVar2 == '+') || (cVar2 == '-')) && (cVar1 == '.')) {
      param_1[unaff_EBX] = '0';
      unaff_EBX = sVar5 - 2;
      param_1[unaff_EBX] = *param_1;
    }
    memset(param_1,0x20,unaff_EBX);
  }
  return;
}


// ================================================================================================
// sub_b0403 @ 0xb0403 [__watcall]
// ================================================================================================

void __watcall
sub_b0403(char *param_1,undefined4 param_2,int param_3,char param_4,size_t param_5,int param_6,
         undefined4 param_7,char param_8,char param_9)

{
  char *pcVar1;
  char *pcVar2;
  int iVar3;
  double *extraout_EDX;
  double *pdVar4;
  undefined *extraout_EDX_00;
  undefined *puVar5;
  int iVar6;
  longdouble lVar7;
  undefined8 uVar8;
  char local_48 [20];
  double local_34;
  undefined8 local_2c;
  int local_24;
  int local_20;
  int local_1c;
  char *local_18;
  char local_14;
  char local_10;
  
  local_18 = param_1;
  local_14 = param_4;
  uVar8 = sub_b2220();
  pdVar4 = (double *)((ulonglong)uVar8 >> 0x20);
  if ((int)uVar8 == 0) {
    local_10 = param_9;
    if (param_9 == 'G') {
      local_34 = ABS(*pdVar4);
      if ((((ulonglong)local_34 & 0x7fffffff00000000) == 0) && (local_34._0_4_ == 0)) {
        param_6 = 0;
        local_10 = 'F';
      }
      else {
        local_34 = local_34 * 0.3010299956639812;
        sub_b22a4();
        lVar7 = (longdouble)sub_961d0();
        local_1c = (int)ROUND(lVar7);
        pdVar4 = extraout_EDX;
        if ((local_1c < -4) || (param_3 <= local_1c)) {
          local_10 = 'E';
        }
        else {
          if (0.0 <= local_34) {
            local_1c = local_1c + 1;
          }
          param_6 = 0;
          local_10 = 'F';
          param_3 = param_3 - local_1c;
        }
      }
    }
    if ((local_10 == 'E') && ((param_6 <= -param_3 || (param_3 + 2 <= param_6)))) goto LAB_000b04e0;
    if (param_9 == 'E') {
      if (param_6 < 1) {
        if (param_6 < 0) {
          param_3 = param_6 + param_3;
        }
      }
      else {
        param_3 = param_3 + 1;
      }
    }
    local_2c = *pdVar4;
    if (((((*(uint *)((int)pdVar4 + 4) & 0x7fffffff) != 0) || (*(int *)pdVar4 != 0)) &&
        (local_10 != 'E')) && (param_6 != 0)) {
      lVar7 = (longdouble)sub_b2321();
      local_2c = (double)lVar7;
    }
    sub_b2408(&local_20,local_18,local_2c._4_4_,param_3,(int)local_2c,local_2c._4_4_,param_3,
              &local_20,&local_24,local_10,local_48);
    pcVar1 = local_18;
    if (local_24 == 0) {
      puVar5 = extraout_EDX_00;
      if (local_14 != '\0') {
        *extraout_EDX_00 = 0x2b;
        puVar5 = extraout_EDX_00 + 1;
      }
    }
    else {
      *extraout_EDX_00 = 0x2d;
      puVar5 = extraout_EDX_00 + 1;
    }
    if (local_10 == 'E') {
      pcVar2 = (char *)sub_b0335(puVar5,local_48,param_6,param_3 - param_6);
      iVar6 = (int)pcVar2 - (int)local_18;
      pcVar1 = pcVar2;
      if ((param_8 != '\0') && (iVar6 < (int)param_5)) {
        pcVar1 = pcVar2 + 1;
        iVar6 = iVar6 + 1;
        *pcVar2 = param_8;
      }
      if ((((ulonglong)local_2c & 0x7fffffff00000000) != 0) || ((int)local_2c != 0)) {
        local_20 = local_20 - param_6;
      }
      iVar3 = sub_b028e(pcVar1,local_20,param_7,param_5 - iVar6);
      iVar6 = iVar6 + iVar3;
    }
    else if ((int)param_5 < (int)(puVar5 + ((local_20 + 1 + param_3) - (int)local_18))) {
      iVar6 = param_5 + 1;
    }
    else {
      iVar6 = sub_b0335(puVar5,local_48,local_20);
      iVar6 = iVar6 - (int)pcVar1;
    }
  }
  else {
    pcVar1 = local_18;
    for (iVar6 = 0; local_48[iVar6] != '\0'; iVar6 = iVar6 + 1) {
      if (iVar6 < (int)param_5) {
        *pcVar1 = local_48[iVar6];
      }
      pcVar1 = pcVar1 + 1;
    }
  }
  if (iVar6 <= (int)param_5) {
    sub_b0398(local_18,iVar6,param_5);
    return;
  }
LAB_000b04e0:
  memset(local_18,0x2a,param_5);
  return;
}


// ================================================================================================
// sub_b0627 @ 0xb0627 [__watcall]
// ================================================================================================

longdouble __watcall sub_b0627(byte *param_1,undefined4 *unaff_EDX)

{
  byte bVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  byte *pbVar6;
  byte *pbVar7;
  int iVar8;
  byte bVar9;
  int iVar10;
  int iVar11;
  longdouble lVar12;
  byte local_38 [20];
  undefined8 local_24;
  byte *local_1c;
  byte *local_18;
  
  for (pbVar6 = param_1; (bVar9 = *pbVar6, bVar9 == 0x20 || ((8 < bVar9 && (bVar9 < 0xe))));
      pbVar6 = pbVar6 + 1) {
  }
  bVar5 = false;
  pbVar7 = pbVar6 + 1;
  if ((bVar9 != 0x2b) && (pbVar7 = pbVar6, bVar9 == 0x2d)) {
    bVar5 = true;
    pbVar7 = pbVar6 + 1;
  }
  bVar2 = false;
  bVar4 = false;
  bVar9 = 0x30;
  iVar8 = 0;
  iVar11 = 0;
  local_18 = param_1;
  while( true ) {
    while( true ) {
      bVar3 = false;
      bVar1 = *pbVar7;
      pbVar6 = pbVar7 + 1;
      if (bVar1 != 0x2e) break;
      if (bVar4) goto LAB_000b069a;
      bVar4 = true;
      pbVar7 = pbVar6;
    }
    if ((bVar1 < 0x30) || (0x39 < bVar1)) break;
    if (bVar4) {
      iVar11 = iVar11 + 1;
    }
    bVar9 = bVar9 | bVar1;
    if (bVar9 != 0x30) {
      if (iVar8 < 0x11) {
        local_38[iVar8] = bVar1;
      }
      iVar8 = iVar8 + 1;
    }
    bVar2 = true;
    pbVar7 = pbVar6;
  }
LAB_000b069a:
  iVar10 = 0;
  if ((bVar2) &&
     ((((bVar1 == 0x65 || (bVar1 == 0x45)) || (bVar1 == 100)) || (local_18 = pbVar7, bVar1 == 0x44))
     )) {
    local_18 = pbVar7 + 2;
    if ((*pbVar6 != 0x2b) && (local_18 = pbVar6, *pbVar6 == 0x2d)) {
      bVar3 = true;
      local_18 = pbVar7 + 2;
    }
    bVar2 = false;
    for (; (bVar9 = *local_18, 0x2f < bVar9 && (bVar9 < 0x3a)); local_18 = local_18 + 1) {
      if (iVar10 < 1000) {
        iVar10 = iVar10 * 10 + (uint)bVar9 + -0x30;
      }
      bVar2 = true;
    }
    if (bVar3) {
      iVar10 = -iVar10;
    }
    local_1c = pbVar7;
    if (!bVar2) {
      local_18 = pbVar7;
    }
  }
  iVar10 = iVar10 - iVar11;
  if (0x11 < iVar8) {
    iVar10 = iVar10 + iVar8 + -0x11;
    iVar8 = 0x11;
  }
  for (; (0 < iVar8 && ((&stack0xffffffc7)[iVar8] == '0')); iVar8 = iVar8 + -1) {
    iVar10 = iVar10 + 1;
  }
  if (iVar8 == 0) {
    local_24 = 0.0;
  }
  else {
    local_38[iVar8] = 0;
    sub_b267e(local_38,&local_24);
    if (iVar10 < 0x135) {
      if (iVar10 < -0x145) {
        sub_98796();
        local_24 = 0.0;
      }
      else {
        if (iVar10 != 0) {
          lVar12 = (longdouble)sub_b2321();
          local_24 = (double)lVar12;
        }
        if (bVar5) {
          local_24 = -local_24;
        }
      }
    }
    else {
      sub_98796();
      if (bVar5) {
        local_24 = -(double)CONCAT44(dword_c4ca4,qword_c4ca0);
      }
      else {
        local_24 = (double)CONCAT44(dword_c4ca4,qword_c4ca0);
      }
    }
  }
  if (unaff_EDX != (undefined4 *)0x0) {
    *unaff_EDX = local_18;
  }
  return (longdouble)local_24;
}


// ================================================================================================
// sub_b07d0 @ 0xb07d0 [__watcall]
// ================================================================================================

void __watcall sub_b07d0(int param_1,uint unaff_EDX)

{
  ushort uVar1;
  byte bVar2;
  short sVar3;
  
  param_1 = param_1 * 0x11;
  *(short *)(&DAT_000f7987 + param_1) = (short)unaff_EDX;
  bVar2 = (byte)(unaff_EDX & 0xffffff03);
  sVar3 = CONCAT11((byte)((unaff_EDX & 0xffffff03) >> 8) ^ (byte)(unaff_EDX >> 8),bVar2);
  if ((int)unaff_EDX < 4) {
    *(undefined2 *)(&DAT_000f7981 + param_1) = 10;
    *(undefined2 *)(&DAT_000f7983 + param_1) = 0xb;
    *(undefined2 *)(&DAT_000f7985 + param_1) = 0xc;
    *(short *)(&DAT_000f797d + param_1) = sVar3 * 2;
    uVar1 = *(ushort *)(&DAT_000f797d + param_1) | 1;
  }
  else {
    *(undefined2 *)(&DAT_000f7981 + param_1) = 0xd4;
    *(undefined2 *)(&DAT_000f7983 + param_1) = 0xd6;
    *(undefined2 *)(&DAT_000f7985 + param_1) = 0xd8;
    uVar1 = sVar3 << 2;
    *(ushort *)(&DAT_000f797d + param_1) = uVar1 | 0xc0;
    uVar1 = uVar1 | 0xc2;
  }
  *(ushort *)(&DAT_000f797f + param_1) = uVar1;
  (&DAT_000f7979)[param_1] = bVar2;
  (&unk_f7978)[param_1] = bVar2 | 4;
  (&DAT_000f797a)[param_1] = (&unk_d86c8)[unaff_EDX * 2];
  return;
}


// ================================================================================================
// sub_b085c @ 0xb085c [__watcall]
// ================================================================================================

void __watcall sub_b085c(int param_1,int unaff_EDX,ushort unaff_BX,ushort unaff_CX,ushort param_5)

{
  undefined2 uVar1;
  byte in_AF;
  byte in_TF;
  byte in_IF;
  byte in_NT;
  undefined local_18;
  undefined local_14;
  char local_10;
  byte local_c;
  
  param_1 = param_1 * 0x11;
  uVar1 = *(undefined2 *)(&DAT_000f7987 + param_1);
  if (*(ushort *)(&DAT_000f7987 + param_1) < 4) {
    local_10 = (char)unaff_EDX + -1;
    local_18 = (undefined)((uint)(unaff_EDX + -1) >> 8);
    local_14 = (undefined)param_5;
    local_c = (byte)(param_5 >> 8);
  }
  else {
    local_10 = (char)(unaff_EDX - 2U >> 1);
    local_18 = (undefined)(unaff_EDX - 2U >> 9);
    local_14 = (undefined)((int)(uint)param_5 >> 1);
    local_c = (byte)((int)(uint)param_5 >> 9);
    if ((unaff_CX & 1) != 0) {
      local_c = local_c | 0x80;
    }
  }
  sub_aa200(*(undefined2 *)(&DAT_000f7981 + param_1),(&unk_f7978)[param_1],&unk_f7978 + param_1,
            unaff_CX,(ushort)(in_NT & 1) * 0x4000 | (ushort)(in_IF & 1) * 0x200 |
                     (ushort)(in_TF & 1) * 0x100 | 0x40 | (ushort)(in_AF & 1) * 0x10 | 4);
  sub_aa200(*(undefined2 *)(&DAT_000f7983 + param_1),unaff_BX | (byte)uVar1 & 3);
  sub_aa200(*(undefined2 *)(&DAT_000f7985 + param_1),0);
  sub_aa200(*(undefined2 *)(&DAT_000f797d + param_1),local_14);
  sub_aa200(*(undefined2 *)(&DAT_000f797d + param_1),local_c);
  sub_aa200((&DAT_000f797a)[param_1],unaff_CX);
  sub_aa200(*(undefined2 *)(&DAT_000f7985 + param_1),0);
  sub_aa200(*(undefined2 *)(&DAT_000f797f + param_1),local_10);
  sub_aa200(*(undefined2 *)(&DAT_000f797f + param_1),local_18);
  sub_aa200(*(undefined2 *)(&DAT_000f7981 + param_1),(&DAT_000f7979)[param_1]);
  return;
}


// ================================================================================================
// sub_b097c @ 0xb097c [__watcall]
// ================================================================================================

void __watcall sub_b097c(int param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  sub_aa200(*(undefined2 *)(&DAT_000f7981 + param_1 * 0x11),(&unk_f7978)[param_1 * 0x11],unaff_EBX,
            unaff_ECX,unaff_EDX);
  return;
}


// ================================================================================================
// sub_b09a4 @ 0xb09a4 [__watcall]
// ================================================================================================

undefined8 __watcall
sub_b09a4(int param_1,undefined4 unaff_EDX,undefined4 param_3,undefined4 unaff_ECX)

{
  uint uVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined *puVar4;
  byte in_AF;
  byte in_TF;
  byte in_IF;
  byte in_NT;
  ulonglong uVar5;
  
  uVar1 = param_1 * 0x11;
  puVar4 = &unk_f7978 + uVar1;
  sub_aa200(*(undefined2 *)(&DAT_000f7985 + uVar1),0,puVar4,unaff_ECX,
            (ushort)(in_NT & 1) * 0x4000 | (ushort)SCARRY4(uVar1,0xf7978) * 0x800 |
            (ushort)(in_IF & 1) * 0x200 | (ushort)(in_TF & 1) * 0x100 |
            (ushort)((int)puVar4 < 0) * 0x80 | (ushort)(puVar4 == (undefined *)0x0) * 0x40 |
            (ushort)(in_AF & 1) * 0x10 | (ushort)((POPCOUNT((uint)puVar4 & 0xff) & 1U) == 0) * 4 |
            (ushort)(0xfff08687 < uVar1));
  uVar2 = sub_b128c(*(undefined2 *)(&DAT_000f797f + uVar1));
  uVar5 = sub_b128c(*(undefined2 *)(&DAT_000f797f + uVar1),uVar2);
  uVar3 = (int)(uVar5 & 0xff000000ff) * 0x100 + (int)((uVar5 & 0xff000000ff) >> 0x20) + 1U & 0xffff;
  if (3 < *(ushort *)(&DAT_000f7987 + uVar1)) {
    uVar3 = uVar3 * 2;
  }
  return CONCAT44(unaff_EDX,uVar3);
}


// ================================================================================================
// sub_b0a14 @ 0xb0a14 [__watcall]
// ================================================================================================

undefined4 __watcall sub_b0a14(undefined4 param_1,undefined4 unaff_EDX,undefined2 unaff_BX)

{
  undefined2 in_DS;
  undefined4 local_10;
  
  word_f799c = read_bytes(param_1,unaff_BX,unaff_EDX,in_DS,&local_10);
  return local_10;
}


// ================================================================================================
// sub_b0a40 @ 0xb0a40 [__watcall]
// ================================================================================================

int __watcall sub_b0a40(int param_1)

{
  int iVar1;
  
  iVar1 = close(param_1);
  word_f799c = (short)iVar1;
  if ((short)iVar1 != 0) {
    iVar1 = 0x10;
  }
  return iVar1;
}


// ================================================================================================
// sub_b0a5c @ 0xb0a5c [__watcall]
// ================================================================================================

undefined4 __watcall sub_b0a5c(int param_1,__off_t unaff_EDX,int unaff_EBX)

{
  __off_t _Var1;
  
  _Var1 = lseek(param_1,unaff_EDX,unaff_EBX);
  if (_Var1 < 0) {
    return 0x10;
  }
  return 0;
}


// ================================================================================================
// sub_b0a78 @ 0xb0a78 [__watcall]
// ================================================================================================

undefined8 __watcall sub_b0a78(char *param_1,undefined4 unaff_EDX)

{
  int iVar1;
  int local_10;
  
  iVar1 = open(param_1,0,&local_10);
  word_f799c = (short)iVar1;
  if (word_f799c != 0) {
    local_10 = -(int)word_f799c;
  }
  return CONCAT44(unaff_EDX,local_10);
}


// ================================================================================================
// sub_b0aa4 @ 0xb0aa4 [__watcall]
// ================================================================================================

void __watcall sub_b0aa4(void)

{
  sub_98ac8();
  return;
}


// ================================================================================================
// sub_b0ab0 @ 0xb0ab0 [__watcall]
// ================================================================================================

void __watcall sub_b0ab0(void)

{
  sub_98af3();
  return;
}


// ================================================================================================
// sub_b0abc @ 0xb0abc [__watcall]
// ================================================================================================

void __watcall sub_b0abc(int param_1,undefined4 param_2,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  undefined2 uVar1;
  undefined4 uVar2;
  byte bVar3;
  uint uVar4;
  byte in_AF;
  byte in_TF;
  byte in_IF;
  byte in_NT;
  undefined8 uVar5;
  ulonglong uVar6;
  ushort uVar7;
  
  uVar7 = (ushort)(in_NT & 1) * 0x4000 | (ushort)(in_IF & 1) * 0x200 | (ushort)(in_TF & 1) * 0x100 |
          0x40 | (ushort)(in_AF & 1) * 0x10 | 4;
  uVar1 = *(undefined2 *)(&unk_d86da + param_1 * 8);
  uVar5 = sub_b0ab0(uVar1);
  *(short *)(&unk_d86e0 + param_1 * 2) = (short)((ulonglong)uVar5 >> 0x20);
  *(int *)(&unk_d86dc + param_1 * 8) = (int)uVar5;
  sub_b0aa4(uVar1,(int)((ulonglong)uVar5 >> 0x20),unaff_EBX,unaff_ECX,uVar7);
  bVar3 = ~('\x01' << ((byte)param_1 & 7));
  if (param_1 < 8) {
    uVar6 = sub_b128c(0x21,bVar3);
    uVar4 = (uint)((uVar6 & 0xff000000ff) >> 0x20) & (uint)(uVar6 & 0xff000000ff);
    uVar2 = 0x21;
  }
  else {
    uVar6 = sub_b128c(0xa1,bVar3);
    uVar4 = (uint)((uVar6 & 0xff000000ff) >> 0x20) & (uint)(uVar6 & 0xff000000ff);
    uVar2 = 0xa1;
  }
  sub_aa200(uVar2,uVar4);
  return;
}


// ================================================================================================
// sub_b0b5c @ 0xb0b5c [__watcall]
// ================================================================================================

void __watcall sub_b0b5c(int param_1,undefined4 param_2,undefined4 param_3,undefined4 unaff_ECX)

{
  undefined4 uVar1;
  char cVar2;
  uint uVar3;
  byte in_CF;
  byte in_PF;
  byte in_AF;
  byte in_ZF;
  byte in_SF;
  byte in_TF;
  byte in_IF;
  byte in_OF;
  byte in_NT;
  ushort uVar4;
  ulonglong uVar5;
  
  uVar4 = (ushort)(in_NT & 1) * 0x4000 | (ushort)(in_OF & 1) * 0x800 | (ushort)(in_IF & 1) * 0x200 |
          (ushort)(in_TF & 1) * 0x100 | (ushort)(in_SF & 1) * 0x80 | (ushort)(in_ZF & 1) * 0x40 |
          (ushort)(in_AF & 1) * 0x10 | (ushort)(in_PF & 1) * 4 | (ushort)(in_CF & 1);
  if (param_1 != 2) {
    uVar3 = CONCAT31((int3)((uint)unaff_ECX >> 8),(char)param_1) & 0xffffff07;
    cVar2 = '\x01' << (sbyte)uVar3;
    if (param_1 < 8) {
      uVar5 = sub_b128c(0x21,cVar2,param_1,uVar3,uVar4);
      uVar3 = (uint)((uVar5 & 0xff000000ff) >> 0x20) | (uint)(uVar5 & 0xff000000ff);
      uVar1 = 0x21;
    }
    else {
      uVar5 = sub_b128c(0xa1,cVar2,param_1,uVar3,uVar4);
      uVar3 = (uint)((uVar5 & 0xff000000ff) >> 0x20) | (uint)(uVar5 & 0xff000000ff);
      uVar1 = 0xa1;
    }
    sub_aa200(uVar1,uVar3);
  }
  sub_b0aa4(*(undefined2 *)(&unk_d86da + param_1 * 8));
  return;
}


// ================================================================================================
// sub_b0be4 @ 0xb0be4 [__watcall]
// ================================================================================================

void __watcall
sub_b0be4(ushort param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  if (7 < param_1) {
    sub_aa200(0xa0,0x20,unaff_EBX,unaff_ECX,unaff_EDX);
  }
  sub_aa200(0x20,0x20,unaff_EBX,unaff_ECX,unaff_EDX);
  return;
}


// ================================================================================================
// sub_b0c10 @ 0xb0c10 [__watcall]
// ================================================================================================

undefined8 __watcall sub_b0c10(int param_1,undefined4 unaff_EDX)

{
  uint uVar1;
  
  if ((&unk_d877a)[param_1] == '\0') {
    uVar1 = CONCAT31((int3)((uint)param_1 >> 8),3);
  }
  else {
    uVar1 = sub_b07d0(0,param_1);
    uVar1 = uVar1 & 0xffffff00;
  }
  return CONCAT44(unaff_EDX,uVar1);
}


// ================================================================================================
// sub_b0c34 @ 0xb0c34 [__watcall]
// ================================================================================================

undefined8 __watcall sub_b0c34(int param_1,undefined4 unaff_EDX)

{
  uint uVar1;
  
  if ((&unk_d877a)[param_1] == '\0') {
    uVar1 = CONCAT31((int3)((uint)param_1 >> 8),3);
  }
  else {
    uVar1 = sub_b07d0(1,param_1);
    uVar1 = uVar1 & 0xffffff00;
  }
  return CONCAT44(unaff_EDX,uVar1);
}


// ================================================================================================
// sub_b0c5c @ 0xb0c5c [__watcall]
// ================================================================================================

char __watcall sub_b0c5c(void)

{
  char cVar1;
  int iVar2;
  
  byte_d8ae4 = 1;
  cVar1 = sub_b0c10(byte_f79a4);
  if (cVar1 != '\0') {
    return cVar1;
  }
  cVar1 = sub_b0c34(byte_f79a6);
  if (cVar1 != '\0') {
    return cVar1;
  }
  iVar2 = sub_b14ac(sub_b0e7c);
  if (iVar2 != 0) {
    return '\b';
  }
  dword_d8784 = iVar2;
  return '\0';
}


// ================================================================================================
// sub_b0cb8 @ 0xb0cb8 [__watcall]
// ================================================================================================

void __watcall
sub_b0cb8(undefined4 param_1,undefined4 unaff_EDX,uint unaff_EBX,byte unaff_CL,ushort param_5)

{
  byte extraout_DL;
  byte extraout_DL_00;
  
  word_f79b8 = (undefined2)param_1;
  word_f79ba = (undefined2)((uint)param_1 >> 0x10);
  word_f79c9 = param_5;
  dword_f79c0 = 0;
  dword_f79c4 = 0;
  dword_f79bc = unaff_EDX;
  if ((param_5 & 1) == 0) {
    if (3 < byte_f79a6) {
      sub_b2720(unaff_EBX,unaff_CL | 4);
      unaff_CL = extraout_DL_00;
    }
  }
  else {
    if (((unaff_CL & 4) == 0) && (3 < byte_f79a4)) {
      unaff_EBX = sub_b2720(unaff_EBX,unaff_CL | 4);
      unaff_CL = extraout_DL;
    }
    sub_aa200(word_d8772,0x42);
    sub_b19c7(word_d8774,unaff_EBX >> 4 & 0xffff);
  }
  byte_f79c8 = unaff_CL | 0x21;
  sub_b0e7c(param_5);
  return;
}


// ================================================================================================
// sub_b0d6c @ 0xb0d6c [__watcall]
// ================================================================================================

undefined4 __watcall
sub_b0d6c(int *param_1,uint unaff_EDX,uint unaff_EBX,undefined unaff_CL,ushort param_5)

{
  ushort uVar1;
  int iVar2;
  byte in_AF;
  byte in_TF;
  byte in_IF;
  byte in_NT;
  ushort uVar3;
  int *local_20;
  uint local_1c;
  uint local_18;
  
  uVar3 = (ushort)(in_NT & 1) * 0x4000 | (ushort)SBORROW4((int)&stack0xfffffff4,0x14) * 0x800 |
          (ushort)(in_IF & 1) * 0x200 | (ushort)(in_TF & 1) * 0x100 |
          (ushort)((int)&local_20 < 0) * 0x80 |
          (ushort)(&stack0x00000000 == (undefined *)0x20) * 0x40 | (ushort)(in_AF & 1) * 0x10 |
          (ushort)((POPCOUNT((uint)&local_20 & 0xff) & 1U) == 0) * 4 |
          (ushort)(&stack0xfffffff4 < (undefined *)0x14);
  local_20 = param_1;
  sub_b122f();
  if (dword_d8784 != 0) {
    sub_b1256();
    return 7;
  }
  dword_d8784 = 1;
  local_18 = local_20[1];
  iVar2 = *local_20;
  if ((param_5 & 1) == 0) {
LAB_000b0e50:
    sub_b0cb8(local_18,unaff_EDX,unaff_EBX,unaff_CL,param_5);
  }
  else {
    if (((byte_f79a4 < 4) || ((local_18 & 1) == 0)) || ((unaff_EBX & 1) != 0)) {
      uVar1 = (ushort)((byte)unaff_EBX & 0x1f);
      if (uVar1 != 0) {
        local_1c = 0x20 - uVar1;
        if (unaff_EDX < (local_1c & 0xffff)) {
          local_1c = unaff_EDX;
        }
        local_1c = local_1c & 0xffff;
        sub_b1f9c(iVar2,unaff_EBX,local_1c,unaff_CL,uVar3);
        unaff_EDX = unaff_EDX - local_1c;
        local_18 = local_18 + local_1c;
        iVar2 = iVar2 + local_1c;
      }
      if (0x1f < unaff_EDX) goto LAB_000b0e50;
    }
    if (unaff_EDX != 0) {
      sub_b1f9c(iVar2,unaff_EBX,unaff_EDX,unaff_CL,uVar3);
    }
    word_f799e = word_f799e | 4;
  }
  sub_b1256();
  return 0;
}


// ================================================================================================
// sub_b0e7c @ 0xb0e7c [__watcall]
// ================================================================================================

longlong __watcall sub_b0e7c(uint param_1,uint unaff_EDX)

{
  uint uVar1;
  short sVar2;
  undefined4 uVar3;
  uint uVar4;
  undefined4 uVar5;
  uint uVar6;
  byte in_AF;
  byte in_TF;
  byte in_IF;
  byte in_NT;
  ushort uVar7;
  
  sVar2 = word_f79ba;
  if (dword_d8784 == 0) {
    uVar3 = 0;
  }
  else {
    dword_f79c4 = dword_f79c4 + dword_f79c0;
    if (dword_f79bc == 0) {
      dword_d8784 = dword_f79bc;
      return (ulonglong)unaff_EDX << 0x20;
    }
    uVar4 = 0x10000 - word_f79b8;
    uVar1 = uVar4 - dword_f79bc;
    uVar6 = uVar4;
    if (uVar4 >= dword_f79bc && uVar1 != 0) {
      uVar6 = dword_f79bc;
    }
    uVar7 = (ushort)(in_NT & 1) * 0x4000 | (ushort)SBORROW4(uVar4,dword_f79bc) * 0x800 |
            (ushort)(in_IF & 1) * 0x200 | (ushort)(in_TF & 1) * 0x100 |
            (ushort)((int)uVar1 < 0) * 0x80 | (ushort)(uVar1 == 0) * 0x40 |
            (ushort)(in_AF & 1) * 0x10 | (ushort)((POPCOUNT(uVar1 & 0xff) & 1U) == 0) * 4 |
            (ushort)(uVar4 < dword_f79bc);
    dword_f79c0 = uVar6;
    if ((param_1 & 1) == 0) {
      uVar3 = 0x44;
      sub_b085c(1,uVar6,0x44,word_f79ba,word_f79b8);
      uVar5 = 0x49;
    }
    else {
      if ((byte_f79c8 & 2) == 0) {
        uVar3 = 0x48;
      }
      else {
        uVar3 = 0x44;
      }
      sub_b085c(0,uVar6,uVar3,word_f79ba,word_f79b8);
      uVar5 = 0x41;
    }
    sub_aa200(word_d8772,uVar5,uVar3,sVar2,uVar7);
    sub_aa200(word_d8776,byte_f79c8);
    sub_b13a1();
    dword_f79bc = dword_f79bc - uVar6;
    word_f79b8 = word_f79b8 + (short)uVar6;
    word_f79ba = word_f79ba + 1;
    uVar3 = 1;
  }
  return CONCAT44(unaff_EDX,uVar3);
}


// ================================================================================================
// sub_b0fa8 @ 0xb0fa8 [__watcall]
// ================================================================================================

undefined8 __watcall sub_b0fa8(undefined4 param_1,undefined4 unaff_EDX)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  int extraout_EDX;
  
  iVar3 = 120000;
  while ((dword_d8784 != 0 && (iVar3 = iVar3 + -1, iVar3 != 0))) {
    uVar1 = sub_b128c(word_d8762);
    if (((uVar1 & 0x80) == 0) && ((word_f799e & 4) == 0)) goto LAB_000b0fe6;
    while( true ) {
      sub_b16bc();
LAB_000b0fe6:
      if ((word_f799e & 2) == 0) break;
      word_f799e = word_f799e & 0xfffd;
    }
    sub_b13a1();
    iVar3 = extraout_EDX;
  }
  if ((dword_d8784 == 0) || (iVar3 != 0)) {
    uVar2 = 0;
  }
  else {
    uVar2 = 9;
  }
  return CONCAT44(unaff_EDX,uVar2);
}


// ================================================================================================
// sub_b1024 @ 0xb1024 [__watcall]
// ================================================================================================

bool __watcall sub_b1024(void)

{
  return dword_d8784 == 0;
}


// ================================================================================================
// sub_b103c @ 0xb103c [__watcall]
// ================================================================================================

void __watcall sub_b103c(void)

{
  undefined4 unaff_ECX;
  byte in_CF;
  byte in_PF;
  byte in_AF;
  byte in_ZF;
  byte in_SF;
  byte in_TF;
  byte in_IF;
  byte in_OF;
  byte in_NT;
  ushort uVar1;
  
  uVar1 = (ushort)(in_NT & 1) * 0x4000 | (ushort)(in_OF & 1) * 0x800 | (ushort)(in_IF & 1) * 0x200 |
          (ushort)(in_TF & 1) * 0x100 | (ushort)(in_SF & 1) * 0x80 | (ushort)(in_ZF & 1) * 0x40 |
          (ushort)(in_AF & 1) * 0x10 | (ushort)(in_PF & 1) * 4 | (ushort)(in_CF & 1);
  if (dword_d8784 != 0) {
    dword_d8784 = 0;
    sub_b097c(0);
    sub_b097c(1);
    byte_f79c8 = byte_f79c8 & 0xde;
    sub_aa200(word_d8772,0x41,0,unaff_ECX,uVar1);
    sub_aa200(word_d8776,byte_f79c8);
    sub_aa200(word_d8772,0x49);
    sub_aa200(word_d8776,byte_f79c8);
  }
  return;
}


// ================================================================================================
// sub_b10d0 @ 0xb10d0 [__watcall]
// ================================================================================================

longlong __watcall sub_b10d0(int *param_1,uint unaff_EDX)

{
  ulonglong uVar1;
  uint uVar2;
  uint uVar3;
  
  sub_b122f();
  uVar3 = param_1[5];
  uVar2 = uVar3;
  if ((*(byte *)(param_1 + 0x12) & 1) != 0) {
    uVar2 = sub_b2720(uVar3);
  }
  *(ushort *)(param_1 + 8) = (ushort)(uVar2 >> 7) & 0x1fff;
  uVar3 = uVar3 + *param_1;
  *(short *)((int)param_1 + 0x1e) = (short)((uVar2 & 0x7f) << 9);
  if ((*(byte *)(param_1 + 0x12) & 1) != 0) {
    uVar3 = sub_b2720(uVar3);
  }
  *(ushort *)((int)param_1 + 0x22) = (ushort)((byte)uVar3 & 0x7f) << 9;
  *(ushort *)(param_1 + 9) = (ushort)(uVar3 >> 7) & 0x1fff;
  *(ushort *)((int)param_1 + 0x22) =
       *(ushort *)((int)param_1 + 0x22) | (ushort)((*(byte *)(param_1 + 0xd) & 0xffffff0f) << 5);
  uVar3 = param_1[5] + param_1[1];
  if ((*(byte *)(param_1 + 0x12) & 1) != 0) {
    uVar3 = sub_b2720();
  }
  *(ushort *)((int)param_1 + 0x26) = (ushort)((byte)uVar3 & 0x7f) << 9;
  *(ushort *)(param_1 + 10) = (ushort)(uVar3 >> 7) & 0x1fff;
  *(ushort *)((int)param_1 + 0x26) =
       *(ushort *)((int)param_1 + 0x26) | (*(byte *)(param_1 + 0xd) & 0xfff0) * 2;
  if ((*(byte *)(param_1 + 0x12) & 1) == 0) {
    uVar3 = (param_1[5] + param_1[0xc]) - 1;
  }
  else {
    uVar3 = sub_b2720(param_1[5] + param_1[0xc] + -2);
  }
  *(ushort *)((int)param_1 + 0x2a) = (ushort)((byte)uVar3 & 0x7f) << 9;
  *(ushort *)(param_1 + 0xb) = (ushort)(uVar3 >> 7) & 0x1fff;
  uVar3 = (uint)*(ushort *)(&unk_d8acc + (uint)word_f79a0 * 2) * 0x200 +
          ((int)(uint)*(ushort *)((int)param_1 + 0x1a) >> 1);
  uVar1 = (ulonglong)uVar3 / (ulonglong)(uint)*(ushort *)((int)param_1 + 0x1a);
  *(short *)((int)param_1 + 0x2e) = (short)uVar1;
  sub_b1256((int)uVar1,uVar3 % (uint)*(ushort *)((int)param_1 + 0x1a));
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// sub_b121c @ 0xb121c [__watcall]
// ================================================================================================

void __watcall sub_b121c(void)

{
  word_d8788 = 0;
  word_f79a2 = 0;
  return;
}


// ================================================================================================
// sub_b122f @ 0xb122f [__watcall]
// ================================================================================================

void __watcall sub_b122f(void)

{
  word_f79a2 = word_f79a2 + 1;
  return;
}


// ================================================================================================
// sub_b1237 @ 0xb1237 [__watcall]
// ================================================================================================

bool __watcall sub_b1237(void)

{
  bool bVar1;
  
  bVar1 = word_f79a2 == 0;
  if (bVar1) {
    sub_b122f();
  }
  return bVar1;
}


// ================================================================================================
// sub_b1256 @ 0xb1256 [__watcall]
// ================================================================================================

void __watcall sub_b1256(void)

{
  word_f79a2 = word_f79a2 + -1;
  if (word_f79a2 == 0) {
    while (((byte)word_f799e & 6) != 0) {
      word_f799e._0_1_ = (byte)word_f799e & 0xfd;
      sub_b16bc();
    }
  }
  return;
}


// ================================================================================================
// sub_b128c @ 0xb128c [__watcall]
// ================================================================================================

undefined8 __watcall sub_b128c(undefined2 param_1,undefined4 unaff_EDX)

{
  byte bVar1;
  
  bVar1 = in(param_1);
  return CONCAT44(unaff_EDX,(uint)bVar1);
}


// ================================================================================================
// sub_b12a0 @ 0xb12a0 [__watcall]
// ================================================================================================

undefined8 __watcall sub_b12a0(undefined4 param_1,undefined4 unaff_EDX)

{
  ushort extraout_var;
  int iVar1;
  
  sub_902a0();
  sub_b0be4(byte_f79a8);
  if (word_f79a2 == 0) {
    iVar1 = (uint)extraout_var << 0x10;
    word_f79a2 = 1;
    do {
      word_f799e = word_f799e & 0xfffd;
      iVar1 = sub_b16bc(iVar1);
    } while ((word_f799e & 2) != 0);
    word_f79a2 = word_f79a2 + -1;
  }
  else {
    word_f799e = word_f799e | 2;
  }
  return CONCAT44(unaff_EDX,param_1);
}


// ================================================================================================
// sub_b131c @ 0xb131c [__watcall]
// ================================================================================================

undefined8 __watcall sub_b131c(undefined4 param_1,undefined4 unaff_EDX)

{
  undefined4 uVar1;
  
  sub_902a0();
  sub_b0be4(byte_f79a7);
  if (dword_d87a0 == 0) {
    dword_d87a0 = 1;
    uVar1 = 0;
    do {
      word_f799e = word_f799e & 0xfff7;
      uVar1 = sub_b15f8(uVar1);
    } while ((word_f799e & 8) != 0);
    dword_d87a0 = dword_d87a0 + -1;
  }
  else {
    word_f799e = word_f799e | 8;
  }
  return CONCAT44(unaff_EDX,param_1);
}


// ================================================================================================
// sub_b13a1 @ 0xb13a1 [__watcall]
// ================================================================================================

undefined __watcall sub_b13a1(void)

{
  undefined uVar1;
  int iVar2;
  char in_ZF;
  
  iVar2 = 10;
  do {
    uVar1 = in(word_d8778);
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0 && in_ZF == '\0');
  return uVar1;
}


// ================================================================================================
// sub_b13b5 @ 0xb13b5 [__watcall]
// ================================================================================================

undefined4 __watcall sub_b13b5(uint param_1)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  short *psVar4;
  
  if ((param_1 < 0x210) || (0x260 < param_1)) {
    uVar1 = 1;
  }
  else {
    uVar3 = (uint)word_d8760;
    if (param_1 - uVar3 != 0) {
      psVar4 = (short *)&word_d8760;
      iVar2 = 0xd;
      do {
        *psVar4 = *psVar4 + (short)(param_1 - uVar3);
        psVar4 = psVar4 + 1;
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
    }
    uVar1 = 0;
  }
  return uVar1;
}


// ================================================================================================
// sub_b1400 @ 0xb1400 [__watcall]
// ================================================================================================

void __watcall sub_b1400(void)

{
  dword_d87ac = 0;
  dword_d87b0 = 0;
  dword_d87b4 = 0;
  dword_d87b8 = 0;
  dword_d87bc = 0;
  dword_d87c0 = 0;
  dword_d87c4 = 0;
  dword_d87c8 = 0;
  dword_d87cc = 0;
  dword_d87d0 = 0;
  dword_d87d4 = 0;
  dword_f79d8 = 0;
  dword_d87a8 = 0;
  return;
}


// ================================================================================================
// sub_b145c @ 0xb145c [__watcall]
// ================================================================================================

undefined4 __watcall sub_b145c(int *param_1,int unaff_EDX)

{
  if ((*param_1 != 0) && (unaff_EDX != 0)) {
    return 1;
  }
  *param_1 = unaff_EDX;
  return 0;
}


// ================================================================================================
// sub_b1484 @ 0xb1484 [__watcall]
// ================================================================================================

undefined4 __watcall sub_b1484(int *param_1,int unaff_EDX)

{
  if ((*param_1 != 0) && (unaff_EDX != 0)) {
    return 1;
  }
  *param_1 = unaff_EDX;
  return 0;
}


// ================================================================================================
// sub_b14ac @ 0xb14ac [__watcall]
// ================================================================================================

undefined8 __watcall sub_b14ac(undefined4 param_1,undefined4 unaff_EDX)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = sub_b145c(&dword_d87b0,param_1);
  if (iVar1 != 0) {
    iVar1 = sub_b145c(&dword_d87b4,param_1);
    if (iVar1 != 0) {
      uVar2 = 8;
      goto LAB_000b14dc;
    }
  }
  uVar2 = 0;
LAB_000b14dc:
  return CONCAT44(unaff_EDX,uVar2);
}


// ================================================================================================
// sub_b14e4 @ 0xb14e4 [__watcall]
// ================================================================================================

undefined8 __watcall sub_b14e4(undefined4 param_1,undefined4 unaff_EDX)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = sub_b145c(&dword_d87b8,param_1);
  if (iVar1 != 0) {
    iVar1 = sub_b145c(&dword_d87bc,param_1);
    if (iVar1 != 0) {
      uVar2 = 8;
      goto LAB_000b1514;
    }
  }
  uVar2 = 0;
LAB_000b1514:
  return CONCAT44(unaff_EDX,uVar2);
}


// ================================================================================================
// sub_b151c @ 0xb151c [__watcall]
// ================================================================================================

undefined8 __watcall sub_b151c(undefined4 param_1,undefined4 unaff_EDX)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = sub_b145c(&dword_d87c0,param_1);
  if (iVar1 != 0) {
    iVar1 = sub_b145c(&dword_d87c4,param_1);
    if (iVar1 != 0) {
      uVar2 = 8;
      goto LAB_000b154c;
    }
  }
  uVar2 = 0;
LAB_000b154c:
  return CONCAT44(unaff_EDX,uVar2);
}


// ================================================================================================
// sub_b1554 @ 0xb1554 [__watcall]
// ================================================================================================

int __watcall sub_b1554(int param_1)

{
  int iVar1;
  
  if (param_1 == 1) {
    iVar1 = sub_b1484(&dword_d87c8);
    if (iVar1 != 0) {
      return 8;
    }
  }
  else if (param_1 == 2) {
    iVar1 = sub_b1484(&dword_d87cc);
    if (iVar1 != 0) {
      return 8;
    }
  }
  else {
    iVar1 = 0xd;
  }
  return iVar1;
}


// ================================================================================================
// sub_b1598 @ 0xb1598 [__watcall]
// ================================================================================================

undefined8 __watcall sub_b1598(undefined4 param_1,undefined4 unaff_EDX)

{
  int iVar1;
  
  iVar1 = sub_b1484(&dword_d87d4,param_1);
  if (iVar1 != 0) {
    iVar1 = 8;
  }
  return CONCAT44(unaff_EDX,iVar1);
}


// ================================================================================================
// sub_b15b8 @ 0xb15b8 [__watcall]
// ================================================================================================

undefined8 __watcall sub_b15b8(undefined4 param_1,undefined4 unaff_EDX)

{
  int iVar1;
  
  iVar1 = sub_b1484(&dword_d87d0,param_1);
  if (iVar1 != 0) {
    iVar1 = 8;
  }
  return CONCAT44(unaff_EDX,iVar1);
}


// ================================================================================================
// sub_b15d8 @ 0xb15d8 [__watcall]
// ================================================================================================

undefined8 __watcall sub_b15d8(undefined4 param_1,undefined4 unaff_EDX)

{
  int iVar1;
  
  iVar1 = sub_b1484(&dword_d87ac,param_1);
  if (iVar1 != 0) {
    iVar1 = 8;
  }
  return CONCAT44(unaff_EDX,iVar1);
}


// ================================================================================================
// sub_b15f8 @ 0xb15f8 [__watcall]
// ================================================================================================

void __watcall
sub_b15f8(undefined4 param_1,undefined4 param_2,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  undefined4 extraout_EDX;
  undefined4 uVar1;
  byte in_AF;
  byte in_TF;
  byte in_IF;
  byte in_NT;
  ushort uVar2;
  ulonglong uVar3;
  uint local_18;
  
  uVar2 = (ushort)(in_NT & 1) * 0x4000 | (ushort)SBORROW4((int)&stack0xffffffec,4) * 0x800 |
          (ushort)(in_IF & 1) * 0x200 | (ushort)(in_TF & 1) * 0x100 |
          (ushort)((int)&local_18 < 0) * 0x80 |
          (ushort)(&stack0x00000000 == (undefined *)0x18) * 0x40 | (ushort)(in_AF & 1) * 0x10 |
          (ushort)((POPCOUNT((uint)&local_18 & 0xff) & 1U) == 0) * 4 |
          (ushort)(&stack0xffffffec < (undefined *)0x4);
  dword_d87a8 = dword_d87a8 + 1;
  local_18 = sub_b128c(word_d8762);
  if ((local_18 & 3) != 0) {
    uVar3 = sub_b128c(word_d876c,local_18,unaff_EBX,unaff_ECX,uVar2);
    uVar1 = (undefined4)(uVar3 >> 0x20);
    if (((uVar3 & 0x100000000) != 0) && (dword_d87d0 != (code *)0x0)) {
      (*dword_d87d0)();
      uVar1 = extraout_EDX;
    }
    if ((local_18 & 2) != 0) {
      sub_b128c(word_d876e,uVar1,(int)uVar3);
      if (dword_d87d4 != (code *)0x0) {
        (*dword_d87d4)();
      }
    }
  }
  dword_d87a8 = dword_d87a8 + -1;
  return;
}


// ================================================================================================
// sub_b1680 @ 0xb1680 [__watcall]
// ================================================================================================

undefined8 __watcall sub_b1680(undefined4 param_1,undefined4 unaff_EDX)

{
  uint uVar1;
  uint extraout_EDX;
  
  uVar1 = sub_b128c(word_d8762);
  if (byte_f79a7 != byte_f79a8) {
    uVar1 = uVar1 & 0xfffffffc;
  }
  if ((uVar1 & 3) != 0) {
    sub_b15f8();
    uVar1 = extraout_EDX;
  }
  return CONCAT44(unaff_EDX,uVar1);
}


// ================================================================================================
// sub_b16bc @ 0xb16bc [__watcall]
// ================================================================================================

undefined8 __watcall sub_b16bc(undefined4 param_1,undefined4 unaff_EDX)

{
  byte bVar1;
  uint uVar2;
  undefined2 uVar6;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  uint uVar7;
  uint extraout_ECX;
  uint extraout_ECX_00;
  uint uVar8;
  uint uVar9;
  byte in_CF;
  byte in_PF;
  byte in_AF;
  byte in_ZF;
  byte in_SF;
  byte in_TF;
  byte in_IF;
  byte in_OF;
  byte in_NT;
  ushort uVar10;
  ulonglong uVar11;
  
  uVar10 = (ushort)(in_NT & 1) * 0x4000 | (ushort)(in_OF & 1) * 0x800 | (ushort)(in_IF & 1) * 0x200
           | (ushort)(in_TF & 1) * 0x100 | (ushort)(in_SF & 1) * 0x80 | (ushort)(in_ZF & 1) * 0x40 |
           (ushort)(in_AF & 1) * 0x10 | (ushort)(in_PF & 1) * 4 | (ushort)(in_CF & 1);
  uVar3 = (uint)word_f79a2;
  word_f79a2 = word_f79a2 + 1;
  uVar9 = 0;
  uVar8 = 0;
  do {
    do {
      uVar2 = sub_b1680(uVar3);
      uVar6 = (undefined2)(uVar2 >> 0x10);
      if ((uVar2 == 0) && ((word_f799e & 4) == 0)) {
        uVar5 = CONCAT22(uVar6,word_f79a2);
        word_f79a2 = word_f79a2 + -1;
        return CONCAT44(unaff_EDX,uVar5);
      }
      if (((uVar2 & 0x80) != 0) || (uVar3 = CONCAT22(uVar6,word_f799e), (word_f799e & 4) != 0)) {
        sub_aa200(word_d8772,0x41);
        uVar3 = sub_b128c(word_d8776);
        if ((((uVar3 & 0x40) != 0) || ((word_f799e & 4) != 0)) &&
           (word_f799e = word_f799e & 0xfffb, dword_d87b0 != (code *)0x0)) {
          iVar4 = (*dword_d87b0)(uVar10);
          if ((iVar4 == 0) && (dword_d87b4 != (code *)0x0)) {
            (*dword_d87b4)();
          }
        }
        sub_aa200(word_d8772,0x49);
        uVar3 = sub_b128c(word_d8776);
        if (((uVar3 & 0x40) != 0) && (dword_d87b0 != (code *)0x0)) {
          uVar3 = (*dword_d87b0)();
          if ((uVar3 == 0) && (dword_d87b4 != (code *)0x0)) {
            uVar3 = (*dword_d87b4)();
          }
        }
      }
      if ((uVar2 & 4) != 0) {
        sub_aa200(word_d8772,0x45);
        sub_aa200(word_d8776,dword_f79d8 & 0xfffffffb);
        uVar3 = sub_aa200(word_d8776,dword_f79d8);
        if (dword_d87c8 != (code *)0x0) {
          uVar3 = (*dword_d87c8)();
          if (uVar3 != 0) {
            uVar3 = 0;
            dword_d87c8 = (code *)0x0;
          }
        }
      }
      if ((uVar2 & 8) != 0) {
        sub_aa200(word_d8772,0x45);
        sub_aa200(word_d8776,dword_f79d8 & 0xfffffff7);
        uVar3 = sub_aa200(word_d8776,dword_f79d8);
        if (dword_d87cc != (code *)0x0) {
          uVar3 = (*dword_d87cc)();
          if (uVar3 != 0) {
            dword_d87cc = (code *)0x0;
          }
        }
      }
    } while ((uVar2 & 0x60) == 0);
    while( true ) {
      sub_aa200(word_d8772,0x8f);
      uVar2 = sub_b128c(word_d8776);
      bVar1 = (byte)uVar2;
      uVar3 = uVar2 & 0xffffffc0;
      if ((char)uVar3 == -0x40) break;
      uVar7 = CONCAT31((int3)uVar2,bVar1) & 0xff1f;
      uVar11 = CONCAT44(uVar2,CONCAT31((int3)(uVar3 >> 8),bVar1)) & 0x1fffffff1f;
      uVar3 = 1 << (bVar1 & 0x1f);
      if ((uVar2 & 0x80) == 0) {
        if ((uVar9 & uVar3) == 0) {
          if (dword_d87b8 == (code *)0x0) {
LAB_000b18dc:
            if (dword_d87bc != (code *)0x0) {
              uVar11 = (*dword_d87bc)();
              uVar7 = extraout_ECX_00;
              if ((int)uVar11 != 0) goto LAB_000b18f1;
            }
          }
          else {
            uVar11 = (*dword_d87b8)();
            uVar7 = extraout_ECX;
            if ((int)uVar11 == 0) goto LAB_000b18dc;
LAB_000b18f1:
            uVar9 = uVar9 | uVar3;
          }
        }
        else {
          uVar11 = CONCAT44(uVar2,~uVar3) & 0x1fffffffff;
          uVar9 = uVar9 & ~uVar3;
        }
      }
      if ((uVar7 & 0x4000) == 0) {
        if ((uVar8 & uVar3) == 0) {
          if (dword_d87c0 == (code *)0x0) {
LAB_000b1917:
            if (dword_d87c4 != (code *)0x0) {
              uVar11 = (*dword_d87c4)();
              if ((int)uVar11 != 0) goto LAB_000b192c;
            }
          }
          else {
            uVar11 = (*dword_d87c0)();
            if ((int)uVar11 == 0) goto LAB_000b1917;
LAB_000b192c:
            uVar8 = uVar8 | uVar3;
          }
        }
        else {
          uVar8 = uVar8 & ~uVar3;
        }
      }
      sub_b1680((int)uVar11,(int)(uVar11 >> 0x20));
    }
  } while( true );
}


// ================================================================================================
// sub_b1951 @ 0xb1951 [__watcall]
// ================================================================================================

undefined8 __watcall sub_b1951(undefined2 param_1,undefined4 unaff_EDX)

{
  ushort uVar1;
  
  uVar1 = in(param_1);
  return CONCAT44(unaff_EDX,(uint)uVar1);
}


// ================================================================================================
// sub_b195c @ 0xb195c [__watcall]
// ================================================================================================

undefined8 __watcall sub_b195c(undefined4 param_1,undefined4 unaff_EDX)

{
  uint uVar1;
  int iVar2;
  byte *pbVar3;
  byte *pbVar4;
  
  for (pbVar3 = &unk_d8b4a; pbVar3 != (byte *)&font_kaufm; pbVar3 = pbVar3 + 6) {
    *pbVar3 = *pbVar3 & 1;
  }
  while( true ) {
    uVar1 = 0x100;
    pbVar3 = (byte *)&font_kaufm;
    for (pbVar4 = &unk_d8b4a; pbVar4 != (byte *)&font_kaufm; pbVar4 = pbVar4 + 6) {
      if (((*pbVar4 & 2) == 0) && (pbVar4[1] < uVar1)) {
        uVar1 = (uint)pbVar4[1];
        pbVar3 = pbVar4;
      }
    }
    if (pbVar3 == (byte *)&font_kaufm) break;
    *pbVar3 = *pbVar3 | 2;
    iVar2 = (**(code **)(pbVar3 + 2))();
    if (iVar2 != 0) {
LAB_000b19c1:
      return CONCAT44(unaff_EDX,iVar2);
    }
  }
  iVar2 = 0;
  goto LAB_000b19c1;
}


// ================================================================================================
// sub_b19c7 @ 0xb19c7 [__watcall]
// ================================================================================================

undefined8 __watcall sub_b19c7(undefined4 param_1,undefined4 unaff_EDX)

{
  out((short)param_1,(short)unaff_EDX);
  return CONCAT44(param_1,unaff_EDX);
}


// ================================================================================================
// sub_b19e0 @ 0xb19e0 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

longlong __watcall sub_b19e0(undefined4 param_1,uint unaff_EDX)

{
  byte_d8b0e = 1;
  _dword_f79e8 = 0;
  dword_f79d8._0_1_ = 0;
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// sub_b1a04 @ 0xb1a04 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __watcall sub_b1a04(undefined4 param_1,undefined4 unaff_EDX)

{
  int iVar1;
  byte in_CF;
  byte in_PF;
  byte in_AF;
  byte in_ZF;
  byte in_SF;
  byte in_TF;
  byte in_IF;
  byte in_OF;
  byte in_NT;
  ushort uVar2;
  
  uVar2 = (ushort)(in_NT & 1) * 0x4000 | (ushort)(in_OF & 1) * 0x800 | (ushort)(in_IF & 1) * 0x200 |
          (ushort)(in_TF & 1) * 0x100 | (ushort)(in_SF & 1) * 0x80 | (ushort)(in_ZF & 1) * 0x40 |
          (ushort)(in_AF & 1) * 0x10 | (ushort)(in_PF & 1) * 4 | (ushort)(in_CF & 1);
  sub_b122f();
  iVar1 = sub_b1554(2,param_1,param_1,unaff_EDX,uVar2);
  if (iVar1 == 0) {
    sub_aa200(word_d8772,0x47);
    sub_aa200(word_d8776,unaff_EDX);
    dword_f79d8._0_1_ = (byte)dword_f79d8 | 8;
    sub_aa200(word_d8772,0x45);
    sub_aa200(word_d8776,(byte)dword_f79d8);
    _dword_f79e8 = _dword_f79e8 | 2;
    sub_aa200(word_d8764,4);
    sub_aa200(word_d8766,_dword_f79e8);
    sub_b1256();
    iVar1 = 0;
  }
  else {
    sub_b1256();
  }
  return iVar1;
}


// ================================================================================================
// sub_b1ac8 @ 0xb1ac8 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __watcall sub_b1ac8(undefined4 param_1,undefined4 unaff_EDX)

{
  int iVar1;
  byte in_CF;
  byte in_PF;
  byte in_AF;
  byte in_ZF;
  byte in_SF;
  byte in_TF;
  byte in_IF;
  byte in_OF;
  byte in_NT;
  ushort uVar2;
  
  uVar2 = (ushort)(in_NT & 1) * 0x4000 | (ushort)(in_OF & 1) * 0x800 | (ushort)(in_IF & 1) * 0x200 |
          (ushort)(in_TF & 1) * 0x100 | (ushort)(in_SF & 1) * 0x80 | (ushort)(in_ZF & 1) * 0x40 |
          (ushort)(in_AF & 1) * 0x10 | (ushort)(in_PF & 1) * 4 | (ushort)(in_CF & 1);
  sub_b122f();
  iVar1 = sub_b1554(1,param_1,param_1,unaff_EDX,uVar2);
  if (iVar1 == 0) {
    sub_aa200(word_d8772,0x46);
    sub_aa200(word_d8776,unaff_EDX);
    dword_f79d8._0_1_ = (byte)dword_f79d8 | 4;
    sub_aa200(word_d8772,0x45);
    sub_aa200(word_d8776,(byte)dword_f79d8);
    _dword_f79e8 = _dword_f79e8 | 1;
    sub_aa200(word_d8764,4);
    sub_aa200(word_d8766,_dword_f79e8);
    sub_b1256();
    iVar1 = 0;
  }
  else {
    sub_b1256();
  }
  return iVar1;
}


// ================================================================================================
// sub_b1b8c @ 0xb1b8c [__watcall]
// ================================================================================================

void __watcall
sub_b1b8c(undefined4 param_1,undefined4 param_2,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  byte in_CF;
  byte in_PF;
  byte in_AF;
  byte in_ZF;
  byte in_SF;
  byte in_TF;
  byte in_IF;
  byte in_OF;
  byte in_NT;
  ushort uVar1;
  
  uVar1 = (ushort)(in_NT & 1) * 0x4000 | (ushort)(in_OF & 1) * 0x800 | (ushort)(in_IF & 1) * 0x200 |
          (ushort)(in_TF & 1) * 0x100 | (ushort)(in_SF & 1) * 0x80 | (ushort)(in_ZF & 1) * 0x40 |
          (ushort)(in_AF & 1) * 0x10 | (ushort)(in_PF & 1) * 4 | (ushort)(in_CF & 1);
  sub_b122f();
  sub_b1554(1,0,unaff_EBX,unaff_ECX,uVar1);
  dword_f79d8._0_1_ = (byte)dword_f79d8 & 0xfb;
  dword_f79e8 = dword_f79e8 & 0xfe;
  sub_aa200(word_d8772,0x45);
  sub_aa200(word_d8776,(byte)dword_f79d8);
  sub_b1256();
  return;
}


// ================================================================================================
// sub_b1bf8 @ 0xb1bf8 [__watcall]
// ================================================================================================

void __watcall
sub_b1bf8(undefined4 param_1,undefined4 param_2,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  byte in_CF;
  byte in_PF;
  byte in_AF;
  byte in_ZF;
  byte in_SF;
  byte in_TF;
  byte in_IF;
  byte in_OF;
  byte in_NT;
  ushort uVar1;
  
  uVar1 = (ushort)(in_NT & 1) * 0x4000 | (ushort)(in_OF & 1) * 0x800 | (ushort)(in_IF & 1) * 0x200 |
          (ushort)(in_TF & 1) * 0x100 | (ushort)(in_SF & 1) * 0x80 | (ushort)(in_ZF & 1) * 0x40 |
          (ushort)(in_AF & 1) * 0x10 | (ushort)(in_PF & 1) * 4 | (ushort)(in_CF & 1);
  sub_b122f();
  sub_b1554(2,0,unaff_EBX,unaff_ECX,uVar1);
  dword_f79d8._0_1_ = (byte)dword_f79d8 & 0xf7;
  dword_f79e8 = dword_f79e8 & 0xfd;
  sub_aa200(word_d8772,0x45);
  sub_aa200(word_d8776,(byte)dword_f79d8);
  sub_b1256();
  return;
}


// ================================================================================================
// sub_b1c70 @ 0xb1c70 [__watcall]
// ================================================================================================

longlong __watcall sub_b1c70(undefined4 param_1,uint unaff_EDX)

{
  ushort uVar1;
  
  byte_d8b10 = 1;
  dword_f7b78 = 0;
  for (uVar1 = 0; uVar1 < word_f79a0; uVar1 = uVar1 + 1) {
    (&unk_f79f8)[(uint)uVar1 * 3] = 0;
    (&unk_f79fc)[(uint)uVar1 * 3] = 0;
  }
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// sub_b1cbc @ 0xb1cbc [__watcall]
// ================================================================================================

uint __watcall sub_b1cbc(undefined4 param_1,undefined4 unaff_EDX)

{
  uint uVar1;
  uint uVar2;
  uint extraout_EDX;
  uint extraout_EDX_00;
  ushort uVar3;
  byte in_AF;
  byte in_TF;
  byte in_IF;
  byte in_NT;
  ushort uVar4;
  uint local_20;
  uint local_1c;
  uint local_18;
  
  uVar4 = (ushort)(in_NT & 1) * 0x4000 | (ushort)SBORROW4((int)&stack0xffffffec,0xc) * 0x800 |
          (ushort)(in_IF & 1) * 0x200 | (ushort)(in_TF & 1) * 0x100 |
          (ushort)((int)&local_20 < 0) * 0x80 |
          (ushort)(&stack0x00000000 == (undefined *)0x20) * 0x40 | (ushort)(in_AF & 1) * 0x10 |
          (ushort)((POPCOUNT((uint)&local_20 & 0xff) & 1U) == 0) * 4 |
          (ushort)(&stack0xffffffec < (undefined *)0xc);
  sub_b122f();
  uVar2 = 0xffffffff;
  local_1c = 0xffffffff;
  local_18 = 1;
  uVar3 = 0;
  while( true ) {
    if (word_f79a0 <= uVar3) {
      if (uVar2 != 0xffffffff) {
        if ((&unk_f7a00)[uVar2 * 3] != 0) {
          (*(code *)(&unk_f7a00)[uVar2 * 3])(uVar4);
          uVar2 = extraout_EDX;
        }
        dword_f7b78 = dword_f7b78 | 1 << ((byte)uVar2 & 0x1f);
        (&unk_f79fc)[uVar2 * 3] = param_1;
        (&unk_f79f8)[uVar2 * 3] = dword_d89dc;
        dword_d89dc = dword_d89dc + 1;
        (&unk_f7a00)[uVar2 * 3] = unaff_EDX;
      }
      sub_b1256();
      return extraout_EDX_00;
    }
    uVar1 = 1 << ((byte)uVar3 & 0x1f);
    if ((uVar1 & dword_f7b78) == 0) break;
    if (local_18 <= (uint)(&unk_f79fc)[(uint)uVar3 * 3]) {
      if ((local_18 < (uint)(&unk_f79fc)[(uint)uVar3 * 3]) ||
         ((uint)(&unk_f79f8)[(uint)uVar3 * 3] < local_1c)) {
        uVar2 = (uint)uVar3;
        local_1c = (&unk_f79f8)[uVar2 * 3];
      }
      local_18 = (&unk_f79fc)[(uint)uVar3 * 3];
    }
    local_20 = (uint)uVar3;
    uVar3 = uVar3 + 1;
  }
  dword_f7b78 = dword_f7b78 | uVar1;
  uVar2 = (uint)uVar3;
  (&unk_f79fc)[uVar2 * 3] = param_1;
  (&unk_f79f8)[uVar2 * 3] = dword_d89dc;
  dword_d89dc = dword_d89dc + 1;
  (&unk_f7a00)[uVar2 * 3] = unaff_EDX;
  sub_b1256();
  return uVar2;
}


// ================================================================================================
// sub_b1e2c @ 0xb1e2c [__watcall]
// ================================================================================================

void __watcall sub_b1e2c(byte param_1)

{
  sub_b122f();
  dword_f7b78 = dword_f7b78 & ~(1 << (param_1 & 0x1f));
  sub_b1256();
  return;
}


// ================================================================================================
// sub_b1e64 @ 0xb1e64 [__watcall]
// ================================================================================================

void __watcall sub_b1e64(undefined4 param_1,int unaff_EDX)

{
  int extraout_EDX;
  byte in_CF;
  byte in_PF;
  byte in_AF;
  byte in_ZF;
  byte in_SF;
  byte in_TF;
  byte in_IF;
  byte in_OF;
  byte in_NT;
  
  sub_b122f(param_1,param_1,unaff_EDX,param_1,
            (ushort)(in_NT & 1) * 0x4000 | (ushort)(in_OF & 1) * 0x800 | (ushort)(in_IF & 1) * 0x200
            | (ushort)(in_TF & 1) * 0x100 | (ushort)(in_SF & 1) * 0x80 | (ushort)(in_ZF & 1) * 0x40
            | (ushort)(in_AF & 1) * 0x10 | (ushort)(in_PF & 1) * 4 | (ushort)(in_CF & 1));
  (&unk_f79fc)[extraout_EDX * 3] = (&unk_f79fc)[extraout_EDX * 3] + unaff_EDX;
  sub_b1256();
  return;
}


// ================================================================================================
// sub_b1ea0 @ 0xb1ea0 [__watcall]
// ================================================================================================

undefined8 __watcall
sub_b1ea0(uint param_1,undefined4 unaff_EDX,undefined4 param_3,undefined4 unaff_ECX)

{
  undefined uVar1;
  undefined4 uVar2;
  byte in_CF;
  byte in_PF;
  byte in_AF;
  byte in_ZF;
  byte in_SF;
  byte in_TF;
  byte in_IF;
  byte in_OF;
  byte in_NT;
  ushort uVar3;
  
  uVar3 = (ushort)(in_NT & 1) * 0x4000 | (ushort)(in_OF & 1) * 0x800 | (ushort)(in_IF & 1) * 0x200 |
          (ushort)(in_TF & 1) * 0x100 | (ushort)(in_SF & 1) * 0x80 | (ushort)(in_ZF & 1) * 0x40 |
          (ushort)(in_AF & 1) * 0x10 | (ushort)(in_PF & 1) * 4 | (ushort)(in_CF & 1);
  sub_b122f();
  sub_aa200(word_d8772,0x43,param_1,unaff_ECX,uVar3);
  sub_b19c7(word_d8774,param_1);
  sub_aa200(word_d8772,0x44);
  sub_aa200(word_d8776,param_1 >> 0x10 & 0xff);
  uVar1 = sub_b128c(word_d8778);
  uVar2 = sub_b1256();
  return CONCAT44(unaff_EDX,CONCAT31((int3)((uint)uVar2 >> 8),uVar1));
}


// ================================================================================================
// sub_b1f1c @ 0xb1f1c [__watcall]
// ================================================================================================

void __watcall sub_b1f1c(uint param_1,undefined unaff_DL)

{
  byte in_CF;
  byte in_PF;
  byte in_AF;
  byte in_ZF;
  byte in_SF;
  byte in_TF;
  byte in_IF;
  byte in_OF;
  byte in_NT;
  ushort uVar1;
  
  uVar1 = (ushort)(in_NT & 1) * 0x4000 | (ushort)(in_OF & 1) * 0x800 | (ushort)(in_IF & 1) * 0x200 |
          (ushort)(in_TF & 1) * 0x100 | (ushort)(in_SF & 1) * 0x80 | (ushort)(in_ZF & 1) * 0x40 |
          (ushort)(in_AF & 1) * 0x10 | (ushort)(in_PF & 1) * 4 | (ushort)(in_CF & 1);
  sub_b122f();
  sub_aa200(word_d8772,0x43,param_1,unaff_DL,uVar1);
  sub_b19c7(word_d8774,param_1);
  sub_aa200(word_d8772,0x44);
  sub_aa200(word_d8776,param_1 >> 0x10 & 0xff);
  sub_aa200(word_d8778,unaff_DL);
  sub_b1256();
  return;
}


// ================================================================================================
// sub_b1f9c @ 0xb1f9c [__watcall]
// ================================================================================================

void __watcall sub_b1f9c(byte *param_1,uint unaff_EDX,int unaff_EBX,byte unaff_CL)

{
  bool bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte *pbVar5;
  char local_18;
  
  local_18 = (char)(unaff_EDX >> 0x10);
  bVar1 = false;
  if ((unaff_CL & 0x80) == 0) {
    bVar2 = 0;
  }
  else {
    bVar2 = 0x80;
  }
  sub_b122f();
  while (unaff_EBX != 0) {
    sub_aa200(word_d8772,0x44);
    sub_aa200(word_d8776,local_18);
    local_18 = local_18 + '\x01';
    pbVar5 = param_1;
    do {
      sub_aa200(word_d8772,0x43);
      param_1 = pbVar5 + 1;
      sub_b19c7(word_d8774,unaff_EDX & 0xffff);
      unaff_EDX = unaff_EDX + 1;
      bVar4 = bVar2 ^ *pbVar5;
      if ((unaff_CL & 0x40) != 0) {
        bVar3 = *pbVar5;
        if (bVar1) {
          bVar3 = bVar4;
        }
        bVar1 = (bool)(bVar1 ^ 1);
        bVar4 = bVar3;
      }
      sub_aa200(word_d8778,bVar4);
      unaff_EBX = unaff_EBX + -1;
    } while ((unaff_EBX != 0) && (pbVar5 = param_1, (short)unaff_EDX != 0));
  }
  sub_b1256();
  return;
}


// ================================================================================================
// sub_b2074 @ 0xb2074 [__watcall]
// ================================================================================================

ulonglong __watcall sub_b2074(uint param_1,undefined4 unaff_EDX)

{
  undefined uVar1;
  undefined uVar2;
  undefined uVar3;
  char cVar4;
  uint uVar5;
  undefined4 uVar6;
  uint uVar7;
  ushort uVar8;
  undefined2 local_30;
  
  uVar1 = sub_b1ea0();
  uVar7 = param_1 ^ 0x20;
  uVar2 = sub_b1ea0(uVar7,0x55);
  sub_b1f1c(param_1);
  sub_b1f1c(uVar7,0);
  uVar5 = sub_b1ea0(param_1);
  if ((char)uVar5 == 'U') {
    sub_b1f1c(param_1,0);
    sub_b1f1c(uVar7,0x55);
    uVar6 = sub_b1ea0(param_1);
    if ((char)uVar6 != '\0') {
      return CONCAT44(unaff_EDX,uVar6) & 0xffffffffffffff00;
    }
    sub_b1f1c(param_1,0xaa);
    sub_b1f1c(uVar7,0);
    uVar6 = sub_b1ea0(param_1);
    if ((char)uVar6 != -0x56) {
      return CONCAT44(unaff_EDX,uVar6) & 0xffffffffffffff00;
    }
    sub_b1f1c(param_1,0xff);
    sub_b1f1c(uVar7,0);
    uVar6 = sub_b1ea0(param_1);
    if ((char)uVar6 != -1) {
      return CONCAT44(unaff_EDX,uVar6) & 0xffffffffffffff00;
    }
    if (param_1 < 0x40000) {
      sub_b1f1c(param_1,uVar1);
      uVar6 = sub_b1f1c(uVar7,uVar2);
      return CONCAT44(unaff_EDX,CONCAT31((int3)((uint)uVar6 >> 8),1));
    }
    for (uVar8 = 0; (uVar8 != 4 && (local_30 = (ushort)(param_1 >> 0x12), uVar8 != local_30));
        uVar8 = uVar8 + 1) {
      uVar5 = param_1 & 0x3ffff | (uint)uVar8 << 0x12;
      uVar3 = sub_b1ea0(uVar5,0xaa);
      sub_b1f1c(uVar5);
      sub_b1f1c(uVar7,0);
      cVar4 = sub_b1ea0(param_1);
      if (cVar4 == -0x56) {
        sub_b1f1c(param_1,uVar1);
        uVar6 = sub_b1f1c(uVar7,uVar2);
        return CONCAT44(unaff_EDX,uVar6) & 0xffffffffffffff00;
      }
      sub_b1f1c(uVar5,uVar3);
    }
    sub_b1f1c(param_1,uVar1);
    uVar6 = sub_b1f1c(uVar7,uVar2);
    uVar5 = CONCAT31((int3)((uint)uVar6 >> 8),2);
  }
  else {
    uVar5 = uVar5 & 0xffffff00;
  }
  return CONCAT44(unaff_EDX,uVar5);
}


// ================================================================================================
// sub_b2220 @ 0xb2220 [__watcall]
// ================================================================================================

undefined8 __watcall
sub_b2220(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
         undefined4 param_5,uint param_6,undefined4 *param_7)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  short local_10;
  short sStack_e;
  short local_c;
  
  local_c = (short)param_6;
  if (((ushort)(param_6 >> 0x10) & 0x7ff0) == 0x7ff0) {
    puVar1 = param_7;
    if ((param_6 & 0x80000000) != 0) {
      puVar1 = (undefined4 *)((int)param_7 + 1);
      *(undefined *)param_7 = 0x2d;
    }
    sStack_e = (short)((uint)param_5 >> 0x10);
    local_10 = (short)param_5;
    uVar2 = dword_c4b60;
    if (((local_10 == 0 && sStack_e == 0) && local_c == 0) && (param_6 & 0xf0000) == 0) {
      uVar2 = dword_c4b5c;
    }
    *puVar1 = uVar2;
    uVar2 = 1;
  }
  else {
    uVar2 = 0;
  }
  return CONCAT44(param_2,uVar2);
}


// ================================================================================================
// sub_b22a4 @ 0xb22a4 [__watcall]
// ================================================================================================

undefined8 __watcall sub_b22a4(undefined4 param_1,undefined4 param_2)

{
  sub_b27a0();
  return CONCAT44(param_2,param_1);
}


// ================================================================================================
// sub_b22e0 @ 0xb22e0 [__watcall] noreturn
// ================================================================================================

void __watcall sub_b22e0(int param_2)

{
  int iVar1;
  undefined4 uVar2;
  longdouble lVar3;
  double param_1;
  int in_stack_0000000c;
  undefined4 in_stack_00000010;
  
  uVar2 = in_stack_00000010;
  iVar1 = in_stack_0000000c;
  if (param_2 != in_stack_0000000c) {
    lVar3 = (longdouble)sub_b2321();
    param_1 = (double)lVar3;
  }
  sub_b27f4(&stack0x00000004,uVar2);
                    /* WARNING: Subroutine does not return */
  sub_b27ba(iVar1,uVar2);
}


// ================================================================================================
// sub_b2319 @ 0xb2319 [__watcall]
// ================================================================================================

void __watcall sub_b2319(void)

{
  return;
}


// ================================================================================================
// sub_b2321 @ 0xb2321 [__watcall]
// ================================================================================================

undefined8 __watcall sub_b2321(undefined4 param_2,undefined4 unaff_EDX)

{
  short *psVar1;
  int iVar2;
  bool bVar3;
  int in_stack_0000000c;
  
  psVar1 = &unk_c4ca8;
  if (in_stack_0000000c < 0) {
    iVar2 = -in_stack_0000000c;
    bVar3 = in_stack_0000000c == -0x134;
    in_stack_0000000c = iVar2;
    if (bVar3 || iVar2 < 0x134) goto LAB_000b23c0;
  }
  else {
    iVar2 = in_stack_0000000c;
    if (in_stack_0000000c < 0x135) goto LAB_000b23c0;
  }
  in_stack_0000000c = iVar2 + -0xd8;
LAB_000b23c0:
  while( true ) {
    if (*psVar1 <= in_stack_0000000c) {
      in_stack_0000000c = in_stack_0000000c - *psVar1;
    }
    if (in_stack_0000000c == 0) break;
    if (*psVar1 != 1) {
      psVar1 = psVar1 + 5;
    }
  }
  return CONCAT44(unaff_EDX,param_2);
}


// ================================================================================================
// sub_b2408 @ 0xb2408 [__watcall]
// ================================================================================================

undefined8 __watcall
sub_b2408(undefined4 param_1_00,undefined4 param_3,undefined4 param_3_00,undefined4 param_4,
         int param_1,uint param_6_00,int param_6,int *param_8,undefined4 *param_9,int param_10,
         char *param_11)

{
  char cVar1;
  char *pcVar2;
  int iVar3;
  int extraout_EDX;
  char *pcVar4;
  char *pcVar5;
  longdouble lVar6;
  undefined8 uVar7;
  char acStack_44 [18];
  undefined2 uStack_32;
  undefined2 local_30;
  short local_2e;
  undefined2 local_2c;
  undefined2 local_2a;
  int iStack_20;
  undefined local_1c;
  
  *param_9 = 0;
  *param_8 = 0;
  uVar7 = sub_b2220();
  pcVar2 = (char *)((ulonglong)uVar7 >> 0x20);
  if ((int)uVar7 == 0) {
    local_30 = 0;
    local_2e = 0;
    local_2c = 0;
    local_2a = 0;
    if (((param_6_00 & 0x7fffffff) != 0) || (param_1 != 0)) {
      if ((double)CONCAT44(param_6_00,param_1) < 0.0) {
        *param_9 = 0xffffffff;
      }
      sub_b2980();
      iVar3 = *param_8;
      if (iVar3 < 0) {
        iVar3 = -iVar3;
      }
      iVar3 = (iVar3 * 3 + 5) / 10;
      if (*param_8 < 0) {
        iVar3 = -iVar3;
      }
      *param_8 = iVar3;
      if (param_10 == 0x46) {
        param_6 = param_6 + iVar3;
      }
      if (-1 < param_6) {
        if (0x10 < param_6) {
          param_6 = 0x10;
        }
        local_1c = 0;
        lVar6 = (longdouble)sub_b27a0();
        if (((longdouble)0 == lVar6) && (extraout_EDX < param_6)) {
          local_1c = 1;
        }
                    /* WARNING: Subroutine does not return */
        sub_b22e0(*param_8);
      }
      iStack_20 = (int)local_2e;
      if ((int)(CONCAT22(local_30,uStack_32) | CONCAT22(local_2e,local_30) |
                CONCAT22(local_2c,local_2e) | CONCAT22(local_2a,local_2c)) >> 0x10 == 0) {
        *param_9 = 0;
        *param_8 = 0;
        if (param_10 == 0x46) {
          param_6 = param_6 - iVar3;
        }
      }
    }
    if (param_6 < 1) {
      param_6 = 1;
    }
    else if (0x11 < param_6) {
      param_6 = 0x11;
    }
    pcVar4 = acStack_44;
    sub_b285f(&local_30,acStack_44,param_6);
    pcVar5 = param_11;
    do {
      cVar1 = *pcVar4;
      *pcVar5 = cVar1;
      pcVar2 = param_11;
      if (cVar1 == '\0') break;
      cVar1 = pcVar4[1];
      pcVar4 = pcVar4 + 2;
      pcVar5[1] = cVar1;
      pcVar5 = pcVar5 + 2;
    } while (cVar1 != '\0');
  }
  return CONCAT44(param_3,pcVar2);
}


// ================================================================================================
// sub_b251b @ 0xb251b [__watcall]
// ================================================================================================

undefined8 __watcall sub_b251b(int param_1,undefined4 param_2,undefined4 param_3,int *unaff_ECX)

{
  char cVar1;
  char *pcVar2;
  int unaff_EBP;
  char *pcVar3;
  undefined4 *unaff_EDI;
  char *pcVar4;
  
  if (param_1 != 0) {
    *unaff_ECX = *unaff_ECX + param_1;
                    /* WARNING: Subroutine does not return */
    sub_b22e0(*unaff_ECX);
  }
  *(int *)(unaff_EBP + -0x1c) = *(int *)(unaff_EBP + -0x2c) >> 0x10;
  if (((*(int *)(unaff_EBP + -0x2e) >> 0x10 == 0 && *(int *)(unaff_EBP + -0x1c) == 0) &&
      *(int *)(unaff_EBP + -0x2a) >> 0x10 == 0) && *(int *)(unaff_EBP + -0x28) >> 0x10 == 0) {
    *unaff_EDI = 0;
    *unaff_ECX = 0;
  }
  pcVar2 = *(char **)(unaff_EBP + 0x20);
  pcVar3 = (char *)(unaff_EBP + -0x40);
  sub_b285f(unaff_EBP + -0x2c,unaff_EBP + -0x40);
  pcVar4 = pcVar2;
  do {
    cVar1 = *pcVar3;
    *pcVar4 = cVar1;
    if (cVar1 == '\0') break;
    cVar1 = pcVar3[1];
    pcVar3 = pcVar3 + 2;
    pcVar4[1] = cVar1;
    pcVar4 = pcVar4 + 2;
  } while (cVar1 != '\0');
  return CONCAT44(*(undefined4 *)(unaff_EBP + -0xc),pcVar2);
}


// ================================================================================================
// sub_b255d @ 0xb255d [__watcall]
// ================================================================================================

undefined8 __watcall sub_b255d(int param_1,undefined4 param_2,undefined4 param_3,int *unaff_ECX)

{
  char cVar1;
  char *pcVar2;
  int unaff_EBP;
  char *pcVar3;
  undefined4 *unaff_EDI;
  char *pcVar4;
  
  if (0 < param_1) {
    *unaff_ECX = *unaff_ECX + 1;
  }
  *(int *)(unaff_EBP + -0x1c) = *(int *)(unaff_EBP + -0x2c) >> 0x10;
  if (((*(int *)(unaff_EBP + -0x2e) >> 0x10 == 0 && *(int *)(unaff_EBP + -0x1c) == 0) &&
      *(int *)(unaff_EBP + -0x2a) >> 0x10 == 0) && *(int *)(unaff_EBP + -0x28) >> 0x10 == 0) {
    *unaff_EDI = 0;
    *unaff_ECX = 0;
  }
  pcVar2 = *(char **)(unaff_EBP + 0x20);
  pcVar3 = (char *)(unaff_EBP + -0x40);
  sub_b285f(unaff_EBP + -0x2c,unaff_EBP + -0x40);
  pcVar4 = pcVar2;
  do {
    cVar1 = *pcVar3;
    *pcVar4 = cVar1;
    if (cVar1 == '\0') break;
    cVar1 = pcVar3[1];
    pcVar3 = pcVar3 + 2;
    pcVar4[1] = cVar1;
    pcVar4 = pcVar4 + 2;
  } while (cVar1 != '\0');
  return CONCAT44(*(undefined4 *)(unaff_EBP + -0xc),pcVar2);
}


// ================================================================================================
// sub_b25ee @ 0xb25ee [__watcall]
// ================================================================================================

void __watcall sub_b25ee(uint *param_1,uint *unaff_EDX)

{
  uint uVar1;
  byte bVar2;
  ushort uVar3;
  uint uVar4;
  uint uVar5;
  uint *puVar6;
  undefined8 uVar7;
  
  uVar1 = param_1[1];
  *unaff_EDX = *param_1;
  unaff_EDX[1] = uVar1;
  uVar4 = uVar1 & 0x7ff00000;
  puVar6 = unaff_EDX;
  if (((uVar4 != 0) && (puVar6 = param_1, uVar4 < 0x43300000)) &&
     (uVar3 = (ushort)(uVar4 >> 0x14), puVar6 = unaff_EDX, 0x3fe < uVar3)) {
    uVar4 = 0;
    bVar2 = (byte)(uVar3 - 0x3ff);
    if (bVar2 < 0x15) {
      uVar5 = -0x100000 >> (bVar2 & 0x1f);
    }
    else {
      uVar5 = 0xffffffff;
      uVar4 = -0x80000000 >> (bVar2 - 0x15 & 0x1f);
    }
    unaff_EDX[1] = unaff_EDX[1] & uVar5;
    *unaff_EDX = *unaff_EDX & uVar4;
    uVar7 = sub_b26c9(~uVar4 & *param_1,~uVar5 & param_1[1]);
    uVar4 = (uint)((ulonglong)uVar7 >> 0x20);
    if (uVar4 != 0) {
      uVar4 = uVar4 | uVar1 & 0x80000000;
    }
    param_1[1] = uVar4;
    *param_1 = (uint)uVar7;
    return;
  }
  puVar6[1] = 0;
  *puVar6 = 0;
  return;
}


// ================================================================================================
// sub_b267e @ 0xb267e [__watcall]
// ================================================================================================

void __watcall sub_b267e(byte *param_1,undefined8 *unaff_EDX)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  bool bVar7;
  bool bVar8;
  undefined8 uVar9;
  
  iVar6 = 0;
  uVar5 = 0;
  while( true ) {
    if (*param_1 == 0) break;
    bVar7 = CARRY4(uVar5,uVar5);
    uVar1 = uVar5 * 2;
    bVar8 = CARRY4(uVar5 * 4,uVar5);
    uVar3 = uVar5 * 5;
    uVar2 = uVar5 * 10;
    uVar4 = *param_1 & 0xffffff0f;
    uVar5 = uVar2 + uVar4;
    iVar6 = (iVar6 * 5 + (uint)bVar7 * 2 + (uint)CARRY4(uVar1,uVar1) + (uint)bVar8) * 2 +
            (uint)CARRY4(uVar3,uVar3) + (uint)CARRY4(uVar2,uVar4);
    param_1 = param_1 + 1;
  }
  uVar9 = sub_b26c9(uVar5,iVar6);
  *unaff_EDX = uVar9;
  return;
}


// ================================================================================================
// sub_b26c9 @ 0xb26c9 [__watcall]
// ================================================================================================

uint __watcall sub_b26c9(uint param_1,uint unaff_EDX)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  bool bVar4;
  
  uVar3 = param_1 | unaff_EDX;
  if (uVar3 != 0) {
    if ((unaff_EDX & 0xfff00000) == 0) {
      do {
        bVar4 = CARRY4(param_1,param_1);
        param_1 = param_1 * 2;
        unaff_EDX = unaff_EDX * 2 + (uint)bVar4;
      } while ((unaff_EDX & 0xfff00000) == 0);
    }
    else if ((unaff_EDX & 0xffe00000) != 0) {
      do {
        uVar2 = unaff_EDX & 1;
        unaff_EDX = unaff_EDX >> 1;
        uVar1 = param_1 & 1;
        param_1 = param_1 >> 1 | (uint)(uVar2 != 0) << 0x1f;
        uVar3 = uVar3 >> 1 | (uint)(uVar1 != 0) << 0x1f;
      } while ((unaff_EDX & 0xffe00000) != 0);
      param_1 = param_1 + CARRY4(uVar3,uVar3);
    }
  }
  return param_1;
}


// ================================================================================================
// sub_b2720 @ 0xb2720 [__watcall]
// ================================================================================================

undefined8 __watcall sub_b2720(uint param_1,undefined4 unaff_EDX)

{
  return CONCAT44(unaff_EDX,(int)(param_1 & 0x3ffff) >> 1 | param_1 & 0xfffc0000);
}


// ================================================================================================
// sub_b273c @ 0xb273c [__watcall]
// ================================================================================================

uint __watcall sub_b273c(uint param_1,uint unaff_EDX,byte unaff_BL)

{
  uint uVar1;
  
  uVar1 = ((unaff_EDX & 0x1ff) << 7 | (int)(param_1 & 0xffff) >> 9) +
          ((int)(unaff_EDX & 0xffff) >> 9) * 0x10000;
  if ((unaff_BL & 1) != 0) {
    uVar1 = uVar1 * 2 & 0x3ffff | uVar1 & 0xc0000;
  }
  return uVar1;
}


// ================================================================================================
// sub_b27a0 @ 0xb27a0 [__watcall]
// ================================================================================================

undefined4 __watcall sub_b27a0(undefined4 param_2)

{
  longdouble lVar1;
  double *in_stack_0000000c;
  
  lVar1 = (longdouble)sub_961d0();
  *in_stack_0000000c = (double)lVar1;
  return param_2;
}


// ================================================================================================
// sub_b27ba @ 0xb27ba [__watcall] noreturn
// ================================================================================================

void __watcall sub_b27ba(void)

{
                    /* WARNING: Subroutine does not return */
  sub_b28c9();
}


// ================================================================================================
// sub_b27c1 @ 0xb27c1 [__watcall]
// ================================================================================================

int __watcall sub_b27c1(int param_1,uint *unaff_EDX)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int unaff_EDI;
  uint *puVar4;
  bool bVar5;
  
  puVar4 = (uint *)(unaff_EDI + (param_1 + 1) * 8);
  uVar2 = unaff_EDX[1];
  iVar3 = 0;
  while( true ) {
    bVar5 = uVar2 < *puVar4;
    if (uVar2 == *puVar4) {
      bVar5 = *unaff_EDX < puVar4[1];
    }
    if (bVar5) break;
    puVar4 = puVar4 + 2;
    iVar3 = iVar3 + 1;
  }
  while( true ) {
    uVar1 = puVar4[-2];
    bVar5 = uVar2 < uVar1;
    if (uVar2 == uVar1) {
      bVar5 = *unaff_EDX < puVar4[-1];
    }
    if (!bVar5) break;
    iVar3 = iVar3 + -1;
    puVar4 = puVar4 + -2;
  }
  return iVar3;
}


// ================================================================================================
// sub_b27f4 @ 0xb27f4 [__watcall]
// ================================================================================================

void __watcall sub_b27f4(uint *param_1,uint *unaff_EDX)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  bool bVar9;
  
  uVar5 = *param_1;
  uVar4 = param_1[1];
  uVar6 = uVar4 ^ uVar4 & 0xfff00000 ^ 0x100000;
  iVar7 = (uVar4 >> 0x14) - 0x433;
  if (iVar7 != 0) {
    if (uVar4 >> 0x14 < 0x433 || iVar7 == 0) {
      uVar4 = 0;
      iVar8 = 0;
      do {
        uVar3 = uVar6 & 1;
        uVar6 = uVar6 >> 1;
        uVar1 = uVar5 & 1;
        uVar2 = uVar5 >> 1;
        uVar5 = uVar2 | (uint)(uVar3 != 0) << 0x1f;
        uVar3 = uVar4 & 1;
        uVar4 = uVar4 >> 1 | (uint)(uVar1 != 0) << 0x1f;
        iVar8 = iVar8 * 2 + (uint)(uVar3 != 0);
        iVar7 = iVar7 + 1;
      } while (iVar7 != 0);
      if ((0x7fffffff < uVar4) && (((uVar4 != 0x80000000 || (iVar8 != 0)) || ((uVar2 & 1) != 0)))) {
        bVar9 = 0xfffffffe < uVar5;
        uVar5 = uVar5 + 1;
        uVar6 = uVar6 + bVar9;
      }
    }
    else {
      do {
        bVar9 = (int)uVar5 < 0;
        uVar5 = uVar5 << 1;
        uVar6 = uVar6 << 1 | (uint)bVar9;
        iVar7 = iVar7 + -1;
      } while (iVar7 != 0);
    }
  }
  *unaff_EDX = uVar5;
  unaff_EDX[1] = uVar6;
  return;
}


// ================================================================================================
// sub_b285f @ 0xb285f [__watcall]
// ================================================================================================

uint __watcall sub_b285f(int *param_1,int unaff_EDX,int unaff_EBX)

{
  ulonglong uVar1;
  byte bVar2;
  ushort uVar3;
  short sVar4;
  uint uVar5;
  int iVar6;
  short sVar8;
  uint uVar9;
  undefined *puVar10;
  uint uStack_14;
  byte bVar7;
  
  iVar6 = *param_1;
  uStack_14 = param_1[1];
  *(undefined *)(unaff_EDX + unaff_EBX) = 0;
  puVar10 = (undefined *)(unaff_EDX + unaff_EBX);
  do {
    uVar9 = 0;
    if (uStack_14 == 0) {
      uVar5 = uStack_14;
      if (iVar6 != 0) goto LAB_000b2889;
      sVar4 = 0;
    }
    else {
      uVar5 = uStack_14 / 10000;
      uVar9 = uStack_14 % 10000;
LAB_000b2889:
      uVar1 = CONCAT44(uVar9,iVar6);
      iVar6 = (int)(uVar1 / 10000);
      uVar3 = (ushort)(uVar1 % 10000);
      bVar7 = (byte)(uVar3 % 100);
      bVar2 = (byte)(uVar3 / 100);
      uVar9 = (uint)CONCAT11(bVar2 / 10,bVar2 % 10);
      sVar4 = CONCAT11(bVar7 / 10,bVar7 % 10);
      uStack_14 = uVar5;
    }
    sVar8 = (short)uVar9 + 0x3030;
    puVar10[-1] = (char)(sVar4 + 0x3030);
    if (unaff_EBX == 1) {
      return uStack_14;
    }
    puVar10[-2] = (char)((ushort)(sVar4 + 0x3030) >> 8);
    if (unaff_EBX == 2) {
      return uStack_14;
    }
    puVar10[-3] = (char)sVar8;
    if (unaff_EBX == 3) {
      return uStack_14;
    }
    puVar10[-4] = (char)((ushort)sVar8 >> 8);
    unaff_EBX = unaff_EBX + -4;
    puVar10 = puVar10 + -4;
    if (unaff_EBX == 0) {
      return uStack_14;
    }
  } while( true );
}


// ================================================================================================
// sub_b28c9 @ 0xb28c9 [__watcall] noreturn
// ================================================================================================

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Instruction at (ram,0x000b2912) overlaps instruction at (ram,0x000b2911)
    */

void __watcall sub_b28c9(undefined4 param_1,undefined4 param_2,undefined4 unaff_EBX,int unaff_ECX)

{
  uint uVar1;
  byte bVar2;
  byte bVar3;
  byte *pbVar5;
  undefined3 uVar10;
  int *piVar6;
  undefined4 uVar7;
  char *pcVar8;
  uint *puVar9;
  ushort *extraout_ECX;
  byte extraout_DL;
  char extraout_DL_00;
  undefined4 *unaff_ESI;
  undefined4 *unaff_EDI;
  int in_FS_OFFSET;
  byte in_AF;
  byte bVar11;
  char cVar4;
  
  bVar11 = 0;
  pbVar5 = (byte *)sub_b297e();
  bVar2 = (byte)pbVar5;
  *pbVar5 = *pbVar5 + bVar2;
  *pbVar5 = *pbVar5 + bVar2;
  *pbVar5 = *pbVar5 + bVar2;
  *pbVar5 = *pbVar5 + bVar2;
  *pbVar5 = *pbVar5 + bVar2;
  *pbVar5 = *pbVar5 + bVar2;
  *(byte **)pbVar5 = pbVar5 + *(int *)pbVar5;
  *pbVar5 = *pbVar5 + bVar2;
  *pbVar5 = *pbVar5 + bVar2;
  *pbVar5 = *pbVar5 + bVar2;
  uVar10 = (undefined3)((uint)pbVar5 >> 8);
  bVar2 = bVar2 | *pbVar5;
  pcVar8 = (char *)CONCAT31(uVar10,bVar2);
  *pcVar8 = *pcVar8 + bVar2;
  *pcVar8 = *pcVar8 + bVar2;
  *pcVar8 = *pcVar8 + bVar2;
  pcVar8[in_FS_OFFSET] = pcVar8[in_FS_OFFSET] + bVar2;
  *pcVar8 = *pcVar8 + bVar2;
  *pcVar8 = *pcVar8 + bVar2;
  piVar6 = (int *)CONCAT31(uVar10,bVar2 + (char)((uint)unaff_ECX >> 8));
  pbVar5 = (byte *)((int)piVar6 + *piVar6);
  bVar3 = (byte)pbVar5;
  *pbVar5 = *pbVar5 + bVar3;
  *pbVar5 = *pbVar5 + bVar3;
  bVar2 = *pbVar5;
  *pbVar5 = *pbVar5 + extraout_DL;
  in_AF = 9 < (bVar3 & 0xf) | in_AF;
  uVar10 = (undefined3)((uint)pbVar5 >> 8);
  bVar3 = bVar3 + in_AF * '\x06';
  cVar4 = bVar3 + (0x90 < (bVar3 & 0xf0) | CARRY1(bVar2,extraout_DL) | in_AF * (0xf9 < bVar3)) * '`'
  ;
  pcVar8 = (char *)CONCAT31(uVar10,cVar4);
  *pcVar8 = *pcVar8 + cVar4;
  *pcVar8 = *pcVar8 + cVar4;
  *pcVar8 = *pcVar8 + cVar4;
  bVar2 = DAT_00000186;
  pbVar5 = (byte *)CONCAT31(uVar10,DAT_00000186);
  *pbVar5 = *pbVar5 + DAT_00000186;
  pbVar5[0x42] = pbVar5[0x42] + bVar2;
  uVar7 = LocalDescriptorTableRegister();
  *(undefined4 *)pbVar5 = uVar7;
  *pbVar5 = *pbVar5 + bVar2;
  pbVar5[0x9896] = pbVar5[0x9896] + bVar2;
  *pbVar5 = *pbVar5 + bVar2;
  while( true ) {
    bVar3 = *pbVar5;
    *pbVar5 = *pbVar5 + bVar2;
    unaff_ECX = unaff_ECX + -1;
    if (unaff_ECX == 0 || *pbVar5 != 0) break;
    *(char *)(unaff_ESI + 0x26) = *(char *)(unaff_ESI + 0x26) + CARRY1(bVar3,bVar2);
  }
  uVar7 = func_0x0000023b();
  cVar4 = in(0xb);
  pcVar8 = (char *)CONCAT31((int3)((uint)uVar7 >> 8),cVar4);
  *pcVar8 = *pcVar8 + cVar4;
  *pcVar8 = *pcVar8 + cVar4;
  pcVar8 = (char *)func_0x00f371ae();
  bVar2 = (byte)pcVar8;
  *pcVar8 = *pcVar8 + bVar2;
  *pcVar8 = *pcVar8 + extraout_DL_00;
  *unaff_EDI = *unaff_ESI;
  uVar10 = (undefined3)(CONCAT22((short)((uint)pcVar8 >> 0x10),CONCAT11(bVar2 / 0x18,bVar2)) >> 8);
  puVar9 = (uint *)CONCAT31(uVar10,bVar2 % 0x18);
  *puVar9 = *puVar9 | (uint)puVar9;
  *(byte *)puVar9 = *(char *)puVar9 + bVar2 % 0x18;
  bVar3 = DAT_5af34e72;
  piVar6 = (int *)CONCAT31(uVar10,DAT_5af34e72);
  *(byte *)piVar6 = *(char *)piVar6 + DAT_5af34e72;
  pbVar5 = (byte *)((int)piVar6 + 0x7a);
  bVar2 = *pbVar5;
  *pbVar5 = *pbVar5 + bVar3;
  pcVar8 = (char *)((int)unaff_ESI + (uint)bVar11 * -8 + -0x6f);
  *pcVar8 = *pcVar8 + (char)((uint)unaff_EBX >> 8) + CARRY1(bVar2,bVar3);
  puVar9 = (uint *)((int)piVar6 + *piVar6);
  *(char *)((int)puVar9 + -0x790d5b3a) = *(char *)((int)puVar9 + -0x790d5b3a) + (char)puVar9;
  pcVar8 = (char *)((uint)puVar9 & *puVar9);
  *pcVar8 = *pcVar8 + (char)pcVar8;
  puVar9 = unaff_EDI + (uint)bVar11 * -2 + 0x1f;
  uVar1 = *puVar9;
  *puVar9 = *puVar9 >> 5;
  *extraout_ECX =
       *extraout_ECX +
       (ushort)((uVar1 >> 4 & 1) != 0) * (((ushort)pcVar8 & 3) - (*extraout_ECX & 3));
  *pcVar8 = *pcVar8 + (char)pcVar8;
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ================================================================================================
// sub_b297e @ 0xb297e [__watcall]
// ================================================================================================

void __watcall sub_b297e(void)

{
  return;
}


// ================================================================================================
// sub_b2980 @ 0xb2980 [__watcall]
// ================================================================================================

undefined8 __watcall
sub_b2980(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,int param_5,
         uint param_6,int *param_7)

{
  int iVar1;
  
  iVar1 = 0;
  if (((param_6 & 0x7fffffff) != 0) || (param_5 != 0)) {
    iVar1 = ((int)(param_6 >> 0x10 & 0x7ff0) >> 4) + -0x3fe;
  }
  *param_7 = iVar1;
  return CONCAT44(param_2,param_1);
}


// ================================================================================================
// sub_b29f0 @ 0xb29f0 [__watcall]
// ================================================================================================

void __watcall
sub_b29f0(undefined4 param_1,undefined2 unaff_DX,undefined4 param_3,undefined4 unaff_ECX)

{
  undefined uVar1;
  undefined3 uVar3;
  uint uVar2;
  undefined2 in_CS;
  short in_DS;
  undefined6 uVar4;
  
  if (word_d2d6e == 0) {
    uVar3 = (undefined3)((uint)param_1 >> 8);
    uVar1 = in(0x21);
    uVar2 = CONCAT31(uVar3,uVar1) | 3;
    out(0x21,(char)uVar2);
    word_d2d6e = in_DS;
    uVar4 = sub_9864c(uVar2,unaff_DX,9,unaff_ECX,CONCAT31(uVar3,uVar1));
    word_d2d60 = (undefined2)((uint6)uVar4 >> 0x20);
    dword_d2d5c = (undefined4)uVar4;
    uVar4 = sub_9864c(dword_d2d5c,word_d2d60,0x16);
    word_d2d66 = (undefined2)((uint6)uVar4 >> 0x20);
    dword_d2d62 = (undefined4)uVar4;
    uVar4 = sub_9864c(dword_d2d62,word_d2d66,0x23);
    word_d2d6c = (undefined2)((uint6)uVar4 >> 0x20);
    dword_d2d68 = (undefined4)uVar4;
    sub_98664(sub_b2b0a,in_CS,9);
    sub_98664(unk_b2c00,in_CS,0x23);
    out(0x21,uVar1);
    funcptr_d2c84 = sub_b2c4a;
    sub_b3454(sub_b2a9b);
  }
  return;
}


// ================================================================================================
// sub_b2a9b @ 0xb2a9b [__watcall]
// ================================================================================================

undefined4 __watcall
sub_b2a9b(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 unaff_ECX)

{
  byte bVar1;
  undefined2 extraout_var;
  
  if (word_d2d6e != 0) {
    word_d2d6e = 0;
    bVar1 = in(0x21);
    out(0x21,bVar1 | 3);
    sub_98664(dword_d2d5c,word_d2d60,9,unaff_ECX,bVar1);
    sub_98664(dword_d2d68,CONCAT22(extraout_var,word_d2d6c),0x23);
    DAT_00000417 = DAT_00000417 & 0xf0;
    out(0x21,bVar1);
    funcptr_d2c84 = sub_b2ccd;
  }
  return param_1;
}


// ================================================================================================
// sub_b2b0a @ 0xb2b0a [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __watcall sub_b2b0a(undefined4 param_1)

{
  byte bVar1;
  uint uVar2;
  uint uVar3;
  
  bVar1 = in(0x61);
  out(0x61,bVar1 | 0x80);
  out(0x61,bVar1);
  bVar1 = in(0x60);
  uVar2 = (uint)bVar1;
  if ((char)bVar1 < '\0') {
    (&unk_d2c5c)[uVar2] = 0;
    out(0x20,0x20);
    return param_1;
  }
  (&unk_d2cdc)[uVar2] = 1;
  out(0x20,0x20);
  if (uVar2 == 0x3a) {
    _dword_d2cd4 = _dword_d2cd4 ^ 1;
    out(0x60,0xed);
    out(0x60,dword_d2cd4 << 2);
  }
  else {
    if ((byte_d2d14 & 1) == 0) {
      if ((byte_d2cf9 & 1) == 0) {
        if (((byte_d2d06 & 1) == 0) && ((byte_d2d12 & 1) == 0)) {
          if ((_dword_d2cd4 & 1) == 0) {
            uVar2 = (uint)(byte)(&unk_d2d7c)[uVar2];
          }
          else {
            uVar2 = (uint)(byte)(&unk_d2e32)[uVar2];
          }
        }
        else {
          uVar2 = (uint)(byte)(&unk_d2dd7)[uVar2];
        }
      }
      else {
        uVar2 = (uint)(byte)(&unk_d2e8d)[uVar2];
      }
    }
    else {
      uVar2 = (uint)(byte)(&unk_d2ee8)[uVar2];
    }
    bVar1 = (byte)uVar2;
    uVar3 = uVar2;
    if (0x7f < bVar1) {
      uVar3 = CONCAT11(bVar1,bVar1) & 0xffffff00;
      if (0x8f < bVar1) {
        uVar3 = (uVar2 & 0xffff7f) << 8;
      }
    }
    if (uVar3 != 0) {
      *(uint *)(&unk_d2c8c + dword_d2ccc * 4) = uVar3;
      dword_d2ccc = dword_d2ccc + 1 & dword_d2cd8;
    }
  }
  return param_1;
}


// ================================================================================================
// sub_b2bf5 @ 0xb2bf5 [__watcall]
// ================================================================================================

undefined4 __watcall
sub_b2bf5(uint param_1,undefined4 param_2,int unaff_EBX,undefined4 param_4,undefined4 param_5,
         undefined4 param_6)

{
  byte bVar1;
  undefined2 uVar2;
  
  if ((byte_d2d2f & 1) == 0) {
    param_1 = CONCAT31((int3)(param_1 >> 8),(&unk_d2ee8)[unaff_EBX]);
  }
  bVar1 = (byte)param_1;
  if (0x7f < bVar1) {
    uVar2 = (undefined2)(param_1 >> 0x10);
    param_1 = CONCAT22(uVar2,CONCAT11(bVar1,bVar1)) & 0xffffff00;
    if (0x8f < bVar1) {
      param_1 = (CONCAT21(uVar2,bVar1) & 0xffff7f) << 8;
    }
  }
  if (param_1 != 0) {
    *(uint *)(&unk_d2c8c + dword_d2ccc * 4) = param_1;
    dword_d2ccc = dword_d2ccc + 1 & dword_d2cd8;
  }
  return param_6;
}


// ================================================================================================
// unk_b2c00 @ 0xb2c00
// ================================================================================================

void unk_b2c00(void)

{
  return;
}


// ================================================================================================
// unk_b2c01 @ 0xb2c01
// ================================================================================================

undefined8 unk_b2c01(void)

{
  undefined4 uVar1;
  undefined4 in_EDX;
  byte in_NT;
  
  sub_902a0();
  uVar1 = sub_b2c4a();
  if ((in_NT & 1) == 0) {
    return CONCAT44(in_EDX,uVar1);
  }
  return CONCAT44(in_EDX,uVar1);
}


// ================================================================================================
// sub_b2c4a @ 0xb2c4a [__watcall]
// ================================================================================================

uint __watcall sub_b2c4a(undefined4 param_1)

{
  int iVar1;
  char cVar2;
  
  cVar2 = (char)((uint)param_1 >> 8);
  if ((cVar2 == '\0') || (cVar2 == '\x10')) {
    do {
    } while (dword_d2cd0 == dword_d2ccc);
    iVar1 = dword_d2cd0 * 4;
    dword_d2cd0 = dword_d2cd0 + 1 & dword_d2cd8;
    return *(uint *)(&unk_d2c8c + iVar1);
  }
  if ((cVar2 == '\x01') || (cVar2 == '\x11')) {
    if (dword_d2cd0 != dword_d2ccc) {
      return *(uint *)(&unk_d2c8c + dword_d2cd0 * 4);
    }
  }
  else if ((cVar2 == '\x02') || (cVar2 == '\x12')) {
    return (byte_d2d06 | byte_d2d12) & 0xffffff01;
  }
  return 0;
}


// ================================================================================================
// sub_b2cbe @ 0xb2cbe [__cdecl]
// ================================================================================================

undefined sub_b2cbe(int param_1)

{
  return (&unk_d2cdc)[param_1];
}


// ================================================================================================
// sub_b2ccd @ 0xb2ccd [__watcall]
// ================================================================================================

undefined2 __watcall sub_b2ccd(void)

{
  code *pcVar1;
  undefined2 uVar2;
  
  pcVar1 = (code *)swi(0x16);
  uVar2 = (*pcVar1)();
  return uVar2;
}


// ================================================================================================
// fatalerror @ 0xb2cd8 [__cdecl]
// ================================================================================================

void fatalerror(void)

{
  undefined4 unaff_retaddr;
  
  if (dword_d2f74 == 0) {
    if (dword_d3024 != 0) {
      setdefaultscreen(unaff_retaddr);
      printf_at(0);
      waitkey();
    }
    restorevideo();
    fatal_dumpregs();
    (*(code *)funcptr_d41f0)();
  }
  restorevideo();
  fatal_dumpregs();
  (*(code *)funcptr_d41f0)();
  return;
}


// ================================================================================================
// sub_b2d28 @ 0xb2d28 [__watcall]
// ================================================================================================

void __watcall sub_b2d28(void)

{
  undefined4 in_stack_00000004;
  
  dword_d2f74 = in_stack_00000004;
  return;
}


// ================================================================================================
// sub_b2d38 @ 0xb2d38 [__watcall]
// ================================================================================================

uint __watcall sub_b2d38(undefined4 param_1,undefined4 param_2,uint unaff_EBX)

{
  code *pcVar1;
  uint uVar2;
  
  uVar2 = 0;
  dword_d3000 = dword_d3000 + -1;
  if ((dword_d3000 == 0) && (dword_d3028 != 0)) {
    if (1 < dword_d3028) {
      pcVar1 = (code *)swi(0x33);
      uVar2 = (*pcVar1)();
      dword_d3000 = dword_d3000 + 1;
      return uVar2 & 1 | unaff_EBX & 2;
    }
    pcVar1 = (code *)swi(0x33);
    (*pcVar1)();
    uVar2 = (uint)(short)unaff_EBX;
  }
  dword_d3000 = dword_d3000 + 1;
  return uVar2;
}


// ================================================================================================
// sub_b2d74 @ 0xb2d74 [__watcall]
// ================================================================================================

void __watcall sub_b2d74(void)

{
  code *pcVar1;
  
  if (dword_d3028 != 0) {
    pcVar1 = (code *)swi(0x33);
    (*pcVar1)();
  }
  return;
}


// ================================================================================================
// sub_b2d94 @ 0xb2d94 [__watcall]
// ================================================================================================

void __watcall sub_b2d94(void)

{
  code *pcVar1;
  
  if (dword_d3028 != 0) {
    pcVar1 = (code *)swi(0x33);
    (*pcVar1)();
  }
  return;
}


// ================================================================================================
// setmousepos @ 0xb2db4 [__cdecl]
// ================================================================================================

void setmousepos(undefined4 param_1,undefined4 param_2)

{
  dword_d302c = param_1;
  dword_d3030 = param_2;
  return;
}


// ================================================================================================
// getmouse @ 0xb2dca [__cdecl]
// ================================================================================================

void getmouse(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  
  uVar1 = readmouse();
  *param_1 = uVar1;
  *param_2 = dword_d302c;
  *param_3 = dword_d3030;
  return;
}


// ================================================================================================
// sub_b2def @ 0xb2def [__watcall]
// ================================================================================================

void __watcall sub_b2def(void)

{
  undefined4 in_stack_00000004;
  undefined4 in_stack_00000008;
  
  dword_d2fec = in_stack_00000004;
  dword_d2ff4 = in_stack_00000008;
  return;
}


// ================================================================================================
// sub_b2e05 @ 0xb2e05 [__watcall]
// ================================================================================================

void __watcall sub_b2e05(void)

{
  undefined4 in_stack_00000004;
  undefined4 in_stack_00000008;
  
  dword_d2ff0 = in_stack_00000004;
  dword_d2ff8 = in_stack_00000008;
  return;
}


// ================================================================================================
// setmouselimits @ 0xb2e1b [__cdecl]
// ================================================================================================

void setmouselimits(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  dword_d2fec = param_1;
  dword_d2ff0 = param_2;
  dword_d2ff4 = param_3;
  dword_d2ff8 = param_4;
  return;
}


// ================================================================================================
// readmouse @ 0xb2e43 [__watcall]
// ================================================================================================

undefined4 __watcall readmouse(void)

{
  code *pcVar1;
  short extraout_CX;
  uint uVar2;
  short extraout_DX;
  
  dword_d3000 = dword_d3000 + -1;
  if ((dword_d3000 == 0) && (dword_d3028 != 0)) {
    pcVar1 = (code *)swi(0x33);
    (*pcVar1)();
    uVar2 = (int)extraout_CX + dword_d302c * 2 + (uint)CARRY4(dword_d2ffc,dword_d2ffc);
    dword_d302c = (int)uVar2 >> 1;
    dword_d2ffc = dword_d2ffc & 0x7fffffff | (uint)((uVar2 & 1) != 0) << 0x1f;
    dword_d3030 = extraout_DX + dword_d3030;
    if (dword_d302c < dword_d2fec) {
      dword_d2ffc = 0;
      dword_d302c = dword_d2fec;
    }
    if (dword_d2ff4 <= dword_d302c) {
      dword_d302c = dword_d2ff4 + -1;
      dword_d2ffc = 0;
    }
    if (dword_d3030 < dword_d2ff0) {
      dword_d3030 = dword_d2ff0;
    }
    if (dword_d2ff8 <= dword_d3030) {
      dword_d3030 = dword_d2ff8 + -1;
    }
    dword_d3000 = dword_d3000 + 1;
    dword_d3034 = sub_b2d38();
    dword_d3000 = dword_d3000 + -1;
  }
  dword_d3000 = dword_d3000 + 1;
  return dword_d3034;
}


// ================================================================================================
// sub_b2ef6 @ 0xb2ef6 [__watcall]
// ================================================================================================

void __watcall sub_b2ef6(void)

{
  dword_d3038 = dword_d3038 + 1;
  return;
}


// ================================================================================================
// sub_b2efd @ 0xb2efd [__watcall]
// ================================================================================================

void __watcall sub_b2efd(void)

{
  dword_d3038 = dword_d3038 + -1;
  return;
}


// ================================================================================================
// sub_b2f04 @ 0xb2f04 [__watcall]
// ================================================================================================

undefined8 __watcall sub_b2f04(void)

{
  code *pcVar1;
  undefined4 unaff_ECX;
  undefined4 unaff_retaddr;
  
  pcVar1 = (code *)swi(0x33);
  (*pcVar1)();
  return CONCAT44(unaff_ECX,unaff_retaddr);
}


// ================================================================================================
// initmouse @ 0xb2f22 [__watcall]
// ================================================================================================

int __watcall initmouse(undefined4 param_1,undefined4 param_2,undefined2 unaff_BX)

{
  code *pcVar1;
  short sVar2;
  undefined2 extraout_CX;
  undefined2 extraout_DX;
  undefined *puVar3;
  
  dword_d3028 = 0;
  dword_d3038 = 0;
  dword_d303c = 0;
  pcVar1 = (code *)swi(0x33);
  sVar2 = (*pcVar1)();
  if (sVar2 != 0) {
    dword_d3028 = dword_d3028 + 1;
    puVar3 = &stack0x00000004;
    if (dword_d301c != 0) {
      dword_d303c = 2;
      pcVar1 = (code *)swi(0x33);
      sVar2 = (*pcVar1)();
      puVar3 = &stack0x00000008;
      if (sVar2 == 0) {
        dword_d3028 = 2;
        puVar3 = &stack0x00000008;
      }
    }
    *(uint *)(puVar3 + -4) = dword_d3048;
    *(uint *)(puVar3 + -8) = dword_d3044;
    *(undefined4 *)(puVar3 + -0xc) = 0;
    *(undefined4 *)(puVar3 + -0x10) = 0;
    *(undefined4 *)(puVar3 + -0x14) = 0xb2f91;
    setmouselimits();
    dword_d302c = dword_d3048 >> 2;
    dword_d3030 = dword_d3044 >> 2;
    pcVar1 = (code *)swi(0x33);
    (*pcVar1)();
    *(undefined4 *)(puVar3 + -0x10) = 0x40;
    *(undefined4 *)(puVar3 + -0x14) = 0x20;
    *(undefined4 *)(puVar3 + -0x18) = 0x20;
    *(undefined4 *)(puVar3 + -0x1c) = 0xb2fd1;
    word_d3004 = unaff_BX;
    word_d3006 = extraout_CX;
    word_d3008 = extraout_DX;
    sub_b2d74();
    funcptr_d306c = sub_b2efd;
    funcptr_d3070 = sub_b2efd;
    funcptr_d3074 = sub_b2ef6;
    mouse_update_callback = readmouse;
    *(code **)(puVar3 + -0x1c) = sub_b2f04;
    *(undefined4 *)(puVar3 + -0x20) = 0xb3003;
    sub_b3454();
  }
  return dword_d3028;
}


// ================================================================================================
// sub_b300c @ 0xb300c [__watcall]
// ================================================================================================

undefined4 __watcall sub_b300c(void)

{
  return 0;
}


// ================================================================================================
// sub_b3010 @ 0xb3010 [__watcall]
// ================================================================================================

void __watcall sub_b3010(void)

{
  sub_902a0();
  (*dword_d3096)();
  return;
}


// ================================================================================================
// sub_b3036 @ 0xb3036 [__cdecl]
// ================================================================================================

void sub_b3036(undefined4 param_1)

{
  undefined2 in_DX;
  undefined2 in_CS;
  undefined6 uVar1;
  
  dword_d3096 = param_1;
  word_d309a = in_CS;
  if (word_d3094 == 0) {
    uVar1 = sub_9864c(in_CS,in_DX,0x24);
    word_d3094 = (short)((uint6)uVar1 >> 0x20);
    dword_d3090 = (undefined4)uVar1;
    sub_98664(sub_b3010,in_CS,0x24);
    sub_b3454(sub_b308b);
  }
  return;
}


// ================================================================================================
// sub_b308b @ 0xb308b [__watcall]
// ================================================================================================

undefined8 __watcall sub_b308b(undefined4 param_1,undefined4 unaff_EDX)

{
  if (word_d3094 != 0) {
    sub_98664(dword_d3090,word_d3094,0x24);
    word_d3094 = 0;
  }
  return CONCAT44(unaff_EDX,param_1);
}


// ================================================================================================
// locateshape @ 0xb30b4 [__cdecl]
// ================================================================================================

int locateshape(int param_1,int *param_2)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  
  iVar2 = *(int *)(param_1 + 8);
  piVar1 = (int *)(param_1 + 0x10);
  if (0 < iVar2) {
    do {
      piVar3 = piVar1;
      iVar2 = iVar2 + -1;
      piVar1 = piVar3 + 2;
    } while (iVar2 != 0 && *param_2 != *piVar3);
    if (*param_2 == *piVar3) {
      return piVar3[1] + param_1;
    }
  }
  fatalerror("locateshape - \'%-4.4s\' SHAPE NOT FOUND\r\n",param_2);
  return 0;
}


// ================================================================================================
// sub_b30bb @ 0xb30bb [__cdecl]
// ================================================================================================

/* WARNING: Removing unreachable block (ram,0x000b30e7) */

int sub_b30bb(int param_1,int *param_2)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  
  iVar2 = *(int *)(param_1 + 8);
  piVar1 = (int *)(param_1 + 0x10);
  if (0 < iVar2) {
    do {
      piVar3 = piVar1;
      iVar2 = iVar2 + -1;
      piVar1 = piVar3 + 2;
    } while (iVar2 != 0 && *param_2 != *piVar3);
    if (*param_2 == *piVar3) {
      return piVar3[1] + param_1;
    }
  }
  return 0;
}


// ================================================================================================
// joy_detect @ 0xb30f4 [__watcall]
// ================================================================================================

void __watcall joy_detect(void)

{
  byte bVar1;
  ushort uVar2;
  int iVar4;
  uint uVar3;
  
  iVar4 = 10000;
  dword_d4164 = 0;
  dword_d4158 = 0;
  dword_d415c = 0;
  dword_d4160 = 0;
  out(0x201,0);
  while( true ) {
    bVar1 = in(0x201);
    uVar3 = (uint)bVar1;
    iVar4 = iVar4 + -1;
    if (iVar4 == 0 || (byte_d416a & bVar1) == 0) break;
    dword_d4158 = dword_d4158 + (uint)(bVar1 & 1);
    dword_d415c = dword_d415c + (uint)(bVar1 >> 1 & 1);
    dword_d4160 = dword_d4160 + (uint)(bVar1 >> 2 & 1);
    dword_d4164 = dword_d4164 + (uint)(bVar1 >> 3 & 1);
  }
  if ((short)iVar4 == 0) {
    uVar2 = CONCAT11(~bVar1,bVar1) & 0xfff;
    uVar3 = (uint)uVar2;
    byte_d416a = (byte)(uVar2 >> 8);
  }
  byte_d4168 = (byte)(uVar3 >> 4) & 0xf;
  return;
}


// ================================================================================================
// sub_b3168 @ 0xb3168 [__watcall]
// ================================================================================================

byte __watcall sub_b3168(void)

{
  int iVar1;
  int iVar2;
  byte bVar3;
  byte bVar4;
  int iVar5;
  uint uVar6;
  
  iVar2 = dword_d41a3;
  iVar1 = dword_d4187;
  byte_d4176 = 0;
  if ((dword_d3040 & 1) == 0) {
    byte_d4176 = 0;
    return 0;
  }
  bVar3 = in(0x201);
  byte_d4175 = bVar3 & 0x30;
  bVar3 = 3;
  dword_d416c = 0x50;
  dword_d4170 = 0x50;
  out(0x201,byte_d4175);
  iVar5 = 0x14;
  do {
    iVar5 = iVar5 + -1;
  } while (iVar5 != 0);
  uVar6 = 0;
  do {
    while( true ) {
      bVar4 = in(0x201);
      bVar4 = bVar4 & bVar3 ^ bVar3;
      if (bVar4 == 0) break;
      if ((((bVar4 & 1) != 0) && (bVar3 = bVar3 & 2, dword_d416c = uVar6, bVar3 == 0)) ||
         (((bVar4 & 2) != 0 && (bVar3 = bVar3 & 1, dword_d4170 = uVar6, bVar3 == 0))))
      goto LAB_000b31db;
    }
    uVar6 = uVar6 + 1;
  } while ((int)uVar6 < 4000);
LAB_000b31db:
  if ((int)dword_d416c < (int)dword_d4177) {
    dword_d4187 = dword_d4187 + -1;
    if (dword_d4187 == 0 || iVar1 < 1) {
      dword_d4177 = dword_d417b;
LAB_000b3219:
      uVar6 = dword_d417f - dword_d4177;
      if (uVar6 != 0 && (int)dword_d4177 <= (int)dword_d417f) {
        dword_d41af = (undefined4)(0x4000 / (ulonglong)uVar6);
      }
      dword_d418f = (uVar6 >> 1) + dword_d4177 + (uVar6 >> 2);
      dword_d418b = dword_d418f + (uVar6 >> 2) * -2;
LAB_000b3285:
      dword_d4187 = 0x14;
      dword_d4183 = 20000;
      dword_d417b = 0;
    }
    else if ((int)dword_d417b <= (int)dword_d416c) {
      dword_d417b = dword_d416c;
    }
  }
  else {
    if ((int)dword_d416c <= (int)dword_d417f) goto LAB_000b3285;
    dword_d4187 = dword_d4187 + -1;
    if (dword_d4187 == 0 || iVar1 < 1) {
      dword_d417f = dword_d4183;
      goto LAB_000b3219;
    }
    if ((int)dword_d416c < (int)dword_d4183) {
      dword_d4183 = dword_d416c;
    }
  }
  if ((int)dword_d416c < dword_d418b) {
    byte_d4176 = 8;
  }
  else if (dword_d418f <= (int)dword_d416c) {
    byte_d4176 = 4;
  }
  if (dword_d4170 < dword_d4193) {
    dword_d41a3 = dword_d41a3 + -1;
    if (dword_d41a3 != 0 && 0 < iVar2) {
      if ((int)dword_d4197 <= (int)dword_d4170) {
        dword_d4197 = dword_d4170;
      }
      goto LAB_000b3391;
    }
    dword_d4193 = dword_d4197;
LAB_000b32fb:
    uVar6 = dword_d419b - dword_d4193;
    if (uVar6 != 0 && (int)dword_d4193 <= (int)dword_d419b) {
      dword_d41b3 = (undefined4)(0x4000 / (ulonglong)uVar6);
    }
    dword_d41ab = (uVar6 >> 1) + dword_d4193 + (uVar6 >> 2);
    dword_d41a7 = dword_d41ab + (uVar6 >> 2) * -2;
  }
  else if ((int)dword_d419b < (int)dword_d4170) {
    dword_d41a3 = dword_d41a3 + -1;
    if (dword_d41a3 != 0) {
      if ((int)dword_d4170 < (int)dword_d419f) {
        dword_d419f = dword_d4170;
      }
      goto LAB_000b3391;
    }
    dword_d419b = dword_d419f;
    goto LAB_000b32fb;
  }
  dword_d41a3 = 0x14;
  dword_d419f = 20000;
  dword_d4197 = 0;
LAB_000b3391:
  if (dword_d4170 < dword_d41a7) {
    byte_d4176 = byte_d4176 | 1;
  }
  else if (dword_d41ab <= dword_d4170) {
    byte_d4176 = byte_d4176 | 2;
  }
  bVar3 = in(0x201);
  if ((bVar3 & 0x30) == byte_d4175) {
    byte_d4174 = bVar3 & 0x30 ^ 0x30;
  }
  byte_d4176 = byte_d4176 | byte_d4174;
  return byte_d4176;
}


// ================================================================================================
// joy_init @ 0xb33db [__cdecl]
// ================================================================================================

void joy_init(void)

{
  dword_d3040 = 1;
  dword_d4177 = 0x50;
  dword_d417f = 0;
  dword_d4193 = 0x50;
  dword_d419b = 0;
  return;
}


// ================================================================================================
// sub_b340b @ 0xb340b [__cdecl]
// ================================================================================================

undefined sub_b340b(uint param_1)

{
  return (&unk_d41b7)[param_1 & 0xf];
}


// ================================================================================================
// sub_b3421 @ 0xb3421 [__watcall]
// ================================================================================================

undefined8 __watcall sub_b3421(void)

{
  uint uVar1;
  
  uVar1 = dword_d416c - dword_d4177;
  if (dword_d416c < dword_d4177) {
    uVar1 = 0;
  }
  return CONCAT44((int)((ulonglong)uVar1 * (ulonglong)dword_d41af >> 0x20),
                  (int)((ulonglong)uVar1 * (ulonglong)dword_d41af) + -0x1f);
}


// ================================================================================================
// sub_b343a @ 0xb343a [__watcall]
// ================================================================================================

undefined8 __watcall sub_b343a(void)

{
  uint uVar1;
  
  uVar1 = dword_d4170 - dword_d4193;
  if (dword_d4170 < dword_d4193) {
    uVar1 = 0;
  }
  return CONCAT44((int)((ulonglong)uVar1 * (ulonglong)dword_d41b3 >> 0x20),
                  (int)((ulonglong)uVar1 * (ulonglong)dword_d41b3) + -0x1f);
}


// ================================================================================================
// sub_b3454 @ 0xb3454 [__cdecl]
// ================================================================================================

void sub_b3454(undefined4 param_1)

{
  sub_99bf6(param_1);
  return;
}


// ================================================================================================
// sub_b345d @ 0xb345d [__watcall] noreturn
// ================================================================================================

void __watcall sub_b345d(void)

{
                    /* WARNING: Subroutine does not return */
  exit(0);
}


// ================================================================================================
// joy_read @ 0xb3464 [__watcall]
// ================================================================================================

undefined2 __watcall joy_read(undefined4 param_1,undefined4 param_2,undefined4 unaff_EBX)

{
  byte bVar1;
  byte bVar2;
  int iVar3;
  uint uVar4;
  
  if (dword_d3040 == 0) {
    return 0;
  }
  byte_d4245 = 0;
  byte_d4246 = 0;
  byte_d4244 = in(0x201);
  bVar2 = (&unk_d4280)[CONCAT22((short)((uint)unaff_EBX >> 0x10),(ushort)dword_d3040)];
  dword_d423c = 0x50;
  dword_d4240 = 0x50;
  dword_d41fc = 0x50;
  dword_d4200 = 0x50;
  out(0x201,0x50);
  iVar3 = 0x14;
  do {
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  uVar4 = 0;
  do {
    while( true ) {
      bVar1 = in(0x201);
      bVar1 = bVar1 & bVar2 ^ bVar2;
      if (bVar1 == 0) break;
      if ((((((bVar1 & 1) != 0) && (bVar2 = bVar2 & 0xe, dword_d423c = uVar4, bVar2 == 0)) ||
           (((bVar1 & 2) != 0 && (bVar2 = bVar2 & 0xd, dword_d4240 = uVar4, bVar2 == 0)))) ||
          (((bVar1 & 4) != 0 && (bVar2 = bVar2 & 0xb, dword_d41fc = uVar4, bVar2 == 0)))) ||
         (((bVar1 & 8) != 0 && (bVar2 = bVar2 & 7, dword_d4200 = uVar4, bVar2 == 0))))
      goto LAB_000b3509;
    }
    uVar4 = uVar4 + 1;
  } while ((int)uVar4 < 4000);
LAB_000b3509:
  if ((dword_d3040 & 1) != 0) {
    if ((int)dword_d423c < (int)dword_d4248) {
      dword_d4248 = dword_d423c;
LAB_000b3532:
      uVar4 = dword_d424c - dword_d4248;
      if (uVar4 != 0 && (int)dword_d4248 <= (int)dword_d424c) {
        dword_d4278 = (undefined4)(0x4000 / (ulonglong)uVar4);
      }
      dword_d425c = (uVar4 >> 1) + dword_d4248 + (uVar4 >> 2);
      dword_d4258 = dword_d425c + (uVar4 >> 2) * -2;
LAB_000b35a1:
      dword_d4254 = 8;
      dword_d4250 = 20000;
    }
    else {
      if ((int)dword_d423c <= (int)dword_d424c) goto LAB_000b35a1;
      dword_d4254 = dword_d4254 + -1;
      if (dword_d4254 == 0) {
        dword_d424c = dword_d4250;
        goto LAB_000b3532;
      }
      if ((int)dword_d423c < (int)dword_d4250) {
        dword_d4250 = dword_d423c;
      }
    }
    if ((int)dword_d423c < dword_d4258) {
      byte_d4245 = 8;
    }
    else if (dword_d425c <= (int)dword_d423c) {
      byte_d4245 = 4;
    }
    if (dword_d4240 < dword_d4260) {
      dword_d4260 = dword_d4240;
LAB_000b35e6:
      uVar4 = dword_d4264 - dword_d4260;
      if (uVar4 != 0 && (int)dword_d4260 <= (int)dword_d4264) {
        dword_d427c = (undefined4)(0x4000 / (ulonglong)uVar4);
      }
      dword_d4274 = (uVar4 >> 1) + dword_d4260 + (uVar4 >> 2);
      dword_d4270 = dword_d4274 + (uVar4 >> 2) * -2;
LAB_000b365e:
      dword_d426c = 8;
      dword_d4268 = 20000;
    }
    else {
      if ((int)dword_d4240 <= (int)dword_d4264) goto LAB_000b365e;
      dword_d426c = dword_d426c + -1;
      if (dword_d426c == 0) {
        dword_d4264 = dword_d4268;
        goto LAB_000b35e6;
      }
      if ((int)dword_d4240 < (int)dword_d4268) {
        dword_d4268 = dword_d4240;
      }
    }
    if (dword_d4240 < dword_d4270) {
      byte_d4245 = byte_d4245 | 1;
    }
    else if (dword_d4274 <= dword_d4240) {
      byte_d4245 = byte_d4245 | 2;
    }
    bVar2 = in(0x201);
    byte_d4245 = byte_d4245 | bVar2 & byte_d4244 & 0x30 ^ 0x30;
  }
  if ((dword_d3040 & 2) == 0) goto LAB_000b3838;
  if ((int)dword_d41fc < (int)dword_d4204) {
    dword_d4204 = dword_d41fc;
LAB_000b36cd:
    uVar4 = dword_d4208 - dword_d4204;
    if (uVar4 != 0 && (int)dword_d4204 <= (int)dword_d4208) {
      dword_d4234 = (undefined4)(0x4000 / (ulonglong)uVar4);
    }
    dword_d4218 = (uVar4 >> 1) + dword_d4204 + (uVar4 >> 2);
    dword_d4214 = dword_d4218 + (uVar4 >> 2) * -2;
LAB_000b373c:
    dword_d4210 = 8;
    dword_d420c = 20000;
  }
  else {
    if ((int)dword_d41fc <= (int)dword_d4208) goto LAB_000b373c;
    dword_d4210 = dword_d4210 + -1;
    if (dword_d4210 == 0) {
      dword_d4208 = dword_d420c;
      goto LAB_000b36cd;
    }
    if ((int)dword_d41fc < (int)dword_d420c) {
      dword_d420c = dword_d41fc;
    }
  }
  if ((int)dword_d41fc < dword_d4214) {
    byte_d4246 = 8;
  }
  else if (dword_d4218 <= (int)dword_d41fc) {
    byte_d4246 = 4;
  }
  if (dword_d4200 < dword_d421c) {
    dword_d421c = dword_d4200;
LAB_000b3781:
    uVar4 = dword_d4220 - dword_d421c;
    if (uVar4 != 0 && (int)dword_d421c <= (int)dword_d4220) {
      dword_d4238 = (undefined4)(0x4000 / (ulonglong)uVar4);
    }
    dword_d4230 = (uVar4 >> 1) + dword_d421c + (uVar4 >> 2);
    dword_d422c = dword_d4230 + (uVar4 >> 2) * -2;
LAB_000b37f9:
    dword_d4228 = 8;
    dword_d4224 = 20000;
  }
  else {
    if ((int)dword_d4200 <= (int)dword_d4220) goto LAB_000b37f9;
    dword_d4228 = dword_d4228 + -1;
    if (dword_d4228 == 0) {
      dword_d4220 = dword_d4224;
      goto LAB_000b3781;
    }
    if ((int)dword_d4200 < (int)dword_d4224) {
      dword_d4224 = dword_d4200;
    }
  }
  if (dword_d4200 < dword_d422c) {
    byte_d4246 = byte_d4246 | 1;
  }
  else if (dword_d4230 <= dword_d4200) {
    byte_d4246 = byte_d4246 | 2;
  }
  bVar2 = in(0x201);
  byte_d4246 = byte_d4246 | (bVar2 & byte_d4244 & 0xc0 ^ 0xc0) >> 2;
LAB_000b3838:
  return CONCAT11(byte_d4246,byte_d4245);
}


// ================================================================================================
// sub_b384e @ 0xb384e [__watcall]
// ================================================================================================

void __watcall sub_b384e(void)

{
  dword_d3040 = dword_d3040 | 1;
  dword_d4248 = 0x50;
  dword_d424c = 0;
  dword_d4260 = 0x50;
  dword_d4264 = 0;
  return;
}


// ================================================================================================
// sub_b387e @ 0xb387e [__watcall]
// ================================================================================================

void __watcall sub_b387e(void)

{
  dword_d3040 = dword_d3040 | 2;
  dword_d4204 = 0x50;
  dword_d4208 = 0;
  dword_d421c = 0x50;
  dword_d4220 = 0;
  return;
}


// ================================================================================================
// sub_b38ae @ 0xb38ae [__watcall]
// ================================================================================================

int __watcall sub_b38ae(void)

{
  uint uVar1;
  
  uVar1 = dword_d423c - dword_d4248;
  if (dword_d423c < dword_d4248) {
    uVar1 = 0;
  }
  return (int)(short)(CONCAT11((char)((ulonglong)uVar1 * (ulonglong)dword_d4278 >> 0x20),
                               (char)((ulonglong)uVar1 * (ulonglong)dword_d4278 >> 8)) + -0x1f);
}


// ================================================================================================
// sub_b38cd @ 0xb38cd [__watcall]
// ================================================================================================

int __watcall sub_b38cd(void)

{
  uint uVar1;
  
  uVar1 = dword_d4240 - dword_d4260;
  if (dword_d4240 < dword_d4260) {
    uVar1 = 0;
  }
  return (int)(short)(CONCAT11((char)((ulonglong)uVar1 * (ulonglong)dword_d427c >> 0x20),
                               (char)((ulonglong)uVar1 * (ulonglong)dword_d427c >> 8)) + -0x1f);
}


// ================================================================================================
// sub_b38ec @ 0xb38ec [__watcall]
// ================================================================================================

int __watcall sub_b38ec(void)

{
  uint uVar1;
  
  uVar1 = dword_d41fc - dword_d4204;
  if (dword_d41fc < dword_d4204) {
    uVar1 = 0;
  }
  return (int)(short)(CONCAT11((char)((ulonglong)uVar1 * (ulonglong)dword_d4234 >> 0x20),
                               (char)((ulonglong)uVar1 * (ulonglong)dword_d4234 >> 8)) + -0x1f);
}


// ================================================================================================
// sub_b390b @ 0xb390b [__watcall]
// ================================================================================================

int __watcall sub_b390b(void)

{
  uint uVar1;
  
  uVar1 = dword_d4200 - dword_d421c;
  if (dword_d4200 < dword_d421c) {
    uVar1 = 0;
  }
  return (int)(short)(CONCAT11((char)((ulonglong)uVar1 * (ulonglong)dword_d4238 >> 0x20),
                               (char)((ulonglong)uVar1 * (ulonglong)dword_d4238 >> 8)) + -0x1f);
}


// ================================================================================================
// clearclip @ 0xb392c [__cdecl]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void clearclip(undefined4 param_1)

{
  fillrect(dword_d30ac,dword_d30b0,_dword_d30b4 - dword_d30ac,dword_d30b8 - dword_d30b0,param_1);
  return;
}


// ================================================================================================
// getticks @ 0xb395c [__watcall]
// ================================================================================================

undefined4 __watcall getticks(void)

{
  return dword_d2fdc;
}


// ================================================================================================
// sub_b3962 @ 0xb3962 [__cdecl]
// ================================================================================================

int sub_b3962(int param_1)

{
  return dword_d2fdc - param_1;
}


// ================================================================================================
// ticks_elapsed @ 0xb396e [__watcall]
// ================================================================================================

int __watcall ticks_elapsed(void)

{
  int iVar1;
  
  iVar1 = dword_d4298;
  dword_d4298 = dword_d2fdc;
  return dword_d2fdc - iVar1;
}


