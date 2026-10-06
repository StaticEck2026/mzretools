// Decompiled by Ghidra from hockey.elf (via ledisasm ELF export)
// This is machine generated pseudo-C meant as a reference for porting, it does not compile as is.
#include "prototypes.h"

// ================================================================================================
// league_db_load @ 0x42295 [__watcall]
// ================================================================================================

/* WARNING: Type propagation algorithm not settling */

undefined4 __watcall league_db_load(undefined4 param_1,int unaff_EDX)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  undefined4 extraout_EDX;
  int iVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  undefined auStack_3b4 [284];
  int aiStack_298 [85];
  byte abStack_143 [115];
  int iStack_d0;
  int aiStack_cc [26];
  undefined auStack_64 [32];
  byte abStack_44 [28];
  undefined uStack_28;
  undefined uStack_27;
  byte bStack_26;
  byte bStack_25;
  undefined local_24;
  undefined uStack_23;
  undefined4 local_20;
  undefined4 uStack_1c;
  uint uStack_18;
  
  __CHK(0x3d4);
  local_20 = 0xffffffff;
  uStack_1c = 0xffffffff;
  if (unaff_EDX != 0) {
    message_dialog(0xffffffff,0xffffffff,&off_c8c59,2,0,0,0,0,0);
    _memset_dwords(aiStack_cc,0,&off_c8c59,0x1a);
    iVar9 = 0;
    do {
      iVar6 = 0;
      do {
        iVar2 = iVar9 * 7 + iVar6;
        abStack_44[iVar2] = (&unk_c83c3)[iVar2];
        iVar6 = iVar6 + 1;
      } while (iVar6 < 7);
      iVar2 = (1 < iVar9) + 6;
      iVar6 = 0;
      do {
        iVar3 = rand();
        iVar4 = rand();
        iVar7 = iVar3 % iVar2 + iVar9 * 7;
        bVar1 = abStack_44[iVar7];
        iVar3 = iVar4 % iVar2 + iVar9 * 7;
        abStack_44[iVar7] = abStack_44[iVar3];
        abStack_44[iVar3] = bVar1;
        iVar6 = iVar6 + 1;
      } while (iVar6 < 0xc);
      iVar9 = iVar9 + 1;
    } while (iVar9 < 4);
  }
  make_path(auStack_64,param_1,off_c80ef,&aDB);
  iVar9 = file_open_rw(auStack_64,&local_20);
  if (iVar9 == 0) {
    make_path(auStack_64,param_1,off_c80e7,&aDB);
    iVar9 = file_open_rw(auStack_64,&uStack_1c);
  }
  if (iVar9 == 0) {
    iVar6 = 0;
    iVar9 = 0;
    while (((iVar6 < 0x444 && (iVar9 == 0)) && (unaff_EDX != 0))) {
      iVar9 = db_read_record2(local_20,&uStack_28);
      if (iVar9 == 0) {
        uVar8 = (uint)bStack_26;
        uVar5 = (uint)bStack_25;
        iVar9 = 0;
        do {
          if (-1 < (int)uVar8) {
            uStack_18 = (uint)(byte)(&unk_c83df)[uVar8];
            iVar2 = (uint)(byte)(&unk_c83df)[uVar8] * 7 + (uint)(byte)(&unk_c83f9)[uVar8];
            if (uVar8 == (byte)(&unk_c83c3)[iVar2]) {
              bStack_26 = abStack_44[iVar2];
              uVar8 = 0xffffffff;
            }
          }
          if (-1 < (int)uVar5) {
            uStack_18 = (uint)(byte)(&unk_c83df)[uVar5];
            iVar2 = (uint)(byte)(&unk_c83df)[uVar5] * 7 + (uint)(byte)(&unk_c83f9)[uVar5];
            if (uVar5 == (byte)(&unk_c83c3)[iVar2]) {
              bStack_25 = abStack_44[iVar2];
              uVar5 = 0xffffffff;
            }
          }
          if (((int)uVar8 < 0) && ((int)uVar5 < 0)) {
            iVar9 = 0x1a;
          }
          iVar9 = iVar9 + 1;
        } while (iVar9 < 0x1a);
        iVar9 = sub_3a28f(local_20,&uStack_28,iVar6);
        if (iVar9 == 0) {
          uVar8 = (uint)bStack_26;
          uVar5 = (uint)bStack_25;
          iVar9 = db_read_record(uStack_1c,auStack_3b4,uVar8);
        }
        if (iVar9 == 0) {
          iVar9 = aiStack_cc[uVar8];
          aiStack_298[iVar9] = iVar6 * 6 + 2;
          aiStack_cc[uVar8] = iVar9 + 1;
          iVar9 = sub_3a2b8(uStack_1c,auStack_3b4,uVar8);
        }
        if (iVar9 == 0) {
          iVar9 = db_read_record(uStack_1c,auStack_3b4,uVar5);
        }
        if (iVar9 == 0) {
          iVar9 = aiStack_cc[uVar5];
          aiStack_298[iVar9] = iVar6 * 6 + 2;
          aiStack_cc[uVar5] = iVar9 + 1;
          iVar9 = sub_3a2b8(uStack_1c,auStack_3b4,uVar5);
        }
      }
      iVar6 = iVar6 + 1;
    }
    uStack_28 = 0xff;
    uStack_27 = 0xff;
    bStack_26 = 0xff;
    bStack_25 = 0xff;
    local_24 = 0xff;
    uStack_23 = 0xff;
    iVar6 = 0x444;
    while ((iVar6 < 0x4ad && (iVar9 == 0))) {
      iVar9 = sub_3a28f(local_20,&uStack_28,iVar6);
      iVar6 = iVar6 + 1;
    }
  }
  file_close(&uStack_1c);
  file_close(&local_20);
  sub_30f12();
  return extraout_EDX;
}


// ================================================================================================
// sub_42631 @ 0x42631 [__watcall]
// ================================================================================================

int __watcall
sub_42631(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4,int param_5)

{
  int iVar1;
  int iVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  undefined *puVar6;
  int iVar7;
  char cVar8;
  undefined local_30;
  undefined local_2f;
  
  __CHK(0x40);
  iVar1 = db_read_record2(param_1,&local_30,param_4 + -1);
  if (iVar1 == 0) {
    sub_41c79(local_30,local_2f);
    puVar3 = (undefined *)0x0;
    iVar7 = 0;
    puVar5 = &local_30;
    while (((iVar7 < 0x444 && (*(int *)(puVar5 + 0x10) == 0)) && (iVar1 == 0))) {
      *(undefined4 *)(puVar5 + -4) = 0x42693;
      iVar1 = db_read_record2(param_1,puVar5,iVar7,puVar3);
      if (iVar1 == 0) {
        *(undefined4 *)(puVar5 + -4) = 0x426ab;
        iVar2 = sub_41c79(*puVar5,puVar5[1]);
        if (*(int *)(puVar5 + 0x14) < iVar2) {
          if (((puVar5[2] != 0xff) && (puVar5[3] != -1)) &&
             ((*(char *)(param_5 + 0x17 + (uint)(byte)puVar5[2] * 0x1e) == '\x01' ||
              (*(char *)(param_5 + 0x17 + (uint)(byte)puVar5[3] * 0x1e) == '\x01')))) {
            *(undefined4 *)(puVar5 + 0x10) = 1;
          }
        }
        else {
          *(int *)(puVar5 + 0x18) = iVar7;
          *(uint *)(puVar5 + 8) = (uint)(byte)puVar5[2];
          cVar8 = *(char *)(param_5 + 0x17 +
                           ((uint)(byte)puVar5[2] * 0x10 - *(int *)(puVar5 + 8)) * 2) == '\x01';
          *(uint *)(puVar5 + 8) = (uint)(byte)puVar5[3];
          if (*(char *)(param_5 + 0x17 + ((uint)(byte)puVar5[3] * 0x10 - *(int *)(puVar5 + 8)) * 2)
              == '\x01') {
            cVar8 = cVar8 + '\x01';
          }
          if ((((puVar5[4] == -1) || (puVar5[5] == -1)) &&
              ((*(int *)(puVar5 + 0x40) == -1 ||
               ((puVar3 = *(undefined **)(puVar5 + 0x40),
                (undefined *)(uint)(byte)puVar5[2] == puVar3 ||
                ((undefined *)(uint)(byte)puVar5[3] == puVar3)))))) &&
             ((((puVar5[0x44] & 1) != 0 && (cVar8 == '\x02')) ||
              ((((puVar5[0x44] & 4) != 0 && (cVar8 == '\0')) ||
               (((puVar5[0x44] & 2) != 0 && (cVar8 == '\x01')))))))) {
            *(undefined4 *)(puVar5 + -4) = 0xffffffff;
            *(undefined4 *)(puVar5 + -8) = *(undefined4 *)(puVar5 + 0xc);
            *(undefined4 *)(puVar5 + -0xc) = *(undefined4 *)(puVar5 + 0x1c);
            puVar4 = puVar5 + -0x10;
            *(undefined4 *)(puVar5 + -0x10) = 0x42770;
            iVar1 = playoff_setup_screen
                              (*(undefined4 *)(puVar5 + 0x38),*(undefined4 *)(puVar5 + 0x3c),iVar7);
            puVar3 = puVar5;
            puVar5 = puVar4;
            if (iVar1 == 0) {
              *(undefined4 *)(puVar4 + -4) = 0x42781;
              iVar1 = sub_3a28f(param_1,puVar4,iVar7);
            }
          }
        }
      }
      iVar7 = iVar7 + 1;
    }
    if ((((*(int *)(puVar5 + 0x44) == 7) && (*(int *)(puVar5 + 0x10) == 0)) && (iVar1 == 0)) &&
       (iVar7 = *(int *)(puVar5 + 0x18), iVar7 < 0x444)) {
      *(undefined4 *)(puVar5 + 0x20) = 0x444;
      puVar3 = (undefined *)0x2;
      *(undefined4 *)(puVar5 + -4) = 0x42821;
      iVar1 = file_write(param_1,puVar5 + 0x20,0,2);
      while ((iVar7 < 0x444 && (iVar1 == 0))) {
        *(undefined4 *)(puVar5 + -4) = 0x42830;
        iVar1 = db_read_record2(param_1,puVar5,iVar7,puVar3);
        puVar6 = puVar5;
        if ((iVar1 == 0) && ((puVar5[4] == -1 || (puVar5[5] == -1)))) {
          *(undefined4 *)(puVar5 + -4) = 0xffffffff;
          *(undefined4 *)(puVar5 + -8) = *(undefined4 *)(puVar5 + 0xc);
          *(undefined4 *)(puVar5 + -0xc) = *(undefined4 *)(puVar5 + 0x1c);
          puVar6 = puVar5 + -0x10;
          *(undefined4 *)(puVar5 + -0x10) = 0x42863;
          iVar1 = playoff_setup_screen
                            (*(undefined4 *)(puVar5 + 0x38),*(undefined4 *)(puVar5 + 0x3c),iVar7);
          puVar3 = puVar5;
          if (iVar1 == 0) {
            *(undefined4 *)(puVar6 + -4) = 0x42874;
            iVar1 = sub_3a28f(param_1,puVar6,iVar7);
          }
        }
        iVar7 = iVar7 + 1;
        puVar5 = puVar6;
      }
      *(undefined4 *)(puVar5 + -4) = *(undefined4 *)(puVar5 + 0x3c);
      *(undefined4 *)(puVar5 + -8) = *(undefined4 *)(puVar5 + 0x38);
      *(undefined4 *)(puVar5 + -0xc) = 0x4289e;
      iVar1 = schedule_screen(param_1,*(undefined4 *)(puVar5 + 0x1c),*(undefined4 *)(puVar5 + 0xc),
                              param_5);
    }
  }
  return iVar1;
}


// ================================================================================================
// schedule_screen @ 0x428ab [__watcall]
// ================================================================================================

int __watcall
schedule_screen(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,int unaff_ECX,
               undefined4 param_5,undefined4 param_6)

{
  undefined uVar1;
  int iVar2;
  undefined4 *puVar3;
  uint uVar4;
  undefined4 uVar5;
  undefined4 *puVar6;
  undefined4 uVar7;
  int aiStack_ac [14];
  int aiStack_74 [14];
  undefined local_3c [32];
  int local_1c;
  int local_14;
  undefined4 local_10;
  
  __CHK(0xc0);
  local_1c = 0;
  iVar2 = sub_42bba(aiStack_ac,param_1,unaff_EDX);
  if (iVar2 != 0) {
    return iVar2;
  }
  puVar3 = (undefined4 *)allocmem(&aSche,0x276,0x20);
  iVar2 = 0;
  do {
    *(undefined *)((int)puVar3 + iVar2 * 6 + 5) = 0xff;
    uVar1 = *(undefined *)((int)puVar3 + iVar2 * 6 + 5);
    *(undefined *)((int)puVar3 + iVar2 * 6 + 4) = uVar1;
    *(undefined *)((int)puVar3 + iVar2 * 6 + 3) = uVar1;
    *(undefined *)((int)puVar3 + iVar2 * 6 + 2) = uVar1;
    *(undefined *)((int)puVar3 + iVar2 * 6 + 1) = uVar1;
    *(undefined *)((int)puVar3 + iVar2 * 6) = uVar1;
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0x69);
  iVar2 = 0;
  do {
    if ((*(char *)(unaff_ECX + 0x17 + aiStack_ac[iVar2] * 0x1e) == '\x01') ||
       (*(char *)(unaff_ECX + 0x17 + aiStack_74[iVar2] * 0x1e) == '\x01')) {
      local_1c = 1;
      break;
    }
    iVar2 = iVar2 + 1;
  } while (iVar2 < 8);
  uVar4 = (uint)(option_flags << 0x11) >> 0x1d;
  if (local_1c == 0) {
    local_14 = sub_42fed(aiStack_ac,puVar3,unaff_EDX,uVar4,unaff_ECX);
    if ((((((local_14 != 0) ||
           (local_14 = sub_43644(puVar3,unaff_EDX,unaff_EBX,param_5,param_6), local_14 != 0)) ||
          (local_14 = sub_43757(puVar3,(uint)(option_flags << 0x11) >> 0x1d,unaff_EDX,unaff_ECX,
                                &local_1c), local_14 != 0)) ||
         ((local_14 = sub_43e40(puVar3,unaff_EDX,unaff_EBX,param_5,param_6), local_14 != 0 ||
          (local_14 = sub_43f4b(puVar3,(uint)(option_flags << 0x11) >> 0x1d,unaff_EDX,unaff_ECX,
                                &local_1c), local_14 != 0)))) ||
        ((local_14 = sub_443b6(puVar3,unaff_EDX,unaff_EBX,param_5,param_6), local_14 != 0 ||
         ((local_14 = sub_444c9(puVar3,(uint)(option_flags << 0x11) >> 0x1d,unaff_EDX,unaff_ECX,
                                param_1,&local_1c), local_14 != 0 ||
          (local_14 = sub_447a6(puVar3,unaff_EDX,unaff_EBX,param_5,param_6), local_14 != 0)))))) ||
       (local_14 = file_write(param_1,puVar3,0x199a,0x276), local_14 != 0)) goto LAB_00042b9d;
    make_path(local_3c,param_5,off_c80eb,param_6);
    savefile(local_3c,dword_d07bb,dword_d07d3);
    awards_screen();
    byte_de268 = 0xff;
    local_10 = 0x4ad;
    uVar5 = 2;
    uVar7 = 0;
    puVar6 = &local_10;
  }
  else {
    local_14 = sub_42fed(aiStack_ac,puVar3,unaff_EDX,uVar4,unaff_ECX);
    if (local_14 != 0) goto LAB_00042b9d;
    uVar5 = 0x276;
    uVar7 = 0x199a;
    puVar6 = puVar3;
  }
  local_14 = file_write(param_1,puVar6,uVar7,uVar5);
LAB_00042b9d:
  freemem(puVar3);
  return local_14;
}


// ================================================================================================
// sub_42bba @ 0x42bba [__watcall]
// ================================================================================================

int __watcall sub_42bba(int *param_1,undefined4 param_2,undefined4 unaff_EBX)

{
  int iVar1;
  int iVar2;
  undefined auStack_3d8 [41];
  byte bStack_3af;
  byte bStack_3ad;
  ushort uStack_3ac;
  ushort uStack_3aa;
  uint auStack_f0 [14];
  uint auStack_b8 [14];
  uint auStack_80 [14];
  int aiStack_48 [14];
  
  __CHK(0x3e4);
  iVar2 = 0;
  do {
    iVar1 = db_read_record(unaff_EBX,auStack_3d8,(&unk_c55e9)[iVar2]);
    if (iVar1 != 0) {
      return iVar1;
    }
    param_1[iVar2] = (&unk_c55e9)[iVar2];
    aiStack_48[iVar2] = (uint)bStack_3af * 2 + (uint)bStack_3ad;
    auStack_f0[iVar2] = (uint)bStack_3af;
    auStack_80[iVar2] = (uint)uStack_3ac;
    auStack_b8[iVar2] = (uint)uStack_3aa;
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0xc);
  sub_42daa(param_1,aiStack_48,auStack_f0,auStack_80,auStack_b8,0xc);
  if ((*(uint *)(&unk_c5519 + *param_1 * 4) | *(uint *)(&unk_c5519 + param_1[1] * 4)) != 3) {
    iVar2 = 2;
    do {
      if ((*(uint *)(&unk_c5519 + *param_1 * 4) | *(uint *)(&unk_c5519 + param_1[iVar2] * 4)) == 3)
      break;
      iVar2 = iVar2 + 1;
    } while (iVar2 < 0xc);
    iVar1 = param_1[iVar2];
    for (; 1 < iVar2; iVar2 = iVar2 + -1) {
      param_1[iVar2] = param_1[iVar2 + -1];
    }
    param_1[1] = iVar1;
  }
  iVar2 = 0;
  do {
    iVar1 = db_read_record(unaff_EBX,auStack_3d8,(&unk_c5619)[iVar2]);
    if (iVar1 != 0) {
      return iVar1;
    }
    param_1[iVar2 + 0xe] = (&unk_c5619)[iVar2];
    aiStack_48[iVar2] = (uint)bStack_3af * 2 + (uint)bStack_3ad;
    auStack_f0[iVar2] = (uint)bStack_3af;
    auStack_80[iVar2] = (uint)uStack_3ac;
    auStack_b8[iVar2] = (uint)uStack_3aa;
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0xe);
  sub_42daa(param_1 + 0xe,aiStack_48,auStack_f0,auStack_80,auStack_b8,0xe);
  if ((*(uint *)(&unk_c5519 + param_1[0xe] * 4) | *(uint *)(&unk_c5519 + param_1[0xf] * 4)) != 0xc)
  {
    iVar2 = 2;
    do {
      if ((*(uint *)(&unk_c5519 + param_1[0xe] * 4) |
          *(uint *)(&unk_c5519 + param_1[iVar2 + 0xe] * 4)) == 0xc) break;
      iVar2 = iVar2 + 1;
    } while (iVar2 < 0xe);
    iVar1 = param_1[iVar2 + 0xe];
    for (; 1 < iVar2; iVar2 = iVar2 + -1) {
      param_1[iVar2 + 0xe] = param_1[iVar2 + 0xd];
    }
    param_1[0xf] = iVar1;
  }
  return 0;
}


// ================================================================================================
// sub_42daa @ 0x42daa [__watcall]
// ================================================================================================

void __watcall
sub_42daa(int param_1,int unaff_EDX,int unaff_EBX,int unaff_ECX,int param_5,int param_6)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  __CHK(0x38);
  iVar4 = 0;
  do {
    iVar2 = iVar4;
    if (param_6 + -1 <= iVar4) {
      return;
    }
    while (iVar2 = iVar2 + 1, iVar2 < param_6) {
      iVar3 = iVar2 * 4;
      iVar1 = iVar4 * 4;
      if (*(int *)(unaff_EDX + iVar1) < *(int *)(unaff_EDX + iVar3)) {
LAB_00042e00:
        iVar1 = *(int *)(param_1 + iVar3);
      }
      else {
        if (*(int *)(unaff_EDX + iVar3) < *(int *)(unaff_EDX + iVar1)) goto LAB_00042e1a;
        if (*(int *)(unaff_EBX + iVar1) < *(int *)(unaff_EBX + iVar3)) goto LAB_00042e00;
        if (*(int *)(unaff_EBX + iVar3) < *(int *)(unaff_EBX + iVar1)) goto LAB_00042e1a;
        if (*(int *)(unaff_ECX + iVar1) < *(int *)(unaff_ECX + iVar3)) goto LAB_00042e00;
        if (*(int *)(unaff_ECX + iVar1) <= *(int *)(unaff_ECX + iVar3)) {
          if (*(int *)(iVar3 + param_5) <= *(int *)(param_5 + iVar1)) {
            if (*(int *)(iVar3 + param_5) < *(int *)(param_5 + iVar1)) goto LAB_00042e00;
            iVar3 = *(int *)(param_1 + iVar3);
            iVar1 = *(int *)(param_1 + iVar1);
            if (iVar1 < iVar3) {
              iVar1 = iVar3;
            }
            goto LAB_00042eab;
          }
        }
LAB_00042e1a:
        iVar1 = *(int *)(param_1 + iVar1);
      }
LAB_00042eab:
      if (iVar1 == *(int *)(iVar2 * 4 + param_1)) {
        sub_42f19(iVar4,iVar2,param_1);
        sub_42f19(iVar4,iVar2,unaff_EDX);
        sub_42f19(iVar4,iVar2,unaff_EBX);
        sub_42f19(iVar4,iVar2,unaff_ECX);
        sub_42f19(iVar4,iVar2,param_5);
      }
    }
    iVar4 = iVar4 + 1;
  } while( true );
}


// ================================================================================================
// sub_42f19 @ 0x42f19 [__watcall]
// ================================================================================================

void __watcall sub_42f19(int param_1,int unaff_EDX,int unaff_EBX)

{
  uint uVar1;
  uint *puVar2;
  uint *puVar3;
  uint uVar4;
  
  __CHK(0xc);
  puVar2 = (uint *)(param_1 * 4 + unaff_EBX);
  puVar3 = (uint *)(unaff_EDX * 4 + unaff_EBX);
  uVar4 = *puVar3;
  uVar1 = *puVar2;
  *puVar2 = uVar1 ^ uVar4;
  uVar4 = *puVar3 ^ uVar1 ^ uVar4;
  *puVar3 = uVar4;
  *puVar2 = *puVar2 ^ uVar4;
  return;
}


// ================================================================================================
// sub_42f42 @ 0x42f42 [__watcall]
// ================================================================================================

void __watcall sub_42f42(int param_1,int unaff_EDX,int unaff_EBX,int unaff_ECX)

{
  undefined uVar1;
  undefined uVar2;
  
  __CHK(8);
  uVar1 = (undefined)unaff_EDX;
  uVar2 = (undefined)unaff_EBX;
  if (((*(uint *)(&unk_c5519 + unaff_EDX * 4) | *(uint *)(&unk_c5519 + unaff_EBX * 4)) == 3) &&
     (unaff_ECX == 7)) {
    *(undefined *)(param_1 + 0x26) = uVar1;
    *(undefined *)(param_1 + 0x20) = uVar1;
    *(undefined *)(param_1 + 0x1b) = uVar1;
    *(undefined *)(param_1 + 0x15) = uVar1;
    *(undefined *)(param_1 + 0xf) = uVar1;
    *(undefined *)(param_1 + 8) = uVar1;
    *(undefined *)(param_1 + 2) = uVar1;
    *(undefined *)(param_1 + 0x27) = uVar2;
    *(undefined *)(param_1 + 0x21) = uVar2;
    *(undefined *)(param_1 + 0x1a) = uVar2;
  }
  else {
    if (unaff_ECX == 7) {
      *(undefined *)(param_1 + 0x26) = uVar1;
      *(undefined *)(param_1 + 0x21) = uVar1;
      *(undefined *)(param_1 + 0x1a) = uVar1;
      *(undefined *)(param_1 + 0x15) = uVar1;
      *(undefined *)(param_1 + 0xf) = uVar1;
      *(undefined *)(param_1 + 8) = uVar1;
      *(undefined *)(param_1 + 2) = uVar1;
      *(undefined *)(param_1 + 0x27) = uVar2;
      *(undefined *)(param_1 + 0x20) = uVar2;
    }
    else {
      if (unaff_ECX != 5) {
        if (unaff_ECX == 3) {
          *(undefined *)(param_1 + 0xe) = uVar1;
          *(undefined *)(param_1 + 9) = uVar1;
          *(undefined *)(param_1 + 2) = uVar1;
          *(undefined *)(param_1 + 0xf) = uVar2;
          *(undefined *)(param_1 + 8) = uVar2;
          *(undefined *)(param_1 + 3) = uVar2;
          return;
        }
        *(undefined *)(param_1 + 2) = uVar1;
        *(undefined *)(param_1 + 3) = uVar2;
        return;
      }
      *(undefined *)(param_1 + 0x1a) = uVar1;
      *(undefined *)(param_1 + 0x15) = uVar1;
      *(undefined *)(param_1 + 0xf) = uVar1;
      *(undefined *)(param_1 + 8) = uVar1;
      *(undefined *)(param_1 + 2) = uVar1;
    }
    *(undefined *)(param_1 + 0x1b) = uVar2;
  }
  *(undefined *)(param_1 + 0x14) = uVar2;
  *(undefined *)(param_1 + 0xe) = uVar2;
  *(undefined *)(param_1 + 9) = uVar2;
  *(undefined *)(param_1 + 3) = uVar2;
  return;
}


// ================================================================================================
// sub_42fed @ 0x42fed [__watcall]
// ================================================================================================

int __watcall
sub_42fed(undefined4 *param_1,int unaff_EDX,undefined4 unaff_EBX,int unaff_ECX,int param_5)

