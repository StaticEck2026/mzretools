// Decompiled by Ghidra from hockey.elf (via ledisasm ELF export)
// This is machine generated pseudo-C meant as a reference for porting, it does not compile as is.
#include "prototypes.h"

// ================================================================================================
// file_write_c @ 0x3a24f [__watcall]
// ================================================================================================

void __watcall file_write_c(void)

{
  __CHK(8);
  file_write();
  return;
}


// ================================================================================================
// file_read_d @ 0x3a266 [__watcall]
// ================================================================================================

void __watcall file_read_d(void)

{
  __CHK(8);
  file_read();
  return;
}


// ================================================================================================
// file_write_d @ 0x3a27d [__watcall]
// ================================================================================================

void __watcall file_write_d(void)

{
  __CHK(8);
  file_write();
  return;
}


// ================================================================================================
// schedule_write_record @ 0x3a28f [__watcall]
// ================================================================================================

void __watcall schedule_write_record(undefined4 param_1,undefined4 unaff_EDX,int unaff_EBX)

{
  __CHK(0xc);
  file_write(param_1,unaff_EDX,unaff_EBX * 6 + 2,6);
  return;
}


// ================================================================================================
// db_write_team_record @ 0x3a2b8 [__watcall]
// ================================================================================================

void __watcall db_write_team_record(undefined4 param_1,undefined4 unaff_EDX,int unaff_EBX)

{
  __CHK(0x10);
  file_write(param_1,unaff_EDX,unaff_EBX * 0x2e8,0x2e8);
  return;
}


// ================================================================================================
// db_read_record_4c @ 0x3a2ee [__watcall]
// ================================================================================================

void __watcall db_read_record_4c(undefined4 param_1,undefined4 unaff_EDX,int unaff_EBX)

{
  __CHK(0x10);
  file_read(param_1,unaff_EDX,unaff_EBX * 0x4c,0x4c);
  return;
}


// ================================================================================================
// pinfo_read_record @ 0x3a31e [__watcall]
// ================================================================================================

void __watcall pinfo_read_record(undefined4 param_1,undefined4 unaff_EDX,int unaff_EBX)

{
  __CHK(0xc);
  file_read(param_1,unaff_EDX,unaff_EBX * 0x1e + 0x20,0x1e);
  return;
}


// ================================================================================================
// league_write_team_entry @ 0x3a347 [__watcall]
// ================================================================================================

void __watcall league_write_team_entry(undefined4 param_1,undefined4 unaff_EDX,int unaff_EBX)

{
  __CHK(0xc);
  file_write(param_1,unaff_EDX,unaff_EBX * 0x1e + 0x20,0x1e);
  return;
}


// ================================================================================================
// file_read_e @ 0x3a36b [__watcall]
// ================================================================================================

void __watcall file_read_e(void)

{
  __CHK(8);
  file_read();
  return;
}


// ================================================================================================
// file_read_f @ 0x3a380 [__watcall]
// ================================================================================================

void __watcall file_read_f(void)

{
  __CHK(8);
  file_read();
  return;
}


// ================================================================================================
// password_prompt @ 0x3a395 [__watcall]
// ================================================================================================

int __watcall password_prompt(int param_1,int unaff_EDX)

{
  int iVar1;
  int iVar2;
  char *pcVar3;
  char acStack_88 [84];
  char acStack_34 [12];
  undefined auStack_28 [4];
  undefined auStack_24 [4];
  undefined local_20 [4];
  int iStack_18;
  
  __CHK(0xa0);
  iVar2 = 0;
  while( true ) {
    iStack_18 = 0;
    strcpy(acStack_88,aEnterPasswordFor);
    pcVar3 = (char *)(unaff_EDX + param_1 * 0x1e);
    strcat(acStack_88,pcVar3);
    iVar1 = text_entry_dialog(acStack_88,acStack_34,10,0x3c,0,0,0,0,6);
    if (iVar1 == 0x1b) {
      return -1;
    }
    pcVar3 = pcVar3 + 0xb;
    password_scramble(pcVar3,param_1);
    iVar1 = strcmp(pcVar3,acStack_34);
    if (iVar1 != 0) {
      getmouse(local_20,auStack_24,auStack_28);
      message_dialog(0xffffffff,0xffffffff,&off_c7965,1,0,0,auStack_24,auStack_28,0xffffffff);
      iStack_18 = -1;
    }
    password_scramble(param_1 * 0x1e + unaff_EDX + 0xb,param_1);
    iVar2 = iVar2 + 1;
    if (iStack_18 == 0) break;
    if (2 < iVar2) {
      return iStack_18;
    }
  }
  return 0;
}


// ================================================================================================
// master_password_prompt @ 0x3a49e [__watcall]
// ================================================================================================

int __watcall master_password_prompt(int param_1,int unaff_EDX,undefined4 unaff_EBX)

{
  int iVar1;
  int iVar2;
  char acStack_84 [84];
  char acStack_30 [12];
  undefined auStack_24 [4];
  undefined auStack_20 [4];
  undefined local_1c [4];
  int iStack_14;
  
  __CHK(0x9c);
  iVar2 = 0;
  while( true ) {
    iStack_14 = 0;
    strcpy(acStack_84,(char *)(unaff_EDX + param_1 * 0x1e));
    strcat(acStack_84,aEnterMasterPassword);
    iVar1 = text_entry_dialog(acStack_84,acStack_30,10,0x3c,0,0,0,0,6);
    if (iVar1 == 0x1b) {
      return -1;
    }
    password_scramble(unaff_EBX,param_1);
    iVar1 = strcmp(&unk_ddd1d,acStack_30);
    if (iVar1 != 0) {
      getmouse(local_1c,auStack_20,auStack_24);
      message_dialog(0xffffffff,0xffffffff,&off_c7965,1,0,0,auStack_20,auStack_24,0xffffffff);
      iStack_14 = -1;
    }
    password_scramble(unaff_EBX,param_1);
    iVar2 = iVar2 + 1;
    if (iStack_14 == 0) break;
    if (2 < iVar2) {
      return iStack_14;
    }
  }
  return 0;
}


// ================================================================================================
// password_scramble @ 0x3a597 [__watcall]
// ================================================================================================

void __watcall password_scramble(int param_1,int unaff_EDX)

{
  size_t sVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  
  __CHK(0x1c);
  sVar1 = strlen(aNHLHockey);
  unaff_EDX = unaff_EDX % (int)sVar1;
  iVar3 = 0;
  iVar4 = 0;
  do {
    bVar2 = *(byte *)(iVar4 + param_1) ^ aNHLHockey[unaff_EDX];
    *(byte *)(iVar4 + param_1) = bVar2;
    *(byte *)(iVar4 + param_1) = bVar2 ^ aVerifyMasterControllerPa[(sVar1 - iVar3) + 0x26];
    unaff_EDX = unaff_EDX + 1;
    iVar3 = iVar3 + 1;
    if ((int)sVar1 <= unaff_EDX) {
      unaff_EDX = 0;
    }
    if ((int)sVar1 <= iVar3) {
      iVar3 = 0;
    }
    iVar4 = iVar4 + 1;
  } while (iVar4 < 10);
  return;
}


// ================================================================================================
// merge_delta_bytes @ 0x3a5fc [__watcall]
// ================================================================================================

void __watcall merge_delta_bytes(int param_1,int unaff_EDX,int unaff_EBX,int unaff_ECX,int param_5)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  __CHK(0xc);
  *(char *)(unaff_EBX + 0x28) =
       *(char *)(unaff_EBX + 0x28) + (*(char *)(unaff_EDX + 0x28) - *(char *)(param_1 + 0x28));
  *(char *)(unaff_EBX + 0x29) =
       *(char *)(unaff_EBX + 0x29) + (*(char *)(unaff_EDX + 0x29) - *(char *)(param_1 + 0x29));
  *(char *)(unaff_EBX + 0x2a) =
       *(char *)(unaff_EBX + 0x2a) + (*(char *)(unaff_EDX + 0x2a) - *(char *)(param_1 + 0x2a));
  *(char *)(unaff_EBX + 0x2b) =
       *(char *)(unaff_EBX + 0x2b) + (*(char *)(unaff_EDX + 0x2b) - *(char *)(param_1 + 0x2b));
  *(short *)(unaff_EBX + 0x2c) =
       *(short *)(unaff_EBX + 0x2c) + (*(short *)(unaff_EDX + 0x2c) - *(short *)(param_1 + 0x2c));
  *(short *)(unaff_EBX + 0x2e) =
       *(short *)(unaff_EBX + 0x2e) + (*(short *)(unaff_EDX + 0x2e) - *(short *)(param_1 + 0x2e));
  *(short *)(unaff_EBX + 0x30) =
       *(short *)(unaff_EBX + 0x30) + (*(short *)(unaff_EDX + 0x30) - *(short *)(param_1 + 0x30));
  *(short *)(unaff_EBX + 0x32) =
       *(short *)(unaff_EBX + 0x32) + (*(short *)(unaff_EDX + 0x32) - *(short *)(param_1 + 0x32));
  *(short *)(unaff_EBX + 0x34) =
       *(short *)(unaff_EBX + 0x34) + (*(short *)(unaff_EDX + 0x34) - *(short *)(param_1 + 0x34));
  *(short *)(unaff_EBX + 0x36) =
       *(short *)(unaff_EBX + 0x36) + (*(short *)(unaff_EDX + 0x36) - *(short *)(param_1 + 0x36));
  *(short *)(unaff_EBX + 0x38) =
       *(short *)(unaff_EBX + 0x38) + (*(short *)(unaff_EDX + 0x38) - *(short *)(param_1 + 0x38));
  *(char *)(unaff_EBX + 0x3a) =
       *(char *)(unaff_EBX + 0x3a) + (*(char *)(unaff_EDX + 0x3a) - *(char *)(param_1 + 0x3a));
  *(char *)(unaff_EBX + 0x3b) =
       *(char *)(unaff_EBX + 0x3b) + (*(char *)(unaff_EDX + 0x3b) - *(char *)(param_1 + 0x3b));
  *(char *)(unaff_EBX + 0x3c) =
       *(char *)(unaff_EBX + 0x3c) + (*(char *)(unaff_EDX + 0x3c) - *(char *)(param_1 + 0x3c));
  *(char *)(unaff_EBX + 0x3d) =
       *(char *)(unaff_EBX + 0x3d) + (*(char *)(unaff_EDX + 0x3d) - *(char *)(param_1 + 0x3d));
  *(short *)(unaff_EBX + 0x3e) =
       *(short *)(unaff_EBX + 0x3e) + (*(short *)(unaff_EDX + 0x3e) - *(short *)(param_1 + 0x3e));
  *(short *)(unaff_EBX + 0x40) =
       *(short *)(unaff_EBX + 0x40) + (*(short *)(unaff_EDX + 0x40) - *(short *)(param_1 + 0x40));
  *(short *)(unaff_EBX + 0x42) =
       *(short *)(unaff_EBX + 0x42) + (*(short *)(unaff_EDX + 0x42) - *(short *)(param_1 + 0x42));
  *(short *)(unaff_EBX + 0x44) =
       *(short *)(unaff_EBX + 0x44) + (*(short *)(unaff_EDX + 0x44) - *(short *)(param_1 + 0x44));
  *(short *)(unaff_EBX + 0x46) =
       *(short *)(unaff_EBX + 0x46) + (*(short *)(unaff_EDX + 0x46) - *(short *)(param_1 + 0x46));
  *(short *)(unaff_EBX + 0x48) =
       *(short *)(unaff_EBX + 0x48) + (*(short *)(unaff_EDX + 0x48) - *(short *)(param_1 + 0x48));
  *(short *)(unaff_EBX + 0x4a) =
       *(short *)(unaff_EBX + 0x4a) + (*(short *)(unaff_EDX + 0x4a) - *(short *)(param_1 + 0x4a));
  if (unaff_ECX == param_5) {
    puVar2 = (undefined4 *)(unaff_EDX + 0xbc);
    puVar3 = (undefined4 *)(unaff_EBX + 0xbc);
    for (iVar1 = 0xc; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar3 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar3 = puVar3 + 1;
    }
  }
  return;
}


// ================================================================================================
// merge_delta_words @ 0x3a71c [__watcall]
// ================================================================================================

void __watcall
merge_delta_words(short *param_1,short *unaff_EDX,short *unaff_EBX,int unaff_ECX,int param_5)

{
  __CHK(0xc);
  *unaff_EBX = *unaff_EBX + (*unaff_EDX - *param_1);
  unaff_EBX[1] = unaff_EBX[1] + (unaff_EDX[1] - param_1[1]);
  unaff_EBX[2] = unaff_EBX[2] + (unaff_EDX[2] - param_1[2]);
  unaff_EBX[3] = unaff_EBX[3] + (unaff_EDX[3] - param_1[3]);
  unaff_EBX[4] = unaff_EBX[4] + (unaff_EDX[4] - param_1[4]);
  unaff_EBX[5] = unaff_EBX[5] + (unaff_EDX[5] - param_1[5]);
  unaff_EBX[6] = unaff_EBX[6] + (unaff_EDX[6] - param_1[6]);
  unaff_EBX[7] = unaff_EBX[7] + (unaff_EDX[7] - param_1[7]);
  unaff_EBX[8] = unaff_EBX[8] + (unaff_EDX[8] - param_1[8]);
  unaff_EBX[9] = unaff_EBX[9] + (unaff_EDX[9] - param_1[9]);
  unaff_EBX[10] = unaff_EBX[10] + (unaff_EDX[10] - param_1[10]);
  unaff_EBX[0xb] = unaff_EBX[0xb] + (unaff_EDX[0xb] - param_1[0xb]);
  unaff_EBX[0xc] = unaff_EBX[0xc] + (unaff_EDX[0xc] - param_1[0xc]);
  unaff_EBX[0xd] = unaff_EBX[0xd] + (unaff_EDX[0xd] - param_1[0xd]);
  unaff_EBX[0xe] = unaff_EBX[0xe] + (unaff_EDX[0xe] - param_1[0xe]);
  unaff_EBX[0xf] = unaff_EBX[0xf] + (unaff_EDX[0xf] - param_1[0xf]);
  unaff_EBX[0x10] = unaff_EBX[0x10] + (unaff_EDX[0x10] - param_1[0x10]);
  unaff_EBX[0x11] = unaff_EBX[0x11] + (unaff_EDX[0x11] - param_1[0x11]);
  if (unaff_ECX == param_5) {
    *(undefined *)(unaff_EBX + 0x12) = *(undefined *)(unaff_EDX + 0x12);
    *(undefined *)((int)unaff_EBX + 0x25) = *(undefined *)((int)unaff_EDX + 0x25);
    *(undefined *)(unaff_EBX + 0x13) = *(undefined *)(unaff_EDX + 0x13);
    *(undefined *)((int)unaff_EBX + 0x27) = *(undefined *)((int)unaff_EDX + 0x27);
  }
  return;
}


// ================================================================================================
// merge_delta_words_b @ 0x3a826 [__watcall]
// ================================================================================================

void __watcall
merge_delta_words_b(short *param_1,short *unaff_EDX,ushort *unaff_EBX,int unaff_ECX,int param_5)

{
  ushort uVar1;
  
  __CHK(0xc);
  *unaff_EBX = *unaff_EBX + (*unaff_EDX - *param_1);
  unaff_EBX[1] = unaff_EBX[1] + (unaff_EDX[1] - param_1[1]);
  unaff_EBX[2] = unaff_EBX[2] + (unaff_EDX[2] - param_1[2]);
  unaff_EBX[3] = unaff_EBX[3] + (unaff_EDX[3] - param_1[3]);
  unaff_EBX[4] = unaff_EBX[4] + (unaff_EDX[4] - param_1[4]);
  unaff_EBX[5] = unaff_EBX[5] + (unaff_EDX[5] - param_1[5]);
  unaff_EBX[6] = unaff_EBX[6] + (unaff_EDX[6] - param_1[6]);
  unaff_EBX[7] = unaff_EBX[7] + (unaff_EDX[7] - param_1[7]);
  unaff_EBX[9] = unaff_EBX[9] + (unaff_EDX[9] - param_1[9]);
  unaff_EBX[10] = unaff_EBX[10] + (unaff_EDX[10] - param_1[10]);
  unaff_EBX[0xb] = unaff_EBX[0xb] + (unaff_EDX[0xb] - param_1[0xb]);
  unaff_EBX[0xc] = unaff_EBX[0xc] + (unaff_EDX[0xc] - param_1[0xc]);
  unaff_EBX[0xd] = unaff_EBX[0xd] + (unaff_EDX[0xd] - param_1[0xd]);
  unaff_EBX[0xe] = unaff_EBX[0xe] + (unaff_EDX[0xe] - param_1[0xe]);
  unaff_EBX[0xf] = unaff_EBX[0xf] + (unaff_EDX[0xf] - param_1[0xf]);
  unaff_EBX[0x10] = unaff_EBX[0x10] + (unaff_EDX[0x10] - param_1[0x10]);
  unaff_EBX[0x11] = unaff_EBX[0x11] + (unaff_EDX[0x11] - param_1[0x11]);
  unaff_EBX[0x12] = unaff_EBX[0x12] + (unaff_EDX[0x12] - param_1[0x12]);
  unaff_EBX[0x14] = unaff_EBX[0x14] + (unaff_EDX[0x14] - param_1[0x14]);
  unaff_EBX[0x15] = unaff_EBX[0x15] + (unaff_EDX[0x15] - param_1[0x15]);
  if (*unaff_EBX == 0) {
    unaff_EBX[8] = 0;
  }
  else {
    unaff_EBX[8] = (ushort)(((uint)unaff_EBX[7] * 100) / (uint)*unaff_EBX);
  }
  uVar1 = unaff_EBX[0xb];
  if (uVar1 != 0) {
    uVar1 = (ushort)(((uint)unaff_EBX[0x12] * 100) / (uint)unaff_EBX[0xb]);
  }
  unaff_EBX[0x13] = uVar1;
  if (unaff_ECX == param_5) {
    *(undefined *)(unaff_EBX + 0x16) = *(undefined *)(unaff_EDX + 0x16);
    *(undefined *)((int)unaff_EBX + 0x2d) = *(undefined *)((int)unaff_EDX + 0x2d);
    *(undefined *)(unaff_EBX + 0x17) = *(undefined *)(unaff_EDX + 0x17);
    *(undefined *)((int)unaff_EBX + 0x2f) = *(undefined *)((int)unaff_EDX + 0x2f);
  }
  return;
}


// ================================================================================================
// merge_team_databases @ 0x3a9aa [__watcall]
// ================================================================================================

undefined4 __watcall
merge_team_databases
          (undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 *unaff_ECX,
          undefined4 *param_5,undefined4 *param_6)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 extraout_EDX;
  int iVar3;
  int iVar4;
  undefined auStack_a74 [76];
  int aiStack_a28 [25];
  int aiStack_9c4 [142];
  undefined auStack_78c [744];
  undefined auStack_4a4 [744];
  undefined auStack_1bc [56];
  undefined auStack_184 [56];
  undefined auStack_14c [56];
  undefined auStack_114 [44];
  undefined4 local_e8;
  undefined auStack_e0 [48];
  undefined auStack_b0 [48];
  undefined auStack_80 [48];
  undefined auStack_50 [32];
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 *puVar5;
  
  __CHK(0xa7c);
  local_18 = 0xffffffff;
  local_1c = 0xffffffff;
  local_20 = 0xffffffff;
  local_24 = 0xffffffff;
  local_28 = 0xffffffff;
  local_2c = 0xffffffff;
  local_30 = 0xffffffff;
  make_path(auStack_50,param_1,off_c80e7,&aDB);
  iVar1 = file_open_read(auStack_50,&local_20);
  puVar2 = &aDB;
  puVar5 = unaff_ECX;
  if (iVar1 == 0) {
    make_path(auStack_50,unaff_EDX,off_c80e7,unaff_ECX);
    iVar1 = file_open_read(auStack_50,&local_18);
    puVar2 = unaff_ECX;
  }
  if (iVar1 == 0) {
    make_path(auStack_50,unaff_EBX,off_c80e7,param_5);
    iVar1 = file_open_rw(auStack_50,&local_1c);
    puVar2 = param_5;
  }
  if (iVar1 == 0) {
    puVar2 = &aDB;
    make_path(auStack_50,param_1,off_c80d7,&aDB);
    iVar1 = file_open_read(auStack_50,&local_24);
  }
  if (iVar1 == 0) {
    puVar2 = &aDB;
    make_path(auStack_50,param_1,off_c80eb,&aDB);
    iVar1 = file_open_read(auStack_50,&local_30);
  }
  if (iVar1 == 0) {
    make_path(auStack_50,unaff_EDX,off_c80eb,puVar5);
    iVar1 = file_open_read(auStack_50,&local_28);
    puVar2 = puVar5;
  }
  if (iVar1 == 0) {
    make_path(auStack_50,unaff_EBX,off_c80eb,param_5);
    iVar1 = file_open_rw(auStack_50,&local_2c);
    puVar2 = param_5;
  }
  iVar3 = 0;
  do {
    if (iVar1 == 0) {
      iVar1 = db_read_record(local_20,auStack_78c,iVar3,puVar2);
    }
    if (iVar1 == 0) {
      iVar1 = db_read_record(local_18,auStack_a74,iVar3,puVar2);
    }
    if (iVar1 == 0) {
      iVar1 = db_read_record(local_1c,auStack_4a4,iVar3,puVar2);
    }
    if (iVar1 == 0) {
      merge_delta_bytes(auStack_78c,auStack_a74,auStack_4a4,param_6,iVar3);
      iVar1 = db_write_team_record(local_1c,auStack_4a4,iVar3);
      puVar2 = param_6;
    }
    if (iVar1 == 0) {
      iVar4 = 0;
      while ((iVar4 < 0x19 && (iVar1 == 0))) {
        if (aiStack_a28[iVar4] != -1) {
          iVar1 = file_read_b(local_24,auStack_114,aiStack_a28[iVar4]);
          if (iVar1 == 0) {
            iVar1 = file_read_c(local_30,auStack_e0,local_e8);
          }
          if (iVar1 == 0) {
            iVar1 = file_read_c(local_28,auStack_b0,local_e8);
          }
          if (iVar1 == 0) {
            iVar1 = file_read_c(local_2c,auStack_80,local_e8);
          }
          if (iVar1 == 0) {
            merge_delta_words(auStack_e0,auStack_b0,auStack_80,param_6,iVar3);
            iVar1 = file_write_c(local_2c,auStack_80,local_e8);
            puVar2 = param_6;
          }
        }
        iVar4 = iVar4 + 1;
      }
      iVar4 = 0;
      while ((iVar4 < 3 && (iVar1 == 0))) {
        if (aiStack_9c4[iVar4] != -1) {
          iVar1 = file_read_b(local_24,auStack_114,aiStack_9c4[iVar4]);
          if (iVar1 == 0) {
            iVar1 = file_read_d(local_30,auStack_14c,local_e8);
          }
          if (iVar1 == 0) {
            iVar1 = file_read_d(local_28,auStack_1bc,local_e8);
          }
          if (iVar1 == 0) {
            iVar1 = file_read_d(local_2c,auStack_184,local_e8);
          }
          if (iVar1 == 0) {
            merge_delta_words_b(auStack_14c,auStack_1bc,auStack_184,param_6,iVar3);
            iVar1 = file_write_d(local_2c,auStack_184,local_e8);
            puVar2 = param_6;
          }
        }
        iVar4 = iVar4 + 1;
      }
    }
    iVar3 = iVar3 + 1;
  } while (iVar3 < 0x1a);
  file_close(&local_2c);
  file_close(&local_28);
  file_close(&local_30);
  file_close(&local_24);
  file_close(&local_1c);
  file_close(&local_18);
  file_close(&local_20);
  return extraout_EDX;
}


// ================================================================================================
// merge_schedule @ 0x3ae1e [__watcall]
// ================================================================================================

undefined4 __watcall
merge_schedule(undefined4 param_1,undefined4 unaff_EDX,undefined4 param_3,undefined4 param_4,
              uint param_5,int *param_6)

