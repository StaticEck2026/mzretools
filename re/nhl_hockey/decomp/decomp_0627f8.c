// Decompiled by Ghidra from hockey.elf (via ledisasm ELF export)
// This is machine generated pseudo-C meant as a reference for porting, it does not compile as is.
#include "prototypes.h"

// ================================================================================================
// sub_627f8 @ 0x627f8 [__watcall]
// ================================================================================================

undefined4 __watcall sub_627f8(void)

{
  __CHK(4);
  return 0;
}


// ================================================================================================
// goal_milestone_check @ 0x62807 [__watcall]
// ================================================================================================

undefined8 __watcall goal_milestone_check(int param_1,undefined4 unaff_EDX,int unaff_EBX)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  
  __CHK(0x30);
  uVar4 = (uint)(*p_puck_y < 0 != ((game_flags & 2) != 0));
  if ((*(char *)(&word_e024c + uVar4) == '\0') ||
     (*(char *)((int)&word_e024c + uVar4 * 2 + 1) == '\0')) {
    iVar5 = 0;
    uVar6 = (uint)(short)((&word_df644)[uVar4 * 0x80] & 0xff);
    if (uVar6 < 0x19) {
      iVar2 = uVar6 * 0x10 + uVar4 * 400;
      iVar1 = *(int *)(&unk_db086 + iVar2) >> 0x10;
      iVar3 = ((int)(&word_db088)[uVar4 * 100 + uVar6 * 4] >> 0x10) + iVar1;
      if (iVar1 == 3) {
        iVar5 = 1;
        unaff_EBX = 3;
      }
      else {
        unaff_EBX = iVar3;
        if (dword_c53fb != 0) {
          if ((option_flags._1_1_ & 2) == 0) {
            unaff_EBX = iVar1 + *(int *)(&unk_deb7c + iVar2);
            if ((unaff_EBX < 10) || (param_1 = unaff_EBX / 10, unaff_EBX % 10 != 0)) {
              unaff_EBX = iVar3 + *(int *)(&unk_deb80 + uVar6 * 0x10 + uVar4 * 400);
              if ((0x13 < unaff_EBX) && (param_1 = unaff_EBX / 0x14, unaff_EBX % 0x14 == 0)) {
                iVar5 = 8;
              }
            }
            else {
              iVar5 = 7;
            }
          }
          else if (*(int *)(&unk_deb7c + iVar2) + *(int *)(&unk_deb74 + iVar2) + iVar1 == 1) {
            iVar5 = 6;
            param_1 = 1;
            unaff_EBX = 1;
          }
          else {
            unaff_EBX = iVar1 + *(int *)(&unk_deb7c + iVar2);
            if ((unaff_EBX < 0x32) || (param_1 = unaff_EBX / 0x32, unaff_EBX % 0x32 != 0)) {
              iVar3 = iVar3 + *(int *)(&unk_deb80 + uVar6 * 0x10 + uVar4 * 400);
              if ((iVar3 < 100) || (param_1 = iVar3 / 100, iVar3 % 100 != 0)) {
                param_1 = uVar6 * 0x10;
                unaff_EBX = unaff_EBX + *(int *)(&unk_deb74 + uVar4 * 400 + param_1);
                if ((unaff_EBX < 100) || (param_1 = unaff_EBX / 100, unaff_EBX % 100 != 0)) {
                  unaff_EBX = iVar3 + *(int *)(&unk_deb78 + uVar4 * 400 + uVar6 * 0x10);
                  if ((99 < unaff_EBX) && (param_1 = unaff_EBX / 100, unaff_EBX % 100 == 0)) {
                    iVar5 = 5;
                  }
                }
                else {
                  iVar5 = 3;
                }
              }
              else {
                iVar5 = 4;
                unaff_EBX = iVar3;
              }
            }
            else {
              iVar5 = 2;
            }
          }
        }
      }
    }
    if ((((dword_c53fb != 0) && (iVar5 == 0)) &&
        (uVar6 = *(int *)(&word_df644 + uVar4 * 0x80) >> 0x10, -1 < (int)uVar6)) &&
       ((int)uVar6 < 0x19)) {
      iVar1 = uVar6 * 0x10 + uVar4 * 400;
      unaff_EBX = (*(int *)(&unk_db086 + iVar1) >> 0x10) +
                  ((int)(&word_db088)[uVar4 * 100 + uVar6 * 4] >> 0x10);
      if ((option_flags._1_1_ & 2) == 0) {
        unaff_EBX = unaff_EBX + *(int *)(&unk_deb80 + iVar1);
        if ((0x13 < unaff_EBX) && (param_1 = unaff_EBX / 0x14, unaff_EBX % 0x14 == 0)) {
          iVar5 = 8;
        }
      }
      else {
        unaff_EBX = unaff_EBX + *(int *)(&unk_deb80 + iVar1);
        if ((unaff_EBX < 100) || (param_1 = unaff_EBX / 100, unaff_EBX % 100 != 0)) {
          unaff_EBX = unaff_EBX + *(int *)(&unk_deb78 + uVar4 * 400 + uVar6 * 0x10);
          if ((99 < unaff_EBX) && (param_1 = unaff_EBX / 100, unaff_EBX % 100 == 0)) {
            iVar5 = 5;
          }
        }
        else {
          iVar5 = 4;
        }
      }
      if (((iVar5 == 0) && (uVar6 = *(int *)(&word_df646 + uVar4 * 0x80) >> 0x10, -1 < (int)uVar6))
         && ((int)uVar6 < 0x19)) {
        iVar1 = uVar6 * 0x10 + uVar4 * 400;
        unaff_EBX = (*(int *)(&unk_db086 + iVar1) >> 0x10) +
                    ((int)(&word_db088)[uVar4 * 100 + uVar6 * 4] >> 0x10);
        if ((option_flags._1_1_ & 2) == 0) {
          unaff_EBX = unaff_EBX + *(int *)(&unk_deb80 + iVar1);
          if ((0x13 < unaff_EBX) && (param_1 = unaff_EBX / 0x14, unaff_EBX % 0x14 == 0)) {
            iVar5 = 8;
          }
        }
        else {
          unaff_EBX = unaff_EBX + *(int *)(&unk_deb80 + iVar1);
          if ((unaff_EBX < 100) || (param_1 = unaff_EBX / 100, unaff_EBX % 100 != 0)) {
            unaff_EBX = unaff_EBX + *(int *)(&unk_deb78 + uVar6 * 0x10 + uVar4 * 400);
            if ((99 < unaff_EBX) && (param_1 = unaff_EBX / 100, unaff_EBX % 100 == 0)) {
              iVar5 = 5;
            }
          }
          else {
            iVar5 = 4;
          }
        }
      }
    }
    if (iVar5 != 0) {
      param_1 = sub_619c8(sub_18f86,uVar4,uVar6,iVar5,unaff_EBX,0,0,0);
      dword_c5840 = 1;
      dword_cbebe._2_2_ = 0xffff;
    }
  }
  return CONCAT44(unaff_EDX,param_1);
}


// ================================================================================================
// sub_62c37 @ 0x62c37 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

longlong __watcall sub_62c37(undefined4 param_1,uint unaff_EDX)

