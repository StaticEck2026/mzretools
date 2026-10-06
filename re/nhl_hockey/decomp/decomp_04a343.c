// Decompiled by Ghidra from hockey.elf (via ledisasm ELF export)
// This is machine generated pseudo-C meant as a reference for porting, it does not compile as is.
#include "prototypes.h"

// ================================================================================================
// ai_wing_offense @ 0x4a343 [__watcall]
// ================================================================================================

void __watcall ai_wing_offense(int param_1)

{
  byte bVar1;
  char cVar2;
  short sVar3;
  short sVar4;
  short extraout_DX;
  int extraout_EDX;
  int extraout_EDX_00;
  
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
    *(undefined *)(param_1 + 0x2f) = 0xff;
    *(undefined2 *)(param_1 + 0x26) = 0;
    *(undefined2 *)(param_1 + 0x28) = 8;
  }
  cVar2 = *(char *)(param_1 + 0x27) + -1;
  *(char *)(param_1 + 0x27) = cVar2;
  if (cVar2 < '\0') {
    *(undefined *)(param_1 + 0x27) = *(undefined *)(param_1 + 0x59);
    if ((-1 < *p_puck_carrier) && (*p_puck_carrier < '\x06' != *(short *)(param_1 + 0x6a) < 6)) {
      set_state(param_1,3);
      return;
    }
    sVar3 = *p_puck_y;
    sVar4 = sVar3 + (*(short *)p_puck_vy >> 6);
    dword_e03ba._2_2_ = sVar3;
    if ((*(byte *)(param_1 + 0x44) & 0x80) == 0) {
      dword_e03ba._2_2_ = -sVar3;
      sVar4 = -sVar4;
    }
    dword_e03ae = CONCAT22(sVar4,(undefined2)dword_e03ae);
    sVar3 = 0;
    if ((((-0x4f < sVar4) && (sVar3 = 4, 0x4d < dword_e03ba._2_2_)) &&
        ((*(byte *)(*(int *)(param_1 + 0x6c) + 0x44) & 0x10) == 0)) && (sVar3 = 8, 0xe7 < sVar4)) {
      sVar3 = 0xc;
    }
    if (sVar3 == *(short *)(param_1 + 0x2e)) {
      sVar4 = randomrange(0x80);
      dword_e03ba = CONCAT22(sVar4,(undefined2)dword_e03ba);
      sVar3 = extraout_DX;
      if (sVar4 != 0) goto LAB_0004a4f6;
    }
    *(short *)(param_1 + 0x2e) = sVar3;
    sVar3 = randomrange((int)(short)(*(short *)(&unk_cca1a + sVar3 * 2) * 2));
    *(ushort *)(param_1 + 0x2a) =
         *(short *)(&wing_zones + extraout_EDX * 2) +
         (sVar3 - *(short *)(&unk_cca1a + extraout_EDX * 2)) + (ushort)*(byte *)(param_1 + 0x59);
    sVar3 = randomrange((int)(short)(*(short *)(&unk_cca1e + extraout_EDX * 2) * 2));
    *(short *)(param_1 + 0x2c) =
         (sVar3 - *(short *)(&unk_cca1e + extraout_EDX_00 * 2)) +
         *(short *)(&unk_cca1c + extraout_EDX_00 * 2);
  }
LAB_0004a4f6:
  dword_e03ba._2_2_ = *(short *)(param_1 + 0x2a);
  if (*(short *)(param_1 + 0x1a) != 5) {
    dword_e03ba._2_2_ = -*(short *)(param_1 + 0x2a);
  }
  dword_e03be._2_2_ = *(short *)(param_1 + 0x2c);
  if ((*(byte *)(param_1 + 0x44) & 0x80) == 0) {
    dword_e03ba._2_2_ = -dword_e03ba._2_2_;
    dword_e03be._2_2_ = -dword_e03be._2_2_;
  }
  ai_skate_towards(param_1,ai_near_carrier_check);
  return;
}


// ================================================================================================
// ai_center_defense @ 0x4a53a [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall ai_center_defense(int param_1)

{
  byte bVar1;
  char cVar2;
  short sVar3;
  
  __CHK(0x10);
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
        if (((cVar2 < '\0') &&
            (*(undefined *)(param_1 + 0x27) = *(undefined *)(param_1 + 0x59), -1 < *p_puck_carrier))
           && (*p_puck_carrier < '\x06' == *(short *)(param_1 + 0x6a) < 6)) {
          set_state(param_1,6);
          return;
        }
        dword_e03ba._2_2_ = *p_puck_x >> 1;
        sVar3 = *p_puck_y;
        if ((*(byte *)(param_1 + 0x44) & 0x80) == 0) {
          sVar3 = -sVar3;
        }
        ram0x000e03aa = CONCAT22(sVar3,dword_e03a8._2_2_);
        dword_e03be._2_2_ = -0x71;
        if (-0x4f < sVar3) {
          dword_e03be._2_2_ = (short)(*p_puck_y + -0x71 >> 1);
        }
        if ((*(byte *)(param_1 + 0x44) & 0x80) == 0) {
          dword_e03be._2_2_ = -dword_e03be._2_2_;
        }
        ai_skate_towards(param_1,0);
      }
    }
  }
  return;
}


// ================================================================================================
// ai_center_offense @ 0x4a65c [__watcall]
// ================================================================================================

void __watcall ai_center_offense(int param_1)

{
  byte bVar1;
  char cVar2;
  short sVar3;
  short extraout_DX;
  short sVar4;
  int extraout_EDX;
  int extraout_EDX_00;
  
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
    *(undefined *)(param_1 + 0x2f) = 0xff;
    *(undefined2 *)(param_1 + 0x26) = 0;
    *(undefined2 *)(param_1 + 0x28) = 8;
  }
  cVar2 = *(char *)(param_1 + 0x27) + -1;
  *(char *)(param_1 + 0x27) = cVar2;
  if (cVar2 < '\0') {
    *(undefined *)(param_1 + 0x27) = *(undefined *)(param_1 + 0x59);
    if ((-1 < *p_puck_carrier) && (*p_puck_carrier < '\x06' != *(short *)(param_1 + 0x6a) < 6)) {
      set_state(param_1,5);
      return;
    }
    sVar3 = *p_puck_y;
    if ((*(byte *)(param_1 + 0x44) & 0x80) == 0) {
      sVar3 = -sVar3;
    }
    dword_e03ba = CONCAT22(sVar3,(undefined2)dword_e03ba);
    sVar4 = 0;
    if ((((-0x4f < sVar3) && (sVar4 = 4, 0x4d < sVar3)) &&
        ((*(byte *)(*(int *)(param_1 + 0x6c) + 0x44) & 0x10) == 0)) && (sVar4 = 8, 0xe7 < sVar3)) {
      sVar4 = 0xc;
    }
    if (sVar4 == *(short *)(param_1 + 0x2e)) {
      sVar3 = randomrange(0x80);
      dword_e03ba = CONCAT22(sVar3,(undefined2)dword_e03ba);
      sVar4 = extraout_DX;
      if (sVar3 != 0) goto LAB_0004a7e0;
    }
    *(short *)(param_1 + 0x2e) = sVar4;
    sVar3 = randomrange((int)(short)(*(short *)(&unk_cca3a + sVar4 * 2) * 2));
    *(short *)(param_1 + 0x2a) =
         (sVar3 - *(short *)(&unk_cca3a + extraout_EDX * 2)) +
         *(short *)(&center_zones + extraout_EDX * 2);
    sVar3 = randomrange((int)(short)(*(short *)(&unk_cca3e + extraout_EDX * 2) * 2));
    *(short *)(param_1 + 0x2c) =
         (sVar3 - *(short *)(&unk_cca3e + extraout_EDX_00 * 2)) +
         *(short *)(&unk_cca3c + extraout_EDX_00 * 2);
  }
LAB_0004a7e0:
  dword_e03ba = CONCAT22(*(undefined2 *)(param_1 + 0x2a),(undefined2)dword_e03ba);
  dword_e03be._2_2_ = *(short *)(param_1 + 0x2c);
  if ((*(byte *)(param_1 + 0x44) & 0x80) == 0) {
    dword_e03be._2_2_ = -dword_e03be._2_2_;
  }
  ai_skate_towards(param_1,ai_near_carrier_check);
  return;
}


// ================================================================================================
// skate_idle @ 0x4a80e [__watcall]
// ================================================================================================

void __watcall
skate_idle(int param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  __CHK(8);
  if (((*(byte *)(param_1 + 0x44) & 0x20) == 0) && ((*(byte *)(param_1 + 0x44) & 8) == 0)) {
    apply_skating(param_1,8,unaff_EBX,unaff_ECX,unaff_EDX);
  }
  return;
}


// ================================================================================================
// ai_stanley_cup @ 0x4a832 [__watcall]
// ================================================================================================

void __watcall
ai_stanley_cup(int param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  short sVar1;
  short sVar2;
  undefined4 uVar3;
  
  __CHK(0x10);
  if ((*(byte *)(param_1 + 0x44) & 0x20) == 0) {
    uVar3 = unaff_ECX;
    if ((*(byte *)(param_1 + 0x44) & 2) != 0) {
      *(byte *)(param_1 + 0x44) = *(byte *)(param_1 + 0x44) & 0xfd;
      *(undefined2 *)(param_1 + 0x2a) = 0xffb0;
      *(undefined2 *)(param_1 + 0x2c) = 0;
      *(undefined2 *)(param_1 + 0x26) = 0;
      *(undefined *)(param_1 + 0x46) = 0;
      set_animation(param_1,0xecb,param_1,unaff_ECX,unaff_EDX,unaff_ECX,unaff_EBX);
      stoppage_timer = 0x100;
    }
    if (*(short *)(param_1 + 0x38) == 0) {
      *(undefined2 *)(*(int *)(param_1 + 0x6c) + 0x46 + (*(int *)(param_1 + 0x44) >> 0x18) * 2) =
           0x300;
      set_animation(param_1,0x833,param_1,unaff_ECX,unaff_EDX,uVar3,unaff_EBX);
    }
    sVar1 = direction8((int)(short)(*(short *)(param_1 + 0x2a) - *(short *)(param_1 + 2)),
                       (int)(short)(*(short *)(param_1 + 0x2c) - *(short *)(param_1 + 6)));
    dword_e03ba = CONCAT22(sVar1,(undefined2)dword_e03ba);
    if (sVar1 < 8) {
      sVar1 = *(short *)(param_1 + 0x26);
      sVar2 = sVar1 + -1;
      *(short *)(param_1 + 0x26) = sVar2;
      if (sVar2 < 0) {
        *(short *)(param_1 + 0x26) = sVar1 + 0xb;
        if (*(short *)(param_1 + 0x36) != dword_e03ba._2_2_) {
          *(ushort *)(param_1 + 0x36) = (ushort)((char)*(short *)(param_1 + 0x36) + 1U & 7);
        }
      }
      skating_accelerate(param_1,dword_e03ba >> 0x10);
    }
  }
  return;
}


// ================================================================================================
// ai_celebrate_goal @ 0x4a90f [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall ai_celebrate_goal(int param_1)

{
  short sVar1;
  undefined2 uVar2;
  
  __CHK(0x14);
  if (((short)*p_puck_carrier == *(short *)(param_1 + 0x6a)) &&
     (*p_puck_carrier = -1, (&unk_dff3a)[dword_dff36 >> 0x10] == '\x18')) {
    set_state(&puck,0x1a);
  }
  if ((*(byte *)(param_1 + 0x44) & 0x20) != 0) {
    return;
  }
  sVar1 = handle_line_change(param_1);
  if (sVar1 != 0) {
    return;
  }
  if ((*(byte *)(param_1 + 0x44) & 2) != 0) {
    *(byte *)(param_1 + 0x44) = *(byte *)(param_1 + 0x44) & 0xfd;
    uVar2 = randomrange(0x78);
    *(undefined2 *)(param_1 + 0x26) = uVar2;
    *(undefined2 *)(param_1 + 0x28) = 8;
    if ((game_flags & 0x80) == 0) {
      if ((short)camera < 0) {
        uVar2 = 0xff9c;
      }
      else {
        uVar2 = 100;
      }
      *(undefined2 *)(param_1 + 0x2a) = uVar2;
      sVar1 = camera._2_2_;
      *(short *)(param_1 + 0x2c) = camera._2_2_;
      if ((short)camera < 0) {
        *(short *)(param_1 + 0x2c) = sVar1 + -0x37;
      }
    }
    else {
      *(undefined2 *)(param_1 + 0x2a) = 0xffb0;
      *(undefined2 *)(param_1 + 0x2c) = 0;
    }
    if (*(short *)(param_1 + 0x6a) == _last_shooter) {
      dword_cca58 = 0;
    }
  }
  sVar1 = *(short *)(param_1 + 0x26) + -1;
  *(short *)(param_1 + 0x26) = sVar1;
  if (sVar1 < 0) {
    *(byte *)(param_1 + 0x44) = *(byte *)(param_1 + 0x44) | 0x20;
    dword_e03be = CONCAT22(0x731,(undefined2)dword_e03be);
    uVar2 = randomrange(0x78);
    *(undefined2 *)(param_1 + 0x26) = uVar2;
    if (*(short *)(param_1 + 0x6a) == _last_shooter) {
      dword_e03be = CONCAT22(0x769,(undefined2)dword_e03be);
      if ((dword_cca58 == 0) || ((dword_cca58 < 3 && (sVar1 = randomrange(2), sVar1 == 0)))) {
        *(undefined2 *)(param_1 + 0x26) = 0;
        dword_cca58 = dword_cca58 + 1;
      }
      else {
        dword_cca58 = 0;
        if (*(short *)(param_1 + 0x26) < 0x1f) {
          uVar2 = 0x1e;
        }
        else {
          uVar2 = (undefined2)((uint)*(undefined4 *)(param_1 + 0x24) >> 0x10);
        }
        *(undefined2 *)(param_1 + 0x26) = uVar2;
      }
    }
    set_animation(param_1,dword_e03be >> 0x10);
    return;
  }
  if ((*(byte *)(param_1 + 0x44) & 8) != 0) {
    return;
  }
  dword_e03ba._2_2_ = *(undefined2 *)(param_1 + 0x2a);
  dword_e03be = CONCAT22(*(undefined2 *)(param_1 + 0x2c),(undefined2)dword_e03be);
  ai_skate_towards(param_1,0);
  return;
}


// ================================================================================================
// ai_exit_bench @ 0x4aac2 [__watcall]
// ================================================================================================

void __watcall ai_exit_bench(int param_1)

{
  byte bVar1;
  undefined2 uVar2;
  
  __CHK(0x10);
  bVar1 = *(byte *)(param_1 + 0x44);
  if ((bVar1 & 0x20) == 0) {
    if ((bVar1 & 2) != 0) {
      *(byte *)(param_1 + 0x44) = bVar1 & 0xfd;
      *(undefined2 *)(param_1 + 0xc) = 0;
      *(undefined2 *)(param_1 + 0xe) = 0;
      *(undefined2 *)(param_1 + 0x48) = 0;
      dword_e03ba._2_2_ = *(short *)(param_1 + 0x6a) + -6;
      if (-1 < dword_e03ba._2_2_) {
        dword_e03ba._2_2_ = *(short *)(param_1 + 0x6a) + -4;
      }
      *(short *)(param_1 + 6) = dword_e03ba._2_2_ * 0xe;
      *(undefined2 *)(param_1 + 2) = 0xff60;
      *(undefined2 *)(param_1 + 0x36) = 2;
      *(byte *)(param_1 + 0x44) = *(byte *)(param_1 + 0x44) & 0xcf | 0x20;
      if (*(short *)(param_1 + 0x1a) == 0) {
        uVar2 = 0xd15;
      }
      else {
        uVar2 = 0x7a1;
      }
      set_animation(param_1,uVar2);
      return;
    }
    *(undefined2 *)(param_1 + 0x36) = 4;
    *(byte *)(param_1 + 0x44) = *(byte *)(param_1 + 0x44) & 0xfb;
    *(byte *)(param_1 + 0x45) = *(byte *)(param_1 + 0x45) & 0xdb;
    *(undefined2 *)(param_1 + 0x38) = 0;
    *(undefined2 *)(param_1 + 0xc) = 0x1000;
    ai_default_skate();
  }
  return;
}


// ================================================================================================
// ai_game_misconduct @ 0x4ab87 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall ai_game_misconduct(int param_1)

{
  short sVar1;
  short sVar2;
  undefined2 uVar3;
  int iVar4;
  
  __CHK(0x14);
  if ((*(byte *)(param_1 + 0x44) & 0x20) == 0) {
    if (*(short *)(param_1 + 0x26) == 100) {
      *(byte *)(param_1 + 0x45) = *(byte *)(param_1 + 0x45) & 0xef;
      *(undefined2 *)(param_1 + 0x12) = 0xffff;
      set_state(param_1,0x29);
    }
    else {
      if ((*(byte *)(param_1 + 0x44) & 2) != 0) {
        *(byte *)(param_1 + 0x44) = *(byte *)(param_1 + 0x44) & 0xfd;
        *(byte *)(param_1 + 0x45) = *(byte *)(param_1 + 0x45) | 4;
        if ((*(byte *)(param_1 + 0x44) & 8) != 0) {
          if (*(short *)(param_1 + 0x6a) == _user1_slot) {
            dword_e03b2 = dword_e03b2 & 0xffff;
          }
          else {
            dword_e03b2 = CONCAT22(2,(undefined2)dword_e03b2);
          }
          switch_to_nearest(param_1,(int)dword_e03b2 >> 0x10);
        }
        *(undefined2 *)(param_1 + 0x28) = 8;
        if ((*(byte *)(param_1 + 0x44) & 0x40) == 0) {
          uVar3 = 0xffe4;
        }
        else {
          uVar3 = 0x24;
        }
        *(undefined2 *)(param_1 + 0x2c) = uVar3;
        *(undefined2 *)(param_1 + 0x2a) = 0xff58;
        *(undefined2 *)(param_1 + 0x26) = 0;
        *(byte *)(param_1 + 0x45) = *(byte *)(param_1 + 0x45) | 0x20;
        *(undefined2 *)(param_1 + 0x30) = 0;
        *(undefined2 *)(param_1 + 0x32) = 0;
      }
      sVar2 = *(short *)(param_1 + 0x26);
      sVar1 = sVar2 + -1;
      *(short *)(param_1 + 0x26) = sVar1;
      if (sVar1 < 0) {
        *(short *)(param_1 + 0x26) = sVar2 + 7;
        sVar2 = *(short *)(param_1 + 6) - *(short *)(param_1 + 0x2c);
        dword_e03ba._2_2_ = *(short *)(param_1 + 2) - *(short *)(param_1 + 0x2a);
        if (sVar2 < 0) {
          iVar4 = -(int)sVar2;
        }
        else {
          iVar4 = (int)sVar2;
        }
        if ((iVar4 < 0x15) && (dword_e03ba._2_2_ < 0x21)) {
          if (*(short *)(param_1 + 0x1a) == 0) {
            uVar3 = 1;
          }
          else {
            uVar3 = 0x289;
          }
          dword_e03be = CONCAT22(uVar3,(undefined2)dword_e03be);
          set_animation(param_1,uVar3);
          *(byte *)(param_1 + 0x44) = *(byte *)(param_1 + 0x44) | 4;
          if (*(short *)(param_1 + 0x36) != 4) {
            if (*(short *)(param_1 + 0x36) < 4) {
              sVar2 = 1;
            }
            else {
              sVar2 = -1;
            }
            *(ushort *)(param_1 + 0x36) =
                 sVar2 + (short)((uint)*(undefined4 *)(param_1 + 0x34) >> 0x10) & 7;
          }
          *(undefined2 *)(param_1 + 0xe) = 0;
          *(undefined2 *)(param_1 + 0xc) = 0xf800;
          if (0x10 < dword_e03ba._2_2_) {
            return;
          }
          *(undefined2 *)(param_1 + 0xc) = 0;
          if (*(short *)(param_1 + 0x36) != 4) {
            return;
          }
          *(undefined2 *)(param_1 + 0xc) = 0xf800;
          *(undefined2 *)(param_1 + 0x36) = 2;
          if (*(short *)(param_1 + 0x1a) == 0) {
            uVar3 = 0xd2d;
          }
          else {
            uVar3 = 0x7bf;
          }
          set_animation(param_1,uVar3);
          *(byte *)(param_1 + 0x44) = *(byte *)(param_1 + 0x44) | 0x20;
          *(undefined2 *)(param_1 + 0x26) = 100;
          if (3 < period_idx) {
            return;
          }
          if ((game_flags & 0x40) != 0) {
            return;
          }
          pick_player_for_position
                    ((*(byte *)(param_1 + 0x44) & 0x40) != 0,*(int *)(param_1 + 0x44) >> 0x18);
          return;
        }
      }
      if ((*(byte *)(param_1 + 0x44) & 4) == 0) {
        dword_e03ba._2_2_ = *(undefined2 *)(param_1 + 0x2a);
        dword_e03be = CONCAT22(*(undefined2 *)(param_1 + 0x2c),(undefined2)dword_e03be);
        ai_skate_towards(param_1,0);
        return;
      }
    }
  }
  return;
}


// ================================================================================================
// ai_penalty_box @ 0x4adab [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall ai_penalty_box(int param_1)

{
  char cVar1;
  byte bVar2;
  int iVar3;
  short sVar4;
  short sVar5;
  
  __CHK(0x18);
  if ((*(byte *)(param_1 + 0x44) & 0x20) == 0) {
    if ((*(byte *)(param_1 + 0x44) & 2) != 0) {
      *(byte *)(param_1 + 0x44) = *(byte *)(param_1 + 0x44) & 0xfd;
      *(byte *)(param_1 + 0x45) = *(byte *)(param_1 + 0x45) | 4;
      if ((*(byte *)(param_1 + 0x44) & 8) != 0) {
        if (*(short *)(param_1 + 0x6a) == _user1_slot) {
          dword_e03b2 = dword_e03b2 & 0xffff;
        }
        else {
          dword_e03b2 = CONCAT22(2,(undefined2)dword_e03b2);
        }
        switch_to_nearest(param_1,(int)dword_e03b2 >> 0x10);
      }
      *(undefined2 *)(param_1 + 0x28) = 8;
      if ((*(byte *)(param_1 + 0x44) & 0x40) == 0) {
        dword_e03ba._2_2_ = -0xb;
        dword_e03be._0_2_ = 0xffff;
        cVar1 = penalized_count;
      }
      else {
        dword_e03ba._2_2_ = 0xb;
        dword_e03be._0_2_ = 0;
        cVar1 = byte_e9abb;
      }
      dword_e03be._2_2_ = (short)cVar1 & 0xf;
      if (2 < dword_e03be._2_2_) {
        dword_e03be._2_2_ = 2;
        dword_e03be_4 = 0;
      }
      sVar5 = dword_e03be._2_2_ + 3;
      ram0x000e03c0 = CONCAT22(dword_e03be_4,sVar5);
      *(short *)(param_1 + 0x2c) = sVar5 * dword_e03ba._2_2_;
      *(undefined2 *)(param_1 + 0x2a) = 0xa0;
      *(undefined2 *)(param_1 + 0x26) = 0;
      *(byte *)(param_1 + 0x45) = *(byte *)(param_1 + 0x45) | 0x20;
      *(undefined2 *)(param_1 + 0x30) = 0;
      *(undefined2 *)(param_1 + 0x32) = 0;
    }
    sVar5 = *(short *)(param_1 + 6) - *(short *)(param_1 + 0x2c);
    if (sVar5 < 0) {
      iVar3 = -(int)sVar5;
    }
    else {
      iVar3 = (int)sVar5;
    }
    if ((iVar3 < 0xd) &&
       (dword_e03ba._2_2_ = *(short *)(param_1 + 2) - *(short *)(param_1 + 0x2a),
       -0x19 < dword_e03ba._2_2_)) {
      sVar5 = *(short *)(param_1 + 0x26);
      sVar4 = sVar5 + -1;
      *(short *)(param_1 + 0x26) = sVar4;
      if (sVar4 < 0) {
        *(short *)(param_1 + 0x26) = sVar5 + 7;
        *(byte *)(param_1 + 0x44) = *(byte *)(param_1 + 0x44) | 4;
        set_animation(param_1,0x289);
        dword_e03ac = 4;
        if (*(short *)(param_1 + 0x36) != 4) {
          bVar2 = 4U - (char)*(short *)(param_1 + 0x36) & 7;
          dword_e03ac = (ushort)bVar2;
          if (bVar2 < 5) {
            sVar5 = 1;
          }
          else {
            sVar5 = -1;
          }
          *(ushort *)(param_1 + 0x36) =
               sVar5 + (short)((uint)*(undefined4 *)(param_1 + 0x34) >> 0x10) & 7;
        }
        *(undefined2 *)(param_1 + 0xe) = 0;
        *(undefined2 *)(param_1 + 0xc) = 0x1000;
        if ((-9 < dword_e03ba._2_2_) &&
           (*(undefined2 *)(param_1 + 0xc) = 0, dword_e03ac == *(ushort *)(param_1 + 0x36))) {
          *(byte *)(param_1 + 0x44) = *(byte *)(param_1 + 0x44) | 0x20;
          *(undefined2 *)(param_1 + 0x36) = 2;
          set_animation(param_1,0x7a1);
          *(byte *)(param_1 + 0x45) = *(byte *)(param_1 + 0x45) & 0xef;
          sVar5 = *(short *)(*(int *)(param_1 + 0x6c) + 0x36);
          if (4 < sVar5) {
            *(short *)(*(int *)(param_1 + 0x6c) + 0x36) = sVar5 + -1;
          }
          set_state(param_1,0xd);
        }
      }
    }
    else {
      dword_e03ba._2_2_ = *(short *)(param_1 + 0x2a);
      ram0x000e03c0 = CONCAT22(dword_e03be_4,*(undefined2 *)(param_1 + 0x2c));
      ai_skate_towards(param_1,0);
    }
  }
  return;
}


// ================================================================================================
// ai_door_open @ 0x4affb [__watcall]
// ================================================================================================

void __watcall ai_door_open(int param_1)

{
  __CHK(8);
  if ((*(byte *)(param_1 + 0x44) & 0x20) == 0) {
    if ((*(byte *)(param_1 + 0x44) & 0x40) == 0) {
      penalized_count = penalized_count + '\x01';
    }
    else {
      byte_e9abb = byte_e9abb + '\x01';
    }
    *(undefined *)(param_1 + 0x1b) = 0xff;
    *(undefined2 *)(param_1 + 0x12) = 0xffff;
  }
  return;
}


// ================================================================================================
// ai_exit_penalty_box @ 0x4b02d [__watcall]
// ================================================================================================

void __watcall
ai_exit_penalty_box(int param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  
  __CHK(0x10);
  bVar1 = *(byte *)(param_1 + 0x44);
  if ((bVar1 & 0x20) == 0) {
    if ((bVar1 & 2) != 0) {
      uVar2 = CONCAT22((short)((uint)unaff_ECX >> 0x10),CONCAT11(bVar1,bVar1)) & 0xffffedff | 0x404;
      *(char *)(param_1 + 0x44) = (char)(uVar2 >> 8);
      *(byte *)(param_1 + 0x45) = *(byte *)(param_1 + 0x45) | 4;
      if ((*(byte *)(param_1 + 0x44) & 0x40) == 0) {
        penalized_count = penalized_count + -1;
        uVar2 = CONCAT31((int3)(uVar2 >> 8),penalized_count);
        if (penalized_count < '\x03') {
          iVar3 = (int)penalized_count;
        }
        else {
          iVar3 = 2;
        }
        iVar3 = iVar3 * -0xb + -0x21;
        *(short *)(param_1 + 6) = (short)iVar3;
      }
      else {
        byte_e9abb = byte_e9abb + -1;
        if (byte_e9abb < '\x03') {
          iVar3 = (int)byte_e9abb;
        }
        else {
          iVar3 = 2;
        }
        *(short *)(param_1 + 6) = (short)(iVar3 << 2) * 4 + (short)iVar3 * -5 + 0x21;
      }
      *(undefined2 *)(param_1 + 0xc) = 0;
      *(undefined2 *)(param_1 + 0xe) = 0;
      *(undefined2 *)(param_1 + 2) = 0x9e;
      *(undefined2 *)(param_1 + 0x36) = 2;
      *(byte *)(param_1 + 0x44) = *(byte *)(param_1 + 0x44) | 0x20;
      set_animation(param_1,0x7bf,iVar3,uVar2,unaff_EDX,unaff_ECX,unaff_EBX);
      sort_draw_order2();
      return;
    }
    *(undefined2 *)(param_1 + 0x36) = 4;
    *(undefined *)(param_1 + 0x43) = 0xff;
    *(undefined *)(param_1 + 0x42) = 0xff;
    *(byte *)(param_1 + 0x44) = *(byte *)(param_1 + 0x44) & 0xf3;
    *(byte *)(param_1 + 0x45) = *(byte *)(param_1 + 0x45) & 0xdb;
    *(undefined2 *)(param_1 + 0xc) = 0xf000;
    ai_default_skate();
  }
  return;
}


// ================================================================================================
// ai_bench @ 0x4b12c [__watcall]
// ================================================================================================

void __watcall ai_bench(int param_1)

