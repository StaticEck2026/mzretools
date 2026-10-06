// Decompiled by Ghidra from hockey.elf (via ledisasm ELF export)
// This is machine generated pseudo-C meant as a reference for porting, it does not compile as is.
#include "prototypes.h"

// ================================================================================================
// sub_938c8 @ 0x938c8 [__watcall]
// ================================================================================================

void __watcall sub_938c8(void)

{
  int iVar1;
  
  if (1 < dword_d4534) {
    iVar1 = 0;
    do {
      *(undefined4 *)(dword_d453c + iVar1) = 0;
      iVar1 = iVar1 + 4;
    } while (iVar1 < 4000);
  }
  return;
}


// ================================================================================================
// sub_938f4 @ 0x938f4 [__cdecl]
// ================================================================================================

void sub_938f4(int param_1)

{
  if ((-1 < param_1) && (param_1 < 0x19)) {
    byte_d4544 = (undefined)param_1;
  }
  return;
}


// ================================================================================================
// sub_93908 @ 0x93908 [__cdecl]
// ================================================================================================

void sub_93908(undefined param_1)

{
  byte_d4545 = param_1;
  return;
}


// ================================================================================================
// sub_93914 @ 0x93914 [__cdecl]
// ================================================================================================

void sub_93914(int param_1)

{
  if (0 < param_1) {
    byte_d4546 = (undefined)param_1;
  }
  return;
}


// ================================================================================================
// sub_93924 @ 0x93924 [__cdecl]
// ================================================================================================

void sub_93924(int param_1)

{
  dword_d453c = param_1 * 0x8000 + 0xb0000;
  return;
}


// ================================================================================================
// debug_openlog @ 0x93938 [__watcall]
// ================================================================================================

void __watcall debug_openlog(char *param_1)

{
  char cVar1;
  short sVar2;
  int iVar3;
  char *pcVar4;
  char *pcVar5;
  char *pcVar6;
  char local_c4 [136];
  undefined local_3c [20];
  undefined local_28 [20];
  
  pcVar5 = local_c4;
  if (dword_d4548 == (FILE *)0x0) {
    do {
      cVar1 = *param_1;
      *pcVar5 = cVar1;
      if (cVar1 == '\0') break;
      cVar1 = param_1[1];
      param_1 = param_1 + 2;
      pcVar5[1] = cVar1;
      pcVar5 = pcVar5 + 2;
    } while (cVar1 != '\0');
    iVar3 = -1;
    pcVar5 = local_c4;
    do {
      if (iVar3 == 0) break;
      iVar3 = iVar3 + -1;
      cVar1 = *pcVar5;
      pcVar5 = pcVar5 + 1;
    } while (cVar1 != '\0');
    sVar2 = ~(ushort)iVar3 - 1;
    if (0 < sVar2) {
      if ((local_c4[sVar2 + -1] != '\\') && (local_c4[sVar2 + -1] != ':')) {
        local_c4[sVar2] = '\\';
        local_c4[sVar2 + 1] = '\0';
      }
    }
    pcVar4 = &aDBUGTXT;
    iVar3 = -1;
    pcVar5 = local_c4;
    do {
      pcVar6 = pcVar5;
      if (iVar3 == 0) break;
      iVar3 = iVar3 + -1;
      pcVar6 = pcVar5 + 1;
      cVar1 = *pcVar5;
      pcVar5 = pcVar6;
    } while (cVar1 != '\0');
    pcVar6 = pcVar6 + -1;
    do {
      cVar1 = *pcVar4;
      *pcVar6 = cVar1;
      if (cVar1 == '\0') break;
      cVar1 = pcVar4[1];
      pcVar4 = pcVar4 + 2;
      pcVar6[1] = cVar1;
      pcVar6 = pcVar6 + 2;
    } while (cVar1 != '\0');
    sub_93b34(local_c4);
    dword_d4548 = fopen(local_c4,(char *)&aWt_c4040);
    if (dword_d4548 == (FILE *)0x0) {
      fclose((FILE *)0x0);
    }
    else {
      sub_93bd4(local_3c,local_28);
      sub_93aa4(s_FILE___s_000c4043 + 1,local_c4);
      sub_93aa4(s_DATE___s_000c404e + 2,local_3c);
      sub_93aa4(s_mTIME___s_000c405a + 2,local_28);
    }
  }
  return;
}


// ================================================================================================
// sub_93a40 @ 0x93a40 [__watcall]
// ================================================================================================

void __watcall sub_93a40(void)

{
  undefined auStack_34 [20];
  undefined local_20 [20];
  
  if (dword_d4548 != (FILE *)0x0) {
    sub_93bd4(local_20,auStack_34);
    sub_93aa4(s_V_CLOSED_000c4067 + 1);
    sub_93aa4(s_DATE___s_000c404e + 2,local_20);
    sub_93aa4(s_i__TIME___s_000c4071 + 3,auStack_34);
    fclose(dword_d4548);
    dword_d4548 = (FILE *)0x0;
  }
  return;
}


// ================================================================================================
// sub_93aa4 @ 0x93aa4 [__cdecl]
// ================================================================================================

void sub_93aa4(char *param_1)

{
  undefined *local_4;
  
  if ((1 < dword_d4534) && (dword_d4548 != (FILE *)0x0)) {
    local_4 = &stack0x00000008;
    sub_9c58c(dword_d4548,param_1,&local_4);
  }
  return;
}


// ================================================================================================
// sub_93ad8 @ 0x93ad8 [__watcall]
// ================================================================================================

void __watcall sub_93ad8(void)

{
  char *in_stack_00000004;
  char acStack_104 [256];
  undefined *local_4;
  
  if (1 < dword_d4534) {
    local_4 = &stack0x00000008;
    vsprintf(acStack_104,in_stack_00000004,&local_4);
    local_4 = (undefined *)0x0;
    if (dword_d4548 != 0) {
      sub_91e72(acStack_104,dword_d4548);
    }
    sub_936c0();
  }
  return;
}


// ================================================================================================
// sub_93b34 @ 0x93b34 [__watcall]
// ================================================================================================

undefined8 __watcall sub_93b34(char *param_1,undefined4 unaff_EDX)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  char *pcVar4;
  int iVar5;
  int iVar6;
  
  iVar6 = 0;
  cVar1 = *param_1;
  pcVar4 = param_1;
  while ((cVar1 != '?' && (*pcVar4 != '\0'))) {
    pcVar4 = pcVar4 + 1;
    iVar6 = iVar6 + 1;
    cVar1 = *pcVar4;
  }
  pcVar4 = param_1 + iVar6;
  if ((*pcVar4 == '\0') || (pcVar4[1] != '?')) {
    uVar2 = 0;
  }
  else {
    iVar5 = 0;
    do {
      *pcVar4 = (char)((longlong)iVar5 / 10) + '0';
      pcVar4[1] = (char)((longlong)iVar5 % 10) + '0';
      iVar3 = sub_b3cc8(param_1);
      if (iVar3 == 0) break;
      iVar5 = iVar5 + 1;
    } while (iVar5 < 100);
    if (99 < iVar5) {
      param_1 = param_1 + iVar6;
      param_1[1] = 'x';
      *param_1 = param_1[1];
      return CONCAT44(unaff_EDX,2);
    }
    uVar2 = 1;
  }
  return CONCAT44(unaff_EDX,uVar2);
}


// ================================================================================================
// sub_93bd4 @ 0x93bd4 [__watcall]
// ================================================================================================

void __watcall sub_93bd4(char *param_1,undefined4 unaff_EDX)

{
  char *__s;
  byte local_18;
  byte local_17;
  ushort local_16;
  byte local_10;
  byte local_f;
  byte local_e;
  
  sub_8eaec(&local_18,unaff_EDX,param_1,unaff_EDX);
  _dos_gettime(&local_10);
  sprintf(param_1,a02d3s02d,(uint)local_18,(&dword_d4548)[local_17],(uint)local_16 % 100);
  sprintf(__s,a2d02d02d,(uint)local_10,(uint)local_f,(uint)local_e);
  return;
}


// ================================================================================================
// sub_93c88 @ 0x93c88 [__watcall]
// ================================================================================================

void __watcall
sub_93c88(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  undefined4 uVar1;
  
  uVar1 = sub_b40bf();
  sub_9c594(uVar1,unaff_EDX,unaff_ECX,unaff_EBX);
  return;
}


// ================================================================================================
// sub_93ca0 @ 0x93ca0 [__watcall]
// ================================================================================================

void __watcall
sub_93ca0(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  clearclip(param_1,unaff_EDX,unaff_ECX,unaff_EBX);
  sub_9c5a8();
  return;
}


// ================================================================================================
// sub_93cb8 @ 0x93cb8 [__watcall]
// ================================================================================================

void __watcall sub_93cb8(void)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined8 uVar7;
  undefined auStack_dc [96];
  undefined local_7c [64];
  char acStack_3c [12];
  undefined uStack_30;
  uint local_2c;
  int local_28;
  uint local_24;
  int local_20;
  undefined local_1c;
  
  local_24 = dword_d4594;
  sub_b3a88(auStack_dc);
  getfontstate(local_7c);
  setfont(&unk_d45d8);
  local_1c = byte_d4544;
  sub_938f4(0);
  if (dword_d3024 == 0) {
    local_24 = 1;
  }
  dword_d457c = sub_9c5b0(0);
  dword_d4580 = sub_9c5b0(0xfcfcfc);
  dword_d4584 = sub_9c5b0(0xfcfc54);
  dword_d4588 = sub_9c5b0(0x80a8);
  dword_d458c = sub_9c5b0(0xa80000);
  local_2c = (uint)(local_24 == 0);
  local_20 = 0;
  iVar4 = dword_d459c;
  iVar5 = dword_d45a0;
  do {
    if ((dword_d4594 != local_24) &&
       (dword_d4594 = local_24, dword_d459c = iVar4, dword_d45a0 = iVar5, local_2c == 0)) {
      local_2c = (uint)(local_24 == 0);
    }
    uVar1 = sub_940f4();
    local_28 = sub_94188(iVar5,iVar4,uVar1);
    uVar7 = CONCAT44(iVar4 + 0x14,local_28);
    if (local_28 < iVar4 + 0x14) {
      uVar7 = CONCAT44(local_28,local_28);
    }
    do {
      uVar7 = sub_93c88((int)uVar7,(int)((ulonglong)uVar7 >> 0x20));
      iVar3 = (int)((ulonglong)uVar7 >> 0x20);
      iVar2 = (int)uVar7;
    } while (iVar2 == 0);
    iVar6 = iVar5;
    if (((iVar2 == 0x4900) && (iVar6 = iVar4, iVar5 == iVar4)) && (0 < iVar4)) {
      iVar4 = iVar4 + -0x15;
      iVar6 = iVar4;
    }
    iVar5 = iVar6;
    if (((iVar2 == 0x5100) && (iVar5 = iVar3, iVar6 == iVar3)) && (iVar5 = iVar6, iVar3 < local_28))
    {
      iVar4 = iVar4 + 0x15;
      iVar5 = iVar3 + 0x15;
    }
    if (((iVar2 == 0x4800) && (0 < iVar5)) && (iVar5 = iVar5 + -1, iVar5 < iVar4)) {
      iVar4 = iVar4 + -1;
    }
    if (((iVar2 == 0x5000) && (iVar5 < local_28)) && (iVar5 = iVar5 + 1, iVar3 < iVar5)) {
      iVar4 = iVar4 + 1;
    }
    iVar6 = iVar5;
    if ((iVar2 == 0x4700) && (iVar6 = iVar4, iVar5 == iVar4)) {
      iVar4 = 0;
      iVar6 = iVar4;
    }
    iVar5 = iVar6;
    if (((iVar2 == 0x4f00) && (iVar6 != local_28)) && (iVar5 = iVar3, iVar6 == iVar3)) {
      iVar4 = local_28 + -0x14;
      iVar5 = local_28;
    }
    if (iVar2 == 0x1b) {
      local_20 = 1;
    }
    if (iVar2 == 0xd) {
      sub_94b6c(dword_ede68,dword_ede84,local_24);
    }
    if (iVar2 == 0x43) {
      setdefaultscreen();
      sub_93ca0(dword_d457c);
    }
    if (iVar2 == 0x46) {
      dword_edab4 = 0;
    }
    if (iVar2 == 0x44) {
      dword_d4590._0_1_ = (byte)dword_d4590 ^ 1;
    }
    if (iVar2 == 0x42) {
      sub_948e4(dword_ede7c,dword_ede78,local_24);
    }
    if (iVar2 == 0x4d) {
      sub_938c8();
    }
    if ((iVar2 == 0x50) || (iVar2 == 0x20)) {
      debug_memmap();
    }
    if (((((iVar2 == 0x53) || (iVar2 == 0x5b)) || (iVar2 == 0x5d)) ||
        ((iVar2 == 0x4b00 || (iVar2 == 0x4d00)))) && ((dword_ede7c & 0x8000) == 0)) {
      sub_95158(dword_ede68,dword_ede84,local_24);
    }
    if (iVar2 == 0x56) {
      sub_95f30();
    }
    if (iVar2 == 0x54) {
      debug_palette(local_24);
    }
    if (iVar2 == 0x57) {
      sub_95f84(dword_ede68,local_24);
    }
    if (iVar2 == 0x41) {
      local_24 = local_24 ^ 1;
    }
    if (iVar2 == 9) {
      local_24 = local_24 ^ 1;
    }
    if ((iVar2 == 0x5300) && ((dword_ede7c & 0x8000) == 0)) {
      releasememblock(dword_ede80);
    }
    if ((iVar2 == 0x5200) && ((dword_ede7c & 0x8000) == 0)) {
      strncpy(acStack_3c,dword_ede64,0xc);
      uStack_30 = 0;
      sub_8d484(dword_ede80);
    }
    if (local_28 < iVar4) {
      iVar4 = iVar4 + -0x15;
      iVar5 = local_28;
    }
    else if (iVar4 < 0) {
      iVar4 = 0;
      iVar5 = 0;
    }
    if (local_28 < iVar5) {
      iVar5 = local_28;
    }
  } while (local_20 == 0);
  dword_d459c = iVar4;
  dword_d45a0 = iVar5;
  sub_96164();
  if (local_2c != 0) {
    setdefaultscreen();
    sub_93ca0(dword_d457c);
  }
  sub_938f4(local_1c);
  setfontstate(local_7c);
  sub_b3aa1(auStack_dc);
  return;
}


// ================================================================================================
// sub_93e38 @ 0x93e38 [__watcall]
// ================================================================================================

void __watcall sub_93e38(void)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined8 uVar7;
  undefined auStack_dc [96];
  undefined auStack_7c [64];
  char acStack_3c [12];
  undefined uStack_30;
  uint uStack_2c;
  int iStack_28;
  uint uStack_24;
  int iStack_20;
  undefined uStack_1c;
  
  dword_d4594 = 1;
  uStack_24 = 1;
  sub_b3a88(auStack_dc);
  getfontstate(auStack_7c);
  setfont(&unk_d45d8);
  uStack_1c = byte_d4544;
  sub_938f4(0);
  if (dword_d3024 == 0) {
    uStack_24 = 1;
  }
  dword_d457c = sub_9c5b0(0);
  dword_d4580 = sub_9c5b0(0xfcfcfc);
  dword_d4584 = sub_9c5b0(0xfcfc54);
  dword_d4588 = sub_9c5b0(0x80a8);
  dword_d458c = sub_9c5b0(0xa80000);
  uStack_2c = (uint)(uStack_24 == 0);
  iStack_20 = 0;
  iVar4 = dword_d459c;
  iVar5 = dword_d45a0;
  do {
    if ((dword_d4594 != uStack_24) &&
       (dword_d4594 = uStack_24, dword_d459c = iVar4, dword_d45a0 = iVar5, uStack_2c == 0)) {
      uStack_2c = (uint)(uStack_24 == 0);
    }
    uVar1 = sub_940f4();
    iStack_28 = sub_94188(iVar5,iVar4,uVar1);
    uVar7 = CONCAT44(iVar4 + 0x14,iStack_28);
    if (iStack_28 < iVar4 + 0x14) {
      uVar7 = CONCAT44(iStack_28,iStack_28);
    }
    do {
      uVar7 = sub_93c88((int)uVar7,(int)((ulonglong)uVar7 >> 0x20));
      iVar3 = (int)((ulonglong)uVar7 >> 0x20);
      iVar2 = (int)uVar7;
    } while (iVar2 == 0);
    iVar6 = iVar5;
    if (((iVar2 == 0x4900) && (iVar6 = iVar4, iVar5 == iVar4)) && (0 < iVar4)) {
      iVar4 = iVar4 + -0x15;
      iVar6 = iVar4;
    }
    iVar5 = iVar6;
    if (((iVar2 == 0x5100) && (iVar5 = iVar3, iVar6 == iVar3)) && (iVar5 = iVar6, iVar3 < iStack_28)
       ) {
      iVar4 = iVar4 + 0x15;
      iVar5 = iVar3 + 0x15;
    }
    if (((iVar2 == 0x4800) && (0 < iVar5)) && (iVar5 = iVar5 + -1, iVar5 < iVar4)) {
      iVar4 = iVar4 + -1;
    }
    if (((iVar2 == 0x5000) && (iVar5 < iStack_28)) && (iVar5 = iVar5 + 1, iVar3 < iVar5)) {
      iVar4 = iVar4 + 1;
    }
    iVar6 = iVar5;
    if ((iVar2 == 0x4700) && (iVar6 = iVar4, iVar5 == iVar4)) {
      iVar4 = 0;
      iVar6 = iVar4;
    }
    iVar5 = iVar6;
    if (((iVar2 == 0x4f00) && (iVar6 != iStack_28)) && (iVar5 = iVar3, iVar6 == iVar3)) {
      iVar4 = iStack_28 + -0x14;
      iVar5 = iStack_28;
    }
    if (iVar2 == 0x1b) {
      iStack_20 = 1;
    }
    if (iVar2 == 0xd) {
      sub_94b6c(dword_ede68,dword_ede84,uStack_24);
    }
    if (iVar2 == 0x43) {
      setdefaultscreen();
      sub_93ca0(dword_d457c);
    }
    if (iVar2 == 0x46) {
      dword_edab4 = 0;
    }
    if (iVar2 == 0x44) {
      dword_d4590._0_1_ = (byte)dword_d4590 ^ 1;
    }
    if (iVar2 == 0x42) {
      sub_948e4(dword_ede7c,dword_ede78,uStack_24);
    }
    if (iVar2 == 0x4d) {
      sub_938c8();
    }
    if ((iVar2 == 0x50) || (iVar2 == 0x20)) {
      debug_memmap();
    }
    if (((((iVar2 == 0x53) || (iVar2 == 0x5b)) || (iVar2 == 0x5d)) ||
        ((iVar2 == 0x4b00 || (iVar2 == 0x4d00)))) && ((dword_ede7c & 0x8000) == 0)) {
      sub_95158(dword_ede68,dword_ede84,uStack_24);
    }
    if (iVar2 == 0x56) {
      sub_95f30();
    }
    if (iVar2 == 0x54) {
      debug_palette(uStack_24);
    }
    if (iVar2 == 0x57) {
      sub_95f84(dword_ede68,uStack_24);
    }
    if (iVar2 == 0x41) {
      uStack_24 = uStack_24 ^ 1;
    }
    if (iVar2 == 9) {
      uStack_24 = uStack_24 ^ 1;
    }
    if ((iVar2 == 0x5300) && ((dword_ede7c & 0x8000) == 0)) {
      releasememblock(dword_ede80);
    }
    if ((iVar2 == 0x5200) && ((dword_ede7c & 0x8000) == 0)) {
      strncpy(acStack_3c,dword_ede64,0xc);
      uStack_30 = 0;
      sub_8d484(dword_ede80);
    }
    if (iStack_28 < iVar4) {
      iVar4 = iVar4 + -0x15;
      iVar5 = iStack_28;
    }
    else if (iVar4 < 0) {
      iVar4 = 0;
      iVar5 = 0;
    }
    if (iStack_28 < iVar5) {
      iVar5 = iStack_28;
    }
  } while (iStack_20 == 0);
  dword_d459c = iVar4;
  dword_d45a0 = iVar5;
  sub_96164();
  if (uStack_2c != 0) {
    setdefaultscreen();
    sub_93ca0(dword_d457c);
  }
  sub_938f4(uStack_1c);
  setfontstate(auStack_7c);
  sub_b3aa1(auStack_dc);
  return;
}


// ================================================================================================
// sub_93e4c @ 0x93e4c [__watcall]
// ================================================================================================

undefined8 __watcall sub_93e4c(int param_1,undefined4 unaff_EDX)

{
  if (param_1 == 1) {
    return CONCAT44(unaff_EDX,(&dword_eda08)[dword_d4598 * 5]);
  }
  return CONCAT44(unaff_EDX,(&dword_eda0c)[dword_d4598 * 5]);
}


// ================================================================================================
// sub_93e79 @ 0x93e79 [__watcall]
// ================================================================================================

void __watcall sub_93e79(undefined4 param_1,undefined4 unaff_EDX)

{
  undefined4 uVar1;
  int iVar2;
  int unaff_EBP;
  undefined4 unaff_ESI;
  int iVar3;
  int unaff_EDI;
  int iVar4;
  int iVar5;
  undefined8 uVar6;
  undefined param_13;
  uint param_14;
  int param_15;
  uint param_16;
  int param_17;
  undefined param_18;
  
  uVar6 = CONCAT44(unaff_EDX,unaff_ESI);
  do {
    iVar2 = (int)((ulonglong)uVar6 >> 0x20);
    iVar4 = unaff_EDI;
    if (iVar2 < param_15) {
      unaff_EBP = unaff_EBP + 0x15;
      iVar4 = iVar2 + 0x15;
    }
    do {
      iVar2 = (int)((ulonglong)uVar6 >> 0x20);
      iVar3 = (int)uVar6;
      if (((iVar3 == 0x4800) && (0 < iVar4)) && (iVar4 = iVar4 + -1, iVar4 < unaff_EBP)) {
        unaff_EBP = unaff_EBP + -1;
      }
      if (((iVar3 == 0x5000) && (iVar4 < param_15)) && (iVar4 = iVar4 + 1, iVar2 < iVar4)) {
        unaff_EBP = unaff_EBP + 1;
      }
      iVar5 = iVar4;
      if ((iVar3 == 0x4700) && (iVar5 = unaff_EBP, iVar4 == unaff_EBP)) {
        unaff_EBP = 0;
        iVar5 = unaff_EBP;
      }
      iVar4 = iVar5;
      if (((iVar3 == 0x4f00) && (iVar5 != param_15)) && (iVar4 = iVar2, iVar5 == iVar2)) {
        unaff_EBP = param_15 + -0x14;
        iVar4 = param_15;
      }
      if (iVar3 == 0x1b) {
        param_17 = 1;
      }
      if (iVar3 == 0xd) {
        sub_94b6c(dword_ede68,dword_ede84,param_16);
      }
      if (iVar3 == 0x43) {
        setdefaultscreen();
        sub_93ca0(dword_d457c);
      }
      if (iVar3 == 0x46) {
        dword_edab4 = 0;
      }
      if (iVar3 == 0x44) {
        dword_d4590._0_1_ = (byte)dword_d4590 ^ 1;
      }
      if (iVar3 == 0x42) {
        sub_948e4(dword_ede7c,dword_ede78,param_16);
      }
      if (iVar3 == 0x4d) {
        sub_938c8();
      }
      if ((iVar3 == 0x50) || (iVar3 == 0x20)) {
        debug_memmap();
      }
      if (((((iVar3 == 0x53) || (iVar3 == 0x5b)) || (iVar3 == 0x5d)) ||
          ((iVar3 == 0x4b00 || (iVar3 == 0x4d00)))) && ((dword_ede7c & 0x8000) == 0)) {
        sub_95158(dword_ede68,dword_ede84,param_16);
      }
      if (iVar3 == 0x56) {
        sub_95f30();
      }
      if (iVar3 == 0x54) {
        debug_palette(param_16);
      }
      if (iVar3 == 0x57) {
        sub_95f84(dword_ede68,param_16);
      }
      if (iVar3 == 0x41) {
        param_16 = param_16 ^ 1;
      }
      if (iVar3 == 9) {
        param_16 = param_16 ^ 1;
      }
      if ((iVar3 == 0x5300) && ((dword_ede7c & 0x8000) == 0)) {
        releasememblock(dword_ede80);
      }
      if ((iVar3 == 0x5200) && ((dword_ede7c & 0x8000) == 0)) {
        strncpy(&stack0x000000a0,dword_ede64,0xc);
        param_13 = 0;
        sub_8d484(dword_ede80);
      }
      if (param_15 < unaff_EBP) {
        unaff_EBP = unaff_EBP + -0x15;
        iVar4 = param_15;
      }
      else if (unaff_EBP < 0) {
        unaff_EBP = 0;
        iVar4 = 0;
      }
      if (param_15 < iVar4) {
        iVar4 = param_15;
      }
      if (param_17 != 0) {
        dword_d459c = unaff_EBP;
        dword_d45a0 = iVar4;
        sub_96164();
        if (param_14 != 0) {
          setdefaultscreen();
          sub_93ca0(dword_d457c);
        }
        sub_938f4(param_18);
        setfontstate(&stack0x00000060);
        sub_b3aa1(&stack0x00000000);
        return;
      }
      if ((dword_d4594 != param_16) &&
         (dword_d4594 = param_16, dword_d459c = unaff_EBP, dword_d45a0 = iVar4, param_14 == 0)) {
        param_14 = (uint)(param_16 == 0);
      }
      uVar1 = sub_940f4();
      param_15 = sub_94188(iVar4,unaff_EBP,uVar1);
      uVar6 = CONCAT44(unaff_EBP + 0x14,param_15);
      if (param_15 < unaff_EBP + 0x14) {
        uVar6 = CONCAT44(param_15,param_15);
      }
      do {
        uVar6 = sub_93c88((int)uVar6,(int)((ulonglong)uVar6 >> 0x20));
        iVar3 = (int)((ulonglong)uVar6 >> 0x20);
        iVar2 = (int)uVar6;
      } while (iVar2 == 0);
      unaff_EDI = iVar4;
      if (((iVar2 == 0x4900) && (unaff_EDI = unaff_EBP, iVar4 == unaff_EBP)) && (0 < unaff_EBP)) {
        unaff_EBP = unaff_EBP + -0x15;
        unaff_EDI = unaff_EBP;
      }
      iVar4 = unaff_EDI;
    } while ((iVar2 != 0x5100) || (iVar4 = iVar3, unaff_EDI != iVar3));
  } while( true );
}


// ================================================================================================
// sub_940f4 @ 0x940f4 [__watcall]
// ================================================================================================

undefined8 __watcall sub_940f4(undefined4 param_1,undefined4 unaff_EDX)

{
  int iVar1;
  undefined8 uVar2;
  
  for (uVar2 = sub_93e4c(1,0); iVar1 = (int)((ulonglong)uVar2 >> 0x20), (int)uVar2 != 0;
      uVar2 = CONCAT44(iVar1 + 1,*(undefined4 *)((int)uVar2 + 0x20))) {
  }
  return CONCAT44(unaff_EDX,iVar1 + 1);
}


// ================================================================================================
// sub_94114 @ 0x94114 [__watcall]
// ================================================================================================

undefined4 __watcall
sub_94114(int param_1,int param_2,int param_3,int param_4,undefined4 param_5,undefined4 param_6,
         undefined4 param_7,undefined4 param_8)

{
  if (param_2 != 2) {
    if ((param_1 < param_3) || (param_3 + 0x15 <= param_1)) {
      return 1;
    }
    if (param_1 == param_4) {
      dword_ede70 = dword_d4580;
      dword_ede60 = 0x70;
      dword_ede68 = param_5;
      dword_ede84 = param_6;
      dword_ede7c = param_7;
      dword_ede78 = param_8;
      return 0;
    }
    dword_ede70 = dword_d457c;
    dword_ede60 = 7;
  }
  return 0;
}


// ================================================================================================
// sub_94188 @ 0x94188 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __watcall sub_94188(int param_1,int unaff_EDX,int unaff_EBX,int unaff_ECX)

{
  char *pcVar1;
  int iVar2;
  undefined1 *__format;
  int iVar3;
  undefined4 *puVar4;
  int iVar5;
  byte bVar6;
  undefined4 local_164 [21];
  char local_110 [84];
  char local_bc [84];
  undefined local_68 [12];
  undefined local_5c [12];
  int local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  int local_40;
  undefined4 local_3c;
  int local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  int local_24;
  
  bVar6 = 0;
  sub_9477c(&local_30,&local_28,&local_2c,&local_34);
  if (dword_d4590 == 0) {
    pcVar1 = s_r_fCS__4_4x_DS__4_4x_HW___7u_Poo_000c4129 + 3;
  }
  else {
    pcVar1 = aCS44xDS44xHW66xPool66x;
  }
  sprintf(local_bc,pcVar1,CONCAT22(dword_d2f78._2_2_,(undefined2)dword_d2f78),
          CONCAT22(_dword_d2f7c,dword_d2f78._2_2_),dword_edab4,local_30);
  if (dword_d4590 == 0) {
    pcVar1 = s___Used___7u_Free___7u_Largst___7_000c417a + 2;
  }
  else {
    pcVar1 = aUsed66xFree66xLargst66x;
  }
  sprintf(local_110,pcVar1,local_28,local_2c,local_34);
  if (unaff_ECX == 0) {
    pcVar1 = aNAMESIZEADREND;
    puVar4 = local_164;
    for (iVar3 = 10; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar4 = *(undefined4 *)pcVar1;
      pcVar1 = pcVar1 + ((uint)bVar6 * -2 + 1) * 4;
      puVar4 = puVar4 + (uint)bVar6 * -2 + 1;
    }
    setdefaultscreen();
    settextpos(dword_d4584,dword_d457c);
    fillrect(0,0,dword_d3044,0,dword_d457c);
    printstr2_at(local_bc,0,0);
    sub_9c5a8();
    fillrect(0,8,dword_d3044,1,dword_d457c);
    printstr2_at(local_110,0,9);
    sub_9c5a8();
    fillrect(0,0x11,dword_d3044,1,dword_d457c);
    printstr2_at(local_164,0,0x12);
    sub_9c5a8();
    fillrect(0,0x1a,dword_d3044,2,dword_d457c);
    sub_9c5a8();
  }
  else {
    pcVar1 = aIDXNAMESIZEADRENDFLAG;
    puVar4 = local_164;
    for (iVar3 = 0xb; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar4 = *(undefined4 *)pcVar1;
      pcVar1 = pcVar1 + ((uint)bVar6 * -2 + 1) * 4;
      puVar4 = puVar4 + (uint)bVar6 * -2 + 1;
    }
    if (unaff_ECX == 1) {
      sub_935e0(&aC_c41f0,0xb);
      sub_9362c(0,0,a80s,local_bc);
      sub_9362c(0,1,a80s,local_110);
      sub_9362c(0,2,a80s,local_164);
      sub_9362c(0,3,a80s,&unk_c41fc);
    }
    else if (unaff_ECX == 2) {
      sub_96185(dword_ede74,&unk_c4200,local_bc);
      sub_96185(dword_ede74,&unk_c4200,local_110);
      sub_96185(dword_ede74,&unk_c4204,local_164);
    }
  }
  iVar3 = 0;
  iVar5 = 0;
  if (0 < unaff_EBX) {
    do {
      sub_947d8(iVar5,&local_3c,&local_50,&local_40,&local_44,&local_48,&local_4c,&local_38);
      if (local_50 != local_38) {
        iVar2 = sub_94114(iVar3,unaff_ECX,unaff_EDX,param_1,local_38,local_50 - local_38,0xa000,0);
        if (iVar2 == 0) {
          sub_948d4(local_38,local_5c);
          sub_948d4(local_50,local_68);
          if (unaff_ECX == 0) {
            if (dword_d4590 == 0) {
              pcVar1 = s____SPACE__9d__8s__8s_000c4226 + 2;
            }
            else {
              pcVar1 = s_x_SPACE__9x__8s__8s_000c4209 + 3;
            }
            sprintf(local_bc,pcVar1,local_50 - local_38,local_5c,local_68);
            settextpos(dword_ede70,dword_d458c);
            printstr2_at(local_bc,0,(iVar3 - unaff_EDX) * 8 + 0x1c);
            sub_9c5a8();
          }
          else {
            if (dword_d4590 == 0) {
              pcVar1 = aSPACE7d66s66s;
            }
            else {
              pcVar1 = s_t___SPACE__6_6x__6_6s__6_6s_000c4241 + 3;
            }
            sprintf(local_bc,pcVar1,local_50 - local_38,local_5c,local_68);
            if (unaff_ECX == 1) {
              sub_93908(dword_ede60);
              sub_9362c(0,(iVar3 - unaff_EDX) + 4,a80s,local_bc);
            }
            else if (unaff_ECX == 2) {
              sub_96185(dword_ede74,&unk_c4200,local_bc);
            }
          }
        }
        iVar3 = iVar3 + 1;
      }
      iVar2 = sub_94114(iVar3,unaff_ECX,unaff_EDX,param_1,local_50,local_44,local_48,local_4c);
      if (iVar2 == 0) {
        if (iVar3 == param_1) {
          dword_ede80 = *(int *)(dword_ede6c + 0x24);
          dword_ede64 = dword_ede80 + 4;
        }
        sub_948d4(local_50,local_5c);
        sub_948d4(local_50 + local_40,local_68);
        if (unaff_ECX == 0) {
          if (dword_d4590 == 0) {
            __format = a1212s9d8s8s;
          }
          else {
            __format = a1212s9x8s8s;
          }
          sprintf(local_110,__format,local_3c,local_44,local_5c,local_68);
          settextpos(dword_d4588,dword_ede70);
          printstr2_at(local_110,0,(iVar3 - unaff_EDX) * 8 + 0x1c);
          sub_9c5a8();
        }
        else {
          if (dword_d4590 == 0) {
            pcVar1 = a33d1212s7d66s66s44x;
          }
          else {
            pcVar1 = a33d1212s66x66s66s44x;
          }
          sprintf(local_110,pcVar1,iVar5,local_3c,local_44,local_5c,local_68,local_48);
          if (unaff_ECX == 1) {
            sub_93908(dword_ede60);
            sub_9362c(0,(iVar3 - unaff_EDX) + 4,a80s,local_110);
            sub_93908(7);
          }
          else if (unaff_ECX == 2) {
            sub_96185(dword_ede74,&unk_c4200,local_110);
          }
        }
      }
      iVar3 = iVar3 + 1;
      iVar5 = iVar5 + 1;
    } while (iVar5 < unaff_EBX);
  }
  local_24 = unaff_EDX + 0x15;
  if (unaff_ECX == 0) {
    if (iVar3 < local_24) {
      iVar5 = (iVar3 - unaff_EDX) * 8 + 0x1c;
    }
    else {
      iVar5 = 0xc4;
    }
    setclip(0,dword_d3044,iVar5,dword_d3048);
    sub_93ca0(dword_d457c);
    setdefaultscreen();
  }
  else if (unaff_ECX == 1) {
    sub_93908(7);
    iVar2 = local_24 + 4;
    for (iVar5 = iVar3 + 4 + -unaff_EDX; iVar5 < -unaff_EDX + iVar2; iVar5 = iVar5 + 1) {
      sub_9362c(0,iVar5,a80s,&unk_c41fc);
    }
  }
  return iVar3 + -1;
}


// ================================================================================================
// sub_9477c @ 0x9477c [__watcall]
// ================================================================================================

void __watcall sub_9477c(uint *param_1,uint *unaff_EDX,uint *unaff_EBX,uint *unaff_ECX)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  uint uVar4;
  
  piVar3 = (int *)sub_93e4c(1);
  piVar1 = (int *)piVar3[8];
  *unaff_ECX = 0;
  uVar4 = *unaff_ECX;
  *unaff_EBX = uVar4;
  *unaff_EDX = uVar4;
  *param_1 = uVar4;
  while (piVar2 = piVar1, piVar2 != (int *)0x0) {
    uVar4 = (*piVar2 - *piVar3) - piVar3[4];
    if ((*(byte *)((int)piVar2 + 0x19) & 0x80) == 0) {
      *unaff_EDX = *unaff_EDX + piVar2[4];
    }
    *unaff_EBX = *unaff_EBX + uVar4;
    if (*unaff_ECX < uVar4) {
      *unaff_ECX = uVar4;
    }
    piVar3 = piVar2;
    piVar1 = (int *)piVar2[8];
  }
  *param_1 = *unaff_EDX + *unaff_EBX;
  return;
}


// ================================================================================================
// sub_947d8 @ 0x947d8 [__watcall]
// ================================================================================================

