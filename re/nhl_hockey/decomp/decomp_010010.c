// Decompiled by Ghidra from hockey.elf (via ledisasm ELF export)
// This is machine generated pseudo-C meant as a reference for porting, it does not compile as is.
#include "prototypes.h"

// ================================================================================================
// sub_10010 @ 0x10010 [__watcall]
// ================================================================================================

undefined4 __watcall sub_10010(int param_1)

{
  __CHK(4);
  if (param_1 != 0) {
    return dword_eda08;
  }
  return dword_eda0c;
}


// ================================================================================================
// sub_1002a @ 0x1002a [__watcall]
// ================================================================================================

void __watcall sub_1002a(uint *param_1,uint *unaff_EDX,uint *unaff_EBX,uint *unaff_ECX)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  uint uVar4;
  
  __CHK(0x14);
  piVar2 = (int *)sub_10010(1);
  piVar1 = (int *)piVar2[8];
  *unaff_ECX = 0;
  uVar4 = *unaff_ECX;
  *unaff_EBX = uVar4;
  *unaff_EDX = uVar4;
  *param_1 = uVar4;
  while (piVar3 = piVar1, piVar3 != (int *)0x0) {
    uVar4 = (*piVar3 - *piVar2) - piVar2[4];
    if ((*(byte *)((int)piVar3 + 0x19) & 0x80) == 0) {
      *unaff_EDX = *unaff_EDX + piVar3[4];
    }
    *unaff_EBX = *unaff_EBX + uVar4;
    if (*unaff_ECX < uVar4) {
      *unaff_ECX = uVar4;
    }
    piVar2 = piVar3;
    piVar1 = (int *)piVar3[8];
  }
  *param_1 = *unaff_EDX + *unaff_EBX;
  return;
}


// ================================================================================================
// main @ 0x10094 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall main(void)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined *puVar4;
  undefined local_84 [4];
  ushort uStack_80;
  undefined2 local_68 [2];
  undefined2 uStack_64;
  undefined auStack_4c [20];
  undefined local_38 [2];
  ushort local_36;
  ushort local_34;
  ushort uStack_32;
  int local_30;
  undefined local_2c [4];
  undefined local_28 [4];
  undefined local_24 [4];
  uint local_20;
  undefined4 local_1c;
  undefined auStack_18 [3];
  byte bStack_15;
  
  __CHK(0x9c);
  _dos_getdrive(&local_30);
  if ((local_30 != 2) && (iVar1 = sub_106c8(3), iVar1 < 0x800)) {
    printf(aInsufficientDiskSpaceFre);
                    /* WARNING: Subroutine does not return */
    exit(0);
  }
  iVar1 = _dos_getdiskfree(0,local_38);
  if (iVar1 != 0) {
    fatalerror(aErrorGettingDiskSpaceFre);
  }
  iVar1 = (uint)local_34 * (uint)uStack_32 + 0x3ff;
  iVar3 = iVar1 >> 0x1f;
  iVar1 = (int)((iVar1 + iVar3 * -0x400) - (uint)(iVar3 << 9 < 0)) >> 10;
  iVar1 = (iVar1 + 7) / iVar1 + 1;
  if (iVar1 <= (int)(uint)local_36) {
    local_68[0] = 0x100;
    uStack_64 = 0xa000;
    int386(0x31,local_68,local_84);
    initmem(200,0x19000);
    sub_1002a(&local_20,local_24,local_28,local_2c);
    if (local_20 < 0x1e5d70) {
      printf(aInsufficientMemoryAvaila);
      printf(aPleaseCheckYourReference);
                    /* WARNING: Subroutine does not return */
      exit(0);
    }
    if ((local_20 < 2100000) && ((uint)uStack_80 * 0x10 < 0x7f800)) {
      printf(aInsufficientConventional);
      printf(aPleaseCheckYourReference_c014d);
                    /* WARNING: Subroutine does not return */
      exit(0);
    }
    if (local_20 < 0x3ef001) {
      dword_c4cfc = 200000;
    }
    else {
      dword_c4cfc = 800000;
    }
    initgraphics(0x280,0x1e0);
    inittimer();
    _input_enabled = 0;
    addtimer(sub_10dcd);
    input_devices = input_devices | 8;
    iVar1 = initmouse();
    if (iVar1 != 0) {
      input_devices = input_devices | 1;
    }
    ui_init();
    (*(code *)mouse_update_callback)();
    sub_b3036(sub_3149d);
    load_nhl_cfg();
    set_video_mode(0x140,200);
    dword_c66c4 = subwindowdefadr(&dword_d30d4,0,0xa8,0x140,0x20);
    set_video_mode(0x280,0x1e0);
    zone_manager_init(100);
    puVar4 = install_path;
    if (byte_ed906 != '\x01') {
      puVar4 = (undefined *)0x0;
    }
    make_path(auStack_4c,puVar4,aPointer3,0);
    _dword_d8b6c = loadshapes(auStack_4c,0);
    pointer_shapes = locateshape(_dword_d8b6c,&aPntr);
    puVar4 = install_path;
    if (byte_ed92e != '\x01') {
      puVar4 = (undefined *)0x0;
    }
    make_path(auStack_4c,puVar4,&aS1,&aVFN);
    font_main = loadfile(auStack_4c,0x20);
    puVar4 = install_path;
    if (byte_ed935 != '\x01') {
      puVar4 = (undefined *)0x0;
    }
    font_current_default = font_main;
    make_path(auStack_4c,puVar4,aScor2b,&aVFN);
    font_scor2b = loadfile(auStack_4c,0x20);
    puVar4 = install_path;
    if (byte_ed936 != '\x01') {
      puVar4 = (undefined *)0x0;
    }
    make_path(auStack_4c,puVar4,aScor3b,&aVFN);
    font_scor3b = loadfile(auStack_4c,0x20);
    puVar4 = install_path;
    if (byte_ed990 != '\x01') {
      puVar4 = (undefined *)0x0;
    }
    make_path(auStack_4c,puVar4,aKaufm020,&aVFN);
    font_kaufm = loadfile(auStack_4c,0x20);
    setfont(font_current_default);
    apply_settings(&settings_exhibition);
    load_cfg_palette();
    intro_sequence();
    local_30 = joy_detect();
    joy_init(((byte_d416a & 0xf) == 0xf) + '\x01');
    if (((byte_d416a & 3) != 0) &&
       (((dword_d4158 != 0 || (dword_d415c != 0)) &&
        (joystick_calibrate(1,0,0,aConfigureLeftJoystick), (dword_d3040 & 1) != 0)))) {
      input_devices = input_devices | 2;
      joystick_enabled = 1;
    }
    if ((((byte_d416a & 0xc) != 0) && ((dword_d4160 != 0 || (dword_d4164 != 0)))) &&
       (joystick_calibrate(2,8,1,aConfigureRightJoystick), (dword_d3040 & 2) != 0)) {
      input_devices = input_devices | 4;
      dword_c4d04 = 1;
    }
    iVar1 = file_open_read(aGameSet,&local_1c);
    if (iVar1 == 0) {
      iVar1 = file_read(local_1c,&settings_exhibition,0xffffffff,0x75);
      if (iVar1 != 0) {
        fatalerror(&aD3);
      }
      iVar1 = file_close(&local_1c);
      if (iVar1 != 0) {
        fatalerror(&aD4);
      }
    }
    else {
      if ((input_devices & 2) == 0) {
        if ((input_devices & 4) == 0) {
          if ((input_devices & 8) == 0) {
            if ((input_devices & 1) == 0) {
              dword_c52fd = 0x10;
            }
            else {
              dword_c52fd = 1;
            }
          }
          else {
            dword_c52fd = 8;
          }
        }
        else {
          dword_c52fd = 4;
        }
      }
      else {
        dword_c52fd = 2;
      }
      dword_c5301 = 0x10;
      dword_c5305 = 0;
      dword_c5309 = 1;
      if (dword_c52fd == 0x10) {
        dword_c52f5 = 0xffffffff;
      }
      else {
        dword_c52f5 = 0xc;
      }
      dword_c52f9 = 0xfffffffe;
    }
    apply_settings(&settings_exhibition);
    loading_screen();
    _dos_gettime(auStack_18);
    srand((uint)bStack_15);
    frontend_main_menu();
    uVar2 = allocmem(&aTemp,0x300,0x20);
    if ((sound_enabled != '\0') && (dword_c721d != 0)) {
      sound_fade(dword_d2431,3,100);
    }
    getpalette(0,0x100,uVar2);
    fade_palette(1,uVar2);
    if ((sound_enabled != '\0') && (dword_c721d != 0)) {
      do {
        iVar1 = sound_channel_status(ram0x000d242c >> 0x18,3);
      } while (iVar1 == 0);
      releasememblock(dword_c721d);
      dword_c721d = 0;
    }
    loading_screen();
    ui_init();
    credits_screen();
    settextmode();
    (*(code *)funcptr_d41f0)();
    return;
  }
  iVar1 = iVar1 * (uint)local_34 * (uint)uStack_32 + 0x3ff;
  iVar3 = iVar1 >> 0x1f;
  printf(aInsufficientDiskSpaceFre_c007a,
         (int)((iVar1 + iVar3 * -0x400) - (uint)(iVar3 << 9 < 0)) >> 10);
                    /* WARNING: Subroutine does not return */
  exit(0);
}


// ================================================================================================
// sub_106c8 @ 0x106c8 [__watcall]
// ================================================================================================

undefined8 __watcall sub_106c8(undefined4 param_1,undefined4 unaff_EDX)

{
  int iVar1;
  undefined local_14 [2];
  ushort local_12;
  ushort uStack_10;
  ushort uStack_e;
  
  __CHK(0x1c);
  iVar1 = _dos_getdiskfree(param_1,local_14);
  if (iVar1 != 0) {
    fatalerror(aErrorGettingDiskSpaceFre_c01df);
  }
  return CONCAT44(unaff_EDX,(uint)uStack_e * (uint)local_12 * (uint)uStack_10);
}


// ================================================================================================
// sub_10712 @ 0x10712 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall sub_10712(void)

{
  __CHK(0x1c);
  if (dword_c5403 < 0) {
    user1_team = 0;
  }
  else if (dword_c5413 == 0) {
    user1_team = 1;
  }
  else {
    user1_team = 2;
  }
  if (dword_c5407 < 0) {
    user2_team._0_2_ = 0;
  }
  else if (dword_c5417 == 0) {
    user2_team._0_2_ = 1;
  }
  else {
    user2_team._0_2_ = 2;
  }
  dword_c4e0c = (uint)(dword_c5413 == dword_c5417);
  if (dword_c540b < 4) {
    if (dword_c540b != 0) {
      if (dword_c540b < 2) {
        controller_type = 1;
      }
      else if (dword_c540b == 2) {
        controller_type = 2;
      }
    }
  }
  else if (dword_c540b < 5) {
    controller_type = 4;
  }
  else if (7 < dword_c540b) {
    if (dword_c540b < 9) {
      controller_type = 8;
    }
    else if (dword_c540b == 0x10) {
      controller_type = 0;
    }
  }
  if (dword_c540f < 4) {
    if (dword_c540f != 0) {
      if (dword_c540f < 2) {
        byte_c4d1d = 1;
      }
      else if (dword_c540f == 2) {
        byte_c4d1d = 2;
      }
    }
  }
  else if (dword_c540f < 5) {
    byte_c4d1d = 4;
  }
  else if (7 < dword_c540f) {
    if (dword_c540f < 9) {
      byte_c4d1d = 8;
    }
    else if (dword_c540f == 0x10) {
      byte_c4d1d = 0;
    }
  }
  initmouse();
  setmousepos(0xa0,100);
  sub_b29f0();
  _input_enabled = 0;
  return;
}


// ================================================================================================
// sub_1086a @ 0x1086a [__watcall]
// ================================================================================================

undefined8 __watcall
sub_1086a(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  int iVar1;
  uint uVar2;
  
  uVar2 = 0;
  iVar1 = sub_b2cbe(0x48,0,unaff_EDX,unaff_ECX,unaff_EBX);
  if (iVar1 != 0) {
    uVar2 = 1;
  }
  iVar1 = sub_b2cbe(0x50,uVar2,unaff_EDX,unaff_ECX,unaff_EBX);
  if (iVar1 != 0) {
    uVar2 = uVar2 | 2;
  }
  iVar1 = sub_b2cbe(0x4b,uVar2,unaff_EDX,unaff_ECX,unaff_EBX);
  if (iVar1 != 0) {
    uVar2 = uVar2 | 8;
  }
  iVar1 = sub_b2cbe(0x4d,uVar2,unaff_EDX,unaff_ECX,unaff_EBX);
  if (iVar1 != 0) {
    uVar2 = uVar2 | 4;
  }
  iVar1 = sub_b2cbe(0x47,uVar2,unaff_EDX,unaff_ECX,unaff_EBX);
  if (iVar1 != 0) {
    uVar2 = uVar2 | 9;
  }
  iVar1 = sub_b2cbe(0x49);
  if (iVar1 != 0) {
    uVar2 = uVar2 | 5;
  }
  iVar1 = sub_b2cbe(0x51);
  if (iVar1 != 0) {
    uVar2 = uVar2 | 6;
  }
  iVar1 = sub_b2cbe(0x4f);
  if (iVar1 != 0) {
    uVar2 = uVar2 | 10;
  }
  uVar2 = *(int *)(&controller_type + uVar2) >> 0x18;
  iVar1 = sub_b2cbe(0x52);
  if (iVar1 == 0) {
LAB_00010933:
    iVar1 = sub_b2cbe(0x38);
    if (iVar1 != 0) {
      iVar1 = sub_b2cbe(0x39);
      if (iVar1 != 0) goto LAB_0001094f;
    }
    iVar1 = sub_b2cbe(0x52);
    if (iVar1 == 0) {
      iVar1 = sub_b2cbe(0x38);
      if (iVar1 == 0) {
        iVar1 = sub_b2cbe(0x1c);
        if (iVar1 == 0) {
          iVar1 = sub_b2cbe(0x39);
          if (iVar1 == 0) goto LAB_00010997;
        }
        uVar2 = uVar2 | 0x20;
        goto LAB_00010997;
      }
    }
    uVar2 = uVar2 | 0x10;
  }
  else {
    iVar1 = sub_b2cbe(0x1c);
    if (iVar1 == 0) goto LAB_00010933;
LAB_0001094f:
    uVar2 = uVar2 | 0x40;
  }
LAB_00010997:
  return CONCAT44(unaff_EDX,uVar2);
}


// ================================================================================================
// sub_109a1 @ 0x109a1 [__watcall]
// ================================================================================================

ulonglong __watcall sub_109a1(int param_1,undefined4 unaff_EDX)

{
  uint uVar1;
  uint uVar2;
  
  if ((&joystick_enabled)[param_1] == 0) {
    return CONCAT44(unaff_EDX,8);
  }
  if (param_1 == 0) {
    uVar2 = joystick_state & 0xff;
  }
  else {
    uVar2 = (int)joystick_state >> 8;
  }
  uVar1 = *(int *)(&controller_type + (uVar2 & 0xf)) >> 0x18;
  if (((uVar2 & 0x10) != 0) && ((uVar2 & 0x20) != 0)) {
    return CONCAT44(unaff_EDX,uVar1) | 0x40;
  }
  if ((uVar2 & 0x10) != 0) {
    return CONCAT44(unaff_EDX,uVar1) | 0x10;
  }
  if ((uVar2 & 0x20) != 0) {
    uVar1 = uVar1 | 0x20;
  }
  return CONCAT44(unaff_EDX,uVar1);
}


// ================================================================================================
// sub_109fc @ 0x109fc [__watcall]
// ================================================================================================

ulonglong __watcall
sub_109fc(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  short sVar1;
  uint uVar2;
  
  (*(code *)mouse_update_callback)(unaff_EDX,unaff_ECX,unaff_EBX);
  if ((100 - dword_d3030) * (100 - dword_d3030) + (dword_d302c + -0xa0) * (dword_d302c + -0xa0) <
      0x9c4) {
    uVar2 = 8;
  }
  else {
    sVar1 = direction8((int)(short)((short)dword_d302c + -0xa0),
                       (int)(short)(100 - (short)dword_d3030));
    uVar2 = (uint)sVar1;
  }
  if ((((byte)dword_d3034 & 1) != 0) && (((byte)dword_d3034 & 2) != 0)) {
    return CONCAT44(unaff_EDX,uVar2) | 0x40;
  }
  if (((byte)dword_d3034 & 1) != 0) {
    return CONCAT44(unaff_EDX,uVar2) | 0x10;
  }
  if (((byte)dword_d3034 & 2) != 0) {
    uVar2 = uVar2 | 0x20;
  }
  return CONCAT44(unaff_EDX,uVar2);
}


// ================================================================================================
// sub_10a86 @ 0x10a86 [__watcall]
// ================================================================================================

void __watcall sub_10a86(int param_1,undefined *unaff_EDX)

{
  char cVar1;
  undefined uVar2;
  undefined4 uVar3;
  undefined *extraout_EDX;
  undefined *extraout_EDX_00;
  undefined *puVar4;
  undefined *extraout_EDX_01;
  
  cVar1 = (&controller_type)[param_1];
  if (cVar1 == '\b') {
    uVar2 = sub_1086a();
    puVar4 = extraout_EDX;
  }
  else {
    if (cVar1 == '\x02') {
      uVar3 = 0;
    }
    else {
      if (cVar1 != '\x04') {
        if (cVar1 != '\x01') {
          *unaff_EDX = 8;
          return;
        }
        uVar2 = sub_109fc();
        puVar4 = extraout_EDX_01;
        goto LAB_00010aa5;
      }
      uVar3 = 1;
    }
    uVar2 = sub_109a1(uVar3);
    puVar4 = extraout_EDX_00;
  }
LAB_00010aa5:
  *puVar4 = uVar2;
  return;
}


// ================================================================================================
// sub_10ac6 @ 0x10ac6 [__watcall]
// ================================================================================================

void __watcall sub_10ac6(byte *param_1)

{
  int iVar1;
  byte bStack_14;
  
  bStack_14 = 0;
  iVar1 = sub_b2cbe();
  if (iVar1 == 0) {
    iVar1 = sub_b2cbe(0x1d);
    if (iVar1 == 0) {
      iVar1 = sub_b2cbe();
      if (iVar1 == 0) {
        iVar1 = sub_b2cbe();
        if (iVar1 == 0) {
          iVar1 = sub_b2cbe();
          if (iVar1 == 0) {
            iVar1 = sub_b2cbe();
            if (iVar1 == 0) {
              iVar1 = sub_b2cbe();
              if (iVar1 == 0) {
                iVar1 = sub_b2cbe();
                if (iVar1 == 0) {
                  iVar1 = sub_b2cbe();
                  if (iVar1 == 0) {
                    iVar1 = sub_b2cbe();
                    if (iVar1 == 0) {
                      iVar1 = sub_b2cbe();
                      if (iVar1 == 0) {
                        iVar1 = sub_b2cbe();
                        if (iVar1 == 0) {
                          iVar1 = sub_b2cbe();
                          if (iVar1 == 0) {
                            iVar1 = sub_b2cbe();
                            if (iVar1 != 0) {
                              bStack_14 = 0x13;
                            }
                          }
                          else {
                            bStack_14 = 0xf;
                          }
                        }
                        else {
                          bStack_14 = 0x44;
                        }
                      }
                      else {
                        bStack_14 = 0x43;
                      }
                    }
                    else {
                      bStack_14 = 0x42;
                    }
                  }
                  else {
                    bStack_14 = 0x41;
                  }
                }
                else {
                  bStack_14 = 0x40;
                }
              }
              else {
                bStack_14 = 0x3f;
              }
            }
            else {
              bStack_14 = 0x3e;
            }
          }
          else {
            bStack_14 = 0x3d;
          }
        }
        else {
          bStack_14 = 0x3c;
        }
      }
      else {
        bStack_14 = 0x3b;
      }
    }
    else {
      iVar1 = sub_b2cbe();
      if (iVar1 == 0) {
        iVar1 = sub_b2cbe();
        if (iVar1 != 0) {
          bStack_14 = 0x32;
        }
      }
      else {
        bStack_14 = 0x1f;
      }
    }
  }
  else {
    bStack_14 = 1;
  }
  if (byte_c4d1e == 0) {
    byte_c4d1e = bStack_14;
  }
  else if (bStack_14 == byte_c4d1e) {
    bStack_14 = 0;
  }
  else {
    byte_c4d1e = 0;
  }
  if (bStack_14 != 0) {
    bStack_14 = bStack_14 | 0x80;
  }
  *param_1 = bStack_14;
  return;
}


// ================================================================================================
// sub_10c7f @ 0x10c7f [__watcall]
// ================================================================================================

void __watcall sub_10c7f(byte *param_1,byte *unaff_EDX)

{
  int iVar1;
  uint uVar2;
  byte bStack_14;
  
  bStack_14 = 0;
  *param_1 = 0;
  iVar1 = sub_b2cbe(1);
  if (iVar1 == 0) {
    iVar1 = sub_b2cbe(0x52);
    if ((((((iVar1 == 0) && (iVar1 = sub_b2cbe(0x38), iVar1 == 0)) &&
          (iVar1 = sub_b2cbe(0x1c), iVar1 == 0)) && (iVar1 = sub_b2cbe(0x39), iVar1 == 0)) &&
        ((((input_devices & 2) == 0 && ((input_devices & 4) == 0)) ||
         ((uVar2 = joy_read(), (uVar2 & 0x30) == 0 && (((int)uVar2 >> 8 & 0x30U) == 0)))))) &&
       (((input_devices & 1) == 0 ||
        ((*(code *)mouse_update_callback)(), ((byte)dword_d3034 & 3) == 0)))) {
      iVar1 = sub_b2cbe(0x1d);
      if (iVar1 == 0) {
        iVar1 = sub_b2cbe();
        if (iVar1 != 0) {
          bStack_14 = 0xf;
        }
      }
      else {
        iVar1 = sub_b2cbe();
        if (iVar1 == 0) {
          iVar1 = sub_b2cbe();
          if (iVar1 != 0) {
            bStack_14 = 0x32;
          }
        }
        else {
          bStack_14 = 0x1f;
        }
      }
      if (byte_c4d1e == 0) {
        byte_c4d1e = bStack_14;
      }
      else if (bStack_14 == byte_c4d1e) {
        bStack_14 = 0;
      }
      else {
        byte_c4d1e = 0;
      }
      if (bStack_14 != 0) {
        bStack_14 = bStack_14 | 0x80;
      }
      *param_1 = bStack_14;
      return;
    }
    if ((game_flags & 0x10) != 0) {
      *unaff_EDX = *unaff_EDX | 0x10;
      return;
    }
  }
  *param_1 = 0x81;
  return;
}


// ================================================================================================
// sub_10dcd @ 0x10dcd [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall sub_10dcd(void)

{
  int iVar1;
  
  if (_input_enabled != 0) {
    if (frame_ticks < 1000) {
      frame_ticks = frame_ticks + 1;
    }
    dword_c4d18 = dword_c4d18 + -1;
    if (dword_c4d18 == -1) {
      dword_c4d18 = 4;
      if (control_count < 0x32) {
        iVar1 = control_read_idx + control_count;
        if (((controller_type & 6) != 0) || ((byte_c4d1d & 6) != 0)) {
          joystick_state = joy_read(iVar1 / 0x32);
        }
        iVar1 = (iVar1 % 0x32) * 3;
        sub_10a86(0,&control_ring + iVar1);
        sub_10a86(1,iVar1 + 0xd8b81);
        if (dword_c5130 == 0) {
          sub_10ac6(iVar1 + 0xd8b82);
        }
        else {
          sub_10c7f(iVar1 + 0xd8b82,&control_ring + iVar1);
        }
        control_count = control_count + 1;
      }
    }
  }
  return;
}


// ================================================================================================
// set_video_mode @ 0x10e9f [__watcall]
// ================================================================================================

void __watcall set_video_mode(int param_1,int unaff_EDX)

{
  __CHK(0x28);
  if ((param_1 != dword_c4e28) || (unaff_EDX != dword_c4e2c)) {
    setpalette(0,0x100,&palette_black);
    setdefaultscreen();
    setclip(0,dword_c4e28,0,dword_c4e2c);
    clearclip(0);
    settimeout(0x28);
    waitvsync();
    initgraphics(param_1,unaff_EDX);
    setpalette(0,0x100,&palette_black);
    setclip(0,param_1,0,unaff_EDX);
    clearclip(0);
    setmouselimits(0,0,param_1,unaff_EDX);
    dword_c4e28 = param_1;
    dword_c4e2c = unaff_EDX;
    waittimeout();
  }
  return;
}


// ================================================================================================
// sub_10f6d @ 0x10f6d [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall
sub_10f6d(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  __CHK(0x1c);
  if (_penalty_box_mode >> 0x10 != -1) {
    getpalette(0,0x100,&palette_save,unaff_EDX,unaff_ECX,unaff_EBX);
    fade_palette_to(1,&palette_save,0x10);
    set_video_mode(0x280,0x1e0);
    fade_ambient_audio();
    if (sound_enabled == '\0') {
      sound_stopall();
    }
    else {
      sub_837a8();
    }
    stop_crowd_loop();
    sub_1baf3(140000);
  }
  setfont(font_current_default);
  sub_190be();
  _period_num = _period_num + 1;
  return;
}