{
  int iVar1;
  int iVar2;
  undefined4 extraout_EDX;
  undefined auStackY_44 [32];
  undefined auStackY_24 [2];
  byte bStackY_22;
  byte bStackY_21;
  undefined4 local_1c;
  undefined2 local_18;
  undefined2 uStackY_16;
  short asStackY_14 [2];
  short asStackY_10 [2];
  
  __CHK(0x48);
  local_18 = 0xffff;
  uStackY_16 = 0xffff;
  local_1c = 0xffffffff;
  make_path(auStackY_44,param_1);
  iVar1 = file_open_read(auStackY_44,&local_1c);
  if (iVar1 == 0) {
    make_path(auStackY_44,unaff_EDX);
    iVar1 = file_open_rw(auStackY_44,&local_18);
  }
  if (iVar1 == 0) {
    iVar1 = file_read(local_1c,asStackY_14,0);
  }
  if (iVar1 == 0) {
    iVar1 = file_read(CONCAT22(uStackY_16,local_18),asStackY_10,0);
  }
  if (iVar1 == 0) {
    *param_6 = (int)asStackY_10[0];
    if (asStackY_10[0] < asStackY_14[0]) {
      *param_6 = (int)asStackY_14[0];
      iVar1 = file_write(CONCAT22(uStackY_16,local_18),asStackY_14,0);
    }
  }
  if (0x443 < asStackY_14[0]) {
    asStackY_14[0] = 0x4ad;
  }
  iVar2 = 0;
  while ((iVar2 < asStackY_14[0] && (iVar1 == 0))) {
    iVar1 = db_read_record2(local_1c,auStackY_24,iVar2);
    if ((iVar1 == 0) && ((param_5 == bStackY_22 || (param_5 == bStackY_21)))) {
      iVar1 = schedule_write_record(CONCAT22(uStackY_16,local_18),auStackY_24,iVar2);
    }
    iVar2 = iVar2 + 1;
  }
  file_close(&local_18);
  file_close(&local_1c);
  return extraout_EDX;
}


// ================================================================================================
// merge_conflict_dialog @ 0x3af70 [__watcall]
// ================================================================================================

int __watcall
merge_conflict_dialog
          (int param_1,int param_2,undefined4 unaff_EBX,undefined4 unaff_ECX,undefined4 param_5,
          undefined4 *param_6,uint *param_7)

{
  int iVar1;
  int iVar2;
  undefined local_1c [4];
  undefined local_18 [4];
  undefined local_14 [4];
  
  __CHK(0x34);
  iVar2 = 0;
  iVar1 = param_2 * 0x1e + param_1;
  if ((*(char *)(iVar1 + 0x18) == '\x01') || (*(char *)(iVar1 + 0x16) == '\x01')) {
    *param_6 = unaff_ECX;
    *param_7 = *(uint *)(param_1 + 0x1a + param_2 * 0x1e);
  }
  else {
    *param_6 = param_5;
    iVar2 = player_league_dialog(unaff_EBX,iVar1);
    league_player_id_check(param_5,param_7);
    if ((iVar2 != 4) && (*param_7 < *(uint *)(iVar1 + 0x1a))) {
      dword_c7c25 = unaff_EBX;
      getmouse(local_14,local_18,local_1c);
      message_dialog(0xffffffff,0xffffffff,&off_c7c1d,3,0,0,local_18,local_1c,0xffffffff);
      iVar2 = -1;
    }
  }
  return iVar2;
}


// ================================================================================================
// league_merge_warning @ 0x3b039 [__watcall]
// ================================================================================================

void __watcall league_merge_warning(void)

{
  int iVar1;
  size_t sVar2;
  undefined4 *puVar3;
  uint uVar4;
  uint extraout_EDX;
  char *pcVar5;
  int iVar6;
  undefined2 in_DS;
  undefined8 uVar7;
  undefined auStack_5c [32];
  char local_3c [16];
  undefined4 uStack_2c;
  undefined auStack_28 [4];
  undefined auStack_24 [4];
  undefined auStack_20 [4];
  byte abStack_1c [4];
  
  __CHK(0x74);
  uStack_2c = 0xffffffff;
  iVar6 = 0;
  set_dialog_colors(0xf9,0xfa,0xf8,0xfa,0);
  iVar1 = return_zero_41337(&league_dir,2);
  if (iVar1 == 0) {
    iVar1 = load_league_info(&league_dir,&unk_dd7b4,&unk_ddd1d,&dword_dd7a8,&dword_ddac0,
                             &dword_dd7b0,&dword_dd7ac,&byte_ddd10);
    strcpy(local_3c,&league_dir);
    puVar3 = (undefined4 *)CONCAT22(0xd,in_DS);
    pcVar5 = &byte_c8164;
    sVar2 = strcspn(local_3c,(char *)CONCAT22(0xc,in_DS));
    uVar4 = CONCAT22(0xc,in_DS) & 0xffffff00;
    local_3c[sVar2] = '\0';
    if ((iVar1 == 0) && (dword_dd7ac != 0)) {
      dword_c80a1 = local_3c;
      getmouse(auStack_20,auStack_24,auStack_28);
      puVar3 = (undefined4 *)0x3;
      message_dialog(0xffffffff,0xffffffff,&off_c809d,3,0,0,auStack_24,auStack_28,0xffffffff);
      iVar6 = -1;
      uVar4 = extraout_EDX;
      pcVar5 = (char *)&off_c809d;
    }
    uVar7 = CONCAT44(uVar4,iVar1);
    if (iVar6 == 0) {
      if (iVar1 == 0) {
        puVar3 = &aDB;
        pcVar5 = aPINFO;
        make_path(auStack_5c,&league_dir,aPINFO,&aDB);
        uVar7 = file_open_rw(auStack_5c,&uStack_2c);
      }
      if ((int)uVar7 == 0) {
        puVar3 = (undefined4 *)0x2;
        pcVar5 = (char *)0x13;
        uVar7 = file_read(uStack_2c,abStack_1c,0x13,2);
      }
      iVar1 = (int)uVar7;
      file_close(&uStack_2c,(int)((ulonglong)uVar7 >> 0x20),pcVar5,puVar3);
      if (iVar1 == 0) {
        if ((abStack_1c[0] & 4) == 0) {
          dword_c7da1 = local_3c;
          dword_c7da5 = aHasNotBeenMerged;
          getmouse(auStack_20,auStack_24,auStack_28);
          message_dialog(0xffffffff,0xffffffff,&off_c7d9d,3,0,0,auStack_24,auStack_28,0xffffffff);
        }
        else {
          iVar1 = league_player_sync(&league_dir,&unk_dd7b4,0xffffffff);
        }
      }
      if (iVar1 != 0) {
        getmouse(auStack_20,auStack_24,auStack_28);
        message_dialog(0xffffffff,0xffffffff,&off_c8ab9,2,0,0,auStack_24,auStack_28,0xffffffff);
      }
    }
  }
  set_dialog_colors(0x2a,0x3f,0x17,0x3f,0);
  return;
}


// ================================================================================================
// league_merge_check @ 0x3b25a [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 __watcall league_merge_check(undefined4 param_1,undefined4 unaff_EDX)

{
  int iVar1;
  size_t sVar2;
  undefined4 uVar3;
  undefined **ppuVar4;
  undefined2 in_DS;
  undefined local_74 [32];
  char local_54 [16];
  undefined4 local_44;
  undefined1 *local_40;
  char local_3c [4];
  undefined4 local_38;
  undefined4 local_34;
  undefined4 uStack_30;
  undefined auStack_2c [4];
  undefined auStack_28 [4];
  undefined auStack_24 [4];
  int local_20;
  undefined2 uStack_1c;
  undefined2 uStack_1a;
  short asStack_18 [2];
  
  __CHK(0x8c);
  uStack_30 = 0xffffffff;
  uStack_1c = 0xffff;
  uStack_1a = 0xffff;
  local_38 = 0xffffffff;
  set_dialog_colors(0xf9,0xfa,0xf8,0xfa,0);
  iVar1 = return_zero_41337(&league_dir,2);
  ram0x000de265 = ram0x000de265 & 0xffffff;
  if (iVar1 == 0) {
    iVar1 = load_league_info(&league_dir,&unk_dd7b4,&unk_ddd1d,&dword_dd7a8,&dword_ddac0,
                             &dword_dd7b0,&dword_dd7ac,&byte_ddd10);
    make_path(local_74,&league_dir,aPLAYER_c80f9,&aID_c8166);
    dword_ddd70 = file_exists_rd(local_74);
    if (iVar1 == 0) {
      strcpy(local_54,&league_dir);
      sVar2 = strcspn(local_54,(char *)CONCAT22(0xc,in_DS));
      local_54[sVar2] = '\0';
      if (dword_dd7ac == 0) {
        if ((&unk_dd7ca)[dword_dd7a8 * 0x1e] == '\x02') {
          dword_c8a2b = local_54;
          getmouse(auStack_24,auStack_28,auStack_2c);
          uVar3 = 3;
          ppuVar4 = &off_c8a27;
        }
        else if (dword_ddd70 == 0) {
          if ((dword_dd7b0 & 4) == 0) {
            make_path(local_74,&league_dir);
            iVar1 = file_open_rw(local_74,&uStack_30);
            if (iVar1 == 0) {
              sprintf(local_3c,a02d_c1904,dword_dd7a8);
              strcpy((char *)&aXx_c8158,local_3c);
              iVar1 = merge_conflict_dialog
                                (&unk_dd7b4,dword_dd7a8,&league_dir,&league_dir,&byte_c816a,
                                 &local_34,&local_44);
            }
            if (iVar1 == 0) {
              message_dialog(0xffffffff);
            }
            local_20 = 0;
            while ((local_20 < 0x1a && (iVar1 == 0))) {
              if (((&unk_dd7cb)[local_20 * 0x1e] == '\x01') &&
                 (((&unk_dd7ca)[local_20 * 0x1e] & 4) == 0)) {
                sprintf(local_3c,a02d_c1904,local_20);
                strcpy((char *)&aXx,local_3c);
                iVar1 = merge_conflict_dialog
                                  (&unk_dd7b4,local_20,&league_dir,&league_dir,&byte_c816a,&local_40
                                   ,&local_44);
                if (iVar1 == 0) {
                  if (dword_c71e4 == 0) {
                    message_dialog(0xffffffff,0xffffffff,&off_c7f77,1,0,0,0,0,0);
                  }
                  make_path(local_74,local_40,aPINFO,&aDB);
                  iVar1 = file_open_rw(local_74,&uStack_1c);
                }
                if (((iVar1 == 0) && (local_20 != dword_dd7a8)) &&
                   (iVar1 = merge_team_databases
                                      (&league_dir,local_40,local_34,&aXx,&aXx_c8158,local_20),
                   iVar1 == 0)) {
                  iVar1 = merge_schedule(local_40,&league_dir,&aXx,&aXx_c8158,local_20,asStack_18);
                }
                if (iVar1 == 0) {
                  iVar1 = local_20 * 0x1e;
                  *(undefined4 *)(&unk_dd7ce + iVar1) = local_44;
                  (&unk_dd7ca)[iVar1] = (&unk_dd7ca)[iVar1] | 4;
                  iVar1 = league_write_team_entry(uStack_30,&unk_dd7b4 + iVar1);
                }
                if (iVar1 == 0) {
                  iVar1 = league_write_team_entry
                                    (CONCAT22(uStack_1a,uStack_1c),&unk_dd7b4 + local_20 * 0x1e);
                }
                if ((iVar1 == 0) && (local_40 != &league_dir)) {
                  dword_dd7b0 = 4;
                  iVar1 = file_write(CONCAT22(uStack_1a,uStack_1c),&dword_dd7b0,0x13,2);
                }
                file_close(&uStack_1c);
                if (iVar1 == 0) {
                  dword_dd7b0 = 8;
                  iVar1 = file_write(uStack_30,&dword_dd7b0,0x13,2);
                }
              }
              local_20 = local_20 + 1;
            }
            if (iVar1 == 0) {
              iVar1 = copy_file(off_c80e7,&aXx_c8158,&aDB,local_34,&league_dir);
            }
            if (iVar1 == 0) {
              iVar1 = copy_file(off_c80eb,&aXx_c8158,&aDB,local_34,&league_dir);
            }
            if (iVar1 == 0) {
              iVar1 = copy_file(off_c80ef,&aXx_c8158,&aDB,local_34,&league_dir);
            }
            restore_dialog_background();
            if (iVar1 == 0) {
              make_path(local_74,&league_dir,off_c80ef,&aDB);
              iVar1 = file_open_read(local_74,&local_38);
            }
            if (iVar1 == 0) {
              iVar1 = file_read(local_38,asStack_18,0,2);
            }
            file_close(&local_38);
            if (iVar1 == 0) {
              message_dialog(0xffffffff,0xffffffff,&off_c7f8e,1,0,0,0,0,0);
              iVar1 = league_play_day(&league_dir,&aDB,(int)asStack_18[0],&unk_dd7b4,0xffffffff,7);
            }
            if (iVar1 == 0) {
              dword_dd7b0 = 4;
              iVar1 = file_write(uStack_30,&dword_dd7b0,0x13,2);
            }
            restore_dialog_background();
            file_close(&uStack_30);
            getmouse(&local_20,auStack_28,auStack_2c);
            if (iVar1 == 4) {
              if (dword_dd7b0 != 8) goto LAB_0003b254;
              uVar3 = 3;
              ppuVar4 = (undefined **)&off_c8a85;
            }
            else {
              if (iVar1 == 0) goto LAB_0003b254;
              uVar3 = 1;
              ppuVar4 = &off_c8ae0;
            }
          }
          else {
            dword_c7da1 = local_54;
            dword_c7da5 = aIsAlreadyMerged;
            getmouse(&local_20,auStack_28,auStack_2c);
            uVar3 = 3;
            ppuVar4 = &off_c7d9d;
          }
        }
        else {
          dword_c89e6 = local_54;
          getmouse(auStack_24,auStack_28,auStack_2c);
          uVar3 = 3;
          ppuVar4 = &off_c89de;
        }
      }
      else {
        dword_c80a1 = local_54;
        getmouse(auStack_24,auStack_28,auStack_2c);
        uVar3 = 3;
        ppuVar4 = &off_c809d;
      }
      message_dialog(0xffffffff,0xffffffff,ppuVar4,uVar3,0,0,auStack_28,auStack_2c,0xffffffff);
    }
  }
LAB_0003b254:
  set_dialog_colors(0x2a,0x3f,0x17,0x3f,0);
  return CONCAT44(unaff_EDX,(int)ram0x000de265 >> 0x18);
}


// ================================================================================================
// league_merge_and_update @ 0x3b8b0 [__watcall]
// ================================================================================================

undefined8 __watcall league_merge_and_update(undefined4 param_1,undefined4 unaff_EDX)

{
  int iVar1;
  undefined uStack_14;
  undefined uStack_13;
  undefined uStack_12;
  
  __CHK(0x24);
  iVar1 = league_merge_check();
  if (dword_dd7ac == 0) {
    if (((&unk_dd7ca)[dword_dd7a8 * 0x1e] != '\x02') && (dword_ddd70 == 0)) {
      if (iVar1 != 0) {
        clearclip(0);
        uStack_14 = 0x17;
        uStack_13 = 0x17;
        uStack_12 = 0x17;
        setpalette(0xf8,1,&uStack_14);
        uStack_14 = 0x2a;
        uStack_13 = 0x2a;
        uStack_12 = 0x2a;
        setpalette(0xf9,1,&uStack_14);
        uStack_14 = 0x3f;
        uStack_13 = 0x3f;
        uStack_12 = 0x3f;
        setpalette(0xfa,1,&uStack_14);
      }
      league_merge_warning();
      if (iVar1 != 0) {
        clearclip(0);
        uStack_14 = 0;
        uStack_13 = 0;
        uStack_12 = 0;
        setpalette(0xf8,1,&uStack_14);
        setpalette(0xf9,1,&uStack_14);
        setpalette(0xfa,1,&uStack_14);
      }
    }
  }
  return CONCAT44(unaff_EDX,iVar1);
}


// ================================================================================================
// league_rebuild @ 0x3b9ca [__watcall]
// ================================================================================================

void __watcall league_rebuild(void)

{
  int iVar1;
  int unaff_ESI;
  char acStack_48 [32];
  undefined4 uStack_28;
  undefined auStack_24 [4];
  undefined auStack_20 [4];
  int iStack_1c;
  undefined auStack_18 [4];
  
  __CHK(0x60);
  uStack_28 = 0xffffffff;
  set_dialog_colors(0xf9,0xfa,0xf8,0xfa,0);
  iVar1 = return_zero_41337(&league_dir,2);
  if (iVar1 == 0) {
    iVar1 = load_league_info(&league_dir,&unk_dd7b4,&unk_ddd1d,&dword_dd7a8,&dword_ddac0,
                             &dword_dd7b0,&dword_dd7ac,&byte_ddd10);
    unaff_ESI = 0;
    iStack_1c = 0;
    while ((iStack_1c < 0x1a && (unaff_ESI == 0))) {
      if ((&unk_dd7cb)[iStack_1c * 0x1e] == '\x01') {
        unaff_ESI = password_prompt(iStack_1c,&unk_dd7b4);
      }
      iStack_1c = iStack_1c + 1;
    }
    if (unaff_ESI == 0) {
      unaff_ESI = master_password_prompt(dword_dd7a8,&unk_dd7b4,&unk_ddd1d);
    }
  }
  if ((iVar1 == 0) && (unaff_ESI == 0)) {
    make_path(acStack_48,&league_dir,aPINFO,&aDB);
    iVar1 = file_open_rw(acStack_48,&uStack_28);
    if (iVar1 == 0) {
      iVar1 = file_read(uStack_28,auStack_18,0x13,2);
    }
    file_close(&uStack_28);
    if (iVar1 == 0) {
      strcpy(acStack_48,&league_dir);
      delete_matching_files(acStack_48,&aGAME_c190e,&aSAV_c190a);
      iVar1 = league_player_sync(&league_dir,&unk_dd7b4,0xffffffff);
    }
    if (iVar1 != 0) {
      getmouse(&iStack_1c,auStack_20,auStack_24);
      message_dialog(0xffffffff,0xffffffff,&off_c8ab9,2,0,0,auStack_20,auStack_24,0xffffffff);
    }
  }
  set_dialog_colors(0x2a,0x3f,0x17,0x3f,0);
  return;
}


// ================================================================================================
// pinfo_find_player @ 0x3bb87 [__watcall]
// ================================================================================================

int __watcall
pinfo_find_player(char *param_1,undefined4 param_2,undefined4 unaff_EBX,int unaff_ECX,int param_5,
                 int param_6,int param_7)

{
  int iVar1;
  size_t sVar2;
  undefined4 uVar3;
  undefined **ppuVar4;
  char *__s2;
  int iVar5;
  undefined2 in_DS;
  undefined auStack_118 [64];
  char acStack_d8 [32];
  char acStack_b8 [32];
  undefined auStack_98 [22];
  char cStack_82;
  char local_78 [16];
  char local_68 [16];
  char local_58 [12];
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  int local_40;
  undefined local_3c [4];
  undefined auStack_38 [4];
  int local_34;
  undefined4 local_30;
  int local_2c;
  int local_28;
  int iStack_18;
  undefined4 uStack_14;
  undefined auStack_10 [4];
  
  __CHK(0x130);
  local_44 = 0xffffffff;
  local_48 = 0xffffffff;
  local_30 = 0xffffffff;
  local_4c = 0xffffffff;
  __s2 = (char *)(unaff_ECX * 0x1e + param_5);
  iVar5 = 0;
  if (param_7 != 0) {
    local_2c = 0;
    do {
      iVar5 = 0;
      local_28 = 0;
      iStack_18 = 0;
      make_path(acStack_d8,&byte_c816a,aPINFO);
      iVar1 = file_open_rw(acStack_d8,&local_30);
      if (iVar1 == 0) {
        iVar5 = pinfo_read_record(local_30,auStack_98,unaff_ECX);
        if (iVar5 == 0) {
          make_path(acStack_d8,&byte_c816a,aPLAYER_c80f9);
          iVar5 = file_open_read(acStack_d8,&local_4c);
        }
        if (iVar5 == 0) {
          iVar5 = file_read(local_4c,local_58,1);
        }
        if (iVar5 == 0) {
          iVar5 = file_read(local_4c,local_68,0xc);
        }
        file_close(&local_4c);
        if (iVar5 == 0) {
          iStack_18 = strcmp(local_58,__s2);
          iVar1 = strcmp(local_68,param_1);
          iStack_18 = iStack_18 + iVar1;
          if (iStack_18 == 0) {
            local_2c = 1;
          }
        }
      }
      else {
        local_28 = -1;
      }
      if (iStack_18 != 0) {
        format_from_league(auStack_118,local_58,local_68);
        dword_c766f = auStack_118;
        getmouse(&local_40,auStack_38,local_3c);
        local_40 = message_dialog(0xffffffff,0xffffffff,&off_c766b,3,&unk_c7677,2,auStack_38,
                                  local_3c,0xffffffff);
        if (local_40 == 0) {
          local_2c = -1;
        }
        else {
          iVar5 = -1;
        }
      }
      if (iVar5 == 0) {
        if (((__s2[0x18] & 2U) == 0) || (local_28 == 0)) {
          cStack_82 = '\x01';
          iVar5 = 0;
          local_2c = 1;
        }
        else {
          iVar5 = player_league_dialog(param_1,__s2,1);
          if (0 < iVar5) {
            iVar5 = 0;
            getmouse(&local_34,auStack_38,local_3c);
            local_40 = message_dialog(0xffffffff,0xffffffff,&off_c7c59,2,&unk_c7c61,2,auStack_38,
                                      local_3c,0xffffffff);
            if (local_40 == 0) {
              cStack_82 = '\x01';
              local_2c = 1;
            }
            if (local_40 < 0) {
              iVar5 = -1;
            }
          }
        }
      }
      file_close(&local_30);
    } while ((local_2c == 0) && (iVar5 == 0));
  }
  if (iVar5 == 0) {
    if ((param_6 == 0) && ((__s2[0x16] != '\x01' || (cStack_82 != '\x01')))) {
      strcpy(local_78,param_1);
      sVar2 = strcspn(local_78,(char *)CONCAT22((short)((uint)param_1 >> 0x10),in_DS));
      local_78[sVar2] = '\0';
      dword_c79c0 = local_78;
      dword_c79c8 = __s2;
      getmouse(&local_34,auStack_38,local_3c);
      uVar3 = 3;
      ppuVar4 = &dword_c79c0;
    }
    else {
      show_league_message(unaff_ECX * 0x1e + param_5);
      for (local_34 = 0; local_34 < 7; local_34 = local_34 + 1) {
        strcpy(acStack_d8,&byte_c816a);
        strcpy(acStack_b8,(&off_c80d7)[local_34]);
        delete_matching_files(acStack_d8,acStack_b8,&unk_c1914);
      }
      strcpy(acStack_d8,&byte_c816a);
      strcpy(acStack_b8,aPINFO);
      delete_matching_files(acStack_d8,acStack_b8,&unk_c1914);
      strcpy(acStack_d8,&byte_c816a);
      strcpy(acStack_b8,aPLAYER_c80f9);
      delete_matching_files(acStack_d8,acStack_b8);
      local_34 = 0;
      while ((local_34 < 7 && (iVar5 == 0))) {
        iVar5 = copy_file((&off_c80d7)[local_34],param_2,unaff_EBX,param_1,&byte_c816a);
        if (iVar5 == 0) {
          iVar5 = copy_file((&off_c80d7)[local_34],&aDB,&aDB,param_1,&byte_c816a);
        }
        local_34 = local_34 + 1;
      }
      if (iVar5 == 0) {
        iVar5 = copy_file(aPINFO,&aDB,&aDB,param_1,&byte_c816a);
      }
      if (iVar5 == 0) {
        make_path(acStack_d8,param_1,&aGAME_c810c,&aSET_c8131);
        make_path(acStack_b8,&byte_c816a,&aGAME_c810c,&aSET_c8131);
        iVar5 = pinfo_copy_records(acStack_d8,acStack_b8);
      }
      *(int *)(__s2 + 0x1a) = *(int *)(__s2 + 0x1a) + 1;
      __s2[0x16] = '\x02';
      __s2[0x18] = __s2[0x18] | 2;
      if (iVar5 == 0) {
        make_path(acStack_d8,&byte_c816a,aPLAYER_c80f9,&aID_c8166);
        iVar5 = file_create(acStack_d8,&local_44);
      }
      if (iVar5 == 0) {
        auStack_10[0] = (undefined)unaff_ECX;
        iVar5 = file_write(local_44,auStack_10,0,1);
      }
      if (iVar5 == 0) {
        iVar5 = file_write(local_44,__s2,0xffffffff,0xb);
      }
      if (iVar5 == 0) {
        iVar5 = file_write(local_44,param_1,0xffffffff,0xd);
      }
      if (iVar5 == 0) {
        iVar5 = file_write(local_44,__s2 + 0x1a,0xffffffff,4);
      }
      file_close(&local_44);
      if (iVar5 == 0) {
        make_path(acStack_d8,&byte_c816a,aPINFO,&aDB);
        iVar5 = file_open_trunc(acStack_d8,&local_30);
      }
      if (iVar5 == 0) {
        uStack_14 = 0;
        iVar5 = file_write(local_30,&uStack_14,0x13,2);
      }
      if (iVar5 == 0) {
        iVar5 = league_write_team_entry(local_30,__s2,unaff_ECX);
      }
      file_close(&local_30);
      if (iVar5 == 0) {
        make_path(acStack_d8,param_1,aPINFO,&aDB);
        iVar5 = file_open_rw(acStack_d8,&local_48);
      }
      if (iVar5 == 0) {
        iVar5 = league_write_team_entry(local_48,__s2,unaff_ECX);
      }
      restore_dialog_background();
      if (iVar5 == 0) goto LAB_0003c2f6;
      __s2[0x16] = '\x01';
      __s2[0x18] = __s2[0x18] | 1;
      league_write_team_entry(local_48,__s2,unaff_ECX);
      getmouse(&local_34,auStack_38,local_3c);
      uVar3 = 2;
      ppuVar4 = &off_c8b37;
    }
    message_dialog(0xffffffff,0xffffffff,ppuVar4,uVar3,0,0,auStack_38,local_3c,0xffffffff);
  }
LAB_0003c2f6:
  file_close(&local_48);
  return iVar5;
}