void __watcall
sub_947d8(int param_1,int *param_2,int *param_3,int *param_4,int *param_5,undefined4 *param_6,
         undefined4 *param_7,int *param_8)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  
  puVar1 = dword_ede6c;
  if (param_1 == 0) {
    *param_2 = (int)(s_ACEMEM_MANAGER_000c4309 + 3);
    iVar2 = sub_8e3cc(dword_d2f80);
    *param_3 = iVar2;
    iVar3 = sub_8e3cc(*(undefined4 *)(&dword_eda08)[dword_d4598 * 5]);
    iVar2 = *param_3;
    *param_4 = iVar3 - iVar2;
    *param_5 = iVar3 - iVar2;
    *param_6 = 0x8000;
    *param_7 = 0;
    *param_8 = *param_3;
    dword_ede6c = (undefined4 *)(&dword_eda08)[dword_d4598 * 5];
  }
  else {
    *param_2 = (int)(dword_ede6c + 1);
    iVar2 = sub_8e3cc(*puVar1);
    *param_3 = iVar2;
    puVar1 = dword_ede6c;
    *param_4 = dword_ede6c[4];
    *param_5 = puVar1[5];
    *param_6 = puVar1[6];
    *param_7 = 0;
    if (param_1 < 2) {
      iVar2 = *param_3;
    }
    else {
      puVar1 = (undefined4 *)puVar1[9];
      iVar2 = sub_8e3cc(*puVar1);
      iVar2 = iVar2 + puVar1[4];
    }
    *param_8 = iVar2;
    dword_ede6c = (undefined4 *)dword_ede6c[8];
  }
  return;
}


// ================================================================================================
// sub_948d4 @ 0x948d4 [__watcall]
// ================================================================================================

void __watcall sub_948d4(undefined4 param_1,char *unaff_EDX)

{
  sprintf(unaff_EDX,(char *)&aX_c4318,param_1);
  return;
}


// ================================================================================================
// sub_948e4 @ 0x948e4 [__watcall]
// ================================================================================================

void __watcall sub_948e4(uint param_1,undefined4 unaff_EDX,int unaff_EBX)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  
  setdefaultscreen();
  sub_93000(0x2e,0x37,0x111,0xa4,dword_d4580);
  sub_93000(0x2f,0x38,0x110,0xa3,dword_d458c);
  fillrect(0x30,0x39,0xe0,0x6a,dword_d457c);
  settextpos(dword_d4584,dword_d457c);
  printf_at(0x38,0x3d,s_6_04_4X__0000_0000_0000_0000__000c431b + 1,param_1);
  sub_9c5a8();
  iVar2 = 0;
  uVar1 = param_1;
  iVar3 = 0xf8;
  do {
    if ((uVar1 & 1) != 0) {
      printstr2_at(&a1_c433c,iVar3,0x3d);
      sub_9c5a8();
    }
    uVar1 = (int)uVar1 >> 1;
    iVar4 = iVar3 + -8;
    if (iVar2 % 4 == 3) {
      iVar4 = iVar3 + -0x10;
    }
    iVar2 = iVar2 + 1;
    iVar3 = iVar4;
  } while (iVar2 < 0x10);
  settextpos(dword_d457c,dword_d458c);
  iVar3 = 0x4d;
  if ((param_1 & 0x8000) != 0) {
    sub_b4fac(0x50,0x4c,0x8f,0x4c,dword_d458c);
    printstr2_at(s___SYSTEM_000c433e + 2,0x50,0x4d);
    sub_9c5a8();
    iVar3 = 0x55;
  }
  if ((param_1 & 0x2000) != 0) {
    sub_b4fac(0x50,iVar3 + -1,0x87,iVar3 + -1,dword_d458c);
    printstr2_at(s__12_SPACE_000c4349 + 3,0x50,iVar3);
    sub_9c5a8();
    iVar3 = iVar3 + 8;
  }
  if ((param_1 & 0xa000) != 0) {
    iVar3 = iVar3 + 8;
  }
  settextpos(dword_d4580,dword_d457c);
  if ((param_1 & 0x20) == 0) {
    pcVar5 = aLOWMemoryBlock;
  }
  else {
    pcVar5 = aHIGHMemoryBlock;
  }
  printstr2_at(pcVar5,0x50,iVar3);
  sub_9c5a8();
  printstr2_at(s_6_6Conventional_memory_000c4379 + 3,0x50,iVar3 + 10);
  sub_9c5a8();
  iVar2 = iVar3 + 0x1e;
  if ((param_1 & 0x10) == 0) {
    pcVar5 = s__Non_Relocatable_block_000c43a2 + 2;
  }
  else {
    pcVar5 = aRelocatableBlock;
  }
  printstr2_at(pcVar5,0x50,iVar3 + 0x14);
  sub_9c5a8();
  if ((param_1 & 0x40) != 0) {
    printstr2_at(s_M_ALIGN_flag_is_set_000c43ba + 2,0x50,iVar2);
    sub_9c5a8();
    iVar2 = iVar3 + 0x28;
  }
  if ((param_1 & 0xf) != 0) {
    printf_at(0x50,iVar2,s__PRIORITY___1d_000c43ce + 2,param_1 & 7);
    sub_9c5a8();
    iVar2 = iVar2 + 10;
  }
  printf_at(0x50,iVar2,s_0Sequence___d_000c43de + 2,unaff_EDX);
  sub_9c5a8();
  if ((param_1 & 8) != 0) {
    printstr2_at(s_SYSBlock_is_PURGABLE_000c43ed + 3,0x50,iVar2 + 10);
    sub_9c5a8();
  }
  if (unaff_EBX == 0) {
    sub_96144();
  }
  return;
}


// ================================================================================================
// sub_94b6c @ 0x94b6c [__watcall]
// ================================================================================================

void __watcall sub_94b6c(int param_1,uint unaff_EDX)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  int iVar4;
  int iVar5;
  byte *pbVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  uint uVar11;
  uint uVar12;
  int iVar13;
  int iVar14;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 uStack_14;
  
  if (unaff_EDX == 0) {
    sub_938c8();
  }
  else {
    local_20 = unaff_EDX >> 4;
    if ((unaff_EDX & 0xf) != 0) {
      local_20 = local_20 + 1;
    }
    iVar13 = 0;
    local_1c = 0;
    bVar2 = false;
    bVar3 = false;
    iVar9 = 0;
    uVar11 = 0;
    do {
      local_18 = local_20 - uVar11;
      if (0x19 < local_18) {
        local_18 = 0x19;
      }
      iVar14 = iVar13;
      if (local_18 <= iVar13) {
        iVar14 = local_18 + -1;
      }
      iVar4 = sub_8e3d4(uVar11 * 0x10 + param_1);
      sub_94e34(local_18,uVar11,iVar4,iVar9,iVar14,local_1c);
      sub_9c5a8();
      do {
        uStack_14 = sub_b39d0();
        iVar5 = sub_9c594(uStack_14);
      } while (iVar5 == 0);
      bVar1 = false;
      if (iVar5 == 0x1b) {
        if (local_1c == 0) {
          bVar3 = true;
        }
        else {
          local_1c = 0;
        }
      }
      uVar12 = uVar11;
      iVar13 = iVar14;
      if (iVar5 == 0x4900) {
        if (iVar14 == 0) {
          if (uVar11 != 0) {
            if (uVar11 < 0x1a) {
              uVar12 = 0;
            }
            else {
              uVar12 = uVar11 - 0x19;
            }
          }
        }
        else {
          iVar13 = 0;
        }
      }
      if (iVar5 == 0x5100) {
        if (iVar13 == local_18 + -1) {
          if (uVar12 + 0x19 < local_20) {
            uVar12 = uVar12 + 0x19;
          }
        }
        else {
          iVar13 = 0x18;
        }
      }
      if ((iVar5 == 0x4800) || (iVar8 = 0, iVar5 == 0x5000)) {
        iVar8 = iVar5;
      }
      if (iVar5 == 8) {
        iVar8 = 0x4b00;
      }
      iVar10 = iVar9;
      if (iVar5 == 0x4700) {
        if (iVar9 == 0) {
          if (iVar13 == 0) {
            if (uVar12 != 0) {
              uVar12 = 0;
            }
          }
          else {
            iVar13 = 0;
          }
        }
        else {
          iVar10 = 0;
        }
      }
      if (iVar5 == 0x4f00) {
        if (iVar10 == 0xf) {
          if (iVar13 == local_18 + -1) {
            if (uVar12 + 0x18 < local_20) {
              uVar12 = local_20 - 0x19;
            }
          }
          else {
            iVar13 = 0x18;
          }
        }
        else {
          iVar10 = 0xf;
        }
      }
      if (local_1c == 1) {
        *(char *)(iVar13 * 0x10 + iVar4 + iVar10) = (char)uStack_14;
        iVar8 = 0x4d00;
      }
      if (iVar5 == 0x4d) {
        local_1c = 1;
      }
      if ((0x2f < iVar5) && (iVar5 < 0x3a)) {
        uStack_14 = iVar5 + -0x30;
        bVar1 = true;
      }
      if ((0x40 < iVar5) && (iVar5 < 0x47)) {
        uStack_14._0_1_ = (char)iVar5 + -0x37;
        bVar1 = true;
      }
      if (bVar1) {
        pbVar6 = (byte *)(iVar4 + iVar10 + iVar13 * 0x10);
        if (bVar2) {
          if (bVar2) {
            *pbVar6 = (char)uStack_14 + (*pbVar6 & 0xf0);
            iVar8 = 0x4d00;
          }
        }
        else {
          uVar7 = CONCAT11(*pbVar6,(char)uStack_14) & 0xffff0fff;
          *pbVar6 = (char)(uVar7 >> 8) + (char)uVar7 * '\x10';
          bVar2 = true;
        }
      }
      if (iVar8 == 0x4b00) {
        iVar10 = iVar10 + -1;
        if (iVar10 < 0) {
          iVar10 = 0xf;
          iVar8 = 0x4800;
        }
      }
      else if ((iVar8 == 0x4d00) && (iVar10 = iVar10 + 1, 0xf < iVar10)) {
        iVar10 = 0;
        iVar8 = 0x5000;
      }
      if (iVar8 == 0x4800) {
        if (iVar13 < 1) {
          if (uVar12 != 0) {
            uVar12 = uVar12 - 1;
          }
        }
        else {
          iVar13 = iVar13 + -1;
        }
      }
      else if (iVar8 == 0x5000) {
        if (iVar13 < 0x18) {
          iVar13 = iVar13 + 1;
        }
        else if (uVar12 + 0x19 < local_20) {
          uVar12 = uVar12 + 1;
        }
      }
      if (((iVar10 != iVar9) || (iVar13 != iVar14)) || (uVar12 != uVar11)) {
        bVar2 = false;
      }
      iVar9 = iVar10;
      uVar11 = uVar12;
    } while (!bVar3);
  }
  return;
}


// ================================================================================================
// sub_94e34 @ 0x94e34 [__watcall]
// ================================================================================================

void __watcall
sub_94e34(int param_1,int param_2,byte *unaff_EBX,uint unaff_ECX,int param_5,int param_6)

{
  int iVar1;
  byte *pbVar2;
  uint uVar3;
  int iVar4;
  int local_14;
  byte local_10;
  
  sub_935e0(&aC_c41f0,0xb);
  local_14 = param_2 << 4;
  iVar1 = 0;
  if (0 < param_1) {
    do {
      sub_935e0(a04x_c4404,local_14);
      uVar3 = 0;
      do {
        pbVar2 = unaff_EBX;
        if ((uVar3 == unaff_ECX) && (iVar1 == param_5)) {
          sub_93908(0x70);
        }
        sub_935e0(&a02x,*pbVar2);
        if (((uVar3 == unaff_ECX) && (iVar1 == param_5)) && (param_6 != 0)) {
          sub_935e0(&unk_c4414);
          sub_93908(7);
        }
        else {
          sub_93908(7);
          sub_935e0(&asc_c4418);
        }
        if ((uVar3 & 3) == 3) {
          sub_935e0(&asc_c4418);
        }
        uVar3 = uVar3 + 1;
        unaff_EBX = pbVar2 + 1;
      } while ((int)uVar3 < 0x10);
      sub_935e0(&asc_c4418);
      iVar4 = 0;
      unaff_EBX = pbVar2 + -0xf;
      do {
        local_10 = *unaff_EBX & 0x7f;
        dword_ede60 = 7;
        if (local_10 < 0x20) {
          local_10 = 0x2e;
        }
        if ((*unaff_EBX & 0x80) != 0) {
          dword_ede60 = 0x70;
        }
        sub_93908(dword_ede60);
        sub_935e0(&aC_c41f0,local_10);
        unaff_EBX = unaff_EBX + 1;
        iVar4 = iVar4 + 1;
      } while (iVar4 < 0x10);
      sub_93908(7);
      sub_935e0(&asc_c441c);
      local_14 = local_14 + 0x10;
      iVar1 = iVar1 + 1;
    } while (iVar1 < param_1);
  }
  for (; iVar1 < 0x19; iVar1 = iVar1 + 1) {
    sub_935e0(a80s,&unk_c41fc);
  }
  return;
}


// ================================================================================================
// sub_94fbc @ 0x94fbc [__cdecl]
// ================================================================================================

undefined4 sub_94fbc(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined3 *puVar2;
  undefined auStack_34 [20];
  undefined local_20 [20];
  
  uVar1 = 0;
  if (param_1 != 0) {
    dword_ede74 = param_1;
    sub_96030(local_20,auStack_34);
    sub_96185(dword_ede74,&unk_c4200,unk_c40a0);
    sub_96185(dword_ede74,s_ock__FILE___s_000c4421 + 3,param_2);
    sub_96185(dword_ede74,aDATES_c4430,local_20);
    sub_96185(dword_ede74,aTIMES_c443c,auStack_34);
    sub_96185(dword_ede74,&unk_c4200,unk_c40a0);
    if (dword_d4590 == 0) {
      puVar2 = &aFF;
    }
    else {
      puVar2 = (undefined3 *)&aN_c4448;
    }
    sub_96185(dword_ede74,s__hexmemdsp___O_s_000c444f + 1,puVar2);
    uVar1 = sub_940f4();
    sub_94188(0,0,uVar1,2);
    uVar1 = 1;
  }
  return uVar1;
}


// ================================================================================================
// debug_memmap @ 0x950ac [__watcall]
// ================================================================================================

void __watcall debug_memmap(void)

{
  undefined4 uVar1;
  undefined2 local_54;
  undefined2 uStack_52;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined uStack_48;
  
  uStack_50 = DAT_000c4468;
  uStack_4c = DAT_000c446c;
  uStack_48 = DAT_000c4470;
  _local_54 = CONCAT22((short)((uint)aXxMMAPTXT >> 0x10),0x454d);
  sub_960ac(&local_54);
  uVar1 = dword_edab4;
  if (dword_d3024 != 0) {
    sub_984d0(&local_54,0x14);
  }
  dword_ede74 = fopen((char *)&local_54,(char *)&aW_c4474);
  if (dword_ede74 == (FILE *)0x0) {
    if (dword_d3024 != 0) {
      sub_984d0(s_seError_Dumping_Memory_Map_000c4476 + 2,0x14);
    }
  }
  else {
    dword_edab4 = uVar1;
    sub_94fbc(dword_ede74,&local_54);
    fclose(dword_ede74);
    uVar1 = dword_edab4;
  }
  dword_edab4 = uVar1;
  return;
}


// ================================================================================================
// sub_95148 @ 0x95148 [__watcall]
// ================================================================================================

void __watcall
sub_95148(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  locateshape(param_1,unaff_EDX,unaff_ECX,unaff_EBX);
  return;
}


// ================================================================================================
// sub_95158 @ 0x95158 [__watcall]
// ================================================================================================

void __watcall sub_95158(int param_1,undefined4 param_2,undefined4 param_3,int unaff_ECX)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  char local_4c [4];
  undefined uStack_48;
  int iStack_44;
  int iStack_40;
  undefined local_3c [4];
  undefined local_38 [4];
  undefined local_34 [4];
  int *local_30;
  int *local_2c;
  undefined4 local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  uint uStack_14;
  int iStack_10;
  
  local_18 = param_1;
  sub_954c8(param_1,&local_28,&local_2c,&local_30,local_34,local_38,local_3c);
  local_1c = shapecount(local_28);
  uStack_48 = 0;
  if ((*local_2c < 0) || (*local_30 < 0)) {
    setdefaultscreen();
    sub_93ca0(dword_d457c);
    settextpos(dword_d4584,dword_d457c);
    sub_9c5a8();
    sub_9c890(s_nceShape_file_is_invalid__Work_w_000c4491 + 3,0x60);
    sub_9c5a8();
    iVar1 = sub_96144();
    if (iVar1 != 0x59) {
      return;
    }
  }
  iVar3 = 0;
  iStack_44 = 0;
  local_20 = 0;
  iVar1 = 0;
  if (0 < local_1c) {
    do {
      sub_90373(local_28,iVar1,local_4c);
      if (local_4c[0] == '!') {
        iVar3 = iVar3 + 1;
      }
      puVar2 = (undefined4 *)sub_95148(local_28,local_4c);
      if (((int)(char)*puVar2 & 0x80U) == 0) {
        local_20 = local_20 + 1;
      }
      else {
        iStack_44 = iStack_44 + 1;
      }
      iVar1 = iVar1 + 1;
    } while (iVar1 < local_1c);
  }
  sub_938c8();
  sub_935e0(s_2xNum____d____packed____d____not_000c44ba + 2,local_1c,iStack_44,local_20,iVar3);
  if (iVar3 == local_1c) {
    sub_935e0(s_TIMThere_are_no_shapes_that_can_b_000c44f9 + 3);
  }
  else {
    if ((unaff_ECX == 0x5b) || (unaff_ECX == 0x4b00)) {
      iVar1 = local_1c + -1;
    }
    else {
      iVar1 = 0;
      unaff_ECX = 0x5d;
    }
    local_24 = 0;
    iStack_40 = local_1c + -1;
    do {
      do {
        sub_90373(local_28,iVar1,local_4c);
        puVar2 = (undefined4 *)getshape(local_28,iVar1);
        iVar3 = sub_8e3cc(puVar2);
        sub_935e0(a44s05x,local_4c,iVar3 - local_18);
        settextpos(dword_d4584,dword_d457c);
        iVar3 = sub_8e3cc(puVar2);
        printf_at(0,0xc0,a44s05x,local_4c,iVar3 - local_18);
        sub_9c5a8();
        if (local_4c[0] == '!') {
          sub_935e0(s_umcx_cy____3d__3d___000c453a + 2,*(int *)((int)puVar2 + 6) >> 0x10,
                    (int)puVar2[2] >> 0x10);
          sub_935e0(s_SNot_drawn__000c454f + 1);
          if ((unaff_ECX == 0x5b) || (unaff_ECX == 0x4b00)) {
            iVar1 = iVar1 + -1;
            if (iVar1 < 0) {
              iVar1 = iStack_40;
            }
          }
          else if ((((unaff_ECX == 0x5d) || (unaff_ECX == 0x53)) || (unaff_ECX == 0x4d00)) &&
                  (iVar1 = iVar1 + 1, local_1c <= iVar1)) {
            iVar1 = 0;
          }
        }
        else {
          iStack_10 = sub_95548(puVar2);
          if (iStack_10 == 0) {
            sub_935e0(aBad);
            sub_93ca0(dword_d457c);
          }
          else {
            uStack_14 = (int)(char)*puVar2 & 0x80;
            setdefaultscreen();
            if (iStack_10 == 2) {
              if (uStack_14 == 0) {
                drawshape(puVar2,0,0);
              }
              else {
                sub_9ca6c(puVar2,0,0);
              }
            }
            else if (uStack_14 == 0) {
              drawshape_home(puVar2);
            }
            else {
              sub_9ca90();
            }
            sub_9c5a8();
          }
        }
      } while (local_4c[0] == '!');
      sub_9c5a8();
      do {
        unaff_ECX = sub_93c88();
      } while (unaff_ECX == 0);
      if (unaff_ECX == 0x1b) {
        local_24 = 1;
      }
      if (((unaff_ECX == 0x5b) || (unaff_ECX == 0x4b00)) && (iVar1 = iVar1 + -1, iVar1 < 0)) {
        iVar1 = iStack_40;
      }
      if ((((unaff_ECX == 0x5d) || (unaff_ECX == 0x53)) || (unaff_ECX == 0x4d00)) &&
         (iVar1 = iVar1 + 1, local_1c <= iVar1)) {
        iVar1 = 0;
      }
      if (unaff_ECX == 0x43) {
        setdefaultscreen();
        sub_93ca0(dword_d457c);
      }
      if (unaff_ECX == 0x4d) {
        sub_938c8();
      }
      if (unaff_ECX == 0x50) {
        debug_memshapes(local_18);
      }
      if (unaff_ECX == 0x56) {
        sub_95f30();
      }
    } while (local_24 == 0);
  }
  return;
}


// ================================================================================================
// sub_954c8 @ 0x954c8 [__watcall]
// ================================================================================================

void __watcall
sub_954c8(undefined4 param_1,undefined4 *param_2,int *param_3,int *unaff_ECX,int *param_5,
         int *param_6,undefined4 *param_7)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = sub_8e3d4(param_1);
  *param_2 = uVar1;
  iVar2 = sub_8e3c4(uVar1);
  *param_3 = iVar2;
  iVar2 = sub_8e3c4(iVar2 + 4);
  *unaff_ECX = iVar2;
  iVar2 = sub_8e3c4(iVar2 + 4);
  *param_5 = iVar2;
  iVar2 = sub_8e3c4(*param_5 + *(int *)*unaff_ECX * 4);
  *param_6 = iVar2;
  uVar1 = sub_8e3c4(*(int *)*unaff_ECX * 4 + *param_6);
  *param_7 = uVar1;
  return;
}


// ================================================================================================
// sub_95548 @ 0x95548 [__watcall]
// ================================================================================================

undefined8 __watcall sub_95548(undefined4 *param_1,undefined4 unaff_EDX)

{
  undefined3 *puVar1;
  char *pcVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  
  sub_935e0(aBytes3dRows3dXY3d3dCxCy3,*(int *)((int)param_1 + 2) >> 0x10,(int)param_1[1] >> 0x10,
            *(int *)((int)param_1 + 10) >> 0x10,(int)param_1[3] >> 0x10,
            *(int *)((int)param_1 + 6) >> 0x10,(int)param_1[2] >> 0x10);
  if (((int)(char)*param_1 & 0x80U) == 0) {
    puVar1 = &aUn;
  }
  else {
    puVar1 = (undefined3 *)&unk_c41fc;
  }
  sub_935e0(s_a__spacked_000c4597 + 1,puVar1);
  if (((int)(char)*param_1 & 0x80U) == 0) {
    pcVar2 = s___unpacked_000c45ad + 3;
  }
  else {
    pcVar2 = s__packed_000c45a3 + 1;
  }
  printf_at(0x70,0xc0,s_ere_3d__3d___3d__3d___s_000c45b9 + 3,*(int *)((int)param_1 + 2) >> 0x10,
            (int)param_1[1] >> 0x10,*(int *)((int)param_1 + 10) >> 0x10,(int)param_1[3] >> 0x10,
            pcVar2);
  sub_9c5a8();
  if (((((-1 < *(short *)(param_1 + 1)) &&
        (iVar4 = *(int *)((int)param_1 + 2) >> 0x10, iVar4 <= dword_d3044)) &&
       (-1 < *(short *)((int)param_1 + 6))) &&
      (((int)param_1[1] >> 0x10 <= dword_d3048 && (-1 < *(short *)(param_1 + 3))))) &&
     ((iVar5 = *(int *)((int)param_1 + 10) >> 0x10, iVar5 <= dword_d3044 &&
      (-1 < *(short *)((int)param_1 + 0xe))))) {
    if ((((int)param_1[3] >> 0x10 <= dword_d3048) && (iVar4 + iVar5 <= dword_d3044)) &&
       (((int)param_1[1] >> 0x10) + ((int)param_1[3] >> 0x10) <= dword_d3048)) {
      uVar3 = 1;
      goto LAB_000956b8;
    }
  }
  setdefaultscreen();
  sub_93ca0(dword_d457c);
  settextpos(dword_d4580,dword_d457c);
  sub_9c890(s_an_Shape_is_invalid__Draw_it_any_000c45d1 + 3,0x60);
  sub_9c5a8();
  iVar4 = sub_96144();
  if (iVar4 == 0x59) {
    uVar3 = 2;
  }
  else {
    uVar3 = 0;
  }
LAB_000956b8:
  return CONCAT44(unaff_EDX,uVar3);
}


// ================================================================================================
// debug_memshapes @ 0x956c0 [__watcall]
// ================================================================================================

void __watcall debug_memshapes(undefined4 param_1)

{
  undefined4 uVar1;
  undefined3 *puVar2;
  int extraout_EDX;
  int extraout_EDX_00;
  undefined4 *extraout_EDX_01;
  int iVar3;
  int iVar4;
  undefined4 uStack_a4;
  undefined4 uStack_a0;
  undefined4 uStack_9c;
  undefined uStack_98;
  undefined auStack_64 [20];
  undefined auStack_50 [20];
  undefined local_3c [4];
  undefined uStack_38;
  undefined local_34 [4];
  int local_30;
  undefined local_2c [4];
  int *local_28;
  undefined4 *local_24;
  undefined4 local_20;
  int iStack_1c;
  
  sub_954c8(param_1,&local_20,&local_24,&local_28,local_2c,&local_30,local_34);
  iStack_1c = *local_28;
  uStack_38 = 0;
  uStack_a4 = aMEMSHPTXT;
  uStack_a0 = DAT_000c45fc;
  uStack_9c = DAT_000c4600;
  uStack_98 = DAT_000c4604;
  sub_960ac(&uStack_a4);
  uVar1 = dword_edab4;
  sub_984d0(&uStack_a4,0x14);
  sub_9c5a8();
  dword_ede74 = fopen((char *)&uStack_a4,(char *)&aW_c4474);
  if (dword_ede74 == (FILE *)0x0) {
    sub_984d0(s_d__Error_Dumping_Shapes_List_000c4605 + 3,0x14);
    sub_9c5a8();
    dword_edab4 = uVar1;
  }
  else {
    dword_edab4 = uVar1;
    sub_96030(auStack_50,auStack_64);
    sub_96185(dword_ede74,&unk_c4200,unk_c40a0);
    sub_96185(dword_ede74,s_ock__FILE___s_000c4421 + 3,&uStack_a4);
    sub_96185(dword_ede74,aDATES_c4430,auStack_50);
    sub_96185(dword_ede74,aTIMES_c443c,auStack_64);
    sub_96185(dword_ede74,&unk_c4200,unk_c40a0);
    sub_96185(dword_ede74,s___Shape_file_name___0_12s_000c4622 + 2,dword_ede64);
    sub_96185(dword_ede74,aShapeFileSizeLd,*local_24);
    iVar4 = iStack_1c;
    sub_96185(dword_ede74,s_d_Number_of_shapes___d_000c4656 + 2,iStack_1c);
    iVar3 = 0;
    if (0 < iVar4) {
      iVar4 = 0;
      do {
        sub_90373(local_20,iVar3,local_3c);
        uVar1 = *(undefined4 *)(iVar4 + local_30);
        getshape(local_20,iVar3);
        sub_96185(dword_ede74,a44s66ld,local_3c,uVar1);
        sub_96185(dword_ede74,aBytes3dRows3d,*(int *)(extraout_EDX + 2) >> 0x10,
                  *(int *)(extraout_EDX + 4) >> 0x10);
        sub_96185(dword_ede74,s_rax_y____3d__3d__cx_cy____3d__3d_000c469e + 2,
                  *(int *)(extraout_EDX_00 + 10) >> 0x10,*(int *)(extraout_EDX_00 + 0xc) >> 0x10,
                  *(int *)(extraout_EDX_00 + 6) >> 0x10,*(int *)(extraout_EDX_00 + 8) >> 0x10);
        if (((int)(char)*extraout_EDX_01 & 0x80U) == 0) {
          puVar2 = &aUn;
        }
        else {
          puVar2 = (undefined3 *)&unk_c41fc;
        }
        sub_96185(dword_ede74,s_a__spacked_000c4597 + 1,puVar2);
        iVar4 = iVar4 + 4;
        iVar3 = iVar3 + 1;
      } while (iVar3 < iStack_1c);
    }
    if (iStack_1c != 0) {
      sub_96185(dword_ede74,&unk_c46c0);
    }
    fclose(dword_ede74);
  }
  return;
}


// ================================================================================================
// debug_palette @ 0x9596c [__watcall]
// ================================================================================================

void __watcall debug_palette(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  byte local_348 [768];
  int local_48;
  int local_44;
  int local_40;
  int local_3c;
  int local_38;
  int local_34;
  int local_30;
  uint local_2c;
  int local_28;
  uint local_24;
  uint local_20;
  uint local_1c;
  
  getpalette(0,0x100,local_348);
  setdefaultscreen();
  sub_93ca0(dword_d457c);
  sub_95ecc(0);
  fillrect(0x18,0x16,0x120,0xa3,0xff);
  sub_9c5a8();
  local_40 = 0x19;
  local_38 = 0;
  do {
    iVar4 = local_40;
    iVar2 = 0x1d;
    iVar3 = local_38;
    do {
      fillrect(iVar2,iVar4,8,7,iVar3);
      iVar2 = iVar2 + 0x12;
      iVar3 = iVar3 + 1;
    } while (iVar2 != 0x13d);
    local_40 = local_40 + 10;
    local_38 = local_38 + 0x10;
  } while (local_38 != 0x100);
  sub_9c5a8();
  iVar3 = 0;
  iVar4 = 0;
  local_2c = 0;
  local_34 = 0x1b;
  local_3c = 0x17;
  sub_92f50(0x1b,0x17,0x26,0x21,dword_d45a4);
  sub_9c5a8();
  local_30 = 0;
  local_1c = (uint)local_348[0];
  local_20 = (uint)local_348[1];
  local_24 = (uint)local_348[2];
  do {
    settimeout(10);
    local_48 = local_34;
    local_44 = local_3c;
    local_28 = 0;
    iVar2 = sub_b39d0();
    if (iVar2 == 0x30) {
      sub_95ecc(0);
    }
    if (iVar2 == 0x31) {
      sub_95ecc(1);
    }
    if (iVar2 == 0x52) {
      local_1c = local_1c + 1;
      if (0x3f < (int)local_1c) {
        local_1c = 0x3f;
      }
      local_28 = 1;
    }
    if (iVar2 == 0x47) {
      local_20 = local_20 + 1;
      if (0x3f < (int)local_20) {
        local_20 = 0x3f;
      }
      local_28 = 1;
    }
    if (iVar2 == 0x42) {
      local_24 = local_24 + 1;
      if (0x3f < (int)local_24) {
        local_24 = 0x3f;
      }
      local_28 = 1;
    }
    if (iVar2 == 0x72) {
      local_1c = local_1c - 1;
      if ((int)local_1c < 0) {
        local_1c = 0;
      }
      local_28 = 1;
    }
    if (iVar2 == 0x67) {
      local_20 = local_20 - 1;
      if ((int)local_20 < 0) {
        local_20 = 0;
      }
      local_28 = 1;
    }
    if (iVar2 == 0x62) {
      local_24 = local_24 - 1;
      if ((int)local_24 < 0) {
        local_24 = 0;
      }
      local_28 = 1;
    }
    if ((iVar2 == 0x56) || (iVar2 == 0x76)) {
      sub_95f30();
    }
    if (iVar2 == 0x4700) {
      if (iVar3 == 0) {
        iVar4 = 0;
      }
      else {
        iVar3 = 0;
      }
    }
    if (iVar2 == 0x4f00) {
      if (iVar3 == 0xf) {
        iVar4 = 0xf;
      }
      else {
        iVar3 = 0xf;
      }
    }
    if ((iVar2 == 0x4800) && (iVar4 = iVar4 + -1, iVar4 < 0)) {
      iVar4 = 0xf;
      iVar3 = iVar3 + -1;
    }
    if ((iVar2 == 0x5000) && (iVar4 = iVar4 + 1, 0xf < iVar4)) {
      iVar4 = 0;
      iVar3 = iVar3 + 1;
    }
    if ((iVar2 == 0x4b00) && (iVar3 = iVar3 + -1, iVar3 < 0)) {
      iVar3 = 0xf;
      iVar4 = iVar4 + -1;
    }
    if ((iVar2 == 0x4d00) && (iVar3 = iVar3 + 1, 0xf < iVar3)) {
      iVar3 = 0;
      iVar4 = iVar4 + 1;
    }
    if (iVar3 < 0) {
      iVar3 = 0xf;
    }
    else if (0xf < iVar3) {
      iVar3 = 0;
    }
    if (iVar4 < 0) {
      iVar4 = 0xf;
    }
    else if (0xf < iVar4) {
      iVar4 = 0;
    }
    if (local_28 != 0) {
      iVar1 = local_30 * 3;
      local_348[iVar1] = (byte)local_1c;
      local_348[iVar1 + 1] = (byte)local_20;
      local_348[iVar1 + 2] = (byte)local_24;
      setpalette(0,0x100,local_348);
    }
    local_34 = iVar3 * 0x12 + 0x1b;
    local_3c = iVar4 * 10 + 0x17;
    sub_92f50(local_48,local_44,local_48 + 0xb,local_44 + 10,(&dword_d45a4)[local_2c]);
    local_2c = local_2c + 1;
    if (2 < local_2c) {
      local_2c = 0;
    }
    sub_92f50(local_34,local_3c,local_34 + 0xb,local_3c + 10,(&dword_d45a4)[local_2c]);
    sub_9c5a8();
    local_30 = iVar4 * 0x10 + iVar3;
    iVar1 = local_30 * 3;
    local_1c = (uint)local_348[iVar1];
    local_20 = (uint)local_348[iVar1 + 1];
    local_24 = (uint)local_348[iVar1 + 2];
    settextpos(dword_d4584,dword_d457c);
    printf_at(0x44,0xc0,a033d022X,local_30,local_30);
    sub_9c5a8();
    settextpos(4,dword_d457c);
    printf_at(0x8c,0xc0,aR022d,local_1c);
    sub_9c5a8();
    settextpos(2,dword_d457c);
    printf_at(0xb4,0xc0,aG022d,local_20);
    sub_9c5a8();
    settextpos(1,dword_d457c);
    printf_at(0xdc,0xc0,aB022d,local_24);
    sub_9c5a8();
    waittimeout();
  } while (iVar2 != 0x1b);
  return;
}


// ================================================================================================
// sub_95ecc @ 0x95ecc [__watcall]
// ================================================================================================

void __watcall sub_95ecc(int param_1)

{
  int iVar1;
  int iVar2;
  
  settextpos(dword_d4584,dword_d457c);
  iVar1 = 0x19;
  iVar2 = 0x19;
  do {
    printf_at(iVar2,0xd,&a02d_c46f8,param_1);
    printf_at(7,iVar1,&a02d_c46f8,param_1);
    sub_9c5a8();
    iVar1 = iVar1 + 10;
    iVar2 = iVar2 + 0x12;
    param_1 = param_1 + 1;
  } while (iVar2 != 0x139);
  return;
}


// ================================================================================================
// sub_95f30 @ 0x95f30 [__watcall]
// ================================================================================================

void __watcall sub_95f30(void)

{
  undefined4 uVar1;
  char local_4c [4];
  char acStack_48 [4];
  ushort local_44;
  char cStack_42;
  
  uVar1 = dword_edab4;
  local_4c = (char  [4])s__ldSCREEN_____000c46fd._3_4_;
  acStack_48 = (char  [4])s__ldSCREEN_____000c46fd._7_4_;
  local_44 = s__ldSCREEN_____000c46fd._11_2_;
  cStack_42 = s__ldSCREEN_____000c46fd[0xd];
  sub_960ac(local_4c);
  local_44 = local_44 & 0xff00;
  sub_984d0(local_4c,0x14);
  sub_9c5a8();
  sub_9d090(local_4c);
  dword_edab4 = uVar1;
  return;
}


// ================================================================================================
// sub_95f84 @ 0x95f84 [__watcall]
// ================================================================================================

void __watcall sub_95f84(void)

{
  undefined4 *puVar1;
  int iVar2;
  uint uVar3;
  
  sub_938c8();
  setdefaultscreen();
  sub_93ca0(dword_d457c);
  iVar2 = sub_9d2e0(dword_ede80);
  puVar1 = *(undefined4 **)(iVar2 + 0x2c);
  setdefaultscreen();
  iVar2 = sub_95548(puVar1);
  if (iVar2 != 0) {
    uVar3 = (int)(char)*puVar1 & 0x80;
    if (iVar2 == 2) {
      if (uVar3 == 0) {
        drawshape(puVar1,0,0);
      }
      else {
        sub_9ca6c(puVar1,0,0);
      }
    }
    else if (uVar3 == 0) {
      drawshape_home(puVar1);
    }
    else {
      sub_9ca90();
    }
    sub_9c5a8();
    while (iVar2 = sub_96144(), iVar2 == 0x56) {
      sub_95f30();
    }
  }
  return;
}


// ================================================================================================
// sub_96030 @ 0x96030 [__watcall]
// ================================================================================================

void __watcall sub_96030(char *param_1,undefined4 unaff_EDX)

{
  char *__s;
  byte local_18;
  byte local_17;
  ushort local_16;
  byte local_10;
  byte local_f;
  byte local_e;
  
  sub_8eaec(&local_18,unaff_EDX,param_1,unaff_EDX);
  _dos_gettime(&local_10);
  sprintf(param_1,a02d3s02d_c470c,(uint)local_18,(&off_93c54)[local_17],(uint)local_16 % 100);
  sprintf(__s,a2d02d02d_c471c,(uint)local_10,(uint)local_f,(uint)local_e);
  return;
}