// ================================================================================================
// draw_player_number @ 0x11005 [__watcall]
// ================================================================================================

void __watcall draw_player_number(short param_1,short unaff_DX,short unaff_BX,short unaff_CX)

{
  short sVar1;
  short local_10;
  
  __CHK(0x1c);
  sVar1 = param_1 + 0xc0;
  local_10 = -unaff_DX + 0x14d;
  if (0 < unaff_CX) {
    sVar1 = param_1 + 0xbc;
  }
  if (-1 < unaff_CX) {
    local_10 = -unaff_DX + 0x14f;
  }
  if (9 < unaff_BX) {
    blit_sprite((&digit_shapes)[(short)((longlong)(int)unaff_BX / 10)],(int)(short)(sVar1 + -3),
                (int)local_10,0,0,0);
    unaff_BX = unaff_BX % 10;
    sVar1 = sVar1 + 4;
  }
  blit_sprite((&digit_shapes)[unaff_BX],(int)sVar1,(int)local_10,0,0,0);
  if (0 < unaff_CX) {
    blit_sprite(*(undefined4 *)(&position_letter_shapes + unaff_CX * 4),(int)(short)(sVar1 + 8),
                (int)local_10,0,0,0);
  }
  return;
}


// ================================================================================================
// draw_sprite_world @ 0x110e0 [__watcall]
// ================================================================================================

void __watcall draw_sprite_world(short param_1,short unaff_DX,short unaff_BX,short unaff_CX)

{
  int in_stack_00000002;
  
  __CHK(0x10);
  if (((-1 < param_1) && (param_1 < 0x46e)) && (*(int *)(&sprite_frames + param_1 * 4) != 0)) {
    blit_sprite(*(undefined4 *)(&sprite_frames + param_1 * 4),(int)(short)(unaff_DX + 0xc0),
                (int)(short)(0x140 - unaff_BX),(int)unaff_CX,in_stack_00000002 >> 0x10,1);
  }
  return;
}


// ================================================================================================
// sub_11136 @ 0x11136 [__watcall]
// ================================================================================================

void __watcall sub_11136(void)

{
  __CHK(0x18);
  blit_sprite(dword_d8c70,0x37,0x225,0,0xffffffff,0);
  return;
}


// ================================================================================================
// sub_11161 @ 0x11161 [__watcall]
// ================================================================================================

void __watcall sub_11161(undefined4 param_1)

{
  int iVar1;
  
  __CHK(0x18);
  while( true ) {
    iVar1 = sub_b2cbe(param_1);
    if (iVar1 == 0) break;
    getkey();
  }
  flushkeys();
  return;
}


// ================================================================================================
// handle_hotkey @ 0x1118f [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 __watcall handle_hotkey(byte param_1,undefined4 unaff_EDX)

{
  uint uVar1;
  undefined4 uVar2;
  
  __CHK(0x2c);
  if ((param_1 & 0x80) != 0) {
    param_1 = param_1 & 0x7f;
    if (param_1 < 0x32) {
      if (param_1 < 0xf) {
        if (param_1 == 1) {
          uVar2 = 1;
          pause_requested = 1;
          goto LAB_000113e9;
        }
      }
      else if (param_1 < 0x10) {
        show_names = (uint)(show_names == 0);
      }
      else if (0x12 < param_1) {
        if (param_1 < 0x14) {
          if (((game_flags & 0x10) == 0) && (_period_num != -1)) {
            dword_e9a9e = CONCAT22(input_enabled,(undefined2)dword_e9a9e);
            _input_enabled = 0;
            if ((controller_type == '\x01') || (byte_c4d1d == '\x01')) {
              dword_df00c = dword_d302c;
              dword_df010 = dword_d3030;
            }
            getpalette(0,0x100,&palette_save);
            fade_palette_to(1,&palette_save,0x10);
            fade_ambient_audio();
            if (sound_enabled == '\0') {
              sound_stopall();
            }
            else {
              sub_837a8();
            }
            sub_8374d();
            stop_crowd_loop();
            ui_init();
            instant_replay(1);
            event_queue_reset();
            ui_shutdown();
            if ((controller_type == '\x01') || (byte_c4d1d == '\x01')) {
              setmousepos(dword_df00c,dword_df010);
              setmouselimits(0,0,0x140,200);
            }
            word_cbec4 = 1;
            show_scoreboard((int)user2_team._2_2_,(int)_away_team_id,_period_num,0);
            _input_enabled = dword_e9a9e >> 0x10;
            uVar2 = 1;
            dword_c7444 = dword_c7444 + 1000;
            dword_c7448 = dword_c7448 + 1000;
            goto LAB_000113e9;
          }
        }
        else if (param_1 == 0x1f) {
          if ((option_flags & 0x80) != 0) {
            sound_pause_all();
            if (sound_enabled == '\0') {
              sound_stopall();
            }
            else {
              sub_837a8();
            }
            sfx_disable();
          }
          uVar1 = (uint)((option_flags & 0x80) == 0);
          option_flags = option_flags & 0xffffff7f;
          option_flags = option_flags | uVar1 << 7;
          if (uVar1 != 0) {
            sound_resume_all();
            sfx_enable();
          }
        }
      }
    }
    else if (param_1 < 0x33) {
      uVar1 = (uint)((option_flags & 0x40) == 0);
      option_flags = option_flags & 0xffffffbf;
      option_flags = option_flags | uVar1 << 6;
      if (uVar1 == 0) {
        stop_crowd_loop();
        music_disable();
      }
      else {
        music_enable();
      }
    }
    else if (param_1 < 0x3f) {
      if (0x3a < param_1) {
        word_e0304 = 1;
        word_e0380 = param_1 - 0x3b;
      }
    }
    else if (param_1 < 0x43) {
      word_e0306 = 1;
      word_e0382 = param_1 - 0x3f;
    }
    else {
      if (param_1 < 0x44) {
        uVar2 = 0;
      }
      else {
        if (param_1 != 0x44) goto LAB_000113e7;
        uVar2 = 1;
      }
      sub_671e8(uVar2);
    }
  }
LAB_000113e7:
  uVar2 = 0;
LAB_000113e9:
  return CONCAT44(unaff_EDX,uVar2);
}


// ================================================================================================
// get_frame_ticks @ 0x1145f [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 __watcall get_frame_ticks(undefined4 param_1,undefined4 unaff_EDX)

{
  undefined4 uVar1;
  
  __CHK(8);
  uVar1 = frame_ticks;
  dword_e9a9e = CONCAT22(input_enabled,(undefined2)dword_e9a9e);
  frame_ticks = 0;
  _input_enabled = (int)input_enabled;
  return CONCAT44(unaff_EDX,uVar1);
}


// ================================================================================================
// run_sim_steps @ 0x1149a [__watcall]
// ================================================================================================

void __watcall run_sim_steps(int param_1)

{
  byte bVar1;
  int iVar2;
  int extraout_EDX;
  int extraout_EDX_00;
  undefined *puVar3;
  undefined4 *puVar4;
  
  __CHK(0xc);
  puVar3 = &stack0xfffffff8;
  iVar2 = 0;
  while( true ) {
    if (param_1 <= iVar2) {
      return;
    }
    if (control_steps_left == 0) {
      *(undefined4 *)(puVar3 + -4) = 0x114bd;
      control_entry = get_key_event();
      if (control_entry == 0) {
        return;
      }
      bVar1 = *(byte *)(control_entry + 2);
      if ((bVar1 & 0x80) != 0) {
        *(undefined4 *)(puVar3 + -4) = 0x114db;
        iVar2 = handle_hotkey(bVar1);
        if (iVar2 == 1) {
          *(undefined4 *)(puVar3 + -4) = 0x114e5;
          flush_key_events();
          return;
        }
      }
      control_steps_left = 3;
    }
    if ((game_flags & 1) == 0) {
      if (penalty_shot_active == 0) {
        dword_d8c78 = dword_d8c78 + 100;
      }
      *(undefined4 *)(puVar3 + -4) = 0x11510;
      game_clock_tick();
    }
    puVar4 = (undefined4 *)(puVar3 + -4);
    puVar3 = puVar3 + -4;
    *puVar4 = 0x11515;
    sim_tick();
    control_steps_left = control_steps_left + -1;
    iVar2 = extraout_EDX;
    if (control_steps_left == 0) {
      *(undefined4 *)(puVar3 + -4) = 0x11527;
      next_key_event();
      iVar2 = extraout_EDX_00;
    }
    if (dword_c5840 != 0) {
      return;
    }
    if (period_over != 0) {
      return;
    }
    if (game_over != 0) break;
    iVar2 = iVar2 + 1;
  }
  return;
}


// ================================================================================================
// sub_11550 @ 0x11550 [__watcall]
// ================================================================================================

void __watcall sub_11550(int param_1)

{
  int iVar1;
  int iVar2;
  
  __CHK(0x28);
  iVar2 = 0;
  for (iVar1 = 0; iVar1 < 0x100; iVar1 = iVar1 + 0x80) {
    waitvbl_end();
    setpalette(iVar1,0x80,iVar2 + param_1);
    iVar2 = iVar2 + 0x180;
  }
  return;
}


// ================================================================================================
// fade_palette_to @ 0x11598 [__watcall]
// ================================================================================================

void __watcall fade_palette_to(int param_1,undefined1 *unaff_EDX,int unaff_EBX)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  __CHK(0x18);
  iVar4 = unaff_EBX;
  if (param_1 == 0) {
    dword_c4e24 = 0;
  }
  else {
    if ((dword_c4e24 != 0) && (2 < unaff_EBX)) {
      iVar4 = 2;
    }
    dword_c4e24 = 1;
  }
  if (iVar4 < 2) {
    if (param_1 != 0) {
      _memset_fill(&unk_d8c88,0,unaff_EBX,0x300);
      unaff_EDX = &unk_d8c88;
    }
    sub_11550(unaff_EDX);
  }
  else {
    byte_c5135 = (char)iVar4 + -1;
    byte_c5138 = (char)iVar4 + '\x01';
    for (iVar2 = *(int *)((int)&dword_c5130 + param_1 + 1) >> 0x18;
        iVar2 != *(int *)(&byte_c5135 + param_1) >> 0x18;
        iVar2 = iVar2 + (*(int *)((int)&dword_c5130 + param_1 + 3) >> 0x18)) {
      iVar3 = 0;
      do {
        cVar1 = unaff_EDX[iVar3];
        (&unk_d8c88)[iVar3] = (char)((cVar1 * iVar2) / iVar4);
        iVar3 = iVar3 + 1;
      } while (iVar3 < 0x300);
      sub_11550(&unk_d8c88,(cVar1 * iVar2) % iVar4);
    }
  }
  return;
}


// ================================================================================================
// game_loop @ 0x1167b [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall game_loop(void)

{
  int iVar1;
  undefined4 uVar2;
  undefined *puVar3;
  int extraout_EDX;
  int iVar4;
  undefined auStack_38 [32];
  
  __CHK(0x48);
  ticks_elapsed();
  do {
    _input_enabled = 1;
    if (game_over != 0) {
      _input_enabled = 0;
      sub_61b85();
      start_period();
      sub_1920f();
      dword_c53f7 = 1;
LAB_000113e9:
      sub_1b982();
      return;
    }
    while (period_over == 0) {
      iVar1 = get_frame_ticks();
      iVar4 = dword_d8c6c + iVar1 * 6;
      iVar1 = iVar4 / 10;
      dword_d8c6c = iVar4 % 10;
      run_sim_steps(iVar1);
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
      set_view_rect();
      dword_d8c40 = 0;
      draw_sprites((int)(short)dword_d8c7c,(int)(short)dword_d8c74);
      if (word_cbec4 != 0) {
        dword_e9a9e = CONCAT22(input_enabled,(undefined2)dword_e9a9e);
        _input_enabled = 0;
        getpalette(0,0x100,&palette_save);
        fade_palette_to(1,&palette_save,0x10);
        sub_61b85();
        _input_enabled = dword_e9a9e >> 0x10;
      }
      iVar1 = update_ambient_audio((int)(short)iVar1);
      if (penalty_shot_active == 0) {
        dword_dc28c = dword_d8c78 / 0x18;
        iVar1 = dword_d8c78 / 0x18;
        dword_d8c78 = dword_d8c78 % 0x18;
        if ((period_over != 0) &&
           (iVar1 = (int)(CONCAT22(clock_sub,clock_seconds) | CONCAT22(clock_seconds,period_idx)) >>
                    0x10, iVar1 == 0)) {
          iVar1 = (dword_c5708 + dword_c5704 * 0x3c) * 100 + dword_c570c;
          dword_dc28c = iVar1;
        }
      }
      else {
        dword_dc28c = 0;
      }
      draw_clock(iVar1);
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
      if (pause_requested != 0) {
        if (dword_c5130 != 0) {
          fade_palette_to(1,&unk_df314,0x10);
          dword_c53f7 = 2;
          goto LAB_000113e9;
        }
        dword_e9a9e = CONCAT22(input_enabled,(undefined2)dword_e9a9e);
        _input_enabled = dword_c5130;
        if ((controller_type == '\x01') || (byte_c4d1d == '\x01')) {
          dword_df00c = dword_d302c;
          dword_df010 = dword_d3030;
        }
        fade_ambient_audio();
        if (sound_enabled == '\0') {
          sound_stopall();
        }
        else {
          sub_837a8();
        }
        stop_crowd_loop();
        sub_8374d();
        sub_61b85();
        setfont(font_current_default);
        getpalette(0,0x100,&palette_save);
        fade_palette_to(1,&palette_save,0x10);
        set_video_mode(0x280,0x1e0);
        pause_menu(0);
        if (dword_c53f7 == 2) goto LAB_000113e9;
        set_video_mode(0x140,200);
        if ((controller_type == '\x01') || (byte_c4d1d == '\x01')) {
          setmousepos(dword_df00c,dword_df010);
        }
        word_cbec4 = 1;
        pause_requested = 0;
        preload_speech_wrapper((&team_abbrev)[user2_team._2_2_],(&team_abbrev)[_away_team_id]);
        show_scoreboard((int)user2_team._2_2_,(int)_away_team_id,_period_num,0);
        iVar1 = (int)dword_cbeca._2_2_;
        dword_c7444 = dword_c7444 + 1000;
        dword_c7448 = dword_c7448 + 1000;
        if (((iVar1 != -1) && (word_cbece != -1)) && (dword_e0244 == 0)) {
          puVar3 = install_path;
          if ((&file_on_disk)[*(int *)(&unk_cc080 + iVar1 * 4)] != '\x01') {
            puVar3 = (undefined *)0x0;
          }
          make_path(auStack_38,puVar3,(&off_cbed0)[iVar1],&aPPV);
          dword_e0244 = loadfile(auStack_38,0x20);
          iVar1 = 0;
          while( true ) {
            iVar4 = shapecount(dword_e0244);
            if (iVar4 <= iVar1) break;
            uVar2 = getshape(dword_e0244,iVar1);
            (&unk_def8c)[iVar1] = uVar2;
            iVar1 = iVar1 + 1;
          }
        }
        _input_enabled = dword_e9a9e >> 0x10;
        flush_key_events();
      }
      if (dword_c5840 != 0) {
        dword_e9a9e = CONCAT22(input_enabled,(undefined2)dword_e9a9e);
        _input_enabled = 0;
        sub_61a27();
        _input_enabled = dword_e9a9e >> 0x10;
        dword_c5840 = extraout_EDX;
        flush_key_events();
      }
    }
    _input_enabled = 0;
    if (dword_c5130 != 0) {
      fade_palette_to(1,&unk_df314,0x10);
      dword_c53f7 = 1;
      goto LAB_000113e9;
    }
    end_of_period();
    if (dword_c53f7 == 2) goto LAB_000113e9;
    if (game_over == 0) {
      select_game_surface();
      preload_speech_wrapper((&team_abbrev)[user2_team._2_2_],(&team_abbrev)[_away_team_id]);
      show_scoreboard((int)user2_team._2_2_,(int)_away_team_id,_period_num,1);
      play_speech(0);
    }
    if ((controller_type == '\x01') || (byte_c4d1d == '\x01')) {
      setmousepos(0xa0,100);
    }
    word_e0306 = 0;
    word_e0304 = 0;
    dword_c5840 = 0;
    control_steps_left = 0;
    period_over = 0;
    dword_d8c6c = 0;
    dword_d8c78._0_2_ = 0;
    dword_d8c78._2_2_ = 0;
    flush_key_events();
  } while( true );
}


// ================================================================================================
// play_game @ 0x11d09 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall play_game(int *param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int *extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 *extraout_EDX_01;
  undefined *puVar4;
  undefined auStack_58 [32];
  char acStack_38 [32];
  
  __CHK(100);
  if (*param_1 < 0) {
    load_music_banks();
    load_player_graphics();
    load_team_palettes((int)user2_team._2_2_,(int)_away_team_id);
    wait_sprite_fade();
    set_video_mode(0x140,200);
    if (user2_team._2_2_ < 0x1a) {
      iVar1 = (int)user2_team._2_2_;
    }
    else {
      iVar1 = 0xc;
    }
    load_rink(iVar1);
    dword_c7448 = 0;
    dword_c7444 = 0;
    iVar1 = sub_13e8f();
    if (iVar1 < 0) {
      dword_c53f7 = 2;
      sub_1b982();
      setdefaultscreen();
      goto LAB_00011fdd;
    }
    sub_1c852();
  }
  else {
    if ((option_flags._1_1_ & 2) == 0) {
      sub_15b76();
      param_1 = extraout_EDX;
    }
    savegame_io(*param_1);
    file_close(extraout_EDX_00);
    *extraout_EDX_01 = 0xffffffff;
    build_lines();
    sub_65b48();
    count_dressed_players(0);
    count_dressed_players(1);
    sub_1c807();
    sound_resume_all();
    sub_1c852();
    if (_penalty_box_mode >> 0x10 != -1) {
      wait_sprite_fade();
      dword_c53f7 = 0;
      pause_menu(0);
      if (dword_c53f7 == 2) {
        sub_1b982();
        return;
      }
      set_video_mode(0x140,200);
      if ((controller_type == '\x01') || (byte_c4d1d == '\x01')) {
        setmousepos(dword_df00c,dword_df010);
      }
      word_cbec4 = 1;
      pause_requested = 0;
      show_scoreboard((int)user2_team._2_2_,(int)_away_team_id,_period_num,0);
      iVar1 = (int)dword_cbeca._2_2_;
      dword_c7444 = dword_c7444 + 1000;
      dword_c7448 = dword_c7448 + 1000;
      if (((iVar1 != -1) && (word_cbece != -1)) && (dword_e0244 == 0)) {
        puVar4 = install_path;
        if ((&file_on_disk)[*(int *)(&unk_cc080 + iVar1 * 4)] != '\x01') {
          puVar4 = (undefined *)0x0;
        }
        make_path(auStack_58,puVar4,(&off_cbed0)[iVar1],&aPPV);
        dword_e0244 = loadfile(auStack_58,0x20);
        for (iVar1 = 0; iVar3 = shapecount(dword_e0244), iVar1 < iVar3; iVar1 = iVar1 + 1) {
          uVar2 = getshape(dword_e0244,iVar1);
          (&unk_def8c)[iVar1] = uVar2;
        }
      }
      preload_speech_wrapper((&team_abbrev)[user2_team._2_2_],(&team_abbrev)[_away_team_id]);
    }
  }
  skip_faceoff_wait = 0;
  dword_c53f7 = 0;
  flush_key_events();
  game_loop();
  sub_1cb7f();
  if ((dword_c53fb != 0) && (dword_c53f7 == 1)) {
    option_flags._1_1_ = option_flags._1_1_ & 0x7f;
    strcpy(acStack_38,&league_dir);
    strcat(acStack_38,&unk_c0200);
    strcat(acStack_38,aGameSav);
    sub_903e8(acStack_38);
  }
LAB_00011fdd:
  set_video_mode(0x280,0x1e0);
  return;
}


// ================================================================================================
// set_state @ 0x11ff4 [__watcall]
// ================================================================================================

void __watcall set_state(int param_1,undefined unaff_DL)

{
  __CHK(8);
  *(undefined *)((*(int *)(param_1 + 0x1a) >> 0x10) + 0x1e + param_1) = unaff_DL;
  *(byte *)(param_1 + 0x44) = *(byte *)(param_1 + 0x44) | 2;
  return;
}


// ================================================================================================
// set_state_reset @ 0x12011 [__watcall]
// ================================================================================================

void __watcall set_state_reset(int param_1,short unaff_DX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  uint uVar1;
  
  __CHK(8);
  uVar1 = CONCAT22((short)((uint)unaff_EBX >> 0x10),*(undefined2 *)(param_1 + 0x1c)) - 1U &
          0xffff0007;
  *(short *)(param_1 + 0x1c) = (short)uVar1;
  set_state(param_1,(int)unaff_DX,uVar1,unaff_ECX,unaff_EBX);
  return;
}


// ================================================================================================
// sub_12034 @ 0x12034 [__watcall]
// ================================================================================================

undefined4 __watcall sub_12034(void)

{
  __CHK(4);
  if ((replay_write_ptr == replay_buffer) && ((action_flags & 0x10) == 0)) {
    return 1;
  }
  return 0;
}


// ================================================================================================
// load_award_stats @ 0x1205d [__watcall]
// ================================================================================================

