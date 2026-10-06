// Decompiled by Ghidra from hockey.elf (via ledisasm ELF export)
// This is machine generated pseudo-C meant as a reference for porting, it does not compile as is.
#include "prototypes.h"

// ================================================================================================
// time_announcements @ 0x5a77c [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall time_announcements(void)

{
  char cVar1;
  char cVar2;
  short sVar3;
  short extraout_DX;
  short extraout_DX_00;
  
  __CHK(0x10);
  cVar1 = byte_df6e9;
  if ((game_flags & 0x10) != 0) {
    return;
  }
  sVar3 = dword_df622._2_2_ - dword_df722._2_2_;
  if ((_period_num == 2) && (clock_seconds < 0x259)) {
    adjust_strategy(0);
    cVar2 = byte_df7e9;
    if (cVar1 != byte_df6e9) {
      byte_df6e8 = byte_df6e8 | 0x40;
    }
    adjust_strategy(1);
    if (cVar2 != byte_df7e9) {
      byte_df7e8 = byte_df7e8 | 0x40;
    }
    if (clock_seconds != 600) {
      return;
    }
    if (extraout_DX < -1) {
      if (byte_df6e6 < 4) {
        byte_df6e6 = byte_df6e6 + 1;
      }
      if (1 < byte_df6e7) {
        byte_df6e7 = byte_df6e7 - 1;
      }
    }
    if (extraout_DX < 2) {
      return;
    }
    if (byte_df7e6 < 4) {
      byte_df7e6 = byte_df7e6 + 1;
    }
    if (byte_df7e7 < 2) {
      return;
    }
    byte_df7e7 = byte_df7e7 - 1;
    return;
  }
  if (_period_num != 3) {
    return;
  }
  if (((clock_seconds < 0x3d) && (0x7fffffff < (uint)(int)sVar3)) ||
     ((clock_seconds < 0x79 && (sVar3 < -1)))) {
    byte_df6e9 = '\x06';
LAB_0005a8f3:
    dword_df6ea = 0xb33;
    byte_df6e8 = byte_df6e8 | 1;
    byte_df6e6 = 4;
    byte_df6e7 = 1;
  }
  else {
    if (((clock_seconds < 0xb5) && (0x7fffffff < (uint)(int)sVar3)) ||
       ((clock_seconds < 0x12d && (sVar3 < -1)))) {
      byte_df6e9 = '\a';
      goto LAB_0005a8f3;
    }
    if (clock_seconds < 0x259) {
      if (sVar3 < -1) {
        byte_df6e9 = '\n';
        goto LAB_0005a8f3;
      }
      if (sVar3 < 3) {
        dword_df6ea = 0xd9a;
      }
      else {
        dword_df6ea = 0xccc;
      }
      byte_df6e8 = byte_df6e8 & 0xfe;
      byte_df6e9 = '\x03';
      byte_df6e6 = 3;
      byte_df6e7 = 2;
    }
    else {
      adjust_strategy(0);
      sVar3 = extraout_DX_00;
    }
  }
  cVar2 = byte_df7e9;
  if (cVar1 != byte_df6e9) {
    byte_df6e8 = byte_df6e8 | 0x40;
  }
  if (((clock_seconds < 0x3d) && (0 < sVar3)) || ((clock_seconds < 0x79 && (1 < sVar3)))) {
    byte_df7e9 = '\x06';
  }
  else if (((clock_seconds < 0xb5) && (1 < sVar3)) || ((clock_seconds < 0x12d && (1 < sVar3)))) {
    byte_df7e9 = '\a';
  }
  else {
    if (600 < clock_seconds) {
      adjust_strategy(1);
      goto LAB_0005aa9b;
    }
    if (sVar3 < 2) {
      if (sVar3 < -2) {
        dword_df7ea = 0xccc;
        byte_df7e9 = '\t';
      }
      else {
        dword_df7ea = 0xd9a;
        byte_df7e9 = '\b';
      }
      byte_df7e8 = byte_df7e8 | 1;
      byte_df7e6 = 3;
      byte_df7e7 = 2;
      goto LAB_0005aa9b;
    }
    byte_df7e9 = '\n';
  }
  dword_df7ea = 0xb33;
  byte_df7e8 = byte_df7e8 | 1;
  byte_df7e6 = 4;
  byte_df7e7 = 1;
LAB_0005aa9b:
  if (cVar2 != byte_df7e9) {
    byte_df7e8 = byte_df7e8 | 0x40;
  }
  return;
}


// ================================================================================================
// goal_disallowed_check @ 0x5aaae [__watcall]
// ================================================================================================

longlong __watcall goal_disallowed_check(undefined4 param_1,uint unaff_EDX)