// ================================================================================================
// league_copy_files @ 0x3c310 [__watcall]
// ================================================================================================

void __watcall league_copy_files(undefined4 param_1,undefined4 unaff_EDX)

{
  int iVar1;
  int iVar2;
  
  __CHK(0x20);
  iVar1 = 0;
  iVar2 = 0;
  while ((iVar2 < 7 && (iVar1 == 0))) {
    iVar1 = copy_file((&off_c80d7)[iVar2],&aDB,&aDB,param_1,unaff_EDX);
    if (iVar1 == 0) {
      iVar1 = copy_file((&off_c80d7)[iVar2],&aXx,&aXx,param_1,unaff_EDX);
    }
    iVar2 = iVar2 + 1;
  }
  if (iVar1 == 0) {
    iVar1 = copy_file(aPINFO,&aDB,&aDB,param_1,unaff_EDX);
  }
  if (iVar1 == 0) {
    copy_file(aPLAYER_c80f9,&aID_c8166,&aID_c8166,param_1,unaff_EDX);
  }
  return;
}


// ================================================================================================
// import_game_set @ 0x3c3af [__watcall]
// ================================================================================================

undefined8 __watcall import_game_set(undefined4 param_1,undefined4 unaff_EDX)

{
  int iVar1;
  int iVar2;
  __mode_t __mode;
  int unaff_EDI;
  undefined auStack_8c [44];
  char local_60 [32];
  char local_40 [16];
  undefined auStack_30 [4];
  undefined auStack_2c [4];
  int local_28;
  undefined4 local_24;
  undefined4 uStack_20;
  undefined auStack_1c [4];
  
  __CHK(0xa4);
  uStack_20 = 0xffffffff;
  local_24 = 0xffffffff;
  make_path(local_60,&byte_c816a,aPLAYER_c80f9,&aID_c8166);
  iVar1 = file_open_read(local_60,&uStack_20);
  if (iVar1 == 0) {
    iVar1 = file_read(uStack_20,&league_dir,0xc,0xd);
  }
  file_close(&uStack_20);
  if (iVar1 == 0) {
    if (iVar1 == 0) {
      iVar1 = load_league_info(&byte_c816a,&unk_dd7b4,&unk_ddd1d,&dword_dd7a8,&dword_ddac0,
                               &dword_dd7b0,&dword_dd7ac,&byte_ddd10);
    }
    strcpy(local_40,&league_dir);
    iVar2 = _dos_findfirst(local_40,0x10,auStack_8c);
    if (iVar2 == 0) {
      getmouse(&local_28,auStack_2c,auStack_30);
      set_dialog_colors(0xf9,0xfa,0xf8,0xfa,0);
      message_dialog(0xffffffff,0xffffffff,&off_c7d62,2,0,0,auStack_2c,auStack_30,0xffffffff);
    }
    else {
      unaff_EDI = master_password_prompt(dword_dd7a8,&unk_dd7b4,&unk_ddd1d);
      if (unaff_EDI == 0) {
        message_dialog(0xffffffff,0xffffffff,&off_c8b00,1,0,0,auStack_2c,auStack_30,0);
        iVar1 = mkdir(local_40,__mode);
        if (iVar1 == 0) {
          local_28 = 0;
          while ((local_28 < 7 && (iVar1 == 0))) {
            iVar1 = copy_file((&off_c80d7)[local_28],&aDB,&aDB,&byte_c816a,&league_dir);
            local_28 = local_28 + 1;
          }
        }
        if (iVar1 == 0) {
          iVar1 = copy_file(aPINFO,&aDB,&aDB,&byte_c816a,&league_dir);
        }
        if (iVar1 == 0) {
          copy_file(&aGAME_c191e,&aSET,&aSET,&byte_c816a,&league_dir);
        }
        restore_dialog_background();
        strcpy(local_60,&league_dir);
        delete_matching_files(local_60,&aGAME_c191e,&aSAV_c1923);
        make_path(local_60,&league_dir,aPINFO,&aDB);
        iVar1 = file_open_rw(local_60,&local_24);
        if (iVar1 == 0) {
          iVar1 = file_read(local_24,auStack_1c,0x13,2);
        }
        file_close(&local_24);
        if (iVar1 == 0) {
          iVar1 = league_player_sync(&league_dir,&unk_dd7b4,0xffffffff);
        }
        if (iVar1 != 0) {
          getmouse(&local_28,auStack_2c,auStack_30);
          message_dialog(0xffffffff,0xffffffff,&off_c8ab9,2,0,0,auStack_2c,auStack_30,0xffffffff);
          delete_directory(local_40);
        }
      }
    }
  }
  if (iVar1 != 0) {
    getmouse(&local_28,auStack_2c,auStack_30);
    set_dialog_colors(0xf9,0xfa,0xf8,0xfa,0);
    message_dialog(0xffffffff,0xffffffff,&off_c792b,1,0,0,auStack_2c,auStack_30,0xffffffff);
  }
  if (unaff_EDI != 0) {
    iVar1 = -1;
  }
  return CONCAT44(unaff_EDX,iVar1);
}


// ================================================================================================
// player_db_sync @ 0x3c6e2 [__watcall]
// ================================================================================================

undefined8 __watcall player_db_sync(undefined4 param_1,undefined4 unaff_EDX)

{
  int iVar1;
  size_t sVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  undefined2 extraout_var;
  undefined **ppuVar6;
  int iVar7;
  undefined2 in_DS;
  undefined auStack_d0 [44];
  undefined auStack_a4 [32];
  undefined auStack_84 [22];
  char cStack_6e;
  uint uStack_6a;
  char local_64 [16];
  undefined auStack_54 [12];
  undefined local_48 [4];
  int local_44;
  undefined local_40 [4];
  undefined4 local_3c;
  char acStack_38 [4];
  undefined local_34 [4];
  undefined4 local_30;
  undefined4 local_2c;
  undefined local_28 [4];
  int iStack_24;
  undefined uStack_20;
  undefined4 uStack_1f;
  
  __CHK(0xe8);
  local_3c = 0xffffffff;
  local_2c = 0xffffffff;
  local_30 = 0xffffffff;
  iVar7 = 0;
  set_dialog_colors(0xf9,0xfa,0xf8,0xfa,0);
  make_path(auStack_a4,&byte_c816a,aPLAYER_c80f9,&aID_c8166);
  iVar1 = file_open_read(auStack_a4,&local_3c);
  if (iVar1 == 0) {
    iVar1 = file_read(local_3c,(int)&uStack_1f + 3,0,1);
  }
  if (iVar1 == 0) {
    iVar1 = file_read(local_3c,auStack_54,1,0xb);
  }
  if (iVar1 == 0) {
    iVar1 = file_read(local_3c,&league_dir,0xc,0xd);
  }
  if (iVar1 == 0) {
    iVar1 = file_read(local_3c,local_34,0x19,4);
  }
  file_close(&local_3c);
  if (iVar1 == 0) {
    sprintf(acStack_38,a02d_c1927,uStack_1f >> 0x18);
    strcpy((char *)&aXx,acStack_38);
    make_path(auStack_a4,&byte_c816a,aPINFO,&aDB);
    iVar1 = file_open_rw(auStack_a4,&local_2c);
  }
  if (iVar1 == 0) {
    iVar1 = pinfo_read_record(local_2c,auStack_84,uStack_1f >> 0x18);
  }
  if (iVar1 == 0) {
    iVar1 = file_read(local_2c,&uStack_20,4,2);
  }
  file_close(&local_2c);
  if ((iVar1 == 0) && (CONCAT11((undefined)uStack_1f,uStack_20) != 0)) {
    strcpy(local_64,&league_dir);
    sVar2 = strcspn(local_64,(char *)CONCAT22(0xc,in_DS));
    local_64[sVar2] = '\0';
    set_dialog_colors(0xf9,0xfa,0xf8,0xfa,0);
    dword_c7ba7 = auStack_54;
    dword_c7baf = local_64;
    getmouse(&local_44,local_40,local_28);
    message_dialog(0xffffffff,0xffffffff,&dword_c7ba7,5,0,0,local_40,local_28,0xffffffff);
    goto LAB_0003cef9;
  }
  if (iVar1 != 0) goto LAB_0003cef9;
  strcpy(local_64,&league_dir);
  iVar3 = _dos_findfirst(local_64,0x10,auStack_d0);
  iStack_24 = iVar3;
  sVar2 = strcspn(local_64,(char *)CONCAT22(extraout_var,in_DS));
  local_64[sVar2] = '\0';
  if (iVar3 == 0) {
    do {
      iVar3 = 0;
      iVar1 = load_league_info(&league_dir,&unk_dd7b4,&unk_ddd1d,&dword_dd7a8,&dword_ddac0,
                               &dword_dd7b0,&dword_dd7ac,&byte_ddd10);
      set_dialog_colors(0xf9,0xfa,0xf8,0xfa,0);
      getmouse(&local_44,local_40,local_28);
      if (((byte)dword_dd7b0 & 0xc) == 0) {
        if (dword_dd7ac != 0) {
          dword_c80a1 = local_64;
          message_dialog(0xffffffff,0xffffffff,&off_c809d,3,0,0,local_40,local_28,0xffffffff);
          goto LAB_0003ca8c;
        }
      }
      else {
        dword_c7e42 = local_64;
        iVar4 = message_dialog(0xffffffff,0xffffffff,&off_c7e3e,4,&unk_c7e4e,2,local_40,local_28,
                               0xffffffff);
        if (iVar4 == 0) {
          league_merge_warning();
          iVar3 = -1;
        }
        else {
LAB_0003ca8c:
          iVar7 = -1;
        }
      }
    } while (iVar3 != 0);
  }
  set_dialog_colors(0xf9,0xfa,0xf8,0xfa,0);
  if ((iVar1 == 0) && (iVar7 == 0)) {
    iVar7 = league_player_id_check(&league_dir,local_48);
    if ((cStack_6e == '\x02') &&
       (((iVar3 = uStack_1f >> 0x18, iStack_24 != 0 || ((&unk_dd7ca)[iVar3 * 0x1e] == '\x02')) ||
        (*(uint *)(&unk_dd7ce + iVar3 * 0x1e) < uStack_6a)))) {
      if (iStack_24 == 0) {
        if (uStack_6a < *(uint *)(&unk_dd7ce + iVar3 * 0x1e)) {
          dword_c7c25 = local_64;
          getmouse(&local_44,local_40,local_28);
          uVar5 = 3;
          ppuVar6 = &off_c7c1d;
          goto LAB_0003cb7f;
        }
        if (iVar7 < 0) {
          show_league_message(auStack_54);
          cStack_6e = '\x01';
          local_44 = 0;
          while ((local_44 < 7 && (iVar1 == 0))) {
            iVar1 = copy_file((&off_c80d7)[local_44],&aXx,&aXx,&byte_c816a,&league_dir);
            local_44 = local_44 + 1;
          }
        }
        else {
          if (iVar7 != iVar3) {
            dword_c7b16 = local_64;
            dword_c7b1e = &unk_dd7b4 + iVar7 * 0x1e;
            getmouse(&local_44,local_40,local_28);
            uVar5 = 4;
            ppuVar6 = &off_c7b12;
            goto LAB_0003cb7f;
          }
          show_league_message(auStack_54);
          cStack_6e = '\x01';
          iVar1 = league_copy_files(&byte_c816a,&league_dir);
        }
        if (iVar1 == 0) {
          iVar1 = copy_file(&aGAME_c810c,&aSET_c8131,&aSET_c8131,&byte_c816a,&league_dir);
        }
        if (iVar1 == 0) {
          make_path(auStack_a4,&league_dir,aPINFO,&aDB);
          iVar1 = file_open_rw(auStack_a4,&local_30);
        }
        if (iVar1 == 0) {
          iVar1 = league_write_team_entry(local_30,auStack_84,uStack_1f >> 0x18);
        }
        file_close(&local_30);
        if (iVar1 == 0) {
          make_path(auStack_a4,&byte_c816a,aPINFO,&aDB);
          iVar1 = file_open_rw(auStack_a4,&local_2c);
        }
        if (iVar1 == 0) {
          league_write_team_entry(local_2c,auStack_84,uStack_1f >> 0x18);
        }
      }
      else {
        show_league_message(auStack_54);
        strcpy(local_64,&league_dir);
        iVar1 = mkdir(local_64,0xc8451);
        cStack_6e = '\x01';
        if (iVar1 == 0) {
          iVar1 = league_copy_files(&byte_c816a,&league_dir);
        }
        if (iVar1 == 0) {
          iVar1 = copy_file(&aGAME_c810c,&aSET_c8131,&aSET_c8131,&byte_c816a,&league_dir);
        }
        if (iVar1 == 0) {
          make_path(auStack_a4,&league_dir,aPINFO,&aDB);
          iVar1 = file_open_rw(auStack_a4,&local_30);
        }
        if (iVar1 == 0) {
          iVar1 = league_write_team_entry(local_30,auStack_84,uStack_1f >> 0x18);
        }
        file_close(&local_30);
        if (iVar1 == 0) {
          make_path(auStack_a4,&byte_c816a,aPINFO,&aDB);
          iVar1 = file_open_rw(auStack_a4,&local_2c);
        }
        if (iVar1 == 0) {
          league_write_team_entry(local_2c,auStack_84,uStack_1f >> 0x18);
        }
      }
      file_close(&local_2c);
    }
    else {
      set_dialog_colors(0xf9,0xfa,0xf8,0xfa,0);
      dword_c7b47 = auStack_54;
      dword_c7b4f = local_64;
      getmouse(&local_44,local_40,local_28);
      uVar5 = 3;
      ppuVar6 = &dword_c7b47;
LAB_0003cb7f:
      message_dialog(0xffffffff,0xffffffff,ppuVar6,uVar5,0,0,local_40,local_28,0xffffffff);
    }
  }
  if ((iVar1 != 0) && (iStack_24 != 0)) {
    strcpy(local_64,&league_dir);
    delete_directory(local_64);
  }
LAB_0003cef9:
  restore_dialog_background();
  if (iVar1 != 0) {
    getmouse(&local_44,local_40,local_28);
    message_dialog(0xffffffff,0xffffffff,&off_c792b,1,0,0,local_40,local_28,0xffffffff);
  }
  return CONCAT44(unaff_EDX,iVar1);
}


// ================================================================================================
// load_game_set_db @ 0x3cf5b [__watcall]
// ================================================================================================

void __watcall load_game_set_db(void)

{
  int iVar1;
  undefined auStack_3c [32];
  undefined auStack_1c [4];
  int local_18;
  undefined4 uStack_14;
  undefined auStack_10 [4];
  
  __CHK(0x54);
  set_dialog_colors(0xf9,0xfa,0xf8,0xfa,0);
  getmouse(&local_18,auStack_10,auStack_1c);
  local_18 = message_dialog(0xffffffff,0xffffffff,&off_c7ce9,2,&unk_c7cf1,2,auStack_10,auStack_1c,
                            0xffffffff);
  if (-1 < local_18) {
    iVar1 = message_dialog(0xffffffff,0xffffffff,&off_c7905,2,0,0,auStack_10,auStack_1c,0xffffffff);
    if (iVar1 == 0) {
      iVar1 = player_id_write(0,0);
    }
    if (iVar1 == 0) {
      if (local_18 == 0) {
        iVar1 = import_game_set();
      }
      else {
        iVar1 = player_db_sync();
      }
      if (iVar1 == 0) {
        make_path(auStack_3c,&league_dir,&aGAME_c191e,&aSET);
        iVar1 = file_open_read(auStack_3c,&uStack_14);
        if (iVar1 == 0) {
          iVar1 = file_read(uStack_14,&settings_league,0xffffffff,0x75);
          if (iVar1 != 0) {
            fatalerror(&aL1_c192d);
          }
          iVar1 = file_close(&uStack_14);
          if (iVar1 != 0) {
            fatalerror(&aL2_c1930);
          }
        }
        apply_settings(&settings_league);
        set_league_menu_titles();
        set_menu_mode(0);
        dword_ce4e3 = league_select_team;
        dword_ce503 = league_calendar_screen;
        dword_ce527 = &unk_ce64f;
      }
      else {
        byte_c5386 = 0;
        set_league_menu_titles();
        set_menu_mode(0);
        dword_ce4e3 = (code *)0x0;
        dword_ce503 = (code *)0x0;
        dword_ce527 = (undefined *)0x0;
      }
    }
  }
  set_dialog_colors(0x2a,0x3f,0x17,0x3f,0);
  return;
}


// ================================================================================================
// select_team_dialog @ 0x3d108 [__watcall]
// ================================================================================================

void __watcall select_team_dialog(void)

{
  int iVar1;
  size_t sVar2;
  int iVar3;
  undefined4 *puVar4;
  int iVar5;
  undefined2 in_DS;
  undefined local_60 [32];
  char acStack_40 [16];
  char acStack_30 [4];
  undefined auStack_2c [4];
  undefined auStack_28 [4];
  int iStack_24;
  int iStack_20;
  undefined auStack_1c [4];
  
  __CHK(0x78);
  iVar1 = return_zero_41337(&league_dir,3);
  do {
    iVar5 = 0;
    if (iVar1 == 0) {
      iVar1 = load_league_info(&league_dir,&unk_dd7b4,&unk_ddd1d,&dword_dd7a8,&dword_ddac0,
                               &dword_dd7b0,&dword_dd7ac,&byte_ddd10);
      strcpy(acStack_40,&league_dir);
      sVar2 = strcspn(acStack_40,(char *)CONCAT22(0xc,in_DS));
      acStack_40[sVar2] = '\0';
      set_dialog_colors(0xf9,0xfa,0xf8,0xfa,0);
      getmouse(&iStack_24,auStack_1c,auStack_2c);
      if (((byte)dword_dd7b0 & 0xc) == 0) {
        if (dword_dd7ac != 0) {
          dword_c80a1 = acStack_40;
          message_dialog(0xffffffff,0xffffffff,&off_c809d,3,0,0,auStack_1c,auStack_2c,0xffffffff);
          goto LAB_0003d23e;
        }
      }
      else {
        dword_c7e42 = acStack_40;
        iStack_24 = message_dialog(0xffffffff,0xffffffff,&off_c7e3e,4,&unk_c7e4e,2,auStack_1c,
                                   auStack_2c,0xffffffff);
        if (iStack_24 == 0) {
          league_merge_warning();
          iVar5 = -1;
        }
        else {
LAB_0003d23e:
          iVar1 = -1;
        }
      }
    }
    if (iVar5 == 0) {
      if (iVar1 == 0) {
        make_path(local_60,&league_dir,off_c80e7,&aDB);
        iVar1 = db_open_check(local_60,&unk_ddac4,1);
        if (iVar1 == 0) {
          iVar1 = -1;
          iStack_20 = league_player_id_check(&league_dir,auStack_28);
          if (iStack_20 < 0) {
            team_info_screen(&league_dir,&dword_ddac0,&unk_ddac4,&unk_dd7b4,8,aSelectATeamToExport,
                             &iStack_20);
            if (dword_ddac0 == 1) {
              set_dialog_colors(0xf9,0xfa,0xf8,0xfa,0);
            }
          }
          else {
            iVar1 = 0;
          }
          iVar5 = 0;
          if ((-1 < iStack_20) && ((&unk_dd7ca)[iStack_20 * 0x1e] == '\x02')) {
            dword_c79c0 = acStack_40;
            dword_c79c8 = &unk_dd7b4 + iStack_20 * 0x1e;
            getmouse(&iStack_24,auStack_1c,auStack_2c);
            iStack_24 = message_dialog(0xffffffff,0xffffffff,&dword_c79c0,4,&unk_c79d0,2,auStack_1c,
                                       auStack_2c,0xffffffff);
            iVar3 = -1;
            if (iStack_24 == 0) {
              iVar3 = master_password_prompt(dword_dd7a8,&unk_dd7b4,&unk_ddd1d);
            }
            if (iVar3 == 0) {
              iVar5 = -1;
              *(short *)(&unk_dd7d0 + iStack_20 * 0x1e) =
                   *(short *)(&unk_dd7d0 + iStack_20 * 0x1e) + 1;
            }
            else {
              iStack_20 = -1;
            }
          }
          if (-1 < iStack_20) {
            if ((dword_ddac0 == 1) || (iVar1 == 0)) {
              set_dialog_colors(0xf9,0xfa,0xf8,0xfa,0);
            }
            sprintf(acStack_30,a02d_c1927,iStack_20);
            strcpy((char *)&aXx,acStack_30);
            if (iVar5 == 0) {
              puVar4 = &aXx;
            }
            else {
              puVar4 = &aDB;
            }
            iVar1 = player_id_write(&league_dir,&unk_dd7b4 + iStack_20 * 0x1e);
            if (iVar1 == 0) {
              pinfo_find_player(&league_dir,puVar4,&aXx,iStack_20,&unk_dd7b4,iVar5,0xffffffff);
            }
          }
        }
      }
      set_dialog_colors(0x2a,0x3f,0x17,0x3f,0);
      return;
    }
  } while( true );
}


// ================================================================================================
// player_id_write @ 0x3d46d [__watcall]
// ================================================================================================

int __watcall player_id_write(int param_1,int unaff_EDX)

{
  char cVar1;
  int iVar2;
  int iVar3;
  undefined auStack_6c [32];
  undefined auStack_4c [16];
  undefined local_3c [12];
  undefined local_30 [8];
  undefined4 local_28;
  undefined local_24 [4];
  undefined local_20 [4];
  int local_1c;
  int iStack_18;
  
  __CHK(0x84);
  local_28 = 0xffffffff;
  dword_dd784 = 0xffffffff;
  do {
    iStack_18 = 0;
    iVar3 = 0;
    local_1c = 0;
    while ((local_1c < 2 && (iVar3 == 0))) {
      dword_dd7a4 = iVar3;
      (&dword_dd748)[local_1c] = 0xffffffff;
      _dos_getdiskfree(local_1c + 1,local_30);
      if (dword_dd7a4 == 0) {
        if ((param_1 != 0) && (unaff_EDX != 0)) {
          byte_c816a = (char)local_1c + 'A';
          make_path(auStack_6c,&byte_c816a,aPLAYER_c80f9);
          iVar2 = file_open_read(auStack_6c,&local_28);
          if (iVar2 == 0) {
            file_read(local_28,local_3c,1,0xb);
            file_read(local_28,auStack_4c,0xffffffff);
            iVar2 = stricmp(unaff_EDX,local_3c);
            if (iVar2 == 0) {
              iVar2 = stricmp(param_1,auStack_4c);
              if (iVar2 == 0) {
                iVar3 = -1;
              }
            }
          }
          file_close(&local_28);
        }
      }
      else {
        (&dword_dd748)[local_1c] = 0;
      }
      local_1c = local_1c + 1;
    }
    if ((dword_dd748 == 0) && (dword_dd74c == 0)) {
      getmouse(&local_1c,local_20,local_24);
      iStack_18 = message_dialog(0xffffffff,0xffffffff,&off_c7fb9,1,0,0,local_20,local_24,0xffffffff
                                );
    }
  } while (((dword_dd748 == 0) && (dword_dd74c == 0)) && (iStack_18 != 4));
  dword_dd784 = 0;
  if ((iVar3 == 0) && (iStack_18 != 4)) {
    if ((dword_dd748 == 0) || (dword_dd74c == 0)) {
      if (dword_dd748 == 0) {
        byte_c816a = 'B';
      }
      else {
        byte_c816a = 'A';
      }
    }
    else {
      getmouse(&local_1c,local_20,local_24);
      cVar1 = message_dialog(0xffffffff,0xffffffff,&off_c7fd6,1,&unk_c8b40,2,local_20,local_24,
                             0xffffffff);
      byte_c816a = cVar1 + 'A';
    }
  }
  return iStack_18;
}