{
  short sVar1;
  undefined2 uVar2;
  int iVar3;
  int iVar4;
  short sVar5;
  code *pcVar6;
  
  __CHK(0x14);
  if ((*(byte *)(param_1 + 0x44) & 0x20) == 0) {
    if (*(short *)(param_1 + 0x26) == 100) {
      *(undefined2 *)(param_1 + 0x12) = 0xffff;
      iVar3 = *(int *)(param_1 + 0x6c);
      iVar4 = (*(int *)(param_1 + 0x44) >> 0x18) * 2 + iVar3;
      if ((*(short *)(iVar4 + 0x7e) < 1) && (-3 < *(int *)(iVar4 + 0x7c) >> 0x10)) {
        *(undefined2 *)(iVar4 + 0x7e) = 0xfffe;
        *(undefined *)((*(int *)(param_1 + 0x44) >> 0x18) * 0x27 + *(int *)(iVar3 + 0xee)) = 3;
      }
      if ((*(char *)(param_1 + 0x42) == '\0') != *(char *)(param_1 + 0x43) < '\x19') {
        *(short *)(param_1 + 0x1a) = (short)*(char *)(param_1 + 0x42);
      }
      set_default_state(param_1);
      if ((game_flags & 1) != 0) {
        *(undefined2 *)(param_1 + 0x2e) = 0;
        set_state_reset(param_1,0x27);
      }
      dword_e03ae = CONCAT22((short)*(char *)(param_1 + 0x43),(undefined2)dword_e03ae);
      *(undefined *)(param_1 + 0x43) = 0xff;
      *(undefined *)(param_1 + 0x42) = 0xff;
      put_player_on_ice(param_1,dword_e03ae >> 0x10);
    }
    else {
      sVar1 = handle_line_change(param_1);
      if (sVar1 == 0) {
        if (((*(byte *)(param_1 + 0x45) & 0x10) != 0) || (((byte)stop_flags & 1) != 0)) {
          skate_idle(param_1);
          return;
        }
        if (((((game_flags & 1) != 0) && (*(short *)(param_1 + 0x1a) == 0)) &&
            ((*(int *)(*(int *)(param_1 + 0x6c) + 0x36) >> 0x10 & 0xfff0U) == 0xff00)) &&
           (iVar3 = late_game_pull_goalie((*(byte *)(param_1 + 0x44) & 0x40) != 0), iVar3 == 0)) {
          *(undefined *)(param_1 + 0x42) = 0xff;
          *(undefined *)(param_1 + 0x43) = *(undefined *)(param_1 + 0x42);
          set_state(param_1,0x27);
          return;
        }
        if ((*(byte *)(param_1 + 0x44) & 2) != 0) {
          *(byte *)(param_1 + 0x44) = *(byte *)(param_1 + 0x44) & 0xfd;
          *(undefined2 *)(param_1 + 0x28) = 8;
          if ((*(byte *)(param_1 + 0x44) & 0x40) == 0) {
            uVar2 = 0xffce;
          }
          else {
            uVar2 = 0x41;
          }
          *(undefined2 *)(param_1 + 0x2c) = uVar2;
          *(undefined2 *)(param_1 + 0x2a) = 0xff58;
          *(undefined2 *)(param_1 + 0x26) = 0;
        }
        if (*(char *)(param_1 + 0x43) == *(char *)(param_1 + 0x47)) {
          *(byte *)(param_1 + 0x45) = *(byte *)(param_1 + 0x45) & 0xfb;
          if ((*(char *)(param_1 + 0x42) == '\0') != *(char *)(param_1 + 0x43) < '\x19') {
            *(short *)(param_1 + 0x1a) = (short)*(char *)(param_1 + 0x42);
          }
          set_default_state(param_1);
          *(undefined *)(param_1 + 0x43) = 0xff;
          *(undefined *)(param_1 + 0x42) = 0xff;
          return;
        }
        if (*(short *)(param_1 + 0x1a) == 0) {
          *(byte *)(param_1 + 0x48) = *(byte *)(param_1 + 0x48) | 3;
        }
        sVar1 = *(short *)(param_1 + 0x26);
        sVar5 = sVar1 + -1;
        *(short *)(param_1 + 0x26) = sVar5;
        if (sVar5 < 0) {
          *(short *)(param_1 + 0x26) = sVar1 + 7;
          sVar1 = *(short *)(param_1 + 6) - *(short *)(param_1 + 0x2c);
          dword_e03ba._2_2_ = *(short *)(param_1 + 2) - *(short *)(param_1 + 0x2a);
          if (sVar1 < 0) {
            iVar3 = -(int)sVar1;
          }
          else {
            iVar3 = (int)sVar1;
          }
          if ((iVar3 < 0x29) && (dword_e03ba._2_2_ < 0x21)) {
            if (*(short *)(param_1 + 0x1a) == 0) {
              uVar2 = 1;
            }
            else {
              uVar2 = 0x289;
            }
            dword_e03be = CONCAT22(uVar2,(undefined2)dword_e03be);
            set_animation(param_1,uVar2);
            *(byte *)(param_1 + 0x44) = *(byte *)(param_1 + 0x44) | 4;
            if (*(short *)(param_1 + 0x36) != 4) {
              if (*(short *)(param_1 + 0x36) < 4) {
                sVar1 = 1;
              }
              else {
                sVar1 = -1;
              }
              *(ushort *)(param_1 + 0x36) =
                   sVar1 + (short)((uint)*(undefined4 *)(param_1 + 0x34) >> 0x10) & 7;
            }
            *(undefined2 *)(param_1 + 0xe) = 0;
            *(undefined2 *)(param_1 + 0xc) = 0xf800;
            if (0x10 < dword_e03ba._2_2_) {
              return;
            }
            *(undefined2 *)(param_1 + 0xc) = 0;
            if (*(short *)(param_1 + 0x36) != 4) {
              return;
            }
            *(undefined2 *)(param_1 + 0xc) = 0xf800;
            *(undefined2 *)(param_1 + 0x36) = 2;
            if (*(short *)(param_1 + 0x1a) == 0) {
              uVar2 = 0xd2d;
            }
            else {
              uVar2 = 0x7bf;
            }
            set_animation(param_1,uVar2);
            *(byte *)(param_1 + 0x44) = *(byte *)(param_1 + 0x44) | 0x20;
            *(undefined2 *)(param_1 + 0x26) = 100;
            return;
          }
        }
        if ((*(byte *)(param_1 + 0x44) & 4) == 0) {
          dword_e03ba._2_2_ = *(undefined2 *)(param_1 + 0x2a);
          dword_e03be = CONCAT22(*(undefined2 *)(param_1 + 0x2c),(undefined2)dword_e03be);
          if (((game_flags & 1) == 0) && (*(short *)(param_1 + 0x1a) != 0)) {
            pcVar6 = ai_near_carrier_check;
          }
          else {
            pcVar6 = (code *)0x0;
          }
          ai_skate_towards(param_1,pcVar6);
          return;
        }
      }
    }
  }
  return;
}


// ================================================================================================
// goalie_puck_vector @ 0x4b467 [__watcall]
// ================================================================================================

void __watcall goalie_puck_vector(int param_1)

{
  int iVar1;
  
  __CHK(0x14);
  iVar1 = *(int *)(param_1 + 4) >> 0x10;
  dword_e03ba._2_2_ = *p_puck_x - *(short *)(param_1 + 2);
  dword_e03be._2_2_ = *p_puck_y - *(short *)(param_1 + 6);
  if (iVar1 < 0) {
    if ((-0xe9 < iVar1) && (*p_puck_y < -0xe8)) {
      dword_e03be._2_2_ = 1;
      return;
    }
  }
  else if ((iVar1 < 0xe8) && (0xe7 < *p_puck_y)) {
    dword_e03be._2_2_ = -1;
  }
  return;
}


// ================================================================================================
// goalie_turn_towards @ 0x4b4e9 [__watcall]
// ================================================================================================

void __watcall goalie_turn_towards(int param_1,int unaff_EDX)

{
  short sVar1;
  short sVar2;
  short sVar3;
  
  __CHK(0x14);
  sVar3 = *(short *)(param_1 + 0x36);
  if ((*(short *)(param_1 + 0x4c) != 0) || (sVar3 - unaff_EDX == 0)) {
    sVar3 = *(short *)(param_1 + 0x4c) + -1;
    *(short *)(param_1 + 0x4c) = sVar3;
    if (sVar3 < 0) {
      *(undefined2 *)(param_1 + 0x4c) = 0;
    }
    return;
  }
  sVar2 = (short)((int)(sVar3 - unaff_EDX & 4U) >> 1) + -1;
  sVar1 = (short)unaff_EDX;
  if ((*(byte *)(param_1 + 0x44) & 0x80) == 0) {
    if ((((sVar3 < 1) || (3 < sVar3)) || (sVar1 < 5)) || (7 < sVar1)) {
      if (((sVar3 < 5) || (7 < sVar3)) || ((sVar1 < 1 || (3 < sVar1)))) goto LAB_0004b591;
      goto LAB_0004b58c;
    }
  }
  else {
    if (((0 < sVar3) && (sVar3 < 4)) && ((4 < sVar1 && (sVar1 < 8)))) {
LAB_0004b58c:
      sVar2 = -1;
      goto LAB_0004b591;
    }
    if ((((sVar3 < 5) || (7 < sVar3)) || (sVar1 < 1)) || (3 < sVar1)) goto LAB_0004b591;
  }
  sVar2 = 1;
LAB_0004b591:
  *(ushort *)(param_1 + 0x36) = sVar2 + *(short *)(param_1 + 0x36) & 7;
  *(undefined2 *)(param_1 + 0x4c) = 2;
  return;
}


// ================================================================================================
// ai_goalie_get_puck @ 0x4b5c2 [__watcall]
// ================================================================================================

void __watcall ai_goalie_get_puck(int *param_1)

{
  short sVar1;
  int iVar2;
  char cVar3;
  int *extraout_EDX;
  int iVar4;
  
  __CHK(0x14);
  if (0 < *(short *)((int)param_1 + 0x4a)) {
    *(short *)((int)param_1 + 0x4a) = *(short *)((int)param_1 + 0x4a) + -1;
  }
  *(byte *)(param_1 + 0x12) = *(byte *)(param_1 + 0x12) | 6;
  iVar4 = *param_1 >> 0x10;
  iVar2 = param_1[1] >> 0x10;
  if (iVar2 < 0) {
    iVar2 = -iVar2;
  }
  if ((((-0x29 < iVar4) && (iVar4 < 0x29)) && (0xc4 < iVar2)) && (iVar2 < 0xe4)) {
    *(byte *)(param_1 + 0x12) = *(byte *)(param_1 + 0x12) & 0xfb;
  }
  if (((-0x31 < iVar4) && (iVar4 < 0x31)) && (0xc4 < iVar2)) {
    *(byte *)(param_1 + 0x12) = *(byte *)(param_1 + 0x12) & 0xfd;
  }
  if (((*(byte *)(param_1 + 0x11) & 8) != 0) || ((game_flags & 1) != 0)) goto LAB_0004b641;
  sVar1 = handle_line_change(param_1);
  if (sVar1 == 0) {
    if ((*(byte *)(extraout_EDX + 0x11) & 2) != 0) {
      *(byte *)(extraout_EDX + 0x11) = *(byte *)(extraout_EDX + 0x11) & 0xfd;
      *(undefined2 *)((int)extraout_EDX + 0x26) = 0;
    }
    cVar3 = *(char *)((int)extraout_EDX + 0x27) + -1;
    *(char *)((int)extraout_EDX + 0x27) = cVar3;
    if (cVar3 < '\0') {
      *(char *)((int)extraout_EDX + 0x27) =
           (char)((int)(uint)*(byte *)((int)extraout_EDX + 0x5a) >> 2);
      param_1 = extraout_EDX;
      if (-1 < *p_puck_carrier) {
LAB_0004b641:
        ai_default_skate(param_1);
        return;
      }
      if (*(short *)p_puck_vy < 0 != ((*(byte *)(extraout_EDX + 0x11) & 0x80) != 0)) {
        sVar1 = *(short *)p_puck_vy;
        if (sVar1 < 0) {
          iVar2 = -(int)sVar1;
        }
        else {
          iVar2 = (int)sVar1;
        }
        if (0x800 < iVar2) goto LAB_0004b641;
      }
      if (*(int *)(extraout_EDX[0x1c] + 0x3e) < 0x96) goto LAB_0004b641;
    }
    ai_chase_puck(extraout_EDX);
  }
  return;
}


// ================================================================================================
// goalie_clamp_target @ 0x4b6f4 [__watcall]
// ================================================================================================

void __watcall goalie_clamp_target(int param_1)

{
  int iVar1;
  
  __CHK(0xc);
  if (*(short *)(param_1 + 6) < 0) {
    iVar1 = -(*(int *)(param_1 + 4) >> 0x10);
  }
  else {
    iVar1 = *(int *)(param_1 + 4) >> 0x10;
  }
  if (iVar1 < 0xe8) {
    if ((short)*p_puck_carrier == *(short *)(param_1 + 0x6a)) {
      dword_e03ba._2_2_ = 0;
    }
    if (0xe3 < dword_e03be._2_2_) {
      dword_e03be = CONCAT22(0xe3,(undefined2)dword_e03be);
    }
    if (dword_e03be >> 0x10 < -0xe3) {
      dword_e03be = CONCAT22(0xff1d,(undefined2)dword_e03be);
    }
  }
  dword_e03be._2_2_ = dword_e03be._2_2_ - dword_e03ae._2_2_;
  return;
}


// ================================================================================================
// ai_goalie @ 0x4b774 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall ai_goalie(int *param_1)

{
  bool bVar1;
  uint uVar2;
  char cVar3;
  short sVar4;
  ushort uVar5;
  undefined2 uVar6;
  short sVar7;
  undefined4 *puVar8;
  uint uVar9;
  short extraout_var;
  short extraout_var_00;
  int iVar10;
  int iVar11;
  int iVar12;
  int extraout_EDX;
  short *psVar13;
  bool bVar14;
  
  __CHK(0x24);
  bVar1 = true;
  if (0 < *(short *)((int)param_1 + 0x4a)) {
    *(short *)((int)param_1 + 0x4a) = *(short *)((int)param_1 + 0x4a) + -1;
  }
  if ((short)*p_puck_carrier != *(short *)((int)param_1 + 0x6a)) {
    *(undefined *)((int)param_1 + 99) = 0;
  }
  *(byte *)(param_1 + 0x12) = *(byte *)(param_1 + 0x12) | 6;
  iVar12 = *param_1 >> 0x10;
  iVar11 = param_1[1] >> 0x10;
  if (iVar11 < 0) {
    iVar11 = -iVar11;
  }
  if ((((-0x29 < iVar12) && (iVar12 < 0x29)) && (0xc4 < iVar11)) && (iVar11 < 0xe4)) {
    *(byte *)(param_1 + 0x12) = *(byte *)(param_1 + 0x12) & 0xfb;
  }
  if (((-0x31 < iVar12) && (iVar12 < 0x31)) && (0xc4 < iVar11)) {
    *(byte *)(param_1 + 0x12) = *(byte *)(param_1 + 0x12) & 0xfd;
  }
  sVar4 = handle_line_change(param_1);
  if (sVar4 != 0) {
    return;
  }
  if ((*(byte *)(param_1 + 0x11) & 2) != 0) {
    *(byte *)(param_1 + 0x11) = *(byte *)(param_1 + 0x11) & 0xfd;
    *(undefined2 *)((int)param_1 + 0x26) = 0;
    *(undefined2 *)(param_1 + 10) = 8;
    *(undefined *)((int)param_1 + 0x2d) = 0xff;
  }
  if (iVar11 < 0xe5) {
    iVar12 = extraout_EDX;
    if (extraout_EDX < 0) {
      iVar12 = -extraout_EDX;
    }
    if (((0x34 < iVar12) || (0xee < iVar11)) || (iVar11 < 0xb3)) {
      if (extraout_EDX < 0) {
        uVar6 = 0xfffc;
      }
      else {
        uVar6 = 4;
      }
      dword_e03ba = CONCAT22(uVar6,(undefined2)dword_e03ba);
      if ((*(byte *)(param_1 + 0x11) & 0x80) == 0) {
        uVar6 = 0xc4;
      }
      else {
        uVar6 = 0xff3c;
      }
      dword_e03be = CONCAT22(uVar6,(undefined2)dword_e03be);
      ai_skate_towards(param_1,0);
      return;
    }
    if (((*(byte *)((int)param_1 + 0x45) & 2) == 0) && ((*(byte *)(param_1 + 0x11) & 0x20) == 0)) {
      if ((short)*p_puck_carrier == *(short *)((int)param_1 + 0x6a)) {
        uVar6 = 0x99;
      }
      else {
        uVar6 = 1;
      }
      set_animation(param_1,uVar6);
    }
    if ((game_flags & 1) != 0) {
      return;
    }
    if (-1 < *(short *)((int)param_1 + 0x2e)) {
      if ((short)*p_puck_carrier == *(short *)((int)param_1 + 0x6a)) {
        if (iVar11 < 0x9b) {
          *(undefined2 *)((int)param_1 + 0x2e) = 0;
        }
        sVar4 = *(short *)((int)param_1 + 0x2e) + -1;
        *(short *)((int)param_1 + 0x2e) = sVar4;
        if (sVar4 < 0) {
          queue_infraction(param_1,4);
        }
      }
      else {
        *(undefined2 *)((int)param_1 + 0x2e) = 0xffff;
      }
    }
    if ((*(byte *)((int)param_1 + 0x45) & 2) != 0) {
      return;
    }
    sVar4 = *(short *)((int)param_1 + 0x26) + -1;
    *(short *)((int)param_1 + 0x26) = sVar4;
    if (-1 < sVar4) {
      sVar4 = (short)*(char *)(param_1 + 10);
      ram0x000e03aa = CONCAT22(sVar4,dword_e03a8._2_2_);
      goto joined_r0x0004b97c;
    }
    *(ushort *)((int)param_1 + 0x26) = *(byte *)((int)param_1 + 0x5a) / 3;
    if ((*(byte *)(param_1 + 0x11) & 8) == 0) {
      uVar5 = *p_puck_y ^ *(ushort *)((int)param_1 + 6);
      dword_e03be = CONCAT22(uVar5,(undefined2)dword_e03be);
      if ((short)uVar5 < 0) {
        dword_e03ba = dword_e03ba & 0xffff;
        if ((*(byte *)(param_1 + 0x11) & 0x80) == 0) {
          uVar6 = 0xd4;
        }
        else {
          uVar6 = 0xff2c;
        }
        ram0x000e03aa = CONCAT22(uVar6,dword_e03a8._2_2_);
        goto LAB_0004c549;
      }
      *(short *)(param_1 + 0xb) = *(short *)(param_1 + 0xb) + -1;
      if ((short)*p_puck_carrier != *(short *)((int)param_1 + 0x6a)) goto LAB_0004baf5;
      if (*(short *)((int)param_1 + 0x2e) < 0) {
        *(undefined2 *)((int)param_1 + 0x2e) = 0x5a;
      }
      *(undefined2 *)(param_1 + 0xb) = 0xffff;
      if ((*(short *)((int)param_1 + 0x2e) < 0x5a) && (sVar4 = randomrange(4), sVar4 == 0)) {
        if (*(short *)((int)param_1 + 0x6a) < 6) {
          iVar11 = 6;
        }
        else {
          iVar11 = 0;
        }
        puVar8 = &entities + iVar11 * 0x20;
        for (sVar4 = 0; sVar4 < 6; sVar4 = sVar4 + 1) {
          if (((((*(byte *)((int)puVar8 + 0x45) & 4) == 0) && (0 < *(short *)((int)puVar8 + 0x1a)))
              && (*(short *)((int)puVar8 + 0x4e) < 0x23)) && (*(short *)((int)puVar8 + 0x4e) < 0x14)
             ) {
            *(byte *)(param_1 + 0x11) = *(byte *)(param_1 + 0x11) | 0x20;
            *(byte *)((int)param_1 + 0x45) = *(byte *)((int)param_1 + 0x45) | 2;
            set_animation(param_1,0x1135);
            return;
          }
          puVar8 = puVar8 + 0x20;
        }
        goalie_pass_mode = 1;
        sVar4 = ai_choose_pass_target(param_1);
        if (sVar4 != 0) {
          return;
        }
      }
    }
    else {
LAB_0004baf5:
      dword_e03ba = CONCAT22(*p_puck_x - *(short *)((int)param_1 + 2),(undefined2)dword_e03ba);
      dword_e03be = CONCAT22(*p_puck_y - *(short *)((int)param_1 + 6),(undefined2)dword_e03be);
      if (*p_puck_carrier < '\0') {
        if ((*(short *)(param_1 + 0xb) == 0) && (*(short *)((int)param_1 + 0x4e) < 0x2d)) {
          uVar5 = *p_puck_y;
          if ((short)uVar5 < 0) {
            iVar11 = -(int)(short)uVar5;
          }
          else {
            iVar11 = (int)(short)uVar5;
          }
          if (((iVar11 < 0xe9) && (*(int *)(param_1[0x1c] + 0x3e) < 0x3c)) &&
             (sVar4 = randomrange(0x100), sVar4 < 10)) {
            uVar6 = direction8((int)dword_e03ba >> 0x10,(int)dword_e03be >> 0x10);
            *(undefined2 *)((int)param_1 + 0x36) = uVar6;
            *(undefined2 *)((int)param_1 + 0x3e) = 8;
            *(byte *)(param_1 + 0x11) = *(byte *)(param_1 + 0x11) | 0x20;
            *(byte *)((int)param_1 + 0x45) = *(byte *)((int)param_1 + 0x45) | 2;
            set_animation(param_1,0x181);
            *(undefined2 *)((int)param_1 + 0x4a) = 0x168;
            if (0x4b0 < crowd_noise._2_2_) {
              return;
            }
            if ((short)(crowd_noise._2_2_ + 0x96) < 0x4b1) {
              crowd_noise._2_2_ = crowd_noise._2_2_ + 0x96;
              return;
            }
            crowd_noise._2_2_ = 0x4b0;
            return;
          }
        }
      }
      else if (((*p_puck_carrier >= '\0') &&
               (*p_puck_carrier < '\x06' != *(short *)((int)param_1 + 0x6a) < 6)) &&
              ((*(short *)((int)param_1 + 0x4a) == 0 &&
               ((sVar4 = randomrange(0x100), sVar4 < 10 && (*(short *)((int)param_1 + 0x4e) < 0x23))
               )))) {
        uVar5 = *p_puck_y;
        if ((short)uVar5 < 0) {
          iVar11 = -(int)(short)uVar5;
        }
        else {
          iVar11 = (int)(short)uVar5;
        }
        if (iVar11 < 0xe9) {
          uVar6 = direction8((int)dword_e03ba >> 0x10,(int)dword_e03be >> 0x10);
          *(undefined2 *)((int)param_1 + 0x36) = uVar6;
          *(byte *)(param_1 + 0x11) = *(byte *)(param_1 + 0x11) | 0x20;
          *(byte *)((int)param_1 + 0x45) = *(byte *)((int)param_1 + 0x45) | 2;
          set_animation(param_1,0x1095);
          *(undefined2 *)((int)param_1 + 0x4a) = 0xf0;
          return;
        }
      }
    }
    psVar13 = (short *)((int)&goal_prediction + 2);
    dword_e03ae = CONCAT22(0xe4,(undefined2)dword_e03ae);
    dword_e03b2 = CONCAT22(0xe8,(undefined2)dword_e03b2);
    if ((*(byte *)(param_1 + 0x11) & 0x80) != 0) {
      dword_e03ae = CONCAT22(0xff1c,(undefined2)dword_e03ae);
      dword_e03b2 = CONCAT22(0xff18,(undefined2)dword_e03b2);
      psVar13 = &DAT_000df818;
    }
    if (*(short *)((int)param_1 + 6) < 0) {
      iVar11 = -(param_1[1] >> 0x10);
    }
    else {
      iVar11 = param_1[1] >> 0x10;
    }
    if (iVar11 < 0xe5) {
      dword_e03ba = CONCAT22(*p_puck_x,(undefined2)dword_e03ba);
      dword_e03be = CONCAT22(*p_puck_y,(undefined2)dword_e03be);
      goalie_clamp_target(param_1);
      sVar7 = direction8((int)dword_e03ba >> 0x10,(int)dword_e03be >> 0x10);
      sVar4 = *(short *)((int)param_1 + 0x36);
      if ((short)(sVar7 - sVar4) != 0) {
        sVar7 = (short)((int)(-(int)(short)(sVar7 - sVar4) & 4U) >> 1) + -1;
        dword_e03be._2_2_ = sVar4 + sVar7;
        if ((1 << ((byte)sVar4 & 0x1f) & 0x42U) != 0) {
          if ((*(byte *)(param_1 + 0x11) & 0x80) == 0) {
            uVar9 = 0x83;
          }
          else {
            uVar9 = 0x38;
          }
          if ((uVar9 & 1 << ((byte)dword_e03be._2_2_ & 0x1f)) != 0) {
            dword_e03be._2_2_ = dword_e03be._2_2_ + sVar7 * -2;
          }
        }
        *(ushort *)((int)param_1 + 0x36) = dword_e03be._2_2_ & 7;
      }
      dword_e03ba._2_2_ = 0xe0;
      uVar5 = *p_puck_y;
      if ((short)uVar5 < 0) {
        iVar11 = -(int)(short)uVar5;
      }
      else {
        iVar11 = (int)(short)uVar5;
      }
      if (0xbb < iVar11) {
        dword_e03ba._2_2_ = 0xa0;
      }
      dword_e03be = CONCAT22(dword_e03ba._2_2_,(undefined2)dword_e03be);
      imul32((int)*(short *)p_puck_vx,dword_e03ba._2_2_);
      dword_e03ba = CONCAT22(*p_puck_x + extraout_var,(undefined2)dword_e03ba);
      imul32((int)*(short *)p_puck_vy,(int)dword_e03be >> 0x10);
      dword_e03be._2_2_ = *p_puck_y + extraout_var_00;
      goalie_clamp_target(param_1);
      iVar11 = approx_distance((int)dword_e03ba >> 0x10,(int)(short)dword_e03be._2_2_);
      if (0x1d < iVar11) {
        ram0x000e03aa = CONCAT22((short)iVar11 + 1,dword_e03a8._2_2_);
        uVar5 = *p_puck_y;
        if ((short)uVar5 < 0) {
          iVar11 = -(int)(short)uVar5;
        }
        else {
          iVar11 = (int)(short)uVar5;
        }
        if ((iVar11 < 0x74) && (iVar11 = count_defenders_ahead(), iVar11 != 0)) {
          dword_e03b2._2_2_ = 0x14;
          if ((action_flags & 8) != 0) {
            dword_e03b2._2_2_ = 0x1c;
          }
        }
        else {
          dword_e03b2._2_2_ = 0x12;
          if ((action_flags & 8) != 0) {
            dword_e03b2._2_2_ = 0x1a;
          }
        }
        dword_e03be._2_2_ =
             (ushort)(((int)dword_e03b2._2_2_ * (int)(short)dword_e03be._2_2_) /
                     ((int)ram0x000e03aa >> 0x10));
        dword_e03b2._2_2_ = dword_e03b2._2_2_ + 8;
        dword_e03ba = CONCAT22((short)(((int)dword_e03b2._2_2_ * ((int)dword_e03ba >> 0x10)) /
                                      ((int)ram0x000e03aa >> 0x10)),(undefined2)dword_e03ba);
      }
      sVar4 = dword_e03be._2_2_ + dword_e03ae._2_2_;
      dword_e03be = CONCAT22(sVar4,(undefined2)dword_e03be);
      ram0x000e03aa = CONCAT22(sVar4,dword_e03a8._2_2_);
      iVar12 = (int)(short)*p_puck_y;
      iVar11 = ((int)*(short *)p_puck_vy >> 9) + iVar12;
      if (*p_puck_carrier < '\0') {
        if ((short)*p_puck_y < 0) {
          iVar12 = -iVar12;
        }
        if (iVar12 < 0xe8) {
          if (*(short *)((int)param_1 + 6) < 0) {
            iVar12 = -(param_1[1] >> 0x10);
          }
          else {
            iVar12 = param_1[1] >> 0x10;
          }
          if ((0x74 < iVar12) && (*(short *)((int)param_1 + 0x4e) < 0x1e)) {
            if (*(short *)((int)param_1 + 6) < 0) {
              iVar12 = -(param_1[1] >> 0x10);
            }
            else {
              iVar12 = param_1[1] >> 0x10;
            }
            iVar10 = iVar11;
            if (iVar11 < 0) {
              iVar10 = -iVar11;
            }
            if (iVar12 < iVar10) {
              bVar1 = false;
            }
          }
        }
      }
      if ((!bVar1) || ((ushort)psVar13[1] < 0x23)) {
        iVar12 = (int)*psVar13;
        if (bVar1) {
          iVar10 = iVar12;
          if (iVar12 < 0) {
            iVar10 = -iVar12;
          }
          if (0x18 < iVar10) {
            if ((*p_puck_carrier < '\0') && ((icing_state._2_1_ & 4) == 0)) {
              sVar4 = *p_puck_x;
              if (sVar4 < 0) {
                iVar11 = -(int)sVar4;
              }
              else {
                iVar11 = (int)sVar4;
              }
              if (0x43 < iVar11) {
                sVar4 = *(short *)p_puck_vy;
                if (sVar4 < 0) {
                  iVar11 = -(int)sVar4;
                }
                else {
                  iVar11 = (int)sVar4;
                }
                if (0x37ff < iVar11) {
                  uVar5 = *p_puck_y;
                  if ((short)uVar5 < 0) {
                    iVar11 = -(int)(short)uVar5;
                  }
                  else {
                    iVar11 = (int)(short)uVar5;
                  }
                  if (0x97 < iVar11) {
                    if ((*(byte *)(param_1 + 0x11) & 0x80) == 0) {
                      iVar11 = (int)*(short *)p_puck_vy;
                    }
                    else {
                      iVar11 = -(int)*(short *)p_puck_vy;
                    }
                    if (((-0x191 < iVar11) && (0x131 < *(int *)(param_1[0x1b] + 0x3e))) &&
                       (0x131 < *(int *)(param_1[0x1c] + 0x3e))) {
                      set_state_reset(param_1,0xf);
                      return;
                    }
                  }
                }
              }
            }
            goto LAB_0004c549;
          }
        }
        iVar12 = iVar12 - (*param_1 >> 0x10);
        if (iVar12 < 0) {
          iVar12 = -iVar12;
        }
        iVar12 = iVar12 + -8;
        if (0x10 < iVar12) {
          iVar12 = 0x10;
        }
        if (iVar12 < 0) {
          iVar12 = 0;
        }
        iVar12 = iVar12 >> 2;
        if (*(short *)((int)param_1 + 6) < 0) {
          iVar10 = -(param_1[1] >> 0x10);
        }
        else {
          iVar10 = param_1[1] >> 0x10;
        }
        if (iVar11 < 0) {
          iVar11 = -iVar11;
        }
        if (iVar10 < iVar11) {
          iVar12 = iVar12 + 4;
        }
        if (bVar1) {
          if (*(short *)((int)param_1 + 0x4e) < 0x1a) {
            uVar5 = *p_puck_y;
            if ((short)uVar5 < 0) {
              iVar11 = -(int)(short)uVar5;
            }
            else {
              iVar11 = (int)(short)uVar5;
            }
            if (iVar11 < 0xe9) goto LAB_0004c1ec;
          }
          if ((int)(uint)(ushort)psVar13[1] < iVar12 + 0xc) {
            uVar5 = *p_puck_y;
            if ((short)uVar5 < 0) {
              iVar11 = -(int)(short)uVar5;
            }
            else {
              iVar11 = (int)(short)uVar5;
            }
            if (iVar11 < 0xea) goto LAB_0004c1ec;
          }
          dword_e03ba = CONCAT22(*psVar13,(undefined2)dword_e03ba);
          uVar5 = *p_puck_y;
          if ((short)uVar5 < 0) {
            iVar11 = -(int)(short)uVar5;
          }
          else {
            iVar11 = (int)(short)uVar5;
          }
          if (0xdc < iVar11) {
            if (*p_puck_x < 1) {
              uVar6 = 0xffe8;
            }
            else {
              uVar6 = 0x18;
            }
            goto LAB_0004c543;
          }
        }
        else {
LAB_0004c1ec:
          if ((short)*p_puck_carrier != *(short *)((int)param_1 + 0x6a)) {
            sVar4 = *p_puck_x;
            if (sVar4 < 0) {
              iVar11 = -(int)sVar4;
            }
            else {
              iVar11 = (int)sVar4;
            }
            if ((iVar11 < 100) && (*p_puck_z < 0x14)) {
              *(short *)(param_1 + 3) = *(short *)(param_1 + 3) >> 1;
              *(short *)((int)param_1 + 0xe) = *(short *)((int)param_1 + 0xe) >> 1;
              if ((*(byte *)(param_1 + 0x12) & 2) == 0) {
                sVar4 = ((*(short *)p_puck_vx >> 10) + *p_puck_x) - (short)((uint)*param_1 >> 0x10);
                dword_e03ba = CONCAT22(sVar4,(undefined2)dword_e03ba);
                sVar7 = ((*(short *)p_puck_vy >> 10) + *p_puck_y) -
                        (short)((uint)param_1[1] >> 0x10);
                dword_e03be = CONCAT22(sVar7,(undefined2)dword_e03be);
                sVar4 = direction8((int)sVar4,(int)sVar7);
                if (sVar4 == 8) {
                  uVar5 = 0;
                }
                else {
                  uVar5 = sVar4 - *(short *)((int)param_1 + 0x36) & 7;
                }
              }
              else {
                uVar5 = (short)*(char *)((int)param_1 + 0x52) - *(short *)((int)param_1 + 0x36) & 7;
              }
              dword_e03ae = CONCAT22(uVar5,(undefined2)dword_e03ae);
              if (uVar5 == 4) {
                sVar4 = *(short *)p_puck_vy;
                if (sVar4 < 0) {
                  iVar11 = -(int)sVar4;
                }
                else {
                  iVar11 = (int)sVar4;
                }
                sVar4 = *(short *)p_puck_vx;
                if (sVar4 < 0) {
                  iVar12 = -(int)sVar4;
                }
                else {
                  iVar12 = (int)sVar4;
                }
                if (0x1200 < iVar12 + iVar11) goto LAB_0004c310;
                dword_e03ba = CONCAT22(8,(undefined2)dword_e03ba);
              }
              else {
LAB_0004c310:
                if ((uVar5 == 0) || (uVar5 == 4)) {
                  iVar11 = param_1[0xd] >> 0x10;
                  if (iVar11 == 0) {
                    bVar14 = false;
                    uVar9 = dword_e03ba;
LAB_0004c337:
                    if (bVar14 == (int)uVar9 < 0) {
LAB_0004c339:
                      uVar6 = 1;
                    }
                    else {
LAB_0004c352:
                      uVar6 = 7;
                    }
                  }
                  else {
                    if (iVar11 == 4) {
                      bVar14 = false;
                      uVar9 = dword_e03ba;
LAB_0004c350:
                      if (bVar14 == (int)uVar9 < 0) goto LAB_0004c352;
                      goto LAB_0004c339;
                    }
                    iVar12 = (int)dword_e03ba >> 0x10;
                    iVar10 = (int)dword_e03be >> 0x10;
                    if ((iVar11 == 1) || (iVar11 == 5)) {
                      if ((int)dword_e03ba < 0) {
                        iVar12 = -iVar12;
                      }
                      if ((int)dword_e03be < 0) {
                        iVar10 = -iVar10;
                      }
                      bVar14 = SBORROW4(iVar12,iVar10);
                      uVar9 = iVar12 - iVar10;
                      goto LAB_0004c337;
                    }
                    if ((iVar11 == 3) || (iVar11 == 7)) {
                      if ((int)dword_e03ba < 0) {
                        iVar12 = -iVar12;
                      }
                      if ((int)dword_e03be < 0) {
                        iVar10 = -iVar10;
                      }
                      bVar14 = SBORROW4(iVar12,iVar10);
                      uVar9 = iVar12 - iVar10;
                      goto LAB_0004c350;
                    }
                    uVar6 = randomrange(2);
                  }
                  dword_e03ae = CONCAT22(uVar6,(undefined2)dword_e03ae);
                }
                sVar4 = (short)((uint)dword_e03ae >> 0x10);
                dword_e03ba = CONCAT22(sVar4 >> 2,(undefined2)dword_e03ba);
                if ((*(byte *)((int)param_1 + 0x55) & 8) != 0) {
                  dword_e03ba = (uint)CONCAT12(sVar4 >> 2 == 0,(undefined2)dword_e03ba);
                }
                if (3 < sVar4) {
                  dword_e03ae = CONCAT22(7 - sVar4,(undefined2)dword_e03ae);
                }
                sVar4 = dword_e03ba._2_2_;
                if (((dword_e03ae._2_2_ < 2) || (9 < *p_puck_z)) || (0x7ff < *(short *)p_puck_vz)) {
                  if ((*p_puck_z < 8) && (*(short *)p_puck_vz < 0x800)) {
                    dword_e03ba._2_2_ = dword_e03ba._2_2_ + 4;
                    if (((8 < (ushort)psVar13[1]) &&
                        ((*(short *)((int)param_1 + 0x36) != 2 &&
                         (*(short *)((int)param_1 + 0x36) != 6)))) && (-1 < *p_puck_carrier)) {
                      dword_e03ba._2_2_ = sVar4 + 2;
                    }
                  }
                }
                else {
                  dword_e03ba._2_2_ = dword_e03ba._2_2_ + 6;
                }
              }
              *(byte *)(param_1 + 0x11) = *(byte *)(param_1 + 0x11) | 0x20;
              *(byte *)((int)param_1 + 0x45) = *(byte *)((int)param_1 + 0x45) | 2;
              set_animation(param_1,*(int *)((int)&dword_cca58 + ((int)dword_e03ba >> 0x10) * 2 + 2)
                                    >> 0x10);
              if ((crowd_noise._2_2_ < 0x4b1) &&
                 (crowd_noise._2_2_ = crowd_noise._2_2_ + 0x96, 0x4b0 < crowd_noise._2_2_)) {
                crowd_noise._2_2_ = 0x4b0;
              }
              dword_e03ba = CONCAT22(*psVar13,(undefined2)dword_e03ba);
              uVar5 = *p_puck_y;
              if ((short)uVar5 < 0) {
                iVar11 = -(int)(short)uVar5;
              }
              else {
                iVar11 = (int)(short)uVar5;
              }
              if (0xdc < iVar11) {
                if (*p_puck_x < 1) {
                  uVar6 = 0xffe8;
                }
                else {
                  uVar6 = 0x18;
                }
                goto LAB_0004c543;
              }
            }
          }
        }
      }
    }
    else {
      ram0x000e03aa = ram0x000e03aa & 0xffff;
      dword_e03ba = dword_e03ba & 0xffff;
      if (*(short *)((int)param_1 + 2) < 0) {
        iVar11 = -(*param_1 >> 0x10);
      }
      else {
        iVar11 = *param_1 >> 0x10;
      }
      if (iVar11 < 0x31) goto LAB_0004b84d;
    }
  }
  else {
    ram0x000e03aa = ram0x000e03aa & 0xffff;
    iVar11 = extraout_EDX;
    if (extraout_EDX < 0) {
      iVar11 = -extraout_EDX;
    }
    if (0x30 < iVar11) {
      dword_e03ba = CONCAT22((short)extraout_EDX,(undefined2)dword_e03ba);
      goto LAB_0004c549;
    }
LAB_0004b84d:
    if (*(short *)((int)param_1 + 2) < 0) {
      uVar6 = 0xff60;
    }
    else {
      uVar6 = 0xa0;
    }
LAB_0004c543:
    dword_e03ba = CONCAT22(uVar6,(undefined2)dword_e03ba);
  }
LAB_0004c549:
  uVar2 = dword_e03be;
  uVar9 = dword_e03ba;
  sVar4 = (short)(dword_e03ba >> 0x10) -
          ((short)(char)((uint)*(undefined4 *)((int)param_1 + 10) >> 0x18) +
          (short)((uint)*param_1 >> 0x10));
  dword_e03ba = CONCAT22(sVar4,(undefined2)dword_e03ba);
  sVar7 = dword_e03ac -
          ((short)((uint)param_1[1] >> 0x10) + (short)(char)((uint)param_1[3] >> 0x18));
  dword_e03be = CONCAT22(sVar7,(undefined2)dword_e03be);
  if (bVar1) {
    iVar11 = (int)sVar4;
    if (sVar4 < 0) {
      iVar11 = -iVar11;
    }
    if (iVar11 < 5) {
      iVar11 = (int)sVar7;
      if (sVar7 < 0) {
        iVar11 = -iVar11;
      }
      if (iVar11 < 5) {
        dword_e03be = uVar2 & 0xffff;
        dword_e03ba = uVar9 & 0xffff;
      }
    }
  }
  cVar3 = direction8((int)dword_e03ba >> 0x10,(int)dword_e03be >> 0x10);
  *(char *)(param_1 + 10) = cVar3;
  sVar4 = (short)cVar3;
  ram0x000e03aa = CONCAT22(sVar4,dword_e03a8._2_2_);
joined_r0x0004b97c:
  if (sVar4 < 8) {
    skating_accelerate(param_1,(int)unique0x1000042e >> 0x10);
  }
  else {
    brake(param_1);
  }
  return;
}