// ================================================================================================
// sub_960ac @ 0x960ac [__watcall]
// ================================================================================================

undefined8 __watcall sub_960ac(char *param_1,undefined4 unaff_EDX)

{
  char cVar1;
  char *pcVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar5 = 0;
  cVar1 = *param_1;
  pcVar2 = param_1;
  while (cVar1 != '?') {
    pcVar2 = pcVar2 + 1;
    iVar5 = iVar5 + 1;
    cVar1 = *pcVar2;
  }
  iVar4 = 0;
  do {
    *pcVar2 = (char)((longlong)iVar4 / 10) + '0';
    pcVar2[1] = (char)((longlong)iVar4 % 10) + '0';
    iVar3 = sub_b3cc8(param_1);
    if (iVar3 == 0) break;
    iVar4 = iVar4 + 1;
  } while (iVar4 < 100);
  if (99 < iVar4) {
    param_1 = param_1 + iVar5;
    param_1[1] = 'x';
    *param_1 = param_1[1];
  }
  return CONCAT44(unaff_EDX,1);
}


// ================================================================================================
// sub_9612c @ 0x9612c [__watcall]
// ================================================================================================

void __watcall sub_9612c(void)

{
  sub_9c5a8();
  dword_d45b0 = sub_93c88();
  return;
}


// ================================================================================================
// sub_96144 @ 0x96144 [__watcall]
// ================================================================================================

void __watcall
sub_96144(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  undefined4 uVar1;
  
  sub_9c5a8();
  sub_96164();
  uVar1 = sub_96170();
  sub_9c594(uVar1,unaff_EDX,unaff_ECX,unaff_EBX);
  return;
}


// ================================================================================================
// sub_96164 @ 0x96164 [__watcall]
// ================================================================================================

void __watcall sub_96164(void)

{
  flushkeys();
  return;
}


// ================================================================================================
// sub_96170 @ 0x96170 [__watcall]
// ================================================================================================

void __watcall sub_96170(void)

{
  int iVar1;
  
  flushkeys();
  do {
    iVar1 = sub_9612c();
  } while (iVar1 == 0);
  return;
}


// ================================================================================================
// sub_96185 @ 0x96185 [__cdecl]
// ================================================================================================

void sub_96185(FILE *param_1,char *param_2)

{
  undefined *local_c [2];
  
  local_c[0] = &stack0x0000000c;
  vfprintf(param_1,param_2,local_c);
  return;
}


// ================================================================================================
// sub_961b0 @ 0x961b0 [__watcall]
// ================================================================================================

undefined8 __watcall sub_961b0(char *param_1,undefined4 unaff_EDX)

{
  char cVar1;
  char *pcVar2;
  
  for (pcVar2 = param_1; cVar1 = *pcVar2, cVar1 != '\0'; pcVar2 = pcVar2 + 1) {
    if ((byte)(cVar1 + 0x9fU) < 0x1a) {
      *pcVar2 = cVar1 + -0x20;
    }
  }
  return CONCAT44(unaff_EDX,param_1);
}


// ================================================================================================
// sub_961d0 @ 0x961d0 [__watcall]
// ================================================================================================

longdouble __watcall sub_961d0(void)

{
  longdouble in_ST0;
  
  return ROUND(in_ST0);
}


// ================================================================================================
// unk_961ee @ 0x961ee
// ================================================================================================

/* WARNING: Removing unreachable block (ram,0x0009d332) */

longdouble unk_961ee(void)

{
  int unaff_EBP;
  
  if (unaff_EBP != 0) {
    FUN_0009d352();
  }
  return (longdouble)0;
}


// ================================================================================================
// unk_961f3 @ 0x961f3
// ================================================================================================

void __watcall
unk_961f3(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  code *pcVar1;
  char cVar2;
  
  if (byte_d51dc != '\x01') {
    return;
  }
  if (byte_d4d08 == '\0') {
    if (byte_d4d06 == '\t') {
      (**(code **)(dword_d41f4 + 0x30))();
    }
    else if (byte_d4d06 == '\0') {
      pcVar1 = (code *)swi(0x21);
      (*pcVar1)();
    }
    else if (byte_d4d06 == '\x01') {
      sub_a6564(0,word_d41f8,unaff_EBX,unaff_ECX,unaff_EDX,unaff_EBX,unaff_ECX);
    }
    else {
      cVar2 = sub_a6564(byte_d4d06,0,unaff_EBX,unaff_ECX,unaff_EDX,unaff_EBX,unaff_ECX);
      if (cVar2 != '\x01') {
        sub_9d521();
      }
    }
  }
  else {
    sub_9d55c();
  }
  byte_d51dc = 0;
  return;
}


// ================================================================================================
// sub_961f8 @ 0x961f8 [__watcall]
// ================================================================================================

undefined8 __watcall sub_961f8(char *param_1,undefined4 unaff_EDX)

{
  char cVar1;
  char *pcVar2;
  
  for (pcVar2 = param_1; cVar1 = *pcVar2, cVar1 != '\0'; pcVar2 = pcVar2 + 1) {
    if ((byte)(cVar1 + 0xbfU) < 0x1a) {
      *pcVar2 = cVar1 + ' ';
    }
  }
  return CONCAT44(unaff_EDX,param_1);
}


// ================================================================================================
// sub_96218 @ 0x96218 [__watcall]
// ================================================================================================

void __watcall sub_96218(int param_1)

{
  code *pcVar1;
  uint uVar2;
  
  if (param_1 != 0) {
    uVar2 = (param_1 * dword_f24cc + 500U) / 1000;
    if (uVar2 == 0) {
      uVar2 = 1;
    }
    do {
      pcVar1 = (code *)swi(0x21);
      (*pcVar1)();
      uVar2 = uVar2 - 1;
    } while (uVar2 != 0);
  }
  return;
}


// ================================================================================================
// sub_9621d @ 0x9621d [__watcall]
// ================================================================================================

void __watcall
sub_9621d(char *param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  undefined4 *puVar1;
  
  if ((param_1 != (char *)0x0) && (*param_1 != '\0')) {
    sub_91e72(param_1,&unk_d4d4c,unaff_EBX,unaff_ECX,unaff_EDX);
    sub_91e72(&asc_c472c,&unk_d4d4c);
  }
  puVar1 = (undefined4 *)sub_9d66b();
  sub_9d677(*puVar1,&unk_d4d4c);
  sub_91e72();
  sub_9b3ca(10,&unk_d4d4c);
  return;
}


// ================================================================================================
// sub_96267 @ 0x96267 [__watcall]
// ================================================================================================

uint __watcall sub_96267(undefined4 param_1,char *unaff_EDX,uint unaff_EBX)

{
  code *pcVar1;
  bool bVar2;
  uint uVar3;
  undefined4 uVar4;
  int iVar5;
  uint uVar6;
  uint extraout_EDX;
  int extraout_EDX_00;
  char *pcVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  undefined4 *puVar11;
  undefined4 *puVar12;
  uint uVar13;
  byte bVar14;
  undefined8 uVar15;
  undefined6 uVar16;
  uint local_24;
  uint local_20;
  char *local_1c;
  uint local_14;
  
  puVar9 = (undefined4 *)&stack0xffffffcc;
  uVar3 = sub_9b72e();
  if (uVar3 == 0) {
    uVar4 = 4;
LAB_00096286:
    sub_9878a(uVar4);
    return 0xffffffff;
  }
  if ((uVar3 & 2) == 0) {
    uVar4 = 6;
    goto LAB_00096286;
  }
  uVar13 = uVar3;
  uVar6 = uVar3;
  if ((uVar3 & 0x80) != 0) {
    bVar14 = 0;
    pcVar1 = (code *)swi(0x21);
    uVar16 = (*pcVar1)();
    uVar13 = (uint)uVar16;
    puVar8 = (undefined4 *)&stack0xffffffd0;
    puVar9 = (undefined4 *)&stack0xffffffd0;
    bVar2 = (bVar14 & 1) != 0;
    uVar6 = CONCAT22((ushort)((short)((uint6)uVar16 >> 0x20) << 1 | (ushort)bVar14) >> 1 |
                     (ushort)bVar2 << 0xf,(short)uVar16);
    local_20 = uVar6;
    if (bVar2) goto LAB_000962c7;
  }
  bVar14 = 0;
  if ((uVar3 & 0x40) == 0) {
    puVar9[-1] = 0x96317;
    uVar3 = sub_9d68e(uVar13,uVar6);
    if (uVar3 < 0xb0) {
                    /* WARNING: Subroutine does not return */
      puVar9[-1] = 0x96325;
      __STKOVERFLOW();
    }
    uVar13 = 0x200;
    if (uVar3 < 0x230) {
      uVar13 = 0x80;
    }
    uVar3 = 0;
    iVar5 = -uVar13;
    local_14 = 0;
    local_24 = 0;
    puVar10 = (undefined4 *)((int)puVar9 + iVar5);
    local_1c = unaff_EDX;
    while (local_14 < unaff_EBX) {
      puVar12 = puVar10;
      if (*local_1c == '\n') {
        *(undefined *)((int)puVar9 + uVar3 + iVar5) = 0xd;
        uVar3 = uVar3 + 1;
        bVar14 = uVar3 < uVar13;
        if (uVar3 == uVar13) {
          pcVar1 = (code *)swi(0x21);
          uVar15 = (*pcVar1)();
          uVar6 = (uint)((ulonglong)uVar15 >> 0x20);
          puVar8 = puVar10 + 1;
          puVar12 = puVar10 + 1;
          bVar2 = (bVar14 & 1) != 0;
          local_20 = ((int)uVar15 << 1 | (uint)bVar14) >> 1 | (uint)bVar2 << 0x1f;
          if (bVar2) goto LAB_000962c7;
          puVar11 = puVar10;
          if (local_20 != uVar13) goto LAB_00096391;
          uVar3 = local_20 ^ uVar13;
          local_24 = local_14;
        }
      }
      pcVar7 = local_1c + 1;
      local_14 = local_14 + 1;
      *(char *)((int)puVar9 + uVar3 + iVar5) = *local_1c;
      uVar3 = uVar3 + 1;
      bVar14 = uVar3 < uVar13;
      puVar10 = puVar12;
      local_1c = pcVar7;
      if (uVar3 == uVar13) {
        pcVar1 = (code *)swi(0x21);
        uVar15 = (*pcVar1)();
        uVar6 = (uint)((ulonglong)uVar15 >> 0x20);
        puVar8 = (undefined4 *)((int)puVar12 + 4);
        puVar10 = (undefined4 *)((int)puVar12 + 4);
        bVar2 = (bVar14 & 1) != 0;
        local_20 = ((int)uVar15 << 1 | (uint)bVar14) >> 1 | (uint)bVar2 << 0x1f;
        if (bVar2) goto LAB_000962c7;
        puVar11 = puVar12;
        if (local_20 != uVar13) {
LAB_00096391:
          *puVar11 = 0x9639b;
          sub_9878a(0xc,uVar6,param_1);
          return local_24 + local_20;
        }
        uVar3 = local_20 ^ uVar13;
        local_24 = local_14;
      }
    }
    bVar14 = 0;
    if (uVar3 == 0) {
      return unaff_EBX;
    }
    pcVar1 = (code *)swi(0x21);
    iVar5 = (*pcVar1)();
    puVar8 = puVar10 + 1;
    bVar2 = (bVar14 & 1) != 0;
    uVar6 = (iVar5 << 1 | (uint)bVar14) >> 1 | (uint)bVar2 << 0x1f;
    local_20 = uVar6;
    if (!bVar2) {
      if (uVar6 == uVar3) {
        return unaff_EBX;
      }
      *puVar10 = 0x96427;
      sub_9878a(0xc,uVar6,param_1);
      return local_24 + extraout_EDX_00;
    }
  }
  else {
    pcVar1 = (code *)swi(0x21);
    iVar5 = (*pcVar1)();
    puVar8 = puVar9 + 1;
    bVar2 = (bVar14 & 1) != 0;
    uVar6 = (iVar5 << 1 | (uint)bVar14) >> 1 | (uint)bVar2 << 0x1f;
    local_20 = uVar6;
    if (!bVar2) {
      if (uVar6 == unaff_EBX) {
        return unaff_EBX;
      }
      *puVar9 = 0x9630a;
      sub_9878a(0xc,uVar6,param_1);
      return extraout_EDX;
    }
  }
LAB_000962c7:
  *(undefined4 *)((int)puVar8 + -4) = 0x962d2;
  uVar3 = sub_9a735(local_20 & 0xffff,uVar6,param_1);
  return uVar3;
}


// ================================================================================================
// sub_96440 @ 0x96440 [__cdecl]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_96440(int param_1,int param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  int local_1c;
  int local_18;
  uint local_10;
  
  if (dword_d30c8 == 0) {
    sub_b6df7(param_1,param_2,param_3);
  }
  else {
    *(short *)(param_1 + 0xc) = (short)param_2;
    *(short *)(param_1 + 0xe) = (short)param_3;
    iVar5 = param_1 + 0x10;
    local_18 = *(int *)(param_1 + 2) >> 0x10;
    local_1c = *(int *)(param_1 + 4) >> 0x10;
    iVar3 = dword_d30b0 - param_3;
    if (0 < iVar3) {
      iVar5 = iVar5 + local_18 * iVar3;
      local_1c = local_1c - iVar3;
      param_3 = param_3 + iVar3;
    }
    iVar3 = (param_3 + local_1c) - dword_d30b8;
    if (0 < iVar3) {
      local_1c = local_1c - iVar3;
    }
    iVar4 = dword_d30ac - param_2;
    iVar3 = 0;
    if (0 < iVar4) {
      iVar5 = iVar5 + iVar4;
      local_18 = local_18 - iVar4;
      param_2 = param_2 + iVar4;
      iVar3 = iVar4;
    }
    iVar4 = (local_18 + param_2) - _dword_d30b4;
    if (0 < iVar4) {
      iVar3 = iVar3 + iVar4;
      local_18 = local_18 - iVar4;
    }
    iVar4 = (&unk_d3104)[param_3];
    iVar1 = dword_d30a4 - local_18;
    local_10 = (uint)(param_2 + iVar4) >> 0x10;
    iVar7 = dword_d30d0;
    sub_b5e00(local_10,iVar1,iVar3,dword_d30d0);
    uVar6 = param_2 + iVar4 & 0xffff;
    if (0 < local_18) {
      for (; 0 < local_1c; local_1c = local_1c + -1) {
        uVar2 = local_18 + uVar6;
        if ((uVar2 & 0x10000) == 0) {
          sub_b3abc(iVar7 + uVar6,iVar5,local_18);
          iVar5 = iVar5 + local_18;
        }
        else {
          sub_b3abc(iVar7 + uVar6,iVar5,0x10000 - uVar6);
          iVar5 = iVar5 + (0x10000 - uVar6);
          uVar2 = uVar2 & 0xffff;
          local_10 = local_10 + 1;
          sub_b5e00(local_10);
          sub_b3abc(iVar7,iVar5,uVar2);
          iVar5 = iVar5 + uVar2;
        }
        uVar6 = uVar2 + iVar1;
        iVar5 = iVar5 + iVar3;
        if ((uVar6 & 0x10000) != 0) {
          uVar6 = uVar6 & 0xffff;
          local_10 = local_10 + 1;
          sub_b5e00(local_10);
        }
      }
    }
  }
  return;
}


// ================================================================================================
// sub_965dc @ 0x965dc [__cdecl]
// ================================================================================================

void sub_965dc(int param_1)

{
  sub_96440(param_1,*(int *)(param_1 + 10) >> 0x10,*(int *)(param_1 + 0xc) >> 0x10);
  return;
}


// ================================================================================================
// sub_965f8 @ 0x965f8 [__cdecl]
// ================================================================================================

void sub_965f8(int param_1,int param_2,int param_3)

{
  sub_96440(param_1,param_2 - (*(int *)(param_1 + 6) >> 0x10),
            param_3 - (*(int *)(param_1 + 8) >> 0x10));
  return;
}


// ================================================================================================
// sub_96620 @ 0x96620 [__watcall]
// ================================================================================================

void __watcall sub_96620(void)

{
  undefined4 uVar1;
  int param_5;
  int param_6;
  int in_stack_0000000c;
  int in_stack_00000010;
  int in_stack_00000014;
  int in_stack_00000018;
  undefined auStack_6c [96];
  
  sub_b3a88(auStack_6c);
  uVar1 = dword_d30d0;
  setdefaultscreen();
  setclip(param_5,in_stack_00000014 + param_5,param_6,in_stack_00000018 + param_6);
  sub_96440(uVar1,param_5 - in_stack_0000000c,param_6 - in_stack_00000010);
  sub_b3aa1(auStack_6c);
  return;
}


// ================================================================================================
// sub_96690 @ 0x96690 [__watcall]
// ================================================================================================

void __watcall sub_96690(undefined4 *param_1)

{
  sub_935e0(aFrameRate3dFrames3dBlock,param_1[2],*param_1,param_1[8]);
  sub_935e0(s_me_Width___3d_Height___3d_000c475d + 3,param_1[3],param_1[4]);
  sub_935e0(s_cdeColours___3d_1st_Colour___3d_000c477d + 3,param_1[6],param_1[5]);
  return;
}


// ================================================================================================
// sub_966e4 @ 0x966e4 [__watcall]
// ================================================================================================

void __watcall sub_966e4(int *param_1,int unaff_EDX)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  byte bVar6;
  byte bVar7;
  byte bVar8;
  byte bVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  byte *pbVar15;
  
  bVar1 = *(byte *)(unaff_EDX + 2);
  bVar2 = *(byte *)(unaff_EDX + 3);
  iVar14 = (uint)*(byte *)(unaff_EDX + 4) + (uint)*(byte *)(unaff_EDX + 5) * 0x100;
  iVar12 = (uint)*(byte *)(unaff_EDX + 6) + (uint)*(byte *)(unaff_EDX + 7) * 0x100;
  bVar3 = *(byte *)(unaff_EDX + 8);
  bVar4 = *(byte *)(unaff_EDX + 9);
  bVar5 = *(byte *)(unaff_EDX + 10);
  bVar6 = *(byte *)(unaff_EDX + 0xb);
  bVar7 = *(byte *)(unaff_EDX + 0xc);
  bVar8 = *(byte *)(unaff_EDX + 0xd);
  pbVar15 = (byte *)(unaff_EDX + 0x10);
  iVar13 = (uint)*(byte *)(unaff_EDX + 0xe) + (uint)*(byte *)(unaff_EDX + 0xf) * 0x100;
  iVar11 = iVar13 * 3;
  iVar10 = allocmem(s_firmvipal_000c47a1 + 3,iVar11,0);
  param_1[7] = iVar10;
  iVar10 = 0;
  if (iVar11 != 0) {
    do {
      bVar9 = *pbVar15;
      pbVar15 = pbVar15 + 1;
      *(char *)(param_1[7] + iVar10) = (char)((int)(uint)bVar9 >> 2);
      iVar10 = iVar10 + 1;
    } while (iVar10 < iVar11);
  }
  param_1[5] = (uint)bVar7 + (uint)bVar8 * 0x100;
  param_1[6] = iVar13;
  *param_1 = (uint)bVar1 + (uint)bVar2 * 0x100;
  param_1[1] = 1;
  param_1[8] = (uint)bVar3 + (uint)bVar4 * 0x100;
  param_1[3] = iVar14;
  param_1[4] = iVar12;
  param_1[10] = iVar11 + 0x10;
  param_1[0xb] = iVar11 + 0x10;
  param_1[2] = (uint)bVar5 + (uint)bVar6 * 0x100;
  iVar11 = windowdefp(iVar14,iVar12,0);
  param_1[0xd] = iVar11;
  iVar11 = windowdefp(iVar14,iVar12,0);
  param_1[0xe] = iVar11;
  iVar12 = windowdefp(iVar14,iVar12,0);
  param_1[0xf] = iVar12;
  return;
}


// ================================================================================================
// sub_96844 @ 0x96844 [__watcall]
// ================================================================================================

int __watcall sub_96844(void)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 in_stack_00000004;
  int in_stack_00000008;
  undefined local_328 [784];
  undefined local_18 [4];
  int local_14;
  int local_10;
  
  iVar1 = sub_8ccc4();
  if (iVar1 != 0) {
    if ((in_stack_00000008 == 1) || (in_stack_00000008 == 0)) {
      iVar2 = sub_8e8f0();
      if (iVar2 == 0) {
        if (in_stack_00000008 != 0) {
          freemem(iVar1);
          iVar1 = 0;
        }
      }
      else {
        uVar3 = sub_8dbd4(iVar2);
        uVar3 = sub_972f0(uVar3);
        sub_966e4(iVar1,uVar3);
        *(int *)(iVar1 + 0x30) = iVar2;
        *(undefined4 *)(iVar1 + 0x24) = 0;
      }
    }
    else {
      sub_b3b5a(in_stack_00000004,&local_10,&local_14,local_18);
      if (local_10 == 0) {
        freemem(iVar1);
        return 0;
      }
      sub_b3c74(local_10,local_328,0x310);
      sub_966e4(iVar1,local_328);
      *(int *)(iVar1 + 0x24) = local_10;
      *(int *)(iVar1 + 0x28) = *(int *)(iVar1 + 0x28) + local_14;
      iVar2 = sub_8cc70(s_DATABUFFER_000c47ab + 1,*(int *)(iVar1 + 0xc) * *(int *)(iVar1 + 0x10),
                        0x40);
      *(int *)(iVar1 + 0x30) = iVar2;
      if (iVar2 == 0) {
        closehandle(local_10);
        freemem(iVar1);
        return 0;
      }
      seekhandle(local_10,*(undefined4 *)(iVar1 + 0x28));
    }
  }
  return iVar1;
}


// ================================================================================================
// sub_969a8 @ 0x969a8 [__watcall]
// ================================================================================================

void __watcall sub_969a8(void)

{
  int in_stack_00000004;
  
  if (in_stack_00000004 != 0) {
    if (*(int *)(in_stack_00000004 + 0x24) != 0) {
      closehandle(*(int *)(in_stack_00000004 + 0x24));
    }
    if (*(int *)(in_stack_00000004 + 0x30) != 0) {
      releasememblock(*(int *)(in_stack_00000004 + 0x30));
    }
    sub_9132c(*(undefined4 *)(in_stack_00000004 + 0x34));
    sub_9132c(*(undefined4 *)(in_stack_00000004 + 0x38));
    sub_9132c(*(undefined4 *)(in_stack_00000004 + 0x3c));
    freemem(*(undefined4 *)(in_stack_00000004 + 0x1c));
    freemem(in_stack_00000004);
  }
  return;
}


// ================================================================================================
// sub_96a10 @ 0x96a10 [__cdecl]
// ================================================================================================

void sub_96a10(int param_1)

{
  *(undefined4 *)(param_1 + 4) = 1;
  if (*(int *)(param_1 + 0x24) == 0) {
    *(undefined4 *)(param_1 + 0x2c) = *(undefined4 *)(param_1 + 0x28);
    return;
  }
  seekhandle(*(int *)(param_1 + 0x24),*(undefined4 *)(param_1 + 0x28));
  return;
}


// ================================================================================================
// sub_96a38 @ 0x96a38 [__cdecl]
// ================================================================================================

void sub_96a38(int param_1,undefined4 *param_2,undefined4 *param_3,undefined4 *param_4)

{
  *param_2 = *(undefined4 *)(param_1 + 0x14);
  *param_3 = *(undefined4 *)(param_1 + 0x18);
  *param_4 = *(undefined4 *)(param_1 + 0x1c);
  return;
}


// ================================================================================================
// sub_96a58 @ 0x96a58 [__cdecl]
// ================================================================================================

undefined4 sub_96a58(int param_1)

{
  return *(undefined4 *)(param_1 + 4);
}


// ================================================================================================
// sub_96a60 @ 0x96a60 [__cdecl]
// ================================================================================================

undefined4 sub_96a60(int param_1)

{
  return *(undefined4 *)(param_1 + 0xc);
}


// ================================================================================================
// sub_96a68 @ 0x96a68 [__cdecl]
// ================================================================================================

undefined4 sub_96a68(int param_1)

{
  return *(undefined4 *)(param_1 + 0x10);
}


// ================================================================================================
// sub_96a70 @ 0x96a70 [__cdecl]
// ================================================================================================

undefined4 sub_96a70(undefined4 *param_1)

{
  return *param_1;
}


// ================================================================================================
// sub_96a78 @ 0x96a78 [__cdecl]
// ================================================================================================

undefined4 sub_96a78(int param_1)

{
  return *(undefined4 *)(param_1 + 8);
}


// ================================================================================================
// sub_96a80 @ 0x96a80 [__cdecl]
// ================================================================================================

bool sub_96a80(int *param_1)

{
  return *param_1 < param_1[1];
}


// ================================================================================================
// sub_96a94 @ 0x96a94 [__watcall]
// ================================================================================================

void __watcall sub_96a94(void)

{
  int iVar1;
  int in_stack_00000004;
  int in_stack_00000008;
  
  if (in_stack_00000008 < 0) {
    in_stack_00000008 = 0;
  }
  sub_96a10(in_stack_00000004);
  iVar1 = *(int *)(in_stack_00000004 + 4);
  while (iVar1 < in_stack_00000008) {
    sub_96e7c(in_stack_00000004);
    iVar1 = *(int *)(in_stack_00000004 + 4);
  }
  return;
}


// ================================================================================================
// sub_96ac4 @ 0x96ac4 [__watcall]
// ================================================================================================

void __watcall sub_96ac4(int param_1,byte *unaff_EDX,byte *unaff_EBX)

{
  byte bVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined4 *puVar8;
  int *piVar9;
  undefined4 *puVar10;
  int iVar11;
  int local_3c;
  int local_20;
  int local_18;
  int local_14;
  
  iVar3 = *(int *)(param_1 + 0xc);
  iVar4 = *(int *)(*(int *)(param_1 + 0x34) + 0x2c);
  iVar5 = *(int *)(*(int *)(param_1 + 0x38) + 0x2c);
  iVar6 = *(int *)(*(int *)(param_1 + 0x3c) + 0x2c);
  iVar7 = *(int *)(*(int *)(param_1 + 0x34) + 0x28);
  local_20 = 0;
  if (0 < *(int *)(param_1 + 0x10)) {
    do {
      local_14 = 0;
      if (0 < iVar3) {
        piVar9 = (int *)(iVar7 + local_20 * 4);
        iVar11 = iVar4;
        do {
          if ((*unaff_EDX == 0xff) && (*unaff_EBX == 0xff)) {
            puVar8 = (undefined4 *)(*piVar9 + iVar11);
            *puVar8 = *(undefined4 *)(unaff_EBX + 1);
            puVar8 = (undefined4 *)((int)puVar8 + iVar3);
            *puVar8 = *(undefined4 *)(unaff_EBX + 5);
            puVar8 = (undefined4 *)((int)puVar8 + iVar3);
            *puVar8 = *(undefined4 *)(unaff_EBX + 9);
            *(undefined4 *)(iVar3 + (int)puVar8) = *(undefined4 *)(unaff_EBX + 0xd);
            unaff_EBX = unaff_EBX + 0x11;
          }
          else {
            bVar1 = *unaff_EDX;
            if (bVar1 == 0xff) {
              bVar1 = *unaff_EBX;
              bVar2 = *unaff_EBX;
              unaff_EBX = unaff_EBX + 1;
              local_3c = iVar6;
            }
            else {
              bVar2 = *unaff_EDX;
              local_3c = iVar5;
            }
            local_18 = ((int)(uint)bVar2 >> 4) + -7;
            puVar10 = (undefined4 *)(*piVar9 + iVar11);
            puVar8 = (undefined4 *)
                     (local_3c + local_14 + ((bVar1 & 0xf) - 7) +
                     *(int *)(iVar7 + (local_20 + local_18) * 4));
            *puVar10 = *puVar8;
            puVar10 = (undefined4 *)((int)puVar10 + iVar3);
            puVar8 = (undefined4 *)((int)puVar8 + iVar3);
            *puVar10 = *puVar8;
            puVar10 = (undefined4 *)((int)puVar10 + iVar3);
            puVar8 = (undefined4 *)((int)puVar8 + iVar3);
            *puVar10 = *puVar8;
            *(undefined4 *)(iVar3 + (int)puVar10) = *(undefined4 *)(iVar3 + (int)puVar8);
          }
          unaff_EDX = unaff_EDX + 1;
          iVar11 = iVar11 + 4;
          local_14 = local_14 + 4;
        } while (local_14 < iVar3);
      }
      local_20 = local_20 + 4;
    } while (local_20 < *(int *)(param_1 + 0x10));
  }
  return;
}


// ================================================================================================
// sub_96c4c @ 0x96c4c [__watcall]
// ================================================================================================

void __watcall sub_96c4c(int param_1,byte *unaff_EDX,byte *unaff_EBX)

{
  byte bVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  byte *pbVar10;
  int iVar11;
  int iVar12;
  byte *pbVar13;
  int local_60;
  int local_5c;
  int local_40;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  
  iVar3 = *(int *)(param_1 + 0xc);
  iVar4 = *(int *)(param_1 + 0x10);
  iVar5 = *(int *)(param_1 + 0x20);
  iVar9 = *(int *)(*(int *)(param_1 + 0x34) + 0x2c) + 0x10;
  iVar6 = *(int *)(*(int *)(param_1 + 0x38) + 0x2c);
  iVar7 = *(int *)(*(int *)(param_1 + 0x3c) + 0x2c);
  local_40 = 0;
  if (0 < iVar4) {
    do {
      local_60 = 0;
      if (0 < iVar3) {
        do {
          if ((*unaff_EDX == 0xff) && (*unaff_EBX == 0xff)) {
            local_2c = local_40;
            unaff_EBX = unaff_EBX + 1;
            if (local_40 < local_40 + iVar5) {
              iVar11 = local_40 * iVar3;
              do {
                if (local_60 < local_60 + iVar5) {
                  pbVar10 = (byte *)(local_60 + iVar11 + iVar9);
                  iVar8 = local_60;
                  pbVar13 = unaff_EBX;
                  do {
                    unaff_EBX = pbVar13 + 1;
                    *pbVar10 = *pbVar13;
                    pbVar10 = pbVar10 + 1;
                    iVar8 = iVar8 + 1;
                    pbVar13 = unaff_EBX;
                  } while (iVar8 < local_60 + iVar5);
                }
                iVar11 = iVar11 + iVar3;
                local_2c = local_2c + 1;
              } while (local_2c < local_40 + iVar5);
            }
          }
          else {
            bVar1 = *unaff_EDX;
            if (bVar1 == 0xff) {
              bVar1 = *unaff_EBX;
              bVar2 = *unaff_EBX;
              unaff_EBX = unaff_EBX + 1;
              local_24 = iVar7;
            }
            else {
              bVar2 = *unaff_EDX;
              local_24 = iVar6;
            }
            local_20 = (bVar1 & 0xf) - 7;
            local_24 = local_24 + 0x10;
            local_5c = ((int)(uint)bVar2 >> 4) + -7;
            if (0 < iVar5) {
              local_28 = local_40;
              do {
                if (0 < iVar5) {
                  iVar11 = local_60;
                  do {
                    if ((local_28 < iVar4) && (iVar11 < iVar3)) {
                      iVar8 = local_20 + iVar11;
                      iVar12 = local_5c + local_28;
                      if ((iVar12 < 0) || (((iVar4 <= iVar12 || (iVar8 < 0)) || (iVar3 <= iVar8))))
                      {
                        *(undefined *)(local_28 * iVar3 + iVar9 + iVar11) = 0;
                      }
                      else {
                        *(undefined *)(local_28 * iVar3 + iVar9 + iVar11) =
                             *(undefined *)(iVar12 * iVar3 + local_24 + iVar8);
                      }
                    }
                    iVar11 = iVar11 + 1;
                  } while (iVar11 < local_60 + iVar5);
                }
                local_28 = local_28 + 1;
              } while (local_28 < iVar5 + local_40);
            }
          }
          unaff_EDX = unaff_EDX + 1;
          local_60 = local_60 + iVar5;
        } while (local_60 < iVar3);
      }
      local_40 = local_40 + iVar5;
    } while (local_40 < iVar4);
  }
  return;
}


// ================================================================================================
// sub_96e7c @ 0x96e7c [__cdecl]
// ================================================================================================

undefined4 sub_96e7c(int param_1)

{
  int iVar1;
  char *pcVar2;
  undefined4 uVar3;
  int iVar4;
  byte local_24;
  byte local_23;
  byte local_22;
  byte local_21;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  char *local_10;
  
  local_14 = *(int *)(param_1 + 0x20);
  local_20 = *(int *)(param_1 + 0xc);
  local_1c = *(int *)(param_1 + 0x10);
  local_18 = ((local_20 + local_14 + -1) / local_14) * ((local_1c + local_14 + -1) / local_14);
  iVar1 = sub_8dbd4(*(undefined4 *)(param_1 + 0x30));
  pcVar2 = (char *)sub_972f0(iVar1 + *(int *)(param_1 + 0x2c));
  local_10 = pcVar2 + local_18;
  iVar1 = sub_96a80(param_1);
  if (iVar1 == 0) {
    uVar3 = *(undefined4 *)(param_1 + 0x3c);
    *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)(param_1 + 0x38);
    *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(param_1 + 0x34);
    *(undefined4 *)(param_1 + 0x34) = uVar3;
    if (*(int *)(param_1 + 0x24) != 0) {
      uVar3 = sub_8dbd4(*(undefined4 *)(param_1 + 0x30));
      pcVar2 = (char *)sub_972f0(uVar3);
      sub_b3c74(*(undefined4 *)(param_1 + 0x24),pcVar2,2);
    }
    if ((*pcVar2 == '\0') && (pcVar2[1] == '\0')) {
      iVar4 = local_20 * local_1c;
      iVar1 = iVar4 + 2;
      if (*(int *)(param_1 + 0x24) == 0) {
        sub_b3abc(pcVar2 + 2,*(int *)(*(int *)(param_1 + 0x34) + 0x2c) + 0x10,iVar4);
      }
      else {
        sub_b3c74(*(int *)(param_1 + 0x24),*(int *)(*(int *)(param_1 + 0x34) + 0x2c) + 0x10,iVar4);
      }
    }
    else {
      if (*(int *)(param_1 + 0x24) == 0) {
        iVar1 = (uint)(byte)pcVar2[2] + (uint)(byte)pcVar2[3] * 0x100 +
                (uint)(byte)pcVar2[4] * 0x10000 + (uint)(byte)pcVar2[5] * 0x1000000;
        pcVar2 = pcVar2 + 6;
        local_10 = local_10 + 6;
      }
      else {
        sub_b3c74(*(int *)(param_1 + 0x24),&local_24,4);
        iVar1 = (uint)local_24 + (uint)local_23 * 0x100 + (uint)local_22 * 0x10000 +
                (uint)local_21 * 0x1000000;
        uVar3 = sub_8dbd4(*(undefined4 *)(param_1 + 0x30));
        pcVar2 = (char *)sub_972f0(uVar3);
        sub_b3c74(*(undefined4 *)(param_1 + 0x24),pcVar2,iVar1);
        local_10 = pcVar2 + local_18;
      }
      iVar1 = iVar1 + 6;
      if (local_14 == 4) {
        sub_96ac4(param_1,pcVar2,local_10);
        *(int *)(param_1 + 4) = *(int *)(param_1 + 4) + 1;
        *(int *)(param_1 + 0x2c) = *(int *)(param_1 + 0x2c) + iVar1;
        return *(undefined4 *)(*(int *)(param_1 + 0x34) + 0x2c);
      }
      sub_96c4c(param_1,pcVar2,local_10);
    }
    *(int *)(param_1 + 4) = *(int *)(param_1 + 4) + 1;
    *(int *)(param_1 + 0x2c) = *(int *)(param_1 + 0x2c) + iVar1;
    iVar1 = *(int *)(param_1 + 0x34);
  }
  else {
    iVar1 = *(int *)(param_1 + 0x34);
  }
  return *(undefined4 *)(iVar1 + 0x2c);
}


// ================================================================================================
// sub_97079 @ 0x97079 [__watcall]
// ================================================================================================

undefined8 __watcall sub_97079(int param_1,undefined4 unaff_EDX)

