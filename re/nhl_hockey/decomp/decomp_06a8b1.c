// Decompiled by Ghidra from hockey.elf (via ledisasm ELF export)
// This is machine generated pseudo-C meant as a reference for porting, it does not compile as is.
#include "prototypes.h"

// ================================================================================================
// zm_add_rect @ 0x6a8b1 [__watcall]
// ================================================================================================

void __watcall zm_add_rect(undefined4 param_1,int unaff_EDX)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  undefined8 uVar4;
  
  __CHK(8);
  iVar1 = dword_ea06c;
  dword_ea068 = param_1;
  if (unaff_EDX == 0) {
    iVar1 = zm_rect_overlaps(&dword_ea034);
    if (iVar1 == 0) {
      return;
    }
    zm_clip_rect_to_view();
    iVar3 = dword_ea06c;
    while (iVar1 = dword_ea06c, iVar3 != -1) {
      uVar4 = zm_rect_contains(iVar3 * 0x10 + dword_ea060);
      uVar2 = (uint)uVar4;
      if (uVar2 != 0) {
        if (uVar2 < 2) {
          return;
        }
        iVar1 = dword_ea06c;
        if (uVar2 == 2) break;
      }
      iVar3 = *(int *)(dword_ea090 + (int)((ulonglong)uVar4 >> 0x20) * 4);
    }
  }
  do {
    iVar3 = dword_ea06c;
    if (iVar1 == -1) break;
    uVar4 = zm_rect_overlaps(iVar1 * 0x10 + dword_ea060);
    iVar1 = (int)((ulonglong)uVar4 >> 0x20);
    uVar2 = (uint)uVar4;
    if (uVar2 != 0) {
      if (uVar2 < 2) {
        zm_split_rect(iVar1);
        return;
      }
      iVar3 = dword_ea06c;
      if (uVar2 == 2) break;
    }
    iVar1 = *(int *)(dword_ea090 + iVar1 * 4);
  } while( true );
LAB_0006a95a:
  if (iVar3 == -1) {
LAB_0006a989:
    zm_insert_rect_sorted();
    return;
  }
  uVar4 = zm_rect_merge_adjacent(dword_ea060 + iVar3 * 0x10);
  uVar2 = (uint)uVar4;
  if (uVar2 != 0) {
    if (uVar2 < 2) {
      return;
    }
    if (uVar2 == 2) goto LAB_0006a989;
  }
  iVar3 = *(int *)(dword_ea090 + (int)((ulonglong)uVar4 >> 0x20) * 4);
  goto LAB_0006a95a;
}


// ================================================================================================
// zm_add_dirty_zones @ 0x6a990 [__watcall]
// ================================================================================================

void __watcall zm_add_dirty_zones(int param_1,byte *unaff_EDX)

{
  byte *pbVar1;
  
  __CHK(0xc);
  pbVar1 = unaff_EDX + dword_ea0b4 * 4;
  do {
    if ((*unaff_EDX & 4) != 0) {
      zm_add_rect(param_1,0);
    }
    param_1 = param_1 + 0x10;
    unaff_EDX = unaff_EDX + 4;
  } while (unaff_EDX < pbVar1);
  return;
}


// ================================================================================================
// zone_manager_init @ 0x6a9ce [__watcall]
// ================================================================================================

void __watcall zone_manager_init(int param_1)

{
  int iVar1;
  int iVar2;
  
  __CHK(0x20);
  if (param_1 == 0) {
    dword_ea078 = param_1;
    return;
  }
  dword_ea078 = 1;
  dword_ea098 = 0;
  dword_ea0b4 = param_1;
  dword_ea084 = allocmem(aZONEMGR,param_1 * 0x50,0x20);
  dword_ea080 = dword_ea084 + dword_ea0b4 * 0x10;
  dword_ea060 = dword_ea080 + dword_ea0b4 * 0x10;
  dword_ea0a0 = dword_ea060 + dword_ea0b4 * 0x20;
  dword_ea0a4 = dword_ea0a0 + dword_ea0b4 * 4;
  dword_ea090 = dword_ea0a4 + dword_ea0b4 * 4;
  dword_ea088 = dword_ea084;
  for (iVar2 = 0; iVar1 = dword_ea0a4, iVar2 < dword_ea0b4; iVar2 = iVar2 + 1) {
    *(undefined4 *)(dword_ea0a4 + iVar2 * 4) = 0;
    *(undefined4 *)(dword_ea0a0 + iVar2 * 4) = *(undefined4 *)(iVar1 + iVar2 * 4);
  }
  dword_ea070 = 0;
  dword_ea07c = 0;
  iVar2 = 0;
  while (iVar2 < dword_ea0b4 * 2 + -1) {
    *(int *)(dword_ea090 + iVar2 * 4) = iVar2 + 1;
    iVar2 = iVar2 + 1;
  }
  *(undefined4 *)(dword_ea090 + -4 + dword_ea0b4 * 8) = 0xffffffff;
  return;
}


// ================================================================================================
// zm_free @ 0x6aad5 [__watcall]
// ================================================================================================

void __watcall
zm_free(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  __CHK(0x14);
  freemem(dword_ea088,unaff_EDX,unaff_ECX,unaff_EBX);
  return;
}


// ================================================================================================
// zm_zone_set_point @ 0x6aaf5 [__watcall]
// ================================================================================================

void __watcall zm_zone_set_point(int param_1,int *unaff_EDX)

{
  byte *pbVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  
  __CHK(0x10);
  if ((dword_ea078 != 0) && (param_1 <= dword_ea0b4)) {
    piVar4 = (int *)(param_1 * 0x10 + dword_ea074);
    iVar2 = *unaff_EDX;
    iVar3 = unaff_EDX[1];
    if ((*(byte *)(dword_ea09c + param_1 * 4) & 4) == 0) {
      piVar4[1] = iVar2;
      *piVar4 = iVar2;
      piVar4[3] = iVar3;
      piVar4[2] = iVar3;
      pbVar1 = (byte *)(param_1 * 4 + dword_ea09c);
      *pbVar1 = *pbVar1 | 4;
      return;
    }
    if (iVar2 < *piVar4) {
      *piVar4 = iVar2;
    }
    else if (piVar4[1] < iVar2) {
      piVar4[1] = iVar2;
    }
    if (iVar3 < piVar4[2]) {
      piVar4[2] = iVar3;
      return;
    }
    if (piVar4[3] < iVar3) {
      piVar4[3] = iVar3;
    }
  }
  return;
}


// ================================================================================================
// zm_zone_set_rect @ 0x6ab7c [__watcall]
// ================================================================================================

void __watcall zm_zone_set_rect(int param_1,int unaff_EDX,int unaff_EBX,int unaff_ECX,int param_5)

{
  byte *pbVar1;
  int *piVar2;
  
  __CHK(0xc);
  if ((dword_ea078 != 0) && (param_1 <= dword_ea0b4)) {
    piVar2 = (int *)(param_1 * 0x10 + dword_ea074);
    if ((*(byte *)(dword_ea09c + param_1 * 4) & 4) == 0) {
      *piVar2 = unaff_EDX;
      piVar2[1] = unaff_ECX;
      piVar2[2] = unaff_EBX;
      piVar2[3] = param_5;
      pbVar1 = (byte *)(param_1 * 4 + dword_ea09c);
      *pbVar1 = *pbVar1 | 4;
      return;
    }
    if (unaff_EDX < *piVar2) {
      *piVar2 = unaff_EDX;
    }
    if (piVar2[1] < unaff_ECX) {
      piVar2[1] = unaff_ECX;
    }
    if (unaff_EBX < piVar2[2]) {
      piVar2[2] = unaff_EBX;
    }
    if (piVar2[3] < param_5) {
      piVar2[3] = param_5;
    }
  }
  return;
}


// ================================================================================================
// zm_zone_set_text @ 0x6abf9 [__watcall]
// ================================================================================================

void __watcall zm_zone_set_text(undefined4 param_1,undefined4 unaff_EDX,int unaff_EBX,int unaff_ECX)

{
  int iVar1;
  int iVar2;
  
  __CHK(0x14);
  iVar1 = (uint)byte_d42c3 + unaff_ECX;
  iVar2 = textwidth(unaff_EDX,iVar1);
  zm_zone_set_rect(param_1,unaff_EBX,unaff_ECX,unaff_EBX + iVar2,iVar1);
  return;
}


// ================================================================================================
// zm_zone_set_points @ 0x6ac31 [__watcall]
// ================================================================================================

void __watcall zm_zone_set_points(int param_1,int unaff_EDX,int *unaff_EBX)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  
  __CHK(0x1c);
  if (((dword_ea078 != 0) && (unaff_EDX != 0)) && (param_1 <= dword_ea0b4)) {
    iVar4 = *unaff_EBX;
    iVar6 = unaff_EBX[1];
    iVar1 = iVar6;
    iVar7 = iVar4;
    while (iVar5 = iVar1, unaff_EDX = unaff_EDX + -1, unaff_EDX != 0) {
      piVar3 = unaff_EBX + 2;
      iVar1 = *piVar3;
      iVar8 = iVar1;
      if ((iVar7 <= iVar1) && (iVar8 = iVar7, iVar4 <= iVar1)) {
        iVar4 = iVar1 + 1;
      }
      iVar2 = unaff_EBX[3];
      unaff_EBX = piVar3;
      iVar1 = iVar2;
      iVar7 = iVar8;
      if ((iVar5 <= iVar2) && (iVar1 = iVar5, iVar6 <= iVar2)) {
        iVar6 = iVar2 + 1;
      }
    }
    zm_zone_set_rect(param_1,iVar7,iVar5,iVar4,iVar6);
  }
  return;
}


// ================================================================================================
// zm_zone_set_circle @ 0x6aca2 [__watcall]
// ================================================================================================

void __watcall zm_zone_set_circle(undefined4 param_1,int unaff_EDX,int unaff_EBX,int unaff_ECX)

{
  int iVar1;
  
  __CHK(0x18);
  if (unaff_ECX == 0) {
    zm_zone_set_point(param_1,&stack0xfffffff0);
  }
  else {
    iVar1 = unaff_ECX - (unaff_ECX >> 2);
    zm_zone_set_rect(param_1,unaff_EDX - unaff_ECX,(unaff_EBX - iVar1) + 1,unaff_EDX + unaff_ECX,
              iVar1 + unaff_EBX + -1);
  }
  return;
}


// ================================================================================================
// zm_zone_set_shape_home @ 0x6ace9 [__watcall]
// ================================================================================================

void __watcall zm_zone_set_shape_home(undefined4 param_1,int unaff_EDX)

{
  int iVar1;
  int iVar2;
  
  __CHK(0x14);
  iVar2 = *(int *)(unaff_EDX + 0xc) >> 0x10;
  iVar1 = *(int *)(unaff_EDX + 10) >> 0x10;
  zm_zone_set_rect(param_1,iVar1,iVar2,(*(int *)(unaff_EDX + 2) >> 0x10) + iVar1,
            (*(int *)(unaff_EDX + 4) >> 0x10) + iVar2);
  return;
}


// ================================================================================================
// zm_zone_set_shape @ 0x6ad22 [__watcall]
// ================================================================================================

void __watcall zm_zone_set_shape(undefined4 param_1,int unaff_EDX,int unaff_EBX,int unaff_ECX)

{
  __CHK(0xc);
  zm_zone_set_rect(param_1,unaff_EBX,unaff_ECX,(*(int *)(unaff_EDX + 2) >> 0x10) + unaff_EBX,
            (*(int *)(unaff_EDX + 4) >> 0x10) + unaff_ECX);
  return;
}


// ================================================================================================
// zm_restore_background @ 0x6ad4f [__watcall]
// ================================================================================================

void __watcall zm_restore_background(void)

{
  int iVar1;
  int extraout_EDX;
  
  __CHK(0xc);
  if ((dword_ea07c != 0) && (iVar1 = dword_ea06c, ((byte)dword_ea058 & 0x41) == 0)) {
    while (iVar1 != -1) {
      zm_restore_rect(dword_ea060 + iVar1 * 0x10);
      iVar1 = *(int *)(dword_ea090 + extraout_EDX * 4);
    }
    return;
  }
  zm_restore_rect(&dword_ea034);
  return;
}


// ================================================================================================
// present_frame @ 0x6ada7 [__watcall]
// ================================================================================================

void __watcall
present_frame(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  int iVar1;
  int extraout_EDX;
  undefined4 uVar2;
  undefined4 uVar3;
  
  __CHK(0x10);
  uVar2 = unaff_ECX;
  uVar3 = unaff_EBX;
  setdefaultscreen();
  empty_func_6a2bc(dword_ea074,dword_ea09c,unaff_EBX,unaff_ECX,unaff_EDX,uVar2,uVar3);
  if ((dword_ea0b4 == 0) || (((byte)dword_ea058 & 0x42) != 0)) {
    zm_copy_playfield_from_hidden();
    dword_ea058._0_1_ = (byte)dword_ea058 & 0xfd;
  }
  else {
    if (dword_ea05c == 0) {
      zm_close_list();
      zm_add_dirty_zones(dword_ea094,dword_ea08c,1);
    }
    zm_add_dirty_zones(dword_ea074,dword_ea09c,0);
    iVar1 = dword_ea06c;
    while (iVar1 != -1) {
      zm_copy_rect_from_hidden(dword_ea060 + iVar1 * 0x10);
      iVar1 = *(int *)(dword_ea090 + extraout_EDX * 4);
    }
  }
  dword_ea098 = (uint)(dword_ea098 == 0);
  return;
}


// ================================================================================================
// zm_bounding_rect @ 0x6ae5c [__watcall]
// ================================================================================================

void __watcall zm_bounding_rect(void)

{
  int iVar1;
  int iVar2;
  
  __CHK(0x10);
  dword_ea044 = 999;
  for (iVar2 = dword_ea06c; iVar2 != -1; iVar2 = *(int *)(dword_ea090 + iVar2 * 4)) {
    iVar1 = *(int *)(dword_ea060 + iVar2 * 0x10);
    if (iVar1 < dword_ea044) {
      dword_ea044 = iVar1;
    }
    if (dword_ea044 == 0) break;
  }
  dword_ea048 = 0;
  for (iVar2 = dword_ea06c; iVar2 != -1; iVar2 = *(int *)(dword_ea090 + iVar2 * 4)) {
    iVar1 = *(int *)(dword_ea060 + 4 + iVar2 * 0x10);
    if (dword_ea048 < iVar1) {
      dword_ea048 = iVar1;
    }
    if (dword_ea038 <= dword_ea048) break;
  }
  dword_ea04c = 999;
  for (iVar2 = dword_ea06c; iVar2 != -1; iVar2 = *(int *)(dword_ea090 + iVar2 * 4)) {
    iVar1 = *(int *)(dword_ea060 + 8 + iVar2 * 0x10);
    if (iVar1 < dword_ea04c) {
      dword_ea04c = iVar1;
    }
    if (dword_ea04c == 0) break;
  }
  dword_ea050 = 0;
  iVar2 = dword_ea06c;
  while( true ) {
    if (iVar2 == -1) {
      return;
    }
    iVar1 = *(int *)(dword_ea060 + 0xc + iVar2 * 0x10);
    if (dword_ea050 < iVar1) {
      dword_ea050 = iVar1;
    }
    if (dword_ea040 <= dword_ea050) break;
    iVar2 = *(int *)(dword_ea090 + iVar2 * 4);
  }
  return;
}


// ================================================================================================
// set_view_rect @ 0x6af52 [__watcall]
// ================================================================================================

void __watcall
set_view_rect(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  __CHK(0x14);
  dword_ea034 = param_1;
  dword_ea038 = unaff_EBX;
  dword_ea03c = unaff_EDX;
  dword_ea040 = unaff_ECX;
  dword_ea0c4 = unaff_ECX;
  dword_ea0c8 = unaff_EBX;
  dword_ea0cc = param_1;
  dword_ea0d0 = unaff_EDX;
  setclip(param_1,unaff_EBX,unaff_EDX,unaff_ECX);
  return;
}


// ================================================================================================
// set_camera_offset @ 0x6af97 [__watcall]
// ================================================================================================

void __watcall set_camera_offset(undefined4 param_1,undefined4 unaff_EDX)

{
  __CHK(4);
  dword_ea0b8 = param_1;
  dword_ea0bc = unaff_EDX;
  return;
}


// ================================================================================================
// zm_clip_view @ 0x6afad [__watcall]
// ================================================================================================

void __watcall zm_clip_view(void)

{
  __CHK(4);
  __CHK(0x24);
  setclip(dword_ea034,dword_ea038,dword_ea03c,dword_ea040);
  return;
}


// ================================================================================================
// zm_clip_current @ 0x6afbe [__watcall]
// ================================================================================================

void __watcall zm_clip_current(void)

{
  undefined4 *puVar1;
  
  __CHK(4);
  if ((((byte)dword_ea058 & 0x20) == 0) || (dword_ea05c == 0)) {
    puVar1 = &dword_ea034;
  }
  else {
    puVar1 = &dword_ea044;
  }
  __CHK(0x24);
  setclip(*puVar1,puVar1[1],puVar1[2],puVar1[3]);
  return;
}


// ================================================================================================
// begin_frame @ 0x6b008 [__watcall]
// ================================================================================================

void __watcall begin_frame(void)

{
  __CHK(0x2c);
  setscreen(dword_ea0ac);
  zm_swap_lists();
  if (((byte)dword_ea058 & 1) == 0) {
    dword_ea05c = 1;
    zm_close_list();
    zm_add_dirty_zones(dword_ea094,dword_ea08c);
  }
  else {
    dword_ea05c = 0;
  }
  zm_restore_background();
  dword_ea058._0_1_ = (byte)dword_ea058 & 0xfe;
  setclip(dword_ea034,dword_ea038,dword_ea03c,dword_ea040);
  return;
}


// ================================================================================================
// joystick_calibrate @ 0x6b093 [__cdecl]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void joystick_calibrate(uint param_1,byte param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  uint uVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  byte bVar10;
  undefined5 *puVar11;
  undefined auStack_358 [768];
  undefined auStack_58 [64];
  undefined4 local_18;
  undefined4 *local_14;
  uint uStack_10;
  
  bVar10 = 0;
  __CHK(0x368);
  dword_d2fd8 = 1;
  (*(code *)funcptr_d45b4)();
  if (param_3 == 0) {
    joystick1_default_center();
  }
  else {
    joystick2_default_center();
  }
  settextpos(0,0);
  iVar1 = joy_read();
  if ((iVar1 >> (param_2 & 0x1f) & 0x30U) == 0) {
    getfontstate(auStack_58);
    setfont(&unk_d45d8);
    setdefaultscreen();
    clearclip(0);
    memset(auStack_358,0,0x300);
    setpalette(0,0x100,auStack_358);
    uVar2 = loadshapes(aJoycal,0);
    local_18 = uVar2;
    uVar3 = locateshape(uVar2,&aScrn_c27d3);
    drawshape2_home(uVar3);
    if (param_3 == 0) {
      puVar11 = &aLeft;
    }
    else {
      puVar11 = &aRite;
    }
    local_14 = (undefined4 *)locateshape(uVar2,puVar11);
    drawshape_remap_home(local_14);
    iVar1 = locateshape(local_18,&aPal_c27e2);
    memcpy(auStack_358,(void *)(iVar1 + 0x10),0x300);
    puVar4 = (undefined4 *)locateshape(local_18,&aPuck);
    local_14 = puVar4;
    puVar5 = (undefined4 *)
             allocmem(aPuckBack,
                      ((int)puVar4[1] >> 0x10) * (*(int *)((int)puVar4 + 2) >> 0x10) + 0x11,0);
    puVar8 = puVar5 + (uint)bVar10 * -2 + 1;
    puVar6 = puVar4 + (uint)bVar10 * -2 + 1;
    *puVar5 = *puVar4;
    puVar9 = puVar8 + (uint)bVar10 * -2 + 1;
    puVar4 = puVar6 + (uint)bVar10 * -2 + 1;
    *puVar8 = *puVar6;
    *puVar9 = *puVar4;
    puVar9[(uint)bVar10 * -2 + 1] = puVar4[(uint)bVar10 * -2 + 1];
    *(undefined *)(puVar9 + (uint)bVar10 * -2 + 1 + (uint)bVar10 * -2 + 1) =
         *(undefined *)(puVar4 + (uint)bVar10 * -2 + 1 + (uint)bVar10 * -2 + 1);
    fade_palette(0,auStack_358,0x10);
    uVar7 = 0xffffffff;
    while( true ) {
      iVar1 = key_poll();
      if (iVar1 != 0) break;
      iVar1 = joy_read();
      uStack_10 = iVar1 >> (param_2 & 0x1f);
      if ((uStack_10 & 0x30) != 0) goto LAB_0006b2fa;
      uStack_10 = joystick_direction(uStack_10);
      if (uStack_10 != uVar7) {
        waitvbl_start();
        if (uVar7 != 0xffffffff) {
          drawshape2(puVar5,*(undefined4 *)(&unk_cd9d0 + uVar7 * 4),
                     *(undefined4 *)(&unk_cd9f4 + uVar7 * 4));
        }
        uVar7 = uStack_10;
        grabshape(puVar5,*(undefined4 *)(&unk_cd9d0 + uStack_10 * 4),
                  *(undefined4 *)(&unk_cd9f4 + uStack_10 * 4));
        drawshape_remap(local_14,*(undefined4 *)(&unk_cd9d0 + uVar7 * 4),
                        *(undefined4 *)(&unk_cd9f4 + uVar7 * 4));
        uVar7 = uStack_10;
        printstr_at(&asc_c27f5,0,0x14);
      }
    }
    _dword_d3040 = _dword_d3040 & ~param_1;
LAB_0006b2fa:
    freemem(puVar5);
    freemem(local_18);
    fade_palette(1,auStack_358,0x10);
    setfontstate(auStack_58);
  }
  else {
    _dword_d3040 = _dword_d3040 & ~param_1;
  }
  (*(code *)funcptr_d45b8)();
  dword_d2fd8 = 0;
  return;
}


// ================================================================================================
// calibrate_left_joystick @ 0x6b35c [__watcall]
// ================================================================================================

void __watcall calibrate_left_joystick(void)

{
  __CHK(0x14);
  joystick_calibrate(1,0,0,aLEFTJOYSTICK);
  return;
}


// ================================================================================================
// calibrate_right_joystick @ 0x6b37a [__watcall]
// ================================================================================================

void __watcall calibrate_right_joystick(void)

{
  __CHK(0x14);
  joystick_calibrate(2,8,1,aRIGHTJOYSTICK);
  return;
}


// ================================================================================================
// event_queue_pop @ 0x6b391 [__watcall]
// ================================================================================================

longlong __watcall event_queue_pop(undefined4 param_1,uint unaff_EDX)

{
  __CHK(0xc);
  if (dword_cda28 == 0) {
    return (ulonglong)unaff_EDX << 0x20;
  }
  dword_cda28 = dword_cda28 + -1;
  dword_cda2c = dword_cda2c + 1 & 0x1f;
  return CONCAT44(unaff_EDX,&event_queue + dword_cda2c * 0xd);
}


// ================================================================================================
// event_queue_reset @ 0x6b3d7 [__watcall]
// ================================================================================================

longlong __watcall event_queue_reset(undefined4 param_1,uint unaff_EDX)

{
  __CHK(8);
  dword_cda28 = 0;
  dword_cda2c = 0x1f;
  dword_cda30 = 0;
  dword_cda38 = 0;
  dword_cda3c = 0;
  dword_cda40 = 0;
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// ui_init @ 0x6b410 [__watcall]
// ================================================================================================

void __watcall
ui_init(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  int iVar1;
  
  __CHK(0x14);
  iVar1 = initmouse();
  if (iVar1 == 0) {
    input_devices = input_devices & 0xfe;
  }
  else {
    input_devices = input_devices | 1;
  }
  if (dword_cda1c == 0) {
    keyboard_install();
    dword_cda24 = 0;
    dword_cda20 = 0;
    dword_cda1c = 1;
    addtimer(ui_timer_callback,unaff_EDX,unaff_ECX,unaff_EBX);
    event_queue_reset();
    ui_poll_callback = ui_poll_events;
  }
  return;
}


// ================================================================================================
// ui_shutdown @ 0x6b47c [__watcall]
// ================================================================================================

void __watcall ui_shutdown(void)

{
  __CHK(0x18);
  if (dword_cda1c != 0) {
    dword_cda24 = 0;
    dword_cda20 = 0;
    removetimer(ui_timer_callback);
    dword_cda1c = 0;
  }
  return;
}


// ================================================================================================
// ui_poll_events @ 0x6b4bb [__watcall]
// ================================================================================================

undefined __watcall ui_poll_events(int *param_1,int *unaff_EDX,int *unaff_EBX)

{
  __CHK(0x1c);
  if (*param_1 == 1) {
    *unaff_EDX = *(int *)((int)param_1 + 5);
    *unaff_EBX = *(int *)((int)param_1 + 9);
    if (*unaff_EDX < 0) {
      *unaff_EDX = 0;
    }
    else if (0x275 < *unaff_EDX) {
      *unaff_EDX = 0x275;
    }
    if (*unaff_EBX < 0) {
      *unaff_EBX = 0;
    }
    else if (0x1d5 < *unaff_EBX) {
      *unaff_EBX = 0x1d5;
    }
  }
  else {
    if (0x1d < dword_ea29c) {
      dword_ea29c = 0x1d;
    }
    dword_cda20 = 8 << ((byte)((longlong)dword_ea29c / 5) & 0x1f);
    if ((*(byte *)((int)param_1 + 5) & 8) != 0) {
      *unaff_EDX = *unaff_EDX - dword_cda20;
    }
    if ((*(byte *)((int)param_1 + 5) & 4) != 0) {
      *unaff_EDX = *unaff_EDX + dword_cda20;
    }
    if ((*(byte *)((int)param_1 + 5) & 1) != 0) {
      *unaff_EBX = *unaff_EBX - dword_cda20;
    }
    if ((*(byte *)((int)param_1 + 5) & 2) != 0) {
      *unaff_EBX = *unaff_EBX + dword_cda20;
    }
    if (*unaff_EDX < 0) {
      *unaff_EDX = 0;
    }
    else if (0x275 < *unaff_EDX) {
      *unaff_EDX = 0x275;
    }
    if (*unaff_EBX < 0) {
      *unaff_EBX = 0;
    }
    else if (0x1d5 < *unaff_EBX) {
      *unaff_EBX = 0x1d5;
    }
    setmousepos(*unaff_EDX,*unaff_EBX);
    dword_d302c = *unaff_EDX;
    dword_d3030 = *unaff_EBX;
  }
  return *(undefined *)(param_1 + 1);
}


// ================================================================================================
// draw_menu_items @ 0x6b5e4 [__watcall]
// ================================================================================================

void __watcall
draw_menu_items(int param_1,int unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX,
               undefined4 param_5)

{
  int *piVar1;
  int iVar2;
  
  __CHK(0x28);
  settextpos(unaff_EBX,0xff,unaff_EDX,param_1,unaff_ECX);
  set_text_colors(unaff_EBX,0);
  for (iVar2 = 0; iVar2 < unaff_EDX; iVar2 = iVar2 + 1) {
    piVar1 = (int *)(iVar2 * 0x20 + param_1);
    draw_box(*piVar1,0,piVar1[2],piVar1[3],unaff_EBX,unaff_ECX,param_5);
    draw_item_text(*piVar1 + 3,2,piVar1[4]);
  }
  param_1 = unaff_EDX * 0x20 + param_1;
  draw_box(*(int *)(param_1 + -0x18) + 1,0,0x27f,*(undefined4 *)(param_1 + -0x14),unaff_EBX,
           unaff_ECX,param_5);
  return;
}


// ================================================================================================
// draw_menu @ 0x6b684 [__watcall]
// ================================================================================================

void __watcall
draw_menu(int *param_1,int param_2,int unaff_EBX,int unaff_ECX,undefined4 param_5,undefined4 param_6
         ,undefined4 param_7)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  
  __CHK(0x28);
  iVar4 = unaff_ECX;
  draw_box(*param_1 + unaff_EBX,param_1[1] + unaff_ECX,param_1[param_2 * 8 + -6] + unaff_EBX,
           param_1[param_2 * 8 + -5] + unaff_ECX,param_5,param_6,param_7);
  if ((param_1[5] == 0) && (param_1[6] == 0)) {
    settextpos(param_7,0xff);
    set_text_colors(param_7,0);
    iVar1 = param_1[4];
    draw_item_text_dim(*param_1 + 3 + unaff_EBX,param_1[1] + 2 + unaff_ECX,iVar1);
  }
  else {
    settextpos(param_5,0xff);
    set_text_colors(param_5,0);
    iVar1 = param_1[4];
    draw_item_text(*param_1 + 3 + unaff_EBX,param_1[1] + 2 + iVar4,iVar1);
  }
  for (iVar3 = 1; iVar3 < param_2; iVar3 = iVar3 + 1) {
    piVar2 = param_1 + iVar3 * 8;
    if ((piVar2[5] == 0) && (piVar2[6] == 0)) {
      settextpos(param_7,0xff);
      set_text_colors(param_7,0,iVar1);
      iVar1 = piVar2[4];
      draw_item_text_dim(*piVar2 + 3 + unaff_EBX,piVar2[1] + 1 + iVar4);
    }
    else {
      settextpos(param_5,0xff);
      set_text_colors(param_5,0);
      iVar1 = param_1[iVar3 * 8 + 4];
      draw_item_text(param_1[iVar3 * 8] + 3 + unaff_EBX,param_1[iVar3 * 8 + 1] + 1 + iVar4,iVar1);
    }
  }
  return;
}