// ================================================================================================
// player_id_read @ 0x3d694 [__watcall]
// ================================================================================================

int __watcall player_id_read(undefined4 param_1,undefined4 unaff_EDX)

{
  int iVar1;
  int iVar2;
  undefined auStack_a8 [64];
  undefined auStack_68 [32];
  undefined auStack_48 [16];
  undefined auStack_38 [12];
  undefined local_2c [8];
  undefined local_24 [4];
  undefined local_20 [4];
  int local_1c;
  undefined4 local_18;
  int iStack_14;
  
  __CHK(0xc0);
  local_18 = 0xffffffff;
  do {
    iVar2 = -1;
    dword_dd784 = 0xffffffff;
    local_1c = 0;
    while ((local_1c < 2 && (iVar2 != 0))) {
      iVar2 = 0;
      dword_dd7a4 = 0;
      (&dword_dd748)[local_1c] = 0xffffffff;
      _dos_getdiskfree(local_1c + 1,local_2c);
      if (dword_dd7a4 == 0) {
        byte_c816a = (char)local_1c + 'A';
        make_path(auStack_68,&byte_c816a,aPLAYER_c80f9);
        iStack_14 = file_open_read(auStack_68,&local_18);
        if (iStack_14 == 0) {
          file_read(local_18,auStack_38,1,0xb);
          file_read(local_18,auStack_48,0xffffffff);
          iVar1 = stricmp(unaff_EDX,auStack_38);
          if (iVar1 != 0) goto LAB_0003d78e;
          iVar1 = stricmp(param_1,auStack_48);
          if (iVar1 != 0) goto LAB_0003d78e;
        }
        else {
LAB_0003d78e:
          iVar2 = -1;
        }
        file_close(&local_18);
      }
      else {
        iVar2 = -1;
      }
      local_1c = local_1c + 1;
    }
    dword_dd784 = 0;
    if (iVar2 != 0) {
      format_from_league(auStack_a8,unaff_EDX,param_1);
      dword_c760d = auStack_a8;
      getmouse(&local_1c,local_20,local_24);
      iStack_14 = message_dialog(0xffffffff,0xffffffff,&off_c7609,6,0,0,local_20,local_24,0xffffffff
                                );
      if (iStack_14 != 0) {
        iVar2 = 0;
      }
    }
    if (iVar2 == 0) {
      return iStack_14;
    }
  } while( true );
}


// ================================================================================================
// player_league_dialog @ 0x3d84f [__watcall]
// ================================================================================================

int __watcall player_league_dialog(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX)

{
  int iVar1;
  undefined auStack_5c [64];
  undefined local_1c [4];
  undefined local_18 [4];
  undefined auStack_14 [4];
  
  __CHK(0x74);
  format_from_league(auStack_5c,unaff_EDX,param_1);
  dword_c7615 = auStack_5c;
  getmouse(auStack_14,local_18,local_1c);
  iVar1 = message_dialog(0xffffffff,0xffffffff,&off_c7611,4,0,0,local_18,local_1c,0xffffffff);
  if (iVar1 != 4) {
    iVar1 = player_id_read(param_1,unaff_EDX,unaff_EBX);
  }
  if (iVar1 == 4) {
    iVar1 = -1;
  }
  return iVar1;
}


// ================================================================================================
// load_league_info @ 0x3d8dd [__watcall]
// ================================================================================================

int __watcall
load_league_info(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 unaff_ECX,
                undefined4 param_5,undefined4 param_6,undefined4 *param_7,undefined4 param_8)

{
  int iVar1;
  size_t sVar2;
  undefined4 uVar3;
  undefined2 in_DS;
  undefined auStack_54 [32];
  char acStack_34 [16];
  undefined auStack_24 [4];
  undefined local_20 [4];
  undefined4 uStack_1c;
  undefined local_18 [4];
  
  __CHK(0x6c);
  uStack_1c = 0xffffffff;
  make_path(auStack_54,param_1,aPINFO,&aDB);
  iVar1 = dos_findfirst_dta(auStack_54);
  if (iVar1 == 0) {
    iVar1 = 1;
    strcpy(acStack_34,&league_dir);
    sVar2 = strcspn(acStack_34,(char *)CONCAT22(0xc,in_DS));
    acStack_34[sVar2] = '\0';
    dword_c756d = acStack_34;
    set_dialog_colors(0xb,0x11,5,0x11,0);
    getmouse(local_20,auStack_24,local_18);
    message_dialog(0xffffffff,0xffffffff,&off_c7569,2,0,0,auStack_24,local_18,0xffffffff);
  }
  else {
    iVar1 = file_open_read(auStack_54,&uStack_1c);
    if (iVar1 == 0) {
      iVar1 = file_read(uStack_1c,param_5,0,2);
    }
    if (iVar1 == 0) {
      iVar1 = file_read(uStack_1c,unaff_ECX,2);
    }
    if (iVar1 == 0) {
      iVar1 = file_read(uStack_1c,param_7,4,2);
    }
    if (iVar1 == 0) {
      iVar1 = file_read(uStack_1c,param_8,6,0xd);
    }
    if (iVar1 == 0) {
      iVar1 = file_read(uStack_1c,param_6,0x13,2);
    }
    if (iVar1 == 0) {
      iVar1 = file_read(uStack_1c,param_3,0x15,0xb);
    }
    if (iVar1 == 0) {
      iVar1 = file_read(uStack_1c,param_2,0x20,0x30c);
    }
    file_close(&uStack_1c);
    make_path(auStack_54,param_1,&aGame_c1938,&aSav_c193d);
    uVar3 = file_exists_rd(auStack_54);
    *param_7 = uVar3;
  }
  return iVar1;
}


// ================================================================================================
// db_open_check @ 0x3dab9 [__watcall]
// ================================================================================================

undefined4 __watcall db_open_check(undefined4 param_1,int unaff_EDX,int unaff_EBX)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 extraout_EDX;
  int iVar3;
  undefined4 uStackY_14;
  
  __CHK(0x18);
  uStackY_14 = 0xffffffff;
  iVar1 = file_open_read(param_1,&uStackY_14);
  if (iVar1 == 0) {
    iVar3 = 0;
    iVar1 = 0;
    while ((iVar3 < 0x1a && (iVar1 == 0))) {
      if (unaff_EBX == 0) {
        iVar1 = iVar3 * 0x2e8 + 0x1a;
        uVar2 = 0xd;
      }
      else {
        iVar1 = iVar3 * 0x2e8 + 5;
        uVar2 = 0x15;
      }
      iVar1 = file_read(uStackY_14,iVar3 * 0x15 + unaff_EDX,iVar1,uVar2);
      iVar3 = iVar3 + 1;
    }
  }
  file_close(&uStackY_14);
  return extraout_EDX;
}


// ================================================================================================
// load_cfg_palette @ 0x3db41 [__watcall]
// ================================================================================================

void __watcall load_cfg_palette(void)

{
  FILE *__stream;
  int iVar1;
  undefined4 uVar2;
  char cStack_28;
  char cStack_27;
  char cStack_26;
  int iStack_18;
  
  __CHK(0x38);
  make_path(&cStack_28,0,&aNHL_c1942,&aCFG_c8145);
  __stream = fopen(&cStack_28,(char *)&aR_c1946);
  if (__stream == (FILE *)0x0) {
    fatalerror(aCannotOpenNhlCfg);
  }
  iVar1 = fscanf(__stream,(char *)&a4x,&iStack_18);
  if (iVar1 == 1) {
    uVar2 = (&unk_d243a)[iStack_18];
  }
  else {
    uVar2 = 0x10;
  }
  fclose(__stream);
  iVar1 = 0;
  do {
    cStack_28 = (&unk_c8b78)[iVar1];
    cStack_27 = cStack_28;
    cStack_26 = cStack_28;
    setpalette(iVar1,1,&cStack_28);
    iVar1 = iVar1 + 1;
  } while (iVar1 < 4);
  atexit_wrap(sound_shutdown);
  setmousepos(0,0);
  set_dialog_colors(2,3,1,3,0);
  set_byte_order(1);
  load_sound_config(uVar2);
  return;
}


// ================================================================================================
// line_editor_load_roster @ 0x3dc2c [__watcall]
// ================================================================================================

int __watcall
line_editor_load_roster(undefined4 param_1,undefined4 unaff_EDX,int unaff_EBX,int unaff_ECX)

{
  int iVar1;
  int iVar2;
  undefined *puVar3;
  undefined uStackY_70;
  undefined uStackY_6f;
  undefined uStackY_6e;
  undefined uStackY_6d;
  char acStackY_5d [33];
  undefined auStackY_3c [32];
  undefined4 local_1c;
  undefined4 local_18;
  int local_14;
  
  __CHK(0x74);
  local_18 = 0xffffffff;
  local_1c = 0xffffffff;
  local_14 = 0;
  do {
    *(undefined *)(unaff_EBX + 2 + local_14 * 0x16) = (undefined)local_14;
    local_14 = local_14 + 1;
  } while (local_14 < 0x1c);
  make_path(auStackY_3c,param_1,off_c80e7,&aDB);
  iVar2 = file_open_read(auStackY_3c,&local_18);
  if (iVar2 == 0) {
    iVar2 = db_read_record(local_18,unaff_ECX,unaff_EDX);
  }
  file_close(&local_18);
  if (iVar2 == 0) {
    make_path(auStackY_3c,param_1,off_c80d7,&aDB);
    iVar2 = file_open_read(auStackY_3c,&local_1c);
  }
  if (iVar2 == 0) {
    local_14 = 0;
    while ((local_14 < 0x19 && (iVar2 == 0))) {
      iVar1 = *(int *)(unaff_ECX + 0x4c + local_14 * 4);
      puVar3 = (undefined *)(local_14 * 0x16 + unaff_EBX);
      if (iVar1 == -1) {
        *puVar3 = 0;
      }
      else {
        iVar2 = file_read_b(local_1c,&uStackY_70,iVar1);
        if (iVar2 == 0) {
          *puVar3 = uStackY_6e;
          puVar3[1] = uStackY_6f;
          puVar3[3] = uStackY_6d;
          puVar3[4] = byte_c8164;
          puVar3[5] = asc_c8111;
          puVar3[6] = 0;
          strcat(puVar3 + 3,acStackY_5d);
        }
      }
      local_14 = local_14 + 1;
    }
    local_14 = 0;
    while ((local_14 < 3 && (iVar2 == 0))) {
      iVar1 = *(int *)(unaff_ECX + 0xb0 + local_14 * 4);
      puVar3 = (undefined *)((local_14 + 0x19) * 0x16 + unaff_EBX);
      if (iVar1 == -1) {
        *puVar3 = 0;
      }
      else {
        iVar2 = file_read_b(local_1c,&uStackY_70,iVar1);
        if (iVar2 == 0) {
          *puVar3 = uStackY_6e;
          puVar3[1] = uStackY_6f;
          puVar3[3] = uStackY_6d;
          puVar3[4] = byte_c8164;
          puVar3[5] = asc_c8111;
          puVar3[6] = 0;
          strcat(puVar3 + 3,acStackY_5d);
        }
      }
      local_14 = local_14 + 1;
    }
  }
  file_close(&local_1c);
  return iVar2;
}


// ================================================================================================
// roster_stats_screen @ 0x3de05 [__watcall]
// ================================================================================================

void __watcall
roster_stats_screen(undefined4 param_1,byte unaff_DL,undefined4 unaff_EBX,undefined4 unaff_ECX,
                   undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  void *__dest;
  undefined4 uVar1;
  int iVar2;
  undefined *puVar3;
  undefined auStack_28 [16];
  
  __CHK(0x38);
  setdefaultscreen();
  __dest = (void *)allocmem(&aTemp_c1964,0x300,0x20);
  getpalette(0,0x100,__dest);
  fade_palette(1,__dest,0x10);
  clearclip(0);
  stats_hub_active = 1;
  stats_current_screen = player_stats_screen;
  stats_current_arg = (uint)unaff_DL;
  standings_rows = allocmem(aTstat_c1969,0x2a4,0x20);
  dword_dd11c = allocmem(&aKeys_c196f,0x5b0,0x20);
  dword_dd110 = allocmem(aPstat_c1974,0x497,0x20);
  dword_dd114 = allocmem(aGstat_c197a,0x10e,0x20);
  puVar3 = install_path;
  if (byte_ed85a != '\x01') {
    puVar3 = (undefined *)0x0;
  }
  make_path(auStack_28,puVar3,aEmbpal_c1980,0);
  uVar1 = loadshapes(auStack_28,0);
  iVar2 = locateshape(uVar1,&aPal_c1987);
  memcpy(__dest,(void *)(iVar2 + 0x10),0x300);
  freemem(uVar1);
  hub_build_remap(1);
  player_stats_screen(unaff_DL);
  draw_menu_items(&unk_c88e2,2,0x40,0x41,0x42);
  fade_palette(0,__dest,0x10);
  run_menu(&unk_c88e2,2,0x40,0x41,0x42);
  stats_hub_active = 0;
  stats_current_screen = (code *)0x0;
  freemem(standings_rows);
  freemem(dword_dd114);
  freemem(dword_dd110);
  freemem(dword_dd11c);
  dword_dd11c = 0;
  standings_rows = 0;
  dword_dd114 = 0;
  dword_dd110 = 0;
  setdefaultscreen();
  fade_palette(1,__dest,0x10);
  clearclip(0);
  freemem(__dest);
  team_roster_screen(param_1,param_5,param_7,param_6,param_8,unaff_ECX,unaff_EBX);
  return;
}


// ================================================================================================
// jersey_number_dialog @ 0x3e055 [__watcall]
// ================================================================================================

int __watcall jersey_number_dialog(undefined4 param_1,int unaff_EDX,int unaff_EBX)

{
  byte bVar1;
  int iVar2;
  byte abStack_654 [1456];
  char acStack_a4 [84];
  char acStack_50 [32];
  undefined local_30 [4];
  undefined local_2c [4];
  undefined local_28 [4];
  int local_24;
  undefined4 local_20;
  byte *local_1c;
  undefined uStack_14;
  undefined uStack_13;
  undefined uStack_12;
  
  __CHK(0x670);
  iVar2 = 0;
  local_24 = 0;
  while ((local_24 < 0x1c && (iVar2 == 0))) {
    iVar2 = file_read_b(param_1,abStack_654 + local_24 * 0x34,
                        *(undefined4 *)(local_24 * 4 + unaff_EBX + 0x4c));
    local_24 = local_24 + 1;
  }
  while( true ) {
    if (iVar2 != 0) {
      return iVar2;
    }
    iVar2 = 0;
    local_24 = 0;
    while ((local_24 < 0x1c && (iVar2 == 0))) {
      if ((unaff_EDX != local_24) &&
         (abStack_654[unaff_EDX * 0x34 + 1] == abStack_654[local_24 * 0x34 + 1])) {
        iVar2 = -1;
      }
      local_24 = local_24 + 1;
    }
    if (iVar2 == 0) break;
    local_20 = allocmem(aDonepal,0xc,0x20);
    getpalette(0xfb,4,local_20);
    uStack_14 = 0x18;
    uStack_13 = 0;
    uStack_12 = 0;
    setpalette(0xfb,1,&uStack_14);
    uStack_14 = 0x2a;
    uStack_13 = 0;
    uStack_12 = 0;
    setpalette(0xfc,1,&uStack_14);
    uStack_14 = 0x3b;
    uStack_13 = 0x12;
    uStack_12 = 0;
    setpalette(0xfd,1,&uStack_14);
    uStack_14 = 0x3b;
    uStack_13 = 0x3b;
    uStack_12 = 0x3b;
    setpalette(0xfe,1,&uStack_14);
    iVar2 = unaff_EDX * 0x34;
    local_1c = abStack_654 + iVar2;
    strcpy(acStack_50,(char *)(abStack_654 + iVar2 + 3));
    strcat(acStack_50,&asc_c8111);
    strcat(acStack_50,(char *)(local_1c + 0x13));
    sprintf(acStack_a4,aTheJerseyNumber2dIsAlrea,(uint)abStack_654[iVar2 + 1],unaff_EBX + 0x1a);
    dword_de25c = acStack_a4;
    getmouse(&local_24,local_28,local_2c);
    message_dialog(0xffffffff,0xffffffff,&dword_de25c,1,0,0,local_28,local_2c,0xffffffff);
    setpalette(0xfb,4,local_20);
    freemem(local_20);
    sprintf(acStack_a4,aEnterJerseyNumberForS,acStack_50);
    local_30[0] = 0;
    bVar1 = text_entry_dialog(acStack_a4,local_30,2,0x16,0xffffffff,1,99,0,0);
    abStack_654[iVar2 + 1] = bVar1;
    iVar2 = file_write_b(param_1,local_1c);
  }
  return 0;
}


// ================================================================================================
// team_edit_screen @ 0x3e390 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __watcall team_edit_screen(undefined4 param_1,undefined4 *unaff_EDX,int unaff_EBX)

{
  byte bVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  undefined auStack_67c [76];
  undefined4 auStack_630 [28];
  undefined auStack_5c0 [48];
  undefined auStack_590 [508];
  undefined auStack_394 [76];
  undefined4 auStack_348 [28];
  undefined auStack_2d8 [48];
  undefined auStack_2a8 [508];
  undefined auStack_ac [52];
  undefined auStack_78 [52];
  undefined auStack_44 [32];
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  int iVar5;
  int iStack_14;
  
  __CHK(0x68c);
  local_20 = 0xffffffff;
  local_24 = 0xffffffff;
  iStack_14 = 0;
  make_path(auStack_44,param_1,off_c80e7);
  iVar2 = file_open_rw(auStack_44,&local_20);
  if (iVar2 == 0) {
    iVar2 = db_read_record(local_20,auStack_67c,*unaff_EDX);
  }
  if (iVar2 == 0) {
    iVar2 = db_read_record(local_20,auStack_394,unaff_EDX[1]);
  }
  if (iVar2 == 0) {
    make_path(auStack_44,param_1,off_c80d7);
    iVar2 = file_open_rw(auStack_44,&local_24);
  }
  if (iVar2 == 0) {
    iVar4 = 0;
    while ((iVar4 < 2 && (iVar2 == 0))) {
      bVar1 = *(byte *)(unaff_EBX + iVar4);
      if ((bVar1 != 0xff) && (((byte *)(unaff_EBX + iVar4))[2] != 0xff)) {
        iStack_14 = -1;
        uVar3 = auStack_630[bVar1];
        iVar2 = file_read_b(local_24,auStack_78);
        if (iVar2 == 0) {
          local_1c = auStack_348[*(byte *)(unaff_EBX + iVar4 + 2)];
          iVar2 = file_read_b(local_24,auStack_ac,local_1c);
        }
        if (iVar2 == 0) {
          auStack_78[0] = *(undefined *)(unaff_EDX + 1);
          auStack_ac[0] = *(undefined *)unaff_EDX;
          auStack_630[*(byte *)(unaff_EBX + iVar4)] = local_1c;
          auStack_348[*(byte *)(unaff_EBX + iVar4 + 2)] = uVar3;
          iVar5 = unaff_EBX;
          lines_remove_player(*(undefined *)(iVar4 + unaff_EBX),auStack_5c0);
          lines_remove_player(*(undefined *)(iVar4 + unaff_EBX),auStack_590);
          lines_remove_player(*(undefined *)(iVar4 + 2 + unaff_EBX),auStack_2d8);
          lines_remove_player(*(undefined *)(iVar4 + 2 + unaff_EBX),auStack_2a8);
          iVar2 = file_write_b(local_24,auStack_78,uVar3);
          unaff_EBX = iVar5;
          if (iVar2 == 0) {
            iVar2 = file_write_b(local_24,auStack_ac,local_1c);
            unaff_EBX = iVar5;
          }
          if (iVar2 == 0) {
            iVar2 = db_write_team_record(local_20,auStack_67c,*unaff_EDX);
          }
          if (iVar2 == 0) {
            iVar2 = db_write_team_record(local_20,auStack_394,unaff_EDX[1]);
          }
          if (iVar2 == 0) {
            iVar2 = jersey_number_dialog(local_24,*(undefined *)(iVar4 + unaff_EBX),auStack_67c);
          }
          if (iVar2 == 0) {
            iVar2 = jersey_number_dialog(local_24,*(undefined *)(iVar4 + 2 + unaff_EBX),auStack_394)
            ;
          }
        }
      }
      iVar4 = iVar4 + 1;
    }
  }
  file_close(&local_24);
  file_close(&local_20);
  if ((iVar2 == 0) && (iStack_14 != 0)) {
    user2_team._2_2_ = *(undefined2 *)unaff_EDX;
    _away_team_id = *(undefined2 *)(unaff_EDX + 1);
    strcpy(&byte_dd750,&league_dir);
    strcat(&byte_dd750,&unk_c8115);
    strcat(&byte_dd750,(char *)&aS_c8117);
    strcat(&byte_dd750,(char *)&aDB);
    strcpy(&byte_dd710,&byte_dd750);
    load_team_databases(0);
    _period_num = 0xfffffffe;
    edit_lines_screen_b(0,&unk_dc200,&unk_cf3cf,3);
    uVar3 = allocmem(&aPal_c19dc,0x300,0x20);
    getpalette(0,0x100,uVar3);
    fade_palette(1,uVar3,0x10);
    freemem(uVar3);
    edit_lines_screen_b(1,&unk_dabf0,&unk_cf3cf,3);
    uVar3 = allocmem(&aPal_c19dc,0x300,0x20);
    getpalette(0,0x100,uVar3);
    fade_palette(1,uVar3,0x10);
    freemem(uVar3);
  }
  return iVar2;
}


// ================================================================================================
// line_editor_draw_entry @ 0x3e7b3 [__watcall]
// ================================================================================================

void __watcall line_editor_draw_entry(int param_1)

{
  int iVar1;
  
  __CHK(0x2c);
  iVar1 = (&dword_ddd84)[param_1] * 0x16 + param_1 * 0x268;
  printf_at(param_1 * 0x1c0 + 5,(uint)byte_d42c3 * (&dword_ddd84)[param_1] + 0x1d,aC2dS,
            (&unk_ddd8c)[iVar1],(&unk_ddd8d)[iVar1],
            &DAT_000ddd8f + param_1 * 0x268 + (&dword_ddd84)[param_1] * 0x16);
  return;
}


// ================================================================================================
// team_roster_load_palettes @ 0x3e835 [__watcall]
// ================================================================================================

void __watcall team_roster_load_palettes(int param_1,int unaff_EDX,int unaff_EBX)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined *puVar4;
  undefined auStack_20 [16];
  
  __CHK(0x2c);
  puVar4 = install_path;
  if (byte_ed86d != '\x01') {
    puVar4 = (undefined *)0x0;
  }
  make_path(auStack_20,puVar4,aHOMEPALS,&aBIN);
  iVar1 = loadfile(auStack_20,0);
  iVar3 = iVar1 + param_1 * 0x1c0;
  iVar2 = 0;
  do {
    *(undefined *)(unaff_EBX + 0x180 + iVar2) = *(undefined *)(iVar3 + iVar2);
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0xc0);
  iVar2 = 0;
  do {
    (&remap_home)[iVar2] = *(undefined *)(iVar3 + 0xc0 + iVar2);
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0x100);
  freemem(iVar1);
  puVar4 = install_path;
  if (byte_ed7f7 != '\x01') {
    puVar4 = (undefined *)0x0;
  }
  make_path(auStack_20,puVar4,aHOMEPALS,&aBIN);
  iVar1 = loadfile(auStack_20,0);
  iVar3 = iVar1 + unaff_EDX * 0x1c0;
  iVar2 = 0;
  do {
    *(undefined *)(unaff_EBX + 0x240 + iVar2) = *(undefined *)(iVar3 + iVar2);
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0xc0);
  iVar2 = 0;
  iVar3 = iVar3 + 0xc0;
  do {
    (&remap_away)[iVar2] = *(undefined *)(iVar3 + iVar2);
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0x90);
  iVar2 = 0x90;
  do {
    (&remap_away)[iVar2] = *(char *)(iVar3 + iVar2) + '@';
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0x100);
  freemem(iVar1);
  *(undefined *)(unaff_EBX + 0x171) = 0x18;
  *(undefined *)(unaff_EBX + 0x172) = 0;
  *(undefined *)(unaff_EBX + 0x173) = 0;
  *(undefined *)(unaff_EBX + 0x174) = 0x2a;
  *(undefined *)(unaff_EBX + 0x175) = 0;
  *(undefined *)(unaff_EBX + 0x176) = 0;
  *(undefined *)(unaff_EBX + 0x177) = 0x3b;
  *(undefined *)(unaff_EBX + 0x178) = 0x12;
  *(undefined *)(unaff_EBX + 0x179) = 0;
  *(undefined *)(unaff_EBX + 0x17a) = 0x3b;
  *(undefined *)(unaff_EBX + 0x17b) = 0x3b;
  *(undefined *)(unaff_EBX + 0x17c) = 0x3b;
  byte_d1333 = 0x7b;
  byte_d1334 = 0x7c;
  byte_d1335 = 0x7d;
  byte_d1336 = 0x7e;
  return;
}