// ================================================================================================
// carrier_reset_target @ 0x4c632 [__watcall]
// ================================================================================================

void __watcall carrier_reset_target(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  short sVar3;
  short sVar4;
  
  __CHK(0x18);
  goalie_pass_mode = 0;
  if (*(short *)(param_1 + 0x6a) < 6) {
    iVar1 = 6;
  }
  else {
    iVar1 = 0;
  }
  puVar2 = &entities + iVar1 * 0x20;
  for (sVar4 = 0; sVar4 < 6; sVar4 = sVar4 + 1) {
    sVar3 = ((short)((uint)*puVar2 >> 0x10) +
            (short)(char)((uint)*(undefined4 *)((int)puVar2 + 10) >> 0x18)) -
            ((short)(char)((uint)*(undefined4 *)(param_1 + 10) >> 0x18) + *p_puck_x);
    if (sVar3 < 0) {
      iVar1 = -(int)sVar3;
    }
    else {
      iVar1 = (int)sVar3;
    }
    if (iVar1 < 0x15) {
      sVar3 = ((short)((uint)puVar2[1] >> 0x10) + (short)(char)((uint)puVar2[3] >> 0x18)) -
              (*p_puck_y + (short)(char)((uint)*(undefined4 *)(param_1 + 0xc) >> 0x18));
      if (sVar3 < 0) {
        iVar1 = -(int)sVar3;
      }
      else {
        iVar1 = (int)sVar3;
      }
      if (iVar1 < 0x15) {
        goalie_pass_mode = goalie_pass_mode + 1;
      }
    }
    puVar2 = puVar2 + 0x20;
  }
  return;
}


// ================================================================================================
// ai_puck_carrier @ 0x4c6f3 [__watcall]
// ================================================================================================

void __watcall ai_puck_carrier(int *param_1)

{
  byte bVar1;
  char cVar2;
  undefined2 uVar3;
  short sVar4;
  int iVar5;
  short sVar6;
  
  __CHK(0x14);
  if ((short)*p_puck_carrier == *(short *)((int)param_1 + 0x6a)) {
    bVar1 = *(byte *)(param_1 + 0x11);
    if ((bVar1 & 0x20) != 0) {
      return;
    }
    if ((game_flags & 1) != 0) {
      skate_idle(param_1);
      return;
    }
    if ((bVar1 & 8) == 0) {
      if ((bVar1 & 2) != 0) {
        *(byte *)(param_1 + 0x11) = bVar1 & 0xfd;
        *(undefined2 *)(param_1 + 0x13) = 0;
        *(undefined2 *)((int)param_1 + 0x26) = 0;
        *(undefined2 *)(param_1 + 10) = 8;
        uVar3 = randomrange(4);
        *(undefined2 *)((int)param_1 + 0x2a) = uVar3;
        goalie_pass_mode = 0;
      }
      cVar2 = *(char *)((int)param_1 + 0x27) + -1;
      *(char *)((int)param_1 + 0x27) = cVar2;
      if (cVar2 < '\0') {
        *(undefined *)((int)param_1 + 0x27) = *(undefined *)((int)param_1 + 0x59);
        pull_goalie_logic(param_1);
        if (breakaway_flag != 0) {
          if (*(short *)((int)param_1 + 6) < 0) {
            iVar5 = -(param_1[1] >> 0x10);
          }
          else {
            iVar5 = param_1[1] >> 0x10;
          }
          if (iVar5 < 0x70) {
            set_state(param_1,0x2e);
            return;
          }
        }
        sVar4 = ai_consider_shot(param_1);
        if (sVar4 != 0) {
          return;
        }
        sVar4 = ai_offense_decision(param_1);
        if (sVar4 != 0) {
          return;
        }
        sVar4 = ai_choose_pass_target(param_1);
        if (sVar4 != 0) {
          return;
        }
      }
      if (((byte)stop_flags & 0x80) == 0) {
        sVar4 = *(short *)((int)param_1 + 0x2a) + 6;
      }
      else {
        sVar4 = *(short *)((int)param_1 + 0x1a) + -1;
      }
      sVar6 = *(short *)(&carrier_targets + (short)(sVar4 * 2) * 2);
      dword_e03be._2_2_ = *(short *)(&unk_cca70 + (short)(sVar4 * 2) * 2);
      if ((*(byte *)(param_1 + 0x11) & 0x80) == 0) {
        sVar6 = -sVar6;
        dword_e03be._2_2_ = -*(short *)(&unk_cca70 + (short)(sVar4 * 2) * 2);
      }
      dword_e03ba = CONCAT22(sVar6,(undefined2)dword_e03ba);
      iVar5 = (*param_1 >> 0x10) - (int)sVar6;
      if (iVar5 < 0) {
        iVar5 = -iVar5;
      }
      if (iVar5 < 0xd) {
        iVar5 = (param_1[1] >> 0x10) - (int)dword_e03be._2_2_;
        if (iVar5 < 0) {
          iVar5 = -iVar5;
        }
        if (iVar5 < 0xd) {
          uVar3 = randomrange(4);
          *(undefined2 *)((int)param_1 + 0x2a) = uVar3;
        }
      }
      ai_skate_towards(param_1,carrier_scan_opponents);
      return;
    }
  }
  ai_default_skate(param_1);
  return;
}


// ================================================================================================
// carrier_near_net_check @ 0x4c8bd [__watcall]
// ================================================================================================

void __watcall carrier_near_net_check(int *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  __CHK(0x18);
  iVar5 = (*param_1 >> 0x10) + (*(int *)((int)param_1 + 10) >> 0x19);
  iVar4 = (param_1[1] >> 0x10) + (param_1[3] >> 0x19);
  if ((*(char *)((*(int *)((int)param_1 + 0x1a) >> 0x10) + 0x1e + (int)param_1) != '\x11') &&
     (((*(byte *)(param_1 + 0x11) & 0x80) != 0) == *(short *)((int)param_1 + 6) < 0)) {
    iVar1 = iVar4;
    if (iVar4 < 0) {
      iVar1 = -iVar4;
    }
    if (0xa9 < iVar1) {
      iVar1 = iVar4;
      if (iVar4 < 0) {
        iVar1 = -iVar4;
      }
      if (iVar1 < 0xe9) {
        iVar1 = iVar5;
        if (iVar5 < 0) {
          iVar1 = -iVar5;
        }
        if ((iVar1 < 0x51) && (iVar1 = *(int *)(param_1[0x1b] + 0xf8) >> 0x10, -1 < iVar1)) {
          iVar2 = dword_e03be >> 0x10;
          iVar3 = iVar2;
          if (dword_e03be < 0) {
            iVar3 = -iVar2;
          }
          if (iVar3 < 0x15) {
            if (dword_e03be < 0) {
              iVar2 = -iVar2;
            }
            if (iVar2 < 0x15) {
              dword_e03ba._2_2_ =
                   direction8((int)(short)((short)iVar5 -
                                          ((short)((uint)(&entities)[iVar1 * 0x20] >> 0x10) +
                                          (short)((int)*(undefined4 *)
                                                        ((int)&DAT_000df824 + iVar1 * 0x80 + 2) >>
                                                 0x19))),
                              (int)(short)((short)iVar4 -
                                          ((short)((uint)(&unk_df820)[iVar1 * 0x20] >> 0x10) +
                                          (short)((int)*(undefined4 *)(&DAT_000df828 + iVar1 * 0x40)
                                                 >> 0x19))));
            }
          }
        }
      }
    }
  }
  return;
}


// ================================================================================================
// carrier_scan_opponents @ 0x4c9fd [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall carrier_scan_opponents(int *param_1)

{
  short sVar1;
  int iVar2;
  int iVar3;
  short sVar4;
  undefined4 *puVar5;
  int iVar6;
  
  __CHK(0x14);
  dword_e03ba._2_2_ = (ushort)dword_e03ba._2_1_;
  goalie_pass_mode = 0;
  dword_e03b2 = CONCAT22(6,(undefined2)dword_e03b2);
  if (*(short *)((int)param_1 + 0x6a) < 6) {
    iVar2 = 6;
  }
  else {
    iVar2 = 0;
  }
  puVar5 = &entities + iVar2 * 0x20;
  dword_e03ac = *p_puck_x + (short)(char)((uint)*(undefined4 *)((int)param_1 + 10) >> 0x18);
  dword_e03ae._2_2_ = *p_puck_y + (short)(char)((uint)param_1[3] >> 0x18);
  do {
    sVar4 = ((short)((uint)*puVar5 >> 0x10) +
            (short)(char)((uint)*(undefined4 *)((int)puVar5 + 10) >> 0x18)) - dword_e03ac;
    dword_e03be = CONCAT22(sVar4,(undefined2)dword_e03be);
    iVar2 = (int)sVar4;
    if (sVar4 < 0) {
      iVar2 = -iVar2;
    }
    if (iVar2 < 0x1a) {
      sVar4 = ((short)(char)((uint)puVar5[3] >> 0x18) + (short)((uint)puVar5[1] >> 0x10)) -
              dword_e03ae._2_2_;
      dword_e03be = CONCAT22(sVar4,(undefined2)dword_e03be);
      iVar2 = (int)sVar4;
      if (sVar4 < 0) {
        iVar2 = -iVar2;
      }
      if (iVar2 < 0x1a) {
        goalie_pass_mode = goalie_pass_mode + 1;
        dword_e03ba._2_2_ =
             direction8((int)(short)(*(short *)((int)param_1 + 2) - *(short *)((int)puVar5 + 2)),
                        (int)(short)(*(short *)((int)param_1 + 6) - *(short *)((int)puVar5 + 6)));
        dword_e03be = CONCAT22(*(ushort *)((int)param_1 + 0x36),(undefined2)dword_e03be) ^ 0x40000;
        if (dword_e03ba._2_2_ == (*(ushort *)((int)param_1 + 0x36) ^ 4)) {
          sVar4 = randomrange(2);
          dword_e03ba._2_2_ = sVar4 + dword_e03ba._2_2_ & 7;
        }
      }
    }
    puVar5 = puVar5 + 0x20;
    sVar4 = dword_e03b2._2_2_ + -1;
    dword_e03b2 = CONCAT22(sVar4,(undefined2)dword_e03b2);
  } while (sVar4 != 0);
  if (((*(byte *)(param_1 + 0x11) & 0x80) != 0) == *(short *)((int)param_1 + 6) < 0) {
    if (dword_e03ae._2_2_ < 0) {
      iVar2 = -(int)dword_e03ae._2_2_;
    }
    else {
      iVar2 = (int)dword_e03ae._2_2_;
    }
    if (0xa9 < iVar2) {
      if (dword_e03ae._2_2_ < 0) {
        iVar2 = -(int)dword_e03ae._2_2_;
      }
      else {
        iVar2 = (int)dword_e03ae._2_2_;
      }
      if (iVar2 < 0xe9) {
        if (dword_e03ac < 0) {
          iVar2 = -(int)dword_e03ac;
        }
        else {
          iVar2 = (int)dword_e03ac;
        }
        if (iVar2 < 0x51) {
          sVar4 = *(short *)(param_1[0x1b] + 0xfa);
          dword_e03b2 = CONCAT22(sVar4,(undefined2)dword_e03b2);
          if (-1 < sVar4) {
            iVar6 = (int)sVar4;
            sVar4 = ((short)(char)((uint)*(undefined4 *)((int)&DAT_000df824 + iVar6 * 0x80 + 2) >>
                                  0x18) + (short)((uint)(&entities)[iVar6 * 0x20] >> 0x10)) -
                    dword_e03ac;
            dword_e03be = CONCAT22(sVar4,(undefined2)dword_e03be);
            iVar3 = (int)sVar4;
            iVar2 = iVar3;
            if (sVar4 < 0) {
              iVar2 = -iVar3;
            }
            if (iVar2 < 0x15) {
              sVar1 = ((short)((uint)(&unk_df820)[iVar6 * 0x20] >> 0x10) +
                      (short)(char)((uint)*(undefined4 *)(&DAT_000df828 + iVar6 * 0x40) >> 0x18)) -
                      dword_e03ae._2_2_;
              dword_e03b2 = CONCAT22(sVar1,(undefined2)dword_e03b2);
              if (sVar4 < 0) {
                iVar3 = -iVar3;
              }
              if (iVar3 < 0x15) {
                dword_e03ba._2_2_ = direction8((int)-sVar4,(int)-sVar1);
              }
            }
          }
          if (dword_e03ac < 0) {
            iVar2 = -(int)dword_e03ac;
          }
          else {
            iVar2 = (int)dword_e03ac;
          }
          if (iVar2 < 0x1f) {
            if ((*(byte *)(param_1 + 0x11) & 0x80) == 0) {
              sVar4 = 0xdc;
            }
            else {
              sVar4 = -0xdc;
            }
            sVar1 = sVar4 - dword_e03ae._2_2_;
            dword_e03be = CONCAT22(sVar1,(undefined2)dword_e03be);
            iVar2 = (int)sVar1;
            if (sVar1 < 0) {
              iVar2 = -iVar2;
            }
            if (iVar2 < 0x15) {
              dword_e03ba._2_2_ =
                   direction8(*param_1 >> 0x10,(int)(short)(*(short *)((int)param_1 + 6) - sVar4));
            }
          }
        }
      }
    }
  }
  return;
}


// ================================================================================================
// ai_nearest_to_puck @ 0x4cd4b [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall ai_nearest_to_puck(undefined4 *param_1)

{
  short sVar1;
  ushort uVar2;
  int iVar3;
  int iVar4;
  char cVar7;
  undefined4 *extraout_EDX;
  undefined4 *puVar5;
  int iVar6;
  uint uVar8;
  undefined4 *puVar9;
  short sStackY_1c;
  
  __CHK(0x28);
  iVar4 = param_1[0x1b];
  if ((*(byte *)(param_1 + 0x11) & 2) != 0) {
    *(byte *)(param_1 + 0x11) = *(byte *)(param_1 + 0x11) & 0xfd;
    *(undefined2 *)((int)param_1 + 0x26) = 0;
    *(undefined2 *)(param_1 + 10) = 8;
    *(undefined2 *)((int)param_1 + 0x2a) = 0;
  }
  uVar8 = CONCAT22((undefined2)dword_e03be,dword_e03ba._2_2_);
  if ((short)*p_puck_carrier == *(short *)((int)param_1 + 0x6a)) {
    if (*(short *)((int)param_1 + 0x1a) == 0) {
      ai_goalie(param_1);
      uVar8 = CONCAT22((undefined2)dword_e03be,dword_e03ba._2_2_);
      iVar6 = CONCAT22(uRam000e03c2,dword_e03be._2_2_);
    }
    else {
      iVar6 = CONCAT22(uRam000e03c2,dword_e03be._2_2_);
      if ((*(byte *)(param_1 + 0x11) & 8) == 0) {
        set_state_reset(param_1,0x10);
        uVar8 = CONCAT22((undefined2)dword_e03be,dword_e03ba._2_2_);
        iVar6 = CONCAT22(uRam000e03c2,dword_e03be._2_2_);
      }
    }
    goto LAB_0004c62c;
  }
  cVar7 = *(char *)((int)param_1 + 0x27) + -1;
  *(char *)((int)param_1 + 0x27) = cVar7;
  uVar8 = CONCAT22((undefined2)dword_e03be,dword_e03ba._2_2_);
  if (-1 < cVar7) goto LAB_0004d1ab;
  *(undefined *)((int)param_1 + 0x27) = *(undefined *)((int)param_1 + 0x59);
  *(undefined4 *)(iVar4 + 0x3a) = 0;
  iVar6 = CONCAT22(uRam000e03c2,dword_e03be._2_2_);
  uVar8 = CONCAT22((undefined2)dword_e03be,dword_e03ba._2_2_);
  if ((*p_puck_carrier < '\0') || (*p_puck_carrier < '\x06' != *(short *)((int)param_1 + 0x6a) < 6))
  {
    sStackY_1c = *(short *)((int)param_1 + 0x6a);
    sVar1 = *(short *)((int)param_1 + 6);
    _dword_e03ac = 0xffffffff;
    dword_e03b2._2_2_ = 6;
    if (*(short *)((int)param_1 + 0x6a) < 6) {
      iVar3 = 0;
    }
    else {
      iVar3 = 6;
    }
    puVar5 = &entities + iVar3 * 0x20;
    puVar9 = param_1;
    if ((int)param_1[0x1a] >> 0x10 != penalty_shot_slot) {
      do {
        uRam000e03c2 = (undefined2)((uint)iVar6 >> 0x10);
        dword_e03be._2_2_ = (short)iVar6;
        dword_e03be._0_2_ = (undefined2)(uVar8 >> 0x10);
        dword_e03ba._2_2_ = (short)uVar8;
        if ((((0 < *(short *)((int)puVar5 + 0x1a)) && (*(short *)((int)puVar5 + 0x3e) == 0)) &&
            ((*(byte *)((int)puVar5 + 0x45) & 4) == 0)) &&
           (*(char *)((int)puVar5 + (*(int *)((int)puVar5 + 0x1a) >> 0x10) + 0x1e) != '\x13')) {
          if (*(short *)((int)puVar5 + 6) < 0) {
            iVar6 = -((int)puVar5[1] >> 0x10);
          }
          else {
            iVar6 = (int)puVar5[1] >> 0x10;
          }
          if ((iVar6 < 0xe8) &&
             ((((*(byte *)(param_1 + 0x11) & 0x80) != 0 && (*(short *)((int)puVar5 + 6) <= sVar1))
              || (((*(byte *)(param_1 + 0x11) & 0x80) == 0 && (sVar1 <= *(short *)((int)puVar5 + 6))
                  ))))) {
            sStackY_1c = *(short *)((int)puVar5 + 0x6a);
            sVar1 = *(short *)((int)puVar5 + 6);
          }
          frame_offsets_lookup(puVar5);
          iVar3 = (int)(short)((((short)((uint)*extraout_EDX >> 0x10) + dword_e03ba._2_2_) -
                               *p_puck_x) - (*(short *)p_puck_vx >> 6));
          iVar6 = (int)(short)(((dword_e03be._2_2_ + (short)((uint)extraout_EDX[1] >> 0x10)) -
                               *p_puck_y) - (*(short *)p_puck_vy >> 6));
          iVar6 = iVar6 * iVar6;
          uVar8 = iVar3 * iVar3 + iVar6;
          puVar5 = extraout_EDX;
          if (uVar8 <= _dword_e03ac) {
            puVar9 = extraout_EDX;
            _dword_e03ac = uVar8;
          }
        }
        puVar5 = puVar5 + 0x20;
        dword_e03b2._2_2_ = dword_e03b2._2_2_ + -1;
      } while (dword_e03b2._2_2_ != 0);
    }
    uRam000e03c2 = (undefined2)((uint)iVar6 >> 0x10);
    dword_e03be._2_2_ = (short)iVar6;
    dword_e03be._0_2_ = (undefined2)(uVar8 >> 0x10);
    dword_e03ba._2_2_ = (short)uVar8;
    if (-1 < (int)_dword_e03ac) {
      *(uint *)(iVar4 + 0x3a) = _dword_e03ac;
      goto LAB_0004cfbf;
    }
  }
  else {
    puVar9 = &entities + *p_puck_carrier * 0x20;
LAB_0004cfbf:
    uVar8 = CONCAT22((undefined2)dword_e03be,dword_e03ba._2_2_);
    iVar6 = CONCAT22(uRam000e03c2,dword_e03be._2_2_);
    if (((puVar9 != param_1) &&
        (uVar8 = CONCAT22((undefined2)dword_e03be,dword_e03ba._2_2_),
        iVar6 = CONCAT22(uRam000e03c2,dword_e03be._2_2_), (game_flags & 1) == 0)) &&
       ((uVar8 = CONCAT22((undefined2)dword_e03be,dword_e03ba._2_2_),
        iVar6 = CONCAT22(uRam000e03c2,dword_e03be._2_2_), 0 < *(short *)((int)puVar9 + 0x1a) &&
        (uVar8 = CONCAT22((undefined2)dword_e03be,dword_e03ba._2_2_),
        iVar6 = CONCAT22(uRam000e03c2,dword_e03be._2_2_), (*(byte *)((int)puVar9 + 0x45) & 4) == 0))
       )) {
      *(byte *)(puVar9 + 0x11) = *(byte *)(puVar9 + 0x11) & 0xfe;
      set_state_reset(puVar9,0x11);
      ai_default_skate(param_1);
      uVar8 = CONCAT22((undefined2)dword_e03be,dword_e03ba._2_2_);
      iVar6 = CONCAT22(uRam000e03c2,dword_e03be._2_2_);
      goto LAB_0004c62c;
    }
  }
  dword_e03be._0_2_ = (undefined2)(uVar8 >> 0x10);
  dword_e03ba._2_2_ = (short)uVar8;
  if ((*(byte *)(param_1 + 0x11) & 0x20) != 0) goto LAB_0004c62c;
  dword_e03be._2_2_ = 2;
  uRam000e03c2 = 0;
  if (dword_e03ac < 0x191) {
LAB_0004d089:
    dword_e03be._2_2_ = 0;
    if (2 < *(short *)((int)param_1 + 0x1a)) goto LAB_0004d0db;
    if (*(short *)((int)param_1 + 0x6a) != sStackY_1c) {
      sVar1 = randomrange((int)(short)((int)(((0x32 - (uint)*(byte *)((int)param_1 + 0x62)) -
                                             (uint)*(byte *)(param_1 + 0x19)) -
                                            (uint)*(byte *)((int)param_1 + 0x5a)) / 2));
      uVar8 = CONCAT22((undefined2)dword_e03be,dword_e03ba._2_2_);
      if (sVar1 == 0) goto LAB_0004d0db;
    }
  }
  else {
    if (dword_e03ac < 0xe11) {
      sVar1 = *(short *)p_puck_vx;
      if (sVar1 < 0) {
        iVar4 = -(int)sVar1;
      }
      else {
        iVar4 = (int)sVar1;
      }
      if (iVar4 < 500) {
        sVar1 = *(short *)p_puck_vy;
        if (sVar1 < 0) {
          iVar4 = -(int)sVar1;
        }
        else {
          iVar4 = (int)sVar1;
        }
        if (iVar4 < 500) goto LAB_0004d089;
      }
    }
    if ((2 < *(short *)((int)param_1 + 0x1a)) &&
       ((((*(byte *)(param_1 + 0x11) & 0x80) != 0 && (0x4e < *(short *)((int)param_1 + 0x1a))) ||
        (((*(byte *)(param_1 + 0x11) & 0x80) == 0 && ((int)param_1[6] >> 0x10 < -0x4e))))))
    goto LAB_0004d089;
LAB_0004d0db:
    sVar1 = *(short *)p_puck_vx;
    if (sVar1 < 0) {
      iVar4 = -(int)sVar1;
    }
    else {
      iVar4 = (int)sVar1;
    }
    if (iVar4 < 500) {
      sVar1 = *(short *)p_puck_vy;
      if (sVar1 < 0) {
        iVar4 = -(int)sVar1;
      }
      else {
        iVar4 = (int)sVar1;
      }
      if (iVar4 < 500) {
        dword_e03be._2_2_ = dword_e03be._2_2_ + -1;
      }
    }
    iVar4 = CONCAT22(uRam000e03c2,dword_e03be._2_2_);
    if ((stop_flags & 0x20) != 0) {
      dword_e03be._2_2_ = dword_e03be._2_2_ + -2;
      iVar4 = CONCAT22(uRam000e03c2,dword_e03be._2_2_);
      if ((stop_flags & 0x40) != (ushort)(*(byte *)(param_1 + 0x11) & 0x40)) {
        iVar4 = CONCAT22(uRam000e03c2,dword_e03be._2_2_) + 4;
      }
    }
    uRam000e03c2 = (undefined2)((uint)iVar4 >> 0x10);
    dword_e03be._2_2_ = (short)iVar4;
    if (dword_e03be._2_2_ < 0) {
      dword_e03ba._2_2_ =
           (short)((int)(0x14 - (uint)*(byte *)(param_1 + 0x19)) >> (-(byte)iVar4 & 0x1f));
    }
    else {
      dword_e03ba._2_2_ = (short)(0x14 - (uint)*(byte *)(param_1 + 0x19) << ((byte)iVar4 & 0x1f));
    }
    uVar2 = randomrange((int)dword_e03ba._2_2_);
    uVar8 = CONCAT22((undefined2)dword_e03be,dword_e03ba._2_2_);
    if (uVar2 < 2) {
      *(undefined2 *)((int)param_1 + 0x2a) = 300;
      uVar8 = CONCAT22((undefined2)dword_e03be,dword_e03ba._2_2_);
    }
  }
LAB_0004d1ab:
  dword_e03be._0_2_ = (undefined2)(uVar8 >> 0x10);
  dword_e03ba._2_2_ = (short)uVar8;
  iVar6 = CONCAT22(uRam000e03c2,dword_e03be._2_2_);
  if ((*(byte *)(param_1 + 0x11) & 0x20) != 0) goto LAB_0004c62c;
  if ((game_flags & 1) != 0) {
    sVar1 = handle_line_change(param_1);
    uVar8 = CONCAT22((undefined2)dword_e03be,dword_e03ba._2_2_);
    iVar6 = CONCAT22(uRam000e03c2,dword_e03be._2_2_);
    if (sVar1 == 0) {
      skate_idle(param_1);
      uVar8 = CONCAT22((undefined2)dword_e03be,dword_e03ba._2_2_);
      iVar6 = CONCAT22(uRam000e03c2,dword_e03be._2_2_);
    }
    goto LAB_0004c62c;
  }
  iVar6 = CONCAT22(uRam000e03c2,dword_e03be._2_2_);
  if ((*(byte *)(param_1 + 0x11) & 8) != 0) goto LAB_0004c62c;
  if (*p_puck_carrier < '\0') {
LAB_0004d1fd:
    dword_e03be._0_2_ = (undefined2)(uVar8 >> 0x10);
    dword_e03ba._2_2_ = (short)uVar8;
    ai_chase_puck(param_1);
  }
  else {
    sVar1 = *(short *)((int)param_1 + 0x2a) + -1;
    *(short *)((int)param_1 + 0x2a) = sVar1;
    uVar8 = CONCAT22((undefined2)dword_e03be,dword_e03ba._2_2_);
    if (-1 < sVar1) goto LAB_0004d1fd;
    *(undefined2 *)((int)param_1 + 0x2a) = 0;
    sVar1 = *p_puck_y + (short)((int)(char)p_puck_vy[1] >> 1);
    iVar4 = (short)(*p_puck_x + (short)((int)(char)p_puck_vx[1] >> 1)) * 3;
    iVar6 = iVar4 >> 0x1f;
    dword_e03ba._2_2_ = (short)((int)((iVar4 + iVar6 * -4) - (uint)(iVar6 << 1 < 0)) >> 2);
    if ((*(byte *)(param_1 + 0x11) & 0x80) == 0) {
      iVar4 = 0xd4;
    }
    else {
      iVar4 = -0xd4;
    }
    dword_e03be._2_2_ = (short)(iVar4 - sVar1 >> 1) + sVar1;
    sVar1 = *p_puck_y;
    if (sVar1 < 0) {
      iVar4 = -(int)sVar1;
    }
    else {
      iVar4 = (int)sVar1;
    }
    if (dword_e03be._2_2_ < 0) {
      iVar6 = -(int)dword_e03be._2_2_;
    }
    else {
      iVar6 = (int)dword_e03be._2_2_;
    }
    if (iVar4 < iVar6) {
      sVar1 = *p_puck_x;
      if (sVar1 < 0) {
        iVar4 = -(int)sVar1;
      }
      else {
        iVar4 = (int)sVar1;
      }
      if (iVar4 < 0x41) {
        iVar4 = (int)dword_e03be._2_2_ - (int)*p_puck_y;
        if (iVar4 < 0) {
          iVar4 = -iVar4;
        }
        if (0x14 < iVar4) {
          if (dword_e03ba._2_2_ < 0) {
            iVar4 = -(int)dword_e03ba._2_2_;
          }
          else {
            iVar4 = (int)dword_e03ba._2_2_;
          }
          if (iVar4 < 0x14) {
            if (dword_e03be._2_2_ < 0) {
              iVar4 = -(int)dword_e03be._2_2_;
            }
            else {
              iVar4 = (int)dword_e03be._2_2_;
            }
            if (200 < iVar4) {
              if (dword_e03be._2_2_ < 0) {
                dword_e03be._2_2_ = -200;
              }
              else {
                dword_e03be._2_2_ = 200;
              }
            }
          }
          else {
            if (dword_e03ba._2_2_ < 0) {
              iVar4 = -(int)dword_e03ba._2_2_;
            }
            else {
              iVar4 = (int)dword_e03ba._2_2_;
            }
            if (iVar4 < 0x28) {
              if (dword_e03be._2_2_ < 0) {
                iVar4 = -(int)dword_e03be._2_2_;
              }
              else {
                iVar4 = (int)dword_e03be._2_2_;
              }
              if (0xd2 < iVar4) {
                if (dword_e03be._2_2_ < 0) {
                  dword_e03be._2_2_ = -0xd2;
                }
                else {
                  dword_e03be._2_2_ = 0xd2;
                }
              }
            }
          }
        }
      }
    }
    ai_skate_towards(param_1,0);
  }
  ai_try_check(param_1);
  iVar6 = CONCAT22(uRam000e03c2,dword_e03be._2_2_);
  uVar8 = CONCAT22((undefined2)dword_e03be,dword_e03ba._2_2_);
LAB_0004c62c:
  uRam000e03c2 = (undefined2)((uint)iVar6 >> 0x10);
  dword_e03be._2_2_ = (short)iVar6;
  dword_e03be._0_2_ = (undefined2)(uVar8 >> 0x10);
  dword_e03ba._2_2_ = (short)uVar8;
  return;
}