// ================================================================================================
// draw_box @ 0x6b7fc [__watcall]
// ================================================================================================

void __watcall
draw_box(int param_1,int param_2,int unaff_EBX,int unaff_ECX,undefined4 param_5,undefined4 param_6,
        undefined4 param_7)

{
  __CHK(0x28);
  fillrect(param_1,param_2,(unaff_EBX - param_1) + 1,(unaff_ECX - param_2) + 1,param_6,unaff_EBX);
  drawline(param_1,param_2,unaff_EBX + -1,param_2,param_5);
  drawline(param_1,param_2,param_1,unaff_ECX + -1,param_5);
  drawline(unaff_EBX,param_2 + 1,unaff_EBX,unaff_ECX,param_7);
  drawline(param_1 + 1,unaff_ECX,unaff_EBX,unaff_ECX,param_7);
  return;
}


// ================================================================================================
// draw_item_text @ 0x6b88e [__watcall]
// ================================================================================================

void __watcall draw_item_text(undefined4 param_1,undefined4 unaff_EDX,int unaff_EBX)

{
  int iVar1;
  char acStackY_58 [80];
  
  __CHK(0x5c);
  for (iVar1 = 0; (*(char *)(unaff_EBX + iVar1) != '\0' && (iVar1 < 0x4f)); iVar1 = iVar1 + 1) {
    acStackY_58[iVar1] = *(char *)(unaff_EBX + iVar1);
  }
  acStackY_58[iVar1] = *(char *)(unaff_EBX + iVar1);
  print_text_at(param_1,unaff_EDX,acStackY_58);
  return;
}


// ================================================================================================
// draw_item_text_dim @ 0x6b8cb [__watcall]
// ================================================================================================

void __watcall draw_item_text_dim(undefined4 param_1,undefined4 unaff_EDX,int unaff_EBX)

{
  int iVar1;
  char acStack_58 [80];
  
  __CHK(0x68);
  for (iVar1 = 0; (*(char *)(unaff_EBX + iVar1) != '\0' && (iVar1 < 0x4f)); iVar1 = iVar1 + 1) {
    acStack_58[iVar1] = *(char *)(unaff_EBX + iVar1);
  }
  acStack_58[iVar1] = *(char *)(unaff_EBX + iVar1);
  printstr_at(acStack_58,param_1,unaff_EDX);
  return;
}


// ================================================================================================
// printstr2_copy_at @ 0x6b910 [__watcall]
// ================================================================================================

void __watcall printstr2_copy_at(undefined4 param_1,undefined4 unaff_EDX,int unaff_EBX)

{
  int iVar1;
  char acStack_58 [80];
  
  __CHK(0x68);
  for (iVar1 = 0; (*(char *)(unaff_EBX + iVar1) != '\0' && (iVar1 < 0x4f)); iVar1 = iVar1 + 1) {
    acStack_58[iVar1] = *(char *)(unaff_EBX + iVar1);
  }
  acStack_58[iVar1] = *(char *)(unaff_EBX + iVar1);
  printstr2_at(acStack_58,param_1,unaff_EDX);
  return;
}


// ================================================================================================
// highlight_menu_item @ 0x6b94e [__watcall]
// ================================================================================================

void __watcall
highlight_menu_item(int *param_1,int unaff_EDX,int unaff_EBX,undefined4 unaff_ECX,undefined4 param_5
                   )

{
  int iVar1;
  int iVar2;
  
  __CHK(0x28);
  if ((param_1[5] != 0) || (param_1[6] != 0)) {
    iVar1 = param_1[1];
    unaff_EDX = unaff_EDX + *param_1 + 1;
    iVar2 = unaff_EBX + iVar1 + (uint)(iVar1 == 0);
    fillrect(unaff_EDX,iVar2,(param_1[2] - *param_1) + -2,
             (param_1[3] - param_1[1]) - (uint)(iVar1 == 0),param_5);
    settextpos(unaff_ECX,0xff);
    set_text_colors(unaff_ECX,0);
    draw_item_text(unaff_EDX + 2,iVar2 + 1,param_1[4]);
  }
  return;
}


// ================================================================================================
// unhighlight_menu_item @ 0x6b9eb [__watcall]
// ================================================================================================

void __watcall
unhighlight_menu_item
          (int *param_1,int unaff_EDX,int unaff_EBX,undefined4 unaff_ECX,undefined4 param_5,
          undefined4 param_6)

{
  int iVar1;
  int iVar2;
  
  __CHK(0x28);
  if ((param_1[5] != 0) || (param_1[6] != 0)) {
    iVar1 = param_1[1];
    unaff_EDX = unaff_EDX + *param_1 + 1;
    iVar2 = unaff_EBX + iVar1 + (uint)(iVar1 == 0);
    fillrect(unaff_EDX,iVar2,(param_1[2] - *param_1) + -2,
             (param_1[3] - param_1[1]) - (uint)(iVar1 == 0),param_6);
    settextpos(unaff_ECX,0xff);
    set_text_colors(unaff_ECX,0);
    draw_item_text(unaff_EDX + 2,iVar2 + 1,param_1[4]);
  }
  return;
}


// ================================================================================================
// hit_test_menus @ 0x6ba4d [__watcall]
// ================================================================================================

undefined4 __watcall
hit_test_menus(int param_1,int param_2,int param_3,int unaff_ECX,int param_5,int param_6,
              int *param_7,int *param_8)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  
  __CHK(0x14);
  do {
    if (unaff_ECX < 0) {
      return 0;
    }
    if (*(int *)(unaff_ECX * 4 + param_3) != 0) {
      for (iVar3 = 0; iVar3 < *(int *)(param_5 + unaff_ECX * 4); iVar3 = iVar3 + 1) {
        piVar1 = (int *)(*(int *)(unaff_ECX * 4 + param_3) + iVar3 * 0x20);
        piVar2 = (int *)(unaff_ECX * 8 + param_6);
        if ((((*piVar2 + *piVar1 <= param_1 + 4) && (param_1 + 4 <= *piVar2 + piVar1[2])) &&
            (piVar2[1] + piVar1[1] <= param_2)) && (param_2 <= piVar2[1] + piVar1[3])) {
          *param_7 = unaff_ECX;
          *param_8 = iVar3;
          return 1;
        }
      }
    }
    unaff_ECX = unaff_ECX + -1;
  } while( true );
}


// ================================================================================================
// ui_timer_callback @ 0x6baeb [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall ui_timer_callback(void)

{
  int iVar1;
  
  iVar1 = 0;
  dword_cda34 = dword_cda34 + -1;
  if (dword_cda34 == 0) {
    dword_cda34 = 5;
    if ((input_devices & 1) != 0) {
      iVar1 = ui_poll_mouse(&dword_ea2a0);
    }
    if (iVar1 == 0) {
      if (((input_devices & 2) != 0) || ((input_devices & 4) != 0)) {
        iVar1 = ui_poll_joystick(&dword_ea2a0);
      }
    }
    if ((iVar1 == 0) && ((input_devices & 8) != 0)) {
      iVar1 = ui_poll_keyboard(&dword_ea2a0);
    }
    if (iVar1 == 0) {
      dword_ea298 = iVar1;
      dword_ea29c = iVar1;
      return;
    }
    if (dword_ea2a0 == 1) {
      dword_ea298 = 0;
      dword_ea29c = 0;
    }
    else if ((_dword_ea2a5 & 0xff) == dword_ea298) {
      dword_ea29c = dword_ea29c + 1;
    }
    else {
      dword_ea29c = 0;
      dword_ea298 = _dword_ea2a5 & 0xff;
    }
    if (dword_cda28 != 0x20) {
      iVar1 = dword_cda30 * 0xd;
      if (dword_ea2a0 == 1) {
        *(undefined4 *)(&event_queue + iVar1) = 1;
        (&unk_ea0fc)[iVar1] = byte_ea2a4;
        *(uint *)(&unk_ea0fd + iVar1) = _dword_ea2a5;
        *(undefined4 *)(&unk_ea101 + iVar1) = dword_ea2a9;
      }
      else {
        *(int *)(&event_queue + iVar1) = dword_ea2a0;
        (&unk_ea0fc)[iVar1] = byte_ea2a4;
        (&unk_ea0fd)[iVar1] = dword_ea2a5;
      }
      dword_cda30 = dword_cda30 + 1 & 0x1f;
      dword_cda28 = dword_cda28 + 1;
    }
  }
  return;
}


// ================================================================================================
// ui_poll_mouse @ 0x6bc30 [__watcall]
// ================================================================================================

undefined8 __watcall ui_poll_mouse(undefined4 *param_1,undefined4 unaff_EDX)

{
  char cVar1;
  
  (*(code *)mouse_update_callback)();
  if ((dword_cda44 == dword_d3034) && (dword_cda48 == dword_d302c)) {
    if (dword_cda4c == dword_d3030) {
      return CONCAT44(unaff_EDX,dword_cda4c ^ dword_d3030);
    }
  }
  dword_cda48 = dword_d302c;
  dword_cda4c = dword_d3030;
  *param_1 = 1;
  if ((dword_cda44 == 0) || (dword_d3034 != 0)) {
    cVar1 = '\0';
  }
  else {
    cVar1 = '\x02';
  }
  *(char *)(param_1 + 1) = cVar1 + (dword_d3034 != 0);
  *(int *)((int)param_1 + 5) = dword_d302c;
  *(uint *)((int)param_1 + 9) = dword_d3030;
  dword_cda44 = dword_d3034;
  return CONCAT44(unaff_EDX,1);
}


// ================================================================================================
// ui_poll_joystick @ 0x6bcda [__watcall]
// ================================================================================================

undefined8 __watcall ui_poll_joystick(undefined4 *param_1,undefined4 unaff_EDX)

{
  uint uVar1;
  undefined4 uVar2;
  bool bVar3;
  
  if (byte_d416a == '\0') {
    uVar2 = 0;
  }
  else {
    joy_detect();
    uVar1 = joy_read();
    if ((input_devices & 2) == 0) {
      uVar1 = (int)uVar1 >> 8;
    }
    if (((uVar1 & 0xff) != 0) || (uVar2 = 0, dword_cda3c != 0)) {
      *param_1 = 2;
      bVar3 = (uVar1 & 0x30) != 0;
      *(bool *)(param_1 + 1) = bVar3;
      if ((dword_cda3c == 0) || ((uVar1 & 0x30) != 0)) {
        if ((uVar1 & 0x30) != 0) {
          dword_cda3c = 1;
        }
      }
      else {
        *(char *)(param_1 + 1) = bVar3 + '\x02';
        dword_cda3c = 0;
      }
      *(byte *)((int)param_1 + 5) = (byte)uVar1 & 0xf;
      uVar2 = 1;
    }
  }
  return CONCAT44(unaff_EDX,uVar2);
}


// ================================================================================================
// ui_poll_keyboard @ 0x6bd69 [__watcall]
// ================================================================================================

longlong __watcall ui_poll_keyboard(undefined4 *param_1,uint unaff_EDX)

{
  int iVar1;
  
  *param_1 = 3;
  *(undefined *)((int)param_1 + 5) = 0;
  *(undefined *)(param_1 + 1) = 0;
  key_down(0x1d);
  iVar1 = key_down(0x47);
  if (iVar1 != 0) {
    *(byte *)((int)param_1 + 5) = *(byte *)((int)param_1 + 5) | 9;
  }
  iVar1 = key_down(0x49);
  if (iVar1 != 0) {
    *(byte *)((int)param_1 + 5) = *(byte *)((int)param_1 + 5) | 5;
  }
  iVar1 = key_down(0x4f);
  if (iVar1 != 0) {
    *(byte *)((int)param_1 + 5) = *(byte *)((int)param_1 + 5) | 10;
  }
  iVar1 = key_down(0x51);
  if (iVar1 != 0) {
    *(byte *)((int)param_1 + 5) = *(byte *)((int)param_1 + 5) | 6;
  }
  iVar1 = key_down(0x48);
  if (iVar1 != 0) {
    *(byte *)((int)param_1 + 5) = *(byte *)((int)param_1 + 5) | 1;
  }
  iVar1 = key_down(0x4d);
  if (iVar1 != 0) {
    *(byte *)((int)param_1 + 5) = *(byte *)((int)param_1 + 5) | 4;
  }
  iVar1 = key_down(0x50);
  if (iVar1 != 0) {
    *(byte *)((int)param_1 + 5) = *(byte *)((int)param_1 + 5) | 2;
  }
  iVar1 = key_down(0x4b);
  if (iVar1 != 0) {
    *(byte *)((int)param_1 + 5) = *(byte *)((int)param_1 + 5) | 8;
  }
  iVar1 = key_down(0x39);
  if (iVar1 != 0) {
    *(byte *)(param_1 + 1) = *(byte *)(param_1 + 1) | 8;
  }
  iVar1 = key_down(1);
  if (iVar1 != 0) {
    *(byte *)(param_1 + 1) = *(byte *)(param_1 + 1) | 4;
  }
  iVar1 = key_down(0x1c);
  if (iVar1 == 0) {
    if (dword_cda40 != 0) {
      *(byte *)(param_1 + 1) = *(byte *)(param_1 + 1) | 2;
      dword_cda40 = 0;
    }
  }
  else {
    *(byte *)(param_1 + 1) = *(byte *)(param_1 + 1) | 1;
    dword_cda40 = 1;
  }
  iVar1 = getkey();
  if (iVar1 != 0) {
    *(byte *)(param_1 + 1) = *(byte *)(param_1 + 1) | 0x20;
  }
  if ((*(char *)(param_1 + 1) == '\0') && (*(char *)((int)param_1 + 5) == '\0')) {
    return (ulonglong)unaff_EDX << 0x20;
  }
  return CONCAT44(unaff_EDX,1);
}


// ================================================================================================
// menu_central_registry @ 0x6be95 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 __watcall menu_central_registry(undefined4 param_1,undefined4 unaff_EDX)

{
  __CHK(0x1c);
  if (sound_enabled != '\0') {
    releasememblock(*(undefined4 *)(dword_ed7b0 + 0x3b60));
  }
  _dword_c7290 = 0xa0;
  dword_c71e0 = 0;
  database_screen();
  if (dword_d07ae != 0) {
    freemem(dword_d07ae);
    dword_d07ae = 0;
  }
  if (dword_d07aa != 0) {
    freemem(dword_d07aa);
    dword_d07aa = 0;
  }
  if (sound_enabled != '\0') {
    dword_ccc94 = 0x20;
    speech_clips_init(dword_c4cfc);
    dword_ccc94 = 0;
  }
  return CONCAT44(unaff_EDX,2);
}


// ================================================================================================
// database_build_list @ 0x6bf4a [__watcall]
// ================================================================================================

void __watcall database_build_list(void)

{
  int iVar1;
  uint uVar2;
  char *pcVar3;
  int iVar4;
  int iVar5;
  
  __CHK(0x20);
  uVar2 = dword_d07df / 0x34;
  iVar4 = 0;
  iVar5 = 0;
  while ((iVar5 < (int)uVar2 && (iVar4 < dword_d07b2))) {
    pcVar3 = (char *)(dword_d07c7 + iVar5 * 0x34);
    if (*pcVar3 == -1) {
      iVar1 = iVar4 * 0x1b;
      *(char *)(dword_d07aa + 2 + iVar1) = (char)iVar4;
      *(char *)(iVar1 + dword_d07aa) = pcVar3[2];
      *(char *)(iVar1 + 1 + dword_d07aa) = pcVar3[1];
      *(undefined *)(dword_d07aa + 3 + iVar1) = 3;
      *(int *)(dword_d07aa + 4 + iVar1) = iVar5 * 0x34;
      *(char *)(dword_d07aa + 8 + iVar1) = pcVar3[3];
      *(undefined *)(dword_d07aa + 9 + iVar1) = byte_c8164;
      *(undefined *)(dword_d07aa + 10 + iVar1) = asc_c8111;
      *(undefined *)(dword_d07aa + 0xb + iVar1) = 0;
      strcat((char *)(iVar1 + dword_d07aa + 8),pcVar3 + 0x13);
      iVar4 = iVar4 + 1;
    }
    iVar5 = iVar5 + 1;
  }
  return;
}


// ================================================================================================
// dbedit_build_team_list @ 0x6c043 [__watcall]
// ================================================================================================

void __watcall dbedit_build_team_list(undefined4 param_1,int unaff_EDX,int *unaff_EBX)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  undefined *puVar4;
  int iVar5;
  undefined8 uVar6;
  
  __CHK(0x14);
  iVar5 = 0;
  do {
    *(char *)(iVar5 * 0x1b + 2 + unaff_EDX) = (char)iVar5;
    iVar5 = iVar5 + 1;
  } while (iVar5 < 0x1c);
  iVar5 = dbedit_teams_record(param_1);
  *unaff_EBX = iVar5;
  iVar5 = 0;
  do {
    iVar2 = *(int *)(*unaff_EBX + 0x4c + iVar5 * 4);
    puVar4 = (undefined *)(iVar5 * 0x1b + unaff_EDX);
    if (iVar2 == -1) {
      *puVar4 = 0;
      puVar4[1] = 100;
      puVar4[2] = 0;
      puVar4[3] = 0;
    }
    else {
      uVar6 = dbedit_key_ptr(iVar2);
      puVar4 = (undefined *)((ulonglong)uVar6 >> 0x20);
      iVar3 = (int)uVar6;
      *puVar4 = *(undefined *)(iVar3 + 2);
      puVar4[1] = *(undefined *)(iVar3 + 1);
      puVar4[3] = 3;
      *(int *)(puVar4 + 4) = iVar2;
      puVar4[8] = *(undefined *)(iVar3 + 3);
      puVar4[9] = byte_c8164;
      puVar4[10] = asc_c8111;
      puVar4[0xb] = 0;
      strcat(puVar4 + 8,(char *)(iVar3 + 0x13));
    }
    iVar5 = iVar5 + 1;
  } while (iVar5 < 0x19);
  iVar5 = 0;
  do {
    iVar2 = *(int *)(*unaff_EBX + 0xb0 + iVar5 * 4);
    puVar4 = (undefined *)((iVar5 + 0x19) * 0x1b + unaff_EDX);
    if (iVar2 == -1) {
      *puVar4 = 0;
      puVar4[1] = 100;
      puVar4[2] = 0;
      puVar4[3] = 0;
    }
    else {
      uVar6 = dbedit_key_ptr(iVar2);
      puVar4 = (undefined *)((ulonglong)uVar6 >> 0x20);
      iVar3 = (int)uVar6;
      *puVar4 = *(undefined *)(iVar3 + 2);
      puVar4[1] = *(undefined *)(iVar3 + 1);
      puVar4[3] = 3;
      *(int *)(puVar4 + 4) = iVar2;
      puVar4[8] = *(undefined *)(iVar3 + 3);
      puVar4[9] = byte_c8164;
      puVar4[10] = asc_c8111;
      puVar4[0xb] = 0;
      strcat(puVar4 + 8,(char *)(iVar3 + 0x13));
    }
    iVar5 = iVar5 + 1;
  } while (iVar5 < 3);
  iVar5 = 0;
  do {
    bVar1 = *(byte *)(*unaff_EBX + iVar5 + 0xe4);
    if (bVar1 != 100) {
      *(undefined *)((uint)bVar1 * 0x1b + 3 + unaff_EDX) = 2;
    }
    iVar5 = iVar5 + 1;
  } while (iVar5 < 8);
  return;
}


// ================================================================================================
// dbedit_load_databases @ 0x6c19b [__watcall]
// ================================================================================================

void __watcall dbedit_load_databases(undefined4 param_1)

{
  undefined auStack_30 [32];
  
  __CHK(0x3c);
  dbedit_free_databases();
  make_path(auStack_30,0,off_c80eb,param_1);
  dword_d07bb = loadfile(auStack_30,0x20);
  dword_d07d3 = filesize(auStack_30);
  make_path(auStack_30,0,off_c80db,param_1);
  dword_d07bf = loadfile(auStack_30,0x20);
  dword_d07d7 = filesize(auStack_30);
  make_path(auStack_30,0,off_c80e3,param_1);
  dword_d07c3 = loadfile(auStack_30,0x20);
  dword_d07db = filesize(auStack_30);
  make_path(auStack_30,0,off_c80d7,param_1);
  dword_d07c7 = loadfile(auStack_30,0x20);
  dword_d07df = filesize(auStack_30);
  make_path(auStack_30,0,off_c80e7,param_1);
  dword_d07cb = loadfile(auStack_30,0x20);
  dword_d07e3 = filesize(auStack_30);
  make_path(auStack_30,0,off_c80df,param_1);
  dword_d07cf = loadfile(auStack_30,0x20);
  dword_d07e7 = filesize(auStack_30);
  return;
}


// ================================================================================================
// menu_save_to_game @ 0x6c2f9 [__watcall]
// ================================================================================================

void __watcall menu_save_to_game(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX)

{
  int iVar1;
  undefined4 uVar2;
  int extraout_EDX;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined uStack_14;
  
  __CHK(0x3c);
  uStack_20 = 0;
  uStack_1c = 0;
  uStack_18 = 0;
  uStack_14 = 0;
  dword_ebc74 = aSaveAsGameDatabases;
  iVar1 = message_dialog(0xffffffff,0xffffffff,&dword_ebc74,1,&unk_d0c24,2,unaff_EDX,unaff_EBX,
                         0xffffffff);
  if (iVar1 == 1) {
    uVar2 = dbedit_validate_lines(unaff_EDX,unaff_EBX);
    player_ratings_card(uVar2,uVar2);
    if (extraout_EDX != 0) {
      unk_ec7c0._0_1_ = aCurrent[0];
      unk_ec7c0._1_1_ = aCurrent[1];
      unk_ec7c0._2_1_ = aCurrent[2];
      unk_ec7c0._3_1_ = aCurrent[3];
      DAT_000ec7c4._0_1_ = aCurrent[4];
      DAT_000ec7c4._1_1_ = aCurrent[5];
      DAT_000ec7c4._2_1_ = aCurrent[6];
      DAT_000ec7c4._3_1_ = aCurrent[7];
      dword_ebc74 = aSavingDatabases;
      message_dialog(0xffffffff,0xffffffff,&dword_ebc74,1,0,0,unaff_EDX,unaff_EBX,0);
      database_disk_check(&uStack_20,&aDB);
      restore_dialog_background();
      player_ratings_card();
    }
  }
  return;
}


// ================================================================================================
// new_database_dialog @ 0x6c3bb [__watcall]
// ================================================================================================

void __watcall new_database_dialog(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX)

{
  bool bVar1;
  int iVar2;
  __mode_t extraout_EDX;
  __mode_t __mode;
  undefined8 uVar3;
  undefined local_60 [44];
  char acStack_34 [16];
  char acStack_24 [16];
  int iStack_14;
  
  __CHK(0x78);
  bVar1 = false;
  iStack_14 = 0;
  iVar2 = text_entry_dialog(aEnterANewDatabaseName,acStack_24,8,0x30,0,0,0,0,5);
  if ((acStack_24[0] != '\0') && (iVar2 != 0x1b)) {
    strcpy(acStack_34,acStack_24);
    strcat(acStack_24,(char *)&aDBX);
    uVar3 = _dos_findfirst(acStack_24,0x10,local_60);
    __mode = (__mode_t)((ulonglong)uVar3 >> 0x20);
    if ((int)uVar3 == 0) {
      uVar3 = message_dialog(0xffffffff,0xffffffff,&off_cfb1c,2,&unk_c7733,2,unaff_EDX,unaff_EBX,
                             0xffffffff);
      __mode = (__mode_t)((ulonglong)uVar3 >> 0x20);
      if ((int)uVar3 == 1) {
        delete_directory(acStack_24);
        __mode = extraout_EDX;
      }
      else {
        bVar1 = true;
      }
    }
    if ((!bVar1) && (iStack_14 = mkdir(acStack_24,__mode), iStack_14 == 0)) {
      strcpy((char *)&unk_ec7c0,acStack_34);
      database_disk_check(acStack_24,&aDB);
      player_ratings_card();
    }
  }
  return;
}


// ================================================================================================
// database_disk_check @ 0x6c4ba [__watcall]
// ================================================================================================

void __watcall database_disk_check(char *param_1,undefined4 unaff_EDX)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined auStack_b4 [26];
  int iStack_9a;
  undefined auStack_88 [32];
  uint local_68 [8];
  int local_48 [6];
  undefined4 uStack_30;
  undefined local_28 [2];
  ushort local_26;
  ushort local_24;
  ushort uStack_22;
  undefined4 local_20;
  undefined4 local_1c;
  
  __CHK(0xcc);
  iVar1 = _dos_getdiskfree(0,local_28);
  if (iVar1 != 0) {
    fatalerror(aErrorGettingDiskSpaceFre_c2854);
  }
  iVar2 = (uint)local_24 * (uint)uStack_22;
  make_path(auStack_88,param_1,off_c80eb,unaff_EDX);
  iVar1 = _dos_findfirst(auStack_88,0,auStack_b4);
  if (iVar1 == 0) {
    local_68[0] = iStack_9a + 0x3ffU >> 10;
  }
  else {
    local_68[0] = 0;
  }
  make_path(auStack_88,param_1,off_c80db,unaff_EDX);
  iVar1 = _dos_findfirst(auStack_88,0);
  if (iVar1 == 0) {
    local_68[1] = iStack_9a + 0x3ffU >> 10;
  }
  else {
    local_68[1] = 0;
  }
  make_path(auStack_88,param_1,off_c80e3);
  iVar1 = _dos_findfirst(auStack_88,0,auStack_b4);
  if (iVar1 == 0) {
    local_68[2] = iStack_9a + 0x3ffU >> 10;
  }
  else {
    local_68[2] = 0;
  }
  make_path(auStack_88,param_1,off_c80d7,unaff_EDX);
  iVar1 = _dos_findfirst(auStack_88,0,auStack_b4);
  if (iVar1 == 0) {
    local_68[3] = iStack_9a + 0x3ffU >> 10;
  }
  else {
    local_68[3] = 0;
  }
  make_path(auStack_88,param_1,off_c80e7,unaff_EDX);
  iVar1 = _dos_findfirst(auStack_88,0,auStack_b4);
  if (iVar1 == 0) {
    local_68[4] = iStack_9a + 0x3ffU >> 10;
  }
  else {
    local_68[4] = 0;
  }
  make_path(auStack_88,param_1,off_c80df,unaff_EDX);
  iVar1 = _dos_findfirst(auStack_88,0);
  if (iVar1 == 0) {
    local_68[5] = iStack_9a + 0x3ffU >> 10;
  }
  else {
    local_68[5] = 0;
  }
  iVar1 = dword_d07d3 + 0x3ff >> 0x1f;
  local_48[0] = (int)((dword_d07d3 + 0x3ff + iVar1 * -0x400) - (uint)(iVar1 << 9 < 0)) >> 10;
  iVar1 = dword_d07d7 + 0x3ff >> 0x1f;
  local_48[1] = (int)((dword_d07d7 + 0x3ff + iVar1 * -0x400) - (uint)(iVar1 << 9 < 0)) >> 10;
  iVar1 = dword_d07db + 0x3ff >> 0x1f;
  local_48[2] = (int)((dword_d07db + 0x3ff + iVar1 * -0x400) - (uint)(iVar1 << 9 < 0)) >> 10;
  iVar1 = dword_d07df + 0x3ff >> 0x1f;
  local_48[3] = (int)((dword_d07df + 0x3ff + iVar1 * -0x400) - (uint)(iVar1 << 9 < 0)) >> 10;
  iVar1 = dword_d07e3 + 0x3ff >> 0x1f;
  local_48[4] = (int)((dword_d07e3 + 0x3ff + iVar1 * -0x400) - (uint)(iVar1 << 9 < 0)) >> 10;
  iVar1 = dword_d07e7 + 0x3ff >> 0x1f;
  local_48[5] = (int)((dword_d07e7 + 0x3ff + iVar1 * -0x400) - (uint)(iVar1 << 9 < 0)) >> 10;
  iVar1 = 0;
  uStack_30 = 0;
  iVar3 = 0;
  do {
    iVar3 = (iVar3 + (local_48[iVar1] + iVar2 + -1) / iVar2) -
            (int)(local_68[iVar1] + iVar2 + -1) / iVar2;
    iVar1 = iVar1 + 1;
  } while (iVar1 < 6);
  if ((int)(uint)local_26 < iVar3) {
    local_1c = 0x140;
    local_20 = 0xf0;
    setmousepos(0x140,0xf0);
    iVar1 = 0;
    do {
      iVar3 = iVar3 + (local_48[iVar1] + iVar2 + -1) / iVar2;
      iVar1 = iVar1 + 1;
    } while (iVar1 < 6);
    iVar1 = iVar3 * iVar2 >> 0x1f;
    sprintf(aXXXKbytesOfFreeDiskSpace,a3dKbytesOfFreeDiskSpace,
            (int)((iVar3 * iVar2 + iVar1 * -0x400) - (uint)(iVar1 << 9 < 0)) >> 10);
    message_dialog(0xffffffff,0xffffffff,&off_cfb8a,3,0,0,&local_1c,&local_20,800);
    if (*param_1 != '\0') {
      rmdir(param_1);
    }
  }
  else {
    make_path(auStack_88,param_1,off_c80eb,unaff_EDX);
    savefile(auStack_88,dword_d07bb,dword_d07d3);
    make_path(auStack_88,param_1,off_c80db,unaff_EDX);
    savefile(auStack_88,dword_d07bf,dword_d07d7);
    make_path(auStack_88,param_1,off_c80e3,unaff_EDX);
    savefile(auStack_88,dword_d07c3,dword_d07db);
    make_path(auStack_88,param_1,off_c80d7,unaff_EDX);
    savefile(auStack_88,dword_d07c7,dword_d07df);
    make_path(auStack_88,param_1,off_c80e7,unaff_EDX);
    savefile(auStack_88,dword_d07cb,dword_d07e3);
    make_path(auStack_88,param_1,off_c80df,unaff_EDX);
    savefile(auStack_88,dword_d07cf,dword_d07e7);
    dword_ebc68 = 0;
  }
  return;
}