// ================================================================================================
// team_roster_screen @ 0x3e9cf [__watcall]
// ================================================================================================

void __watcall
team_roster_screen(undefined4 param_1,undefined4 param_2,undefined4 unaff_EBX,undefined4 param_4,
                  undefined4 param_5,int param_6,undefined4 *param_7)

{
  int iVar1;
  undefined4 uVar2;
  void *__dest;
  undefined *puVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined auStack_44 [32];
  undefined auStack_24 [16];
  undefined4 uStack_14;
  void *pvStack_10;
  
  __CHK(0x60);
  setscreen(dword_de264);
  puVar3 = install_path;
  if (byte_ed858 != '\x01') {
    puVar3 = (undefined *)0x0;
  }
  make_path(auStack_24,puVar3,aEmbnhl_c19f3,0);
  uStack_14 = loadshapes(auStack_24,0);
  uVar2 = locateshape(uStack_14,&aBkgd_c19fa,0,0);
  drawshape_remap(uVar2);
  freemem(uStack_14);
  draw_menu_items(unaff_EBX,param_5,0x40,0x41,0x42);
  draw_bevel_box_b(0x1c0,0,0x27f,0x1df,1);
  draw_bevel_box_b(0,0,0xbe,0x1df,1);
  __dest = (void *)allocmem(&aPal_c19dc,0x300,0x20);
  pvStack_10 = __dest;
  make_path(auStack_44,0,aEmbpal_c1980,0);
  dword_dd104 = loadshapes(auStack_44,0);
  dword_dd100 = locateshape(dword_dd104,&aPal_c1987);
  memcpy(__dest,(void *)(dword_dd100 + 0x10),0x300);
  freemem(dword_dd104);
  team_roster_load_palettes(*param_7,param_7[1],__dest);
  dword_ddd7c = &remap_home;
  dword_ddd80 = &remap_away;
  iVar5 = 0;
  do {
    memcpy(&unk_d12c8,(void *)((int)(&dword_ddd7c)[iVar5 >> 1] + 0x90),0x30);
    jersey_number_bitmap
              (&unk_d1238,*(undefined *)(param_6 + 1 + iVar5 * 0x16),
               (&unk_d1238)[(byte)(&unk_d11bc)[param_7[iVar5 >> 1] * 4]],byte_d12de);
    setremaptable(&unk_d1238);
    drawshape2_trans(param_2,(&unk_c8b7c)[iVar5 * 2],(&unk_c8b80)[iVar5 * 2]);
    iVar5 = iVar5 + 1;
  } while (iVar5 < 4);
  iVar5 = 0;
  do {
    iVar6 = 0;
    do {
      if ((&unk_ddd8c)[iVar6 * 0x16 + iVar5 * 0x268] == '\0') break;
      if (iVar6 == (&dword_ddd84)[iVar5]) {
        uVar2 = 0x42;
      }
      else {
        uVar2 = 0x40;
      }
      settextpos(uVar2,0x41);
      iVar4 = iVar5 * 0x268;
      iVar1 = iVar6 * 0x16;
      printf_at(iVar5 * 0x1c0 + 5,(uint)byte_d42c3 * iVar6 + 0x1d,aC2dS,(&unk_ddd8c)[iVar1 + iVar4],
                (&unk_ddd8d)[iVar1 + iVar4],&DAT_000ddd8f + iVar1 + iVar4);
      iVar6 = iVar6 + 1;
    } while (iVar6 < 0x1c);
    iVar5 = iVar5 + 1;
    if (1 < iVar5) {
      setdefaultscreen();
      drawshape2_home(*(undefined4 *)(dword_de264 + 0x2c));
      fade_palette(0,pvStack_10,0x10);
      freemem(pvStack_10);
      return;
    }
  } while( true );
}


// ================================================================================================
// line_editor_hit_test @ 0x3ecae [__watcall]
// ================================================================================================

undefined4 __watcall
line_editor_hit_test(int param_1,int unaff_EDX,int unaff_EBX,uint *unaff_ECX,undefined4 *param_5)

