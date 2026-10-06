// Decompiled by Ghidra from hockey.elf (via ledisasm ELF export)
// This is machine generated pseudo-C meant as a reference for porting, it does not compile as is.
#include "prototypes.h"

// ================================================================================================
// sub_b3981 @ 0xb3981 [__watcall]
// ================================================================================================

void __watcall sub_b3981(void)

{
  dword_d2fdc = 0;
  return;
}


// ================================================================================================
// settimeout @ 0xb3989 [__cdecl]
// ================================================================================================

void settimeout(int param_1)

{
  dword_d4294 = param_1 + dword_d2fdc;
  return;
}


// ================================================================================================
// waittimeout @ 0xb3999 [__watcall]
// ================================================================================================

void __watcall waittimeout(void)

{
  do {
  } while (dword_d2fdc - dword_d4294 < 0);
  return;
}


// ================================================================================================
// sub_b39a7 @ 0xb39a7 [__watcall]
// ================================================================================================

bool __watcall sub_b39a7(void)

{
  return dword_d4294 <= dword_d2fdc;
}


// ================================================================================================
// sub_b39b7 @ 0xb39b7 [__cdecl]
// ================================================================================================

void sub_b39b7(int param_1)

{
  do {
  } while (0 < param_1);
  return;
}


// ================================================================================================
// sub_b39d0 @ 0xb39d0 [__watcall]
// ================================================================================================

ushort __watcall sub_b39d0(void)

{
  ushort uVar1;
  undefined in_ZF;
  
  (*(code *)funcptr_d2c84)();
  if ((bool)in_ZF) {
    return 0;
  }
  uVar1 = (*(code *)funcptr_d2c84)();
  if ((char)uVar1 != '\0') {
    uVar1 = uVar1 & 0xff;
  }
  return uVar1;
}


// ================================================================================================
// getkey @ 0xb39ed [__watcall]
// ================================================================================================

void __watcall getkey(void)

{
                    /* WARNING: Could not recover jumptable at 0x000b39ed. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)funcptr_d42a0)();
  return;
}


// ================================================================================================
// sub_b39f3 @ 0xb39f3 [__watcall]
// ================================================================================================

ushort __watcall sub_b39f3(void)

{
  ushort uVar1;
  undefined in_ZF;
  
  uVar1 = (*(code *)funcptr_d2c84)();
  if ((bool)in_ZF) {
    return 0;
  }
  if ((char)uVar1 != '\0') {
    uVar1 = uVar1 & 0xff;
  }
  return uVar1;
}


// ================================================================================================
// sub_b3a08 @ 0xb3a08 [__cdecl]
// ================================================================================================

void sub_b3a08(undefined *param_1)

{
  funcptr_d42a0 = param_1;
  return;
}


// ================================================================================================
// sub_b3a12 @ 0xb3a12 [__watcall]
// ================================================================================================

undefined * __watcall sub_b3a12(void)

{
  return funcptr_d42a0;
}


// ================================================================================================
// waitkey @ 0xb3a18 [__watcall]
// ================================================================================================

void __watcall waitkey(void)

{
  short sVar1;
  
  do {
    sVar1 = (*(code *)funcptr_d42a0)();
  } while (sVar1 == 0);
  return;
}


// ================================================================================================
// flushkeys @ 0xb3a24 [__watcall]
// ================================================================================================

void __watcall flushkeys(void)

{
  short sVar1;
  
  do {
    sVar1 = sub_b39d0();
  } while (sVar1 != 0);
  return;
}


// ================================================================================================
// sub_b3a2f @ 0xb3a2f [__watcall]
// ================================================================================================

short __watcall sub_b3a2f(void)

{
  short sVar1;
  
  do {
    sVar1 = (*(code *)funcptr_d42a0)();
    if (sVar1 != 0) {
      return sVar1;
    }
    sVar1 = sub_b39a7();
  } while (sVar1 == 0);
  return 0;
}


// ================================================================================================
// sub_b3a48 @ 0xb3a48 [__watcall]
// ================================================================================================

int __watcall sub_b3a48(void)

{
  int iVar1;
  int iVar2;
  int in_stack_00000004;
  
  iVar1 = getticks();
  do {
    iVar2 = getkey(0);
    if (iVar2 != 0) {
      return iVar2;
    }
    iVar2 = getticks();
  } while (iVar2 - (iVar1 + in_stack_00000004) < 0);
  return 0;
}


// ================================================================================================
// sub_b3a72 @ 0xb3a72 [__watcall]
// ================================================================================================

void __watcall sub_b3a72(void)

{
  code *pcVar1;
  
  pcVar1 = (code *)swi(0x16);
  (*pcVar1)();
  return;
}


// ================================================================================================
// sub_b3a88 @ 0xb3a88 [__cdecl]
// ================================================================================================

void sub_b3a88(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = &dword_d30a4;
  for (iVar1 = 0x18; iVar1 != 0; iVar1 = iVar1 + -1) {
    *param_1 = *puVar2;
    puVar2 = puVar2 + 1;
    param_1 = param_1 + 1;
  }
  return;
}


// ================================================================================================
// sub_b3aa1 @ 0xb3aa1 [__cdecl]
// ================================================================================================

void sub_b3aa1(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = &dword_d30a4;
  for (iVar1 = 0x18; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = *param_1;
    param_1 = param_1 + 1;
    puVar2 = puVar2 + 1;
  }
  return;
}


// ================================================================================================
// sub_b3abc @ 0xb3abc [__cdecl]
// ================================================================================================

void sub_b3abc(undefined4 *param_1,undefined4 *param_2,uint param_3)

{
  uint uVar1;
  undefined4 *puVar2;
  undefined *puVar3;
  undefined4 *puVar4;
  undefined *puVar5;
  
  if (param_2 < param_1) {
    for (uVar1 = param_3 >> 2; uVar1 != 0; uVar1 = uVar1 - 1) {
      *param_2 = *param_1;
      param_1 = param_1 + 1;
      param_2 = param_2 + 1;
    }
    for (param_3 = param_3 & 3; param_3 != 0; param_3 = param_3 - 1) {
      *(undefined *)param_2 = *(undefined *)param_1;
      param_1 = (undefined4 *)((int)param_1 + 1);
      param_2 = (undefined4 *)((int)param_2 + 1);
    }
    return;
  }
  puVar2 = (undefined4 *)((param_3 - 4) + (int)param_1);
  puVar4 = (undefined4 *)((param_3 - 4) + (int)param_2);
  for (uVar1 = param_3 >> 2; uVar1 != 0; uVar1 = uVar1 - 1) {
    *puVar4 = *puVar2;
    puVar2 = puVar2 + -1;
    puVar4 = puVar4 + -1;
  }
  puVar3 = (undefined *)((int)puVar2 + 3);
  puVar5 = (undefined *)((int)puVar4 + 3);
  for (param_3 = param_3 & 3; param_3 != 0; param_3 = param_3 - 1) {
    *puVar5 = *puVar3;
    puVar3 = puVar3 + -1;
    puVar5 = puVar5 + -1;
  }
  return;
}


// ================================================================================================
// sub_b3b00 @ 0xb3b00 [__watcall]
// ================================================================================================

undefined8 __watcall sub_b3b00(void)

{
  code *pcVar1;
  undefined2 uVar2;
  undefined4 unaff_ECX;
  undefined2 extraout_DX;
  
  pcVar1 = (code *)swi(0x21);
  uVar2 = (*pcVar1)();
  return CONCAT44(unaff_ECX,CONCAT22(extraout_DX,uVar2));
}


// ================================================================================================
// openhandle @ 0xb3b19 [__cdecl]
// ================================================================================================

void openhandle(undefined4 param_1,undefined4 *param_2,int *param_3,undefined4 *param_4,int param_5)

{
  code *pcVar1;
  undefined4 uVar2;
  int iVar3;
  int *piVar4;
  bool bVar5;
  int local_8;
  
  local_8 = param_5;
  *param_2 = 0;
  bVar5 = false;
  pcVar1 = (code *)swi(0x21);
  uVar2 = (*pcVar1)();
  if (!bVar5) {
    *param_2 = uVar2;
    bVar5 = false;
    uVar2 = sub_b3b00(0x4202,0,uVar2);
    if (!bVar5) {
      *param_4 = uVar2;
      bVar5 = false;
      sub_b3b00(0x4200,0,*param_2);
      if (!bVar5) {
        *param_3 = 0;
        return;
      }
    }
  }
  piVar4 = &local_8;
  if (byte_d4410 != '\0') {
    bVar5 = false;
    pcVar1 = (code *)swi(0x21);
    uVar2 = (*pcVar1)();
    piVar4 = (int *)&stack0xfffffffc;
    if (!bVar5) {
      *param_2 = uVar2;
      bVar5 = false;
      piVar4 = (int *)&stack0xfffffffc;
      if (*dword_d4438 == '\0') {
        pcVar1 = (code *)swi(0x21);
        (*pcVar1)();
        piVar4 = (int *)register0x00000010;
        if (bVar5) goto LAB_000b3c2b;
      }
      *(undefined4 *)((int)piVar4 + -4) = param_1;
      *(char **)((int)piVar4 + -8) = dword_d4438;
      *(undefined4 *)((int)piVar4 + -0xc) = 0xb3bfd;
      iVar3 = (*dword_d443c)();
      bVar5 = false;
      if (iVar3 != 0) {
        *param_3 = iVar3;
        *param_4 = *dword_d4440;
        uVar2 = *param_2;
        *(undefined4 *)((int)piVar4 + -4) = 0xb3c27;
        sub_b3b00(0x4200,iVar3,uVar2);
        if (!bVar5) {
          return;
        }
      }
    }
  }
LAB_000b3c2b:
  uVar2 = *param_2;
  *param_2 = 0;
  *(undefined4 *)((int)piVar4 + -4) = uVar2;
  *(undefined4 *)((int)piVar4 + -8) = 0xb3c3c;
  closehandle();
  if (local_8 == 0) {
    *param_4 = 0;
    *param_3 = 0;
    return;
  }
  *(undefined4 *)((int)piVar4 + -4) = param_1;
  *(char **)((int)piVar4 + -8) = aOpenhandleSFILEERROR;
  *(code **)((int)piVar4 + -0xc) = closehandle;
  fatalerror();
  *(undefined **)((int)piVar4 + -0xc) = &stack0xfffffffc;
  if (*(int *)((int)piVar4 + -4) != 0) {
    pcVar1 = (code *)swi(0x21);
    (*pcVar1)();
  }
  return;
}


// ================================================================================================
// sub_b3b2e @ 0xb3b2e [__cdecl]
// ================================================================================================

void sub_b3b2e(undefined4 param_1,undefined4 *param_2,int *param_3,undefined4 *param_4)

{
  code *pcVar1;
  undefined4 uVar2;
  int iVar3;
  int *piVar4;
  bool bVar5;
  int local_8;
  
  local_8 = 0;
  *param_2 = 0;
  bVar5 = false;
  pcVar1 = (code *)swi(0x21);
  uVar2 = (*pcVar1)();
  if (!bVar5) {
    *param_2 = uVar2;
    bVar5 = false;
    uVar2 = sub_b3b00(0x4202,0,uVar2);
    if (!bVar5) {
      *param_4 = uVar2;
      bVar5 = false;
      sub_b3b00(0x4200,0,*param_2);
      if (!bVar5) {
        *param_3 = 0;
        return;
      }
    }
  }
  piVar4 = &local_8;
  if (byte_d4410 != '\0') {
    bVar5 = false;
    pcVar1 = (code *)swi(0x21);
    uVar2 = (*pcVar1)();
    piVar4 = (int *)&stack0xfffffffc;
    if (!bVar5) {
      *param_2 = uVar2;
      bVar5 = false;
      piVar4 = (int *)&stack0xfffffffc;
      if (*dword_d4438 == '\0') {
        pcVar1 = (code *)swi(0x21);
        (*pcVar1)();
        piVar4 = (int *)register0x00000010;
        if (bVar5) goto LAB_000b3c2b;
      }
      *(undefined4 *)((int)piVar4 + -4) = param_1;
      *(char **)((int)piVar4 + -8) = dword_d4438;
      *(undefined4 *)((int)piVar4 + -0xc) = 0xb3bfd;
      iVar3 = (*dword_d443c)();
      bVar5 = false;
      if (iVar3 != 0) {
        *param_3 = iVar3;
        *param_4 = *dword_d4440;
        uVar2 = *param_2;
        *(undefined4 *)((int)piVar4 + -4) = 0xb3c27;
        sub_b3b00(0x4200,iVar3,uVar2);
        if (!bVar5) {
          return;
        }
      }
    }
  }
LAB_000b3c2b:
  uVar2 = *param_2;
  *param_2 = 0;
  *(undefined4 *)((int)piVar4 + -4) = uVar2;
  *(undefined4 *)((int)piVar4 + -8) = 0xb3c3c;
  closehandle();
  if (local_8 == 0) {
    *param_4 = 0;
    *param_3 = 0;
    return;
  }
  *(undefined4 *)((int)piVar4 + -4) = param_1;
  *(char **)((int)piVar4 + -8) = aOpenhandleSFILEERROR;
  *(code **)((int)piVar4 + -0xc) = closehandle;
  fatalerror();
  *(undefined **)((int)piVar4 + -0xc) = &stack0xfffffffc;
  if (*(int *)((int)piVar4 + -4) != 0) {
    pcVar1 = (code *)swi(0x21);
    (*pcVar1)();
  }
  return;
}


// ================================================================================================
// sub_b3b44 @ 0xb3b44 [__cdecl]
// ================================================================================================

void sub_b3b44(undefined4 param_1,undefined4 *param_2,int *param_3,undefined4 *param_4)

{
  code *pcVar1;
  undefined4 uVar2;
  int iVar3;
  int *piVar4;
  bool bVar5;
  int local_8;
  
  local_8 = 0;
  *param_2 = 0;
  bVar5 = false;
  pcVar1 = (code *)swi(0x21);
  uVar2 = (*pcVar1)();
  if (!bVar5) {
    *param_2 = uVar2;
    bVar5 = false;
    uVar2 = sub_b3b00(0x4202,0,uVar2);
    if (!bVar5) {
      *param_4 = uVar2;
      bVar5 = false;
      sub_b3b00(0x4200,0,*param_2);
      if (!bVar5) {
        *param_3 = 0;
        return;
      }
    }
  }
  piVar4 = &local_8;
  if (byte_d4410 != '\0') {
    bVar5 = false;
    pcVar1 = (code *)swi(0x21);
    uVar2 = (*pcVar1)();
    piVar4 = (int *)&stack0xfffffffc;
    if (!bVar5) {
      *param_2 = uVar2;
      bVar5 = false;
      piVar4 = (int *)&stack0xfffffffc;
      if (*dword_d4438 == '\0') {
        pcVar1 = (code *)swi(0x21);
        (*pcVar1)();
        piVar4 = (int *)register0x00000010;
        if (bVar5) goto LAB_000b3c2b;
      }
      *(undefined4 *)((int)piVar4 + -4) = param_1;
      *(char **)((int)piVar4 + -8) = dword_d4438;
      *(undefined4 *)((int)piVar4 + -0xc) = 0xb3bfd;
      iVar3 = (*dword_d443c)();
      bVar5 = false;
      if (iVar3 != 0) {
        *param_3 = iVar3;
        *param_4 = *dword_d4440;
        uVar2 = *param_2;
        *(undefined4 *)((int)piVar4 + -4) = 0xb3c27;
        sub_b3b00(0x4200,iVar3,uVar2);
        if (!bVar5) {
          return;
        }
      }
    }
  }
LAB_000b3c2b:
  uVar2 = *param_2;
  *param_2 = 0;
  *(undefined4 *)((int)piVar4 + -4) = uVar2;
  *(undefined4 *)((int)piVar4 + -8) = 0xb3c3c;
  closehandle();
  if (local_8 == 0) {
    *param_4 = 0;
    *param_3 = 0;
    return;
  }
  *(undefined4 *)((int)piVar4 + -4) = param_1;
  *(char **)((int)piVar4 + -8) = aOpenhandleSFILEERROR;
  *(code **)((int)piVar4 + -0xc) = closehandle;
  fatalerror();
  *(undefined **)((int)piVar4 + -0xc) = &stack0xfffffffc;
  if (*(int *)((int)piVar4 + -4) != 0) {
    pcVar1 = (code *)swi(0x21);
    (*pcVar1)();
  }
  return;
}


// ================================================================================================
// sub_b3b5a @ 0xb3b5a [__cdecl]
// ================================================================================================

void sub_b3b5a(undefined4 param_1,undefined4 *param_2,int *param_3,undefined4 *param_4)

{
  code *pcVar1;
  undefined4 uVar2;
  int iVar3;
  int *piVar4;
  bool bVar5;
  int local_8;
  
  local_8 = 1;
  *param_2 = 0;
  bVar5 = false;
  pcVar1 = (code *)swi(0x21);
  uVar2 = (*pcVar1)();
  if (!bVar5) {
    *param_2 = uVar2;
    bVar5 = false;
    uVar2 = sub_b3b00(0x4202,0,uVar2);
    if (!bVar5) {
      *param_4 = uVar2;
      bVar5 = false;
      sub_b3b00(0x4200,0,*param_2);
      if (!bVar5) {
        *param_3 = 0;
        return;
      }
    }
  }
  piVar4 = &local_8;
  if (byte_d4410 != '\0') {
    bVar5 = false;
    pcVar1 = (code *)swi(0x21);
    uVar2 = (*pcVar1)();
    piVar4 = (int *)&stack0xfffffffc;
    if (!bVar5) {
      *param_2 = uVar2;
      bVar5 = false;
      piVar4 = (int *)&stack0xfffffffc;
      if (*dword_d4438 == '\0') {
        pcVar1 = (code *)swi(0x21);
        (*pcVar1)();
        piVar4 = (int *)register0x00000010;
        if (bVar5) goto LAB_000b3c2b;
      }
      *(undefined4 *)((int)piVar4 + -4) = param_1;
      *(char **)((int)piVar4 + -8) = dword_d4438;
      *(undefined4 *)((int)piVar4 + -0xc) = 0xb3bfd;
      iVar3 = (*dword_d443c)();
      bVar5 = false;
      if (iVar3 != 0) {
        *param_3 = iVar3;
        *param_4 = *dword_d4440;
        uVar2 = *param_2;
        *(undefined4 *)((int)piVar4 + -4) = 0xb3c27;
        sub_b3b00(0x4200,iVar3,uVar2);
        if (!bVar5) {
          return;
        }
      }
    }
  }
LAB_000b3c2b:
  uVar2 = *param_2;
  *param_2 = 0;
  *(undefined4 *)((int)piVar4 + -4) = uVar2;
  *(undefined4 *)((int)piVar4 + -8) = 0xb3c3c;
  closehandle();
  if (local_8 == 0) {
    *param_4 = 0;
    *param_3 = 0;
    return;
  }
  *(undefined4 *)((int)piVar4 + -4) = param_1;
  *(char **)((int)piVar4 + -8) = aOpenhandleSFILEERROR;
  *(code **)((int)piVar4 + -0xc) = closehandle;
  fatalerror();
  *(undefined **)((int)piVar4 + -0xc) = &stack0xfffffffc;
  if (*(int *)((int)piVar4 + -4) != 0) {
    pcVar1 = (code *)swi(0x21);
    (*pcVar1)();
  }
  return;
}


// ================================================================================================
// closehandle @ 0xb3c60 [__cdecl]
// ================================================================================================

void closehandle(int param_1)

{
  code *pcVar1;
  
  if (param_1 != 0) {
    pcVar1 = (code *)swi(0x21);
    (*pcVar1)();
  }
  return;
}


// ================================================================================================
// sub_b3c70 @ 0xb3c70 [__cdecl]
// ================================================================================================

undefined4 sub_b3c70(undefined4 param_1,undefined4 param_2,uint param_3)

{
  uint uVar1;
  code *pcVar2;
  bool bVar3;
  
  while( true ) {
    bVar3 = param_3 < 0x4000;
    uVar1 = param_3 - 0x4000;
    if (((int)param_3 < 0x4000) &&
       (bVar3 = 0xffffbfff < uVar1, uVar1 == 0xffffc000 || SCARRY4(uVar1,0x4000) != (int)param_3 < 0
       )) break;
    pcVar2 = (code *)swi(0x21);
    (*pcVar2)();
    param_3 = uVar1;
    if (bVar3) {
      return 0;
    }
  }
  return 1;
}


// ================================================================================================
// sub_b3c74 @ 0xb3c74 [__cdecl]
// ================================================================================================

undefined4 sub_b3c74(undefined4 param_1,undefined4 param_2,uint param_3)

{
  uint uVar1;
  code *pcVar2;
  bool bVar3;
  
  while( true ) {
    bVar3 = param_3 < 0x4000;
    uVar1 = param_3 - 0x4000;
    if (((int)param_3 < 0x4000) &&
       (bVar3 = 0xffffbfff < uVar1, uVar1 == 0xffffc000 || SCARRY4(uVar1,0x4000) != (int)param_3 < 0
       )) break;
    pcVar2 = (code *)swi(0x21);
    (*pcVar2)();
    param_3 = uVar1;
    if (bVar3) {
      return 0;
    }
  }
  return 1;
}


// ================================================================================================
// seekhandle @ 0xb3cb3 [__cdecl]
// ================================================================================================

void seekhandle(undefined4 param_1,undefined4 param_2)

{
  sub_b3b00(0x4200,param_2,param_1);
  return;
}


// ================================================================================================
// sub_b3cc8 @ 0xb3cc8 [__cdecl]
// ================================================================================================

undefined1 * sub_b3cc8(char *param_1)

{
  char cVar1;
  code *pcVar2;
  undefined1 *puVar3;
  int iVar4;
  char *pcVar5;
  char *pcVar6;
  undefined in_CF;
  byte bVar7;
  
  bVar7 = 0;
  pcVar2 = (code *)swi(0x21);
  (*pcVar2)();
  pcVar2 = (code *)swi(0x21);
  (*pcVar2)();
  if ((bool)in_CF) {
    puVar3 = (undefined1 *)0x0;
  }
  else {
    dword_d44ac = &unk_d4448;
    iVar4 = 0x57;
    pcVar5 = &unk_d4448;
    do {
      cVar1 = *param_1;
      *pcVar5 = cVar1;
      if (cVar1 == '\0') break;
      if ((cVar1 == ':') || (cVar1 == '\\')) {
        dword_d44ac = pcVar5 + (uint)bVar7 * -2 + 1;
      }
      iVar4 = iVar4 + -1;
      param_1 = param_1 + (uint)bVar7 * -2 + 1;
      pcVar5 = pcVar5 + (uint)bVar7 * -2 + 1;
    } while (iVar4 != 0);
    pcVar5 = &unk_d44ce;
    pcVar6 = dword_d44ac;
    for (iVar4 = 0xd; iVar4 != 0; iVar4 = iVar4 + -1) {
      *pcVar6 = *pcVar5;
      pcVar5 = pcVar5 + 1;
      pcVar6 = pcVar6 + 1;
    }
    puVar3 = &unk_d4448;
  }
  return puVar3;
}


// ================================================================================================
// sub_b3d2a @ 0xb3d2a [__watcall]
// ================================================================================================

undefined1 * __watcall sub_b3d2a(void)

{
  code *pcVar1;
  undefined1 *puVar2;
  int iVar3;
  undefined *puVar4;
  undefined in_CF;
  
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  if ((bool)in_CF) {
    puVar2 = (undefined1 *)0x0;
  }
  else {
    puVar2 = &unk_d44ce;
    puVar4 = dword_d44ac;
    for (iVar3 = 0xd; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar4 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar4 = puVar4 + 1;
    }
    puVar2 = &unk_d4448;
  }
  return puVar2;
}


// ================================================================================================
// sub_b3d40 @ 0xb3d40 [__watcall]
// ================================================================================================

undefined4 __watcall sub_b3d40(void)

{
  return dword_d2fe0;
}


// ================================================================================================
// settimeout2 @ 0xb3d46 [__cdecl]
// ================================================================================================

void settimeout2(int param_1)

{
  dword_d4530 = param_1 + dword_d2fe0;
  return;
}


// ================================================================================================
// sub_b3d56 @ 0xb3d56 [__watcall]
// ================================================================================================

void __watcall sub_b3d56(void)

{
  do {
  } while (dword_d2fe0 - dword_d4530 < 0);
  return;
}


// ================================================================================================
// timeout2_expired @ 0xb3d64 [__watcall]
// ================================================================================================

bool __watcall timeout2_expired(void)

{
  return dword_d4530 <= dword_d2fe0;
}


// ================================================================================================
// sub_b3d74 @ 0xb3d74 [__cdecl]
// ================================================================================================

void sub_b3d74(int param_1)

{
  do {
  } while (0 < param_1);
  return;
}


// ================================================================================================
// approx_distance @ 0xb3d94 [__cdecl]
// ================================================================================================

uint approx_distance(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = sub_b49c0(param_2,param_1);
  if (iVar1 < 0) {
    iVar1 = -iVar1;
  }
  if (0x100 < iVar1) {
    iVar1 = 0x200 - iVar1;
  }
  if (iVar1 < 0x81) {
    uVar2 = sub_b4a66(iVar1);
    if (param_1 < 0) {
      param_1 = -param_1;
    }
    return (uint)(param_1 << 0x10) / uVar2;
  }
  uVar2 = sub_b4a60(iVar1);
  if (param_2 < 0) {
    param_2 = -param_2;
  }
  return (uint)(param_2 << 0x10) / uVar2;
}


// ================================================================================================
// sub_b3dfc @ 0xb3dfc [__watcall]
// ================================================================================================

void __watcall
sub_b3dfc(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX,
         char *param_5,char *param_6)

{
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  undefined4 unaff_retaddr;
  
  dword_d4f2c = unaff_EBX;
  dword_d4f30 = unaff_ECX;
  dword_d4f34 = unaff_EDX;
  dword_d4f38 = unaff_ESI;
  dword_d4f3c = unaff_EDI;
  dword_d4f40 = unaff_retaddr;
  sprintf(param_5,param_6);
  return;
}


// ================================================================================================
// fatal_dumpregs @ 0xb3e4a [__watcall]
// ================================================================================================

void __watcall
fatal_dumpregs(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX,
              char *param_5)

{
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  undefined4 unaff_retaddr;
  
  dword_d4f2c = unaff_EBX;
  dword_d4f30 = unaff_ECX;
  dword_d4f34 = unaff_EDX;
  dword_d4f38 = unaff_ESI;
  dword_d4f3c = unaff_EDI;
  dword_d4f40 = unaff_retaddr;
  printf(param_5);
  return;
}


// ================================================================================================
// sub_b3e98 @ 0xb3e98 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall sub_b3e98(void)

{
  code *pcVar1;
  
  if (byte_d4f44 == '\0') {
    pcVar1 = (code *)swi(0x10);
    byte_d4f44 = (*pcVar1)();
    byte_d4f45 = DAT_00000410;
    word_d4f46 = _DAT_0000044a;
    byte_d4f48 = DAT_00000484;
    sub_b3454();
  }
  return;
}


// ================================================================================================
// restorevideo @ 0xb3ed8 [__watcall]
// ================================================================================================

undefined8 __watcall restorevideo(void)

{
  code *pcVar1;
  undefined *puVar2;
  undefined *puVar3;
  
  puVar3 = &stack0xffffffe0;
  if (byte_d4f44 != '\0') {
    DAT_00000410 = byte_d4f45;
    pcVar1 = (code *)swi(0x10);
    (*pcVar1)();
    puVar2 = &stack0xffffffe4;
    if ((((byte_d4f44 == '\x03') && (puVar2 = &stack0xffffffe4, word_d4f46 == 0x50)) &&
        (puVar2 = &stack0xffffffe4, 0x29 < byte_d4f48)) &&
       (puVar2 = &stack0xffffffe4, byte_d4f48 < 0x33)) {
      pcVar1 = (code *)swi(0x10);
      (*pcVar1)();
      puVar2 = &stack0xffffffe8;
    }
    DAT_00000410 = byte_d4f45;
    if ((byte_d4f45 & 0x30) == 0x30) {
      *(undefined4 *)(puVar2 + -4) = 0;
      *(undefined4 *)(puVar2 + -8) = 0xb3f3a;
      sub_910b0();
    }
    pcVar1 = (code *)swi(0x10);
    (*pcVar1)();
    puVar3 = puVar2 + 4;
    byte_d4f44 = '\0';
  }
  return CONCAT44(*(undefined4 *)(puVar3 + 0x14),*(undefined4 *)(puVar3 + 0x1c));
}


// ================================================================================================
// sub_b3f50 @ 0xb3f50 [__watcall]
// ================================================================================================

void __watcall sub_b3f50(void)

{
  ushort *puVar1;
  uint uVar2;
  int iVar3;
  undefined *puVar4;
  undefined2 in_SS;
  bool bVar5;
  bool bVar6;
  bool bVar7;
  bool bVar8;
  bool bVar9;
  byte in_AC;
  byte in_VIF;
  byte in_VIP;
  byte in_ID;
  ushort uVar10;
  uint uVar11;
  byte in_CR0;
  undefined auStack_4 [4];
  
  dword_d305c = 1;
  puVar1 = (ushort *)segment(in_SS,(short)auStack_4);
  iVar3 = CONCAT22((short)((uint)auStack_4 >> 0x10),(short)auStack_4 + 2);
  *(ushort *)(iVar3 + -2) = *puVar1 | 0x7000;
  uVar10 = *(ushort *)(iVar3 + -2);
  bVar9 = (uVar10 & 0x4000) != 0;
  bVar8 = (uVar10 & 0x400) != 0;
  bVar7 = (uVar10 & 0x200) != 0;
  bVar6 = (uVar10 & 0x100) != 0;
  bVar5 = (uVar10 & 0x10) != 0;
  *(ushort *)(iVar3 + -2) =
       (ushort)bVar9 * 0x4000 | (ushort)((uVar10 & 0x800) != 0) * 0x800 | (ushort)bVar8 * 0x400 |
       (ushort)bVar7 * 0x200 | (ushort)bVar6 * 0x100 | (ushort)((uVar10 & 0x80) != 0) * 0x80 |
       (ushort)((uVar10 & 0x40) != 0) * 0x40 | (ushort)bVar5 * 0x10 |
       (ushort)((uVar10 & 4) != 0) * 4 | (ushort)((uVar10 & 1) != 0);
  puVar1 = (ushort *)segment(in_SS,(short)(iVar3 + -2));
  uVar10 = (short)(iVar3 + -2) + 2;
  if ((*puVar1 & 0x7000) != 0) {
    dword_d3060 = 1;
    byte_d3068 = in_CR0 & 1;
    puVar4 = (undefined *)(CONCAT22((short)((uint)(iVar3 + -2) >> 0x10),uVar10) & 0xfffffffc);
    *(uint *)(puVar4 + -4) =
         (uint)bVar9 * 0x4000 | (uint)bVar8 * 0x400 | (uint)bVar7 * 0x200 | (uint)bVar6 * 0x100 |
         (uint)((int)puVar4 < 0) * 0x80 | (uint)(puVar4 == (undefined *)0x0) * 0x40 |
         (uint)bVar5 * 0x10 | (uint)((POPCOUNT(uVar10 & 0xfc) & 1U) == 0) * 4 |
         (uint)(in_ID & 1) * 0x200000 | (uint)(in_VIP & 1) * 0x100000 | (uint)(in_VIF & 1) * 0x80000
         | (uint)(in_AC & 1) * 0x40000;
    uVar2 = *(uint *)(puVar4 + -4);
    *(uint *)(puVar4 + -4) = uVar2 ^ 0x40000;
    uVar11 = *(uint *)(puVar4 + -4);
    *(uint *)(puVar4 + -4) =
         (uint)((uVar11 & 0x4000) != 0) * 0x4000 | (uint)((uVar11 & 0x800) != 0) * 0x800 |
         (uint)((uVar11 & 0x400) != 0) * 0x400 | (uint)((uVar11 & 0x200) != 0) * 0x200 |
         (uint)((uVar11 & 0x100) != 0) * 0x100 | (uint)((uVar11 & 0x80) != 0) * 0x80 |
         (uint)((uVar11 & 0x40) != 0) * 0x40 | (uint)((uVar11 & 0x10) != 0) * 0x10 |
         (uint)((uVar11 & 4) != 0) * 4 | (uint)((uVar11 & 1) != 0) |
         (uint)((uVar11 & 0x200000) != 0) * 0x200000 | (uint)((uVar11 & 0x40000) != 0) * 0x40000;
    byte_d3064 = (byte)((ushort)((ushort)((uint)*(undefined4 *)(puVar4 + -4) >> 0x10) ^
                                (ushort)(uVar2 >> 0x10)) >> 2) & 1;
  }
  return;
}


// ================================================================================================
// sub_b3fb0 @ 0xb3fb0 [__cdecl]
// ================================================================================================

void sub_b3fb0(undefined4 *param_1,uint param_2,undefined param_3)

{
  uint uVar1;
  
  for (uVar1 = param_2 >> 2; uVar1 != 0; uVar1 = uVar1 - 1) {
    *param_1 = CONCAT22(CONCAT11(param_3,param_3),CONCAT11(param_3,param_3));
    param_1 = param_1 + 1;
  }
  for (param_2 = param_2 & 3; param_2 != 0; param_2 = param_2 - 1) {
    *(undefined *)param_1 = param_3;
    param_1 = (undefined4 *)((int)param_1 + 1);
  }
  return;
}


// ================================================================================================
// sub_b3fc2 @ 0xb3fc2 [__cdecl]
// ================================================================================================

void sub_b3fc2(undefined4 *param_1,uint param_2)

{
  uint uVar1;
  
  for (uVar1 = param_2 >> 2; uVar1 != 0; uVar1 = uVar1 - 1) {
    *param_1 = 0;
    param_1 = param_1 + 1;
  }
  for (param_2 = param_2 & 3; param_2 != 0; param_2 = param_2 - 1) {
    *(undefined *)param_1 = 0;
    param_1 = (undefined4 *)((int)param_1 + 1);
  }
  return;
}


// ================================================================================================
// sub_b3fe0 @ 0xb3fe0 [__watcall]
// ================================================================================================

void __watcall sub_b3fe0(void)

{
  dword_d4fa0 = 0;
  return;
}


// ================================================================================================
// sub_b3fec @ 0xb3fec [__watcall]
// ================================================================================================

short __watcall sub_b3fec(void)

{
  char cVar1;
  short sVar2;
  uint uVar3;
  
  sVar2 = sub_b39d0();
  if (sVar2 != 0) {
    return sVar2;
  }
  uVar3 = sub_b3168();
  cVar1 = byte_d4fe8;
  if ((uVar3 & 0x30) == 0) {
    sVar2 = (short)*(undefined4 *)(&unk_d4fa4 + (uVar3 & 0xf) * 2);
  }
  else {
    sVar2 = 0xd;
  }
  if (sVar2 == word_d4fe4) {
    if (sVar2 != 0) {
      sVar2 = sub_b3962(dword_d4feb);
      if (word_d4fe9 <= sVar2) {
        word_d4fe9 = 0xf;
LAB_000b409f:
        dword_d4feb = getticks();
        return word_d4fe4;
      }
    }
  }
  else if (sVar2 == word_d4fe6) {
    byte_d4fe8 = byte_d4fe8 + -1;
    if (byte_d4fe8 == '\0' || cVar1 < '\x01') {
      word_d4fe9 = 0x46;
      word_d4fe4 = sVar2;
      goto LAB_000b409f;
    }
  }
  else {
    byte_d4fe8 = '\x03';
    word_d4fe6 = sVar2;
  }
  return 0;
}


// ================================================================================================
// sub_b3ff7 @ 0xb3ff7 [__watcall]
// ================================================================================================

short __watcall sub_b3ff7(void)

{
  char cVar1;
  short sVar2;
  undefined4 uVar3;
  uint uVar4;
  
  uVar3 = sub_b39d0();
  if ((short)uVar3 != 0) {
    sVar2 = sub_b4aa4(uVar3);
    return sVar2;
  }
  uVar4 = sub_b3168();
  cVar1 = byte_d4fe8;
  if ((uVar4 & 0x30) == 0) {
    sVar2 = (short)*(undefined4 *)(&unk_d4fa4 + (uVar4 & 0xf) * 2);
  }
  else {
    sVar2 = 0xd;
  }
  if (sVar2 == word_d4fe4) {
    if (sVar2 != 0) {
      sVar2 = sub_b3962(dword_d4feb);
      if (word_d4fe9 <= sVar2) {
        word_d4fe9 = 0xf;
LAB_000b409f:
        dword_d4feb = getticks();
        return word_d4fe4;
      }
    }
  }
  else if (sVar2 == word_d4fe6) {
    byte_d4fe8 = byte_d4fe8 + -1;
    if (byte_d4fe8 == '\0' || cVar1 < '\x01') {
      word_d4fe9 = 0x46;
      word_d4fe4 = sVar2;
      goto LAB_000b409f;
    }
  }
  else {
    byte_d4fe8 = '\x03';
    word_d4fe6 = sVar2;
  }
  return 0;
}


// ================================================================================================
// sub_b400b @ 0xb400b [__watcall]
// ================================================================================================

short __watcall sub_b400b(void)

{
  char cVar1;
  short sVar2;
  undefined4 uVar3;
  uint uVar4;
  
  uVar3 = sub_b39d0();
  if ((short)uVar3 != 0) {
    sVar2 = sub_b4aa4(uVar3);
    return sVar2;
  }
  sVar2 = (*(code *)mouse_update_callback)();
  uVar4 = (uint)(ushort)(sVar2 << 4);
  if ((ushort)(sVar2 << 4) == 0) {
    uVar4 = sub_b3168();
  }
  cVar1 = byte_d4fe8;
  if ((uVar4 & 0x30) == 0) {
    sVar2 = (short)*(undefined4 *)(&unk_d4fa4 + (uVar4 & 0xf) * 2);
  }
  else {
    sVar2 = 0xd;
  }
  if (sVar2 == word_d4fe4) {
    if (sVar2 != 0) {
      sVar2 = sub_b3962(dword_d4feb);
      if (word_d4fe9 <= sVar2) {
        word_d4fe9 = 0xf;
LAB_000b409f:
        dword_d4feb = getticks();
        return word_d4fe4;
      }
    }
  }
  else if (sVar2 == word_d4fe6) {
    byte_d4fe8 = byte_d4fe8 + -1;
    if (byte_d4fe8 == '\0' || cVar1 < '\x01') {
      word_d4fe9 = 0x46;
      word_d4fe4 = sVar2;
      goto LAB_000b409f;
    }
  }
  else {
    byte_d4fe8 = '\x03';
    word_d4fe6 = sVar2;
  }
  return 0;
}


// ================================================================================================
// sub_b40bf @ 0xb40bf [__watcall]
// ================================================================================================

void __watcall sub_b40bf(void)

{
  int iVar1;
  
  iVar1 = sub_b39d0();
  if (iVar1 != 0) {
    sub_b4aa4(iVar1);
  }
  return;
}


// ================================================================================================
// sub_b40d4 @ 0xb40d4 [__watcall]
// ================================================================================================

/* WARNING: Removing unreachable block (ram,0x000b484d) */
/* WARNING: Removing unreachable block (ram,0x000b487b) */
/* WARNING: Removing unreachable block (ram,0x000b488f) */
/* WARNING: Removing unreachable block (ram,0x000b48ad) */
/* WARNING: Removing unreachable block (ram,0x000b48c3) */
/* WARNING: Removing unreachable block (ram,0x000b48ce) */
/* WARNING: Removing unreachable block (ram,0x000b48d4) */
/* WARNING: Removing unreachable block (ram,0x000b48e1) */
/* WARNING: Removing unreachable block (ram,0x000b48e7) */
/* WARNING: Removing unreachable block (ram,0x000b48b5) */
/* WARNING: Removing unreachable block (ram,0x000b489f) */
/* WARNING: Removing unreachable block (ram,0x000b4885) */
/* WARNING: Removing unreachable block (ram,0x000b4857) */
/* WARNING: Removing unreachable block (ram,0x000b485f) */
/* WARNING: Removing unreachable block (ram,0x000b4144) */
/* WARNING: Removing unreachable block (ram,0x000b4157) */
/* WARNING: Removing unreachable block (ram,0x000b415e) */
/* WARNING: Removing unreachable block (ram,0x000b4162) */
/* WARNING: Removing unreachable block (ram,0x000b4165) */
/* WARNING: Removing unreachable block (ram,0x000b416c) */
/* WARNING: Removing unreachable block (ram,0x000b4173) */
/* WARNING: Removing unreachable block (ram,0x000b4177) */
/* WARNING: Removing unreachable block (ram,0x000b417a) */
/* WARNING: Removing unreachable block (ram,0x000b418d) */
/* WARNING: Removing unreachable block (ram,0x000b4190) */
/* WARNING: Removing unreachable block (ram,0x000b4194) */
/* WARNING: Removing unreachable block (ram,0x000b4197) */
/* WARNING: Removing unreachable block (ram,0x000b419e) */
/* WARNING: Removing unreachable block (ram,0x000b41a1) */
/* WARNING: Removing unreachable block (ram,0x000b41a5) */
/* WARNING: Removing unreachable block (ram,0x000b41a8) */
/* WARNING: Removing unreachable block (ram,0x000b41ac) */
/* WARNING: Removing unreachable block (ram,0x000b45d2) */
/* WARNING: Removing unreachable block (ram,0x000b45f9) */
/* WARNING: Removing unreachable block (ram,0x000b460f) */
/* WARNING: Removing unreachable block (ram,0x000b461a) */
/* WARNING: Removing unreachable block (ram,0x000b4621) */
/* WARNING: Removing unreachable block (ram,0x000b4638) */
/* WARNING: Removing unreachable block (ram,0x000b463e) */
/* WARNING: Removing unreachable block (ram,0x000b4658) */
/* WARNING: Removing unreachable block (ram,0x000b4653) */
/* WARNING: Removing unreachable block (ram,0x000b45fd) */
/* WARNING: Removing unreachable block (ram,0x000b45e3) */
/* WARNING: Removing unreachable block (ram,0x000b465b) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __watcall sub_b40d4(void)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  int iVar10;
  int iVar11;
  bool bVar12;
  int in_stack_00000004;
  int in_stack_00000008;
  int in_stack_0000000c;
  int in_stack_00000010;
  undefined4 *in_stack_00000014;
  
  in_stack_00000014[0xd] = 0xff;
  *in_stack_00000014 = 0;
  in_stack_00000014[2] = 0;
  in_stack_00000014[8] = 0;
  in_stack_00000014[9] = 0;
  in_stack_00000014[10] = 0;
  in_stack_00000014[0xb] = 0;
  if (in_stack_00000010 < in_stack_00000008) {
    in_stack_00000014[1] = in_stack_0000000c;
    in_stack_00000014[3] = in_stack_00000010;
    in_stack_00000014[4] = in_stack_00000004;
    in_stack_00000014[5] = in_stack_00000008;
  }
  else {
    in_stack_00000014[1] = in_stack_00000004;
    in_stack_00000014[3] = in_stack_00000008;
    in_stack_00000014[4] = in_stack_0000000c;
    in_stack_00000014[5] = in_stack_00000010;
  }
  if (in_stack_00000008 == in_stack_00000010) {
    *(undefined *)(in_stack_00000014 + 0xd) = 1;
    if (in_stack_00000004 == in_stack_0000000c) {
      *(undefined *)(in_stack_00000014 + 0xd) = 9;
    }
    iVar7 = in_stack_00000004;
    if (in_stack_0000000c < in_stack_00000004) {
      *(undefined *)(in_stack_00000014 + 0xd) = 0;
      in_stack_00000014[1] = in_stack_0000000c;
      in_stack_00000014[4] = in_stack_00000004;
      iVar7 = in_stack_0000000c;
      in_stack_0000000c = in_stack_00000004;
    }
    in_stack_00000014[6] = (in_stack_0000000c - iVar7) + 1;
  }
  else {
LAB_000b413c:
    uVar5 = in_stack_00000014[5] - in_stack_00000014[3];
    if (SBORROW4(in_stack_00000014[5],in_stack_00000014[3])) goto LAB_000b41c3;
    iVar7 = in_stack_00000014[4];
    iVar10 = in_stack_00000014[1];
    uVar8 = iVar7 - iVar10;
    if (SBORROW4(iVar7,in_stack_00000014[1])) goto LAB_000b41c3;
    if (uVar8 == 0) {
      bVar12 = uVar5 + 1 == 0;
      in_stack_00000014[6] = uVar5 + 1;
      *(undefined *)(in_stack_00000014 + 0xd) = 2;
      goto LAB_000b4246;
    }
    uVar6 = uVar5;
    if (iVar7 < iVar10) {
      uVar9 = -uVar8;
      if (uVar9 < uVar5) {
        *(undefined *)(in_stack_00000014 + 0xd) = 5;
        uVar5 = uVar9;
      }
      else {
        if (-uVar5 == uVar8) {
          *(undefined *)(in_stack_00000014 + 0xd) = 3;
          goto LAB_000b4242;
        }
        *(undefined *)(in_stack_00000014 + 0xd) = 7;
        uVar6 = uVar9;
      }
    }
    else if (uVar8 < uVar5) {
      *(undefined *)(in_stack_00000014 + 0xd) = 6;
      uVar5 = uVar8;
    }
    else {
      if (uVar8 == uVar5) {
        *(undefined *)(in_stack_00000014 + 0xd) = 4;
LAB_000b4242:
        bVar12 = uVar5 + 1 == 0;
        in_stack_00000014[6] = uVar5 + 1;
        goto LAB_000b4246;
      }
      *(undefined *)(in_stack_00000014 + 0xd) = 8;
      uVar6 = uVar8;
    }
    if ((int)uVar6 < dword_d5678) {
      iVar7 = (uint)*(ushort *)((&off_d567c)[uVar6] + uVar5 * 2) << 0x10;
    }
    else {
      iVar7 = (int)(((ulonglong)uVar5 << 0x20) / (ulonglong)uVar6) +
              (uint)(uVar6 >> 1 < (uint)(((ulonglong)uVar5 << 0x20) % (ulonglong)uVar6));
    }
    in_stack_00000014[0xc] = iVar7;
    bVar12 = uVar6 + 1 == 0;
    if (SCARRY4(uVar6,1)) {
LAB_000b41c3:
      iVar7 = ((int)in_stack_00000014[5] >> 1) - ((int)in_stack_00000014[3] >> 1) >> 1;
      iVar10 = ((int)in_stack_00000014[4] >> 1) - ((int)in_stack_00000014[1] >> 1) >> 1;
      while ((int)in_stack_00000014[3] < -15999) {
LAB_000b4911:
        iVar2 = in_stack_00000014[3] + iVar7;
        in_stack_00000014[3] = iVar2;
        iVar3 = iVar2 - dword_d30b0;
        if (iVar3 != 0 && dword_d30b0 <= iVar2) {
          if (iVar7 < iVar3) {
            iVar3 = iVar7;
          }
          iVar11 = iVar2 - dword_d30b8;
          iVar4 = iVar3;
          if ((iVar11 == 0 || iVar2 < dword_d30b8) ||
             (iVar4 = iVar3 - iVar11, iVar4 != 0 && iVar11 <= iVar3)) {
            if ((int)in_stack_00000014[1] < dword_d30ac) {
              in_stack_00000014[8] = in_stack_00000014[8] + iVar4;
            }
            else {
              in_stack_00000014[10] = in_stack_00000014[10] + iVar4;
            }
          }
        }
        in_stack_00000014[1] = in_stack_00000014[1] + iVar10;
      }
      do {
        if ((int)in_stack_00000014[5] < 16000) {
          if (((int)in_stack_00000014[1] < -15999) || (15999 < (int)in_stack_00000014[1]))
          goto LAB_000b4911;
          if ((-16000 < (int)in_stack_00000014[4]) && ((int)in_stack_00000014[4] < 16000))
          goto LAB_000b413c;
        }
        iVar3 = in_stack_00000014[5] - iVar7;
        in_stack_00000014[5] = iVar3;
        iVar2 = (iVar3 - dword_d30b8) + 1;
        if (SCARRY4(iVar3 - dword_d30b8,1) != iVar2 < 0) {
          iVar4 = -iVar2;
          if (-iVar7 != iVar2 && iVar7 <= -iVar2) {
            iVar4 = iVar7;
          }
          iVar2 = (iVar3 - dword_d30b0) + 1;
          if ((SCARRY4(iVar3 - dword_d30b0,1) == iVar2 < 0) ||
             (bVar12 = SCARRY4(iVar4,iVar2), iVar4 = iVar4 + iVar2,
             iVar4 != 0 && bVar12 == iVar4 < 0)) {
            if ((int)in_stack_00000014[4] < dword_d30ac) {
              in_stack_00000014[9] = in_stack_00000014[9] + iVar4;
            }
            else {
              in_stack_00000014[0xb] = in_stack_00000014[0xb] + iVar4;
            }
          }
        }
        in_stack_00000014[4] = in_stack_00000014[4] - iVar10;
      } while( true );
    }
    in_stack_00000014[6] = uVar6 + 1;
LAB_000b4246:
    if (!bVar12) {
                    /* WARNING: Could not recover jumptable at 0x000b424b. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      uVar1 = (*(code *)0xb4293)();
      return uVar1;
    }
  }
  return 0;
}


// ================================================================================================
// sub_b40e2 @ 0xb40e2 [__cdecl]
// ================================================================================================

/* WARNING: Removing unreachable block (ram,0x000b4870) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint sub_b40e2(int param_1,int param_2,int param_3,int param_4,undefined4 *param_5)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  byte bVar7;
  ushort uVar8;
  byte bVar11;
  uint uVar9;
  uint uVar10;
  int iVar12;
  int iVar13;
  bool bVar14;
  
  param_5[0xd] = 0xff;
  *param_5 = 0;
  param_5[2] = 0;
  param_5[8] = 0;
  param_5[9] = 0;
  param_5[10] = 0;
  param_5[0xb] = 0;
  if (param_4 < param_2) {
    param_5[1] = param_3;
    param_5[3] = param_4;
    param_5[4] = param_1;
    param_5[5] = param_2;
  }
  else {
    param_5[1] = param_1;
    param_5[3] = param_2;
    param_5[4] = param_3;
    param_5[5] = param_4;
  }
  if (param_2 == param_4) {
    *(undefined *)(param_5 + 0xd) = 1;
    if (param_1 == param_3) {
      *(undefined *)(param_5 + 0xd) = 9;
    }
    iVar12 = param_1;
    if (param_3 < param_1) {
      *(undefined *)(param_5 + 0xd) = 0;
      param_5[1] = param_3;
      param_5[4] = param_1;
      iVar12 = param_3;
      param_3 = param_1;
    }
    iVar3 = dword_d30b8;
    iVar1 = dword_d30b0;
    if (param_2 < dword_d30b0) {
      bVar7 = 4;
      param_5[3] = dword_d30b0;
      param_5[5] = iVar1;
    }
    else if (param_2 < dword_d30b8) {
      param_5[6] = (param_3 - iVar12) + 1;
      if (param_3 < dword_d30ac) {
        param_5[5] = param_5[5] + -1;
        param_5[9] = 1;
        bVar7 = 2;
      }
      else {
        if (iVar12 < _dword_d30b4) {
          iVar1 = dword_d30ac - iVar12;
          if (iVar1 != 0 && iVar12 <= dword_d30ac) {
            param_5[1] = dword_d30ac;
            param_5[6] = param_5[6] - iVar1;
          }
          iVar12 = _dword_d30b4 + -1;
          if (param_3 - iVar12 == 0 || param_3 < iVar12) {
            return 0;
          }
          param_5[6] = param_5[6] - (param_3 - iVar12);
          param_5[4] = iVar12;
          return 0;
        }
        param_5[5] = param_5[5] + -1;
        param_5[0xb] = 1;
        bVar7 = 1;
      }
    }
    else {
      bVar7 = 8;
      param_5[3] = dword_d30b8;
      param_5[5] = iVar3;
    }
    *(byte *)((int)param_5 + 0x35) = bVar7;
    param_5[6] = 0;
    return (uint)bVar7;
  }
LAB_000b413c:
  uVar8 = 0;
  if ((int)param_5[3] < dword_d30b8) {
    if ((int)param_5[3] < dword_d30b0) {
      uVar8 = 0x400;
    }
    if ((int)param_5[5] < dword_d30b0) {
      bVar7 = 4;
    }
    else {
      if (dword_d30b8 <= (int)param_5[5]) {
        uVar8 = uVar8 | 8;
      }
      if ((int)param_5[1] < dword_d30ac) {
        uVar8 = uVar8 | 0x200;
      }
      if (_dword_d30b4 <= (int)param_5[1]) {
        uVar8 = uVar8 | 0x100;
      }
      if ((int)param_5[4] < dword_d30ac) {
        uVar8 = uVar8 | 2;
      }
      if (_dword_d30b4 <= (int)param_5[4]) {
        uVar8 = uVar8 | 1;
      }
      bVar7 = (byte)uVar8;
      bVar11 = (byte)(uVar8 >> 8);
      if ((bVar11 & bVar7) == 0) {
        uVar5 = param_5[5] - param_5[3];
        if (SBORROW4(param_5[5],param_5[3])) goto LAB_000b41c3;
        iVar12 = param_5[4];
        iVar1 = param_5[1];
        uVar9 = iVar12 - iVar1;
        if (SBORROW4(iVar12,param_5[1])) goto LAB_000b41c3;
        if (uVar9 == 0) {
          bVar14 = uVar5 + 1 == 0;
          param_5[6] = uVar5 + 1;
          *(undefined *)(param_5 + 0xd) = 2;
          goto LAB_000b4246;
        }
        uVar6 = uVar5;
        if (iVar12 < iVar1) {
          uVar10 = -uVar9;
          if (uVar10 < uVar5) {
            *(undefined *)(param_5 + 0xd) = 5;
            uVar5 = uVar10;
          }
          else {
            if (-uVar5 == uVar9) {
              *(undefined *)(param_5 + 0xd) = 3;
              goto LAB_000b4242;
            }
            *(undefined *)(param_5 + 0xd) = 7;
            uVar6 = uVar10;
          }
        }
        else if (uVar9 < uVar5) {
          *(undefined *)(param_5 + 0xd) = 6;
          uVar5 = uVar9;
        }
        else {
          if (uVar9 == uVar5) {
            *(undefined *)(param_5 + 0xd) = 4;
LAB_000b4242:
            bVar14 = uVar5 + 1 == 0;
            param_5[6] = uVar5 + 1;
            goto LAB_000b4246;
          }
          *(undefined *)(param_5 + 0xd) = 8;
          uVar6 = uVar9;
        }
        if ((int)uVar6 < dword_d5678) {
          iVar12 = (uint)*(ushort *)((&off_d567c)[uVar6] + uVar5 * 2) << 0x10;
        }
        else {
          iVar12 = (int)(((ulonglong)uVar5 << 0x20) / (ulonglong)uVar6) +
                   (uint)(uVar6 >> 1 < (uint)(((ulonglong)uVar5 << 0x20) % (ulonglong)uVar6));
        }
        param_5[0xc] = iVar12;
        bVar14 = uVar6 + 1 == 0;
        if (SCARRY4(uVar6,1)) {
LAB_000b41c3:
          iVar12 = ((int)param_5[5] >> 1) - ((int)param_5[3] >> 1) >> 1;
          iVar1 = ((int)param_5[4] >> 1) - ((int)param_5[1] >> 1) >> 1;
          while ((int)param_5[3] < -15999) {
LAB_000b4911:
            iVar2 = param_5[3] + iVar12;
            param_5[3] = iVar2;
            iVar3 = iVar2 - dword_d30b0;
            if (iVar3 != 0 && dword_d30b0 <= iVar2) {
              if (iVar12 < iVar3) {
                iVar3 = iVar12;
              }
              iVar13 = iVar2 - dword_d30b8;
              iVar4 = iVar3;
              if ((iVar13 == 0 || iVar2 < dword_d30b8) ||
                 (iVar4 = iVar3 - iVar13, iVar4 != 0 && iVar13 <= iVar3)) {
                if ((int)param_5[1] < dword_d30ac) {
                  param_5[8] = param_5[8] + iVar4;
                }
                else {
                  param_5[10] = param_5[10] + iVar4;
                }
              }
            }
            param_5[1] = param_5[1] + iVar1;
          }
          do {
            if ((int)param_5[5] < 16000) {
              if (((int)param_5[1] < -15999) || (15999 < (int)param_5[1])) goto LAB_000b4911;
              if ((-16000 < (int)param_5[4]) && ((int)param_5[4] < 16000)) goto LAB_000b413c;
            }
            iVar3 = param_5[5] - iVar12;
            param_5[5] = iVar3;
            iVar2 = (iVar3 - dword_d30b8) + 1;
            if (SCARRY4(iVar3 - dword_d30b8,1) != iVar2 < 0) {
              iVar4 = -iVar2;
              if (-iVar12 != iVar2 && iVar12 <= -iVar2) {
                iVar4 = iVar12;
              }
              iVar2 = (iVar3 - dword_d30b0) + 1;
              if ((SCARRY4(iVar3 - dword_d30b0,1) == iVar2 < 0) ||
                 (bVar14 = SCARRY4(iVar4,iVar2), iVar4 = iVar4 + iVar2,
                 iVar4 != 0 && bVar14 == iVar4 < 0)) {
                if ((int)param_5[4] < dword_d30ac) {
                  param_5[9] = param_5[9] + iVar4;
                }
                else {
                  param_5[0xb] = param_5[0xb] + iVar4;
                }
              }
            }
            param_5[4] = param_5[4] - iVar1;
          } while( true );
        }
        param_5[6] = uVar6 + 1;
LAB_000b4246:
        if (bVar14) {
          return 0;
        }
                    /* WARNING: Could not recover jumptable at 0x000b424b. Too many branches */
                    /* WARNING: Treating indirect jump as call */
        uVar5 = (**(code **)(&UNK_000b4253 + (uint)(bVar7 | bVar11) * 4))();
        return uVar5;
      }
      bVar7 = bVar7 & bVar11;
    }
  }
  else {
    bVar7 = 8;
  }
  *(byte *)((int)param_5 + 0x35) = bVar7;
  param_5[6] = 0;
  iVar12 = dword_d30b0;
  bVar7 = *(byte *)((int)param_5 + 0x35);
  if ((bVar7 & 4) == 0) {
    if ((bVar7 & 8) == 0) {
      iVar12 = param_5[5];
      if (dword_d30b8 <= iVar12) {
        iVar12 = dword_d30b8 + -1;
      }
      iVar1 = param_5[3] + (uint)(0x7fffffff < (uint)param_5[2]);
      if (iVar1 < dword_d30b0) {
        iVar1 = dword_d30b0;
      }
      param_5[3] = iVar1;
      param_5[2] = 0;
      iVar12 = (iVar12 - iVar1) + 1;
      param_5[5] = iVar1 + -1;
      if ((bVar7 & 2) == 0) {
        param_5[0xb] = param_5[0xb] + iVar12;
      }
      else {
        param_5[9] = param_5[9] + iVar12;
      }
    }
    else {
      param_5[3] = dword_d30b8;
      param_5[2] = 0;
    }
  }
  else {
    param_5[3] = dword_d30b0;
    param_5[2] = 0;
    param_5[5] = iVar12 + -1;
  }
  return (uint)bVar7;
}


// ================================================================================================
// sub_b49c0 @ 0xb49c0 [__cdecl]
// ================================================================================================

void sub_b49c0(int param_1,int param_2)

{
  uint uVar1;
  
  uVar1 = 0;
  if (param_2 < 0) {
    uVar1 = 8;
    param_2 = -param_2;
  }
  if (param_1 < 0) {
    uVar1 = uVar1 | 0x10;
    param_1 = -param_1;
  }
  if (param_2 <= param_1) {
    if (param_1 == param_2) {
                    /* WARNING: Could not recover jumptable at 0x000b4a05. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)((int)&PTR_LAB_000b4a0c + uVar1))();
      return;
    }
    uVar1 = uVar1 | 4;
  }
                    /* WARNING: Could not recover jumptable at 0x000b49f9. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)((int)&PTR_LAB_000b4a0c + uVar1))();
  return;
}


// ================================================================================================
// sub_b4a60 @ 0xb4a60 [__cdecl]
// ================================================================================================

undefined * sub_b4a60(ushort param_1)

{
  char cVar2;
  uint uVar1;
  
  param_1 = param_1 & 0x3ff;
  cVar2 = (char)(param_1 >> 8);
  if ((POPCOUNT(cVar2) & 1U) != 0) {
    uVar1 = (uint)CONCAT11(cVar2 + -1,(char)param_1);
    if ((char)(cVar2 + -1) == '\0') {
      return (&unk_d6578)[-uVar1];
    }
    return (undefined *)-*(int *)(&unk_d5d78 + uVar1 * 4);
  }
  if (cVar2 == '\0') {
    return *(undefined **)(&unk_d6178 + (uint)param_1 * 4);
  }
  return (undefined *)-*(int *)(&unk_d7178 + (uint)param_1 * -4);
}


// ================================================================================================
// sub_b4a66 @ 0xb4a66 [__cdecl]
// ================================================================================================

undefined * sub_b4a66(undefined4 param_1)

{
  ushort uVar1;
  uint uVar2;
  char cVar3;
  
  uVar1 = CONCAT11((char)((uint)param_1 >> 8) + '\x01',(char)param_1) & 0x3ff;
  cVar3 = (char)(uVar1 >> 8);
  if ((POPCOUNT(cVar3) & 1U) != 0) {
    uVar2 = (uint)CONCAT11(cVar3 + -1,(char)uVar1);
    if ((char)(cVar3 + -1) == '\0') {
      return (&unk_d6578)[-uVar2];
    }
    return (undefined *)-*(int *)(&unk_d5d78 + uVar2 * 4);
  }
  if (cVar3 == '\0') {
    return *(undefined **)(&unk_d6178 + (uint)uVar1 * 4);
  }
  return (undefined *)-*(int *)(&unk_d7178 + (uint)uVar1 * -4);
}


// ================================================================================================
// sub_b4aa4 @ 0xb4aa4 [__cdecl]
// ================================================================================================

uint sub_b4aa4(uint param_1)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  
  iVar2 = dword_d5562;
  dword_d5562 = dword_d5562 + -1;
  if (dword_d5562 == 0) {
    if ((char)param_1 == '\0') {
      uVar3 = param_1 >> 8 & 0xff;
      if (0x83 < uVar3) {
        uVar3 = 0x84;
      }
      bVar1 = (&unk_d54dc)[uVar3];
    }
    else {
      param_1 = param_1 & 0x7f;
      bVar1 = (&unk_d545c)[param_1];
    }
    if (bVar1 != 0) {
      (*(code *)(&unk_d5566)[bVar1 - 1])();
      dword_d5562 = dword_d5562 + 1;
      return 0;
    }
  }
  dword_d5562 = iVar2;
  return param_1;
}


// ================================================================================================
// sub_b4afd @ 0xb4afd [__watcall]
// ================================================================================================

void __watcall sub_b4afd(void)

{
  char cVar1;
  int iVar2;
  int *piVar3;
  uint uVar4;
  uint in_stack_00000004;
  int in_stack_00000008;
  
  iVar2 = 0x40;
  piVar3 = &unk_d5566;
  do {
    if (*piVar3 == in_stack_00000008) {
LAB_000b4b20:
      cVar1 = 'A' - (char)iVar2;
      if ((char)in_stack_00000004 == '\0') {
        uVar4 = in_stack_00000004 >> 8 & 0xff;
        if (uVar4 < 0x85) {
          (&unk_d54dc)[uVar4] = cVar1;
          return;
        }
      }
      else if ((int)in_stack_00000004 < 0x80) {
        (&unk_d545c)[in_stack_00000004] = cVar1;
      }
      return;
    }
    if (*(short *)piVar3 == 0) {
      *piVar3 = in_stack_00000008;
      goto LAB_000b4b20;
    }
    piVar3 = piVar3 + 1;
    iVar2 = iVar2 + -1;
    if (iVar2 == 0) {
      return;
    }
  } while( true );
}


// ================================================================================================
// sub_b4b4e @ 0xb4b4e [__watcall]
// ================================================================================================

void __watcall sub_b4b4e(void)

{
  uint uVar1;
  uint in_stack_00000004;
  
  if ((char)in_stack_00000004 == '\0') {
    uVar1 = in_stack_00000004 >> 8 & 0xff;
    if (uVar1 < 0x85) {
      (&unk_d54dc)[uVar1] = 0;
      return;
    }
  }
  else if ((int)in_stack_00000004 < 0x80) {
    (&unk_d545c)[in_stack_00000004] = 0;
  }
  return;
}


// ================================================================================================
// settextmode @ 0xb4b58 [__watcall]
// ================================================================================================

void __watcall settextmode(void)

{
  code *pcVar1;
  
  sub_910b0(0);
  DAT_00000410 = DAT_00000410 & 0xcf;
  DAT_00000410 = DAT_00000410 | 0x10;
  pcVar1 = (code *)swi(0x10);
  (*pcVar1)();
  pcVar1 = (code *)swi(0x10);
  (*pcVar1)();
  dword_d3024 = 0;
  return;
}


// ================================================================================================
// setpalette @ 0xb4b88 [__cdecl]
// ================================================================================================

undefined8 setpalette(undefined4 param_1,int param_2,undefined *param_3)

{
  out(0x3c8,(char)param_1);
  param_2 = param_2 * 3;
  do {
    param_1 = CONCAT31((int3)((uint)param_1 >> 8),*param_3);
    out(0x3c9,*param_3);
    param_2 = param_2 + -1;
    param_3 = param_3 + 1;
  } while (param_2 != 0);
  return CONCAT44(0x3c9,param_1);
}


// ================================================================================================
// setdefaultscreen @ 0xb4ba8 [__watcall]
// ================================================================================================

void __watcall setdefaultscreen(void)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  puVar2 = &dword_d30d4;
  puVar3 = &dword_d30a4;
  for (iVar1 = 0xc; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  return;
}


// ================================================================================================
// setclip @ 0xb4bc4 [__cdecl]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void setclip(int param_1,int param_2,int param_3,int param_4)

{
  if (param_1 < 0) {
    param_1 = 0;
  }
  if (param_3 < 0) {
    param_3 = 0;
  }
  if (dword_d30a4 < param_2) {
    param_2 = dword_d30a4;
  }
  if (dword_d30a8 < param_4) {
    param_4 = dword_d30a8;
  }
  dword_d30ac = param_1;
  dword_d30b0 = param_3;
  _dword_d30b4 = param_2;
  dword_d30b8 = param_4;
  dword_d30bc = param_1;
  dword_d30c0 = param_2;
  return;
}


// ================================================================================================
// sub_b4c28 @ 0xb4c28 [__watcall]
// ================================================================================================

void __watcall sub_b4c28(void)

{
  dword_d429c = 10000;
  return;
}


// ================================================================================================
// waitvsync @ 0xb4c33 [__watcall]
// ================================================================================================

void __watcall waitvsync(void)

{
  byte bVar1;
  
  if (dword_d4fa0 < 2) {
    if (dword_d4fa0 != 1) {
      do {
        bVar1 = in(0x3da);
        dword_d429c = dword_d429c + -1;
      } while (dword_d429c != 0 && (bVar1 & 8) != 0);
      if (dword_d429c == 0) {
        dword_d429c = 10000;
        return;
      }
    }
    do {
      bVar1 = in(0x3da);
      dword_d429c = dword_d429c + -1;
    } while (dword_d429c != 0 && (bVar1 & 8) == 0);
    if (dword_d429c == 0) {
      dword_d429c = 10000;
      return;
    }
  }
  dword_d429c = 100000;
  return;
}


// ================================================================================================
// waitvbl_start @ 0xb4c61 [__watcall]
// ================================================================================================

void __watcall waitvbl_start(void)

{
  byte bVar1;
  
  do {
    bVar1 = in(0x3da);
    dword_d429c = dword_d429c + -1;
  } while (dword_d429c != 0 && (bVar1 & 8) != 0);
  if (dword_d429c != 0) {
    do {
      bVar1 = in(0x3da);
      dword_d429c = dword_d429c + -1;
    } while (dword_d429c != 0 && (bVar1 & 8) == 0);
    if (dword_d429c != 0) {
      dword_d429c = 100000;
      return;
    }
  }
  dword_d429c = 10000;
  return;
}


// ================================================================================================
// waitvbl_end @ 0xb4c84 [__watcall]
// ================================================================================================

void __watcall waitvbl_end(void)

{
  byte bVar1;
  
  do {
    bVar1 = in(0x3da);
    dword_d429c = dword_d429c + -1;
  } while (dword_d429c != 0 && (bVar1 & 8) == 0);
  if (dword_d429c != 0) {
    do {
      bVar1 = in(0x3da);
      dword_d429c = dword_d429c + -1;
    } while (dword_d429c != 0 && (bVar1 & 8) != 0);
    if (dword_d429c != 0) {
      dword_d429c = 100000;
      return;
    }
  }
  dword_d429c = 10000;
  return;
}


// ================================================================================================
// sub_b4ca7 @ 0xb4ca7 [__watcall]
// ================================================================================================

byte __watcall sub_b4ca7(void)

{
  byte bVar1;
  
  bVar1 = in(0x3da);
  return bVar1 & 8;
}


// ================================================================================================
// sub_b4cb4 @ 0xb4cb4 [__watcall]
// ================================================================================================

byte __watcall sub_b4cb4(void)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  byte *pbVar7;
  byte *pbVar8;
  byte *pbVar9;
  bool bVar10;
  int in_stack_00000004;
  short in_stack_00000008;
  short in_stack_0000000c;
  int *piStack_24;
  int iVar6;
  
  iVar2 = (int)(short)(in_stack_00000008 - *(short *)(in_stack_00000004 + 8));
  iVar3 = (int)*(short *)(in_stack_00000004 + 4);
  piStack_24 = (int *)(off_d30cc +
                      (short)(in_stack_0000000c - *(short *)(in_stack_00000004 + 10)) * 4);
  pbVar9 = (byte *)(*piStack_24 + iVar2 + dword_d30d0);
  iVar6 = iVar3;
  pbVar7 = (byte *)(in_stack_00000004 + 0x10);
LAB_000b4d3c:
  do {
    while( true ) {
      pbVar8 = pbVar7 + 1;
      bVar1 = *pbVar7;
      if ((char)bVar1 < '\x01') break;
      iVar4 = (int)(short)(ushort)bVar1;
      pbVar7 = pbVar7 + 2;
      bVar1 = *pbVar8;
      if (bVar1 == 0xff) {
        pbVar9 = pbVar9 + iVar4;
        iVar5 = iVar6 - iVar4;
        bVar10 = iVar6 < iVar4;
        iVar6 = iVar5;
        if (iVar5 == 0 || bVar10) {
          do {
            piStack_24 = piStack_24 + 1;
            bVar10 = SCARRY4(iVar5,iVar3);
            iVar5 = iVar5 + iVar3;
          } while (iVar5 == 0 || bVar10 != iVar5 < 0);
          pbVar9 = (byte *)((*piStack_24 + iVar2 + dword_d30d0 + iVar3) - iVar5);
          iVar6 = iVar5;
        }
      }
      else {
        while (iVar5 = iVar6 - iVar4, iVar5 == 0 || iVar6 < iVar4) {
          for (iVar4 = iVar4 + iVar5; iVar4 != 0; iVar4 = iVar4 + -1) {
            *pbVar9 = bVar1;
            pbVar9 = pbVar9 + 1;
          }
          piStack_24 = piStack_24 + 1;
          pbVar9 = (byte *)(*piStack_24 + iVar2 + dword_d30d0);
          iVar4 = -iVar5;
          iVar6 = iVar3;
        }
        for (; iVar6 = iVar5, iVar4 != 0; iVar4 = iVar4 + -1) {
          *pbVar9 = bVar1;
          pbVar9 = pbVar9 + 1;
        }
      }
    }
    if (-1 < (char)bVar1) {
      return bVar1;
    }
    iVar4 = (int)(short)(ushort)(byte)-bVar1;
    do {
      iVar5 = iVar6 - iVar4;
      if (iVar5 != 0 && iVar4 <= iVar6) goto code_r0x000b4da9;
      for (iVar4 = iVar4 + iVar5; iVar4 != 0; iVar4 = iVar4 + -1) {
        *pbVar9 = *pbVar8;
        pbVar8 = pbVar8 + 1;
        pbVar9 = pbVar9 + 1;
      }
      piStack_24 = piStack_24 + 1;
      pbVar9 = (byte *)(*piStack_24 + iVar2 + dword_d30d0);
      iVar4 = -iVar5;
      iVar6 = iVar3;
      pbVar7 = pbVar8;
    } while (-iVar5 != 0 && iVar5 < 1);
  } while( true );
code_r0x000b4da9:
  for (; iVar6 = iVar5, pbVar7 = pbVar8, iVar4 != 0; iVar4 = iVar4 + -1) {
    *pbVar9 = *pbVar8;
    pbVar8 = pbVar8 + 1;
    pbVar9 = pbVar9 + 1;
  }
  goto LAB_000b4d3c;
}


// ================================================================================================
// blit_rle_frame @ 0xb4cd8 [__cdecl]
// ================================================================================================

byte blit_rle_frame(int param_1,int param_2,int param_3)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  byte *pbVar6;
  byte *pbVar7;
  byte *pbVar8;
  bool bVar9;
  int *piStack_24;
  int iVar5;
  
  iVar2 = (int)*(short *)(param_1 + 4);
  piStack_24 = (int *)(off_d30cc + param_3 * 4);
  pbVar8 = (byte *)(*piStack_24 + param_2 + dword_d30d0);
  iVar5 = iVar2;
  pbVar6 = (byte *)(param_1 + 0x10);
LAB_000b4d3c:
  do {
    while( true ) {
      pbVar7 = pbVar6 + 1;
      bVar1 = *pbVar6;
      if ((char)bVar1 < '\x01') break;
      iVar3 = (int)(short)(ushort)bVar1;
      pbVar6 = pbVar6 + 2;
      bVar1 = *pbVar7;
      if (bVar1 == 0xff) {
        pbVar8 = pbVar8 + iVar3;
        iVar4 = iVar5 - iVar3;
        bVar9 = iVar5 < iVar3;
        iVar5 = iVar4;
        if (iVar4 == 0 || bVar9) {
          do {
            piStack_24 = piStack_24 + 1;
            bVar9 = SCARRY4(iVar4,iVar2);
            iVar4 = iVar4 + iVar2;
          } while (iVar4 == 0 || bVar9 != iVar4 < 0);
          pbVar8 = (byte *)((*piStack_24 + param_2 + dword_d30d0 + iVar2) - iVar4);
          iVar5 = iVar4;
        }
      }
      else {
        while (iVar4 = iVar5 - iVar3, iVar4 == 0 || iVar5 < iVar3) {
          for (iVar3 = iVar3 + iVar4; iVar3 != 0; iVar3 = iVar3 + -1) {
            *pbVar8 = bVar1;
            pbVar8 = pbVar8 + 1;
          }
          piStack_24 = piStack_24 + 1;
          pbVar8 = (byte *)(*piStack_24 + param_2 + dword_d30d0);
          iVar3 = -iVar4;
          iVar5 = iVar2;
        }
        for (; iVar5 = iVar4, iVar3 != 0; iVar3 = iVar3 + -1) {
          *pbVar8 = bVar1;
          pbVar8 = pbVar8 + 1;
        }
      }
    }
    if (-1 < (char)bVar1) {
      return bVar1;
    }
    iVar3 = (int)(short)(ushort)(byte)-bVar1;
    do {
      iVar4 = iVar5 - iVar3;
      if (iVar4 != 0 && iVar3 <= iVar5) goto code_r0x000b4da9;
      for (iVar3 = iVar3 + iVar4; iVar3 != 0; iVar3 = iVar3 + -1) {
        *pbVar8 = *pbVar7;
        pbVar7 = pbVar7 + 1;
        pbVar8 = pbVar8 + 1;
      }
      piStack_24 = piStack_24 + 1;
      pbVar8 = (byte *)(*piStack_24 + param_2 + dword_d30d0);
      iVar3 = -iVar4;
      iVar5 = iVar2;
      pbVar6 = pbVar7;
    } while (-iVar4 != 0 && iVar4 < 1);
  } while( true );
code_r0x000b4da9:
  for (; iVar5 = iVar4, pbVar6 = pbVar7, iVar3 != 0; iVar3 = iVar3 + -1) {
    *pbVar8 = *pbVar7;
    pbVar7 = pbVar7 + 1;
    pbVar8 = pbVar8 + 1;
  }
  goto LAB_000b4d3c;
}


// ================================================================================================
// blit_rle_frame_home @ 0xb4cf2 [__cdecl]
// ================================================================================================

byte blit_rle_frame_home(int param_1)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  byte *pbVar7;
  byte *pbVar8;
  byte *pbVar9;
  bool bVar10;
  int *local_24;
  int iVar6;
  
  iVar2 = (int)*(short *)(param_1 + 0xc);
  iVar3 = (int)*(short *)(param_1 + 4);
  local_24 = (int *)(off_d30cc + *(short *)(param_1 + 0xe) * 4);
  pbVar9 = (byte *)(*local_24 + iVar2 + dword_d30d0);
  iVar6 = iVar3;
  pbVar7 = (byte *)(param_1 + 0x10);
LAB_000b4d3c:
  do {
    while( true ) {
      pbVar8 = pbVar7 + 1;
      bVar1 = *pbVar7;
      if ((char)bVar1 < '\x01') break;
      iVar4 = (int)(short)(ushort)bVar1;
      pbVar7 = pbVar7 + 2;
      bVar1 = *pbVar8;
      if (bVar1 == 0xff) {
        pbVar9 = pbVar9 + iVar4;
        iVar5 = iVar6 - iVar4;
        bVar10 = iVar6 < iVar4;
        iVar6 = iVar5;
        if (iVar5 == 0 || bVar10) {
          do {
            local_24 = local_24 + 1;
            bVar10 = SCARRY4(iVar5,iVar3);
            iVar5 = iVar5 + iVar3;
          } while (iVar5 == 0 || bVar10 != iVar5 < 0);
          pbVar9 = (byte *)((*local_24 + iVar2 + dword_d30d0 + iVar3) - iVar5);
          iVar6 = iVar5;
        }
      }
      else {
        while (iVar5 = iVar6 - iVar4, iVar5 == 0 || iVar6 < iVar4) {
          for (iVar4 = iVar4 + iVar5; iVar4 != 0; iVar4 = iVar4 + -1) {
            *pbVar9 = bVar1;
            pbVar9 = pbVar9 + 1;
          }
          local_24 = local_24 + 1;
          pbVar9 = (byte *)(*local_24 + iVar2 + dword_d30d0);
          iVar4 = -iVar5;
          iVar6 = iVar3;
        }
        for (; iVar6 = iVar5, iVar4 != 0; iVar4 = iVar4 + -1) {
          *pbVar9 = bVar1;
          pbVar9 = pbVar9 + 1;
        }
      }
    }
    if (-1 < (char)bVar1) {
      return bVar1;
    }
    iVar4 = (int)(short)(ushort)(byte)-bVar1;
    do {
      iVar5 = iVar6 - iVar4;
      if (iVar5 != 0 && iVar4 <= iVar6) goto code_r0x000b4da9;
      for (iVar4 = iVar4 + iVar5; iVar4 != 0; iVar4 = iVar4 + -1) {
        *pbVar9 = *pbVar8;
        pbVar8 = pbVar8 + 1;
        pbVar9 = pbVar9 + 1;
      }
      local_24 = local_24 + 1;
      pbVar9 = (byte *)(*local_24 + iVar2 + dword_d30d0);
      iVar4 = -iVar5;
      iVar6 = iVar3;
      pbVar7 = pbVar8;
    } while (-iVar5 != 0 && iVar5 < 1);
  } while( true );
code_r0x000b4da9:
  for (; iVar6 = iVar5, pbVar7 = pbVar8, iVar4 != 0; iVar4 = iVar4 + -1) {
    *pbVar9 = *pbVar8;
    pbVar8 = pbVar8 + 1;
    pbVar9 = pbVar9 + 1;
  }
  goto LAB_000b4d3c;
}


// ================================================================================================
// setremaptable @ 0xb4dd4 [__cdecl]
// ================================================================================================

void setremaptable(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = &unk_d42e4;
  for (iVar1 = 0x40; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = *param_1;
    param_1 = param_1 + 1;
    puVar2 = puVar2 + 1;
  }
  return;
}


// ================================================================================================
// sub_b4dec @ 0xb4dec [__watcall]
// ================================================================================================

void __watcall sub_b4dec(void)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *in_stack_00000004;
  
  puVar2 = &unk_d42e4;
  for (iVar1 = 0x40; iVar1 != 0; iVar1 = iVar1 + -1) {
    *in_stack_00000004 = *puVar2;
    puVar2 = puVar2 + 1;
    in_stack_00000004 = in_stack_00000004 + 1;
  }
  return;
}


// ================================================================================================
// sub_b4e04 @ 0xb4e04 [__watcall]
// ================================================================================================

void __watcall sub_b4e04(void)

{
  undefined4 *puVar1;
  int in_stack_00000004;
  uint in_stack_00000008;
  undefined4 *in_stack_0000000c;
  
  puVar1 = (undefined4 *)((int)&unk_d42e4 + in_stack_00000004);
  for (; (in_stack_00000008 & 3) != 0; in_stack_00000008 = in_stack_00000008 - 1) {
    *(undefined *)puVar1 = *(undefined *)in_stack_0000000c;
    in_stack_0000000c = (undefined4 *)((int)in_stack_0000000c + 1);
    puVar1 = (undefined4 *)((int)puVar1 + 1);
  }
  for (in_stack_00000008 = in_stack_00000008 >> 2; in_stack_00000008 != 0;
      in_stack_00000008 = in_stack_00000008 - 1) {
    *puVar1 = *in_stack_0000000c;
    in_stack_0000000c = in_stack_0000000c + 1;
    puVar1 = puVar1 + 1;
  }
  return;
}


// ================================================================================================
// sub_b4e2c @ 0xb4e2c [__watcall]
// ================================================================================================

byte __watcall sub_b4e2c(void)

{
  byte bVar1;
  undefined uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  byte *pbVar8;
  byte *pbVar9;
  undefined *puVar10;
  undefined *puVar11;
  bool bVar12;
  int in_stack_00000004;
  short in_stack_00000008;
  short in_stack_0000000c;
  int *piStack_24;
  
  iVar3 = (int)(short)(in_stack_00000008 - *(short *)(in_stack_00000004 + 8));
  iVar4 = (int)*(short *)(in_stack_00000004 + 4);
  piStack_24 = (int *)(off_d30cc +
                      (short)(in_stack_0000000c - *(short *)(in_stack_00000004 + 10)) * 4);
  puVar10 = (undefined *)(*piStack_24 + iVar3 + dword_d30d0);
  iVar6 = iVar4;
  pbVar9 = (byte *)(in_stack_00000004 + 0x10);
LAB_000b4eb4:
  do {
    while( true ) {
      pbVar8 = pbVar9 + 1;
      bVar1 = *pbVar9;
      if ((char)bVar1 < '\x01') break;
      iVar5 = (int)(short)(ushort)bVar1;
      pbVar9 = pbVar9 + 2;
      if (*pbVar8 == 0xff) {
        puVar10 = puVar10 + iVar5;
        iVar7 = iVar6 - iVar5;
        bVar12 = iVar6 < iVar5;
        iVar6 = iVar7;
        if (iVar7 == 0 || bVar12) {
          do {
            piStack_24 = piStack_24 + 1;
            bVar12 = SCARRY4(iVar7,iVar4);
            iVar7 = iVar7 + iVar4;
          } while (iVar7 == 0 || bVar12 != iVar7 < 0);
          puVar10 = (undefined *)((*piStack_24 + iVar3 + dword_d30d0 + iVar4) - iVar7);
          iVar6 = iVar7;
        }
      }
      else {
        uVar2 = *(undefined *)((int)&unk_d42e4 + (int)(short)(ushort)*pbVar8);
        while (iVar7 = iVar6 - iVar5, iVar7 == 0 || iVar6 < iVar5) {
          for (iVar5 = iVar5 + iVar7; iVar5 != 0; iVar5 = iVar5 + -1) {
            *puVar10 = uVar2;
            puVar10 = puVar10 + 1;
          }
          piStack_24 = piStack_24 + 1;
          puVar10 = (undefined *)(*piStack_24 + iVar3 + dword_d30d0);
          iVar5 = -iVar7;
          iVar6 = iVar4;
        }
        for (; iVar6 = iVar7, iVar5 != 0; iVar5 = iVar5 + -1) {
          *puVar10 = uVar2;
          puVar10 = puVar10 + 1;
        }
      }
    }
    if (-1 < (char)bVar1) {
      return bVar1;
    }
    iVar5 = (int)(short)(ushort)(byte)-bVar1;
    do {
      iVar7 = iVar6 - iVar5;
      puVar11 = puVar10;
      if (iVar7 != 0 && iVar5 <= iVar6) goto LAB_000b4f2a;
      iVar6 = iVar5 + iVar7;
      iVar5 = -iVar7;
      pbVar9 = pbVar8;
      do {
        pbVar8 = pbVar9 + 1;
        *puVar10 = *(undefined *)((int)&unk_d42e4 + (int)(short)(ushort)*pbVar9);
        iVar6 = iVar6 + -1;
        pbVar9 = pbVar8;
        puVar10 = puVar10 + 1;
      } while (iVar6 != 0);
      piStack_24 = piStack_24 + 1;
      puVar10 = (undefined *)(*piStack_24 + iVar3 + dword_d30d0);
      iVar6 = iVar4;
    } while (iVar5 != 0 && iVar7 < 1);
  } while( true );
LAB_000b4f2a:
  do {
    puVar10 = puVar11 + 1;
    *puVar11 = *(undefined *)((int)&unk_d42e4 + (int)(short)(ushort)*pbVar8);
    iVar5 = iVar5 + -1;
    iVar6 = iVar7;
    pbVar9 = pbVar8 + 1;
    pbVar8 = pbVar8 + 1;
    puVar11 = puVar10;
  } while (iVar5 != 0);
  goto LAB_000b4eb4;
}


// ================================================================================================
// sub_b4e50 @ 0xb4e50 [__cdecl]
// ================================================================================================

byte sub_b4e50(int param_1,int param_2,int param_3)

{
  byte bVar1;
  undefined uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  byte *pbVar7;
  byte *pbVar8;
  undefined *puVar9;
  undefined *puVar10;
  bool bVar11;
  int *piStack_24;
  
  iVar3 = (int)*(short *)(param_1 + 4);
  piStack_24 = (int *)(off_d30cc + param_3 * 4);
  puVar9 = (undefined *)(*piStack_24 + param_2 + dword_d30d0);
  iVar5 = iVar3;
  pbVar8 = (byte *)(param_1 + 0x10);
LAB_000b4eb4:
  do {
    while( true ) {
      pbVar7 = pbVar8 + 1;
      bVar1 = *pbVar8;
      if ((char)bVar1 < '\x01') break;
      iVar4 = (int)(short)(ushort)bVar1;
      pbVar8 = pbVar8 + 2;
      if (*pbVar7 == 0xff) {
        puVar9 = puVar9 + iVar4;
        iVar6 = iVar5 - iVar4;
        bVar11 = iVar5 < iVar4;
        iVar5 = iVar6;
        if (iVar6 == 0 || bVar11) {
          do {
            piStack_24 = piStack_24 + 1;
            bVar11 = SCARRY4(iVar6,iVar3);
            iVar6 = iVar6 + iVar3;
          } while (iVar6 == 0 || bVar11 != iVar6 < 0);
          puVar9 = (undefined *)((*piStack_24 + param_2 + dword_d30d0 + iVar3) - iVar6);
          iVar5 = iVar6;
        }
      }
      else {
        uVar2 = *(undefined *)((int)&unk_d42e4 + (int)(short)(ushort)*pbVar7);
        while (iVar6 = iVar5 - iVar4, iVar6 == 0 || iVar5 < iVar4) {
          for (iVar4 = iVar4 + iVar6; iVar4 != 0; iVar4 = iVar4 + -1) {
            *puVar9 = uVar2;
            puVar9 = puVar9 + 1;
          }
          piStack_24 = piStack_24 + 1;
          puVar9 = (undefined *)(*piStack_24 + param_2 + dword_d30d0);
          iVar4 = -iVar6;
          iVar5 = iVar3;
        }
        for (; iVar5 = iVar6, iVar4 != 0; iVar4 = iVar4 + -1) {
          *puVar9 = uVar2;
          puVar9 = puVar9 + 1;
        }
      }
    }
    if (-1 < (char)bVar1) {
      return bVar1;
    }
    iVar4 = (int)(short)(ushort)(byte)-bVar1;
    do {
      iVar6 = iVar5 - iVar4;
      puVar10 = puVar9;
      if (iVar6 != 0 && iVar4 <= iVar5) goto LAB_000b4f2a;
      iVar5 = iVar4 + iVar6;
      iVar4 = -iVar6;
      pbVar8 = pbVar7;
      do {
        pbVar7 = pbVar8 + 1;
        *puVar9 = *(undefined *)((int)&unk_d42e4 + (int)(short)(ushort)*pbVar8);
        iVar5 = iVar5 + -1;
        pbVar8 = pbVar7;
        puVar9 = puVar9 + 1;
      } while (iVar5 != 0);
      piStack_24 = piStack_24 + 1;
      puVar9 = (undefined *)(*piStack_24 + param_2 + dword_d30d0);
      iVar5 = iVar3;
    } while (iVar4 != 0 && iVar6 < 1);
  } while( true );
LAB_000b4f2a:
  do {
    puVar9 = puVar10 + 1;
    *puVar10 = *(undefined *)((int)&unk_d42e4 + (int)(short)(ushort)*pbVar7);
    iVar4 = iVar4 + -1;
    iVar5 = iVar6;
    pbVar8 = pbVar7 + 1;
    pbVar7 = pbVar7 + 1;
    puVar10 = puVar9;
  } while (iVar4 != 0);
  goto LAB_000b4eb4;
}


// ================================================================================================
// sub_b4e6a @ 0xb4e6a [__watcall]
// ================================================================================================

byte __watcall sub_b4e6a(void)

{
  byte bVar1;
  undefined uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  byte *pbVar8;
  byte *pbVar9;
  undefined *puVar10;
  undefined *puVar11;
  bool bVar12;
  int in_stack_00000004;
  int *local_24;
  
  iVar3 = (int)*(short *)(in_stack_00000004 + 0xc);
  iVar4 = (int)*(short *)(in_stack_00000004 + 4);
  local_24 = (int *)(off_d30cc + *(short *)(in_stack_00000004 + 0xe) * 4);
  puVar10 = (undefined *)(*local_24 + iVar3 + dword_d30d0);
  iVar6 = iVar4;
  pbVar9 = (byte *)(in_stack_00000004 + 0x10);
LAB_000b4eb4:
  do {
    while( true ) {
      pbVar8 = pbVar9 + 1;
      bVar1 = *pbVar9;
      if ((char)bVar1 < '\x01') break;
      iVar5 = (int)(short)(ushort)bVar1;
      pbVar9 = pbVar9 + 2;
      if (*pbVar8 == 0xff) {
        puVar10 = puVar10 + iVar5;
        iVar7 = iVar6 - iVar5;
        bVar12 = iVar6 < iVar5;
        iVar6 = iVar7;
        if (iVar7 == 0 || bVar12) {
          do {
            local_24 = local_24 + 1;
            bVar12 = SCARRY4(iVar7,iVar4);
            iVar7 = iVar7 + iVar4;
          } while (iVar7 == 0 || bVar12 != iVar7 < 0);
          puVar10 = (undefined *)((*local_24 + iVar3 + dword_d30d0 + iVar4) - iVar7);
          iVar6 = iVar7;
        }
      }
      else {
        uVar2 = *(undefined *)((int)&unk_d42e4 + (int)(short)(ushort)*pbVar8);
        while (iVar7 = iVar6 - iVar5, iVar7 == 0 || iVar6 < iVar5) {
          for (iVar5 = iVar5 + iVar7; iVar5 != 0; iVar5 = iVar5 + -1) {
            *puVar10 = uVar2;
            puVar10 = puVar10 + 1;
          }
          local_24 = local_24 + 1;
          puVar10 = (undefined *)(*local_24 + iVar3 + dword_d30d0);
          iVar5 = -iVar7;
          iVar6 = iVar4;
        }
        for (; iVar6 = iVar7, iVar5 != 0; iVar5 = iVar5 + -1) {
          *puVar10 = uVar2;
          puVar10 = puVar10 + 1;
        }
      }
    }
    if (-1 < (char)bVar1) {
      return bVar1;
    }
    iVar5 = (int)(short)(ushort)(byte)-bVar1;
    do {
      iVar7 = iVar6 - iVar5;
      puVar11 = puVar10;
      if (iVar7 != 0 && iVar5 <= iVar6) goto LAB_000b4f2a;
      iVar6 = iVar5 + iVar7;
      iVar5 = -iVar7;
      pbVar9 = pbVar8;
      do {
        pbVar8 = pbVar9 + 1;
        *puVar10 = *(undefined *)((int)&unk_d42e4 + (int)(short)(ushort)*pbVar9);
        iVar6 = iVar6 + -1;
        pbVar9 = pbVar8;
        puVar10 = puVar10 + 1;
      } while (iVar6 != 0);
      local_24 = local_24 + 1;
      puVar10 = (undefined *)(*local_24 + iVar3 + dword_d30d0);
      iVar6 = iVar4;
    } while (iVar5 != 0 && iVar7 < 1);
  } while( true );
LAB_000b4f2a:
  do {
    puVar10 = puVar11 + 1;
    *puVar11 = *(undefined *)((int)&unk_d42e4 + (int)(short)(ushort)*pbVar8);
    iVar5 = iVar5 + -1;
    iVar6 = iVar7;
    pbVar9 = pbVar8 + 1;
    pbVar8 = pbVar8 + 1;
    puVar11 = puVar10;
  } while (iVar5 != 0);
  goto LAB_000b4eb4;
}


// ================================================================================================
// setscreen @ 0xb4f70 [__cdecl]
// ================================================================================================

void setscreen(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = &dword_d30a4;
  for (iVar1 = 0xc; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = *param_1;
    param_1 = param_1 + 1;
    puVar2 = puVar2 + 1;
  }
  return;
}


// ================================================================================================
// windowdefp @ 0xb4f8c [__cdecl]
// ================================================================================================

undefined4 windowdefp(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)windowdef(param_1,param_2,param_3);
  return *puVar1;
}


// ================================================================================================
// sub_b4fac @ 0xb4fac [__cdecl]
// ================================================================================================

void sub_b4fac(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
              undefined4 param_5)

{
  int iVar1;
  undefined local_3c [24];
  int local_24;
  undefined4 local_20;
  
  iVar1 = sub_b40e2(param_1,param_2,param_3,param_4,local_3c);
  if ((iVar1 == 0) && (0 < local_24)) {
    local_20 = param_5;
    sub_9b498(local_3c);
  }
  return;
}


// ================================================================================================
// sub_b4fe8 @ 0xb4fe8 [__watcall]
// ================================================================================================

uint __watcall sub_b4fe8(void)

{
  byte bVar1;
  ushort uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  short sVar9;
  undefined2 uVar14;
  int iVar11;
  uint uVar12;
  byte *pbVar15;
  byte *pbVar16;
  byte *pbVar17;
  int iVar18;
  bool bVar19;
  int in_stack_00000004;
  short in_stack_00000008;
  short in_stack_0000000c;
  int *piStack_24;
  uint uStack_18;
  uint uStack_14;
  short sVar10;
  uint uVar13;
  
  iVar3 = (int)(short)(in_stack_00000008 - *(short *)(in_stack_00000004 + 8));
  iVar4 = (int)(short)(in_stack_0000000c - *(short *)(in_stack_00000004 + 10));
  pbVar16 = (byte *)(in_stack_00000004 + 0x10);
  uVar5 = (uint)*(short *)(in_stack_00000004 + 4);
  iVar18 = 0;
  uStack_18 = 0;
  uVar7 = (uint)*(short *)(in_stack_00000004 + 6);
  if (iVar4 < dword_d30b0) {
    iVar18 = 1;
    uVar6 = (iVar4 + uVar7) - dword_d30b0;
    if (uVar6 == 0 || (int)(iVar4 + uVar7) < dword_d30b0) {
      return uVar6;
    }
    uStack_18 = (uVar7 - uVar6) * uVar5;
    uVar7 = (dword_d30b0 + uVar6) - dword_d30b8;
    uStack_14 = uVar6;
    iVar4 = dword_d30b0;
    if ((uVar7 != 0 && dword_d30b8 <= (int)(dword_d30b0 + uVar6)) &&
       (uStack_14 = uVar6 - uVar7, uStack_14 == 0 || (int)uVar6 < (int)uVar7)) {
      return uVar7;
    }
  }
  else {
    uVar6 = (iVar4 + uVar7) - dword_d30b8;
    uStack_14 = uVar7;
    if (uVar6 != 0 && dword_d30b8 <= (int)(iVar4 + uVar7)) {
      iVar18 = 1;
      uStack_14 = uVar7 - uVar6;
      if (uVar7 - uVar6 == 0 || (int)uVar7 < (int)uVar6) {
        return uVar6;
      }
    }
  }
  if (iVar3 < dword_d30bc) {
    iVar18 = iVar18 + 1;
    uVar7 = (iVar3 + uVar5) - dword_d30bc;
    if (uVar7 == 0 || (int)(iVar3 + uVar5) < dword_d30bc) {
      return uVar7;
    }
    uStack_18 = uStack_18 + (uVar5 - uVar7);
    if (dword_d30c0 - dword_d30bc <= (int)uVar7) {
      uVar7 = dword_d30c0 - dword_d30bc;
    }
    uVar6 = uVar5 - uVar7;
    uVar5 = uVar7;
    iVar3 = dword_d30bc;
  }
  else {
    uVar7 = (iVar3 + uVar5) - dword_d30c0;
    uVar6 = 0;
    if (uVar7 != 0 && dword_d30c0 <= (int)(iVar3 + uVar5)) {
      if (uVar5 - uVar7 == 0 || (int)uVar5 < (int)uVar7) {
        return uVar7;
      }
      iVar18 = iVar18 + 1;
      uVar5 = uVar5 - uVar7;
      uVar6 = uVar7;
    }
  }
  if (iVar18 != 0) {
    piStack_24 = (int *)(off_d30cc + iVar4 * 4);
    pbVar17 = (byte *)(*piStack_24 + iVar3 + dword_d30d0);
    uVar13 = uVar5;
    if (uStack_18 == 0) goto LAB_000b5178;
    if ((int)uStack_18 < 0) {
      iVar18 = (uStack_18 & 0x7fff) + 1;
      uVar8 = uVar5;
      iVar4 = 0x7fff;
      do {
        while( true ) {
          bVar1 = *pbVar16;
          if ((char)bVar1 < '\x01') break;
          uVar7 = 0;
          uVar2 = (ushort)bVar1;
          uVar8 = CONCAT22((short)(uVar8 >> 0x10),uVar2);
          pbVar16 = pbVar16 + 2;
          sVar10 = (short)iVar4;
          uVar14 = (undefined2)((uint)iVar4 >> 0x10);
          sVar9 = sVar10 - uVar2;
          iVar4 = CONCAT22(uVar14,sVar9);
          if (sVar9 == 0 || sVar10 < (short)uVar2) {
            uVar12 = CONCAT22(uVar14,sVar9 + (short)iVar18);
            goto LAB_000b5271;
          }
        }
        if (-1 < (char)bVar1) {
          return (int)(short)CONCAT31((int3)(uVar7 >> 8),bVar1);
        }
        uVar7 = (uint)(byte)-bVar1;
        uVar8 = (uint)(short)(ushort)(byte)-bVar1;
        pbVar16 = pbVar16 + uVar8 + 1;
        iVar11 = iVar4 - uVar8;
        bVar19 = (int)uVar8 <= iVar4;
        iVar4 = iVar11;
      } while (iVar11 != 0 && bVar19);
      pbVar15 = pbVar16 + -uVar8;
      uStack_18 = iVar11 + uVar8 + iVar18;
      goto LAB_000b5242;
    }
LAB_000b525a:
    do {
      do {
        pbVar15 = pbVar16 + 1;
        bVar1 = *pbVar16;
        if ((char)bVar1 < '\x01') {
          if (-1 < (char)bVar1) {
            return (int)(short)CONCAT31((int3)(uVar7 >> 8),bVar1);
          }
          uVar7 = (uint)(byte)-bVar1;
          uVar8 = (uint)(short)(ushort)(byte)-bVar1;
          goto LAB_000b5242;
        }
        uVar7 = 0;
        uVar8 = (uint)(short)(ushort)bVar1;
        pbVar16 = pbVar16 + 2;
        uVar12 = uStack_18 - uVar8;
        bVar19 = (int)uVar8 <= (int)uStack_18;
        uStack_18 = uVar12;
      } while (uVar12 != 0 && bVar19);
LAB_000b5271:
      uVar7 = (uint)pbVar16[-1];
      if (pbVar16[-1] != 0xff) {
        uVar12 = uVar12 + uVar8;
        goto LAB_000b51bd;
      }
      do {
        uVar8 = uVar12 + uVar5;
        pbVar15 = pbVar16;
        if (uVar8 != 0 && SCARRY4(uVar12,uVar5) == (int)uVar8 < 0) {
          pbVar17 = (byte *)((*piStack_24 + iVar3 + dword_d30d0 + uVar5) - uVar8);
          uVar13 = uVar8;
LAB_000b5178:
          do {
            pbVar15 = pbVar16 + 1;
            bVar1 = *pbVar16;
            sVar9 = (short)CONCAT31((int3)(uVar7 >> 8),bVar1);
            if ((char)bVar1 < '\x01') {
              if (-1 < (char)bVar1) goto LAB_000b5183;
              uVar7 = (uint)(byte)-bVar1;
              iVar4 = (int)(short)(ushort)(byte)-bVar1;
              pbVar16 = pbVar15;
              while (uVar12 = uVar13 - iVar4, uVar12 == 0 || (int)uVar13 < iVar4) {
                uVar8 = -uVar12;
                pbVar15 = pbVar16;
                for (iVar4 = iVar4 + uVar12; iVar4 != 0; iVar4 = iVar4 + -1) {
                  *pbVar17 = *pbVar15;
                  pbVar15 = pbVar15 + 1;
                  pbVar17 = pbVar17 + 1;
                }
                uStack_14 = uStack_14 - 1;
                bVar19 = uStack_14 == 0;
                if (bVar19) goto LAB_000b51d6;
                piStack_24 = piStack_24 + 1;
                pbVar17 = (byte *)(*piStack_24 + iVar3 + dword_d30d0);
                uStack_18 = uVar6;
LAB_000b5242:
                pbVar16 = pbVar15 + uStack_18;
                iVar4 = uVar8 - uStack_18;
                uVar13 = uVar5;
                if (iVar4 == 0) goto LAB_000b5178;
                if ((int)uVar8 < (int)uStack_18) {
                  pbVar16 = pbVar16 + iVar4;
                  goto LAB_000b5256;
                }
              }
              for (; uVar13 = uVar12, iVar4 != 0; iVar4 = iVar4 + -1) {
                *pbVar17 = *pbVar16;
                pbVar16 = pbVar16 + 1;
                pbVar17 = pbVar17 + 1;
              }
              goto LAB_000b5178;
            }
            iVar4 = (int)(short)(ushort)bVar1;
            pbVar16 = pbVar16 + 2;
            bVar1 = *pbVar15;
            uVar7 = (uint)bVar1;
            if (bVar1 != 0xff) {
              while( true ) {
                sVar9 = (short)uVar7;
                uVar12 = uVar13 - iVar4;
                if (uVar12 != 0 && iVar4 <= (int)uVar13) break;
                uVar8 = -uVar12;
                for (iVar4 = iVar4 + uVar12; iVar4 != 0; iVar4 = iVar4 + -1) {
                  *pbVar17 = (byte)uVar7;
                  pbVar17 = pbVar17 + 1;
                }
                uStack_14 = uStack_14 - 1;
                if (uStack_14 == 0) goto LAB_000b5183;
                piStack_24 = piStack_24 + 1;
                pbVar17 = (byte *)(*piStack_24 + iVar3 + dword_d30d0);
                uVar12 = uVar6;
LAB_000b51bd:
                iVar4 = uVar8 - uVar12;
                uVar13 = uVar5;
                if (iVar4 == 0) goto LAB_000b5178;
                if ((int)uVar8 < (int)uVar12) goto LAB_000b5256;
              }
              for (; uVar13 = uVar12, iVar4 != 0; iVar4 = iVar4 + -1) {
                *pbVar17 = (byte)uVar7;
                pbVar17 = pbVar17 + 1;
              }
              goto LAB_000b5178;
            }
            pbVar17 = pbVar17 + iVar4;
            uVar8 = uVar13 - iVar4;
            bVar19 = iVar4 <= (int)uVar13;
            uVar13 = uVar8;
            pbVar15 = pbVar16;
          } while (uVar8 != 0 && bVar19);
        }
        uStack_14 = uStack_14 - 1;
        bVar19 = uStack_14 == 0;
LAB_000b51d6:
        sVar9 = (short)uVar7;
        if (bVar19) {
LAB_000b5183:
          return (int)sVar9;
        }
        piStack_24 = piStack_24 + 1;
        uVar12 = uVar8 + uVar6;
        pbVar16 = pbVar15;
      } while (uVar12 == 0 || SCARRY4(uVar8,uVar6) != (int)uVar12 < 0);
      pbVar17 = (byte *)(*piStack_24 + iVar3 + dword_d30d0);
      uStack_18 = uVar12;
    } while( true );
  }
  piStack_24 = (int *)(off_d30cc + iVar4 * 4);
  pbVar17 = (byte *)(*piStack_24 + iVar3 + dword_d30d0);
  uVar7 = uVar5;
LAB_000b4d3c:
  do {
    while( true ) {
      pbVar15 = pbVar16 + 1;
      bVar1 = *pbVar16;
      if ((char)bVar1 < '\x01') break;
      iVar4 = (int)(short)(ushort)bVar1;
      pbVar16 = pbVar16 + 2;
      bVar1 = *pbVar15;
      uVar6 = uVar7;
      if (bVar1 == 0xff) {
        pbVar17 = pbVar17 + iVar4;
        uVar6 = uVar7 - iVar4;
        bVar19 = (int)uVar7 < iVar4;
        uVar7 = uVar6;
        if (uVar6 == 0 || bVar19) {
          do {
            piStack_24 = piStack_24 + 1;
            bVar19 = SCARRY4(uVar6,uVar5);
            uVar6 = uVar6 + uVar5;
          } while (uVar6 == 0 || bVar19 != (int)uVar6 < 0);
          pbVar17 = (byte *)((*piStack_24 + iVar3 + dword_d30d0 + uVar5) - uVar6);
          uVar7 = uVar6;
        }
      }
      else {
        while (uVar7 = uVar6 - iVar4, uVar7 == 0 || (int)uVar6 < iVar4) {
          for (iVar4 = iVar4 + uVar7; iVar4 != 0; iVar4 = iVar4 + -1) {
            *pbVar17 = bVar1;
            pbVar17 = pbVar17 + 1;
          }
          piStack_24 = piStack_24 + 1;
          pbVar17 = (byte *)(*piStack_24 + iVar3 + dword_d30d0);
          iVar4 = -uVar7;
          uVar6 = uVar5;
        }
        for (; iVar4 != 0; iVar4 = iVar4 + -1) {
          *pbVar17 = bVar1;
          pbVar17 = pbVar17 + 1;
        }
      }
    }
    if (-1 < (char)bVar1) {
      return (int)(short)(ushort)bVar1;
    }
    iVar4 = (int)(short)(ushort)(byte)-bVar1;
    do {
      uVar6 = uVar7 - iVar4;
      if (uVar6 != 0 && iVar4 <= (int)uVar7) goto code_r0x000b4da9;
      for (iVar4 = iVar4 + uVar6; iVar4 != 0; iVar4 = iVar4 + -1) {
        *pbVar17 = *pbVar15;
        pbVar15 = pbVar15 + 1;
        pbVar17 = pbVar17 + 1;
      }
      piStack_24 = piStack_24 + 1;
      pbVar17 = (byte *)(*piStack_24 + iVar3 + dword_d30d0);
      iVar4 = -uVar6;
      uVar7 = uVar5;
      pbVar16 = pbVar15;
    } while (-uVar6 != 0 && (int)uVar6 < 1);
  } while( true );
LAB_000b5256:
  uVar7 = 0;
  uStack_18 = -iVar4;
  goto LAB_000b525a;
code_r0x000b4da9:
  for (; uVar7 = uVar6, pbVar16 = pbVar15, iVar4 != 0; iVar4 = iVar4 + -1) {
    *pbVar17 = *pbVar15;
    pbVar15 = pbVar15 + 1;
    pbVar17 = pbVar17 + 1;
  }
  goto LAB_000b4d3c;
}


// ================================================================================================
// sub_b500c @ 0xb500c [__cdecl]
// ================================================================================================

uint sub_b500c(int param_1,int param_2,int param_3)

{
  byte bVar1;
  ushort uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  short sVar7;
  undefined2 uVar12;
  int iVar9;
  uint uVar10;
  int iVar13;
  byte *pbVar14;
  byte *pbVar15;
  byte *pbVar16;
  int iVar17;
  bool bVar18;
  int *piStack_24;
  uint uStack_18;
  uint uStack_14;
  short sVar8;
  uint uVar11;
  
  pbVar15 = (byte *)(param_1 + 0x10);
  uVar3 = (uint)*(short *)(param_1 + 4);
  iVar17 = 0;
  uStack_18 = 0;
  uVar5 = (uint)*(short *)(param_1 + 6);
  if (param_3 < dword_d30b0) {
    iVar17 = 1;
    uVar4 = (param_3 + uVar5) - dword_d30b0;
    if (uVar4 == 0 || (int)(param_3 + uVar5) < dword_d30b0) {
      return uVar4;
    }
    uStack_18 = (uVar5 - uVar4) * uVar3;
    uVar5 = (dword_d30b0 + uVar4) - dword_d30b8;
    uStack_14 = uVar4;
    param_3 = dword_d30b0;
    if ((uVar5 != 0 && dword_d30b8 <= (int)(dword_d30b0 + uVar4)) &&
       (uStack_14 = uVar4 - uVar5, uStack_14 == 0 || (int)uVar4 < (int)uVar5)) {
      return uVar5;
    }
  }
  else {
    uVar4 = (param_3 + uVar5) - dword_d30b8;
    uStack_14 = uVar5;
    if (uVar4 != 0 && dword_d30b8 <= (int)(param_3 + uVar5)) {
      iVar17 = 1;
      uStack_14 = uVar5 - uVar4;
      if (uVar5 - uVar4 == 0 || (int)uVar5 < (int)uVar4) {
        return uVar4;
      }
    }
  }
  if (param_2 < dword_d30bc) {
    iVar17 = iVar17 + 1;
    uVar5 = (param_2 + uVar3) - dword_d30bc;
    if (uVar5 == 0 || (int)(param_2 + uVar3) < dword_d30bc) {
      return uVar5;
    }
    uStack_18 = uStack_18 + (uVar3 - uVar5);
    if (dword_d30c0 - dword_d30bc <= (int)uVar5) {
      uVar5 = dword_d30c0 - dword_d30bc;
    }
    uVar4 = uVar3 - uVar5;
    uVar3 = uVar5;
    param_2 = dword_d30bc;
  }
  else {
    uVar5 = (param_2 + uVar3) - dword_d30c0;
    uVar4 = 0;
    if (uVar5 != 0 && dword_d30c0 <= (int)(param_2 + uVar3)) {
      if (uVar3 - uVar5 == 0 || (int)uVar3 < (int)uVar5) {
        return uVar5;
      }
      iVar17 = iVar17 + 1;
      uVar3 = uVar3 - uVar5;
      uVar4 = uVar5;
    }
  }
  if (iVar17 != 0) {
    piStack_24 = (int *)(off_d30cc + param_3 * 4);
    pbVar16 = (byte *)(*piStack_24 + param_2 + dword_d30d0);
    uVar11 = uVar3;
    if (uStack_18 == 0) goto LAB_000b5178;
    if ((int)uStack_18 < 0) {
      iVar13 = (uStack_18 & 0x7fff) + 1;
      uVar6 = uVar3;
      iVar17 = 0x7fff;
      do {
        while( true ) {
          bVar1 = *pbVar15;
          if ((char)bVar1 < '\x01') break;
          uVar5 = 0;
          uVar2 = (ushort)bVar1;
          uVar6 = CONCAT22((short)(uVar6 >> 0x10),uVar2);
          pbVar15 = pbVar15 + 2;
          sVar8 = (short)iVar17;
          uVar12 = (undefined2)((uint)iVar17 >> 0x10);
          sVar7 = sVar8 - uVar2;
          iVar17 = CONCAT22(uVar12,sVar7);
          if (sVar7 == 0 || sVar8 < (short)uVar2) {
            uVar10 = CONCAT22(uVar12,sVar7 + (short)iVar13);
            goto LAB_000b5271;
          }
        }
        if (-1 < (char)bVar1) {
          return (int)(short)CONCAT31((int3)(uVar5 >> 8),bVar1);
        }
        uVar5 = (uint)(byte)-bVar1;
        uVar6 = (uint)(short)(ushort)(byte)-bVar1;
        pbVar15 = pbVar15 + uVar6 + 1;
        iVar9 = iVar17 - uVar6;
        bVar18 = (int)uVar6 <= iVar17;
        iVar17 = iVar9;
      } while (iVar9 != 0 && bVar18);
      pbVar14 = pbVar15 + -uVar6;
      uStack_18 = iVar9 + uVar6 + iVar13;
      goto LAB_000b5242;
    }
LAB_000b525a:
    do {
      do {
        pbVar14 = pbVar15 + 1;
        bVar1 = *pbVar15;
        if ((char)bVar1 < '\x01') {
          if (-1 < (char)bVar1) {
            return (int)(short)CONCAT31((int3)(uVar5 >> 8),bVar1);
          }
          uVar5 = (uint)(byte)-bVar1;
          uVar6 = (uint)(short)(ushort)(byte)-bVar1;
          goto LAB_000b5242;
        }
        uVar5 = 0;
        uVar6 = (uint)(short)(ushort)bVar1;
        pbVar15 = pbVar15 + 2;
        uVar10 = uStack_18 - uVar6;
        bVar18 = (int)uVar6 <= (int)uStack_18;
        uStack_18 = uVar10;
      } while (uVar10 != 0 && bVar18);
LAB_000b5271:
      uVar5 = (uint)pbVar15[-1];
      if (pbVar15[-1] != 0xff) {
        uVar10 = uVar10 + uVar6;
        goto LAB_000b51bd;
      }
      do {
        uVar6 = uVar10 + uVar3;
        pbVar14 = pbVar15;
        if (uVar6 != 0 && SCARRY4(uVar10,uVar3) == (int)uVar6 < 0) {
          pbVar16 = (byte *)((*piStack_24 + param_2 + dword_d30d0 + uVar3) - uVar6);
          uVar11 = uVar6;
LAB_000b5178:
          do {
            pbVar14 = pbVar15 + 1;
            bVar1 = *pbVar15;
            sVar7 = (short)CONCAT31((int3)(uVar5 >> 8),bVar1);
            if ((char)bVar1 < '\x01') {
              if (-1 < (char)bVar1) goto LAB_000b5183;
              uVar5 = (uint)(byte)-bVar1;
              iVar17 = (int)(short)(ushort)(byte)-bVar1;
              pbVar15 = pbVar14;
              while (uVar10 = uVar11 - iVar17, uVar10 == 0 || (int)uVar11 < iVar17) {
                uVar6 = -uVar10;
                pbVar14 = pbVar15;
                for (iVar17 = iVar17 + uVar10; iVar17 != 0; iVar17 = iVar17 + -1) {
                  *pbVar16 = *pbVar14;
                  pbVar14 = pbVar14 + 1;
                  pbVar16 = pbVar16 + 1;
                }
                uStack_14 = uStack_14 - 1;
                bVar18 = uStack_14 == 0;
                if (bVar18) goto LAB_000b51d6;
                piStack_24 = piStack_24 + 1;
                pbVar16 = (byte *)(*piStack_24 + param_2 + dword_d30d0);
                uStack_18 = uVar4;
LAB_000b5242:
                pbVar15 = pbVar14 + uStack_18;
                iVar17 = uVar6 - uStack_18;
                uVar11 = uVar3;
                if (iVar17 == 0) goto LAB_000b5178;
                if ((int)uVar6 < (int)uStack_18) {
                  pbVar15 = pbVar15 + iVar17;
                  goto LAB_000b5256;
                }
              }
              for (; uVar11 = uVar10, iVar17 != 0; iVar17 = iVar17 + -1) {
                *pbVar16 = *pbVar15;
                pbVar15 = pbVar15 + 1;
                pbVar16 = pbVar16 + 1;
              }
              goto LAB_000b5178;
            }
            iVar17 = (int)(short)(ushort)bVar1;
            pbVar15 = pbVar15 + 2;
            bVar1 = *pbVar14;
            uVar5 = (uint)bVar1;
            if (bVar1 != 0xff) {
              while( true ) {
                sVar7 = (short)uVar5;
                uVar10 = uVar11 - iVar17;
                if (uVar10 != 0 && iVar17 <= (int)uVar11) break;
                uVar6 = -uVar10;
                for (iVar17 = iVar17 + uVar10; iVar17 != 0; iVar17 = iVar17 + -1) {
                  *pbVar16 = (byte)uVar5;
                  pbVar16 = pbVar16 + 1;
                }
                uStack_14 = uStack_14 - 1;
                if (uStack_14 == 0) goto LAB_000b5183;
                piStack_24 = piStack_24 + 1;
                pbVar16 = (byte *)(*piStack_24 + param_2 + dword_d30d0);
                uVar10 = uVar4;
LAB_000b51bd:
                iVar17 = uVar6 - uVar10;
                uVar11 = uVar3;
                if (iVar17 == 0) goto LAB_000b5178;
                if ((int)uVar6 < (int)uVar10) goto LAB_000b5256;
              }
              for (; uVar11 = uVar10, iVar17 != 0; iVar17 = iVar17 + -1) {
                *pbVar16 = (byte)uVar5;
                pbVar16 = pbVar16 + 1;
              }
              goto LAB_000b5178;
            }
            pbVar16 = pbVar16 + iVar17;
            uVar6 = uVar11 - iVar17;
            bVar18 = iVar17 <= (int)uVar11;
            uVar11 = uVar6;
            pbVar14 = pbVar15;
          } while (uVar6 != 0 && bVar18);
        }
        uStack_14 = uStack_14 - 1;
        bVar18 = uStack_14 == 0;
LAB_000b51d6:
        sVar7 = (short)uVar5;
        if (bVar18) {
LAB_000b5183:
          return (int)sVar7;
        }
        piStack_24 = piStack_24 + 1;
        uVar10 = uVar6 + uVar4;
        pbVar15 = pbVar14;
      } while (uVar10 == 0 || SCARRY4(uVar6,uVar4) != (int)uVar10 < 0);
      pbVar16 = (byte *)(*piStack_24 + param_2 + dword_d30d0);
      uStack_18 = uVar10;
    } while( true );
  }
  piStack_24 = (int *)(off_d30cc + param_3 * 4);
  pbVar16 = (byte *)(*piStack_24 + param_2 + dword_d30d0);
  uVar5 = uVar3;
LAB_000b4d3c:
  do {
    while( true ) {
      pbVar14 = pbVar15 + 1;
      bVar1 = *pbVar15;
      if ((char)bVar1 < '\x01') break;
      iVar17 = (int)(short)(ushort)bVar1;
      pbVar15 = pbVar15 + 2;
      bVar1 = *pbVar14;
      uVar4 = uVar5;
      if (bVar1 == 0xff) {
        pbVar16 = pbVar16 + iVar17;
        uVar4 = uVar5 - iVar17;
        bVar18 = (int)uVar5 < iVar17;
        uVar5 = uVar4;
        if (uVar4 == 0 || bVar18) {
          do {
            piStack_24 = piStack_24 + 1;
            bVar18 = SCARRY4(uVar4,uVar3);
            uVar4 = uVar4 + uVar3;
          } while (uVar4 == 0 || bVar18 != (int)uVar4 < 0);
          pbVar16 = (byte *)((*piStack_24 + param_2 + dword_d30d0 + uVar3) - uVar4);
          uVar5 = uVar4;
        }
      }
      else {
        while (uVar5 = uVar4 - iVar17, uVar5 == 0 || (int)uVar4 < iVar17) {
          for (iVar17 = iVar17 + uVar5; iVar17 != 0; iVar17 = iVar17 + -1) {
            *pbVar16 = bVar1;
            pbVar16 = pbVar16 + 1;
          }
          piStack_24 = piStack_24 + 1;
          pbVar16 = (byte *)(*piStack_24 + param_2 + dword_d30d0);
          iVar17 = -uVar5;
          uVar4 = uVar3;
        }
        for (; iVar17 != 0; iVar17 = iVar17 + -1) {
          *pbVar16 = bVar1;
          pbVar16 = pbVar16 + 1;
        }
      }
    }
    if (-1 < (char)bVar1) {
      return (int)(short)(ushort)bVar1;
    }
    iVar17 = (int)(short)(ushort)(byte)-bVar1;
    do {
      uVar4 = uVar5 - iVar17;
      if (uVar4 != 0 && iVar17 <= (int)uVar5) goto code_r0x000b4da9;
      for (iVar17 = iVar17 + uVar4; iVar17 != 0; iVar17 = iVar17 + -1) {
        *pbVar16 = *pbVar14;
        pbVar14 = pbVar14 + 1;
        pbVar16 = pbVar16 + 1;
      }
      piStack_24 = piStack_24 + 1;
      pbVar16 = (byte *)(*piStack_24 + param_2 + dword_d30d0);
      iVar17 = -uVar4;
      uVar5 = uVar3;
      pbVar15 = pbVar14;
    } while (-uVar4 != 0 && (int)uVar4 < 1);
  } while( true );
LAB_000b5256:
  uVar5 = 0;
  uStack_18 = -iVar17;
  goto LAB_000b525a;
code_r0x000b4da9:
  for (; uVar5 = uVar4, pbVar15 = pbVar14, iVar17 != 0; iVar17 = iVar17 + -1) {
    *pbVar16 = *pbVar14;
    pbVar14 = pbVar14 + 1;
    pbVar16 = pbVar16 + 1;
  }
  goto LAB_000b4d3c;
}


// ================================================================================================
// sub_b5026 @ 0xb5026 [__watcall]
// ================================================================================================

uint __watcall sub_b5026(void)

{
  byte bVar1;
  ushort uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  short sVar9;
  undefined2 uVar14;
  int iVar11;
  uint uVar12;
  byte *pbVar15;
  byte *pbVar16;
  byte *pbVar17;
  int iVar18;
  bool bVar19;
  int in_stack_00000004;
  int *local_24;
  uint local_18;
  uint local_14;
  short sVar10;
  uint uVar13;
  
  iVar3 = (int)*(short *)(in_stack_00000004 + 0xc);
  iVar4 = (int)*(short *)(in_stack_00000004 + 0xe);
  pbVar16 = (byte *)(in_stack_00000004 + 0x10);
  uVar5 = (uint)*(short *)(in_stack_00000004 + 4);
  iVar18 = 0;
  local_18 = 0;
  uVar7 = (uint)*(short *)(in_stack_00000004 + 6);
  if (iVar4 < dword_d30b0) {
    iVar18 = 1;
    uVar6 = (iVar4 + uVar7) - dword_d30b0;
    if (uVar6 == 0 || (int)(iVar4 + uVar7) < dword_d30b0) {
      return uVar6;
    }
    local_18 = (uVar7 - uVar6) * uVar5;
    uVar7 = (dword_d30b0 + uVar6) - dword_d30b8;
    local_14 = uVar6;
    iVar4 = dword_d30b0;
    if ((uVar7 != 0 && dword_d30b8 <= (int)(dword_d30b0 + uVar6)) &&
       (local_14 = uVar6 - uVar7, local_14 == 0 || (int)uVar6 < (int)uVar7)) {
      return uVar7;
    }
  }
  else {
    uVar6 = (iVar4 + uVar7) - dword_d30b8;
    local_14 = uVar7;
    if (uVar6 != 0 && dword_d30b8 <= (int)(iVar4 + uVar7)) {
      iVar18 = 1;
      local_14 = uVar7 - uVar6;
      if (uVar7 - uVar6 == 0 || (int)uVar7 < (int)uVar6) {
        return uVar6;
      }
    }
  }
  if (iVar3 < dword_d30bc) {
    iVar18 = iVar18 + 1;
    uVar7 = (iVar3 + uVar5) - dword_d30bc;
    if (uVar7 == 0 || (int)(iVar3 + uVar5) < dword_d30bc) {
      return uVar7;
    }
    local_18 = local_18 + (uVar5 - uVar7);
    if (dword_d30c0 - dword_d30bc <= (int)uVar7) {
      uVar7 = dword_d30c0 - dword_d30bc;
    }
    uVar6 = uVar5 - uVar7;
    uVar5 = uVar7;
    iVar3 = dword_d30bc;
  }
  else {
    uVar7 = (iVar3 + uVar5) - dword_d30c0;
    uVar6 = 0;
    if (uVar7 != 0 && dword_d30c0 <= (int)(iVar3 + uVar5)) {
      if (uVar5 - uVar7 == 0 || (int)uVar5 < (int)uVar7) {
        return uVar7;
      }
      iVar18 = iVar18 + 1;
      uVar5 = uVar5 - uVar7;
      uVar6 = uVar7;
    }
  }
  if (iVar18 != 0) {
    local_24 = (int *)(off_d30cc + iVar4 * 4);
    pbVar17 = (byte *)(*local_24 + iVar3 + dword_d30d0);
    uVar13 = uVar5;
    if (local_18 == 0) goto LAB_000b5178;
    if ((int)local_18 < 0) {
      iVar18 = (local_18 & 0x7fff) + 1;
      uVar8 = uVar5;
      iVar4 = 0x7fff;
      do {
        while( true ) {
          bVar1 = *pbVar16;
          if ((char)bVar1 < '\x01') break;
          uVar7 = 0;
          uVar2 = (ushort)bVar1;
          uVar8 = CONCAT22((short)(uVar8 >> 0x10),uVar2);
          pbVar16 = pbVar16 + 2;
          sVar10 = (short)iVar4;
          uVar14 = (undefined2)((uint)iVar4 >> 0x10);
          sVar9 = sVar10 - uVar2;
          iVar4 = CONCAT22(uVar14,sVar9);
          if (sVar9 == 0 || sVar10 < (short)uVar2) {
            uVar12 = CONCAT22(uVar14,sVar9 + (short)iVar18);
            goto LAB_000b5271;
          }
        }
        if (-1 < (char)bVar1) {
          return (int)(short)CONCAT31((int3)(uVar7 >> 8),bVar1);
        }
        uVar7 = (uint)(byte)-bVar1;
        uVar8 = (uint)(short)(ushort)(byte)-bVar1;
        pbVar16 = pbVar16 + uVar8 + 1;
        iVar11 = iVar4 - uVar8;
        bVar19 = (int)uVar8 <= iVar4;
        iVar4 = iVar11;
      } while (iVar11 != 0 && bVar19);
      pbVar15 = pbVar16 + -uVar8;
      local_18 = iVar11 + uVar8 + iVar18;
      goto LAB_000b5242;
    }
LAB_000b525a:
    do {
      do {
        pbVar15 = pbVar16 + 1;
        bVar1 = *pbVar16;
        if ((char)bVar1 < '\x01') {
          if (-1 < (char)bVar1) {
            return (int)(short)CONCAT31((int3)(uVar7 >> 8),bVar1);
          }
          uVar7 = (uint)(byte)-bVar1;
          uVar8 = (uint)(short)(ushort)(byte)-bVar1;
          goto LAB_000b5242;
        }
        uVar7 = 0;
        uVar8 = (uint)(short)(ushort)bVar1;
        pbVar16 = pbVar16 + 2;
        uVar12 = local_18 - uVar8;
        bVar19 = (int)uVar8 <= (int)local_18;
        local_18 = uVar12;
      } while (uVar12 != 0 && bVar19);
LAB_000b5271:
      uVar7 = (uint)pbVar16[-1];
      if (pbVar16[-1] != 0xff) {
        uVar12 = uVar12 + uVar8;
        goto LAB_000b51bd;
      }
      do {
        uVar8 = uVar12 + uVar5;
        pbVar15 = pbVar16;
        if (uVar8 != 0 && SCARRY4(uVar12,uVar5) == (int)uVar8 < 0) {
          pbVar17 = (byte *)((*local_24 + iVar3 + dword_d30d0 + uVar5) - uVar8);
          uVar13 = uVar8;
LAB_000b5178:
          do {
            pbVar15 = pbVar16 + 1;
            bVar1 = *pbVar16;
            sVar9 = (short)CONCAT31((int3)(uVar7 >> 8),bVar1);
            if ((char)bVar1 < '\x01') {
              if (-1 < (char)bVar1) goto LAB_000b5183;
              uVar7 = (uint)(byte)-bVar1;
              iVar4 = (int)(short)(ushort)(byte)-bVar1;
              pbVar16 = pbVar15;
              while (uVar12 = uVar13 - iVar4, uVar12 == 0 || (int)uVar13 < iVar4) {
                uVar8 = -uVar12;
                pbVar15 = pbVar16;
                for (iVar4 = iVar4 + uVar12; iVar4 != 0; iVar4 = iVar4 + -1) {
                  *pbVar17 = *pbVar15;
                  pbVar15 = pbVar15 + 1;
                  pbVar17 = pbVar17 + 1;
                }
                local_14 = local_14 - 1;
                bVar19 = local_14 == 0;
                if (bVar19) goto LAB_000b51d6;
                local_24 = local_24 + 1;
                pbVar17 = (byte *)(*local_24 + iVar3 + dword_d30d0);
                local_18 = uVar6;
LAB_000b5242:
                pbVar16 = pbVar15 + local_18;
                iVar4 = uVar8 - local_18;
                uVar13 = uVar5;
                if (iVar4 == 0) goto LAB_000b5178;
                if ((int)uVar8 < (int)local_18) {
                  pbVar16 = pbVar16 + iVar4;
                  goto LAB_000b5256;
                }
              }
              for (; uVar13 = uVar12, iVar4 != 0; iVar4 = iVar4 + -1) {
                *pbVar17 = *pbVar16;
                pbVar16 = pbVar16 + 1;
                pbVar17 = pbVar17 + 1;
              }
              goto LAB_000b5178;
            }
            iVar4 = (int)(short)(ushort)bVar1;
            pbVar16 = pbVar16 + 2;
            bVar1 = *pbVar15;
            uVar7 = (uint)bVar1;
            if (bVar1 != 0xff) {
              while( true ) {
                sVar9 = (short)uVar7;
                uVar12 = uVar13 - iVar4;
                if (uVar12 != 0 && iVar4 <= (int)uVar13) break;
                uVar8 = -uVar12;
                for (iVar4 = iVar4 + uVar12; iVar4 != 0; iVar4 = iVar4 + -1) {
                  *pbVar17 = (byte)uVar7;
                  pbVar17 = pbVar17 + 1;
                }
                local_14 = local_14 - 1;
                if (local_14 == 0) goto LAB_000b5183;
                local_24 = local_24 + 1;
                pbVar17 = (byte *)(*local_24 + iVar3 + dword_d30d0);
                uVar12 = uVar6;
LAB_000b51bd:
                iVar4 = uVar8 - uVar12;
                uVar13 = uVar5;
                if (iVar4 == 0) goto LAB_000b5178;
                if ((int)uVar8 < (int)uVar12) goto LAB_000b5256;
              }
              for (; uVar13 = uVar12, iVar4 != 0; iVar4 = iVar4 + -1) {
                *pbVar17 = (byte)uVar7;
                pbVar17 = pbVar17 + 1;
              }
              goto LAB_000b5178;
            }
            pbVar17 = pbVar17 + iVar4;
            uVar8 = uVar13 - iVar4;
            bVar19 = iVar4 <= (int)uVar13;
            uVar13 = uVar8;
            pbVar15 = pbVar16;
          } while (uVar8 != 0 && bVar19);
        }
        local_14 = local_14 - 1;
        bVar19 = local_14 == 0;
LAB_000b51d6:
        sVar9 = (short)uVar7;
        if (bVar19) {
LAB_000b5183:
          return (int)sVar9;
        }
        local_24 = local_24 + 1;
        uVar12 = uVar8 + uVar6;
        pbVar16 = pbVar15;
      } while (uVar12 == 0 || SCARRY4(uVar8,uVar6) != (int)uVar12 < 0);
      pbVar17 = (byte *)(*local_24 + iVar3 + dword_d30d0);
      local_18 = uVar12;
    } while( true );
  }
  local_24 = (int *)(off_d30cc + iVar4 * 4);
  pbVar17 = (byte *)(*local_24 + iVar3 + dword_d30d0);
  uVar7 = uVar5;
LAB_000b4d3c:
  do {
    while( true ) {
      pbVar15 = pbVar16 + 1;
      bVar1 = *pbVar16;
      if ((char)bVar1 < '\x01') break;
      iVar4 = (int)(short)(ushort)bVar1;
      pbVar16 = pbVar16 + 2;
      bVar1 = *pbVar15;
      uVar6 = uVar7;
      if (bVar1 == 0xff) {
        pbVar17 = pbVar17 + iVar4;
        uVar6 = uVar7 - iVar4;
        bVar19 = (int)uVar7 < iVar4;
        uVar7 = uVar6;
        if (uVar6 == 0 || bVar19) {
          do {
            local_24 = local_24 + 1;
            bVar19 = SCARRY4(uVar6,uVar5);
            uVar6 = uVar6 + uVar5;
          } while (uVar6 == 0 || bVar19 != (int)uVar6 < 0);
          pbVar17 = (byte *)((*local_24 + iVar3 + dword_d30d0 + uVar5) - uVar6);
          uVar7 = uVar6;
        }
      }
      else {
        while (uVar7 = uVar6 - iVar4, uVar7 == 0 || (int)uVar6 < iVar4) {
          for (iVar4 = iVar4 + uVar7; iVar4 != 0; iVar4 = iVar4 + -1) {
            *pbVar17 = bVar1;
            pbVar17 = pbVar17 + 1;
          }
          local_24 = local_24 + 1;
          pbVar17 = (byte *)(*local_24 + iVar3 + dword_d30d0);
          iVar4 = -uVar7;
          uVar6 = uVar5;
        }
        for (; iVar4 != 0; iVar4 = iVar4 + -1) {
          *pbVar17 = bVar1;
          pbVar17 = pbVar17 + 1;
        }
      }
    }
    if (-1 < (char)bVar1) {
      return (int)(short)(ushort)bVar1;
    }
    iVar4 = (int)(short)(ushort)(byte)-bVar1;
    do {
      uVar6 = uVar7 - iVar4;
      if (uVar6 != 0 && iVar4 <= (int)uVar7) goto code_r0x000b4da9;
      for (iVar4 = iVar4 + uVar6; iVar4 != 0; iVar4 = iVar4 + -1) {
        *pbVar17 = *pbVar15;
        pbVar15 = pbVar15 + 1;
        pbVar17 = pbVar17 + 1;
      }
      local_24 = local_24 + 1;
      pbVar17 = (byte *)(*local_24 + iVar3 + dword_d30d0);
      iVar4 = -uVar6;
      uVar7 = uVar5;
      pbVar16 = pbVar15;
    } while (-uVar6 != 0 && (int)uVar6 < 1);
  } while( true );
LAB_000b5256:
  uVar7 = 0;
  local_18 = -iVar4;
  goto LAB_000b525a;
code_r0x000b4da9:
  for (; uVar7 = uVar6, pbVar16 = pbVar15, iVar4 != 0; iVar4 = iVar4 + -1) {
    *pbVar17 = *pbVar15;
    pbVar15 = pbVar15 + 1;
    pbVar17 = pbVar17 + 1;
  }
  goto LAB_000b4d3c;
}


// ================================================================================================
// sub_b5290 @ 0xb5290 [__watcall]
// ================================================================================================

uint __watcall sub_b5290(void)

{
  byte bVar1;
  undefined uVar2;
  short sVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  int iVar10;
  int iVar11;
  uint uVar12;
  uint uVar13;
  byte *pbVar14;
  byte *pbVar15;
  undefined *puVar16;
  undefined *puVar17;
  int iVar18;
  byte *pbVar19;
  byte *pbVar20;
  bool bVar21;
  int in_stack_00000004;
  short in_stack_00000008;
  short in_stack_0000000c;
  int *piStack_24;
  uint uStack_18;
  uint uStack_14;
  
  iVar4 = (int)(short)(in_stack_00000008 - *(short *)(in_stack_00000004 + 8));
  iVar5 = (int)(short)(in_stack_0000000c - *(short *)(in_stack_00000004 + 10));
  pbVar15 = (byte *)(in_stack_00000004 + 0x10);
  uVar6 = (uint)*(short *)(in_stack_00000004 + 4);
  iVar18 = 0;
  uStack_18 = 0;
  uVar8 = (uint)*(short *)(in_stack_00000004 + 6);
  if (iVar5 < dword_d30b0) {
    iVar18 = 1;
    uVar7 = (iVar5 + uVar8) - dword_d30b0;
    if (uVar7 == 0 || (int)(iVar5 + uVar8) < dword_d30b0) {
      return uVar7;
    }
    uStack_18 = (uVar8 - uVar7) * uVar6;
    uVar8 = (dword_d30b0 + uVar7) - dword_d30b8;
    uStack_14 = uVar7;
    iVar5 = dword_d30b0;
    if ((uVar8 != 0 && dword_d30b8 <= (int)(dword_d30b0 + uVar7)) &&
       (uStack_14 = uVar7 - uVar8, uStack_14 == 0 || (int)uVar7 < (int)uVar8)) {
      return uVar8;
    }
  }
  else {
    uVar7 = (iVar5 + uVar8) - dword_d30b8;
    uStack_14 = uVar8;
    if (uVar7 != 0 && dword_d30b8 <= (int)(iVar5 + uVar8)) {
      iVar18 = 1;
      uStack_14 = uVar8 - uVar7;
      if (uVar8 - uVar7 == 0 || (int)uVar8 < (int)uVar7) {
        return uVar7;
      }
    }
  }
  if (iVar4 < dword_d30bc) {
    iVar18 = iVar18 + 1;
    uVar8 = (iVar4 + uVar6) - dword_d30bc;
    if (uVar8 == 0 || (int)(iVar4 + uVar6) < dword_d30bc) {
      return uVar8;
    }
    uStack_18 = uStack_18 + (uVar6 - uVar8);
    if (dword_d30c0 - dword_d30bc <= (int)uVar8) {
      uVar8 = dword_d30c0 - dword_d30bc;
    }
    uVar7 = uVar6 - uVar8;
    uVar6 = uVar8;
    iVar4 = dword_d30bc;
  }
  else {
    uVar8 = (iVar4 + uVar6) - dword_d30c0;
    uVar7 = 0;
    if (uVar8 != 0 && dword_d30c0 <= (int)(iVar4 + uVar6)) {
      if (uVar6 - uVar8 == 0 || (int)uVar6 < (int)uVar8) {
        return uVar8;
      }
      iVar18 = iVar18 + 1;
      uVar6 = uVar6 - uVar8;
      uVar7 = uVar8;
    }
  }
  if (iVar18 != 0) {
    piStack_24 = (int *)(off_d30cc + iVar5 * 4);
    pbVar19 = (byte *)(*piStack_24 + iVar4 + dword_d30d0);
    uVar13 = uVar6;
    if (uStack_18 == 0) goto LAB_000b541e;
    if ((int)uStack_18 < 0) {
      iVar18 = (uStack_18 & 0x7fff) + 1;
      iVar5 = 0x7fff;
      do {
        while( true ) {
          bVar1 = *pbVar15;
          if ((char)bVar1 < '\x01') break;
          uVar8 = 0;
          iVar11 = (int)(short)(ushort)bVar1;
          pbVar15 = pbVar15 + 2;
          iVar10 = iVar5 - iVar11;
          bVar21 = iVar5 < iVar11;
          iVar5 = iVar10;
          if (iVar10 == 0 || bVar21) {
            uVar12 = iVar10 + iVar18;
            goto LAB_000b5536;
          }
        }
        if (-1 < (char)bVar1) {
          return (int)(short)CONCAT31((int3)(uVar8 >> 8),bVar1);
        }
        uVar8 = 0;
        uVar9 = (uint)(short)(ushort)(byte)-bVar1;
        pbVar15 = pbVar15 + uVar9 + 1;
        iVar11 = iVar5 - uVar9;
        bVar21 = (int)uVar9 <= iVar5;
        iVar5 = iVar11;
      } while (iVar11 != 0 && bVar21);
      pbVar14 = pbVar15 + -uVar9;
      uStack_18 = iVar11 + uVar9 + iVar18;
      goto LAB_000b5507;
    }
LAB_000b551f:
    do {
      do {
        pbVar14 = pbVar15 + 1;
        bVar1 = *pbVar15;
        if ((char)bVar1 < '\x01') {
          if (-1 < (char)bVar1) {
            return (int)(short)CONCAT31((int3)(uVar8 >> 8),bVar1);
          }
          uVar9 = (uint)(short)(ushort)(byte)-bVar1;
          goto LAB_000b5507;
        }
        uVar8 = 0;
        iVar11 = (int)(short)(ushort)bVar1;
        pbVar15 = pbVar15 + 2;
        uVar12 = uStack_18 - iVar11;
        bVar21 = iVar11 <= (int)uStack_18;
        uStack_18 = uVar12;
      } while (uVar12 != 0 && bVar21);
LAB_000b5536:
      bVar1 = pbVar15[-1];
      uVar8 = (uint)bVar1;
      if (bVar1 != 0xff) {
        uVar8 = (uint)*(byte *)((int)&unk_d42e4 + (int)(short)(ushort)bVar1);
        uVar12 = uVar12 + iVar11;
        goto LAB_000b546c;
      }
      do {
        uVar9 = uVar12 + uVar6;
        pbVar14 = pbVar15;
        if (uVar9 != 0 && SCARRY4(uVar12,uVar6) == (int)uVar9 < 0) {
          pbVar19 = (byte *)((*piStack_24 + iVar4 + dword_d30d0 + uVar6) - uVar9);
          uVar13 = uVar9;
LAB_000b541e:
          do {
            pbVar14 = pbVar15 + 1;
            bVar1 = *pbVar15;
            sVar3 = (short)CONCAT31((int3)(uVar8 >> 8),bVar1);
            if ((char)bVar1 < '\x01') {
              if (-1 < (char)bVar1) goto LAB_000b5429;
              iVar5 = (int)(short)(ushort)(byte)-bVar1;
              pbVar15 = pbVar14;
              while (uVar9 = uVar13 - iVar5, pbVar14 = pbVar15, pbVar20 = pbVar19,
                    uVar9 == 0 || (int)uVar13 < iVar5) {
                iVar5 = iVar5 + uVar9;
                uVar9 = -uVar9;
                do {
                  pbVar14 = pbVar15 + 1;
                  uVar8 = (uint)*(byte *)((int)&unk_d42e4 + (int)(short)(ushort)*pbVar15);
                  *pbVar19 = *(byte *)((int)&unk_d42e4 + (int)(short)(ushort)*pbVar15);
                  iVar5 = iVar5 + -1;
                  pbVar15 = pbVar14;
                  pbVar19 = pbVar19 + 1;
                } while (iVar5 != 0);
                uStack_14 = uStack_14 - 1;
                bVar21 = uStack_14 == 0;
                if (bVar21) goto LAB_000b5485;
                piStack_24 = piStack_24 + 1;
                pbVar19 = (byte *)(*piStack_24 + iVar4 + dword_d30d0);
                uStack_18 = uVar7;
LAB_000b5507:
                uVar8 = 0;
                pbVar15 = pbVar14 + uStack_18;
                iVar5 = uVar9 - uStack_18;
                uVar13 = uVar6;
                if (iVar5 == 0) goto LAB_000b541e;
                if ((int)uVar9 < (int)uStack_18) {
                  pbVar15 = pbVar15 + iVar5;
                  goto LAB_000b551b;
                }
              }
              do {
                pbVar15 = pbVar14 + 1;
                uVar8 = 0;
                pbVar19 = pbVar20 + 1;
                *pbVar20 = *(byte *)((int)&unk_d42e4 + (int)(short)(ushort)*pbVar14);
                iVar5 = iVar5 + -1;
                uVar13 = uVar9;
                pbVar14 = pbVar15;
                pbVar20 = pbVar19;
              } while (iVar5 != 0);
              goto LAB_000b541e;
            }
            iVar5 = (int)(short)(ushort)bVar1;
            pbVar15 = pbVar15 + 2;
            bVar1 = *pbVar14;
            uVar8 = (uint)bVar1;
            if (bVar1 != 0xff) {
              uVar8 = (uint)*(byte *)((int)&unk_d42e4 + (int)(short)(ushort)bVar1);
              while( true ) {
                sVar3 = (short)uVar8;
                uVar9 = uVar13 - iVar5;
                if (uVar9 != 0 && iVar5 <= (int)uVar13) break;
                iVar11 = -uVar9;
                for (iVar5 = iVar5 + uVar9; iVar5 != 0; iVar5 = iVar5 + -1) {
                  *pbVar19 = (byte)uVar8;
                  pbVar19 = pbVar19 + 1;
                }
                uStack_14 = uStack_14 - 1;
                if (uStack_14 == 0) goto LAB_000b5429;
                piStack_24 = piStack_24 + 1;
                pbVar19 = (byte *)(*piStack_24 + iVar4 + dword_d30d0);
                uVar12 = uVar7;
LAB_000b546c:
                iVar5 = iVar11 - uVar12;
                uVar13 = uVar6;
                if (iVar5 == 0) goto LAB_000b541e;
                if (iVar11 < (int)uVar12) goto LAB_000b551b;
              }
              for (; uVar13 = uVar9, iVar5 != 0; iVar5 = iVar5 + -1) {
                *pbVar19 = (byte)uVar8;
                pbVar19 = pbVar19 + 1;
              }
              goto LAB_000b541e;
            }
            pbVar19 = pbVar19 + iVar5;
            uVar9 = uVar13 - iVar5;
            bVar21 = iVar5 <= (int)uVar13;
            uVar13 = uVar9;
            pbVar14 = pbVar15;
          } while (uVar9 != 0 && bVar21);
        }
        uStack_14 = uStack_14 - 1;
        bVar21 = uStack_14 == 0;
LAB_000b5485:
        sVar3 = (short)uVar8;
        if (bVar21) {
LAB_000b5429:
          return (int)sVar3;
        }
        piStack_24 = piStack_24 + 1;
        uVar12 = uVar9 + uVar7;
        pbVar15 = pbVar14;
      } while (uVar12 == 0 || SCARRY4(uVar9,uVar7) != (int)uVar12 < 0);
      pbVar19 = (byte *)(*piStack_24 + iVar4 + dword_d30d0);
      uStack_18 = uVar12;
    } while( true );
  }
  piStack_24 = (int *)(off_d30cc + iVar5 * 4);
  puVar16 = (undefined *)(*piStack_24 + iVar4 + dword_d30d0);
  uVar8 = uVar6;
LAB_000b4eb4:
  do {
    while( true ) {
      pbVar19 = pbVar15 + 1;
      bVar1 = *pbVar15;
      if ((char)bVar1 < '\x01') break;
      iVar5 = (int)(short)(ushort)bVar1;
      pbVar15 = pbVar15 + 2;
      if (*pbVar19 == 0xff) {
        puVar16 = puVar16 + iVar5;
        uVar7 = uVar8 - iVar5;
        bVar21 = (int)uVar8 < iVar5;
        uVar8 = uVar7;
        if (uVar7 == 0 || bVar21) {
          do {
            piStack_24 = piStack_24 + 1;
            bVar21 = SCARRY4(uVar7,uVar6);
            uVar7 = uVar7 + uVar6;
          } while (uVar7 == 0 || bVar21 != (int)uVar7 < 0);
          puVar16 = (undefined *)((*piStack_24 + iVar4 + dword_d30d0 + uVar6) - uVar7);
          uVar8 = uVar7;
        }
      }
      else {
        uVar2 = *(undefined *)((int)&unk_d42e4 + (int)(short)(ushort)*pbVar19);
        uVar7 = uVar8;
        while (uVar8 = uVar7 - iVar5, uVar8 == 0 || (int)uVar7 < iVar5) {
          for (iVar5 = iVar5 + uVar8; iVar5 != 0; iVar5 = iVar5 + -1) {
            *puVar16 = uVar2;
            puVar16 = puVar16 + 1;
          }
          piStack_24 = piStack_24 + 1;
          puVar16 = (undefined *)(*piStack_24 + iVar4 + dword_d30d0);
          iVar5 = -uVar8;
          uVar7 = uVar6;
        }
        for (; iVar5 != 0; iVar5 = iVar5 + -1) {
          *puVar16 = uVar2;
          puVar16 = puVar16 + 1;
        }
      }
    }
    if (-1 < (char)bVar1) {
      return (int)(short)(ushort)bVar1;
    }
    iVar5 = (int)(short)(ushort)(byte)-bVar1;
    do {
      uVar7 = uVar8 - iVar5;
      puVar17 = puVar16;
      if (uVar7 != 0 && iVar5 <= (int)uVar8) goto LAB_000b4f2a;
      iVar18 = iVar5 + uVar7;
      iVar5 = -uVar7;
      pbVar15 = pbVar19;
      do {
        pbVar19 = pbVar15 + 1;
        *puVar16 = *(undefined *)((int)&unk_d42e4 + (int)(short)(ushort)*pbVar15);
        iVar18 = iVar18 + -1;
        pbVar15 = pbVar19;
        puVar16 = puVar16 + 1;
      } while (iVar18 != 0);
      piStack_24 = piStack_24 + 1;
      puVar16 = (undefined *)(*piStack_24 + iVar4 + dword_d30d0);
      uVar8 = uVar6;
    } while (iVar5 != 0 && (int)uVar7 < 1);
  } while( true );
LAB_000b551b:
  uVar8 = 0;
  uStack_18 = -iVar5;
  goto LAB_000b551f;
LAB_000b4f2a:
  do {
    puVar16 = puVar17 + 1;
    *puVar17 = *(undefined *)((int)&unk_d42e4 + (int)(short)(ushort)*pbVar19);
    iVar5 = iVar5 + -1;
    uVar8 = uVar7;
    pbVar15 = pbVar19 + 1;
    pbVar19 = pbVar19 + 1;
    puVar17 = puVar16;
  } while (iVar5 != 0);
  goto LAB_000b4eb4;
}


// ================================================================================================
// sub_b52b4 @ 0xb52b4 [__watcall]
// ================================================================================================

uint __watcall sub_b52b4(void)

{
  byte bVar1;
  undefined uVar2;
  short sVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  uint uVar11;
  uint uVar12;
  byte *pbVar13;
  byte *pbVar14;
  undefined *puVar15;
  undefined *puVar16;
  int iVar17;
  byte *pbVar18;
  byte *pbVar19;
  bool bVar20;
  int in_stack_00000004;
  int in_stack_00000008;
  int in_stack_0000000c;
  int *piStack_24;
  uint uStack_18;
  uint uStack_14;
  
  pbVar14 = (byte *)(in_stack_00000004 + 0x10);
  uVar4 = (uint)*(short *)(in_stack_00000004 + 4);
  iVar17 = 0;
  uStack_18 = 0;
  uVar7 = (uint)*(short *)(in_stack_00000004 + 6);
  if (in_stack_0000000c < dword_d30b0) {
    iVar17 = 1;
    uVar5 = (in_stack_0000000c + uVar7) - dword_d30b0;
    if (uVar5 == 0 || (int)(in_stack_0000000c + uVar7) < dword_d30b0) {
      return uVar5;
    }
    uStack_18 = (uVar7 - uVar5) * uVar4;
    uVar7 = (dword_d30b0 + uVar5) - dword_d30b8;
    uStack_14 = uVar5;
    in_stack_0000000c = dword_d30b0;
    if ((uVar7 != 0 && dword_d30b8 <= (int)(dword_d30b0 + uVar5)) &&
       (uStack_14 = uVar5 - uVar7, uStack_14 == 0 || (int)uVar5 < (int)uVar7)) {
      return uVar7;
    }
  }
  else {
    uVar5 = (in_stack_0000000c + uVar7) - dword_d30b8;
    uStack_14 = uVar7;
    if (uVar5 != 0 && dword_d30b8 <= (int)(in_stack_0000000c + uVar7)) {
      iVar17 = 1;
      uStack_14 = uVar7 - uVar5;
      if (uVar7 - uVar5 == 0 || (int)uVar7 < (int)uVar5) {
        return uVar5;
      }
    }
  }
  if (in_stack_00000008 < dword_d30bc) {
    iVar17 = iVar17 + 1;
    uVar7 = (in_stack_00000008 + uVar4) - dword_d30bc;
    if (uVar7 == 0 || (int)(in_stack_00000008 + uVar4) < dword_d30bc) {
      return uVar7;
    }
    uStack_18 = uStack_18 + (uVar4 - uVar7);
    if (dword_d30c0 - dword_d30bc <= (int)uVar7) {
      uVar7 = dword_d30c0 - dword_d30bc;
    }
    uVar5 = uVar4 - uVar7;
    uVar4 = uVar7;
    in_stack_00000008 = dword_d30bc;
  }
  else {
    uVar7 = (in_stack_00000008 + uVar4) - dword_d30c0;
    uVar5 = 0;
    if (uVar7 != 0 && dword_d30c0 <= (int)(in_stack_00000008 + uVar4)) {
      if (uVar4 - uVar7 == 0 || (int)uVar4 < (int)uVar7) {
        return uVar7;
      }
      iVar17 = iVar17 + 1;
      uVar4 = uVar4 - uVar7;
      uVar5 = uVar7;
    }
  }
  if (iVar17 != 0) {
    piStack_24 = (int *)(off_d30cc + in_stack_0000000c * 4);
    pbVar18 = (byte *)(*piStack_24 + in_stack_00000008 + dword_d30d0);
    uVar12 = uVar4;
    if (uStack_18 == 0) goto LAB_000b541e;
    if ((int)uStack_18 < 0) {
      iVar6 = (uStack_18 & 0x7fff) + 1;
      iVar17 = 0x7fff;
      do {
        while( true ) {
          bVar1 = *pbVar14;
          if ((char)bVar1 < '\x01') break;
          uVar7 = 0;
          iVar10 = (int)(short)(ushort)bVar1;
          pbVar14 = pbVar14 + 2;
          iVar9 = iVar17 - iVar10;
          bVar20 = iVar17 < iVar10;
          iVar17 = iVar9;
          if (iVar9 == 0 || bVar20) {
            uVar11 = iVar9 + iVar6;
            goto LAB_000b5536;
          }
        }
        if (-1 < (char)bVar1) {
          return (int)(short)CONCAT31((int3)(uVar7 >> 8),bVar1);
        }
        uVar7 = 0;
        uVar8 = (uint)(short)(ushort)(byte)-bVar1;
        pbVar14 = pbVar14 + uVar8 + 1;
        iVar10 = iVar17 - uVar8;
        bVar20 = (int)uVar8 <= iVar17;
        iVar17 = iVar10;
      } while (iVar10 != 0 && bVar20);
      pbVar13 = pbVar14 + -uVar8;
      uStack_18 = iVar10 + uVar8 + iVar6;
      goto LAB_000b5507;
    }
LAB_000b551f:
    do {
      do {
        pbVar13 = pbVar14 + 1;
        bVar1 = *pbVar14;
        if ((char)bVar1 < '\x01') {
          if (-1 < (char)bVar1) {
            return (int)(short)CONCAT31((int3)(uVar7 >> 8),bVar1);
          }
          uVar8 = (uint)(short)(ushort)(byte)-bVar1;
          goto LAB_000b5507;
        }
        uVar7 = 0;
        iVar10 = (int)(short)(ushort)bVar1;
        pbVar14 = pbVar14 + 2;
        uVar11 = uStack_18 - iVar10;
        bVar20 = iVar10 <= (int)uStack_18;
        uStack_18 = uVar11;
      } while (uVar11 != 0 && bVar20);
LAB_000b5536:
      bVar1 = pbVar14[-1];
      uVar7 = (uint)bVar1;
      if (bVar1 != 0xff) {
        uVar7 = (uint)*(byte *)((int)&unk_d42e4 + (int)(short)(ushort)bVar1);
        uVar11 = uVar11 + iVar10;
        goto LAB_000b546c;
      }
      do {
        uVar8 = uVar11 + uVar4;
        pbVar13 = pbVar14;
        if (uVar8 != 0 && SCARRY4(uVar11,uVar4) == (int)uVar8 < 0) {
          pbVar18 = (byte *)((*piStack_24 + in_stack_00000008 + dword_d30d0 + uVar4) - uVar8);
          uVar12 = uVar8;
LAB_000b541e:
          do {
            pbVar13 = pbVar14 + 1;
            bVar1 = *pbVar14;
            sVar3 = (short)CONCAT31((int3)(uVar7 >> 8),bVar1);
            if ((char)bVar1 < '\x01') {
              if (-1 < (char)bVar1) goto LAB_000b5429;
              iVar17 = (int)(short)(ushort)(byte)-bVar1;
              pbVar14 = pbVar13;
              while (uVar8 = uVar12 - iVar17, pbVar13 = pbVar14, pbVar19 = pbVar18,
                    uVar8 == 0 || (int)uVar12 < iVar17) {
                iVar17 = iVar17 + uVar8;
                uVar8 = -uVar8;
                do {
                  pbVar13 = pbVar14 + 1;
                  uVar7 = (uint)*(byte *)((int)&unk_d42e4 + (int)(short)(ushort)*pbVar14);
                  *pbVar18 = *(byte *)((int)&unk_d42e4 + (int)(short)(ushort)*pbVar14);
                  iVar17 = iVar17 + -1;
                  pbVar14 = pbVar13;
                  pbVar18 = pbVar18 + 1;
                } while (iVar17 != 0);
                uStack_14 = uStack_14 - 1;
                bVar20 = uStack_14 == 0;
                if (bVar20) goto LAB_000b5485;
                piStack_24 = piStack_24 + 1;
                pbVar18 = (byte *)(*piStack_24 + in_stack_00000008 + dword_d30d0);
                uStack_18 = uVar5;
LAB_000b5507:
                uVar7 = 0;
                pbVar14 = pbVar13 + uStack_18;
                iVar17 = uVar8 - uStack_18;
                uVar12 = uVar4;
                if (iVar17 == 0) goto LAB_000b541e;
                if ((int)uVar8 < (int)uStack_18) {
                  pbVar14 = pbVar14 + iVar17;
                  goto LAB_000b551b;
                }
              }
              do {
                pbVar14 = pbVar13 + 1;
                uVar7 = 0;
                pbVar18 = pbVar19 + 1;
                *pbVar19 = *(byte *)((int)&unk_d42e4 + (int)(short)(ushort)*pbVar13);
                iVar17 = iVar17 + -1;
                uVar12 = uVar8;
                pbVar13 = pbVar14;
                pbVar19 = pbVar18;
              } while (iVar17 != 0);
              goto LAB_000b541e;
            }
            iVar17 = (int)(short)(ushort)bVar1;
            pbVar14 = pbVar14 + 2;
            bVar1 = *pbVar13;
            uVar7 = (uint)bVar1;
            if (bVar1 != 0xff) {
              uVar7 = (uint)*(byte *)((int)&unk_d42e4 + (int)(short)(ushort)bVar1);
              while( true ) {
                sVar3 = (short)uVar7;
                uVar8 = uVar12 - iVar17;
                if (uVar8 != 0 && iVar17 <= (int)uVar12) break;
                iVar10 = -uVar8;
                for (iVar17 = iVar17 + uVar8; iVar17 != 0; iVar17 = iVar17 + -1) {
                  *pbVar18 = (byte)uVar7;
                  pbVar18 = pbVar18 + 1;
                }
                uStack_14 = uStack_14 - 1;
                if (uStack_14 == 0) goto LAB_000b5429;
                piStack_24 = piStack_24 + 1;
                pbVar18 = (byte *)(*piStack_24 + in_stack_00000008 + dword_d30d0);
                uVar11 = uVar5;
LAB_000b546c:
                iVar17 = iVar10 - uVar11;
                uVar12 = uVar4;
                if (iVar17 == 0) goto LAB_000b541e;
                if (iVar10 < (int)uVar11) goto LAB_000b551b;
              }
              for (; uVar12 = uVar8, iVar17 != 0; iVar17 = iVar17 + -1) {
                *pbVar18 = (byte)uVar7;
                pbVar18 = pbVar18 + 1;
              }
              goto LAB_000b541e;
            }
            pbVar18 = pbVar18 + iVar17;
            uVar8 = uVar12 - iVar17;
            bVar20 = iVar17 <= (int)uVar12;
            uVar12 = uVar8;
            pbVar13 = pbVar14;
          } while (uVar8 != 0 && bVar20);
        }
        uStack_14 = uStack_14 - 1;
        bVar20 = uStack_14 == 0;
LAB_000b5485:
        sVar3 = (short)uVar7;
        if (bVar20) {
LAB_000b5429:
          return (int)sVar3;
        }
        piStack_24 = piStack_24 + 1;
        uVar11 = uVar8 + uVar5;
        pbVar14 = pbVar13;
      } while (uVar11 == 0 || SCARRY4(uVar8,uVar5) != (int)uVar11 < 0);
      pbVar18 = (byte *)(*piStack_24 + in_stack_00000008 + dword_d30d0);
      uStack_18 = uVar11;
    } while( true );
  }
  piStack_24 = (int *)(off_d30cc + in_stack_0000000c * 4);
  puVar15 = (undefined *)(*piStack_24 + in_stack_00000008 + dword_d30d0);
  uVar7 = uVar4;
LAB_000b4eb4:
  do {
    while( true ) {
      pbVar18 = pbVar14 + 1;
      bVar1 = *pbVar14;
      if ((char)bVar1 < '\x01') break;
      iVar17 = (int)(short)(ushort)bVar1;
      pbVar14 = pbVar14 + 2;
      if (*pbVar18 == 0xff) {
        puVar15 = puVar15 + iVar17;
        uVar5 = uVar7 - iVar17;
        bVar20 = (int)uVar7 < iVar17;
        uVar7 = uVar5;
        if (uVar5 == 0 || bVar20) {
          do {
            piStack_24 = piStack_24 + 1;
            bVar20 = SCARRY4(uVar5,uVar4);
            uVar5 = uVar5 + uVar4;
          } while (uVar5 == 0 || bVar20 != (int)uVar5 < 0);
          puVar15 = (undefined *)((*piStack_24 + in_stack_00000008 + dword_d30d0 + uVar4) - uVar5);
          uVar7 = uVar5;
        }
      }
      else {
        uVar2 = *(undefined *)((int)&unk_d42e4 + (int)(short)(ushort)*pbVar18);
        uVar5 = uVar7;
        while (uVar7 = uVar5 - iVar17, uVar7 == 0 || (int)uVar5 < iVar17) {
          for (iVar17 = iVar17 + uVar7; iVar17 != 0; iVar17 = iVar17 + -1) {
            *puVar15 = uVar2;
            puVar15 = puVar15 + 1;
          }
          piStack_24 = piStack_24 + 1;
          puVar15 = (undefined *)(*piStack_24 + in_stack_00000008 + dword_d30d0);
          iVar17 = -uVar7;
          uVar5 = uVar4;
        }
        for (; iVar17 != 0; iVar17 = iVar17 + -1) {
          *puVar15 = uVar2;
          puVar15 = puVar15 + 1;
        }
      }
    }
    if (-1 < (char)bVar1) {
      return (int)(short)(ushort)bVar1;
    }
    iVar17 = (int)(short)(ushort)(byte)-bVar1;
    do {
      uVar5 = uVar7 - iVar17;
      puVar16 = puVar15;
      if (uVar5 != 0 && iVar17 <= (int)uVar7) goto LAB_000b4f2a;
      iVar6 = iVar17 + uVar5;
      iVar17 = -uVar5;
      pbVar14 = pbVar18;
      do {
        pbVar18 = pbVar14 + 1;
        *puVar15 = *(undefined *)((int)&unk_d42e4 + (int)(short)(ushort)*pbVar14);
        iVar6 = iVar6 + -1;
        pbVar14 = pbVar18;
        puVar15 = puVar15 + 1;
      } while (iVar6 != 0);
      piStack_24 = piStack_24 + 1;
      puVar15 = (undefined *)(*piStack_24 + in_stack_00000008 + dword_d30d0);
      uVar7 = uVar4;
    } while (iVar17 != 0 && (int)uVar5 < 1);
  } while( true );
LAB_000b551b:
  uVar7 = 0;
  uStack_18 = -iVar17;
  goto LAB_000b551f;
LAB_000b4f2a:
  do {
    puVar15 = puVar16 + 1;
    *puVar16 = *(undefined *)((int)&unk_d42e4 + (int)(short)(ushort)*pbVar18);
    iVar17 = iVar17 + -1;
    uVar7 = uVar5;
    pbVar14 = pbVar18 + 1;
    pbVar18 = pbVar18 + 1;
    puVar16 = puVar15;
  } while (iVar17 != 0);
  goto LAB_000b4eb4;
}


// ================================================================================================
// sub_b52ce @ 0xb52ce [__watcall]
// ================================================================================================

uint __watcall sub_b52ce(void)

{
  byte bVar1;
  undefined uVar2;
  short sVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  int iVar10;
  int iVar11;
  uint uVar12;
  uint uVar13;
  byte *pbVar14;
  byte *pbVar15;
  undefined *puVar16;
  undefined *puVar17;
  int iVar18;
  byte *pbVar19;
  byte *pbVar20;
  bool bVar21;
  int in_stack_00000004;
  int *local_24;
  uint local_18;
  uint local_14;
  
  iVar4 = (int)*(short *)(in_stack_00000004 + 0xc);
  iVar5 = (int)*(short *)(in_stack_00000004 + 0xe);
  pbVar15 = (byte *)(in_stack_00000004 + 0x10);
  uVar6 = (uint)*(short *)(in_stack_00000004 + 4);
  iVar18 = 0;
  local_18 = 0;
  uVar8 = (uint)*(short *)(in_stack_00000004 + 6);
  if (iVar5 < dword_d30b0) {
    iVar18 = 1;
    uVar7 = (iVar5 + uVar8) - dword_d30b0;
    if (uVar7 == 0 || (int)(iVar5 + uVar8) < dword_d30b0) {
      return uVar7;
    }
    local_18 = (uVar8 - uVar7) * uVar6;
    uVar8 = (dword_d30b0 + uVar7) - dword_d30b8;
    local_14 = uVar7;
    iVar5 = dword_d30b0;
    if ((uVar8 != 0 && dword_d30b8 <= (int)(dword_d30b0 + uVar7)) &&
       (local_14 = uVar7 - uVar8, local_14 == 0 || (int)uVar7 < (int)uVar8)) {
      return uVar8;
    }
  }
  else {
    uVar7 = (iVar5 + uVar8) - dword_d30b8;
    local_14 = uVar8;
    if (uVar7 != 0 && dword_d30b8 <= (int)(iVar5 + uVar8)) {
      iVar18 = 1;
      local_14 = uVar8 - uVar7;
      if (uVar8 - uVar7 == 0 || (int)uVar8 < (int)uVar7) {
        return uVar7;
      }
    }
  }
  if (iVar4 < dword_d30bc) {
    iVar18 = iVar18 + 1;
    uVar8 = (iVar4 + uVar6) - dword_d30bc;
    if (uVar8 == 0 || (int)(iVar4 + uVar6) < dword_d30bc) {
      return uVar8;
    }
    local_18 = local_18 + (uVar6 - uVar8);
    if (dword_d30c0 - dword_d30bc <= (int)uVar8) {
      uVar8 = dword_d30c0 - dword_d30bc;
    }
    uVar7 = uVar6 - uVar8;
    uVar6 = uVar8;
    iVar4 = dword_d30bc;
  }
  else {
    uVar8 = (iVar4 + uVar6) - dword_d30c0;
    uVar7 = 0;
    if (uVar8 != 0 && dword_d30c0 <= (int)(iVar4 + uVar6)) {
      if (uVar6 - uVar8 == 0 || (int)uVar6 < (int)uVar8) {
        return uVar8;
      }
      iVar18 = iVar18 + 1;
      uVar6 = uVar6 - uVar8;
      uVar7 = uVar8;
    }
  }
  if (iVar18 != 0) {
    local_24 = (int *)(off_d30cc + iVar5 * 4);
    pbVar19 = (byte *)(*local_24 + iVar4 + dword_d30d0);
    uVar13 = uVar6;
    if (local_18 == 0) goto LAB_000b541e;
    if ((int)local_18 < 0) {
      iVar18 = (local_18 & 0x7fff) + 1;
      iVar5 = 0x7fff;
      do {
        while( true ) {
          bVar1 = *pbVar15;
          if ((char)bVar1 < '\x01') break;
          uVar8 = 0;
          iVar11 = (int)(short)(ushort)bVar1;
          pbVar15 = pbVar15 + 2;
          iVar10 = iVar5 - iVar11;
          bVar21 = iVar5 < iVar11;
          iVar5 = iVar10;
          if (iVar10 == 0 || bVar21) {
            uVar12 = iVar10 + iVar18;
            goto LAB_000b5536;
          }
        }
        if (-1 < (char)bVar1) {
          return (int)(short)CONCAT31((int3)(uVar8 >> 8),bVar1);
        }
        uVar8 = 0;
        uVar9 = (uint)(short)(ushort)(byte)-bVar1;
        pbVar15 = pbVar15 + uVar9 + 1;
        iVar11 = iVar5 - uVar9;
        bVar21 = (int)uVar9 <= iVar5;
        iVar5 = iVar11;
      } while (iVar11 != 0 && bVar21);
      pbVar14 = pbVar15 + -uVar9;
      local_18 = iVar11 + uVar9 + iVar18;
      goto LAB_000b5507;
    }
LAB_000b551f:
    do {
      do {
        pbVar14 = pbVar15 + 1;
        bVar1 = *pbVar15;
        if ((char)bVar1 < '\x01') {
          if (-1 < (char)bVar1) {
            return (int)(short)CONCAT31((int3)(uVar8 >> 8),bVar1);
          }
          uVar9 = (uint)(short)(ushort)(byte)-bVar1;
          goto LAB_000b5507;
        }
        uVar8 = 0;
        iVar11 = (int)(short)(ushort)bVar1;
        pbVar15 = pbVar15 + 2;
        uVar12 = local_18 - iVar11;
        bVar21 = iVar11 <= (int)local_18;
        local_18 = uVar12;
      } while (uVar12 != 0 && bVar21);
LAB_000b5536:
      bVar1 = pbVar15[-1];
      uVar8 = (uint)bVar1;
      if (bVar1 != 0xff) {
        uVar8 = (uint)*(byte *)((int)&unk_d42e4 + (int)(short)(ushort)bVar1);
        uVar12 = uVar12 + iVar11;
        goto LAB_000b546c;
      }
      do {
        uVar9 = uVar12 + uVar6;
        pbVar14 = pbVar15;
        if (uVar9 != 0 && SCARRY4(uVar12,uVar6) == (int)uVar9 < 0) {
          pbVar19 = (byte *)((*local_24 + iVar4 + dword_d30d0 + uVar6) - uVar9);
          uVar13 = uVar9;
LAB_000b541e:
          do {
            pbVar14 = pbVar15 + 1;
            bVar1 = *pbVar15;
            sVar3 = (short)CONCAT31((int3)(uVar8 >> 8),bVar1);
            if ((char)bVar1 < '\x01') {
              if (-1 < (char)bVar1) goto LAB_000b5429;
              iVar5 = (int)(short)(ushort)(byte)-bVar1;
              pbVar15 = pbVar14;
              while (uVar9 = uVar13 - iVar5, pbVar14 = pbVar15, pbVar20 = pbVar19,
                    uVar9 == 0 || (int)uVar13 < iVar5) {
                iVar5 = iVar5 + uVar9;
                uVar9 = -uVar9;
                do {
                  pbVar14 = pbVar15 + 1;
                  uVar8 = (uint)*(byte *)((int)&unk_d42e4 + (int)(short)(ushort)*pbVar15);
                  *pbVar19 = *(byte *)((int)&unk_d42e4 + (int)(short)(ushort)*pbVar15);
                  iVar5 = iVar5 + -1;
                  pbVar15 = pbVar14;
                  pbVar19 = pbVar19 + 1;
                } while (iVar5 != 0);
                local_14 = local_14 - 1;
                bVar21 = local_14 == 0;
                if (bVar21) goto LAB_000b5485;
                local_24 = local_24 + 1;
                pbVar19 = (byte *)(*local_24 + iVar4 + dword_d30d0);
                local_18 = uVar7;
LAB_000b5507:
                uVar8 = 0;
                pbVar15 = pbVar14 + local_18;
                iVar5 = uVar9 - local_18;
                uVar13 = uVar6;
                if (iVar5 == 0) goto LAB_000b541e;
                if ((int)uVar9 < (int)local_18) {
                  pbVar15 = pbVar15 + iVar5;
                  goto LAB_000b551b;
                }
              }
              do {
                pbVar15 = pbVar14 + 1;
                uVar8 = 0;
                pbVar19 = pbVar20 + 1;
                *pbVar20 = *(byte *)((int)&unk_d42e4 + (int)(short)(ushort)*pbVar14);
                iVar5 = iVar5 + -1;
                uVar13 = uVar9;
                pbVar14 = pbVar15;
                pbVar20 = pbVar19;
              } while (iVar5 != 0);
              goto LAB_000b541e;
            }
            iVar5 = (int)(short)(ushort)bVar1;
            pbVar15 = pbVar15 + 2;
            bVar1 = *pbVar14;
            uVar8 = (uint)bVar1;
            if (bVar1 != 0xff) {
              uVar8 = (uint)*(byte *)((int)&unk_d42e4 + (int)(short)(ushort)bVar1);
              while( true ) {
                sVar3 = (short)uVar8;
                uVar9 = uVar13 - iVar5;
                if (uVar9 != 0 && iVar5 <= (int)uVar13) break;
                iVar11 = -uVar9;
                for (iVar5 = iVar5 + uVar9; iVar5 != 0; iVar5 = iVar5 + -1) {
                  *pbVar19 = (byte)uVar8;
                  pbVar19 = pbVar19 + 1;
                }
                local_14 = local_14 - 1;
                if (local_14 == 0) goto LAB_000b5429;
                local_24 = local_24 + 1;
                pbVar19 = (byte *)(*local_24 + iVar4 + dword_d30d0);
                uVar12 = uVar7;
LAB_000b546c:
                iVar5 = iVar11 - uVar12;
                uVar13 = uVar6;
                if (iVar5 == 0) goto LAB_000b541e;
                if (iVar11 < (int)uVar12) goto LAB_000b551b;
              }
              for (; uVar13 = uVar9, iVar5 != 0; iVar5 = iVar5 + -1) {
                *pbVar19 = (byte)uVar8;
                pbVar19 = pbVar19 + 1;
              }
              goto LAB_000b541e;
            }
            pbVar19 = pbVar19 + iVar5;
            uVar9 = uVar13 - iVar5;
            bVar21 = iVar5 <= (int)uVar13;
            uVar13 = uVar9;
            pbVar14 = pbVar15;
          } while (uVar9 != 0 && bVar21);
        }
        local_14 = local_14 - 1;
        bVar21 = local_14 == 0;
LAB_000b5485:
        sVar3 = (short)uVar8;
        if (bVar21) {
LAB_000b5429:
          return (int)sVar3;
        }
        local_24 = local_24 + 1;
        uVar12 = uVar9 + uVar7;
        pbVar15 = pbVar14;
      } while (uVar12 == 0 || SCARRY4(uVar9,uVar7) != (int)uVar12 < 0);
      pbVar19 = (byte *)(*local_24 + iVar4 + dword_d30d0);
      local_18 = uVar12;
    } while( true );
  }
  local_24 = (int *)(off_d30cc + iVar5 * 4);
  puVar16 = (undefined *)(*local_24 + iVar4 + dword_d30d0);
  uVar8 = uVar6;
LAB_000b4eb4:
  do {
    while( true ) {
      pbVar19 = pbVar15 + 1;
      bVar1 = *pbVar15;
      if ((char)bVar1 < '\x01') break;
      iVar5 = (int)(short)(ushort)bVar1;
      pbVar15 = pbVar15 + 2;
      if (*pbVar19 == 0xff) {
        puVar16 = puVar16 + iVar5;
        uVar7 = uVar8 - iVar5;
        bVar21 = (int)uVar8 < iVar5;
        uVar8 = uVar7;
        if (uVar7 == 0 || bVar21) {
          do {
            local_24 = local_24 + 1;
            bVar21 = SCARRY4(uVar7,uVar6);
            uVar7 = uVar7 + uVar6;
          } while (uVar7 == 0 || bVar21 != (int)uVar7 < 0);
          puVar16 = (undefined *)((*local_24 + iVar4 + dword_d30d0 + uVar6) - uVar7);
          uVar8 = uVar7;
        }
      }
      else {
        uVar2 = *(undefined *)((int)&unk_d42e4 + (int)(short)(ushort)*pbVar19);
        uVar7 = uVar8;
        while (uVar8 = uVar7 - iVar5, uVar8 == 0 || (int)uVar7 < iVar5) {
          for (iVar5 = iVar5 + uVar8; iVar5 != 0; iVar5 = iVar5 + -1) {
            *puVar16 = uVar2;
            puVar16 = puVar16 + 1;
          }
          local_24 = local_24 + 1;
          puVar16 = (undefined *)(*local_24 + iVar4 + dword_d30d0);
          iVar5 = -uVar8;
          uVar7 = uVar6;
        }
        for (; iVar5 != 0; iVar5 = iVar5 + -1) {
          *puVar16 = uVar2;
          puVar16 = puVar16 + 1;
        }
      }
    }
    if (-1 < (char)bVar1) {
      return (int)(short)(ushort)bVar1;
    }
    iVar5 = (int)(short)(ushort)(byte)-bVar1;
    do {
      uVar7 = uVar8 - iVar5;
      puVar17 = puVar16;
      if (uVar7 != 0 && iVar5 <= (int)uVar8) goto LAB_000b4f2a;
      iVar18 = iVar5 + uVar7;
      iVar5 = -uVar7;
      pbVar15 = pbVar19;
      do {
        pbVar19 = pbVar15 + 1;
        *puVar16 = *(undefined *)((int)&unk_d42e4 + (int)(short)(ushort)*pbVar15);
        iVar18 = iVar18 + -1;
        pbVar15 = pbVar19;
        puVar16 = puVar16 + 1;
      } while (iVar18 != 0);
      local_24 = local_24 + 1;
      puVar16 = (undefined *)(*local_24 + iVar4 + dword_d30d0);
      uVar8 = uVar6;
    } while (iVar5 != 0 && (int)uVar7 < 1);
  } while( true );
LAB_000b551b:
  uVar8 = 0;
  local_18 = -iVar5;
  goto LAB_000b551f;
LAB_000b4f2a:
  do {
    puVar16 = puVar17 + 1;
    *puVar17 = *(undefined *)((int)&unk_d42e4 + (int)(short)(ushort)*pbVar19);
    iVar5 = iVar5 + -1;
    uVar8 = uVar7;
    pbVar15 = pbVar19 + 1;
    pbVar19 = pbVar19 + 1;
    puVar17 = puVar16;
  } while (iVar5 != 0);
  goto LAB_000b4eb4;
}


// ================================================================================================
// sub_b555c @ 0xb555c [__watcall]
// ================================================================================================

byte __watcall sub_b555c(void)

{
  int iVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  byte *pbVar7;
  byte *pbVar8;
  byte *pbVar9;
  byte *pbVar10;
  bool bVar11;
  int in_stack_00000004;
  short in_stack_00000008;
  short in_stack_0000000c;
  int *piStack_24;
  
  iVar3 = (int)*(short *)(in_stack_00000004 + 4);
  iVar1 = (int)(short)((in_stack_00000008 - *(short *)(in_stack_00000004 + 4)) +
                      *(short *)(in_stack_00000004 + 8)) + iVar3 + -1;
  piStack_24 = (int *)(off_d30cc +
                      (short)(in_stack_0000000c - *(short *)(in_stack_00000004 + 10)) * 4);
  pbVar9 = (byte *)(*piStack_24 + iVar1 + dword_d30d0);
  iVar5 = iVar3;
  pbVar8 = (byte *)(in_stack_00000004 + 0x10);
LAB_000b55ec:
  do {
    while( true ) {
      bVar2 = *pbVar8;
      pbVar7 = pbVar8 + 1;
      if ((char)bVar2 < '\x01') break;
      iVar4 = (int)(short)(ushort)bVar2;
      bVar2 = *pbVar7;
      pbVar8 = pbVar8 + 2;
      if (bVar2 == 0xff) {
        pbVar9 = pbVar9 + -iVar4;
        iVar6 = iVar5 - iVar4;
        bVar11 = iVar5 < iVar4;
        iVar5 = iVar6;
        if (iVar6 == 0 || bVar11) {
          do {
            piStack_24 = piStack_24 + 1;
            bVar11 = SCARRY4(iVar6,iVar3);
            iVar6 = iVar6 + iVar3;
          } while (iVar6 == 0 || bVar11 != iVar6 < 0);
          pbVar9 = (byte *)(((*piStack_24 + iVar1 + dword_d30d0) - iVar3) + iVar6);
          iVar5 = iVar6;
        }
      }
      else {
        while (iVar6 = iVar5 - iVar4, iVar6 == 0 || iVar5 < iVar4) {
          for (iVar4 = iVar4 + iVar6; iVar4 != 0; iVar4 = iVar4 + -1) {
            *pbVar9 = bVar2;
            pbVar9 = pbVar9 + -1;
          }
          piStack_24 = piStack_24 + 1;
          pbVar9 = (byte *)(*piStack_24 + iVar1 + dword_d30d0);
          iVar4 = -iVar6;
          iVar5 = iVar3;
        }
        for (; iVar5 = iVar6, iVar4 != 0; iVar4 = iVar4 + -1) {
          *pbVar9 = bVar2;
          pbVar9 = pbVar9 + -1;
        }
      }
    }
    if (-1 < (char)bVar2) {
      return bVar2;
    }
    iVar4 = (int)(short)(ushort)(byte)-bVar2;
    do {
      iVar6 = iVar5 - iVar4;
      pbVar10 = pbVar9;
      if (iVar6 != 0 && iVar4 <= iVar5) goto LAB_000b565e;
      iVar5 = iVar4 + iVar6;
      iVar4 = -iVar6;
      do {
        bVar2 = *pbVar7;
        pbVar7 = pbVar7 + 1;
        *pbVar9 = bVar2;
        iVar5 = iVar5 + -1;
        pbVar9 = pbVar9 + -1;
      } while (iVar5 != 0);
      piStack_24 = piStack_24 + 1;
      pbVar9 = (byte *)(*piStack_24 + iVar1 + dword_d30d0);
      iVar5 = iVar3;
      pbVar8 = pbVar7;
    } while (iVar4 != 0 && iVar6 < 1);
  } while( true );
LAB_000b565e:
  do {
    bVar2 = *pbVar7;
    pbVar7 = pbVar7 + 1;
    pbVar9 = pbVar10 + -1;
    *pbVar10 = bVar2;
    iVar4 = iVar4 + -1;
    iVar5 = iVar6;
    pbVar8 = pbVar7;
    pbVar10 = pbVar9;
  } while (iVar4 != 0);
  goto LAB_000b55ec;
}


// ================================================================================================
// sub_b5584 @ 0xb5584 [__watcall]
// ================================================================================================

byte __watcall sub_b5584(void)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  byte *pbVar6;
  byte *pbVar7;
  byte *pbVar8;
  byte *pbVar9;
  bool bVar10;
  int in_stack_00000004;
  int in_stack_00000008;
  int in_stack_0000000c;
  int *piStack_24;
  
  iVar2 = (int)*(short *)(in_stack_00000004 + 4);
  in_stack_00000008 = in_stack_00000008 + iVar2 + -1;
  piStack_24 = (int *)(off_d30cc + in_stack_0000000c * 4);
  pbVar8 = (byte *)(*piStack_24 + in_stack_00000008 + dword_d30d0);
  iVar4 = iVar2;
  pbVar7 = (byte *)(in_stack_00000004 + 0x10);
LAB_000b55ec:
  do {
    while( true ) {
      bVar1 = *pbVar7;
      pbVar6 = pbVar7 + 1;
      if ((char)bVar1 < '\x01') break;
      iVar3 = (int)(short)(ushort)bVar1;
      bVar1 = *pbVar6;
      pbVar7 = pbVar7 + 2;
      if (bVar1 == 0xff) {
        pbVar8 = pbVar8 + -iVar3;
        iVar5 = iVar4 - iVar3;
        bVar10 = iVar4 < iVar3;
        iVar4 = iVar5;
        if (iVar5 == 0 || bVar10) {
          do {
            piStack_24 = piStack_24 + 1;
            bVar10 = SCARRY4(iVar5,iVar2);
            iVar5 = iVar5 + iVar2;
          } while (iVar5 == 0 || bVar10 != iVar5 < 0);
          pbVar8 = (byte *)(((*piStack_24 + in_stack_00000008 + dword_d30d0) - iVar2) + iVar5);
          iVar4 = iVar5;
        }
      }
      else {
        while (iVar5 = iVar4 - iVar3, iVar5 == 0 || iVar4 < iVar3) {
          for (iVar3 = iVar3 + iVar5; iVar3 != 0; iVar3 = iVar3 + -1) {
            *pbVar8 = bVar1;
            pbVar8 = pbVar8 + -1;
          }
          piStack_24 = piStack_24 + 1;
          pbVar8 = (byte *)(*piStack_24 + in_stack_00000008 + dword_d30d0);
          iVar3 = -iVar5;
          iVar4 = iVar2;
        }
        for (; iVar4 = iVar5, iVar3 != 0; iVar3 = iVar3 + -1) {
          *pbVar8 = bVar1;
          pbVar8 = pbVar8 + -1;
        }
      }
    }
    if (-1 < (char)bVar1) {
      return bVar1;
    }
    iVar3 = (int)(short)(ushort)(byte)-bVar1;
    do {
      iVar5 = iVar4 - iVar3;
      pbVar9 = pbVar8;
      if (iVar5 != 0 && iVar3 <= iVar4) goto LAB_000b565e;
      iVar4 = iVar3 + iVar5;
      iVar3 = -iVar5;
      do {
        bVar1 = *pbVar6;
        pbVar6 = pbVar6 + 1;
        *pbVar8 = bVar1;
        iVar4 = iVar4 + -1;
        pbVar8 = pbVar8 + -1;
      } while (iVar4 != 0);
      piStack_24 = piStack_24 + 1;
      pbVar8 = (byte *)(*piStack_24 + in_stack_00000008 + dword_d30d0);
      iVar4 = iVar2;
      pbVar7 = pbVar6;
    } while (iVar3 != 0 && iVar5 < 1);
  } while( true );
LAB_000b565e:
  do {
    bVar1 = *pbVar6;
    pbVar6 = pbVar6 + 1;
    pbVar8 = pbVar9 + -1;
    *pbVar9 = bVar1;
    iVar3 = iVar3 + -1;
    iVar4 = iVar5;
    pbVar7 = pbVar6;
    pbVar9 = pbVar8;
  } while (iVar3 != 0);
  goto LAB_000b55ec;
}


// ================================================================================================
// sub_b559e @ 0xb559e [__watcall]
// ================================================================================================

byte __watcall sub_b559e(void)

{
  int iVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  byte *pbVar7;
  byte *pbVar8;
  byte *pbVar9;
  byte *pbVar10;
  bool bVar11;
  int in_stack_00000004;
  int *local_24;
  
  iVar3 = (int)*(short *)(in_stack_00000004 + 4);
  iVar1 = (int)*(short *)(in_stack_00000004 + 0xc) + iVar3 + -1;
  local_24 = (int *)(off_d30cc + *(short *)(in_stack_00000004 + 0xe) * 4);
  pbVar9 = (byte *)(*local_24 + iVar1 + dword_d30d0);
  iVar5 = iVar3;
  pbVar8 = (byte *)(in_stack_00000004 + 0x10);
LAB_000b55ec:
  do {
    while( true ) {
      bVar2 = *pbVar8;
      pbVar7 = pbVar8 + 1;
      if ((char)bVar2 < '\x01') break;
      iVar4 = (int)(short)(ushort)bVar2;
      bVar2 = *pbVar7;
      pbVar8 = pbVar8 + 2;
      if (bVar2 == 0xff) {
        pbVar9 = pbVar9 + -iVar4;
        iVar6 = iVar5 - iVar4;
        bVar11 = iVar5 < iVar4;
        iVar5 = iVar6;
        if (iVar6 == 0 || bVar11) {
          do {
            local_24 = local_24 + 1;
            bVar11 = SCARRY4(iVar6,iVar3);
            iVar6 = iVar6 + iVar3;
          } while (iVar6 == 0 || bVar11 != iVar6 < 0);
          pbVar9 = (byte *)(((*local_24 + iVar1 + dword_d30d0) - iVar3) + iVar6);
          iVar5 = iVar6;
        }
      }
      else {
        while (iVar6 = iVar5 - iVar4, iVar6 == 0 || iVar5 < iVar4) {
          for (iVar4 = iVar4 + iVar6; iVar4 != 0; iVar4 = iVar4 + -1) {
            *pbVar9 = bVar2;
            pbVar9 = pbVar9 + -1;
          }
          local_24 = local_24 + 1;
          pbVar9 = (byte *)(*local_24 + iVar1 + dword_d30d0);
          iVar4 = -iVar6;
          iVar5 = iVar3;
        }
        for (; iVar5 = iVar6, iVar4 != 0; iVar4 = iVar4 + -1) {
          *pbVar9 = bVar2;
          pbVar9 = pbVar9 + -1;
        }
      }
    }
    if (-1 < (char)bVar2) {
      return bVar2;
    }
    iVar4 = (int)(short)(ushort)(byte)-bVar2;
    do {
      iVar6 = iVar5 - iVar4;
      pbVar10 = pbVar9;
      if (iVar6 != 0 && iVar4 <= iVar5) goto LAB_000b565e;
      iVar5 = iVar4 + iVar6;
      iVar4 = -iVar6;
      do {
        bVar2 = *pbVar7;
        pbVar7 = pbVar7 + 1;
        *pbVar9 = bVar2;
        iVar5 = iVar5 + -1;
        pbVar9 = pbVar9 + -1;
      } while (iVar5 != 0);
      local_24 = local_24 + 1;
      pbVar9 = (byte *)(*local_24 + iVar1 + dword_d30d0);
      iVar5 = iVar3;
      pbVar8 = pbVar7;
    } while (iVar4 != 0 && iVar6 < 1);
  } while( true );
LAB_000b565e:
  do {
    bVar2 = *pbVar7;
    pbVar7 = pbVar7 + 1;
    pbVar9 = pbVar10 + -1;
    *pbVar10 = bVar2;
    iVar4 = iVar4 + -1;
    iVar5 = iVar6;
    pbVar8 = pbVar7;
    pbVar10 = pbVar9;
  } while (iVar4 != 0);
  goto LAB_000b55ec;
}


// ================================================================================================
// sub_b5690 @ 0xb5690 [__watcall]
// ================================================================================================

uint __watcall sub_b5690(void)

{
  byte bVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  uint uVar11;
  uint uVar12;
  byte *pbVar13;
  byte *pbVar14;
  byte *pbVar15;
  byte *pbVar16;
  int iVar17;
  bool bVar18;
  int in_stack_00000004;
  short in_stack_00000008;
  short in_stack_0000000c;
  int *piStack_24;
  uint uStack_18;
  uint uStack_14;
  
  iVar3 = (int)(short)((in_stack_00000008 - *(short *)(in_stack_00000004 + 4)) +
                      *(short *)(in_stack_00000004 + 8));
  iVar4 = (int)(short)(in_stack_0000000c - *(short *)(in_stack_00000004 + 10));
  pbVar14 = (byte *)(in_stack_00000004 + 0x10);
  uVar5 = (uint)*(short *)(in_stack_00000004 + 4);
  iVar17 = 0;
  uStack_18 = 0;
  uVar7 = (uint)*(short *)(in_stack_00000004 + 6);
  if (iVar4 < dword_d30b0) {
    iVar17 = 1;
    uVar6 = (iVar4 + uVar7) - dword_d30b0;
    if (uVar6 == 0 || (int)(iVar4 + uVar7) < dword_d30b0) {
      return uVar6;
    }
    uStack_18 = (uVar7 - uVar6) * uVar5;
    uVar7 = (dword_d30b0 + uVar6) - dword_d30b8;
    uStack_14 = uVar6;
    iVar4 = dword_d30b0;
    if ((uVar7 != 0 && dword_d30b8 <= (int)(dword_d30b0 + uVar6)) &&
       (uStack_14 = uVar6 - uVar7, uStack_14 == 0 || (int)uVar6 < (int)uVar7)) {
      return uVar7;
    }
  }
  else {
    uVar6 = (iVar4 + uVar7) - dword_d30b8;
    uStack_14 = uVar7;
    if (uVar6 != 0 && dword_d30b8 <= (int)(iVar4 + uVar7)) {
      iVar17 = 1;
      uStack_14 = uVar7 - uVar6;
      if (uVar7 - uVar6 == 0 || (int)uVar7 < (int)uVar6) {
        return uVar6;
      }
    }
  }
  if (iVar3 < dword_d30bc) {
    iVar17 = iVar17 + 1;
    uVar7 = (iVar3 + uVar5) - dword_d30bc;
    if (uVar7 == 0 || (int)(iVar3 + uVar5) < dword_d30bc) {
      return uVar7;
    }
    if (dword_d30c0 - dword_d30bc <= (int)uVar7) {
      uVar7 = dword_d30c0 - dword_d30bc;
    }
    uVar6 = uVar5 - uVar7;
    uVar5 = uVar7;
    iVar3 = dword_d30bc;
  }
  else {
    uVar7 = (iVar3 + uVar5) - dword_d30c0;
    uVar6 = 0;
    if (uVar7 != 0 && dword_d30c0 <= (int)(iVar3 + uVar5)) {
      uStack_18 = uStack_18 + uVar7;
      if (uVar5 - uVar7 == 0 || (int)uVar5 < (int)uVar7) {
        return uVar7;
      }
      iVar17 = iVar17 + 1;
      uVar5 = uVar5 - uVar7;
      uVar6 = uVar7;
    }
  }
  iVar3 = iVar3 + uVar5 + -1;
  if (iVar17 != 0) {
    piStack_24 = (int *)(off_d30cc + iVar4 * 4);
    pbVar15 = (byte *)(*piStack_24 + iVar3 + dword_d30d0);
    uVar12 = uVar5;
    if (uStack_18 == 0) goto LAB_000b582a;
    if ((int)uStack_18 < 0) {
      iVar17 = (uStack_18 & 0x7fff) + 1;
      iVar4 = 0x7fff;
      do {
        while( true ) {
          bVar1 = *pbVar14;
          if ((char)bVar1 < '\x01') break;
          uVar7 = 0;
          iVar10 = (int)(short)(ushort)bVar1;
          pbVar14 = pbVar14 + 2;
          iVar9 = iVar4 - iVar10;
          bVar18 = iVar4 < iVar10;
          iVar4 = iVar9;
          if (iVar9 == 0 || bVar18) {
            uVar11 = iVar9 + iVar17;
            goto LAB_000b592e;
          }
        }
        if (-1 < (char)bVar1) {
          return (int)(short)CONCAT31((int3)(uVar7 >> 8),bVar1);
        }
        uVar7 = 0;
        uVar8 = (uint)(short)(ushort)(byte)-bVar1;
        pbVar14 = pbVar14 + uVar8 + 1;
        iVar10 = iVar4 - uVar8;
        bVar18 = (int)uVar8 <= iVar4;
        iVar4 = iVar10;
      } while (iVar10 != 0 && bVar18);
      pbVar13 = pbVar14 + -uVar8;
      uStack_18 = iVar10 + uVar8 + iVar17;
      goto LAB_000b58fd;
    }
LAB_000b5915:
    do {
      do {
        bVar1 = *pbVar14;
        pbVar13 = pbVar14 + 1;
        if ((char)bVar1 < '\x01') {
          if (-1 < (char)bVar1) {
            return (int)(short)CONCAT31((int3)(uVar7 >> 8),bVar1);
          }
          uVar8 = (uint)(short)(ushort)(byte)-bVar1;
          goto LAB_000b58fd;
        }
        uVar7 = 0;
        iVar10 = (int)(short)(ushort)bVar1;
        pbVar14 = pbVar14 + 2;
        uVar11 = uStack_18 - iVar10;
        bVar18 = iVar10 <= (int)uStack_18;
        uStack_18 = uVar11;
      } while (uVar11 != 0 && bVar18);
LAB_000b592e:
      uVar7 = (uint)pbVar14[-1];
      pbVar13 = pbVar14;
      if (pbVar14[-1] != 0xff) {
        uVar11 = uVar11 + iVar10;
        goto LAB_000b5870;
      }
      do {
        uVar8 = uVar11 + uVar5;
        if (uVar8 != 0 && SCARRY4(uVar11,uVar5) == (int)uVar8 < 0) {
          pbVar15 = (byte *)(((*piStack_24 + iVar3 + dword_d30d0) - uVar5) + uVar8);
          uVar12 = uVar8;
          pbVar14 = pbVar13;
LAB_000b582a:
          do {
            bVar1 = *pbVar14;
            sVar2 = (short)CONCAT31((int3)(uVar7 >> 8),bVar1);
            if ((char)bVar1 < '\x01') {
              if (-1 < (char)bVar1) goto LAB_000b5833;
              iVar4 = (int)(short)(ushort)(byte)-bVar1;
              pbVar13 = pbVar14 + 1;
              while (uVar8 = uVar12 - iVar4, pbVar16 = pbVar15, uVar8 == 0 || (int)uVar12 < iVar4) {
                iVar4 = iVar4 + uVar8;
                uVar8 = -uVar8;
                do {
                  bVar1 = *pbVar13;
                  uVar7 = (uint)bVar1;
                  pbVar13 = pbVar13 + 1;
                  *pbVar15 = bVar1;
                  iVar4 = iVar4 + -1;
                  pbVar15 = pbVar15 + -1;
                } while (iVar4 != 0);
                uStack_14 = uStack_14 - 1;
                bVar18 = uStack_14 == 0;
                if (bVar18) goto LAB_000b5889;
                piStack_24 = piStack_24 + 1;
                pbVar15 = (byte *)(*piStack_24 + iVar3 + dword_d30d0);
                uStack_18 = uVar6;
LAB_000b58fd:
                uVar7 = 0;
                pbVar14 = pbVar13 + uStack_18;
                iVar4 = uVar8 - uStack_18;
                uVar12 = uVar5;
                if (iVar4 == 0) goto LAB_000b582a;
                pbVar13 = pbVar14;
                if ((int)uVar8 < (int)uStack_18) {
                  pbVar14 = pbVar14 + iVar4;
                  goto LAB_000b5911;
                }
              }
              do {
                bVar1 = *pbVar13;
                uVar7 = 0;
                pbVar13 = pbVar13 + 1;
                pbVar15 = pbVar16 + -1;
                *pbVar16 = bVar1;
                iVar4 = iVar4 + -1;
                uVar12 = uVar8;
                pbVar14 = pbVar13;
                pbVar16 = pbVar15;
              } while (iVar4 != 0);
              goto LAB_000b582a;
            }
            iVar4 = (int)(short)(ushort)bVar1;
            bVar1 = pbVar14[1];
            uVar7 = (uint)bVar1;
            pbVar14 = pbVar14 + 2;
            if (bVar1 != 0xff) {
              while( true ) {
                sVar2 = (short)uVar7;
                uVar8 = uVar12 - iVar4;
                if (uVar8 != 0 && iVar4 <= (int)uVar12) break;
                iVar10 = -uVar8;
                for (iVar4 = iVar4 + uVar8; iVar4 != 0; iVar4 = iVar4 + -1) {
                  *pbVar15 = (byte)uVar7;
                  pbVar15 = pbVar15 + -1;
                }
                uStack_14 = uStack_14 - 1;
                if (uStack_14 == 0) goto LAB_000b5833;
                piStack_24 = piStack_24 + 1;
                pbVar15 = (byte *)(*piStack_24 + iVar3 + dword_d30d0);
                uVar11 = uVar6;
LAB_000b5870:
                iVar4 = iVar10 - uVar11;
                uVar12 = uVar5;
                if (iVar4 == 0) goto LAB_000b582a;
                if (iVar10 < (int)uVar11) goto LAB_000b5911;
              }
              for (; uVar12 = uVar8, iVar4 != 0; iVar4 = iVar4 + -1) {
                *pbVar15 = (byte)uVar7;
                pbVar15 = pbVar15 + -1;
              }
              goto LAB_000b582a;
            }
            pbVar15 = pbVar15 + -iVar4;
            uVar8 = uVar12 - iVar4;
            bVar18 = iVar4 <= (int)uVar12;
            uVar12 = uVar8;
            pbVar13 = pbVar14;
          } while (uVar8 != 0 && bVar18);
        }
        uStack_14 = uStack_14 - 1;
        bVar18 = uStack_14 == 0;
LAB_000b5889:
        sVar2 = (short)uVar7;
        if (bVar18) {
LAB_000b5833:
          return (int)sVar2;
        }
        piStack_24 = piStack_24 + 1;
        uVar11 = uVar8 + uVar6;
      } while (uVar11 == 0 || SCARRY4(uVar8,uVar6) != (int)uVar11 < 0);
      pbVar15 = (byte *)(*piStack_24 + iVar3 + dword_d30d0);
      uStack_18 = uVar11;
      pbVar14 = pbVar13;
    } while( true );
  }
  piStack_24 = (int *)(off_d30cc + iVar4 * 4);
  pbVar15 = (byte *)(*piStack_24 + iVar3 + dword_d30d0);
  uVar7 = uVar5;
LAB_000b55ec:
  do {
    while( true ) {
      bVar1 = *pbVar14;
      pbVar13 = pbVar14 + 1;
      if ((char)bVar1 < '\x01') break;
      iVar4 = (int)(short)(ushort)bVar1;
      bVar1 = *pbVar13;
      pbVar14 = pbVar14 + 2;
      uVar6 = uVar7;
      if (bVar1 == 0xff) {
        pbVar15 = pbVar15 + -iVar4;
        uVar6 = uVar7 - iVar4;
        bVar18 = (int)uVar7 < iVar4;
        uVar7 = uVar6;
        if (uVar6 == 0 || bVar18) {
          do {
            piStack_24 = piStack_24 + 1;
            bVar18 = SCARRY4(uVar6,uVar5);
            uVar6 = uVar6 + uVar5;
          } while (uVar6 == 0 || bVar18 != (int)uVar6 < 0);
          pbVar15 = (byte *)(((*piStack_24 + iVar3 + dword_d30d0) - uVar5) + uVar6);
          uVar7 = uVar6;
        }
      }
      else {
        while (uVar7 = uVar6 - iVar4, uVar7 == 0 || (int)uVar6 < iVar4) {
          for (iVar4 = iVar4 + uVar7; iVar4 != 0; iVar4 = iVar4 + -1) {
            *pbVar15 = bVar1;
            pbVar15 = pbVar15 + -1;
          }
          piStack_24 = piStack_24 + 1;
          pbVar15 = (byte *)(*piStack_24 + iVar3 + dword_d30d0);
          iVar4 = -uVar7;
          uVar6 = uVar5;
        }
        for (; iVar4 != 0; iVar4 = iVar4 + -1) {
          *pbVar15 = bVar1;
          pbVar15 = pbVar15 + -1;
        }
      }
    }
    if (-1 < (char)bVar1) {
      return (int)(short)(ushort)bVar1;
    }
    iVar4 = (int)(short)(ushort)(byte)-bVar1;
    do {
      uVar6 = uVar7 - iVar4;
      pbVar16 = pbVar15;
      if (uVar6 != 0 && iVar4 <= (int)uVar7) goto LAB_000b565e;
      iVar17 = iVar4 + uVar6;
      iVar4 = -uVar6;
      do {
        bVar1 = *pbVar13;
        pbVar13 = pbVar13 + 1;
        *pbVar15 = bVar1;
        iVar17 = iVar17 + -1;
        pbVar15 = pbVar15 + -1;
      } while (iVar17 != 0);
      piStack_24 = piStack_24 + 1;
      pbVar15 = (byte *)(*piStack_24 + iVar3 + dword_d30d0);
      uVar7 = uVar5;
      pbVar14 = pbVar13;
    } while (iVar4 != 0 && (int)uVar6 < 1);
  } while( true );
LAB_000b5911:
  uVar7 = 0;
  uStack_18 = -iVar4;
  goto LAB_000b5915;
LAB_000b565e:
  do {
    bVar1 = *pbVar13;
    pbVar13 = pbVar13 + 1;
    pbVar15 = pbVar16 + -1;
    *pbVar16 = bVar1;
    iVar4 = iVar4 + -1;
    uVar7 = uVar6;
    pbVar14 = pbVar13;
    pbVar16 = pbVar15;
  } while (iVar4 != 0);
  goto LAB_000b55ec;
}


// ================================================================================================
// sub_b56b8 @ 0xb56b8 [__watcall]
// ================================================================================================

uint __watcall sub_b56b8(void)

{
  byte bVar1;
  short sVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  uint uVar11;
  int iVar12;
  byte *pbVar13;
  byte *pbVar14;
  byte *pbVar15;
  byte *pbVar16;
  int iVar17;
  bool bVar18;
  int in_stack_00000004;
  int in_stack_00000008;
  int in_stack_0000000c;
  int *piStack_24;
  uint uStack_18;
  uint uStack_14;
  
  pbVar14 = (byte *)(in_stack_00000004 + 0x10);
  uVar3 = (uint)*(short *)(in_stack_00000004 + 4);
  iVar17 = 0;
  uStack_18 = 0;
  uVar6 = (uint)*(short *)(in_stack_00000004 + 6);
  if (in_stack_0000000c < dword_d30b0) {
    iVar17 = 1;
    uVar4 = (in_stack_0000000c + uVar6) - dword_d30b0;
    if (uVar4 == 0 || (int)(in_stack_0000000c + uVar6) < dword_d30b0) {
      return uVar4;
    }
    uStack_18 = (uVar6 - uVar4) * uVar3;
    uVar6 = (dword_d30b0 + uVar4) - dword_d30b8;
    uStack_14 = uVar4;
    in_stack_0000000c = dword_d30b0;
    if ((uVar6 != 0 && dword_d30b8 <= (int)(dword_d30b0 + uVar4)) &&
       (uStack_14 = uVar4 - uVar6, uStack_14 == 0 || (int)uVar4 < (int)uVar6)) {
      return uVar6;
    }
  }
  else {
    uVar4 = (in_stack_0000000c + uVar6) - dword_d30b8;
    uStack_14 = uVar6;
    if (uVar4 != 0 && dword_d30b8 <= (int)(in_stack_0000000c + uVar6)) {
      iVar17 = 1;
      uStack_14 = uVar6 - uVar4;
      if (uVar6 - uVar4 == 0 || (int)uVar6 < (int)uVar4) {
        return uVar4;
      }
    }
  }
  if (in_stack_00000008 < dword_d30bc) {
    iVar17 = iVar17 + 1;
    uVar6 = (in_stack_00000008 + uVar3) - dword_d30bc;
    if (uVar6 == 0 || (int)(in_stack_00000008 + uVar3) < dword_d30bc) {
      return uVar6;
    }
    if (dword_d30c0 - dword_d30bc <= (int)uVar6) {
      uVar6 = dword_d30c0 - dword_d30bc;
    }
    uVar4 = uVar3 - uVar6;
    uVar3 = uVar6;
    in_stack_00000008 = dword_d30bc;
  }
  else {
    uVar6 = (in_stack_00000008 + uVar3) - dword_d30c0;
    uVar4 = 0;
    if (uVar6 != 0 && dword_d30c0 <= (int)(in_stack_00000008 + uVar3)) {
      uStack_18 = uStack_18 + uVar6;
      if (uVar3 - uVar6 == 0 || (int)uVar3 < (int)uVar6) {
        return uVar6;
      }
      iVar17 = iVar17 + 1;
      uVar3 = uVar3 - uVar6;
      uVar4 = uVar6;
    }
  }
  iVar12 = in_stack_00000008 + uVar3 + -1;
  if (iVar17 != 0) {
    piStack_24 = (int *)(off_d30cc + in_stack_0000000c * 4);
    pbVar15 = (byte *)(*piStack_24 + iVar12 + dword_d30d0);
    uVar11 = uVar3;
    if (uStack_18 == 0) goto LAB_000b582a;
    if ((int)uStack_18 < 0) {
      iVar5 = (uStack_18 & 0x7fff) + 1;
      iVar17 = 0x7fff;
      do {
        while( true ) {
          bVar1 = *pbVar14;
          if ((char)bVar1 < '\x01') break;
          uVar6 = 0;
          iVar9 = (int)(short)(ushort)bVar1;
          pbVar14 = pbVar14 + 2;
          iVar8 = iVar17 - iVar9;
          bVar18 = iVar17 < iVar9;
          iVar17 = iVar8;
          if (iVar8 == 0 || bVar18) {
            uVar10 = iVar8 + iVar5;
            goto LAB_000b592e;
          }
        }
        if (-1 < (char)bVar1) {
          return (int)(short)CONCAT31((int3)(uVar6 >> 8),bVar1);
        }
        uVar6 = 0;
        uVar7 = (uint)(short)(ushort)(byte)-bVar1;
        pbVar14 = pbVar14 + uVar7 + 1;
        iVar9 = iVar17 - uVar7;
        bVar18 = (int)uVar7 <= iVar17;
        iVar17 = iVar9;
      } while (iVar9 != 0 && bVar18);
      pbVar13 = pbVar14 + -uVar7;
      uStack_18 = iVar9 + uVar7 + iVar5;
      goto LAB_000b58fd;
    }
LAB_000b5915:
    do {
      do {
        bVar1 = *pbVar14;
        pbVar13 = pbVar14 + 1;
        if ((char)bVar1 < '\x01') {
          if (-1 < (char)bVar1) {
            return (int)(short)CONCAT31((int3)(uVar6 >> 8),bVar1);
          }
          uVar7 = (uint)(short)(ushort)(byte)-bVar1;
          goto LAB_000b58fd;
        }
        uVar6 = 0;
        iVar9 = (int)(short)(ushort)bVar1;
        pbVar14 = pbVar14 + 2;
        uVar10 = uStack_18 - iVar9;
        bVar18 = iVar9 <= (int)uStack_18;
        uStack_18 = uVar10;
      } while (uVar10 != 0 && bVar18);
LAB_000b592e:
      uVar6 = (uint)pbVar14[-1];
      pbVar13 = pbVar14;
      if (pbVar14[-1] != 0xff) {
        uVar10 = uVar10 + iVar9;
        goto LAB_000b5870;
      }
      do {
        uVar7 = uVar10 + uVar3;
        if (uVar7 != 0 && SCARRY4(uVar10,uVar3) == (int)uVar7 < 0) {
          pbVar15 = (byte *)(((*piStack_24 + iVar12 + dword_d30d0) - uVar3) + uVar7);
          uVar11 = uVar7;
          pbVar14 = pbVar13;
LAB_000b582a:
          do {
            bVar1 = *pbVar14;
            sVar2 = (short)CONCAT31((int3)(uVar6 >> 8),bVar1);
            if ((char)bVar1 < '\x01') {
              if (-1 < (char)bVar1) goto LAB_000b5833;
              iVar17 = (int)(short)(ushort)(byte)-bVar1;
              pbVar13 = pbVar14 + 1;
              while (uVar7 = uVar11 - iVar17, pbVar16 = pbVar15, uVar7 == 0 || (int)uVar11 < iVar17)
              {
                iVar17 = iVar17 + uVar7;
                uVar7 = -uVar7;
                do {
                  bVar1 = *pbVar13;
                  uVar6 = (uint)bVar1;
                  pbVar13 = pbVar13 + 1;
                  *pbVar15 = bVar1;
                  iVar17 = iVar17 + -1;
                  pbVar15 = pbVar15 + -1;
                } while (iVar17 != 0);
                uStack_14 = uStack_14 - 1;
                bVar18 = uStack_14 == 0;
                if (bVar18) goto LAB_000b5889;
                piStack_24 = piStack_24 + 1;
                pbVar15 = (byte *)(*piStack_24 + iVar12 + dword_d30d0);
                uStack_18 = uVar4;
LAB_000b58fd:
                uVar6 = 0;
                pbVar14 = pbVar13 + uStack_18;
                iVar17 = uVar7 - uStack_18;
                uVar11 = uVar3;
                if (iVar17 == 0) goto LAB_000b582a;
                pbVar13 = pbVar14;
                if ((int)uVar7 < (int)uStack_18) {
                  pbVar14 = pbVar14 + iVar17;
                  goto LAB_000b5911;
                }
              }
              do {
                bVar1 = *pbVar13;
                uVar6 = 0;
                pbVar13 = pbVar13 + 1;
                pbVar15 = pbVar16 + -1;
                *pbVar16 = bVar1;
                iVar17 = iVar17 + -1;
                uVar11 = uVar7;
                pbVar14 = pbVar13;
                pbVar16 = pbVar15;
              } while (iVar17 != 0);
              goto LAB_000b582a;
            }
            iVar17 = (int)(short)(ushort)bVar1;
            bVar1 = pbVar14[1];
            uVar6 = (uint)bVar1;
            pbVar14 = pbVar14 + 2;
            if (bVar1 != 0xff) {
              while( true ) {
                sVar2 = (short)uVar6;
                uVar7 = uVar11 - iVar17;
                if (uVar7 != 0 && iVar17 <= (int)uVar11) break;
                iVar9 = -uVar7;
                for (iVar17 = iVar17 + uVar7; iVar17 != 0; iVar17 = iVar17 + -1) {
                  *pbVar15 = (byte)uVar6;
                  pbVar15 = pbVar15 + -1;
                }
                uStack_14 = uStack_14 - 1;
                if (uStack_14 == 0) goto LAB_000b5833;
                piStack_24 = piStack_24 + 1;
                pbVar15 = (byte *)(*piStack_24 + iVar12 + dword_d30d0);
                uVar10 = uVar4;
LAB_000b5870:
                iVar17 = iVar9 - uVar10;
                uVar11 = uVar3;
                if (iVar17 == 0) goto LAB_000b582a;
                if (iVar9 < (int)uVar10) goto LAB_000b5911;
              }
              for (; uVar11 = uVar7, iVar17 != 0; iVar17 = iVar17 + -1) {
                *pbVar15 = (byte)uVar6;
                pbVar15 = pbVar15 + -1;
              }
              goto LAB_000b582a;
            }
            pbVar15 = pbVar15 + -iVar17;
            uVar7 = uVar11 - iVar17;
            bVar18 = iVar17 <= (int)uVar11;
            uVar11 = uVar7;
            pbVar13 = pbVar14;
          } while (uVar7 != 0 && bVar18);
        }
        uStack_14 = uStack_14 - 1;
        bVar18 = uStack_14 == 0;
LAB_000b5889:
        sVar2 = (short)uVar6;
        if (bVar18) {
LAB_000b5833:
          return (int)sVar2;
        }
        piStack_24 = piStack_24 + 1;
        uVar10 = uVar7 + uVar4;
      } while (uVar10 == 0 || SCARRY4(uVar7,uVar4) != (int)uVar10 < 0);
      pbVar15 = (byte *)(*piStack_24 + iVar12 + dword_d30d0);
      uStack_18 = uVar10;
      pbVar14 = pbVar13;
    } while( true );
  }
  piStack_24 = (int *)(off_d30cc + in_stack_0000000c * 4);
  pbVar15 = (byte *)(*piStack_24 + iVar12 + dword_d30d0);
  uVar6 = uVar3;
LAB_000b55ec:
  do {
    while( true ) {
      bVar1 = *pbVar14;
      pbVar13 = pbVar14 + 1;
      if ((char)bVar1 < '\x01') break;
      iVar17 = (int)(short)(ushort)bVar1;
      bVar1 = *pbVar13;
      pbVar14 = pbVar14 + 2;
      uVar4 = uVar6;
      if (bVar1 == 0xff) {
        pbVar15 = pbVar15 + -iVar17;
        uVar4 = uVar6 - iVar17;
        bVar18 = (int)uVar6 < iVar17;
        uVar6 = uVar4;
        if (uVar4 == 0 || bVar18) {
          do {
            piStack_24 = piStack_24 + 1;
            bVar18 = SCARRY4(uVar4,uVar3);
            uVar4 = uVar4 + uVar3;
          } while (uVar4 == 0 || bVar18 != (int)uVar4 < 0);
          pbVar15 = (byte *)(((*piStack_24 + iVar12 + dword_d30d0) - uVar3) + uVar4);
          uVar6 = uVar4;
        }
      }
      else {
        while (uVar6 = uVar4 - iVar17, uVar6 == 0 || (int)uVar4 < iVar17) {
          for (iVar17 = iVar17 + uVar6; iVar17 != 0; iVar17 = iVar17 + -1) {
            *pbVar15 = bVar1;
            pbVar15 = pbVar15 + -1;
          }
          piStack_24 = piStack_24 + 1;
          pbVar15 = (byte *)(*piStack_24 + iVar12 + dword_d30d0);
          iVar17 = -uVar6;
          uVar4 = uVar3;
        }
        for (; iVar17 != 0; iVar17 = iVar17 + -1) {
          *pbVar15 = bVar1;
          pbVar15 = pbVar15 + -1;
        }
      }
    }
    if (-1 < (char)bVar1) {
      return (int)(short)(ushort)bVar1;
    }
    iVar17 = (int)(short)(ushort)(byte)-bVar1;
    do {
      uVar4 = uVar6 - iVar17;
      pbVar16 = pbVar15;
      if (uVar4 != 0 && iVar17 <= (int)uVar6) goto LAB_000b565e;
      iVar5 = iVar17 + uVar4;
      iVar17 = -uVar4;
      do {
        bVar1 = *pbVar13;
        pbVar13 = pbVar13 + 1;
        *pbVar15 = bVar1;
        iVar5 = iVar5 + -1;
        pbVar15 = pbVar15 + -1;
      } while (iVar5 != 0);
      piStack_24 = piStack_24 + 1;
      pbVar15 = (byte *)(*piStack_24 + iVar12 + dword_d30d0);
      uVar6 = uVar3;
      pbVar14 = pbVar13;
    } while (iVar17 != 0 && (int)uVar4 < 1);
  } while( true );
LAB_000b5911:
  uVar6 = 0;
  uStack_18 = -iVar17;
  goto LAB_000b5915;
LAB_000b565e:
  do {
    bVar1 = *pbVar13;
    pbVar13 = pbVar13 + 1;
    pbVar15 = pbVar16 + -1;
    *pbVar16 = bVar1;
    iVar17 = iVar17 + -1;
    uVar6 = uVar4;
    pbVar14 = pbVar13;
    pbVar16 = pbVar15;
  } while (iVar17 != 0);
  goto LAB_000b55ec;
}


// ================================================================================================
// sub_b56d2 @ 0xb56d2 [__watcall]
// ================================================================================================

uint __watcall sub_b56d2(void)

{
  byte bVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  uint uVar11;
  uint uVar12;
  byte *pbVar13;
  byte *pbVar14;
  byte *pbVar15;
  byte *pbVar16;
  int iVar17;
  bool bVar18;
  int in_stack_00000004;
  int *local_24;
  uint local_18;
  uint local_14;
  
  iVar3 = (int)*(short *)(in_stack_00000004 + 0xc);
  iVar4 = (int)*(short *)(in_stack_00000004 + 0xe);
  pbVar14 = (byte *)(in_stack_00000004 + 0x10);
  uVar5 = (uint)*(short *)(in_stack_00000004 + 4);
  iVar17 = 0;
  local_18 = 0;
  uVar7 = (uint)*(short *)(in_stack_00000004 + 6);
  if (iVar4 < dword_d30b0) {
    iVar17 = 1;
    uVar6 = (iVar4 + uVar7) - dword_d30b0;
    if (uVar6 == 0 || (int)(iVar4 + uVar7) < dword_d30b0) {
      return uVar6;
    }
    local_18 = (uVar7 - uVar6) * uVar5;
    uVar7 = (dword_d30b0 + uVar6) - dword_d30b8;
    local_14 = uVar6;
    iVar4 = dword_d30b0;
    if ((uVar7 != 0 && dword_d30b8 <= (int)(dword_d30b0 + uVar6)) &&
       (local_14 = uVar6 - uVar7, local_14 == 0 || (int)uVar6 < (int)uVar7)) {
      return uVar7;
    }
  }
  else {
    uVar6 = (iVar4 + uVar7) - dword_d30b8;
    local_14 = uVar7;
    if (uVar6 != 0 && dword_d30b8 <= (int)(iVar4 + uVar7)) {
      iVar17 = 1;
      local_14 = uVar7 - uVar6;
      if (uVar7 - uVar6 == 0 || (int)uVar7 < (int)uVar6) {
        return uVar6;
      }
    }
  }
  if (iVar3 < dword_d30bc) {
    iVar17 = iVar17 + 1;
    uVar7 = (iVar3 + uVar5) - dword_d30bc;
    if (uVar7 == 0 || (int)(iVar3 + uVar5) < dword_d30bc) {
      return uVar7;
    }
    if (dword_d30c0 - dword_d30bc <= (int)uVar7) {
      uVar7 = dword_d30c0 - dword_d30bc;
    }
    uVar6 = uVar5 - uVar7;
    uVar5 = uVar7;
    iVar3 = dword_d30bc;
  }
  else {
    uVar7 = (iVar3 + uVar5) - dword_d30c0;
    uVar6 = 0;
    if (uVar7 != 0 && dword_d30c0 <= (int)(iVar3 + uVar5)) {
      local_18 = local_18 + uVar7;
      if (uVar5 - uVar7 == 0 || (int)uVar5 < (int)uVar7) {
        return uVar7;
      }
      iVar17 = iVar17 + 1;
      uVar5 = uVar5 - uVar7;
      uVar6 = uVar7;
    }
  }
  iVar3 = iVar3 + uVar5 + -1;
  if (iVar17 != 0) {
    local_24 = (int *)(off_d30cc + iVar4 * 4);
    pbVar15 = (byte *)(*local_24 + iVar3 + dword_d30d0);
    uVar12 = uVar5;
    if (local_18 == 0) goto LAB_000b582a;
    if ((int)local_18 < 0) {
      iVar17 = (local_18 & 0x7fff) + 1;
      iVar4 = 0x7fff;
      do {
        while( true ) {
          bVar1 = *pbVar14;
          if ((char)bVar1 < '\x01') break;
          uVar7 = 0;
          iVar10 = (int)(short)(ushort)bVar1;
          pbVar14 = pbVar14 + 2;
          iVar9 = iVar4 - iVar10;
          bVar18 = iVar4 < iVar10;
          iVar4 = iVar9;
          if (iVar9 == 0 || bVar18) {
            uVar11 = iVar9 + iVar17;
            goto LAB_000b592e;
          }
        }
        if (-1 < (char)bVar1) {
          return (int)(short)CONCAT31((int3)(uVar7 >> 8),bVar1);
        }
        uVar7 = 0;
        uVar8 = (uint)(short)(ushort)(byte)-bVar1;
        pbVar14 = pbVar14 + uVar8 + 1;
        iVar10 = iVar4 - uVar8;
        bVar18 = (int)uVar8 <= iVar4;
        iVar4 = iVar10;
      } while (iVar10 != 0 && bVar18);
      pbVar13 = pbVar14 + -uVar8;
      local_18 = iVar10 + uVar8 + iVar17;
      goto LAB_000b58fd;
    }
LAB_000b5915:
    do {
      do {
        bVar1 = *pbVar14;
        pbVar13 = pbVar14 + 1;
        if ((char)bVar1 < '\x01') {
          if (-1 < (char)bVar1) {
            return (int)(short)CONCAT31((int3)(uVar7 >> 8),bVar1);
          }
          uVar8 = (uint)(short)(ushort)(byte)-bVar1;
          goto LAB_000b58fd;
        }
        uVar7 = 0;
        iVar10 = (int)(short)(ushort)bVar1;
        pbVar14 = pbVar14 + 2;
        uVar11 = local_18 - iVar10;
        bVar18 = iVar10 <= (int)local_18;
        local_18 = uVar11;
      } while (uVar11 != 0 && bVar18);
LAB_000b592e:
      uVar7 = (uint)pbVar14[-1];
      pbVar13 = pbVar14;
      if (pbVar14[-1] != 0xff) {
        uVar11 = uVar11 + iVar10;
        goto LAB_000b5870;
      }
      do {
        uVar8 = uVar11 + uVar5;
        if (uVar8 != 0 && SCARRY4(uVar11,uVar5) == (int)uVar8 < 0) {
          pbVar15 = (byte *)(((*local_24 + iVar3 + dword_d30d0) - uVar5) + uVar8);
          uVar12 = uVar8;
          pbVar14 = pbVar13;
LAB_000b582a:
          do {
            bVar1 = *pbVar14;
            sVar2 = (short)CONCAT31((int3)(uVar7 >> 8),bVar1);
            if ((char)bVar1 < '\x01') {
              if (-1 < (char)bVar1) goto LAB_000b5833;
              iVar4 = (int)(short)(ushort)(byte)-bVar1;
              pbVar13 = pbVar14 + 1;
              while (uVar8 = uVar12 - iVar4, pbVar16 = pbVar15, uVar8 == 0 || (int)uVar12 < iVar4) {
                iVar4 = iVar4 + uVar8;
                uVar8 = -uVar8;
                do {
                  bVar1 = *pbVar13;
                  uVar7 = (uint)bVar1;
                  pbVar13 = pbVar13 + 1;
                  *pbVar15 = bVar1;
                  iVar4 = iVar4 + -1;
                  pbVar15 = pbVar15 + -1;
                } while (iVar4 != 0);
                local_14 = local_14 - 1;
                bVar18 = local_14 == 0;
                if (bVar18) goto LAB_000b5889;
                local_24 = local_24 + 1;
                pbVar15 = (byte *)(*local_24 + iVar3 + dword_d30d0);
                local_18 = uVar6;
LAB_000b58fd:
                uVar7 = 0;
                pbVar14 = pbVar13 + local_18;
                iVar4 = uVar8 - local_18;
                uVar12 = uVar5;
                if (iVar4 == 0) goto LAB_000b582a;
                pbVar13 = pbVar14;
                if ((int)uVar8 < (int)local_18) {
                  pbVar14 = pbVar14 + iVar4;
                  goto LAB_000b5911;
                }
              }
              do {
                bVar1 = *pbVar13;
                uVar7 = 0;
                pbVar13 = pbVar13 + 1;
                pbVar15 = pbVar16 + -1;
                *pbVar16 = bVar1;
                iVar4 = iVar4 + -1;
                uVar12 = uVar8;
                pbVar14 = pbVar13;
                pbVar16 = pbVar15;
              } while (iVar4 != 0);
              goto LAB_000b582a;
            }
            iVar4 = (int)(short)(ushort)bVar1;
            bVar1 = pbVar14[1];
            uVar7 = (uint)bVar1;
            pbVar14 = pbVar14 + 2;
            if (bVar1 != 0xff) {
              while( true ) {
                sVar2 = (short)uVar7;
                uVar8 = uVar12 - iVar4;
                if (uVar8 != 0 && iVar4 <= (int)uVar12) break;
                iVar10 = -uVar8;
                for (iVar4 = iVar4 + uVar8; iVar4 != 0; iVar4 = iVar4 + -1) {
                  *pbVar15 = (byte)uVar7;
                  pbVar15 = pbVar15 + -1;
                }
                local_14 = local_14 - 1;
                if (local_14 == 0) goto LAB_000b5833;
                local_24 = local_24 + 1;
                pbVar15 = (byte *)(*local_24 + iVar3 + dword_d30d0);
                uVar11 = uVar6;
LAB_000b5870:
                iVar4 = iVar10 - uVar11;
                uVar12 = uVar5;
                if (iVar4 == 0) goto LAB_000b582a;
                if (iVar10 < (int)uVar11) goto LAB_000b5911;
              }
              for (; uVar12 = uVar8, iVar4 != 0; iVar4 = iVar4 + -1) {
                *pbVar15 = (byte)uVar7;
                pbVar15 = pbVar15 + -1;
              }
              goto LAB_000b582a;
            }
            pbVar15 = pbVar15 + -iVar4;
            uVar8 = uVar12 - iVar4;
            bVar18 = iVar4 <= (int)uVar12;
            uVar12 = uVar8;
            pbVar13 = pbVar14;
          } while (uVar8 != 0 && bVar18);
        }
        local_14 = local_14 - 1;
        bVar18 = local_14 == 0;
LAB_000b5889:
        sVar2 = (short)uVar7;
        if (bVar18) {
LAB_000b5833:
          return (int)sVar2;
        }
        local_24 = local_24 + 1;
        uVar11 = uVar8 + uVar6;
      } while (uVar11 == 0 || SCARRY4(uVar8,uVar6) != (int)uVar11 < 0);
      pbVar15 = (byte *)(*local_24 + iVar3 + dword_d30d0);
      local_18 = uVar11;
      pbVar14 = pbVar13;
    } while( true );
  }
  local_24 = (int *)(off_d30cc + iVar4 * 4);
  pbVar15 = (byte *)(*local_24 + iVar3 + dword_d30d0);
  uVar7 = uVar5;
LAB_000b55ec:
  do {
    while( true ) {
      bVar1 = *pbVar14;
      pbVar13 = pbVar14 + 1;
      if ((char)bVar1 < '\x01') break;
      iVar4 = (int)(short)(ushort)bVar1;
      bVar1 = *pbVar13;
      pbVar14 = pbVar14 + 2;
      uVar6 = uVar7;
      if (bVar1 == 0xff) {
        pbVar15 = pbVar15 + -iVar4;
        uVar6 = uVar7 - iVar4;
        bVar18 = (int)uVar7 < iVar4;
        uVar7 = uVar6;
        if (uVar6 == 0 || bVar18) {
          do {
            local_24 = local_24 + 1;
            bVar18 = SCARRY4(uVar6,uVar5);
            uVar6 = uVar6 + uVar5;
          } while (uVar6 == 0 || bVar18 != (int)uVar6 < 0);
          pbVar15 = (byte *)(((*local_24 + iVar3 + dword_d30d0) - uVar5) + uVar6);
          uVar7 = uVar6;
        }
      }
      else {
        while (uVar7 = uVar6 - iVar4, uVar7 == 0 || (int)uVar6 < iVar4) {
          for (iVar4 = iVar4 + uVar7; iVar4 != 0; iVar4 = iVar4 + -1) {
            *pbVar15 = bVar1;
            pbVar15 = pbVar15 + -1;
          }
          local_24 = local_24 + 1;
          pbVar15 = (byte *)(*local_24 + iVar3 + dword_d30d0);
          iVar4 = -uVar7;
          uVar6 = uVar5;
        }
        for (; iVar4 != 0; iVar4 = iVar4 + -1) {
          *pbVar15 = bVar1;
          pbVar15 = pbVar15 + -1;
        }
      }
    }
    if (-1 < (char)bVar1) {
      return (int)(short)(ushort)bVar1;
    }
    iVar4 = (int)(short)(ushort)(byte)-bVar1;
    do {
      uVar6 = uVar7 - iVar4;
      pbVar16 = pbVar15;
      if (uVar6 != 0 && iVar4 <= (int)uVar7) goto LAB_000b565e;
      iVar17 = iVar4 + uVar6;
      iVar4 = -uVar6;
      do {
        bVar1 = *pbVar13;
        pbVar13 = pbVar13 + 1;
        *pbVar15 = bVar1;
        iVar17 = iVar17 + -1;
        pbVar15 = pbVar15 + -1;
      } while (iVar17 != 0);
      local_24 = local_24 + 1;
      pbVar15 = (byte *)(*local_24 + iVar3 + dword_d30d0);
      uVar7 = uVar5;
      pbVar14 = pbVar13;
    } while (iVar4 != 0 && (int)uVar6 < 1);
  } while( true );
LAB_000b5911:
  uVar7 = 0;
  local_18 = -iVar4;
  goto LAB_000b5915;
LAB_000b565e:
  do {
    bVar1 = *pbVar13;
    pbVar13 = pbVar13 + 1;
    pbVar15 = pbVar16 + -1;
    *pbVar16 = bVar1;
    iVar4 = iVar4 + -1;
    uVar7 = uVar6;
    pbVar14 = pbVar13;
    pbVar16 = pbVar15;
  } while (iVar4 != 0);
  goto LAB_000b55ec;
}


// ================================================================================================
// sub_b594c @ 0xb594c [__watcall]
// ================================================================================================

byte __watcall sub_b594c(void)

{
  int iVar1;
  byte bVar2;
  undefined uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  byte *pbVar8;
  byte *pbVar9;
  undefined *puVar10;
  undefined *puVar11;
  bool bVar12;
  int in_stack_00000004;
  short in_stack_00000008;
  short in_stack_0000000c;
  int *piStack_24;
  
  iVar4 = (int)*(short *)(in_stack_00000004 + 4);
  iVar1 = (int)(short)((in_stack_00000008 - *(short *)(in_stack_00000004 + 4)) +
                      *(short *)(in_stack_00000004 + 8)) + iVar4 + -1;
  piStack_24 = (int *)(off_d30cc +
                      (short)(in_stack_0000000c - *(short *)(in_stack_00000004 + 10)) * 4);
  puVar10 = (undefined *)(*piStack_24 + iVar1 + dword_d30d0);
  iVar6 = iVar4;
  pbVar9 = (byte *)(in_stack_00000004 + 0x10);
LAB_000b59dc:
  do {
    while( true ) {
      bVar2 = *pbVar9;
      pbVar8 = pbVar9 + 1;
      if ((char)bVar2 < '\x01') break;
      iVar5 = (int)(short)(ushort)bVar2;
      pbVar9 = pbVar9 + 2;
      if (*pbVar8 == 0xff) {
        puVar10 = puVar10 + -iVar5;
        iVar7 = iVar6 - iVar5;
        bVar12 = iVar6 < iVar5;
        iVar6 = iVar7;
        if (iVar7 == 0 || bVar12) {
          do {
            piStack_24 = piStack_24 + 1;
            bVar12 = SCARRY4(iVar7,iVar4);
            iVar7 = iVar7 + iVar4;
          } while (iVar7 == 0 || bVar12 != iVar7 < 0);
          puVar10 = (undefined *)(((*piStack_24 + iVar1 + dword_d30d0) - iVar4) + iVar7);
          iVar6 = iVar7;
        }
      }
      else {
        uVar3 = *(undefined *)((int)&unk_d42e4 + (int)(short)(ushort)*pbVar8);
        while (iVar7 = iVar6 - iVar5, iVar7 == 0 || iVar6 < iVar5) {
          for (iVar5 = iVar5 + iVar7; iVar5 != 0; iVar5 = iVar5 + -1) {
            *puVar10 = uVar3;
            puVar10 = puVar10 + -1;
          }
          piStack_24 = piStack_24 + 1;
          puVar10 = (undefined *)(*piStack_24 + iVar1 + dword_d30d0);
          iVar5 = -iVar7;
          iVar6 = iVar4;
        }
        for (; iVar6 = iVar7, iVar5 != 0; iVar5 = iVar5 + -1) {
          *puVar10 = uVar3;
          puVar10 = puVar10 + -1;
        }
      }
    }
    if (-1 < (char)bVar2) {
      return bVar2;
    }
    iVar5 = (int)(short)(ushort)(byte)-bVar2;
    do {
      iVar7 = iVar6 - iVar5;
      puVar11 = puVar10;
      if (iVar7 != 0 && iVar5 <= iVar6) goto LAB_000b5a57;
      iVar6 = iVar5 + iVar7;
      iVar5 = -iVar7;
      do {
        bVar2 = *pbVar8;
        pbVar8 = pbVar8 + 1;
        *puVar10 = *(undefined *)((int)&unk_d42e4 + (int)(short)(ushort)bVar2);
        iVar6 = iVar6 + -1;
        puVar10 = puVar10 + -1;
      } while (iVar6 != 0);
      piStack_24 = piStack_24 + 1;
      puVar10 = (undefined *)(*piStack_24 + iVar1 + dword_d30d0);
      iVar6 = iVar4;
      pbVar9 = pbVar8;
    } while (iVar5 != 0 && iVar7 < 1);
  } while( true );
LAB_000b5a57:
  do {
    bVar2 = *pbVar8;
    pbVar8 = pbVar8 + 1;
    puVar10 = puVar11 + -1;
    *puVar11 = *(undefined *)((int)&unk_d42e4 + (int)(short)(ushort)bVar2);
    iVar5 = iVar5 + -1;
    iVar6 = iVar7;
    pbVar9 = pbVar8;
    puVar11 = puVar10;
  } while (iVar5 != 0);
  goto LAB_000b59dc;
}


// ================================================================================================
// sub_b5974 @ 0xb5974 [__watcall]
// ================================================================================================

byte __watcall sub_b5974(void)

{
  byte bVar1;
  undefined uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  byte *pbVar7;
  byte *pbVar8;
  undefined *puVar9;
  undefined *puVar10;
  bool bVar11;
  int in_stack_00000004;
  int in_stack_00000008;
  int in_stack_0000000c;
  int *piStack_24;
  
  iVar3 = (int)*(short *)(in_stack_00000004 + 4);
  in_stack_00000008 = in_stack_00000008 + iVar3 + -1;
  piStack_24 = (int *)(off_d30cc + in_stack_0000000c * 4);
  puVar9 = (undefined *)(*piStack_24 + in_stack_00000008 + dword_d30d0);
  iVar5 = iVar3;
  pbVar8 = (byte *)(in_stack_00000004 + 0x10);
LAB_000b59dc:
  do {
    while( true ) {
      bVar1 = *pbVar8;
      pbVar7 = pbVar8 + 1;
      if ((char)bVar1 < '\x01') break;
      iVar4 = (int)(short)(ushort)bVar1;
      pbVar8 = pbVar8 + 2;
      if (*pbVar7 == 0xff) {
        puVar9 = puVar9 + -iVar4;
        iVar6 = iVar5 - iVar4;
        bVar11 = iVar5 < iVar4;
        iVar5 = iVar6;
        if (iVar6 == 0 || bVar11) {
          do {
            piStack_24 = piStack_24 + 1;
            bVar11 = SCARRY4(iVar6,iVar3);
            iVar6 = iVar6 + iVar3;
          } while (iVar6 == 0 || bVar11 != iVar6 < 0);
          puVar9 = (undefined *)(((*piStack_24 + in_stack_00000008 + dword_d30d0) - iVar3) + iVar6);
          iVar5 = iVar6;
        }
      }
      else {
        uVar2 = *(undefined *)((int)&unk_d42e4 + (int)(short)(ushort)*pbVar7);
        while (iVar6 = iVar5 - iVar4, iVar6 == 0 || iVar5 < iVar4) {
          for (iVar4 = iVar4 + iVar6; iVar4 != 0; iVar4 = iVar4 + -1) {
            *puVar9 = uVar2;
            puVar9 = puVar9 + -1;
          }
          piStack_24 = piStack_24 + 1;
          puVar9 = (undefined *)(*piStack_24 + in_stack_00000008 + dword_d30d0);
          iVar4 = -iVar6;
          iVar5 = iVar3;
        }
        for (; iVar5 = iVar6, iVar4 != 0; iVar4 = iVar4 + -1) {
          *puVar9 = uVar2;
          puVar9 = puVar9 + -1;
        }
      }
    }
    if (-1 < (char)bVar1) {
      return bVar1;
    }
    iVar4 = (int)(short)(ushort)(byte)-bVar1;
    do {
      iVar6 = iVar5 - iVar4;
      puVar10 = puVar9;
      if (iVar6 != 0 && iVar4 <= iVar5) goto LAB_000b5a57;
      iVar5 = iVar4 + iVar6;
      iVar4 = -iVar6;
      do {
        bVar1 = *pbVar7;
        pbVar7 = pbVar7 + 1;
        *puVar9 = *(undefined *)((int)&unk_d42e4 + (int)(short)(ushort)bVar1);
        iVar5 = iVar5 + -1;
        puVar9 = puVar9 + -1;
      } while (iVar5 != 0);
      piStack_24 = piStack_24 + 1;
      puVar9 = (undefined *)(*piStack_24 + in_stack_00000008 + dword_d30d0);
      iVar5 = iVar3;
      pbVar8 = pbVar7;
    } while (iVar4 != 0 && iVar6 < 1);
  } while( true );
LAB_000b5a57:
  do {
    bVar1 = *pbVar7;
    pbVar7 = pbVar7 + 1;
    puVar9 = puVar10 + -1;
    *puVar10 = *(undefined *)((int)&unk_d42e4 + (int)(short)(ushort)bVar1);
    iVar4 = iVar4 + -1;
    iVar5 = iVar6;
    pbVar8 = pbVar7;
    puVar10 = puVar9;
  } while (iVar4 != 0);
  goto LAB_000b59dc;
}


// ================================================================================================
// sub_b598e @ 0xb598e [__watcall]
// ================================================================================================

byte __watcall sub_b598e(void)

{
  int iVar1;
  byte bVar2;
  undefined uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  byte *pbVar8;
  byte *pbVar9;
  undefined *puVar10;
  undefined *puVar11;
  bool bVar12;
  int in_stack_00000004;
  int *local_24;
  
  iVar4 = (int)*(short *)(in_stack_00000004 + 4);
  iVar1 = (int)*(short *)(in_stack_00000004 + 0xc) + iVar4 + -1;
  local_24 = (int *)(off_d30cc + *(short *)(in_stack_00000004 + 0xe) * 4);
  puVar10 = (undefined *)(*local_24 + iVar1 + dword_d30d0);
  iVar6 = iVar4;
  pbVar9 = (byte *)(in_stack_00000004 + 0x10);
LAB_000b59dc:
  do {
    while( true ) {
      bVar2 = *pbVar9;
      pbVar8 = pbVar9 + 1;
      if ((char)bVar2 < '\x01') break;
      iVar5 = (int)(short)(ushort)bVar2;
      pbVar9 = pbVar9 + 2;
      if (*pbVar8 == 0xff) {
        puVar10 = puVar10 + -iVar5;
        iVar7 = iVar6 - iVar5;
        bVar12 = iVar6 < iVar5;
        iVar6 = iVar7;
        if (iVar7 == 0 || bVar12) {
          do {
            local_24 = local_24 + 1;
            bVar12 = SCARRY4(iVar7,iVar4);
            iVar7 = iVar7 + iVar4;
          } while (iVar7 == 0 || bVar12 != iVar7 < 0);
          puVar10 = (undefined *)(((*local_24 + iVar1 + dword_d30d0) - iVar4) + iVar7);
          iVar6 = iVar7;
        }
      }
      else {
        uVar3 = *(undefined *)((int)&unk_d42e4 + (int)(short)(ushort)*pbVar8);
        while (iVar7 = iVar6 - iVar5, iVar7 == 0 || iVar6 < iVar5) {
          for (iVar5 = iVar5 + iVar7; iVar5 != 0; iVar5 = iVar5 + -1) {
            *puVar10 = uVar3;
            puVar10 = puVar10 + -1;
          }
          local_24 = local_24 + 1;
          puVar10 = (undefined *)(*local_24 + iVar1 + dword_d30d0);
          iVar5 = -iVar7;
          iVar6 = iVar4;
        }
        for (; iVar6 = iVar7, iVar5 != 0; iVar5 = iVar5 + -1) {
          *puVar10 = uVar3;
          puVar10 = puVar10 + -1;
        }
      }
    }
    if (-1 < (char)bVar2) {
      return bVar2;
    }
    iVar5 = (int)(short)(ushort)(byte)-bVar2;
    do {
      iVar7 = iVar6 - iVar5;
      puVar11 = puVar10;
      if (iVar7 != 0 && iVar5 <= iVar6) goto LAB_000b5a57;
      iVar6 = iVar5 + iVar7;
      iVar5 = -iVar7;
      do {
        bVar2 = *pbVar8;
        pbVar8 = pbVar8 + 1;
        *puVar10 = *(undefined *)((int)&unk_d42e4 + (int)(short)(ushort)bVar2);
        iVar6 = iVar6 + -1;
        puVar10 = puVar10 + -1;
      } while (iVar6 != 0);
      local_24 = local_24 + 1;
      puVar10 = (undefined *)(*local_24 + iVar1 + dword_d30d0);
      iVar6 = iVar4;
      pbVar9 = pbVar8;
    } while (iVar5 != 0 && iVar7 < 1);
  } while( true );
LAB_000b5a57:
  do {
    bVar2 = *pbVar8;
    pbVar8 = pbVar8 + 1;
    puVar10 = puVar11 + -1;
    *puVar11 = *(undefined *)((int)&unk_d42e4 + (int)(short)(ushort)bVar2);
    iVar5 = iVar5 + -1;
    iVar6 = iVar7;
    pbVar9 = pbVar8;
    puVar11 = puVar10;
  } while (iVar5 != 0);
  goto LAB_000b59dc;
}


// ================================================================================================
// sub_b5aa0 @ 0xb5aa0 [__watcall]
// ================================================================================================

uint __watcall sub_b5aa0(void)

{
  byte bVar1;
  undefined uVar2;
  short sVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  int iVar10;
  int iVar11;
  uint uVar12;
  uint uVar13;
  byte *pbVar14;
  byte *pbVar15;
  byte *pbVar16;
  undefined *puVar17;
  undefined *puVar18;
  int iVar19;
  byte *pbVar20;
  bool bVar21;
  int in_stack_00000004;
  short in_stack_00000008;
  short in_stack_0000000c;
  int *piStack_24;
  uint uStack_18;
  uint uStack_14;
  
  iVar4 = (int)(short)((in_stack_00000008 - *(short *)(in_stack_00000004 + 4)) +
                      *(short *)(in_stack_00000004 + 8));
  iVar5 = (int)(short)(in_stack_0000000c - *(short *)(in_stack_00000004 + 10));
  pbVar15 = (byte *)(in_stack_00000004 + 0x10);
  uVar6 = (uint)*(short *)(in_stack_00000004 + 4);
  iVar19 = 0;
  uStack_18 = 0;
  uVar8 = (uint)*(short *)(in_stack_00000004 + 6);
  if (iVar5 < dword_d30b0) {
    iVar19 = 1;
    uVar7 = (iVar5 + uVar8) - dword_d30b0;
    if (uVar7 == 0 || (int)(iVar5 + uVar8) < dword_d30b0) {
      return uVar7;
    }
    uStack_18 = (uVar8 - uVar7) * uVar6;
    uVar8 = (dword_d30b0 + uVar7) - dword_d30b8;
    uStack_14 = uVar7;
    iVar5 = dword_d30b0;
    if ((uVar8 != 0 && dword_d30b8 <= (int)(dword_d30b0 + uVar7)) &&
       (uStack_14 = uVar7 - uVar8, uStack_14 == 0 || (int)uVar7 < (int)uVar8)) {
      return uVar8;
    }
  }
  else {
    uVar7 = (iVar5 + uVar8) - dword_d30b8;
    uStack_14 = uVar8;
    if (uVar7 != 0 && dword_d30b8 <= (int)(iVar5 + uVar8)) {
      iVar19 = 1;
      uStack_14 = uVar8 - uVar7;
      if (uVar8 - uVar7 == 0 || (int)uVar8 < (int)uVar7) {
        return uVar7;
      }
    }
  }
  if (iVar4 < dword_d30bc) {
    iVar19 = iVar19 + 1;
    uVar8 = (iVar4 + uVar6) - dword_d30bc;
    if (uVar8 == 0 || (int)(iVar4 + uVar6) < dword_d30bc) {
      return uVar8;
    }
    if (dword_d30c0 - dword_d30bc <= (int)uVar8) {
      uVar8 = dword_d30c0 - dword_d30bc;
    }
    uVar7 = uVar6 - uVar8;
    uVar6 = uVar8;
    iVar4 = dword_d30bc;
  }
  else {
    uVar8 = (iVar4 + uVar6) - dword_d30c0;
    uVar7 = 0;
    if (uVar8 != 0 && dword_d30c0 <= (int)(iVar4 + uVar6)) {
      uStack_18 = uStack_18 + uVar8;
      if (uVar6 - uVar8 == 0 || (int)uVar6 < (int)uVar8) {
        return uVar8;
      }
      iVar19 = iVar19 + 1;
      uVar6 = uVar6 - uVar8;
      uVar7 = uVar8;
    }
  }
  iVar4 = iVar4 + uVar6 + -1;
  if (iVar19 != 0) {
    piStack_24 = (int *)(off_d30cc + iVar5 * 4);
    pbVar14 = (byte *)(*piStack_24 + iVar4 + dword_d30d0);
    uVar13 = uVar6;
    if (uStack_18 == 0) goto LAB_000b5c38;
    if ((int)uStack_18 < 0) {
      iVar19 = (uStack_18 & 0x7fff) + 1;
      iVar5 = 0x7fff;
      do {
        while( true ) {
          bVar1 = *pbVar15;
          if ((char)bVar1 < '\x01') break;
          uVar8 = 0;
          iVar11 = (int)(short)(ushort)bVar1;
          pbVar15 = pbVar15 + 2;
          iVar10 = iVar5 - iVar11;
          bVar21 = iVar5 < iVar11;
          iVar5 = iVar10;
          if (iVar10 == 0 || bVar21) {
            uVar12 = iVar10 + iVar19;
            goto LAB_000b5d5b;
          }
        }
        if (-1 < (char)bVar1) {
          return (int)(short)CONCAT31((int3)(uVar8 >> 8),bVar1);
        }
        uVar8 = 0;
        uVar9 = (uint)(short)(ushort)(byte)-bVar1;
        pbVar15 = pbVar15 + uVar9 + 1;
        iVar11 = iVar5 - uVar9;
        bVar21 = (int)uVar9 <= iVar5;
        iVar5 = iVar11;
      } while (iVar11 != 0 && bVar21);
      pbVar16 = pbVar15 + -uVar9;
      uStack_18 = iVar11 + uVar9 + iVar19;
      goto LAB_000b5d2a;
    }
LAB_000b5d42:
    do {
      do {
        bVar1 = *pbVar15;
        pbVar16 = pbVar15 + 1;
        if ((char)bVar1 < '\x01') {
          if (-1 < (char)bVar1) {
            return (int)(short)CONCAT31((int3)(uVar8 >> 8),bVar1);
          }
          uVar9 = (uint)(short)(ushort)(byte)-bVar1;
          goto LAB_000b5d2a;
        }
        uVar8 = 0;
        iVar11 = (int)(short)(ushort)bVar1;
        pbVar15 = pbVar15 + 2;
        uVar12 = uStack_18 - iVar11;
        bVar21 = iVar11 <= (int)uStack_18;
        uStack_18 = uVar12;
      } while (uVar12 != 0 && bVar21);
LAB_000b5d5b:
      bVar1 = pbVar15[-1];
      uVar8 = (uint)bVar1;
      pbVar16 = pbVar15;
      if (bVar1 != 0xff) {
        uVar8 = (uint)*(byte *)((int)&unk_d42e4 + (int)(short)(ushort)bVar1);
        uVar12 = uVar12 + iVar11;
        goto LAB_000b5c8b;
      }
      do {
        uVar9 = uVar12 + uVar6;
        if (uVar9 != 0 && SCARRY4(uVar12,uVar6) == (int)uVar9 < 0) {
          pbVar14 = (byte *)(((*piStack_24 + iVar4 + dword_d30d0) - uVar6) + uVar9);
          uVar13 = uVar9;
          pbVar15 = pbVar16;
LAB_000b5c38:
          do {
            bVar1 = *pbVar15;
            sVar3 = (short)CONCAT31((int3)(uVar8 >> 8),bVar1);
            if ((char)bVar1 < '\x01') {
              if (-1 < (char)bVar1) goto LAB_000b5c45;
              iVar5 = (int)(short)(ushort)(byte)-bVar1;
              pbVar16 = pbVar15 + 1;
              while (uVar9 = uVar13 - iVar5, pbVar20 = pbVar14, uVar9 == 0 || (int)uVar13 < iVar5) {
                iVar5 = iVar5 + uVar9;
                uVar9 = -uVar9;
                do {
                  bVar1 = *pbVar16;
                  pbVar16 = pbVar16 + 1;
                  uVar8 = (uint)*(byte *)((int)&unk_d42e4 + (int)(short)(ushort)bVar1);
                  *pbVar14 = *(byte *)((int)&unk_d42e4 + (int)(short)(ushort)bVar1);
                  iVar5 = iVar5 + -1;
                  pbVar14 = pbVar14 + -1;
                } while (iVar5 != 0);
                uStack_14 = uStack_14 - 1;
                bVar21 = uStack_14 == 0;
                if (bVar21) goto LAB_000b5ca4;
                piStack_24 = piStack_24 + 1;
                pbVar14 = (byte *)(*piStack_24 + iVar4 + dword_d30d0);
                uStack_18 = uVar7;
LAB_000b5d2a:
                uVar8 = 0;
                pbVar15 = pbVar16 + uStack_18;
                iVar5 = uVar9 - uStack_18;
                uVar13 = uVar6;
                if (iVar5 == 0) goto LAB_000b5c38;
                pbVar16 = pbVar15;
                if ((int)uVar9 < (int)uStack_18) {
                  pbVar15 = pbVar15 + iVar5;
                  goto LAB_000b5d3e;
                }
              }
              do {
                bVar1 = *pbVar16;
                pbVar16 = pbVar16 + 1;
                uVar8 = 0;
                pbVar14 = pbVar20 + -1;
                *pbVar20 = *(byte *)((int)&unk_d42e4 + (int)(short)(ushort)bVar1);
                iVar5 = iVar5 + -1;
                uVar13 = uVar9;
                pbVar15 = pbVar16;
                pbVar20 = pbVar14;
              } while (iVar5 != 0);
              goto LAB_000b5c38;
            }
            iVar5 = (int)(short)(ushort)bVar1;
            bVar1 = pbVar15[1];
            uVar8 = (uint)bVar1;
            pbVar16 = pbVar15 + 2;
            pbVar15 = pbVar16;
            if (bVar1 != 0xff) {
              uVar8 = (uint)*(byte *)((int)&unk_d42e4 + (int)(short)(ushort)bVar1);
              while( true ) {
                sVar3 = (short)uVar8;
                uVar9 = uVar13 - iVar5;
                if (uVar9 != 0 && iVar5 <= (int)uVar13) break;
                iVar11 = -uVar9;
                for (iVar5 = iVar5 + uVar9; iVar5 != 0; iVar5 = iVar5 + -1) {
                  *pbVar14 = (byte)uVar8;
                  pbVar14 = pbVar14 + -1;
                }
                uStack_14 = uStack_14 - 1;
                if (uStack_14 == 0) goto LAB_000b5c45;
                piStack_24 = piStack_24 + 1;
                pbVar14 = (byte *)(*piStack_24 + iVar4 + dword_d30d0);
                uVar12 = uVar7;
LAB_000b5c8b:
                iVar5 = iVar11 - uVar12;
                uVar13 = uVar6;
                if (iVar5 == 0) goto LAB_000b5c38;
                if (iVar11 < (int)uVar12) goto LAB_000b5d3e;
              }
              for (; uVar13 = uVar9, iVar5 != 0; iVar5 = iVar5 + -1) {
                *pbVar14 = (byte)uVar8;
                pbVar14 = pbVar14 + -1;
              }
              goto LAB_000b5c38;
            }
            pbVar14 = pbVar14 + -iVar5;
            uVar9 = uVar13 - iVar5;
            bVar21 = iVar5 <= (int)uVar13;
            uVar13 = uVar9;
          } while (uVar9 != 0 && bVar21);
        }
        uStack_14 = uStack_14 - 1;
        bVar21 = uStack_14 == 0;
LAB_000b5ca4:
        sVar3 = (short)uVar8;
        if (bVar21) {
LAB_000b5c45:
          return (int)sVar3;
        }
        piStack_24 = piStack_24 + 1;
        uVar12 = uVar9 + uVar7;
      } while (uVar12 == 0 || SCARRY4(uVar9,uVar7) != (int)uVar12 < 0);
      pbVar14 = (byte *)(*piStack_24 + iVar4 + dword_d30d0);
      uStack_18 = uVar12;
      pbVar15 = pbVar16;
    } while( true );
  }
  piStack_24 = (int *)(off_d30cc + iVar5 * 4);
  puVar17 = (undefined *)(*piStack_24 + iVar4 + dword_d30d0);
  uVar8 = uVar6;
LAB_000b59dc:
  do {
    while( true ) {
      bVar1 = *pbVar15;
      pbVar14 = pbVar15 + 1;
      if ((char)bVar1 < '\x01') break;
      iVar5 = (int)(short)(ushort)bVar1;
      pbVar15 = pbVar15 + 2;
      if (*pbVar14 == 0xff) {
        puVar17 = puVar17 + -iVar5;
        uVar7 = uVar8 - iVar5;
        bVar21 = (int)uVar8 < iVar5;
        uVar8 = uVar7;
        if (uVar7 == 0 || bVar21) {
          do {
            piStack_24 = piStack_24 + 1;
            bVar21 = SCARRY4(uVar7,uVar6);
            uVar7 = uVar7 + uVar6;
          } while (uVar7 == 0 || bVar21 != (int)uVar7 < 0);
          puVar17 = (undefined *)(((*piStack_24 + iVar4 + dword_d30d0) - uVar6) + uVar7);
          uVar8 = uVar7;
        }
      }
      else {
        uVar2 = *(undefined *)((int)&unk_d42e4 + (int)(short)(ushort)*pbVar14);
        uVar7 = uVar8;
        while (uVar8 = uVar7 - iVar5, uVar8 == 0 || (int)uVar7 < iVar5) {
          for (iVar5 = iVar5 + uVar8; iVar5 != 0; iVar5 = iVar5 + -1) {
            *puVar17 = uVar2;
            puVar17 = puVar17 + -1;
          }
          piStack_24 = piStack_24 + 1;
          puVar17 = (undefined *)(*piStack_24 + iVar4 + dword_d30d0);
          iVar5 = -uVar8;
          uVar7 = uVar6;
        }
        for (; iVar5 != 0; iVar5 = iVar5 + -1) {
          *puVar17 = uVar2;
          puVar17 = puVar17 + -1;
        }
      }
    }
    if (-1 < (char)bVar1) {
      return (int)(short)(ushort)bVar1;
    }
    iVar5 = (int)(short)(ushort)(byte)-bVar1;
    do {
      uVar7 = uVar8 - iVar5;
      puVar18 = puVar17;
      if (uVar7 != 0 && iVar5 <= (int)uVar8) goto LAB_000b5a57;
      iVar19 = iVar5 + uVar7;
      iVar5 = -uVar7;
      do {
        bVar1 = *pbVar14;
        pbVar14 = pbVar14 + 1;
        *puVar17 = *(undefined *)((int)&unk_d42e4 + (int)(short)(ushort)bVar1);
        iVar19 = iVar19 + -1;
        puVar17 = puVar17 + -1;
      } while (iVar19 != 0);
      piStack_24 = piStack_24 + 1;
      puVar17 = (undefined *)(*piStack_24 + iVar4 + dword_d30d0);
      uVar8 = uVar6;
      pbVar15 = pbVar14;
    } while (iVar5 != 0 && (int)uVar7 < 1);
  } while( true );
LAB_000b5d3e:
  uVar8 = 0;
  uStack_18 = -iVar5;
  goto LAB_000b5d42;
LAB_000b5a57:
  do {
    bVar1 = *pbVar14;
    pbVar14 = pbVar14 + 1;
    puVar17 = puVar18 + -1;
    *puVar18 = *(undefined *)((int)&unk_d42e4 + (int)(short)(ushort)bVar1);
    iVar5 = iVar5 + -1;
    uVar8 = uVar7;
    pbVar15 = pbVar14;
    puVar18 = puVar17;
  } while (iVar5 != 0);
  goto LAB_000b59dc;
}


// ================================================================================================
// sub_b5ac8 @ 0xb5ac8 [__watcall]
// ================================================================================================

uint __watcall sub_b5ac8(void)

{
  byte bVar1;
  undefined uVar2;
  short sVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  uint uVar11;
  uint uVar12;
  int iVar13;
  byte *pbVar14;
  byte *pbVar15;
  byte *pbVar16;
  undefined *puVar17;
  undefined *puVar18;
  int iVar19;
  byte *pbVar20;
  bool bVar21;
  int in_stack_00000004;
  int in_stack_00000008;
  int in_stack_0000000c;
  int *piStack_24;
  uint uStack_18;
  uint uStack_14;
  
  pbVar15 = (byte *)(in_stack_00000004 + 0x10);
  uVar4 = (uint)*(short *)(in_stack_00000004 + 4);
  iVar19 = 0;
  uStack_18 = 0;
  uVar7 = (uint)*(short *)(in_stack_00000004 + 6);
  if (in_stack_0000000c < dword_d30b0) {
    iVar19 = 1;
    uVar5 = (in_stack_0000000c + uVar7) - dword_d30b0;
    if (uVar5 == 0 || (int)(in_stack_0000000c + uVar7) < dword_d30b0) {
      return uVar5;
    }
    uStack_18 = (uVar7 - uVar5) * uVar4;
    uVar7 = (dword_d30b0 + uVar5) - dword_d30b8;
    uStack_14 = uVar5;
    in_stack_0000000c = dword_d30b0;
    if ((uVar7 != 0 && dword_d30b8 <= (int)(dword_d30b0 + uVar5)) &&
       (uStack_14 = uVar5 - uVar7, uStack_14 == 0 || (int)uVar5 < (int)uVar7)) {
      return uVar7;
    }
  }
  else {
    uVar5 = (in_stack_0000000c + uVar7) - dword_d30b8;
    uStack_14 = uVar7;
    if (uVar5 != 0 && dword_d30b8 <= (int)(in_stack_0000000c + uVar7)) {
      iVar19 = 1;
      uStack_14 = uVar7 - uVar5;
      if (uVar7 - uVar5 == 0 || (int)uVar7 < (int)uVar5) {
        return uVar5;
      }
    }
  }
  if (in_stack_00000008 < dword_d30bc) {
    iVar19 = iVar19 + 1;
    uVar7 = (in_stack_00000008 + uVar4) - dword_d30bc;
    if (uVar7 == 0 || (int)(in_stack_00000008 + uVar4) < dword_d30bc) {
      return uVar7;
    }
    if (dword_d30c0 - dword_d30bc <= (int)uVar7) {
      uVar7 = dword_d30c0 - dword_d30bc;
    }
    uVar5 = uVar4 - uVar7;
    uVar4 = uVar7;
    in_stack_00000008 = dword_d30bc;
  }
  else {
    uVar7 = (in_stack_00000008 + uVar4) - dword_d30c0;
    uVar5 = 0;
    if (uVar7 != 0 && dword_d30c0 <= (int)(in_stack_00000008 + uVar4)) {
      uStack_18 = uStack_18 + uVar7;
      if (uVar4 - uVar7 == 0 || (int)uVar4 < (int)uVar7) {
        return uVar7;
      }
      iVar19 = iVar19 + 1;
      uVar4 = uVar4 - uVar7;
      uVar5 = uVar7;
    }
  }
  iVar13 = in_stack_00000008 + uVar4 + -1;
  if (iVar19 != 0) {
    piStack_24 = (int *)(off_d30cc + in_stack_0000000c * 4);
    pbVar14 = (byte *)(*piStack_24 + iVar13 + dword_d30d0);
    uVar12 = uVar4;
    if (uStack_18 == 0) goto LAB_000b5c38;
    if ((int)uStack_18 < 0) {
      iVar6 = (uStack_18 & 0x7fff) + 1;
      iVar19 = 0x7fff;
      do {
        while( true ) {
          bVar1 = *pbVar15;
          if ((char)bVar1 < '\x01') break;
          uVar7 = 0;
          iVar10 = (int)(short)(ushort)bVar1;
          pbVar15 = pbVar15 + 2;
          iVar9 = iVar19 - iVar10;
          bVar21 = iVar19 < iVar10;
          iVar19 = iVar9;
          if (iVar9 == 0 || bVar21) {
            uVar11 = iVar9 + iVar6;
            goto LAB_000b5d5b;
          }
        }
        if (-1 < (char)bVar1) {
          return (int)(short)CONCAT31((int3)(uVar7 >> 8),bVar1);
        }
        uVar7 = 0;
        uVar8 = (uint)(short)(ushort)(byte)-bVar1;
        pbVar15 = pbVar15 + uVar8 + 1;
        iVar10 = iVar19 - uVar8;
        bVar21 = (int)uVar8 <= iVar19;
        iVar19 = iVar10;
      } while (iVar10 != 0 && bVar21);
      pbVar16 = pbVar15 + -uVar8;
      uStack_18 = iVar10 + uVar8 + iVar6;
      goto LAB_000b5d2a;
    }
LAB_000b5d42:
    do {
      do {
        bVar1 = *pbVar15;
        pbVar16 = pbVar15 + 1;
        if ((char)bVar1 < '\x01') {
          if (-1 < (char)bVar1) {
            return (int)(short)CONCAT31((int3)(uVar7 >> 8),bVar1);
          }
          uVar8 = (uint)(short)(ushort)(byte)-bVar1;
          goto LAB_000b5d2a;
        }
        uVar7 = 0;
        iVar10 = (int)(short)(ushort)bVar1;
        pbVar15 = pbVar15 + 2;
        uVar11 = uStack_18 - iVar10;
        bVar21 = iVar10 <= (int)uStack_18;
        uStack_18 = uVar11;
      } while (uVar11 != 0 && bVar21);
LAB_000b5d5b:
      bVar1 = pbVar15[-1];
      uVar7 = (uint)bVar1;
      pbVar16 = pbVar15;
      if (bVar1 != 0xff) {
        uVar7 = (uint)*(byte *)((int)&unk_d42e4 + (int)(short)(ushort)bVar1);
        uVar11 = uVar11 + iVar10;
        goto LAB_000b5c8b;
      }
      do {
        uVar8 = uVar11 + uVar4;
        if (uVar8 != 0 && SCARRY4(uVar11,uVar4) == (int)uVar8 < 0) {
          pbVar14 = (byte *)(((*piStack_24 + iVar13 + dword_d30d0) - uVar4) + uVar8);
          uVar12 = uVar8;
          pbVar15 = pbVar16;
LAB_000b5c38:
          do {
            bVar1 = *pbVar15;
            sVar3 = (short)CONCAT31((int3)(uVar7 >> 8),bVar1);
            if ((char)bVar1 < '\x01') {
              if (-1 < (char)bVar1) goto LAB_000b5c45;
              iVar19 = (int)(short)(ushort)(byte)-bVar1;
              pbVar16 = pbVar15 + 1;
              while (uVar8 = uVar12 - iVar19, pbVar20 = pbVar14, uVar8 == 0 || (int)uVar12 < iVar19)
              {
                iVar19 = iVar19 + uVar8;
                uVar8 = -uVar8;
                do {
                  bVar1 = *pbVar16;
                  pbVar16 = pbVar16 + 1;
                  uVar7 = (uint)*(byte *)((int)&unk_d42e4 + (int)(short)(ushort)bVar1);
                  *pbVar14 = *(byte *)((int)&unk_d42e4 + (int)(short)(ushort)bVar1);
                  iVar19 = iVar19 + -1;
                  pbVar14 = pbVar14 + -1;
                } while (iVar19 != 0);
                uStack_14 = uStack_14 - 1;
                bVar21 = uStack_14 == 0;
                if (bVar21) goto LAB_000b5ca4;
                piStack_24 = piStack_24 + 1;
                pbVar14 = (byte *)(*piStack_24 + iVar13 + dword_d30d0);
                uStack_18 = uVar5;
LAB_000b5d2a:
                uVar7 = 0;
                pbVar15 = pbVar16 + uStack_18;
                iVar19 = uVar8 - uStack_18;
                uVar12 = uVar4;
                if (iVar19 == 0) goto LAB_000b5c38;
                pbVar16 = pbVar15;
                if ((int)uVar8 < (int)uStack_18) {
                  pbVar15 = pbVar15 + iVar19;
                  goto LAB_000b5d3e;
                }
              }
              do {
                bVar1 = *pbVar16;
                pbVar16 = pbVar16 + 1;
                uVar7 = 0;
                pbVar14 = pbVar20 + -1;
                *pbVar20 = *(byte *)((int)&unk_d42e4 + (int)(short)(ushort)bVar1);
                iVar19 = iVar19 + -1;
                uVar12 = uVar8;
                pbVar15 = pbVar16;
                pbVar20 = pbVar14;
              } while (iVar19 != 0);
              goto LAB_000b5c38;
            }
            iVar19 = (int)(short)(ushort)bVar1;
            bVar1 = pbVar15[1];
            uVar7 = (uint)bVar1;
            pbVar16 = pbVar15 + 2;
            pbVar15 = pbVar16;
            if (bVar1 != 0xff) {
              uVar7 = (uint)*(byte *)((int)&unk_d42e4 + (int)(short)(ushort)bVar1);
              while( true ) {
                sVar3 = (short)uVar7;
                uVar8 = uVar12 - iVar19;
                if (uVar8 != 0 && iVar19 <= (int)uVar12) break;
                iVar10 = -uVar8;
                for (iVar19 = iVar19 + uVar8; iVar19 != 0; iVar19 = iVar19 + -1) {
                  *pbVar14 = (byte)uVar7;
                  pbVar14 = pbVar14 + -1;
                }
                uStack_14 = uStack_14 - 1;
                if (uStack_14 == 0) goto LAB_000b5c45;
                piStack_24 = piStack_24 + 1;
                pbVar14 = (byte *)(*piStack_24 + iVar13 + dword_d30d0);
                uVar11 = uVar5;
LAB_000b5c8b:
                iVar19 = iVar10 - uVar11;
                uVar12 = uVar4;
                if (iVar19 == 0) goto LAB_000b5c38;
                if (iVar10 < (int)uVar11) goto LAB_000b5d3e;
              }
              for (; uVar12 = uVar8, iVar19 != 0; iVar19 = iVar19 + -1) {
                *pbVar14 = (byte)uVar7;
                pbVar14 = pbVar14 + -1;
              }
              goto LAB_000b5c38;
            }
            pbVar14 = pbVar14 + -iVar19;
            uVar8 = uVar12 - iVar19;
            bVar21 = iVar19 <= (int)uVar12;
            uVar12 = uVar8;
          } while (uVar8 != 0 && bVar21);
        }
        uStack_14 = uStack_14 - 1;
        bVar21 = uStack_14 == 0;
LAB_000b5ca4:
        sVar3 = (short)uVar7;
        if (bVar21) {
LAB_000b5c45:
          return (int)sVar3;
        }
        piStack_24 = piStack_24 + 1;
        uVar11 = uVar8 + uVar5;
      } while (uVar11 == 0 || SCARRY4(uVar8,uVar5) != (int)uVar11 < 0);
      pbVar14 = (byte *)(*piStack_24 + iVar13 + dword_d30d0);
      uStack_18 = uVar11;
      pbVar15 = pbVar16;
    } while( true );
  }
  piStack_24 = (int *)(off_d30cc + in_stack_0000000c * 4);
  puVar17 = (undefined *)(*piStack_24 + iVar13 + dword_d30d0);
  uVar7 = uVar4;
LAB_000b59dc:
  do {
    while( true ) {
      bVar1 = *pbVar15;
      pbVar14 = pbVar15 + 1;
      if ((char)bVar1 < '\x01') break;
      iVar19 = (int)(short)(ushort)bVar1;
      pbVar15 = pbVar15 + 2;
      if (*pbVar14 == 0xff) {
        puVar17 = puVar17 + -iVar19;
        uVar5 = uVar7 - iVar19;
        bVar21 = (int)uVar7 < iVar19;
        uVar7 = uVar5;
        if (uVar5 == 0 || bVar21) {
          do {
            piStack_24 = piStack_24 + 1;
            bVar21 = SCARRY4(uVar5,uVar4);
            uVar5 = uVar5 + uVar4;
          } while (uVar5 == 0 || bVar21 != (int)uVar5 < 0);
          puVar17 = (undefined *)(((*piStack_24 + iVar13 + dword_d30d0) - uVar4) + uVar5);
          uVar7 = uVar5;
        }
      }
      else {
        uVar2 = *(undefined *)((int)&unk_d42e4 + (int)(short)(ushort)*pbVar14);
        uVar5 = uVar7;
        while (uVar7 = uVar5 - iVar19, uVar7 == 0 || (int)uVar5 < iVar19) {
          for (iVar19 = iVar19 + uVar7; iVar19 != 0; iVar19 = iVar19 + -1) {
            *puVar17 = uVar2;
            puVar17 = puVar17 + -1;
          }
          piStack_24 = piStack_24 + 1;
          puVar17 = (undefined *)(*piStack_24 + iVar13 + dword_d30d0);
          iVar19 = -uVar7;
          uVar5 = uVar4;
        }
        for (; iVar19 != 0; iVar19 = iVar19 + -1) {
          *puVar17 = uVar2;
          puVar17 = puVar17 + -1;
        }
      }
    }
    if (-1 < (char)bVar1) {
      return (int)(short)(ushort)bVar1;
    }
    iVar19 = (int)(short)(ushort)(byte)-bVar1;
    do {
      uVar5 = uVar7 - iVar19;
      puVar18 = puVar17;
      if (uVar5 != 0 && iVar19 <= (int)uVar7) goto LAB_000b5a57;
      iVar6 = iVar19 + uVar5;
      iVar19 = -uVar5;
      do {
        bVar1 = *pbVar14;
        pbVar14 = pbVar14 + 1;
        *puVar17 = *(undefined *)((int)&unk_d42e4 + (int)(short)(ushort)bVar1);
        iVar6 = iVar6 + -1;
        puVar17 = puVar17 + -1;
      } while (iVar6 != 0);
      piStack_24 = piStack_24 + 1;
      puVar17 = (undefined *)(*piStack_24 + iVar13 + dword_d30d0);
      uVar7 = uVar4;
      pbVar15 = pbVar14;
    } while (iVar19 != 0 && (int)uVar5 < 1);
  } while( true );
LAB_000b5d3e:
  uVar7 = 0;
  uStack_18 = -iVar19;
  goto LAB_000b5d42;
LAB_000b5a57:
  do {
    bVar1 = *pbVar14;
    pbVar14 = pbVar14 + 1;
    puVar17 = puVar18 + -1;
    *puVar18 = *(undefined *)((int)&unk_d42e4 + (int)(short)(ushort)bVar1);
    iVar19 = iVar19 + -1;
    uVar7 = uVar5;
    pbVar15 = pbVar14;
    puVar18 = puVar17;
  } while (iVar19 != 0);
  goto LAB_000b59dc;
}


// ================================================================================================
// sub_b5ae2 @ 0xb5ae2 [__watcall]
// ================================================================================================

uint __watcall sub_b5ae2(void)

{
  byte bVar1;
  undefined uVar2;
  short sVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  int iVar10;
  int iVar11;
  uint uVar12;
  uint uVar13;
  byte *pbVar14;
  byte *pbVar15;
  byte *pbVar16;
  undefined *puVar17;
  undefined *puVar18;
  int iVar19;
  byte *pbVar20;
  bool bVar21;
  int in_stack_00000004;
  int *local_24;
  uint local_18;
  uint local_14;
  
  iVar4 = (int)*(short *)(in_stack_00000004 + 0xc);
  iVar5 = (int)*(short *)(in_stack_00000004 + 0xe);
  pbVar15 = (byte *)(in_stack_00000004 + 0x10);
  uVar6 = (uint)*(short *)(in_stack_00000004 + 4);
  iVar19 = 0;
  local_18 = 0;
  uVar8 = (uint)*(short *)(in_stack_00000004 + 6);
  if (iVar5 < dword_d30b0) {
    iVar19 = 1;
    uVar7 = (iVar5 + uVar8) - dword_d30b0;
    if (uVar7 == 0 || (int)(iVar5 + uVar8) < dword_d30b0) {
      return uVar7;
    }
    local_18 = (uVar8 - uVar7) * uVar6;
    uVar8 = (dword_d30b0 + uVar7) - dword_d30b8;
    local_14 = uVar7;
    iVar5 = dword_d30b0;
    if ((uVar8 != 0 && dword_d30b8 <= (int)(dword_d30b0 + uVar7)) &&
       (local_14 = uVar7 - uVar8, local_14 == 0 || (int)uVar7 < (int)uVar8)) {
      return uVar8;
    }
  }
  else {
    uVar7 = (iVar5 + uVar8) - dword_d30b8;
    local_14 = uVar8;
    if (uVar7 != 0 && dword_d30b8 <= (int)(iVar5 + uVar8)) {
      iVar19 = 1;
      local_14 = uVar8 - uVar7;
      if (uVar8 - uVar7 == 0 || (int)uVar8 < (int)uVar7) {
        return uVar7;
      }
    }
  }
  if (iVar4 < dword_d30bc) {
    iVar19 = iVar19 + 1;
    uVar8 = (iVar4 + uVar6) - dword_d30bc;
    if (uVar8 == 0 || (int)(iVar4 + uVar6) < dword_d30bc) {
      return uVar8;
    }
    if (dword_d30c0 - dword_d30bc <= (int)uVar8) {
      uVar8 = dword_d30c0 - dword_d30bc;
    }
    uVar7 = uVar6 - uVar8;
    uVar6 = uVar8;
    iVar4 = dword_d30bc;
  }
  else {
    uVar8 = (iVar4 + uVar6) - dword_d30c0;
    uVar7 = 0;
    if (uVar8 != 0 && dword_d30c0 <= (int)(iVar4 + uVar6)) {
      local_18 = local_18 + uVar8;
      if (uVar6 - uVar8 == 0 || (int)uVar6 < (int)uVar8) {
        return uVar8;
      }
      iVar19 = iVar19 + 1;
      uVar6 = uVar6 - uVar8;
      uVar7 = uVar8;
    }
  }
  iVar4 = iVar4 + uVar6 + -1;
  if (iVar19 != 0) {
    local_24 = (int *)(off_d30cc + iVar5 * 4);
    pbVar14 = (byte *)(*local_24 + iVar4 + dword_d30d0);
    uVar13 = uVar6;
    if (local_18 == 0) goto LAB_000b5c38;
    if ((int)local_18 < 0) {
      iVar19 = (local_18 & 0x7fff) + 1;
      iVar5 = 0x7fff;
      do {
        while( true ) {
          bVar1 = *pbVar15;
          if ((char)bVar1 < '\x01') break;
          uVar8 = 0;
          iVar11 = (int)(short)(ushort)bVar1;
          pbVar15 = pbVar15 + 2;
          iVar10 = iVar5 - iVar11;
          bVar21 = iVar5 < iVar11;
          iVar5 = iVar10;
          if (iVar10 == 0 || bVar21) {
            uVar12 = iVar10 + iVar19;
            goto LAB_000b5d5b;
          }
        }
        if (-1 < (char)bVar1) {
          return (int)(short)CONCAT31((int3)(uVar8 >> 8),bVar1);
        }
        uVar8 = 0;
        uVar9 = (uint)(short)(ushort)(byte)-bVar1;
        pbVar15 = pbVar15 + uVar9 + 1;
        iVar11 = iVar5 - uVar9;
        bVar21 = (int)uVar9 <= iVar5;
        iVar5 = iVar11;
      } while (iVar11 != 0 && bVar21);
      pbVar16 = pbVar15 + -uVar9;
      local_18 = iVar11 + uVar9 + iVar19;
      goto LAB_000b5d2a;
    }
LAB_000b5d42:
    do {
      do {
        bVar1 = *pbVar15;
        pbVar16 = pbVar15 + 1;
        if ((char)bVar1 < '\x01') {
          if (-1 < (char)bVar1) {
            return (int)(short)CONCAT31((int3)(uVar8 >> 8),bVar1);
          }
          uVar9 = (uint)(short)(ushort)(byte)-bVar1;
          goto LAB_000b5d2a;
        }
        uVar8 = 0;
        iVar11 = (int)(short)(ushort)bVar1;
        pbVar15 = pbVar15 + 2;
        uVar12 = local_18 - iVar11;
        bVar21 = iVar11 <= (int)local_18;
        local_18 = uVar12;
      } while (uVar12 != 0 && bVar21);
LAB_000b5d5b:
      bVar1 = pbVar15[-1];
      uVar8 = (uint)bVar1;
      pbVar16 = pbVar15;
      if (bVar1 != 0xff) {
        uVar8 = (uint)*(byte *)((int)&unk_d42e4 + (int)(short)(ushort)bVar1);
        uVar12 = uVar12 + iVar11;
        goto LAB_000b5c8b;
      }
      do {
        uVar9 = uVar12 + uVar6;
        if (uVar9 != 0 && SCARRY4(uVar12,uVar6) == (int)uVar9 < 0) {
          pbVar14 = (byte *)(((*local_24 + iVar4 + dword_d30d0) - uVar6) + uVar9);
          uVar13 = uVar9;
          pbVar15 = pbVar16;
LAB_000b5c38:
          do {
            bVar1 = *pbVar15;
            sVar3 = (short)CONCAT31((int3)(uVar8 >> 8),bVar1);
            if ((char)bVar1 < '\x01') {
              if (-1 < (char)bVar1) goto LAB_000b5c45;
              iVar5 = (int)(short)(ushort)(byte)-bVar1;
              pbVar16 = pbVar15 + 1;
              while (uVar9 = uVar13 - iVar5, pbVar20 = pbVar14, uVar9 == 0 || (int)uVar13 < iVar5) {
                iVar5 = iVar5 + uVar9;
                uVar9 = -uVar9;
                do {
                  bVar1 = *pbVar16;
                  pbVar16 = pbVar16 + 1;
                  uVar8 = (uint)*(byte *)((int)&unk_d42e4 + (int)(short)(ushort)bVar1);
                  *pbVar14 = *(byte *)((int)&unk_d42e4 + (int)(short)(ushort)bVar1);
                  iVar5 = iVar5 + -1;
                  pbVar14 = pbVar14 + -1;
                } while (iVar5 != 0);
                local_14 = local_14 - 1;
                bVar21 = local_14 == 0;
                if (bVar21) goto LAB_000b5ca4;
                local_24 = local_24 + 1;
                pbVar14 = (byte *)(*local_24 + iVar4 + dword_d30d0);
                local_18 = uVar7;
LAB_000b5d2a:
                uVar8 = 0;
                pbVar15 = pbVar16 + local_18;
                iVar5 = uVar9 - local_18;
                uVar13 = uVar6;
                if (iVar5 == 0) goto LAB_000b5c38;
                pbVar16 = pbVar15;
                if ((int)uVar9 < (int)local_18) {
                  pbVar15 = pbVar15 + iVar5;
                  goto LAB_000b5d3e;
                }
              }
              do {
                bVar1 = *pbVar16;
                pbVar16 = pbVar16 + 1;
                uVar8 = 0;
                pbVar14 = pbVar20 + -1;
                *pbVar20 = *(byte *)((int)&unk_d42e4 + (int)(short)(ushort)bVar1);
                iVar5 = iVar5 + -1;
                uVar13 = uVar9;
                pbVar15 = pbVar16;
                pbVar20 = pbVar14;
              } while (iVar5 != 0);
              goto LAB_000b5c38;
            }
            iVar5 = (int)(short)(ushort)bVar1;
            bVar1 = pbVar15[1];
            uVar8 = (uint)bVar1;
            pbVar16 = pbVar15 + 2;
            pbVar15 = pbVar16;
            if (bVar1 != 0xff) {
              uVar8 = (uint)*(byte *)((int)&unk_d42e4 + (int)(short)(ushort)bVar1);
              while( true ) {
                sVar3 = (short)uVar8;
                uVar9 = uVar13 - iVar5;
                if (uVar9 != 0 && iVar5 <= (int)uVar13) break;
                iVar11 = -uVar9;
                for (iVar5 = iVar5 + uVar9; iVar5 != 0; iVar5 = iVar5 + -1) {
                  *pbVar14 = (byte)uVar8;
                  pbVar14 = pbVar14 + -1;
                }
                local_14 = local_14 - 1;
                if (local_14 == 0) goto LAB_000b5c45;
                local_24 = local_24 + 1;
                pbVar14 = (byte *)(*local_24 + iVar4 + dword_d30d0);
                uVar12 = uVar7;
LAB_000b5c8b:
                iVar5 = iVar11 - uVar12;
                uVar13 = uVar6;
                if (iVar5 == 0) goto LAB_000b5c38;
                if (iVar11 < (int)uVar12) goto LAB_000b5d3e;
              }
              for (; uVar13 = uVar9, iVar5 != 0; iVar5 = iVar5 + -1) {
                *pbVar14 = (byte)uVar8;
                pbVar14 = pbVar14 + -1;
              }
              goto LAB_000b5c38;
            }
            pbVar14 = pbVar14 + -iVar5;
            uVar9 = uVar13 - iVar5;
            bVar21 = iVar5 <= (int)uVar13;
            uVar13 = uVar9;
          } while (uVar9 != 0 && bVar21);
        }
        local_14 = local_14 - 1;
        bVar21 = local_14 == 0;
LAB_000b5ca4:
        sVar3 = (short)uVar8;
        if (bVar21) {
LAB_000b5c45:
          return (int)sVar3;
        }
        local_24 = local_24 + 1;
        uVar12 = uVar9 + uVar7;
      } while (uVar12 == 0 || SCARRY4(uVar9,uVar7) != (int)uVar12 < 0);
      pbVar14 = (byte *)(*local_24 + iVar4 + dword_d30d0);
      local_18 = uVar12;
      pbVar15 = pbVar16;
    } while( true );
  }
  local_24 = (int *)(off_d30cc + iVar5 * 4);
  puVar17 = (undefined *)(*local_24 + iVar4 + dword_d30d0);
  uVar8 = uVar6;
LAB_000b59dc:
  do {
    while( true ) {
      bVar1 = *pbVar15;
      pbVar14 = pbVar15 + 1;
      if ((char)bVar1 < '\x01') break;
      iVar5 = (int)(short)(ushort)bVar1;
      pbVar15 = pbVar15 + 2;
      if (*pbVar14 == 0xff) {
        puVar17 = puVar17 + -iVar5;
        uVar7 = uVar8 - iVar5;
        bVar21 = (int)uVar8 < iVar5;
        uVar8 = uVar7;
        if (uVar7 == 0 || bVar21) {
          do {
            local_24 = local_24 + 1;
            bVar21 = SCARRY4(uVar7,uVar6);
            uVar7 = uVar7 + uVar6;
          } while (uVar7 == 0 || bVar21 != (int)uVar7 < 0);
          puVar17 = (undefined *)(((*local_24 + iVar4 + dword_d30d0) - uVar6) + uVar7);
          uVar8 = uVar7;
        }
      }
      else {
        uVar2 = *(undefined *)((int)&unk_d42e4 + (int)(short)(ushort)*pbVar14);
        uVar7 = uVar8;
        while (uVar8 = uVar7 - iVar5, uVar8 == 0 || (int)uVar7 < iVar5) {
          for (iVar5 = iVar5 + uVar8; iVar5 != 0; iVar5 = iVar5 + -1) {
            *puVar17 = uVar2;
            puVar17 = puVar17 + -1;
          }
          local_24 = local_24 + 1;
          puVar17 = (undefined *)(*local_24 + iVar4 + dword_d30d0);
          iVar5 = -uVar8;
          uVar7 = uVar6;
        }
        for (; iVar5 != 0; iVar5 = iVar5 + -1) {
          *puVar17 = uVar2;
          puVar17 = puVar17 + -1;
        }
      }
    }
    if (-1 < (char)bVar1) {
      return (int)(short)(ushort)bVar1;
    }
    iVar5 = (int)(short)(ushort)(byte)-bVar1;
    do {
      uVar7 = uVar8 - iVar5;
      puVar18 = puVar17;
      if (uVar7 != 0 && iVar5 <= (int)uVar8) goto LAB_000b5a57;
      iVar19 = iVar5 + uVar7;
      iVar5 = -uVar7;
      do {
        bVar1 = *pbVar14;
        pbVar14 = pbVar14 + 1;
        *puVar17 = *(undefined *)((int)&unk_d42e4 + (int)(short)(ushort)bVar1);
        iVar19 = iVar19 + -1;
        puVar17 = puVar17 + -1;
      } while (iVar19 != 0);
      local_24 = local_24 + 1;
      puVar17 = (undefined *)(*local_24 + iVar4 + dword_d30d0);
      uVar8 = uVar6;
      pbVar15 = pbVar14;
    } while (iVar5 != 0 && (int)uVar7 < 1);
  } while( true );
LAB_000b5d3e:
  uVar8 = 0;
  local_18 = -iVar5;
  goto LAB_000b5d42;
LAB_000b5a57:
  do {
    bVar1 = *pbVar14;
    pbVar14 = pbVar14 + 1;
    puVar17 = puVar18 + -1;
    *puVar18 = *(undefined *)((int)&unk_d42e4 + (int)(short)(ushort)bVar1);
    iVar5 = iVar5 + -1;
    uVar8 = uVar7;
    pbVar15 = pbVar14;
    puVar18 = puVar17;
  } while (iVar5 != 0);
  goto LAB_000b59dc;
}


// ================================================================================================
// sub_b5d80 @ 0xb5d80 [__cdecl]
// ================================================================================================

void sub_b5d80(int param_1,int param_2,undefined param_3)

{
  undefined *extraout_EDX;
  
  if ((((param_1 < dword_d30bc) || (dword_d30c0 <= param_1)) || (param_2 < dword_d30b0)) ||
     (dword_d30b8 <= param_2)) {
    return;
  }
  if (dword_d30c8 == 0) {
    *(undefined *)(param_1 + *(int *)(off_d30cc + param_2 * 4) + dword_d30d0) = param_3;
    return;
  }
  if ((char)((uint)(param_1 + (&unk_d3104)[param_2]) >> 0x10) == byte_d4f54) {
    *(undefined *)((param_1 + (&unk_d3104)[param_2] & 0xffffU) + dword_d30d0) = param_3;
    return;
  }
  sub_b5e04();
  *extraout_EDX = param_3;
  return;
}


// ================================================================================================
// putpixel @ 0xb5db0 [__cdecl]
// ================================================================================================

void putpixel(int param_1,int param_2,undefined param_3)

{
  undefined *extraout_EDX;
  
  if (dword_d30c8 == 0) {
    *(undefined *)(param_1 + *(int *)(off_d30cc + param_2 * 4) + dword_d30d0) = param_3;
    return;
  }
  if ((char)((uint)(param_1 + (&unk_d3104)[param_2]) >> 0x10) == byte_d4f54) {
    *(undefined *)((param_1 + (&unk_d3104)[param_2] & 0xffffU) + dword_d30d0) = param_3;
    return;
  }
  sub_b5e04();
  *extraout_EDX = param_3;
  return;
}


// ================================================================================================
// sub_b5e00 @ 0xb5e00 [__cdecl]
// ================================================================================================

void sub_b5e00(char param_1)

{
  if (param_1 != byte_d4f54) {
                    /* WARNING: Could not recover jumptable at 0x000b5e18. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    byte_d4f54 = param_1;
    (**(code **)(&DAT_000b5e1f + dword_d4f4c * 4))();
    return;
  }
  return;
}


// ================================================================================================
// sub_b5e04 @ 0xb5e04 [__watcall]
// ================================================================================================

void __watcall sub_b5e04(char param_1)

{
  if (param_1 != byte_d4f54) {
                    /* WARNING: Could not recover jumptable at 0x000b5e18. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    byte_d4f54 = param_1;
    (**(code **)(&DAT_000b5e1f + dword_d4f4c * 4))();
    return;
  }
  return;
}


// ================================================================================================
// sub_b5ea7 @ 0xb5ea7 [__watcall]
// ================================================================================================

void __watcall sub_b5ea7(void)

{
  code *pcVar1;
  
  pcVar1 = (code *)swi(0x10);
  (*pcVar1)();
  return;
}


// ================================================================================================
// sub_b5eb8 @ 0xb5eb8 [__cdecl]
// ================================================================================================

void sub_b5eb8(void)

{
  code *pcVar1;
  
  pcVar1 = (code *)swi(0x10);
  (*pcVar1)();
  return;
}


// ================================================================================================
// sub_b5ec5 @ 0xb5ec5 [__watcall]
// ================================================================================================

void __watcall sub_b5ec5(void)

{
  code *pcVar1;
  
  pcVar1 = (code *)swi(0x10);
  (*pcVar1)();
  return;
}


// ================================================================================================
// sub_b5ed6 @ 0xb5ed6 [__watcall]
// ================================================================================================

void __watcall sub_b5ed6(void)

{
  code *pcVar1;
  
  pcVar1 = (code *)swi(0x10);
  (*pcVar1)();
  return;
}


// ================================================================================================
// sub_b5ee8 @ 0xb5ee8 [__watcall]
// ================================================================================================

void __watcall sub_b5ee8(void)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  undefined4 *puVar10;
  int in_stack_00000004;
  short in_stack_00000008;
  short in_stack_0000000c;
  undefined4 *puStack_1c;
  
  iVar2 = (int)(short)(in_stack_00000008 - *(short *)(in_stack_00000004 + 8));
  iVar3 = (int)(short)(in_stack_0000000c - *(short *)(in_stack_00000004 + 10));
  iVar5 = (int)*(short *)(in_stack_00000004 + 6);
  puStack_1c = (undefined4 *)(in_stack_00000004 + 0x10);
  if (iVar3 < dword_d30b0) {
    iVar4 = (iVar3 + iVar5) - dword_d30b0;
    if (iVar4 == 0 || iVar3 + iVar5 < dword_d30b0) {
      return;
    }
    puStack_1c = (undefined4 *)
                 ((int)puStack_1c + (iVar5 - iVar4) * (int)*(short *)(in_stack_00000004 + 4));
    iVar5 = (dword_d30b0 + iVar4) - dword_d30b8;
    iVar6 = iVar4;
    iVar3 = dword_d30b0;
    if ((iVar5 != 0 && dword_d30b8 <= dword_d30b0 + iVar4) &&
       (iVar6 = iVar4 - iVar5, iVar6 == 0 || iVar4 < iVar5)) {
      return;
    }
  }
  else {
    iVar4 = (iVar3 + iVar5) - dword_d30b8;
    iVar6 = iVar5;
    if ((iVar4 != 0 && dword_d30b8 <= iVar3 + iVar5) &&
       (iVar6 = iVar5 - iVar4, iVar5 - iVar4 == 0 || iVar5 < iVar4)) {
      return;
    }
  }
  uVar7 = (uint)*(short *)(in_stack_00000004 + 4);
  if (iVar2 < dword_d30bc) {
    uVar8 = (iVar2 + uVar7) - dword_d30bc;
    if (uVar8 != 0 && dword_d30bc <= (int)(iVar2 + uVar7)) {
      puStack_1c = (undefined4 *)((int)puStack_1c + (uVar7 - uVar8));
      uVar9 = dword_d30c0 - dword_d30bc;
      if (uVar9 != 0 && dword_d30bc <= dword_d30c0) {
        if ((int)uVar9 <= (int)uVar8) {
          uVar8 = uVar9;
        }
        iVar5 = uVar7 - uVar8;
        iVar2 = dword_d30bc;
        goto LAB_000b5feb;
      }
    }
  }
  else {
    iVar4 = (iVar2 + uVar7) - dword_d30c0;
    uVar8 = uVar7;
    iVar5 = 0;
    if (((int)(iVar2 + uVar7) < dword_d30c0) ||
       (uVar8 = uVar7 - iVar4, iVar5 = iVar4, uVar8 != 0 && iVar4 <= (int)uVar7)) {
LAB_000b5feb:
      if (0 < (int)uVar8) {
        puVar10 = (undefined4 *)(*(int *)(off_d30cc + iVar3 * 4) + iVar2 + dword_d30d0);
        iVar2 = dword_d30c4 - uVar8;
        uVar7 = uVar8 >> 1;
        if ((uVar8 & 1) != 0) {
          if (uVar7 != 0) {
            do {
              for (uVar9 = uVar8 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
                *puVar10 = *puStack_1c;
                puStack_1c = puStack_1c + 1;
                puVar10 = puVar10 + 1;
              }
              for (uVar9 = (uint)((uVar7 & 1) != 0); uVar9 != 0; uVar9 = uVar9 - 1) {
                *(undefined2 *)puVar10 = *(undefined2 *)puStack_1c;
                puStack_1c = (undefined4 *)((int)puStack_1c + 2);
                puVar10 = (undefined4 *)((int)puVar10 + 2);
              }
              *(undefined *)puVar10 = *(undefined *)puStack_1c;
              puStack_1c = (undefined4 *)((int)puStack_1c + iVar5 + 1);
              puVar10 = (undefined4 *)((int)puVar10 + iVar2 + 1);
              iVar3 = iVar6 + -1;
              bVar1 = 0 < iVar6;
              iVar6 = iVar3;
            } while (iVar3 != 0 && bVar1);
            return;
          }
          do {
            *(undefined *)puVar10 = *(undefined *)puStack_1c;
            puStack_1c = (undefined4 *)((int)puStack_1c + iVar5 + 1);
            puVar10 = (undefined4 *)((int)puVar10 + iVar2 + 1);
            iVar3 = iVar6 + -1;
            bVar1 = 0 < iVar6;
            iVar6 = iVar3;
          } while (iVar3 != 0 && bVar1);
          return;
        }
        do {
          for (uVar9 = uVar8 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
            *puVar10 = *puStack_1c;
            puStack_1c = puStack_1c + 1;
            puVar10 = puVar10 + 1;
          }
          for (uVar9 = (uint)((uVar7 & 1) != 0); uVar9 != 0; uVar9 = uVar9 - 1) {
            *(undefined2 *)puVar10 = *(undefined2 *)puStack_1c;
            puStack_1c = (undefined4 *)((int)puStack_1c + 2);
            puVar10 = (undefined4 *)((int)puVar10 + 2);
          }
          puStack_1c = (undefined4 *)((int)puStack_1c + iVar5);
          puVar10 = (undefined4 *)((int)puVar10 + iVar2);
          iVar3 = iVar6 + -1;
          bVar1 = 0 < iVar6;
          iVar6 = iVar3;
        } while (iVar3 != 0 && bVar1);
      }
      return;
    }
  }
  return;
}


// ================================================================================================
// sub_b5f0f @ 0xb5f0f [__cdecl]
// ================================================================================================

void sub_b5f0f(int param_1,int param_2,int param_3)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  undefined4 *puVar9;
  undefined4 *puStack_1c;
  
  iVar3 = (int)*(short *)(param_1 + 6);
  puStack_1c = (undefined4 *)(param_1 + 0x10);
  if (param_3 < dword_d30b0) {
    iVar2 = (param_3 + iVar3) - dword_d30b0;
    if (iVar2 == 0 || param_3 + iVar3 < dword_d30b0) {
      return;
    }
    puStack_1c = (undefined4 *)((int)puStack_1c + (iVar3 - iVar2) * (int)*(short *)(param_1 + 4));
    iVar3 = (dword_d30b0 + iVar2) - dword_d30b8;
    iVar4 = iVar2;
    param_3 = dword_d30b0;
    if ((iVar3 != 0 && dword_d30b8 <= dword_d30b0 + iVar2) &&
       (iVar4 = iVar2 - iVar3, iVar4 == 0 || iVar2 < iVar3)) {
      return;
    }
  }
  else {
    iVar2 = (param_3 + iVar3) - dword_d30b8;
    iVar4 = iVar3;
    if ((iVar2 != 0 && dword_d30b8 <= param_3 + iVar3) &&
       (iVar4 = iVar3 - iVar2, iVar3 - iVar2 == 0 || iVar3 < iVar2)) {
      return;
    }
  }
  uVar5 = (uint)*(short *)(param_1 + 4);
  if (param_2 < dword_d30bc) {
    uVar6 = (param_2 + uVar5) - dword_d30bc;
    if (uVar6 != 0 && dword_d30bc <= (int)(param_2 + uVar5)) {
      puStack_1c = (undefined4 *)((int)puStack_1c + (uVar5 - uVar6));
      uVar7 = dword_d30c0 - dword_d30bc;
      if (uVar7 != 0 && dword_d30bc <= dword_d30c0) {
        if ((int)uVar7 <= (int)uVar6) {
          uVar6 = uVar7;
        }
        iVar3 = uVar5 - uVar6;
        param_2 = dword_d30bc;
        goto LAB_000b5feb;
      }
    }
  }
  else {
    iVar2 = (param_2 + uVar5) - dword_d30c0;
    uVar6 = uVar5;
    iVar3 = 0;
    if (((int)(param_2 + uVar5) < dword_d30c0) ||
       (uVar6 = uVar5 - iVar2, iVar3 = iVar2, uVar6 != 0 && iVar2 <= (int)uVar5)) {
LAB_000b5feb:
      if (0 < (int)uVar6) {
        puVar9 = (undefined4 *)(*(int *)(off_d30cc + param_3 * 4) + param_2 + dword_d30d0);
        iVar2 = dword_d30c4 - uVar6;
        uVar5 = uVar6 >> 1;
        if ((uVar6 & 1) != 0) {
          if (uVar5 != 0) {
            do {
              for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
                *puVar9 = *puStack_1c;
                puStack_1c = puStack_1c + 1;
                puVar9 = puVar9 + 1;
              }
              for (uVar7 = (uint)((uVar5 & 1) != 0); uVar7 != 0; uVar7 = uVar7 - 1) {
                *(undefined2 *)puVar9 = *(undefined2 *)puStack_1c;
                puStack_1c = (undefined4 *)((int)puStack_1c + 2);
                puVar9 = (undefined4 *)((int)puVar9 + 2);
              }
              *(undefined *)puVar9 = *(undefined *)puStack_1c;
              puStack_1c = (undefined4 *)((int)puStack_1c + iVar3 + 1);
              puVar9 = (undefined4 *)((int)puVar9 + iVar2 + 1);
              iVar8 = iVar4 + -1;
              bVar1 = 0 < iVar4;
              iVar4 = iVar8;
            } while (iVar8 != 0 && bVar1);
            return;
          }
          do {
            *(undefined *)puVar9 = *(undefined *)puStack_1c;
            puStack_1c = (undefined4 *)((int)puStack_1c + iVar3 + 1);
            puVar9 = (undefined4 *)((int)puVar9 + iVar2 + 1);
            iVar8 = iVar4 + -1;
            bVar1 = 0 < iVar4;
            iVar4 = iVar8;
          } while (iVar8 != 0 && bVar1);
          return;
        }
        do {
          for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
            *puVar9 = *puStack_1c;
            puStack_1c = puStack_1c + 1;
            puVar9 = puVar9 + 1;
          }
          for (uVar7 = (uint)((uVar5 & 1) != 0); uVar7 != 0; uVar7 = uVar7 - 1) {
            *(undefined2 *)puVar9 = *(undefined2 *)puStack_1c;
            puStack_1c = (undefined4 *)((int)puStack_1c + 2);
            puVar9 = (undefined4 *)((int)puVar9 + 2);
          }
          puStack_1c = (undefined4 *)((int)puStack_1c + iVar3);
          puVar9 = (undefined4 *)((int)puVar9 + iVar2);
          iVar8 = iVar4 + -1;
          bVar1 = 0 < iVar4;
          iVar4 = iVar8;
        } while (iVar8 != 0 && bVar1);
      }
      return;
    }
  }
  return;
}


// ================================================================================================
// sub_b5f28 @ 0xb5f28 [__watcall]
// ================================================================================================

void __watcall sub_b5f28(void)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  undefined4 *puVar10;
  int in_stack_00000004;
  undefined4 *local_1c;
  
  iVar2 = (int)*(short *)(in_stack_00000004 + 0xc);
  iVar3 = (int)*(short *)(in_stack_00000004 + 0xe);
  iVar5 = (int)*(short *)(in_stack_00000004 + 6);
  local_1c = (undefined4 *)(in_stack_00000004 + 0x10);
  if (iVar3 < dword_d30b0) {
    iVar4 = (iVar3 + iVar5) - dword_d30b0;
    if (iVar4 == 0 || iVar3 + iVar5 < dword_d30b0) {
      return;
    }
    local_1c = (undefined4 *)
               ((int)local_1c + (iVar5 - iVar4) * (int)*(short *)(in_stack_00000004 + 4));
    iVar5 = (dword_d30b0 + iVar4) - dword_d30b8;
    iVar6 = iVar4;
    iVar3 = dword_d30b0;
    if ((iVar5 != 0 && dword_d30b8 <= dword_d30b0 + iVar4) &&
       (iVar6 = iVar4 - iVar5, iVar6 == 0 || iVar4 < iVar5)) {
      return;
    }
  }
  else {
    iVar4 = (iVar3 + iVar5) - dword_d30b8;
    iVar6 = iVar5;
    if ((iVar4 != 0 && dword_d30b8 <= iVar3 + iVar5) &&
       (iVar6 = iVar5 - iVar4, iVar5 - iVar4 == 0 || iVar5 < iVar4)) {
      return;
    }
  }
  uVar7 = (uint)*(short *)(in_stack_00000004 + 4);
  if (iVar2 < dword_d30bc) {
    uVar8 = (iVar2 + uVar7) - dword_d30bc;
    if (uVar8 != 0 && dword_d30bc <= (int)(iVar2 + uVar7)) {
      local_1c = (undefined4 *)((int)local_1c + (uVar7 - uVar8));
      uVar9 = dword_d30c0 - dword_d30bc;
      if (uVar9 != 0 && dword_d30bc <= dword_d30c0) {
        if ((int)uVar9 <= (int)uVar8) {
          uVar8 = uVar9;
        }
        iVar5 = uVar7 - uVar8;
        iVar2 = dword_d30bc;
        goto LAB_000b5feb;
      }
    }
  }
  else {
    iVar4 = (iVar2 + uVar7) - dword_d30c0;
    uVar8 = uVar7;
    iVar5 = 0;
    if (((int)(iVar2 + uVar7) < dword_d30c0) ||
       (uVar8 = uVar7 - iVar4, iVar5 = iVar4, uVar8 != 0 && iVar4 <= (int)uVar7)) {
LAB_000b5feb:
      if (0 < (int)uVar8) {
        puVar10 = (undefined4 *)(*(int *)(off_d30cc + iVar3 * 4) + iVar2 + dword_d30d0);
        iVar2 = dword_d30c4 - uVar8;
        uVar7 = uVar8 >> 1;
        if ((uVar8 & 1) != 0) {
          if (uVar7 != 0) {
            do {
              for (uVar9 = uVar8 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
                *puVar10 = *local_1c;
                local_1c = local_1c + 1;
                puVar10 = puVar10 + 1;
              }
              for (uVar9 = (uint)((uVar7 & 1) != 0); uVar9 != 0; uVar9 = uVar9 - 1) {
                *(undefined2 *)puVar10 = *(undefined2 *)local_1c;
                local_1c = (undefined4 *)((int)local_1c + 2);
                puVar10 = (undefined4 *)((int)puVar10 + 2);
              }
              *(undefined *)puVar10 = *(undefined *)local_1c;
              local_1c = (undefined4 *)((int)local_1c + iVar5 + 1);
              puVar10 = (undefined4 *)((int)puVar10 + iVar2 + 1);
              iVar3 = iVar6 + -1;
              bVar1 = 0 < iVar6;
              iVar6 = iVar3;
            } while (iVar3 != 0 && bVar1);
            return;
          }
          do {
            *(undefined *)puVar10 = *(undefined *)local_1c;
            local_1c = (undefined4 *)((int)local_1c + iVar5 + 1);
            puVar10 = (undefined4 *)((int)puVar10 + iVar2 + 1);
            iVar3 = iVar6 + -1;
            bVar1 = 0 < iVar6;
            iVar6 = iVar3;
          } while (iVar3 != 0 && bVar1);
          return;
        }
        do {
          for (uVar9 = uVar8 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
            *puVar10 = *local_1c;
            local_1c = local_1c + 1;
            puVar10 = puVar10 + 1;
          }
          for (uVar9 = (uint)((uVar7 & 1) != 0); uVar9 != 0; uVar9 = uVar9 - 1) {
            *(undefined2 *)puVar10 = *(undefined2 *)local_1c;
            local_1c = (undefined4 *)((int)local_1c + 2);
            puVar10 = (undefined4 *)((int)puVar10 + 2);
          }
          local_1c = (undefined4 *)((int)local_1c + iVar5);
          puVar10 = (undefined4 *)((int)puVar10 + iVar2);
          iVar3 = iVar6 + -1;
          bVar1 = 0 < iVar6;
          iVar6 = iVar3;
        } while (iVar3 != 0 && bVar1);
      }
      return;
    }
  }
  return;
}


// ================================================================================================
// sub_b6064 @ 0xb6064 [__watcall]
// ================================================================================================

void __watcall sub_b6064(void)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  ushort *puVar10;
  ushort *puVar11;
  int in_stack_00000004;
  short in_stack_00000008;
  short in_stack_0000000c;
  ushort *puStack_1c;
  
  iVar2 = (int)(short)(in_stack_00000008 - *(short *)(in_stack_00000004 + 8));
  iVar3 = (int)(short)(in_stack_0000000c - *(short *)(in_stack_00000004 + 10));
  iVar6 = (int)*(short *)(in_stack_00000004 + 6);
  puStack_1c = (ushort *)(in_stack_00000004 + 0x10);
  if (iVar3 < dword_d30b0) {
    iVar4 = (iVar3 + iVar6) - dword_d30b0;
    if (iVar4 == 0 || iVar3 + iVar6 < dword_d30b0) {
      return;
    }
    puStack_1c = (ushort *)
                 ((int)puStack_1c + (iVar6 - iVar4) * (int)*(short *)(in_stack_00000004 + 4));
    iVar6 = (dword_d30b0 + iVar4) - dword_d30b8;
    iVar7 = iVar4;
    iVar3 = dword_d30b0;
    if ((iVar6 != 0 && dword_d30b8 <= dword_d30b0 + iVar4) &&
       (iVar7 = iVar4 - iVar6, iVar7 == 0 || iVar4 < iVar6)) {
      return;
    }
  }
  else {
    iVar4 = (iVar3 + iVar6) - dword_d30b8;
    iVar7 = iVar6;
    if ((iVar4 != 0 && dword_d30b8 <= iVar3 + iVar6) &&
       (iVar7 = iVar6 - iVar4, iVar6 - iVar4 == 0 || iVar6 < iVar4)) {
      return;
    }
  }
  uVar8 = (uint)*(short *)(in_stack_00000004 + 4);
  if (iVar2 < dword_d30bc) {
    uVar9 = (iVar2 + uVar8) - dword_d30bc;
    if (uVar9 != 0 && dword_d30bc <= (int)(iVar2 + uVar8)) {
      puStack_1c = (ushort *)((int)puStack_1c + (uVar8 - uVar9));
      uVar5 = dword_d30c0 - dword_d30bc;
      if (uVar5 != 0 && dword_d30bc <= dword_d30c0) {
        if ((int)uVar5 <= (int)uVar9) {
          uVar9 = uVar5;
        }
        iVar6 = uVar8 - uVar9;
        iVar2 = dword_d30bc;
        goto LAB_000b6167;
      }
    }
  }
  else {
    iVar4 = (iVar2 + uVar8) - dword_d30c0;
    uVar9 = uVar8;
    iVar6 = 0;
    if (((int)(iVar2 + uVar8) < dword_d30c0) ||
       (uVar9 = uVar8 - iVar4, iVar6 = iVar4, uVar9 != 0 && iVar4 <= (int)uVar8)) {
LAB_000b6167:
      if (0 < (int)uVar9) {
        puVar11 = (ushort *)(*(int *)(off_d30cc + iVar3 * 4) + iVar2 + dword_d30d0);
        iVar2 = dword_d30c4 - uVar9;
        uVar5 = uVar9 >> 1;
        uVar8 = uVar5;
        if ((uVar9 & 1) != 0) {
          if (uVar5 != 0) {
            do {
              do {
                puVar10 = puStack_1c;
                *puVar11 = *puVar11 ^ *puVar10;
                puVar11 = puVar11 + 1;
                uVar8 = uVar8 - 1;
                puStack_1c = puVar10 + 1;
              } while (uVar8 != 0);
              *(byte *)puVar11 = *(byte *)puVar11 ^ *(byte *)(puVar10 + 1);
              puVar11 = (ushort *)((int)puVar11 + iVar2 + 1);
              iVar3 = iVar7 + -1;
              bVar1 = 0 < iVar7;
              uVar8 = uVar5;
              puStack_1c = (ushort *)((int)puVar10 + iVar6 + 3);
              iVar7 = iVar3;
            } while (iVar3 != 0 && bVar1);
            return;
          }
          do {
            *(byte *)puVar11 = *(byte *)puVar11 ^ *(byte *)puStack_1c;
            puStack_1c = (ushort *)((int)puStack_1c + iVar6 + 1);
            puVar11 = (ushort *)((int)puVar11 + iVar2 + 1);
            iVar3 = iVar7 + -1;
            bVar1 = 0 < iVar7;
            iVar7 = iVar3;
          } while (iVar3 != 0 && bVar1);
          return;
        }
        do {
          do {
            puVar10 = puStack_1c + 1;
            *puVar11 = *puVar11 ^ *puStack_1c;
            puVar11 = puVar11 + 1;
            uVar8 = uVar8 - 1;
            puStack_1c = puVar10;
          } while (uVar8 != 0);
          puStack_1c = (ushort *)((int)puVar10 + iVar6);
          puVar11 = (ushort *)((int)puVar11 + iVar2);
          iVar3 = iVar7 + -1;
          bVar1 = 0 < iVar7;
          uVar8 = uVar5;
          iVar7 = iVar3;
        } while (iVar3 != 0 && bVar1);
      }
      return;
    }
  }
  return;
}


// ================================================================================================
// sub_b608b @ 0xb608b [__cdecl]
// ================================================================================================

void sub_b608b(int param_1,int param_2,int param_3)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  ushort *puVar9;
  ushort *puVar10;
  ushort *puStack_1c;
  
  iVar4 = (int)*(short *)(param_1 + 6);
  puStack_1c = (ushort *)(param_1 + 0x10);
  if (param_3 < dword_d30b0) {
    iVar2 = (param_3 + iVar4) - dword_d30b0;
    if (iVar2 == 0 || param_3 + iVar4 < dword_d30b0) {
      return;
    }
    puStack_1c = (ushort *)((int)puStack_1c + (iVar4 - iVar2) * (int)*(short *)(param_1 + 4));
    iVar4 = (dword_d30b0 + iVar2) - dword_d30b8;
    iVar5 = iVar2;
    param_3 = dword_d30b0;
    if ((iVar4 != 0 && dword_d30b8 <= dword_d30b0 + iVar2) &&
       (iVar5 = iVar2 - iVar4, iVar5 == 0 || iVar2 < iVar4)) {
      return;
    }
  }
  else {
    iVar2 = (param_3 + iVar4) - dword_d30b8;
    iVar5 = iVar4;
    if ((iVar2 != 0 && dword_d30b8 <= param_3 + iVar4) &&
       (iVar5 = iVar4 - iVar2, iVar4 - iVar2 == 0 || iVar4 < iVar2)) {
      return;
    }
  }
  uVar6 = (uint)*(short *)(param_1 + 4);
  if (param_2 < dword_d30bc) {
    uVar7 = (param_2 + uVar6) - dword_d30bc;
    if (uVar7 != 0 && dword_d30bc <= (int)(param_2 + uVar6)) {
      puStack_1c = (ushort *)((int)puStack_1c + (uVar6 - uVar7));
      uVar3 = dword_d30c0 - dword_d30bc;
      if (uVar3 != 0 && dword_d30bc <= dword_d30c0) {
        if ((int)uVar3 <= (int)uVar7) {
          uVar7 = uVar3;
        }
        iVar4 = uVar6 - uVar7;
        param_2 = dword_d30bc;
        goto LAB_000b6167;
      }
    }
  }
  else {
    iVar2 = (param_2 + uVar6) - dword_d30c0;
    uVar7 = uVar6;
    iVar4 = 0;
    if (((int)(param_2 + uVar6) < dword_d30c0) ||
       (uVar7 = uVar6 - iVar2, iVar4 = iVar2, uVar7 != 0 && iVar2 <= (int)uVar6)) {
LAB_000b6167:
      if (0 < (int)uVar7) {
        puVar10 = (ushort *)(*(int *)(off_d30cc + param_3 * 4) + param_2 + dword_d30d0);
        iVar2 = dword_d30c4 - uVar7;
        uVar3 = uVar7 >> 1;
        uVar6 = uVar3;
        if ((uVar7 & 1) != 0) {
          if (uVar3 != 0) {
            do {
              do {
                puVar9 = puStack_1c;
                *puVar10 = *puVar10 ^ *puVar9;
                puVar10 = puVar10 + 1;
                uVar6 = uVar6 - 1;
                puStack_1c = puVar9 + 1;
              } while (uVar6 != 0);
              *(byte *)puVar10 = *(byte *)puVar10 ^ *(byte *)(puVar9 + 1);
              puVar10 = (ushort *)((int)puVar10 + iVar2 + 1);
              iVar8 = iVar5 + -1;
              bVar1 = 0 < iVar5;
              uVar6 = uVar3;
              puStack_1c = (ushort *)((int)puVar9 + iVar4 + 3);
              iVar5 = iVar8;
            } while (iVar8 != 0 && bVar1);
            return;
          }
          do {
            *(byte *)puVar10 = *(byte *)puVar10 ^ *(byte *)puStack_1c;
            puStack_1c = (ushort *)((int)puStack_1c + iVar4 + 1);
            puVar10 = (ushort *)((int)puVar10 + iVar2 + 1);
            iVar8 = iVar5 + -1;
            bVar1 = 0 < iVar5;
            iVar5 = iVar8;
          } while (iVar8 != 0 && bVar1);
          return;
        }
        do {
          do {
            puVar9 = puStack_1c + 1;
            *puVar10 = *puVar10 ^ *puStack_1c;
            puVar10 = puVar10 + 1;
            uVar6 = uVar6 - 1;
            puStack_1c = puVar9;
          } while (uVar6 != 0);
          puStack_1c = (ushort *)((int)puVar9 + iVar4);
          puVar10 = (ushort *)((int)puVar10 + iVar2);
          iVar8 = iVar5 + -1;
          bVar1 = 0 < iVar5;
          uVar6 = uVar3;
          iVar5 = iVar8;
        } while (iVar8 != 0 && bVar1);
      }
      return;
    }
  }
  return;
}


// ================================================================================================
// sub_b60a4 @ 0xb60a4 [__watcall]
// ================================================================================================

void __watcall sub_b60a4(void)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  ushort *puVar10;
  ushort *puVar11;
  int in_stack_00000004;
  ushort *local_1c;
  
  iVar2 = (int)*(short *)(in_stack_00000004 + 0xc);
  iVar3 = (int)*(short *)(in_stack_00000004 + 0xe);
  iVar6 = (int)*(short *)(in_stack_00000004 + 6);
  local_1c = (ushort *)(in_stack_00000004 + 0x10);
  if (iVar3 < dword_d30b0) {
    iVar4 = (iVar3 + iVar6) - dword_d30b0;
    if (iVar4 == 0 || iVar3 + iVar6 < dword_d30b0) {
      return;
    }
    local_1c = (ushort *)((int)local_1c + (iVar6 - iVar4) * (int)*(short *)(in_stack_00000004 + 4));
    iVar6 = (dword_d30b0 + iVar4) - dword_d30b8;
    iVar7 = iVar4;
    iVar3 = dword_d30b0;
    if ((iVar6 != 0 && dword_d30b8 <= dword_d30b0 + iVar4) &&
       (iVar7 = iVar4 - iVar6, iVar7 == 0 || iVar4 < iVar6)) {
      return;
    }
  }
  else {
    iVar4 = (iVar3 + iVar6) - dword_d30b8;
    iVar7 = iVar6;
    if ((iVar4 != 0 && dword_d30b8 <= iVar3 + iVar6) &&
       (iVar7 = iVar6 - iVar4, iVar6 - iVar4 == 0 || iVar6 < iVar4)) {
      return;
    }
  }
  uVar8 = (uint)*(short *)(in_stack_00000004 + 4);
  if (iVar2 < dword_d30bc) {
    uVar9 = (iVar2 + uVar8) - dword_d30bc;
    if (uVar9 != 0 && dword_d30bc <= (int)(iVar2 + uVar8)) {
      local_1c = (ushort *)((int)local_1c + (uVar8 - uVar9));
      uVar5 = dword_d30c0 - dword_d30bc;
      if (uVar5 != 0 && dword_d30bc <= dword_d30c0) {
        if ((int)uVar5 <= (int)uVar9) {
          uVar9 = uVar5;
        }
        iVar6 = uVar8 - uVar9;
        iVar2 = dword_d30bc;
        goto LAB_000b6167;
      }
    }
  }
  else {
    iVar4 = (iVar2 + uVar8) - dword_d30c0;
    uVar9 = uVar8;
    iVar6 = 0;
    if (((int)(iVar2 + uVar8) < dword_d30c0) ||
       (uVar9 = uVar8 - iVar4, iVar6 = iVar4, uVar9 != 0 && iVar4 <= (int)uVar8)) {
LAB_000b6167:
      if (0 < (int)uVar9) {
        puVar11 = (ushort *)(*(int *)(off_d30cc + iVar3 * 4) + iVar2 + dword_d30d0);
        iVar2 = dword_d30c4 - uVar9;
        uVar5 = uVar9 >> 1;
        uVar8 = uVar5;
        if ((uVar9 & 1) != 0) {
          if (uVar5 != 0) {
            do {
              do {
                puVar10 = local_1c;
                *puVar11 = *puVar11 ^ *puVar10;
                puVar11 = puVar11 + 1;
                uVar8 = uVar8 - 1;
                local_1c = puVar10 + 1;
              } while (uVar8 != 0);
              *(byte *)puVar11 = *(byte *)puVar11 ^ *(byte *)(puVar10 + 1);
              puVar11 = (ushort *)((int)puVar11 + iVar2 + 1);
              iVar3 = iVar7 + -1;
              bVar1 = 0 < iVar7;
              uVar8 = uVar5;
              local_1c = (ushort *)((int)puVar10 + iVar6 + 3);
              iVar7 = iVar3;
            } while (iVar3 != 0 && bVar1);
            return;
          }
          do {
            *(byte *)puVar11 = *(byte *)puVar11 ^ *(byte *)local_1c;
            local_1c = (ushort *)((int)local_1c + iVar6 + 1);
            puVar11 = (ushort *)((int)puVar11 + iVar2 + 1);
            iVar3 = iVar7 + -1;
            bVar1 = 0 < iVar7;
            iVar7 = iVar3;
          } while (iVar3 != 0 && bVar1);
          return;
        }
        do {
          do {
            puVar10 = local_1c + 1;
            *puVar11 = *puVar11 ^ *local_1c;
            puVar11 = puVar11 + 1;
            uVar8 = uVar8 - 1;
            local_1c = puVar10;
          } while (uVar8 != 0);
          local_1c = (ushort *)((int)puVar10 + iVar6);
          puVar11 = (ushort *)((int)puVar11 + iVar2);
          iVar3 = iVar7 + -1;
          bVar1 = 0 < iVar7;
          uVar8 = uVar5;
          iVar7 = iVar3;
        } while (iVar3 != 0 && bVar1);
      }
      return;
    }
  }
  return;
}


// ================================================================================================
// sub_b61f0 @ 0xb61f0 [__watcall]
// ================================================================================================

void __watcall sub_b61f0(void)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  ushort *puVar10;
  ushort *puVar11;
  int in_stack_00000004;
  short in_stack_00000008;
  short in_stack_0000000c;
  ushort *puStack_1c;
  
  iVar2 = (int)(short)(in_stack_00000008 - *(short *)(in_stack_00000004 + 8));
  iVar3 = (int)(short)(in_stack_0000000c - *(short *)(in_stack_00000004 + 10));
  iVar6 = (int)*(short *)(in_stack_00000004 + 6);
  puStack_1c = (ushort *)(in_stack_00000004 + 0x10);
  if (iVar3 < dword_d30b0) {
    iVar4 = (iVar3 + iVar6) - dword_d30b0;
    if (iVar4 == 0 || iVar3 + iVar6 < dword_d30b0) {
      return;
    }
    puStack_1c = (ushort *)
                 ((int)puStack_1c + (iVar6 - iVar4) * (int)*(short *)(in_stack_00000004 + 4));
    iVar6 = (dword_d30b0 + iVar4) - dword_d30b8;
    iVar7 = iVar4;
    iVar3 = dword_d30b0;
    if ((iVar6 != 0 && dword_d30b8 <= dword_d30b0 + iVar4) &&
       (iVar7 = iVar4 - iVar6, iVar7 == 0 || iVar4 < iVar6)) {
      return;
    }
  }
  else {
    iVar4 = (iVar3 + iVar6) - dword_d30b8;
    iVar7 = iVar6;
    if ((iVar4 != 0 && dword_d30b8 <= iVar3 + iVar6) &&
       (iVar7 = iVar6 - iVar4, iVar6 - iVar4 == 0 || iVar6 < iVar4)) {
      return;
    }
  }
  uVar8 = (uint)*(short *)(in_stack_00000004 + 4);
  if (iVar2 < dword_d30bc) {
    uVar9 = (iVar2 + uVar8) - dword_d30bc;
    if (uVar9 != 0 && dword_d30bc <= (int)(iVar2 + uVar8)) {
      puStack_1c = (ushort *)((int)puStack_1c + (uVar8 - uVar9));
      uVar5 = dword_d30c0 - dword_d30bc;
      if (uVar5 != 0 && dword_d30bc <= dword_d30c0) {
        if ((int)uVar5 <= (int)uVar9) {
          uVar9 = uVar5;
        }
        iVar6 = uVar8 - uVar9;
        iVar2 = dword_d30bc;
        goto LAB_000b62f3;
      }
    }
  }
  else {
    iVar4 = (iVar2 + uVar8) - dword_d30c0;
    uVar9 = uVar8;
    iVar6 = 0;
    if (((int)(iVar2 + uVar8) < dword_d30c0) ||
       (uVar9 = uVar8 - iVar4, iVar6 = iVar4, uVar9 != 0 && iVar4 <= (int)uVar8)) {
LAB_000b62f3:
      if (0 < (int)uVar9) {
        puVar11 = (ushort *)(*(int *)(off_d30cc + iVar3 * 4) + iVar2 + dword_d30d0);
        iVar2 = dword_d30c4 - uVar9;
        uVar5 = uVar9 >> 1;
        uVar8 = uVar5;
        if ((uVar9 & 1) != 0) {
          if (uVar5 != 0) {
            do {
              do {
                puVar10 = puStack_1c;
                *puVar11 = *puVar11 & *puVar10;
                puVar11 = puVar11 + 1;
                uVar8 = uVar8 - 1;
                puStack_1c = puVar10 + 1;
              } while (uVar8 != 0);
              *(byte *)puVar11 = *(byte *)puVar11 & *(byte *)(puVar10 + 1);
              puVar11 = (ushort *)((int)puVar11 + iVar2 + 1);
              iVar3 = iVar7 + -1;
              bVar1 = 0 < iVar7;
              uVar8 = uVar5;
              puStack_1c = (ushort *)((int)puVar10 + iVar6 + 3);
              iVar7 = iVar3;
            } while (iVar3 != 0 && bVar1);
            return;
          }
          do {
            *(byte *)puVar11 = *(byte *)puVar11 & *(byte *)puStack_1c;
            puStack_1c = (ushort *)((int)puStack_1c + iVar6 + 1);
            puVar11 = (ushort *)((int)puVar11 + iVar2 + 1);
            iVar3 = iVar7 + -1;
            bVar1 = 0 < iVar7;
            iVar7 = iVar3;
          } while (iVar3 != 0 && bVar1);
          return;
        }
        do {
          do {
            puVar10 = puStack_1c + 1;
            *puVar11 = *puVar11 & *puStack_1c;
            puVar11 = puVar11 + 1;
            uVar8 = uVar8 - 1;
            puStack_1c = puVar10;
          } while (uVar8 != 0);
          puStack_1c = (ushort *)((int)puVar10 + iVar6);
          puVar11 = (ushort *)((int)puVar11 + iVar2);
          iVar3 = iVar7 + -1;
          bVar1 = 0 < iVar7;
          uVar8 = uVar5;
          iVar7 = iVar3;
        } while (iVar3 != 0 && bVar1);
      }
      return;
    }
  }
  return;
}


// ================================================================================================
// sub_b6217 @ 0xb6217 [__cdecl]
// ================================================================================================

void sub_b6217(int param_1,int param_2,int param_3)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  ushort *puVar9;
  ushort *puVar10;
  ushort *puStack_1c;
  
  iVar4 = (int)*(short *)(param_1 + 6);
  puStack_1c = (ushort *)(param_1 + 0x10);
  if (param_3 < dword_d30b0) {
    iVar2 = (param_3 + iVar4) - dword_d30b0;
    if (iVar2 == 0 || param_3 + iVar4 < dword_d30b0) {
      return;
    }
    puStack_1c = (ushort *)((int)puStack_1c + (iVar4 - iVar2) * (int)*(short *)(param_1 + 4));
    iVar4 = (dword_d30b0 + iVar2) - dword_d30b8;
    iVar5 = iVar2;
    param_3 = dword_d30b0;
    if ((iVar4 != 0 && dword_d30b8 <= dword_d30b0 + iVar2) &&
       (iVar5 = iVar2 - iVar4, iVar5 == 0 || iVar2 < iVar4)) {
      return;
    }
  }
  else {
    iVar2 = (param_3 + iVar4) - dword_d30b8;
    iVar5 = iVar4;
    if ((iVar2 != 0 && dword_d30b8 <= param_3 + iVar4) &&
       (iVar5 = iVar4 - iVar2, iVar4 - iVar2 == 0 || iVar4 < iVar2)) {
      return;
    }
  }
  uVar6 = (uint)*(short *)(param_1 + 4);
  if (param_2 < dword_d30bc) {
    uVar7 = (param_2 + uVar6) - dword_d30bc;
    if (uVar7 != 0 && dword_d30bc <= (int)(param_2 + uVar6)) {
      puStack_1c = (ushort *)((int)puStack_1c + (uVar6 - uVar7));
      uVar3 = dword_d30c0 - dword_d30bc;
      if (uVar3 != 0 && dword_d30bc <= dword_d30c0) {
        if ((int)uVar3 <= (int)uVar7) {
          uVar7 = uVar3;
        }
        iVar4 = uVar6 - uVar7;
        param_2 = dword_d30bc;
        goto LAB_000b62f3;
      }
    }
  }
  else {
    iVar2 = (param_2 + uVar6) - dword_d30c0;
    uVar7 = uVar6;
    iVar4 = 0;
    if (((int)(param_2 + uVar6) < dword_d30c0) ||
       (uVar7 = uVar6 - iVar2, iVar4 = iVar2, uVar7 != 0 && iVar2 <= (int)uVar6)) {
LAB_000b62f3:
      if (0 < (int)uVar7) {
        puVar10 = (ushort *)(*(int *)(off_d30cc + param_3 * 4) + param_2 + dword_d30d0);
        iVar2 = dword_d30c4 - uVar7;
        uVar3 = uVar7 >> 1;
        uVar6 = uVar3;
        if ((uVar7 & 1) != 0) {
          if (uVar3 != 0) {
            do {
              do {
                puVar9 = puStack_1c;
                *puVar10 = *puVar10 & *puVar9;
                puVar10 = puVar10 + 1;
                uVar6 = uVar6 - 1;
                puStack_1c = puVar9 + 1;
              } while (uVar6 != 0);
              *(byte *)puVar10 = *(byte *)puVar10 & *(byte *)(puVar9 + 1);
              puVar10 = (ushort *)((int)puVar10 + iVar2 + 1);
              iVar8 = iVar5 + -1;
              bVar1 = 0 < iVar5;
              uVar6 = uVar3;
              puStack_1c = (ushort *)((int)puVar9 + iVar4 + 3);
              iVar5 = iVar8;
            } while (iVar8 != 0 && bVar1);
            return;
          }
          do {
            *(byte *)puVar10 = *(byte *)puVar10 & *(byte *)puStack_1c;
            puStack_1c = (ushort *)((int)puStack_1c + iVar4 + 1);
            puVar10 = (ushort *)((int)puVar10 + iVar2 + 1);
            iVar8 = iVar5 + -1;
            bVar1 = 0 < iVar5;
            iVar5 = iVar8;
          } while (iVar8 != 0 && bVar1);
          return;
        }
        do {
          do {
            puVar9 = puStack_1c + 1;
            *puVar10 = *puVar10 & *puStack_1c;
            puVar10 = puVar10 + 1;
            uVar6 = uVar6 - 1;
            puStack_1c = puVar9;
          } while (uVar6 != 0);
          puStack_1c = (ushort *)((int)puVar9 + iVar4);
          puVar10 = (ushort *)((int)puVar10 + iVar2);
          iVar8 = iVar5 + -1;
          bVar1 = 0 < iVar5;
          uVar6 = uVar3;
          iVar5 = iVar8;
        } while (iVar8 != 0 && bVar1);
      }
      return;
    }
  }
  return;
}


// ================================================================================================
// sub_b6230 @ 0xb6230 [__watcall]
// ================================================================================================

void __watcall sub_b6230(void)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  ushort *puVar10;
  ushort *puVar11;
  int in_stack_00000004;
  ushort *local_1c;
  
  iVar2 = (int)*(short *)(in_stack_00000004 + 0xc);
  iVar3 = (int)*(short *)(in_stack_00000004 + 0xe);
  iVar6 = (int)*(short *)(in_stack_00000004 + 6);
  local_1c = (ushort *)(in_stack_00000004 + 0x10);
  if (iVar3 < dword_d30b0) {
    iVar4 = (iVar3 + iVar6) - dword_d30b0;
    if (iVar4 == 0 || iVar3 + iVar6 < dword_d30b0) {
      return;
    }
    local_1c = (ushort *)((int)local_1c + (iVar6 - iVar4) * (int)*(short *)(in_stack_00000004 + 4));
    iVar6 = (dword_d30b0 + iVar4) - dword_d30b8;
    iVar7 = iVar4;
    iVar3 = dword_d30b0;
    if ((iVar6 != 0 && dword_d30b8 <= dword_d30b0 + iVar4) &&
       (iVar7 = iVar4 - iVar6, iVar7 == 0 || iVar4 < iVar6)) {
      return;
    }
  }
  else {
    iVar4 = (iVar3 + iVar6) - dword_d30b8;
    iVar7 = iVar6;
    if ((iVar4 != 0 && dword_d30b8 <= iVar3 + iVar6) &&
       (iVar7 = iVar6 - iVar4, iVar6 - iVar4 == 0 || iVar6 < iVar4)) {
      return;
    }
  }
  uVar8 = (uint)*(short *)(in_stack_00000004 + 4);
  if (iVar2 < dword_d30bc) {
    uVar9 = (iVar2 + uVar8) - dword_d30bc;
    if (uVar9 != 0 && dword_d30bc <= (int)(iVar2 + uVar8)) {
      local_1c = (ushort *)((int)local_1c + (uVar8 - uVar9));
      uVar5 = dword_d30c0 - dword_d30bc;
      if (uVar5 != 0 && dword_d30bc <= dword_d30c0) {
        if ((int)uVar5 <= (int)uVar9) {
          uVar9 = uVar5;
        }
        iVar6 = uVar8 - uVar9;
        iVar2 = dword_d30bc;
        goto LAB_000b62f3;
      }
    }
  }
  else {
    iVar4 = (iVar2 + uVar8) - dword_d30c0;
    uVar9 = uVar8;
    iVar6 = 0;
    if (((int)(iVar2 + uVar8) < dword_d30c0) ||
       (uVar9 = uVar8 - iVar4, iVar6 = iVar4, uVar9 != 0 && iVar4 <= (int)uVar8)) {
LAB_000b62f3:
      if (0 < (int)uVar9) {
        puVar11 = (ushort *)(*(int *)(off_d30cc + iVar3 * 4) + iVar2 + dword_d30d0);
        iVar2 = dword_d30c4 - uVar9;
        uVar5 = uVar9 >> 1;
        uVar8 = uVar5;
        if ((uVar9 & 1) != 0) {
          if (uVar5 != 0) {
            do {
              do {
                puVar10 = local_1c;
                *puVar11 = *puVar11 & *puVar10;
                puVar11 = puVar11 + 1;
                uVar8 = uVar8 - 1;
                local_1c = puVar10 + 1;
              } while (uVar8 != 0);
              *(byte *)puVar11 = *(byte *)puVar11 & *(byte *)(puVar10 + 1);
              puVar11 = (ushort *)((int)puVar11 + iVar2 + 1);
              iVar3 = iVar7 + -1;
              bVar1 = 0 < iVar7;
              uVar8 = uVar5;
              local_1c = (ushort *)((int)puVar10 + iVar6 + 3);
              iVar7 = iVar3;
            } while (iVar3 != 0 && bVar1);
            return;
          }
          do {
            *(byte *)puVar11 = *(byte *)puVar11 & *(byte *)local_1c;
            local_1c = (ushort *)((int)local_1c + iVar6 + 1);
            puVar11 = (ushort *)((int)puVar11 + iVar2 + 1);
            iVar3 = iVar7 + -1;
            bVar1 = 0 < iVar7;
            iVar7 = iVar3;
          } while (iVar3 != 0 && bVar1);
          return;
        }
        do {
          do {
            puVar10 = local_1c + 1;
            *puVar11 = *puVar11 & *local_1c;
            puVar11 = puVar11 + 1;
            uVar8 = uVar8 - 1;
            local_1c = puVar10;
          } while (uVar8 != 0);
          local_1c = (ushort *)((int)puVar10 + iVar6);
          puVar11 = (ushort *)((int)puVar11 + iVar2);
          iVar3 = iVar7 + -1;
          bVar1 = 0 < iVar7;
          uVar8 = uVar5;
          iVar7 = iVar3;
        } while (iVar3 != 0 && bVar1);
      }
      return;
    }
  }
  return;
}


// ================================================================================================
// sub_b637c @ 0xb637c [__cdecl]
// ================================================================================================

void sub_b637c(int param_1,int param_2,byte param_3)

{
  byte *pbVar1;
  byte *extraout_EDX;
  
  if ((((param_1 < dword_d30bc) || (dword_d30c0 <= param_1)) || (param_2 < dword_d30b0)) ||
     (dword_d30b8 <= param_2)) {
    return;
  }
  if (dword_d30c8 == 0) {
    pbVar1 = (byte *)(param_1 + *(int *)(off_d30cc + param_2 * 4) + dword_d30d0);
    *pbVar1 = *pbVar1 & param_3;
    return;
  }
  pbVar1 = (byte *)((param_1 + (&unk_d3104)[param_2] & 0xffffU) + dword_d30d0);
  if ((char)((uint)(param_1 + (&unk_d3104)[param_2]) >> 0x10) == byte_d4f54) {
    *pbVar1 = *pbVar1 & param_3;
    return;
  }
  sub_b5e04();
  *extraout_EDX = *extraout_EDX & param_3;
  return;
}


// ================================================================================================
// sub_b63ac @ 0xb63ac [__cdecl]
// ================================================================================================

void sub_b63ac(int param_1,int param_2,byte param_3)

{
  byte *pbVar1;
  byte *extraout_EDX;
  
  if (dword_d30c8 == 0) {
    pbVar1 = (byte *)(param_1 + *(int *)(off_d30cc + param_2 * 4) + dword_d30d0);
    *pbVar1 = *pbVar1 & param_3;
    return;
  }
  pbVar1 = (byte *)((param_1 + (&unk_d3104)[param_2] & 0xffffU) + dword_d30d0);
  if ((char)((uint)(param_1 + (&unk_d3104)[param_2]) >> 0x10) == byte_d4f54) {
    *pbVar1 = *pbVar1 & param_3;
    return;
  }
  sub_b5e04();
  *extraout_EDX = *extraout_EDX & param_3;
  return;
}


// ================================================================================================
// sub_b63fc @ 0xb63fc [__watcall]
// ================================================================================================

void __watcall sub_b63fc(void)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  ushort *puVar10;
  ushort *puVar11;
  int in_stack_00000004;
  short in_stack_00000008;
  short in_stack_0000000c;
  ushort *puStack_1c;
  
  iVar2 = (int)(short)(in_stack_00000008 - *(short *)(in_stack_00000004 + 8));
  iVar3 = (int)(short)(in_stack_0000000c - *(short *)(in_stack_00000004 + 10));
  iVar6 = (int)*(short *)(in_stack_00000004 + 6);
  puStack_1c = (ushort *)(in_stack_00000004 + 0x10);
  if (iVar3 < dword_d30b0) {
    iVar4 = (iVar3 + iVar6) - dword_d30b0;
    if (iVar4 == 0 || iVar3 + iVar6 < dword_d30b0) {
      return;
    }
    puStack_1c = (ushort *)
                 ((int)puStack_1c + (iVar6 - iVar4) * (int)*(short *)(in_stack_00000004 + 4));
    iVar6 = (dword_d30b0 + iVar4) - dword_d30b8;
    iVar7 = iVar4;
    iVar3 = dword_d30b0;
    if ((iVar6 != 0 && dword_d30b8 <= dword_d30b0 + iVar4) &&
       (iVar7 = iVar4 - iVar6, iVar7 == 0 || iVar4 < iVar6)) {
      return;
    }
  }
  else {
    iVar4 = (iVar3 + iVar6) - dword_d30b8;
    iVar7 = iVar6;
    if ((iVar4 != 0 && dword_d30b8 <= iVar3 + iVar6) &&
       (iVar7 = iVar6 - iVar4, iVar6 - iVar4 == 0 || iVar6 < iVar4)) {
      return;
    }
  }
  uVar8 = (uint)*(short *)(in_stack_00000004 + 4);
  if (iVar2 < dword_d30bc) {
    uVar9 = (iVar2 + uVar8) - dword_d30bc;
    if (uVar9 != 0 && dword_d30bc <= (int)(iVar2 + uVar8)) {
      puStack_1c = (ushort *)((int)puStack_1c + (uVar8 - uVar9));
      uVar5 = dword_d30c0 - dword_d30bc;
      if (uVar5 != 0 && dword_d30bc <= dword_d30c0) {
        if ((int)uVar5 <= (int)uVar9) {
          uVar9 = uVar5;
        }
        iVar6 = uVar8 - uVar9;
        iVar2 = dword_d30bc;
        goto LAB_000b64ff;
      }
    }
  }
  else {
    iVar4 = (iVar2 + uVar8) - dword_d30c0;
    uVar9 = uVar8;
    iVar6 = 0;
    if (((int)(iVar2 + uVar8) < dword_d30c0) ||
       (uVar9 = uVar8 - iVar4, iVar6 = iVar4, uVar9 != 0 && iVar4 <= (int)uVar8)) {
LAB_000b64ff:
      if (0 < (int)uVar9) {
        puVar11 = (ushort *)(*(int *)(off_d30cc + iVar3 * 4) + iVar2 + dword_d30d0);
        iVar2 = dword_d30c4 - uVar9;
        uVar5 = uVar9 >> 1;
        uVar8 = uVar5;
        if ((uVar9 & 1) != 0) {
          if (uVar5 != 0) {
            do {
              do {
                puVar10 = puStack_1c;
                *puVar11 = *puVar11 | *puVar10;
                puVar11 = puVar11 + 1;
                uVar8 = uVar8 - 1;
                puStack_1c = puVar10 + 1;
              } while (uVar8 != 0);
              *(byte *)puVar11 = *(byte *)puVar11 | *(byte *)(puVar10 + 1);
              puVar11 = (ushort *)((int)puVar11 + iVar2 + 1);
              iVar3 = iVar7 + -1;
              bVar1 = 0 < iVar7;
              uVar8 = uVar5;
              puStack_1c = (ushort *)((int)puVar10 + iVar6 + 3);
              iVar7 = iVar3;
            } while (iVar3 != 0 && bVar1);
            return;
          }
          do {
            *(byte *)puVar11 = *(byte *)puVar11 | *(byte *)puStack_1c;
            puStack_1c = (ushort *)((int)puStack_1c + iVar6 + 1);
            puVar11 = (ushort *)((int)puVar11 + iVar2 + 1);
            iVar3 = iVar7 + -1;
            bVar1 = 0 < iVar7;
            iVar7 = iVar3;
          } while (iVar3 != 0 && bVar1);
          return;
        }
        do {
          do {
            puVar10 = puStack_1c + 1;
            *puVar11 = *puVar11 | *puStack_1c;
            puVar11 = puVar11 + 1;
            uVar8 = uVar8 - 1;
            puStack_1c = puVar10;
          } while (uVar8 != 0);
          puStack_1c = (ushort *)((int)puVar10 + iVar6);
          puVar11 = (ushort *)((int)puVar11 + iVar2);
          iVar3 = iVar7 + -1;
          bVar1 = 0 < iVar7;
          uVar8 = uVar5;
          iVar7 = iVar3;
        } while (iVar3 != 0 && bVar1);
      }
      return;
    }
  }
  return;
}


// ================================================================================================
// sub_b6423 @ 0xb6423 [__cdecl]
// ================================================================================================

void sub_b6423(int param_1,int param_2,int param_3)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  ushort *puVar9;
  ushort *puVar10;
  ushort *puStack_1c;
  
  iVar4 = (int)*(short *)(param_1 + 6);
  puStack_1c = (ushort *)(param_1 + 0x10);
  if (param_3 < dword_d30b0) {
    iVar2 = (param_3 + iVar4) - dword_d30b0;
    if (iVar2 == 0 || param_3 + iVar4 < dword_d30b0) {
      return;
    }
    puStack_1c = (ushort *)((int)puStack_1c + (iVar4 - iVar2) * (int)*(short *)(param_1 + 4));
    iVar4 = (dword_d30b0 + iVar2) - dword_d30b8;
    iVar5 = iVar2;
    param_3 = dword_d30b0;
    if ((iVar4 != 0 && dword_d30b8 <= dword_d30b0 + iVar2) &&
       (iVar5 = iVar2 - iVar4, iVar5 == 0 || iVar2 < iVar4)) {
      return;
    }
  }
  else {
    iVar2 = (param_3 + iVar4) - dword_d30b8;
    iVar5 = iVar4;
    if ((iVar2 != 0 && dword_d30b8 <= param_3 + iVar4) &&
       (iVar5 = iVar4 - iVar2, iVar4 - iVar2 == 0 || iVar4 < iVar2)) {
      return;
    }
  }
  uVar6 = (uint)*(short *)(param_1 + 4);
  if (param_2 < dword_d30bc) {
    uVar7 = (param_2 + uVar6) - dword_d30bc;
    if (uVar7 != 0 && dword_d30bc <= (int)(param_2 + uVar6)) {
      puStack_1c = (ushort *)((int)puStack_1c + (uVar6 - uVar7));
      uVar3 = dword_d30c0 - dword_d30bc;
      if (uVar3 != 0 && dword_d30bc <= dword_d30c0) {
        if ((int)uVar3 <= (int)uVar7) {
          uVar7 = uVar3;
        }
        iVar4 = uVar6 - uVar7;
        param_2 = dword_d30bc;
        goto LAB_000b64ff;
      }
    }
  }
  else {
    iVar2 = (param_2 + uVar6) - dword_d30c0;
    uVar7 = uVar6;
    iVar4 = 0;
    if (((int)(param_2 + uVar6) < dword_d30c0) ||
       (uVar7 = uVar6 - iVar2, iVar4 = iVar2, uVar7 != 0 && iVar2 <= (int)uVar6)) {
LAB_000b64ff:
      if (0 < (int)uVar7) {
        puVar10 = (ushort *)(*(int *)(off_d30cc + param_3 * 4) + param_2 + dword_d30d0);
        iVar2 = dword_d30c4 - uVar7;
        uVar3 = uVar7 >> 1;
        uVar6 = uVar3;
        if ((uVar7 & 1) != 0) {
          if (uVar3 != 0) {
            do {
              do {
                puVar9 = puStack_1c;
                *puVar10 = *puVar10 | *puVar9;
                puVar10 = puVar10 + 1;
                uVar6 = uVar6 - 1;
                puStack_1c = puVar9 + 1;
              } while (uVar6 != 0);
              *(byte *)puVar10 = *(byte *)puVar10 | *(byte *)(puVar9 + 1);
              puVar10 = (ushort *)((int)puVar10 + iVar2 + 1);
              iVar8 = iVar5 + -1;
              bVar1 = 0 < iVar5;
              uVar6 = uVar3;
              puStack_1c = (ushort *)((int)puVar9 + iVar4 + 3);
              iVar5 = iVar8;
            } while (iVar8 != 0 && bVar1);
            return;
          }
          do {
            *(byte *)puVar10 = *(byte *)puVar10 | *(byte *)puStack_1c;
            puStack_1c = (ushort *)((int)puStack_1c + iVar4 + 1);
            puVar10 = (ushort *)((int)puVar10 + iVar2 + 1);
            iVar8 = iVar5 + -1;
            bVar1 = 0 < iVar5;
            iVar5 = iVar8;
          } while (iVar8 != 0 && bVar1);
          return;
        }
        do {
          do {
            puVar9 = puStack_1c + 1;
            *puVar10 = *puVar10 | *puStack_1c;
            puVar10 = puVar10 + 1;
            uVar6 = uVar6 - 1;
            puStack_1c = puVar9;
          } while (uVar6 != 0);
          puStack_1c = (ushort *)((int)puVar9 + iVar4);
          puVar10 = (ushort *)((int)puVar10 + iVar2);
          iVar8 = iVar5 + -1;
          bVar1 = 0 < iVar5;
          uVar6 = uVar3;
          iVar5 = iVar8;
        } while (iVar8 != 0 && bVar1);
      }
      return;
    }
  }
  return;
}


// ================================================================================================
// sub_b643c @ 0xb643c [__watcall]
// ================================================================================================

void __watcall sub_b643c(void)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  ushort *puVar10;
  ushort *puVar11;
  int in_stack_00000004;
  ushort *local_1c;
  
  iVar2 = (int)*(short *)(in_stack_00000004 + 0xc);
  iVar3 = (int)*(short *)(in_stack_00000004 + 0xe);
  iVar6 = (int)*(short *)(in_stack_00000004 + 6);
  local_1c = (ushort *)(in_stack_00000004 + 0x10);
  if (iVar3 < dword_d30b0) {
    iVar4 = (iVar3 + iVar6) - dword_d30b0;
    if (iVar4 == 0 || iVar3 + iVar6 < dword_d30b0) {
      return;
    }
    local_1c = (ushort *)((int)local_1c + (iVar6 - iVar4) * (int)*(short *)(in_stack_00000004 + 4));
    iVar6 = (dword_d30b0 + iVar4) - dword_d30b8;
    iVar7 = iVar4;
    iVar3 = dword_d30b0;
    if ((iVar6 != 0 && dword_d30b8 <= dword_d30b0 + iVar4) &&
       (iVar7 = iVar4 - iVar6, iVar7 == 0 || iVar4 < iVar6)) {
      return;
    }
  }
  else {
    iVar4 = (iVar3 + iVar6) - dword_d30b8;
    iVar7 = iVar6;
    if ((iVar4 != 0 && dword_d30b8 <= iVar3 + iVar6) &&
       (iVar7 = iVar6 - iVar4, iVar6 - iVar4 == 0 || iVar6 < iVar4)) {
      return;
    }
  }
  uVar8 = (uint)*(short *)(in_stack_00000004 + 4);
  if (iVar2 < dword_d30bc) {
    uVar9 = (iVar2 + uVar8) - dword_d30bc;
    if (uVar9 != 0 && dword_d30bc <= (int)(iVar2 + uVar8)) {
      local_1c = (ushort *)((int)local_1c + (uVar8 - uVar9));
      uVar5 = dword_d30c0 - dword_d30bc;
      if (uVar5 != 0 && dword_d30bc <= dword_d30c0) {
        if ((int)uVar5 <= (int)uVar9) {
          uVar9 = uVar5;
        }
        iVar6 = uVar8 - uVar9;
        iVar2 = dword_d30bc;
        goto LAB_000b64ff;
      }
    }
  }
  else {
    iVar4 = (iVar2 + uVar8) - dword_d30c0;
    uVar9 = uVar8;
    iVar6 = 0;
    if (((int)(iVar2 + uVar8) < dword_d30c0) ||
       (uVar9 = uVar8 - iVar4, iVar6 = iVar4, uVar9 != 0 && iVar4 <= (int)uVar8)) {
LAB_000b64ff:
      if (0 < (int)uVar9) {
        puVar11 = (ushort *)(*(int *)(off_d30cc + iVar3 * 4) + iVar2 + dword_d30d0);
        iVar2 = dword_d30c4 - uVar9;
        uVar5 = uVar9 >> 1;
        uVar8 = uVar5;
        if ((uVar9 & 1) != 0) {
          if (uVar5 != 0) {
            do {
              do {
                puVar10 = local_1c;
                *puVar11 = *puVar11 | *puVar10;
                puVar11 = puVar11 + 1;
                uVar8 = uVar8 - 1;
                local_1c = puVar10 + 1;
              } while (uVar8 != 0);
              *(byte *)puVar11 = *(byte *)puVar11 | *(byte *)(puVar10 + 1);
              puVar11 = (ushort *)((int)puVar11 + iVar2 + 1);
              iVar3 = iVar7 + -1;
              bVar1 = 0 < iVar7;
              uVar8 = uVar5;
              local_1c = (ushort *)((int)puVar10 + iVar6 + 3);
              iVar7 = iVar3;
            } while (iVar3 != 0 && bVar1);
            return;
          }
          do {
            *(byte *)puVar11 = *(byte *)puVar11 | *(byte *)local_1c;
            local_1c = (ushort *)((int)local_1c + iVar6 + 1);
            puVar11 = (ushort *)((int)puVar11 + iVar2 + 1);
            iVar3 = iVar7 + -1;
            bVar1 = 0 < iVar7;
            iVar7 = iVar3;
          } while (iVar3 != 0 && bVar1);
          return;
        }
        do {
          do {
            puVar10 = local_1c + 1;
            *puVar11 = *puVar11 | *local_1c;
            puVar11 = puVar11 + 1;
            uVar8 = uVar8 - 1;
            local_1c = puVar10;
          } while (uVar8 != 0);
          local_1c = (ushort *)((int)puVar10 + iVar6);
          puVar11 = (ushort *)((int)puVar11 + iVar2);
          iVar3 = iVar7 + -1;
          bVar1 = 0 < iVar7;
          uVar8 = uVar5;
          iVar7 = iVar3;
        } while (iVar3 != 0 && bVar1);
      }
      return;
    }
  }
  return;
}


// ================================================================================================
// sub_b6588 @ 0xb6588 [__cdecl]
// ================================================================================================

void sub_b6588(int param_1,int param_2,byte param_3)

{
  byte *pbVar1;
  byte *extraout_EDX;
  
  if ((((param_1 < dword_d30bc) || (dword_d30c0 <= param_1)) || (param_2 < dword_d30b0)) ||
     (dword_d30b8 <= param_2)) {
    return;
  }
  if (dword_d30c8 == 0) {
    pbVar1 = (byte *)(param_1 + *(int *)(off_d30cc + param_2 * 4) + dword_d30d0);
    *pbVar1 = *pbVar1 | param_3;
    return;
  }
  pbVar1 = (byte *)((param_1 + (&unk_d3104)[param_2] & 0xffffU) + dword_d30d0);
  if ((char)((uint)(param_1 + (&unk_d3104)[param_2]) >> 0x10) == byte_d4f54) {
    *pbVar1 = *pbVar1 | param_3;
    return;
  }
  sub_b5e04();
  *extraout_EDX = *extraout_EDX | param_3;
  return;
}


// ================================================================================================
// sub_b65b8 @ 0xb65b8 [__cdecl]
// ================================================================================================

void sub_b65b8(int param_1,int param_2,byte param_3)

{
  byte *pbVar1;
  byte *extraout_EDX;
  
  if (dword_d30c8 == 0) {
    pbVar1 = (byte *)(param_1 + *(int *)(off_d30cc + param_2 * 4) + dword_d30d0);
    *pbVar1 = *pbVar1 | param_3;
    return;
  }
  pbVar1 = (byte *)((param_1 + (&unk_d3104)[param_2] & 0xffffU) + dword_d30d0);
  if ((char)((uint)(param_1 + (&unk_d3104)[param_2]) >> 0x10) == byte_d4f54) {
    *pbVar1 = *pbVar1 | param_3;
    return;
  }
  sub_b5e04();
  *extraout_EDX = *extraout_EDX | param_3;
  return;
}


// ================================================================================================
// sub_b6608 @ 0xb6608 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall sub_b6608(void)

{
  bool bVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  uint uVar5;
  undefined2 uVar6;
  uint uVar7;
  undefined4 *puVar8;
  int in_stack_00000004;
  int in_stack_00000008;
  uint in_stack_0000000c;
  uint in_stack_00000010;
  undefined in_stack_00000014;
  
  iVar2 = dword_d30ac - in_stack_00000004;
  if (iVar2 != 0 && in_stack_00000004 <= dword_d30ac) {
    in_stack_00000004 = dword_d30ac;
    uVar5 = in_stack_0000000c - iVar2;
    bVar1 = (int)in_stack_0000000c < iVar2;
    in_stack_0000000c = uVar5;
    if (uVar5 == 0 || bVar1) {
      return;
    }
  }
  iVar2 = (in_stack_00000004 + in_stack_0000000c) - _dword_d30b4;
  if ((iVar2 == 0 || (int)(in_stack_00000004 + in_stack_0000000c) < _dword_d30b4) ||
     (uVar5 = in_stack_0000000c - iVar2, bVar1 = iVar2 <= (int)in_stack_0000000c,
     in_stack_0000000c = uVar5, uVar5 != 0 && bVar1)) {
    iVar2 = dword_d30b0 - in_stack_00000008;
    if (iVar2 != 0 && in_stack_00000008 <= dword_d30b0) {
      if (in_stack_00000010 - iVar2 == 0 || (int)in_stack_00000010 < iVar2) {
        return;
      }
      in_stack_00000008 = dword_d30b0;
      in_stack_00000010 = in_stack_00000010 - iVar2;
    }
    iVar2 = (in_stack_00000008 + in_stack_00000010) - dword_d30b8;
    if ((((iVar2 == 0 || (int)(in_stack_00000008 + in_stack_00000010) < dword_d30b8) ||
         (uVar5 = in_stack_00000010 - iVar2, bVar1 = iVar2 <= (int)in_stack_00000010,
         in_stack_00000010 = uVar5, uVar5 != 0 && bVar1)) && (0 < (int)in_stack_0000000c)) &&
       (0 < (int)in_stack_00000010)) {
      uVar6 = CONCAT11(in_stack_00000014,in_stack_00000014);
      uVar3 = CONCAT22(uVar6,uVar6);
      puVar8 = (undefined4 *)
               (*(int *)(off_d30cc + in_stack_00000008 * 4) + dword_d30d0 + in_stack_00000004);
      iVar2 = dword_d30c4 - in_stack_0000000c;
      uVar5 = in_stack_0000000c >> 2;
      switch(in_stack_0000000c & 3) {
      case 0:
        do {
          for (uVar4 = uVar5; uVar4 != 0; uVar4 = uVar4 - 1) {
            *puVar8 = uVar3;
            puVar8 = puVar8 + 1;
          }
          puVar8 = (undefined4 *)((int)puVar8 + iVar2);
          uVar4 = in_stack_00000010 - 1;
          bVar1 = 0 < (int)in_stack_00000010;
          in_stack_00000010 = uVar4;
        } while (uVar4 != 0 && bVar1);
        return;
      case 2:
        do {
          for (uVar4 = uVar5; uVar4 != 0; uVar4 = uVar4 - 1) {
            *puVar8 = uVar3;
            puVar8 = puVar8 + 1;
          }
          *(undefined2 *)puVar8 = uVar6;
          puVar8 = (undefined4 *)((int)puVar8 + iVar2 + 2);
          uVar4 = in_stack_00000010 - 1;
          bVar1 = 0 < (int)in_stack_00000010;
          in_stack_00000010 = uVar4;
        } while (uVar4 != 0 && bVar1);
        return;
      case 3:
        do {
          for (uVar4 = uVar5; uVar4 != 0; uVar4 = uVar4 - 1) {
            *puVar8 = uVar3;
            puVar8 = puVar8 + 1;
          }
          *(undefined2 *)puVar8 = uVar6;
          *(undefined *)((int)puVar8 + 2) = in_stack_00000014;
          puVar8 = (undefined4 *)((int)puVar8 + iVar2 + 3);
          uVar4 = in_stack_00000010 - 1;
          bVar1 = 0 < (int)in_stack_00000010;
          in_stack_00000010 = uVar4;
        } while (uVar4 != 0 && bVar1);
        return;
      }
      uVar4 = uVar5;
      if (uVar5 == 0) {
        iVar2 = iVar2 + 1;
        uVar5 = in_stack_00000010 >> 1;
        if ((in_stack_00000010 & 1) != 0) {
          *(undefined *)puVar8 = in_stack_00000014;
          puVar8 = (undefined4 *)((int)puVar8 + iVar2);
        }
        for (; uVar5 != 0; uVar5 = uVar5 - 1) {
          *(undefined *)puVar8 = in_stack_00000014;
          *(undefined *)(iVar2 + (int)puVar8) = in_stack_00000014;
          puVar8 = (undefined4 *)((int)puVar8 + iVar2 * 2);
        }
        return;
      }
      do {
        for (; uVar4 != 0; uVar4 = uVar4 - 1) {
          *puVar8 = uVar3;
          puVar8 = puVar8 + 1;
        }
        *(undefined *)puVar8 = in_stack_00000014;
        puVar8 = (undefined4 *)((int)puVar8 + iVar2 + 1);
        uVar7 = in_stack_00000010 - 1;
        bVar1 = 0 < (int)in_stack_00000010;
        uVar4 = uVar5;
        in_stack_00000010 = uVar7;
      } while (uVar7 != 0 && bVar1);
      return;
    }
  }
  return;
}


// ================================================================================================
// sub_b6665 @ 0xb6665 [__cdecl]
// ================================================================================================

void sub_b6665(int param_1,int param_2,uint param_3,uint param_4,undefined param_5)

{
  bool bVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  undefined2 uVar5;
  int iVar6;
  uint uVar7;
  undefined4 *puVar8;
  
  if (((int)param_3 < 1) || ((int)param_4 < 1)) {
    return;
  }
  uVar5 = CONCAT11(param_5,param_5);
  uVar2 = CONCAT22(uVar5,uVar5);
  puVar8 = (undefined4 *)(*(int *)(off_d30cc + param_2 * 4) + dword_d30d0 + param_1);
  iVar6 = dword_d30c4 - param_3;
  uVar4 = param_3 >> 2;
  switch(param_3 & 3) {
  case 0:
    do {
      for (uVar3 = uVar4; uVar3 != 0; uVar3 = uVar3 - 1) {
        *puVar8 = uVar2;
        puVar8 = puVar8 + 1;
      }
      puVar8 = (undefined4 *)((int)puVar8 + iVar6);
      uVar3 = param_4 - 1;
      bVar1 = 0 < (int)param_4;
      param_4 = uVar3;
    } while (uVar3 != 0 && bVar1);
    return;
  case 2:
    do {
      for (uVar3 = uVar4; uVar3 != 0; uVar3 = uVar3 - 1) {
        *puVar8 = uVar2;
        puVar8 = puVar8 + 1;
      }
      *(undefined2 *)puVar8 = uVar5;
      puVar8 = (undefined4 *)((int)puVar8 + iVar6 + 2);
      uVar3 = param_4 - 1;
      bVar1 = 0 < (int)param_4;
      param_4 = uVar3;
    } while (uVar3 != 0 && bVar1);
    return;
  case 3:
    do {
      for (uVar3 = uVar4; uVar3 != 0; uVar3 = uVar3 - 1) {
        *puVar8 = uVar2;
        puVar8 = puVar8 + 1;
      }
      *(undefined2 *)puVar8 = uVar5;
      *(undefined *)((int)puVar8 + 2) = param_5;
      puVar8 = (undefined4 *)((int)puVar8 + iVar6 + 3);
      uVar3 = param_4 - 1;
      bVar1 = 0 < (int)param_4;
      param_4 = uVar3;
    } while (uVar3 != 0 && bVar1);
    return;
  }
  uVar3 = uVar4;
  if (uVar4 != 0) {
    do {
      for (; uVar3 != 0; uVar3 = uVar3 - 1) {
        *puVar8 = uVar2;
        puVar8 = puVar8 + 1;
      }
      *(undefined *)puVar8 = param_5;
      puVar8 = (undefined4 *)((int)puVar8 + iVar6 + 1);
      uVar7 = param_4 - 1;
      bVar1 = 0 < (int)param_4;
      uVar3 = uVar4;
      param_4 = uVar7;
    } while (uVar7 != 0 && bVar1);
    return;
  }
  iVar6 = iVar6 + 1;
  uVar4 = param_4 >> 1;
  if ((param_4 & 1) != 0) {
    *(undefined *)puVar8 = param_5;
    puVar8 = (undefined4 *)((int)puVar8 + iVar6);
  }
  for (; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined *)puVar8 = param_5;
    *(undefined *)(iVar6 + (int)puVar8) = param_5;
    puVar8 = (undefined4 *)((int)puVar8 + iVar6 * 2);
  }
  return;
}


// ================================================================================================
// sub_b6720 @ 0xb6720 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall sub_b6720(void)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  ushort uVar6;
  uint uVar7;
  uint *puVar8;
  int in_stack_00000004;
  int in_stack_00000008;
  uint in_stack_0000000c;
  uint in_stack_00000010;
  byte in_stack_00000014;
  
  iVar2 = dword_d30ac - in_stack_00000004;
  if (iVar2 != 0 && in_stack_00000004 <= dword_d30ac) {
    in_stack_00000004 = dword_d30ac;
    uVar5 = in_stack_0000000c - iVar2;
    bVar1 = (int)in_stack_0000000c < iVar2;
    in_stack_0000000c = uVar5;
    if (uVar5 == 0 || bVar1) {
      return;
    }
  }
  iVar2 = (in_stack_00000004 + in_stack_0000000c) - _dword_d30b4;
  if ((iVar2 == 0 || (int)(in_stack_00000004 + in_stack_0000000c) < _dword_d30b4) ||
     (uVar5 = in_stack_0000000c - iVar2, bVar1 = iVar2 <= (int)in_stack_0000000c,
     in_stack_0000000c = uVar5, uVar5 != 0 && bVar1)) {
    iVar2 = dword_d30b0 - in_stack_00000008;
    if (iVar2 != 0 && in_stack_00000008 <= dword_d30b0) {
      if (in_stack_00000010 - iVar2 == 0 || (int)in_stack_00000010 < iVar2) {
        return;
      }
      in_stack_00000008 = dword_d30b0;
      in_stack_00000010 = in_stack_00000010 - iVar2;
    }
    iVar2 = (in_stack_00000008 + in_stack_00000010) - dword_d30b8;
    if ((((iVar2 == 0 || (int)(in_stack_00000008 + in_stack_00000010) < dword_d30b8) ||
         (uVar5 = in_stack_00000010 - iVar2, bVar1 = iVar2 <= (int)in_stack_00000010,
         in_stack_00000010 = uVar5, uVar5 != 0 && bVar1)) && (0 < (int)in_stack_0000000c)) &&
       (0 < (int)in_stack_00000010)) {
      uVar6 = CONCAT11(in_stack_00000014,in_stack_00000014);
      uVar3 = CONCAT22(uVar6,uVar6);
      puVar8 = (uint *)(*(int *)(off_d30cc + in_stack_00000008 * 4) + dword_d30d0 +
                       in_stack_00000004);
      iVar2 = dword_d30c4 - in_stack_0000000c;
      uVar5 = in_stack_0000000c >> 2;
      switch(in_stack_0000000c & 3) {
      case 0:
        do {
          for (uVar4 = uVar5; uVar4 != 0; uVar4 = uVar4 - 1) {
            *puVar8 = *puVar8 ^ uVar3;
            puVar8 = puVar8 + 1;
          }
          puVar8 = (uint *)((int)puVar8 + iVar2);
          uVar4 = in_stack_00000010 - 1;
          bVar1 = 0 < (int)in_stack_00000010;
          in_stack_00000010 = uVar4;
        } while (uVar4 != 0 && bVar1);
        return;
      case 2:
        uVar4 = uVar5;
        do {
          for (; uVar4 != 0; uVar4 = uVar4 - 1) {
            *puVar8 = *puVar8 ^ uVar3;
            puVar8 = puVar8 + 1;
          }
          *(ushort *)puVar8 = *(ushort *)puVar8 ^ uVar6;
          puVar8 = (uint *)((int)puVar8 + iVar2 + 2);
          uVar7 = in_stack_00000010 - 1;
          bVar1 = 0 < (int)in_stack_00000010;
          uVar4 = uVar5;
          in_stack_00000010 = uVar7;
        } while (uVar7 != 0 && bVar1);
        return;
      case 3:
        uVar4 = uVar5;
        do {
          for (; uVar4 != 0; uVar4 = uVar4 - 1) {
            *puVar8 = *puVar8 ^ uVar3;
            puVar8 = puVar8 + 1;
          }
          *(ushort *)puVar8 = *(ushort *)puVar8 ^ uVar6;
          *(byte *)((int)puVar8 + 2) = *(byte *)((int)puVar8 + 2) ^ in_stack_00000014;
          puVar8 = (uint *)((int)puVar8 + iVar2 + 3);
          uVar7 = in_stack_00000010 - 1;
          bVar1 = 0 < (int)in_stack_00000010;
          uVar4 = uVar5;
          in_stack_00000010 = uVar7;
        } while (uVar7 != 0 && bVar1);
        return;
      }
      if (uVar5 == 0) {
        iVar2 = iVar2 + 1;
        uVar5 = in_stack_00000010 >> 1;
        if ((in_stack_00000010 & 1) != 0) {
          *(byte *)puVar8 = *(byte *)puVar8 ^ in_stack_00000014;
          puVar8 = (uint *)((int)puVar8 + iVar2);
        }
        for (; uVar5 != 0; uVar5 = uVar5 - 1) {
          *(byte *)puVar8 = *(byte *)puVar8 ^ in_stack_00000014;
          *(byte *)(iVar2 + (int)puVar8) = *(byte *)(iVar2 + (int)puVar8) ^ in_stack_00000014;
          puVar8 = (uint *)((int)puVar8 + iVar2 * 2);
        }
        return;
      }
      uVar4 = uVar5;
      do {
        for (; uVar4 != 0; uVar4 = uVar4 - 1) {
          *puVar8 = *puVar8 ^ uVar3;
          puVar8 = puVar8 + 1;
        }
        *(byte *)puVar8 = *(byte *)puVar8 ^ in_stack_00000014;
        puVar8 = (uint *)((int)puVar8 + iVar2 + 1);
        uVar7 = in_stack_00000010 - 1;
        bVar1 = 0 < (int)in_stack_00000010;
        uVar4 = uVar5;
        in_stack_00000010 = uVar7;
      } while (uVar7 != 0 && bVar1);
      return;
    }
  }
  return;
}


// ================================================================================================
// sub_b677d @ 0xb677d [__cdecl]
// ================================================================================================

void sub_b677d(int param_1,int param_2,uint param_3,uint param_4,byte param_5)

{
  bool bVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  ushort uVar5;
  int iVar6;
  uint uVar7;
  uint *puVar8;
  
  if (((int)param_3 < 1) || ((int)param_4 < 1)) {
    return;
  }
  uVar5 = CONCAT11(param_5,param_5);
  uVar2 = CONCAT22(uVar5,uVar5);
  puVar8 = (uint *)(*(int *)(off_d30cc + param_2 * 4) + dword_d30d0 + param_1);
  iVar6 = dword_d30c4 - param_3;
  uVar4 = param_3 >> 2;
  switch(param_3 & 3) {
  case 0:
    do {
      for (uVar3 = uVar4; uVar3 != 0; uVar3 = uVar3 - 1) {
        *puVar8 = *puVar8 ^ uVar2;
        puVar8 = puVar8 + 1;
      }
      puVar8 = (uint *)((int)puVar8 + iVar6);
      uVar3 = param_4 - 1;
      bVar1 = 0 < (int)param_4;
      param_4 = uVar3;
    } while (uVar3 != 0 && bVar1);
    return;
  case 2:
    uVar3 = uVar4;
    do {
      for (; uVar3 != 0; uVar3 = uVar3 - 1) {
        *puVar8 = *puVar8 ^ uVar2;
        puVar8 = puVar8 + 1;
      }
      *(ushort *)puVar8 = *(ushort *)puVar8 ^ uVar5;
      puVar8 = (uint *)((int)puVar8 + iVar6 + 2);
      uVar7 = param_4 - 1;
      bVar1 = 0 < (int)param_4;
      uVar3 = uVar4;
      param_4 = uVar7;
    } while (uVar7 != 0 && bVar1);
    return;
  case 3:
    uVar3 = uVar4;
    do {
      for (; uVar3 != 0; uVar3 = uVar3 - 1) {
        *puVar8 = *puVar8 ^ uVar2;
        puVar8 = puVar8 + 1;
      }
      *(ushort *)puVar8 = *(ushort *)puVar8 ^ uVar5;
      *(byte *)((int)puVar8 + 2) = *(byte *)((int)puVar8 + 2) ^ param_5;
      puVar8 = (uint *)((int)puVar8 + iVar6 + 3);
      uVar7 = param_4 - 1;
      bVar1 = 0 < (int)param_4;
      uVar3 = uVar4;
      param_4 = uVar7;
    } while (uVar7 != 0 && bVar1);
    return;
  }
  if (uVar4 != 0) {
    uVar3 = uVar4;
    do {
      for (; uVar3 != 0; uVar3 = uVar3 - 1) {
        *puVar8 = *puVar8 ^ uVar2;
        puVar8 = puVar8 + 1;
      }
      *(byte *)puVar8 = *(byte *)puVar8 ^ param_5;
      puVar8 = (uint *)((int)puVar8 + iVar6 + 1);
      uVar7 = param_4 - 1;
      bVar1 = 0 < (int)param_4;
      uVar3 = uVar4;
      param_4 = uVar7;
    } while (uVar7 != 0 && bVar1);
    return;
  }
  iVar6 = iVar6 + 1;
  uVar4 = param_4 >> 1;
  if ((param_4 & 1) != 0) {
    *(byte *)puVar8 = *(byte *)puVar8 ^ param_5;
    puVar8 = (uint *)((int)puVar8 + iVar6);
  }
  for (; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(byte *)puVar8 = *(byte *)puVar8 ^ param_5;
    *(byte *)(iVar6 + (int)puVar8) = *(byte *)(iVar6 + (int)puVar8) ^ param_5;
    puVar8 = (uint *)((int)puVar8 + iVar6 * 2);
  }
  return;
}


// ================================================================================================
// sub_b6860 @ 0xb6860 [__watcall]
// ================================================================================================

void __watcall sub_b6860(void)

{
  bool bVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined2 *puVar8;
  undefined2 *puVar9;
  int in_stack_00000004;
  short in_stack_00000008;
  short in_stack_0000000c;
  
  puVar9 = (undefined2 *)
           (*(int *)(off_d30cc + (short)(in_stack_0000000c - *(short *)(in_stack_00000004 + 10)) * 4
                    ) + dword_d30d0 +
           (int)(short)(in_stack_00000008 - *(short *)(in_stack_00000004 + 8)));
  iVar5 = (int)*(short *)(in_stack_00000004 + 6);
  if (iVar5 != 0) {
    uVar2 = (uint)*(short *)(in_stack_00000004 + 4);
    iVar7 = dword_d30c4 - uVar2;
    puVar8 = (undefined2 *)(in_stack_00000004 + 0x10);
    uVar3 = uVar2 >> 1;
    uVar4 = uVar3;
    if ((uVar2 & 1) != 0) {
      if (uVar3 == 0) {
        do {
          *(undefined *)puVar9 = *(undefined *)puVar8;
          puVar9 = (undefined2 *)((int)puVar9 + iVar7 + 1);
          iVar6 = iVar5 + -1;
          bVar1 = 0 < iVar5;
          iVar5 = iVar6;
          puVar8 = (undefined2 *)((int)puVar8 + 1);
        } while (iVar6 != 0 && bVar1);
        return;
      }
      do {
        for (; uVar4 != 0; uVar4 = uVar4 - 1) {
          *puVar9 = *puVar8;
          puVar8 = puVar8 + 1;
          puVar9 = puVar9 + 1;
        }
        *(undefined *)puVar9 = *(undefined *)puVar8;
        puVar9 = (undefined2 *)((int)puVar9 + iVar7 + 1);
        iVar6 = iVar5 + -1;
        bVar1 = 0 < iVar5;
        uVar4 = uVar3;
        puVar8 = (undefined2 *)((int)puVar8 + 1);
        iVar5 = iVar6;
      } while (iVar6 != 0 && bVar1);
      return;
    }
    do {
      for (; uVar4 != 0; uVar4 = uVar4 - 1) {
        *puVar9 = *puVar8;
        puVar8 = puVar8 + 1;
        puVar9 = puVar9 + 1;
      }
      puVar9 = (undefined2 *)((int)puVar9 + iVar7);
      iVar6 = iVar5 + -1;
      bVar1 = 0 < iVar5;
      uVar4 = uVar3;
      iVar5 = iVar6;
    } while (iVar6 != 0 && bVar1);
  }
  return;
}


// ================================================================================================
// sub_b6887 @ 0xb6887 [__cdecl]
// ================================================================================================

void sub_b6887(int param_1,int param_2,int param_3)

{
  bool bVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined2 *puVar8;
  undefined2 *puVar9;
  
  puVar9 = (undefined2 *)(*(int *)(off_d30cc + param_3 * 4) + dword_d30d0 + param_2);
  iVar5 = (int)*(short *)(param_1 + 6);
  if (iVar5 != 0) {
    uVar2 = (uint)*(short *)(param_1 + 4);
    iVar7 = dword_d30c4 - uVar2;
    puVar8 = (undefined2 *)(param_1 + 0x10);
    uVar3 = uVar2 >> 1;
    uVar4 = uVar3;
    if ((uVar2 & 1) != 0) {
      if (uVar3 == 0) {
        do {
          *(undefined *)puVar9 = *(undefined *)puVar8;
          puVar9 = (undefined2 *)((int)puVar9 + iVar7 + 1);
          iVar6 = iVar5 + -1;
          bVar1 = 0 < iVar5;
          iVar5 = iVar6;
          puVar8 = (undefined2 *)((int)puVar8 + 1);
        } while (iVar6 != 0 && bVar1);
        return;
      }
      do {
        for (; uVar4 != 0; uVar4 = uVar4 - 1) {
          *puVar9 = *puVar8;
          puVar8 = puVar8 + 1;
          puVar9 = puVar9 + 1;
        }
        *(undefined *)puVar9 = *(undefined *)puVar8;
        puVar9 = (undefined2 *)((int)puVar9 + iVar7 + 1);
        iVar6 = iVar5 + -1;
        bVar1 = 0 < iVar5;
        uVar4 = uVar3;
        puVar8 = (undefined2 *)((int)puVar8 + 1);
        iVar5 = iVar6;
      } while (iVar6 != 0 && bVar1);
      return;
    }
    do {
      for (; uVar4 != 0; uVar4 = uVar4 - 1) {
        *puVar9 = *puVar8;
        puVar8 = puVar8 + 1;
        puVar9 = puVar9 + 1;
      }
      puVar9 = (undefined2 *)((int)puVar9 + iVar7);
      iVar6 = iVar5 + -1;
      bVar1 = 0 < iVar5;
      uVar4 = uVar3;
      iVar5 = iVar6;
    } while (iVar6 != 0 && bVar1);
  }
  return;
}


// ================================================================================================
// sub_b68a0 @ 0xb68a0 [__watcall]
// ================================================================================================

void __watcall sub_b68a0(void)

{
  bool bVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined2 *puVar8;
  undefined2 *puVar9;
  int in_stack_00000004;
  
  puVar9 = (undefined2 *)
           (*(int *)(off_d30cc + *(short *)(in_stack_00000004 + 0xe) * 4) + dword_d30d0 +
           (int)*(short *)(in_stack_00000004 + 0xc));
  iVar5 = (int)*(short *)(in_stack_00000004 + 6);
  if (iVar5 != 0) {
    uVar2 = (uint)*(short *)(in_stack_00000004 + 4);
    iVar7 = dword_d30c4 - uVar2;
    puVar8 = (undefined2 *)(in_stack_00000004 + 0x10);
    uVar3 = uVar2 >> 1;
    uVar4 = uVar3;
    if ((uVar2 & 1) != 0) {
      if (uVar3 == 0) {
        do {
          *(undefined *)puVar9 = *(undefined *)puVar8;
          puVar9 = (undefined2 *)((int)puVar9 + iVar7 + 1);
          iVar6 = iVar5 + -1;
          bVar1 = 0 < iVar5;
          iVar5 = iVar6;
          puVar8 = (undefined2 *)((int)puVar8 + 1);
        } while (iVar6 != 0 && bVar1);
        return;
      }
      do {
        for (; uVar4 != 0; uVar4 = uVar4 - 1) {
          *puVar9 = *puVar8;
          puVar8 = puVar8 + 1;
          puVar9 = puVar9 + 1;
        }
        *(undefined *)puVar9 = *(undefined *)puVar8;
        puVar9 = (undefined2 *)((int)puVar9 + iVar7 + 1);
        iVar6 = iVar5 + -1;
        bVar1 = 0 < iVar5;
        uVar4 = uVar3;
        puVar8 = (undefined2 *)((int)puVar8 + 1);
        iVar5 = iVar6;
      } while (iVar6 != 0 && bVar1);
      return;
    }
    do {
      for (; uVar4 != 0; uVar4 = uVar4 - 1) {
        *puVar9 = *puVar8;
        puVar8 = puVar8 + 1;
        puVar9 = puVar9 + 1;
      }
      puVar9 = (undefined2 *)((int)puVar9 + iVar7);
      iVar6 = iVar5 + -1;
      bVar1 = 0 < iVar5;
      uVar4 = uVar3;
      iVar5 = iVar6;
    } while (iVar6 != 0 && bVar1);
  }
  return;
}


// ================================================================================================
// sub_b6918 @ 0xb6918 [__watcall]
// ================================================================================================

void __watcall sub_b6918(void)

{
  int iVar1;
  char *pcVar2;
  bool bVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  char *pcVar7;
  char *pcVar8;
  int in_stack_00000004;
  short in_stack_00000008;
  short in_stack_0000000c;
  int iStack_14;
  
  iVar4 = (int)*(short *)(in_stack_00000004 + 4);
  iVar6 = dword_d30c4 - iVar4;
  iVar5 = iVar4;
  pcVar7 = (char *)(in_stack_00000004 + 0x10);
  pcVar2 = (char *)(*(int *)(off_d30cc +
                            (short)(in_stack_0000000c - *(short *)(in_stack_00000004 + 10)) * 4) +
                    (int)(short)(in_stack_00000008 - *(short *)(in_stack_00000004 + 8)) +
                   dword_d30d0);
  iStack_14 = (int)*(short *)(in_stack_00000004 + 6);
  do {
    do {
      pcVar8 = pcVar2;
      pcVar2 = pcVar7 + 1;
      if (*pcVar7 != -1) {
        *pcVar8 = *pcVar7;
      }
      iVar5 = iVar5 + -1;
      pcVar7 = pcVar2;
      pcVar2 = pcVar8 + 1;
    } while (iVar5 != 0);
    iVar1 = iStack_14 + -1;
    bVar3 = 0 < iStack_14;
    iVar5 = iVar4;
    pcVar2 = pcVar8 + iVar6 + 1;
    iStack_14 = iVar1;
  } while (iVar1 != 0 && bVar3);
  return;
}


// ================================================================================================
// sub_b693c @ 0xb693c [__cdecl]
// ================================================================================================

void sub_b693c(int param_1,int param_2,int param_3)

{
  int iVar1;
  char *pcVar2;
  bool bVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  char *pcVar7;
  char *pcVar8;
  int iStack_14;
  
  iVar4 = (int)*(short *)(param_1 + 4);
  iVar6 = dword_d30c4 - iVar4;
  iVar5 = iVar4;
  pcVar7 = (char *)(param_1 + 0x10);
  pcVar2 = (char *)(*(int *)(off_d30cc + param_3 * 4) + param_2 + dword_d30d0);
  iStack_14 = (int)*(short *)(param_1 + 6);
  do {
    do {
      pcVar8 = pcVar2;
      pcVar2 = pcVar7 + 1;
      if (*pcVar7 != -1) {
        *pcVar8 = *pcVar7;
      }
      iVar5 = iVar5 + -1;
      pcVar7 = pcVar2;
      pcVar2 = pcVar8 + 1;
    } while (iVar5 != 0);
    iVar1 = iStack_14 + -1;
    bVar3 = 0 < iStack_14;
    iVar5 = iVar4;
    pcVar2 = pcVar8 + iVar6 + 1;
    iStack_14 = iVar1;
  } while (iVar1 != 0 && bVar3);
  return;
}


// ================================================================================================
// sub_b6956 @ 0xb6956 [__watcall]
// ================================================================================================

void __watcall sub_b6956(void)

{
  int iVar1;
  char *pcVar2;
  bool bVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  char *pcVar7;
  char *pcVar8;
  int in_stack_00000004;
  int local_14;
  
  iVar4 = (int)*(short *)(in_stack_00000004 + 4);
  iVar6 = dword_d30c4 - iVar4;
  iVar5 = iVar4;
  pcVar7 = (char *)(in_stack_00000004 + 0x10);
  pcVar2 = (char *)(*(int *)(off_d30cc + *(short *)(in_stack_00000004 + 0xe) * 4) +
                    (int)*(short *)(in_stack_00000004 + 0xc) + dword_d30d0);
  local_14 = (int)*(short *)(in_stack_00000004 + 6);
  do {
    do {
      pcVar8 = pcVar2;
      pcVar2 = pcVar7 + 1;
      if (*pcVar7 != -1) {
        *pcVar8 = *pcVar7;
      }
      iVar5 = iVar5 + -1;
      pcVar7 = pcVar2;
      pcVar2 = pcVar8 + 1;
    } while (iVar5 != 0);
    iVar1 = local_14 + -1;
    bVar3 = 0 < local_14;
    iVar5 = iVar4;
    pcVar2 = pcVar8 + iVar6 + 1;
    local_14 = iVar1;
  } while (iVar1 != 0 && bVar3);
  return;
}


// ================================================================================================
// sub_b69c0 @ 0xb69c0 [__watcall]
// ================================================================================================

int __watcall sub_b69c0(void)

{
  char *pcVar1;
  char cVar2;
  bool bVar3;
  char *pcVar4;
  short sVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined4 uVar9;
  int iVar11;
  int iVar12;
  int iVar13;
  char *pcVar14;
  int in_stack_00000004;
  short in_stack_00000008;
  short in_stack_0000000c;
  char *pcStack_1c;
  int iStack_18;
  undefined4 uVar10;
  
  iVar6 = (int)(short)(in_stack_00000008 - *(short *)(in_stack_00000004 + 8));
  iVar7 = (int)(short)(in_stack_0000000c - *(short *)(in_stack_00000004 + 10));
  iVar11 = (int)*(short *)(in_stack_00000004 + 6);
  pcStack_1c = (char *)(in_stack_00000004 + 0x10);
  if (iVar7 < dword_d30b0) {
    iVar8 = (iVar7 + iVar11) - dword_d30b0;
    if (iVar8 == 0 || iVar7 + iVar11 < dword_d30b0) {
      return iVar8;
    }
    pcStack_1c = pcStack_1c + (iVar11 - iVar8) * (int)*(short *)(in_stack_00000004 + 4);
    iVar11 = (dword_d30b0 + iVar8) - dword_d30b8;
    iStack_18 = iVar8;
    iVar7 = dword_d30b0;
    if ((iVar11 != 0 && dword_d30b8 <= dword_d30b0 + iVar8) &&
       (iStack_18 = iVar8 - iVar11, iStack_18 == 0 || iVar8 < iVar11)) {
      return iVar11;
    }
  }
  else {
    iVar8 = (iVar7 + iVar11) - dword_d30b8;
    iStack_18 = iVar11;
    if ((iVar8 != 0 && dword_d30b8 <= iVar7 + iVar11) &&
       (iStack_18 = iVar11 - iVar8, iVar11 - iVar8 == 0 || iVar11 < iVar8)) {
      return iVar8;
    }
  }
  iVar11 = (int)*(short *)(in_stack_00000004 + 4);
  if (iVar6 < dword_d30bc) {
    iVar8 = (iVar6 + iVar11) - dword_d30bc;
    if (iVar8 != 0 && dword_d30bc <= iVar6 + iVar11) {
      pcStack_1c = pcStack_1c + (iVar11 - iVar8);
      iVar6 = dword_d30c0 - dword_d30bc;
      if (iVar6 != 0 && dword_d30bc <= dword_d30c0) {
        if (iVar6 <= iVar8) {
          iVar8 = iVar6;
        }
        iVar12 = iVar8;
        iVar13 = iVar11 - iVar8;
        iVar6 = dword_d30bc;
        goto LAB_000b6ac3;
      }
    }
  }
  else {
    iVar8 = (iVar6 + iVar11) - dword_d30c0;
    iVar12 = iVar11;
    iVar13 = 0;
    if ((iVar6 + iVar11 < dword_d30c0) ||
       (iVar12 = iVar11 - iVar8, iVar13 = iVar8, iVar12 != 0 && iVar8 <= iVar11)) {
LAB_000b6ac3:
      sVar5 = (short)iVar8;
      if (0 < iVar12) {
        iVar8 = dword_d30c4 - iVar12;
        uVar10 = 0xff00;
        iVar11 = iVar12;
        pcVar4 = (char *)(*(int *)(off_d30cc + iVar7 * 4) + iVar6 + dword_d30d0);
        do {
          do {
            pcVar14 = pcVar4;
            pcVar1 = pcStack_1c + 1;
            cVar2 = *pcStack_1c;
            uVar9 = CONCAT31((int3)((uint)uVar10 >> 8),cVar2);
            sVar5 = (short)uVar9;
            if (cVar2 != (char)((uint)uVar10 >> 8)) {
              *pcVar14 = cVar2;
            }
            iVar11 = iVar11 + -1;
            uVar10 = uVar9;
            pcStack_1c = pcVar1;
            pcVar4 = pcVar14 + 1;
          } while (iVar11 != 0);
          pcStack_1c = pcVar1 + iVar13;
          iVar6 = iStack_18 + -1;
          bVar3 = 0 < iStack_18;
          iVar11 = iVar12;
          pcVar4 = pcVar14 + iVar8 + 1;
          iStack_18 = iVar6;
        } while (iVar6 != 0 && bVar3);
      }
      return (int)sVar5;
    }
  }
  return iVar8;
}


// ================================================================================================
// sub_b69e4 @ 0xb69e4 [__cdecl]
// ================================================================================================

int sub_b69e4(int param_1,int param_2,int param_3)

{
  int iVar1;
  char *pcVar2;
  char cVar3;
  bool bVar4;
  char *pcVar5;
  short sVar6;
  int iVar7;
  undefined4 uVar8;
  int iVar10;
  int iVar11;
  int iVar12;
  char *pcVar13;
  char *pcStack_1c;
  int iStack_18;
  undefined4 uVar9;
  
  iVar10 = (int)*(short *)(param_1 + 6);
  pcStack_1c = (char *)(param_1 + 0x10);
  if (param_3 < dword_d30b0) {
    iVar7 = (param_3 + iVar10) - dword_d30b0;
    if (iVar7 == 0 || param_3 + iVar10 < dword_d30b0) {
      return iVar7;
    }
    pcStack_1c = pcStack_1c + (iVar10 - iVar7) * (int)*(short *)(param_1 + 4);
    iVar10 = (dword_d30b0 + iVar7) - dword_d30b8;
    iStack_18 = iVar7;
    param_3 = dword_d30b0;
    if ((iVar10 != 0 && dword_d30b8 <= dword_d30b0 + iVar7) &&
       (iStack_18 = iVar7 - iVar10, iStack_18 == 0 || iVar7 < iVar10)) {
      return iVar10;
    }
  }
  else {
    iVar7 = (param_3 + iVar10) - dword_d30b8;
    iStack_18 = iVar10;
    if ((iVar7 != 0 && dword_d30b8 <= param_3 + iVar10) &&
       (iStack_18 = iVar10 - iVar7, iVar10 - iVar7 == 0 || iVar10 < iVar7)) {
      return iVar7;
    }
  }
  iVar10 = (int)*(short *)(param_1 + 4);
  if (param_2 < dword_d30bc) {
    iVar7 = (param_2 + iVar10) - dword_d30bc;
    if (iVar7 != 0 && dword_d30bc <= param_2 + iVar10) {
      pcStack_1c = pcStack_1c + (iVar10 - iVar7);
      iVar11 = dword_d30c0 - dword_d30bc;
      if (iVar11 != 0 && dword_d30bc <= dword_d30c0) {
        if (iVar11 <= iVar7) {
          iVar7 = iVar11;
        }
        iVar11 = iVar7;
        iVar12 = iVar10 - iVar7;
        param_2 = dword_d30bc;
        goto LAB_000b6ac3;
      }
    }
  }
  else {
    iVar7 = (param_2 + iVar10) - dword_d30c0;
    iVar11 = iVar10;
    iVar12 = 0;
    if ((param_2 + iVar10 < dword_d30c0) ||
       (iVar11 = iVar10 - iVar7, iVar12 = iVar7, iVar11 != 0 && iVar7 <= iVar10)) {
LAB_000b6ac3:
      sVar6 = (short)iVar7;
      if (0 < iVar11) {
        iVar7 = dword_d30c4 - iVar11;
        uVar9 = 0xff00;
        iVar10 = iVar11;
        pcVar5 = (char *)(*(int *)(off_d30cc + param_3 * 4) + param_2 + dword_d30d0);
        do {
          do {
            pcVar13 = pcVar5;
            pcVar2 = pcStack_1c + 1;
            cVar3 = *pcStack_1c;
            uVar8 = CONCAT31((int3)((uint)uVar9 >> 8),cVar3);
            sVar6 = (short)uVar8;
            if (cVar3 != (char)((uint)uVar9 >> 8)) {
              *pcVar13 = cVar3;
            }
            iVar10 = iVar10 + -1;
            uVar9 = uVar8;
            pcStack_1c = pcVar2;
            pcVar5 = pcVar13 + 1;
          } while (iVar10 != 0);
          pcStack_1c = pcVar2 + iVar12;
          iVar1 = iStack_18 + -1;
          bVar4 = 0 < iStack_18;
          iVar10 = iVar11;
          pcVar5 = pcVar13 + iVar7 + 1;
          iStack_18 = iVar1;
        } while (iVar1 != 0 && bVar4);
      }
      return (int)sVar6;
    }
  }
  return iVar7;
}


// ================================================================================================
// sub_b69fe @ 0xb69fe [__watcall]
// ================================================================================================

int __watcall sub_b69fe(void)

{
  char *pcVar1;
  char cVar2;
  bool bVar3;
  char *pcVar4;
  short sVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined4 uVar9;
  int iVar11;
  int iVar12;
  int iVar13;
  char *pcVar14;
  int in_stack_00000004;
  char *local_1c;
  int local_18;
  undefined4 uVar10;
  
  iVar6 = (int)*(short *)(in_stack_00000004 + 0xc);
  iVar7 = (int)*(short *)(in_stack_00000004 + 0xe);
  iVar11 = (int)*(short *)(in_stack_00000004 + 6);
  local_1c = (char *)(in_stack_00000004 + 0x10);
  if (iVar7 < dword_d30b0) {
    iVar8 = (iVar7 + iVar11) - dword_d30b0;
    if (iVar8 == 0 || iVar7 + iVar11 < dword_d30b0) {
      return iVar8;
    }
    local_1c = local_1c + (iVar11 - iVar8) * (int)*(short *)(in_stack_00000004 + 4);
    iVar11 = (dword_d30b0 + iVar8) - dword_d30b8;
    local_18 = iVar8;
    iVar7 = dword_d30b0;
    if ((iVar11 != 0 && dword_d30b8 <= dword_d30b0 + iVar8) &&
       (local_18 = iVar8 - iVar11, local_18 == 0 || iVar8 < iVar11)) {
      return iVar11;
    }
  }
  else {
    iVar8 = (iVar7 + iVar11) - dword_d30b8;
    local_18 = iVar11;
    if ((iVar8 != 0 && dword_d30b8 <= iVar7 + iVar11) &&
       (local_18 = iVar11 - iVar8, iVar11 - iVar8 == 0 || iVar11 < iVar8)) {
      return iVar8;
    }
  }
  iVar11 = (int)*(short *)(in_stack_00000004 + 4);
  if (iVar6 < dword_d30bc) {
    iVar8 = (iVar6 + iVar11) - dword_d30bc;
    if (iVar8 != 0 && dword_d30bc <= iVar6 + iVar11) {
      local_1c = local_1c + (iVar11 - iVar8);
      iVar6 = dword_d30c0 - dword_d30bc;
      if (iVar6 != 0 && dword_d30bc <= dword_d30c0) {
        if (iVar6 <= iVar8) {
          iVar8 = iVar6;
        }
        iVar12 = iVar8;
        iVar13 = iVar11 - iVar8;
        iVar6 = dword_d30bc;
        goto LAB_000b6ac3;
      }
    }
  }
  else {
    iVar8 = (iVar6 + iVar11) - dword_d30c0;
    iVar12 = iVar11;
    iVar13 = 0;
    if ((iVar6 + iVar11 < dword_d30c0) ||
       (iVar12 = iVar11 - iVar8, iVar13 = iVar8, iVar12 != 0 && iVar8 <= iVar11)) {
LAB_000b6ac3:
      sVar5 = (short)iVar8;
      if (0 < iVar12) {
        iVar8 = dword_d30c4 - iVar12;
        uVar10 = 0xff00;
        iVar11 = iVar12;
        pcVar4 = (char *)(*(int *)(off_d30cc + iVar7 * 4) + iVar6 + dword_d30d0);
        do {
          do {
            pcVar14 = pcVar4;
            pcVar1 = local_1c + 1;
            cVar2 = *local_1c;
            uVar9 = CONCAT31((int3)((uint)uVar10 >> 8),cVar2);
            sVar5 = (short)uVar9;
            if (cVar2 != (char)((uint)uVar10 >> 8)) {
              *pcVar14 = cVar2;
            }
            iVar11 = iVar11 + -1;
            uVar10 = uVar9;
            local_1c = pcVar1;
            pcVar4 = pcVar14 + 1;
          } while (iVar11 != 0);
          local_1c = pcVar1 + iVar13;
          iVar6 = local_18 + -1;
          bVar3 = 0 < local_18;
          iVar11 = iVar12;
          pcVar4 = pcVar14 + iVar8 + 1;
          local_18 = iVar6;
        } while (iVar6 != 0 && bVar3);
      }
      return (int)sVar5;
    }
  }
  return iVar8;
}


// ================================================================================================
// sub_b6b18 @ 0xb6b18 [__watcall]
// ================================================================================================

void __watcall sub_b6b18(void)

{
  short sVar1;
  short sVar2;
  bool bVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int *piVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  int in_stack_00000004;
  short in_stack_00000008;
  short in_stack_0000000c;
  
  sVar1 = *(short *)(in_stack_00000004 + 8);
  sVar2 = *(short *)(in_stack_00000004 + 4);
  piVar7 = (int *)(off_d30cc + (short)(in_stack_0000000c - *(short *)(in_stack_00000004 + 10)) * 4);
  puVar9 = (undefined4 *)(in_stack_00000004 + 0x10);
  iVar5 = (int)*(short *)(in_stack_00000004 + 6);
  do {
    puVar8 = (undefined4 *)(*piVar7 + dword_d30d0 + (int)(short)(in_stack_00000008 - sVar1));
    for (uVar4 = (int)sVar2; (uVar4 & 3) != 0; uVar4 = uVar4 - 1) {
      *(undefined *)puVar9 = *(undefined *)puVar8;
      puVar8 = (undefined4 *)((int)puVar8 + 1);
      puVar9 = (undefined4 *)((int)puVar9 + 1);
    }
    for (uVar4 = uVar4 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *puVar9 = *puVar8;
      puVar8 = puVar8 + 1;
      puVar9 = puVar9 + 1;
    }
    piVar7 = piVar7 + 1;
    iVar6 = iVar5 + -1;
    bVar3 = 0 < iVar5;
    iVar5 = iVar6;
  } while (iVar6 != 0 && bVar3);
  return;
}


// ================================================================================================
// sub_b6b3f @ 0xb6b3f [__cdecl]
// ================================================================================================

void sub_b6b3f(int param_1,int param_2,int param_3)

{
  short sVar1;
  bool bVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  
  *(short *)(param_1 + 0xc) = (short)param_2;
  *(short *)(param_1 + 0xe) = (short)param_3;
  sVar1 = *(short *)(param_1 + 4);
  piVar6 = (int *)(off_d30cc + param_3 * 4);
  puVar8 = (undefined4 *)(param_1 + 0x10);
  iVar4 = (int)*(short *)(param_1 + 6);
  do {
    puVar7 = (undefined4 *)(*piVar6 + dword_d30d0 + param_2);
    for (uVar3 = (int)sVar1; (uVar3 & 3) != 0; uVar3 = uVar3 - 1) {
      *(undefined *)puVar8 = *(undefined *)puVar7;
      puVar7 = (undefined4 *)((int)puVar7 + 1);
      puVar8 = (undefined4 *)((int)puVar8 + 1);
    }
    for (uVar3 = uVar3 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
      *puVar8 = *puVar7;
      puVar7 = puVar7 + 1;
      puVar8 = puVar8 + 1;
    }
    piVar6 = piVar6 + 1;
    iVar5 = iVar4 + -1;
    bVar2 = 0 < iVar4;
    iVar4 = iVar5;
  } while (iVar5 != 0 && bVar2);
  return;
}


// ================================================================================================
// sub_b6b60 @ 0xb6b60 [__watcall]
// ================================================================================================

void __watcall sub_b6b60(void)

{
  short sVar1;
  short sVar2;
  bool bVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int *piVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  int in_stack_00000004;
  
  sVar1 = *(short *)(in_stack_00000004 + 0xc);
  sVar2 = *(short *)(in_stack_00000004 + 4);
  piVar7 = (int *)(off_d30cc + *(short *)(in_stack_00000004 + 0xe) * 4);
  puVar9 = (undefined4 *)(in_stack_00000004 + 0x10);
  iVar5 = (int)*(short *)(in_stack_00000004 + 6);
  do {
    puVar8 = (undefined4 *)(*piVar7 + dword_d30d0 + (int)sVar1);
    for (uVar4 = (int)sVar2; (uVar4 & 3) != 0; uVar4 = uVar4 - 1) {
      *(undefined *)puVar9 = *(undefined *)puVar8;
      puVar8 = (undefined4 *)((int)puVar8 + 1);
      puVar9 = (undefined4 *)((int)puVar9 + 1);
    }
    for (uVar4 = uVar4 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *puVar9 = *puVar8;
      puVar8 = puVar8 + 1;
      puVar9 = puVar9 + 1;
    }
    piVar7 = piVar7 + 1;
    iVar6 = iVar5 + -1;
    bVar3 = 0 < iVar5;
    iVar5 = iVar6;
  } while (iVar6 != 0 && bVar3);
  return;
}


// ================================================================================================
// sub_b6bc0 @ 0xb6bc0 [__watcall]
// ================================================================================================

int __watcall sub_b6bc0(void)

{
  undefined *puVar1;
  char cVar2;
  bool bVar3;
  char *pcVar4;
  short sVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  uint uVar14;
  char *pcVar15;
  int in_stack_00000004;
  short in_stack_00000008;
  short in_stack_0000000c;
  undefined *puStack_1c;
  int iStack_18;
  
  iVar6 = (int)(short)(in_stack_00000008 - *(short *)(in_stack_00000004 + 8));
  uVar7 = (uint)(short)(in_stack_0000000c - *(short *)(in_stack_00000004 + 10));
  iVar11 = (int)*(short *)(in_stack_00000004 + 6);
  puStack_1c = (undefined *)(in_stack_00000004 + 0x10);
  if ((int)uVar7 < (int)dword_d30b0) {
    iVar8 = (uVar7 + iVar11) - dword_d30b0;
    if (iVar8 == 0 || (int)(uVar7 + iVar11) < (int)dword_d30b0) {
      return iVar8;
    }
    puStack_1c = puStack_1c + (iVar11 - iVar8) * (int)*(short *)(in_stack_00000004 + 4);
    iVar11 = (dword_d30b0 + iVar8) - dword_d30b8;
    iStack_18 = iVar8;
    uVar7 = dword_d30b0;
    if ((iVar11 != 0 && dword_d30b8 <= (int)(dword_d30b0 + iVar8)) &&
       (iStack_18 = iVar8 - iVar11, iStack_18 == 0 || iVar8 < iVar11)) {
      return iVar11;
    }
  }
  else {
    iVar8 = (uVar7 + iVar11) - dword_d30b8;
    iStack_18 = iVar11;
    if ((iVar8 != 0 && dword_d30b8 <= (int)(uVar7 + iVar11)) &&
       (iStack_18 = iVar11 - iVar8, iVar11 - iVar8 == 0 || iVar11 < iVar8)) {
      return iVar8;
    }
  }
  iVar11 = (int)*(short *)(in_stack_00000004 + 4);
  if (iVar6 < dword_d30bc) {
    iVar8 = (iVar6 + iVar11) - dword_d30bc;
    if (iVar8 != 0 && dword_d30bc <= iVar6 + iVar11) {
      puStack_1c = puStack_1c + (iVar11 - iVar8);
      iVar6 = dword_d30c0 - dword_d30bc;
      if (iVar6 != 0 && dword_d30bc <= dword_d30c0) {
        if (iVar6 <= iVar8) {
          iVar8 = iVar6;
        }
        iVar12 = iVar8;
        iVar13 = iVar11 - iVar8;
        iVar6 = dword_d30bc;
        goto LAB_000b6cc7;
      }
    }
  }
  else {
    iVar8 = (iVar6 + iVar11) - dword_d30c0;
    iVar12 = iVar11;
    iVar13 = 0;
    if ((iVar6 + iVar11 < dword_d30c0) ||
       (iVar12 = iVar11 - iVar8, iVar13 = iVar8, iVar12 != 0 && iVar8 <= iVar11)) {
LAB_000b6cc7:
      sVar5 = (short)iVar8;
      if (0 < iVar12) {
        iVar8 = dword_d30c4 - iVar12;
        uVar14 = uVar7 & 0xffff0000;
        uVar9 = 0xff00;
        iVar11 = iVar12;
        pcVar4 = (char *)(*(int *)(off_d30cc + uVar7 * 4) + iVar6 + dword_d30d0);
        do {
          do {
            pcVar15 = pcVar4;
            puVar1 = puStack_1c + 1;
            uVar14 = CONCAT31((int3)(uVar14 >> 8),*puStack_1c);
            cVar2 = *(char *)((int)&unk_d42e4 + uVar14);
            uVar10 = CONCAT31((int3)((uint)uVar9 >> 8),cVar2);
            sVar5 = (short)uVar10;
            if (cVar2 != (char)((uint)uVar9 >> 8)) {
              *pcVar15 = cVar2;
            }
            iVar11 = iVar11 + -1;
            uVar9 = uVar10;
            puStack_1c = puVar1;
            pcVar4 = pcVar15 + 1;
          } while (iVar11 != 0);
          puStack_1c = puVar1 + iVar13;
          iVar6 = iStack_18 + -1;
          bVar3 = 0 < iStack_18;
          iVar11 = iVar12;
          pcVar4 = pcVar15 + iVar8 + 1;
          iStack_18 = iVar6;
        } while (iVar6 != 0 && bVar3);
      }
      return (int)sVar5;
    }
  }
  return iVar8;
}


// ================================================================================================
// sub_b6be5 @ 0xb6be5 [__cdecl]
// ================================================================================================

int sub_b6be5(int param_1,int param_2,uint param_3)

{
  int iVar1;
  undefined *puVar2;
  char cVar3;
  bool bVar4;
  char *pcVar5;
  short sVar6;
  int iVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  uint uVar13;
  char *pcVar14;
  undefined *puStack_1c;
  int iStack_18;
  
  iVar10 = (int)*(short *)(param_1 + 6);
  puStack_1c = (undefined *)(param_1 + 0x10);
  if ((int)param_3 < (int)dword_d30b0) {
    iVar7 = (param_3 + iVar10) - dword_d30b0;
    if (iVar7 == 0 || (int)(param_3 + iVar10) < (int)dword_d30b0) {
      return iVar7;
    }
    puStack_1c = puStack_1c + (iVar10 - iVar7) * (int)*(short *)(param_1 + 4);
    iVar10 = (dword_d30b0 + iVar7) - dword_d30b8;
    iStack_18 = iVar7;
    param_3 = dword_d30b0;
    if ((iVar10 != 0 && dword_d30b8 <= (int)(dword_d30b0 + iVar7)) &&
       (iStack_18 = iVar7 - iVar10, iStack_18 == 0 || iVar7 < iVar10)) {
      return iVar10;
    }
  }
  else {
    iVar7 = (param_3 + iVar10) - dword_d30b8;
    iStack_18 = iVar10;
    if ((iVar7 != 0 && dword_d30b8 <= (int)(param_3 + iVar10)) &&
       (iStack_18 = iVar10 - iVar7, iVar10 - iVar7 == 0 || iVar10 < iVar7)) {
      return iVar7;
    }
  }
  iVar10 = (int)*(short *)(param_1 + 4);
  if (param_2 < dword_d30bc) {
    iVar7 = (param_2 + iVar10) - dword_d30bc;
    if (iVar7 != 0 && dword_d30bc <= param_2 + iVar10) {
      puStack_1c = puStack_1c + (iVar10 - iVar7);
      iVar11 = dword_d30c0 - dword_d30bc;
      if (iVar11 != 0 && dword_d30bc <= dword_d30c0) {
        if (iVar11 <= iVar7) {
          iVar7 = iVar11;
        }
        iVar11 = iVar7;
        iVar12 = iVar10 - iVar7;
        param_2 = dword_d30bc;
        goto LAB_000b6cc7;
      }
    }
  }
  else {
    iVar7 = (param_2 + iVar10) - dword_d30c0;
    iVar11 = iVar10;
    iVar12 = 0;
    if ((param_2 + iVar10 < dword_d30c0) ||
       (iVar11 = iVar10 - iVar7, iVar12 = iVar7, iVar11 != 0 && iVar7 <= iVar10)) {
LAB_000b6cc7:
      sVar6 = (short)iVar7;
      if (0 < iVar11) {
        iVar7 = dword_d30c4 - iVar11;
        uVar13 = param_3 & 0xffff0000;
        uVar8 = 0xff00;
        iVar10 = iVar11;
        pcVar5 = (char *)(*(int *)(off_d30cc + param_3 * 4) + param_2 + dword_d30d0);
        do {
          do {
            pcVar14 = pcVar5;
            puVar2 = puStack_1c + 1;
            uVar13 = CONCAT31((int3)(uVar13 >> 8),*puStack_1c);
            cVar3 = *(char *)((int)&unk_d42e4 + uVar13);
            uVar9 = CONCAT31((int3)((uint)uVar8 >> 8),cVar3);
            sVar6 = (short)uVar9;
            if (cVar3 != (char)((uint)uVar8 >> 8)) {
              *pcVar14 = cVar3;
            }
            iVar10 = iVar10 + -1;
            uVar8 = uVar9;
            puStack_1c = puVar2;
            pcVar5 = pcVar14 + 1;
          } while (iVar10 != 0);
          puStack_1c = puVar2 + iVar12;
          iVar1 = iStack_18 + -1;
          bVar4 = 0 < iStack_18;
          iVar10 = iVar11;
          pcVar5 = pcVar14 + iVar7 + 1;
          iStack_18 = iVar1;
        } while (iVar1 != 0 && bVar4);
      }
      return (int)sVar6;
    }
  }
  return iVar7;
}


// ================================================================================================
// sub_b6c00 @ 0xb6c00 [__watcall]
// ================================================================================================

int __watcall sub_b6c00(void)

{
  undefined *puVar1;
  char cVar2;
  bool bVar3;
  char *pcVar4;
  short sVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  uint uVar14;
  char *pcVar15;
  int in_stack_00000004;
  undefined *local_1c;
  int local_18;
  
  iVar6 = (int)*(short *)(in_stack_00000004 + 0xc);
  uVar7 = (uint)*(short *)(in_stack_00000004 + 0xe);
  iVar11 = (int)*(short *)(in_stack_00000004 + 6);
  local_1c = (undefined *)(in_stack_00000004 + 0x10);
  if ((int)uVar7 < (int)dword_d30b0) {
    iVar8 = (uVar7 + iVar11) - dword_d30b0;
    if (iVar8 == 0 || (int)(uVar7 + iVar11) < (int)dword_d30b0) {
      return iVar8;
    }
    local_1c = local_1c + (iVar11 - iVar8) * (int)*(short *)(in_stack_00000004 + 4);
    iVar11 = (dword_d30b0 + iVar8) - dword_d30b8;
    local_18 = iVar8;
    uVar7 = dword_d30b0;
    if ((iVar11 != 0 && dword_d30b8 <= (int)(dword_d30b0 + iVar8)) &&
       (local_18 = iVar8 - iVar11, local_18 == 0 || iVar8 < iVar11)) {
      return iVar11;
    }
  }
  else {
    iVar8 = (uVar7 + iVar11) - dword_d30b8;
    local_18 = iVar11;
    if ((iVar8 != 0 && dword_d30b8 <= (int)(uVar7 + iVar11)) &&
       (local_18 = iVar11 - iVar8, iVar11 - iVar8 == 0 || iVar11 < iVar8)) {
      return iVar8;
    }
  }
  iVar11 = (int)*(short *)(in_stack_00000004 + 4);
  if (iVar6 < dword_d30bc) {
    iVar8 = (iVar6 + iVar11) - dword_d30bc;
    if (iVar8 != 0 && dword_d30bc <= iVar6 + iVar11) {
      local_1c = local_1c + (iVar11 - iVar8);
      iVar6 = dword_d30c0 - dword_d30bc;
      if (iVar6 != 0 && dword_d30bc <= dword_d30c0) {
        if (iVar6 <= iVar8) {
          iVar8 = iVar6;
        }
        iVar12 = iVar8;
        iVar13 = iVar11 - iVar8;
        iVar6 = dword_d30bc;
        goto LAB_000b6cc7;
      }
    }
  }
  else {
    iVar8 = (iVar6 + iVar11) - dword_d30c0;
    iVar12 = iVar11;
    iVar13 = 0;
    if ((iVar6 + iVar11 < dword_d30c0) ||
       (iVar12 = iVar11 - iVar8, iVar13 = iVar8, iVar12 != 0 && iVar8 <= iVar11)) {
LAB_000b6cc7:
      sVar5 = (short)iVar8;
      if (0 < iVar12) {
        iVar8 = dword_d30c4 - iVar12;
        uVar14 = uVar7 & 0xffff0000;
        uVar9 = 0xff00;
        iVar11 = iVar12;
        pcVar4 = (char *)(*(int *)(off_d30cc + uVar7 * 4) + iVar6 + dword_d30d0);
        do {
          do {
            pcVar15 = pcVar4;
            puVar1 = local_1c + 1;
            uVar14 = CONCAT31((int3)(uVar14 >> 8),*local_1c);
            cVar2 = *(char *)((int)&unk_d42e4 + uVar14);
            uVar10 = CONCAT31((int3)((uint)uVar9 >> 8),cVar2);
            sVar5 = (short)uVar10;
            if (cVar2 != (char)((uint)uVar9 >> 8)) {
              *pcVar15 = cVar2;
            }
            iVar11 = iVar11 + -1;
            uVar9 = uVar10;
            local_1c = puVar1;
            pcVar4 = pcVar15 + 1;
          } while (iVar11 != 0);
          local_1c = puVar1 + iVar13;
          iVar6 = local_18 + -1;
          bVar3 = 0 < local_18;
          iVar11 = iVar12;
          pcVar4 = pcVar15 + iVar8 + 1;
          local_18 = iVar6;
        } while (iVar6 != 0 && bVar3);
      }
      return (int)sVar5;
    }
  }
  return iVar8;
}


// ================================================================================================
// sub_b6d24 @ 0xb6d24 [__watcall]
// ================================================================================================

void __watcall sub_b6d24(void)

{
  int iVar1;
  byte *pbVar2;
  bool bVar3;
  char *pcVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  byte *pbVar8;
  char *pcVar9;
  int in_stack_00000004;
  short in_stack_00000008;
  short in_stack_0000000c;
  int iStack_14;
  
  iVar5 = (int)*(short *)(in_stack_00000004 + 4);
  iVar7 = dword_d30c4 - iVar5;
  iVar6 = iVar5;
  pbVar8 = (byte *)(in_stack_00000004 + 0x10);
  pcVar4 = (char *)(*(int *)(off_d30cc +
                            (short)(in_stack_0000000c - *(short *)(in_stack_00000004 + 10)) * 4) +
                    dword_d30d0 +
                   (int)(short)(in_stack_00000008 - *(short *)(in_stack_00000004 + 8)));
  iStack_14 = (int)*(short *)(in_stack_00000004 + 6);
  do {
    do {
      pcVar9 = pcVar4;
      pbVar2 = pbVar8 + 1;
      if (*(char *)((int)&unk_d42e4 + (uint)*pbVar8) != -1) {
        *pcVar9 = *(char *)((int)&unk_d42e4 + (uint)*pbVar8);
      }
      iVar6 = iVar6 + -1;
      pbVar8 = pbVar2;
      pcVar4 = pcVar9 + 1;
    } while (iVar6 != 0);
    iVar1 = iStack_14 + -1;
    bVar3 = 0 < iStack_14;
    iVar6 = iVar5;
    pcVar4 = pcVar9 + iVar7 + 1;
    iStack_14 = iVar1;
  } while (iVar1 != 0 && bVar3);
  return;
}


// ================================================================================================
// sub_b6d47 @ 0xb6d47 [__cdecl]
// ================================================================================================

void sub_b6d47(int param_1,int param_2,int param_3)

{
  int iVar1;
  byte *pbVar2;
  bool bVar3;
  char *pcVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  byte *pbVar8;
  char *pcVar9;
  int iStack_14;
  
  iVar5 = (int)*(short *)(param_1 + 4);
  iVar7 = dword_d30c4 - iVar5;
  iVar6 = iVar5;
  pbVar8 = (byte *)(param_1 + 0x10);
  pcVar4 = (char *)(*(int *)(off_d30cc + param_3 * 4) + dword_d30d0 + param_2);
  iStack_14 = (int)*(short *)(param_1 + 6);
  do {
    do {
      pcVar9 = pcVar4;
      pbVar2 = pbVar8 + 1;
      if (*(char *)((int)&unk_d42e4 + (uint)*pbVar8) != -1) {
        *pcVar9 = *(char *)((int)&unk_d42e4 + (uint)*pbVar8);
      }
      iVar6 = iVar6 + -1;
      pbVar8 = pbVar2;
      pcVar4 = pcVar9 + 1;
    } while (iVar6 != 0);
    iVar1 = iStack_14 + -1;
    bVar3 = 0 < iStack_14;
    iVar6 = iVar5;
    pcVar4 = pcVar9 + iVar7 + 1;
    iStack_14 = iVar1;
  } while (iVar1 != 0 && bVar3);
  return;
}


// ================================================================================================
// sub_b6d60 @ 0xb6d60 [__watcall]
// ================================================================================================

void __watcall sub_b6d60(void)

{
  int iVar1;
  byte *pbVar2;
  bool bVar3;
  char *pcVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  byte *pbVar8;
  char *pcVar9;
  int in_stack_00000004;
  int local_14;
  
  iVar5 = (int)*(short *)(in_stack_00000004 + 4);
  iVar7 = dword_d30c4 - iVar5;
  iVar6 = iVar5;
  pbVar8 = (byte *)(in_stack_00000004 + 0x10);
  pcVar4 = (char *)(*(int *)(off_d30cc + *(short *)(in_stack_00000004 + 0xe) * 4) + dword_d30d0 +
                   (int)*(short *)(in_stack_00000004 + 0xc));
  local_14 = (int)*(short *)(in_stack_00000004 + 6);
  do {
    do {
      pcVar9 = pcVar4;
      pbVar2 = pbVar8 + 1;
      if (*(char *)((int)&unk_d42e4 + (uint)*pbVar8) != -1) {
        *pcVar9 = *(char *)((int)&unk_d42e4 + (uint)*pbVar8);
      }
      iVar6 = iVar6 + -1;
      pbVar8 = pbVar2;
      pcVar4 = pcVar9 + 1;
    } while (iVar6 != 0);
    iVar1 = local_14 + -1;
    bVar3 = 0 < local_14;
    iVar6 = iVar5;
    pcVar4 = pcVar9 + iVar7 + 1;
    local_14 = iVar1;
  } while (iVar1 != 0 && bVar3);
  return;
}


// ================================================================================================
// sub_b6dd0 @ 0xb6dd0 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall sub_b6dd0(void)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  undefined2 *puVar10;
  int in_stack_00000004;
  short in_stack_00000008;
  short in_stack_0000000c;
  undefined2 *puStack_1c;
  
  iVar2 = (int)(short)(in_stack_00000008 - *(short *)(in_stack_00000004 + 8));
  iVar3 = (int)(short)(in_stack_0000000c - *(short *)(in_stack_00000004 + 10));
  iVar6 = (int)*(short *)(in_stack_00000004 + 6);
  puStack_1c = (undefined2 *)(in_stack_00000004 + 0x10);
  if (iVar3 < dword_d30b0) {
    iVar4 = (iVar3 + iVar6) - dword_d30b0;
    if (iVar4 == 0 || iVar3 + iVar6 < dword_d30b0) {
      return;
    }
    puStack_1c = (undefined2 *)
                 ((int)puStack_1c + (iVar6 - iVar4) * (int)*(short *)(in_stack_00000004 + 4));
    iVar6 = (dword_d30b0 + iVar4) - dword_d30b8;
    iVar7 = iVar4;
    iVar3 = dword_d30b0;
    if ((iVar6 != 0 && dword_d30b8 <= dword_d30b0 + iVar4) &&
       (iVar7 = iVar4 - iVar6, iVar7 == 0 || iVar4 < iVar6)) {
      return;
    }
  }
  else {
    iVar4 = (iVar3 + iVar6) - dword_d30b8;
    iVar7 = iVar6;
    if ((iVar4 != 0 && dword_d30b8 <= iVar3 + iVar6) &&
       (iVar7 = iVar6 - iVar4, iVar6 - iVar4 == 0 || iVar6 < iVar4)) {
      return;
    }
  }
  uVar8 = (uint)*(short *)(in_stack_00000004 + 4);
  if (iVar2 < dword_d30ac) {
    uVar9 = (iVar2 + uVar8) - dword_d30ac;
    if (uVar9 == 0 || (int)(iVar2 + uVar8) < dword_d30ac) {
      return;
    }
    puStack_1c = (undefined2 *)((int)puStack_1c + (uVar8 - uVar9));
    uVar5 = _dword_d30b4 - dword_d30ac;
    if (uVar5 == 0 || _dword_d30b4 < dword_d30ac) {
      return;
    }
    if ((int)uVar5 <= (int)uVar9) {
      uVar9 = uVar5;
    }
    iVar6 = uVar8 - uVar9;
    iVar2 = dword_d30ac;
  }
  else {
    iVar4 = (iVar2 + uVar8) - _dword_d30b4;
    uVar9 = uVar8;
    iVar6 = 0;
    if ((_dword_d30b4 <= (int)(iVar2 + uVar8)) &&
       (uVar9 = uVar8 - iVar4, iVar6 = iVar4, uVar9 == 0 || (int)uVar8 < iVar4)) {
      return;
    }
  }
  if (0 < (int)uVar9) {
    puVar10 = (undefined2 *)(*(int *)(off_d30cc + iVar3 * 4) + dword_d30d0 + iVar2);
    iVar2 = dword_d30c4 - uVar9;
    if (iVar6 == 0) {
      uVar5 = uVar9 >> 1;
      uVar8 = uVar5;
      if ((uVar9 & 1) == 0) {
        do {
          for (; uVar8 != 0; uVar8 = uVar8 - 1) {
            *puStack_1c = *puVar10;
            puVar10 = puVar10 + 1;
            puStack_1c = puStack_1c + 1;
          }
          puVar10 = (undefined2 *)((int)puVar10 + iVar2);
          iVar3 = iVar7 + -1;
          bVar1 = 0 < iVar7;
          uVar8 = uVar5;
          iVar7 = iVar3;
        } while (iVar3 != 0 && bVar1);
      }
      else if (uVar5 == 0) {
        do {
          *(undefined *)puStack_1c = *(undefined *)puVar10;
          puVar10 = (undefined2 *)((int)puVar10 + iVar2 + 1);
          iVar2 = iVar2 + 1;
          iVar3 = iVar7 + -1;
          bVar1 = 0 < iVar7;
          iVar7 = iVar3;
          puStack_1c = (undefined2 *)((int)puStack_1c + 1);
        } while (iVar3 != 0 && bVar1);
      }
      else {
        do {
          for (; uVar8 != 0; uVar8 = uVar8 - 1) {
            *puStack_1c = *puVar10;
            puVar10 = puVar10 + 1;
            puStack_1c = puStack_1c + 1;
          }
          *(undefined *)puStack_1c = *(undefined *)puVar10;
          puVar10 = (undefined2 *)((int)puVar10 + iVar2 + 1);
          iVar3 = iVar7 + -1;
          bVar1 = 0 < iVar7;
          uVar8 = uVar5;
          puStack_1c = (undefined2 *)((int)puStack_1c + 1);
          iVar7 = iVar3;
        } while (iVar3 != 0 && bVar1);
      }
    }
    else {
      uVar5 = uVar9 >> 1;
      uVar8 = uVar5;
      if ((uVar9 & 1) == 0) {
        do {
          for (; uVar8 != 0; uVar8 = uVar8 - 1) {
            *puStack_1c = *puVar10;
            puVar10 = puVar10 + 1;
            puStack_1c = puStack_1c + 1;
          }
          puStack_1c = (undefined2 *)((int)puStack_1c + iVar6);
          puVar10 = (undefined2 *)((int)puVar10 + iVar2);
          iVar3 = iVar7 + -1;
          bVar1 = 0 < iVar7;
          uVar8 = uVar5;
          iVar7 = iVar3;
        } while (iVar3 != 0 && bVar1);
      }
      else if (uVar5 == 0) {
        do {
          *(undefined *)puStack_1c = *(undefined *)puVar10;
          puStack_1c = (undefined2 *)((int)puStack_1c + iVar6 + 1);
          puVar10 = (undefined2 *)((int)puVar10 + iVar2 + 1);
          iVar3 = iVar7 + -1;
          bVar1 = 0 < iVar7;
          iVar7 = iVar3;
        } while (iVar3 != 0 && bVar1);
      }
      else {
        do {
          for (; uVar8 != 0; uVar8 = uVar8 - 1) {
            *puStack_1c = *puVar10;
            puVar10 = puVar10 + 1;
            puStack_1c = puStack_1c + 1;
          }
          *(undefined *)puStack_1c = *(undefined *)puVar10;
          puStack_1c = (undefined2 *)((int)puStack_1c + iVar6 + 1);
          puVar10 = (undefined2 *)((int)puVar10 + iVar2 + 1);
          iVar3 = iVar7 + -1;
          bVar1 = 0 < iVar7;
          uVar8 = uVar5;
          iVar7 = iVar3;
        } while (iVar3 != 0 && bVar1);
      }
    }
  }
  return;
}


// ================================================================================================
// sub_b6df7 @ 0xb6df7 [__cdecl]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_b6df7(int param_1,int param_2,int param_3)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  undefined2 *puVar9;
  undefined2 *puStack_1c;
  
  *(short *)(param_1 + 0xc) = (short)param_2;
  *(short *)(param_1 + 0xe) = (short)param_3;
  iVar4 = (int)*(short *)(param_1 + 6);
  puStack_1c = (undefined2 *)(param_1 + 0x10);
  if (param_3 < dword_d30b0) {
    iVar2 = (param_3 + iVar4) - dword_d30b0;
    if (iVar2 == 0 || param_3 + iVar4 < dword_d30b0) {
      return;
    }
    puStack_1c = (undefined2 *)((int)puStack_1c + (iVar4 - iVar2) * (int)*(short *)(param_1 + 4));
    iVar4 = (dword_d30b0 + iVar2) - dword_d30b8;
    iVar5 = iVar2;
    param_3 = dword_d30b0;
    if ((iVar4 != 0 && dword_d30b8 <= dword_d30b0 + iVar2) &&
       (iVar5 = iVar2 - iVar4, iVar5 == 0 || iVar2 < iVar4)) {
      return;
    }
  }
  else {
    iVar2 = (param_3 + iVar4) - dword_d30b8;
    iVar5 = iVar4;
    if ((iVar2 != 0 && dword_d30b8 <= param_3 + iVar4) &&
       (iVar5 = iVar4 - iVar2, iVar4 - iVar2 == 0 || iVar4 < iVar2)) {
      return;
    }
  }
  uVar6 = (uint)*(short *)(param_1 + 4);
  if (param_2 < dword_d30ac) {
    uVar7 = (param_2 + uVar6) - dword_d30ac;
    if (uVar7 == 0 || (int)(param_2 + uVar6) < dword_d30ac) {
      return;
    }
    puStack_1c = (undefined2 *)((int)puStack_1c + (uVar6 - uVar7));
    uVar3 = _dword_d30b4 - dword_d30ac;
    if (uVar3 == 0 || _dword_d30b4 < dword_d30ac) {
      return;
    }
    if ((int)uVar3 <= (int)uVar7) {
      uVar7 = uVar3;
    }
    iVar4 = uVar6 - uVar7;
    param_2 = dword_d30ac;
  }
  else {
    iVar2 = (param_2 + uVar6) - _dword_d30b4;
    uVar7 = uVar6;
    iVar4 = 0;
    if ((_dword_d30b4 <= (int)(param_2 + uVar6)) &&
       (uVar7 = uVar6 - iVar2, iVar4 = iVar2, uVar7 == 0 || (int)uVar6 < iVar2)) {
      return;
    }
  }
  if (0 < (int)uVar7) {
    puVar9 = (undefined2 *)(*(int *)(off_d30cc + param_3 * 4) + dword_d30d0 + param_2);
    iVar2 = dword_d30c4 - uVar7;
    if (iVar4 == 0) {
      uVar3 = uVar7 >> 1;
      uVar6 = uVar3;
      if ((uVar7 & 1) == 0) {
        do {
          for (; uVar6 != 0; uVar6 = uVar6 - 1) {
            *puStack_1c = *puVar9;
            puVar9 = puVar9 + 1;
            puStack_1c = puStack_1c + 1;
          }
          puVar9 = (undefined2 *)((int)puVar9 + iVar2);
          iVar4 = iVar5 + -1;
          bVar1 = 0 < iVar5;
          uVar6 = uVar3;
          iVar5 = iVar4;
        } while (iVar4 != 0 && bVar1);
      }
      else if (uVar3 == 0) {
        do {
          *(undefined *)puStack_1c = *(undefined *)puVar9;
          puVar9 = (undefined2 *)((int)puVar9 + iVar2 + 1);
          iVar2 = iVar2 + 1;
          iVar4 = iVar5 + -1;
          bVar1 = 0 < iVar5;
          iVar5 = iVar4;
          puStack_1c = (undefined2 *)((int)puStack_1c + 1);
        } while (iVar4 != 0 && bVar1);
      }
      else {
        do {
          for (; uVar6 != 0; uVar6 = uVar6 - 1) {
            *puStack_1c = *puVar9;
            puVar9 = puVar9 + 1;
            puStack_1c = puStack_1c + 1;
          }
          *(undefined *)puStack_1c = *(undefined *)puVar9;
          puVar9 = (undefined2 *)((int)puVar9 + iVar2 + 1);
          iVar4 = iVar5 + -1;
          bVar1 = 0 < iVar5;
          uVar6 = uVar3;
          puStack_1c = (undefined2 *)((int)puStack_1c + 1);
          iVar5 = iVar4;
        } while (iVar4 != 0 && bVar1);
      }
    }
    else {
      uVar3 = uVar7 >> 1;
      uVar6 = uVar3;
      if ((uVar7 & 1) == 0) {
        do {
          for (; uVar6 != 0; uVar6 = uVar6 - 1) {
            *puStack_1c = *puVar9;
            puVar9 = puVar9 + 1;
            puStack_1c = puStack_1c + 1;
          }
          puStack_1c = (undefined2 *)((int)puStack_1c + iVar4);
          puVar9 = (undefined2 *)((int)puVar9 + iVar2);
          iVar8 = iVar5 + -1;
          bVar1 = 0 < iVar5;
          uVar6 = uVar3;
          iVar5 = iVar8;
        } while (iVar8 != 0 && bVar1);
      }
      else if (uVar3 == 0) {
        do {
          *(undefined *)puStack_1c = *(undefined *)puVar9;
          puStack_1c = (undefined2 *)((int)puStack_1c + iVar4 + 1);
          puVar9 = (undefined2 *)((int)puVar9 + iVar2 + 1);
          iVar8 = iVar5 + -1;
          bVar1 = 0 < iVar5;
          iVar5 = iVar8;
        } while (iVar8 != 0 && bVar1);
      }
      else {
        do {
          for (; uVar6 != 0; uVar6 = uVar6 - 1) {
            *puStack_1c = *puVar9;
            puVar9 = puVar9 + 1;
            puStack_1c = puStack_1c + 1;
          }
          *(undefined *)puStack_1c = *(undefined *)puVar9;
          puStack_1c = (undefined2 *)((int)puStack_1c + iVar4 + 1);
          puVar9 = (undefined2 *)((int)puVar9 + iVar2 + 1);
          iVar8 = iVar5 + -1;
          bVar1 = 0 < iVar5;
          uVar6 = uVar3;
          iVar5 = iVar8;
        } while (iVar8 != 0 && bVar1);
      }
    }
  }
  return;
}


// ================================================================================================
// sub_b6e18 @ 0xb6e18 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall sub_b6e18(void)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  undefined2 *puVar10;
  int in_stack_00000004;
  undefined2 *local_1c;
  
  iVar2 = (int)*(short *)(in_stack_00000004 + 0xc);
  iVar3 = (int)*(short *)(in_stack_00000004 + 0xe);
  iVar6 = (int)*(short *)(in_stack_00000004 + 6);
  local_1c = (undefined2 *)(in_stack_00000004 + 0x10);
  if (iVar3 < dword_d30b0) {
    iVar4 = (iVar3 + iVar6) - dword_d30b0;
    if (iVar4 == 0 || iVar3 + iVar6 < dword_d30b0) {
      return;
    }
    local_1c = (undefined2 *)
               ((int)local_1c + (iVar6 - iVar4) * (int)*(short *)(in_stack_00000004 + 4));
    iVar6 = (dword_d30b0 + iVar4) - dword_d30b8;
    iVar7 = iVar4;
    iVar3 = dword_d30b0;
    if ((iVar6 != 0 && dword_d30b8 <= dword_d30b0 + iVar4) &&
       (iVar7 = iVar4 - iVar6, iVar7 == 0 || iVar4 < iVar6)) {
      return;
    }
  }
  else {
    iVar4 = (iVar3 + iVar6) - dword_d30b8;
    iVar7 = iVar6;
    if ((iVar4 != 0 && dword_d30b8 <= iVar3 + iVar6) &&
       (iVar7 = iVar6 - iVar4, iVar6 - iVar4 == 0 || iVar6 < iVar4)) {
      return;
    }
  }
  uVar8 = (uint)*(short *)(in_stack_00000004 + 4);
  if (iVar2 < dword_d30ac) {
    uVar9 = (iVar2 + uVar8) - dword_d30ac;
    if (uVar9 == 0 || (int)(iVar2 + uVar8) < dword_d30ac) {
      return;
    }
    local_1c = (undefined2 *)((int)local_1c + (uVar8 - uVar9));
    uVar5 = _dword_d30b4 - dword_d30ac;
    if (uVar5 == 0 || _dword_d30b4 < dword_d30ac) {
      return;
    }
    if ((int)uVar5 <= (int)uVar9) {
      uVar9 = uVar5;
    }
    iVar6 = uVar8 - uVar9;
    iVar2 = dword_d30ac;
  }
  else {
    iVar4 = (iVar2 + uVar8) - _dword_d30b4;
    uVar9 = uVar8;
    iVar6 = 0;
    if ((_dword_d30b4 <= (int)(iVar2 + uVar8)) &&
       (uVar9 = uVar8 - iVar4, iVar6 = iVar4, uVar9 == 0 || (int)uVar8 < iVar4)) {
      return;
    }
  }
  if (0 < (int)uVar9) {
    puVar10 = (undefined2 *)(*(int *)(off_d30cc + iVar3 * 4) + dword_d30d0 + iVar2);
    iVar2 = dword_d30c4 - uVar9;
    if (iVar6 == 0) {
      uVar5 = uVar9 >> 1;
      uVar8 = uVar5;
      if ((uVar9 & 1) == 0) {
        do {
          for (; uVar8 != 0; uVar8 = uVar8 - 1) {
            *local_1c = *puVar10;
            puVar10 = puVar10 + 1;
            local_1c = local_1c + 1;
          }
          puVar10 = (undefined2 *)((int)puVar10 + iVar2);
          iVar3 = iVar7 + -1;
          bVar1 = 0 < iVar7;
          uVar8 = uVar5;
          iVar7 = iVar3;
        } while (iVar3 != 0 && bVar1);
      }
      else if (uVar5 == 0) {
        do {
          *(undefined *)local_1c = *(undefined *)puVar10;
          puVar10 = (undefined2 *)((int)puVar10 + iVar2 + 1);
          iVar2 = iVar2 + 1;
          iVar3 = iVar7 + -1;
          bVar1 = 0 < iVar7;
          iVar7 = iVar3;
          local_1c = (undefined2 *)((int)local_1c + 1);
        } while (iVar3 != 0 && bVar1);
      }
      else {
        do {
          for (; uVar8 != 0; uVar8 = uVar8 - 1) {
            *local_1c = *puVar10;
            puVar10 = puVar10 + 1;
            local_1c = local_1c + 1;
          }
          *(undefined *)local_1c = *(undefined *)puVar10;
          puVar10 = (undefined2 *)((int)puVar10 + iVar2 + 1);
          iVar3 = iVar7 + -1;
          bVar1 = 0 < iVar7;
          uVar8 = uVar5;
          local_1c = (undefined2 *)((int)local_1c + 1);
          iVar7 = iVar3;
        } while (iVar3 != 0 && bVar1);
      }
    }
    else {
      uVar5 = uVar9 >> 1;
      uVar8 = uVar5;
      if ((uVar9 & 1) == 0) {
        do {
          for (; uVar8 != 0; uVar8 = uVar8 - 1) {
            *local_1c = *puVar10;
            puVar10 = puVar10 + 1;
            local_1c = local_1c + 1;
          }
          local_1c = (undefined2 *)((int)local_1c + iVar6);
          puVar10 = (undefined2 *)((int)puVar10 + iVar2);
          iVar3 = iVar7 + -1;
          bVar1 = 0 < iVar7;
          uVar8 = uVar5;
          iVar7 = iVar3;
        } while (iVar3 != 0 && bVar1);
      }
      else if (uVar5 == 0) {
        do {
          *(undefined *)local_1c = *(undefined *)puVar10;
          local_1c = (undefined2 *)((int)local_1c + iVar6 + 1);
          puVar10 = (undefined2 *)((int)puVar10 + iVar2 + 1);
          iVar3 = iVar7 + -1;
          bVar1 = 0 < iVar7;
          iVar7 = iVar3;
        } while (iVar3 != 0 && bVar1);
      }
      else {
        do {
          for (; uVar8 != 0; uVar8 = uVar8 - 1) {
            *local_1c = *puVar10;
            puVar10 = puVar10 + 1;
            local_1c = local_1c + 1;
          }
          *(undefined *)local_1c = *(undefined *)puVar10;
          local_1c = (undefined2 *)((int)local_1c + iVar6 + 1);
          puVar10 = (undefined2 *)((int)puVar10 + iVar2 + 1);
          iVar3 = iVar7 + -1;
          bVar1 = 0 < iVar7;
          uVar8 = uVar5;
          iVar7 = iVar3;
        } while (iVar3 != 0 && bVar1);
      }
    }
  }
  return;
}


// ================================================================================================
// sub_b6f84 @ 0xb6f84 [__cdecl]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_b6f84(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
              undefined4 param_5)

{
  if (dword_d30d0 != *(int *)(param_1 + 0x2c)) {
    *(undefined4 *)(param_1 + 8) = param_2;
    *(undefined4 *)(param_1 + 0x10) = param_3;
    *(undefined4 *)(param_1 + 0xc) = param_4;
    *(undefined4 *)(param_1 + 0x14) = param_5;
    *(undefined4 *)(param_1 + 0x18) = param_2;
    *(undefined4 *)(param_1 + 0x1c) = param_3;
    return;
  }
  *(undefined4 *)(param_1 + 8) = param_2;
  *(undefined4 *)(param_1 + 0x10) = param_3;
  *(undefined4 *)(param_1 + 0xc) = param_4;
  *(undefined4 *)(param_1 + 0x14) = param_5;
  dword_d30ac = param_2;
  _dword_d30b4 = param_3;
  dword_d30b0 = param_4;
  dword_d30b8 = param_5;
  *(undefined4 *)(param_1 + 0x18) = param_2;
  *(undefined4 *)(param_1 + 0x1c) = param_3;
  dword_d30bc = param_2;
  dword_d30c0 = param_3;
  return;
}


// ================================================================================================
// sub_b6ffc @ 0xb6ffc [__watcall]
// ================================================================================================

int __watcall sub_b6ffc(void)

{
  int in_stack_00000004;
  
  return (int)*(short *)(in_stack_00000004 + 4);
}


// ================================================================================================
// sub_b7005 @ 0xb7005 [__watcall]
// ================================================================================================

int __watcall sub_b7005(void)

{
  int in_stack_00000004;
  
  return (int)*(short *)(in_stack_00000004 + 6);
}


// ================================================================================================
// sub_b700e @ 0xb700e [__cdecl]
// ================================================================================================

char * sub_b700e(char *param_1)

{
  char cVar1;
  char *pcVar2;
  
  if (-1 < *param_1) {
    return (char *)((int)*(short *)(param_1 + 4) * (int)*(short *)(param_1 + 6) + 0x10);
  }
  pcVar2 = param_1 + 0xe;
  do {
    do {
      pcVar2 = pcVar2 + 2;
      cVar1 = *pcVar2;
      if (cVar1 == '\0') goto LAB_000b7045;
    } while (-1 < cVar1);
    do {
      pcVar2 = pcVar2 + (byte)-cVar1 + 1;
      cVar1 = *pcVar2;
    } while (cVar1 < '\0');
  } while (cVar1 != '\0');
LAB_000b7045:
  return pcVar2 + (1 - (int)param_1);
}


// ================================================================================================
// sub_b704c @ 0xb704c [__cdecl]
// ================================================================================================

void sub_b704c(int param_1)

{
                    /* WARNING: Could not recover jumptable at 0x000b7087. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(&DAT_000b708f + *(int *)(param_1 + 0x34) * 4))();
  return;
}


// ================================================================================================
// sub_b7218 @ 0xb7218 [__cdecl]
// ================================================================================================

void sub_b7218(byte *param_1,byte *param_2,int param_3)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  byte *pbVar6;
  byte *pbVar7;
  byte *pbVar8;
  
  pbVar6 = param_2;
  for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
    *(undefined4 *)pbVar6 = *(undefined4 *)param_1;
    param_1 = param_1 + 4;
    pbVar6 = pbVar6 + 4;
  }
  if (param_3 != 0) {
    *(int *)(pbVar6 + -8) = *(int *)(pbVar6 + -0xc) - *(int *)(pbVar6 + -8);
    iVar2 = *(int *)(pbVar6 + -0xc);
    pbVar8 = pbVar6 + iVar2 + -1;
    iVar5 = iVar2;
    while( true ) {
      while( true ) {
        bVar1 = *param_1;
        uVar3 = (uint)bVar1;
        if ((char)bVar1 < '\x01') break;
        bVar1 = param_1[1];
        do {
          *pbVar8 = bVar1;
          iVar5 = iVar5 + -1;
          if (iVar5 == 0) {
            pbVar6 = pbVar6 + iVar2;
            pbVar8 = pbVar6 + iVar2;
            iVar5 = iVar2;
          }
          pbVar8 = pbVar8 + -1;
          uVar3 = uVar3 - 1;
        } while (uVar3 != 0);
        param_1 = param_1 + 2;
      }
      if (-1 < (char)bVar1) break;
      uVar3 = (uint)(byte)-bVar1;
      pbVar7 = param_1 + 1;
      do {
        param_1 = pbVar7 + 1;
        *pbVar8 = *pbVar7;
        iVar5 = iVar5 + -1;
        if (iVar5 == 0) {
          pbVar6 = pbVar6 + iVar2;
          pbVar8 = pbVar6 + iVar2;
          iVar5 = iVar2;
        }
        pbVar8 = pbVar8 + -1;
        uVar3 = uVar3 - 1;
        pbVar7 = param_1;
      } while (uVar3 != 0);
    }
LAB_000b7277:
    *param_2 = *param_2 & 0x7f;
    return;
  }
  uVar3 = 0;
  do {
    bVar1 = (byte)uVar3 | *param_1;
    uVar3 = CONCAT31((int3)(uVar3 >> 8),bVar1);
    if (-1 < (char)bVar1) {
      pbVar8 = param_1;
      if (bVar1 == 0) goto LAB_000b7277;
      do {
        param_1 = pbVar8 + 2;
        bVar1 = pbVar8[1];
        for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
          *(uint *)pbVar6 = CONCAT31(CONCAT21(CONCAT11(bVar1,bVar1),bVar1),bVar1);
          pbVar6 = pbVar6 + 4;
        }
        for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
          *pbVar6 = bVar1;
          pbVar6 = pbVar6 + 1;
        }
        bVar1 = *param_1;
        uVar3 = (uint)bVar1;
        if (bVar1 == 0) goto LAB_000b7277;
        pbVar8 = param_1;
      } while (-1 < (char)bVar1);
    }
    for (uVar3 = CONCAT31((int3)(uVar3 >> 8),-(char)uVar3); param_1 = param_1 + 1, (uVar3 & 3) != 0;
        uVar3 = uVar3 - 1) {
      *pbVar6 = *param_1;
      pbVar6 = pbVar6 + 1;
    }
    for (uVar3 = uVar3 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
      *(undefined4 *)pbVar6 = *(undefined4 *)param_1;
      param_1 = param_1 + 4;
      pbVar6 = pbVar6 + 4;
    }
  } while( true );
}


// ================================================================================================
// sub_b72d4 @ 0xb72d4 [__cdecl]
// ================================================================================================

void sub_b72d4(undefined4 param_1,undefined4 param_2)

{
  dword_d86bc = param_1;
  dword_d86b8 = param_2;
  return;
}


// ================================================================================================
// sub_b72e9 @ 0xb72e9 [__cdecl]
// ================================================================================================

void sub_b72e9(int param_1,int param_2,int param_3)

{
  char cVar1;
  int *piVar2;
  char *pcVar3;
  
  param_2 = param_2 + dword_d86bc;
  pcVar3 = (char *)(param_1 + dword_d30d0);
  piVar2 = dword_d86b8;
  do {
    cVar1 = *(char *)(*piVar2 + param_2);
    if (cVar1 != -1) {
      *pcVar3 = cVar1;
    }
    piVar2 = piVar2 + 1;
    pcVar3 = pcVar3 + 1;
    param_3 = param_3 + -1;
  } while (param_3 != 0);
  return;
}


// ================================================================================================
// sub_b731e @ 0xb731e [__watcall]
// ================================================================================================

void __watcall sub_b731e(void)

{
  int *piVar1;
  undefined *puVar2;
  int in_stack_00000004;
  int in_stack_00000008;
  int in_stack_0000000c;
  
  in_stack_00000008 = in_stack_00000008 + dword_d86bc;
  puVar2 = (undefined *)(in_stack_00000004 + dword_d30d0);
  piVar1 = dword_d86b8;
  do {
    *puVar2 = *(undefined *)((int)&unk_d42e4 + (uint)*(byte *)(*piVar1 + in_stack_00000008));
    piVar1 = piVar1 + 1;
    puVar2 = puVar2 + 1;
    in_stack_0000000c = in_stack_0000000c + -1;
  } while (in_stack_0000000c != 0);
  return;
}


// ================================================================================================
// sub_b7357 @ 0xb7357 [__watcall]
// ================================================================================================

void __watcall sub_b7357(void)

{
  char cVar1;
  int *piVar2;
  char *pcVar3;
  int in_stack_00000004;
  int in_stack_00000008;
  int in_stack_0000000c;
  
  in_stack_00000008 = in_stack_00000008 + dword_d86bc;
  pcVar3 = (char *)(in_stack_00000004 + dword_d30d0);
  piVar2 = dword_d86b8;
  do {
    cVar1 = *(char *)((int)&unk_d42e4 + (uint)*(byte *)(*piVar2 + in_stack_00000008));
    if (cVar1 != -1) {
      *pcVar3 = cVar1;
    }
    piVar2 = piVar2 + 1;
    pcVar3 = pcVar3 + 1;
    in_stack_0000000c = in_stack_0000000c + -1;
  } while (in_stack_0000000c != 0);
  return;
}


// ================================================================================================
// sub_b7394 @ 0xb7394 [__watcall]
// ================================================================================================

void __watcall sub_b7394(void)

{
  byte bVar1;
  int *piVar2;
  byte *pbVar3;
  int in_stack_00000004;
  int in_stack_00000008;
  int in_stack_0000000c;
  
  in_stack_00000008 = in_stack_00000008 + dword_d86bc;
  pbVar3 = (byte *)(in_stack_00000004 + dword_d30d0);
  piVar2 = dword_d86b8;
  do {
    bVar1 = *(byte *)(*piVar2 + in_stack_00000008);
    if (bVar1 != 0xff) {
      if (bVar1 == 0xfe) {
        bVar1 = *(byte *)((int)&unk_d89e4 + (uint)*pbVar3);
      }
      *pbVar3 = bVar1;
    }
    piVar2 = piVar2 + 1;
    pbVar3 = pbVar3 + 1;
    in_stack_0000000c = in_stack_0000000c + -1;
  } while (in_stack_0000000c != 0);
  return;
}


// ================================================================================================
// sub_b73d7 @ 0xb73d7 [__watcall]
// ================================================================================================

void __watcall sub_b73d7(void)

{
  byte bVar1;
  int *piVar2;
  byte *pbVar3;
  int in_stack_00000004;
  int in_stack_00000008;
  int in_stack_0000000c;
  
  in_stack_00000008 = in_stack_00000008 + dword_d86bc;
  pbVar3 = (byte *)(in_stack_00000004 + dword_d30d0);
  piVar2 = dword_d86b8;
  do {
    bVar1 = *(byte *)((int)&unk_d42e4 + (uint)*(byte *)(*piVar2 + in_stack_00000008));
    if (bVar1 != 0xff) {
      if (bVar1 == 0xfe) {
        bVar1 = *(byte *)((int)&unk_d89e4 + (uint)*pbVar3);
      }
      *pbVar3 = bVar1;
    }
    piVar2 = piVar2 + 1;
    pbVar3 = pbVar3 + 1;
    in_stack_0000000c = in_stack_0000000c + -1;
  } while (in_stack_0000000c != 0);
  return;
}


// ================================================================================================
// sub_b7420 @ 0xb7420 [__cdecl]
// ================================================================================================

void sub_b7420(int param_1,int param_2,uint param_3)

{
  uint uVar1;
  int *piVar2;
  uint uVar3;
  undefined *puVar4;
  undefined2 *puVar5;
  
  piVar2 = dword_d86b8;
  param_2 = param_2 + dword_d86bc;
  puVar4 = (undefined *)(param_1 + dword_d30d0);
  if ((int)param_3 < 9) {
    do {
      *puVar4 = *(undefined *)(*piVar2 + param_2);
      piVar2 = piVar2 + 1;
      puVar4 = puVar4 + 1;
      param_3 = param_3 - 1;
    } while (param_3 != 0);
    return;
  }
  if (((uint)puVar4 & 1) == 0) {
    uVar3 = -(param_3 & 0xfffffffe) & 0x1e;
    uVar1 = (param_3 - 0x20) + uVar3;
    puVar5 = (undefined2 *)(puVar4 + -uVar3);
    piVar2 = dword_d86b8 + -uVar3;
    switch(uVar3) {
    case 2:
      goto switchD_000b74a3_caseD_2;
    case 4:
      goto switchD_000b74a3_caseD_4;
    case 6:
      goto switchD_000b74a3_caseD_6;
    case 8:
      goto switchD_000b74a3_caseD_8;
    case 10:
      goto switchD_000b74a3_caseD_a;
    case 0xc:
      goto switchD_000b74a3_caseD_c;
    case 0xe:
      goto switchD_000b74a3_caseD_e;
    case 0x10:
      goto switchD_000b74a3_caseD_10;
    case 0x12:
      goto switchD_000b74a3_caseD_12;
    case 0x14:
      goto switchD_000b74a3_caseD_14;
    case 0x16:
      goto switchD_000b74a3_caseD_16;
    case 0x18:
      goto switchD_000b74a3_caseD_18;
    case 0x1a:
      goto switchD_000b74a3_caseD_1a;
    case 0x1c:
      goto switchD_000b74a3_caseD_1c;
    case 0x1e:
      goto switchD_000b74a3_caseD_1e;
    }
  }
  else {
    *puVar4 = *(undefined *)(*dword_d86b8 + param_2);
    uVar3 = -(param_3 - 1 & 0xfffffffe) & 0x1e;
    uVar1 = (param_3 - 0x21) + uVar3;
    puVar5 = (undefined2 *)(puVar4 + (1 - uVar3));
    piVar2 = piVar2 + (1 - uVar3);
    switch(uVar3) {
    case 2:
      goto switchD_000b74a3_caseD_2;
    case 4:
      goto switchD_000b74a3_caseD_4;
    case 6:
      goto switchD_000b74a3_caseD_6;
    case 8:
      goto switchD_000b74a3_caseD_8;
    case 10:
      goto switchD_000b74a3_caseD_a;
    case 0xc:
      goto switchD_000b74a3_caseD_c;
    case 0xe:
      goto switchD_000b74a3_caseD_e;
    case 0x10:
      goto switchD_000b74a3_caseD_10;
    case 0x12:
      goto switchD_000b74a3_caseD_12;
    case 0x14:
      goto switchD_000b74a3_caseD_14;
    case 0x16:
      goto switchD_000b74a3_caseD_16;
    case 0x18:
      goto switchD_000b74a3_caseD_18;
    case 0x1a:
      goto switchD_000b74a3_caseD_1a;
    case 0x1c:
      goto switchD_000b74a3_caseD_1c;
    case 0x1e:
      goto switchD_000b74a3_caseD_1e;
    }
  }
  while( true ) {
    *puVar5 = CONCAT11(*(undefined *)(piVar2[1] + param_2),*(undefined *)(*piVar2 + param_2));
switchD_000b74a3_caseD_2:
    puVar5[1] = CONCAT11(*(undefined *)(piVar2[3] + param_2),*(undefined *)(piVar2[2] + param_2));
switchD_000b74a3_caseD_4:
    puVar5[2] = CONCAT11(*(undefined *)(piVar2[5] + param_2),*(undefined *)(piVar2[4] + param_2));
switchD_000b74a3_caseD_6:
    puVar5[3] = CONCAT11(*(undefined *)(piVar2[7] + param_2),*(undefined *)(piVar2[6] + param_2));
switchD_000b74a3_caseD_8:
    puVar5[4] = CONCAT11(*(undefined *)(piVar2[9] + param_2),*(undefined *)(piVar2[8] + param_2));
switchD_000b74a3_caseD_a:
    puVar5[5] = CONCAT11(*(undefined *)(piVar2[0xb] + param_2),*(undefined *)(piVar2[10] + param_2))
    ;
switchD_000b74a3_caseD_c:
    puVar5[6] = CONCAT11(*(undefined *)(piVar2[0xd] + param_2),*(undefined *)(piVar2[0xc] + param_2)
                        );
switchD_000b74a3_caseD_e:
    puVar5[7] = CONCAT11(*(undefined *)(piVar2[0xf] + param_2),*(undefined *)(piVar2[0xe] + param_2)
                        );
switchD_000b74a3_caseD_10:
    puVar5[8] = CONCAT11(*(undefined *)(piVar2[0x11] + param_2),
                         *(undefined *)(piVar2[0x10] + param_2));
switchD_000b74a3_caseD_12:
    puVar5[9] = CONCAT11(*(undefined *)(piVar2[0x13] + param_2),
                         *(undefined *)(piVar2[0x12] + param_2));
switchD_000b74a3_caseD_14:
    puVar5[10] = CONCAT11(*(undefined *)(piVar2[0x15] + param_2),
                          *(undefined *)(piVar2[0x14] + param_2));
switchD_000b74a3_caseD_16:
    puVar5[0xb] = CONCAT11(*(undefined *)(piVar2[0x17] + param_2),
                           *(undefined *)(piVar2[0x16] + param_2));
switchD_000b74a3_caseD_18:
    puVar5[0xc] = CONCAT11(*(undefined *)(piVar2[0x19] + param_2),
                           *(undefined *)(piVar2[0x18] + param_2));
switchD_000b74a3_caseD_1a:
    puVar5[0xd] = CONCAT11(*(undefined *)(piVar2[0x1b] + param_2),
                           *(undefined *)(piVar2[0x1a] + param_2));
switchD_000b74a3_caseD_1c:
    puVar5[0xe] = CONCAT11(*(undefined *)(piVar2[0x1d] + param_2),
                           *(undefined *)(piVar2[0x1c] + param_2));
switchD_000b74a3_caseD_1e:
    puVar5[0xf] = CONCAT11(*(undefined *)(piVar2[0x1f] + param_2),
                           *(undefined *)(piVar2[0x1e] + param_2));
    uVar1 = uVar1 - 0x20;
    if ((int)uVar1 < 0) break;
    puVar5 = puVar5 + 0x10;
    piVar2 = piVar2 + 0x20;
  }
  if ((uVar1 & 1) == 0) {
    return;
  }
  *(undefined *)(puVar5 + 0x10) = *(undefined *)(piVar2[0x20] + param_2);
  return;
}


// ================================================================================================
// sub_b7614 @ 0xb7614 [__watcall]
// ================================================================================================

void __watcall sub_b7614(void)

{
  byte *pbVar1;
  byte bVar2;
  bool bVar3;
  byte *pbVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  byte *pbVar11;
  int in_stack_00000004;
  short in_stack_00000008;
  short in_stack_0000000c;
  byte *pbStack_1c;
  int iStack_18;
  
  iVar5 = (int)(short)(in_stack_00000008 - *(short *)(in_stack_00000004 + 8));
  iVar6 = (int)(short)(in_stack_0000000c - *(short *)(in_stack_00000004 + 10));
  iVar9 = (int)*(short *)(in_stack_00000004 + 6);
  pbStack_1c = (byte *)(in_stack_00000004 + 0x10);
  if (iVar6 < dword_d30b0) {
    iVar7 = (iVar6 + iVar9) - dword_d30b0;
    if (iVar7 == 0 || iVar6 + iVar9 < dword_d30b0) {
      return;
    }
    pbStack_1c = pbStack_1c + (iVar9 - iVar7) * (int)*(short *)(in_stack_00000004 + 4);
    iVar9 = (dword_d30b0 + iVar7) - dword_d30b8;
    iStack_18 = iVar7;
    iVar6 = dword_d30b0;
    if ((iVar9 != 0 && dword_d30b8 <= dword_d30b0 + iVar7) &&
       (iStack_18 = iVar7 - iVar9, iStack_18 == 0 || iVar7 < iVar9)) {
      return;
    }
  }
  else {
    iVar7 = (iVar6 + iVar9) - dword_d30b8;
    iStack_18 = iVar9;
    if ((iVar7 != 0 && dword_d30b8 <= iVar6 + iVar9) &&
       (iStack_18 = iVar9 - iVar7, iVar9 - iVar7 == 0 || iVar9 < iVar7)) {
      return;
    }
  }
  iVar9 = (int)*(short *)(in_stack_00000004 + 4);
  if (iVar5 < dword_d30bc) {
    iVar7 = (iVar5 + iVar9) - dword_d30bc;
    if (iVar7 != 0 && dword_d30bc <= iVar5 + iVar9) {
      pbStack_1c = pbStack_1c + (iVar9 - iVar7);
      iVar5 = dword_d30c0 - dword_d30bc;
      if (iVar5 != 0 && dword_d30bc <= dword_d30c0) {
        if (iVar5 <= iVar7) {
          iVar7 = iVar5;
        }
        iVar10 = iVar9 - iVar7;
        iVar5 = dword_d30bc;
        goto LAB_000b7717;
      }
    }
  }
  else {
    iVar8 = (iVar5 + iVar9) - dword_d30c0;
    iVar7 = iVar9;
    iVar10 = 0;
    if ((iVar5 + iVar9 < dword_d30c0) ||
       (iVar7 = iVar9 - iVar8, iVar10 = iVar8, iVar7 != 0 && iVar8 <= iVar9)) {
LAB_000b7717:
      if (0 < iVar7) {
        iVar8 = dword_d30c4 - iVar7;
        iVar9 = iVar7;
        pbVar4 = (byte *)(*(int *)(off_d30cc + iVar6 * 4) + dword_d30d0 + iVar5);
        do {
          do {
            pbVar11 = pbVar4;
            pbVar1 = pbStack_1c + 1;
            bVar2 = *pbStack_1c;
            if (bVar2 != 0xff) {
              if (bVar2 == 0xfe) {
                *pbVar11 = *(byte *)((int)&unk_d89e4 + (uint)*pbVar11);
              }
              else {
                *pbVar11 = bVar2;
              }
            }
            iVar9 = iVar9 + -1;
            pbStack_1c = pbVar1;
            pbVar4 = pbVar11 + 1;
          } while (iVar9 != 0);
          pbStack_1c = pbVar1 + iVar10;
          iVar5 = iStack_18 + -1;
          bVar3 = 0 < iStack_18;
          iVar9 = iVar7;
          pbVar4 = pbVar11 + iVar8 + 1;
          iStack_18 = iVar5;
        } while (iVar5 != 0 && bVar3);
      }
      return;
    }
  }
  return;
}


// ================================================================================================
// sub_b763b @ 0xb763b [__cdecl]
// ================================================================================================

void sub_b763b(int param_1,int param_2,int param_3)

{
  int iVar1;
  byte *pbVar2;
  byte bVar3;
  bool bVar4;
  byte *pbVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  byte *pbVar10;
  byte *pbStack_1c;
  int iStack_18;
  
  iVar8 = (int)*(short *)(param_1 + 6);
  pbStack_1c = (byte *)(param_1 + 0x10);
  if (param_3 < dword_d30b0) {
    iVar6 = (param_3 + iVar8) - dword_d30b0;
    if (iVar6 == 0 || param_3 + iVar8 < dword_d30b0) {
      return;
    }
    pbStack_1c = pbStack_1c + (iVar8 - iVar6) * (int)*(short *)(param_1 + 4);
    iVar8 = (dword_d30b0 + iVar6) - dword_d30b8;
    iStack_18 = iVar6;
    param_3 = dword_d30b0;
    if ((iVar8 != 0 && dword_d30b8 <= dword_d30b0 + iVar6) &&
       (iStack_18 = iVar6 - iVar8, iStack_18 == 0 || iVar6 < iVar8)) {
      return;
    }
  }
  else {
    iVar6 = (param_3 + iVar8) - dword_d30b8;
    iStack_18 = iVar8;
    if ((iVar6 != 0 && dword_d30b8 <= param_3 + iVar8) &&
       (iStack_18 = iVar8 - iVar6, iVar8 - iVar6 == 0 || iVar8 < iVar6)) {
      return;
    }
  }
  iVar8 = (int)*(short *)(param_1 + 4);
  if (param_2 < dword_d30bc) {
    iVar6 = (param_2 + iVar8) - dword_d30bc;
    if (iVar6 != 0 && dword_d30bc <= param_2 + iVar8) {
      pbStack_1c = pbStack_1c + (iVar8 - iVar6);
      iVar9 = dword_d30c0 - dword_d30bc;
      if (iVar9 != 0 && dword_d30bc <= dword_d30c0) {
        if (iVar9 <= iVar6) {
          iVar6 = iVar9;
        }
        iVar9 = iVar8 - iVar6;
        param_2 = dword_d30bc;
        goto LAB_000b7717;
      }
    }
  }
  else {
    iVar7 = (param_2 + iVar8) - dword_d30c0;
    iVar6 = iVar8;
    iVar9 = 0;
    if ((param_2 + iVar8 < dword_d30c0) ||
       (iVar6 = iVar8 - iVar7, iVar9 = iVar7, iVar6 != 0 && iVar7 <= iVar8)) {
LAB_000b7717:
      if (0 < iVar6) {
        iVar7 = dword_d30c4 - iVar6;
        iVar8 = iVar6;
        pbVar5 = (byte *)(*(int *)(off_d30cc + param_3 * 4) + dword_d30d0 + param_2);
        do {
          do {
            pbVar10 = pbVar5;
            pbVar2 = pbStack_1c + 1;
            bVar3 = *pbStack_1c;
            if (bVar3 != 0xff) {
              if (bVar3 == 0xfe) {
                *pbVar10 = *(byte *)((int)&unk_d89e4 + (uint)*pbVar10);
              }
              else {
                *pbVar10 = bVar3;
              }
            }
            iVar8 = iVar8 + -1;
            pbStack_1c = pbVar2;
            pbVar5 = pbVar10 + 1;
          } while (iVar8 != 0);
          pbStack_1c = pbVar2 + iVar9;
          iVar1 = iStack_18 + -1;
          bVar4 = 0 < iStack_18;
          iVar8 = iVar6;
          pbVar5 = pbVar10 + iVar7 + 1;
          iStack_18 = iVar1;
        } while (iVar1 != 0 && bVar4);
      }
      return;
    }
  }
  return;
}


// ================================================================================================
// sub_b7654 @ 0xb7654 [__watcall]
// ================================================================================================

void __watcall sub_b7654(void)

{
  byte *pbVar1;
  byte bVar2;
  bool bVar3;
  byte *pbVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  byte *pbVar11;
  int in_stack_00000004;
  byte *local_1c;
  int local_18;
  
  iVar5 = (int)*(short *)(in_stack_00000004 + 0xc);
  iVar6 = (int)*(short *)(in_stack_00000004 + 0xe);
  iVar9 = (int)*(short *)(in_stack_00000004 + 6);
  local_1c = (byte *)(in_stack_00000004 + 0x10);
  if (iVar6 < dword_d30b0) {
    iVar7 = (iVar6 + iVar9) - dword_d30b0;
    if (iVar7 == 0 || iVar6 + iVar9 < dword_d30b0) {
      return;
    }
    local_1c = local_1c + (iVar9 - iVar7) * (int)*(short *)(in_stack_00000004 + 4);
    iVar9 = (dword_d30b0 + iVar7) - dword_d30b8;
    local_18 = iVar7;
    iVar6 = dword_d30b0;
    if ((iVar9 != 0 && dword_d30b8 <= dword_d30b0 + iVar7) &&
       (local_18 = iVar7 - iVar9, local_18 == 0 || iVar7 < iVar9)) {
      return;
    }
  }
  else {
    iVar7 = (iVar6 + iVar9) - dword_d30b8;
    local_18 = iVar9;
    if ((iVar7 != 0 && dword_d30b8 <= iVar6 + iVar9) &&
       (local_18 = iVar9 - iVar7, iVar9 - iVar7 == 0 || iVar9 < iVar7)) {
      return;
    }
  }
  iVar9 = (int)*(short *)(in_stack_00000004 + 4);
  if (iVar5 < dword_d30bc) {
    iVar7 = (iVar5 + iVar9) - dword_d30bc;
    if (iVar7 != 0 && dword_d30bc <= iVar5 + iVar9) {
      local_1c = local_1c + (iVar9 - iVar7);
      iVar5 = dword_d30c0 - dword_d30bc;
      if (iVar5 != 0 && dword_d30bc <= dword_d30c0) {
        if (iVar5 <= iVar7) {
          iVar7 = iVar5;
        }
        iVar10 = iVar9 - iVar7;
        iVar5 = dword_d30bc;
        goto LAB_000b7717;
      }
    }
  }
  else {
    iVar8 = (iVar5 + iVar9) - dword_d30c0;
    iVar7 = iVar9;
    iVar10 = 0;
    if ((iVar5 + iVar9 < dword_d30c0) ||
       (iVar7 = iVar9 - iVar8, iVar10 = iVar8, iVar7 != 0 && iVar8 <= iVar9)) {
LAB_000b7717:
      if (0 < iVar7) {
        iVar8 = dword_d30c4 - iVar7;
        iVar9 = iVar7;
        pbVar4 = (byte *)(*(int *)(off_d30cc + iVar6 * 4) + dword_d30d0 + iVar5);
        do {
          do {
            pbVar11 = pbVar4;
            pbVar1 = local_1c + 1;
            bVar2 = *local_1c;
            if (bVar2 != 0xff) {
              if (bVar2 == 0xfe) {
                *pbVar11 = *(byte *)((int)&unk_d89e4 + (uint)*pbVar11);
              }
              else {
                *pbVar11 = bVar2;
              }
            }
            iVar9 = iVar9 + -1;
            local_1c = pbVar1;
            pbVar4 = pbVar11 + 1;
          } while (iVar9 != 0);
          local_1c = pbVar1 + iVar10;
          iVar5 = local_18 + -1;
          bVar3 = 0 < local_18;
          iVar9 = iVar7;
          pbVar4 = pbVar11 + iVar8 + 1;
          local_18 = iVar5;
        } while (iVar5 != 0 && bVar3);
      }
      return;
    }
  }
  return;
}


// ================================================================================================
// sub_b7778 @ 0xb7778 [__watcall]
// ================================================================================================

void __watcall sub_b7778(void)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *in_stack_00000004;
  
  puVar2 = &unk_d89e4;
  for (iVar1 = 0x40; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = *in_stack_00000004;
    in_stack_00000004 = in_stack_00000004 + 1;
    puVar2 = puVar2 + 1;
  }
  return;
}


// ================================================================================================
// sub_b7790 @ 0xb7790 [__watcall]
// ================================================================================================

void __watcall sub_b7790(void)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *in_stack_00000004;
  
  puVar2 = &unk_d89e4;
  for (iVar1 = 0x40; iVar1 != 0; iVar1 = iVar1 + -1) {
    *in_stack_00000004 = *puVar2;
    puVar2 = puVar2 + 1;
    in_stack_00000004 = in_stack_00000004 + 1;
  }
  return;
}


// ================================================================================================
// sub_b77a8 @ 0xb77a8 [__watcall]
// ================================================================================================

void __watcall sub_b77a8(void)

{
  uint uVar1;
  undefined4 *puVar2;
  int in_stack_00000004;
  uint in_stack_00000008;
  undefined4 *in_stack_0000000c;
  
  puVar2 = (undefined4 *)((int)&unk_d89e4 + in_stack_00000004);
  for (uVar1 = in_stack_00000008 >> 2; uVar1 != 0; uVar1 = uVar1 - 1) {
    *puVar2 = *in_stack_0000000c;
    in_stack_0000000c = in_stack_0000000c + 1;
    puVar2 = puVar2 + 1;
  }
  for (in_stack_00000008 = in_stack_00000008 & 3; in_stack_00000008 != 0;
      in_stack_00000008 = in_stack_00000008 - 1) {
    *(undefined *)puVar2 = *(undefined *)in_stack_0000000c;
    in_stack_0000000c = (undefined4 *)((int)in_stack_0000000c + 1);
    puVar2 = (undefined4 *)((int)puVar2 + 1);
  }
  return;
}


// ================================================================================================
// sub_b77d0 @ 0xb77d0 [__watcall]
// ================================================================================================

void __watcall sub_b77d0(void)

{
  int iVar1;
  byte *pbVar2;
  byte bVar3;
  bool bVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  byte *pbVar8;
  byte *pbVar9;
  int in_stack_00000004;
  short in_stack_00000008;
  short in_stack_0000000c;
  int iStack_14;
  
  iVar5 = (int)*(short *)(in_stack_00000004 + 4);
  iVar7 = dword_d30c4 - iVar5;
  iVar6 = iVar5;
  pbVar8 = (byte *)(in_stack_00000004 + 0x10);
  pbVar2 = (byte *)(*(int *)(off_d30cc +
                            (short)(in_stack_0000000c - *(short *)(in_stack_00000004 + 10)) * 4) +
                    (int)(short)(in_stack_00000008 - *(short *)(in_stack_00000004 + 8)) +
                   dword_d30d0);
  iStack_14 = (int)*(short *)(in_stack_00000004 + 6);
  do {
    do {
      pbVar9 = pbVar2;
      pbVar2 = pbVar8 + 1;
      bVar3 = *pbVar8;
      if (bVar3 != 0xff) {
        if (bVar3 == 0xfe) {
          *pbVar9 = *(byte *)((int)&unk_d89e4 + (uint)*pbVar9);
        }
        else {
          *pbVar9 = bVar3;
        }
      }
      iVar6 = iVar6 + -1;
      pbVar8 = pbVar2;
      pbVar2 = pbVar9 + 1;
    } while (iVar6 != 0);
    iVar1 = iStack_14 + -1;
    bVar4 = 0 < iStack_14;
    iVar6 = iVar5;
    pbVar2 = pbVar9 + iVar7 + 1;
    iStack_14 = iVar1;
  } while (iVar1 != 0 && bVar4);
  return;
}


// ================================================================================================
// sub_b77f4 @ 0xb77f4 [__cdecl]
// ================================================================================================

void sub_b77f4(int param_1,int param_2,int param_3)

{
  int iVar1;
  byte *pbVar2;
  byte bVar3;
  bool bVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  byte *pbVar8;
  byte *pbVar9;
  int iStack_14;
  
  iVar5 = (int)*(short *)(param_1 + 4);
  iVar7 = dword_d30c4 - iVar5;
  iVar6 = iVar5;
  pbVar8 = (byte *)(param_1 + 0x10);
  pbVar2 = (byte *)(*(int *)(off_d30cc + param_3 * 4) + param_2 + dword_d30d0);
  iStack_14 = (int)*(short *)(param_1 + 6);
  do {
    do {
      pbVar9 = pbVar2;
      pbVar2 = pbVar8 + 1;
      bVar3 = *pbVar8;
      if (bVar3 != 0xff) {
        if (bVar3 == 0xfe) {
          *pbVar9 = *(byte *)((int)&unk_d89e4 + (uint)*pbVar9);
        }
        else {
          *pbVar9 = bVar3;
        }
      }
      iVar6 = iVar6 + -1;
      pbVar8 = pbVar2;
      pbVar2 = pbVar9 + 1;
    } while (iVar6 != 0);
    iVar1 = iStack_14 + -1;
    bVar4 = 0 < iStack_14;
    iVar6 = iVar5;
    pbVar2 = pbVar9 + iVar7 + 1;
    iStack_14 = iVar1;
  } while (iVar1 != 0 && bVar4);
  return;
}


// ================================================================================================
// sub_b780e @ 0xb780e [__watcall]
// ================================================================================================

void __watcall sub_b780e(void)

{
  int iVar1;
  byte *pbVar2;
  byte bVar3;
  bool bVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  byte *pbVar8;
  byte *pbVar9;
  int in_stack_00000004;
  int local_14;
  
  iVar5 = (int)*(short *)(in_stack_00000004 + 4);
  iVar7 = dword_d30c4 - iVar5;
  iVar6 = iVar5;
  pbVar8 = (byte *)(in_stack_00000004 + 0x10);
  pbVar2 = (byte *)(*(int *)(off_d30cc + *(short *)(in_stack_00000004 + 0xe) * 4) +
                    (int)*(short *)(in_stack_00000004 + 0xc) + dword_d30d0);
  local_14 = (int)*(short *)(in_stack_00000004 + 6);
  do {
    do {
      pbVar9 = pbVar2;
      pbVar2 = pbVar8 + 1;
      bVar3 = *pbVar8;
      if (bVar3 != 0xff) {
        if (bVar3 == 0xfe) {
          *pbVar9 = *(byte *)((int)&unk_d89e4 + (uint)*pbVar9);
        }
        else {
          *pbVar9 = bVar3;
        }
      }
      iVar6 = iVar6 + -1;
      pbVar8 = pbVar2;
      pbVar2 = pbVar9 + 1;
    } while (iVar6 != 0);
    iVar1 = local_14 + -1;
    bVar4 = 0 < local_14;
    iVar6 = iVar5;
    pbVar2 = pbVar9 + iVar7 + 1;
    local_14 = iVar1;
  } while (iVar1 != 0 && bVar4);
  return;
}