// ================================================================================================
// dbedit_save_databases @ 0x6c96c [__watcall]
// ================================================================================================

void __watcall dbedit_save_databases(undefined4 param_1)

{
  undefined auStack_38 [32];
  
  __CHK(0x48);
  make_path(auStack_38,0,off_c80eb,param_1);
  savefile(auStack_38,dword_d07bb,dword_d07d3);
  make_path(auStack_38,0,off_c80db,param_1);
  savefile(auStack_38,dword_d07bf,dword_d07d7);
  make_path(auStack_38,0,off_c80e3,param_1);
  savefile(auStack_38,dword_d07c3,dword_d07db);
  make_path(auStack_38,0,off_c80d7,param_1);
  savefile(auStack_38,dword_d07c7,dword_d07df);
  make_path(auStack_38,0,off_c80e7,param_1);
  savefile(auStack_38,dword_d07cb,dword_d07e3);
  make_path(auStack_38,0,off_c80df,param_1);
  savefile(auStack_38,dword_d07cf,dword_d07e7);
  return;
}


// ================================================================================================
// dbedit_free_databases @ 0x6ca8f [__watcall]
// ================================================================================================

void __watcall dbedit_free_databases(void)

{
  __CHK(0x20);
  if (dword_d07cf != 0) {
    freemem(dword_d07cf);
    dword_d07cf = 0;
    dword_d07e7 = 0;
  }
  if (dword_d07cb != 0) {
    freemem(dword_d07cb);
    dword_d07cb = 0;
    dword_d07e3 = 0;
  }
  if (dword_d07c7 != 0) {
    freemem(dword_d07c7);
    dword_d07c7 = 0;
    dword_d07df = 0;
  }
  if (dword_d07c3 != 0) {
    freemem(dword_d07c3);
    dword_d07c3 = 0;
    dword_d07db = 0;
  }
  if (dword_d07bf != 0) {
    freemem(dword_d07bf);
    dword_d07bf = 0;
    dword_d07d7 = 0;
  }
  if (dword_d07bb != 0) {
    freemem(dword_d07bb);
    dword_d07bb = 0;
    dword_d07d3 = 0;
  }
  return;
}


// ================================================================================================
// dbedit_carteams_record @ 0x6cb6b [__watcall]
// ================================================================================================

undefined8 __watcall dbedit_carteams_record(int param_1,undefined4 unaff_EDX)

{
  __CHK(8);
  return CONCAT44(unaff_EDX,dword_d07c3 + param_1 * 0x4c);
}


// ================================================================================================
// dbedit_teams_record @ 0x6cb90 [__watcall]
// ================================================================================================

undefined8 __watcall dbedit_teams_record(int param_1,undefined4 unaff_EDX)

{
  __CHK(8);
  return CONCAT44(unaff_EDX,dword_d07cb + param_1 * 0x2e8);
}


// ================================================================================================
// dbedit_key_ptr @ 0x6cbb7 [__watcall]
// ================================================================================================

undefined8 __watcall dbedit_key_ptr(int param_1,undefined4 unaff_EDX)

{
  __CHK(8);
  return CONCAT44(unaff_EDX,param_1 + dword_d07c7);
}


// ================================================================================================
// dbedit_season_ptr @ 0x6cbcc [__watcall]
// ================================================================================================

undefined8 __watcall dbedit_season_ptr(int param_1,undefined4 unaff_EDX)

{
  __CHK(8);
  return CONCAT44(unaff_EDX,param_1 + dword_d07bb);
}


// ================================================================================================
// dbedit_season_ptr_b @ 0x6cbe1 [__watcall]
// ================================================================================================

undefined8 __watcall dbedit_season_ptr_b(int param_1,undefined4 unaff_EDX)

{
  __CHK(8);
  return CONCAT44(unaff_EDX,param_1 + dword_d07bb);
}


// ================================================================================================
// dbedit_career_ptr @ 0x6cbe8 [__watcall]
// ================================================================================================

undefined8 __watcall dbedit_career_ptr(int param_1,undefined4 unaff_EDX)

{
  __CHK(8);
  return CONCAT44(unaff_EDX,param_1 + dword_d07bf);
}


// ================================================================================================
// dbedit_career_ptr_b @ 0x6cbfd [__watcall]
// ================================================================================================

undefined8 __watcall dbedit_career_ptr_b(int param_1,undefined4 unaff_EDX)

{
  __CHK(8);
  return CONCAT44(unaff_EDX,param_1 + dword_d07bf);
}


// ================================================================================================
// dbedit_att_ptr @ 0x6cc04 [__watcall]
// ================================================================================================

undefined8 __watcall dbedit_att_ptr(int param_1,undefined4 unaff_EDX)

{
  __CHK(8);
  return CONCAT44(unaff_EDX,param_1 + dword_d07cf);
}


// ================================================================================================
// dbedit_att_ptr_b @ 0x6cc19 [__watcall]
// ================================================================================================

undefined8 __watcall dbedit_att_ptr_b(int param_1,undefined4 unaff_EDX)

{
  __CHK(8);
  return CONCAT44(unaff_EDX,param_1 + dword_d07cf);
}


// ================================================================================================
// database_screen @ 0x6cc20 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall database_screen(void)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  byte bVar7;
  undefined auStack_6c [64];
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 uStack_1c;
  
  bVar7 = 0;
  __CHK(0x7c);
  local_2c = dword_c71d0;
  local_20 = dword_c71d4;
  uStack_1c = dword_c71cc;
  local_24 = dword_c71d8;
  local_28 = dword_c71dc;
  dword_c71cc = 0x41;
  dword_c71d0 = 0x40;
  dword_c71d4 = 0x42;
  dword_c71d8 = 0x40;
  dword_c71dc = 0x42;
  dword_ebea0 = 0;
  dword_d0b12 = 0;
  uVar1 = allocmem(&aTemp_c2894,0x300,0x20);
  if ((sound_enabled != '\0') && (dword_c721d != 0)) {
    sound_fade(dword_d2431,3,0x32);
  }
  getpalette(0,0x100,uVar1);
  fade_palette(1,uVar1,0x10);
  unk_ec7c0._0_1_ = aCurrent_c2899[0];
  unk_ec7c0._1_1_ = aCurrent_c2899[1];
  unk_ec7c0._2_1_ = aCurrent_c2899[2];
  unk_ec7c0._3_1_ = aCurrent_c2899[3];
  (&DAT_000ec7c4)[(uint)bVar7 * -2] = *(undefined4 *)(aCurrent_c2899 + (uint)bVar7 * -8 + 4);
  setdefaultscreen();
  dword_ea2b0 = font_main;
  setfont(font_main);
  getfontstate(auStack_6c);
  if ((sound_enabled != '\0') && (dword_c721d != 0)) {
    do {
      iVar2 = sound_channel_status(ram0x000d242c >> 0x18,3);
    } while (iVar2 == 0);
    releasememblock(dword_c721d);
    dword_c721d = 0;
  }
  dword_ea2b4 = windowdefp(0x280,0x1e0,0x20);
  dword_ebe9c = (undefined4 *)
                allocmem(aPointer_c28a1,
                         ((*(int *)((int)pointer_shapes + 2) >> 0x10) + 1) *
                         (((int)pointer_shapes[1] >> 0x10) + 1) + 0x11,0x20);
  puVar5 = dword_ebe9c + (uint)bVar7 * -2 + 1;
  puVar3 = pointer_shapes + (uint)bVar7 * -2 + 1;
  *dword_ebe9c = *pointer_shapes;
  puVar6 = puVar5 + (uint)bVar7 * -2 + 1;
  puVar4 = puVar3 + (uint)bVar7 * -2 + 1;
  *puVar5 = *puVar3;
  *puVar6 = *puVar4;
  puVar6[(uint)bVar7 * -2 + 1] = puVar4[(uint)bVar7 * -2 + 1];
  *(undefined *)(puVar6 + (uint)bVar7 * -2 + 1 + (uint)bVar7 * -2 + 1) =
       *(undefined *)(puVar4 + (uint)bVar7 * -2 + 1 + (uint)bVar7 * -2 + 1);
  *(short *)(dword_ebe9c + 1) = *(short *)(pointer_shapes + 1) + 1;
  *(short *)((int)dword_ebe9c + 6) = *(short *)((int)pointer_shapes + 6) + 1;
  dbedit_load_databases(&aDB);
  database_menu(&unk_d0450,6,0x40,0x41,0x42);
  dbedit_free_databases();
  freemem(dword_ebe9c);
  if ((sound_enabled != '\0') && (dword_c721d != 0)) {
    sound_fade(dword_d2431,3,0x32);
  }
  getpalette(0,0x100,uVar1);
  fade_palette(1,uVar1,0x10);
  freemem(uVar1);
  setfontstate(auStack_6c);
  freemem(dword_ea2b4);
  dword_c71cc = uStack_1c;
  dword_c71d0 = local_2c;
  dword_c71d4 = local_20;
  dword_c71d8 = local_24;
  dword_c71dc = local_28;
  if ((sound_enabled != '\0') && (dword_c721d != 0)) {
    do {
      iVar2 = sound_channel_status(ram0x000d242c >> 0x18,3);
    } while (iVar2 == 0);
    releasememblock(dword_c721d);
    dword_c721d = 0;
  }
  return;
}


// ================================================================================================
// dbedit_draw_team_title @ 0x6cefb [__watcall]
// ================================================================================================

void __watcall dbedit_draw_team_title(undefined4 param_1,undefined4 param_2,int unaff_EBX)

{
  int iVar1;
  size_t sVar2;
  char acStack_60 [84];
  
  __CHK(0x70);
  if ((&byte_d07a8)[unaff_EBX] != '\x01') {
    sprintf(acStack_60,(char *)&aS_c28a9,*(int *)(&unk_ea988 + unaff_EBX * 4) + 0x1a);
    while( true ) {
      iVar1 = textwidth(acStack_60);
      if (iVar1 < 0x92) break;
      sVar2 = strlen(acStack_60);
      acStack_60[sVar2 - 1] = '\0';
    }
  }
  print_text_at(param_1);
  return;
}


// ================================================================================================
// dbedit_draw_roster_column @ 0x6cf6f [__watcall]
// ================================================================================================

void __watcall dbedit_draw_roster_column(int param_1,int unaff_EDX,int unaff_EBX)

{
  ulonglong uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  char acStack_70 [84];
  int local_1c;
  int local_18;
  int iStack_14;
  
  __CHK(0x94);
  if ((&byte_d07a8)[unaff_EBX] == '\x01') {
    iVar4 = 0;
    for (iVar3 = dword_ebca4; (iVar4 < 0x1c && (iVar3 < dword_d07b2)); iVar3 = iVar3 + 1) {
      local_1c = iVar3 * 0x1b;
      sprintf(acStack_70,(char *)&a2d,(uint)*(byte *)(dword_d07aa + local_1c + 1),unaff_EBX,
              unaff_EDX,param_1);
      printstr_at(acStack_70,param_1,(uint)byte_d42c3 * iVar4 + unaff_EDX);
      sprintf(acStack_70,(char *)&aC_d07eb,(uint)*(byte *)(dword_d07aa + local_1c));
      printstr_at(acStack_70,param_1 + 0x28,(uint)byte_d42c3 * iVar4 + unaff_EDX);
      format_team_name(acStack_70,0,dword_d07aa + local_1c + 8,0x91);
      printstr_at(acStack_70,param_1 + 0x50,(uint)byte_d42c3 * iVar4 + unaff_EDX);
      if (*(char *)(iVar3 + dword_d07ae) != '\0') {
        if (unaff_EBX == 0) {
          uVar2 = 0x23;
        }
        else {
          uVar2 = 0x15e;
        }
        fillrect2(uVar2,(uint)byte_d42c3 * iVar4 + 0x35,0xf0,(uint)byte_d42c3,0x80);
      }
      iVar4 = iVar4 + 1;
    }
    if (dword_d0c20 != 0) {
      buttons_draw_all(&unk_d0bb8,2);
      dword_d0c10 = dword_ebca4;
      uVar1 = (longlong)(dword_d0bfc + -4) * (longlong)dword_ebca4 & 0xffffffff;
      dword_d0c04 = (undefined4)(uVar1 / dword_d0c18);
      scrollbar_draw(&unk_d0bf0,(int)(uVar1 % (ulonglong)dword_d0c18));
    }
  }
  else {
    iVar3 = 0;
    do {
      local_18 = unaff_EBX * 0x2f4;
      iStack_14 = iVar3 * 0x1b;
      iVar4 = local_18 + iStack_14;
      if ((&unk_ea990)[iVar4] == '\0') {
        iVar3 = 0x1c;
      }
      else {
        sprintf(acStack_70,(char *)&a2d,(uint)(byte)(&unk_ea991)[iVar4]);
        printstr_at(acStack_70,param_1,(uint)byte_d42c3 * iVar3 + unaff_EDX);
        sprintf(acStack_70,(char *)&aC_d07eb,(uint)(byte)(&unk_ea990)[iVar4]);
        printstr_at(acStack_70,param_1 + 0x28,(uint)byte_d42c3 * iVar3 + unaff_EDX);
        format_team_name(acStack_70,0,local_18 + iStack_14 + 0xea998,0x91);
        printstr_at(acStack_70,param_1 + 0x50,(uint)byte_d42c3 * iVar3 + unaff_EDX);
        if ((&unk_eaf80)[unaff_EBX * 0x1c + iVar3] != '\0') {
          if (unaff_EBX == 0) {
            uVar2 = 0x23;
          }
          else {
            uVar2 = 0x15e;
          }
          fillrect2(uVar2,(uint)byte_d42c3 * iVar3 + 0x35,0xf0,(uint)byte_d42c3,0x80);
        }
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < 0x1c);
  }
  return;
}


// ================================================================================================
// dbedit_draw_database_title @ 0x6d256 [__watcall]
// ================================================================================================

void __watcall dbedit_draw_database_title(void)

{
  char acStackY_40 [4];
  char acStackY_3c [4];
  char acStackY_38 [44];
  
  __CHK(0x44);
  acStackY_40[0] = aDATABASE[0];
  acStackY_40[1] = aDATABASE[1];
  acStackY_40[2] = aDATABASE[2];
  acStackY_40[3] = aDATABASE[3];
  acStackY_3c[0] = aDATABASE[4];
  acStackY_3c[1] = aDATABASE[5];
  acStackY_3c[2] = aDATABASE[6];
  acStackY_3c[3] = aDATABASE[7];
  acStackY_38[0] = aDATABASE[8];
  acStackY_38[1] = aDATABASE[9];
  acStackY_38[2] = aDATABASE[10];
  acStackY_38[3] = aDATABASE[0xb];
  strupr(&unk_ec7c0);
  strcat(acStackY_40,(char *)&unk_ec7c0);
  print_centered_shadow(0x18,acStackY_40);
  return;
}


// ================================================================================================
// dbedit_draw_rosters @ 0x6d299 [__watcall]
// ================================================================================================

void __watcall dbedit_draw_rosters(int param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  undefined4 uVar1;
  
  __CHK(0xc);
  if (param_1 != 0) {
    dbedit_draw_team_title(0x19e,0x25,1,unaff_ECX,unaff_EDX,unaff_EBX);
    uVar1 = 0x167;
  }
  else {
    dbedit_draw_team_title(100,0x25,0,unaff_ECX,unaff_EDX,unaff_EBX);
    uVar1 = 0x2d;
  }
  dbedit_draw_roster_column(uVar1,0x35,param_1 != 0);
  dbedit_draw_database_title();
  return;
}


// ================================================================================================
// player_ratings_card @ 0x6d2f8 [__watcall]
// ================================================================================================

void __watcall player_ratings_card(void)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  int extraout_ECX;
  undefined *puVar4;
  int iVar5;
  int iVar6;
  char acStack_68 [84];
  
  __CHK(0x80);
  setscreen(dword_ea2b4);
  set_text_colors(0x40,0x43);
  draw_menu_items(&unk_d0450,5,0x40,0x41,0x42);
  puVar4 = install_path;
  if (byte_ed98f != '\x01') {
    puVar4 = (undefined *)0x0;
  }
  make_path(acStack_68,puVar4,aPrez2,0);
  uVar1 = loadshapes(acStack_68,0);
  iVar2 = locateshape(uVar1,&aPal_c28ca);
  memcpy(&palette_save,(void *)(iVar2 + 0x10),0x300);
  uVar3 = locateshape(uVar1,&aEa);
  setclip(0,0x280,0x13,0x1e0);
  drawshape_remap_home(uVar3);
  setclip(0,0x280,0,0x1e0);
  freemem(uVar1);
  dbedit_draw_rosters(0);
  dbedit_draw_rosters(1);
  if (dword_d0b12 == 2) {
    draw_bevel_box_b(0xb4,0x8c,0x1cc,0x154,1);
    fillrect(0xb4,0x8c,0x119,0xc9,0x41);
    drawline(0xb4,0x8c,0x1cb,0x8c,0x40);
    drawline(0xb4,0x8c,0xb4,0x153,0x40);
    drawline(0x1cc,0x8d,0x1cc,0x154,0x42);
    drawline(0xb5,0x154,0x1cc,0x154,0x42);
    putpixel(0xb4,0x154,0x41);
    putpixel(0x1cc,0x8c,0x41);
    strcpy(acStack_68,aRatings_d0819);
    strcat(acStack_68,&asc_c8111);
    strcat(acStack_68,(char *)(dword_eaf78 + 0x1a));
    iVar2 = textwidth(acStack_68);
    print_text_at((0x118 - iVar2) / 2 + 0xb4,0x99,acStack_68);
    iVar6 = dword_eaf78 + 0x2dc;
    iVar5 = 0xb0;
    iVar2 = 0;
    do {
      print_text_at(0xd2,iVar5,(&off_d0ac2)[iVar2]);
      sprintf(acStack_68,(char *)&a2d,(uint)*(byte *)(iVar6 + (uint)(byte)(&unk_d0ae6)[iVar2]));
      print_text_at(0x1a9,iVar5,acStack_68);
      iVar2 = extraout_ECX + 1;
      iVar5 = iVar5 + 0xd;
    } while (iVar2 < 9);
    buttons_draw_all(&unk_d0b80,2);
  }
  setdefaultscreen();
  drawshape2_home(*(undefined4 *)(dword_ea2b4 + 0x2c));
  return;
}


// ================================================================================================
// dbedit_return @ 0x6d5bb [__watcall]
// ================================================================================================

void __watcall dbedit_return(void)

{
  __CHK(4);
  dword_ebea0 = 0xffffffff;
  return;
}


// ================================================================================================
// dbedit_select_team @ 0x6d5d0 [__watcall]
// ================================================================================================

void __watcall dbedit_select_team(int *param_1)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  
  __CHK(0x20);
  uVar4 = (uint)(*param_1 != 1);
  iVar2 = param_1[1];
  iVar6 = param_1[2];
  bVar1 = (&byte_d079e)[uVar4];
  (&byte_d079e)[uVar4] = (&unk_c83c3)[iVar6 + iVar2 * 7];
  if (bVar1 == 0xff) {
    funcptr_d01cd = dbedit_free_agents;
    funcptr_d028d = dbedit_free_agents;
  }
  else {
    iVar3 = *(int *)(&unk_c5519 + (uint)bVar1 * 4) >> 1;
    if (iVar3 == 4) {
      iVar3 = 3;
    }
    iVar5 = 0;
    do {
      if (bVar1 == (&unk_c83c3)[iVar3 * 7 + iVar5]) break;
      iVar5 = iVar5 + 1;
    } while (iVar5 < 7);
    *(code **)((&off_d0151)[iVar3 * 8] + iVar5 * 0x20 + 0x14) = dbedit_select_team;
    *(code **)((&off_d0211)[iVar3 * 8] + iVar5 * 0x20 + 0x14) = dbedit_select_team;
  }
  iVar6 = iVar6 * 0x20;
  *(undefined4 *)((&off_d0151)[iVar2 * 8] + iVar6 + 0x14) = 0;
  *(undefined4 *)((&off_d0211)[iVar2 * 8] + iVar6 + 0x14) = 0;
  if (uVar4 == 0) {
    funcptr_d0391 = dbedit_edit_team_lines;
  }
  else {
    funcptr_d0411 = dbedit_edit_team_lines;
  }
  (&byte_d07a8)[uVar4] = 0;
  dbedit_free_lists(uVar4);
  player_ratings_card();
  return;
}


// ================================================================================================
// dbedit_free_agents @ 0x6d6db [__watcall]
// ================================================================================================

void __watcall dbedit_free_agents(int *param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  __CHK(0x18);
  uVar3 = (uint)(*param_1 != 1);
  iVar1 = *(int *)(&unk_c5519 + (uint)(byte)(&byte_d079e)[uVar3] * 4) >> 1;
  if (iVar1 == 4) {
    iVar1 = 3;
  }
  iVar2 = 0;
  do {
    if ((uint)(byte)(&unk_c83c3)[iVar1 * 7 + iVar2] == (uint)(byte)(&byte_d079e)[uVar3]) break;
    iVar2 = iVar2 + 1;
  } while (iVar2 < 7);
  *(code **)((&off_d0151)[iVar1 * 8] + iVar2 * 0x20 + 0x14) = dbedit_select_team;
  *(code **)((&off_d0211)[iVar1 * 8] + iVar2 * 0x20 + 0x14) = dbedit_select_team;
  funcptr_d01cd = (undefined *)0x0;
  funcptr_d028d = (undefined *)0x0;
  if (uVar3 == 0) {
    funcptr_d0391 = (undefined *)0x0;
  }
  else {
    funcptr_d0411 = (undefined *)0x0;
  }
  (&byte_d079e)[uVar3] = 0xff;
  (&byte_d07a8)[uVar3] = 1;
  dbedit_free_lists(uVar3);
  player_ratings_card();
  return;
}


// ================================================================================================
// cmp_key_names @ 0x6d78b [__watcall]
// ================================================================================================

int __watcall cmp_key_names(char *param_1,char *unaff_EDX)

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
    iVar3 = strcmp(param_1 + 0xb,unaff_EDX + 0xb);
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
// shellsort_records @ 0x6d7ed [__watcall]
// ================================================================================================

void __watcall shellsort_records(int param_1,int unaff_EDX,int unaff_EBX,code *unaff_ECX)

{
  byte bVar2;
  int iVar1;
  int iVar3;
  int iVar4;
  undefined4 local_20;
  undefined4 local_14;
  undefined4 uStackY_10;
  
  __CHK(0x28);
  local_14 = unaff_EDX >> 1;
  do {
    if (local_14 < 1) {
      return;
    }
    for (local_20 = local_14; local_20 < unaff_EDX; local_20 = local_20 + 1) {
      for (uStackY_10 = local_20 - local_14; -1 < uStackY_10; uStackY_10 = uStackY_10 - local_14) {
        iVar4 = uStackY_10 * unaff_EBX + param_1;
        iVar3 = param_1 + (uStackY_10 + local_14) * unaff_EBX;
        iVar1 = (*unaff_ECX)();
        if (iVar1 < 0) break;
        for (iVar1 = 0; iVar1 < unaff_EBX; iVar1 = iVar1 + 1) {
          bVar2 = *(byte *)(iVar4 + iVar1) ^ *(byte *)(iVar3 + iVar1);
          *(byte *)(iVar4 + iVar1) = bVar2;
          bVar2 = *(byte *)(iVar3 + iVar1) ^ bVar2;
          *(byte *)(iVar3 + iVar1) = bVar2;
          *(byte *)(iVar4 + iVar1) = *(byte *)(iVar4 + iVar1) ^ bVar2;
        }
      }
    }
    local_14 = local_14 >> 1;
  } while( true );
}


// ================================================================================================
// dbedit_build_free_agent_list @ 0x6d89a [__watcall]
// ================================================================================================

void __watcall dbedit_build_free_agent_list(int param_1,undefined4 param_2,undefined4 param_3,int unaff_ECX)

{
  int iVar1;
  int unaff_ESI;
  
  do {
    if (*(char *)(dword_d07c7 + param_1 * 0x34) == -1) {
      dword_d07b2 = dword_d07b2 + 1;
    }
    param_1 = param_1 + 1;
  } while (param_1 < unaff_ECX);
  dword_d07aa = allocmem(&aUar,dword_d07b2 * 0x1b,0);
  dword_d07ae = allocmem(&aUarm,dword_d07b2,0);
  database_build_list();
  shellsort_records(dword_d07aa,dword_d07b2,0x1b,cmp_key_names);
  for (iVar1 = 0; iVar1 < dword_d07b2; iVar1 = iVar1 + 1) {
    *(undefined *)(dword_d07ae + iVar1) = 0;
  }
  dword_ebca4 = 0;
  if (dword_d07b2 < 0x1d) {
    dword_d0c20 = 0;
  }
  else {
    dword_d0c20 = 0xffffffff;
    scrollbar_init(&unk_d0bf0,0x1c);
  }
  if (unaff_ESI == 0) {
    dword_d0331 = 0;
  }
  else {
    dword_d03b1 = 0;
  }
  dword_d0351 = 0;
  dword_d03d1 = 0;
  return;
}


// ================================================================================================
// dbedit_build_team_roster @ 0x6d98e [__watcall]
// ================================================================================================

void __watcall dbedit_build_team_roster(void)

{
  undefined4 uVar1;
  int iVar2;
  undefined1 *puVar3;
  code *unaff_ESI;
  
  uVar1 = dbedit_carteams_record((&byte_d079e)[(int)unaff_ESI]);
  *(undefined4 *)(&unk_ea988 + (int)unaff_ESI * 4) = uVar1;
  dbedit_build_team_list((&byte_d079e)[(int)unaff_ESI],&unk_ea990 + (int)unaff_ESI * 0x2f4,
            &dword_eaf78 + (int)unaff_ESI);
  shellsort_records(&unk_ea990 + (int)unaff_ESI * 0x2f4,0x1c,0x1b,cmp_key_names);
  for (iVar2 = 0; iVar2 < 0x1c; iVar2 = iVar2 + 1) {
    (&unk_eaf80)[(int)unaff_ESI * 0x1c + iVar2] = 0;
  }
  if (unaff_ESI == (code *)0x0) {
    puVar3 = dword_d07ae;
    if (byte_d07a9 != '\x01') {
      puVar3 = &unk_eaf9c;
    }
    dword_d0331 = unaff_ESI;
    dword_d0351 = unaff_ESI;
    iVar2 = dbedit_find_player_entry(puVar3);
    if (iVar2 != 0) {
      dword_d03d1 = roster_move_players;
    }
  }
  else {
    dword_d03b1 = 0;
    dword_d03d1 = (code *)0x0;
    puVar3 = dword_d07ae;
    if (byte_d07a8 != '\x01') {
      puVar3 = &unk_eaf80;
    }
    iVar2 = dbedit_find_player_entry(puVar3);
    if (iVar2 != 0) {
      dword_d0351 = roster_move_players;
    }
  }
  return;
}


