// Decompiled by Ghidra from hockey.elf (via ledisasm ELF export)
// This is machine generated pseudo-C meant as a reference for porting, it does not compile as is.
#include "prototypes.h"

// ================================================================================================
// sub_3170d @ 0x3170d [__watcall]
// ================================================================================================

int __watcall
sub_3170d(int param_1,int param_2,undefined4 param_3,undefined4 unaff_ECX,undefined4 param_5,
         code *param_6,int param_7,uint param_8)

{
  bool bVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  int extraout_EDX;
  bool bVar5;
  bool bVar6;
  int iStack_10;
  
  __CHK(0x1c);
  uVar3 = param_3;
  setdefaultscreen();
  dword_dd694 = uVar3;
  dword_dd6a0 = param_5;
  dword_dd690 = 0;
  dword_dd698 = param_1;
  dword_dd6a4 = unaff_ECX;
  sub_31599(param_8);
  dword_dd68c = 1;
  dword_dd69c = 1;
  bVar1 = false;
  sub_314b4(param_8);
  settimeout(param_7);
  settimeout2(4);
LAB_00031901:
  do {
    iStack_10 = getkey();
    if (iStack_10 == 0) {
      iVar4 = timeout2_expired();
      if (iVar4 == 0) {
        if (param_6 != (code *)0x0) {
          (*param_6)();
        }
        goto LAB_00031901;
      }
      iStack_10 = 0;
    }
    if (iStack_10 != 0) {
      settimeout(param_7);
      if ((iStack_10 == 0xd) || ((iStack_10 == 0x1b && ((param_8 & 4) != 0)))) goto LAB_00031a9f;
      if (iStack_10 == 0x4d00) {
        if (*(char *)(param_1 + dword_dd690) == '\0') goto LAB_00031901;
        sub_314b4(param_8);
        if (dword_dd690 < param_2) {
          dword_dd690 = dword_dd690 + 1;
        }
      }
      else if (iStack_10 == 0x4b00) {
        sub_314b4(param_8);
        if (dword_dd690 != 0) {
          dword_dd690 = dword_dd690 + -1;
        }
      }
      else if (iStack_10 == 0x4700) {
        sub_314b4(param_8);
        dword_dd690 = 0;
      }
      else if (iStack_10 == 0x4f00) {
        sub_314b4(param_8);
        for (dword_dd690 = 0; *(char *)(param_1 + dword_dd690) != '\0';
            dword_dd690 = dword_dd690 + 1) {
        }
      }
      else if (iStack_10 == 0x5200) {
        sub_314b4(param_8);
        if (bVar1) {
          bVar1 = false;
          dword_dd68c = 1;
        }
        else {
          bVar1 = true;
          dword_dd68c = (uint)byte_d42c3;
        }
      }
      else {
        if (iStack_10 == 0x5300) {
          if ((param_2 <= dword_dd690) || (*(char *)(param_1 + dword_dd690) == '\0'))
          goto LAB_00031901;
          sub_314b4(param_8);
          for (iVar4 = dword_dd690; iVar4 < param_2; iVar4 = iVar4 + 1) {
            *(undefined *)(param_1 + iVar4) = *(undefined *)(param_1 + 1 + iVar4);
          }
LAB_000318ea:
          *(undefined *)(param_2 + -1 + param_1) = 0;
        }
        else {
          if (iStack_10 == 8) {
            if (dword_dd690 != 0) {
              sub_314b4(param_8);
              iVar4 = dword_dd690 + -1;
              dword_dd690 = iVar4;
              for (; iVar4 < param_2; iVar4 = iVar4 + 1) {
                *(undefined *)(param_1 + iVar4) = *(undefined *)(param_1 + 1 + iVar4);
              }
              goto LAB_000318ea;
            }
            goto LAB_00031901;
          }
          if ((param_8 & 8) == 0) {
            if ((param_8 & 0x10) == 0) {
              if ((((iStack_10 < 0x20) || (0x7a < iStack_10)) || (param_2 <= dword_dd690)) ||
                 (((param_8 & 1) != 0 &&
                  (((param_8 & 1) == 0 ||
                   ((*(int *)((int)&qword_c4b64 + (byte)((char)iStack_10 + 1) + 5) >> 0x18 & 0xe0U)
                    == 0)))))) goto LAB_00031901;
            }
            else if ((iStack_10 != 0x20) && ((iStack_10 < 0x41 || (0x5a < iStack_10)))) {
              if (0x60 < iStack_10) {
                bVar6 = SBORROW4(iStack_10,0x7a);
                iVar4 = iStack_10 + -0x7a;
                bVar5 = iVar4 == 0;
                goto LAB_000319c6;
              }
              goto LAB_00031901;
            }
          }
          else {
            if (iStack_10 < 0x30) goto LAB_00031901;
            bVar6 = SBORROW4(iStack_10,0x39);
            iVar4 = iStack_10 + -0x39;
            bVar5 = iStack_10 == 0x39;
LAB_000319c6:
            if (!bVar5 && bVar6 == iVar4 < 0) goto LAB_00031901;
          }
          sub_314b4(param_8);
          if (bVar1) {
            for (iVar4 = param_2 + -2; dword_dd690 <= iVar4; iVar4 = iVar4 + -1) {
              *(undefined *)(param_1 + 1 + iVar4) = *(undefined *)(param_1 + iVar4);
            }
          }
          else if (*(char *)(param_1 + dword_dd690) == '\0') {
            *(undefined *)(param_1 + 1 + dword_dd690) = 0;
          }
          *(char *)(param_1 + dword_dd690) = (char)iStack_10;
          if (dword_dd690 < param_2) {
            dword_dd690 = dword_dd690 + 1;
          }
        }
        sub_31599(param_8);
      }
      sub_314b4(param_8);
      goto LAB_00031901;
    }
    settimeout2(4);
    uVar2 = dword_dd69c;
    dword_dd69c = 1;
    sub_314b4(param_8,uVar2);
    dword_dd69c = (uint)(extraout_EDX == 0);
    if ((param_7 != 0) && (iVar4 = sub_b39a7(), iVar4 != 0)) {
LAB_00031a9f:
      sub_314b4(param_8);
      return iStack_10;
    }
  } while( true );
}


// ================================================================================================
// frontend_main_menu @ 0x31ab5 [__watcall]
// ================================================================================================

/* WARNING: Type propagation algorithm not settling */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

longlong __watcall frontend_main_menu(undefined4 param_1,uint unaff_EDX)

{
  bool bVar1;
  ulonglong uVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined4 uVar8;
  undefined4 extraout_EDX;
  undefined *puVar9;
  int iVar10;
  int extraout_EDX_00;
  int *piVar11;
  undefined4 *puVar12;
  undefined4 *puVar13;
  undefined4 *puVar14;
  byte bVar15;
  ulonglong uVar16;
  undefined8 uVar17;
  int *local_c0;
  int local_bc [9];
  int local_98 [4];
  undefined4 *local_88 [4];
  int local_78 [13];
  int local_44;
  int local_40;
  int local_3c [3];
  int *local_30;
  int local_2c;
  undefined4 *local_28;
  int *local_24;
  int local_20;
  int iStack_1c;
  
  bVar15 = 0;
  __CHK(0xcc);
  local_3c[1] = 0xffffffff;
  iStack_1c = 0;
  local_bc[0] = 0x31ae6;
  set_hub_title(0);
  local_88[0] = &dword_ce3af;
  local_78[8] = 3;
  local_88[3] = (undefined4 *)0x0;
  local_88[2] = (undefined4 *)0x0;
  local_88[1] = (undefined4 *)0x0;
  local_78[7] = 0;
  local_78[6] = 0;
  local_78[5] = 0;
  local_78[4] = 0;
  local_78[3] = 0;
  local_78[2] = 0;
  local_78[1] = 0;
  local_78[0] = 0;
  local_bc[2] = 0;
  local_bc[1] = 0;
  local_30 = (int *)((dword_ce3af + dword_ce3b7) / 2);
  local_3c[2] = (dword_ce3b3 + dword_ce3bb) / 2;
  local_bc[0] = 0x1e0;
  local_c0 = (int *)0x27c;
  local_24 = local_30;
  local_20 = local_3c[2];
  setmouselimits(0,0);
  local_bc[0] = local_20;
  local_c0 = local_24;
  setmousepos();
  local_bc[0] = 0x31ba5;
  (*(code *)mouse_update_callback)();
  local_bc[0] = 0x31baa;
  sub_8b85b();
  local_bc[0] = 0x31bb1;
  set_menu_mode(0);
  dword_c65c0 = hub_sports_central;
  dword_c65c4 = hub_playoff_tree;
  dword_c65c8 = hub_league_calendar;
  dword_c65cc = hub_standings;
  dword_c65d0 = hub_stats;
  local_c0 = (int *)((((int)pointer_shapes[1] >> 0x10) + 1) *
                     ((*(int *)((int)pointer_shapes + 2) >> 0x10) + 1) + 0x11);
  local_bc[0] = 0x20;
  local_28 = (undefined4 *)allocmem(aPointer_c1724);
  puVar13 = local_28 + (uint)bVar15 * -2 + 1;
  puVar7 = pointer_shapes + (uint)bVar15 * -2 + 1;
  *local_28 = *pointer_shapes;
  puVar14 = puVar13 + (uint)bVar15 * -2 + 1;
  puVar12 = puVar7 + (uint)bVar15 * -2 + 1;
  *puVar13 = *puVar7;
  *puVar14 = *puVar12;
  puVar14[(uint)bVar15 * -2 + 1] = puVar12[(uint)bVar15 * -2 + 1];
  *(undefined *)(puVar14 + (uint)bVar15 * -2 + 1 + (uint)bVar15 * -2 + 1) =
       *(undefined *)(puVar12 + (uint)bVar15 * -2 + 1 + (uint)bVar15 * -2 + 1);
  *(short *)(local_28 + 1) = *(short *)(pointer_shapes + 1) + 1;
  *(short *)((int)local_28 + 6) = *(short *)((int)pointer_shapes + 6) + 1;
  if ((sound_enabled != '\0') && (dword_c721d == 0)) {
    if (byte_c7218 == '\0') {
      puVar9 = install_path;
      if (byte_ed9ab != '\x01') {
        puVar9 = (undefined *)0x0;
      }
      local_bc[0] = 0x31cb7;
      make_path(local_98,puVar9,aTonights_c173a,&aIff_c172c);
      byte_c7218 = '\x01';
    }
    else {
      puVar9 = install_path;
      if (byte_ed9a7 != '\x01') {
        puVar9 = (undefined *)0x0;
      }
      local_bc[0] = 0x31c87;
      make_path(local_98,puVar9,aMaindesk,&aIff_c172c);
      byte_c7218 = '\0';
    }
    local_bc[0] = 0x31cc7;
    dword_c721d = loadsound(local_98);
  }
  puVar9 = install_path;
  if (byte_ed836 != '\x01') {
    puVar9 = (undefined *)0x0;
  }
  local_bc[0] = 0x31cef;
  make_path(local_98,puVar9,aEasndesk_c1743,0);
  local_bc[0] = 0;
  local_c0 = local_98;
  piVar5 = (int *)loadshapes();
  local_bc[0] = 0x31d07;
  wait_sprite_fade();
  local_bc[0] = 0x31d0c;
  setdefaultscreen();
  local_bc[0] = (int)&aDesk_c174c;
  local_c0 = piVar5;
  local_bc[0] = locateshape();
  local_c0 = (int *)0x31d20;
  drawshape_home();
  local_bc[0] = 0xf8;
  local_c0 = (int *)0x31d3f;
  draw_menu_items(local_88[0],local_78[8],0xfa,0xf9);
  local_bc[0] = local_20;
  local_c0 = local_24;
  grabshape(local_28);
  local_bc[0] = local_20;
  local_c0 = local_24;
  drawshape_remap(pointer_shapes);
  dword_c7290 = 0x50;
  if (((sound_enabled != '\0') && (dword_c721d != 0)) && (((byte)option_flags & 0x40) != 0)) {
    local_bc[0] = 0x31db7;
    playsample(dword_c721d,dword_d2431,3,0x4c);
  }
  local_bc[0] = (int)&aPal_c1751;
  local_c0 = piVar5;
  iVar6 = locateshape();
  piVar11 = (int *)0x10;
  local_bc[0] = 0x31dd4;
  fade_palette(0,iVar6 + 0x10,0x10);
  local_c0 = (int *)0x31dda;
  local_bc[0] = (int)piVar5;
  freemem();
  local_bc[0] = 0x31de2;
  uVar16 = event_queue_reset();
LAB_00031de2:
  uVar8 = 0;
  do {
    local_bc[0] = 0x31de9;
    uVar17 = event_queue_pop((int)uVar16,(int)(uVar16 >> 0x20),piVar11);
    uVar2 = CONCAT44((int)((ulonglong)uVar17 >> 0x20),uVar8);
    if ((int)uVar17 == 0) break;
    piVar11 = local_3c + 2;
    local_bc[0] = 0x31e01;
    uVar16 = (*ui_poll_callback)();
    uVar8 = (undefined4)uVar16;
    uVar2 = uVar16;
  } while ((uVar16 & 2) == 0);
  uVar16 = CONCAT44((int)(uVar2 >> 0x20),local_3c[2]);
  if ((uVar2 & 2) == 0) goto code_r0x00031e10;
  local_bc[0] = (int)&local_40;
  local_c0 = local_3c;
  iVar6 = hit_test_menus(local_30,local_3c[2],local_88,iStack_1c,local_78 + 8,local_bc + 1);
  if (iVar6 == 0) {
    local_bc[0] = local_20;
    local_c0 = local_24;
    drawshape(local_28);
    for (iVar6 = iStack_1c; 0 < iVar6; iVar6 = iVar6 + -1) {
      local_78[iVar6] = 0;
      if (local_78[iVar6 + 4] != 0) {
        local_bc[0] = local_98[iVar6 * 2 + -7];
        local_c0 = (int *)local_98[iVar6 * 2 + -8];
        drawshape(local_78[iVar6 + 4]);
        local_98[iVar6 * 2 + -7] = 0;
        local_98[iVar6 * 2 + -8] = 0;
        local_bc[0] = local_78[iVar6 + 4];
        local_c0 = (int *)0x32668;
        freemem();
      }
    }
    iStack_1c = 0;
    local_88[3] = (undefined4 *)0x0;
    local_88[2] = (undefined4 *)0x0;
    local_88[1] = (undefined4 *)0x0;
    local_78[7] = 0;
    local_78[6] = 0;
    local_78[5] = 0;
    local_78[4] = 0;
    local_78[3] = 0;
    local_78[2] = 0;
    local_78[1] = 0;
    local_78[0xb] = 0;
    local_78[10] = 0;
    local_78[9] = 0;
  }
  else if (local_88[local_3c[0]][local_40 * 8 + 5] == 0) {
    if (local_88[local_3c[0]][local_40 * 8 + 6] != 0) {
      local_bc[0] = local_20;
      local_c0 = local_24;
      drawshape(local_28);
      iVar6 = iStack_1c;
      if (iStack_1c != local_3c[0]) {
        for (; local_3c[0] < iVar6; iVar6 = iVar6 + -1) {
          local_78[iVar6] = 0;
          if (local_78[iVar6 + 4] != 0) {
            local_bc[0] = local_98[iVar6 * 2 + -7];
            local_c0 = (int *)local_98[iVar6 * 2 + -8];
            drawshape(local_78[iVar6 + 4]);
            local_98[iVar6 * 2 + -7] = 0;
            local_98[iVar6 * 2 + -8] = 0;
            local_bc[0] = local_78[iVar6 + 4];
            local_c0 = (int *)0x323e4;
            freemem();
            local_78[iVar6 + 4] = 0;
            local_88[iVar6] = (undefined4 *)0x0;
            local_78[iVar6 + 8] = 0;
          }
        }
        iStack_1c = local_3c[0];
      }
      iVar4 = iStack_1c;
      local_bc[0] = 0xf8;
      local_c0 = (int *)0xf9;
      highlight_menu_item(local_88[iStack_1c] + local_78[iStack_1c] * 8,local_98[iStack_1c * 2 + -8]
                          ,local_98[iStack_1c * 2 + -7],0xfa);
      iVar6 = local_40;
      local_78[iVar4] = local_40;
      local_bc[0] = 0xf8;
      local_c0 = (int *)0xf9;
      unhighlight_menu_item
                (local_88[iVar4] + iVar6 * 8,local_98[iVar4 * 2 + -8],local_98[iVar4 * 2 + -7],0xfa)
      ;
      iVar3 = local_3c[0];
      iVar10 = local_40;
      iVar6 = iVar4 + 1;
      iStack_1c = iVar6;
      local_88[iVar6] = (undefined4 *)local_88[local_3c[0]][local_40 * 8 + 6];
      piVar5 = local_88[iVar3] + iVar10 * 8;
      local_78[iVar4 + 9] = piVar5[7];
      if (iVar6 == 1) {
        iVar6 = *piVar5;
      }
      else {
        iVar6 = piVar5[2];
      }
      local_98[iStack_1c * 2 + -8] = iVar6 + (int)(&local_c0)[iStack_1c * 2];
      if (iStack_1c == 1) {
        iVar6 = local_88[local_3c[0]][local_40 * 8 + 3];
      }
      else {
        iVar6 = local_88[local_3c[0]][local_40 * 8 + 1];
      }
      local_2c = iStack_1c * 8;
      local_98[iStack_1c * 2 + -7] = iVar6 + local_bc[iStack_1c * 2];
      iVar3 = iStack_1c;
      piVar5 = local_88[iStack_1c];
      local_78[0xc] = (piVar5[local_78[iStack_1c + 8] * 8 + -6] - *piVar5) + 1;
      local_44 = (piVar5[local_78[iStack_1c + 8] * 8 + -5] - piVar5[1]) + 1;
      local_bc[0] = 0x20;
      local_c0 = (int *)(local_78[0xc] * local_44 + 0x11);
      puVar7 = (undefined4 *)allocmem(aMenubuff_c1756);
      local_78[iVar3 + 4] = (int)puVar7;
      puVar13 = puVar7 + (uint)bVar15 * -2 + 1;
      puVar12 = pointer_shapes + (uint)bVar15 * -2 + 1;
      *puVar7 = *pointer_shapes;
      puVar14 = puVar13 + (uint)bVar15 * -2 + 1;
      puVar7 = puVar12 + (uint)bVar15 * -2 + 1;
      *puVar13 = *puVar12;
      *puVar14 = *puVar7;
      puVar14[(uint)bVar15 * -2 + 1] = puVar7[(uint)bVar15 * -2 + 1];
      *(undefined *)(puVar14 + (uint)bVar15 * -2 + 1 + (uint)bVar15 * -2 + 1) =
           *(undefined *)(puVar7 + (uint)bVar15 * -2 + 1 + (uint)bVar15 * -2 + 1);
      *(short *)(local_78[iVar3 + 4] + 4) = (short)local_78[0xc];
      *(short *)(local_78[iVar3 + 4] + 6) = (short)local_44;
      local_bc[0] = *(int *)((int)local_bc + local_2c + 8U);
      local_c0 = *(int **)((int)local_bc + local_2c + 4U);
      grabshape(local_78[iVar3 + 4]);
      local_bc[0] = 0xf8;
      local_c0 = (int *)0xf9;
      draw_menu(local_88[iVar3],local_78[iVar3 + 8],*(undefined4 *)((int)local_bc + local_2c + 4U),
                *(undefined4 *)((int)local_bc + local_2c + 8U),0xfa);
      local_78[iVar3] = 0;
      local_bc[0] = 0xf8;
      local_c0 = (int *)0xf9;
      iVar6 = *(int *)((int)local_bc + local_2c + 8U);
      iVar10 = *(int *)((int)local_bc + local_2c + 4U);
      puVar7 = local_88[iVar3];
      goto LAB_00032364;
    }
    local_bc[0] = local_20;
    local_c0 = local_24;
    drawshape(local_28);
  }
  else if (local_40 == local_78[local_3c[0]]) {
    local_bc[0] = local_20;
    local_c0 = local_24;
    drawshape(local_28);
    for (iVar6 = iStack_1c; 0 < iVar6; iVar6 = iVar6 + -1) {
      local_78[iVar6] = 0;
      if (local_78[iVar6 + 4] != 0) {
        local_bc[0] = local_98[iVar6 * 2 + -7];
        local_c0 = (int *)local_98[iVar6 * 2 + -8];
        drawshape(local_78[iVar6 + 4]);
        local_98[iVar6 * 2 + -7] = 0;
        local_98[iVar6 * 2 + -8] = 0;
        local_bc[0] = local_78[iVar6 + 4];
        local_c0 = (int *)0x31f79;
        freemem();
      }
    }
    iStack_1c = 0;
    local_bc[0] = (int)local_28;
    local_c0 = (int *)0x31f97;
    freemem();
    dword_c7219 = 0;
    local_bc[0] = 0x31fbc;
    iVar6 = (*(code *)local_88[local_3c[0]][local_40 * 8 + 5])();
    local_bc[0] = 0x31fca;
    file_close(local_3c + 1);
    local_c0 = (int *)((((int)pointer_shapes[1] >> 0x10) + 1) *
                       ((*(int *)((int)pointer_shapes + 2) >> 0x10) + 1) + 0x11);
    local_bc[0] = 0x20;
    local_28 = (undefined4 *)allocmem(aPointer_c1724);
    puVar13 = local_28 + (uint)bVar15 * -2 + 1;
    puVar7 = pointer_shapes + (uint)bVar15 * -2 + 1;
    *local_28 = *pointer_shapes;
    puVar14 = puVar13 + (uint)bVar15 * -2 + 1;
    puVar12 = puVar7 + (uint)bVar15 * -2 + 1;
    *puVar13 = *puVar7;
    *puVar14 = *puVar12;
    puVar14[(uint)bVar15 * -2 + 1] = puVar12[(uint)bVar15 * -2 + 1];
    *(undefined *)(puVar14 + (uint)bVar15 * -2 + 1 + (uint)bVar15 * -2 + 1) =
         *(undefined *)(puVar12 + (uint)bVar15 * -2 + 1 + (uint)bVar15 * -2 + 1);
    *(short *)(local_28 + 1) = *(short *)(pointer_shapes + 1) + 1;
    *(short *)((int)local_28 + 6) = *(short *)((int)pointer_shapes + 6) + 1;
    local_88[3] = (undefined4 *)0x0;
    local_88[2] = (undefined4 *)0x0;
    local_88[1] = (undefined4 *)0x0;
    local_78[7] = 0;
    local_78[6] = 0;
    local_78[5] = 0;
    local_78[4] = 0;
    local_78[3] = 0;
    local_78[2] = 0;
    local_78[1] = 0;
    local_78[0xb] = 0;
    local_78[10] = 0;
    local_78[9] = 0;
    if (iVar6 == 1) {
      local_bc[0] = 0x326ee;
      event_queue_reset();
      local_bc[0] = 0x326f3;
      ui_shutdown();
      local_c0 = (int *)0x326f9;
      local_bc[0] = extraout_EDX_00;
      freemem();
      return (ulonglong)unaff_EDX << 0x20;
    }
    if (iVar6 == 2) {
      local_bc[0] = 0x32072;
      setdefaultscreen();
      if (((dword_c7219 == 0) && (sound_enabled != '\0')) && (dword_c721d != 0)) {
        local_bc[0] = 0x320a1;
        sound_fade(dword_d2431,3,0x46);
        do {
          local_bc[0] = 0x320b3;
          iVar6 = sound_channel_status(ram0x000d242c >> 0x18,3);
        } while (iVar6 == 0);
        local_bc[0] = dword_c721d;
        local_c0 = (int *)0x320c3;
        releasememblock();
        dword_c721d = 0;
      }
      else {
        dword_c7219 = 0;
      }
      bVar1 = false;
      if ((sound_enabled != '\0') && (dword_c721d == 0)) {
        bVar1 = true;
        if (byte_c7218 == '\0') {
          puVar9 = (undefined *)0x0;
          if (byte_ed9ab == '\x01') {
            puVar9 = install_path;
          }
          local_bc[0] = 0x32154;
          make_path(local_98,puVar9,aTonights_c173a,&aIff_c172c);
          byte_c7218 = '\x01';
        }
        else {
          puVar9 = install_path;
          if (byte_ed9a7 != '\x01') {
            puVar9 = (undefined *)0x0;
          }
          local_bc[0] = 0x32128;
          make_path(local_98,puVar9,aMaindesk,&aIff_c172c);
          byte_c7218 = '\0';
        }
        local_bc[0] = 0x32164;
        dword_c721d = loadsound(local_98);
      }
      local_bc[0] = 0x1e0;
      local_c0 = (int *)0x0;
      setclip(0,0x280);
      puVar9 = install_path;
      if (byte_ed836 != '\x01') {
        puVar9 = (undefined *)0x0;
      }
      local_bc[0] = 0x321a2;
      make_path(local_98,puVar9,aEasndesk_c1743,0);
      local_bc[0] = 0;
      local_c0 = local_98;
      piVar5 = (int *)loadshapes();
      local_bc[0] = (int)&aDesk_c174c;
      local_c0 = piVar5;
      local_bc[0] = locateshape();
      local_c0 = (int *)0x321c9;
      drawshape_home();
      local_bc[0] = 0xf8;
      local_c0 = (int *)0x321e8;
      draw_menu_items(local_88[0],local_78[8],0xfa,0xf9);
      local_bc[0] = (int)&aPal_c1751;
      local_c0 = piVar5;
      iVar6 = locateshape();
      if ((((sound_enabled != '\0') && (bVar1)) && (((byte)option_flags & 0x40) != 0)) &&
         (dword_c721d != 0)) {
        local_bc[0] = 0x32231;
        playsample(dword_c721d,dword_d2431,3,0x4c);
      }
      local_bc[0] = 0x3223f;
      fade_palette(0,iVar6 + 0x10,0x10);
      local_c0 = (int *)0x32245;
      local_bc[0] = (int)piVar5;
      freemem();
    }
    local_bc[0] = 0x3224f;
    set_hub_title(0);
    local_bc[0] = local_20;
    local_c0 = local_24;
    setmousepos();
    local_bc[0] = 0x3226c;
    event_queue_reset();
  }
  else {
    local_bc[0] = local_20;
    local_c0 = local_24;
    drawshape(local_28);
    iVar6 = iStack_1c;
    if (iStack_1c != local_3c[0]) {
      for (; local_3c[0] < iVar6; iVar6 = iVar6 + -1) {
        local_78[iVar6] = 0;
        if (local_78[iVar6 + 4] != 0) {
          local_bc[0] = local_98[iVar6 * 2 + -7];
          local_c0 = (int *)local_98[iVar6 * 2 + -8];
          drawshape(local_78[iVar6 + 4]);
          local_98[iVar6 * 2 + -7] = 0;
          local_98[iVar6 * 2 + -8] = 0;
          local_bc[0] = local_78[iVar6 + 4];
          local_c0 = (int *)0x322dd;
          freemem();
          local_78[iVar6 + 4] = 0;
          local_88[iVar6] = (undefined4 *)0x0;
          local_78[iVar6 + 8] = 0;
        }
      }
      iStack_1c = local_3c[0];
    }
    local_bc[0] = 0xf8;
    local_c0 = (int *)0xf9;
    highlight_menu_item(local_88[local_3c[0]] + local_78[local_3c[0]] * 8,
                        local_98[local_3c[0] * 2 + -8],local_98[local_3c[0] * 2 + -7],0xfa);
    iVar3 = local_3c[0];
    local_78[local_3c[0]] = local_40;
    local_bc[0] = 0xf8;
    local_c0 = (int *)0xf9;
    iVar6 = local_98[iVar3 * 2 + -7];
    iVar10 = local_98[iVar3 * 2 + -8];
    puVar7 = local_88[iVar3] + local_78[iVar3] * 8;
LAB_00032364:
    local_bc[0] = 0xf8;
    local_c0 = (int *)0xf9;
    unhighlight_menu_item(puVar7,iVar10,iVar6,0xfa);
  }
  local_bc[0] = local_3c[2];
  local_c0 = local_30;
  grabshape(local_28);
  piVar11 = local_30;
  goto LAB_00031e85;
code_r0x00031e10:
  if ((local_30 != local_24) || (local_3c[2] != local_20)) {
    local_bc[0] = 0x31e35;
    setdefaultscreen();
    puVar7 = local_28;
    local_bc[0] = local_20;
    local_c0 = local_24;
    drawshape(local_28);
    local_bc[0] = local_3c[2];
    local_c0 = local_30;
    grabshape(puVar7);
LAB_00031e85:
    local_c0 = local_30;
    local_bc[0] = local_3c[2];
    drawshape_remap(pointer_shapes);
    uVar16 = CONCAT44(extraout_EDX,local_3c[2]);
    local_24 = local_30;
    local_20 = local_3c[2];
  }
  goto LAB_00031de2;
}