undefined8 __watcall load_award_stats(undefined4 param_1,undefined4 unaff_EDX)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  ushort *puVar7;
  undefined4 *puVar8;
  ushort *puVar9;
  uint uVar10;
  undefined4 *puVar11;
  undefined4 auStackY_418 [10];
  byte bStackY_3ef;
  byte bStackY_3ee;
  byte bStackY_3ed;
  byte bStackY_3dd;
  int aiStackY_3cc [25];
  int aiStackY_368 [142];
  ushort auStackY_130 [24];
  ushort local_100;
  ushort uStackY_fe;
  ushort local_fc;
  undefined4 auStackY_f8 [11];
  undefined4 uStackY_cc;
  undefined4 uStackY_c4;
  undefined4 uStackY_98;
  ushort uStackY_90;
  ushort local_8e [7];
  short sStackY_80;
  ushort uStackY_7e;
  undefined4 uStackY_78;
  ushort local_68;
  ushort local_66;
  ushort local_64;
  char cStackY_62;
  undefined auStackY_60 [32];
  char local_40;
  char local_3f;
  char local_3e;
  char local_3d;
  char local_3c;
  char local_3b;
  char local_3a;
  char cStackY_39;
  char local_38;
  char cStackY_37;
  char cStackY_36;
  uint local_34;
  uint local_30;
  int local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  int iStackY_1c;
  
  __CHK(0x41c);
  local_20 = 0xffffffff;
  local_24 = 0xffffffff;
  local_28 = 0xffffffff;
  make_path(auStackY_60,&league_dir,off_c80e7,&aDB);
  iVar2 = db_open_check(auStackY_60,&unk_ddac4,1);
  if (iVar2 == 0) {
    make_path(auStackY_60,&league_dir,off_c80e7,&aDB);
    iVar2 = file_open_read(auStackY_60,&local_20);
  }
  if (iVar2 == 0) {
    make_path(auStackY_60,&league_dir,off_c80d7,&aDB);
    iVar2 = file_open_read(auStackY_60,&local_24);
  }
  if (iVar2 == 0) {
    make_path(auStackY_60,&league_dir,off_c80eb,&aDB);
    iVar2 = file_open_read(auStackY_60,&local_28);
  }
  _memset_fill(&local_40,0,iVar2,0xb);
  iStackY_1c = 0;
  do {
    if ((0x19 < iStackY_1c) || (iVar2 != 0)) {
      file_close(&local_28);
      file_close(&local_24);
      file_close(&local_20);
      return CONCAT44(unaff_EDX,iVar2);
    }
    iVar2 = db_read_record(local_20,auStackY_418,iStackY_1c);
    iVar6 = (uint)bStackY_3ed + (uint)bStackY_3ef * 2;
    if ((bStackY_3ef == 0) && (bStackY_3ee == 0)) {
      uVar4 = 0;
    }
    else {
      uVar4 = ((uint)bStackY_3ef * 100) / ((uint)bStackY_3ee + (uint)bStackY_3ef);
    }
    if ((((cStackY_39 == '\0') || (local_2c < iVar6)) ||
        ((iVar6 == local_2c && ((int)local_30 < (int)uVar4)))) ||
       (((iVar6 == local_2c && (uVar4 == local_30)) && (byte_d9299 < bStackY_3ef)))) {
      puVar8 = auStackY_418;
      puVar11 = &unk_d9270;
      for (iVar3 = 0xba; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar11 = *puVar8;
        puVar8 = puVar8 + 1;
        puVar11 = puVar11 + 1;
      }
      local_2c = iVar6;
      local_30 = uVar4;
      cStackY_39 = -1;
    }
    if ((cStackY_36 == '\0') || ((int)local_34 < (int)(uint)bStackY_3dd)) {
      puVar8 = auStackY_418;
      puVar11 = &unk_d8f88;
      for (iVar6 = 0xba; iVar6 != 0; iVar6 = iVar6 + -1) {
        *puVar11 = *puVar8;
        puVar8 = puVar8 + 1;
        puVar11 = puVar11 + 1;
      }
      local_34 = (uint)bStackY_3dd;
      cStackY_36 = -1;
    }
    iVar6 = 0;
    while ((iVar6 < 0x19 && (iVar2 == 0))) {
      if (aiStackY_3cc[iVar6] != -1) {
        iVar2 = sub_1463d(local_24,&uStackY_c4,aiStackY_3cc[iVar6]);
        if (iVar2 == 0) {
          iVar2 = sub_1478b(local_28,&uStackY_90,uStackY_98);
        }
        puVar9 = (ushort *)off_c524f;
        if ((iVar2 == 0) && (uStackY_90 != 0)) {
          if (local_40 == '\0') {
LAB_00012307:
            puVar8 = &uStackY_c4;
            puVar11 = &unk_d9558;
            for (iVar3 = 0xd; iVar3 != 0; iVar3 = iVar3 + -1) {
              *puVar11 = *puVar8;
              puVar8 = puVar8 + 1;
              puVar11 = puVar11 + 1;
            }
            puVar7 = &uStackY_90;
            for (iVar3 = 0xb; iVar3 != 0; iVar3 = iVar3 + -1) {
              *(undefined4 *)puVar9 = *(undefined4 *)puVar7;
              puVar7 = puVar7 + 2;
              puVar9 = puVar9 + 2;
            }
            *puVar9 = *puVar7;
            *(undefined *)(puVar9 + 1) = *(undefined *)(puVar7 + 1);
            local_40 = -1;
          }
          else if ((*(ushort *)(off_c524f + 2) < local_8e[0]) ||
                  ((local_8e[0] == *(ushort *)(off_c524f + 2) && (uStackY_90 < *(ushort *)off_c524f)
                   ))) goto LAB_00012307;
          puVar9 = (ushort *)off_c5253;
          uVar1 = (ushort)local_8e._4_4_;
          if (local_3f == '\0') {
LAB_00012363:
            puVar8 = &uStackY_c4;
            puVar11 = &unk_d958c;
            for (iVar3 = 0xd; iVar3 != 0; iVar3 = iVar3 + -1) {
              *puVar11 = *puVar8;
              puVar8 = puVar8 + 1;
              puVar11 = puVar11 + 1;
            }
            puVar7 = &uStackY_90;
            for (iVar3 = 0xb; iVar3 != 0; iVar3 = iVar3 + -1) {
              *(undefined4 *)puVar9 = *(undefined4 *)puVar7;
              puVar7 = puVar7 + 2;
              puVar9 = puVar9 + 2;
            }
            *puVar9 = *puVar7;
            *(undefined *)(puVar9 + 1) = *(undefined *)(puVar7 + 1);
            local_3f = -1;
          }
          else if ((*(ushort *)(off_c5253 + 6) < uVar1) ||
                  ((uVar1 == *(ushort *)(off_c5253 + 6) && (uStackY_90 < *(ushort *)off_c5253))))
          goto LAB_00012363;
          puVar9 = (ushort *)off_c5257;
          if (uStackY_c4._2_1_ == 'D') {
            if (local_3e != '\0') {
              if ((uVar1 <= *(ushort *)(off_c5257 + 6)) &&
                 ((uVar1 != *(ushort *)(off_c5257 + 6) || (*(ushort *)off_c5257 <= uStackY_90))))
              goto LAB_000123f7;
            }
            puVar8 = &uStackY_c4;
            puVar11 = &unk_d95c0;
            for (iVar3 = 0xd; iVar3 != 0; iVar3 = iVar3 + -1) {
              *puVar11 = *puVar8;
              puVar8 = puVar8 + 1;
              puVar11 = puVar11 + 1;
            }
            puVar7 = &uStackY_90;
            for (iVar3 = 0xb; iVar3 != 0; iVar3 = iVar3 + -1) {
              *(undefined4 *)puVar9 = *(undefined4 *)puVar7;
              puVar7 = puVar7 + 2;
              puVar9 = puVar9 + 2;
            }
            *puVar9 = *puVar7;
            *(undefined *)(puVar9 + 1) = *(undefined *)(puVar7 + 1);
            local_3e = -1;
          }
LAB_000123f7:
          puVar9 = (ushort *)off_c525b;
          if (((uStackY_c4._2_1_ == 'L') || (uStackY_c4._2_1_ == 'R')) || (uStackY_c4._2_1_ == 'C'))
          {
            if (local_3d != '\0') {
              if ((sStackY_80 <= *(short *)(off_c525b + 0x10)) &&
                 ((sStackY_80 != *(short *)(off_c525b + 0x10) ||
                  (*(ushort *)off_c525b <= uStackY_90)))) goto LAB_00012466;
            }
            puVar8 = &uStackY_c4;
            puVar11 = &unk_d95f4;
            for (iVar3 = 0xd; iVar3 != 0; iVar3 = iVar3 + -1) {
              *puVar11 = *puVar8;
              puVar8 = puVar8 + 1;
              puVar11 = puVar11 + 1;
            }
            puVar7 = &uStackY_90;
            for (iVar3 = 0xb; iVar3 != 0; iVar3 = iVar3 + -1) {
              *(undefined4 *)puVar9 = *(undefined4 *)puVar7;
              puVar7 = puVar7 + 2;
              puVar9 = puVar9 + 2;
            }
            *puVar9 = *puVar7;
            *(undefined *)(puVar9 + 1) = *(undefined *)(puVar7 + 1);
            local_3d = -1;
          }
LAB_00012466:
          puVar9 = (ushort *)off_c5267;
          if ((uStackY_c4._2_1_ != 'G') && (cStackY_62 != '\0')) {
            if (local_3a != '\0') {
              if ((uVar1 <= *(ushort *)(off_c5267 + 6)) &&
                 ((uVar1 != *(ushort *)(off_c5267 + 6) || (*(ushort *)off_c5267 <= uStackY_90))))
              goto LAB_000124d6;
            }
            puVar8 = &uStackY_c4;
            puVar11 = &unk_d9690;
            for (iVar3 = 0xd; iVar3 != 0; iVar3 = iVar3 + -1) {
              *puVar11 = *puVar8;
              puVar8 = puVar8 + 1;
              puVar11 = puVar11 + 1;
            }
            puVar7 = &uStackY_90;
            for (iVar3 = 0xb; iVar3 != 0; iVar3 = iVar3 + -1) {
              *(undefined4 *)puVar9 = *(undefined4 *)puVar7;
              puVar7 = puVar7 + 2;
              puVar9 = puVar9 + 2;
            }
            *puVar9 = *puVar7;
            *(undefined *)(puVar9 + 1) = *(undefined *)(puVar7 + 1);
            local_3a = -1;
          }
LAB_000124d6:
          puVar9 = (ushort *)off_c526f;
          if (local_38 == '\0') {
LAB_00012505:
            puVar8 = &uStackY_c4;
            puVar11 = &unk_d96f8;
            for (iVar3 = 0xd; iVar3 != 0; iVar3 = iVar3 + -1) {
              *puVar11 = *puVar8;
              puVar8 = puVar8 + 1;
              puVar11 = puVar11 + 1;
            }
            puVar7 = &uStackY_90;
            for (iVar3 = 0xb; iVar3 != 0; iVar3 = iVar3 + -1) {
              *(undefined4 *)puVar9 = *(undefined4 *)puVar7;
              puVar7 = puVar7 + 2;
              puVar9 = puVar9 + 2;
            }
            *puVar9 = *puVar7;
            *(undefined *)(puVar9 + 1) = *(undefined *)(puVar7 + 1);
            local_38 = -1;
          }
          else if ((*(ushort *)(off_c526f + 0x18) < (ushort)uStackY_78) ||
                  (((ushort)uStackY_78 == *(ushort *)(off_c526f + 0x18) &&
                   (uStackY_7e < *(ushort *)(off_c526f + 0x12))))) goto LAB_00012505;
          if (byte_c524d == '\x01') {
            uVar10 = (uint)*(ushort *)(off_c5273 + 0x28) + (uint)*(ushort *)(off_c5273 + 0x2a);
            uVar4 = (uint)*(ushort *)(off_c5273 + 0x2c);
          }
          else {
            uVar4 = (uint)*(ushort *)(off_c5273 + 0x32) + (uint)*(ushort *)(off_c5273 + 0x30);
            uVar10 = (uint)*(ushort *)(off_c5273 + 0x34);
          }
          uVar5 = (uint)local_68 + (uint)local_66 + (uint)local_64;
          if (((cStackY_37 == '\0') || (uVar4 + uVar10 < uVar5)) ||
             ((uVar5 == uVar4 + uVar10 && (uStackY_90 < *(ushort *)off_c5273)))) {
            puVar8 = &uStackY_c4;
            puVar11 = &unk_d972c;
            for (iVar3 = 0xd; iVar3 != 0; iVar3 = iVar3 + -1) {
              *puVar11 = *puVar8;
              puVar8 = puVar8 + 1;
              puVar11 = puVar11 + 1;
            }
            puVar9 = &uStackY_90;
            puVar7 = &unk_d98c3;
            for (iVar3 = 0xb; iVar3 != 0; iVar3 = iVar3 + -1) {
              *(undefined4 *)puVar7 = *(undefined4 *)puVar9;
              puVar9 = puVar9 + 2;
              puVar7 = puVar7 + 2;
            }
            *puVar7 = *puVar9;
            *(undefined *)(puVar7 + 1) = *(undefined *)(puVar9 + 1);
            off_c5273 = (undefined *)&unk_d98c3;
            byte_c524d = '\x01';
            cStackY_37 = -1;
          }
        }
      }
      iVar6 = iVar6 + 1;
    }
    iVar6 = 0;
    while ((iVar6 < 3 && (iVar2 == 0))) {
      if (aiStackY_368[iVar6] != -1) {
        iVar2 = sub_1463d(local_24,auStackY_f8,aiStackY_368[iVar6]);
        if (iVar2 == 0) {
          iVar2 = sub_3a266(local_28,auStackY_130,uStackY_cc);
        }
        puVar9 = (ushort *)off_c525f;
        if ((iVar2 == 0) && (auStackY_130[0] != 0)) {
          if (local_3c == '\0') {
LAB_00012697:
            puVar8 = auStackY_f8;
            puVar11 = &unk_d9628;
            for (iVar3 = 0xd; iVar3 != 0; iVar3 = iVar3 + -1) {
              *puVar11 = *puVar8;
              puVar8 = puVar8 + 1;
              puVar11 = puVar11 + 1;
            }
            puVar7 = auStackY_130;
            for (iVar3 = 0xd; iVar3 != 0; iVar3 = iVar3 + -1) {
              *(undefined4 *)puVar9 = *(undefined4 *)puVar7;
              puVar7 = puVar7 + 2;
              puVar9 = puVar9 + 2;
            }
            *puVar9 = *puVar7;
            local_3c = -1;
          }
          else if ((*(ushort *)(off_c525f + 2) < (ushort)auStackY_130._2_4_) ||
                  (((ushort)auStackY_130._2_4_ == *(ushort *)(off_c525f + 2) &&
                   (*(ushort *)(off_c525f + 0x14) < (ushort)auStackY_130._20_4_))))
          goto LAB_00012697;
          puVar9 = (ushort *)off_c5263;
          if (0x18 < auStackY_130[0]) {
            if (local_3b != '\0') {
              if ((*(ushort *)(off_c5263 + 0x10) <= (ushort)auStackY_130._16_4_) &&
                 (((ushort)auStackY_130._16_4_ != *(ushort *)(off_c5263 + 0x10) ||
                  ((ushort)auStackY_130._12_4_ <= *(ushort *)(off_c5263 + 0xc)))))
              goto LAB_0001272b;
            }
            puVar8 = auStackY_f8;
            puVar11 = &unk_d965c;
            for (iVar3 = 0xd; iVar3 != 0; iVar3 = iVar3 + -1) {
              *puVar11 = *puVar8;
              puVar8 = puVar8 + 1;
              puVar11 = puVar11 + 1;
            }
            puVar7 = auStackY_130;
            for (iVar3 = 0xd; iVar3 != 0; iVar3 = iVar3 + -1) {
              *(undefined4 *)puVar9 = *(undefined4 *)puVar7;
              puVar7 = puVar7 + 2;
              puVar9 = puVar9 + 2;
            }
            *puVar9 = *puVar7;
            local_3b = -1;
          }
LAB_0001272b:
          if (byte_c524d == '\x01') {
            uVar4 = (uint)*(ushort *)(off_c5273 + 0x2a) + (uint)*(ushort *)(off_c5273 + 0x28);
            uVar10 = (uint)*(ushort *)(off_c5273 + 0x2c);
          }
          else {
            uVar10 = (uint)*(ushort *)(off_c5273 + 0x30) + (uint)*(ushort *)(off_c5273 + 0x32);
            uVar4 = (uint)*(ushort *)(off_c5273 + 0x34);
          }
          uVar5 = (uint)local_fc + (uint)local_100 + (uint)uStackY_fe;
          if (((cStackY_37 == '\0') || (uVar4 + uVar10 < uVar5)) ||
             ((uVar5 == uVar4 + uVar10 && (auStackY_130[0] < *(ushort *)off_c5273)))) {
            puVar8 = &uStackY_c4;
            puVar11 = &unk_d972c;
            for (iVar3 = 0xd; iVar3 != 0; iVar3 = iVar3 + -1) {
              *puVar11 = *puVar8;
              puVar8 = puVar8 + 1;
              puVar11 = puVar11 + 1;
            }
            puVar9 = auStackY_130;
            puVar7 = &unk_d9794;
            for (iVar3 = 0xd; iVar3 != 0; iVar3 = iVar3 + -1) {
              *(undefined4 *)puVar7 = *(undefined4 *)puVar9;
              puVar9 = puVar9 + 2;
              puVar7 = puVar7 + 2;
            }
            *puVar7 = *puVar9;
            off_c5273 = (undefined *)&unk_d9794;
            byte_c524d = '\0';
            cStackY_37 = -1;
          }
        }
      }
      iVar6 = iVar6 + 1;
    }
    iStackY_1c = iStackY_1c + 1;
  } while( true );
}


// ================================================================================================
// league_leaders_screen @ 0x12849 [__watcall]
// ================================================================================================

undefined8 __watcall league_leaders_screen(undefined4 param_1,undefined4 unaff_EDX)

{
  char cVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  undefined *puVar5;
  char *pcVar6;
  undefined4 *puVar7;
  int iVar8;
  undefined2 *puVar9;
  int iVar10;
  byte bVar11;
  char acStack_58 [44];
  undefined4 local_2c;
  undefined2 *local_28;
  undefined2 *local_24;
  int local_20;
  int iStack_1c;
  
  bVar11 = 0;
  __CHK(0x6c);
  iVar8 = 0;
  event_queue_reset();
  local_20 = 0;
  while ((iVar10 = local_20, local_20 < 0xb && (iVar8 != 3))) {
    set_text_colors(*(undefined4 *)(&unk_c513c + local_20 * 4),0);
    getticks();
    puVar5 = install_path;
    if ((&file_on_disk)[*(int *)(&unk_c5168 + iVar10 * 4)] != '\x01') {
      puVar5 = (undefined *)0x0;
    }
    make_path(acStack_58,puVar5,(&off_c5194)[iVar10],0);
    local_2c = loadshapes(acStack_58,0);
    uVar2 = getshape(local_2c,1);
    drawshape_home(uVar2);
    iVar8 = local_20;
    if ((&unk_c5244)[local_20] == '\x02') {
      if (local_20 == 10) {
        pcVar6 = (char *)&unk_d8f88;
      }
      else {
        pcVar6 = (char *)&unk_d9270;
      }
      strcpy(acStack_58,pcVar6);
      iVar8 = sub_909e0(acStack_58,&aANA,3);
      if (iVar8 == 0) {
        iVar8 = textwidth(&unk_c03a3);
        pcVar6 = &unk_c03a3;
      }
      else {
        if (local_20 == 10) {
          pcVar6 = &unk_d8f8d;
        }
        else {
          pcVar6 = &unk_d9275;
        }
        strcpy(acStack_58,pcVar6);
        iVar8 = sub_909e0(acStack_58,&aCal,3);
        if ((iVar8 == 0) || (iVar8 = sub_909e0(acStack_58,&aFlo,3), iVar8 == 0)) {
          pcVar6 = &unk_c03c4;
        }
        else {
          pcVar6 = &unk_c03c6;
        }
        strcat(acStack_58,pcVar6);
        iVar8 = textwidth(acStack_58);
        pcVar6 = acStack_58;
      }
      print_text_at(0x1fe - (iVar8 >> 1),0x76,pcVar6);
    }
    else {
      sprintf(acStack_58,aSS,local_20 * 0x34 + 0xd955b,local_20 * 0x34 + 0xd956b);
      iVar10 = textwidth(acStack_58);
      print_text_at(0x1fe - (iVar10 >> 1),0x76,acStack_58);
      strcpy(acStack_58,&unk_ddac4 + (uint)*(byte *)(&unk_d9558 + iVar8 * 0xd) * 0x15);
      iVar10 = sub_909e0(acStack_58,&aANA,3);
      if (iVar10 == 0) {
        puVar7 = (undefined4 *)&unk_c03a3;
        pcVar6 = acStack_58;
        for (iVar8 = 6; iVar8 != 0; iVar8 = iVar8 + -1) {
          *(undefined4 *)pcVar6 = *puVar7;
          puVar7 = puVar7 + (uint)bVar11 * -2 + 1;
          pcVar6 = (char *)((int)pcVar6 + ((uint)bVar11 * -2 + 1) * 4);
        }
        *pcVar6 = *(undefined *)puVar7;
      }
      else {
        cVar1 = *(char *)(&unk_d9558 + iVar8 * 0xd);
        if (((cVar1 == '\x02') || (cVar1 == '\x18')) || (cVar1 == '\x19')) {
          pcVar6 = &unk_c03c4;
        }
        else {
          pcVar6 = &unk_c03c6;
        }
        strcat(acStack_58,pcVar6);
      }
      iVar8 = textwidth(acStack_58);
      uVar3 = (uint)byte_d42c3;
      print_text_at(0x1fe - (iVar8 >> 1),uVar3 + 0x76,acStack_58);
      iVar8 = local_20;
      iVar4 = 0x1a4;
      iVar10 = uVar3 + 0xa2;
      if ((&unk_c5244)[local_20] == '\0') {
        print_text_at(0x1a4,iVar10,&aGP);
        print_text_at(0x1a4,(uint)byte_d42c3 + iVar10,&aMin);
        print_text_at(0x1a4,(uint)byte_d42c3 * 2 + iVar10,&aGAA);
        print_text_at(0x1a4,(uint)byte_d42c3 * 3 + iVar10,&aW);
        print_text_at(0x1a4,(uint)byte_d42c3 * 4 + iVar10,&aL);
        print_text_at(0x1a4,(uint)byte_d42c3 * 5 + iVar10,&aT);
        print_text_at(0x1a4,(uint)byte_d42c3 * 6 + iVar10,&aSO);
        print_text_at(0x1a4,(uint)byte_d42c3 * 7 + iVar10,&aEN);
        print_text_at(0x1a4,(uint)byte_d42c3 * 8 + iVar10,aShots);
        print_text_at(0x1a4,(uint)byte_d42c3 * 9 + iVar10,&aPct);
        puVar9 = (undefined2 *)(&off_c524f)[iVar8];
        iStack_1c = 0;
        local_24 = puVar9;
        do {
          iVar8 = iVar4 + 0x34;
          iVar4 = iVar4 + 0x50;
          print_text_at(iVar8,iVar10 - (uint)byte_d42c3,(&off_c527b)[iStack_1c]);
          sub_176ae(iVar4,iVar10,&aD_c5283,*puVar9);
          sub_176ae(iVar4,(uint)byte_d42c3 + iVar10,&aD_c5283,puVar9[6]);
          sub_176db(iVar4,(uint)byte_d42c3 * 2 + iVar10,aD02d_c5286,(ushort)puVar9[8] / 100,
                    (uint)(ushort)puVar9[8] % 100);
          sub_176ae(iVar4,(uint)byte_d42c3 * 3 + iVar10,&aD_c5283,puVar9[1]);
          sub_176ae(iVar4,(uint)byte_d42c3 * 4 + iVar10,&aD_c5283,puVar9[2]);
          if (iStack_1c == 0) {
            sub_176ae(iVar4,(uint)byte_d42c3 * 5 + iVar10,&aD_c5283,puVar9[3]);
          }
          sub_176ae(iVar4,(uint)byte_d42c3 * 6 + iVar10,&aD_c5283,puVar9[4]);
          sub_176ae(iVar4,(uint)byte_d42c3 * 7 + iVar10,&aD_c5283,puVar9[5]);
          sub_176ae(iVar4,(uint)byte_d42c3 * 8 + iVar10,&aD_c5283,puVar9[9]);
          sub_176db(iVar4,(uint)byte_d42c3 * 9 + iVar10,aD01d,(ushort)puVar9[10] / 10,
                    (uint)(ushort)puVar9[10] % 10);
          puVar9 = local_24 + 0xb;
          iStack_1c = iStack_1c + 1;
        } while (iStack_1c < 2);
      }
      else if ((&unk_c5244)[local_20] == '\x01') {
        print_text_at(0x1a4,iVar10,&aGP);
        print_text_at(0x1a4,(uint)byte_d42c3 + iVar10,&aG);
        print_text_at(0x1a4,(uint)byte_d42c3 * 2 + iVar10,&aA);
        print_text_at(0x1a4,(uint)byte_d42c3 * 3 + iVar10,&aPt);
        print_text_at(0x1a4,(uint)byte_d42c3 * 4 + iVar10,&aPIM);
        print_text_at(0x1a4,(uint)byte_d42c3 * 5 + iVar10,&unk_c03fa);
        print_text_at(0x1a4,(uint)byte_d42c3 * 6 + iVar10,&aPPG);
        print_text_at(0x1a4,(uint)byte_d42c3 * 7 + iVar10,&aSHG);
        print_text_at(0x1a4,(uint)byte_d42c3 * 8 + iVar10,aShots);
        print_text_at(0x1a4,(uint)byte_d42c3 * 9 + iVar10,&aPct);
        puVar9 = (undefined2 *)(&off_c524f)[iVar8];
        iStack_1c = 0;
        local_28 = puVar9;
        do {
          iVar8 = iVar4 + 0x34;
          iVar4 = iVar4 + 0x50;
          print_text_at(iVar8,iVar10 - (uint)byte_d42c3,(&off_c527b)[iStack_1c]);
          sub_176ae(iVar4,iVar10,&aD_c5283,*puVar9);
          sub_176ae(iVar4,(uint)byte_d42c3 + iVar10,&aD_c5283,puVar9[1]);
          sub_176ae(iVar4,(uint)byte_d42c3 * 2 + iVar10,&aD_c5283,puVar9[2]);
          sub_176ae(iVar4,(uint)byte_d42c3 * 3 + iVar10,&aD_c5283,puVar9[3]);
          sub_176ae(iVar4,(uint)byte_d42c3 * 4 + iVar10,&aD_c5283,puVar9[6]);
          sub_176ae(iVar4,(uint)byte_d42c3 * 5 + iVar10,&aD_c5283,*(int *)(puVar9 + 7) >> 0x10);
          sub_176ae(iVar4,(uint)byte_d42c3 * 6 + iVar10,&aD_c5283,puVar9[4]);
          sub_176ae(iVar4,(uint)byte_d42c3 * 7 + iVar10,&aD_c5283,puVar9[5]);
          sub_176ae(iVar4,(uint)byte_d42c3 * 8 + iVar10,&aD_c5283,puVar9[7]);
          if (puVar9[7] == 0) {
            uVar3 = 0;
          }
          else {
            uVar3 = ((uint)(ushort)puVar9[1] * 1000 + (ushort)puVar9[7] / 2) /
                    (uint)(ushort)puVar9[7];
          }
          sub_176db(iVar4,(uint)byte_d42c3 * 9 + iVar10,aD01d,uVar3 / 10,uVar3 % 10);
          puVar9 = local_28 + 9;
          iStack_1c = iStack_1c + 1;
        } while (iStack_1c < 2);
      }
    }
    iVar8 = 0x1ba;
    iVar10 = local_20 * 8;
    if (*(int *)(&unk_c51f0 + iVar10) != 0) {
      iVar8 = textwidth(*(int *)(&unk_c51f0 + iVar10));
      print_text_at(0x1fe - (iVar8 >> 1),0x1ba,*(undefined4 *)(&unk_c51f0 + iVar10));
      iVar8 = 0x1ba - (uint)byte_d42c3;
    }
    iVar10 = local_20;
    iVar4 = textwidth((&off_c51ec)[local_20 * 2]);
    print_text_at(0x1fe - (iVar4 >> 1),iVar8,(&off_c51ec)[iVar10 * 2]);
    iVar8 = locateshape(local_2c,&aPal);
    fade_palette(0,iVar8 + 0x10,0x10);
    freemem(local_2c);
    iVar8 = sub_33e6a(10000);
    uVar2 = allocmem(aPalmem,0x300,0);
    getpalette(0,0x100,uVar2);
    fade_palette(1,uVar2,0x10);
    freemem(uVar2);
    local_20 = local_20 + 1;
  }
  return CONCAT44(unaff_EDX,iVar8);
}