{
  int iVar1;
  undefined uVar2;
  int iVar3;
  undefined *puVar4;
  char cVar7;
  undefined *puVar5;
  undefined *puVar6;
  undefined *puVar8;
  undefined *puVar9;
  undefined *puVar10;
  undefined *puVar11;
  undefined *puVar12;
  undefined auStackY_5f8 [620];
  int local_38c [31];
  undefined auStackY_310 [620];
  int local_a4 [32];
  int local_24;
  
  __CHK(0x5fc);
  local_24 = 0;
  do {
    if ((*(char *)(param_1[local_24] * 0x1e + param_5 + 0x17) == '\x01') &&
       (iVar3 = db_read_record(unaff_EBX,auStackY_5f8,param_1[local_24]), iVar3 != 0)) {
      return iVar3;
    }
    if ((*(char *)(param_1[local_24 + 0xe] * 0x1e + param_5 + 0x17) == '\x01') &&
       (iVar3 = db_read_record(unaff_EBX,auStackY_310,param_1[local_24 + 0xe]), iVar3 != 0)) {
      return iVar3;
    }
    iVar3 = 0;
    do {
      local_a4[iVar3] = -1;
      local_38c[iVar3] = -1;
      iVar3 = iVar3 + 1;
    } while (iVar3 < 0x1c);
    if ((*(char *)(param_1[local_24] * 0x1e + param_5 + 0x17) == '\x01') &&
       (iVar3 = sub_3a2b8(unaff_EBX,auStackY_5f8), iVar3 != 0)) {
      return iVar3;
    }
    if ((*(char *)(param_1[local_24 + 0xe] * 0x1e + param_5 + 0x17) == '\x01') &&
       (iVar3 = sub_3a2b8(unaff_EBX,auStackY_310,param_1[local_24 + 0xe]), iVar3 != 0)) {
      return iVar3;
    }
    local_24 = local_24 + 1;
  } while (local_24 < 8);
  local_24 = 0;
  do {
    if ((*(char *)(param_1[local_24] * 0x1e + param_5 + 0x17) == '\x01') &&
       (iVar3 = db_read_record(unaff_EBX,auStackY_5f8,param_1[local_24]), iVar3 != 0)) {
      return iVar3;
    }
    if ((*(char *)(param_1[7 - local_24] * 0x1e + param_5 + 0x17) == '\x01') &&
       (iVar3 = db_read_record(unaff_EBX,auStackY_310,param_1[7 - local_24]), iVar3 != 0)) {
      return iVar3;
    }
    for (iVar3 = 0; iVar3 < unaff_ECX; iVar3 = iVar3 + 1) {
      iVar1 = (local_24 * 7 + 0x444 + iVar3) * 6 + 2;
      local_a4[iVar3] = iVar1;
      local_38c[iVar3] = iVar1;
    }
    if ((*(char *)(param_1[local_24] * 0x1e + param_5 + 0x17) == '\x01') &&
       (iVar3 = sub_3a2b8(unaff_EBX,auStackY_5f8), iVar3 != 0)) {
      return iVar3;
    }
    if ((*(char *)(param_1[7 - local_24] * 0x1e + param_5 + 0x17) == '\x01') &&
       (iVar3 = sub_3a2b8(unaff_EBX,auStackY_310,param_1[7 - local_24]), iVar3 != 0)) {
      return iVar3;
    }
    local_24 = local_24 + 1;
  } while (local_24 < 4);
  local_24 = 0;
  while( true ) {
    if ((*(char *)(param_1[local_24 + 0xe] * 0x1e + param_5 + 0x17) == '\x01') &&
       (iVar3 = db_read_record(unaff_EBX,auStackY_5f8,param_1[local_24 + 0xe]), iVar3 != 0)) {
      return iVar3;
    }
    if ((*(char *)(param_1[-local_24 + 0x15] * 0x1e + param_5 + 0x17) == '\x01') &&
       (iVar3 = db_read_record(unaff_EBX,auStackY_310,param_1[-local_24 + 0x15]), iVar3 != 0))
    break;
    for (iVar3 = 0; iVar3 < unaff_ECX; iVar3 = iVar3 + 1) {
      iVar1 = (local_24 * 7 + 0x460 + iVar3) * 6 + 2;
      local_a4[iVar3] = iVar1;
      local_38c[iVar3] = iVar1;
    }
    if ((*(char *)(param_1[local_24 + 0xe] * 0x1e + param_5 + 0x17) == '\x01') &&
       (iVar3 = sub_3a2b8(unaff_EBX,auStackY_5f8), iVar3 != 0)) {
      return iVar3;
    }
    if ((*(char *)(param_1[-local_24 + 0x15] * 0x1e + param_5 + 0x17) == '\x01') &&
       (iVar3 = sub_3a2b8(unaff_EBX,auStackY_310,param_1[-local_24 + 0x15]), iVar3 != 0)) {
      return iVar3;
    }
    local_24 = local_24 + 1;
    if (3 < local_24) {
      sub_42f42(unaff_EDX,*param_1,param_1[7],unaff_ECX);
      sub_42f42(unaff_EDX + 0x2a,param_1[1],param_1[6],unaff_ECX);
      sub_42f42(unaff_EDX + 0x54,param_1[2],param_1[5],unaff_ECX);
      sub_42f42(unaff_EDX + 0x7e,param_1[3],param_1[4],unaff_ECX);
      sub_42f42(unaff_EDX + 0xa8,param_1[0xe],param_1[0x15],unaff_ECX);
      sub_42f42(unaff_EDX + 0xd2,param_1[0xf],param_1[0x14],unaff_ECX);
      sub_42f42(unaff_EDX + 0xfc,param_1[0x10],param_1[0x13],unaff_ECX);
      sub_42f42(unaff_EDX + 0x126,param_1[0x11],param_1[0x12],unaff_ECX);
      for (local_24 = 0; local_24 < unaff_ECX; local_24 = local_24 + 1) {
        puVar8 = (undefined *)(unaff_EDX + (local_24 + 0x31) * 6);
        *puVar8 = 4;
        uVar2 = *puVar8;
        puVar4 = (undefined *)((local_24 + 0x2a) * 6 + unaff_EDX);
        *puVar4 = uVar2;
        puVar10 = (undefined *)(unaff_EDX + (local_24 + 0x23) * 6);
        *puVar10 = uVar2;
        puVar5 = (undefined *)(unaff_EDX + (local_24 + 0x1c) * 6);
        *puVar5 = uVar2;
        puVar12 = (undefined *)(unaff_EDX + (local_24 + 0x15) * 6);
        *puVar12 = uVar2;
        puVar9 = (undefined *)((local_24 + 0xe) * 6 + unaff_EDX);
        *puVar9 = uVar2;
        puVar6 = (undefined *)(unaff_EDX + (local_24 + 7) * 6);
        *puVar6 = uVar2;
        puVar11 = (undefined *)(local_24 * 6 + unaff_EDX);
        *puVar11 = uVar2;
        cVar7 = (char)local_24 * '\x02' + '\x11';
        puVar12[1] = cVar7;
        puVar9[1] = cVar7;
        puVar6[1] = cVar7;
        puVar11[1] = cVar7;
        cVar7 = (char)local_24 * '\x02' + '\x10';
        puVar8[1] = cVar7;
        puVar4[1] = cVar7;
        puVar10[1] = cVar7;
        puVar5[1] = cVar7;
      }
      return 0;
    }
  }
  return iVar3;
}


// ================================================================================================
// sub_43644 @ 0x43644 [__watcall]
// ================================================================================================

undefined4 __watcall sub_43644(int param_1,undefined4 param_2,undefined4 unaff_EBX)

{
  undefined4 *puVar1;
  int *piVar2;
  undefined4 *puVar3;
  undefined uVar4;
  byte bVar5;
  int iVar6;
  int iVar7;
  undefined *puVar8;
  int iVar10;
  undefined auStackY_84 [104];
  undefined4 *puVar9;
  
  __CHK(0x94);
  puVar8 = auStackY_84;
  _memset_dwords(auStackY_84,0,unaff_EBX,0x1a);
  iVar6 = sub_42221(param_1);
  do {
    for (iVar10 = 0; iVar10 < iVar6; iVar10 = iVar10 + 1) {
      iVar7 = iVar6 / 2 + 1;
      if ((iVar7 == *(int *)(puVar8 + (uint)*(byte *)(param_1 + 2) * 4)) ||
         (iVar7 == *(int *)(puVar8 + (uint)*(byte *)(param_1 + 3) * 4))) {
        *(undefined *)(param_1 + 3 + iVar10 * 6) = 0xff;
        uVar4 = *(undefined *)(param_1 + 3 + iVar10 * 6);
        *(undefined *)(param_1 + 2 + iVar10 * 6) = uVar4;
        *(undefined *)(param_1 + 1 + iVar10 * 6) = uVar4;
        *(undefined *)(param_1 + iVar10 * 6) = uVar4;
      }
      else {
        if (*(char *)(param_1 + iVar10 * 6 + 4) == -1) {
          *(undefined4 *)(puVar8 + -4) = 2;
          *(undefined4 *)(puVar8 + -8) = *(undefined4 *)(puVar8 + 0x68);
          *(undefined4 *)(puVar8 + -0xc) = *(undefined4 *)(puVar8 + 0x70);
          piVar2 = (int *)(puVar8 + 0x74);
          puVar3 = (undefined4 *)(puVar8 + 0x88);
          puVar1 = (undefined4 *)(puVar8 + 0x6c);
          puVar9 = (undefined4 *)(puVar8 + -0x10);
          puVar8 = puVar8 + -0x10;
          *puVar9 = 0x4370b;
          playoff_setup_screen(*puVar1,*puVar3,*piVar2 * 7 + 0x444 + iVar10);
        }
        iVar7 = iVar10 * 6 + param_1;
        if (*(byte *)(iVar7 + 5) < *(byte *)(iVar7 + 4)) {
          bVar5 = *(byte *)(iVar7 + 2);
        }
        else {
          bVar5 = *(byte *)(iVar7 + 3);
        }
        *(int *)(puVar8 + (uint)bVar5 * 4) = *(int *)(puVar8 + (uint)bVar5 * 4) + 1;
      }
    }
    iVar10 = *(int *)(puVar8 + 0x74);
    *(int *)(puVar8 + 0x74) = iVar10 + 1;
    param_1 = param_1 + 0x2a;
  } while (iVar10 + 1 < 8);
  return 0;
}


// ================================================================================================
// sub_43757 @ 0x43757 [__watcall]
// ================================================================================================

int __watcall
sub_43757(int param_1,int unaff_EDX,undefined4 unaff_EBX,int unaff_ECX,undefined4 *param_5)

{
  undefined *puVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  undefined *puVar6;
  undefined auStackY_610 [648];
  int aiStackY_388 [24];
  undefined auStackY_328 [648];
  int aiStackY_a0 [24];
  uint local_40 [8];
  int local_20;
  char local_18 [4];
  undefined local_14 [4];
  undefined uStackY_10;
  
  __CHK(0x618);
  local_20 = sub_42221();
  iVar5 = local_20;
  do {
    iVar4 = iVar5 + -1;
    if (iVar4 < 0) goto LAB_0004385f;
    puVar6 = (undefined *)(iVar4 * 6 + param_1);
    if ((((puVar6[4] != -1) || (puVar6 = (undefined *)((iVar5 + 6) * 6 + param_1), puVar6[4] != -1))
        || (puVar6 = (undefined *)((iVar5 + 0xd) * 6 + param_1), puVar6[4] != -1)) ||
       (puVar6 = (undefined *)((iVar5 + 0x14) * 6 + param_1), puVar6[4] != -1)) {
      local_14[0] = *puVar6;
      local_18[0] = puVar6[1] + '\x01';
      goto LAB_0004385f;
    }
    puVar6 = (undefined *)((iVar5 + 0x1b) * 6 + param_1);
  } while (((puVar6[4] == -1) &&
           (puVar6 = (undefined *)((iVar5 + 0x22) * 6 + param_1), puVar6[4] == -1)) &&
          ((puVar6 = (undefined *)((iVar5 + 0x29) * 6 + param_1), puVar6[4] == -1 &&
           (puVar6 = (undefined *)((iVar5 + 0x30) * 6 + param_1), iVar5 = iVar4, puVar6[4] == -1))))
  ;
  local_14[0] = *puVar6;
  local_18[0] = puVar6[1];
LAB_0004385f:
  for (iVar5 = 0; iVar5 < unaff_EDX; iVar5 = iVar5 + 1) {
    sub_41c9b(local_14,local_18);
    puVar6 = (undefined *)((iVar5 + 0x4d) * 6 + param_1);
    *puVar6 = local_14[0];
    uStackY_10 = local_14[0];
    puVar1 = (undefined *)((iVar5 + 0x46) * 6 + param_1);
    *puVar1 = local_14[0];
    puVar6[1] = local_18[0];
    puVar1[1] = local_18[0];
    local_18[0] = local_18[0] + '\x01';
    sub_41c9b(local_14,local_18);
    puVar6 = (undefined *)((iVar5 + 0x3f) * 6 + param_1);
    *puVar6 = local_14[0];
    uStackY_10 = local_14[0];
    puVar1 = (undefined *)((iVar5 + 0x38) * 6 + param_1);
    *puVar1 = local_14[0];
    puVar6[1] = local_18[0];
    puVar1[1] = local_18[0];
    local_18[0] = local_18[0] + '\x01';
  }
  _memset_dwords(local_40,0xffffffff);
  uVar3 = sub_87760(param_1,local_20);
  if (uVar3 == *(byte *)(param_1 + 2)) {
    local_40[0] = (uint)*(byte *)(param_1 + 2);
    uVar3 = local_40[7];
  }
  local_40[7] = uVar3;
  uVar3 = sub_87760(param_1 + 0x2a,local_20);
  if (uVar3 == *(byte *)(param_1 + 0x2c)) {
    local_40[1] = (uint)*(byte *)(param_1 + 0x2c);
    uVar3 = local_40[6];
  }
  local_40[6] = uVar3;
  uVar3 = sub_87760(param_1 + 0x54,local_20);
  if (uVar3 == *(byte *)(param_1 + 0x56)) {
    local_40[2] = (uint)*(byte *)(param_1 + 0x56);
    uVar3 = local_40[5];
  }
  local_40[5] = uVar3;
  uVar3 = sub_87760(param_1 + 0x7e,local_20);
  if (uVar3 == *(byte *)(param_1 + 0x80)) {
    local_40[3] = (uint)*(byte *)(param_1 + 0x80);
  }
  else {
    local_40[4] = uVar3;
  }
  iVar5 = 0;
  for (iVar4 = 0; iVar4 < 8; iVar4 = iVar4 + 1) {
    uVar3 = local_40[iVar4];
    if ((-1 < (int)uVar3) && ((int)uVar3 < 0x1a)) {
      local_40[iVar5] = uVar3;
      iVar5 = iVar5 + 1;
    }
  }
  sub_42f42(param_1 + 0x150,local_40[0],local_40[3],unaff_EDX);
  sub_42f42(param_1 + 0x17a,local_40[1],local_40[2]);
  *param_5 = 0;
  iVar5 = 0;
  do {
    if (*(char *)(local_40[iVar5] * 0x1e + unaff_ECX + 0x17) == '\x01') {
      *param_5 = 1;
      iVar4 = db_read_record(unaff_EBX,auStackY_610,local_40[iVar5]);
      if (iVar4 != 0) {
        return iVar4;
      }
    }
    if (*(char *)(local_40[3 - iVar5] * 0x1e + unaff_ECX + 0x17) == '\x01') {
      *param_5 = 1;
      iVar4 = db_read_record(unaff_EBX,auStackY_328,local_40[3 - iVar5]);
      if (iVar4 != 0) {
        return iVar4;
      }
    }
    for (iVar4 = 0; iVar4 < unaff_EDX; iVar4 = iVar4 + 1) {
      iVar2 = (iVar5 * 7 + 0x47c + iVar4) * 6 + 2;
      aiStackY_a0[iVar4] = iVar2;
      aiStackY_388[iVar4] = iVar2;
    }
    if ((*(char *)(local_40[iVar5] * 0x1e + unaff_ECX + 0x17) == '\x01') &&
       (iVar4 = sub_3a2b8(unaff_EBX,auStackY_610,local_40[iVar5]), iVar4 != 0)) {
      return iVar4;
    }
    if ((*(char *)(local_40[3 - iVar5] * 0x1e + unaff_ECX + 0x17) == '\x01') &&
       (iVar4 = sub_3a2b8(unaff_EBX,auStackY_328,local_40[3 - iVar5]), iVar4 != 0)) {
      return iVar4;
    }
    iVar5 = iVar5 + 1;
  } while (iVar5 < 2);
  _memset_dwords(local_40,0xffffffff);
  uVar3 = sub_87760(param_1 + 0xa8,local_20);
  if (uVar3 == *(byte *)(param_1 + 0xaa)) {
    local_40[0] = (uint)*(byte *)(param_1 + 0xaa);
    uVar3 = local_40[7];
  }
  local_40[7] = uVar3;
  uVar3 = sub_87760(param_1 + 0xd2,local_20);
  if (uVar3 == *(byte *)(param_1 + 0xd4)) {
    local_40[1] = (uint)*(byte *)(param_1 + 0xd4);
    uVar3 = local_40[6];
  }
  local_40[6] = uVar3;
  uVar3 = sub_87760(param_1 + 0xfc,local_20);
  if (uVar3 == *(byte *)(param_1 + 0xfe)) {
    local_40[2] = (uint)*(byte *)(param_1 + 0xfe);
    uVar3 = local_40[5];
  }
  local_40[5] = uVar3;
  uVar3 = sub_87760(param_1 + 0x126,local_20);
  if (uVar3 == *(byte *)(param_1 + 0x128)) {
    local_40[3] = (uint)*(byte *)(param_1 + 0x128);
  }
  else {
    local_40[4] = uVar3;
  }
  iVar5 = 0;
  for (iVar4 = 0; iVar4 < 8; iVar4 = iVar4 + 1) {
    uVar3 = local_40[iVar4];
    if ((-1 < (int)uVar3) && ((int)uVar3 < 0x1a)) {
      local_40[iVar5] = uVar3;
      iVar5 = iVar5 + 1;
    }
  }
  sub_42f42(param_1 + 0x1a4,local_40[0],local_40[3],unaff_EDX);
  sub_42f42(param_1 + 0x1ce,local_40[1],local_40[2]);
  iVar5 = 0;
  while( true ) {
    if (*(char *)(local_40[iVar5] * 0x1e + unaff_ECX + 0x17) == '\x01') {
      *param_5 = 1;
      iVar4 = db_read_record(unaff_EBX,auStackY_610,local_40[iVar5]);
      if (iVar4 != 0) {
        return iVar4;
      }
    }
    if (*(char *)(local_40[3 - iVar5] * 0x1e + unaff_ECX + 0x17) == '\x01') {
      *param_5 = 1;
      iVar4 = db_read_record(unaff_EBX,auStackY_328,local_40[3 - iVar5]);
      if (iVar4 != 0) {
        return iVar4;
      }
    }
    for (iVar4 = 0; iVar4 < unaff_EDX; iVar4 = iVar4 + 1) {
      iVar2 = (iVar5 * 7 + 0x48a + iVar4) * 6 + 2;
      aiStackY_a0[iVar4] = iVar2;
      aiStackY_388[iVar4] = iVar2;
    }
    if ((*(char *)(local_40[iVar5] * 0x1e + unaff_ECX + 0x17) == '\x01') &&
       (iVar4 = sub_3a2b8(unaff_EBX,auStackY_610,local_40[iVar5]), iVar4 != 0)) break;
    if ((*(char *)(local_40[3 - iVar5] * 0x1e + unaff_ECX + 0x17) == '\x01') &&
       (iVar4 = sub_3a2b8(unaff_EBX,auStackY_328,local_40[3 - iVar5]), iVar4 != 0)) {
      return iVar4;
    }
    iVar5 = iVar5 + 1;
    if (1 < iVar5) {
      return 0;
    }
  }
  return iVar4;
}


// ================================================================================================
// sub_43e40 @ 0x43e40 [__watcall]
// ================================================================================================

undefined4 __watcall sub_43e40(int param_1,undefined4 param_2,undefined4 unaff_EBX)

{
  int *piVar1;
  undefined4 *puVar2;
  undefined uVar3;
  byte bVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  undefined4 *puVar8;
  int iVar10;
  undefined auStackY_78 [104];
  undefined4 uStackY_10;
  undefined4 *puVar9;
  
  __CHK(0x94);
  puVar8 = (undefined4 *)&stack0xffffff7c;
  param_1 = param_1 + 0x150;
  _memset_dwords(auStackY_78,0,unaff_EBX,0x1a);
  iVar6 = sub_42221(param_1);
  uStackY_10 = 0;
  do {
    for (iVar10 = 0; iVar10 < iVar6; iVar10 = iVar10 + 1) {
      iVar7 = iVar6 / 2 + 1;
      if ((iVar7 == puVar8[*(byte *)(param_1 + 2) + 3]) ||
         (iVar7 == puVar8[*(byte *)(param_1 + 3) + 3])) {
        *(undefined *)(param_1 + 2 + iVar10 * 6) = 0xff;
        uVar3 = *(undefined *)(param_1 + 2 + iVar10 * 6);
        *(undefined *)(param_1 + 3 + iVar10 * 6) = uVar3;
        *(undefined *)(param_1 + 1 + iVar10 * 6) = uVar3;
        *(undefined *)(param_1 + iVar10 * 6) = uVar3;
      }
      else {
        if (*(char *)(param_1 + iVar10 * 6 + 4) == -1) {
          puVar8[-1] = 2;
          puVar8[-2] = puVar8[1];
          puVar8[-3] = puVar8[2];
          piVar1 = puVar8 + 0x1d;
          puVar2 = puVar8 + 0x22;
          uVar5 = *puVar8;
          puVar9 = puVar8 + -4;
          puVar8 = puVar8 + -4;
          *puVar9 = 0x43f04;
          playoff_setup_screen(uVar5,*puVar2,*piVar1 * 7 + 0x47c + iVar10);
        }
        iVar7 = iVar10 * 6 + param_1;
        if (*(byte *)(iVar7 + 5) < *(byte *)(iVar7 + 4)) {
          bVar4 = *(byte *)(iVar7 + 2);
        }
        else {
          bVar4 = *(byte *)(iVar7 + 3);
        }
        *(int *)((int)puVar8 + (uint)bVar4 * 4 + 0xc) =
             *(int *)((int)puVar8 + (uint)bVar4 * 4 + 0xc) + 1;
      }
    }
    iVar10 = puVar8[0x1d];
    puVar8[0x1d] = iVar10 + 1;
    param_1 = param_1 + 0x2a;
  } while (iVar10 + 1 < 4);
  return 0;
}


// ================================================================================================
// sub_43f4b @ 0x43f4b [__watcall]
// ================================================================================================

int __watcall
sub_43f4b(int param_1,int unaff_EDX,undefined4 unaff_EBX,int unaff_ECX,undefined4 *param_5)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  undefined *puVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  undefined auStackY_600 [676];
  int aiStackY_35c [17];
  undefined auStackY_318 [676];
  int aiStackY_74 [17];
  int local_30;
  int local_2c;
  uint local_28;
  uint local_24;
  char local_14 [4];
  undefined auStackY_10 [4];
  
  __CHK(0x608);
  iVar3 = param_1 + 0x150;
  local_2c = sub_42221(iVar3);
  iVar7 = local_2c;
  do {
    iVar6 = iVar7 + -1;
    if (iVar6 < 0) goto LAB_00044001;
    puVar4 = (undefined *)(iVar3 + iVar6 * 6);
    if ((puVar4[4] != -1) || (puVar4 = (undefined *)(iVar3 + (iVar7 + 6) * 6), puVar4[4] != -1)) {
      auStackY_10[0] = *puVar4;
      local_14[0] = puVar4[1] + '\x01';
      goto LAB_00044001;
    }
    puVar4 = (undefined *)(iVar3 + (iVar7 + 0xd) * 6);
  } while ((puVar4[4] == -1) &&
          (puVar4 = (undefined *)(iVar3 + (iVar7 + 0x14) * 6), iVar7 = iVar6, puVar4[4] == -1));
  auStackY_10[0] = *puVar4;
  local_14[0] = puVar4[1];
LAB_00044001:
  for (iVar7 = 0; iVar7 < unaff_EDX; iVar7 = iVar7 + 1) {
    sub_41c9b(auStackY_10,local_14);
    puVar4 = (undefined *)(iVar3 + (iVar7 + 0x23) * 6);
    *puVar4 = auStackY_10[0];
    puVar4[1] = local_14[0];
    local_14[0] = local_14[0] + '\x01';
    sub_41c9b(auStackY_10,local_14);
    puVar4 = (undefined *)(iVar3 + (iVar7 + 0x1c) * 6);
    *puVar4 = auStackY_10[0];
    puVar4[1] = local_14[0];
    local_14[0] = local_14[0] + '\x01';
  }
  uVar1 = sub_87760(iVar3,local_2c);
  local_28 = uVar1;
  uVar2 = sub_87760(param_1 + 0x17a,local_2c);
  local_30 = param_1 + 0x1f8;
  uVar5 = uVar2;
  uVar8 = local_28;
  if (*(byte *)(param_1 + 0x152) == local_28) {
    uVar5 = (uint)*(byte *)(param_1 + 0x152);
    uVar8 = uVar2;
  }
  sub_42f42(local_30,uVar5,uVar8,unaff_EDX);
  *param_5 = 0;
  if (*(char *)(uVar1 * 0x1e + unaff_ECX + 0x17) == '\x01') {
    *param_5 = 1;
    iVar3 = db_read_record(unaff_EBX,auStackY_318,uVar1);
    if (iVar3 != 0) {
      return iVar3;
    }
  }
  if (*(char *)(uVar2 * 0x1e + unaff_ECX + 0x17) == '\x01') {
    *param_5 = 1;
    iVar3 = db_read_record(unaff_EBX,auStackY_600);
    if (iVar3 != 0) {
      return iVar3;
    }
  }
  for (iVar3 = 0; iVar3 < unaff_EDX; iVar3 = iVar3 + 1) {
    iVar7 = (iVar3 + 0x498) * 6 + 2;
    aiStackY_35c[iVar3] = iVar7;
    aiStackY_74[iVar3] = iVar7;
  }
  if (((*(char *)(uVar1 * 0x1e + unaff_ECX + 0x17) != '\x01') ||
      (iVar3 = sub_3a2b8(unaff_EBX,auStackY_318,uVar1), iVar3 == 0)) &&
     ((*(char *)(uVar2 * 0x1e + unaff_ECX + 0x17) != '\x01' ||
      (iVar3 = sub_3a2b8(unaff_EBX,auStackY_600,uVar2), iVar3 == 0)))) {
    uVar1 = sub_87760(param_1 + 0x1a4,local_2c);
    local_24 = uVar1;
    uVar2 = sub_87760(param_1 + 0x1ce,local_2c);
    uVar5 = uVar2;
    uVar8 = local_24;
    if (*(byte *)(param_1 + 0x1a6) == local_24) {
      uVar5 = (uint)*(byte *)(param_1 + 0x1a6);
      uVar8 = uVar2;
    }
    sub_42f42(param_1 + 0x222,uVar5,uVar8,unaff_EDX);
    if (*(char *)(uVar1 * 0x1e + unaff_ECX + 0x17) == '\x01') {
      *param_5 = 1;
      iVar3 = db_read_record(unaff_EBX,auStackY_318,uVar1);
      if (iVar3 != 0) {
        return iVar3;
      }
    }
    if (*(char *)(uVar2 * 0x1e + unaff_ECX + 0x17) == '\x01') {
      *param_5 = 1;
      iVar3 = db_read_record(unaff_EBX,auStackY_600,uVar2);
      if (iVar3 != 0) {
        return iVar3;
      }
    }
    for (iVar3 = 0; iVar3 < unaff_EDX; iVar3 = iVar3 + 1) {
      iVar7 = (iVar3 + 0x49f) * 6 + 2;
      aiStackY_35c[iVar3] = iVar7;
      aiStackY_74[iVar3] = iVar7;
    }
    if (((*(char *)(uVar1 * 0x1e + unaff_ECX + 0x17) != '\x01') ||
        (iVar3 = sub_3a2b8(unaff_EBX,auStackY_318,uVar1), iVar3 == 0)) &&
       ((*(char *)(uVar2 * 0x1e + unaff_ECX + 0x17) != '\x01' ||
        (iVar3 = sub_3a2b8(unaff_EBX,auStackY_600,uVar2), iVar3 == 0)))) {
      iVar3 = 0;
    }
  }
  return iVar3;
}