{
  undefined4 uVar1;
  int iVar2;
  
  __CHK(0x14);
  uVar1 = 0;
  *param_5 = 0;
  param_1 = param_1 + 4;
  if ((param_1 < 0xbf) || (0x1bf < param_1)) {
    if ((0x1c < unaff_EDX) && (unaff_EDX < (int)((uint)byte_d42c3 * 0x1c + 0x1d))) {
      *unaff_ECX = (uint)(0xbd < param_1);
      *(int *)(*unaff_ECX * 4 + unaff_EBX) = (unaff_EDX + -0x1d) / (int)(uint)byte_d42c3 + 100;
      uVar1 = 1;
    }
  }
  else {
    iVar2 = 0;
    do {
      if (((((int)(&unk_c8b7c)[iVar2 * 2] <= param_1) && (param_1 < (&unk_c8b7c)[iVar2 * 2] + 0x3a))
          && ((int)(&unk_c8b80)[iVar2 * 2] <= unaff_EDX)) &&
         (unaff_EDX < (&unk_c8b80)[iVar2 * 2] + 0x28)) {
        if ((int)*unaff_ECX < 0) {
          *unaff_ECX = iVar2 / 2;
          *(int *)((iVar2 / 2) * 4 + unaff_EBX) = iVar2;
          *param_5 = 0xffffffff;
        }
        else {
          *(int *)(*unaff_ECX * 4 + unaff_EBX) = iVar2;
        }
        uVar1 = 1;
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 < 4);
  }
  return uVar1;
}


// ================================================================================================
// line_editor_done @ 0x3edaa [__watcall]
// ================================================================================================

void __watcall line_editor_done(void)

{
  undefined4 uVar1;
  int iVar2;
  int in_stack_00000014;
  undefined4 local_14;
  undefined4 local_10;
  int local_c;
  undefined4 uStack_8;
  
  uStack_8 = 0x3edb4;
  __CHK(0x2c);
  iVar2 = 0;
  local_c = 0;
  do {
    if (((*(char *)(local_c + in_stack_00000014) == -1) &&
        (((char *)(local_c + in_stack_00000014))[2] != -1)) ||
       ((*(char *)(local_c + in_stack_00000014) != -1 &&
        (((char *)(local_c + in_stack_00000014))[2] == -1)))) {
      iVar2 = -1;
    }
    local_c = local_c + 1;
  } while (local_c < 2);
  if (iVar2 == 0) {
    dword_dd79c = 1;
  }
  else {
    uVar1 = allocmem(aDonepal,0xc,0x20);
    getpalette(0xfb,4,uVar1);
    uStack_8._0_3_ = 0x18;
    setpalette(0xfb,1,&uStack_8);
    uStack_8._0_3_ = 0x2a;
    setpalette(0xfc,1,&uStack_8);
    uStack_8._0_3_ = 0x123b;
    setpalette(0xfd,1,&uStack_8);
    uStack_8 = CONCAT13(uStack_8._3_1_,0x3b3b3b);
    setpalette(0xfe,1,&uStack_8);
    getmouse(&local_c,&local_10,&local_14);
    message_dialog(0xffffffff,0xffffffff,&off_c8bdd,3,0,0,&local_10,&local_14,0xffffffff);
    setpalette(0xfb,4,uVar1);
    freemem(uVar1);
    setmousepos(local_10,local_14);
  }
  return;
}


// ================================================================================================
// line_editor_cancel @ 0x3ef27 [__watcall]
// ================================================================================================

void __watcall line_editor_cancel(void)

{
  __CHK(4);
  dword_dd79c = 0xffffffff;
  return;
}


// ================================================================================================
// line_editor_find_number @ 0x3ef3c [__watcall]
// ================================================================================================

int __watcall line_editor_find_number(int param_1,char unaff_DL)

{
  int iVar1;
  
  __CHK(0x14);
  iVar1 = 0;
  do {
    if ((&unk_ddd8e)[iVar1 * 0x16 + param_1 * 0x268] == unaff_DL) {
      return iVar1;
    }
    iVar1 = iVar1 + 1;
  } while (iVar1 < 0x1c);
  return -1;
}


// ================================================================================================
// line_editor_screen @ 0x3ef89 [__watcall]
// ================================================================================================

/* WARNING: Type propagation algorithm not settling */

int __watcall
line_editor_screen(undefined4 param_1,undefined4 param_2,char ******param_3,char ******unaff_ECX,
                  char ******param_5,undefined4 param_6,undefined4 param_7,char ******param_8)

{
  undefined uVar1;
  byte bVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  char *****pppppcVar9;
  char *****pppppcVar10;
  char ******ppppppcVar11;
  undefined4 uVar12;
  char ******ppppppcVar13;
  int iVar14;
  char ****ppppcVar15;
  undefined4 *puVar16;
  int extraout_ECX;
  undefined4 uVar17;
  undefined *puVar18;
  undefined4 *puVar19;
  byte *pbVar20;
  undefined4 *puVar21;
  undefined4 *puVar22;
  char *pcVar23;
  char *pcVar24;
  byte bVar25;
  ulonglong uVar26;
  char acStack_118 [80];
  int aiStack_c8 [10];
  int local_a0 [8];
  char ******local_80 [5];
  int local_6c;
  undefined4 local_68;
  undefined4 local_64;
  int local_60;
  int local_5c;
  int local_58;
  char ******local_54;
  char *****local_50;
  char ******local_4c;
  char *****local_48;
  char ******local_44;
  int local_40;
  char ******local_3c;
  undefined4 *local_38;
  char *****local_34;
  int local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 *local_20;
  int local_1c;
  int local_18;
  char ******local_14;
  char ******local_10;
  
  bVar25 = 0;
  __CHK(0x140);
  local_10 = (char ******)0x0;
  local_24 = 0x40;
  local_28 = 0x41;
  local_2c = 0x42;
  local_3c = (char ******)0x0;
  do {
    acStack_118[(int)local_3c * 0x16 + 1] = -1;
    local_3c = (char ******)((int)local_3c + 1);
  } while ((int)local_3c < 4);
  team_roster_screen(param_2,param_1,param_5,param_7,param_8,acStack_118,param_3);
  local_38 = (undefined4 *)locateshape(param_6,&aPntr_c19ff);
  local_80[4] = param_5;
  local_80[0] = param_8;
  local_64 = 0;
  local_68 = 0;
  local_6c = 0;
  local_a0[3] = 0;
  local_a0[2] = 0;
  local_a0[1] = 0;
  local_a0[0] = 0;
  local_a0[7] = 0;
  local_a0[6] = 0;
  local_a0[5] = 0;
  local_a0[4] = 0;
  aiStack_c8[3] = 0;
  aiStack_c8[2] = 0;
  funcptr_cf2c3 = (undefined *)0x0;
  funcptr_cf2a3 = (undefined *)0x0;
  local_20 = (undefined4 *)
             allocmem(aPointer_c1a04,
                      ((*(int *)((int)local_38 + 2) >> 0x10) * 4 + 4) *
                      (((int)local_38[1] >> 0x10) + 1) + 0x11,0x20);
  puVar21 = local_20 + (uint)bVar25 * -2 + 1;
  puVar16 = local_38 + (uint)bVar25 * -2 + 1;
  *local_20 = *local_38;
  puVar22 = puVar21 + (uint)bVar25 * -2 + 1;
  puVar19 = puVar16 + (uint)bVar25 * -2 + 1;
  *puVar21 = *puVar16;
  *puVar22 = *puVar19;
  puVar22[(uint)bVar25 * -2 + 1] = puVar19[(uint)bVar25 * -2 + 1];
  *(undefined *)(puVar22 + (uint)bVar25 * -2 + 1 + (uint)bVar25 * -2 + 1) =
       *(undefined *)(puVar19 + (uint)bVar25 * -2 + 1 + (uint)bVar25 * -2 + 1);
  *(short *)(local_20 + 1) = *(short *)(local_38 + 1) + 1;
  *(short *)((int)local_20 + 6) = *(short *)((int)local_38 + 6) + 1;
  getmouse(&local_3c,&local_44,&local_48);
  local_4c = local_44;
  local_50 = local_48;
  if ((int)local_48 < 0x20) {
    pppppcVar10 = (char *****)0x0;
  }
  else {
    pppppcVar10 = local_48 + -8;
  }
  if ((int)local_44 < 0x1c) {
    ppppppcVar11 = (char ******)0x0;
  }
  else {
    ppppppcVar11 = local_44 + -7;
  }
  grabshape(local_20,ppppppcVar11,pppppcVar10);
  drawshape_trans(pointer_shapes,(byte *)((int)local_44 + -3),local_48);
  puVar18 = &stack0xfffffed8;
  pppppcVar10 = (char *****)event_queue_reset();
  dword_dd79c = 0;
  ppppppcVar11 = param_5;
  do {
    uVar26 = ZEXT48(pppppcVar10);
    do {
      *(undefined4 *)(puVar18 + -4) = 0x3f13f;
      uVar26 = event_queue_pop((int)uVar26,(int)(uVar26 >> 0x20),ppppppcVar11);
      iVar14 = (int)uVar26;
      if (iVar14 != 0) {
        ppppppcVar11 = &local_50;
        *(undefined4 *)(puVar18 + -4) = 0x3f151;
        uVar12 = (*ui_poll_callback)();
        uVar26 = CONCAT44(uVar12,uVar12);
        iVar14 = extraout_ECX;
      }
    } while ((iVar14 != 0) && ((uVar26 & 0x200000000) == 0));
    if ((uVar26 & 0x200000000) == 0) {
      if ((local_4c != local_44) || (pppppcVar10 = local_50, local_50 != local_48)) {
        if ((int)local_48 < 0x20) {
          pppppcVar10 = (char *****)0x0;
        }
        else {
          pppppcVar10 = local_48 + -8;
        }
        *(char ******)(puVar18 + -4) = pppppcVar10;
        if ((int)local_44 < 0x1c) {
          ppppppcVar11 = (char ******)0x0;
        }
        else {
          ppppppcVar11 = local_44 + -7;
        }
        *(char *******)(puVar18 + -8) = ppppppcVar11;
        *(undefined4 **)(puVar18 + -0xc) = local_20;
        *(undefined4 *)(puVar18 + -0x10) = 0x3f1a2;
        drawshape();
        ppppppcVar11 = local_4c;
        if ((int)local_50 < 0x20) {
          pppppcVar10 = (char *****)0x0;
        }
        else {
          pppppcVar10 = local_50 + -8;
        }
        *(char ******)(puVar18 + -4) = pppppcVar10;
        if ((int)local_4c < 0x1c) {
          ppppppcVar13 = (char ******)0x0;
        }
        else {
          ppppppcVar13 = local_4c + -7;
        }
        *(char *******)(puVar18 + -8) = ppppppcVar13;
        *(undefined4 **)(puVar18 + -0xc) = local_20;
        *(undefined4 *)(puVar18 + -0x10) = 0x3f1ce;
        grabshape();
        if (((((int)local_80[4][3] < (int)local_50) && (0xbe < (int)local_4c)) &&
            ((int)local_4c < 0x1c0)) &&
           ((dword_de260 != (char *****)0xffffffff && ((&dword_ddd84)[(int)dword_de260] != -1)))) {
          if (local_6c != 0) {
            *(int **)(puVar18 + -4) = &local_58;
            *(char ********)(puVar18 + -8) = &local_54;
            *(int **)(puVar18 + -0xc) = aiStack_c8 + 2;
            *(char ********)(puVar18 + -0x10) = local_80;
            ppppppcVar11 = (char ******)(local_80 + 4);
            *(undefined4 *)(puVar18 + -0x14) = 0x3f23e;
            iVar14 = hit_test_menus(local_4c,local_50,ppppppcVar11,local_10);
            if (iVar14 != 0) goto LAB_0003fe92;
          }
          iVar14 = (&dword_ddd7c)[(int)dword_de260];
          *(undefined4 *)(puVar18 + -4) = 0x3f267;
          memcpy(&unk_d12c8,(void *)(iVar14 + 0x90),0x30);
          ppppppcVar11 = (char ******)
                         (uint)(byte)(&unk_d1238)
                                     [(byte)(&unk_d11bc)[(int)param_3[(int)dword_de260] * 4]];
          uVar1 = (&unk_ddd8d)[(&dword_ddd84)[(int)dword_de260] * 0x16 + (int)dword_de260 * 0x268];
          *(undefined4 *)(puVar18 + -4) = 0x3f2c9;
          jersey_number_bitmap(&unk_d1238,uVar1,ppppppcVar11,byte_d12de);
          *(undefined1 **)(puVar18 + -4) = &unk_d1238;
          *(undefined4 *)(puVar18 + -8) = 0x3f2d3;
          setremaptable();
          *(char ******)(puVar18 + -4) = local_50 + -8;
          *(char *******)(puVar18 + -8) = local_4c + -7;
          *(undefined4 *)(puVar18 + -0xc) = param_1;
          *(undefined4 *)(puVar18 + -0x10) = 0x3f2f0;
          drawshape_trans();
        }
        goto LAB_0003fe92;
      }
    }
    else {
      *(int **)(puVar18 + -4) = &local_58;
      *(char ********)(puVar18 + -8) = &local_54;
      *(int **)(puVar18 + -0xc) = aiStack_c8 + 2;
      *(char ********)(puVar18 + -0x10) = local_80;
      *(undefined4 *)(puVar18 + -0x14) = 0x3f319;
      iVar14 = hit_test_menus(local_4c,local_50,local_80 + 4,local_10);
      pppppcVar10 = local_48 + -8;
      if (iVar14 == 0) {
        if ((int)local_48 < 0x20) {
          pppppcVar10 = (char *****)0x0;
        }
        *(char ******)(puVar18 + -4) = pppppcVar10;
        if ((int)local_44 < 0x1c) {
          ppppppcVar11 = (char ******)0x0;
        }
        else {
          ppppppcVar11 = local_44 + -7;
        }
        *(char *******)(puVar18 + -8) = ppppppcVar11;
        *(undefined4 **)(puVar18 + -0xc) = local_20;
        *(undefined4 *)(puVar18 + -0x10) = 0x3f7e4;
        drawshape();
        *(int **)(puVar18 + -4) = &local_40;
        *(undefined4 *)(puVar18 + -8) = 0x3f800;
        pppppcVar10 = (char *****)line_editor_hit_test(local_4c,local_50);
        ppppppcVar11 = (char ******)&dword_ddd74;
        if (pppppcVar10 != (char *****)0x0) {
          for (local_3c = param_8; ppppppcVar11 = local_3c, pppppcVar9 = dword_de260,
              -1 < (int)local_3c; local_3c = (char ******)((int)local_3c + -1)) {
            iVar14 = local_a0[(int)local_3c];
            if (iVar14 != 0) {
              *(int *)(puVar18 + -4) = aiStack_c8[(int)local_3c * 2 + 3];
              *(int *)(puVar18 + -8) = aiStack_c8[(int)local_3c * 2 + 2];
              *(int *)(puVar18 + -0xc) = iVar14;
              *(undefined4 *)(puVar18 + -0x10) = 0x3f830;
              drawshape();
              ppppppcVar11 = local_3c;
              aiStack_c8[(int)local_3c * 2 + 3] = 0;
              aiStack_c8[(int)ppppppcVar11 * 2 + 2] = 0;
              *(int *)(puVar18 + -4) = local_a0[(int)ppppppcVar11];
              *(undefined4 *)(puVar18 + -8) = 0x3f84a;
              freemem();
            }
          }
          local_10 = (char ******)0x0;
          local_64 = 0;
          local_68 = 0;
          local_6c = 0;
          local_a0[2] = 0;
          local_a0[1] = 0;
          local_a0[0] = 0;
          local_a0[7] = 0;
          local_a0[6] = 0;
          local_a0[5] = 0;
          local_80[3] = (char ******)0x0;
          local_80[2] = (char ******)0x0;
          local_80[1] = (char ******)0x0;
          if (((int)(&dword_ddd74)[(int)dword_de260] < 100) &&
             (((&dword_ddd84)[(int)dword_de260] != -1 || (local_40 != 0)))) {
            iVar14 = 0;
            local_14 = (char ******)(&dword_ddd74)[(int)dword_de260];
            pppppcVar10 = (char *****)(&dword_ddd84)[(int)dword_de260];
            local_34 = pppppcVar10;
            pbVar20 = (byte *)((int)unaff_ECX + (int)local_14);
            if (local_40 == 0) {
              iVar4 = (int)local_14 * 0x16;
              local_30 = (int)pppppcVar10 * 0x16;
              pppppcVar10 = (char *****)((int)dword_de260 * 0x268 + local_30);
              ppppppcVar11 = local_14;
              if ((int)local_14 < 2) {
                if ((dword_de260 == (char *****)0x0) &&
                   (ppppppcVar11 = (char ******)(uint)*(byte *)unaff_ECX,
                   *(byte *)unaff_ECX != (&unk_ddd8e)[(int)pppppcVar10])) {
                  ppppppcVar11 = (char ******)(uint)*(byte *)((int)unaff_ECX + 1);
                  if (*(byte *)((int)unaff_ECX + 1) != (&unk_ddd8e)[(int)pppppcVar10]) {
                    *pbVar20 = (&unk_ddd8e)[(int)pppppcVar10];
                    iVar14 = (int)dword_de260 * 0x268 + local_30;
                    pcVar24 = acStack_118 + (uint)bVar25 * -8 + iVar4 + 4;
                    puVar16 = (undefined4 *)(&DAT_000ddd90 + (uint)bVar25 * -8 + iVar14);
                    *(undefined4 *)(acStack_118 + iVar4) = *(undefined4 *)(&unk_ddd8c + iVar14);
                    pcVar23 = pcVar24 + ((uint)bVar25 * -2 + 1) * 4;
                    puVar19 = puVar16 + (uint)bVar25 * -2 + 1;
                    *(undefined4 *)pcVar24 = *puVar16;
                    pcVar24 = pcVar23 + ((uint)bVar25 * -2 + 1) * 4;
                    puVar16 = puVar19 + (uint)bVar25 * -2 + 1;
                    *(undefined4 *)pcVar23 = *puVar19;
                    *(undefined4 *)pcVar24 = *puVar16;
                    *(undefined4 *)(pcVar24 + ((uint)bVar25 * -2 + 1) * 4) =
                         puVar16[(uint)bVar25 * -2 + 1];
                    *(undefined2 *)
                     (pcVar24 + ((uint)bVar25 * -2 + 1) * 4 + ((uint)bVar25 * -2 + 1) * 4) =
                         *(undefined2 *)(puVar16 + (uint)bVar25 * -2 + 1 + (uint)bVar25 * -2 + 1);
                    if (((acStack_118[iVar4] == 'G') &&
                        (acStack_118[(int)((int)local_14 + 2) * 0x16] != 'G')) ||
                       ((acStack_118[(int)local_14 * 0x16] != 'G' &&
                        (acStack_118[(int)((int)local_14 + 2) * 0x16] == 'G')))) {
                      ((byte *)((int)unaff_ECX + (int)local_14))[2] = 0xff;
                      acStack_118[(int)((int)local_14 + 2) * 0x16 + 1] = -1;
                    }
LAB_0003fb7b:
                    *(undefined4 *)(puVar18 + -4) = 0x41;
                    *(undefined4 *)(puVar18 + -8) = 0x40;
                    *(undefined4 *)(puVar18 + -0xc) = 0x3fb84;
                    settextpos();
                    *(undefined4 *)(puVar18 + -4) = 0x3fb91;
                    line_editor_draw_entry(dword_de260);
                    pppppcVar10 = dword_de260;
                    (&dword_ddd84)[(int)dword_de260] = 0xffffffff;
                    dword_de260 = (char *****)0xffffffff;
                    iVar14 = -1;
                    ppppppcVar11 = (char ******)0xffffffff;
                  }
                }
              }
              else if (((int)local_14 < 4) && (dword_de260 == (char *****)0x1)) {
                bVar2 = (&unk_ddd8e)[(int)pppppcVar10];
                ppppppcVar11 = (char ******)(uint)*(byte *)((int)unaff_ECX + 2);
                if ((*(byte *)((int)unaff_ECX + 2) != bVar2) &&
                   (ppppppcVar11 = unaff_ECX, bVar2 != *(byte *)((int)unaff_ECX + 3))) {
                  *pbVar20 = bVar2;
                  iVar14 = (int)dword_de260 * 0x268 + local_30;
                  pcVar24 = acStack_118 + (uint)bVar25 * -8 + iVar4 + 4;
                  puVar16 = (undefined4 *)(&DAT_000ddd90 + (uint)bVar25 * -8 + iVar14);
                  *(undefined4 *)(acStack_118 + iVar4) = *(undefined4 *)(&unk_ddd8c + iVar14);
                  pcVar23 = pcVar24 + ((uint)bVar25 * -2 + 1) * 4;
                  puVar19 = puVar16 + (uint)bVar25 * -2 + 1;
                  *(undefined4 *)pcVar24 = *puVar16;
                  pcVar24 = pcVar23 + ((uint)bVar25 * -2 + 1) * 4;
                  puVar16 = puVar19 + (uint)bVar25 * -2 + 1;
                  *(undefined4 *)pcVar23 = *puVar19;
                  *(undefined4 *)pcVar24 = *puVar16;
                  *(undefined4 *)(pcVar24 + ((uint)bVar25 * -2 + 1) * 4) =
                       puVar16[(uint)bVar25 * -2 + 1];
                  *(undefined2 *)
                   (pcVar24 + ((uint)bVar25 * -2 + 1) * 4 + ((uint)bVar25 * -2 + 1) * 4) =
                       *(undefined2 *)(puVar16 + (uint)bVar25 * -2 + 1 + (uint)bVar25 * -2 + 1);
                  if (((acStack_118[iVar4] == 'G') &&
                      (acStack_118[(int)((int)local_14 + -2) * 0x16] != 'G')) ||
                     ((acStack_118[(int)local_14 * 0x16] != 'G' &&
                      (acStack_118[(int)((int)local_14 + -2) * 0x16] == 'G')))) {
                    ((byte *)((int)unaff_ECX + (int)local_14))[-2] = 0xff;
                    acStack_118[(int)((int)local_14 + -2) * 0x16 + 1] = -1;
                  }
                  goto LAB_0003fb7b;
                }
              }
            }
            else if (*pbVar20 == 0xff) {
              dword_de260 = (char *****)0xffffffff;
            }
            else {
              if ((pppppcVar10 != (char *****)0xffffffff) &&
                 ((char *****)(uint)*pbVar20 != pppppcVar10)) {
                *(undefined4 *)(puVar18 + -4) = 0x41;
                *(undefined4 *)(puVar18 + -8) = 0x40;
                *(undefined4 *)(puVar18 + -0xc) = 0x3f8f9;
                settextpos();
                *(undefined4 *)(puVar18 + -4) = 0x3f906;
                line_editor_draw_entry(dword_de260);
              }
              pbVar20 = (byte *)((int)unaff_ECX + (int)local_14);
              bVar2 = *pbVar20;
              *(undefined4 *)(puVar18 + -4) = 0x3f91d;
              uVar12 = line_editor_find_number(dword_de260,bVar2);
              (&dword_ddd84)[(int)dword_de260] = uVar12;
              *(undefined4 *)(puVar18 + -4) = 0x41;
              *(undefined4 *)(puVar18 + -8) = 0x42;
              *(undefined4 *)(puVar18 + -0xc) = 0x3f934;
              settextpos();
              *(undefined4 *)(puVar18 + -4) = 0x3f941;
              line_editor_draw_entry(dword_de260);
              *pbVar20 = 0xff;
              pppppcVar10 = (char *****)((int)local_14 * 0xb);
              acStack_118[(int)local_14 * 0x16 + 1] = -1;
              iVar14 = -1;
            }
            if (iVar14 != 0) {
              local_3c = (char ******)0x0;
              do {
                iVar14 = (&dword_ddd7c)[(int)local_3c >> 1];
                *(undefined4 *)(puVar18 + -4) = 0x3fbde;
                memcpy(&unk_d12c8,(void *)(iVar14 + 0x90),0x30);
                uVar1 = (&unk_d1238)[(byte)(&unk_d11bc)[(int)param_3[(int)local_3c >> 1] * 4]];
                cVar3 = acStack_118[(int)local_3c * 0x16 + 1];
                *(undefined4 *)(puVar18 + -4) = 0x3fc30;
                jersey_number_bitmap(&unk_d1238,cVar3,uVar1,byte_d12de);
                *(undefined1 **)(puVar18 + -4) = &unk_d1238;
                *(undefined4 *)(puVar18 + -8) = 0x3fc3a;
                setremaptable();
                ppppppcVar11 = (char ******)(&unk_c8b80)[(int)local_3c * 2];
                *(char *******)(puVar18 + -4) = ppppppcVar11;
                *(undefined4 *)(puVar18 + -8) = (&unk_c8b7c)[(int)local_3c * 2];
                *(undefined4 *)(puVar18 + -0xc) = param_1;
                *(undefined4 *)(puVar18 + -0x10) = 0x3fc56;
                pppppcVar10 = (char *****)drawshape2_trans();
                local_3c = (char ******)((int)local_3c + 1);
              } while ((int)local_3c < 4);
            }
          }
          else {
            pppppcVar10 = (char *****)((int)dword_de260 * 4);
            if (99 < (int)(&dword_ddd74)[(int)dword_de260]) {
              iVar14 = (&dword_ddd74)[(int)dword_de260] + -100;
              (&dword_ddd74)[(int)dword_de260] = iVar14;
              ppppppcVar11 = (char ******)(iVar14 * 0x16);
              if (*(byte *)((int)ppppppcVar11 + (int)(&unk_ddd8c + (int)dword_de260 * 0x268)) != 0)
              {
                if ((&dword_ddd84)[(int)pppppcVar9] == (&dword_ddd74)[(int)pppppcVar9]) {
                  *(undefined4 *)(puVar18 + -4) = 0x41;
                  *(undefined4 *)(puVar18 + -8) = 0x40;
                  *(undefined4 *)(puVar18 + -0xc) = 0x3fccc;
                  settextpos();
                  *(undefined4 *)(puVar18 + -4) = 0x3fcd9;
                  line_editor_draw_entry(dword_de260);
                  pppppcVar10 = dword_de260;
                  (&dword_ddd84)[(int)dword_de260] = 0xffffffff;
                  dword_de260 = (char *****)0xffffffff;
                }
                else {
                  if ((&dword_ddd84)[(int)pppppcVar9] != -1) {
                    *(undefined4 *)(puVar18 + -4) = 0x41;
                    *(undefined4 *)(puVar18 + -8) = 0x40;
                    *(undefined4 *)(puVar18 + -0xc) = 0x3fd00;
                    settextpos();
                    *(undefined4 *)(puVar18 + -4) = 0x3fd0d;
                    line_editor_draw_entry(dword_de260);
                  }
                  (&dword_ddd84)[(int)dword_de260] = (&dword_ddd74)[(int)dword_de260];
                  *(undefined4 *)(puVar18 + -4) = 0x41;
                  *(undefined4 *)(puVar18 + -8) = 0x42;
                  *(undefined4 *)(puVar18 + -0xc) = 0x3fd29;
                  settextpos();
                  *(undefined4 *)(puVar18 + -4) = 0x3fd36;
                  pppppcVar10 = (char *****)line_editor_draw_entry(dword_de260);
                }
              }
            }
          }
        }
      }
      else {
        if (local_80[(int)(local_54 + 1)][local_58 * 8 + 5] == (char *****)0x0) {
          if (local_80[(int)(local_54 + 1)][local_58 * 8 + 6] == (char *****)0x0) {
            if ((int)local_48 < 0x20) {
              pppppcVar10 = (char *****)0x0;
            }
            *(char ******)(puVar18 + -4) = pppppcVar10;
            if ((int)local_44 < 0x1c) {
              ppppppcVar11 = (char ******)0x0;
            }
            else {
              ppppppcVar11 = local_44 + -7;
            }
            *(char *******)(puVar18 + -8) = ppppppcVar11;
            *(undefined4 **)(puVar18 + -0xc) = local_20;
            *(undefined4 *)(puVar18 + -0x10) = 0x3f780;
            drawshape();
            *(undefined4 *)(puVar18 + -4) = local_2c;
            *(undefined4 *)(puVar18 + -8) = local_28;
            iVar14 = aiStack_c8[(int)local_54 * 2 + 3];
            iVar4 = aiStack_c8[(int)local_54 * 2 + 2];
            iVar5 = local_a0[(int)(local_54 + 1)];
            pppppcVar10 = (char *****)local_80[(int)(local_54 + 1)];
            *(undefined4 *)(puVar18 + -0xc) = 0x3f7ab;
            menu_item_draw_normal(pppppcVar10 + iVar5 * 8,iVar4,iVar14,local_24);
            ppppppcVar13 = local_54;
            local_a0[(int)(local_54 + 1)] = local_58;
            *(undefined4 *)(puVar18 + -4) = local_2c;
            *(undefined4 *)(puVar18 + -8) = local_28;
            goto LAB_0003f4e9;
          }
          if ((int)local_48 < 0x20) {
            pppppcVar10 = (char *****)0x0;
          }
          *(char ******)(puVar18 + -4) = pppppcVar10;
          if ((int)local_44 < 0x1c) {
            ppppppcVar11 = (char ******)0x0;
          }
          else {
            ppppppcVar11 = local_44 + -7;
          }
          *(char *******)(puVar18 + -8) = ppppppcVar11;
          *(undefined4 **)(puVar18 + -0xc) = local_20;
          *(undefined4 *)(puVar18 + -0x10) = 0x3f53b;
          drawshape();
          if (local_10 != local_54) {
            for (local_3c = local_10; ppppppcVar11 = local_3c, (int)local_54 < (int)local_3c;
                local_3c = (char ******)((int)local_3c + -1)) {
              local_a0[(int)(local_3c + 1)] = 0;
              iVar14 = local_a0[(int)ppppppcVar11];
              if (iVar14 != 0) {
                *(int *)(puVar18 + -4) = aiStack_c8[(int)local_3c * 2 + 3];
                *(int *)(puVar18 + -8) = aiStack_c8[(int)local_3c * 2 + 2];
                *(int *)(puVar18 + -0xc) = iVar14;
                *(undefined4 *)(puVar18 + -0x10) = 0x3f56f;
                drawshape();
                ppppppcVar11 = local_3c;
                aiStack_c8[(int)local_3c * 2 + 3] = 0;
                aiStack_c8[(int)ppppppcVar11 * 2 + 2] = 0;
                *(int *)(puVar18 + -4) = local_a0[(int)ppppppcVar11];
                *(undefined4 *)(puVar18 + -8) = 0x3f589;
                freemem();
                ppppppcVar11 = local_3c;
                local_a0[(int)local_3c] = 0;
                local_80[(int)(ppppppcVar11 + 1)] = (char ******)0x0;
                local_80[(int)ppppppcVar11] = (char ******)0x0;
              }
            }
            local_10 = local_54;
          }
          ppppppcVar11 = local_10;
          uVar12 = local_28;
          *(undefined4 *)(puVar18 + -4) = local_2c;
          *(undefined4 *)(puVar18 + -8) = local_28;
          iVar14 = aiStack_c8[(int)local_10 * 2 + 3];
          iVar4 = aiStack_c8[(int)local_10 * 2 + 2];
          iVar5 = local_a0[(int)(local_10 + 1)];
          pppppcVar10 = (char *****)local_80[(int)(local_10 + 1)];
          *(undefined4 *)(puVar18 + -0xc) = 0x3f5d5;
          menu_item_draw_normal(pppppcVar10 + iVar5 * 8,iVar4,iVar14,local_24);
          local_a0[(int)(ppppppcVar11 + 1)] = local_58;
          *(undefined4 *)(puVar18 + -4) = local_2c;
          *(undefined4 *)(puVar18 + -8) = uVar12;
          iVar14 = aiStack_c8[(int)ppppppcVar11 * 2 + 3];
          iVar4 = aiStack_c8[(int)ppppppcVar11 * 2 + 2];
          pppppcVar10 = (char *****)local_80[(int)(ppppppcVar11 + 1)];
          *(undefined4 *)(puVar18 + -0xc) = 0x3f5fd;
          menu_item_draw_selected(pppppcVar10 + local_58 * 8,iVar4,iVar14,local_24);
          ppppppcVar13 = local_54;
          iVar14 = local_58;
          ppppppcVar11 = (char ******)((int)ppppppcVar11 + 1);
          local_10 = ppppppcVar11;
          local_80[(int)(ppppppcVar11 + 1)] =
               (char ******)local_80[(int)(local_54 + 1)][local_58 * 8 + 6];
          pppppcVar10 = (char *****)(local_80[(int)(ppppppcVar13 + 1)] + iVar14 * 8);
          local_80[(int)ppppppcVar11] = (char ******)pppppcVar10[7];
          if (ppppppcVar11 == (char ******)0x1) {
            ppppcVar15 = *pppppcVar10;
          }
          else {
            ppppcVar15 = pppppcVar10[2];
          }
          aiStack_c8[(int)local_10 * 2 + 2] = (int)ppppcVar15 + aiStack_c8[(int)local_10 * 2];
          if (local_10 == (char ******)0x1) {
            ppppcVar15 = (char ****)local_80[(int)(local_54 + 1)][local_58 * 8 + 3];
          }
          else {
            ppppcVar15 = (char ****)local_80[(int)(local_54 + 1)][local_58 * 8 + 1];
          }
          local_1c = (int)local_10 * 8;
          aiStack_c8[(int)local_10 * 2 + 3] = (int)ppppcVar15 + aiStack_c8[(int)local_10 * 2 + 1];
          local_18 = (int)local_10 * 4;
          pppppcVar10 = (char *****)local_80[(int)(local_10 + 1)];
          local_60 = (int)pppppcVar10[(int)local_80[(int)local_10] * 8 + -6] +
                     (1 - (int)*pppppcVar10);
          local_5c = (int)pppppcVar10[(int)local_80[(int)local_10] * 8 + -5] +
                     (1 - (int)pppppcVar10[1]);
          *(undefined4 *)(puVar18 + -4) = 0x20;
          *(int *)(puVar18 + -8) = local_60 * 4 * local_5c + 0x11;
          *(char **)(puVar18 + -0xc) = aMenubuff_c1a0c;
          *(undefined4 *)(puVar18 + -0x10) = 0x3f6b7;
          puVar16 = (undefined4 *)allocmem();
          iVar14 = local_18;
          *(undefined4 **)((int)local_a0 + local_18) = puVar16;
          puVar21 = puVar16 + (uint)bVar25 * -2 + 1;
          puVar19 = pointer_shapes + (uint)bVar25 * -2 + 1;
          *puVar16 = *pointer_shapes;
          puVar22 = puVar21 + (uint)bVar25 * -2 + 1;
          puVar16 = puVar19 + (uint)bVar25 * -2 + 1;
          *puVar21 = *puVar19;
          *puVar22 = *puVar16;
          puVar22[(uint)bVar25 * -2 + 1] = puVar16[(uint)bVar25 * -2 + 1];
          *(undefined *)(puVar22 + (uint)bVar25 * -2 + 1 + (uint)bVar25 * -2 + 1) =
               *(undefined *)(puVar16 + (uint)bVar25 * -2 + 1 + (uint)bVar25 * -2 + 1);
          *(short *)(*(int *)((int)local_a0 + iVar14) + 4) = (short)local_60;
          *(short *)(*(int *)((int)local_a0 + local_18) + 6) = (short)local_5c;
          *(undefined4 *)(puVar18 + -4) = *(undefined4 *)((int)aiStack_c8 + local_1c + 0xc);
          *(undefined4 *)(puVar18 + -8) = *(undefined4 *)((int)aiStack_c8 + local_1c + 8);
          *(undefined4 *)(puVar18 + -0xc) = *(undefined4 *)((int)local_a0 + local_18);
          *(undefined4 *)(puVar18 + -0x10) = 0x3f701;
          grabshape();
          uVar17 = local_24;
          *(undefined4 *)(puVar18 + -4) = local_2c;
          *(undefined4 *)(puVar18 + -8) = local_28;
          *(undefined4 *)(puVar18 + -0xc) = local_24;
          uVar12 = *(undefined4 *)((int)aiStack_c8 + local_1c + 0xc);
          uVar6 = *(undefined4 *)((int)aiStack_c8 + local_1c + 8);
          uVar7 = *(undefined4 *)((int)local_80 + local_18);
          uVar8 = *(undefined4 *)((int)local_80 + local_18 + 0x10);
          *(undefined4 *)(puVar18 + -0x10) = 0x3f731;
          draw_menu(uVar8,uVar7,uVar6,uVar12);
          *(undefined4 *)((int)local_a0 + local_18 + 0x10) = 0;
          *(undefined4 *)(puVar18 + -4) = local_2c;
          *(undefined4 *)(puVar18 + -8) = local_28;
          ppppppcVar11 = *(char *******)((int)aiStack_c8 + local_1c + 0xc);
          iVar14 = *(int *)((int)aiStack_c8 + local_1c + 8);
          pppppcVar10 = *(char ******)((int)local_80 + local_18 + 0x10);
        }
        else {
          if (local_58 == local_a0[(int)(local_54 + 1)]) {
            if ((int)local_48 < 0x20) {
              pppppcVar10 = (char *****)0x0;
            }
            *(char ******)(puVar18 + -4) = pppppcVar10;
            if ((int)local_44 < 0x1c) {
              ppppppcVar11 = (char ******)0x0;
            }
            else {
              ppppppcVar11 = local_44 + -7;
            }
            *(char *******)(puVar18 + -8) = ppppppcVar11;
            *(undefined4 **)(puVar18 + -0xc) = local_20;
            *(undefined4 *)(puVar18 + -0x10) = 0x3f372;
            drawshape();
            ppppppcVar11 = param_3;
            for (local_3c = param_8; -1 < (int)local_3c;
                local_3c = (char ******)((int)local_3c + -1)) {
              if (local_a0[(int)local_3c] != 0) {
                *(int *)(puVar18 + -4) = aiStack_c8[(int)local_3c * 2 + 3];
                *(int *)(puVar18 + -8) = aiStack_c8[(int)local_3c * 2 + 2];
                *(int *)(puVar18 + -0xc) = local_a0[(int)local_3c];
                *(undefined4 *)(puVar18 + -0x10) = 0x3f3a2;
                drawshape();
                ppppppcVar13 = local_3c;
                aiStack_c8[(int)local_3c * 2 + 3] = 0;
                aiStack_c8[(int)ppppppcVar13 * 2 + 2] = 0;
                *(int *)(puVar18 + -4) = local_a0[(int)ppppppcVar13];
                *(undefined4 *)(puVar18 + -8) = 0x3f3bc;
                freemem();
              }
            }
            local_10 = (char ******)0x0;
            pppppcVar10 = (char *****)local_80[(int)(local_54 + 1)];
            *(char *******)(puVar18 + -4) = unaff_ECX;
            *(char *******)(puVar18 + -8) = param_8;
            *(char *******)(puVar18 + -0xc) = param_5;
            *(undefined4 *)(puVar18 + -0x10) = param_7;
            *(undefined4 *)(puVar18 + -0x14) = param_1;
            ppppcVar15 = pppppcVar10[local_58 * 8 + 5];
            *(undefined4 *)(puVar18 + -0x18) = 0x3f421;
            param_3 = ppppppcVar11;
            iVar14 = (*(code *)ppppcVar15)();
            local_64 = 0;
            local_68 = 0;
            local_6c = 0;
            local_a0[2] = 0;
            local_a0[1] = 0;
            local_a0[0] = 0;
            local_a0[7] = 0;
            local_a0[6] = 0;
            local_a0[5] = 0;
            local_80[3] = (char ******)0x0;
            local_80[2] = (char ******)0x0;
            local_80[1] = (char ******)0x0;
            if (iVar14 == 1) {
              *(undefined4 *)(puVar18 + -0x18) = 0x3f451;
              event_queue_reset();
              *(undefined4 **)(puVar18 + -0x18) = local_20;
              *(undefined4 *)(puVar18 + -0x1c) = 0x3f45a;
              freemem();
              return 0;
            }
            *(char ******)(puVar18 + -0x18) = local_48;
            *(char *******)(puVar18 + -0x1c) = local_44;
            *(undefined4 *)(puVar18 + -0x20) = 0x3f471;
            setmousepos();
            local_4c = local_44;
            local_50 = local_48;
            *(undefined4 *)(puVar18 + -0x18) = 0x3f485;
            pppppcVar10 = (char *****)event_queue_reset();
            puVar18 = puVar18 + -0x14;
            goto LAB_0003fd36;
          }
          if ((int)local_48 < 0x20) {
            pppppcVar10 = (char *****)0x0;
          }
          *(char ******)(puVar18 + -4) = pppppcVar10;
          if ((int)local_44 < 0x1c) {
            ppppppcVar11 = (char ******)0x0;
          }
          else {
            ppppppcVar11 = local_44 + -7;
          }
          *(char *******)(puVar18 + -8) = ppppppcVar11;
          *(undefined4 **)(puVar18 + -0xc) = local_20;
          *(undefined4 *)(puVar18 + -0x10) = 0x3f4ac;
          drawshape();
          *(undefined4 *)(puVar18 + -4) = local_2c;
          *(undefined4 *)(puVar18 + -8) = local_28;
          iVar14 = aiStack_c8[(int)local_54 * 2 + 3];
          iVar4 = aiStack_c8[(int)local_54 * 2 + 2];
          iVar5 = local_a0[(int)(local_54 + 1)];
          pppppcVar10 = (char *****)local_80[(int)(local_54 + 1)];
          *(undefined4 *)(puVar18 + -0xc) = 0x3f4d7;
          menu_item_draw_normal(pppppcVar10 + iVar5 * 8,iVar4,iVar14,local_24);
          ppppppcVar13 = local_54;
          local_a0[(int)(local_54 + 1)] = local_58;
          *(undefined4 *)(puVar18 + -4) = local_2c;
          *(undefined4 *)(puVar18 + -8) = local_28;
LAB_0003f4e9:
          ppppppcVar11 = (char ******)aiStack_c8[(int)ppppppcVar13 * 2 + 3];
          iVar14 = aiStack_c8[(int)ppppppcVar13 * 2 + 2];
          pppppcVar10 = (char *****)
                        (local_80[(int)(ppppppcVar13 + 1)] + local_a0[(int)(ppppppcVar13 + 1)] * 8);
          uVar17 = local_24;
        }
        *(undefined4 *)(puVar18 + -0xc) = 0x3f50a;
        pppppcVar10 = (char *****)menu_item_draw_selected(pppppcVar10,iVar14,ppppppcVar11,uVar17);
      }
LAB_0003fd36:
      if (dword_dd79c == 0) {
        if ((int)local_50 < 0x20) {
          pppppcVar10 = (char *****)0x0;
        }
        else {
          pppppcVar10 = local_50 + -8;
        }
        *(char ******)(puVar18 + -4) = pppppcVar10;
        if ((int)local_4c < 0x1c) {
          ppppppcVar13 = (char ******)0x0;
        }
        else {
          ppppppcVar13 = local_4c + -7;
        }
        *(char *******)(puVar18 + -8) = ppppppcVar13;
        *(undefined4 **)(puVar18 + -0xc) = local_20;
        *(undefined4 *)(puVar18 + -0x10) = 0x3fd6c;
        grabshape();
        if (((((int)local_80[4][3] < (int)local_50) && (0xbe < (int)local_4c)) &&
            ((int)local_4c < 0x1c0)) &&
           ((dword_de260 != (char *****)0xffffffff && ((&dword_ddd84)[(int)dword_de260] != -1)))) {
          if (local_6c != 0) {
            *(int **)(puVar18 + -4) = &local_58;
            *(char ********)(puVar18 + -8) = &local_54;
            *(int **)(puVar18 + -0xc) = aiStack_c8 + 2;
            *(char ********)(puVar18 + -0x10) = local_80;
            ppppppcVar11 = (char ******)(local_80 + 4);
            *(undefined4 *)(puVar18 + -0x14) = 0x3fddd;
            iVar14 = hit_test_menus(local_4c,local_50,ppppppcVar11,local_10);
            if (iVar14 != 0) goto LAB_0003fe92;
          }
          iVar14 = (&dword_ddd7c)[(int)dword_de260];
          *(undefined4 *)(puVar18 + -4) = 0x3fe06;
          memcpy(&unk_d12c8,(void *)(iVar14 + 0x90),0x30);
          ppppppcVar11 = (char ******)
                         (uint)(byte)(&unk_d1238)
                                     [(byte)(&unk_d11bc)[(int)param_3[(int)dword_de260] * 4]];
          uVar1 = (&unk_ddd8d)[(&dword_ddd84)[(int)dword_de260] * 0x16 + (int)dword_de260 * 0x268];
          *(undefined4 *)(puVar18 + -4) = 0x3fe68;
          jersey_number_bitmap(&unk_d1238,uVar1,ppppppcVar11,byte_d12de);
          *(undefined1 **)(puVar18 + -4) = &unk_d1238;
          *(undefined4 *)(puVar18 + -8) = 0x3fe72;
          setremaptable();
          *(char ******)(puVar18 + -4) = local_50 + -8;
          *(char *******)(puVar18 + -8) = local_4c + -7;
          *(undefined4 *)(puVar18 + -0xc) = param_1;
          *(undefined4 *)(puVar18 + -0x10) = 0x3fe8f;
          drawshape_trans();
        }
LAB_0003fe92:
        *(char ******)(puVar18 + -4) = local_50;
        *(byte **)(puVar18 + -8) = (byte *)((int)local_4c + -3);
        *(undefined4 **)(puVar18 + -0xc) = pointer_shapes;
        *(undefined4 *)(puVar18 + -0x10) = 0x3fea9;
        drawshape_trans();
        local_44 = local_4c;
        local_48 = local_50;
        pppppcVar10 = local_50;
      }
    }
    if (dword_dd79c != 0) {
      *(undefined4 **)(puVar18 + -4) = local_20;
      *(undefined4 *)(puVar18 + -8) = 0x3fece;
      freemem();
      if (0 < dword_dd79c) {
        dword_dd79c = 0;
      }
      return dword_dd79c;
    }
  } while( true );
}


// ================================================================================================
// cmp_player_names @ 0x3fef0 [__watcall]
// ================================================================================================

int __watcall cmp_player_names(char *param_1,char *unaff_EDX)

{
  char cVar1;
  char cVar2;
  int iVar3;
  
  __CHK(8);
  cVar1 = *param_1;
  cVar2 = *unaff_EDX;
  if (cVar1 == cVar2) {
    if (*param_1 == '\0') {
      return 0;
    }
    iVar3 = strcmp(param_1 + 6,unaff_EDX + 6);
    return iVar3;
  }
  if ((cVar1 != '\0') &&
     (((cVar2 == '\0' || (cVar1 == 'L')) ||
      ((cVar2 != 'L' &&
       ((cVar1 == 'C' || ((cVar2 != 'C' && ((cVar1 == 'R' || ((cVar2 != 'R' && (cVar1 == 'D'))))))))
       )))))) {
    return -1;
  }
  return 1;
}


// ================================================================================================
// line_editor @ 0x3ff52 [__watcall]
// ================================================================================================

int __watcall
line_editor(undefined4 param_1,undefined4 *unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX,
           undefined4 param_5)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined *puVar4;
  undefined auStack_640 [744];
  undefined auStack_358 [744];
  undefined auStack_70 [64];
  undefined auStack_30 [16];
  undefined4 local_20;
  
  __CHK(0x654);
  setdefaultscreen();
  uVar1 = allocmem(&aTemp_c1964,0x300,0x20);
  getpalette(0,0x100,uVar1);
  fade_palette(1,uVar1,0x10);
  freemem(uVar1);
  setscreen(dword_de264);
  clearclip(0);
  getfontstate(auStack_70);
  puVar4 = install_path;
  if (byte_ed8b3 != '\x01') {
    puVar4 = (undefined *)0x0;
  }
  make_path(auStack_30,puVar4,&aS1_c1a15,&aVFN);
  uVar1 = loadfile(auStack_30,0);
  setfont(uVar1);
  puVar4 = install_path;
  if (byte_ed8b4 != '\x01') {
    puVar4 = (undefined *)0x0;
  }
  make_path(auStack_30,puVar4,aLineditp,0);
  uVar2 = loadshapes(auStack_30,0);
  local_20 = locateshape(uVar2,&aShrt);
  dword_ddd84 = 0xffffffff;
  dword_ddd88 = 0xffffffff;
  dword_ddd74 = 0xffffffff;
  dword_ddd78 = 0xffffffff;
  dword_de260 = 0xffffffff;
  iVar3 = line_editor_load_roster(param_1,*unaff_EDX,&unk_ddd8c,auStack_640);
  if (iVar3 == 0) {
    iVar3 = line_editor_load_roster(param_1,unaff_EDX[1],&unk_ddff4,auStack_358);
  }
  if (iVar3 == 0) {
    qsort(&unk_ddd8c,0x1c,0x16,cmp_player_names);
    qsort(&unk_ddff4,0x1c,0x16,cmp_player_names);
    iVar3 = line_editor_screen(local_20,auStack_640,unaff_EDX,unaff_EBX,unaff_ECX,uVar2,uVar1,
                               param_5);
  }
  freemem(uVar2);
  setfontstate(auStack_70);
  freemem(uVar1);
  return iVar3;
}