// ================================================================================================
// team_abbrev_lookup @ 0x13188 [__watcall]
// ================================================================================================

void __watcall team_abbrev_lookup(void)

{
  int iVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  undefined4 *puVar6;
  char acStackY_48 [44];
  int iStackY_1c;
  
  __CHK(0x4c);
  iStackY_1c = 0;
  do {
    iVar4 = iStackY_1c;
    iVar1 = iStackY_1c * 0x13 + 0x8c;
    print_text_at(0x14,iVar1,(&off_c51c0)[iStackY_1c]);
    if ((&unk_c5244)[iVar4] == '\x02') {
      iVar3 = sub_909e0(acStackY_48,&aANA,3);
      if (iVar3 == 0) {
        pcVar5 = &unk_c03a3;
      }
      else {
        if (iVar4 == 10) {
          pcVar5 = &unk_d8f8d;
        }
        else {
          pcVar5 = &unk_d9275;
        }
        strcpy(acStackY_48,pcVar5);
        iVar4 = sub_909e0(acStackY_48,&aCal,3);
        if ((iVar4 == 0) || (iVar4 = sub_909e0(acStackY_48,&aFlo,3), iVar4 == 0)) {
          pcVar5 = &unk_c03c4;
        }
        else {
          pcVar5 = &unk_c03c6;
        }
        strcat(acStackY_48,pcVar5);
        pcVar5 = acStackY_48;
      }
    }
    else {
      sub_29c75(acStackY_48,iVar4 * 0x34 + 0xd955b,iVar4 * 0x34 + 0xd956b,0xd2);
      print_text_at(0xb4,iVar1,acStackY_48);
      strcpy(acStackY_48,&unk_ddac4 + (uint)*(byte *)(&unk_d9558 + iVar4 * 0xd) * 0x15);
      iVar3 = sub_909e0(acStackY_48,&aANA,3);
      if (iVar3 == 0) {
        puVar6 = (undefined4 *)&unk_c03a3;
        pcVar5 = acStackY_48;
        for (iVar4 = 6; iVar4 != 0; iVar4 = iVar4 + -1) {
          *(undefined4 *)pcVar5 = *puVar6;
          puVar6 = puVar6 + 1;
          pcVar5 = (char *)((int)pcVar5 + 4);
        }
        *pcVar5 = *(undefined *)puVar6;
        pcVar5 = acStackY_48;
      }
      else {
        cVar2 = *(char *)(&unk_d9558 + iVar4 * 0xd);
        if (((cVar2 == '\x02') || (cVar2 == '\x18')) || (cVar2 == '\x19')) {
          pcVar5 = &unk_c03c4;
        }
        else {
          pcVar5 = &unk_c03c6;
        }
        strcat(acStackY_48,pcVar5);
        pcVar5 = acStackY_48;
      }
    }
    print_text_at(400,iVar1,pcVar5);
    iStackY_1c = iStackY_1c + 1;
  } while (iStackY_1c < 0xb);
  return;
}


// ================================================================================================
// awards_screen @ 0x13320 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall awards_screen(void)

{
  void *__dest;
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined *puVar4;
  char *pcVar5;
  undefined4 unaff_EDI;
  undefined auStack_68 [64];
  undefined auStack_28 [16];
  
  __CHK(0x78);
  event_queue_reset();
  __dest = (void *)allocmem(aPalmem,0x300,0x20);
  getpalette(0,0x100,__dest);
  if ((sound_enabled != '\0') && (dword_c721d != 0)) {
    sound_fade(dword_d2431,3,0x32);
  }
  fade_palette(1,__dest,0x10);
  if ((sound_enabled != '\0') && (dword_c721d != 0)) {
    do {
      iVar1 = sound_channel_status(ram0x000d242c >> 0x18,3);
    } while (iVar1 == 0);
    releasememblock(dword_c721d);
    dword_c721d = 0;
  }
  getfontstate(auStack_68);
  setfont(font_kaufm);
  puVar4 = install_path;
  if (byte_ed9aa != '\x01') {
    puVar4 = (undefined *)0x0;
  }
  make_path(auStack_28,puVar4,aAwardsi,0);
  uVar2 = loadshapes(auStack_28,0);
  uVar3 = locateshape(uVar2,&aScrn);
  drawshape_home(uVar3);
  uVar3 = locateshape(uVar2,&aTitl);
  drawshape_home(uVar3);
  iVar1 = locateshape(uVar2,&aPal);
  memcpy(__dest,(void *)(iVar1 + 0x10),0x300);
  freemem(uVar2);
  if ((sound_enabled == '\0') || (dword_c721d != 0)) {
    if (dword_c541f != 1) {
      puVar4 = install_path;
      if (dword_c541f == 8) {
        pcVar5 = aMtafan;
        if (byte_ed8c6 != '\x01') {
          puVar4 = (undefined *)0x0;
        }
      }
      else {
        pcVar5 = aAdafan;
        if (byte_ed7e4 != '\x01') {
          puVar4 = (undefined *)0x0;
        }
      }
      make_path(auStack_28,puVar4,pcVar5,0);
      unaff_EDI = sub_8f13b(auStack_28);
      play_sample_by_ptr();
    }
  }
  else {
    puVar4 = install_path;
    if (byte_ed9ec != '\x01') {
      puVar4 = (undefined *)0x0;
    }
    make_path(auStack_28,puVar4,aAwards,&aIff);
    dword_c721d = loadsound(auStack_28);
    if ((dword_c721d != 0) && (((byte)option_flags & 0x40) != 0)) {
      playsample(dword_c721d,dword_d2431,3,0x4c);
    }
  }
  fade_palette(0,__dest,0x10);
  if ((sound_enabled == '\0') && (dword_c541f != 1)) {
    sfx_set_volume();
    fade_palette(1,__dest,0x10);
    stop_crowd_loop();
    sub_8f1fe(unaff_EDI);
  }
  else if (sound_enabled == '\0') {
    sub_33e6a(0x140);
    fade_palette(1,__dest,0x10);
  }
  else {
    iVar1 = 0;
    while ((iVar1 == 0 && (iVar1 = sound_channel_status(ram0x000d242c >> 0x18,3), iVar1 == 0))) {
      iVar1 = sub_33e6a(10);
    }
    sound_fade(dword_d2431,3,0x32);
    fade_palette(1,__dest);
    do {
      iVar1 = sound_channel_status(ram0x000d242c >> 0x18,3);
    } while (iVar1 == 0);
    if (dword_c721d != 0) {
      releasememblock(dword_c721d);
    }
    dword_c721d = 0;
  }
  freemem(__dest);
  iVar1 = load_award_stats();
  if ((sound_enabled == '\0') || (dword_c721d != 0)) {
    puVar4 = install_path;
    if (dword_c541f == 8) {
      pcVar5 = aMtawards;
      if (byte_ed8c8 != '\x01') {
        puVar4 = (undefined *)0x0;
      }
    }
    else {
      pcVar5 = aAdawards;
      if (byte_ed7e6 != '\x01') {
        puVar4 = (undefined *)0x0;
      }
    }
    make_path(auStack_28,puVar4,pcVar5,0);
    unaff_EDI = sub_8f13b(auStack_28);
    play_sample_by_ptr();
  }
  else {
    puVar4 = install_path;
    if (byte_ed9f0 != '\x01') {
      puVar4 = (undefined *)0x0;
    }
    make_path(auStack_28,puVar4,aAwasong,&aIff);
    dword_c721d = loadsound(auStack_28);
    if ((dword_c721d != 0) && (((byte)option_flags & 0x40) != 0)) {
      playsample(dword_c721d,dword_d2431,3);
    }
  }
  if (iVar1 == 0) {
    iVar1 = league_leaders_screen();
    if (iVar1 < 3) {
      puVar4 = install_path;
      if (byte_ed9aa != '\x01') {
        puVar4 = (undefined *)0x0;
      }
      make_path(auStack_28,puVar4,aAwardsi,0);
      uVar2 = loadshapes(auStack_28,0);
      event_queue_reset();
      setdefaultscreen();
      set_text_colors(1,0);
      uVar3 = locateshape(uVar2,&aScrn);
      drawshape_home(uVar3);
      uVar3 = locateshape(uVar2,&aSumm);
      drawshape_home(uVar3);
      team_abbrev_lookup();
      setdefaultscreen();
      iVar1 = locateshape(uVar2,&aPal);
      fade_palette(0,iVar1 + 0x10,0x10);
      sub_33e6a(9000);
      fade_palette(1,iVar1 + 0x10,0x10);
      freemem(uVar2);
    }
    setdefaultscreen();
    clearclip(0);
  }
  if (sound_enabled == '\0') {
    stop_crowd_loop();
    sub_8f1fe(unaff_EDI);
  }
  else {
    sound_fade(dword_d2431,3,0x78);
    do {
      iVar1 = sound_channel_status(ram0x000d242c >> 0x18,3);
    } while (iVar1 == 0);
    if (dword_c721d != 0) {
      releasememblock(dword_c721d);
    }
    dword_c721d = 0;
  }
  setfontstate(auStack_68);
  return;
}


// ================================================================================================
// fill_sprite_frames @ 0x13867 [__watcall]
// ================================================================================================

void __watcall fill_sprite_frames(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  char acStack_24 [12];
  
  __CHK(0x34);
  iVar2 = param_1 * 0x32;
  iVar3 = 0;
  do {
    sprintf(acStack_24,(char *)&a04d,iVar2);
    uVar1 = sub_b30bb((&sprite_banks)[param_1],acStack_24);
    *(undefined4 *)(&sprite_frames + iVar2 * 4) = uVar1;
    iVar2 = iVar2 + 1;
    if (0x46d < iVar2) {
      return;
    }
    iVar3 = iVar3 + 1;
  } while (iVar3 < 0x32);
  return;
}


// ================================================================================================
// load_effect_frames @ 0x138d2 [__watcall]
// ================================================================================================

void __watcall load_effect_frames(void)

{
  undefined4 uVar1;
  undefined *puVar2;
  int iVar3;
  undefined auStack_30 [16];
  char acStack_20 [16];
  
  __CHK(0x40);
  if (dword_cc0e0 == 0) {
    puVar2 = (undefined *)0x0;
    if (byte_ed85c == '\x01') {
      puVar2 = install_path;
    }
    make_path(auStack_30,puVar2,aF000149,&aPPV);
    dword_cc0e0 = loadfile(auStack_30,0x20);
    iVar3 = 0;
    do {
      sprintf(acStack_20,(char *)&a04d,iVar3);
      uVar1 = locateshape(dword_cc0e0,acStack_20);
      (&effect_frames)[iVar3] = uVar1;
      iVar3 = iVar3 + 1;
    } while (iVar3 < 0x69);
  }
  return;
}


// ================================================================================================
// load_sprite_banks @ 0x1395f [__watcall]
// ================================================================================================

void __watcall load_sprite_banks(void)

{
  undefined4 uVar1;
  undefined *puVar2;
  int iVar3;
  undefined1 *__format;
  undefined auStack_30 [16];
  char acStack_20 [16];
  
  __CHK(0x44);
  iVar3 = 0;
  do {
    if ((&sprite_banks)[iVar3] == 0) {
      if (iVar3 < 0x14) {
        if (iVar3 % 2 == 0) {
          __format = aD00D49_c048a;
        }
        else {
          __format = aD50D99_c0480;
        }
      }
      else if (iVar3 % 2 == 0) {
        __format = aD00D49;
      }
      else {
        __format = aD50D99;
      }
      sprintf(acStack_20,__format,iVar3 / 2,iVar3 / 2);
      puVar2 = install_path;
      if ((&file_on_disk)[iVar3] != '\x01') {
        puVar2 = (undefined *)0x0;
      }
      make_path(auStack_30,puVar2,acStack_20,&aPPV);
      uVar1 = loadfile(auStack_30,0x20);
      (&sprite_banks)[iVar3] = uVar1;
      fill_sprite_frames(iVar3);
    }
    iVar3 = iVar3 + 1;
  } while (iVar3 < 0x17);
  load_effect_frames();
  return;
}


// ================================================================================================
// load_rink_end_shapes @ 0x13a2f [__watcall]
// ================================================================================================

void __watcall load_rink_end_shapes(void)

{
  undefined *puVar1;
  undefined auStack_1c [16];
  
  __CHK(0x28);
  puVar1 = install_path;
  if (byte_ed976 != '\x01') {
    puVar1 = (undefined *)0x0;
  }
  make_path(auStack_1c,puVar1,aTrinknd,&aPPV);
  dword_d8c68 = loadfile(auStack_1c,0x20);
  dword_d8c70 = locateshape(dword_d8c68,&a0000);
  return;
}


// ================================================================================================
// load_player_graphics @ 0x13a91 [__watcall]
// ================================================================================================

void __watcall load_player_graphics(void)

{
  undefined4 uVar1;
  undefined *puVar2;
  int iVar3;
  undefined auStack_2c [16];
  char acStack_1c [12];
  
  __CHK(0x3c);
  setdefaultscreen();
  dword_c7290 = 0x52;
  puVar2 = install_path;
  if (byte_ed86c != '\x01') {
    puVar2 = (undefined *)0x0;
  }
  make_path(auStack_2c,puVar2,aHILIGHT,&aVFN);
  dword_ed700 = loadfile(auStack_2c,0x20);
  puVar2 = install_path;
  if (byte_ed8d7 != '\x01') {
    puVar2 = (undefined *)0x0;
  }
  make_path(auStack_2c,puVar2,aNumshp,&aPPV);
  dword_d8c80 = loadfile(auStack_2c,0x20);
  iVar3 = 0;
  do {
    sprintf(acStack_1c,(char *)&a04d,iVar3);
    uVar1 = locateshape(dword_d8c80,acStack_1c);
    (&digit_shapes)[iVar3] = uVar1;
    iVar3 = iVar3 + 1;
  } while (iVar3 < 10);
  sub_90b80(dword_d8c80,a000G000D000D000L000C000R,&position_letter_shapes);
  sub_1cbd8();
  load_rink_end_shapes();
  settextpos(4,0xff);
  load_sprite_banks();
  sub_8e3c0();
  word_cbec4 = 1;
  dword_c66d4 = 1;
  dword_c66d0 = 1;
  return;
}


// ================================================================================================
// sub_13bb4 @ 0x13bb4 [__watcall]
// ================================================================================================

void __watcall sub_13bb4(void)

{
  undefined4 uVar1;
  undefined *puVar2;
  int iVar3;
  undefined auStack_2c [16];
  char acStack_1c [12];
  
  __CHK(0x3c);
  dword_c7290 = 0x52;
  puVar2 = install_path;
  if (byte_ed86c != '\x01') {
    puVar2 = (undefined *)0x0;
  }
  make_path(auStack_2c,puVar2,aHILIGHT,&aVFN);
  dword_ed700 = loadfile(auStack_2c,0x20);
  puVar2 = install_path;
  if (byte_ed8d7 != '\x01') {
    puVar2 = (undefined *)0x0;
  }
  make_path(auStack_2c,puVar2,aNumshp,&aPPV);
  dword_d8c80 = loadfile(auStack_2c,0x20);
  iVar3 = 0;
  do {
    sprintf(acStack_1c,(char *)&a04d,iVar3);
    uVar1 = locateshape(dword_d8c80,acStack_1c);
    (&digit_shapes)[iVar3] = uVar1;
    iVar3 = iVar3 + 1;
  } while (iVar3 < 10);
  sub_90b80(dword_d8c80,a000G000D000D000L000C000R,&position_letter_shapes);
  sub_1cbd8();
  load_rink_end_shapes();
  settextpos(4,0xff);
  load_sprite_banks();
  sub_8e3c0();
  word_cbec4 = 1;
  dword_c66d4 = 1;
  dword_c66d0 = 1;
  return;
}


// ================================================================================================
// sub_13c79 @ 0x13c79 [__watcall]
// ================================================================================================

void __watcall sub_13c79(void)

{
  short sVar1;
  short sVar2;
  undefined2 uVar3;
  uint uVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  undefined4 uStackY_10;
  
  __CHK(0x10);
  if (dword_cc0ec == 0) {
    puVar6 = &uStackY_10;
    uStackY_10 = 0x13c98;
    sub_5e0b0();
    faceoff_spot._2_2_ = 0;
    faceoff_spot._0_2_ = 0;
    *p_puck_y = 0;
    *p_puck_x = 0;
    puVar5 = &entities;
    dword_e03ac = 0xc;
    do {
      *(undefined2 *)((int)puVar5 + 0x2e) = 0xff9c;
      sVar1 = *(short *)((int)puVar5 + 0x1a);
      dword_e03be = CONCAT22(sVar1,(undefined2)dword_e03be);
      *(undefined4 *)((int)puVar6 + -4) = 0x13cef;
      set_state_reset(puVar5,(sVar1 == 4) + '\x16');
      if (-1 < dword_e03be) {
        sVar1 = dword_df648._2_2_;
        if ((*(byte *)(puVar5 + 0x11) & 0x40) != 0) {
          sVar1 = dword_df748._2_2_;
        }
        sVar1 = (char)(&faceoff_lineup)[(dword_e03be >> 0x10) + (int)(short)((6 - sVar1) * 8)] * 2;
        dword_e03b2 = CONCAT22(sVar1,(short)dword_e03b2);
        dword_e03ba._2_2_ = *(short *)(&faceoff_spots + sVar1 * 2);
        dword_e03be._2_2_ = *(short *)(&unk_cbe8e + sVar1 * 2);
        if ((*(byte *)(puVar5 + 0x11) & 0x80) == 0) {
          dword_e03ba._2_2_ = -dword_e03ba._2_2_;
          dword_e03be._2_2_ = -*(short *)(&unk_cbe8e + sVar1 * 2);
        }
        *(short *)((int)puVar5 + 2) = dword_e03ba._2_2_;
        *(short *)((int)puVar5 + 6) = dword_e03be._2_2_;
        *(undefined2 *)((int)puVar5 + 0xe) = 0;
        *(undefined2 *)(puVar5 + 3) = *(undefined2 *)((int)puVar5 + 0xe);
        sVar1 = *p_puck_y - dword_e03be._2_2_;
        sVar2 = *p_puck_x - dword_e03ba._2_2_;
        *(undefined4 *)((int)puVar6 + -4) = 0x13dd7;
        uVar3 = direction8((int)sVar2,(int)sVar1);
        *(undefined2 *)((int)puVar5 + 0x36) = uVar3;
        if (*(short *)((int)puVar5 + 0x1a) == 0) {
          if (*(char *)((int)puVar5 + 0x65) == '\0') {
            uVar4 = 8U - ((int)puVar5[0xd] >> 0x10) & 7;
          }
          else {
            uVar4 = (int)puVar5[0xd] >> 0x10;
          }
          *(short *)((int)puVar5 + 0x12) = ((short)(uVar4 << 2) - (short)uVar4) + 0x196;
          dword_e03be = CONCAT22(1,(undefined2)dword_e03be);
        }
        else {
          if (*(char *)((int)puVar5 + 0x65) == '\0') {
            uVar4 = 8U - ((int)puVar5[0xd] >> 0x10) & 7;
          }
          else {
            uVar4 = (int)puVar5[0xd] >> 0x10;
          }
          *(short *)((int)puVar5 + 0x12) = (short)(uVar4 << 2) + (short)uVar4;
          dword_e03be = CONCAT22(0x289,(undefined2)dword_e03be);
        }
        *(byte *)((int)puVar5 + 0x45) = *(byte *)((int)puVar5 + 0x45) & 0xfb;
        *(byte *)(puVar5 + 0x11) = *(byte *)(puVar5 + 0x11) & 0xdf;
        *(undefined2 *)((int)puVar5 + 0x3a) = 0;
        *(short *)(puVar5 + 0xe) = dword_e03be._2_2_;
        *(undefined2 *)(puVar5 + 0xf) = 0xffff;
      }
      puVar5 = puVar5 + 0x20;
      dword_e03ac = dword_e03ac + -1;
    } while (dword_e03ac != 0);
  }
  return;
}


// ================================================================================================
// sub_13e8f @ 0x13e8f [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

longlong __watcall sub_13e8f(undefined4 param_1,uint unaff_EDX)