{
  int iVar1;
  uint uVar2;
  bool bVar3;
  
  __CHK(0x24);
  if ((dword_cc0ac != 0x3f) && (-1 < _ref_infraction)) {
    iVar1 = (_ref_infraction >> 0x10) * 0x80;
    bVar3 = ((&unk_df860)[iVar1] & 0x40) != 0;
    uVar2 = 1 << ((byte)((uint)*(undefined4 *)
                                ((&DAT_000df888)[(_ref_infraction >> 0x10) * 0x20] + 0x36) >> 0x10)
                 & 0x1f);
    if (bVar3) {
      uVar2 = uVar2 << 3;
    }
    if ((uVar2 & dword_cc0ac) == 0) {
      dword_cc0ac = dword_cc0ac | uVar2;
      sub_619c8(sub_18f74,bVar3,*(int *)(&unk_df860 + iVar1) >> 0x18,0,0,0,0,0);
      dword_c5840 = 1;
      return CONCAT44(unaff_EDX,1);
    }
  }
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// sub_62cd7 @ 0x62cd7 [__watcall]
// ================================================================================================

undefined4 __watcall sub_62cd7(undefined4 param_1)

{
  int iVar1;
  
  __CHK(4);
  iVar1 = CONCAT22((short)((uint)param_1 >> 0x10),period_idx) << 0xe;
  return CONCAT22((short)((uint)iVar1 >> 0x10),((short)iVar1 + dword_e9ab6._2_2_) - clock_seconds);
}


// ================================================================================================
// maybe_queue_infraction @ 0x62cf9 [__watcall]
// ================================================================================================

void __watcall
maybe_queue_infraction(int param_1,short unaff_DX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  bool bVar1;
  undefined6 uVar2;
  
  __CHK(8);
  if ((((game_flags & 1) == 0) && (*(short *)(param_1 + 0x6a) != 0x10)) &&
     (penalty_shot_active == 0)) {
    if (unaff_DX != 6) {
      if (unaff_DX == 8) {
        bVar1 = ((byte)option_flags & 2) == 0;
      }
      else if (unaff_DX == 0x1d) {
        bVar1 = ((byte)option_flags & 8) == 0;
      }
      else {
        if (((byte)option_flags & 1) == 0) {
          return;
        }
        if ('\a' < (char)(&penalized_count)[(*(byte *)(param_1 + 0x44) & 0x40) != 0]) {
          return;
        }
        uVar2 = injury_check(param_1);
        unaff_DX = (short)((uint6)uVar2 >> 0x20);
        bVar1 = (int)uVar2 == 0;
      }
      if (bVar1) {
        return;
      }
    }
    queue_infraction(param_1,(int)unaff_DX,param_1,unaff_ECX,unaff_EBX);
  }
  return;
}


// ================================================================================================
// queue_infraction @ 0x62d80 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall queue_infraction(int param_1,short unaff_DX)

{
  int iVar1;
  short sVar2;
  undefined4 uVar3;
  
  __CHK(0xc);
  if (((action_flags & 0x80) == 0) && (penalty_box_mode == 0)) {
    if ((penalty_shot_setup == 0) &&
       (_dword_cbec6 >> 0x10 < *(int *)(&infraction_priority + unaff_DX * 4))) {
      sVar2 = *(short *)(&infraction_priority + unaff_DX * 4);
      _dword_cbec6 = CONCAT22(sVar2,dword_cbec6);
      if ((sVar2 != -1) && (sVar2 != 6)) {
        dword_cbeca._0_2_ = 0x50;
      }
    }
    if (6 < unaff_DX) {
      if ((crowd_noise._2_2_ < 0x321) &&
         (crowd_noise._2_2_ = crowd_noise._2_2_ + 400, 800 < crowd_noise._2_2_)) {
        crowd_noise._2_2_ = 800;
      }
      if ((*(byte *)(param_1 + 0x44) & 0x40) == 0) {
        uVar3 = 0xa0;
      }
      else {
        excitement._2_2_ = excitement._2_2_ + 0x14;
        uVar3 = 0x7d;
      }
      play_sfx(uVar3);
    }
    for (sVar2 = 0; sVar2 < 0x20; sVar2 = sVar2 + 1) {
      iVar1 = sVar2 * 2;
      if (*(char *)((int)&infraction_queue + iVar1 + 3) == '\0') {
        *(char *)((int)&infraction_queue + iVar1 + 3) = (char)unaff_DX;
        (&unk_e9a17)[iVar1] = *(undefined *)(param_1 + 0x6a);
        if ((&infraction_is_penalty)[unaff_DX] == '\0') {
          return;
        }
        if ((*(byte *)(param_1 + 0x45) & 0x10) != 0) {
          (&unk_e9a17)[iVar1] = 0;
          *(undefined *)((int)&infraction_queue + iVar1 + 3) = 0;
          return;
        }
        *(byte *)(param_1 + 0x45) = *(byte *)(param_1 + 0x45) | 0x10;
        return;
      }
    }
  }
  return;
}


// ================================================================================================
// ref_announce @ 0x62ea2 [__watcall]
// ================================================================================================

void __watcall
ref_announce(short param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  undefined2 uVar1;
  
  __CHK(8);
  if ((param_1 != 5) && (param_1 != 0x1c)) {
    ref_phase = 0;
    if (param_1 == 7) {
      uVar1 = 0x23;
    }
    else {
      uVar1 = 0x20;
    }
    ref_infraction = param_1;
    set_state(&referee,uVar1,unaff_EBX,unaff_ECX,unaff_EDX);
  }
  return;
}


// ================================================================================================
// penalty_box_update @ 0x62ee9 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall penalty_box_update(void)

{
  short *psVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  short sVar6;
  undefined4 *puVar7;
  byte bVar8;
  short sVar9;
  int iVar10;
  short sVar11;
  undefined2 uStack_2a;
  undefined local_28;
  byte bStack_27;
  undefined2 local_26;
  char cStack_24;
  char cStack_23;
  
  __CHK(0x3c);
  if ((ref_phase == 0) || (iVar3 = speech_busy(), iVar3 != 0)) {
    return;
  }
  while( true ) {
    if (infraction_queue._3_1_ == '\0') {
      if (((dword_cbeca._2_2_ != 0) && (dword_cbeca._2_2_ != 2)) && (-1 < dword_cbebe._2_2_)) {
        return;
      }
      iVar3 = 0xdf614;
      for (sVar11 = 0; sVar11 < 2; sVar11 = sVar11 + 1) {
        sVar9 = 6;
        for (sVar6 = 0x1b; -1 < sVar6; sVar6 = sVar6 + -1) {
          iVar4 = sVar6 * 2 + iVar3;
          if (((0 < *(short *)(iVar4 + 0x7e)) &&
              (bVar8 = *(byte *)(iVar4 + 0x7f), *(byte *)(iVar4 + 0x7f) = bVar8 & 0xdf,
              (bVar8 & 0x10) == 0)) && (4 < sVar9)) {
            sVar9 = sVar9 + -1;
          }
        }
        *(short *)(iVar3 + 0x36) = sVar9;
        iVar3 = 0xdf714;
      }
      game_flags = game_flags & 0xfb;
      if ((&unk_dff3a)[dword_dff36 >> 0x10] == '\x1b') {
        return;
      }
      if ((&unk_dff3a)[dword_dff36 >> 0x10] == '\x1c') {
        return;
      }
      set_state(&puck,0x1b);
      return;
    }
    sVar11 = 1;
    while (*(char *)((int)&infraction_queue + sVar11 * 2 + 3) != '\0') {
      sVar11 = sVar11 + 1;
    }
    sVar11 = sVar11 + -1;
    iVar3 = sVar11 * 2;
    if (((&unk_e9a17)[iVar3] & 0x80) == 0) {
      if (-1 < (short)(&unk_df836)[(*(int *)((int)&infraction_queue + iVar3 + 1) >> 0x18) * 0x40]) {
        return;
      }
      (&unk_e9a17)[iVar3] = 0;
      *(undefined *)((int)&infraction_queue + iVar3 + 3) = 0;
      return;
    }
    bVar8 = (&unk_e9a17)[iVar3] & 0x7f;
    (&unk_e9a17)[iVar3] = bVar8;
    sVar6 = (short)*(char *)((int)&infraction_queue + iVar3 + 3);
    iVar4 = (int)sVar6;
    if (sVar6 == 0x1a) {
      sub_64398();
      sVar6 = dword_e9ab6._2_2_ - clock_seconds;
      if ((clock_seconds < 0x3c) && (clock_sub != 0)) {
        sVar6 = sVar6 + -1;
      }
      iVar3 = (int)sVar11;
      iVar10 = (*(int *)((int)&infraction_queue + iVar3 * 2 + 1) >> 0x18) * 0x80;
      (&unk_e9a17)[iVar3 * 2] = 0;
      *(undefined *)((int)&infraction_queue + iVar3 * 2 + 3) = 0;
      record_penalty(((&unk_df860)[iVar10] & 0x40) != 0,*(int *)(&unk_df860 + iVar10) >> 0x18,
                     iVar4 + -9,0,(int)sVar6 / 0x3c,(int)sVar6 % 0x3c,0);
      goto LAB_00063461;
    }
    cVar2 = (&infraction_is_penalty)[iVar4];
    bStack_27 = cVar2 >> 7;
    if ('\0' < cVar2) break;
    if (cVar2 < '\0') {
      iVar10 = *(int *)((int)&infraction_queue + iVar3 + 1) >> 0x18;
      iVar5 = iVar10 * 0x80;
      uStack_2a = (undefined2)((uint)(&entities + iVar10 * 0x20) >> 0x10);
      iVar3 = (&DAT_000df888)[iVar10 * 0x20];
      *(undefined *)(*(int *)(iVar3 + 0xee) + (*(int *)(&unk_df860 + iVar5) >> 0x18) * 0x27) = 8;
      if (-3 < *(int *)(iVar3 + 0x7c + (*(int *)(&unk_df860 + iVar5) >> 0x18) * 2) >> 0x10) {
        set_state(&entities + iVar10 * 0x20,0x1d);
      }
      *(undefined2 *)(iVar3 + 0x7e + (*(int *)(&unk_df860 + iVar5) >> 0x18) * 2) = 0xfffb;
      sVar6 = dword_e9ab6._2_2_ - clock_seconds;
      if ((clock_seconds < 0x3c) && (clock_sub != 0)) {
        sVar6 = sVar6 + -1;
      }
      record_penalty(((&unk_df860)[iVar5] & 0x40) != 0,*(int *)(&unk_df860 + iVar5) >> 0x18,
                     iVar4 + -9,CONCAT13(bStack_27,CONCAT12(cVar2,uStack_2a)) >> 0x10,
                     (int)sVar6 / 0x3c,(int)sVar6 % 0x3c,(int)sVar11);
      iVar3 = (int)sVar11;
      _penalized_slot = (short)(char)(&unk_e9a17)[iVar3 * 2];
      (&unk_e9a17)[iVar3 * 2] = 0;
      *(undefined *)((int)&infraction_queue + iVar3 * 2 + 3) = 0;
      goto LAB_00063461;
    }
    _penalized_slot = (short)(char)bVar8;
    (&unk_e9a17)[iVar3] = 0;
    *(undefined *)((int)&infraction_queue + iVar3 + 3) = 0;
    if ((((action_flags & 0x80) == 0) && (penalty_box_mode == 0)) || (sVar6 == 7))
    goto LAB_00063461;
  }
  iVar3 = *(int *)((int)&infraction_queue + iVar3 + 1) >> 0x18;
  iVar10 = iVar3 * 0x80;
  puVar7 = &entities + iVar3 * 0x20;
  uStack_2a = (undefined2)((uint)puVar7 >> 0x10);
  iVar3 = (&DAT_000df888)[iVar3 * 0x20];
  *(short *)(iVar3 + 10) = *(short *)(iVar3 + 10) + 1;
  *(short *)(iVar3 + 0xc) = *(short *)(iVar3 + 0xc) + (short)cVar2;
  cStack_24 = (&DAT_000df863)[iVar10];
  cStack_23 = cStack_24 >> 7;
  if (cStack_24 < '\x19') {
    psVar1 = (short *)(*(int *)(iVar3 + 0xe6) +
                       (CONCAT13(cStack_23,CONCAT12(cStack_24,local_26)) >> 0x10) * 0x10 + 4);
    *psVar1 = *psVar1 + (short)cVar2;
  }
  add_penalty_display(((&unk_df860)[iVar10] & 0x40) != 0,(&DAT_000df87a)[iVar10],
                      CONCAT13(bStack_27,CONCAT12(cVar2,uStack_2a)) >> 0x10);
  sVar6 = dword_e9ab6._2_2_ - clock_seconds;
  if ((clock_seconds < 0x3c) && (clock_sub != 0)) {
    sVar6 = sVar6 + -1;
  }
  record_penalty(((&unk_df860)[iVar10] & 0x40) != 0,*(int *)(&unk_df860 + iVar10) >> 0x18,iVar4 + -9
                 ,CONCAT13(bStack_27,CONCAT12(cVar2,uStack_2a)) >> 0x10,(int)sVar6 / 0x3c,
                 (int)sVar6 % 0x3c,(int)sVar11);
  sVar6 = cVar2 * 0x3c;
  local_28 = (undefined)sVar6;
  bStack_27 = (byte)((ushort)sVar6 >> 8);
  if (sVar6 == 300) {
    bStack_27 = bStack_27 | 0x40;
  }
  iVar10 = *(int *)(iVar3 + 0x7c + (CONCAT13(cStack_23,CONCAT12(cStack_24,local_26)) >> 0x10) * 2)
           >> 0x10;
  if ((iVar10 == -3) || (iVar10 == -4)) {
    sVar6 = 0;
    for (puVar7 = *(undefined4 **)(iVar3 + 0xf6);
        (sVar6 < 6 &&
        (((*(short *)((int)puVar7 + 0x1a) < 1 ||
          (*(int *)(iVar3 + 0x7c + ((int)puVar7[0x11] >> 0x18) * 2) >> 0x10 != -1)) ||
         ((*(byte *)((int)puVar7 + 0x45) & 0x10) != 0)))); puVar7 = puVar7 + 0x20) {
      sVar6 = sVar6 + 1;
    }
    if (sVar6 == 6) {
      return;
    }
    cStack_24 = *(char *)((int)puVar7 + 0x47);
    cStack_23 = cStack_24 >> 7;
    (&unk_e9a17)[sVar11 * 2] = (&unk_e9a17)[sVar11 * 2] & 0x80 | *(byte *)((int)puVar7 + 0x6a);
    sprintf(&byte_e0344,aServedByD,(uint)*(byte *)((int)puVar7 + 0x5e));
  }
  iVar10 = (CONCAT13(cStack_23,CONCAT12(cStack_24,local_26)) >> 0x10) * 2 + iVar3;
  bVar8 = bStack_27 | 0x20;
  if ((-1 < *(short *)(iVar10 + 0x7e)) && ((*(byte *)(iVar10 + 0x7f) & 0x10) != 0)) {
    bVar8 = bStack_27 | 0x30;
  }
  bStack_27 = bVar8;
  iVar10 = CONCAT13(cStack_23,CONCAT12(cStack_24,local_26)) >> 0x10;
  *(ushort *)(iVar3 + 0x7e + iVar10 * 2) = CONCAT11(bStack_27,local_28);
  *(undefined *)(*(int *)(iVar3 + 0xee) + iVar10 * 0x27) = 5;
  for (sVar11 = 0; (sVar11 < 0x1c && (-1 < *(char *)(iVar3 + 0xb6 + (int)sVar11)));
      sVar11 = sVar11 + 1) {
  }
  *(char *)(iVar3 + sVar11 + 0xb6) = cStack_24;
  *(undefined *)(iVar3 + sVar11 + 0xb7) = 0xff;
  set_state(puVar7,0xc);
  _penalized_slot = *(short *)((int)puVar7 + 0x6a);
LAB_00063461:
  ref_announce(iVar4);
  return;
}


// ================================================================================================
// sub_63475 @ 0x63475 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall sub_63475(void)

{
  short sVar1;
  int iVar2;
  
  whistle_timer = whistle_timer + -1;
  if (whistle_timer < 0) {
    whistle_timer = 0;
  }
  stoppage_timer = stoppage_timer + -1;
  if (stoppage_timer < 0) {
    game_flags = game_flags & 0xf7;
    whistle_timer = 0;
    sVar1 = 0;
    do {
      iVar2 = (int)sVar1;
      sVar1 = sVar1 + 1;
      if (*(char *)((int)&infraction_queue + iVar2 * 2 + 3) == '\0') {
        whistle_timer = 0;
        return;
      }
    } while ((&infraction_is_penalty)[*(int *)(&unk_e9a11 + sVar1 * 2) >> 0x18] == '\0');
    stop_flags._0_1_ = (byte)stop_flags | 4;
    marker_frames = 0xffff;
    penalty_box_mode = 1;
    *p_puck_carrier = 0xff;
    set_state_reset(&puck,0x1a);
    faceoff_timer = 0x1c20;
    ref_phase._1_1_ = 0xff;
    whistle_timer = 0;
    if ((short)dword_cbeca == 0) {
      _word_cbec8 = 0xffff;
    }
  }
  return;
}


// ================================================================================================
// start_stoppage @ 0x63543 [__watcall]
// ================================================================================================

void __watcall start_stoppage(short param_1)

{
  char cVar1;
  short sVar2;
  int iVar3;
  
  __CHK(0xc);
  cVar1 = *(char *)((int)&infraction_queue + param_1 * 2 + 3);
  if ((game_flags & 1) == 0) {
    game_flags = game_flags | 1;
    faceoff_spot._2_2_ = 0;
    faceoff_spot._0_2_ = 0;
    if (cVar1 != '\a') {
      faceoff_spot._0_2_ = last_touch_x;
      faceoff_spot._2_2_ = last_touch_y;
      if ((cVar1 != '\x03') && (cVar1 != '\x1d')) {
        faceoff_spot._0_2_ = *p_puck_x;
        faceoff_spot._2_2_ = *p_puck_y;
        if (cVar1 == '\b') {
          if (faceoff_spot._2_2_ < 0) {
            iVar3 = -(int)faceoff_spot._2_2_;
          }
          else {
            iVar3 = (int)faceoff_spot._2_2_;
          }
          if (iVar3 < 0x4e) {
            if (faceoff_spot._2_2_ < 0) {
              faceoff_spot._2_2_ = -0x4e;
            }
            else {
              faceoff_spot._2_2_ = 0x4e;
            }
          }
        }
        else if (cVar1 == '\x06') {
          if (((&unk_df860)[(char)(&unk_e9a17)[param_1 * 2] * 0x80] & 0x80) == 0) {
            faceoff_spot._2_2_ = 600;
          }
          else {
            faceoff_spot._2_2_ = -600;
          }
        }
      }
    }
    if (penalty_shot_setup != 0) {
      faceoff_spot._0_2_ = dword_cc110;
      faceoff_spot._2_2_ = dword_cc114;
    }
    if ((short)faceoff_spot < 0x60) {
      if ((short)faceoff_spot < -0x5f) {
        faceoff_spot._0_2_ = -0x60;
      }
    }
    else {
      faceoff_spot._0_2_ = 0x60;
    }
    if (faceoff_spot._2_2_ < 0x90) {
      if (faceoff_spot._2_2_ < -0x8f) {
        if ((short)faceoff_spot < 0) {
          faceoff_spot._0_2_ = -0x60;
        }
        else {
          faceoff_spot._0_2_ = 0x60;
        }
        faceoff_spot._2_2_ = -0xb8;
      }
    }
    else {
      if ((short)faceoff_spot < 0) {
        faceoff_spot._0_2_ = -0x60;
      }
      else {
        faceoff_spot._0_2_ = 0x60;
      }
      faceoff_spot._2_2_ = 0xb8;
    }
    sVar2 = 0;
    do {
      if (((&unk_df860)[(char)((&unk_e9a17)[sVar2 * 2] & 0x7f) * 0x80] & 0x80) == 0) {
        if (faceoff_spot._2_2_ < -0x4d) {
          faceoff_spot._2_2_ = -0x3d;
          if ((short)faceoff_spot < 0) {
            faceoff_spot._0_2_ = -100;
          }
          else {
            faceoff_spot._0_2_ = 100;
          }
        }
      }
      else if (0x4d < faceoff_spot._2_2_) {
        faceoff_spot._2_2_ = 0x3d;
        if ((short)faceoff_spot < 0) {
          faceoff_spot._0_2_ = -100;
        }
        else {
          faceoff_spot._0_2_ = 100;
        }
      }
      sVar2 = sVar2 + 1;
    } while (*(char *)((int)&infraction_queue + sVar2 * 2 + 3) != '\0');
  }
  stoppage_timer = 0;
  game_flags = game_flags | 4;
  play_sfx(0xa4);
  ref_announce(5);
  return;
}


// ================================================================================================
// process_infractions @ 0x637b5 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall process_infractions(void)

{
  char cVar1;
  int iVar2;
  uint extraout_EDX;
  uint extraout_EDX_00;
  uint uVar3;
  
  __CHK(0x10);
  if (((action_flags & 0x80) == 0) && (uVar3 = (uint)penalty_box_mode, penalty_box_mode == 0)) {
    while( true ) {
      iVar2 = (short)uVar3 * 2;
      cVar1 = *(char *)((int)&infraction_queue + iVar2 + 3);
      if (cVar1 == '\0') break;
      if ((game_flags & 4) == 0) {
        if ((&infraction_is_penalty)[cVar1] == '\0') {
LAB_00063871:
          start_stoppage((int)(short)uVar3);
          uVar3 = extraout_EDX_00;
          goto LAB_00063879;
        }
        if ((-1 < *p_puck_carrier) &&
           ((char)(&unk_e9a17)[iVar2] < '\x06' == *p_puck_carrier < '\x06')) {
          whistle_timer = 0x28;
          if (_dword_cbec6 >> 0x10 != -1) {
            dword_cbeca._0_2_ = 0x50;
          }
          goto LAB_00063871;
        }
        if ((game_flags & 8) == 0) {
          game_flags = game_flags | 8;
          ref_announce(0x1c);
          uVar3 = extraout_EDX;
        }
      }
      else {
LAB_00063879:
        iVar2 = (short)uVar3 * 2;
        if (((&unk_e9a17)[iVar2] & 0x80) == 0) {
          (&unk_e9a17)[iVar2] = (&unk_e9a17)[iVar2] | 0x80;
          if (stoppage_timer < (short)((short)(char)(&stoppage_duration)[cVar1] << 5)) {
            stoppage_timer = (short)(char)(&stoppage_duration)[cVar1] << 5;
          }
          if (dword_cbec6 != 0) {
            stoppage_timer = 0x140;
          }
          if ((penalty_shot_setup == 0) || (cVar1 != '\x05')) {
            cVar1 = (&announce_delay)[cVar1];
          }
          else {
            stoppage_timer = (short)byte_c9111 << 5;
            cVar1 = byte_c9146;
          }
          if (marker_frames < (short)(cVar1 * 0x20)) {
            marker_frames = cVar1 * 0x20;
          }
        }
      }
      uVar3 = uVar3 + 1;
    }
  }
  return;
}


// ================================================================================================
// sub_6392a @ 0x6392a [__watcall]
// ================================================================================================

void __watcall sub_6392a(int param_1,undefined4 param_2,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  uint uVar1;
  short extraout_DX;
  int iVar2;
  
  __CHK(0xc);
  for (iVar2 = *(int *)(param_1 + 0xf6); -1 < *(short *)(iVar2 + 0x1a); iVar2 = iVar2 + 0x80) {
  }
  *(short *)(param_1 + 0x36) = *(short *)(param_1 + 0x36) + 1;
  byte_df658 = byte_df658 | 1;
  byte_df758 = byte_df758 | 1;
  byte_df6e8 = byte_df6e8 | 0x40;
  byte_df7e8 = byte_df7e8 | 0x40;
  uVar1 = (uint)(*(short *)(param_1 + 0x38) < 0);
  *(short *)(iVar2 + 0x1a) = (short)(char)(&unk_cbc36)[(*(int *)(param_1 + 0x34) >> 0x10) + uVar1];
  set_default_state(iVar2);
  put_player_on_ice(iVar2,(int)extraout_DX,iVar2,uVar1,unaff_ECX,unaff_EBX);
  *(byte *)(iVar2 + 0x45) = *(byte *)(iVar2 + 0x45) | 4;
  return;
}


// ================================================================================================
// zone_time_stats @ 0x639a4 [__watcall]
// ================================================================================================

void __watcall zone_time_stats(void)

{
  bool bVar1;
  int iVar2;
  
  __CHK(8);
  if ((game_flags & 0x10) == 0) {
    if (*p_puck_y < 0x4f) {
      if (-0x4f < *p_puck_y) {
        return;
      }
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
    if ((game_flags & 2) != 0) {
      bVar1 = (bool)(bVar1 ^ 1);
    }
    if (bVar1) {
      iVar2 = 0xdf714;
    }
    else {
      iVar2 = 0xdf614;
    }
    *(short *)(iVar2 + 0xe) = *(short *)(iVar2 + 0xe) + 1;
  }
  return;
}


// ================================================================================================
// penalty_expired @ 0x639f9 [__watcall]
// ================================================================================================

void __watcall penalty_expired(int param_1,short unaff_DX)

{
  int iVar1;
  
  __CHK(0xc);
  iVar1 = unaff_DX * 2 + param_1;
  if ((*(ushort *)(iVar1 + 0x7e) & 0x3fff) < 6) {
    if (*(short *)(iVar1 + 0x7e) == 0) {
      sub_6392a(param_1);
    }
    play_sfx(0x97);
  }
  return;
}


// ================================================================================================
// penalty_timers @ 0x63a37 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall penalty_timers(int param_1)

{
  char cVar1;
  int iVar2;
  ushort uVar3;
  short sVar4;
  short sVar5;
  char acStackY_8018 [32765];
  undefined uStackY_1b;
  undefined2 uStackY_1a;
  char acStackY_18 [4];
  
  __CHK(0x1c);
  dword_e03be._2_2_ = 2;
  uRam000e03c2 = 0;
  ram0x000e03b0 = 2;
  sVar5 = 0;
  for (sVar4 = 0; sVar4 < 0x1c; sVar4 = sVar4 + 1) {
    cVar1 = *(char *)(param_1 + 0xb6 + (int)sVar4);
    if (cVar1 < '\0') break;
    dword_e03be._2_2_ = dword_e03be._2_2_ + -1;
    if (-1 < dword_e03be._2_2_) {
      acStackY_18[sVar5] = cVar1;
      sVar5 = sVar5 + 1;
      iVar2 = (short)cVar1 * 2 + param_1;
      uVar3 = *(short *)(iVar2 + 0x7e) - 1;
      *(ushort *)(iVar2 + 0x7e) = uVar3;
      if ((uVar3 & 0x3fff) == 0) {
        *(undefined *)(*(int *)(param_1 + 0xee) + (short)cVar1 * 0x27) = 7;
        *(byte *)(iVar2 + 0x7f) = *(byte *)(iVar2 + 0x7f) & 0xbf;
        ram0x000e03aa = CONCAT22(1,dword_e03a8._2_2_);
        while (iVar2 = (ram0x000e03aa >> 0x10) + (int)sVar4,
              cVar1 = *(char *)(param_1 + 0xb6 + iVar2), *(char *)(param_1 + 0xb5 + iVar2) = cVar1,
              -1 < cVar1) {
          dword_e03ac = dword_e03ac + 1;
        }
        sVar4 = sVar4 + -1;
      }
    }
  }
  if (dword_e03be._2_2_ == 1) {
    iVar2 = CONCAT13(acStackY_18[0],CONCAT21(uStackY_1a,uStackY_1b));
  }
  else if (dword_e03be._2_2_ == 0) {
    penalty_expired(param_1,(int)acStackY_18[0]);
    iVar2 = CONCAT13(acStackY_18[1],CONCAT12(acStackY_18[0],6));
  }
  else {
    if (dword_e03be._2_2_ != -1) {
      return;
    }
    iVar2 = CONCAT13(acStackY_18[1],CONCAT12(acStackY_18[0],uStackY_1a));
  }
  penalty_expired(param_1,iVar2 >> 0x18);
  return;
}


// ================================================================================================
// lead_time_stats @ 0x63b57 [__watcall]
// ================================================================================================

void __watcall lead_time_stats(void)

{
  __CHK(4);
  if (((byte)stop_flags & 0x20) != 0) {
    if (((byte)stop_flags & 0x40) == 0) {
      unk_df61a._2_2_ = unk_df61a._2_2_ + 1;
      return;
    }
    dword_df71c._0_2_ = (short)dword_df71c + 1;
  }
  return;
}


// ================================================================================================
// update_line_timers @ 0x63b85 [__watcall]
// ================================================================================================

void __watcall update_line_timers(void)

{
  short sVar1;
  
  __CHK(8);
  misc_flags = misc_flags & 0xbf;
  sVar1 = dword_c90d0;
  if (((game_flags & 1) == 0) && (penalty_shot_active == 0)) {
    sVar1 = dword_c90d0 + -1;
    if ((short)(dword_c90d0 + -1) < 0) {
      misc_flags = misc_flags | 0x40;
      dword_c90d0 = dword_c90d0 + 0x17;
      zone_time_stats();
      lead_time_stats();
      penalty_timers(0xdf614);
      penalty_timers(0xdf714);
      sVar1 = dword_c90d0;
    }
  }
  dword_c90d0 = sVar1;
  return;
}


// ================================================================================================
// update_stoppage @ 0x63bf8 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall update_stoppage(void)

{
  short sVar1;
  int iVar2;
  
  __CHK(4);
  update_line_timers();
  process_infractions();
  __CHK(0x14);
  if ((game_flags & 1) != 0) {
    update_announcer();
    if ((-1 < marker_frames) && (marker_frames = marker_frames + -1, marker_frames < 0)) {
      stop_flags._0_1_ = (byte)stop_flags | 4;
    }
    if ((game_flags & 4) != 0) {
      if (stoppage_timer < 0) {
        penalty_box_update();
        return;
      }
      whistle_timer = whistle_timer + -1;
      if (whistle_timer < 0) {
        whistle_timer = 0;
      }
      stoppage_timer = stoppage_timer + -1;
      if (stoppage_timer < 0) {
        game_flags = game_flags & 0xf7;
        whistle_timer = 0;
        sVar1 = 0;
        do {
          iVar2 = (int)sVar1;
          sVar1 = sVar1 + 1;
          if (*(char *)((int)&infraction_queue + iVar2 * 2 + 3) == '\0') {
            whistle_timer = 0;
            return;
          }
        } while ((&infraction_is_penalty)[*(int *)(&unk_e9a11 + sVar1 * 2) >> 0x18] == '\0');
        stop_flags._0_1_ = (byte)stop_flags | 4;
        marker_frames = -1;
        penalty_box_mode = 1;
        *p_puck_carrier = 0xff;
        set_state_reset(&puck,0x1a);
        faceoff_timer = 0x1c20;
        ref_phase._1_1_ = 0xff;
        whistle_timer = 0;
        if ((short)dword_cbeca == 0) {
          _word_cbec8 = 0xffff;
        }
      }
    }
  }
  return;
}


// ================================================================================================
// update_lead_change @ 0x63c73 [__watcall]
// ================================================================================================

void __watcall update_lead_change(void)

{
  bool bVar1;
  ushort uVar2;
  int iVar3;
  undefined4 uVar4;
  
  __CHK(0x10);
  iVar3 = 0xdf714;
  if (dword_df648._2_2_ == dword_df748._2_2_) {
    stop_flags = stop_flags & 0xffdf;
    return;
  }
  if ((short)(dword_df648._2_2_ - dword_df748._2_2_) < 1) {
    if ((stop_flags & 0x40) != 0) goto LAB_00063cde;
    uVar2 = stop_flags & 0xff9f | 0x40;
  }
  else {
    iVar3 = 0xdf614;
    uVar2 = stop_flags & 0xff9f;
    if ((stop_flags & 0x40) == 0) goto LAB_00063cde;
  }
  stop_flags = uVar2;
LAB_00063cde:
  if ((stop_flags & 0x20) == 0) {
    stop_flags = stop_flags | 0x20;
    *(short *)(iVar3 + 4) = *(short *)(iVar3 + 4) + 1;
    if ((game_flags & 1) != 0) {
      if (((option_flags._1_1_ & 1) == 0) || (sound_enabled == '\0')) {
        bVar1 = true;
      }
      else {
        bVar1 = false;
      }
      if (bVar1) {
        if (iVar3 == 0xdf614) {
          uVar4 = 1;
        }
        else {
          uVar4 = 4;
        }
        play_speech(uVar4);
      }
    }
  }
  return;
}


// ================================================================================================
// clear_infractions @ 0x63d3c [__watcall]
// ================================================================================================

void __watcall clear_infractions(void)

{
  short sVar1;
  
  __CHK(0xc);
  for (sVar1 = 0; sVar1 < 0x20; sVar1 = sVar1 + 1) {
    (&unk_e9a17)[sVar1 * 2] = 0;
    *(undefined *)((int)&infraction_queue + sVar1 * 2 + 3) = 0;
  }
  return;
}


// ================================================================================================
// goal_ends_penalty @ 0x63d69 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall goal_ends_penalty(ushort param_1)

{
  char cVar1;
  bool bVar2;
  short sVar3;
  int iVar4;
  short sVar5;
  int iVar6;
  int iVar7;
  
  __CHK(0x20);
  if ((short)param_1 < 1) {
    iVar6 = 0xdf614;
  }
  else {
    iVar6 = 0xdf714;
  }
  if (param_1 == 0) {
    iVar7 = 0xdf714;
  }
  else {
    iVar7 = 0xdf614;
  }
  sVar3 = 0;
  sVar5 = 0;
  while (*(char *)((int)&infraction_queue + sVar5 * 2 + 3) != '\0') {
    if ((period_idx == 3) && (dword_df622._2_2_ != dword_df722._2_2_)) {
      bVar2 = false;
    }
    else {
      bVar2 = true;
    }
    if (bVar2) {
      iVar4 = *(int *)((int)&infraction_queue + sVar5 * 2) >> 0x18;
      if (((*(int *)(&unk_c9120 + iVar4) >> 0x18 != -1) &&
          ((&infraction_is_penalty)[iVar4] != '\x05')) &&
         (((&infraction_is_penalty)[iVar4] != '\x02' ||
          (param_1 == (char)(&unk_e9a17)[sVar5 * 2] < '\x06')))) goto LAB_00063e4f;
      if (sVar3 != sVar5) {
        *(undefined *)((int)&infraction_queue + sVar3 * 2 + 3) =
             *(undefined *)((int)&infraction_queue + sVar5 * 2 + 3);
        (&unk_e9a17)[sVar3 * 2] = (&unk_e9a17)[sVar5 * 2];
        sVar3 = sVar3 + 1;
      }
    }
    else {
LAB_00063e4f:
      if ((-1 < (char)(&unk_e9a17)[sVar5 * 2]) && ((char)(&unk_e9a17)[sVar5 * 2] < '\f')) {
        (&unk_df861)[(*(int *)((int)&infraction_queue + sVar5 * 2 + 1) >> 0x18) * 0x80] =
             (&unk_df861)[(*(int *)((int)&infraction_queue + sVar5 * 2 + 1) >> 0x18) * 0x80] & 0xef;
      }
      (&unk_e9a17)[sVar5 * 2] = 0;
      *(undefined *)((int)&infraction_queue + sVar5 * 2 + 3) = 0;
    }
    sVar5 = sVar5 + 1;
  }
  if ((infraction_queue._3_1_ == '\0') && (_word_cbec8 == 6)) {
    _word_cbec8 = -1;
  }
  if (*(short *)(iVar7 + 0x36) < *(short *)(iVar6 + 0x36)) {
    for (sVar5 = 0; sVar5 < 0x1c; sVar5 = sVar5 + 1) {
      cVar1 = *(char *)(sVar5 + 0xb6 + iVar7);
      sVar3 = (short)cVar1;
      if (cVar1 < '\0') {
        return;
      }
      if ((*(byte *)(iVar7 + 0x7f + sVar3 * 2) & 0x40) == 0) break;
    }
    iVar4 = (int)sVar3;
    *(undefined2 *)(iVar7 + 0x7e + iVar4 * 2) = 0;
    *(undefined *)(*(int *)(iVar7 + 0xee) + iVar4 * 0x27) = 7;
    sub_6392a(iVar7,iVar4);
    sub_14ca0(param_1 == 0,*(undefined *)(iVar4 * 0x27 + 5 + *(int *)(iVar7 + 0xee)));
    sVar3 = 1;
    while (cVar1 = *(char *)((int)sVar3 + (int)sVar5 + 0xb6 + iVar7),
          *(char *)((int)sVar3 + (int)sVar5 + 0xb5 + iVar7) = cVar1, -1 < cVar1) {
      sVar3 = sVar3 + 1;
    }
    *(short *)(iVar6 + 2) = *(short *)(iVar6 + 2) + 1;
    byte_df658 = byte_df658 | 1;
    byte_df758 = byte_df758 | 1;
  }
  return;
}


// ================================================================================================
// start_penalty_shot @ 0x63f72 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall start_penalty_shot(void)

{
  undefined2 uVar1;
  int iVar2;
  undefined *puVar3;
  int iVar4;
  undefined4 *puVar5;
  
  __CHK(0x10);
  puVar3 = p_puck_vz;
  *(undefined2 *)p_puck_vz = 0;
  uVar1 = *(undefined2 *)puVar3;
  *(undefined2 *)p_puck_vy = uVar1;
  *(undefined2 *)p_puck_vx = uVar1;
  *p_puck_z = uVar1;
  *p_puck_y = uVar1;
  *p_puck_x = uVar1;
  set_state(&puck,0x18);
  iVar2 = penalty_shot_slot;
  iVar4 = penalty_shot_slot * 0x80;
  puVar5 = &entities + penalty_shot_slot * 0x20;
  (&unk_df861)[iVar4] = (&unk_df861)[iVar4] & 0xdb;
  (&unk_df860)[iVar4] = (&unk_df860)[iVar4] & 0xfb;
  set_state_reset(puVar5,0x2e);
  set_state_reset(puVar5,0x2e);
  set_state_reset(puVar5,0x2e);
  set_state_reset(puVar5,0x2e);
  set_state_reset(puVar5,0x2e);
  set_state_reset(puVar5,0x2e);
  set_state_reset(puVar5,0x2e);
  set_state_reset(puVar5,0x2e);
  if (((int)user1_team == (penalty_shot_team == 0) + 1) && (_user1_slot != -1)) {
    _user1_slot = find_switch_target(0xffffffff);
  }
  if (((int)(short)user2_team == (penalty_shot_team == 0) + 1) && (user2_slot != -1)) {
    user2_slot = find_switch_target(0xffffffff);
  }
  iVar2 = (&DAT_000df888)[iVar2 * 0x20];
  *(undefined2 *)(iVar2 + 0x34) = 0xffff;
  *(undefined2 *)(iVar2 + 0x32) = *(undefined2 *)(iVar2 + 0x34);
  *(undefined2 *)(iVar2 + 0x30) = *(undefined2 *)(iVar2 + 0x34);
  crowd_noise._2_2_ = crowd_noise._2_2_ + 100;
  *p_puck_carrier = (undefined)penalty_shot_slot;
  penalty_shot_active = 1;
  penalty_shot_setup = 1;
  dword_cc120 = 1000;
  clear_infractions();
  return;
}


// ================================================================================================
// count_defenders_ahead @ 0x64102 [__watcall]
// ================================================================================================

undefined8 __watcall count_defenders_ahead(undefined4 param_1,undefined4 unaff_EDX)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  
  __CHK(0x2c);
  defenders_ahead = 0;
  if (-1 < *p_puck_carrier) {
    iVar2 = (int)*p_puck_carrier;
    iVar3 = iVar2 * 0x80;
    iVar4 = (int)(&unk_df820)[iVar2 * 0x20] >> 0x10;
    if (((&unk_df860)[iVar3] & 0x80) == 0) {
      if (iVar4 < 1) {
        iVar2 = approx_distance(iVar4 + 0xe8,(int)(&entities)[iVar2 * 0x20] >> 0x10);
        iVar6 = 0;
        if (*(short *)((int)&DAT_000df884 + iVar3 + 2) < 6) {
          iVar3 = 6;
        }
        else {
          iVar3 = 0;
        }
        piVar5 = &entities + iVar3 * 0x20;
        for (; iVar6 < 6; iVar6 = iVar6 + 1) {
          if (0 < *(short *)((int)piVar5 + 0x1a)) {
            if ((piVar5[1] >> 0x10 < iVar4 + -4) ||
               ((*(short *)((int)piVar5 + 0xe) < 1 &&
                (iVar3 = approx_distance((piVar5[1] >> 0x10) + 0xe8,*piVar5 >> 0x10), iVar3 <= iVar2
                )))) goto LAB_00064128;
          }
          piVar5 = piVar5 + 0x20;
        }
        goto LAB_0006426a;
      }
    }
    else if (-1 < iVar4) {
      iVar2 = approx_distance(iVar4 + -0xe8,(int)(&entities)[iVar2 * 0x20] >> 0x10);
      iVar6 = 0;
      if (*(short *)((int)&DAT_000df884 + iVar3 + 2) < 6) {
        iVar3 = 6;
      }
      else {
        iVar3 = 0;
      }
      piVar5 = &entities + iVar3 * 0x20;
      for (; iVar6 < 6; iVar6 = iVar6 + 1) {
        if (0 < *(short *)((int)piVar5 + 0x1a)) {
          if ((iVar4 + 4 < piVar5[1] >> 0x10) ||
             ((-1 < *(short *)((int)piVar5 + 0xe) &&
              (iVar3 = approx_distance((piVar5[1] >> 0x10) + -0xe8,*piVar5 >> 0x10), iVar3 <= iVar2)
              ))) goto LAB_00064128;
        }
        piVar5 = piVar5 + 0x20;
      }
LAB_0006426a:
      defenders_ahead = 1;
      uVar1 = 1;
      goto LAB_0006346e;
    }
  }
LAB_00064128:
  uVar1 = 0;
LAB_0006346e:
  return CONCAT44(unaff_EDX,uVar1);
}


// ================================================================================================
// sub_6427f @ 0x6427f [__watcall]
// ================================================================================================

longlong __watcall sub_6427f(int param_1,uint unaff_EDX)

{
  int iVar1;
  int extraout_EDX;
  
  __CHK(0x10);
  if (((((game_flags & 0x10) == 0) && (((byte)option_flags & 1) != 0)) &&
      ((short)*p_puck_carrier == *(short *)(param_1 + 0x6a))) && (breakaway_flag != 0)) {
    if ((*(byte *)(param_1 + 0x44) & 0x80) == 0) {
      if (((0 < *(short *)(param_1 + 0xe)) || (*(short *)(param_1 + 0x36) < 3)) ||
         (5 < *(short *)(param_1 + 0x36))) goto LAB_000642b8;
    }
    else if ((*(short *)(param_1 + 0xe) < 0) ||
            ((1 < *(short *)(param_1 + 0x36) && (*(short *)(param_1 + 0x36) < 7))))
    goto LAB_000642b8;
    count_defenders_ahead();
    breakaway_flag = defenders_ahead;
    iVar1 = defenders_ahead;
    if (defenders_ahead != 0) {
      if (*(short *)(extraout_EDX + 6) < 0) {
        iVar1 = -(*(int *)(extraout_EDX + 4) >> 0x10);
      }
      else {
        iVar1 = *(int *)(extraout_EDX + 4) >> 0x10;
      }
      if ((0xe4 < iVar1) || (*(short *)(*(int *)(extraout_EDX + 0x70) + 0x38) < 0))
      goto LAB_000642b8;
      iVar1 = 1;
    }
    return CONCAT44(unaff_EDX,iVar1);
  }
LAB_000642b8:
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// note_breakaway @ 0x64338 [__watcall]
// ================================================================================================

longlong __watcall note_breakaway(undefined4 param_1,uint unaff_EDX)

{
  int iVar1;
  
  __CHK(8);
  count_defenders_ahead();
  breakaway_flag = defenders_ahead;
  if ((defenders_ahead != 0) &&
     (crowd_noise._2_2_ = crowd_noise._2_2_ + 100, penalty_shot_phase == 0)) {
    if (*p_puck_carrier < '\x06') {
      iVar1 = 0xdf614;
    }
    else {
      iVar1 = 0xdf714;
    }
    *(short *)(iVar1 + 0x1c) = *(short *)(iVar1 + 0x1c) + 1;
    return CONCAT44(unaff_EDX,1);
  }
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// sub_64398 @ 0x64398 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall sub_64398(void)

{
  int iVar1;
  
  __CHK(0xc);
  if (penalty_shot_phase == 0) {
    penalty_shot_team = (uint)(5 < penalty_shot_slot);
    if (penalty_shot_slot < 6) {
      iVar1 = 0xdf614;
    }
    else {
      iVar1 = 0xdf714;
    }
    *(short *)(iVar1 + 0x20) = *(short *)(iVar1 + 0x20) + 1;
    dword_df648._2_2_ = 1;
    dword_df748._2_2_ = 1;
    dword_cc100 = *(int *)(&unk_df860 + penalty_shot_slot * 0x80) >> 0x18;
    penalty_shot_phase = 1;
    _dword_cc110 = (int)(short)faceoff_spot;
    _dword_cc114 = (int)faceoff_spot._2_2_;
    faceoff_spot._0_2_ = 0;
    faceoff_spot._2_2_ = 0;
  }
  return;
}


// ================================================================================================
// end_penalty_shot @ 0x64439 [__watcall]
// ================================================================================================

void __watcall
end_penalty_shot(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  __CHK(0xc);
  if ((penalty_shot_active != 0) && (penalty_shot_phase != 0)) {
    penalty_shot_phase = 0;
    penalty_shot_active = 0;
    penalty_shot_slot = 0xffffffff;
    queue_infraction(&puck,5,unaff_EBX,0,unaff_EDX,unaff_ECX);
    last_touch_x = dword_cc110;
    last_touch_y = dword_cc114;
    set_state(&referee,0x21);
  }
  return;
}


// ================================================================================================
// sub_644a8 @ 0x644a8 [__watcall]
// ================================================================================================

void __watcall sub_644a8(short param_1,int unaff_EDX,int unaff_EBX,char unaff_CL)

{
  int iVar1;
  undefined uVar2;
  
  __CHK(0x24);
  iVar1 = 0;
  do {
    *(int *)((int)&unk_e9c85 + iVar1 * 4 + 3) = iVar1;
    if ((&unk_db3ae)[param_1 * 0x444 + iVar1 * 0x27] == unaff_CL) {
      (&unk_e9c24)[iVar1] = (int)*(short *)(unaff_EBX + iVar1 * 2);
    }
    else {
      (&unk_e9c24)[iVar1] = 0xffffffff;
    }
    iVar1 = iVar1 + 1;
  } while (iVar1 < 0x19);
  sub_93540(0x19,&unk_e9c24,0x9c88);
  iVar1 = 0;
  do {
    if ((int)(&unk_e9c24)[iVar1] < 0) {
      uVar2 = 0xff;
    }
    else {
      uVar2 = (undefined)((uint)(&unk_e9c85)[iVar1] >> 0x18);
    }
    *(undefined *)(iVar1 + unaff_EDX) = uVar2;
    iVar1 = iVar1 + 1;
  } while (iVar1 < 0x19);
  return;
}


// ================================================================================================
// sub_6455f @ 0x6455f [__watcall]
// ================================================================================================

void __watcall sub_6455f(short param_1,int unaff_EDX,int unaff_EBX)

{
  int iVar1;
  undefined uVar2;
  
  __CHK(0x24);
  iVar1 = 0;
  do {
    *(int *)((int)&unk_e9c85 + iVar1 * 4 + 3) = iVar1;
    if ((&unk_db3ae)[param_1 * 0x444 + iVar1 * 0x27] == 'D') {
      (&unk_e9c24)[iVar1] = 0xffffffff;
    }
    else {
      (&unk_e9c24)[iVar1] = (int)*(short *)(unaff_EBX + iVar1 * 2);
    }
    iVar1 = iVar1 + 1;
  } while (iVar1 < 0x19);
  sub_93540(0x19,&unk_e9c24,0x9c88);
  iVar1 = 0;
  do {
    if ((int)(&unk_e9c24)[iVar1] < 0) {
      uVar2 = 0xff;
    }
    else {
      uVar2 = (undefined)((uint)(&unk_e9c85)[iVar1] >> 0x18);
    }
    *(undefined *)(unaff_EDX + iVar1) = uVar2;
    iVar1 = iVar1 + 1;
  } while (iVar1 < 0x19);
  return;
}


// ================================================================================================
// build_lines @ 0x64614 [__watcall]
// ================================================================================================

void __watcall build_lines(void)

{
  char cVar1;
  int iVar2;
  short sVar3;
  char *pcVar4;
  short *psVar5;
  short sVar6;
  int iVar7;
  int iVar8;
  short asStackY_f0 [50];
  undefined2 auStackY_8c [50];
  int local_28;
  undefined2 *local_24;
  int local_20;
  int iStackY_1c;
  
  __CHK(0xf4);
  for (sVar6 = 0; sVar6 < 2; sVar6 = sVar6 + 1) {
    for (sVar3 = 0; sVar3 < 0x19; sVar3 = sVar3 + 1) {
      iVar8 = (int)sVar6;
      iVar7 = (int)sVar3;
      if (((&rosters)[iVar7 * 0x27 + iVar8 * 0x444] == '\0') ||
         ((&rosters)[iVar7 * 0x27 + iVar8 * 0x444] == '\x01')) {
        asStackY_f0[(int)sVar3 + sVar6 * 0x19] = -1;
        auStackY_8c[(int)sVar3 + sVar6 * 0x19] = 0xffff;
      }
      else {
        iVar2 = iVar8 * 500;
        local_20 = (uint)(byte)(&DAT_000daca1)[iVar7 * 0x14 + iVar2] +
                   (uint)(byte)(&DAT_000daca2)[iVar7 * 0x14 + iVar2] +
                   (uint)(byte)(&DAT_000daca4)[iVar7 * 0x14 + iVar2] +
                   (uint)(byte)(&DAT_000daca6)[iVar7 * 0x14 + iVar2] +
                   (uint)(byte)(&DAT_000daca9)[iVar7 * 0x14 + iVar2] +
                   (uint)(byte)(&DAT_000dacaa)[iVar7 * 0x14 + iVar2] +
                   (uint)(byte)(&DAT_000daca3)[iVar7 * 0x14 + iVar2];
        iStackY_1c = local_20 + (uint)(byte)(&DAT_000dacad)[iVar7 * 0x14 + iVar2];
        auStackY_8c[iVar8 * 0x19 + iVar7] = (short)iStackY_1c;
        asStackY_f0[iVar8 * 0x19 + iVar7] =
             (ushort)(byte)(&DAT_000dacad)[iVar7 * 0x14 + iVar2] +
             (ushort)(byte)(&DAT_000daca3)[iVar7 * 0x14 + iVar2] +
             (ushort)(byte)(&DAT_000dacac)[iVar7 * 0x14 + iVar2] +
             (ushort)(byte)(&DAT_000daca1)[iVar7 * 0x14 + iVar2] +
             (ushort)(byte)(&DAT_000daca2)[iVar7 * 0x14 + iVar2] +
             (ushort)(byte)(&DAT_000daca4)[iVar7 * 0x14 + iVar2] +
             (ushort)(byte)(&DAT_000daca6)[iVar7 * 0x14 + iVar2] +
             (ushort)(byte)(&DAT_000daca9)[iVar7 * 0x14 + iVar2] +
             (ushort)(byte)(&DAT_000dacab)[iVar7 * 0x14 + iVar2] +
             (ushort)(byte)(&DAT_000daca5)[iVar7 * 0x14 + iVar2];
      }
    }
    iVar8 = (int)sVar6;
    local_24 = auStackY_8c + iVar8 * 0x19;
    local_28 = iVar8 * 0x19;
    sub_644a8(iVar8,&unk_e9d50 + local_28,local_24,0x44);
    sub_644a8(iVar8,&unk_e9eae + local_28,local_24,0x52);
    sub_644a8(iVar8,&unk_e9de6 + local_28,local_24,0x4c);
    sub_644a8(iVar8,&unk_e9cec + local_28,local_24,0x43);
    psVar5 = asStackY_f0 + iVar8 * 0x19;
    sub_644a8(iVar8,&unk_e9db4 + local_28,psVar5,0x44);
    sub_644a8(iVar8,&unk_e9d1e + local_28,psVar5,0x52);
    sub_644a8(iVar8,&unk_e9e7c + local_28,psVar5,0x4c);
    sub_644a8(iVar8,&unk_e9d82 + local_28,psVar5,0x43);
    sub_6455f(iVar8,&unk_e9e4a + local_28,local_24);
    sub_6455f(iVar8,&unk_e9ee0 + local_28,psVar5);
    for (sVar3 = 0; sVar3 < 0x19; sVar3 = sVar3 + 1) {
      (&unk_e9e18)[(int)sVar3 + sVar6 * 0x19] =
           (&unk_cd418)[(byte)(&rosters)[sVar6 * 0x444 + sVar3 * 0x27]];
    }
    if (sVar6 == 0) {
      pcVar4 = (char *)&unk_dc200;
    }
    else {
      pcVar4 = &unk_dabf0;
    }
    for (sVar3 = 0; sVar3 < 0x12; sVar3 = sVar3 + 1) {
      cVar1 = *pcVar4;
      pcVar4 = pcVar4 + 1;
      (&unk_e9e18)[(int)cVar1 + sVar6 * 0x19] = 0;
    }
  }
  return;
}


// ================================================================================================
// lineup_player_ok @ 0x64a0b [__watcall]
// ================================================================================================

uint __watcall lineup_player_ok(short param_1,uint unaff_EDX,uint unaff_EBX)

{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  short sVar5;
  undefined4 *puVar6;
  short sVar7;
  short sVar8;
  
  __CHK(0x24);
  if (param_1 == 0) {
    puVar6 = &unk_dc200;
  }
  else {
    puVar6 = (undefined4 *)&unk_dabf0;
  }
  sVar8 = (short)unaff_EBX;
  if (((&unk_cd418)[(byte)(&rosters)[sVar8 * 0x27 + param_1 * 0x444]] == '\0') ||
     (((&unk_cd418)[(byte)(&rosters)[sVar8 * 0x27 + param_1 * 0x444]] == '\x02' &&
      ((&unk_e9e18)[param_1 * 0x19 + (int)sVar8] != '\x02')))) {
LAB_00064a75:
    uVar3 = 0;
  }
  else {
    cVar1 = (&unk_db3ae)[sVar8 * 0x27 + param_1 * 0x444];
    sVar2 = (short)unaff_EDX;
    if (sVar2 < 0xc) {
      sVar5 = 0;
      for (sVar7 = 0; sVar7 < 0xc; sVar7 = sVar7 + 1) {
        if ((((int)sVar2 % 3 != (int)sVar7 % 3) || (sVar7 < sVar2)) &&
           (*(char *)((int)sVar7 + (int)puVar6) == sVar8)) {
          sVar5 = sVar5 + 1;
        }
      }
      if ((1 < sVar5) && (6 < word_e9f12)) goto LAB_00064a75;
      unaff_EDX = ((int)sVar2 / 3) * 3;
      sVar7 = (short)unaff_EDX + 2;
    }
    else if (sVar2 < 0x12) {
      if (2 < (short)word_e9f14) {
        sVar5 = 0;
        for (sVar7 = 0xc; sVar7 < 0x12; sVar7 = sVar7 + 1) {
          if ((((int)sVar2 % 2 != (int)sVar7 % 2) || (sVar7 < sVar2)) &&
             (*(char *)((int)sVar7 + (int)puVar6) == sVar8)) {
            sVar5 = sVar5 + 1;
          }
        }
        if (1 < sVar5) goto LAB_00064a75;
      }
      unaff_EDX = unaff_EDX & 0xfffffffe;
      sVar7 = (short)unaff_EDX + 1;
    }
    else if (sVar2 < 0x1c) {
      if (((cVar1 == 'D') && ((short)word_e9f14 < 4)) || ((cVar1 != 'D' && (word_e9f12 < 6)))) {
        if (sVar2 < 0x17) {
          unaff_EDX = 0x12;
        }
        else {
          unaff_EDX = 0x17;
        }
        sVar7 = (short)unaff_EDX + 4;
      }
      else {
        unaff_EDX = 0x12;
        sVar7 = 0x1b;
      }
    }
    else if ((cVar1 == 'D') && ((short)word_e9f14 < 4)) {
      if (sVar2 < 0x20) {
        unaff_EDX = 0x1c;
      }
      else {
        unaff_EDX = 0x20;
      }
      sVar7 = (short)unaff_EDX + 3;
    }
    else {
      unaff_EDX = 0x1c;
      sVar7 = 0x23;
    }
    for (; sVar5 = (short)unaff_EDX, sVar5 <= sVar7; unaff_EDX = unaff_EDX + 1) {
      if (sVar5 != sVar2) {
        if (sVar2 < 0x1c) {
          if (0x11 < sVar2) {
            iVar4 = sVar2 + 5;
            goto LAB_00064c7e;
          }
        }
        else {
          iVar4 = sVar2 + 4;
LAB_00064c7e:
          if (sVar5 == iVar4) goto LAB_00064c93;
        }
        if (*(char *)((int)sVar5 + (int)puVar6) == sVar8) {
          return CONCAT22(sVar5 >> 0xf,(short)*(char *)((int)sVar5 + (int)puVar6)) ^ unaff_EBX;
        }
      }
LAB_00064c93:
    }
    uVar3 = 1;
  }
  return uVar3;
}


// ================================================================================================
// sub_64ca8 @ 0x64ca8 [__watcall]
// ================================================================================================

undefined4 __watcall sub_64ca8(int param_1,short unaff_DX,short unaff_BX)

{
  int iVar1;
  short sVar2;
  short sVar3;
  int iVar4;
  undefined4 *puVar5;
  int iVar6;
  undefined2 local_1a;
  short sStackY_14;
  
  __CHK(0x24);
  sStackY_14 = 0;
  do {
    if ((0x18 < sStackY_14) ||
       (sVar3 = (short)*(char *)(sStackY_14 + param_1), *(char *)(sStackY_14 + param_1) < '\0')) {
      return 0xffffffff;
    }
    iVar4 = (int)unaff_DX;
    iVar6 = (int)sVar3;
    iVar1 = iVar4 * 0x19 + iVar6;
    if (((&unk_e9e18)[iVar1] != '\0') &&
       (sVar2 = lineup_player_ok(iVar4,(int)unaff_BX,iVar6), sVar2 != 0)) {
      if ((&unk_e9e18)[iVar1] != '\x02') goto LAB_00064e26;
      if ((word_e9f14._2_2_ < 0x12) &&
         (((&unk_db3ae)[iVar6 * 0x27 + iVar4 * 0x444] == 'D' || (word_e9f12 < 0xc)))) {
        (&rosters)[sVar3 * 0x27 + unaff_DX * 0x444] = 3;
        if (unaff_DX == 0) {
          puVar5 = &unk_dc200;
        }
        else {
          puVar5 = (undefined4 *)&unk_dabf0;
        }
        for (sVar2 = 0x28; sVar2 < 0x30; sVar2 = sVar2 + 1) {
          if (*(char *)((int)sVar2 + (int)puVar5) == sVar3) {
            *(char *)((int)sVar2 + (int)puVar5) = 'd';
          }
        }
        (&unk_e9e18)[unaff_DX * 0x19 + (int)sVar3] = 1;
        word_e9f14._2_2_ = word_e9f14._2_2_ + 1;
        if ((&unk_db3ae)[sVar3 * 0x27 + unaff_DX * 0x444] == 'D') {
          word_e9f14._0_2_ = (short)word_e9f14 + 1;
        }
        else {
          word_e9f12 = word_e9f12 + 1;
        }
LAB_00064e26:
        return CONCAT22(local_1a,sVar3);
      }
    }
    sStackY_14 = sStackY_14 + 1;
  } while( true );
}


// ================================================================================================
// choose_lineup_player @ 0x64e60 [__watcall]
// ================================================================================================

short __watcall choose_lineup_player(short param_1,short unaff_DX)

{
  char cVar1;
  char cVar2;
  short sVar3;
  short sVar4;
  short sVar5;
  int iVar6;
  undefined *puVar7;
  undefined4 *puVar8;
  
  __CHK(0x24);
  if (param_1 == 0) {
    puVar8 = &unk_dc200;
  }
  else {
    puVar8 = (undefined4 *)&unk_dabf0;
  }
  sVar3 = (short)(char)(&unk_cd473)[unaff_DX];
  sVar5 = sVar3;
  do {
    iVar6 = (int)sVar5;
    sVar5 = sVar5 + 1;
  } while ((char)(&unk_cd421)[iVar6] != unaff_DX);
  for (; -1 < (char)(&unk_cd421)[sVar5]; sVar5 = sVar5 + 1) {
    cVar1 = *(char *)((*(int *)(&unk_cd41e + sVar5) >> 0x18) + (int)puVar8);
    sVar4 = lineup_player_ok((int)param_1,(int)unaff_DX,
                             (int)*(char *)((*(int *)(&unk_cd41e + sVar5) >> 0x18) + (int)puVar8));
    if (sVar4 != 0) {
      return (short)cVar1;
    }
  }
  cVar1 = (&unk_db3ae)[param_1 * 0x444 + *(char *)((int)unaff_DX + (int)puVar8) * 0x27];
  iVar6 = param_1 * 0x19;
  if (cVar1 == 'D') {
    if ((unaff_DX < 0x1c) && (0x11 < unaff_DX)) {
      puVar7 = &unk_e9d50 + iVar6;
    }
    else {
      puVar7 = &unk_e9db4 + param_1 * 0x19;
    }
  }
  else if (cVar1 == 'C') {
    if (unaff_DX < 0x1c) {
      puVar7 = &unk_e9cec;
    }
    else {
      puVar7 = &unk_e9d82;
    }
    sVar5 = sub_64ca8(puVar7 + iVar6);
    if (-1 < sVar5) {
      return sVar5;
    }
    if (unaff_DX < 0x1c) {
      puVar7 = &unk_e9de6;
    }
    else {
      puVar7 = &unk_e9e7c;
    }
    sVar5 = sub_64ca8(puVar7 + param_1 * 0x19,(int)param_1,(int)unaff_DX);
    if (-1 < sVar5) {
      return sVar5;
    }
    if (unaff_DX < 0x1c) {
      puVar7 = &unk_e9eae + param_1 * 0x19;
    }
    else {
      puVar7 = &unk_e9d1e + param_1 * 0x19;
    }
  }
  else if (cVar1 == 'R') {
    if (unaff_DX < 0x1c) {
      puVar7 = &unk_e9eae;
    }
    else {
      puVar7 = &unk_e9d1e;
    }
    sVar5 = sub_64ca8(puVar7 + iVar6);
    if (-1 < sVar5) {
      return sVar5;
    }
    if (unaff_DX < 0x1c) {
      puVar7 = &unk_e9de6;
    }
    else {
      puVar7 = &unk_e9e7c;
    }
    sVar5 = sub_64ca8(puVar7 + param_1 * 0x19,(int)param_1,(int)unaff_DX);
    if (-1 < sVar5) {
      return sVar5;
    }
    if (unaff_DX < 0x1c) {
      puVar7 = &unk_e9cec + param_1 * 0x19;
    }
    else {
      puVar7 = &unk_e9d82 + param_1 * 0x19;
    }
  }
  else {
    if (cVar1 != 'L') goto LAB_00065122;
    if (unaff_DX < 0x1c) {
      puVar7 = &unk_e9de6;
    }
    else {
      puVar7 = &unk_e9e7c;
    }
    sVar5 = sub_64ca8(puVar7 + iVar6);
    if (-1 < sVar5) {
      return sVar5;
    }
    if (unaff_DX < 0x1c) {
      puVar7 = &unk_e9eae;
    }
    else {
      puVar7 = &unk_e9d1e;
    }
    sVar5 = sub_64ca8(puVar7 + param_1 * 0x19,(int)param_1,(int)unaff_DX);
    if (-1 < sVar5) {
      return sVar5;
    }
    if (unaff_DX < 0x1c) {
      puVar7 = &unk_e9cec + param_1 * 0x19;
    }
    else {
      puVar7 = &unk_e9d82 + param_1 * 0x19;
    }
  }
  sVar5 = sub_64ca8(puVar7,(int)param_1,(int)unaff_DX);
  if (-1 < sVar5) {
    return sVar5;
  }
LAB_00065122:
  while ((char)(&unk_cd421)[sVar3] != unaff_DX) {
    cVar2 = *(char *)((*(int *)(&unk_cd41e + sVar3) >> 0x18) + (int)puVar8);
    sVar5 = lineup_player_ok((int)param_1,(int)unaff_DX,
                             (int)*(char *)((*(int *)(&unk_cd41e + sVar3) >> 0x18) + (int)puVar8));
    if (sVar5 != 0) {
      return (short)cVar2;
    }
    sVar3 = sVar3 + 1;
  }
  if (cVar1 == 'D') {
    if ((unaff_DX < 0x12) || (0x1b < unaff_DX)) {
      puVar7 = &unk_e9db4 + param_1 * 0x19;
    }
    else {
      puVar7 = &unk_e9d50 + param_1 * 0x19;
    }
  }
  else if (unaff_DX < 0x1c) {
    puVar7 = &unk_e9e4a + param_1 * 0x19;
  }
  else {
    puVar7 = &unk_e9ee0 + param_1 * 0x19;
  }
  sVar5 = 0;
  while ((sVar5 < 0x19 && (sVar3 = (short)(char)puVar7[sVar5], -1 < sVar3))) {
    sVar4 = lineup_player_ok((int)param_1,(int)unaff_DX,(int)sVar3);
    if (sVar4 != 0) {
      return sVar3;
    }
    sVar5 = sVar5 + 1;
  }
  if (cVar1 == 'D') {
    if ((unaff_DX < 0x12) || (0x1b < unaff_DX)) {
      puVar7 = &unk_e9ee0 + param_1 * 0x19;
    }
    else {
      puVar7 = &unk_e9e4a + param_1 * 0x19;
    }
  }
  else if (unaff_DX < 0x1c) {
    puVar7 = &unk_e9d50 + param_1 * 0x19;
  }
  else {
    puVar7 = &unk_e9db4 + param_1 * 0x19;
  }
  sVar5 = 0;
  while ((sVar5 < 0x19 && (sVar3 = (short)(char)puVar7[sVar5], -1 < sVar3))) {
    sVar4 = lineup_player_ok((int)param_1,(int)unaff_DX,(int)sVar3);
    if (sVar4 != 0) {
      return sVar3;
    }
    sVar5 = sVar5 + 1;
  }
  return 0;
}


// ================================================================================================
// sub_652d6 @ 0x652d6 [__watcall]
// ================================================================================================

void __watcall sub_652d6(short param_1,short unaff_DX,short unaff_BX)

{
  undefined4 *puVar1;
  int iVar2;
  short sVar3;
  short sVar4;
  
  __CHK(0x14);
  if (param_1 == 0) {
    puVar1 = &unk_dc200;
  }
  else {
    puVar1 = (undefined4 *)&unk_dabf0;
  }
  if (unaff_DX == 0x24) {
    *(undefined1 *)(puVar1 + 9) = *(undefined1 *)((int)puVar1 + 0x25);
  }
  sVar4 = 0x19;
  do {
    if (0x1b < sVar4) {
      *(undefined *)((int)puVar1 + 0x25) = *(undefined *)(puVar1 + 9);
      return;
    }
    if ((sVar4 != *(char *)(puVar1 + 9)) && (sVar4 != *(char *)((int)puVar1 + 0x25))) {
      iVar2 = sVar4 * 0x27 + param_1 * 0x444;
      if ((&unk_cd418)[(byte)(&rosters)[iVar2]] == '\x01') goto LAB_0006536c;
      if (((&rosters)[iVar2] == '\x02') && (unaff_BX != 0)) {
        (&rosters)[iVar2] = 3;
        for (sVar3 = 0x28; sVar3 < 0x30; sVar3 = sVar3 + 1) {
          if (*(char *)((int)sVar3 + (int)puVar1) == sVar4) {
            *(char *)((int)sVar3 + (int)puVar1) = 'd';
          }
        }
LAB_0006536c:
        *(char *)((int)puVar1 + 0x25) = (char)sVar4;
        return;
      }
    }
    sVar4 = sVar4 + 1;
  } while( true );
}


// ================================================================================================
// sub_653be @ 0x653be [__watcall]
// ================================================================================================

void __watcall sub_653be(short param_1,short unaff_DX)

{
  char cVar1;
  short sVar2;
  undefined4 *puVar3;
  
  __CHK(0x20);
  if (param_1 == 0) {
    puVar3 = &unk_dc200;
  }
  else {
    puVar3 = (undefined4 *)&unk_dabf0;
  }
  if (unaff_DX == 0x26) {
    if ((&unk_cd418)[(byte)(&rosters)[((int)puVar3[9] >> 0x18) * 0x27 + param_1 * 0x444]] == '\x01')
    {
      *(undefined1 *)((int)puVar3 + 0x26) = *(undefined1 *)((int)puVar3 + 0x27);
    }
    else {
      for (sVar2 = 0; sVar2 < 0x19; sVar2 = sVar2 + 1) {
        cVar1 = (&unk_e9e4a)[(int)sVar2 + param_1 * 0x19];
        if (cVar1 < '\0') break;
        if ((&unk_cd418)[(byte)(&rosters)[(short)cVar1 * 0x27 + param_1 * 0x444]] == '\x01') {
          *(char *)((int)puVar3 + 0x26) = cVar1;
          break;
        }
      }
    }
  }
  sVar2 = 0;
  while( true ) {
    if (0x18 < sVar2) {
      return;
    }
    cVar1 = (&unk_e9e4a)[(int)sVar2 + param_1 * 0x19];
    if (cVar1 < '\0') break;
    if (((&unk_cd418)[(byte)(&rosters)[(short)cVar1 * 0x27 + param_1 * 0x444]] == '\x01') &&
       ((short)cVar1 != (short)*(char *)((int)puVar3 + 0x26))) {
      *(char *)((int)puVar3 + 0x27) = cVar1;
      return;
    }
    sVar2 = sVar2 + 1;
  }
  return;
}


// ================================================================================================
// sub_6552e @ 0x6552e [__watcall]
// ================================================================================================

void __watcall sub_6552e(short param_1,short unaff_DX,short unaff_BX,short unaff_CX,short param_5)

{
  char cVar1;
  undefined4 *puVar2;
  
  __CHK(0x18);
  if (param_1 == 0) {
    puVar2 = &unk_dc200;
  }
  else {
    puVar2 = (undefined4 *)&unk_dabf0;
  }
  (&unk_e9e18)[param_1 * 0x19 + (int)*(char *)((int)unaff_DX + (int)puVar2)] = 0;
  for (; unaff_BX < unaff_CX; unaff_BX = unaff_BX + 1) {
    cVar1 = choose_lineup_player((int)param_1,(int)unaff_DX);
    *(char *)((int)unaff_DX + (int)puVar2) = cVar1;
    if (unaff_DX < 0x12) {
      (&unk_e9e18)[param_1 * 0x19 + (int)cVar1] = 0;
    }
    unaff_DX = unaff_DX + param_5;
  }
  return;
}


// ================================================================================================
// pick_player_for_position @ 0x655cc [__watcall]
// ================================================================================================

void __watcall pick_player_for_position(short param_1,short unaff_DX)

{
  char cVar1;
  short sVar2;
  char *pcVar3;
  short sVar4;
  short sStack_14;
  
  __CHK(0x28);
  if (param_1 == 0) {
    pcVar3 = (char *)&unk_dc200;
  }
  else {
    pcVar3 = &unk_dabf0;
  }
  if ((&unk_db3ae)[unaff_DX * 0x27 + param_1 * 0x444] == 'D') {
    word_e9f14._0_2_ = 0;
    for (sStack_14 = 0; sStack_14 < 0x19; sStack_14 = sStack_14 + 1) {
      if ((char)(&unk_e9db4)[param_1 * 0x19 + (int)sStack_14] < 0) break;
      if ((&unk_cd418)
          [(byte)(&rosters)
                 [(short)(char)(&unk_e9db4)[param_1 * 0x19 + (int)sStack_14] * 0x27 +
                  param_1 * 0x444]] == '\x01') {
        word_e9f14._0_2_ = (short)word_e9f14 + 1;
      }
    }
  }
  else if ((&unk_db3ae)[unaff_DX * 0x27 + param_1 * 0x444] != 'G') {
    word_e9f12 = 0;
    for (sStack_14 = 0; sStack_14 < 0x19; sStack_14 = sStack_14 + 1) {
      if ((char)(&unk_e9e4a)[(int)sStack_14 + param_1 * 0x19] < 0) break;
      if ((&unk_cd418)
          [(byte)(&rosters)
                 [(short)(char)(&unk_e9e4a)[(int)sStack_14 + param_1 * 0x19] * 0x27 +
                  param_1 * 0x444]] == '\x01') {
        word_e9f12 = word_e9f12 + 1;
      }
    }
  }
  sVar4 = 0;
  for (sStack_14 = 0; sStack_14 < 4; sStack_14 = sStack_14 + 1) {
    for (sVar2 = 0; sVar2 < 3; sVar2 = sVar2 + 1) {
      cVar1 = *pcVar3;
      pcVar3 = pcVar3 + 1;
      if (cVar1 == unaff_DX) {
        sub_6552e((int)param_1,(int)sVar4,(int)sStack_14,4,3);
      }
      sVar4 = sVar4 + 1;
    }
  }
  for (sStack_14 = 0; sStack_14 < 3; sStack_14 = sStack_14 + 1) {
    for (sVar2 = 0; sVar2 < 2; sVar2 = sVar2 + 1) {
      cVar1 = *pcVar3;
      pcVar3 = pcVar3 + 1;
      if (cVar1 == unaff_DX) {
        sub_6552e((int)param_1,(int)sVar4,(int)sStack_14,3,2);
      }
      sVar4 = sVar4 + 1;
    }
  }
  for (sStack_14 = 0; sStack_14 < 2; sStack_14 = sStack_14 + 1) {
    for (sVar2 = 0; sVar2 < 5; sVar2 = sVar2 + 1) {
      cVar1 = *pcVar3;
      pcVar3 = pcVar3 + 1;
      if (cVar1 == unaff_DX) {
        sub_6552e((int)param_1,(int)sVar4,(int)sStack_14,2,5);
      }
      sVar4 = sVar4 + 1;
    }
  }
  for (sStack_14 = 0; sStack_14 < 2; sStack_14 = sStack_14 + 1) {
    for (sVar2 = 0; sVar2 < 4; sVar2 = sVar2 + 1) {
      cVar1 = *pcVar3;
      pcVar3 = pcVar3 + 1;
      if (cVar1 == unaff_DX) {
        sub_6552e((int)param_1,(int)sVar4,(int)sStack_14,2,4);
      }
      sVar4 = sVar4 + 1;
    }
  }
  for (sStack_14 = 0; sStack_14 < 2; sStack_14 = sStack_14 + 1) {
    cVar1 = *pcVar3;
    pcVar3 = pcVar3 + 1;
    if (cVar1 == unaff_DX) {
      sub_652d6((int)param_1,(int)sVar4,0);
    }
    sVar4 = sVar4 + 1;
  }
  for (sStack_14 = 0; sStack_14 < 2; sStack_14 = sStack_14 + 1) {
    cVar1 = *pcVar3;
    pcVar3 = pcVar3 + 1;
    if (cVar1 == unaff_DX) {
      sub_653be((int)param_1,(int)sVar4);
    }
    sVar4 = sVar4 + 1;
  }
  return;
}


// ================================================================================================
// count_dressed_players @ 0x658f3 [__watcall]
// ================================================================================================

void __watcall count_dressed_players(short param_1)

{
  short sVar1;
  undefined4 *puVar2;
  
  __CHK(0x1c);
  if (param_1 == 0) {
    puVar2 = &unk_dc200;
  }
  else {
    puVar2 = (undefined4 *)&unk_dabf0;
  }
  word_e9f14._0_2_ = 0;
  for (sVar1 = 0; sVar1 < 0x19; sVar1 = sVar1 + 1) {
    if ((char)(&unk_e9db4)[(int)sVar1 + param_1 * 0x19] < 0) break;
    if ((&unk_cd418)
        [(byte)(&rosters)
               [(short)(char)(&unk_e9db4)[(int)sVar1 + param_1 * 0x19] * 0x27 + param_1 * 0x444]] ==
        '\x01') {
      word_e9f14._0_2_ = (short)word_e9f14 + 1;
    }
  }
  word_e9f12 = 0;
  for (sVar1 = 0; sVar1 < 0x19; sVar1 = sVar1 + 1) {
    if ((char)(&unk_e9e4a)[param_1 * 0x19 + (int)sVar1] < 0) break;
    if ((&unk_cd418)
        [(byte)(&rosters)
               [(short)(char)(&unk_e9e4a)[param_1 * 0x19 + (int)sVar1] * 0x27 + param_1 * 0x444]] ==
        '\x01') {
      word_e9f12 = word_e9f12 + 1;
    }
  }
  word_e9f14._2_2_ = word_e9f12 + (short)word_e9f14;
  for (sVar1 = 0; sVar1 < 0x19; sVar1 = sVar1 + 1) {
    (&unk_e9c24)[sVar1] = 0;
  }
  for (sVar1 = 0; sVar1 < 0x24; sVar1 = sVar1 + 1) {
    (&unk_e9c24)[*(char *)((int)sVar1 + (int)puVar2)] = 1;
  }
  (&unk_e9c24)[(int)puVar2[9] >> 0x18] = 1;
  (&unk_e9c24)[*(int *)((int)puVar2 + 0x23) >> 0x18] = 1;
  for (sVar1 = 0; sVar1 < 0x19; sVar1 = sVar1 + 1) {
    if (((&unk_e9c24)[sVar1] != 0) &&
       (((&rosters)[sVar1 * 0x27 + param_1 * 0x444] == '\0' ||
        ((&rosters)[sVar1 * 0x27 + param_1 * 0x444] == '\x01')))) {
      pick_player_for_position((int)param_1,(int)sVar1);
    }
  }
  for (sVar1 = 0x24; sVar1 < 0x25; sVar1 = sVar1 + 1) {
    if (((&rosters)[param_1 * 0x444 + *(char *)((int)sVar1 + (int)puVar2) * 0x27] == '\0') ||
       ((&rosters)[param_1 * 0x444 + *(char *)((int)sVar1 + (int)puVar2) * 0x27] == '\x01')) {
      sub_652d6((int)param_1,(int)sVar1,1);
    }
  }
  for (sVar1 = 0; sVar1 < 0x19; sVar1 = sVar1 + 1) {
    (&unk_e9e18)[(int)sVar1 + param_1 * 0x19] = (&unk_e9e18)[param_1 * 0x19 + (int)sVar1] == '\x01';
  }
  return;
}


// ================================================================================================
// sub_65b48 @ 0x65b48 [__watcall]
// ================================================================================================

void __watcall sub_65b48(void)

{
  int iVar1;
  
  __CHK(0xc);
  iVar1 = 0;
  do {
    (&unk_e9e18)[iVar1] = (&unk_e9e18)[iVar1] == '\x01';
    (&unk_e9e31)[iVar1] = (&unk_e9e31)[iVar1] == '\x01';
    iVar1 = iVar1 + 1;
  } while (iVar1 < 0x19);
  return;
}


// ================================================================================================
// injury_check @ 0x65b83 [__watcall]
// ================================================================================================

undefined8 __watcall injury_check(int param_1,undefined4 unaff_EDX)

{
  char cVar1;
  short sVar2;
  short sVar3;
  int iVar4;
  ushort uVar5;
  bool bVar6;
  bool bVar7;
  
  __CHK(0x24);
  bVar7 = false;
  bVar6 = (*(byte *)(param_1 + 0x44) & 0x40) != 0;
  sVar2 = 0;
  for (sVar3 = 0; sVar3 < 0x19; sVar3 = sVar3 + 1) {
    uVar5 = (ushort)bVar6;
    cVar1 = (&unk_e9db4)[(int)sVar3 + (short)uVar5 * 0x19];
    if (cVar1 < '\0') break;
    if ((short)cVar1 == (short)*(char *)(param_1 + 0x47)) {
      bVar7 = true;
    }
    if (((&rosters)[(short)cVar1 * 0x27 + (short)uVar5 * 0x444] == '\x04') ||
       ((&rosters)[(short)cVar1 * 0x27 + (short)uVar5 * 0x444] == '\x03')) {
      sVar2 = sVar2 + 1;
    }
  }
  if (bVar7) {
    bVar6 = SBORROW2(sVar2,2);
    sVar3 = sVar2 + -2;
    bVar7 = sVar2 == 2;
  }
  else {
    sVar2 = 0;
    for (sVar3 = 0; sVar3 < 0x19; sVar3 = sVar3 + 1) {
      iVar4 = (int)(short)(ushort)bVar6;
      if ((char)(&unk_e9e4a)[iVar4 * 0x19 + (int)sVar3] < '\0') break;
      if (((&rosters)[iVar4 * 0x444 + (short)(char)(&unk_e9e4a)[iVar4 * 0x19 + (int)sVar3] * 0x27]
           == '\x04') ||
         ((&rosters)[iVar4 * 0x444 + (short)(char)(&unk_e9e4a)[iVar4 * 0x19 + (int)sVar3] * 0x27] ==
          '\x03')) {
        sVar2 = sVar2 + 1;
      }
    }
    bVar6 = SBORROW2(sVar2,4);
    sVar3 = sVar2 + -4;
    bVar7 = sVar2 == 4;
  }
  return CONCAT44(unaff_EDX,(uint)(!bVar7 && bVar6 == sVar3 < 0));
}


// ================================================================================================
// sub_65ca8 @ 0x65ca8 [__watcall]
// ================================================================================================

void __watcall sub_65ca8(int param_1,int unaff_EDX,int unaff_EBX,int unaff_ECX,undefined4 param_5)

{
  int iVar1;
  int iVar2;
  
  __CHK(0x28);
  for (iVar2 = unaff_EDX + 1; iVar1 = param_1, iVar2 < unaff_EDX + unaff_ECX; iVar2 = iVar2 + 2) {
    for (; iVar1 < unaff_EBX + param_1; iVar1 = iVar1 + 2) {
      sub_b5d80(iVar1,iVar2,param_5);
    }
  }
  return;
}


// ================================================================================================
// update_camera @ 0x65d01 [__watcall]
// ================================================================================================

/* WARNING: Removing unreachable block (ram,0x00065ebf) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall update_camera(void)

{
  bool bVar1;
  short sVar2;
  undefined2 uVar3;
  int iVar4;
  undefined4 *puVar5;
  short sVar6;
  short sVar7;
  short sVar8;
  short sVar9;
  int iVar10;
  
  __CHK(0x20);
  sVar6 = 0x28;
  sVar7 = 10;
  bVar1 = false;
  dword_e03ac = (short)camera_target_y;
  dword_e03ae._2_2_ = _camera_target_x;
  if ((game_flags & 0x80) != 0) {
    dword_e03ae._2_2_ = -100;
    dword_e03ac = 0xf;
    sVar7 = 0xf - camera._2_2_;
    if (sVar7 < -5) {
      dword_e03be = CONCAT22(0x14,(undefined2)dword_e03be);
    }
    else if (5 < sVar7) {
      dword_e03be = CONCAT22(10,(undefined2)dword_e03be);
    }
    if (sVar7 < 0) {
      iVar4 = -(int)sVar7;
    }
    else {
      iVar4 = (int)sVar7;
    }
    if (5 < iVar4) {
      sVar7 = dword_e03be._2_2_ - camera._2_2_;
      iVar4 = (int)sVar7;
      if (sVar7 < 0) {
        iVar4 = -iVar4;
      }
      if (0x20 < iVar4) {
        if (sVar7 < 0) {
          sVar7 = -0x20;
        }
        else {
          sVar7 = 0x20;
        }
      }
      dword_e03be = CONCAT22(sVar7,(undefined2)dword_e03be);
      if (sVar7 != 0) {
        dword_e03be = CONCAT22(sVar7 >> 5,(undefined2)dword_e03be);
        if (sVar7 >> 5 == 0) {
          dword_e03be = CONCAT22(1,(undefined2)dword_e03be);
        }
        camera._2_2_ = camera._2_2_ + dword_e03be._2_2_;
      }
    }
    sVar7 = -100 - (short)camera;
    dword_e03ba = CONCAT22(sVar7,(undefined2)dword_e03ba);
    if (sVar7 < -0x28) {
      dword_e03be._2_2_ = -0x20;
    }
    else {
      if (sVar7 < 0x29) {
        _camera_target_x = 0xff9c;
        camera_target_y._0_2_ = 0xf;
        dword_e03ac = 0xf;
        dword_e03ae._2_2_ = 0xff9c;
        return;
      }
      dword_e03be._2_2_ = -0x8c;
    }
    sVar7 = dword_e03be._2_2_ - (short)camera;
    iVar4 = (int)sVar7;
    if (sVar7 < 0) {
      iVar4 = -iVar4;
    }
    if (0x20 < iVar4) {
      if (sVar7 < 0) {
        sVar7 = -0x20;
      }
      else {
        sVar7 = 0x20;
      }
    }
    dword_e03be = CONCAT22(sVar7,(undefined2)dword_e03be);
    if (sVar7 == 0) {
      _camera_target_x = 0xff9c;
      camera_target_y._0_2_ = 0xf;
      dword_e03ac = 0xf;
      dword_e03ae._2_2_ = 0xff9c;
      return;
    }
    dword_e03be._2_2_ = sVar7 >> 5;
    if (dword_e03be._2_2_ == 0) {
      dword_e03be._2_2_ = 1;
    }
    goto LAB_00066480;
  }
  if ((clock_seconds != 0) || (clock_sub != 0)) {
    if ((((game_flags & 4) == 0) || (-1 < stoppage_timer)) && (ref_phase < 1)) {
      if ((action_flags & 0x40) == 0) {
        bVar1 = false;
        if (*p_puck_carrier < '\0') {
          puVar5 = &puck;
        }
        else {
          iVar4 = (int)*p_puck_carrier;
          puVar5 = &entities + iVar4 * 0x20;
          dword_e03ba = CONCAT22(2,(undefined2)dword_e03ba);
          if (*(short *)((int)&DAT_000df884 + iVar4 * 0x80 + 2) == 0x10) {
            camera_target_y._2_2_ =
                 -(short)(char)((uint)*(undefined4 *)(&DAT_000df828 + iVar4 * 0x40) >> 0x18);
          }
          else if (((&unk_df860)[iVar4 * 0x80] & 0x80) == 0) {
            camera_target_y._2_2_ = camera_target_y._2_2_ + -2;
            bVar1 = 100 < (short)(&DAT_000df82a)[iVar4 * 0x40];
            if (camera_target_y._2_2_ < -0x31) {
              camera_target_y._2_2_ = -0x32;
            }
          }
          else {
            bVar1 = *(int *)(&DAT_000df828 + iVar4 * 0x40) >> 0x10 < -100;
            camera_target_y._2_2_ = camera_target_y._2_2_ + 2;
            if (0x31 < camera_target_y._2_2_) {
              camera_target_y._2_2_ = 0x32;
            }
          }
        }
        dword_e03ac = camera_target_y._2_2_ +
                      (short)((uint)puVar5[1] >> 0x10) + (short)(char)((uint)puVar5[3] >> 0x18);
        dword_e03ae._2_2_ = *(short *)((int)puVar5 + 2);
      }
    }
    else {
      _camera_target_x = referee._2_2_;
      camera_target_y._0_2_ = DAT_000e0020._2_2_;
      sVar8 = referee._2_2_ - (short)camera;
      ram0x000e03aa = CONCAT22(sVar8,dword_e03a8._2_2_);
      sVar9 = word_e0046 - (short)camera;
      dword_e03ae = CONCAT22(sVar9,(undefined2)dword_e03ae);
      iVar4 = (int)sVar8;
      sVar2 = (short)camera;
      if ((int)(dword_e03ae ^ ram0x000e03aa) >> 0x10 < 0) {
LAB_00066022:
        _camera_target_x = sVar2;
      }
      else {
        if (sVar8 < 0) {
          iVar4 = -iVar4;
        }
        iVar10 = (int)sVar9;
        if (sVar9 < 0) {
          iVar10 = -iVar10;
        }
        sVar2 = word_e0046;
        if (iVar10 < iVar4) goto LAB_00066022;
      }
      sVar8 = DAT_000e0020._2_2_ - camera._2_2_;
      ram0x000e03aa = CONCAT22(sVar8,dword_e03a8._2_2_);
      sVar9 = word_e0048 - camera._2_2_;
      dword_e03ae = CONCAT22(sVar9,(undefined2)dword_e03ae);
      iVar4 = (int)sVar8;
      sVar2 = camera._2_2_;
      if ((int)(dword_e03ae ^ ram0x000e03aa) >> 0x10 < 0) {
LAB_0006606c:
        camera_target_y._0_2_ = sVar2;
      }
      else {
        if (sVar8 < 0) {
          iVar4 = -iVar4;
        }
        iVar10 = (int)sVar9;
        if (sVar9 < 0) {
          iVar10 = -iVar10;
        }
        sVar2 = word_e0048;
        if (iVar10 < iVar4) goto LAB_0006606c;
      }
      dword_e03ae._2_2_ = _camera_target_x;
      iVar10 = (referee >> 0x10) - (int)(short)faceoff_spot;
      iVar4 = (DAT_000e0020 >> 0x10) - (int)faceoff_spot._2_2_;
      dword_e03ac = (short)camera_target_y;
      if ((((&unk_e003a)[dword_e0036 >> 0x10] == '\"') || ((&unk_e003a)[dword_e0036 >> 0x10] == ',')
          ) && (iVar4 * iVar4 + iVar10 * iVar10 < 0x640)) {
        dword_e03ac = faceoff_spot._2_2_;
        dword_e03ae._2_2_ = (short)faceoff_spot;
        sVar7 = 0;
        sVar6 = 0;
      }
    }
  }
  sVar2 = dword_e03ac - camera._2_2_;
  iVar4 = (int)sVar2;
  if (SBORROW4(iVar4,-(int)sVar7) == iVar4 + sVar7 < 0) {
    if (sVar7 < sVar2) {
      sVar8 = dword_e03ac;
      if (!bVar1) {
        sVar8 = dword_e03ac - sVar7;
      }
      dword_e03be = CONCAT22(sVar8,(undefined2)dword_e03be);
      if (0xec < sVar8) {
        dword_e03be = CONCAT22(0xec,(undefined2)dword_e03be);
      }
    }
  }
  else {
    dword_e03be = CONCAT22(dword_e03ac + sVar7,(undefined2)dword_e03be);
    if ((short)(dword_e03ac + sVar7) < -0xbc) {
      dword_e03be = CONCAT22(0xff44,(undefined2)dword_e03be);
    }
  }
  if (sVar2 < 0) {
    iVar4 = -iVar4;
  }
  else {
    iVar4 = (int)sVar2;
  }
  if (sVar7 < iVar4) {
    sVar7 = dword_e03be._2_2_ - camera._2_2_;
    dword_e03be = CONCAT22(sVar7,(undefined2)dword_e03be);
    if ((game_flags & 1) != 0) {
      iVar4 = (int)sVar7;
      if (sVar7 < 0) {
        iVar4 = -iVar4;
      }
      if (0x20 < iVar4) {
        if (sVar7 < 0) {
          uVar3 = 0xffe0;
        }
        else {
          uVar3 = 0x20;
        }
        dword_e03be = CONCAT22(uVar3,(undefined2)dword_e03be);
      }
    }
    if (dword_e03be._2_2_ != 0) {
      sVar7 = dword_e03be._2_2_ >> !bVar1 + 3;
      dword_e03be = CONCAT22(sVar7,(undefined2)dword_e03be);
      if (sVar7 == 0) {
        dword_e03be = CONCAT22(1,(undefined2)dword_e03be);
      }
      camera._2_2_ = camera._2_2_ + dword_e03be._2_2_;
    }
  }
  sVar7 = dword_e03ae._2_2_ - (short)camera;
  dword_e03ba = CONCAT22(sVar7,(undefined2)dword_e03ba);
  if (SBORROW4((int)sVar7,-(int)sVar6) == (int)sVar7 + (int)sVar6 < 0) {
    if (sVar7 <= sVar6) {
      _camera_target_x = dword_e03ae._2_2_;
      camera_target_y._0_2_ = dword_e03ac;
      return;
    }
    dword_e03be._2_2_ = dword_e03ae._2_2_ - sVar6;
    if (0x20 < dword_e03be._2_2_) {
      dword_e03be._2_2_ = 0x20;
    }
  }
  else {
    dword_e03be._2_2_ = sVar6 + dword_e03ae._2_2_;
    if (dword_e03be._2_2_ < -0x20) {
      dword_e03be._2_2_ = -0x20;
    }
  }
  sVar7 = dword_e03be._2_2_ - (short)camera;
  iVar4 = (int)sVar7;
  if (sVar7 < 0) {
    iVar4 = -iVar4;
  }
  if (0x20 < iVar4) {
    if (sVar7 < 0) {
      sVar7 = -0x20;
    }
    else {
      sVar7 = 0x20;
    }
  }
  dword_e03be = CONCAT22(sVar7,(undefined2)dword_e03be);
  if (sVar7 == 0) {
    _camera_target_x = dword_e03ae._2_2_;
    camera_target_y._0_2_ = dword_e03ac;
    return;
  }
  dword_e03be._2_2_ = sVar7 >> 4;
  if (dword_e03be._2_2_ == 0) {
    dword_e03be._2_2_ = 1;
  }
LAB_00066480:
  camera._0_2_ = (short)camera + dword_e03be._2_2_;
  _camera_target_x = dword_e03ae._2_2_;
  camera_target_y._0_2_ = dword_e03ac;
  dword_e03ac = dword_e03ac;
  dword_e03ae._2_2_ = dword_e03ae._2_2_;
  return;
}


// ================================================================================================
// load_cutscene_clip @ 0x66497 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall load_cutscene_clip(short param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined *puVar3;
  int iVar4;
  char acStack_28 [16];
  
  __CHK(0x38);
  iVar4 = param_1 * 4;
  iVar1 = sub_8dab8();
  if (*(int *)(&unk_cd4b0 + iVar4) <= iVar1) {
    dword_e9a9e = CONCAT22(input_enabled,(undefined2)dword_e9a9e);
    _input_enabled = 0;
    puVar3 = install_path;
    if ((&file_on_disk)[*(int *)(&unk_cc080 + iVar4)] != '\x01') {
      puVar3 = (undefined *)0x0;
    }
    make_path(acStack_28,puVar3,(&off_cbed0)[param_1],&aPPV);
    dword_e0244 = loadfile(acStack_28,0x20);
    for (iVar1 = 0; iVar4 = shapecount(dword_e0244), iVar1 < iVar4; iVar1 = iVar1 + 1) {
      sprintf(acStack_28,(char *)&a04d_c1db6,iVar1);
      uVar2 = locateshape(dword_e0244,acStack_28);
      (&unk_def8c)[iVar1] = uVar2;
    }
    _input_enabled = dword_e9a9e >> 0x10;
    dword_e0248 = (&off_cc01d)[param_1];
    dword_e9ab2._0_2_ = *(undefined2 *)(&unk_cc054 + param_1 * 4);
    dword_e9ab2._2_2_ = 1;
    word_cbece = (short)*(char *)(dword_e0248 + 1);
    dword_cbeca._2_2_ = param_1;
  }
  return;
}


// ================================================================================================
// draw_penalty_box_overlay @ 0x665ad [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall draw_penalty_box_overlay(void)

{
  short sVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  short sVar7;
  short sVar8;
  short unaff_DI;
  int iVar9;
  undefined4 uVar10;
  short sStack_3c;
  undefined4 local_3a;
  short local_30;
  short sStack_2c;
  short sStack_28;
  undefined4 uStack_22;
  short sStack_1c;
  
  __CHK(0x60);
  if (dword_cbebe._2_2_ < 0x10) {
    unaff_DI = dword_cbebe._2_2_ + -0x10;
  }
  else if (dword_cbebe._2_2_ < 0x101) {
    unaff_DI = 0;
  }
  else if (599 < dword_cbebe._2_2_) {
    unaff_DI = 600 - dword_cbebe._2_2_;
  }
  _word_cbec8 = 0xffff;
  dword_cbeca._0_2_ = 0;
  if (unaff_DI < 0) {
    iVar9 = (unaff_DI + 0x10) * 0x42;
    iVar4 = iVar9 >> 0x1f;
    local_30 = (short)((int)((iVar9 + iVar4 * -0x10) - (uint)(iVar4 << 3 < 0)) >> 4);
    iVar9 = (unaff_DI + 0x10) * 0x2a;
    iVar4 = iVar9 >> 0x1f;
    uStack_22 = CONCAT22((short)dword_d30ac,(undefined2)uStack_22);
    sStack_3c = dword_d30b4;
    sStack_28 = (short)dword_d30b0;
    local_3a = CONCAT22((undefined2)dword_d30b8,(undefined2)local_3a);
    sVar7 = ((short)dword_dd6ac + 0x4a) - local_30;
    if (period_idx == 4) {
      sVar7 = sVar7 + 0xac;
    }
    sVar8 = (short)((int)((iVar9 + iVar4 * -0x10) - (uint)(iVar4 << 3 < 0)) >> 4);
    sVar1 = (_dword_dd6aa + 0x32) - sVar8;
    setclip((int)(short)(sVar7 + ((short)dword_d30ac - (short)dword_dd6ac)),
            (int)(short)(local_30 * 2 + sVar7 + ((short)dword_d30ac - (short)dword_dd6ac)),
            (int)(short)(sVar1 + ((short)dword_d30b0 - _dword_dd6aa)),
            (int)(short)(sVar1 + sVar8 * 2 + ((short)dword_d30b0 - _dword_dd6aa)));
  }
  sVar7 = (short)dword_dd6ac + 0xc;
  if (period_idx == 4) {
    sVar7 = (short)dword_dd6ac + 0xb8;
  }
  sVar8 = sVar7 + ((short)dword_d30ac - (short)dword_dd6ac);
  sStack_2c = _dword_dd6aa + 0xc + ((short)dword_d30b0 - _dword_dd6aa);
  iVar4 = (int)(short)(_dword_dd6aa + 0x57 + ((short)dword_d30b0 - _dword_dd6aa));
  iVar9 = (int)(short)(sVar7 + 0x7b + ((short)dword_d30ac - (short)dword_dd6ac));
  if (((unaff_DI < 0) || (dword_cbeca._2_2_ == -1)) || (word_cbece == -1)) {
    iVar6 = (int)sStack_2c;
    iVar5 = (int)sVar8;
    iVar2 = iVar9 - iVar5;
    sub_90ec0(iVar5,iVar6,iVar2,iVar4 - iVar6,0x10);
    sub_65ca8(iVar5,iVar6,iVar2,iVar4 - iVar6,9);
  }
  if ((unaff_DI == 0) || (0x3d < local_30)) {
    iVar2 = sVar8 + -4;
    fillrect(iVar2,sStack_2c + -4,0x83,4,0);
    fillrect(iVar2,(int)sStack_2c,4,0x4b,0);
    fillrect(iVar9,(int)sStack_2c,4,0x4b,0);
    fillrect(iVar2,iVar4,0x83,4,0);
  }
  if (unaff_DI < 0) {
    setclip(uStack_22 >> 0x10,(int)sStack_3c,(int)sStack_28,local_3a >> 0x10);
  }
  else if ((dword_cbeca._2_2_ == -1) || (word_cbece == -1)) {
    if (byte_e0344 == '\0') {
      if (byte_e0308 == '\0') {
        sStack_1c = 0x12;
        sStack_2c = sStack_2c + 0xf;
      }
      else {
        sStack_1c = 0xf;
        sStack_2c = sStack_2c + 0xb;
      }
    }
    else {
      sStack_1c = 0xd;
      sStack_2c = sStack_2c + 8;
    }
    sVar8 = sVar8 + 0x3e;
    setfont(font_scor3b);
    settextpos(0x25,0xff);
    if (byte_e02c8 != '\0') {
      iVar9 = textwidth(&byte_e02c8,(int)sStack_2c);
      printstr_at(&byte_e02c8,(int)sVar8 - iVar9 / 2);
    }
    sVar7 = sStack_2c;
    if (byte_e0250 != '\0') {
      sVar7 = sStack_2c + sStack_1c;
      iVar9 = textwidth(&byte_e0250,(int)sVar7);
      printstr_at(&byte_e0250,(int)sVar8 - iVar9 / 2);
    }
    if (byte_e028c != '\0') {
      sVar7 = sVar7 + sStack_1c;
      iVar9 = textwidth(&byte_e028c,(int)sVar7);
      printstr_at(&byte_e028c,(int)sVar8 - iVar9 / 2);
    }
    if (byte_e0308 != '\0') {
      sVar7 = sVar7 + sStack_1c;
      iVar9 = textwidth(&byte_e0308,(int)sVar7);
      printstr_at(&byte_e0308,(int)sVar8 - iVar9 / 2);
    }
    if (byte_e0344 != '\0') {
      iVar9 = textwidth(&byte_e0344,(int)(short)(sVar7 + sStack_1c));
      printstr_at(&byte_e0344,(int)sVar8 - iVar9 / 2);
    }
    setfont(font_scor2b);
    settextpos(0x27,0xff);
    if (byte_e02c8 != '\0') {
      iVar9 = textwidth(&byte_e02c8,(int)sStack_2c);
      printstr_at(&byte_e02c8,(int)sVar8 - iVar9 / 2);
    }
    if (byte_e0250 != '\0') {
      sStack_2c = sStack_2c + sStack_1c;
      iVar9 = textwidth(&byte_e0250,(int)sStack_2c);
      printstr_at(&byte_e0250,(int)sVar8 - iVar9 / 2);
    }
    if (byte_e028c != '\0') {
      sStack_2c = sStack_2c + sStack_1c;
      iVar9 = textwidth(&byte_e028c,(int)sStack_2c);
      printstr_at(&byte_e028c,(int)sVar8 - iVar9 / 2);
    }
    if (byte_e0308 != '\0') {
      sStack_2c = sStack_2c + sStack_1c;
      iVar9 = textwidth(&byte_e0308,(int)sStack_2c);
      printstr_at(&byte_e0308,(int)sVar8 - iVar9 / 2);
    }
    if (byte_e0344 != '\0') {
      iVar9 = textwidth(&byte_e0344,(int)(short)(sStack_2c + sStack_1c));
      printstr_at(&byte_e0344,(int)sVar8 - iVar9 / 2);
    }
  }
  else {
    if ((dword_cbeca._2_2_ == 10) && (0x10 < word_cbece)) {
      sub_b500c(dword_df004,(int)sVar8,(int)sStack_2c);
      iVar9 = sStack_2c + 0x1f;
      iVar2 = sVar8 + 0x11;
      uVar10 = (&unk_def8c)[word_cbece];
    }
    else if ((dword_cbeca._2_2_ == 8) && ((0x11 < word_cbece && (word_cbece < 0x15)))) {
      iVar2 = (int)sVar8;
      sub_b500c(dword_defe0,iVar2,(int)sStack_2c);
      iVar9 = sStack_2c + 0x3c;
      uVar10 = (&unk_def8c)[word_cbece];
    }
    else {
      iVar9 = (int)sStack_2c;
      iVar2 = (int)sVar8;
      uVar10 = (&unk_def8c)[word_cbece];
    }
    sub_b500c(uVar10,iVar2,iVar9);
    if ((dword_cbeca._2_2_ == 0) && (word_cbece == 2)) {
      sStack_2c = sStack_2c + 0x23;
      if (0x2ee < crowd_noise._2_2_) {
        uVar3 = (crowd_noise >> 0x10) - 0x2ee;
        if (199 < (int)uVar3) {
          uVar3 = 200;
        }
        sub_65ca8((int)sVar8,(int)sStack_2c,
                  (int)(short)((int)((uint)(ushort)((short)uVar3 >> 0xf) << 0x10 | uVar3 & 0xffff) /
                              5),iVar4 - sStack_2c,0x30);
      }
      if (0x3b6 < crowd_noise._2_2_) {
        sVar8 = sVar8 + 0x28;
        uVar3 = (crowd_noise >> 0x10) - 0x3b6;
        if (199 < (int)uVar3) {
          uVar3 = 200;
        }
        sub_65ca8((int)sVar8,(int)sStack_2c,
                  (int)(short)((int)((uint)(ushort)((short)uVar3 >> 0xf) << 0x10 | uVar3 & 0xffff) /
                              5),iVar4 - sStack_2c,0x27);
      }
      if (0x47e < crowd_noise._2_2_) {
        uVar3 = (crowd_noise >> 0x10) - 0x47e;
        if (0xd6 < (int)uVar3) {
          uVar3 = 0xd7;
        }
        sub_65ca8((int)(short)(sVar8 + 0x28),(int)sStack_2c,
                  (int)(short)((int)((uint)(ushort)((short)uVar3 >> 0xf) << 0x10 | uVar3 & 0xffff) /
                              5),iVar4 - sStack_2c,0x60);
      }
    }
  }
  dword_d8c40 = dword_d8c40 + 1;
  sub_6ab7c();
  return;
}


// ================================================================================================
// sub_66dda @ 0x66dda [__watcall]
// ================================================================================================

void __watcall sub_66dda(void)

{
  __CHK(8);
  if (dword_cbebe._2_2_ == 0x100) {
    dword_cbebe._2_2_ = 0x10;
    return;
  }
  dword_cbebe._2_2_ = 0;
  return;
}


// ================================================================================================
// update_announcer @ 0x66e06 [__watcall]
// ================================================================================================

void __watcall update_announcer(void)

{
  short sVar1;
  
  __CHK(0x1c);
  if ((-1 < dword_cbebe._2_2_) &&
     (((stoppage_timer < 0x100 || (0x140 < stoppage_timer)) || ((game_flags & 0x40) != 0)))) {
    if (((dword_cbeca._2_2_ == 0) && (word_cbece < 5)) && (crowd_noise._2_2_ < 0x5dc)) {
      if ((dword_e9ab2._2_2_ == 1) && (crowd_noise._2_2_ < 0x280)) {
        crowd_noise._2_2_ = 0x280;
      }
      if (((0 < dword_e9ab2._2_2_) && (dword_e9ab2._2_2_ < 5)) ||
         (((7 < dword_e9ab2._2_2_ && (dword_e9ab2._2_2_ < 0xd)) || (0x10 < dword_e9ab2._2_2_)))) {
        crowd_noise._2_2_ = crowd_noise._2_2_ + 8;
      }
    }
    if (((dword_cbebe._2_2_ == 0x10) && (dword_cbeca >> 0x10 != -1)) && (dword_e0248 != (char *)0x0)
       ) {
      sVar1 = (short)dword_e9ab2 + -1;
      dword_e9ab2 = CONCAT22(dword_e9ab2._2_2_,sVar1);
      if (sVar1 < 0) {
        if (*dword_e0248 == dword_e9ab2._2_2_) {
          freemem(dword_e0244);
          if ((&unk_cc049)[dword_cbeca >> 0x10] != '\0') {
            dword_cbebe._2_2_ = 600;
          }
          word_cbece = -1;
          dword_cbeca = CONCAT22(0xffff,(undefined2)dword_cbeca);
          dword_e0248 = (char *)0x0;
        }
        else {
          word_cbece = (short)dword_e0248[(short)(dword_e9ab2._2_2_ + 1)];
          dword_e9ab2 = CONCAT22(dword_e9ab2._2_2_ + 1,
                                 *(undefined2 *)(&unk_cc054 + (dword_cbeca >> 0x10) * 4));
        }
      }
    }
    else {
      if ((dword_cbebe._2_2_ < 0x100) || (599 < dword_cbebe._2_2_)) {
        dword_cbebe._2_2_ = dword_cbebe._2_2_ + 1;
      }
      if (0x268 < dword_cbebe._2_2_) {
        dword_cbebe._2_2_ = -1;
        byte_e0344 = 0;
        byte_e0308 = 0;
        byte_e028c = 0;
        byte_e0250 = 0;
        byte_e02c8 = 0;
      }
    }
  }
  return;
}


// ================================================================================================
// draw_message_box @ 0x66fe2 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall draw_message_box(short param_1)

{
  short sVar1;
  short sVar2;
  short sVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  short sVar9;
  short sVar10;
  int iVar11;
  
  __CHK(0x54);
  sVar9 = (short)dword_dd6ac + 0xc;
  sVar1 = _dword_dd6aa + 0x95;
  sVar2 = _dword_dd6aa + 0x9e;
  setfont(font_scor3b);
  sVar3 = textwidth((&message_strings)[param_1]);
  sVar10 = sVar9 + ((short)dword_d30ac - (short)dword_dd6ac);
  sVar1 = sVar1 + ((short)dword_d30b0 - _dword_dd6aa);
  iVar7 = (int)(short)(sVar2 + ((short)dword_d30b0 - _dword_dd6aa));
  iVar11 = (int)sVar1;
  iVar8 = iVar7 - iVar11;
  iVar4 = (int)(short)(sVar3 + 4 + sVar9 + ((short)dword_d30ac - (short)dword_dd6ac));
  iVar5 = (int)sVar10;
  iVar6 = iVar4 - iVar5;
  fillrect(iVar5,iVar11,iVar6,iVar8,0x10,iVar7);
  sub_65ca8(iVar5,iVar11,iVar6,iVar8,9);
  iVar5 = iVar5 + -4;
  fillrect(iVar5,iVar11 + -4,(int)(short)(sVar3 + 0xc),4,0);
  fillrect(iVar5,iVar11,4,9,0);
  fillrect(iVar4,iVar11,4,9,0);
  fillrect(iVar5,iVar7,(int)(short)(sVar3 + 0xc),4,0);
  settextpos(0x25,0xff);
  iVar6 = (int)(short)(sVar1 + 1);
  iVar4 = (int)(short)(sVar10 + 2);
  printstr_at((&message_strings)[param_1],iVar4,iVar6,iVar4);
  setfont(font_scor2b);
  settextpos(0x27,0xff);
  printstr_at((&message_strings)[param_1],iVar4,iVar6);
  dword_d8c40 = dword_d8c40 + 1;
  sub_6ab7c();
  return;
}


// ================================================================================================
// sub_671e8 @ 0x671e8 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall sub_671e8(short param_1)

{
  ushort uVar1;
  int iVar2;
  undefined *puVar3;
  
  __CHK(0x14);
  uVar1 = (&word_df64c)[param_1 * 0x80];
  if ((_period_num != -1) &&
     (((iVar2 = param_1 + 1, user1_team == iVar2 || ((short)user2_team == iVar2)) &&
      (((int)(short)uVar1 & 0xfff0U) != 0xff00)))) {
    if (((short)_word_cbec8 < (short)(ushort)(-1 < (short)uVar1)) || ((short)_word_cbec8 < 2)) {
      dword_cbeca._0_2_ = 0x50;
      _word_cbec8 = (ushort)(-1 < (short)uVar1);
    }
    if ((short)uVar1 < 0) {
      iVar2 = (int)param_1;
      *(&off_cd4a0)[iVar2 * 3] = 2;
      uVar1 = (&word_df64c)[iVar2 * 0x80];
      (&word_df64c)[iVar2 * 0x80] = uVar1 & 0xf;
      puVar3 = (&off_cd498)[iVar2 * 3 + (int)(short)(uVar1 & 0xf)];
    }
    else {
      iVar2 = (int)param_1;
      *(&off_cd498)[iVar2 * 3 + (int)(short)(uVar1 & 0xf)] = 2;
      (&word_df64c)[iVar2 * 0x80] = (&word_df64c)[iVar2 * 0x80] | 0xfff0;
      puVar3 = (&off_cd4a0)[iVar2 * 3];
    }
    *puVar3 = 1;
    apply_line_change(param_1 * 0x100 + 0xdf614);
  }
  return;
}


// ================================================================================================
// sub_672f9 @ 0x672f9 [__watcall]
// ================================================================================================

void __watcall sub_672f9(short param_1,short unaff_DX)

{
  short sVar1;
  int iVar2;
  
  __CHK(0x10);
  sVar1 = (&word_df64c)[param_1 * 0x80];
  iVar2 = param_1 + 1;
  if ((user1_team == iVar2) || ((short)user2_team == iVar2)) {
    if (unaff_DX < 0) {
      (&word_df64c)[param_1 * 0x80] = (&word_df64c)[param_1 * 0x80] | 0xfff0;
    }
    else {
      (&word_df64c)[param_1 * 0x80] = unaff_DX;
      if (((game_flags & 1) == 0) && ((game_flags & 8) != 0)) {
        if (-1 < *p_puck_carrier) {
          if ((uint)(*p_puck_carrier < '\x06') != (int)param_1) {
            *(undefined *)((int)&word_df64c + param_1 * 0x100 + 1) = 0xff;
          }
        }
      }
    }
    if (((-1 < (short)(&word_df64c)[param_1 * 0x80]) || (-1 < sVar1)) &&
       (sVar1 != (&word_df64c)[param_1 * 0x80])) {
      apply_line_change(param_1 * 0x100 + 0xdf614);
    }
  }
  return;
}


// ================================================================================================
// load_team_palettes @ 0x673c5 [__watcall]
// ================================================================================================

void __watcall load_team_palettes(int param_1,int unaff_EDX,int unaff_EBX)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  undefined *puVar5;
  undefined auStack_24 [16];
  
  __CHK(0x30);
  puVar5 = install_path;
  if (byte_ed86d != '\x01') {
    puVar5 = (undefined *)0x0;
  }
  make_path(auStack_24,puVar5,aHOMEPALS_c1dbc,&aBIN);
  iVar1 = loadfile(auStack_24,0);
  iVar4 = iVar1 + param_1 * 0x1c0;
  iVar2 = 0;
  do {
    *(undefined *)(unaff_EBX + 0x180 + iVar2) = *(undefined *)(iVar4 + iVar2);
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0xc0);
  iVar2 = 0;
  do {
    (&remap_home)[iVar2] = *(undefined *)(iVar4 + 0xc0 + iVar2);
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0x100);
  freemem(iVar1);
  puVar5 = install_path;
  if (byte_ed7f7 != '\x01') {
    puVar5 = (undefined *)0x0;
  }
  make_path(auStack_24,puVar5,aAWAYPALS,&aBIN);
  iVar1 = loadfile(auStack_24,0);
  iVar4 = iVar1 + unaff_EDX * 0x1c0;
  iVar2 = 0;
  do {
    *(undefined *)(unaff_EBX + 0x240 + iVar2) = *(undefined *)(iVar4 + iVar2);
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0xc0);
  iVar2 = 0;
  iVar4 = iVar4 + 0xc0;
  do {
    (&remap_away)[iVar2] = *(undefined *)(iVar4 + iVar2);
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0x90);
  iVar2 = 0x90;
  do {
    (&remap_away)[iVar2] = *(char *)(iVar4 + iVar2) + '@';
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0x100);
  freemem(iVar1);
  puVar5 = install_path;
  if (byte_ed92b != '\x01') {
    puVar5 = (undefined *)0x0;
  }
  make_path(auStack_24,puVar5,aRinkpal,0);
  uVar3 = loadshapes(auStack_24,0);
  iVar1 = locateshape(uVar3,&aPal_c1dd6);
  iVar2 = 0;
  do {
    *(undefined *)(unaff_EBX + iVar2) = *(undefined *)(iVar1 + 0x10 + iVar2);
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0x180);
  iVar2 = 0x2f1;
  do {
    *(undefined *)(unaff_EBX + iVar2) = *(undefined *)(iVar1 + 0x10 + iVar2);
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0x300);
  freemem(uVar3);
  return;
}


// ================================================================================================
// sub_67564 @ 0x67564 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall sub_67564(void)

{
  __CHK(4);
  word_cd4fe = 1;
  _word_cd500 = 0xffff;
  return;
}


// ================================================================================================
// sub_67581 @ 0x67581 [__watcall]
// ================================================================================================

undefined * __watcall sub_67581(void)

{
  __CHK(4);
  if ((action_flags & 0x10) == 0) {
    return replay_buffer;
  }
  return replay_write_ptr;
}


// ================================================================================================
// replay_buffer_start @ 0x675a0 [__watcall]
// ================================================================================================

undefined8 __watcall replay_buffer_start(undefined4 param_1,undefined4 unaff_EDX)

{
  __CHK(8);
  if (replay_write_ptr != replay_buffer) {
    return CONCAT44(unaff_EDX,replay_write_ptr + -0x80);
  }
  if ((action_flags & 0x10) != 0) {
    return CONCAT44(unaff_EDX,replay_buffer + 0x9580);
  }
  return CONCAT44(unaff_EDX,replay_buffer);
}


// ================================================================================================
// replay_record_frame @ 0x675d6 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall replay_record_frame(void)

{
  undefined *puVar1;
  byte *pbVar2;
  uint *puVar3;
  undefined4 *puVar4;
  short sVar5;
  
  __CHK(0x1c);
  if ((game_flags & 0x10) == 0) {
    if ((short)(word_cd4fe + 1) < 2) {
      if (((byte)stop_flags & 4) == 0) {
        _word_cd500 = (undefined2)crowd_noise;
      }
      else {
        _word_cd500 = 0xffff;
      }
      crowd_noise._0_2_ = 0xffff;
      word_cd4fe = word_cd4fe + 1;
    }
    else {
      word_cd4fe = word_cd4fe + -1;
      if (((byte)stop_flags & 4) != 0) {
        replay_write_ptr = (uint *)replay_buffer_start();
      }
      puVar4 = &entities;
      for (sVar5 = 0; sVar5 < 0x11; sVar5 = sVar5 + 1) {
        *replay_write_ptr =
             (int)(short)(*(ushort *)((int)puVar4 + 6) & 0x3ff) << 10 |
             (int)(short)(*(ushort *)((int)puVar4 + 2) & 0x3ff) |
             (int)(short)(*(ushort *)((int)puVar4 + 0x12) & 0x7ff) << 0x14 |
             (int)(short)((*(ushort *)(puVar4 + 0x15) >> 8 & 8) << 8) << 0x14;
        replay_write_ptr = replay_write_ptr + 1;
        puVar4 = puVar4 + 0x20;
      }
      puVar4 = &entities;
      for (sVar5 = 0; sVar5 < 0xc; sVar5 = sVar5 + 1) {
        puVar3 = (uint *)((int)replay_write_ptr + 1);
        *(undefined *)replay_write_ptr = *(undefined *)((int)puVar4 + 0x5e);
        replay_write_ptr = puVar3;
        puVar4 = puVar4 + 0x20;
      }
      puVar4 = &entities;
      sVar5 = 0;
      while( true ) {
        if (5 < sVar5) break;
        dword_e03ba._2_2_ = *(ushort *)((int)puVar4 + 0x1a);
        if ((short)dword_e03ba._2_2_ < 0) {
          dword_e03ba._2_2_ = 0xf;
        }
        if (*(short *)((int)puVar4 + 0x9a) < 0) {
          dword_e03ba._2_2_ = dword_e03ba._2_2_ | 0xf0;
        }
        else {
          dword_e03ba._2_2_ = dword_e03ba._2_2_ | *(short *)((int)puVar4 + 0x9a) << 4;
        }
        puVar4 = puVar4 + 0x40;
        puVar3 = (uint *)((int)replay_write_ptr + 1);
        *(undefined *)replay_write_ptr = dword_e03ba._2_1_;
        replay_write_ptr = puVar3;
        sVar5 = sVar5 + 1;
      }
      puVar1 = (undefined *)((int)replay_write_ptr + 1);
      *(undefined *)replay_write_ptr = *p_puck_z;
      replay_write_ptr = (uint *)puVar1;
      puVar1 = (undefined *)((int)replay_write_ptr + 1);
      *(undefined *)replay_write_ptr = byte_dffa6;
      replay_write_ptr = (uint *)puVar1;
      puVar1 = (undefined *)((int)replay_write_ptr + 1);
      *(undefined *)replay_write_ptr = word_cd500;
      replay_write_ptr = (uint *)puVar1;
      pbVar2 = (byte *)((int)replay_write_ptr + 1);
      *(undefined *)replay_write_ptr = (undefined)crowd_noise;
      replay_write_ptr = (uint *)pbVar2;
      crowd_noise._0_2_ = 0xffff;
      _word_cd500 = 0xffff;
      pbVar2 = (byte *)((int)replay_write_ptr + 1);
      *(byte *)replay_write_ptr = (char)user2_slot << 4 | user1_slot & 0xf;
      replay_write_ptr = (uint *)pbVar2;
      pbVar2 = (byte *)((int)replay_write_ptr + 1);
      *(byte *)replay_write_ptr = *p_puck_carrier;
      replay_write_ptr = (uint *)pbVar2;
      pbVar2 = (byte *)((int)replay_write_ptr + 1);
      *(byte *)replay_write_ptr = byte_e9abb << 4 | penalized_count & 0xf;
      replay_write_ptr = (uint *)pbVar2;
      pbVar2 = (byte *)((int)replay_write_ptr + 1);
      *(byte *)replay_write_ptr = (byte)camera;
      replay_write_ptr = (uint *)pbVar2;
      *(undefined2 *)replay_write_ptr = camera._2_2_;
      replay_write_ptr = (uint *)((int)replay_write_ptr + 2);
      *(undefined2 *)replay_write_ptr = crowd_noise._2_2_;
      replay_write_ptr = (uint *)((int)replay_write_ptr + 2);
      for (sVar5 = 0; sVar5 < 10; sVar5 = sVar5 + 1) {
        puVar3 = (uint *)((int)replay_write_ptr + 1);
        *(byte *)replay_write_ptr =
             *(byte *)((int)&unk_dee96 + (sVar5 * 2 + 1) * 0xc + 1) & 0xf |
             *(char *)((int)&unk_dee96 + sVar5 * 0x18 + 1) << 4;
        replay_write_ptr = puVar3;
      }
      for (sVar5 = 0; sVar5 < 0x14; sVar5 = sVar5 + 1) {
        puVar3 = (uint *)((int)replay_write_ptr + 1);
        *(undefined1 *)replay_write_ptr = (&unk_dee94)[sVar5 * 0xc];
        replay_write_ptr = puVar3;
      }
      if (replay_buffer + 0x9600 <= replay_write_ptr) {
        action_flags = action_flags | 0x10;
        replay_write_ptr = (uint *)replay_buffer;
      }
    }
  }
  return;
}


// ================================================================================================
// replay_seek_frames @ 0x67900 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __watcall replay_seek_frames(int param_1,short unaff_DX)

{
  uint uVar1;
  uint *puVar2;
  uint *puVar3;
  short sVar4;
  byte bVar5;
  ushort uVar6;
  int iVar7;
  int aiStack_5c [17];
  int iStack_18;
  
  __CHK(0x6c);
  puVar2 = dword_e03a4;
  iStack_18 = param_1;
  if ((short)param_1 < 0) {
    while ((short)param_1 < 0) {
      if ((uint *)replay_buffer == dword_e03a4) {
        if ((action_flags & 0x10) != 0) {
          dword_e03a4 = (uint *)(replay_buffer + 0x9600);
          goto LAB_00067a0b;
        }
LAB_000679f9:
        param_1 = -1;
        break;
      }
LAB_00067a0b:
      if (dword_e03a4 == replay_write_ptr) goto LAB_000679f9;
      dword_e03a4 = dword_e03a4 + -0x20;
      param_1 = param_1 + 1;
    }
  }
  else {
    while (0 < (short)param_1) {
      param_1 = param_1 + -1;
      puVar3 = dword_e03a4 + 0x20;
      if ((uint *)(replay_buffer + 0x9600) == dword_e03a4 + 0x20) {
        if ((action_flags & 0x10) == 0) {
          param_1 = -1;
          break;
        }
        dword_e03a4 = (uint *)replay_buffer;
        puVar3 = dword_e03a4;
      }
      dword_e03a4 = puVar3;
      if (dword_e03a4 == replay_write_ptr) {
        param_1 = -1;
        dword_e03a4 = dword_e03a4 + -0x20;
        break;
      }
      if ((unaff_DX != 0) && (puVar2 != dword_e03a4)) {
        if (*(byte *)(dword_e03a4 + 0x16) != 0xff) {
          play_sfx(*(byte *)(dword_e03a4 + 0x16));
        }
        if (*(byte *)((int)dword_e03a4 + 0x59) != 0xff) {
          play_sfx(*(byte *)((int)dword_e03a4 + 0x59));
        }
      }
    }
  }
  for (sVar4 = 0; sVar4 < 0x11; sVar4 = sVar4 + 1) {
    uVar1 = *dword_e03a4;
    dword_e03ba._2_1_ = (byte)uVar1;
    dword_e03ba._3_1_ = (byte)(uVar1 >> 8);
    dword_e03be._0_2_ = (short)(uVar1 >> 0x10);
    uVar6 = (ushort)uVar1 & 0x3ff;
    dword_e03be._2_1_ = (byte)uVar6;
    dword_e03be._3_1_ = (byte)(uVar6 >> 8);
    dword_e03a4 = dword_e03a4 + 1;
    if ((uVar1 & 0x200) != 0) {
      dword_e03be._3_1_ = dword_e03be._3_1_ | 0xfc;
    }
    *(ushort *)(&unk_e9f18 + sVar4 * 2) = CONCAT11(dword_e03be._3_1_,dword_e03be._2_1_);
    uVar1 = CONCAT22((short)dword_e03be,CONCAT11(dword_e03ba._3_1_,dword_e03ba._2_1_)) >> 10;
    dword_e03ba._2_1_ = (byte)uVar1;
    dword_e03ba._3_1_ = (byte)(uVar1 >> 8);
    dword_e03be._0_2_ = (short)dword_e03be >> 10;
    uVar6 = (ushort)uVar1 & 0x3ff;
    dword_e03be._2_1_ = (byte)uVar6;
    dword_e03be._3_1_ = (byte)(uVar6 >> 8);
    if ((uVar1 & 0x200) != 0) {
      dword_e03be._3_1_ = dword_e03be._3_1_ | 0xfc;
    }
    *(ushort *)(&unk_e9f3a + sVar4 * 2) = CONCAT11(dword_e03be._3_1_,dword_e03be._2_1_);
    iVar7 = CONCAT22((short)dword_e03be,CONCAT11(dword_e03ba._3_1_,dword_e03ba._2_1_)) >> 10;
    ram0x000e03b9 = (uint)ram0x000e03b9;
    dword_e03ba._3_1_ = (byte)((uint)iVar7 >> 8);
    dword_e03be._0_2_ = (short)dword_e03be >> 10;
    uVar6 = (ushort)iVar7 & 0x7ff;
    dword_e03be._2_1_ = (byte)uVar6;
    dword_e03be._3_1_ = (byte)(uVar6 >> 8);
    if (uVar6 == 0x7ff) {
      dword_e03be._2_1_ = 0xff;
      dword_e03be._3_1_ = 0xff;
    }
    (&unk_e9f5c)[sVar4] = CONCAT11(dword_e03be._3_1_,dword_e03be._2_1_);
    (&unk_e9f7e)[sVar4] = (dword_e03ba._3_1_ & 8) != 0;
  }
  for (sVar4 = 0; sVar4 < 0xc; sVar4 = sVar4 + 1) {
    bVar5 = *(byte *)dword_e03a4;
    dword_e03a4 = (uint *)((int)dword_e03a4 + 1);
    (&unk_e9f8f)[sVar4] = bVar5;
  }
  for (sVar4 = 0; sVar4 < 6; sVar4 = sVar4 + 1) {
    ram0x000e03b9 = CONCAT13(*(byte *)dword_e03a4,ram0x000e03b9);
    bVar5 = *(byte *)dword_e03a4 & 0xf;
    if (bVar5 == 0xf) {
      bVar5 = 0xff;
    }
    dword_e03a4 = (uint *)((int)dword_e03a4 + 1);
    (&unk_e9f9b)[sVar4 * 2] = bVar5;
    bVar5 = (byte)((int)ram0x000e03b9 >> 0x1c) & 0xf;
    if (bVar5 == 0xf) {
      bVar5 = 0xff;
    }
    (&unk_e9f9c)[sVar4 * 2] = bVar5;
  }
  dword_e9fa5._2_2_ = (short)(char)*(byte *)dword_e03a4;
  dword_e9fa9._0_2_ = (short)(char)*(byte *)((int)dword_e03a4 + 1);
  dword_e9fa9._2_1_ = *(byte *)(dword_e03a4 + 1) & 0xf;
  if (dword_e9fa9._2_1_ == 0xf) {
    dword_e9fa9._2_1_ = 0xff;
  }
  dword_e03be._2_1_ = (char)*(byte *)(dword_e03a4 + 1) >> 4 & 0xf;
  dword_e9fa9._3_1_ = dword_e03be._2_1_;
  if (dword_e03be._2_1_ == 0xf) {
    dword_e9fa9._3_1_ = 0xff;
  }
  byte_e9fad = *(byte *)((int)dword_e03a4 + 5);
  dword_e03ba._2_1_ = *(byte *)((int)dword_e03a4 + 6);
  byte_e9fae = dword_e03ba._2_1_ & 0xf;
  byte_e9faf = (char)dword_e03ba._2_1_ >> 4 & 0xf;
  camera._0_2_ = (short)(char)*(byte *)((int)dword_e03a4 + 7);
  camera._2_2_ = *(undefined2 *)(dword_e03a4 + 2);
  crowd_noise._2_2_ = *(undefined2 *)((int)dword_e03a4 + 10);
  dword_e03a4 = dword_e03a4 + 3;
  word_e9fb0 = (short)camera;
  word_e9fb2 = camera._2_2_;
  for (sVar4 = 0; sVar4 < 10; sVar4 = sVar4 + 1) {
    dword_e03ba._2_1_ = *(byte *)dword_e03a4;
    dword_e03a4 = (uint *)((int)dword_e03a4 + 1);
    *(char *)((int)&unk_e9fd9 + sVar4 * 2 + 3) = (char)((int)(uint)dword_e03ba._2_1_ >> 4);
    (&unk_e9fdd)[sVar4 * 2] = dword_e03ba._2_1_ & 0xf;
  }
  for (sVar4 = 0; sVar4 < 0x14; sVar4 = sVar4 + 1) {
    dword_e03ba._2_1_ = *(byte *)dword_e03a4;
    dword_e03ba._3_1_ = 0;
    if (dword_e03ba._2_1_ == 0xff) {
      dword_e03ba._2_1_ = 0xff;
      dword_e03ba._3_1_ = 0xff;
    }
    dword_e03a4 = (uint *)((int)dword_e03a4 + 1);
    (&unk_e9fb4)[sVar4] = CONCAT11(dword_e03ba._3_1_,dword_e03ba._2_1_);
  }
  if ((unaff_DX == 0) || (dword_e03a4 == replay_write_ptr)) {
    sound_pause_all();
  }
  else {
    update_ambient_audio((int)(short)((short)iStack_18 * 2));
  }
  dword_e03a4 = dword_e03a4 + -0x20;
  for (sVar4 = 0; sVar4 < 0x11; sVar4 = sVar4 + 1) {
    iVar7 = (int)sVar4;
    aiStack_5c[iVar7] = *(int *)((int)&word_e9f36 + iVar7 * 2 + 2) >> 0x10;
    *(int *)(&unk_e9ff0 + iVar7 * 2) = iVar7;
  }
  sub_93540(0x11,aiStack_5c,&unk_e9ff0);
  return param_1;
}


// ================================================================================================
// replay_draw_frame @ 0x67dcc [__watcall]
// ================================================================================================

/* WARNING: Removing unreachable block (ram,0x00068024) */

void __watcall replay_draw_frame(short param_1,short unaff_DX)

{
  undefined2 uVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  short sVar8;
  short sVar9;
  bool bVar10;
  int aiStack_48 [6];
  int local_30;
  int iStack_2c;
  short sStack_28;
  short local_26;
  undefined2 uStack_24;
  undefined4 local_22;
  undefined2 local_1e;
  byte bStack_1c;
  char cStack_1b;
  short sStack_18;
  
  __CHK(100);
  if (-0x10 < (short)camera) {
    if ((camera._2_2_ < 0x50) && (-0x94 < camera._2_2_)) {
      for (sVar8 = 0; (sVar8 < byte_e9fae && (sVar8 < 3)); sVar8 = sVar8 + 1) {
        draw_sprite_world(0x17e,0xb3,(int)(short)((sVar8 + 3) * -0xb),0,0);
      }
    }
    if ((-0x4b < camera._2_2_) && (camera._2_2_ < 0xb1)) {
      iVar3 = byte_e9faf + -1;
      if (1 < iVar3) {
        iVar3 = 2;
      }
      for (; -1 < (short)iVar3; iVar3 = iVar3 + -1) {
        draw_sprite_world(0x17e,0xb3,(int)(short)(((short)iVar3 + 3) * 0xb),0,1);
      }
    }
  }
  for (sVar8 = 0; sVar8 < 0x12; sVar8 = sVar8 + 1) {
    if (-1 < (short)(&unk_e9fb4)[sVar8]) {
      sVar9 = (&unk_e9fb4)[sVar8] * 3;
      sVar2 = *(short *)((int)&aGgG + sVar9 * 2 + 2);
      local_22 = CONCAT22(sVar2,(undefined2)local_22);
      sStack_18 = *(short *)((int)&aGgG + (short)(sVar9 + 1) * 2 + 2);
      bStack_1c = (&unk_cce00)
                  [(*(int *)((int)&unk_e9fd9 + (int)sVar8) >> 0x18) +
                   (*(int *)((int)&aGgG + (short)(sVar9 + 2) * 2) >> 0x10)];
      cStack_1b = (char)bStack_1c >> 7;
      blit_sprite((&effect_frames)[CONCAT13(cStack_1b,CONCAT12(bStack_1c,local_1e)) >> 0x10],
                  (int)sVar2,(int)sStack_18,0xc0 < sVar2,0xffffffff,0);
    }
  }
  for (sVar8 = 0x13; 0x11 < sVar8; sVar8 = sVar8 + -1) {
    sVar2 = (&unk_e9fb4)[sVar8];
    if (sVar2 < 0) {
      bStack_1c = 0xff;
      cStack_1b = -1;
    }
    else {
      sVar2 = sVar2 * 3;
      local_22 = CONCAT22(*(undefined2 *)((int)&aGgG + sVar2 * 2 + 2),(undefined2)local_22);
      sStack_18 = *(short *)((int)&aGgG + (short)(sVar2 + 1) * 2 + 2);
      sVar2 = sVar2 + 2;
      bStack_1c = (&unk_cce00)
                  [(*(int *)((int)&unk_e9fd9 + (int)sVar8) >> 0x18) +
                   (*(int *)((int)&aGgG + sVar2 * 2) >> 0x10)];
      cStack_1b = (char)bStack_1c >> 7;
    }
    if ((100 < CONCAT11(cStack_1b,bStack_1c)) || (sVar2 < 0)) {
      if (sVar8 == 0x12) {
        uVar1 = 0x1a5;
      }
      else {
        uVar1 = 0x12d;
      }
      blit_sprite(dword_e0220,4,uVar1,0,sVar8 == 0x13,0);
    }
    if (-1 < cStack_1b) {
      blit_sprite((&effect_frames)[CONCAT13(cStack_1b,CONCAT12(bStack_1c,local_1e)) >> 0x10],
                  local_22 >> 0x10,(int)sStack_18,0,sVar8 == 0x13,0);
    }
    if (sVar8 == 0x12) {
      blit_sprite(dword_e0230,4,0x1a5,0,0xffffffff,0);
    }
    else {
      bStack_1c = (byte)word_e9f7a;
      cStack_1b = (char)((ushort)word_e9f7a >> 8);
      if (0x361 < word_e9f7a) {
        draw_sprite_world(CONCAT13(cStack_1b,CONCAT12(bStack_1c,local_1e)) >> 0x10,
                          (int)(short)word_e9f36,(int)word_e9f58,0,0);
      }
    }
  }
  if (camera._2_2_ < -0xb0) {
    uStack_24 = (undefined2)dword_d30b8;
    setclip(dword_d30bc,dword_d30c0,dword_d30b0,0x244);
  }
  for (sVar8 = 0; sVar8 < 3; sVar8 = sVar8 + 1) {
    iVar3 = (int)sVar8;
    aiStack_48[iVar3 + 3] = 0;
    aiStack_48[iVar3] = iVar3;
  }
  if (byte_e9fad != -1) {
    aiStack_48[5] = *(int *)((int)&word_e9f36 + byte_e9fad * 2 + 2) >> 0x10;
  }
  if (-1 < (char)dword_e9fa9._2_1_) {
    aiStack_48[3] = *(int *)((int)&word_e9f36 + (char)dword_e9fa9._2_1_ * 2 + 2) >> 0x10;
  }
  if (-1 < (char)dword_e9fa9._3_1_) {
    aiStack_48[4] = *(int *)((int)&word_e9f36 + (char)dword_e9fa9._3_1_ * 2 + 2) >> 0x10;
  }
  sub_93540(3,aiStack_48 + 3,(short)aiStack_48);
  for (sVar8 = 0; sVar8 < 3; sVar8 = sVar8 + 1) {
    sVar2 = *(short *)(aiStack_48 + sVar8);
    if (sVar2 == 2) {
      iVar4 = (int)byte_e9fad;
      if (iVar4 != -1) {
        uVar1 = 0;
        iVar3 = *(int *)((int)&word_e9f14 + iVar4 * 2 + 2) >> 0x10;
        iVar5 = arrow_frames >> 0x10;
        iVar6 = 0;
        iVar4 = *(int *)((int)&word_e9f36 + iVar4 * 2 + 2) >> 0x10;
LAB_0006833f:
        draw_sprite_world(iVar5,iVar3,iVar4,iVar6,uVar1);
      }
    }
    else {
      bStack_1c = dword_e9fa9._2_1_;
      if (sVar2 != 0) {
        bStack_1c = dword_e9fa9._3_1_;
      }
      cStack_1b = (char)bStack_1c >> 7;
      if ((-1 < (char)bStack_1c) &&
         (iVar3 = (CONCAT13(cStack_1b,CONCAT12(bStack_1c,local_1e)) >> 0x10) * 2,
         *(int *)(&unk_e9f5a + iVar3) >> 0x10 != -1)) {
        local_22 = CONCAT22(*(short *)(&unk_e9f18 + iVar3),(undefined2)local_22);
        sStack_18 = *(short *)(&unk_e9f3a + iVar3);
        bStack_1c = 0;
        if ((int)sStack_18 < 0x140 - (unaff_DX + 0xa8)) {
          sStack_18 = 0x140 - (unaff_DX + 0xa8);
          bStack_1c = 1;
        }
        else if (0x140 - unaff_DX <= (int)sStack_18) {
          sStack_18 = 0x141 - unaff_DX;
          bStack_1c = 2;
        }
        iVar3 = (int)*(short *)(&unk_e9f18 + iVar3);
        if (bStack_1c == 0) {
          if (iVar3 < 0x140 - (0xc0 - param_1)) {
            if (iVar3 < param_1 + -0xc0) {
              local_22 = CONCAT22(param_1 + -0xc0,(undefined2)local_22);
              bStack_1c = 4;
            }
          }
          else {
            local_22 = CONCAT22(-(0xc0 - param_1) + 0x13f,(undefined2)local_22);
            bStack_1c = 8;
          }
        }
        else if (iVar3 < 0x134 - (0xc0 - param_1)) {
          if (iVar3 < param_1 + -0xb4) {
            local_22 = CONCAT22(param_1 + -0xb4,(undefined2)local_22);
            bStack_1c = bStack_1c | 4;
          }
        }
        else {
          local_22 = CONCAT22(-(0xc0 - param_1) + 0x133,(undefined2)local_22);
          bStack_1c = bStack_1c | 8;
        }
        cStack_1b = '\0';
        iVar3 = local_22 >> 0x10;
        if (bStack_1c == 0) {
          uVar1 = 0;
          iVar4 = (int)sStack_18;
          iVar5 = *(int *)(&marker_frames + sVar2) >> 0x10;
          iVar6 = 0;
        }
        else {
          uVar1 = 0;
          local_30 = (int)(short)(ushort)(bStack_1c & 8);
          iStack_2c = (int)sStack_18;
          sStack_28 = (short)((uint)local_22 >> 0x10);
          local_26 = sStack_28 >> 0xf;
          iVar3 = sub_b340b((int)(uint)CONCAT12(bStack_1c,local_1e) >> 0x10,0);
          iVar5 = *(int *)((int)&arrow_frames + iVar3 * 2 + sVar2 * 0x10) >> 0x10;
          iVar3 = CONCAT22(local_26,sStack_28);
          iVar6 = local_30;
          iVar4 = iStack_2c;
        }
        goto LAB_0006833f;
      }
    }
  }
  bStack_1c = (byte)word_e9f7a;
  cStack_1b = (char)((ushort)word_e9f7a >> 8);
  if ((word_e9f7a < 0x284) || (0x288 < word_e9f7a)) {
    if (((word_e9f7a != 0x189) ||
        ((CONCAT13(dword_e9fa5._3_1_,CONCAT12(dword_e9fa5._2_1_,(undefined2)dword_e9fa5)) >> 0x10 <
          -0xff || (byte_e9fad == '\x10')))) &&
       ((word_e9f58 < 0 || ((word_e9f7a < 0x22a || (0x237 < word_e9f7a)))))) goto LAB_00068400;
    bVar10 = false;
  }
  else {
    bVar10 = (short)word_e9f36 < 0;
  }
  draw_sprite_world(CONCAT13(cStack_1b,CONCAT12(bStack_1c,local_1e)) >> 0x10,(int)(short)word_e9f36,
                    (int)word_e9f58,bVar10,0);
LAB_00068400:
  if ((byte_e9fad != '\x10') && (-1 < dword_e9fa5._3_1_)) {
    draw_sprite_world((int)dword_e9f76._2_2_,(int)dword_e9f32._2_2_,
                      (int)(short)((short)(((CONCAT13(dword_e9fa5._3_1_,
                                                      CONCAT12(dword_e9fa5._2_1_,
                                                               (undefined2)dword_e9fa5)) >> 0x10) *
                                           3) / 2) + dword_e9f54._2_2_),0,0);
  }
  sVar8 = 0;
  do {
    if (0x10 < sVar8) {
      if ((dword_e9f54._2_2_ < -0xe7) && (-0xed < dword_e9f54._2_2_)) {
        if (dword_e9f32 < 0) {
          iVar3 = -(int)dword_e9f32._2_2_;
        }
        else {
          iVar3 = (int)dword_e9f32._2_2_;
        }
        if ((iVar3 < 0x15) && (0xc < CONCAT11(dword_e9fa5._3_1_,dword_e9fa5._2_1_))) {
          draw_sprite_world((int)dword_e9f76._2_2_,(int)dword_e9f32._2_2_,
                            (int)(short)((short)(((CONCAT13(dword_e9fa5._3_1_,
                                                            CONCAT12(dword_e9fa5._2_1_,
                                                                     (undefined2)dword_e9fa5)) >>
                                                  0x10) * 3) / 2) + dword_e9f54._2_2_),0,0);
        }
      }
      if (camera._2_2_ < -0xb0) {
        setclip(dword_d30bc,dword_d30c0,dword_d30b0,uStack_24);
      }
      if (camera._2_2_ < -0x90) {
        sub_11136();
      }
      if (((word_e9f58 < 0) && (0x229 < word_e9f7a)) && (word_e9f7a < 0x238)) {
        draw_sprite_world((int)word_e9f7a,(int)(short)word_e9f36,(int)word_e9f58,0,0);
      }
      if (((dword_e9f54._2_2_ < -0x108) && (byte_e9fad == -1)) && (-1 < dword_e9fa5._3_1_)) {
        draw_sprite_world((int)dword_e9f76._2_2_,(int)dword_e9f32._2_2_,
                          (int)(short)((short)(((CONCAT13(dword_e9fa5._3_1_,
                                                          CONCAT12(dword_e9fa5._2_1_,
                                                                   (undefined2)dword_e9fa5)) >> 0x10
                                                ) * 3) / 2) + dword_e9f54._2_2_),0,0);
      }
      return;
    }
    sVar2 = (&unk_e9ff0)[sVar8 * 2];
    if (sVar2 != 0xf) {
      if (sVar2 == 0xe) {
        if (((byte_e9fad == -1) && (0 < CONCAT11(dword_e9fa5._3_1_,dword_e9fa5._2_1_))) &&
           (dword_e9f54._2_2_ < 0xe8)) {
          if ((dword_e9f54 >> 0x10 < -0xe7) && (-0xf1 < dword_e9f54 >> 0x10)) {
            iVar3 = dword_e9f32 >> 0x10;
            if (dword_e9f32 < 0) {
              iVar3 = -iVar3;
            }
            if ((iVar3 < 0x15) && (CONCAT11(dword_e9fa5._3_1_,dword_e9fa5._2_1_) < 0xd))
            goto LAB_00068722;
          }
          sVar2 = (short)(((CONCAT13(dword_e9fa5._3_1_,
                                     CONCAT12(dword_e9fa5._2_1_,(undefined2)dword_e9fa5)) >> 0x10) *
                          3) / 2) + dword_e9f54._2_2_;
LAB_0006871d:
          draw_sprite_world(dword_e9f76 >> 0x10,dword_e9f32 >> 0x10,(int)sVar2,0,0);
        }
      }
      else if ((0xb < sVar2) || (-1 < (char)(&unk_e9f9b)[sVar2])) {
        if ((*(int *)(&unk_e9f5a + sVar2 * 2) >> 0x10 != -1) && (sVar2 < 0xc)) {
          if (((((byte_e9fad == -1) || (sVar2 != byte_e9fad)) && (sVar2 != (char)dword_e9fa9._2_1_))
              && ((sVar2 != (char)dword_e9fa9._3_1_ && (iVar3 = (int)sVar2, iVar3 != dword_ed74c))))
             && (sVar2 != dword_cd4fa._2_2_)) {
            if (show_names == 0) goto LAB_00068622;
            iVar6 = *(int *)(&unk_e9f8c + iVar3);
            iVar4 = *(int *)((int)&word_e9f36 + iVar3 * 2 + 2);
            iVar3 = *(int *)((int)&word_e9f14 + iVar3 * 2 + 2);
            uVar7 = 0xffffffff;
          }
          else {
            iVar3 = (int)sVar2;
            sStack_28 = (short)(char)((uint)*(undefined4 *)(&unk_e9f98 + iVar3) >> 0x18);
            local_26 = (short)((int)*(undefined4 *)(&unk_e9f98 + iVar3) >> 0x1f);
            iVar6 = *(int *)(&unk_e9f8c + iVar3);
            iVar4 = *(int *)((int)&word_e9f36 + iVar3 * 2 + 2);
            iVar3 = *(int *)((int)&word_e9f14 + iVar3 * 2 + 2);
            uVar7 = CONCAT22(local_26,sStack_28);
          }
          draw_player_number(iVar3 >> 0x10,iVar4 >> 0x10,iVar6 >> 0x18,uVar7);
        }
LAB_00068622:
        iVar3 = (int)sVar2;
        draw_sprite_world(*(int *)(&unk_e9f5a + iVar3 * 2) >> 0x10,
                          *(int *)((int)&word_e9f14 + iVar3 * 2 + 2) >> 0x10,
                          *(int *)((int)&word_e9f36 + iVar3 * 2 + 2) >> 0x10,
                          *(int *)((int)&word_e9f7a + iVar3 + 1) >> 0x18,5 < sVar2);
        if ((sVar2 == 0xc) && (byte_e9fad != '\x10')) {
          if (dword_e9f32 < 0) {
            iVar3 = -(int)dword_e9f32._2_2_;
          }
          else {
            iVar3 = (int)dword_e9f32._2_2_;
          }
          if ((iVar3 == 6) && (dword_e9f54._2_2_ == 0xf0)) {
LAB_000686e1:
            sVar2 = (short)(((CONCAT13(dword_e9fa5._3_1_,
                                       CONCAT12(dword_e9fa5._2_1_,(undefined2)dword_e9fa5)) >> 0x10)
                            * 3) / 2) + dword_e9f54._2_2_;
            goto LAB_0006871d;
          }
          if ((sRam000e9f52 <= dword_e9f54._2_2_) &&
             (0xc < CONCAT11(dword_e9fa5._3_1_,dword_e9fa5._2_1_))) {
            iVar3 = (int)dword_e9f32._2_2_ - (iRam000e9f2e >> 0x10);
            if (iVar3 < 0) {
              iVar3 = -iVar3;
            }
            if (iVar3 < 0x15) goto LAB_000686e1;
          }
        }
      }
    }
LAB_00068722:
    sVar8 = sVar8 + 1;
  } while( true );
}


// ================================================================================================
// dump_stats_log @ 0x688a4 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall dump_stats_log(void)

{
  short sVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined *puVar8;
  int extraout_EDX;
  int extraout_EDX_00;
  int extraout_EDX_01;
  int extraout_EDX_02;
  int extraout_EDX_03;
  int extraout_EDX_04;
  int *extraout_EDX_05;
  int extraout_EDX_06;
  int extraout_EDX_07;
  int extraout_EDX_08;
  int extraout_EDX_09;
  int extraout_EDX_10;
  int extraout_EDX_11;
  char *__format;
  undefined2 *puVar9;
  char acStack_218 [512];
  
  __CHK(0x250);
  if (word_cbc42 != 0) {
    if (((byte)stop_flags & 0x80) == 0) {
      puVar9 = (undefined2 *)&unk_c234d;
    }
    else {
      puVar9 = &aO_c234b;
    }
    sub_935e0(puVar9);
    acStack_218[0] = '\0';
    iVar3 = sprintf(acStack_218,unk_c234f,ram0x000df63c >> 0x10,dword_df73c >> 0x10);
    iVar4 = sprintf(acStack_218 + iVar3,aPsDDDDDFDDDDBDD,penalty_shot_phase,penalty_shot_active,
                    penalty_shot_setup,dword_cc120,penalty_shot_timer,penalty_shot_slot,dword_cc100,
                    penalty_shot_team,_dword_cc108,defenders_ahead,breakaway_flag);
    uVar5 = all_players_arrived();
    sub_935e0(aLipD,uVar5);
    iVar6 = sprintf(acStack_218 + iVar3 + iVar4,aHVposDDDD,(int)(short)camera,(int)camera._2_2_,
                    (int)_camera_target_x,(int)(short)camera_target_y);
    iVar6 = iVar3 + iVar4 + iVar6;
    iVar3 = sprintf(acStack_218 + iVar6,aRefDD,(int)ref_phase,(int)whistle_timer);
    iVar6 = iVar6 + iVar3;
    iVar3 = sprintf(acStack_218 + iVar6,aPbDD,infraction_queue >> 0x18,(int)unk_e9a17);
    iVar6 = iVar6 + iVar3;
    iVar3 = sprintf(acStack_218 + iVar6,aGDD,ram0x000df64a >> 0x10,ram0x000df74a >> 0x10);
    iVar6 = iVar6 + iVar3;
    iVar3 = sprintf(acStack_218 + iVar6,aGODPODGoDGsD,(int)game_over,(int)period_over,
                    (uint)((game_flags & 0x40) != 0),(uint)((game_flags & 0x80) != 0));
    iVar6 = iVar6 + iVar3;
    iVar3 = sprintf(acStack_218 + iVar6,aGDD_c23f4,(int)clock_seconds,(int)clock_sub);
    iVar6 = iVar6 + iVar3;
    iVar3 = sprintf(acStack_218 + iVar6,aC12DDDD,(int)_user1_slot,(int)user2_slot,(int)user1_team,
                    (int)(short)user2_team);
    sprintf(acStack_218 + iVar6 + iVar3,aPuckcDGmclockDGmpenDPcdw,
            (int)*(char *)CONCAT22(p_puck_carrier._2_2_,(undefined2)p_puck_carrier),
            (uint)((game_flags & 1) != 0),(uint)((game_flags & 4) != 0),_away_team_id >> 0x10);
    sub_935e0(acStack_218);
    for (sVar2 = 0; sVar2 < 0x11; sVar2 = sVar2 + 1) {
      if (((sVar2 != 0xc) && (sVar2 != 0xd)) && (sVar2 != 0xf)) {
        acStack_218[0] = '\0';
        iVar3 = sprintf(acStack_218,(char *)&aD_c2437,(int)(&unk_df848)[sVar2 * 0x20] >> 0x10);
        iVar4 = sprintf(acStack_218 + iVar3,(char *)&aD_c243c,(uint)*(byte *)(extraout_EDX + 0x5e));
        iVar6 = sprintf(acStack_218 + iVar3 + iVar4,(char *)&aD_c243c,
                        *(int *)(extraout_EDX_00 + 0x44) >> 0x18);
        iVar6 = iVar3 + iVar4 + iVar6;
        iVar3 = sprintf(acStack_218 + iVar6,(char *)&aD_c243c,
                        *(int *)(&unk_df690 +
                                (uint)((*(byte *)(extraout_EDX_01 + 0x44) & 0x40) != 0) * 0x80 +
                                (*(int *)(extraout_EDX_01 + 0x44) >> 0x18)) >> 0x10);
        iVar6 = iVar6 + iVar3;
        iVar3 = sprintf(acStack_218 + iVar6,(char *)&aD_c2440,
                        *(int *)(extraout_EDX_02 + 0x40) >> 0x18);
        iVar6 = iVar6 + iVar3;
        iVar3 = sprintf(acStack_218 + iVar6,(char *)&aD_c2445,
                        *(int *)(extraout_EDX_03 + 0x3f) >> 0x18);
        iVar6 = iVar6 + iVar3;
        if (*(short *)(extraout_EDX_04 + 0x1a) < 0) {
          puVar7 = &aPen;
        }
        else {
          puVar7 = (undefined4 *)(&off_cd984)[*(int *)(extraout_EDX_04 + 0x18) >> 0x10];
        }
        iVar3 = sprintf(acStack_218 + iVar6,aDS,(int)sVar2,puVar7);
        iVar6 = iVar6 + iVar3;
        iVar3 = sprintf(acStack_218 + iVar6,unk_c2451,*extraout_EDX_05 >> 0x10,
                        extraout_EDX_05[1] >> 0x10,*(int *)((int)extraout_EDX_05 + 10) >> 0x10,
                        extraout_EDX_05[3] >> 0x10,extraout_EDX_05[0xd] >> 0x10,
                        extraout_EDX_05[10] >> 0x10,*(int *)((int)extraout_EDX_05 + 0x2a) >> 0x10);
        iVar6 = iVar6 + iVar3;
        iVar3 = extraout_EDX_06;
        if (sVar2 == 0xe) {
          iVar3 = sprintf(acStack_218 + iVar6,aVzD,(int)*(short *)p_puck_vz);
          iVar6 = iVar6 + iVar3;
          iVar3 = extraout_EDX_07;
        }
        iVar3 = sprintf(acStack_218 + iVar6,(char *)&aAS,
                        (&off_cd8c4)
                        [*(int *)(iVar3 + 0x1b + (*(int *)(iVar3 + 0x1a) >> 0x10)) >> 0x18]);
        iVar6 = iVar6 + iVar3;
        iVar3 = extraout_EDX_08;
        if ((*(byte *)(extraout_EDX_08 + 0x44) & 0x20) != 0) {
          iVar3 = sprintf(acStack_218 + iVar6,(char *)&aL_c2478);
          iVar6 = iVar6 + iVar3;
          iVar3 = extraout_EDX_09;
        }
        if ((*(byte *)(iVar3 + 0x45) & 2) != 0) {
          iVar3 = sprintf(acStack_218 + iVar6,(char *)&aI_c247a);
          iVar6 = iVar6 + iVar3;
        }
        iVar3 = sprintf(acStack_218 + iVar6,(char *)&asc_c247c);
        for (sVar1 = 0;
            (sVar1 < 0x78 && (*(int *)(extraout_EDX_10 + 0x36) >> 0x10 != (&unk_cd504)[sVar1]));
            sVar1 = sVar1 + 1) {
        }
        if (sVar1 < 0x78) {
          puVar8 = (&off_cd6e4)[sVar1];
          __format = (char *)&aS_c2485;
        }
        else {
          puVar8 = (undefined *)(*(int *)(extraout_EDX_10 + 0x36) >> 0x10);
          __format = aSpaD;
        }
        iVar4 = sprintf(acStack_218 + iVar6 + iVar3,__format,puVar8);
        iVar4 = iVar6 + iVar3 + iVar4;
        if ((*(int *)(extraout_EDX_11 + 0x10) >> 0x10 < -1) ||
           (0x46d < *(short *)(extraout_EDX_11 + 0x12))) {
          sprintf(acStack_218 + iVar4,aDebErrorDFrameD,*(int *)(extraout_EDX_11 + 0x68) >> 0x10,
                  *(int *)(extraout_EDX_11 + 0x10) >> 0x10);
          sub_935e0(acStack_218);
          waitkey();
        }
        else {
          sprintf(acStack_218 + iVar4,&unk_c24a0);
          sub_935e0(acStack_218);
        }
      }
    }
  }
  if (word_cbc42 == 0) {
    sVar2 = getkey();
  }
  else {
    sVar2 = waitkey();
  }
  if (sVar2 == 0x30) {
    sub_935e0(aBail);
    (*(code *)funcptr_d41f0)();
  }
  else if (sVar2 == 0x6d) {
    sub_93e38();
  }
  else if (sVar2 == 100) {
    write_stats_table(aStatsLog);
  }
  else if (sVar2 == 0x5c) {
    if (word_cbc42 != 0) {
      flush_key_events();
    }
    word_cbc42 = (ushort)(word_cbc42 == 0);
  }
  return;
}


// ================================================================================================
// write_stats_table @ 0x68e7b [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall write_stats_table(char *param_1)

{
  short sVar1;
  undefined4 uVar2;
  FILE *pFVar3;
  undefined *puVar4;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_ECX_02;
  undefined4 extraout_ECX_03;
  undefined4 extraout_ECX_04;
  undefined4 extraout_ECX_05;
  undefined4 extraout_ECX_06;
  undefined4 extraout_ECX_07;
  undefined4 extraout_ECX_08;
  undefined4 extraout_ECX_09;
  undefined4 extraout_ECX_10;
  undefined4 extraout_ECX_11;
  undefined4 extraout_ECX_12;
  undefined4 extraout_ECX_13;
  undefined4 extraout_ECX_14;
  undefined4 extraout_ECX_15;
  undefined4 extraout_ECX_16;
  undefined4 uVar5;
  FILE *extraout_ECX_17;
  FILE *extraout_ECX_18;
  short sVar6;
  int extraout_EDX;
  int extraout_EDX_00;
  int iVar7;
  int extraout_EDX_01;
  int extraout_EDX_02;
  int extraout_EDX_03;
  int extraout_EDX_04;
  undefined4 *puVar8;
  short *psVar9;
  int *piVar10;
  int *piVar11;
  
  __CHK(0x74);
  pFVar3 = fopen(param_1,(char *)&aAT);
  if (pFVar3 == (FILE *)0x0) {
    sub_935e0(aErrorDumpStats);
  }
  else {
    sub_96185(pFVar3,unk_c24c8,dword_d8c78,dword_d8c6c,dword_c53fb);
    sub_96185(pFVar3,aTmstructs);
    uVar5 = extraout_ECX;
    for (sVar6 = 0; sVar6 < 2; sVar6 = sVar6 + 1) {
      puVar8 = (undefined4 *)((int)&dword_df612 + sVar6 * 0x100 + 2);
      iVar7 = 0;
      while ((ushort)iVar7 < 0xe8) {
        uVar2 = *puVar8;
        puVar8 = puVar8 + 1;
        sub_96185(uVar5,&aX,uVar2);
        uVar5 = extraout_ECX_00;
        iVar7 = extraout_EDX + 4;
      }
      sub_96185(uVar5,&unk_c24a0);
      uVar5 = extraout_ECX_01;
    }
    sub_96185(uVar5,aSortcords);
    uVar5 = extraout_ECX_02;
    for (sVar6 = 0; sVar6 < 0x11; sVar6 = sVar6 + 1) {
      psVar9 = (short *)(&entities + sVar6 * 0x20);
      iVar7 = 0;
      while ((short)iVar7 < 0x48) {
        sVar1 = *psVar9;
        psVar9 = psVar9 + 1;
        sub_96185(uVar5,&aX,(int)sVar1);
        uVar5 = extraout_ECX_03;
        iVar7 = extraout_EDX_00 + 2;
      }
      sub_96185(uVar5,&unk_c24a0);
      uVar5 = extraout_ECX_04;
    }
    for (sVar6 = 0; sVar6 < 0x11; sVar6 = sVar6 + 1) {
      iVar7 = sVar6 * 0x80;
      sub_96185(uVar5,aDDDDDDDDDDDDDDDDDDX,(int)(&DAT_000df884)[sVar6 * 0x20] >> 0x10,
                *(int *)(&unk_df860 + iVar7) >> 0x18,(&DAT_000df87a)[iVar7],(&DAT_000df872)[iVar7],
                (&DAT_000df873)[iVar7],(&DAT_000df874)[iVar7],(&DAT_000df875)[iVar7],
                (&DAT_000df876)[iVar7],(&DAT_000df877)[iVar7],(&DAT_000df881)[iVar7],
                (&DAT_000df880)[iVar7],(&DAT_000df87c)[iVar7],(&DAT_000df878)[iVar7],
                (&DAT_000df87d)[iVar7],(&DAT_000df87b)[iVar7],(&DAT_000df879)[iVar7],
                (&DAT_000df87e)[iVar7],(&unk_df87f)[iVar7],*(int *)(&DAT_000df86e + iVar7) >> 0x10);
      uVar5 = extraout_ECX_05;
    }
    sub_96185(uVar5,unk_c2550);
    sub_96185(extraout_ECX_06,aShtsScoreShotsScorePpgPp);
    sub_96185(extraout_ECX_07,aHomeDDDDDDDDDDD,(int)dword_df612._2_2_,(int)dword_df622._2_2_,
              byte_c5430,byte_c542f,(int)(short)dword_df616,(int)dword_df616._2_2_,
              (int)(short)dword_df61e,(int)dword_df61e._2_2_,(int)(short)dword_df622,
              (int)(short)dword_df63a,(int)dword_df63a._2_2_);
    piVar10 = dword_df6fa;
    sub_96185(extraout_ECX_08,aIPnumGAPenPpgShgEngShtSt);
    iVar7 = 0;
    uVar5 = extraout_ECX_09;
    while (piVar11 = dword_df6fe, sVar6 = (short)iVar7, sVar6 < 0x19) {
      puVar4 = (undefined *)(dword_df702 + sVar6 * 0x27);
      sub_96185(uVar5,a3d3d3d3d3d3d3d3d3d3d3d,(int)sVar6,puVar4[5],(int)*(short *)piVar10,
                *piVar10 >> 0x10,*(int *)((int)piVar10 + 2) >> 0x10,piVar10[1] >> 0x10,
                *(int *)((int)piVar10 + 6) >> 0x10,piVar10[2] >> 0x10,
                *(int *)((int)piVar10 + 10) >> 0x10,piVar10[3] >> 0x10,*puVar4);
      piVar10 = piVar10 + 4;
      uVar5 = extraout_ECX_10;
      iVar7 = extraout_EDX_01 + 1;
    }
    sub_96185(uVar5,aIPnumMinShtSavStatus);
    iVar7 = 0;
    uVar5 = extraout_ECX_11;
    while (sVar6 = (short)iVar7, sVar6 < 3) {
      puVar4 = (undefined *)(dword_df702 + (sVar6 + 0x19) * 0x27);
      sub_96185(uVar5,a3d3d5d3d3d3d,(int)sVar6,puVar4[5],(int)*(short *)piVar11,*piVar11 >> 0x10,
                *(int *)((int)piVar11 + 2) >> 0x10,*puVar4);
      piVar11 = (int *)((int)piVar11 + 6);
      uVar5 = extraout_ECX_12;
      iVar7 = extraout_EDX_02 + 1;
    }
    sub_96185(uVar5,aShtsScoreShotsScorePpgPp_c2689);
    sub_96185(extraout_ECX_13,aAwayDDDDDDDDDDD,(int)dword_df712._2_2_,(int)dword_df722._2_2_,
              byte_c5432,byte_c5431,(int)(short)dword_df716,(int)dword_df716._2_2_,
              (int)dword_df71c._2_2_,(int)_dword_df720,(int)(short)dword_df722,
              (int)dword_df738._2_2_,(int)(short)dword_df73c);
    piVar10 = dword_df7fa;
    sub_96185(extraout_ECX_14,aIPnumGAPenPpgShgEngShtSt_c26fa);
    iVar7 = 0;
    uVar5 = extraout_ECX_15;
    while (piVar11 = dword_df7fe, sVar6 = (short)iVar7, sVar6 < 0x19) {
      puVar4 = (undefined *)(dword_df802 + sVar6 * 0x27);
      sub_96185(uVar5,a3d3d3d3d3d3d3d3d3d3d3d_c272a,(int)sVar6,puVar4[5],(int)*(short *)piVar10,
                *piVar10 >> 0x10,*(int *)((int)piVar10 + 2) >> 0x10,piVar10[1] >> 0x10,
                *(int *)((int)piVar10 + 6) >> 0x10,piVar10[2] >> 0x10,
                *(int *)((int)piVar10 + 10) >> 0x10,piVar10[3] >> 0x10,*puVar4);
      piVar10 = piVar10 + 4;
      uVar5 = extraout_ECX_16;
      iVar7 = extraout_EDX_03 + 1;
    }
    sub_96185(uVar5,aIPnumMinShtSavStatus_c2757);
    iVar7 = 0;
    pFVar3 = extraout_ECX_17;
    while (sVar6 = (short)iVar7, sVar6 < 3) {
      puVar4 = (undefined *)((sVar6 + 0x19) * 0x27 + dword_df802);
      sub_96185(pFVar3,a3d3d5d3d3d3d,(int)sVar6,puVar4[5],(int)*(short *)piVar11,*piVar11 >> 0x10,
                *(int *)((int)piVar11 + 2) >> 0x10,*puVar4);
      piVar11 = (int *)((int)piVar11 + 6);
      pFVar3 = extraout_ECX_18;
      iVar7 = extraout_EDX_04 + 1;
    }
    fclose(pFVar3);
  }
  return;
}


// ================================================================================================
// simulate_game_offscreen @ 0x69336 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __watcall
simulate_game_offscreen
          (undefined4 param_1,short unaff_DX,undefined2 *unaff_EBX,int *unaff_ECX,undefined4 param_5
          )

{
  short sVar1;
  short sVar2;
  short sVar3;
  undefined *puVar4;
  bool bVar5;
  short sVar6;
  undefined2 uVar7;
  undefined2 *puVar8;
  int iVar9;
  undefined4 uVar10;
  ushort extraout_DX;
  undefined2 extraout_DX_00;
  short extraout_DX_01;
  undefined2 *puVar11;
  int extraout_EDX;
  int iVar12;
  int iVar13;
  undefined4 *puVar14;
  int iVar15;
  undefined4 *puVar16;
  undefined *puVar17;
  undefined4 *puVar18;
  undefined4 *puVar19;
  int iVar20;
  int iVar21;
  undefined4 *puVar22;
  byte bVar23;
  undefined8 uVar24;
  undefined4 local_114;
  undefined2 auStackY_ec [56];
  undefined4 auStackY_7c [12];
  undefined4 auStackY_4c [12];
  uint local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  bVar23 = 0;
  __CHK(0x120);
  dword_ccc98 = 0;
  local_18 = CONCAT22((short)((uint)param_1 >> 0x10),game_over);
  iVar21 = 0;
  puVar8 = auStackY_ec;
  do {
    puVar11 = &unk_df692 + iVar21 * 0x80;
    iVar20 = 0;
    do {
      *puVar8 = *puVar11;
      puVar11 = puVar11 + 1;
      puVar8 = puVar8 + 1;
      iVar20 = iVar20 + 1;
    } while (iVar20 < 0x1c);
    iVar21 = iVar21 + 1;
  } while (iVar21 < 2);
  local_1c = option_flags;
  puVar14 = &unk_dc200;
  puVar22 = auStackY_4c;
  for (iVar21 = 0xc; iVar21 != 0; iVar21 = iVar21 + -1) {
    *puVar22 = *puVar14;
    puVar14 = puVar14 + 1;
    puVar22 = puVar22 + 1;
  }
  puVar14 = (undefined4 *)&unk_dabf0;
  puVar22 = auStackY_7c;
  for (iVar21 = 0xc; iVar21 != 0; iVar21 = iVar21 + -1) {
    *puVar22 = *puVar14;
    puVar14 = puVar14 + 1;
    puVar22 = puVar22 + 1;
  }
  local_114 = 0x69465;
  sub_61b85();
  option_flags = option_flags & 0xffffffe4;
  game_over = 0;
  excitement._2_2_ = 0;
  user2_team._2_2_ = (short)param_1;
  local_114 = 0x6949a;
  _away_team_id = unaff_DX;
  sub_1bbcc(2);
  if (dword_cbeca >> 0x10 != -1) {
    local_114 = dword_e0244;
    freemem();
  }
  local_114 = 0x694d1;
  load_team_palettes((int)user2_team._2_2_,(int)_away_team_id,&unk_df314);
  local_114 = 0x694d6;
  load_sprite_banks();
  word_df74c = 0;
  word_df64c = 0;
  local_114 = 0x694eb;
  sub_5b97a();
  user2_slot = 0xffff;
  _user1_slot = 0xffff;
  user2_team._0_2_ = 0;
  user1_team = 0;
  local_114 = 0x69516;
  sVar6 = randomrange(0x78);
  clock_seconds = sVar6 + 0x3c;
  clock_sub = 0;
  hud_clock_min = (int)clock_seconds / 0x3c;
  hud_clock_sec = (int)clock_seconds % 0x3c;
  hud_clock_tenths = 0;
  _period_num = param_5;
  period_idx = (short)param_5 - 1;
  dword_df622 = CONCAT22(*unaff_EBX,(undefined2)dword_df622);
  dword_df722 = CONCAT22(*(undefined2 *)unaff_ECX,(undefined2)dword_df722);
  local_114 = 0x69595;
  _word_df63e = randomrange(7);
  _word_df63e = _word_df63e % 4;
  local_114 = 0x695b5;
  sVar6 = randomrange(7);
  dword_df73c._2_2_ = sVar6 % 4;
  local_114 = 0x695cb;
  wait_sprite_fade((int)sVar6 / 4);
  local_114 = 0x695da;
  set_video_mode(0x140,200);
  if (user2_team._2_2_ < 0x1a) {
    iVar21 = (int)user2_team._2_2_;
  }
  else {
    iVar21 = 0xc;
  }
  local_114 = 0x695f8;
  load_rink(iVar21);
  local_114 = 0x69616;
  iVar21 = show_scoreboard((int)user2_team._2_2_,(int)_away_team_id);
  game_flags = 0x10;
  if ((period_idx & 1) != 0) {
    if ((period_idx == 3) && ((option_flags & 0x200) != 0)) {
      iVar21 = 0;
    }
    else {
      iVar21 = 1;
    }
    if (iVar21 != 0) {
      game_flags = 0x12;
    }
  }
  local_14 = CONCAT22((short)((uint)iVar21 >> 0x10),stop_flags);
  _misc_flags = 0;
  _action_flags = 0;
  stop_flags = 4;
  icing_state._3_1_ = 0;
  icing_state._2_1_ = 0;
  shot_power._2_2_ = 0xffff;
  whistle_timer = 0;
  ref_phase = 0xffff;
  stoppage_timer = 0xffff;
  ref_infraction = 0;
  _penalized_slot = 0xffff;
  dword_cbebe._2_2_ = 0xffff;
  penalty_box_mode = 0;
  _word_cbec8 = 0xffff;
  word_cbece = 0xffff;
  dword_cbeca = -0x10000;
  dword_cbec6 = 0;
  crowd_noise = crowd_noise & 0xffff;
  dword_ccc88 = 0;
  word_df81a = 0xffff;
  word_df816 = 0xffff;
  local_114 = 0x69720;
  sub_5d7f7(0xffffffff,0xffffffff);
  puVar16 = &local_114;
  local_114 = 0x69725;
  sort_draw_order();
  camera._2_2_ = extraout_DX ^ 0xffff;
  camera._0_2_ = 0;
  camera_target_y._2_2_ = 0;
  camera_target_y._0_2_ = 0;
  _camera_target_x = 0;
  dword_c7444 = dword_c7444 + 1000;
  dword_c7448 = dword_c7448 + 1000;
  *(undefined4 *)((int)puVar16 + -4) = 0x69765;
  count_penalized();
  *(undefined4 *)((int)puVar16 + -4) = 0x6976f;
  sub_5b826(0xdf614);
  *(undefined4 *)((int)puVar16 + -4) = 0x69779;
  apply_line_change(0xdf614);
  *(undefined4 *)((int)puVar16 + -4) = 0x69783;
  dress_line(0xdf614);
  word_df644 = extraout_DX_00;
  word_df646 = extraout_DX_00;
  dword_df648._0_2_ = extraout_DX_00;
  *(undefined4 *)((int)puVar16 + -4) = 0x697a4;
  sub_5b826(0xdf714);
  *(undefined4 *)((int)puVar16 + -4) = 0x697ae;
  apply_line_change(0xdf714);
  *(undefined4 *)((int)puVar16 + -4) = 0x697b8;
  dress_line(0xdf714);
  word_df742._2_2_ = extraout_DX_00;
  word_df746 = extraout_DX_00;
  dword_df748._0_2_ = extraout_DX_00;
  *(undefined4 *)((int)puVar16 + -4) = 0x697d2;
  reset_players_for_faceoff();
  puVar14 = &entities;
  iVar21 = 0;
  do {
    if ((*(byte *)(puVar14 + 0x11) & 0x80) == 0) {
      iVar20 = 6;
    }
    else {
      iVar20 = 0;
    }
    iVar9 = puVar14[6];
    *(undefined4 *)((int)puVar16 + -4) = 0x697fd;
    uVar24 = randomrange(0x14);
    *(int *)((int)puVar16 + 0x100) = (int)uVar24 + -10;
    *(short *)((int)puVar14 + 2) =
         *(short *)(&unk_cd9a0 + (int)((ulonglong)uVar24 >> 0x20) * 4) +
         (short)*(undefined4 *)((int)puVar16 + 0x100);
    sVar6 = *(short *)((int)puVar14 + 0x1a);
    if (sVar6 == 0) {
      uVar7 = 4;
    }
    else {
      uVar7 = 0x14;
    }
    *(undefined4 *)((int)puVar16 + -4) = 0x69845;
    sVar6 = randomrange(uVar7,sVar6 == 0);
    if (sVar6 == extraout_EDX) {
      sVar6 = 10;
    }
    else {
      sVar6 = 4;
    }
    *(short *)((int)puVar14 + 6) =
         sVar6 + (short)((uint)*(undefined4 *)(&unk_cd9a0 + (iVar20 + (iVar9 >> 0x10)) * 4) >> 0x10)
    ;
    *(undefined2 *)((int)puVar14 + 0xe) = 0;
    *(undefined2 *)(puVar14 + 3) = *(undefined2 *)((int)puVar14 + 0xe);
    sVar6 = *p_puck_y;
    sVar1 = *(short *)((int)puVar14 + 6);
    sVar2 = *p_puck_x;
    sVar3 = *(short *)((int)puVar14 + 2);
    *(undefined4 *)((int)puVar16 + -4) = 0x69895;
    uVar7 = direction8((int)(short)(sVar2 - sVar3),(int)(short)(sVar6 - sVar1));
    *(undefined2 *)((int)puVar14 + 0x36) = uVar7;
    iVar21 = iVar21 + 1;
    puVar14 = puVar14 + 0x20;
  } while (iVar21 < 0xc);
  word_dff44 = 0x78;
  *(undefined4 *)((int)puVar16 + -4) = 0x698bc;
  sVar6 = randomrange(0x14);
  puck._2_2_ = sVar6 + -10;
  *(undefined4 *)((int)puVar16 + -4) = 0x698cf;
  sVar6 = randomrange(0x14);
  dword_dff20._2_2_ = sVar6 + -10;
  dword_dff24._2_2_ = 0;
  *(undefined4 *)((int)puVar16 + -4) = 0x698eb;
  sVar6 = randomrange(2000);
  word_dff28 = sVar6 + -1000;
  *(undefined4 *)((int)puVar16 + -4) = 0x69901;
  sVar6 = randomrange(2000);
  word_dff2a = sVar6 + -1000;
  _word_dff2e = 0x18a;
  word_dff70 = 0;
  *(undefined4 *)((int)puVar16 + -4) = 0x6992c;
  set_state(&puck,0x18);
  dword_dffac._2_2_ = 0x189;
  word_dfff0 = 0;
  *(undefined4 *)((int)puVar16 + -4) = 0x6994d;
  set_state(&dword_dff9c,0x19);
  referee._2_2_ = 0xff88;
  DAT_000e0020._2_2_ = 0;
  word_e0052 = 2;
  word_e002a = 0;
  word_e0028 = 0;
  *(undefined4 *)((int)puVar16 + -4) = 0x69986;
  set_state(&referee,0x1f);
  puVar17 = (undefined *)((int)puVar16 + -4);
  *(undefined4 *)((int)puVar16 + -4) = 0x6998b;
  sim_tick();
  puVar18 = (undefined4 *)(puVar17 + -4);
  *(undefined4 *)(puVar17 + -4) = 0x69990;
  sim_tick();
  *(undefined4 *)((int)puVar18 + -4) = 0x69995;
  sort_draw_order2();
  iVar21 = 0;
  dword_d8c78._0_2_ = 0;
  dword_d8c78._2_2_ = 0;
  control_steps_left = 0;
  puVar4 = (undefined *)CONCAT22(p_puck_carrier._2_2_,(undefined2)p_puck_carrier);
  *puVar4 = 0xff;
  _input_enabled = 0;
  *(undefined4 *)((int)puVar18 + -4) = 0x699b8;
  flush_key_events(puVar4,0);
  word_cbec4 = 2;
  period_over = extraout_DX_01;
  game_over = extraout_DX_01;
  *(undefined4 *)((int)puVar18 + -4) = 0x699d4;
  ticks_elapsed();
  _input_enabled = 1;
  dword_c5130 = 1;
  pause_requested = 0;
  while (period_over == 0) {
    *(undefined4 *)((int)puVar18 + -4) = 0x699fe;
    iVar20 = get_frame_ticks();
    iVar21 = iVar21 + iVar20 * 6;
    iVar20 = iVar21 / 10;
    iVar21 = iVar21 % 10;
    *(undefined4 *)((int)puVar18 + -4) = 0x69a2b;
    run_sim_steps(iVar20);
    dword_d8c7c = (short)camera + 0x20;
    dword_d8c74 = 0xec - (short)camera._2_2_;
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
    *(undefined4 *)((int)puVar18 + -4) = 0x69aa2;
    set_camera_offset(0,0);
    *(undefined4 *)((int)puVar18 + -4) = 0x69aa7;
    begin_frame();
    iVar12 = dword_d8c7c;
    iVar9 = dword_d8c74;
    *(undefined4 *)((int)puVar18 + -4) = 0x69ab7;
    draw_rink(iVar12,iVar9);
    *(undefined4 *)((int)puVar18 + -4) = 0x69af4;
    set_view_rect();
    dword_d8c40 = 0;
    iVar12 = (int)(short)dword_d8c74;
    iVar9 = (int)(short)dword_d8c7c;
    *(undefined4 *)((int)puVar18 + -4) = 0x69b12;
    draw_sprites(iVar9,iVar12);
    iVar13 = (int)_dword_dd6b0;
    iVar9 = (int)_dword_dd6aa;
    iVar12 = (int)word_dd6b2;
    iVar15 = (int)(short)dword_dd6ac;
    *(undefined4 *)((int)puVar18 + -4) = 0x69b47;
    set_camera_offset(-(iVar12 * 8 + iVar15),-(iVar13 * 8 + iVar9));
    *(undefined4 *)((int)puVar18 + -4) = 0x69b4c;
    present_frame();
    if (word_cbec4 != 0) {
      dword_e9a9e = CONCAT22(input_enabled,(undefined2)dword_e9a9e);
      _input_enabled = 0;
      *(undefined **)((int)puVar18 + -4) = &palette_save;
      *(undefined4 *)((int)puVar18 + -8) = 0x100;
      *(undefined4 *)((int)puVar18 + -0xc) = 0;
      *(undefined4 *)((int)puVar18 + -0x10) = 0x69b7a;
      getpalette();
      *(undefined4 *)((int)puVar18 + -4) = 0x69b91;
      fade_palette_to(1,&palette_save,0x10);
      _input_enabled = dword_e9a9e >> 0x10;
    }
    *(undefined4 *)((int)puVar18 + -4) = 0x69ba6;
    update_ambient_audio((int)(short)iVar20);
    dword_dc28c = dword_d8c78 / 0x18;
    iVar20 = dword_d8c78 / 0x18;
    dword_d8c78 = dword_d8c78 % 0x18;
    if ((period_over != 0) &&
       (iVar20 = (int)(CONCAT22(clock_seconds,period_idx) | CONCAT22(clock_sub,clock_seconds)) >>
                 0x10, iVar20 == 0)) {
      iVar20 = (hud_clock_sec + hud_clock_min * 0x3c) * 100 + hud_clock_tenths;
      dword_dc28c = iVar20;
    }
    *(undefined4 *)((int)puVar18 + -4) = 0x69c27;
    draw_clock(iVar20);
    if (word_cbec4 != 0) {
      dword_e9a9e = CONCAT22(input_enabled,(undefined2)dword_e9a9e);
      _input_enabled = 0;
      if (word_cbec4 == 2) {
        *(undefined4 *)((int)puVar18 + -4) = 0x69c52;
        speech_stop();
        *(undefined4 *)((int)puVar18 + -4) = 0x69c5f;
        say_highlight_intro_wrapper
                  (*(undefined4 *)((int)puVar18 + 8),*(undefined4 *)((int)puVar18 + 4));
        *(undefined4 *)((int)puVar18 + -4) = 0x69c70;
        fade_palette_to(0,&unk_df314,0x10);
        word_cbec4 = 0;
        *(undefined4 *)((int)puVar18 + -4) = 0x69c83;
        sVar6 = randomrange(200);
        crowd_noise = CONCAT22(sVar6 + 100,(undefined2)crowd_noise);
        dword_ccc88 = (int)(short)(sVar6 + 100);
      }
      _input_enabled = dword_e9a9e >> 0x10;
    }
    if (pause_requested != 0) break;
    *(undefined4 *)((int)puVar18 + -4) = 0x69cb6;
    read_control_p1();
    if (((dword_e03be._2_1_ & 0x10) != 0) || ((dword_e03be._2_1_ & 0x20) != 0)) break;
    *(undefined4 *)((int)puVar18 + -4) = 0x69ccb;
    read_control_p2();
    if (((dword_e03be._2_1_ & 0x10) != 0) || ((dword_e03be._2_1_ & 0x20) != 0)) break;
  }
  _input_enabled = 0;
  if (dword_cbeca >> 0x10 != -1) {
    *(undefined4 *)((int)puVar18 + -4) = dword_e0244;
    *(undefined4 *)((int)puVar18 + -8) = 0x69d00;
    freemem();
  }
  _word_cbec8 = 0xffff;
  word_cbece = 0xffff;
  dword_cbeca = CONCAT22(0xffff,(undefined2)dword_cbeca);
  dword_c5130 = 0;
  dword_ccc98 = 0;
  *(undefined **)((int)puVar18 + -4) = &palette_save;
  *(undefined4 *)((int)puVar18 + -8) = 0x100;
  *(undefined4 *)((int)puVar18 + -0xc) = 0;
  *(undefined4 *)((int)puVar18 + -0x10) = 0x69d3b;
  getpalette();
  *(undefined4 *)((int)puVar18 + -4) = 0x69d52;
  fade_palette_to(1,&palette_save);
  *(undefined4 *)((int)puVar18 + -4) = 0x69d57;
  fade_ambient_audio();
  crowd_noise = crowd_noise & 0xffff;
  dword_ccc88 = 0;
  if ((sound_enabled == '\0') || ((option_flags & 0x100) == 0)) {
    *(undefined4 *)((int)puVar18 + -4) = 0x69d8f;
    sound_stopall();
  }
  else {
    puVar19 = (undefined4 *)((int)puVar18 + -4);
    puVar18 = (undefined4 *)((int)puVar18 + -4);
    *puVar19 = 0x69d7f;
    sub_8373e();
    do {
      *(undefined4 *)((int)puVar18 + -4) = 0x69d84;
      iVar21 = sub_836e4();
    } while (iVar21 != 0);
  }
  puVar18[-1] = 0x69d94;
  stop_crowd_loop();
  period_over = 0xffff;
  puVar18[-1] = 0x69dac;
  set_video_mode(0x280,0x1e0);
  if (pause_requested == 0) {
    puVar18[-1] = 0x69dbf;
    sub_1baf3(140000);
    puVar18[-1] = 0x69dc4;
    loading_screen();
  }
  game_over = (short)puVar18[0x3e];
  user2_team._2_2_ = (short)puVar18[3];
  _away_team_id = *(short *)((int)puVar18 + 0xe);
  word_df64c = *(undefined2 *)(puVar18 + 4);
  word_df74c = *(undefined2 *)((int)puVar18 + 0x12);
  user1_team = *(undefined2 *)(puVar18 + 5);
  user2_team._0_2_ = *(undefined2 *)((int)puVar18 + 0x16);
  _period_num = (int)*(short *)(puVar18 + 6);
  period_idx._0_1_ = (byte)*(undefined2 *)((int)puVar18 + 0x1a);
  period_idx._1_1_ = (undefined)((ushort)*(undefined2 *)((int)puVar18 + 0x1a) >> 8);
  dword_df648._2_2_ = *(undefined2 *)(puVar18 + 7);
  dword_df748._2_2_ = *(undefined2 *)((int)puVar18 + 0x1e);
  *(int *)*puVar18 = dword_df622 >> 0x10;
  *unaff_ECX = dword_df722 >> 0x10;
  dword_df622 = CONCAT22(*(undefined2 *)(puVar18 + 8),(undefined2)dword_df622);
  dword_df722 = CONCAT22(*(undefined2 *)((int)puVar18 + 0x22),(undefined2)dword_df722);
  iVar21 = 0;
  puVar14 = puVar18 + 9;
  do {
    puVar8 = &unk_df692 + iVar21 * 0x80;
    iVar20 = 0;
    do {
      *puVar8 = *(undefined2 *)puVar14;
      puVar14 = (undefined4 *)((int)puVar14 + 2);
      puVar8 = puVar8 + 1;
      iVar20 = iVar20 + 1;
    } while (iVar20 < 0x1c);
    iVar21 = iVar21 + 1;
  } while (iVar21 < 2);
  option_flags = puVar18[0x3d];
  puVar14 = puVar18 + 0x31;
  puVar22 = &unk_dc200;
  for (iVar21 = 0xc; iVar21 != 0; iVar21 = iVar21 + -1) {
    *puVar22 = *puVar14;
    puVar14 = puVar14 + (uint)bVar23 * -2 + 1;
    puVar22 = puVar22 + (uint)bVar23 * -2 + 1;
  }
  puVar14 = puVar18 + 0x25;
  puVar22 = (undefined4 *)&unk_dabf0;
  for (iVar21 = 0xc; iVar21 != 0; iVar21 = iVar21 + -1) {
    *puVar22 = *puVar14;
    puVar14 = puVar14 + (uint)bVar23 * -2 + 1;
    puVar22 = puVar22 + (uint)bVar23 * -2 + 1;
  }
  puVar18[-1] = 0x69ef0;
  sub_1bbcc(4);
  puVar18[-1] = 0x69ef5;
  sub_5de42();
  game_flags = 1;
  if (((byte)period_idx & 1) != 0) {
    if ((CONCAT11(period_idx._1_1_,(byte)period_idx) == 3) && ((option_flags & 0x200) != 0)) {
      bVar5 = false;
    }
    else {
      bVar5 = true;
    }
    if (bVar5) {
      game_flags = 3;
    }
  }
  _misc_flags = 0;
  _action_flags = 0;
  stop_flags = (undefined2)puVar18[0x3f];
  *(undefined *)CONCAT22(p_puck_carrier._2_2_,(undefined2)p_puck_carrier) = 0xff;
  dword_cbebe._2_2_ = 0xffff;
  camera._0_2_ = 0;
  camera._2_2_ = 0;
  puVar18[-1] = 0x69f91;
  load_team_palettes((int)user2_team._2_2_,(int)_away_team_id,&unk_df314);
  word_cbc54 = 0;
  word_cbc52 = 0;
  word_cbc58 = 0;
  word_cbc56 = 0;
  word_cbc64 = 0xffff;
  word_cbc62 = 0xffff;
  word_cbc6c = 0;
  word_cbc6a = 0;
  word_cbec4 = 1;
  dword_d8c78._0_2_ = 0;
  dword_d8c78._2_2_ = 0;
  whistle_timer = 0;
  ref_phase = 0xffff;
  puVar18[-1] = 0x69ffc;
  set_state(&referee,0x1e);
  puVar18[-1] = 0x6a001;
  clear_infractions();
  stoppage_timer = 0xffff;
  puVar18[-1] = 0x6a00d;
  flush_key_events();
  if (pause_requested == 0) {
    uVar10 = 0;
  }
  else {
    pause_requested = 0;
    uVar10 = 0xffffffff;
  }
  return uVar10;
}


// ================================================================================================
// mark_rink_dirty @ 0x6a033 [__watcall]
// ================================================================================================

void __watcall mark_rink_dirty(uint param_1)

{
  __CHK(4);
  dword_ea058 = dword_ea058 | param_1;
  return;
}


// ================================================================================================
// sub_6a044 @ 0x6a044 [__watcall]
// ================================================================================================

void __watcall sub_6a044(uint param_1)

{
  __CHK(4);
  dword_ea058 = dword_ea058 & ~param_1;
  return;
}


// ================================================================================================
// sub_6a057 @ 0x6a057 [__watcall]
// ================================================================================================

void __watcall sub_6a057(uint param_1)

{
  __CHK(4);
  dword_ea058 = dword_ea058 ^ param_1;
  return;
}


// ================================================================================================
// sub_6a068 @ 0x6a068 [__watcall]
// ================================================================================================

undefined4 __watcall sub_6a068(void)

{
  __CHK(4);
  return dword_ea058;
}


// ================================================================================================
// sub_6a078 @ 0x6a078 [__watcall]
// ================================================================================================

void __watcall sub_6a078(int param_1,uint unaff_EDX)

{
  uint *puVar1;
  
  __CHK(8);
  puVar1 = (uint *)(param_1 * 4 + dword_ea09c);
  *puVar1 = *puVar1 | unaff_EDX;
  return;
}


// ================================================================================================
// sub_6a092 @ 0x6a092 [__watcall]
// ================================================================================================

void __watcall sub_6a092(int param_1,uint unaff_EDX)

{
  uint *puVar1;
  
  __CHK(8);
  puVar1 = (uint *)(dword_ea09c + param_1 * 4);
  *puVar1 = *puVar1 & ~unaff_EDX;
  return;
}


// ================================================================================================
// sub_6a0aa @ 0x6a0aa [__watcall]
// ================================================================================================

void __watcall sub_6a0aa(int param_1,uint unaff_EDX)

{
  uint *puVar1;
  
  __CHK(8);
  puVar1 = (uint *)(param_1 * 4 + dword_ea09c);
  *puVar1 = *puVar1 ^ unaff_EDX;
  return;
}


// ================================================================================================
// sub_6a0c4 @ 0x6a0c4 [__watcall]
// ================================================================================================

undefined8 __watcall sub_6a0c4(int param_1,undefined4 unaff_EDX)

{
  __CHK(8);
  return CONCAT44(unaff_EDX,*(undefined4 *)(param_1 * 4 + dword_ea09c));
}


// ================================================================================================
// sub_6a0de @ 0x6a0de [__watcall]
// ================================================================================================

undefined8 __watcall sub_6a0de(int param_1,undefined4 unaff_EDX)

{
  __CHK(8);
  return CONCAT44(unaff_EDX,param_1 * 0x10 + dword_ea074);
}


// ================================================================================================
// sub_6a0f6 @ 0x6a0f6 [__watcall]
// ================================================================================================

void __watcall sub_6a0f6(undefined4 param_1)

{
  __CHK(4);
  dword_ea0ac = param_1;
  return;
}


// ================================================================================================
// sub_6a106 @ 0x6a106 [__watcall]
// ================================================================================================

void __watcall sub_6a106(void)

{
  __CHK(0x24);
  if (dword_ea0ac == (undefined4 *)0x0) {
    fatalerror(aZMHiddenWindowNoHiddenWi);
  }
  setscreen(dword_ea0ac);
  setclip(0,*dword_ea0ac,0,dword_ea0ac[1]);
  return;
}


// ================================================================================================
// sub_6a156 @ 0x6a156 [__watcall]
// ================================================================================================

void __watcall sub_6a156(undefined4 param_1)

{
  __CHK(4);
  dword_ea0b0 = param_1;
  return;
}


// ================================================================================================
// sub_6a166 @ 0x6a166 [__watcall]
// ================================================================================================

void __watcall sub_6a166(void)

{
  __CHK(0x24);
  if (dword_ea0b0 == (undefined4 *)0x0) {
    fatalerror(aZMBackgroundWindowNoBack);
  }
  setscreen(dword_ea0b0);
  setclip(0,*dword_ea0b0,0,dword_ea0b0[1]);
  return;
}


// ================================================================================================
// sub_6a1a0 @ 0x6a1a0 [__watcall]
// ================================================================================================

void __watcall sub_6a1a0(int *param_1)

{
  __CHK(0x24);
  setclip(*param_1 + dword_ea0b8,param_1[1] + dword_ea0b8,param_1[2] + dword_ea0bc,
          param_1[3] + dword_ea0bc);
  return;
}


// ================================================================================================
// sub_6a1d6 @ 0x6a1d6 [__watcall]
// ================================================================================================

void __watcall sub_6a1d6(int *param_1)

{
  __CHK(0x28);
  setclip(*param_1 + dword_ea0b8,param_1[1] + dword_ea0b8,param_1[2] + dword_ea0bc,
          param_1[3] + dword_ea0bc);
  drawshape(*(undefined4 *)(dword_ea0ac + 0x2c),dword_ea0b8,dword_ea0bc);
  return;
}


// ================================================================================================
// sub_6a234 @ 0x6a234 [__watcall]
// ================================================================================================

void __watcall
sub_6a234(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  __CHK(0x20);
  setclip(0,0x140,0,0xa8,unaff_EDX,unaff_ECX,unaff_EBX);
  drawshape(*(undefined4 *)(dword_ea0ac + 0x2c),dword_ea0b8,dword_ea0bc);
  return;
}


// ================================================================================================
// sub_6a27a @ 0x6a27a [__watcall]
// ================================================================================================

void __watcall sub_6a27a(void)

{
  __CHK(8);
  dword_ea054[1] = dword_ea054[1] + 2;
  *dword_ea054 = (*dword_ea054 >> 2) << 2;
  dword_ea054[1] = (dword_ea054[1] + -1 >> 2) * 4 + 4;
  dword_ea054[3] = dword_ea054[3] + 1;
  return;
}


// ================================================================================================
// sub_6a2bc @ 0x6a2bc [__watcall]
// ================================================================================================

void __watcall sub_6a2bc(void)

{
  __CHK(4);
  return;
}


// ================================================================================================
// sub_6a2c7 @ 0x6a2c7 [__watcall]
// ================================================================================================

void __watcall
sub_6a2c7(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX,
         undefined4 param_5)

{
  __CHK(0x28);
  sub_b4fac(param_1,unaff_EDX,param_1,unaff_ECX,param_5,unaff_ECX);
  sub_b4fac(param_1,unaff_ECX,unaff_EBX,unaff_ECX,param_5);
  sub_b4fac(unaff_EBX,unaff_ECX,unaff_EBX,unaff_EDX,param_5);
  sub_b4fac(unaff_EBX,unaff_EDX,param_1,unaff_EDX,param_5);
  return;
}


// ================================================================================================
// sub_6a335 @ 0x6a335 [__watcall]
// ================================================================================================

void __watcall sub_6a335(int *param_1,undefined4 unaff_EDX)

{
  __CHK(0x14);
  sub_6a2c7(*param_1 + dword_ea0b8,param_1[2] + dword_ea0bc,param_1[1] + dword_ea0b8 + -1,
            param_1[3] + dword_ea0bc + -1,unaff_EDX);
  return;
}


// ================================================================================================
// sub_6a373 @ 0x6a373 [__watcall]
// ================================================================================================

void __watcall sub_6a373(undefined4 *param_1)

{
  __CHK(0x2c);
  setclip(*param_1,param_1[1],param_1[2],param_1[3]);
  drawshape(*(undefined4 *)(dword_ea0b0 + 0x2c),dword_ea0b8,dword_ea0bc);
  return;
}


// ================================================================================================
// sub_6a3c0 @ 0x6a3c0 [__watcall]
// ================================================================================================

void __watcall sub_6a3c0(void)

{
  __CHK(0xc);
  if (dword_ea098 == 0) {
    dword_ea074 = dword_ea084;
    dword_ea09c = dword_ea0a0;
    dword_ea094 = dword_ea080;
    dword_ea08c = dword_ea0a4;
  }
  else {
    dword_ea074 = dword_ea080;
    dword_ea09c = dword_ea0a4;
    dword_ea094 = dword_ea084;
    dword_ea08c = dword_ea0a0;
  }
  memset(dword_ea09c,0,dword_ea0b4 * 2);
  return;
}


// ================================================================================================
// sub_6a439 @ 0x6a439 [__watcall]
// ================================================================================================

void __watcall sub_6a439(void)

{
  __CHK(0x10);
  if (dword_ea07c != 0) {
    *(undefined4 *)(dword_ea090 + dword_ea064 * 4) = dword_ea070;
    dword_ea07c = 0;
    dword_ea070 = dword_ea06c;
  }
  dword_ea064 = 0xffffffff;
  dword_ea06c = 0xffffffff;
  return;
}


// ================================================================================================
// sub_6a48e @ 0x6a48e [__watcall]
// ================================================================================================

longlong __watcall sub_6a48e(int *param_1,uint unaff_EDX)

{
  __CHK(0xc);
  if (((dword_ea068[3] <= param_1[3]) && (dword_ea068[1] <= param_1[1])) &&
     (*param_1 <= *dword_ea068)) {
    if (dword_ea068[2] < param_1[2]) {
      return CONCAT44(unaff_EDX,2);
    }
    return CONCAT44(unaff_EDX,1);
  }
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// sub_6a4d3 @ 0x6a4d3 [__watcall]
// ================================================================================================

undefined8 __watcall sub_6a4d3(int *param_1,undefined4 unaff_EDX)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  
  __CHK(0x14);
  if (param_1[3] == dword_ea068[2]) {
    iVar4 = *param_1 - *dword_ea068;
    iVar1 = iVar4;
    if (iVar4 < 0) {
      iVar1 = -iVar4;
    }
    if (iVar1 < 0x11) {
      iVar2 = param_1[1] - dword_ea068[1];
      iVar1 = iVar2;
      if (iVar2 < 0) {
        iVar1 = -iVar2;
      }
      if (iVar1 < 0x11) {
        param_1[3] = dword_ea068[3];
LAB_0006a535:
        if (iVar2 < 0) {
          param_1[1] = param_1[1] - iVar2;
        }
        if (0 < iVar4) {
          *param_1 = *param_1 - iVar4;
        }
        uVar3 = 1;
        goto LAB_0006a59e;
      }
    }
  }
  else if (param_1[2] == dword_ea068[3]) {
    iVar4 = *param_1 - *dword_ea068;
    iVar1 = iVar4;
    if (iVar4 < 0) {
      iVar1 = -iVar4;
    }
    if (iVar1 < 0x11) {
      iVar2 = param_1[1] - dword_ea068[1];
      iVar1 = iVar2;
      if (iVar2 < 0) {
        iVar1 = -iVar2;
      }
      if (iVar1 < 0x11) {
        param_1[2] = dword_ea068[2];
        goto LAB_0006a535;
      }
    }
  }
  else if (dword_ea068[3] < param_1[2]) {
    uVar3 = 2;
    goto LAB_0006a59e;
  }
  uVar3 = 0;
LAB_0006a59e:
  return CONCAT44(unaff_EDX,uVar3);
}


// ================================================================================================
// sub_6a5a5 @ 0x6a5a5 [__watcall]
// ================================================================================================

longlong __watcall sub_6a5a5(int *param_1,uint unaff_EDX)

{
  __CHK(0xc);
  if (((dword_ea068[2] < param_1[3]) && (*dword_ea068 < param_1[1])) && (*param_1 < dword_ea068[1]))
  {
    if (dword_ea068[3] <= param_1[2]) {
      return CONCAT44(unaff_EDX,2);
    }
    return CONCAT44(unaff_EDX,1);
  }
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// sub_6a5ea @ 0x6a5ea [__watcall]
// ================================================================================================

void __watcall sub_6a5ea(void)

{
  __CHK(0x10);
  if (*dword_ea068 < dword_ea034) {
    *dword_ea068 = dword_ea034;
  }
  if (dword_ea068[2] < dword_ea03c) {
    dword_ea068[2] = dword_ea03c;
  }
  if (dword_ea038 < dword_ea068[1]) {
    dword_ea068[1] = dword_ea038;
  }
  if (dword_ea040 < dword_ea068[3]) {
    dword_ea068[3] = dword_ea040;
  }
  return;
}


// ================================================================================================
// sub_6a649 @ 0x6a649 [__watcall]
// ================================================================================================

void __watcall sub_6a649(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  __CHK(0x14);
  iVar1 = dword_ea06c;
  iVar3 = -1;
  while ((iVar2 = iVar1, iVar2 != -1 && (iVar2 != param_1))) {
    iVar3 = iVar2;
    iVar1 = *(int *)(dword_ea090 + iVar2 * 4);
  }
  if (iVar3 == -1) {
    dword_ea06c = *(int *)(dword_ea090 + param_1 * 4);
  }
  else {
    *(undefined4 *)(dword_ea090 + iVar3 * 4) = *(undefined4 *)(dword_ea090 + iVar2 * 4);
  }
  if (param_1 == dword_ea064) {
    dword_ea064 = iVar3;
  }
  *(int *)(param_1 * 4 + dword_ea090) = dword_ea070;
  dword_ea070 = param_1;
  dword_ea07c = dword_ea07c + -1;
  return;
}


// ================================================================================================
// sub_6a6cc @ 0x6a6cc [__watcall]
// ================================================================================================

void __watcall sub_6a6cc(void)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  int iVar5;
  int iVar6;
  int *piVar7;
  int iVar8;
  undefined4 *puVar9;
  
  __CHK(0x18);
  iVar5 = dword_ea070;
  iVar2 = dword_ea06c;
  iVar6 = -1;
  while ((iVar8 = iVar2, iVar8 != -1 &&
         (*(int *)(dword_ea060 + iVar8 * 0x10 + 8) <= (int)dword_ea068[2]))) {
    iVar2 = *(int *)(dword_ea090 + iVar8 * 4);
    iVar6 = iVar8;
  }
  iVar8 = dword_ea070 * 4;
  piVar7 = (int *)(dword_ea090 + iVar8);
  iVar2 = *piVar7;
  if (iVar6 == -1) {
    dword_ea070 = iVar2;
    *piVar7 = dword_ea06c;
    dword_ea06c = iVar5;
  }
  else {
    piVar7 = (int *)(iVar6 * 4 + dword_ea090);
    iVar3 = *piVar7;
    *piVar7 = dword_ea070;
    dword_ea070 = iVar2;
    *(int *)(dword_ea090 + iVar8) = iVar3;
  }
  if (iVar6 == dword_ea064) {
    dword_ea064 = iVar5;
    *(undefined4 *)(dword_ea090 + iVar5 * 4) = 0xffffffff;
  }
  puVar4 = dword_ea068;
  puVar9 = (undefined4 *)(dword_ea060 + iVar5 * 0x10);
  puVar1 = dword_ea068 + 1;
  *puVar9 = *dword_ea068;
  puVar9[1] = *puVar1;
  puVar9[2] = puVar4[2];
  puVar9[3] = puVar4[3];
  dword_ea07c = dword_ea07c + 1;
  return;
}


// ================================================================================================
// sub_6a791 @ 0x6a791 [__watcall]
// ================================================================================================

void __watcall sub_6a791(int param_1)

{
  bool bVar1;
  bool bVar2;
  int *piVar3;
  int iStackY_48;
  int local_44;
  int iStackY_40;
  int local_3c;
  int iStackY_38;
  int iStackY_34;
  int local_30;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  int iStackY_1c;
  
  __CHK(0x4c);
  piVar3 = (int *)(param_1 * 0x10 + dword_ea060);
  local_20 = piVar3[2];
  iStackY_1c = piVar3[3];
  if (piVar3[2] < dword_ea068[2]) {
    iStackY_38 = *piVar3;
    iStackY_34 = piVar3[1];
    local_30 = piVar3[2];
    local_2c = dword_ea068[2];
    local_20 = local_2c;
LAB_0006a7e1:
    bVar1 = true;
  }
  else {
    if (dword_ea068[2] < piVar3[2]) {
      iStackY_38 = *dword_ea068;
      iStackY_34 = dword_ea068[1];
      local_30 = dword_ea068[2];
      local_2c = piVar3[2];
      goto LAB_0006a7e1;
    }
    bVar1 = false;
  }
  if (dword_ea068[3] < piVar3[3]) {
    iStackY_48 = *piVar3;
    local_44 = piVar3[1];
    local_3c = piVar3[3];
    iStackY_40 = dword_ea068[3];
    iStackY_1c = iStackY_40;
  }
  else {
    if (dword_ea068[3] <= piVar3[3]) {
      bVar2 = false;
      goto LAB_0006a842;
    }
    iStackY_48 = *dword_ea068;
    local_44 = dword_ea068[1];
    local_3c = dword_ea068[3];
    iStackY_40 = piVar3[3];
  }
  bVar2 = true;
LAB_0006a842:
  local_28 = *piVar3;
  if (*dword_ea068 < local_28) {
    local_28 = *dword_ea068;
  }
  local_24 = piVar3[1];
  if (local_24 < dword_ea068[1]) {
    local_24 = dword_ea068[1];
  }
  sub_6a649(param_1);
  if (bVar1) {
    sub_6a8b1(&iStackY_38,1);
  }
  sub_6a8b1(&local_28,1);
  if (bVar2) {
    sub_6a8b1(&iStackY_48,1);
  }
  return;
}