// ================================================================================================
// dbedit_find_player_entry @ 0x6da88 [__watcall]
// ================================================================================================

undefined8 __watcall dbedit_find_player_entry(char *param_1,undefined4 unaff_EDX)

{
  char cVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  
  __CHK(0x10);
  iVar3 = 0;
  iVar2 = dword_d07b2;
  if (param_1 != dword_d07ae) {
    iVar2 = 0x1c;
  }
  while (0 < iVar2) {
    iVar2 = iVar2 + -1;
    pcVar4 = param_1 + 1;
    cVar1 = *param_1;
    param_1 = pcVar4;
    if (cVar1 != '\0') {
      iVar3 = iVar3 + 1;
    }
  }
  return CONCAT44(unaff_EDX,iVar3);
}


// ================================================================================================
// dbedit_roster_click @ 0x6dac3 [__watcall]
// ================================================================================================

void __watcall dbedit_roster_click(int param_1,int unaff_EDX)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 *puVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  
  __CHK(0x30);
  iVar6 = -1;
  if ((param_1 < 0x23) || (0x113 < param_1)) {
    if ((0x15d < param_1) && (param_1 < 0x24f)) {
      iVar6 = 1;
    }
  }
  else {
    iVar6 = 0;
  }
  if (-1 < iVar6) {
    if ((0x34 < unaff_EDX) && (uVar5 = (uint)byte_d42c3, unaff_EDX < (int)(uVar5 * 0x1c + 0x35))) {
      iVar1 = (unaff_EDX + -0x35) / (int)uVar5;
      iVar4 = iVar1 * uVar5 + 0x35;
      if ((&byte_d07a8)[iVar6] == '\x01') {
        if (dword_ebca4 + iVar1 < dword_d07b2) {
          if (iVar6 == 0) {
            uVar2 = 0x23;
          }
          else {
            uVar2 = 0x15e;
          }
          fillrect2(uVar2,iVar4,0xf0,uVar5,0x80);
          dword_d07ae[iVar1 + dword_ebca4] = ~dword_d07ae[iVar1 + dword_ebca4];
        }
      }
      else if ((&unk_ea990)[iVar1 * 0x1b + iVar6 * 0x2f4] != '\0') {
        if (iVar6 == 0) {
          uVar2 = 0x23;
        }
        else {
          uVar2 = 0x15e;
        }
        fillrect2(uVar2,iVar4,0xf0,uVar5,0x80);
        iVar1 = iVar1 + iVar6 * 0x1c;
        (&unk_eaf80)[iVar1] = ~(&unk_eaf80)[iVar1];
      }
    }
    puVar3 = dword_d07ae;
    if ((&byte_d07a8)[iVar6] != '\x01') {
      puVar3 = &unk_eaf80 + iVar6 * 0x1c;
    }
    iVar1 = dbedit_find_player_entry(puVar3);
    if (iVar1 < 1) {
      if (iVar6 == 0) {
        dword_d0331 = (code *)0x0;
        dword_d0351 = (code *)0x0;
      }
      else {
        dword_d03b1 = (code *)0x0;
        dword_d03d1 = (code *)0x0;
      }
    }
    else if (iVar6 == 0) {
      if ((byte_d07a8 != '\x01') && (dword_d07b2 < 0x1e)) {
        dword_d0331 = free_agent_move_dialog;
      }
      if (byte_d07a9 != '\x01') {
        dword_d0351 = roster_move_players;
      }
    }
    else {
      if ((byte_d07a9 != '\x01') && (dword_d07b2 < 0x1e)) {
        dword_d03b1 = free_agent_move_dialog;
      }
      if (byte_d07a8 != '\x01') {
        dword_d03d1 = roster_move_players;
      }
    }
  }
  return;
}


// ================================================================================================
// jersey_number_prompt @ 0x6dcbe [__watcall]
// ================================================================================================

void __watcall jersey_number_prompt(int param_1,int unaff_EDX)

{
  undefined uVar1;
  int iVar2;
  int iVar3;
  char acStack_90 [84];
  char acStack_3c [32];
  undefined local_1c [4];
  int iStack_18;
  
  __CHK(0xac);
  iStack_18 = dbedit_key_ptr(*(undefined4 *)
                         ((&dword_eaf78)[param_1] + 0x4c +
                         (uint)(byte)(&unk_ea992)[unaff_EDX * 0x1b + param_1 * 0x2f4] * 4));
  while( true ) {
    iVar3 = 0;
    iVar2 = 0;
    while ((iVar2 < 0x1c && (iVar3 == 0))) {
      if ((iVar2 != unaff_EDX) &&
         ((&unk_ea991)[param_1 * 0x2f4 + unaff_EDX * 0x1b] ==
          (&unk_ea991)[iVar2 * 0x1b + param_1 * 0x2f4])) {
        iVar3 = -1;
      }
      iVar2 = iVar2 + 1;
    }
    if (iVar3 == 0) break;
    strcpy(acStack_3c,(char *)(iStack_18 + 3));
    strcat(acStack_3c,&asc_c8111);
    strcat(acStack_3c,(char *)(iStack_18 + 0x13));
    sprintf(acStack_90,aTheJerseyNumber2dIsAlrea_c28dd,(uint)*(byte *)(iStack_18 + 1));
    dword_ebc74 = acStack_90;
    dword_ebc78 = aPleaseEnterANewJerseyNum;
    dword_ebc7c = acStack_3c;
    local_1c[0] = 0;
    uVar1 = database_dialog_box(&dword_ebc74,3,local_1c,2,0x16,0xffffffff,0,99,0xffffffff);
    *(undefined *)(iStack_18 + 1) = uVar1;
    (&unk_ea991)[unaff_EDX * 0x1b + param_1 * 0x2f4] = *(undefined *)(iStack_18 + 1);
  }
  return;
}


// ================================================================================================
// dbedit_snapshot_rosters @ 0x6de4c [__watcall]
// ================================================================================================

void __watcall dbedit_snapshot_rosters(void)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  __CHK(0x10);
  dword_d0b12 = 2;
  puVar2 = dword_eaf78;
  puVar3 = &unk_eafb8;
  for (iVar1 = 0xba; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  player_ratings_card();
  return;
}


// ================================================================================================
// dbedit_free_lists_all @ 0x6de7e [__watcall]
// ================================================================================================

/* WARNING: Removing unreachable block (ram,0x0006d96b) */
/* WARNING: Removing unreachable block (ram,0x0006da0c) */
/* WARNING: Removing unreachable block (ram,0x0006da28) */
/* WARNING: Removing unreachable block (ram,0x0006da21) */
/* WARNING: Removing unreachable block (ram,0x0006da2d) */
/* WARNING: Removing unreachable block (ram,0x0006da3a) */

void __watcall dbedit_free_lists_all(void)

{
  undefined1 *puVar1;
  int iVar2;
  
  __CHK(4);
  dbedit_free_lists(0);
  __CHK(0x24);
  if (byte_d07a9 == '\x01') {
    if (dword_d07ae != (undefined1 *)0x0) {
      freemem(dword_d07ae);
      dword_d07ae = (undefined1 *)0x0;
    }
    if (dword_d07aa != 0) {
      freemem(dword_d07aa);
      dword_d07aa = 0;
    }
    dword_d07b2 = 0;
    for (iVar2 = 0; iVar2 < (int)(dword_d07df / 0x34); iVar2 = iVar2 + 1) {
      if (*(char *)(dword_d07c7 + iVar2 * 0x34) == -1) {
        dword_d07b2 = dword_d07b2 + 1;
      }
    }
    dword_d07aa = allocmem(&aUar,dword_d07b2 * 0x1b,0);
    dword_d07ae = (undefined1 *)allocmem(&aUarm,dword_d07b2,0);
    database_build_list();
    shellsort_records(dword_d07aa,dword_d07b2,0x1b,cmp_key_names);
    for (iVar2 = 0; iVar2 < dword_d07b2; iVar2 = iVar2 + 1) {
      dword_d07ae[iVar2] = 0;
    }
    dword_ebca4 = 0;
    if (dword_d07b2 < 0x1d) {
      dword_d0c20 = 0;
    }
    else {
      dword_d0c20 = 0xffffffff;
      scrollbar_init(&unk_d0bf0,0x1c);
    }
    dword_d03b1 = 0;
    dword_d0351 = (code *)0x0;
    dword_d03d1 = 0;
  }
  else {
    uRam000ea98c = dbedit_carteams_record(byte_d079f);
    dbedit_build_team_list(byte_d079f,&unk_eac84,&dword_eaf7c);
    shellsort_records(&unk_eac84,0x1c,0x1b,cmp_key_names);
    for (iVar2 = 0; iVar2 < 0x1c; iVar2 = iVar2 + 1) {
      (&unk_eaf9c)[iVar2] = 0;
    }
    dword_d03b1 = 0;
    dword_d03d1 = 0;
    puVar1 = dword_d07ae;
    if (byte_d07a8 != '\x01') {
      puVar1 = &unk_eaf80;
    }
    iVar2 = dbedit_find_player_entry(puVar1);
    if (iVar2 != 0) {
      dword_d0351 = roster_move_players;
    }
  }
  return;
}


// ================================================================================================
// dbedit_free_lists @ 0x6de94 [__watcall]
// ================================================================================================

void __watcall dbedit_free_lists(code *param_1)

{
  code *pcVar1;
  undefined4 uVar2;
  undefined1 *puVar3;
  int iVar4;
  
  __CHK(0x24);
  if ((&byte_d07a8)[(int)param_1] == '\x01') {
    if (dword_d07ae != (undefined1 *)0x0) {
      freemem(dword_d07ae);
      dword_d07ae = (undefined1 *)0x0;
    }
    if (dword_d07aa != 0) {
      freemem(dword_d07aa);
      dword_d07aa = 0;
    }
    dword_d07b2 = 0;
    for (iVar4 = 0; iVar4 < (int)(dword_d07df / 0x34); iVar4 = iVar4 + 1) {
      if (*(char *)(dword_d07c7 + iVar4 * 0x34) == -1) {
        dword_d07b2 = dword_d07b2 + 1;
      }
    }
    dword_d07aa = allocmem(&aUar,dword_d07b2 * 0x1b,0);
    dword_d07ae = (undefined1 *)allocmem(&aUarm,dword_d07b2,0);
    database_build_list();
    shellsort_records(dword_d07aa,dword_d07b2,0x1b,cmp_key_names);
    for (iVar4 = 0; iVar4 < dword_d07b2; iVar4 = iVar4 + 1) {
      dword_d07ae[iVar4] = 0;
    }
    dword_ebca4 = 0;
    if (dword_d07b2 < 0x1d) {
      dword_d0c20 = 0;
    }
    else {
      dword_d0c20 = 0xffffffff;
      scrollbar_init(&unk_d0bf0,0x1c);
    }
    pcVar1 = param_1;
    if (param_1 != (code *)0x0) {
      dword_d03b1 = 0;
      pcVar1 = dword_d0331;
    }
    dword_d0331 = pcVar1;
    dword_d0351 = (code *)0x0;
    dword_d03d1 = (code *)0x0;
  }
  else {
    uVar2 = dbedit_carteams_record((&byte_d079e)[(int)param_1]);
    *(undefined4 *)(&unk_ea988 + (int)param_1 * 4) = uVar2;
    dbedit_build_team_list((&byte_d079e)[(int)param_1],&unk_ea990 + (int)param_1 * 0x2f4,
              &dword_eaf78 + (int)param_1);
    shellsort_records(&unk_ea990 + (int)param_1 * 0x2f4,0x1c,0x1b,cmp_key_names);
    for (iVar4 = 0; iVar4 < 0x1c; iVar4 = iVar4 + 1) {
      (&unk_eaf80)[(int)param_1 * 0x1c + iVar4] = 0;
    }
    if (param_1 == (code *)0x0) {
      puVar3 = dword_d07ae;
      if (byte_d07a9 != '\x01') {
        puVar3 = &unk_eaf9c;
      }
      dword_d0331 = param_1;
      dword_d0351 = param_1;
      iVar4 = dbedit_find_player_entry(puVar3);
      if (iVar4 != 0) {
        dword_d03d1 = roster_move_players;
      }
    }
    else {
      dword_d03b1 = 0;
      dword_d03d1 = (code *)0x0;
      puVar3 = dword_d07ae;
      if (byte_d07a8 != '\x01') {
        puVar3 = &unk_eaf80;
      }
      iVar4 = dbedit_find_player_entry(puVar3);
      if (iVar4 != 0) {
        dword_d0351 = roster_move_players;
      }
    }
  }
  return;
}


// ================================================================================================
// dbedit_edit_team_lines @ 0x6df06 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall dbedit_edit_team_lines(int *param_1)

{
  uint uVar1;
  ushort uVar2;
  ushort uVar3;
  ushort uVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  byte bVar9;
  undefined4 auStack_304 [186];
  uint local_1c;
  uint uStack_18;
  
  bVar9 = 0;
  __CHK(0x30c);
  local_1c = (uint)(*param_1 != 3);
  if (local_1c == 0) {
    uVar2 = (ushort)byte_d079e;
    uVar4 = _away_team_id;
    uVar3 = user2_team._2_2_;
  }
  else {
    uVar2 = user2_team._2_2_;
    uVar4 = (ushort)byte_d079f;
    uVar3 = _away_team_id;
  }
  _away_team_id = uVar4;
  user2_team._2_2_ = uVar2;
  uStack_18 = (uint)uVar3;
  if (dword_d07ae != 0) {
    freemem(dword_d07ae);
    dword_d07ae = 0;
  }
  if (dword_d07aa != 0) {
    freemem(dword_d07aa);
    dword_d07aa = 0;
  }
  uVar1 = local_1c;
  puVar7 = &team_names + local_1c * 0xba;
  puVar6 = auStack_304;
  for (iVar5 = 0xba; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar6 = *puVar7;
    puVar7 = puVar7 + (uint)bVar9 * -2 + 1;
    puVar6 = puVar6 + (uint)bVar9 * -2 + 1;
  }
  puVar7 = (undefined4 *)(&dword_eaf78)[local_1c];
  puVar6 = puVar7;
  puVar8 = &team_names + uVar1 * 0xba;
  for (iVar5 = 0xba; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar8 = *puVar6;
    puVar6 = puVar6 + (uint)bVar9 * -2 + 1;
    puVar8 = puVar8 + (uint)bVar9 * -2 + 1;
  }
  edit_lines_screen_a(local_1c & 0xff,puVar7 + 0x2f,&unk_d05f4,3);
  setdefaultscreen();
  clearclip(0);
  puVar7 = auStack_304;
  puVar6 = &team_names;
  for (iVar5 = 0xba; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar6 = *puVar7;
    puVar7 = puVar7 + (uint)bVar9 * -2 + 1;
    puVar6 = puVar6 + (uint)bVar9 * -2 + 1;
  }
  uVar3 = (ushort)uStack_18;
  if (local_1c == 0) {
    user2_team._2_2_ = (ushort)uStack_18;
    uVar3 = _away_team_id;
  }
  _away_team_id = uVar3;
  if ((&byte_d079e)[local_1c == 0] == -1) {
    dbedit_free_lists(local_1c == 0);
  }
  player_ratings_card();
  fade_palette(0,&palette_save,0x10);
  return;
}


// ================================================================================================
// database_menu @ 0x6e089 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __watcall database_menu(undefined4 param_1)

{
  code *pcVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined *puVar6;
  undefined4 uVar7;
  int *piVar8;
  undefined4 *puVar9;
  undefined4 uVar10;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  int iVar11;
  undefined4 uVar12;
  int iVar13;
  undefined4 *puVar14;
  int iVar15;
  undefined4 *puVar16;
  undefined4 *puVar17;
  undefined4 *puVar18;
  byte bVar19;
  undefined4 local_8c [27];
  
  bVar19 = 0;
  __CHK(0xa0);
  dword_ebc68 = 0;
  puVar14 = local_8c;
  local_8c[0] = 0x6e0b4;
  dbedit_free_lists_all();
  puVar14[-1] = 0x6e0b9;
  player_ratings_card();
  puVar14[6] = param_1;
  puVar14[0xf] = extraout_EDX;
  iVar15 = 0;
  *puVar14 = 0;
  puVar14[1] = 0;
  do {
    puVar14[iVar15 + 9] = 0;
    puVar14[iVar15 + 0xc] = 0;
    if (0 < iVar15) {
      puVar14[iVar15 + 6] = 0;
      puVar14[iVar15 + 0xf] = 0;
    }
    iVar15 = iVar15 + 1;
  } while (iVar15 < 3);
  iVar15 = *(int *)puVar14[6];
  iVar11 = *(int *)(puVar14[6] + 8);
  puVar14[0x19] = (iVar15 + iVar11) / 2;
  puVar14[0x17] = (iVar15 + iVar11) / 2;
  iVar15 = (*(int *)(puVar14[6] + 4) + *(int *)(puVar14[6] + 0xc)) / 2;
  puVar14[0x18] = iVar15;
  puVar14[0x16] = iVar15;
  puVar14[-1] = iVar15;
  puVar14[-2] = puVar14[0x19];
  puVar14[-3] = dword_ebe9c;
  puVar14[-4] = 0x6e13e;
  grabshape();
  puVar14[-1] = puVar14[0x18];
  puVar14[-2] = puVar14[0x19];
  puVar14[-3] = pointer_shapes;
  puVar14[-4] = 0x6e157;
  drawshape_remap();
  puVar14[-1] = 0x6e16b;
  fade_palette(0,&palette_save);
  puVar14[-1] = 0x1e0;
  puVar14[-2] = 0x280;
  puVar14[-3] = 0;
  puVar14[-4] = 0;
  puVar14[-5] = 0x6e17e;
  setmouselimits();
  puVar14[-1] = puVar14[0x18];
  puVar14[-2] = puVar14[0x19];
  puVar14[-3] = 0x6e190;
  setmousepos();
  puVar6 = mouse_update_callback;
  puVar14[-1] = 0x6e199;
  (*(code *)puVar6)();
  puVar14[-1] = 0x6e19e;
  event_queue_reset();
  do {
    if ((sound_enabled != '\0') && (dword_c721d != 0)) {
      iVar15 = ram0x000d242c >> 0x18;
      puVar14[-1] = 0x6e1c2;
      iVar15 = sound_channel_status(iVar15,3);
      if (iVar15 != 0) {
        puVar14[-1] = dword_c721d;
        puVar14[-2] = 0x6e1d2;
        releasememblock();
        dword_c721d = 0;
      }
    }
    puVar14[0x1e] = 0;
    do {
      puVar14[-1] = 0x6e1e8;
      iVar15 = event_queue_pop();
      pcVar1 = ui_poll_callback;
      if (iVar15 == 0) break;
      puVar14[-1] = 0x6e1fc;
      uVar7 = (*pcVar1)();
      puVar14[0x1e] = uVar7;
    } while ((*(byte *)(puVar14 + 0x1e) & 2) == 0);
    if ((dword_d0c20 != 0) &&
       ((((byte_d07a8 == '\x01' || (byte_d07a9 == '\x01')) && (dword_d0b12 != 2)) &&
        (iVar15 = puVar14[0x1e], iVar15 != 0)))) {
      puVar14[-1] = puVar14[0x18];
      puVar14[-2] = puVar14[0x19];
      puVar14[-3] = dword_ebe9c;
      puVar14[-4] = 0x6e25d;
      drawshape();
      puVar14[-1] = iVar15;
      puVar14[-2] = 0x6e278;
      iVar15 = button_at(&unk_d0bb8,2,puVar14[0x17],puVar14[0x16]);
      if ((iVar15 == 0) && (0 < dword_ebca4)) {
        dword_ebca4 = dword_ebca4 + -1;
LAB_0006e2b2:
        puVar14[-1] = 0x6e2b7;
        player_ratings_card();
      }
      else if ((iVar15 == 1) && (dword_ebca4 < dword_d07b2 + -0x1c)) {
        dword_ebca4 = dword_ebca4 + 1;
        goto LAB_0006e2b2;
      }
      puVar14[-1] = puVar14[0x1e];
      puVar14[-2] = 0x6e2d3;
      iVar15 = scrollbar_at(&unk_d0bf0,1,puVar14[0x17],puVar14[0x16]);
      if ((-1 < iVar15) && (dword_ebca4 != dword_d0c10)) {
        dword_ebca4 = dword_d0c10;
        puVar14[-1] = 0x6e2f1;
        player_ratings_card();
      }
      puVar14[-1] = puVar14[0x16];
      puVar14[-2] = puVar14[0x17];
      puVar14[-3] = dword_ebe9c;
      puVar14[-4] = 0x6e307;
      grabshape();
      puVar14[-1] = puVar14[0x16];
      puVar14[-2] = puVar14[0x17];
      puVar14[-3] = pointer_shapes;
      puVar14[-4] = 0x6e320;
      drawshape_remap();
      puVar14[0x19] = puVar14[0x17];
      puVar14[0x18] = puVar14[0x16];
    }
    if ((dword_d0b12 == 2) && ((*(byte *)(puVar14 + 0x1e) & 1) != 0)) {
      puVar14[-1] = puVar14[0x18];
      puVar14[-2] = puVar14[0x19];
      puVar14[-3] = dword_ebe9c;
      puVar14[-4] = 0x6e359;
      drawshape();
      puVar14[-1] = puVar14[0x1e];
      puVar14[-2] = 0x6e378;
      button_at(&unk_d0b80,2,puVar14[0x17],puVar14[0x16]);
      puVar14[-1] = puVar14[0x16];
      puVar14[-2] = puVar14[0x17];
      puVar14[-3] = dword_ebe9c;
      puVar14[-4] = 0x6e38e;
      grabshape();
      puVar14[-1] = puVar14[0x16];
      puVar14[-2] = puVar14[0x17];
      puVar14[-3] = pointer_shapes;
LAB_0006ea14:
      puVar14[-4] = 0x6ea19;
      drawshape_remap();
      puVar14[0x19] = puVar14[0x17];
      puVar14[0x18] = puVar14[0x16];
    }
    else {
      if ((*(byte *)(puVar14 + 0x1e) & 2) != 0) {
        if (dword_d0b12 == 2) {
          puVar14[-1] = puVar14[0x18];
          puVar14[-2] = puVar14[0x19];
          puVar14[-3] = dword_ebe9c;
          puVar14[-4] = 0x6e42d;
          drawshape();
LAB_0006e430:
          puVar14[-1] = puVar14[0x18];
          puVar14[-2] = puVar14[0x19];
          puVar14[-3] = dword_ebe9c;
        }
        else {
          puVar14[-1] = puVar14 + 0x14;
          puVar14[-2] = puVar14 + 0x15;
          puVar14[-3] = puVar14;
          puVar14[-4] = puVar14 + 0xf;
          puVar14[-5] = 0x6e472;
          iVar15 = hit_test_menus(puVar14[0x17],puVar14[0x16],puVar14 + 6,puVar14[0x1d]);
          if (iVar15 != 0) {
            if (*(int *)(puVar14[0x14] * 0x20 + puVar14[puVar14[0x15] + 6] + 0x14) == 0) {
              if (*(int *)(puVar14[0x14] * 0x20 + puVar14[puVar14[0x15] + 6] + 0x18) == 0) {
                puVar14[-1] = puVar14[0x18];
                puVar14[-2] = puVar14[0x19];
                puVar14[-3] = dword_ebe9c;
                puVar14[-4] = 0x6e8bc;
                drawshape();
                puVar14[-1] = puVar14[0x23];
                puVar14[-2] = puVar14[0x1a];
                iVar15 = puVar14[0x15];
                uVar7 = puVar14[iVar15 * 2 + 1];
                uVar12 = puVar14[iVar15 * 2];
                iVar11 = puVar14[iVar15 + 0xc];
                iVar15 = puVar14[iVar15 + 6];
                puVar14[-3] = 0x6e8ee;
                highlight_menu_item(iVar15 + iVar11 * 0x20,uVar12,uVar7,puVar14[0x1b]);
                iVar15 = puVar14[0x15];
                iVar11 = puVar14[0x14];
                puVar14[iVar15 + 0xc] = iVar11;
                puVar14[-1] = puVar14[0x23];
                puVar14[-2] = puVar14[0x1a];
                uVar7 = puVar14[iVar15 * 2 + 1];
                uVar12 = puVar14[iVar15 * 2];
                iVar15 = iVar11 * 0x20 + puVar14[iVar15 + 6];
                uVar10 = puVar14[0x1b];
              }
              else {
                puVar14[-1] = puVar14[0x18];
                puVar14[-2] = puVar14[0x19];
                puVar14[-3] = dword_ebe9c;
                puVar14[-4] = 0x6e680;
                drawshape();
                iVar15 = puVar14[0x1d];
                if (iVar15 != puVar14[0x15]) {
                  for (; (int)puVar14[0x15] < iVar15; iVar15 = iVar15 + -1) {
                    puVar14[iVar15 + 0xc] = 0;
                    iVar11 = puVar14[iVar15 + 9];
                    if (iVar11 != 0) {
                      puVar14[-1] = puVar14[iVar15 * 2 + 1];
                      puVar14[-2] = puVar14[iVar15 * 2];
                      puVar14[-3] = iVar11;
                      puVar14[-4] = 0x6e6b6;
                      drawshape();
                      puVar14[iVar15 * 2 + 1] = 0;
                      puVar14[iVar15 * 2] = 0;
                      puVar14[-1] = puVar14[iVar15 + 9];
                      puVar14[-2] = 0x6e6cc;
                      freemem();
                      puVar14[iVar15 + 9] = 0;
                      puVar14[iVar15 + 6] = 0;
                      puVar14[iVar15 + 0xf] = 0;
                    }
                  }
                  puVar14[0x1d] = puVar14[0x15];
                }
                puVar14[-1] = puVar14[0x23];
                puVar14[-2] = puVar14[0x1a];
                iVar15 = puVar14[0x1d];
                uVar7 = puVar14[iVar15 * 2 + 1];
                uVar12 = puVar14[iVar15 * 2];
                iVar11 = puVar14[iVar15 + 0xc];
                iVar13 = puVar14[iVar15 + 6];
                puVar14[-3] = 0x6e71d;
                highlight_menu_item(iVar11 * 0x20 + iVar13,uVar12,uVar7,puVar14[0x1b]);
                puVar14[iVar15 + 0xc] = puVar14[0x14];
                puVar14[-1] = puVar14[0x23];
                puVar14[-2] = puVar14[0x1a];
                uVar7 = puVar14[iVar15 * 2 + 1];
                uVar12 = puVar14[iVar15 * 2];
                iVar11 = puVar14[iVar15 + 6];
                puVar14[-3] = 0x6e750;
                unhighlight_menu_item(puVar14[0x14] * 0x20 + iVar11,uVar12,uVar7,puVar14[0x1b]);
                iVar11 = puVar14[0x15];
                iVar13 = puVar14[0x14];
                iVar2 = puVar14[iVar11 + 6];
                puVar14[0x1d] = iVar15 + 1;
                puVar14[iVar15 + 7] = *(undefined4 *)(iVar2 + 0x18 + iVar13 * 0x20);
                piVar8 = (int *)(puVar14[iVar11 + 6] + iVar13 * 0x20);
                puVar14[iVar15 + 0x10] = piVar8[7];
                if (iVar15 + 1 == 1) {
                  iVar15 = *piVar8;
                }
                else {
                  iVar15 = piVar8[2];
                }
                puVar14[puVar14[0x1d] * 2] = iVar15 + puVar14[puVar14[0x1d] * 2 + -2];
                if (puVar14[0x1d] == 1) {
                  iVar15 = *(int *)(puVar14[0x14] * 0x20 + 0xc + puVar14[puVar14[0x15] + 6]);
                }
                else {
                  iVar15 = *(int *)(puVar14[0x14] * 0x20 + 4 + puVar14[puVar14[0x15] + 6]);
                }
                iVar11 = puVar14[0x1d];
                puVar14[0x1c] = iVar11 * 8;
                puVar14[iVar11 * 2 + 1] = iVar15 + puVar14[iVar11 * 2 + -1];
                iVar15 = puVar14[0x1d];
                iVar11 = puVar14[iVar15 + 0xf];
                piVar8 = (int *)puVar14[iVar15 + 6];
                iVar13 = (piVar8[iVar11 * 8 + -6] - *piVar8) + 1;
                puVar14[0x13] = iVar13;
                iVar11 = (piVar8[iVar11 * 8 + -5] - piVar8[1]) + 1;
                puVar14[0x12] = iVar11;
                puVar14[-1] = 0;
                puVar14[-2] = iVar13 * 4 * iVar11 + 0x11;
                puVar14[-3] = aMenubuff_c2929;
                puVar14[-4] = 0x6e80e;
                puVar9 = (undefined4 *)allocmem();
                puVar14[iVar15 + 9] = puVar9;
                puVar17 = puVar9 + (uint)bVar19 * -2 + 1;
                puVar16 = pointer_shapes + (uint)bVar19 * -2 + 1;
                *puVar9 = *pointer_shapes;
                puVar18 = puVar17 + (uint)bVar19 * -2 + 1;
                puVar9 = puVar16 + (uint)bVar19 * -2 + 1;
                *puVar17 = *puVar16;
                *puVar18 = *puVar9;
                puVar18[(uint)bVar19 * -2 + 1] = puVar9[(uint)bVar19 * -2 + 1];
                *(undefined *)(puVar18 + (uint)bVar19 * -2 + 1 + (uint)bVar19 * -2 + 1) =
                     *(undefined *)(puVar9 + (uint)bVar19 * -2 + 1 + (uint)bVar19 * -2 + 1);
                *(short *)(puVar14[iVar15 + 9] + 4) = (short)puVar14[0x13];
                *(short *)(puVar14[iVar15 + 9] + 6) = (short)puVar14[0x12];
                puVar14[-1] = *(undefined4 *)((int)puVar14 + puVar14[0x1c] + 4);
                puVar14[-2] = *(undefined4 *)((int)puVar14 + puVar14[0x1c]);
                puVar14[-3] = puVar14[iVar15 + 9];
                puVar14[-4] = 0x6e852;
                grabshape();
                uVar7 = puVar14[0x23];
                puVar14[-1] = uVar7;
                uVar12 = puVar14[0x1a];
                puVar14[-2] = uVar12;
                puVar14[-3] = puVar14[0x1b];
                uVar10 = *(undefined4 *)((int)puVar14 + puVar14[0x1c] + 4);
                uVar3 = *(undefined4 *)((int)puVar14 + puVar14[0x1c]);
                uVar4 = puVar14[iVar15 + 0xf];
                uVar5 = puVar14[iVar15 + 6];
                puVar14[-4] = 0x6e884;
                draw_menu(uVar5,uVar4,uVar3,uVar10);
                puVar14[iVar15 + 0xc] = 0;
                puVar14[-1] = uVar7;
                puVar14[-2] = uVar12;
                uVar7 = *(undefined4 *)((int)puVar14 + puVar14[0x1c] + 4);
                uVar12 = *(undefined4 *)((int)puVar14 + puVar14[0x1c]);
                iVar15 = puVar14[iVar15 + 6];
                uVar10 = puVar14[0x1b];
              }
            }
            else {
              if (puVar14[0x14] == puVar14[puVar14[0x15] + 0xc]) {
                puVar14[-1] = puVar14[0x18];
                puVar14[-2] = puVar14[0x19];
                puVar14[-3] = dword_ebe9c;
                puVar14[-4] = 0x6e4bc;
                drawshape();
                for (iVar15 = 2; -1 < iVar15; iVar15 = iVar15 + -1) {
                  iVar11 = puVar14[iVar15 + 9];
                  if (iVar11 != 0) {
                    puVar14[-1] = puVar14[iVar15 * 2 + 1];
                    puVar14[-2] = puVar14[iVar15 * 2];
                    puVar14[-3] = iVar11;
                    puVar14[-4] = 0x6e4e3;
                    drawshape();
                    puVar14[iVar15 * 2 + 1] = 0;
                    puVar14[iVar15 * 2] = 0;
                    puVar14[-1] = puVar14[iVar15 + 9];
                    puVar14[-2] = 0x6e4f9;
                    freemem();
                  }
                }
                iVar15 = 0;
                puVar14[0x1d] = 0;
                pcVar1 = *(code **)(puVar14[puVar14[0x15] + 6] + puVar14[0x14] * 0x20 + 0x14);
                puVar14[-1] = 0x6e527;
                (*pcVar1)();
                do {
                  puVar14[iVar15 + 9] = 0;
                  if (0 < iVar15) {
                    puVar14[iVar15 + 6] = 0;
                    puVar14[iVar15 + 0xc] = 0;
                    puVar14[iVar15 + 0xf] = 0;
                  }
                  iVar15 = iVar15 + 1;
                } while (iVar15 < 3);
                puVar14[-1] = puVar14[0x18];
                puVar14[-2] = puVar14[0x19];
                puVar14[-3] = 0x6e557;
                setmousepos();
                puVar14[0x17] = puVar14[0x19];
                puVar14[0x16] = puVar14[0x18];
                puVar14[-1] = 0x6e56f;
                event_queue_reset(puVar14[0x18],extraout_EDX_00,puVar14 + 0x18);
                goto LAB_0006e430;
              }
              puVar14[-1] = puVar14[0x18];
              puVar14[-2] = puVar14[0x19];
              puVar14[-3] = dword_ebe9c;
              puVar14[-4] = 0x6e58a;
              drawshape();
              iVar15 = puVar14[0x1d];
              if (iVar15 != puVar14[0x15]) {
                for (; (int)puVar14[0x15] < iVar15; iVar15 = iVar15 + -1) {
                  puVar14[iVar15 + 0xc] = 0;
                  iVar11 = puVar14[iVar15 + 9];
                  if (iVar11 != 0) {
                    puVar14[-1] = puVar14[iVar15 * 2 + 1];
                    puVar14[-2] = puVar14[iVar15 * 2];
                    puVar14[-3] = iVar11;
                    puVar14[-4] = 0x6e5c0;
                    drawshape();
                    puVar14[iVar15 * 2 + 1] = 0;
                    puVar14[iVar15 * 2] = 0;
                    puVar14[-1] = puVar14[iVar15 + 9];
                    puVar14[-2] = 0x6e5d6;
                    freemem();
                    puVar14[iVar15 + 9] = 0;
                    puVar14[iVar15 + 6] = 0;
                    puVar14[iVar15 + 0xf] = 0;
                  }
                }
                puVar14[0x1d] = puVar14[0x15];
              }
              puVar14[-1] = puVar14[0x23];
              puVar14[-2] = puVar14[0x1a];
              iVar15 = puVar14[0x15];
              uVar7 = puVar14[iVar15 * 2 + 1];
              uVar12 = puVar14[iVar15 * 2];
              iVar11 = puVar14[iVar15 + 0xc];
              iVar15 = puVar14[iVar15 + 6];
              puVar14[-3] = 0x6e625;
              highlight_menu_item(iVar15 + iVar11 * 0x20,uVar12,uVar7,puVar14[0x1b]);
              iVar15 = puVar14[0x15];
              puVar14[iVar15 + 0xc] = puVar14[0x14];
              puVar14[-1] = puVar14[0x23];
              puVar14[-2] = puVar14[0x1a];
              uVar7 = puVar14[iVar15 * 2 + 1];
              uVar12 = puVar14[iVar15 * 2];
              iVar15 = puVar14[iVar15 + 0xc] * 0x20 + puVar14[iVar15 + 6];
              uVar10 = puVar14[0x1b];
            }
            puVar14[-3] = 0x6e923;
            unhighlight_menu_item(iVar15,uVar12,uVar7,uVar10);
            goto LAB_0006e430;
          }
          puVar14[-1] = puVar14[0x18];
          puVar14[-2] = puVar14[0x19];
          puVar14[-3] = dword_ebe9c;
          puVar14[-4] = 0x6e93e;
          drawshape();
          for (iVar15 = 2; -1 < iVar15; iVar15 = iVar15 + -1) {
            iVar11 = puVar14[iVar15 + 9];
            if (iVar11 != 0) {
              puVar14[-1] = puVar14[iVar15 * 2 + 1];
              puVar14[-2] = puVar14[iVar15 * 2];
              puVar14[-3] = iVar11;
              puVar14[-4] = 0x6e965;
              drawshape();
              puVar14[iVar15 * 2 + 1] = 0;
              puVar14[iVar15 * 2] = 0;
              puVar14[-1] = puVar14[iVar15 + 9];
              puVar14[-2] = 0x6e97b;
              freemem();
            }
          }
          puVar14[0x1d] = 0;
          iVar15 = 0;
          do {
            puVar14[iVar15 + 9] = 0;
            if (0 < iVar15) {
              puVar14[iVar15 + 6] = 0;
              puVar14[iVar15 + 0xc] = 0;
              puVar14[iVar15 + 0xf] = 0;
            }
            iVar15 = iVar15 + 1;
          } while (iVar15 < 3);
          puVar14[-1] = 0x6e9b9;
          dbedit_roster_click(puVar14[0x17],puVar14[0x16]);
          puVar14[-1] = puVar14[0x18];
          puVar14[-2] = puVar14[0x19];
          puVar14[-3] = dword_ebe9c;
        }
        puVar14[-4] = 0x6e9cf;
        grabshape();
        puVar14[-1] = puVar14[0x18];
        puVar14[-2] = puVar14[0x19];
        puVar14[-3] = dword_ebe9c;
        puVar14[-4] = 0x6e9e8;
        drawshape();
        puVar14[-1] = puVar14[0x16];
        puVar14[-2] = puVar14[0x17];
        puVar14[-3] = dword_ebe9c;
        puVar14[-4] = 0x6ea00;
        grabshape();
        puVar14[-1] = puVar14[0x16];
        puVar14[-2] = puVar14[0x17];
        puVar14[-3] = pointer_shapes;
        goto LAB_0006ea14;
      }
      if ((puVar14[0x17] != puVar14[0x19]) || (puVar14[0x16] != puVar14[0x18])) {
        puVar14[-1] = puVar14[0x18];
        puVar14[-2] = puVar14[0x19];
        puVar14[-3] = dword_ebe9c;
        puVar14[-4] = 0x6e3dc;
        drawshape();
        puVar14[-1] = puVar14[0x16];
        puVar14[-2] = puVar14[0x17];
        puVar14[-3] = dword_ebe9c;
        puVar14[-4] = 0x6e3f5;
        grabshape();
        puVar14[-1] = puVar14[0x16];
        puVar14[-2] = puVar14[0x17];
        puVar14[-3] = pointer_shapes;
        goto LAB_0006ea14;
      }
    }
    if (dword_ebea0 == -1) {
      puVar14[-1] = puVar14[0x18];
      puVar14[-2] = puVar14[0x19];
      puVar14[-3] = dword_ebe9c;
      puVar14[-4] = 0x6ea4c;
      drawshape();
      if (dword_ebc68 != 0) {
        dword_ebc74 = aTheDatabaseHasNotBeenSav;
        dword_ebc78 = aAreYouSureYouWantToExit;
        puVar14[-1] = 0xffffffff;
        puVar14[-2] = puVar14 + 0x16;
        puVar14[-3] = puVar14 + 0x17;
        puVar14[-4] = 2;
        puVar14[-5] = &unk_c7733;
        puVar14[-6] = 0x6ea91;
        iVar15 = message_dialog(0xffffffff,0xffffffff);
        if (iVar15 < 1) {
          dword_ebea0 = 0;
        }
      }
    }
    if (dword_ebea0 != 0) {
      return 0;
    }
  } while( true );
}