// ================================================================================================
// sub_443b6 @ 0x443b6 [__watcall]
// ================================================================================================

undefined4 __watcall sub_443b6(int param_1,undefined4 param_2,undefined4 unaff_EBX)

{
  int *piVar1;
  undefined4 *puVar2;
  undefined uVar3;
  byte bVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  undefined4 *puVar8;
  int iVar10;
  undefined auStackY_78 [104];
  undefined4 uStackY_10;
  undefined4 *puVar9;
  
  __CHK(0x94);
  puVar8 = (undefined4 *)&stack0xffffff7c;
  param_1 = param_1 + 0x1f8;
  _memset_dwords(auStackY_78,0,unaff_EBX,0x1a);
  iVar6 = sub_42221(param_1);
  uStackY_10 = 0;
  do {
    for (iVar10 = 0; iVar10 < iVar6; iVar10 = iVar10 + 1) {
      iVar7 = iVar6 / 2 + 1;
      if ((iVar7 == puVar8[*(byte *)(param_1 + 2) + 3]) ||
         (iVar7 == puVar8[*(byte *)(param_1 + 3) + 3])) {
        *(undefined *)(param_1 + 5 + iVar10 * 6) = 0xff;
        uVar3 = *(undefined *)(param_1 + 5 + iVar10 * 6);
        *(undefined *)(param_1 + 4 + iVar10 * 6) = uVar3;
        *(undefined *)(param_1 + 3 + iVar10 * 6) = uVar3;
        *(undefined *)(param_1 + 2 + iVar10 * 6) = uVar3;
        *(undefined *)(param_1 + 1 + iVar10 * 6) = uVar3;
        *(undefined *)(param_1 + iVar10 * 6) = uVar3;
      }
      else {
        if (*(char *)(param_1 + iVar10 * 6 + 4) == -1) {
          puVar8[-1] = 2;
          puVar8[-2] = puVar8[1];
          puVar8[-3] = puVar8[2];
          piVar1 = puVar8 + 0x1d;
          puVar2 = puVar8 + 0x22;
          uVar5 = *puVar8;
          puVar9 = puVar8 + -4;
          puVar8 = puVar8 + -4;
          *puVar9 = 0x44482;
          playoff_setup_screen(uVar5,*puVar2,*piVar1 * 7 + 0x498 + iVar10);
        }
        iVar7 = iVar10 * 6 + param_1;
        if (*(byte *)(iVar7 + 5) < *(byte *)(iVar7 + 4)) {
          bVar4 = *(byte *)(iVar7 + 2);
        }
        else {
          bVar4 = *(byte *)(iVar7 + 3);
        }
        *(int *)((int)puVar8 + (uint)bVar4 * 4 + 0xc) =
             *(int *)((int)puVar8 + (uint)bVar4 * 4 + 0xc) + 1;
      }
    }
    iVar10 = puVar8[0x1d];
    puVar8[0x1d] = iVar10 + 1;
    param_1 = param_1 + 0x2a;
  } while (iVar10 + 1 < 2);
  return 0;
}


// ================================================================================================
// sub_444c9 @ 0x444c9 [__watcall]
// ================================================================================================

int __watcall
sub_444c9(int param_1,int unaff_EDX,undefined4 unaff_EBX,int unaff_ECX,undefined4 param_5,
         undefined4 *param_6)

{
  undefined *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined auStack_628 [41];
  byte bStack_5ff;
  byte bStack_5fd;
  ushort uStack_5fc;
  ushort uStack_5fa;
  int aiStack_368 [10];
  undefined auStack_340 [41];
  byte bStack_317;
  byte bStack_315;
  ushort uStack_314;
  ushort uStack_312;
  int aiStack_80 [10];
  int local_58;
  int iStack_54;
  uint local_38;
  uint local_34;
  uint local_30;
  uint local_2c;
  uint local_28;
  uint local_24;
  int local_20;
  int local_1c;
  int local_18;
  char local_14 [4];
  undefined auStack_10 [4];
  
  __CHK(0x638);
  iVar2 = param_1 + 0x1f8;
  local_18 = sub_42221(iVar2);
  iVar4 = local_18;
  do {
    iVar3 = iVar4 + -1;
    if (iVar3 < 0) goto LAB_0004454d;
    puVar1 = (undefined *)(iVar2 + iVar3 * 6);
    if (puVar1[4] != -1) {
      auStack_10[0] = *puVar1;
      local_14[0] = puVar1[1];
      goto LAB_0004454d;
    }
    puVar1 = (undefined *)(iVar2 + (iVar4 + 6) * 6);
    iVar4 = iVar3;
  } while (puVar1[4] == -1);
  auStack_10[0] = *puVar1;
  local_14[0] = puVar1[1] + '\x01';
LAB_0004454d:
  for (iVar4 = 0; iVar4 < unaff_EDX; iVar4 = iVar4 + 1) {
    local_14[0] = local_14[0] + '\x02';
    sub_41c9b(auStack_10,local_14);
    puVar1 = (undefined *)(iVar2 + (iVar4 + 0xe) * 6);
    *puVar1 = auStack_10[0];
    puVar1[1] = local_14[0];
  }
  local_58 = sub_87760(iVar2,local_18);
  iStack_54 = sub_87760(param_1 + 0x222,local_18);
  *param_6 = 0;
  if (*(char *)(unaff_ECX + 0x17 + local_58 * 0x1e) == '\x01') {
    *param_6 = 1;
    iVar2 = db_read_record(unaff_EBX,auStack_628,local_58);
    if (iVar2 != 0) {
      return iVar2;
    }
  }
  if (*(char *)(unaff_ECX + 0x17 + iStack_54 * 0x1e) == '\x01') {
    *param_6 = 1;
    iVar2 = db_read_record(unaff_EBX,auStack_340,iStack_54);
    if (iVar2 != 0) {
      return iVar2;
    }
  }
  for (iVar2 = 0; iVar2 < unaff_EDX; iVar2 = iVar2 + 1) {
    iVar4 = (iVar2 + 0x4a6) * 6 + 2;
    aiStack_80[iVar2] = iVar4;
    aiStack_368[iVar2] = iVar4;
  }
  if (((*(char *)(unaff_ECX + 0x17 + local_58 * 0x1e) != '\x01') ||
      (iVar2 = sub_3a2b8(unaff_EBX,auStack_628,local_58), iVar2 == 0)) &&
     ((*(char *)(unaff_ECX + 0x17 + iStack_54 * 0x1e) != '\x01' ||
      (iVar2 = sub_3a2b8(unaff_EBX,auStack_340,iStack_54), iVar2 == 0)))) {
    local_30 = (uint)bStack_5ff;
    local_20 = local_30 * 2 + (uint)bStack_5fd;
    local_38 = (uint)uStack_5fc;
    local_28 = (uint)uStack_5fa;
    local_2c = (uint)bStack_317;
    local_1c = local_2c * 2 + (uint)bStack_315;
    local_34 = (uint)uStack_314;
    local_24 = (uint)uStack_312;
    sub_42daa(&local_58,&local_20,&local_30,&local_38,&local_28,2);
    sub_42f42(param_1 + 0x24c,local_58,iStack_54,unaff_EDX);
    iVar2 = 0;
  }
  return iVar2;
}


// ================================================================================================
// sub_447a6 @ 0x447a6 [__watcall]
// ================================================================================================

undefined4 __watcall sub_447a6(int param_1,undefined4 param_2,undefined4 unaff_EBX)

{
  int iVar1;
  undefined4 *puVar2;
  undefined uVar3;
  byte bVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  undefined4 *puVar8;
  int iVar10;
  undefined auStackY_74 [104];
  undefined4 *puVar9;
  
  __CHK(0x90);
  puVar8 = (undefined4 *)&stack0xffffff80;
  iVar1 = param_1 + 0x24c;
  _memset_dwords(auStackY_74,0,unaff_EBX,0x1a);
  iVar6 = sub_42221(iVar1);
  for (iVar10 = 0; iVar10 < iVar6; iVar10 = iVar10 + 1) {
    iVar7 = iVar6 / 2 + 1;
    if ((iVar7 == puVar8[*(byte *)(param_1 + 0x24e) + 3]) ||
       (iVar7 == puVar8[*(byte *)(param_1 + 0x24f) + 3])) {
      *(undefined *)(param_1 + 0x24f + iVar10 * 6) = 0xff;
      uVar3 = *(undefined *)(param_1 + 0x24f + iVar10 * 6);
      *(undefined *)(param_1 + 0x24e + iVar10 * 6) = uVar3;
      *(undefined *)(param_1 + 0x24d + iVar10 * 6) = uVar3;
      *(undefined *)(iVar1 + iVar10 * 6) = uVar3;
    }
    else {
      if (*(char *)(iVar1 + iVar10 * 6 + 4) == -1) {
        puVar8[-1] = 2;
        puVar8[-2] = puVar8[1];
        puVar8[-3] = puVar8[2];
        puVar2 = puVar8 + 0x21;
        uVar5 = *puVar8;
        puVar9 = puVar8 + -4;
        puVar8 = puVar8 + -4;
        *puVar9 = 0x44852;
        playoff_setup_screen(uVar5,*puVar2,iVar10 + 0x4a6);
      }
      iVar7 = iVar10 * 6 + iVar1;
      if (*(byte *)(iVar7 + 5) < *(byte *)(iVar7 + 4)) {
        bVar4 = *(byte *)(iVar7 + 2);
      }
      else {
        bVar4 = *(byte *)(iVar7 + 3);
      }
      *(int *)((int)puVar8 + (uint)bVar4 * 4 + 0xc) =
           *(int *)((int)puVar8 + (uint)bVar4 * 4 + 0xc) + 1;
    }
  }
  return 0;
}


// ================================================================================================
// sub_44899 @ 0x44899 [__watcall]
// ================================================================================================

int __watcall
sub_44899(undefined4 param_1,undefined4 param_2,undefined4 unaff_EBX,undefined4 unaff_ECX,
         undefined4 param_5,undefined4 param_6,undefined4 param_7)

{
  int iVar1;
  undefined auStack_34 [32];
  undefined auStack_14 [4];
  undefined4 local_10;
  
  __CHK(0x48);
  switch(param_7) {
  case 2:
    iVar1 = sub_43644(dword_c8c61,param_2,unaff_EBX,param_5,param_6);
    if (iVar1 != 0) {
      return iVar1;
    }
    iVar1 = sub_43757(dword_c8c61,(uint)(option_flags << 0x11) >> 0x1d,param_2,unaff_ECX,auStack_14)
    ;
    if (iVar1 != 0) {
      return iVar1;
    }
switchD_000448c0_caseD_3:
    iVar1 = sub_43e40(dword_c8c61,param_2,unaff_EBX,param_5,param_6);
    if ((iVar1 == 0) &&
       (iVar1 = sub_43f4b(dword_c8c61,(uint)(option_flags << 0x11) >> 0x1d,param_2,unaff_ECX,
                          auStack_14), iVar1 == 0)) {
switchD_000448c0_caseD_4:
      iVar1 = sub_443b6(dword_c8c61,param_2,unaff_EBX,param_5,param_6);
      if ((iVar1 == 0) &&
         (iVar1 = sub_444c9(dword_c8c61,(uint)(option_flags << 0x11) >> 0x1d,param_2,unaff_ECX,
                            param_1,auStack_14), iVar1 == 0)) {
switchD_000448c0_caseD_5:
        iVar1 = sub_447a6(dword_c8c61,param_2,unaff_EBX,param_5,param_6);
        if ((iVar1 == 0) && (iVar1 = file_write(param_1,dword_c8c61,0x199a,0x276), iVar1 == 0)) {
          make_path(auStack_34,param_5,off_c80eb,param_6);
          savefile(auStack_34,dword_d07bb,dword_d07d3);
          awards_screen();
          byte_de268 = 0xff;
          local_10 = 0x4ad;
          iVar1 = file_write(param_1,&local_10,0,2);
        }
      }
    }
    return iVar1;
  case 3:
    goto switchD_000448c0_caseD_3;
  case 4:
    goto switchD_000448c0_caseD_4;
  case 5:
    goto switchD_000448c0_caseD_5;
  default:
    return -1;
  }
}


// ================================================================================================
// schedule_screen2 @ 0x44a41 [__watcall]
// ================================================================================================

int __watcall
schedule_screen2(undefined4 param_1,undefined4 param_2,undefined4 param_3,int unaff_ECX,
                undefined4 param_5,undefined4 param_6,int param_7,int param_8)

{
  int iVar1;
  short sVar2;
  int iVar3;
  undefined4 uVar4;
  undefined auStack_44 [32];
  char local_24;
  char cStack_23;
  byte bStack_22;
  byte bStack_21;
  char local_20;
  char cStack_1f;
  int local_1c;
  undefined4 uStack_10;
  
  __CHK(0x54);
  local_1c = 0;
  iVar3 = 0;
  iVar1 = 0;
  while (((iVar1 < 0x69 && (iVar3 == 0)) && (local_1c == 0))) {
    iVar3 = db_read_record2(param_1,&local_24);
    if (((((bStack_22 != 0xff) && (bStack_21 != 0xff)) &&
         ((*(char *)(unaff_ECX + 0x17 + (uint)bStack_22 * 0x1e) == '\x01' ||
          (*(char *)(unaff_ECX + 0x17 + (uint)bStack_21 * 0x1e) == '\x01')))) &&
        ((local_24 != -1 && (cStack_23 != -1)))) && ((local_20 == -1 || (cStack_1f == -1)))) {
      local_1c = 1;
    }
    iVar1 = iVar1 + 1;
  }
  if ((((iVar3 == 0) && (local_1c == 0)) && (param_8 == 7)) && (param_7 == -1)) {
    iVar3 = file_read(param_1,&uStack_10,0,2);
    if (iVar3 != 0) {
      return iVar3;
    }
    dword_c8c61 = allocmem(&aSch,0x276,0x20);
    iVar3 = file_read(param_1,dword_c8c61,0x199a,0x276);
    if (iVar3 != 0) goto LAB_00044da9;
    sVar2 = (short)uStack_10;
    if (sVar2 < 0x47c) {
      uStack_10 = 0x47c;
      iVar3 = sub_43644(dword_c8c61,param_2,param_3,param_5,param_6);
      if ((iVar3 != 0) ||
         (iVar3 = sub_43757(dword_c8c61,(uint)(option_flags << 0x11) >> 0x1d,param_2,unaff_ECX,
                            &local_1c), iVar3 != 0)) goto LAB_00044da9;
      if (local_1c == 0) {
        uVar4 = 3;
LAB_00044be1:
        sub_44899(param_1,param_2,param_3,unaff_ECX,param_5,param_6,uVar4);
      }
    }
    else if (sVar2 < 0x498) {
      uStack_10 = 0x498;
      iVar3 = sub_43e40(dword_c8c61,param_2,param_3,param_5,param_6);
      if ((iVar3 != 0) ||
         (iVar3 = sub_43f4b(dword_c8c61,(uint)(option_flags << 0x11) >> 0x1d,param_2,unaff_ECX,
                            &local_1c), iVar3 != 0)) goto LAB_00044da9;
      if (local_1c == 0) {
        uVar4 = 4;
        goto LAB_00044be1;
      }
    }
    else if (sVar2 < 0x4a6) {
      uStack_10 = 0x4a6;
      iVar3 = sub_443b6(dword_c8c61,param_2,param_3,param_5,param_6);
      if ((iVar3 != 0) ||
         (iVar3 = sub_444c9(dword_c8c61,(uint)(option_flags << 0x11) >> 0x1d,param_2,unaff_ECX,
                            param_1,&local_1c), iVar3 != 0)) goto LAB_00044da9;
      if (local_1c == 0) {
        sub_44899(param_1,param_2,param_3,unaff_ECX,param_5,param_6,5);
        uStack_10 = 0x4ad;
      }
    }
    else if (sVar2 < 0x4ad) {
      uStack_10 = 0x4ad;
      iVar3 = sub_447a6(dword_c8c61,param_2,param_3,param_5,param_6);
      if (iVar3 != 0) goto LAB_00044da9;
      make_path(auStack_44,param_5,off_c80eb,param_6);
      savefile(auStack_44,dword_d07bb,dword_d07d3);
      awards_screen();
      byte_de268 = 0xff;
    }
    iVar3 = file_write(param_1,&uStack_10,0,2);
    if (iVar3 != 0) goto LAB_00044da9;
  }
  if (dword_c8c61 != 0) {
    iVar3 = file_write(param_1,dword_c8c61,0x199a,0x276);
  }
LAB_00044da9:
  if (dword_c8c61 != 0) {
    freemem(dword_c8c61);
    dword_c8c61 = 0;
  }
  return iVar3;
}


// ================================================================================================
// new_league_dialog @ 0x44dcf [__watcall]
// ================================================================================================

void __watcall new_league_dialog(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined8 uVar5;
  undefined local_88 [44];
  undefined auStack_5c [32];
  char local_3c [16];
  int iStack_2c;
  undefined local_28 [4];
  undefined auStack_24 [4];
  int iStack_20;
  int iStack_1c;
  
  __CHK(0xa0);
  set_dialog_colors(0xf9,0xfa,0xf8,0xfa,0);
  iVar4 = 0;
  iVar3 = 0;
  iStack_20 = 0;
  do {
    memset(&unk_dd7b4 + iStack_20 * 0x1e,0,0xb);
    memset((void *)(iStack_20 * 0x1e + 0xdd7bf),0,0xb);
    (&unk_dd7ca)[iStack_20 * 0x1e] = 1;
    (&unk_dd7cb)[iStack_20 * 0x1e] = 0;
    (&unk_dd7cc)[iStack_20 * 0x1e] = 2;
    (&unk_dd7cd)[iStack_20 * 0x1e] = 0;
    *(undefined4 *)(&unk_dd7ce + iStack_20 * 0x1e) = 0;
    iStack_20 = iStack_20 + 1;
  } while (iStack_20 < 0x1a);
  iStack_20 = sub_2fedf(aEnterNewLeagueName,local_3c,8,0x30,0,0,0,0,5);
  if ((local_3c[0] != '\0') && (iStack_20 != 0x1b)) {
    getmouse(&iStack_20,auStack_24,local_28);
    strcat(local_3c,(char *)&aLP_c815c);
    strcpy(&league_dir,local_3c);
    iVar1 = _dos_findfirst(local_3c,0x10,local_88);
    if (iVar1 == 0) {
      iStack_1c = message_dialog(0xffffffff,0xffffffff,&off_c772b,2,&unk_c7733,2,auStack_24,local_28
                                 ,0xffffffff);
      if (iStack_1c == 1) {
        sub_14442(local_3c);
      }
      else {
        iVar3 = 1;
      }
    }
    if (iVar3 == 0) {
      iStack_1c = message_dialog(0xffffffff,0xffffffff,&off_c77aa,1,&unk_c77ae,2,auStack_24,local_28
                                 ,0xffffffff);
      if (iStack_1c == -1) {
        iVar3 = -1;
      }
    }
    if (iVar3 == 0) {
      iVar1 = sub_2fdd1();
      if (iVar1 == -1) {
        iVar3 = -1;
      }
    }
    if (iVar3 == 0) {
      uVar5 = sub_106c8(0);
      if ((int)uVar5 < 0x800) {
        message_dialog(0xffffffff,0xffffffff,&off_c8d02,1,0,0,auStack_24,local_28,500);
        iVar4 = 1;
      }
      else {
        iVar4 = mkdir(local_3c,(__mode_t)((ulonglong)uVar5 >> 0x20));
      }
    }
    if ((iVar3 == 0) && (iVar4 == 0)) {
      make_path(auStack_5c,0,off_c80e7,&aDB);
      iVar4 = db_open_check(auStack_5c,&unk_ddac4,1);
      if (iVar4 == 0) {
        team_info_screen(&league_dir,&dword_ddac0,&unk_ddac4,&unk_dd7b4,1,aSelectHumanControlledTea,
                         &iStack_2c);
        iVar1 = 0xb6;
        for (iVar3 = 0; iVar3 < 0x1a; iVar3 = iVar3 + 1) {
          if (((&unk_dd7cb)[iVar3 * 0x1e] == '\x01') && ((&unk_dd7cc)[iVar3 * 0x1e] == '\x01')) {
            iVar1 = iVar1 + -7;
          }
        }
        sub_149bf(0,&unk_c8d06,dword_dd770);
        iVar3 = 0;
        do {
          iVar2 = 1;
          do {
            (&unk_c8d06)[iVar2 * 7 + iVar3] = (&unk_c8d06)[iVar3];
            iVar2 = iVar2 + 1;
          } while (iVar2 < 0x1b);
          iVar3 = iVar3 + 1;
        } while (iVar3 < 7);
        make_path(auStack_5c,&league_dir,aGameSet_c1a7c,0);
        iVar3 = sub_142e7(auStack_5c);
        if (iVar3 != 0) {
          dword_c9002 = 0;
        }
        iVar3 = check_disk_space(0,&unk_c8d06 + iVar1);
        if (iVar3 != 0) {
          sprintf(aXXXXKbytesOfFreeDiskSpac,a4dKbytesOfFreeDiskSpace,iVar3);
          message_dialog(0xffffffff,0xffffffff,&off_c8cc8,3,0,0,auStack_24,local_28,800);
          iVar4 = 1;
        }
        if ((iVar4 == 0) && (-1 < iStack_2c)) {
          message_dialog(0xffffffff,0xffffffff,&off_c7bea,1,0,0,0,0,0);
          iVar4 = sub_413cd(&league_dir,&unk_dd7b4,&unk_ddd1d,dword_dd7a8,dword_ddac0,dword_dd7b0,
                            dword_dd7ac,&byte_ddd10);
          iStack_20 = 0;
          while ((iStack_20 < 7 && (iVar4 == 0))) {
            iVar4 = sub_1466b((&off_c80d7)[iStack_20],dword_dd770,&aDB,0,&league_dir);
            iStack_20 = iStack_20 + 1;
          }
          if (iVar4 == 0) {
            load_game_set(&settings_league);
            iVar4 = league_db_load(&league_dir,iStack_1c);
          }
          sub_30f12();
          if (iVar4 == 0) {
            iVar4 = league_player_sync(&league_dir,&unk_dd7b4,0xffffffff);
          }
        }
      }
    }
    if ((iVar4 != 0) || (iStack_2c < 0)) {
      if (iVar4 != 0) {
        getmouse(&iStack_20,auStack_24,local_28);
        message_dialog(0xffffffff,0xffffffff,&off_c7826,1,0,0,auStack_24,local_28,0xffffffff);
      }
      byte_c5386 = 0;
      sub_14442(local_3c);
    }
  }
  set_dialog_colors(0x2a,0x3f,0x17,0x3f,0);
  return;
}


// ================================================================================================
// sub_45282 @ 0x45282 [__watcall]
// ================================================================================================

undefined8 __watcall sub_45282(int param_1,undefined4 unaff_EDX)

{
  uint uVar1;
  
  __CHK(0xc);
  uVar1 = rand();
  return CONCAT44(unaff_EDX,
                  (int)((longlong)((ulonglong)uVar1 & 0xffffffff00007fff) % (longlong)param_1));
}


// ================================================================================================
// sub_452a6 @ 0x452a6 [__watcall]
// ================================================================================================

void __watcall sub_452a6(int *param_1,int unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  __CHK(8);
  if (*param_1 < 4) {
    *(undefined4 *)(unaff_EDX + *param_1 * 8) = unaff_EBX;
    *(undefined4 *)(unaff_EDX + 4 + *param_1 * 8) = unaff_ECX;
    *param_1 = *param_1 + 1;
  }
  return;
}


// ================================================================================================
// playoff_setup_screen @ 0x452c5 [__watcall]
// ================================================================================================

int __watcall
playoff_setup_screen
          (undefined4 param_1,undefined4 param_2,int unaff_EBX,int unaff_ECX,undefined4 param_5,
          undefined4 param_6,uint param_7)