{
  int iVar1;
  int extraout_EDX;
  
  __CHK(0x20);
  build_lines();
  count_dressed_players(0);
  count_dressed_players(1);
  period_idx = 0xffff;
  crowd_noise._2_2_ = 0;
  sound_resume_all();
  skip_faceoff_wait = 0;
  sub_14056();
  show_scoreboard((int)user2_team._2_2_,(int)_away_team_id);
  crowd_noise._2_2_ = 0;
  dword_ccc88 = 0;
  iVar1 = match_sequence(0,0);
  if (iVar1 < 0) {
    return CONCAT44(unaff_EDX,0xffffffff);
  }
  if (skip_faceoff_wait != 0) {
    word_cbec4 = 1;
  }
  period_idx = 0;
  sub_14056();
  skip_faceoff_wait = extraout_EDX;
  if (extraout_EDX != 0) {
    getpalette(0,0x100,&palette_save);
    fade_palette_to(1,&palette_save,0x10);
  }
  if ((((byte)option_flags & 4) != 0) || (skip_faceoff_wait == 0)) {
    sub_13c79();
  }
  if ((dword_cc0ec == 0) && (skip_faceoff_wait == 0)) {
    word_cbec4 = 0;
  }
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// sub_13fa7 @ 0x13fa7 [__watcall]
// ================================================================================================

longlong __watcall sub_13fa7(undefined4 param_1,uint unaff_EDX)

{
  int iVar1;
  undefined4 extraout_EDX;
  int extraout_EDX_00;
  
  __CHK(0x14);
  build_lines();
  count_dressed_players(0);
  count_dressed_players(1);
  period_idx = 0xffff;
  crowd_noise._2_2_ = 0;
  sound_resume_all();
  skip_faceoff_wait = 0;
  sub_14056();
  crowd_noise._2_2_ = 0;
  dword_ccc88 = extraout_EDX;
  iVar1 = match_sequence(0);
  if (iVar1 < 0) {
    return CONCAT44(unaff_EDX,0xffffffff);
  }
  if (skip_faceoff_wait != 0) {
    word_cbec4 = 1;
  }
  period_idx = 0;
  sub_14056();
  skip_faceoff_wait = extraout_EDX_00;
  if ((dword_cc0ec == 0) && (extraout_EDX_00 == 0)) {
    word_cbec4 = 0;
  }
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// sub_14056 @ 0x14056 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall sub_14056(void)

{
  char cVar1;
  int extraout_EDX;
  int iVar2;
  
  __CHK(0x20);
  dword_e9ac8._0_1_ = 0xff;
  byte_e9ad3._0_1_ = 0xff;
  dword_cc0ac = 0;
  word_e024e._1_1_ = 0;
  word_e024e._0_1_ = 0;
  word_e024c._1_1_ = 0;
  word_e024c._0_1_ = 0;
  dword_cbebe._2_2_ = 0xffff;
  _penalized_slot = 0xffff;
  ref_phase = 0xffff;
  stoppage_timer = 0xffff;
  word_cc0b0 = 0xffff;
  goalie_pass_mode = 0;
  shot_power._2_2_ = 0;
  shot_power._0_2_ = 0;
  pending_dir = 0;
  last_passer = 0;
  _last_shooter = 0;
  penalty_box_mode = 0;
  ref_infraction = 0;
  whistle_timer = 0;
  dword_c90d0 = 0;
  word_cbc5c = 0;
  word_cbc5a = 0;
  word_cbc58 = 0;
  word_cbc56 = 0;
  word_cbc54 = 0;
  word_cbc52 = 0;
  word_e0382 = 0;
  word_e0380 = 0;
  word_e0306 = 0;
  word_e0304 = 0;
  word_cbc6c = 0;
  word_cbc6a = 0;
  word_cbc68 = 0;
  word_cbc66 = 0;
  word_cbc64 = 0;
  word_cbc62 = 0;
  word_cbc60 = 0;
  word_cbc5e = 0;
  dword_df010 = 0;
  dword_df00c = 0;
  dword_cbeca._0_2_ = 0;
  dword_cbec6 = 0;
  word_cbec2 = 0;
  _word_cbec8 = 0xffff;
  word_cbece = 0xffff;
  dword_cbeca._2_2_ = 0xffff;
  byte_e0344 = 0;
  byte_e0308 = 0;
  byte_e028c = 0;
  byte_e0250 = 0;
  byte_e02c8 = 0;
  penalty_shot_phase = 0;
  penalty_shot_active = 0;
  penalty_shot_setup = 0;
  defenders_ahead = 0;
  breakaway_flag = 0;
  penalty_shot_slot = 0xffffffff;
  excitement._2_2_ = 0;
  iVar2 = 0;
  do {
    *(undefined2 *)(&unk_dee94 + iVar2 * 0xc) = 0xffff;
    cVar1 = randomrange(0x28);
    *(char *)(extraout_EDX + 2) = cVar1 + '<';
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0x14);
  _memset_fill(&unk_e9b2c,0);
  dword_e9a9e._0_2_ = 0;
  _dword_e9aae = 0;
  dword_e9ab6._0_2_ = 0;
  excitement._0_2_ = 0;
  word_e9aa4 = 0;
  word_e9aa2 = 0;
  word_e9aaa = 0;
  _dword_e009c = 0;
  word_e9a9c = 0xffff;
  sub_5e086();
  _period_num = 1;
  if ((controller_type == '\x01') || (byte_c4d1d == '\x01')) {
    setmousepos(0xa0,100);
  }
  dword_c5840 = 0;
  control_steps_left = 0;
  period_over = 0;
  game_over = 0;
  dword_d8c78 = 0;
  dword_d8c6c = 0;
  _input_enabled = 0;
  dword_e9a9e._2_2_ = 0;
  flush_key_events();
  return;
}


// ================================================================================================
// sub_142e7 @ 0x142e7 [__watcall]
// ================================================================================================

undefined8 __watcall sub_142e7(undefined4 param_1,undefined4 unaff_EDX)

{
  int iVar1;
  undefined4 uStackY_c;
  
  __CHK(0x10);
  uStackY_c = 0xffffffff;
  iVar1 = file_open_read(param_1,&uStackY_c);
  file_close(&uStackY_c);
  return CONCAT44(unaff_EDX,(uint)(iVar1 == 0));
}


// ================================================================================================
// make_path @ 0x1431e [__watcall]
// ================================================================================================

void __watcall make_path(char *param_1,char *unaff_EDX,char *unaff_EBX,char *unaff_ECX)

{
  __CHK(8);
  if ((unaff_EDX == (char *)0x0) || (*unaff_EDX == '\0')) {
    *param_1 = '\0';
  }
  else {
    strcpy(param_1,unaff_EDX);
    strcat(param_1,&unk_c8115);
  }
  if (unaff_EBX != (char *)0x0) {
    strcat(param_1,unaff_EBX);
  }
  if (unaff_ECX != (char *)0x0) {
    strcat(param_1,unaff_ECX);
  }
  return;
}


// ================================================================================================
// sub_14368 @ 0x14368 [__watcall]
// ================================================================================================

int __watcall sub_14368(char *param_1,char *unaff_EDX,char *unaff_EBX)

{
  int iVar1;
  undefined auStackY_54 [30];
  char acStackY_36 [14];
  char acStackY_28 [32];
  
  __CHK(0x58);
  strcpy(acStackY_28,param_1);
  strcat(acStackY_28,&unk_c8115);
  strcat(acStackY_28,unaff_EDX);
  strcat(acStackY_28,&byte_c8164);
  strcat(acStackY_28,unaff_EBX);
  iVar1 = _dos_findfirst(acStackY_28,0,auStackY_54);
  if (iVar1 == 0) {
    strcpy(acStackY_28,param_1);
    strcat(acStackY_28,&unk_c8115);
    strcat(acStackY_28,acStackY_36);
    sub_903e8(acStackY_28);
    while (iVar1 = _dos_findnext(auStackY_54), iVar1 == 0) {
      strcpy(acStackY_28,param_1);
      strcat(acStackY_28,&unk_c8115);
      strcat(acStackY_28,acStackY_36);
      sub_903e8(acStackY_28);
    }
  }
  return iVar1;
}


// ================================================================================================
// sub_14442 @ 0x14442 [__watcall]
// ================================================================================================

void __watcall sub_14442(char *param_1)

{
  int iVar1;
  undefined auStackY_58 [30];
  char acStackY_3a [14];
  char acStackY_2c [32];
  
  __CHK(0x5c);
  strcpy(acStackY_2c,param_1);
  strcat(acStackY_2c,&unk_c8115);
  strcat(acStackY_2c,&unk_c8113);
  strcat(acStackY_2c,&byte_c8164);
  strcat(acStackY_2c,&unk_c8113);
  iVar1 = _dos_findfirst(acStackY_2c,0,auStackY_58);
  if (iVar1 == 0) {
    strcpy(acStackY_2c,param_1);
    strcat(acStackY_2c,&unk_c8115);
    strcat(acStackY_2c,acStackY_3a);
    sub_903e8(acStackY_2c);
    while (iVar1 = _dos_findnext(auStackY_58), iVar1 == 0) {
      strcpy(acStackY_2c,param_1);
      strcat(acStackY_2c,&unk_c8115);
      strcat(acStackY_2c,acStackY_3a);
      sub_903e8(acStackY_2c);
    }
  }
  rmdir(param_1);
  return;
}


// ================================================================================================
// file_open_read @ 0x14525 [__watcall]
// ================================================================================================

void __watcall
file_open_read(char *param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  __CHK(8);
  open(param_1,0x40,unaff_EDX,unaff_ECX,unaff_EBX);
  return;
}


// ================================================================================================
// sub_1453e @ 0x1453e [__watcall]
// ================================================================================================

void __watcall
sub_1453e(char *param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  __CHK(8);
  open(param_1,0x41,unaff_EDX,unaff_ECX,unaff_EBX);
  return;
}


// ================================================================================================
// file_open_rw @ 0x14552 [__watcall]
// ================================================================================================

void __watcall
file_open_rw(char *param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  __CHK(8);
  open(param_1,0x42,unaff_EDX,unaff_ECX,unaff_EBX);
  return;
}


// ================================================================================================
// sub_14566 @ 0x14566 [__watcall]
// ================================================================================================

void __watcall sub_14566(char *param_1)

{
  __CHK(8);
  creat(param_1,0);
  return;
}


// ================================================================================================
// file_close @ 0x1457c [__watcall]
// ================================================================================================

undefined8 __watcall file_close(int *param_1,undefined4 unaff_EDX)

{
  int iVar1;
  
  __CHK(0xc);
  iVar1 = 0;
  if (-1 < *param_1) {
    iVar1 = close(*param_1);
  }
  *param_1 = -1;
  return CONCAT44(unaff_EDX,iVar1);
}


// ================================================================================================
// file_read @ 0x145a2 [__watcall]
// ================================================================================================

int __watcall file_read(int param_1,undefined4 unaff_EDX,int unaff_EBX,int unaff_ECX)

{
  __off_t _Var1;
  int iVar2;
  undefined2 in_DS;
  int iStack_10;
  
  __CHK(0x18);
  iVar2 = 0;
  if (-1 < unaff_EBX) {
    _Var1 = lseek(param_1,unaff_EBX,0);
    if (_Var1 < 0) {
      iVar2 = -1;
    }
  }
  if (iVar2 == 0) {
    iVar2 = read_bytes(param_1,unaff_ECX,unaff_EDX,in_DS,&iStack_10);
  }
  if (unaff_ECX != iStack_10) {
    iVar2 = 1;
  }
  return iVar2;
}


// ================================================================================================
// file_write @ 0x145f9 [__watcall]
// ================================================================================================

int __watcall file_write(int param_1,undefined4 unaff_EDX,int unaff_EBX,int unaff_ECX)

{
  __off_t _Var1;
  int iVar2;
  undefined2 in_DS;
  int iStack_10;
  
  __CHK(0x18);
  iVar2 = 0;
  if (-1 < unaff_EBX) {
    _Var1 = lseek(param_1,unaff_EBX,0);
    if (_Var1 < 0) {
      iVar2 = -1;
    }
  }
  if (iVar2 == 0) {
    iVar2 = sub_90d14(param_1,unaff_ECX,unaff_EDX,in_DS,&iStack_10);
  }
  if (unaff_ECX != iStack_10) {
    iVar2 = 1;
  }
  return iVar2;
}


// ================================================================================================
// sub_1463d @ 0x1463d [__watcall]
// ================================================================================================

void __watcall sub_1463d(void)

{
  __CHK(8);
  file_read();
  return;
}


// ================================================================================================
// sub_14654 @ 0x14654 [__watcall]
// ================================================================================================

void __watcall sub_14654(void)

{
  __CHK(8);
  file_write();
  return;
}


// ================================================================================================
// sub_1466b @ 0x1466b [__watcall]
// ================================================================================================

undefined4 __watcall
sub_1466b(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX,
         undefined4 param_5)

{
  int iVar1;
  undefined4 extraout_EDX;
  undefined2 in_DS;
  undefined auStack_458 [1024];
  undefined auStack_58 [32];
  undefined auStack_38 [32];
  int local_18;
  undefined4 local_14;
  int local_10;
  undefined4 uStack_c;
  
  __CHK(0x460);
  local_14 = 0xffffffff;
  uStack_c = 0xffffffff;
  make_path(auStack_58,unaff_ECX,param_1,unaff_EDX);
  iVar1 = file_open_read(auStack_58,&local_14);
  if (iVar1 == 0) {
    make_path(auStack_38,param_5,param_1,unaff_EBX);
    iVar1 = sub_14566(auStack_38,&uStack_c);
  }
  do {
    if (iVar1 != 0) break;
    iVar1 = read_bytes(local_14,0x400,auStack_458,in_DS,&local_18);
    if (((iVar1 == 0) && (local_18 != 0)) &&
       (iVar1 = sub_90d14(uStack_c,local_18,auStack_458,in_DS,&local_10), local_10 != local_18)) {
      iVar1 = 1;
    }
  } while (local_18 != 0);
  file_close(&uStack_c);
  file_close(&local_14);
  return extraout_EDX;
}


// ================================================================================================
// sub_1478b @ 0x1478b [__watcall]
// ================================================================================================

void __watcall sub_1478b(void)

{
  __CHK(8);
  file_read();
  return;
}


// ================================================================================================
// db_read_record2 @ 0x147a0 [__watcall]
// ================================================================================================

void __watcall db_read_record2(undefined4 param_1,undefined4 unaff_EDX,int unaff_EBX)

{
  __CHK(0xc);
  file_read(param_1,unaff_EDX,unaff_EBX * 6 + 2,6);
  return;
}


// ================================================================================================
// db_read_record @ 0x147c9 [__watcall]
// ================================================================================================

void __watcall db_read_record(undefined4 param_1,undefined4 unaff_EDX,int unaff_EBX)

{
  __CHK(0x10);
  file_read(param_1,unaff_EDX,unaff_EBX * 0x2e8,0x2e8);
  return;
}


// ================================================================================================
// sub_147ff @ 0x147ff [__watcall]
// ================================================================================================

void __watcall sub_147ff(undefined4 param_1,undefined4 unaff_EDX,int unaff_EBX)

{
  __CHK(0x10);
  file_read(param_1,unaff_EDX,unaff_EBX * 0xb,0xb);
  return;
}


// ================================================================================================
// check_disk_space @ 0x14825 [__watcall]
// ================================================================================================

int __watcall check_disk_space(undefined4 param_1,int *unaff_EDX)

{
  int iVar1;
  int iVar2;
  undefined local_18 [2];
  ushort local_16;
  ushort uStack_14;
  ushort uStack_12;
  
  __CHK(0x20);
  iVar2 = 0;
  iVar1 = _dos_getdiskfree(param_1,local_18);
  if (iVar1 != 0) {
    fatalerror(aErrorGettingDiskSpaceFre_c064c);
  }
  iVar1 = (int)((uint)uStack_12 * (uint)uStack_14) >> 0x1f;
  iVar1 = (int)(((uint)uStack_12 * (uint)uStack_14 + iVar1 * -0x400) - (uint)(iVar1 << 9 < 0)) >> 10
  ;
  for (; *unaff_EDX != 0; unaff_EDX = unaff_EDX + 1) {
    iVar2 = iVar2 + (*unaff_EDX + iVar1 + -1) / iVar1;
  }
  if ((int)(uint)local_16 < iVar2) {
    iVar2 = iVar2 * iVar1;
  }
  else {
    iVar2 = 0;
  }
  return iVar2;
}


// ================================================================================================
// check_disk_space_for_game @ 0x148a5 [__watcall]
// ================================================================================================

undefined8 __watcall check_disk_space_for_game(undefined4 param_1,undefined4 unaff_EDX)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  undefined auStack_70 [26];
  int iStack_56;
  undefined auStack_44 [32];
  undefined local_24 [2];
  ushort local_22;
  ushort local_20;
  ushort uStack_1e;
  undefined4 local_1c;
  undefined4 uStack_18;
  
  __CHK(0x88);
  uStack_18 = 0x140;
  local_1c = 0xf0;
  iVar1 = _dos_getdiskfree(0,local_24);
  if (iVar1 != 0) {
    fatalerror(aErrorGettingDiskSpaceFre_c066b);
  }
  uVar4 = (uint)uStack_1e * (uint)local_20;
  iVar1 = (int)(uVar4 + 0x1fff) / (int)uVar4;
  make_path(auStack_44,&league_dir,aGsummaryDb,0);
  iVar2 = _dos_findfirst(auStack_44,0,auStack_70);
  if (iVar2 == 0) {
    uVar3 = 0;
    if (0x1fff < (int)uVar4) goto LAB_000149b6;
    iVar1 = iVar1 - ((iStack_56 + uVar4) - 1) / uVar4;
  }
  if ((int)(uint)local_22 < iVar1) {
    iVar2 = (int)(iVar1 * uVar4) >> 0x1f;
    sprintf(aPlayTheGameYouRequireXXK,aPlayTheGameYouRequire2dK,
            (int)((iVar1 * uVar4 + iVar2 * -0x400) - (uint)(iVar2 << 9 < 0)) >> 10);
    setmousepos(uStack_18,local_1c);
    message_dialog(0xffffffff,0xffffffff,&off_c56b5,3,0,0,&uStack_18,&local_1c,800);
    uVar3 = 1;
  }
  else {
    uVar3 = 0;
  }
LAB_000149b6:
  return CONCAT44(unaff_EDX,uVar3);
}


// ================================================================================================
// sub_149bf @ 0x149bf [__watcall]
// ================================================================================================

undefined4 __watcall sub_149bf(undefined4 param_1,int unaff_EDX,undefined4 unaff_EBX)

{
  int iVar1;
  undefined auStackY_5c [26];
  int iStackY_42;
  undefined auStackY_30 [32];
  
  __CHK(0x68);
  iVar1 = 0;
  do {
    make_path(auStackY_30,param_1,(&off_c80d7)[iVar1],unaff_EBX);
    _dos_findfirst(auStackY_30,0,auStackY_5c);
    *(uint *)(iVar1 * 4 + unaff_EDX) = iStackY_42 + 0x3ffU >> 10;
    iVar1 = iVar1 + 1;
  } while (iVar1 < 7);
  return 0;
}


// ================================================================================================
// draw_score_digits @ 0x14a20 [__watcall]
// ================================================================================================

void __watcall draw_score_digits(uint param_1,short unaff_DX)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  
  __CHK(0x1c);
  uVar1 = param_1;
  if (99 < unaff_DX) {
    uVar1 = (int)unaff_DX / 100 & 0xffff;
    unaff_DX = unaff_DX % 100;
  }
  select_game_surface(uVar1);
  if ((short)param_1 == 0) {
    if (unaff_DX < 10) {
      iVar2 = 10;
    }
    else {
      iVar2 = (int)unaff_DX / 10;
    }
    sub_b4cd8(*(undefined4 *)(&unk_dc2c4 + iVar2 * 4),0x2e,4);
    uVar4 = 0x38;
    uVar3 = *(undefined4 *)(&unk_dc2c4 + ((int)unaff_DX % 10) * 4);
  }
  else {
    if (unaff_DX < 10) {
      iVar2 = 10;
    }
    else {
      iVar2 = (int)unaff_DX / 10;
    }
    sub_b4cd8(*(undefined4 *)(&unk_dc2c4 + iVar2 * 4),0xff,4);
    uVar4 = 0x109;
    uVar3 = *(undefined4 *)(&unk_dc2c4 + ((int)unaff_DX % 10) * 4);
  }
  sub_b4cd8(uVar3,uVar4,4);
  sub_8c1e2();
  return;
}


// ================================================================================================
// draw_line_indicator @ 0x14afe [__watcall]
// ================================================================================================

void __watcall draw_line_indicator(short param_1)

{
  short extraout_DX;
  undefined4 uVar1;
  undefined4 uVar2;
  
  __CHK(0x24);
  select_game_surface();
  if (param_1 == 0) {
    if ((extraout_DX < 4 != dword_c584c < 4) || (extraout_DX < 6 != dword_c584c < 6)) {
      dword_c585c = 0;
    }
    dword_c584c = (int)extraout_DX;
    uVar2 = 0x2a;
    uVar1 = *(undefined4 *)(&unk_dc26c + dword_c584c * 4);
  }
  else {
    if ((extraout_DX < 4 != dword_c5850 < 4) || (extraout_DX < 6 != dword_c5850 < 6)) {
      dword_c5860 = 0;
    }
    dword_c5850 = (int)extraout_DX;
    uVar2 = 0xfb;
    uVar1 = *(undefined4 *)(&unk_dc26c + dword_c5850 * 4);
  }
  sub_b4cd8(uVar1,uVar2,0x14);
  sub_8c1e2();
  return;
}


// ================================================================================================
// sub_14bef @ 0x14bef [__watcall]
// ================================================================================================

void __watcall sub_14bef(short param_1,int unaff_EDX)

{
  short sVar1;
  int iVar2;
  undefined *puVar3;
  undefined4 *puVar4;
  
  __CHK(0x10);
  puVar3 = &stack0xfffffff4;
  iVar2 = 0;
  do {
    puVar4 = (undefined4 *)(puVar3 + -4);
    puVar3 = puVar3 + -4;
    *puVar4 = 0x14c0d;
    sVar1 = sub_5a2ee((int)param_1,(int)(short)iVar2);
    *(int *)(unaff_EDX + iVar2 * 4) = sVar1 + -0x60;
    iVar2 = iVar2 + 1;
  } while (iVar2 < 8);
  return;
}


// ================================================================================================
// add_penalty_display @ 0x14c22 [__watcall]
// ================================================================================================

void __watcall add_penalty_display(short param_1,short unaff_DX,short unaff_BX)

{
  short *psVar1;
  short sVar2;
  
  __CHK(0x10);
  dword_c585c = 0;
  dword_c5860 = 0;
  if (param_1 == 0) {
    psVar1 = &word_c571c;
  }
  else {
    psVar1 = &word_c575c;
  }
  sVar2 = 0;
  while( true ) {
    if (7 < sVar2) {
      return;
    }
    if (*psVar1 == -1) break;
    psVar1 = psVar1 + 4;
    sVar2 = sVar2 + 1;
  }
  *psVar1 = unaff_DX;
  psVar1[1] = unaff_BX;
  psVar1[3] = 0;
  psVar1[2] = psVar1[3];
  if (param_1 != 0) {
    dword_c5848 = 0;
    return;
  }
  dword_c5844 = 0;
  return;
}


// ================================================================================================
// sub_14ca0 @ 0x14ca0 [__watcall]
// ================================================================================================

void __watcall sub_14ca0(short param_1,short unaff_DX)

{
  short *psVar1;
  short sVar2;
  short *psVar3;
  
  __CHK(0xc);
  if (param_1 == 0) {
    psVar1 = &word_c571c;
  }
  else {
    psVar1 = &word_c575c;
  }
  sVar2 = 0;
  for (; (psVar3 = (short *)0x0, sVar2 < 8 && (psVar3 = psVar1, unaff_DX != *psVar1));
      psVar1 = psVar1 + 4) {
    sVar2 = sVar2 + 1;
  }
  if (psVar3 != (short *)0x0) {
    psVar3[3] = 0;
    psVar3[2] = psVar3[3];
    psVar3[1] = psVar3[3];
  }
  return;
}


// ================================================================================================
// draw_clock @ 0x14cf1 [__watcall]
// ================================================================================================

void __watcall draw_clock(void)

{
  int iVar1;
  
  __CHK(0x20);
  select_game_surface();
  if (-1 < dword_c5704) {
    dword_c583c = dword_dc28c;
    dword_dc28c = 0;
    iVar1 = sub_15374();
    if ((iVar1 != 0) && ((game_flags & 0x10) == 0)) {
      sub_15655(&word_c571c,dword_c583c);
      sub_15655(&word_c575c,dword_c583c);
    }
    sub_14bef(0,&unk_c56e4);
    sub_14bef(1,&unk_c56c4);
    sub_1540a();
    sub_15707(*(int *)(&unk_c56e4 + dword_c584c * 4) / 500,0x2b);
    sub_15707(*(int *)(&unk_c56c4 + dword_c5850 * 4) / 500,0xfc);
    if (((word_cbc6a == 0) && (dword_c5844 == 0)) && ((game_flags & 0x10) == 0)) {
      if (word_c571c < 0) {
        dword_c5844 = 1;
        sub_157bd(&dword_c585c,&unk_dc2f4,dword_c584c,&unk_c56e4,0x4a);
        dword_c5854 = 0;
      }
      else {
        if (dword_c5854 == 0) {
          sub_b4cf2(dword_dc2bc);
          dword_c5854 = 1;
        }
        sub_15995(&word_c571c,0x48);
        dword_c585c = 0;
      }
    }
    else {
      sub_157bd(&dword_c585c,&unk_dc2f4,dword_c584c,&unk_c56e4,0x4a);
      dword_c5854 = 0;
    }
    if (((word_cbc6c == 0) && (dword_c5848 == 0)) && ((game_flags & 0x10) == 0)) {
      if (word_c575c < 0) {
        dword_c5848 = 1;
        sub_157bd(&dword_c5860,&unk_dc300,dword_c5850,&unk_c56c4,0xc1);
        dword_c5858 = 0;
      }
      else {
        if (dword_c5858 == 0) {
          sub_b4cf2(dword_dc2c0);
          dword_c5858 = 1;
        }
        sub_15995(&word_c575c,0xbf);
        dword_c5860 = 0;
      }
    }
    else {
      sub_157bd(&dword_c5860,&unk_dc300,dword_c5850,&unk_c56c4,0xc1);
      dword_c5858 = 0;
    }
  }
  return;
}


// ================================================================================================
// sub_14f31 @ 0x14f31 [__watcall]
// ================================================================================================

void __watcall sub_14f31(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  __CHK(0x28);
  if (dword_c5704 == 0) {
    sub_b4cd8(dword_dc334,0xaa,3);
    uVar1 = dword_dc334;
    if (9 < dword_c5708) {
      uVar1 = (&unk_dc30c)[dword_c5708 / 10];
    }
    sub_b4cd8(uVar1,0x8c,3);
    sub_b4cd8((&unk_dc30c)[dword_c5708 % 10],0x95,3);
    uVar2 = 0xa1;
    uVar1 = (&unk_dc30c)[dword_c570c / 10];
  }
  else {
    uVar1 = dword_dc334;
    if (9 < dword_c5704) {
      uVar1 = (&unk_dc30c)[dword_c5704 / 10];
    }
    sub_b4cd8(uVar1,0x8c,3);
    sub_b4cd8((&unk_dc30c)[dword_c5704 % 10],0x95,3);
    sub_b4cd8((&unk_dc30c)[dword_c5708 / 10],0xa1,3);
    uVar2 = 0xaa;
    uVar1 = (&unk_dc30c)[dword_c5708 % 10];
  }
  sub_b4cd8(uVar1,uVar2,3);
  dword_c5710 = dword_c5704;
  dword_c5714 = dword_c5708;
  dword_c5718 = dword_c570c;
  return;
}


// ================================================================================================
// show_scoreboard @ 0x150c6 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall show_scoreboard(int param_1,int unaff_EDX,int unaff_EBX,int unaff_ECX)

{
  ulonglong uVar1;
  short sVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  uint uVar5;
  undefined *puVar6;
  undefined auStack_20 [16];
  undefined4 uStack_10;
  
  __CHK(0x34);
  if (unaff_ECX != 0) {
    sVar2 = sub_5b9d1();
    dword_c5704 = (int)sVar2 / 0x3c;
    dword_c5708 = (int)sVar2 % 0x3c;
    dword_c570c = 0;
  }
  dword_c583c = 0;
  dword_c5848 = 0;
  dword_c5844 = 0;
  dword_c584c = ram0x000df63c >> 0x10;
  dword_c5850 = dword_df73c >> 0x10;
  dword_c5858 = 0;
  dword_c5854 = 0;
  dword_c5860 = 0;
  dword_c585c = 0;
  select_game_surface();
  puVar6 = install_path;
  if (byte_ed939 != '\x01') {
    puVar6 = (undefined *)0x0;
  }
  make_path(auStack_20,puVar6,aScrbrd2,&aPPV);
  uVar3 = loadfile(auStack_20,0);
  uStack_10 = uVar3;
  uVar4 = locateshape(uVar3,&aSrb3);
  sub_b4cf2(uVar4);
  draw_score_digits(0,dword_df622 >> 0x10);
  draw_score_digits(1,dword_df722 >> 0x10);
  select_game_surface();
  sub_14f31();
  if (unaff_EBX == 0) {
    uVar4 = 0x98;
    puVar6 = off_c57c8;
  }
  else {
    uVar1 = (longlong)unaff_EBX % 100;
    uVar5 = (int)uVar1 >> 0x1f;
    uVar4 = locateshape(uVar3,(&off_c579c)
                              [(int)((longlong)((ulonglong)uVar5 << 0x20 | uVar1 & 0xffffffff) / 10)
                              ],0x98,0x16);
    sub_b4cd8(uVar4);
    uVar4 = 0xa0;
    puVar6 = (&off_c579c)[(int)((longlong)((ulonglong)uVar5 << 0x20 | uVar1 & 0xffffffff) % 10)];
  }
  uVar3 = locateshape(uVar3,puVar6,uVar4,0x16);
  sub_b4cd8(uVar3);
  freemem(uStack_10);
  puVar6 = install_path;
  if (byte_ed823 != '\x01') {
    puVar6 = (undefined *)0x0;
  }
  make_path(auStack_20,puVar6,aCrests4,&aPPV);
  uVar3 = loadfile(auStack_20,0);
  byte_dca1b = 0x67;
  byte_dc91b = 0x67;
  byte_dc9d7 = 0xff;
  byte_dcad7 = 0xff;
  setremaptable(&unk_dc9d8);
  uVar4 = locateshape(uVar3,(&off_c57cc)[param_1],4,4);
  sub_b4e50(uVar4);
  setremaptable(&unk_dc8d8);
  uVar4 = locateshape(uVar3,(&off_c57cc)[unaff_EDX],0x11c,4);
  sub_b4e50(uVar4);
  byte_dca1b = 0x43;
  byte_dc91b = 0x43;
  freemem(uVar3);
  sub_b4cd8(*(undefined4 *)(&unk_dc26c + dword_c584c * 4),0x2a,0x14);
  sub_b4cd8(*(undefined4 *)(&unk_dc26c + dword_c5850 * 4),0xfb,0x14);
  return;
}