{
  short sVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  uint uVar5;
  undefined **ppuVar6;
  undefined4 *puVar7;
  
  if ((-1 < param_1) && (param_1 < 7)) {
    for (uVar2 = 0; (int)uVar2 < (int)dword_d4f64; uVar2 = uVar2 + 1) {
      if (param_1 == (&unk_edeb0)[uVar2 * 0xb]) goto LAB_0009715c;
    }
    if (dword_d4f64 == 0) {
      for (uVar2 = 0; uVar2 < 7; uVar2 = uVar2 + 1) {
        (&unk_d4bc8)[uVar2 * 0xb] = 0xffffffff;
      }
    }
    uVar2 = dword_d4f64;
    (&unk_d4bc8)[param_1 * 0xb] = dword_d4f64;
    ppuVar6 = &funcptr_d4ba0 + param_1 * 0xb;
    puVar7 = (undefined4 *)(&unk_ede88 + uVar2 * 0x2c);
    for (iVar4 = 0xb; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar7 = *ppuVar6;
      ppuVar6 = ppuVar6 + 1;
      puVar7 = puVar7 + 1;
    }
    (&unk_edeb0)[uVar2 * 0xb] = param_1;
    uVar5 = uVar2 & 0xff;
    uVar3 = sub_9717f(uVar5);
    sVar1 = sub_97194(uVar5,uVar3);
    if (sVar1 != 0) {
      sub_971ab(uVar5,uVar3);
      (&unk_f243e)[uVar2] = (&unk_edeac)[uVar2 * 0x2c];
      iVar4 = sub_971f8(uVar5,7);
      if ((0 < iVar4) && (iVar4 < 100)) {
        dword_d4f96 = uVar2;
      }
      dword_d4f64 = dword_d4f64 + 1;
      goto LAB_0009715c;
    }
  }
  uVar2 = 0xffffffff;
LAB_0009715c:
  return CONCAT44(unaff_EDX,uVar2);
}


// ================================================================================================
// sub_97166 @ 0x97166 [__watcall]
// ================================================================================================

undefined4 __watcall sub_97166(int param_1)

{
  if (dword_d4f64 < 1) {
    return 0xffffffff;
  }
  return (&unk_d4bc8)[param_1 * 0xb];
}


// ================================================================================================
// sub_9717f @ 0x9717f [__watcall]
// ================================================================================================

void __watcall
sub_9717f(uint param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  (**(code **)(&unk_ede88 + (param_1 & 0xff) * 0x2c))(unaff_EDX,unaff_ECX,unaff_EBX);
  return;
}


// ================================================================================================
// sub_97194 @ 0x97194 [__watcall]
// ================================================================================================

void __watcall
sub_97194(uint param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  (**(code **)(&unk_ede8c + (param_1 & 0xff) * 0x2c))(unaff_EDX,unaff_ECX,unaff_EBX);
  return;
}


// ================================================================================================
// sub_971ab @ 0x971ab [__watcall]
// ================================================================================================

void __watcall
sub_971ab(uint param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  (**(code **)(&unk_ede90 + (param_1 & 0xff) * 0x2c))(unaff_EDX,unaff_ECX,unaff_EBX);
  return;
}


// ================================================================================================
// sub_971be @ 0x971be [__watcall]
// ================================================================================================

void __watcall
sub_971be(uint param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  if ((int)(param_1 & 0xff) < dword_d4f64) {
    (**(code **)(&unk_ede94 + (param_1 & 0xff) * 0x2c))(unaff_EDX,unaff_ECX,unaff_EBX);
  }
  return;
}


// ================================================================================================
// sub_971db @ 0x971db [__watcall]
// ================================================================================================

void __watcall
sub_971db(uint param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  if ((int)(param_1 & 0xff) < dword_d4f64) {
    (**(code **)(&unk_ede98 + (param_1 & 0xff) * 0x2c))(unaff_EDX,unaff_ECX,unaff_EBX);
  }
  return;
}


// ================================================================================================
// sub_971f8 @ 0x971f8 [__watcall]
// ================================================================================================

void __watcall
sub_971f8(uint param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  (**(code **)(&unk_ede9c + (param_1 & 0xff) * 0x2c))(unaff_EDX,unaff_ECX,unaff_EBX);
  return;
}


// ================================================================================================
// sub_9720b @ 0x9720b [__watcall]
// ================================================================================================

void __watcall sub_9720b(uint param_1,undefined2 unaff_DX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  if ((int)(param_1 & 0xff) < dword_d4f64) {
    (**(code **)(&unk_edea0 + (param_1 & 0xff) * 0x2c))(unaff_DX,unaff_EBX,unaff_ECX);
  }
  return;
}


// ================================================================================================
// sub_9722e @ 0x9722e [__watcall]
// ================================================================================================

void __watcall sub_9722e(byte param_1,undefined2 unaff_DX,undefined *unaff_EBX,undefined4 unaff_ECX)

{
  ushort uVar1;
  char cVar2;
  
  if ((int)(uint)param_1 < dword_d4f64) {
    uVar1 = CONCAT11(*unaff_EBX,param_1) & 0xf0ff;
    cVar2 = (char)(uVar1 >> 8);
    if ((cVar2 == -0x80) || (cVar2 == -0x70)) {
      unaff_EBX[1] = unaff_EBX[1] + '\x18';
    }
    (**(code **)(&unk_edea4 + (uVar1 & 0xff) * 0x2c))(unaff_DX,unaff_EBX,unaff_ECX);
  }
  return;
}


// ================================================================================================
// sub_97268 @ 0x97268 [__watcall]
// ================================================================================================

void __watcall
sub_97268(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,
         undefined4 param_6,undefined4 param_7,undefined4 param_8,undefined4 param_9,
         undefined4 param_10)

{
  if ((int)(param_1 & 0xff) < dword_d4f64) {
    (**(code **)(&unk_edea8 + (param_1 & 0xff) * 0x2c))
              (param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10);
  }
  return;
}


// ================================================================================================
// sub_972ab @ 0x972ab [__watcall]
// ================================================================================================

undefined4 __watcall sub_972ab(void)

{
  sub_902a0();
  return 1;
}


// ================================================================================================
// sub_972b8 @ 0x972b8 [__watcall]
// ================================================================================================

void __watcall sub_972b8(void)

{
  sub_902a0();
  return;
}


// ================================================================================================
// sub_972c0 @ 0x972c0 [__watcall]
// ================================================================================================

void __watcall sub_972c0(void)

{
  sub_902a0();
  return;
}


// ================================================================================================
// sub_972c8 @ 0x972c8 [__watcall]
// ================================================================================================

undefined4 __watcall sub_972c8(void)

{
  sub_902a0();
  return 0xffffffff;
}


// ================================================================================================
// sub_972d5 @ 0x972d5 [__watcall]
// ================================================================================================

void __watcall sub_972d5(void)

{
  sub_902a0();
  return;
}


// ================================================================================================
// sub_972dd @ 0x972dd [__watcall]
// ================================================================================================

void __watcall sub_972dd(void)

{
  sub_902a0();
  return;
}


// ================================================================================================
// sub_972e5 @ 0x972e5 [__watcall]
// ================================================================================================

void __watcall sub_972e5(void)

{
  sub_902a0();
  return;
}


// ================================================================================================
// sub_972f0 @ 0x972f0 [__cdecl]
// ================================================================================================

undefined4 sub_972f0(undefined4 param_1)

{
  return param_1;
}


// ================================================================================================
// sub_972f5 @ 0x972f5 [__watcall]
// ================================================================================================

undefined4 __watcall sub_972f5(void)

{
  return 0;
}


// ================================================================================================
// sub_97300 @ 0x97300 [__watcall]
// ================================================================================================

undefined8 __watcall sub_97300(char *param_1,undefined4 unaff_EDX)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  char *pcVar4;
  
  iVar2 = sub_98a9f(param_1,aCopyright,9);
  if (iVar2 == 0) {
    uVar3 = 0xffffffff;
    pcVar4 = param_1;
    do {
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      cVar1 = *pcVar4;
      pcVar4 = pcVar4 + 1;
    } while (cVar1 != '\0');
    param_1 = param_1 + ~uVar3;
  }
  return CONCAT44(unaff_EDX,param_1);
}


// ================================================================================================
// sub_97334 @ 0x97334 [__watcall]
// ================================================================================================

int __watcall sub_97334(byte *param_1,int unaff_EDX)

{
  byte bVar1;
  int iVar2;
  
  iVar2 = 0;
  while (unaff_EDX = unaff_EDX + -1, unaff_EDX != -1) {
    bVar1 = *param_1;
    param_1 = param_1 + 1;
    iVar2 = iVar2 * 0x100 + (uint)bVar1;
  }
  return iVar2;
}


// ================================================================================================
// sub_97350 @ 0x97350 [__watcall]
// ================================================================================================

/* WARNING: Removing unreachable block (ram,0x0009752a) */
/* WARNING: Removing unreachable block (ram,0x000975b3) */

undefined8 __watcall
sub_97350(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  byte bVar1;
  byte *pbVar2;
  undefined4 uVar3;
  
  pbVar2 = (byte *)sub_97300(param_1,unaff_EDX,param_1,unaff_ECX,unaff_EDX,unaff_ECX,unaff_EBX);
  if (pbVar2[1] != 0xfb) {
    if ((((uint)*pbVar2 * 0x100 + (uint)pbVar2[1]) * 0x100 + (uint)pbVar2[2]) * 0x100 +
        (uint)pbVar2[3] == 0x3f3) {
      return CONCAT44(unaff_EDX,0x21);
    }
    uVar3 = 0;
    goto LAB_00097623;
  }
  bVar1 = *pbVar2 & 0xfe;
  if (bVar1 < 0x44) {
    if (bVar1 < 0x2c) {
      if (0x25 < bVar1) {
        if (0x26 < bVar1) {
          if (bVar1 < 0x28) goto LAB_000975e3;
          if (bVar1 < 0x29) goto LAB_00097578;
          if (bVar1 != 0x2a) {
            return CONCAT44(unaff_EDX,0x12);
          }
        }
        return CONCAT44(unaff_EDX,0x18);
      }
      if (bVar1 == 0x10) {
LAB_000974b8:
        return CONCAT44(unaff_EDX,0xc);
      }
    }
    else {
      if (bVar1 < 0x2d) {
        return CONCAT44(unaff_EDX,0x19);
      }
      if (bVar1 < 0x32) {
        if (0x2d < bVar1) {
          if (0x2e < bVar1) {
            if (bVar1 != 0x30) {
              return CONCAT44(unaff_EDX,0x12);
            }
            return CONCAT44(unaff_EDX,7);
          }
LAB_00097578:
          return CONCAT44(unaff_EDX,0x1a);
        }
      }
      else {
        if (bVar1 < 0x33) {
          return CONCAT44(unaff_EDX,9);
        }
        if (0x33 < bVar1) {
          if (bVar1 < 0x35) {
            return CONCAT44(unaff_EDX,10);
          }
          if (bVar1 != 0x42) {
            return CONCAT44(unaff_EDX,0x12);
          }
          goto LAB_0009758e;
        }
      }
    }
  }
  else {
    if (bVar1 < 0x45) {
LAB_0009758e:
      return CONCAT44(unaff_EDX,0x17);
    }
    if (bVar1 < 0x72) {
      if (bVar1 < 0x6a) {
        if (0x45 < bVar1) {
          if (bVar1 < 0x47) {
            return CONCAT44(unaff_EDX,5);
          }
          if (bVar1 != 0x66) {
            return CONCAT44(unaff_EDX,0x12);
          }
          return CONCAT44(unaff_EDX,0x1b);
        }
      }
      else {
        if (bVar1 < 0x6b) {
LAB_00097562:
          return CONCAT44(unaff_EDX,0x1f);
        }
        if (0x6d < bVar1) {
          if (bVar1 < 0x6f) {
            return CONCAT44(unaff_EDX,1);
          }
          if (bVar1 == 0x70) {
            return CONCAT44(unaff_EDX,0x11);
          }
          uVar3 = 0x12;
          goto LAB_00097623;
        }
      }
    }
    else {
      if (bVar1 < 0x73) {
        return CONCAT44(unaff_EDX,0xb);
      }
      if (bVar1 < 0x78) {
        if (0x73 < bVar1) {
          if (bVar1 < 0x75) {
            return CONCAT44(unaff_EDX,0x10);
          }
          if (bVar1 == 0x76) {
            uVar3 = 0x14;
            if ((pbVar2[5] == 1) && (pbVar2[6] == 1)) {
              uVar3 = 0x15;
            }
            if ((pbVar2[5] == 2) && (pbVar2[6] == 1)) {
              return CONCAT44(unaff_EDX,0x16);
            }
LAB_00097623:
            return CONCAT44(unaff_EDX,uVar3);
          }
        }
      }
      else {
        if (bVar1 < 0x79) goto LAB_000974b8;
        if (0x79 < bVar1) {
          if (bVar1 < 0x7b) {
            uVar3 = 2;
            if ((pbVar2[5] == 1) && (pbVar2[6] == 1)) {
              uVar3 = 3;
            }
            if ((pbVar2[5] == 2) && (pbVar2[6] == 1)) {
              return CONCAT44(unaff_EDX,4);
            }
            goto LAB_00097623;
          }
          if (bVar1 == 0xc0) goto LAB_00097562;
        }
      }
    }
  }
LAB_000975e3:
  return CONCAT44(unaff_EDX,0x12);
}


// ================================================================================================
// sub_9762c @ 0x9762c [__watcall]
// ================================================================================================

int __watcall sub_9762c(void)

{
  int iVar1;
  int iVar2;
  undefined8 uVar3;
  int in_stack_00000004;
  int in_stack_00000008;
  
  iVar1 = in_stack_00000008;
  if ((2 < in_stack_00000008) &&
     (iVar1 = (*(code *)funcptr_d3088)(in_stack_00000004,in_stack_00000008), iVar1 == 0)) {
    iVar2 = sub_97300(in_stack_00000004);
    iVar1 = in_stack_00000008 - (iVar2 - in_stack_00000004);
    uVar3 = sub_97350(iVar2);
    if ((0 < (int)uVar3) && ((int)uVar3 < 0x1f)) {
      iVar1 = sub_97334((int)((ulonglong)uVar3 >> 0x20) + 2,3);
      return iVar1;
    }
  }
  return iVar1;
}


// ================================================================================================
// sub_9767c @ 0x9767c [__watcall]
// ================================================================================================

undefined8 __watcall sub_9767c(int param_1,undefined4 unaff_EDX)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  undefined8 uVar4;
  
  if (param_1 < 0x11) {
    uVar3 = dword_edee4 >> (0x20 - (byte)param_1 & 0x1f);
    dword_edee4 = dword_edee4 << ((byte)param_1 & 0x1f);
    dword_edee0 = dword_edee0 - param_1;
    if (dword_edee0 < 0x10) {
      iVar2 = 0x18 - dword_edee0;
      do {
        bVar1 = *dword_edef0;
        dword_edef0 = dword_edef0 + 1;
        dword_edee4 = dword_edee4 | (uint)bVar1 << ((byte)iVar2 & 0x1f);
        iVar2 = iVar2 + -8;
        dword_edee0 = dword_edee0 + 8;
      } while (8 < iVar2);
    }
  }
  else {
    iVar2 = sub_9767c(param_1 + -0x10);
    uVar4 = sub_9767c(0x10,iVar2 << 0x10);
    uVar3 = (uint)uVar4 | (uint)((ulonglong)uVar4 >> 0x20);
  }
  return CONCAT44(unaff_EDX,uVar3);
}


// ================================================================================================
// sub_97714 @ 0x97714 [__watcall]
// ================================================================================================

undefined8 __watcall sub_97714(undefined4 param_1,undefined4 unaff_EDX)

{
  int iVar1;
  int iVar2;
  undefined8 uVar3;
  
  iVar2 = 2;
  iVar1 = 1;
  do {
    iVar2 = iVar2 * 2;
    uVar3 = sub_9767c(1,iVar1 + 1);
    iVar1 = (int)((ulonglong)uVar3 >> 0x20);
  } while ((int)uVar3 == 0);
  iVar1 = sub_9767c(iVar1);
  return CONCAT44(unaff_EDX,iVar1 + iVar2 + -4);
}


// ================================================================================================
// bitlz_decode @ 0x97740 [__watcall]
// ================================================================================================

int __watcall bitlz_decode(byte *param_1,char *unaff_EDX,int unaff_EBX)

{
  char cVar1;
  char cVar2;
  int iVar3;
  undefined4 uVar4;
  char *pcVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  undefined8 uVar12;
  char acStack_2e8 [256];
  char acStack_1e8 [256];
  int aiStack_e8 [16];
  int aiStack_a8 [16];
  uint auStack_68 [16];
  int local_28;
  int local_24;
  uint local_1c;
  
  local_24 = 0;
  dword_edee8 = unaff_EDX;
  dword_edef0 = param_1;
  if (param_1 != (byte *)0x0) {
    dword_edef0 = param_1 + 2;
    local_1c = (uint)*param_1 * 0x100 + (uint)param_1[1];
    if ((local_1c & 0x100) != 0) {
      dword_edef0 = param_1 + 5;
    }
    local_1c = local_1c & 0xfffffeff;
    iVar10 = 0;
    dword_edee0 = 0;
    dword_edee4 = 0;
    sub_9767c(0);
    local_24 = sub_9767c(0x18);
    if (unaff_EBX != 0) {
      cVar1 = sub_9767c(8);
      iVar7 = 0;
      local_28 = 0xf;
      iVar8 = 4;
      iVar9 = 1;
      do {
        iVar11 = iVar9;
        *(int *)((int)aiStack_a8 + iVar8) = iVar7 * 2 - iVar10;
        uVar12 = sub_97714();
        iVar3 = (int)uVar12;
        *(int *)((int)aiStack_e8 + iVar8) = iVar3;
        iVar10 = iVar10 + iVar3;
        iVar7 = (int)((ulonglong)uVar12 >> 0x20) + iVar3;
        uVar6 = 0;
        if (iVar3 != 0) {
          uVar6 = iVar7 << ((byte)local_28 & 0x1f) & 0xffff;
        }
        *(uint *)((int)auStack_68 + iVar8) = uVar6;
        local_28 = local_28 + -1;
        iVar8 = iVar8 + 4;
        iVar9 = iVar11 + 1;
      } while ((iVar3 == 0) || (uVar6 != 0));
      uVar4 = _memset_fill(acStack_2e8,0,iVar8,0x100);
      uVar6 = 0xffffffff;
      iVar9 = 0;
      if (0 < iVar10) {
        do {
          uVar12 = sub_97714(uVar4,uVar6);
          uVar6 = (uint)((ulonglong)uVar12 >> 0x20);
          iVar7 = (int)uVar12 + 1;
          while (iVar7 != 0) {
            uVar6 = uVar6 + 1 & 0xff;
            if (acStack_2e8[uVar6] == '\0') {
              iVar7 = iVar7 + -1;
            }
          }
          acStack_2e8[uVar6] = '\x01';
          acStack_1e8[iVar9] = (char)uVar6;
          iVar9 = iVar9 + 1;
          uVar4 = 0;
        } while (iVar9 < iVar10);
      }
      while( true ) {
        while( true ) {
          while( true ) {
            iVar10 = 1;
            uVar6 = auStack_68[1];
            for (iVar9 = 4;
                (uVar6 <= dword_edee4 >> 0x10 &&
                (SBORROW4(iVar9,iVar11 * 4) != iVar9 + iVar11 * -4 < 0)); iVar9 = iVar9 + 4) {
              iVar10 = iVar10 + 1;
              uVar6 = *(uint *)((int)auStack_68 + iVar9 + 4);
            }
            uVar12 = sub_9767c(iVar10);
            if (acStack_1e8[(int)uVar12 - aiStack_a8[(int)((ulonglong)uVar12 >> 0x20)]] == cVar1)
            break;
            *dword_edee8 = acStack_1e8[(int)uVar12 - aiStack_a8[(int)((ulonglong)uVar12 >> 0x20)]];
            dword_edee8 = dword_edee8 + 1;
          }
          iVar10 = sub_97714();
          if (iVar10 == 0) break;
          cVar2 = dword_edee8[-1];
          while (iVar10 = iVar10 + -1, iVar10 != -1) {
            *dword_edee8 = cVar2;
            dword_edee8 = dword_edee8 + 1;
          }
        }
        iVar10 = sub_9767c(1);
        if (iVar10 != 0) break;
        cVar2 = sub_9767c(8);
        *dword_edee8 = cVar2;
        dword_edee8 = dword_edee8 + 1;
      }
      pcVar5 = unaff_EDX + local_24;
      if (local_1c == 0x32fb) {
        cVar1 = '\0';
        dword_edee8 = unaff_EDX;
        if (unaff_EDX < pcVar5) {
          do {
            cVar1 = cVar1 + *dword_edee8;
            *dword_edee8 = cVar1;
            dword_edee8 = dword_edee8 + 1;
          } while (dword_edee8 < pcVar5);
        }
      }
      else if (local_1c == 0x34fb) {
        cVar2 = '\0';
        cVar1 = '\0';
        dword_edee8 = unaff_EDX;
        if (unaff_EDX < pcVar5) {
          do {
            cVar2 = cVar2 + *dword_edee8;
            cVar1 = cVar1 + cVar2;
            *dword_edee8 = cVar1;
            dword_edee8 = dword_edee8 + 1;
          } while (dword_edee8 < pcVar5);
        }
      }
    }
  }
  return local_24;
}


// ================================================================================================
// sub_979f8 @ 0x979f8 [__watcall]
// ================================================================================================

void __watcall sub_979f8(byte param_1)

{
  int extraout_EDX;
  
  while( true ) {
    if (*(char *)((uint)param_1 + dword_edef8) == '\0') break;
    sub_979f8(*(undefined *)((uint)param_1 + dword_edeec));
    param_1 = *(byte *)(extraout_EDX + dword_edef4);
  }
  *dword_edee8 = param_1;
  dword_edee8 = dword_edee8 + 1;
  return;
}


// ================================================================================================
// bytepair_decode @ 0x97a38 [__watcall]
// ================================================================================================

int __watcall bytepair_decode(byte *param_1,byte *unaff_EDX)

{
  byte bVar1;
  byte bVar2;
  undefined *puVar3;
  int iVar4;
  int extraout_EDX;
  byte *pbVar5;
  undefined auStack_318 [256];
  undefined local_218 [256];
  undefined local_118 [256];
  int local_18;
  
  dword_edef4 = auStack_318;
  local_18 = 0;
  dword_edef8 = local_118;
  dword_edeec = local_218;
  dword_edee8 = unaff_EDX;
  if (param_1 != (byte *)0x0) {
    pbVar5 = param_1 + 2;
    if ((uint)*param_1 * 0x100 + (uint)param_1[1] == 0x47fb) {
      pbVar5 = param_1 + 5;
    }
    local_18 = ((uint)*pbVar5 * 0x100 + (uint)pbVar5[1]) * 0x100 + (uint)pbVar5[2];
    iVar4 = 0;
    dword_edef4 = auStack_318;
    do {
      puVar3 = dword_edef8;
      dword_edef8[iVar4] = 0;
      iVar4 = iVar4 + 1;
    } while (iVar4 < 0x100);
    puVar3[pbVar5[3]] = 1;
    bVar2 = pbVar5[4];
    iVar4 = 0;
    dword_edef0 = pbVar5 + 5;
    if (bVar2 != 0) {
      do {
        bVar1 = *dword_edef0;
        pbVar5 = dword_edef0 + 2;
        dword_edeec[bVar1] = dword_edef0[1];
        dword_edef0 = dword_edef0 + 3;
        dword_edef4[bVar1] = *pbVar5;
        dword_edef8[bVar1] = 0xff;
        iVar4 = iVar4 + 1;
      } while (iVar4 < (int)(uint)bVar2);
    }
    while( true ) {
      while( true ) {
        while( true ) {
          bVar2 = *dword_edef0;
          pbVar5 = dword_edef0 + 1;
          if (dword_edef8[bVar2] != '\0') break;
          *dword_edee8 = bVar2;
          dword_edee8 = dword_edee8 + 1;
          dword_edef0 = pbVar5;
        }
        if (-1 < (char)dword_edef8[bVar2]) break;
        dword_edef0 = pbVar5;
        sub_979f8(dword_edeec[bVar2]);
        sub_979f8(dword_edef4[extraout_EDX]);
      }
      param_1 = dword_edef0 + 2;
      if (*pbVar5 == 0) break;
      *dword_edee8 = *pbVar5;
      dword_edee8 = dword_edee8 + 1;
      dword_edef0 = param_1;
    }
  }
  dword_edef0 = param_1;
  return local_18;
}


// ================================================================================================
// delta_decode @ 0x97bb8 [__watcall]
// ================================================================================================

int __watcall delta_decode(byte *param_1,char *unaff_EDX)

{
  char *pcVar1;
  byte bVar2;
  byte *pbVar3;
  byte *pbVar4;
  char cVar5;
  int iVar6;
  
  iVar6 = 0;
  if (param_1 != (byte *)0x0) {
    pbVar3 = param_1 + 2;
    iVar6 = (uint)*param_1 * 0x100 + (uint)param_1[1];
    if (iVar6 == 0x62fb) {
      pbVar3 = param_1 + 5;
    }
    else if (iVar6 == 0x66fb) {
      pbVar3 = param_1 + 6;
    }
    pbVar4 = pbVar3 + 3;
    iVar6 = ((uint)*pbVar3 * 0x100 + (uint)pbVar3[1]) * 0x100 + (uint)pbVar3[2];
    pcVar1 = unaff_EDX + iVar6;
    cVar5 = '\0';
    if (unaff_EDX < pcVar1) {
      do {
        bVar2 = *pbVar4;
        pbVar4 = pbVar4 + 1;
        cVar5 = cVar5 + bVar2;
        *unaff_EDX = cVar5;
        unaff_EDX = unaff_EDX + 1;
      } while (unaff_EDX < pcVar1);
    }
  }
  return iVar6;
}


// ================================================================================================
// pack7a_decode @ 0x97c2c [__watcall]
// ================================================================================================

int __watcall pack7a_decode(byte *param_1,byte *unaff_EDX)

{
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  int local_1c;
  
  local_1c = 0;
  if (param_1 != (byte *)0x0) {
    pbVar2 = param_1 + 2;
    if ((uint)*param_1 * 0x100 + (uint)param_1[1] == 0x7bfb) {
      pbVar2 = param_1 + 5;
    }
    local_1c = ((uint)*pbVar2 * 0x100 + (uint)pbVar2[1]) * 0x100 + (uint)pbVar2[2];
    uVar5 = (uint)pbVar2[3];
    bVar1 = pbVar2[4];
    pbVar2 = pbVar2 + 5;
    do {
      iVar6 = (int)(char)*pbVar2;
      uVar4 = (uint)bVar1;
      while( true ) {
        uVar4 = uVar4 - 1;
        pbVar2 = pbVar2 + 1;
        if (uVar4 == 0) break;
        iVar6 = iVar6 * 0x100 + (uint)*pbVar2;
      }
      if (iVar6 < 0) {
        iVar3 = -iVar6 * uVar5;
        do {
          *unaff_EDX = *pbVar2;
          pbVar2 = pbVar2 + 1;
          unaff_EDX = unaff_EDX + 1;
          iVar3 = iVar3 + -1;
        } while (iVar3 != 0);
      }
      else if (iVar6 != 0) {
        iVar3 = iVar6 + 1;
        uVar4 = uVar5;
        do {
          do {
            *unaff_EDX = *pbVar2;
            pbVar2 = pbVar2 + 1;
            unaff_EDX = unaff_EDX + 1;
            uVar4 = uVar4 - 1;
          } while (uVar4 != 0);
          pbVar2 = pbVar2 + -uVar5;
          iVar3 = iVar3 + -1;
          uVar4 = uVar5;
        } while (iVar3 != 0);
        pbVar2 = pbVar2 + uVar5;
      }
    } while (iVar6 != 0);
  }
  return local_1c;
}


// ================================================================================================
// refpack_decode @ 0x97ce0 [__watcall]
// ================================================================================================

int __watcall refpack_decode(byte *param_1,byte *unaff_EDX,int unaff_EBX)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  uint uVar5;
  byte *pbVar6;
  byte *pbVar7;
  uint uVar8;
  int iVar9;
  int local_1c;
  
  local_1c = 0;
  if (param_1 != (byte *)0x0) {
    pbVar6 = param_1 + 2;
    if (((uint)*param_1 * 0x100 + (uint)param_1[1] & 0x100) != 0) {
      pbVar6 = param_1 + 5;
    }
    pbVar7 = pbVar6 + 3;
    local_1c = ((uint)*pbVar6 * 0x100 + (uint)pbVar6[1]) * 0x100 + (uint)pbVar6[2];
    if (unaff_EBX != 0) {
      while( true ) {
        while( true ) {
          while( true ) {
            while( true ) {
              bVar2 = *pbVar7;
              uVar8 = (uint)bVar2;
              pbVar6 = pbVar7 + 1;
              uVar5 = uVar8 & 3;
              if ((bVar2 & 0x80) != 0) break;
              bVar3 = *pbVar6;
              pbVar7 = pbVar7 + 2;
              if ((bVar2 & 3) != 0) {
                do {
                  *unaff_EDX = *pbVar7;
                  pbVar7 = pbVar7 + 1;
                  unaff_EDX = unaff_EDX + 1;
                  uVar5 = uVar5 - 1;
                } while (uVar5 != 0);
              }
              pbVar6 = unaff_EDX + -((uVar8 & 0x60) * 8 + (uint)bVar3 + 1);
              iVar9 = ((uVar8 & 0x1c) >> 2) + 1;
              *unaff_EDX = *pbVar6;
              unaff_EDX[1] = pbVar6[1];
              pbVar6 = pbVar6 + 2;
              unaff_EDX = unaff_EDX + 2;
              do {
                *unaff_EDX = *pbVar6;
                pbVar6 = pbVar6 + 1;
                unaff_EDX = unaff_EDX + 1;
                iVar9 = iVar9 + -1;
              } while (iVar9 != 0);
            }
            if ((bVar2 & 0x40) != 0) break;
            bVar2 = *pbVar6;
            bVar3 = pbVar7[2];
            pbVar7 = pbVar7 + 3;
            for (uVar5 = (uint)(bVar2 >> 6); uVar5 != 0; uVar5 = uVar5 - 1) {
              *unaff_EDX = *pbVar7;
              pbVar7 = pbVar7 + 1;
              unaff_EDX = unaff_EDX + 1;
            }
            pbVar6 = unaff_EDX + -((bVar2 & 0x3f) * 0x100 + (uint)bVar3 + 1);
            iVar9 = (uVar8 & 0x3f) + 1;
            *unaff_EDX = *pbVar6;
            unaff_EDX[1] = pbVar6[1];
            unaff_EDX[2] = pbVar6[2];
            pbVar6 = pbVar6 + 3;
            unaff_EDX = unaff_EDX + 3;
            do {
              *unaff_EDX = *pbVar6;
              pbVar6 = pbVar6 + 1;
              unaff_EDX = unaff_EDX + 1;
              iVar9 = iVar9 + -1;
            } while (iVar9 != 0);
          }
          if ((bVar2 & 0x20) != 0) break;
          bVar3 = *pbVar6;
          bVar1 = pbVar7[2];
          bVar4 = pbVar7[3];
          pbVar7 = pbVar7 + 4;
          if ((bVar2 & 3) != 0) {
            do {
              *unaff_EDX = *pbVar7;
              pbVar7 = pbVar7 + 1;
              unaff_EDX = unaff_EDX + 1;
              uVar5 = uVar5 - 1;
            } while (uVar5 != 0);
          }
          pbVar6 = unaff_EDX +
                   -(((uVar8 & 0x10) >> 4) * 0x10000 + (uint)bVar3 * 0x100 + (uint)bVar1 + 1);
          iVar9 = ((uVar8 & 0xc) >> 2) * 0x100 + (uint)bVar4 + 1;
          *unaff_EDX = *pbVar6;
          unaff_EDX[1] = pbVar6[1];
          unaff_EDX[2] = pbVar6[2];
          unaff_EDX[3] = pbVar6[3];
          pbVar6 = pbVar6 + 4;
          unaff_EDX = unaff_EDX + 4;
          do {
            *unaff_EDX = *pbVar6;
            pbVar6 = pbVar6 + 1;
            unaff_EDX = unaff_EDX + 1;
            iVar9 = iVar9 + -1;
          } while (iVar9 != 0);
        }
        if (0xfb < uVar8) break;
        iVar9 = (uVar8 & 0x1f) + 1;
        pbVar7 = pbVar6;
        do {
          *unaff_EDX = *pbVar7;
          unaff_EDX[1] = pbVar7[1];
          unaff_EDX[2] = pbVar7[2];
          unaff_EDX[3] = pbVar7[3];
          pbVar7 = pbVar7 + 4;
          unaff_EDX = unaff_EDX + 4;
          iVar9 = iVar9 + -1;
        } while (iVar9 != 0);
      }
      if ((bVar2 & 3) != 0) {
        do {
          *unaff_EDX = *pbVar6;
          pbVar6 = pbVar6 + 1;
          unaff_EDX = unaff_EDX + 1;
          uVar5 = uVar5 - 1;
        } while (uVar5 != 0);
      }
    }
  }
  return local_1c;
}


// ================================================================================================
// unpack @ 0x97eb8 [__cdecl]
// ================================================================================================

int unpack(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  byte bVar1;
  int iVar2;
  byte *pbVar3;
  int local_10;
  
  iVar2 = (*(code *)funcptr_d308c)(param_1,param_2,param_3);
  if (iVar2 != 0) {
    return iVar2;
  }
  local_10 = sub_9762c();
  pbVar3 = (byte *)sub_97300(param_1);
  iVar2 = 0;
  if (pbVar3[1] != 0xfb) goto LAB_00098009;
  bVar1 = *pbVar3 & 0xfe;
  if (0x5f < bVar1) {
    if (0x60 < bVar1) {
      if (0x69 < bVar1) {
        if (bVar1 < 0x6b) {
LAB_00097fcb:
          sub_b3abc(pbVar3 + 5,param_2,local_10);
          iVar2 = local_10;
          goto LAB_00098009;
        }
        if (bVar1 < 0x72) {
          if (bVar1 == 0x6e) goto LAB_00097fcb;
        }
        else {
          if (bVar1 < 0x73) goto LAB_00097fbe;
          if ((0x79 < bVar1) && (bVar1 < 0x7c)) {
            local_10 = pack7a_decode(pbVar3,param_2);
            goto LAB_00098009;
          }
        }
        goto LAB_00097fef;
      }
      if ((bVar1 < 0x62) || ((0x62 < bVar1 && (bVar1 != 0x66)))) goto LAB_00097fef;
    }
LAB_00097fbe:
    iVar2 = delta_decode(pbVar3,param_2);
    goto LAB_00098009;
  }
  if (bVar1 < 0x32) {
    if (0xf < bVar1) {
      if (bVar1 < 0x11) {
        iVar2 = refpack_decode(pbVar3,param_2,1);
        goto LAB_00098009;
      }
      if (bVar1 == 0x30) goto LAB_00097f9f;
    }
  }
  else {
    if (bVar1 < 0x33) {
LAB_00097f9f:
      iVar2 = bitlz_decode(pbVar3,param_2,1);
      goto LAB_00098009;
    }
    if (0x33 < bVar1) {
      if (bVar1 < 0x35) goto LAB_00097f9f;
      if (bVar1 == 0x46) {
        iVar2 = bytepair_decode(pbVar3,param_2);
        goto LAB_00098009;
      }
    }
  }
LAB_00097fef:
  if (param_4 != 0) {
    fatalerror(s_funpack___INVALID_PACK_CODE___x__000c47c2 + 2,*pbVar3);
  }
LAB_00098009:
  if (iVar2 == 0) {
    sub_b3abc(pbVar3,param_2,local_10);
    iVar2 = local_10;
  }
  return iVar2;
}


// ================================================================================================
// sub_98028 @ 0x98028 [__cdecl]
// ================================================================================================

void sub_98028(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  unpack(param_1,param_2,param_3,1);
  return;
}


// ================================================================================================
// sub_98044 @ 0x98044 [__watcall]
// ================================================================================================

void __watcall sub_98044(void)

{
  undefined4 in_stack_00000004;
  undefined4 in_stack_00000008;
  undefined4 in_stack_0000000c;
  
  unpack(in_stack_00000004,in_stack_00000008,in_stack_0000000c,0);
  return;
}


// ================================================================================================
// sub_9805e @ 0x9805e [__watcall]
// ================================================================================================

undefined8 __watcall
sub_9805e(undefined2 *param_1,undefined4 unaff_EDX,undefined2 *unaff_EBX,short unaff_CX,uint param_5
         )

{
  undefined2 *puVar1;
  uint uVar2;
  int in_FS_OFFSET;
  
  if ((unaff_EBX != param_1) || (unaff_CX != (short)unaff_EDX)) {
    if ((unaff_EBX < param_1) &&
       (puVar1 = (undefined2 *)((int)unaff_EBX + param_5), param_1 < puVar1)) {
      param_1 = (undefined2 *)((int)param_1 + param_5);
      for (; param_5 != 0; param_5 = param_5 - 1) {
        puVar1 = (undefined2 *)((int)puVar1 - 1);
        param_1 = (undefined2 *)((int)param_1 + -1);
        *(undefined *)(in_FS_OFFSET + (int)param_1) = *(undefined *)puVar1;
      }
    }
    else {
      puVar1 = param_1;
      for (uVar2 = param_5 >> 1; uVar2 != 0; uVar2 = uVar2 - 1) {
        *puVar1 = *unaff_EBX;
        unaff_EBX = unaff_EBX + 1;
        puVar1 = puVar1 + 1;
      }
      for (uVar2 = (uint)((param_5 & 1) != 0); uVar2 != 0; uVar2 = uVar2 - 1) {
        *(undefined *)puVar1 = *(undefined *)unaff_EBX;
        unaff_EBX = (undefined2 *)((int)unaff_EBX + 1);
        puVar1 = (undefined2 *)((int)puVar1 + 1);
      }
    }
  }
  return CONCAT44(unaff_EDX,param_1);
}