{
  short *psVar1;
  byte *pbVar2;
  ushort *puVar3;
  ushort uVar4;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  int *piVar10;
  int iVar11;
  byte bVar12;
  char cVar13;
  byte bVar14;
  uint uVar15;
  int unaff_ESI;
  int unaff_EDI;
  undefined8 uVar16;
  byte abStack_210 [52];
  byte abStack_1dc [52];
  byte abStack_1a8 [52];
  byte abStack_174 [52];
  byte abStack_140 [36];
  byte abStack_11c [12];
  int aiStack_110 [8];
  int aiStack_f0 [10];
  int aiStack_c8 [12];
  int aiStack_98 [2];
  byte *local_90 [2];
  int aiStack_88 [4];
  uint local_78;
  uint local_74;
  int local_70;
  int local_6c;
  int local_68;
  int local_64;
  int local_60;
  int local_5c;
  int local_58;
  int local_54;
  int local_50;
  int local_4c;
  int local_48;
  uint local_44;
  uint local_40;
  byte abStack_3c [4];
  byte abStack_38 [4];
  byte local_34 [4];
  int local_30;
  byte local_2c [4];
  byte local_28 [4];
  byte local_24;
  byte local_20;
  byte local_1c;
  byte local_18;
  byte local_14;
  char cStack_10;
  
  __CHK(0x224);
  local_44 = 0;
  do {
    local_48 = 0;
    do {
      iVar5 = local_44 * 5 + local_48;
      abStack_11c[iVar5 + -0xc] = 0;
      abStack_11c[iVar5] = 0;
      local_48 = local_48 + 1;
    } while (local_48 < 5);
    local_44 = local_44 + 1;
  } while ((int)local_44 < 2);
  local_20 = 0;
  local_24 = 0;
  aiStack_f0[6] = (int)*(byte *)(unaff_ECX + 2);
  aiStack_f0[7] = (int)*(byte *)(unaff_ECX + 3);
  local_90[0] = (byte *)(unaff_ECX + 4);
  local_90[1] = (byte *)(unaff_ECX + 5);
  *(undefined *)(unaff_ECX + 4) = 0;
  *(undefined *)(unaff_ECX + 5) = 0;
  local_68 = 0;
  local_44 = 0;
  do {
    iVar5 = allocmem(&aT_c1aa4,0x2e8,0x20);
    uVar15 = local_44;
    aiStack_110[local_44 + 0x1a] = iVar5;
    iVar5 = allocmem(&aAt,0x4c,0x20);
    aiStack_110[uVar15 + 0x18] = iVar5;
    iVar5 = allocmem(&aPk,100,0x20);
    aiStack_110[uVar15 + 0x1e] = iVar5;
    iVar5 = allocmem(&aPs,100,0x20);
    aiStack_110[uVar15 + 0x14] = iVar5;
    iVar5 = allocmem(&aPset,100,0x20);
    aiStack_110[uVar15 + 0x16] = iVar5;
    iVar5 = allocmem(&aAps,100,0x20);
    aiStack_110[uVar15 + 10] = iVar5;
    iVar5 = allocmem(aApset,100,0x20);
    aiStack_110[uVar15] = iVar5;
    iVar5 = allocmem(&aGk,0xc,0x20);
    aiStack_110[uVar15 + 0xc] = iVar5;
    iVar5 = allocmem(&aGs,0xc,0x20);
    aiStack_110[uVar15 + 8] = iVar5;
    iVar5 = allocmem(&aGset,0xc,0x20);
    aiStack_110[uVar15 + 2] = iVar5;
    iVar5 = allocmem(&aAgs,0xc,0x20);
    aiStack_110[uVar15 + 0x12] = iVar5;
    iVar5 = allocmem(aAgset,0xc,0x20);
    aiStack_110[uVar15 + 4] = iVar5;
    local_44 = uVar15 + 1;
  } while ((int)local_44 < 2);
  local_70 = 0;
  local_44 = 0;
  iVar5 = unaff_EBX;
  while ((uVar15 = local_44, (int)local_44 < 2 && (local_70 == 0))) {
    abStack_38[local_44] = 0;
    local_70 = sub_3a2ee(param_6,aiStack_110[local_44 + 0x18]);
    if (local_70 == 0) {
      local_70 = db_read_record(param_5,aiStack_110[uVar15 + 0x1a]);
      if (unaff_EBX < 0x444) {
        aiStack_110[uVar15 + 0x10] = aiStack_110[uVar15 + 0x18] + 0x28;
        iVar11 = aiStack_110[uVar15 + 0x1a] + 0x28;
      }
      else {
        aiStack_110[uVar15 + 0x10] = aiStack_110[uVar15 + 0x18] + 0x3a;
        iVar11 = aiStack_110[uVar15 + 0x1a] + 0x3a;
      }
      aiStack_110[uVar15 + 0x1c] = iVar11;
      local_34[local_44] = 0xb4;
      aiStack_88[local_44] = 0;
    }
    local_44 = local_44 + 1;
  }
  local_44 = 0;
  while (((int)local_44 < 2 && (local_70 == 0))) {
    local_48 = local_70;
    while ((local_48 < 0x19 && (local_70 == 0))) {
      iVar11 = local_44 * 0x19 + local_48;
      abStack_174[iVar11] = 0;
      abStack_1dc[iVar11] = 0;
      abStack_210[iVar11] = 0;
      abStack_1a8[iVar11] = 0;
      uVar15 = local_44;
      iVar11 = local_48 * 4;
      if (*(int *)(iVar11 + 0x4c + aiStack_110[local_44 + 0x1a]) != -1) {
        uVar6 = sub_6cbb7();
        *(undefined4 *)(iVar11 + aiStack_110[uVar15 + 0x1e]) = uVar6;
        if (local_70 == 0) {
          uVar6 = sub_6cbe8(*(undefined4 *)(*(int *)(iVar11 + aiStack_110[uVar15 + 0x1e]) + 0x28));
          *(undefined4 *)(iVar11 + aiStack_110[uVar15 + 10]) = uVar6;
          puVar3 = *(ushort **)(iVar11 + aiStack_110[uVar15 + 10]);
          local_40 = (uint)puVar3[7];
          local_74 = (uint)*puVar3;
          puVar3[7] = (ushort)(((uint)puVar3[7] * 0x54) / (uint)*puVar3);
          puVar3 = *(ushort **)(iVar11 + aiStack_110[uVar15 + 10]);
          local_40 = (uint)puVar3[6];
          local_74 = (uint)*puVar3;
          puVar3[6] = (ushort)(((uint)puVar3[6] * 0x54) / (uint)*puVar3);
          puVar3 = *(ushort **)(iVar11 + aiStack_110[uVar15 + 10]);
          local_40 = (uint)puVar3[5];
          local_74 = (uint)*puVar3;
          puVar3[5] = (ushort)(((uint)puVar3[5] * 0x54) / (uint)*puVar3);
          puVar3 = *(ushort **)(iVar11 + aiStack_110[uVar15 + 10]);
          local_74 = (uint)*puVar3;
          puVar3[4] = (ushort)(((uint)puVar3[4] * 0x54) / (uint)*puVar3);
          puVar3 = *(ushort **)(iVar11 + aiStack_110[uVar15 + 10]);
          local_40 = (uint)puVar3[2];
          local_74 = (uint)*puVar3;
          puVar3[2] = (ushort)(((uint)puVar3[2] * 0x54) / (uint)*puVar3);
          puVar3 = *(ushort **)(iVar11 + aiStack_110[uVar15 + 10]);
          local_40 = (uint)puVar3[1];
          local_74 = (uint)*puVar3;
          puVar3[1] = (ushort)(((uint)puVar3[1] * 0x54) / (uint)*puVar3);
          iVar7 = *(int *)(iVar11 + aiStack_110[uVar15 + 10]);
          local_30 = (uint)*(ushort *)(iVar7 + 2) + (uint)*(ushort *)(iVar7 + 4);
          *(short *)(iVar7 + 6) = (short)local_30;
          **(undefined2 **)(iVar11 + aiStack_110[uVar15 + 10]) = 0x54;
          if (iVar5 < 0x444) {
            *(undefined4 *)(iVar11 + aiStack_110[uVar15]) =
                 *(undefined4 *)(iVar11 + aiStack_110[uVar15 + 10]);
          }
          else {
            *(int *)(iVar11 + aiStack_110[uVar15]) =
                 *(int *)(iVar11 + aiStack_110[uVar15 + 10]) + 0x12;
          }
          aiStack_88[local_44] =
               aiStack_88[local_44] +
               (uint)*(ushort *)(*(int *)(aiStack_110[local_44 + 10] + local_48 * 4) + 0xc);
        }
        if (local_70 == 0) {
          iVar7 = local_48 * 4;
          uVar16 = sub_6cbcc(*(undefined4 *)(*(int *)(iVar7 + aiStack_110[local_44 + 0x1e]) + 0x2c))
          ;
          iVar11 = (int)((ulonglong)uVar16 >> 0x20);
          *(int *)(iVar7 + *(int *)((int)aiStack_110 + iVar11 + 0x50)) = (int)uVar16;
          if (iVar5 < 0x444) {
            *(undefined4 *)(*(int *)((int)aiStack_110 + iVar11 + 0x58) + iVar7) =
                 *(undefined4 *)(iVar7 + *(int *)((int)aiStack_110 + iVar11 + 0x50));
          }
          else {
            *(int *)(iVar7 + *(int *)((int)aiStack_110 + iVar11 + 0x58)) =
                 *(int *)(iVar7 + *(int *)((int)aiStack_110 + iVar11 + 0x50)) + 0x12;
          }
        }
      }
      local_48 = local_48 + 1;
    }
    local_48 = 0;
    while ((local_48 < 3 && (local_70 == 0))) {
      iVar11 = local_48 * 4;
      if (*(int *)(iVar11 + 0xb0 + aiStack_110[local_44 + 0x1a]) != -1) {
        uVar16 = sub_6cbb7();
        iVar7 = (int)((ulonglong)uVar16 >> 0x20);
        *(int *)(iVar11 + *(int *)((int)aiStack_110 + iVar7 + 0x30)) = (int)uVar16;
        if (local_70 == 0) {
          uVar16 = sub_6cbfd(*(undefined4 *)
                              (*(int *)(iVar11 + *(int *)((int)aiStack_110 + iVar7 + 0x30)) + 0x28))
          ;
          iVar7 = (int)((ulonglong)uVar16 >> 0x20);
          *(int *)(iVar11 + *(int *)((int)aiStack_110 + iVar7 + 0x48)) = (int)uVar16;
          if (iVar5 < 0x444) {
            *(undefined4 *)(*(int *)((int)aiStack_110 + iVar7 + 0x10) + iVar11) =
                 *(undefined4 *)(iVar11 + *(int *)((int)aiStack_110 + iVar7 + 0x48));
          }
          else {
            *(int *)(iVar11 + *(int *)((int)aiStack_110 + iVar7 + 0x10)) =
                 *(int *)(iVar11 + *(int *)((int)aiStack_110 + iVar7 + 0x48)) + 0x16;
          }
        }
        if (local_70 == 0) {
          iVar7 = local_48 * 4;
          uVar16 = sub_6cbe1(*(undefined4 *)(*(int *)(iVar7 + aiStack_110[local_44 + 0xc]) + 0x2c));
          iVar11 = (int)((ulonglong)uVar16 >> 0x20);
          *(int *)(*(int *)((int)aiStack_110 + iVar11 + 0x20) + iVar7) = (int)uVar16;
          if (iVar5 < 0x444) {
            iVar8 = *(int *)((int)aiStack_110 + iVar11 + 8);
            iVar11 = *(int *)(iVar7 + *(int *)((int)aiStack_110 + iVar11 + 0x20));
          }
          else {
            iVar8 = *(int *)((int)aiStack_110 + iVar11 + 8);
            iVar11 = *(int *)(iVar7 + *(int *)((int)aiStack_110 + iVar11 + 0x20)) + 0x16;
          }
          *(int *)(iVar8 + iVar7) = iVar11;
        }
      }
      local_48 = local_48 + 1;
    }
    local_44 = local_44 + 1;
  }
  local_44 = 0;
  while ((uVar15 = local_44, (int)local_44 < 2 && (local_70 == 0))) {
    local_28[local_44] = 5;
    aiStack_88[local_44] = (aiStack_88[local_44] * 1000) / 0x54;
    uVar9 = rand();
    if ((uint)(((ulonglong)uVar9 & 0xffffffff00007fff) % 1000) < 0x137) {
      cVar13 = *(char *)(aiStack_110[uVar15 + 0x1a] + 0xe1);
    }
    else {
      cVar13 = *(char *)(aiStack_110[uVar15 + 0x1a] + 0xe0);
    }
    abStack_3c[local_44] = cVar13 - 0x19;
    *(char *)aiStack_110[local_44 + 0x1c] = *(char *)aiStack_110[local_44 + 0x1c] + '\x01';
    psVar1 = *(short **)(aiStack_110[local_44 + 2] + (uint)abStack_3c[local_44] * 4);
    local_48 = 0;
    *psVar1 = *psVar1 + 1;
    do {
      abStack_1a8[local_44 * 0x19 + local_48] = 0;
      local_48 = local_48 + 1;
    } while (local_48 < 0x19);
    local_48 = 0;
    do {
      iVar11 = 0;
      do {
        bVar12 = *(byte *)(aiStack_110[local_44 + 0x1a] + local_48 * 3 + 0xbc + iVar11);
        if (bVar12 < 0x19) {
          abStack_1a8[(uint)bVar12 + local_44 * 0x19] =
               abStack_1a8[(uint)bVar12 + local_44 * 0x19] + 1;
        }
        iVar11 = iVar11 + 1;
      } while (iVar11 < 3);
      local_48 = local_48 + 1;
    } while (local_48 < 4);
    local_48 = 0;
    do {
      iVar11 = 0;
      do {
        bVar12 = *(byte *)(iVar11 + 200 + local_48 * 2 + aiStack_110[local_44 + 0x1a]);
        if (bVar12 < 0x19) {
          abStack_1a8[(uint)bVar12 + local_44 * 0x19] =
               abStack_1a8[(uint)bVar12 + local_44 * 0x19] + 1;
        }
        iVar11 = iVar11 + 1;
      } while (iVar11 < 2);
      local_48 = local_48 + 1;
    } while (local_48 < 3);
    local_48 = 0;
    do {
      iVar11 = 0;
      do {
        bVar12 = *(byte *)(aiStack_110[local_44 + 0x1a] + local_48 * 5 + 0xce + iVar11);
        if (bVar12 < 0x19) {
          abStack_1a8[(uint)bVar12 + local_44 * 0x19] =
               abStack_1a8[(uint)bVar12 + local_44 * 0x19] + 1;
        }
        iVar11 = iVar11 + 1;
      } while (iVar11 < 5);
      local_48 = local_48 + 1;
    } while (local_48 < 2);
    local_48 = 0;
    do {
      iVar11 = 0;
      do {
        bVar12 = *(byte *)(iVar11 + 0xd8 + local_48 * 4 + aiStack_110[local_44 + 0x1a]);
        if (bVar12 < 0x19) {
          abStack_1a8[local_44 * 0x19 + (uint)bVar12] =
               abStack_1a8[local_44 * 0x19 + (uint)bVar12] + 1;
        }
        iVar11 = iVar11 + 1;
      } while (iVar11 < 4);
      local_48 = local_48 + 1;
    } while (local_48 < 2);
    local_48 = 0;
    do {
      bVar12 = *(byte *)(aiStack_110[local_44 + 0x1a] + local_48 + 0xe2);
      if (bVar12 < 0x19) {
        abStack_1a8[(uint)bVar12 + local_44 * 0x19] =
             abStack_1a8[(uint)bVar12 + local_44 * 0x19] + 1;
      }
      local_48 = local_48 + 1;
    } while (local_48 < 2);
    local_48 = 0;
    do {
      uVar15 = local_44;
      if (abStack_1a8[local_44 * 0x19 + local_48] != 0) {
        psVar1 = *(short **)(aiStack_110[local_44 + 0x16] + local_48 * 4);
        *psVar1 = *psVar1 + 1;
      }
      abStack_1a8[local_44 * 0x19 + local_48] = 0;
      local_48 = local_48 + 1;
    } while (local_48 < 0x19);
    local_44 = uVar15 + 1;
  }
  if ((option_flags & 0xc00) == 0x800) {
    local_64 = 0x3c;
  }
  else if ((option_flags & 0xc00) == 0x400) {
    local_64 = 0x1e;
  }
  else {
    local_64 = 0xf;
  }
  local_48 = 0;
  local_60 = 0;
  do {
    if ((local_64 <= local_48) || (local_70 != 0)) {
      if (*local_90[0] == *local_90[1]) {
        *(char *)(aiStack_c8[10] + 3) = *(char *)(aiStack_c8[10] + 3) + '\x01';
        *(char *)(aiStack_c8[0xb] + 3) = *(char *)(aiStack_c8[0xb] + 3) + '\x01';
        psVar1 = (short *)(*(int *)((uint)abStack_3c[0] * 4 + aiStack_110[2]) + 6);
        *psVar1 = *psVar1 + 1;
        psVar1 = (short *)(*(int *)((uint)abStack_3c[1] * 4 + aiStack_110[3]) + 6);
        *psVar1 = *psVar1 + 1;
      }
      else {
        if (*local_90[1] < *local_90[0]) {
          *(char *)(aiStack_c8[10] + 1) = *(char *)(aiStack_c8[10] + 1) + '\x01';
          *(char *)(aiStack_c8[0xb] + 2) = *(char *)(aiStack_c8[0xb] + 2) + '\x01';
          psVar1 = (short *)(*(int *)((uint)abStack_3c[0] * 4 + aiStack_110[2]) + 2);
          *psVar1 = *psVar1 + 1;
          piVar10 = (int *)((uint)abStack_3c[1] * 4 + aiStack_110[3]);
        }
        else {
          *(char *)(aiStack_c8[0xb] + 1) = *(char *)(aiStack_c8[0xb] + 1) + '\x01';
          *(char *)(aiStack_c8[10] + 2) = *(char *)(aiStack_c8[10] + 2) + '\x01';
          psVar1 = (short *)(*(int *)((uint)abStack_3c[1] * 4 + aiStack_110[3]) + 2);
          *psVar1 = *psVar1 + 1;
          piVar10 = (int *)((uint)abStack_3c[0] * 4 + aiStack_110[2]);
        }
        *(short *)(*piVar10 + 4) = *(short *)(*piVar10 + 4) + 1;
      }
      aiStack_88[2] = 0;
      if (*local_90[0] == 0) {
        psVar1 = (short *)(*(int *)((uint)abStack_3c[1] * 4 + aiStack_110[3]) + 8);
        *psVar1 = *psVar1 + 1;
        sub_452a6(aiStack_88 + 2,abStack_140,1);
      }
      if (*local_90[1] == 0) {
        psVar1 = (short *)(*(int *)((uint)abStack_3c[0] * 4 + aiStack_110[2]) + 8);
        *psVar1 = *psVar1 + 1;
        sub_452a6(aiStack_88 + 2,abStack_140,0);
      }
      local_44 = 0;
      while (((int)local_44 < 3 && (local_70 == 0))) {
        local_48 = local_70;
        while ((local_48 < 2 && (local_70 == 0))) {
          pbVar2 = abStack_140 + local_44 * 8 + local_48 * 4;
          pbVar2[0] = 0xff;
          pbVar2[1] = 0;
          pbVar2[2] = 0;
          pbVar2[3] = 0;
          local_48 = local_48 + 1;
        }
        local_44 = local_44 + 1;
      }
      uVar15 = 0xffff;
      local_44 = 0;
      while (((int)local_44 < 2 && (local_70 == 0))) {
        for (local_48 = local_70; local_48 < 0x19; local_48 = local_48 + 1) {
          iVar5 = local_44 * 0x19 + local_48;
          if (((char)uVar15 == -1) ||
             ((uint)abStack_1dc[iVar5] + (uint)abStack_210[iVar5] + (uint)abStack_1a8[iVar5] * 2 !=
              0)) {
            uVar15 = (uint)CONCAT11((undefined)local_44,(undefined)local_48);
          }
        }
        local_44 = local_44 + 1;
      }
      if ((char)(uVar15 >> 8) != -1) {
        sub_452a6(aiStack_88 + 2,abStack_140);
      }
      uVar15 = 0xffff;
      local_44 = 0;
      while (((int)local_44 < 2 && (local_70 == 0))) {
        for (local_48 = local_70; local_48 < 0x19; local_48 = local_48 + 1) {
          if (((char)uVar15 == -1) || (abStack_1a8[local_44 * 0x19 + local_48] != 0)) {
            uVar15 = (uint)CONCAT11((undefined)local_44,(undefined)local_48);
          }
        }
        local_44 = local_44 + 1;
      }
      if ((char)(uVar15 >> 8) != -1) {
        sub_452a6(aiStack_88 + 2,abStack_140);
      }
      uVar15 = 0xffff;
      local_44 = 0;
      while (((int)local_44 < 2 && (local_70 == 0))) {
        for (local_48 = local_70; local_48 < 0x19; local_48 = local_48 + 1) {
          if (((char)uVar15 == -1) || (abStack_210[local_44 * 0x19 + local_48] != 0)) {
            uVar15 = (uint)CONCAT11((undefined)local_44,(undefined)local_48);
          }
        }
        local_44 = local_44 + 1;
      }
      cVar13 = (char)(uVar15 >> 8);
      if (cVar13 != -1) {
        sub_452a6(aiStack_88 + 2,abStack_140,cVar13,uVar15 & 0xff);
      }
      local_44 = 0;
      while (((int)local_44 < 3 && (local_70 == 0))) {
        bVar12 = abStack_140[local_44 * 8];
        if ((bVar12 != 0xff) && (abStack_140[local_44 * 8 + 4] != 0xff)) {
          iVar5 = (uint)abStack_140[local_44 * 8 + 4] * 4;
          if (*(char *)(*(int *)(iVar5 + aiStack_110[bVar12 + 0x1e]) + 2) == 'G') {
            psVar1 = (short *)(local_44 * 2 + 0x30 + *(int *)(iVar5 + aiStack_110[bVar12 + 8]));
            *psVar1 = *psVar1 + 1;
          }
          else {
            psVar1 = (short *)(local_44 * 2 + 0x28 + *(int *)(iVar5 + aiStack_110[bVar12 + 0x14]));
            *psVar1 = *psVar1 + 1;
          }
        }
        local_44 = local_44 + 1;
      }
      local_44 = 0;
      do {
        puVar3 = *(ushort **)((uint)abStack_3c[local_44] * 4 + aiStack_110[local_44 + 2]);
        if (*puVar3 == 0) {
          puVar3[8] = 0;
        }
        else {
          puVar3[8] = (ushort)(((uint)puVar3[7] * 100) / (uint)*puVar3);
        }
        iVar5 = *(int *)(aiStack_110[local_44 + 2] + (uint)abStack_3c[local_44] * 4);
        uVar4 = *(ushort *)(iVar5 + 0x12);
        if (uVar4 != 0) {
          uVar15 = (uint)uVar4;
          uVar4 = (ushort)((int)((uVar15 - *(ushort *)(iVar5 + 0xe)) * 1000 + uVar15 / 2) /
                          (int)uVar15);
        }
        *(ushort *)(iVar5 + 0x14) = uVar4;
        local_44 = local_44 + 1;
      } while ((int)local_44 < 2);
      local_44 = 0;
      while ((iVar5 = local_70, (int)local_44 < 2 && (local_70 == 0))) {
        iVar11 = sub_3a2b8(param_5,aiStack_110[local_44 + 0x1a],aiStack_110[local_44 + 0xe]);
        local_70 = iVar11;
        local_48 = iVar5;
        while ((local_48 < 0x19 && (iVar11 == 0))) {
          iVar5 = local_48 * 4;
          if (*(int *)(iVar5 + 0x4c + aiStack_110[local_44 + 0x1a]) != -1) {
            memcpy((void *)(*(int *)(*(int *)(iVar5 + aiStack_110[local_44 + 0x1e]) + 0x2c) +
                           dword_d07bb),*(void **)(aiStack_110[local_44 + 0x14] + iVar5),0x2f);
          }
          local_48 = local_48 + 1;
        }
        local_48 = 0;
        while ((local_48 < 3 && (local_70 == 0))) {
          iVar5 = local_48 * 4;
          if (*(int *)(iVar5 + 0xb0 + aiStack_110[local_44 + 0x1a]) != -1) {
            memcpy((void *)(*(int *)(*(int *)(iVar5 + aiStack_110[local_44 + 0xc]) + 0x2c) +
                           dword_d07bb),*(void **)(aiStack_110[local_44 + 8] + iVar5),0x2f);
          }
          local_48 = local_48 + 1;
        }
        local_44 = local_44 + 1;
      }
      local_44 = 0;
      do {
        uVar15 = local_44;
        freemem(aiStack_110[local_44 + 4]);
        freemem(aiStack_110[uVar15 + 0x12]);
        freemem(aiStack_110[uVar15 + 2]);
        freemem(aiStack_110[uVar15 + 8]);
        freemem(aiStack_110[uVar15 + 0xc]);
        freemem(aiStack_110[uVar15]);
        freemem(aiStack_110[uVar15 + 10]);
        freemem(aiStack_110[uVar15 + 0x16]);
        freemem(aiStack_110[uVar15 + 0x14]);
        freemem(aiStack_110[uVar15 + 0x1e]);
        freemem(aiStack_110[uVar15 + 0x18]);
        freemem(aiStack_110[uVar15 + 0x1a]);
        local_44 = uVar15 + 1;
      } while ((int)(uVar15 + 1) < 2);
      return local_70;
    }
    if (local_20 == 0) {
      local_44 = local_70;
      do {
        iVar11 = 0;
        do {
          iVar7 = sub_45282(10);
          if (iVar7 != iVar11) {
            iVar8 = iVar11 * 4 + local_44 * 0x28;
            iVar7 = iVar7 * 4 + local_44 * 0x28;
            uVar15 = *(uint *)(&unk_c900c + iVar7);
            uVar9 = *(uint *)(&unk_c900c + iVar8);
            *(uint *)(&unk_c900c + iVar8) = uVar9 ^ uVar15;
            uVar15 = *(uint *)(&unk_c900c + iVar7) ^ uVar9 ^ uVar15;
            *(uint *)(&unk_c900c + iVar7) = uVar15;
            *(uint *)(&unk_c900c + iVar8) = *(uint *)(&unk_c900c + iVar8) ^ uVar15;
          }
          iVar11 = iVar11 + 1;
        } while (iVar11 < 10);
        local_44 = local_44 + 1;
      } while ((int)local_44 < 2);
    }
    if (local_24 == 0) {
      local_44 = 0;
      do {
        iVar11 = 0;
        do {
          iVar7 = sub_45282(3);
          if (iVar7 != iVar11) {
            iVar8 = iVar11 * 4 + local_44 * 0xc;
            iVar7 = iVar7 * 4 + local_44 * 0xc;
            uVar15 = *(uint *)(&unk_c905c + iVar7);
            uVar9 = *(uint *)(&unk_c905c + iVar8);
            *(uint *)(&unk_c905c + iVar8) = uVar9 ^ uVar15;
            uVar15 = *(uint *)(&unk_c905c + iVar7) ^ uVar9 ^ uVar15;
            *(uint *)(&unk_c905c + iVar7) = uVar15;
            *(uint *)(&unk_c905c + iVar8) = *(uint *)(&unk_c905c + iVar8) ^ uVar15;
          }
          iVar11 = iVar11 + 1;
        } while (iVar11 < 3);
        local_44 = local_44 + 1;
      } while ((int)local_44 < 2);
    }
    local_44 = 0;
    do {
      local_2c[local_44] = local_28[local_44];
      local_28[local_44] = 0;
      iVar11 = 0;
      do {
        iVar7 = local_44 * 5 + iVar11;
        if (abStack_11c[iVar7 + -0xc] != 0) {
          abStack_11c[iVar7 + -0xc] = abStack_11c[iVar7 + -0xc] - 1;
        }
        if (abStack_11c[local_44 * 5 + iVar11 + -0xc] == 0) {
          local_28[local_44] = local_28[local_44] + 1;
        }
        iVar11 = iVar11 + 1;
      } while (iVar11 < 5);
      aiStack_110[local_44 + 6] = 0;
      local_44 = local_44 + 1;
    } while ((int)local_44 < 2);
    if ((local_2c[0] != local_28[0]) || (local_2c[1] != local_28[1])) {
      if ((local_28[1] < local_28[0]) && (local_2c[0] <= local_2c[1])) {
        *(short *)(aiStack_c8[10] + 10) = *(short *)(aiStack_c8[10] + 10) + 1;
        iVar11 = aiStack_c8[0xb];
      }
      else {
        if ((local_28[1] <= local_28[0]) || (local_2c[0] < local_2c[1])) goto LAB_00046097;
        *(short *)(aiStack_c8[0xb] + 10) = *(short *)(aiStack_c8[0xb] + 10) + 1;
        iVar11 = aiStack_c8[10];
      }
      *(short *)(iVar11 + 0xe) = *(short *)(iVar11 + 0xe) + 1;
    }
LAB_00046097:
    if (local_28[1] < local_28[0]) {
      aiStack_110[6] = ((uint)local_28[0] - (uint)local_28[1]) * 0x5f;
      aiStack_110[7] = ((uint)local_28[0] - (uint)local_28[1]) * -0x5f;
    }
    else if (local_28[0] < local_28[1]) {
      aiStack_110[7] = ((uint)local_28[1] - (uint)local_28[0]) * 0x5f;
      aiStack_110[6] = ((uint)local_28[1] - (uint)local_28[0]) * -0x5f;
    }
    local_44 = 0;
    do {
      iVar11 = sub_45282(1000);
      if (iVar11 < aiStack_88[local_44] / (int)(uint)local_34[local_44]) {
        bVar12 = 0xff;
        iVar11 = 0;
        do {
          local_74 = *(int *)(&unk_c900c + (uint)local_20 * 4 + local_44 * 0x28) * 3;
          bVar14 = *(byte *)(aiStack_110[local_44 + 0x1a] +
                             *(int *)(&unk_c900c + (uint)local_20 * 4 + local_44 * 0x28) * 3 + 0xbc
                            + iVar11);
          local_74 = (uint)bVar14;
          local_4c = ((uint)*(ushort *)(*(int *)(aiStack_110[local_44 + 10] + local_74 * 4) + 0xc) *
                     1000) / 0x13b0 + (uint)abStack_174[local_44 * 0x19 + local_74] * -1000;
          if ((bVar12 == 0xff) || (local_54 < local_4c)) {
            unaff_EDI = *(int *)(aiStack_110[local_44 + 0x16] + (uint)bVar14 * 4);
            bVar12 = (byte)iVar11;
            local_54 = local_4c;
            local_14 = bVar14;
          }
          iVar11 = iVar11 + 1;
        } while (iVar11 < 3);
        iVar11 = 0;
        do {
          bVar14 = *(byte *)(iVar11 + 200 +
                            *(int *)(&unk_c905c + (uint)local_24 * 4 + local_44 * 0xc) * 2 +
                            aiStack_110[local_44 + 0x1a]);
          aiStack_88[3] = (int)bVar14;
          local_5c = aiStack_88[3] * 4;
          local_74 = ((uint)*(ushort *)(*(int *)(aiStack_110[local_44 + 10] + local_5c) + 0xc) *
                     1000) / 0x13b0;
          local_40 = local_44;
          local_40 = (uint)abStack_174[local_44 * 0x19 + aiStack_88[3]];
          local_4c = local_74 + (uint)abStack_174[local_44 * 0x19 + aiStack_88[3]] * -1000;
          if (local_54 < local_4c) {
            unaff_EDI = *(int *)(aiStack_110[local_44 + 0x16] + local_5c);
            bVar12 = (char)iVar11 + 3;
            local_54 = local_4c;
            local_14 = bVar14;
          }
          iVar11 = iVar11 + 1;
        } while (iVar11 < 2);
        if (abStack_11c[(uint)bVar12 + local_44 * 5 + -0xc] == 0) {
          iVar11 = sub_45282(1000);
          if (iVar11 < 0x3c) {
            bVar14 = 5;
          }
          else {
            bVar14 = 2;
          }
          abStack_11c[local_44 * 5 + (uint)bVar12 + -0xc] = bVar14 + 1;
          uVar15 = local_44;
          *(short *)(unaff_EDI + 0xc) = *(short *)(unaff_EDI + 0xc) + (ushort)bVar14;
          iVar11 = aiStack_110[local_44 + 0x1c];
          abStack_174[(uint)local_14 + local_44 * 0x19] =
               abStack_174[(uint)local_14 + local_44 * 0x19] + 1;
          *(short *)(iVar11 + 0x10) = *(short *)(iVar11 + 0x10) + (ushort)bVar14;
          aiStack_88[uVar15] = aiStack_88[uVar15] + -1000;
        }
      }
      else {
        uVar15 = ((uint)*(ushort *)
                         (*(int *)(aiStack_110[local_44 + 0x12] + (uint)abStack_3c[local_44] * 4) +
                         0x12) * 1000) / 0x13b0;
        iVar11 = 0;
        do {
          uVar15 = uVar15 + ((uint)*(ushort *)
                                    (*(int *)(aiStack_110[local_44 + 10] +
                                             (uint)*(byte *)(*(int *)(&unk_c900c +
                                                                     local_44 * 0x28 +
                                                                     (uint)local_20 * 4) * 3 +
                                                             aiStack_110[local_44 + 0x1a] + 0xbc +
                                                            iVar11) * 4) + 0xe) * 1000) / 0x13b0;
          iVar11 = iVar11 + 1;
        } while (iVar11 < 3);
        iVar11 = 0;
        do {
          local_74 = *(int *)(&unk_c905c + (uint)local_24 * 4 + local_44 * 0xc) * 2;
          uVar15 = uVar15 + ((uint)*(ushort *)
                                    (*(int *)(aiStack_110[local_44 + 10] +
                                             (uint)*(byte *)(aiStack_110[local_44 + 0x1a] +
                                                             *(int *)(&unk_c905c +
                                                                     (uint)local_24 * 4 +
                                                                     local_44 * 0xc) * 2 + 200 +
                                                            iVar11) * 4) + 0xe) * 1000) / 0x13b0;
          iVar11 = iVar11 + 1;
        } while (iVar11 < 2);
        if (1000 < (int)(uVar15 * (local_60 + 1) +
                        (uint)abStack_11c
                              [local_44 * 5 +
                               *(int *)(&unk_c900c + local_44 * 0x28 + (uint)local_20 * 4)] * -1000)
           ) {
          cVar13 = -1;
          iVar11 = 0;
          do {
            local_74 = *(int *)(&unk_c900c + (uint)local_20 * 4 + local_44 * 0x28) * 3;
            bVar12 = *(byte *)(aiStack_110[local_44 + 0x1a] +
                               *(int *)(&unk_c900c + (uint)local_20 * 4 + local_44 * 0x28) * 3 +
                               0xbc + iVar11);
            local_40 = 0x3c;
            local_74 = ((uint)*(ushort *)
                               (*(int *)(aiStack_110[local_44 + 10] + (uint)bVar12 * 4) + 0xe) *
                       1000) / 0x13b0;
            local_50 = local_74 + (uint)abStack_1dc[(uint)bVar12 + local_44 * 0x19] * -1000;
            if (((cVar13 == -1) || (local_58 < local_50)) &&
               (abStack_11c[local_44 * 5 + iVar11 + -0xc] == 0)) {
              unaff_EDI = *(int *)(aiStack_110[local_44 + 0x16] + (uint)bVar12 * 4);
              cVar13 = (char)iVar11;
              local_58 = local_50;
              local_14 = bVar12;
            }
            iVar11 = iVar11 + 1;
          } while (iVar11 < 3);
          iVar11 = 0;
          do {
            bVar12 = *(byte *)(iVar11 + 200 +
                              aiStack_110[local_44 + 0x1a] +
                              *(int *)(&unk_c905c + local_44 * 0xc + (uint)local_24 * 4) * 2);
            local_78 = (uint)bVar12;
            local_6c = local_78 * 4;
            local_74 = ((uint)*(ushort *)(*(int *)(aiStack_110[local_44 + 10] + local_6c) + 0xe) *
                       1000) / 0x13b0;
            local_40 = local_44;
            local_40 = (uint)abStack_1dc[local_44 * 0x19 + local_78];
            local_50 = local_74 + (uint)abStack_1dc[local_44 * 0x19 + local_78] * -1000;
            if ((local_58 < local_50) &&
               (local_40 = local_44, abStack_11c[local_44 * 5 + iVar11 + -9] == 0)) {
              unaff_EDI = *(int *)(aiStack_110[local_44 + 0x16] + local_6c);
              local_58 = local_50;
              local_14 = bVar12;
            }
            iVar11 = iVar11 + 1;
          } while (iVar11 < 2);
          iVar11 = local_44 * 0x19;
          uVar15 = (uint)local_14;
          abStack_11c[*(int *)(&unk_c900c + (uint)local_20 * 4 + local_44 * 0x28) + local_44 * 5] =
               abStack_11c
               [*(int *)(&unk_c900c + (uint)local_20 * 4 + local_44 * 0x28) + local_44 * 5] + 1;
          abStack_1dc[uVar15 + iVar11] = abStack_1dc[uVar15 + iVar11] + 1;
          *(short *)(unaff_EDI + 0xe) = *(short *)(unaff_EDI + 0xe) + 1;
          psVar1 = (short *)(*(int *)(aiStack_110[local_44 + 2] + (uint)abStack_3c[local_44] * 4) +
                            0x12);
          *psVar1 = *psVar1 + 1;
          iVar11 = *(int *)(aiStack_110[(local_44 ^ 1) + 0x12] + (uint)abStack_3c[local_44 ^ 1] * 4)
          ;
          if (*(short *)(iVar11 + 0x12) == 0) {
            uVar15 = rand();
            uVar15 = (int)(((ulonglong)uVar15 & 0xffffffff00007fff) % 10) + 1;
          }
          else {
            uVar15 = ((uint)*(ushort *)(iVar11 + 0xe) * 1000) / (uint)*(ushort *)(iVar11 + 0x12);
          }
          bVar12 = abStack_38[local_44];
          iVar11 = *(int *)(aiStack_110[local_44 + 10] + (uint)local_14 * 4);
          if (*(short *)(iVar11 + 0xe) == 0) {
            uVar9 = rand();
            uVar9 = (int)(((ulonglong)uVar9 & 0xffffffff00007fff) % 10) + 1;
          }
          else {
            uVar9 = ((uint)*(ushort *)(iVar11 + 2) * 1000) / (uint)*(ushort *)(iVar11 + 0xe);
          }
          if ((local_60 < local_64) || (param_7 != local_44)) {
            iVar11 = (int)(uVar9 + (uVar15 - ((uint)bVar12 * 1000) / 0x21)) / 2 +
                     aiStack_110[local_44 + 6] + 0xd;
          }
          else {
            iVar11 = 1000;
          }
          iVar7 = sub_45282(1000);
          if (((param_7 == 0) || (param_7 == 1)) && (local_44 != param_7)) {
            local_74 = (uint)abStack_38[local_44 ^ 1];
            local_40 = (uint)abStack_38[local_44];
            if (((int)(abStack_38[local_44 ^ 1] - 1) <= (int)(uint)abStack_38[local_44]) ||
               (abStack_38[local_44 ^ 1] == 0)) {
              iVar7 = iVar11 + 1;
            }
          }
          if (iVar7 <= iVar11) {
            local_1c = local_14;
            *(short *)(unaff_EDI + 2) = *(short *)(unaff_EDI + 2) + 1;
            *(short *)(unaff_EDI + 6) = *(short *)(unaff_EDI + 6) + 1;
            uVar15 = local_44 ^ 1;
            bVar12 = abStack_3c[uVar15];
            iVar11 = aiStack_110[uVar15 + 2];
            abStack_1a8[(uint)local_14 + local_44 * 0x19] =
                 abStack_1a8[(uint)local_14 + local_44 * 0x19] + 1;
            psVar1 = (short *)(*(int *)((uint)bVar12 * 4 + iVar11) + 0xe);
            *psVar1 = *psVar1 + 1;
            *(short *)(aiStack_110[local_44 + 0x1c] + 4) =
                 *(short *)(aiStack_110[local_44 + 0x1c] + 4) + 1;
            *local_90[local_44] = *local_90[local_44] + 1;
            abStack_38[local_44] = abStack_38[local_44] + 1;
            if (0 < aiStack_110[local_44 + 6]) {
              *(short *)(aiStack_110[local_44 + 0x1c] + 8) =
                   *(short *)(aiStack_110[local_44 + 0x1c] + 8) + 1;
              *(short *)(unaff_EDI + 8) = *(short *)(unaff_EDI + 8) + 1;
              *(short *)(aiStack_110[uVar15 + 0x1c] + 0xc) =
                   *(short *)(aiStack_110[uVar15 + 0x1c] + 0xc) + 1;
            }
            *(short *)(aiStack_110[(local_44 ^ 1) + 0x1c] + 6) =
                 *(short *)(aiStack_110[(local_44 ^ 1) + 0x1c] + 6) + 1;
            if (aiStack_110[local_44 + 6] < 0) {
              *(short *)(unaff_EDI + 10) = *(short *)(unaff_EDI + 10) + 1;
            }
            iVar11 = 0;
            do {
              local_40 = (uint)local_20 * 4;
              uVar15 = local_44 ^ 1;
              psVar1 = (short *)(*(int *)(aiStack_110[local_44 + 0x16] +
                                         (uint)*(byte *)(*(int *)(&unk_c900c +
                                                                 local_44 * 0x28 + local_40) * 3 +
                                                         aiStack_110[local_44 + 0x1a] + 0xbc +
                                                        iVar11) * 4) + 0x10);
              *psVar1 = *psVar1 + 1;
              psVar1 = (short *)(*(int *)(aiStack_110[uVar15 + 0x16] +
                                         (uint)*(byte *)(*(int *)(&unk_c900c +
                                                                 uVar15 * 0x28 + local_40) * 3 +
                                                         aiStack_110[uVar15 + 0x1a] + 0xbc + iVar11)
                                         * 4) + 0x10);
              *psVar1 = *psVar1 + -1;
              iVar11 = iVar11 + 1;
            } while (iVar11 < 3);
            iVar11 = 0;
            do {
              local_40 = (uint)local_24 * 4;
              uVar15 = local_44 ^ 1;
              psVar1 = (short *)(*(int *)((uint)*(byte *)(aiStack_110[local_44 + 0x1a] +
                                                          *(int *)(&unk_c905c +
                                                                  local_44 * 0xc + local_40) * 2 +
                                                          200 + iVar11) * 4 +
                                         aiStack_110[local_44 + 0x16]) + 0x10);
              *psVar1 = *psVar1 + 1;
              psVar1 = (short *)(*(int *)(aiStack_110[uVar15 + 0x16] +
                                         (uint)*(byte *)(aiStack_110[uVar15 + 0x1a] +
                                                         *(int *)(&unk_c905c +
                                                                 uVar15 * 0xc + local_40) * 2 + 200
                                                        + iVar11) * 4) + 0x10);
              *psVar1 = *psVar1 + -1;
              iVar11 = iVar11 + 1;
            } while (iVar11 < 2);
            cStack_10 = '\0';
            iVar11 = sub_45282(1000);
            if ((iVar11 < 0x321) && (1 < local_28[local_44])) {
              cStack_10 = '\x02';
            }
            else if ((iVar11 < 0x385) && (local_28[local_44] != 0)) {
              cStack_10 = '\x01';
            }
            local_18 = 0xff;
            while (cStack_10 != '\0') {
              cVar13 = -1;
              iVar11 = 0;
              do {
                local_40 = *(int *)(&unk_c900c + local_44 * 0x28 + (uint)local_20 * 4) * 3;
                bVar12 = *(byte *)(aiStack_110[local_44 + 0x1a] +
                                   *(int *)(&unk_c900c + local_44 * 0x28 + (uint)local_20 * 4) * 3 +
                                   0xbc + iVar11);
                local_40 = ((uint)*(ushort *)
                                   (*(int *)(aiStack_110[local_44 + 10] + (uint)bVar12 * 4) + 4) *
                           1000) / 0x13b0;
                iVar7 = local_40 + (uint)abStack_210[(uint)bVar12 + local_44 * 0x19] * -1000;
                if ((((cVar13 == -1) || (unaff_ESI < iVar7)) &&
                    (local_40 = local_44, abStack_11c[local_44 * 5 + iVar11 + -0xc] == 0)) &&
                   ((bVar12 != local_1c && (bVar12 != local_18)))) {
                  unaff_EDI = *(int *)(aiStack_110[local_44 + 0x16] + (uint)bVar12 * 4);
                  cVar13 = (char)iVar11;
                  local_14 = bVar12;
                  unaff_ESI = iVar7;
                }
                iVar11 = iVar11 + 1;
              } while (iVar11 < 3);
              iVar11 = 0;
              do {
                local_40 = *(int *)(&unk_c905c + (uint)local_24 * 4 + local_44 * 0xc) * 2;
                bVar12 = *(byte *)(aiStack_110[local_44 + 0x1a] +
                                   *(int *)(&unk_c905c + (uint)local_24 * 4 + local_44 * 0xc) * 2 +
                                   200 + iVar11);
                local_40 = ((uint)*(ushort *)
                                   (*(int *)(aiStack_110[local_44 + 10] + (uint)bVar12 * 4) + 4) *
                           1000) / 0x13b0;
                iVar7 = local_40 + (uint)abStack_210[(uint)bVar12 + local_44 * 0x19] * -1000;
                if (((cVar13 == -1) || (unaff_ESI < iVar7)) &&
                   ((local_40 = local_44, abStack_11c[local_44 * 5 + iVar11 + -9] == 0 &&
                    ((bVar12 != local_1c && (bVar12 != local_18)))))) {
                  unaff_EDI = *(int *)(aiStack_110[local_44 + 0x16] + (uint)bVar12 * 4);
                  cVar13 = (char)iVar11 + '\x03';
                  local_14 = bVar12;
                  unaff_ESI = iVar7;
                }
                iVar11 = iVar11 + 1;
              } while (iVar11 < 2);
              if (cVar13 == -1) {
                cStack_10 = '\0';
              }
              else {
                local_18 = local_14;
                abStack_210[(uint)local_14 + local_44 * 0x19] =
                     abStack_210[(uint)local_14 + local_44 * 0x19] + 1;
                *(short *)(unaff_EDI + 4) = *(short *)(unaff_EDI + 4) + 1;
                *(short *)(unaff_EDI + 6) = *(short *)(unaff_EDI + 6) + 1;
                cStack_10 = cStack_10 + -1;
              }
            }
          }
        }
      }
      psVar1 = (short *)(*(int *)((uint)abStack_3c[local_44] * 4 + aiStack_110[local_44 + 2]) + 0xc)
      ;
      *psVar1 = *psVar1 + 1;
      local_44 = local_44 + 1;
    } while ((int)local_44 < 2);
    local_20 = local_20 + 1;
    if (local_20 == 10) {
      local_20 = 0;
    }
    local_24 = local_24 + 1;
    if (local_24 == 3) {
      local_24 = 0;
    }
    if (local_64 + -1 == local_48) {
      if (iVar5 < 0x444) {
        if ((*local_90[0] == *local_90[1]) && (local_68 < 5)) {
          local_68 = local_68 + 1;
          goto LAB_00047189;
        }
      }
      else if (*local_90[0] == *local_90[1]) {
LAB_00047189:
        local_48 = local_48 + -1;
      }
    }
    local_48 = local_48 + 1;
    local_60 = local_60 + 1;
  } while( true );
}