// ================================================================================================
// sub_15374 @ 0x15374 [__watcall]
// ================================================================================================

longlong __watcall sub_15374(int param_1,uint unaff_EDX)

{
  __CHK(0x14);
  dword_c5710 = dword_c5704;
  dword_c5714 = dword_c5708;
  dword_c5718 = dword_c570c;
  dword_c570c = dword_c570c - param_1;
  if (dword_c570c < 0) {
    dword_c570c = dword_c570c + 100;
    dword_c5708 = dword_c5708 + -1;
    if (dword_c5708 < 0) {
      dword_c5708 = 0x3b;
      dword_c5704 = dword_c5704 + -1;
      if (dword_c5704 < 0) {
        dword_c570c = 0;
        dword_c5708 = 0;
        dword_c5704 = 0;
        return (ulonglong)unaff_EDX << 0x20;
      }
    }
  }
  return CONCAT44(unaff_EDX,1);
}


// ================================================================================================
// sub_1540a @ 0x1540a [__watcall]
// ================================================================================================

undefined8 __watcall sub_1540a(undefined4 param_1,undefined4 unaff_EDX)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  __CHK(0x28);
  if (dword_c5704 == 0) {
    if (dword_c5710 != 0) {
      sub_b4cd8(dword_dc334,0xaa,3);
    }
    if (dword_c5714 != dword_c5708) {
      if (dword_c5714 / 10 != dword_c5708 / 10) {
        uVar2 = dword_dc334;
        if (9 < dword_c5708) {
          uVar2 = (&unk_dc30c)[dword_c5708 / 10];
        }
        sub_b4cd8(uVar2,0x8c,3);
      }
      if (dword_c5714 % 10 != dword_c5708 % 10) {
        sub_b4cd8((&unk_dc30c)[dword_c5708 % 10],0x95,3);
      }
    }
    iVar1 = dword_c570c / 10;
    if (dword_c5718 / 10 == iVar1) goto LAB_00014f2a;
    uVar3 = 0xa1;
    uVar2 = (&unk_dc30c)[iVar1];
  }
  else {
    if (dword_c5710 != dword_c5704) {
      if (dword_c5710 / 10 != dword_c5704 / 10) {
        uVar2 = dword_dc334;
        if (9 < dword_c5704) {
          uVar2 = (&unk_dc30c)[dword_c5704 / 10];
        }
        sub_b4cd8(uVar2,0x8c,3);
      }
      if (dword_c5710 % 10 != dword_c5704 % 10) {
        sub_b4cd8((&unk_dc30c)[dword_c5704 % 10],0x95,3);
      }
    }
    iVar1 = dword_c5714;
    if (dword_c5714 == dword_c5708) goto LAB_00014f2a;
    if (dword_c5714 / 10 != dword_c5708 / 10) {
      sub_b4cd8((&unk_dc30c)[dword_c5708 / 10],0xa1,3);
    }
    iVar1 = dword_c5708 / 10;
    if (dword_c5714 % 10 == dword_c5708 % 10) goto LAB_00014f2a;
    uVar3 = 0xaa;
    uVar2 = (&unk_dc30c)[dword_c5708 % 10];
  }
  iVar1 = sub_b4cd8(uVar2,uVar3,3);
LAB_00014f2a:
  return CONCAT44(unaff_EDX,iVar1);
}


// ================================================================================================
// sub_15655 @ 0x15655 [__watcall]
// ================================================================================================

void __watcall sub_15655(int param_1,short unaff_DX)

{
  undefined2 *puVar1;
  short *psVar2;
  int iVar3;
  short sVar4;
  int iVar5;
  int iVar6;
  undefined4 *puVar7;
  
  __CHK(0x18);
  iVar6 = 0;
  do {
    puVar1 = (undefined2 *)(iVar6 * 8 + param_1);
    sVar4 = puVar1[3] - unaff_DX;
    puVar1[3] = sVar4;
    if (sVar4 < 0) {
      puVar1[3] = sVar4 + 100;
      sVar4 = puVar1[2];
      puVar1[2] = sVar4 + -1;
      if ((short)(sVar4 + -1) < 0) {
        puVar1[2] = 0x3b;
        sVar4 = puVar1[1];
        puVar1[1] = sVar4 + -1;
        if ((short)(sVar4 + -1) < 0) {
          puVar1[1] = 0;
          puVar1[2] = 0;
          puVar1[3] = 0;
          *puVar1 = 0xffff;
        }
      }
    }
    iVar6 = iVar6 + 1;
  } while (iVar6 < 2);
  iVar6 = 0;
  do {
    iVar5 = iVar6;
    iVar3 = iVar6;
    if (*(short *)(param_1 + iVar6 * 8) < 0) {
      while (iVar3 = iVar3 + 1, iVar3 < 8) {
        psVar2 = (short *)(iVar3 * 8 + param_1);
        if (-1 < *psVar2) {
          puVar7 = (undefined4 *)(iVar5 * 8 + param_1);
          *puVar7 = *(undefined4 *)psVar2;
          puVar7[1] = *(undefined4 *)(psVar2 + 2);
          *psVar2 = -1;
          iVar5 = iVar5 + 1;
        }
      }
    }
    iVar6 = iVar6 + 1;
  } while (iVar6 < 7);
  return;
}


// ================================================================================================
// sub_15707 @ 0x15707 [__watcall]
// ================================================================================================

void __watcall sub_15707(int param_1,int unaff_EDX)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uStack_18;
  
  __CHK(0x38);
  if ((&word_cbc52)[0xa0 < unaff_EDX] == 0) {
    uStack_18 = 0x67;
    uVar2 = 0;
  }
  else {
    uStack_18 = 0;
    uVar2 = 7;
  }
  fillrect((unaff_EDX + 9) - param_1,0x1a,param_1,3,uStack_18);
  iVar3 = unaff_EDX + 0x10;
  fillrect(iVar3,0x1a,param_1,3,uStack_18,iVar3);
  iVar1 = 8 - param_1;
  fillrect(unaff_EDX + 1,0x1a,iVar1,3,uVar2,iVar3,iVar1);
  fillrect(param_1 + iVar3,0x1a,iVar1,3,uVar2);
  return;
}


// ================================================================================================
// sub_157bd @ 0x157bd [__watcall]
// ================================================================================================

void __watcall
sub_157bd(int *param_1,undefined4 *unaff_EDX,uint unaff_EBX,int unaff_ECX,int param_5)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int unaff_EDI;
  uint local_2c;
  int local_1c;
  undefined4 local_14;
  undefined4 uStack_10;
  
  __CHK(0x4c);
  bVar1 = 0xa0 < param_5;
  uVar5 = unaff_EBX;
  if ((&word_cbc6a)[bVar1] != 0) {
    uVar5 = *(int *)(&word_cbc60 + bVar1) >> 0x10;
  }
  if (uVar5 < 4) {
    if (*param_1 == 0) {
      sub_b4cf2(*unaff_EDX);
      *param_1 = 1;
    }
    unaff_EDI = 8;
    local_2c = 0;
    local_1c = 4;
  }
  else if (uVar5 < 6) {
    if (*param_1 == 0) {
      sub_b4cf2(unaff_EDX[1]);
      *param_1 = 1;
    }
    unaff_EDI = 0xe;
    local_2c = 4;
    local_1c = 6;
  }
  else if (uVar5 < 8) {
    if (*param_1 == 0) {
      sub_b4cf2(unaff_EDX[2]);
      *param_1 = 1;
    }
    unaff_EDI = 0xe;
    local_2c = 6;
    local_1c = 8;
  }
  for (; (int)local_2c < local_1c; local_2c = local_2c + 1) {
    if ((local_2c == uVar5) && ((&word_cbc56)[bVar1] != 0)) {
      uStack_10 = 0x61;
      local_14 = 7;
    }
    else {
      if (local_2c == unaff_EBX) {
        uStack_10 = 0x21;
      }
      else {
        uStack_10 = 0x67;
      }
      local_14 = 0;
    }
    iVar2 = *(int *)(local_2c * 4 + unaff_ECX) / 200;
    fillrect((param_5 + 0x15) - iVar2,unaff_EDI,iVar2,3,uStack_10);
    iVar3 = param_5 + 0x20;
    fillrect(iVar3,unaff_EDI,iVar2,3,uStack_10,iVar3);
    iVar4 = 0x14 - iVar2;
    fillrect(param_5 + 1,unaff_EDI,iVar4,3,local_14,iVar3,iVar4);
    fillrect(iVar2 + iVar3,unaff_EDI,iVar4,3,local_14);
    unaff_EDI = unaff_EDI + 6;
  }
  return;
}


// ================================================================================================
// sub_15995 @ 0x15995 [__watcall]
// ================================================================================================

void __watcall sub_15995(int param_1,int unaff_EDX)

{
  short sVar1;
  int *piVar2;
  int iVar3;
  undefined4 uVar4;
  int iStack_18;
  
  __CHK(0x2c);
  iVar3 = 9;
  for (iStack_18 = 0; iStack_18 < 4; iStack_18 = iStack_18 + 1) {
    sVar1 = *(short *)(iStack_18 * 8 + param_1);
    if (sVar1 < 0) {
      sub_b4cd8(dword_dc2b8,unaff_EDX + 10,iVar3);
      sub_b4cd8(dword_dc2b8,unaff_EDX + 0x10,iVar3);
      sub_b4cd8(dword_dc2b8,unaff_EDX + 0x1b,iVar3);
      sub_b4cd8(dword_dc2b8,unaff_EDX + 0x21,iVar3);
      sub_b4cd8(dword_dc2b8,unaff_EDX + 0x2a,iVar3);
      uVar4 = dword_dc2b8;
    }
    else {
      uVar4 = dword_dc2b8;
      if (9 < sVar1) {
        uVar4 = *(undefined4 *)(&unk_dc290 + ((int)sVar1 / 10) * 4);
      }
      sub_b4cd8(uVar4,unaff_EDX + 10,iVar3);
      piVar2 = (int *)(iStack_18 * 8 + param_1);
      sub_b4cd8(*(undefined4 *)(&unk_dc290 + ((int)*(short *)piVar2 % 10) * 4),unaff_EDX + 0x10,
                iVar3);
      uVar4 = dword_dc2b8;
      if (9 < *(short *)((int)piVar2 + 2)) {
        uVar4 = *(undefined4 *)(&unk_dc290 + ((*piVar2 >> 0x10) / 10) * 4);
      }
      sub_b4cd8(uVar4,unaff_EDX + 0x1b,iVar3);
      piVar2 = (int *)(iStack_18 * 8 + param_1);
      sub_b4cd8(*(undefined4 *)(&unk_dc290 + ((*piVar2 >> 0x10) % 10) * 4),unaff_EDX + 0x21,iVar3);
      sub_b4cd8(*(undefined4 *)(&unk_dc290 + ((*(int *)((int)piVar2 + 2) >> 0x10) / 10) * 4),
                unaff_EDX + 0x2a,iVar3);
      uVar4 = *(undefined4 *)(&unk_dc290 + ((*(int *)((int)piVar2 + 2) >> 0x10) % 10) * 4);
    }
    sub_b4cd8(uVar4,unaff_EDX + 0x30,iVar3);
    iVar3 = iVar3 + 5;
  }
  return;
}


// ================================================================================================
// sub_15b76 @ 0x15b76 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall sub_15b76(void)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  byte bVar4;
  int iStack_18;
  
  bVar4 = 0;
  __CHK(0x28);
  if ((((*(uint *)(&unk_c5519 + user2_team._2_2_ * 4) | *(uint *)(&unk_c5519 + _away_team_id * 4)) &
       3) == 0) ||
     (((*(uint *)(&unk_c5519 + user2_team._2_2_ * 4) | *(uint *)(&unk_c5519 + _away_team_id * 4)) &
      0xc) == 0)) {
    dword_dc338 = 0;
  }
  else {
    dword_dc338 = allocmem(aStanley,0x2a,0x20);
    sub_891b2(&iStack_18);
    iVar1 = 0;
    do {
      puVar2 = (undefined4 *)(iStack_18 + 2 + (iVar1 + 0x4a6) * 6);
      puVar3 = (undefined4 *)(dword_dc338 + iVar1 * 6);
      *puVar3 = *puVar2;
      *(undefined2 *)(puVar3 + (uint)bVar4 * -2 + 1) =
           *(undefined2 *)(puVar2 + (uint)bVar4 * -2 + 1);
      iVar1 = iVar1 + 1;
    } while (iVar1 < 7);
    if (iStack_18 != 0) {
      freemem(iStack_18);
    }
  }
  return;
}


// ================================================================================================
// game_over_check @ 0x15c30 [__watcall]
// ================================================================================================

undefined4 __watcall game_over_check(undefined param_1,undefined unaff_DL)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  
  __CHK(0x14);
  if (dword_dc338 != 0) {
    iVar4 = 0;
    while( true ) {
      iVar1 = dword_dc338 + iVar4 * 6;
      if (*(char *)(iVar1 + 4) == -1) break;
      iVar4 = iVar4 + 1;
    }
    *(undefined *)(iVar1 + 4) = param_1;
    *(undefined *)(iVar4 * 6 + dword_dc338 + 5) = unaff_DL;
    if (dword_c53fb == 1) {
      uVar3 = (uint)(option_flags << 0x11) >> 0x1d;
    }
    else {
      uVar3 = sub_42221(dword_dc338);
    }
    iVar2 = sub_15ce1(dword_dc338,uVar3);
    iVar1 = dword_dc338;
    iVar4 = iVar4 * 6;
    *(undefined *)(iVar4 + 5 + dword_dc338) = 0xff;
    *(undefined *)(iVar4 + 4 + dword_dc338) = *(undefined *)(iVar4 + 5 + iVar1);
    if (-1 < iVar2) {
      return 1;
    }
  }
  return 0;
}


// ================================================================================================
// sub_15ce1 @ 0x15ce1 [__watcall]
// ================================================================================================

uint __watcall sub_15ce1(int param_1,uint unaff_EDX)

{
  byte *pbVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  
  __CHK(0x24);
  uVar6 = (unaff_EDX >> 1) + 1;
  pbVar1 = (byte *)(param_1 + 2);
  uVar2 = (uint)*(byte *)(param_1 + 3);
  uVar3 = 0;
  uVar5 = 0;
  do {
    if ((uVar6 <= uVar5) || (uVar6 <= uVar3)) {
      if ((int)uVar3 < (int)uVar5) {
        uVar2 = (uint)*pbVar1;
      }
      return uVar2;
    }
    if (*(char *)(param_1 + 4) == -1) {
      return 0xffffffff;
    }
    uVar4 = uVar5 + 1;
    if ((uint)*(byte *)(param_1 + 2) == (uint)*pbVar1) {
      if (*(byte *)(param_1 + 4) <= *(byte *)(param_1 + 5)) {
LAB_00015d3b:
        uVar3 = uVar3 + 1;
        uVar4 = uVar5;
      }
    }
    else if (*(byte *)(param_1 + 5) < *(byte *)(param_1 + 4)) goto LAB_00015d3b;
    param_1 = param_1 + 6;
    uVar5 = uVar4;
  } while( true );
}


// ================================================================================================
// demo_game @ 0x15d6b [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 __watcall demo_game(undefined4 param_1,undefined4 unaff_EDX)

{
  short sVar1;
  int iVar2;
  int extraout_EDX;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 auStackY_90 [30];
  
  __CHK(0x94);
  loading_screen();
  ui_shutdown();
  word_cbc4a = 0x3c;
  sub_3371c();
  dword_c5130 = 1;
  iVar2 = rand();
  _dword_c9100 = rand();
  _dword_c9100 = iVar2 * 0x10000 + _dword_c9100;
  dword_c5886 = (dword_c5886 + 1) % 3;
  puVar3 = (undefined4 *)&settings_exhibition;
  puVar4 = auStackY_90;
  for (iVar2 = 0x1d; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar4 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
  }
  *(undefined *)puVar4 = *(undefined *)puVar3;
  if (dword_c5886 == 2) {
    dword_c52e9 = 0x1b;
    dword_c52ed = 0x1a;
  }
  else if (dword_c5886 == 1) {
    sVar1 = randomrange(0x11);
    dword_c52e9 = *(int *)((int)&dword_c5860 + sVar1 * 2 + 1) >> 0x18;
    dword_c52ed = *(int *)((int)&dword_c5860 + sVar1 * 2 + 2) >> 0x18;
  }
  else {
    iVar2 = rand();
    dword_c52e9 = iVar2 % 0x1a;
    sVar1 = randomrange(0x19,dword_c52e9 + 1);
    dword_c52ed = (extraout_EDX + sVar1) % 0x1a;
  }
  dword_c52fd = 0x10;
  dword_c53fb = 0;
  dword_c5301 = 0x10;
  dword_c5305 = 0;
  dword_c5309 = 1;
  dword_c52f5 = 0xffffffff;
  dword_c52f9 = 0xfffffffe;
  apply_settings(&settings_exhibition);
  option_flags._0_1_ = 0xff;
  if (sound_enabled == '\0') {
    option_flags._1_1_ = option_flags._1_1_ & 0xfe;
  }
  else {
    option_flags._1_1_ = option_flags._1_1_ | 1;
  }
  option_flags._1_1_ = option_flags._1_1_ & 3 | 2;
  preload_speech_wrapper((&team_abbrev)[user2_team._2_2_],(&team_abbrev)[_away_team_id]);
  sub_10712();
  sub_1befd(0,0);
  if (user2_team._2_2_ < 0x1a) {
    iVar2 = (int)user2_team._2_2_;
  }
  else {
    iVar2 = 0xc;
  }
  load_rink(iVar2);
  load_music_banks();
  sub_13bb4();
  wait_sprite_fade();
  dword_cc0ec = 1;
  sub_13fa7();
  dword_cc0ec = 0;
  skip_faceoff_wait = 0;
  dword_c53f7 = 0;
  set_video_mode(0x140,200);
  load_team_palettes((int)user2_team._2_2_,(int)_away_team_id,&unk_df314);
  show_scoreboard((int)user2_team._2_2_,(int)_away_team_id,1);
  flush_key_events();
  game_loop();
  set_video_mode(0x280,0x1e0);
  word_cbc4a = 300;
  dword_c5130 = 0;
  puVar3 = auStackY_90;
  puVar4 = (undefined4 *)&settings_exhibition;
  for (iVar2 = 0x1d; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar4 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
  }
  *(undefined *)puVar4 = *(undefined *)puVar3;
  apply_settings(&settings_exhibition);
  ui_init();
  return CONCAT44(unaff_EDX,(uint)(dword_c53f7 == 2));
}


// ================================================================================================
// sub_1600c @ 0x1600c [__watcall]
// ================================================================================================

undefined8 __watcall sub_1600c(undefined4 param_1,undefined4 unaff_EDX)

{
  int iVar1;
  uint uVar2;
  
  __CHK(0x14);
  iVar1 = getkey();
  if (iVar1 == 0) {
    if (((input_devices & 2) != 0) || ((input_devices & 4) != 0)) {
      uVar2 = joy_read();
      if (((uVar2 & 0x30) != 0) || (((int)uVar2 >> 8 & 0x30U) != 0)) {
        iVar1 = 1;
      }
    }
  }
  if ((iVar1 == 0) && ((input_devices & 1) != 0)) {
    (*(code *)mouse_update_callback)();
    if (((byte)dword_d3034 & 3) != 0) {
      iVar1 = 1;
    }
  }
  return CONCAT44(unaff_EDX,iVar1);
}


// ================================================================================================
// sub_16072 @ 0x16072 [__watcall]
// ================================================================================================

undefined8 __watcall sub_16072(char *param_1,undefined4 unaff_EDX)

{
  __CHK(0xc);
  return CONCAT44(unaff_EDX,
                  (int)param_1[3] +
                  ((*param_1 * 0x100 + (int)param_1[1]) * 0x100 + (int)param_1[2]) * 0x100);
}