// ================================================================================================
// sub_3270b @ 0x3270b [__watcall]
// ================================================================================================

undefined4 __watcall sub_3270b(void)

{
  __CHK(4);
  return 1;
}


// ================================================================================================
// save_settings @ 0x3271b [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall save_settings(int param_1)

{
  __CHK(0xc);
  strcpy((char *)(param_1 + 4),&league_dir);
  strcpy((char *)(param_1 + 0x11),&byte_dd750);
  strcpy((char *)(param_1 + 0x31),&byte_dd710);
  *(int *)(param_1 + 0x51) = (int)user2_team._2_2_;
  *(int *)(param_1 + 0x55) = (int)_away_team_id;
  *(undefined4 *)(param_1 + 0x59) = option_flags;
  *(undefined4 *)(param_1 + 0x5d) = dword_c5403;
  *(undefined4 *)(param_1 + 0x61) = dword_c5407;
  *(undefined4 *)(param_1 + 0x65) = dword_c540b;
  *(undefined4 *)(param_1 + 0x69) = dword_c540f;
  *(undefined4 *)(param_1 + 0x6d) = dword_c5413;
  *(undefined4 *)(param_1 + 0x71) = dword_c5417;
  return;
}


// ================================================================================================
// apply_settings @ 0x327a1 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall apply_settings(int *param_1)

{
  char *pcVar1;
  int iVar2;
  bool bVar3;
  
  __CHK(0x1c);
  strcpy(&league_dir,(char *)(param_1 + 1));
  strcpy(&byte_dd750,(char *)((int)param_1 + 0x11));
  strcpy(&byte_dd710,(char *)((int)param_1 + 0x31));
  dword_c53fb = *param_1;
  user2_team._2_2_ = *(short *)((int)param_1 + 0x51);
  _away_team_id = *(short *)((int)param_1 + 0x55);
  option_flags = *(uint *)((int)param_1 + 0x59);
  dword_c5403 = *(undefined4 *)((int)param_1 + 0x5d);
  dword_c5407 = *(undefined4 *)((int)param_1 + 0x61);
  dword_c540b = *(uint *)((int)param_1 + 0x65);
  dword_c540f = *(uint *)((int)param_1 + 0x69);
  dword_c5413 = *(undefined4 *)((int)param_1 + 0x6d);
  dword_c5417 = *(undefined4 *)((int)param_1 + 0x71);
  if (dword_c540b < 2) {
    if ((dword_c540b == 1) && ((input_devices & 1) == 0)) {
      dword_c540b = 0;
    }
  }
  else if (dword_c540b < 3) {
    if ((input_devices & 2) == 0) {
      dword_c540b = 0;
    }
  }
  else if ((dword_c540b == 4) && ((input_devices & 4) == 0)) {
    dword_c540b = 0;
  }
  if (dword_c540f < 2) {
    if ((dword_c540f == 1) && ((input_devices & 1) == 0)) {
      dword_c540f = 0;
    }
  }
  else if (dword_c540f < 3) {
    if ((input_devices & 2) == 0) {
      dword_c540f = 0;
    }
  }
  else if ((dword_c540f == 4) && ((input_devices & 4) == 0)) {
    dword_c540f = 0;
  }
  if (dword_c540b == 0) {
    if (((input_devices & 2) == 0) || (dword_c540f == 2)) {
      if (((input_devices & 4) == 0) || (dword_c540f == 4)) {
        if (((input_devices & 8) == 0) || (dword_c540f == 8)) {
          if (((input_devices & 1) == 0) || (dword_c540f == 1)) {
            dword_c540b = 0x10;
          }
          else {
            dword_c540b = 1;
          }
        }
        else {
          dword_c540b = 8;
        }
      }
      else {
        dword_c540b = 4;
      }
    }
    else {
      dword_c540b = 2;
    }
  }
  if (dword_c540f == 0) {
    if (((input_devices & 2) == 0) || (dword_c540b == 2)) {
      if (((input_devices & 4) == 0) || (dword_c540b == 4)) {
        if (((input_devices & 8) == 0) || (dword_c540b == 8)) {
          if (((input_devices & 1) == 0) || (dword_c540b == 1)) {
            dword_c540f = 0x10;
          }
          else {
            dword_c540f = 1;
          }
        }
        else {
          dword_c540f = 8;
        }
      }
      else {
        dword_c540f = 4;
      }
    }
    else {
      dword_c540f = 2;
    }
  }
  if ((dword_c540b == 0x10) != (dword_c540f == 0x10)) {
    bVar3 = dword_c540b != 0x10;
    iVar2 = (&dword_c5413)[!bVar3];
    (&dword_c5413)[bVar3] = (uint)(iVar2 == 0);
    (&dword_c5403)[bVar3] = (iVar2 != 0) - 2;
  }
  if ((option_flags & 0x40) == 0) {
    music_disable();
  }
  else {
    music_enable();
  }
  if ((option_flags & 0x80) == 0) {
    sfx_disable();
  }
  else {
    sfx_enable();
  }
  sub_8b85b();
  if (dword_c53fb == 0) {
    pcVar1 = (&team_abbrev)[user2_team._2_2_];
    if (pcVar1[2] == '\0') {
      strncpy(aGameLAAtMTL + 0xd,pcVar1,2);
      aGameLAAtMTL[0xf] = ' ';
    }
    else {
      strncpy(aGameLAAtMTL + 0xd,pcVar1,3);
    }
    pcVar1 = (&team_abbrev)[_away_team_id];
    if (pcVar1[2] == '\0') {
      strncpy(aGameLAAtMTL + 6,pcVar1,2);
      aGameLAAtMTL[8] = ' ';
    }
    else {
      strncpy(aGameLAAtMTL + 6,pcVar1,3);
    }
  }
  return;
}


// ================================================================================================
// load_game_set @ 0x32b1d [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall load_game_set(int *param_1)

{
  int iVar1;
  uint uVar2;
  char acStack_44 [4];
  char acStack_40 [4];
  char cStack_3c;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 uStack_1c;
  
  __CHK(0x5c);
  if (dword_c53fb == 0) {
    acStack_44[0] = aGameSet_c175f[0];
    acStack_44[1] = aGameSet_c175f[1];
    acStack_44[2] = aGameSet_c175f[2];
    acStack_44[3] = aGameSet_c175f[3];
    acStack_40[0] = aGameSet_c175f[4];
    acStack_40[1] = aGameSet_c175f[5];
    acStack_40[2] = aGameSet_c175f[6];
    acStack_40[3] = aGameSet_c175f[7];
    cStack_3c = aGameSet_c175f[8];
  }
  else {
    make_path(acStack_44,&league_dir,&aGame,&aSet);
  }
  iVar1 = sub_142e7(acStack_44);
  if ((iVar1 == 0) && (uVar2 = sub_106c8(), uVar2 < 0x75)) {
    uStack_1c = 0x140;
    local_20 = 0xf0;
    setmousepos(0x140,0xf0);
    message_dialog(0xffffffff,0xffffffff,&off_c7282,3,0,0,&uStack_1c,&local_20,800);
    return;
  }
  strcpy((char *)(param_1 + 1),&league_dir);
  strcpy((char *)((int)param_1 + 0x11),&byte_dd750);
  strcpy((char *)((int)param_1 + 0x31),&byte_dd710);
  *param_1 = dword_c53fb;
  *(int *)((int)param_1 + 0x51) = (int)user2_team._2_2_;
  *(int *)((int)param_1 + 0x55) = (int)_away_team_id;
  *(undefined4 *)((int)param_1 + 0x59) = option_flags;
  *(undefined4 *)((int)param_1 + 0x5d) = dword_c5403;
  *(undefined4 *)((int)param_1 + 0x61) = dword_c5407;
  *(undefined4 *)((int)param_1 + 0x65) = dword_c540b;
  *(undefined4 *)((int)param_1 + 0x69) = dword_c540f;
  *(undefined4 *)((int)param_1 + 0x6d) = dword_c5413;
  *(undefined4 *)((int)param_1 + 0x71) = dword_c5417;
  iVar1 = sub_14566(acStack_44,&local_24);
  if (iVar1 != 0) {
    fatalerror(&aE2);
  }
  iVar1 = file_write(local_24,param_1,0xffffffff,0x75);
  if (iVar1 != 0) {
    fatalerror(&aE3);
  }
  iVar1 = file_close(&local_24);
  if (iVar1 != 0) {
    fatalerror(&aE4);
  }
  return;
}


// ================================================================================================
// sub_32c9e @ 0x32c9e [__watcall]
// ================================================================================================

undefined4 __watcall sub_32c9e(undefined4 param_1,undefined4 unaff_EDX)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 local_104;
  undefined auStackY_100 [85];
  undefined4 uStackY_ab;
  undefined4 local_8c;
  undefined auStackY_88 [85];
  undefined4 uStackY_33;
  undefined4 uStackY_14;
  
  __CHK(0x108);
  iVar1 = file_open_read(param_1,&uStackY_14);
  if (((iVar1 == 0) && (iVar1 = file_read(uStackY_14,&local_8c,0xffffffff,0x75), iVar1 == 0)) &&
     (iVar1 = file_close(&uStackY_14), iVar1 == 0)) {
    iVar1 = file_open_rw(unaff_EDX,&uStackY_14);
    if (iVar1 == 0) {
      iVar1 = file_read(uStackY_14,&local_104,0xffffffff,0x75);
      if (iVar1 != 0) {
        return 0xffffffff;
      }
      uStackY_ab = uStackY_33;
      memcpy(auStackY_100,auStackY_88,0xd);
    }
    else {
      iVar1 = sub_14566(unaff_EDX,&uStackY_14);
      if (iVar1 != 0) {
        return 0xffffffff;
      }
      puVar2 = &local_8c;
      puVar3 = &local_104;
      for (iVar1 = 0x1d; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar3 = *puVar2;
        puVar2 = puVar2 + 1;
        puVar3 = puVar3 + 1;
      }
      *(undefined *)puVar3 = *(undefined *)puVar2;
    }
    iVar1 = file_write(uStackY_14,&local_104,0,0x75);
    if ((iVar1 == 0) && (iVar1 = file_close(&uStackY_14), iVar1 == 0)) {
      return 0;
    }
  }
  return 0xffffffff;
}


// ================================================================================================
// exhibition_mode @ 0x32da9 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 __watcall exhibition_mode(int *param_1,undefined4 unaff_EDX)

{
  undefined4 uVar1;
  int iVar2;
  uint extraout_EDX;
  uint extraout_EDX_00;
  uint uVar3;
  undefined8 uVar4;
  
  __CHK(0x28);
  uVar4 = check_disk_space_for_game(param_1,0);
  if ((int)uVar4 == 0) {
    dword_c65c0 = exh_hub_sports_central;
    dword_c65c4 = exh_hub_playoff_tree;
    dword_c65c8 = exh_hub_league_calendar;
    dword_c65cc = exh_hub_standings;
    dword_c65d0 = exh_hub_stats;
    dword_dc234 = (int)((ulonglong)uVar4 >> 0x20);
    sub_10712();
    option_flags._1_1_ = option_flags._1_1_ | 2;
    uVar3 = extraout_EDX;
    if (*param_1 < 0) {
      sub_1befd(0);
      uVar1 = team_select_screen((int)user2_team._2_2_,(int)_away_team_id);
      ui_shutdown(uVar1,uVar1);
      uVar3 = extraout_EDX_00;
    }
    if ((uVar3 & 4) == 0) {
      set_menu_mode(1);
      if (-1 < *param_1) {
        uVar1 = allocmem(aPalette,0x300,0x20);
        getpalette(0,0x100,uVar1);
        if ((sound_enabled != '\0') && (dword_c721d != 0)) {
          sound_fade(dword_d2431,3,100);
        }
        fade_palette(1,uVar1);
        freemem(uVar1);
        if ((sound_enabled != '\0') && (dword_c721d != 0)) {
          do {
            iVar2 = sound_channel_status(ram0x000d242c >> 0x18,3);
          } while (iVar2 == 0);
          releasememblock(dword_c721d);
          dword_c721d = 0;
        }
        sub_479e9();
      }
      play_game(param_1);
      set_menu_mode(0);
    }
    uVar1 = allocmem(&aTemp_c1783,0x300,0x20);
    if ((sound_enabled != '\0') && (dword_c721d != 0)) {
      sound_fade(dword_d2431,3,0x19);
    }
    getpalette(0,0x100,uVar1);
    fade_palette(1,uVar1,0x10);
    freemem(uVar1);
    if ((sound_enabled != '\0') && (dword_c721d != 0)) {
      do {
        iVar2 = sound_channel_status(ram0x000d242c >> 0x18,3);
      } while (iVar2 == 0);
      releasememblock(dword_c721d);
      dword_c721d = 0;
    }
    ui_init();
    dword_c65c0 = hub_sports_central;
    dword_c65c4 = hub_playoff_tree;
    dword_c65c8 = hub_league_calendar;
    dword_c65cc = hub_standings;
    dword_c65d0 = hub_stats;
    uVar1 = 2;
  }
  else {
    uVar1 = 0;
  }
  return CONCAT44(unaff_EDX,uVar1);
}


// ================================================================================================
// new_league_mode @ 0x32ff4 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 __watcall new_league_mode(undefined4 param_1,undefined4 unaff_EDX)

{
  undefined4 uVar1;
  int iVar2;
  
  __CHK(0x20);
  save_settings(&settings_exhibition);
  settings_league = 2;
  dword_c53d3 = 0xc;
  dword_c53d7 = 0x15;
  if (sound_enabled == '\0') {
    word_c53db = word_c53db & 0xfeff | 0x2ff;
  }
  else {
    word_c53db = word_c53db | 0x3ff;
  }
  word_c53db = word_c53db & 0x83ff | 0x7800;
  if ((input_devices & 2) == 0) {
    if ((input_devices & 4) == 0) {
      if ((input_devices & 8) == 0) {
        if ((input_devices & 1) == 0) {
          dword_c53e7 = 0x10;
        }
        else {
          dword_c53e7 = 1;
        }
      }
      else {
        dword_c53e7 = 8;
      }
    }
    else {
      dword_c53e7 = 4;
    }
  }
  else {
    dword_c53e7 = 2;
  }
  if (dword_c53e7 == 0x10) {
    dword_c53df = 0xffffffff;
  }
  else {
    dword_c53df = 0xc;
  }
  dword_c53eb = 0x10;
  dword_c53e3 = 0xfffffffe;
  dword_c53ef = 0;
  dword_c53f3 = 1;
  apply_settings(&settings_league);
  sub_7a6ad(0);
  new_league_dialog();
  sub_7b39c();
  if (byte_c5386 == '\0') {
    sub_1d518();
    set_menu_mode(0);
    dword_ce4e3 = (code *)0x0;
    dword_ce503 = (code *)0x0;
    dword_ce527 = (undefined *)0x0;
  }
  else {
    sub_1d518();
    set_menu_mode(0);
    dword_ce4e3 = sub_336e6;
    dword_ce503 = league_calendar_screen;
    dword_ce527 = &unk_ce64f;
  }
  apply_settings(&settings_exhibition);
  uVar1 = allocmem(&aTemp_c1783,0x300,0x20);
  getpalette(0,0x100,uVar1);
  if ((sound_enabled != '\0') && (dword_c721d != 0)) {
    sound_fade(dword_d2431,3,100);
  }
  fade_palette(1,uVar1,0x10);
  freemem(uVar1);
  if ((sound_enabled != '\0') && (dword_c721d != 0)) {
    do {
      iVar2 = sound_channel_status(ram0x000d242c >> 0x18,3);
    } while (iVar2 == 0);
    releasememblock(dword_c721d);
    dword_c721d = 0;
  }
  return CONCAT44(unaff_EDX,2);
}


// ================================================================================================
// sub_3322a @ 0x3322a [__watcall]
// ================================================================================================

undefined8 __watcall sub_3322a(undefined4 param_1,undefined4 unaff_EDX)

{
  undefined4 uVar1;
  
  __CHK(0x20);
  save_settings(&settings_exhibition);
  apply_settings(&settings_league);
  set_menu_mode(3);
  select_human_team_dialog();
  set_menu_mode(0);
  save_settings(&settings_league);
  apply_settings(&settings_exhibition);
  uVar1 = allocmem(&aTemp_c1783,0x300,0x20);
  getpalette(0,0x100,uVar1);
  fade_palette(1,uVar1,0x10);
  freemem(uVar1);
  return CONCAT44(unaff_EDX,2);
}


// ================================================================================================
// sub_332c0 @ 0x332c0 [__watcall]
// ================================================================================================

undefined8 __watcall sub_332c0(undefined4 param_1,undefined4 unaff_EDX)

{
  undefined4 uVar1;
  
  __CHK(0x20);
  save_settings(&settings_exhibition);
  apply_settings(&settings_league);
  set_menu_mode(3);
  select_human_control_dialog();
  set_menu_mode(0);
  save_settings(&settings_league);
  apply_settings(&settings_exhibition);
  uVar1 = allocmem(&aTemp_c1783,0x300,0x20);
  getpalette(0,0x100,uVar1);
  fade_palette(1,uVar1,0x10);
  freemem(uVar1);
  return CONCAT44(unaff_EDX,2);
}


// ================================================================================================
// sub_332f6 @ 0x332f6 [__watcall]
// ================================================================================================

undefined8 __watcall sub_332f6(undefined4 param_1,undefined4 unaff_EDX)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  __CHK(0x24);
  iVar3 = 0;
  uVar2 = 0;
  save_settings(&settings_exhibition);
  apply_settings(&settings_league);
  iVar1 = sub_40f4e();
  if (iVar1 == 0) {
    iVar3 = -1;
  }
  if (byte_de268 != '\0') {
    uVar2 = allocmem(&aTemp_c1783,0x300,0x20);
    getpalette(0,0x100,uVar2);
    fade_palette(1,uVar2,0x10);
    freemem(uVar2);
    uVar2 = 2;
  }
  if (iVar3 != 0) {
    sub_7a13a();
  }
  save_settings(&settings_league);
  apply_settings(&settings_exhibition);
  return CONCAT44(unaff_EDX,uVar2);
}


// ================================================================================================
// sub_3339d @ 0x3339d [__watcall]
// ================================================================================================

undefined4 __watcall sub_3339d(void)

{
  __CHK(4);
  save_settings(&settings_exhibition);
  apply_settings(&settings_league);
  sub_3b9ca();
  save_settings(&settings_league);
  apply_settings(&settings_exhibition);
  return 0;
}


// ================================================================================================
// sub_333d7 @ 0x333d7 [__watcall]
// ================================================================================================

longlong __watcall sub_333d7(undefined4 param_1,uint unaff_EDX)