// ================================================================================================
// loading_screen_timer @ 0x47951 [__watcall]
// ================================================================================================

void __watcall
loading_screen_timer
          (undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  uint uVar1;
  
  __CHK(0x1c);
  if (dword_deb6c != 1) {
    if (byte_deb71 != '\0') {
      byte_deb71 = byte_deb71 + -1;
      return;
    }
    dword_deb6c = 1;
    byte_deb71 = '\x03';
    uVar1 = (uint)byte_deb70;
    byte_deb70 = (byte)((uVar1 + 1) % 3);
    waitvbl_start((uVar1 + 1) / 3);
    setpalette(0,0x100,&unk_de26c + (uint)byte_deb70 * 0x300,unaff_EDX,unaff_ECX,unaff_EBX);
    dword_deb6c = 0;
  }
  return;
}


// ================================================================================================
// loading_screen @ 0x479e9 [__watcall]
// ================================================================================================

void __watcall loading_screen(void)

{
  void *__src;
  bool bVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  undefined *puVar6;
  int iVar7;
  char acStack_924 [768];
  char acStack_624 [768];
  char acStack_324 [768];
  undefined auStack_24 [16];
  
  __CHK(0x934);
  if (dword_c9074 == 0) {
    getpalette(0,0x100,&unk_de26c);
    fade_palette(1,&unk_de26c,8);
    setdefaultscreen();
    clearclip(0);
    iVar2 = sub_8dab8();
    if (140000 < iVar2) {
      memset(&unk_de26c,0,0x900);
      puVar6 = install_path;
      if (byte_ed9ee != '\x01') {
        puVar6 = (undefined *)0x0;
      }
      make_path(auStack_24,puVar6,&aLoad,0);
      uVar3 = loadshapes(auStack_24,0);
      iVar2 = locateshape(uVar3,&aPal_c1ad9);
      __src = (void *)(iVar2 + 0x10);
      memcpy(acStack_924,__src,0x300);
      memcpy(acStack_624,__src,0x300);
      memcpy(acStack_324,__src,0x300);
      iVar2 = 1;
      do {
        if (iVar2 < 0x60) {
          iVar7 = iVar2 + 0x2f;
        }
        else {
          iVar7 = iVar2 + -0x5f;
        }
        iVar7 = iVar7 * 3;
        iVar5 = iVar2 * 3;
        acStack_624[iVar5] = acStack_924[iVar7];
        acStack_624[iVar5 + 1] = acStack_924[iVar7 + 1];
        acStack_624[iVar5 + 2] = acStack_924[iVar7 + 2];
        iVar2 = iVar2 + 1;
      } while (iVar2 < 0x90);
      iVar2 = 1;
      do {
        if (iVar2 < 0x30) {
          iVar7 = iVar2 + 0x60;
        }
        else {
          iVar7 = iVar2 + -0x2f;
        }
        iVar7 = iVar7 * 3;
        iVar5 = iVar2 * 3;
        acStack_324[iVar5] = acStack_924[iVar7];
        acStack_324[iVar5 + 1] = acStack_924[iVar7 + 1];
        acStack_324[iVar5 + 2] = acStack_924[iVar7 + 2];
        iVar2 = iVar2 + 1;
      } while (iVar2 < 0x90);
      uVar4 = locateshape(uVar3,&aLoad);
      drawshape2(uVar4,100,0x4b);
      freemem(uVar3);
      dword_deb6c = 1;
      byte_deb70 = 0;
      byte_deb71 = 3;
      addtimer(loading_screen_timer);
      dword_deb6c = 0;
      bVar1 = false;
      while (!bVar1) {
        bVar1 = true;
        iVar2 = 0;
        do {
          iVar7 = 0;
          do {
            iVar5 = iVar2 * 0x300 + iVar7;
            if (((char)(&unk_de26c)[iVar5] < acStack_924[iVar5]) &&
               ((&unk_de26c)[iVar5] = (&unk_de26c)[iVar5] + '\x01', bVar1)) {
              bVar1 = false;
            }
            iVar7 = iVar7 + 1;
          } while (iVar7 < 0x300);
          iVar2 = iVar2 + 1;
        } while (iVar2 < 3);
        settimeout(2);
        waittimeout();
      }
      dword_c9074 = 1;
    }
  }
  return;
}


// ================================================================================================
// wait_sprite_fade @ 0x47c31 [__watcall]
// ================================================================================================

void __watcall wait_sprite_fade(void)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  __CHK(0x1c);
  if (dword_c9074 != 0) {
    bVar1 = false;
    while (!bVar1) {
      bVar1 = true;
      iVar3 = 0;
      do {
        iVar4 = 0;
        do {
          iVar2 = iVar3 * 0x300 + iVar4;
          if ('\0' < (char)(&unk_de26c)[iVar2]) {
            (&unk_de26c)[iVar2] = (&unk_de26c)[iVar2] + -1;
            if (bVar1) {
              bVar1 = false;
            }
          }
          iVar4 = iVar4 + 1;
        } while (iVar4 < 0x300);
        iVar3 = iVar3 + 1;
      } while (iVar3 < 3);
      dword_deb6c = 0;
      settimeout(2);
      waittimeout();
    }
    dword_deb6c = 1;
    removetimer(loading_screen_timer);
    dword_c9074 = 0;
  }
  return;
}


// ================================================================================================
// init_match @ 0x47cd6 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall init_match(void)

