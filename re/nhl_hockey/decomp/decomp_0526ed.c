// Decompiled by Ghidra from hockey.elf (via ledisasm ELF export)
// This is machine generated pseudo-C meant as a reference for porting, it does not compile as is.
#include "prototypes.h"

// ================================================================================================
// ai_init_period @ 0x526ed [__watcall]
// ================================================================================================

void __watcall ai_init_period(int param_1)

{
  short sVar1;
  int extraout_EDX;
  
  __CHK(8);
  if ((*(byte *)(param_1 + 0x44) & 0x20) == 0) {
    *(undefined2 *)(param_1 + 0x12) = 0xffff;
    sVar1 = handle_line_change(param_1);
    if (sVar1 != 0) {
      *(undefined2 *)(extraout_EDX + 0x26) = 100;
      *(undefined2 *)(extraout_EDX + 0x2e) = 0;
    }
  }
  return;
}


// ================================================================================================
// ai_all_goto_faceoff @ 0x52720 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall ai_all_goto_faceoff(int *param_1)

{
  char cVar1;
  short sVar2;
  byte bVar3;
  short sVar4;
  short sVar5;
  undefined2 uVar6;
  int iVar7;
  int iVar8;
  
  __CHK(0x18);
  if (*(short *)((int)param_1 + 0x1a) < 0) {
    set_state(param_1,0xd);
    *(undefined2 *)((int)param_1 + 0x2e) = 0xff9c;
    *(byte *)((int)param_1 + 0x45) = *(byte *)((int)param_1 + 0x45) | 4;
  }
  if ((*(byte *)(param_1 + 0x11) & 0x20) != 0) {
    return;
  }
  sVar4 = handle_line_change(param_1);
  if (sVar4 != 0) {
    return;
  }
  if (param_1[0xb] >> 0x10 == -100) {
    ai_default_skate(param_1);
    cVar1 = *(char *)((int)param_1 + (*(int *)((int)param_1 + 0x1a) >> 0x10) + 0x1e);
    if ((cVar1 != '\a') && (cVar1 != '(')) {
      return;
    }
    ai_default_skate(param_1);
    return;
  }
  if ((*(byte *)(param_1 + 0x11) & 2) != 0) {
    *(byte *)(param_1 + 0x11) = *(byte *)(param_1 + 0x11) & 0xfd;
    *(undefined2 *)(param_1 + 10) = 8;
    *(undefined2 *)((int)param_1 + 0x26) = 0;
    dword_e03b2._2_2_ = -*(short *)(param_1[0x1b] + 0x36);
    if ((-6 < dword_e03b2._2_2_) && (*(short *)(param_1[0x1b] + 0x38) < 0)) {
      dword_e03b2._2_2_ = dword_e03b2._2_2_ + -1;
    }
    sVar2 = (char)(&unk_cbea8)
                  [(int)*(short *)((int)param_1 + 0x1a) + (int)(short)((dword_e03b2._2_2_ + 6) * 8)]
            * 2;
    dword_e03b2 = CONCAT22(sVar2,(undefined2)dword_e03b2);
    sVar4 = *(short *)(&unk_cbe8c + sVar2 * 2);
    sVar5 = *(short *)(&unk_cbe8e + sVar2 * 2);
    if ((*(byte *)(param_1 + 0x11) & 0x80) == 0) {
      sVar4 = -sVar4;
      sVar5 = -sVar5;
    }
    dword_e03be = CONCAT22(sVar5,(undefined2)dword_e03be);
    dword_e03ba = CONCAT22(sVar4,(undefined2)dword_e03ba);
    if (*(short *)((int)param_1 + 0x1a) == 0) {
      if (dword_c90b2._2_2_ < 0) {
        iVar7 = -(int)dword_c90b2._2_2_;
      }
      else {
        iVar7 = (int)dword_c90b2._2_2_;
      }
      if ((0x27 < iVar7) && (dword_c90b2._2_2_ < 0 != ((*(byte *)(param_1 + 0x11) & 0x80) == 0))) {
        if ((*(byte *)(param_1 + 0x11) & 0x80) == 0) {
          sVar5 = 0x27;
        }
        else {
          sVar5 = -0x27;
        }
        sVar5 = dword_c90b2._2_2_ - sVar5;
        if (sVar5 < 0) {
          sVar5 = -sVar5;
        }
        iVar7 = (int)(short)dword_c90b2 * (int)sVar5 * 3;
        iVar8 = iVar7 >> 0x1f;
        dword_e03ba._2_2_ =
             sVar4 + (short)((int)((iVar7 + iVar8 * -0x1000) - (uint)(iVar8 << 0xb < 0)) >> 0xc);
      }
    }
    else {
      if (sVar2 < 5) {
        if ((int)(dword_e03ba ^ CONCAT22((short)dword_c90b2,camera_target_y._2_2_)) >> 0x10 < 0) {
          dword_e03be = CONCAT22(sVar5 - (dword_c90b2._2_2_ >> 3),(undefined2)dword_e03be);
        }
        dword_e03ba = CONCAT22(sVar4 - ((short)dword_c90b2 >> 2),(undefined2)dword_e03ba);
      }
      dword_e03ba._2_2_ = dword_e03ba._2_2_ + (short)dword_c90b2;
      dword_e03be._2_2_ = dword_e03be._2_2_ + dword_c90b2._2_2_;
    }
    if ((dword_cc118 != 0) && (param_1[0x1a] >> 0x10 == dword_cc0fc)) {
      dword_e03ba = dword_e03ba & 0xffff;
      if ((*(byte *)(param_1 + 0x11) & 0x80) == 0) {
        uVar6 = 10;
      }
      else {
        uVar6 = 0xfff6;
      }
      dword_e03be = CONCAT22(uVar6,(undefined2)dword_e03be);
    }
    *(short *)((int)param_1 + 0x2a) = dword_e03ba._2_2_;
    *(short *)(param_1 + 0xb) = dword_e03be._2_2_;
    *(byte *)((int)param_1 + 0x45) = *(byte *)((int)param_1 + 0x45) | 0x20;
    *(undefined2 *)(param_1 + 0xc) = 0;
    *(undefined2 *)((int)param_1 + 0x32) = 0;
    if (*(short *)((int)param_1 + 0x1a) == 0) {
      uVar6 = 0x99;
    }
    else {
      uVar6 = 0x289;
    }
    set_animation(param_1,uVar6);
  }
  iVar7 = (*param_1 >> 0x10) - (param_1[10] >> 0x10);
  iVar8 = (param_1[1] >> 0x10) - (*(int *)((int)param_1 + 0x2a) >> 0x10);
  iVar7 = iVar7 * iVar7 + iVar8 * iVar8;
  if (iVar7 < 0x40) {
    if (*(short *)(param_1 + 3) < 0) {
      iVar8 = -(*(int *)((int)param_1 + 10) >> 0x10);
    }
    else {
      iVar8 = *(int *)((int)param_1 + 10) >> 0x10;
    }
    if (iVar8 < 0x10) {
      if (*(short *)((int)param_1 + 0xe) < 0) {
        iVar8 = -(param_1[3] >> 0x10);
      }
      else {
        iVar8 = param_1[3] >> 0x10;
      }
      if (iVar8 < 0x10) {
        *(undefined2 *)((int)param_1 + 2) = *(undefined2 *)((int)param_1 + 0x2a);
        *(undefined2 *)((int)param_1 + 6) = *(undefined2 *)(param_1 + 0xb);
        sVar4 = *(short *)((int)param_1 + 0x26);
        sVar5 = sVar4 + -1;
        *(short *)((int)param_1 + 0x26) = sVar5;
        if (-1 < sVar5) {
          return;
        }
        *(short *)((int)param_1 + 0x26) = sVar4 + 7;
        if (*(short *)((int)param_1 + 0x1a) == 0) {
          uVar6 = 0x99;
        }
        else {
          uVar6 = 0x289;
        }
        set_animation(param_1,uVar6);
        sVar4 = direction8((int)(short)((short)dword_c90b2 - *(short *)((int)param_1 + 2)),
                           (int)(short)(dword_c90b2._2_2_ - *(short *)((int)param_1 + 6)));
        _dword_e03ac = (int)sVar4;
        if (*(short *)((int)param_1 + 0x1a) == 0) {
          if (sVar4 == 2) {
            if ((*(byte *)(param_1 + 0x11) & 0x80) == 0) {
              uVar6 = 3;
            }
            else {
              uVar6 = 1;
            }
          }
          else {
            if (sVar4 != 6) goto LAB_00052b24;
            if ((*(byte *)(param_1 + 0x11) & 0x80) == 0) {
              uVar6 = 5;
            }
            else {
              uVar6 = 7;
            }
          }
          dword_e03ae._0_2_ = sVar4 >> 0xf;
          _dword_e03ac = CONCAT22((short)dword_e03ae,uVar6);
        }
LAB_00052b24:
        if (dword_e03ac != *(short *)((int)param_1 + 0x36)) {
          bVar3 = (char)_dword_e03ac - (char)*(short *)((int)param_1 + 0x36) & 7;
          _dword_e03ac = CONCAT22((short)dword_e03ae,(ushort)bVar3);
          if (bVar3 < 5) {
            sVar4 = 1;
          }
          else {
            sVar4 = -1;
          }
          *(ushort *)((int)param_1 + 0x36) = sVar4 + (short)((uint)param_1[0xd] >> 0x10) & 7;
          return;
        }
        *(undefined2 *)((int)param_1 + 0xe) = 0;
        *(undefined2 *)(param_1 + 3) = *(undefined2 *)((int)param_1 + 0xe);
        *(undefined2 *)((int)param_1 + 0x2e) = 0xff9c;
        return;
      }
    }
  }
  dword_e03ba = CONCAT22(*(undefined2 *)((int)param_1 + 0x2a),(undefined2)dword_e03ba);
  dword_e03be = CONCAT22(*(undefined2 *)(param_1 + 0xb),(undefined2)dword_e03be);
  if (iVar7 < 400) {
    ref_skate_to_point(param_1,0);
  }
  else {
    ai_skate_towards(param_1,0);
  }
  return;
}


// ================================================================================================
// handle_line_change @ 0x52bb6 [__watcall]
// ================================================================================================

longlong __watcall handle_line_change(int param_1,uint unaff_EDX)

{
  char cVar1;
  bool bVar2;
  uint uVar3;
  uint uVar4;
  undefined4 uVar5;
  
  __CHK(0x10);
  if ((((game_flags & 1) == 0) && ((*(byte *)(param_1 + 0x44) & 8) != 0)) ||
     ((*(byte *)(param_1 + 0x45) & 0x10) != 0)) goto LAB_00052bda;
  uVar3 = *(int *)(param_1 + 0x68) >> 0x10;
  uVar4 = dword_cc0fc;
  if (uVar3 == dword_cc0fc) goto LAB_00052bf0;
  if ((((dword_cc11c != 0) &&
       ((cVar1 = *(char *)((*(int *)(param_1 + 0x1a) >> 0x10) + param_1 + 0x1e), cVar1 == '\a' ||
        (cVar1 == '\t')))) ||
      ((*(char *)(param_1 + 0x42) < '\0' && (*(char *)(param_1 + 0x43) < '\0')))) ||
     (((clock_seconds == dword_e9ab6._2_2_ && (clock_sub == 0)) &&
      ((((short)*(char *)(param_1 + 0x42) == *(short *)(param_1 + 0x1a) &&
        ((*(char *)(param_1 + 0x43) == *(char *)(param_1 + 0x47) &&
         (*(char *)(param_1 + 0x1e + (*(int *)(param_1 + 0x1a) >> 0x10)) == '\'')))) ||
       (((&word_cbc6a)[(*(byte *)(param_1 + 0x44) & 0x40) != 0] != 0 &&
        (*(char *)(param_1 + 0x1e + (*(int *)(param_1 + 0x1a) >> 0x10)) == ')'))))))))
  goto LAB_00052bda;
  if (*(char *)(param_1 + 0x43) == *(char *)(param_1 + 0x47)) {
    if (dword_cc11c != 0) {
      cVar1 = *(char *)((*(int *)(param_1 + 0x1a) >> 0x10) + param_1 + 0x1e);
      uVar4 = CONCAT31((int3)(dword_cc0fc >> 8),cVar1);
      if ((cVar1 == ')') || (cVar1 == '-')) goto LAB_00052ca7;
    }
    *(byte *)(param_1 + 0x45) = *(byte *)(param_1 + 0x45) & 0xfb;
    *(byte *)(param_1 + 0x44) = *(byte *)(param_1 + 0x44) & 0xfb;
    if (-1 < *(char *)(param_1 + 0x42)) {
      if ((*(char *)(param_1 + 0x42) == '\0') != *(char *)(param_1 + 0x47) < '\x19') {
        *(short *)(param_1 + 0x1a) = (short)*(char *)(param_1 + 0x42);
      }
    }
    set_default_state(param_1);
    if ((game_flags & 1) != 0) {
      if ((clock_seconds == dword_e9ab6._2_2_) && (clock_sub == 0)) {
        bVar2 = false;
      }
      else {
        bVar2 = true;
      }
      if (bVar2) {
        *(undefined2 *)(param_1 + 0x2e) = 0;
        if ((*(short *)(param_1 + 0x1a) < 1) ||
           ((&word_cbc6a)[(*(byte *)(param_1 + 0x44) & 0x40) != 0] == 0)) {
          uVar5 = 0x27;
        }
        else {
          uVar5 = 0x28;
        }
        set_state_reset(param_1,uVar5);
      }
    }
    *(undefined *)(param_1 + 0x43) = 0xff;
    *(undefined *)(param_1 + 0x42) = 0xff;
  }
  else {
LAB_00052ca7:
    if (*(char *)(param_1 + 0x1e + (*(int *)(param_1 + 0x1a) >> 0x10)) == '\v') {
LAB_00052bda:
      return (ulonglong)unaff_EDX << 0x20;
    }
    uVar3 = CONCAT22((short)((uint)p_puck_carrier >> 0x10),(short)*p_puck_carrier);
    uVar4 = CONCAT22((short)(uVar4 >> 0x10),*(short *)(param_1 + 0x6a));
    if ((short)*p_puck_carrier == *(short *)(param_1 + 0x6a)) {
LAB_00052bf0:
      return CONCAT44(unaff_EDX,uVar3 ^ uVar4);
    }
    *(byte *)(param_1 + 0x45) = *(byte *)(param_1 + 0x45) | 4;
    *(byte *)(param_1 + 0x44) = *(byte *)(param_1 + 0x44) & 0xfb;
    *(undefined2 *)(param_1 + 0x26) = 0;
    if ((game_flags & 1) != 0) {
      *(undefined2 *)(param_1 + 0x2e) = 0;
    }
    set_state(param_1,0xb);
  }
  return CONCAT44(unaff_EDX,1);
}


// ================================================================================================
// ai_all_penalty_shot_wait @ 0x52db0 [__watcall]
// ================================================================================================

void __watcall ai_all_penalty_shot_wait(int param_1)

{
  short sVar1;
  undefined2 uVar2;
  int iVar3;
  code *pcVar4;
  short sVar5;
  
  __CHK(0x14);
  if ((*(byte *)(param_1 + 0x44) & 0x20) == 0) {
    if (*(short *)(param_1 + 0x26) == 100) {
      *(undefined2 *)(param_1 + 0x12) = 0xffff;
      *(undefined2 *)(param_1 + 2) = 0xff58;
    }
    else if (dword_cc118 != 0) {
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
        *(undefined *)(param_1 + 0x42) = 0xff;
        *(undefined *)(param_1 + 0x43) = *(undefined *)(param_1 + 0x42);
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
                 (short)((uint)*(undefined4 *)(param_1 + 0x34) >> 0x10) + sVar1 & 7;
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
          *(byte *)(param_1 + 0x45) = *(byte *)(param_1 + 0x45) | 4;
          *(undefined2 *)(param_1 + 0x2e) = 0xff9c;
          *(undefined2 *)(param_1 + 0x26) = 100;
          return;
        }
      }
      if ((*(byte *)(param_1 + 0x44) & 4) == 0) {
        dword_e03ba._2_2_ = *(undefined2 *)(param_1 + 0x2a);
        dword_e03be = CONCAT22(*(undefined2 *)(param_1 + 0x2c),(undefined2)dword_e03be);
        if (((game_flags & 1) == 0) && (*(short *)(param_1 + 0x1a) != 0)) {
          pcVar4 = ai_near_carrier_check;
        }
        else {
          pcVar4 = (code *)0x0;
        }
        ai_skate_towards(param_1,pcVar4);
        return;
      }
    }
  }
  return;
}