// ================================================================================================
// ea_sports_intro @ 0x1609f [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 __watcall ea_sports_intro(void)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  int iVar4;
  uint uVar5;
  undefined4 uVar6;
  undefined *puVar7;
  char *pcVar8;
  char *pcVar9;
  int iVar11;
  undefined4 *puVar12;
  undefined4 *puVar13;
  undefined4 *puVar14;
  undefined4 *puVar15;
  byte bVar16;
  undefined8 uVar17;
  char acStack_368 [768];
  undefined auStack_68 [32];
  undefined4 local_48;
  undefined4 local_3c;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 *local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 uStack_1c;
  undefined4 *puVar10;
  
  bVar16 = 0;
  __CHK(0x378);
  pcVar9 = acStack_368;
  local_3c = 0;
  event_queue_reset();
  setdefaultscreen();
  clearclip(0);
  puVar7 = install_path;
  if (byte_ed834 != '\x01') {
    puVar7 = (undefined *)0x0;
  }
  make_path(auStack_68,puVar7,aEascrn,0);
  local_48 = loadshapes(auStack_68,0);
  iVar1 = locateshape(local_48,&aPal_c0861);
  memcpy(acStack_368,(void *)(iVar1 + 0x10),0x300);
  iVar1 = 0;
  do {
    if (acStack_368[iVar1] < ';') {
      acStack_368[iVar1] = acStack_368[iVar1] + '\x05';
    }
    else {
      acStack_368[iVar1] = '?';
    }
    iVar1 = iVar1 + 1;
  } while (iVar1 < 0x300);
  uVar2 = locateshape(local_48,&aScrn_c0866);
  drawshape2_home(uVar2);
  puVar3 = (undefined4 *)locateshape(local_48,&aMsk1);
  local_2c = (undefined4 *)allocmem(&aMASK,0x9c51,0x20);
  puVar14 = local_2c + (uint)bVar16 * -2 + 1;
  puVar12 = puVar3 + (uint)bVar16 * -2 + 1;
  *local_2c = *puVar3;
  puVar15 = puVar14 + (uint)bVar16 * -2 + 1;
  puVar13 = puVar12 + (uint)bVar16 * -2 + 1;
  *puVar14 = *puVar12;
  *puVar15 = *puVar13;
  puVar15[(uint)bVar16 * -2 + 1] = puVar13[(uint)bVar16 * -2 + 1];
  *(undefined *)(puVar15 + (uint)bVar16 * -2 + 1 + (uint)bVar16 * -2 + 1) =
       *(undefined *)(puVar13 + (uint)bVar16 * -2 + 1 + (uint)bVar16 * -2 + 1);
  *(undefined2 *)(local_2c + 1) = 200;
  *(undefined2 *)((int)local_2c + 6) = 200;
  memcpy(local_2c + 4,puVar3 + 4,40000);
  freemem(local_48);
  if ((sound_enabled == '\0') || (dword_c721d != 0)) {
    puVar7 = install_path;
    if (dword_c541f == 8) {
      pcVar8 = aMttitle;
      if (byte_ed8d0 != '\x01') {
        puVar7 = (undefined *)0x0;
      }
    }
    else {
      pcVar8 = aAdtitle;
      if (byte_ed8d0 != '\x01') {
        puVar7 = (undefined *)0x0;
      }
    }
    make_path(auStack_68,puVar7,pcVar8,&aKMS_c8140);
    dword_dc33c = sub_8f13b(auStack_68);
  }
  else {
    puVar7 = install_path;
    if (byte_ed9a6 != '\x01') {
      puVar7 = (undefined *)0x0;
    }
    make_path(auStack_68,puVar7,aTitle30,&aIff_c0875);
    dword_c721d = loadsound(auStack_68);
  }
  puVar7 = install_path;
  if (byte_ed7f0 != '\x01') {
    puVar7 = (undefined *)0x0;
  }
  make_path(auStack_68,puVar7,aTitle,&aCmv);
  local_28 = sub_1b0f3(300000,0x2000,0x20);
  sub_1b1c2(local_28,auStack_68);
  uVar2 = sub_1ac25();
  settimeout(0x96);
  while (iVar1 = sub_b39a7(), iVar1 == 0) {
    iff_parse();
  }
  local_34 = 10;
  acStack_368[0] = '\0';
  acStack_368[1] = 0;
  acStack_368[2] = 0;
  if (sound_enabled == '\0') {
    play_sample_by_ptr(dword_dc33c);
    fade_palette(0,acStack_368);
  }
  else {
    if (dword_c721d != 0) {
      playsample(dword_c721d,dword_d2431,3,0x4c);
    }
    fade_palette(0,acStack_368);
    settimeout(0x5a);
    while (iVar1 = sub_b39a7(), iVar1 == 0) {
      iff_parse();
    }
  }
  iVar1 = 0;
  local_24 = getticks();
  uStack_1c = 0;
  local_30 = 1;
  iVar11 = 0;
  ticks_elapsed();
  local_20 = 0;
  do {
    *(undefined4 *)(pcVar9 + -4) = *(undefined4 *)(pcVar9 + 0x340);
    *(undefined4 *)(pcVar9 + -8) = 0x163bc;
    iVar4 = sub_1b8ac();
    *(int *)(pcVar9 + 0x324) = iVar4;
    if (iVar4 == -1) {
      iVar1 = -1;
    }
    else if (iVar4 == 0) {
      *(undefined4 *)(pcVar9 + -4) = 0x16639;
      iff_parse(0,0);
    }
    else {
      *(undefined4 *)(pcVar9 + -4) = 0x163e1;
      uVar5 = sub_16072();
      *(uint *)(pcVar9 + 0x330) = uVar5;
      if (uVar5 < 0x4d564966) {
        if (uVar5 == 0x4d564965) {
          *(int *)(pcVar9 + 0x348) = *(int *)(pcVar9 + 0x348) + 1;
        }
        else {
LAB_000165c6:
          iVar1 = -1;
        }
      }
      else if (uVar5 < 0x4d564967) {
        *(int *)(pcVar9 + 0x34c) = *(int *)(pcVar9 + 0x34c) + *(int *)(pcVar9 + 0x334);
        iVar11 = iVar11 + 1;
        *(undefined4 *)(pcVar9 + -4) = 0x16427;
        uVar6 = sub_1b002(uVar2);
        *(undefined4 *)(pcVar9 + 0x328) = uVar6;
        *(undefined4 *)(pcVar9 + -4) = 0x16433;
        iVar4 = getticks();
        if (iVar4 - *(int *)(pcVar9 + 0x344) < *(int *)(pcVar9 + 0x34c)) {
          *(undefined4 *)(pcVar9 + -4) = *(undefined4 *)(pcVar9 + 0x32c);
          *(undefined4 *)(pcVar9 + -8) = 0x16450;
          setscreen();
          *(undefined4 *)(pcVar9 + -4) = *(undefined4 *)(pcVar9 + 0x33c);
          *(undefined4 *)(pcVar9 + -8) = 0x16460;
          drawshape2_home();
          *(undefined4 *)(pcVar9 + -4) = 0;
          *(undefined4 *)(pcVar9 + -8) = 0;
          *(undefined4 *)(pcVar9 + -0xc) = *(undefined4 *)(pcVar9 + 0x328);
          *(undefined4 *)(pcVar9 + -0x10) = 0x16474;
          sub_9087c();
          *(undefined4 *)(pcVar9 + -4) = 0x1647c;
          setdefaultscreen();
          *(undefined4 *)(pcVar9 + -4) = 0x56;
          *(undefined4 *)(pcVar9 + -8) = 0x21;
          *(undefined4 *)(pcVar9 + -0xc) = *(undefined4 *)(*(int *)(pcVar9 + 0x32c) + 0x2c);
          *(undefined4 *)(pcVar9 + -0x10) = 0x16490;
          drawshape2_remap();
        }
        if ((*(int *)(pcVar9 + 0x338) == 1) && (*(int *)(pcVar9 + 0x348) == 0)) {
          if ((sound_enabled != '\0') && (dword_c588a != 0)) {
            dword_c588a = 0;
            puVar10 = (undefined4 *)(pcVar9 + -4);
            pcVar9 = pcVar9 + -4;
            *puVar10 = 0x164ce;
            say_nhl_intro();
          }
          *(undefined4 *)(pcVar9 + 0x338) = 0;
          *(undefined4 *)(pcVar9 + -4) = 0x164dc;
          uVar6 = getticks();
          *(undefined4 *)(pcVar9 + 0x344) = uVar6;
        }
      }
      else {
        if (uVar5 != 0x4d564968) goto LAB_000165c6;
        *(undefined4 *)(pcVar9 + -4) = 0x164ef;
        cmv_load_palette(uVar2);
        *(undefined4 *)(pcVar9 + -4) = 0x164f6;
        sub_1b092(uVar2);
        if (*(int *)(pcVar9 + 0x32c) == 0) {
          *(undefined4 *)(pcVar9 + -4) = 0;
          *(undefined4 *)(pcVar9 + -8) = 0x16509;
          uVar6 = sub_1b0ad(uVar2);
          *(undefined4 *)(pcVar9 + -8) = uVar6;
          *(undefined4 *)(pcVar9 + -0xc) = 0x16511;
          uVar6 = sub_1b09f(uVar2);
          *(undefined4 *)(pcVar9 + -0xc) = uVar6;
          *(undefined4 *)(pcVar9 + -0x10) = 0x16517;
          uVar6 = windowdefp();
          *(undefined4 *)(pcVar9 + 0x32c) = uVar6;
        }
        *(undefined4 *)(pcVar9 + -4) = *(undefined4 *)(pcVar9 + 0x32c);
        *(undefined4 *)(pcVar9 + -8) = 0x1652e;
        setscreen();
        *(undefined4 *)(pcVar9 + -4) = *(undefined4 *)(pcVar9 + 0x33c);
        *(undefined4 *)(pcVar9 + -8) = 0x1653e;
        drawshape2_home();
        *(undefined4 *)(pcVar9 + -4) = 0x16546;
        setdefaultscreen();
        *(undefined4 *)(pcVar9 + -4) = 0x56;
        *(undefined4 *)(pcVar9 + -8) = 0x21;
        *(undefined4 *)(pcVar9 + -0xc) = *(undefined4 *)(*(int *)(pcVar9 + 0x32c) + 0x2c);
        *(undefined4 *)(pcVar9 + -0x10) = 0x1655a;
        drawshape2_remap();
        *(undefined4 *)(pcVar9 + -4) = 0x16564;
        iVar4 = sub_1b0d7(uVar2);
        *(undefined4 *)(pcVar9 + -4) = 0x16572;
        uVar6 = sub_1b0e5(uVar2);
        *(undefined4 *)(pcVar9 + -4) = 0x1657b;
        uVar17 = sub_1b0c9(uVar2,uVar6);
        *(undefined4 *)(pcVar9 + -4) = 0x1658d;
        memcpy(pcVar9 + (int)uVar17 * 3,(void *)((ulonglong)uVar17 >> 0x20),iVar4 * 3);
        *(char **)(pcVar9 + -4) = pcVar9;
        *(undefined4 *)(pcVar9 + -8) = 0x100;
        *(undefined4 *)(pcVar9 + -0xc) = 0;
        *(undefined4 *)(pcVar9 + -0x10) = 0x1659c;
        setpalette();
        *(undefined4 *)(pcVar9 + -4) = 0x165a6;
        iVar4 = sub_1b0bb(uVar2);
        *(int *)(pcVar9 + 0x334) = (int)(100 / (longlong)iVar4);
      }
      *(undefined4 *)(pcVar9 + -4) = *(undefined4 *)(pcVar9 + 0x324);
      *(undefined4 *)(pcVar9 + -8) = *(undefined4 *)(pcVar9 + 0x340);
      *(undefined4 *)(pcVar9 + -0xc) = 0x165e0;
      sub_1b92e();
      *(undefined4 *)(pcVar9 + -4) = 0x165e8;
      iff_parse();
      if (*(int *)(pcVar9 + 0x330) == 0x4d564966) {
        *(undefined4 *)(pcVar9 + -4) = 0x165fa;
        iVar4 = getticks();
        if (iVar4 - *(int *)(pcVar9 + 0x344) < *(int *)(pcVar9 + 0x34c)) {
          *(int *)(pcVar9 + -4) = *(int *)(pcVar9 + 0x34c) - (iVar4 - *(int *)(pcVar9 + 0x344));
          *(undefined4 *)(pcVar9 + -8) = 0x16616;
          settimeout();
          while( true ) {
            *(undefined4 *)(pcVar9 + -4) = 0x1661e;
            iVar4 = sub_b39a7();
            if ((iVar4 != 0) || (iVar1 != 0)) break;
            if (0x23 < iVar11) {
              *(undefined4 *)(pcVar9 + -4) = 0x16630;
              iVar1 = sub_1600c();
            }
          }
        }
      }
    }
    if ((iVar1 == 0) && (0x23 < iVar11)) {
      *(undefined4 *)(pcVar9 + -4) = 0x16647;
      iVar1 = sub_1600c();
    }
    if ((iVar1 != 0) || (1 < *(int *)(pcVar9 + 0x348))) {
      if (*(int *)(pcVar9 + 0x32c) != 0) {
        *(int *)(pcVar9 + -4) = *(int *)(pcVar9 + 0x32c);
        *(undefined4 *)(pcVar9 + -8) = 0x1666c;
        sub_9132c();
      }
      *(undefined4 *)(pcVar9 + -4) = 0x16676;
      sub_1acf1(uVar2);
      *(undefined4 *)(pcVar9 + -4) = *(undefined4 *)(pcVar9 + 0x340);
      *(undefined4 *)(pcVar9 + -8) = 0x16683;
      sub_1b18b();
      if ((sound_enabled != '\0') && (dword_c721d != 0)) {
        *(undefined4 *)(pcVar9 + -4) = 0x166ac;
        sound_fade(dword_d2431,3,100);
      }
      *(undefined4 *)(pcVar9 + -4) = 0x166bd;
      fade_palette(1,pcVar9,0x10);
      if ((sound_enabled == '\0') || (dword_c721d == 0)) {
        *(undefined4 *)(pcVar9 + -4) = 0x16703;
        stop_crowd_loop();
        *(undefined4 *)(pcVar9 + -4) = 0x1670d;
        sub_8f1fe(dword_dc33c);
      }
      else {
        do {
          *(undefined4 *)(pcVar9 + -4) = 0x166e1;
          iVar11 = sound_channel_status(ram0x000d242c >> 0x18,3);
        } while (iVar11 == 0);
        *(int *)(pcVar9 + -4) = dword_c721d;
        *(undefined4 *)(pcVar9 + -8) = 0x166f1;
        releasememblock();
        dword_c721d = 0;
      }
      *(undefined4 *)(pcVar9 + -4) = *(undefined4 *)(pcVar9 + 0x33c);
      *(undefined4 *)(pcVar9 + -8) = 0x1671a;
      freemem();
      return CONCAT44(*(undefined4 *)(pcVar9 + 0x35c),iVar1);
    }
  } while( true );
}


// ================================================================================================
// intro_sequence @ 0x1672a [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall intro_sequence(void)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 uVar5;
  undefined *puVar6;
  bool bVar7;
  char acStack_664 [768];
  char acStack_364 [768];
  char acStack_64 [32];
  undefined4 local_44 [5];
  undefined local_30 [3];
  byte bStack_2d;
  int local_2c;
  undefined4 local_28;
  int local_24;
  int local_20;
  int iStack_1c;
  
  __CHK(0x674);
  local_2c = 0;
  if (sound_enabled != '\0') {
    releasememblock(*(undefined4 *)(dword_ed7b0 + 0x3b60));
  }
  event_queue_reset();
  setdefaultscreen();
  clearclip(0);
  _memset_fill(&palette_black,0);
  setpalette(0,0x100,&palette_black);
  puVar6 = install_path;
  if (byte_ed8f3 != '\x01') {
    puVar6 = (undefined *)0x0;
  }
  make_path(acStack_64,puVar6,aPioneer1,0);
  uVar3 = loadshapes(acStack_64,0);
  iVar4 = locateshape(uVar3,&aPl2);
  memcpy(acStack_364,(void *)(iVar4 + 0x10),0x300);
  iVar4 = locateshape(uVar3,&aPl1);
  memcpy(acStack_664,(void *)(iVar4 + 0x10),0x300);
  uVar5 = locateshape(uVar3,&aBkgd);
  drawshape2_home(uVar5);
  freemem(uVar3);
  puVar6 = install_path;
  if (byte_ed8f4 != '\x01') {
    puVar6 = (undefined *)0x0;
  }
  make_path(acStack_64,puVar6,aPioneer2,0);
  uVar3 = loadshapes(acStack_64,0);
  if ((sound_enabled == '\0') || (dword_c721d != 0)) {
    local_28 = 200;
  }
  else {
    puVar6 = install_path;
    if (byte_ed8f8 != '\x01') {
      puVar6 = (undefined *)0x0;
    }
    make_path(acStack_64,puVar6,aPioneer4,&aIff_c0875);
    local_20 = loadsound(acStack_64);
    puVar6 = install_path;
    if (byte_ed8f7 != '\x01') {
      puVar6 = (undefined *)0x0;
    }
    make_path(acStack_64,puVar6,aPioneer3,&aIff_c0875);
    iStack_1c = loadsound(acStack_64);
    puVar6 = install_path;
    if (byte_ed8f6 != '\x01') {
      puVar6 = (undefined *)0x0;
    }
    make_path(acStack_64,puVar6,aPioneer2,&aIff_c0875);
    dword_c721d = loadsound(acStack_64);
    local_24 = dword_c721d;
    if (dword_c721d != 0) {
      playsample(dword_c721d,dword_d2431,1,0x7f);
    }
    settimeout(0x104);
    waittimeout();
    local_28 = 0x50;
  }
  if ((sound_enabled != '\0') && (dword_c721d != 0)) {
    playsample(dword_c721d,dword_d2431,0);
  }
  fade_palette(0,acStack_664,0x5a);
  bVar7 = true;
  while (bVar7) {
    bVar7 = false;
    iVar4 = 0;
    do {
      cVar1 = acStack_664[iVar4];
      if (cVar1 < acStack_364[iVar4]) {
        bVar7 = true;
        acStack_664[iVar4] = cVar1 + '\x01';
      }
      else if (acStack_364[iVar4] < cVar1) {
        bVar7 = true;
        acStack_664[iVar4] = cVar1 + -1;
      }
      iVar4 = iVar4 + 1;
    } while (iVar4 < 0x300);
    settimeout(2);
    waittimeout();
    if (bVar7) {
      setpalette(0,0x100,acStack_664);
    }
  }
  settimeout(local_28);
  waittimeout();
  iVar4 = 1;
  do {
    sprintf(acStack_64,aFlaD,iVar4);
    uVar5 = locateshape(uVar3,acStack_64);
    local_44[iVar4] = uVar5;
    iVar4 = iVar4 + 1;
  } while (iVar4 < 5);
  local_44[0] = locateshape(uVar3,&aPion);
  bVar7 = true;
  while (bVar7) {
    bVar7 = false;
    iVar4 = 0;
    do {
      if (acStack_664[iVar4] < acStack_364[iVar4]) {
        bVar7 = true;
        acStack_664[iVar4] = acStack_664[iVar4] + '\x01';
      }
      iVar4 = iVar4 + 1;
    } while (iVar4 < 0x270);
    settimeout(5);
    waittimeout();
    if (bVar7) {
      setpalette(0,0x100,acStack_664);
    }
  }
  memset(acStack_664,0x3f,0x300);
  iVar4 = locateshape(uVar3,&aPio);
  memcpy(acStack_364,(void *)(iVar4 + 0x10),0x300);
  settimeout(0x50);
  waittimeout();
  if ((sound_enabled != '\0') && (iStack_1c != 0)) {
    playsample(iStack_1c,dword_d2431,2,0x7f);
  }
  iVar4 = 1;
  do {
    drawshape_remap_home(local_44[iVar4]);
    iVar4 = iVar4 + 1;
  } while (iVar4 < 5);
  setpalette(0,0x100,acStack_664);
  drawshape2_home(local_44[0]);
  freemem(uVar3);
  bVar7 = true;
  while (bVar7) {
    bVar7 = false;
    iVar4 = 0;
    do {
      if (acStack_364[iVar4] < acStack_664[iVar4]) {
        bVar7 = true;
        acStack_664[iVar4] = acStack_664[iVar4] + -1;
      }
      iVar4 = iVar4 + 1;
    } while (iVar4 < 0x300);
    settimeout(5);
    waittimeout();
    if (bVar7) {
      setpalette(0,0x100,acStack_664);
    }
  }
  settimeout(0x28);
  waittimeout();
  if ((sound_enabled != '\0') && (local_20 != 0)) {
    playsample(local_20,dword_d2431);
  }
  iVar4 = 0xe0;
  do {
    if (0xe0 < iVar4) {
      iVar2 = (iVar4 + -1) * 3;
      acStack_664[iVar2] = '\0';
      acStack_664[iVar2 + 1] = '\0';
      acStack_664[iVar2 + 2] = '\0';
    }
    iVar2 = iVar4 * 3;
    acStack_664[iVar2] = '?';
    acStack_664[iVar2 + 1] = '?';
    acStack_664[iVar2 + 2] = '?';
    settimeout(2);
    waittimeout();
    setpalette(0,0x100,acStack_664);
    iVar4 = iVar4 + 1;
  } while (iVar4 < 0xf0);
  settimeout(200);
  waittimeout();
  if (sound_enabled == '\0') {
    if (local_2c == 0) {
      sub_33e6a(0x78);
    }
  }
  else {
    sound_fade(dword_d2431,0,100);
    sound_fade(dword_d2431,1,100);
    sound_fade(dword_d2431,2,100);
    sound_fade(dword_d2431,3,100);
  }
  if (sound_enabled != '\0') {
    do {
      iVar4 = sound_channel_status(ram0x000d242c >> 0x18,0);
    } while (iVar4 == 0);
    do {
      iVar4 = sound_channel_status(ram0x000d242c >> 0x18,1);
    } while (iVar4 == 0);
    do {
      iVar4 = sound_channel_status(ram0x000d242c >> 0x18,2);
    } while (iVar4 == 0);
    do {
      iVar4 = sound_channel_status(ram0x000d242c >> 0x18,3);
    } while (iVar4 == 0);
    dword_c721d = 0;
    if (local_24 != 0) {
      releasememblock(local_24);
    }
    if (iStack_1c != 0) {
      releasememblock(iStack_1c);
    }
    if (local_20 != 0) {
      releasememblock(local_20);
    }
  }
  if (sound_enabled != '\0') {
    dword_ccc94 = 0x20;
    sub_83459(dword_c4cfc);
    dword_ccc94 = 0;
  }
  speech_stop();
  fade_palette(1,acStack_364,0x10);
  _dos_gettime(local_30);
  srand((uint)bStack_2d);
  do {
    puVar6 = install_path;
    if (byte_ed833 != '\x01') {
      puVar6 = (undefined *)0x0;
    }
    make_path(acStack_64,puVar6,aEaopen,0);
    uVar3 = loadshapes(acStack_64,0);
    iVar4 = locateshape(uVar3,&aPal_c0861);
    memcpy(acStack_664,(void *)(iVar4 + 0x10),0x300);
    uVar5 = locateshape(uVar3,&aScrn_c0866);
    sub_912c8(uVar5);
    freemem(uVar3);
    if ((sound_enabled != '\0') && (dword_c721d == 0)) {
      puVar6 = install_path;
      if (byte_ed9a8 != '\x01') {
        puVar6 = (undefined *)0x0;
      }
      make_path(acStack_64,puVar6,aEasports,&aIff_c0875);
      dword_c721d = loadsound(acStack_64);
      if (dword_c721d != 0) {
        playsample(dword_c721d,dword_d2431,3,0x4c);
      }
    }
    fade_palette(0,acStack_664,0x10);
    settimeout(200);
    waittimeout();
    if ((sound_enabled != '\0') && (dword_c721d != 0)) {
      do {
        iVar4 = sound_channel_status(ram0x000d242c >> 0x18,3);
      } while (iVar4 == 0);
      releasememblock(dword_c721d);
      dword_c721d = 0;
    }
    fade_palette(1,acStack_664,0x10);
    setdefaultscreen();
    clearclip(0);
    iVar4 = ea_sports_intro();
  } while ((iVar4 == 0) && (iVar4 = demo_game(), iVar4 == 0));
  setdefaultscreen();
  clearclip(0);
  speech_stop();
  dword_cc0ec = 0;
  dword_c5130 = 0;
  return;
}


// ================================================================================================
// credits_screen @ 0x16f9a [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall credits_screen(void)