{
  short sVar1;
  undefined2 uVar2;
  short sVar3;
  short sVar4;
  int iVar5;
  int iVar6;
  short extraout_DX;
  short extraout_DX_00;
  undefined2 extraout_var;
  undefined4 uVar7;
  undefined *puVar8;
  undefined4 *puVar9;
  undefined *puVar10;
  undefined4 local_28;
  char acStackY_24 [8];
  undefined4 local_1c;
  int iStackY_18;
  
  __CHK(0x28);
  local_28 = 0x47cf2;
  play_speech(10);
  local_1c = CONCAT22(extraout_var,(short)(char)(&unk_cc9b0)[user2_team._2_2_]);
  sVar1 = *(short *)(&unk_cc9cc + (*(int *)(&unk_cc9ad + user2_team._2_2_) >> 0x18) * 2);
  local_28 = 0x47d2c;
  load_cutscene_clip(((char)(&unk_cc9b0)[user2_team._2_2_] != 1) + '\x03');
  byte_e0344 = 0;
  byte_e0308 = 0;
  byte_e028c = 0;
  byte_e0250 = 0;
  faceoff_spot._2_2_ = 0;
  byte_e02c8 = 0;
  _period_num = 0xffffffff;
  faceoff_spot._0_2_ = 0;
  _dword_c9100 = _dword_c9100 + (int)_away_team_id + user2_team._2_2_ * 0x10000;
  show_names = 0;
  dword_e9b04 = 0x708;
  period_over = 0;
  user2_slot = 0xffff;
  _user1_slot = 0xffff;
  local_28 = 0x47dbc;
  reset_team_for_period(0xdf614);
  local_28 = 0x47dc6;
  apply_line_change(0xdf614);
  local_28 = 0x47dd0;
  dress_line(0xdf614);
  local_28 = 0x47dda;
  reset_team_for_period(0xdf714);
  local_28 = 0x47de4;
  apply_line_change(0xdf714);
  local_28 = 0x47dee;
  dress_line(0xdf714);
  local_28 = 0x47df3;
  reset_players_for_faceoff();
  puVar8 = &unk_dfd9c;
  for (iStackY_18 = 0; (short)iStackY_18 < 2; iStackY_18 = iStackY_18 + 1) {
    for (sVar4 = 0; sVar4 < 5; sVar4 = sVar4 + 1) {
      acStackY_24[sVar4] = '\0';
    }
    for (sVar4 = 0; sVar4 < 6; sVar4 = sVar4 + 1) {
      if (*(short *)(puVar8 + 0x1a) == 0) {
        *(undefined2 *)(puVar8 + 2) = 0;
        *(undefined2 *)(puVar8 + 0x2a) = 0;
        if ((puVar8[0x44] & 0x80) == 0) {
          uVar2 = 0xdc;
        }
        else {
          uVar2 = 0xff24;
        }
        *(undefined2 *)(puVar8 + 6) = uVar2;
        *(undefined2 *)(puVar8 + 0x2c) = uVar2;
        *(undefined2 *)(puVar8 + 0x2e) = 0xff9c;
        *(undefined2 *)(puVar8 + 0xe) = 0;
        *(undefined2 *)(puVar8 + 0xc) = *(undefined2 *)(puVar8 + 0xe);
        if ((puVar8[0x44] & 0x80) == 0) {
          uVar2 = 4;
        }
        else {
          uVar2 = 0;
        }
        *(undefined2 *)(puVar8 + 0x36) = uVar2;
        local_28 = 0x47e79;
        set_animation(puVar8,0x99);
      }
      else {
        local_28 = 0x47e88;
        iVar5 = randomrange(5);
        while (iVar6 = (int)(short)iVar5, acStackY_24[iVar6] != '\0') {
          iVar5 = (iVar6 + 1) % 5;
        }
        acStackY_24[iVar6] = '\x01';
        local_28 = 0x47eb8;
        sVar3 = randomrange(8,iVar5 * 0x28 + -0x50);
        sVar3 = extraout_DX + sVar3 + -4;
        *(short *)(puVar8 + 2) = sVar3;
        *(short *)(puVar8 + 0x2a) = sVar3;
        local_28 = 0x47ecf;
        sVar3 = randomrange(2);
        *(short *)(puVar8 + 2) = *(short *)(puVar8 + 2) + sVar3;
        if ((puVar8[0x44] & 0x80) == 0) {
          uVar7 = 0x30;
        }
        else {
          uVar7 = 0xffffffc6;
        }
        local_28 = 0x47eef;
        sVar3 = randomrange(4,uVar7);
        sVar3 = extraout_DX_00 + sVar3 + -2;
        *(short *)(puVar8 + 6) = sVar3;
        *(short *)(puVar8 + 0x2c) = sVar3;
        *(undefined2 *)(puVar8 + 0x36) = 4;
        *(undefined2 *)(puVar8 + 0xe) = 0;
        *(undefined2 *)(puVar8 + 0xc) = *(undefined2 *)(puVar8 + 0xe);
        local_28 = 0x47f1b;
        sVar3 = randomrange(0x28);
        *(short *)(puVar8 + 0x2e) = sVar1 + sVar3 + -0x14;
        local_28 = 0x47f2f;
        set_animation(puVar8,0);
        *(undefined2 *)(puVar8 + 0x12) = 0x171;
      }
      local_28 = 0x47f41;
      set_state(puVar8,0x25);
      puVar8 = puVar8 + -0x80;
    }
  }
  word_dff44 = 0x78;
  puck._2_2_ = 200;
  dword_dff20._2_2_ = 0xfed4;
  word_dff28 = 0;
  word_dff2a = 0;
  local_28 = 0x47f9e;
  set_state(&puck,0x1a);
  word_e0042 = (undefined2)local_1c;
  referee._2_2_ = 0x8e;
  word_e0046 = 0x8e;
  local_28 = 0x47fc3;
  sVar4 = randomrange(2);
  referee._2_2_ = referee._2_2_ + sVar4;
  DAT_000e0020._2_2_ = 0;
  word_e0048 = 0;
  word_e0052 = 4;
  word_e002a = 0;
  word_e0028 = 0;
  local_28 = 0x48002;
  word_e004a = sVar1;
  set_animation(&referee,0);
  word_e002e = 0x289;
  local_28 = 0x4801a;
  set_state(&referee,0x26);
  ref_phase = 0;
  action_flags = action_flags | 0x40;
  puVar9 = &local_28;
  local_28 = 0x4802d;
  sim_tick();
  puVar10 = (undefined *)((int)puVar9 + -4);
  *(undefined4 *)((int)puVar9 + -4) = 0x48032;
  sim_tick();
  *(undefined4 *)(puVar10 + -4) = 0x48037;
  sort_draw_order2();
  dword_d8c6c = 0;
  control_steps_left = 0;
  *p_puck_carrier = 0xff;
  _input_enabled = 0;
  *(undefined4 *)(puVar10 + -4) = 0x48058;
  flush_key_events();
  camera._0_2_ = 0;
  _camera_target_x = 0;
  camera._2_2_ = 0;
  camera_target_y._0_2_ = 0;
  dword_d8c7c = 0x20;
  dword_d8c74 = 0xec;
  if (dword_cbeca >> 0x10 != -1) {
    *(undefined4 *)(puVar10 + -4) = 0x4809c;
    sub_66dda();
  }
  *(undefined4 *)(puVar10 + -4) = 0x480a1;
  select_game_surface();
  word_cbc58 = 0;
  word_cbc56 = 0;
  word_cbc54 = 0;
  word_cbc52 = 0;
  *(undefined4 *)(puVar10 + -4) = 0x480c4;
  draw_clock();
  return;
}


// ================================================================================================
// faceoff_wait_loop @ 0x480cc [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 __watcall faceoff_wait_loop(void)

{
  short sVar1;
  int iVar2;
  undefined4 uVar3;
  int unaff_ECX;
  int iVar4;
  int extraout_EDX;
  int unaff_ESI;
  undefined4 in_stack_0000000c;
  
code_r0x000480cc:
  if (unaff_ECX < 0) {
    dword_d8c7c = 0;
  }
  do {
    if (dword_d8c74 < 0x1a9) {
      if (dword_d8c74 < 0) {
        dword_d8c74 = 0;
      }
    }
    else {
      dword_d8c74 = 0x1a8;
    }
    set_camera_offset(0,0);
    begin_frame();
    draw_rink(dword_d8c7c,dword_d8c74);
    iVar4 = _dword_dd6b0 * 8 + (int)_dword_dd6aa;
    iVar2 = word_dd6b2 * 8 + (int)(short)dword_dd6ac;
    set_view_rect(iVar2,iVar4,iVar2 + 0x140,iVar4 + 0xa8);
    dword_d8c40 = 0;
    draw_sprites((int)(short)dword_d8c7c,(int)(short)dword_d8c74);
    set_camera_offset(-((int)(short)dword_dd6ac + word_dd6b2 * 8),
                      -(_dword_dd6b0 * 8 + (int)_dword_dd6aa));
    present_frame();
    if (word_cbec4 != 0) {
      dword_e9a9e = CONCAT22(input_enabled,(undefined2)dword_e9a9e);
      _input_enabled = 0;
      fade_palette_to(0,&unk_df314);
      word_cbec4 = 0;
      _input_enabled = dword_e9a9e >> 0x10;
    }
    update_ambient_audio((int)(short)unaff_ESI);
    if (pause_requested != 0) goto LAB_0004824e;
    read_control_p1();
    if (((dword_e03be._2_1_ & 0x10) != 0) || ((dword_e03be._2_1_ & 0x20) != 0)) {
LAB_0004821a:
      skip_faceoff_wait = 1;
      word_cbec4 = 1;
LAB_0004824e:
      _input_enabled = 0;
      if (dword_cbeca >> 0x10 != -1) {
        freemem(dword_e0244);
        dword_cbeca = CONCAT22(0xffff,(undefined2)dword_cbeca);
      }
      if (pause_requested == 0) {
        if (skip_faceoff_wait != 0) {
          getpalette(0,0x100,&palette_save);
          fade_palette_to(1,&palette_save,0x10);
        }
        stop_crowd_loop();
        sub_8374d();
        uVar3 = 0;
        iVar2 = dword_d8c74;
        iVar4 = dword_d8c7c;
      }
      else {
        getpalette(0,0x100,&palette_save);
        fade_palette_to(1,&palette_save,0x10);
        fade_ambient_audio();
        stop_crowd_loop();
        sub_8374d();
        pause_requested = 0;
        uVar3 = 0xffffffff;
        iVar2 = dword_d8c74;
        iVar4 = dword_d8c7c;
      }
      dword_d8c7c._2_2_ = (undefined2)((uint)iVar4 >> 0x10);
      dword_d8c7c._0_2_ = (short)iVar4;
      dword_d8c74._2_2_ = (undefined2)((uint)iVar2 >> 0x10);
      dword_d8c74._0_2_ = (short)iVar2;
      return CONCAT44(in_stack_0000000c,uVar3);
    }
    read_control_p2();
    if (((dword_e03be._2_1_ & 0x10) != 0) || ((dword_e03be._2_1_ & 0x20) != 0)) goto LAB_0004821a;
    waittimeout();
    if (dword_e9b04 == 0) goto LAB_0004824e;
    settimeout(4);
    sVar1 = get_frame_ticks();
    iVar2 = dword_d8c6c + sVar1 * 6;
    unaff_ESI = iVar2 / 10;
    dword_d8c6c = iVar2 % 10;
    run_sim_steps((int)(short)unaff_ESI);
    dword_e9b04 = dword_e9b04 - extraout_EDX;
    if (dword_e9b04 < 0) {
      dword_e9b04 = 0;
    }
    unaff_ECX = (short)camera + 0x20;
    dword_d8c74 = 0xec - camera._2_2_;
    dword_d8c7c = unaff_ECX;
    if (unaff_ECX < 0x41) goto code_r0x000480cc;
    dword_d8c7c = 0x40;
  } while( true );
}


// ================================================================================================
// match_sequence @ 0x4830e [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

longlong __watcall match_sequence(short param_1,uint unaff_EDX)

{
  short sVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 extraout_EDX;
  int extraout_EDX_00;
  int iVar4;
  
  __CHK(4);
  if (dword_cc0ec != 0) {
    return (ulonglong)unaff_EDX << 0x20;
  }
  if (param_1 == 0) {
    init_match();
  }
  sound_resume_all();
  __CHK(0x28);
  ticks_elapsed();
  _input_enabled = 1;
  pause_requested = 0;
  dword_c7444 = dword_c7444 + 1000;
  dword_c7448 = dword_c7448 + 1000;
  do {
    if (dword_e9b04 == 0) {
LAB_0004824e:
      _input_enabled = 0;
      if (dword_cbeca >> 0x10 != -1) {
        freemem(dword_e0244);
        dword_cbeca = CONCAT22(0xffff,(undefined2)dword_cbeca);
      }
      if (pause_requested == 0) {
        if (skip_faceoff_wait != 0) {
          getpalette(0,0x100,&palette_save);
          fade_palette_to(1,&palette_save,0x10);
        }
        stop_crowd_loop();
        sub_8374d();
        uVar2 = 0;
        iVar4 = dword_d8c74;
        iVar3 = dword_d8c7c;
      }
      else {
        getpalette(0,0x100,&palette_save);
        fade_palette_to(1,&palette_save,0x10);
        fade_ambient_audio();
        stop_crowd_loop();
        sub_8374d();
        pause_requested = 0;
        uVar2 = 0xffffffff;
        iVar4 = dword_d8c74;
        iVar3 = dword_d8c7c;
      }
      dword_d8c7c._2_2_ = (undefined2)((uint)iVar3 >> 0x10);
      dword_d8c7c._0_2_ = (short)iVar3;
      dword_d8c74._2_2_ = (undefined2)((uint)iVar4 >> 0x10);
      dword_d8c74._0_2_ = (short)iVar4;
      return CONCAT44(extraout_EDX,uVar2);
    }
    settimeout(4);
    sVar1 = get_frame_ticks();
    iVar4 = dword_d8c6c + sVar1 * 6;
    dword_d8c6c = iVar4 % 10;
    sVar1 = (short)(iVar4 / 10);
    run_sim_steps((int)sVar1);
    dword_e9b04 = dword_e9b04 - extraout_EDX_00;
    if (dword_e9b04 < 0) {
      dword_e9b04 = 0;
    }
    dword_d8c7c = (short)camera + 0x20;
    dword_d8c74 = 0xec - camera._2_2_;
    if (dword_d8c7c < 0x41) {
      if (dword_d8c7c < 0) {
        dword_d8c7c = 0;
      }
    }
    else {
      dword_d8c7c = 0x40;
    }
    if (dword_d8c74 < 0x1a9) {
      if (dword_d8c74 < 0) {
        dword_d8c74 = 0;
      }
    }
    else {
      dword_d8c74 = 0x1a8;
    }
    set_camera_offset(0,0);
    begin_frame();
    draw_rink(dword_d8c7c,dword_d8c74);
    iVar3 = _dword_dd6b0 * 8 + (int)_dword_dd6aa;
    iVar4 = word_dd6b2 * 8 + (int)(short)dword_dd6ac;
    set_view_rect(iVar4,iVar3,iVar4 + 0x140,iVar3 + 0xa8);
    dword_d8c40 = 0;
    draw_sprites((int)(short)dword_d8c7c,(int)(short)dword_d8c74);
    set_camera_offset(-((int)(short)dword_dd6ac + word_dd6b2 * 8),
                      -(_dword_dd6b0 * 8 + (int)_dword_dd6aa));
    present_frame();
    if (word_cbec4 != 0) {
      dword_e9a9e = CONCAT22(input_enabled,(undefined2)dword_e9a9e);
      _input_enabled = 0;
      fade_palette_to(0,&unk_df314);
      word_cbec4 = 0;
      _input_enabled = dword_e9a9e >> 0x10;
    }
    update_ambient_audio((int)sVar1);
    if (pause_requested != 0) goto LAB_0004824e;
    read_control_p1();
    if (((dword_e03be._2_1_ & 0x10) != 0) || ((dword_e03be._2_1_ & 0x20) != 0)) {
LAB_0004821a:
      skip_faceoff_wait = 1;
      word_cbec4 = 1;
      goto LAB_0004824e;
    }
    read_control_p2();
    if (((dword_e03be._2_1_ & 0x10) != 0) || ((dword_e03be._2_1_ & 0x20) != 0)) goto LAB_0004821a;
    waittimeout();
  } while( true );
}


// ================================================================================================
// sequence_loop @ 0x48333 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 __watcall sequence_loop(undefined4 param_1,undefined4 unaff_EDX)

{
  short sVar1;
  undefined4 uVar2;
  int iVar3;
  int extraout_EDX;
  int iVar4;
  
  __CHK(0x28);
  ticks_elapsed();
  _input_enabled = 1;
  pause_requested = 0;
  dword_c7444 = dword_c7444 + 1000;
  dword_c7448 = dword_c7448 + 1000;
  do {
    if (dword_e9b04 == 0) {
LAB_0004824e:
      _input_enabled = 0;
      if (dword_cbeca >> 0x10 != -1) {
        freemem(dword_e0244);
        dword_cbeca = CONCAT22(0xffff,(undefined2)dword_cbeca);
      }
      if (pause_requested == 0) {
        if (skip_faceoff_wait != 0) {
          getpalette(0,0x100,&palette_save);
          fade_palette_to(1,&palette_save,0x10);
        }
        stop_crowd_loop();
        sub_8374d();
        uVar2 = 0;
        iVar4 = dword_d8c74;
        iVar3 = dword_d8c7c;
      }
      else {
        getpalette(0,0x100,&palette_save);
        fade_palette_to(1,&palette_save,0x10);
        fade_ambient_audio();
        stop_crowd_loop();
        sub_8374d();
        pause_requested = 0;
        uVar2 = 0xffffffff;
        iVar4 = dword_d8c74;
        iVar3 = dword_d8c7c;
      }
      dword_d8c7c._2_2_ = (undefined2)((uint)iVar3 >> 0x10);
      dword_d8c7c._0_2_ = (short)iVar3;
      dword_d8c74._2_2_ = (undefined2)((uint)iVar4 >> 0x10);
      dword_d8c74._0_2_ = (short)iVar4;
      return CONCAT44(unaff_EDX,uVar2);
    }
    settimeout(4);
    sVar1 = get_frame_ticks();
    iVar4 = dword_d8c6c + sVar1 * 6;
    dword_d8c6c = iVar4 % 10;
    sVar1 = (short)(iVar4 / 10);
    run_sim_steps((int)sVar1);
    dword_e9b04 = dword_e9b04 - extraout_EDX;
    if (dword_e9b04 < 0) {
      dword_e9b04 = 0;
    }
    dword_d8c7c = (short)camera + 0x20;
    dword_d8c74 = 0xec - camera._2_2_;
    if (dword_d8c7c < 0x41) {
      if (dword_d8c7c < 0) {
        dword_d8c7c = 0;
      }
    }
    else {
      dword_d8c7c = 0x40;
    }
    if (dword_d8c74 < 0x1a9) {
      if (dword_d8c74 < 0) {
        dword_d8c74 = 0;
      }
    }
    else {
      dword_d8c74 = 0x1a8;
    }
    set_camera_offset(0,0);
    begin_frame();
    draw_rink(dword_d8c7c,dword_d8c74);
    iVar3 = _dword_dd6b0 * 8 + (int)_dword_dd6aa;
    iVar4 = word_dd6b2 * 8 + (int)(short)dword_dd6ac;
    set_view_rect(iVar4,iVar3,iVar4 + 0x140,iVar3 + 0xa8);
    dword_d8c40 = 0;
    draw_sprites((int)(short)dword_d8c7c,(int)(short)dword_d8c74);
    set_camera_offset(-((int)(short)dword_dd6ac + word_dd6b2 * 8),
                      -(_dword_dd6b0 * 8 + (int)_dword_dd6aa));
    present_frame();
    if (word_cbec4 != 0) {
      dword_e9a9e = CONCAT22(input_enabled,(undefined2)dword_e9a9e);
      _input_enabled = 0;
      fade_palette_to(0,&unk_df314);
      word_cbec4 = 0;
      _input_enabled = dword_e9a9e >> 0x10;
    }
    update_ambient_audio((int)sVar1);
    if (pause_requested != 0) goto LAB_0004824e;
    read_control_p1();
    if (((dword_e03be._2_1_ & 0x10) != 0) || ((dword_e03be._2_1_ & 0x20) != 0)) {
LAB_0004821a:
      skip_faceoff_wait = 1;
      word_cbec4 = 1;
      goto LAB_0004824e;
    }
    read_control_p2();
    if (((dword_e03be._2_1_ & 0x10) != 0) || ((dword_e03be._2_1_ & 0x20) != 0)) goto LAB_0004821a;
    waittimeout();
  } while( true );
}


// ================================================================================================
// ai_anthem @ 0x4842a [__watcall]
// ================================================================================================

void __watcall ai_anthem(int param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  short sVar1;
  
  __CHK(0x10);
  if (((*(byte *)(param_1 + 0x44) & 0x20) == 0) && (*(int *)(param_1 + 0x2c) >> 0x10 != -100)) {
    sVar1 = *(short *)(param_1 + 0x2e) + -1;
    *(short *)(param_1 + 0x2e) = sVar1;
    if (sVar1 < 1) {
      set_state_reset(param_1,0x27,param_1,unaff_ECX,unaff_EDX,unaff_ECX,unaff_EBX);
    }
    else {
      sVar1 = randomrange(100);
      if (sVar1 == 0) {
        sVar1 = randomrange(2);
        *(short *)(param_1 + 2) = *(short *)(param_1 + 0x2a) + sVar1;
      }
      if ((*(byte *)(param_1 + 0x45) & 2) == 0) {
        sVar1 = randomrange(0x50);
        if (sVar1 == 0) {
          sVar1 = randomrange(9);
          set_animation(param_1,*(int *)(&unk_cc9ce + ((int)sVar1 % 5) * 2) >> 0x10);
          *(byte *)(param_1 + 0x45) = *(byte *)(param_1 + 0x45) | 2;
          return;
        }
      }
    }
  }
  return;
}


// ================================================================================================
// ai_ref_anthem @ 0x484da [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall ai_ref_anthem(int *param_1)

{
  byte bVar1;
  short sVar2;
  undefined2 uVar3;
  int iVar4;
  int iVar5;
  short sVar6;
  
  __CHK(0x14);
  if ((*(byte *)(param_1 + 0x11) & 0x20) == 0) {
    if (param_1[0xb] >> 0x10 == -100) {
      if (10 < dword_e9b04) {
        iVar4 = 0;
        while( true ) {
          if (0xb < iVar4) {
            dword_e9b04 = 10;
            return;
          }
          if ((int)(&unk_df848)[iVar4 * 0x20] >> 0x10 != -100) break;
          iVar4 = iVar4 + 1;
        }
      }
    }
    else {
      if ((0 < *(short *)((int)param_1 + 0x2e)) &&
         (sVar2 = *(short *)((int)param_1 + 0x2e) + -1, *(short *)((int)param_1 + 0x2e) = sVar2,
         0 < sVar2)) {
        sVar2 = randomrange(100);
        if (sVar2 == 0) {
          sVar2 = randomrange(2);
          *(short *)((int)param_1 + 2) = *(short *)((int)param_1 + 0x2a) + sVar2;
        }
        if ((*(byte *)((int)param_1 + 0x45) & 2) != 0) {
          return;
        }
        sVar2 = randomrange(0x50);
        if (sVar2 != 0) {
          return;
        }
        sVar2 = randomrange(2);
        if (sVar2 == 0) {
          uVar3 = 0xdc3;
        }
        else {
          uVar3 = 0xdab;
        }
        set_animation(param_1,uVar3);
        *(byte *)((int)param_1 + 0x45) = *(byte *)((int)param_1 + 0x45) | 2;
        return;
      }
      if ((*(byte *)(param_1 + 0x11) & 2) != 0) {
        *(byte *)(param_1 + 0x11) = *(byte *)(param_1 + 0x11) & 0xfd;
        *(undefined2 *)(param_1 + 10) = 8;
        *(undefined2 *)((int)param_1 + 0x26) = 0;
        *(undefined2 *)((int)param_1 + 0x2a) = 0xfff1;
        *(undefined2 *)(param_1 + 0xb) = 0;
        *(byte *)((int)param_1 + 0x45) = *(byte *)((int)param_1 + 0x45) | 0x20;
        *(undefined2 *)(param_1 + 0xc) = 0;
        *(undefined2 *)((int)param_1 + 0x32) = 0;
        set_animation(param_1,0xa5b);
        camera_target_y._0_2_ = 0;
        ref_phase = 1;
        crowd_noise._2_2_ = 800;
      }
      iVar5 = (*param_1 >> 0x10) - (param_1[10] >> 0x10);
      iVar4 = (param_1[1] >> 0x10) - (*(int *)((int)param_1 + 0x2a) >> 0x10);
      iVar4 = iVar4 * iVar4 + iVar5 * iVar5;
      if (iVar4 < 0x40) {
        if (*(short *)(param_1 + 3) < 0) {
          iVar5 = -(*(int *)((int)param_1 + 10) >> 0x10);
        }
        else {
          iVar5 = *(int *)((int)param_1 + 10) >> 0x10;
        }
        if (iVar5 < 0x10) {
          if (*(short *)((int)param_1 + 0xe) < 0) {
            iVar5 = -(param_1[3] >> 0x10);
          }
          else {
            iVar5 = param_1[3] >> 0x10;
          }
          if (iVar5 < 0x10) {
            *(undefined2 *)((int)param_1 + 2) = *(undefined2 *)((int)param_1 + 0x2a);
            *(undefined2 *)((int)param_1 + 6) = *(undefined2 *)(param_1 + 0xb);
            sVar2 = *(short *)((int)param_1 + 0x26);
            sVar6 = sVar2 + -1;
            *(short *)((int)param_1 + 0x26) = sVar6;
            if (-1 < sVar6) {
              return;
            }
            *(short *)((int)param_1 + 0x26) = sVar2 + 7;
            set_animation(param_1,0xa5b);
            sVar2 = direction8((int)-*(short *)((int)param_1 + 2),(int)-*(short *)((int)param_1 + 6)
                              );
            _dword_e03ac = (int)sVar2;
            if (sVar2 == *(short *)((int)param_1 + 0x36)) {
              *(undefined2 *)((int)param_1 + 0xe) = 0;
              *(undefined2 *)(param_1 + 3) = *(undefined2 *)((int)param_1 + 0xe);
              *(undefined2 *)((int)param_1 + 0x2e) = 0xff9c;
              set_animation(param_1,0xc57);
              return;
            }
            bVar1 = (char)sVar2 - (char)*(short *)((int)param_1 + 0x36) & 7;
            _dword_e03ac = CONCAT22(sVar2 >> 0xf,(ushort)bVar1);
            if (bVar1 < 5) {
              sVar2 = 1;
            }
            else {
              sVar2 = -1;
            }
            *(ushort *)((int)param_1 + 0x36) = sVar2 + (short)((uint)param_1[0xd] >> 0x10) & 7;
            return;
          }
        }
      }
      dword_e03ba._2_2_ = *(undefined2 *)((int)param_1 + 0x2a);
      dword_e03be._2_2_ = *(undefined2 *)(param_1 + 0xb);
      if (0x90 < iVar4) {
        ai_skate_towards(param_1,0);
        return;
      }
      ref_skate_to_point(param_1,0);
    }
  }
  return;
}