{
  int iVar1;
  undefined4 uVar2;
  
  __CHK(0x20);
  save_settings(&settings_exhibition);
  apply_settings(&settings_league);
  iVar1 = sub_3b8b0();
  save_settings(&settings_league);
  apply_settings(&settings_exhibition);
  if (iVar1 != 0) {
    uVar2 = allocmem(&aTemp_c1783,0x300,0x20);
    getpalette(0,0x100,uVar2);
    fade_palette(1,uVar2,0x10);
    freemem(uVar2);
    return CONCAT44(unaff_EDX,2);
  }
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// sub_33469 @ 0x33469 [__watcall]
// ================================================================================================

longlong __watcall sub_33469(undefined4 param_1,uint unaff_EDX)

{
  int iVar1;
  undefined4 uVar2;
  
  __CHK(0x20);
  save_settings(&settings_exhibition);
  apply_settings(&settings_league);
  iVar1 = league_merge_check();
  save_settings(&settings_league);
  apply_settings(&settings_exhibition);
  if (iVar1 != 0) {
    uVar2 = allocmem(&aTemp_c1783,0x300,0x20);
    getpalette(0,0x100,uVar2);
    fade_palette(1,uVar2,0x10);
    freemem(uVar2);
    return CONCAT44(unaff_EDX,2);
  }
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// sub_334fb @ 0x334fb [__watcall]
// ================================================================================================

undefined4 __watcall sub_334fb(void)

{
  __CHK(4);
  save_settings(&settings_exhibition);
  apply_settings(&settings_league);
  league_merge_warning();
  save_settings(&settings_league);
  apply_settings(&settings_exhibition);
  return 0;
}


// ================================================================================================
// sub_33523 @ 0x33523 [__watcall]
// ================================================================================================

undefined8 __watcall sub_33523(undefined4 param_1,undefined4 unaff_EDX)

{
  undefined4 uVar1;
  
  __CHK(0x20);
  save_settings(&settings_exhibition);
  apply_settings(&settings_league);
  set_menu_mode(3);
  statistics_menu();
  set_menu_mode(0);
  save_settings(&settings_league);
  apply_settings(&settings_exhibition);
  uVar1 = allocmem(&aTemp_c1783,0x300,0x20);
  getpalette(0,0x100,uVar1);
  fade_palette(1,uVar1,0x10);
  freemem(uVar1);
  return CONCAT44(unaff_EDX,2);
}


// ================================================================================================
// league_calendar_screen @ 0x33559 [__watcall]
// ================================================================================================

undefined8 __watcall league_calendar_screen(int *param_1,undefined4 unaff_EDX)

{
  int iVar1;
  undefined4 uVar2;
  char acStack_30 [32];
  
  __CHK(0x40);
  save_settings(&settings_exhibition);
  apply_settings(&settings_league);
  set_menu_mode(3);
  sub_7a6ad(1);
  set_hub_title(2);
  if (*param_1 < 0) {
    strcpy(acStack_30,&league_dir);
    strcat(acStack_30,aGameSav_c1788);
    iVar1 = file_open_read(acStack_30,param_1);
    if (iVar1 != 0) {
      *param_1 = -1;
    }
  }
  league_calendar_flow(param_1);
  dword_c65c0 = hub_sports_central;
  dword_c65c4 = hub_playoff_tree;
  dword_c65c8 = hub_league_calendar;
  dword_c65cc = hub_standings;
  dword_c65d0 = hub_stats;
  set_menu_mode(0);
  save_settings(&settings_league);
  apply_settings(&settings_exhibition);
  uVar2 = allocmem(&aTemp_c1783,0x300,0x20);
  getpalette(0,0x100,uVar2);
  fade_palette(1,uVar2,0x10);
  freemem(uVar2);
  return CONCAT44(unaff_EDX,2);
}


// ================================================================================================
// sub_3366f @ 0x3366f [__watcall]
// ================================================================================================

longlong __watcall sub_3366f(undefined4 param_1,uint unaff_EDX)

{
  int iVar1;
  
  __CHK(8);
  save_settings(&settings_exhibition);
  apply_settings(&settings_league);
  dword_c53fb = 0;
  iVar1 = sub_80075();
  if (iVar1 == 0) {
    apply_settings(&settings_exhibition);
    return CONCAT44(unaff_EDX,2);
  }
  apply_settings(&settings_exhibition);
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// sub_336be @ 0x336be [__watcall]
// ================================================================================================

undefined4 __watcall sub_336be(void)

{
  __CHK(4);
  save_settings(&settings_exhibition);
  apply_settings(&settings_league);
  load_game_set_db();
  save_settings(&settings_league);
  apply_settings(&settings_exhibition);
  return 0;
}


// ================================================================================================
// sub_336e6 @ 0x336e6 [__watcall]
// ================================================================================================

undefined8 __watcall sub_336e6(undefined4 param_1,undefined4 unaff_EDX)

{
  undefined4 uVar1;
  
  __CHK(0x20);
  save_settings(&settings_exhibition);
  apply_settings(&settings_league);
  set_menu_mode(3);
  select_team_dialog();
  set_menu_mode(0);
  save_settings(&settings_league);
  apply_settings(&settings_exhibition);
  uVar1 = allocmem(&aTemp_c1783,0x300,0x20);
  getpalette(0,0x100,uVar1);
  fade_palette(1,uVar1,0x10);
  freemem(uVar1);
  return CONCAT44(unaff_EDX,2);
}


// ================================================================================================
// sub_3371c @ 0x3371c [__watcall]
// ================================================================================================

void __watcall sub_3371c(void)

{
  __CHK(4);
  return;
}


// ================================================================================================
// sub_33727 @ 0x33727 [__watcall]
// ================================================================================================

void __watcall sub_33727(void)

{
  __CHK(0x1c);
  if (dword_c73d4 != 0) {
    freemem(dword_c73d4);
    dword_c73d4 = 0;
  }
  if (dword_c73d0 != 0) {
    freemem(dword_c73d0);
    dword_c73d0 = 0;
    dword_c7440 = 0xffffffff;
  }
  return;
}


// ================================================================================================
// load_rink @ 0x3377c [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall load_rink(int param_1)

{
  undefined2 uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined *puVar5;
  undefined local_38 [16];
  undefined4 local_28;
  undefined4 uStack_24;
  short sStack_20;
  short sStack_1e;
  short sStack_1c;
  
  __CHK(0x48);
  if ((dword_c73d4 != 0) && (iVar2 = sub_8dbc0(dword_c73d4), iVar2 != 0x37840)) {
    freemem(dword_c73d4);
    dword_c73d4 = 0;
  }
  if ((dword_c73d0 != 0) && (iVar2 = sub_8dbc0(dword_c73d0), iVar2 != 0x37840)) {
    freemem(dword_c73d0);
    dword_c73d0 = 0;
  }
  if (dword_c73d0 == 0) {
    dword_c73d0 = windowdefp(0x180,0x250,0);
    dword_c7440 = -1;
  }
  if (param_1 != dword_c7440) {
    puVar5 = install_path;
    if (byte_ed927 != '\x01') {
      puVar5 = (undefined *)0x0;
    }
    make_path(local_38,puVar5,&aRink_c1794,0);
    uVar3 = loadshapes(local_38,0);
    dword_dd6ac = CONCAT22(0x4a,(undefined2)dword_dd6ac);
    ram0x000dd6a6 = CONCAT22(0x30,dword_dd6a4._2_2_);
    setscreen(dword_c73d0);
    uVar4 = locateshape(uVar3,&aRink_c1794);
    drawshape_remap_home(uVar4);
    freemem(uVar3);
    puVar5 = install_path;
    if ((&unk_ed7cd)[*(int *)(&unk_c73d8 + param_1 * 4)] != '\x01') {
      puVar5 = (undefined *)0x0;
    }
    make_path(local_38,puVar5,&aBOS_c7298 + param_1 * 3,&aTil);
    sStack_1c = filesize(local_38);
    if ((int)sStack_1c % 0x40 != 0) {
      fatalerror(aInvalidFileSSizeD,local_38,(int)sStack_1c);
    }
    local_28 = allocmem(aTILES,(int)sStack_1c,0);
    iVar2 = sub_92ee4(local_38,local_28);
    if (iVar2 == 0) {
      fatalerror(aErrorLoadingFileS,local_38);
    }
    puVar5 = install_path;
    if ((&file_on_disk)[*(int *)(&unk_c73d8 + param_1 * 4)] != '\x01') {
      puVar5 = (undefined *)0x0;
    }
    make_path(local_38,puVar5,&aBOS_c7298 + param_1 * 3,&aMap);
    uVar3 = loadfile(local_38,0);
    iVar2 = param_1 * 0xc;
    sStack_20 = (short)((int)(((int)sStack_1c + ((int)sStack_1c >> 0xf) * -0x40) -
                             (uint)(((int)sStack_1c >> 0xf) << 5 < 0)) >> 6);
    sStack_1e = sStack_20 >> 0xf;
    uStack_24 = uVar3;
    load_rink_tiles(uVar3,local_28,(int)sStack_20,*(int *)(&unk_c729c + iVar2) >> 0x10,
                    *(int *)((int)&aBOS_c7298 + iVar2 + 2) >> 0x10,0);
    if (0 < *(short *)(&unk_c72a0 + iVar2)) {
      load_rink_tiles(uVar3,local_28,CONCAT22(sStack_1e,sStack_20),
                      *(int *)(&unk_c72a0 + iVar2) >> 0x10,*(int *)(&unk_c729e + iVar2) >> 0x10,
                      0x6000);
    }
    freemem(uStack_24);
    freemem(local_28);
    dword_c7440 = param_1;
  }
  *(short *)(*(int *)(dword_c73d0 + 0x2c) + 4) = dword_dd6a8 << 3;
  *(short *)(*(int *)(dword_c73d0 + 0x2c) + 6) = dword_dd6ac._2_2_ << 3;
  iVar2 = dword_c73d0;
  **(undefined **)(dword_c73d0 + 0x2c) = 0;
  **(uint **)(iVar2 + 0x2c) = **(uint **)(iVar2 + 0x2c) & 0xff;
  iVar2 = *(int *)(dword_c73d0 + 0x2c);
  *(undefined2 *)(iVar2 + 0xe) = 0;
  uVar1 = *(undefined2 *)(iVar2 + 0xe);
  *(undefined2 *)(*(int *)(dword_c73d0 + 0x2c) + 0xc) = uVar1;
  *(undefined2 *)(*(int *)(dword_c73d0 + 0x2c) + 10) = uVar1;
  *(undefined2 *)(*(int *)(dword_c73d0 + 0x2c) + 8) = uVar1;
  if (dword_c73d4 == 0) {
    dword_c73d4 = windowdefp(0x180,0x250,0);
  }
  *(short *)(*(int *)(dword_c73d4 + 0x2c) + 4) = dword_dd6a8 << 3;
  *(short *)(*(int *)(dword_c73d4 + 0x2c) + 6) = dword_dd6ac._2_2_ << 3;
  iVar2 = dword_c73d4;
  **(undefined **)(dword_c73d4 + 0x2c) = 0;
  **(uint **)(iVar2 + 0x2c) = **(uint **)(iVar2 + 0x2c) & 0xff;
  iVar2 = *(int *)(dword_c73d4 + 0x2c);
  *(undefined2 *)(iVar2 + 0xe) = 0;
  uVar1 = *(undefined2 *)(iVar2 + 0xe);
  *(undefined2 *)(*(int *)(dword_c73d4 + 0x2c) + 0xc) = uVar1;
  *(undefined2 *)(*(int *)(dword_c73d4 + 0x2c) + 10) = uVar1;
  *(undefined2 *)(*(int *)(dword_c73d4 + 0x2c) + 8) = uVar1;
  iVar2 = (dword_dd6ac >> 0x10) * 4 + -0x3c;
  _dword_dd6b0 = (undefined2)
                 ((int)((iVar2 + (iVar2 >> 0x1f) * -8) - (uint)((iVar2 >> 0x1f) << 2 < 0)) >> 3);
  _dword_dd6aa = (undefined2)((longlong)iVar2 % 8);
  iVar2 = (ram0x000dd6a6 >> 0x10) << 2;
  word_dd6b2 = (short)((longlong)iVar2 / 8) + -0x14;
  dword_dd6ac = CONCAT22(dword_dd6ac._2_2_,(short)((longlong)iVar2 % 8));
  mark_rink_dirty(0x180);
  set_camera_offset(0,0);
  set_view_rect(0,0,0x180,0x250);
  sub_6a0f6(dword_c73d4);
  sub_6a156(dword_c73d0);
  mark_rink_dirty(1);
  sub_6a106();
  sub_6ad4f();
  return;
}


// ================================================================================================
// load_rink_tiles @ 0x33c08 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall load_rink_tiles(short *param_1,int unaff_EDX,undefined4 param_3,short unaff_CX)

{
  int iVar1;
  short sVar2;
  short sVar3;
  unkbyte10 Var4;
  int iVar5;
  uint uVar6;
  char *pcVar7;
  char *pcVar8;
  int iVar9;
  uint uVar10;
  uint uVar11;
  int iVar12;
  int iStack00000006;
  unkbyte10 in_stack_00000002;
  int local_1c;
  
  Var4 = in_stack_00000002;
  iStack00000006 = (int)((unkuint10)in_stack_00000002 >> 0x20);
  iVar5 = iStack00000006;
  __CHK(0x2c);
  sVar2 = param_1[1];
  sVar3 = *param_1;
  local_1c = 0;
  do {
    if (sVar2 <= local_1c) {
      return;
    }
    for (iVar1 = 0; iVar1 < sVar3; iVar1 = iVar1 + 1) {
      uVar6 = (uint)param_1[sVar3 * local_1c + iVar1 + 3];
      uVar10 = uVar6 & 0x4000 ^ iVar5 >> 0x10;
      uVar11 = iVar5 >> 0x10 ^ uVar6 & 0x2000;
      pcVar8 = (char *)(unaff_EDX + (uVar6 & 0x3ff) * 0x40);
      iStack00000006._2_2_ = (short)((unkuint10)Var4 >> 0x30);
      iVar12 = ram0x000dd6a6 >> 0x10;
      iVar9 = (int)Var4 >> 0x10;
      if (iStack00000006._2_2_ == 0) {
        pcVar7 = (char *)(*(int *)(dword_c73d0 + 0x2c) + 0x10 +
                         (local_1c + unaff_CX) * iVar12 * 0x40 + (iVar9 + iVar1) * 8);
      }
      else {
        pcVar7 = (char *)(*(int *)(dword_c73d0 + 0x2c) + 0x10 +
                         (unaff_CX - local_1c) * iVar12 * 0x40 + (iVar9 - iVar1) * 8);
      }
      if (uVar10 != 0) {
        pcVar7 = pcVar7 + iVar12 * 0x38;
      }
      if (uVar11 != 0) {
        pcVar7 = pcVar7 + 7;
      }
      iVar12 = 0;
      do {
        iVar9 = 0;
        do {
          if (*pcVar8 != -1) {
            *pcVar7 = *pcVar8;
          }
          pcVar8 = pcVar8 + 1;
          if (uVar11 == 0) {
            pcVar7 = pcVar7 + 1;
          }
          else {
            pcVar7 = pcVar7 + -1;
          }
          iVar9 = iVar9 + 1;
        } while (iVar9 < 8);
        iVar9 = ram0x000dd6a6 >> 0x10;
        if (uVar10 == 0) {
          if (uVar11 != 0) {
            iVar9 = iVar9 << 3;
            goto LAB_00033d5e;
          }
          iVar9 = iVar9 << 3;
LAB_00033d95:
          iVar9 = iVar9 + -8;
        }
        else {
          if (uVar11 == 0) {
            iVar9 = iVar9 * -8;
            goto LAB_00033d95;
          }
          iVar9 = iVar9 * -8;
LAB_00033d5e:
          iVar9 = iVar9 + 8;
        }
        pcVar7 = pcVar7 + iVar9;
        iVar12 = iVar12 + 1;
      } while (iVar12 < 8);
    }
    local_1c = local_1c + 1;
  } while( true );
}


// ================================================================================================
// draw_rink @ 0x33dd3 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __watcall draw_rink(int param_1,int unaff_EDX)

{
  int iVar1;
  
  __CHK(0x10);
  iVar1 = param_1;
  if (-dword_c7444 != param_1) {
    word_dd6b2 = (undefined2)(param_1 >> 3);
    iVar1 = param_1 / 8;
    dword_dd6ac._0_2_ = (undefined2)((longlong)param_1 % 8);
  }
  if (-dword_c7448 != unaff_EDX) {
    _dword_dd6b0 = (undefined2)(unaff_EDX >> 3);
    iVar1 = unaff_EDX / 8;
    _dword_dd6aa = (undefined2)((longlong)unaff_EDX % 8);
  }
  if (-dword_c7448 != unaff_EDX || -dword_c7444 != param_1) {
    dword_c7444 = -param_1;
    dword_c7448 = -unaff_EDX;
    iVar1 = mark_rink_dirty(3);
  }
  return iVar1;
}


// ================================================================================================
// sub_33e6a @ 0x33e6a [__watcall]
// ================================================================================================

undefined8 __watcall sub_33e6a(int param_1,undefined4 unaff_EDX)

{
  int iVar1;
  int unaff_EBP;
  int iVar2;
  int iVar3;
  ulonglong uVar4;
  undefined local_28 [8];
  int local_20;
  uint uStackY_1c;
  
  __CHK(0x30);
  local_20 = getticks();
  iVar3 = 0;
  iVar2 = 0;
  do {
    iVar1 = event_queue_pop();
    if (iVar1 != 0) {
      uVar4 = (*ui_poll_callback)();
      uStackY_1c = (uint)uVar4;
      if ((uVar4 & 2) != 0) {
        if (iVar2 == 0) {
          unaff_EBP = getticks(uStackY_1c,(int)(uVar4 >> 0x20),local_28);
        }
        else {
          iVar3 = -1;
        }
        iVar2 = iVar2 + 1;
      }
      if ((uStackY_1c & 4) != 0) {
        iVar2 = 3;
        iVar3 = -1;
      }
    }
    iVar1 = getticks();
    if ((iVar2 != 0) && (0x14 < iVar1 - unaff_EBP)) {
      iVar3 = -1;
    }
  } while ((iVar3 == 0) && (iVar1 - local_20 < param_1));
  return CONCAT44(unaff_EDX,iVar2);
}


// ================================================================================================
// load_crests @ 0x33f02 [__watcall]
// ================================================================================================

void __watcall load_crests(void)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined *puVar4;
  undefined auStack_320 [480];
  undefined auStack_140 [288];
  undefined auStack_20 [16];
  
  __CHK(0x330);
  getpalette(0,0x100,auStack_320);
  fade_palette(1,auStack_320,0x10);
  puVar4 = install_path;
  if (byte_ed821 != '\x01') {
    puVar4 = (undefined *)0x0;
  }
  make_path(auStack_20,puVar4,aCRESTS3,&aBIN);
  iVar1 = loadfile(auStack_20,0);
  iVar2 = 0x1e0;
  do {
    auStack_320[iVar2] = *(undefined *)(iVar1 + -0x1e0 + iVar2);
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0x300);
  freemem(iVar1);
  uVar3 = loadshapes(&unk_dc890,0);
  iVar1 = locateshape(uVar3,&aPal_c17e8);
  iVar2 = 0;
  do {
    auStack_320[iVar2] = *(undefined *)(iVar1 + 0x10 + iVar2);
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0x180);
  iVar2 = 0x2f1;
  do {
    auStack_320[iVar2] = *(undefined *)(iVar1 + 0x10 + iVar2);
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0x2fd);
  freemem(uVar3);
  fade_palette(0,auStack_320,0x10);
  return;
}


// ================================================================================================
// calendar_draw_games @ 0x33ffd [__watcall]
// ================================================================================================

void __watcall
calendar_draw_games(int param_1,int param_2,undefined4 param_3,int unaff_ECX,int param_5,
                   uint param_6,undefined4 param_7,undefined4 param_8)

{
  byte bVar1;
  undefined *puVar2;
  undefined4 uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  char *pcVar8;
  byte *pbVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  undefined2 *puVar13;
  undefined auStack_a8 [64];
  char cStack_68;
  undefined uStack_67;
  undefined uStack_66;
  undefined uStack_65;
  char acStack_48 [16];
  int local_38;
  int local_34;
  undefined4 local_30;
  int local_2c;
  int local_28;
  int local_24;
  undefined4 local_20;
  int local_1c;
  undefined4 local_18;
  int local_14;
  uint uStack_10;
  
  __CHK(0xcc);
  local_30 = locateshape(param_8,&aBoxr);
  local_20 = locateshape(param_8,&aBoxb);
  uVar3 = locateshape(param_8,&aBkgd_c17fe);
  drawshape_home(uVar3);
  sprintf(&cStack_68,a02d9D,param_1 + 1,(param_1 < 9) + 3);
  uVar3 = locateshape(param_8,&cStack_68);
  drawshape_home(uVar3);
  puVar2 = (&off_c57cc)[param_6];
  cStack_68 = '!';
  uStack_67 = *puVar2;
  uStack_66 = puVar2[1];
  uStack_65 = puVar2[2];
  drawshape_remap_centered(*(undefined4 *)(param_6 * 4 + param_2),0x26,0x3f);
  getfontstate(auStack_a8);
  setfont(param_7);
  iVar10 = dword_c898e;
  iVar12 = dword_c8976;
  if ((&unk_c845e)[param_1] != '\0') {
    iVar10 = dword_c897a;
    iVar12 = dword_c895e;
  }
  dword_d42a8 = 0xb6;
  printstr_at(&aHome,iVar12 + 7,iVar10 + 5);
  dword_d42a8 = 0xb7;
  printstr_at(&aAway,iVar12 + 7,iVar10 + 0x11);
  iVar10 = 0;
  while (iVar10 < (int)(uint)(byte)(&unk_c8445)[param_1]) {
    iVar12 = (&dword_c895e)[(int)((uint)(byte)(&unk_c845e)[param_1] + iVar10) % 7];
    iVar11 = (&dword_c897a)[(int)((uint)(byte)(&unk_c845e)[param_1] + iVar10) / 7];
    iVar10 = iVar10 + 1;
    sprintf(&cStack_68,(char *)&aD_c1815,iVar10);
    dword_d42a8 = 0xc0;
    printstr_at(&cStack_68,iVar12 + 4,iVar11 + 1);
    dword_d42a8 = 0xff;
    printstr_at(&cStack_68,iVar12 + 3,iVar11);
  }
  local_1c = -1;
  iVar10 = 0;
  do {
    if (param_5 <= iVar10) {
      if (-1 < local_1c) {
        iVar10 = (uint)*(byte *)(local_1c * 6 + unaff_ECX + 1) + (uint)(byte)(&unk_c845e)[param_1] +
                 -1;
        iVar12 = (&dword_c895e)[iVar10 % 7];
        iVar11 = (&dword_c897a)[iVar10 / 7];
        local_24 = iVar12 + 0x4c;
        iVar10 = iVar11 + 0x3e;
        local_38 = iVar11 + -1;
        local_34 = iVar12 + -1;
        sub_b4fac(local_34,local_38,local_24,local_38,0xbb);
        local_2c = local_24 + -1;
        sub_b4fac(iVar12,iVar11,local_2c,iVar11,0xbb);
        sub_b4fac(local_34,local_38,local_34,iVar10,0xbb);
        local_28 = iVar11 + 0x3d;
        sub_b4fac(iVar12,iVar11,iVar12,local_28,0xbb);
        sub_b4fac(local_24,local_38,local_24,iVar10,0xbb);
        sub_b4fac(local_2c,iVar11,local_2c,local_28,0xbb);
        sub_b4fac(local_34,iVar10,local_24,iVar10,0xbb);
        sub_b4fac(iVar12,local_28,local_2c,local_28,0xbb);
      }
      setfontstate(auStack_a8);
      return;
    }
    pbVar9 = (byte *)(iVar10 * 6 + unaff_ECX);
    if ((uint)*pbVar9 == param_1 + 1U) {
      iVar12 = (uint)(byte)(&unk_c845e)[param_1] + CONCAT31((int3)(param_1 + 1U >> 8),pbVar9[1]) +
               -1;
      iVar11 = (&dword_c895e)[iVar12 % 7];
      iVar12 = (&dword_c897a)[iVar12 / 7];
      uStack_10 = (uint)pbVar9[2];
      if (uStack_10 == param_6) {
        local_18 = local_30;
        uStack_10 = (uint)pbVar9[3];
        bVar1 = pbVar9[5];
        uVar6 = (uint)bVar1;
        if (bVar1 < pbVar9[4]) {
          uVar4 = (uint)pbVar9[4];
LAB_000342ae:
          puVar13 = &aW_c1818;
          uVar5 = uVar4;
          uVar4 = uVar6;
        }
        else {
          if (pbVar9[4] < bVar1) {
            uVar4 = (uint)pbVar9[4];
            goto LAB_000342c5;
          }
          uVar5 = (uint)pbVar9[4];
          puVar13 = &aT_c1825;
          uVar4 = uVar6;
        }
      }
      else {
        local_18 = local_20;
        bVar1 = pbVar9[5];
        uVar4 = (uint)bVar1;
        if (pbVar9[4] <= bVar1) {
          if (bVar1 <= pbVar9[4]) {
            uVar5 = (uint)pbVar9[4];
            puVar13 = &aT_c1825;
            goto LAB_00034328;
          }
          uVar6 = (uint)pbVar9[4];
          goto LAB_000342ae;
        }
        uVar6 = (uint)pbVar9[4];
LAB_000342c5:
        puVar13 = &aL_c1823;
        uVar5 = uVar4;
        uVar4 = uVar6;
      }
LAB_00034328:
      sprintf(acStack_48,unk_c181a,puVar13,uVar5,uVar4);
      local_14 = unaff_ECX + iVar10 * 6;
      if ((*(char *)(local_14 + 4) == -1) || (*(char *)(local_14 + 5) == -1)) {
        drawshape_remap(local_18,iVar11,iVar12);
        drawshape_remap(*(undefined4 *)(uStack_10 * 4 + param_2),iVar11,iVar12);
        sprintf(&cStack_68,(char *)&aD_c1815,(uint)*(byte *)(unaff_ECX + 1 + iVar10 * 6));
        dword_d42a8 = 0xff;
        printstr_at(&cStack_68,iVar11 + 4,iVar12 + 1);
        dword_d42a8 = 0xc0;
        iVar11 = iVar11 + 3;
        pcVar8 = &cStack_68;
      }
      else {
        drawshape_remap(*(undefined4 *)(uStack_10 * 4 + param_2),iVar11,iVar12);
        sprintf(&cStack_68,(char *)&aD_c1815,(uint)*(byte *)(local_14 + 1));
        dword_d42a8 = 0xc0;
        printstr_at(&cStack_68,iVar11 + 4,iVar12 + 1);
        dword_d42a8 = 0xff;
        printstr_at(&cStack_68,iVar11 + 3,iVar12);
        drawshape_remap(local_18,iVar11,iVar12);
        dword_d42a8 = 0xff;
        iVar7 = textwidth(acStack_48,iVar12 + 0x31);
        printstr_at(acStack_48,(iVar11 + 0x27) - (iVar7 >> 1));
        dword_d42a8 = 0xc0;
        iVar12 = iVar12 + 0x30;
        iVar7 = textwidth(acStack_48,iVar12);
        iVar11 = (iVar11 + 0x26) - (iVar7 >> 1);
        pcVar8 = acStack_48;
      }
      printstr_at(pcVar8,iVar11,iVar12);
      pbVar9 = (byte *)(iVar10 * 6 + unaff_ECX);
      if ((*pbVar9 == dword_ddd30) && (CONCAT31((int3)(dword_ddd30 >> 8),pbVar9[1]) == dword_ddd28))
      {
        local_1c = iVar10;
      }
    }
    iVar10 = iVar10 + 1;
  } while( true );
}


// ================================================================================================
// sub_34691 @ 0x34691 [__watcall]
// ================================================================================================

void __watcall sub_34691(void)

{
  __CHK(0x10);
  funcptr_c85f6 = sub_34691;
  funcptr_c8616 = sub_346fe;
  dword_dd7a0 = dword_dd7a0 + 1;
  if (dword_dd7a0 == 0xc) {
    dword_dd7a0 = 0;
  }
  if (dword_dd7a0 == 6) {
    dword_dd7a0 = 5;
  }
  if (dword_dd7a0 == 5) {
    funcptr_c85f6 = (undefined *)0x0;
  }
  dword_dd780 = 0xffffffff;
  return;
}


// ================================================================================================
// sub_346fe @ 0x346fe [__watcall]
// ================================================================================================

void __watcall sub_346fe(void)

{
  __CHK(0xc);
  funcptr_c85f6 = sub_34691;
  funcptr_c8616 = sub_346fe;
  dword_dd7a0 = dword_dd7a0 + -1;
  if (dword_dd7a0 == -1) {
    dword_dd7a0 = 0xb;
  }
  if (dword_dd7a0 == 8) {
    dword_dd7a0 = 9;
  }
  if (dword_dd7a0 == 9) {
    funcptr_c8616 = (undefined *)0x0;
  }
  dword_dd780 = 0xffffffff;
  return;
}


// ================================================================================================
// sub_3476b @ 0x3476b [__watcall]
// ================================================================================================

void __watcall sub_3476b(void)

{
  __CHK(8);
  dword_dd794 = 0xffffffff;
  dword_dd780 = 0xffffffff;
  return;
}


// ================================================================================================
// sub_34789 @ 0x34789 [__watcall]
// ================================================================================================

void __watcall
sub_34789(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  int iVar1;
  
  __CHK(0x18);
  iVar1 = locateshape(param_1,&aPal_c1827,unaff_EDX,unaff_ECX,unaff_EBX);
  fade_palette(0,iVar1 + 0x10,0x10);
  return;
}


// ================================================================================================
// sub_347b7 @ 0x347b7 [__watcall]
// ================================================================================================

void __watcall sub_347b7(uint param_1,int unaff_EDX,int unaff_EBX)

{
  int iVar1;
  uint uVar2;
  
  __CHK(0xc);
  iVar1 = unaff_EBX * 6 + unaff_EDX;
  uVar2 = (uint)*(byte *)(iVar1 + 2);
  if (param_1 == uVar2) {
    uVar2 = (uint)*(byte *)(iVar1 + 3);
  }
  else {
    param_1 = (uint)*(byte *)(iVar1 + 3);
  }
  if ((&unk_dd7cb)[uVar2 * 0x1e] != '\x01') {
    uVar2 = 0xffffffff;
  }
  unaff_EDX = unaff_EBX * 6 + unaff_EDX;
  sub_7db67(param_1,uVar2,*(undefined *)(unaff_EDX + 2),*(undefined *)(unaff_EDX + 3));
  return;
}


// ================================================================================================
// calendar_screen @ 0x34821 [__watcall]
// ================================================================================================

/* WARNING: Type propagation algorithm not settling */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __watcall calendar_screen(undefined4 param_1,undefined4 param_2,uint unaff_EBX)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  short sVar7;
  short sVar8;
  int iVar9;
  int *piVar10;
  undefined4 *puVar11;
  undefined4 uVar12;
  int iVar13;
  undefined *puVar14;
  int iVar15;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 *******pppppppuVar16;
  undefined4 *******pppppppuVar17;
  undefined4 *puVar18;
  char *pcVar19;
  undefined4 *puVar20;
  undefined4 *puVar21;
  byte bVar22;
  ulonglong uVar23;
  undefined8 uVar24;
  byte abStackY_304e6 [6];
  byte abStackY_304e0 [195820];
  undefined4 uVar25;
  undefined auStack_7e0 [768];
  byte abStack_4e0 [678];
  undefined4 uStack_23a;
  undefined4 auStack_154 [26];
  undefined auStack_ec [24];
  int local_d4 [8];
  char *local_b4 [3];
  int local_a8 [3];
  char *local_9c [6];
  int local_84;
  char *local_80;
  int local_7c;
  undefined4 *******local_78;
  undefined4 *******local_74;
  undefined4 *******local_70;
  undefined4 *******local_6c;
  undefined local_68 [4];
  undefined4 uStack_64;
  int local_60;
  undefined4 *******local_5c;
  undefined4 local_58;
  int local_54;
  undefined4 *******local_50;
  int local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 uStack_3c;
  undefined4 local_38;
  undefined4 local_34;
  short local_30;
  short local_2c;
  undefined4 uStack_28;
  short sStack_24;
  undefined4 uStack_22;
  undefined4 uStack_1e;
  undefined2 uStack_1a;
  undefined2 uStack_18;
  undefined2 uStack_16;
  short sStack_14;
  
  bVar22 = 0;
  __CHK(0x7f8);
  uStack_64 = 0xffffffff;
  local_34._0_2_ = 0;
  local_34._2_2_ = 0;
  local_48 = 0xc0;
  local_40 = 0xc;
  local_44 = 0x67;
  setdefaultscreen();
  clearclip(0);
  if ((sound_enabled != '\0') && (dword_c721d != 0)) {
    sound_fade(dword_d2431,3,100);
  }
  getpalette(0,0x100,&palette_save);
  fade_palette(1,&palette_save,0x10);
  if ((sound_enabled != '\0') && (dword_c721d != 0)) {
    do {
      iVar9 = sound_channel_status(ram0x000d242c >> 0x18,3);
    } while (iVar9 == 0);
    releasememblock(dword_c721d);
    dword_c721d = 0;
  }
  sub_479e9();
  dword_c65c0 = cal_hub_a;
  dword_c65c4 = cal_hub_b;
  dword_c65c8 = cal_hub_c;
  dword_c65cc = cal_hub_standings;
  dword_c65d0 = cal_hub_stats;
  set_dialog_colors(0xc,0xc0,0x67,0xc0,0xff);
  local_2c = 0;
  dword_dd780 = -1;
  dword_dd794 = 0;
  dword_ddd2c = 0;
  local_38 = font_main;
  puVar14 = install_path;
  if (byte_ed98d != '\x01') {
    puVar14 = (undefined *)0x0;
  }
  make_path(auStack_ec,puVar14,aCalendar_c182c,0);
  dword_c8992 = loadshapes(auStack_ec,0x20);
  puVar14 = install_path;
  if (byte_ed98e != '\x01') {
    puVar14 = (undefined *)0x0;
  }
  make_path(auStack_ec,puVar14,aCallogo,0);
  local_58 = loadshapes(auStack_ec,0x20);
  sVar7 = 0;
  while( true ) {
    uStack_18._1_1_ = (undefined)((ushort)sVar7 >> 8);
    uStack_18._0_1_ = (undefined)sVar7;
    if (0xff < sVar7) break;
    auStack_7e0[CONCAT13(uStack_18._1_1_,CONCAT12((undefined)uStack_18,uStack_1a)) >> 0x10] =
         (undefined)uStack_18;
    sVar7 = sVar7 + 1;
  }
  uStack_18 = sVar7;
  setremaptable(auStack_7e0);
  sVar7 = 0;
  while( true ) {
    uStack_18._1_1_ = (undefined)((ushort)sVar7 >> 8);
    uStack_18._0_1_ = (undefined)sVar7;
    uStack_18 = sVar7;
    if (0x19 < sVar7) break;
    iVar9 = CONCAT13(uStack_18._1_1_,CONCAT12((undefined)uStack_18,uStack_1a)) >> 0x10;
    uVar12 = locateshape(local_58,(&off_c57cc)[iVar9]);
    auStack_154[iVar9] = uVar12;
    sVar7 = uStack_18 + 1;
  }
  make_path(auStack_ec,param_1);
  sVar7 = file_open_read(auStack_ec,&uStack_64);
  if (sVar7 == 0) {
    sVar7 = file_read(uStack_64,&sStack_24,0);
  }
  if (sVar7 == 0) {
    dword_dd7a0 = -1;
    sVar8 = 5;
    uStack_28 = 0xffffffff;
    uStack_22 = CONCAT22(0xffff,(undefined2)uStack_22);
    uStack_18 = 0;
    while ((uStack_18 < 0x4ad && (sVar7 == 0))) {
      iVar9 = local_2c * 6;
      sVar7 = db_read_record2(uStack_64,abStack_4e0 + iVar9);
      if (sVar7 == 0) {
        if (uStack_18 == sStack_24) {
          if ((abStack_4e0[iVar9 + 2] == 0xff) || (abStack_4e0[iVar9 + 3] == 0xff)) {
            iVar9 = (int)local_2c;
            bVar3 = abStack_4e0[(iVar9 + -1) * 6];
            bVar1 = abStack_4e0[iVar9 * 6];
            bVar2 = abStack_4e0[iVar9 * 6 + 1];
          }
          else {
            bVar3 = abStack_4e0[iVar9];
            bVar1 = abStack_4e0[iVar9];
            bVar2 = abStack_4e0[iVar9 + 1];
          }
          dword_ddd30 = (uint)bVar1;
          sVar8 = bVar3 - 1;
          dword_ddd28 = (uint)bVar2;
        }
        if ((abStack_4e0[local_2c * 6 + 2] == unaff_EBX) ||
           (abStack_4e0[local_2c * 6 + 3] == unaff_EBX)) {
          iVar9 = local_2c * 6;
          if ((abStack_4e0[iVar9] != 0xff) && (abStack_4e0[iVar9 + 1] != 0xff)) {
            if (((abStack_4e0[iVar9 + 4] == 0xff) && (abStack_4e0[iVar9 + 5] == 0xff)) &&
               (dword_dd7a0 < 0)) {
              dword_dd7a0 = abStack_4e0[iVar9] - 1;
              uStack_28 = CONCAT22(uStack_16,uStack_18);
              uStack_22 = CONCAT22(local_2c,(undefined2)uStack_22);
            }
            *(short *)((int)&uStack_23a + local_2c * 2 + 2) = uStack_18;
            local_2c = local_2c + 1;
          }
        }
      }
      uStack_18 = uStack_18 + 1;
    }
    if (dword_dd7a0 < 0) {
      dword_dd7a0 = (int)sVar8;
    }
  }
  if (sVar7 != 0) {
    wait_sprite_fade();
  }
  file_close(&uStack_64);
  if ((-1 < (short)uStack_28) && (sVar7 == 0)) {
    iVar9 = uStack_22 >> 0x10;
    sub_347b7(unaff_EBX,abStack_4e0,iVar9);
    dword_ddd30 = (uint)abStack_4e0[iVar9 * 6];
    dword_ddd28 = (uint)abStack_4e0[iVar9 * 6 + 1];
    dword_dd780 = *(int *)((int)&uStack_23a + iVar9 * 2) >> 0x10;
  }
  if (sVar7 == 0) {
    if (dword_dd7a0 == 5) {
      funcptr_c85f6 = (undefined *)0x0;
    }
    else {
      funcptr_c85f6 = sub_34691;
    }
    if (dword_dd7a0 == 9) {
      funcptr_c8616 = (undefined *)0x0;
    }
    else {
      funcptr_c8616 = sub_346fe;
    }
    sStack_14 = (short)dword_dd7a0;
    setdefaultscreen();
    local_b4[0] = aStatistics_c864c + 0xb;
    local_9c[0] = (char *)0x3;
    local_b4[1] = (char *)0x0;
    local_a8[0] = 0;
    local_a8[1] = 0;
    local_9c[3] = (char *)0x0;
    local_9c[4] = (char *)0x0;
    local_d4[2] = 0;
    local_d4[3] = 0;
    wait_sprite_fade();
    setdefaultscreen();
    draw_menu_items(aStatistics_c864c + 0xb,3,local_48,local_40,local_44);
    calendar_draw_games(dword_dd7a0,auStack_154,uStack_3c,abStack_4e0,(int)local_2c,unaff_EBX,
                        local_38,dword_c8992);
    if ((sound_enabled != '\0') && (dword_c721d == 0)) {
      puVar14 = install_path;
      if (byte_ed9ae != '\x01') {
        puVar14 = (undefined *)0x0;
      }
      make_path(auStack_ec,puVar14,aCalendar_c182c,&aIff_c183d);
      dword_c721d = loadsound(auStack_ec);
      if ((dword_c721d != 0) && (((byte)option_flags & 0x40) != 0)) {
        playsample(dword_c721d,dword_d2431,3,0x4c);
      }
    }
    sub_34789(dword_c8992);
    local_5c = (undefined4 *******)
               allocmem(aPointer_c1842,
                        (((int)pointer_shapes[1] >> 0x10) + 1) *
                        ((*(int *)((int)pointer_shapes + 2) >> 0x10) * 4 + 4) + 0x11,0x20);
    pppppppuVar17 = local_5c + (uint)bVar22 * -2 + 1;
    puVar11 = pointer_shapes + (uint)bVar22 * -2 + 1;
    *local_5c = (undefined4 ******)*pointer_shapes;
    pppppppuVar16 = pppppppuVar17 + (uint)bVar22 * -2 + 1;
    puVar18 = puVar11 + (uint)bVar22 * -2 + 1;
    *pppppppuVar17 = (undefined4 ******)*puVar11;
    *pppppppuVar16 = (undefined4 ******)*puVar18;
    pppppppuVar16[(uint)bVar22 * -2 + 1] = (undefined4 ******)puVar18[(uint)bVar22 * -2 + 1];
    *(undefined *)(pppppppuVar16 + (uint)bVar22 * -2 + 1 + (uint)bVar22 * -2 + 1) =
         *(undefined *)(puVar18 + (uint)bVar22 * -2 + 1 + (uint)bVar22 * -2 + 1);
    *(short *)(local_5c + 1) = *(short *)(pointer_shapes + 1) + 1;
    *(short *)((int)local_5c + 6) = *(short *)((int)pointer_shapes + 6) + 1;
    local_50 = local_5c;
    getmouse(local_68,&local_6c,&local_70);
    local_74 = local_6c;
    local_78 = local_70;
    grabshape(local_5c,local_6c,local_70);
    pppppppuVar17 = local_70;
    drawshape_remap(pointer_shapes,local_6c,local_70);
    uVar23 = event_queue_reset();
    do {
      uVar12 = 0;
      do {
        uVar24 = event_queue_pop((int)uVar23,(int)(uVar23 >> 0x20),pppppppuVar17);
        uVar23 = CONCAT44((int)((ulonglong)uVar24 >> 0x20),uVar12);
        if ((int)uVar24 == 0) break;
        pppppppuVar17 = &local_78;
        uVar23 = (*ui_poll_callback)();
        uVar12 = (undefined4)uVar23;
      } while ((uVar23 & 2) == 0);
      pppppppuVar16 = local_50;
      uVar12 = (undefined4)(uVar23 >> 0x20);
      if ((uVar23 & 2) == 0) {
        if ((local_74 != local_6c) || (local_78 != local_70)) {
          drawshape(local_50,local_6c,local_70);
          grabshape(pppppppuVar16,local_74,local_78);
          pppppppuVar16 = local_78;
LAB_00035eea:
          drawshape_remap(pointer_shapes,local_74,local_78);
          uVar12 = extraout_EDX_00;
          pppppppuVar17 = pppppppuVar16;
          goto LAB_00035ef2;
        }
      }
      else {
        iVar9 = hit_test_menus(local_74,local_78,local_b4,local_34,local_b4 + 6,local_d4 + 2,
                               &local_7c,&local_80);
        if (iVar9 == 0) {
          drawshape(local_50,local_6c,local_70);
          if (local_34 == 0) {
            local_30 = -1;
            iVar9 = 0;
            sVar7 = uStack_18;
            if ((((0x51 < (int)local_74) && ((int)local_74 < 0x25f)) && (0x43 < (int)local_78)) &&
               ((int)local_78 < 0x1b2)) {
              sVar8 = (((short)((int)(local_78 + -0x11) / 0x3d << 3) -
                       (short)((int)(local_78 + -0x11) / 0x3d)) +
                      (short)(((int)local_74 + -0x52) / 0x4b)) -
                      (ushort)(byte)(&unk_c845e)[dword_dd7a0] % 7;
              uStack_1e = CONCAT22(sVar8,(undefined2)uStack_1e);
              if ((-1 < sVar8) && (sVar8 < (short)(ushort)(byte)(&unk_c8445)[dword_dd7a0])) {
                uStack_18._0_1_ = 0;
                uStack_18._1_1_ = 0;
                sVar7 = 0;
                while( true ) {
                  uVar5 = dword_ddd30;
                  uVar4 = dword_ddd28;
                  uStack_18._1_1_ = (undefined)((ushort)sVar7 >> 8);
                  uStack_18._0_1_ = (undefined)sVar7;
                  iVar9 = CONCAT22(local_34._2_2_,(short)local_34);
                  if (local_2c <= sVar7) break;
                  iVar15 = CONCAT13(uStack_18._1_1_,CONCAT12((undefined)uStack_18,uStack_1a)) >>
                           0x10;
                  iVar9 = iVar15 * 6;
                  if ((((uint)abStack_4e0[iVar9] == dword_dd7a0 + 1U) &&
                      (CONCAT31((int3)(dword_dd7a0 + 1U >> 8),abStack_4e0[iVar9 + 1]) ==
                       (uStack_1e >> 0x10) + 1)) &&
                     ((abStack_4e0[iVar9 + 4] == 0xff && (abStack_4e0[iVar9 + 5] == 0xff)))) {
                    if (*(int *)((int)&uStack_23a + iVar15 * 2) >> 0x10 == dword_dd780) {
                      dword_dd794 = -1;
                    }
                    if ((sStack_24 < 0x444) ||
                       (*(short *)((int)&uStack_23a +
                                  (CONCAT13(uStack_18._1_1_,CONCAT12((undefined)uStack_18,uStack_1a)
                                           ) >> 0x10) * 2 + 2) == (short)uStack_28)) {
                      local_30 = *(short *)((int)&uStack_23a +
                                           (CONCAT13(uStack_18._1_1_,
                                                     CONCAT12((undefined)uStack_18,uStack_1a)) >>
                                           0x10) * 2 + 2);
                      uStack_22 = CONCAT22(sVar7,(undefined2)uStack_22);
                      uStack_18._0_1_ = (undefined)local_2c;
                      uStack_18._1_1_ = (undefined)((ushort)local_2c >> 8);
                      sVar7 = local_2c;
                    }
                    dword_ddd30 = (uint)abStack_4e0[(uStack_22 >> 0x10) * 6];
                    dword_ddd28 = (uint)abStack_4e0[(uStack_22 >> 0x10) * 6 + 1];
                    uStack_18 = sVar7;
                    if (dword_dd794 == 0) {
                      sub_347b7(unaff_EBX,abStack_4e0);
                    }
                    setdefaultscreen();
                    draw_menu_items(aStatistics_c864c + 0xb,3,local_48,local_40,local_44);
                    if ((uVar5 == dword_ddd30) && (uVar4 != dword_ddd28)) {
                      iVar9 = (byte)(&unk_c845d)[dword_ddd30] + uVar4 + -1;
                      iVar15 = iVar9 % 7;
                      iVar9 = iVar9 / 7;
                      setclip((&dword_c895e)[iVar15] + -2,(&dword_c895e)[iVar15] + 0x4d,
                              (&dword_c897a)[iVar9] + -2,(&dword_c897a)[iVar9] + 0x3f);
                      calendar_draw_games(dword_dd7a0,auStack_154,uStack_3c,abStack_4e0,
                                          (int)local_2c,unaff_EBX,local_38,dword_c8992);
                    }
                    iVar9 = (byte)(&unk_c845d)[dword_ddd30] + dword_ddd28 + -1;
                    iVar15 = iVar9 % 7;
                    iVar9 = iVar9 / 7;
                    setclip((&dword_c895e)[iVar15] + -2,(&dword_c895e)[iVar15] + 0x4d,
                            (&dword_c897a)[iVar9] + -2,(&dword_c897a)[iVar9] + 0x3f);
                    calendar_draw_games(dword_dd7a0,auStack_154,uStack_3c,abStack_4e0,(int)local_2c,
                                        unaff_EBX,local_38,dword_c8992);
                    setclip(0,0x280,0,0x1e0);
                    sVar7 = uStack_18;
                  }
                  sVar7 = sVar7 + 1;
                  uStack_18._0_1_ = (undefined)sVar7;
                  uStack_18._1_1_ = (undefined)((ushort)sVar7 >> 8);
                }
              }
            }
            local_34 = iVar9;
            dword_dd780 = (int)local_30;
          }
          else {
            uStack_18._0_1_ = (undefined)local_34;
            uStack_18._1_1_ = (undefined)((uint)local_34 >> 8);
            sVar7 = (short)local_34;
            while( true ) {
              uStack_18._1_1_ = (undefined)((ushort)sVar7 >> 8);
              uStack_18._0_1_ = (undefined)sVar7;
              if (sVar7 < 0) break;
              iVar9 = CONCAT13(uStack_18._1_1_,CONCAT12((undefined)uStack_18,uStack_1a)) >> 0x10;
              uStack_18 = sVar7;
              if (local_b4[iVar9 + 3] != (char *)0x0) {
                drawshape(local_b4[iVar9 + 3],local_d4[iVar9 * 2 + 2],local_d4[iVar9 * 2 + 3]);
                local_d4[iVar9 * 2 + 2] = 0;
                local_d4[iVar9 * 2 + 3] = 0;
                freemem(local_b4[iVar9 + 3]);
              }
              sVar7 = uStack_18 + -1;
              uStack_18._0_1_ = (undefined)sVar7;
              uStack_18._1_1_ = (undefined)((ushort)sVar7 >> 8);
            }
            local_34 = 0;
            local_b4[1] = (char *)0x0;
            local_a8[0] = 0;
            local_a8[1] = 0;
            local_9c[4] = (char *)0x0;
            local_9c[1] = (char *)0x0;
          }
        }
        else {
          if (*(int *)(local_b4[local_7c] + (int)local_80 * 0x20 + 0x14) == 0) {
            if (*(int *)(local_b4[local_7c] + (int)local_80 * 0x20 + 0x18) == 0) {
              drawshape(local_50,local_6c,local_70);
              sVar7 = uStack_18;
              if (local_34 != local_7c) {
                uStack_18._0_1_ = (undefined)local_34;
                uStack_18._1_1_ = (undefined)((uint)local_34 >> 8);
                sVar7 = (short)local_34;
                while( true ) {
                  uStack_18._1_1_ = (undefined)((ushort)sVar7 >> 8);
                  uStack_18._0_1_ = (undefined)sVar7;
                  iVar9 = CONCAT13(uStack_18._1_1_,CONCAT12((undefined)uStack_18,uStack_1a)) >> 0x10
                  ;
                  if (iVar9 <= local_7c) break;
                  uStack_18 = sVar7;
                  local_b4[iVar9 + 9] = (char *)0x0;
                  if (local_b4[iVar9 + 3] != (char *)0x0) {
                    drawshape(local_b4[iVar9 + 3],local_d4[iVar9 * 2 + 2],local_d4[iVar9 * 2 + 3]);
                    local_d4[iVar9 * 2 + 2] = 0;
                    local_d4[iVar9 * 2 + 3] = 0;
                    freemem(local_b4[iVar9 + 3]);
                    local_b4[iVar9 + 3] = (char *)0x0;
                    local_b4[iVar9] = (char *)0x0;
                    local_b4[iVar9 + 6] = (char *)0x0;
                  }
                  sVar7 = uStack_18 + -1;
                  uStack_18._0_1_ = (undefined)sVar7;
                  uStack_18._1_1_ = (undefined)((ushort)sVar7 >> 8);
                }
                local_34._0_2_ = (short)local_7c;
                local_34._2_2_ = (undefined2)((uint)local_7c >> 0x10);
                local_34 = local_7c;
              }
              uVar25 = local_40;
              uStack_18 = sVar7;
              highlight_menu_item(local_b4[local_7c] + (int)local_b4[local_7c + 9] * 0x20,
                                  local_d4[local_7c * 2 + 2],local_d4[local_7c * 2 + 3],local_48,
                                  local_40,local_44);
              iVar6 = local_7c;
              local_b4[local_7c + 9] = local_80;
              iVar9 = local_d4[iVar6 * 2 + 3];
              iVar15 = local_d4[iVar6 * 2 + 2];
              pcVar19 = local_b4[iVar6] + (int)local_b4[iVar6 + 9] * 0x20;
              uVar12 = local_48;
            }
            else {
              drawshape(local_50,local_6c,local_70);
              sVar7 = uStack_18;
              iVar9 = local_34;
              if (local_34 != local_7c) {
                uStack_18._0_1_ = (undefined)local_34;
                uStack_18._1_1_ = (undefined)((uint)local_34 >> 8);
                sVar7 = (short)local_34;
                while( true ) {
                  uStack_18._1_1_ = (undefined)((ushort)sVar7 >> 8);
                  uStack_18._0_1_ = (undefined)sVar7;
                  iVar9 = CONCAT13(uStack_18._1_1_,CONCAT12((undefined)uStack_18,uStack_1a)) >> 0x10
                  ;
                  if (iVar9 <= local_7c) break;
                  uStack_18 = sVar7;
                  local_b4[iVar9 + 9] = (char *)0x0;
                  if (local_b4[iVar9 + 3] != (char *)0x0) {
                    drawshape(local_b4[iVar9 + 3],local_d4[iVar9 * 2 + 2],local_d4[iVar9 * 2 + 3]);
                    local_d4[iVar9 * 2 + 2] = 0;
                    local_d4[iVar9 * 2 + 3] = 0;
                    freemem(local_b4[iVar9 + 3]);
                    local_b4[iVar9 + 3] = (char *)0x0;
                    local_b4[iVar9] = (char *)0x0;
                    local_b4[iVar9 + 6] = (char *)0x0;
                  }
                  sVar7 = uStack_18 + -1;
                  uStack_18._0_1_ = (undefined)sVar7;
                  uStack_18._1_1_ = (undefined)((ushort)sVar7 >> 8);
                }
                local_34._0_2_ = (short)local_7c;
                local_34._2_2_ = (undefined2)((uint)local_7c >> 0x10);
                iVar9 = local_7c;
              }
              uStack_18 = sVar7;
              local_34 = iVar9;
              highlight_menu_item(local_b4[iVar9] + (int)local_b4[iVar9 + 9] * 0x20,
                                  local_d4[iVar9 * 2 + 2],local_d4[iVar9 * 2 + 3],local_48,local_40,
                                  local_44);
              local_b4[iVar9 + 9] = local_80;
              unhighlight_menu_item
                        (local_b4[iVar9] + (int)local_80 * 0x20,local_d4[iVar9 * 2 + 2],
                         local_d4[iVar9 * 2 + 3],local_48,local_40,local_44);
              iVar6 = local_7c;
              iVar13 = (int)local_80 * 0x20;
              iVar15 = iVar9 + 1;
              local_34._0_2_ = (short)iVar15;
              local_34._2_2_ = (undefined2)((uint)iVar15 >> 0x10);
              local_34 = iVar15;
              local_b4[iVar15] = *(char **)(local_b4[local_7c] + iVar13 + 0x18);
              piVar10 = (int *)(local_b4[iVar6] + iVar13);
              local_b4[iVar9 + 7] = (char *)piVar10[7];
              if (iVar15 == 1) {
                iVar9 = *piVar10;
              }
              else {
                iVar9 = piVar10[2];
              }
              local_d4[local_34 * 2 + 2] = iVar9 + local_d4[local_34 * 2];
              if (local_34 == 1) {
                iVar9 = *(int *)(local_b4[local_7c] + (int)local_80 * 0x20 + 0xc);
              }
              else {
                iVar9 = *(int *)(local_b4[local_7c] + (int)local_80 * 0x20 + 4);
              }
              local_54 = local_34 * 8;
              local_d4[local_34 * 2 + 3] = iVar9 + local_d4[local_34 * 2 + 1];
              local_4c = local_34 * 4;
              piVar10 = (int *)local_b4[local_34];
              local_84 = (piVar10[(int)local_b4[local_34 + 6] * 8 + -6] - *piVar10) + 1;
              local_60 = (piVar10[(int)local_b4[local_34 + 6] * 8 + -5] - piVar10[1]) + 1;
              puVar11 = (undefined4 *)allocmem(aMenubuff_c184a,local_84 * 4 * local_60 + 0x11,0x20);
              iVar9 = local_4c;
              *(undefined4 **)((int)local_b4 + local_4c + 0xc) = puVar11;
              puVar20 = puVar11 + (uint)bVar22 * -2 + 1;
              puVar18 = pointer_shapes + (uint)bVar22 * -2 + 1;
              *puVar11 = *pointer_shapes;
              puVar21 = puVar20 + (uint)bVar22 * -2 + 1;
              puVar11 = puVar18 + (uint)bVar22 * -2 + 1;
              *puVar20 = *puVar18;
              *puVar21 = *puVar11;
              puVar21[(uint)bVar22 * -2 + 1] = puVar11[(uint)bVar22 * -2 + 1];
              *(undefined *)(puVar21 + (uint)bVar22 * -2 + 1 + (uint)bVar22 * -2 + 1) =
                   *(undefined *)(puVar11 + (uint)bVar22 * -2 + 1 + (uint)bVar22 * -2 + 1);
              *(short *)(*(int *)((int)local_b4 + iVar9 + 0xc) + 4) = (short)local_84;
              *(short *)(*(int *)((int)local_b4 + local_4c + 0xc) + 6) = (short)local_60;
              grabshape(*(undefined4 *)((int)local_b4 + local_4c + 0xc),
                        *(undefined4 *)((int)local_d4 + local_54 + 8),
                        *(undefined4 *)((int)local_d4 + local_54 + 0xc));
              uVar12 = local_48;
              draw_menu(*(undefined4 *)((int)local_b4 + local_4c),
                        *(undefined4 *)((int)local_b4 + local_4c + 0x18),
                        *(undefined4 *)((int)local_d4 + local_54 + 8),
                        *(undefined4 *)((int)local_d4 + local_54 + 0xc),local_48,local_40,local_44);
              *(undefined4 *)((int)local_b4 + local_4c + 0x24) = 0;
              iVar9 = *(int *)((int)local_d4 + local_54 + 0xc);
              iVar15 = *(int *)((int)local_d4 + local_54 + 8);
              pcVar19 = *(char **)((int)local_b4 + local_4c);
              uVar25 = local_40;
            }
          }
          else {
            if (local_80 == local_b4[local_7c + 9]) {
              drawshape(local_50,local_6c,local_70);
              uStack_18._0_1_ = (undefined)local_34;
              uStack_18._1_1_ = (undefined)((uint)local_34 >> 8);
              sVar7 = (short)local_34;
              while( true ) {
                uStack_18._1_1_ = (undefined)((ushort)sVar7 >> 8);
                uStack_18._0_1_ = (undefined)sVar7;
                uStack_18 = sVar7;
                if (sVar7 < 0) break;
                iVar9 = CONCAT13(uStack_18._1_1_,CONCAT12((undefined)uStack_18,uStack_1a)) >> 0x10;
                if (local_b4[iVar9 + 3] != (char *)0x0) {
                  drawshape(local_b4[iVar9 + 3],local_d4[iVar9 * 2 + 2],local_d4[iVar9 * 2 + 3]);
                  local_d4[iVar9 * 2 + 2] = 0;
                  local_d4[iVar9 * 2 + 3] = 0;
                  freemem(local_b4[iVar9 + 3]);
                }
                sVar7 = uStack_18 + -1;
                uStack_18._0_1_ = (undefined)sVar7;
                uStack_18._1_1_ = (undefined)((ushort)sVar7 >> 8);
              }
              local_34._0_2_ = 0;
              local_34._2_2_ = 0;
              iVar9 = (**(code **)(local_b4[local_7c] + (int)local_80 * 0x20 + 0x14))();
              setremaptable(auStack_7e0);
              local_b4[1] = (char *)0x0;
              local_a8[0] = 0;
              local_a8[1] = 0;
              local_9c[4] = (char *)0x0;
              local_9c[1] = (char *)0x0;
              if (iVar9 == 1) {
                freemem(local_50);
                if ((sound_enabled != '\0') && (dword_c721d != 0)) {
                  sound_fade(dword_d2431,3,100);
                }
                return 0;
              }
              setmousepos(local_6c,local_70);
              local_74 = local_6c;
              local_78 = local_70;
              event_queue_reset();
              if (sStack_14 != dword_dd7a0) {
                setdefaultscreen();
                draw_menu_items(aStatistics_c864c + 0xb,3,local_48,local_40,local_44);
                calendar_draw_games(dword_dd7a0,auStack_154,uStack_3c,abStack_4e0,(int)local_2c,
                                    unaff_EBX,local_38,dword_c8992);
              }
              if (dword_ddd2c != 0) {
                setdefaultscreen();
                draw_menu_items(aStatistics_c864c + 0xb,3,local_48,local_40,local_44);
                calendar_draw_games(dword_dd7a0,auStack_154,uStack_3c,abStack_4e0,(int)local_2c,
                                    unaff_EBX,local_38,dword_c8992);
                sub_34789(dword_c8992);
                dword_ddd2c = 0;
              }
              sStack_14 = (short)dword_dd7a0;
              sVar7 = uStack_18;
              goto LAB_00035e6a;
            }
            drawshape(local_50,local_6c,local_70);
            sVar7 = uStack_18;
            if (local_34 != local_7c) {
              uStack_18._0_1_ = (undefined)local_34;
              uStack_18._1_1_ = (undefined)((uint)local_34 >> 8);
              sVar7 = (short)local_34;
              while( true ) {
                uStack_18._1_1_ = (undefined)((ushort)sVar7 >> 8);
                uStack_18._0_1_ = (undefined)sVar7;
                iVar9 = CONCAT13(uStack_18._1_1_,CONCAT12((undefined)uStack_18,uStack_1a)) >> 0x10;
                if (iVar9 <= local_7c) break;
                uStack_18 = sVar7;
                local_b4[iVar9 + 9] = (char *)0x0;
                if (local_b4[iVar9 + 3] != (char *)0x0) {
                  drawshape(local_b4[iVar9 + 3],local_d4[iVar9 * 2 + 2],local_d4[iVar9 * 2 + 3]);
                  local_d4[iVar9 * 2 + 3] = 0;
                  local_d4[iVar9 * 2 + 2] = 0;
                  freemem(local_b4[iVar9 + 3]);
                  local_b4[iVar9 + 3] = (char *)0x0;
                  local_b4[iVar9] = (char *)0x0;
                  local_b4[iVar9 + 6] = (char *)0x0;
                }
                sVar7 = uStack_18 + -1;
                uStack_18._0_1_ = (undefined)sVar7;
                uStack_18._1_1_ = (undefined)((ushort)sVar7 >> 8);
              }
              local_34._0_2_ = (short)local_7c;
              local_34._2_2_ = (undefined2)((uint)local_7c >> 0x10);
              local_34 = local_7c;
            }
            uStack_18 = sVar7;
            highlight_menu_item(local_b4[local_7c] + (int)local_b4[local_7c + 9] * 0x20,
                                local_d4[local_7c * 2 + 2],local_d4[local_7c * 2 + 3],local_48,
                                local_40,local_44);
            iVar6 = local_7c;
            local_b4[local_7c + 9] = local_80;
            iVar9 = local_d4[iVar6 * 2 + 3];
            iVar15 = local_d4[iVar6 * 2 + 2];
            pcVar19 = local_b4[iVar6] + (int)local_b4[iVar6 + 9] * 0x20;
            uVar12 = local_48;
            uVar25 = local_40;
          }
          unhighlight_menu_item(pcVar19,iVar15,iVar9,uVar12,uVar25,local_44);
          sVar7 = uStack_18;
        }
LAB_00035e6a:
        uStack_18 = sVar7;
        grabshape(local_50,local_6c,local_70);
        pppppppuVar17 = local_50;
        drawshape(local_50,local_6c,local_70);
        grabshape(local_50,local_74,local_78);
        uVar12 = extraout_EDX;
        pppppppuVar16 = local_74;
        if (dword_dd794 == 0) goto LAB_00035eea;
LAB_00035ef2:
        local_6c = local_74;
        local_70 = local_78;
      }
      uVar23 = CONCAT44(uVar12,local_78);
    } while (dword_dd794 == 0);
  }
  freemem(local_50);
  freemem(local_58);
  freemem(dword_c8992);
  dword_c8992 = 0;
  dword_c65c0 = exh_hub_sports_central;
  dword_c65c4 = exh_hub_playoff_tree;
  dword_c65c8 = exh_hub_league_calendar;
  dword_c65cc = exh_hub_standings;
  dword_c65d0 = exh_hub_stats;
  if ((sound_enabled != '\0') && (dword_c721d != 0)) {
    sound_fade(dword_d2431,3,100);
  }
  return dword_dd780;
}


// ================================================================================================
// league_import_export_check @ 0x35fb9 [__watcall]
// ================================================================================================

int __watcall
league_import_export_check(char *param_1,int unaff_EDX,int unaff_EBX,int unaff_ECX,int param_5)

{
  int iVar1;
  size_t sVar2;
  int iVar3;
  char *__src;
  undefined2 in_DS;
  undefined auStack_c0 [64];
  undefined auStack_80 [32];
  undefined auStack_60 [22];
  byte bStack_4a;
  char acStack_40 [16];
  char acStack_30 [12];
  undefined local_24 [4];
  undefined local_20 [4];
  undefined local_1c [4];
  undefined local_18 [4];
  undefined4 local_14;
  
  __CHK(0xd8);
  local_14 = 0xffffffff;
  iVar3 = 0;
  __src = (char *)(unaff_EBX * 0x1e + unaff_EDX);
  dword_c7ae8 = (char *)0x0;
  iVar1 = sub_41344(param_1,local_24);
  if (__src[0x17] != '\x01') goto LAB_0003614e;
  if ((iVar1 == unaff_EBX) ||
     ((iVar1 < 0 && ((__src[0x18] == '\x01' || ((__src[0x16] & 1U) != 0)))))) {
    if ((__src[0x16] & 2U) == 0) goto LAB_0003614e;
    dword_c7ae8 = aMustBeImportedFromTheDis;
  }
  else if (unaff_ECX == 0) {
    getmouse(local_18,local_1c,local_20);
    message_dialog(0xffffffff,0xffffffff,&off_c800c,2,0,0,local_1c,local_20,0xffffffff);
  }
  else {
    if (param_5 == 0) {
      iVar3 = sub_3d84f(param_1,__src,0xffffffff);
    }
    else {
      sub_41171(auStack_c0,__src,param_1);
      dword_c7615 = auStack_c0;
      iVar3 = player_id_read(param_1,__src,0xffffffff);
    }
    if (iVar3 != 0) goto LAB_0003614e;
    make_path(auStack_80,&byte_c816a,aPINFO,&aDB);
    iVar3 = file_open_read(auStack_80,&local_14);
    if (iVar3 == 0) {
      iVar3 = pinfo_read_record(local_14,auStack_60,unaff_EBX);
    }
    file_close(&local_14);
    if ((iVar3 != 0) || ((bStack_4a & 1) == 0)) goto LAB_0003614e;
    dword_c7ae8 = aMustBeExportedToTheDiskF;
  }
  iVar3 = 4;
LAB_0003614e:
  if (dword_c7ae8 != (char *)0x0) {
    strcpy(acStack_40,param_1);
    sVar2 = strcspn(acStack_40,(char *)CONCAT22((short)((uint)param_1 >> 0x10),in_DS));
    acStack_40[sVar2] = '\0';
    dword_c7ae4 = acStack_40;
    strcpy(acStack_30,__src);
    dword_c7aec = acStack_30;
    getmouse(local_18,local_1c,local_20);
    message_dialog(0xffffffff,0xffffffff,&off_c7ae0,5,0,0,local_1c,local_20,0xffffffff);
  }
  return iVar3;
}


// ================================================================================================
// sub_36207 @ 0x36207 [__watcall]
// ================================================================================================

void __watcall sub_36207(char *param_1,undefined4 param_2,int unaff_EBX,int unaff_ECX)

{
  char *__src;
  char acStack_8 [4];
  
  builtin_strncpy(acStack_8,"\x11b\x03",4);
  __CHK(0x18);
  if (*(char *)(unaff_EBX + 0x17 + unaff_ECX * 0x1e) == '\x01') {
    sprintf(acStack_8,a02d,unaff_ECX);
    strcpy(param_1,__src);
    strcat(param_1,&unk_c8115);
    strcat(param_1,(char *)&aS_c8117);
    strcat(param_1,acStack_8);
    return;
  }
  *param_1 = '\0';
  return;
}


// ================================================================================================
// season_record_result @ 0x3626d [__watcall]
// ================================================================================================

int __watcall
season_record_result
          (undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,uint unaff_ECX,int param_5,
          undefined4 param_6)

{
  short sVar1;
  short sVar2;
  char *pcVar3;
  int iVar4;
  int iVar5;
  ushort *puVar6;
  short *psVar7;
  uint uVar8;
  undefined auStack_410 [40];
  char local_3e8 [18];
  char acStack_3d6 [18];
  int aiStack_3c4 [25];
  int aiStack_360 [142];
  ushort local_128 [11];
  ushort auStack_112 [13];
  short asStack_f8 [4];
  undefined auStack_f0 [2];
  char cStack_ee;
  undefined4 uStack_c4;
  short local_bc [9];
  short asStack_aa [11];
  short asStack_94 [4];
  undefined auStack_8c [32];
  char acStack_6c [25];
  char local_53 [4];
  char cStack_4f;
  int iStack_4d;
  undefined uStack_47;
  undefined uStack_46;
  undefined1 *local_44 [6];
  int local_2c;
  int local_28;
  int local_24;
  char *local_20;
  int local_1c;
  int local_18;
  undefined local_14 [4];
  undefined uStack_10;
  undefined uStack_f;
  
  __CHK(0x420);
  local_44[5] = (undefined1 *)0xffffffff;
  local_44[4] = (undefined1 *)0xffffffff;
  local_44[3] = (undefined1 *)0xffffffff;
  local_44[2] = (undefined1 *)0xffffffff;
  local_44[0] = (undefined1 *)&unk_dc200;
  local_44[1] = &unk_dabf0;
  if (param_5 < 0x444) {
    local_20 = local_3e8;
    psVar7 = local_bc;
    puVar6 = local_128;
  }
  else {
    local_20 = acStack_3d6;
    psVar7 = asStack_aa;
    puVar6 = auStack_112;
  }
  make_path(auStack_8c,param_1,off_c80e7,unaff_EDX,unaff_EBX,unaff_EDX);
  iVar4 = file_open_rw(auStack_8c,local_44 + 5);
  if (iVar4 == 0) {
    make_path(auStack_8c,param_1,off_c80d7);
    iVar4 = file_open_read(auStack_8c,local_44 + 4);
  }
  if (iVar4 == 0) {
    make_path(auStack_8c,param_1,off_c80eb);
    iVar4 = file_open_rw(auStack_8c,local_44 + 3);
  }
  if (iVar4 == 0) {
    make_path(auStack_8c,param_6,aGSUMMARY);
    iVar4 = file_open_rw(auStack_8c,local_44 + 2);
  }
  if (iVar4 == 0) {
    iVar4 = db_read_record(local_44[5],auStack_410,unaff_EBX);
  }
  if (iVar4 != 0) goto LAB_000365ff;
  *local_20 = *local_20 + '\x01';
  if (dword_df722._2_2_ < dword_df622._2_2_) {
    local_18 = (dword_df722 >> 0x10) + 1;
    local_1c = iVar4;
    if (unaff_ECX == 0) {
LAB_0003641f:
      local_20[1] = local_20[1] + '\x01';
    }
    else {
LAB_0003642b:
      local_20[2] = local_20[2] + '\x01';
    }
  }
  else {
    if (dword_df622._2_2_ < dword_df722._2_2_) {
      local_18 = dword_df622._2_2_ + 1;
      local_1c = 1;
      if (unaff_ECX == 0) goto LAB_0003642b;
      goto LAB_0003641f;
    }
    local_1c = -1;
    local_20[3] = local_20[3] + '\x01';
    local_18 = dword_df622 >> 0x10;
  }
  local_2c = unaff_ECX * 0x100;
  *(short *)(local_20 + 4) =
       *(short *)(local_20 + 4) + *(short *)((int)&dword_df622 + unaff_ECX * 0x100 + 2);
  pcVar3 = local_20;
  iVar5 = (unaff_ECX ^ 1) * 0x100;
  *(short *)(local_20 + 6) = *(short *)(local_20 + 6) + *(short *)((int)&dword_df622 + iVar5 + 2);
  *(short *)(pcVar3 + 10) = *(short *)(pcVar3 + 10) + *(short *)((int)&dword_df616 + local_2c + 2);
  *(short *)(pcVar3 + 8) = *(short *)(pcVar3 + 8) + *(short *)((int)&dword_df616 + local_2c);
  *(short *)(pcVar3 + 0xe) = *(short *)(pcVar3 + 0xe) + *(short *)((int)&dword_df616 + iVar5 + 2);
  *(short *)(pcVar3 + 0xc) =
       *(short *)(pcVar3 + 0xc) + *(short *)(&dword_df616 + (unaff_ECX ^ 1) * 0x40);
  *(short *)(pcVar3 + 0x10) = *(short *)(pcVar3 + 0x10) + *(short *)((int)&dword_df61e + iVar5 + 2);
  local_24 = 0;
  while ((local_24 < 3 && (iVar4 == 0))) {
    if (*(int *)((int)&dword_e9af4 + local_24 * 4 + 2) >> 0x10 == unaff_ECX) {
      iVar4 = sub_1463d(local_44[4],auStack_f0,
                        aiStack_3c4[*(int *)(&unk_e9af8 + local_24 * 2) >> 0x10]);
      if (iVar4 == 0) {
        if (cStack_ee == 'G') {
          iVar4 = sub_3a266(local_44[3],local_128,uStack_c4);
        }
        else {
          iVar4 = sub_1478b(local_44[3],local_bc,uStack_c4);
        }
      }
      if (iVar4 == 0) {
        if (cStack_ee == 'G') {
          asStack_f8[local_24] = asStack_f8[local_24] + 1;
          iVar4 = sub_3a27d(local_44[3],local_128,uStack_c4);
        }
        else {
          asStack_94[local_24] = asStack_94[local_24] + 1;
          iVar4 = sub_3a24f(local_44[3],local_bc,uStack_c4);
        }
      }
    }
    local_24 = local_24 + 1;
  }
LAB_000365ff:
  if (local_1c < 0) {
    uStack_10 = *(undefined *)(dword_df6ee + 0x24 + (int)(short)(word_df64c & 1));
    uStack_f = *(undefined *)((short)(word_df74c & 1) + 0x24 + dword_df7ee);
  }
  else {
    if (iVar4 == 0) {
      iVar4 = sub_147ff(local_44[2],local_53 + 3);
    }
    if (iVar4 == 0) {
      iVar5 = 0;
      uStack_10 = 0xff;
      uStack_f = 0xff;
      local_28 = iStack_4d >> 0x10;
      local_24 = 0;
      local_14 = (undefined  [4])0x0;
      while ((local_24 <= local_28 && (iVar4 == 0))) {
        iVar4 = sub_147ff(local_44[2],local_53 + 3,local_24);
        if ((iVar4 == 0) && (local_53[3] == '\x01')) {
          if (cStack_4f == '\0') {
            iVar5 = iVar5 + 1;
          }
          else {
            local_14 = (undefined  [4])((int)local_14 + 1);
          }
          if (local_1c == 0) {
            if (iVar5 == local_18) {
              uStack_10 = uStack_47;
              uStack_f = uStack_46;
            }
          }
          else if (local_14 == (undefined  [4])local_18) {
            uStack_10 = uStack_46;
            uStack_f = uStack_47;
          }
        }
        local_24 = local_24 + 1;
      }
    }
  }
  _memset_fill(acStack_6c,0x1010101,iVar4,0x19);
  local_24 = 0;
  do {
    if ((byte)local_44[unaff_ECX][local_24 + 0x28] < 0x19) {
      acStack_6c[(byte)local_44[unaff_ECX][local_24 + 0x28]] = '\0';
    }
    local_24 = local_24 + 1;
  } while (local_24 < 8);
  local_24 = 0;
  while ((local_24 < 0x19 && (iVar4 == 0))) {
    if (aiStack_3c4[local_24] != -1) {
      iVar4 = sub_1463d(local_44[4],auStack_f0,aiStack_3c4[local_24]);
      if (iVar4 == 0) {
        iVar4 = sub_1478b(local_44[3],local_bc,uStack_c4);
      }
      if ((iVar4 == 0) && (acStack_6c[local_24] != '\0')) {
        *psVar7 = *psVar7 + 1;
        iVar4 = unaff_ECX * 400 + local_24 * 0x10;
        psVar7[1] = psVar7[1] + *(short *)(&word_db088 + local_24 * 4 + unaff_ECX * 100);
        psVar7[2] = psVar7[2] + *(short *)((int)&word_db088 + iVar4 + 2);
        sVar1 = *(short *)(&word_db088 + local_24 * 4 + unaff_ECX * 100);
        sVar2 = psVar7[3];
        psVar7[3] = sVar2 + sVar1;
        psVar7[3] = sVar2 + sVar1 + *(short *)((int)&word_db088 + iVar4 + 2);
        psVar7[6] = psVar7[6] + *(short *)(&word_db08c + local_24 * 4 + unaff_ECX * 100);
        psVar7[8] = psVar7[8] + *(short *)((int)&word_db08c + iVar4 + 2);
        psVar7[4] = psVar7[4] + *(short *)(&word_db090 + local_24 * 4 + unaff_ECX * 100);
        psVar7[5] = psVar7[5] + *(short *)((int)&word_db090 + iVar4 + 2);
        psVar7[7] = psVar7[7] + *(short *)((int)&word_db094 + iVar4 + 2);
        iVar4 = sub_3a24f(local_44[3],local_bc,uStack_c4);
      }
    }
    local_24 = local_24 + 1;
  }
  local_24 = 0;
  do {
    local_53[local_24] = '\0';
    local_24 = local_24 + 1;
  } while (local_24 < 3);
  local_24 = 0;
  do {
    if ((byte)local_44[unaff_ECX][local_24 + 0x24] < 0x1c) {
      acStack_6c[(byte)local_44[unaff_ECX][local_24 + 0x24]] =
           acStack_6c[(byte)local_44[unaff_ECX][local_24 + 0x24]] + '\x01';
    }
    local_24 = local_24 + 1;
  } while (local_24 < 2);
  local_24 = 0;
  do {
    if ((2 < local_24) || (iVar4 != 0)) {
      if (iVar4 == 0) {
        iVar4 = sub_3a2b8(local_44[5],auStack_410,unaff_EBX);
      }
      file_close(local_44 + 2);
      file_close(local_44 + 3);
      file_close(local_44 + 4);
      file_close(local_44 + 5);
      return iVar4;
    }
    if (aiStack_360[local_24] != -1) {
      iVar4 = sub_1463d(local_44[4],auStack_f0,aiStack_360[local_24]);
      if (iVar4 == 0) {
        iVar4 = sub_3a266(local_44[3],local_128,uStack_c4);
      }
      if (((iVar4 == 0) && (local_53[local_24] != '\0')) &&
         (iVar5 = local_24 * 6 + unaff_ECX * 0x12, *(short *)((int)&word_dc240 + iVar5) != 0)) {
        *puVar6 = *puVar6 + 1;
        puVar6[6] = puVar6[6] + (short)((*(int *)(&unk_dc23e + iVar5) >> 0x10) / 0x3c);
        puVar6[9] = puVar6[9] + *(short *)((int)&word_dc240 + iVar5 + 2);
        puVar6[7] = puVar6[7] + (&word_dc244)[unaff_ECX * 9 + local_24 * 3];
        if (*(int *)(local_14 + unaff_ECX + 1) >> 0x18 == (uint)(byte)((char)local_24 + 0x19)) {
          if (dword_df722._2_2_ < dword_df622._2_2_) {
            if (unaff_ECX == 0) {
LAB_00036a52:
              puVar6[1] = puVar6[1] + 1;
            }
            else {
LAB_00036a58:
              puVar6[2] = puVar6[2] + 1;
            }
          }
          else {
            if (dword_df622._2_2_ < dword_df722._2_2_) {
              if (unaff_ECX == 0) goto LAB_00036a58;
              goto LAB_00036a52;
            }
            puVar6[3] = puVar6[3] + 1;
          }
          if (((dword_df722._2_2_ == 0) && (unaff_ECX == 0)) ||
             ((dword_df622._2_2_ == 0 && (unaff_ECX == 1)))) {
            puVar6[4] = puVar6[4] + 1;
          }
        }
        if (*puVar6 == 0) {
          puVar6[8] = 0;
        }
        else {
          puVar6[8] = (ushort)(((uint)puVar6[7] * 100) / (uint)*puVar6);
        }
        if (puVar6[9] == 0) {
          puVar6[10] = 0;
        }
        else {
          uVar8 = (uint)puVar6[9];
          puVar6[10] = (ushort)((int)((uVar8 - puVar6[7]) * 1000 + uVar8 / 2) / (int)uVar8);
        }
        iVar4 = sub_3a27d(local_44[3],local_128,uStack_c4);
      }
    }
    local_24 = local_24 + 1;
  } while( true );
}


// ================================================================================================
// league_calendar_flow @ 0x36b93 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall league_calendar_flow(int *param_1)

{
  undefined2 uVar1;
  int iVar2;
  size_t sVar3;
  int iVar4;
  undefined4 uVar5;
  short sVar6;
  char *pcVar7;
  undefined4 *puVar8;
  undefined **ppuVar9;
  uint unaff_EBP;
  undefined2 in_DS;
  bool bVar10;
  undefined *puVar11;
  undefined local_ac [32];
  char local_8c [16];
  undefined local_7c [16];
  undefined4 local_6c;
  undefined auStack_68 [4];
  int local_64;
  undefined local_60 [4];
  undefined auStack_5c [4];
  int local_58;
  undefined4 local_54;
  undefined4 local_50;
  char local_4c [4];
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  int iStack_3c;
  undefined4 local_38;
  int iStack_34;
  int iStack_30;
  undefined4 local_2c;
  int iStack_28;
  int iStack_24;
  undefined4 local_20;
  int iStack_1c;
  
  __CHK(0xc4);
  local_40 = 0xffffffff;
  local_50 = 0xffffffff;
  local_54 = 0xffffffff;
  local_6c = 0xffffffff;
  local_48 = 0xffffffff;
  iStack_3c = 0;
  iStack_34 = 0;
  iStack_28 = 0;
  dword_ddd44 = CONCAT22(0xffff,(undefined2)dword_ddd44);
  setmouselimits(0,0,0x280,0x1e0);
  if (-1 < *param_1) {
    sub_41b80(*param_1);
  }
  iVar2 = sub_41337(&league_dir,3);
  do {
    iStack_1c = 0;
    if (iVar2 == 0) {
      iVar2 = load_league_info(&league_dir,&unk_dd7b4,&unk_ddd1d,&dword_dd7a8,&dword_ddac0,
                               &dword_dd7b0,&dword_dd7ac,&byte_ddd10);
    }
    if (iVar2 == 0) {
      strcpy(local_8c,&league_dir);
      sVar3 = strcspn(local_8c,(char *)CONCAT22(0xc,in_DS));
      local_8c[sVar3] = '\0';
      if (((byte)dword_dd7b0 & 0xc) == 0) {
        make_path(local_ac,&league_dir,off_c80e7,&aDB);
        iVar2 = db_open_check(local_ac,&unk_ddac4,1);
      }
      else {
        getmouse(&local_58,auStack_5c,local_60);
        set_dialog_colors(0xf9,0xfa,0xf8,0xfa,0);
        if (((byte)dword_dd7b0 & 8) == 0) {
          dword_c7e42 = local_8c;
          puVar11 = &unk_c7e4e;
          uVar5 = 4;
          ppuVar9 = &off_c7e3e;
        }
        else {
          dword_c7f0b = local_8c;
          puVar11 = &unk_c7f1b;
          uVar5 = 5;
          ppuVar9 = &off_c7f07;
        }
        local_58 = message_dialog(0xffffffff,0xffffffff,ppuVar9,uVar5,puVar11,2,auStack_5c,local_60,
                                  0xffffffff);
        if (local_58 == 0) {
          if (((byte)dword_dd7b0 & 8) != 0) {
            league_merge_check();
          }
          league_merge_warning();
          iStack_1c = -1;
        }
        else {
          iVar2 = -1;
        }
      }
    }
  } while (iStack_1c != 0);
  if (*param_1 < 0) {
    iStack_24 = iStack_1c;
    if (iVar2 == 0) {
      set_dialog_colors(0xf9,0xfa,0xf8,0xfa,0);
      dword_ddd38 = sub_41344(&league_dir,auStack_68);
      if ((int)dword_ddd38 < 0) {
        team_info_screen(&league_dir,&dword_ddac0,&unk_ddac4,&unk_dd7b4,8,aSelectATeamToPlay,
                         &dword_ddd38);
        iStack_24 = -1;
      }
    }
    if ((iVar2 == 0) && (-1 < (int)dword_ddd38)) {
      iVar2 = league_import_export_check(&league_dir,&unk_dd7b4,dword_ddd38,0,0);
      if (iVar2 == 0) {
        sprintf(local_4c,a02d,dword_ddd38);
        strcpy((char *)&aXx,local_4c);
        if (((&unk_dd7ca)[dword_ddd38 * 0x1e] & 1) == 0) {
          pcVar7 = &byte_c816a;
        }
        else {
          pcVar7 = &league_dir;
        }
        strcpy(&unk_ddd4c,pcVar7);
        if ((dword_ddac0 == 1) || (iStack_24 == 0)) {
          set_dialog_colors(0xf9,0xfa,0xf8,0xfa,0);
        }
        iVar2 = password_prompt(dword_ddd38,&unk_dd7b4);
      }
      if (iVar2 == 0) {
        make_path(local_ac,&league_dir,off_c80e7,&aDB);
        iVar2 = db_open_check(local_ac,&unk_ddac4,0);
      }
      if (iVar2 == 0) {
        iStack_28 = -1;
      }
    }
    local_2c = allocmem(&aPal_c1862,0x300,0x20);
    if ((sound_enabled != '\0') && (dword_c721d != 0)) {
      sound_fade(dword_d2431,3,100);
    }
    getpalette(0,0x100,local_2c);
    fade_palette(1,local_2c,0x10);
    freemem(local_2c);
    if ((sound_enabled != '\0') && (dword_c721d != 0)) {
      do {
        iVar4 = sound_channel_status(ram0x000d242c >> 0x18,3);
      } while (iVar4 == 0);
      releasememblock(dword_c721d);
      dword_c721d = 0;
    }
  }
  else {
    set_dialog_colors(0xf9,0xfa,0xf8,0xfa,0);
    sprintf(local_4c,a02d,dword_ddd38);
    strcpy((char *)&aXx,local_4c);
    iVar2 = password_prompt(dword_ddd38,&unk_dd7b4);
    if (iVar2 == 0) {
      iStack_28 = -1;
    }
  }
  if (iStack_28 != 0) {
    do {
      if (((dword_ddd44 >> 0x10 == -1) && (*param_1 < 0)) || (iStack_3c != 0)) {
        uVar1 = calendar_screen(&unk_ddd4c,&aXx,dword_ddd38);
        dword_ddd44 = CONCAT22(uVar1,(undefined2)dword_ddd44);
      }
      if (-1 < dword_ddd44) {
        make_path(local_ac,&unk_ddd4c);
        iVar2 = file_open_rw(local_ac,&local_40);
        if (*param_1 < 0) {
          if (iVar2 == 0) {
            iVar2 = file_read(local_40,&word_ddd48);
          }
          if (iVar2 == 0) {
            iVar2 = db_read_record2(local_40,&byte_ddd40);
          }
          if (iVar2 == 0) {
            dword_ddd34 = (uint)byte_ddd42;
            if (dword_ddd34 == dword_ddd38) {
              dword_ddd34 = CONCAT31((int3)(dword_ddd38 >> 8),byte_ddd43);
            }
            dword_ddd3c = -1;
            if ((&unk_dd7cb)[dword_ddd34 * 0x1e] == '\0') {
              dword_ddd3c = 0;
            }
          }
        }
        file_close(&local_40);
        if (dword_ddd3c != 0) {
          if ((iVar2 == 0) &&
             (iVar2 = league_import_export_check(&league_dir,&unk_dd7b4,dword_ddd34,0xffffffff,0),
             iVar2 == 0)) {
            sprintf(local_4c,a02d,dword_ddd34);
            strcpy((char *)&aXx_c8158,local_4c);
            if ((((&unk_dd7ca)[dword_ddd34 * 0x1e] & 1) == 0) || (iStack_24 == 0)) {
              pcVar7 = &byte_c816a;
            }
            else {
              pcVar7 = &league_dir;
            }
            strcpy(&unk_ddd59,pcVar7);
          }
          if (iVar2 == 0) {
            make_path(local_ac,&unk_ddd59,off_c80ef,&aXx_c8158);
            iVar2 = file_open_rw(local_ac,&local_50);
          }
          if ((*param_1 < 0) && (iVar2 == 0)) {
            iVar2 = file_read(local_50,&word_ddd4a,0,2);
          }
          file_close(&local_50);
          if (iVar2 == 0) {
            sprintf(local_4c,a02d,dword_ddd34);
            strcpy((char *)&aXx_c8158,local_4c);
            iVar2 = password_prompt(dword_ddd34,&unk_dd7b4);
            if (iVar2 != 0) {
              iStack_34 = -1;
            }
          }
        }
        if (iVar2 == 0) {
          if (-1 < *param_1) {
            uVar5 = allocmem(&aTemp_c1866,0x300,0x20);
            getpalette(0,0x100,uVar5);
            fade_palette(1,uVar5);
            freemem(uVar5);
          }
          if ((sound_enabled != '\0') && (dword_c721d != 0)) {
            sound_fade(dword_d2431,3);
            do {
              iVar2 = sound_channel_status(ram0x000d242c >> 0x18,3);
            } while (iVar2 == 0);
            releasememblock(dword_c721d);
            dword_c721d = 0;
          }
          if (-1 < *param_1) {
            sub_479e9();
          }
          bVar10 = byte_ddd42 != dword_ddd38;
          if (bVar10) {
            local_38 = 1;
            sub_36207(&byte_dd750,&unk_ddd59,&unk_dd7b4);
            puVar11 = &unk_ddd4c;
          }
          else {
            local_38 = 0;
            sub_36207(&byte_dd750,&unk_ddd4c,&unk_dd7b4);
            puVar11 = &unk_ddd59;
          }
          unaff_EBP = (uint)!bVar10;
          sub_36207(&byte_dd710,puVar11,&unk_dd7b4,byte_ddd43);
          if (byte_dd710 == '\0') {
            strcpy(&byte_dd710,&byte_dd750);
          }
          if (byte_dd750 == '\0') {
            strcpy(&byte_dd750,&byte_dd710);
          }
          dword_dc234 = dword_ddd44 >> 0x10;
          if (dword_ddd44._2_2_ < 0x444) {
            option_flags._1_1_ = option_flags._1_1_ | 2;
          }
          else {
            option_flags._1_1_ = option_flags._1_1_ & 0xfd;
          }
          if (*param_1 < 0) {
            byte_dc268 = byte_ddd40;
            byte_dc267 = byte_ddd41;
            user2_team._2_2_ = (ushort)byte_ddd42;
            _away_team_id = (ushort)byte_ddd43;
          }
          sub_10712();
          iVar2 = 0;
          if (*param_1 < 0) {
            iVar2 = check_disk_space_for_game();
            if (iVar2 == 0) {
              sub_1befd(byte_dc268,byte_dc267);
              iVar2 = team_select_screen(user2_team._2_1_,away_team_id);
            }
            else {
              iVar2 = 4;
            }
          }
          if (iVar2 == 4) {
            dword_c53f7 = 2;
          }
          else {
            dword_c65c0 = exh_hub_sports_central;
            dword_c65c4 = exh_hub_playoff_tree;
            dword_c65c8 = exh_hub_league_calendar;
            dword_c65cc = exh_hub_standings;
            dword_c65d0 = exh_hub_stats;
            ui_shutdown();
            play_game(param_1);
            ui_init();
            if (dword_c53f7 == 1) {
              dword_ddd44._0_2_ = CONCAT11(dword_df722._2_1_,dword_df622._2_1_);
            }
          }
        }
        if ((iVar2 == 0) && (dword_c53f7 == 1)) {
          iStack_30 = dword_ddd44 >> 0x10;
          clearclip(0);
          puVar11 = install_path;
          if (byte_ed836 != '\x01') {
            puVar11 = (undefined *)0x0;
          }
          make_path(local_ac,puVar11,aEasndesk_c186b,0);
          local_44 = loadshapes(local_ac,0);
          iVar4 = locateshape(local_44,&aPal_c1827);
          setpalette(0,0x100,iVar4 + 0x10);
          freemem(local_44);
          local_4c[0] = '\x17';
          local_4c[1] = 0x17;
          local_4c[2] = 0x17;
          setpalette(0xf8,1,local_4c);
          local_4c[0] = '*';
          local_4c[1] = 0x2a;
          local_4c[2] = 0x2a;
          setpalette(0xf9,1,local_4c);
          local_4c[0] = '?';
          local_4c[1] = 0x3f;
          local_4c[2] = 0x3f;
          setpalette(0xfa,1,local_4c);
          set_dialog_colors(0xf9,0xfa,0xf8,0xfa,0);
          if ((dword_ddd3c != 0) &&
             (iVar2 = league_import_export_check
                                (&league_dir,&unk_dd7b4,dword_ddd34,0xffffffff,0xffffffff),
             iVar2 == 0)) {
            sprintf(local_4c,a02d,dword_ddd34);
            strcpy((char *)&aXx_c8158,local_4c);
            if ((((&unk_dd7ca)[dword_ddd34 * 0x1e] & 1) == 0) || (iStack_24 == 0)) {
              pcVar7 = &byte_c816a;
            }
            else {
              pcVar7 = &league_dir;
            }
            strcpy(&unk_ddd59,pcVar7);
          }
          if (iVar2 == 0) {
            make_path(local_ac,&unk_ddd4c,off_c80ef,&aXx);
            iVar2 = file_open_rw(local_ac,&local_40);
            if ((dword_ddd3c != 0) && (iVar2 == 0)) {
              make_path(local_ac,&unk_ddd59,off_c80ef,&aXx_c8158);
              iVar2 = file_open_rw(local_ac,&local_50);
            }
          }
          if (iVar2 == 0) {
            message_dialog(0xffffffff,0xffffffff,&off_c7f8e,1,0,0,0,0,0);
            local_7c[0] = 0;
            local_64 = iVar2;
            make_path(local_ac,&unk_ddd4c,aPINFO,&aDB);
            iVar2 = sub_1453e(local_ac,&local_48);
          }
          if (iVar2 == 0) {
            iVar2 = file_write(local_48,&local_64,4,2);
          }
          if (iVar2 == 0) {
            iVar2 = file_write(local_48,local_7c,6,0xd);
          }
          file_close(&local_48);
          if (dword_ddd3c != 0) {
            if (iVar2 == 0) {
              make_path(local_ac,&unk_ddd59,aPINFO,&aDB);
              iVar2 = sub_1453e(local_ac,&local_48);
            }
            if (iVar2 == 0) {
              iVar2 = file_write(local_48,&local_64,4,2);
            }
            if (iVar2 == 0) {
              iVar2 = file_write(local_48,local_7c,6,0xd);
            }
            file_close(&local_48);
          }
          if (iVar2 == 0) {
            iVar2 = sub_3a28f(local_40,&byte_ddd40);
          }
          if ((iVar2 == 0) && (dword_ddd3c != 0)) {
            iVar2 = sub_3a28f(local_50,&byte_ddd40);
          }
          if (iVar2 == 0) {
            if (dword_ddd44._2_2_ < 0x444) {
              sVar6 = dword_ddd44._2_2_ + 1;
              dword_ddd44 = CONCAT22(sVar6,(undefined2)dword_ddd44);
              if (word_ddd48 < sVar6) {
                iVar2 = file_write(local_40,0xddd46,0,2);
              }
              if (((iVar2 == 0) && (dword_ddd3c != 0)) && (word_ddd4a < dword_ddd44._2_2_)) {
                iVar2 = file_write(local_50,0xddd46,0,2);
              }
            }
            else {
              make_path(local_ac,&unk_ddd4c,off_c80e7,&aXx);
              iVar2 = file_open_rw(local_ac,&local_54);
              if (iVar2 == 0) {
                iVar2 = sub_41f64(local_40,local_54,dword_ddd44 >> 0x10);
              }
              file_close(&local_54);
              if ((iVar2 == 0) && (dword_ddd3c != 0)) {
                make_path(local_ac,&unk_ddd59,off_c80e7,&aXx_c8158);
                iVar2 = file_open_rw(local_ac,&local_6c);
                if (iVar2 == 0) {
                  iVar2 = sub_41f64(local_50,local_6c,dword_ddd44 >> 0x10);
                }
                file_close(&local_6c);
              }
            }
          }
          if (iVar2 == 0) {
            iVar2 = sub_41cc4(&unk_ddd4c,&aXx,(dword_ddd44 >> 0x10) + -1,&unk_dd7b4,dword_ddd38,2);
            if (iVar2 == 0) {
              iVar2 = season_record_result
                                (&unk_ddd4c,&aXx,dword_ddd38,local_38,iStack_30,&unk_ddd4c);
            }
            if (iVar2 == 0) {
              if (dword_ddd3c == 0) {
                puVar8 = &aXx;
                puVar11 = &unk_ddd4c;
              }
              else {
                iVar2 = sub_41cc4(&unk_ddd59,&aXx_c8158,dword_ddd44 >> 0x10,&unk_dd7b4,dword_ddd34,2
                                 );
                if (iVar2 != 0) goto LAB_000379f4;
                puVar8 = &aXx_c8158;
                puVar11 = &unk_ddd59;
              }
              iVar2 = season_record_result
                                (puVar11,puVar8,dword_ddd34,unaff_EBP,iStack_30,&unk_ddd4c);
            }
          }
LAB_000379f4:
          sub_30f12();
          clearclip(0);
        }
        if (((iVar2 != 0) && (iStack_34 == 0)) && (iVar2 != 4)) {
          getmouse(&local_58,auStack_5c,local_60);
          message_dialog(0xffffffff,0xffffffff,&off_c7805,1,0,0,auStack_5c,local_60,0xffffffff);
        }
        if (dword_ddd3c != 0) {
          file_close(&local_50);
        }
        file_close(&local_40);
      }
      local_20 = allocmem(&aTemp_c1866,0x300,0x20);
      if ((sound_enabled != '\0') && (dword_c721d != 0)) {
        sound_fade(dword_d2431,3,100);
      }
      getpalette(0,0x100,local_20);
      fade_palette(1,local_20,0x10);
      freemem(local_20);
      if ((sound_enabled != '\0') && (dword_c721d != 0)) {
        do {
          iVar4 = sound_channel_status(ram0x000d242c >> 0x18,3);
        } while (iVar4 == 0);
        releasememblock(dword_c721d);
        dword_c721d = 0;
      }
      ui_init();
      iStack_3c = -1;
      if (iVar2 == 4) {
        iVar2 = 0;
      }
      make_path(local_ac,&league_dir,&aGAME,&aSAV);
    } while (((-1 < dword_ddd44) && (iVar2 == 0)) && (iVar4 = sub_142e7(local_ac), iVar4 == 0));
  }
  setmouselimits(0,0,0x280,0x1e0);
  return;
}


// ================================================================================================
// sub_37b92 @ 0x37b92 [__watcall]
// ================================================================================================

uint __watcall sub_37b92(int param_1,int unaff_EDX,int unaff_EBX)

{
  byte *pbVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint local_1c;
  
  __CHK(0x24);
  local_1c = 0xffffffff;
  iVar2 = 0;
  do {
    iVar3 = 0;
    do {
      pbVar1 = (byte *)(iVar3 + iVar2 * 7 + unaff_EBX);
      if (iVar2 < 2) {
        iVar4 = iVar3 * 0x55 + 0x40;
      }
      else {
        iVar4 = iVar3 * 0x55 + 0x16;
      }
      if ((((iVar4 <= param_1) && (param_1 <= iVar4 + 0x46)) && (iVar2 * 0x5c + 0x58 <= unaff_EDX))
         && (unaff_EDX <= iVar2 * 0x5c + 0x91)) {
        iVar2 = 4;
        iVar3 = 6;
        local_1c = (uint)*pbVar1;
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < 7);
    iVar2 = iVar2 + 1;
  } while (iVar2 < 4);
  if (local_1c == 99) {
    local_1c = 0xffffffff;
  }
  return local_1c;
}


// ================================================================================================
// sub_37c53 @ 0x37c53 [__watcall]
// ================================================================================================

void __watcall sub_37c53(uint param_1,int unaff_EDX,undefined4 unaff_EBX,int unaff_ECX)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 uStack_10;
  
  __CHK(0x38);
  set_text_colors(dword_c71d8,dword_c71dc);
  uStack_10 = 0;
  do {
    iVar5 = 0;
    do {
      if (*(byte *)(iVar5 + uStack_10 * 7 + unaff_ECX) == param_1) {
        if (uStack_10 < 2) {
          iVar4 = iVar5 * 0x55 + 0x39;
        }
        else {
          iVar4 = iVar5 * 0x55 + 0xf;
        }
        iVar1 = uStack_10 * 0x5c + 0x97;
        setclip(iVar4,iVar4 + 0x4d,iVar1,(uint)byte_d42c3 + iVar1 + 1);
        drawshape_remap(unaff_EBX,0,0);
        setclip(0,0x280,0,0x1e0);
        iVar3 = unaff_EDX + param_1 * 0x1e;
        iVar2 = textwidth(iVar3);
        print_text_at((iVar4 + 0x2a) - (iVar2 >> 1),iVar1,iVar3);
      }
      iVar5 = iVar5 + 1;
    } while (iVar5 < 7);
    uStack_10 = uStack_10 + 1;
  } while (uStack_10 < 4);
  return;
}


// ================================================================================================
// sub_37d6a @ 0x37d6a [__watcall]
// ================================================================================================

void __watcall
sub_37d6a(uint param_1,int unaff_EDX,undefined4 unaff_EBX,int unaff_ECX,undefined4 param_5)

{
  int iVar1;
  int iVar2;
  
  __CHK(0x28);
  dword_c8998 = (void *)allocmem(&aBack,0x4688,0x20,unaff_EBX);
  memset(dword_c8998,0,0x11);
  *(undefined2 *)((int)dword_c8998 + 4) = 0x4e;
  *(undefined2 *)((int)dword_c8998 + 6) = 0x41;
  iVar2 = 0;
  do {
    iVar1 = 0;
    do {
      if (*(byte *)(iVar1 + iVar2 * 7 + unaff_EDX) == param_1) {
        if (iVar2 < 2) {
          dword_ddd6c = iVar1 * 0x55 + 0x3c;
        }
        else {
          dword_ddd6c = iVar1 * 0x55 + 0x12;
        }
        dword_ddd68 = iVar2 * 0x5c + 0x54;
        drawshape(unaff_EBX,unaff_ECX + -4,param_5);
        grabshape(dword_c8998,dword_ddd6c,dword_ddd68);
      }
      iVar1 = iVar1 + 1;
    } while (iVar1 < 7);
    iVar2 = iVar2 + 1;
  } while (iVar2 < 4);
  return;
}


// ================================================================================================
// sub_37e5b @ 0x37e5b [__watcall]
// ================================================================================================

void __watcall sub_37e5b(void)

{
  __CHK(0x20);
  if (dword_c8998 != 0) {
    drawshape(dword_c8998,dword_ddd6c,dword_ddd68);
    freemem(dword_c8998);
    dword_c8998 = 0;
  }
  return;
}


// ================================================================================================
// sub_37ea6 @ 0x37ea6 [__watcall]
// ================================================================================================

void __watcall sub_37ea6(uint param_1,int unaff_EDX,int unaff_EBX)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  __CHK(0x48);
  iVar4 = 0;
  do {
    iVar3 = 0;
    do {
      if (*(byte *)(iVar3 + iVar4 * 7 + unaff_EDX) == param_1) {
        if (iVar4 < 2) {
          iVar2 = iVar3 * 0x55 + 0x3e;
        }
        else {
          iVar2 = iVar3 * 0x55 + 0x14;
        }
        iVar1 = iVar4 * 0x5c;
        if (unaff_EBX == 0) {
          sub_93000(iVar2,iVar1 + 0x56,iVar2 + 0x4a,iVar1 + 0x93,0);
          sub_93000(iVar2 + -1,iVar1 + 0x55,iVar2 + 0x4b,iVar1 + 0x94,0);
        }
        else {
          sub_92f50(iVar2,iVar1 + 0x56,iVar2 + 0x4a,iVar1 + 0x93,0x80);
          sub_92f50(iVar2 + -1,iVar1 + 0x55,iVar2 + 0x4b,iVar1 + 0x94,0x80);
        }
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < 7);
    iVar4 = iVar4 + 1;
  } while (iVar4 < 4);
  return;
}


// ================================================================================================
// sub_37fba @ 0x37fba [__watcall]
// ================================================================================================

void __watcall sub_37fba(int param_1,char *unaff_EDX,int unaff_EBX,undefined4 unaff_ECX)

{
  undefined4 uVar1;
  undefined *puVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  undefined4 auStack_cc [26];
  char acStack_64 [84];
  undefined4 uStack_10;
  
  __CHK(0xe8);
  strcpy(acStack_64,unaff_EDX);
  sub_17573(0x28,acStack_64);
  puVar2 = install_path;
  if (byte_ed98e != '\x01') {
    puVar2 = (undefined *)0x0;
  }
  make_path(acStack_64,puVar2,aCallogo_c1885,0);
  uStack_10 = loadshapes(acStack_64,0);
  iVar4 = 0;
  do {
    uVar1 = locateshape(uStack_10,(&off_c57cc)[iVar4]);
    auStack_cc[iVar4] = uVar1;
    iVar4 = iVar4 + 1;
  } while (iVar4 < 0x1a);
  iVar4 = 0;
  do {
    iVar6 = 0;
    do {
      uVar5 = (uint)*(byte *)(iVar6 + unaff_EBX + iVar4 * 7);
      if (uVar5 == 99) break;
      if (iVar4 < 2) {
        iVar3 = iVar6 * 0x55 + 0x40;
      }
      else {
        iVar3 = iVar6 * 0x55 + 0x16;
      }
      drawshape_remap(auStack_cc[uVar5],iVar3,iVar4 * 0x5c + 0x58);
      if (*(char *)(uVar5 * 0x1e + param_1 + 0x17) == '\x01') {
        sub_37c53(uVar5,param_1,unaff_ECX,unaff_EBX);
      }
      iVar6 = iVar6 + 1;
    } while (iVar6 < 7);
    iVar4 = iVar4 + 1;
    if (3 < iVar4) {
      freemem(uStack_10);
      return;
    }
  } while( true );
}


// ================================================================================================
// league_control_dialog @ 0x380e9 [__watcall]
// ================================================================================================

void __watcall
league_control_dialog(int param_1,int unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  void *__s;
  void *__s_00;
  int iVar1;
  size_t sVar2;
  int iVar3;
  char *pcVar4;
  int aiStack_f8 [26];
  char acStack_90 [84];
  char acStack_3c [12];
  char acStack_30 [12];
  int iStack_10;
  
  __CHK(0x110);
  sVar2 = unaff_EDX << 2;
  __s = (void *)allocmem(&aPLST,sVar2,0x20);
  memset(__s,0,sVar2);
  sVar2 = unaff_EDX * 0xb;
  __s_00 = (void *)allocmem(&aPTLS,sVar2,0x20);
  memset(__s_00,0,sVar2);
  iVar3 = 0;
  iVar1 = 0;
  do {
    pcVar4 = (char *)(iVar1 * 0x1e + param_1);
    if (pcVar4[0x17] == '\x01') {
      strcpy(acStack_90,pcVar4);
      pcVar4 = (char *)((int)__s_00 + iVar3 * 0xb);
      strcpy(pcVar4,acStack_90);
      aiStack_f8[iVar3] = iVar1;
      *(char **)(iVar3 * 4 + (int)__s) = pcVar4;
      iVar3 = iVar3 + 1;
    }
    iVar1 = iVar1 + 1;
  } while (iVar1 < 0x1a);
  if (unaff_EDX < 2) {
    iVar1 = 0;
    iVar3 = 0;
    do {
      if (*(char *)(param_1 + 0x17 + iVar3 * 0x1e) == '\x01') {
        aiStack_f8[0] = iVar3;
        iVar3 = 0x1a;
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < 0x1a);
  }
  else {
    iVar1 = sub_303fb(__s,unaff_EDX,aWhoWillControlTheLeague,0,0,0);
  }
  *(undefined *)(param_1 + 0x18 + aiStack_f8[iVar1] * 0x1e) = 1;
  *(undefined *)(param_1 + 0x19 + aiStack_f8[iVar1] * 0x1e) = 1;
  dword_dd7a8 = aiStack_f8[iVar1];
  do {
    iStack_10 = 0;
    strcpy(acStack_90,aEnterMasterControllerPas);
    strcat(acStack_90,(char *)(aiStack_f8[iVar1] * 0x1e + param_1));
    sub_2fedf(acStack_90,acStack_3c,10,0x3c,0,0,0,0,2);
    strcpy(acStack_90,aVerifyMasterControllerPa);
    strcat(acStack_90,(char *)(aiStack_f8[iVar1] * 0x1e + param_1));
    sub_2fedf(acStack_90,acStack_30,10,0x3c,0,0,0,0,2);
    iVar3 = strcmp(acStack_3c,acStack_30);
    if (iVar3 != 0) {
      message_dialog(0xffffffff,0xffffffff,&off_c8055,2,0,0,unaff_EBX,unaff_ECX,0xffffffff);
      iStack_10 = -1;
    }
  } while (iStack_10 != 0);
  strcpy(&unk_ddd1d,acStack_3c);
  sub_3a597(&unk_ddd1d,aiStack_f8[iVar1]);
  dword_dd7b0 = iStack_10;
  dword_dd7ac = iStack_10;
  byte_ddd10 = 0;
  freemem(__s);
  freemem(__s_00);
  return;
}


// ================================================================================================
// sub_38386 @ 0x38386 [__watcall]
// ================================================================================================

void __watcall sub_38386(int param_1,int unaff_EDX,uint unaff_EBX,int unaff_ECX)

{
  int iVar1;
  int iVar2;
  undefined local_1c [4];
  undefined local_18 [4];
  int local_14;
  
  __CHK(0x34);
  getmouse(&local_14,local_18,local_1c);
  local_14 = 0;
  do {
    if (((((unaff_EBX & 1) == 0) ||
         (iVar1 = local_14 * 0x1e + param_1, *(char *)(iVar1 + 0x17) != '\x01')) ||
        (*(char *)(iVar1 + 0x18) != '\x02')) &&
       ((((unaff_EBX & 2) == 0 || (*(char *)(local_14 * 0x1e + 0x17 + param_1) != '\x01')) ||
        (*(char *)(local_14 * 0x1e + 0x17 + unaff_EDX) != '\0')))) {
      iVar1 = local_14 * 0x1e + param_1;
      if (*(char *)(iVar1 + 0x17) == '\0') goto LAB_0003848b;
    }
    else {
      iVar1 = local_14 * 0x1e + param_1;
      if (1 < unaff_ECX) {
        dword_c7a34 = iVar1;
        iVar2 = message_dialog(0xffffffff,0xffffffff,&off_c7a30,3,&unk_c7a3c,2,local_18,local_1c,
                               0xffffffff);
        iVar1 = local_14 * 0x1e + param_1;
        if (iVar2 != 1) {
          *(undefined *)(iVar1 + 0x18) = 2;
          *(undefined *)(param_1 + 0x16 + local_14 * 0x1e) = 2;
          goto LAB_0003849f;
        }
      }
LAB_0003848b:
      *(undefined *)(iVar1 + 0x18) = 1;
      *(undefined *)(param_1 + 0x16 + local_14 * 0x1e) = 1;
    }
LAB_0003849f:
    local_14 = local_14 + 1;
    if (0x19 < local_14) {
      return;
    }
  } while( true );
}


// ================================================================================================
// sub_384b8 @ 0x384b8 [__watcall]
// ================================================================================================

undefined4 __watcall sub_384b8(undefined4 param_1,int unaff_EDX)

{
  int iVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined auStackY_7a4 [40];
  byte local_77c;
  byte bStackY_77b;
  byte local_77a;
  byte bStackY_779;
  ushort uStackY_778;
  ushort uStackY_776;
  uint auStackY_4bc [28];
  uint auStackY_44c [28];
  uint auStackY_3dc [28];
  uint auStackY_36c [28];
  uint auStackY_2fc [28];
  uint auStackY_28c [26];
  uint auStackY_224 [26];
  uint auStackY_1bc [26];
  uint auStackY_154 [26];
  uint auStackY_ec [26];
  uint auStackY_84 [26];
  uint local_1c;
  undefined4 uStackY_18;
  
  __CHK(0x7a8);
  iVar5 = 0;
  do {
    uStackY_18 = db_read_record(param_1,auStackY_7a4,iVar5);
    auStackY_84[iVar5] = (uint)local_77c;
    auStackY_28c[iVar5] = (uint)bStackY_77b;
    auStackY_1bc[iVar5] = (uint)local_77a;
    auStackY_224[iVar5] = (uint)bStackY_779;
    auStackY_154[iVar5] = (uint)uStackY_778;
    auStackY_ec[iVar5] = (uint)uStackY_776;
    iVar5 = iVar5 + 1;
  } while (iVar5 < 0x1a);
  iVar5 = 0;
  do {
    iVar3 = 0;
    do {
      iVar4 = iVar5 * 7;
      bVar2 = (&unk_c83c3)[iVar4 + iVar3];
      local_1c = auStackY_224[bVar2] + auStackY_28c[bVar2] * 2;
      auStackY_4bc[iVar3 + iVar5 * 7] = local_1c;
      auStackY_44c[iVar3 + iVar5 * 7] = auStackY_84[bVar2];
      auStackY_3dc[iVar3 + iVar5 * 7] = auStackY_28c[bVar2];
      auStackY_2fc[iVar3 + iVar5 * 7] = auStackY_154[bVar2];
      auStackY_36c[iVar3 + iVar5 * 7] = auStackY_ec[bVar2];
      *(undefined1 *)(iVar3 + iVar4 + unaff_EDX) = (&unk_c83c3)[iVar4 + iVar3];
      iVar3 = iVar3 + 1;
    } while (iVar3 < 7);
    iVar5 = iVar5 + 1;
  } while (iVar5 < 4);
  iVar5 = 0;
  do {
    iVar3 = 0;
    iVar4 = iVar3;
LAB_0003885c:
    do {
      iVar3 = iVar3 + 1;
      if (iVar3 < 6) {
        if (((int)auStackY_4bc[iVar5 * 7 + iVar3] <= (int)auStackY_4bc[iVar4 + iVar5 * 7]) &&
           ((auStackY_4bc[iVar5 * 7 + iVar3] != auStackY_4bc[iVar4 + iVar5 * 7] ||
            ((int)auStackY_44c[iVar4 + iVar5 * 7] <= (int)auStackY_44c[iVar5 * 7 + iVar3])))) {
          if ((auStackY_4bc[iVar5 * 7 + iVar3] != auStackY_4bc[iVar4 + iVar5 * 7]) ||
             ((auStackY_44c[iVar5 * 7 + iVar3] != auStackY_44c[iVar4 + iVar5 * 7] ||
              ((int)auStackY_3dc[iVar5 * 7 + iVar3] <= (int)auStackY_3dc[iVar4 + iVar5 * 7])))) {
            if ((auStackY_4bc[iVar5 * 7 + iVar3] != auStackY_4bc[iVar4 + iVar5 * 7]) ||
               (((auStackY_44c[iVar5 * 7 + iVar3] != auStackY_44c[iVar4 + iVar5 * 7] ||
                 (auStackY_3dc[iVar5 * 7 + iVar3] != auStackY_3dc[iVar4 + iVar5 * 7])) ||
                ((int)auStackY_2fc[iVar5 * 7 + iVar3] <= (int)auStackY_2fc[iVar4 + iVar5 * 7])))) {
              if ((((auStackY_4bc[iVar5 * 7 + iVar3] != auStackY_4bc[iVar4 + iVar5 * 7]) ||
                   (auStackY_44c[iVar5 * 7 + iVar3] != auStackY_44c[iVar4 + iVar5 * 7])) ||
                  (auStackY_3dc[iVar5 * 7 + iVar3] != auStackY_3dc[iVar4 + iVar5 * 7])) ||
                 ((auStackY_2fc[iVar5 * 7 + iVar3] != auStackY_2fc[iVar4 + iVar5 * 7] ||
                  ((int)auStackY_36c[iVar4 + iVar5 * 7] <= (int)auStackY_36c[iVar5 * 7 + iVar3]))))
              goto LAB_0003885c;
            }
          }
        }
        auStackY_4bc[iVar5 * 7 + iVar3] =
             auStackY_4bc[iVar5 * 7 + iVar3] ^ auStackY_4bc[iVar4 + iVar5 * 7];
        auStackY_4bc[iVar4 + iVar5 * 7] =
             auStackY_4bc[iVar4 + iVar5 * 7] ^ auStackY_4bc[iVar5 * 7 + iVar3];
        auStackY_4bc[iVar5 * 7 + iVar3] =
             auStackY_4bc[iVar5 * 7 + iVar3] ^ auStackY_4bc[iVar4 + iVar5 * 7];
        auStackY_44c[iVar5 * 7 + iVar3] =
             auStackY_44c[iVar5 * 7 + iVar3] ^ auStackY_44c[iVar4 + iVar5 * 7];
        auStackY_44c[iVar4 + iVar5 * 7] =
             auStackY_44c[iVar4 + iVar5 * 7] ^ auStackY_44c[iVar5 * 7 + iVar3];
        auStackY_44c[iVar5 * 7 + iVar3] =
             auStackY_44c[iVar5 * 7 + iVar3] ^ auStackY_44c[iVar4 + iVar5 * 7];
        auStackY_3dc[iVar5 * 7 + iVar3] =
             auStackY_3dc[iVar5 * 7 + iVar3] ^ auStackY_3dc[iVar4 + iVar5 * 7];
        auStackY_3dc[iVar4 + iVar5 * 7] =
             auStackY_3dc[iVar4 + iVar5 * 7] ^ auStackY_3dc[iVar5 * 7 + iVar3];
        auStackY_3dc[iVar5 * 7 + iVar3] =
             auStackY_3dc[iVar5 * 7 + iVar3] ^ auStackY_3dc[iVar4 + iVar5 * 7];
        auStackY_2fc[iVar5 * 7 + iVar3] =
             auStackY_2fc[iVar5 * 7 + iVar3] ^ auStackY_2fc[iVar4 + iVar5 * 7];
        auStackY_2fc[iVar4 + iVar5 * 7] =
             auStackY_2fc[iVar4 + iVar5 * 7] ^ auStackY_2fc[iVar5 * 7 + iVar3];
        auStackY_2fc[iVar5 * 7 + iVar3] =
             auStackY_2fc[iVar5 * 7 + iVar3] ^ auStackY_2fc[iVar4 + iVar5 * 7];
        auStackY_36c[iVar5 * 7 + iVar3] =
             auStackY_36c[iVar5 * 7 + iVar3] ^ auStackY_36c[iVar4 + iVar5 * 7];
        auStackY_36c[iVar4 + iVar5 * 7] =
             auStackY_36c[iVar4 + iVar5 * 7] ^ auStackY_36c[iVar5 * 7 + iVar3];
        auStackY_36c[iVar5 * 7 + iVar3] =
             auStackY_36c[iVar5 * 7 + iVar3] ^ auStackY_36c[iVar4 + iVar5 * 7];
        iVar1 = iVar5 * 7 + unaff_EDX;
        bVar2 = *(byte *)(iVar1 + iVar3) ^ *(byte *)(iVar4 + iVar1);
        *(byte *)(iVar1 + iVar3) = bVar2;
        bVar2 = *(byte *)(iVar4 + iVar1) ^ bVar2;
        *(byte *)(iVar4 + iVar1) = bVar2;
        *(byte *)(iVar1 + iVar3) = *(byte *)(iVar1 + iVar3) ^ bVar2;
        goto LAB_0003885c;
      }
      iVar3 = iVar4 + 1;
      iVar4 = iVar3;
    } while (iVar3 < 5);
    iVar5 = iVar5 + 1;
  } while (iVar5 < 2);
  do {
    if (3 < iVar5) {
      return uStackY_18;
    }
    iVar3 = 0;
    iVar4 = iVar3;
LAB_00038af5:
    do {
      iVar3 = iVar3 + 1;
      if (iVar3 < 7) {
        if (((int)auStackY_4bc[iVar5 * 7 + iVar3] <= (int)auStackY_4bc[iVar4 + iVar5 * 7]) &&
           ((auStackY_4bc[iVar5 * 7 + iVar3] != auStackY_4bc[iVar4 + iVar5 * 7] ||
            ((int)auStackY_44c[iVar4 + iVar5 * 7] <= (int)auStackY_44c[iVar5 * 7 + iVar3])))) {
          if ((auStackY_4bc[iVar5 * 7 + iVar3] != auStackY_4bc[iVar4 + iVar5 * 7]) ||
             ((auStackY_44c[iVar5 * 7 + iVar3] != auStackY_44c[iVar4 + iVar5 * 7] ||
              ((int)auStackY_3dc[iVar5 * 7 + iVar3] <= (int)auStackY_3dc[iVar4 + iVar5 * 7])))) {
            if ((auStackY_4bc[iVar5 * 7 + iVar3] != auStackY_4bc[iVar4 + iVar5 * 7]) ||
               (((auStackY_44c[iVar5 * 7 + iVar3] != auStackY_44c[iVar4 + iVar5 * 7] ||
                 (auStackY_3dc[iVar5 * 7 + iVar3] != auStackY_3dc[iVar4 + iVar5 * 7])) ||
                ((int)auStackY_2fc[iVar5 * 7 + iVar3] <= (int)auStackY_2fc[iVar4 + iVar5 * 7])))) {
              if ((((auStackY_4bc[iVar5 * 7 + iVar3] != auStackY_4bc[iVar4 + iVar5 * 7]) ||
                   (auStackY_44c[iVar5 * 7 + iVar3] != auStackY_44c[iVar4 + iVar5 * 7])) ||
                  (auStackY_3dc[iVar5 * 7 + iVar3] != auStackY_3dc[iVar4 + iVar5 * 7])) ||
                 ((auStackY_2fc[iVar5 * 7 + iVar3] != auStackY_2fc[iVar4 + iVar5 * 7] ||
                  ((int)auStackY_36c[iVar4 + iVar5 * 7] <= (int)auStackY_36c[iVar5 * 7 + iVar3]))))
              goto LAB_00038af5;
            }
          }
        }
        auStackY_4bc[iVar5 * 7 + iVar3] =
             auStackY_4bc[iVar5 * 7 + iVar3] ^ auStackY_4bc[iVar4 + iVar5 * 7];
        auStackY_4bc[iVar4 + iVar5 * 7] =
             auStackY_4bc[iVar4 + iVar5 * 7] ^ auStackY_4bc[iVar5 * 7 + iVar3];
        auStackY_4bc[iVar5 * 7 + iVar3] =
             auStackY_4bc[iVar5 * 7 + iVar3] ^ auStackY_4bc[iVar4 + iVar5 * 7];
        auStackY_44c[iVar5 * 7 + iVar3] =
             auStackY_44c[iVar5 * 7 + iVar3] ^ auStackY_44c[iVar4 + iVar5 * 7];
        auStackY_44c[iVar4 + iVar5 * 7] =
             auStackY_44c[iVar4 + iVar5 * 7] ^ auStackY_44c[iVar5 * 7 + iVar3];
        auStackY_44c[iVar5 * 7 + iVar3] =
             auStackY_44c[iVar5 * 7 + iVar3] ^ auStackY_44c[iVar4 + iVar5 * 7];
        auStackY_3dc[iVar5 * 7 + iVar3] =
             auStackY_3dc[iVar5 * 7 + iVar3] ^ auStackY_3dc[iVar4 + iVar5 * 7];
        auStackY_3dc[iVar4 + iVar5 * 7] =
             auStackY_3dc[iVar4 + iVar5 * 7] ^ auStackY_3dc[iVar5 * 7 + iVar3];
        auStackY_3dc[iVar5 * 7 + iVar3] =
             auStackY_3dc[iVar5 * 7 + iVar3] ^ auStackY_3dc[iVar4 + iVar5 * 7];
        auStackY_2fc[iVar5 * 7 + iVar3] =
             auStackY_2fc[iVar5 * 7 + iVar3] ^ auStackY_2fc[iVar4 + iVar5 * 7];
        auStackY_2fc[iVar4 + iVar5 * 7] =
             auStackY_2fc[iVar4 + iVar5 * 7] ^ auStackY_2fc[iVar5 * 7 + iVar3];
        auStackY_2fc[iVar5 * 7 + iVar3] =
             auStackY_2fc[iVar5 * 7 + iVar3] ^ auStackY_2fc[iVar4 + iVar5 * 7];
        auStackY_36c[iVar5 * 7 + iVar3] =
             auStackY_36c[iVar5 * 7 + iVar3] ^ auStackY_36c[iVar4 + iVar5 * 7];
        auStackY_36c[iVar4 + iVar5 * 7] =
             auStackY_36c[iVar4 + iVar5 * 7] ^ auStackY_36c[iVar5 * 7 + iVar3];
        auStackY_36c[iVar5 * 7 + iVar3] =
             auStackY_36c[iVar5 * 7 + iVar3] ^ auStackY_36c[iVar4 + iVar5 * 7];
        iVar1 = iVar5 * 7 + unaff_EDX;
        bVar2 = *(byte *)(iVar1 + iVar3) ^ *(byte *)(iVar4 + iVar1);
        *(byte *)(iVar1 + iVar3) = bVar2;
        bVar2 = *(byte *)(iVar4 + iVar1) ^ bVar2;
        *(byte *)(iVar4 + iVar1) = bVar2;
        *(byte *)(iVar1 + iVar3) = *(byte *)(iVar1 + iVar3) ^ bVar2;
        goto LAB_00038af5;
      }
      iVar3 = iVar4 + 1;
      iVar4 = iVar3;
    } while (iVar3 < 6);
    iVar5 = iVar5 + 1;
  } while( true );
}


// ================================================================================================
// sub_38b25 @ 0x38b25 [__watcall]
// ================================================================================================

void __watcall sub_38b25(void)

{
  __CHK(4);
  dword_dd798 = 1;
  return;
}


// ================================================================================================
// sub_38b3a @ 0x38b3a [__watcall]
// ================================================================================================

void __watcall sub_38b3a(void)

{
  __CHK(4);
  dword_dd798 = 0xffffffff;
  return;
}


// ================================================================================================
// team_info_screen @ 0x38b4f [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall
team_info_screen(undefined4 param_1,int *unaff_EDX,int unaff_EBX,void *unaff_ECX,uint param_5,
                undefined4 param_6,uint *param_7)

{
  bool bVar1;
  int iVar2;
  undefined4 uVar3;
  void *__dest;
  undefined4 ******ppppppuVar4;
  undefined4 uVar5;
  undefined *puVar6;
  int *piVar7;
  undefined4 *puVar8;
  int iVar9;
  uint *puVar10;
  int iVar11;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 ******ppppppuVar12;
  undefined4 ******ppppppuVar13;
  int iVar14;
  char *pcVar15;
  char *pcVar16;
  uint uVar17;
  undefined4 ******ppppppuVar18;
  undefined4 ******ppppppuVar19;
  undefined4 *puVar20;
  byte bVar21;
  ulonglong uVar22;
  undefined8 uVar23;
  char acStackY_2566 [1018];
  undefined2 auStackY_216c [1018];
  undefined4 auStackY_1978 [1458];
  undefined auStack_29c [256];
  char acStack_19c [4];
  undefined4 uStack_198;
  char acStack_192 [74];
  undefined auStack_148 [64];
  undefined local_108 [32];
  byte local_e8 [20];
  int local_d4 [6];
  undefined4 local_bc;
  undefined4 uStack_b8;
  char local_ac [12];
  char local_a0 [12];
  undefined *local_94 [2];
  int local_8c [5];
  int local_78;
  int local_74;
  int local_70;
  undefined4 *****local_6c;
  int local_68;
  undefined4 *****local_64;
  int local_60;
  uint local_5c;
  undefined4 local_58;
  int local_54;
  undefined4 local_50;
  int local_3c;
  int local_38;
  int local_18;
  int local_14;
  uint local_10;
  
  bVar21 = 0;
  __CHK(0x2b4);
  local_18 = 0;
  getfontstate(auStack_148);
  setfont(font_main);
  setdefaultscreen();
  local_10 = 0;
  do {
    auStack_29c[local_10] = (undefined)local_10;
    local_10 = local_10 + 1;
  } while ((int)local_10 < 0x100);
  setremaptable(auStack_29c);
  set_dialog_colors(0x41,0x40,0x42,0x40,0);
  if ((param_5 & 1) == 0) {
    make_path(local_108,param_1,off_c80e7,&aDB);
    iVar9 = file_open_read(local_108,&local_58);
    if (iVar9 == 0) {
      iVar9 = sub_384b8(local_58,local_e8);
    }
    file_close(&local_58);
  }
  else {
    iVar9 = 0;
    memcpy(local_e8,&unk_c83c3,0x1c);
  }
  if (iVar9 == 0) {
    if ((param_5 == 8) && (*unaff_EDX == 1)) {
      bVar1 = false;
    }
    else {
      bVar1 = true;
    }
    if (bVar1) {
      sound_fade(dword_d2431,3,100);
      uVar3 = allocmem(&aPal_c1897,0x300,0x20);
      getpalette(0,0x100,uVar3);
      fade_palette(1,uVar3,0x10);
      freemem(uVar3);
      if ((sound_enabled != '\0') && (dword_c721d != 0)) {
        do {
          iVar9 = sound_channel_status(ram0x000d242c >> 0x18,3);
        } while (iVar9 == 0);
        releasememblock(dword_c721d);
        dword_c721d = 0;
      }
      __dest = (void *)allocmem(&aTPI,0x30c,0x20);
      memcpy(__dest,unaff_ECX,0x30c);
      puVar6 = install_path;
      if (byte_ed858 != '\x01') {
        puVar6 = (undefined *)0x0;
      }
      make_path(local_108,puVar6,aEmbnhl_c189f,0);
      local_50 = loadshapes(local_108,0);
      uVar3 = locateshape(local_50,&aBkgd_c18a6);
      setdefaultscreen();
      clearclip(0);
      set_text_colors(0x40,0x43);
      drawshape_remap(uVar3,0,0);
      sub_37fba(__dest,param_6,local_e8,uVar3);
      if ((param_5 & 1) == 0) {
        if ((param_5 & 8) != 0) {
          off_c87b0 = &unk_c86cc;
          goto LAB_00038e22;
        }
        off_c87b0 = (undefined *)0x0;
        local_8c[2] = 1;
      }
      else {
        off_c87b0 = &unk_c86fc;
LAB_00038e22:
        local_8c[2] = 2;
      }
      local_94[0] = &unk_c8778;
      local_94[1] = (undefined *)0x0;
      local_8c[0] = 0;
      local_8c[1] = 0;
      local_bc = 0;
      uStack_b8 = 0;
      local_d4[2] = 0;
      local_d4[3] = 0;
      draw_menu_items(&unk_c8778,local_8c[2],0x40,0x41,0x42);
      local_14 = 0;
      *param_7 = (uint)local_e8[0];
      sub_37ea6((uint)local_e8[0],local_e8,0xffffffff);
      if (param_5 == 1) {
        local_38 = 0;
      }
      else {
        local_38 = *unaff_EDX;
      }
      ppppppuVar4 = (undefined4 ******)
                    allocmem(aPointer_c18ab,
                             (((int)pointer_shapes[1] >> 0x10) + 1) *
                             ((*(int *)((int)pointer_shapes + 2) >> 0x10) * 4 + 4) + 0x11,0x20);
      ppppppuVar18 = ppppppuVar4 + (uint)bVar21 * -2 + 1;
      ppppppuVar12 = pointer_shapes + (uint)bVar21 * -2 + 1;
      *ppppppuVar4 = *pointer_shapes;
      ppppppuVar19 = ppppppuVar18 + (uint)bVar21 * -2 + 1;
      ppppppuVar13 = ppppppuVar12 + (uint)bVar21 * -2 + 1;
      *ppppppuVar18 = *ppppppuVar12;
      *ppppppuVar19 = *ppppppuVar13;
      ppppppuVar19[(uint)bVar21 * -2 + 1] = ppppppuVar13[(uint)bVar21 * -2 + 1];
      *(undefined *)(ppppppuVar19 + (uint)bVar21 * -2 + 1 + (uint)bVar21 * -2 + 1) =
           *(undefined *)(ppppppuVar13 + (uint)bVar21 * -2 + 1 + (uint)bVar21 * -2 + 1);
      *(short *)(ppppppuVar4 + 1) = *(short *)(pointer_shapes + 1) + 1;
      *(short *)((int)ppppppuVar4 + 6) = *(short *)((int)pointer_shapes + 6) + 1;
      if ((sound_enabled != '\0') && (dword_c721d == 0)) {
        puVar6 = install_path;
        if (byte_ed9ac != '\x01') {
          puVar6 = (undefined *)0x0;
        }
        make_path(local_108,puVar6,aLeaguetm_c18b8,&aIff_c18b3);
        dword_c721d = loadsound(local_108);
        if ((dword_c721d != 0) && (((byte)option_flags & 0x40) != 0)) {
          playsample(dword_c721d,dword_d2431,3);
        }
      }
      puVar6 = install_path;
      if (byte_ed979 != '\x01') {
        puVar6 = (undefined *)0x0;
      }
      make_path(local_108,puVar6,aTspal,0);
      uVar5 = loadshapes(local_108,0);
      iVar9 = locateshape(uVar5,&aPal_c18c7);
      fade_palette(0,iVar9 + 0x10,0x10);
      freemem(uVar5);
      getmouse(&local_5c,&local_60,&local_64);
      local_68 = local_60;
      local_6c = local_64;
      grabshape(ppppppuVar4,local_60 + -4,local_64);
      drawshape_remap(pointer_shapes,local_60 + -4,local_64);
      uVar22 = event_queue_reset();
      local_3c = 0;
      dword_dd798 = 0;
      ppppppuVar12 = ppppppuVar4;
      do {
        uVar5 = 0;
        do {
          uVar23 = event_queue_pop((int)uVar22,(int)(uVar22 >> 0x20),ppppppuVar12);
          uVar22 = CONCAT44((int)((ulonglong)uVar23 >> 0x20),uVar5);
          if ((int)uVar23 == 0) break;
          ppppppuVar12 = &local_6c;
          uVar22 = (*ui_poll_callback)();
          uVar5 = (undefined4)uVar22;
        } while ((uVar22 & 2) == 0);
        uVar5 = (undefined4)(uVar22 >> 0x20);
        if ((uVar22 & 2) == 0) {
          if ((local_68 != local_60) || (local_6c != local_64)) {
            drawshape(ppppppuVar4,local_60 + -4,local_64);
            grabshape(ppppppuVar4,local_68 + -4,local_6c);
LAB_0003a0de:
            ppppppuVar12 = pointer_shapes;
            drawshape_remap(pointer_shapes,local_68 + -4,local_6c);
            uVar5 = extraout_EDX_00;
            goto LAB_0003a100;
          }
        }
        else {
          iVar9 = hit_test_menus(local_68,local_6c,local_94,local_18,local_8c + 2,local_d4 + 2,
                                 &local_74,local_8c + 5);
          iVar11 = local_60 + -4;
          if (iVar9 == 0) {
            drawshape(ppppppuVar4,iVar11,local_64);
            if (local_18 == 0) {
              local_5c = sub_37b92(local_68,local_6c);
              if (((param_5 == 0x10) && (local_14 == 1)) && (local_5c == *param_7)) {
                local_5c = 0xffffffff;
              }
              if (-1 < (int)local_5c) {
                puVar10 = param_7 + local_14;
                uVar17 = *puVar10;
                *puVar10 = local_5c;
                if (uVar17 == local_5c) {
                  if (((param_5 & 0x18) == 0) ||
                     (*(char *)((int)__dest + (local_5c * 0x10 - uVar17) * 2 + 0x17) != '\x01')) {
                    if (((param_5 & 4) != 0) && (1 < local_38)) {
                      puVar10 = param_7 + local_14;
                      if ((*(char *)((int)__dest + *puVar10 * 0x1e + 0x19) == '\0') &&
                         (*(char *)((int)__dest + *puVar10 * 0x1e + 0x17) == '\x01')) {
                        sub_37d6a(*puVar10,local_e8,ppppppuVar4,local_60,local_64);
                        sub_37ea6(*puVar10,local_e8,0);
                        sub_37ea6(*puVar10,local_e8,0xffffffff);
                        dword_c786c = (void *)(*puVar10 * 0x1e + (int)__dest);
                        iVar9 = message_dialog(0xffffffff,0xffffffff,&off_c7868,2,&unk_c7870,2,
                                               &local_60,&local_64,0xffffffff);
                        if ((iVar9 == 0) && (iVar9 = password_prompt(*puVar10,__dest), iVar9 == 0))
                        {
                          *(undefined *)((int)__dest + *puVar10 * 0x1e + 0x17) = 0;
                          local_38 = local_38 + -1;
                          memset((void *)(*puVar10 * 0x1e + (int)__dest),0,0xb);
                          memset((void *)((int)__dest + *puVar10 * 0x1e + 0xb),0,0xb);
                          sub_37e5b(*puVar10,local_e8);
                          sub_37c53(*puVar10,__dest,uVar3,local_e8);
                        }
                        else {
                          sub_37e5b(*puVar10,local_e8);
                        }
                        goto LAB_0003a06b;
                      }
                    }
                    if (((param_5 & 3) != 0) &&
                       (puVar10 = param_7 + local_14,
                       *(char *)((int)__dest + *puVar10 * 0x1e + 0x17) == '\0')) {
                      sub_37d6a(*puVar10,local_e8,ppppppuVar4,local_60,local_64);
                      sub_37ea6(*puVar10,local_e8,0);
                      sub_37ea6(*puVar10,local_e8,0xffffffff);
                      memset((void *)(*puVar10 * 0x1e + (int)__dest),0,0xb);
                      memset((void *)((int)__dest + *puVar10 * 0x1e + 0xb),0,0xb);
                      acStack_19c[0] = aWhoWillPlayThe[0];
                      acStack_19c[1] = aWhoWillPlayThe[1];
                      acStack_19c[2] = aWhoWillPlayThe[2];
                      acStack_19c[3] = aWhoWillPlayThe[3];
                      puVar8 = (undefined4 *)
                               (&stack0xfffffe6c + (uint)bVar21 * -8 + (uint)bVar21 * -8);
                      pcVar15 = aWhoWillPlayThe + (uint)bVar21 * -8 + (uint)bVar21 * -8 + 8;
                      (&uStack_198)[(uint)bVar21 * -2] =
                           *(undefined4 *)(aWhoWillPlayThe + (uint)bVar21 * -8 + 4);
                      puVar20 = puVar8 + (uint)bVar21 * -2 + 1;
                      pcVar16 = pcVar15 + ((uint)bVar21 * -2 + 1) * 4;
                      *puVar8 = *(undefined4 *)pcVar15;
                      *puVar20 = *(undefined4 *)pcVar16;
                      *(undefined2 *)(puVar20 + (uint)bVar21 * -2 + 1) =
                           *(undefined2 *)(pcVar16 + ((uint)bVar21 * -2 + 1) * 4);
                      *(char *)((int)(puVar20 + (uint)bVar21 * -2 + 1) + (uint)bVar21 * -4 + 2) =
                           (pcVar16 + ((uint)bVar21 * -2 + 1) * 4)[(uint)bVar21 * -4 + 2];
                      if (*puVar10 == 0x18) {
                        pcVar15 = aMightyDucksOfAnaheim_c18e8;
                      }
                      else {
                        pcVar15 = (char *)(unaff_EBX + *puVar10 * 0x15);
                      }
                      strcat(acStack_19c,pcVar15);
                      strcat(acStack_19c,&unk_c1900);
                      do {
                        iVar9 = sub_2fedf(acStack_19c,local_a0,10,0x46,0,0,0,1,4);
                        if (iVar9 != 0x1b) {
                          strcpy((char *)(param_7[local_14] * 0x1e + (int)__dest),local_a0);
                          iVar9 = 0;
                          uVar17 = 0;
                          do {
                            if (((uVar17 != param_7[local_14]) &&
                                (*(char *)((int)__dest + uVar17 * 0x1e + 0x17) == '\x01')) &&
                               (iVar11 = stricmp((void *)(param_7[local_14] * 0x1e + (int)__dest)),
                               iVar11 == 0)) {
                              message_dialog(0xffffffff,0xffffffff,&off_c7592,1,0,0,&local_68,
                                             &local_6c,0xffffffff);
                              iVar9 = 1;
                            }
                            uVar17 = uVar17 + 1;
                          } while ((int)uVar17 < 0x1a);
                        }
                      } while ((iVar9 != 0) && (iVar9 != 0x1b));
                      do {
                        if (iVar9 == 0x1b) break;
                        strcpy(acStack_19c,aEnterPasswordFor);
                        strcat(acStack_19c,(char *)(param_7[local_14] * 0x1e + (int)__dest));
                        iVar9 = sub_2fedf(acStack_19c,local_a0,10,0x3c,0,0,0,0,6);
                        if (iVar9 != 0x1b) {
                          strcpy(acStack_19c,aVerifyPasswordFor);
                          strcat(acStack_19c,(char *)(param_7[local_14] * 0x1e + (int)__dest));
                          iVar9 = sub_2fedf(acStack_19c,local_ac,10,0x3c,0,0,0,0,6);
                        }
                        if (iVar9 != 0x1b) {
                          iVar9 = 0;
                          iVar11 = strcmp(local_a0,local_ac);
                          if (iVar11 != 0) {
                            message_dialog(0xffffffff,0xffffffff,&off_c8055,2,0,0,&local_60,
                                           &local_64,0xffffffff);
                            iVar9 = -1;
                          }
                        }
                      } while (iVar9 != 0);
                      puVar10 = param_7 + local_14;
                      if (iVar9 == 0x1b) {
                        sub_37e5b(*puVar10,local_e8);
                      }
                      else {
                        *(undefined *)((int)__dest + *puVar10 * 0x1e + 0x17) = 1;
                        local_38 = local_38 + 1;
                        strcpy((char *)((int)__dest + *puVar10 * 0x1e + 0xb),local_a0);
                        sub_3a597((int)__dest + *puVar10 * 0x1e + 0xb);
                        sub_37e5b(*puVar10,local_e8);
                        sub_37c53(*puVar10,__dest,uVar3,local_e8);
                      }
                      event_queue_reset();
                    }
                  }
                  else {
                    sub_37ea6(uVar17,local_e8,0);
                    sub_37ea6(*puVar10,local_e8,0xffffffff);
                    if ((local_14 == 0) && ((param_5 & 0x10) != 0)) {
                      local_14 = 1;
                      param_7[1] = 0xffffffff;
                    }
                    else {
                      local_3c = -1;
                    }
                  }
                }
                else {
                  if (-1 < (int)uVar17) {
                    sub_37ea6(uVar17,local_e8,0xffffffff);
                  }
                  sub_37ea6(param_7[local_14],local_e8,0xffffffff);
                }
              }
            }
            else {
              for (local_10 = 1; -1 < (int)local_10; local_10 = local_10 + -1) {
                if (local_8c[local_10] != 0) {
                  drawshape(local_8c[local_10],local_d4[local_10 * 2 + 2],local_d4[local_10 * 2 + 3]
                           );
                  local_d4[local_10 * 2 + 2] = 0;
                  local_d4[local_10 * 2 + 3] = 0;
                  freemem(local_8c[local_10]);
                }
              }
              local_18 = 0;
              local_94[1] = (undefined *)0x0;
              local_8c[0] = 0;
              local_8c[1] = 0;
              uStack_b8 = 0;
              local_8c[3] = 0;
            }
          }
          else {
            if (*(int *)(local_94[local_74] + local_78 * 0x20 + 0x14) == 0) {
              if (*(int *)(local_94[local_74] + local_78 * 0x20 + 0x18) == 0) {
                drawshape(ppppppuVar4,iVar11,local_64);
                highlight_menu_item(local_94[local_74] + local_d4[local_74 + 6] * 0x20,
                                    local_d4[local_74 * 2 + 2],local_d4[local_74 * 2 + 3],0x40,0x41,
                                    0x42);
                iVar14 = local_74;
                local_d4[local_74 + 6] = local_78;
                iVar9 = local_d4[iVar14 * 2 + 3];
                iVar11 = local_d4[iVar14 * 2 + 2];
                puVar6 = local_94[iVar14] + local_d4[iVar14 + 6] * 0x20;
              }
              else {
                drawshape(ppppppuVar4,iVar11,local_64);
                if (local_18 != local_74) {
                  for (local_10 = local_18; local_74 < (int)local_10; local_10 = local_10 + -1) {
                    local_d4[local_10 + 6] = 0;
                    if (local_8c[local_10] != 0) {
                      drawshape(local_8c[local_10],local_d4[local_10 * 2 + 2],
                                local_d4[local_10 * 2 + 3]);
                      local_d4[local_10 * 2 + 2] = 0;
                      local_d4[local_10 * 2 + 3] = 0;
                      freemem(local_8c[local_10]);
                      local_8c[local_10] = 0;
                      local_94[local_10] = (undefined *)0x0;
                      local_8c[local_10 + 2] = 0;
                    }
                  }
                  local_18 = local_74;
                }
                local_54 = local_d4[local_18 + 6] * 0x20;
                highlight_menu_item(local_94[local_18] + local_d4[local_18 + 6] * 0x20,
                                    local_d4[local_18 * 2 + 2],local_d4[local_18 * 2 + 3],0x40,0x41,
                                    0x42);
                local_d4[local_18 + 6] = local_78;
                unhighlight_menu_item
                          (local_94[local_18] + local_78 * 0x20,local_d4[local_18 * 2 + 2],
                           local_d4[local_18 * 2 + 3],0x40,0x41,0x42);
                iVar9 = local_74;
                iVar11 = local_78 * 0x20;
                iVar14 = local_18 + 1;
                local_94[iVar14] = *(undefined **)(local_94[local_74] + iVar11 + 0x18);
                piVar7 = (int *)(local_94[iVar9] + iVar11);
                local_8c[local_18 + 3] = piVar7[7];
                if (iVar14 == 1) {
                  iVar9 = *piVar7;
                }
                else {
                  iVar9 = piVar7[2];
                }
                local_d4[iVar14 * 2 + 2] = iVar9 + local_d4[iVar14 * 2];
                if (iVar14 == 1) {
                  iVar9 = *(int *)(local_94[local_74] + local_78 * 0x20 + 0xc);
                }
                else {
                  iVar9 = *(int *)(local_94[local_74] + local_78 * 0x20 + 4);
                }
                local_d4[iVar14 * 2 + 3] = iVar9 + local_d4[iVar14 * 2 + 1];
                piVar7 = (int *)local_94[iVar14];
                local_70 = (piVar7[local_8c[local_18 + 3] * 8 + -6] - *piVar7) + 1;
                local_8c[4] = (piVar7[local_8c[local_18 + 3] * 8 + -5] - piVar7[1]) + 1;
                puVar8 = (undefined4 *)
                         allocmem(aMenubuff_c18cc,local_70 * 4 * local_8c[4] + 0x11,0x20);
                local_8c[iVar14] = (int)puVar8;
                puVar20 = puVar8 + (uint)bVar21 * -2 + 1;
                ppppppuVar12 = pointer_shapes + (uint)bVar21 * -2 + 1;
                *puVar8 = *pointer_shapes;
                puVar8 = puVar20 + (uint)bVar21 * -2 + 1;
                ppppppuVar13 = ppppppuVar12 + (uint)bVar21 * -2 + 1;
                *puVar20 = *ppppppuVar12;
                *puVar8 = *ppppppuVar13;
                puVar8[(uint)bVar21 * -2 + 1] = ppppppuVar13[(uint)bVar21 * -2 + 1];
                *(undefined *)(puVar8 + (uint)bVar21 * -2 + 1 + (uint)bVar21 * -2 + 1) =
                     *(undefined *)(ppppppuVar13 + (uint)bVar21 * -2 + 1 + (uint)bVar21 * -2 + 1);
                *(short *)(local_8c[iVar14] + 4) = (short)local_70;
                *(short *)(local_8c[iVar14] + 6) = (short)local_8c[4];
                grabshape(local_8c[iVar14],local_d4[iVar14 * 2 + 2],local_d4[iVar14 * 2 + 3]);
                draw_menu(local_94[iVar14],local_8c[local_18 + 3],local_d4[iVar14 * 2 + 2],
                          local_d4[iVar14 * 2 + 3],0x40,0x41,0x42);
                local_d4[local_18 + 7] = 0;
                iVar9 = local_d4[iVar14 * 2 + 3];
                iVar11 = local_d4[iVar14 * 2 + 2];
                puVar6 = local_94[iVar14];
                local_18 = iVar14;
              }
            }
            else {
              if (local_78 == local_d4[local_74 + 6]) {
                drawshape(ppppppuVar4,iVar11,local_64);
                for (local_10 = 1; -1 < (int)local_10; local_10 = local_10 + -1) {
                  if (local_8c[local_10] != 0) {
                    drawshape(local_8c[local_10],local_d4[local_10 * 2 + 2],
                              local_d4[local_10 * 2 + 3]);
                    local_d4[local_10 * 2 + 2] = 0;
                    local_d4[local_10 * 2 + 3] = 0;
                    freemem(local_8c[local_10]);
                  }
                }
                local_18 = 0;
                (**(code **)(local_94[local_74] + local_78 * 0x20 + 0x14))();
                if (dword_dd798 == -1) {
                  param_7[local_14] = 0xffffffff;
                  uVar5 = allocmem(&aPal_c1897,0x300,0x20);
                  if ((sound_enabled != '\0') && (dword_c721d != 0)) {
                    sound_fade(dword_d2431,3,100);
                  }
                  getpalette(0,0x100,uVar5);
                  fade_palette(1,uVar5,0x10);
                  freemem(uVar5);
LAB_000393b2:
                  local_3c = -1;
                }
                else if ((dword_dd798 == 1) &&
                        (((((param_5 & 7) != 0 && (0 < local_38)) ||
                          (((param_5 & 8) != 0 &&
                           (*(char *)((int)__dest + param_7[local_14] * 0x1e + 0x17) == '\x01'))))
                         || (((((param_5 & 0x10) != 0 && (local_14 == 1)) &&
                              (*(char *)((int)__dest + *param_7 * 0x1e + 0x17) == '\x01')) &&
                             (*(char *)((int)__dest + param_7[1] * 0x1e + 0x17) == '\x01'))))))
                goto LAB_000393b2;
                local_94[1] = (undefined *)0x0;
                local_8c[0] = 0;
                local_8c[1] = 0;
                uStack_b8 = 0;
                local_8c[3] = 0;
                setmousepos(local_60,local_64);
                local_68 = local_60;
                local_6c = local_64;
                event_queue_reset();
                goto LAB_0003a06b;
              }
              drawshape(ppppppuVar4,iVar11,local_64);
              highlight_menu_item(local_94[local_74] + local_d4[local_74 + 6] * 0x20,
                                  local_d4[local_74 * 2 + 2],local_d4[local_74 * 2 + 3],0x40,0x41,
                                  0x42);
              iVar2 = local_74;
              iVar14 = local_78;
              local_d4[local_74 + 6] = local_78;
              iVar9 = local_d4[iVar2 * 2 + 3];
              iVar11 = local_d4[iVar2 * 2 + 2];
              puVar6 = local_94[iVar2] + iVar14 * 0x20;
            }
            unhighlight_menu_item(puVar6,iVar11,iVar9,0x40,0x41,0x42);
          }
LAB_0003a06b:
          grabshape(ppppppuVar4,local_60 + -4,local_64);
          ppppppuVar12 = (undefined4 ******)local_64;
          drawshape(ppppppuVar4,local_60 + -4,local_64);
          grabshape(ppppppuVar4,local_68 + -4,local_6c);
          uVar5 = extraout_EDX;
          if (local_3c == 0) goto LAB_0003a0de;
LAB_0003a100:
          local_60 = local_68;
          local_64 = local_6c;
        }
        uVar22 = CONCAT44(uVar5,local_6c);
      } while (local_3c == 0);
      *unaff_EDX = local_38;
      freemem(ppppppuVar4);
      if ((-1 < (int)param_7[local_14]) && ((param_5 & 8) == 0)) {
        if ((param_5 & 1) != 0) {
          league_control_dialog(__dest,*unaff_EDX,&local_60,&local_64);
        }
        sub_38386(__dest,unaff_ECX,param_5,*unaff_EDX);
        memcpy(unaff_ECX,__dest,0x30c);
      }
      freemem(__dest);
      freemem(local_50);
      goto LAB_0003a233;
    }
  }
  if (iVar9 == 0) {
    local_10 = 0;
    do {
      if (*(char *)((int)unaff_ECX + local_10 * 0x1e + 0x17) == '\x01') {
        *param_7 = local_10;
        local_10 = 0x1a;
      }
      local_10 = local_10 + 1;
    } while ((int)local_10 < 0x1a);
  }
LAB_0003a233:
  setfontstate(auStack_148);
  return;
}