// ================================================================================================
// sub_980e5 @ 0x980e5 [__watcall]
// ================================================================================================

char * __watcall sub_980e5(uint param_1,char *unaff_EDX,uint unaff_EBX)

{
  char cVar1;
  uint uVar2;
  char *pcVar3;
  char *pcVar4;
  char local_37 [35];
  
  pcVar3 = local_37;
  do {
    uVar2 = param_1 / unaff_EBX;
    *pcVar3 = "0123456789abcdefghijklmnopqrstuvwxyz"[param_1 % unaff_EBX];
    pcVar3 = pcVar3 + 1;
    param_1 = uVar2;
    pcVar4 = unaff_EDX;
  } while (uVar2 != 0);
  do {
    pcVar3 = pcVar3 + -1;
    cVar1 = *pcVar3;
    *pcVar4 = cVar1;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  return unaff_EDX;
}


// ================================================================================================
// sub_9812f @ 0x9812f [__watcall]
// ================================================================================================

undefined * __watcall sub_9812f(int param_1,undefined *unaff_EDX,int unaff_EBX)

{
  if ((unaff_EBX == 10) && (param_1 < 0)) {
    param_1 = -param_1;
    *unaff_EDX = 0x2d;
  }
  sub_980e5(param_1);
  return unaff_EDX;
}


// ================================================================================================
// sub_9814a @ 0x9814a [__watcall]
// ================================================================================================

char * __watcall sub_9814a(char *param_1,int unaff_EDX,int unaff_EBX)

{
  uint uVar1;
  int iVar2;
  char *pcVar3;
  bool bVar4;
  undefined8 uVar5;
  int local_14;
  
  uVar1 = *(uint *)(unaff_EBX + 0xc);
  *(byte *)(unaff_EBX + 0xc) = *(byte *)(unaff_EBX + 0xc) & 0xcf;
  pcVar3 = param_1;
  do {
    uVar5 = CONCAT44(pcVar3,local_14);
    unaff_EDX = unaff_EDX + -1;
    if (unaff_EDX < 1) break;
    uVar5 = sub_9b833(unaff_EBX);
    pcVar3 = (char *)((ulonglong)uVar5 >> 0x20);
    iVar2 = (int)uVar5;
    if (iVar2 == -1) break;
    local_14._0_1_ = (char)uVar5;
    *pcVar3 = (char)local_14;
    pcVar3 = pcVar3 + 1;
    uVar5 = CONCAT44(pcVar3,iVar2);
    bVar4 = (char)local_14 != '\n';
    local_14 = iVar2;
  } while (bVar4);
  pcVar3 = (char *)((ulonglong)uVar5 >> 0x20);
  local_14 = (int)uVar5;
  if ((local_14 == -1) && ((pcVar3 == param_1 || ((*(byte *)(unaff_EBX + 0xc) & 0x20) != 0)))) {
    param_1 = (char *)0x0;
  }
  else {
    *pcVar3 = '\0';
  }
  *(uint *)(unaff_EBX + 0xc) = *(uint *)(unaff_EBX + 0xc) | uVar1 & 0x30;
  return param_1;
}


// ================================================================================================
// sub_981ad @ 0x981ad [__watcall]
// ================================================================================================

void __watcall sub_981ad(void)

{
  return;
}


// ================================================================================================
// sub_981b0 @ 0x981b0 [__watcall]
// ================================================================================================

void __watcall sub_981b0(int param_1,undefined4 unaff_EDX,undefined4 unaff_EBX)

{
  setdefaultscreen();
  grabshape(*(undefined4 *)(param_1 + 0x2c),unaff_EDX,unaff_EBX);
  return;
}


// ================================================================================================
// sub_981d4 @ 0x981d4 [__watcall]
// ================================================================================================

void __watcall sub_981d4(int param_1,undefined4 unaff_EDX,undefined4 unaff_EBX)

{
  setdefaultscreen();
  drawshape2(*(undefined4 *)(param_1 + 0x2c),unaff_EDX,unaff_EBX);
  return;
}


// ================================================================================================
// sub_981f8 @ 0x981f8 [__watcall]
// ================================================================================================

uint __watcall
sub_981f8(undefined4 param_1,int param_2,int unaff_EBX,int unaff_ECX,int param_5,uint param_6)

{
  undefined4 uVar1;
  uint uVar2;
  uint uVar3;
  undefined auStack_cc [96];
  undefined local_6c [64];
  int local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  
  dword_d2fd8 = 1;
  local_28 = param_1;
  (*(code *)funcptr_d45b4)();
  local_24 = sub_9c5a8();
  sub_9c5a8();
  uVar1 = windowdefp(unaff_ECX,param_5,0);
  local_20 = uVar1;
  sub_b3a88(auStack_cc);
  getfontstate(local_6c);
  setfont(&unk_d45d8);
  local_2c = param_2 + unaff_ECX;
  sub_b6f84(&dword_d30d4,param_2,local_2c,unaff_EBX,unaff_EBX + param_5);
  (*(code *)funcptr_d3070)();
  setscreen(uVar1);
  sub_981b0(uVar1,param_2,unaff_EBX);
  setdefaultscreen();
  uVar1 = sub_9c5b0(0);
  fillrect(param_2,unaff_EBX,unaff_ECX,param_5,uVar1);
  uVar1 = sub_9c5b0(0xa80000);
  sub_93000(param_2 + 4,unaff_EBX + 4,local_2c + -5,unaff_EBX + param_5 + -4,uVar1);
  uVar1 = sub_9c5b0(0xfcfcfc,0);
  settextpos(uVar1);
  sub_a1800(local_28,unaff_EBX + 9);
  (*(code *)funcptr_d3074)();
  sub_a1840(&dword_d30d4);
  do {
    uVar2 = (*(code *)mouse_update_callback)();
  } while ((uVar2 & param_6) != 0);
  do {
    uVar2 = sub_b39d0();
    uVar3 = (*(code *)mouse_update_callback)();
    if (uVar2 != 0) break;
  } while ((uVar3 & param_6) == 0);
  uVar3 = uVar3 & param_6 & 1;
  if ((uVar2 | 0x20) == 0x79) {
    uVar3 = 1;
  }
  sub_b6f84(&dword_d30d4,param_2,param_2 + unaff_ECX,unaff_EBX,unaff_EBX + param_5);
  (*(code *)funcptr_d306c)();
  sub_981d4(local_20,param_2,unaff_EBX);
  (*(code *)funcptr_d3074)();
  setfontstate(local_6c);
  sub_b3aa1(auStack_cc);
  sub_9132c(local_20);
  sub_9c5a8();
  (*(code *)funcptr_d45b8)();
  dword_d2fd8 = 0;
  return uVar3;
}


// ================================================================================================
// sub_984a8 @ 0x984a8 [__watcall]
// ================================================================================================

void __watcall sub_984a8(void)

{
  int iVar1;
  
  iVar1 = sub_981f8(aEXITTODOSYN,0x50,0x58,0xa0,0x18,7);
  if (iVar1 != 0) {
    (*(code *)funcptr_d41f0)();
  }
  return;
}


// ================================================================================================
// sub_984d0 @ 0x984d0 [__cdecl]
// ================================================================================================

void sub_984d0(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined auStack_a8 [96];
  undefined local_48 [64];
  
  dword_d2fd8 = 1;
  sub_9c5a8();
  sub_9c5a8();
  uVar1 = windowdefp(0x140,10,0);
  sub_b3a88(auStack_a8);
  getfontstate(local_48);
  setfont(&unk_d45d8);
  setscreen(uVar1);
  sub_b6f84(&dword_d30d4,0,0x140,0xbe,200);
  (*(code *)funcptr_d3070)();
  sub_981b0(uVar1,0,0xbe);
  setdefaultscreen();
  uVar2 = sub_9c5b0(0);
  fillrect(0,0xbe,0x140,10,uVar2);
  uVar2 = sub_9c5b0(0xfcfcfc,0);
  settextpos(uVar2);
  sub_a1800(param_1,0xbf);
  (*(code *)funcptr_d3074)();
  sub_b3d74(param_2);
  (*(code *)funcptr_d306c)();
  sub_981d4(uVar1,0,0xbe);
  (*(code *)funcptr_d3074)();
  setfontstate(local_48);
  sub_b3aa1(auStack_a8);
  sub_9132c(uVar1);
  sub_9c5a8();
  dword_d2fd8 = 0;
  return;
}


// ================================================================================================
// debug_pause @ 0x9862c [__watcall]
// ================================================================================================

void __watcall debug_pause(void)

{
  sub_981f8(s_izPAUSE___PRESS_ANY_KEY_TO_RESUM_000c47fa + 2,0x10,0x58,0x120,0x18,1);
  return;
}


// ================================================================================================
// sub_9864c @ 0x9864c [__watcall]
// ================================================================================================

undefined6 __watcall sub_9864c(undefined4 param_1,undefined4 param_2,undefined4 unaff_EBX)

{
  code *pcVar1;
  undefined2 in_ES;
  
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  return CONCAT24(in_ES,unaff_EBX);
}


// ================================================================================================
// sub_98664 @ 0x98664 [__watcall]
// ================================================================================================

undefined8 __watcall sub_98664(undefined4 param_1)

{
  code *pcVar1;
  undefined4 unaff_EBP;
  
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  return CONCAT44(param_1,unaff_EBP);
}


// ================================================================================================
// sub_98683 @ 0x98683 [__watcall]
// ================================================================================================

void __watcall sub_98683(undefined4 param_1,undefined4 unaff_EDX)

{
  int iVar1;
  undefined4 *puVar2;
  undefined2 in_DS;
  undefined4 uStack_c;
  
  puVar2 = &uStack_c;
  uStack_c = 0x98690;
  iVar1 = sub_a1877(param_1,in_DS);
  if (iVar1 == 0) {
                    /* WARNING: Subroutine does not return */
    *(undefined4 *)((int)puVar2 + -4) = 0x9869d;
    sub_90267(param_1,unaff_EDX);
  }
  return;
}


// ================================================================================================
// unk_986a0 @ 0x986a0
// ================================================================================================

void unk_986a0(void)

{
  return;
}


// ================================================================================================
// sub_986b0 @ 0x986b0 [__watcall]
// ================================================================================================

undefined4 * __watcall sub_986b0(void)

{
  dword_edefc = 0;
  return &dword_edefc;
}


// ================================================================================================
// memman_lock @ 0x986c0 [__cdecl]
// ================================================================================================

void memman_lock(undefined4 *param_1)

{
  *param_1 = 1;
  return;
}


// ================================================================================================
// sub_986cc @ 0x986cc [__cdecl]
// ================================================================================================

undefined4 sub_986cc(int *param_1)

{
  if (*param_1 != 0) {
    return 0;
  }
  *param_1 = 1;
  return 1;
}


// ================================================================================================
// memman_unlock @ 0x986e4 [__cdecl]
// ================================================================================================

void memman_unlock(undefined4 *param_1)

{
  *param_1 = 0;
  return;
}


// ================================================================================================
// sub_986ef @ 0x986ef [__watcall]
// ================================================================================================

void __watcall
sub_986ef(undefined4 *param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  sub_9b3ca(unaff_EDX,*param_1,param_1,unaff_ECX,unaff_EBX);
  param_1[4] = param_1[4] + 1;
  return;
}


// ================================================================================================
// vfprintf @ 0x98700 [__cdecl]
// ================================================================================================

int __watcall vfprintf(FILE *__s,char *__format,__gnuc_va_list __arg)

{
  char *pcVar1;
  int iVar2;
  byte bVar3;
  int extraout_EDX;
  bool bVar4;
  
  pcVar1 = __s->_IO_read_base;
  *(byte *)&__s->_IO_read_base = *(byte *)&__s->_IO_read_base & 0xcf;
  if (__s->_IO_read_end == (char *)0x0) {
    sub_9b353(__s);
  }
  bVar3 = *(byte *)((int)&__s->_IO_read_base + 1);
  bVar4 = (bVar3 & 4) != 0;
  if (bVar4) {
    bVar3 = bVar3 & 0xfa;
    *(byte *)((int)&__s->_IO_read_base + 1) = bVar3;
    *(byte *)((int)&__s->_IO_read_base + 1) = bVar3 | 1;
  }
  iVar2 = __prtf(__s);
  if (bVar4) {
    bVar3 = *(byte *)((int)&__s->_IO_read_base + 1);
    *(byte *)((int)&__s->_IO_read_base + 1) = bVar3 & 0xfa;
    *(byte *)((int)&__s->_IO_read_base + 1) = bVar3 & 0xfa | 4;
    sub_9b232(__s);
    iVar2 = extraout_EDX;
  }
  if ((*(byte *)&__s->_IO_read_base & 0x20) != 0) {
    iVar2 = -1;
  }
  __s->_IO_read_base = (char *)((uint)__s->_IO_read_base | (uint)pcVar1 & 0x30);
  return iVar2;
}


// ================================================================================================
// sub_9878a @ 0x9878a [__watcall]
// ================================================================================================

void __watcall
sub_9878a(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  undefined8 uVar1;
  
  uVar1 = sub_9d66b(param_1,param_1,unaff_EBX,unaff_ECX,unaff_EDX);
  *(undefined4 *)uVar1 = (int)((ulonglong)uVar1 >> 0x20);
  return;
}


// ================================================================================================
// sub_98796 @ 0x98796 [__watcall]
// ================================================================================================

void __watcall sub_98796(void)

{
  sub_9878a(0xe);
  return;
}


// ================================================================================================
// sub_9879d @ 0x9879d [__watcall]
// ================================================================================================

undefined4 __watcall sub_9879d(void)

{
  sub_9878a(9);
  return 0xffffffff;
}


// ================================================================================================
// sub_987ad @ 0x987ad [__watcall]
// ================================================================================================

void __watcall
sub_987ad(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  undefined8 uVar1;
  
  uVar1 = sub_9d671(param_1,param_1,unaff_EBX,unaff_ECX,unaff_EDX);
  *(undefined4 *)uVar1 = (int)((ulonglong)uVar1 >> 0x20);
  return;
}


// ================================================================================================
// sub_987b9 @ 0x987b9 [__watcall]
// ================================================================================================

void __watcall sub_987b9(void)

{
  (*(code *)funcptr_d4d11)();
  return;
}


// ================================================================================================
// segread @ 0x987c0 [__watcall]
// ================================================================================================

void __watcall segread(undefined2 *param_1)

{
  undefined2 in_ES;
  undefined2 in_CS;
  undefined2 in_SS;
  undefined2 in_DS;
  undefined2 in_FS;
  undefined2 in_GS;
  
  param_1[1] = in_CS;
  param_1[3] = in_DS;
  *param_1 = in_ES;
  param_1[2] = in_SS;
  param_1[4] = in_FS;
  param_1[5] = in_GS;
  return;
}


// ================================================================================================
// int386x @ 0x987e8 [__watcall]
// ================================================================================================

undefined4 __watcall
int386x(undefined4 param_1,undefined4 param_2,undefined4 *unaff_EBX,undefined4 unaff_ECX)

{
  sub_a189e(param_1,unaff_EBX,unaff_ECX);
  return *unaff_EBX;
}


// ================================================================================================
// sub_98801 @ 0x98801 [__watcall]
// ================================================================================================

undefined4 __watcall sub_98801(undefined4 param_1,undefined4 unaff_EDX)

{
  bool bVar1;
  byte bVar2;
  int iVar3;
  undefined2 in_DS;
  undefined4 uStack_18;
  byte local_14;
  
  local_14 = local_14 & 0xfe;
  while( true ) {
    iVar3 = sub_98839(in_DS,param_1,unaff_EDX,&uStack_18);
    bVar2 = local_14;
    if (iVar3 == 0) {
      return param_1;
    }
    if (iVar3 == 1) break;
    if (((byte_d4d06 == '\x01') && (byte_d4d07 == '\0')) || (byte_d4d06 == '\t')) {
      bVar1 = false;
    }
    else {
      bVar1 = true;
    }
    if (!bVar1) {
      return 0;
    }
    if (iVar3 == 2) {
      if (((local_14 & 1) != 0) || (iVar3 = sub_9adf2(uStack_18), iVar3 == 0)) {
        return 0;
      }
      local_14 = bVar2 | 1;
    }
  }
  return 0;
}


// ================================================================================================
// sub_98839 @ 0x98839 [__watcall]
// ================================================================================================

undefined4 __watcall sub_98839(short param_1,uint unaff_EDX,uint unaff_EBX,uint *unaff_ECX)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint *puVar6;
  undefined4 uVar7;
  uint unaff_ESI;
  short in_DS;
  
  uVar3 = unaff_EBX + 7 & 0xfffffffc;
  if (uVar3 < unaff_EBX) {
    uVar3 = 0xffffffff;
  }
  if (uVar3 < 0xc) {
    uVar3 = 0xc;
  }
  puVar1 = (uint *)(unaff_EDX - 4);
  uVar5 = *puVar1 & 0xfffffffe;
  if (uVar5 < uVar3) {
    uVar3 = uVar3 - uVar5;
    puVar6 = (uint *)((int)puVar1 + uVar5);
    while( true ) {
      *unaff_ECX = uVar3;
      uVar5 = *puVar6;
      if (uVar5 == 0xffffffff) break;
      if ((uVar5 & 1) != 0) {
        return 1;
      }
      uVar3 = puVar6[2];
      uVar2 = puVar6[1];
      uVar4 = dword_d43e8;
      if (in_DS == param_1) {
        for (; (unaff_ESI = uVar4, *(uint *)(uVar4 + 8) != 0 &&
               ((unaff_EDX < uVar4 || (*(uint *)(uVar4 + 8) <= unaff_EDX))));
            uVar4 = *(uint *)(uVar4 + 8)) {
        }
      }
      if (puVar6 == *(uint **)(unaff_ESI + 0xc)) {
        *(uint *)(unaff_ESI + 0xc) = (*(uint **)(unaff_ESI + 0xc))[1];
      }
      if (*unaff_ECX <= uVar5) {
        uVar4 = uVar5 - *unaff_ECX;
        if (0xb < uVar4) {
          puVar6 = (uint *)((int)puVar6 + *unaff_ECX);
          *puVar6 = uVar4;
          puVar6[1] = uVar2;
          puVar6[2] = uVar3;
          *(uint **)(uVar2 + 8) = puVar6;
          *(uint **)(uVar3 + 4) = puVar6;
          *puVar1 = *puVar1 + *unaff_ECX;
          byte_f24c4 = 0;
          return 0;
        }
      }
      *(uint *)(uVar2 + 8) = uVar3;
      *(uint *)(uVar3 + 4) = uVar2;
      *puVar1 = *puVar1 + uVar5;
      *(int *)(unaff_ESI + 0x1c) = *(int *)(unaff_ESI + 0x1c) + -1;
      byte_f24c4 = 0;
      if (*unaff_ECX <= uVar5) goto LAB_000989bd;
      uVar3 = *unaff_ECX - uVar5;
      puVar6 = (uint *)((int)puVar6 + uVar5);
    }
    uVar7 = 2;
  }
  else {
    if (0xb < uVar5 - uVar3) {
      *puVar1 = uVar3 | 1;
      *(uint *)((int)puVar1 + uVar3) = uVar5 - uVar3 | 1;
      uVar5 = dword_d43e8;
      if (in_DS == param_1) {
        for (; (unaff_ESI = uVar5, *(uint *)(uVar5 + 8) != 0 &&
               ((unaff_EDX < uVar5 || (*(uint *)(uVar5 + 8) <= unaff_EDX))));
            uVar5 = *(uint *)(uVar5 + 8)) {
        }
      }
      *(int *)(unaff_ESI + 0x18) = *(int *)(unaff_ESI + 0x18) + 1;
      sub_91a67((uint *)((int)puVar1 + uVar3) + 1);
    }
LAB_000989bd:
    uVar7 = 0;
  }
  return uVar7;
}


// ================================================================================================
// sub_989c8 @ 0x989c8 [__watcall]
// ================================================================================================

void __watcall sub_989c8(int param_1)

{
  bool bVar1;
  int iVar2;
  undefined2 in_DS;
  undefined4 unaff_retaddr;
  byte in_stack_00000004;
  
  do {
    if (param_1 == 1) {
      return;
    }
    if (((byte_d4d06 == '\x01') && (byte_d4d07 == '\0')) || (byte_d4d06 == '\t')) {
      bVar1 = false;
    }
    else {
      bVar1 = true;
    }
    if (!bVar1) {
      return;
    }
    if (param_1 == 2) {
      if ((in_stack_00000004 & 1) != 0) {
        return;
      }
      iVar2 = sub_9adf2(unaff_retaddr);
      if (iVar2 == 0) {
        return;
      }
      in_stack_00000004 = in_stack_00000004 | 1;
    }
    param_1 = sub_98839(in_DS);
    if (param_1 == 0) {
      return;
    }
  } while( true );
}


// ================================================================================================
// sub_98a2b @ 0x98a2b [__watcall]
// ================================================================================================

int __watcall sub_98a2b(int param_1)

{
  return (*(uint *)(param_1 + -4) & 0xfffffffe) - 4;
}


// ================================================================================================
// sub_98a40 @ 0x98a40 [__cdecl]
// ================================================================================================

int sub_98a40(undefined4 param_1)

{
  undefined auStack_c [4];
  undefined local_8 [4];
  int local_4;
  
  sub_b3b2e(param_1,&local_4,local_8,auStack_c);
  closehandle(local_4);
  if (local_4 != 0) {
    local_4 = 1;
  }
  return local_4;
}


// ================================================================================================
// sub_98a81 @ 0x98a81 [__cdecl]
// ================================================================================================

void sub_98a81(undefined4 param_1,undefined4 param_2)

{
  sub_a1cf4(param_1,param_2,&stack0x0000000c,dword_d5444);
  return;
}


// ================================================================================================
// sub_98a9f @ 0x98a9f [__watcall]
// ================================================================================================

int __watcall sub_98a9f(byte *param_1,byte *unaff_EDX,int unaff_EBX)

{
  while( true ) {
    if (unaff_EBX == 0) {
      return 0;
    }
    if (*param_1 != *unaff_EDX) break;
    if (*param_1 == 0) {
      return 0;
    }
    param_1 = param_1 + 1;
    unaff_EDX = unaff_EDX + 1;
    unaff_EBX = unaff_EBX + -1;
  }
  return (uint)*param_1 - (uint)*unaff_EDX;
}


// ================================================================================================
// sub_98ac8 @ 0x98ac8 [__watcall]
// ================================================================================================

void __watcall sub_98ac8(undefined4 param_1,undefined4 unaff_EDX)

{
  code *pcVar1;
  
  if ((1 < byte_d4d06) && (byte_d4d06 < 9)) {
    pcVar1 = (code *)swi(0x21);
    (*pcVar1)();
    return;
  }
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)(unaff_EDX);
  return;
}


// ================================================================================================
// sub_98af3 @ 0x98af3 [__watcall]
// ================================================================================================

undefined6 __watcall
sub_98af3(undefined4 param_1,undefined4 param_2,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  code *pcVar1;
  undefined2 in_ES;
  
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)(unaff_ECX,unaff_EBX);
  return CONCAT24(in_ES,param_1);
}


// ================================================================================================
// sub_98b30 @ 0x98b30 [__cdecl]
// ================================================================================================

void sub_98b30(undefined4 param_1,undefined4 *param_2)

{
  int iVar1;
  int iVar2;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  
  iVar1 = sub_b6ffc();
  iVar2 = sub_b7005();
  local_28 = 1;
  local_24 = 1;
  local_20 = iVar1 + -3;
  local_1c = 1;
  iVar2 = iVar2 + -3;
  local_18 = local_20;
  local_14 = iVar2;
  local_10 = local_20;
  sub_a2000(param_1,&local_28,param_2);
  local_28 = local_10;
  local_20 = 1;
  local_18 = 1;
  local_14 = 1;
  local_40 = param_2[4];
  local_3c = param_2[5];
  local_38 = param_2[6];
  local_34 = param_2[7];
  local_30 = *param_2;
  local_2c = param_2[1];
  local_24 = iVar2;
  local_1c = iVar2;
  sub_a2000(param_1,&local_28,&local_40);
  return;
}


// ================================================================================================
// sub_98bec @ 0x98bec [__watcall]
// ================================================================================================

void __watcall sub_98bec(void)

{
  int iVar1;
  undefined4 in_stack_00000004;
  int in_stack_00000008;
  int *in_stack_0000000c;
  int local_40;
  int local_3c;
  int local_38;
  int local_34;
  int local_30;
  int local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  int local_10;
  
  local_10 = sub_b6ffc();
  iVar1 = sub_b7005();
  local_40 = 1;
  local_3c = 1;
  local_38 = local_10 + -2;
  local_34 = 1;
  iVar1 = iVar1 + -2;
  local_28 = *(undefined4 *)(in_stack_00000008 + *in_stack_0000000c * 8);
  local_24 = *(undefined4 *)(in_stack_00000008 + 4 + *in_stack_0000000c * 8);
  local_20 = *(undefined4 *)(in_stack_00000008 + in_stack_0000000c[1] * 8);
  local_1c = *(undefined4 *)(in_stack_00000008 + 4 + in_stack_0000000c[1] * 8);
  local_18 = *(undefined4 *)(in_stack_00000008 + in_stack_0000000c[2] * 8);
  local_14 = *(undefined4 *)(in_stack_00000008 + 4 + in_stack_0000000c[2] * 8);
  local_30 = local_38;
  local_2c = iVar1;
  local_10 = local_38;
  sub_a2000(in_stack_00000004,&local_40,&local_28);
  local_40 = local_10;
  local_38 = 1;
  local_30 = 1;
  local_2c = 1;
  local_28 = *(undefined4 *)(in_stack_00000008 + in_stack_0000000c[2] * 8);
  local_24 = *(undefined4 *)(in_stack_00000008 + 4 + in_stack_0000000c[2] * 8);
  local_20 = *(undefined4 *)(in_stack_00000008 + in_stack_0000000c[3] * 8);
  local_1c = *(undefined4 *)(in_stack_00000008 + 4 + in_stack_0000000c[3] * 8);
  local_18 = *(undefined4 *)(in_stack_00000008 + *in_stack_0000000c * 8);
  local_14 = *(undefined4 *)(in_stack_00000008 + 4 + *in_stack_0000000c * 8);
  local_3c = iVar1;
  local_34 = iVar1;
  sub_a2000(in_stack_00000004,&local_40,&local_28);
  return;
}


// ================================================================================================
// sub_98d20 @ 0x98d20 [__watcall]
// ================================================================================================

int * __watcall sub_98d20(int param_1,int unaff_EDX,int unaff_EBX)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  
  piVar3 = (int *)0x0;
  if (dword_d2f60 < dword_edaa8) {
    piVar1 = dword_d2f60;
    do {
      if (unaff_EBX <= *piVar1) {
        if (piVar1[1] == 0) {
          if (piVar3 == (int *)0x0) {
            piVar3 = piVar1;
          }
        }
        else if ((param_1 == piVar1[2]) && (piVar1[3] == param_1 + unaff_EDX)) {
          piVar1[1] = piVar1[1] + 1;
          return piVar1 + 2;
        }
      }
      piVar1 = piVar1 + *piVar1 + 2;
    } while (piVar1 < dword_edaa8);
  }
  if (piVar3 == (int *)0x0) {
    return (int *)0x0;
  }
  iVar4 = *piVar3;
  if (unaff_EBX + 8 <= iVar4) {
    piVar3[unaff_EBX + 2] = (iVar4 - unaff_EBX) + -2;
    piVar3[unaff_EBX + 3] = 0;
    iVar4 = unaff_EBX;
  }
  *piVar3 = iVar4;
  piVar3[1] = 1;
  iVar2 = 0;
  piVar1 = piVar3 + 2;
  if (0 < iVar4) {
    do {
      *piVar1 = param_1;
      param_1 = param_1 + unaff_EDX;
      iVar2 = iVar2 + 1;
      piVar1 = piVar1 + 1;
    } while (iVar2 < iVar4);
  }
  return piVar3 + 2;
}


// ================================================================================================
// removewindow @ 0x98dd8 [__watcall]
// ================================================================================================

void __watcall removewindow(int *param_1)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  int *piVar4;
  
  iVar1 = param_1[1];
  param_1[1] = iVar1 + -1;
  if (iVar1 + -1 == 0) {
    piVar2 = (int *)0x0;
    for (piVar3 = dword_d2f60; piVar3 < param_1; piVar3 = piVar3 + *piVar3 + 2) {
      piVar2 = piVar3;
    }
    if (piVar3 != param_1) {
      fatalerror(aRemovewindowROWSPACECORR);
    }
    piVar4 = piVar3 + *piVar3 + 2;
    if ((piVar4 < dword_edaa8) && (piVar4[1] == 0)) {
      *piVar3 = *piVar3 + *piVar4 + 2;
    }
    if ((piVar2 != (int *)0x0) && (piVar2[1] == 0)) {
      *piVar2 = *piVar2 + *piVar3 + 2;
    }
  }
  return;
}


// ================================================================================================
// loadfile_auto @ 0x98e50 [__cdecl]
// ================================================================================================

undefined4 * loadfile_auto(undefined4 param_1,uint param_2,undefined4 param_3)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined local_70 [100];
  
  uVar1 = sub_a2610();
  puVar2 = (undefined4 *)find_loaded_file(local_70);
  if (puVar2 == (undefined4 *)0x0) {
    iVar3 = stricmp(uVar1,&aVsh);
    if ((iVar3 != 0) && (iVar3 = stricmp(uVar1,&aQvs), iVar3 != 0)) {
      puVar2 = (undefined4 *)loadfile_packed(local_70,param_2,param_3);
      return puVar2;
    }
    puVar4 = (undefined4 *)loadfile_packed(local_70,param_2 ^ 0x20,param_3);
    puVar2 = puVar4;
    if (puVar4 != (undefined4 *)0x0) {
      uVar1 = packed_size(*puVar4);
      puVar2 = (undefined4 *)reservemem_locked(local_70,uVar1,param_2,param_3);
      shpi_from_compressed(*puVar4,*puVar2);
      releasememblock(puVar4);
    }
  }
  return puVar2;
}


// ================================================================================================
// sub_98f11 @ 0x98f11 [__watcall]
// ================================================================================================

void __watcall sub_98f11(void)

{
  if (((byte_d4f5e == '\0') && (word_d4f88 == 0)) && (dword_d4f64 != 0)) {
    byte_d4f5e = '\x01';
    sub_98f46();
    byte_d4f5e = byte_d4f5e + -1;
  }
  return;
}


// ================================================================================================
// sub_98f46 @ 0x98f46 [__watcall]
// ================================================================================================

void __watcall sub_98f46(void)

{
  byte bVar1;
  char cVar2;
  ushort uVar3;
  int iVar4;
  uint uVar5;
  int *piVar6;
  undefined1 *puVar7;
  undefined4 *puVar8;
  int iVar9;
  int iVar10;
  
  iVar4 = 0;
  byte_d4f5d = byte_d4f5d + '\x01';
  do {
    piVar6 = &unk_f22fc + iVar4 * 5;
    if (*piVar6 != 0) {
      iVar9 = (&unk_f2300)[iVar4 * 5];
      (&unk_f2300)[iVar4 * 5] = iVar9 - (&unk_f2304)[iVar4 * 5];
      iVar9 = iVar9 - (&unk_f2304)[iVar4 * 5] >> 0x18;
      if (iVar9 != *piVar6) {
        sub_971f8((&unk_f230c)[iVar4 * 0x14],iVar9 * 0x10000 + iVar4 * 0x1000000 + 0x32);
        if (iVar9 < 1) {
          sub_8fcac((&unk_f2308)[iVar4 * 5],iVar4);
          iVar9 = 0;
        }
        *piVar6 = iVar9;
      }
    }
    iVar4 = iVar4 + 1;
  } while (iVar4 < 4);
  if (-1 < (int)dword_d4f96) {
    iVar4 = sub_971f8(dword_d4f96 & 0xff,8);
    if (iVar4 != 0) {
      sub_971db(dword_d4f96 & 0xff);
    }
  }
  for (uVar5 = 0; (int)uVar5 < dword_d4f64; uVar5 = uVar5 + 1) {
    if (uVar5 != dword_d4f96) {
      sub_971db(uVar5 & 0xff);
    }
  }
  sub_99822();
  if (dword_d4f8a == 0) {
    puVar7 = &unk_f1a1c;
    iVar4 = 0;
    do {
      bVar1 = puVar7[1];
      uVar5 = (uint)bVar1;
      if (bVar1 != 0) {
        if ((bVar1 & 8) != 0) {
          cVar2 = *(char *)(*(int *)(puVar7 + 6) + 0x15);
          uVar5 = (uint)CONCAT11(byte_d4f5d,cVar2);
          if (cVar2 != byte_d4f5d) {
            *(char *)(*(int *)(puVar7 + 6) + 0x15) = byte_d4f5d;
            iVar9 = *(int *)(puVar7 + 6);
            uVar3 = *(ushort *)(iVar9 + 0xe);
            uVar5 = (uint)uVar3;
            if (uVar3 != 0) {
              bVar1 = *(byte *)(iVar9 + 0x10);
              *(ushort *)(iVar9 + 0xe) = uVar3 - 1;
              iVar9 = sub_a2ac8((int)(short)uVar3);
              iVar9 = (uint)bVar1 * iVar9;
              iVar10 = (int)*(short *)(*(int *)(puVar7 + 6) + 0xc);
              uVar5 = iVar9 % iVar10;
              *(char *)(*(int *)(puVar7 + 6) + 0x11) = (char)(iVar9 / iVar10);
            }
          }
        }
        sub_990cb(puVar7,uVar5);
      }
      puVar7 = puVar7 + 0x54;
      iVar4 = iVar4 + 1;
    } while (iVar4 < 0x18);
    puVar8 = &unk_f189c;
    iVar4 = 0;
    do {
      if ((*(char *)((int)puVar8 + 5) == -1) &&
         (iVar9 = puVar8[2], puVar8[2] = iVar9 + -1, iVar9 + -1 == 0)) {
        sub_99620(puVar8);
      }
      puVar8 = puVar8 + 3;
      iVar4 = iVar4 + 1;
    } while (iVar4 < 0x20);
  }
  if (-1 < (int)dword_d4f96) {
    iVar4 = sub_971f8(dword_d4f96 & 0xff,8);
    if (iVar4 != 0) {
      sub_971db(dword_d4f96 & 0xff);
    }
  }
  return;
}


// ================================================================================================
// sub_990cb @ 0x990cb [__watcall]
// ================================================================================================

void __watcall sub_990cb(char *param_1)