// ================================================================================================
// dbedit_error_dialog_loop @ 0x6eab5 [__cdecl]
// ================================================================================================

int dbedit_error_dialog_loop(void)

{
  undefined4 **ppuVar1;
  int *in_EAX;
  int iVar2;
  undefined4 uVar3;
  int in_ECX;
  int *in_EDX;
  undefined4 unaff_EBX;
  undefined4 ***pppuVar4;
  undefined4 ***pppuVar5;
  undefined4 ***pppuVar6;
  undefined8 uVar7;
  ulonglong uVar8;
  undefined4 **local_1c;
  undefined4 **local_18;
  int local_14;
  uint uStack_10;
  
  __CHK(0x3c);
  local_14 = -1;
  pppuVar5 = (undefined4 ***)*in_EAX;
  pppuVar6 = (undefined4 ***)*in_EDX;
  local_1c = pppuVar6;
  local_18 = pppuVar5;
  setmousepos(pppuVar5,pppuVar6);
  pppuVar4 = dword_ebe9c;
  grabshape(dword_ebe9c,pppuVar5,pppuVar6);
  drawshape_remap(pointer_shapes,pppuVar5,pppuVar6);
  do {
    do {
      iVar2 = key_down(1);
    } while (iVar2 != 0);
    iVar2 = key_down(0x1c);
  } while (iVar2 != 0);
  uVar7 = event_queue_reset();
  iVar2 = 0;
  do {
    uVar7 = event_queue_pop((int)uVar7,(int)((ulonglong)uVar7 >> 0x20),pppuVar4);
    if ((int)uVar7 != 0) {
      pppuVar4 = &local_1c;
      uVar8 = (*ui_poll_callback)();
      uStack_10._0_1_ = (undefined)uVar8;
      uVar3 = CONCAT22((short)(uVar8 >> 0x10),CONCAT11((undefined)uStack_10,(undefined)uStack_10));
      if ((uVar8 & 4) == 0) {
        if ((uVar8 & 3) != 0) {
          uStack_10 = (uint)uVar8;
          drawshape(dword_ebe9c,pppuVar5,pppuVar6);
          ppuVar1 = local_18;
          if (in_ECX < 1) {
            if ((uStack_10 & 2) != 0) goto LAB_0006eba8;
          }
          else {
            local_14 = button_at(unaff_EBX,in_ECX,local_18,local_1c,uStack_10);
            pppuVar4 = (undefined4 ***)ppuVar1;
            if (-1 < local_14) {
LAB_0006eba8:
              iVar2 = -1;
            }
          }
          grabshape(dword_ebe9c,pppuVar5,pppuVar6);
          uVar7 = drawshape_remap(pointer_shapes,pppuVar5,pppuVar6);
          uVar8 = CONCAT44((int)((ulonglong)uVar7 >> 0x20),uStack_10);
          uVar3 = (undefined4)uVar7;
        }
      }
      else {
        uVar8 = CONCAT44(0xffffffff,(uint)uVar8);
        local_14 = -1;
        iVar2 = -1;
      }
      uStack_10 = (uint)uVar8;
      uVar7 = CONCAT44((int)(uVar8 >> 0x20),uVar3);
      if ((pppuVar5 != (undefined4 ***)local_18) || (pppuVar6 != (undefined4 ***)local_1c)) {
        drawshape(dword_ebe9c,pppuVar5,pppuVar6);
        grabshape(dword_ebe9c,local_18,local_1c);
        pppuVar4 = (undefined4 ***)local_1c;
        uVar7 = drawshape_remap(pointer_shapes,local_18,local_1c);
        pppuVar5 = (undefined4 ***)local_18;
        pppuVar6 = (undefined4 ***)local_1c;
      }
    }
    if (iVar2 != 0) {
      do {
        do {
          iVar2 = key_down(1);
        } while (iVar2 != 0);
        iVar2 = key_down(0x1c);
      } while (iVar2 != 0);
      event_queue_reset();
      drawshape(dword_ebe9c,pppuVar5,pppuVar6);
      event_queue_reset();
      setmousepos(local_18,local_1c);
      *in_EAX = (int)local_18;
      *in_EDX = (int)local_1c;
      return local_14;
    }
  } while( true );
}


// ================================================================================================
// dbedit_errors_screen @ 0x6ec95 [__watcall]
// ================================================================================================

void __watcall dbedit_errors_screen(undefined4 *param_1,int *unaff_EDX,int *unaff_EBX)

{
  __CHK(0x28);
  setscreen(dword_ea2b4);
  clearclip(0x41);
  draw_menu_items(&unk_d0450,5,0x40,0x41,0x42);
  fillrect(0,0x13,0x280,0x1cd,0x41);
  buttons_draw_all(&unk_d0ca2,2);
  *param_1 = 0;
  if (*unaff_EBX != 0) {
    print_centered_shadow(*unaff_EDX * 0xd + 0x1f,aErrorsFoundInDatabases);
    *unaff_EDX = *unaff_EDX + 2;
    *unaff_EBX = 0;
  }
  return;
}


// ================================================================================================
// dbedit_show_errors @ 0x6ed39 [__watcall]
// ================================================================================================

void __watcall dbedit_show_errors(undefined4 *param_1,undefined4 *unaff_EDX,undefined4 unaff_EBX)

{
  __CHK(0x18);
  setdefaultscreen();
  drawshape2_home(*(undefined4 *)(dword_ea2b4 + 0x2c),unaff_EBX);
  *param_1 = 0xffffffff;
  *unaff_EDX = 0;
  dbedit_error_dialog_loop();
  return;
}


// ================================================================================================
// check_lines @ 0x6ed8f [__watcall]
// ================================================================================================

int __watcall
check_lines(undefined4 param_1,int *param_2,int *unaff_EBX,undefined4 unaff_ECX,uint param_5,
           undefined4 param_6,undefined4 param_7)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  char *pcVar5;
  char *pcVar6;
  char acStackY_74 [84];
  int local_14;
  int iStackY_10;
  
  __CHK(0x78);
  iStackY_10 = -2;
  iVar1 = dbedit_teams_record();
  uVar4 = 0;
  local_14 = 0;
  do {
    if (((9 < local_14) || (iStackY_10 == 1)) || (iStackY_10 == -1)) {
      return iStackY_10;
    }
    iStackY_10 = -2;
    if (*unaff_EBX != 0) {
      dbedit_errors_screen(unaff_EBX,param_2,unaff_ECX);
      uVar4 = unaff_ECX;
    }
    uVar2 = param_5 & *(uint *)(&unk_d0cda + local_14 * 4);
    if (uVar2 != 0) {
      if (uVar2 < 0x10) {
        if (uVar2 < 2) {
          if (uVar2 == 1) {
            iVar3 = 9;
            pcVar5 = aTheForwardLinesAreNotCom;
            pcVar6 = acStackY_74;
            goto LAB_0006ee80;
          }
        }
        else if (uVar2 < 3) {
          iVar3 = 9;
          pcVar5 = aTheDefenceLinesAreNotCom;
          pcVar6 = acStackY_74;
LAB_0006ee80:
          for (; iVar3 != 0; iVar3 = iVar3 + -1) {
            *(undefined4 *)pcVar6 = *(undefined4 *)pcVar5;
            pcVar5 = pcVar5 + 4;
            pcVar6 = (char *)((int)pcVar6 + 4);
          }
          *(undefined2 *)pcVar6 = *(undefined2 *)pcVar5;
          *(char *)((int)pcVar6 + 2) = pcVar5[2];
        }
        else if (3 < uVar2) {
          if (uVar2 < 5) {
            iVar3 = 10;
            pcVar5 = aThePowerPlayLinesAreNotC;
            pcVar6 = acStackY_74;
            goto LAB_0006eea4;
          }
          if (uVar2 == 8) {
            iVar3 = 0xb;
            pcVar5 = aThePenaltyKillingLinesAr;
            pcVar6 = acStackY_74;
            goto LAB_0006ee80;
          }
        }
      }
      else if (uVar2 < 0x11) {
        iVar3 = 9;
        pcVar5 = aTheGoalieLinesAreNotComp;
        pcVar6 = acStackY_74;
LAB_0006eea4:
        for (; iVar3 != 0; iVar3 = iVar3 + -1) {
          *(undefined4 *)pcVar6 = *(undefined4 *)pcVar5;
          pcVar5 = pcVar5 + 4;
          pcVar6 = (char *)((int)pcVar6 + 4);
        }
        *(undefined2 *)pcVar6 = *(undefined2 *)pcVar5;
      }
      else if (uVar2 < 0x80) {
        if (0x1f < uVar2) {
          if (uVar2 < 0x21) {
            iVar3 = 0xb;
            pcVar5 = aTheExtraAttackerLinesAre;
            pcVar6 = acStackY_74;
            goto LAB_0006eea4;
          }
          if (uVar2 == 0x40) {
            iVar3 = 8;
            pcVar5 = aThereAreNotEnoughPlayers;
            pcVar6 = acStackY_74;
            goto LAB_0006ef0a;
          }
        }
      }
      else if (uVar2 < 0x81) {
        iVar3 = 8;
        pcVar5 = aThereAreNotEnoughGoalies;
        pcVar6 = acStackY_74;
LAB_0006ef0a:
        for (; iVar3 != 0; iVar3 = iVar3 + -1) {
          *(undefined4 *)pcVar6 = *(undefined4 *)pcVar5;
          pcVar5 = pcVar5 + 4;
          pcVar6 = pcVar6 + 4;
        }
        *pcVar6 = *pcVar5;
      }
      else if (0xff < uVar2) {
        if (uVar2 < 0x101) {
          iVar3 = 8;
          pcVar5 = aThereAreNotEnoughForward;
          pcVar6 = acStackY_74;
          goto LAB_0006eea4;
        }
        if (uVar2 == 0x200) {
          iVar3 = 8;
          pcVar5 = aThereAreNotEnoughDefence;
          pcVar6 = acStackY_74;
          goto LAB_0006ef0a;
        }
      }
      strcat(acStackY_74,(char *)(iVar1 + 0x1a));
      print_centered_shadow(*param_2 * 0xd + 0x1f,acStackY_74,uVar4);
      iVar3 = *param_2;
      *param_2 = iVar3 + 1;
      if (0x1d < iVar3 + 1) {
        iStackY_10 = dbedit_show_errors(unaff_EBX,param_2,param_6,param_7);
        uVar4 = param_6;
      }
    }
    local_14 = local_14 + 1;
  } while( true );
}


// ================================================================================================
// dbedit_validate_lines @ 0x6ef84 [__watcall]
// ================================================================================================