// ================================================================================================
// sub_48789 @ 0x48789 [__watcall]
// ================================================================================================

undefined4 __watcall sub_48789(short param_1,short unaff_DX,short unaff_BX)

{
  int iVar1;
  int iVar2;
  
  __CHK(0xc);
  iVar2 = 0;
  while( true ) {
    iVar1 = (int)param_1;
    if (iVar1 <= iVar2) {
      (&unk_e9af8)[iVar1 * 2] = unaff_DX;
      (&unk_e9afa)[iVar1 * 2] = unaff_BX;
      return 1;
    }
    if ((unaff_DX == (&unk_e9af8)[iVar2 * 2]) && (unaff_BX == (&unk_e9afa)[iVar2 * 2])) break;
    iVar2 = iVar2 + 1;
  }
  return 0;
}


// ================================================================================================
// sub_487d9 @ 0x487d9 [__watcall]
// ================================================================================================

undefined4 __watcall sub_487d9(int param_1,int unaff_EDX)

{
  undefined4 *puVar1;
  int iVar2;
  
  __CHK(0xc);
  if (*(int *)(&unk_df690 + param_1 * 0x80 + unaff_EDX) >> 0x10 < -1) {
    return 0;
  }
  if (param_1 != 0) {
    param_1 = 6;
  }
  puVar1 = &entities + param_1 * 0x20;
  iVar2 = 0;
  do {
    if ((int)puVar1[0x11] >> 0x18 == unaff_EDX) {
      if (*(short *)((int)puVar1 + 0x1a) != 6) {
        return 1;
      }
      return 0;
    }
    iVar2 = iVar2 + 1;
    puVar1 = puVar1 + 0x20;
  } while (iVar2 < 6);
  return 1;
}


// ================================================================================================
// compare_player_stats @ 0x4883b [__watcall]
// ================================================================================================

int __watcall compare_player_stats(int *param_1,int *unaff_EDX)

{
  uint uVar1;
  uint uVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int *piVar8;
  int local_1c;
  
  __CHK(0x28);
  uVar1 = (uint)(CONCAT44(*param_1 >> 0x1f,*param_1) / 0x19);
  uVar2 = *unaff_EDX / 0x19;
  iVar6 = *param_1 % 0x19;
  iVar7 = *unaff_EDX % 0x19;
  piVar8 = &word_db088 + uVar1 * 100 + iVar6 * 4;
  piVar3 = &word_db088 + uVar2 * 100 + iVar7 * 4;
  iVar5 = (*piVar8 >> 0x10) + (int)*(short *)piVar8;
  if ((uVar1 == dword_e9af0) && (iVar6 == dword_e9af4)) {
    iVar5 = iVar5 + 2;
  }
  local_1c = (int)*(short *)piVar3 + (*piVar3 >> 0x10);
  if ((uVar2 == dword_e9af0) && (iVar7 == dword_e9af4)) {
    local_1c = local_1c + 2;
  }
  if (iVar5 == local_1c) {
    if (*(short *)piVar3 == *(short *)piVar8) {
      if ((((0 < iVar5) && (uVar1 != uVar2)) &&
          (iVar5 = ((int)(&dword_df622)[uVar2 * 0x40] >> 0x10) -
                   ((int)(&dword_df622)[uVar1 * 0x40] >> 0x10), iVar5 != 0)) && (0 < iVar5 != uVar2)
         ) {
        return iVar5;
      }
      if (*(short *)((int)piVar3 + 0xe) == *(short *)((int)piVar8 + 0xe)) {
        if ((*(short *)((int)piVar3 + 6) < 1) && (*(short *)((int)piVar8 + 6) < 1)) {
          iVar5 = sub_487d9(uVar1,iVar6);
          iVar4 = sub_487d9(uVar2,iVar7);
          if (iVar5 != iVar4) {
            if (iVar4 != 0) {
              return 1;
            }
            return -1;
          }
          iVar5 = iVar6 * 0x14 + uVar1 * 500;
          iVar6 = iVar7 * 0x14 + uVar2 * 500;
          local_1c = (uint)(byte)(&player_ratings)[iVar6 + 0xb] +
                     (uint)(byte)(&player_ratings)[iVar6 + 9] +
                     (uint)(byte)(&player_ratings)[iVar6 + 4] +
                     (uint)(byte)(&player_ratings)[iVar6 + 1] +
                     (uint)(byte)(&player_ratings)[iVar6 + 2] +
                     (uint)(byte)(&player_ratings)[iVar6 + 6] +
                     (uint)(byte)(&player_ratings)[iVar6 + 10] +
                     (uint)(byte)(&player_ratings)[iVar6 + 3] +
                     (uint)(byte)(&player_ratings)[iVar6 + 0xd] +
                     (uint)(byte)(&player_ratings)[iVar6 + 5];
          iVar5 = (uint)(byte)(&player_ratings)[iVar5 + 0xb] +
                  (uint)(byte)(&player_ratings)[iVar5 + 0xd] +
                  (uint)(byte)(&player_ratings)[iVar5 + 6] +
                  (uint)(byte)(&player_ratings)[iVar5 + 4] +
                  (uint)(byte)(&player_ratings)[iVar5 + 1] +
                  (uint)(byte)(&player_ratings)[iVar5 + 2] +
                  (uint)(byte)(&player_ratings)[iVar5 + 9] +
                  (uint)(byte)(&player_ratings)[iVar5 + 10] +
                  (uint)(byte)(&player_ratings)[iVar5 + 3] +
                  (uint)(byte)(&player_ratings)[iVar5 + 5];
          goto LAB_00048abd;
        }
        local_1c = piVar3[1];
        iVar5 = piVar8[1];
      }
      else {
        local_1c = piVar3[3];
        iVar5 = piVar8[3];
      }
      local_1c = local_1c >> 0x10;
      iVar5 = iVar5 >> 0x10;
    }
    else {
      local_1c = (int)*(short *)piVar3;
      iVar5 = (int)*(short *)piVar8;
    }
    local_1c = local_1c - iVar5;
  }
  else {
LAB_00048abd:
    local_1c = local_1c - iVar5;
  }
  return local_1c;
}


// ================================================================================================
// compute_three_stars @ 0x48ac8 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall compute_three_stars(void)

{
  char cVar1;
  longlong lVar2;
  short sVar3;
  short sVar4;
  short sVar5;
  int iVar6;
  short *psVar7;
  ushort uVar8;
  short sVar9;
  int iVar10;
  int iVar11;
  uint uVar12;
  undefined2 auStackY_200f0 [65536];
  int aiStackY_f0 [50];
  int local_28;
  int iStackY_24;
  undefined4 uStackY_20;
  short sStackY_1c;
  
  __CHK(0xf4);
  sVar3 = 0;
  for (sVar9 = 0; sVar9 < 3; sVar9 = sVar9 + 1) {
    (&unk_e9afa)[sVar9 * 2] = 0xffff;
    (&unk_e9af8)[sVar9 * 2] = 0xffff;
  }
  dword_e9af4._0_2_ = -1;
  dword_e9af4._2_2_ = -1;
  dword_e9af0._0_2_ = 0xffff;
  dword_e9af0._2_2_ = 0xffff;
  if (3 < _period_num) {
    if (dword_df722._2_2_ != dword_df622._2_2_) {
      uVar8 = (ushort)(0 < (short)(dword_df722._2_2_ - dword_df622._2_2_));
      uVar12 = (uint)(short)uVar8;
      if (last_touch_slot < 6 != uVar12) {
        dword_e9af0._2_2_ = 0;
        dword_e9af4._0_2_ = (short)((uint)*(undefined4 *)(&word_df642 + uVar12 * 0x80) >> 0x10);
        dword_e9af4._2_2_ = (short)dword_e9af4 >> 0xf;
        dword_e9af0._0_2_ = uVar8;
        iVar6 = game_over_check(dword_df622 >> 0x10,dword_df722 >> 0x10);
        if (iVar6 != 0) {
          sVar3 = sub_48789(0,uVar12,(int)(short)dword_e9af4);
        }
      }
    }
  }
  for (sVar9 = 0; sVar9 < 2; sVar9 = sVar9 + 1) {
    if (*(short *)((int)&dword_df622 + (uint)(sVar9 == 0) * 0x100 + 2) == 0) {
      uVar8 = (ushort)(*(short *)((int)&word_dc240 + sVar9 * 0x12 + 2) <
                      *(short *)((int)&DAT_000dc246 + sVar9 * 0x12 + 2));
      iVar6 = sVar9 * 0x12;
      if ((*(short *)((int)&word_dc240 + iVar6 + 2) < (short)(&unk_dc24e)[sVar9 * 9]) &&
         (*(short *)((int)&DAT_000dc246 + iVar6 + 2) < (short)(&unk_dc24e)[sVar9 * 9])) {
        uVar8 = 2;
      }
      if ((short)(char)(&unk_cc9e4)[(uint)(option_flags << 0x14) >> 0x1e] <
          *(short *)((int)&word_dc240 + (short)uVar8 * 6 + sVar9 * 0x12 + 2)) {
        sVar5 = sub_48789((int)sVar3,(int)sVar9,uVar8 + 0x19);
        sVar3 = sVar3 + sVar5;
      }
    }
  }
  sStackY_1c = 0;
  for (sVar9 = 0; sVar9 < 0x32; sVar9 = sVar9 + 1) {
    iVar6 = (int)sVar9 / 0x19;
    local_28 = iVar6 * 0x444;
    iVar10 = (int)sVar9 % 0x19;
    cVar1 = (&rosters)[iVar10 * 0x27 + local_28];
    if (((cVar1 != '\0') && (cVar1 != '\x02')) &&
       ((psVar7 = (short *)(&word_db088 + iVar6 * 100 + iVar10 * 4), cVar1 != '\x01' ||
        ((((*psVar7 != 0 || (psVar7[1] != 0)) || (psVar7[2] != 0)) ||
         ((psVar7[3] != 0 || (psVar7[7] != 0)))))))) {
      aiStackY_f0[sStackY_1c] = (int)sVar9;
      sStackY_1c = sStackY_1c + 1;
    }
  }
  sub_9244c(aiStackY_f0,(int)sStackY_1c,4);
  sVar9 = 0;
  while( true ) {
    if (sStackY_1c <= sVar9) goto LAB_00048ea9;
    iVar6 = (int)*(short *)(aiStackY_f0 + sVar9) / 0x19;
    local_28 = iVar6 * 400;
    lVar2 = (longlong)(int)*(short *)(aiStackY_f0 + sVar9) % 0x19;
    iVar10 = (int)lVar2;
    if ((*(int *)(&unk_db086 + iVar10 * 0x10 + iVar6 * 400) >> 0x10) +
        ((int)(&word_db088)[iVar6 * 100 + iVar10 * 4] >> 0x10) < 2) break;
    sVar5 = sub_48789((int)sVar3,(int)(short)iVar6,(int)(short)lVar2);
    sVar3 = sVar3 + sVar5;
    if (2 < sVar3) {
      return;
    }
    sVar9 = sVar9 + 1;
  }
  for (sVar5 = 0; sVar5 < 6; sVar5 = sVar5 + 1) {
    iStackY_24 = (int)sVar5 / 3;
    iVar6 = iStackY_24 * 0x12;
    uStackY_20._0_2_ = (undefined2)iVar6;
    uStackY_20._2_2_ = (undefined2)((uint)iVar6 >> 0x10);
    iVar10 = (int)sVar5 % 3;
    iVar11 = iVar6 + iVar10 * 6;
    uStackY_20 = iVar6;
    if (((short)(char)(&unk_cc9e7)[(uint)(option_flags << 0x14) >> 0x1e] <=
         *(short *)((int)&word_dc240 + iVar11 + 2)) &&
       (local_28 = (*(int *)((int)&word_dc240 + iVar11 + 2) >> 0x10) * 1000,
       iVar6 = *(int *)((int)&word_dc240 + iVar11) >> 0x10, (local_28 + iVar6 / 2) / iVar6 < 0x4c))
    {
      sVar4 = sub_48789((int)sVar3,(int)(short)iStackY_24,(int)(short)((short)iVar10 + 0x19));
      sVar3 = sVar3 + sVar4;
      if (2 < sVar3) {
        return;
      }
    }
  }
LAB_00048ea9:
  while( true ) {
    if (sStackY_1c <= sVar9) {
      return;
    }
    sVar5 = sub_48789((int)sVar3,(int)(short)((longlong)(int)*(short *)(aiStackY_f0 + sVar9) / 0x19)
                      ,(int)(short)((longlong)(int)*(short *)(aiStackY_f0 + sVar9) % 0x19));
    sVar3 = sVar3 + sVar5;
    if (2 < sVar3) break;
    sVar9 = sVar9 + 1;
  }
  return;
}


// ================================================================================================
// three_stars_sequence @ 0x48f0b [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall three_stars_sequence(void)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 extraout_EDX;
  undefined4 *puVar4;
  undefined **ppuVar5;
  undefined *puVar6;
  undefined *puStack_18;
  
  __CHK(0x24);
  uVar2 = _period_num;
  if (dword_cc0ec == 0) {
    _input_enabled = dword_cc0ec;
    puStack_18 = (undefined *)0x48f39;
    flush_key_events();
    puStack_18 = &palette_save;
    getpalette(extraout_EDX,0x100);
    puStack_18 = (undefined *)0x48f60;
    fade_palette_to(1,&palette_save);
    word_cbec4 = 1;
    puStack_18 = (undefined *)0x48f6e;
    compute_three_stars();
    uVar1 = dword_cbeca;
    dword_e9ac8._0_1_ = 0xff;
    penalty_box_mode = 0;
    ref_infraction = 0;
    whistle_timer = 0;
    dword_c90d0 = 0;
    dword_cbeca = dword_cbeca & 0xffff0000;
    dword_cbec6 = 0;
    word_cbc6c = 0;
    word_cbc6a = 0;
    word_cbc58 = 0;
    word_cbc56 = 0;
    word_cbc54 = 0;
    word_cbc52 = 0;
    word_e0306 = 0;
    word_e0304 = 0;
    if ((int)uVar1 >> 0x10 != -1) {
      puStack_18 = dword_e0244;
      freemem();
    }
    _word_cbec8 = 0xffff;
    word_cbece = 0xffff;
    dword_cbeca = CONCAT22(0xffff,(undefined2)dword_cbeca);
    byte_e0344 = 0;
    byte_e0308 = 0;
    byte_e028c = 0;
    byte_e0250 = 0;
    byte_e02c8 = 0;
    _period_num = 0xffffffff;
    period_over = 0;
    game_over = 0;
    game_flags = game_flags & 0x7f | 1;
    dword_e9b04 = 12000;
    user2_slot = 0xffff;
    _user1_slot = 0xffff;
    byte_e9abb = 0;
    penalized_count = 0;
    puVar4 = &entities;
    iVar3 = 0;
    do {
      *(undefined2 *)((int)puVar4 + 2) = 0xff38;
      *(undefined2 *)((int)puVar4 + 0x2a) = *(undefined2 *)((int)puVar4 + 2);
      *(undefined2 *)((int)puVar4 + 6) = 0;
      *(undefined2 *)(puVar4 + 0xb) = *(undefined2 *)((int)puVar4 + 6);
      *(undefined2 *)((int)puVar4 + 0x2e) = 0xff9c;
      *(undefined2 *)((int)puVar4 + 0xe) = 0;
      *(undefined2 *)(puVar4 + 3) = *(undefined2 *)((int)puVar4 + 0xe);
      *(undefined2 *)((int)puVar4 + 0x12) = 0xffff;
      *(undefined *)((int)puVar4 + 0x42) = 0xff;
      *(undefined *)((int)puVar4 + 0x43) = *(undefined *)((int)puVar4 + 0x42);
      puStack_18 = (undefined *)0x490de;
      set_animation(puVar4,0);
      puStack_18 = (undefined *)0x490e7;
      set_state(puVar4,0);
      *(byte *)(puVar4 + 0x11) = *(byte *)(puVar4 + 0x11) & 0xd7;
      *(byte *)((int)puVar4 + 0x45) = *(byte *)((int)puVar4 + 0x45) | 4;
      iVar3 = iVar3 + 1;
      puVar4 = puVar4 + 0x20;
    } while (iVar3 < 0xc);
    word_dff44 = 0x78;
    puck._2_2_ = 200;
    dword_dff20._2_2_ = 0xfed4;
    word_dff28 = 0;
    word_dff2a = 0;
    puStack_18 = (undefined *)0x4913b;
    set_state(&puck,0x1a);
    DAT_000dffc4 = 0x78;
    dword_dff9c._2_2_ = 200;
    dword_dffa0._2_2_ = 0xfed4;
    DAT_000dffa8 = 0;
    DAT_000dffaa = 0;
    puStack_18 = (undefined *)0x4916c;
    set_state(&dword_dff9c,0x19);
    word_e0042 = 0;
    referee._2_2_ = 0xff38;
    word_e0046 = 0xff38;
    DAT_000e0020._2_2_ = 0;
    word_e0048 = 0;
    word_e002a = 0;
    word_e0028 = 0;
    puStack_18 = (undefined *)0x491b0;
    set_animation(&referee,0);
    word_e002e = 0xffff;
    puStack_18 = (undefined *)0x491c8;
    set_state(&referee,0x15);
    ref_phase = 0;
    action_flags = action_flags | 0x40;
    ppuVar5 = &puStack_18;
    puStack_18 = (undefined *)0x491db;
    sim_tick();
    puVar6 = (undefined *)((int)ppuVar5 + -4);
    *(undefined4 *)((int)ppuVar5 + -4) = 0x491e0;
    sim_tick();
    *(undefined4 *)(puVar6 + -4) = 0x491e5;
    sort_draw_order2();
    dword_d8c6c = 0;
    control_steps_left = 0;
    *p_puck_carrier = 0xff;
    camera._0_2_ = 0xffe0;
    _camera_target_x = 0xffe0;
    camera._2_2_ = 0;
    camera_target_y._0_2_ = 0;
    *(undefined4 *)(puVar6 + -4) = 0x4921f;
    sub_66dda();
    *(undefined4 *)(puVar6 + -4) = 0x49224;
    iVar3 = sequence_loop();
    if (iVar3 < 0) {
      crowd_noise._2_2_ = 0;
    }
    _period_num = uVar2;
    *(undefined4 *)(puVar6 + -4) = 0x4923a;
    fade_ambient_audio();
    crowd_noise._2_2_ = 0;
    if (sound_enabled == '\0') {
      *(undefined4 *)(puVar6 + -4) = 0x4925b;
      sound_stopall();
    }
    else {
      *(undefined4 *)(puVar6 + -4) = 0x49251;
      sub_837a8();
    }
  }
  return;
}


// ================================================================================================
// sub_49260 @ 0x49260 [__watcall]
// ================================================================================================

void __watcall sub_49260(int param_1,short unaff_DX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  byte bVar1;
  short sVar2;
  
  __CHK(8);
  if (*(short *)(param_1 + 0x1a) == 0) {
    goalie_move(param_1,(int)unaff_DX);
    return;
  }
  bVar1 = (byte)unaff_DX & 0xf;
  if (bVar1 < 8) {
    sVar2 = (ushort)bVar1 - *(short *)(param_1 + 0x36);
    if (sVar2 != 0) {
      *(ushort *)(param_1 + 0x36) =
           (short)((int)(-(int)sVar2 & 4U) >> 1) + -1 +
           (short)((uint)*(undefined4 *)(param_1 + 0x34) >> 0x10) & 7;
    }
    set_animation(param_1,0x2e9,param_1,unaff_ECX,unaff_EBX);
    skating_accelerate(param_1,*(int *)(param_1 + 0x34) >> 0x10);
  }
  else {
    if ((bVar1 == 9) &&
       (*(int *)(param_1 + 10) >> 0x10 != 0 || *(int *)(param_1 + 0xc) >> 0x10 != 0)) {
      brake(param_1);
      return;
    }
    if ((*(byte *)(param_1 + 0x45) & 2) == 0) {
      set_animation(param_1,0x289,param_1,unaff_ECX,unaff_EBX);
      return;
    }
  }
  return;
}


// ================================================================================================
// sub_492f9 @ 0x492f9 [__watcall]
// ================================================================================================

void __watcall
sub_492f9(undefined4 *param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  char cVar1;
  undefined2 uVar2;
  char cVar5;
  int iVar3;
  int iVar4;
  short sVar6;
  short sVar7;
  ushort uVar8;
  int iVar9;
  
  __CHK(0x10);
  cVar1 = *(char *)((int)param_1 + 0x29);
  cVar5 = cVar1 + -1;
  *(char *)((int)param_1 + 0x29) = cVar5;
  if (-1 < cVar5) goto LAB_0004944f;
  *(char *)((int)param_1 + 0x29) = cVar1 + '\v';
  sVar6 = ((short)((uint)dword_e03ba >> 0x10) -
          (short)(char)((uint)*(undefined4 *)((int)param_1 + 10) >> 0x18)) -
          (short)((uint)*param_1 >> 0x10);
  dword_e03ba = CONCAT22(sVar6,(undefined2)dword_e03ba);
  sVar7 = ((short)((uint)dword_e03be >> 0x10) - (short)(char)((uint)param_1[3] >> 0x18)) -
          (short)((uint)param_1[1] >> 0x10);
  dword_e03be = CONCAT22(sVar7,(undefined2)dword_e03be);
  iVar3 = (int)sVar6;
  iVar4 = iVar3;
  if (sVar6 < 0) {
    iVar4 = -iVar3;
  }
  iVar9 = (int)sVar7;
  if (iVar4 < 0xd) {
    iVar4 = iVar9;
    if (sVar7 < 0) {
      iVar4 = -iVar9;
    }
    if (0xc < iVar4) goto LAB_000493b0;
    dword_e03ba = CONCAT22(9,(undefined2)dword_e03ba);
  }
  else {
LAB_000493b0:
    uVar2 = direction8(iVar3,iVar9,param_1,unaff_ECX,unaff_EDX,unaff_ECX,unaff_EBX);
    dword_e03ba = CONCAT22(uVar2,(undefined2)dword_e03ba);
  }
  *(undefined *)(param_1 + 10) = dword_e03ba._2_1_;
  if ((7 < dword_e03ba._2_2_) &&
     ((int)param_1[3] >> 0x10 == 0 && *(int *)((int)param_1 + 10) >> 0x10 == 0)) {
    sVar6 = *(short *)((int)param_1 + 0x2a) - *(short *)((int)param_1 + 2);
    dword_e03ba = CONCAT22(sVar6,(undefined2)dword_e03ba);
    sVar7 = *(short *)(param_1 + 0xb) - *(short *)((int)param_1 + 6);
    dword_e03be = CONCAT22(sVar7,(undefined2)dword_e03be);
    sVar6 = direction8((int)sVar6,(int)sVar7,param_1,*(short *)((int)param_1 + 6),unaff_EDX,
                       unaff_ECX,unaff_EBX);
    uVar8 = *(short *)((int)param_1 + 0x36) - sVar6;
    dword_e03ba = CONCAT22(uVar8,(undefined2)dword_e03ba);
    if (uVar8 != 0) {
      *(ushort *)((int)param_1 + 0x36) =
           ((short)((uint)param_1[0xd] >> 0x10) + ((short)(uVar8 & 4) >> 1)) - 1U & 7;
    }
  }
LAB_0004944f:
  sub_49260(param_1,*(int *)((int)param_1 + 0x25) >> 0x18);
  return;
}


// ================================================================================================
// ai_three_stars @ 0x49460 [__watcall]
// ================================================================================================

void __watcall ai_three_stars(int *param_1)

{
  ushort uVar1;
  undefined2 uVar2;
  int iVar3;
  ushort extraout_DX;
  int iVar4;
  short sVar5;
  
  __CHK(0x14);
  if ((*(byte *)(param_1 + 0x11) & 0x20) == 0) {
    if ((*(byte *)(param_1 + 0x11) & 2) != 0) {
      *(byte *)(param_1 + 0x11) = *(byte *)(param_1 + 0x11) & 0xfd;
      *(undefined2 *)((int)param_1 + 0x2e) = 0;
      *(undefined2 *)(param_1 + 10) = 8;
      uVar1 = (ushort)((*(byte *)(param_1 + 0x11) & 0x40) != 0);
      if (((*(short *)((int)param_1 + 0x1a) == 0) || (uVar1 != 0)) ||
         (dword_df622._2_2_ <= dword_df722._2_2_)) {
        *(undefined2 *)((int)param_1 + 0x26) = 0xffff;
      }
      else {
        uVar2 = randomrange(8);
        *(undefined2 *)((int)param_1 + 0x26) = uVar2;
        uVar1 = extraout_DX;
      }
      *(undefined2 *)((int)param_1 + 0x2a) =
           *(undefined2 *)(&unk_cc9ea + (param_1[0xb] >> 0x10) * 4 + (short)uVar1 * 0x10);
      *(undefined2 *)(param_1 + 0xb) =
           *(undefined2 *)(&unk_cc9ec + (param_1[0xb] >> 0x10) * 4 + (short)uVar1 * 0x10);
    }
    iVar4 = (*param_1 >> 0x10) - (param_1[10] >> 0x10);
    iVar3 = (param_1[1] >> 0x10) - (*(int *)((int)param_1 + 0x2a) >> 0x10);
    if (iVar3 * iVar3 + iVar4 * iVar4 < 900) {
      sVar5 = *(short *)((int)param_1 + 0x2e) + 1;
      *(short *)((int)param_1 + 0x2e) = sVar5;
      if (3 < sVar5) {
        ai_default_skate(param_1);
        return;
      }
      iVar3 = (short)(ushort)((*(byte *)(param_1 + 0x11) & 0x40) != 0) * 0x10;
      *(undefined2 *)((int)param_1 + 0x2a) =
           *(undefined2 *)(&unk_cc9ea + iVar3 + (param_1[0xb] >> 0x10) * 4);
      *(undefined2 *)(param_1 + 0xb) =
           *(undefined2 *)(&unk_cc9ec + (param_1[0xb] >> 0x10) * 4 + iVar3);
      if (*(short *)((int)param_1 + 0x26) == *(short *)((int)param_1 + 0x2e)) {
        *(byte *)(param_1 + 0x11) = *(byte *)(param_1 + 0x11) | 0x20;
        set_animation(param_1,0x731);
        return;
      }
    }
    dword_e03ba._2_2_ = *(undefined2 *)((int)param_1 + 0x2a);
    dword_e03be._2_2_ = *(undefined2 *)(param_1 + 0xb);
    sub_492f9(param_1);
  }
  return;
}