{
  char cVar1;
  int iVar2;
  short sVar3;
  uint uVar4;
  int iVar5;
  int *piVar6;
  int *extraout_EDX;
  undefined4 *puVar7;
  undefined4 *extraout_EDX_00;
  byte *pbVar8;
  byte *pbVar9;
  undefined8 uVar10;
  byte local_1c;
  
  iVar2 = dword_d4f9a;
  if (*(int *)(param_1 + 10) == 0) {
    return;
  }
  pbVar9 = &unk_f21fc + dword_d4f9a;
  dword_d4f9a = dword_d4f9a + 4;
  *pbVar9 = 0x80;
  if ((param_1[1] & 8U) != 0) {
    iVar5 = *(int *)(param_1 + 6);
    if (*(short *)(iVar5 + 0xe) == 0) {
      piVar6 = &unk_f189c;
      for (sVar3 = 0; sVar3 < 0x20; sVar3 = sVar3 + 1) {
        if ((*piVar6 == *(int *)(param_1 + 2)) && (*(char *)((int)piVar6 + 5) == *param_1)) {
          sub_99620(piVar6);
          piVar6 = extraout_EDX;
        }
        piVar6 = piVar6 + 3;
      }
      *pbVar9 = param_1[0x50] | 0xb0;
      (&DAT_000f21fd)[iVar2] = 0x7b;
      (&DAT_000f21fe)[iVar2] = 0;
      sub_997b7(param_1[0x51],3,pbVar9);
      param_1[10] = '\0';
      param_1[0xb] = '\0';
      param_1[0xc] = '\0';
      param_1[0xd] = '\0';
      param_1[1] = '\0';
      goto LAB_00099513;
    }
    uVar10 = sub_a2ac8((int)*(short *)(iVar5 + 0xe),(int)*(short *)(iVar5 + 0xc));
    if ((int)uVar10 == (int)((ulonglong)uVar10 >> 0x20)) {
      *(undefined *)(*(int *)(param_1 + 6) + 0x11) = *(undefined *)(*(int *)(param_1 + 6) + 0x10);
      param_1[1] = param_1[1] & 0xf7;
    }
    else {
      sVar3 = *(short *)(*(int *)(param_1 + 6) + 0xe);
      if ((sVar3 != 0) &&
         (uVar10 = sub_a2ac8((int)sVar3,(int)*(short *)(*(int *)(param_1 + 6) + 0xc)),
         (int)uVar10 != (int)((ulonglong)uVar10 >> 0x20))) {
        sub_99522(param_1,7);
      }
    }
  }
  *(short *)(param_1 + 0x4a) = *(short *)(param_1 + 0x4a) + 0x80;
  while ((*(short *)(param_1 + 0x4c) <= *(short *)(param_1 + 0x4a) && (*(int *)(param_1 + 10) != 0))
        ) {
    puVar7 = &unk_f189c;
    for (sVar3 = 0; sVar3 < 0x20; sVar3 = sVar3 + 1) {
      if ((*(char *)((int)puVar7 + 5) == *param_1) &&
         (iVar5 = puVar7[2], puVar7[2] = iVar5 + -1, iVar5 + -1 == 0)) {
        sub_99620(puVar7);
        puVar7 = extraout_EDX_00;
      }
      puVar7 = puVar7 + 3;
    }
    if (*(int *)(param_1 + 0xe) == 0) {
      if (*(int *)(param_1 + 10) != 0) {
        while ((*(int *)(param_1 + 0xe) == 0 && (*(int *)(param_1 + 10) != 0))) {
          sub_99925(&unk_f1884,*(int *)(param_1 + 10));
          uVar4 = (uint)byte_f188e;
          iVar5 = *(int *)(param_1 + 10);
          *(uint *)(param_1 + 10) = iVar5 + uVar4;
          cVar1 = byte_f188d;
          if (byte_f188c < 0xd9) {
            if (byte_f188c < 0x80) {
              byte_f188d = param_1[0x52];
            }
            byte_f188c = byte_f188c & 0x7f;
            if (param_1[0x50] != '\t') {
              byte_f188c = byte_f188c + *(char *)(*(int *)(param_1 + 6) + 0x13);
            }
            if (dword_d4f92 != 0) {
              local_1c = param_1[0x51];
              if ((param_1[0x50] == '\t') &&
                 (iVar5 = snd_patch_record(byte_f188c + 0x5c), iVar5 != 0)) {
                local_1c = *(byte *)(iVar5 + 0xf) & 0x7f;
              }
              sub_99700(byte_f188c,byte_f188d,dword_f1888,param_1[0x50],local_1c,*param_1,
                        *(undefined4 *)(param_1 + 2));
            }
          }
          else if (byte_f188c < 0xe2) {
            if (byte_f188c < 0xdc) {
              if (0xd8 < byte_f188c) {
                if (byte_f188c < 0xdb) {
                  if (param_1[0x31] == 0) {
                    param_1[10] = '\0';
                    param_1[0xb] = '\0';
                    param_1[0xc] = '\0';
                    param_1[0xd] = '\0';
                    param_1[2] = '\0';
                    param_1[3] = '\0';
                    param_1[4] = '\0';
                    param_1[5] = '\0';
                    param_1[1] = '\0';
                  }
                  else {
                    *(undefined4 *)(param_1 + 10) =
                         *(undefined4 *)(param_1 + (uint)(byte)param_1[0x31] * 4 + 0x32);
                    param_1[0x31] = param_1[0x31] + -1;
                  }
                }
                else {
                  param_1[0x31] = '\0';
                  param_1[0x30] = '\0';
                  iVar5 = *(int *)(param_1 + 0x32);
LAB_00099329:
                  *(int *)(param_1 + 10) = iVar5;
                }
              }
            }
            else if (byte_f188c < 0xdd) {
              param_1[0x4f] = byte_f188d;
              *pbVar9 = param_1[0x50] | 0xc0;
              (&DAT_000f21fd)[iVar2] = cVar1;
              iVar5 = snd_patch_record(cVar1);
              if (iVar5 != 0) {
                if ((*(byte *)(iVar5 + 0xf) & 0x80) == 0) {
                  param_1[0x51] = '\x7f';
                }
                else {
                  param_1[0x51] = *(byte *)(iVar5 + 0xf) & 0x7f;
                }
              }
              cVar1 = param_1[0x51];
              sVar3 = 2;
              pbVar8 = pbVar9;
LAB_000993c5:
              sub_9722e(cVar1,sVar3,pbVar8);
            }
            else if (byte_f188c < 0xde) {
              sub_9966e(*(undefined4 *)(param_1 + 2),byte_f188d);
            }
            else if ((byte_f188c == 0xdf) && ((param_1[1] & 8U) == 0)) {
              sub_99522(param_1,byte_f188d,dword_f1888 & 0xff);
            }
          }
          else if (byte_f188c < 0xe3) {
            *(uint *)(param_1 + (uint)(byte)param_1[0x30] * 4 + 0x18) = iVar5 + uVar4;
            param_1[(byte)param_1[0x30] + 0x12] = cVar1 + -1;
            param_1[0x30] = param_1[0x30] + '\x01';
          }
          else if (byte_f188c < 0xe5) {
            if (byte_f188c < 0xe4) {
              if (param_1[0x30] != 0) {
                *(undefined4 *)(param_1 + 10) =
                     *(undefined4 *)(param_1 + (uint)(byte)param_1[0x30] * 4 + 0x14);
                cVar1 = param_1[(byte)param_1[0x30] + 0x11];
                param_1[(byte)param_1[0x30] + 0x11] = cVar1 + -1;
                if (cVar1 == '\0') {
                  param_1[0x30] = param_1[0x30] + -1;
                }
              }
            }
            else {
              param_1[0x52] = byte_f188d;
            }
          }
          else if (byte_f188c < 0xe6) {
            sub_996b0(param_1,(int)(short)dword_f1888);
          }
          else if (byte_f188c < 0xe8) {
            if (byte_f188c == 0xe6) {
              cVar1 = param_1[0x31];
              param_1[0x31] = cVar1 + 1U;
              *(undefined4 *)(param_1 + (uint)(byte)(cVar1 + 1U) * 4 + 0x32) =
                   *(undefined4 *)(param_1 + 10);
              iVar5 = dword_f1888 + 4;
              goto LAB_00099329;
            }
          }
          else {
            if (byte_f188c < 0xe9) {
              sVar3 = byte_f188e - 4;
              cVar1 = param_1[0x51];
              pbVar8 = &unk_f1784;
              goto LAB_000993c5;
            }
            if (byte_f188c == 0xea) {
              param_1[0x4e] = byte_f188d;
            }
          }
          if (*(int *)(param_1 + 10) != 0) {
            sub_99925(&dword_f1890,*(int *)(param_1 + 10));
            *(undefined4 *)(param_1 + 0xe) = dword_f1890;
          }
        }
        *(int *)(param_1 + 0xe) = *(int *)(param_1 + 0xe) + -1;
      }
    }
    else {
      *(int *)(param_1 + 0xe) = *(int *)(param_1 + 0xe) + -1;
    }
    *(short *)(param_1 + 0x4a) = *(short *)(param_1 + 0x4a) - *(short *)(param_1 + 0x4c);
  }
LAB_00099513:
  dword_d4f9a = dword_d4f9a + -4;
  return;
}


// ================================================================================================
// sub_99522 @ 0x99522 [__watcall]
// ================================================================================================

void __watcall sub_99522(int param_1,byte unaff_DL,byte unaff_BL)

{
  byte bVar1;
  int iVar2;
  byte *pbVar3;
  
  iVar2 = dword_d4f9a;
  pbVar3 = &unk_f21fc + dword_d4f9a;
  dword_d4f9a = dword_d4f9a + 4;
  *pbVar3 = *(byte *)(param_1 + 0x50) | 0xb0;
  (&DAT_000f21fd)[iVar2] = unaff_DL;
  if (6 < unaff_DL) {
    if (unaff_DL < 8) {
      (&unk_f234d)[(uint)*(byte *)(param_1 + 0x50) * 7] = unaff_BL;
      unaff_BL = (byte)(((uint)*(byte *)(*(int *)(param_1 + 6) + 0x11) * (uint)unaff_BL) / 0x7f);
      if (0x7f < unaff_BL) {
        unaff_BL = 0x7f;
      }
    }
    else if (unaff_DL == 10) {
      (&unk_f234e)[(uint)*(byte *)(param_1 + 0x50) * 7] = unaff_BL;
      bVar1 = *(byte *)(*(int *)(param_1 + 6) + 0x12);
      if (bVar1 < 0x40) {
        unaff_BL = unaff_BL -
                   (char)((int)((0x3f - (uint)*(byte *)(*(int *)(param_1 + 6) + 0x12)) *
                               (uint)unaff_BL) / 0x3f);
      }
      else {
        unaff_BL = unaff_BL + (char)((int)((0x7f - (uint)unaff_BL) * (bVar1 - 0x3f)) / 0x3f);
      }
    }
  }
  (&DAT_000f21fe)[iVar2] = unaff_BL;
  sub_9722e(*(undefined *)(param_1 + 0x51),3,pbVar3);
  dword_d4f9a = dword_d4f9a + -4;
  return;
}


// ================================================================================================
// sub_99620 @ 0x99620 [__watcall]
// ================================================================================================

void __watcall sub_99620(undefined4 *param_1)

{
  int iVar1;
  byte *pbVar2;
  
  iVar1 = dword_d4f9a;
  pbVar2 = &unk_f21fc + dword_d4f9a;
  dword_d4f9a = dword_d4f9a + 4;
  *pbVar2 = *(byte *)((int)param_1 + 6) | 0x80;
  (&DAT_000f21fd)[iVar1] = *(undefined *)(param_1 + 1);
  (&DAT_000f21fe)[iVar1] = 0;
  sub_9722e(*(undefined *)((int)param_1 + 7),3);
  *param_1 = 0;
  dword_d4f9a = dword_d4f9a + -4;
  return;
}


// ================================================================================================
// sub_9966e @ 0x9966e [__watcall]
// ================================================================================================

undefined4 __watcall sub_9966e(int param_1,byte unaff_DL)

{
  short sVar1;
  undefined1 *puVar2;
  
  puVar2 = &unk_f1a1c;
  for (sVar1 = 0; sVar1 < 0x18; sVar1 = sVar1 + 1) {
    if (param_1 == *(int *)(puVar2 + 2)) {
      *(short *)(puVar2 + 0x4c) = (short)(32000 / (ulonglong)(longlong)(int)(uint)unaff_DL);
    }
    puVar2 = puVar2 + 0x54;
  }
  return 0;
}


// ================================================================================================
// sub_996b0 @ 0x996b0 [__watcall]
// ================================================================================================

void __watcall sub_996b0(int param_1,undefined4 unaff_EDX)

{
  int iVar1;
  byte *pbVar2;
  
  iVar1 = dword_d4f9a;
  pbVar2 = &unk_f21fc + dword_d4f9a;
  dword_d4f9a = dword_d4f9a + 4;
  *pbVar2 = *(byte *)(param_1 + 0x50) | 0xe0;
  (&DAT_000f21fd)[iVar1] = 0;
  (&DAT_000f21fe)[iVar1] = (byte)((uint)unaff_EDX >> 8) & 0x7f;
  sub_9722e(*(undefined *)(param_1 + 0x51),3);
  dword_d4f9a = dword_d4f9a + -4;
  return;
}


// ================================================================================================
// sub_99700 @ 0x99700 [__watcall]
// ================================================================================================

int __watcall
sub_99700(undefined param_1,undefined param_2,int param_3,byte unaff_CL,undefined param_5,
         char param_6,int param_7)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  byte *pbVar4;
  
  iVar1 = dword_d4f9a;
  pbVar4 = &unk_f21fc + dword_d4f9a;
  piVar2 = &unk_f189c;
  iVar3 = 0;
  dword_d4f9a = dword_d4f9a + 4;
  do {
    if (*piVar2 == 0) {
      *piVar2 = param_7;
      *(undefined *)(piVar2 + 1) = param_1;
      *(char *)((int)piVar2 + 5) = param_6;
      *(byte *)((int)piVar2 + 6) = unaff_CL;
      *(undefined *)((int)piVar2 + 7) = param_5;
      if (param_3 == 0) {
        piVar2[2] = 1;
      }
      else {
        piVar2[2] = param_3;
      }
      *pbVar4 = unaff_CL | 0x90;
      (&DAT_000f21fd)[iVar1] = param_1;
      (&DAT_000f21fe)[iVar1] = param_2;
      if (param_6 == -1) {
        sub_997b7(param_5,3);
      }
      else {
        sub_9722e(param_5,3);
      }
      goto LAB_000997a6;
    }
    piVar2 = piVar2 + 3;
    iVar3 = iVar3 + 1;
  } while (iVar3 < 0x20);
  iVar3 = -1;
LAB_000997a6:
  dword_d4f9a = dword_d4f9a + -4;
  return iVar3;
}


// ================================================================================================
// sub_997b7 @ 0x997b7 [__watcall]
// ================================================================================================

void __watcall sub_997b7(undefined param_1,short unaff_DX,undefined *unaff_EBX)

{
  undefined1 *puVar1;
  
  if ((byte_d4f5c == '\0') && (unaff_DX + dword_d4f58 < 0x80)) {
    (&unk_f1704)[dword_d4f58] = param_1;
    word_d4f88 = word_d4f88 + 1;
    byte_d4f5c = byte_d4f5c + '\x01';
    dword_d4f58 = dword_d4f58 + 1;
    for (; unaff_DX != 0; unaff_DX = unaff_DX + -1) {
      puVar1 = &unk_f1704 + dword_d4f58;
      dword_d4f58 = dword_d4f58 + 1;
      *puVar1 = *unaff_EBX;
      unaff_EBX = unaff_EBX + 1;
    }
    byte_d4f5c = byte_d4f5c + -1;
    word_d4f88 = word_d4f88 + -1;
  }
  return;
}


// ================================================================================================
// sub_99822 @ 0x99822 [__watcall]
// ================================================================================================

void __watcall sub_99822(void)

{
  short sVar1;
  short sVar2;
  
  if ((dword_d4f58 != 0) && (byte_d4f5c == '\0')) {
    sVar1 = 0;
    byte_d4f5c = '\x01';
    do {
      sVar2 = 3;
      if (((&unk_f1705)[sVar1] & 0xf0) == 0xc0) {
        sVar2 = 2;
      }
      sub_9722e((&unk_f1704)[sVar1],sVar2,&unk_f1705 + sVar1);
      sVar1 = sVar1 + sVar2 + 1;
    } while (sVar1 < dword_d4f58);
    dword_d4f58 = 0;
    byte_d4f5c = byte_d4f5c + -1;
  }
  return;
}


// ================================================================================================
// sub_998a0 @ 0x998a0 [__watcall]
// ================================================================================================

void __watcall sub_998a0(undefined param_1,byte unaff_DL,undefined unaff_BL)

{
  int iVar1;
  byte *pbVar2;
  
  iVar1 = dword_d4f9a;
  pbVar2 = &unk_f21fc + dword_d4f9a;
  dword_d4f9a = dword_d4f9a + 4;
  *pbVar2 = unaff_DL | 0xc0;
  (&DAT_000f21fd)[iVar1] = unaff_BL;
  sub_9722e(param_1,2);
  dword_d4f9a = dword_d4f9a + -4;
  return;
}


// ================================================================================================
// sub_99925 @ 0x99925 [__watcall]
// ================================================================================================

void __watcall sub_99925(int *param_1,byte *unaff_EDX)

{
  byte bVar1;
  int iVar2;
  byte *pbVar3;
  byte *pbVar4;
  undefined8 uVar5;
  
  *param_1 = 0;
  pbVar3 = unaff_EDX;
  do {
    pbVar4 = pbVar3;
    *param_1 = *param_1 * 0x80 + (uint)(*pbVar4 & 0x7f);
    pbVar3 = pbVar4 + 1;
  } while ((*pbVar4 & 0x80) != 0);
  bVar1 = pbVar4[1];
  *(byte *)(param_1 + 2) = bVar1;
  pbVar3 = pbVar4 + 2;
  if (0x11 < (byte)(bVar1 + 0x27)) goto switchD_0009996a_caseD_d9;
  switch(bVar1) {
  case 0xd9:
  case 0xda:
  case 0xdb:
  case 0xe3:
    break;
  default:
    *(byte *)((int)param_1 + 9) = *pbVar3;
    goto LAB_0009998e;
  case 0xdf:
    *(byte *)((int)param_1 + 9) = *pbVar3;
    param_1[1] = (uint)pbVar4[3];
    pbVar3 = pbVar4 + 4;
    break;
  case 0xe5:
    uVar5 = sub_99a0e(pbVar3);
    param_1[1] = (uint)uVar5 & 0xffff;
    pbVar3 = (byte *)((int)((ulonglong)uVar5 >> 0x20) + 2);
    break;
  case 0xe6:
    *(byte *)((int)param_1 + 9) = *pbVar3;
    iVar2 = sub_99a0b(pbVar4 + 3);
    param_1[1] = iVar2;
    pbVar3 = pbVar4 + 7;
    break;
  case 0xe8:
    for (iVar2 = 0; iVar2 < (int)(uint)*pbVar3; iVar2 = iVar2 + 1) {
      (&unk_f1784)[iVar2] = pbVar4[iVar2 + 3];
    }
  case 0xe7:
    pbVar3 = pbVar3 + *pbVar3;
LAB_0009998e:
    pbVar3 = pbVar3 + 1;
  }
switchD_0009996a_caseD_d9:
  if (bVar1 < 0xd9) {
    *(byte *)((int)param_1 + 9) = *pbVar3;
    param_1[1] = 0;
    pbVar4 = pbVar3 + 1;
    do {
      param_1[1] = param_1[1] * 0x80 + (uint)(*pbVar4 & 0x7f);
      pbVar3 = pbVar4 + 1;
      bVar1 = *pbVar4;
      pbVar4 = pbVar3;
    } while ((bVar1 & 0x80) != 0);
  }
  *(char *)((int)param_1 + 10) = (char)pbVar3 - (char)unaff_EDX;
  return;
}


// ================================================================================================
// sub_99a0b @ 0x99a0b [__watcall]
// ================================================================================================

undefined4 __watcall sub_99a0b(undefined4 *param_1)

{
  return *param_1;
}


// ================================================================================================
// sub_99a0e @ 0x99a0e [__watcall]
// ================================================================================================

undefined2 __watcall sub_99a0e(undefined2 *param_1)

{
  return *param_1;
}


// ================================================================================================
// sub_99a12 @ 0x99a12 [__watcall]
// ================================================================================================

void __watcall sub_99a12(undefined4 *param_1,undefined4 *unaff_EDX,uint unaff_EBX,uint unaff_ECX)

{
  uint uVar1;
  undefined4 *puVar2;
  
  if (param_1 != (undefined4 *)0x0) {
    if ((int)unaff_ECX < (int)unaff_EBX) {
      unaff_EBX = unaff_ECX;
    }
    puVar2 = param_1;
    for (uVar1 = unaff_EBX >> 2; uVar1 != 0; uVar1 = uVar1 - 1) {
      *puVar2 = *unaff_EDX;
      unaff_EDX = unaff_EDX + 1;
      puVar2 = puVar2 + 1;
    }
    for (uVar1 = unaff_EBX & 3; uVar1 != 0; uVar1 = uVar1 - 1) {
      *(undefined *)puVar2 = *(undefined *)unaff_EDX;
      unaff_EDX = (undefined4 *)((int)unaff_EDX + 1);
      puVar2 = (undefined4 *)((int)puVar2 + 1);
    }
    *(undefined *)(unaff_EBX + (int)param_1) = 0;
  }
  return;
}


// ================================================================================================
// sub_99a45 @ 0x99a45 [__watcall]
// ================================================================================================

void __watcall
sub_99a45(char *param_1,char *unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX,undefined4 param_5
         )

{
  char cVar1;
  char *pcVar2;
  char *pcVar3;
  char *pcVar4;
  char *pcVar5;
  
  if ((*param_1 == '\0') || (param_1[1] != ':')) {
    pcVar4 = param_1;
    if (unaff_EDX != (char *)0x0) {
      *unaff_EDX = '\0';
    }
  }
  else {
    if (unaff_EDX != (char *)0x0) {
      cVar1 = *param_1;
      unaff_EDX[2] = '\0';
      *unaff_EDX = cVar1;
      unaff_EDX[1] = ':';
    }
    param_1 = param_1 + 2;
    pcVar4 = param_1;
  }
  do {
    pcVar2 = pcVar4;
    pcVar4 = pcVar2;
    pcVar5 = (char *)0x0;
    do {
      while( true ) {
        pcVar3 = pcVar4;
        cVar1 = *pcVar3;
        if (cVar1 == '\0') {
          sub_99a12(unaff_EBX,param_1,(int)pcVar2 - (int)param_1,0x81);
          if (pcVar5 == (char *)0x0) {
            pcVar5 = pcVar3;
          }
          sub_99a12(unaff_ECX,pcVar2,(int)pcVar5 - (int)pcVar2,8);
          sub_99a12(param_5,pcVar5,(int)pcVar3 - (int)pcVar5,4);
          return;
        }
        if (cVar1 != '.') break;
        pcVar4 = pcVar3 + 1;
        pcVar5 = pcVar3;
      }
      pcVar4 = pcVar3 + 1;
    } while ((cVar1 != '\\') && (cVar1 != '/'));
  } while( true );
}


// ================================================================================================
// sub_99ae2 @ 0x99ae2 [__watcall]
// ================================================================================================

char __watcall sub_99ae2(char param_1,char *unaff_EDX)

{
  if ((param_1 == '\\') || (param_1 == '/')) {
    if (*unaff_EDX == '\0') {
      *unaff_EDX = param_1;
    }
    param_1 = *unaff_EDX;
  }
  return param_1;
}


// ================================================================================================
// sub_99af4 @ 0x99af4 [__watcall]
// ================================================================================================

void __watcall
sub_99af4(char *param_1,char *unaff_EDX,char *unaff_EBX,char *unaff_ECX,char *param_5)

{
  char cVar1;
  char *pcVar2;
  char local_c [4];
  
  local_c[0] = '\0';
  if ((unaff_EDX != (char *)0x0) && (*unaff_EDX != '\0')) {
    *param_1 = *unaff_EDX;
    param_1[1] = ':';
    param_1 = param_1 + 2;
  }
  *param_1 = '\0';
  if ((unaff_EBX != (char *)0x0) && (pcVar2 = param_1, *unaff_EBX != '\0')) {
    do {
      param_1 = pcVar2;
      cVar1 = *unaff_EBX;
      unaff_EBX = unaff_EBX + 1;
      cVar1 = sub_99ae2(cVar1,local_c);
      *param_1 = cVar1;
      pcVar2 = param_1 + 1;
    } while (*unaff_EBX != '\0');
    if (local_c[0] == '\0') {
      local_c[0] = '\\';
    }
    if (local_c[0] != *param_1) {
      *pcVar2 = local_c[0];
      param_1 = pcVar2;
    }
  }
  if (local_c[0] == '\0') {
    local_c[0] = '\\';
  }
  if (unaff_ECX == (char *)0x0) {
    if (local_c[0] == *param_1) {
      param_1 = param_1 + 1;
    }
  }
  else {
    cVar1 = sub_99ae2(*unaff_ECX,local_c);
    if ((cVar1 != local_c[0]) && (local_c[0] == *param_1)) {
      param_1 = param_1 + 1;
    }
    for (; *unaff_ECX != '\0'; unaff_ECX = unaff_ECX + 1) {
      cVar1 = sub_99ae2(*unaff_ECX,local_c);
      *param_1 = cVar1;
      param_1 = param_1 + 1;
    }
  }
  if ((param_5 != (char *)0x0) && (*param_5 != '\0')) {
    if (*param_5 == '.') goto LAB_00099ba9;
    *param_1 = '.';
    while( true ) {
      param_1 = param_1 + 1;
LAB_00099ba9:
      cVar1 = *param_5;
      if (cVar1 == '\0') break;
      param_5 = param_5 + 1;
      *param_1 = cVar1;
    }
  }
  *param_1 = '\0';
  return;
}


// ================================================================================================
// sub_99bbf @ 0x99bbf [__watcall]
// ================================================================================================

void __watcall sub_99bbf(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX)

{
  int iVar1;
  int extraout_EDX;
  
  iVar1 = dword_f24c0;
  dword_f24c0 = 0x20;
  iVar1 = iVar1 << 2;
  while (iVar1 != 0) {
    (**(code **)(&unk_f243c + iVar1))(*(code **)(&unk_f243c + iVar1),unaff_EDX,unaff_EBX);
    iVar1 = extraout_EDX;
  }
  return;
}


// ================================================================================================
// sub_99bf6 @ 0x99bf6 [__watcall]
// ================================================================================================

longlong __watcall sub_99bf6(undefined4 param_1,uint unaff_EDX)

{
  funcptr_d2f68 = sub_99bbf;
  if (dword_f24c0 < 0x20) {
    *(undefined4 *)(&unk_f2440 + dword_f24c0 * 4) = param_1;
    dword_f24c0 = dword_f24c0 + 1;
    return (ulonglong)unaff_EDX << 0x20;
  }
  return CONCAT44(unaff_EDX,0xffffffff);
}


// ================================================================================================
// __CMain @ 0x99c32 [__watcall] noreturn
// ================================================================================================

void __watcall __CMain(undefined4 param_1)

{
  undefined *puVar1;
  int iVar2;
  uint uVar3;
  undefined *puVar4;
  undefined8 uVar5;
  
  puVar4 = &stack0xfffffff8;
  uVar5 = sub_9d68e(param_1,dword_d4cf0 + 3U & 0xfffffffc);
  uVar3 = (uint)((ulonglong)uVar5 >> 0x20);
  if (uVar3 < (uint)uVar5) {
    iVar2 = -uVar3;
    puVar4 = &stack0xfffffff8 + iVar2;
    puVar1 = &stack0xfffffff8 + iVar2;
  }
  else {
    puVar1 = (undefined *)0x0;
  }
  dword_d4cf4 = puVar1 + dword_d4cf0;
  *(undefined4 *)(puVar4 + -4) = 0x99c67;
  sub_a2acf();
  *(undefined4 *)(puVar4 + -4) = 0x99c77;
  iVar2 = main(dword_f58d8,dword_f58dc);
                    /* WARNING: Subroutine does not return */
  *(code **)(puVar4 + -4) = sub_99c7c;
  exit(iVar2);
}


// ================================================================================================
// sub_99c7c @ 0x99c7c [__watcall]
// ================================================================================================

void __watcall sub_99c7c(void)

{
  return;
}


// ================================================================================================
// sub_99c82 @ 0x99c82 [__watcall]
// ================================================================================================

void __watcall sub_99c82(byte param_1)

{
  byte bVar1;
  char *pcVar2;
  char *pcVar3;
  
  while( true ) {
    pcVar2 = &unk_d8b3e;
    bVar1 = param_1;
    for (pcVar3 = &unk_d8b14; pcVar3 < &unk_d8b3e; pcVar3 = pcVar3 + 6) {
      if ((*pcVar3 != '\x02') && ((byte)pcVar3[1] <= bVar1)) {
        bVar1 = pcVar3[1];
        pcVar2 = pcVar3;
      }
    }
    if (pcVar2 == &unk_d8b3e) break;
    if (*(code **)(pcVar2 + 2) != (code *)0x0) {
      (**(code **)(pcVar2 + 2))();
    }
    *pcVar2 = '\x02';
  }
  return;
}


// ================================================================================================
// sub_99ccd @ 0x99ccd [__watcall]
// ================================================================================================

void __watcall sub_99ccd(byte param_1,byte unaff_DL)

{
  byte bVar1;
  char *pcVar2;
  char *pcVar3;
  
  while( true ) {
    pcVar2 = &unk_d8b4a;
    bVar1 = param_1;
    for (pcVar3 = &unk_d8b3e; pcVar3 < &unk_d8b4a; pcVar3 = pcVar3 + 6) {
      if ((*pcVar3 != '\x02') && (bVar1 <= (byte)pcVar3[1])) {
        bVar1 = pcVar3[1];
        pcVar2 = pcVar3;
      }
    }
    if (pcVar2 == &unk_d8b4a) break;
    if ((bVar1 <= unaff_DL) && (*(code **)(pcVar2 + 2) != (code *)0x0)) {
      (**(code **)(pcVar2 + 2))();
    }
    *pcVar2 = '\x02';
  }
  return;
}


// ================================================================================================
// __prtf @ 0x99d1c [__watcall]
// ================================================================================================

undefined4 __watcall __prtf(undefined4 param_1,char *unaff_EDX,int *unaff_EBX,code *unaff_ECX)

{
  int iVar1;
  char cVar2;
  undefined6 *puVar3;
  char *pcVar4;
  char *extraout_ECX;
  undefined4 *puVar5;
  undefined2 *puVar6;
  bool bVar7;
  undefined auStack_5c [40];
  undefined4 local_34;
  int local_30;
  int local_2c;
  int local_28;
  undefined4 local_24;
  byte local_20;
  char local_1f;
  char local_1e;
  char local_1d [5];
  undefined local_14 [4];
  
  local_14[0] = 0;
  local_20 = 0;
  local_24 = 0;
  local_34 = param_1;
  do {
    while( true ) {
      while( true ) {
        while( true ) {
          cVar2 = *unaff_EDX;
          if (cVar2 == '\0') {
            return local_24;
          }
          unaff_EDX = unaff_EDX + 1;
          if (cVar2 == '%') break;
          (*unaff_ECX)();
        }
        unaff_EDX = (char *)sub_99f9d(unaff_EDX,unaff_EBX,&local_34);
        local_1f = *unaff_EDX;
        unaff_EDX = unaff_EDX + 1;
        if (local_1f == '\0') {
          return local_24;
        }
        if (local_1f == 'n') break;
        sub_9a2b5(auStack_5c,unaff_EBX,&local_34,local_14);
        if (((local_20 & 8) == 0) && (local_1e == ' ')) {
          while (local_30 = local_30 + -1, -1 < local_30) {
            (*unaff_ECX)();
          }
        }
        pcVar4 = local_1d;
        while (*pcVar4 != '\0') {
          (*unaff_ECX)();
          pcVar4 = extraout_ECX;
        }
        while (iVar1 = local_28 + -1, local_28 != 0) {
          local_28 = iVar1;
          (*unaff_ECX)();
        }
        local_28 = iVar1;
        if (((local_20 & 8) == 0) && (local_1e != ' ')) {
          while (local_30 = local_30 + -1, -1 < local_30) {
            (*unaff_ECX)();
          }
        }
        if ((local_1f == 's') || (local_1f == 'S')) {
          if ((local_20 & 0x20) == 0) {
            while (iVar1 = local_2c + -1, bVar7 = local_2c != 0, local_2c = iVar1, bVar7) {
              (*unaff_ECX)();
            }
          }
          else {
            while (iVar1 = local_2c + -1, bVar7 = local_2c != 0, local_2c = iVar1, bVar7) {
              (*unaff_ECX)();
            }
          }
        }
        else {
          while (iVar1 = local_2c + -1, bVar7 = local_2c != 0, local_2c = iVar1, bVar7) {
            (*unaff_ECX)();
          }
        }
        if (((local_20 & 8) != 0) && (0 < local_30)) {
          while (iVar1 = local_30 + -1, bVar7 = local_30 != 0, local_30 = iVar1, bVar7) {
            (*unaff_ECX)();
          }
        }
      }
      if ((local_20 & 0x20) == 0) break;
      if ((local_20 & 0x80) == 0) {
        if ((local_20 & 0x40) == 0) {
          puVar5 = (undefined4 *)*unaff_EBX;
          *unaff_EBX = (int)(puVar5 + 1);
          puVar5 = (undefined4 *)*puVar5;
        }
        else {
          puVar5 = (undefined4 *)*unaff_EBX;
          *unaff_EBX = (int)(puVar5 + 1);
          puVar5 = (undefined4 *)*puVar5;
        }
LAB_00099d99:
        *puVar5 = local_24;
      }
      else {
        puVar3 = (undefined6 *)*unaff_EBX;
        *unaff_EBX = (int)(puVar3 + 1);
        puVar5 = (undefined4 *)*puVar3;
LAB_00099d82:
        *puVar5 = local_24;
      }
    }
    if ((local_20 & 0x10) == 0) {
      if ((local_20 & 0x80) == 0) {
        if ((local_20 & 0x40) == 0) {
          puVar5 = (undefined4 *)*unaff_EBX;
          *unaff_EBX = (int)(puVar5 + 1);
          puVar5 = (undefined4 *)*puVar5;
        }
        else {
          puVar5 = (undefined4 *)*unaff_EBX;
          *unaff_EBX = (int)(puVar5 + 1);
          puVar5 = (undefined4 *)*puVar5;
        }
        goto LAB_00099d99;
      }
      puVar3 = (undefined6 *)*unaff_EBX;
      *unaff_EBX = (int)(puVar3 + 1);
      puVar5 = (undefined4 *)*puVar3;
      goto LAB_00099d82;
    }
    if ((local_20 & 0x80) == 0) {
      if ((local_20 & 0x40) == 0) {
        puVar5 = (undefined4 *)*unaff_EBX;
        *unaff_EBX = (int)(puVar5 + 1);
        puVar6 = (undefined2 *)*puVar5;
      }
      else {
        puVar5 = (undefined4 *)*unaff_EBX;
        *unaff_EBX = (int)(puVar5 + 1);
        puVar6 = (undefined2 *)*puVar5;
      }
      *puVar6 = (short)local_24;
    }
    else {
      puVar3 = (undefined6 *)*unaff_EBX;
      *unaff_EBX = (int)(puVar3 + 1);
      *(undefined2 *)*puVar3 = (short)local_24;
    }
  } while( true );
}


// ================================================================================================
// sub_99f9d @ 0x99f9d [__watcall]
// ================================================================================================

byte * __watcall sub_99f9d(undefined4 param_1,int *unaff_EDX,int unaff_EBX)

{
  byte bVar1;
  int *piVar2;
  int iVar3;
  byte *pbVar4;
  byte *pbVar5;
  
  *(undefined *)(unaff_EBX + 0x17) = 0;
  *(undefined *)(unaff_EBX + 0x16) = 0x20;
  pbVar4 = (byte *)sub_9a0d0(param_1,unaff_EBX);
  *(undefined4 *)(unaff_EBX + 4) = 0;
  if ((*pbVar4 < 0x30) || (0x39 < *pbVar4)) {
    if (*pbVar4 == 0x2a) {
      piVar2 = (int *)*unaff_EDX;
      *unaff_EDX = (int)(piVar2 + 1);
      iVar3 = *piVar2;
      *(int *)(unaff_EBX + 4) = iVar3;
      if (iVar3 < 0) {
        *(int *)(unaff_EBX + 4) = -iVar3;
        *(byte *)(unaff_EBX + 0x14) = *(byte *)(unaff_EBX + 0x14) | 8;
      }
      pbVar4 = pbVar4 + 1;
    }
  }
  else {
    do {
      bVar1 = *pbVar4;
      pbVar4 = pbVar4 + 1;
      *(uint *)(unaff_EBX + 4) = *(int *)(unaff_EBX + 4) * 10 + (bVar1 - 0x30);
      if (*pbVar4 < 0x30) break;
    } while (*pbVar4 < 0x3a);
  }
  *(undefined4 *)(unaff_EBX + 8) = 0xffffffff;
  pbVar5 = pbVar4;
  if (*pbVar4 == 0x2e) {
    pbVar5 = pbVar4 + 1;
    *(undefined4 *)(unaff_EBX + 8) = 0;
    if (*pbVar5 == 0x2a) {
      piVar2 = (int *)*unaff_EDX;
      *unaff_EDX = (int)(piVar2 + 1);
      iVar3 = *piVar2;
      *(int *)(unaff_EBX + 8) = iVar3;
      if (iVar3 < 0) {
        *(undefined4 *)(unaff_EBX + 8) = 0xffffffff;
      }
      pbVar5 = pbVar4 + 2;
    }
    else {
      for (; (0x2f < *pbVar5 && (*pbVar5 < 0x3a)); pbVar5 = pbVar5 + 1) {
        *(uint *)(unaff_EBX + 8) = *(int *)(unaff_EBX + 8) * 10 + (*pbVar5 - 0x30);
      }
    }
  }
  bVar1 = *pbVar5;
  pbVar4 = pbVar5 + 1;
  if (bVar1 < 0x4e) {
    if (0x45 < bVar1) {
      if (bVar1 < 0x47) {
        *(byte *)(unaff_EBX + 0x14) = *(byte *)(unaff_EBX + 0x14) | 0x80;
      }
      else {
        if (bVar1 != 0x4c) {
          return pbVar5;
        }
        *(byte *)(unaff_EBX + 0x14) = *(byte *)(unaff_EBX + 0x14) | 0x40;
      }
      return pbVar4;
    }
  }
  else {
    if (0x4e < bVar1) {
      if (bVar1 < 0x6c) {
        if (bVar1 == 0x68) {
          *(byte *)(unaff_EBX + 0x14) = *(byte *)(unaff_EBX + 0x14) | 0x10;
          return pbVar4;
        }
        return pbVar5;
      }
      if ((0x6c < bVar1) && (bVar1 != 0x77)) {
        return pbVar5;
      }
      *(byte *)(unaff_EBX + 0x14) = *(byte *)(unaff_EBX + 0x14) | 0x20;
      return pbVar5 + 1;
    }
    *(byte *)(unaff_EBX + 0x14) = *(byte *)(unaff_EBX + 0x14) | 0x40;
    pbVar5 = pbVar4;
  }
  return pbVar5;
}