// ================================================================================================
// ai_shoot @ 0x4d3f8 [__watcall]
// ================================================================================================

void __watcall ai_shoot(int param_1)

{
  int iVar1;
  int extraout_EDX;
  short sVar2;
  
  __CHK(0x14);
  if ((*(byte *)(param_1 + 0x44) & 0x20) != 0) {
    return;
  }
  if ((*(byte *)(param_1 + 0x44) & 2) != 0) {
    *(byte *)(param_1 + 0x44) = *(byte *)(param_1 + 0x44) & 0xfd;
    start_shot(param_1);
    return;
  }
  if ((action_flags & 8) == 0) {
    ai_default_skate(param_1);
    return;
  }
  dword_e03ac = 0;
  sVar2 = *(short *)(param_1 + 0x28) + -1;
  *(short *)(param_1 + 0x28) = sVar2;
  if (sVar2 < 0) {
    dword_e03ac = dword_e03ac | 0x20;
  }
  sVar2 = *(short *)(param_1 + 0x4c) + -1;
  *(short *)(param_1 + 0x4c) = sVar2;
  if (sVar2 < 0) {
    *(undefined2 *)(param_1 + 0x4c) = 0;
  }
  if (*(short *)(param_1 + 6) < 0) {
    iVar1 = -(*(int *)(param_1 + 4) >> 0x10);
  }
  else {
    iVar1 = *(int *)(param_1 + 4) >> 0x10;
  }
  if (iVar1 < 0x9e) {
    if (*(short *)(param_1 + 6) < 0) {
      iVar1 = -(*(int *)(param_1 + 4) >> 0x10);
    }
    else {
      iVar1 = *(int *)(param_1 + 4) >> 0x10;
    }
    if ((((0x53 < iVar1) && (*(int *)(*(int *)(param_1 + 0x70) + 0x3e) < 0x24)) &&
        (*(short *)(param_1 + 0x4c) == 0)) &&
       (sVar2 = randomrange(0x14), param_1 = extraout_EDX, sVar2 == 0)) {
      *(undefined2 *)(extraout_EDX + 0x4c) = 300;
      dword_e03be._2_1_ = dword_e03be._2_1_ | 0x10;
      goto LAB_0004d4e4;
    }
  }
  dword_e03be._2_1_ = dword_e03be._2_1_ & 0xaf;
LAB_0004d4e4:
  shot_control(param_1);
  return;
}


// ================================================================================================
// ai_faceoff_wait @ 0x4d4f0 [__watcall]
// ================================================================================================

void __watcall ai_faceoff_wait(int param_1)

{
  __CHK(4);
  if (((*(byte *)(param_1 + 0x44) & 0x20) == 0) && (((byte)stop_flags & 1) == 0)) {
    __CHK(8);
    *(ushort *)(param_1 + 0x1c) = (ushort)((char)*(undefined2 *)(param_1 + 0x1c) + 1U & 7);
    *(byte *)(param_1 + 0x44) = *(byte *)(param_1 + 0x44) | 2;
    return;
  }
  return;
}


// ================================================================================================
// ai_default_skate @ 0x4d509 [__watcall]
// ================================================================================================

void __watcall ai_default_skate(int param_1)

{
  __CHK(8);
  *(ushort *)(param_1 + 0x1c) = (ushort)((char)*(undefined2 *)(param_1 + 0x1c) + 1U & 7);
  *(byte *)(param_1 + 0x44) = *(byte *)(param_1 + 0x44) | 2;
  return;
}


// ================================================================================================
// ai_faceoff @ 0x4d528 [__watcall]
// ================================================================================================

void __watcall
ai_faceoff(int param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  undefined2 uVar1;
  short sVar2;
  short sVar3;
  uint uVar4;
  short *psVar5;
  short *extraout_EDX;
  
  __CHK(0x10);
  if ((*(byte *)(param_1 + 0x44) & 0x20) != 0) {
    return;
  }
  if (((byte)stop_flags & 1) != 0) {
    if ((*(byte *)(param_1 + 0x44) & 2) != 0) {
      uVar4 = CONCAT31((int3)((uint)unaff_ECX >> 8),*(byte *)(param_1 + 0x44)) & 0xfffffffd;
      *(char *)(param_1 + 0x44) = (char)uVar4;
      *(undefined2 *)(param_1 + 0x26) = 0;
      if (*(short *)(param_1 + 0x36) == 0) {
        uVar1 = 0x16c;
      }
      else {
        uVar1 = 0x167;
      }
      *(undefined2 *)(param_1 + 0x12) = uVar1;
      set_animation(param_1,0,param_1,uVar4,unaff_EDX,unaff_ECX,unaff_EBX);
      if ((*(byte *)(param_1 + 0x44) & 0x40) == 0) {
        *(undefined2 *)(param_1 + 0x2e) = 0x28;
      }
      else {
        sVar2 = randomrange(10);
        *(short *)(param_1 + 0x2e) = sVar2 + 0x14;
      }
    }
    psVar5 = (short *)((int)&faceoff_ready_home + 2);
    if ((*(byte *)(param_1 + 0x44) & 0x40) != 0) {
      psVar5 = &faceoff_ready_away;
    }
    sVar2 = *(short *)(param_1 + 0x12);
    if ((sVar2 == 0x169) || (sVar2 == 0x16e)) {
      dword_e03ba._2_2_ = 2;
    }
    else if ((sVar2 == 0x16a) || (sVar2 == 0x16f)) {
      if (*(short *)(param_1 + 0x3c) == 7) {
        play_sfx(((*(byte *)(param_1 + 0x44) & 0x40) != 0) + 0x9e);
        psVar5 = extraout_EDX;
      }
      dword_e03ba._2_2_ = 3;
    }
    else {
      dword_e03ba._2_2_ = 1;
    }
    if (*(char *)(param_1 + 0x65) == '\0') {
      dword_e03ba._2_2_ = dword_e03ba._2_2_ + 3;
    }
    *psVar5 = dword_e03ba._2_2_;
    if ((*(byte *)(param_1 + 0x44) & 8) == 0) {
      if ((*(byte *)(param_1 + 0x45) & 2) != 0) {
        return;
      }
      *(byte *)(param_1 + 0x45) = *(byte *)(param_1 + 0x45) | 2;
      if ((*(short *)(param_1 + 0x2e) < 0) &&
         ((faceoff_timer < 0x11 || (sVar3 = randomrange(8), sVar3 == 0)))) {
        *(undefined2 *)(param_1 + 0x2e) = 0xffff;
        if ((short)faceoff_timer < 0x11) {
          *(byte *)(param_1 + 0x44) = *(byte *)(param_1 + 0x44) | 0x20;
          uVar1 = 0x7dd;
        }
        else {
          uVar1 = 0xd05;
        }
      }
      else {
        sVar3 = *(short *)(param_1 + 0x2e) + -1;
        *(short *)(param_1 + 0x2e) = sVar3;
        if (-1 < sVar3) {
          return;
        }
        uVar1 = 0x7f1;
      }
      set_animation(param_1,uVar1,param_1,sVar2,unaff_EDX,unaff_ECX,unaff_EBX);
      return;
    }
    return;
  }
  *(undefined2 *)(param_1 + 0x3e) = 0x14;
  ai_default_skate(param_1);
  return;
}


// ================================================================================================
// puck_update @ 0x4d6b4 [__watcall]
// ================================================================================================

void __watcall puck_update(int *param_1)

{
  short sVar1;
  uint uVar2;
  int iVar3;
  undefined4 extraout_EDX;
  int *extraout_EDX_00;
  short sVar4;
  
  __CHK(0x18);
  word_df816 = word_df816 + -1;
  word_df81a = word_df81a + -1;
  sVar1 = *(short *)((int)param_1 + 0x26);
  sVar4 = sVar1 + -1;
  *(short *)((int)param_1 + 0x26) = sVar4;
  if (sVar4 < 0) {
    *(short *)((int)param_1 + 0x26) = sVar1 + 4;
    predict_puck_goal_line(param_1);
  }
  if (-1 < *p_puck_carrier) {
    update_carrier(&entities + *p_puck_carrier * 0x20);
    frame_offsets_lookup(extraout_EDX);
    *(short *)((int)param_1 + 2) =
         (short)((uint)*param_1 >> 0x10) +
         (short)(((dword_e03ba >> 0x10) + (*extraout_EDX_00 >> 0x10)) - (*param_1 >> 0x10) >> 2);
    *(short *)((int)param_1 + 6) =
         (short)((param_1[1] >> 0x10) +
                (((dword_e03be >> 0x10) + (extraout_EDX_00[1] >> 0x10)) - (param_1[1] >> 0x10) >> 2)
                );
    *(undefined2 *)(param_1 + 3) = *(undefined2 *)(extraout_EDX_00 + 3);
    *(undefined2 *)((int)param_1 + 0xe) = *(undefined2 *)((int)extraout_EDX_00 + 0xe);
  }
  check_icing();
  check_offside(param_1);
  update_offside_flags(param_1);
  if ((game_flags & 1) != 0) goto LAB_0004d88f;
  if (*p_puck_carrier < '\0') {
    uVar2 = (game_flags & 2) == 0 ^ penalty_shot_team;
    if ((penalty_shot_active == 0) ||
       (((uVar2 != 0 || (*(short *)p_puck_vy < 0)) && ((uVar2 == 0 || (0 < *(short *)p_puck_vy))))))
    {
      penalty_shot_timer = 0;
    }
    else {
      penalty_shot_timer = penalty_shot_timer + 1;
      if (0x1d < penalty_shot_timer) {
        end_penalty_shot();
        penalty_shot_timer = 0;
      }
    }
    if ((*(short *)((int)param_1 + 2) == *(short *)((int)param_1 + 0x76)) &&
       (*(short *)((int)param_1 + 6) == *(short *)((int)param_1 + 0x7a))) {
      sVar1 = *p_puck_x;
      if (sVar1 < 0) {
        iVar3 = -(int)sVar1;
      }
      else {
        iVar3 = (int)sVar1;
      }
      if (iVar3 < 0xa3) {
        sVar1 = *p_puck_y;
        if (sVar1 < 0) {
          iVar3 = -(int)sVar1;
        }
        else {
          iVar3 = (int)sVar1;
        }
        if (((iVar3 < 0x10e) && (0x14 < dword_df652)) && (0x14 < dword_df752)) goto LAB_0004d7a0;
      }
      sVar1 = *(short *)(param_1 + 10);
      *(short *)(param_1 + 10) = sVar1 + -1;
      if ((short)(sVar1 + -1) < 0) {
        queue_infraction(param_1,3);
      }
      goto LAB_0004d88f;
    }
  }
  else {
    penalty_shot_timer = 0;
  }
LAB_0004d7a0:
  *(undefined2 *)(param_1 + 10) = 0x78;
LAB_0004d88f:
  if (*(short *)(param_1 + 4) < 0) {
    iVar3 = -(*(int *)((int)param_1 + 0xe) >> 0x10);
  }
  else {
    iVar3 = *(int *)((int)param_1 + 0xe) >> 0x10;
  }
  if ((iVar3 < 0x100) && (*(short *)((int)param_1 + 10) == 0)) {
    puck_flat(param_1);
  }
  puck_check_players(param_1);
  return;
}


// ================================================================================================
// ai_puck_normal @ 0x4d8c7 [__watcall]
// ================================================================================================

void __watcall ai_puck_normal(int param_1)

{
  __CHK(8);
  if ((*(byte *)(param_1 + 0x44) & 2) != 0) {
    *(byte *)(param_1 + 0x44) = *(byte *)(param_1 + 0x44) & 0xfd;
    *(undefined2 *)(param_1 + 0x26) = 0;
    *(undefined2 *)(param_1 + 0x28) = 0x78;
    penalty_shot_timer = 0;
  }
  puck_update();
  return;
}


// ================================================================================================
// ai_puck_idle @ 0x4d8fd [__watcall]
// ================================================================================================

void __watcall ai_puck_idle(int param_1)

{
  __CHK(4);
  __CHK(8);
  if ((3 < *(short *)(param_1 + 0x3a)) && (*(short *)(param_1 + 0x3a) < 0xc)) {
    *(byte *)(param_1 + 0x36) = *(byte *)(param_1 + 0x36) ^ 2;
  }
  *(byte *)(param_1 + 0x36) = *(byte *)(param_1 + 0x36) | 4;
  *(undefined2 *)(param_1 + 0x3a) = 0;
  *(undefined2 *)(param_1 + 0x3c) = 0xffff;
  return;
}


// ================================================================================================
// puck_flat @ 0x4d907 [__watcall]
// ================================================================================================

void __watcall puck_flat(int param_1)

{
  __CHK(8);
  if ((3 < *(short *)(param_1 + 0x3a)) && (*(short *)(param_1 + 0x3a) < 0xc)) {
    *(byte *)(param_1 + 0x36) = *(byte *)(param_1 + 0x36) ^ 2;
  }
  *(byte *)(param_1 + 0x36) = *(byte *)(param_1 + 0x36) | 4;
  *(undefined2 *)(param_1 + 0x3a) = 0;
  *(undefined2 *)(param_1 + 0x3c) = 0xffff;
  return;
}


// ================================================================================================
// start_line_change_ui @ 0x4d938 [__watcall]
// ================================================================================================

void __watcall start_line_change_ui(int param_1)

{
  short sVar1;
  int iVar2;
  ushort uVar3;
  short extraout_DX;
  
  __CHK(0x18);
  uVar3 = (ushort)((*(byte *)(param_1 + 0x44) & 0x40) != 0);
  dword_e03ba._2_2_ = 1;
  pick_next_line();
  sVar1 = dword_e03ba._2_2_;
  if (dword_e03ba._2_2_ < 0) {
    (&word_cbc5e)[extraout_DX] = 0;
    if (extraout_DX < 1) {
      iVar2 = 0xdf614;
    }
    else {
      iVar2 = 0xdf714;
    }
    (&word_cbc62)[(short)uVar3] = *(undefined2 *)(iVar2 + 0x2a);
  }
  else {
    (&word_cbc5e)[extraout_DX] = 1;
    (&word_cbc62)[extraout_DX] = sVar1;
  }
  (&word_cbc66)[(short)uVar3] = 0x3c;
  (&word_cbc56)[(short)uVar3] = 1;
  (&word_cbc5a)[(short)uVar3] = 0xc;
  (&word_cbc6a)[(short)uVar3] = 1;
  if (uVar3 == 0) {
    dword_c585c = 0;
  }
  else {
    dword_c5860 = 0;
  }
  return;
}


// ================================================================================================
// request_line_change_button @ 0x4d9fc [__watcall]
// ================================================================================================

void __watcall request_line_change_button(int param_1)

{
  byte bVar1;
  
  __CHK(0xc);
  if (((byte)option_flags & 4) != 0) {
    bVar1 = *(byte *)(*(int *)(param_1 + 0x6c) + 0x44);
    if ((bVar1 & 2) == 0) {
      *(byte *)(*(int *)(param_1 + 0x6c) + 0x44) = bVar1 | 2;
      action_flags = action_flags & 0xf3;
      *(byte *)(param_1 + 0x45) = *(byte *)(param_1 + 0x45) | 8;
      start_line_change_ui();
    }
  }
  return;
}


// ================================================================================================
// user_line_change_prompt @ 0x4da37 [__watcall]
// ================================================================================================

void __watcall user_line_change_prompt(int param_1,int unaff_EDX)

{
  int extraout_EDX;
  
  __CHK(8);
  *(byte *)(unaff_EDX + 0x45) = *(byte *)(unaff_EDX + 0x45) & 0xf7;
  request_line_change_button(unaff_EDX);
  if ((*(byte *)(extraout_EDX + 0x45) & 8) != 0) {
    if ((*(byte *)(extraout_EDX + 0x44) & 0x40) != 0) {
      *(undefined2 *)(param_1 + 0x28) = 0x168;
      *(undefined2 *)(param_1 + 0x2c) = *(undefined2 *)(extraout_EDX + 0x6a);
      return;
    }
    *(undefined2 *)(param_1 + 0x26) = 600;
    *(undefined2 *)(param_1 + 0x2a) = *(undefined2 *)(extraout_EDX + 0x6a);
  }
  return;
}


// ================================================================================================
// faceoff_resolve @ 0x4da7b [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall faceoff_resolve(int param_1)

{
  uint3 uVar1;
  char cVar2;
  short sVar3;
  ushort uVar4;
  undefined2 uVar5;
  short extraout_DX;
  short sVar6;
  
  __CHK(0x18);
  stop_crowd_loop();
  play_sfx(0xab);
  stop_flags._0_1_ = (byte)stop_flags & 0xfa;
  game_flags = game_flags & 0xfe;
  *(byte *)(param_1 + 0x45) = *(byte *)(param_1 + 0x45) & 0xfe;
  misc_flags = misc_flags | 0x10;
  sVar3 = 0;
  while ((sVar3 < 6 && ((&unk_df836)[sVar3 * 0x40] != 4))) {
    sVar3 = sVar3 + 1;
  }
  sVar6 = 6;
  while ((sVar6 < 0xc && ((&unk_df836)[sVar6 * 0x40] != 4))) {
    sVar6 = sVar6 + 1;
  }
  dword_e03ac = (0x10 - (char)(&faceoff_bonus)[faceoff_ready_home >> 0x10]) +
                (short)(char)(&faceoff_bonus)[_faceoff_side_home >> 0x10] +
                ((ushort)(byte)(&unk_daea7)[(*(int *)(&unk_df860 + sVar6 * 0x80) >> 0x18) * 0x14] -
                (ushort)(byte)(&unk_dacb3)[(*(int *)(&unk_df860 + sVar3 * 0x80) >> 0x18) * 0x14]);
  sVar3 = randomrange(0x21);
  uVar4 = faceoff_side_away;
  last_touch_slot = sVar6;
  if (dword_e03ac <= sVar3) {
    uVar4 = faceoff_side_home;
    last_touch_slot = extraout_DX;
  }
  if ((uVar4 & 0x800) == 0) {
    dword_e03ae._2_2_ = faceoff_dir_home;
    dword_e03b2._2_2_ = 0x800;
  }
  else {
    dword_e03ae._2_2_ = faceoff_dir_away;
    dword_e03b2._2_2_ = -0x800;
  }
  dword_e03ba = CONCAT22(dword_e03ae._2_2_,(undefined2)dword_e03ba);
  if ((dword_e03ae._2_2_ & 8) == 0) {
    dword_e03ba = CONCAT22(dword_e03ae._2_2_,(undefined2)dword_e03ba) & 0x7ffff;
    sVar3 = randomrange(4);
    if (sVar3 != 0) goto LAB_0004dc41;
    cVar2 = randomrange(5);
    uVar1 = CONCAT12(cVar2 + -2,(undefined2)dword_e03ba);
  }
  else {
    cVar2 = randomrange(5);
    uVar1 = CONCAT12(cVar2 + -2,(undefined2)dword_e03ba);
  }
  dword_e03ba = (uint)(uVar1 & 0x7ffff);
  if (dword_e03b2._2_2_ < 0) {
    dword_e03ba = dword_e03ba ^ 0x40000;
  }
LAB_0004dc41:
  sVar3 = dword_e03ba._2_2_ * 2;
  dword_e03ba = CONCAT22(sVar3,(undefined2)dword_e03ba);
  *(short *)(param_1 + 0xc) = *(short *)(&dir8_vectors + sVar3 * 2) << 5;
  *(short *)(param_1 + 0xe) =
       *(short *)(&unk_c90e2 + ((int)dword_e03ba >> 0x10) * 2) * 0x20 + dword_e03b2._2_2_;
  uVar5 = randomrange(0x800);
  *(undefined2 *)(param_1 + 0x10) = uVar5;
  *p_puck_z = 0;
  *(byte *)(param_1 + 0x44) = *(byte *)(param_1 + 0x44) & 0xfb;
  set_state(param_1,0x18);
  set_state(&referee,0x1f);
  if (referee._2_2_ < 1) {
    word_e0028 = 0xfb00;
  }
  else {
    word_e0028 = 0x500;
  }
  return;
}


// ================================================================================================
// offside_entry_check @ 0x4dcdd [__watcall]
// ================================================================================================

longlong __watcall offside_entry_check(int param_1,uint unaff_EDX)