// ================================================================================================
// statistics_menu @ 0x40183 [__watcall]
// ================================================================================================

/* WARNING: Type propagation algorithm not settling */

void __watcall statistics_menu(void)

{
  int iVar1;
  undefined4 uVar2;
  undefined **ppuVar3;
  int iVar4;
  int iVar5;
  byte bVar6;
  undefined4 uStack_f0;
  undefined2 auStack_ec [24];
  undefined4 uStack_bc;
  undefined2 auStack_b8 [24];
  undefined local_88 [32];
  char local_68 [16];
  int local_58;
  int local_54;
  byte bStack_50;
  byte bStack_4f;
  int local_48 [3];
  int local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined2 uStack_20;
  undefined2 uStack_1e;
  short asStack_1c [2];
  
  bVar6 = 0;
  __CHK(0x108);
  local_38 = 0xffffffff;
  iVar4 = 0;
  local_48[1] = 0xffffffff;
  dword_de264 = windowdefp(0x280,0x1e0,0);
  local_34 = dword_d0b16;
  local_24 = dword_d0b1a;
  local_28 = dword_d0b1e;
  local_2c = dword_d0b22;
  local_30 = dword_d0b26;
  uStack_20 = (undefined2)dword_d0b2a;
  uStack_1e = (undefined2)((uint)dword_d0b2a >> 0x10);
  dword_d0b16 = 0x41;
  dword_d0b1a = 0x40;
  dword_d0b1e = 0x42;
  dword_d0b22 = 0x41;
  dword_d0b26 = 0x40;
  dword_d0b2a = 0x41;
  do {
    iVar5 = 0;
    if (iVar4 == 0) {
      iVar4 = load_league_info(&league_dir,&unk_dd7b4,&unk_ddd1d,&dword_dd7a8,&dword_ddac0,
                               &dword_dd7b0,&dword_dd7ac,&byte_ddd10);
    }
    if (iVar4 == 0) {
      set_dialog_colors(0xf9,0xfa,0xf8,0xfa,0xf7);
      getmouse(local_48,&local_3c,local_48 + 2);
      strcpy(local_68,&league_dir);
      iVar1 = _strcspn(local_68,&byte_c8164);
      local_68[iVar1] = '\0';
      if (dword_dd7ac == 0) {
        if (((byte)dword_dd7b0 & 4) == 0) {
          dword_c7dee = local_68;
          local_48[0] = message_dialog(0xffffffff,0xffffffff,&off_c7dea,4,&unk_c7e4e,2,&local_3c,
                                       local_48 + 2,0xffffffff);
          if (local_48[0] != 0) goto LAB_00040326;
          league_merge_check();
          iVar5 = -1;
        }
        else {
          make_path(local_88,&league_dir,off_c80e7,&aDB);
          iVar4 = db_open_check(local_88,&unk_ddac4,1);
        }
      }
      else {
        dword_c80a1 = local_68;
        message_dialog(0xffffffff,0xffffffff,&off_c809d,3,0,0,&local_3c,local_48 + 2,0xffffffff);
LAB_00040326:
        iVar4 = -1;
      }
    }
  } while (iVar5 != 0);
  if (iVar4 == 0) {
    make_path(local_88,&league_dir,off_c80ef,&aDB);
    iVar4 = file_open_rw(local_88,&local_38);
    if (iVar4 == 0) {
      iVar4 = file_read(local_38,asStack_1c,0,2);
    }
    if ((iVar4 == 0) && (asStack_1c[0] < 0x4ad)) {
      iVar4 = db_read_record2(local_38,&bStack_50,(int)asStack_1c[0]);
    }
    file_close(&local_38);
    if ((iVar4 == 0) &&
       ((((bStack_50 == 3 && (0x15 < bStack_4f)) || ((3 < bStack_50 && (bStack_50 < 10)))) ||
        (0x443 < asStack_1c[0])))) {
      getmouse(local_48,&local_3c,local_48 + 2);
      set_dialog_colors(0xf9,0xfa,0xf8,0xfa,0xf7);
      getmouse(local_48,&local_3c,local_48 + 2);
      message_dialog(0xffffffff,0xffffffff,&off_c8c26,2,0,0,&local_3c,local_48 + 2,0xffffffff);
      iVar4 = -1;
    }
    if (iVar4 == 0) {
      if (dword_ddac0 == 1) {
        set_dialog_colors(0xf9,0xfa,0xf8,0xfa,0xf7);
        getmouse(local_48,&local_3c,local_48 + 2);
        uVar2 = 2;
        ppuVar3 = &off_c753c;
      }
      else {
        team_info_screen(&league_dir,&dword_ddac0,&unk_ddac4,&unk_dd7b4,0x10,
                         aSelectTwoTeamsForTrading,&local_58);
        iVar4 = 0;
        if ((-1 < local_58) && (-1 < local_54)) {
          iVar5 = password_prompt(local_58,&unk_dd7b4);
          if (iVar5 == 0) {
            iVar5 = password_prompt(local_54,&unk_dd7b4);
          }
          if (iVar5 == 0) {
            uStack_f0 = aShow;
            auStack_ec[(uint)bVar6 * -4] = (&DAT_000c1a2a)[(uint)bVar6 * -4];
            strcat((char *)&uStack_f0,(&off_c54a9)[local_58]);
            strcat((char *)&uStack_f0,aStatistics);
            uStack_bc = aShow;
            auStack_b8[(uint)bVar6 * -4] = (&DAT_000c1a2a)[(uint)bVar6 * -4];
            dword_c87c8 = &uStack_f0;
            strcat((char *)&uStack_bc,(&off_c54a9)[local_54]);
            strcat((char *)&uStack_bc,aStatistics);
            dword_c87e8 = &uStack_bc;
            local_3c = textwidth(&uStack_f0);
            local_48[2] = textwidth(&uStack_bc);
            iVar5 = local_48[2];
            if (local_48[2] < local_3c) {
              iVar5 = local_3c;
            }
            dword_c87c0 = iVar5 + 6;
            dword_c87e0 = dword_c87c0;
            iVar5 = line_editor(&league_dir,&local_58,local_48 + 1,&unk_c885c,3);
          }
          if (iVar5 == 0) {
            iVar4 = team_edit_screen(&league_dir,&local_58,local_48 + 1);
          }
        }
        if (iVar4 == 0) goto LAB_0004072e;
        getmouse(local_48,&local_3c,local_48 + 2);
        uVar2 = 1;
        ppuVar3 = &off_c7847;
      }
      message_dialog(0xffffffff,0xffffffff,ppuVar3,uVar2,0,0,&local_3c,local_48 + 2,0xffffffff);
    }
  }
LAB_0004072e:
  dword_d0b16 = local_34;
  dword_d0b1a = local_24;
  dword_d0b1e = local_28;
  dword_d0b22 = local_2c;
  dword_d0b26 = local_30;
  dword_d0b2a = CONCAT22(uStack_1e,uStack_20);
  freemem(dword_de264);
  return;
}


// ================================================================================================
// set_team_palette_homepals @ 0x40792 [__watcall]
// ================================================================================================

void __watcall set_team_palette_homepals(int param_1,int unaff_EDX)

{
  int iVar1;
  int iVar2;
  undefined *puVar3;
  int iVar4;
  undefined auStack_1a0 [192];
  undefined auStack_e0 [192];
  undefined auStack_20 [16];
  
  __CHK(0x1b0);
  puVar3 = install_path;
  if (byte_ed86d != '\x01') {
    puVar3 = (undefined *)0x0;
  }
  make_path(auStack_20,puVar3,aHOMEPALS_c1a3c,&aBIN);
  iVar1 = loadfile(auStack_20,0);
  iVar4 = iVar1 + param_1 * 0x1c0;
  iVar2 = 0;
  do {
    auStack_1a0[iVar2] = *(undefined *)(iVar4 + iVar2);
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0xc0);
  iVar2 = 0;
  do {
    (&remap_home)[iVar2] = *(undefined *)(iVar4 + 0xc0 + iVar2);
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0x100);
  iVar2 = iVar1 + unaff_EDX * 0x1c0;
  iVar4 = 0;
  do {
    auStack_e0[iVar4] = *(undefined *)(iVar2 + iVar4);
    iVar4 = iVar4 + 1;
  } while (iVar4 < 0xc0);
  iVar4 = 0;
  iVar2 = iVar2 + 0xc0;
  do {
    (&remap_away)[iVar4] = *(undefined *)(iVar2 + iVar4);
    iVar4 = iVar4 + 1;
  } while (iVar4 < 0x90);
  iVar4 = 0x90;
  do {
    (&remap_away)[iVar4] = *(char *)(iVar2 + iVar4) + '@';
    iVar4 = iVar4 + 1;
  } while (iVar4 < 0x100);
  freemem(iVar1);
  auStack_e0[0xb1] = 0x18;
  auStack_e0[0xb2] = 0;
  auStack_e0[0xb3] = 0;
  auStack_e0[0xb4] = 0x2a;
  auStack_e0[0xb5] = 0;
  auStack_e0[0xb6] = 0;
  auStack_e0[0xb7] = 0x3b;
  auStack_e0[0xb8] = 0x12;
  auStack_e0[0xb9] = 0;
  auStack_e0[0xba] = 0x3b;
  auStack_e0[0xbb] = 0x3b;
  auStack_e0[0xbc] = 0x3b;
  setpalette(0x80,0x80,auStack_1a0);
  return;
}


// ================================================================================================
// select_human_team_dialog @ 0x408f5 [__watcall]
// ================================================================================================

void __watcall select_human_team_dialog(void)

{
  int iVar1;
  size_t sVar2;
  undefined4 uVar3;
  undefined *puVar4;
  int iVar5;
  undefined2 in_DS;
  undefined auStack_5c [32];
  char local_3c [16];
  undefined auStack_2c [4];
  undefined auStack_28 [4];
  int iStack_24;
  int iStack_20;
  undefined uStack_1c;
  undefined uStack_1b;
  undefined uStack_1a;
  
  __CHK(0x74);
  byte_de268 = '\0';
  iVar1 = return_zero_41337(&league_dir,2);
  do {
    iVar5 = 0;
    if (iVar1 == 0) {
      iVar1 = load_league_info(&league_dir,&unk_dd7b4,&unk_ddd1d,&dword_dd7a8,&dword_ddac0,
                               &dword_dd7b0,&dword_dd7ac,&byte_ddd10);
    }
    if (iVar1 == 0) {
      strcpy(local_3c,&league_dir);
      sVar2 = strcspn(local_3c,(char *)CONCAT22(0xc,in_DS));
      local_3c[sVar2] = '\0';
      getmouse(&iStack_24,auStack_28,auStack_2c);
      set_dialog_colors(0xf9,0xfa,0xf8,0xfa,0);
      if (dword_dd7ac == 0) {
        if ((dword_dd7b0 & 4) == 0) {
          dword_c7dee = local_3c;
          iStack_24 = message_dialog(0xffffffff,0xffffffff,&off_c7dea,4,&unk_c7e4e,2,auStack_28,
                                     auStack_2c,0xffffffff);
          if (iStack_24 != 0) goto LAB_00040a39;
          league_merge_check();
          iVar5 = -1;
        }
      }
      else {
        dword_c80a1 = local_3c;
        message_dialog(0xffffffff,0xffffffff,&off_c809d,3,0,0,auStack_28,auStack_2c,0xffffffff);
LAB_00040a39:
        iVar1 = -1;
      }
    }
    if (iVar5 == 0) {
      if (byte_de268 != '\0') {
        clearclip(0);
        puVar4 = install_path;
        if (byte_ed836 != '\x01') {
          puVar4 = (undefined *)0x0;
        }
        make_path(auStack_5c,puVar4,aEasndesk_c1a48,0);
        uVar3 = loadshapes(auStack_5c,0);
        iVar5 = locateshape(uVar3,&aPal_c1a51);
        setpalette(0,0x100,iVar5 + 0x10);
        freemem(uVar3);
        uStack_1c = 0x17;
        uStack_1b = 0x17;
        uStack_1a = 0x17;
        setpalette(0xf8,1,&uStack_1c);
        uStack_1c = 0x2a;
        uStack_1b = 0x2a;
        uStack_1a = 0x2a;
        setpalette(0xf9,1,&uStack_1c);
        uStack_1c = 0x3f;
        uStack_1b = 0x3f;
        uStack_1a = 0x3f;
        setpalette(0xfa,1,&uStack_1c);
      }
      iVar5 = dword_ddac0;
      if (iVar1 == 0) {
        if (dword_ddac0 < 0x1a) {
          make_path(auStack_5c,&league_dir,off_c80e7,&aDB);
          db_open_check(auStack_5c,&unk_ddac4,1);
          team_info_screen(&league_dir,&dword_ddac0,&unk_ddac4,&unk_dd7b4,2,
                           aSelectNewHumanControlled,&iStack_20);
          if (((-1 < iStack_20) && (iVar5 != dword_ddac0)) &&
             (iVar1 = pinfo_db_create(&league_dir,&unk_dd7b4,&unk_ddd1d,dword_dd7a8,dword_ddac0,
                                      dword_dd7b0,dword_dd7ac,&byte_ddd10), iVar1 == 0)) {
            league_player_sync(&league_dir,&unk_dd7b4,0xffffffff);
          }
        }
        else {
          getmouse(&iStack_24,auStack_28,auStack_2c);
          message_dialog(0xffffffff,0xffffffff,&off_c750f,1,0,0,auStack_28,auStack_2c,0xffffffff);
        }
      }
      return;
    }
  } while( true );
}


// ================================================================================================
// select_human_control_dialog @ 0x40c29 [__watcall]
// ================================================================================================

void __watcall select_human_control_dialog(void)

{
  int iVar1;
  size_t sVar2;
  undefined4 uVar3;
  undefined *puVar4;
  int iVar5;
  undefined2 in_DS;
  undefined local_5c [32];
  char local_3c [16];
  undefined auStack_2c [4];
  undefined auStack_28 [4];
  int iStack_24;
  int iStack_20;
  undefined uStack_1c;
  undefined uStack_1b;
  undefined uStack_1a;
  
  __CHK(0x74);
  byte_de268 = '\0';
  iVar1 = return_zero_41337(&league_dir,2);
  do {
    iVar5 = 0;
    if (iVar1 == 0) {
      iVar1 = load_league_info(&league_dir,&unk_dd7b4,&unk_ddd1d,&dword_dd7a8,&dword_ddac0,
                               &dword_dd7b0,&dword_dd7ac,&byte_ddd10);
    }
    if (iVar1 == 0) {
      strcpy(local_3c,&league_dir);
      sVar2 = strcspn(local_3c,(char *)CONCAT22(0xc,in_DS));
      local_3c[sVar2] = '\0';
      getmouse(&iStack_20,auStack_28,auStack_2c);
      set_dialog_colors(0xf9,0xfa,0xf8,0xfa,0);
      if (dword_dd7ac == 0) {
        if ((dword_dd7b0 & 4) == 0) {
          dword_c7dee = local_3c;
          iStack_20 = message_dialog(0xffffffff,0xffffffff,&off_c7dea,4,&unk_c7e4e,2,auStack_28,
                                     auStack_2c,0xffffffff);
          if (iStack_20 != 0) goto LAB_00040d6d;
          league_merge_check();
          iVar5 = -1;
        }
      }
      else {
        dword_c80a1 = local_3c;
        message_dialog(0xffffffff,0xffffffff,&off_c809d,3,0,0,auStack_28,auStack_2c,0xffffffff);
LAB_00040d6d:
        iVar1 = -1;
      }
    }
    if (iVar5 == 0) {
      if (byte_de268 != '\0') {
        clearclip(0);
        puVar4 = install_path;
        if (byte_ed836 != '\x01') {
          puVar4 = (undefined *)0x0;
        }
        make_path(local_5c,puVar4,aEasndesk_c1a48,0);
        uVar3 = loadshapes(local_5c,0);
        iVar5 = locateshape(uVar3,&aPal_c1a51);
        setpalette(0,0x100,iVar5 + 0x10);
        freemem(uVar3);
        uStack_1c = 0x17;
        uStack_1b = 0x17;
        uStack_1a = 0x17;
        setpalette(0xf8,1,&uStack_1c);
        uStack_1c = 0x2a;
        uStack_1b = 0x2a;
        uStack_1a = 0x2a;
        setpalette(0xf9,1,&uStack_1c);
        uStack_1c = 0x3f;
        uStack_1b = 0x3f;
        uStack_1a = 0x3f;
        setpalette(0xfa,1,&uStack_1c);
      }
      iVar5 = dword_ddac0;
      if (iVar1 == 0) {
        if (dword_ddac0 < 2) {
          set_dialog_colors(0xf9,0xfa,0xf8,0xfa,0);
          getmouse(&iStack_20,auStack_28,auStack_2c);
          message_dialog(0xffffffff,0xffffffff,&off_c753c,2,0,0,auStack_28,auStack_2c,0xffffffff);
        }
        else {
          make_path(local_5c,&league_dir,off_c80e7,&aDB);
          db_open_check(local_5c,&unk_ddac4,1);
          team_info_screen(&league_dir,&dword_ddac0,&unk_ddac4,&unk_dd7b4,4,
                           aSelectHumanControlledTea_c81ac,&iStack_24);
          if ((-1 < iStack_24) && (iVar5 != dword_ddac0)) {
            pinfo_db_create(&league_dir,&unk_dd7b4,&unk_ddd1d,dword_dd7a8,dword_ddac0,dword_dd7b0,
                            dword_dd7ac,&byte_ddd10);
          }
        }
      }
      return;
    }
  } while( true );
}


// ================================================================================================
// league_settings_flow @ 0x40f4e [__watcall]
// ================================================================================================

undefined8 __watcall league_settings_flow(undefined4 param_1,undefined4 unaff_EDX)

{
  int iVar1;
  size_t sVar2;
  int iVar3;
  undefined2 in_DS;
  char local_34 [16];
  undefined auStack_24 [4];
  undefined auStack_20 [4];
  int iStack_1c;
  undefined uStack_18;
  undefined uStack_17;
  undefined uStack_16;
  
  __CHK(0x4c);
  iVar1 = return_zero_41337(&league_dir,2);
  do {
    iVar3 = 0;
    if (iVar1 == 0) {
      iVar1 = load_league_info(&league_dir,&unk_dd7b4,&unk_ddd1d,&dword_dd7a8,&dword_ddac0,
                               &dword_dd7b0,&dword_dd7ac,&byte_ddd10);
    }
    if (iVar1 == 0) {
      strcpy(local_34,&league_dir);
      sVar2 = strcspn(local_34,(char *)CONCAT22(0xc,in_DS));
      local_34[sVar2] = '\0';
      if (((byte)dword_dd7b0 & 4) == 0) {
        dword_c7dee = local_34;
        set_dialog_colors(0xf9,0xfa,0xf8,0xfa,0);
        getmouse(&iStack_1c,auStack_20,auStack_24);
        iStack_1c = message_dialog(0xffffffff,0xffffffff,&off_c7dea,4,&unk_c7e4e,2,auStack_20,
                                   auStack_24,0xffffffff);
        if (iStack_1c == 0) {
          league_merge_check();
          iVar3 = -1;
        }
        else {
          iVar1 = -1;
        }
      }
    }
  } while (iVar3 != 0);
  if (iVar1 == 0) {
    if (byte_de268 != '\0') {
      clearclip(0);
      uStack_18 = 0x17;
      uStack_17 = 0x17;
      uStack_16 = 0x17;
      setpalette(0xf8,1,&uStack_18);
      uStack_18 = 0x2a;
      uStack_17 = 0x2a;
      uStack_16 = 0x2a;
      setpalette(0xf9,1,&uStack_18);
      uStack_18 = 0x3f;
      uStack_17 = 0x3f;
      uStack_16 = 0x3f;
      setpalette(0xfa,1,&uStack_18);
    }
    set_dialog_colors(0xf9,0xfa,0xf8,0xfa,0);
    iVar1 = master_password_prompt(dword_dd7a8,&unk_dd7b4,&unk_ddd1d);
    if (byte_de268 != '\0') {
      clearclip(0);
      uStack_18 = 0;
      uStack_17 = 0;
      uStack_16 = 0;
      setpalette(0xf8,1,&uStack_18);
      setpalette(0xf9,1,&uStack_18);
      setpalette(0xfa,1,&uStack_18);
    }
  }
  return CONCAT44(unaff_EDX,iVar1);
}