// ================================================================================================
// ai_ref_three_stars @ 0x495b8 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall ai_ref_three_stars(int param_1)

{
  char cVar1;
  int iVar2;
  short sVar3;
  undefined2 uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  undefined4 *puVar8;
  int iVar9;
  
  __CHK(0x2c);
  if ((dword_cbebe >> 0x10 == -1) ||
     ((0xf < dword_cbebe._2_2_ && ((dword_cbebe._2_2_ < 600 || (0x267 < dword_cbebe._2_2_)))))) {
    if ((*(byte *)(param_1 + 0x44) & 2) != 0) {
      *(byte *)(param_1 + 0x44) = *(byte *)(param_1 + 0x44) & 0xfd;
      byte_e02c8 = aEASports[0];
      byte_e02c8_1._0_1_ = aEASports[1];
      byte_e02c8_1._1_1_ = aEASports[2];
      byte_e02c8_1._2_1_ = aEASports[3];
      DAT_000e02cc._0_1_ = aEASports[4];
      DAT_000e02cc._1_1_ = aEASports[5];
      DAT_000e02cc._2_1_ = aEASports[6];
      DAT_000e02cc._3_1_ = aEASports[7];
      DAT_000e02d0._0_1_ = aEASports[8];
      DAT_000e02d0._1_1_ = aEASports[9];
      byte_e0344 = 0;
      byte_e0308 = 0;
      *(undefined2 *)(param_1 + 0x26) = 2;
      sVar3 = randomrange(0x14);
      *(short *)(param_1 + 0x28) = sVar3 + 0x14;
      if (((option_flags._1_1_ & 1) != 0) && (sound_enabled != '\0')) {
        *(short *)(param_1 + 0x28) = sVar3 + 0xf0;
      }
      *(undefined2 *)(param_1 + 0x2a) = 0xffff;
      iVar7 = *(int *)(param_1 + 0x24) >> 0x10;
      iVar9 = *(int *)((int)&dword_e9af4 + iVar7 * 4 + 2) >> 0x10;
      iVar5 = *(int *)(&unk_e9af8 + iVar7 * 2);
      sprintf(&byte_e0250,aSStar,(&star_names)[iVar7]);
      iVar7 = (iVar5 >> 0x10) * 0x27;
      iVar2 = iVar7 + iVar9 * 0x444;
      format_player_name(&byte_e028c,&team_names + iVar9 * 0xba,(&unk_db3ad)[iVar7 + iVar9 * 0x444],
                         &rosters + iVar2 + 7,&rosters + iVar2 + 0x17,&unk_c1b3e);
      sVar3 = user2_team._2_2_;
      if (iVar9 != 0) {
        sVar3 = _away_team_id;
      }
      say_star_wrapper((&team_abbrev)[sVar3],(*(int *)(param_1 + 0x24) >> 0x10) + 1,
                       (&unk_db3ad)[iVar9 * 0x444 + (iVar5 >> 0x10) * 0x27]);
    }
    sVar3 = *(short *)(param_1 + 0x28) + -1;
    *(short *)(param_1 + 0x28) = sVar3;
    if (sVar3 < 1) {
      if (*(short *)(param_1 + 0x26) < 0) {
        dword_e9b04 = 0;
        period_over = 1;
        game_over = 1;
      }
      else {
        iVar5 = (*(int *)(param_1 + 0x28) >> 0x10) * 0x80;
        if (((*(short *)(param_1 + 0x2a) < 0) || (*(short *)(&DAT_000df842 + iVar5) != 100)) ||
           (*(int *)(&DAT_000df82c + iVar5) >> 0x10 != -1)) {
          if (-1 < *(short *)(param_1 + 0x28)) {
            iVar5 = ((&unk_e9af8)[(*(int *)(param_1 + 0x24) >> 0x10) * 2] != 0) + 5;
            *(short *)(param_1 + 0x2a) = (short)iVar5;
            iVar7 = iVar5 * 0x80;
            puVar8 = &entities + iVar5 * 0x20;
            uVar6 = (uint)(((&unk_df860)[iVar7] & 0x40) != 0);
            if (uVar6 == 0) {
              crowd_noise._2_2_ = 0x5dc;
            }
            else {
              crowd_noise._2_2_ = 700;
            }
            cVar1 = *(char *)(&unk_e9afa + (*(int *)(param_1 + 0x24) >> 0x10) * 2);
            (&DAT_000df863)[iVar7] = cVar1;
            if (cVar1 < 0x19) {
              uVar4 = 4;
            }
            else {
              uVar4 = 0;
            }
            (&unk_df836)[iVar5 * 0x40] = uVar4;
            *(undefined2 *)(&DAT_000df842 + iVar7) = 0;
            (&DAT_000df85f)[iVar7] = 0xff;
            (&DAT_000df85e)[iVar7] = (&DAT_000df85f)[iVar7];
            (&unk_df65a)[uVar6 * 0x80 + (int)cVar1] = 0x300;
            *(byte *)(param_1 + 0x45) = *(byte *)(param_1 + 0x45) & 0xfb;
            put_player_on_ice(puVar8,(int)(short)cVar1);
            set_state(puVar8,0);
            set_state_reset(puVar8,0x1d);
            set_state_reset(puVar8,0x14);
            set_state_reset(puVar8,9);
          }
        }
        else {
          sVar3 = randomrange(0x1e);
          *(short *)(param_1 + 0x28) = sVar3 + 0x14;
          if (((option_flags._1_1_ & 1) != 0) && (sound_enabled != '\0')) {
            *(short *)(param_1 + 0x28) = *(short *)(param_1 + 0x28) + 0xdc;
          }
          *(undefined2 *)(param_1 + 0x2a) = 0xffff;
          sVar3 = *(short *)(param_1 + 0x26) + -1;
          *(short *)(param_1 + 0x26) = sVar3;
          if (sVar3 < 0) {
            dword_cbebe = CONCAT22(600,(undefined2)dword_cbebe);
          }
          else {
            iVar7 = *(int *)(param_1 + 0x24) >> 0x10;
            iVar9 = *(int *)((int)&dword_e9af4 + iVar7 * 4 + 2) >> 0x10;
            iVar5 = *(int *)(&unk_e9af8 + iVar7 * 2);
            sprintf(&byte_e0250,aSStar,(&star_names)[iVar7]);
            iVar7 = (iVar5 >> 0x10) * 0x27;
            iVar2 = iVar7 + iVar9 * 0x444;
            format_player_name(&byte_e028c,&team_names + iVar9 * 0xba,
                               (&unk_db3ad)[iVar7 + iVar9 * 0x444],&rosters + iVar2 + 7,
                               &rosters + iVar2 + 0x17,&unk_c1b3e);
            sVar3 = user2_team._2_2_;
            if (iVar9 != 0) {
              sVar3 = _away_team_id;
            }
            say_star_wrapper((&team_abbrev)[sVar3],(*(int *)(param_1 + 0x24) >> 0x10) + 1,
                             (&unk_db3ad)[(iVar5 >> 0x10) * 0x27 + iVar9 * 0x444]);
          }
        }
      }
    }
  }
  return;
}


// ================================================================================================
// ai_get_cup @ 0x499d8 [__watcall]
// ================================================================================================

void __watcall ai_get_cup(int param_1)

{
  short sVar1;
  int iVar2;
  
  __CHK(0x14);
  stoppage_timer = 300;
  if ((*(byte *)(param_1 + 0x44) & 0x20) == 0) {
    if ((*(byte *)(param_1 + 0x44) & 2) != 0) {
      *(byte *)(param_1 + 0x44) = *(byte *)(param_1 + 0x44) & 0xfd;
      *(undefined2 *)(param_1 + 0x28) = 8;
      *(undefined2 *)(param_1 + 0x2c) = 6;
      *(undefined2 *)(param_1 + 0x2a) = 0xff6f;
      *(undefined2 *)(param_1 + 0x26) = 0;
      *(undefined2 *)(param_1 + 0x2e) = 0;
    }
    sVar1 = *(short *)(param_1 + 0x26);
    if (sVar1 == 100) {
      if (word_dffc2 == 100) {
        word_dffc2 = 200;
        byte_dffe2 = 0;
        byte_dffe0 = byte_dffe0 | 0x20;
        set_animation(&dword_dff9c,0xea9);
        *(byte *)(param_1 + 0x55) = *(byte *)(param_1 + 0x55) & 0xf7;
        *(undefined2 *)(param_1 + 0x12) = 0x165;
        *(undefined2 *)(param_1 + 0x36) = 2;
        *(undefined *)(param_1 + 0x46) = 0;
        *(byte *)(param_1 + 0x44) = *(byte *)(param_1 + 0x44) | 0x20;
        set_animation(param_1,0xe83);
        *(undefined2 *)(*(int *)(param_1 + 0x6c) + 0x46 + (*(int *)(param_1 + 0x44) >> 0x18) * 2) =
             0x800;
        ai_default_skate(param_1);
        bench_cheer((*(byte *)(param_1 + 0x44) & 0x40) != 0);
        return;
      }
    }
    else {
      *(short *)(param_1 + 0x26) = sVar1 + -1;
      if ((short)(sVar1 + -1) < 0) {
        *(short *)(param_1 + 0x26) = sVar1 + 7;
        sVar1 = *(short *)(param_1 + 6) - *(short *)(param_1 + 0x2c);
        dword_e03be = CONCAT22(sVar1,(undefined2)dword_e03be);
        dword_e03ba._2_2_ = *(short *)(param_1 + 2) - *(short *)(param_1 + 0x2a);
        iVar2 = (int)sVar1;
        if (sVar1 < 0) {
          iVar2 = -iVar2;
        }
        if ((iVar2 < 5) && (dword_e03ba._2_2_ < 5)) {
          *(undefined2 *)(param_1 + 6) = *(undefined2 *)(param_1 + 0x2c);
          *(undefined2 *)(param_1 + 2) = *(undefined2 *)(param_1 + 0x2a);
          *(undefined2 *)(param_1 + 0xe) = 0;
          *(undefined2 *)(param_1 + 0xc) = 0;
          set_animation(param_1,0x289);
          *(byte *)(param_1 + 0x44) = *(byte *)(param_1 + 0x44) | 4;
          sVar1 = *(short *)(param_1 + 0x36);
          if (sVar1 != 6) {
            if ((sVar1 < 7) && (2 < sVar1)) {
              sVar1 = 1;
            }
            else {
              sVar1 = -1;
            }
            *(ushort *)(param_1 + 0x36) =
                 sVar1 + (short)((uint)*(undefined4 *)(param_1 + 0x34) >> 0x10) & 7;
          }
          if (*(short *)(param_1 + 0x36) != 6) {
            return;
          }
          *(undefined2 *)(param_1 + 0x26) = 100;
          return;
        }
      }
      if ((*(byte *)(param_1 + 0x44) & 4) == 0) {
        dword_e03ba._2_2_ = *(short *)(param_1 + 0x2a);
        dword_e03be = CONCAT22(*(undefined2 *)(param_1 + 0x2c),(undefined2)dword_e03be);
        ref_skate_to_point(param_1,0);
      }
    }
  }
  return;
}


// ================================================================================================
// ai_puck_give_cup @ 0x49bc2 [__watcall]
// ================================================================================================

void __watcall ai_puck_give_cup(int param_1)

{
  short sVar1;
  int iVar2;
  
  __CHK(0x10);
  if ((*(byte *)(param_1 + 0x44) & 2) != 0) {
    ai_puck_shadow(param_1);
    iVar2 = speech_busy();
    if (iVar2 != 0) {
      return;
    }
    if (dword_cbebe._2_2_ == 0x100) {
      dword_cbebe._2_2_ = 600;
    }
    if (-0x20 < (short)camera) {
      return;
    }
    if (camera._2_2_ < 0) {
      iVar2 = -(int)camera._2_2_;
    }
    else {
      iVar2 = (int)camera._2_2_;
    }
    if (0x14 < iVar2) {
      return;
    }
    *(byte *)(param_1 + 0x44) = *(byte *)(param_1 + 0x44) & 0xfd;
    *(undefined2 *)(param_1 + 2) = 0xff42;
    *(undefined2 *)(param_1 + 6) = 3;
    *(undefined2 *)(param_1 + 0x26) = 0;
    *(undefined2 *)(param_1 + 0xe) = 0;
    *(undefined2 *)(param_1 + 0xc) = *(undefined2 *)(param_1 + 0xe);
    *(undefined *)(param_1 + 0x46) = 0;
    *(undefined2 *)(param_1 + 0x12) = 0x362;
    set_animation(param_1,0xe97);
  }
  if (*(short *)(param_1 + 0x26) < 100) {
    if (*(short *)(param_1 + 0x38) == 0) {
      *(undefined2 *)(param_1 + 0x26) = 100;
      return;
    }
    if ((3 < *(short *)(param_1 + 0x3a)) && (*(short *)(param_1 + 0x3c) < 0xc)) {
      *(undefined2 *)(param_1 + 2) = 0xff51;
      return;
    }
  }
  else if ((((*(short *)(param_1 + 0x26) == 200) && (*(short *)(param_1 + 0x12) == 0x365)) &&
           (*(short *)(param_1 + 0x38) == 0)) && (sVar1 = randomrange(0x28), sVar1 == 0)) {
    set_animation(param_1,0xeb5);
  }
  return;
}


// ================================================================================================
// ai_defense_offense @ 0x49cdd [__watcall]
// ================================================================================================

void __watcall ai_defense_offense(int param_1)

{
  byte bVar1;
  char cVar2;
  short sVar3;
  ushort uVar4;
  
  __CHK(0x14);
  if ((*(byte *)(param_1 + 0x44) & 0x20) == 0) {
    sVar3 = handle_line_change(param_1);
    if (sVar3 == 0) {
      if ((game_flags & 1) != 0) {
        skate_idle(param_1);
        return;
      }
      bVar1 = *(byte *)(param_1 + 0x44);
      if ((bVar1 & 8) == 0) {
        if ((bVar1 & 2) != 0) {
          *(byte *)(param_1 + 0x44) = bVar1 & 0xfd;
          *(undefined2 *)(param_1 + 0x26) = 0;
          *(undefined2 *)(param_1 + 0x28) = 8;
        }
        cVar2 = *(char *)(param_1 + 0x27) + -1;
        *(char *)(param_1 + 0x27) = cVar2;
        if (cVar2 < '\0') {
          *(undefined *)(param_1 + 0x27) = *(undefined *)(param_1 + 0x5a);
          if ((*(byte *)(*(int *)(param_1 + 0x6c) + 0x44) & 0x10) != 0) {
LAB_00049d5e:
            set_state(param_1,2);
            return;
          }
          dword_e03be._2_2_ = *p_puck_y;
          if ((*(byte *)(param_1 + 0x44) & 0x80) == 0) {
            dword_e03be._2_2_ = -dword_e03be._2_2_;
          }
          if ((dword_e03be._2_2_ < 0x53) ||
             ((-1 < *p_puck_carrier && (*p_puck_carrier < '\x06' != *(short *)(param_1 + 0x6a) < 6))
             )) goto LAB_00049d5e;
        }
        if (*(short *)(param_1 + 0x1a) == 2) {
          uVar4 = 100;
        }
        else {
          uVar4 = 0xff9c;
        }
        dword_e03be._2_2_ = 0x58;
        dword_e03ba._2_2_ = uVar4;
        if ((*(byte *)(param_1 + 0x44) & 0x80) == 0) {
          dword_e03ba._2_2_ = -uVar4;
          dword_e03be._2_2_ = -0x58;
        }
        if ((short)(*p_puck_x ^ dword_e03ba._2_2_) < 0) {
          uVar4 = ((short)*p_puck_x >> 1) + dword_e03ba._2_2_;
        }
        else {
          uVar4 = *p_puck_x;
        }
        dword_e03ba = CONCAT22(uVar4,(undefined2)dword_e03ba);
        ai_skate_towards(param_1,ai_near_carrier_check);
      }
    }
  }
  return;
}


// ================================================================================================
// ai_defense_defense @ 0x49e3a [__watcall]
// ================================================================================================

void __watcall ai_defense_defense(int param_1)

{
  byte bVar1;
  bool bVar2;
  char cVar3;
  short sVar4;
  undefined2 uVar5;
  int iVar6;
  undefined4 *puVar7;
  
  __CHK(0x18);
  if (((*(byte *)(param_1 + 0x44) & 0x20) == 0) && (sVar4 = handle_line_change(param_1), sVar4 == 0)
     ) {
    if ((game_flags & 1) == 0) {
      bVar1 = *(byte *)(param_1 + 0x44);
      if ((bVar1 & 8) == 0) {
        if ((bVar1 & 2) != 0) {
          *(byte *)(param_1 + 0x44) = bVar1 & 0xfd;
          *(undefined2 *)(param_1 + 0x26) = 0;
          *(undefined2 *)(param_1 + 0x28) = 8;
        }
        cVar3 = *(char *)(param_1 + 0x27) + -1;
        *(char *)(param_1 + 0x27) = cVar3;
        if (cVar3 < '\0') {
          *(undefined *)(param_1 + 0x27) = *(undefined *)(param_1 + 0x5a);
          dword_e03be._2_2_ = *p_puck_y;
          dword_e03ae._2_2_ = *(short *)p_puck_vy >> 6;
          if ((*(byte *)(param_1 + 0x44) & 0x80) == 0) {
            dword_e03be._2_2_ = -dword_e03be._2_2_;
            dword_e03ae._2_2_ = -dword_e03ae._2_2_;
          }
          if (dword_e03ae._2_2_ < 0) {
            dword_e03ae._2_2_ = 0;
          }
          dword_e03ae._2_2_ = dword_e03ae._2_2_ + dword_e03be._2_2_;
          if (((0x4d < dword_e03ae._2_2_) &&
              ((*(byte *)(*(int *)(param_1 + 0x6c) + 0x44) & 0x10) == 0)) && (-1 < *p_puck_carrier))
          {
            if (((stop_flags & 0x20) == 0) ||
               ((stop_flags & 0x40) == (ushort)(*(byte *)(param_1 + 0x44) & 0x40))) {
              bVar2 = true;
            }
            else {
              bVar2 = false;
            }
            if (((bVar2) && (-1 < *p_puck_carrier)) &&
               (*p_puck_carrier < '\x06' == *(short *)(param_1 + 0x6a) < 6)) {
              set_state(param_1,1);
              return;
            }
          }
          if (*(short *)(param_1 + 0x1a) == 2) {
            uVar5 = 0x50;
          }
          else {
            uVar5 = 0xffb0;
          }
          *(undefined2 *)(param_1 + 0x2a) = uVar5;
          if (*(short *)(param_1 + 0x6a) < 6) {
            iVar6 = 6;
          }
          else {
            iVar6 = 0;
          }
          puVar7 = &entities + iVar6 * 0x20;
          dword_e03ac = 6;
          if ((*(byte *)(param_1 + 0x44) & 0x80) == 0) {
            dword_e03ba._2_2_ = -1000;
            do {
              if (((*(byte *)((int)puVar7 + 0x45) & 4) == 0) &&
                 (-1 < *(short *)((int)puVar7 + 0x1a))) {
                dword_e03be._2_2_ = *(short *)((int)puVar7 + 0xe);
                if (dword_e03be._2_2_ < 0) {
                  dword_e03be._2_2_ = 0;
                }
                sVar4 = (dword_e03be._2_2_ >> 4) + (short)((uint)puVar7[1] >> 0x10);
                if (dword_e03ba._2_2_ <= sVar4) {
                  dword_e03ba._2_2_ = sVar4;
                }
              }
              puVar7 = puVar7 + 0x20;
              dword_e03ac = dword_e03ac + -1;
            } while (dword_e03ac != 0);
            sVar4 = dword_e03ba._2_2_ + 0x32;
            dword_e03ba = CONCAT22(sVar4,(undefined2)dword_e03ba);
            if (0xa9 < sVar4) {
              dword_e03ba = CONCAT22(0xc3,(undefined2)dword_e03ba);
            }
            *(short *)(param_1 + 0x2c) = dword_e03ba._2_2_;
            *(short *)(param_1 + 0x2a) = -*(short *)(param_1 + 0x2a);
          }
          else {
            dword_e03ba._2_2_ = 1000;
            do {
              if (((*(byte *)((int)puVar7 + 0x45) & 4) == 0) &&
                 (-1 < *(short *)((int)puVar7 + 0x1a))) {
                dword_e03be._2_2_ = *(short *)((int)puVar7 + 0xe);
                if (0 < dword_e03be._2_2_) {
                  dword_e03be._2_2_ = 0;
                }
                sVar4 = (dword_e03be._2_2_ >> 4) + (short)((uint)puVar7[1] >> 0x10);
                if (sVar4 <= dword_e03ba._2_2_) {
                  dword_e03ba._2_2_ = sVar4;
                }
              }
              puVar7 = puVar7 + 0x20;
              dword_e03ac = dword_e03ac + -1;
            } while (dword_e03ac != 0);
            dword_e03ba._2_2_ = dword_e03ba._2_2_ + -0x32;
            if (dword_e03ba._2_2_ < -0xa9) {
              dword_e03ba = CONCAT22(0xff3d,(undefined2)dword_e03ba);
            }
            *(short *)(param_1 + 0x2c) = dword_e03ba._2_2_;
          }
          if (((int)*p_puck_x ^ *(int *)(param_1 + 0x28) >> 0x10) < 0) {
            *(undefined2 *)(param_1 + 0x2a) = 0;
            iVar6 = dword_e03ba >> 0x10;
            if (dword_e03ba < 0) {
              iVar6 = -iVar6;
            }
            if (iVar6 == 0xc3) {
              if (dword_e03ba < 0) {
                uVar5 = 0xff4a;
              }
              else {
                uVar5 = 0xb6;
              }
              *(undefined2 *)(param_1 + 0x2c) = uVar5;
            }
          }
        }
        dword_e03ba = CONCAT22(*(undefined2 *)(param_1 + 0x2a),(undefined2)dword_e03ba);
        dword_e03be = CONCAT22(*(undefined2 *)(param_1 + 0x2c),(undefined2)dword_e03be);
        ai_skate_towards(param_1,ai_near_carrier_check);
        ai_try_check(param_1);
      }
    }
    else {
      skate_idle(param_1);
    }
  }
  return;
}


// ================================================================================================
// ai_wing_defense @ 0x4a1a6 [__watcall]
// ================================================================================================

void __watcall ai_wing_defense(int param_1)

{
  byte bVar1;
  char cVar2;
  short sVar3;
  undefined4 uVar4;
  short sVar5;
  
  __CHK(0x18);
  if ((*(byte *)(param_1 + 0x44) & 0x20) != 0) {
    return;
  }
  sVar3 = handle_line_change(param_1);
  if (sVar3 != 0) {
    return;
  }
  if ((game_flags & 1) != 0) {
    skate_idle(param_1);
    return;
  }
  bVar1 = *(byte *)(param_1 + 0x44);
  if ((bVar1 & 8) != 0) {
    return;
  }
  if ((bVar1 & 2) != 0) {
    *(byte *)(param_1 + 0x44) = bVar1 & 0xfd;
    *(undefined2 *)(param_1 + 0x26) = 0;
    *(undefined2 *)(param_1 + 0x28) = 8;
  }
  cVar2 = *(char *)(param_1 + 0x27) + -1;
  *(char *)(param_1 + 0x27) = cVar2;
  if (((cVar2 < '\0') &&
      (*(undefined *)(param_1 + 0x27) = *(undefined *)(param_1 + 0x59), -1 < *p_puck_carrier)) &&
     (*p_puck_carrier < '\x06' == *(short *)(param_1 + 0x6a) < 6)) {
    set_state(param_1,4);
    return;
  }
  if (*(short *)(param_1 + 0x1a) == 5) {
    uVar4 = 0xffffff88;
  }
  else {
    uVar4 = 0x78;
  }
  dword_e03ba._2_2_ = (ushort)uVar4;
  dword_e03be._0_2_ = (undefined2)((uint)uVar4 >> 0x10);
  dword_e03be._2_2_ = 0x8e;
  dword_e03ac = 0x44;
  if ((*(byte *)(param_1 + 0x44) & 0x80) == 0) {
    sVar3 = 0x44;
    if ((*(byte *)(*(int *)(param_1 + 0x6c) + 0x44) & 0x10) != 0) goto LAB_0004a315;
    sVar5 = *p_puck_y;
    if (0x44 < sVar5) {
      dword_e03ac = 0xe8;
      sVar3 = dword_e03be._2_2_;
      if (0xe7 < *p_puck_y) {
        dword_e03be._2_2_ = 0xe8;
        sVar3 = dword_e03be._2_2_;
      }
      goto LAB_0004a315;
    }
  }
  else {
    dword_e03ba._2_2_ = -dword_e03ba._2_2_;
    dword_e03be._2_2_ = -0x8e;
    dword_e03ac = 0xffbc;
    if ((*(byte *)(*(int *)(param_1 + 0x6c) + 0x44) & 0x10) != 0) {
      dword_e03be._2_2_ = -0x44;
      sVar3 = dword_e03be._2_2_;
      goto LAB_0004a315;
    }
    sVar3 = *p_puck_y;
    if (-0x45 < *p_puck_y) goto LAB_0004a315;
    sVar5 = -0xe8;
    dword_e03ac = 0xff18;
    sVar3 = dword_e03be._2_2_;
    if (-0xe8 < *p_puck_y) goto LAB_0004a315;
  }
  sVar3 = sVar5;
LAB_0004a315:
  dword_e03be._2_2_ = sVar3;
  if (-1 < (short)(dword_e03ba._2_2_ ^ *p_puck_x)) {
    dword_e03ba._2_2_ = *p_puck_x;
  }
  ai_skate_towards(param_1,0);
  return;
}