// ================================================================================================
// sub_9a0d0 @ 0x9a0d0 [__watcall]
// ================================================================================================

void __watcall sub_9a0d0(char *param_1,int unaff_EDX)

{
  char cVar1;
  byte bVar2;
  
  *(undefined *)(unaff_EDX + 0x14) = 0;
  do {
    cVar1 = *param_1;
    if (cVar1 == '-') {
      *(byte *)(unaff_EDX + 0x14) = *(byte *)(unaff_EDX + 0x14) | 8;
    }
    else if (cVar1 == '#') {
      *(byte *)(unaff_EDX + 0x14) = *(byte *)(unaff_EDX + 0x14) | 1;
    }
    else if (cVar1 == '+') {
      bVar2 = *(byte *)(unaff_EDX + 0x14);
      *(byte *)(unaff_EDX + 0x14) = bVar2 | 4;
      *(byte *)(unaff_EDX + 0x14) = bVar2 & 0xfd | 4;
    }
    else if (cVar1 == ' ') {
      if ((*(byte *)(unaff_EDX + 0x14) & 4) == 0) {
        *(byte *)(unaff_EDX + 0x14) = *(byte *)(unaff_EDX + 0x14) | 2;
      }
    }
    else {
      if (cVar1 != '0') {
        return;
      }
      *(undefined *)(unaff_EDX + 0x16) = 0x30;
    }
    param_1 = param_1 + 1;
  } while( true );
}


// ================================================================================================
// sub_9a12b @ 0x9a12b [__watcall]
// ================================================================================================

void __watcall sub_9a12b(char *param_1,undefined4 param_2,int unaff_EBX)

{
  char cVar1;
  int iVar2;
  
  for (iVar2 = 0; (cVar1 = *param_1, param_1 = param_1 + 1, cVar1 != '\0' && (iVar2 != unaff_EBX));
      iVar2 = iVar2 + 1) {
  }
  return;
}


// ================================================================================================
// sub_9a14f @ 0x9a14f [__watcall]
// ================================================================================================

void __watcall sub_9a14f(short *param_1,undefined4 param_2,int unaff_EBX)

{
  short sVar1;
  int iVar2;
  
  for (iVar2 = 0; (sVar1 = *param_1, param_1 = param_1 + 1, sVar1 != 0 && (iVar2 != unaff_EBX));
      iVar2 = iVar2 + 1) {
  }
  return;
}


// ================================================================================================
// sub_9a172 @ 0x9a172 [__watcall]
// ================================================================================================

void __watcall sub_9a172(undefined4 param_1,char *unaff_EDX,int unaff_EBX)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  char *pcVar4;
  char *pcVar5;
  
  sub_9812f(param_1,unaff_EDX,0x10);
  uVar3 = 0xffffffff;
  pcVar4 = unaff_EDX;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  iVar2 = unaff_EBX + -1;
  pcVar4 = unaff_EDX + (~uVar3 - 1);
  pcVar5 = unaff_EDX + iVar2;
  while (pcVar4 != unaff_EDX) {
    pcVar4 = pcVar4 + -1;
    iVar2 = iVar2 + -1;
    *pcVar5 = *pcVar4;
    pcVar5 = pcVar5 + -1;
  }
  pcVar4 = unaff_EDX + iVar2;
  for (; -1 < iVar2; iVar2 = iVar2 + -1) {
    *pcVar4 = '0';
    pcVar4 = pcVar4 + -1;
  }
  unaff_EDX[unaff_EBX] = '\0';
  return;
}


// ================================================================================================
// sub_9a1d3 @ 0x9a1d3 [__watcall]
// ================================================================================================

void __watcall sub_9a1d3(char *param_1,uint unaff_EDX,int unaff_EBX)

{
  int iVar1;
  char *pcVar2;
  char *pcVar3;
  char *pcVar4;
  
  pcVar2 = param_1;
  if ((int)unaff_EDX < 0) {
    unaff_EDX = -unaff_EDX;
    pcVar2 = param_1 + 1;
    *param_1 = '-';
  }
  if (*(int *)(unaff_EBX + 8) == -1) {
    *(undefined4 *)(unaff_EBX + 8) = 4;
  }
  sub_9812f(unaff_EDX >> 0x10,pcVar2,10);
  pcVar4 = pcVar2;
  do {
    pcVar3 = pcVar4;
    pcVar4 = pcVar3 + 1;
  } while (*pcVar3 != '\0');
  if (*(int *)(unaff_EBX + 8) != 0) {
    *pcVar3 = '.';
    for (iVar1 = 0; iVar1 < *(int *)(unaff_EBX + 8); iVar1 = iVar1 + 1) {
      unaff_EDX = (unaff_EDX & 0xffff) * 10;
      *pcVar4 = (char)(unaff_EDX >> 0x10) + '0';
      pcVar4 = pcVar4 + 1;
    }
    *pcVar4 = '\0';
    pcVar3 = pcVar4;
  }
  if ((unaff_EDX & 0x8000) != 0) {
    while (pcVar3 != pcVar2) {
      pcVar4 = pcVar3 + -1;
      if (*pcVar4 == '.') {
        pcVar4 = pcVar3 + -2;
      }
      if (*pcVar4 != '9') {
        *pcVar4 = *pcVar4 + '\x01';
        return;
      }
      *pcVar4 = '0';
      pcVar3 = pcVar4;
    }
    *pcVar2 = '1';
    pcVar2 = pcVar2 + 1;
    do {
      pcVar4 = pcVar2;
      pcVar2 = pcVar4 + 1;
    } while (*pcVar4 == '0');
    if (*pcVar4 == '.') {
      *pcVar4 = '0';
      pcVar4[1] = '.';
      for (pcVar4 = pcVar4 + 2; *pcVar4 == '0'; pcVar4 = pcVar4 + 1) {
      }
    }
    *pcVar4 = '0';
    pcVar4[1] = '\0';
  }
  return;
}


// ================================================================================================
// sub_9a2ae @ 0x9a2ae [__watcall]
// ================================================================================================

void __watcall sub_9a2ae(void)

{
  (*(code *)funcptr_d5668)();
  return;
}


// ================================================================================================
// sub_9a2b5 @ 0x9a2b5 [__watcall]
// ================================================================================================

undefined8 __watcall sub_9a2b5(ushort *param_1,int *unaff_EDX,int unaff_EBX,ushort *unaff_ECX)

{
  byte bVar1;
  uint *puVar2;
  int *piVar3;
  short *psVar4;
  undefined4 *puVar5;
  byte *pbVar6;
  bool bVar7;
  uint uVar8;
  int iVar9;
  ushort uVar10;
  undefined4 uVar11;
  uint unaff_EBP;
  ushort *puVar12;
  ushort in_DS;
  ushort uVar13;
  bool bVar14;
  undefined8 uVar15;
  
  bVar7 = true;
  bVar1 = *(byte *)(unaff_EBX + 0x15);
  *(undefined4 *)(unaff_EBX + 0xc) = 0;
  if (bVar1 < 0x69) {
    if (0x57 < bVar1) {
      if (bVar1 < 0x59) goto LAB_0009a302;
      if (bVar1 == 100) goto LAB_0009a336;
    }
  }
  else {
    if (0x69 < bVar1) {
      if (bVar1 < 0x75) {
        bVar14 = bVar1 == 0x6f;
      }
      else {
        if (bVar1 < 0x76) goto LAB_0009a302;
        bVar14 = bVar1 == 0x78;
      }
      if (!bVar14) goto LAB_0009a340;
LAB_0009a302:
      if ((*(byte *)(unaff_EBX + 0x14) & 0x20) == 0) {
        if ((*(byte *)(unaff_EBX + 0x14) & 0x10) == 0) {
          puVar2 = (uint *)*unaff_EDX;
          *unaff_EDX = (int)(puVar2 + 1);
          unaff_EBP = *puVar2;
        }
        else {
          puVar12 = (ushort *)*unaff_EDX;
          *unaff_EDX = (int)(puVar12 + 2);
          unaff_EBP = (uint)*puVar12;
        }
      }
      else {
        puVar2 = (uint *)*unaff_EDX;
        *unaff_EDX = (int)(puVar2 + 1);
        unaff_EBP = *puVar2;
      }
      *(byte *)(unaff_EBX + 0x14) = *(byte *)(unaff_EBX + 0x14) & 0xf9;
    }
LAB_0009a336:
    if (*(int *)(unaff_EBX + 8) != -1) {
      *(undefined *)(unaff_EBX + 0x16) = 0x20;
    }
  }
LAB_0009a340:
  bVar1 = *(byte *)(unaff_EBX + 0x15);
  uVar11 = 10;
  puVar12 = param_1;
  uVar10 = in_DS;
  uVar13 = in_DS;
  if (bVar1 < 0x65) {
    if (bVar1 < 0x50) {
      if (bVar1 < 0x46) {
        bVar14 = bVar1 == 0x45;
      }
      else {
        if (bVar1 < 0x47) goto LAB_0009a3ec;
        bVar14 = bVar1 == 0x47;
      }
      if (!bVar14) goto LAB_0009a639;
      goto LAB_0009a416;
    }
    if (0x50 < bVar1) {
      if (bVar1 < 0x58) {
        if (bVar1 != 0x53) goto LAB_0009a639;
LAB_0009a4a5:
        param_1 = unaff_ECX;
        if ((*(byte *)(unaff_EBX + 0x14) & 0x80) == 0) {
          if ((*(byte *)(unaff_EBX + 0x14) & 0x40) == 0) {
            puVar5 = (undefined4 *)*unaff_EDX;
            *unaff_EDX = (int)(puVar5 + 1);
            puVar12 = (ushort *)*puVar5;
          }
          else {
            puVar5 = (undefined4 *)*unaff_EDX;
            *unaff_EDX = (int)(puVar5 + 1);
            puVar12 = (ushort *)*puVar5;
          }
          if (puVar12 != (ushort *)0x0) {
            param_1 = puVar12;
          }
        }
        else {
          puVar5 = (undefined4 *)*unaff_EDX;
          *unaff_EDX = (int)(puVar5 + 2);
          if (((ushort *)*puVar5 != (ushort *)0x0) || (*(ushort *)(puVar5 + 1) != 0)) {
            param_1 = (ushort *)*puVar5;
            uVar10 = *(ushort *)(puVar5 + 1);
          }
        }
        bVar1 = *(byte *)(unaff_EBX + 0x14);
        bVar7 = false;
        *(byte *)(unaff_EBX + 0x14) = bVar1 & 0xf9;
        if (*(char *)(unaff_EBX + 0x15) == 'S') {
          if ((bVar1 & 0x20) == 0) {
            uVar8 = (uint)*(byte *)param_1;
            param_1 = (ushort *)((int)param_1 + 1);
          }
          else {
            uVar8 = (uint)*param_1;
            param_1 = param_1 + 1;
          }
        }
        else {
          if ((bVar1 & 0x20) == 0) {
            uVar8 = (uint)uVar10;
            uVar11 = *(undefined4 *)(unaff_EBX + 8);
            goto LAB_0009a45b;
          }
          uVar8 = sub_9a14f(param_1,uVar10,*(undefined4 *)(unaff_EBX + 8));
        }
      }
      else {
        if (bVar1 < 0x59) {
LAB_0009a551:
          if (((*(byte *)(unaff_EBX + 0x14) & 1) != 0) && (unaff_EBP != 0)) {
            *(undefined *)(unaff_EBX + 0x17) = 0x30;
            *(undefined *)(unaff_EBX + 0x19) = 0;
            *(undefined *)(unaff_EBX + 0x18) = *(undefined *)(unaff_EBX + 0x15);
          }
          uVar11 = 0x10;
LAB_0009a56e:
          sub_a2b13(unaff_EBP,param_1,uVar11);
          if (*(char *)(unaff_EBX + 0x15) == 'X') {
            sub_9a6fe(param_1);
          }
          goto LAB_0009a443;
        }
        if (bVar1 < 99) goto LAB_0009a639;
        if (99 < bVar1) goto LAB_0009a465;
        pbVar6 = (byte *)*unaff_EDX;
        *unaff_EDX = (int)(pbVar6 + 4);
        bVar1 = *pbVar6;
        *(byte *)((int)param_1 + 1) = 0;
        *(byte *)param_1 = bVar1;
        *(undefined4 *)(unaff_EBX + 8) = 1;
        uVar8 = 1;
        bVar7 = false;
        *(byte *)(unaff_EBX + 0x14) = *(byte *)(unaff_EBX + 0x14) & 0xf9;
      }
      goto LAB_0009a663;
    }
LAB_0009a58d:
    if (*(int *)(unaff_EBX + 4) == 0) {
      if ((*(byte *)(unaff_EBX + 0x14) & 0x80) == 0) {
        *(undefined4 *)(unaff_EBX + 4) = 8;
      }
      else {
        *(undefined4 *)(unaff_EBX + 4) = 0xd;
      }
    }
    *(byte *)(unaff_EBX + 0x14) = *(byte *)(unaff_EBX + 0x14) & 0xf9;
    puVar5 = (undefined4 *)*unaff_EDX;
    *unaff_EDX = (int)(puVar5 + 1);
    uVar11 = *puVar5;
    if ((*(byte *)(unaff_EBX + 0x14) & 0x80) != 0) {
      *unaff_EDX = (int)(puVar5 + 2);
      sub_9a172(puVar5[1] & 0xffff,param_1,4);
      *(byte *)(param_1 + 2) = 0x3a;
      puVar12 = (ushort *)((int)param_1 + 5);
    }
    sub_9a172(uVar11,puVar12,8);
    if (*(char *)(unaff_EBX + 0x15) == 'P') {
      sub_9a6fe(param_1);
    }
LAB_0009a452:
    uVar11 = 0xffffffff;
    uVar8 = (uint)in_DS;
    uVar10 = in_DS;
    in_DS = uVar13;
LAB_0009a45b:
    uVar8 = sub_9a12b(param_1,uVar8,uVar11);
  }
  else {
    if (bVar1 < 0x66) {
LAB_0009a416:
      uVar15 = sub_9a2ae(param_1,unaff_EDX,unaff_EBX);
      uVar8 = (uint)((ulonglong)uVar15 >> 0x20);
      param_1 = (ushort *)uVar15;
      uVar11 = 0xffffffff;
      uVar10 = (ushort)((ulonglong)uVar15 >> 0x20);
      goto LAB_0009a45b;
    }
    if (bVar1 < 0x6f) {
      if (bVar1 < 0x67) {
LAB_0009a3ec:
        if ((*(byte *)(unaff_EBX + 0x14) & 0x10) != 0) {
          puVar5 = (undefined4 *)*unaff_EDX;
          *unaff_EDX = (int)(puVar5 + 1);
          sub_9a1d3(param_1,*puVar5,unaff_EBX);
          uVar11 = 0xffffffff;
          uVar8 = (uint)uVar10;
          in_DS = uVar10;
          goto LAB_0009a45b;
        }
      }
      else if (0x67 < bVar1) {
        if (bVar1 == 0x69) {
LAB_0009a465:
          if ((*(byte *)(unaff_EBX + 0x14) & 0x20) == 0) {
            if ((*(byte *)(unaff_EBX + 0x14) & 0x10) == 0) {
              puVar5 = (undefined4 *)*unaff_EDX;
              *unaff_EDX = (int)(puVar5 + 1);
              sub_9812f(*puVar5,param_1);
              goto LAB_0009a443;
            }
            psVar4 = (short *)*unaff_EDX;
            *unaff_EDX = (int)(psVar4 + 2);
            iVar9 = (int)*psVar4;
          }
          else {
            piVar3 = (int *)*unaff_EDX;
            *unaff_EDX = (int)(piVar3 + 1);
            iVar9 = *piVar3;
          }
          sub_a2b5c(iVar9,param_1);
          goto LAB_0009a443;
        }
        goto LAB_0009a639;
      }
      goto LAB_0009a416;
    }
    if (bVar1 < 0x70) {
      if ((*(byte *)(unaff_EBX + 0x14) & 1) != 0) {
        *(byte *)param_1 = 0x30;
        puVar12 = (ushort *)((int)param_1 + 1);
      }
      sub_a2b5c(unaff_EBP,puVar12,8);
LAB_0009a443:
      if ((*(int *)(unaff_EBX + 8) == 0) && (*(byte *)puVar12 == 0x30)) {
        *(byte *)param_1 = 0;
      }
      goto LAB_0009a452;
    }
    if (bVar1 < 0x73) {
      if (bVar1 == 0x70) goto LAB_0009a58d;
    }
    else {
      if (bVar1 < 0x74) goto LAB_0009a4a5;
      if (0x74 < bVar1) {
        if (bVar1 < 0x76) goto LAB_0009a56e;
        if (bVar1 == 0x78) goto LAB_0009a551;
      }
    }
LAB_0009a639:
    *(undefined4 *)(unaff_EBX + 4) = 0;
    bVar1 = *(byte *)(unaff_EBX + 0x15);
    *(byte *)((int)param_1 + 1) = 0;
    *(byte *)param_1 = bVar1;
    *(undefined4 *)(unaff_EBX + 8) = 1;
    bVar7 = false;
    *(byte *)(unaff_EBX + 0x14) = *(byte *)(unaff_EBX + 0x14) & 0xf9;
    uVar8 = 1;
  }
LAB_0009a663:
  if (!bVar7) goto LAB_0009a6a9;
  if (*(byte *)param_1 == 0x2d) {
    param_1 = (ushort *)((int)param_1 + 1);
    *(undefined *)(unaff_EBX + 0x18) = 0;
    uVar8 = uVar8 - 1;
    *(undefined *)(unaff_EBX + 0x17) = 0x2d;
  }
  else {
    if ((*(byte *)(unaff_EBX + 0x14) & 2) == 0) {
      if ((*(byte *)(unaff_EBX + 0x14) & 4) == 0) goto LAB_0009a698;
      *(undefined *)(unaff_EBX + 0x17) = 0x2b;
    }
    else {
      *(undefined *)(unaff_EBX + 0x17) = 0x20;
    }
    *(undefined *)(unaff_EBX + 0x18) = 0;
  }
LAB_0009a698:
  if (*(int *)(unaff_EBX + 8) < (int)uVar8) {
    *(uint *)(unaff_EBX + 8) = uVar8;
  }
  else {
    *(uint *)(unaff_EBX + 0xc) = *(int *)(unaff_EBX + 8) - uVar8;
  }
LAB_0009a6a9:
  if (*(char *)(unaff_EBX + 0x16) == '*') {
    *(undefined *)(unaff_EBX + 0x17) = 0;
    *(byte *)(unaff_EBX + 0x14) = *(byte *)(unaff_EBX + 0x14) & 0xf9;
  }
  if (((*(int *)(unaff_EBX + 8) == -1) || ((int)uVar8 < *(int *)(unaff_EBX + 8))) &&
     (*(char *)(unaff_EBX + 0x15) != 'c')) {
    *(uint *)(unaff_EBX + 8) = uVar8;
  }
  iVar9 = sub_9a12b(unaff_EBX + 0x17,in_DS,0xffffffff);
  *(int *)(unaff_EBX + 4) =
       *(int *)(unaff_EBX + 4) - (iVar9 + *(int *)(unaff_EBX + 8) + *(int *)(unaff_EBX + 0xc));
  return CONCAT44(CONCAT22((short)((uint)*(int *)(unaff_EBX + 0xc) >> 0x10),uVar10),param_1);
}


// ================================================================================================
// sub_9a6fe @ 0x9a6fe [__watcall]
// ================================================================================================

void __watcall sub_9a6fe(char *param_1)

{
  undefined uVar1;
  undefined *extraout_EDX;
  
  while (*param_1 != '\0') {
    uVar1 = sub_a2b77(*param_1);
    *extraout_EDX = uVar1;
    param_1 = extraout_EDX + 1;
  }
  return;
}


// ================================================================================================
// sub_9a716 @ 0x9a716 [__watcall]
// ================================================================================================

undefined2 __watcall sub_9a716(undefined2 param_1)

{
  bool in_CF;
  
  if (in_CF) {
    sub_9a735();
  }
  else {
    param_1 = 0;
  }
  return param_1;
}


// ================================================================================================
// sub_9a729 @ 0x9a729 [__watcall]
// ================================================================================================

ulonglong __watcall sub_9a729(uint param_1,int unaff_EDX)

{
  uint uVar1;
  byte bVar2;
  uint extraout_EDX;
  
  if (unaff_EDX == 0) {
    return 0;
  }
  if (unaff_EDX == 0) {
    return (ulonglong)param_1;
  }
  uVar1 = param_1 & 0xff;
  sub_987ad(param_1 & 0xff);
  if (extraout_EDX < 0x100) {
    if (2 < byte_d4d0f) {
      bVar2 = (byte)extraout_EDX;
      if (bVar2 == 0x50) {
        uVar1 = 0xe;
      }
      else if (bVar2 < 0x22) {
        if (0x1f < bVar2) {
          uVar1 = 5;
        }
      }
      else {
        uVar1 = 0x13;
      }
    }
    if (0x13 < (byte)uVar1) {
      uVar1 = 0x13;
    }
    uVar1 = *(int *)(&unk_d4ff1 + uVar1) >> 0x18;
  }
  else {
    uVar1 = extraout_EDX >> 8 & 0xff;
  }
  sub_9878a(uVar1);
  return CONCAT44(unaff_EDX,0xffffffff);
}


// ================================================================================================
// sub_9a730 @ 0x9a730 [__watcall]
// ================================================================================================

ulonglong __watcall sub_9a730(uint param_1,int unaff_EDX)

{
  uint uVar1;
  byte bVar2;
  uint extraout_EDX;
  
  if (unaff_EDX == 0) {
    return (ulonglong)param_1;
  }
  uVar1 = param_1 & 0xff;
  sub_987ad(param_1 & 0xff);
  if (extraout_EDX < 0x100) {
    if (2 < byte_d4d0f) {
      bVar2 = (byte)extraout_EDX;
      if (bVar2 == 0x50) {
        uVar1 = 0xe;
      }
      else if (bVar2 < 0x22) {
        if (0x1f < bVar2) {
          uVar1 = 5;
        }
      }
      else {
        uVar1 = 0x13;
      }
    }
    if (0x13 < (byte)uVar1) {
      uVar1 = 0x13;
    }
    uVar1 = *(int *)(&unk_d4ff1 + uVar1) >> 0x18;
  }
  else {
    uVar1 = extraout_EDX >> 8 & 0xff;
  }
  sub_9878a(uVar1);
  return CONCAT44(unaff_EDX,0xffffffff);
}


// ================================================================================================
// sub_9a735 @ 0x9a735 [__watcall]
// ================================================================================================

undefined8 __watcall sub_9a735(byte param_1,undefined4 unaff_EDX)

{
  uint uVar1;
  byte bVar2;
  uint extraout_EDX;
  
  uVar1 = (uint)param_1;
  sub_987ad(param_1);
  if (extraout_EDX < 0x100) {
    if (2 < byte_d4d0f) {
      bVar2 = (byte)extraout_EDX;
      if (bVar2 == 0x50) {
        uVar1 = 0xe;
      }
      else if (bVar2 < 0x22) {
        if (0x1f < bVar2) {
          uVar1 = 5;
        }
      }
      else {
        uVar1 = 0x13;
      }
    }
    if (0x13 < (byte)uVar1) {
      uVar1 = 0x13;
    }
    uVar1 = *(int *)(&unk_d4ff1 + uVar1) >> 0x18;
  }
  else {
    uVar1 = extraout_EDX >> 8 & 0xff;
  }
  sub_9878a(uVar1);
  return CONCAT44(unaff_EDX,0xffffffff);
}


// ================================================================================================
// windowdef @ 0x9a7a0 [__cdecl]
// ================================================================================================

int * windowdef(int param_1,int param_2,undefined4 param_3)

{
  int *piVar1;
  int *piVar2;
  byte *pbVar3;
  int iVar4;
  
  piVar2 = (int *)sub_8cc70(aMCGAWINDOW,param_1 * param_2 + 0x40,param_3);
  if (piVar2 == (int *)0x0) {
    fatalerror(aWindowdefOUTOFMEMORY);
  }
  piVar1 = (int *)*piVar2;
  if (piVar1 == (int *)0x0) {
    fatalerror(s__windowdef___BAD_BLOCK_000c48af + 1);
  }
  pbVar3 = (byte *)sub_8e3c4(piVar1 + 0xc);
  sub_b3fc2(piVar1,0x40);
  *(short *)(pbVar3 + 4) = (short)param_1;
  *(short *)(pbVar3 + 6) = (short)param_2;
  pbVar3[0] = 0;
  pbVar3[1] = 0;
  pbVar3[2] = 0;
  pbVar3[3] = 0;
  *pbVar3 = *pbVar3 | 1;
  *piVar1 = param_1;
  piVar1[8] = param_1;
  piVar1[4] = param_1;
  piVar1[7] = param_1;
  piVar1[1] = param_2;
  piVar1[5] = param_2;
  piVar1[0xb] = (int)pbVar3;
  iVar4 = sub_98d20(0x10,param_1,param_2);
  piVar1[10] = iVar4;
  if (iVar4 == 0) {
    fatalerror(s_gwindowdefadr___OUT_OF_ROW_SPACE_000c48c7 + 1,param_1,param_2);
  }
  return piVar2;
}


// ================================================================================================
// sub_9a874 @ 0x9a874 [__watcall]
// ================================================================================================

uint * __watcall sub_9a874(uint param_1,undefined4 param_2,int unaff_EBX)

{
  uint uVar1;
  uint uVar2;
  uint *puVar3;
  uint uVar4;
  uint *puVar5;
  
  if (((param_1 != 0) && (param_1 < 0xfffffff9)) &&
     (uVar2 = param_1 + 7 & 0xfffffffc, uVar2 = (uVar2 - 0xc & -(uint)(0xb < uVar2)) + 0xc,
     uVar2 <= *(uint *)(unaff_EBX + 0x14))) {
    puVar3 = *(uint **)(unaff_EBX + 0xc);
    uVar4 = *(uint *)(unaff_EBX + 0x10);
    if (uVar2 <= uVar4) {
      puVar3 = *(uint **)(unaff_EBX + 0x28);
      uVar4 = 0;
    }
    do {
      uVar1 = *puVar3;
      if (uVar2 <= uVar1) {
        *(uint *)(unaff_EBX + 0x10) = uVar4;
        *(int *)(unaff_EBX + 0x18) = *(int *)(unaff_EBX + 0x18) + 1;
        uVar4 = puVar3[2];
        if (uVar1 - uVar2 < 0xc) {
          *(int *)(unaff_EBX + 0x1c) = *(int *)(unaff_EBX + 0x1c) + -1;
          uVar2 = puVar3[1];
          *(uint *)(uVar2 + 8) = uVar4;
          *(uint *)(uVar4 + 4) = uVar2;
          *(uint *)(unaff_EBX + 0xc) = uVar2;
        }
        else {
          puVar5 = (uint *)((int)puVar3 + uVar2);
          *(uint **)(unaff_EBX + 0xc) = puVar5;
          *puVar5 = uVar1 - uVar2;
          *puVar3 = uVar2;
          uVar2 = puVar3[1];
          puVar5[1] = uVar2;
          puVar5[2] = uVar4;
          *(uint **)(uVar2 + 8) = puVar5;
          *(uint **)(uVar4 + 4) = puVar5;
        }
        *puVar3 = *puVar3 | 1;
        return puVar3 + 1;
      }
      uVar4 = (uVar4 - uVar1 & -(uint)(uVar1 <= uVar4)) + uVar1;
      puVar3 = (uint *)puVar3[2];
    } while (puVar3 != (uint *)(unaff_EBX + 0x20U));
    *(uint *)(unaff_EBX + 0x14) = uVar4;
  }
  return (uint *)0x0;
}


// ================================================================================================
// sub_9a917 @ 0x9a917 [__watcall]
// ================================================================================================

void __watcall sub_9a917(void)

{
  return;
}


// ================================================================================================
// sub_9a91c @ 0x9a91c [__watcall]
// ================================================================================================

void __watcall sub_9a91c(undefined4 *param_1,undefined4 param_2,int unaff_EBX)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint *puVar4;
  uint *puVar5;
  uint *puVar6;
  
  if (param_1 == (undefined4 *)0x0) {
    return;
  }
  puVar4 = param_1 + -1;
  if ((*puVar4 & 1) == 0) {
    return;
  }
  uVar3 = *puVar4 & 0xfffffffe;
  puVar6 = (uint *)((int)puVar4 + uVar3);
  if ((*puVar6 & 1) == 0) {
    if (puVar6 == *(uint **)(unaff_EBX + 0xc)) {
      *(uint **)(unaff_EBX + 0xc) = puVar4;
    }
    *puVar4 = uVar3 + *puVar6;
    uVar3 = puVar6[1];
    puVar6 = (uint *)puVar6[2];
    *(uint **)(uVar3 + 8) = puVar6;
    puVar6[1] = uVar3;
    *(int *)(unaff_EBX + 0x1c) = *(int *)(unaff_EBX + 0x1c) + -1;
  }
  else {
    *puVar4 = uVar3;
    puVar6 = *(uint **)(unaff_EBX + 0xc);
    if (puVar4 < puVar6) {
      if (((uint *)puVar6[1] < puVar4) || (puVar6 = *(uint **)(unaff_EBX + 0x28), puVar4 < puVar6))
      goto LAB_0009a9da;
    }
    else {
      puVar6 = (uint *)puVar6[2];
      if ((puVar4 < puVar6) ||
         (puVar6 = (uint *)(unaff_EBX + 0x20), *(uint **)(unaff_EBX + 0x24) < puVar4))
      goto LAB_0009a9da;
    }
    uVar3 = *(uint *)(unaff_EBX + 0x1c);
    uVar1 = *(uint *)(unaff_EBX + 0x18) / (uVar3 + 1);
    if (uVar1 < uVar3) {
      iVar2 = uVar1 * 2;
      if (*(int *)(unaff_EBX + 0x18) - uVar3 <= uVar3) {
        iVar2 = 0;
      }
      puVar6 = (uint *)((int)puVar4 + *puVar4);
      do {
        uVar3 = *puVar6;
        if ((uVar3 & 1) == 0) goto LAB_0009a9da;
        if (uVar3 == 0xffffffff) break;
        puVar6 = (uint *)((int)puVar6 + (uVar3 & 0xfffffffe));
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
    }
    puVar6 = *(uint **)(unaff_EBX + 0xc);
    if (puVar4 < puVar6) {
      puVar6 = *(uint **)(unaff_EBX + 0x28);
    }
    while (((puVar6 <= puVar4 && (puVar6 = (uint *)puVar6[2], puVar6 <= puVar4)) &&
           (puVar6 = (uint *)puVar6[2], puVar6 <= puVar4))) {
      puVar6 = (uint *)puVar6[2];
    }
  }
LAB_0009a9da:
  puVar5 = (uint *)puVar6[1];
  uVar3 = *puVar4;
  if ((uint *)((int)puVar5 + *puVar5) == puVar4) {
    uVar3 = uVar3 + *puVar5;
    *puVar5 = uVar3;
    if (puVar4 == *(uint **)(unaff_EBX + 0xc)) {
      *(uint **)(unaff_EBX + 0xc) = puVar5;
    }
  }
  else {
    *(int *)(unaff_EBX + 0x1c) = *(int *)(unaff_EBX + 0x1c) + 1;
    param_1[1] = puVar6;
    *param_1 = puVar5;
    puVar5[2] = (uint)puVar4;
    puVar6[1] = (uint)puVar4;
    puVar5 = puVar4;
  }
  *(int *)(unaff_EBX + 0x18) = *(int *)(unaff_EBX + 0x18) + -1;
  if ((puVar5 < *(uint **)(unaff_EBX + 0xc)) && (*(uint *)(unaff_EBX + 0x10) < uVar3)) {
    *(uint *)(unaff_EBX + 0x10) = uVar3;
  }
  if (*(uint *)(unaff_EBX + 0x14) < uVar3) {
    *(uint *)(unaff_EBX + 0x14) = uVar3;
  }
  return;
}


// ================================================================================================
// FUN_0009aa22 @ 0x9aa22
// ================================================================================================

void __watcall FUN_0009aa22(void)

{
  return;
}


// ================================================================================================
// sub_9aa27 @ 0x9aa27 [__watcall]
// ================================================================================================

void __watcall sub_9aa27(int param_1)

{
  int iVar1;
  int iVar2;
  
  if (param_1 == dword_d43ec) {
    dword_d43ec = *(int *)(dword_d43ec + 8);
  }
  if (param_1 == dword_d43e8) {
    dword_d43e8 = *(int *)(dword_d43e8 + 8);
  }
  iVar1 = *(int *)(param_1 + 4);
  iVar2 = *(int *)(param_1 + 8);
  if (iVar1 != 0) {
    *(int *)(iVar1 + 8) = iVar2;
  }
  if (iVar2 != 0) {
    *(int *)(iVar2 + 4) = iVar1;
  }
  return;
}


// ================================================================================================
// sub_9aa66 @ 0x9aa66 [__watcall]
// ================================================================================================

undefined8 __watcall sub_9aa66(undefined4 param_1)

{
  int iVar1;
  code *pcVar2;
  int *piVar3;
  undefined2 *puVar4;
  undefined2 in_ES;
  byte bVar5;
  undefined8 uVar6;
  undefined4 uStack_18;
  
  uVar6 = CONCAT44(dword_d43e8,param_1);
  puVar4 = (undefined2 *)&stack0xffffffec;
  while (piVar3 = (int *)((ulonglong)uVar6 >> 0x20), piVar3 != (int *)0x0) {
    if (*(int *)piVar3[9] + 0x2c == *piVar3) {
      iVar1 = piVar3[2];
      *(undefined4 *)(puVar4 + -2) = 0x9aa94;
      sub_9aa27(piVar3,piVar3,piVar3 + -2,iVar1);
      bVar5 = 0;
      if (piVar3[-1] == 0) {
        pcVar2 = (code *)swi(0x31);
        uVar6 = (*pcVar2)();
        puVar4 = puVar4 + 2;
      }
      else {
        puVar4[-2] = in_ES;
        pcVar2 = (code *)swi(0x21);
        uVar6 = (*pcVar2)();
        uVar6 = CONCAT44((int)((ulonglong)uVar6 >> 0x20),
                         ((int)uVar6 << 1 | (uint)bVar5) >> 1 | (uint)((bVar5 & 1) != 0) << 0x1f);
        in_ES = *puVar4;
        puVar4 = puVar4 + 2;
      }
    }
    else {
      uVar6 = CONCAT44(piVar3[2],*(int *)piVar3[9] + 0x2c);
    }
  }
  return CONCAT44(*(undefined4 *)(puVar4 + 4),(int)uVar6);
}


// ================================================================================================
// sub_9aac4 @ 0x9aac4 [__watcall]
// ================================================================================================

uint * __watcall sub_9aac4(int *param_1,uint unaff_EDX)

{
  undefined2 uVar1;
  undefined2 uVar2;
  code *pcVar3;
  undefined2 *puVar4;
  uint *puVar5;
  uint *puVar6;
  undefined2 extraout_CX;
  int *extraout_EDX;
  uint3 uVar9;
  int extraout_EDX_00;
  uint uVar7;
  int *piVar8;
  byte bVar10;
  
  sub_9aa66();
  piVar8 = dword_d43e8;
  while( true ) {
    if (piVar8 == (int *)0x0) {
      return (uint *)0x0;
    }
    if (param_1 < piVar8) {
      return (uint *)0x0;
    }
    if (piVar8 + 0xb == param_1) break;
    piVar8 = (int *)piVar8[2];
  }
  sub_9aa27(piVar8);
  if (extraout_EDX[-1] != 0) {
    return (uint *)0x0;
  }
  uVar9 = (uint3)(*extraout_EDX + (unaff_EDX - *param_1) + 0x100b >> 8) & 0xfffff0;
  bVar10 = (((uint)uVar9 << 8) >> 0xf & 1) != 0;
  uVar1 = *(undefined2 *)(extraout_EDX + -2);
  uVar2 = *(undefined2 *)((int)extraout_EDX + -6);
  pcVar3 = (code *)swi(0x31);
  (*pcVar3)();
  puVar4 = (undefined2 *)(1 - (uint)bVar10);
  if (puVar4 != (undefined2 *)0x0) {
    puVar4 = (undefined2 *)CONCAT22((short)(uVar9 >> 8),extraout_CX);
    *puVar4 = uVar1;
    puVar4[1] = uVar2;
  }
  if (puVar4 != (undefined2 *)0x0) {
    piVar8 = (int *)(puVar4 + 4);
    *(undefined4 *)(puVar4 + 2) = 0;
    *piVar8 = extraout_EDX_00 + -0xc;
    puVar5 = (uint *)sub_9abae(piVar8);
    *(undefined4 *)(puVar4 + 0x10) = 1;
    uVar7 = *puVar5;
    if (0xb < uVar7 - unaff_EDX) {
      *puVar5 = unaff_EDX | 1;
      puVar6 = (uint *)((int)puVar5 + (unaff_EDX | 1) & 0xfffffffe);
      uVar7 = uVar7 - unaff_EDX | 1;
      *puVar6 = uVar7;
      *(undefined4 *)(puVar4 + 0xe) = 0xffffffff;
      *(int *)(puVar4 + 0x10) = *(int *)(puVar4 + 0x10) + 1;
      sub_91a67(puVar6 + 1,uVar7,piVar8,puVar5);
      return puVar5;
    }
    return puVar5;
  }
  return (uint *)0x0;
}