// ================================================================================================
// format_from_league @ 0x41171 [__watcall]
// ================================================================================================

void __watcall format_from_league(char *param_1,char *unaff_EDX,char *unaff_EBX)

{
  size_t sVar1;
  undefined2 in_DS;
  char acStackY_1c [16];
  
  __CHK(0x20);
  strcpy(acStackY_1c,unaff_EBX);
  sVar1 = strcspn(acStackY_1c,(char *)CONCAT22((short)((uint)unaff_EBX >> 0x10),in_DS));
  acStackY_1c[sVar1] = '\0';
  strcpy(param_1,unaff_EDX);
  strcat(param_1,aFromTheLeague);
  strcat(param_1,acStackY_1c);
  return;
}


// ================================================================================================
// load_league_list @ 0x411c8 [__watcall]
// ================================================================================================

int __watcall load_league_list(int *param_1,int *unaff_EDX,uint unaff_EBX)

{
  int iVar1;
  int iVar2;
  void *pvVar3;
  undefined *__n;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined2 in_DS;
  undefined auStack_5c [30];
  char acStack_3e [14];
  char acStack_30 [16];
  undefined local_20 [4];
  undefined *local_1c;
  
  __CHK(0x70);
  strcpy(acStack_30,&unk_c8113);
  strcat(acStack_30,(char *)&aLP_c815c);
  iVar5 = 0;
  iVar2 = _dos_findfirst(acStack_30,0x10,auStack_5c);
  if (iVar2 == 0) {
    iVar5 = 1;
    while (iVar2 = _dos_findnext(auStack_5c), iVar2 == 0) {
      iVar5 = iVar5 + 1;
    }
  }
  iVar2 = iVar5;
  if (iVar5 != 0) {
    pvVar3 = (void *)allocmem(&aLLST,iVar5 << 2,0x20);
    *param_1 = (int)pvVar3;
    memset(pvVar3,0,iVar5 << 2);
    __n = (undefined *)(iVar5 * 9);
    pvVar3 = (void *)allocmem(&aLLSN,__n,0x20);
    *unaff_EDX = (int)pvVar3;
    iVar4 = 0;
    memset(pvVar3,0,(size_t)__n);
    for (iVar6 = 0; iVar6 < iVar5; iVar6 = iVar6 + 1) {
      if (iVar6 == 0) {
        __n = auStack_5c;
        _dos_findfirst(acStack_30,0x10);
      }
      else {
        _dos_findnext(auStack_5c,iVar4,__n);
      }
      iVar4 = league_player_id_check(acStack_3e,local_20);
      if (((iVar4 < 0) && ((unaff_EBX & 2) != 0)) || ((-1 < iVar4 && ((unaff_EBX & 1) != 0)))) {
        __n = (undefined *)strcspn(acStack_3e,(char *)CONCAT22((short)((uint)iVar4 >> 0x10),in_DS));
        iVar1 = iVar6 * 9;
        local_1c = __n;
        strncpy((char *)(*unaff_EDX + iVar1),acStack_3e,(size_t)__n);
        local_1c[*unaff_EDX + iVar1] = 0;
        iVar4 = *param_1;
        *(int *)(iVar4 + iVar6 * 4) = iVar1 + *unaff_EDX;
      }
      else {
        iVar2 = iVar2 + -1;
      }
    }
  }
  if (iVar2 == 0) {
    *param_1 = 0;
    *unaff_EDX = 0;
  }
  return iVar2;
}


// ================================================================================================
// return_zero_41337 @ 0x41337 [__watcall]
// ================================================================================================

undefined4 __watcall return_zero_41337(void)

{
  __CHK(4);
  return 0;
}


// ================================================================================================
// league_player_id_check @ 0x41344 [__watcall]
// ================================================================================================

int __watcall league_player_id_check(undefined4 param_1,undefined4 unaff_EDX)

{
  int iVar1;
  undefined auStackY_34 [32];
  undefined4 local_14;
  char acStackY_10 [4];
  
  __CHK(0x38);
  local_14 = 0xffffffff;
  make_path(auStackY_34,param_1,aPLAYER_c80f9,&aID_c8166);
  iVar1 = file_open_read(auStackY_34,&local_14);
  if (iVar1 == 0) {
    iVar1 = file_read(local_14,acStackY_10,0,1);
  }
  if (iVar1 == 0) {
    iVar1 = file_read(local_14,unaff_EDX,0x19,4);
  }
  if (iVar1 != 0) {
    acStackY_10[0] = -1;
  }
  file_close(&local_14);
  return (int)acStackY_10[0];
}


// ================================================================================================
// pinfo_db_create @ 0x413cd [__watcall]
// ================================================================================================

undefined4 __watcall pinfo_db_create(undefined4 param_1,undefined4 unaff_EDX,undefined4 param_3)

{
  int iVar1;
  undefined4 extraout_EDX;
  undefined4 in_stack_00000010;
  undefined auStackY_30 [32];
  undefined4 uStackY_c;
  
  __CHK(0x34);
  uStackY_c = 0xffffffff;
  make_path(auStackY_30,param_1,aPINFO,&aDB);
  iVar1 = file_create(auStackY_30,&uStackY_c);
  if (iVar1 == 0) {
    iVar1 = file_write(uStackY_c,&stack0x00000004,0,2);
  }
  if (iVar1 == 0) {
    iVar1 = file_write(uStackY_c,&stack0xfffffff0,2);
  }
  if (iVar1 == 0) {
    iVar1 = file_write(uStackY_c,&stack0x0000000c,4,2);
  }
  if (iVar1 == 0) {
    iVar1 = file_write(uStackY_c,in_stack_00000010,6,0xd);
  }
  if (iVar1 == 0) {
    iVar1 = file_write(uStackY_c,&stack0x00000008,0x13,2);
  }
  if (iVar1 == 0) {
    iVar1 = file_write(uStackY_c,param_3,0x15,0xb);
  }
  if (iVar1 == 0) {
    iVar1 = file_write(uStackY_c,unaff_EDX,0x20,0x30c);
  }
  file_close(&uStackY_c,iVar1);
  return extraout_EDX;
}


// ================================================================================================
// show_league_message @ 0x414e0 [__watcall]
// ================================================================================================

void __watcall show_league_message(undefined4 param_1)

{
  __CHK(0x24);
  dword_c7bd5 = param_1;
  message_dialog(0xffffffff,0xffffffff,&off_c7bd1,2,0,0,0,0,0);
  return;
}


// ================================================================================================
// league_player_sync @ 0x41516 [__watcall]
// ================================================================================================

int __watcall league_player_sync(char *param_1,int unaff_EDX,int unaff_EBX)

{
  bool bVar1;
  int iVar2;
  int extraout_ECX;
  int iVar3;
  char *__src;
  char acStack_cc [64];
  char acStack_8c [32];
  char acStack_6c [16];
  undefined auStack_5c [16];
  char local_4c [12];
  char local_40;
  undefined auStack_3f [7];
  undefined4 local_38;
  undefined4 local_34;
  undefined local_30 [4];
  undefined local_2c [4];
  int local_28;
  int local_18;
  undefined4 uStack_14;
  
  __CHK(0xe4);
  local_38 = 0xffffffff;
  local_34 = 0xffffffff;
  iVar3 = 0;
  local_18 = 0;
  do {
    if ((0x19 < local_18) || (iVar3 != 0)) {
      if (iVar3 == 0) {
        make_path(acStack_8c,param_1,aPINFO,&aDB);
        iVar3 = file_open_rw(acStack_8c,&local_34);
      }
      if (iVar3 == 0) {
        uStack_14 = 0;
        iVar3 = file_write(local_34,&uStack_14,0x13,2);
      }
      file_close(&local_34);
      return iVar3;
    }
    if ((*(char *)(local_18 * 0x1e + unaff_EDX + 0x17) == '\x01') &&
       ((unaff_EBX < 0 || (unaff_EBX == local_18)))) {
      sprintf(acStack_cc,a02d_c1a62,local_18);
      strcpy((char *)&aXx,acStack_cc);
      iVar2 = extraout_ECX * 0x1e + unaff_EDX;
      if ((*(char *)(iVar2 + 0x18) == '\x02') && ((*(byte *)(iVar2 + 0x16) & 1) == 0)) {
        do {
          bVar1 = false;
          __src = (char *)(unaff_EDX + local_18 * 0x1e);
          strcpy(local_4c,__src);
          dword_c7615 = local_4c;
          getmouse(&local_28,local_2c,local_30);
          iVar3 = message_dialog(0xffffffff,0xffffffff,&off_c7611,4,0,0,local_2c,local_30,0xffffffff
                                );
          if (iVar3 == 0) {
            iVar3 = player_id_write(param_1,__src);
          }
          if (iVar3 == 0) {
            make_path(acStack_8c,&byte_c816a,aPLAYER_c80f9,&aID_c8166);
            iVar2 = file_open_read(acStack_8c,&local_38);
            if (iVar2 == 0) {
              file_read(local_38,local_4c,1,0xb);
              file_read(local_38,auStack_5c,0xffffffff,0xd);
              iVar2 = stricmp(local_18 * 0x1e + unaff_EDX,local_4c);
              if (iVar2 == 0) {
                iVar2 = stricmp(param_1,auStack_5c);
                if (iVar2 == 0) goto LAB_0004179b;
              }
              format_from_league(acStack_cc,local_4c,auStack_5c);
              dword_c766f = acStack_cc;
              getmouse(&local_28,local_2c,local_30);
              local_28 = message_dialog(0xffffffff,0xffffffff,&off_c766b,3,&unk_c7677,2,local_2c,
                                        local_30,0xffffffff);
              if ((local_28 == 1) || (local_28 < 0)) {
                bVar1 = true;
              }
            }
LAB_0004179b:
            file_close(&local_38);
          }
        } while ((bVar1) && (iVar3 == 0));
        event_queue_reset();
        if (iVar3 == 0) {
          iVar3 = pinfo_find_player(param_1,&aDB,&aXx,local_18,unaff_EDX,0xffffffff,0);
        }
        else {
          iVar3 = -1;
        }
      }
      else {
        show_league_message(local_18 * 0x1e + unaff_EDX);
        iVar2 = 0;
        while ((iVar2 < 7 && (iVar3 == 0))) {
          strcpy(acStack_6c,param_1);
          strcpy(acStack_8c,(&off_c80d7)[iVar2]);
          strcpy(&local_40,(char *)&aXx);
          delete_matching_files(acStack_6c,acStack_8c,auStack_3f);
          iVar3 = copy_file((&off_c80d7)[iVar2],&aDB,&aXx,param_1,param_1);
          iVar2 = iVar2 + 1;
        }
        if (iVar3 == 0) {
          make_path(acStack_8c,param_1,aPINFO,&aDB);
          iVar3 = file_open_rw(acStack_8c,&local_34);
        }
        if (iVar3 == 0) {
          iVar3 = unaff_EDX + local_18 * 0x1e;
          *(undefined *)(iVar3 + 0x16) = 1;
          iVar3 = league_write_team_entry(local_34,iVar3,local_18);
        }
        file_close(&local_34);
        restore_dialog_background();
      }
    }
    local_18 = local_18 + 1;
  } while( true );
}


// ================================================================================================
// league_save_db @ 0x41978 [__watcall]
// ================================================================================================

void __watcall league_save_db(undefined4 param_1)

{
  int iVar1;
  int extraout_EDX;
  undefined auStackY_4c [32];
  char acStackY_2c [4];
  char acStackY_28 [12];
  undefined4 local_1c;
  undefined4 uStackY_18;
  
  __CHK(0x50);
  local_1c = 0xffffffff;
  iVar1 = file_write(param_1,&league_team,0xffffffff,4);
  if (iVar1 == 0) {
    iVar1 = file_write(param_1,&dword_ddd34,0xffffffff,4);
  }
  if (iVar1 == 0) {
    iVar1 = file_write(param_1,&dword_ddd3c,0xffffffff,4);
  }
  if (iVar1 == 0) {
    iVar1 = file_write(param_1,&word_ddd48,0xffffffff,4);
  }
  if (iVar1 == 0) {
    iVar1 = file_write(param_1,&word_ddd4a,0xffffffff,4);
  }
  if (iVar1 == 0) {
    iVar1 = file_write(param_1,0xddd46,0xffffffff,4);
  }
  if (iVar1 == 0) {
    iVar1 = file_write(param_1,&unk_ddd4c,0xffffffff,0xd);
  }
  if (iVar1 == 0) {
    iVar1 = file_write(param_1,&unk_ddd59,0xffffffff,0xd);
  }
  if (iVar1 == 0) {
    iVar1 = file_write(param_1,&byte_ddd40,0xffffffff,6);
  }
  uStackY_18 = 0xffffffff;
  acStackY_2c[0] = aSaved[0];
  acStackY_2c[1] = aSaved[1];
  acStackY_2c[2] = aSaved[2];
  acStackY_2c[3] = aSaved[3];
  acStackY_28[0] = aSaved[4];
  acStackY_28[1] = aSaved[5];
  if (iVar1 == 0) {
    make_path(auStackY_4c,&unk_ddd4c,aPINFO,&aDB);
    iVar1 = file_open_trunc(auStackY_4c,&local_1c);
  }
  if (iVar1 == 0) {
    iVar1 = file_write(local_1c,&uStackY_18,4,2);
  }
  if (iVar1 == 0) {
    iVar1 = file_write(local_1c,acStackY_2c,6,0xd);
  }
  file_close(&local_1c,iVar1);
  if (dword_ddd3c != 0) {
    iVar1 = extraout_EDX;
    if (extraout_EDX == 0) {
      make_path(auStackY_4c,&unk_ddd59,aPINFO,&aDB);
      iVar1 = file_open_trunc(auStackY_4c,&local_1c);
    }
    if (iVar1 == 0) {
      iVar1 = file_write(local_1c,&uStackY_18,4,2);
    }
    if (iVar1 == 0) {
      file_write(local_1c,acStackY_2c,6,0xd);
    }
    file_close(&local_1c);
  }
  return;
}


// ================================================================================================
// league_db_read_header @ 0x41b80 [__watcall]
// ================================================================================================

void __watcall league_db_read_header(undefined4 param_1)

{
  int iVar1;
  
  __CHK(0x14);
  iVar1 = file_read(param_1,&league_team,0xffffffff,4);
  if (iVar1 == 0) {
    iVar1 = file_read(param_1,&dword_ddd34,0xffffffff,4);
  }
  if (iVar1 == 0) {
    iVar1 = file_read(param_1,&dword_ddd3c,0xffffffff,4);
  }
  if (iVar1 == 0) {
    iVar1 = file_read(param_1,&word_ddd48,0xffffffff,4);
  }
  if (iVar1 == 0) {
    iVar1 = file_read(param_1,&word_ddd4a,0xffffffff,4);
  }
  if (iVar1 == 0) {
    iVar1 = file_read(param_1,0xddd46,0xffffffff,4);
  }
  if (iVar1 == 0) {
    iVar1 = file_read(param_1,&unk_ddd4c,0xffffffff,0xd);
  }
  if (iVar1 == 0) {
    iVar1 = file_read(param_1,&unk_ddd59,0xffffffff,0xd);
  }
  if (iVar1 == 0) {
    file_read(param_1,&byte_ddd40,0xffffffff,6);
  }
  return;
}


// ================================================================================================
// date_to_day_index @ 0x41c79 [__watcall]
// ================================================================================================

int __watcall date_to_day_index(int param_1,int unaff_EDX)

{
  __CHK(8);
  if (param_1 < 9) {
    param_1 = param_1 + 0xc;
  }
  return param_1 * 0x1f + unaff_EDX;
}


// ================================================================================================
// day_to_month_day @ 0x41c9b [__watcall]
// ================================================================================================

void __watcall day_to_month_day(byte *param_1,byte *unaff_EDX)

{
  __CHK(0xc);
  while( true ) {
    if (*unaff_EDX <= (byte)(&unk_c8444)[*param_1]) break;
    *unaff_EDX = *unaff_EDX - (&unk_c8444)[*param_1];
    *param_1 = *param_1 + 1;
  }
  return;
}


// ================================================================================================
// league_play_day @ 0x41cc4 [__watcall]
// ================================================================================================

int __watcall
league_play_day(undefined4 param_1,undefined4 unaff_EDX,int unaff_EBX,undefined4 unaff_ECX,
               undefined4 param_5,undefined4 param_6)

{
  bool bVar1;
  int iVar2;
  undefined auStack_48 [32];
  undefined auStack_28 [2];
  char cStack_26;
  char cStack_25;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  
  __CHK(0x60);
  local_18 = 0xffffffff;
  local_1c = 0xffffffff;
  local_20 = 0xffffffff;
  byte_de268 = 0;
  make_path(auStack_48,param_1,off_c80ef,unaff_EDX);
  iVar2 = file_open_rw(auStack_48,&local_18);
  if (iVar2 == 0) {
    make_path(auStack_48,param_1,off_c80e7,unaff_EDX);
    iVar2 = file_open_rw(auStack_48,&local_1c);
  }
  if (iVar2 == 0) {
    make_path(auStack_48,param_1,off_c80e3,unaff_EDX);
    iVar2 = file_open_read(auStack_48,&local_20);
  }
  if ((iVar2 == 0) && (unaff_EBX < 0x4ad)) {
    iVar2 = db_read_record2(local_18,auStack_28,unaff_EBX);
  }
  if (iVar2 == 0) {
    make_path(auStack_48,param_1,off_c80eb,unaff_EDX);
    dword_d07bb = loadfile(auStack_48,0x20);
    dword_d07d3 = filesize(auStack_48);
    make_path(auStack_48,param_1,off_c80db,unaff_EDX);
    dword_d07bf = loadfile(auStack_48,0x20);
    dword_d07d7 = filesize(auStack_48);
    make_path(auStack_48,param_1,off_c80d7,unaff_EDX);
    dword_d07c7 = loadfile(auStack_48,0x20);
    dword_d07df = filesize(auStack_48);
    if (0 < unaff_EBX) {
      if (unaff_EBX < 0x445) {
        if (((unaff_EBX == 0x444) && (cStack_26 != -1)) && (cStack_25 != -1)) {
          bVar1 = false;
        }
        else {
          bVar1 = true;
        }
        if (bVar1) {
          iVar2 = schedule_play_games(local_18,local_1c,local_20,unaff_EBX,unaff_ECX,param_1,
                                      unaff_EDX,param_5,param_6);
          goto LAB_00041ea6;
        }
      }
      iVar2 = schedule_screen2(local_18,local_1c,local_20,unaff_ECX,param_1,unaff_EDX,param_5,
                               param_6);
    }
  }
LAB_00041ea6:
  if ((iVar2 == 0) && (dword_d07bb != 0)) {
    make_path(auStack_48,param_1,off_c80eb,unaff_EDX);
    savefile(auStack_48,dword_d07bb,dword_d07d3);
  }
  if (dword_d07bb != 0) {
    freemem(dword_d07bb);
  }
  if (dword_d07bf != 0) {
    freemem(dword_d07bf);
  }
  if (dword_d07c7 != 0) {
    freemem(dword_d07c7);
  }
  dword_d07bb = 0;
  dword_d07bf = 0;
  dword_d07c7 = 0;
  dword_d07d3 = 0;
  dword_d07d7 = 0;
  dword_d07df = 0;
  file_close(&local_20);
  file_close(&local_1c);
  file_close(&local_18);
  return iVar2;
}


// ================================================================================================
// playoff_trim_series @ 0x41f64 [__watcall]
// ================================================================================================

int __watcall playoff_trim_series(undefined4 param_1,undefined4 unaff_EDX,int unaff_EBX)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint unaff_EBP;
  undefined auStackY_380 [620];
  undefined4 auStackY_114 [31];
  int aiStackY_98 [26];
  undefined local_30;
  undefined local_2f;
  byte bStackY_2e;
  byte bStackY_2d;
  byte local_2c;
  byte bStackY_2b;
  int local_20;
  int local_18;
  uint uStackY_14;
  
  __CHK(900);
  iVar5 = 0;
  _memset_dwords(aiStackY_98,0,0,0x1a);
  if (unaff_EBX < 0x47c) {
    local_20 = 0;
  }
  else if (unaff_EBX < 0x498) {
    local_20 = 7;
  }
  else if (unaff_EBX < 0x4a6) {
    local_20 = 0xe;
  }
  else if (unaff_EBX < 0x4ad) {
    local_20 = 0x15;
  }
  iVar2 = (unaff_EBX + -0x444) - (unaff_EBX + -0x444) % 7;
  local_18 = 0;
  iVar3 = 0;
  while ((iVar3 < 7 && (iVar5 == 0))) {
    iVar5 = db_read_record2(param_1,&local_30,iVar2 + 0x444 + iVar3);
    if (iVar5 == 0) {
      if (iVar3 == 0) {
        unaff_EBP = (uint)bStackY_2e;
        uStackY_14 = (uint)bStackY_2d;
      }
      if ((bStackY_2e != 0xff) && (bStackY_2d != 0xff)) {
        local_18 = local_18 + 1;
      }
    }
    iVar3 = iVar3 + 1;
  }
  iVar3 = (local_18 + 1) / 2;
  iVar4 = 0;
  while ((iVar4 < local_18 && (iVar5 == 0))) {
    if ((iVar5 == 0) && ((aiStackY_98[unaff_EBP] == iVar3 || (iVar3 == aiStackY_98[uStackY_14])))) {
      local_30 = 0xff;
      local_2f = 0xff;
      local_2c = 0xff;
      bStackY_2b = 0xff;
      iVar5 = schedule_write_record(param_1,&local_30,iVar2 + 0x444 + iVar4);
      if (iVar5 == 0) {
        iVar5 = db_read_record(unaff_EDX,auStackY_380,unaff_EBP);
      }
      if (iVar5 == 0) {
        auStackY_114[local_20 + iVar4] = 0xffffffff;
        iVar5 = db_write_team_record(unaff_EDX,auStackY_380,unaff_EBP);
      }
      if (iVar5 == 0) {
        iVar5 = db_read_record(unaff_EDX,auStackY_380,uStackY_14);
      }
      if (iVar5 == 0) {
        auStackY_114[local_20 + iVar4] = 0xffffffff;
        iVar5 = db_write_team_record(unaff_EDX,auStackY_380,uStackY_14);
      }
    }
    else {
      iVar5 = db_read_record2(param_1,&local_30,iVar2 + 0x444 + iVar4);
      if ((local_2c != 0xff) && (bStackY_2b != 0xff)) {
        bVar1 = bStackY_2d;
        if (bStackY_2b < local_2c) {
          bVar1 = bStackY_2e;
        }
        aiStackY_98[bVar1] = aiStackY_98[bVar1] + 1;
      }
    }
    iVar4 = iVar4 + 1;
  }
  return iVar5;
}


// ================================================================================================
// playoff_series_count @ 0x42221 [__watcall]
// ================================================================================================

undefined8 __watcall playoff_series_count(int param_1,undefined4 unaff_EDX)

{
  int iVar1;
  undefined4 unaff_ESI;
  
  __CHK(0x10);
  iVar1 = 0;
  do {
    if (*(char *)(param_1 + iVar1 * 6) == -1) break;
    iVar1 = iVar1 + 1;
  } while (iVar1 < 7);
  switch(iVar1) {
  case 1:
    unaff_ESI = 1;
    break;
  case 3:
    iVar1 = series_winner(param_1,5);
    if (-1 < iVar1) {
LAB_00042277:
      unaff_ESI = 5;
      break;
    }
  case 2:
    unaff_ESI = 3;
    break;
  case 4:
  case 5:
    iVar1 = series_winner(param_1,7);
    if (iVar1 < 0) goto LAB_00042277;
  case 6:
  case 7:
    unaff_ESI = 7;
  }
  return CONCAT44(unaff_EDX,unaff_ESI);
}