{
  bool bVar1;
  uint uVar2;
  undefined4 *puVar3;
  int iVar4;
  
  __CHK(8);
  if (((game_flags & 8) != 0) &&
     (bVar1 = ((game_flags & 2) != 0) != *p_puck_y < 0, uVar2 = (uint)bVar1,
     last_touch_slot < 6 != bVar1)) {
    if (uVar2 != 0) {
      uVar2 = 6;
    }
    puVar3 = &entities + uVar2 * 0x20;
    iVar4 = 0;
    do {
      if ((-1 < *(short *)((int)puVar3 + 0x1a)) && ((*(byte *)((int)puVar3 + 0x45) & 0x10) != 0)) {
        return CONCAT44(unaff_EDX,1);
      }
      iVar4 = iVar4 + 1;
      puVar3 = puVar3 + 0x20;
    } while (iVar4 < 6);
  }
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// score_goal @ 0x5ab36 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall score_goal(undefined4 *param_1)

{
  short *psVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  ushort uVar5;
  short sVar6;
  bool bVar7;
  undefined4 uVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  ushort uStackY_1e;
  
  iVar9 = (uint)uStackY_1e << 0x10;
  __CHK(0x24);
  bVar7 = dword_dff20._2_2_ < 0 != ((game_flags & 2) != 0);
  if (bVar7) {
    iVar11 = 0xdf714;
    iVar10 = 0xdf614;
  }
  else {
    iVar11 = 0xdf614;
    iVar10 = 0xdf714;
  }
  if ((((game_flags & 1) == 0) && (iVar3 = goal_disallowed_check(), iVar3 == 0)) &&
     ((*(byte *)(iVar11 + 0x44) & 0x10) == 0)) {
    if ((penalty_shot_active == 0) ||
       ((int)(uint)CONCAT12(bVar7,uStackY_1e) >> 0x10 == penalty_shot_team)) {
      *(short *)(iVar11 + 0x10) = *(short *)(iVar11 + 0x10) + 1;
      if ((int)(uint)CONCAT12(bVar7,uStackY_1e) >> 0x10 != (uint)(last_touch_slot < 6)) {
        stop_flags._0_1_ = (byte)stop_flags | 0x10;
        _last_shooter = last_touch_slot;
      }
      shot_landed();
      play_sfx(0x9c);
      hold_camera();
      if (bVar7) {
        if (crowd_noise._2_2_ < 800) {
          crowd_noise._2_2_ = 800;
        }
      }
      else {
        crowd_noise._2_2_ = crowd_noise._2_2_ + 800;
        if (2000 < crowd_noise._2_2_) {
          crowd_noise._2_2_ = 2000;
        }
        if (crowd_noise._2_2_ < 0x708) {
          crowd_noise._2_2_ = 0x708;
        }
      }
      play_crowd_chant((int)(uint)CONCAT12(bVar7,uStackY_1e) >> 0x10);
      if (!bVar7) {
        if (((option_flags._1_1_ & 1) == 0) || (sound_enabled == '\0')) {
          bVar2 = true;
        }
        else {
          bVar2 = false;
        }
        if (bVar2) {
          play_speech(3);
        }
      }
      if (bVar7) {
        excitement._2_2_ = excitement._2_2_ + 10;
      }
      else {
        excitement._2_2_ = excitement._2_2_ + 0x1e;
      }
      if (*(short *)(iVar11 + 0x36) < *(short *)(iVar10 + 0x36)) {
        _word_e9ab0 = 2;
      }
      else if (*(short *)(iVar10 + 0x36) < *(short *)(iVar11 + 0x36)) {
        _word_e9ab0 = 4;
      }
      else {
        _word_e9ab0 = 1;
      }
      if (*(short *)(iVar10 + 0x38) < 0) {
        _word_e9ab0 = _word_e9ab0 | 8;
      }
      if ((game_flags & 0x10) == 0) {
        uVar5 = *(ushort *)(iVar11 + 0x30) & 0xff;
        if (uVar5 < 0x19) {
          psVar1 = (short *)(*(int *)(iVar11 + 0xe6) + (short)uVar5 * 0x10);
          *psVar1 = *psVar1 + 1;
        }
        if (*(short *)(iVar10 + 0x36) < *(short *)(iVar11 + 0x36)) {
          psVar1 = (short *)(*(int *)(iVar11 + 0xe6) + 8 + (short)uVar5 * 0x10);
          *psVar1 = *psVar1 + 1;
        }
        else if (*(short *)(iVar11 + 0x36) < *(short *)(iVar10 + 0x36)) {
          psVar1 = (short *)((short)uVar5 * 0x10 + 10 + *(int *)(iVar11 + 0xe6));
          *psVar1 = *psVar1 + 1;
        }
        if (*(short *)(iVar10 + 0x38) < 0) {
          psVar1 = (short *)(*(int *)(iVar11 + 0xe6) + 0xc + (short)uVar5 * 0x10);
          *psVar1 = *psVar1 + 1;
        }
        if (penalty_shot_phase == 0) {
          if (breakaway_flag != 0) {
            *(short *)(iVar11 + 0x1e) = *(short *)(iVar11 + 0x1e) + 1;
          }
        }
        else {
          *(short *)(iVar11 + 0x22) = *(short *)(iVar11 + 0x22) + 1;
        }
        if ((one_timer_pending & 1 << bVar7) != 0) {
          *(short *)(iVar11 + 0x1a) = *(short *)(iVar11 + 0x1a) + 1;
        }
        sVar6 = *(short *)(iVar11 + 0x32);
        if (-1 < sVar6) {
          if (sVar6 < 0x19) {
            psVar1 = (short *)(*(int *)(iVar11 + 0xe6) + 2 + sVar6 * 0x10);
            *psVar1 = *psVar1 + 1;
          }
          sVar6 = *(short *)(iVar11 + 0x34);
          if ((-1 < sVar6) && (sVar6 < 0x19)) {
            psVar1 = (short *)(*(int *)(iVar11 + 0xe6) + 2 + sVar6 * 0x10);
            *psVar1 = *psVar1 + 1;
          }
        }
        if (((-1 < *(short *)(iVar10 + 0x38)) &&
            (sVar6 = *(byte *)(*(int *)(iVar10 + 0xda) + 0x24 + (*(int *)(iVar10 + 0x36) >> 0x10)) -
                     0x19, -1 < sVar6)) && (sVar6 < 3)) {
          psVar1 = (short *)(*(int *)(iVar10 + 0xea) + 4 + sVar6 * 6);
          *psVar1 = *psVar1 + 1;
        }
        if (penalty_shot_active == 0) {
          if (*(short *)(iVar11 + 0x36) <= *(short *)(iVar10 + 0x36)) {
            iVar3 = *(int *)(iVar11 + 0xf6);
            iVar4 = *(int *)(iVar10 + 0xf6);
            for (sVar6 = 0; sVar6 < 6; sVar6 = sVar6 + 1) {
              if (0 < *(short *)(iVar3 + 0x1a)) {
                iVar9 = (*(int *)(iVar3 + 0x44) >> 0x18) * 0x10;
                psVar1 = (short *)(*(int *)(iVar11 + 0xe6) + iVar9 + 6);
                *psVar1 = *psVar1 + 1;
              }
              if (0 < *(short *)(iVar4 + 0x1a)) {
                iVar9 = (*(int *)(iVar4 + 0x44) >> 0x18) * 0x10;
                psVar1 = (short *)(*(int *)(iVar10 + 0xe6) + iVar9 + 6);
                *psVar1 = *psVar1 + -1;
              }
              iVar3 = iVar3 + 0x80;
              iVar4 = iVar4 + 0x80;
            }
          }
          uStackY_1e = (ushort)((uint)iVar9 >> 0x10);
          goal_ends_penalty((int)(uint)CONCAT12(bVar7,uStackY_1e) >> 0x10);
        }
        else {
          last_touch_y = 0;
          last_touch_x = 0;
          faceoff_spot._2_2_ = 0;
          faceoff_spot._0_2_ = 0;
        }
        uStackY_1e = (ushort)((uint)iVar9 >> 0x10);
        breakaway_flag = 0;
        one_timer_pending = 0;
      }
      draw_score_digits((int)(uint)CONCAT12(bVar7,uStackY_1e) >> 0x10,*(int *)(iVar11 + 0xe) >> 0x10
                       );
      iVar9 = *(int *)(iVar11 + 0xf6);
      sVar6 = 6;
      do {
        if ((0 < *(short *)(iVar9 + 0x1a)) && ((*(byte *)(iVar9 + 0x45) & 1) == 0)) {
          *(byte *)(iVar9 + 0x44) = *(byte *)(iVar9 + 0x44) & 0xfb;
          if (*(char *)(iVar9 + 0x1e + (*(int *)(iVar9 + 0x1a) >> 0x10)) == '-') {
            DAT_000dff4a = 0;
            set_state_reset(iVar9,0x28);
            set_state_reset(iVar9,7);
            uVar8 = 9;
          }
          else {
            uVar8 = 7;
          }
          set_state_reset(iVar9,uVar8);
        }
        iVar9 = iVar9 + 0x80;
        sVar6 = sVar6 + -1;
      } while (sVar6 != 0);
      puck_in_net = 0;
      if (puck._2_2_ < 0) {
        puck._2_2_ = -6;
      }
      else {
        puck._2_2_ = 6;
      }
      word_dff2a = 0;
      if (dword_dff20._2_2_ < 0) {
        dword_dff20._2_2_ = -0xf0;
      }
      else {
        dword_dff20._2_2_ = 0xf0;
      }
      dword_dff2c = 0x600;
      dword_dff24._2_2_ = 0;
      word_df816._1_1_ = 0xff;
      word_df81a._1_1_ = 0xff;
      DAT_000dff60 = DAT_000dff60 | 4;
      word_dff28 = sVar6;
      set_state(&puck,0x1a);
      set_animation(&dword_dff9c,0x7fd);
      queue_infraction(*(undefined4 *)(iVar10 + 0xf6),7);
      if ((game_flags & 0x10) == 0) {
        end_penalty_shot();
        set_state(&referee,0x1f);
        _dword_cc114 = 0;
        _dword_cc110 = 0;
      }
      if ((game_flags & 0x10) == 0) {
        sVar6 = dword_df622._2_2_ - dword_df722._2_2_;
        if (((sVar6 < -3) && (1 < byte_df6e6)) &&
           ((user1_team != 1 && (((short)user2_team != 1 && (((byte)word_df64c & 1) == 0)))))) {
          word_df64c._0_1_ = (byte)word_df64c ^ 1;
        }
        if ((sVar6 < -1) && (1 < byte_df6e6)) {
          byte_df6e6 = byte_df6e6 - 1;
        }
        if ((sVar6 < 1) && (1 < byte_df6e7)) {
          byte_df6e7 = byte_df6e7 - 1;
        }
        if ((((3 < sVar6) && (1 < byte_df7e6)) && (user1_team != 2)) &&
           (((short)user2_team != 2 && (((byte)word_df74c & 1) == 0)))) {
          word_df74c._0_1_ = (byte)word_df74c ^ 1;
        }
        if ((1 < sVar6) && (1 < byte_df7e6)) {
          byte_df7e6 = byte_df7e6 - 1;
        }
        if ((-1 < sVar6) && (1 < byte_df7e7)) {
          byte_df7e7 = byte_df7e7 - 1;
        }
        time_announcements();
      }
    }
    else {
      end_penalty_shot();
    }
  }
  else {
    puck_in_net = 0;
    word_dff28 = 0;
    if (puck._2_2_ < *(short *)((int)param_1 + 2)) {
      sVar6 = -6;
    }
    else {
      sVar6 = 6;
    }
    puck._2_2_ = sVar6 + (short)((uint)*param_1 >> 0x10);
    word_dff2a = 0;
    if (*(short *)((int)param_1 + 6) < 0) {
      sVar6 = -4;
    }
    else {
      sVar6 = 4;
    }
    dword_dff20._2_2_ = sVar6 + (short)((uint)param_1[1] >> 0x10);
    dword_dff2c = 0x600;
    dword_dff24._2_2_ = 0;
    word_df816._1_1_ = 0xff;
    word_df81a._1_1_ = 0xff;
    DAT_000dff60 = DAT_000dff60 | 4;
    if ((game_flags & 1) == 0) {
      set_state(&puck,0x1a);
      if ((*(byte *)(iVar11 + 0x44) & 0x10) != 0) {
        maybe_queue_infraction(*(undefined4 *)(iVar11 + 0xf6),8);
      }
      queue_infraction(*(undefined4 *)(iVar10 + 0xf6),0x1b);
    }
  }
  return;
}


// ================================================================================================
// follow_puck_user_switch @ 0x5b1ce [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall follow_puck_user_switch(short param_1)

{
  __CHK(0x14);
  if (param_1 == _user1_slot) {
    return;
  }
  if (param_1 == user2_slot) {
    return;
  }
  dword_e03be._2_2_ = (5 < param_1) + 1;
  if (user2_slot == last_passer) {
    if ((short)user2_team == dword_e03be._2_2_) goto LAB_0005b23a;
    if (dword_e03be._2_2_ != user1_team) {
      return;
    }
  }
  else if (user1_team != dword_e03be._2_2_) {
    if (dword_e03be._2_2_ != (short)user2_team) {
      return;
    }
LAB_0005b23a:
    if (param_1 == user2_slot) {
      return;
    }
    user2_slot = find_switch_target((int)param_1,(int)user2_slot);
    return;
  }
  if (param_1 != _user1_slot) {
    _user1_slot = find_switch_target((int)param_1,(int)_user1_slot);
  }
  return;
}


// ================================================================================================
// set_default_state @ 0x5b298 [__watcall]
// ================================================================================================

void __watcall
set_default_state(int param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  short sVar1;
  
  __CHK(8);
  sVar1 = *(short *)(param_1 + 0x1a);
  if ((-1 < sVar1) && (sVar1 < 7)) {
    set_state(param_1,*(int *)((int)&controls_blocked + sVar1 + 2) >> 0x18,unaff_EBX,unaff_ECX,
              unaff_EDX);
  }
  return;
}


// ================================================================================================
// put_player_on_ice @ 0x5b2c5 [__watcall]
// ================================================================================================

/* WARNING: Removing unreachable block (ram,0x0005b596) */
/* WARNING: Removing unreachable block (ram,0x0005b6c6) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall put_player_on_ice(int param_1,short unaff_DX)

{
  ushort uVar1;
  int iVar2;
  undefined *puVar3;
  byte bVar4;
  char cVar5;
  short sVar6;
  undefined4 uVar7;
  int iVar8;
  uint uVar9;
  char cStackY_2c;
  undefined2 uStackY_2a;
  undefined local_28;
  undefined uStackY_27;
  char local_24;
  char local_20;
  char local_1c;
  char cStackY_18;
  
  __CHK(0x34);
  local_28 = (undefined)unaff_DX;
  uStackY_27 = (undefined)((ushort)unaff_DX >> 8);
  *(byte *)(param_1 + 0x45) = *(byte *)(param_1 + 0x45) & 0xbf;
  if (*(short *)(param_1 + 0x6a) < 6) {
    iVar2 = 0xdf614;
  }
  else {
    iVar2 = 0xdf714;
  }
  *(undefined *)(param_1 + 0x47) = local_28;
  sVar6 = *(short *)(iVar2 + 0x7e + (CONCAT13(uStackY_27,CONCAT12(local_28,uStackY_2a)) >> 0x10) * 2
                    );
  dword_e03be = CONCAT22(sVar6,(undefined2)dword_e03be);
  if (sVar6 < 0) {
    if (sVar6 != -2) goto LAB_0005b344;
    uVar7 = 9;
  }
  else {
    uVar7 = 10;
  }
  set_state_reset(param_1,uVar7);
  *(byte *)(param_1 + 0x44) = *(byte *)(param_1 + 0x44) & 0xdf;
  *(undefined2 *)(param_1 + 0x38) = 0;
LAB_0005b344:
  iVar8 = CONCAT13(uStackY_27,CONCAT12(local_28,uStackY_2a)) >> 0x10;
  *(undefined2 *)(iVar2 + 0x7e + iVar8 * 2) = 0xffff;
  *(undefined *)(*(int *)(iVar2 + 0xee) + iVar8 * 0x27) = 4;
  iVar8 = *(int *)(iVar2 + 0xf2);
  local_20 = '\0';
  cStackY_18 = '\0';
  local_24 = '\0';
  local_1c = '\0';
  if (*(short *)(param_1 + 0x1a) != 0) {
    if ((stop_flags & 0x20) != 0) {
      if ((ushort)(*(byte *)(param_1 + 0x44) & 0x40) == (stop_flags & 0x40)) {
        if (*(byte *)(iVar8 + 0x2dd) < 7) {
          local_1c = 3 < *(byte *)(iVar8 + 0x2dd);
        }
        else {
          local_1c = '\x02';
        }
      }
      else {
        if (*(byte *)(iVar8 + 0x2dc) < 7) {
          uVar9 = (uint)(3 < *(byte *)(iVar8 + 0x2dc));
        }
        else {
          uVar9 = 2;
        }
        cStackY_2c = (char)(uVar9 - 2);
        uStackY_2a = (undefined2)(uVar9 - 2 >> 0x10);
        local_24 = cStackY_2c;
      }
    }
    if ((*(byte *)(param_1 + 0x44) & 0x40) == 0) {
      if (*(byte *)(iVar8 + 0x2de) < 7) {
        local_20 = 3 < *(byte *)(iVar8 + 0x2de);
      }
      else {
        local_20 = '\x02';
      }
    }
    else {
      if (*(byte *)(iVar8 + 0x2df) < 7) {
        local_20 = 3 < *(byte *)(iVar8 + 0x2df);
      }
      else {
        local_20 = '\x02';
      }
      local_20 = local_20 + -2;
    }
    if (((2 < period_idx) || ((period_idx == 2 && (_period_idx >> 0x10 < dword_e9ab6 >> 0x11)))) &&
       ((dword_df622._2_2_ == dword_df722._2_2_ ||
        (0 < (short)(dword_df622._2_2_ - dword_df722._2_2_) !=
         ((*(byte *)(param_1 + 0x44) & 0x40) == 0))))) {
      cStackY_18 = '\x02';
    }
  }
  *(undefined2 *)(param_1 + 0x48) = 0;
  *(undefined2 *)(param_1 + 0x4c) = 0;
  *(undefined2 *)(param_1 + 0x4a) = 0;
  *(undefined *)(param_1 + 0x53) = 0;
  if (unaff_DX < 0x19) {
    iVar8 = CONCAT13(uStackY_27,CONCAT12(local_28,uStackY_2a)) >> 0x10;
    *(undefined *)(param_1 + 0x5e) = *(undefined *)(*(int *)(iVar2 + 0xee) + 5 + iVar8 * 0x27);
    puVar3 = (undefined *)(iVar8 * 0x14 + *(int *)(iVar2 + 0xde));
    *(undefined *)(param_1 + 0x65) = *puVar3;
    bVar4 = *(byte *)(param_1 + 0x55) & 0xf7;
    *(byte *)(param_1 + 0x55) = bVar4;
    if (*(char *)(param_1 + 0x65) == '\0') {
      *(byte *)(param_1 + 0x55) = bVar4 | 8;
    }
    *(undefined *)(param_1 + 0x58) = puVar3[1];
    *(undefined *)(param_1 + 0x57) = puVar3[2];
    if (*(byte *)(param_1 + 0x58) < 3) {
      cVar5 = *(char *)(param_1 + 0x58);
    }
    else {
      cVar5 = '\x03';
    }
    *(char *)(param_1 + 0x58) = *(char *)(param_1 + 0x58) - cVar5;
    if (*(byte *)(param_1 + 0x57) < 3) {
      cVar5 = *(char *)(param_1 + 0x57);
    }
    else {
      cVar5 = '\x03';
    }
    *(char *)(param_1 + 0x57) = *(char *)(param_1 + 0x57) - cVar5;
    *(undefined *)(param_1 + 0x56) = puVar3[3];
    *(undefined *)(param_1 + 0x5b) = puVar3[4];
    uVar1 = (short)cStackY_18 + (ushort)(byte)puVar3[5];
    if (0xf < uVar1) {
      uVar1 = 0xf;
    }
    *(char *)(param_1 + 100) = (char)uVar1;
    sVar6 = (short)local_20 + (ushort)(byte)puVar3[6] + (short)local_1c + (short)local_24;
    if (sVar6 < 0) {
      sVar6 = 0;
    }
    if (0xf < sVar6) {
      sVar6 = 0xf;
    }
    *(char *)(param_1 + 0x60) = (char)sVar6;
    sVar6 = (short)local_24 + (short)local_1c + (ushort)(byte)puVar3[7] + (short)local_20;
    if (sVar6 < 0) {
      sVar6 = 0;
    }
    if (0xf < sVar6) {
      sVar6 = 0xf;
    }
    *(char *)(param_1 + 0x5c) = (char)sVar6;
    sVar6 = (short)local_20 + (ushort)(byte)puVar3[9] + (short)local_1c;
    if (sVar6 < 0) {
      sVar6 = 0;
    }
    if (0xf < sVar6) {
      sVar6 = 0xf;
    }
    *(char *)(param_1 + 0x5d) = (char)sVar6;
    uVar1 = (short)local_24 + (ushort)(byte)puVar3[10] + (short)local_1c + (short)local_20 +
            (short)cStackY_18;
    if ((short)uVar1 < 0) {
      uVar1 = 0;
    }
    if (0xf < (short)uVar1) {
      uVar1 = 0xf;
    }
    *(char *)(param_1 + 0x59) = (char)((short)(uVar1 ^ 0xf) + 0xf >> 1);
    uVar1 = (short)local_20 + (ushort)(byte)puVar3[0xb];
    if ((short)uVar1 < 0) {
      uVar1 = 0;
    }
    if (0xf < (short)uVar1) {
      uVar1 = 0xf;
    }
    *(char *)(param_1 + 0x5a) = (char)((short)(uVar1 ^ 0xf) + 0xf >> 1);
    *(undefined *)(param_1 + 0x62) = puVar3[0xc];
    *(undefined *)(param_1 + 0x61) = puVar3[0xd];
    uVar1 = (ushort)(byte)puVar3[0xe] + cStackY_18 * 2;
    if (0xf < uVar1) {
      uVar1 = 0xf;
    }
    *(char *)(param_1 + 0x5f) = (char)uVar1;
  }
  else {
    iVar8 = CONCAT13(uStackY_27,CONCAT12(local_28,uStackY_2a)) >> 0x10;
    *(undefined *)(param_1 + 0x5e) = *(undefined *)(*(int *)(iVar2 + 0xee) + 5 + iVar8 * 0x27);
    puVar3 = (undefined *)(iVar8 * 0x10 + -400 + *(int *)(iVar2 + 0xe2));
    *(undefined *)(param_1 + 0x65) = *puVar3;
    bVar4 = *(byte *)(param_1 + 0x55);
    *(byte *)(param_1 + 0x55) = bVar4 & 0xf7;
    if (*(char *)(param_1 + 0x65) == '\0') {
      *(byte *)(param_1 + 0x55) = bVar4 & 0xf7 | 8;
    }
    *(undefined *)(param_1 + 0x62) = puVar3[1];
    *(undefined *)(param_1 + 0x5d) = puVar3[2];
    *(undefined *)(param_1 + 0x5f) = puVar3[3];
    *(undefined *)(param_1 + 0x61) = puVar3[4];
    *(undefined *)(param_1 + 0x5b) = puVar3[5];
    *(undefined *)(param_1 + 0x58) = puVar3[6];
    *(undefined *)(param_1 + 0x57) = puVar3[7];
    if (*(byte *)(param_1 + 0x58) < 3) {
      cVar5 = *(char *)(param_1 + 0x58);
    }
    else {
      cVar5 = '\x03';
    }
    *(char *)(param_1 + 0x58) = *(char *)(param_1 + 0x58) - cVar5;
    if (*(byte *)(param_1 + 0x57) < 3) {
      cVar5 = *(char *)(param_1 + 0x57);
    }
    else {
      cVar5 = '\x03';
    }
    *(char *)(param_1 + 0x57) = *(char *)(param_1 + 0x57) - cVar5;
    *(undefined *)(param_1 + 0x56) = puVar3[8];
    uVar1 = (short)cStackY_18 +
            (short)local_1c + (ushort)(byte)puVar3[10] + (short)local_24 + (short)local_20;
    if ((short)uVar1 < 0) {
      uVar1 = 0;
    }
    if (0xf < (short)uVar1) {
      uVar1 = 0xf;
    }
    *(char *)(param_1 + 0x59) = (char)((short)(uVar1 ^ 0xf) + 0xf >> 1);
    uVar1 = (short)local_20 + (ushort)(byte)puVar3[0xb];
    if ((short)uVar1 < 0) {
      uVar1 = 0;
    }
    if (0xf < (short)uVar1) {
      uVar1 = 0xf;
    }
    *(char *)(param_1 + 0x5a) = (char)((short)(uVar1 ^ 0xf) + 0xf >> 1);
  }
  return;
}


// ================================================================================================
// sub_5b826 @ 0x5b826 [__watcall]
// ================================================================================================

void __watcall sub_5b826(int param_1)

{
  int iVar1;
  short sVar2;
  undefined2 *puVar3;
  
  __CHK(0x18);
  puVar3 = (undefined2 *)(param_1 + 0x46);
  for (sVar2 = 0; sVar2 < 0x1c; sVar2 = sVar2 + 1) {
    *puVar3 = 0x1000;
    puVar3 = puVar3 + 1;
    iVar1 = sVar2 * 2 + param_1;
    if (*(int *)(iVar1 + 0x7c) >> 0x10 == -3) {
      *(undefined2 *)(iVar1 + 0x7e) = 0xfffe;
      *(undefined *)(*(int *)(param_1 + 0xee) + sVar2 * 0x27) = 3;
    }
  }
  return;
}


// ================================================================================================
// sub_5b881 @ 0x5b881 [__watcall]
// ================================================================================================

void __watcall sub_5b881(void)

{
  undefined *puVar1;
  ushort uVar2;
  
  __CHK(0xc);
  puVar1 = (undefined *)((int)&dword_df612 + 2);
  for (uVar2 = 0; uVar2 < 0x200; uVar2 = uVar2 + 1) {
    *puVar1 = 0;
    puVar1 = puVar1 + 1;
  }
  word_df64c = 0;
  word_df642 = 0xffff;
  word_df74c = 0;
  word_df742._0_2_ = 0xffff;
  byte_df6ca = 0xff;
  byte_df7ca = 0xff;
  dword_df70a = &entities;
  dword_df6f2 = &player_ratings;
  dword_df6f6 = &unk_dac40;
  dword_df6ee = &unk_dc200;
  dword_df6fa = &word_db088;
  dword_df6fe = &word_dc240;
  dword_df702 = &rosters;
  dword_df706 = &team_names;
  dword_df80a = &unk_dfb1c;
  dword_df7f2 = &unk_dae94;
  dword_df7f6 = &unk_dac70;
  dword_df7ee = &unk_dabf0;
  dword_df7fa = &unk_db218;
  dword_df7fe = &unk_dc252;
  dword_df802 = &unk_db7ec;
  dword_df806 = &unk_dbf18;
  return;
}


// ================================================================================================
// sub_5b97a @ 0x5b97a [__watcall]
// ================================================================================================

void __watcall sub_5b97a(void)

{
  int iVar1;
  byte *pbVar2;
  undefined2 *puVar3;
  short sVar4;
  short sVar5;
  
  __CHK(0x14);
  iVar1 = 0xdf614;
  for (sVar5 = 0; sVar5 < 2; sVar5 = sVar5 + 1) {
    *(undefined2 *)(iVar1 + 0x36) = 6;
    puVar3 = (undefined2 *)(iVar1 + 0x7e);
    pbVar2 = *(byte **)(iVar1 + 0xee);
    for (sVar4 = 0; sVar4 < 0x1c; sVar4 = sVar4 + 1) {
      *puVar3 = *(undefined2 *)(&unk_ccca8 + (uint)*pbVar2 * 2);
      puVar3 = puVar3 + 1;
      pbVar2 = pbVar2 + 0x27;
    }
    iVar1 = 0xdf714;
  }
  return;
}


// ================================================================================================
// sub_5b9d1 @ 0x5b9d1 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined2 __watcall sub_5b9d1(void)

{
  undefined2 uVar1;
  
  __CHK(4);
  uVar1 = (&word_cbc4a)[(option_flags << 0x14) >> 0x1e];
  if (((option_flags & 0x200) != 0) && (3 < _period_num)) {
    uVar1 = word_cbc4a;
  }
  return uVar1;
}


// ================================================================================================
// sub_5ba07 @ 0x5ba07 [__watcall]
// ================================================================================================

void __watcall sub_5ba07(void)

{
  short sVar1;
  
  __CHK(8);
  clock_seconds = sub_5b9d1();
  clock_sub = 0;
  dword_e9ab6._2_2_ = clock_seconds;
  sVar1 = randomrange((int)(clock_seconds >> 1));
  dword_e9aac = clock_seconds - sVar1;
  game_flags = game_flags | 1;
  return;
}


// ================================================================================================
// sub_5ba4e @ 0x5ba4e [__watcall]
// ================================================================================================

void __watcall sub_5ba4e(void)

{
  undefined4 *puVar1;
  short sVar2;
  ushort uVar3;
  
  __CHK(0x10);
  for (sVar2 = 0; sVar2 < 0x11; sVar2 = sVar2 + 1) {
    puVar1 = &entities + sVar2 * 0x20;
    for (uVar3 = 0; uVar3 < 0x80; uVar3 = uVar3 + 1) {
      *(undefined *)puVar1 = 0;
      puVar1 = (undefined4 *)((int)puVar1 + 1);
    }
  }
  return;
}


// ================================================================================================
// sub_5ba89 @ 0x5ba89 [__watcall]
// ================================================================================================

void __watcall sub_5ba89(void)

{
  byte bVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined2 *puVar4;
  short sVar5;
  undefined1 *puVar6;
  short *psVar7;
  
  __CHK(0x18);
  sub_5ba4e();
  puVar4 = &entity_init;
  puVar2 = &entities;
  puVar6 = &unk_e9ade;
  psVar7 = &draw_order_pos;
  sVar5 = 0;
  do {
    *(short *)((int)puVar2 + 0x6a) = sVar5;
    *(undefined *)((int)puVar2 + 0x47) = 0xff;
    *(undefined *)((int)puVar2 + 0x42) = 0xff;
    *(undefined *)((int)puVar2 + 0x43) = *(undefined *)((int)puVar2 + 0x42);
    *(undefined2 *)((int)puVar2 + 2) = *puVar4;
    *(undefined2 *)((int)puVar2 + 6) = puVar4[1];
    *(undefined2 *)((int)puVar2 + 10) = puVar4[2];
    *(undefined2 *)((int)puVar2 + 0x12) = puVar4[3];
    *(undefined2 *)(puVar2 + 0x15) = puVar4[4];
    *(undefined2 *)((int)puVar2 + 0x66) = puVar4[5];
    *(undefined2 *)(puVar2 + 0x1a) = puVar4[6];
    *(undefined *)((int)puVar2 + 0x1e) = *(undefined *)(puVar4 + 7);
    bVar1 = *(byte *)(puVar4 + 8);
    *(byte *)(puVar2 + 0x11) = bVar1;
    puVar4 = puVar4 + 9;
    if ((bVar1 & 0x40) == 0) {
      uVar3 = 0xdf614;
    }
    else {
      uVar3 = 0xdf714;
    }
    puVar2[0x1b] = uVar3;
    if ((*(byte *)(puVar2 + 0x11) & 0x40) == 0) {
      uVar3 = 0xdf714;
    }
    else {
      uVar3 = 0xdf614;
    }
    puVar2[0x1c] = uVar3;
    *(undefined2 *)((int)puVar2 + 0x2e) = 0;
    *puVar6 = (char)sVar5;
    *psVar7 = sVar5;
    puVar6 = puVar6 + 1;
    psVar7 = psVar7 + 1;
    puVar2 = puVar2 + 0x20;
    sVar5 = sVar5 + 1;
  } while (sVar5 != 0x11);
  word_e0052 = 2;
  dword_e0036._0_2_ = 0xffff;
  byte_e0072 = 7;
  byte_e0073 = 0xf;
  byte_e0074 = 0xf;
  ref_phase = 0xffff;
  sort_draw_order2();
  return;
}


// ================================================================================================
// player_available @ 0x5bb9e [__watcall]
// ================================================================================================

undefined4 __watcall player_available(int param_1,short unaff_DX,short unaff_BX)

{
  short sVar1;
  
  __CHK(8);
  param_1 = unaff_DX * 2 + param_1;
  if ((*(short *)(param_1 + 0x7e) < 1) && (-3 < *(int *)(param_1 + 0x7c) >> 0x10)) {
    sVar1 = 5;
    while( true ) {
      if (sVar1 < 0) {
        (&unk_e0384)[unaff_BX] = (char)unaff_DX;
        return 1;
      }
      if ((sVar1 != unaff_BX) && (unaff_DX == (char)(&unk_e0384)[sVar1])) break;
      sVar1 = sVar1 + -1;
    }
  }
  return 0;
}


// ================================================================================================
// assign_line_positions @ 0x5bbfa [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall assign_line_positions(int param_1)

{
  char cVar1;
  short sVar2;
  int iVar3;
  undefined uVar4;
  short sVar5;
  short sVar6;
  short sVar7;
  short sVar8;
  int iVar9;
  char *pcVar10;
  int iVar11;
  undefined *puVar12;
  int iVar13;
  bool bVar14;
  short local_28;
  undefined2 uStackY_22;
  undefined uStackY_20;
  undefined uStackY_1f;
  char cStackY_1c;
  
  __CHK(0x30);
  local_28 = 0;
  sVar2 = *(short *)(param_1 + 0x2a);
  uStackY_20 = (undefined)sVar2;
  uStackY_1f = (undefined)((ushort)sVar2 >> 8);
  iVar3 = *(int *)(param_1 + 0xda);
  for (sVar5 = 0; sVar5 < 6; sVar5 = sVar5 + 1) {
    (&unk_e0384)[sVar5] = 0xff;
  }
  if (((penalty_shot_phase == 0) || ((param_1 == 0xdf714) == penalty_shot_team)) &&
     (*(short *)(param_1 + 0x38) < 0)) {
    local_28 = 1;
  }
  else {
    *(undefined2 *)(param_1 + 0x2e) = 0xffff;
  }
  sVar5 = *(short *)(param_1 + 0x36);
  do {
    sVar5 = sVar5 + -1;
    if (sVar5 < 0) {
      sVar5 = 5;
      do {
        if (sVar5 < 0) {
          return;
        }
        iVar13 = (int)sVar5;
        if (-1 < (char)(&unk_e0384)[iVar13]) {
          sVar6 = (short)(char)(&unk_e038a)[iVar13];
          iVar9 = (int)(short)(char)(&unk_e0384)[iVar13];
          iVar11 = iVar9 * 2 + param_1;
          if (((*(int *)(iVar11 + 0x7c) >> 0x10 < -2) || (0 < *(short *)(iVar11 + 0x7e))) ||
             (((*(int *)(param_1 + 0x34) >> 0x10) + -2 <= iVar13 &&
              (sVar7 = player_available(param_1,iVar9), sVar7 == 0)))) {
            pcVar10 = &unk_cccc8 + (*(int *)(&unk_cccb8 + sVar6 * 2) >> 0x10);
LAB_0005bdac:
            cVar1 = *pcVar10;
            pcVar10 = pcVar10 + 1;
            if (-1 < cVar1) goto LAB_0005bea3;
            bVar14 = param_1 == 0xdf714;
            if ((sVar6 == 6) || (sVar2 < 6)) {
              if ((sVar6 == 1) || (sVar6 == 2)) {
                puVar12 = &unk_e9d50 + (short)(ushort)bVar14 * 0x19;
              }
              else {
                puVar12 = &unk_e9e4a + (short)(ushort)bVar14 * 0x19;
              }
            }
            else if ((sVar6 == 1) || (sVar6 == 2)) {
              puVar12 = &unk_e9db4 + (short)(ushort)bVar14 * 0x19;
            }
            else {
              puVar12 = &unk_e9ee0 + (short)(ushort)bVar14 * 0x19;
            }
            sVar7 = 0;
            do {
              cStackY_1c = puVar12[sVar7];
              sVar7 = sVar7 + 1;
              if (cStackY_1c < '\0') {
                sVar7 = 0x18;
                do {
                  cStackY_1c = (char)sVar7;
                  sVar7 = sVar7 + -1;
                  if (sVar7 < 0) goto LAB_0005becb;
                  sVar8 = player_available(param_1,(int)cStackY_1c,(int)sVar5);
                } while (sVar8 == 0);
              }
              sVar8 = player_available(param_1,(int)cStackY_1c,(int)sVar5);
            } while (sVar8 == 0);
          }
LAB_0005becb:
          if (sVar6 == 6) {
            *(short *)(param_1 + 0x2e) = (short)(char)(&unk_e0384)[sVar5];
          }
        }
        sVar5 = sVar5 + -1;
      } while( true );
    }
    sVar6 = (short)(char)(&unk_cbc37)[(int)local_28 + (int)sVar5];
    (&unk_e038a)[sVar5] = (&unk_cbc37)[(int)local_28 + (int)sVar5];
    if (sVar6 == 0) {
      iVar13 = *(int *)(param_1 + 0x36);
      iVar9 = _unk_cccb8;
LAB_0005bcbf:
      iVar13 = *(int *)(&unk_cccc5 + (iVar13 >> 0x10) + (iVar9 >> 0x10));
LAB_0005bccc:
      uVar4 = *(undefined *)((iVar13 >> 0x18) + iVar3);
    }
    else {
      if (sVar6 != 6) {
        if ((sVar2 < 4) && (sVar6 < 3)) {
          iVar9 = *(int *)(&unk_cccb8 + sVar6 * 2);
          iVar13 = *(int *)(param_1 + 0x2a);
          goto LAB_0005bcbf;
        }
        iVar13 = *(int *)(&unk_cccc5 +
                         (CONCAT13(uStackY_1f,CONCAT12(uStackY_20,uStackY_22)) >> 0x10) +
                         (*(int *)(&unk_cccb8 + sVar6 * 2) >> 0x10));
        goto LAB_0005bccc;
      }
      uVar4 = *(undefined *)(iVar3 + 0x26);
    }
    (&unk_e0384)[sVar5] = uVar4;
  } while( true );
LAB_0005bea3:
  sVar7 = player_available(param_1,(int)*(char *)(cVar1 + iVar3),(int)sVar5);
  if (sVar7 != 0) goto LAB_0005becb;
  goto LAB_0005bdac;
}


// ================================================================================================
// apply_line_change @ 0x5bef4 [__watcall]
// ================================================================================================

void __watcall apply_line_change(int param_1,undefined4 param_2,int unaff_EBX)

{
  char cVar1;
  int iVar2;
  int iVar3;
  short sVar4;
  short sVar5;
  
  __CHK(0x1c);
  sVar5 = 6;
  iVar2 = *(int *)(param_1 + 0xf6);
  do {
    *(undefined *)(iVar2 + 0x42) = 0xff;
    *(undefined *)(iVar2 + 0x43) = 0xff;
    iVar2 = iVar2 + 0x80;
    sVar5 = sVar5 + -1;
  } while (sVar5 != 0);
  assign_line_positions(param_1);
  sVar5 = 5;
  do {
    cVar1 = (&unk_e0384)[sVar5];
    if (-1 < cVar1) {
      iVar2 = *(int *)(param_1 + 0xf6) + -0x80;
      for (sVar4 = 0; sVar4 < 6; sVar4 = sVar4 + 1) {
        if (*(char *)(iVar2 + 199) == cVar1) {
          *(undefined *)(iVar2 + 0xc2) = (&unk_e038a)[sVar5];
          *(char *)(iVar2 + 0xc3) = cVar1;
          (&unk_e0384)[sVar5] = 0xff;
          break;
        }
        iVar2 = iVar2 + 0x80;
      }
    }
    sVar5 = sVar5 + -1;
    if (sVar5 == -1) {
      sVar5 = 5;
      do {
        cVar1 = (&unk_e0384)[sVar5];
        iVar2 = unaff_EBX;
        if (-1 < cVar1) {
          sVar4 = 0;
          iVar3 = *(int *)(param_1 + 0xf6) + -0x80;
          while ((iVar2 = unaff_EBX, sVar4 < 6 &&
                 ((iVar2 = iVar3 + 0x80, -1 < *(char *)(iVar3 + 0xc3) ||
                  (unaff_EBX = iVar2, *(short *)(iVar3 + 0x9a) < 0))))) {
            sVar4 = sVar4 + 1;
            iVar3 = iVar2;
          }
          if (*(short *)(iVar2 + 0x1a) < 0) {
            set_state(iVar2,0x29);
            *(undefined2 *)(iVar2 + 0x1a) = 5;
          }
          *(undefined *)(iVar2 + 0x42) = (&unk_e038a)[sVar5];
          *(char *)(iVar2 + 0x43) = cVar1;
          (&unk_e0384)[sVar5] = 0xff;
        }
        sVar5 = sVar5 + -1;
        unaff_EBX = iVar2;
      } while (sVar5 != -1);
      return;
    }
  } while( true );
}


// ================================================================================================
// period_init @ 0x5c010 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall period_init(void)

{
  undefined2 extraout_DX;
  undefined4 *puVar1;
  undefined4 uStackY_18;
  
  __CHK(0x18);
  word_e0306 = 0;
  word_e0304 = 0;
  uStackY_18 = 0x5c034;
  sub_5a669();
  uStackY_18 = 0x5c040;
  dword_e9a9e._0_2_ = extraout_DX;
  sub_5d7f7();
  uStackY_18 = 0x5c045;
  sub_5ba07();
  if (user1_team == 1) {
    _user1_slot = 2;
  }
  else if (user1_team == 2) {
    _user1_slot = 8;
  }
  if ((short)user2_team != 0) {
    if ((short)user2_team == user1_team) {
      user2_slot = _user1_slot + -1;
    }
    else if ((short)user2_team == 1) {
      user2_slot = 2;
    }
    else if ((short)user2_team == 2) {
      user2_slot = 8;
    }
  }
  byte_e9ad3._0_1_ = 0xff;
  _word_cbec8 = 0xffff;
  dword_cbeca._0_2_ = 0;
  dword_cbebe._2_2_ = 0xffff;
  penalty_shot_phase = 0;
  penalty_shot_active = 0;
  penalty_shot_setup = 0;
  defenders_ahead = 0;
  breakaway_flag = 0;
  penalty_shot_slot = 0xffffffff;
  faceoff_spot._0_2_ = 0;
  faceoff_spot._2_2_ = 0;
  uStackY_18 = 0x5c11f;
  set_state(&puck,0x1b);
  if (period_idx != 0) {
    crowd_noise._2_2_ = 0;
  }
  stop_flags._0_1_ = (byte)stop_flags | 4;
  action_flags = action_flags & 0xaf;
  replay_write_ptr = replay_buffer;
  uStackY_18 = 0x5c14d;
  sub_67564();
  crowd_noise._0_2_ = 0xffff;
  puVar1 = &uStackY_18;
  uStackY_18 = 0x5c15b;
  sim_tick();
  *(undefined4 *)((int)puVar1 + -4) = 0x5c160;
  sim_tick();
  excitement._2_2_ = 0x10;
  if (period_idx < 2) {
    misc_flags = misc_flags | 0x80;
  }
  *p_puck_carrier = 0xff;
  camera._2_2_ = 0;
  camera._0_2_ = 0;
  camera_target_y._2_2_ = 0;
  camera_target_y._0_2_ = 0;
  _camera_target_x = 0;
  word_cbec4 = 1;
  dword_c7444 = dword_c7444 + 1000;
  dword_c7448 = dword_c7448 + 1000;
  return;
}


// ================================================================================================
// sim_tick @ 0x5c1c4 [__watcall]
// ================================================================================================

void __watcall sim_tick(void)

{
  __CHK(4);
  sim_game_state();
  sim_update_players();
  update_camera();
  replay_record_frame();
  return;
}


// ================================================================================================
// regenerate_energy @ 0x5c1e2 [__watcall]
// ================================================================================================

void __watcall regenerate_energy(void)

{
  int iVar1;
  int iVar2;
  short sVar3;
  short sVar4;
  short sVar5;
  
  __CHK(0x14);
  if (((byte)option_flags & 4) != 0) {
    iVar2 = 0xdf614;
    for (sVar5 = 0; sVar5 < 2; sVar5 = sVar5 + 1) {
      sVar3 = 0x1b;
      do {
        iVar1 = sVar3 * 2 + iVar2;
        if ((*(int *)(iVar1 + 0x7c) >> 0x10 == -2) &&
           (sVar4 = *(short *)(iVar1 + 0x46) + 8, *(short *)(iVar1 + 0x46) = sVar4, 0x1000 < sVar4))
        {
          *(undefined2 *)(iVar1 + 0x46) = 0x1000;
        }
        sVar3 = sVar3 + -1;
      } while (-1 < sVar3);
      iVar2 = 0xdf714;
    }
  }
  return;
}


// ================================================================================================
// update_crowd_random @ 0x5c248 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall update_crowd_random(void)

{
  short sVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  
  __CHK(0x10);
  if (word_e9aa4 < excitement._2_2_) {
    word_e9aa4 = excitement._2_2_;
  }
  _dword_e009c = _dword_e009c + ((int)excitement >> 0x10);
  excitement._0_2_ = (ushort)excitement + 1;
  sVar1 = excitement._2_2_ + -1;
  excitement = CONCAT22(sVar1,(ushort)excitement);
  if (sVar1 < 0) {
    excitement = (uint)(ushort)excitement;
  }
  if (((game_flags & 1) != 0) && (600 < crowd_noise._2_2_)) {
    iVar2 = 1000 - (crowd_noise >> 0x10);
    iVar4 = iVar2 >> 0x1f;
    iVar2 = (int)((iVar2 + iVar4 * -4) - (uint)(iVar4 << 1 < 0)) >> 2;
    if (iVar2 < 0x19) {
      iVar2 = 0x19;
    }
    sVar1 = randomrange((int)(short)iVar2);
    if (sVar1 == 0) {
      uVar3 = 0xa6;
    }
    else {
      if (sVar1 != 1) {
        return;
      }
      uVar3 = 0x96;
    }
    play_sfx(uVar3);
  }
  return;
}


// ================================================================================================
// sim_game_state @ 0x5c302 [__watcall]
// ================================================================================================

void __watcall sim_game_state(void)

{
  char cVar1;
  int iVar2;
  short sVar3;
  short sVar4;
  
  __CHK(0xc);
  update_stoppage();
  update_effects();
  if ((((game_flags & 1) == 0) && (clock_seconds == 0)) && (clock_sub == 0)) {
    play_sfx(0x90);
    hold_camera();
    setup_faceoff();
  }
  cVar1 = word_cc0d8._1_1_;
  if (penalty_box_mode == 0) {
    cVar1 = word_cc0d8._1_1_ + -1;
    if ((char)(word_cc0d8._1_1_ + -1) < '\0') {
      word_cc0d8._1_1_ = word_cc0d8._1_1_ + '\x17';
      word_cc0d8._0_1_ = (byte)word_cc0d8 ^ 1;
      cpu_line_change();
      update_crowd_random();
      regenerate_energy();
      if ((game_flags & 1) == 0) {
        update_lead_change();
      }
      cVar1 = word_cc0d8._1_1_;
      if (((byte)option_flags & 4) != 0) {
        iVar2 = 0xdf614;
        for (sVar4 = 0; cVar1 = word_cc0d8._1_1_, sVar4 < 2; sVar4 = sVar4 + 1) {
          iVar2 = *(int *)(iVar2 + 0xf6);
          sVar3 = 6;
          do {
            if (((-1 < *(short *)(iVar2 + 0x1a)) && (-1 < *(char *)(iVar2 + 0x43))) &&
               ((penalty_shot_phase == 0 && (((byte)word_cc0d8 & 1) != 0)))) {
              (&word_cbc52)[sVar4] = 1;
              return;
            }
            iVar2 = iVar2 + 0x80;
            sVar3 = sVar3 + -1;
          } while (sVar3 != 0);
          (&word_cbc52)[sVar4] = 0;
          iVar2 = 0xdf714;
        }
      }
    }
  }
  word_cc0d8._1_1_ = cVar1;
  return;
}


// ================================================================================================
// sim_update_players @ 0x5c40f [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall sim_update_players(void)

{
  short *psVar1;
  bool bVar2;
  undefined uVar3;
  undefined2 uVar4;
  short sVar5;
  int iVar6;
  int iVar7;
  short sVar8;
  int iVar9;
  undefined4 uVar10;
  int *piVar11;
  short local_24;
  short local_20;
  
  __CHK(0x30);
  if ((game_flags & 1) != 0) {
    if ((game_flags & 0x80) != 0) {
LAB_0005c4ae:
      controls_blocked = 1;
      goto LAB_0005c4b7;
    }
    if ((((((byte)stop_flags & 1) == 0) && (stoppage_timer < 0)) && (infraction_queue._3_1_ == '\0')
        ) && (((&unk_e003a)[dword_e0036 >> 0x10] != ' ' &&
              ((&unk_e003a)[dword_e0036 >> 0x10] != '#')))) {
      if (((dword_cbeca._2_2_ == 2) || ((dword_cbeca._2_2_ == 0 || (dword_cbebe._2_2_ < 0)))) ||
         (0xff < dword_cbebe._2_2_)) {
        bVar2 = true;
      }
      else {
        bVar2 = false;
      }
      if (bVar2) goto LAB_0005c4ae;
    }
  }
  controls_blocked = 0;
LAB_0005c4b7:
  piVar11 = &entities;
  word_df70e = 0xffff;
  dword_df652 = 0xffff;
  word_df656 = 0xffff;
  word_df80e = 0xffff;
  dword_df752 = 0xffff;
  word_df756 = 0xffff;
  for (sVar5 = 0; sVar5 < 0xc; sVar5 = sVar5 + 1) {
    iVar7 = piVar11[0x1b];
    iVar9 = (int)*p_puck_x - (*piVar11 >> 0x10);
    local_20 = (short)iVar9;
    iVar6 = (int)*p_puck_y - (piVar11[1] >> 0x10);
    local_24 = (short)iVar6;
    uVar4 = approx_distance(iVar9,local_24);
    *(undefined2 *)((int)piVar11 + 0x4e) = uVar4;
    uVar3 = direction8((int)local_20,(int)local_24);
    *(undefined *)((int)piVar11 + 0x52) = uVar3;
    local_20 = (short)(iVar9 >> 2);
    local_24 = (short)(iVar6 >> 2);
    *(short *)(piVar11 + 0x14) = local_20 * local_20 + local_24 * local_24;
    if (*(short *)((int)piVar11 + 0x1a) == 0) {
      *(short *)(iVar7 + 0xfa) = sVar5;
    }
    else if ((((0 < *(short *)((int)piVar11 + 0x1a)) && ((*(byte *)((int)piVar11 + 0x45) & 4) == 0))
             && ((*(byte *)(piVar11 + 0x11) & 0x20) == 0)) &&
            (iVar9 = *(int *)((int)piVar11 + 0x4e) >> 0x10, iVar9 < *(int *)(iVar7 + 0x3e))) {
      *(int *)(iVar7 + 0x3e) = iVar9;
      *(short *)(iVar7 + 0x42) = sVar5;
    }
    piVar11 = piVar11 + 0x20;
  }
  piVar11 = &entities;
  sVar5 = 0;
  do {
    if (0x10 < sVar5) {
      if (*p_puck_z < 0x18) {
        sVar5 = *p_puck_x;
        if (sVar5 < 0) {
          iVar7 = -(int)sVar5;
        }
        else {
          iVar7 = (int)sVar5;
        }
        if ((0xa0 < iVar7) && (-1 < *p_puck_carrier)) {
          if (*p_puck_x < 0) {
            sVar5 = -0xa0;
          }
          else {
            sVar5 = 0xa0;
          }
          *p_puck_x = sVar5;
          _word_dff2e = 0x18a;
        }
      }
      if (((*p_puck_z < 1) && (-1 < *p_puck_carrier)) &&
         ((*p_puck_y < -0x104 || (0x108 < *p_puck_y)))) {
        if (*p_puck_y < 0) {
          sVar5 = -0x104;
        }
        else {
          sVar5 = 0x108;
        }
        *p_puck_y = sVar5;
        _word_dff2e = 0x18a;
      }
      return;
    }
    piVar11[0x1d] = *piVar11;
    piVar11[0x1e] = piVar11[1];
    piVar11[0x1f] = piVar11[2];
    if ((-1 < *(short *)((int)piVar11 + 0x1a)) || (*(short *)((int)piVar11 + 0x6a) == 0x10)) {
      advance_animation(piVar11);
      sVar8 = *(short *)((int)piVar11 + 0x3e) + -1;
      *(short *)((int)piVar11 + 0x3e) = sVar8;
      if (sVar8 < 0) {
        *(undefined2 *)((int)piVar11 + 0x3e) = 0;
      }
      sVar8 = *(short *)(piVar11 + 0x10);
      *(short *)(piVar11 + 0x10) = sVar8 + -1;
      if ((short)(sVar8 + -1) < 0) {
        *(undefined2 *)(piVar11 + 0x10) = 0;
      }
      if ((*(short *)((int)piVar11 + 0x6a) != 0x10) && ((misc_flags & 0x40) != 0)) {
        if ((-1 < *(char *)((int)piVar11 + 0x47)) &&
           (((*(short *)((int)piVar11 + 0x1a) == 0 && ('\x18' < *(char *)((int)piVar11 + 0x47))) &&
            ((game_flags & 0x10) == 0)))) {
          psVar1 = (short *)(*(int *)(piVar11[0x1b] + 0xea) + ((piVar11[0x11] >> 0x18) + -0x19) * 6)
          ;
          *psVar1 = *psVar1 + 1;
        }
      }
      sVar8 = *(short *)(piVar11 + 0xe);
      if ((sVar8 != 0xa0b) && ((sVar8 < 0xf0f || (0x1055 < sVar8)))) {
        dword_e03b2 = CONCAT22(0x10,(undefined2)dword_e03b2);
        if (*(short *)((int)piVar11 + 10) == 0) {
          if ((*(byte *)(piVar11 + 0x11) & 1) == 0) {
            dword_e03ac = 6;
          }
          else {
            dword_e03ac = 9;
          }
          dword_e03ae._0_2_ = 0;
          if (*(short *)(piVar11 + 3) != 0) {
            dword_e03ba._2_2_ = *(short *)(piVar11 + 3) >> (sbyte)dword_e03ac;
            if (dword_e03ba._2_2_ == 0) {
              dword_e03ba._2_2_ = 1;
              dword_e03be._0_2_ = 0;
            }
            sVar8 = *(short *)(piVar11 + 3);
            *(short *)(piVar11 + 3) = sVar8 - dword_e03ba._2_2_;
            if (*(short *)((int)piVar11 + 0x6a) < 0xc) {
              if ((short)(sVar8 - dword_e03ba._2_2_) < 0) {
                iVar7 = -(*(int *)((int)piVar11 + 10) >> 0x10);
              }
              else {
                iVar7 = *(int *)((int)piVar11 + 10) >> 0x10;
              }
              if (16000 < iVar7) {
                if (*(short *)(piVar11 + 3) < 1) {
                  uVar4 = 0xc180;
                }
                else {
                  uVar4 = 16000;
                }
                *(undefined2 *)(piVar11 + 3) = uVar4;
              }
            }
          }
          if (*(short *)((int)piVar11 + 0xe) != 0) {
            dword_e03ba._2_2_ = *(short *)((int)piVar11 + 0xe) >> ((byte)dword_e03ac & 0x1f);
            if (dword_e03ba._2_2_ == 0) {
              dword_e03ba._2_2_ = 1;
              dword_e03be._0_2_ = 0;
            }
            sVar8 = *(short *)((int)piVar11 + 0xe) - dword_e03ba._2_2_;
            *(short *)((int)piVar11 + 0xe) = sVar8;
            if (*(short *)((int)piVar11 + 0x6a) < 0xc) {
              if (sVar8 < 0) {
                iVar7 = -(piVar11[3] >> 0x10);
              }
              else {
                iVar7 = piVar11[3] >> 0x10;
              }
              if (16000 < iVar7) {
                if (*(short *)((int)piVar11 + 0xe) < 1) {
                  uVar4 = 0xc180;
                }
                else {
                  uVar4 = 16000;
                }
                *(undefined2 *)((int)piVar11 + 0xe) = uVar4;
              }
            }
          }
        }
        if (*(short *)(piVar11 + 3) != 0) {
          *piVar11 = *piVar11 + (dword_e03b2 >> 0x10) * (int)*(short *)(piVar11 + 3);
        }
        dword_e03ba._2_2_ = *(short *)((int)piVar11 + 0xe);
        if (dword_e03ba._2_2_ != 0) {
          piVar11[1] = piVar11[1] + (dword_e03b2 >> 0x10) * (int)dword_e03ba._2_2_;
        }
        if ((-1 < *(short *)((int)piVar11 + 10)) &&
           ((*(short *)((int)piVar11 + 10) != 0 || (*(short *)(piVar11 + 4) != 0)))) {
          *(short *)(piVar11 + 4) = *(short *)(piVar11 + 4) + dword_e03b2._2_2_ * -6;
          iVar9 = (dword_e03b2 >> 0x10) * (*(int *)((int)piVar11 + 0xe) >> 0x10);
          dword_e03ba._2_2_ = (short)iVar9;
          dword_e03be._0_2_ = (undefined2)((uint)iVar9 >> 0x10);
          iVar7 = piVar11[2];
          piVar11[2] = iVar7 + iVar9;
          if (iVar7 + iVar9 < 0) {
            piVar11[2] = 0;
            *(short *)(piVar11 + 4) = -*(short *)(piVar11 + 4) >> 1;
            dword_e03ba._2_2_ = 5 - *(char *)((int)piVar11 + 0x11);
            if (dword_e03ba._2_2_ < 0) {
              dword_e03ba._2_2_ = 0;
            }
            if (dword_e03ba._2_2_ < 4) {
              play_sfx(0xab);
            }
          }
        }
      }
      dword_e03a0._0_2_ = *(short *)((int)piVar11 + 0x6a);
      if ((short)dword_e03a0 == _user1_slot) {
        read_control_p1();
        uVar10 = 0;
LAB_0005c8cd:
        control_player(piVar11,uVar10);
      }
      else if ((short)dword_e03a0 == user2_slot) {
        read_control_p2();
        uVar10 = 2;
        goto LAB_0005c8cd;
      }
      iVar7 = *(int *)((int)piVar11 + (*(int *)((int)piVar11 + 0x1a) >> 0x10) + 0x1b) >> 0x18;
      if (iVar7 != 0) {
        (*(code *)(&ai_state_handlers)[iVar7])();
      }
      if ((*(short *)((int)piVar11 + 0x6a) < 0xc) && ((game_flags & 1) == 0)) {
        if ((*(short *)((int)piVar11 + 0x1a) == 0) &&
           (((short)*p_puck_carrier != *(short *)((int)piVar11 + 0x6a) &&
            ((*(byte *)(piVar11 + 0x12) & 1) == 0)))) {
          if (*piVar11 >> 0x10 < -0x2b) {
            if (-0x32 < *piVar11 >> 0x10) {
              *(undefined2 *)((int)piVar11 + 2) = 0xffd5;
              goto LAB_0005c963;
            }
          }
          else if ((0x2b < *(short *)((int)piVar11 + 2)) && (*(short *)((int)piVar11 + 2) < 0x31)) {
            *(undefined2 *)((int)piVar11 + 2) = 0x2b;
LAB_0005c963:
            *(undefined2 *)(piVar11 + 3) = 0;
          }
          sVar8 = *(short *)((int)piVar11 + 6);
          if (sVar8 < 0) {
            if ((-0xc6 < piVar11[1] >> 0x10) && (piVar11[1] >> 0x10 < -0xc0)) {
              *(undefined2 *)((int)piVar11 + 6) = 0xff3a;
              goto LAB_0005c9a0;
            }
          }
          else if ((0xc0 < sVar8) && (sVar8 < 0xc6)) {
            *(undefined2 *)((int)piVar11 + 6) = 0xc6;
LAB_0005c9a0:
            *(undefined2 *)((int)piVar11 + 0xe) = 0;
          }
        }
      }
      *(undefined2 *)(piVar11 + 0xc) = 0;
      *(undefined2 *)((int)piVar11 + 0x32) = 0;
      dword_e03ac = *(short *)((int)piVar11 + 2);
      dword_e03ae._2_2_ = *(short *)((int)piVar11 + 6);
      if (((*(short *)((int)piVar11 + 0x76) != dword_e03ac) ||
          (*(short *)((int)piVar11 + 0x7a) != dword_e03ae._2_2_)) ||
         (*(short *)((int)piVar11 + 0x6a) == 0xe)) {
        move_entity(piVar11,(int)dword_e03ac);
      }
      sVar8 = *(short *)(piVar11 + 6);
      *(short *)(piVar11 + 6) = sVar8 + -2;
      if ((short)(sVar8 + -2) < 0) {
        *(undefined2 *)(piVar11 + 6) = 0;
      }
    }
    *(undefined2 *)((int)piVar11 + 0x16) = *(undefined2 *)(piVar11 + 6);
    sVar5 = sVar5 + 1;
    piVar11 = piVar11 + 0x20;
  } while( true );
}


// ================================================================================================
// advance_animation @ 0x5caef [__watcall]
// ================================================================================================

undefined8 __watcall advance_animation(int param_1,undefined4 unaff_EDX)

{
  ushort uVar1;
  char cVar2;
  ushort uVar3;
  uint uVar4;
  undefined2 uVar7;
  int iVar5;
  int iVar6;
  ushort *puVar8;
  short sVar9;
  int iVar10;
  
  __CHK(0x18);
  if (*(short *)(param_1 + 0x38) == 0) {
    *(byte *)(param_1 + 0x44) = *(byte *)(param_1 + 0x44) & 0xdf;
    *(byte *)(param_1 + 0x45) = *(byte *)(param_1 + 0x45) & 0xfd;
    iVar6 = param_1;
    goto LAB_0005a41f;
  }
  uVar4 = CONCAT22((short)((uint)param_1 >> 0x10),*(undefined2 *)(param_1 + 0x36));
  if ((action_flags & 0x80) != 0) {
    if ((*(short *)(param_1 + 0x6a) < 0xc) || (*(short *)(param_1 + 0x6a) == 0x10)) {
      uVar4 = uVar4 - 2 & 0xffff0007;
    }
  }
  if ((*(byte *)(param_1 + 0x55) & 8) != 0) {
    uVar4 = 8 - uVar4 & 0xffff0007;
  }
  puVar8 = (ushort *)(&anim_sequences + (*(int *)(param_1 + 0x36) >> 0x10) * 2);
  uVar1 = *puVar8;
  if ((short)uVar4 == 0) {
    uVar4 = CONCAT22((short)(uVar4 >> 0x10),*puVar8) & 0xffff7fff;
    uVar3 = (ushort)uVar4;
  }
  else {
    uVar3 = puVar8[(short)uVar4];
  }
  iVar10 = (int)(short)uVar3;
  uVar7 = (undefined2)(uVar4 >> 0x10);
  iVar6 = CONCAT22(uVar7,*(short *)(param_1 + 0x3a));
  uVar3 = puVar8[iVar10 + *(short *)(param_1 + 0x3a) + 8];
  if (*(short *)(param_1 + 0x3c) < 0) {
    uVar1 = (puVar8 + iVar10 + *(short *)(param_1 + 0x3a) + 8)[1];
    iVar6 = CONCAT22(uVar7,uVar1);
    if ((short)uVar1 < 0) {
      iVar6 = -iVar6;
    }
LAB_0005cc38:
    *(short *)(param_1 + 0x3c) = (short)iVar6;
  }
  else {
    sVar9 = *(short *)(param_1 + 0x3c) + -1;
    *(short *)(param_1 + 0x3c) = sVar9;
    if (sVar9 < 0) {
      *(short *)(param_1 + 0x3a) = *(short *)(param_1 + 0x3a) + 2;
      iVar5 = iVar6 + 2;
      if ((short)puVar8[iVar10 + (short)iVar5 + 7] < 0) {
        *(undefined2 *)(param_1 + 0x3a) = 0;
        iVar5 = CONCAT22((short)((uint)iVar5 >> 0x10),*(undefined2 *)(param_1 + 0x3a));
        *(byte *)(param_1 + 0x44) = *(byte *)(param_1 + 0x44) & 0xdf;
        *(byte *)(param_1 + 0x45) = *(byte *)(param_1 + 0x45) & 0xfd;
        if ((0x1026 < *(short *)(param_1 + 0x38)) && (*(short *)(param_1 + 0x38) < 0x1056)) {
          *(undefined2 *)(param_1 + 0xe) = 0;
          *(undefined2 *)(param_1 + 0xc) = *(undefined2 *)(param_1 + 0xe);
          *(undefined2 *)(param_1 + 2) = 0xff60;
          *(undefined2 *)(param_1 + 0x36) = 2;
          *(byte *)(param_1 + 0x44) = *(byte *)(param_1 + 0x44) | 0x20;
          iVar6 = set_animation(param_1,0x7a1);
          goto LAB_0005a41f;
        }
        if ((uVar1 & 0x8000) == 0) {
          *(undefined2 *)(param_1 + 0x38) = 0;
        }
      }
      iVar6 = CONCAT22((short)((uint)iVar5 >> 0x10),puVar8[iVar10 + (short)iVar5 + 9]);
      if ((short)puVar8[iVar10 + (short)iVar5 + 9] < 0) {
        iVar6 = -iVar6;
      }
      goto LAB_0005cc38;
    }
  }
  cVar2 = *(char *)(param_1 + 0x46) + -1;
  iVar6 = CONCAT31((int3)((uint)iVar6 >> 8),cVar2);
  *(char *)(param_1 + 0x46) = cVar2;
  if ((-1 < cVar2) || (*(undefined *)(param_1 + 0x46) = 0, uVar3 == *(ushort *)(param_1 + 0x12)))
  goto LAB_0005a41f;
  *(ushort *)(param_1 + 0x12) = uVar3;
  if ((((short)uVar3 < 0x112) || ((0x14e < (short)uVar3 || (((int)(short)uVar3 - 0x112U & 3) != 0)))
      ) && (((short)uVar3 < 0x207 || ((0x215 < (short)uVar3 || ((uVar3 & 1) == 0)))))) {
    if ((0x314 < (short)uVar3) && ((short)uVar3 < 0x32b)) {
      iVar6 = (int)(short)uVar3 / 3;
      if ((int)(short)uVar3 % 3 == 0) goto LAB_0005cd12;
    }
    if ((0x389 < (short)uVar3) && ((short)uVar3 < 0x3ae)) {
      iVar6 = ((short)uVar3 + -0x38a) / 5;
      if (((short)uVar3 + -0x38a) % 5 == 0) goto LAB_0005cd12;
    }
    if ((((uVar3 == 0x36f) || (uVar3 == 0x373)) || (uVar3 == 0x377)) ||
       (((uVar3 == 0x3bf || (uVar3 == 0x3c3)) || ((uVar3 == 0x3ce || (uVar3 == 0x3d1))))))
    goto LAB_0005cd12;
  }
  else {
LAB_0005cd12:
    iVar6 = play_sfx(0xb3);
  }
  *(undefined *)(param_1 + 0x46) = 4;
LAB_0005a41f:
  return CONCAT44(unaff_EDX,iVar6);
}


// ================================================================================================
// hold_camera @ 0x5cd25 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall hold_camera(void)

{
  __CHK(4);
  _camera_target_x = (undefined2)camera;
  camera_target_y._0_2_ = camera._2_2_;
  action_flags = action_flags | 0x40;
  return;
}


// ================================================================================================
// sub_5cd4f @ 0x5cd4f [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall sub_5cd4f(void)

{
  __CHK(0xc);
  dword_e03a8 = 0;
  dword_e03a0 = 0;
  ram0x000e03b8 = 0;
  ram0x000e03b4 = 0;
  ram0x000e03b0 = 0;
  _dword_e03ac = 0;
  ram0x000e03c0 = 0;
  ram0x000e03bc = 0;
  _camera_target_x = 0;
  camera_target_y._0_2_ = 0;
  camera_target_y._2_2_ = 0;
  faceoff_spot._0_2_ = 0;
  faceoff_spot._2_2_ = 0;
  faceoff_dir_home = 0;
  faceoff_dir_away = 0;
  puck_in_net = 0;
  goalie_pass_mode = 0;
  word_cc0d8 = 0;
  word_cc0da = 0;
  crowd_noise._0_2_ = 0xffff;
  game_flags = 0;
  _action_flags = 0;
  stop_flags = 0;
  _misc_flags = 0;
  clear_infractions();
  return;
}


// ================================================================================================
// draw_sprites @ 0x5ce12 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall draw_sprites(int param_1,short unaff_DX)

{
  char cVar1;
  undefined uVar2;
  int iVar3;
  short sVar4;
  short sVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  ushort uVar10;
  short sVar11;
  undefined2 uVar12;
  ushort uVar13;
  int *piVar14;
  short sVar15;
  bool bVar16;
  short local_54;
  int aiStack_50 [6];
  int local_38;
  int local_34;
  int iStack_30;
  short sStack_2c;
  short local_2a;
  short sStack_28;
  short sStack_24;
  short sStack_20;
  undefined4 uStack_1c;
  undefined2 uStack_18;
  
  __CHK(0x6c);
  local_54 = (short)param_1;
  sStack_28 = _user1_slot;
  sStack_24 = user2_slot;
  if (controls_blocked != 0) {
    sStack_24 = -1;
    sStack_28 = -1;
  }
  if (-0x10 < (short)camera) {
    if ((camera._2_2_ < 0x50) && (-0x94 < camera._2_2_)) {
      for (sVar15 = 0; (sVar15 < penalized_count && (sVar15 < 3)); sVar15 = sVar15 + 1) {
        draw_sprite_world(0x17e,0xb3,(int)(short)((sVar15 + 3) * -0xb),0,0);
      }
    }
    if ((-0x4b < camera._2_2_) && (camera._2_2_ < 0xb1)) {
      iVar6 = (ram0x000e9ab8 >> 0x18) + -1;
      if (1 < iVar6) {
        iVar6 = 2;
      }
      for (; -1 < (short)iVar6; iVar6 = iVar6 + -1) {
        draw_sprite_world(0x17e,0xb3,(int)(short)(((short)iVar6 + 3) * 0xb),0,1);
      }
    }
  }
  draw_nets_and_effects();
  if (camera._2_2_ < -0xb0) {
    uStack_18 = (undefined2)dword_d30b8;
    setclip(dword_d30bc,dword_d30c0,dword_d30b0,0x244);
  }
  for (sVar15 = 0; sVar15 < 3; sVar15 = sVar15 + 1) {
    iVar6 = (int)sVar15;
    aiStack_50[iVar6 + 3] = 0;
    aiStack_50[iVar6] = iVar6;
  }
  if (-1 < *(char *)CONCAT22(p_puck_carrier._2_2_,(undefined2)p_puck_carrier)) {
    aiStack_50[5] =
         (int)(&unk_df820)
              [*(char *)CONCAT22(p_puck_carrier._2_2_,(undefined2)p_puck_carrier) * 0x20] >> 0x10;
  }
  if (-1 < sStack_28) {
    aiStack_50[3] = (int)(&unk_df820)[sStack_28 * 0x20] >> 0x10;
  }
  if (-1 < sStack_24) {
    aiStack_50[4] = (int)(&unk_df820)[sStack_24 * 0x20] >> 0x10;
  }
  sub_93540(3,aiStack_50 + 3,(short)aiStack_50);
  for (sStack_20 = 0; sStack_20 < 3; sStack_20 = sStack_20 + 1) {
    sVar15 = *(short *)(aiStack_50 + sStack_20);
    if (sVar15 == 2) {
      cVar1 = *(char *)CONCAT22(p_puck_carrier._2_2_,(undefined2)p_puck_carrier);
      if (-1 < cVar1) {
        uVar12 = 0;
        iVar8 = dword_cc0b4 >> 0x10;
        uVar10 = 0;
        iVar6 = (int)(&entities)[cVar1 * 0x20] >> 0x10;
        iVar7 = (int)(&unk_df820)[cVar1 * 0x20] >> 0x10;
LAB_0005d1c9:
        draw_sprite_world(iVar8,iVar6,iVar7,uVar10,uVar12);
      }
    }
    else {
      sVar5 = sStack_28;
      if (sVar15 != 0) {
        sVar5 = sStack_24;
      }
      if (-1 < sVar5) {
        sVar5 = sStack_28;
        if (sVar15 != 0) {
          sVar5 = sStack_24;
        }
        iVar6 = sVar5 * 0x80;
        if (*(int *)(&DAT_000df82c + iVar6) >> 0x10 != -1) {
          sVar5 = *(short *)((int)&entities + iVar6 + 2);
          sStack_2c = *(short *)((int)&unk_df820 + iVar6 + 2);
          uVar13 = 0;
          local_2a = sStack_2c >> 0xf;
          if ((int)sStack_2c < 0x140 - (unaff_DX + 0xa8)) {
            uVar13 = 2;
            sVar11 = 0x140 - (unaff_DX + 0xa8);
          }
          else {
            sVar11 = sStack_2c;
            if (0x140 - unaff_DX <= (int)sStack_2c) {
              sVar11 = 0x141 - unaff_DX;
              uVar13 = 1;
            }
          }
          uStack_1c = 0x140 - (0xc0 - param_1);
          if (uVar13 == 0) {
            local_38 = 0x140 - (0xc0 - local_54);
            if (sVar5 < local_38) {
              if ((int)sVar5 < local_54 + -0xc0) {
                sVar5 = local_54 + -0xc0;
                uVar13 = 8;
              }
            }
            else {
              sVar5 = (short)uStack_1c + -1;
              uVar13 = 4;
            }
          }
          else {
            iStack_30 = (int)sVar5;
            local_38 = 0x134 - (0xc0 - local_54);
            if (iStack_30 < local_38) {
              if (iStack_30 < local_54 + -0xb4) {
                sVar5 = local_54 + -0xb4;
                uVar13 = uVar13 | 8;
              }
            }
            else {
              sVar5 = (short)uStack_1c + -0xd;
              uVar13 = uVar13 | 4;
            }
          }
          if (uVar13 == 0) {
            uVar12 = 0;
            iVar7 = (int)sVar11;
            iVar6 = (int)sVar5;
            iVar8 = *(int *)(&word_cc0b0 + sVar15) >> 0x10;
            uVar10 = 0;
          }
          else {
            uVar12 = 0;
            uVar10 = uVar13 & 8;
            local_38 = (int)sVar11;
            local_34 = (int)sVar5;
            iVar6 = sub_b340b(uVar13,0);
            iVar8 = *(int *)((int)&dword_cc0b4 + sVar15 * 0x10 + iVar6 * 2) >> 0x10;
            iVar6 = local_34;
            iVar7 = local_38;
          }
          goto LAB_0005d1c9;
        }
      }
    }
  }
  if ((dword_dffac._2_2_ < 0x284) || (0x288 < dword_dffac._2_2_)) {
    if (((dword_dffac._2_2_ == 0x189) &&
        ((-1 < *p_puck_z &&
         (*(char *)CONCAT22(p_puck_carrier._2_2_,(undefined2)p_puck_carrier) != '\x10')))) ||
       ((-1 < dword_dffa0 && ((0x229 < dword_dffac._2_2_ && (dword_dffac._2_2_ < 0x238)))))) {
      bVar16 = false;
      goto LAB_0005d267;
    }
  }
  else {
    bVar16 = dword_dff9c < 0;
LAB_0005d267:
    draw_sprite_world(dword_dffac >> 0x10,dword_dff9c >> 0x10,dword_dffa0 >> 0x10,bVar16,0);
  }
  if (*(char *)CONCAT22(p_puck_carrier._2_2_,(undefined2)p_puck_carrier) != '\x10') {
    if (dword_dff24._2_2_ == 0) {
      iVar6 = dword_dff20 >> 0x10;
    }
    else {
      if (dword_dff24._2_2_ < 1) goto LAB_0005d2c6;
      iVar6 = (int)(short)((short)(((dword_dff24 >> 0x10) * 3) / 2) +
                          (short)((uint)dword_dff20 >> 0x10));
    }
    draw_sprite_world(_dword_dff2c >> 0x10,puck >> 0x10,iVar6,0,0);
  }
LAB_0005d2c6:
  for (sVar15 = 0x10; -1 < sVar15; sVar15 = sVar15 + -1) {
    iVar6 = *(int *)((int)&draw_order_list + (int)sVar15) >> 0x18;
    iVar7 = iVar6 * 0x80;
    piVar14 = &entities + iVar6 * 0x20;
    sVar5 = *(short *)((int)&DAT_000df884 + iVar7 + 2);
    if (sVar5 != 0xf) {
      if (sVar5 == 0xe) {
        if (((*(char *)CONCAT22(p_puck_carrier._2_2_,(undefined2)p_puck_carrier) < '\0') &&
            (0 < *p_puck_z)) && (sVar5 = *p_puck_y, sVar5 < 0xe8)) {
          if ((sVar5 < -0xe7) && (-0xf1 < sVar5)) {
            sVar5 = *p_puck_x;
            if (sVar5 < 0) {
              iVar8 = -(int)sVar5;
            }
            else {
              iVar8 = (int)sVar5;
            }
            if ((iVar8 < 0x15) && (*p_puck_z < 0xd)) goto LAB_0005d500;
          }
          sVar5 = (short)((((int)(&DAT_000df824)[iVar6 * 0x20] >> 0x10) * 3) / 2) +
                  (short)((uint)(&unk_df820)[iVar6 * 0x20] >> 0x10);
          iVar8 = *piVar14 >> 0x10;
          iVar6 = *(int *)(&DAT_000df82c + iVar7);
LAB_0005d4f6:
          draw_sprite_world(iVar6 >> 0x10,iVar8,(int)sVar5,0,0);
        }
      }
      else if ((-1 < (short)(&unk_df836)[iVar6 * 0x40]) || (sVar5 == 0x10)) {
        if ((*(int *)(&DAT_000df82c + iVar7) >> 0x10 != -1) &&
           (*(short *)((int)&DAT_000df884 + iVar7 + 2) < 0xc)) {
          sVar5 = *(short *)((int)&DAT_000df884 + iVar7 + 2);
          if (((*(char *)CONCAT22(p_puck_carrier._2_2_,(undefined2)p_puck_carrier) == sVar5) ||
              (sVar5 == sStack_28)) || (sVar5 == sStack_24)) {
            iVar9 = *(int *)(&DAT_000df834 + iVar6 * 0x40) >> 0x10;
            uVar2 = (&DAT_000df87a)[iVar7];
            iVar3 = (&unk_df820)[iVar6 * 0x20];
            iVar8 = *piVar14;
          }
          else {
            if (show_names == 0) goto LAB_0005d416;
            uVar2 = (&DAT_000df87a)[iVar7];
            iVar3 = (&unk_df820)[iVar6 * 0x20];
            iVar8 = *piVar14;
            iVar9 = -1;
          }
          draw_player_number(iVar8 >> 0x10,iVar3 >> 0x10,uVar2,iVar9);
        }
LAB_0005d416:
        draw_sprite_world(*(int *)(&DAT_000df82c + iVar7) >> 0x10,*piVar14 >> 0x10,
                          (int)(&unk_df820)[iVar6 * 0x20] >> 0x10,
                          (*(byte *)((int)&DAT_000df870 + iVar7 + 1) & 8) != 0,
                          5 < *(short *)((int)&DAT_000df884 + iVar7 + 2));
        if ((*(short *)((int)&DAT_000df884 + iVar7 + 2) == 0xc) &&
           (*(char *)CONCAT22(p_puck_carrier._2_2_,(undefined2)p_puck_carrier) != '\x10')) {
          sVar5 = *p_puck_x;
          if (sVar5 < 0) {
            iVar7 = -(int)sVar5;
          }
          else {
            iVar7 = (int)sVar5;
          }
          if ((iVar7 == 6) && (*p_puck_y == 0xf0)) {
LAB_0005d4c0:
            sVar5 = *p_puck_y + (short)((*p_puck_z * 3) / 2);
            iVar8 = (int)*p_puck_x;
            iVar6 = _dword_dff2c;
            goto LAB_0005d4f6;
          }
          if (((int)*p_puck_y <= ((int)(&unk_df820)[iVar6 * 0x20] >> 0x10) + 6) && (0xc < *p_puck_z)
             ) {
            iVar6 = (int)*p_puck_x - (*piVar14 >> 0x10);
            if (iVar6 < 0) {
              iVar6 = -iVar6;
            }
            if (iVar6 < 0x18) goto LAB_0005d4c0;
          }
        }
      }
    }
LAB_0005d500:
  }
  if ((*p_puck_y < -0xe7) && (-0xed < *p_puck_y)) {
    sVar15 = *p_puck_x;
    if (sVar15 < 0) {
      iVar6 = -(int)sVar15;
    }
    else {
      iVar6 = (int)sVar15;
    }
    if ((iVar6 < 0x15) && (0xc < *p_puck_z)) {
      draw_sprite_world(_dword_dff2c >> 0x10,(int)*p_puck_x,
                        (int)(short)((short)((*p_puck_z * 3) / 2) + *p_puck_y),0,0);
    }
  }
  if (camera._2_2_ < -0xb0) {
    setclip(dword_d30bc,dword_d30c0,dword_d30b0,uStack_18);
  }
  if (camera._2_2_ < -0x90) {
    sub_11136();
  }
  if (((dword_dffa0 < 0) && (0x229 < dword_dffac._2_2_)) && (dword_dffac._2_2_ < 0x238)) {
    draw_sprite_world(dword_dffac >> 0x10,dword_dff9c >> 0x10,dword_dffa0 >> 0x10,0,0);
  }
  if ((*p_puck_y < -0x108) &&
     (*(char *)CONCAT22(p_puck_carrier._2_2_,(undefined2)p_puck_carrier) < '\0')) {
    if (dword_dff24._2_2_ == 0) {
      iVar6 = dword_dff20 >> 0x10;
    }
    else {
      if (dword_dff24._2_2_ < 1) goto LAB_0005d684;
      iVar6 = (int)(short)((short)(((dword_dff24 >> 0x10) * 3) / 2) +
                          (short)((uint)dword_dff20 >> 0x10));
    }
    draw_sprite_world(_dword_dff2c >> 0x10,puck >> 0x10,iVar6,0,0);
  }
LAB_0005d684:
  if (-1 < dword_cbebe._2_2_) {
    draw_penalty_box_overlay();
  }
  if (_dword_cbec6 >> 0x10 != -1) {
    draw_message_box();
    if ((0 < (short)dword_cbeca) &&
       (dword_cbeca._0_2_ = (short)dword_cbeca + -1, (short)dword_cbeca < 1)) {
      dword_cbeca._0_2_ = 0;
      _dword_cbec6 = CONCAT22(0xffff,dword_cbec6);
    }
  }
  if ((((controller_type == '\x01') || (byte_c4d1d == '\x01')) && (_period_num != -1)) &&
     (controls_blocked == 0)) {
    sVar15 = sStack_24;
    if (controller_type == '\x01') {
      sVar15 = sStack_28;
    }
    if (sVar15 != -1) {
      if ((dword_d3030 + -100) * (dword_d3030 + -100) +
          (dword_d302c + -0xa0) * (dword_d302c + -0xa0) < 0x9c4) {
        sVar4 = 0;
        sVar11 = 0;
        sVar5 = 8;
      }
      else {
        sVar5 = direction8((int)(short)((short)dword_d302c + -0xa0),
                           (int)(short)(100 - (short)dword_d3030));
        sVar11 = (short)((short)dword_d302c + -0xa0) >> 0xf;
        sVar11 = (short)(((short)dword_d302c + -0xa0 + sVar11 * -4) -
                        (ushort)((short)(sVar11 << 1) < 0)) >> 2;
        iVar6 = 100 - dword_d3030 >> 0x1f;
        sVar4 = (short)((int)(((100 - dword_d3030) + iVar6 * -4) - (uint)(iVar6 << 1 < 0)) >> 2);
      }
      if ((sVar5 < 5) || (7 < sVar5)) {
        uVar12 = 0;
      }
      else {
        uVar12 = 1;
      }
      draw_sprite_world(*(int *)(&unk_ccd4f + sVar5 * 4) >> 0x10,
                        (int)(short)(sVar11 + *(short *)((int)&entities + sVar15 * 0x80 + 2)),
                        (int)(short)(sVar4 + *(short *)((int)&unk_df820 + sVar15 * 0x80 + 2)),uVar12
                        ,0);
    }
  }
  return;
}


// ================================================================================================
// sub_5d7f7 @ 0x5d7f7 [__watcall]
// ================================================================================================

void __watcall sub_5d7f7(void)

{
  undefined4 *puVar1;
  short sVar2;
  
  __CHK(0xc);
  action_flags = action_flags & 0xfe;
  camera._0_2_ = 0;
  camera._2_2_ = 0;
  sub_5ba89();
  if ((game_flags & 2) != 0) {
    puVar1 = &entities;
    for (sVar2 = 0; sVar2 < 0xc; sVar2 = sVar2 + 1) {
      *(byte *)(puVar1 + 0x11) = *(byte *)(puVar1 + 0x11) ^ 0x80;
      puVar1 = puVar1 + 0x20;
    }
  }
  byte_c90c3 = 0xff;
  user2_slot._1_1_ = 0xff;
  return;
}


// ================================================================================================
// setup_faceoff @ 0x5d852 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall setup_faceoff(void)

{
  char cVar1;
  undefined2 uVar2;
  short sVar3;
  undefined4 *puVar4;
  int iVar5;
  int *piVar6;
  undefined4 uVar7;
  int iVar8;
  int iVar9;
  short unaff_DI;
  
  __CHK(0x18);
  set_state_reset(&puck,0x18);
  if (period_idx < 2) {
    uVar7 = 1;
    puVar4 = &puck;
  }
  else {
    dword_e03ba._2_2_ = 7;
    iVar5 = game_over_check(dword_df622 >> 0x10,dword_df722 >> 0x10);
    if (iVar5 != 0) {
      dword_e03ba._2_2_ = 8;
    }
    dword_e03be._2_2_ = dword_df622._2_2_ - dword_df722._2_2_;
    if (dword_e03be._2_2_ == 0) {
      if ((period_idx == 3) && ((option_flags._1_1_ & 2) != 0)) {
        clear_infractions();
        if ((crowd_noise._2_2_ < 0x4b1) &&
           (crowd_noise._2_2_ = crowd_noise._2_2_ + 900, 0x4b0 < crowd_noise._2_2_)) {
          crowd_noise._2_2_ = 0x4b0;
        }
        game_flags = game_flags | 0x41;
        excitement._2_2_ = excitement._2_2_ + 0x28;
        ram0x000e03aa = ram0x000e03aa & 0xffff;
        while (sVar3 = dword_e03ac, dword_e03ac < 0xc) {
          (&unk_df860)[((int)ram0x000e03aa >> 0x10) * 0x80] =
               (&unk_df860)[((int)ram0x000e03aa >> 0x10) * 0x80] & 0xf7;
          ram0x000e03aa = CONCAT22(sVar3 + 1,dword_e03a8._2_2_);
        }
        uVar7 = 2;
      }
      else {
        uVar7 = 1;
      }
      puVar4 = &entities;
    }
    else {
      user2_slot = 0xffff;
      _user1_slot = 0xffff;
      *p_puck_carrier = 0xff;
      if ((&unk_dff3a)[dword_dff36 >> 0x10] == '\x18') {
        set_state(&puck,0x1a);
      }
      ram0x000e03aa = ram0x000e03aa & 0xffff;
      while (dword_e03ac < 0xc) {
        (&unk_df860)[((int)ram0x000e03aa >> 0x10) * 0x80] =
             (&unk_df860)[((int)ram0x000e03aa >> 0x10) * 0x80] & 0xf7;
        dword_e03ac = dword_e03ac + 1;
      }
      if (dword_e03be._2_2_ < 0) {
        iVar5 = 6;
      }
      else {
        iVar5 = 0;
      }
      piVar6 = &entities + iVar5 * 0x20;
      play_crowd_chant(dword_e03be._2_2_ < 0);
      if (dword_e03ba._2_2_ == 8) {
        byte_ccca0 = 1;
        game_flags = game_flags | 0x80;
        set_state_reset(&dword_dff9c,0x2b);
        iVar9 = 40000;
        unaff_DI = *(short *)((int)&DAT_000df884 + iVar5 * 0x80 + 2);
        ram0x000e03aa = ram0x000e03aa & 0xffff;
        while (dword_e03ac < 6) {
          if (0 < *(short *)((int)piVar6 + 0x1a)) {
            iVar5 = (*piVar6 >> 0x10) + 0x91;
            iVar8 = (piVar6[1] >> 0x10) + -6;
            iVar5 = iVar5 * iVar5 + iVar8 * iVar8;
            if (iVar5 <= iVar9) {
              unaff_DI = *(short *)((int)piVar6 + 0x6a);
              iVar9 = iVar5;
            }
          }
          dword_e03ac = dword_e03ac + 1;
          piVar6 = piVar6 + 0x20;
        }
      }
      if (dword_e03be._2_2_ < 0) {
        iVar5 = 6;
      }
      else {
        iVar5 = 0;
      }
      puVar4 = &entities + iVar5 * 0x20;
      _last_shooter = 0xffff;
      dword_e03be._2_2_ = 0;
      ram0x000e03aa = CONCAT22(6,dword_e03a8._2_2_);
      do {
        if (*(short *)((int)puVar4 + 0x1a) < 1) {
          if (*(short *)((int)puVar4 + 0x1a) < 0) {
            iVar5 = puVar4[0x1b];
            cVar1 = *(char *)(iVar5 + 0xb6);
            if (-1 < cVar1) {
              if (dword_e03be._2_2_ == 0) {
                uVar2 = 5;
              }
              else {
                uVar2 = 3;
              }
              *(undefined2 *)((int)puVar4 + 0x1a) = uVar2;
              dword_e03be._2_2_ = dword_e03be._2_2_ + 1;
              set_state_reset(puVar4,7);
              put_player_on_ice(puVar4,(int)(short)cVar1);
              sVar3 = 1;
              while( true ) {
                cVar1 = *(char *)(iVar5 + 0xb6 + (int)sVar3);
                *(char *)(iVar5 + 0xb5 + (int)sVar3) = cVar1;
                if (cVar1 < '\0') break;
                sVar3 = sVar3 + 1;
              }
            }
          }
        }
        else {
          if ((dword_e03ba._2_2_ == 8) && (unaff_DI == *(short *)((int)puVar4 + 0x6a))) {
            set_state_reset(puVar4,8);
            uVar7 = 0x2a;
          }
          else {
            uVar7 = 7;
          }
          set_state_reset(puVar4,uVar7);
        }
        puVar4 = puVar4 + 0x20;
        sVar3 = dword_e03ac + -1;
        ram0x000e03aa = CONCAT22(sVar3,dword_e03a8._2_2_);
      } while (sVar3 != 0);
      clear_infractions();
      if (dword_df722._2_2_ < dword_df622._2_2_) {
        if ((crowd_noise._2_2_ < 0x5dd) &&
           (crowd_noise._2_2_ = crowd_noise._2_2_ + 1000, 0x5dc < crowd_noise._2_2_)) {
          crowd_noise._2_2_ = 0x5dc;
        }
        if (dword_e03ba._2_2_ == 8) {
          crowd_noise._2_2_ = crowd_noise._2_2_ + 800;
        }
      }
      else if (crowd_noise._2_2_ < 800) {
        crowd_noise._2_2_ = 800;
      }
      game_flags = game_flags | 0x41;
      excitement._2_2_ = excitement._2_2_ + 0x28;
      uVar7 = 2;
    }
  }
  queue_infraction(puVar4,uVar7);
  return;
}


// ================================================================================================
// game_clock_tick @ 0x5dc10 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall game_clock_tick(void)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 uStackY_14;
  
  __CHK(0x14);
  if (penalty_shot_active != 0) {
    dword_cc120 = dword_cc120 + -1;
    if (0 < dword_cc120) {
      return;
    }
    uStackY_14 = 0x5dc41;
    end_penalty_shot();
    return;
  }
  if ((clock_seconds == 0) && (clock_sub == 0)) {
    return;
  }
  if (-1 < (short)(clock_sub + -1)) {
    clock_sub = clock_sub + -1;
    return;
  }
  if (clock_seconds < 1) {
    clock_sub = 0;
  }
  else {
    _period_idx = CONCAT22(clock_seconds + -1,period_idx);
    clock_sub = clock_sub + 0x17;
  }
  if ((clock_seconds == 0x3d) || (puVar2 = (undefined4 *)&stack0xfffffff0, clock_seconds == 0x3c)) {
    if ((sound_enabled == '\0') || ((option_flags._1_1_ & 1) == 0)) {
      uStackY_14 = 0x5dcd1;
      play_sfx(0x97);
      puVar2 = (undefined4 *)&stack0xfffffff0;
    }
    else {
      puVar2 = (undefined4 *)&stack0xfffffff0;
      if (clock_seconds == 0x3c) {
        dword_e9a9e = CONCAT22(input_enabled,(undefined2)dword_e9a9e);
        _input_enabled = 0;
        puVar2 = &uStackY_14;
        uStackY_14 = 0x5dcf8;
        speech_period_summary();
        _input_enabled = dword_e9a9e >> 0x10;
      }
    }
  }
  iVar1 = (_period_idx >> 0x10) / 0x3c;
  if ((_period_idx >> 0x10) % 0x3c == 0) {
    if ((_period_num != 3) ||
       ((((iVar1 = CONCAT22((short)((uint)iVar1 >> 0x10),clock_seconds), clock_seconds != 0x3c &&
          (clock_seconds != 0x78)) && (clock_seconds != 0xb4)) &&
        ((clock_seconds != 300 && (clock_seconds != 600)))))) {
      if (_period_num != 2) {
        return;
      }
      if (clock_seconds != 600) {
        return;
      }
    }
    *(undefined4 *)((int)puVar2 + -4) = 0x5dd66;
    time_announcements(iVar1);
    return;
  }
  return;
}


// ================================================================================================
// sort_draw_order @ 0x5dd6b [__watcall]
// ================================================================================================

void __watcall sort_draw_order(void)

{
  char cVar1;
  char cVar2;
  undefined2 uVar3;
  bool bVar4;
  undefined2 *puVar5;
  char *pcVar6;
  char *pcVar7;
  undefined4 *puVar8;
  short sVar9;
  short sVar10;
  
  __CHK(4);
  action_flags = action_flags & 0x7f;
  __CHK(0x20);
  puVar8 = &entities;
  puVar5 = (undefined2 *)&draw_order_keys;
  for (sVar9 = 0; sVar9 < 0x11; sVar9 = sVar9 + 1) {
    if ((action_flags & 0x80) == 0) {
      uVar3 = *(undefined2 *)((int)puVar8 + 6);
    }
    else {
      uVar3 = *(undefined2 *)((int)puVar8 + 2);
    }
    *puVar5 = uVar3;
    puVar8 = puVar8 + 0x20;
    puVar5 = puVar5 + 1;
  }
  do {
    bVar4 = false;
    pcVar7 = &unk_e9ade;
    sVar9 = 0;
    for (sVar10 = 0; sVar10 < 0x10; sVar10 = sVar10 + 1) {
      cVar1 = *pcVar7;
      pcVar6 = pcVar7 + 1;
      cVar2 = *pcVar6;
      if (*(short *)(&draw_order_keys + *pcVar6 * 2) < *(short *)(&draw_order_keys + *pcVar7 * 2)) {
        *pcVar6 = cVar1;
        *pcVar7 = cVar2;
        (&draw_order_pos)[(short)cVar1] = sVar9 + 1;
        (&draw_order_pos)[(short)cVar2] = sVar9;
        bVar4 = true;
      }
      pcVar7 = pcVar6;
      sVar9 = sVar9 + 1;
    }
  } while (bVar4);
  return;
}


// ================================================================================================
// sort_draw_order2 @ 0x5dd7c [__watcall]
// ================================================================================================

void __watcall sort_draw_order2(void)

{
  char cVar1;
  char cVar2;
  undefined2 uVar3;
  bool bVar4;
  undefined2 *puVar5;
  char *pcVar6;
  char *pcVar7;
  undefined4 *puVar8;
  short sVar9;
  short sVar10;
  
  __CHK(0x20);
  puVar8 = &entities;
  puVar5 = (undefined2 *)&draw_order_keys;
  for (sVar9 = 0; sVar9 < 0x11; sVar9 = sVar9 + 1) {
    if ((action_flags & 0x80) == 0) {
      uVar3 = *(undefined2 *)((int)puVar8 + 6);
    }
    else {
      uVar3 = *(undefined2 *)((int)puVar8 + 2);
    }
    *puVar5 = uVar3;
    puVar8 = puVar8 + 0x20;
    puVar5 = puVar5 + 1;
  }
  do {
    bVar4 = false;
    pcVar7 = &unk_e9ade;
    sVar9 = 0;
    for (sVar10 = 0; sVar10 < 0x10; sVar10 = sVar10 + 1) {
      cVar1 = *pcVar7;
      pcVar6 = pcVar7 + 1;
      cVar2 = *pcVar6;
      if (*(short *)(&draw_order_keys + *pcVar6 * 2) < *(short *)(&draw_order_keys + *pcVar7 * 2)) {
        *pcVar6 = cVar1;
        *pcVar7 = cVar2;
        (&draw_order_pos)[(short)cVar1] = sVar9 + 1;
        (&draw_order_pos)[(short)cVar2] = sVar9;
        bVar4 = true;
      }
      pcVar7 = pcVar6;
      sVar9 = sVar9 + 1;
    }
  } while (bVar4);
  return;
}


// ================================================================================================
// sub_5dd9e @ 0x5dd9e [__watcall]
// ================================================================================================

void __watcall sub_5dd9e(void)

{
  __CHK(4);
  if (game_over == 0) {
    game_over = 1;
  }
  return;
}


// ================================================================================================
// end_period_flag @ 0x5ddbc [__watcall]
// ================================================================================================

void __watcall end_period_flag(void)

{
  __CHK(4);
  if (period_over == 0) {
    period_over = 1;
  }
  return;
}


// ================================================================================================
// sub_5ddda @ 0x5ddda [__watcall]
// ================================================================================================

void __watcall sub_5ddda(void)

{
  short sVar1;
  undefined4 uVar2;
  int extraout_EDX;
  int iVar3;
  
  __CHK(0x10);
  count_penalized();
  uVar2 = 0xdf614;
  iVar3 = 0xdf714;
  for (sVar1 = 0; sVar1 < 2; sVar1 = sVar1 + 1) {
    sub_5b826(uVar2);
    *(undefined2 *)(extraout_EDX + 0x2a) = 0;
    if ((((byte)option_flags & 4) != 0) &&
       (*(short *)(extraout_EDX + 0x36) != *(short *)(iVar3 + 0x36))) {
      if ((short)(*(short *)(extraout_EDX + 0x36) - *(short *)(iVar3 + 0x36)) < 1) {
        *(undefined2 *)(extraout_EDX + 0x2a) = 6;
      }
      else {
        *(undefined2 *)(extraout_EDX + 0x2a) = 4;
      }
    }
    uVar2 = 0xdf714;
    iVar3 = 0xdf614;
  }
  return;
}


// ================================================================================================
// sub_5de42 @ 0x5de42 [__watcall]
// ================================================================================================

void __watcall sub_5de42(void)

{
  short sVar1;
  
  __CHK(0xc);
  sub_5ddda();
  for (sVar1 = 0; sVar1 < 0x11; sVar1 = sVar1 + 1) {
    *(undefined2 *)((int)&entities + sVar1 * 0x80 + 2) = 0;
  }
  return;
}


// ================================================================================================
// period_cleanup @ 0x5de70 [__watcall]
// ================================================================================================

void __watcall period_cleanup(void)

{
  __CHK(4);
  if (period_idx != 4) {
    sub_5de42();
    if (0 < period_idx) {
      sub_10f6d();
    }
    period_init();
    sub_510a9();
    return;
  }
  __CHK(4);
  if (game_over == 0) {
    game_over = 1;
  }
  return;
}


// ================================================================================================
// end_of_period @ 0x5dea6 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall end_of_period(void)

{
  short sVar1;
  byte bVar2;
  short sVar3;
  
  __CHK(0x14);
  word_cbc54 = 0;
  word_cbc52 = 0;
  word_cbc58 = 0;
  word_cbc56 = 0;
  word_cbc64 = 0xffff;
  word_cbc62 = 0xffff;
  word_cbc6c = 0;
  word_cbc6a = 0;
  bVar2 = game_flags;
  if (_penalty_box_mode >> 0x10 != -1) {
    bVar2 = game_flags ^ 2;
    sVar3 = period_idx + 1;
    sVar1 = period_idx + -2;
    period_idx = sVar3;
    if (2 < sVar3) {
      if (sVar3 == 3 || SBORROW2(sVar3,3) != sVar1 < 0) {
        if ((option_flags._1_1_ & 2) != 0) {
          bVar2 = game_flags;
        }
      }
      else {
        period_idx = 3;
        if ((option_flags._1_1_ & 2) != 0) {
          period_idx = 4;
        }
      }
      game_flags = bVar2;
      dword_e03ba._2_2_ = dword_df622._2_2_ - dword_df722._2_2_;
      bVar2 = game_flags;
      if (dword_e03ba._2_2_ != 0) {
        period_idx = 4;
      }
    }
  }
  game_flags = bVar2;
  period_cleanup();
  return;
}


// ================================================================================================
// count_penalized @ 0x5df86 [__watcall]
// ================================================================================================

void __watcall count_penalized(void)

{
  int iVar1;
  int iVar2;
  short sVar3;
  short sVar4;
  
  __CHK(0x18);
  iVar2 = 0xdf614;
  for (sVar4 = 0; sVar4 < 2; sVar4 = sVar4 + 1) {
    (&penalized_count)[sVar4] = 0;
    for (sVar3 = 0x1b; -1 < sVar3; sVar3 = sVar3 + -1) {
      iVar1 = sVar3 * 2 + iVar2;
      if ((short)*(ushort *)(iVar1 + 0x7e) < 1) {
        if (-3 < *(int *)(iVar1 + 0x7c) >> 0x10) {
          *(undefined2 *)(iVar1 + 0x7e) = 0xfffe;
          *(undefined *)(*(int *)(iVar2 + 0xee) + sVar3 * 0x27) = 3;
        }
      }
      else if (((*(byte *)(iVar1 + 0x7f) & 0x10) == 0) || ((*(ushort *)(iVar1 + 0x7e) & 0x7ff) != 0)
              ) {
        (&penalized_count)[sVar4] = (&penalized_count)[sVar4] + '\x01';
      }
    }
    iVar2 = 0xdf714;
  }
  return;
}


// ================================================================================================
// reset_players_for_faceoff @ 0x5e01a [__watcall]
// ================================================================================================

void __watcall reset_players_for_faceoff(void)

{
  short sVar1;
  int iVar2;
  short sVar3;
  
  __CHK(0x14);
  iVar2 = 0xdf614;
  for (sVar3 = 0; sVar3 < 2; sVar3 = sVar3 + 1) {
    *(byte *)(iVar2 + 0x44) = *(byte *)(iVar2 + 0x44) & 0xef;
    iVar2 = *(int *)(iVar2 + 0xf6);
    for (sVar1 = 0; sVar1 < 6; sVar1 = sVar1 + 1) {
      *(undefined *)(iVar2 + 0x45) = 0;
      if (-1 < *(short *)(iVar2 + 0x1a)) {
        set_animation(iVar2,0x289);
        *(undefined2 *)(iVar2 + 0x3e) = 0;
        *(undefined2 *)(iVar2 + 0x18) = *(undefined2 *)(iVar2 + 0x3e);
        *(byte *)(iVar2 + 0x44) = *(byte *)(iVar2 + 0x44) & 0xc2;
      }
      iVar2 = iVar2 + 0x80;
    }
    iVar2 = 0xdf714;
  }
  return;
}


// ================================================================================================
// sub_5e086 @ 0x5e086 [__watcall]
// ================================================================================================

void __watcall sub_5e086(void)

{
  __CHK(8);
  sub_5cd4f();
  sub_5b881();
  period_idx = 0;
  sub_5b97a();
  period_cleanup();
  return;
}


// ================================================================================================
// sub_5e0b0 @ 0x5e0b0 [__watcall]
// ================================================================================================

void __watcall sub_5e0b0(void)

{
  int iVar1;
  short sVar2;
  
  __CHK(4);
  apply_line_change(0xdf614);
  dress_line(0xdf614);
  apply_line_change(0xdf714);
  __CHK(0x14);
  sVar2 = 6;
  iVar1 = dword_df80a;
  do {
    *(short *)(iVar1 + 0x1a) = (short)*(char *)(iVar1 + 0x42);
    if (-1 < *(char *)(iVar1 + 0x42)) {
      set_default_state(iVar1);
      if (*(short *)(iVar1 + 0x1a) == 4) {
        set_state_reset(iVar1,0x11);
      }
      (&DAT_000df792)[*(int *)(iVar1 + 0x40) >> 0x18] = 0xffff;
      *(undefined *)(dword_df802 + (*(int *)(iVar1 + 0x40) >> 0x18) * 0x27) = 4;
      put_player_on_ice(iVar1,*(int *)(iVar1 + 0x40) >> 0x18);
    }
    *(undefined *)(iVar1 + 0x43) = 0xff;
    *(undefined *)(iVar1 + 0x42) = 0xff;
    iVar1 = iVar1 + 0x80;
    sVar2 = sVar2 + -1;
  } while (sVar2 != 0);
  return;
}


// ================================================================================================
// dress_line @ 0x5e0dd [__watcall]
// ================================================================================================

void __watcall dress_line(int param_1)

{
  int iVar1;
  short sVar2;
  
  __CHK(0x14);
  iVar1 = *(int *)(param_1 + 0xf6);
  sVar2 = 6;
  do {
    *(short *)(iVar1 + 0x1a) = (short)*(char *)(iVar1 + 0x42);
    if (-1 < *(char *)(iVar1 + 0x42)) {
      set_default_state(iVar1);
      if (*(short *)(iVar1 + 0x1a) == 4) {
        set_state_reset(iVar1,0x11);
      }
      *(undefined2 *)(param_1 + 0x7e + (*(int *)(iVar1 + 0x40) >> 0x18) * 2) = 0xffff;
      *(undefined *)(*(int *)(param_1 + 0xee) + (*(int *)(iVar1 + 0x40) >> 0x18) * 0x27) = 4;
      put_player_on_ice(iVar1,*(int *)(iVar1 + 0x40) >> 0x18);
    }
    *(undefined *)(iVar1 + 0x43) = 0xff;
    *(undefined *)(iVar1 + 0x42) = 0xff;
    iVar1 = iVar1 + 0x80;
    sVar2 = sVar2 + -1;
  } while (sVar2 != 0);
  return;
}


// ================================================================================================
// apply_skating @ 0x5e16d [__watcall]
// ================================================================================================

void __watcall apply_skating(int param_1,ushort unaff_DX)

{
  short sVar1;
  ushort uVar2;
  int iVar3;
  int iVar4;
  undefined2 uVar5;
  short sVar6;
  short sStackY_18;
  
  __CHK(0x20);
  if (*(short *)(param_1 + 0x1a) == 0) {
    goalie_move(param_1,(int)(short)unaff_DX);
    return;
  }
  if ((*(byte *)(param_1 + 0x44) & 0x10) == 0) {
    if (*(short *)(param_1 + 0x6a) == 0x10) {
      if ((whistle_timer == 0) &&
         (((game_flags & 1) != 0 || ((((byte)stop_flags & 0x80) == 0 && ((game_flags & 8) == 0))))))
      {
        uVar5 = 0xa5b;
      }
      else {
        uVar5 = 0xb4b;
      }
    }
    else {
      uVar5 = 0x289;
    }
  }
  else {
    uVar5 = 0x529;
  }
  unaff_DX = unaff_DX & 0xf;
  if (7 < unaff_DX) {
    if ((unaff_DX == 9) &&
       (*(int *)(param_1 + 0xc) >> 0x10 != 0 || *(int *)(param_1 + 10) >> 0x10 != 0)) {
      stop_skating(param_1);
      return;
    }
    if ((*(byte *)(param_1 + 0x45) & 2) != 0) {
      return;
    }
    set_animation(param_1,uVar5);
    return;
  }
  if ((short)*p_puck_carrier != *(short *)(param_1 + 0x6a)) {
    sStackY_18 = *p_puck_x - *(short *)(param_1 + 2);
    sVar1 = *(short *)(param_1 + 6);
    sVar6 = ((short)(char)p_puck_vy[1] + *p_puck_y) - sVar1;
    uVar2 = unaff_DX;
    if ((*(byte *)(param_1 + 0x44) & 0x80) == 0) {
      sStackY_18 = -sStackY_18;
      sVar1 = -sVar1;
      sVar6 = -sVar6;
      uVar2 = unaff_DX ^ 4;
    }
    if ((((*(byte *)(param_1 + 0x44) & 0x10) != 0) ||
        (((sVar1 < 0 && (uVar2 == 4)) &&
         (sVar1 = direction8((int)sStackY_18,(int)sVar6), ((int)sVar1 + 1U & 7) < 3)))) &&
       (((*(byte *)(param_1 + 0x44) & 0x10) == 0 ||
        ((((char)uVar2 - 3U & 7) < 3 &&
         (sVar1 = direction8((int)sStackY_18,(int)sVar6), ((int)sVar1 + 2U & 7) < 5)))))) {
      if ((((*(byte *)(param_1 + 0x44) & 0x10) == 0) && (*(short *)(param_1 + 0x6a) != 0x10)) &&
         (((game_flags & 1) == 0 &&
          (((int)(*(uint *)(param_1 + 0xc) | *(uint *)(param_1 + 10)) >> 0x10 == 0 ||
           (sVar1 = direction8(), (((int)sVar1 - (int)(short)unaff_DX) + 1U & 7) < 3)))))) {
        *(byte *)(param_1 + 0x44) = *(byte *)(param_1 + 0x44) | 0x10;
      }
      goto LAB_0005e334;
    }
  }
  *(byte *)(param_1 + 0x44) = *(byte *)(param_1 + 0x44) & 0xef;
LAB_0005e334:
  uVar2 = unaff_DX - *(short *)(param_1 + 0x36) & 7;
  if (*(int *)(&unk_ccd78 + (short)uVar2 * 4) != 0) {
    iVar4 = *(int *)(param_1 + 10) >> 0x10;
    iVar3 = *(int *)(param_1 + 0xc) >> 0x10;
    dword_e03ae._2_2_ = (ushort)((uint)(iVar3 * iVar3 + iVar4 * iVar4) >> 0x10);
    dword_e03b2._0_2_ = (short)dword_e03ae._2_2_ >> 0xf;
    dword_e03b2._2_2_ = 0x300 - dword_e03ae._2_2_;
    if (dword_e03b2._2_2_ < 0x180) {
      dword_e03b2._2_2_ = 0x180;
    }
    iVar3 = (int)dword_e03b2._2_2_ * *(int *)(&unk_ccd78 + (short)uVar2 * 4);
    if ((*(byte *)(param_1 + 0x44) & 0x10) != 0) {
      iVar3 = -iVar3;
    }
    dword_e03b6._0_2_ = (undefined2)((uint)iVar3 >> 0x10);
    dword_e03b2._2_2_ = (short)iVar3;
    *(int *)(param_1 + 0x34) = *(int *)(param_1 + 0x34) + iVar3;
    *(ushort *)(param_1 + 0x36) = *(ushort *)(param_1 + 0x36) & 7;
    if (0x14 < dword_e03ae._2_2_) {
      if (((*(byte *)(param_1 + 0x55) & 8) != 0) == *(int *)(&unk_ccd78 + (short)uVar2 * 4) < 0) {
        if (*(short *)(param_1 + 0x6a) == 0x10) {
          if ((whistle_timer == 0) &&
             (((game_flags & 1) != 0 ||
              ((((byte)stop_flags & 0x80) == 0 && ((game_flags & 8) == 0)))))) {
            uVar5 = 0xad3;
          }
          else {
            uVar5 = 0xbc3;
          }
        }
        else {
          uVar5 = 0x349;
        }
      }
      else if (*(short *)(param_1 + 0x6a) == 0x10) {
        if ((whistle_timer == 0) &&
           (((game_flags & 1) != 0 || ((((byte)stop_flags & 0x80) == 0 && ((game_flags & 8) == 0))))
           )) {
          uVar5 = 0xabb;
        }
        else {
          uVar5 = 0xbab;
        }
      }
      else {
        uVar5 = 0x331;
      }
      *(byte *)(param_1 + 0x45) = *(byte *)(param_1 + 0x45) | 2;
    }
    set_animation(param_1,uVar5);
    if (2 < dword_e03ae._2_2_) {
      if ((*(byte *)(param_1 + 0x44) & 0x10) == 0) {
        uVar2 = (ushort)((uint)*(undefined4 *)(param_1 + 0x34) >> 0x10);
      }
      else {
        uVar2 = *(ushort *)(param_1 + 0x36) ^ 4;
      }
      skating_accelerate(param_1,(int)(short)uVar2);
    }
    return;
  }
  skating_turn(param_1,(int)(short)uVar2,*(int *)(param_1 + 0x34) >> 0x10);
  return;
}


// ================================================================================================
// ai_ref_positioning @ 0x5e4c4 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall ai_ref_positioning(int *param_1)

{
  short sVar1;
  int iVar2;
  undefined4 *puVar3;
  short sVar4;
  short sVar5;
  short sVar6;
  short sVar7;
  bool bVar8;
  short sStackY_1c;
  
  __CHK(0x30);
  if ((*(byte *)((int)param_1 + 0x45) & 0x20) != 0) {
    return;
  }
  if (*(short *)((int)param_1 + 6) < 0) {
    sVar5 = -(short)((uint)param_1[1] >> 0x10);
  }
  else {
    sVar5 = (short)((uint)param_1[1] >> 0x10);
  }
  if ((0xa2 < sVar5) && (0xf2 < sVar5)) {
    if (*(short *)((int)param_1 + 2) < 0) {
      iVar2 = -(*param_1 >> 0x10);
    }
    else {
      iVar2 = *param_1 >> 0x10;
    }
    if (iVar2 < 0x32) {
      if (*(short *)((int)param_1 + 6) < 1) {
        if (*(short *)((int)param_1 + 0xe) < 0) {
          if (*(short *)((int)param_1 + 2) < 0) {
            dword_e03ba._2_2_ = 5;
            return;
          }
          dword_e03ba._2_2_ = 3;
          return;
        }
      }
      else if (0 < *(short *)((int)param_1 + 0xe)) {
        if (*(short *)((int)param_1 + 2) < 0) {
          dword_e03ba._2_2_ = 7;
          return;
        }
        dword_e03ba._2_2_ = 1;
        return;
      }
      if (*(short *)((int)param_1 + 2) < 0) {
        dword_e03ba._2_2_ = 6;
        return;
      }
      dword_e03ba._2_2_ = 2;
      return;
    }
  }
  sStackY_1c = 100;
  puVar3 = &entities;
  sVar5 = 0;
  do {
    if (0xe < sVar5) {
      return;
    }
    if (((sVar5 != 0xc) && (sVar5 != 0xd)) && ((sVar5 != 0xe || (0x50 < sStackY_1c)))) {
      sVar4 = *(short *)((int)param_1 + 2) - *(short *)((int)puVar3 + 2);
      sVar6 = sVar4 + ((short)*(char *)((int)param_1 + 0xd) - (short)*(char *)((int)puVar3 + 0xd));
      if (sVar6 < 0) {
        sVar6 = -sVar6;
      }
      unique0x100000f9 = CONCAT22(sVar6,(short)ram0x000e03aa);
      if (sVar6 < 0x29) {
        sVar7 = *(short *)((int)param_1 + 6) - *(short *)((int)puVar3 + 6);
        sVar1 = ((short)*(char *)((int)param_1 + 0xf) - (short)*(char *)((int)puVar3 + 0xf)) + sVar7
        ;
        if (sVar1 < 0) {
          sVar1 = -sVar1;
        }
        dword_e03be = CONCAT22(sVar1,(short)dword_e03be);
        if ((sVar1 < 0x29) && ((int)sVar1 + (int)sVar6 < (int)sStackY_1c)) {
          sStackY_1c = sVar6 + sVar1;
          dword_e03ba._2_2_ = direction8((int)sVar4,(int)sVar7);
          if (*param_1 >> 0x10 < -0x82) {
            if (4 < (short)dword_e03ba._2_2_) {
              bVar8 = SBORROW2(dword_e03ba._2_2_,8);
              sVar6 = dword_e03ba._2_2_ - 8;
LAB_0005e6eb:
              if (bVar8 != sVar6 < 0) {
                if (*(short *)((int)puVar3 + 0xe) == 0) {
                  dword_e03ba._2_2_ = 0;
                }
                else {
                  dword_e03ba._2_2_ = 4;
                }
              }
            }
          }
          else if (*(short *)((int)param_1 + 2) < 0x83) {
            if ((*param_1 >> 0x10 < -99) || (-1 < *(short *)((int)param_1 + 2))) {
              if ((*(short *)((int)param_1 + 2) < 100) &&
                 (((-1 < *(short *)((int)param_1 + 2) && (4 < (short)dword_e03ba._2_2_)) &&
                  ((short)dword_e03ba._2_2_ < 8)))) {
                if ((dword_e03ba._2_2_ == 6) && (*(short *)((int)puVar3 + 0xe) != 0)) {
                  dword_e03ba._2_2_ = (-1 < sVar7) + 3;
                }
                else {
                  dword_e03ba._2_2_ = (ushort)(0 < sVar7);
                }
              }
            }
            else if ((0 < (short)dword_e03ba._2_2_) && ((short)dword_e03ba._2_2_ < 4)) {
              if ((dword_e03ba._2_2_ == 2) && (*(short *)((int)puVar3 + 0xe) != 0)) {
                dword_e03ba._2_2_ = (sVar7 < 0) + 4;
              }
              else if (sVar7 < 1) {
                dword_e03ba._2_2_ = 0;
              }
              else {
                dword_e03ba._2_2_ = 7;
              }
            }
          }
          else if (0 < (short)dword_e03ba._2_2_) {
            bVar8 = SBORROW2(dword_e03ba._2_2_,4);
            sVar6 = dword_e03ba._2_2_ - 4;
            goto LAB_0005e6eb;
          }
        }
      }
    }
    sVar5 = sVar5 + 1;
    puVar3 = puVar3 + 0x20;
  } while( true );
}


// ================================================================================================
// ai_near_carrier_check @ 0x5e7fe [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall ai_near_carrier_check(int param_1)

{
  short sVar1;
  int iVar2;
  short sVar3;
  int iVar4;
  short sVar5;
  
  __CHK(0x1c);
  if (-1 < *p_puck_carrier) {
    iVar2 = *p_puck_carrier * 0x80;
    sVar1 = *(short *)(param_1 + 2) - *(short *)((int)&entities + iVar2 + 2);
    sVar3 = ((short)*(char *)(param_1 + 0xd) - (short)*(char *)((int)&DAT_000df828 + iVar2 + 1)) +
            sVar1;
    ram0x000e03aa = CONCAT22(sVar3,dword_e03a8._2_2_);
    iVar4 = (int)sVar3;
    if (sVar3 < 0) {
      iVar4 = -iVar4;
    }
    if (iVar4 < 0x29) {
      sVar3 = *(short *)(param_1 + 6) - *(short *)((int)&unk_df820 + iVar2 + 2);
      sVar5 = ((short)*(char *)(param_1 + 0xf) - (short)*(char *)((int)&DAT_000df82a + iVar2 + 1)) +
              sVar3;
      dword_e03be = CONCAT22(sVar5,(undefined2)dword_e03be);
      iVar4 = (int)sVar5;
      if (sVar5 < 0) {
        iVar4 = -iVar4;
      }
      if (iVar4 < 0x29) {
        dword_e03be = CONCAT22(sVar3,(undefined2)dword_e03be);
        dword_e03ba._2_2_ = sVar1;
        dword_e03ba._2_2_ = direction8((int)sVar1,(int)sVar3);
        if (((byte)option_flags & 2) != 0) {
          if ((*(byte *)(param_1 + 0x44) & 0x80) == 0) {
            sVar1 = -(short)((uint)*(undefined4 *)(param_1 + 4) >> 0x10);
          }
          else {
            sVar1 = (short)((uint)*(undefined4 *)(param_1 + 4) >> 0x10);
          }
          sVar1 = sVar1 + -0x4e;
          dword_e03be = CONCAT22(sVar1,(undefined2)dword_e03be);
          if ((sVar1 < 0xb) && (-0x33 < sVar1)) {
            dword_e03be = CONCAT22(*(short *)(param_1 + 2),(undefined2)dword_e03be);
            if (*(short *)((int)&entities + iVar2 + 2) < *(short *)(param_1 + 2)) {
              dword_e03ba._2_2_ = 2;
            }
            else {
              dword_e03ba._2_2_ = 6;
            }
          }
        }
      }
    }
  }
  return;
}


// ================================================================================================
// ai_skate_towards @ 0x5e93b [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall ai_skate_towards(int *param_1,code *unaff_EDX)

{
  char cVar1;
  undefined2 uVar2;
  short sVar3;
  short sVar4;
  char cVar6;
  int iVar5;
  int iVar7;
  ushort uVar8;
  int iVar9;
  int extraout_EDX;
  int iVar10;
  int iVar11;
  
  __CHK(0x18);
  cVar1 = *(char *)((int)param_1 + 0x29);
  cVar6 = cVar1 + -1;
  *(char *)((int)param_1 + 0x29) = cVar6;
  if (-1 < cVar6) goto LAB_0005eb02;
  iVar9 = dword_e03ba >> 0x10;
  iVar7 = dword_e03be >> 0x10;
  *(char *)((int)param_1 + 0x29) = cVar1 + '\v';
  ai_choose_direction(param_1,iVar9);
  iVar9 = (*param_1 >> 0x10) + (*(int *)((int)param_1 + 10) >> 0x18);
  iVar11 = (param_1[1] >> 0x10) + (param_1[3] >> 0x18);
  dword_e03ba._2_2_ = dword_e03ba._2_2_ - (short)iVar9;
  dword_e03be._2_2_ = dword_e03be._2_2_ - (short)iVar11;
  iVar9 = extraout_EDX - iVar9;
  iVar7 = iVar7 - iVar11;
  if (iVar9 < 0) {
    iVar9 = -iVar9;
  }
  if (iVar7 < 0) {
    iVar7 = -iVar7;
  }
  iVar5 = (int)dword_e03ba._2_2_;
  iVar11 = iVar5;
  if (dword_e03ba._2_2_ < 0) {
    iVar11 = -iVar5;
  }
  iVar10 = (int)dword_e03be._2_2_;
  if (iVar11 < 0xd) {
    iVar11 = iVar10;
    if (dword_e03be._2_2_ < 0) {
      iVar11 = -iVar10;
    }
    if (((0xc < iVar11) || ((0xc < iVar9 && (*(short *)(param_1 + 3) == 0)))) ||
       ((0xc < iVar7 && (*(short *)((int)param_1 + 0xe) == 0)))) goto LAB_0005ea23;
    dword_e03ba = CONCAT22(9,(undefined2)dword_e03ba);
  }
  else {
LAB_0005ea23:
    uVar2 = direction8(iVar5,iVar10);
    dword_e03ba = CONCAT22(uVar2,(undefined2)dword_e03ba);
  }
  if (unaff_EDX != (code *)0x0) {
    (*unaff_EDX)();
  }
  *(undefined *)(param_1 + 10) = dword_e03ba._2_1_;
  if ((7 < dword_e03ba._2_2_) &&
     (*(int *)((int)param_1 + 10) >> 0x10 == 0 && param_1[3] >> 0x10 == 0)) {
    sVar3 = (short)camera_target_y;
    sVar4 = _camera_target_x;
    if ((byte_dff61 & 1) == 0) {
      sVar3 = *p_puck_y;
      sVar4 = *p_puck_x;
    }
    dword_e03ba._2_2_ = sVar4 - *(short *)((int)param_1 + 2);
    dword_e03be._2_2_ = sVar3 - *(short *)((int)param_1 + 6);
    sVar4 = direction8((int)dword_e03ba._2_2_,(int)dword_e03be._2_2_);
    uVar8 = *(short *)((int)param_1 + 0x36) - sVar4;
    dword_e03ba = CONCAT22(uVar8,(undefined2)dword_e03ba);
    if (uVar8 != 0) {
      *(ushort *)((int)param_1 + 0x36) =
           (((short)(uVar8 & 4) >> 1) + (short)((uint)param_1[0xd] >> 0x10)) - 1U & 7;
    }
  }
LAB_0005eb02:
  apply_skating(param_1,*(int *)((int)param_1 + 0x25) >> 0x18);
  return;
}


// ================================================================================================
// ai_chase_puck @ 0x5eb17 [__watcall]
// ================================================================================================

void __watcall ai_chase_puck(int *param_1)

{
  short sVar1;
  undefined2 uVar2;
  ushort uVar3;
  char cVar7;
  int iVar4;
  uint uVar5;
  int iVar6;
  short sVar8;
  short sVar9;
  
  __CHK(0x24);
  dword_e03ba._2_2_ = *p_puck_x + (short)((int)(char)p_puck_vx[1] >> 1);
  dword_e03be._2_2_ = *p_puck_y + (short)((int)(char)p_puck_vy[1] >> 1);
  cVar7 = *(char *)((int)param_1 + 0x29) + -1;
  *(char *)((int)param_1 + 0x29) = cVar7;
  uVar5 = CONCAT22((undefined2)dword_e03be,dword_e03ba._2_2_);
  if (cVar7 < '\0') {
    if (*(short *)((int)param_1 + 0x1a) == 0) {
      cVar7 = '\x05';
    }
    else {
      cVar7 = '\n';
    }
    *(char *)((int)param_1 + 0x29) = *(char *)((int)param_1 + 0x29) + cVar7;
    ai_choose_direction(param_1);
    sVar9 = dword_e03be._2_2_;
    sVar8 = dword_e03ba._2_2_;
    if (*p_puck_carrier < '\0') {
LAB_0005ec1e:
      frame_offsets_lookup(param_1);
      sVar8 = (sVar8 - ((short)*(char *)((int)param_1 + 0xd) + (short)dword_e03ba._2_1_)) -
              *(short *)((int)param_1 + 2);
      dword_e03ba._2_1_ = (char)sVar8;
      dword_e03ba._3_1_ = (undefined)((ushort)sVar8 >> 8);
      sVar9 = (sVar9 - ((short)*(char *)((int)param_1 + 0xf) + (short)dword_e03be._2_1_)) -
              *(short *)((int)param_1 + 6);
      dword_e03be._2_1_ = (char)sVar9;
      dword_e03be._3_1_ = (undefined)((ushort)sVar9 >> 8);
      iVar6 = CONCAT13(dword_e03be._3_1_,CONCAT12(dword_e03be._2_1_,(undefined2)dword_e03be));
      iVar4 = CONCAT13(dword_e03ba._3_1_,CONCAT12(dword_e03ba._2_1_,(undefined2)dword_e03ba));
      dword_e03ba._2_2_ = sVar8;
      dword_e03be._2_2_ = sVar9;
      sVar8 = direction8(iVar4 >> 0x10,iVar6 >> 0x10);
    }
    else {
      sVar1 = *(short *)p_puck_vx;
      if (sVar1 < 0) {
        iVar4 = -(int)sVar1;
      }
      else {
        iVar4 = (int)sVar1;
      }
      if (300 < iVar4) goto LAB_0005ec1e;
      sVar1 = *(short *)p_puck_vy;
      if (sVar1 < 0) {
        iVar4 = -(int)sVar1;
      }
      else {
        iVar4 = (int)sVar1;
      }
      if (300 < iVar4) goto LAB_0005ec1e;
      uVar5 = approx_distance((int)dword_e03ba._2_2_ - (*param_1 >> 0x10),
                              (short)((int)dword_e03be._2_2_ - (param_1[1] >> 0x10)));
      if (0x18 < uVar5) goto LAB_0005ec1e;
      sVar8 = (short)*(char *)((int)param_1 + 0x52);
    }
    dword_e03ba._2_1_ = (char)sVar8;
    dword_e03ba._3_1_ = (undefined)((ushort)sVar8 >> 8);
    *(char *)(param_1 + 10) = dword_e03ba._2_1_;
    uVar5 = CONCAT22((undefined2)dword_e03be,CONCAT11(dword_e03ba._3_1_,dword_e03ba._2_1_));
    if (*(short *)((int)param_1 + 0x1a) != 0) {
      uVar3 = direction8((int)*(short *)p_puck_vx,(int)*(short *)p_puck_vy);
      dword_e03ba._2_1_ = (char)(uVar3 ^ 4);
      dword_e03ba._3_1_ = (undefined)(uVar3 >> 8);
      if ((uVar3 ^ 4) == *(ushort *)((int)param_1 + 0x36)) {
        sVar8 = *(short *)p_puck_vx;
        if (sVar8 < 0) {
          iVar4 = -(int)sVar8;
        }
        else {
          iVar4 = (int)sVar8;
        }
        if (iVar4 < 4000) {
          sVar8 = *(short *)p_puck_vy;
          if (sVar8 < 0) {
            iVar4 = -(int)sVar8;
          }
          else {
            iVar4 = (int)sVar8;
          }
          if (iVar4 < 4000) goto LAB_0005ed0d;
        }
        sVar8 = randomrange(4);
        uVar5 = CONCAT22((undefined2)dword_e03be,CONCAT11(dword_e03ba._3_1_,dword_e03ba._2_1_));
        if (sVar8 != 0) goto LAB_0005ed9b;
      }
LAB_0005ed0d:
      sVar8 = *p_puck_x - *(short *)((int)param_1 + 2);
      dword_e03ba._2_1_ = (char)sVar8;
      dword_e03ba._3_1_ = (undefined)((ushort)sVar8 >> 8);
      sVar9 = *p_puck_y - *(short *)((int)param_1 + 6);
      dword_e03be._2_1_ = (char)sVar9;
      dword_e03be._3_1_ = (undefined)((ushort)sVar9 >> 8);
      iVar6 = CONCAT13(dword_e03be._3_1_,CONCAT12(dword_e03be._2_1_,(undefined2)dword_e03be));
      iVar4 = CONCAT13(dword_e03ba._3_1_,CONCAT12(dword_e03ba._2_1_,(undefined2)dword_e03ba));
      dword_e03ba._2_2_ = sVar8;
      dword_e03be._2_2_ = sVar9;
      sVar8 = direction8(iVar4 >> 0x10,iVar6 >> 0x10);
      uVar5 = CONCAT22((undefined2)dword_e03be,dword_e03ba._2_2_);
      if (sVar8 == *(short *)((int)param_1 + 0x36)) {
        iVar4 = CONCAT13(dword_e03ba._3_1_,CONCAT12(dword_e03ba._2_1_,(undefined2)dword_e03ba));
        iVar6 = imul32(iVar4 >> 0x10,(short)((uint)iVar4 >> 0x10));
        iVar4 = CONCAT13(dword_e03be._3_1_,CONCAT12(dword_e03be._2_1_,(undefined2)dword_e03be));
        iVar4 = imul32(iVar4 >> 0x10,(short)((uint)iVar4 >> 0x10));
        uVar5 = iVar6 + iVar4;
        dword_e03ba._2_1_ = (char)uVar5;
        dword_e03ba._3_1_ = (undefined)(uVar5 >> 8);
        dword_e03be._0_2_ = (undefined2)(uVar5 >> 0x10);
        if ((900 < uVar5) && (uVar5 < 0x5a5)) {
          lunge_for_puck(param_1);
          sVar8 = dword_e03be._2_2_;
          uVar2 = CONCAT11(dword_e03ba._3_1_,dword_e03ba._2_1_);
          goto LAB_0005e7f8;
        }
      }
    }
  }
LAB_0005ed9b:
  dword_e03be._0_2_ = (undefined2)(uVar5 >> 0x10);
  dword_e03ba._2_2_ = (short)uVar5;
  apply_skating(param_1,*(int *)((int)param_1 + 0x25) >> 0x18);
  sVar8 = dword_e03be._2_2_;
  uVar2 = dword_e03ba._2_2_;
LAB_0005e7f8:
  dword_e03ba._3_1_ = (undefined)((ushort)uVar2 >> 8);
  dword_e03ba._2_1_ = (char)uVar2;
  dword_e03be._3_1_ = (undefined)((ushort)sVar8 >> 8);
  dword_e03be._2_1_ = (char)sVar8;
  return;
}


// ================================================================================================
// skating_accelerate @ 0x5edad [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall skating_accelerate(int param_1,short unaff_DX)

{
  short sVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  __CHK(0x14);
  iVar5 = *(byte *)(param_1 + 0x57) + 0x30;
  iVar3 = *(short *)(&dir8_vectors + (short)(unaff_DX * 2) * 2) * iVar5;
  iVar4 = iVar3 >> 0x1f;
  sVar2 = (short)((int)((iVar3 + iVar4 * -0x40) - (uint)(iVar4 << 5 < 0)) >> 6);
  iVar5 = *(short *)(&unk_c90e2 + (short)(unaff_DX * 2) * 2) * iVar5;
  iVar3 = iVar5 >> 0x1f;
  sVar1 = (short)((int)((iVar5 + iVar3 * -0x40) - (uint)(iVar3 << 5 < 0)) >> 6);
  if ((*(short *)(param_1 + 0x32) != 0) && ((*(int *)(param_1 + 0x30) >> 0x10 ^ (int)sVar2) < 0)) {
    sVar2 = 0;
  }
  if ((*(short *)(param_1 + 0x30) != 0) && (-1 < (*(int *)(param_1 + 0x2e) >> 0x10 ^ (int)sVar1))) {
    sVar1 = 0;
  }
  dword_e03ac = (ushort)*(byte *)(param_1 + 0x57) +
                (0x20 - (short)((int)(uint)*(byte *)(param_1 + 0x56) >> 3));
  if (*(short *)(param_1 + 0x1a) == 0) {
    dword_e03ac = dword_e03ac + *(byte *)(param_1 + 0x57) + 0x14;
  }
  iVar3 = (int)sVar2 * (int)dword_e03ac;
  dword_e03ba._2_2_ = (short)(iVar3 >> 5);
  dword_e03be._0_2_ = (short)(iVar3 >> 0x15);
  iVar3 = (int)dword_e03ac * (int)sVar1;
  dword_e03be._2_2_ = (short)(iVar3 >> 5);
  sRam000e03c2 = (short)(iVar3 >> 0x15);
  dword_e03ba._2_2_ = dword_e03ba._2_2_ + *(short *)(param_1 + 0xc);
  dword_e03be._2_2_ = dword_e03be._2_2_ + *(short *)(param_1 + 0xe);
  register0x00000008 =
       (int)dword_e03ba._2_2_ * (int)dword_e03ba._2_2_ +
       (int)dword_e03be._2_2_ * (int)dword_e03be._2_2_;
  if (*(short *)(param_1 + 0x6a) == 0x10) {
    if ((game_flags & 1) != 0) {
      if (*(short *)(param_1 + 6) < 0) {
        iVar3 = -(*(int *)(param_1 + 4) >> 0x10);
      }
      else {
        iVar3 = *(int *)(param_1 + 4) >> 0x10;
      }
      if (0x73 < iVar3) {
        dword_e03ac = 0xc;
        goto LAB_0005ef2b;
      }
    }
    dword_e03ac = 0xf;
  }
  else {
    dword_e03ac = (short)((uint)*(byte *)(param_1 + 0x58) *
                          (*(int *)(*(int *)(param_1 + 0x6c) + 0x44 +
                                   (*(int *)(param_1 + 0x44) >> 0x18) * 2) >> 0x10) >> 0xc);
  }
LAB_0005ef2b:
  iVar3 = *(int *)(&unk_ccd98 + dword_e03ac * 4);
  dword_e03ac = (short)iVar3;
  dword_e03ae._0_2_ = (short)((uint)iVar3 >> 0x10);
  if ((*(byte *)(param_1 + 0x45) & 0x40) != 0) {
    dword_e03ac = (short)(iVar3 >> 3);
    dword_e03ae._0_2_ = (short)dword_e03ae >> 3;
  }
  if (register0x00000008 <= CONCAT22((short)dword_e03ae,dword_e03ac)) {
    *(short *)(param_1 + 0xc) = dword_e03ba._2_2_;
    *(short *)(param_1 + 0xe) = dword_e03be._2_2_;
  }
  if ((((*(short *)(param_1 + 0x6a) != 0x10) && (((byte)option_flags & 4) != 0)) &&
      ((game_flags & 1) == 0)) &&
     ((*(short *)(param_1 + 0x1a) != 0 &&
      (dword_e03ba._2_2_ = randomrange(0x80), dword_e03ba._2_2_ == 0)))) {
    dword_e03ba._2_2_ =
         *(short *)(*(int *)(param_1 + 0x6c) + 0x46 + (*(int *)(param_1 + 0x44) >> 0x18) * 2) +
         -0x28;
    if (dword_e03ba._2_2_ < 0xc00) {
      sVar2 = dword_e03ba._2_2_;
      if (dword_e03ba._2_2_ < 0) {
        sVar2 = 0;
      }
      *(short *)(*(int *)(param_1 + 0x6c) + 0x46 + (*(int *)(param_1 + 0x44) >> 0x18) * 2) = sVar2;
      return;
    }
    dword_e03ba._2_2_ = dword_e03ba._2_2_ + (ushort)*(byte *)(param_1 + 0x61);
    if (0x1000 < dword_e03ba._2_2_) {
      dword_e03ba._2_2_ = 0x1000;
    }
    sVar2 = dword_e03ba._2_2_;
    if (dword_e03ba._2_2_ < 0) {
      sVar2 = 0;
    }
    *(short *)(*(int *)(param_1 + 0x6c) + 0x46 + (*(int *)(param_1 + 0x44) >> 0x18) * 2) = sVar2;
  }
  return;
}


// ================================================================================================
// net_zone_flags @ 0x5f04e [__watcall]
// ================================================================================================

undefined4 __watcall
net_zone_flags(int *param_1,int unaff_EDX,int unaff_EBX,int unaff_ECX,byte *param_5,byte *param_6)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  __CHK(0x1c);
  iVar3 = *param_1 >> 0x10;
  iVar2 = param_1[1];
  iVar4 = dword_e03ba >> 0x10;
  iVar5 = dword_e03be >> 0x10;
  param_6[0] = 0;
  param_6[1] = 0;
  param_6[2] = 0;
  param_6[3] = 0;
  *(undefined4 *)param_5 = *(undefined4 *)param_6;
  if (iVar2 >> 0x10 < unaff_EDX) {
    param_5[0] = 4;
    param_5[1] = 0;
    param_5[2] = 0;
    param_5[3] = 0;
    if (unaff_EDX <= iVar5) goto LAB_0005f0bc;
LAB_0005f0ab:
    uVar1 = 0;
  }
  else {
    if (iVar5 < unaff_EDX) {
      param_6[0] = 4;
      param_6[1] = 0;
      param_6[2] = 0;
      param_6[3] = 0;
    }
LAB_0005f0bc:
    if (iVar2 >> 0x10 < unaff_EBX) {
      if (unaff_EBX <= iVar5) {
        param_6[0] = 1;
        param_6[1] = 0;
        param_6[2] = 0;
        param_6[3] = 0;
      }
    }
    else {
      param_5[0] = 1;
      param_5[1] = 0;
      param_5[2] = 0;
      param_5[3] = 0;
      if (unaff_EBX <= iVar5) goto LAB_0005f0ab;
    }
    if (iVar3 < unaff_ECX) {
      if (unaff_ECX <= iVar4) {
        *param_6 = *param_6 | 2;
      }
    }
    else {
      *param_5 = *param_5 | 2;
      if (unaff_ECX <= iVar4) goto LAB_0005f0ab;
    }
    iVar2 = -unaff_ECX;
    if (-iVar3 == unaff_ECX || iVar2 < iVar3) {
      if (-iVar4 != unaff_ECX && iVar4 <= iVar2) {
        *param_6 = *param_6 | 8;
      }
    }
    else {
      *param_5 = *param_5 | 8;
      if (-iVar4 != unaff_ECX && iVar4 <= iVar2) goto LAB_0005f0ab;
    }
    uVar1 = 1;
  }
  return uVar1;
}


// ================================================================================================
// ai_choose_direction @ 0x5f151 [__watcall]
// ================================================================================================

void __watcall ai_choose_direction(int *param_1)

{
  undefined2 uVar1;
  short sVar2;
  short sVar3;
  int iVar4;
  undefined2 uVar5;
  int iVar6;
  short sVar7;
  int iVar8;
  int iVar9;
  bool bVar10;
  bool bVar11;
  bool bVar12;
  uint local_4c;
  uint local_48 [5];
  int local_34;
  int local_30;
  int local_2c;
  int *local_28;
  int local_24;
  int local_20;
  
  __CHK(0x5c);
  if ((*(short *)((int)param_1 + 0x1a) == 0) ||
     (*(char *)((int)param_1 + (*(int *)((int)param_1 + 0x1a) >> 0x10) + 0x1e) == '\'')) {
    local_2c = 1;
  }
  else {
    local_2c = 0;
  }
  if (local_2c == 0) {
    iVar8 = 10;
  }
  else {
    iVar8 = -6;
  }
  local_30 = (int)dword_e03be >> 0x10;
  if (((game_flags & 1) != 0) && (*(short *)((int)param_1 + 0x6a) == 0x10)) {
    iVar9 = local_30;
    if ((int)dword_e03be < 0) {
      iVar9 = -local_30;
    }
    if ((iVar9 < 0xe8) && (-1 < (int)(param_1[1] ^ dword_e03be) >> 0x10)) {
      return;
    }
  }
  iVar9 = *param_1 >> 0x10;
  local_34 = param_1[1] >> 0x10;
  local_20 = dword_e03ba >> 0x10;
  if (local_2c == 0) {
    iVar4 = 0;
  }
  else {
    iVar4 = -8;
  }
  if (local_2c == 0) {
    iVar6 = 0x23;
  }
  else {
    iVar6 = 6;
  }
  iVar4 = net_zone_flags(param_1,0xe8 - iVar6,0xfc,iVar4 + 0x2c,local_48,&local_4c);
  if (iVar4 == 0) {
    if (local_2c == 0) {
      iVar4 = 0;
    }
    else {
      iVar4 = -8;
    }
    if (local_2c == 0) {
      iVar6 = 0x23;
    }
    else {
      iVar6 = 6;
    }
    iVar4 = net_zone_flags(param_1,0xffffff04,iVar6 + -0xe8,iVar4 + 0x2c,local_48,&local_4c);
    if (iVar4 == 0) {
      return;
    }
    uVar5 = 0xff03;
    if (local_2c == 0) {
      sVar7 = 0x24;
    }
    else {
      sVar7 = 7;
    }
    sVar7 = sVar7 + -0xe8;
    uVar1 = 0xff18;
    if ((*(byte *)(param_1 + 0x11) & 0x80) == 0) {
      iVar4 = param_1[0x1c];
    }
    else {
      iVar4 = param_1[0x1b];
    }
    local_24 = *(int *)(iVar4 + 0xf8) >> 0x10;
    if (-1 < local_24) {
      local_28 = &entities + local_24 * 0x20;
    }
  }
  else {
    uVar5 = 0xfd;
    if (local_2c == 0) {
      sVar7 = 0x24;
    }
    else {
      sVar7 = 7;
    }
    sVar7 = 0xe8 - sVar7;
    local_34 = -local_34;
    local_30 = -local_30;
    uVar1 = 0xe8;
    if ((*(byte *)(param_1 + 0x11) & 0x80) == 0) {
      iVar4 = param_1[0x1b];
    }
    else {
      iVar4 = param_1[0x1c];
    }
    local_24 = *(int *)(iVar4 + 0xf8) >> 0x10;
    if (-1 < local_24) {
      local_28 = &entities + local_24 * 0x20;
    }
    if ((local_48[0] & 5) != 0) {
      local_48[0] = local_48[0] ^ 5;
    }
    if ((local_4c & 5) != 0) {
      local_4c = local_4c ^ 5;
    }
  }
  sVar2 = (short)iVar8;
  if (local_4c == 0) {
    if (-0xe9 < local_34) {
      if (local_2c == 0) {
        if (-0xe9 < local_30) {
          if (local_24 < 0) {
            return;
          }
          if (iVar9 < local_20) {
            if (*local_28 >> 0x10 <= iVar9) {
              return;
            }
          }
          else if (iVar9 < local_28[1] >> 0x10) {
            return;
          }
          goto LAB_0005f48b;
        }
        dword_e03be = CONCAT22(sVar7,(undefined2)dword_e03be);
        if ((local_24 < 0) || (-1 < (local_20 - (*local_28 >> 0x10) ^ iVar9 - local_20))) {
          iVar4 = iVar9;
          if (iVar9 < 0) {
            iVar4 = -iVar9;
          }
          if (iVar8 + 0x2c <= iVar4) {
            return;
          }
LAB_0005f448:
          if (-1 < iVar9) {
            dword_e03ba = CONCAT22(sVar2 + 0x2c,(undefined2)dword_e03ba);
            goto LAB_0005f3d2;
          }
        }
        else {
LAB_0005f45b:
          if (*local_28 >> 0x10 <= iVar9) goto LAB_0005f3c5;
        }
LAB_0005f3f9:
        sVar2 = -0x2c - sVar2;
LAB_0005f3cc:
        dword_e03ba = CONCAT22(sVar2,(undefined2)dword_e03ba);
      }
      else {
        if (local_30 < -0xe8) {
          return;
        }
        dword_e03be = CONCAT22(sVar7,(undefined2)dword_e03be);
        if (local_20 < 0) {
          if (-0x2b - iVar8 <= local_20) goto LAB_0005f3f9;
        }
        else if (local_20 < iVar8 + 0x2c) {
LAB_0005f3c5:
          sVar2 = sVar2 + 0x2c;
          goto LAB_0005f3cc;
        }
      }
LAB_0005f3d2:
      if (iVar9 < 0) {
        iVar9 = -iVar9;
      }
      if (iVar9 < 0x27) {
        return;
      }
      goto LAB_0005f3e1;
    }
    if (local_30 < -0xe8) {
      return;
    }
    if (iVar9 < -0x2b - iVar8) {
      sVar2 = -0x2c - sVar2;
LAB_0005f505:
      dword_e03ba = CONCAT22(sVar2,(undefined2)dword_e03ba);
    }
    else {
      if (iVar8 + 0x2c <= iVar9) {
LAB_0005f4d2:
        sVar2 = sVar2 + 0x2c;
        goto LAB_0005f505;
      }
      dword_e03be = CONCAT22(uVar5,(undefined2)dword_e03be);
      if (local_20 < 0) {
        if (-0x2b - iVar8 <= local_20) {
          sVar2 = -0x2c - sVar2;
          goto LAB_0005f505;
        }
      }
      else if (local_20 < iVar8 + 0x2c) goto LAB_0005f4d2;
    }
    if (iVar9 < 0) {
      iVar9 = -iVar9;
    }
    if (iVar9 < 0x27) {
      return;
    }
    goto LAB_0005f48b;
  }
  if (0xc < local_48[0]) {
    return;
  }
  sVar3 = -0x2c - sVar2;
  switch(local_48[0]) {
  case 0:
    if (local_34 < -0xe8) {
      if (iVar9 < -0x2b - iVar8) {
LAB_0005f5af:
        sVar3 = -0x2c - sVar2;
        break;
      }
      if (iVar9 < iVar8 + 0x2c) {
        dword_e03be = CONCAT22(uVar5,(undefined2)dword_e03be);
        if (local_20 < 0) {
          iVar8 = -0x2b - iVar8;
          bVar12 = SBORROW4(iVar8,local_20);
          bVar11 = iVar8 - local_20 < 0;
          bVar10 = iVar8 == local_20;
          goto LAB_0005f5a9;
        }
        iVar8 = iVar8 + 0x2c;
        bVar12 = SBORROW4(iVar8,local_20);
        bVar11 = iVar8 - local_20 < 0;
        bVar10 = iVar8 == local_20;
        goto LAB_0005f58d;
      }
    }
    else {
      if (local_2c == 0) {
        if (-0xe9 < local_30) {
          if ((-1 < local_24) && ((iVar9 - local_20 ^ local_20 - (*local_28 >> 0x10)) < 0))
          goto LAB_0005f45b;
          iVar4 = iVar9;
          if (iVar9 < 0) {
            iVar4 = -iVar9;
          }
          if (iVar4 < iVar8 + 0x2c) goto LAB_0005f448;
          goto LAB_0005f3d2;
        }
        dword_e03be = CONCAT22(uVar1,(undefined2)dword_e03be);
        if (-1 < local_24) {
          if (local_28[1] >> 0x10 <= iVar9) goto LAB_0005f593;
          goto LAB_0005f5af;
        }
        if (local_20 < 0) {
          iVar8 = -0x2b - iVar8;
          bVar12 = SBORROW4(iVar8,local_20);
          bVar11 = iVar8 - local_20 < 0;
          bVar10 = iVar8 == local_20;
          goto LAB_0005f5a9;
        }
        iVar8 = iVar8 + 0x2c;
        bVar12 = SBORROW4(iVar8,local_20);
        bVar11 = iVar8 - local_20 < 0;
        bVar10 = iVar8 == local_20;
      }
      else {
        if ((local_4c & 1) != 0) {
          return;
        }
        dword_e03be = CONCAT22(sVar7,(undefined2)dword_e03be);
        if (local_20 < 0) {
          iVar8 = -0x2b - iVar8;
          bVar12 = SBORROW4(iVar8,local_20);
          bVar11 = iVar8 - local_20 < 0;
          bVar10 = iVar8 == local_20;
LAB_0005f5a9:
          if (!bVar10 && bVar12 == bVar11) {
            return;
          }
          goto LAB_0005f5af;
        }
        iVar8 = iVar8 + 0x2c;
        bVar12 = SBORROW4(iVar8,local_20);
        bVar11 = iVar8 - local_20 < 0;
        bVar10 = iVar8 == local_20;
      }
LAB_0005f58d:
      if (bVar10 || bVar12 != bVar11) {
        return;
      }
    }
LAB_0005f593:
    sVar3 = sVar2 + 0x2c;
    break;
  case 1:
    dword_e03be = CONCAT22(sVar7,(undefined2)dword_e03be);
    if ((local_4c & 4) != 0) {
      return;
    }
    goto joined_r0x0005f6fc;
  case 2:
    dword_e03ba = CONCAT22(sVar2 + 0x2c,(undefined2)dword_e03ba);
    if ((local_4c & 5) != 0) {
      return;
    }
    goto LAB_0005f48b;
  case 3:
    if (local_4c == 8) goto LAB_0005f48b;
    goto LAB_0005f6a5;
  case 4:
    dword_e03be = CONCAT22(uVar5,(undefined2)dword_e03be);
    if ((local_4c & 1) == 0) {
      return;
    }
joined_r0x0005f6fc:
    if (-1 < local_20) {
      if (iVar8 + 0x2c <= local_20) {
        return;
      }
LAB_0005f6a5:
      dword_e03ba = CONCAT22(sVar2 + 0x2c,(undefined2)dword_e03ba);
      return;
    }
    if (local_20 < -0x2b - iVar8) {
      return;
    }
    break;
  default:
    goto LAB_0005e7f7;
  case 6:
    if (local_4c != 8) goto LAB_0005f6a5;
    goto LAB_0005f3e1;
  case 8:
    dword_e03ba = CONCAT22(sVar3,(undefined2)dword_e03ba);
    if ((local_4c & 5) == 0) {
      return;
    }
LAB_0005f48b:
    dword_e03be = CONCAT22(sVar7,(undefined2)dword_e03be);
    return;
  case 9:
    if (local_4c == 2) goto LAB_0005f48b;
    break;
  case 0xc:
    if (local_4c != 2) {
      return;
    }
LAB_0005f3e1:
    dword_e03be = CONCAT22(uVar5,(undefined2)dword_e03be);
    goto LAB_0005e7f7;
  }
  dword_e03ba = CONCAT22(sVar3,(undefined2)dword_e03ba);
LAB_0005e7f7:
  return;
}


// ================================================================================================
// stop_skating @ 0x5f745 [__watcall]
// ================================================================================================

void __watcall
stop_skating(int param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  undefined2 uVar1;
  int iVar2;
  
  __CHK(0xc);
  if (*(short *)(param_1 + 0xc) < 0) {
    iVar2 = -(*(int *)(param_1 + 10) >> 0x10);
  }
  else {
    iVar2 = *(int *)(param_1 + 10) >> 0x10;
  }
  if (iVar2 < 0x1001) {
    if (*(short *)(param_1 + 0xe) < 0) {
      iVar2 = -(*(int *)(param_1 + 0xc) >> 0x10);
    }
    else {
      iVar2 = *(int *)(param_1 + 0xc) >> 0x10;
    }
    if (iVar2 < 0x1001) goto LAB_0005f820;
  }
  if ((*(byte *)(param_1 + 0x44) & 0x10) == 0) {
    *(byte *)(param_1 + 0x45) = *(byte *)(param_1 + 0x45) | 2;
    if (*(short *)(param_1 + 0x6a) == 0x10) {
      if ((whistle_timer == 0) &&
         (((game_flags & 1) != 0 || ((((byte)stop_flags & 0x80) == 0 && ((game_flags & 8) == 0))))))
      {
        uVar1 = 0xaeb;
      }
      else {
        uVar1 = 0xbdb;
      }
    }
    else {
      uVar1 = 0x361;
    }
  }
  else if (*(short *)(param_1 + 0x6a) == 0x10) {
    if ((whistle_timer == 0) &&
       (((game_flags & 1) != 0 || ((((byte)stop_flags & 0x80) == 0 && ((game_flags & 8) == 0)))))) {
      uVar1 = 0xa5b;
    }
    else {
      uVar1 = 0xb4b;
    }
  }
  else {
    uVar1 = 0x289;
  }
  set_animation(param_1,uVar1,param_1,unaff_ECX,unaff_EDX,unaff_EBX);
LAB_0005f820:
  brake(param_1);
  return;
}


// ================================================================================================
// brake @ 0x5f82a [__watcall]
// ================================================================================================

void __watcall brake(int param_1)

{
  short sVar1;
  short sVar2;
  
  __CHK(0x18);
  sVar2 = *(byte *)(param_1 + 0x57) + 200;
  if (*(short *)(param_1 + 0x1a) == 0) {
    sVar2 = sVar2 + (ushort)*(byte *)(param_1 + 0x57) * 2;
  }
  sVar1 = *(short *)(param_1 + 0xc);
  if (sVar1 < 0) {
    *(short *)(param_1 + 0xc) = sVar1 + sVar2;
    if ((short)(sVar1 + sVar2) < 1) goto LAB_0005f87a;
  }
  else {
    *(short *)(param_1 + 0xc) = sVar1 - sVar2;
    if (-1 < (short)(sVar1 - sVar2)) goto LAB_0005f87a;
  }
  *(undefined2 *)(param_1 + 0xc) = 0;
LAB_0005f87a:
  sVar1 = *(short *)(param_1 + 0xe);
  if (sVar1 < 0) {
    *(short *)(param_1 + 0xe) = sVar1 + sVar2;
    if ((short)(sVar1 + sVar2) < 1) {
      return;
    }
  }
  else {
    *(short *)(param_1 + 0xe) = sVar1 - sVar2;
    if (-1 < (short)(sVar1 - sVar2)) {
      return;
    }
  }
  *(undefined2 *)(param_1 + 0xe) = 0;
  return;
}


// ================================================================================================
// goalie_move @ 0x5f8b2 [__watcall]
// ================================================================================================

void __watcall goalie_move(int param_1,byte unaff_DL,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  short sVar1;
  short sVar2;
  
  __CHK(0xc);
  unaff_DL = unaff_DL & 0xf;
  if (7 < unaff_DL) {
    if ((unaff_DL == 9) &&
       (*(int *)(param_1 + 10) >> 0x10 != 0 || *(int *)(param_1 + 0xc) >> 0x10 != 0)) {
      brake(param_1);
      return;
    }
    if ((*(byte *)(param_1 + 0x45) & 2) != 0) {
      return;
    }
    set_animation(param_1,1,param_1,unaff_ECX,unaff_ECX,unaff_EBX);
    return;
  }
  if ((((game_flags & 1) == 0) && ((short)*p_puck_carrier != *(short *)(param_1 + 0x6a))) &&
     (*(char *)(param_1 + 0x1e + (*(int *)(param_1 + 0x1a) >> 0x10)) == '\x0f')) {
    if ((short)*(char *)(param_1 + 0x52) == *(short *)(param_1 + 0x36)) goto LAB_0005f96e;
    sVar2 = (short)((uint)*(int *)(param_1 + 0x34) >> 0x10);
    sVar1 = (short)((int)((*(int *)(param_1 + 0x34) >> 0x10) - (*(int *)(param_1 + 0x4f) >> 0x18) &
                         4U) >> 1) + -1;
  }
  else {
    sVar2 = (ushort)unaff_DL - *(short *)(param_1 + 0x36);
    if (sVar2 == 0) goto LAB_0005f96e;
    sVar1 = (short)((uint)*(undefined4 *)(param_1 + 0x34) >> 0x10);
    sVar2 = (short)((int)(-(int)sVar2 & 4U) >> 1) + -1;
  }
  *(ushort *)(param_1 + 0x36) = sVar2 + sVar1 & 7;
LAB_0005f96e:
  set_animation(param_1,0x1f1);
  skating_accelerate(param_1,*(int *)(param_1 + 0x34) >> 0x10);
  return;
}


// ================================================================================================
// skating_turn @ 0x5f98a [__watcall]
// ================================================================================================

void __watcall skating_turn(int param_1,ushort unaff_DX,ushort unaff_BX,undefined4 unaff_ECX)

{
  undefined2 uVar1;
  
  __CHK(8);
  dword_e03b2._2_2_ = 2;
  if ((*(byte *)(param_1 + 0x44) & 0x10) != 0) {
    unaff_DX = unaff_DX ^ 4;
    dword_e03b2._2_2_ = 6;
  }
  if (unaff_DX != 0) {
    dword_e03ba._2_2_ = direction8(*(int *)(param_1 + 10) >> 0x10,*(int *)(param_1 + 0xc) >> 0x10);
    if (((dword_e03ba._2_2_ & 8) == 0) &&
       (dword_e03ba._2_2_ = (dword_e03ba._2_2_ - *(short *)(param_1 + 0x36)) + dword_e03b2._2_2_ & 7
       , dword_e03ba._2_2_ < 4)) {
      stop_skating(param_1);
      return;
    }
    if ((*(byte *)(param_1 + 0x55) & 8) == 0) {
      *(short *)(param_1 + 0x36) = *(short *)(param_1 + 0x36) + 1;
    }
    else {
      *(short *)(param_1 + 0x36) = *(short *)(param_1 + 0x36) + -1;
    }
    *(ushort *)(param_1 + 0x36) = *(ushort *)(param_1 + 0x36) & 7;
    if ((*(byte *)(param_1 + 0x44) & 0x10) == 0) {
      if (*(short *)(param_1 + 0x6a) == 0x10) {
        if ((whistle_timer == 0) &&
           (((game_flags & 1) != 0 || ((((byte)stop_flags & 0x80) == 0 && ((game_flags & 8) == 0))))
           )) {
          uVar1 = 0xa5b;
        }
        else {
          uVar1 = 0xb4b;
        }
      }
      else {
        uVar1 = 0x289;
      }
    }
    else {
      uVar1 = 0x529;
    }
    set_animation(param_1,uVar1,unaff_BX,param_1,unaff_ECX);
    return;
  }
  if ((*(byte *)(param_1 + 0x44) & 0x10) == 0) {
    if (*(short *)(param_1 + 0x6a) == 0x10) {
      if ((whistle_timer == 0) &&
         (((game_flags & 1) != 0 || ((((byte)stop_flags & 0x80) == 0 && ((game_flags & 8) == 0))))))
      {
        uVar1 = 0xa73;
      }
      else {
        uVar1 = 0xb63;
      }
    }
    else if ((short)*p_puck_carrier == *(short *)(param_1 + 0x6a)) {
      uVar1 = 0x2a1;
    }
    else if ((*(byte *)(param_1 + 0x45) & 0x40) == 0) {
      uVar1 = 0x2e9;
    }
    else {
      uVar1 = 0x8d3;
    }
  }
  else {
    uVar1 = 0x541;
  }
  if ((*(byte *)(param_1 + 0x45) & 2) == 0) {
    set_animation(param_1,uVar1,unaff_BX,param_1,unaff_ECX);
  }
  if ((*(byte *)(param_1 + 0x44) & 0x10) != 0) {
    unaff_BX = unaff_BX ^ 4;
  }
  skating_accelerate(param_1,(int)(short)unaff_BX);
  return;
}


// ================================================================================================
// save_game @ 0x5fb03 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

longlong __watcall save_game(undefined4 param_1,uint unaff_EDX)

{
  undefined2 *puVar1;
  int iVar2;
  int iVar3;
  undefined2 *puVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  byte bVar8;
  undefined4 local_a4;
  undefined2 local_a0;
  undefined2 local_9e [52];
  undefined local_36 [30];
  
  bVar8 = 0;
  __CHK(0xb0);
  iVar2 = file_write(param_1,&dword_c5413,0xffffffff,4);
  if (iVar2 != 0) {
    fatalerror(aErrorSavingGame);
  }
  iVar2 = 0;
  do {
    iVar3 = file_write(param_1,&entities + iVar2 * 0x20,0xffffffff,0x66);
    if (iVar3 != 0) {
      fatalerror(aErrorSavingGame);
    }
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0x11);
  iVar2 = 0;
  do {
    iVar3 = file_write(param_1,iVar2 * 0x100 + 0xdf614,0xffffffff,0xd4);
    if (iVar3 != 0) {
      fatalerror(aErrorSavingGame);
    }
    iVar2 = iVar2 + 1;
  } while (iVar2 < 2);
  iVar2 = file_write(param_1,&unk_dc200,0xffffffff,0x30);
  if (iVar2 != 0) {
    fatalerror(aErrorSavingGame);
  }
  iVar2 = file_write(param_1,&unk_dabf0,0xffffffff,0x30);
  if (iVar2 != 0) {
    fatalerror(aErrorSavingGame);
  }
  local_a4._0_2_ = user2_team._2_2_;
  local_a4._2_2_ = _away_team_id;
  local_a0 = (undefined2)camera;
  local_9e[0] = camera._2_2_;
  iVar2 = 0;
  puVar1 = local_9e + 1;
  do {
    puVar4 = puVar1;
    *puVar4 = *(undefined2 *)((int)&faceoff_ready_home + iVar2 * 2 + 2);
    iVar2 = iVar2 + 1;
    puVar1 = puVar4 + 1;
  } while (iVar2 < 6);
  puVar4[1] = _last_shooter;
  puVar4[2] = last_passer;
  puVar4[3] = pending_dir;
  puVar4[4] = (undefined2)shot_power;
  puVar4[5] = shot_power._2_2_;
  puVar4[6] = goalie_pass_mode;
  iVar2 = 0;
  puVar1 = puVar4 + 7;
  do {
    puVar4 = puVar1;
    *puVar4 = *(undefined2 *)((int)&goal_prediction + iVar2 * 2 + 2);
    iVar2 = iVar2 + 1;
    puVar1 = puVar4 + 1;
  } while (iVar2 < 4);
  puVar4[1] = (undefined2)icing_state;
  puVar4[2] = word_e9abc;
  puVar4[3] = last_touch_slot;
  puVar4[4] = last_touch_x;
  puVar4[5] = last_touch_y;
  puVar4[6] = _camera_target_x;
  puVar4[7] = (undefined2)camera_target_y;
  puVar4[8] = camera_target_y._2_2_;
  puVar4[9] = (undefined2)faceoff_spot;
  puVar4[10] = faceoff_spot._2_2_;
  puVar4[0xb] = faceoff_dir_home;
  puVar4[0xc] = faceoff_dir_away;
  puVar4[0xd] = _action_flags;
  puVar4[0xe] = stop_flags;
  puVar4[0xf] = _misc_flags;
  puVar4[0x10] = _user1_slot;
  puVar4[0x11] = user2_slot;
  puVar4[0x12] = user1_team;
  puVar4[0x13] = (undefined2)user2_team;
  puVar4[0x14] = stoppage_timer;
  puVar4[0x15] = dword_c90d0;
  puVar4[0x16] = whistle_timer;
  puVar4[0x17] = ref_phase;
  puVar4[0x18] = ref_infraction;
  puVar4[0x19] = _penalized_slot;
  puVar4[0x1a] = period_idx;
  puVar4[0x1b] = clock_seconds;
  puVar4[0x1c] = clock_sub;
  puVar4[0x1d] = (undefined2)show_names;
  puVar4[0x1e] = penalty_box_mode;
  puVar4[0x1f] = period_over;
  puVar4[0x20] = game_over;
  puVar4[0x21] = dword_cbebe._2_2_;
  puVar4[0x22] = word_cbec2;
  puVar4[0x23] = word_cbec4;
  puVar4[0x24] = (undefined2)dword_c5840;
  puVar4[0x25] = dword_cbec6;
  puVar4[0x26] = _word_e9ab0;
  puVar4[0x27] = _word_cbec8;
  puVar4[0x28] = (undefined2)dword_cbeca;
  *(undefined4 *)(puVar4 + 0x29) = _dword_c9100;
  puVar4[0x2b] = _penalized_count;
  puVar4[0x2c] = icing_state._2_2_;
  iVar2 = file_write(param_1,&local_a4,0xffffffff,0x80);
  if (iVar2 != 0) {
    fatalerror(aErrorSavingGame);
  }
  iVar2 = 0;
  puVar5 = &local_a4;
  do {
    puVar6 = puVar5;
    *(undefined2 *)puVar6 = *(undefined2 *)(&unk_e0384 + iVar2 * 2);
    iVar2 = iVar2 + 1;
    puVar5 = (undefined4 *)((int)puVar6 + 2);
  } while (iVar2 < 6);
  *(undefined *)((int)puVar6 + 2) = controller_type;
  *(undefined *)((int)puVar6 + 3) = byte_c4d1d;
  *(undefined *)(puVar6 + 1) = puck_in_net;
  *(undefined *)((int)puVar6 + 5) = game_flags;
  *(undefined2 *)((int)puVar6 + 6) = word_cbc52;
  *(undefined2 *)(puVar6 + 2) = word_cbc54;
  *(undefined2 *)((int)puVar6 + 10) = word_cbc56;
  *(undefined2 *)(puVar6 + 3) = word_cbc58;
  *(undefined2 *)((int)puVar6 + 0xe) = word_cbc5a;
  *(undefined2 *)(puVar6 + 4) = word_cbc5c;
  *(undefined2 *)((int)puVar6 + 0x12) = word_cbc5e;
  *(undefined2 *)(puVar6 + 5) = word_cbc60;
  *(undefined2 *)((int)puVar6 + 0x16) = word_cbc62;
  *(undefined2 *)(puVar6 + 6) = word_cbc64;
  *(undefined2 *)((int)puVar6 + 0x1a) = word_cbc66;
  *(undefined2 *)(puVar6 + 7) = word_cbc68;
  *(undefined2 *)((int)puVar6 + 0x1e) = word_cbc6a;
  *(undefined2 *)(puVar6 + 8) = word_cbc6c;
  *(undefined2 *)((int)puVar6 + 0x22) = word_e0304;
  *(undefined2 *)(puVar6 + 9) = word_e0306;
  *(undefined2 *)((int)puVar6 + 0x26) = word_e0380;
  *(undefined2 *)(puVar6 + 10) = word_e0382;
  *(undefined2 *)((int)puVar6 + 0x2a) = (undefined2)dword_df00c;
  *(undefined2 *)(puVar6 + 0xb) = (undefined2)dword_df010;
  *(undefined2 *)((int)puVar6 + 0x2e) = dword_def84;
  *(undefined2 *)(puVar6 + 0xc) = (undefined2)dword_def88;
  *(undefined2 *)((int)puVar6 + 0x32) = _period_num;
  *(undefined2 *)(puVar6 + 0xd) = word_cc0d8;
  *(undefined2 *)((int)puVar6 + 0x36) = (undefined2)dword_e9ab6;
  *(undefined2 *)(puVar6 + 0xe) = _dword_e9aae;
  *(undefined2 *)((int)puVar6 + 0x3a) = dword_e9aac;
  *(undefined2 *)(puVar6 + 0xf) = (undefined2)dword_e9a9e;
  *(undefined2 *)((int)puVar6 + 0x3e) = word_cc0da;
  *(undefined2 *)(puVar6 + 0x10) = (undefined2)crowd_noise;
  *(undefined2 *)((int)puVar6 + 0x42) = word_e9a9c;
  *(undefined2 *)(puVar6 + 0x11) = crowd_noise._2_2_;
  *(undefined2 *)((int)puVar6 + 0x46) = word_e9aaa;
  *(undefined2 *)(puVar6 + 0x12) = word_e9aa2;
  *(undefined2 *)((int)puVar6 + 0x4a) = excitement._2_2_;
  *(undefined2 *)(puVar6 + 0x13) = word_e9aa4;
  *(undefined2 *)((int)puVar6 + 0x4e) = (undefined2)excitement;
  *(undefined2 *)(puVar6 + 0x14) = dword_e009c;
  *(undefined2 *)((int)puVar6 + 0x52) = (undefined2)dword_c5403;
  *(undefined2 *)(puVar6 + 0x15) = (undefined2)dword_c5407;
  *(undefined2 *)((int)puVar6 + 0x56) = (undefined2)dword_c540b;
  *(undefined2 *)(puVar6 + 0x16) = (undefined2)dword_c540f;
  *(undefined2 *)((int)puVar6 + 0x5a) = (undefined2)dword_c5704;
  *(undefined2 *)(puVar6 + 0x17) = (undefined2)dword_c5708;
  *(undefined2 *)((int)puVar6 + 0x5e) = (undefined2)dword_c570c;
  *(undefined2 *)(puVar6 + 0x18) = word_cc0b0;
  *(undefined2 *)((int)puVar6 + 0x62) = (undefined2)dword_d8c78;
  *(undefined2 *)(puVar6 + 0x19) = (undefined2)dword_d8c6c;
  *(undefined2 *)((int)puVar6 + 0x66) = (undefined2)dword_cc0ac;
  *(undefined2 *)(puVar6 + 0x1a) = word_e024c;
  *(undefined2 *)((int)puVar6 + 0x6a) = word_e024e;
  *(undefined2 *)(puVar6 + 0x1b) = (undefined2)dword_c53fb;
  *(undefined *)((int)puVar6 + 0x6e) = byte_dc268;
  *(undefined *)((int)puVar6 + 0x6f) = byte_dc267;
  *(undefined *)(puVar6 + 0x1c) = byte_dc264;
  *(undefined *)((int)puVar6 + 0x71) = byte_dc265;
  *(undefined *)((int)puVar6 + 0x72) = byte_dc266;
  *(undefined *)((int)puVar6 + 0x73) = (undefined)one_timer_pending;
  iVar2 = file_write(param_1,&local_a4,0xffffffff,0x80);
  if (iVar2 != 0) {
    fatalerror(aErrorSavingGame);
  }
  iVar2 = 0;
  puVar5 = &local_a4;
  do {
    puVar6 = puVar5;
    *(undefined2 *)puVar6 = *(undefined2 *)(&unk_dee94 + iVar2 * 0xc);
    *(undefined2 *)((int)puVar6 + 2) = (&unk_dee96)[iVar2 * 6];
    iVar2 = iVar2 + 1;
    puVar5 = puVar6 + 1;
  } while (iVar2 < 0x14);
  *(undefined2 *)(puVar6 + 1) = dword_cbeca._2_2_;
  *(undefined2 *)((int)puVar6 + 6) = word_cbece;
  *(undefined2 *)(puVar6 + 2) = (undefined2)dword_e9ab2;
  *(undefined2 *)((int)puVar6 + 10) = dword_e9ab2._2_2_;
  *(undefined2 *)(puVar6 + 3) = (undefined2)breakaway_flag;
  *(undefined2 *)((int)puVar6 + 0xe) = (undefined2)penalty_shot_slot;
  *(undefined2 *)(puVar6 + 4) = (undefined2)dword_cc100;
  *(undefined2 *)((int)puVar6 + 0x12) = (undefined2)penalty_shot_team;
  *(undefined2 *)(puVar6 + 5) = dword_cc108;
  *(undefined2 *)((int)puVar6 + 0x16) = dword_cc10c;
  *(undefined2 *)(puVar6 + 6) = dword_cc110;
  *(undefined2 *)((int)puVar6 + 0x1a) = dword_cc114;
  *(undefined2 *)(puVar6 + 7) = (undefined2)penalty_shot_phase;
  *(undefined2 *)((int)puVar6 + 0x1e) = (undefined2)penalty_shot_setup;
  *(undefined2 *)(puVar6 + 8) = (undefined2)dword_cc120;
  *(undefined2 *)((int)puVar6 + 0x22) = (undefined2)defenders_ahead;
  *(undefined2 *)(puVar6 + 9) = (undefined2)penalty_shot_active;
  *(undefined2 *)((int)puVar6 + 0x26) = (undefined2)penalty_shot_timer;
  *(undefined2 *)(puVar6 + 10) = breakaway_lane_x;
  *(undefined2 *)((int)puVar6 + 0x2a) = breakaway_target_y;
  *(undefined2 *)(puVar6 + 0xb) = breakaway_trigger_y;
  *(undefined2 *)((int)puVar6 + 0x2e) = breakaway_waypoint;
  *(undefined2 *)(puVar6 + 0xc) = breakaway_lane_side;
  *(undefined2 *)((int)puVar6 + 0x32) = breakaway_heading;
  iVar2 = file_write(param_1,&local_a4,0xffffffff,0x80);
  if (iVar2 != 0) {
    fatalerror(aErrorSavingGame);
  }
  iVar2 = file_write(param_1,0xe9a16,0xffffffff,0x42);
  if (iVar2 != 0) {
    fatalerror(aErrorSavingGame);
  }
  iVar2 = file_write(param_1,&dword_e9ac8,0xffffffff,0xb);
  if (iVar2 != 0) {
    fatalerror(aErrorSavingGame);
  }
  iVar2 = file_write(param_1,&byte_e9ad3,0xffffffff,0xb);
  if (iVar2 != 0) {
    fatalerror(aErrorSavingGame);
  }
  iVar2 = file_write(param_1,&unk_c5423,0xffffffff,0xb);
  if (iVar2 != 0) {
    fatalerror(aErrorSavingGame);
  }
  iVar2 = file_write(param_1,&unk_c542e,0xffffffff,0xb);
  if (iVar2 != 0) {
    fatalerror(aErrorSavingGame);
  }
  iVar2 = file_write(param_1,&word_c571c,0xffffffff,0x40);
  if (iVar2 != 0) {
    fatalerror(aErrorSavingGame);
  }
  iVar2 = file_write(param_1,&word_c575c,0xffffffff);
  if (iVar2 != 0) {
    fatalerror(aErrorSavingGame);
  }
  puVar5 = &local_a4;
  iVar2 = 0;
  iVar3 = 0;
  do {
    if (0x80 < iVar2 + 0x10U) {
      iVar2 = file_write(param_1,&local_a4,0xffffffff);
      if (iVar2 != 0) {
        fatalerror(aErrorSavingGame);
      }
      puVar5 = &local_a4;
      iVar2 = 0;
    }
    puVar7 = puVar5 + (uint)bVar8 * -2 + 1;
    puVar6 = &word_db08c + (iVar3 % 0x19) * 4 + (iVar3 / 0x19) * 100 + (uint)bVar8 * -2;
    *puVar5 = (&word_db088)[(iVar3 % 0x19) * 4 + (iVar3 / 0x19) * 100];
    *puVar7 = *puVar6;
    puVar7[(uint)bVar8 * -2 + 1] = puVar6[(uint)bVar8 * -2 + 1];
    (puVar7 + (uint)bVar8 * -2 + 1)[(uint)bVar8 * -2 + 1] =
         (puVar6 + (uint)bVar8 * -2 + 1)[(uint)bVar8 * -2 + 1];
    puVar5 = puVar5 + 4;
    iVar2 = iVar2 + 0x10;
    iVar3 = iVar3 + 1;
  } while (iVar3 < 0x32);
  iVar3 = 0;
  do {
    if (0x80 < iVar2 + 6U) {
      iVar2 = file_write(param_1,&local_a4,0xffffffff);
      if (iVar2 != 0) {
        fatalerror(aErrorSavingGame);
      }
      puVar5 = &local_a4;
      iVar2 = 0;
    }
    *puVar5 = *(undefined4 *)((int)&word_dc240 + (iVar3 / 3) * 0x12 + (iVar3 % 3) * 6);
    *(undefined2 *)(puVar5 + (uint)bVar8 * -2 + 1) =
         (&word_dc244)[(iVar3 % 3) * 3 + (iVar3 / 3) * 9 + (uint)bVar8 * -4];
    puVar5 = (undefined4 *)((int)puVar5 + 6);
    iVar2 = iVar2 + 6;
    iVar3 = iVar3 + 1;
  } while (iVar3 < 6);
  if (iVar2 != 0) {
    iVar2 = file_write(param_1,&local_a4,0xffffffff);
    if (iVar2 != 0) {
      fatalerror(aErrorSavingGame);
    }
  }
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// savegame_io @ 0x60612 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

longlong __watcall savegame_io(undefined4 param_1,uint unaff_EDX)

{
  undefined4 *puVar1;
  short sVar2;
  short *psVar3;
  int iVar4;
  undefined4 uVar5;
  char *pcVar6;
  short *psVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  int iVar10;
  undefined4 *puVar11;
  byte bVar12;
  short local_128;
  undefined2 local_126;
  undefined2 local_124;
  short local_122 [52];
  char local_ba [18];
  undefined4 auStack_a8 [16];
  undefined4 auStack_68 [16];
  int local_28;
  undefined4 *local_24;
  int local_20;
  int iStack_1c;
  
  bVar12 = 0;
  __CHK(0x134);
  iVar4 = file_read(param_1,&dword_c5413,0xffffffff,4);
  if (iVar4 != 0) {
    fatalerror(aErrorSavingGame);
  }
  iStack_1c = 0;
  do {
    iVar4 = file_read(param_1,&entities + iStack_1c * 0x20,0xffffffff,0x66);
    if (iVar4 != 0) {
      fatalerror(aErrorLoadingGame);
    }
    iStack_1c = iStack_1c + 1;
  } while (iStack_1c < 0x11);
  iStack_1c = 0;
  do {
    iVar4 = file_read(param_1,iStack_1c * 0x100 + 0xdf614,0xffffffff,0xd4);
    if (iVar4 != 0) {
      fatalerror(aErrorLoadingGame);
    }
    iStack_1c = iStack_1c + 1;
  } while (iStack_1c < 2);
  iVar4 = file_read(param_1,&unk_dc200,0xffffffff,0x30);
  if (iVar4 != 0) {
    fatalerror(aErrorLoadingGame);
  }
  iVar4 = file_read(param_1,&unk_dabf0,0xffffffff,0x30);
  if (iVar4 != 0) {
    fatalerror(aErrorLoadingGame);
  }
  iVar4 = file_read(param_1,&local_128,0xffffffff,0x80);
  if (iVar4 != 0) {
    fatalerror(aErrorLoadingGame);
  }
  user2_team._2_2_ = (short)_local_128;
  _away_team_id = local_126;
  camera._0_2_ = local_124;
  camera._2_2_ = local_122[0];
  iStack_1c = 0;
  psVar3 = local_122 + 1;
  do {
    psVar7 = psVar3;
    *(short *)((int)&faceoff_ready_home + iStack_1c * 2 + 2) = *psVar7;
    iStack_1c = iStack_1c + 1;
    psVar3 = psVar7 + 1;
  } while (iStack_1c < 6);
  _last_shooter = psVar7[1];
  last_passer = psVar7[2];
  pending_dir = psVar7[3];
  shot_power._0_2_ = psVar7[4];
  shot_power._2_2_ = psVar7[5];
  goalie_pass_mode = psVar7[6];
  iStack_1c = 0;
  psVar3 = psVar7 + 7;
  do {
    psVar7 = psVar3;
    *(short *)((int)&goal_prediction + iStack_1c * 2 + 2) = *psVar7;
    iStack_1c = iStack_1c + 1;
    psVar3 = psVar7 + 1;
  } while (iStack_1c < 4);
  icing_state._0_2_ = psVar7[1];
  word_e9abc = psVar7[2];
  last_touch_slot = psVar7[3];
  last_touch_x = psVar7[4];
  last_touch_y = psVar7[5];
  _camera_target_x = psVar7[6];
  camera_target_y._0_2_ = psVar7[7];
  camera_target_y._2_2_ = psVar7[8];
  faceoff_spot._0_2_ = psVar7[9];
  faceoff_spot._2_2_ = psVar7[10];
  faceoff_dir_home = psVar7[0xb];
  faceoff_dir_away = psVar7[0xc];
  _action_flags = psVar7[0xd];
  stop_flags = psVar7[0xe];
  _misc_flags = psVar7[0xf];
  _user1_slot = psVar7[0x10];
  user2_slot = psVar7[0x11];
  user1_team = psVar7[0x12];
  user2_team._0_2_ = psVar7[0x13];
  stoppage_timer = psVar7[0x14];
  dword_c90d0 = psVar7[0x15];
  whistle_timer = psVar7[0x16];
  ref_phase = psVar7[0x17];
  ref_infraction = psVar7[0x18];
  _penalized_slot = psVar7[0x19];
  period_idx = psVar7[0x1a];
  clock_seconds = psVar7[0x1b];
  clock_sub = psVar7[0x1c];
  show_names = (int)psVar7[0x1d];
  penalty_box_mode = psVar7[0x1e];
  period_over = psVar7[0x1f];
  game_over = psVar7[0x20];
  dword_cbebe._2_2_ = psVar7[0x21];
  word_cbec2 = psVar7[0x22];
  word_cbec4 = psVar7[0x23];
  dword_c5840 = (int)psVar7[0x24];
  dword_cbec6 = psVar7[0x25];
  _word_e9ab0 = psVar7[0x26];
  _word_cbec8 = psVar7[0x27];
  dword_cbeca._0_2_ = psVar7[0x28];
  _dword_c9100 = *(undefined4 *)(psVar7 + 0x29);
  _penalized_count = psVar7[0x2b];
  icing_state._2_2_ = psVar7[0x2c];
  iVar4 = file_read(param_1,&local_128,0xffffffff);
  if (iVar4 != 0) {
    fatalerror(aErrorLoadingGame);
  }
  iStack_1c = 0;
  psVar3 = &local_128;
  do {
    pcVar6 = (char *)psVar3;
    *(undefined2 *)(&unk_e0384 + iStack_1c * 2) = *(undefined2 *)pcVar6;
    iStack_1c = iStack_1c + 1;
    psVar3 = (short *)(pcVar6 + 2);
  } while (iStack_1c < 6);
  controller_type = pcVar6[2];
  byte_c4d1d = pcVar6[3];
  puck_in_net = pcVar6[4];
  game_flags = pcVar6[5];
  word_cbc52 = *(undefined2 *)(pcVar6 + 6);
  word_cbc54 = *(undefined2 *)(pcVar6 + 8);
  word_cbc56 = *(undefined2 *)(pcVar6 + 10);
  word_cbc58 = *(undefined2 *)(pcVar6 + 0xc);
  word_cbc5a = *(undefined2 *)(pcVar6 + 0xe);
  word_cbc5c = *(undefined2 *)(pcVar6 + 0x10);
  word_cbc5e = *(undefined2 *)(pcVar6 + 0x12);
  word_cbc60 = *(undefined2 *)(pcVar6 + 0x14);
  word_cbc62 = *(undefined2 *)(pcVar6 + 0x16);
  word_cbc64 = *(undefined2 *)(pcVar6 + 0x18);
  word_cbc66 = *(undefined2 *)(pcVar6 + 0x1a);
  word_cbc68 = *(undefined2 *)(pcVar6 + 0x1c);
  word_cbc6a = *(undefined2 *)(pcVar6 + 0x1e);
  word_cbc6c = *(undefined2 *)(pcVar6 + 0x20);
  word_e0304 = *(undefined2 *)(pcVar6 + 0x22);
  word_e0306 = *(undefined2 *)(pcVar6 + 0x24);
  word_e0380 = *(undefined2 *)(pcVar6 + 0x26);
  word_e0382 = *(undefined2 *)(pcVar6 + 0x28);
  dword_df00c = (int)*(short *)(pcVar6 + 0x2a);
  dword_df010 = (int)*(short *)(pcVar6 + 0x2c);
  _dword_def84 = (int)*(short *)(pcVar6 + 0x2e);
  dword_def88 = (int)*(short *)(pcVar6 + 0x30);
  _period_num = (int)*(short *)(pcVar6 + 0x32);
  word_cc0d8 = *(undefined2 *)(pcVar6 + 0x34);
  dword_e9ab6._0_2_ = *(undefined2 *)(pcVar6 + 0x36);
  _dword_e9aae = *(undefined2 *)(pcVar6 + 0x38);
  dword_e9aac = *(undefined2 *)(pcVar6 + 0x3a);
  dword_e9a9e._0_2_ = *(undefined2 *)(pcVar6 + 0x3c);
  word_cc0da = *(undefined2 *)(pcVar6 + 0x3e);
  word_e9a9c = *(undefined2 *)(pcVar6 + 0x42);
  crowd_noise = CONCAT22(*(short *)(pcVar6 + 0x44),*(undefined2 *)(pcVar6 + 0x40));
  dword_ccc88 = (int)*(short *)(pcVar6 + 0x44);
  word_e9aaa = *(undefined2 *)(pcVar6 + 0x46);
  word_e9aa2 = *(undefined2 *)(pcVar6 + 0x48);
  excitement._2_2_ = *(undefined2 *)(pcVar6 + 0x4a);
  word_e9aa4 = *(undefined2 *)(pcVar6 + 0x4c);
  excitement._0_2_ = *(undefined2 *)(pcVar6 + 0x4e);
  _dword_e009c = (int)*(short *)(pcVar6 + 0x50);
  dword_c5403 = (int)*(short *)(pcVar6 + 0x52);
  dword_c5407 = (int)*(short *)(pcVar6 + 0x54);
  dword_c540b = (int)*(short *)(pcVar6 + 0x56);
  dword_c540f = (int)*(short *)(pcVar6 + 0x58);
  dword_c5704 = (int)*(short *)(pcVar6 + 0x5a);
  dword_c5708 = (int)*(short *)(pcVar6 + 0x5c);
  dword_c570c = (int)*(short *)(pcVar6 + 0x5e);
  word_cc0b0 = *(undefined2 *)(pcVar6 + 0x60);
  dword_d8c78 = (int)*(short *)(pcVar6 + 0x62);
  dword_d8c6c = (int)*(short *)(pcVar6 + 100);
  dword_cc0ac = (int)*(short *)(pcVar6 + 0x66);
  word_e024c = *(undefined2 *)(pcVar6 + 0x68);
  word_e024e = *(undefined2 *)(pcVar6 + 0x6a);
  dword_c53fb = (uint)*(short *)(pcVar6 + 0x6c);
  byte_dc268 = pcVar6[0x6e];
  byte_dc267 = pcVar6[0x6f];
  byte_dc264 = pcVar6[0x70];
  byte_dc265 = pcVar6[0x71];
  byte_dc266 = pcVar6[0x72];
  one_timer_pending = (int)pcVar6[0x73];
  iVar4 = file_read(param_1,&local_128,0xffffffff,0x80);
  if (iVar4 != 0) {
    fatalerror(aErrorLoadingGame);
  }
  _memset_fill(&unk_e9b2c,0,&local_128,0x20);
  iStack_1c = 0;
  psVar3 = &local_128;
  do {
    psVar7 = psVar3;
    iVar4 = iStack_1c * 0xc;
    sVar2 = *psVar7;
    *(short *)(&unk_dee94 + iVar4) = sVar2;
    iVar10 = (int)sVar2;
    local_28 = ((int)((iVar10 + (iVar10 >> 0x1f) * -0x10) - (uint)((iVar10 >> 0x1f) << 3 < 0)) >> 4)
               * 2;
    *(ushort *)(&unk_e9b2c + local_28) =
         (ushort)((uint)*(undefined4 *)(&unk_e9b2a + local_28) >> 0x10) |
         (ushort)(1 << ((byte)((longlong)iVar10 % 0x10) & 0x1f));
    (&unk_dee96)[iStack_1c * 6] = psVar7[1];
    if (-1 < iVar10) {
      *(undefined2 *)(&DAT_000dee99 + iVar4) = *(undefined2 *)((int)&aGgG + iVar10 * 6 + 2);
      *(undefined2 *)(&DAT_000dee9b + iVar4) =
           *(undefined2 *)((int)&aGgG + (iVar10 * 3 + 1) * 2 + 2);
      *(undefined2 *)(&DAT_000dee9d + iVar4) =
           *(undefined2 *)((int)&aGgG + (iVar10 * 3 + 2) * 2 + 2);
      (&DAT_000dee9f)[iVar4] = (&unk_cce00)[*(int *)(&DAT_000dee9b + iVar4) >> 0x10];
      (&DAT_000dee98)[iVar4] =
           (&unk_cce00)
           [(*(int *)(&DAT_000dee9b + iVar4) >> 0x10) + (*(int *)(&unk_dee94 + iVar4) >> 0x18)];
    }
    iStack_1c = iStack_1c + 1;
    psVar3 = psVar7 + 2;
  } while (iStack_1c < 0x14);
  dword_cbeca._2_2_ = psVar7[2];
  word_cbece = psVar7[3];
  dword_e9ab2._0_2_ = psVar7[4];
  dword_e9ab2._2_2_ = psVar7[5];
  breakaway_flag = (int)psVar7[6];
  penalty_shot_slot = (int)psVar7[7];
  dword_cc100 = (int)psVar7[8];
  penalty_shot_team = (int)psVar7[9];
  _dword_cc108 = (int)psVar7[10];
  _dword_cc10c = (int)psVar7[0xb];
  _dword_cc110 = (int)psVar7[0xc];
  _dword_cc114 = (int)psVar7[0xd];
  penalty_shot_phase = (int)psVar7[0xe];
  penalty_shot_setup = (int)psVar7[0xf];
  dword_cc120 = (int)psVar7[0x10];
  defenders_ahead = (int)psVar7[0x11];
  penalty_shot_active = (int)psVar7[0x12];
  penalty_shot_timer = (int)psVar7[0x13];
  _breakaway_lane_x = (int)psVar7[0x14];
  _breakaway_target_y = (int)psVar7[0x15];
  _breakaway_trigger_y = (int)psVar7[0x16];
  _breakaway_waypoint = (int)psVar7[0x17];
  _breakaway_lane_side = (int)psVar7[0x18];
  _breakaway_heading = (int)psVar7[0x19];
  iVar4 = file_read(param_1,0xe9a16,0xffffffff,0x42);
  if (iVar4 != 0) {
    fatalerror(aErrorLoadingGame);
  }
  iVar4 = file_read(param_1,&dword_e9ac8,0xffffffff,0xb);
  if (iVar4 != 0) {
    fatalerror(aErrorLoadingGame);
  }
  iVar4 = file_read(param_1,&byte_e9ad3,0xffffffff,0xb);
  if (iVar4 != 0) {
    fatalerror(aErrorLoadingGame);
  }
  iVar4 = file_read(param_1,&unk_c5423,0xffffffff,0xb);
  if (iVar4 != 0) {
    fatalerror(aErrorLoadingGame);
  }
  iVar4 = file_read(param_1,&unk_c542e,0xffffffff,0xb);
  if (iVar4 != 0) {
    fatalerror(aErrorLoadingGame);
  }
  iVar4 = file_read(param_1,auStack_68,0xffffffff,0x40);
  if (iVar4 != 0) {
    fatalerror(aErrorLoadingGame);
  }
  iVar4 = file_read(param_1,auStack_a8,0xffffffff,0x40);
  if (iVar4 != 0) {
    fatalerror(aErrorLoadingGame);
  }
  local_20 = 0;
  iStack_1c = 0;
  do {
    psVar3 = (short *)local_24;
    if (local_20 == 0) {
      local_20 = 0x80;
      if (0x2f < iStack_1c) {
        local_20 = 0x44;
      }
      iVar4 = file_read(param_1,&local_128,0xffffffff,local_20);
      psVar3 = &local_128;
      if (iVar4 != 0) {
        fatalerror(aErrorLoadingGame);
        psVar3 = &local_128;
      }
    }
    local_24 = (undefined4 *)psVar3;
    puVar8 = local_24 + 4;
    puVar1 = &word_db088 + (iStack_1c % 0x19) * 4 + (iStack_1c / 0x19) * 100;
    puVar11 = puVar1 + (uint)bVar12 * -2 + 1;
    puVar9 = local_24 + (uint)bVar12 * -2 + 1;
    *puVar1 = *local_24;
    *puVar11 = *puVar9;
    puVar11[(uint)bVar12 * -2 + 1] = puVar9[(uint)bVar12 * -2 + 1];
    (puVar11 + (uint)bVar12 * -2 + 1)[(uint)bVar12 * -2 + 1] =
         (puVar9 + (uint)bVar12 * -2 + 1)[(uint)bVar12 * -2 + 1];
    local_20 = local_20 + -0x10;
    iStack_1c = iStack_1c + 1;
    local_24 = puVar8;
  } while (iStack_1c < 0x32);
  iStack_1c = 0;
  do {
    puVar1 = (undefined4 *)((int)&word_dc240 + (iStack_1c % 3) * 6 + (iStack_1c / 3) * 0x12);
    *puVar1 = *puVar8;
    *(undefined2 *)(puVar1 + (uint)bVar12 * -2 + 1) =
         *(undefined2 *)(puVar8 + (uint)bVar12 * -2 + 1);
    iStack_1c = iStack_1c + 1;
    puVar8 = (undefined4 *)((int)puVar8 + 6);
  } while (iStack_1c < 6);
  if ((controller_type == '\x01') || (byte_c4d1d == '\x01')) {
    setmousepos(0xa0,100);
  }
  if (dword_c53fb == 0) {
    save_settings(&settings_exhibition);
    puVar8 = (undefined4 *)&settings_exhibition;
  }
  else if (dword_c53fb < 2) {
    save_settings(&settings_playoff);
    puVar8 = &settings_playoff;
  }
  else {
    if (dword_c53fb != 2) goto LAB_00061249;
    save_settings(&settings_league);
    puVar8 = &settings_league;
  }
  apply_settings(puVar8);
LAB_00061249:
  dword_e9ab6._2_2_ = sub_5b9d1();
  sub_1bbcc(1);
  load_team_palettes((int)user2_team._2_2_,(int)_away_team_id,&unk_df314);
  dword_c66d4 = 1;
  dword_c66d0 = 1;
  dword_dc28c = 0;
  load_music_banks();
  _memset_dwords(&sprite_banks,0xffffffff,&unk_df314,0x17);
  dword_cc0e0 = 0xffffffff;
  load_player_graphics();
  _memset_dwords(&sprite_banks,0);
  dword_cc0e0 = 0;
  if ((dword_cbeca._2_2_ != -1) && (word_cbece != -1)) {
    dword_e0248 = (&off_cc01d)[dword_cbeca._2_2_];
  }
  show_penalty();
  replay_write_ptr = replay_buffer;
  sub_67564();
  _action_flags = _action_flags & 0xffef;
  word_cbec4 = 1;
  dword_df70a = &entities;
  dword_df6f2 = &player_ratings;
  dword_df6f6 = &unk_dac40;
  dword_df6ee = &unk_dc200;
  dword_df6fa = &word_db088;
  dword_df6fe = &word_dc240;
  dword_df702 = &rosters;
  dword_df706 = &team_names;
  dword_df80a = &unk_dfb1c;
  dword_df7f2 = &unk_dae94;
  dword_df7f6 = &unk_dac70;
  dword_df7ee = &unk_dabf0;
  dword_df7fa = &unk_db218;
  dword_df7fe = &unk_dc252;
  dword_df802 = &unk_db7ec;
  dword_df806 = &unk_dbf18;
  puVar8 = &entities;
  iStack_1c = 0;
  do {
    *(short *)((int)puVar8 + 0x6a) = (short)iStack_1c;
    *(undefined2 *)((int)puVar8 + 0x66) = (&unk_cbd64)[iStack_1c * 9];
    *(undefined2 *)(puVar8 + 0x1a) = (&unk_cbd66)[iStack_1c * 9];
    if ((*(byte *)(puVar8 + 0x11) & 0x40) == 0) {
      uVar5 = 0xdf614;
    }
    else {
      uVar5 = 0xdf714;
    }
    puVar8[0x1b] = uVar5;
    if ((*(byte *)(puVar8 + 0x11) & 0x40) == 0) {
      uVar5 = 0xdf714;
    }
    else {
      uVar5 = 0xdf614;
    }
    puVar8[0x1c] = uVar5;
    puVar8[0x1d] = *puVar8;
    puVar8[0x1e] = puVar8[1];
    puVar8[0x1f] = puVar8[2];
    (&unk_e9ade)[iStack_1c] = (undefined)iStack_1c;
    (&draw_order_pos)[iStack_1c] = (short)iStack_1c;
    iStack_1c = iStack_1c + 1;
    puVar8 = puVar8 + 0x20;
  } while (iStack_1c < 0x11);
  sort_draw_order2();
  iStack_1c = 0;
  do {
    *(undefined4 *)(&word_c571c + iStack_1c * 4) = auStack_68[iStack_1c * 2];
    *(undefined4 *)(&unk_c5720 + iStack_1c * 4 + (uint)bVar12 * -4) =
         auStack_68[iStack_1c * 2 + (uint)bVar12 * -2 + 1];
    *(undefined4 *)(&word_c575c + iStack_1c * 4) = auStack_a8[iStack_1c * 2];
    *(undefined4 *)(&unk_c5760 + iStack_1c * 4 + (uint)bVar12 * -4) =
         auStack_a8[iStack_1c * 2 + (uint)bVar12 * -2 + 1];
    iStack_1c = iStack_1c + 1;
  } while (iStack_1c < 8);
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// start_crowd_sound @ 0x614c2 [__watcall]
// ================================================================================================

void __watcall start_crowd_sound(int param_1,int unaff_EDX)

{
  int iVar1;
  int iVar2;
  
  __CHK(0x14);
  iVar2 = param_1 * 0xc;
  *(short *)(&unk_dee94 + iVar2) = (short)unaff_EDX;
  iVar1 = ((int)((unaff_EDX + (unaff_EDX >> 0x1f) * -0x10) - (uint)((unaff_EDX >> 0x1f) << 3 < 0))
          >> 4) * 2;
  *(ushort *)(&unk_e9b2c + iVar1) =
       (ushort)((uint)*(undefined4 *)(&unk_e9b2a + iVar1) >> 0x10) |
       (ushort)(1 << ((byte)((longlong)unaff_EDX % 0x10) & 0x1f));
  *(undefined2 *)(&DAT_000dee99 + iVar2) = *(undefined2 *)((int)&aGgG + unaff_EDX * 6 + 2);
  *(undefined2 *)(&DAT_000dee9b + iVar2) = *(undefined2 *)((int)&aGgG + (unaff_EDX * 3 + 1) * 2 + 2)
  ;
  *(undefined2 *)(&DAT_000dee9d + iVar2) = *(undefined2 *)((int)&aGgG + (unaff_EDX * 3 + 2) * 2 + 2)
  ;
  (&DAT_000dee9f)[iVar2] = (&unk_cce00)[*(int *)(&DAT_000dee9b + iVar2) >> 0x10];
  (&DAT_000dee98)[iVar2] = (&unk_cce01)[*(int *)(&DAT_000dee9b + iVar2) >> 0x10];
  *(undefined *)(&unk_dee96 + param_1 * 6) = 0xc;
  *(undefined *)((int)&unk_dee96 + iVar2 + 1) = 1;
  return;
}


// ================================================================================================
// play_crowd_chant @ 0x61576 [__watcall]
// ================================================================================================

void __watcall
play_crowd_chant(int param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  __CHK(8);
  if (param_1 == 0) {
    uVar2 = 0x87;
    uVar1 = 0x12;
  }
  else {
    uVar2 = 0x88;
    uVar1 = 0x13;
  }
  start_crowd_sound(uVar1,uVar2,unaff_EBX,unaff_ECX,unaff_EDX);
  return;
}


// ================================================================================================
// update_effects @ 0x615a2 [__watcall]
// ================================================================================================

void __watcall update_effects(void)

{
  char *pcVar1;
  char cVar2;
  uint uVar3;
  undefined uVar4;
  undefined2 uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int *piVar9;
  short sVar10;
  short sStackY_18;
  
  __CHK(0x1c);
  if (crowd_noise._2_2_ < 0x2bd) {
    if (0x15e < crowd_noise._2_2_) {
      crowd_noise = CONCAT22(crowd_noise._2_2_ + -3,(undefined2)crowd_noise);
    }
  }
  else {
    crowd_noise = CONCAT22(crowd_noise._2_2_ + -2,(undefined2)crowd_noise);
  }
  uVar3 = crowd_noise;
  sVar10 = crowd_noise._2_2_ + -1;
  crowd_noise = CONCAT22(sVar10,(undefined2)crowd_noise);
  if (sVar10 < 0) {
    crowd_noise = uVar3 & 0xffff;
    sVar10 = randomrange(0x10);
    if (sVar10 == 0) {
      uVar5 = randomrange(0x20);
      crowd_noise = CONCAT22(uVar5,(undefined2)crowd_noise);
    }
  }
  sStackY_18 = 0;
  do {
    if (0x13 < sStackY_18) {
      return;
    }
    iVar8 = (int)sStackY_18;
    iVar6 = iVar8 * 0xc;
    piVar9 = (int *)(&unk_dee94 + iVar6);
    if (*(short *)piVar9 < 0) {
      cVar2 = *(char *)(&unk_dee96 + iVar8 * 6);
      *(char *)(&unk_dee96 + iVar8 * 6) = cVar2 + -1;
      if ((char)(cVar2 + -1) < '\0') {
        if (sStackY_18 == 0x12) {
          sVar10 = randomrange(0x11);
          sVar10 = sVar10 + 0x89;
        }
        else if (sStackY_18 == 0x13) {
          sVar10 = randomrange(0x11);
          sVar10 = sVar10 + 0x9a;
        }
        else {
          if ((sStackY_18 == 0x11) && ((game_flags & 1) != 0)) {
            sVar10 = randomrange(4);
            if (sVar10 < 2) {
              sVar10 = sVar10 + 0x85;
              goto LAB_0006170e;
            }
          }
          sVar10 = randomrange(0x85);
          while( true ) {
            iVar6 = (int)sVar10;
            if ((*(int *)(&unk_e9b2a +
                         ((int)((iVar6 + (iVar6 >> 0x1f) * -0x10) - (uint)((iVar6 >> 0x1f) << 3 < 0)
                               ) >> 4) * 2) >> 0x10 & 1 << ((byte)((longlong)iVar6 % 0x10) & 0x1f))
                == 0) break;
            sVar10 = sVar10 + 1;
            if (0x84 < sVar10) {
              sVar10 = 0;
            }
          }
        }
LAB_0006170e:
        start_crowd_sound((int)sStackY_18,(int)sVar10);
      }
    }
    else {
      cVar2 = *(char *)(&unk_dee96 + iVar8 * 6);
      *(char *)(&unk_dee96 + iVar8 * 6) = cVar2 + -1;
      if ((char)(cVar2 + -1) < '\0') {
        if ((char)(&DAT_000dee9f)[iVar6] < '\0') {
          iVar7 = -(*(int *)(&DAT_000dee9c + iVar6) >> 0x18);
        }
        else {
          iVar7 = *(int *)(&DAT_000dee9c + iVar6) >> 0x18;
        }
        if (*piVar9 >> 0x18 < iVar7) {
          *(undefined *)(&unk_dee96 + iVar8 * 6) = 0xc;
          pcVar1 = (char *)((int)&unk_dee96 + iVar6 + 1);
          *pcVar1 = *pcVar1 + '\x01';
          (&DAT_000dee98)[iVar6] =
               (&unk_cce00)[(*(int *)(&DAT_000dee9b + iVar6) >> 0x10) + (*piVar9 >> 0x18)];
        }
        else {
          if ((char)(&DAT_000dee9f)[iVar6] < '\0') {
            sVar10 = randomrange(2);
            if (sVar10 != 0) {
              (&DAT_000dee98)[iVar6] = (&unk_cce01)[*(int *)(&DAT_000dee9b + iVar6) >> 0x10];
              *(undefined *)(&unk_dee96 + iVar8 * 6) = 0xc;
              *(undefined *)((int)&unk_dee96 + iVar6 + 1) = 1;
              goto LAB_00061848;
            }
          }
          iVar7 = (int)*(short *)piVar9;
          iVar6 = ((int)((iVar7 + (iVar7 >> 0x1f) * -0x10) - (uint)((iVar7 >> 0x1f) << 3 < 0)) >> 4)
                  * 2;
          *(ushort *)(&unk_e9b2c + iVar6) =
               (ushort)((uint)*(undefined4 *)(&unk_e9b2a + iVar6) >> 0x10) &
               ~(ushort)(1 << ((byte)((longlong)iVar7 % 0x10) & 0x1f));
          *(short *)piVar9 = -1;
          iVar6 = 1000 - ((int)crowd_noise >> 0x10);
          iVar7 = iVar6 >> 0x1f;
          sVar10 = (short)((int)((iVar6 + iVar7 * -8) - (uint)(iVar7 << 2 < 0)) >> 3);
          if (sVar10 < 0x14) {
            sVar10 = 0x14;
          }
          if ((0x11 < sStackY_18) && (sVar10 < 100)) {
            sVar10 = 100;
          }
          if ((sStackY_18 == 0x11) && ((game_flags & 1) != 0)) {
            uVar4 = 0x78;
          }
          else {
            uVar4 = randomrange((int)sVar10);
          }
          *(undefined *)(&unk_dee96 + iVar8 * 6) = uVar4;
        }
      }
    }
LAB_00061848:
    sStackY_18 = sStackY_18 + 1;
  } while( true );
}


// ================================================================================================
// draw_nets_and_effects @ 0x61862 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall draw_nets_and_effects(void)

{
  short sVar1;
  short sVar2;
  short *psVar3;
  short sVar4;
  short sStack_24;
  
  __CHK(0x34);
  psVar3 = (short *)&unk_dee94;
  for (sVar4 = 0; sVar4 < 0x12; sVar4 = sVar4 + 1) {
    if (-1 < *psVar3) {
      blit_sprite((&effect_frames)[*(int *)((int)psVar3 + 1) >> 0x18],
                  *(int *)((int)psVar3 + 3) >> 0x10,*(int *)((int)psVar3 + 5) >> 0x10,
                  0xc0 < *(short *)((int)psVar3 + 5),0xffffffff,0);
    }
    psVar3 = psVar3 + 6;
  }
  psVar3 = psVar3 + 6;
  for (sVar4 = 1; -1 < sVar4; sVar4 = sVar4 + -1) {
    if (*psVar3 < 0) {
      sStack_24 = -1;
    }
    else {
      sStack_24 = (short)*(char *)(psVar3 + 2);
    }
    sVar1 = *(short *)((int)psVar3 + 5);
    sVar2 = *(short *)((int)psVar3 + 7);
    if ((100 < sStack_24) || (*psVar3 < 0)) {
      blit_sprite(dword_e0220,4,*(int *)(&unk_cd2f8 + sVar4 * 4) >> 0x10,0,(int)sVar4,0);
    }
    if (-1 < sStack_24) {
      blit_sprite((&effect_frames)[sStack_24],(int)sVar1,(int)sVar2,0,(int)sVar4,0);
    }
    if (sVar4 == 0) {
      blit_sprite(dword_e0230,4,_unk_cd2f8 >> 0x10,0,0xffffffff,0);
    }
    else if (((game_flags & 0x80) != 0) && (0x361 < dword_dffac._2_2_)) {
      draw_sprite_world(dword_dffac >> 0x10,dword_dff9c >> 0x10,dword_dffa0 >> 0x10,0,0);
    }
    psVar3 = psVar3 + -6;
  }
  return;
}


// ================================================================================================
// sub_619c8 @ 0x619c8 [__watcall]
// ================================================================================================

void __watcall
sub_619c8(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 unaff_ECX,
         undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  int iVar1;
  
  __CHK(8);
  iVar1 = dword_cd350;
  (&unk_e9bc0)[dword_cd350 * 8] = param_1;
  (&unk_e9ba4)[iVar1 * 8] = param_2;
  (&unk_e9ba8)[iVar1 * 8] = param_3;
  (&unk_e9bac)[iVar1 * 8] = unaff_ECX;
  (&unk_e9bb0)[iVar1 * 8] = param_5;
  (&unk_e9bb4)[iVar1 * 8] = param_6;
  (&unk_e9bb8)[iVar1 * 8] = param_7;
  (&unk_e9bbc)[iVar1 * 8] = param_8;
  dword_cd350 = dword_cd350 + 1;
  return;
}


// ================================================================================================
// sub_61a27 @ 0x61a27 [__watcall]
// ================================================================================================

void __watcall sub_61a27(void)

{
  code *pcVar1;
  undefined *puVar2;
  int iVar3;
  
  __CHK(0x28);
  puVar2 = &stack0xffffffe8;
  for (iVar3 = 0; iVar3 < dword_cd350; iVar3 = iVar3 + 1) {
    *(undefined4 *)(puVar2 + -4) = (&unk_e9bbc)[iVar3 * 8];
    *(undefined4 *)(puVar2 + -8) = (&unk_e9bb8)[iVar3 * 8];
    *(undefined4 *)(puVar2 + -0xc) = (&unk_e9bb4)[iVar3 * 8];
    pcVar1 = (code *)(&unk_e9bc0)[iVar3 * 8];
    *(undefined4 *)(puVar2 + -0x10) = 0x61a73;
    (*pcVar1)();
    puVar2 = puVar2 + -0xc;
  }
  dword_cd350 = 0;
  return;
}


// ================================================================================================
// sub_61a8a @ 0x61a8a [__watcall]
// ================================================================================================

void __watcall sub_61a8a(undefined4 param_1)

{
  int iVar1;
  __off_t _Var2;
  int iStack_14;
  
  __CHK(0x1c);
  word_c5428 = word_c5428 + 1;
  iVar1 = file_open_rw(&byte_dac20,&iStack_14);
  if (iVar1 != 0) {
    fatalerror(&aB3);
  }
  _Var2 = lseek(iStack_14,0,0);
  if (_Var2 < 0) {
    fatalerror(&aB4);
  }
  iVar1 = file_write(iStack_14,&unk_c5423,0xffffffff,0xb);
  if (iVar1 != 0) {
    fatalerror(&aB5_c1c5e);
  }
  _Var2 = lseek(iStack_14,-0xb,2);
  if (_Var2 < 0) {
    fatalerror(&aB6);
  }
  iVar1 = file_write(iStack_14,param_1,0xffffffff,0xb);
  if (iVar1 != 0) {
    fatalerror(&aB7);
  }
  iVar1 = file_write(iStack_14,&unk_c542e,0xffffffff,0xb);
  if (iVar1 != 0) {
    fatalerror(&aB8_c1c67);
  }
  file_close(&iStack_14);
  return;
}


// ================================================================================================
// sub_61b85 @ 0x61b85 [__watcall]
// ================================================================================================

void __watcall sub_61b85(void)

{
  int iVar1;
  int extraout_EDX;
  
  __CHK(0xc);
  iVar1 = 0;
  while (iVar1 < dword_cd34c) {
    sub_61a8a(&unk_e9b4c + iVar1 * 0xb);
    iVar1 = extraout_EDX + 1;
  }
  dword_cd34c = 0;
  return;
}


// ================================================================================================
// sub_61bbf @ 0x61bbf [__watcall]
// ================================================================================================

void __watcall sub_61bbf(void)

{
  int iVar1;
  undefined4 uStack_10;
  
  __CHK(0x18);
  iVar1 = file_open_rw(&byte_dac20,&uStack_10);
  if (iVar1 != 0) {
    fatalerror(&aB3);
  }
  iVar1 = file_write(uStack_10,&unk_c5423,0xffffffff,0xb);
  if (iVar1 != 0) {
    fatalerror(&aB4);
  }
  file_close(&uStack_10);
  return;
}


// ================================================================================================
// sub_61c22 @ 0x61c22 [__watcall]
// ================================================================================================

void __watcall sub_61c22(void)

{
  int iVar1;
  __off_t _Var2;
  int iStack_10;
  
  __CHK(0x18);
  iVar1 = file_open_rw(&byte_dac20,&iStack_10);
  if (iVar1 != 0) {
    fatalerror(&aB3);
  }
  _Var2 = lseek(iStack_10,-0xb,2);
  if (_Var2 < 0) {
    fatalerror(&aB6);
  }
  iVar1 = file_write(iStack_10,&unk_c542e,0xffffffff,0xb);
  if (iVar1 != 0) {
    fatalerror(&aB4);
  }
  file_close(&iStack_10);
  return;
}


// ================================================================================================
// sub_61c86 @ 0x61c86 [__watcall]
// ================================================================================================

void __watcall sub_61c86(void)

{
  int iVar1;
  __off_t _Var2;
  int iStack_10;
  
  __CHK(0x18);
  word_c5428 = word_c5428 + 1;
  iVar1 = file_open_rw(&byte_dac20,&iStack_10);
  if (iVar1 != 0) {
    fatalerror(&aB3);
  }
  _Var2 = lseek(iStack_10,0,0);
  if (_Var2 < 0) {
    fatalerror(&aB4);
  }
  iVar1 = file_write(iStack_10,&unk_c5423,0xffffffff,0xb);
  if (iVar1 != 0) {
    fatalerror(&aB5_c1c5e);
  }
  _Var2 = lseek(iStack_10,0,2);
  if (_Var2 < 0) {
    fatalerror(&aB6);
  }
  iVar1 = file_write(iStack_10,&unk_c542e,0xffffffff,0xb);
  if (iVar1 != 0) {
    fatalerror(&aB8_c1c67);
  }
  file_close(&iStack_10);
  return;
}


// ================================================================================================
// format_player_name @ 0x61d48 [__watcall]
// ================================================================================================

void __watcall
format_player_name(char *param_1,undefined4 unaff_EDX,short unaff_BX,char *unaff_ECX,char *param_5,
                  undefined4 param_6)

{
  int iVar1;
  size_t sVar2;
  int iVar3;
  char acStack_28 [20];
  undefined2 local_14;
  undefined2 uStack_12;
  short sStack_10;
  
  __CHK(0x48);
  local_14 = (undefined2)unaff_EDX;
  uStack_12 = (undefined2)((uint)unaff_EDX >> 0x10);
  sStack_10 = unaff_BX;
  setfont(font_scor2b);
  iVar3 = (int)sStack_10;
  sprintf(param_1,aSDSSS,CONCAT22(uStack_12,local_14),iVar3,unaff_ECX,param_5,param_6);
  iVar1 = textwidth(param_1);
  if (0x7c < iVar1) {
    sprintf(param_1,aSDCSS,CONCAT22(uStack_12,local_14),iVar3,(int)*unaff_ECX,param_5,param_6);
    iVar1 = textwidth(param_1);
    if (0x7c < iVar1) {
      sprintf(param_1,aSDSS,CONCAT22(uStack_12,local_14),iVar3,param_5,param_6);
      iVar1 = textwidth(param_1);
      if (0x7c < iVar1) {
        sprintf(param_1,aSDS,CONCAT22(uStack_12,local_14),iVar3,param_6);
        iVar1 = textwidth(param_1);
        strcpy(acStack_28,param_5);
        sVar2 = strlen(acStack_28);
        while( true ) {
          iVar3 = textwidth(acStack_28);
          if (iVar3 <= 0x7c - iVar1) break;
          (&stack0xffffffd7)[sVar2] = 0;
          sVar2 = sVar2 - 1;
        }
        sprintf(param_1,aSDSS,CONCAT22(uStack_12,local_14),(int)sStack_10,acStack_28,param_6);
      }
    }
  }
  setfont(font_current_default);
  return;
}


// ================================================================================================
// show_penalty @ 0x61e99 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall show_penalty(void)

{
  undefined1 *puVar1;
  undefined uVar2;
  undefined4 *puVar3;
  int iVar4;
  int iVar5;
  undefined1 *puVar6;
  int extraout_EDX;
  int extraout_EDX_00;
  int extraout_EDX_01;
  int extraout_EDX_02;
  int extraout_EDX_03;
  uint uVar7;
  char *pcVar8;
  int iVar9;
  byte bVar10;
  char acStack_24 [12];
  
  bVar10 = 0;
  __CHK(0x3c);
  byte_e0344 = 0;
  _byte_e0308 = _byte_e0308 & 0xffffff00;
  _byte_e028c = _byte_e028c & 0xffffff00;
  _byte_e0250 = _byte_e0250 & 0xffffff00;
  byte_e02c8 = 0;
  if ((char)dword_e9ac8 == '\x01') {
    uVar7 = dword_e9ac8 >> 8 & 0xff;
    sprintf(&byte_e02c8,a02d02dS,(uint)byte_e9acc._3_1_,(uint)(byte)byte_e9ad0,
            &DAT_000dbc4a + uVar7 * 0x2e8);
    if ((byte_e9acc._1_1_ & 2) == 0) {
      if ((byte_e9acc._1_1_ & 4) == 0) {
        puVar3 = (undefined4 *)&unk_c1b49;
      }
      else {
        puVar3 = &aPP_c1ca8;
      }
    }
    else {
      puVar3 = &aSH_c1cac;
    }
    iVar4 = sprintf(acStack_24,(char *)&aS_c1cb0,puVar3);
    iVar5 = extraout_EDX;
    if (((dword_c53fb != 0) && ((game_flags & 0x10) == 0)) && (extraout_EDX < 0x19)) {
      iVar5 = extraout_EDX * 0x10 + uVar7 * 400;
      sprintf(acStack_24 + iVar4,unk_c1cb3,
              (*(int *)(&unk_db086 + iVar5) >> 0x10) + *(int *)(&unk_deb7c + iVar5));
      iVar5 = extraout_EDX_00;
    }
    iVar9 = uVar7 * 0x444;
    iVar4 = iVar5 * 0x27 + iVar9;
    format_player_name(&byte_e0250,&unk_c1b49,(&unk_db3ad)[iVar5 * 0x27 + iVar9],
                       &rosters + iVar4 + 7,&rosters + iVar4 + 0x17,acStack_24);
    if (dword_e9ac8._3_1_ == -1) {
      sprintf(&byte_e028c,aUnassisted);
    }
    else {
      sprintf(&byte_e028c,aAssists);
      iVar5 = extraout_EDX_01 * 0x27 + iVar9;
      format_player_name(&byte_e0308,&unk_c1b49,(&unk_db3ad)[iVar9 + extraout_EDX_01 * 0x27],
                         &rosters + iVar5 + 7,&rosters + iVar5 + 0x17,&unk_c1b49);
    }
    if ((byte)byte_e9acc == 0xff) {
      return;
    }
    iVar5 = (uint)(byte)byte_e9acc * 0x27;
    puVar1 = &rosters + iVar5 + uVar7 * 0x444;
    uVar2 = (&unk_db3ad)[iVar5 + uVar7 * 0x444];
    puVar6 = &byte_e0344;
  }
  else {
    if ((char)dword_e9ac8 != '\x02') {
      if ((char)dword_e9ac8 != '\x03') {
        byte_e02c8 = 0;
        byte_e0344 = 0;
        return;
      }
      uVar7 = (uint)dword_e9ac8._1_1_;
      iVar9 = (int)dword_e9ac8 >> 0x18;
      sprintf(&byte_e02c8,a02d02dSInjury,(uint)byte_e9acc._1_1_,(uint)byte_e9acc._2_1_,
              &team_names + uVar7 * 0xba);
      iVar4 = uVar7 * 0x444;
      iVar5 = extraout_EDX_03 * 0x27 + iVar4;
      format_player_name(&byte_e0250,&unk_c1b49,(&unk_db3ad)[extraout_EDX_03 * 0x27 + iVar4],
                         &rosters + iVar5 + 7,&rosters + iVar5 + 0x17,&unk_c1b49);
      if (iVar9 < 1) {
        pcVar8 = aGoneFor1Period;
      }
      else {
        pcVar8 = aGoneForTheGame;
      }
      sprintf(&byte_e028c,pcVar8);
      return;
    }
    uVar7 = (uint)dword_e9ac8._1_1_;
    if (dword_e9ac8._3_1_ != '\x11') {
      sprintf(&byte_e02c8,a02d02dSPenalty,(uint)byte_e9acc._2_1_,(uint)byte_e9acc._3_1_,
              &team_names + uVar7 * 0xba);
      iVar4 = uVar7 * 0x444;
      iVar5 = extraout_EDX_02 * 0x27 + iVar4;
      format_player_name(&byte_e0250,&unk_c1b49,(&unk_db3ad)[iVar4 + extraout_EDX_02 * 0x27],
                         &rosters + iVar5 + 7,&rosters + iVar5 + 0x17,&unk_c1b49);
      strcpy(&byte_e028c,(&off_cd304)[dword_e9ac8 >> 0x18]);
      if ((byte)byte_e9acc == 0xff) {
        byte_e0308 = aGameMisconduct[0];
        byte_e0308_1._0_1_ = aGameMisconduct[1];
        byte_e0308_1._1_1_ = aGameMisconduct[2];
        byte_e0308_1._2_1_ = aGameMisconduct[3];
        (&DAT_000e030c)[(uint)bVar10 * -2] =
             *(undefined4 *)(aGameMisconduct + (uint)bVar10 * -8 + 4);
        (&DAT_000e0310)[(uint)bVar10 * -2 + (uint)bVar10 * -2] =
             *(undefined4 *)(aGameMisconduct + (uint)bVar10 * -8 + (uint)bVar10 * -8 + 8);
        (&DAT_000e0310 + (uint)bVar10 * -2 + (uint)bVar10 * -2)[(uint)bVar10 * -2 + 1] =
             *(undefined4 *)
              (aGameMisconduct + (uint)bVar10 * -8 + (uint)bVar10 * -8 + 8 +
              ((uint)bVar10 * -2 + 1) * 4);
        return;
      }
      sprintf(&byte_e0308,aDMinutes,(uint)(byte)byte_e9acc);
      return;
    }
    sprintf(&byte_e02c8,a02d02dS,(uint)byte_e9acc._2_1_,(uint)byte_e9acc._3_1_,
            &team_names + penalty_shot_team * 0xba);
    byte_e0250 = aPenaltyShot_c1ccd[0];
    byte_e0250_1._0_1_ = aPenaltyShot_c1ccd[1];
    byte_e0250_1._1_1_ = aPenaltyShot_c1ccd[2];
    byte_e0250_1._2_1_ = aPenaltyShot_c1ccd[3];
    (&DAT_000e0254)[(uint)bVar10 * -2] = *(undefined4 *)(aPenaltyShot_c1ccd + (uint)bVar10 * -8 + 4)
    ;
    (&DAT_000e0258)[(uint)bVar10 * -2 + (uint)bVar10 * -2] =
         *(undefined4 *)(aPenaltyShot_c1ccd + (uint)bVar10 * -8 + (uint)bVar10 * -8 + 8);
    *(char *)(&DAT_000e0258 + (uint)bVar10 * -2 + (uint)bVar10 * -2 + (uint)bVar10 * -2 + 1) =
         (aPenaltyShot_c1ccd + (uint)bVar10 * -8 + (uint)bVar10 * -8 + 8)
         [((uint)bVar10 * -2 + 1) * 4];
    byte_e028c = aToBeTakenBy[0];
    byte_e028c_1._0_1_ = aToBeTakenBy[1];
    byte_e028c_1._1_1_ = aToBeTakenBy[2];
    byte_e028c_1._2_1_ = aToBeTakenBy[3];
    puVar3 = &DAT_000e0294 + (uint)bVar10 * -2 + (uint)bVar10 * -2;
    pcVar8 = aToBeTakenBy + (uint)bVar10 * -8 + (uint)bVar10 * -8 + 8;
    (&DAT_000e0290)[(uint)bVar10 * -2] = *(undefined4 *)(aToBeTakenBy + (uint)bVar10 * -8 + 4);
    *puVar3 = *(undefined4 *)pcVar8;
    *(undefined2 *)(puVar3 + (uint)bVar10 * -2 + 1) =
         *(undefined2 *)(pcVar8 + ((uint)bVar10 * -2 + 1) * 4);
    *(char *)((int)(puVar3 + (uint)bVar10 * -2 + 1) + (uint)bVar10 * -4 + 2) =
         (pcVar8 + ((uint)bVar10 * -2 + 1) * 4)[(uint)bVar10 * -4 + 2];
    puVar1 = &rosters + dword_cc100 * 0x27 + penalty_shot_team * 0x444;
    uVar2 = (&unk_db3ad)[dword_cc100 * 0x27 + penalty_shot_team * 0x444];
    puVar6 = &byte_e0308;
  }
  format_player_name(puVar6,&unk_c1b49,uVar2,puVar1 + 7,puVar1 + 0x17,&unk_c1b49);
  return;
}


// ================================================================================================
// announce_goal @ 0x62343 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall
announce_goal(int param_1,undefined param_2,undefined unaff_BL,undefined unaff_CL,undefined param_5,
             undefined param_6,undefined param_7)

{
  int iVar1;
  short sVar2;
  undefined2 uVar3;
  undefined uStackY_c;
  
  __CHK(0x10);
  uStackY_c = (undefined)param_1;
  dword_e9ac8 = CONCAT13(unaff_BL,CONCAT12(param_2,CONCAT11(uStackY_c,1)));
  byte_e9acc = CONCAT13(param_6,CONCAT12(period_num,CONCAT11(param_5,unaff_CL)));
  byte_e9ad0 = CONCAT11(*(undefined *)
                         ((short)((&word_df64c)[param_1 * 0x80] & 1) + 0x24 +
                         (&dword_df6ee)[param_1 * 0x40]),param_7);
  byte_e9ad2 = *(undefined *)
                ((short)((&word_df64c)[(uint)(param_1 == 0) * 0x80] & 1) + 0x24 +
                (&dword_df6ee)[(uint)(param_1 == 0) * 0x40]);
  if ((game_flags & 0x10) == 0) {
    iVar1 = dword_cd34c * 0xb;
    *(undefined4 *)(&unk_e9b4c + iVar1) = dword_e9ac8;
    *(undefined4 *)(&DAT_000e9b50 + iVar1) = byte_e9acc;
    *(undefined2 *)(&DAT_000e9b54 + iVar1) = byte_e9ad0;
    (&DAT_000e9b56)[iVar1] = byte_e9ad2;
    iVar1 = dword_cd34c + 1;
    if (7 < dword_cd34c + 1) {
      iVar1 = dword_cd34c;
    }
    dword_cd34c = iVar1;
    if (param_1 == 0) {
      byte_c542f = byte_c542f + '\x01';
    }
    else {
      byte_c5431 = byte_c5431 + '\x01';
    }
  }
  if (param_1 == 0) {
    sVar2 = randomrange(0x14);
    if (sVar2 < 10) {
      uVar3 = 1;
    }
    else {
      uVar3 = 5;
    }
    load_cutscene_clip(uVar3);
  }
  show_penalty();
  sub_66dda();
  dword_e9a9e = CONCAT22(input_enabled,(undefined2)dword_e9a9e);
  byte_e9ad3 = dword_e9ac8;
  byte_e9ad7 = byte_e9acc;
  draw_order_list = byte_e9ad0;
  unk_e9add = byte_e9ad2;
  _input_enabled = (int)input_enabled;
  return;
}


// ================================================================================================
// record_penalty @ 0x624b9 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __watcall
record_penalty(uint param_1,int param_2,int unaff_EBX,undefined unaff_CL,undefined4 param_5,
              undefined4 param_6,int param_7)

{
  short sVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  undefined4 extraout_EDX;
  undefined uStack_10;
  
  __CHK(0x2c);
  if ((game_flags & 0x10) != 0) {
    return 0;
  }
  uStack_10 = (undefined)param_1;
  dword_e9ac8 = CONCAT13((char)unaff_EBX,CONCAT12((char)param_2,CONCAT11(uStack_10,2)));
  byte_e9acc = CONCAT13((undefined)param_6,
                        CONCAT12((undefined)param_5,CONCAT11(period_num,unaff_CL)));
  iVar3 = dword_cd34c * 0xb;
  *(undefined4 *)(&unk_e9b4c + iVar3) = dword_e9ac8;
  *(undefined4 *)(&DAT_000e9b50 + iVar3) = byte_e9acc;
  *(undefined2 *)(&DAT_000e9b54 + iVar3) = byte_e9ad0;
  (&DAT_000e9b56)[iVar3] = byte_e9ad2;
  iVar3 = dword_cd34c + 1;
  if (7 < dword_cd34c + 1) {
    iVar3 = dword_cd34c;
  }
  dword_cd34c = iVar3;
  if ((dword_cbebe >> 0x10 != -1) || (unaff_EBX == 0x11)) goto LAB_000625df;
  if ((param_1 == 0) || (sVar1 = randomrange(4), sVar1 != 0)) {
    if (unaff_EBX == 4) {
      sVar1 = randomrange(3);
      if (sVar1 != 0) goto LAB_000625df;
      uVar2 = 6;
    }
    else if (unaff_EBX == 6) {
      sVar1 = randomrange(3);
      if (sVar1 != 0) goto LAB_000625df;
      uVar2 = 7;
    }
    else {
      if ((unaff_EBX != 5) || (sVar1 = randomrange(3), sVar1 != 0)) goto LAB_000625df;
      uVar2 = 9;
    }
  }
  else {
    uVar2 = 10;
  }
  load_cutscene_clip(uVar2);
LAB_000625df:
  show_penalty();
  sub_66dda();
  dword_e9a9e = CONCAT22(input_enabled,(undefined2)dword_e9a9e);
  _input_enabled = 0;
  if (400 < crowd_noise._2_2_) {
    crowd_noise._2_2_ = 400;
  }
  sVar1 = user2_team._2_2_;
  if (param_1 != 0) {
    sVar1 = _away_team_id;
  }
  if (unaff_EBX == 0x11) {
    sVar1 = user2_team._2_2_;
    if (penalty_shot_team != 0) {
      sVar1 = _away_team_id;
    }
    say_penalty_shot_wrapper
              ((&team_abbrev)[sVar1],(&unk_db3ad)[dword_cc100 * 0x27 + penalty_shot_team * 0x444],
               param_5,param_6);
  }
  else {
    if (_dword_e9aac >> 0x10 == param_1) {
      iVar3 = 2;
    }
    else {
      iVar3 = 1;
      _dword_e9aac = CONCAT22((short)param_1,dword_e9aac);
    }
    iVar4 = iVar3;
    if ((param_7 != 0) &&
       ((*(byte *)((int)&infraction_queue + param_7 * 2 + 2) & 0x1f) < 6 != param_1)) {
      iVar4 = iVar3 + 1;
    }
    say_penalty_wrapper((&team_abbrev)[sVar1],(&unk_db3ad)[param_2 * 0x27 + param_1 * 0x444],
                        extraout_EDX,(&off_cd354)[unaff_EBX],param_5,param_6,iVar3,iVar4,
                        param_7 == 0);
    if (param_7 == 0) {
      _dword_e9aac = CONCAT22(0xffff,dword_e9aac);
    }
  }
  _input_enabled = dword_e9a9e >> 0x10;
  return 0;
}


// ================================================================================================
// announce_injury @ 0x62764 [__watcall]
// ================================================================================================

undefined4 __watcall
announce_injury(undefined param_1,undefined unaff_DL,undefined unaff_BL,undefined unaff_CL,
               undefined param_5)

{
  int iVar1;
  undefined4 uVar2;
  
  __CHK(0xc);
  uVar2 = byte_e9acc;
  if ((game_flags & 0x10) == 0) {
    dword_e9ac8 = CONCAT13(unaff_BL,CONCAT12(unaff_DL,CONCAT11(param_1,3)));
    byte_e9acc._3_1_ = SUB41(uVar2,3);
    byte_e9acc._0_3_ = CONCAT12(param_5,CONCAT11(unaff_CL,period_num));
    iVar1 = dword_cd34c * 0xb;
    *(undefined4 *)(&unk_e9b4c + iVar1) = dword_e9ac8;
    *(undefined4 *)(&DAT_000e9b50 + iVar1) = byte_e9acc;
    *(undefined2 *)(&DAT_000e9b54 + iVar1) = byte_e9ad0;
    (&DAT_000e9b56)[iVar1] = byte_e9ad2;
    iVar1 = dword_cd34c + 1;
    if (7 < dword_cd34c + 1) {
      iVar1 = dword_cd34c;
    }
    dword_cd34c = iVar1;
    show_penalty();
    sub_66dda();
  }
  return 0;
}