// ================================================================================================
// ai_ref_penalty_shot @ 0x52fb0 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall
ai_ref_penalty_shot(int *param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  char cVar1;
  undefined *puVar2;
  undefined uVar3;
  byte bVar4;
  short sVar5;
  undefined2 uVar6;
  char cVar8;
  int iVar7;
  int iVar9;
  
  __CHK(0x10);
  if ((*(byte *)(param_1 + 0x11) & 0x20) == 0) {
    if ((*(byte *)(param_1 + 0x11) & 2) != 0) {
      *(byte *)(param_1 + 0x11) = *(byte *)(param_1 + 0x11) & 0xfd;
      *(undefined2 *)(param_1 + 10) = 8;
      *(undefined *)((int)param_1 + 0x26) = 0;
      uVar3 = direction8((int)-*(short *)((int)param_1 + 2),(int)-*(short *)((int)param_1 + 6),
                         param_1,unaff_ECX,unaff_EDX,unaff_ECX,unaff_EBX);
      *(undefined *)((int)param_1 + 0x27) = uVar3;
      *(undefined2 *)((int)param_1 + 0x2a) = 0;
      *(undefined2 *)(param_1 + 0xb) = 0;
      *(undefined2 *)((int)param_1 + 0x2e) = 0;
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
    if (dword_cc0fc == -1) {
      set_state(param_1,0x21);
      return;
    }
    if (*(short *)((int)param_1 + 0x2e) != 100) {
      if (*(short *)((int)param_1 + 0x2e) == 1) {
        *p_puck_carrier = 0xff;
        puVar2 = p_puck_vz;
        *(undefined2 *)p_puck_vz = 0;
        uVar6 = *(undefined2 *)puVar2;
        *(undefined2 *)p_puck_vy = uVar6;
        *(undefined2 *)p_puck_vx = uVar6;
        *p_puck_z = uVar6;
        *p_puck_y = uVar6;
        *p_puck_x = uVar6;
        *(short *)((int)param_1 + 0x2e) = *(short *)((int)param_1 + 0x2e) + 1;
      }
      iVar9 = (*param_1 >> 0x10) - (param_1[10] >> 0x10);
      iVar7 = (param_1[1] >> 0x10) - (*(int *)((int)param_1 + 0x2a) >> 0x10);
      if (iVar9 * iVar9 + iVar7 * iVar7 < 0x40) {
        if (*(short *)(param_1 + 3) < 0) {
          iVar7 = -(*(int *)((int)param_1 + 10) >> 0x10);
        }
        else {
          iVar7 = *(int *)((int)param_1 + 10) >> 0x10;
        }
        if (iVar7 < 0x10) {
          if (*(short *)((int)param_1 + 0xe) < 0) {
            iVar7 = -(param_1[3] >> 0x10);
          }
          else {
            iVar7 = param_1[3] >> 0x10;
          }
          if (iVar7 < 0x10) {
            if (*(short *)((int)param_1 + 0x2e) == 0) {
              _dword_e03ac = param_1[9] >> 0x18;
            }
            else {
              *(undefined2 *)((int)param_1 + 2) = *(undefined2 *)((int)param_1 + 0x2a);
              *(undefined2 *)((int)param_1 + 6) = *(undefined2 *)(param_1 + 0xb);
              _dword_e03ac = 6;
            }
            cVar1 = *(char *)((int)param_1 + 0x26);
            cVar8 = cVar1 + -1;
            *(char *)((int)param_1 + 0x26) = cVar8;
            if (-1 < cVar8) {
              return;
            }
            *(char *)((int)param_1 + 0x26) = cVar1 + '\a';
            set_animation(param_1,0xa5b);
            if (dword_e03ac != *(short *)((int)param_1 + 0x36)) {
              bVar4 = (char)_dword_e03ac - (char)*(short *)((int)param_1 + 0x36) & 7;
              _dword_e03ac = CONCAT22((undefined2)dword_e03ae,(ushort)bVar4);
              if (bVar4 < 5) {
                sVar5 = 1;
              }
              else {
                sVar5 = -1;
              }
              *(ushort *)((int)param_1 + 0x36) = sVar5 + (short)((uint)param_1[0xd] >> 0x10) & 7;
              return;
            }
            *(undefined2 *)((int)param_1 + 0xe) = 0;
            *(undefined2 *)(param_1 + 3) = *(undefined2 *)((int)param_1 + 0xe);
            if (*(short *)((int)param_1 + 0x2e) != 0) {
              iVar7 = speech_busy();
              if (iVar7 != 0) {
                return;
              }
              if (dword_cbeca >> 0x10 != -1) {
                return;
              }
              iVar7 = sub_51440();
              if (iVar7 == 0) {
                return;
              }
              dword_c90d4 = 0xffff;
              play_sfx(0xa4);
              *(undefined2 *)((int)param_1 + 0x2e) = 100;
              return;
            }
            *(byte *)(param_1 + 0x11) = *(byte *)(param_1 + 0x11) | 0x20;
            set_animation(param_1,0xc03);
            *(undefined2 *)((int)param_1 + 0x2a) = 0x96;
            if (((game_flags & 2) == 0) == dword_cc104) {
              uVar6 = 10;
            }
            else {
              uVar6 = 0xfff6;
            }
            *(undefined2 *)(param_1 + 0xb) = uVar6;
            *(short *)((int)param_1 + 0x2e) = *(short *)((int)param_1 + 0x2e) + 1;
            dword_c90d4 = 0;
            action_flags = action_flags & 0xbf;
            return;
          }
        }
      }
      dword_e03ba._2_2_ = *(undefined2 *)((int)param_1 + 0x2a);
      dword_e03be._2_2_ = *(undefined2 *)(param_1 + 0xb);
      ref_skate_to_point(param_1,0);
    }
  }
  return;
}


// ================================================================================================
// sub_53294 @ 0x53294 [__watcall]
// ================================================================================================

int __watcall sub_53294(int param_1)

{
  __CHK(4);
  return param_1 << 0x10;
}


// ================================================================================================
// sub_532a2 @ 0x532a2 [__watcall]
// ================================================================================================

void __watcall sub_532a2(int param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  __CHK(8);
  *(byte *)(param_1 + 0x44) = *(byte *)(param_1 + 0x44) | 0x20;
  set_animation(param_1,0x589,unaff_EBX,unaff_ECX,unaff_EDX);
  return;
}


// ================================================================================================
// body_check @ 0x532bd [__watcall]
// ================================================================================================

void __watcall body_check(int param_1)

{
  short sVar1;
  
  __CHK(0x18);
  sVar1 = *(short *)(*(int *)(param_1 + 0x6c) + 0x46 + (*(int *)(param_1 + 0x44) >> 0x18) * 2);
  dword_e03ba._2_2_ = sVar1;
  if (((byte)option_flags & 4) != 0) {
    dword_e03ba._2_2_ = sVar1 + -0xcc;
    sVar1 = dword_e03ba._2_2_;
    if (dword_e03ba._2_2_ < 0) {
      sVar1 = 0;
    }
    *(short *)(*(int *)(param_1 + 0x6c) + 0x46 + (*(int *)(param_1 + 0x44) >> 0x18) * 2) = sVar1;
    if (dword_e03ba._2_2_ < 0) {
      dword_e03ba._2_2_ = 0;
    }
  }
  dword_e03ba._2_2_ = dword_e03ba._2_2_ >> 7;
  *(short *)(param_1 + 0xc) =
       *(short *)(param_1 + 0xc) +
       *(short *)(&dir8_vectors + (*(int *)(param_1 + 0x34) >> 0x10) * 4) * dword_e03ba._2_2_;
  *(short *)(param_1 + 0xe) =
       *(short *)(param_1 + 0xe) +
       *(short *)(&unk_c90e2 + (*(int *)(param_1 + 0x34) >> 0x10) * 4) * dword_e03ba._2_2_;
  *(byte *)(param_1 + 0x44) = *(byte *)(param_1 + 0x44) | 0x20;
  set_animation(param_1,0x621);
  return;
}


// ================================================================================================
// start_poke_check @ 0x53387 [__watcall]
// ================================================================================================

void __watcall start_poke_check(int param_1,int unaff_EDX)

{
  short sVar1;
  uint uVar2;
  short sVar3;
  undefined2 uVar4;
  int iVar5;
  
  __CHK(0x14);
  *(byte *)(param_1 + 0x44) = *(byte *)(param_1 + 0x44) | 0x20;
  *(short *)(param_1 + 0x36) = (short)*(char *)(param_1 + 0x52);
  if ((unaff_EDX == 10) || (unaff_EDX == 3)) {
    if ((*p_puck_z < 3) && (*(short *)p_puck_vz < 2000)) {
      uVar4 = 0x14ad;
    }
    else {
      uVar4 = 0x1475;
    }
    goto LAB_000534ae;
  }
  *(short *)(param_1 + 0x36) = *(short *)(param_1 + 0x4a);
  sVar1 = *(short *)(param_1 + 0x4a) * 2;
  sVar3 = *(short *)(&unk_ccc32 + sVar1 * 2);
  if (unaff_EDX < 3) {
    sVar3 = -sVar3;
  }
  uVar2 = *(int *)(param_1 + 0xc) >> 0x10;
  if ((int)((int)sVar3 ^ uVar2) < 0) {
LAB_0005342a:
    *(short *)(param_1 + 0xe) = *(short *)(param_1 + 0xe) >> 3;
  }
  else {
    if (*(short *)(param_1 + 0xe) < 0) {
      uVar2 = -uVar2;
    }
    if (sVar3 < 0) {
      iVar5 = -(int)sVar3;
    }
    else {
      iVar5 = (int)sVar3;
    }
    if ((int)uVar2 <= iVar5) goto LAB_0005342a;
    *(short *)(param_1 + 0xe) = *(short *)(param_1 + 0xe) >> 1;
  }
  *(short *)(param_1 + 0xe) = *(short *)(param_1 + 0xe) + sVar3;
  sVar3 = *(short *)(&unk_ccc30 + sVar1 * 2);
  if (unaff_EDX < 3) {
    sVar3 = -sVar3;
  }
  if (unaff_EDX < 3 == (*(char *)(param_1 + 0x65) == '\0')) {
    uVar4 = 0x141d;
  }
  else {
    uVar4 = 0x13c5;
  }
  uVar2 = *(int *)(param_1 + 10) >> 0x10;
  if ((int)((int)sVar3 ^ uVar2) < 0) {
LAB_000534a5:
    *(short *)(param_1 + 0xc) = *(short *)(param_1 + 0xc) >> 3;
  }
  else {
    if (*(short *)(param_1 + 0xc) < 0) {
      uVar2 = -uVar2;
    }
    if (sVar3 < 0) {
      iVar5 = -(int)sVar3;
    }
    else {
      iVar5 = (int)sVar3;
    }
    if ((int)uVar2 <= iVar5) goto LAB_000534a5;
    *(short *)(param_1 + 0xc) = *(short *)(param_1 + 0xc) >> 1;
  }
  *(short *)(param_1 + 0xc) = *(short *)(param_1 + 0xc) + sVar3;
LAB_000534ae:
  set_animation(param_1,uVar4);
  return;
}


// ================================================================================================
// sub_534bb @ 0x534bb [__watcall]
// ================================================================================================

void __watcall sub_534bb(int param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  short sVar1;
  int iVar2;
  int iVar3;
  
  __CHK(0x10);
  iVar3 = 8;
  if (((stop_flags & 0x20) != 0) &&
     ((ushort)(*(byte *)(param_1 + 0x44) & 0x40) != (stop_flags & 0x40))) {
    iVar3 = 4;
  }
  iVar3 = iVar3 + (0xf - (uint)*(byte *)(param_1 + 0x5a));
  sVar1 = randomrange((int)(short)(iVar3 / 2));
  if (sVar1 < 2) {
    iVar2 = try_block_shot(param_1);
    if (iVar2 != 0) {
      start_poke_check(param_1,iVar2,iVar3,param_1,unaff_EDX,unaff_ECX,unaff_EBX);
    }
  }
  return;
}


// ================================================================================================
// ai_try_check @ 0x53537 [__watcall]
// ================================================================================================

void __watcall ai_try_check(int param_1)

{
  int iVar1;
  int iVar2;
  short sVar3;
  undefined4 *puVar4;
  
  __CHK(0x18);
  sVar3 = 0x14 - (ushort)*(byte *)(param_1 + 100);
  dword_e03ba._2_2_ = sVar3;
  if (((byte)option_flags & 1) != 0) {
    dword_e03ba._2_2_ = sVar3 + (sVar3 >> 1);
  }
  sVar3 = randomrange((int)(short)(dword_e03ba._2_2_ * 2));
  if (sVar3 < 9) {
    if (*(short *)(param_1 + 0x6a) < 6) {
      iVar1 = 6;
    }
    else {
      iVar1 = 0;
    }
    puVar4 = &entities + iVar1 * 0x20;
    dword_e03ac = 6;
    do {
      if (((*(short *)((int)puVar4 + 0x1a) != 0) && ((*(byte *)(puVar4 + 0x11) & 0x20) == 0)) &&
         ((*(byte *)((int)puVar4 + 0x45) & 1) == 0)) {
        dword_e03ba._2_2_ = *(short *)((int)puVar4 + 2) - *(short *)(param_1 + 2);
        if (dword_e03ba._2_2_ < 0) {
          iVar1 = -(int)dword_e03ba._2_2_;
        }
        else {
          iVar1 = (int)dword_e03ba._2_2_;
        }
        if (iVar1 < 0x1f) {
          sVar3 = *(short *)((int)puVar4 + 6) - *(short *)(param_1 + 6);
          dword_e03be = CONCAT22(sVar3,(undefined2)dword_e03be);
          iVar2 = (int)sVar3;
          iVar1 = iVar2;
          if (sVar3 < 0) {
            iVar1 = -iVar2;
          }
          if ((iVar1 < 0x1f) &&
             (sVar3 = direction8((int)dword_e03ba._2_2_,iVar2), sVar3 == *(short *)(param_1 + 0x36))
             ) {
            sVar3 = randomrange(4);
            if (sVar3 != 0) {
              body_check(param_1);
              return;
            }
            start_hook(param_1,puVar4);
            return;
          }
        }
      }
      puVar4 = puVar4 + 0x20;
      dword_e03ac = dword_e03ac + -1;
    } while (dword_e03ac != 0);
    sub_534bb(param_1);
  }
  return;
}


// ================================================================================================
// sub_5369f @ 0x5369f [__watcall]
// ================================================================================================

void __watcall sub_5369f(int *param_1)

{
  uint uVar1;
  short sVar2;
  int iVar3;
  
  __CHK(0x10);
  iVar3 = 0x14 - (uint)*(byte *)((int)param_1 + 0x62);
  uVar1 = iVar3 * 0x10;
  if ((*(byte *)(param_1 + 0x11) & 8) != 0) {
    uVar1 = iVar3 * 0x20;
  }
  iVar3 = (*param_1 >> 0x10) - (int)*p_puck_x;
  if (iVar3 < 0) {
    iVar3 = -iVar3;
  }
  if (iVar3 < 0x29) {
    iVar3 = (param_1[1] >> 0x10) - (int)*p_puck_y;
    if (iVar3 < 0) {
      iVar3 = -iVar3;
    }
    if (iVar3 < 0x29) {
      uVar1 = (uint)(ushort)((short)uVar1 >> 1);
    }
  }
  if (2 < period_idx) {
    uVar1 = uVar1 << 3;
  }
  if ((option_flags._1_1_ & 2) == 0) {
    uVar1 = uVar1 * 2;
  }
  sVar2 = *(short *)(param_1[0x1c] + 0x36) - *(short *)(param_1[0x1b] + 0x36);
  if (0 < sVar2) {
    uVar1 = uVar1 << 2;
  }
  if (1 < sVar2) {
    uVar1 = uVar1 << 2;
  }
  sVar2 = (short)uVar1;
  if ((((game_flags & 8) != 0) && (-1 < *p_puck_carrier)) &&
     (*p_puck_carrier < '\x06' != *(short *)((int)param_1 + 0x6a) < 6)) {
    sVar2 = (short)(uVar1 << 2);
  }
  randomrange((int)(short)((sVar2 >> 1) + sVar2));
  return;
}


// ================================================================================================
// sub_5378d @ 0x5378d [__watcall]
// ================================================================================================

longlong __watcall sub_5378d(int param_1,uint unaff_EDX)

{
  short sVar1;
  short sVar2;
  bool bVar3;
  
  __CHK(0x10);
  sVar1 = *(short *)(param_1 + 6);
  sVar2 = *(short *)(param_1 + 0x36);
  if (*(short *)(param_1 + 2) < -0x78) {
    if ((sVar2 == 6) || ((0xe8 < sVar1 && (sVar2 == 7)))) goto LAB_000537d6;
    if (-0xe9 < sVar1) goto LAB_00053826;
    bVar3 = sVar2 == 5;
  }
  else if (*(short *)(param_1 + 2) < 0x79) {
    if ((0xf2 < sVar1) && (sVar2 == 0)) goto LAB_000537d6;
    if (-0xf3 < sVar1) goto LAB_00053826;
    bVar3 = sVar2 == 4;
  }
  else {
    if ((sVar2 == 2) || ((0xe8 < sVar1 && (sVar2 == 1)))) goto LAB_000537d6;
    if (-0xe9 < sVar1) goto LAB_00053826;
    bVar3 = sVar2 == 3;
  }
  if (!bVar3) {
LAB_00053826:
    return (ulonglong)unaff_EDX << 0x20;
  }
LAB_000537d6:
  return CONCAT44(unaff_EDX,1);
}


// ================================================================================================
// resolve_body_check @ 0x5382c [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall resolve_body_check(int *param_1,int *unaff_EDX,short unaff_BX)

{
  short sVar1;
  undefined2 uVar2;
  short sVar3;
  int iVar4;
  int *piVar5;
  short extraout_DX;
  ushort uVar6;
  bool bVar7;
  char cStackY_14;
  
  __CHK(0x1c);
  cStackY_14 = '\0';
  do {
    piVar5 = unaff_EDX;
    if ('\x01' < cStackY_14) {
      return;
    }
    sVar1 = *(short *)(piVar5 + 0xe);
    if ((sVar1 == 0x639) || (sVar1 == 0x873)) {
      resolve_poke_hit(param_1,piVar5);
    }
    else if (sVar1 == 0x589) {
      resolve_hook_hit(param_1,piVar5);
    }
    else if (*(short *)(param_1 + 0xe) == 0x621) {
      if ((game_flags & 1) != 0) {
        *(undefined2 *)(param_1 + 6) = 0x100;
        *(undefined2 *)(piVar5 + 6) = 0x100;
      }
      sVar1 = direction8((int)(short)(*(short *)((int)piVar5 + 2) - *(short *)((int)param_1 + 2)),
                         (int)(short)(*(short *)((int)piVar5 + 6) - *(short *)((int)param_1 + 6)));
      uVar6 = (byte)((char)sVar1 - (char)*(undefined2 *)((int)param_1 + 0x36)) & 0xff07;
      if ((*(byte *)((int)param_1 + 0x55) & 8) != 0) {
        uVar6 = (byte)(8 - (char)uVar6) & 0xff07;
      }
      *(byte *)(param_1 + 0x11) = *(byte *)(param_1 + 0x11) | 0x20;
      if (*(short *)((int)piVar5 + 2) < 0) {
        iVar4 = -(*piVar5 >> 0x10);
      }
      else {
        iVar4 = *piVar5 >> 0x10;
      }
      if (iVar4 < 0x91) {
        if (0 < *(short *)((int)param_1 + 6) != ((*(byte *)(param_1 + 0x11) & 0x80) != 0)) {
          if (*(short *)((int)piVar5 + 6) < 0) {
            iVar4 = -(piVar5[1] >> 0x10);
          }
          else {
            iVar4 = piVar5[1] >> 0x10;
          }
          if (iVar4 + -0xe8 < 0x3c) {
            if (*(short *)((int)piVar5 + 2) < 0) {
              iVar4 = -(*piVar5 >> 0x10);
            }
            else {
              iVar4 = *piVar5 >> 0x10;
            }
            if (iVar4 < 0x50) goto LAB_0005395e;
          }
        }
        uVar2 = 0x1e;
      }
      else {
LAB_0005395e:
        uVar2 = 0x14;
      }
      if (((*(short *)((int)piVar5 + 0x6a) == 0x10) ||
          (sVar3 = randomrange(uVar2,*(undefined *)((int)param_1 + 0x62)), extraout_DX <= sVar3)) ||
         (2 < ((int)(short)uVar6 + 1U & 7))) {
LAB_00053a39:
        iVar4 = *(int *)(&unk_ccc4e + (short)uVar6 * 2) >> 0x10;
      }
      else {
        iVar4 = (*param_1 >> 0x10) - (*piVar5 >> 0x10);
        if (iVar4 < 0) {
          iVar4 = -iVar4;
        }
        if (0x13 < iVar4) goto LAB_00053a39;
        iVar4 = (param_1[1] >> 0x10) - (piVar5[1] >> 0x10);
        if (iVar4 < 0) {
          iVar4 = -iVar4;
        }
        if (0x13 < iVar4) goto LAB_00053a39;
        if (*(short *)(piVar5 + 3) < 0) {
          iVar4 = -(*(int *)((int)piVar5 + 10) >> 0x10);
        }
        else {
          iVar4 = *(int *)((int)piVar5 + 10) >> 0x10;
        }
        if (iVar4 < 500) {
          if (*(short *)((int)piVar5 + 0xe) < 0) {
            iVar4 = -(piVar5[3] >> 0x10);
          }
          else {
            iVar4 = piVar5[3] >> 0x10;
          }
          if (499 < iVar4) goto LAB_00053a11;
        }
        else {
LAB_00053a11:
          iVar4 = param_1[0xd];
          sVar3 = direction8(*(int *)((int)piVar5 + 10) >> 0x10,piVar5[3] >> 0x10);
          if ((((int)sVar3 - (iVar4 >> 0x10)) + 2U & 3) == 0) goto LAB_00053a39;
        }
        iVar4 = 0xed7;
      }
      set_animation(param_1,iVar4);
      if ((*(short *)((int)piVar5 + 0x1a) != 0) && (0x13 < unaff_BX)) {
        if ((*(byte *)(param_1 + 0x11) & 8) == 0) {
          sVar3 = 100;
        }
        else {
          sVar3 = 0xa0;
        }
        if (((*(byte *)(piVar5 + 0x11) & 8) != 0) != (sVar3 == 0xa0)) {
          sVar3 = 0x78;
        }
        sVar3 = (short)((int)(((int)sVar3 - (uint)*(byte *)((int)param_1 + 0x56)) +
                             (uint)*(byte *)((int)piVar5 + 0x56)) >> 1) -
                (short)((uint)*(undefined4 *)((int)piVar5 + 0x16) >> 0x10);
        if ((sVar3 < 1) ||
           (((((game_flags & 0x10) == 0 && (iVar4 = sub_6427f(piVar5), iVar4 != 0)) &&
             (dword_cc0fc < 0)) ||
            (sVar3 = randomrange((int)sVar3), sVar3 <= (short)(ushort)*(byte *)(param_1 + 0x19)))))
        {
          if (*(short *)((int)piVar5 + 0x6a) == 0x10) {
            if ((*(byte *)(param_1 + 0x11) & 8) == 0) goto LAB_00053cc8;
            word_cbec2 = word_cbec2 + 1;
            if (2 < word_cbec2) {
              word_cbec2 = 0;
              maybe_queue_infraction(param_1,0x16);
            }
          }
          else if ((game_flags & 0x10) == 0) {
            iVar4 = sub_6427f(piVar5);
            if (iVar4 == 0) {
              if (((*(short *)(piVar5 + 6) < 0x24) ||
                  (2 < (((int)sVar1 - (param_1[0xd] >> 0x10)) + 1U & 7))) ||
                 ((2 < (((piVar5[0xd] >> 0x10) - (param_1[0xd] >> 0x10)) + 1U & 7) ||
                  ((sVar1 = sub_5378d(piVar5), sVar1 == 0 ||
                   (sVar1 = sub_5369f(param_1), 0x13 < sVar1)))))) {
                sVar1 = sub_5369f(param_1);
                if (3 < sVar1) goto LAB_00053cbf;
                if (*(short *)(param_1 + 0xe) == 0xed7) {
                  sVar1 = randomrange(10);
                  if (sVar1 < 9) {
                    uVar2 = 0xe;
                  }
                  else {
                    uVar2 = 0x13;
                  }
                }
                else if ((*(short *)(piVar5 + 6) < 0x24) || (sVar1 = randomrange(4), sVar1 != 0)) {
                  sVar1 = randomrange(10);
                  if (sVar1 < 7) {
                    uVar2 = 0xd;
                  }
                  else {
                    uVar2 = 0x15;
                  }
                }
                else {
                  uVar2 = 0x19;
                }
              }
              else {
                uVar2 = 0x17;
              }
            }
            else {
              if (-1 < dword_cc0fc) goto LAB_00053cbf;
              dword_cc0fc = piVar5[0x1a] >> 0x10;
              bVar7 = _misc_flags >> 0x10 != dword_cc0fc;
              if (bVar7) {
                if (bVar7) {
                  _dword_cc108 = 0xffffffff;
                }
                else {
                  _dword_cc108 = 2;
                }
              }
              else {
                _dword_cc108 = 1;
              }
              uVar2 = 0x1a;
            }
            maybe_queue_infraction(param_1,uVar2);
          }
LAB_00053cbf:
          knock_down(param_1,piVar5);
        }
        else if (((*(short *)((int)piVar5 + 0x6a) != 0x10) &&
                 (sVar1 = sub_5369f(param_1), sVar1 < 5)) && ((game_flags & 0x10) == 0)) {
          sVar1 = randomrange(2);
          maybe_queue_infraction(param_1,(sVar1 != 0) + '\v');
        }
      }
    }
LAB_00053cc8:
    cStackY_14 = cStackY_14 + '\x01';
    unaff_EDX = param_1;
    param_1 = piVar5;
  } while( true );
}


// ================================================================================================
// sub_53ce5 @ 0x53ce5 [__watcall]
// ================================================================================================

void __watcall sub_53ce5(int param_1,int unaff_EDX,short unaff_BX,short unaff_CX)

{
  short sVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  
  __CHK(0x14);
  if ((*(short *)(param_1 + 0x6a) < 0xc) || (*(short *)(param_1 + 0x6a) == 0x10)) {
    unaff_CX = unaff_CX - *(short *)(unaff_EDX + 6);
    unaff_BX = unaff_BX - *(short *)(unaff_EDX + 2);
    if (*(short *)(unaff_EDX + 0x6a) == 0xc) {
      if ((int)dword_c909e + (int)unaff_CX < -0x22) {
        return;
      }
    }
    else if (0x21 < (int)unaff_CX - (int)dword_c909e) {
      return;
    }
    if (unaff_BX < 0) {
      iVar2 = -(int)unaff_BX;
    }
    else {
      iVar2 = (int)unaff_BX;
    }
    if (iVar2 - dword_c909c < 0x40) {
      dword_e03ba = CONCAT22(-unaff_CX,(undefined2)dword_e03ba);
      dword_e03be = CONCAT22(unaff_BX,(undefined2)dword_e03be);
      iVar2 = (int)unaff_BX * (int)unaff_BX >> 2;
      if (((iVar2 < 0x101) && ((int)unaff_CX * (int)unaff_CX * 2 + iVar2 < 0x101)) &&
         ((*(short *)(param_1 + 0x6a) == 0x10 || (sVar1 = sub_54990(param_1), sVar1 == 0)))) {
        iVar2 = sub_b3d94((int)unaff_BX,(int)unaff_CX);
        sVar1 = (short)(((dword_e03ba >> 0x10) << 8) / (int)(iVar2 + 1U & 0xffff));
        dword_e03ba = CONCAT22(sVar1,(undefined2)dword_e03ba);
        if (0xff < sVar1) {
          dword_e03ba = CONCAT22(0xff,(undefined2)dword_e03ba);
        }
        if (dword_e03ba >> 0x10 < -0xff) {
          dword_e03ba = CONCAT22(0xff01,(undefined2)dword_e03ba);
        }
        iVar3 = (dword_e03be >> 0x10) << 8;
        uVar4 = iVar2 + 1U & 0xffff;
        sVar1 = (short)(iVar3 / (int)uVar4);
        dword_e03be = CONCAT22(sVar1,(undefined2)dword_e03be);
        if (0xff < sVar1) {
          dword_e03be = CONCAT22(0xff,(undefined2)dword_e03be);
        }
        if (dword_e03be >> 0x10 < -0xff) {
          dword_e03be = CONCAT22(0xff01,(undefined2)dword_e03be);
        }
        dword_ccc2c = 1;
        bounce_off_boards(param_1,iVar3 % (int)uVar4);
      }
    }
  }
  return;
}


// ================================================================================================
// check_injury @ 0x53e6a [__watcall]
// ================================================================================================

void __watcall check_injury(int param_1,int unaff_EDX)

{
  short sVar1;
  int iVar2;
  int iVar3;
  undefined uStackY_c;
  
  __CHK(0x10);
  for (uStackY_c = '\0'; iVar3 = unaff_EDX, uStackY_c < '\x02'; uStackY_c = uStackY_c + '\x01') {
    if ((((*(short *)(iVar3 + 0x1a) == 0) && ((game_flags & 1) == 0)) &&
        (((short)*p_puck_carrier == *(short *)(param_1 + 0x6a) ||
         (0x19 < *(short *)(param_1 + 0x18))))) && (2 < *(short *)(param_1 + 0x18))) {
      knock_down(iVar3,param_1);
      if ((7 < word_e9b28) &&
         (((short)*p_puck_carrier != *(short *)(param_1 + 0x6a) || (9 < word_e9b28)))) {
        if (*(short *)(iVar3 + 6) < 0) {
          iVar2 = -(*(int *)(iVar3 + 4) >> 0x10);
        }
        else {
          iVar2 = *(int *)(iVar3 + 4) >> 0x10;
        }
        if ((((0x9f < iVar2) && (*(short *)(param_1 + 0x6a) != 0x10)) &&
            (-3 < *(int *)(*(int *)(param_1 + 0x6c) + 0x7c + (*(int *)(param_1 + 0x44) >> 0x18) * 2)
                  >> 0x10)) &&
           ((0x1e < *(short *)(iVar3 + 0x18) && ((*(byte *)(param_1 + 0x45) & 0x10) == 0)))) {
          sVar1 = randomrange((int)(short)(0x14 - (ushort)*(byte *)(param_1 + 0x62)));
          if ((sVar1 < 3) && (((game_flags & 0x10) == 0 && ((*(byte *)(iVar3 + 6) & 4) == 0)))) {
            maybe_queue_infraction(param_1,0x11);
          }
        }
      }
    }
    unaff_EDX = param_1;
    param_1 = iVar3;
  }
  return;
}


// ================================================================================================
// pull_goalie_logic @ 0x53f8c [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall pull_goalie_logic(int param_1)

{
  bool bVar1;
  int iVar2;
  undefined4 *puVar3;
  char cVar4;
  int iVar5;
  
  __CHK(0x1c);
  bVar1 = false;
  iVar5 = 0;
  if (((byte)option_flags & 2) == 0) {
    return;
  }
  if (dword_cc128 != 0) {
    return;
  }
  if (dword_cc11c != 0) {
    return;
  }
  if (*(short *)(param_1 + 0x6a) < 6) {
    iVar2 = 0;
  }
  else {
    iVar2 = 6;
  }
  puVar3 = &entities + iVar2 * 0x20;
  if ((*(byte *)(param_1 + 0x44) & 0x80) == 0) {
    if ((-0x52 < *(int *)(param_1 + 4) >> 0x10) && (*(short *)(param_1 + 0xe) < 1)) {
      iVar5 = 4;
    }
    if (-(int)*p_puck_y == iVar5 + 0x4e || -(iVar5 + 0x4e) < (int)*p_puck_y) {
      for (cVar4 = '\0'; cVar4 < '\x06'; cVar4 = cVar4 + '\x01') {
        if ((-1 < *(short *)((int)puVar3 + 0x1a)) &&
           (-((int)puVar3[1] >> 0x10) != iVar5 + 0x4e && (int)puVar3[1] >> 0x10 <= -(iVar5 + 0x4e)))
        goto LAB_00054033;
        puVar3 = puVar3 + 0x20;
      }
    }
  }
  else {
    if ((*(short *)(param_1 + 6) < 0x52) && (-1 < *(short *)(param_1 + 0xe))) {
      iVar5 = 4;
    }
    if ((int)*p_puck_y <= iVar5 + 0x4e) {
      for (cVar4 = '\0'; cVar4 < '\x06'; cVar4 = cVar4 + '\x01') {
        if ((-1 < *(short *)((int)puVar3 + 0x1a)) && (iVar5 + 0x4e < (int)puVar3[1] >> 0x10))
        goto LAB_00054033;
        puVar3 = puVar3 + 0x20;
      }
    }
  }
LAB_00054091:
  if (bVar1) {
    if (((((byte)stop_flags & 0x80) == 0) &&
        (stop_flags._0_1_ = (byte)stop_flags | 0x80, _word_cbec8 < 4)) &&
       (*p_puck_y < 0 != ((*(byte *)(param_1 + 0x44) & 0x80) != 0))) {
      _word_cbec8 = 4;
      dword_cbeca._0_2_ = 0;
    }
  }
  else if (((((byte)stop_flags & 0x80) != 0) &&
           (stop_flags._0_1_ = (byte)stop_flags & 0x7f, _word_cbec8 == 4)) &&
          ((short)dword_cbeca == 0)) {
    _word_cbec8 = -1;
  }
  return;
LAB_00054033:
  bVar1 = true;
  goto LAB_00054091;
}


// ================================================================================================
// stickhandling_skill @ 0x54134 [__watcall]
// ================================================================================================

undefined8 __watcall stickhandling_skill(int param_1,undefined4 unaff_EDX)

{
  ushort uVar1;
  uint uVar2;
  
  __CHK(8);
  uVar1 = *(ushort *)(param_1 + 0x38);
  if (uVar1 < 0x101) {
    if (uVar1 < 0xc9) {
      if (uVar1 == 0xb1) {
        if (*(char *)(param_1 + 0x65) == '\0') goto LAB_0005419b;
        goto LAB_00054196;
      }
    }
    else if ((uVar1 < 0xca) || (uVar1 == 0xe1)) {
LAB_00054190:
      if (*(char *)(param_1 + 0x65) != '\0') {
LAB_0005419b:
        uVar2 = (uint)*(byte *)(param_1 + 0x62);
        goto LAB_000541c3;
      }
LAB_00054196:
      uVar2 = (uint)*(byte *)(param_1 + 0x5d);
      goto LAB_000541c3;
    }
  }
  else {
    if (uVar1 < 0x102) {
LAB_000541b8:
      if (*(char *)(param_1 + 0x65) != '\0') {
LAB_000541ae:
        uVar2 = (uint)*(byte *)(param_1 + 0x61);
        goto LAB_000541c3;
      }
LAB_000541b3:
      uVar2 = (uint)*(byte *)(param_1 + 0x5f);
      goto LAB_000541c3;
    }
    if (uVar1 < 0x11d5) {
      if (uVar1 == 0x119) {
        if (*(char *)(param_1 + 0x65) == '\0') goto LAB_000541ae;
        goto LAB_000541b3;
      }
    }
    else {
      if (uVar1 < 0x11d6) goto LAB_00054190;
      if (uVar1 == 0x121d) goto LAB_000541b8;
    }
  }
  uVar2 = (uint)*(byte *)(param_1 + 0x5b);
LAB_000541c3:
  return CONCAT44(unaff_EDX,uVar2);
}


// ================================================================================================
// two_line_pass_check @ 0x541ca [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

longlong __watcall two_line_pass_check(int param_1,uint unaff_EDX)

{
  bool bVar1;
  bool bVar2;
  int iVar3;
  
  __CHK(8);
  if ((((((byte)option_flags & 2) != 0) && ((game_flags & 0x10) == 0)) && (dword_cc128 == 0)) &&
     (dword_cc11c == 0)) {
    iVar3 = (int)*p_puck_y;
    if (iVar3 < 0) {
      iVar3 = -iVar3;
    }
    if (iVar3 < 0xe9) {
      if ((*(byte *)(param_1 + 0x44) & 0x80) == 0) {
        iVar3 = 0;
      }
      else {
        iVar3 = 2;
      }
      iVar3 = *(int *)((int)&unk_df812 + iVar3 * 2) >> 0x10;
      if (iVar3 < 0) {
        iVar3 = -iVar3;
      }
      if ((iVar3 < 0x2d) && ((*(byte *)(*(int *)(param_1 + 0x70) + 0x44) & 0x10) != 0)) {
        bVar1 = *(short *)(param_1 + 0x6a) < 6;
        bVar2 = dword_e9ac2 < 6;
        if (bVar2 == bVar1) {
          return CONCAT44(unaff_EDX,(uint)(bVar2 != bVar1));
        }
        queue_infraction(&entities + (ram0x000e9ac0 >> 0x10) * 0x20,8);
        return CONCAT44(unaff_EDX,1);
      }
    }
  }
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// puck_player_interaction @ 0x5428a [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall puck_player_interaction(int param_1,short unaff_DX)

{
  longlong lVar1;
  uint uVar2;
  short sVar3;
  short sVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  short sVar10;
  ushort extraout_DX;
  ushort uVar11;
  uint uVar12;
  undefined4 *puVar13;
  uint uVar14;
  
  __CHK(0x18);
  uVar2 = CONCAT22(sRam000e03c2,dword_e03be._2_2_);
  uVar14 = CONCAT22((undefined2)dword_e03be,dword_e03ba._2_2_);
  if ((unaff_DX == *p_puck_carrier) || ((0xb < unaff_DX && (unaff_DX != 0x10)))) goto LAB_00054d5d;
  iVar5 = (int)unaff_DX;
  iVar6 = iVar5 * 0x80;
  puVar13 = &entities + iVar5 * 0x20;
  if ((((&unk_df860)[iVar6] & 4) != 0) || ((&unk_df85a)[iVar5 * 0x40] != 0)) goto LAB_00054d5d;
  if ((((&unk_df861)[iVar6] & 4) == 0) && ((&unk_df836)[iVar5 * 0x40] == 0)) {
    sVar3 = stickhandling_skill(puVar13);
    sVar10 = *(short *)p_puck_vx;
    if (sVar10 < 0) {
      sVar10 = -sVar10;
    }
    sVar4 = *(short *)p_puck_vy;
    if (sVar4 < 0) {
      sVar4 = -sVar4;
    }
    sVar4 = sVar4 + sVar10;
    if (sVar4 == 0) {
      sVar4 = 1;
    }
    iVar8 = sVar3 * 0x800 + -4000;
    lVar1 = (longlong)iVar8 / (longlong)(int)sVar4;
    iVar7 = (int)lVar1;
    if ((short)lVar1 < 0) {
      iVar7 = 0;
    }
    if (4 < (short)iVar7) {
      iVar7 = 4;
    }
    stick_offset_from_frame(puVar13,iVar8 % (int)sVar4);
    sVar10 = dword_e03ba._2_2_;
    if (dword_e03ba._2_2_ < 0) {
      sVar10 = -dword_e03ba._2_2_;
    }
    dword_e03b2._2_2_ = (short)(((int)sVar10 << 2) / 3);
    sVar3 = dword_e03be._2_2_;
    if ((short)dword_e03be._2_2_ < 0) {
      sVar3 = -dword_e03be._2_2_;
    }
    dword_e03ae._2_2_ = (undefined2)(((int)sVar3 << 2) / 3);
    dword_e03ac = sVar10 + (short)iVar7;
    frame_offsets_lookup(puVar13,((int)sVar3 << 2) % 3);
    sVar10 = dword_e03ba._2_2_ + (*(short *)((int)&entities + iVar6 + 2) - *p_puck_x);
    if (sVar10 < 0) {
      sVar10 = -sVar10;
    }
    uVar12 = CONCAT22((undefined2)dword_e03be,sVar10);
    uVar9 = CONCAT22(sRam000e03c2,dword_e03be._2_2_);
    if (sVar10 < dword_e03ac) {
      sVar4 = dword_e03be._2_2_ + (*(short *)((int)&unk_df820 + iVar6 + 2) - *p_puck_y);
      if (sVar4 < 0) {
        sVar4 = -sVar4;
      }
      uVar12 = CONCAT22((undefined2)dword_e03be,sVar10);
      uVar9 = CONCAT22(sRam000e03c2,sVar4);
      if (sVar4 < dword_e03ac) {
        if ((short)(dword_e03b2._2_2_ + sVar3) < 6) {
          iVar8 = 5;
        }
        else {
          iVar8 = (int)(short)(dword_e03b2._2_2_ + sVar3);
        }
        uVar12 = CONCAT22((undefined2)dword_e03be,sVar10);
        uVar9 = CONCAT22(sRam000e03c2,sVar4);
        if ((*p_puck_z <= (short)(iVar8 + iVar7)) &&
           ((sVar3 = (sVar3 - dword_e03b2._2_2_) - (short)iVar7, sVar3 < 0 ||
            (uVar12 = CONCAT22((undefined2)dword_e03be,sVar10), uVar9 = CONCAT22(sRam000e03c2,sVar4)
            , sVar3 < *p_puck_z)))) {
          uVar12 = (int)sVar10 * (int)sVar10 + (int)sVar4 * (int)sVar4;
          dword_e03ba._2_2_ = (short)uVar12;
          dword_e03be._0_2_ = (undefined2)(uVar12 >> 0x10);
          uVar9 = (ram0x000e03aa >> 0x10) * (ram0x000e03aa >> 0x10);
          if (0 < *(short *)(param_1 + 0x3e)) {
            dword_e03be._2_2_ = (ushort)((int)uVar9 >> 2);
            sRam000e03c2 = (short)((int)uVar9 >> 0x12);
            uVar9 = CONCAT22(sRam000e03c2,dword_e03be._2_2_);
          }
          sRam000e03c2 = (short)(uVar9 >> 0x10);
          dword_e03be._2_2_ = (ushort)uVar9;
          if (dword_e03ba._2_2_ <= (short)dword_e03be._2_2_) {
            two_line_pass_check(puVar13);
            goalie_save(param_1,puVar13);
            uVar12 = CONCAT22((undefined2)dword_e03be,dword_e03ba._2_2_);
            uVar9 = CONCAT22(sRam000e03c2,dword_e03be._2_2_);
          }
        }
      }
    }
  }
  else {
    uVar12 = CONCAT22((undefined2)dword_e03be,dword_e03ba._2_2_);
    uVar9 = CONCAT22(sRam000e03c2,dword_e03be._2_2_);
    if (((((&unk_df861)[iVar6] & 4) == 0) &&
        (((uVar12 = CONCAT22((undefined2)dword_e03be,dword_e03ba._2_2_),
          uVar9 = CONCAT22(sRam000e03c2,dword_e03be._2_2_), -1 < (short)(&unk_df836)[iVar5 * 0x40]
          && (uVar12 = CONCAT22((undefined2)dword_e03be,dword_e03ba._2_2_),
             uVar9 = CONCAT22(sRam000e03c2,dword_e03be._2_2_), unaff_DX != 0x10)) &&
         (uVar12 = CONCAT22((undefined2)dword_e03be,dword_e03ba._2_2_),
         uVar9 = CONCAT22(sRam000e03c2,dword_e03be._2_2_), *(short *)(param_1 + 10) < 6)))) &&
       (uVar12 = uVar14, uVar9 = uVar2, *(short *)(param_1 + 0x10) < 0x201)) {
      frame_offsets_lookup(puVar13);
      sVar10 = dword_e03ba._2_2_ +
               (*(short *)((int)&entities + iVar6 + 2) - *(short *)(param_1 + 2));
      if (sVar10 < 0) {
        iVar8 = -(int)sVar10;
      }
      else {
        iVar8 = (int)sVar10;
      }
      uVar12 = CONCAT22((undefined2)dword_e03be,sVar10);
      uVar9 = CONCAT22(sRam000e03c2,dword_e03be._2_2_);
      if (iVar8 < 0xf) {
        sVar3 = dword_e03be._2_2_ +
                (*(short *)((int)&unk_df820 + iVar6 + 2) - *(short *)(param_1 + 6));
        if (sVar3 < 0) {
          iVar8 = -(int)sVar3;
        }
        else {
          iVar8 = (int)sVar3;
        }
        uVar12 = CONCAT22((undefined2)dword_e03be,sVar10);
        uVar9 = CONCAT22(sRam000e03c2,sVar3);
        if (iVar8 < 0xf) {
          uVar12 = (int)sVar10 * (int)sVar10 + (int)sVar3 * (int)sVar3;
          dword_e03ba._2_2_ = (short)uVar12;
          dword_e03be._0_2_ = (undefined2)(uVar12 >> 0x10);
          dword_e03be._2_2_ = 0xc4;
          sRam000e03c2 = 0;
          if (0 < *(short *)(param_1 + 0x3e)) {
            dword_e03be._2_2_ = 0x31;
          }
          uVar9 = (uint)dword_e03be._2_2_;
          if ((uVar12 <= dword_e03be._2_2_) &&
             ((((short)(&DAT_000df82e)[iVar5 * 0x40] < 0x430 ||
               (0x44f < (short)(&DAT_000df82e)[iVar5 * 0x40])) ||
              (uVar9 = (uint)dword_e03be._2_2_, uVar12 < 0x25)))) {
            goalie_save(param_1,puVar13);
            uVar2 = CONCAT22(sRam000e03c2,dword_e03be._2_2_);
            uVar14 = CONCAT22((undefined2)dword_e03be,dword_e03ba._2_2_);
            goto LAB_00054d5d;
          }
        }
      }
    }
  }
  sRam000e03c2 = (short)(uVar9 >> 0x10);
  dword_e03be._2_2_ = (ushort)uVar9;
  dword_e03be._0_2_ = (undefined2)(uVar12 >> 0x10);
  dword_e03ba._2_2_ = (short)uVar12;
  if ((&unk_df836)[iVar5 * 0x40] == 0) {
    dword_e03ba._2_2_ = *(short *)((int)&entities + iVar6 + 2) - *(short *)(param_1 + 2);
    if (dword_e03ba._2_2_ < 0) {
      iVar5 = -(int)dword_e03ba._2_2_;
    }
    else {
      iVar5 = (int)dword_e03ba._2_2_;
    }
    uVar14 = CONCAT22((undefined2)dword_e03be,dword_e03ba._2_2_);
    uVar2 = uVar9;
    if (iVar5 < 0xb) {
      dword_e03be._2_2_ = *(short *)((int)&unk_df820 + iVar6 + 2) - *(short *)(param_1 + 6);
      if ((short)dword_e03be._2_2_ < 0) {
        iVar5 = -(int)(short)dword_e03be._2_2_;
      }
      else {
        iVar5 = (int)(short)dword_e03be._2_2_;
      }
      uVar14 = CONCAT22((undefined2)dword_e03be,dword_e03ba._2_2_);
      uVar2 = CONCAT22(sRam000e03c2,dword_e03be._2_2_);
      if ((iVar5 < 0xb) &&
         (uVar14 = CONCAT22((undefined2)dword_e03be,dword_e03ba._2_2_),
         uVar2 = CONCAT22(sRam000e03c2,dword_e03be._2_2_),
         (uint)((int)(short)dword_e03be._2_2_ * (int)(short)dword_e03be._2_2_ +
               (int)dword_e03ba._2_2_ * (int)dword_e03ba._2_2_) < 0x65)) {
        two_line_pass_check(puVar13);
        puck_hits_player(param_1,puVar13);
        uVar14 = CONCAT22((undefined2)dword_e03be,dword_e03ba._2_2_);
        uVar2 = CONCAT22(sRam000e03c2,dword_e03be._2_2_);
      }
    }
    goto LAB_00054d5d;
  }
  uVar11 = (&DAT_000df82e)[iVar5 * 0x40];
  if (((((short)uVar11 < 0x431) || (0x44f < (short)uVar11)) || ((uVar11 & 1) == 0)) ||
     (7 < *p_puck_z)) {
LAB_000547f1:
    sRam000e03c2 = (short)(uVar9 >> 0x10);
    sVar3 = 8;
    sVar10 = 0x40;
    if (0x44f < (short)uVar11) {
      sVar3 = 0x10;
      sVar10 = 0x100;
    }
    sVar4 = *(short *)((int)&entities + iVar6 + 2) - *(short *)(param_1 + 2);
    if (sVar4 < 0) {
      iVar5 = -(int)sVar4;
    }
    else {
      iVar5 = (int)sVar4;
    }
    uVar14 = CONCAT22((undefined2)dword_e03be,sVar4);
    uVar2 = uVar9;
    if (sVar3 < iVar5) goto LAB_00054d5d;
    dword_e03be._2_2_ = *(short *)((int)&unk_df820 + iVar6 + 2) - *(short *)(param_1 + 6);
    if ((short)dword_e03be._2_2_ < 0) {
      iVar5 = -(int)(short)dword_e03be._2_2_;
    }
    else {
      iVar5 = (int)(short)dword_e03be._2_2_;
    }
    uVar14 = CONCAT22((undefined2)dword_e03be,sVar4);
    uVar2 = CONCAT22(sRam000e03c2,dword_e03be._2_2_);
    if ((sVar3 < iVar5) ||
       (uVar14 = (int)sVar4 * (int)sVar4 +
                 (int)(short)dword_e03be._2_2_ * (int)(short)dword_e03be._2_2_,
       uVar2 = CONCAT22(sRam000e03c2,dword_e03be._2_2_), (uint)(int)sVar10 < uVar14))
    goto LAB_00054d5d;
  }
  else {
    stick_offsets_lookup(puVar13);
    sVar3 = dword_e03ba._2_2_ >> 1;
    dword_e03be._2_2_ = (short)dword_e03be._2_2_ >> 1;
    sVar10 = sVar3;
    if (sVar3 < 0) {
      sVar10 = -sVar3;
    }
    sVar3 = sVar3 + (*(short *)((int)&entities + iVar6 + 2) - *(short *)(param_1 + 2));
    if (sVar3 < 0) {
      iVar5 = -(int)sVar3;
    }
    else {
      iVar5 = (int)sVar3;
    }
    uVar11 = extraout_DX;
    uVar9 = CONCAT22(sRam000e03c2,dword_e03be._2_2_);
    if (sVar10 < iVar5) goto LAB_000547f1;
    dword_e03be._2_2_ =
         dword_e03be._2_2_ + (*(short *)((int)&unk_df820 + iVar6 + 2) - *(short *)(param_1 + 6));
    if ((short)dword_e03be._2_2_ < 0) {
      iVar5 = -(int)(short)dword_e03be._2_2_;
    }
    else {
      iVar5 = (int)(short)dword_e03be._2_2_;
    }
    iVar8 = (int)sVar10;
    uVar9 = CONCAT22(sRam000e03c2,dword_e03be._2_2_);
    if (iVar8 < iVar5) goto LAB_000547f1;
    uVar14 = (int)sVar3 * (int)sVar3 + (int)(short)dword_e03be._2_2_ * (int)(short)dword_e03be._2_2_
    ;
    dword_e03be._0_2_ = (undefined2)(uVar14 >> 0x10);
    uVar9 = CONCAT22(sRam000e03c2,dword_e03be._2_2_);
    if ((uint)(iVar8 * iVar8) < uVar14) goto LAB_000547f1;
  }
  dword_e03be._0_2_ = (undefined2)(uVar14 >> 0x10);
  dword_e03ba._2_2_ = (short)uVar14;
  attach_puck_to_stick(param_1,puVar13);
  uVar2 = CONCAT22(sRam000e03c2,dword_e03be._2_2_);
  uVar14 = CONCAT22((undefined2)dword_e03be,dword_e03ba._2_2_);
LAB_00054d5d:
  sRam000e03c2 = (short)(uVar2 >> 0x10);
  dword_e03be._2_2_ = (ushort)uVar2;
  dword_e03be._0_2_ = (undefined2)(uVar14 >> 0x10);
  dword_e03ba._2_2_ = (short)uVar14;
  return;
}


// ================================================================================================
// puck_check_players @ 0x548ac [__watcall]
// ================================================================================================

void __watcall puck_check_players(int param_1)

{
  int iVar1;
  short sVar2;
  
  __CHK(0x14);
  if (*(short *)(param_1 + 6) < 0) {
    iVar1 = -(*(int *)(param_1 + 4) >> 0x10);
  }
  else {
    iVar1 = *(int *)(param_1 + 4) >> 0x10;
  }
  if (400 < iVar1) {
    *(undefined2 *)(param_1 + 0xe) = 0;
    *(undefined2 *)(param_1 + 0xc) = *(undefined2 *)(param_1 + 0xe);
  }
  if (*(short *)(param_1 + 10) < 0x11) {
    sVar2 = (&draw_order_pos)[*(int *)(param_1 + 0x68) >> 0x10];
    while ((sVar2 != 0x10 &&
           ((*(int *)(&unk_e9a56 + (*(int *)((int)&draw_order_list + sVar2 + 1) >> 0x18) * 2) >>
            0x10) - (*(int *)(param_1 + 4) >> 0x10) < 0x29))) {
      puck_player_interaction(param_1,(int)(short)(char)(&unk_e9adf)[sVar2]);
      sVar2 = sVar2 + 1;
    }
    sVar2 = (&draw_order_pos)[*(int *)(param_1 + 0x68) >> 0x10];
    while ((sVar2 != 0 &&
           ((*(int *)(param_1 + 4) >> 0x10) -
            (*(int *)(&unk_e9a56 + (*(int *)((int)&byte_e9ad7 + sVar2 + 3) >> 0x18) * 2) >> 0x10) <
            0x29))) {
      puck_player_interaction(param_1,(int)(short)(char)(&unk_e9add)[sVar2]);
      sVar2 = sVar2 + -1;
    }
  }
  return;
}


// ================================================================================================
// sub_54990 @ 0x54990 [__watcall]
// ================================================================================================

undefined4 __watcall sub_54990(int param_1)

{
  short sVar1;
  short sVar2;
  int iVar3;
  int extraout_EDX;
  
  __CHK(0x10);
  sVar2 = randomrange(0x20);
  if (sVar2 == 0) {
    sVar2 = *p_puck_y - *(short *)(extraout_EDX + 6);
    if (sVar2 < 0) {
      iVar3 = -(int)sVar2;
    }
    else {
      iVar3 = (int)sVar2;
    }
    if (iVar3 < 0x29) {
      sVar2 = *(short *)(param_1 + 0xc);
      sVar1 = *(short *)(param_1 + 0xe);
      if (sVar2 < 0) {
        iVar3 = -(int)sVar2;
      }
      else {
        iVar3 = (int)sVar2;
      }
      if (iVar3 < 0x1b59) {
        if (sVar1 < 0) {
          iVar3 = -(int)sVar1;
        }
        else {
          iVar3 = (int)sVar1;
        }
        if (iVar3 < 0x1b59) {
          return 0;
        }
      }
      *(short *)(extraout_EDX + 0xc) = sVar2 >> 2;
      *(short *)(extraout_EDX + 0xe) = sVar1 >> 2;
      *(undefined2 *)(param_1 + 0xc) = 0;
      *(undefined2 *)(param_1 + 0xe) = 0;
      action_flags = action_flags | 0x40;
      if ((game_flags & 1) == 0) {
        queue_infraction(param_1,0x1e);
      }
      return 1;
    }
  }
  return 0;
}


// ================================================================================================
// sub_54a53 @ 0x54a53 [__watcall]
// ================================================================================================

undefined8 __watcall sub_54a53(undefined4 param_1,undefined4 unaff_EDX)

{
  char cVar1;
  short sVar2;
  ushort uVar3;
  int iVar4;
  char *pcVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  
  __CHK(0x18);
  if ((short)(dword_df648._2_2_ - dword_df748._2_2_) < 1) {
    if (-1 < (short)(dword_df648._2_2_ - dword_df748._2_2_)) {
      iVar6 = 0;
      goto LAB_0005412e;
    }
    iVar7 = 0xdf714;
    iVar8 = 0xdf614;
  }
  else {
    iVar7 = 0xdf614;
    iVar8 = 0xdf714;
  }
  iVar4 = 0;
  iVar6 = 0;
  pcVar5 = (char *)(iVar8 + 0xb6);
  while( true ) {
    cVar1 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    if (cVar1 < '\0') break;
    sVar2 = *(short *)(iVar8 + 0x7e + (short)cVar1 * 2);
    if (-1 < sVar2) {
      iVar4 = (CONCAT22((short)cVar1 >> 0xf,sVar2) & 0xffff3fff) - iVar4;
      iVar6 = iVar6 + iVar4;
    }
  }
  if (*(short *)(iVar7 + 0x36) != 6) {
    iVar6 = iVar6 - iVar4;
    pcVar5 = (char *)(iVar7 + 0xb6);
    do {
      cVar1 = *pcVar5;
      pcVar5 = pcVar5 + 1;
      if (cVar1 < '\0') goto LAB_0005412e;
      uVar3 = *(ushort *)(iVar7 + 0x7e + (short)cVar1 * 2);
    } while ((short)uVar3 < 0);
    if ((short)(uVar3 & 0x3fff) <= (short)iVar6) {
      iVar6 = iVar6 + iVar4;
    }
  }
LAB_0005412e:
  return CONCAT44(unaff_EDX,iVar6);
}


// ================================================================================================
// ai_consider_shot @ 0x54af9 [__watcall]
// ================================================================================================

undefined8 __watcall ai_consider_shot(int param_1,undefined4 unaff_EDX)

{
  int iVar1;
  int iVar2;
  short sVar3;
  undefined4 uVar4;
  uint uVar5;
  short extraout_DX;
  
  __CHK(0x18);
  if ((((byte)option_flags & 4) != 0) && (dword_cc128 == 0)) {
    dword_e03ba._2_2_ = *p_puck_y;
    if ((*(byte *)(param_1 + 0x44) & 0x80) == 0) {
      dword_e03ba._2_2_ = -dword_e03ba._2_2_;
    }
    if ((((-1 < (short)dword_e03ba._2_2_) && ((short)dword_e03ba._2_2_ < 0x4f)) &&
        (sVar3 = randomrange(4), sVar3 == 0)) && ((*(byte *)(param_1 + 0x45) & 8) == 0)) {
      iVar1 = *(int *)(param_1 + 0x6c);
      iVar2 = *(int *)(param_1 + 0x70);
      sVar3 = *(short *)(iVar1 + 0x36) - *(short *)(iVar2 + 0x36);
      if ((*(byte *)(iVar1 + 0xd4) & 0x40) == 0) {
        sub_5a03b(iVar1);
        if ((0xe < clock_seconds) && ((0x1d < clock_seconds || (dword_e03ba._2_2_ < 0x801)))) {
          if (extraout_DX == 0) {
            uVar5 = *(uint *)(iVar1 + 0xd6);
          }
          else {
            uVar5 = 0xf33;
          }
          sVar3 = extraout_DX;
          if (dword_e03ba._2_2_ <= uVar5) goto LAB_00054b8c;
        }
      }
      else if (0xe < clock_seconds) {
LAB_00054b8c:
        if ((sVar3 == 0) || (sVar3 = sub_54a53(), 0xe < sVar3)) {
          choose_line(iVar2,iVar1);
          apply_line_change(iVar1);
          ai_desperation_shot(param_1);
          uVar4 = 1;
          goto LAB_0005412e;
        }
      }
    }
  }
  uVar4 = 0;
LAB_0005412e:
  return CONCAT44(unaff_EDX,uVar4);
}


// ================================================================================================
// sub_54c09 @ 0x54c09 [__watcall]
// ================================================================================================

undefined4 __watcall sub_54c09(int *param_1,int *unaff_EDX)

{
  short sVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  bool bVar7;
  undefined8 uVar8;
  
  __CHK(0x1c);
  bVar7 = (*(byte *)(param_1 + 0x11) & 0x80) != 0;
  if (*(short *)((int)param_1 + 0x1a) != 0) {
    uVar8 = count_defenders_ahead(bVar7,bVar7);
    uVar3 = (uint)((ulonglong)uVar8 >> 0x20);
    if ((int)uVar8 == 0) {
      iVar5 = unaff_EDX[1] >> 0x10;
      iVar2 = param_1[1] >> 0x10;
      if (bVar7) {
        iVar6 = 0x4e;
      }
      else {
        iVar6 = -0x4e;
      }
      if (iVar6 < iVar2 == uVar3) {
        iVar6 = iVar2;
        if (iVar2 < 0) {
          iVar6 = -iVar2;
        }
        iVar4 = iVar5;
        if (iVar5 < 0) {
          iVar4 = -iVar5;
        }
        if (iVar4 < iVar6) {
          iVar6 = iVar2;
          if (iVar2 < 0) {
            iVar6 = -iVar2;
          }
          if ((((iVar6 < 0x77) &&
               ((uVar3 == 0 ||
                ((-1 < *(short *)((int)unaff_EDX + 0xe) && (-1 < *(short *)((int)param_1 + 0xe))))))
               ) && ((uVar3 != 0 ||
                     ((*(short *)((int)unaff_EDX + 0xe) < 1 && (*(short *)((int)param_1 + 0xe) < 1))
                     )))) && (-1 < (int)(((unaff_EDX[3] >> 0x18) + iVar5) - 0x4eU ^ iVar2 - 0x4eU)))
          {
            iVar5 = iVar5 - iVar2;
            if (iVar5 < 0) {
              iVar5 = -iVar5;
            }
            if (iVar5 < 0x3d) {
              iVar2 = (*param_1 >> 0x10) - (*unaff_EDX >> 0x10);
              if (iVar2 < 0) {
                iVar2 = -iVar2;
              }
              if (iVar2 < 0x29) {
                sVar1 = direction8(*(int *)((int)unaff_EDX + 10) >> 0x10,unaff_EDX[3] >> 0x10);
                iVar2 = (int)sVar1;
                if (iVar2 == 8) {
                  iVar2 = unaff_EDX[0xd] >> 0x10;
                }
                sVar1 = direction8((int)(short)(*(short *)((int)param_1 + 2) -
                                               *(short *)((int)unaff_EDX + 2)),
                                   (int)(short)(*(short *)((int)param_1 + 6) -
                                               *(short *)((int)unaff_EDX + 6)));
                if (((iVar2 - sVar1) + 1U & 7) < 3) {
                  return 1;
                }
              }
            }
          }
        }
      }
    }
  }
  return 0;
}


// ================================================================================================
// pass_to_entity @ 0x54d63 [__watcall]
// ================================================================================================

void __watcall pass_to_entity(int param_1,int unaff_EDX)

{
  short *psVar1;
  undefined2 uVar2;
  
  __CHK(0xc);
  *(undefined2 *)(param_1 + 0x3e) = 0x28;
  if ((game_flags & 0x10) == 0) {
    psVar1 = (short *)(*(int *)(param_1 + 0x6c) + 0x26);
    *psVar1 = *psVar1 + 1;
  }
  shot_power._2_2_ = *(undefined2 *)(unaff_EDX + 0x6a);
  *(undefined *)(param_1 + 0x53) = 0;
  set_state_reset(unaff_EDX,0x13);
  *(undefined2 *)p_puck_vz = 0;
  uVar2 = randomrange((int)(short)((0x12 - (ushort)*(byte *)(param_1 + 0x5d)) * 0x14));
  *(undefined2 *)p_puck_vx = uVar2;
  uVar2 = randomrange((int)(short)((0x12 - (ushort)*(byte *)(param_1 + 0x5d)) * 0x14));
  *(undefined2 *)p_puck_vy = uVar2;
  word_dff5a = 0;
  return;
}


// ================================================================================================
// do_pass @ 0x54df4 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall do_pass(undefined4 *param_1)

{
  uint uVar1;
  short sVar2;
  ushort uVar3;
  undefined2 uVar4;
  int iVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  uint uVar9;
  int iVar10;
  ushort uStackY_1c;
  
  __CHK(0x28);
  dword_cc0f4 = 0;
  action_flags = action_flags & 0xfb;
  *p_puck_carrier = 0xff;
  *(undefined2 *)((int)param_1 + 0x3e) = 0x10;
  dword_c90a2 = *(undefined2 *)((int)param_1 + 0x6a);
  if (((*(byte *)(param_1 + 0x11) & 8) == 0) && (*(char *)((int)param_1 + 0x53) != '\0')) {
    puVar8 = &entities + (*(int *)((int)param_1 + 0x46) >> 0x10) * 0x20;
LAB_00054e4c:
    pass_to_entity(param_1,puVar8);
  }
  else {
    if (*(short *)((int)param_1 + 0x1a) == 0) {
      uStackY_1c = 8;
    }
    else {
      uStackY_1c = (ushort)*(byte *)((int)param_1 + 0x5d);
    }
    shot_power._0_2_ = uStackY_1c * 4 + 0xa0;
    if (*(short *)((int)param_1 + 0x6a) < 6) {
      iVar5 = 0;
    }
    else {
      iVar5 = 6;
    }
    puVar7 = &entities + iVar5 * 0x20;
    uVar1 = 0xffffffff;
    puVar8 = (undefined4 *)0x0;
    uStackY_1c = 6;
    do {
      if (((param_1 != puVar7) && (0 < *(short *)((int)puVar7 + 0x1a))) &&
         ((*(byte *)((int)puVar7 + 0x45) & 4) == 0)) {
        iVar10 = (int)(short)(*(short *)((int)puVar7 + 2) - *p_puck_x);
        iVar5 = (int)(short)(*(short *)((int)puVar7 + 6) - *p_puck_y);
        sVar2 = direction8(iVar10,iVar5);
        uVar3 = sVar2 - pending_dir & 7;
        if ((uVar3 < 2) || (uVar3 == 7)) {
          if (uVar3 == 0) {
            iVar6 = 0;
          }
          else {
            iVar6 = 0x10000;
          }
          uVar9 = iVar5 * iVar5 + iVar10 * iVar10 + iVar6;
          if (uVar9 <= uVar1) {
            puVar8 = puVar7;
            uVar1 = uVar9;
          }
        }
      }
      puVar7 = puVar7 + 0x20;
      uStackY_1c = uStackY_1c + -1;
    } while (uStackY_1c != 0);
    if (puVar8 == (undefined4 *)0x0) {
      iVar5 = (int)(short)shot_power;
      *(short *)p_puck_vy =
           (short)(((*(int *)(&dir8_vectors + pending_dir * 4) >> 0x10) * iVar5 * 0x400) / 3000) +
           *(short *)((int)param_1 + 0xe);
      *(short *)p_puck_vx =
           (short)(((*(int *)(&clock_sub + pending_dir * 2) >> 0x10) * iVar5 * 0x400) / 3000) +
           *(short *)(param_1 + 3);
      uVar4 = randomrange(0x1000);
      *(undefined2 *)p_puck_vz = uVar4;
    }
    else {
      if (((*(byte *)(param_1 + 0x11) & 8) != 0) && (iVar5 = sub_54c09(param_1,puVar8), iVar5 != 0))
      goto LAB_00054e4c;
      sub_551cf(puVar8);
    }
    if (*(short *)((int)param_1 + 0x1a) == 0) {
      if (*(short *)p_puck_vy < 0 != ((*(byte *)(param_1 + 0x11) & 0x80) == 0)) {
        *(short *)p_puck_vy = -*(short *)p_puck_vy;
      }
      uStackY_1c = 0x1b9;
      *(byte *)((int)param_1 + 0x45) = *(byte *)((int)param_1 + 0x45) | 2;
      if ((*(byte *)(param_1 + 0x11) & 8) != 0) {
        if ((puVar8 == (undefined4 *)0x0) || ((*(byte *)(puVar8 + 0x11) & 8) != 0)) {
          if (*(short *)((int)param_1 + 0x6a) == _user1_slot) {
            uVar4 = 0;
          }
          else {
            uVar4 = 2;
          }
          switch_to_nearest(param_1,uVar4);
        }
        else if (*(short *)((int)param_1 + 0x6a) == _user1_slot) {
          if (_user1_slot != *(short *)((int)puVar8 + 0x6a)) {
            _user1_slot = find_switch_target((int)puVar8[0x1a] >> 0x10,(int)_user1_slot);
          }
        }
        else if (*(short *)((int)puVar8 + 0x6a) != user2_slot) {
          user2_slot = find_switch_target((int)puVar8[0x1a] >> 0x10,(int)user2_slot);
        }
      }
    }
    else {
      sVar2 = direction8((int)*(short *)p_puck_vx,(int)*(short *)p_puck_vy);
      sVar2 = shot_is_backhand(param_1,(int)sVar2);
      if (sVar2 == 0) {
        uStackY_1c = 0x389;
      }
      else {
        uStackY_1c = 0x3c1;
      }
    }
    set_animation(param_1,uStackY_1c);
    *(byte *)(param_1 + 0x11) = *(byte *)(param_1 + 0x11) | 0x20;
    play_sfx(('\x05' < (char)p_puck_vz[1]) + 0x98);
  }
  return;
}


// ================================================================================================
// pass_button @ 0x5514e [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall pass_button(int param_1)

{
  __CHK(8);
  if (((byte)dword_e03ac & 0x10) == 0) {
    if ((dword_e03ba._2_2_ & 8) != 0) {
      return;
    }
    pending_dir = dword_e03ba._2_2_ & 7;
    dword_e03ba._2_2_ = dword_e03ba._2_2_ | 8;
    if (((*(byte *)(param_1 + 0x44) & 8) != 0) &&
       ((&controller_type)[*(short *)(param_1 + 0x6a) != _user1_slot] == '\x01')) {
      return;
    }
  }
  do_pass();
  return;
}


// ================================================================================================
// shoot_button @ 0x551af [__watcall]
// ================================================================================================

void __watcall shoot_button(int param_1)

{
  __CHK(4);
  pending_dir = *(ushort *)(param_1 + 0x36) & 7;
  action_flags = action_flags | 4;
  return;
}


// ================================================================================================
// sub_551cf @ 0x551cf [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall sub_551cf(int param_1)

{
  short *psVar1;
  short sVar2;
  char cVar3;
  short sVar4;
  short sVar5;
  int iVar6;
  int iVar7;
  short sVar8;
  short sVar9;
  short sVar10;
  short sVar11;
  short sVar12;
  undefined2 uStack_2e;
  char cStack_2c;
  undefined uStack_2b;
  short sStack_18;
  
  __CHK(0x38);
  if ((game_flags & 0x10) == 0) {
    psVar1 = (short *)(*(int *)(param_1 + 0x6c) + 0x26);
    *psVar1 = *psVar1 + 1;
  }
  shot_power._2_2_ = *(undefined2 *)(param_1 + 0x6a);
  set_state_reset(param_1,0x13);
  frame_offsets_lookup(param_1);
  sVar8 = (dword_e03ba._2_2_ + *(short *)(param_1 + 2)) - *p_puck_x;
  sVar9 = (dword_e03be._2_2_ + *(short *)(param_1 + 6)) - *p_puck_y;
  sVar4 = (short)((uint)((*(int *)(param_1 + 10) >> 0x10) * 0xf0) >> 0x10);
  sVar5 = (short)((uint)((*(int *)(param_1 + 0xc) >> 0x10) * 0xf0) >> 0x10);
  sVar11 = sVar8 >> 2;
  sVar2 = sVar9 >> 2;
  sVar12 = (sVar4 * sVar11 + sVar5 * sVar2) * 2;
  sVar10 = (short)((int)_pending_dir >> 0x12);
  sStack_18 = (sVar4 * sVar4 + sVar5 * sVar5) - sVar10 * sVar10;
  iVar6 = (int)sVar12 * (int)sVar12 +
          ((int)sVar2 * (int)sVar2 + (int)sVar11 * (int)sVar11) * (int)sStack_18 * -4;
  if (iVar6 < 1) {
    iVar6 = 0;
  }
  else {
    iVar6 = sub_93470((short)iVar6);
  }
  sStack_18 = sStack_18 >> 2;
  if (sStack_18 == 0) {
    sStack_18 = 1;
  }
  for (sVar11 = 0; sVar11 < 2; sVar11 = sVar11 + 1) {
    cStack_2c = (char)iVar6;
    uStack_2b = (undefined)((uint)iVar6 >> 8);
    iVar6 = -iVar6;
    iVar7 = ((CONCAT13(uStack_2b,CONCAT12(cStack_2c,uStack_2e)) >> 0x10) - (int)sVar12) /
            (int)sStack_18;
    cStack_2c = (char)iVar7;
    uStack_2b = (undefined)((uint)iVar7 >> 8);
    if (-1 < (short)iVar7) break;
  }
  if (CONCAT11(uStack_2b,cStack_2c) < 1) {
    cStack_2c = '\x01';
    uStack_2b = 0;
  }
  if (0x18 < CONCAT11(uStack_2b,cStack_2c)) {
    cStack_2c = '\x18';
    uStack_2b = 0;
  }
  cVar3 = cStack_2c;
  if (0xb < CONCAT11(uStack_2b,cStack_2c)) {
    cVar3 = '\f';
  }
  sVar12 = (short)cVar3;
  if (6 < sVar12) {
    cVar3 = randomrange((int)(sVar12 / 2));
    cVar3 = cVar3 + (char)((sVar12 + 1) / 2);
  }
  p_puck_vz[1] = cVar3;
  *(char *)(param_1 + 0x27) = cStack_2c * '\b' + -10;
  word_dff5a = (char)((uint)*(undefined4 *)(param_1 + 0x24) >> 0x18) + -6;
  iVar6 = CONCAT13(uStack_2b,CONCAT12(cStack_2c,uStack_2e)) >> 0x10;
  register0x00000004 = (sVar4 * iVar6 >> 1) + (int)sVar8;
  *(short *)(param_1 + 0x2a) = *p_puck_x + dword_e03ba._2_2_;
  register0x00000008 = (iVar6 * sVar5 >> 1) + (int)sVar9;
  *(short *)(param_1 + 0x2c) = *p_puck_y + dword_e03be._2_2_;
  sVar12 = CONCAT11(uStack_2b,cStack_2c) * 0x78;
  cStack_2c = (char)sVar12;
  uStack_2b = (undefined)((ushort)sVar12 >> 8);
  iVar6 = sub_53294(ram0x000e03bc);
  iVar7 = CONCAT13(uStack_2b,CONCAT12(cStack_2c,uStack_2e)) >> 0x10;
  *(short *)p_puck_vx = (short)(iVar6 / iVar7);
  iVar6 = sub_53294(ram0x000e03c0,iVar6 % iVar7);
  *(short *)p_puck_vy = (short)(iVar6 / iVar7);
  return;
}


// ================================================================================================
// ai_choose_pass_target @ 0x55493 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 __watcall ai_choose_pass_target(int param_1,undefined4 unaff_EDX)

{
  ushort uVar1;
  short sVar2;
  char cVar3;
  byte bVar4;
  short sVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  undefined4 extraout_EDX;
  undefined4 uVar10;
  undefined4 *puVar11;
  undefined2 extraout_var;
  
  __CHK(0x18);
  *(undefined *)(param_1 + 0x53) = 0;
  if ((dword_c90aa == 0) &&
     (sVar5 = randomrange(*(byte *)(param_1 + 0x5f) + 0x10), uVar10 = extraout_EDX, 9 < sVar5))
  goto LAB_0005412e;
  sVar5 = randomrange(6);
  if (5 < *(short *)(param_1 + 0x6a)) {
    sVar5 = sVar5 + 6;
  }
  dword_e03ba = CONCAT22(sVar5,(undefined2)dword_e03ba);
  if (sVar5 != *(short *)(param_1 + 0x6a)) {
    iVar8 = (int)sVar5;
    iVar9 = iVar8 * 0x80;
    if (((0 < (short)(&unk_df836)[iVar8 * 0x40]) && (((&unk_df861)[iVar9] & 4) == 0)) &&
       (((&unk_df860)[iVar9] & 0x20) == 0)) {
      if ((*(short *)(param_1 + 0x1a) != 0) &&
         (0 < *p_puck_y != ((*(byte *)(param_1 + 0x44) & 0x80) != 0))) {
        uVar1 = *p_puck_x;
        if ((short)uVar1 < 0) {
          iVar6 = -(int)(short)uVar1;
        }
        else {
          iVar6 = (int)(short)uVar1;
        }
        if (iVar6 < 0x33) {
          sVar5 = *p_puck_y;
          if (sVar5 < 0) {
            iVar6 = -(int)sVar5;
          }
          else {
            iVar6 = (int)sVar5;
          }
          if (0xac < iVar6) {
            sVar5 = *p_puck_y;
            if (sVar5 < 0) {
              iVar6 = -(int)sVar5;
            }
            else {
              iVar6 = (int)sVar5;
            }
            if (0xea < iVar6) {
              uVar1 = *(ushort *)((int)&entities + iVar9 + 2);
              dword_e03ba = CONCAT22(uVar1,(undefined2)dword_e03ba);
              sVar5 = *(short *)((int)&unk_df820 + iVar9 + 2);
              dword_e03be = CONCAT22(sVar5,(undefined2)dword_e03be);
              iVar6 = (int)(short)uVar1;
              if ((short)uVar1 < 0) {
                iVar6 = -iVar6;
              }
              if (0x3b < iVar6) {
                if ((short)(uVar1 ^ *p_puck_x) < 0) {
                  sVar2 = *p_puck_y;
                  if (sVar2 < 0) {
                    iVar6 = -(int)sVar2;
                  }
                  else {
                    iVar6 = (int)sVar2;
                  }
                  iVar7 = (int)sVar5;
                  if (sVar5 < 0) {
                    iVar7 = -iVar7;
                  }
                  if ((int)(iVar7 - 0xe8U ^ iVar6 - 0xe8U) < 0) goto LAB_000554fc;
                }
                goto LAB_00055656;
              }
            }
            goto LAB_000554fc;
          }
        }
      }
LAB_00055656:
      sVar5 = *(short *)((int)&unk_df820 + iVar9 + 2);
      dword_e03ba._2_2_ = sVar5;
      dword_e03be._2_2_ = *(short *)(param_1 + 6);
      if ((*(byte *)(param_1 + 0x44) & 0x80) == 0) {
        dword_e03ba._2_2_ = -sVar5;
        dword_e03be._2_2_ = -*(short *)(param_1 + 6);
      }
      if ((((byte)option_flags & 2) == 0) ||
         (-1 < (int)((int)dword_e03be._2_2_ - 0x4eU ^ (int)dword_e03ba._2_2_ - 0x4eU))) {
        if ((dword_e03ba._2_2_ < 0x4f) &&
           (sVar5 = dword_e03ba._2_2_ - dword_e03be._2_2_,
           dword_e03ba = CONCAT22(sVar5,(undefined2)dword_e03ba), sVar5 < -0xf)) {
          cVar3 = sub_54c09(param_1,&entities + iVar8 * 0x20);
          *(char *)(param_1 + 0x53) = cVar3;
          goto joined_r0x000556f3;
        }
      }
      else {
        cVar3 = sub_54c09(param_1,&entities + iVar8 * 0x20);
        *(char *)(param_1 + 0x53) = cVar3;
joined_r0x000556f3:
        if (cVar3 == '\0') goto LAB_000554fc;
        *(undefined2 *)(param_1 + 0x48) = *(undefined2 *)((int)&DAT_000df884 + iVar9 + 2);
      }
      if ((((((byte)option_flags & 8) == 0) || (((&unk_df861)[iVar9] & 0x80) == 0)) ||
          (-0x4f < dword_e03be >> 0x10)) || (dword_e03ba._2_2_ < 1)) {
        pending_dir = (short)(char)((&DAT_000df86e)[iVar9] ^ 4);
        _dword_e03ac = (int)(&DAT_000df868)[iVar8 * 0x20] >> 0x10;
        if (*(short *)(param_1 + 0x6a) < 6) {
          iVar8 = 6;
        }
        else {
          iVar8 = 0;
        }
        puVar11 = &entities + iVar8 * 0x20;
        dword_e03ae._2_2_ = 6;
        do {
          iVar8 = (int)puVar11[0x13] >> 0x10;
          if ((iVar8 <= _dword_e03ac) &&
             ((bVar4 = (((&DAT_000df86e)[iVar9] ^ 4) - (*(byte *)((int)puVar11 + 0x52) ^ 4)) + 1 & 7
              , bVar4 == 1 ||
              ((*(short *)(param_1 + 0x1a) == 0 &&
               (((iVar8 < 0x1e || ((bVar4 < 3 && (iVar8 < 0x3c)))) ||
                (((bVar4 == 3 || (bVar4 == 7)) && (iVar8 < 0x28)))))))))) goto LAB_000554fc;
          puVar11 = puVar11 + 0x20;
          dword_e03ae._2_2_ = dword_e03ae._2_2_ + -1;
        } while (dword_e03ae._2_2_ != 0);
        do_pass(param_1);
        uVar10 = CONCAT22(extraout_var,*(short *)(param_1 + 0x1a));
        if (*(short *)(param_1 + 0x1a) != 0) {
          ai_default_skate(param_1);
          uVar10 = 1;
        }
        goto LAB_0005412e;
      }
    }
  }
LAB_000554fc:
  uVar10 = 0;
LAB_0005412e:
  return CONCAT44(unaff_EDX,uVar10);
}


// ================================================================================================
// ai_offense_decision @ 0x55804 [__watcall]
// ================================================================================================

undefined8 __watcall ai_offense_decision(int param_1,undefined4 unaff_EDX)

{
  short sVar1;
  short sVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  
  __CHK(0x18);
  if ((dword_cc128 == 0) &&
     ((((((stop_flags & 0x20) != 0 && ((stop_flags & 0x40) != (*(byte *)(param_1 + 0x44) & 0xff40)))
        && (dword_c90aa != 0)) && (sVar1 = randomrange(4), sVar1 == 0)) ||
      ((clock_seconds < 4 &&
       (*(short *)(*(int *)(param_1 + 0x6c) + 0x10) < *(short *)(*(int *)(param_1 + 0x70) + 0x10))))
      ))) {
LAB_00054bf8:
    ai_desperation_shot(param_1);
    uVar4 = 1;
  }
  else {
    sVar1 = 0x20 - (ushort)*(byte *)(param_1 + 0x5f);
    dword_e03b2 = CONCAT22(sVar1,(undefined2)dword_e03b2);
    if ((*(byte *)(param_1 + 0x44) & 0x80) == 0) {
      sVar2 = -0xe8;
    }
    else {
      sVar2 = 0xe8;
    }
    dword_e03be._2_2_ = sVar2 - *p_puck_y;
    sVar2 = -*p_puck_x;
    dword_e03ba = CONCAT22(sVar2,(undefined2)dword_e03ba);
    if ((uint)((int)dword_e03be._2_2_ * (int)dword_e03be._2_2_ + (int)sVar2 * (int)sVar2) < 0x2711)
    {
      if (*(short *)(*(int *)(param_1 + 0x70) + 0x38) < 0) {
LAB_000558f5:
        dword_e03b2 = CONCAT22(1,(undefined2)dword_e03b2);
      }
      else {
        dword_e03b6._2_2_ = direction8();
        if (*(short *)(param_1 + 0x6a) < 6) {
          iVar3 = 6;
        }
        else {
          iVar3 = 0;
        }
        puVar5 = &entities + iVar3 * 0x20;
        dword_e03ae._2_2_ = 6;
        do {
          if (*(short *)((int)puVar5 + 0x1a) == 0) {
            if ((*(byte *)((int)puVar5 + 0x45) & 2) != 0) goto LAB_000558f5;
          }
          else {
            sVar1 = *(short *)((int)puVar5 + 2) - *p_puck_x;
            dword_e03ba = CONCAT22(sVar1,(undefined2)dword_e03ba);
            sVar2 = *(short *)((int)puVar5 + 6) - *p_puck_y;
            dword_e03be = CONCAT22(sVar2,(undefined2)dword_e03be);
            sVar1 = direction8((int)sVar1,(int)sVar2);
            if (sVar1 == dword_e03b6._2_2_) {
              dword_e03b2 = CONCAT22(dword_e03b2._2_2_ * 2,(undefined2)dword_e03b2);
            }
          }
          puVar5 = puVar5 + 0x20;
          dword_e03ae._2_2_ = dword_e03ae._2_2_ + -1;
        } while (dword_e03ae._2_2_ != 0);
      }
    }
    else {
      dword_e03b2._2_2_ = sVar1 * 0x10;
    }
    sVar1 = randomrange(dword_e03b2 >> 0x10);
    if (sVar1 < 9) {
      sVar1 = *p_puck_y;
      if ((*(byte *)(param_1 + 0x44) & 0x80) == 0) {
        sVar1 = -sVar1;
      }
      dword_e03ba = CONCAT22(sVar1,(undefined2)dword_e03ba);
      if (-1 < sVar1) {
        dword_e03be = CONCAT22(0xe8 - sVar1,(undefined2)dword_e03be);
        if (((-1 < (short)(0xe8 - sVar1)) && ((dword_cc128 == 0 || (0x73 < sVar1)))) &&
           ((stop_flags & 0x80) == 0)) goto LAB_00054bf8;
      }
    }
    uVar4 = 0;
  }
  return CONCAT44(unaff_EDX,uVar4);
}


// ================================================================================================
// ai_desperation_shot @ 0x55a35 [__watcall]
// ================================================================================================

void __watcall
ai_desperation_shot(int param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  ushort uVar1;
  
  __CHK(8);
  dword_e03ba._2_2_ = *p_puck_y;
  if ((*(byte *)(param_1 + 0x44) & 0x80) == 0) {
    dword_e03ba._2_2_ = -dword_e03ba._2_2_;
  }
  uVar1 = (ushort)((int)(uint)(ushort)(0xe8 - dword_e03ba._2_2_) >> 3);
  dword_e03be = CONCAT22(uVar1,(undefined2)dword_e03be);
  if (0x13 < uVar1) {
    uVar1 = 0x14;
  }
  *(ushort *)(param_1 + 0x28) = uVar1;
  set_state(param_1,0x12,unaff_EBX,unaff_ECX,unaff_EDX);
  return;
}


// ================================================================================================
// check_offside @ 0x55a9f [__watcall]
// ================================================================================================

void __watcall check_offside(int param_1)

{
  int iVar1;
  int iVar2;
  short sVar3;
  short sVar4;
  
  __CHK(0x18);
  if (((byte)option_flags & 2) == 0) {
    return;
  }
  if (dword_cc128 != 0) {
    return;
  }
  if (dword_cc11c != 0) {
    return;
  }
  sVar4 = 0;
  iVar2 = 0xdf614;
  do {
    if (1 < sVar4) {
      dword_e03ba._2_2_ = 0x4a;
      if (*(short *)(param_1 + 6) < 0x4a) {
        dword_e03ba._2_2_ = -0x4a;
        if (-0x4a < *(short *)(param_1 + 6)) {
          dword_e03ba._2_2_ = 0xffb6;
          return;
        }
        if (*(short *)(param_1 + 0x7a) < -0x49) {
          dword_e03ba._2_2_ = 0xffb6;
          return;
        }
        sub_64338();
        dword_e03ba._2_2_ = dword_e03ba._2_2_ + -10;
        if ((game_flags & 2) == 0) {
          iVar2 = 0xdf714;
        }
        else {
          iVar2 = 0xdf614;
        }
        iVar1 = *(int *)(iVar2 + 0xf6);
        if (dword_e9ac2 < 6 == *(short *)(iVar1 + 0x6a) < 6) {
          sVar4 = 6;
          do {
            if ((-1 < *(short *)(iVar1 + 0x1a)) && (*(short *)(iVar1 + 6) < dword_e03ba._2_2_)) {
              *(byte *)(iVar2 + 0x44) = *(byte *)(iVar2 + 0x44) | 0x10;
            }
            iVar1 = iVar1 + 0x80;
            sVar4 = sVar4 + -1;
          } while (sVar4 != 0);
          return;
        }
      }
      else {
        if (0x49 < *(short *)(param_1 + 0x7a)) {
          dword_e03ba._2_2_ = 0x4a;
          return;
        }
        sub_64338();
        dword_e03ba._2_2_ = dword_e03ba._2_2_ + 10;
        if ((game_flags & 2) == 0) {
          iVar2 = 0xdf614;
        }
        else {
          iVar2 = 0xdf714;
        }
        iVar1 = *(int *)(iVar2 + 0xf6);
        if (dword_e9ac2 < 6 == *(short *)(iVar1 + 0x6a) < 6) {
          sVar4 = 6;
          do {
            if ((-1 < *(short *)(iVar1 + 0x1a)) && (dword_e03ba._2_2_ < *(short *)(iVar1 + 6))) {
              *(byte *)(iVar2 + 0x44) = *(byte *)(iVar2 + 0x44) | 0x10;
            }
            iVar1 = iVar1 + 0x80;
            sVar4 = sVar4 + -1;
          } while (sVar4 != 0);
          return;
        }
      }
      *(byte *)(iVar2 + 0x44) = *(byte *)(iVar2 + 0x44) & 0xef;
      return;
    }
    if ((*(byte *)(iVar2 + 0x44) & 0x10) != 0) {
      iVar1 = *(int *)(iVar2 + 0xf6);
      for (sVar3 = 0; sVar3 < 6; sVar3 = sVar3 + 1) {
        if (-1 < *(short *)(iVar1 + 0x1a)) {
          dword_e03ba._2_2_ = *(short *)(iVar1 + 6);
          if ((*(byte *)(iVar1 + 0x44) & 0x80) == 0) {
            dword_e03ba._2_2_ = -dword_e03ba._2_2_;
          }
          if (0x4e < dword_e03ba._2_2_) break;
        }
        iVar1 = iVar1 + 0x80;
      }
      if (5 < sVar3) {
        *(byte *)(iVar2 + 0x44) = *(byte *)(iVar2 + 0x44) & 0xef;
      }
    }
    iVar2 = 0xdf714;
    sVar4 = sVar4 + 1;
  } while( true );
}


// ================================================================================================
// update_offside_flags @ 0x55c6f [__watcall]
// ================================================================================================

void __watcall update_offside_flags(int param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  short sVar3;
  
  __CHK(0xc);
  if (((byte)option_flags & 8) != 0) {
    if ((game_flags & 2) == 0) {
      puVar2 = &entities;
      puVar1 = &unk_dfb1c;
    }
    else {
      puVar2 = &unk_dfb1c;
      puVar1 = &entities;
    }
    if (*(short *)(param_1 + 6) < 0) {
      if (-1 < *(short *)(param_1 + 0x7a)) {
        sVar3 = 6;
        do {
          if ((*(short *)((int)puVar1 + 0x1a) < 0) || (-1 < *(short *)((int)puVar1 + 6))) {
            *(byte *)((int)puVar1 + 0x45) = *(byte *)((int)puVar1 + 0x45) & 0x7f;
          }
          else {
            *(byte *)((int)puVar1 + 0x45) = *(byte *)((int)puVar1 + 0x45) | 0x80;
          }
          *(byte *)((int)puVar2 + 0x45) = *(byte *)((int)puVar2 + 0x45) & 0x7f;
          puVar2 = puVar2 + 0x20;
          puVar1 = puVar1 + 0x20;
          sVar3 = sVar3 + -1;
        } while (sVar3 != 0);
      }
    }
    else if (*(short *)(param_1 + 0x7a) < 0) {
      sVar3 = 6;
      do {
        if ((*(short *)((int)puVar2 + 0x1a) < 0) || (*(short *)((int)puVar2 + 6) < 1)) {
          *(byte *)((int)puVar2 + 0x45) = *(byte *)((int)puVar2 + 0x45) & 0x7f;
        }
        else {
          *(byte *)((int)puVar2 + 0x45) = *(byte *)((int)puVar2 + 0x45) | 0x80;
        }
        *(byte *)((int)puVar1 + 0x45) = *(byte *)((int)puVar1 + 0x45) & 0x7f;
        puVar2 = puVar2 + 0x20;
        puVar1 = puVar1 + 0x20;
        sVar3 = sVar3 + -1;
      } while (sVar3 != 0);
      return;
    }
  }
  return;
}


// ================================================================================================
// sub_55d28 @ 0x55d28 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall sub_55d28(void)

{
  short *psVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  
  __CHK(0x18);
  if (((((byte)stop_flags & 0x10) != 0) &&
      (stop_flags._0_1_ = (byte)stop_flags & 0xef, (game_flags & 1) == 0)) &&
     (iVar3 = _dword_c909e >> 0x10, iVar4 = iVar3 * 0x80,
     0 < *p_puck_y == (((&unk_df860)[iVar4] & 0x80) != 0))) {
    if ((crowd_noise._2_2_ < 0x3e9) &&
       (crowd_noise._2_2_ = crowd_noise._2_2_ + 100, 1000 < crowd_noise._2_2_)) {
      crowd_noise._2_2_ = 1000;
    }
    excitement._2_2_ = excitement._2_2_ + 10;
    if ((game_flags & 0x10) == 0) {
      psVar1 = (short *)(&DAT_000df888)[iVar3 * 0x20];
      iVar3 = (&DAT_000df88c)[iVar3 * 0x20];
      *psVar1 = *psVar1 + 1;
      if ((((byte)stop_flags & 0x20) != 0) && (*(short *)(iVar3 + 0x36) < psVar1[0x1b])) {
        psVar1[3] = psVar1[3] + 1;
      }
      if (((&unk_df860)[iVar4] & 0x40) == 0) {
        byte_c5430 = byte_c5430 + '\x01';
      }
      else {
        byte_c5432 = byte_c5432 + '\x01';
      }
      if ((char)(&DAT_000df863)[iVar4] < '\x19') {
        psVar1 = (short *)((*(int *)(&unk_df860 + iVar4) >> 0x18) * 0x10 + 0xe +
                          *(int *)(psVar1 + 0x73));
        *psVar1 = *psVar1 + 1;
      }
      if (((-1 < *(short *)(iVar3 + 0x38)) &&
          (sVar2 = *(byte *)((*(int *)(iVar3 + 0x36) >> 0x10) + 0x24 + *(int *)(iVar3 + 0xda)) -
                   0x19, -1 < sVar2)) && (sVar2 < 3)) {
        psVar1 = (short *)(*(int *)(iVar3 + 0xea) + 2 + sVar2 * 6);
        *psVar1 = *psVar1 + 1;
      }
    }
  }
  return;
}


// ================================================================================================
// sub_55e72 @ 0x55e72 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall sub_55e72(int param_1)

{
  short sVar1;
  int iVar2;
  uint uVar3;
  int extraout_EDX;
  
  __CHK(0x24);
  *(byte *)(param_1 + 0x45) = *(byte *)(param_1 + 0x45) | 4;
  if ((crowd_noise._2_2_ < 0x3e9) &&
     (crowd_noise._2_2_ = crowd_noise._2_2_ + 300, 1000 < crowd_noise._2_2_)) {
    crowd_noise._2_2_ = 1000;
  }
  excitement._2_2_ = excitement._2_2_ + 0x1e;
  play_sfx(0xa1);
  _camera_target_x = *(undefined2 *)(param_1 + 2);
  camera_target_y._0_2_ = *(short *)(param_1 + 6);
  if (*(short *)(param_1 + 2) < (short)camera) {
    camera_target_y._0_2_ = (short)camera_target_y + 0x32;
  }
  action_flags = action_flags | 0x40;
  sVar1 = randomrange(*(byte *)(*(int *)(*(int *)(param_1 + 0x6c) + 0xde) + 0xf +
                               (*(int *)(param_1 + 0x44) >> 0x18) * 0x14) + 8);
  uVar3 = (uint)(6 < sVar1);
  if ((uVar3 == 0) || (word_e9b28 < 0x2e)) {
    *(undefined2 *)(extraout_EDX + 0x7e + (*(int *)(param_1 + 0x44) >> 0x18) * 2) = 0xfffd;
    *(undefined *)((*(int *)(param_1 + 0x44) >> 0x18) * 0x27 + *(int *)(extraout_EDX + 0xee)) = 6;
    uVar3 = 0xffffffff;
  }
  else {
    *(undefined2 *)(extraout_EDX + 0x7e + (*(int *)(param_1 + 0x44) >> 0x18) * 2) = 0xfffc;
    *(undefined *)((*(int *)(param_1 + 0x44) >> 0x18) * 0x27 + *(int *)(extraout_EDX + 0xee)) = 1;
  }
  dword_cbec6 = 1;
  iVar2 = (dword_e9ab6 >> 0x10) - (_period_idx >> 0x10);
  if ((clock_seconds < 0x3c) && (clock_sub != 0)) {
    iVar2 = iVar2 + -1;
  }
  sub_62764((*(byte *)(param_1 + 0x44) & 0x40) != 0,*(int *)(param_1 + 0x44) >> 0x18,uVar3,
            iVar2 / 0x3c,iVar2 % 0x3c,0,0);
  pick_player_for_position((*(byte *)(param_1 + 0x44) & 0x40) != 0,*(int *)(param_1 + 0x44) >> 0x18)
  ;
  return;
}


// ================================================================================================
// sub_5601d @ 0x5601d [__watcall]
// ================================================================================================

int __watcall sub_5601d(int *param_1,int unaff_EDX)

{
  short sVar1;
  short sVar2;
  short sVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  short sVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  
  __CHK(0x2c);
  if (*(short *)((int)param_1 + 2) < 0) {
    iVar4 = -0x60;
  }
  else {
    iVar4 = 0x60;
  }
  iVar8 = (*param_1 >> 0x10) - iVar4;
  if (*(short *)((int)param_1 + 6) < 0) {
    iVar5 = -0xca;
  }
  else {
    iVar5 = 0xca;
  }
  iVar9 = (param_1[1] >> 0x10) - iVar5;
  iVar6 = sub_b3d94(iVar8,iVar9);
  if (0x17 < iVar6) {
    iVar10 = (iVar8 * 0x100) / iVar6 >> 2;
    iVar6 = (iVar9 * 0x100) / iVar6 >> 2;
    iVar8 = iVar6;
    if (iVar6 < 0) {
      iVar8 = -iVar6;
    }
    iVar9 = iVar10;
    if (iVar10 < 0) {
      iVar9 = -iVar10;
    }
    sVar1 = (short)iVar10;
    sVar2 = (short)iVar6;
    sVar3 = (short)iVar5;
    sVar7 = (short)iVar4;
    if (iVar8 < iVar9) {
      if (iVar4 < 0) {
        if ((unaff_EDX != 0) && (unaff_EDX + -1 < 3)) {
          *(short *)((int)param_1 + 2) = sVar7 + sVar1 + 6;
          if (iVar5 < 1) {
            sVar7 = 0;
          }
          else {
            sVar7 = -10;
          }
          *(short *)((int)param_1 + 6) = sVar2 + sVar3 + sVar7;
          *(undefined2 *)(param_1 + 3) = 0;
          *(undefined2 *)((int)param_1 + 0xe) = 0;
          if ((*(byte *)((int)param_1 + 0x55) & 8) == 0) {
            *(short *)((int)param_1 + 2) =
                 *(short *)((int)param_1 + 2) +
                 *(short *)(&unk_ccbdc + (param_1[0xd] >> 0x10) * 2) + 0x9a;
          }
          else {
            *(short *)((int)param_1 + 2) =
                 *(short *)((int)param_1 + 2) -
                 (*(short *)(&unk_ccbcc + (8U - (param_1[0xd] >> 0x10) & 7) * 2) + -0x9a);
          }
          if ((*(byte *)((int)param_1 + 0x55) & 8) != 0) {
            return 0xf9b;
          }
          return 0xfe1;
        }
      }
      else if (4 < unaff_EDX) {
        *(short *)((int)param_1 + 2) = sVar7 + sVar1 + -6;
        if (iVar5 < 1) {
          sVar7 = 0;
        }
        else {
          sVar7 = -10;
        }
        *(short *)((int)param_1 + 6) = sVar2 + sVar3 + sVar7;
        *(undefined2 *)(param_1 + 3) = 0;
        *(undefined2 *)((int)param_1 + 0xe) = 0;
        if ((*(byte *)((int)param_1 + 0x55) & 8) == 0) {
          *(short *)((int)param_1 + 2) =
               *(short *)((int)param_1 + 2) +
               *(short *)(&unk_ccbcc + (param_1[0xd] >> 0x10) * 2) + -0x9a;
        }
        else {
          *(short *)((int)param_1 + 2) =
               *(short *)((int)param_1 + 2) -
               (*(short *)(&unk_ccbdc + (8U - (param_1[0xd] >> 0x10) & 7) * 2) + 0x9a);
        }
        if ((*(byte *)((int)param_1 + 0x55) & 8) == 0) {
          return 0xf9b;
        }
        return 0xfe1;
      }
    }
    else if (iVar5 < 0) {
      if ((unaff_EDX + 1U & 7) < 3) {
        *(short *)((int)param_1 + 2) = sVar7 + sVar1;
        *(short *)((int)param_1 + 6) = sVar2 + sVar3;
        *(undefined2 *)(param_1 + 3) = 0;
        *(undefined2 *)((int)param_1 + 0xe) = 0;
        *(short *)((int)param_1 + 6) =
             *(short *)((int)param_1 + 6) +
             *(short *)(&unk_ccbfc + (param_1[0xd] >> 0x10) * 2) + 0x108;
        return 0xf55;
      }
    }
    else if (4 < (unaff_EDX + 2U & 7)) {
      *(short *)((int)param_1 + 2) = sVar7 + sVar1;
      if ((iVar4 < 0) && ((*(byte *)((int)param_1 + 0x55) & 8) == 0)) {
        *(short *)((int)param_1 + 2) = *(short *)((int)param_1 + 2) + 6;
      }
      if ((0 < iVar4) && ((*(byte *)((int)param_1 + 0x55) & 8) != 0)) {
        *(short *)((int)param_1 + 2) = *(short *)((int)param_1 + 2) + -6;
      }
      *(short *)((int)param_1 + 6) = sVar2 + sVar3 + -8;
      *(undefined2 *)(param_1 + 3) = 0;
      *(undefined2 *)((int)param_1 + 0xe) = 0;
      *(short *)((int)param_1 + 6) =
           *(short *)((int)param_1 + 6) +
           *(short *)(&unk_ccbec + (param_1[0xd] >> 0x10) * 2) + -0x108;
      return 0xf0f;
    }
  }
  return *(int *)((int)param_1 + 0x36) >> 0x10;
}


// ================================================================================================
// knock_down @ 0x562db [__watcall]
// ================================================================================================

void __watcall knock_down(int param_1,int *unaff_EDX)

{
  short *psVar1;
  short sVar2;
  short sVar3;
  undefined2 uVar4;
  short sVar5;
  undefined4 uVar6;
  int iVar7;
  int extraout_EDX;
  ushort uVar8;
  
  __CHK(0x14);
  if ((0xb < *(short *)((int)unaff_EDX + 0x6a)) && (*(short *)((int)unaff_EDX + 0x6a) != 0x10)) {
    return;
  }
  if ((*(byte *)((int)unaff_EDX + 0x45) & 1) != 0) {
    return;
  }
  sVar5 = *(short *)(unaff_EDX + 0xe);
  if (sVar5 == 0xa0b) {
    return;
  }
  if (sVar5 == 0x8d3) {
    return;
  }
  if (sVar5 == 0x681) {
    return;
  }
  if (sVar5 == 0x6d9) {
    return;
  }
  if (sVar5 == 0x993) {
    return;
  }
  if (sVar5 == 0x13c5) {
    return;
  }
  if (sVar5 == 0x141d) {
    return;
  }
  if (*(short *)((int)unaff_EDX + 0x6a) == 0x10) {
    if (sVar5 == 0xb13) {
      return;
    }
    *(byte *)(unaff_EDX + 0x11) = *(byte *)(unaff_EDX + 0x11) | 0x20;
    set_animation(unaff_EDX,0xb13);
    if ((crowd_noise._2_2_ < 0x3e9) &&
       (crowd_noise._2_2_ = crowd_noise._2_2_ + 500, 1000 < crowd_noise._2_2_)) {
      crowd_noise._2_2_ = 1000;
    }
    excitement._2_2_ = excitement._2_2_ + 0xf;
    sub_58084(1);
  }
  else {
    if ((*(byte *)(unaff_EDX + 0x18) < 0xc) ||
       (sVar2 = randomrange(0x10), sVar2 + 0x10 <= *(int *)((int)unaff_EDX + 0x16) >> 0x10)) {
      if ((*(short *)(param_1 + 0x1a) != 0) &&
         (((game_flags & 0x10) == 0 && ((game_flags & 1) == 0)))) {
        psVar1 = (short *)(*(int *)(param_1 + 0x6c) + 0x24);
        *psVar1 = *psVar1 + 1;
      }
      *(undefined2 *)((int)unaff_EDX + 0x3e) = 0x78;
      sVar2 = direction8((int)(short)(*(short *)(param_1 + 2) - *(short *)((int)unaff_EDX + 2)),
                         (int)(short)(*(short *)(param_1 + 6) - *(short *)((int)unaff_EDX + 6)));
      if ((*(short *)(param_1 + 0x1a) == 0) ||
         (*(short *)(param_1 + 0x6a) < 6 == *(short *)((int)unaff_EDX + 0x6a) < 6)) {
        sVar5 = *(short *)(unaff_EDX + 0xe);
      }
      else {
        if (*(short *)((int)unaff_EDX + 2) < 0) {
          iVar7 = -(*unaff_EDX >> 0x10);
        }
        else {
          iVar7 = *unaff_EDX >> 0x10;
        }
        if (0x5f < iVar7) {
          if (*(short *)((int)unaff_EDX + 6) < 0) {
            iVar7 = -(unaff_EDX[1] >> 0x10);
          }
          else {
            iVar7 = unaff_EDX[1] >> 0x10;
          }
          if ((0xc9 < iVar7) &&
             (sVar5 = sub_5601d(unaff_EDX,(int)sVar2), sVar5 != *(short *)(unaff_EDX + 0xe)))
          goto LAB_000566ad;
        }
        if (*(short *)((int)unaff_EDX + 2) < 0x80) {
          iVar7 = *unaff_EDX >> 0x10;
          if (iVar7 < -0x7f) {
            if ((0xd0 < *(short *)((int)unaff_EDX + 6)) || (unaff_EDX[1] >> 0x10 < -0xd6))
            goto LAB_000564cf;
            if ((sVar2 == 0) || (3 < sVar2)) goto LAB_000566ad;
            *(undefined2 *)(unaff_EDX + 3) = 0;
            if (((unaff_EDX[1] >> 0x10 < -0x54) || (-0xb < unaff_EDX[1] >> 0x10)) &&
               ((*(short *)((int)unaff_EDX + 6) < 0x27 || (0x74 < *(short *)((int)unaff_EDX + 6)))))
            {
              if ((*(byte *)((int)unaff_EDX + 0x55) & 8) != 0) {
                sVar5 = 0xf9b;
                sVar3 = *(short *)(&unk_ccbcc + (8U - (unaff_EDX[0xd] >> 0x10) & 7) * 2);
                goto LAB_00056515;
              }
              sVar5 = 0xfe1;
              sVar3 = *(short *)(&unk_ccbdc + (unaff_EDX[0xd] >> 0x10) * 2);
            }
            else if ((*(byte *)((int)unaff_EDX + 0x55) & 8) == 0) {
              sVar5 = 0x1055;
              sVar3 = *(short *)(&unk_ccc1c + (unaff_EDX[0xd] >> 0x10) * 2);
            }
            else {
              sVar5 = 0x1027;
              sVar3 = *(short *)(&unk_ccc0c + (8U - (unaff_EDX[0xd] >> 0x10) & 7) * 2);
LAB_00056515:
              sVar3 = -sVar3;
            }
LAB_00056517:
            *(short *)((int)unaff_EDX + 2) = sVar3;
          }
          else if (*(short *)((int)unaff_EDX + 6) < 0xee) {
            if (unaff_EDX[1] >> 0x10 < -0xf1) {
              if ((0x68 < *(short *)((int)unaff_EDX + 2)) || (iVar7 < -0x68)) goto LAB_000564cf;
              if (((int)sVar2 + 1U & 7) < 3) {
                *(undefined2 *)((int)unaff_EDX + 6) =
                     *(undefined2 *)(&unk_ccbfc + (unaff_EDX[0xd] >> 0x10) * 2);
                *(undefined2 *)((int)unaff_EDX + 0xe) = 0;
                sVar5 = 0xf55;
              }
            }
          }
          else {
            if ((0x68 < *(short *)((int)unaff_EDX + 2)) || (iVar7 < -0x68)) goto LAB_000564cf;
            if (4 < ((int)sVar2 + 2U & 7)) {
              *(undefined2 *)((int)unaff_EDX + 6) =
                   *(undefined2 *)(&unk_ccbec + (unaff_EDX[0xd] >> 0x10) * 2);
              *(undefined2 *)((int)unaff_EDX + 0xe) = 0;
              sVar5 = 0xf0f;
            }
          }
        }
        else if ((*(short *)((int)unaff_EDX + 6) < 0xd1) && (-0xd7 < unaff_EDX[1] >> 0x10)) {
          if (4 < sVar2) {
            *(undefined2 *)(unaff_EDX + 3) = 0;
            if ((*(byte *)((int)unaff_EDX + 0x55) & 8) != 0) {
              sVar5 = 0xfe1;
              sVar3 = *(short *)(&unk_ccbdc + (8U - (unaff_EDX[0xd] >> 0x10) & 7) * 2);
              goto LAB_00056515;
            }
            sVar5 = 0xf9b;
            sVar3 = *(short *)(&unk_ccbcc + (unaff_EDX[0xd] >> 0x10) * 2);
            goto LAB_00056517;
          }
        }
        else {
LAB_000564cf:
          sVar5 = sub_5601d(unaff_EDX,(int)sVar2);
        }
      }
LAB_000566ad:
      if (sVar5 == *(short *)(unaff_EDX + 0xe)) {
        uVar8 = (sVar2 - *(short *)((int)unaff_EDX + 0x36)) + 1U & 7;
        if (uVar8 < 3) {
          sVar5 = 0x6d9;
        }
        else if ((*(short *)(param_1 + 0x6a) == 0xe) && ((uVar8 == 3 || (uVar8 == 7)))) {
          sVar5 = 0x6d9;
          if ((((*(short *)(param_1 + 0x12) < 0x450) && (*(short *)(param_1 + 0x12) < 0x468)) &&
              (dword_cc0fc < 0)) &&
             ((((game_flags & 1) == 0 && ((game_flags & 0x10) == 0)) &&
              ((((byte)option_flags & 0x10) != 0 &&
               (((*(byte *)((int)unaff_EDX + 0x36) & 3) == 0 &&
                ((*(byte *)((int)unaff_EDX + 0x45) & 0x10) == 0)))))))) {
            if ((*(byte *)(unaff_EDX + 0x11) & 8) == 0) {
              uVar4 = 0xa0;
            }
            else {
              uVar4 = 200;
            }
            sVar2 = randomrange(uVar4);
            if ((sVar2 < 0x15) && (iVar7 = injury_check(unaff_EDX), iVar7 != 0)) {
              if ((crowd_noise._2_2_ < 0x3e9) &&
                 (crowd_noise._2_2_ = crowd_noise._2_2_ + 500, 1000 < crowd_noise._2_2_)) {
                crowd_noise._2_2_ = 1000;
              }
              excitement._2_2_ = excitement._2_2_ + 0xf;
              *(byte *)(unaff_EDX + 0x11) = *(byte *)(unaff_EDX + 0x11) | 0x20;
              set_animation(unaff_EDX,0xa0b);
              sub_55e72(unaff_EDX);
              queue_infraction(param_1,10);
              return;
            }
          }
        }
        else if (((*(byte *)((int)unaff_EDX + 0x36) & 3) == 0) &&
                ((9 < *(byte *)(param_1 + 100) && (*(short *)(param_1 + 0x6a) < 0xc)))) {
          sVar5 = 0x993;
          sub_61576((*(byte *)(param_1 + 0x44) & 0x40) != 0);
        }
        else {
          sVar5 = 0x681;
        }
      }
      else {
        crowd_noise._2_2_ = crowd_noise._2_2_ + 100;
        if (((((short)*p_puck_carrier != *(short *)((int)unaff_EDX + 0x6a)) &&
             (sVar2 = sub_5369f(param_1), sVar2 < 4)) && (0xf0e < sVar5)) && (sVar5 < 0xfe2)) {
          if (*(short *)(unaff_EDX + 6) < 0x24) {
            uVar4 = 0x14;
          }
          else {
            uVar4 = 0x18;
          }
          maybe_queue_infraction(param_1,uVar4);
        }
      }
    }
    else {
      *(undefined2 *)(unaff_EDX + 0x10) = 0x3c;
      sVar5 = 0x8d3;
    }
    *(byte *)(unaff_EDX + 0x11) = *(byte *)(unaff_EDX + 0x11) | 0x20;
    set_animation(unaff_EDX,(int)sVar5);
    if (*(char *)((int)unaff_EDX + (*(int *)((int)unaff_EDX + 0x1a) >> 0x10) + 0x1e) == '\x12') {
      ai_default_skate(unaff_EDX);
    }
    if ((crowd_noise._2_2_ < 0x3e9) &&
       (crowd_noise._2_2_ = crowd_noise._2_2_ + 500, 1000 < crowd_noise._2_2_)) {
      crowd_noise._2_2_ = 1000;
    }
    excitement._2_2_ = excitement._2_2_ + 0xf;
    if ((*p_puck_carrier < '\0') || ((short)*p_puck_carrier != *(short *)((int)unaff_EDX + 0x6a))) {
      if ((sVar5 < 0xf0f) || (0x1055 < sVar5)) {
        uVar6 = 1;
      }
      else {
        uVar6 = 2;
      }
      sub_58084(uVar6);
      return;
    }
    *p_puck_carrier = -1;
    if ((((dword_cc0fc < 0) && ((game_flags & 0x10) == 0)) && (((byte)option_flags & 0x10) != 0)) &&
       (((*(short *)(unaff_EDX + 0xe) == 0x6d9 && ((*(byte *)((int)unaff_EDX + 0x36) & 3) == 0)) &&
        ((*(byte *)((int)unaff_EDX + 0x45) & 0x10) == 0)))) {
      if ((*(byte *)(unaff_EDX + 0x11) & 8) == 0) {
        uVar4 = 0xa0;
      }
      else {
        uVar4 = 200;
      }
      sVar5 = randomrange(uVar4);
      if (((sVar5 <= *(short *)(unaff_EDX + 6)) && ((game_flags & 1) == 0)) &&
         (iVar7 = injury_check(unaff_EDX), iVar7 != 0)) {
        *(byte *)(unaff_EDX + 0x11) = *(byte *)(unaff_EDX + 0x11) | 0x20;
        set_animation(unaff_EDX,0xa0b);
        sub_55e72(unaff_EDX);
        if ((((*(short *)(param_1 + 0x1a) == 0) || (((byte)option_flags & 1) == 0)) ||
            ('\a' < (char)(&word_e9aba)[(*(byte *)(param_1 + 0x44) & 0x40) != 0])) ||
           (iVar7 = injury_check(param_1), iVar7 == 0)) {
          queue_infraction(param_1,10);
        }
        else {
          sVar5 = direction8((int)(short)(*(short *)((int)unaff_EDX + 2) - *(short *)(param_1 + 2)),
                             (int)(short)(*(short *)((int)unaff_EDX + 6) - *(short *)(param_1 + 6)))
          ;
          iVar7 = *(int *)(param_1 + 0x34) >> 0x10;
          if ((((sVar5 - iVar7) + 1U & 7) < 3) &&
             ((((unaff_EDX[0xd] >> 0x10) - iVar7) + 1U & 7) < 3)) {
            uVar6 = 0x17;
          }
          else {
            uVar6 = 9;
          }
          queue_infraction(param_1,uVar6);
          for (iVar7 = 0; sVar5 = (short)iVar7, sVar5 < 0x20; iVar7 = iVar7 + 1) {
            if (*(char *)((int)&infraction_queue + sVar5 * 2 + 3) == '\0') {
              start_stoppage((int)(short)(sVar5 + -1));
              iVar7 = extraout_EDX;
            }
          }
        }
      }
    }
    if ((*(byte *)(unaff_EDX + 0x11) & 0x40) == 0) {
      uVar6 = 0xa0;
      goto LAB_00056a4a;
    }
  }
  uVar6 = 0x7d;
LAB_00056a4a:
  play_sfx(uVar6);
  return;
}


// ================================================================================================
// resolve_hook_hit @ 0x56a54 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall resolve_hook_hit(int param_1,int unaff_EDX)

{
  short sVar1;
  int iVar2;
  undefined4 uVar3;
  bool bVar4;
  
  __CHK(0x10);
  if ((*(byte *)(param_1 + 0x44) & 0x20) != 0) {
    return;
  }
  if (*(short *)(param_1 + 0x6a) == 0x10) {
    return;
  }
  if (*(short *)(param_1 + 0x1a) == 0) {
    return;
  }
  if ((*(byte *)(param_1 + 0x45) & 1) == 0) {
    if (((((byte)option_flags & 1) == 0) && ((*(byte *)(unaff_EDX + 0x44) & 8) != 0)) &&
       (sVar1 = randomrange((int)(short)((*(byte *)(unaff_EDX + 100) + 0x10) -
                                        (ushort)*(byte *)(param_1 + 0x57))), sVar1 < 0xc)) {
      return;
    }
    iVar2 = *(int *)(unaff_EDX + 0x34);
    sVar1 = direction8((int)(short)(*(short *)(param_1 + 2) - *(short *)(unaff_EDX + 2)),
                       (int)(short)(*(short *)(param_1 + 6) - *(short *)(unaff_EDX + 6)));
    if (2 < (((int)sVar1 - (iVar2 >> 0x10)) + 1U & 7)) {
      return;
    }
    knock_down(unaff_EDX,param_1);
    iVar2 = sub_6427f(param_1);
    if (iVar2 == 0) {
      sVar1 = sub_5369f(unaff_EDX);
      if (4 < sVar1) {
        byte_c90ba = 0xff;
        return;
      }
      uVar3 = 0x10;
    }
    else {
      if (-1 < dword_cc0fc) {
        byte_c90ba = 0xff;
        return;
      }
      dword_cc0fc = *(int *)(param_1 + 0x68) >> 0x10;
      bVar4 = _misc_flags >> 0x10 != dword_cc0fc;
      if (bVar4) {
        if (bVar4) {
          _dword_cc108 = 0xffffffff;
        }
        else {
          _dword_cc108 = 2;
        }
      }
      else {
        _dword_cc108 = 1;
      }
      uVar3 = 0x1a;
    }
    maybe_queue_infraction(unaff_EDX,uVar3);
    byte_c90ba = 0xff;
    return;
  }
  return;
}


// ================================================================================================
// resolve_poke_hit @ 0x56b79 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall resolve_poke_hit(int param_1,int unaff_EDX)

{
  short sVar1;
  undefined2 uVar2;
  int iVar3;
  bool bVar4;
  
  __CHK(0x10);
  if (((((*(byte *)(param_1 + 0x44) & 0x20) == 0) && (*(short *)(param_1 + 0x6a) != 0x10)) &&
      (*(short *)(param_1 + 0x1a) != 0)) && ((*(byte *)(param_1 + 0x45) & 1) == 0)) {
    iVar3 = *(int *)(unaff_EDX + 0x34);
    sVar1 = direction8((int)(short)(*(short *)(param_1 + 2) - *(short *)(unaff_EDX + 2)),
                       (int)(short)(*(short *)(param_1 + 6) - *(short *)(unaff_EDX + 6)));
    if ((((int)sVar1 - (iVar3 >> 0x10)) + 1U & 7) < 3) {
      if ((short)*p_puck_carrier == *(short *)(param_1 + 0x6a)) {
        action_flags = action_flags & 0xf7;
      }
      uVar2 = (undefined2)
              ((*(int *)(unaff_EDX + 10) >> 0x10) + (*(int *)(param_1 + 10) >> 0x10) >> 1);
      *(undefined2 *)(param_1 + 0xc) = uVar2;
      *(undefined2 *)(unaff_EDX + 0xc) = uVar2;
      uVar2 = (undefined2)
              ((*(int *)(unaff_EDX + 0xc) >> 0x10) + (*(int *)(param_1 + 0xc) >> 0x10) >> 1);
      *(undefined2 *)(param_1 + 0xe) = uVar2;
      *(undefined2 *)(unaff_EDX + 0xe) = uVar2;
      *(byte *)(param_1 + 0x44) = *(byte *)(param_1 + 0x44) | 0x20;
      set_animation(param_1,0x669);
      *(byte *)(unaff_EDX + 0x44) = *(byte *)(unaff_EDX + 0x44) | 0x20;
      if (*(short *)(unaff_EDX + 0x38) == 0x639) {
        uVar2 = 0x651;
      }
      else {
        uVar2 = 0x88b;
      }
      set_animation(unaff_EDX,uVar2);
      iVar3 = sub_6427f(param_1);
      if (iVar3 == 0) {
        sVar1 = sub_5369f(unaff_EDX);
        if (sVar1 < 7) {
          if (*(short *)(unaff_EDX + 0x38) == 0x651) {
            uVar2 = 0x12;
          }
          else {
            uVar2 = 0xf;
          }
          maybe_queue_infraction(unaff_EDX,uVar2);
        }
      }
      else if (dword_cc0fc < 0) {
        dword_cc0fc = *(int *)(param_1 + 0x68) >> 0x10;
        bVar4 = _misc_flags >> 0x10 != dword_cc0fc;
        if (bVar4) {
          if (bVar4) {
            _dword_cc108 = 0xffffffff;
          }
          else {
            _dword_cc108 = 2;
          }
        }
        else {
          _dword_cc108 = 1;
        }
        maybe_queue_infraction(unaff_EDX,0x1a);
        *p_puck_carrier = -1;
        *(undefined2 *)(unaff_EDX + 0x3e) = 0x20;
      }
      byte_c90ba = 0xff;
    }
  }
  return;
}


// ================================================================================================
// attach_puck_to_stick @ 0x56d06 [__watcall]
// ================================================================================================

void __watcall attach_puck_to_stick(int param_1,int unaff_EDX)

{
  short sVar1;
  short extraout_DX;
  undefined2 uVar2;
  undefined2 extraout_var;
  undefined2 extraout_var_00;
  
  __CHK(0x14);
  sVar1 = *(short *)(param_1 + 0x12);
  uVar2 = (undefined2)((uint)unaff_EDX >> 0x10);
  if ((sVar1 < 0x430) || (0x467 < sVar1)) {
    if ((*(short *)(param_1 + 10) < 9) &&
       (dword_e03be._2_2_ = dword_e03ba._2_2_ & 0xf, dword_e03be._2_2_ != 0)) {
      return;
    }
  }
  else if (((sVar1 < 0x450) && ((*(byte *)(param_1 + 0x12) & 1) != 0)) &&
          (8 < *(short *)(param_1 + 10))) {
    return;
  }
  if (*(short *)(unaff_EDX + 0x6a) != 0x10) {
    update_carrier(unaff_EDX);
    uVar2 = extraout_var;
  }
  *(undefined2 *)(param_1 + 0x10) = 0;
  *(undefined2 *)(unaff_EDX + 0x3e) = 8;
  dword_e03ba._2_2_ = *(short *)(param_1 + 2) - *(short *)(unaff_EDX + 2);
  dword_e03be._2_2_ = *(short *)(param_1 + 6) - *(short *)(unaff_EDX + 6);
  if (dword_e03be._2_2_ == 0) {
    frame_offsets_lookup(unaff_EDX);
    uVar2 = extraout_var_00;
  }
  sVar1 = *(short *)(param_1 + 0xe);
  *(undefined *)(param_1 + 0xd) = dword_e03ba._2_1_;
  *(undefined *)(param_1 + 0xf) = dword_e03be._2_1_;
  sub_4dfa4(param_1,CONCAT22(uVar2,*(undefined2 *)(param_1 + 0xc)));
  if (*(short *)(param_1 + 10) < 9) {
    if (*(short *)(unaff_EDX + 0x38) != 0x84b) {
      play_sfx(0xa3);
      return;
    }
  }
  else {
    uVar2 = 0xa3;
    if ((9000000 < (int)sVar1 * (int)sVar1 + (int)extraout_DX * (int)extraout_DX) &&
       (0xc < *(short *)(param_1 + 10))) {
      uVar2 = 0xa2;
      knock_down(param_1,unaff_EDX);
    }
    if (*(short *)(unaff_EDX + 0x38) != 0x84b) {
      play_sfx(uVar2);
    }
    if (((*(byte *)(unaff_EDX + 0x44) & 0x20) == 0) && (*(short *)(unaff_EDX + 0x6a) != 0x10)) {
      *(byte *)(unaff_EDX + 0x44) = *(byte *)(unaff_EDX + 0x44) | 0x20;
      set_animation(unaff_EDX,0x84b);
    }
  }
  return;
}


// ================================================================================================
// check_icing @ 0x56e52 [__watcall]
// ================================================================================================

void __watcall check_icing(void)

{
  short sVar1;
  int iVar2;
  
  __CHK(8);
  if ((((dword_e9abe._2_1_ & 4) != 0) && ((dword_e9abe._2_1_ & 1) == 0)) && (*p_puck_carrier < '\0')
     ) {
    if ((dword_e9abe._2_1_ & 2) == 0) {
      if (-0xe9 < *p_puck_y) {
        return;
      }
    }
    else if (*p_puck_y < 0xe8) {
      return;
    }
    sVar1 = *p_puck_x;
    if (sVar1 < 0) {
      iVar2 = -(int)sVar1;
    }
    else {
      iVar2 = (int)sVar1;
    }
    if (iVar2 < 0x2d) {
      dword_e9abe._2_1_ = dword_e9abe._2_1_ & 0xfb;
      return;
    }
    dword_e9abe._2_1_ = dword_e9abe._2_1_ | 1;
  }
  return;
}


// ================================================================================================
// ai_puck_shadow @ 0x56ecf [__watcall]
// ================================================================================================

void __watcall ai_puck_shadow(int param_1)

{
  __CHK(8);
  if (*(short *)(param_1 + 0x12) != 0x189) {
    if ((*(int *)(param_1 + 0x10) >> 0x10 != -1) && (*(short *)(param_1 + 0x38) == 0x7fd)) {
      *(undefined2 *)(param_1 + 2) = 0;
      *(undefined2 *)(param_1 + 6) = 0x122;
      *(undefined2 *)(param_1 + 10) = 0xe;
      if (*p_puck_y < 0) {
        *(undefined2 *)(param_1 + 0x54) = 0x8000;
        *(undefined2 *)(param_1 + 6) = 0xfef6;
        *(short *)(param_1 + 10) = *(short *)(param_1 + 10) + -1;
      }
    }
    return;
  }
  *(undefined2 *)(param_1 + 2) = *p_puck_x;
  *(short *)(param_1 + 6) = *p_puck_y;
  *(undefined2 *)(param_1 + 10) = 0;
  if ((action_flags & 0x80) != 0) {
    *(short *)(param_1 + 2) = *(short *)(param_1 + 2) + 1;
    return;
  }
  *(short *)(param_1 + 6) = *(short *)(param_1 + 6) + 1;
  return;
}


// ================================================================================================
// sub_56f5a @ 0x56f5a [__watcall]
// ================================================================================================

void __watcall sub_56f5a(int param_1)

{
  int iVar1;
  int iVar2;
  int extraout_EDX;
  int extraout_EDX_00;
  int extraout_EDX_01;
  int extraout_EDX_02;
  
  __CHK(0x14);
  dword_e03ba = CONCAT22(*(undefined2 *)(param_1 + 0x6a),(undefined2)dword_e03ba);
  iVar1 = dword_e03ba;
  dword_e03ba._2_1_ = (undefined)*(undefined2 *)(param_1 + 0x6a);
  *p_puck_carrier = dword_e03ba._2_1_;
  dword_e03ba = iVar1;
  iVar1 = *(int *)(param_1 + 0x6c);
  iVar2 = *(int *)(param_1 + 0x70);
  if ((dword_cc128 != 0) && ((short)*(char *)(param_1 + 0x47) == *(short *)(iVar1 + 0x30))) {
    end_penalty_shot();
    dword_cc0f4 = 0;
    dword_cc0f8 = 0;
    param_1 = extraout_EDX;
  }
  *(undefined *)(iVar2 + 0x33) = 0xff;
  *(undefined *)(iVar2 + 0x35) = 0xff;
  *(byte *)(iVar2 + 0x44) = *(byte *)(iVar2 + 0x44) | 8;
  if ((misc_flags & 0x10) == 0) {
    play_sfx(0x9b);
    param_1 = extraout_EDX_00;
    goto LAB_0005704f;
  }
  misc_flags = misc_flags & 0xef;
  if ((game_flags & 0x10) == 0) {
    *(short *)(iVar1 + 0x12) = *(short *)(iVar1 + 0x12) + 1;
    if ((*p_puck_y < 0x4f) || ((*(byte *)(param_1 + 0x44) & 0x80) == 0)) {
      if ((-0x4f < *p_puck_y) || ((*(byte *)(param_1 + 0x44) & 0x80) != 0)) goto LAB_0005700a;
    }
    *(short *)(iVar1 + 0x14) = *(short *)(iVar1 + 0x14) + 1;
  }
LAB_0005700a:
  if (crowd_noise._2_2_ < 0x3e9) {
    crowd_noise._2_2_ = crowd_noise._2_2_ + 200;
    if (1000 < crowd_noise._2_2_) {
      crowd_noise._2_2_ = 1000;
    }
  }
  if ((*(byte *)(param_1 + 0x44) & 0x40) == 0) {
    excitement._2_2_ = excitement._2_2_ + 10;
  }
LAB_0005704f:
  sub_50afe(param_1);
  action_flags = action_flags & 0xf3;
  if (*(short *)(extraout_EDX_01 + 0x1a) == 0) {
    sub_55d28();
    end_penalty_shot();
    if (*(short *)(extraout_EDX_02 + 0x38) == 0x181) {
      *(undefined2 *)(extraout_EDX_02 + 0x2e) = 5;
    }
    else {
      *(undefined2 *)(extraout_EDX_02 + 0x2e) = 0x8c;
    }
  }
  sub_5b1ce(dword_e03ba >> 0x10);
  return;
}


// ================================================================================================
// puck_hits_player @ 0x57096 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall puck_hits_player(int param_1,int unaff_EDX)

{
  char cVar1;
  uint uVar2;
  short sVar3;
  ushort uVar4;
  undefined2 uVar5;
  short sVar6;
  int iVar7;
  int iVar8;
  undefined4 uVar9;
  undefined uStackY_14;
  
  __CHK(0x18);
  uVar2 = ram0x000e03aa;
  uStackY_14 = 0;
  sVar3 = CONCAT11(dword_e03ba._3_1_,dword_e03ba._2_1_);
  sVar6 = CONCAT11(dword_e03be._3_1_,dword_e03be._2_1_);
  if ((game_flags & 0x10) == 0) {
    ram0x000e03aa = ram0x000e03aa & 0xffff;
    if (*(short *)(param_1 + 10) < 9) {
      ram0x000e03aa = CONCAT22(2,(short)uVar2);
    }
    sVar3 = direction8((int)(short)-CONCAT11(dword_e03ba._3_1_,dword_e03ba._2_1_),
                       (int)(short)-CONCAT11(dword_e03be._3_1_,dword_e03be._2_1_));
    uVar4 = sVar3 - *(short *)(unaff_EDX + 0x36);
    dword_e03ba._2_1_ = (byte)uVar4 & 7;
    dword_e03ba._3_1_ = 0;
    if ((uVar4 & 3) == 0) {
      uVar5 = randomrange(0x100);
      dword_e03ba._2_1_ = (byte)uVar5;
      dword_e03ba._3_1_ = (char)((ushort)uVar5 >> 8);
    }
    uVar5 = (undefined2)ram0x000e03aa;
    sVar3 = ((short)(ram0x000e03aa >> 0x10) + ((short)(dword_e03ba._2_1_ & 4) >> 2 ^ 1U)) * 2;
    unique0x10000180 = CONCAT22(sVar3,uVar5);
    if ((*(byte *)(unaff_EDX + 0x55) & 8) != 0) {
      dword_e03ac._0_1_ = (undefined)sVar3;
      dword_e03ac._1_1_ = (undefined)((ushort)sVar3 >> 8);
      ram0x000e03aa = CONCAT13(dword_e03ac._1_1_,CONCAT12((undefined)dword_e03ac,uVar5)) ^ 0x20000;
    }
    if (((*(short *)(unaff_EDX + 0x12) < 0x206) || (0x215 < *(short *)(unaff_EDX + 0x12))) ||
       (sVar3 = CONCAT11(dword_e03ba._3_1_,dword_e03ba._2_1_),
       sVar6 = CONCAT11(dword_e03be._3_1_,dword_e03be._2_1_), *p_puck_z < 5)) {
      *(undefined *)(unaff_EDX + 99) = 0;
      if ((((short)dword_e9a9e == 0) && ((*(byte *)(unaff_EDX + 0x44) & 0x40) == 0)) &&
         ((((byte)stop_flags & 0x10) != 0 && (_word_c90a0 < 6 != *(short *)(unaff_EDX + 0x6a) < 6)))
         ) {
        iVar7 = _dword_c909e >> 0x10;
        if (*(short *)((int)&unk_df820 + iVar7 * 0x80 + 2) < 0) {
          iVar8 = -((int)(&unk_df820)[iVar7 * 0x20] >> 0x10);
        }
        else {
          iVar8 = (int)(&unk_df820)[iVar7 * 0x20] >> 0x10;
        }
        if ((0x58 < iVar8) &&
           (0 < *(short *)((int)&unk_df820 + iVar7 * 0x80 + 2) !=
            ((*(byte *)(unaff_EDX + 0x44) & 0x80) != 0))) {
          sVar3 = *(short *)p_puck_vy;
          if (sVar3 < 0) {
            sVar3 = -sVar3;
          }
          sVar6 = *(short *)p_puck_vx;
          if (sVar6 < 0) {
            sVar6 = -sVar6;
          }
          if ((17000 < (short)(sVar6 + sVar3)) ||
             (((6000 < (short)(sVar6 + sVar3) && (0x119c < *(short *)(unaff_EDX + 0x38))) &&
              (*(short *)(unaff_EDX + 0x38) < 0x121e)))) {
            uStackY_14 = 1;
          }
        }
      }
      sub_55d28();
      update_carrier(unaff_EDX);
      if ((game_flags & 1) == 0) {
        sVar3 = *(short *)p_puck_vy;
        if (sVar3 < 0) {
          iVar7 = -(int)sVar3;
        }
        else {
          iVar7 = (int)sVar3;
        }
        if (4000 < iVar7) {
          if ((*(byte *)(unaff_EDX + 0x44) & 0x40) == 0) {
            uVar9 = 0x7d;
          }
          else {
            uVar9 = 0xa1;
          }
          play_sfx(uVar9);
        }
      }
      sVar3 = *(short *)p_puck_vy;
      if (sVar3 < 0) {
        iVar7 = -(int)sVar3;
      }
      else {
        iVar7 = (int)sVar3;
      }
      if (iVar7 < 0xbb9) {
        uVar9 = 0xa3;
      }
      else {
        uVar9 = 0x9d;
      }
      play_sfx(uVar9);
      cVar1 = *p_puck_carrier;
      if (cVar1 < '\0') {
        uVar5 = randomrange((int)(short)(((short)((int)((uint)*(byte *)(unaff_EDX + 0x5b) * 5) >> 2)
                                         + 2) * 0x200));
        dword_e03ba._2_1_ = (byte)uVar5;
        dword_e03ba._3_1_ = (char)((ushort)uVar5 >> 8) + ' ';
        sVar3 = *(short *)p_puck_vx;
        if (sVar3 < 0) {
          iVar7 = -(int)sVar3;
        }
        else {
          iVar7 = (int)sVar3;
        }
        if (iVar7 <= CONCAT13(dword_e03ba._3_1_,CONCAT12(dword_e03ba._2_1_,(undefined2)dword_e03ba))
                     >> 0x10) {
          sVar3 = *(short *)p_puck_vy;
          if (sVar3 < 0) {
            iVar7 = -(int)sVar3;
          }
          else {
            iVar7 = (int)sVar3;
          }
          if ((iVar7 <= CONCAT13(dword_e03ba._3_1_,
                                 CONCAT12(dword_e03ba._2_1_,(undefined2)dword_e03ba)) >> 0x10) &&
             ((*(byte *)(unaff_EDX + 0x45) & 4) == 0)) {
            *(undefined2 *)p_puck_vz = 0;
            if (8 < *p_puck_z) {
              *p_puck_z = 8;
            }
            *(short *)p_puck_vx = *(short *)p_puck_vx >> 2;
            *(short *)p_puck_vy = *(short *)p_puck_vy >> 2;
            sub_56f5a(unaff_EDX);
            *(undefined *)(unaff_EDX + 99) = uStackY_14;
            sVar3 = CONCAT11(dword_e03ba._3_1_,dword_e03ba._2_1_);
            sVar6 = CONCAT11(dword_e03be._3_1_,dword_e03be._2_1_);
            goto LAB_0005747b;
          }
        }
      }
      else {
        *p_puck_carrier = -1;
        (&unk_df85a)[cVar1 * 0x40] = 0x14;
        dword_c90a2 = *(undefined2 *)((int)&DAT_000df884 + cVar1 * 0x80 + 2);
        action_flags = action_flags & 0xf3;
      }
      *(undefined2 *)p_puck_vz = 0;
      if (10 < *p_puck_z) {
        *p_puck_z = 10;
      }
      *(undefined2 *)(unaff_EDX + 0x3e) = 10;
      *(undefined2 *)(unaff_EDX + 0x2c) = 4;
      dword_e03ba._2_2_ = *(short *)(param_1 + 2) - *(short *)(unaff_EDX + 2);
      dword_e03be._2_2_ = *(short *)(param_1 + 6) - *(short *)(unaff_EDX + 6);
      if (dword_e03be._2_2_ == 0) {
        frame_offsets_lookup(unaff_EDX);
      }
      sVar3 = dword_e03be._2_2_;
      if (dword_e03be._2_2_ == 0) {
        sVar3 = 1;
      }
      dword_e03be._3_1_ = (undefined)((ushort)sVar3 >> 8);
      dword_e03be._2_1_ = (char)sVar3;
      if (-1 < (int)(CONCAT13(dword_e03be._3_1_,CONCAT12(dword_e03be._2_1_,(undefined2)dword_e03be))
                    ^ *(uint *)(unaff_EDX + 0xc)) >> 0x10) {
        sVar3 = -sVar3;
      }
      dword_e03be._2_2_ = sVar3;
      *(char *)(param_1 + 0xd) = (char)dword_e03ba._2_1_ >> 1;
      *(char *)(param_1 + 0xf) = dword_e03be._2_1_ >> 1;
      sub_4dfa4(param_1);
      sVar3 = dword_e03ba._2_2_;
      sVar6 = dword_e03be._2_2_;
    }
  }
LAB_0005747b:
  dword_e03be._3_1_ = (undefined)((ushort)sVar6 >> 8);
  dword_e03be._2_1_ = (char)sVar6;
  dword_e03ba._3_1_ = (char)((ushort)sVar3 >> 8);
  dword_e03ba._2_1_ = (byte)sVar3;
  return;
}


// ================================================================================================
// goalie_save @ 0x57483 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall goalie_save(uint param_1,int unaff_EDX)

{
  short sVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined extraout_DL;
  undefined4 uVar6;
  uint uVar7;
  int iVar8;
  
  __CHK(0x24);
  uVar6 = 0;
  if (*(short *)(unaff_EDX + 0x1a) == 0) {
    if ((game_flags & 0x10) != 0) {
      return;
    }
    *(undefined *)(unaff_EDX + 99) = 0;
    uVar2 = param_1;
    if ((((short)dword_e9a9e == 0) && ((*(byte *)(unaff_EDX + 0x44) & 0x40) == 0)) &&
       (((byte)stop_flags & 0x10) != 0)) {
      uVar2 = (uint)(_word_c90a0 < 6 != *(short *)(unaff_EDX + 0x6a) < 6);
      if (uVar2 != 0) {
        iVar8 = _dword_c909e >> 0x10;
        if (*(short *)((int)&unk_df820 + iVar8 * 0x80 + 2) < 0) {
          uVar2 = -((int)(&unk_df820)[iVar8 * 0x20] >> 0x10);
        }
        else {
          uVar2 = (int)(&unk_df820)[iVar8 * 0x20] >> 0x10;
        }
        if ((0x58 < (int)uVar2) &&
           (uVar2 = (uint)(((*(byte *)(unaff_EDX + 0x44) & 0x80) != 0) !=
                          0 < *(short *)((int)&unk_df820 + iVar8 * 0x80 + 2)), uVar2 != 0)) {
          sVar1 = *(short *)p_puck_vy;
          if (sVar1 < 0) {
            uVar2 = -(int)sVar1;
          }
          else {
            uVar2 = (uint)sVar1;
          }
          if ((int)uVar2 < 0x2ee1) {
            sVar1 = *(short *)p_puck_vy;
            if (sVar1 < 0) {
              uVar2 = -(int)sVar1;
            }
            else {
              uVar2 = (uint)sVar1;
            }
            if ((((int)uVar2 < 0x1771) || (*(short *)(unaff_EDX + 0x38) < 0x119d)) ||
               (0x121d < *(short *)(unaff_EDX + 0x38))) goto LAB_000575b8;
          }
          uVar6 = 1;
        }
      }
    }
LAB_000575b8:
    sub_55d28(uVar2,uVar6);
  }
  *(byte *)(unaff_EDX + 0x44) = *(byte *)(unaff_EDX + 0x44) & 0xfe;
  if (*p_puck_carrier < '\0') {
    if ((*(short *)(unaff_EDX + 0x1a) == 0) &&
       (0x40 < CONCAT22((undefined2)dword_e03be,dword_e03ba._2_2_))) {
      return;
    }
    uVar2 = (int)*(short *)p_puck_vx * (int)*(short *)p_puck_vx +
            (int)*(short *)p_puck_vy * (int)*(short *)p_puck_vy;
    dword_e03ba._2_2_ = (short)uVar2;
    dword_e03be._0_2_ = (undefined2)(uVar2 >> 0x10);
    dword_e03be._2_2_ = 0;
    if (((byte)stop_flags & 0x10) == 0) {
      dword_e03be._2_2_ = (ushort)*(byte *)(unaff_EDX + 0x60) * 700;
    }
    dword_e03be._2_2_ = dword_e03be._2_2_ + 13000;
    uVar7 = (int)dword_e03be._2_2_ * (int)dword_e03be._2_2_;
    dword_e03be._2_2_ = (short)uVar7;
    uRam000e03c2 = (undefined2)(uVar7 >> 0x10);
    if ((*(short *)(unaff_EDX + 0x38) < 0x13c5) || (0x14ad < *(short *)(unaff_EDX + 0x38))) {
      if (uVar2 <= uVar7) {
LAB_00057802:
        uRam000e03c2 = (undefined2)(uVar7 >> 0x10);
        dword_e03be._2_2_ = (short)uVar7;
        dword_e03be._0_2_ = (undefined2)(uVar2 >> 0x10);
        dword_e03ba._2_2_ = (short)uVar2;
        *(undefined2 *)p_puck_vz = 0;
        sub_56f5a(unaff_EDX);
        if (*(short *)(unaff_EDX + 0x1a) != 0) {
          return;
        }
        if (8 < *p_puck_z) {
          *p_puck_z = 8;
        }
        *(short *)p_puck_vx = *(short *)p_puck_vx >> 2;
        *(short *)p_puck_vy = *(short *)p_puck_vy >> 2;
        *(undefined *)(unaff_EDX + 99) = extraout_DL;
        return;
      }
      if (*(short *)(unaff_EDX + 0x6a) == shot_power._2_2_) {
        sVar1 = randomrange(2);
        uVar7 = CONCAT22(uRam000e03c2,dword_e03be._2_2_);
        uVar2 = CONCAT22((undefined2)dword_e03be,dword_e03ba._2_2_);
        if (sVar1 != 0) goto LAB_00057802;
      }
    }
    uRam000e03c2 = (undefined2)(uVar7 >> 0x10);
    dword_e03be._2_2_ = (short)uVar7;
    dword_e03be._0_2_ = (undefined2)(uVar2 >> 0x10);
    dword_e03ba._2_2_ = (short)uVar2;
    *(undefined2 *)(unaff_EDX + 0x3e) = 8;
  }
  else {
    if ((0x13c4 < *(short *)(unaff_EDX + 0x38)) && (*(short *)(unaff_EDX + 0x38) < 0x14ae)) {
      return;
    }
    iVar8 = (int)*p_puck_carrier;
    iVar3 = iVar8 * 0x80;
    if (((*(byte *)(unaff_EDX + 0x44) ^ (&unk_df860)[iVar3]) & 0x40) == 0) {
      return;
    }
    if (0x24 < CONCAT22((undefined2)dword_e03be,dword_e03ba._2_2_)) {
      return;
    }
    if (*(short *)(unaff_EDX + 0x1a) != 0) {
      if ((&unk_df836)[iVar8 * 0x40] == 0) {
        return;
      }
      iVar4 = sub_933f0(*(int *)((*(int *)(&unk_df860 + iVar3) >> 0x18) * 2 + 0x44 +
                                (&DAT_000df888)[iVar8 * 0x20]) >> 0x10,(&DAT_000df87c)[iVar3]);
      iVar5 = sub_933f0(*(int *)(*(int *)(unaff_EDX + 0x6c) + 0x44 +
                                (*(int *)(unaff_EDX + 0x44) >> 0x18) * 2) >> 0x10,
                        *(undefined *)(unaff_EDX + 0x60));
      dword_e03ba._2_2_ = ((short)(iVar4 >> 0xc) + 0x20) - (short)(iVar5 >> 0xc);
      if ((((&unk_df860)[iVar3] & 8) != 0) && ((*(byte *)(unaff_EDX + 0x44) & 8) == 0)) {
        dword_e03ba._2_2_ =
             (short)((int)(((int)dword_e03ba._2_2_ + ((int)dword_e03ba._2_2_ >> 0xf) * -8) -
                          (uint)(((int)dword_e03ba._2_2_ >> 0xf) << 2 < 0)) >> 3) +
             dword_e03ba._2_2_;
      }
      sVar1 = randomrange((int)dword_e03ba._2_2_);
      if (2 < sVar1) {
        return;
      }
    }
    iVar4 = sub_933f0(*(int *)((&DAT_000df888)[iVar8 * 0x20] + 0x44 +
                              (*(int *)(&unk_df860 + iVar3) >> 0x18) * 2) >> 0x10,
                      (&DAT_000df87c)[iVar3]);
    (&unk_df85a)[iVar8 * 0x40] = (short)(iVar4 >> 0xc) + 0x14;
    iVar8 = sub_933f0(*(int *)((*(int *)(unaff_EDX + 0x44) >> 0x18) * 2 + 0x44 +
                              *(int *)(unaff_EDX + 0x6c)) >> 0x10,*(undefined *)(unaff_EDX + 0x60));
    *(short *)(unaff_EDX + 0x3e) = (short)(iVar8 >> 0xc) + 0x14;
    dword_c90a2 = *(undefined2 *)((int)&DAT_000df884 + iVar3 + 2);
    action_flags = action_flags & 0xf3;
  }
  play_sfx(0x99);
  update_carrier(unaff_EDX);
  sub_57a3e(param_1);
  return;
}


// ================================================================================================
// start_shot @ 0x5786e [__watcall]
// ================================================================================================

void __watcall
start_shot(int param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  short sVar1;
  undefined4 uVar2;
  
  __CHK(0x10);
  pending_dir = 8;
  action_flags = action_flags | 8;
  dword_e03ba._2_2_ = 0;
  if ((*(byte *)(param_1 + 0x44) & 0x80) == 0) {
    dword_e03be._2_2_ = -0xf0;
  }
  else {
    dword_e03be._2_2_ = 0xf0;
  }
  dword_e03ba._2_2_ =
       direction8((int)-*(short *)(param_1 + 2),
                  (int)(short)(dword_e03be._2_2_ - *(short *)(param_1 + 6)),param_1,0,unaff_EDX,
                  unaff_ECX,unaff_EBX);
  shot_power._0_2_ = 0xf;
  sVar1 = shot_is_backhand(param_1,(int)dword_e03ba._2_2_);
  if (sVar1 == 0) {
    uVar2 = 0x3f9;
  }
  else {
    uVar2 = 0x491;
  }
  set_animation(param_1,uVar2);
  return;
}


// ================================================================================================
// shot_control @ 0x578fa [__watcall]
// ================================================================================================

void __watcall shot_control(int param_1)

{
  ushort uVar1;
  short sVar2;
  
  __CHK(0x14);
  if (0xd < *(short *)(param_1 + 0x3a)) {
    do_shot();
    return;
  }
  if ((dword_e03ba._2_2_ & 8) == 0) {
    pending_dir = dword_e03ba._2_2_ & 7;
    dword_e03ba._2_2_ = pending_dir;
  }
  if (*(short *)(param_1 + 0x3a) < 10) {
    if (((dword_e03be._2_1_ & 0x10) == 0) && ((dword_e03be._2_1_ & 0x40) == 0)) {
      if (*(short *)(param_1 + 0x3a) < 8) {
        shot_power._0_2_ = (short)shot_power + 1;
        if ((9 < *(byte *)(param_1 + 0x5b)) || (sVar2 = *(short *)(param_1 + 0x3a), sVar2 < 5)) {
          if (((byte)dword_e03ac & 0x20) == 0) {
            return;
          }
          sVar2 = *(short *)(param_1 + 0x3a);
        }
        *(short *)(param_1 + 0x3a) = 0xe - sVar2;
      }
    }
    else {
      action_flags = action_flags & 0xf7;
      *(byte *)(param_1 + 0x44) = *(byte *)(param_1 + 0x44) | 0x20;
      uVar1 = *(ushort *)(param_1 + 0x38);
      if (uVar1 < 0x491) {
        if (uVar1 == 0x3f9) {
          *(undefined2 *)(param_1 + 0x38) = 0x1265;
          return;
        }
      }
      else {
        if (uVar1 < 0x492) {
          *(undefined2 *)(param_1 + 0x38) = 0x12dd;
          return;
        }
        if (0xdd2 < uVar1) {
          if (uVar1 < 0xdd4) {
            *(undefined2 *)(param_1 + 0x38) = 0x1355;
            return;
          }
          if (uVar1 != 0xe2b) {
            return;
          }
          *(undefined2 *)(param_1 + 0x38) = 0x138d;
          return;
        }
      }
    }
  }
  return;
}


// ================================================================================================
// shot_is_backhand @ 0x579ff [__watcall]
// ================================================================================================

undefined4 __watcall shot_is_backhand(int param_1,char unaff_DL)

{
  uint uVar1;
  byte bVar2;
  
  __CHK(8);
  bVar2 = (char)*(undefined2 *)(param_1 + 0x36) - unaff_DL & 7;
  if ((*(byte *)(param_1 + 0x55) & 8) == 0) {
    uVar1 = 1 << bVar2 & 0x1e;
  }
  else {
    uVar1 = 1 << bVar2 & 0xf0;
  }
  return CONCAT22((short)((uint)(1 << bVar2) >> 0x10),(ushort)(uVar1 != 0));
}


// ================================================================================================
// sub_57a3e @ 0x57a3e [__watcall]
// ================================================================================================

void __watcall
sub_57a3e(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  short sVar1;
  int extraout_EDX;
  int extraout_EDX_00;
  int extraout_EDX_01;
  
  __CHK(8);
  *p_puck_carrier = 0xff;
  sVar1 = randomrange(0x2000,param_1,unaff_EBX,unaff_ECX,unaff_EDX);
  *(short *)(extraout_EDX + 0xe) = sVar1 + -0x1000;
  sVar1 = randomrange(0x2000);
  *(short *)(extraout_EDX_00 + 0xc) = sVar1 + -0x1000;
  dword_e03ba._2_2_ = randomrange(0x1000);
  *(undefined2 *)(extraout_EDX_01 + 0x10) = dword_e03ba._2_2_;
  sub_4dfa4(extraout_EDX_01);
  return;
}


// ================================================================================================
// shot_setup @ 0x57a98 [__watcall]
// ================================================================================================

void __watcall shot_setup(int param_1)

{
  short sVar1;
  int iVar2;
  undefined4 *puVar3;
  short sVar4;
  int iVar5;
  short sStack_1c;
  
  __CHK(0x34);
  if ((*(byte *)(param_1 + 0x44) & 8) == 0) {
    if (*(short *)(param_1 + 0x6a) < 6) {
      iVar2 = 6;
    }
    else {
      iVar2 = 0;
    }
    sVar4 = 0;
    for (puVar3 = &entities + iVar2 * 0x20; (sVar4 < 6 && (*(short *)((int)puVar3 + 0x1a) != 0));
        puVar3 = puVar3 + 0x20) {
      sVar4 = sVar4 + 1;
    }
    if (sVar4 == 6) {
      pending_dir = 8;
    }
    else {
      sVar4 = ((short)((uint)*puVar3 >> 0x10) +
              (short)((int)*(undefined4 *)((int)puVar3 + 10) >> 0x19)) - *p_puck_x;
      iVar2 = (int)(short)(((short)((uint)puVar3[1] >> 0x10) + (short)((int)puVar3[3] >> 0x19)) -
                          *p_puck_y);
      sStack_1c = sub_b3d94((int)sVar4,iVar2);
      if (sStack_1c == 0) {
        sStack_1c = 1;
      }
      sVar1 = 0xe8;
      if ((*(byte *)(param_1 + 0x44) & 0x80) == 0) {
        sVar1 = -0xe8;
      }
      iVar5 = (int)sVar4 * ((int)sVar1 - (int)*p_puck_y);
      sVar4 = (short)((iVar5 - (0x12 - *p_puck_x) * iVar2) / (int)sStack_1c) +
              (short)((iVar5 - (-0x12 - *p_puck_x) * iVar2) / (int)sStack_1c);
      if (sVar4 < 0) {
        iVar2 = -(int)sVar4;
      }
      else {
        iVar2 = (int)sVar4;
      }
      if (iVar2 < 0x2d) {
        if ((*(byte *)(param_1 + 0x44) & 0x80) != 0) {
          sVar4 = -sVar4;
        }
        if (sVar4 < 0) {
          pending_dir = 6;
        }
        else {
          pending_dir = 2;
        }
      }
      else {
        pending_dir = 0;
      }
    }
  }
  return;
}


// ================================================================================================
// do_shot @ 0x57c0b [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall do_shot(int *param_1)

{
  short sVar1;
  short sVar2;
  short sVar3;
  int iVar4;
  uint uVar5;
  short sVar6;
  ushort extraout_DX;
  ushort uVar7;
  short extraout_DX_00;
  uint uVar8;
  ushort uVar9;
  int iVar10;
  uint uVar11;
  short sVar12;
  undefined4 local_26;
  undefined4 local_22;
  undefined4 uStack_1e;
  
  __CHK(0x38);
  shot_setup();
  _word_c90a0 = *(undefined2 *)((int)param_1 + 0x6a);
  action_flags = action_flags & 0xf7;
  *(byte *)(param_1 + 0x11) = *(byte *)(param_1 + 0x11) | 0x20;
  if ((((short)*p_puck_carrier == *(short *)((int)param_1 + 0x6a)) ||
      (*(short *)(param_1 + 0xe) == 0xdd3)) || (*(short *)(param_1 + 0xe) == 0xe2b)) {
    stop_flags._0_1_ = (byte)stop_flags | 0x10;
    if ((*(short *)(param_1 + 0xe) == 0x491) || (*(short *)(param_1 + 0xe) == 0xe2b)) {
      shot_power._0_2_ = (short)shot_power - ((short)shot_power >> 2);
    }
    local_22 = CONCAT22(0xaa,(undefined2)local_22);
    uVar9 = (ushort)*(byte *)((int)param_1 + 0x5b);
    if (0xc < *(byte *)((int)param_1 + 0x5b)) {
      if (*(short *)((int)param_1 + 2) < 0) {
        iVar4 = -(*param_1 >> 0x10);
      }
      else {
        iVar4 = *param_1 >> 0x10;
      }
      if (*(short *)((int)param_1 + 6) < 0) {
        iVar10 = -(param_1[1] >> 0x10);
      }
      else {
        iVar10 = param_1[1] >> 0x10;
      }
      if (iVar4 + iVar10 < 500) {
        uVar9 = uVar9 + 2;
      }
    }
    if (0xe < uVar9) {
      uVar9 = uVar9 + 1;
    }
    if (0xd < uVar9) {
      uVar9 = uVar9 + 1;
    }
    if (10 < uVar9) {
      uVar9 = uVar9 + 1;
    }
    iVar4 = sub_933f0(*(int *)(param_1[0x1b] + 0x44 + (param_1[0x11] >> 0x18) * 2) >> 0x10,uVar9);
    shot_power._0_2_ =
         (short)((uint)((short)((short)shot_power * ((short)(iVar4 >> 0xc) + 0x14)) * 0x5249) >>
                0x10);
    if (dword_cc0f8 != 0) {
      count_defenders_ahead();
      dword_cc0f8 = dword_cc124;
    }
    if ((short)shot_power >> 4 != 3 && -1 < (short)(3 - ((short)shot_power >> 4))) {
      local_22 = CONCAT22(0x9a,(undefined2)local_22);
    }
    *p_puck_carrier = -1;
    *(undefined2 *)((int)param_1 + 0x3e) = 0x10;
    dword_c90a2 = *(undefined2 *)((int)param_1 + 0x6a);
    sVar6 = 0xe8;
    if ((*(byte *)(param_1 + 0x11) & 0x80) == 0) {
      sVar6 = -0xe8;
    }
    sVar1 = *(short *)(&shot_targets + pending_dir * 4) - *p_puck_x;
    local_26 = CONCAT22(sVar1,(undefined2)local_26);
    sVar6 = sVar6 - *p_puck_y;
    uStack_1e = CONCAT22(sVar6,(undefined2)uStack_1e);
    sVar12 = *(short *)(&unk_ccc62 + pending_dir * 4);
    sVar2 = sub_b3d94((int)sVar1,(int)sVar6);
    if (sVar2 == 0) {
      sVar2 = 1;
    }
    if ((game_flags & 0x10) == 0) {
      uVar9 = (ushort)*(byte *)(param_1 + 0x17);
      if (0xe < *(byte *)(param_1 + 0x17)) {
        uVar9 = uVar9 + 1;
      }
      if (0xd < uVar9) {
        uVar9 = uVar9 + 1;
      }
      if ((200 < sVar2) ||
         (sVar3 = randomrange(*(byte *)(param_1 + 0x17) + 0x10), uVar9 = extraout_DX, sVar3 < 0xf))
      {
        uVar9 = (ushort)((int)((int)sVar2 *
                               ((((int)(short)shot_power >> 4) - (int)(short)uVar9) + 0x10) &
                              0xffffU) >> 6);
        if (sVar2 < 0xfa) {
          uVar9 = (short)uVar9 >> 1;
        }
        if (0xa0 < uVar9) {
          uVar9 = 0xa0;
        }
        sVar3 = randomrange(uVar9 * 2);
        local_26 = CONCAT22(sVar1 + (sVar3 - uVar9),(undefined2)local_26);
        if (0x3c < uVar9) {
          uVar9 = 0x3c;
        }
        uVar7 = uVar9;
        if (sVar6 < 0) {
          uVar7 = (short)uVar9 >> 1;
        }
        sVar1 = randomrange(uVar7 * 2);
        uStack_1e = CONCAT22(sVar6 + (sVar1 - extraout_DX_00),(undefined2)uStack_1e);
        sVar6 = (short)((int)(short)uVar9 >> 1);
        if (sVar2 < 0xa0) {
          sVar6 = (short)((uint)(int)(short)uVar9 / 3);
        }
        if (sVar2 < 0x50) {
          sVar6 = (short)uVar9 >> 2;
        }
        sVar6 = randomrange(sVar6);
        sVar12 = sVar12 + sVar6;
      }
    }
    iVar10 = (int)sVar2;
    *(short *)p_puck_vx = (short)(((local_26 >> 0x10) * (short)shot_power * 0x3b) / iVar10);
    iVar4 = (uStack_1e >> 0x10) * (short)shot_power * 0x3b;
    uVar8 = iVar4 % iVar10;
    *(short *)p_puck_vy = (short)(iVar4 / iVar10);
    if (dword_cc128 != 0) {
      uVar8 = *(int *)((int)param_1 + 10) >> 0x10;
      if (-1 < (int)((int)*(short *)p_puck_vx ^ uVar8)) {
        if (*(short *)(param_1 + 3) < 0) {
          uVar8 = -uVar8;
        }
        sVar6 = *(short *)p_puck_vx;
        if (sVar6 < 0) {
          iVar4 = -(int)sVar6;
        }
        else {
          iVar4 = (int)sVar6;
        }
        if (iVar4 < (int)uVar8) {
          *(short *)p_puck_vx = *(short *)(param_1 + 3) + 500;
        }
      }
      uVar5 = param_1[3] >> 0x10;
      uVar8 = (int)*(short *)p_puck_vy ^ uVar5;
      if (-1 < (int)uVar8) {
        uVar8 = uVar5;
        if (*(short *)((int)param_1 + 0xe) < 0) {
          uVar8 = -uVar5;
        }
        sVar6 = *(short *)p_puck_vy;
        if (sVar6 < 0) {
          iVar4 = -(int)sVar6;
        }
        else {
          iVar4 = (int)sVar6;
        }
        if (iVar4 < (int)uVar8) {
          uVar8 = CONCAT22((short)(uVar8 >> 0x10),*(undefined2 *)((int)param_1 + 0xe)) + 500;
          *(short *)p_puck_vy = (short)uVar8;
        }
      }
    }
    if (sVar12 != 0) {
      uVar11 = (uint)(short)shot_power;
      uVar5 = sVar2 * 0xb33;
      uVar8 = uVar5 % uVar11;
      uVar9 = (short)((uVar11 * 0x44 * (int)sVar12) / (uint)(int)sVar2) + (short)(uVar5 / uVar11);
      if (0x1800 < uVar9) {
        uVar9 = 0x1800;
      }
      *(ushort *)p_puck_vz = uVar9;
    }
    play_sfx(local_22 >> 0x10,uVar8);
    if (dword_cc128 != 0) {
      set_state(param_1,0x11);
    }
  }
  else {
    play_sfx(0x99);
  }
  return;
}


// ================================================================================================
// sub_58084 @ 0x58084 [__watcall]
// ================================================================================================

void __watcall sub_58084(short param_1)

{
  short sVar1;
  short extraout_DX;
  undefined2 uVar2;
  
  __CHK(8);
  if (param_1 == 2) {
    play_sfx(0xb1);
    param_1 = extraout_DX;
  }
  if ((param_1 != 0) && (0x20 < word_e9b28)) {
    sVar1 = randomrange(2);
    if (sVar1 == 0) {
      uVar2 = 0x93;
      goto LAB_000580eb;
    }
  }
  word_cc0da = (ushort)(word_cc0da == 0);
  if (word_cc0da == 0) {
    uVar2 = 0xb2;
  }
  else {
    uVar2 = 0xb0;
  }
LAB_000580eb:
  play_sfx(uVar2);
  return;
}


// ================================================================================================
// move_entity @ 0x580f5 [__watcall]
// ================================================================================================

void __watcall move_entity(int *param_1,short unaff_DX,short unaff_BX)

{
  char cVar1;
  int iVar2;
  short sVar3;
  short sVar4;
  undefined2 uStackY_12;
  undefined uStackY_10;
  undefined uStackY_f;
  
  __CHK(0x14);
  dword_ccc2c = 0;
  byte_c90ba = '\0';
  sVar4 = unaff_BX;
  if ((action_flags & 0x80) != 0) {
    sVar4 = unaff_DX;
    unaff_DX = unaff_BX;
  }
  if ((*(byte *)(param_1 + 0x11) & 4) == 0) {
    dword_c909c = *(undefined2 *)((int)param_1 + 0x66);
    dword_c909e = *(undefined2 *)(param_1 + 0x1a);
    collide_boards(param_1,*param_1 >> 0x10,param_1[1] >> 0x10);
    if ((param_1[0xc] >> 0x10 == 0 && *(int *)((int)param_1 + 0x2e) >> 0x10 == 0) &&
       (*(short *)((int)param_1 + 0x6a) < 0xc)) {
      frame_offsets_lookup(param_1);
      dword_c909c = 1;
      dword_c909e = 1;
      collide_boards(param_1,(int)(short)(*(short *)((int)param_1 + 2) + dword_e03ba._2_2_),
                     (int)(short)(*(short *)((int)param_1 + 6) + dword_e03be._2_2_));
    }
    uStackY_12 = 5;
    collide_neighbours(param_1,(int)unaff_DX,(int)sVar4);
  }
  if (byte_c90ba == '\0') {
    uStackY_10 = (undefined)*(undefined2 *)((int)param_1 + 0x6a);
    uStackY_f = (undefined)((ushort)*(undefined2 *)((int)param_1 + 0x6a) >> 8);
    for (sVar3 = (&draw_order_pos)[CONCAT13(uStackY_f,CONCAT12(uStackY_10,uStackY_12)) >> 0x10];
        sVar3 != 0x10; sVar3 = sVar3 + 1) {
      iVar2 = (int)sVar3;
      cVar1 = (&unk_e9adf)[iVar2];
      if (sVar4 <= *(short *)(&draw_order_keys +
                             (*(int *)((int)&draw_order_list + iVar2 + 1) >> 0x18) * 2)) break;
      (&unk_e9ade)[iVar2] = cVar1;
      (&unk_e9adf)[iVar2] = uStackY_10;
      (&draw_order_pos)[CONCAT13(uStackY_f,CONCAT12(uStackY_10,uStackY_12)) >> 0x10] =
           (&draw_order_pos)[CONCAT13(uStackY_f,CONCAT12(uStackY_10,uStackY_12)) >> 0x10] + 1;
      (&draw_order_pos)[(short)cVar1] = (&draw_order_pos)[(short)cVar1] + -1;
    }
    for (sVar3 = (&draw_order_pos)[CONCAT13(uStackY_f,CONCAT12(uStackY_10,uStackY_12)) >> 0x10];
        sVar3 != 0; sVar3 = sVar3 + -1) {
      iVar2 = (int)sVar3;
      cVar1 = (&unk_e9add)[iVar2];
      if (*(short *)(&draw_order_keys + (*(int *)((int)&byte_e9ad7 + iVar2 + 3) >> 0x18) * 2) <=
          sVar4) break;
      (&unk_e9ade)[iVar2] = cVar1;
      (&unk_e9add)[iVar2] = uStackY_10;
      (&draw_order_pos)[CONCAT13(uStackY_f,CONCAT12(uStackY_10,uStackY_12)) >> 0x10] =
           (&draw_order_pos)[CONCAT13(uStackY_f,CONCAT12(uStackY_10,uStackY_12)) >> 0x10] + -1;
      (&draw_order_pos)[(short)cVar1] = (&draw_order_pos)[(short)cVar1] + 1;
    }
    *(short *)(&draw_order_keys + (CONCAT13(uStackY_f,CONCAT12(uStackY_10,uStackY_12)) >> 0x10) * 2)
         = sVar4;
  }
  else if ((*(short *)(param_1 + 0xe) < 0xf0f) || (0x1055 < *(short *)(param_1 + 0xe))) {
    *(undefined2 *)((int)param_1 + 2) = *(undefined2 *)((int)param_1 + 0x76);
    *(undefined2 *)((int)param_1 + 6) = *(undefined2 *)((int)param_1 + 0x7a);
  }
  return;
}


// ================================================================================================
// collide_boards @ 0x582c9 [__watcall]
// ================================================================================================

void __watcall collide_boards(int param_1,short unaff_DX,short unaff_BX)

{
  uint uVar1;
  undefined2 uVar2;
  short sVar3;
  short sVar4;
  ushort uVar5;
  int iVar6;
  int iVar7;
  short local_14;
  
  __CHK(0x24);
  local_14 = 0xa0 - dword_c909c;
  sVar3 = 0x108 - dword_c909e;
  dword_e03b2._2_2_ = 0x40 - local_14;
  sVar4 = 0x40 - sVar3;
  dword_e03b6._2_2_ = sVar4;
  if ((unaff_BX <= sVar4) || (dword_e03b6._2_2_ = -sVar4, dword_e03b6._2_2_ <= unaff_BX)) {
    if ((unaff_DX < dword_e03b2._2_2_) ||
       (dword_e03b2._2_2_ = -dword_e03b2._2_2_, dword_e03b2._2_2_ < unaff_DX)) {
      dword_e03ba = CONCAT22(unaff_BX - dword_e03b6._2_2_,(undefined2)dword_e03ba);
      dword_e03be._2_2_ = unaff_DX - dword_e03b2._2_2_;
      dword_e03ae._2_2_ =
           sub_b3d94((int)(short)(unaff_BX - dword_e03b6._2_2_),
                     (int)(short)(unaff_DX - dword_e03b2._2_2_));
      dword_e03be._2_2_ = -dword_e03be._2_2_;
      if (0x3f < dword_e03ae._2_2_) {
        iVar7 = (int)dword_e03ae._2_2_;
        dword_e03ba = CONCAT22((short)((((int)dword_e03ba >> 0x10) << 8) / iVar7),
                               (undefined2)dword_e03ba);
        iVar6 = (int)dword_e03be._2_2_;
        dword_e03be = CONCAT22((short)((iVar6 << 8) / iVar7),(undefined2)dword_e03be);
        collide_corner(param_1,(iVar6 << 8) % iVar7);
      }
    }
    else {
      collide_net(param_1,&entities + ((sVar4 == dword_e03b6._2_2_) + 0xc) * 0x20,(int)unaff_DX,
                  (int)unaff_BX);
    }
  }
  uVar1 = dword_e03ba;
  uVar5 = *(ushort *)(param_1 + 0x32) | *(ushort *)(param_1 + 0x30);
  dword_e03ba = CONCAT22(uVar5,(undefined2)dword_e03ba);
  if (uVar5 == 0) {
    dword_e03ba = CONCAT22(0x100,(undefined2)dword_e03ba);
    uVar2 = (undefined2)dword_e03be;
    dword_e03be = dword_e03be & 0xffff;
    if ((unaff_BX < sVar3) &&
       (dword_e03ba = CONCAT22(0xff00,(undefined2)dword_e03ba), -sVar3 < unaff_BX)) {
      dword_e03ba = uVar1 & 0xffff;
      dword_e03be = CONCAT22(0xff00,uVar2);
      if (unaff_DX < local_14) {
        local_14 = -local_14;
        dword_e03be = CONCAT22(0x100,uVar2);
        if (local_14 < unaff_DX) {
          return;
        }
      }
    }
    collide_corner(param_1);
  }
  return;
}


// ================================================================================================
// collide_net @ 0x584aa [__watcall]
// ================================================================================================

void __watcall collide_net(int *param_1,int unaff_EDX,short unaff_BX,short unaff_CX)

{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  
  __CHK(0x10);
  if (0xd < *(short *)((int)param_1 + 10)) {
    return;
  }
  if (*(short *)((int)param_1 + 0x6a) != 0xe) {
    sub_53ce5(param_1,unaff_EDX,(int)unaff_BX,(int)unaff_CX);
    return;
  }
  unaff_BX = unaff_BX - *(short *)(unaff_EDX + 2);
  dword_e03b2._2_2_ = dword_c909c + 0x10;
  if (dword_e03b2._2_2_ < unaff_BX) {
    return;
  }
  dword_e03b2._2_2_ = -dword_e03b2._2_2_;
  if (unaff_BX < dword_e03b2._2_2_) {
    return;
  }
  unaff_CX = unaff_CX - *(short *)(unaff_EDX + 6);
  dword_e03b6._2_2_ = dword_c909e + 2;
  if (dword_e03b6._2_2_ < unaff_CX) {
    return;
  }
  dword_e03b6._2_2_ = -dword_e03b6._2_2_;
  if (unaff_CX < dword_e03b6._2_2_) {
    return;
  }
  if (0xc < *(short *)((int)param_1 + 0x7e)) {
    *(short *)((int)param_1 + 10) = *(short *)((int)param_1 + 0x7e);
    if (-1 < *(short *)(param_1 + 4)) {
      return;
    }
    *(short *)(param_1 + 4) = -*(short *)(param_1 + 4) >> 1;
    return;
  }
  byte_c90ba = 0xff;
  *(byte *)(param_1 + 0x11) = *(byte *)(param_1 + 0x11) & 0x7f;
  cVar1 = *p_puck_carrier;
  if (-1 < cVar1) {
    *p_puck_carrier = -1;
    (&unk_df85a)[cVar1 * 0x40] = 8;
    dword_e03be._2_2_ = *p_puck_y;
    if (((&unk_df860)[cVar1 * 0x80] & 0x80) == 0) {
      dword_e03be._2_2_ = -dword_e03be._2_2_;
    }
    if (dword_e03be._2_2_ < 0) {
      *(byte *)(param_1 + 0x11) = *(byte *)(param_1 + 0x11) | 0x80;
    }
  }
  uVar3 = CONCAT22((undefined2)dword_e03ba,dword_e03b6._2_2_);
  dword_e03ba._2_2_ = 0xff00;
  iVar4 = param_1[1] - param_1[0x1e];
  iVar5 = iVar4 >> 8;
  dword_e03be._2_2_ = (short)((uint)iVar4 >> 8);
  sRam000e03c2 = (short)(char)((uint)iVar4 >> 0x18);
  if (iVar5 != 0) {
    if (0 < iVar5) {
      dword_e03ba._2_2_ = 0x100;
      dword_e03b6._2_2_ = -dword_e03b6._2_2_;
    }
    dword_e03b6._2_2_ = dword_e03b6._2_2_ + unaff_CX;
    dword_e03ae._2_2_ = (ushort)((uint)(*param_1 - param_1[0x1d]) >> 8);
    dword_e03b2._0_2_ = (short)(char)((uint)(*param_1 - param_1[0x1d]) >> 0x18);
    uVar3 = ((int)(short)dword_e03ae._2_2_ * (int)dword_e03b6._2_2_) / (int)dword_e03be._2_2_;
    iVar5 = ((int)(short)dword_e03ae._2_2_ * (int)dword_e03b6._2_2_) % (int)dword_e03be._2_2_;
    dword_e03b6._2_2_ = (short)uVar3;
    dword_e03ba._0_2_ = (undefined2)(uVar3 >> 0x10);
    if (uVar3 < 0x10000) {
      unaff_BX = unaff_BX - dword_e03b6._2_2_;
      if (dword_e03b2._2_2_ <= unaff_BX) {
        iVar5 = -CONCAT22((undefined2)dword_e03ba,dword_e03b2._2_2_);
        dword_e03b2._2_2_ = (short)iVar5;
        if (unaff_BX <= dword_e03b2._2_2_) {
          dword_e03be._2_2_ = 0;
          iVar5 = CONCAT22((short)((uint)iVar5 >> 0x10),dword_e03ba._2_2_);
          dword_e03ae._2_2_ = *(ushort *)((int)param_1 + 6) ^ dword_e03ba._2_2_;
          if ((-1 < (short)dword_e03ae._2_2_) &&
             (dword_e03ba._2_2_ = -dword_e03ba._2_2_, (*(byte *)(param_1 + 0x11) & 0x80) == 0)) {
            if ((*(short *)((int)param_1 + 10) != 0xd) &&
               ((dword_e03b2._2_2_ = dword_e03b2._2_2_ + -1, unaff_BX <= dword_e03b2._2_2_ &&
                (dword_e03b2._2_2_ = -dword_e03b2._2_2_, dword_e03b2._2_2_ <= unaff_BX)))) {
              score_goal(unaff_EDX);
              return;
            }
            stop_flags._0_1_ = (byte)stop_flags & 0xef;
            if ((game_flags & 1) == 0) {
              if ((crowd_noise._2_2_ < 0x4b1) &&
                 (crowd_noise._2_2_ = crowd_noise._2_2_ + 500, 0x4b0 < crowd_noise._2_2_)) {
                crowd_noise._2_2_ = 0x4b0;
              }
              excitement._2_2_ = excitement._2_2_ + 0x28;
            }
            play_sfx(0xac);
            dword_e03ba._2_2_ = randomrange(0x1000);
            if (-1 < *(short *)((int)param_1 + 6)) {
              dword_e03ba._2_2_ = -dword_e03ba._2_2_;
            }
            *(ushort *)((int)param_1 + 0xe) = dword_e03ba._2_2_;
            sVar2 = randomrange(0x2000);
            *(short *)(param_1 + 3) = sVar2 + -0x1000;
            sVar2 = randomrange(0x2000);
            *(short *)(param_1 + 4) = sVar2 + -0x1000;
            sub_4dfa4(param_1);
            end_penalty_shot();
            dword_cc0f4 = 0;
            dword_cc0f8 = 0;
            return;
          }
          goto LAB_000587be;
        }
      }
    }
  }
  dword_e03ba._2_2_ = 0;
  dword_e03be._2_2_ = 0x100;
  if (-1 < (short)(*(short *)((int)param_1 + 2) - *(short *)((int)param_1 + 0x76))) {
    dword_e03be._2_2_ = 0xff00;
  }
LAB_000587be:
  dword_e03ba._0_2_ = (undefined2)(uVar3 >> 0x10);
  dword_e03b6._2_2_ = (short)uVar3;
  dword_ccc2c = 1;
  bounce_off_boards(param_1,iVar5);
  return;
}


// ================================================================================================
// bounce_off_boards @ 0x587d3 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall bounce_off_boards(int param_1)

{
  short sVar1;
  undefined2 uVar2;
  int iVar3;
  
  __CHK(0x1c);
  *(undefined2 *)(param_1 + 0x30) = dword_e03ba._2_2_;
  *(undefined2 *)(param_1 + 0x32) = dword_e03be._2_2_;
  dword_e03ac = -(short)((uint)((dword_e03ba >> 0x10) * (*(int *)(param_1 + 0xc) >> 0x10) -
                               (*(int *)(param_1 + 10) >> 0x10) * (dword_e03be >> 0x10)) >> 8);
  dword_e03ae._2_2_ =
       (short)((uint)((dword_e03be >> 0x10) * (*(int *)(param_1 + 0xc) >> 0x10) +
                     (*(int *)(param_1 + 10) >> 0x10) * (dword_e03ba >> 0x10)) >> 8);
  if (*(short *)(param_1 + 0x6a) != 0xe) {
    if (1000 < dword_e03ac) {
      dword_ccc2c = 0;
      return;
    }
    if (((dword_e03ac < -0xfff) && (9 < *(short *)(param_1 + 0x18))) && (dword_ccc2c == 0)) {
      play_sfx(0xb1);
    }
    dword_e03ac = dword_e03ac >> 2;
    if (-0x385 < dword_e03ac) {
      dword_e03ac = -1000;
    }
    *(short *)(param_1 + 0xc) =
         (short)((uint)((dword_e03ba >> 0x10) * (int)dword_e03ae._2_2_ -
                       (int)dword_e03ac * (dword_e03be >> 0x10)) >> 8);
    *(short *)(param_1 + 0xe) =
         (short)((uint)((int)dword_e03ac * (dword_e03ba >> 0x10) +
                       (dword_e03be >> 0x10) * (int)dword_e03ae._2_2_) >> 8);
    if (dword_ccc2c != 0) {
      if (((*(int *)(param_1 + 0x74) >> 0x10 < -0x17) && (0 < *(short *)(param_1 + 0xc))) ||
         ((0x17 < *(short *)(param_1 + 0x76) && (*(short *)(param_1 + 0xc) < 0)))) {
        *(undefined2 *)(param_1 + 0xc) = 0;
        *(undefined2 *)(param_1 + 2) = *(undefined2 *)(param_1 + 0x76);
      }
      if (*(short *)(param_1 + 0x7a) < 0) {
        sVar1 = -0xec;
      }
      else {
        sVar1 = 0xec;
      }
      if (((sVar1 + 10 < *(int *)(param_1 + 0x78) >> 0x10) && (*(short *)(param_1 + 0xe) < 0)) ||
         ((*(int *)(param_1 + 0x78) >> 0x10 < sVar1 + -6 && (0 < *(short *)(param_1 + 0xe))))) {
        *(undefined2 *)(param_1 + 0xe) = 0;
        *(undefined2 *)(param_1 + 6) = *(undefined2 *)(param_1 + 0x7a);
      }
    }
    goto LAB_00058b61;
  }
  stop_flags._0_1_ = (byte)stop_flags & 0xef;
  shot_power._2_2_ = 0xffff;
  if (-1 < dword_e03ac) {
    shot_power._2_2_ = 0xffff;
    dword_ccc2c = 0;
    return;
  }
  dword_e03ac = dword_e03ac >> 2;
  if (dword_e03ac < -0x3ff) {
    sVar1 = randomrange(0x800);
    *(short *)(param_1 + 0x10) = -sVar1;
    sub_4dfa4(param_1);
    if (dword_ccc2c == 0) {
      sVar1 = (dword_e03ac >> 10) + 4;
      if (sVar1 < 0) {
        sVar1 = 0;
      }
      if (*(ushort *)(param_1 + 10) < 0xb) {
        if (-1 < *p_puck_carrier) goto LAB_0005894b;
        if (sVar1 % 3 == 2) {
          uVar2 = 0x95;
        }
        else if (sVar1 % 3 == 1) {
          uVar2 = 0x7b;
        }
        else {
          uVar2 = 0xad;
        }
      }
      else {
        sVar1 = randomrange(3);
        if (sVar1 == 0) {
          uVar2 = 0xaf;
        }
        else if (sVar1 == 1) {
          uVar2 = 0xa5;
        }
        else {
          uVar2 = 0xa7;
        }
      }
      play_sfx(uVar2);
    }
  }
LAB_0005894b:
  dword_e03ae._2_2_ = (dword_e03ae._2_2_ - (dword_e03ae._2_2_ >> 6)) - (dword_e03ae._2_2_ >> 7);
  *(short *)(param_1 + 0xc) =
       (short)((uint)((dword_e03ba >> 0x10) * (int)dword_e03ae._2_2_ -
                     (int)dword_e03ac * (dword_e03be >> 0x10)) >> 8);
  *(short *)(param_1 + 0xe) =
       (short)((uint)((int)dword_e03ae._2_2_ * (dword_e03be >> 0x10) +
                     (dword_e03ba >> 0x10) * (int)dword_e03ac) >> 8);
  if (*p_puck_carrier < '\0') {
LAB_000589fc:
    end_penalty_shot();
  }
  else {
    sVar1 = *p_puck_y;
    if (sVar1 < 0) {
      iVar3 = -(int)sVar1;
    }
    else {
      iVar3 = (int)sVar1;
    }
    if (0xe8 < iVar3) goto LAB_000589fc;
  }
  dword_cc0f4 = 0;
  dword_cc0f8 = 0;
LAB_00058b61:
  dword_ccc2c = 0;
  if (0 < *(short *)(param_1 + 0x10)) {
    *(undefined2 *)(param_1 + 0x10) = 0;
  }
  return;
}


// ================================================================================================
// collide_corner @ 0x58b7f [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall collide_corner(int *param_1)

{
  undefined2 uVar1;
  int iVar2;
  
  __CHK(0x14);
  if (*(short *)((int)param_1 + 0x6a) == 0xe) {
    if (0x1d < (short)*(ushort *)((int)param_1 + 10)) {
LAB_00058c88:
      action_flags = action_flags | 0x40;
      *(byte *)(param_1 + 0x11) = *(byte *)(param_1 + 0x11) | 4;
      if (*(short *)((int)param_1 + 6) < 0) {
        *(byte *)((int)param_1 + 0x55) = *(byte *)((int)param_1 + 0x55) | 0x80;
      }
      *(undefined2 *)((int)param_1 + 0x92) = 0xffff;
      if ((game_flags & 1) == 0) {
        queue_infraction(&entities + (ram0x000e9ac0 >> 0x10) * 0x20,3);
      }
      end_penalty_shot();
      dword_cc0f4 = 0;
      dword_cc0f8 = 0;
      return;
    }
    if (0x12 < *(ushort *)((int)param_1 + 10)) {
      if (*(short *)((int)param_1 + 6) < 0xf8) goto LAB_00058c88;
      if (*(short *)((int)param_1 + 2) < 0) {
        iVar2 = -(*param_1 >> 0x10);
      }
      else {
        iVar2 = *param_1 >> 0x10;
      }
      if (0x27 < iVar2) {
        if (*(short *)((int)param_1 + 2) < 0) {
          iVar2 = -(*param_1 >> 0x10);
        }
        else {
          iVar2 = *param_1 >> 0x10;
        }
        if (((iVar2 < 0x39) && (3999 < *(short *)((int)param_1 + 0xe))) && (0x25 < word_e9ac4)) {
          *(short *)((int)param_1 + 0xe) = *(short *)((int)param_1 + 0xe) >> 1;
          set_animation(param_1 + 0x20,0x821);
          if (*(short *)((int)param_1 + 2) < 0) {
            uVar1 = 0xffc0;
          }
          else {
            uVar1 = 0x3f;
          }
          *(undefined2 *)((int)param_1 + 0x82) = uVar1;
          *(undefined2 *)((int)param_1 + 0x86) = 0x10b;
          play_sfx(0xae);
          if ((crowd_noise._2_2_ < 0x5dd) &&
             (crowd_noise._2_2_ = crowd_noise._2_2_ + 0x4b0, 0x5dc < crowd_noise._2_2_)) {
            crowd_noise._2_2_ = 0x5dc;
          }
          excitement._2_2_ = excitement._2_2_ + 0xf;
          goto LAB_00058c88;
        }
      }
    }
  }
  bounce_off_boards(param_1);
  return;
}


// ================================================================================================
// collide_neighbours @ 0x58ce2 [__watcall]
// ================================================================================================

void __watcall collide_neighbours(int param_1,short unaff_DX,short unaff_BX)

{
  short sVar1;
  
  __CHK(0x18);
  if (((*(byte *)(param_1 + 0x45) & 0x20) == 0) &&
     ((*(short *)(param_1 + 0x6a) < 0xc || (*(short *)(param_1 + 0x6a) == 0x10)))) {
    for (sVar1 = (&draw_order_pos)[*(int *)(param_1 + 0x68) >> 0x10]; sVar1 != 0x10;
        sVar1 = sVar1 + 1) {
      if (0x10 < (short)(*(short *)(&draw_order_keys +
                                   (*(int *)((int)&draw_order_list + sVar1 + 1) >> 0x18) * 2) -
                        unaff_BX)) break;
      collide_pair(param_1,(int)unaff_DX,
                   (int)(short)(*(short *)(&draw_order_keys +
                                          (*(int *)((int)&draw_order_list + sVar1 + 1) >> 0x18) * 2)
                               - unaff_BX),(int)(short)(char)(&unk_e9adf)[sVar1]);
    }
    for (sVar1 = (&draw_order_pos)[*(int *)(param_1 + 0x68) >> 0x10]; sVar1 != 0; sVar1 = sVar1 + -1
        ) {
      if (0x10 < (short)(unaff_BX -
                        *(short *)(&draw_order_keys +
                                  (*(int *)((int)&byte_e9ad7 + sVar1 + 3) >> 0x18) * 2))) {
        return;
      }
      collide_pair(param_1,(int)unaff_DX,
                   (int)(short)(unaff_BX -
                               *(short *)(&draw_order_keys +
                                         (*(int *)((int)&byte_e9ad7 + sVar1 + 3) >> 0x18) * 2)),
                   (int)(short)(char)(&unk_e9add)[sVar1]);
    }
  }
  return;
}


// ================================================================================================
// collide_pair @ 0x58dc7 [__watcall]
// ================================================================================================

void __watcall collide_pair(int param_1,short unaff_DX,short unaff_BX,short unaff_CX)

{
  undefined2 uVar1;
  char cVar2;
  short sVar3;
  byte bVar4;
  ushort uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  undefined4 *puVar10;
  short sVar11;
  short sVar12;
  int iVar13;
  int iVar14;
  short sStackY_1c;
  undefined2 uStackY_12;
  char cStackY_10;
  undefined uStackY_f;
  
  __CHK(0x20);
  iVar6 = (int)unaff_CX;
  iVar7 = iVar6 * 0x80;
  puVar10 = &entities + iVar6 * 0x20;
  iVar9 = CONCAT22((undefined2)dword_e03be,dword_e03ba._2_2_);
  iVar13 = CONCAT22(sRam000e03c2,dword_e03be._2_2_);
  if (((((&unk_df860)[iVar7] & 4) == 0) &&
      (iVar9 = CONCAT22((undefined2)dword_e03be,dword_e03ba._2_2_),
      iVar13 = CONCAT22(sRam000e03c2,dword_e03be._2_2_), ((&unk_df861)[iVar7] & 0x20) == 0)) &&
     ((sVar11 = *(short *)((int)&DAT_000df884 + iVar7 + 2), sVar11 < 0xc ||
      (iVar9 = CONCAT22((undefined2)dword_e03be,dword_e03ba._2_2_),
      iVar13 = CONCAT22(sRam000e03c2,dword_e03be._2_2_), sVar11 == 0x10)))) {
    uVar1 = *(undefined2 *)((int)&entities + iVar7 + 2);
    cStackY_10 = (char)uVar1;
    uStackY_f = (undefined)((ushort)uVar1 >> 8);
    if ((action_flags & 0x80) != 0) {
      uVar1 = *(undefined2 *)((int)&unk_df820 + iVar7 + 2);
      cStackY_10 = (char)uVar1;
      uStackY_f = (undefined)((ushort)uVar1 >> 8);
    }
    unaff_DX = CONCAT11(uStackY_f,cStackY_10) - unaff_DX;
    cStackY_10 = (char)unaff_DX;
    uStackY_f = (undefined)((ushort)unaff_DX >> 8);
    if (unaff_DX < 0) {
      iVar8 = -(CONCAT13(uStackY_f,CONCAT12(cStackY_10,uStackY_12)) >> 0x10);
    }
    else {
      iVar8 = CONCAT13(uStackY_f,CONCAT12(cStackY_10,uStackY_12)) >> 0x10;
    }
    iVar9 = CONCAT22((undefined2)dword_e03be,dword_e03ba._2_2_);
    iVar13 = CONCAT22(sRam000e03c2,dword_e03be._2_2_);
    if ((iVar8 < 0x11) &&
       (iVar9 = CONCAT13(uStackY_f,CONCAT12(cStackY_10,uStackY_12)) >> 0x10,
       iVar9 = iVar9 * iVar9 + (int)unaff_BX * (int)unaff_BX, dword_e03ba._2_2_ = (undefined2)iVar9,
       dword_e03be._0_2_ = (undefined2)((uint)iVar9 >> 0x10),
       iVar13 = CONCAT22(sRam000e03c2,dword_e03be._2_2_), iVar9 < 0x101)) {
      sVar11 = *(short *)(param_1 + 0xc) - (&DAT_000df828)[iVar6 * 0x40];
      sVar12 = *(short *)((int)&entities + iVar7 + 2) - *(short *)(param_1 + 2);
      cStackY_10 = (char)sVar12;
      uStackY_f = (undefined)((ushort)sVar12 >> 8);
      sVar12 = *(short *)((int)&unk_df820 + iVar7 + 2) - *(short *)(param_1 + 6);
      iVar8 = (int)(short)(*(short *)(param_1 + 0xe) - (&DAT_000df82a)[iVar6 * 0x40]);
      iVar13 = sVar12 * iVar8 +
               (int)sVar11 * (CONCAT13(uStackY_f,CONCAT12(cStackY_10,uStackY_12)) >> 0x10);
      if (-1 < iVar13) {
        dword_e03be._2_2_ = (short)(iVar13 >> 4);
        sRam000e03c2 = (short)(iVar13 >> 0x14);
        if (((*(short *)(param_1 + 0x6a) == 0x10) ||
            (*(short *)((int)&DAT_000df884 + iVar7 + 2) == 0x10)) ||
           ((((&unk_df860)[iVar7] ^ *(byte *)(param_1 + 0x44)) & 0x40) != 0)) {
          cVar2 = (char)((uint)(iVar13 >> 4) >> 8);
          dword_e03b2._2_2_ = (short)cVar2;
          if (cVar2 < '\x06') {
            dword_e03b2._2_2_ = 5;
            dword_e03b6._0_2_ = 0;
          }
          word_e9b28 = dword_e03b2._2_2_;
          *(short *)(param_1 + 0x18) = *(short *)(param_1 + 0x18) + dword_e03b2._2_2_;
          (&DAT_000df834)[iVar6 * 0x40] = (&DAT_000df834)[iVar6 * 0x40] + dword_e03b2._2_2_;
          if (((&unk_df861)[iVar7] & 1) == 0) {
            *(undefined2 *)(&DAT_000df830 + iVar7) = *(undefined2 *)(param_1 + 0x6a);
          }
          if ((*(byte *)(param_1 + 0x45) & 1) == 0) {
            *(undefined2 *)(param_1 + 0x14) = *(undefined2 *)((int)&DAT_000df884 + iVar7 + 2);
          }
          if (0x13 < dword_e03b2._2_2_) {
            if (((short)*p_puck_carrier == *(short *)(param_1 + 0x6a)) ||
               ((short)*p_puck_carrier == *(short *)((int)&DAT_000df884 + iVar7 + 2))) {
              sub_58084(0);
            }
          }
          check_injury(param_1,puVar10);
          resolve_body_check(param_1,puVar10,(int)dword_e03b2._2_2_);
          iVar9 = CONCAT22((undefined2)dword_e03be,dword_e03ba._2_2_);
        }
        sVar3 = dword_e03be._2_2_;
        dword_e03b2._2_2_ = dword_e03be._2_2_;
        iVar13 = CONCAT22(sRam000e03c2,dword_e03be._2_2_);
        if (-1 < byte_c90ba) {
          iVar13 = (int)sVar12;
          iVar14 = CONCAT13(uStackY_f,CONCAT12(cStackY_10,uStackY_12)) >> 0x10;
          dword_e03b6._2_2_ = (short)(iVar13 * sVar11 - iVar8 * iVar14 >> 4);
          sVar11 = *(byte *)(param_1 + 0x56) + 0x8c;
          dword_e03a0._0_2_ = 0;
          dword_e03be._2_2_ = (byte)(&DAT_000df872)[iVar7] + 0x8c + sVar11;
          iVar9 = ((int)sVar11 * (int)sVar3) / (int)dword_e03be._2_2_;
          dword_e03ba._2_2_ = (undefined2)iVar9;
          dword_e03be._0_2_ = (undefined2)((uint)iVar9 >> 0x10);
          dword_e03be._2_2_ = dword_e03ba._2_2_;
          sRam000e03c2 = (undefined2)dword_e03be;
          *(short *)(param_1 + 0xc) =
               (&DAT_000df828)[iVar6 * 0x40] +
               (short)(iVar9 * iVar14 + dword_e03b6._2_2_ * iVar13 >> 4);
          sStackY_1c = (short)(CONCAT22((undefined2)dword_e03be,dword_e03ba._2_2_) * iVar13 -
                               dword_e03b6._2_2_ * iVar14 >> 4);
          *(short *)(param_1 + 0xe) = (&DAT_000df82a)[iVar6 * 0x40] + sStackY_1c;
          (&DAT_000df828)[iVar6 * 0x40] =
               (&DAT_000df828)[iVar6 * 0x40] +
               (short)(iVar14 * CONCAT22(sRam000e03c2,dword_e03be._2_2_) >> 4);
          (&DAT_000df82a)[iVar6 * 0x40] =
               (&DAT_000df82a)[iVar6 * 0x40] +
               (short)(iVar13 * CONCAT22(sRam000e03c2,dword_e03be._2_2_) >> 4);
          byte_c90ba = -1;
          iVar9 = CONCAT22((undefined2)dword_e03be,dword_e03ba._2_2_);
          iVar13 = CONCAT22(sRam000e03c2,dword_e03be._2_2_);
          if (((game_flags & 1) == 0) &&
             (iVar9 = CONCAT22((undefined2)dword_e03be,dword_e03ba._2_2_),
             iVar13 = CONCAT22(sRam000e03c2,dword_e03be._2_2_),
             (((&unk_df860)[iVar7] ^ *(byte *)(param_1 + 0x44)) & 0x40) == 0)) {
            sVar11 = direction8((int)(short)(*(short *)((int)&entities + iVar7 + 2) -
                                            *(short *)(param_1 + 2)),
                                (int)(short)(*(short *)((int)&unk_df820 + iVar7 + 2) -
                                            *(short *)(param_1 + 6)));
            cStackY_10 = (char)sVar11;
            if ((*(byte *)(param_1 + 0x44) & 8) == 0) {
              sVar12 = direction8((int)(short)(*(short *)(param_1 + 0x2a) - *(short *)(param_1 + 2))
                                  ,(int)(short)(*(short *)(param_1 + 0x2c) - *(short *)(param_1 + 6)
                                               ));
              if ((sVar12 == sVar11) ||
                 (((*(short *)(param_1 + 0xc) == 0 && (*(short *)(param_1 + 0xe) == 0)) &&
                  (sVar11 == *(short *)(param_1 + 0x36))))) {
                *(byte *)(param_1 + 0x28) = cStackY_10 + 2U & 7;
                apply_skating(param_1,*(int *)(param_1 + 0x25) >> 0x18);
              }
            }
            iVar9 = CONCAT22((undefined2)dword_e03be,dword_e03ba._2_2_);
            iVar13 = CONCAT22(sRam000e03c2,dword_e03be._2_2_);
            if (((&unk_df860)[iVar7] & 8) == 0) {
              bVar4 = cStackY_10 + 4U & 7;
              uVar5 = direction8((int)(short)((&DAT_000df846)[iVar6 * 0x40] -
                                             *(short *)((int)&entities + iVar7 + 2)),
                                 (int)(short)(*(short *)(&unk_df848 + iVar6 * 0x20) -
                                             *(short *)((int)&unk_df820 + iVar7 + 2)));
              if ((uVar5 == bVar4) ||
                 (((iVar9 = CONCAT22((undefined2)dword_e03be,dword_e03ba._2_2_),
                   iVar13 = CONCAT22(sRam000e03c2,dword_e03be._2_2_), *(short *)(param_1 + 0xc) == 0
                   && (iVar9 = CONCAT22((undefined2)dword_e03be,dword_e03ba._2_2_),
                      iVar13 = CONCAT22(sRam000e03c2,dword_e03be._2_2_),
                      *(short *)(param_1 + 0xe) == 0)) &&
                  (iVar9 = CONCAT22((undefined2)dword_e03be,dword_e03ba._2_2_),
                  iVar13 = CONCAT22(sRam000e03c2,dword_e03be._2_2_),
                  (ushort)bVar4 == *(ushort *)((int)&DAT_000df850 + iVar7 + 2))))) {
                *(byte *)(iVar7 + 0xdf844) = bVar4 + 2 & 7;
                apply_skating(puVar10,*(int *)(iVar7 + 0xdf841) >> 0x18);
                iVar13 = CONCAT22(sRam000e03c2,dword_e03be._2_2_);
                iVar9 = CONCAT22((undefined2)dword_e03be,dword_e03ba._2_2_);
              }
            }
          }
        }
      }
    }
  }
  sRam000e03c2 = (short)((uint)iVar13 >> 0x10);
  dword_e03be._2_2_ = (short)iVar13;
  dword_e03be._0_2_ = (undefined2)((uint)iVar9 >> 0x10);
  dword_e03ba._2_2_ = (undefined2)iVar9;
  return;
}


// ================================================================================================
// maybe_pull_goalie @ 0x591c7 [__watcall]
// ================================================================================================

void __watcall maybe_pull_goalie(int param_1,int unaff_EDX,short unaff_BX)

{
  short sVar1;
  
  __CHK(8);
  if ((((dword_cc118 == 0) && (period_idx == 2)) &&
      (sVar1 = *(short *)(unaff_EDX + 0x10) - *(short *)(param_1 + 0x10), 0 < sVar1)) &&
     ((sVar1 < 3 && (clock_seconds < 0x3d)))) {
    if ((*(byte *)(*(int *)(param_1 + 0xf6) + 0x44) & 0x80) == 0) {
      unaff_BX = -unaff_BX;
    }
    if (-1 < unaff_BX) {
      *(undefined *)(param_1 + 0x39) = 0xff;
      *(&off_cd498)
       [(int)(short)(*(ushort *)(param_1 + 0x38) & 0xf) + (short)(ushort)(param_1 == 0xdf714) * 3] =
           2;
      *(&off_cd4a0)[(short)(ushort)(param_1 == 0xdf714) * 3] = 1;
      apply_line_change();
    }
  }
  return;
}


// ================================================================================================
// cpu_line_change @ 0x59265 [__watcall]
// ================================================================================================

void __watcall cpu_line_change(void)

{
  int iVar1;
  short sVar2;
  undefined4 uVar3;
  
  __CHK(0x14);
  if ((game_flags & 1) == 0) {
    iVar1 = 0xdf614;
    uVar3 = 0xdf714;
    for (sVar2 = 0; sVar2 < 2; sVar2 = sVar2 + 1) {
      if (((-1 < *(short *)(iVar1 + 0x38)) && (-1 < *p_puck_carrier)) &&
         ((sVar2 == 0) == *p_puck_carrier < '\x06')) {
        if ((game_flags & 8) == 0) {
          if (((int)user1_team != sVar2 + 1) && ((int)(short)user2_team != sVar2 + 1)) {
            maybe_pull_goalie(iVar1,uVar3,(int)*p_puck_y);
          }
        }
        else {
          *(undefined *)(iVar1 + 0x39) = 0xff;
          *(&off_cd498)[sVar2 * 3 + (int)(short)(*(ushort *)(iVar1 + 0x38) & 0xf)] = 2;
          *(&off_cd4a0)[sVar2 * 3] = 1;
          apply_line_change();
        }
      }
      iVar1 = 0xdf714;
      uVar3 = 0xdf614;
    }
  }
  return;
}


// ================================================================================================
// sub_59352 @ 0x59352 [__watcall]
// ================================================================================================

void __watcall sub_59352(void)

{
  int iVar1;
  short sVar2;
  undefined4 uVar3;
  int iVar4;
  undefined2 uStackY_1a;
  
  __CHK(0x1c);
  iVar1 = 0xdf614;
  uVar3 = 0xdf714;
  for (sVar2 = 0; sVar2 < 2; sVar2 = sVar2 + 1) {
    if ((*(byte *)(iVar1 + 0x38) & 0xf0) == 0) {
      *(undefined *)(iVar1 + 0x39) = 0;
      iVar4 = (int)sVar2;
      *(&off_cd4a0)[iVar4 * 3] = 2;
      *(&off_cd498)
       [((int)(CONCAT22(*(undefined2 *)(iVar1 + 0x38),uStackY_1a) & 0xfffff) >> 0x10) + iVar4 * 3] =
           1;
      if (((int)user1_team != iVar4 + 1) && ((int)(short)user2_team != iVar4 + 1)) {
        uStackY_1a = 5;
        maybe_pull_goalie(iVar1,uVar3,dword_c90b2 >> 0x10);
      }
    }
    iVar1 = 0xdf714;
    uVar3 = 0xdf614;
  }
  return;
}


// ================================================================================================
// sub_593f5 @ 0x593f5 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

longlong __watcall sub_593f5(int param_1,uint unaff_EDX)

{
  int iVar1;
  int iVar2;
  bool bVar3;
  
  __CHK(0x14);
  iVar2 = dword_c90b2 >> 0x10;
  if ((((period_idx == 2) && (clock_seconds < 0x3d)) &&
      (bVar3 = _user2_slot >> 0x10 != param_1 + 1, bVar3)) && (bVar3)) {
    iVar1 = ((int)(&dword_df622)[(uint)(param_1 == 0) * 0x40] >> 0x10) -
            ((int)(&dword_df622)[param_1 * 0x40] >> 0x10);
    if ((iVar1 < 1) || (2 < iVar1)) {
      return (ulonglong)unaff_EDX << 0x20;
    }
    if ((*(byte *)((&dword_df70a)[param_1 * 0x40] + 0x44) & 0x80) == 0) {
      iVar2 = -iVar2;
    }
    if (-1 < iVar2) {
      return CONCAT44(unaff_EDX,1);
    }
  }
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// sub_59493 @ 0x59493 [__watcall]
// ================================================================================================

void __watcall
sub_59493(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  __CHK(0x14);
  sub_8e8b8(unaff_EDX,dword_ccc94,unaff_ECX,unaff_EBX);
  return;
}


// ================================================================================================
// sub_594b2 @ 0x594b2 [__watcall]
// ================================================================================================

void __watcall sub_594b2(void)

{
  __CHK(0x14);
  sub_8e908();
  return;
}


// ================================================================================================
// update_ambient_audio @ 0x594cd [__watcall]
// ================================================================================================

void __watcall update_ambient_audio(short param_1)

{
  int iVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  __CHK(0x14);
  if ((((byte)option_flags & 0x80) != 0) && (((byte)dword_c541f & 0x2a) != 0)) {
    iVar3 = (int)param_1;
    iVar5 = iVar3 * 0x1e;
    iVar4 = (crowd_noise >> 0x10) - dword_ccc88;
    iVar6 = iVar4;
    if (iVar4 < 0) {
      iVar6 = -iVar4;
    }
    iVar1 = crowd_noise >> 0x10;
    if (iVar6 != iVar5 && SBORROW4(iVar6,iVar5) == iVar6 + iVar3 * -0x1e < 0) {
      if (iVar4 < 0) {
        iVar5 = iVar3 * -0x1e;
      }
      dword_ccc88 = dword_ccc88 + iVar5;
      iVar1 = dword_ccc88;
    }
    dword_ccc88 = iVar1;
    if (dword_ccc88 < 0x200) {
      iVar5 = 0;
    }
    else if (dword_ccc88 < 0x390) {
      iVar5 = (dword_ccc88 + -0x200) / 10;
      if (((byte)dword_c541f & 8) != 0) {
        iVar5 = iVar5 + 0x20;
      }
    }
    else {
      iVar6 = dword_ccc88 + -0x390 >> 2;
      iVar5 = iVar6 + 0x28;
      if (((byte)dword_c541f & 8) != 0) {
        iVar5 = iVar6 + 0x48;
      }
    }
    if (0x7f < iVar5) {
      iVar5 = 0x7f;
    }
    iVar6 = dword_ccc88 / 0xc + 10;
    if (((byte)dword_c541f & 8) != 0) {
      iVar6 = dword_ccc88 / 0xc + 0x3c;
    }
    if (0x7f < iVar6) {
      iVar6 = 0x7f;
    }
    if (iVar6 < 10) {
      iVar6 = 10;
    }
    if ((dword_ccc8c < 1) || (iVar5 != 0)) {
      if ((dword_ccc8c == 0) && (0 < iVar5)) {
        sub_8fd84(byte_d2439,8,0x7d);
        sub_8fe1c(byte_d2439,8,0x24);
        sub_8fde5(byte_d2439,8,0x40);
      }
    }
    else {
      sub_8fdb2(byte_d2439,8,0);
      sub_8fe4f(byte_d2439,8,0x24);
    }
    if ((0 < iVar5) && ((sub_8fdb2(byte_d2439,8,iVar5), 0x7e < iVar5 || (0x7e < dword_ccc8c)))) {
      if (iVar5 < 0x7f) {
        iVar3 = 0;
      }
      else {
        sVar2 = randomrange(6);
        iVar3 = (int)sVar2;
      }
      sub_8fde5(byte_d2439,8,0x40 - iVar3);
    }
    dword_ccc8c = iVar5;
    if ((dword_ccc90 == 0) && (0 < iVar6)) {
      sub_8fd84(byte_d2439,7,0x7e);
      sub_8fe1c(byte_d2439,7,0x24);
    }
    sub_8fdb2(byte_d2439,7,iVar6);
    iVar5 = iVar6 / 3 + 0x20;
    if (((byte)dword_c541f & 8) == 0) {
      iVar3 = 0;
    }
    else {
      iVar3 = 0x32;
    }
    if (iVar6 == iVar3 + 10) {
      sVar2 = randomrange(6,iVar6 % 3,iVar5);
      iVar5 = iVar5 + sVar2;
    }
    sub_8fde5(byte_d2439,7,iVar5);
    dword_ccc90 = iVar6;
  }
  return;
}


// ================================================================================================
// sound_pause_all @ 0x59748 [__watcall]
// ================================================================================================

void __watcall sound_pause_all(void)

{
  __CHK(0x10);
  if ((((byte)option_flags & 0x80) != 0) && (((byte)dword_c541f & 0x2a) != 0)) {
    if (0 < dword_ccc8c) {
      sub_8fdb2(byte_d2439,8,0);
      sub_8fe4f(byte_d2439,8);
      dword_ccc8c = 0;
    }
    if (0 < dword_ccc90) {
      sub_8fdb2(byte_d2439,7,0);
      sub_8fe4f(byte_d2439,7,0x24);
      dword_ccc90 = 0;
    }
  }
  return;
}


// ================================================================================================
// fade_ambient_audio @ 0x597e3 [__watcall]
// ================================================================================================

void __watcall fade_ambient_audio(void)

{
  uint uVar1;
  uint uVar2;
  short sVar3;
  
  __CHK(0x1c);
  uVar1 = crowd_noise;
  if ((((byte)option_flags & 0x80) != 0) && (((byte)dword_c541f & 0x2a) != 0)) {
    while (0 < crowd_noise._2_2_) {
      settimeout(1);
      uVar2 = crowd_noise;
      sVar3 = crowd_noise._2_2_ + -0x32;
      crowd_noise = CONCAT22(sVar3,(undefined2)crowd_noise);
      if (sVar3 < 0) {
        crowd_noise = uVar2 & 0xffff;
      }
      update_ambient_audio(2);
      waittimeout();
    }
    sound_pause_all();
    crowd_noise = CONCAT22((short)(uVar1 >> 0x10),(undefined2)crowd_noise);
  }
  return;
}


// ================================================================================================
// sound_resume_all @ 0x59863 [__watcall]
// ================================================================================================

void __watcall sound_resume_all(void)

{
  __CHK(8);
  dword_ccc88 = 0;
  dword_ccc8c = 0;
  dword_ccc90 = 0;
  return;
}


// ================================================================================================
// play_sfx @ 0x59884 [__watcall]
// ================================================================================================

void __watcall
play_sfx(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  int extraout_EDX;
  uint uVar1;
  undefined8 uVar3;
  int iVar2;
  
  __CHK(0xc);
  crowd_noise._0_2_ = (undefined2)param_1;
  uVar3 = speech_busy(param_1,param_1,unaff_EBX,unaff_ECX,unaff_EDX,unaff_ECX);
  uVar1 = (uint)((ulonglong)uVar3 >> 0x20);
  if ((((int)uVar3 == 0) || ((uVar1 == 0x9c && (((game_flags & 0x10) == 0 || (dword_ccc98 != 0))))))
     && (((dword_c541f != 8 && (dword_c541f != 4)) || ((uVar1 != 0xa0 && (uVar1 != 0xa1)))))) {
    if (uVar1 == 0x7d) {
      crowd_noise._2_2_ = crowd_noise._2_2_ + 500;
      return;
    }
    if ((dword_c541f == 4) && (uVar1 == 0xaa)) {
      sub_8f270(dword_ed7a4,dword_d2427);
      return;
    }
    if (uVar1 == 0x90) {
      iVar2 = 0x90;
      if (dword_c541f == 4) {
        sub_8f61d(0x90);
        iVar2 = extraout_EDX;
      }
      uVar1 = iVar2 + 1;
    }
    sub_8f61d(uVar1 & 0xffff);
  }
  return;
}


// ================================================================================================
// sub_59945 @ 0x59945 [__watcall]
// ================================================================================================

void __watcall
sub_59945(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  short sVar1;
  
  __CHK(0xc);
  if (dword_ccc84 != -1) {
    sVar1 = sub_8f80e(dword_ccc84,param_1,dword_ccc84,unaff_ECX,unaff_EDX,unaff_EBX);
    if (sVar1 == 0) {
      sub_8f7ae(dword_ccc84);
      dword_ccc84 = -1;
    }
  }
  return;
}


// ================================================================================================
// stop_crowd_loop @ 0x59981 [__watcall]
// ================================================================================================

void __watcall stop_crowd_loop(void)

{
  short sVar1;
  
  __CHK(8);
  if (dword_ccc84 != -1) {
    sVar1 = sub_8f80e(dword_ccc84);
    if (sVar1 == 0) {
      sub_8f67d(dword_ccc84);
      dword_ccc84 = -1;
    }
  }
  return;
}


// ================================================================================================
// play_sample_by_ptr @ 0x599b9 [__watcall]
// ================================================================================================

void __watcall
play_sample_by_ptr(int param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  __CHK(0xc);
  stop_crowd_loop();
  if ((((byte)dword_c541f & 0x11) == 0) && (param_1 != 0)) {
    dword_ccc84 = sub_8f270(param_1,dword_d2427,param_1,unaff_ECX,unaff_EDX,unaff_EBX);
  }
  return;
}


// ================================================================================================
// sfx_set_volume @ 0x599ee [__watcall]
// ================================================================================================

void __watcall sfx_set_volume(void)

{
  short sVar1;
  
  __CHK(4);
  if (dword_ccc84 != -1) {
    do {
      sVar1 = sub_8f80e(dword_ccc84);
    } while (sVar1 == 0);
  }
  return;
}


// ================================================================================================
// play_speech @ 0x59a11 [__watcall]
// ================================================================================================

void __watcall play_speech(int param_1)

{
  uint uVar1;
  undefined4 uVar2;
  
  __CHK(0xc);
  if (param_1 < 6) {
    if ((&unk_ed368)[param_1] == 0) {
      uVar1 = rand();
      param_1 = (int)(((ulonglong)uVar1 & 0xffffffff00007fff) % 3) + 6;
    }
    else {
      play_sample_by_ptr((&unk_ed368)[param_1]);
      param_1 = 0xc;
    }
  }
  if (param_1 < 9) {
    uVar2 = *(undefined4 *)(&unk_ed374 + param_1 * 4);
  }
  else {
    if (0xb < param_1) {
      return;
    }
    uVar2 = (&dword_ed35c)[param_1];
  }
  play_sample_by_ptr(uVar2);
  return;
}


// ================================================================================================
// speech_period_summary @ 0x59a7e [__watcall]
// ================================================================================================

void __watcall speech_period_summary(void)

{
  __CHK(4);
  if (((sound_enabled != '\0') && ((option_flags._1_1_ & 1) != 0)) && ((game_flags & 0x10) == 0)) {
    sub_837a8();
    sub_854ac();
    return;
  }
  return;
}


// ================================================================================================
// speech_busy @ 0x59aad [__watcall]
// ================================================================================================

undefined4 __watcall speech_busy(void)

{
  __CHK(4);
  if ((sound_enabled == '\0') || ((option_flags._1_1_ & 1) == 0)) {
    return 0;
  }
  __CHK(4);
  if ((speech_enabled != 0) &&
     ((*(int *)(dword_ed7ac + 0x60) != 0 || (*(int *)(dword_ed7ac + 0x5c) != 0)))) {
    return 1;
  }
  return 0;
}


// ================================================================================================
// say_goal_wrapper @ 0x59ad0 [__watcall]
// ================================================================================================

void __watcall say_goal_wrapper(undefined4 param_1)

{
  __CHK(0x10);
  if (((sound_enabled != '\0') && ((option_flags._1_1_ & 1) != 0)) && ((game_flags & 0x10) == 0)) {
    sub_837a8();
    say_goal(param_1);
  }
  return;
}


// ================================================================================================
// say_star_wrapper @ 0x59b0f [__watcall]
// ================================================================================================

void __watcall say_star_wrapper(undefined4 param_1)

{
  __CHK(8);
  if ((sound_enabled != '\0') && ((option_flags._1_1_ & 1) != 0)) {
    sub_837a8();
    say_star(param_1);
  }
  return;
}


// ================================================================================================
// say_penalty_wrapper @ 0x59b3c [__watcall]
// ================================================================================================

void __watcall say_penalty_wrapper(undefined4 param_1)

{
  __CHK(0x24);
  if ((sound_enabled != '\0') && ((option_flags._1_1_ & 1) != 0)) {
    sub_837a8();
    say_penalty(param_1);
  }
  return;
}


// ================================================================================================
// say_penalty_shot_wrapper @ 0x59b88 [__watcall]
// ================================================================================================

void __watcall say_penalty_shot_wrapper(undefined4 param_1)

{
  __CHK(8);
  if ((sound_enabled != '\0') && ((option_flags._1_1_ & 1) != 0)) {
    sub_837a8();
    say_penalty_shot(param_1);
  }
  return;
}


// ================================================================================================
// say_game_intro_wrapper @ 0x59bb5 [__watcall]
// ================================================================================================

void __watcall
say_game_intro_wrapper(int param_1,int unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  int iVar1;
  
  __CHK(0xc);
  iVar1 = param_1;
  if (0x19 < param_1) {
    iVar1 = 0xc;
  }
  if ((sound_enabled != '\0') && ((option_flags._1_1_ & 1) != 0)) {
    say_game_intro((&team_abbrev)[iVar1],(&team_abbrev)[unaff_EDX],(&team_abbrev)[param_1],iVar1,
                   unaff_ECX,unaff_EBX);
  }
  return;
}


// ================================================================================================
// say_period_score @ 0x59bfc [__watcall]
// ================================================================================================

void __watcall say_period_score(void)

{
  __CHK(4);
  if ((sound_enabled != '\0') && ((option_flags._1_1_ & 1) != 0)) {
    sub_84a7d();
    return;
  }
  return;
}


// ================================================================================================
// say_nhl_intro @ 0x59c1d [__watcall]
// ================================================================================================

void __watcall say_nhl_intro(void)

{
  __CHK(4);
  if ((sound_enabled != '\0') && ((option_flags._1_1_ & 1) != 0)) {
    sub_846b4();
    return;
  }
  return;
}


// ================================================================================================
// say_goodnight @ 0x59c3e [__watcall]
// ================================================================================================

void __watcall say_goodnight(void)

{
  __CHK(4);
  if ((sound_enabled != '\0') && ((option_flags._1_1_ & 1) != 0)) {
    sub_846c8();
    return;
  }
  return;
}


// ================================================================================================
// say_lineups @ 0x59c5f [__watcall]
// ================================================================================================

void __watcall say_lineups(void)

{
  __CHK(4);
  if ((sound_enabled != '\0') && ((option_flags._1_1_ & 1) != 0)) {
    sub_846dc();
    return;
  }
  return;
}


// ================================================================================================
// say_elsenhl @ 0x59c80 [__watcall]
// ================================================================================================

void __watcall say_elsenhl(void)

{
  __CHK(4);
  if ((sound_enabled != '\0') && ((option_flags._1_1_ & 1) != 0)) {
    sub_847ba();
    return;
  }
  return;
}


// ================================================================================================
// say_highlight_intro_wrapper @ 0x59ca9 [__watcall]
// ================================================================================================

void __watcall
say_highlight_intro_wrapper(int param_1,int unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  __CHK(8);
  if ((sound_enabled != '\0') && ((option_flags._1_1_ & 1) != 0)) {
    say_highlight_intro((&team_abbrev)[param_1],(&team_abbrev)[unaff_EDX],(&team_abbrev)[param_1],
                        unaff_ECX,unaff_EBX);
  }
  return;
}


// ================================================================================================
// say_series_result_wrapper @ 0x59cdd [__watcall]
// ================================================================================================

void __watcall say_series_result_wrapper(int param_1)

{
  __CHK(0x14);
  if ((sound_enabled != '\0') && ((option_flags._1_1_ & 1) != 0)) {
    say_series_result((&team_abbrev)[param_1]);
  }
  return;
}


// ================================================================================================
// say_playoff_intro_wrapper @ 0x59d16 [__watcall]
// ================================================================================================

void __watcall
say_playoff_intro_wrapper
          (int param_1,int unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX,undefined4 param_5)

{
  __CHK(0x10);
  if ((sound_enabled != '\0') && ((option_flags._1_1_ & 1) != 0)) {
    say_playoff_game_intro
              ((&team_abbrev)[param_1],(&team_abbrev)[unaff_EDX],(&team_abbrev)[param_1],unaff_EBX,
               unaff_ECX,param_5);
  }
  return;
}


// ================================================================================================
// speech_stop @ 0x59d54 [__watcall]
// ================================================================================================

void __watcall speech_stop(void)

{
  int iVar1;
  
  __CHK(4);
  if (sound_enabled != '\0') {
    do {
      iVar1 = sub_85507();
    } while (iVar1 == 0);
  }
  return;
}


// ================================================================================================
// preload_speech_wrapper @ 0x59d71 [__watcall]
// ================================================================================================

void __watcall
preload_speech_wrapper
          (undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  int iVar1;
  
  __CHK(0xc);
  if (sound_enabled != '\0') {
    do {
      iVar1 = preload_speech(param_1,unaff_EDX,param_1,unaff_EDX,unaff_ECX,unaff_EBX);
    } while (iVar1 == 0);
  }
  return;
}


// ================================================================================================
// set_animation @ 0x59d9a [__watcall]
// ================================================================================================

void __watcall set_animation(int param_1,short unaff_DX)

{
  __CHK(4);
  if (unaff_DX != *(short *)(param_1 + 0x38)) {
    *(undefined2 *)(param_1 + 0x3a) = 0;
    *(short *)(param_1 + 0x38) = unaff_DX;
    *(undefined2 *)(param_1 + 0x3c) = 0xffff;
  }
  return;
}


// ================================================================================================
// draw_rink_marks @ 0x59dbb [__watcall]
// ================================================================================================
// decompilation failed: 
Low-level Error: Overlapping input varnodes

// ================================================================================================
// switch_to_nearest @ 0x59e69 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall switch_to_nearest(int param_1,short unaff_DX)

{
  int *piVar1;
  short sVar2;
  int iVar3;
  short sVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  short sStackY_18;
  
  __CHK(0x28);
  uVar7 = 0xffffffff;
  sVar4 = user1_team;
  if (unaff_DX != 0) {
    sVar4 = (short)user2_team;
  }
  if (sVar4 == 1) {
    piVar1 = &entities;
  }
  else {
    piVar1 = &unk_dfb1c;
  }
  sStackY_18 = *(short *)(param_1 + 0x6a);
  sVar4 = 6;
  do {
    if ((((0 < *(short *)((int)piVar1 + 0x1a)) && ((*(byte *)((int)piVar1 + 0x45) & 4) == 0)) &&
        ((*(byte *)(piVar1 + 0x11) & 0x20) == 0)) &&
       (iVar5 = (int)(short)(*p_puck_x + (short)(char)((ushort)*(undefined2 *)p_puck_vx >> 8)) -
                (*piVar1 >> 0x10),
       iVar3 = (int)(short)(*p_puck_y + (short)(char)((ushort)*(undefined2 *)p_puck_vy >> 8)) -
               (piVar1[1] >> 0x10), uVar6 = iVar5 * iVar5 + iVar3 * iVar3, uVar6 <= uVar7)) {
      sVar2 = user2_slot;
      if (unaff_DX != 0) {
        sVar2 = _user1_slot;
      }
      if (*(short *)((int)piVar1 + 0x6a) != sVar2) {
        uVar7 = uVar6;
        sStackY_18 = *(short *)((int)piVar1 + 0x6a);
      }
    }
    piVar1 = piVar1 + 0x20;
    sVar4 = sVar4 + -1;
  } while (sVar4 != 0);
  sVar4 = _user1_slot;
  if (unaff_DX != 0) {
    sVar4 = user2_slot;
  }
  if (sVar4 == sStackY_18) {
    sub_532a2(param_1);
  }
  else if (unaff_DX == 0) {
    if (sStackY_18 != _user1_slot) {
      _user1_slot = find_switch_target((int)sStackY_18,(int)_user1_slot);
    }
  }
  else if (sStackY_18 != user2_slot) {
    user2_slot = find_switch_target((int)sStackY_18,(int)user2_slot);
  }
  return;
}


// ================================================================================================
// find_switch_target @ 0x59fe1 [__watcall]
// ================================================================================================

undefined4 __watcall find_switch_target(undefined4 param_1,undefined4 unaff_EDX)

{
  int iVar1;
  short sVar2;
  
  __CHK(0xc);
  sVar2 = (short)unaff_EDX;
  if ((-1 < sVar2) && (sVar2 < 0xc)) {
    iVar1 = sVar2 * 0x80;
    if (((&unk_df861)[iVar1] & 8) != 0) {
      return unaff_EDX;
    }
    (&unk_df860)[iVar1] = (&unk_df860)[iVar1] & 0xf5 | 2;
  }
  sVar2 = (short)param_1;
  if ((-1 < sVar2) && (sVar2 < 0xc)) {
    (&unk_df860)[sVar2 * 0x80] = (&unk_df860)[sVar2 * 0x80] | 8;
  }
  return param_1;
}


// ================================================================================================
// sub_5a03b @ 0x5a03b [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall sub_5a03b(int param_1)

{
  int iVar1;
  short sVar2;
  short sVar3;
  
  __CHK(0x14);
  iVar1 = *(int *)(param_1 + 0xf6);
  ram0x000e03bc = 0;
  sVar2 = 0;
  sVar3 = 6;
  do {
    if (0 < *(short *)(iVar1 + 0x1a)) {
      ram0x000e03bc =
           ram0x000e03bc + (*(int *)(param_1 + 0x44 + (*(int *)(iVar1 + 0x44) >> 0x18) * 2) >> 0x10)
      ;
      sVar2 = sVar2 + 1;
    }
    iVar1 = iVar1 + 0x80;
    sVar3 = sVar3 + -1;
  } while (sVar3 != 0);
  if (sVar2 != 0) {
    ram0x000e03bc = CONCAT22((undefined2)dword_e03be,(short)(ram0x000e03bc / (int)sVar2));
  }
  return;
}


// ================================================================================================
// choose_line @ 0x5a0a3 [__watcall]
// ================================================================================================

void __watcall choose_line(int param_1,int unaff_EDX)

{
  short sVar1;
  short sVar2;
  short sVar3;
  uint uVar4;
  short sVar5;
  char *pcVar6;
  short local_18;
  
  __CHK(0x1c);
  if (*(short *)(unaff_EDX + 0x36) == *(short *)(param_1 + 0x36)) {
    if ((*(byte *)(unaff_EDX + 0xd4) & 1) == 0) {
      sVar1 = *(short *)(param_1 + 0x2a);
      if (sVar1 < 6) {
        if (3 < sVar1) {
          sVar1 = sVar1 + -4;
        }
      }
      else {
        sVar1 = sVar1 + -6;
      }
    }
    else {
      sVar1 = *(short *)(unaff_EDX + 0x2a);
      if ((((game_flags & 1) != 0) && (sVar1 < 4)) && ((*(byte *)(unaff_EDX + 0xd4) & 0x40) == 0)) {
        sub_5a03b(unaff_EDX);
        if (*(short *)(unaff_EDX + 0x36) == *(short *)(param_1 + 0x36)) {
          uVar4 = *(uint *)(unaff_EDX + 0xd6);
        }
        else {
          uVar4 = 0xf33;
        }
        if (uVar4 < dword_e03ba._2_2_) {
          return;
        }
      }
      if (3 < sVar1) {
        sVar1 = 3;
      }
      if ((*(char *)(unaff_EDX + 0xd5) == '\x06') && ((sVar1 < 4 || (5 < sVar1)))) {
        sVar1 = 3;
      }
    }
    if ((*(char *)(unaff_EDX + 0xd5) == '\x01') && ((*(byte *)(unaff_EDX + 0xd4) & 0x80) != 0)) {
      sVar1 = sVar1 + 4;
    }
    pcVar6 = (char *)(sVar1 * 4 + (&off_cbd2e)[*(int *)(unaff_EDX + 0xd2) >> 0x18]);
    local_18 = *(short *)(unaff_EDX + 0x2a);
    sVar1 = sub_5a30c(unaff_EDX,(int)local_18);
    for (sVar2 = 0; sVar5 = -1, sVar2 < 4; sVar2 = sVar2 + 1) {
      sVar5 = (short)*pcVar6;
      pcVar6 = pcVar6 + 1;
      if (sVar5 < 0) break;
      sVar3 = sub_5a30c(unaff_EDX,(int)sVar5);
      if (*(uint *)(unaff_EDX + 0xd6) < (uint)(int)sVar3) break;
      if (sVar1 < sVar3) {
        local_18 = sVar5;
        sVar1 = sVar3;
      }
    }
    if (sVar5 < 0) {
      sVar5 = local_18;
    }
    if (sVar5 != *(short *)(unaff_EDX + 0x2a)) {
      *(short *)(unaff_EDX + 0x2a) = sVar5;
      if ((*(char *)(unaff_EDX + 0xd5) == '\x01') && (sVar5 == 2)) {
        *(byte *)(unaff_EDX + 0xd4) = *(byte *)(unaff_EDX + 0xd4) ^ 0x80;
      }
      if (sVar5 < 4) {
        sVar1 = *(short *)(unaff_EDX + 0x2c);
        sVar2 = sVar1 + 1;
        *(short *)(unaff_EDX + 0x2c) = sVar2;
        if (2 < sVar2) {
          *(short *)(unaff_EDX + 0x2c) = sVar1 + -2;
        }
      }
    }
  }
  else {
    sVar5 = 4;
    if ((short)(*(short *)(unaff_EDX + 0x36) - *(short *)(param_1 + 0x36)) < 0) {
      sVar5 = 6;
    }
    sVar1 = sub_5a30c(unaff_EDX,sVar5);
    if (sVar1 < 0xf33) {
      sVar2 = sub_5a30c(unaff_EDX,sVar5 + 1);
      if (sVar1 < sVar2) {
        sVar5 = sVar5 + 1;
      }
    }
    *(short *)(unaff_EDX + 0x2a) = sVar5;
  }
  sub_14afe(unaff_EDX == 0xdf714,(int)sVar5);
  *(byte *)(unaff_EDX + 0xd4) = *(byte *)(unaff_EDX + 0xd4) & 0xbf;
  return;
}


// ================================================================================================
// sub_5a288 @ 0x5a288 [__watcall]
// ================================================================================================

int __watcall sub_5a288(int param_1,short unaff_DX,undefined4 param_3,short unaff_CX)

{
  byte bVar1;
  byte *pbVar2;
  short sVar3;
  short sVar4;
  int unaff_ESI;
  short sVar5;
  
  if (unaff_DX < 6) {
    pbVar2 = (byte *)((unaff_DX + -4) * 5 + *(int *)(param_1 + 0xda) + 0x12);
    sVar5 = 5;
  }
  else {
    pbVar2 = (byte *)(unaff_CX * 4 + *(int *)(param_1 + 0xda) + 4);
    sVar5 = 4;
  }
  sVar3 = 0;
  for (sVar4 = 0; sVar4 < sVar5; sVar4 = sVar4 + 1) {
    bVar1 = *pbVar2;
    pbVar2 = pbVar2 + 1;
    sVar3 = sVar3 + *(short *)(unaff_ESI + 0x46 + (uint)bVar1 * 2);
  }
  return (int)sVar3 / (int)sVar5;
}


// ================================================================================================
// sub_5a2ee @ 0x5a2ee [__watcall]
// ================================================================================================

int __watcall sub_5a2ee(short param_1,short unaff_DX)

{
  byte bVar1;
  int iVar2;
  byte *pbVar3;
  short sVar4;
  short sVar5;
  short sVar6;
  
  __CHK(4);
  if (param_1 < 1) {
    iVar2 = 0xdf614;
  }
  else {
    iVar2 = 0xdf714;
  }
  __CHK(0x14);
  if (unaff_DX < 4) {
    pbVar3 = (byte *)(unaff_DX * 3 + *(int *)(iVar2 + 0xda));
    sVar6 = 3;
  }
  else if (unaff_DX < 6) {
    pbVar3 = (byte *)((unaff_DX + -4) * 5 + *(int *)(iVar2 + 0xda) + 0x12);
    sVar6 = 5;
  }
  else {
    pbVar3 = (byte *)(unaff_DX * 4 + *(int *)(iVar2 + 0xda) + 4);
    sVar6 = 4;
  }
  sVar4 = 0;
  for (sVar5 = 0; sVar5 < sVar6; sVar5 = sVar5 + 1) {
    bVar1 = *pbVar3;
    pbVar3 = pbVar3 + 1;
    sVar4 = sVar4 + *(short *)(iVar2 + 0x46 + (uint)bVar1 * 2);
  }
  return (int)sVar4 / (int)sVar6;
}


// ================================================================================================
// sub_5a30c @ 0x5a30c [__watcall]
// ================================================================================================

int __watcall sub_5a30c(int param_1,short unaff_DX)

{
  byte bVar1;
  byte *pbVar2;
  short sVar3;
  short sVar4;
  short sVar5;
  
  __CHK(0x14);
  if (unaff_DX < 4) {
    pbVar2 = (byte *)(unaff_DX * 3 + *(int *)(param_1 + 0xda));
    sVar5 = 3;
  }
  else if (unaff_DX < 6) {
    pbVar2 = (byte *)((unaff_DX + -4) * 5 + *(int *)(param_1 + 0xda) + 0x12);
    sVar5 = 5;
  }
  else {
    pbVar2 = (byte *)(unaff_DX * 4 + *(int *)(param_1 + 0xda) + 4);
    sVar5 = 4;
  }
  sVar3 = 0;
  for (sVar4 = 0; sVar4 < sVar5; sVar4 = sVar4 + 1) {
    bVar1 = *pbVar2;
    pbVar2 = pbVar2 + 1;
    sVar3 = sVar3 + *(short *)(param_1 + 0x46 + (uint)bVar1 * 2);
  }
  return (int)sVar3 / (int)sVar5;
}


// ================================================================================================
// predict_puck_goal_line @ 0x5a341 [__watcall]
// ================================================================================================

void __watcall predict_puck_goal_line(void)

{
  short sVar1;
  int iVar2;
  short sVar3;
  short *psVar4;
  short sVar5;
  
  __CHK(0x20);
  psVar4 = (short *)((int)&unk_df812 + 2);
  sVar5 = 0xe8;
  sVar1 = 0;
  do {
    if (1 < sVar1) {
      return;
    }
    sVar3 = *p_puck_y;
    if (((*(short *)p_puck_vy == 0) ||
        (iVar2 = ((int)(short)(sVar5 - sVar3) << 0xc) / (int)*(short *)p_puck_vy, iVar2 < 0)) ||
       (0xffff < iVar2)) {
LAB_0005a402:
      psVar4[1] = -1;
    }
    else {
      psVar4[1] = (short)iVar2;
      iVar2 = ((int)*(short *)p_puck_vx * (int)(short)(sVar5 - sVar3)) / (int)*(short *)p_puck_vy;
      if (0xffff < iVar2) goto LAB_0005a402;
      sVar3 = (short)iVar2 + *p_puck_x;
      if (0x9f < sVar3) {
        sVar3 = 0x140 - sVar3;
      }
      if (sVar3 < -0x9f) {
        sVar3 = -0x140 - sVar3;
      }
      *psVar4 = sVar3;
    }
    sVar5 = -sVar5;
    sVar1 = sVar1 + 1;
    psVar4 = psVar4 + 2;
  } while( true );
}


// ================================================================================================
// frame_offsets_lookup @ 0x5a425 [__watcall]
// ================================================================================================

void __watcall frame_offsets_lookup(int param_1)

{
  short sVar1;
  
  __CHK(0x10);
  dword_e03be._2_2_ = 0;
  dword_e03ba._2_2_ = 0;
  sVar1 = *(short *)(param_1 + 0x12);
  if ((-1 < sVar1) && (sVar1 < 0x468)) {
    if (sVar1 < 0x378) {
      if (0x283 < sVar1) {
        dword_e03ba._2_2_ = 0;
        dword_e03be._2_2_ = 0;
        return;
      }
    }
    else {
      sVar1 = sVar1 + -0xf4;
    }
    if (sVar1 < 0x2da) {
      if (0x293 < sVar1) {
        dword_e03ba._2_2_ = 0;
        dword_e03be._2_2_ = 0;
        return;
      }
    }
    else {
      sVar1 = sVar1 + -0x46;
    }
    dword_e03ba._2_2_ = (short)(char)(&frame_offsets)[(short)(sVar1 * 2)];
    dword_e03be._2_2_ = (short)(char)(&unk_cc149)[(short)(sVar1 * 2)];
    if ((*(byte *)(param_1 + 0x55) & 8) != 0) {
      dword_e03ba._2_2_ = -dword_e03ba._2_2_;
    }
  }
  return;
}


// ================================================================================================
// stick_offsets_lookup @ 0x5a4ad [__watcall]
// ================================================================================================

void __watcall stick_offsets_lookup(int param_1)

{
  short sVar1;
  
  __CHK(0x10);
  dword_e03be._2_2_ = 0;
  dword_e03ba._2_2_ = 0;
  sVar1 = *(short *)(param_1 + 0x12);
  if ((-1 < sVar1) && (((0x195 < sVar1 && (sVar1 < 0x21a)) || ((0x3cd < sVar1 && (sVar1 < 0x450)))))
     ) {
    if (0x3cd < sVar1) {
      sVar1 = sVar1 + -0x1b4;
    }
    sVar1 = (sVar1 + -0x196) * 2;
    dword_e03ba._2_2_ = (short)(char)(&unk_cc7a4)[sVar1];
    dword_e03be._2_2_ = (short)(char)(&unk_cc7a5)[sVar1];
    if ((*(byte *)(param_1 + 0x55) & 8) != 0) {
      dword_e03ba._2_2_ = -dword_e03ba._2_2_;
    }
  }
  return;
}


// ================================================================================================
// stick_offset_from_frame @ 0x5a534 [__watcall]
// ================================================================================================

void __watcall
stick_offset_from_frame
          (undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  short sVar1;
  short sVar2;
  undefined4 extraout_EDX;
  
  __CHK(0x10);
  stick_offsets_lookup(param_1,param_1,unaff_EBX,unaff_ECX,unaff_EDX,unaff_ECX,unaff_EBX);
  sVar2 = dword_e03be._2_2_;
  sVar1 = dword_e03ba._2_2_;
  frame_offsets_lookup(extraout_EDX);
  dword_e03ba._2_2_ = sVar1 - dword_e03ba._2_2_;
  dword_e03be._2_2_ = sVar2 - dword_e03be._2_2_;
  return;
}


// ================================================================================================
// adjust_strategy @ 0x5a581 [__watcall]
// ================================================================================================

void __watcall adjust_strategy(int param_1)

{
  short sVar1;
  
  __CHK(0x10);
  sVar1 = dword_df622._2_2_ - dword_df722._2_2_;
  if (param_1 != 0) {
    if (1 < sVar1) {
      byte_df7e8 = byte_df7e8 | 1;
      byte_df7e9 = 8;
      return;
    }
    if (sVar1 < -3) {
      dword_df7ea = 0xd9a;
      byte_df7e6 = 3;
      byte_df7e7 = 2;
    }
    else {
      dword_df7ea = 0xccc;
    }
    byte_df7e8 = byte_df7e8 | 1;
    byte_df7e9 = 1;
    return;
  }
  byte_df6e8 = byte_df6e8 & 0xfe;
  if (sVar1 < -1) {
    byte_df6e9 = 5;
    return;
  }
  if (3 < sVar1) {
    dword_df6ea = 0xd9a;
    byte_df6e9 = 4;
    byte_df6e6 = 3;
    byte_df6e7 = 2;
    return;
  }
  dword_df6ea = 0xccc;
  byte_df6e9 = 0;
  return;
}


// ================================================================================================
// sub_5a669 @ 0x5a669 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall sub_5a669(void)

{
  __CHK(0x14);
  byte_df7e8 = 0;
  byte_df6e8 = 0;
  byte_df6e6 = 3;
  byte_df6e7 = 2;
  byte_df7e6 = 3;
  byte_df7e7 = 2;
  if (_period_num < 4) {
    if (_period_num == 3) {
      adjust_strategy(0);
      adjust_strategy(1);
    }
    else {
      dword_df6ea = 0xccc;
      byte_df6e9 = 0;
      dword_df7ea = 0xccc;
      byte_df7e8 = 0x81;
      byte_df7e9 = 1;
    }
  }
  else {
    dword_df6ea = 0xd9a;
    byte_df6e9 = 2;
    dword_df7ea = 0xd9a;
    byte_df7e8 = 1;
    byte_df7e9 = 8;
  }
  word_df740 = 0;
  dword_df73c._2_2_ = 0;
  word_df640 = 0;
  _word_df63e = 0;
  if (((byte)option_flags & 4) != 0) {
    if ((user1_team != 1) && ((short)user2_team != 1)) {
      word_df640 = 2;
    }
    if ((user1_team != 2) && ((short)user2_team != 2)) {
      dword_df73c._2_2_ = 3;
      word_df740 = 2;
    }
  }
  return;
}