undefined4 __watcall dbedit_validate_lines(undefined4 param_1,undefined4 unaff_EDX)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  undefined8 uVar7;
  undefined4 local_30;
  undefined4 local_2c;
  int local_28;
  undefined4 local_24;
  int local_20;
  int local_1c;
  int iStack_18;
  
  __CHK(0x48);
  local_28 = 0;
  local_24 = 0xffffffff;
  local_2c = 0xffffffff;
  local_30 = 0xffffffff;
  local_20 = 0;
  do {
    uVar4 = 0;
    iVar5 = 0;
    iStack_18 = 0;
    local_1c = 0;
    iVar6 = 0;
    uVar7 = dbedit_teams_record(local_20,0);
    iVar3 = (int)((ulonglong)uVar7 >> 0x20);
    iVar2 = (int)uVar7;
    do {
      iVar1 = *(int *)(iVar3 * 4 + iVar2 + 0x4c);
      if (iVar1 != -1) {
        iVar5 = iVar5 + 1;
        uVar7 = dbedit_key_ptr(iVar1);
        iVar3 = (int)((ulonglong)uVar7 >> 0x20);
        if (*(char *)((int)uVar7 + 2) == 'D') {
          iVar6 = iVar6 + 1;
        }
        else {
          local_1c = local_1c + 1;
        }
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < 0x19);
    iVar3 = 0;
    do {
      if (*(int *)(iVar2 + 0xb0 + iVar3 * 4) != -1) {
        iStack_18 = iStack_18 + 1;
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < 3);
    iVar3 = 0;
    do {
      if (*(char *)(iVar3 + iVar2 + 0xbc) == 'd') {
        uVar4 = 1;
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < 0xc);
    iVar3 = 0;
    do {
      if (*(char *)(iVar3 + iVar2 + 200) == 'd') {
        uVar4 = uVar4 | 2;
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < 6);
    iVar3 = 0;
    do {
      if (*(char *)(iVar3 + iVar2 + 0xce) == 'd') {
        uVar4 = uVar4 | 4;
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < 10);
    iVar3 = 0;
    do {
      if (*(char *)(iVar3 + iVar2 + 0xd8) == 'd') {
        uVar4 = uVar4 | 8;
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < 8);
    iVar3 = 0;
    do {
      if (*(char *)(iVar3 + iVar2 + 0xe0) == 'd') {
        uVar4 = uVar4 | 0x10;
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < 2);
    iVar3 = 0;
    do {
      if (*(char *)(iVar3 + iVar2 + 0xe2) == 'd') {
        uVar4 = uVar4 | 0x20;
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < 2);
    if (iVar5 < 5) {
      uVar4 = uVar4 | 0x40;
    }
    if (local_1c < 3) {
      uVar4 = uVar4 | 0x100;
    }
    if (iVar6 < 2) {
      uVar4 = uVar4 | 0x200;
    }
    if (iStack_18 < 2) {
      uVar4 = uVar4 | 0x80;
    }
    iVar2 = -2;
    if (uVar4 != 0) {
      local_24 = 0;
      iVar2 = check_lines(local_20,&local_28,&local_2c,&local_30,uVar4,param_1,unaff_EDX);
      if (local_28 != 0) {
        local_28 = local_28 + 1;
      }
    }
    if ((iVar2 == -2) && ((0x1d < local_28 || ((0 < local_28 && (local_20 == 0x1b)))))) {
      iVar2 = dbedit_show_errors(&local_2c,&local_28,param_1,unaff_EDX);
    }
    if ((iVar2 == -1) || (iVar2 == 1)) {
      local_20 = 0x1c;
    }
    local_20 = local_20 + 1;
  } while (local_20 < 0x1c);
  return local_24;
}


// ================================================================================================
// player_name_normalize @ 0x6f159 [__watcall]
// ================================================================================================

void __watcall player_name_normalize(char *param_1,int unaff_EDX,int unaff_EBX)

{
  size_t sVar1;
  int iVar2;
  int iVar3;
  int local_1c;
  
  __CHK(0x20);
  sVar1 = strlen(param_1);
  for (iVar2 = 0;
      ((*(int *)((int)&qword_c4b64 + (byte)(param_1[iVar2] + 1) + 5) >> 0x18 & 0xc0U) == 0 &&
      (iVar2 < (int)sVar1)); iVar2 = iVar2 + 1) {
  }
  iVar3 = 0;
  local_1c = 0;
  while (((iVar2 < (int)sVar1 && (iVar3 < 0xf)) && (local_1c == 0))) {
    if ((*(int *)((int)&qword_c4b64 + (byte)(param_1[iVar2] + 1) + 5) >> 0x18 & 0xc0U) == 0) {
      local_1c = -1;
    }
    else {
      *(char *)(iVar3 + unaff_EDX) = param_1[iVar2];
      iVar3 = iVar3 + 1;
    }
    iVar2 = iVar2 + 1;
  }
  *(undefined *)(iVar3 + unaff_EDX) = 0;
  if ((iVar3 == 0xf) &&
     ((*(int *)((int)&qword_c4b64 + (byte)(param_1[iVar2] + 1) + 5) >> 0x18 & 0xc0U) != 0)) {
    for (; ((*(int *)((int)&qword_c4b64 + (byte)(param_1[iVar2] + 1) + 5) >> 0x18 & 0xc0U) != 0 &&
           (iVar2 < (int)sVar1)); iVar2 = iVar2 + 1) {
    }
  }
  for (; ((*(int *)((int)&qword_c4b64 + (byte)(param_1[iVar2] + 1) + 5) >> 0x18 & 0xc0U) == 0 &&
         (iVar2 < (int)sVar1)); iVar2 = iVar2 + 1) {
  }
  iVar3 = 0;
  local_1c = 0;
  while (((iVar2 < (int)sVar1 && (iVar3 < 0xf)) && (local_1c == 0))) {
    if ((*(int *)((int)&qword_c4b64 + (byte)(param_1[iVar2] + 1) + 5) >> 0x18 & 0xc0U) == 0) {
      local_1c = -1;
    }
    else {
      *(char *)(iVar3 + unaff_EBX) = param_1[iVar2];
      iVar3 = iVar3 + 1;
    }
    iVar2 = iVar2 + 1;
  }
  *(undefined *)(iVar3 + unaff_EBX) = 0;
  return;
}


// ================================================================================================
// roster_move_players @ 0x6f29c [__watcall]
// ================================================================================================

void __watcall roster_move_players(int *param_1,undefined4 unaff_EDX,undefined4 unaff_EBX)

{
  undefined4 uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  undefined *puVar5;
  int iVar6;
  int iVar7;
  undefined8 uVar8;
  int local_28;
  int local_20;
  int local_18;
  int iStack_14;
  
  __CHK(0x4c);
  uVar2 = (uint)(*param_1 != 3);
  uVar3 = (uint)(uVar2 == 0);
  local_28 = 0;
  local_20 = 0;
  iVar7 = 0;
  if ((&byte_d07a8)[uVar2] == '\0') {
    for (local_18 = 0; local_18 < 0x1c; local_18 = local_18 + 1) {
      if ((&unk_eaf80)[uVar2 * 0x1c + local_18] != '\0') {
        local_20 = local_20 + 1;
        uVar1 = *(undefined4 *)(&unk_ea994 + uVar2 * 0x2f4 + local_18 * 0x1b);
        uVar8 = dbedit_key_ptr();
        puVar5 = (undefined *)uVar8;
        iStack_14 = -1;
        if ((&unk_ea990)[(int)((ulonglong)uVar8 >> 0x20)] == 'G') {
          iVar6 = 0;
          while ((iVar6 < 3 && (iStack_14 < 0))) {
            if (*(int *)((&dword_eaf78)[uVar3] + 0xb0 + iVar6 * 4) == -1) {
              iStack_14 = iVar6 + 0x19;
            }
            iVar6 = iVar6 + 1;
          }
        }
        else {
          iVar6 = 0;
          while ((iVar6 < 0x19 && (iStack_14 < 0))) {
            if (*(int *)((&dword_eaf78)[uVar3] + 0x4c + iVar6 * 4) == -1) {
              iStack_14 = iVar6;
            }
            iVar6 = iVar6 + 1;
          }
        }
        if (-1 < iStack_14) {
          local_28 = -1;
          *puVar5 = (&byte_d079e)[uVar3];
          iVar7 = iVar7 + 1;
          *(undefined4 *)(iStack_14 * 4 + (&dword_eaf78)[uVar3] + 0x4c) = uVar1;
          (&unk_ea993)[iStack_14 * 0x1b + uVar3 * 0x2f4] = 2;
          dbedit_team_scan_players((&byte_d079e)[uVar2],uVar1);
          iVar6 = 0;
          do {
            iVar4 = dbedit_key_ptr(*(undefined4 *)((&dword_eaf78)[uVar3] + 0x4c + iVar6 * 4));
            if (puVar5[1] == *(char *)(iVar4 + 1)) {
              iVar4 = (0x1c - iVar7) * 0x1b + uVar3 * 0x2f4;
              (&unk_ea991)[iVar4] = puVar5[1];
              (&unk_ea992)[iVar4] = (undefined)iStack_14;
              jersey_number_prompt(uVar3,0x1c - iVar7);
            }
            iVar6 = iVar6 + 1;
          } while (iVar6 < 0x1c);
        }
      }
    }
  }
  else {
    for (local_18 = 0; local_18 < dword_d07b2; local_18 = local_18 + 1) {
      if (*(char *)(dword_d07ae + local_18) != '\0') {
        local_20 = local_20 + 1;
        uVar1 = *(undefined4 *)(local_18 * 0x1b + 4 + dword_d07aa);
        uVar8 = dbedit_key_ptr();
        puVar5 = (undefined *)uVar8;
        iStack_14 = -1;
        if (*(char *)((int)((ulonglong)uVar8 >> 0x20) + dword_d07aa) == 'G') {
          iVar6 = 0;
          while ((iVar6 < 3 && (iStack_14 < 0))) {
            if (*(int *)((&dword_eaf78)[uVar3] + 0xb0 + iVar6 * 4) == -1) {
              iStack_14 = iVar6 + 0x19;
            }
            iVar6 = iVar6 + 1;
          }
        }
        else {
          iVar6 = 0;
          while ((iVar6 < 0x19 && (iStack_14 < 0))) {
            if (*(int *)((&dword_eaf78)[uVar3] + 0x4c + iVar6 * 4) == -1) {
              iStack_14 = iVar6;
            }
            iVar6 = iVar6 + 1;
          }
        }
        if (-1 < iStack_14) {
          local_28 = -1;
          *puVar5 = (&byte_d079e)[uVar3];
          iVar7 = iVar7 + 1;
          *(undefined4 *)(iStack_14 * 4 + (&dword_eaf78)[uVar3] + 0x4c) = uVar1;
          (&unk_ea993)[iStack_14 * 0x1b + uVar3 * 0x2f4] = 2;
          iVar6 = 0;
          do {
            iVar4 = dbedit_key_ptr(*(undefined4 *)((&dword_eaf78)[uVar3] + 0x4c + iVar6 * 4));
            if (puVar5[1] == *(char *)(iVar4 + 1)) {
              iVar4 = (0x1c - iVar7) * 0x1b + uVar3 * 0x2f4;
              (&unk_ea991)[iVar4] = puVar5[1];
              (&unk_ea992)[iVar4] = (undefined)iStack_14;
              jersey_number_prompt(uVar3,0x1c - iVar7);
            }
            iVar6 = iVar6 + 1;
          } while (iVar6 < 0x1c);
        }
      }
    }
  }
  if (iVar7 != local_20) {
    if (local_20 == 1) {
      dword_ebc74 = aThereIsNoSpaceToAdd;
      dword_ebc78 = aTheSelectedPlayer;
    }
    else {
      dword_ebc74 = aThereIsNotEnoughSpaceTo;
      dword_ebc78 = aAddAllSelectedPlayers;
    }
    message_dialog(0xffffffff,0xffffffff,&dword_ebc74,2,0,0,unaff_EDX,unaff_EBX,0xffffffff);
  }
  if (local_28 != 0) {
    dword_ebc68 = 1;
    dbedit_free_lists(0);
    dbedit_free_lists(1);
    player_ratings_card();
  }
  return;
}


// ================================================================================================
// rating_scale @ 0x6f6ad [__watcall]
// ================================================================================================

longdouble __watcall rating_scale(byte param_1)

{
  __CHK(0xc);
  return (longdouble)((param_1 + 5) * 5);
}


// ================================================================================================
// create_player_form @ 0x6f6d4 [__watcall]
// ================================================================================================

void __watcall create_player_form(int param_1,int unaff_EDX,undefined2 *unaff_EBX)

{
  uint uVar1;
  ushort uVar2;
  short sVar3;
  undefined2 uVar4;
  uint uVar5;
  int extraout_EDX;
  int extraout_EDX_00;
  int extraout_EDX_01;
  int extraout_EDX_02;
  int extraout_EDX_03;
  int extraout_EDX_04;
  int extraout_EDX_05;
  int extraout_EDX_06;
  int extraout_EDX_07;
  int extraout_EDX_08;
  int extraout_EDX_09;
  int extraout_EDX_10;
  uint uVar6;
  longdouble lVar7;
  longdouble lVar8;
  longdouble lVar9;
  longdouble lVar10;
  longdouble lVar11;
  longdouble lVar12;
  longdouble lVar13;
  longdouble lVar14;
  longdouble lVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float local_28;
  
  __CHK(100);
  lVar7 = (longdouble)rating_scale(*(undefined *)(unaff_EDX + 1));
  lVar8 = (longdouble)rating_scale(*(undefined *)(extraout_EDX + 2));
  lVar9 = (longdouble)rating_scale(*(undefined *)(extraout_EDX_00 + 4));
  rating_scale(*(undefined *)(extraout_EDX_01 + 5));
  lVar10 = (longdouble)rating_scale(*(undefined *)(extraout_EDX_02 + 6));
  lVar11 = (longdouble)rating_scale(*(undefined *)(extraout_EDX_03 + 7));
  lVar12 = (longdouble)rating_scale(*(undefined *)(extraout_EDX_04 + 9));
  lVar13 = (longdouble)rating_scale(*(undefined *)(extraout_EDX_05 + 10));
  rating_scale(*(undefined *)(extraout_EDX_06 + 0xb));
  rating_scale(*(undefined *)(extraout_EDX_07 + 0xc));
  lVar14 = (longdouble)rating_scale(*(undefined *)(extraout_EDX_08 + 0xd));
  lVar15 = (longdouble)rating_scale(*(undefined *)(extraout_EDX_09 + 0xe));
  local_28 = (float)lVar15;
  rating_scale(*(undefined *)(extraout_EDX_10 + 0x13));
  randomrange(0x14d);
  randomrange(0x15);
  lVar15 = (longdouble)fround();
  *unaff_EBX = (short)(int)ROUND(lVar15);
  lVar15 = (longdouble)fround();
  unaff_EBX[7] = (short)(int)ROUND(lVar15);
  lVar15 = (longdouble)fround();
  unaff_EBX[8] = (short)(int)ROUND(lVar15);
  fVar18 = ((float)lVar8 + (float)lVar13 + (float)lVar10 + (float)lVar7 + (float)lVar14) /
           dword_c2cc8;
  if (*(char *)(param_1 + 2) == 'D') {
    fVar17 = (dword_c2cc0 - local_28) / dword_c2cd0;
    fVar16 = dword_c2ccc;
  }
  else {
    fVar17 = (dword_c2cc0 - local_28) / dword_c2cd8;
    fVar16 = dword_c2cd4;
  }
  local_28 = local_28 / fVar16;
  if (1.0 <= local_28) {
    uVar5 = 0x3a;
  }
  else {
    lVar7 = (longdouble)fround();
    uVar5 = (int)ROUND(lVar7) & 0xffff;
  }
  if (1.0 <= fVar17) {
    uVar6 = 0x5a;
  }
  else {
    lVar7 = (longdouble)fround();
    uVar6 = (int)ROUND(lVar7) & 0xffff;
  }
  fVar17 = (float)uVar5 * (((float)lVar9 + (float)lVar11) / dword_c2cbc);
  fVar16 = (float)uVar6 * ((float)lVar12 / dword_c2cc0);
  lVar7 = (longdouble)fround();
  uVar6 = (uint)ROUND(lVar7);
  uVar2 = (ushort)uVar6;
  lVar7 = (longdouble)fround();
  uVar1 = (uint)ROUND(lVar7);
  sVar3 = (short)uVar1;
  uVar5 = (uVar6 & 0xffff) + (uVar1 & 0xffff);
  if (0x80 < uVar5) {
    uVar2 = (ushort)(((ulonglong)uVar6 & 0xffffffff0000ffff) /
                    (ulonglong)(longlong)((int)uVar5 >> 7));
    sVar3 = (short)(((ulonglong)uVar1 & 0xffffffff0000ffff) /
                   (ulonglong)(longlong)((int)((uint)uVar2 + (uVar1 & 0xffff)) >> 7));
  }
  unaff_EBX[1] = uVar2;
  unaff_EBX[2] = sVar3;
  unaff_EBX[3] = unaff_EBX[1] + sVar3;
  unaff_EBX[4] = (ushort)unaff_EBX[1] / 10;
  uVar4 = randomrange(unaff_EBX[4],(uint)(ushort)unaff_EBX[1] % 10,unaff_EBX,10,fVar16,fVar17,fVar18
                     );
  unaff_EBX[5] = uVar4;
  lVar7 = (longdouble)fround();
  unaff_EBX[6] = (short)(int)ROUND(lVar7);
  return;
}


// ================================================================================================
// empty_func_6fa72 @ 0x6fa72 [__watcall]
// ================================================================================================

void __watcall empty_func_6fa72(void)

{
  __CHK(4);
  return;
}


// ================================================================================================
// free_agent_draw_shoots @ 0x6fa7d [__watcall]
// ================================================================================================

void __watcall free_agent_draw_shoots(void)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  __CHK(0x24);
  print_text_at(0x1e,0x12a,s_CShoots_000c2cf3 + 1);
  if ((char)byte_d0f94 == '\0') {
    puVar1 = &aR_c2cff;
  }
  else {
    puVar1 = &aL_c2cfb;
  }
  print_text_at(200,0x12a,puVar1);
  iVar2 = 0;
  iVar4 = 1;
  iVar3 = 0x137;
  do {
    if (iVar4 == 8) {
      iVar2 = 0x136;
      iVar3 = iVar3 + -0x68;
    }
    print_text_at(iVar2 + 0x1e,iVar3,(&off_d0880)[iVar4]);
    print_textf(iVar2 + 200,iVar3,&a3d,(*(byte *)((int)&byte_d0f94 + iVar4) + 5) * 5);
    iVar3 = iVar3 + 0xd;
    iVar4 = iVar4 + 1;
  } while (iVar4 < 0xf);
  return;
}


// ================================================================================================
// free_agent_draw_glove @ 0x6fb35 [__watcall]
// ================================================================================================

void __watcall free_agent_draw_glove(void)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  __CHK(0x24);
  print_text_at(0x1e,0x12a,aGloveHand_c2d03);
  if ((char)byte_d0fe0 == '\0') {
    puVar1 = &aR_c2cff;
  }
  else {
    puVar1 = &aL_c2cfb;
  }
  print_text_at(200,0x12a,puVar1);
  iVar2 = 0;
  iVar4 = 1;
  iVar3 = 0x137;
  do {
    if (iVar4 == 6) {
      iVar2 = 0x136;
      iVar3 = iVar3 + -0x4e;
    }
    print_text_at(iVar2 + 0x1e,iVar3,(&off_d09db)[iVar4]);
    print_textf(iVar2 + 200,iVar3,&a3d,(*(byte *)((int)&byte_d0fe0 + iVar4) + 5) * 5);
    iVar3 = iVar3 + 0xd;
    iVar4 = iVar4 + 1;
  } while (iVar4 < 0xb);
  return;
}


// ================================================================================================
// ratings_confirm_dialog @ 0x6fbe8 [__watcall]
// ================================================================================================

void __watcall ratings_confirm_dialog(char *param_1,undefined4 unaff_EDX)

{
  char cVar1;
  undefined2 auStack_10 [2];
  
  __CHK(0x28);
  auStack_10[0] = word_c2d10;
  if (*param_1 != '\0') {
    auStack_10[0] = word_c2d0e;
  }
  dword_ebc74 = unaff_EDX;
  cVar1 = database_dialog_box(&dword_ebc74,1,auStack_10,1,0x10,0,0,0,0);
  if (cVar1 != -1) {
    if (((char)auStack_10[0] == 'L') || ((char)auStack_10[0] == 'l')) {
      *param_1 = '\x01';
    }
    else if (((char)auStack_10[0] == 'R') || ((char)auStack_10[0] == 'r')) {
      *param_1 = '\0';
    }
  }
  return;
}


// ================================================================================================
// skater_ratings_edit @ 0x6fc60 [__watcall]
// ================================================================================================

int __watcall skater_ratings_edit(int *param_1,int *unaff_EDX,int *unaff_EBX)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  char *pcVar4;
  byte *pbVar5;
  undefined4 *puVar6;
  byte *pbVar7;
  byte bVar8;
  int *apiStackY_204c [2015];
  int *local_b4;
  char acStack_b0 [52];
  char acStack_7c [4];
  undefined4 auStack_78 [12];
  char acStack_48 [32];
  undefined4 *local_28;
  int local_24;
  int local_20;
  byte *local_1c;
  int local_18;
  int iStack_14;
  
  bVar8 = 0;
  __CHK(0xd4);
  local_24 = 0;
  local_20 = 0;
  iStack_14 = 0x12a;
  iVar3 = 0;
  local_b4 = param_1;
  while ((iVar3 < 0xf && (local_24 == 0))) {
    if (iVar3 == 8) {
      local_20 = 0x136;
      iStack_14 = iStack_14 + -0x68;
    }
    if ((((local_20 + 200 <= *local_b4) && (*local_b4 < local_20 + 0xe4)) &&
        (iStack_14 <= *unaff_EDX)) && (*unaff_EDX < iStack_14 + 0xd)) {
      local_24 = 1;
      local_28 = &byte_d0f94;
      acStack_7c[0] = aEnterANewRating[0];
      acStack_7c[1] = aEnterANewRating[1];
      acStack_7c[2] = aEnterANewRating[2];
      acStack_7c[3] = aEnterANewRating[3];
      puVar6 = auStack_78 + (uint)bVar8 * -2 + (uint)bVar8 * -2 + 1;
      pcVar4 = aEnterANewRating + (uint)bVar8 * -8 + (uint)bVar8 * -8 + 8;
      auStack_78[(uint)bVar8 * -2] = *(undefined4 *)(aEnterANewRating + (uint)bVar8 * -8 + 4);
      *puVar6 = *(undefined4 *)pcVar4;
      puVar6[(uint)bVar8 * -2 + 1] = *(undefined4 *)(pcVar4 + ((uint)bVar8 * -2 + 1) * 4);
      (puVar6 + (uint)bVar8 * -2 + 1)[(uint)bVar8 * -2 + 1] =
           *(undefined4 *)(pcVar4 + ((uint)bVar8 * -2 + 1) * 4 + ((uint)bVar8 * -2 + 1) * 4);
      dword_ebc74 = acStack_7c;
      pbVar7 = &unk_d0fbc + iVar3;
      local_1c = &unk_d0fa8 + iVar3;
      sprintf(acStack_b0,a2dS2d,(*local_1c + 5) * 5,(&off_d0880)[iVar3],(*pbVar7 + 5) * 5);
      dword_ebc78 = acStack_b0;
      pbVar5 = (byte *)((int)&byte_d0f94 + iVar3);
      if (iVar3 == 0) {
        ratings_confirm_dialog(pbVar5,aShootsLeftOrRight);
      }
      else {
        sprintf(acStack_48,(char *)&aD_c5283,(*pbVar5 + 5) * 5);
        local_18 = (*pbVar5 + 5) * 5;
        bVar1 = database_dialog_box(&dword_ebc74,2,acStack_48,2,0x1c,0xffffffff,(*local_1c + 5) * 5,
                                    (*pbVar7 + 5) * 5,0);
        uVar2 = (uint)bVar1;
        if (((uVar2 != 0xff) && ((*local_1c + 5) * 5 <= uVar2)) && (uVar2 <= (*pbVar7 + 5) * 5)) {
          bVar1 = bVar1 / 5 - 5;
          if ((int)uVar2 < local_18) {
            *pbVar5 = bVar1;
            if (((iVar3 != 0) && (iVar3 != 3)) && (iVar3 != 0xd)) {
              *unaff_EBX = *unaff_EBX + local_18 + (*pbVar5 + 5) * -5;
            }
          }
          else if (((iVar3 == 0) || (iVar3 == 3)) || (iVar3 == 0xd)) {
            *(char *)((int)local_28 + iVar3) = (char)((ulonglong)(longlong)(int)uVar2 / 5) + -5;
          }
          else if (*unaff_EBX < (int)(uVar2 - local_18)) {
            dword_ebc74 = aNotEnoughRatingUnits;
            message_dialog(0xffffffff,0xffffffff,&dword_ebc74,1,0,0,local_b4,unaff_EDX,0xffffffff);
          }
          else {
            *pbVar5 = bVar1;
            *unaff_EBX = *unaff_EBX - ((*pbVar5 + 5) * 5 - local_18);
          }
        }
      }
    }
    iVar3 = iVar3 + 1;
    iStack_14 = iStack_14 + 0xd;
  }
  return local_24;
}


// ================================================================================================
// goalie_ratings_edit @ 0x6ff69 [__watcall]
// ================================================================================================

int __watcall goalie_ratings_edit(int *param_1,int *unaff_EDX,int *unaff_EBX)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  char *pcVar4;
  byte *pbVar5;
  undefined4 *puVar6;
  byte *pbVar7;
  byte bVar8;
  int *apiStackY_204c [2015];
  int *local_b4;
  char acStack_b0 [52];
  char acStack_7c [4];
  undefined4 auStack_78 [12];
  char acStack_48 [32];
  undefined4 *local_28;
  int local_24;
  int local_20;
  byte *local_1c;
  int local_18;
  int iStack_14;
  
  bVar8 = 0;
  __CHK(0xd4);
  local_24 = 0;
  local_20 = 0;
  iStack_14 = 0x12a;
  iVar3 = 0;
  local_b4 = param_1;
  while ((iVar3 < 0xf && (local_24 == 0))) {
    if (iVar3 == 6) {
      local_20 = 0x136;
      iStack_14 = iStack_14 + -0x4e;
    }
    if ((((local_20 + 200 <= *local_b4) && (*local_b4 < local_20 + 0xe4)) &&
        (iStack_14 <= *unaff_EDX)) && (*unaff_EDX < iStack_14 + 0xd)) {
      local_24 = 1;
      local_28 = &byte_d0fe0;
      acStack_7c[0] = aEnterANewRating[0];
      acStack_7c[1] = aEnterANewRating[1];
      acStack_7c[2] = aEnterANewRating[2];
      acStack_7c[3] = aEnterANewRating[3];
      puVar6 = auStack_78 + (uint)bVar8 * -2 + (uint)bVar8 * -2 + 1;
      pcVar4 = aEnterANewRating + (uint)bVar8 * -8 + (uint)bVar8 * -8 + 8;
      auStack_78[(uint)bVar8 * -2] = *(undefined4 *)(aEnterANewRating + (uint)bVar8 * -8 + 4);
      *puVar6 = *(undefined4 *)pcVar4;
      puVar6[(uint)bVar8 * -2 + 1] = *(undefined4 *)(pcVar4 + ((uint)bVar8 * -2 + 1) * 4);
      (puVar6 + (uint)bVar8 * -2 + 1)[(uint)bVar8 * -2 + 1] =
           *(undefined4 *)(pcVar4 + ((uint)bVar8 * -2 + 1) * 4 + ((uint)bVar8 * -2 + 1) * 4);
      dword_ebc74 = acStack_7c;
      pbVar7 = &unk_d1000 + iVar3;
      local_1c = &unk_d0ff0 + iVar3;
      sprintf(acStack_b0,a2dS2d,(*local_1c + 5) * 5,(&off_d09db)[iVar3],(*pbVar7 + 5) * 5);
      dword_ebc78 = acStack_b0;
      pbVar5 = (byte *)((int)&byte_d0fe0 + iVar3);
      if (iVar3 == 0) {
        ratings_confirm_dialog(pbVar5,aGloveHandLeftOrRight);
      }
      else {
        sprintf(acStack_48,(char *)&aD_c5283,(*pbVar5 + 5) * 5);
        local_18 = (*pbVar5 + 5) * 5;
        bVar1 = database_dialog_box(&dword_ebc74,2,acStack_48,2,0x1c,0xffffffff,(*local_1c + 5) * 5,
                                    (*pbVar7 + 5) * 5,0);
        uVar2 = (uint)bVar1;
        if (((uVar2 != 0xff) && ((*local_1c + 5) * 5 <= uVar2)) && (uVar2 <= (*pbVar7 + 5) * 5)) {
          bVar1 = bVar1 / 5 - 5;
          if ((int)uVar2 < local_18) {
            *pbVar5 = bVar1;
            if ((iVar3 != 0) && (iVar3 != 8)) {
              *unaff_EBX = *unaff_EBX + local_18 + (*pbVar5 + 5) * -5;
            }
          }
          else if ((iVar3 == 0) || (iVar3 == 8)) {
            *(char *)((int)local_28 + iVar3) = (char)((ulonglong)(longlong)(int)uVar2 / 5) + -5;
          }
          else if (*unaff_EBX < (int)(uVar2 - local_18)) {
            dword_ebc74 = aNotEnoughRatingUnits;
            message_dialog(0xffffffff,0xffffffff,&dword_ebc74,1,0,0,local_b4,unaff_EDX,0xffffffff);
          }
          else {
            *pbVar5 = bVar1;
            *unaff_EBX = *unaff_EBX - ((*pbVar5 + 5) * 5 - local_18);
          }
        }
      }
    }
    iVar3 = iVar3 + 1;
    iStack_14 = iStack_14 + 0xd;
  }
  return local_24;
}


// ================================================================================================
// free_agent_card @ 0x7025b [__watcall]
// ================================================================================================

void __watcall free_agent_card(int param_1,undefined4 unaff_EDX)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined *puVar4;
  char *__src;
  byte bVar5;
  char acStackY_143a [1018];
  undefined2 auStackY_1040 [2028];
  char acStack_58 [4];
  undefined4 uStack_54;
  char acStack_50 [56];
  
  bVar5 = 0;
  __CHK(0x6c);
  setscreen(dword_ea2b4);
  puVar4 = install_path;
  if (byte_ed98f != '\x01') {
    puVar4 = (undefined *)0x0;
  }
  make_path(acStack_58,puVar4,aPrez2_c2d7d,0);
  uVar1 = loadshapes(acStack_58,0x20);
  iVar2 = locateshape(uVar1,&aPal_c2d83);
  memcpy(&palette_save,(void *)(iVar2 + 0x10),0x300);
  uVar3 = locateshape(uVar1,&aEa_c2d88);
  drawshape_remap_home(uVar3);
  freemem(uVar1);
  puVar4 = install_path;
  if (byte_ed908 != '\x01') {
    puVar4 = (undefined *)0x0;
  }
  make_path(acStack_58,puVar4,aPstatbar_c2d8d,0);
  uVar1 = loadshapes(acStack_58,0);
  uVar3 = locateshape(uVar1,&aPst2_c2d96);
  drawshape_remap_home(uVar3);
  freemem(uVar1);
  setfont(font_kaufm);
  set_text_colors(0x40,0x42);
  acStack_58[0] = aFreeAgent[0];
  acStack_58[1] = aFreeAgent[1];
  acStack_58[2] = aFreeAgent[2];
  acStack_58[3] = aFreeAgent[3];
  (&uStack_54)[(uint)bVar5 * -2] = *(undefined4 *)(aFreeAgent + (uint)bVar5 * -8 + 4);
  *(undefined2 *)(acStack_50 + ((uint)bVar5 * -4 + (uint)bVar5 * -4) * 2) =
       *(undefined2 *)(aFreeAgent + (uint)bVar5 * -8 + (uint)bVar5 * -8 + 8);
  (acStack_50 + ((uint)bVar5 * -4 + (uint)bVar5 * -4) * 2)[((uint)bVar5 * -2 + 1) * 2] =
       (aFreeAgent + (uint)bVar5 * -8 + (uint)bVar5 * -8 + 8)[((uint)bVar5 * -2 + 1) * 2];
  iVar2 = textwidth(acStack_58);
  print_outlined(0x140 - (iVar2 >> 1),0x52,acStack_58);
  set_text_colors(0x40,0x42);
  sprintf(acStack_58,aSS_c2da6,param_1 + 3,param_1 + 0x13);
  print_centered_shadow(0x98,acStack_58);
  sprintf(acStack_58,(char *)&aD_c2dac,(uint)*(byte *)(param_1 + 1));
  bVar5 = *(byte *)(param_1 + 2);
  if (bVar5 < 0x47) {
    if (bVar5 < 0x43) goto LAB_00070428;
    if (bVar5 < 0x44) {
      __src = aCenter_c2db0;
    }
    else {
      if (bVar5 != 0x44) goto LAB_00070428;
      __src = aDefence_c2db7;
    }
  }
  else if (bVar5 < 0x48) {
    __src = aGoalie_c2dd4;
  }
  else {
    if (bVar5 < 0x4c) goto LAB_00070428;
    if (bVar5 < 0x4d) {
      __src = aLeftWing_c2dbf;
    }
    else {
      if (bVar5 != 0x52) goto LAB_00070428;
      __src = aRightWing_c2dc9;
    }
  }
  strcat(acStack_58,__src);
LAB_00070428:
  print_centered_shadow(0xb2,acStack_58);
  setfont(font_main);
  if (*(char *)(param_1 + 2) == 'G') {
    free_agent_draw_glove();
  }
  else {
    free_agent_draw_shoots();
  }
  sprintf(acStack_58,aRatingUnitsAvailable3d,unaff_EDX);
  print_centered_shadow(0x110,acStack_58);
  buttons_draw_all(&a2_d0c5c,2);
  setdefaultscreen();
  drawshape_home(*(undefined4 *)(dword_ea2b4 + 0x2c));
  return;
}


// ================================================================================================
// ratings_edit_screen @ 0x704a6 [__watcall]
// ================================================================================================

undefined8 __watcall ratings_edit_screen(int param_1,undefined4 unaff_EDX)

{
  undefined *puVar1;
  uint uVar2;
  int extraout_ECX;
  int iVar3;
  undefined **ppuVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  int iVar7;
  byte bVar8;
  ulonglong uVar9;
  undefined *local_34;
  int local_30;
  undefined4 local_2c;
  undefined *local_28;
  int local_24;
  int local_20;
  uint uStack_1c;
  
  bVar8 = 0;
  __CHK(0x44);
  local_2c = 0x118;
  local_20 = 0;
  puVar1 = (undefined *)allocmem(&aTemp_c2df8,0x300,0x20);
  local_28 = puVar1;
  getpalette(0,0x100,puVar1);
  fade_palette(1,puVar1,0x10);
  if (*(char *)(param_1 + 2) == 'G') {
    local_2c = 0x104;
    byte_d0fe0 = unk_d0fd0;
    (&DAT_000d0fe4)[(uint)bVar8 * -2] = (&DAT_000d0fd4)[(uint)bVar8 * -2];
    (&DAT_000d0fe8)[(uint)bVar8 * -2 + (uint)bVar8 * -2] =
         (&DAT_000d0fd8)[(uint)bVar8 * -2 + (uint)bVar8 * -2];
    (&DAT_000d0fe8 + (uint)bVar8 * -2 + (uint)bVar8 * -2)[(uint)bVar8 * -2 + 1] =
         (&DAT_000d0fd8 + (uint)bVar8 * -2 + (uint)bVar8 * -2)[(uint)bVar8 * -2 + 1];
  }
  else {
    byte_d0f94 = unk_d0f80;
    puVar6 = &DAT_000d0f9c + (uint)bVar8 * -2 + (uint)bVar8 * -2;
    puVar5 = &DAT_000d0f88 + (uint)bVar8 * -2 + (uint)bVar8 * -2;
    (&DAT_000d0f98)[(uint)bVar8 * -2] = (&DAT_000d0f84)[(uint)bVar8 * -2];
    *puVar6 = *puVar5;
    puVar6[(uint)bVar8 * -2 + 1] = puVar5[(uint)bVar8 * -2 + 1];
    (puVar6 + (uint)bVar8 * -2 + 1)[(uint)bVar8 * -2 + 1] =
         (puVar5 + (uint)bVar8 * -2 + 1)[(uint)bVar8 * -2 + 1];
  }
  free_agent_card(param_1,local_2c);
  puVar1 = (undefined *)0xf0;
  iVar7 = 0x140;
  grabshape(dword_ebe9c,0x140,0xf0);
  drawshape_remap(pointer_shapes,0x140,0xf0);
  fade_palette(0,local_28,0x10);
  ppuVar4 = (undefined **)local_28;
  freemem(local_28);
  local_34 = (undefined *)0xf0;
  local_30 = 0x140;
  setmousepos(0x140,0xf0);
  (*(code *)mouse_update_callback)();
  uVar2 = event_queue_reset();
  do {
    uVar9 = (ulonglong)uVar2;
    uStack_1c = 0;
    do {
      uVar9 = event_queue_pop((int)uVar9,(int)(uVar9 >> 0x20),ppuVar4);
      iVar3 = (int)uVar9;
      if (iVar3 != 0) {
        uVar9 = (*ui_poll_callback)();
        uStack_1c = (uint)uVar9;
        iVar3 = extraout_ECX;
        ppuVar4 = &local_34;
      }
      uVar2 = (uint)uVar9;
    } while ((iVar3 != 0) && ((uStack_1c & 2) == 0));
    if ((uStack_1c & 2) == 0) {
      if ((iVar7 != local_30) || (puVar1 != local_34)) {
        drawshape(dword_ebe9c,iVar7,puVar1);
        grabshape(dword_ebe9c,local_30,local_34);
        ppuVar4 = (undefined **)pointer_shapes;
        goto LAB_000706bc;
      }
    }
    else {
      drawshape(dword_ebe9c,iVar7,puVar1);
      if (*(char *)(param_1 + 2) == 'G') {
        iVar7 = goalie_ratings_edit(&local_30,&local_34,&local_2c);
      }
      else {
        iVar7 = skater_ratings_edit(&local_30,&local_34,&local_2c);
      }
      if (iVar7 == 0) {
        local_24 = button_at(&a2_d0c5c,2,local_30,local_34,uStack_1c);
        if (-1 < local_24) {
          local_20 = 1;
        }
      }
      else {
        free_agent_card(param_1,local_2c);
      }
      grabshape(dword_ebe9c,local_30,local_34);
      ppuVar4 = (undefined **)local_34;
LAB_000706bc:
      uVar2 = drawshape_remap(pointer_shapes,local_30,local_34);
      puVar1 = local_34;
      iVar7 = local_30;
    }
    if (local_20 != 0) {
      return CONCAT44(unaff_EDX,local_24);
    }
  } while( true );
}


// ================================================================================================
// create_player_menu @ 0x706e2 [__watcall]
// ================================================================================================

void __watcall
create_player_menu(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX
                  )

{
  bool bVar1;
  int iVar2;
  size_t sVar3;
  undefined4 uVar4;
  undefined *puVar5;
  int iVar6;
  undefined4 *puVar7;
  int iVar8;
  undefined4 uVar9;
  char local_1ec [84];
  undefined auStack_198 [56];
  undefined uStack_160;
  undefined uStack_15f;
  char acStack_15e [17];
  char acStack_14d [17];
  int iStack_13c;
  int iStack_138;
  int iStack_134;
  undefined auStack_130 [4];
  undefined auStack_12c [48];
  undefined auStack_fc [44];
  undefined auStack_d0 [40];
  char acStack_a8 [32];
  char acStack_88 [32];
  int local_68 [6];
  undefined4 uStack_50;
  undefined auStack_4c [20];
  undefined auStack_38 [16];
  undefined local_28 [2];
  ushort local_26;
  ushort local_24;
  ushort uStack_22;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 uStack_14;
  
  __CHK(0x20c);
  local_18 = 0xffffffff;
  local_1c = 0xffffffff;
  local_20 = 0xffffffff;
  uStack_14 = 0xffffffff;
  iVar2 = _dos_getdiskfree(0,local_28,unaff_EBX,unaff_ECX,unaff_EBX,unaff_EDX);
  if (iVar2 != 0) {
    fatalerror(aErrorGettingDiskSpaceFre_c2dfd);
  }
  iVar8 = (uint)local_24 * (uint)uStack_22;
  local_68[0] = dword_d07d3 + 0x36;
  local_68[1] = dword_d07d7 + 0x2c;
  local_68[5] = dword_d07e7 + 0x14;
  local_68[3] = dword_d07df + 0x34;
  local_68[2] = dword_d07db;
  local_68[4] = dword_d07e3;
  uStack_50 = 0;
  iVar2 = 0;
  iVar6 = 0;
  do {
    iVar2 = iVar2 + (local_68[iVar6] + iVar8 + -1) / iVar8;
    iVar6 = iVar6 + 1;
  } while (iVar6 < 6);
  if ((int)(uint)local_26 < iVar2) {
    iVar6 = iVar2 * iVar8 >> 0x1f;
    sprintf(aXXXKbytesOfFreeDiskSpace_d1056,a3dKbytesOfFreeDiskSpace_c2e1c,
            (int)((iVar2 * iVar8 + iVar6 * -0x400) - (uint)(iVar6 << 9 < 0)) >> 10);
    uVar9 = 800;
    uVar4 = 3;
    puVar7 = &off_d1077;
LAB_00070819:
    message_dialog(0xffffffff,0xffffffff,puVar7,uVar4,0,0,unaff_EDX,unaff_EBX,uVar9);
    return;
  }
  if (0x1d < dword_d07b2) {
    dword_ebc74 = aNotEnoughSpaceToCreate;
    dword_ebc78 = aANewFreeAgent;
    uVar9 = 0xffffffff;
    uVar4 = 2;
    puVar7 = &dword_ebc74;
    goto LAB_00070819;
  }
  dword_ebc74 = aCreateAPlayerOrGoalie;
  iVar2 = message_dialog(0xffffffff,0xffffffff,&dword_ebc74,1,&unk_d0edd,2,unaff_EDX,unaff_EBX,
                         0xffffffff);
  if (iVar2 < 0) {
    return;
  }
  if (iVar2 == 0) {
    dword_ebc74 = aEnterTheNameOfTheNewPlay;
  }
  else {
    dword_ebc74 = aEnterTheNameOfTheNewGoal;
  }
  acStack_a8[0] = '\0';
  iVar6 = database_dialog_box(&dword_ebc74,1,acStack_a8,0x1f,0xba,0,0,0,0);
  if (iVar6 == -1) {
    return;
  }
  sVar3 = strlen(acStack_a8);
  if (sVar3 == 0) {
    return;
  }
  acStack_15e[1] = 0;
  acStack_14d[0] = '\0';
  player_name_normalize(acStack_a8,acStack_15e + 1);
  strcpy(acStack_88,acStack_15e + 1);
  strcat(acStack_88,&asc_c8111);
  strcat(acStack_88,acStack_14d);
  if (iVar2 == 0) {
    dword_ebc74 = aEnterAPositionFor;
    dword_ebc78 = acStack_88;
    dword_ebc7c = unk_c2ebf;
    acStack_a8[0] = '\0';
    do {
      iVar2 = database_dialog_box(&dword_ebc74,3,acStack_a8,1,0xe,0,0,0,0);
      if (iVar2 == -1) {
        return;
      }
      sVar3 = strlen(acStack_a8);
      if (sVar3 == 0) {
        return;
      }
      strupr(acStack_a8);
      if ((((acStack_a8[0] == 'C') || (acStack_a8[0] == 'L')) || (acStack_a8[0] == 'R')) ||
         (acStack_a8[0] == 'D')) {
        bVar1 = false;
      }
      else {
        bVar1 = true;
      }
    } while (bVar1);
    memcpy(acStack_15e,acStack_a8,1);
  }
  else {
    acStack_15e[0] = 'G';
  }
  iStack_134 = dword_d07d3;
  iStack_138 = dword_d07d7;
  iStack_13c = dword_d07e7;
  memset(auStack_130,0,4);
  dword_ebc74 = aEnterAJerseyNumberFor;
  dword_ebc78 = acStack_88;
  acStack_a8[0] = '\0';
  iVar2 = database_dialog_box(&dword_ebc74,2,acStack_a8,2,0x16,0xffffffff,0,99,0);
  if (iVar2 < 0) {
    return;
  }
  uStack_15f = (undefined)iVar2;
  uStack_160 = 0xff;
  uVar4 = allocmem(&aTemp_c2df8,0x300,0x20);
  getpalette(0,0x100,uVar4);
  iVar2 = ratings_edit_screen(&uStack_160);
  if (0 < iVar2) {
    fade_palette(1,uVar4,0x10);
    clearclip(0);
    dbedit_save_databases(&aTMP);
    make_path(&unk_ea968,0,off_c80d7,&aTMP);
    iVar2 = file_open_trunc(&unk_ea968,&local_18);
    if (iVar2 == 0) {
      make_path(&unk_ea968,0,off_c80eb,&aTMP);
      iVar2 = file_open_trunc(&unk_ea968,&local_1c);
    }
    if (iVar2 == 0) {
      make_path(&unk_ea968,0,off_c80db,&aTMP);
      iVar2 = file_open_trunc(&unk_ea968,&local_20);
    }
    if (iVar2 == 0) {
      make_path(&unk_ea968,0,off_c80df,&aTMP);
      iVar2 = file_open_trunc(&unk_ea968,&uStack_14);
    }
    if (iVar2 == 0) {
      if (acStack_15e[0] == 'G') {
        memset(auStack_198,0,0x36);
        memset(auStack_fc,0,0x2c);
        iVar2 = file_write(local_1c,auStack_198,iStack_134,0x36);
        if (iVar2 == 0) {
          iVar2 = 0;
          do {
            auStack_38[*(int *)(&unk_d0a04 + iVar2) >> 0x18] =
                 *(undefined *)((int)&byte_d0fe0 + iVar2);
            iVar2 = iVar2 + 1;
          } while (iVar2 < 0xb);
          iVar2 = file_write(local_20,auStack_fc,iStack_138,0x2c);
        }
        if (iVar2 == 0) {
          uVar9 = 0x10;
          puVar5 = auStack_38;
          goto LAB_00070d58;
        }
      }
      else {
        memset(auStack_12c,0,0x2f);
        memset(auStack_d0,0,0x28);
        iVar2 = file_write(local_1c,auStack_12c,iStack_134,0x2f);
        if (iVar2 == 0) {
          iVar2 = 0;
          do {
            auStack_4c[*(int *)(&unk_d08b9 + iVar2) >> 0x18] =
                 *(undefined *)((int)&byte_d0f94 + iVar2);
            iVar2 = iVar2 + 1;
          } while (iVar2 < 0xf);
          create_player_form(&uStack_160,auStack_4c,auStack_d0);
          iVar2 = file_write(local_20,auStack_d0,iStack_138,0x28);
        }
        if (iVar2 == 0) {
          uVar9 = 0x14;
          puVar5 = auStack_4c;
LAB_00070d58:
          iVar2 = file_write(uStack_14,puVar5,iStack_13c,uVar9);
        }
      }
      if (iVar2 == 0) {
        iVar2 = file_write(local_18,&uStack_160,dword_d07df,0x34);
      }
    }
    file_close(&uStack_14);
    file_close(&local_20);
    file_close(&local_1c);
    file_close(&local_18);
    if (iVar2 == 0) {
      player_temp_file();
      dbedit_free_lists(0);
      dbedit_free_lists(1);
    }
    dbedit_remove_temp_files();
    if (iVar2 == 0) {
      dword_ebc68 = 1;
      goto LAB_00070e66;
    }
    dword_ebc74 = aErrorWhileMakingNewDatab;
    strcpy(local_1ec,aNewPlayer);
    strcat(local_1ec,aNotAddedToDatabases);
    fade_palette(0,uVar4,0x10);
    dword_ebc78 = local_1ec;
    message_dialog(0xffffffff,0xffffffff,&dword_ebc74,2,0,0,unaff_EDX,unaff_EBX,0xffffffff);
  }
  fade_palette(1,uVar4,0x10);
LAB_00070e66:
  player_ratings_card();
  fade_palette(0,uVar4,0x10);
  freemem(uVar4);
  return;
}


// ================================================================================================
// free_agent_move_dialog @ 0x70e8d [__watcall]
// ================================================================================================

void __watcall free_agent_move_dialog(int *param_1,undefined4 unaff_EDX,undefined4 unaff_EBX)

{
  uint uVar1;
  undefined *puVar2;
  int iVar3;
  int iVar4;
  char acStack_44 [32];
  int local_24;
  uint local_20;
  int local_1c;
  int local_18;
  undefined4 uStack_14;
  
  __CHK(100);
  local_1c = 0;
  local_24 = 0;
  local_18 = 0;
  uVar1 = (uint)(*param_1 != 3);
  local_20 = (uint)(uVar1 == 0);
  iVar4 = 0;
  do {
    if (((&unk_eaf80)[uVar1 * 0x1c + iVar4] != '\0') &&
       (local_24 = local_24 + 1, dword_d07b2 < 0x1e)) {
      local_18 = local_18 + 1;
      uStack_14 = *(undefined4 *)(&unk_ea994 + iVar4 * 0x1b + uVar1 * 0x2f4);
      puVar2 = (undefined *)dbedit_key_ptr();
      dword_ebc74 = (char *)&aMove;
      strcpy(acStack_44,puVar2 + 3);
      strcat(acStack_44,&asc_c8111);
      strcat(acStack_44,puVar2 + 0x13);
      dword_ebc78 = acStack_44;
      dword_ebc7c = aToFreeAgentList;
      iVar3 = message_dialog(0xffffffff,0xffffffff,&dword_ebc74,3,&unk_c7733,2,unaff_EDX,unaff_EBX,
                             0xffffffff);
      if ((iVar3 == 1) && (local_1c = iVar3, (byte)(&byte_d079e)[uVar1] < 0x1a)) {
        *puVar2 = 0xff;
        dbedit_team_scan_players((&byte_d079e)[uVar1],uStack_14);
      }
    }
    iVar4 = iVar4 + 1;
  } while (iVar4 < 0x1c);
  if (local_24 != local_18) {
    dword_ebc74 = aThereIsNotEnoughSpace;
    dword_ebc78 = aInTheFreeAgentList;
    dword_ebc7c = aForAllSelectedPlayers;
    message_dialog(0xffffffff,0xffffffff,&dword_ebc74,3,0,0,unaff_EDX,unaff_EBX,0xffffffff);
  }
  if (local_1c != 0) {
    dword_ebc68 = 1;
    dbedit_free_lists(uVar1);
    if ((&byte_d07a8)[local_20] == '\x01') {
      dbedit_free_lists();
    }
    player_ratings_card();
  }
  return;
}


// ================================================================================================
// dbedit_team_scan_players @ 0x71043 [__watcall]
// ================================================================================================

void __watcall dbedit_team_scan_players(undefined param_1)

{
  int iVar1;
  int iVar2;
  char *pcVar3;
  int iVar4;
  undefined uVar5;
  char cVar7;
  uint uVar6;
  undefined8 uVar8;
  undefined8 uVar9;
  
  __CHK(0x14);
  uVar8 = dbedit_teams_record(param_1);
  iVar1 = dbedit_key_ptr((int)((ulonglong)uVar8 >> 0x20));
  for (uVar6 = 0xff00; (cVar7 = (char)(uVar6 >> 8), (byte)uVar6 < 0x1c && (cVar7 == -1));
      uVar6 = CONCAT31((int3)(uVar6 >> 8),(char)uVar6 + '\x01')) {
    iVar4 = (uVar6 & 0xff) * 4 + (int)uVar8;
    uVar9 = dbedit_key_ptr(*(undefined4 *)(iVar4 + 0x4c));
    uVar6 = (uint)((ulonglong)uVar9 >> 0x20);
    iVar2 = (int)uVar9;
    if ((*(int *)(iVar1 + 0x24) == *(int *)(iVar2 + 0x24)) &&
       ((*(int *)(iVar1 + 0x28) == *(int *)(iVar2 + 0x28) &&
        (*(int *)(iVar1 + 0x2c) == *(int *)(iVar2 + 0x2c))))) {
      dword_d07b2 = dword_d07b2 + 1;
      *(undefined4 *)(iVar4 + 0x4c) = 0xffffffff;
      uVar5 = (undefined)((ulonglong)uVar9 >> 0x20);
      uVar6 = (uint)CONCAT11(uVar5,uVar5);
    }
  }
  if (cVar7 != -1) {
    for (uVar6 = uVar6 & 0xffffff00; (byte)uVar6 < 0x30;
        uVar6 = CONCAT31((int3)(uVar6 >> 8),(byte)uVar6 + 1)) {
      pcVar3 = (char *)((uVar6 & 0xff) + (int)uVar8 + 0xbc);
      if ((char)(uVar6 >> 8) == *pcVar3) {
        *pcVar3 = 'd';
      }
    }
  }
  return;
}


// ================================================================================================
// player_temp_file @ 0x710d8 [__watcall]
// ================================================================================================

void __watcall
player_temp_file(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  __CHK(0x18);
  dbedit_free_databases();
  make_path(&unk_ea968,0,off_c80eb,&aTMP,unaff_EDX,unaff_ECX,unaff_EBX);
  dword_d07bb = loadfile(&unk_ea968,0x20);
  dword_d07d3 = filesize(&unk_ea968);
  make_path(&unk_ea968,0,off_c80db,&aTMP);
  dword_d07bf = loadfile(&unk_ea968,0x20);
  dword_d07d7 = filesize(&unk_ea968);
  make_path(&unk_ea968,0,off_c80e3,&aTMP);
  dword_d07c3 = loadfile(&unk_ea968,0x20);
  dword_d07db = filesize(&unk_ea968);
  make_path(&unk_ea968,0,off_c80d7,&aTMP);
  dword_d07c7 = loadfile(&unk_ea968,0x20);
  dword_d07df = filesize(&unk_ea968);
  make_path(&unk_ea968,0,off_c80e7,&aTMP);
  dword_d07cb = loadfile(&unk_ea968,0x20);
  dword_d07e3 = filesize(&unk_ea968);
  make_path(&unk_ea968,0,off_c80df,&aTMP);
  dword_d07cf = loadfile(&unk_ea968,0x20);
  dword_d07e7 = filesize(&unk_ea968);
  return;
}


// ================================================================================================
// dbedit_remove_temp_files @ 0x7125c [__watcall]
// ================================================================================================

void __watcall
dbedit_remove_temp_files(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  __CHK(0x10);
  make_path(&unk_ea968,0,off_c80eb,&aTMP,unaff_EDX,unaff_ECX,unaff_EBX);
  remove_file(&unk_ea968);
  make_path(&unk_ea968,0,off_c80db,&aTMP);
  remove_file(&unk_ea968);
  make_path(&unk_ea968,0,off_c80e3,&aTMP);
  remove_file(&unk_ea968);
  make_path(&unk_ea968,0,off_c80d7,&aTMP);
  remove_file(&unk_ea968);
  make_path(&unk_ea968,0,off_c80e7,&aTMP);
  remove_file(&unk_ea968);
  make_path(&unk_ea968,0,off_c80df,&aTMP);
  remove_file(&unk_ea968);
  return;
}


// ================================================================================================
// roster_count_check @ 0x71333 [__watcall]
// ================================================================================================

void __watcall roster_count_check(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX)

{
  uint *puVar1;
  byte bVar2;
  byte bVar3;
  int iVar4;
  undefined4 uVar5;
  byte *pbVar6;
  byte bVar7;
  int iVar8;
  char *pcVar9;
  byte *pbVar10;
  int iVar11;
  int iVar12;
  undefined4 *puVar13;
  char *pcVar14;
  undefined4 *puVar15;
  undefined8 uVar16;
  char acStack_f4 [84];
  undefined4 uStack_a0;
  byte abStack_84 [28];
  byte abStack_68 [28];
  byte abStack_4c [28];
  byte abStack_30 [28];
  int iStack_14;
  
  __CHK(0x114);
  iVar8 = 0;
  iStack_14 = 0;
  iVar12 = 0;
  iVar4 = 0;
  iVar11 = 0;
  do {
    if ((&unk_eaf80)[iVar11] != '\0') {
      iStack_14 = iStack_14 + 1;
    }
    if ((&unk_eaf9c)[iVar11] != '\0') {
      iVar8 = iVar8 + 1;
    }
    iVar11 = iVar11 + 1;
  } while (iVar11 < 0x19);
  iVar11 = 0;
  do {
    if ((&unk_eaf99)[iVar11] != '\0') {
      iVar12 = iVar12 + 1;
    }
    if ((&unk_eafb5)[iVar11] != '\0') {
      iVar4 = iVar4 + 1;
    }
    iVar11 = iVar11 + 1;
  } while (iVar11 < 3);
  if ((iVar8 == iStack_14) && (iVar12 == iVar4)) {
    iVar4 = 0;
    iVar8 = 0;
    iVar11 = 0;
    do {
      if ((&unk_eaf80)[iVar11] != '\0') {
        abStack_4c[iVar4] = (&unk_ea992)[iVar11 * 0x1b];
        abStack_84[iVar4] = (byte)iVar11;
        iVar4 = iVar4 + 1;
      }
      if ((&unk_eaf9c)[iVar11] != '\0') {
        abStack_30[iVar8] = (&unk_eac86)[iVar11 * 0x1b];
        abStack_68[iVar8] = (byte)iVar11;
        iVar8 = iVar8 + 1;
      }
      iVar11 = iVar11 + 1;
    } while (iVar11 < 0x1c);
    iStack_14 = iStack_14 + iVar12;
    for (iVar4 = 0; iVar4 < iStack_14; iVar4 = iVar4 + 1) {
      uVar5 = dbedit_key_ptr(*(undefined4 *)(dword_eaf78 + 0x4c + (uint)abStack_4c[iVar4] * 4));
      uVar16 = dbedit_key_ptr(*(undefined4 *)((uint)abStack_30[iVar4] * 4 + 0x4c + dword_eaf7c),uVar5);
      pbVar10 = (byte *)((ulonglong)uVar16 >> 0x20);
      pbVar6 = (byte *)uVar16;
      bVar7 = *pbVar6;
      bVar2 = *pbVar10;
      *pbVar10 = bVar2 ^ bVar7;
      bVar7 = *pbVar6 ^ bVar2 ^ bVar7;
      *pbVar6 = bVar7;
      *pbVar10 = *pbVar10 ^ bVar7;
      puVar1 = (uint *)(dword_eaf78 + (uint)abStack_4c[iVar4] * 4 + 0x4c);
      *puVar1 = *puVar1 ^ *(uint *)((uint)abStack_30[iVar4] * 4 + 0x4c + dword_eaf7c);
      puVar1 = (uint *)(dword_eaf7c + (uint)abStack_30[iVar4] * 4 + 0x4c);
      *puVar1 = *puVar1 ^ *(uint *)(dword_eaf78 + 0x4c + (uint)abStack_4c[iVar4] * 4);
      puVar1 = (uint *)(dword_eaf78 + (uint)abStack_4c[iVar4] * 4 + 0x4c);
      *puVar1 = *puVar1 ^ *(uint *)((uint)abStack_30[iVar4] * 4 + 0x4c + dword_eaf7c);
      bVar3 = abStack_84[iVar4];
      iVar8 = (uint)bVar3 * 0x1b;
      iVar11 = (uint)abStack_68[iVar4] * 0x1b;
      bVar7 = (&unk_eac86)[iVar11];
      bVar2 = (&unk_ea992)[iVar8];
      (&unk_ea992)[iVar8] = bVar2 ^ bVar7;
      bVar7 = (&unk_eac86)[iVar11] ^ bVar2 ^ bVar7;
      (&unk_eac86)[iVar11] = bVar7;
      (&unk_ea992)[iVar8] = (&unk_ea992)[iVar8] ^ bVar7;
      puVar13 = (undefined4 *)(&unk_ea990 + iVar8);
      puVar15 = &uStack_a0;
      for (iVar12 = 6; iVar12 != 0; iVar12 = iVar12 + -1) {
        *puVar15 = *puVar13;
        puVar13 = puVar13 + 1;
        puVar15 = puVar15 + 1;
      }
      *(undefined2 *)puVar15 = *(undefined2 *)puVar13;
      *(undefined *)((int)puVar15 + 2) = *(undefined *)((int)puVar13 + 2);
      puVar13 = (undefined4 *)(&unk_eac84 + iVar11);
      puVar15 = (undefined4 *)(&unk_ea990 + iVar8);
      for (iVar12 = 6; iVar12 != 0; iVar12 = iVar12 + -1) {
        *puVar15 = *puVar13;
        puVar13 = puVar13 + 1;
        puVar15 = puVar15 + 1;
      }
      *(undefined2 *)puVar15 = *(undefined2 *)puVar13;
      *(undefined *)((int)puVar15 + 2) = *(undefined *)((int)puVar13 + 2);
      puVar13 = &uStack_a0;
      puVar15 = (undefined4 *)(&unk_eac84 + iVar11);
      for (iVar8 = 6; iVar8 != 0; iVar8 = iVar8 + -1) {
        *puVar15 = *puVar13;
        puVar13 = puVar13 + 1;
        puVar15 = puVar15 + 1;
      }
      *(undefined2 *)puVar15 = *(undefined2 *)puVar13;
      *(undefined *)((int)puVar15 + 2) = *(undefined *)((int)puVar13 + 2);
      jersey_number_prompt(0,(uint)bVar3);
      jersey_number_prompt(1,abStack_68[iVar4]);
      iVar11 = dword_eaf78 + 0xbc;
      iVar8 = 0;
      do {
        pbVar6 = (byte *)(iVar11 + iVar8);
        if (*pbVar6 == abStack_4c[iVar4]) {
          *pbVar6 = 100;
        }
        iVar8 = iVar8 + 1;
      } while (iVar8 < 0x30);
      iVar11 = dword_eaf7c + 0xbc;
      iVar8 = 0;
      do {
        pbVar6 = (byte *)(iVar11 + iVar8);
        if (*pbVar6 == abStack_30[iVar4]) {
          *pbVar6 = 100;
        }
        iVar8 = iVar8 + 1;
      } while (iVar8 < 0x30);
    }
    dword_ebc68 = 1;
    dbedit_free_lists(0);
    dbedit_free_lists(1);
    player_ratings_card();
    return;
  }
  pcVar9 = aTheNumberOfSelected;
  pcVar14 = acStack_f4;
  for (iVar11 = 6; iVar11 != 0; iVar11 = iVar11 + -1) {
    *(undefined4 *)pcVar14 = *(undefined4 *)pcVar9;
    pcVar9 = pcVar9 + 4;
    pcVar14 = pcVar14 + 4;
  }
  if ((iVar8 == iStack_14) || (iVar12 == iVar4)) {
    if (iVar8 == iStack_14) {
      if (iVar12 == iVar4) goto LAB_000713eb;
      pcVar9 = aGoalies;
    }
    else {
      pcVar9 = aPlayers;
    }
  }
  else {
    pcVar9 = aPlayersAndGoalies;
  }
  strcat(acStack_f4,pcVar9);
LAB_000713eb:
  dword_ebc74 = acStack_f4;
  dword_ebc78 = aMustBeTheSameOnBothTeams;
  message_dialog(0xffffffff,0xffffffff,&dword_ebc74,2,0,0,unaff_EDX,unaff_EBX,0xffffffff);
  return;
}


// ================================================================================================
// dbedit_find_player_by_name @ 0x71690 [__watcall]
// ================================================================================================

void __watcall dbedit_find_player_by_name(char *param_1,char *unaff_EDX,int unaff_EBX)

{
  int iVar1;
  int iVar2;
  char acStackY_30 [16];
  char acStackY_20 [16];
  
  __CHK(0x34);
  if ((&byte_d07a8)[unaff_EBX] == '\x01') {
    for (iVar2 = 0; iVar2 < dword_d07b2; iVar2 = iVar2 + 1) {
      *(undefined *)(iVar2 + dword_d07ae) = 0;
    }
    if (dword_d0c20 != 0) {
      dword_ebca4 = -1;
    }
    for (iVar2 = 0; iVar2 < dword_d07b2; iVar2 = iVar2 + 1) {
      player_name_normalize(iVar2 * 0x1b + dword_d07aa + 8,acStackY_20,acStackY_30);
      strlwr(acStackY_20);
      strlwr(acStackY_30);
      iVar1 = strcmp(param_1,acStackY_20);
      if ((((iVar1 == 0) && (iVar1 = strcmp(unaff_EDX,acStackY_30), iVar1 == 0)) ||
          ((*unaff_EDX == '\0' && (iVar1 = strcmp(param_1,acStackY_30), iVar1 == 0)))) &&
         ((*(byte *)(iVar2 + dword_d07ae) = ~*(byte *)(iVar2 + dword_d07ae), dword_d0c20 != 0 &&
          (dword_ebca4 == -1)))) {
        dword_ebca4 = iVar2;
      }
    }
  }
  else {
    iVar2 = 0;
    do {
      (&unk_eaf80)[unaff_EBX * 0x1c + iVar2] = 0;
      iVar2 = iVar2 + 1;
    } while (iVar2 < 0x1c);
    iVar2 = 0;
    do {
      iVar1 = dbedit_key_ptr(*(undefined4 *)(&unk_ea994 + iVar2 * 0x1b + unaff_EBX * 0x2f4));
      strcpy(acStackY_20,(char *)(iVar1 + 3));
      strcpy(acStackY_30,(char *)(iVar1 + 0x13));
      strlwr(acStackY_20);
      strlwr(acStackY_30);
      iVar1 = strcmp(param_1,acStackY_20);
      if (((iVar1 == 0) && (iVar1 = strcmp(unaff_EDX,acStackY_30), iVar1 == 0)) ||
         ((*unaff_EDX == '\0' && (iVar1 = strcmp(param_1,acStackY_30), iVar1 == 0)))) {
        (&unk_eaf80)[unaff_EBX * 0x1c + iVar2] = ~(&unk_eaf80)[unaff_EBX * 0x1c + iVar2];
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 < 0x1c);
  }
  return;
}


// ================================================================================================
// dbedit_setup_team_menu @ 0x7183d [__watcall]
// ================================================================================================

void __watcall dbedit_setup_team_menu(int param_1,uint unaff_EDX)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  __CHK(0x14);
  uVar3 = (uint)(byte)(&byte_d079e)[param_1];
  if (uVar3 == 0xff) {
    funcptr_d01cd = dbedit_free_agents;
    funcptr_d028d = dbedit_free_agents;
  }
  else {
    iVar1 = *(int *)(&unk_c5519 + uVar3 * 4) >> 1;
    if (iVar1 == 4) {
      iVar1 = 3;
    }
    iVar2 = 0;
    do {
      if ((byte)(&unk_c83c3)[iVar1 * 7 + iVar2] == uVar3) break;
      iVar2 = iVar2 + 1;
    } while (iVar2 < 7);
    *(code **)((&off_d0151)[iVar1 * 8] + iVar2 * 0x20 + 0x14) = dbedit_select_team;
    *(code **)((&off_d0211)[iVar1 * 8] + iVar2 * 0x20 + 0x14) = dbedit_select_team;
  }
  if (unaff_EDX == 100) {
    if (param_1 == 0) {
      funcptr_d0391 = (undefined *)0x0;
    }
    else {
      funcptr_d0411 = (undefined *)0x0;
    }
    funcptr_d01cd = (undefined *)0x0;
    funcptr_d028d = (undefined *)0x0;
    return;
  }
  iVar1 = *(int *)(&unk_c5519 + unaff_EDX * 4) >> 1;
  if (iVar1 == 4) {
    iVar1 = 3;
  }
  iVar2 = 0;
  do {
    if ((byte)(&unk_c83c3)[iVar1 * 7 + iVar2] == unaff_EDX) break;
    iVar2 = iVar2 + 1;
  } while (iVar2 < 7);
  *(undefined4 *)((&off_d0151)[iVar1 * 8] + iVar2 * 0x20 + 0x14) = 0;
  *(undefined4 *)((&off_d0211)[iVar1 * 8] + iVar2 * 0x20 + 0x14) = 0;
  if (param_1 == 0) {
    funcptr_d0391 = dbedit_edit_team_lines;
    return;
  }
  funcptr_d0411 = dbedit_edit_team_lines;
  return;
}


// ================================================================================================
// roster_edit_screen @ 0x71961 [__watcall]
// ================================================================================================

void __watcall roster_edit_screen(int *param_1,undefined4 unaff_EDX,undefined4 unaff_EBX)

{
  int iVar1;
  int iVar2;
  undefined1 *puVar3;
  int iVar4;
  char *pcVar5;
  int iVar6;
  uint uVar7;
  undefined4 auStack_1c8 [28];
  undefined auStack_158 [112];
  uint auStack_e8 [27];
  char acStack_7c [32];
  char acStack_5c [16];
  char acStack_4c [16];
  char local_3c [16];
  char acStack_2c [16];
  code *pcStack_1c;
  uint local_18;
  code *pcStack_14;
  
  __CHK(0x1e8);
  pcStack_14 = (code *)(uint)(*param_1 != 1);
  pcStack_1c = (code *)(uint)(pcStack_14 == (code *)0x0);
  acStack_7c[0] = '\0';
  dword_ebc74 = aEnterNameOfPlayerToFind;
  database_dialog_box(&dword_ebc74,1,acStack_7c,0x1f,0xba,0,0,0,0);
  strlwr(acStack_7c);
  player_name_normalize(acStack_7c,acStack_2c);
  if ((acStack_5c[0] != '\0') || (acStack_2c[0] != '\0')) {
    iVar6 = 0;
    uVar7 = 0;
    do {
      iVar1 = dbedit_teams_record(uVar7);
      auStack_e8[iVar6] = 0xffffffff;
      iVar4 = 0;
      while ((iVar4 < 0x1c && ((int)auStack_e8[iVar6] < 0))) {
        iVar2 = dbedit_key_ptr(*(undefined4 *)(iVar1 + 0x4c + iVar4 * 4));
        strcpy(acStack_4c,(char *)(iVar2 + 3));
        strcpy(local_3c,(char *)(iVar2 + 0x13));
        strlwr(acStack_4c);
        strlwr(local_3c);
        iVar2 = strcmp(acStack_2c,acStack_4c);
        if (((iVar2 == 0) && (iVar2 = strcmp(acStack_5c,local_3c), iVar2 == 0)) ||
           ((acStack_5c[0] == '\0' && (iVar2 = strcmp(acStack_2c,local_3c), iVar2 == 0)))) {
          auStack_e8[iVar6] = uVar7;
          iVar6 = iVar6 + 1;
        }
        iVar4 = iVar4 + 1;
      }
      uVar7 = uVar7 + 1;
    } while ((int)uVar7 < 0x1a);
    uVar7 = dword_d07df / 0x34;
    auStack_e8[iVar6] = 0xffffffff;
    iVar1 = 0;
    while ((iVar1 < (int)uVar7 && ((int)auStack_e8[iVar6] < 0))) {
      pcVar5 = (char *)(dword_d07c7 + iVar1 * 0x34);
      if (*pcVar5 == -1) {
        strcpy(acStack_4c,pcVar5 + 3);
        strcpy(local_3c,pcVar5 + 0x13);
        strlwr(acStack_4c);
        strlwr(local_3c);
        iVar4 = strcmp(acStack_2c,acStack_4c);
        if (((iVar4 == 0) && (iVar4 = strcmp(acStack_5c,local_3c), iVar4 == 0)) ||
           ((acStack_5c[0] == '\0' && (iVar4 = strcmp(acStack_2c,local_3c), iVar4 == 0)))) {
          auStack_e8[iVar6] = 100;
          iVar6 = iVar6 + 1;
        }
      }
      iVar1 = iVar1 + 1;
    }
    if (iVar6 < 1) {
      dword_ebc74 = acStack_7c;
      dword_ebc78 = aDoesNotExist;
      message_dialog(0xffffffff,0xffffffff,&dword_ebc74,2,0,0,unaff_EDX,unaff_EBX,0xffffffff);
    }
    else {
      if (1 < iVar6) {
        iVar1 = 0;
        for (iVar4 = 0; iVar4 < iVar6; iVar4 = iVar4 + 1) {
          uVar7 = auStack_e8[iVar4];
          if (uVar7 == 100) {
            auStack_1c8[iVar1] = aFreeAgentList;
          }
          else if ((int)uVar7 < 0x1a) {
            auStack_1c8[iVar1] = (&off_c54a9)[uVar7];
          }
          iVar1 = iVar1 + 1;
        }
        iVar6 = listbox_dialog(auStack_1c8,iVar6,aChooseWhichTeamToDisplay,0,0,auStack_158);
        auStack_e8[0] = auStack_e8[iVar6];
      }
      local_18 = auStack_e8[0];
      if (auStack_e8[0] == 100) {
        if ((&byte_d07a8)[(int)pcStack_1c] == '\x01') {
          dword_ebc74 = acStack_7c;
          dword_ebc78 = aIsAlreadyDisplayedOn;
          if (pcStack_14 == (code *)0x0) {
            dword_ebc7c = aRoster2;
          }
          else {
            dword_ebc7c = aRoster1;
          }
          message_dialog(0xffffffff,0xffffffff,&dword_ebc74,3,0,0,unaff_EDX,unaff_EBX,0xffffffff);
        }
        else if ((&byte_d07a8)[(int)pcStack_14] != '\x01') {
          dbedit_setup_team_menu(pcStack_14,100);
          (&byte_d07a8)[(int)pcStack_14] = 1;
          dbedit_free_lists();
          (&byte_d079e)[(int)pcStack_14] = 0xff;
        }
      }
      else if ((byte)(&byte_d079e)[(int)pcStack_1c] == auStack_e8[0]) {
        dword_ebc74 = acStack_7c;
        dword_ebc78 = aIsAlreadyDisplayedOn;
        if (pcStack_14 == (code *)0x0) {
          dword_ebc7c = aRoster2;
        }
        else {
          dword_ebc7c = aRoster1;
        }
        message_dialog(0xffffffff,0xffffffff,&dword_ebc74,3,0,0,unaff_EDX,unaff_EBX,0xffffffff);
        pcStack_14 = pcStack_1c;
      }
      else if ((byte)(&byte_d079e)[(int)pcStack_14] != auStack_e8[0]) {
        dbedit_setup_team_menu(pcStack_14,auStack_e8[0]);
        (&byte_d07a8)[(int)pcStack_14] = 0;
        (&byte_d079e)[(int)pcStack_14] = (undefined)local_18;
        dbedit_free_lists(pcStack_14);
      }
      dbedit_find_player_by_name(acStack_2c,acStack_5c,pcStack_14);
      player_ratings_card();
      puVar3 = dword_d07ae;
      if ((&byte_d07a8)[(int)pcStack_14] != '\x01') {
        puVar3 = &unk_eaf80 + (int)pcStack_14 * 0x1c;
      }
      iVar6 = dbedit_find_player_entry(puVar3);
      if (iVar6 < 1) {
        if (pcStack_14 == (code *)0x0) {
          dword_d0331 = pcStack_14;
          dword_d0351 = pcStack_14;
        }
        else {
          dword_d03b1 = (code *)0x0;
          dword_d03d1 = (code *)0x0;
        }
      }
      else if (pcStack_14 == (code *)0x0) {
        if ((byte_d07a8 != '\x01') && (dword_d07b2 < 0x1e)) {
          dword_d0331 = free_agent_move_dialog;
        }
        if (byte_d07a9 != '\x01') {
          dword_d0351 = roster_move_players;
        }
      }
      else {
        if ((byte_d07a9 != '\x01') && (dword_d07b2 < 0x1e)) {
          dword_d03b1 = free_agent_move_dialog;
        }
        if (byte_d07a8 != '\x01') {
          dword_d03d1 = roster_move_players;
        }
      }
    }
  }
  return;
}


// ================================================================================================
// database_dialog_box @ 0x71f0c [__watcall]
// ================================================================================================

int __watcall
database_dialog_box(int param_1,int unaff_EDX,char *unaff_EBX,int unaff_ECX,int param_5,int param_6,
                   int param_7,int param_8,int param_9)

{
  bool bVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  size_t sVar6;
  int iVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  undefined4 *puVar11;
  byte bVar12;
  char acStack_74 [52];
  int iStack_40;
  undefined4 local_3c;
  int local_38;
  int local_34;
  int local_30;
  undefined4 *local_2c;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_10;
  
  bVar12 = 0;
  __CHK(0x90);
  local_10 = -1;
  local_34 = 0;
  local_38 = 0;
  local_24 = byte_d42c3 + 2;
  iVar5 = unaff_EDX;
  for (iVar7 = 0; iVar7 < unaff_EDX; iVar7 = iVar7 + 1) {
    dialog_measure_line(*(undefined4 *)(iVar7 * 4 + param_1),&local_34,&local_38,local_24);
  }
  local_20 = param_5 + 8;
  if (local_34 < local_20) {
    local_34 = local_20;
  }
  local_1c = (0x280 - (local_34 + 0x10)) / 2;
  local_30 = (0x1e0 - (local_38 + 0x1f)) / 2;
  local_28 = ((int)((local_1c + (local_1c >> 0x1f) * -4) - (uint)((local_1c >> 0x1f) << 1 < 0)) >> 2
             ) << 2;
  iVar7 = local_34 + 0x16 >> 0x1f;
  iVar4 = (int)((local_34 + 0x16 + iVar7 * -4) - (uint)(iVar7 << 1 < 0)) >> 2;
  iStack_40 = iVar4 << 2;
  iVar7 = local_38 + 0x23;
  local_38 = local_38 + 0x1f;
  local_34 = local_34 + 0x10;
  local_18 = local_30;
  local_2c = (undefined4 *)allocmem(aDSBOX,(iVar4 * 0x10 + 4) * iVar7 + 0x11,0);
  puVar9 = local_2c + (uint)bVar12 * -2 + 1;
  puVar11 = pointer_shapes + (uint)bVar12 * -2 + 1;
  *local_2c = *pointer_shapes;
  puVar10 = puVar9 + (uint)bVar12 * -2 + 1;
  puVar8 = puVar11 + (uint)bVar12 * -2 + 1;
  *puVar9 = *puVar11;
  *puVar10 = *puVar8;
  puVar10[(uint)bVar12 * -2 + 1] = puVar8[(uint)bVar12 * -2 + 1];
  *(undefined *)(puVar10 + (uint)bVar12 * -2 + 1 + (uint)bVar12 * -2 + 1) =
       *(undefined *)(puVar8 + (uint)bVar12 * -2 + 1 + (uint)bVar12 * -2 + 1);
  *(short *)(local_2c + 1) = (short)iStack_40 + 1;
  *(short *)((int)local_2c + 6) = (short)local_38 + 4;
  grabshape(local_2c,local_28,local_18);
  draw_bevel_box_b(local_1c,local_18,local_1c + local_34 + -1,local_18 + local_38 + -1,0);
  local_18 = local_18 + 8;
  for (iVar7 = 0; uVar3 = dword_d0b1e, uVar2 = dword_d0b1a, iVar7 < iVar5; iVar7 = iVar7 + 1) {
    puVar11 = (undefined4 *)(iVar7 * 4 + param_1);
    iVar4 = textwidth(*puVar11);
    print_text_at((local_34 - iVar4) / 2 + local_1c,local_18,*puVar11);
    local_18 = local_18 + local_24;
  }
  local_1c = local_1c + (local_34 - local_20) / 2;
  local_3c = dword_d0b16;
  dword_d0b16 = 0;
  dword_d42ac = 0;
  dword_d0b1a = dword_d0b1e;
  dword_d0b1e = uVar2;
  draw_bevel_box_b(local_1c,local_18,local_1c + local_20 + -1,local_18 + 0x11,0);
  dword_d0b16 = local_3c;
  bVar1 = false;
  dword_d0b1a = uVar2;
  dword_d0b1e = uVar3;
  if (param_6 == 0) {
    strcpy(acStack_74,unaff_EBX);
    do {
      iVar5 = text_entry_loop(unaff_EBX,unaff_ECX,local_20 + -8,local_1c + 2,local_18 + 2,return_zero_2fed2,0,0x14
                       );
      if (iVar5 == 0x1b) {
        if (param_9 == 0) {
          bVar1 = true;
        }
        else {
          strcpy(unaff_EBX,acStack_74);
        }
      }
      else {
        bVar1 = true;
        if ((param_9 == 0) || (*unaff_EBX != '\0')) {
          local_10 = 1;
        }
        else {
          bVar1 = false;
        }
      }
    } while (!bVar1);
  }
  else {
    do {
      iVar7 = text_entry_loop(unaff_EBX,unaff_ECX,local_20 + -8,local_1c + 2,local_18 + 2,return_zero_2fed2,0,0xc)
      ;
      iVar5 = unaff_ECX;
      if (iVar7 == 0x1b) {
        if (param_9 == 0) break;
      }
      else {
        local_10 = -1;
        if ((param_9 == 0) || (*unaff_EBX != '\0')) {
          iVar7 = 0;
          while ((iVar7 < unaff_ECX && (((&unk_c4b6c)[(byte)(unaff_EBX[iVar7] + 1)] & 0x20) != 0)))
          {
            local_10 = atoi(unaff_EBX);
            iVar7 = iVar7 + 1;
          }
        }
      }
      unaff_ECX = iVar5;
    } while ((local_10 < param_7) || (param_8 < local_10));
  }
  do {
    do {
      iVar5 = key_down(1);
    } while (iVar5 != 0);
    iVar5 = key_down(0x1c);
  } while (iVar5 != 0);
  event_queue_reset();
  drawshape(local_2c,local_28,local_30);
  freemem(local_2c);
  for (sVar6 = strlen(unaff_EBX); (0 < (int)sVar6 && (unaff_EBX[sVar6 - 1] == ' '));
      sVar6 = sVar6 - 1) {
    unaff_EBX[sVar6 - 1] = '\0';
  }
  while (*unaff_EBX == ' ') {
    sVar6 = strlen(unaff_EBX);
    for (iVar5 = 0; iVar5 < (int)sVar6; iVar5 = iVar5 + 1) {
      unaff_EBX[iVar5] = unaff_EBX[iVar5 + 1];
    }
  }
  return local_10;
}


// ================================================================================================
// database_buttons @ 0x7230b [__watcall]
// ================================================================================================

void __watcall database_buttons(void)

{
  undefined *puVar1;
  undefined auStack_38 [32];
  
  __CHK(0x44);
  if (dword_c6f78 == 0) {
    puVar1 = (undefined *)0x0;
    if (byte_ed993 == '\x01') {
      puVar1 = install_path;
    }
    make_path(auStack_38,puVar1,aDbBut,0);
    dword_c6f78 = loadshapes(auStack_38,0);
    dword_dd638 = locateshape(dword_c6f78,&aNone_c3023);
    dword_dd644 = locateshape(dword_c6f78,&aDel_c3028);
    dword_dd640 = locateshape(dword_c6f78,&aOpen_c302d);
    dword_dd64c = locateshape(dword_c6f78,&aCan_c3032);
    dword_dd664 = locateshape(dword_c6f78,&aNoar_c3037);
    dword_dd648 = locateshape(dword_c6f78,&aUp_c303c);
    dword_dd654 = locateshape(dword_c6f78,&aDown_c3041);
    dword_dd65c = locateshape(dword_c6f78,&aArro_c3046);
    dword_dd650 = locateshape(dword_c6f78,&aDbno);
    dword_dd634 = locateshape(dword_c6f78,&aDbcu);
    dword_dd660 = locateshape(dword_c6f78,&aDbtm);
    dword_dd63c = locateshape(dword_c6f78,&aDbor);
  }
  return;
}


// ================================================================================================
// scan_database_files @ 0x7248c [__watcall]
// ================================================================================================

void __watcall scan_database_files(void)

{
  char cVar1;
  int iVar2;
  int iVar3;
  undefined auStackY_40 [30];
  char acStackY_22 [14];
  
  __CHK(0x44);
  iVar3 = 0;
  dword_ec710 = 0;
  dword_ec6b8 = 0;
  dword_ec768 = 0;
  dword_ec714 = 0;
  dword_ec6bc = 0;
  dword_ec76c = 0;
  dword_ec718 = 0;
  dword_ec6c0 = 0;
  dword_ec770 = 0;
  dword_ec71c = 0;
  dword_ec6c4 = 0;
  dword_ec774 = 0;
  iVar2 = _dos_findfirst(&aDb_c305f,0,auStackY_40);
  if (iVar2 == 0) {
    dword_ec6c8 = &unk_dd2d4;
    unk_dd2d4._0_1_ = aCURRENT[0];
    unk_dd2d4._1_1_ = aCURRENT[1];
    unk_dd2d4._2_1_ = aCURRENT[2];
    unk_dd2d4._3_1_ = aCURRENT[3];
    DAT_000dd2d8._0_1_ = aCURRENT[4];
    DAT_000dd2d8._1_1_ = aCURRENT[5];
    DAT_000dd2d8._2_1_ = aCURRENT[6];
    DAT_000dd2d8._3_1_ = aCURRENT[7];
    dword_ec6b8 = dword_ec6b8 + 1;
    byte_dd2dc = 0;
    iVar3 = 9;
  }
  iVar2 = _dos_findfirst(aOrg,0,auStackY_40);
  if (iVar2 == 0) {
    dword_ec778 = (int)&unk_dd2d4 + iVar3;
    *(undefined4 *)((int)&unk_dd2d4 + iVar3) = aORIGINAL._0_4_;
    *(undefined4 *)((int)&DAT_000dd2d8 + iVar3) = aORIGINAL._4_4_;
    (&byte_dd2dc)[iVar3] = aORIGINAL[8];
    dword_ec768 = dword_ec768 + 1;
    (&byte_dd2dc)[iVar3] = 0;
    iVar3 = iVar3 + 9;
  }
  iVar2 = _dos_findfirst(aDbx,0x10);
  if (iVar2 == 0) {
    do {
      (&unk_ec720)[dword_ec710] = (int)&unk_dd2d4 + iVar3;
      iVar2 = 0;
      dword_ec710 = dword_ec710 + 1;
      do {
        cVar1 = acStackY_22[iVar2];
        if ((cVar1 == '\0') || (cVar1 == '.')) break;
        *(char *)((int)&unk_dd2d4 + iVar3) = cVar1;
        iVar2 = iVar2 + 1;
        iVar3 = iVar3 + 1;
      } while (iVar2 < 8);
      *(undefined *)((int)&unk_dd2d4 + iVar3) = 0;
      iVar3 = iVar3 + 1;
    } while ((dword_ec710 < 0x10) && (iVar2 = _dos_findnext(auStackY_40), iVar2 == 0));
    qsort(&unk_ec720,dword_ec710,4,cmp_name_strings);
    if (dword_ec710 < 6) {
      dword_ec71c = dword_ec710 + -1;
    }
    else {
      dword_ec71c = 5;
    }
  }
  return;
}


// ================================================================================================
// database_type_menu @ 0x72605 [__watcall]
// ================================================================================================

void __watcall database_type_menu(void)

{
  undefined4 uVar1;
  
  __CHK(0x24);
  settextpos(0xf8,0xff);
  if ((int)dword_dd658 < 0) {
    printstr_at(&aOpen_c3081,0x2d,0xc0);
    printstr_at(aDelete_c3086,0x6e,0xc0);
    settextpos(0xfa,0xff);
    printstr_at(&aDone_c308d,0xb5,0xc0);
    settextpos(0xf8,0xff);
    printstr_at(aCurrent_c3092,0xb1,0x4c);
    printstr_at(aOriginal,0xb1,100);
    printstr_at(aTemporary,0xa7,0x7c);
    drawshape_remap(dword_dd664,0x18,0x46);
  }
  else {
    if (((byte)dword_dd668 & 0x80) == 0) {
      printstr_at(aTemporary,0xa7,0x7c);
    }
    if (((byte)dword_dd668 & 0x40) == 0) {
      printstr_at(aOriginal,0xb1,100);
    }
    if (((byte)dword_dd668 & 0x20) == 0) {
      printstr2_at(aCurrent_c3092,0xb1,0x4c);
    }
    uVar1 = dword_dd634;
    if (((dword_dd658 == 0) || (uVar1 = dword_dd63c, dword_dd658 < 2)) ||
       (uVar1 = dword_dd660, dword_dd658 == 2)) {
      drawshape_remap(uVar1,0xa3,0x4b);
    }
    if (dword_dd658 == 2) {
      settextpos(0xfa,0xff);
    }
    printstr_at(aDelete_c3086,0x6e,0xc0);
    settextpos(0xf8,0xff);
  }
  return;
}


// ================================================================================================
// database_dialog @ 0x727ee [__watcall]
// ================================================================================================

void __watcall database_dialog(void)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined *puVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  undefined auStack_3c [32];
  int iStack_1c;
  
  __CHK(0x54);
  setdefaultscreen();
  puVar6 = install_path;
  if (byte_ed994 != '\x01') {
    puVar6 = (undefined *)0x0;
  }
  make_path(auStack_3c,puVar6,aDbdialog,0);
  uVar4 = loadshapes(auStack_3c,0);
  uVar5 = locateshape(uVar4,&aPdbx,10,0x13);
  drawshape2_remap(uVar5);
  freemem(uVar4);
  dword_dd668 = 0x10;
  dword_dd658 = -1;
  if (dword_ec710 != 0) {
    dword_dd668 = 0x90;
    dword_dd658 = 2;
  }
  if (dword_ec768 != 0) {
    dword_dd668 = dword_dd668 | 0x40;
    dword_dd658 = 1;
  }
  if (dword_ec6b8 != 0) {
    dword_dd668 = dword_dd668 | 0x20;
    dword_dd658 = 0;
  }
  if (-1 < dword_dd658) {
    dword_dd668 = dword_dd668 | 0x204;
    settextpos(0xfa,0xff);
    piVar1 = (int *)(&off_d1184)[dword_dd658];
    printstr_at(piVar1[piVar1[1] + 4],dword_d1114 + 0xd,dword_d1118 + 0x13);
    fillrect(dword_d1124 + 10,dword_d1128 + 0x13,(dword_d112c - dword_d1124) + 1,
             (dword_d1130 - dword_d1128) + 1,0xf8);
    iVar7 = 10;
    for (iVar8 = piVar1[2]; iVar3 = dword_d1108, iVar2 = dword_d1104, iVar8 <= piVar1[3];
        iVar8 = iVar8 + 1) {
      printstr_at(piVar1[iVar8 + 4],(&unk_d1084)[iVar7 * 4] + 10,(&unk_d1088)[iVar7 * 4] + 0x10);
      iVar7 = iVar7 + 1;
    }
    if (*piVar1 < 7) {
      switch(*piVar1) {
      case 6:
        dword_dd668 = dword_dd668 | 0x8000;
      case 5:
        dword_dd668 = dword_dd668 | 0x4000;
      case 4:
        dword_dd668 = dword_dd668 | 0x2000;
      case 3:
        dword_dd668 = dword_dd668 | 0x1000;
      case 2:
        dword_dd668 = dword_dd668 | 0x800;
      case 1:
        dword_dd668 = dword_dd668 | 0x400;
      }
    }
    else {
      dword_dd668 = dword_dd668 | 0xff03;
      iVar8 = dword_d1104 + 10;
      iVar9 = dword_d1108 + 0x13;
      iStack_1c = dword_d110c + 10;
      iVar7 = dword_d1108 + 0x12 + (int)(0x354 / (longlong)*piVar1);
      drawline(iVar8,iVar9,dword_d110c + 9,iVar9,0x7d);
      drawline(iVar8,iVar9,iVar8,iVar7 + -1,0x7d);
      iVar8 = iStack_1c;
      drawline(iStack_1c,iVar3 + 0x12,iStack_1c,iVar7,0x7b);
      drawline(iVar2 + 9,iVar7,iVar8,iVar7,0x7b);
    }
  }
  return;
}