{
  char cVar1;
  char *pcVar2;
  undefined5 *puVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined5 *extraout_EDX;
  int extraout_EDX_00;
  int extraout_EDX_01;
  undefined *puVar7;
  int extraout_EDX_02;
  char *pcVar8;
  undefined5 **ppuVar9;
  undefined4 *puVar10;
  undefined4 *puVar11;
  int iVar12;
  undefined4 *puVar13;
  undefined4 *puVar14;
  int iVar15;
  byte bVar16;
  undefined5 *puStack_388;
  undefined auStack_384 [768];
  undefined5 auStack_84 [8];
  undefined auStack_44 [16];
  undefined4 local_34;
  undefined4 local_30;
  undefined4 *local_24;
  
  bVar16 = 0;
  __CHK(0x394);
  puStack_388 = (undefined5 *)0x16fb5;
  sub_17756();
  puStack_388 = (undefined5 *)0x16fba;
  speech_stop();
  puStack_388 = auStack_84;
  getfontstate();
  puStack_388 = font_main;
  setfont();
  puStack_388 = (undefined5 *)0x16fe5;
  set_text_colors(0x7f,0);
  puStack_388 = (undefined5 *)0x0;
  local_24 = (undefined4 *)allocmem(aBackwin,0x19337);
  puVar7 = install_path;
  if (byte_ed9e9 != '\x01') {
    puVar7 = (undefined *)0x0;
  }
  puStack_388 = (undefined5 *)0x17026;
  make_path(auStack_44,puVar7,aCredits,0);
  puStack_388 = (undefined5 *)0x0;
  puVar3 = (undefined5 *)loadshapes(auStack_44);
  puStack_388 = &aPal_c0861;
  iVar4 = locateshape(puVar3);
  puStack_388 = (undefined5 *)0x17059;
  memcpy(auStack_384,(void *)(iVar4 + 0x10),0x300);
  puStack_388 = (undefined5 *)0x1706a;
  memcpy(&palette_black,(void *)(iVar4 + 0x10),0x300);
  puStack_388 = &aBkgd;
  uVar5 = locateshape(puVar3);
  puVar13 = local_24 + (uint)bVar16 * -2 + 1;
  puVar10 = pointer_shapes + (uint)bVar16 * -2 + 1;
  *local_24 = *pointer_shapes;
  puVar14 = puVar13 + (uint)bVar16 * -2 + 1;
  puVar11 = puVar10 + (uint)bVar16 * -2 + 1;
  *puVar13 = *puVar10;
  *puVar14 = *puVar11;
  puVar14[(uint)bVar16 * -2 + 1] = puVar11[(uint)bVar16 * -2 + 1];
  *(undefined *)(puVar14 + (uint)bVar16 * -2 + 1 + (uint)bVar16 * -2 + 1) =
       *(undefined *)(puVar11 + (uint)bVar16 * -2 + 1 + (uint)bVar16 * -2 + 1);
  *(undefined2 *)(local_24 + 1) = 0x135;
  *(undefined2 *)((int)local_24 + 6) = 0x14e;
  puStack_388 = (undefined5 *)0x170a4;
  wait_sprite_fade(local_24,uVar5);
  puStack_388 = extraout_EDX;
  drawshape_home();
  puStack_388 = puVar3;
  freemem();
  puStack_388 = (undefined5 *)0x3f;
  grabshape(local_24,0x14a);
  if ((sound_enabled == '\0') || (dword_c721d != 0)) {
    puVar7 = install_path;
    if (dword_c541f == 8) {
      if (byte_ed8d0 != '\x01') {
        puVar7 = (undefined *)0x0;
      }
    }
    else if (byte_ed8d0 != '\x01') {
      puVar7 = (undefined *)0x0;
    }
    puStack_388 = (undefined5 *)0x1718c;
    make_path(auStack_44,puVar7,aAdtitle,&aKMS_c8140);
    puStack_388 = (undefined5 *)0x17198;
    local_30 = sub_8f13b(auStack_44);
    puVar7 = install_path;
    if (byte_ed92d != '\x01') {
      puVar7 = (undefined *)0x0;
    }
    puStack_388 = (undefined5 *)0x171c8;
    make_path(auStack_44,puVar7,aRockditi,&aKMS_c8140);
    puStack_388 = (undefined5 *)0x171d4;
    local_34 = sub_8f13b(auStack_44);
    puStack_388 = (undefined5 *)0x171e7;
    play_sample_by_ptr(local_30);
  }
  else {
    puVar7 = install_path;
    if (byte_ed9ad != '\x01') {
      puVar7 = (undefined *)0x0;
    }
    puStack_388 = (undefined5 *)0x17108;
    make_path(auStack_44,puVar7,aCredits,&aIff_c0875);
    puStack_388 = (undefined5 *)0x17114;
    dword_c721d = loadsound(auStack_44);
    if (dword_c721d != 0) {
      puStack_388 = (undefined5 *)0x17136;
      playsample(dword_c721d,dword_d2431,3,0x4c);
    }
  }
  pcVar8 = (char *)0x10;
  puStack_388 = (undefined5 *)0x171f5;
  fade_palette(0,auStack_384,0x10);
  ppuVar9 = &puStack_388;
  puStack_388 = (undefined5 *)0x171fa;
  say_goodnight();
  *(undefined4 *)((int)ppuVar9 + 0x35c) = 0;
  *(undefined4 *)((int)ppuVar9 + 0x364) = 0;
  iVar4 = extraout_EDX_00;
  do {
    if (*(int *)((int)ppuVar9 + 0x364) == 7) {
      *(undefined4 *)((int)ppuVar9 + -4) = font_kaufm;
      *(undefined4 *)((int)ppuVar9 + -8) = 0x17220;
      setfont();
      iVar4 = extraout_EDX_01;
    }
    uVar5 = (&off_c6399)[*(int *)((int)ppuVar9 + 0x364)];
    *(undefined4 *)((int)ppuVar9 + 0x368) = uVar5;
    *(undefined4 *)((int)ppuVar9 + -4) = 0x1723d;
    event_queue_reset(uVar5,iVar4,pcVar8);
    if (*(int *)((int)ppuVar9 + 0x364) != 0) {
      *(undefined4 *)((int)ppuVar9 + -4) = 0x17251;
      uVar5 = sub_33e6a(0x62);
      *(undefined4 *)((int)ppuVar9 + 0x35c) = uVar5;
    }
    if (*(int *)((int)ppuVar9 + 0x35c) != 0) break;
    if (*(undefined **)((int)ppuVar9 + 0x368) != &unk_c638c) {
      pcVar2 = *(char **)(*(undefined **)((int)ppuVar9 + 0x368) + 5);
      if (*pcVar2 == '\0') {
        *(undefined4 *)((int)ppuVar9 + -4) = 0x3f;
        *(undefined4 *)((int)ppuVar9 + -8) = 0x14a;
        *(undefined4 *)((int)ppuVar9 + -0xc) = *(undefined4 *)((int)ppuVar9 + 0x360);
        *(undefined4 *)((int)ppuVar9 + -0x10) = 0x17332;
        drawshape();
      }
      else {
        puVar7 = install_path;
        if (byte_ed9ea != '\x01') {
          puVar7 = (undefined *)0x0;
        }
        *(undefined4 *)((int)ppuVar9 + -4) = 0x172a7;
        make_path((undefined *)((int)ppuVar9 + 0x340),puVar7);
        *(undefined4 *)((int)ppuVar9 + -4) = 0;
        *(undefined **)((int)ppuVar9 + -8) = (undefined *)((int)ppuVar9 + 0x340);
        *(undefined4 *)((int)ppuVar9 + -0xc) = 0x172b6;
        uVar5 = loadshapes();
        *(undefined5 **)((int)ppuVar9 + -4) = &aShp0;
        *(undefined4 *)((int)ppuVar9 + -8) = uVar5;
        *(undefined4 *)((int)ppuVar9 + -0xc) = 0x172c6;
        uVar6 = locateshape();
        *(undefined4 *)((int)ppuVar9 + -4) = 0x3f;
        *(undefined4 *)((int)ppuVar9 + -8) = 0x14a;
        *(undefined4 *)((int)ppuVar9 + -0xc) = *(undefined4 *)((int)ppuVar9 + 0x360);
        *(undefined4 *)((int)ppuVar9 + -0x10) = 0x172df;
        drawshape();
        *(undefined4 *)((int)ppuVar9 + -4) = 0x172e7;
        iVar4 = rand();
        *(int *)((int)ppuVar9 + -4) = iVar4 % 8 + 0x6a;
        *(undefined4 *)((int)ppuVar9 + -8) = 0x172fc;
        iVar4 = rand();
        *(int *)((int)ppuVar9 + -8) = iVar4 % 8 + 0x85;
        *(undefined4 *)((int)ppuVar9 + -0xc) = uVar6;
        *(undefined4 *)((int)ppuVar9 + -0x10) = 0x17310;
        drawshape_remap();
        *(undefined4 *)((int)ppuVar9 + -4) = uVar5;
        *(undefined4 *)((int)ppuVar9 + -8) = 0x17319;
        freemem();
        pcVar8 = pcVar2;
      }
      *(undefined4 *)((int)ppuVar9 + 0x358) = *(undefined4 *)(*(int *)((int)ppuVar9 + 0x368) + 1);
      iVar4 = (int)**(char **)((int)ppuVar9 + 0x368);
      iVar15 = 0xda - ((int)((uint)byte_d42c3 * iVar4) >> 1);
      for (iVar12 = 0; cVar1 = **(char **)((int)ppuVar9 + 0x368), iVar12 < cVar1;
          iVar12 = iVar12 + 1) {
        pcVar8 = *(char **)(iVar12 * 4 + *(int *)((int)ppuVar9 + 0x368) + 9);
        *(char **)((int)ppuVar9 + -4) = pcVar8;
        *(undefined4 *)((int)ppuVar9 + -8) = 0x1737c;
        iVar4 = textwidth();
        *(undefined4 *)((int)ppuVar9 + -4) = 0x17393;
        sub_174d8(0x1ea - (iVar4 >> 1),iVar15);
        iVar15 = iVar15 + (uint)byte_d42c3;
        iVar4 = extraout_EDX_02;
      }
      *(undefined4 *)((int)ppuVar9 + -4) = 0x173b0;
      event_queue_reset((int)cVar1,iVar4,pcVar8);
      *(undefined4 *)((int)ppuVar9 + -4) = 0x173bc;
      iVar4 = sub_33e6a(*(undefined4 *)((int)ppuVar9 + 0x358));
      if (iVar4 != 0) break;
    }
    iVar4 = *(int *)((int)ppuVar9 + 0x364) + 1;
    *(int *)((int)ppuVar9 + 0x364) = iVar4;
  } while (iVar4 < 0x1d);
  *(undefined4 *)((int)ppuVar9 + -4) = 0x3f;
  *(undefined4 *)((int)ppuVar9 + -8) = 0x14a;
  *(undefined4 *)((int)ppuVar9 + -0xc) = *(undefined4 *)((int)ppuVar9 + 0x360);
  *(undefined4 *)((int)ppuVar9 + -0x10) = 0x173ec;
  drawshape();
  uVar5 = dword_d2431;
  if ((sound_enabled != '\0') && (dword_c721d != 0)) {
    *(undefined4 *)((int)ppuVar9 + -4) = 0x17415;
    sound_fade(uVar5,3,100);
  }
  *(undefined4 *)((int)ppuVar9 + -4) = 0x1741a;
  sub_8374d();
  *(undefined4 *)((int)ppuVar9 + -4) = 0x1742b;
  fade_palette(1,ppuVar9,0x10);
  if ((sound_enabled == '\0') || (dword_c721d == 0)) {
    *(undefined4 *)((int)ppuVar9 + -4) = 0x17470;
    stop_crowd_loop();
    *(undefined4 *)((int)ppuVar9 + -4) = 0x1747c;
    sub_8f1fe(*(undefined4 *)((int)ppuVar9 + 0x354));
    *(undefined4 *)((int)ppuVar9 + -4) = 0x17488;
    sub_8f1fe(*(undefined4 *)((int)ppuVar9 + 0x350));
  }
  else {
    do {
      iVar4 = ram0x000d242c >> 0x18;
      *(undefined4 *)((int)ppuVar9 + -4) = 0x1744f;
      iVar4 = sound_channel_status(iVar4,3);
    } while (iVar4 == 0);
    *(int *)((int)ppuVar9 + -4) = dword_c721d;
    *(undefined4 *)((int)ppuVar9 + -8) = 0x1745f;
    releasememblock();
    dword_c721d = 0;
  }
  *(undefined **)((int)ppuVar9 + -4) = (undefined *)((int)ppuVar9 + 0x300);
  *(undefined4 *)((int)ppuVar9 + -8) = 0x17495;
  setfontstate();
  *(undefined4 *)((int)ppuVar9 + -4) = *(undefined4 *)((int)ppuVar9 + 0x360);
  *(undefined4 *)((int)ppuVar9 + -8) = 0x174a5;
  freemem();
  *(undefined4 *)((int)ppuVar9 + -4) = 0x174ad;
  setdefaultscreen();
  *(undefined4 *)((int)ppuVar9 + -4) = 0;
  *(undefined4 *)((int)ppuVar9 + -8) = 0x174b4;
  clearclip();
  return;
}


// ================================================================================================
// set_text_colors @ 0x174c2 [__watcall]
// ================================================================================================

void __watcall set_text_colors(undefined4 param_1,undefined4 unaff_EDX)

{
  __CHK(4);
  dword_c6418 = param_1;
  dword_c641c = unaff_EDX;
  return;
}


// ================================================================================================
// sub_174d8 @ 0x174d8 [__watcall]
// ================================================================================================

void __watcall sub_174d8(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX)

{
  uint uVar1;
  int iVar2;
  undefined auStack_70 [96];
  
  __CHK(0x84);
  uVar1 = textwidth(unaff_EBX,param_1);
  iVar2 = windowdefp((uVar1 & 0xffc0) + 0x40,byte_d42c3 + 1,0);
  sub_b3a88(auStack_70);
  setscreen(iVar2);
  clearclip(0xff);
  print_text_at(0,0,unaff_EBX);
  sub_b3aa1(auStack_70);
  drawshape_remap(*(undefined4 *)(iVar2 + 0x2c),param_1,unaff_EDX);
  sub_9132c(iVar2);
  return;
}


// ================================================================================================
// sub_17573 @ 0x17573 [__watcall]
// ================================================================================================

void __watcall sub_17573(int param_1,undefined4 unaff_EDX)

{
  int iVar1;
  
  __CHK(0x24);
  iVar1 = textwidth(unaff_EDX);
  iVar1 = (0x280 - iVar1) / 2;
  dword_d42a8 = dword_c641c;
  printstr_at(unaff_EDX,iVar1 + 1,param_1 + 1);
  dword_d42a8 = dword_c6418;
  printstr_at(unaff_EDX,iVar1,param_1);
  sub_17793(iVar1,param_1,unaff_EDX);
  return;
}


// ================================================================================================
// print_text_at @ 0x175e2 [__watcall]
// ================================================================================================

void __watcall print_text_at(int param_1,int unaff_EDX,undefined4 unaff_EBX)

{
  __CHK(0x20);
  dword_d42a8 = dword_c641c;
  printstr_at(unaff_EBX,param_1 + 1,unaff_EDX + 1);
  dword_d42a8 = dword_c6418;
  printstr_at(unaff_EBX,param_1,unaff_EDX);
  sub_17793(param_1,unaff_EDX,unaff_EBX);
  return;
}


// ================================================================================================
// sub_17636 @ 0x17636 [__watcall]
// ================================================================================================

void __watcall sub_17636(int param_1,int unaff_EDX,undefined4 unaff_EBX)

{
  int iVar1;
  
  __CHK(0x24);
  dword_d42a8 = dword_c641c;
  iVar1 = 0;
  do {
    printstr_at(unaff_EBX,(&unk_c6420)[iVar1] + param_1,(&unk_c6430)[iVar1] + unaff_EDX);
    iVar1 = iVar1 + 1;
  } while (iVar1 < 4);
  dword_d42a8 = dword_c6418;
  printstr_at(unaff_EBX,param_1,unaff_EDX);
  sub_17793(param_1,unaff_EDX,unaff_EBX);
  return;
}


// ================================================================================================
// sub_176ae @ 0x176ae [__watcall]
// ================================================================================================

void __watcall sub_176ae(undefined4 param_1,undefined4 param_2,char *unaff_EBX,undefined4 unaff_ECX)

{
  undefined4 extraout_EDX;
  char acStack_58 [80];
  undefined4 uStack_8;
  
  uStack_8 = 0x176b8;
  __CHK(0x68);
  sprintf(acStack_58,unaff_EBX,unaff_ECX);
  print_text_at(param_1,extraout_EDX,acStack_58);
  return;
}


// ================================================================================================
// sub_176db @ 0x176db [__watcall]
// ================================================================================================

void __watcall
sub_176db(undefined4 param_1,undefined4 param_2,char *unaff_EBX,undefined4 unaff_ECX,
         undefined4 param_5)

{
  undefined4 extraout_EDX;
  char acStack_5c [84];
  
  __CHK(0x70);
  sprintf(acStack_5c,unaff_EBX,unaff_ECX,param_5);
  print_text_at(param_1,extraout_EDX,acStack_5c);
  return;
}


// ================================================================================================
// sub_17711 @ 0x17711 [__watcall]
// ================================================================================================

void __watcall sub_17711(void)

{
  __CHK(0xc);
  if (dword_c6410 == (void *)0x0) {
    dword_c6410 = (void *)sub_91984(0xe74);
  }
  dword_c6414 = 1;
  memset(dword_c6410,0x20,0xe10);
  return;
}


// ================================================================================================
// sub_17756 @ 0x17756 [__watcall]
// ================================================================================================

void __watcall sub_17756(void)

{
  __CHK(0xc);
  if (dword_c6410 != 0) {
    sub_91a67(dword_c6410);
  }
  dword_c6410 = 0;
  return;
}


// ================================================================================================
// sub_1777e @ 0x1777e [__watcall]
// ================================================================================================

void __watcall sub_1777e(void)

{
  __CHK(8);
  dword_c6414 = 0;
  return;
}


// ================================================================================================
// sub_17793 @ 0x17793 [__watcall]
// ================================================================================================

void __watcall sub_17793(int param_1,int unaff_EDX,char *unaff_EBX)

{
  size_t __n;
  void *__dest;
  
  __CHK(0xc);
  if ((dword_c6410 != 0) && (dword_c6414 == 1)) {
    __dest = (void *)(dword_c6410 + (param_1 * 100) / 0x280 + ((unaff_EDX * 0x24) / 0x1e0) * 100);
    __n = strlen(unaff_EBX);
    memcpy(__dest,unaff_EBX,__n);
  }
  return;
}


// ================================================================================================
// export_stats_dialog @ 0x17816 [__watcall]
// ================================================================================================

void __watcall export_stats_dialog(char *param_1)

{
  int iVar1;
  FILE *pFVar2;
  undefined4 uVar3;
  char *__src;
  undefined **ppuVar4;
  undefined4 uVar5;
  char acStack_a0 [100];
  undefined local_3c;
  undefined uStack_3b;
  char acStack_38 [20];
  undefined4 local_24;
  undefined4 local_20;
  undefined local_1c [4];
  undefined auStack_18 [4];
  
  __CHK(0xb8);
  if (dword_c6410 != (char *)0x0) {
    local_24 = 4;
    local_20 = 0;
    strcpy(acStack_38,param_1);
    strcat(acStack_38,(char *)&aOUT);
    iVar1 = sub_142e7(acStack_38);
    if (iVar1 == 0) {
      iVar1 = check_disk_space(0,&local_24);
    }
    else {
      iVar1 = 0;
    }
    if (iVar1 == 0) {
      uStack_3b = 0;
      pFVar2 = fopen(acStack_38,(char *)&aRt);
      if (pFVar2 != (FILE *)0x0) {
        fclose(pFVar2);
        iVar1 = message_dialog(0xffffffff,0xffffffff,&off_c648e,2,&unk_c6499,2,auStack_18,local_1c,
                               0xffffffff);
        if (iVar1 != 1) {
          return;
        }
      }
      pFVar2 = fopen(acStack_38,(char *)&aWt);
      if (pFVar2 == (FILE *)0x0) {
        uVar5 = 0xffffffff;
        uVar3 = 1;
        ppuVar4 = &off_c652a;
      }
      else {
        iVar1 = 0;
        __src = dword_c6410;
        do {
          strncpy(acStack_a0,__src,100);
          local_3c = 10;
          uStack_3b = 0;
          sub_91e72(acStack_a0,pFVar2);
          __src = __src + 100;
          iVar1 = iVar1 + 1;
        } while (iVar1 < 0x24);
        fclose(pFVar2);
        uVar5 = 0xffffffff;
        uVar3 = 1;
        ppuVar4 = &off_c64f5;
      }
    }
    else {
      sprintf(aRequireXXKbytesOfFreeDis,aRequire2dKbytesOfFreeDis,iVar1);
      uVar5 = 800;
      uVar3 = 3;
      ppuVar4 = (undefined **)&off_c659a;
    }
    message_dialog(0xffffffff,0xffffffff,ppuVar4,uVar3,0,0,auStack_18,local_1c,uVar5);
  }
  return;
}


// ================================================================================================
// sub_179b6 @ 0x179b6 [__watcall]
// ================================================================================================

undefined8 __watcall sub_179b6(undefined4 param_1,undefined4 unaff_EDX)

{
  __CHK(8);
  dword_c65bc = 1;
  return CONCAT44(unaff_EDX,1);
}


// ================================================================================================
// sub_179d0 @ 0x179d0 [__watcall]
// ================================================================================================

undefined4 __watcall sub_179d0(void)

{
  __CHK(4);
  dword_c65bc = 2;
  return 1;
}


// ================================================================================================
// unk_179e6 @ 0x179e6
// ================================================================================================

undefined4 unk_179e6(void)

{
  __CHK(4);
  dword_c65bc = 3;
  return 1;
}


// ================================================================================================
// sub_179eb @ 0x179eb [__watcall]
// ================================================================================================

undefined4 __watcall sub_179eb(void)

{
  undefined4 unaff_retaddr;
  
  __CHK(unaff_retaddr);
  dword_c65bc = 3;
  return 1;
}


// ================================================================================================
// sub_17a00 @ 0x17a00 [__watcall]
// ================================================================================================

void __watcall sub_17a00(void)

{
  __CHK(0x20);
  if ((dword_c695a != 0) || (dword_c6956 != 0)) {
    byte_c671c = 1;
    byte_c6777 = 2;
    byte_c6759 = 2;
    byte_c6745 = 2;
    byte_c672f = 2;
    dword_c695a = 0;
    if (dword_c6956 != 0) {
      dword_c65b4 = 0;
    }
    dword_c6956 = 0;
    strncpy(&unk_c65d4,&unk_c529c,0x1f);
    if (dword_dc738 != 0) {
      getpalette(0,0x100,&unk_dc340);
      fade_palette(1,&unk_dc340,0x10);
      dword_c6a60 = 1;
      dword_dd120 = &unk_dc340;
      dword_dc6b4 = 0xffffffff;
      (*dword_c65b8)();
      dword_c6a60 = 0;
      dword_dd120 = (undefined *)0x0;
      fade_palette(0,&unk_dc340,0x10);
    }
  }
  return;
}


// ================================================================================================
// sub_17af3 @ 0x17af3 [__watcall]
// ================================================================================================

void __watcall sub_17af3(void)

{
  __CHK(0x24);
  if ((dword_c695a != 0) || (dword_c6956 != 1)) {
    byte_c672f = 1;
    byte_c6777 = 2;
    byte_c6759 = 2;
    byte_c6745 = 2;
    byte_c671c = 2;
    dword_c695a = 0;
    if (dword_c6956 == 0) {
      dword_c65b4 = 0;
    }
    dword_c6956 = 1;
    strncpy(&unk_c65d4,&unk_c529c,0x1f);
    if (dword_dc738 != 0) {
      getpalette(0,0x100,&unk_dc340);
      fade_palette(1,&unk_dc340,0x10);
      dword_c6a60 = 1;
      dword_dd120 = &unk_dc340;
      dword_dc6b4 = 0xffffffff;
      (*dword_c65b8)();
      dword_c6a60 = 0;
      dword_dd120 = (undefined *)0x0;
      fade_palette(0,&unk_dc340,0x10);
    }
  }
  return;
}


// ================================================================================================
// sub_17be7 @ 0x17be7 [__watcall]
// ================================================================================================

void __watcall sub_17be7(void)

{
  __CHK(0x24);
  if ((dword_c695a != 1) || (dword_c6956 != 0)) {
    byte_c6745 = 1;
    byte_c6777 = 2;
    byte_c6759 = 2;
    byte_c672f = 2;
    byte_c671c = 2;
    dword_c695a = 1;
    if (dword_c6956 != 0) {
      dword_c65b4 = 0;
    }
    dword_c6956 = 0;
    strncpy(&unk_c65d4,&byte_c5386,0x1f);
    if (dword_dc738 != 0) {
      getpalette(0,0x100,&unk_dc340);
      fade_palette(1,&unk_dc340,0x10);
      dword_c6a60 = 1;
      dword_dd120 = &unk_dc340;
      dword_dc6b4 = 0xffffffff;
      (*dword_c65b8)();
      dword_c6a60 = 0;
      dword_dd120 = (undefined *)0x0;
      fade_palette(0,&unk_dc340,0x10);
    }
  }
  return;
}


// ================================================================================================
// sub_17ce0 @ 0x17ce0 [__watcall]
// ================================================================================================

void __watcall sub_17ce0(void)

{
  int iVar1;
  
  __CHK(0x24);
  if (((dword_c695a == 1) && (dword_c6956 == 1)) &&
     (iVar1 = strcmp(&unk_c65d4,&byte_c5386), iVar1 == 0)) {
    return;
  }
  byte_c6759 = 1;
  byte_c6777 = 2;
  byte_c6745 = 2;
  byte_c672f = 2;
  byte_c671c = 2;
  dword_c695a = 1;
  if (dword_c6956 == 0) {
    dword_c65b4 = dword_c6956;
  }
  dword_c6956 = 1;
  strncpy(&unk_c65d4,&byte_c5386,0x1f);
  if (dword_dc738 != 0) {
    getpalette(0,0x100,&unk_dc340);
    fade_palette(1,&unk_dc340,0x10);
    dword_c6a60 = 1;
    dword_dd120 = &unk_dc340;
    dword_dc6b4 = 0xffffffff;
    (*dword_c65b8)();
    dword_c6a60 = 0;
    dword_dd120 = (undefined *)0x0;
    fade_palette(0,&unk_dc340,0x10);
  }
  return;
}


// ================================================================================================
// sub_17d6e @ 0x17d6e [__watcall]
// ================================================================================================

void __watcall sub_17d6e(void)

{
  int iVar1;
  
  __CHK(0x24);
  if (((dword_c695a == 1) && (dword_c6956 == 1)) &&
     (iVar1 = strcmp(&unk_c65d4,&byte_c5311), iVar1 == 0)) {
    return;
  }
  byte_c6777 = 1;
  byte_c6759 = 2;
  byte_c6745 = 2;
  byte_c672f = 2;
  byte_c671c = 2;
  dword_c695a = 1;
  if (dword_c6956 == 0) {
    dword_c65b4 = dword_c6956;
  }
  dword_c6956 = 1;
  strncpy(&unk_c65d4,&byte_c5311,0x1f);
  if (dword_dc738 != 0) {
    getpalette(0,0x100,&unk_dc340);
    fade_palette(1,&unk_dc340,0x10);
    dword_c6a60 = 1;
    dword_dd120 = &unk_dc340;
    dword_dc6b4 = 0xffffffff;
    (*dword_c65b8)();
    dword_c6a60 = 0;
    dword_dd120 = (undefined *)0x0;
    fade_palette(0,&unk_dc340,0x10);
  }
  return;
}


// ================================================================================================
// sub_17dfc @ 0x17dfc [__watcall]
// ================================================================================================

undefined8 __watcall sub_17dfc(undefined4 param_1,undefined4 unaff_EDX)

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
    dword_dc6a8 = team_stats_screen(5);
    fade_palette(0,dword_dc6ac,0x10);
    freemem(dword_dc6ac);
    return CONCAT44(unaff_EDX,dword_dc6a8);
  }
  uVar1 = (*dword_c65c0)();
  return CONCAT44(unaff_EDX,uVar1);
}


// ================================================================================================
// sub_17edf @ 0x17edf [__watcall]
// ================================================================================================

undefined8 __watcall sub_17edf(undefined4 param_1,undefined4 unaff_EDX)

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
    dword_dc6a8 = team_stats_screen(0);
    fade_palette(0,dword_dc6ac,0x10);
    freemem(dword_dc6ac);
    return CONCAT44(unaff_EDX,dword_dc6a8);
  }
  uVar1 = (*dword_c65c0)();
  return CONCAT44(unaff_EDX,uVar1);
}


// ================================================================================================
// sub_17fbc @ 0x17fbc [__watcall]
// ================================================================================================

undefined8 __watcall sub_17fbc(undefined4 param_1,undefined4 unaff_EDX)

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
    dword_dc6a8 = team_stats_screen(1);
    fade_palette(0,dword_dc6ac,0x10);
    freemem(dword_dc6ac);
    return CONCAT44(unaff_EDX,dword_dc6a8);
  }
  uVar1 = (*dword_c65c0)();
  return CONCAT44(unaff_EDX,uVar1);
}