// ================================================================================================
// sub_9abae @ 0x9abae [__watcall]
// ================================================================================================

undefined8 __watcall sub_9abae(int *param_1,undefined4 unaff_EDX)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  
  piVar1 = dword_d43e8;
  piVar3 = (int *)0x0;
  while ((piVar2 = piVar1, piVar2 != (int *)0x0 && (piVar2 <= param_1))) {
    piVar3 = piVar2;
    piVar1 = (int *)piVar2[2];
  }
  param_1[1] = (int)piVar3;
  param_1[2] = (int)piVar2;
  piVar1 = param_1;
  if (piVar3 != (int *)0x0) {
    piVar3[2] = (int)param_1;
    piVar1 = dword_d43e8;
  }
  dword_d43e8 = piVar1;
  if (piVar2 != (int *)0x0) {
    piVar2[1] = (int)param_1;
  }
  piVar1 = param_1 + 8;
  piVar3 = param_1 + 0xb;
  param_1[8] = 0;
  param_1[4] = 0;
  param_1[6] = 0;
  param_1[7] = 0;
  param_1[9] = (int)piVar1;
  param_1[10] = (int)piVar1;
  param_1[3] = (int)piVar1;
  *piVar3 = *param_1 + -0x2c;
  *(undefined4 *)((int)piVar3 + *param_1 + -0x2c) = 0xffffffff;
  return CONCAT44(unaff_EDX,piVar3);
}


// ================================================================================================
// sub_9ac22 @ 0x9ac22 [__watcall]
// ================================================================================================

longlong __watcall sub_9ac22(undefined4 param_1,uint unaff_EDX)

{
  int *piVar1;
  undefined3 uVar2;
  ushort in_DS;
  
  if (dword_d43e8 != 0) {
    piVar1 = *(int **)(dword_d43e8 + 0x24);
    if (((1 < byte_d4d06) && (byte_d4d06 < 9)) && (byte_d4d08 == '\0')) {
      uVar2 = SegmentLimit((uint)in_DS);
      dword_d4cd8 = (ushort)uVar2 + 1;
    }
    if ((int)piVar1 + *piVar1 + 4 == dword_d4cd8) {
      return CONCAT44(unaff_EDX,*piVar1);
    }
  }
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// sub_9ac70 @ 0x9ac70 [__watcall]
// ================================================================================================

undefined8 __watcall sub_9ac70(uint param_1,undefined4 param_2,int unaff_EBX)

{
  code *pcVar1;
  bool bVar2;
  undefined2 *puVar3;
  int iVar4;
  int *piVar5;
  undefined2 extraout_CX;
  undefined2 extraout_CX_00;
  undefined2 extraout_DX;
  undefined *puVar6;
  uint unaff_ESI;
  undefined *unaff_EDI;
  byte bVar7;
  
  sub_9aa66();
  bVar7 = (param_1 >> 0xf & 1) != 0;
  pcVar1 = (code *)swi(0x31);
  (*pcVar1)();
  puVar6 = &stack0xffffffec;
  puVar3 = (undefined2 *)(1 - (uint)bVar7);
  if (puVar3 != (undefined2 *)0x0) {
    puVar3 = (undefined2 *)CONCAT22((short)(param_1 >> 0x10),extraout_CX);
    *puVar3 = (short)unaff_EDI;
    puVar3[1] = (short)unaff_ESI;
  }
  if (puVar3 == (undefined2 *)0x0) {
    if ((dword_f58e0 & 0xfff00000) != 0) {
      dword_f58e0 = 0xfffff;
    }
    puVar6 = &stack0xffffffec;
    if (unaff_EDI < &UNK_00010001) {
      bVar7 = 0;
      pcVar1 = (code *)swi(0x21);
      (*pcVar1)();
      puVar6 = &stack0xfffffff0;
      if ((bVar7 & 1) == 0) {
        bVar7 = (unaff_ESI >> 3 & 1) != 0;
        pcVar1 = (code *)swi(0x21);
        iVar4 = (*pcVar1)();
        bVar2 = (bVar7 & 1) != 0;
        pcVar1 = (code *)swi(0x21);
        (*pcVar1)();
        puVar6 = &stack0xfffffff8;
        if (!bVar2) {
          pcVar1 = (code *)swi(0x31);
          (*pcVar1)();
          puVar6 = &stack0xfffffffc;
          piVar5 = (int *)(CONCAT22(extraout_CX_00,extraout_DX) + 8);
          *(uint *)(CONCAT22(extraout_CX_00,extraout_DX) + 4) =
               (iVar4 << 1 | (uint)bVar7) >> 1 | (uint)bVar2 << 0x1f;
          *piVar5 = unaff_EBX + -8;
          goto LAB_0009ad3a;
        }
      }
    }
    piVar5 = (int *)0x0;
  }
  else {
    piVar5 = (int *)(puVar3 + 4);
    *piVar5 = (int)(unaff_EDI + -8);
    *(undefined4 *)(puVar3 + 2) = 0;
  }
LAB_0009ad3a:
  return CONCAT44(*(undefined4 *)(puVar6 + 0xc),piVar5);
}


// ================================================================================================
// sub_9ad43 @ 0x9ad43 [__watcall]
// ================================================================================================

undefined8 __watcall sub_9ad43(uint param_1)

{
  code *pcVar1;
  int iVar2;
  uint *puVar3;
  uint uVar4;
  uint *puVar5;
  uint *puVar6;
  uint *puVar7;
  byte bVar8;
  undefined8 uVar9;
  uint local_18;
  
  puVar7 = &local_18;
  local_18 = param_1;
  puVar5 = &local_18;
  if ((dword_d5670 != 0) && (puVar5 = &local_18, dword_d4cd8 != -2)) {
    iVar2 = sub_9af36(&local_18);
    if (iVar2 == 0) goto LAB_0009ad3a;
    bVar8 = byte_d4d06 == '\0';
    if (byte_d4d06 == '\x01') {
      puVar3 = (uint *)sub_9ac70(local_18);
      puVar6 = puVar3;
      puVar7 = &local_18;
      if (puVar3 != (uint *)0x0) {
        local_18 = *puVar3;
        puVar7 = &local_18;
      }
    }
    else {
      pcVar1 = (code *)swi(0x21);
      uVar4 = (*pcVar1)();
      puVar7 = (uint *)&stack0xffffffec;
      puVar6 = (uint *)~-(uint)bVar8;
      puVar3 = (uint *)(uVar4 & (uint)puVar6);
    }
    puVar5 = puVar7;
    if (((puVar3 != (uint *)0x0) && (uVar4 = *puVar7 - 4, uVar4 <= *puVar7)) &&
       (*puVar7 = uVar4, 0x37 < uVar4)) {
      *puVar3 = uVar4;
      puVar7[-1] = 0x9adc7;
      uVar9 = sub_9abae(puVar3,puVar3,puVar6);
      iVar2 = (int)((ulonglong)uVar9 >> 0x20);
      puVar5 = (uint *)uVar9;
      uVar4 = *puVar5;
      *puVar7 = uVar4;
      *puVar5 = uVar4 | 1;
      *(undefined4 *)(iVar2 + 0x14) = 0xffffffff;
      *(int *)(iVar2 + 0x18) = *(int *)(iVar2 + 0x18) + 1;
      puVar7[-1] = 0x9ade8;
      sub_91a67(puVar5 + 1);
      iVar2 = 1;
      goto LAB_0009ad3a;
    }
  }
  puVar7 = puVar5;
  iVar2 = 0;
LAB_0009ad3a:
  return CONCAT44(*(undefined4 *)((int)puVar7 + 0xc),iVar2);
}


// ================================================================================================
// sub_9adf2 @ 0x9adf2 [__watcall]
// ================================================================================================

undefined8 __watcall sub_9adf2(uint param_1,undefined4 unaff_EDX)

{
  int *piVar1;
  undefined3 uVar2;
  int iVar3;
  uint *puVar4;
  uint *puVar5;
  uint uVar6;
  uint *puVar7;
  ushort in_DS;
  undefined8 uVar8;
  uint local_18;
  
  local_18 = param_1;
  if (((byte_d4d06 == 1) && (byte_d4d07 == '\0')) || (byte_d4d06 == 9)) {
    iVar3 = sub_9ad43(param_1);
    goto LAB_0009af2d;
  }
  if ((dword_d5670 == 0) || (dword_d4cd8 == 0xfffffffe)) goto LAB_0009ae29;
  iVar3 = sub_9af36(&local_18);
  if (iVar3 == 0) goto LAB_0009af2d;
  if (((1 < byte_d4d06) && (byte_d4d06 < 9)) && (byte_d4d08 == '\0')) {
    uVar2 = SegmentLimit((uint)in_DS);
    dword_d4cd8 = (ushort)uVar2 + 1;
  }
  uVar6 = local_18 + dword_d4cd8;
  if (uVar6 < dword_d4cd8) {
    uVar6 = 0xfffffffe;
  }
  uVar8 = sub_a2c54(uVar6);
  puVar7 = (uint *)((ulonglong)uVar8 >> 0x20);
  puVar4 = (uint *)uVar8;
  if (((puVar4 != (uint *)0xffffffff) && (puVar4 < (uint *)0xfffffff9)) && (puVar4 < puVar7)) {
    uVar6 = (int)puVar7 - (int)puVar4;
    local_18 = uVar6 - 4;
    puVar7 = dword_d43e8;
    if (local_18 <= uVar6) {
      for (; ((puVar7 != (uint *)0x0 && ((uint *)puVar7[2] != (uint *)0x0)) &&
             ((puVar4 < puVar7 || ((uint *)puVar7[2] <= puVar4)))); puVar7 = (uint *)puVar7[2]) {
      }
      if (puVar7 == (uint *)0x0) {
LAB_0009aef0:
        if (local_18 < 0x38) goto LAB_0009ae29;
        *puVar4 = local_18;
        uVar8 = sub_9abae(puVar4,puVar4);
        local_18 = *(uint *)uVar8;
      }
      else {
        puVar5 = (uint *)(*puVar7 + (int)puVar7);
        uVar8 = CONCAT44(puVar7,puVar5);
        if (puVar4 + -1 != puVar5) goto LAB_0009aef0;
        *puVar7 = *puVar7 + uVar6;
        *(undefined4 *)((int)puVar5 + uVar6) = 0xffffffff;
        local_18 = uVar6;
      }
      iVar3 = (int)((ulonglong)uVar8 >> 0x20);
      *(uint *)uVar8 = local_18 | 1;
      piVar1 = (int *)(iVar3 + 0x18);
      *piVar1 = *piVar1 + 1;
      *(undefined4 *)(iVar3 + 0x14) = 0xffffffff;
      sub_91a67((uint *)uVar8 + 1);
      iVar3 = 1;
      goto LAB_0009af2d;
    }
  }
LAB_0009ae29:
  iVar3 = 0;
LAB_0009af2d:
  return CONCAT44(unaff_EDX,iVar3);
}


// ================================================================================================
// sub_9af36 @ 0x9af36 [__watcall]
// ================================================================================================

longlong __watcall sub_9af36(uint *param_1,uint unaff_EDX)

{
  uint uVar1;
  undefined8 uVar2;
  
  uVar1 = *param_1 + 3 & 0xfffffffc;
  if (uVar1 != 0) {
    if (((byte_d4d06 == '\x01') && (byte_d4d07 == '\0')) || (byte_d4d06 == '\t')) {
      uVar1 = uVar1 + 8;
    }
    else {
      uVar2 = sub_9ac22();
      uVar1 = (int)((ulonglong)uVar2 >> 0x20) - (int)uVar2;
    }
    *param_1 = uVar1;
    uVar1 = uVar1 + 0x3c;
    if (*param_1 <= uVar1) {
      if (uVar1 < dword_d5674) {
        uVar1 = dword_d5674 & 0xfffffffe;
      }
      *param_1 = uVar1;
      uVar1 = uVar1 + 0xfff;
      if (*param_1 <= uVar1) {
        *param_1 = (uint)((uint3)(uVar1 >> 8) & 0xfffff0) << 8;
        return CONCAT44(unaff_EDX,(uint)((uVar1 & 0xfffff000) != 0));
      }
    }
  }
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// sub_9afad @ 0x9afad [__watcall]
// ================================================================================================

undefined4 __watcall sub_9afad(void)

{
  return 0;
}


// ================================================================================================
// sub_9afb0 @ 0x9afb0 [__watcall]
// ================================================================================================

int __watcall sub_9afb0(int param_1)

{
  if ((0x40 < param_1) && (param_1 < 0x5b)) {
    param_1 = param_1 + 0x20;
  }
  return param_1;
}


// ================================================================================================
// sub_9afbe @ 0x9afbe [__watcall]
// ================================================================================================

undefined8 __watcall sub_9afbe(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX)

{
  undefined4 *__s;
  undefined4 *puVar1;
  uint uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  
  if (dword_edf00 == (undefined4 *)0x0) {
    for (__s = (undefined4 *)&unk_d4d18; __s < &aA_d4f20; __s = (undefined4 *)((int)__s + 0x1a)) {
      if ((*(byte *)(__s + 3) & 3) == 0) {
        uVar3 = sub_91984(8);
        uVar4 = CONCAT44((int)((ulonglong)uVar3 >> 0x20),__s);
        puVar1 = (undefined4 *)uVar3;
        if (puVar1 == (undefined4 *)0x0) goto LAB_0009b054;
        uVar2 = 3;
        goto LAB_0009b02f;
      }
    }
    uVar2 = 0x4003;
    uVar4 = sub_91984(0x22);
    puVar1 = (undefined4 *)uVar4;
    if (puVar1 == (undefined4 *)0x0) {
LAB_0009b054:
      sub_9878a(5,(int)((ulonglong)uVar4 >> 0x20),unaff_EBX,(int)uVar4);
      __s = (undefined4 *)0x0;
      goto LAB_0009b060;
    }
    __s = puVar1 + 2;
  }
  else {
    __s = (undefined4 *)dword_edf00[1];
    uVar2 = (uint)((ushort)__s[3] & 0x4003 | 3);
    puVar1 = dword_edf00;
    dword_edf00 = (undefined4 *)*dword_edf00;
  }
LAB_0009b02f:
  memset(__s,0,0x1a);
  __s[3] = uVar2;
  puVar1[1] = __s;
  *puVar1 = dword_f24c8;
  dword_f24c8 = puVar1;
LAB_0009b060:
  return CONCAT44(unaff_EDX,__s);
}


// ================================================================================================
// sub_9b066 @ 0x9b066 [__watcall]
// ================================================================================================

void __watcall sub_9b066(int param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  puVar1 = &dword_f24c8;
  do {
    puVar2 = puVar1;
    puVar1 = (undefined4 *)*puVar2;
    if (puVar1 == (undefined4 *)0x0) {
      return;
    }
  } while (param_1 != puVar1[1]);
  *(byte *)(param_1 + 0xc) = *(byte *)(puVar1[1] + 0xc) | 3;
  *puVar2 = *puVar1;
  *puVar1 = dword_edf00;
  dword_edf00 = puVar1;
  return;
}


// ================================================================================================
// sub_9b09f @ 0x9b09f [__watcall]
// ================================================================================================

void __watcall
sub_9b09f(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  undefined4 *extraout_EDX;
  
  while (dword_edf00 != (undefined4 *)0x0) {
    sub_91a67(dword_edf00,*dword_edf00,unaff_EBX,unaff_ECX,unaff_EDX);
    dword_edf00 = extraout_EDX;
  }
  return;
}


// ================================================================================================
// sub_9b0bd @ 0x9b0bd [__watcall]
// ================================================================================================

undefined4 __watcall sub_9b0bd(int param_1,int *unaff_EDX)

{
  *(byte *)(unaff_EDX + 3) = *(byte *)(unaff_EDX + 3) & 0xef;
  if ((param_1 <= unaff_EDX[1]) && (unaff_EDX[2] - *unaff_EDX <= param_1)) {
    *unaff_EDX = *unaff_EDX + param_1;
    unaff_EDX[1] = unaff_EDX[1] - param_1;
    return 0;
  }
  unaff_EDX[1] = 0;
  *unaff_EDX = unaff_EDX[2];
  return 1;
}


// ================================================================================================
// sub_9b0ff @ 0x9b0ff [__watcall]
// ================================================================================================

/* WARNING: Removing unreachable block (ram,0x0009b179) */

undefined4 __watcall sub_9b0ff(undefined4 *param_1,int unaff_EDX,uint unaff_EBX)

{
  int iVar1;
  __off_t _Var2;
  int iVar3;
  
  if ((*(byte *)(param_1 + 3) & 6) == 0) {
    if (unaff_EBX == 0) {
      iVar1 = sub_a2d16(param_1[4]);
      iVar1 = sub_9b0bd(unaff_EDX - (iVar1 - param_1[1]),param_1);
      if ((iVar1 != 0) && (_Var2 = lseek(param_1[4],unaff_EDX,0), _Var2 == -1)) {
        return 0xffffffff;
      }
    }
    else if (unaff_EBX < 2) {
      iVar1 = param_1[1];
      iVar3 = sub_9b0bd(unaff_EDX,param_1);
      if ((iVar3 != 0) && (_Var2 = lseek(param_1[4],unaff_EDX - iVar1,unaff_EBX), _Var2 == -1)) {
        return 0xffffffff;
      }
    }
    else {
      if (unaff_EBX != 2) goto LAB_0009b125;
      *param_1 = param_1[2];
      *(byte *)(param_1 + 3) = *(byte *)(param_1 + 3) & 0xef;
      param_1[1] = 0;
      _Var2 = lseek(param_1[4],unaff_EDX,2);
      if (_Var2 == -1) {
        return 0xffffffff;
      }
    }
  }
  else {
    if ((*(byte *)((int)param_1 + 0xd) & 0x10) == 0) {
      if (unaff_EBX == 1) {
        unaff_EDX = unaff_EDX - param_1[1];
      }
      param_1[1] = 0;
      *param_1 = param_1[2];
    }
    else {
      iVar1 = sub_9b232(param_1);
      if (iVar1 != 0) {
        if (unaff_EBX != 0) {
          return 0xffffffff;
        }
        if (-1 < unaff_EDX) {
          return 0xffffffff;
        }
LAB_0009b125:
        sub_9878a(9);
        return 0xffffffff;
      }
    }
    *(byte *)(param_1 + 3) = *(byte *)(param_1 + 3) & 0xeb;
    _Var2 = lseek(param_1[4],unaff_EDX,unaff_EBX);
    if (_Var2 == -1) {
      return 0xffffffff;
    }
  }
  return 0;
}


// ================================================================================================
// sub_9b1fb @ 0x9b1fb [__watcall]
// ================================================================================================

void __watcall sub_9b1fb(int param_1)

{
  byte bVar1;
  int iVar2;
  undefined8 uVar3;
  
  if ((*(byte *)(param_1 + 0xd) & 0x20) == 0) {
    uVar3 = sub_9b710(*(undefined4 *)(param_1 + 0x10));
    iVar2 = (int)((ulonglong)uVar3 >> 0x20);
    if ((int)uVar3 != 0) {
      bVar1 = *(byte *)(iVar2 + 0xd);
      *(byte *)(iVar2 + 0xd) = bVar1 | 0x20;
      if ((bVar1 & 7) == 0) {
        *(byte *)(iVar2 + 0xd) = bVar1 | 0x22;
      }
    }
  }
  return;
}


// ================================================================================================
// sub_9b22c @ 0x9b22c [__watcall]
// ================================================================================================

undefined4 __watcall sub_9b22c(void)

{
  return dword_d4ce4;
}


// ================================================================================================
// sub_9b232 @ 0x9b232 [__watcall]
// ================================================================================================

undefined8 __watcall sub_9b232(undefined4 *param_1,undefined4 unaff_EDX)

{
  ushort uVar1;
  int iVar2;
  undefined4 uVar3;
  
  uVar3 = 0;
  if ((*(byte *)((int)param_1 + 0xd) & 0x10) == 0) {
    if ((param_1[2] != 0) &&
       (uVar1 = *(ushort *)(param_1 + 3), *(byte *)(param_1 + 3) = *(byte *)(param_1 + 3) & 0xef,
       (uVar1 & 0x2000) == 0)) {
      iVar2 = param_1[1];
      if (iVar2 != 0) {
        iVar2 = lseek(param_1[4],-iVar2,1);
      }
      if (iVar2 == -1) {
        *(byte *)(param_1 + 3) = *(byte *)(param_1 + 3) | 0x20;
        uVar3 = 0xffffffff;
      }
    }
  }
  else {
    *(byte *)((int)param_1 + 0xd) = *(byte *)((int)param_1 + 0xd) & 0xef;
    if (((*(byte *)(param_1 + 3) & 2) != 0) && (param_1[2] != 0)) {
      iVar2 = sub_a2e02(param_1[4],param_1[2],param_1[1]);
      if (iVar2 == -1) {
        *(byte *)(param_1 + 3) = *(byte *)(param_1 + 3) | 0x20;
        uVar3 = 0xffffffff;
      }
      else if (iVar2 != param_1[1]) {
        sub_9878a(0xc);
        uVar3 = 0xffffffff;
        *(byte *)(param_1 + 3) = *(byte *)(param_1 + 3) | 0x20;
      }
    }
  }
  param_1[1] = 0;
  *param_1 = param_1[2];
  return CONCAT44(unaff_EDX,uVar3);
}


// ================================================================================================
// sub_9b2f1 @ 0x9b2f1 [__watcall]
// ================================================================================================

undefined8 __watcall sub_9b2f1(int param_1,undefined4 unaff_EDX)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined8 uVar4;
  
  uVar4 = sub_a2d16(*(undefined4 *)(param_1 + 0x10),param_1);
  iVar3 = (int)((ulonglong)uVar4 >> 0x20);
  iVar2 = (int)uVar4;
  if ((iVar2 != -1) && (iVar1 = *(int *)(iVar3 + 4), iVar1 != 0)) {
    if ((*(byte *)(iVar3 + 0xd) & 0x10) != 0) {
      return CONCAT44(unaff_EDX,iVar1 + iVar2);
    }
    iVar2 = iVar2 - iVar1;
  }
  return CONCAT44(unaff_EDX,iVar2);
}


// ================================================================================================
// sub_9b321 @ 0x9b321 [__watcall]
// ================================================================================================

longlong __watcall sub_9b321(undefined4 param_1,undefined4 param_2,uint unaff_EBX)

{
  code *pcVar1;
  undefined4 extraout_EDX;
  byte in_CF;
  
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  if ((in_CF & 1) == 0) {
    sub_9b783(extraout_EDX,0);
    return (ulonglong)unaff_EBX << 0x20;
  }
  sub_9878a(4,extraout_EDX,param_1);
  return CONCAT44(unaff_EBX,0xffffffff);
}


// ================================================================================================
// sub_9b353 @ 0x9b353 [__watcall]
// ================================================================================================

void __watcall
sub_9b353(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  byte bVar1;
  int extraout_EDX;
  undefined4 *puVar2;
  undefined8 uVar3;
  
  sub_9b1fb(param_1,param_1,unaff_EBX,unaff_ECX,unaff_EDX,unaff_ECX);
  if (*(int *)(extraout_EDX + 0x14) == 0) {
    if ((*(byte *)(extraout_EDX + 0xd) & 2) == 0) {
      if ((*(byte *)(extraout_EDX + 0xd) & 4) == 0) {
        *(undefined4 *)(extraout_EDX + 0x14) = 0x1000;
      }
      else {
        *(undefined4 *)(extraout_EDX + 0x14) = 1;
      }
    }
    else {
      *(undefined4 *)(extraout_EDX + 0x14) = 0x86;
    }
  }
  uVar3 = sub_91984(*(undefined4 *)(extraout_EDX + 0x14));
  puVar2 = (undefined4 *)((ulonglong)uVar3 >> 0x20);
  puVar2[2] = (int)uVar3;
  if ((int)uVar3 == 0) {
    puVar2[5] = 1;
    bVar1 = *(byte *)((int)puVar2 + 0xd) & 0xf8;
    puVar2[2] = puVar2 + 6;
    *(byte *)((int)puVar2 + 0xd) = bVar1;
    *(byte *)((int)puVar2 + 0xd) = bVar1 | 4;
  }
  else {
    *(byte *)(puVar2 + 3) = *(byte *)(puVar2 + 3) | 8;
  }
  puVar2[1] = 0;
  *puVar2 = puVar2[2];
  return;
}


// ================================================================================================
// sub_9b3ca @ 0x9b3ca [__watcall]
// ================================================================================================

uint __watcall sub_9b3ca(uint param_1,int *unaff_EDX)

{
  int iVar1;
  uint uVar2;
  int extraout_EDX;
  int *extraout_EDX_00;
  undefined8 uVar3;
  
  if ((*(byte *)(unaff_EDX + 3) & 2) == 0) {
    sub_9878a(4);
    *(byte *)(extraout_EDX + 0xc) = *(byte *)(extraout_EDX + 0xc) | 0x20;
LAB_0009b3e5:
    param_1 = 0xffffffff;
  }
  else {
    if (unaff_EDX[2] == 0) {
      sub_9b353(unaff_EDX);
      unaff_EDX = extraout_EDX_00;
    }
    uVar2 = 0x400;
    if ((param_1 == 10) && (uVar2 = 0x600, (*(byte *)(unaff_EDX + 3) & 0x40) == 0)) {
      *(byte *)((int)unaff_EDX + 0xd) = *(byte *)((int)unaff_EDX + 0xd) | 0x10;
      *(undefined *)*unaff_EDX = 0xd;
      iVar1 = unaff_EDX[1];
      *unaff_EDX = *unaff_EDX + 1;
      unaff_EDX[1] = iVar1 + 1;
      if (iVar1 + 1 == unaff_EDX[5]) {
        uVar3 = sub_9b232(unaff_EDX);
        unaff_EDX = (int *)((ulonglong)uVar3 >> 0x20);
        if ((int)uVar3 != 0) goto LAB_0009b3e5;
      }
    }
    *(byte *)((int)unaff_EDX + 0xd) = *(byte *)((int)unaff_EDX + 0xd) | 0x10;
    *(char *)*unaff_EDX = (char)param_1;
    iVar1 = unaff_EDX[1];
    *unaff_EDX = *unaff_EDX + 1;
    unaff_EDX[1] = iVar1 + 1;
    if (((uVar2 & unaff_EDX[3]) != 0) || (iVar1 + 1 == unaff_EDX[5])) {
      iVar1 = sub_9b232(unaff_EDX);
      if (iVar1 != 0) goto LAB_0009b3e5;
    }
    param_1 = param_1 & 0xff;
  }
  return param_1;
}


// ================================================================================================
// sub_9b498 @ 0x9b498 [__cdecl]
// ================================================================================================

void sub_9b498(int *param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  bool bVar8;
  int local_20;
  int local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  if (dword_d30c8 == 0) {
    sub_b704c(param_1);
  }
  else {
    uVar3 = param_1[1] * 0x10000 + (*param_1 >> 0x10 & 0xffffU) + 0x8000;
    local_14 = param_1[3] * 0x10000 + (param_1[2] >> 0x10 & 0xffffU) + 0x8000;
    uVar7 = (int)uVar3 >> 0x10 & 0xffff;
    uVar4 = (int)local_14 >> 0x10 & 0xffff;
    iVar2 = param_1[7];
    iVar6 = param_1[6];
    if (*(byte *)(param_1 + 0xd) < 10) {
      uVar3 = uVar3 & 0xffff;
      local_14 = local_14 & 0xffff;
      switch(*(byte *)(param_1 + 0xd)) {
      default:
        if (iVar6 != 0) {
          fillrect(uVar7,uVar4,iVar6,1,iVar2);
          return;
        }
        break;
      case 2:
        if (iVar6 != 0) {
          fillrect(uVar7,param_1[3],1,iVar6,iVar2);
          return;
        }
        break;
      case 3:
        iVar5 = param_1[3];
        while (iVar6 = iVar6 + -1, iVar6 != -1) {
          putpixel(uVar7,iVar5,iVar2);
          iVar5 = iVar5 + 1;
          uVar7 = uVar7 - 1;
        }
        break;
      case 4:
        iVar5 = param_1[3];
        while (iVar6 = iVar6 + -1, iVar6 != -1) {
          putpixel(uVar7,iVar5,iVar2);
          iVar5 = iVar5 + 1;
          uVar7 = uVar7 + 1;
        }
        break;
      case 5:
        uVar4 = param_1[0xc];
        local_20 = param_1[3];
        while (iVar6 = iVar6 + -1, iVar6 != -1) {
          iVar5 = local_20 + 1;
          putpixel(uVar7,local_20,iVar2);
          uVar3 = uVar3 + (uVar4 >> 0x10);
          local_20 = iVar5;
          if ((uVar3 & 0xffff0000) != 0) {
            uVar3 = uVar3 & 0xffff;
            uVar7 = uVar7 - 1;
          }
        }
        break;
      case 6:
        uVar4 = param_1[0xc];
        local_1c = param_1[3];
        while (iVar6 = iVar6 + -1, iVar6 != -1) {
          iVar5 = local_1c + 1;
          putpixel(uVar7,local_1c,iVar2);
          uVar3 = uVar3 + (uVar4 >> 0x10);
          local_1c = iVar5;
          if ((uVar3 & 0xffff0000) != 0) {
            uVar3 = uVar3 & 0xffff;
            uVar7 = uVar7 + 1;
          }
        }
        break;
      case 7:
        uVar3 = param_1[0xc];
        local_18 = local_14;
        while (iVar6 = iVar6 + -1, iVar6 != -1) {
          putpixel(uVar7,uVar4,iVar2);
          uVar7 = uVar7 - 1;
          uVar1 = local_18 + (uVar3 >> 0x10);
          local_18._2_2_ = (short)(uVar1 >> 0x10);
          bVar8 = local_18._2_2_ != 0;
          local_18 = uVar1;
          if (bVar8) {
            local_18 = uVar1 & 0xffff;
            uVar4 = uVar4 + 1;
          }
        }
        break;
      case 8:
        uVar3 = param_1[0xc];
        while (iVar6 = iVar6 + -1, iVar6 != -1) {
          putpixel(uVar7,uVar4,iVar2);
          uVar7 = uVar7 + 1;
          uVar1 = local_14 + (uVar3 >> 0x10);
          local_14._2_2_ = (short)(uVar1 >> 0x10);
          bVar8 = local_14._2_2_ != 0;
          local_14 = uVar1;
          if (bVar8) {
            local_14 = uVar1 & 0xffff;
            uVar4 = uVar4 + 1;
          }
        }
        break;
      case 9:
        putpixel(uVar7,uVar4,iVar2);
      }
    }
  }
  return;
}


// ================================================================================================
// sub_9b710 @ 0x9b710 [__watcall]
// ================================================================================================

undefined8 __watcall
sub_9b710(undefined4 param_1,undefined4 param_2,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  code *pcVar1;
  uint extraout_EDX;
  
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)(unaff_ECX,unaff_EBX);
  return CONCAT44(unaff_ECX,(uint)((extraout_EDX & 0x80) != 0));
}


// ================================================================================================
// sub_9b72e @ 0x9b72e [__watcall]
// ================================================================================================

longlong __watcall sub_9b72e(uint param_1,uint unaff_EDX)

{
  int iVar1;
  undefined8 uVar2;
  
  if (dword_d500c <= param_1) {
    return (ulonglong)unaff_EDX << 0x20;
  }
  if ((int)param_1 < 6) {
    iVar1 = param_1 * 4;
    if ((off_d5060[iVar1 + 1] & 0x40) == 0) {
      off_d5060[iVar1 + 1] = off_d5060[iVar1 + 1] | 0x40;
      uVar2 = sub_9b710(param_1);
      param_1 = (uint)((ulonglong)uVar2 >> 0x20);
      if ((int)uVar2 != 0) {
        off_d5060[iVar1 + 1] = off_d5060[iVar1 + 1] | 0x20;
      }
    }
  }
  return CONCAT44(unaff_EDX,*(undefined4 *)(off_d5060 + param_1 * 4));
}


// ================================================================================================
// sub_9b783 @ 0x9b783 [__watcall]
// ================================================================================================

void __watcall sub_9b783(int param_1,uint unaff_EDX)

{
  *(uint *)(off_d5060 + param_1 * 4) = unaff_EDX | 0x4000;
  return;
}


// ================================================================================================
// sub_9b798 @ 0x9b798 [__watcall]
// ================================================================================================

void __watcall sub_9b798(undefined2 *param_1,undefined4 param_2,byte *unaff_EBX)

{
  byte bVar1;
  int iVar2;
  undefined2 *puVar3;
  int in_FS_OFFSET;
  
  puVar3 = param_1;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  for (iVar2 = 0; iVar2 != 0; iVar2 = iVar2 + -1) {
    *(undefined *)puVar3 = 0;
    puVar3 = (undefined2 *)((int)puVar3 + 1);
  }
  for (; bVar1 = *unaff_EBX, bVar1 != 0; unaff_EBX = unaff_EBX + 1) {
    *(byte *)((int)param_1 + in_FS_OFFSET + ((int)(uint)bVar1 >> 3)) =
         *(byte *)((int)param_1 + in_FS_OFFSET + ((int)(uint)bVar1 >> 3)) | (&unk_c4c70)[bVar1 & 7];
  }
  return;
}


// ================================================================================================
// sub_9b7f5 @ 0x9b7f5 [__watcall]
// ================================================================================================

void __watcall sub_9b7f5(void *param_1,byte *unaff_EDX)

{
  byte bVar1;
  
  memset(param_1,0,0x20);
  for (; bVar1 = *unaff_EDX, bVar1 != 0; unaff_EDX = unaff_EDX + 1) {
    *(byte *)((int)param_1 + ((int)(uint)bVar1 >> 3)) =
         *(byte *)((int)param_1 + ((int)(uint)bVar1 >> 3)) | (&unk_c4c70)[bVar1 & 7];
  }
  return;
}


// ================================================================================================
// sub_9b833 @ 0x9b833 [__watcall]
// ================================================================================================

undefined8 __watcall sub_9b833(undefined4 *param_1,undefined4 unaff_EDX)

{
  uint uVar1;
  undefined4 *extraout_EDX;
  int iVar2;
  undefined8 uVar3;
  
  if ((*(byte *)(param_1 + 3) & 1) == 0) {
    sub_9878a(4);
    uVar1 = 0xffffffff;
    *(byte *)(extraout_EDX + 3) = *(byte *)(extraout_EDX + 3) | 0x20;
    param_1 = extraout_EDX;
  }
  else {
    iVar2 = param_1[1];
    param_1[1] = iVar2 + -1;
    if (iVar2 + -1 < 0) {
      uVar3 = sub_9b8bc(param_1);
      param_1 = (undefined4 *)((ulonglong)uVar3 >> 0x20);
      uVar1 = (uint)uVar3;
    }
    else {
      uVar1 = (uint)*(byte *)*param_1;
      *param_1 = (byte *)*param_1 + 1;
    }
  }
  uVar3 = CONCAT44(param_1,uVar1);
  if ((*(byte *)(param_1 + 3) & 0x40) == 0) {
    if (uVar1 == 0xd) {
      iVar2 = param_1[1];
      param_1[1] = iVar2 + -1;
      if (iVar2 + -1 < 0) {
        uVar3 = sub_9b8bc(param_1);
      }
      else {
        uVar3 = CONCAT44(param_1,(uint)*(byte *)*param_1);
        *param_1 = (byte *)*param_1 + 1;
      }
    }
    iVar2 = (int)((ulonglong)uVar3 >> 0x20);
    uVar1 = (uint)uVar3;
    if (uVar1 == 0x1a) {
      uVar1 = 0xffffffff;
      *(byte *)(iVar2 + 0xc) = *(byte *)(iVar2 + 0xc) | 0x10;
    }
  }
  return CONCAT44(unaff_EDX,uVar1);
}


// ================================================================================================
// sub_9b8bc @ 0x9b8bc [__watcall]
// ================================================================================================

undefined8 __watcall sub_9b8bc(undefined4 param_1,undefined4 unaff_EDX)

{
  byte *pbVar1;
  undefined4 *puVar2;
  undefined8 uVar3;
  
  uVar3 = sub_9b8eb(param_1,param_1);
  puVar2 = (undefined4 *)((ulonglong)uVar3 >> 0x20);
  if ((int)uVar3 == 0) {
    return CONCAT44(unaff_EDX,0xffffffff);
  }
  pbVar1 = (byte *)*puVar2;
  puVar2[1] = puVar2[1] + -1;
  *puVar2 = pbVar1 + 1;
  return CONCAT44(unaff_EDX,(uint)*pbVar1);
}