{
  __CHK(8);
  if (((((byte)option_flags & 2) != 0) && (penalty_shot_active == 0)) && (penalty_shot_setup == 0))
  {
    dword_e03ba._2_2_ = *p_puck_y;
    if ((*(byte *)(param_1 + 0x44) & 0x80) == 0) {
      dword_e03ba._2_2_ = -dword_e03ba._2_2_;
    }
    if (((0x4d < dword_e03ba._2_2_) && ((*(byte *)(*(int *)(param_1 + 0x6c) + 0x44) & 0x10) != 0))
       && ((game_flags & 0x10) == 0)) {
      maybe_queue_infraction(param_1,8);
      return CONCAT44(unaff_EDX,1);
    }
  }
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// carrier_zone_entry @ 0x4dd51 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

longlong __watcall carrier_zone_entry(int param_1,uint unaff_EDX)

{
  __CHK(0x10);
  if ((((game_flags & 0x10) == 0) && (((byte)option_flags & 8) != 0)) &&
     (((*(byte *)(param_1 + 0x45) & 0x80) != 0 ||
      (0 < *p_puck_y == ((*(byte *)(param_1 + 0x44) & 0x80) == 0))))) {
    if ((*(short *)(param_1 + 0x6a) != last_touch_slot) &&
       (last_touch_slot < 6 == *(short *)(param_1 + 0x6a) < 6)) {
      if ((*(byte *)(param_1 + 0x44) & 0x80) == 0) {
        if ((0x4d < last_touch_y) && (*(short *)(param_1 + 6) < 1)) {
LAB_0004de0b:
          return CONCAT44(unaff_EDX,1);
        }
      }
      else if ((_last_touch_slot >> 0x10 < -0x4d) && (-1 < *(short *)(param_1 + 6)))
      goto LAB_0004de0b;
    }
  }
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// update_carrier @ 0x4de14 [__watcall]
// ================================================================================================

void __watcall update_carrier(int param_1)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  short sVar4;
  short sVar5;
  
  __CHK(0x14);
  sVar4 = carrier_zone_entry();
  if ((sVar4 == 0) && ((game_flags & 1) == 0)) {
    last_touch_x = *(undefined2 *)(param_1 + 2);
    last_touch_y = *(undefined2 *)(param_1 + 6);
    last_touch_slot = *(undefined2 *)(param_1 + 0x6a);
  }
  iVar2 = *(int *)(param_1 + 0x6c);
  if ((short)*(char *)(param_1 + 0x47) == *(short *)(iVar2 + 0x30)) {
    if ((*(byte *)(iVar2 + 0x44) & 8) != 0) {
      *(byte *)(iVar2 + 0x44) = *(byte *)(iVar2 + 0x44) & 0xf7;
    }
  }
  else {
    if ((*(byte *)(iVar2 + 0x44) & 8) == 0) {
      *(undefined2 *)(iVar2 + 0x34) = *(undefined2 *)(iVar2 + 0x32);
      *(undefined2 *)(iVar2 + 0x32) = *(undefined2 *)(iVar2 + 0x30);
    }
    else {
      *(byte *)(iVar2 + 0x44) = *(byte *)(iVar2 + 0x44) & 0xf7;
    }
    cVar1 = *(char *)(param_1 + 0x47);
    *(short *)(iVar2 + 0x30) = (short)cVar1;
    if ((short)cVar1 == *(short *)(iVar2 + 0x34)) {
      *(undefined *)(iVar2 + 0x35) = 0xff;
    }
  }
  if (*(short *)(param_1 + 0x1a) != 0) {
    stop_flags._0_1_ = (byte)stop_flags & 0xef;
  }
  sVar5 = offside_entry_check(param_1);
  if ((sVar5 == 0) && (sVar4 != 0)) {
    maybe_queue_infraction(param_1,0x1d);
  }
  uVar3 = icing_state;
  if (((((icing_state & 0x40000) != 0) && ((icing_state & 0x10000) != 0)) &&
      (*(short *)(param_1 + 0x1a) != 0)) &&
     (((icing_state & 0x20000) != 0) != ((*(byte *)(param_1 + 0x44) & 0x80) != 0))) {
    maybe_queue_infraction(&entities + ((int)icing_state >> 0x18) * 0x20,6);
    return;
  }
  icing_state._0_3_ = (uint3)icing_state & 0xffff;
  dword_e03ba._2_2_ = *p_puck_y;
  if ((*(byte *)(param_1 + 0x44) & 0x80) != 0) {
    icing_state._0_3_ = CONCAT12(2,(short)uVar3);
    dword_e03ba._2_2_ = -dword_e03ba._2_2_;
  }
  icing_state = CONCAT13(*(undefined *)(param_1 + 0x6a),(uint3)icing_state);
  if (-1 < dword_e03ba._2_2_) {
    dword_e03ba._2_2_ = dword_df648._2_2_ - dword_df748._2_2_;
    if ((*(byte *)(param_1 + 0x44) & 0x40) != 0) {
      dword_e03ba._2_2_ = -dword_e03ba._2_2_;
    }
    if (-1 < dword_e03ba._2_2_) {
      icing_state = CONCAT13(*(undefined *)(param_1 + 0x6a),(uint3)icing_state) | 0x40000;
    }
  }
  return;
}


// ================================================================================================
// puck_spin @ 0x4dfa4 [__watcall]
// ================================================================================================

void __watcall puck_spin(int param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  int iVar1;
  
  __CHK(0xc);
  iVar1 = *(int *)(param_1 + 0xc) >> 0x10;
  if ((*(int *)(param_1 + 10) >> 0x10) + iVar1 < 0x14) {
    puck_flat();
    return;
  }
  *(ushort *)(param_1 + 0x36) = (dword_e03ba._2_2_ & 1 ^ *(ushort *)(param_1 + 0x36)) & 3;
  *(undefined2 *)(param_1 + 0x3c) = 0xffff;
  set_animation(param_1,0x239,iVar1,unaff_ECX,unaff_EDX,unaff_EBX);
  return;
}


// ================================================================================================
// ai_ref_faceoff @ 0x4dff7 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall
ai_ref_faceoff(int param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  undefined2 uVar1;
  short sVar2;
  
  __CHK(0xc);
  if ((((*(byte *)(param_1 + 0x44) & 0x20) == 0) && (dword_cbec6 == 0)) &&
     ((clock_seconds != 0 || (clock_sub != 0)))) {
    if ((*(byte *)(param_1 + 0x44) & 2) != 0) {
      *(byte *)(param_1 + 0x44) = *(byte *)(param_1 + 0x44) & 0xfd;
      if ((short)faceoff_spot < 1) {
        uVar1 = 2;
      }
      else {
        uVar1 = 6;
      }
      *(undefined2 *)(param_1 + 0x36) = uVar1;
      set_animation(param_1,0xc57,param_1,unaff_ECX,unaff_EDX,unaff_EBX);
      *(byte *)(param_1 + 0x44) = *(byte *)(param_1 + 0x44) & 0xfb;
      *(byte *)(param_1 + 0x45) = *(byte *)(param_1 + 0x45) & 0xdf;
    }
    if (((byte)stop_flags & 1) == 0) {
      if ((short)faceoff_spot < 1) {
        sVar2 = (short)faceoff_spot + -0xf;
      }
      else {
        sVar2 = (short)faceoff_spot + 0xf;
      }
      *(short *)(param_1 + 2) = sVar2;
      *(undefined2 *)(param_1 + 6) = faceoff_spot._2_2_;
      *(undefined2 *)(param_1 + 0xe) = 0;
      *(undefined2 *)(param_1 + 0xc) = *(undefined2 *)(param_1 + 0xe);
    }
  }
  return;
}


// ================================================================================================
// ai_ref_normal @ 0x4e0bd [__watcall]
// ================================================================================================

void __watcall ai_ref_normal(int param_1)

{
  char cVar1;
  short sVar2;
  undefined2 uVar3;
  int iVar4;
  
  __CHK(0x18);
  cVar1 = *p_puck_carrier;
  if ((*(byte *)(param_1 + 0x44) & 0x20) != 0) {
    return;
  }
  if ((clock_seconds == 0) && (clock_sub == 0)) {
    apply_skating(param_1,8);
    return;
  }
  if ((*(byte *)(param_1 + 0x44) & 2) != 0) {
    *(byte *)(param_1 + 0x44) = *(byte *)(param_1 + 0x44) & 0xfd;
    set_animation(param_1,0xa5b);
  }
  sVar2 = *p_puck_x;
  if (sVar2 < 0) {
    iVar4 = -(int)sVar2;
  }
  else {
    iVar4 = (int)sVar2;
  }
  if (iVar4 < 0x32) {
    sVar2 = *p_puck_y;
    if (sVar2 < 0) {
      iVar4 = -(int)sVar2;
    }
    else {
      iVar4 = (int)sVar2;
    }
    if (iVar4 < 0xad) goto LAB_0004e1bd;
    sVar2 = *p_puck_y;
    if (sVar2 < 0) {
      iVar4 = -(int)sVar2;
    }
    else {
      iVar4 = (int)sVar2;
    }
    if (0xe7 < iVar4) goto LAB_0004e1bd;
    if (*(short *)(param_1 + 2) < 1) {
      uVar3 = 0xffba;
    }
    else {
      uVar3 = 0x46;
    }
    *(undefined2 *)(param_1 + 0x2a) = uVar3;
    if (*p_puck_y < 1) {
      uVar3 = 0xff13;
    }
    else {
      uVar3 = 0xed;
    }
  }
  else {
LAB_0004e1bd:
    sVar2 = *p_puck_y;
    if (sVar2 < 0) {
      iVar4 = -(int)sVar2;
    }
    else {
      iVar4 = (int)sVar2;
    }
    if ((iVar4 < 99) ||
       ((-1 < *p_puck_carrier && (*p_puck_y < 0 == (((&unk_df860)[cVar1 * 0x80] & 0x80) != 0))))) {
      if (*(short *)(param_1 + 2) < 1) {
        uVar3 = 0xff70;
      }
      else {
        uVar3 = 0x90;
      }
      *(undefined2 *)(param_1 + 0x2a) = uVar3;
      iVar4 = (*(int *)(param_1 + 4) >> 0x10) - (camera >> 0x10);
      if (iVar4 < 0) {
        iVar4 = -iVar4;
      }
      if (iVar4 < 0x33) goto LAB_0004a337;
      uVar3 = camera._2_2_;
    }
    else {
      if (*(short *)(param_1 + 2) < 1) {
        uVar3 = 0xff88;
      }
      else {
        uVar3 = 0x78;
      }
      *(undefined2 *)(param_1 + 0x2a) = uVar3;
      if (*p_puck_y < 1) {
        uVar3 = 0xff18;
      }
      else {
        uVar3 = 0xe8;
      }
    }
  }
  *(undefined2 *)(param_1 + 0x2c) = uVar3;
LAB_0004a337:
  dword_e03ba._2_2_ = *(undefined2 *)(param_1 + 0x2a);
  dword_e03be._2_2_ = *(undefined2 *)(param_1 + 0x2c);
  ai_skate_towards(param_1,ai_ref_positioning);
  return;
}


// ================================================================================================
// ref_skate_to_point @ 0x4e292 [__watcall]
// ================================================================================================

void __watcall ref_skate_to_point(undefined4 *param_1)

{
  short sVar1;
  short sVar2;
  short sVar3;
  undefined2 uVar4;
  short sVar5;
  ushort uVar6;
  int iVar7;
  short sVar8;
  short sVar9;
  short sVar10;
  short local_20;
  
  __CHK(0x2c);
  sVar9 = dword_e03ba._2_2_ - *(short *)((int)param_1 + 2);
  sVar5 = sVar9;
  if (sVar9 < 0) {
    sVar5 = -sVar9;
  }
  sVar8 = dword_e03be._2_2_ - *(short *)((int)param_1 + 6);
  sVar1 = sVar8;
  if (sVar8 < 0) {
    sVar1 = -sVar8;
  }
  if ((sVar5 < 8) && (sVar1 < 8)) {
    *(undefined2 *)((int)param_1 + 0xe) = 0;
    *(undefined2 *)(param_1 + 3) = *(undefined2 *)((int)param_1 + 0xe);
    *(short *)((int)param_1 + 2) = dword_e03ba._2_2_;
    *(short *)((int)param_1 + 6) = dword_e03be._2_2_;
  }
  else {
    if (*(short *)((int)param_1 + 2) < 0) {
      sVar10 = -(short)((uint)*param_1 >> 0x10);
    }
    else {
      sVar10 = (short)((uint)*param_1 >> 0x10);
    }
    if (*(short *)((int)param_1 + 6) < 0) {
      sVar2 = -(short)((uint)param_1[1] >> 0x10);
    }
    else {
      sVar2 = (short)((uint)param_1[1] >> 0x10);
    }
    sVar3 = dword_e03be._2_2_;
    if ((int)dword_e03be < 0) {
      sVar3 = -dword_e03be._2_2_;
    }
    if (((sVar10 < 0x1f) && (0xf1 < sVar2)) && (sVar3 < 0xf2)) {
      if (*(short *)((int)param_1 + 6) < 0) {
        uVar4 = 0xff04;
      }
      else {
        uVar4 = 0xfc;
      }
      dword_e03be = CONCAT22(uVar4,(undefined2)dword_e03be);
      if (dword_e03ba < 0) {
        uVar4 = 0xffd8;
      }
      else {
        uVar4 = 0x28;
      }
      dword_e03ba = CONCAT22(uVar4,(undefined2)dword_e03ba);
      if (0 < *(short *)((int)param_1 + 0xe) != 0 < *(short *)((int)param_1 + 6)) {
        *(undefined2 *)((int)param_1 + 0xe) = 0;
      }
      sVar9 = dword_e03ba._2_2_ - *(short *)((int)param_1 + 2);
      sVar5 = sVar9;
      if (sVar9 < 0) {
        sVar5 = -sVar9;
      }
      sVar8 = dword_e03be._2_2_ - *(short *)((int)param_1 + 6);
      sVar1 = sVar8;
      if (sVar8 < 0) {
        sVar1 = -sVar8;
      }
    }
    else if ((((0xf < sVar10) && (sVar10 < 0x1f)) &&
             ((0xe7 < sVar2 && ((-1 < (int)(dword_e03be ^ param_1[1]) >> 0x10 && (sVar3 < 0xe8))))))
            && (0xe0 < sVar3)) {
      iVar7 = dword_e03ba >> 0x10;
      if (dword_e03ba < 0) {
        iVar7 = -iVar7;
      }
      if (iVar7 < 0x14) {
        if (*(short *)((int)param_1 + 6) < 0) {
          uVar4 = 0xff24;
        }
        else {
          uVar4 = 0xdc;
        }
        dword_e03be = CONCAT22(uVar4,(undefined2)dword_e03be);
        if (*(short *)((int)param_1 + 2) < 0) {
          uVar4 = 0xffd8;
        }
        else {
          uVar4 = 0x28;
        }
        dword_e03ba = CONCAT22(uVar4,(undefined2)dword_e03ba);
        if (0 < *(short *)((int)param_1 + 2) != 0 < *(short *)(param_1 + 3)) {
          *(undefined2 *)(param_1 + 3) = 0;
        }
        sVar9 = dword_e03ba._2_2_ - *(short *)((int)param_1 + 2);
        sVar5 = sVar9;
        if (sVar9 < 0) {
          sVar5 = -sVar9;
        }
        sVar8 = dword_e03be._2_2_ - *(short *)((int)param_1 + 6);
        sVar1 = sVar8;
        if (sVar8 < 0) {
          sVar1 = -sVar8;
        }
      }
    }
    ai_skate_towards(param_1);
    if ((sVar5 < 0x19) && (sVar1 < 0x19)) {
      if (*(short *)(param_1 + 3) < 0) {
        iVar7 = -(*(int *)((int)param_1 + 10) >> 0x10);
      }
      else {
        iVar7 = *(int *)((int)param_1 + 10) >> 0x10;
      }
      if (0x9c4 < iVar7) {
        iVar7 = *(int *)((int)param_1 + 10);
        *(short *)(param_1 + 3) =
             (short)((uint)iVar7 >> 0x10) -
             (short)((int)(((iVar7 >> 0x10) + (iVar7 >> 0x1f) * -4) -
                          (uint)((iVar7 >> 0x1f) << 1 < 0)) >> 2);
      }
      if (*(short *)((int)param_1 + 0xe) < 0) {
        iVar7 = -((int)param_1[3] >> 0x10);
      }
      else {
        iVar7 = (int)param_1[3] >> 0x10;
      }
      if (0x9c4 < iVar7) {
        iVar7 = param_1[3];
        *(short *)((int)param_1 + 0xe) =
             (short)((uint)iVar7 >> 0x10) -
             (short)((int)(((iVar7 >> 0x10) + (iVar7 >> 0x1f) * -4) -
                          (uint)((iVar7 >> 0x1f) << 1 < 0)) >> 2);
      }
    }
    if (*(short *)((int)param_1 + 0x6a) == 0x10) {
      sVar10 = 0xa5b;
      local_20 = 0xa73;
    }
    else if (*(short *)((int)param_1 + 0x1a) == 0) {
      sVar10 = 0x99;
      local_20 = 0x1f1;
    }
    else {
      sVar10 = 0x289;
      local_20 = 0x2e9;
    }
    if (7 < sVar5) {
      if (*(short *)(param_1 + 3) < 0) {
        iVar7 = -(*(int *)((int)param_1 + 10) >> 0x10);
      }
      else {
        iVar7 = *(int *)((int)param_1 + 10) >> 0x10;
      }
      if (iVar7 < 0x640) {
        if (((*(short *)(param_1 + 3) == 0) &&
            (sVar5 = local_20, sVar10 == *(short *)(param_1 + 0xe))) ||
           (sVar5 = sVar10, *(short *)(param_1 + 0xe) == 0)) {
          set_animation(param_1,sVar5);
        }
        if (sVar9 < 1) {
          uVar4 = 0xf9c0;
        }
        else {
          uVar4 = 0x640;
        }
        *(undefined2 *)(param_1 + 3) = uVar4;
      }
    }
    if (7 < sVar1) {
      if (*(short *)((int)param_1 + 0xe) < 0) {
        iVar7 = -((int)param_1[3] >> 0x10);
      }
      else {
        iVar7 = (int)param_1[3] >> 0x10;
      }
      if (iVar7 < 0x640) {
        if (((*(short *)(param_1 + 3) == 0) && (sVar10 == *(short *)(param_1 + 0xe))) ||
           (local_20 = sVar10, *(short *)(param_1 + 0xe) == 0)) {
          set_animation(param_1,local_20);
        }
        if (sVar8 < 1) {
          uVar4 = 0xf9c0;
        }
        else {
          uVar4 = 0x640;
        }
        *(undefined2 *)((int)param_1 + 0xe) = uVar4;
      }
    }
    sVar5 = direction8((int)(short)(dword_e03ba._2_2_ - *(short *)((int)param_1 + 2)),
                       (int)(short)(dword_e03be._2_2_ - *(short *)((int)param_1 + 6)));
    uVar6 = sVar5 - *(short *)((int)param_1 + 0x36) & 7;
    if ((2 < ((int)(short)uVar6 + 1U & 7)) && (*(char *)((int)param_1 + 0x29) == '\0')) {
      if (uVar6 < 5) {
        sVar5 = 1;
      }
      else {
        sVar5 = -1;
      }
      *(ushort *)((int)param_1 + 0x36) = sVar5 + (short)((uint)param_1[0xd] >> 0x10) & 7;
    }
  }
  return;
}


// ================================================================================================
// ref_check_announcements @ 0x4e71a [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

longlong __watcall ref_check_announcements(undefined4 param_1,uint unaff_EDX)

{
  bool bVar1;
  short sVar2;
  undefined4 uVar3;
  int iVar4;
  int extraout_EDX;
  undefined4 extraout_EDX_00;
  
  __CHK(0xc);
  if (((game_flags & 0x10) == 0) && (dword_cbebe >> 0x10 == -1)) {
    if (((ref_infraction == 0x1d) ||
        (((ref_infraction == 0x1e || (ref_infraction == 3)) || (ref_infraction == 4)))) ||
       ((ref_infraction == 8 || (ref_infraction == 6)))) {
      bVar1 = false;
    }
    else {
      bVar1 = true;
    }
    if (bVar1) goto LAB_0004e8ea;
    iVar4 = dword_e9ab6 >> 0x11;
    if ((_period_idx >> 0x10 < iVar4) && (0x3b < clock_seconds)) {
      iVar4 = CONCAT31((int3)(dword_e9ab6 >> 0x19),misc_flags);
      if ((misc_flags & 0x80) != 0) {
        misc_flags = misc_flags & 0x7f;
        uVar3 = 2;
        goto LAB_0004e7ba;
      }
    }
    if ((period_idx == 2) && (clock_seconds <= dword_e9aac)) {
      dword_e9aac = -1;
      uVar3 = 5;
LAB_0004e7ba:
      play_speech(uVar3);
      return (ulonglong)unaff_EDX << 0x20;
    }
    if (((option_flags._1_1_ & 1) != 0) &&
       ((sound_enabled != '\0' &&
        (iVar4 = (dword_df748 >> 0x10) - (dword_df648 >> 0x10), iVar4 != 0)))) {
      sVar2 = randomrange(4,iVar4);
      iVar4 = extraout_EDX;
      if (sVar2 == 0) {
        if (extraout_EDX < 1) {
          uVar3 = 1;
        }
        else {
          uVar3 = 4;
        }
        goto LAB_0004e7ba;
      }
    }
    sVar2 = randomrange(8,iVar4);
    iVar4 = (int)sVar2;
    if ((dword_cc0ec == 0) && (iVar4 == 0)) {
      if (((((byte)option_flags & 0x80) != 0) && (((byte)dword_c541f & 0x2a) != 0)) &&
         (crowd_noise._2_2_ < 0x2bd)) {
        load_cutscene_clip(0);
        if (dword_cbeca >> 0x10 != -1) {
          sub_66dda();
          return CONCAT44(unaff_EDX,1);
        }
      }
    }
    else if ((dword_cc0ec == 0) && (iVar4 == 1)) {
      load_cutscene_clip(2);
      if (dword_cbeca >> 0x10 != -1) {
        play_speech(9);
        sub_66dda();
        return CONCAT44(unaff_EDX,extraout_EDX_00);
      }
    }
    else {
      if (iVar4 < 5) {
        iVar4 = iVar4 + 4;
      }
      else {
        if (iVar4 != 5) goto LAB_0004e8ea;
        iVar4 = 0xb;
      }
      play_speech(iVar4);
    }
  }
LAB_0004e8ea:
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// ai_ref_get_new_puck @ 0x4e8ef [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall ai_ref_get_new_puck(int param_1)

{
  byte bVar1;
  short sVar2;
  int iVar3;
  undefined4 uVar4;
  short sVar5;
  
  __CHK(0x18);
  if ((*(byte *)(param_1 + 0x44) & 0x20) != 0) {
    return;
  }
  if ((*(byte *)(param_1 + 0x44) & 2) != 0) {
    if (((dword_cbec6 != 0) || ((clock_seconds == 0 && (clock_sub == 0)))) ||
       ((period_idx == 3 && (dword_df622._2_2_ != dword_df722._2_2_)))) {
      ref_phase = 0xffff;
      if (dword_cbebe._2_2_ == 0x100) {
        dword_cbebe._2_2_ = 600;
      }
      set_state(&puck,0x1b);
      uVar4 = 0x1e;
      goto LAB_0004e97c;
    }
    ref_phase = 1;
    *(byte *)(param_1 + 0x44) = *(byte *)(param_1 + 0x44) & 0xfd;
    all_goto_positions();
    *(undefined2 *)(param_1 + 0x28) = 8;
    *(undefined2 *)(param_1 + 0x2c) = 0;
    *(undefined2 *)(param_1 + 0x2a) = 0xa0;
    *(undefined2 *)(param_1 + 0x26) = 0;
    *(byte *)(param_1 + 0x45) = *(byte *)(param_1 + 0x45) | 0x20;
    *(undefined2 *)(param_1 + 0x30) = 0;
    *(undefined2 *)(param_1 + 0x32) = 0;
    set_animation(param_1,0xa5b);
    iVar3 = ref_check_announcements();
    if (iVar3 != 0) {
      return;
    }
    if (dword_cbebe._2_2_ == 0x100) {
      dword_cbebe._2_2_ = 600;
    }
  }
  sVar2 = *(short *)(param_1 + 6) - *(short *)(param_1 + 0x2c);
  dword_e03ba = CONCAT22(sVar2,(undefined2)dword_e03ba);
  iVar3 = (int)sVar2;
  if (sVar2 < 0) {
    iVar3 = -iVar3;
  }
  if ((6 < iVar3) ||
     (sVar2 = *(short *)(param_1 + 2) - *(short *)(param_1 + 0x2a),
     dword_e03ba = CONCAT22(sVar2,(undefined2)dword_e03ba), sVar2 < -10)) {
    dword_e03ba = CONCAT22(*(undefined2 *)(param_1 + 0x2a),(undefined2)dword_e03ba);
    dword_e03be._2_2_ = *(undefined2 *)(param_1 + 0x2c);
    ref_skate_to_point(param_1,0);
    return;
  }
  sVar2 = *(short *)(param_1 + 0x26);
  sVar5 = sVar2 + -1;
  *(short *)(param_1 + 0x26) = sVar5;
  if (-1 < sVar5) {
    return;
  }
  *(short *)(param_1 + 0x26) = sVar2 + 7;
  set_animation(param_1,0xa5b);
  _dword_e03ac = 2;
  if (*(short *)(param_1 + 0x36) != 2) {
    bVar1 = 2U - (char)*(short *)(param_1 + 0x36) & 7;
    _dword_e03ac = (uint)bVar1;
    if (bVar1 < 5) {
      sVar2 = 1;
    }
    else {
      sVar2 = -1;
    }
    *(ushort *)(param_1 + 0x36) = sVar2 + (short)((uint)*(undefined4 *)(param_1 + 0x34) >> 0x10) & 7
    ;
  }
  *(undefined2 *)(param_1 + 0xe) = 0;
  *(undefined2 *)(param_1 + 0xc) = 0;
  if (dword_e03ac != *(short *)(param_1 + 0x36)) {
    return;
  }
  *(byte *)(param_1 + 0x44) = *(byte *)(param_1 + 0x44) | 0x20;
  set_animation(param_1,0xc1b);
  uVar4 = 0x22;
LAB_0004e97c:
  set_state(param_1,uVar4);
  return;
}


// ================================================================================================
// ai_ref_call_penalty @ 0x4eb04 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall ai_ref_call_penalty(int param_1)

{
  bool bVar1;
  short sVar2;
  short sVar3;
  int iVar4;
  int iVar5;
  byte bVar6;
  int iVar7;
  int iVar8;
  
  __CHK(0x2c);
  if ((*(byte *)(param_1 + 0x44) & 0x20) != 0) {
    return;
  }
  if ((*(byte *)(param_1 + 0x44) & 2) != 0) {
    *(byte *)(param_1 + 0x44) = *(byte *)(param_1 + 0x44) & 0xfd;
    if ((short)(&ref_signal_dir)[_ref_phase >> 0x10] < 0) {
      if (ref_infraction == 7) {
        bVar1 = *p_puck_y < 0 != ((game_flags & 2) != 0);
        if (bVar1) {
          iVar5 = 0xdf714;
        }
        else {
          iVar5 = 0xdf614;
        }
        iVar7 = (dword_e9ab6 >> 0x10) - (_period_idx >> 0x10);
        if ((clock_seconds < 0x3c) && (clock_sub != 0)) {
          iVar7 = iVar7 + -1;
        }
        if (*(short *)(iVar5 + 0x34) < 0) {
          iVar4 = -1;
        }
        else {
          iVar4 = *(int *)(iVar5 + 0x32) >> 0x10;
        }
        if (*(short *)(iVar5 + 0x32) < 0) {
          iVar8 = -1;
        }
        else {
          iVar8 = *(int *)(iVar5 + 0x30) >> 0x10;
        }
        announce_goal(bVar1,*(int *)(iVar5 + 0x2e) >> 0x10,iVar8,iVar4,_dword_e9aae >> 0x10,
                      iVar7 / 0x3c,iVar7 % 0x3c);
      }
      goto LAB_0004ec1b;
    }
    *(undefined2 *)(param_1 + 0x28) = 8;
    *(undefined2 *)(param_1 + 0x2c) = 0;
    *(undefined2 *)(param_1 + 0x2a) = 0xa0;
    *(undefined2 *)(param_1 + 0x26) = 0;
    *(byte *)(param_1 + 0x45) = *(byte *)(param_1 + 0x45) | 0x20;
    *(undefined2 *)(param_1 + 0x30) = 0;
    *(undefined2 *)(param_1 + 0x32) = 0;
  }
  sVar2 = *(short *)(param_1 + 6) - *(short *)(param_1 + 0x2c);
  dword_e03ba = CONCAT22(sVar2,(undefined2)dword_e03ba);
  iVar5 = (int)sVar2;
  if (sVar2 < 0) {
    iVar5 = -iVar5;
  }
  if ((0xc < iVar5) ||
     (sVar2 = *(short *)(param_1 + 2) - *(short *)(param_1 + 0x2a),
     dword_e03ba = CONCAT22(sVar2,(undefined2)dword_e03ba), sVar2 < -0x14)) {
    dword_e03ba = CONCAT22(*(undefined2 *)(param_1 + 0x2a),(undefined2)dword_e03ba);
    dword_e03be._2_2_ = *(undefined2 *)(param_1 + 0x2c);
    ref_skate_to_point(param_1,0);
    return;
  }
  sVar2 = *(short *)(param_1 + 0x26);
  sVar3 = sVar2 + -1;
  *(short *)(param_1 + 0x26) = sVar3;
  if (-1 < sVar3) {
    return;
  }
  *(short *)(param_1 + 0x26) = sVar2 + 7;
  set_animation(param_1,0xa5b);
  dword_e03ac = (&ref_signal_dir)[_ref_phase >> 0x10];
  if (dword_e03ac != *(ushort *)(param_1 + 0x36)) {
    bVar6 = (char)dword_e03ac - (char)*(ushort *)(param_1 + 0x36) & 7;
    dword_e03ac = (ushort)bVar6;
    if (bVar6 < 5) {
      sVar2 = 1;
    }
    else {
      sVar2 = -1;
    }
    *(ushort *)(param_1 + 0x36) = (short)((uint)*(undefined4 *)(param_1 + 0x34) >> 0x10) + sVar2 & 7
    ;
  }
  *(undefined2 *)(param_1 + 0xe) = 0;
  *(undefined2 *)(param_1 + 0xc) = 0;
  if (dword_e03ac != *(ushort *)(param_1 + 0x36)) {
    return;
  }
  *(byte *)(param_1 + 0x44) = *(byte *)(param_1 + 0x44) | 0x20;
  set_animation(param_1,*(int *)((int)&ref_signal_anim + (_ref_phase >> 0x10) * 2) >> 0x10);
LAB_0004ec1b:
  set_state(param_1,0x21);
  return;
}


// ================================================================================================
// ai_ref_pickup_puck @ 0x4ed7c [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall ai_ref_pickup_puck(int param_1)

{
  bool bVar1;
  short sVar2;
  undefined2 uVar3;
  short sVar4;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  int iVar8;
  char cVar9;
  
  __CHK(0x28);
  if ((*(byte *)(param_1 + 0x44) & 0x20) != 0) {
    return;
  }
  if ((((dword_cbeca._2_2_ != 2) && (dword_cbeca._2_2_ != 0)) && (-1 < dword_cbebe._2_2_)) &&
     (dword_cbebe._2_2_ < 0x100)) {
    set_animation(param_1,0xa5b);
    if (dword_cbebe._2_2_ < 0xec) {
      return;
    }
    if ((char)byte_e9ad3 != '\x01') {
      return;
    }
    cVar9 = byte_e9ad3._3_1_ != 0xff;
    if ((byte)byte_e9ad7 != 0xff) {
      cVar9 = cVar9 + '\x01';
    }
    sVar2 = user2_team._2_2_;
    if (byte_e9ad3._1_1_ != 0) {
      sVar2 = _away_team_id;
    }
    dword_e9a9e = CONCAT22(input_enabled,(short)dword_e9a9e);
    _input_enabled = 0;
    iVar7 = (short)(ushort)byte_e9ad3._1_1_ * 0x444;
    say_goal_wrapper((&team_abbrev)[sVar2],cVar9,
                     (&unk_db3ad)[iVar7 + (short)(ushort)byte_e9ad3._2_1_ * 0x27],
                     (&unk_db3ad)[(short)(ushort)byte_e9ad3._3_1_ * 0x27 + iVar7],
                     (&unk_db3ad)[(short)(ushort)(byte)byte_e9ad7 * 0x27 + iVar7]);
    if (period_idx < 3) {
      _input_enabled = dword_e9a9e >> 0x10;
      byte_e9ad3._0_1_ = 0xff;
      return;
    }
    _input_enabled = dword_e9a9e >> 0x10;
    dword_cbebe._2_2_ = 0x38;
    byte_e9ad3._0_1_ = 0xff;
    return;
  }
  if (infraction_queue._3_1_ != '\0') {
    set_animation(param_1,0xa5b);
    ref_phase = 0xffff;
    return;
  }
  sVar2 = *p_puck_x;
  if (sVar2 < 0) {
    iVar7 = -(int)sVar2;
  }
  else {
    iVar7 = (int)sVar2;
  }
  if (iVar7 < 0xa1) {
    sVar2 = *p_puck_y;
    if (sVar2 < 0) {
      iVar7 = -(int)sVar2;
    }
    else {
      iVar7 = (int)sVar2;
    }
    if (iVar7 < 0x113) {
      if ((*(byte *)(param_1 + 0x44) & 2) != 0) {
        if (((dword_cbec6 != 0) || ((clock_seconds == 0 && (clock_sub == 0)))) ||
           ((period_idx == 3 && (dword_df622._2_2_ != dword_df722._2_2_)))) {
          ref_phase = 0xffff;
          if (dword_cbebe._2_2_ == 0x100) {
            dword_cbebe._2_2_ = 600;
          }
          set_state(&puck,0x1b);
          uVar6 = 0x1e;
          goto LAB_0004f140;
        }
        ref_phase = 1;
        *(byte *)(param_1 + 0x44) = *(byte *)(param_1 + 0x44) & 0xfd;
        all_goto_positions();
        *(undefined2 *)(param_1 + 0x28) = 8;
        *(undefined2 *)(param_1 + 0x26) = 0;
        *(undefined2 *)(param_1 + 0x2e) = 0;
        *(byte *)(param_1 + 0x45) = *(byte *)(param_1 + 0x45) | 0x20;
        *(undefined2 *)(param_1 + 0x30) = 0;
        *(undefined2 *)(param_1 + 0x32) = 0;
        set_animation(param_1,0xa5b);
        if (ref_infraction == 4) {
          sVar2 = sub_62c37();
          if (sVar2 == 0) {
            iVar7 = (_ref_infraction >> 0x10) * 0x80;
            if (((&unk_df87f)[iVar7] == '\0') || ((short)dword_e9a9e != 0)) goto LAB_0004f0b9;
            (&unk_df87f)[iVar7] = 0;
            load_cutscene_clip(8);
            if (dword_cbeca >> 0x10 != -1) {
              dword_e9a9e = CONCAT22(dword_e9a9e._2_2_,1);
              sub_66dda();
              return;
            }
          }
        }
        else if (ref_infraction == 7) {
          if ((game_flags & 0x10) != 0) {
            period_over = 1;
            return;
          }
          goal_milestone_check();
        }
        else {
LAB_0004f0b9:
          iVar7 = ref_check_announcements();
          if (iVar7 != 0) {
            return;
          }
        }
        if (dword_cbebe._2_2_ == 0x100) {
          dword_cbebe._2_2_ = 600;
        }
      }
      if (dword_c5840 != 0) {
        return;
      }
      if (-1 < *p_puck_carrier) {
        *p_puck_carrier = -1;
        set_state(&puck,0x1a);
      }
      if (*(short *)(param_1 + 0x2e) < 0x259) {
        sVar2 = *p_puck_x;
        if (sVar2 < 0) {
          iVar7 = -(int)sVar2;
        }
        else {
          iVar7 = (int)sVar2;
        }
        if (iVar7 == 6) {
          sVar2 = *p_puck_y;
          if (sVar2 < 0) {
            iVar7 = -(int)sVar2;
          }
          else {
            iVar7 = (int)sVar2;
          }
          if (iVar7 != 0xf0) goto LAB_0004f1e3;
          *(short *)(param_1 + 0x2a) = *p_puck_x;
          if (*p_puck_y < 0) {
            uVar3 = 0xff1d;
          }
          else {
            uVar3 = 0xe3;
          }
          *(undefined2 *)(param_1 + 0x2c) = uVar3;
          dword_e03ba = CONCAT22(*(short *)(param_1 + 2) - *(short *)(param_1 + 0x2a),
                                 (undefined2)dword_e03ba);
          if (*p_puck_y < 0) {
            sVar2 = -0xee;
          }
          else {
            sVar2 = 0xee;
          }
          sVar2 = (short)((uint)*(undefined4 *)(param_1 + 4) >> 0x10) - sVar2;
        }
        else {
LAB_0004f1e3:
          *(short *)(param_1 + 0x2a) = *p_puck_x + (*(short *)p_puck_vx >> 7);
          *(short *)(param_1 + 0x2c) = *p_puck_y + (*(short *)p_puck_vy >> 7);
          sVar2 = direction8((int)*(short *)p_puck_vx,(int)*(short *)p_puck_vy);
          dword_e03ba._2_2_ = sVar2;
          sVar2 = direction8((int)(short)(*(short *)(param_1 + 2) - *p_puck_x),
                             (int)(short)(*(short *)(param_1 + 6) - *p_puck_y));
          if (((7 < dword_e03ba._2_2_) || (7 < sVar2)) || (sVar2 == dword_e03ba._2_2_)) {
            *(short *)(param_1 + 0x2a) = *p_puck_x;
            *(short *)(param_1 + 0x2c) = *p_puck_y;
          }
          iVar8 = *(int *)(param_1 + 0x2a) >> 0x10;
          iVar7 = (int)*p_puck_y;
          if ((int)(iVar8 - 0xe8U ^ iVar7 - 0xe8U) < 0) {
            iVar5 = (0xe8 - iVar7) * ((*(int *)(param_1 + 0x28) >> 0x10) - (int)*p_puck_x);
            iVar8 = iVar8 - iVar7;
            if (iVar8 != 0) {
              iVar5 = iVar5 / iVar8;
            }
            sVar2 = *p_puck_x + (short)iVar5;
            if (sVar2 < 0) {
              iVar7 = -(int)sVar2;
            }
            else {
              iVar7 = (int)sVar2;
            }
            if (iVar7 < 0x19) {
              *(short *)(param_1 + 0x2a) = *p_puck_x;
              *(short *)(param_1 + 0x2c) = *p_puck_y;
            }
          }
          iVar8 = *(int *)(param_1 + 0x2a) >> 0x10;
          iVar7 = (int)*p_puck_y;
          if ((int)(iVar7 + 0xe8U ^ iVar8 + 0xe8U) < 0) {
            iVar5 = (-0xe8 - iVar7) * ((*(int *)(param_1 + 0x28) >> 0x10) - (int)*p_puck_x);
            iVar8 = iVar8 - iVar7;
            if (iVar8 != 0) {
              iVar5 = iVar5 / iVar8;
            }
            sVar2 = (short)iVar5 + *p_puck_x;
            if (sVar2 < 0) {
              iVar7 = -(int)sVar2;
            }
            else {
              iVar7 = (int)sVar2;
            }
            if (iVar7 < 0x19) {
              *(short *)(param_1 + 0x2a) = *p_puck_x;
              *(short *)(param_1 + 0x2c) = *p_puck_y;
            }
          }
          dword_e03ba = CONCAT22(*(short *)(param_1 + 2) - *p_puck_x,(undefined2)dword_e03ba);
          sVar2 = *(short *)(param_1 + 6) - *p_puck_y;
        }
        dword_e03be = CONCAT22(sVar2,(undefined2)dword_e03be);
        iVar7 = dword_e03ba >> 0x10;
        if (dword_e03ba < 0) {
          iVar7 = -iVar7;
        }
        if (0xc < iVar7) goto LAB_0004f596;
        iVar7 = (int)sVar2;
        if (sVar2 < 0) {
          iVar7 = -iVar7;
        }
        if (0xc < iVar7) goto LAB_0004f596;
        sVar2 = *p_puck_x;
        if (sVar2 < 0) {
          iVar7 = -(int)sVar2;
        }
        else {
          iVar7 = (int)sVar2;
        }
        if (iVar7 == 6) {
          sVar2 = *p_puck_y;
          if (sVar2 < 0) {
            iVar7 = -(int)sVar2;
          }
          else {
            iVar7 = (int)sVar2;
          }
          if (iVar7 != 0xf0) goto LAB_0004f488;
          if (*(short *)(param_1 + 6) < 0) {
            iVar7 = -(*(int *)(param_1 + 4) >> 0x10);
          }
          else {
            iVar7 = *(int *)(param_1 + 4) >> 0x10;
          }
          if (iVar7 < 0xe9) goto LAB_0004f488;
          bVar1 = false;
        }
        else {
LAB_0004f488:
          bVar1 = true;
        }
        if (!bVar1) {
LAB_0004f596:
          *(short *)(param_1 + 0x2e) = *(short *)(param_1 + 0x2e) + 1;
          dword_e03ba = CONCAT22(*(undefined2 *)(param_1 + 0x2a),(undefined2)dword_e03ba);
          dword_e03be = CONCAT22(*(undefined2 *)(param_1 + 0x2c),(undefined2)dword_e03be);
          ref_skate_to_point(param_1,0);
          return;
        }
        sVar2 = *(short *)(param_1 + 0x26);
        sVar4 = sVar2 + -1;
        *(short *)(param_1 + 0x26) = sVar4;
        if (-1 < sVar4) {
          return;
        }
        *(short *)(param_1 + 0x26) = sVar2 + 7;
        set_animation(param_1,0xa5b);
        dword_e03ac = direction8((int)(short)(*p_puck_x - *(short *)(param_1 + 2)),
                                 (int)(short)(*p_puck_y - *(short *)(param_1 + 6)));
        if (((short)dword_e03ac < 8) &&
           (2 < (((int)(short)dword_e03ac - (*(int *)(param_1 + 0x34) >> 0x10)) + 1U & 7))) {
          dword_e03ac = dword_e03ac - *(short *)(param_1 + 0x36) & 7;
          if (dword_e03ac < 5) {
            sVar2 = 1;
          }
          else {
            sVar2 = -1;
          }
          *(ushort *)(param_1 + 0x36) =
               sVar2 + (short)((uint)*(undefined4 *)(param_1 + 0x34) >> 0x10) & 7;
          goto LAB_0004f596;
        }
        *(undefined2 *)(param_1 + 0xe) = 0;
        *(undefined2 *)(param_1 + 0xc) = *(undefined2 *)(param_1 + 0xe);
        *p_puck_carrier = '\x10';
        *(undefined2 *)p_puck_vx = 0;
        *(undefined2 *)p_puck_vy = 0;
        *(undefined2 *)p_puck_vz = 0;
        *p_puck_z = 0xff9c;
        if ((short)dword_e03ac < 8) {
          *(ushort *)(param_1 + 0x36) = dword_e03ac;
        }
        *(byte *)(param_1 + 0x44) = *(byte *)(param_1 + 0x44) | 0x20;
        set_animation(param_1,0xc03);
      }
      else {
        *p_puck_carrier = '\x10';
        *(undefined2 *)p_puck_vx = 0;
        *(undefined2 *)p_puck_vy = 0;
        *(undefined2 *)p_puck_vz = 0;
        *p_puck_z = 100;
      }
      uVar6 = 0x22;
      goto LAB_0004f140;
    }
  }
  uVar6 = 0x24;
LAB_0004f140:
  set_state(param_1,uVar6);
  return;
}


// ================================================================================================
// ai_ref_goto_faceoff @ 0x4f5bf [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall ai_ref_goto_faceoff(int *param_1)

{
  byte bVar1;
  short sVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  short sVar6;
  
  __CHK(0x18);
  if (penalty_shot_phase == 0) {
    if ((*(byte *)(param_1 + 0x11) & 0x20) != 0) {
      return;
    }
    if ((*(byte *)(param_1 + 0x11) & 2) != 0) {
      *(byte *)(param_1 + 0x11) = *(byte *)(param_1 + 0x11) & 0xfd;
      *(undefined2 *)(param_1 + 10) = 8;
      *(undefined2 *)((int)param_1 + 0x26) = 0;
      if ((short)faceoff_spot < 1) {
        sVar2 = (short)faceoff_spot + -0xf;
      }
      else {
        sVar2 = (short)faceoff_spot + 0xf;
      }
      *(short *)((int)param_1 + 0x2a) = sVar2;
      *(undefined2 *)(param_1 + 0xb) = faceoff_spot._2_2_;
      *(byte *)((int)param_1 + 0x45) = *(byte *)((int)param_1 + 0x45) | 0x20;
      *(undefined2 *)(param_1 + 0xc) = 0;
      *(undefined2 *)((int)param_1 + 0x32) = 0;
      *p_puck_carrier = 0x10;
      *(undefined2 *)p_puck_vx = 0;
      *(undefined2 *)p_puck_vy = 0;
      *(undefined2 *)p_puck_vz = 0;
      *p_puck_z = 0xff9c;
      set_animation(param_1,0xa5b);
    }
    iVar4 = (*param_1 >> 0x10) - (param_1[10] >> 0x10);
    iVar5 = (param_1[1] >> 0x10) - (*(int *)((int)param_1 + 0x2a) >> 0x10);
    if (iVar4 * iVar4 + iVar5 * iVar5 < 0x40) {
      if (*(short *)(param_1 + 3) < 0) {
        iVar4 = -(*(int *)((int)param_1 + 10) >> 0x10);
      }
      else {
        iVar4 = *(int *)((int)param_1 + 10) >> 0x10;
      }
      if (iVar4 < 0x10) {
        if (*(short *)((int)param_1 + 0xe) < 0) {
          iVar4 = -(param_1[3] >> 0x10);
        }
        else {
          iVar4 = param_1[3] >> 0x10;
        }
        if (iVar4 < 0x10) {
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
          if ((short)faceoff_spot < 1) {
            _dword_e03ac = 2;
          }
          else {
            _dword_e03ac = 6;
          }
          if (dword_e03ac != *(short *)((int)param_1 + 0x36)) {
            bVar1 = (char)_dword_e03ac - (char)*(short *)((int)param_1 + 0x36) & 7;
            _dword_e03ac = (uint)bVar1;
            if (bVar1 < 5) {
              sVar2 = 1;
            }
            else {
              sVar2 = -1;
            }
            *(ushort *)((int)param_1 + 0x36) = sVar2 + (short)((uint)param_1[0xd] >> 0x10) & 7;
            return;
          }
          *(undefined2 *)((int)param_1 + 0xe) = 0;
          *(undefined2 *)(param_1 + 3) = *(undefined2 *)((int)param_1 + 0xe);
          iVar4 = speech_busy();
          if (iVar4 != 0) {
            return;
          }
          if (dword_cbeca >> 0x10 != -1) {
            return;
          }
          ref_phase = 0xffff;
          uVar3 = 0x1e;
          goto LAB_0004f5de;
        }
      }
    }
    dword_e03ba._2_2_ = *(undefined2 *)((int)param_1 + 0x2a);
    dword_e03be._2_2_ = *(undefined2 *)(param_1 + 0xb);
    ref_skate_to_point(param_1,0);
  }
  else {
    uVar3 = 0x2c;
LAB_0004f5de:
    set_state(param_1,uVar3);
  }
  return;
}


// ================================================================================================
// ai_ref_point_goal @ 0x4f7d0 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall ai_ref_point_goal(int param_1)

{
  byte bVar1;
  undefined2 uVar2;
  short sVar3;
  int iVar4;
  int iVar5;
  short sVar6;
  
  __CHK(0x18);
  if ((*(byte *)(param_1 + 0x44) & 0x20) == 0) {
    if ((*(byte *)(param_1 + 0x44) & 2) != 0) {
      *(byte *)(param_1 + 0x44) = *(byte *)(param_1 + 0x44) & 0xfd;
      *(undefined2 *)(param_1 + 0x28) = 8;
      *(undefined2 *)(param_1 + 0x26) = 0;
      if (*p_puck_y < 1) {
        uVar2 = 0xff1a;
      }
      else {
        uVar2 = 0xe6;
      }
      *(undefined2 *)(param_1 + 0x2c) = uVar2;
      if (*(short *)(param_1 + 2) < 1) {
        uVar2 = 0xffce;
      }
      else {
        uVar2 = 0x32;
      }
      *(undefined2 *)(param_1 + 0x2a) = uVar2;
      *(byte *)(param_1 + 0x45) = *(byte *)(param_1 + 0x45) | 0x20;
      *(undefined2 *)(param_1 + 0x30) = 0;
      *(undefined2 *)(param_1 + 0x32) = 0;
    }
    sVar3 = *(short *)(param_1 + 6) - *(short *)(param_1 + 0x2c);
    dword_e03ba = CONCAT22(sVar3,(undefined2)dword_e03ba);
    iVar4 = (int)sVar3;
    if (sVar3 < 0) {
      iVar4 = -iVar4;
    }
    if (iVar4 < 0xd) {
      if (*(short *)(param_1 + 6) < 0) {
        iVar4 = -(*(int *)(param_1 + 4) >> 0x10);
      }
      else {
        iVar4 = *(int *)(param_1 + 4) >> 0x10;
      }
      if (*(short *)(param_1 + 0x2c) < 0) {
        iVar5 = -(*(int *)(param_1 + 0x2a) >> 0x10);
      }
      else {
        iVar5 = *(int *)(param_1 + 0x2a) >> 0x10;
      }
      if (iVar4 <= iVar5) {
        sVar3 = *(short *)(param_1 + 2) - *(short *)(param_1 + 0x2a);
        dword_e03ba = CONCAT22(sVar3,(undefined2)dword_e03ba);
        iVar4 = (int)sVar3;
        if (sVar3 < 0) {
          iVar4 = -iVar4;
        }
        if (iVar4 < 0xd) {
          sVar3 = *(short *)(param_1 + 0x26);
          sVar6 = sVar3 + -1;
          *(short *)(param_1 + 0x26) = sVar6;
          if (-1 < sVar6) {
            return;
          }
          *(short *)(param_1 + 0x26) = sVar3 + 7;
          set_animation(param_1,0xa5b);
          sVar3 = direction8((int)-*(short *)(param_1 + 2),
                             (int)(short)(*(short *)(param_1 + 0x2c) - *(short *)(param_1 + 6)));
          _dword_e03ac = (int)sVar3;
          if (sVar3 != *(short *)(param_1 + 0x36)) {
            bVar1 = (char)sVar3 - (char)*(short *)(param_1 + 0x36) & 7;
            _dword_e03ac = CONCAT22(sVar3 >> 0xf,(ushort)bVar1);
            if (bVar1 < 5) {
              sVar3 = 1;
            }
            else {
              sVar3 = -1;
            }
            *(ushort *)(param_1 + 0x36) =
                 sVar3 + (short)((uint)*(undefined4 *)(param_1 + 0x34) >> 0x10) & 7;
            return;
          }
          *(undefined2 *)(param_1 + 0xe) = 0;
          *(undefined2 *)(param_1 + 0xc) = *(undefined2 *)(param_1 + 0xe);
          *(byte *)(param_1 + 0x44) = *(byte *)(param_1 + 0x44) | 0x20;
          set_animation(param_1,0xc1b);
          set_state(param_1,0x20);
          return;
        }
      }
    }
    dword_e03ba = CONCAT22(*(undefined2 *)(param_1 + 0x2a),(undefined2)dword_e03ba);
    dword_e03be._2_2_ = *(undefined2 *)(param_1 + 0x2c);
    ref_skate_to_point(param_1,0);
  }
  return;
}


// ================================================================================================
// ai_null @ 0x4f990 [__watcall]
// ================================================================================================

void __watcall ai_null(void)

{
  __CHK(4);
  return;
}


// ================================================================================================
// breakaway_next_waypoint @ 0x4f99b [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall breakaway_next_waypoint(void)

{
  __CHK(8);
  _breakaway_lane_x = *(int *)(&breakaway_waypoints + _breakaway_waypoint * 0xc);
  if (_breakaway_lane_side < 0) {
    _breakaway_lane_x = -_breakaway_lane_x;
  }
  _breakaway_target_y = *(undefined4 *)(&unk_ccb1c + _breakaway_waypoint * 0xc);
  _breakaway_trigger_y = *(undefined4 *)(&unk_ccb20 + _breakaway_waypoint * 0xc);
  _breakaway_waypoint = _breakaway_waypoint + 1;
  return;
}


// ================================================================================================
// breakaway_pick_lane @ 0x4f9ef [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall
breakaway_pick_lane(int *param_1,int unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  short sVar1;
  int iVar2;
  int extraout_EDX;
  int extraout_EDX_00;
  int extraout_EDX_01;
  int extraout_EDX_02;
  
  __CHK(0xc);
  if (unaff_EDX < 0x27) {
    sVar1 = randomrange(4,0x3a,param_1,unaff_ECX,unaff_ECX,unaff_EBX);
    if (sVar1 == 0) {
      sVar1 = randomrange(0x10);
      _breakaway_lane_x = extraout_EDX_02;
      if (7 < sVar1) goto LAB_0004fabd;
    }
    else {
      _breakaway_lane_x = extraout_EDX_01;
      if (*(char *)((int)param_1 + 0x65) == '\0') goto LAB_0004fabd;
    }
    _breakaway_lane_x = -0x3a;
LAB_0004fabd:
    if ((*(byte *)(param_1 + 0x11) & 0x80) == 0) {
      _breakaway_lane_x = -_breakaway_lane_x;
    }
    _breakaway_lane_side = _breakaway_lane_x;
    _breakaway_target_y = 0x3c;
    _breakaway_trigger_y = 0x1e;
    return;
  }
  iVar2 = *param_1 >> 0x10;
  if (iVar2 < 0) {
    iVar2 = -iVar2;
  }
  if (0x14 < iVar2) {
    _breakaway_lane_x = 0;
    _breakaway_target_y = 0x97;
    _breakaway_trigger_y = 0x66;
    _breakaway_waypoint = 2;
    _breakaway_lane_side = 0;
    return;
  }
  sVar1 = randomrange(4,0x2c,param_1,unaff_ECX,unaff_ECX,unaff_EBX);
  if (sVar1 == 0) {
    sVar1 = randomrange(0x10);
    _breakaway_lane_side = extraout_EDX_00;
    if (7 < sVar1) goto LAB_0004fa57;
  }
  else {
    _breakaway_lane_side = extraout_EDX;
    if (*(char *)((int)param_1 + 0x65) == '\0') goto LAB_0004fa57;
  }
  _breakaway_lane_side = -0x2c;
LAB_0004fa57:
  if ((*(byte *)(param_1 + 0x11) & 0x80) == 0) {
    _breakaway_lane_side = -_breakaway_lane_side;
  }
  _breakaway_waypoint = 2;
  _breakaway_target_y = 0x97;
  _breakaway_trigger_y = 0x66;
  _breakaway_lane_x = _breakaway_lane_side;
  return;
}


// ================================================================================================
// ai_breakaway @ 0x4fae8 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall ai_breakaway(int param_1)

{
  byte bVar1;
  undefined2 uVar2;
  short sVar3;
  short sVar4;
  int iVar5;
  uint uVar6;
  
  __CHK(0x14);
  if (((short)*p_puck_carrier != *(short *)(param_1 + 0x6a)) ||
     (bVar1 = *(byte *)(param_1 + 0x44), (bVar1 & 8) != 0)) {
    ai_default_skate(param_1);
    return;
  }
  if ((bVar1 & 0x20) == 0) {
    if ((game_flags & 1) != 0) {
      set_animation(param_1,0x289);
      *(undefined2 *)(param_1 + 0x3e) = 0x3c;
      skate_idle(param_1);
      return;
    }
    iVar5 = *(int *)(param_1 + 4) >> 0x10;
    if ((bVar1 & 0x80) == 0) {
      iVar5 = -iVar5;
    }
    if ((*(byte *)(param_1 + 0x44) & 2) != 0) {
      *(byte *)(param_1 + 0x44) = *(byte *)(param_1 + 0x44) & 0xfd;
      *(undefined2 *)(param_1 + 0x26) = 0;
      *(undefined *)(param_1 + 0x29) = 0;
      *(undefined *)(param_1 + 0x28) = 8;
      _breakaway_waypoint = 0;
      uVar2 = randomrange(4);
      *(undefined2 *)(param_1 + 0x2a) = uVar2;
      breakaway_pick_lane(param_1,iVar5);
    }
    if (_breakaway_trigger_y < 0) {
      iVar5 = (*(int *)(param_1 + 0x34) >> 0x10) - _breakaway_heading;
      if (iVar5 != 0) {
        uVar6 = iVar5 + 1U & 7;
        if (2 < uVar6) {
          sVar3 = randomrange(4);
          if (sVar3 == 0) goto LAB_0004fbea;
        }
        if (uVar6 < 3) {
          sVar3 = randomrange(0x20);
          if (sVar3 == 0) {
LAB_0004fbea:
            sVar4 = randomrange(2);
            sVar3 = 2;
            if (_breakaway_lane_side < 0) {
              sVar3 = 5;
            }
            pending_dir = sVar4 + sVar3;
            shot_power._0_2_ = 0x14;
            dword_e03ba = CONCAT22(-*(short *)(param_1 + 2),(undefined2)dword_e03ba);
            if ((*(byte *)(param_1 + 0x44) & 0x80) == 0) {
              sVar3 = -0xe8;
            }
            else {
              sVar3 = 0xe8;
            }
            sVar3 = sVar3 - (short)((uint)*(undefined4 *)(param_1 + 4) >> 0x10);
            dword_e03be = CONCAT22(sVar3,(undefined2)dword_e03be);
            sVar3 = direction8((int)-*(short *)(param_1 + 2),(int)sVar3);
            sVar3 = shot_is_backhand(param_1,(int)sVar3);
            if (sVar3 == 0) {
              uVar2 = 0xe2b;
            }
            else {
              uVar2 = 0xdd3;
            }
            set_animation(param_1,uVar2);
            advance_animation(param_1);
            *(undefined2 *)(param_1 + 0x3c) = 2;
            do_shot(param_1);
            return;
          }
        }
      }
    }
    else if (_breakaway_trigger_y <= iVar5) {
      breakaway_next_waypoint();
      _breakaway_heading = *(int *)(param_1 + 0x34) >> 0x10;
    }
    dword_e03ba = CONCAT22(breakaway_lane_x,(undefined2)dword_e03ba);
    sVar3 = breakaway_target_y;
    if ((*(byte *)(param_1 + 0x44) & 0x80) == 0) {
      sVar3 = -breakaway_target_y;
    }
    dword_e03be = CONCAT22(sVar3,(undefined2)dword_e03be);
    *(char *)(param_1 + 0x29) = *(char *)(param_1 + 0x29) + -2;
    ai_skate_towards(param_1,0);
  }
  return;
}


// ================================================================================================
// next_key_event @ 0x4fce8 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall next_key_event(void)

{
  __CHK(0x14);
  if (0 < control_count) {
    dword_e9a9e = CONCAT22(input_enabled,(undefined2)dword_e9a9e);
    control_count = control_count + -1;
    control_read_idx = control_read_idx + 1;
    if (0x31 < control_read_idx) {
      control_read_idx = 0;
    }
    _input_enabled = (int)input_enabled;
  }
  return;
}


// ================================================================================================
// flush_key_events @ 0x4fd47 [__watcall]
// ================================================================================================

void __watcall flush_key_events(void)

{
  __CHK(8);
  control_count = 0;
  dword_c4d18 = 0;
  return;
}


// ================================================================================================
// get_key_event @ 0x4fd62 [__watcall]
// ================================================================================================

longlong __watcall get_key_event(undefined4 param_1,uint unaff_EDX)

{
  __CHK(8);
  if (control_count == 0) {
    return (ulonglong)unaff_EDX << 0x20;
  }
  return CONCAT44(unaff_EDX,&control_ring + control_read_idx * 3);
}


// ================================================================================================
// line_change_bench_step @ 0x4fd8e [__watcall]
// ================================================================================================

undefined8 __watcall line_change_bench_step(int param_1,undefined4 unaff_EDX)

{
  byte bVar1;
  short sVar2;
  int iVar3;
  ushort uVar4;
  int iVar5;
  int iVar6;
  
  __CHK(0x18);
  bVar1 = *(byte *)(*(int *)(param_1 + 0x6c) + 0x44);
  iVar3 = CONCAT22((short)((uint)param_1 >> 0x10),CONCAT11(bVar1,(char)param_1));
  if ((bVar1 & 1) != 0) {
    *(byte *)(*(int *)(param_1 + 0x6c) + 0x44) = bVar1 & 0xfe;
    iVar3 = start_line_change_ui(param_1);
  }
  uVar4 = (ushort)((*(byte *)(param_1 + 0x44) & 0x40) != 0);
  if ((dword_e03ac & 0x40) == 0) {
    sVar2 = (&word_cbc66)[(short)uVar4];
    (&word_cbc66)[(short)uVar4] = sVar2 + -1;
    if (sVar2 == 0) {
      (&word_cbc66)[(short)uVar4] = 0x3b;
      if ((short)(&word_cbc62)[(short)uVar4] < 4) {
        iVar3 = *(int *)(&word_cbc5c + (short)uVar4);
        iVar6 = 4;
      }
      else {
        iVar3 = *(int *)(&word_cbc5c + (short)uVar4);
        iVar6 = 2;
      }
      iVar5 = (iVar3 >> 0x10) + 1;
      iVar3 = iVar5 / iVar6;
      (&word_cbc5e)[(short)uVar4] = (short)(iVar5 % iVar6);
      (&word_cbc62)[(short)uVar4] =
           *(undefined2 *)(&unk_ccb4a + (*(int *)(&word_cbc60 + (short)uVar4) >> 0x10) * 2);
      (&word_cbc56)[(short)uVar4] = 1;
      (&word_cbc5a)[(short)uVar4] = 0xc;
    }
    sVar2 = (&word_cbc5a)[(short)uVar4];
    (&word_cbc5a)[(short)uVar4] = sVar2 + -1;
    if (sVar2 == 0) {
      (&word_cbc5a)[(short)uVar4] = 0xb;
      (&word_cbc56)[(short)uVar4] = (ushort)((&word_cbc56)[(short)uVar4] == 0);
    }
    if (((((*(byte *)(param_1 + 0x44) & 8) != 0) && (controls_blocked == 0)) &&
        ((*(byte *)(param_1 + 0x44) & 0x20) == 0)) && ((*(byte *)(param_1 + 0x45) & 1) == 0)) {
      iVar3 = apply_skating(param_1,dword_e03ba >> 0x10);
    }
  }
  else {
    dword_e03ac = (&word_cbc5e)[(short)uVar4];
    iVar3 = cpu_line_change_select(param_1);
    (&word_cbc56)[(short)uVar4] = 0;
    (&word_cbc6a)[(short)uVar4] = 0;
  }
  return CONCAT44(unaff_EDX,iVar3);
}


// ================================================================================================
// faceoff_control @ 0x4ff0d [__watcall]
// ================================================================================================

void __watcall
faceoff_control(int param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  byte bVar1;
  short sVar2;
  int iVar3;
  undefined4 uVar4;
  
  __CHK(0x10);
  if (*(char *)(param_1 + 0x1e + (*(int *)(param_1 + 0x1a) >> 0x10)) == '\x17') {
    if ((*(byte *)(param_1 + 0x44) & 0x80) == 0) {
      faceoff_dir_home = dword_e03ba._2_2_;
    }
    else {
      faceoff_dir_away = dword_e03ba._2_2_;
    }
    bVar1 = *(byte *)(param_1 + 0x45);
    if ((bVar1 & 2) == 0) {
      if ((dword_e03be._2_1_ & 0x10) == 0) {
        iVar3 = CONCAT22((short)((uint)unaff_ECX >> 0x10),*(undefined2 *)(param_1 + 0x2e)) + -1;
        sVar2 = (short)iVar3;
        *(short *)(param_1 + 0x2e) = sVar2;
        if (sVar2 < 0) {
          set_animation(param_1,0x7f1,param_1,iVar3,unaff_EDX,unaff_ECX,unaff_EBX);
          return;
        }
      }
      else {
        *(byte *)(param_1 + 0x45) = bVar1 | 2;
        if (faceoff_timer < 0x11) {
          *(byte *)(param_1 + 0x44) = *(byte *)(param_1 + 0x44) | 0x20;
          uVar4 = 0x7dd;
        }
        else {
          uVar4 = 0xd05;
        }
        set_animation(param_1,uVar4,param_1,bVar1,unaff_EDX,unaff_ECX,unaff_EBX);
        *(undefined2 *)(param_1 + 0x2e) = 0xffff;
      }
    }
  }
  return;
}


// ================================================================================================
// start_hook @ 0x4ffae [__watcall]
// ================================================================================================

void __watcall start_hook(int param_1,int unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  short sVar1;
  undefined4 uVar2;
  
  __CHK(8);
  *(byte *)(param_1 + 0x44) = *(byte *)(param_1 + 0x44) | 0x20;
  if (*(short *)(param_1 + 0x18) != 0) {
    sVar1 = *(short *)(param_1 + 6) - *(short *)(unaff_EDX + 6);
    if ((*(byte *)(param_1 + 0x44) & 0x80) != 0) {
      sVar1 = -sVar1;
    }
    if (-1 < sVar1) {
      uVar2 = 0x639;
      goto LAB_0004ffe7;
    }
  }
  uVar2 = 0x873;
LAB_0004ffe7:
  set_animation(param_1,uVar2,unaff_EDX,unaff_ECX,unaff_EBX);
  return;
}


// ================================================================================================
// try_block_shot @ 0x4ffee [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 __watcall try_block_shot(int *param_1,undefined4 unaff_EDX)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  bool bVar7;
  short sVar8;
  short sVar9;
  short local_28;
  
  __CHK(0x34);
  if (-1 < *p_puck_carrier) {
    bVar7 = *(short *)((int)param_1 + 0x6a) < 6;
    if (*p_puck_carrier < '\x06' == bVar7) {
      uVar1 = (uint)(*p_puck_carrier < '\x06' != bVar7);
      goto LAB_00050333;
    }
  }
  sVar8 = *p_puck_y;
  if (sVar8 < 0) {
    iVar2 = -(int)sVar8;
  }
  else {
    iVar2 = (int)sVar8;
  }
  if (((iVar2 < 0xe9) && (0x4d < iVar2)) && (*(short *)((int)param_1 + 0x4e) < 0x51)) {
    bVar7 = (*(byte *)(param_1 + 0x11) & 0x80) != 0;
    iVar2 = bVar7 + 0xc;
    if (bVar7) {
      iVar3 = 3;
    }
    else {
      iVar3 = 1;
    }
    if (9 < *(int *)((int)&goal_prediction + iVar3 * 2) >> 0x10) {
      if (*p_puck_carrier < '\0') {
        if ((((bVar7) && (0 < *(short *)p_puck_vy)) || ((!bVar7 && (*(short *)p_puck_vy < 0)))) ||
           ((_coll_half_h < 0 || (_last_shooter < 6 == *(short *)((int)param_1 + 0x6a) < 6))))
        goto LAB_00050331;
        iVar3 = _coll_half_h >> 0x10;
      }
      else {
        iVar3 = (int)*p_puck_carrier;
      }
      iVar3 = *(int *)((int)&DAT_000df850 + iVar3 * 0x80 + 2) >> 0x10;
      if ((((((iVar3 == 0x3f9) || (iVar3 == 0x491)) || (iVar3 == 0xdd3)) ||
           ((iVar3 == 0xe2b || (iVar3 == 0x1265)))) || (iVar3 == 0x12dd)) ||
         ((iVar3 == 0x1355 || (iVar3 == 0x138d)))) {
        iVar3 = (int)*p_puck_x - ((int)(&entities)[iVar2 * 0x20] >> 0x10);
        local_28 = (short)iVar3;
        sVar8 = *p_puck_y - (short)((uint)(&unk_df820)[iVar2 * 0x20] >> 0x10);
        iVar3 = approx_distance(iVar3,sVar8);
        sVar8 = direction8((int)local_28,(int)sVar8);
        iVar6 = param_1[1] >> 0x10;
        if (((bVar7) && (((iVar6 < -0x4e && (-0xe8 < iVar6)) && (iVar6 < *p_puck_y)))) ||
           ((((!bVar7 && (0x4e < iVar6)) && (iVar6 < 0xe8)) && (*p_puck_y < iVar6)))) {
          iVar6 = (*param_1 >> 0x10) - ((int)(&entities)[iVar2 * 0x20] >> 0x10);
          local_28 = (short)iVar6;
          sVar9 = (short)((uint)param_1[1] >> 0x10) -
                  (short)((uint)(&unk_df820)[iVar2 * 0x20] >> 0x10);
          iVar2 = approx_distance(iVar6,sVar9);
          sVar9 = direction8((int)local_28,(int)sVar9);
          iVar6 = (int)sVar9;
          if ((*(byte *)(param_1 + 0x11) & 8) == 0) {
            if ((iVar6 != 2) && (iVar6 != 6)) {
              if (*(short *)((int)param_1 + 6) < 0) {
                iVar4 = -(param_1[1] >> 0x10);
              }
              else {
                iVar4 = param_1[1] >> 0x10;
              }
              if (0x7f < iVar4) {
                if (*(short *)((int)param_1 + 2) < 0) {
                  iVar4 = -(*param_1 >> 0x10);
                }
                else {
                  iVar4 = *param_1 >> 0x10;
                }
                if (iVar4 < 0x65) goto LAB_000502a2;
              }
            }
          }
          else {
LAB_000502a2:
            iVar4 = *(int *)((int)param_1 + 0x4f) >> 0x18;
            uVar5 = (iVar4 - (param_1[0xd] >> 0x10)) + 2U & 7;
            uVar1 = (sVar8 - iVar6) + 2U & 7;
            if ((((iVar4 - sVar8) + 1U & 7) < 3) &&
               ((((((*(byte *)(param_1 + 0x11) & 8) != 0 && (uVar5 < 5)) && (uVar1 < 5)) ||
                 ((((*(byte *)(param_1 + 0x11) & 8) == 0 && (uVar5 != 0)) &&
                  ((uVar1 != 0 && ((uVar5 < 4 && (uVar1 < 4)))))))) &&
                ((iVar2 < iVar3 && (iVar2 + (param_1[0x13] >> 0x10) < iVar3 * 2)))))) {
              if ((uVar5 == 2) && (uVar1 == 2)) {
                uVar1 = 10;
              }
              else {
                *(short *)((int)param_1 + 0x4a) = sVar8;
                uVar1 = uVar1 + 1;
              }
              goto LAB_00050333;
            }
          }
        }
      }
    }
  }
LAB_00050331:
  uVar1 = 0;
LAB_00050333:
  return CONCAT44(unaff_EDX,uVar1);
}


// ================================================================================================
// opponent_in_reach @ 0x5033d [__watcall]
// ================================================================================================

undefined8 __watcall opponent_in_reach(int *param_1,undefined4 unaff_EDX)

{
  short sVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  
  __CHK(0x1c);
  if (*(short *)((int)param_1 + 0x6a) < 6) {
    iVar2 = 6;
  }
  else {
    iVar2 = 0;
  }
  piVar6 = &entities + iVar2 * 0x20;
  iVar2 = 0;
  do {
    iVar4 = (*piVar6 >> 0x10) - (*param_1 >> 0x10);
    sVar1 = direction8((int)(short)iVar4,(int)(short)iVar4);
    if ((((int)sVar1 - (param_1[0xd] >> 0x10)) + 2U & 7) < 5) {
      iVar5 = iVar4;
      if (iVar4 < 0) {
        iVar5 = -iVar4;
      }
      if (iVar5 < 0x1e) {
        if (iVar4 < 0) {
          iVar4 = -iVar4;
        }
        if (iVar4 < 0x1e) {
          uVar3 = 1;
          goto LAB_00050336;
        }
      }
    }
    iVar2 = iVar2 + 1;
    piVar6 = piVar6 + 0x20;
    if (5 < iVar2) {
      uVar3 = 0;
LAB_00050336:
      return CONCAT44(unaff_EDX,uVar3);
    }
  } while( true );
}


// ================================================================================================
// hook_button @ 0x503cd [__watcall]
// ================================================================================================

void __watcall
hook_button(int param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  int iVar1;
  
  __CHK(0xc);
  *(byte *)(param_1 + 0x44) = *(byte *)(param_1 + 0x44) | 0x20;
  if (*(short *)(param_1 + 0x18) == 0) {
    iVar1 = opponent_in_reach(param_1);
    if (iVar1 == 1) {
      set_animation(param_1,0x873);
      return;
    }
    iVar1 = try_block_shot(param_1);
    if (iVar1 != 0) {
      start_poke_check(param_1);
      return;
    }
  }
  start_hook(param_1,&entities + (*(int *)(param_1 + 0x12) >> 0x10) * 0x20,param_1,unaff_ECX,
             unaff_EDX,unaff_EBX);
  return;
}


// ================================================================================================
// request_line_change @ 0x50434 [__watcall]
// ================================================================================================

undefined4 __watcall request_line_change(int param_1,int unaff_EDX)

{
  short sVar1;
  int iVar2;
  short sVar3;
  
  __CHK(0x14);
  if (((byte)option_flags & 4) != 0) {
    iVar2 = *(int *)(param_1 + 0x6c);
    sVar1 = *(short *)(*(int *)(param_1 + 0x70) + 0x36);
    sVar3 = *(short *)(iVar2 + 0x36);
    if (((sVar1 == sVar3) || (unaff_EDX < 2)) && ((sVar1 != sVar3 || (unaff_EDX < 4)))) {
      if ((short)(sVar1 - sVar3) < 0) {
        unaff_EDX = unaff_EDX + 4;
      }
      else if (0 < (short)(sVar1 - sVar3)) {
        unaff_EDX = unaff_EDX + 6;
      }
      *(byte *)(param_1 + 0x45) = *(byte *)(param_1 + 0x45) & 0xf7;
      *(byte *)(param_1 + 0x44) = *(byte *)(param_1 + 0x44) | 8;
      *(byte *)(iVar2 + 0x44) = *(byte *)(iVar2 + 0x44) & 0xfd;
      if (*(int *)(iVar2 + 0x28) >> 0x10 != unaff_EDX) {
        *(short *)(iVar2 + 0x2a) = (short)unaff_EDX;
        if (unaff_EDX < 4) {
          sVar1 = *(short *)(iVar2 + 0x2c);
          sVar3 = sVar1 + 1;
          *(short *)(iVar2 + 0x2c) = sVar3;
          if (2 < sVar3) {
            *(short *)(iVar2 + 0x2c) = sVar1 + -2;
          }
        }
        draw_line_indicator((*(byte *)(param_1 + 0x44) & 0x40) != 0,(int)(short)unaff_EDX);
        apply_line_change(iVar2);
      }
      return 1;
    }
  }
  return 0;
}


// ================================================================================================
// control_player @ 0x504da [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall control_player(int param_1,short unaff_DX)

{
  short sVar1;
  uint uVar2;
  int iVar3;
  
  __CHK(0x14);
  uVar2 = (uint)((*(byte *)(param_1 + 0x44) & 0x40) != 0);
  if (((penalty_shot_phase == 0) && (penalty_shot_active == 0)) || ((game_flags & 1) == 0)) {
    if ((((&word_e0304)[uVar2] != 0) && (penalty_shot_active == 0)) &&
       ((user1_team != (short)user2_team || (*(short *)(param_1 + 0x6a) == _user1_slot)))) {
      if ((((game_flags & 1) == 0) || ((*(byte *)(param_1 + 0x45) & 8) != 0)) &&
         (sVar1 = request_line_change(param_1,*(int *)(&unk_e037e + uVar2 * 2) >> 0x10), sVar1 != 0)
         ) {
        (&word_cbc56)[uVar2] = 0;
        (&word_cbc6a)[uVar2] = 0;
      }
      (&word_e0304)[uVar2] = 0;
    }
    if (((byte)stop_flags & 1) != 0) {
      faceoff_control(param_1);
      return;
    }
    if ((*(byte *)(param_1 + 0x45) & 8) != 0) {
      line_change_bench_step(param_1);
      return;
    }
    if (((&unk_dff3a)[dword_dff36 >> 0x10] == '\x1c') && (penalty_shot_phase == 0)) {
      if (((dword_e03be._2_1_ & 0x10) != 0) || ((dword_e03be._2_1_ & 0x20) != 0)) {
        skip_faceoff_wait = 1;
        return;
      }
    }
    else if ((*(byte *)(param_1 + 0x44) & 8) != 0) {
      iVar3 = shot_power >> 0x10;
      if ((*(byte *)(param_1 + 0x44) & 0x20) == 0) {
        sVar1 = *(short *)(param_1 + 0x6a);
        if (*p_puck_carrier == sVar1) {
          pull_goalie_logic(param_1);
          if ((*(short *)(param_1 + 0x1a) == 0) && ((*(byte *)(param_1 + 0x45) & 2) != 0)) {
            return;
          }
          if ((action_flags & 4) != 0) {
            pass_button(param_1);
            return;
          }
          if ((action_flags & 8) != 0) {
            shot_control(param_1);
            return;
          }
          if ((dword_e03be._2_1_ & 0x10) != 0) {
            shoot_button(param_1);
            return;
          }
          if (((dword_e03be._2_1_ & 0x40) != 0) && (penalty_shot_active == 0)) {
            request_line_change_button(param_1);
            return;
          }
          if (*(short *)(param_1 + 0x1a) == 0) {
            return;
          }
          if ((dword_e03be._2_1_ & 0x20) != 0) {
            start_shot(param_1);
            return;
          }
        }
        else {
          if (controls_blocked != 0) {
            return;
          }
          if ((dword_e03be._2_1_ & 0x40) != 0) {
            hook_button(param_1);
            return;
          }
          if ((dword_e03be._2_1_ & 0x10) != 0) {
LAB_00050631:
            switch_to_nearest(param_1,(int)unaff_DX);
            return;
          }
          if (*(short *)(param_1 + 0x1a) == 0) {
            return;
          }
          if (sVar1 == shot_power._2_2_) {
            if ((dword_e03be._2_1_ & 0x20) != 0) {
              body_check(param_1);
            }
            if (one_timer_pending != 0) goto LAB_0005065c;
            if ((dword_e03be._2_1_ & 0x10) != 0) goto LAB_00050631;
            if (controls_blocked != 0) {
              return;
            }
          }
          else {
            if (((((*p_puck_carrier < '\0') && ((dword_e03be._2_1_ & 0x20) != 0)) &&
                 (-1 < shot_power)) &&
                ((shot_power._2_2_ < 6 == sVar1 < 6 && (((&unk_df860)[iVar3 * 0x80] & 8) == 0)))) &&
               (((&unk_df861)[iVar3 * 0x80] & 4) == 0)) goto LAB_000506ed;
            if ((dword_e03be._2_1_ & 0x20) != 0) {
              body_check(param_1);
              return;
            }
          }
        }
        apply_skating(param_1,dword_e03ba >> 0x10);
      }
      else if (((short)*p_puck_carrier != *(short *)(param_1 + 0x6a)) && (controls_blocked == 0)) {
        if ((dword_e03be._2_1_ & 0x10) != 0) goto LAB_00050631;
        sVar1 = *(short *)(param_1 + 0x6a);
        if (shot_power._2_2_ == sVar1) {
          if (one_timer_pending != 0) {
LAB_0005065c:
            pending_dir = dword_e03ba._2_2_ & 0xf;
            return;
          }
        }
        else if ((((*p_puck_carrier < '\0') && ((dword_e03be._2_1_ & 0x20) != 0)) &&
                 (-1 < shot_power)) &&
                (((0 < (short)(&unk_df836)[iVar3 * 0x40] && (shot_power._2_2_ < 6 == sVar1 < 6)) &&
                 ((((&unk_df860)[iVar3 * 0x80] & 8) == 0 && (((&unk_df861)[iVar3 * 0x80] & 4) == 0))
                 )))) {
LAB_000506ed:
          if (sVar1 == _user1_slot) {
            if (*(short *)((int)&DAT_000df884 + iVar3 * 0x80 + 2) != _user1_slot) {
              _user1_slot = find_switch_target((int)(&DAT_000df884)[iVar3 * 0x20] >> 0x10,
                                               (int)_user1_slot);
            }
          }
          else if (*(short *)((int)&DAT_000df884 + iVar3 * 0x80 + 2) != user2_slot) {
            user2_slot = find_switch_target((int)(&DAT_000df884)[iVar3 * 0x20] >> 0x10,
                                            (int)user2_slot);
          }
          one_timer_pending = 1;
          return;
        }
      }
    }
  }
  return;
}


// ================================================================================================
// pick_next_line @ 0x50908 [__watcall]
// ================================================================================================

void __watcall pick_next_line(int param_1)

{
  short sVar1;
  short sVar2;
  short sVar3;
  
  __CHK(0x10);
  sVar1 = *(short *)(*(int *)(param_1 + 0x70) + 0x36);
  sVar2 = *(short *)(*(int *)(param_1 + 0x6c) + 0x36);
  if (sVar1 != sVar2) {
    sVar3 = dword_e03ba._2_2_;
    dword_e03ba = CONCAT22(dword_e03ba._2_2_ + 0x20,(undefined2)dword_e03ba);
    if (0 < (short)(sVar1 - sVar2)) {
      dword_e03ba = CONCAT22(sVar3 + 0x40,(undefined2)dword_e03ba);
    }
  }
  dword_e03be._2_2_ = *(short *)(*(int *)(param_1 + 0x6c) + 0x2a);
  dword_e03ba._2_2_ = dword_e03ba._2_2_ + dword_e03be._2_2_ * 4;
  dword_e03ba = CONCAT22((short)(char)(&unk_ccb5a)[dword_e03ba._2_2_],(undefined2)dword_e03ba);
  return;
}


// ================================================================================================
// cpu_line_change_select @ 0x50975 [__watcall]
// ================================================================================================

void __watcall cpu_line_change_select(int param_1)

{
  short sVar1;
  int iVar2;
  short sVar3;
  int extraout_EDX;
  
  __CHK(0x14);
  iVar2 = *(int *)(param_1 + 0x6c);
  dword_e03ba._2_2_ = dword_e03ac;
  pick_next_line(param_1);
  if (-1 < dword_e03ba._2_2_) {
    *(byte *)(extraout_EDX + 0x45) = *(byte *)(extraout_EDX + 0x45) & 0xf7;
    *(byte *)(extraout_EDX + 0x44) = *(byte *)(extraout_EDX + 0x44) | 8;
    *(byte *)(iVar2 + 0x44) = *(byte *)(iVar2 + 0x44) & 0xfd;
    sVar1 = dword_e03ba._2_2_;
    if (dword_e03ba._2_2_ != *(short *)(iVar2 + 0x2a)) {
      *(short *)(iVar2 + 0x2a) = dword_e03ba._2_2_;
      if (sVar1 < 4) {
        sVar1 = *(short *)(iVar2 + 0x2c);
        sVar3 = sVar1 + 1;
        *(short *)(iVar2 + 0x2c) = sVar3;
        if (2 < sVar3) {
          *(short *)(iVar2 + 0x2c) = sVar1 + -2;
        }
      }
      draw_line_indicator((*(byte *)(extraout_EDX + 0x44) & 0x40) != 0,(int)dword_e03ba._2_2_);
      apply_line_change(iVar2);
    }
  }
  return;
}


// ================================================================================================
// read_control_p1 @ 0x50a05 [__watcall]
// ================================================================================================

undefined8 __watcall read_control_p1(undefined4 param_1,undefined4 unaff_EDX)

{
  ushort uVar1;
  uint uVar2;
  
  __CHK(0x10);
  uVar1 = (ushort)icing_state;
  if (control_entry == (byte *)0x0) {
    dword_e03ba._2_2_ = 8;
  }
  else {
    dword_e03ba._2_2_ = (ushort)*control_entry;
  }
  uVar2 = CONCAT22((short)((uint)param_1 >> 0x10),dword_e03ba._2_2_) & 0xffff0070;
  icing_state._0_2_ = (ushort)uVar2;
  dword_e03ae._2_2_ = (ushort)icing_state;
  dword_e03ac = uVar1 ^ (ushort)icing_state;
  dword_e03be._2_2_ = (ushort)icing_state & (uVar1 ^ (ushort)icing_state);
  return CONCAT44(unaff_EDX,CONCAT22((short)(uVar2 >> 0x10),dword_e03ba._2_2_));
}


// ================================================================================================
// read_control_p2 @ 0x50a84 [__watcall]
// ================================================================================================

undefined8 __watcall read_control_p2(undefined4 param_1,undefined4 unaff_EDX)

{
  ushort uVar1;
  uint uVar2;
  
  __CHK(0x10);
  uVar1 = word_e9abc;
  if (control_entry == 0) {
    dword_e03ba._2_2_ = 8;
  }
  else {
    dword_e03ba._2_2_ = (ushort)*(byte *)(control_entry + 1);
  }
  uVar2 = CONCAT22((short)((uint)param_1 >> 0x10),dword_e03ba._2_2_) & 0xffff0070;
  word_e9abc = (ushort)uVar2;
  dword_e03ae._2_2_ = word_e9abc;
  dword_e03ac = uVar1 ^ word_e9abc;
  dword_e03be._2_2_ = word_e9abc & (uVar1 ^ word_e9abc);
  return CONCAT44(unaff_EDX,CONCAT22((short)(uVar2 >> 0x10),dword_e03ba._2_2_));
}


// ================================================================================================
// center_mouse @ 0x50ade [__watcall]
// ================================================================================================

void __watcall
center_mouse(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  __CHK(0x18);
  setmousepos(0xa0,100,unaff_EDX,unaff_ECX,unaff_EBX);
  return;
}


// ================================================================================================
// pass_completed @ 0x50afe [__watcall]
// ================================================================================================

void __watcall pass_completed(int param_1)

{
  short *psVar1;
  
  __CHK(0xc);
  if (((-1 < shot_power._2_2_) && (shot_power._2_2_ < 6 == *(short *)(param_1 + 0x6a) < 6)) &&
     ((game_flags & 0x10) == 0)) {
    psVar1 = (short *)(*(int *)(param_1 + 0x6c) + 0x28);
    *psVar1 = *psVar1 + 1;
  }
  shot_power._2_2_ = 0xffff;
  return;
}


// ================================================================================================
// one_timer_step @ 0x50b55 [__watcall]
// ================================================================================================

void __watcall one_timer_step(int param_1)

{
  short *psVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  int extraout_EDX;
  undefined4 uVar5;
  
  __CHK(0x18);
  if ((*p_puck_carrier < '\0') && (iVar3 = *(int *)(param_1 + 0x24) >> 0x18, -0x1a < iVar3)) {
    if (one_timer_pending != 0) {
      if ((*(short *)(param_1 + 0x38) == 0xdd3) || (*(short *)(param_1 + 0x38) == 0xe2b)) {
        if (*(short *)(param_1 + 0x3a) < 3) {
          if (((dword_e03be._2_2_ & 0x10) != 0) || ((dword_e03be._2_2_ & 0x40) != 0)) {
            action_flags = action_flags & 0xf7;
            *(byte *)(param_1 + 0x44) = *(byte *)(param_1 + 0x44) | 0x20;
            if (*(short *)(param_1 + 0x38) == 0xdd3) {
              *(undefined2 *)(param_1 + 0x38) = 0x1355;
            }
            else {
              *(undefined2 *)(param_1 + 0x38) = 0x138d;
            }
            one_timer_pending = 0;
          }
        }
        *(undefined2 *)(param_1 + 0x3e) = 5;
        dword_e03ba = CONCAT22(*(undefined2 *)(param_1 + 0x36),(undefined2)dword_e03ba) & 0x7ffff;
        if ((*(byte *)(param_1 + 0x55) & 8) != 0) {
          dword_e03ba = CONCAT22(8 - dword_e03ba._2_2_,(undefined2)dword_e03ba) & 0x7ffff;
        }
        dword_e03be._2_2_ = (ushort)(char)(&unk_ccbbb)[((int)dword_e03ba >> 0x10) * 2];
        sVar2 = (short)(char)(&onetimer_offsets)[((int)dword_e03ba >> 0x10) * 2];
        if ((*(byte *)(param_1 + 0x55) & 8) != 0) {
          sVar2 = -sVar2;
        }
        dword_e03ba = CONCAT22(sVar2,(undefined2)dword_e03ba);
        iVar4 = (int)(short)((*(short *)(param_1 + 2) + sVar2) - *p_puck_x);
        iVar3 = (int)(short)((dword_e03be._2_2_ + *(short *)(param_1 + 6)) - *p_puck_y);
        iVar3 = iVar4 * iVar4 + iVar3 * iVar3;
        if (((*(short *)(param_1 + 0x3a) == 0) &&
            ((*(int *)(param_1 + 0x24) >> 0x18 < -4 || (iVar3 < 400)))) ||
           ((*(short *)(param_1 + 0x3a) == 2 && (iVar3 < 0x100)))) {
          *(undefined2 *)(param_1 + 0x3c) = 0;
          advance_animation(param_1);
          iVar3 = extraout_EDX;
        }
        if ((iVar3 < 0x65) || ((iVar3 < 0x91 && (*(int *)(param_1 + 0x24) >> 0x18 < -10)))) {
          if (8 < pending_dir) {
            pending_dir = 8;
          }
          shot_power._0_2_ = *(byte *)(param_1 + 0x5b) / 2 + 0x1e;
          *(undefined2 *)(param_1 + 0x3a) = 4;
          *(undefined2 *)(param_1 + 0x3c) = 4;
          *(undefined *)(param_1 + 0x46) = 0;
          advance_animation(param_1);
          psVar1 = (short *)(*(int *)(param_1 + 0x6c) + 0x18);
          *psVar1 = *psVar1 + 1;
          crowd_noise._2_2_ = crowd_noise._2_2_ + 100;
          update_carrier(param_1);
          do_shot(param_1);
          pass_completed(param_1);
          *(byte *)(param_1 + 0x44) = *(byte *)(param_1 + 0x44) & 0xfe;
          ai_default_skate(param_1);
          one_timer_pending = 0;
        }
      }
      else if (((*(char *)(param_1 + 0x27) < '\x17') && (-0xb < iVar3)) &&
              (((*(byte *)(param_1 + 0x44) & 8) != 0 ||
               ((((*(byte *)(param_1 + 0x44) & 0x80) == 0 || (0x45 < *(short *)(param_1 + 6))) &&
                (((*(byte *)(param_1 + 0x44) & 0x80) != 0 || (*(int *)(param_1 + 4) >> 0x10 < -0x45)
                 ))))))) {
        psVar1 = (short *)(*(int *)(param_1 + 0x6c) + 0x16);
        *psVar1 = *psVar1 + 1;
        iVar3 = (int)(short)((*(char *)(param_1 + 0x27) + 10) * 0x10);
        if ((*(byte *)(param_1 + 0x44) & 0x80) == 0) {
          sVar2 = -0xe8;
        }
        else {
          sVar2 = 0xe8;
        }
        sVar2 = direction8((int)(short)-((short)((uint)(*(short *)p_puck_vx * iVar3) >> 0x10) +
                                        *p_puck_x),
                           (int)(short)(sVar2 - ((short)((uint)(iVar3 * *(short *)p_puck_vy) >> 0x10
                                                        ) + *p_puck_y)));
        sVar2 = shot_is_backhand(param_1,(int)sVar2);
        if (sVar2 == 0) {
          uVar5 = 0xdd3;
        }
        else {
          uVar5 = 0xe2b;
        }
        set_animation(param_1,uVar5);
      }
    }
  }
  else {
    if ((short)*p_puck_carrier == *(short *)(param_1 + 0x6a)) {
      pass_completed(param_1);
    }
    shot_power._2_2_ = 0xffff;
    *(byte *)(param_1 + 0x44) = *(byte *)(param_1 + 0x44) & 0xfe;
    ai_default_skate(param_1);
    one_timer_pending = 0;
  }
  return;
}


// ================================================================================================
// one_timer_chance @ 0x50e5c [__watcall]
// ================================================================================================

longlong __watcall one_timer_chance(uint *param_1,uint unaff_EDX)

{
  short sVar1;
  int iVar2;
  uint *puVar3;
  undefined2 uVar4;
  
  __CHK(0x10);
  if (*(short *)((int)param_1 + 6) < 0) {
    iVar2 = -((int)param_1[1] >> 0x10);
  }
  else {
    iVar2 = (int)param_1[1] >> 0x10;
  }
  if ((((0x4e < iVar2) && (iVar2 < 0xde)) &&
      (*(short *)((int)param_1 + 6) < 0 != ((*(byte *)(param_1 + 0x11) & 0x80) != 0))) &&
     (-1 < *(short *)(param_1[0x1c] + 0x38))) {
    if (*(short *)((int)param_1 + 0x6a) < 6) {
      iVar2 = 6;
    }
    else {
      iVar2 = 0;
    }
    puVar3 = &entities + iVar2 * 0x20;
    iVar2 = 0;
    do {
      if (*(short *)((int)puVar3 + 0x1a) == 0) break;
      iVar2 = iVar2 + 1;
      puVar3 = puVar3 + 0x20;
    } while (iVar2 < 6);
    uVar4 = 3;
    iVar2 = (int)*puVar3 >> 0x10;
    if ((int)(*param_1 ^ *puVar3) >> 0x10 != 0) {
      if (*(short *)((int)puVar3 + 2) < 0) {
        iVar2 = -iVar2;
      }
      if (0xc < iVar2) goto LAB_00050f19;
      if (6 < iVar2) {
        uVar4 = 2;
      }
    }
    sVar1 = randomrange(uVar4);
    if (sVar1 == 0) {
LAB_00050f19:
      return CONCAT44(unaff_EDX,1);
    }
  }
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// ai_pass_receiver @ 0x50f3f [__watcall]
// ================================================================================================

void __watcall ai_pass_receiver(int param_1)

{
  byte bVar1;
  short sVar2;
  int iVar3;
  undefined4 extraout_EDX;
  int extraout_EDX_00;
  int extraout_EDX_01;
  undefined8 uVar4;
  
  __CHK(0x18);
  if ((*(byte *)(param_1 + 0x44) & 0x20) == 0) {
    if ((game_flags & 1) == 0) {
      *(char *)(param_1 + 0x27) = *(char *)(param_1 + 0x27) + -1;
      bVar1 = *(byte *)(param_1 + 0x44);
      if ((bVar1 & 8) == 0) {
        if ((bVar1 & 2) != 0) {
          *(byte *)(param_1 + 0x44) = bVar1 & 0xfc | 1;
          *(undefined2 *)(param_1 + 0x28) = 8;
          dword_e03ba._2_2_ = ((*(byte *)(param_1 + 0x44) & 0x40) != 0) + 1;
          if (((*p_puck_carrier < '\0') && (user1_team != dword_e03ba._2_2_)) &&
             (dword_e03ba._2_2_ != (short)user2_team)) {
            uVar4 = one_timer_chance(param_1);
            param_1 = (int)((ulonglong)uVar4 >> 0x20);
            if ((int)uVar4 != 0) {
              one_timer_pending = 1;
            }
          }
        }
        if (one_timer_pending == 0) {
          if (*p_puck_carrier < '\0') {
            sVar2 = *(short *)p_puck_vx;
            if (sVar2 < 0) {
              iVar3 = -(int)sVar2;
            }
            else {
              iVar3 = (int)sVar2;
            }
            if (iVar3 < 0x168) {
              sVar2 = *(short *)p_puck_vy;
              if (sVar2 < 0) {
                iVar3 = -(int)sVar2;
              }
              else {
                iVar3 = (int)sVar2;
              }
              if (iVar3 < 0x168) {
                ai_chase_puck(param_1);
                param_1 = extraout_EDX_00;
              }
            }
            if (-6 < *(int *)(param_1 + 0x24) >> 0x18) {
              return;
            }
          }
          *(byte *)(param_1 + 0x44) = *(byte *)(param_1 + 0x44) & 0xfe;
          ai_default_skate(param_1);
          one_timer_pending = 0;
          if ((short)*p_puck_carrier == *(short *)(extraout_EDX_01 + 0x6a)) {
            pass_completed(extraout_EDX_01);
            return;
          }
          if (*p_puck_carrier < '\0') {
            one_timer_pending = 0;
            return;
          }
          shot_power._2_2_ = 0xffff;
          one_timer_pending = 0;
          return;
        }
        dword_e03be._2_1_ = dword_e03be._2_1_ & 0xaf;
      }
      one_timer_step(param_1);
    }
    else {
      one_timer_pending = 0;
      ai_default_skate(param_1);
      skate_idle(extraout_EDX);
    }
  }
  return;
}


// ================================================================================================
// sub_510a9 @ 0x510a9 [__watcall]
// ================================================================================================

void __watcall sub_510a9(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  __CHK(0x14);
  iVar5 = 0xdf614;
  for (iVar4 = 0; iVar4 < 2; iVar4 = iVar4 + 1) {
    iVar2 = 6;
    for (iVar3 = 0x1b; -1 < iVar3; iVar3 = iVar3 + -1) {
      if ((0 < *(short *)(iVar5 + 0x7e + iVar3 * 2)) && (4 < iVar2)) {
        iVar2 = iVar2 + -1;
        iVar1 = iVar4 * 6 + iVar2;
        (&unk_df836)[iVar1 * 0x40] = 0xffff;
        *(undefined2 *)((int)&unk_df848 + iVar1 * 0x80 + 2) = 0xff9c;
      }
    }
    *(short *)(iVar5 + 0x36) = (short)iVar2;
    iVar5 = 0xdf714;
  }
  return;
}


// ================================================================================================
// sub_51115 @ 0x51115 [__watcall]
// ================================================================================================

void __watcall sub_51115(int param_1)

{
  int iVar1;
  short sVar2;
  int iVar3;
  undefined2 uStackY_1e;
  
  __CHK(0x20);
  sVar2 = 0;
  while( true ) {
    if (0x18 < sVar2) {
      return;
    }
    iVar3 = (int)(uint)CONCAT12((*(byte *)(param_1 + 0x44) & 0x40) != 0,uStackY_1e) >> 0x10;
    iVar1 = iVar3 * 0x444 + sVar2 * 0x27;
    if ((&rosters)[iVar1] == '\a') break;
    sVar2 = sVar2 + 1;
  }
  *(undefined2 *)(param_1 + 0x36) = 4;
  set_animation(param_1,0x7bf);
  *(byte *)(param_1 + 0x44) = *(byte *)(param_1 + 0x44) | 0x20;
  *(undefined2 *)(param_1 + 0x26) = 0x5a;
  *(short *)(param_1 + 0x2e) = sVar2;
  (&rosters)[iVar1] = 3;
  (&unk_df692)[iVar3 * 0x80 + (int)sVar2] = 0xfffe;
  return;
}


// ================================================================================================
// send_team_to_faceoff @ 0x511b4 [__watcall]
// ================================================================================================

void __watcall
send_team_to_faceoff(short param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  int iVar1;
  undefined4 *puVar2;
  
  __CHK(0x10);
  if (penalty_shot_phase == 0) {
    puVar2 = &entities + param_1 * 0xc0;
    iVar1 = 0;
    do {
      if ((penalty_shot_setup == 0) ||
         (*(char *)((int)puVar2 + (*(int *)((int)puVar2 + 0x1a) >> 0x10) + 0x1e) != '-')) {
        if (((-1 < *(short *)((int)puVar2 + 0x1a)) &&
            (((*(int *)((int)puVar2 + 0x3f) >> 0x18 == -1 && ((int)puVar2[0x10] >> 0x18 == -1)) &&
             ((int)puVar2[0xb] >> 0x10 != -100)))) &&
           (*(char *)((int)puVar2 + (*(int *)((int)puVar2 + 0x1a) >> 0x10) + 0x1e) != '\'')) {
          set_state_reset(puVar2,0x27,puVar2,iVar1,unaff_EDX,unaff_ECX,unaff_EBX);
        }
      }
      else {
        *(undefined2 *)((int)puVar2 + 0x2e) = 0;
        set_state(puVar2,0x29);
      }
      iVar1 = iVar1 + 1;
      puVar2 = puVar2 + 0x20;
    } while (iVar1 < 6);
  }
  return;
}


// ================================================================================================
// dress_line_if_start @ 0x5125f [__watcall]
// ================================================================================================

void __watcall dress_line_if_start(short param_1)

{
  __CHK(8);
  if ((((dword_cc0ec == 0) && (period_idx == 0)) && (clock_seconds == dword_e9ab6._2_2_)) &&
     (clock_sub == 0)) {
    dress_line(param_1 * 0x100 + 0xdf614);
  }
  return;
}


// ================================================================================================
// all_goto_positions @ 0x512a7 [__watcall]
// ================================================================================================

void __watcall all_goto_positions(void)

{
  char cVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  
  __CHK(0x14);
  puVar5 = &entities;
  if (penalty_shot_phase == 0) {
    iVar3 = 0;
    do {
      if (penalty_shot_setup == 0) {
        if (*(short *)((int)puVar5 + 0x1a) < 1) {
          if ((*(short *)((int)puVar5 + 0x1a) == 0) &&
             (*(undefined2 *)((int)puVar5 + 0x2e) = 0,
             *(int *)((int)puVar5 + (*(int *)((int)puVar5 + 0x1a) >> 0x10) + 0x1b) >> 0x18 != 0x29))
          {
            cVar1 = '\'';
            goto LAB_00051424;
          }
        }
        else {
          *(undefined2 *)((int)puVar5 + 0x2e) = 0;
          iVar2 = *(int *)((int)puVar5 + (*(int *)((int)puVar5 + 0x1a) >> 0x10) + 0x1b) >> 0x18;
          if ((iVar2 != 0x29) && (iVar2 != 0x1d)) {
            cVar1 = (((byte)option_flags & 4) != 0) + '\'';
            goto LAB_00051424;
          }
        }
      }
      else {
        cVar1 = *(char *)((int)puVar5 + (*(int *)((int)puVar5 + 0x1a) >> 0x10) + 0x1e);
        if (cVar1 == '-') {
          if (((byte)option_flags & 4) != 0) goto LAB_0005142b;
          set_state_reset(puVar5,0x27);
          cVar1 = '\t';
        }
        else if (*(short *)((int)puVar5 + 0x1a) < 1) {
          if ((*(short *)((int)puVar5 + 0x1a) != 0) || (cVar1 == ')')) goto LAB_0005142b;
          cVar1 = '\'';
        }
        else {
          *(undefined *)((int)puVar5 + 0x42) = 0xff;
          *(undefined *)((int)puVar5 + 0x43) = *(undefined *)((int)puVar5 + 0x42);
          cVar1 = '(';
        }
LAB_00051424:
        set_state_reset(puVar5,cVar1);
      }
LAB_0005142b:
      iVar3 = iVar3 + 1;
      puVar5 = puVar5 + 0x20;
      if (0xb < iVar3) {
        return;
      }
    } while( true );
  }
  iVar3 = 0;
  do {
    if (0 < *(short *)((int)puVar5 + 0x1a)) {
      *(undefined2 *)((int)puVar5 + 0x2e) = 0;
      if (iVar3 == penalty_shot_slot) {
        uVar4 = 0x27;
      }
      else {
        iVar2 = *(int *)((int)puVar5 + (*(int *)((int)puVar5 + 0x1a) >> 0x10) + 0x1b) >> 0x18;
        if ((iVar2 == 0x29) || (iVar2 == 0x1d)) goto LAB_00051308;
        uVar4 = 0x2d;
      }
      set_state_reset(puVar5,uVar4);
    }
LAB_00051308:
    if (*(short *)((int)puVar5 + 0x1a) == 0) {
      *(undefined2 *)((int)puVar5 + 0x2e) = 0;
      if (((*(byte *)(puVar5 + 0x11) & 0x40) != 0) == penalty_shot_team) {
        uVar4 = 0x2d;
      }
      else {
        *(undefined *)((int)puVar5 + 0x43) = 0xff;
        *(undefined *)((int)puVar5 + 0x42) = 0xff;
        uVar4 = 0x27;
      }
      set_state_reset(puVar5,uVar4);
    }
    iVar3 = iVar3 + 1;
    puVar5 = puVar5 + 0x20;
    if (0xb < iVar3) {
      return;
    }
  } while( true );
}


// ================================================================================================
// all_players_arrived @ 0x51440 [__watcall]
// ================================================================================================

longlong __watcall all_players_arrived(undefined4 param_1,uint unaff_EDX)

{
  undefined4 *puVar1;
  int iVar2;
  
  __CHK(0xc);
  puVar1 = &entities;
  iVar2 = 0;
  while ((*(short *)((int)puVar1 + 0x1a) < 0 || ((int)puVar1[0xb] >> 0x10 == -100))) {
    iVar2 = iVar2 + 1;
    puVar1 = puVar1 + 0x20;
    if (0xb < iVar2) {
      return CONCAT44(unaff_EDX,1);
    }
  }
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// ai_bench_wait @ 0x5147d [__watcall]
// ================================================================================================

void __watcall ai_bench_wait(int param_1)

{
  short sVar1;
  undefined2 uVar2;
  int iVar3;
  int iVar4;
  
  __CHK(0x14);
  if (((*(byte *)(param_1 + 0x44) & 0x20) == 0) && (sVar1 = handle_line_change(param_1), sVar1 == 0)
     ) {
    if ((*(byte *)(param_1 + 0x44) & 2) != 0) {
      *(byte *)(param_1 + 0x44) = *(byte *)(param_1 + 0x44) & 0xfd;
      *(undefined2 *)(param_1 + 0x28) = 8;
      if ((*(byte *)(param_1 + 0x44) & 0x40) == 0) {
        uVar2 = 0xffce;
      }
      else {
        uVar2 = 0x41;
      }
      *(undefined2 *)(param_1 + 0x2c) = uVar2;
      sVar1 = randomrange(4);
      *(short *)(param_1 + 0x2c) = *(short *)(param_1 + 0x2c) + (2 - sVar1) * 0xf;
      *(undefined2 *)(param_1 + 0x2a) = 0xff58;
      *(undefined2 *)(param_1 + 0x26) = 0;
      *(undefined2 *)(param_1 + 0x2e) = 0;
    }
    sVar1 = *(short *)(param_1 + 0x26);
    if (sVar1 == 0x5a) {
      set_state_reset(param_1,0x28);
      put_player_on_ice(param_1,*(int *)(param_1 + 0x2c) >> 0x10);
      *(undefined2 *)(param_1 + 0x12) = 0xffff;
      *(undefined2 *)(param_1 + 0x2e) = 0;
      *(undefined2 *)(param_1 + 0x26) = 0;
      return;
    }
    if (sVar1 == 100) {
      if (((0 < *(short *)(param_1 + 0x1a)) && (*(short *)(param_1 + 0x36) == 6)) &&
         (iVar3 = *(int *)(*(int *)(param_1 + 0x6c) + 0x44 + (*(int *)(param_1 + 0x44) >> 0x18) * 2)
         , iVar4 = iVar3 >> 0x1f,
         sVar1 = randomrange((int)(short)((short)((int)(((iVar3 >> 0x10) + iVar4 * -0x20) -
                                                       (uint)(iVar4 << 4 < 0)) >> 5) + 0x50)),
         sVar1 == 0)) {
        set_animation(param_1,0xd97);
        *(byte *)(param_1 + 0x44) = *(byte *)(param_1 + 0x44) | 0x20;
        return;
      }
      if (*(short *)(param_1 + 0x38) == 0) {
        set_animation(param_1,0x289);
      }
    }
    else {
      *(short *)(param_1 + 0x26) = sVar1 + -1;
      if ((short)(sVar1 + -1) < 0) {
        *(short *)(param_1 + 0x26) = sVar1 + 7;
        if ((*(byte *)(param_1 + 0x44) & 0x40) == 0) {
          sVar1 = -0x32;
        }
        else {
          sVar1 = 0x46;
        }
        sVar1 = (short)((uint)*(undefined4 *)(param_1 + 4) >> 0x10) - sVar1;
        dword_e03ba._2_2_ = *(short *)(param_1 + 2) - *(short *)(param_1 + 0x2a);
        if (sVar1 < 0) {
          iVar3 = -(int)sVar1;
        }
        else {
          iVar3 = (int)sVar1;
        }
        if ((iVar3 < 0x27) && (dword_e03ba._2_2_ < 0x20)) {
          if (*(short *)(param_1 + 0x1a) == 0) {
            uVar2 = 1;
          }
          else {
            uVar2 = 0x289;
          }
          dword_e03be = CONCAT22(uVar2,(undefined2)dword_e03be);
          set_animation(param_1,uVar2);
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
                 (short)((uint)*(undefined4 *)(param_1 + 0x34) >> 0x10) + sVar1 & 7;
          }
          *(undefined2 *)(param_1 + 0xe) = 0;
          *(undefined2 *)(param_1 + 0xc) = 0xf800;
          if (0x10 < dword_e03ba._2_2_) {
            return;
          }
          *(undefined2 *)(param_1 + 0xc) = 0;
          if (*(short *)(param_1 + 0x36) != 6) {
            return;
          }
          *(undefined2 *)(param_1 + 0x26) = 100;
          set_animation(param_1,0x289);
          sub_51115(param_1);
          return;
        }
      }
      if ((*(byte *)(param_1 + 0x44) & 4) == 0) {
        dword_e03ba._2_2_ = *(undefined2 *)(param_1 + 0x2a);
        dword_e03be = CONCAT22(*(undefined2 *)(param_1 + 0x2c),(undefined2)dword_e03be);
        ai_skate_towards(param_1,0);
        return;
      }
    }
  }
  return;
}


// ================================================================================================
// ai_puck_faceoff @ 0x516e1 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall ai_puck_faceoff(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  char extraout_DL;
  char cVar4;
  int iVar5;
  int *piVar6;
  undefined4 local_28;
  int local_24;
  int local_20;
  
  __CHK(0x28);
  local_24 = param_1 + 0x26;
  local_20 = param_1 + 0x28;
  piVar6 = &local_24;
  if ((*(byte *)(param_1 + 0x44) & 2) != 0) {
    if (*p_puck_carrier != '\x10') {
      if (((-1 < *p_puck_carrier) && (penalty_shot_setup != 0)) &&
         ((&unk_df836)[*p_puck_carrier * 0x40] == 0)) {
        (&unk_df85a)[*p_puck_carrier * 0x40] = 0x78;
        *(undefined2 *)p_puck_vy = 0;
        *(undefined2 *)p_puck_vx = 0;
      }
      *p_puck_carrier = -1;
    }
    *(byte *)(param_1 + 0x44) = *(byte *)(param_1 + 0x44) & 0xfd;
    if (((clock_seconds == 0) && (clock_sub == 0)) || ((game_flags & 0x40) != 0)) {
      local_28 = 0x51781;
      end_period_flag();
      return;
    }
    if ((period_idx == 3) && (dword_df622._2_2_ != dword_df722._2_2_)) {
      local_28 = 0x517a4;
      setup_faceoff();
      return;
    }
    if ((game_flags & 8) != 0) {
      local_28 = 0x517b9;
      start_stoppage(0);
      return;
    }
    if (penalty_shot_phase != 0) {
      *(undefined *)(param_1 + 0x27) = 0xff;
      *(undefined *)(param_1 + 0x29) = 0xff;
      local_28 = 0x517d9;
      apply_line_change(0xdf714);
      local_28 = 0x517e3;
      send_team_to_faceoff(1);
      word_cbc58 = 0;
      word_cbc54 = 0;
      word_cbc6c = 0;
      local_28 = 0x51804;
      apply_line_change(0xdf614);
      local_28 = 0x5180b;
      send_team_to_faceoff(0);
      word_cbc56 = 0;
      word_cbc52 = 0;
      word_cbc6a = 0;
      piVar6 = &local_24;
      goto LAB_00051bc1;
    }
    if (penalty_shot_setup != 0) {
      if ((_user1_slot < 0) && (user1_team != 0)) {
        if (user1_team == 1) {
          puVar2 = &entities;
        }
        else {
          puVar2 = &unk_dfb1c;
        }
        for (cVar4 = '\0'; cVar4 < '\x06'; cVar4 = cVar4 + '\x01') {
          if ((-1 < *(short *)((int)puVar2 + 0x1a)) &&
             (user2_slot != *(short *)((int)puVar2 + 0x6a))) {
            if (*(short *)((int)puVar2 + 0x6a) != _user1_slot) {
              local_28 = 0x51896;
              _user1_slot = find_switch_target((int)puVar2[0x1a] >> 0x10,(int)_user1_slot);
            }
            break;
          }
          puVar2 = puVar2 + 0x20;
        }
      }
      if ((user2_slot < 0) && ((short)user2_team != 0)) {
        if ((short)user2_team == 1) {
          puVar2 = &entities;
        }
        else {
          puVar2 = &unk_dfb1c;
        }
        for (cVar4 = '\0'; cVar4 < '\x06'; cVar4 = cVar4 + '\x01') {
          if ((-1 < *(short *)((int)puVar2 + 0x1a)) &&
             (_user1_slot != *(short *)((int)puVar2 + 0x6a))) {
            if (*(short *)((int)puVar2 + 0x6a) != user2_slot) {
              local_28 = 0x5190d;
              user2_slot = find_switch_target((int)puVar2[0x1a] >> 0x10,(int)user2_slot);
            }
            break;
          }
          puVar2 = puVar2 + 0x20;
        }
      }
    }
    local_28 = 0x51926;
    cpu_pull_goalie_check();
    if (((byte)option_flags & 4) == 0) {
      local_28 = 0x51939;
      apply_line_change(0xdf614);
      local_28 = 0x51943;
      apply_line_change(0xdf714);
    }
    *(undefined *)(param_1 + 0x27) = 0xff;
    *(undefined *)(param_1 + 0x29) = 0xff;
    piVar6 = &local_24;
    if (((byte)option_flags & 4) != 0) {
      byte_df658 = byte_df658 & 0xfd;
      byte_df758 = byte_df758 & 0xfd;
      puVar2 = &entities;
      for (cVar4 = '\0'; cVar4 < '\f'; cVar4 = cVar4 + '\x01') {
        *(byte *)((int)puVar2 + 0x45) = *(byte *)((int)puVar2 + 0x45) & 0xf7;
        puVar2 = puVar2 + 0x20;
      }
      piVar6 = &local_24;
      if (((int)(CONCAT22(user1_team,user2_slot) | CONCAT22((short)user2_team,user1_team)) >> 0x10
           != 0) && (piVar6 = &local_24, penalty_box_mode != 0)) {
        action_flags = action_flags | 0x40;
        piVar6 = &local_28;
        local_28 = 0x519aa;
        sort_draw_order();
        penalty_box_mode = 0;
      }
      dword_e03ba._2_2_ = _user1_slot;
      if (-1 < _user1_slot) {
        *(undefined4 *)((int)piVar6 + -4) = 0x519dc;
        user_line_change_prompt(param_1,&entities + _user1_slot * 0x20);
      }
      dword_e03ba._2_2_ = user2_slot;
      if ((-1 < user2_slot) && ((short)user2_team != user1_team)) {
        *(undefined4 *)((int)piVar6 + -4) = 0x51a15;
        user_line_change_prompt(param_1,&entities + user2_slot * 0x20);
      }
      dword_e03ba._2_2_ = 2;
      dword_e03be._0_2_ = 0;
      if (((((byte)option_flags & 4) != 0) && (user1_team != 2)) && ((short)user2_team != 2)) {
        *(undefined4 *)((int)piVar6 + -4) = 0x51a4f;
        choose_line(0xdf614,0xdf714);
        *(undefined4 *)((int)piVar6 + -4) = 0x51a59;
        apply_line_change(0xdf714);
        *(undefined4 *)((int)piVar6 + -4) = 0x51a63;
        send_team_to_faceoff(1);
      }
    }
  }
  cVar4 = '\0';
  do {
    iVar5 = (int)cVar4;
    iVar3 = iVar5 * 4;
    if (-1 < **(short **)((int)piVar6 + iVar3)) {
      dword_e03be._2_2_ = (*(short **)((int)piVar6 + iVar3))[2];
      *(int *)((int)piVar6 + 8) = iVar5 << 8;
      iVar1 = *(int *)((int)piVar6 + 8);
      if (((&unk_df861)[dword_e03be._2_2_ * 0x80] & 8) == 0) {
        *(undefined *)(*(int *)((int)piVar6 + iVar3) + 1) = 0xff;
        (&word_cbc56)[iVar5] = 0;
        (&word_cbc6a)[iVar5] = 0;
      }
      else {
        **(short **)((int)piVar6 + iVar3) = **(short **)((int)piVar6 + iVar3) + -1;
        if ((-1 < **(short **)((int)piVar6 + iVar3)) ||
           (((&unk_df861)[dword_e03be._2_2_ * 0x80] & 8) == 0)) goto LAB_00051b1e;
        dword_e03ac = 0;
        *(undefined4 *)((int)piVar6 + -4) = 0x51afb;
        cpu_line_change_select();
        (&word_cbc56)[iVar5] = 0;
        (&word_cbc6a)[iVar5] = 0;
      }
      *(undefined4 *)((int)piVar6 + -4) = 0x51b10;
      apply_line_change(iVar1 + 0xdf614);
      *(undefined4 *)((int)piVar6 + -4) = 0x51b17;
      send_team_to_faceoff(iVar5);
      *(undefined4 *)((int)piVar6 + -4) = 0x51b1e;
      dress_line_if_start(iVar5);
      cVar4 = extraout_DL;
    }
LAB_00051b1e:
    cVar4 = cVar4 + '\x01';
  } while (cVar4 != '\x02');
  if (-1 < *(short *)(param_1 + 0x26)) {
    return;
  }
  if (-1 < *(short *)(param_1 + 0x28)) {
    return;
  }
  dword_e03ba._2_2_ = 1;
  if (((((byte)option_flags & 4) != 0) && (user1_team != 1)) && ((short)user2_team != 1)) {
    *(undefined4 *)((int)piVar6 + -4) = 0x51b74;
    choose_line(0xdf714,0xdf614);
    *(undefined4 *)((int)piVar6 + -4) = 0x51b7e;
    apply_line_change(0xdf614);
    *(undefined4 *)((int)piVar6 + -4) = 0x51b85;
    send_team_to_faceoff(0);
  }
  if (((byte)option_flags & 4) == 0) {
    word_df740 = 0;
    dword_df73c._2_2_ = 0;
    word_df640 = 0;
    _word_df63e = 0;
    *(undefined4 *)((int)piVar6 + -4) = 0x51bb5;
    draw_line_indicator(0,0);
    *(undefined4 *)((int)piVar6 + -4) = 0x51bc1;
    draw_line_indicator(1,0);
  }
LAB_00051bc1:
  *(undefined4 *)((int)piVar6 + -4) = 0x51bcd;
  set_state(param_1,0x1c);
  *(undefined2 *)(param_1 + 0x2e) = 1000;
  return;
}


// ================================================================================================
// ai_puck_faceoff2 @ 0x51bdb [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall ai_puck_faceoff2(int param_1)

{
  short sVar1;
  short sVar2;
  undefined2 uVar3;
  int iVar4;
  byte extraout_DL;
  uint uVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  undefined4 uStackY_1c;
  
  __CHK(0x20);
  if ((*(byte *)(param_1 + 0x44) & 2) == 0) {
    sVar1 = *(short *)(param_1 + 0x26) + -1;
    *(short *)(param_1 + 0x26) = sVar1;
    if (sVar1 < 0) {
      uStackY_1c = 0x526e8;
      faceoff_resolve(param_1);
      return;
    }
    if (sVar1 == 0x11) {
      uStackY_1c = 0x526a7;
      set_animation(&referee,0xc43);
    }
    if (*(short *)(param_1 + 0x26) == 0) {
      return;
    }
    sVar1 = (short)((*(int *)(param_1 + 0x24) >> 0x10) + 6 >> 3);
    dword_e03ba = CONCAT22(sVar1,(undefined2)dword_e03ba);
    if (2 < sVar1) {
      return;
    }
    faceoff_countdown_digit = 10 - sVar1;
    return;
  }
  sVar1 = *(short *)(param_1 + 0x2e) + -1;
  *(short *)(param_1 + 0x2e) = sVar1;
  if (((((0 < sVar1) && (dword_cc0ec == 0)) && (skip_faceoff_wait == 0)) && (dword_cbec6 == 0)) &&
     (((period_idx != 0 || (clock_sub != 0)) || (clock_seconds != dword_e9ab6._2_2_)))) {
    if (-1 < ref_phase) {
      return;
    }
    if (-1 < dword_cbebe._2_2_) {
      return;
    }
    uStackY_1c = 0x51c69;
    iVar4 = all_players_arrived();
    if (iVar4 == 0) {
      return;
    }
  }
  *(byte *)(param_1 + 0x44) = *(byte *)(param_1 + 0x44) & 0xfd;
  if ((skip_faceoff_wait != 0) && (dword_cbeca >> 0x10 != -1)) {
    uStackY_1c = dword_e0244;
    freemem();
  }
  penalty_shot_setup = 0;
  dword_e9a9e = CONCAT22(input_enabled,(undefined2)dword_e9a9e);
  _input_enabled = 0;
  uStackY_1c = 0x51cb9;
  sub_61b85();
  _input_enabled = dword_e9a9e >> 0x10;
  _word_cbec8 = 0xffff;
  word_cbece = 0xffff;
  dword_cbebe._2_2_ = 0xffff;
  dword_cbeca = 0xffff0000;
  byte_e0344 = 0;
  byte_e0308 = 0;
  byte_e028c = 0;
  byte_e0250 = 0;
  byte_e02c8 = 0;
  if ((((dword_cc0ec == 0) && (period_idx == 0)) && (clock_seconds == dword_e9ab6._2_2_)) &&
     ((clock_sub == 0 && (skip_faceoff_wait == 0)))) {
    word_cbec4 = 0;
  }
  else if ((dword_cc0ec == 0) && ((skip_faceoff_wait == 0 && (dword_cbec6 == 0)))) {
    word_cbec4 = dword_cbec6;
  }
  else {
    word_cbec4 = 1;
  }
  ref_phase = 0xffff;
  skip_faceoff_wait = 0;
  dword_cbec6 = 0;
  action_flags = action_flags & 0xfe;
  misc_flags = misc_flags & 0xfe;
  icing_state._2_1_ = 0;
  whistle_timer = 0;
  word_df816._1_1_ = 0xff;
  word_df81a._1_1_ = 0xff;
  stop_flags._0_1_ = (byte)stop_flags & 0x78 | 5;
  shot_power._2_2_ = 0xffff;
  puVar8 = &uStackY_1c;
  uStackY_1c = 0x51dfd;
  sort_draw_order();
  penalty_box_mode = (ushort)extraout_DL;
  _camera_target_x = (short)faceoff_spot;
  camera_target_y._0_2_ = faceoff_spot._2_2_;
  if ((short)faceoff_spot < 0) {
    iVar4 = -(int)(short)faceoff_spot;
  }
  else {
    iVar4 = (int)(short)faceoff_spot;
  }
  if (0x20 < iVar4) {
    if ((short)faceoff_spot < 1) {
      _camera_target_x = -0x20;
    }
    else {
      _camera_target_x = 0x20;
    }
  }
  if (faceoff_spot._2_2_ < -0xbb) {
    camera_target_y._0_2_ = -0xbc;
  }
  else if (0xeb < faceoff_spot._2_2_) {
    camera_target_y._0_2_ = 0xec;
  }
  camera._0_2_ = _camera_target_x;
  camera._2_2_ = (short)camera_target_y;
  camera_target_y._2_2_ = 0;
  *p_puck_x = (short)faceoff_spot;
  *p_puck_y = faceoff_spot._2_2_;
  if (penalty_shot_phase == 0) {
    *p_puck_z = 0xff9c;
  }
  else {
    *p_puck_z = 0;
  }
  *(undefined2 *)p_puck_vx = 0;
  *(undefined2 *)p_puck_vy = 0;
  *(undefined2 *)p_puck_vz = 0;
  *p_puck_carrier = 0xff;
  word_dfe28 = 0;
  word_dfe2a = 0;
  word_dfe1e = 0;
  word_dfe22 = 0xec;
  DAT_000dfea8 = 0;
  DAT_000dfeaa = 0;
  DAT_000dfe9e = 0;
  DAT_000dfea2 = 0xff14;
  ref_infraction = 0;
  _penalized_slot = 0xffff;
  _dword_e9aae = 0xffff;
  last_touch_x = (short)faceoff_spot;
  last_touch_y = faceoff_spot._2_2_;
  dword_dffac._2_2_ = 0x189;
  word_dffd4 = 0;
  word_dfff0 = 0;
  word_dff70 = 0;
  _word_dff2e = 0x18a;
  action_flags = action_flags & 0xbf;
  *(undefined4 *)((int)puVar8 + -4) = 0x51fbf;
  update_camera();
  if (penalty_shot_phase == 0) {
    *(undefined4 *)((int)puVar8 + -4) = 0x52157;
    count_penalized();
    *(undefined4 *)((int)puVar8 + -4) = 0x52161;
    apply_line_change(0xdf614);
    *(undefined4 *)((int)puVar8 + -4) = 0x5216b;
    dress_line(0xdf614);
    *(undefined4 *)((int)puVar8 + -4) = 0x52175;
    apply_line_change(0xdf714);
    *(undefined4 *)((int)puVar8 + -4) = 0x5217f;
    dress_line(0xdf714);
    *(undefined4 *)((int)puVar8 + -4) = 0x52184;
    reset_players_for_faceoff();
    puVar7 = &entities;
    dword_e03ac = 0xc;
    do {
      *(undefined2 *)((int)puVar7 + 2) = 0xff10;
      *(undefined2 *)((int)puVar7 + 6) = 0;
      dword_e03be = CONCAT22(*(undefined2 *)((int)puVar7 + 0x1a),(ushort)dword_e03be);
      if ((int)puVar7[0xb] >> 0x10 == -100) {
        *(undefined2 *)((int)puVar7 + 0x2e) = 0;
      }
      if (-1 < (int)dword_e03be) {
        if (dword_e03be._2_2_ != 0) {
          if (dword_e03be._2_2_ == 4) {
            iVar4 = puVar7[0x1b];
            *(short *)(iVar4 + 0x30) = (short)*(char *)((int)puVar7 + 0x47);
            *(undefined *)(iVar4 + 0x33) = 0xff;
            *(undefined *)(iVar4 + 0x35) = 0xff;
            *(byte *)(iVar4 + 0x44) = *(byte *)(iVar4 + 0x44) & 0xf7;
            dword_e03ba = CONCAT22(0x17,(undefined2)dword_e03ba);
          }
          else {
            dword_e03ba = CONCAT22(0x16,(undefined2)dword_e03ba);
          }
          iVar4 = (int)dword_e03ba >> 0x10;
          *(undefined4 *)((int)puVar8 + -4) = 0x5220d;
          set_state_reset(puVar7,iVar4);
        }
        dword_e03b2._2_2_ = -*(short *)(puVar7[0x1b] + 0x36);
        if ((-6 < dword_e03b2._2_2_) && (*(short *)(puVar7[0x1b] + 0x38) < 0)) {
          dword_e03b2._2_2_ = dword_e03b2._2_2_ + -1;
        }
        dword_e03b2._2_2_ =
             (char)(&faceoff_lineup)
                   [(int)(short)((dword_e03b2._2_2_ + 6) * 8) + ((int)dword_e03be >> 0x10)] * 2;
        dword_e03ba._2_2_ = *(short *)(&faceoff_spots + dword_e03b2._2_2_ * 2);
        dword_e03be._2_2_ = *(short *)(&unk_cbe8e + dword_e03b2._2_2_ * 2);
        if ((*(byte *)(puVar7 + 0x11) & 0x80) == 0) {
          dword_e03ba._2_2_ = -*(short *)(&faceoff_spots + dword_e03b2._2_2_ * 2);
          dword_e03be._2_2_ = -*(short *)(&unk_cbe8e + dword_e03b2._2_2_ * 2);
        }
        if (*(short *)((int)puVar7 + 0x1a) == 0) {
          if (faceoff_spot._2_2_ < 0) {
            iVar4 = -(int)faceoff_spot._2_2_;
          }
          else {
            iVar4 = (int)faceoff_spot._2_2_;
          }
          if ((0x27 < iVar4) && (faceoff_spot._2_2_ < 0 != ((*(byte *)(puVar7 + 0x11) & 0x80) == 0))
             ) {
            if ((*(byte *)(puVar7 + 0x11) & 0x80) == 0) {
              sVar1 = 0x27;
            }
            else {
              sVar1 = -0x27;
            }
            sVar1 = faceoff_spot._2_2_ - sVar1;
            if (sVar1 < 0) {
              sVar1 = -sVar1;
            }
            iVar4 = (int)(short)faceoff_spot * (int)sVar1 * 3;
            iVar6 = iVar4 >> 0x1f;
            dword_e03ba._2_2_ =
                 dword_e03ba._2_2_ +
                 (short)((int)((iVar4 + iVar6 * -0x1000) - (uint)(iVar6 << 0xb < 0)) >> 0xc);
          }
        }
        else {
          if (dword_e03b2._2_2_ < 5) {
            if ((int)(dword_e03ba ^ CONCAT22((short)faceoff_spot,camera_target_y._2_2_)) >> 0x10 < 0
               ) {
              dword_e03be._2_2_ = dword_e03be._2_2_ - (faceoff_spot._2_2_ >> 3);
            }
            dword_e03ba = CONCAT22(dword_e03ba._2_2_ - ((short)faceoff_spot >> 2),
                                   (undefined2)dword_e03ba);
          }
          dword_e03ba._2_2_ = dword_e03ba._2_2_ + (short)faceoff_spot;
          dword_e03be._2_2_ = dword_e03be._2_2_ + faceoff_spot._2_2_;
        }
        *(short *)((int)puVar7 + 2) = dword_e03ba._2_2_;
        *(short *)((int)puVar7 + 6) = dword_e03be._2_2_;
        *(undefined2 *)(puVar7 + 3) = 0;
        *(undefined2 *)((int)puVar7 + 0xe) = 0;
        sVar1 = *p_puck_y - dword_e03be._2_2_;
        sVar2 = *p_puck_x - dword_e03ba._2_2_;
        *(undefined4 *)((int)puVar8 + -4) = 0x52413;
        uVar3 = direction8((int)sVar2,(int)sVar1);
        *(undefined2 *)((int)puVar7 + 0x36) = uVar3;
        if (*(short *)((int)puVar7 + 0x1a) == 0) {
          if (*(char *)((int)puVar7 + 0x65) == '\0') {
            uVar5 = 8U - ((int)puVar7[0xd] >> 0x10) & 7;
          }
          else {
            uVar5 = (int)puVar7[0xd] >> 0x10;
          }
          *(short *)((int)puVar7 + 0x12) = ((short)(uVar5 << 2) - (short)uVar5) + 0x196;
          dword_e03be = CONCAT22(1,(ushort)dword_e03be);
          if (*(short *)((int)puVar7 + 0x36) == 2) {
            if ((*(byte *)(puVar7 + 0x11) & 0x80) == 0) {
              uVar3 = 3;
            }
            else {
              uVar3 = 1;
            }
          }
          else {
            if (*(short *)((int)puVar7 + 0x36) != 6) goto LAB_000524f9;
            if ((*(byte *)(puVar7 + 0x11) & 0x80) == 0) {
              uVar3 = 5;
            }
            else {
              uVar3 = 7;
            }
          }
          *(undefined2 *)((int)puVar7 + 0x36) = uVar3;
        }
        else if (*(short *)((int)puVar7 + 0x1a) == 4) {
          if (*(short *)((int)puVar7 + 0x36) == 0) {
            uVar3 = 0x16c;
          }
          else {
            uVar3 = 0x167;
          }
          *(undefined2 *)((int)puVar7 + 0x12) = uVar3;
          dword_e03be = (uint)(ushort)dword_e03be;
        }
        else {
          if (*(char *)((int)puVar7 + 0x65) == '\0') {
            uVar5 = 8U - ((int)puVar7[0xd] >> 0x10) & 7;
          }
          else {
            uVar5 = (int)puVar7[0xd] >> 0x10;
          }
          *(short *)((int)puVar7 + 0x12) = (short)(uVar5 << 2) + (short)uVar5;
          dword_e03be = CONCAT22(0x289,(ushort)dword_e03be);
        }
LAB_000524f9:
        *(byte *)((int)puVar7 + 0x45) = *(byte *)((int)puVar7 + 0x45) & 0xfb;
        *(byte *)(puVar7 + 0x11) = *(byte *)(puVar7 + 0x11) & 0xdf;
        iVar4 = (int)dword_e03be >> 0x10;
        *(undefined4 *)((int)puVar8 + -4) = 0x52511;
        set_animation(puVar7,iVar4);
      }
      *(byte *)((int)puVar7 + 0x45) = *(byte *)((int)puVar7 + 0x45) & 0x7f;
      puVar7 = puVar7 + 0x20;
      dword_e03ac = dword_e03ac + -1;
    } while (dword_e03ac != 0);
    if ((short)faceoff_spot < 1) {
      word_e0052 = 2;
      sVar1 = -0xf;
    }
    else {
      word_e0052 = 6;
      sVar1 = 0xf;
    }
    referee._2_2_ = (short)faceoff_spot + sVar1;
    DAT_000e0020._2_2_ = faceoff_spot._2_2_;
    if (word_e0052 < 4) {
      word_e002e = 0x2bf;
    }
    else {
      word_e002e = 0x2c7;
    }
    *(undefined4 *)((int)puVar8 + -4) = 0x52593;
    set_state_reset(&referee,0x1e);
    word_e0028 = 0;
    word_e002a = 0;
    DAT_000e0060 = DAT_000e0060 & 0xdf;
    *(undefined4 *)((int)puVar8 + -4) = 0x525af;
    set_animation(&referee,0xc57);
    *(undefined4 *)((int)puVar8 + -4) = 0x525b4;
    sort_draw_order2();
    _user1_slot = -1;
    user2_slot = -1;
    if (user1_team != 0) {
      dword_e03b2._2_2_ = 0;
      *(undefined4 *)((int)puVar8 + -4) = 0x525e2;
      switch_to_nearest(param_1,0);
    }
    if ((short)user2_team != 0) {
      dword_e03b2._2_2_ = 2;
      dword_e03b6._0_2_ = 0;
      iVar4 = CONCAT22(2,(undefined2)dword_e03b2);
      *(undefined4 *)((int)puVar8 + -4) = 0x52606;
      switch_to_nearest(param_1,iVar4 >> 0x10);
    }
    *(undefined4 *)((int)puVar8 + -4) = 0x5260b;
    center_mouse();
    *(undefined4 *)((int)puVar8 + -4) = 0x52615;
    sVar1 = randomrange(0x78);
    *(short *)(param_1 + 0x26) = sVar1 + 0xb4;
    faceoff_ready_home._2_2_ = 1;
    faceoff_side_home = 0x8000;
    faceoff_ready_away = 4;
    faceoff_side_away = 0xa800;
    faceoff_countdown_digit = 7;
    word_e039a = 0x8000;
    if ((game_flags & 2) == 0) {
      faceoff_side_home = 0x8800;
      faceoff_side_away = 0xa000;
    }
    faceoff_dir_away = 0xffff;
    faceoff_dir_home = 0xffff;
  }
  else {
    *(undefined4 *)((int)puVar8 + -4) = 0x51fd1;
    sort_draw_order2();
    iVar4 = (int)_user1_slot;
    if ((iVar4 != CONCAT22(penalty_shot_slot._2_2_,(short)penalty_shot_slot)) &&
       ((int)user2_slot != CONCAT22(penalty_shot_slot._2_2_,(short)penalty_shot_slot))) {
      if ((int)user1_team == penalty_shot_team + 1) {
        if (iVar4 != CONCAT22(penalty_shot_slot._2_2_,(short)penalty_shot_slot)) {
          iVar6 = (int)(short)penalty_shot_slot;
          *(undefined4 *)((int)puVar8 + -4) = 0x52022;
          _user1_slot = find_switch_target(iVar6,iVar4);
        }
      }
      else if (((int)(short)user2_team == penalty_shot_team + 1) &&
              ((int)user2_slot != CONCAT22(penalty_shot_slot._2_2_,(short)penalty_shot_slot))) {
        iVar4 = (int)(short)penalty_shot_slot;
        *(undefined4 *)((int)puVar8 + -4) = 0x5204b;
        user2_slot = find_switch_target(iVar4);
      }
    }
    puVar7 = &entities;
    sVar1 = 0;
    while ((sVar1 < 0xc &&
           ((*(short *)((int)puVar7 + 0x1a) != 0 ||
            (((*(byte *)(puVar7 + 0x11) & 0x40) != 0) == penalty_shot_team))))) {
      sVar1 = sVar1 + 1;
      puVar7 = puVar7 + 0x20;
    }
    *(undefined2 *)(puVar7 + 0x12) = 0;
    *(undefined2 *)(puVar7 + 0x13) = 0;
    *(undefined2 *)((int)puVar7 + 0x4a) = 0;
    *(undefined *)((int)puVar7 + 0x53) = 0;
    *(byte *)((int)puVar7 + 0x45) = *(byte *)((int)puVar7 + 0x45) & 0xdb;
    *(byte *)(puVar7 + 0x11) = *(byte *)(puVar7 + 0x11) & 0xfb;
    if ((int)user1_team == (penalty_shot_team == 0) + 1) {
      if (_user1_slot != -1) {
        *(undefined4 *)((int)puVar8 + -4) = 0x520d7;
        _user1_slot = find_switch_target(0xffffffff);
      }
    }
    else if (((int)(short)user2_team == (penalty_shot_team == 0) + 1) && (user2_slot != -1)) {
      *(undefined4 *)((int)puVar8 + -4) = 0x5210f;
      user2_slot = find_switch_target(0xffffffff);
    }
    *(undefined4 *)((int)puVar8 + -4) = 0x5211a;
    center_mouse();
    *(undefined4 *)((int)puVar8 + -4) = 0x5211f;
    stop_crowd_loop();
    stop_flags._0_1_ = (byte)stop_flags & 0xfa;
    game_flags = game_flags & 0xfe;
    *(byte *)(param_1 + 0x45) = *(byte *)(param_1 + 0x45) & 0xfe;
    misc_flags = misc_flags | 0x10;
    *(byte *)(param_1 + 0x44) = *(byte *)(param_1 + 0x44) & 0xfb;
    *(undefined4 *)((int)puVar8 + -4) = 0x52148;
    set_state(param_1,0x18);
    *(undefined4 *)((int)puVar8 + -4) = 0x5214d;
    start_penalty_shot();
  }
  return;
}


