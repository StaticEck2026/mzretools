// Decompiled by Ghidra from hockey.elf (via ledisasm ELF export)
// This is machine generated pseudo-C meant as a reference for porting, it does not compile as is.
#include "prototypes.h"

// ================================================================================================
// sub_72a5c @ 0x72a5c [__watcall]
// ================================================================================================

undefined4 __watcall sub_72a5c(int param_1,int unaff_EDX,int *unaff_EBX)

{
  int iVar1;
  
  __CHK(0xc);
  iVar1 = 0;
  while ((((param_1 + -6 < (int)(&unk_d1084)[iVar1 * 4] ||
           ((int)(&unk_d108c)[iVar1 * 4] < param_1 + -6)) ||
          (unaff_EDX + -0x13 < (int)(&unk_d1088)[iVar1 * 4])) ||
         ((int)(&unk_d1090)[iVar1 * 4] < unaff_EDX + -0x13))) {
    iVar1 = iVar1 + 1;
    if (0xf < iVar1) {
      return 0;
    }
  }
  *unaff_EBX = iVar1;
  return 1;
}


// ================================================================================================
// sub_72ac6 @ 0x72ac6 [__watcall]
// ================================================================================================

undefined8 __watcall sub_72ac6(int *param_1,undefined4 unaff_EDX)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  undefined4 uStack_1c;
  
  __CHK(0x38);
  settextpos(0xfa,0xff);
  iVar5 = 0;
  do {
    fillrect((&dword_d1124)[iVar5 * 4] + 10,(&dword_d1128)[iVar5 * 4] + 0x13,
             ((&dword_d112c)[iVar5 * 4] - (&dword_d1124)[iVar5 * 4]) + 1,
             ((&dword_d1130)[iVar5 * 4] - (&dword_d1128)[iVar5 * 4]) + 1,0xf9);
    iVar5 = iVar5 + 1;
  } while (iVar5 < 6);
  if (param_1 == (int *)0x0) {
    uStack_1c = 0;
  }
  else {
    if (*param_1 < 7) {
      for (iVar5 = 0; iVar5 < *param_1; iVar5 = iVar5 + 1) {
        sub_2c135(param_1[iVar5 + 4],(&dword_d1124)[iVar5 * 4] + 10,(&dword_d1128)[iVar5 * 4] + 0x10
                 );
      }
    }
    else {
      iVar5 = 0;
      do {
        sub_2c135(param_1[param_1[2] + iVar5 + 4],(&dword_d1124)[iVar5 * 4] + 10,
                  (&dword_d1128)[iVar5 * 4] + 0x10);
        iVar5 = iVar5 + 1;
      } while (iVar5 < 6);
    }
    if (0 < *param_1) {
      fillrect(dword_d1114 + 0xd,dword_d1118 + 0x16,(dword_d111c - dword_d1114) + -5,
               (dword_d1120 - dword_d1118) + -5,0xf8);
      sub_2c135(param_1[param_1[1] + 4],dword_d1114 + 0xd,dword_d1118 + 0x13);
    }
    iVar5 = param_1[1];
    if ((param_1[2] <= iVar5) && (iVar5 <= param_1[3])) {
      iVar5 = iVar5 - param_1[2];
      fillrect((&dword_d1124)[iVar5 * 4] + 10,(&dword_d1128)[iVar5 * 4] + 0x13,
               (&dword_d112c)[iVar5 * 4] - (&dword_d1124)[iVar5 * 4],
               (&dword_d1130)[iVar5 * 4] - (&dword_d1128)[iVar5 * 4],0xf8);
      sub_2c135(param_1[param_1[2] + iVar5 + 4],(&dword_d1124)[iVar5 * 4] + 10,
                (&dword_d1128)[iVar5 * 4] + 0x10);
    }
    fillrect(dword_d1104 + 10,dword_d1108 + 0x13,(dword_d110c - dword_d1104) + 1,
             (dword_d1110 - dword_d1108) + 1,0xf9);
    iVar5 = dword_d1104;
    if (*param_1 < 7) {
      dword_dd668._0_2_ = (ushort)dword_dd668 & 0x6fc;
      switch(*param_1) {
      case 6:
        dword_dd668._0_2_ = (ushort)dword_dd668 | 0x8000;
      case 5:
        dword_dd668._0_2_ = (ushort)dword_dd668 | 0x4000;
      case 4:
        dword_dd668._0_2_ = (ushort)dword_dd668 | 0x2000;
      case 3:
        dword_dd668._0_2_ = (ushort)dword_dd668 | 0x1000;
      case 2:
        dword_dd668._0_2_ = (ushort)dword_dd668 | 0x800;
      case 1:
        dword_dd668._0_2_ = (ushort)dword_dd668 | 0x400;
      }
    }
    else {
      dword_dd668._0_2_ = (ushort)dword_dd668 | 0xf903;
      iVar4 = dword_d1104 + 10;
      iVar1 = dword_d1108 + 0x13 + (param_1[2] * 0x8e) / *param_1;
      iVar3 = dword_d110c + 10;
      iVar2 = dword_d1108 + 0x13 + ((param_1[3] + 1) * 0x8e) / *param_1;
      sub_b4fac(iVar4,iVar1,dword_d110c + 9,iVar1,0x7d,iVar3);
      sub_b4fac(iVar4,iVar1,iVar4,iVar2 + -1,0x7d);
      sub_b4fac(iVar3,iVar1 + 1,iVar3,iVar2,0x7b);
      sub_b4fac(iVar5 + 0xb,iVar2,iVar3,iVar2,0x7b);
    }
    uVar6 = dword_dd634;
    if (((dword_dd658 == 0) || (uVar6 = dword_dd63c, dword_dd658 < 2)) ||
       (uVar6 = dword_dd660, dword_dd658 == 2)) {
      drawshape_remap(uVar6,0xa3,0x4b);
    }
  }
  return CONCAT44(unaff_EDX,uStack_1c);
}


// ================================================================================================
// database_select_screen @ 0x72de7 [__watcall]
// ================================================================================================

undefined8 __watcall database_select_screen(void)

{
  undefined4 **ppuVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  undefined4 ***pppuVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  int *piVar10;
  undefined4 **ppuVar11;
  undefined4 **ppuVar12;
  byte bVar13;
  undefined4 uVar14;
  undefined4 **local_38;
  uint local_34;
  uint local_30;
  int *local_2c;
  int *local_28;
  int *local_24;
  int *local_20;
  int iStack_1c;
  
  bVar13 = 0;
  __CHK(0x44);
  iStack_1c = 0;
  local_38 = &local_24;
  getmouse(&local_30,&local_20);
  pppuVar7 = (undefined4 ***)&local_34;
  local_28 = local_20;
  local_2c = local_24;
  local_38 = (undefined4 **)0x72e2c;
  setdefaultscreen();
  local_38 = (undefined4 **)0x20;
  ppuVar1 = (undefined4 **)
            allocmem(aPointer_c30bb,
                     (((int)pointer_shapes[1] >> 0x10) + 1) *
                     ((*(int *)((int)pointer_shapes + 2) >> 0x10) + 1) + 0x11);
  ppuVar11 = ppuVar1 + (uint)bVar13 * -2 + 1;
  puVar8 = pointer_shapes + (uint)bVar13 * -2 + 1;
  *ppuVar1 = (undefined4 *)*pointer_shapes;
  ppuVar12 = ppuVar11 + (uint)bVar13 * -2 + 1;
  puVar9 = puVar8 + (uint)bVar13 * -2 + 1;
  *ppuVar11 = (undefined4 *)*puVar8;
  *ppuVar12 = (undefined4 *)*puVar9;
  ppuVar12[(uint)bVar13 * -2 + 1] = (undefined4 *)puVar9[(uint)bVar13 * -2 + 1];
  *(undefined *)(ppuVar12 + (uint)bVar13 * -2 + 1 + (uint)bVar13 * -2 + 1) =
       *(undefined *)(puVar9 + (uint)bVar13 * -2 + 1 + (uint)bVar13 * -2 + 1);
  *(short *)(ppuVar1 + 1) = *(short *)(pointer_shapes + 1) + 1;
  *(short *)((int)ppuVar1 + 6) = *(short *)((int)pointer_shapes + 6) + 1;
  local_38 = (undefined4 **)local_2c;
  grabshape(ppuVar1,local_28 + -1);
  local_38 = (undefined4 **)local_2c;
  drawshape_remap(pointer_shapes,local_28 + -1);
  piVar10 = (int *)(&off_d1184)[dword_dd658];
  local_38 = (undefined4 **)0x72ec6;
  event_queue_reset();
LAB_00072ec6:
  local_30 = 0;
  do {
    local_38 = (undefined4 **)0x72ed1;
    iVar2 = event_queue_pop();
    if (iVar2 == 0) break;
    local_38 = (undefined4 **)0x72ee3;
    local_30 = (*ui_poll_callback)();
  } while (local_30 == 0);
  if (local_30 == 0) goto code_r0x00072ef6;
  local_38 = (undefined4 **)local_24;
  drawshape2(ppuVar1,local_20 + -1);
  if (((local_30 & 1) == 0) || ((dword_dd668 & 0x100) == 0)) {
    if ((local_30 & 2) == 0) {
      if ((local_30 & 4) != 0) goto LAB_0007319a;
    }
    else {
      iStack_1c = 0;
      local_38 = (undefined4 **)0x730e1;
      iVar2 = sub_72a5c(local_28,local_2c,&local_34);
      if (iVar2 != 0) {
        local_34 = 1 << ((byte)local_34 & 0x1f);
        if ((local_34 & dword_dd668) != 0) {
          if (local_34 < 0x10) {
            if (local_34 < 2) {
              if (local_34 == 1) {
                local_38 = (undefined4 **)0x46;
                drawshape_remap(dword_dd648,0x18);
                if (piVar10[2] != 0) {
                  piVar10[2] = piVar10[2] + -1;
                  piVar10[3] = piVar10[3] + -1;
                  local_38 = (undefined4 **)0x731d0;
                  sub_72ac6(piVar10);
                }
                local_38 = (undefined4 **)0x46;
                uVar14 = 0x18;
                uVar4 = dword_dd664;
                goto LAB_000731db;
              }
            }
            else {
              if (local_34 < 3) {
                local_38 = (undefined4 **)0x46;
                drawshape_remap(dword_dd654,0x18);
                if (piVar10[3] + 1 < *piVar10) {
                  piVar10[2] = piVar10[2] + 1;
                  piVar10[3] = piVar10[3] + 1;
                  local_38 = (undefined4 **)0x73210;
                  sub_72ac6(piVar10);
                }
                local_38 = (undefined4 **)0x46;
                uVar14 = 0x18;
                uVar4 = dword_dd664;
LAB_000731db:
                drawshape_remap(uVar4,uVar14);
                goto LAB_00073395;
              }
              if (3 < local_34) {
                if (local_34 < 5) {
                  local_38 = (undefined4 **)0xbf;
                  drawshape_remap(dword_dd640,0x23);
                  local_38 = ppuVar1;
                  freemem();
                  local_38 = (undefined4 **)0x732f4;
                  sub_733c4();
                  pppuVar7 = &local_38;
                  local_38 = (undefined4 **)0x732f9;
                  sub_6de7e();
                  *(undefined4 *)((int)pppuVar7 + -4) = 0x732fe;
                  player_ratings_card();
                  uVar4 = 1;
                  goto switchD_00072a22_caseD_6;
                }
                if (local_34 == 8) {
                  local_38 = (undefined4 **)0xbf;
                  drawshape_remap(dword_dd644,0x23);
                  local_38 = (undefined4 **)0x73332;
                  database_dbx_check((&off_d1184)[dword_dd658]);
                  if (dword_dd658 < 0) {
                    piVar10 = (int *)0x0;
                  }
                  else {
                    piVar10 = (int *)(&off_d1184)[dword_dd658];
                  }
                  local_38 = (undefined4 **)0x7334e;
                  sub_72ac6(piVar10);
                  local_38 = (undefined4 **)0xbf;
                  uVar14 = 0x23;
                  uVar4 = dword_dd638;
                  goto LAB_000731db;
                }
              }
            }
LAB_00073361:
            local_38 = (undefined4 **)0x73370;
            sub_2c3ff(local_28,local_2c,&local_34);
            if (9 < (int)local_34) {
              piVar10[1] = piVar10[2] + local_34 + -10;
            }
          }
          else {
            if (local_34 < 0x11) {
              local_38 = (undefined4 **)0xbf;
              drawshape_remap(dword_dd64c,0x23);
LAB_0007319a:
              local_38 = ppuVar1;
              freemem();
              uVar4 = 0;
switchD_00072a22_caseD_6:
              return CONCAT44(*(undefined4 *)((int)pppuVar7 + 0x28),uVar4);
            }
            if (local_34 < 0x40) {
              if (local_34 != 0x20) goto LAB_00073361;
              dword_dd658 = 0;
              dword_dd668 = dword_dd668 & 0xfffffff7;
            }
            else {
              if (0x40 < local_34) {
                if (local_34 < 0x80) goto LAB_00073361;
                if (local_34 < 0x81) {
                  dword_dd658 = 2;
                  dword_dd668 = dword_dd668 | 8;
                  goto LAB_00073294;
                }
                if (local_34 != 0x100) goto LAB_00073361;
                iVar2 = *piVar10;
                iVar5 = ((int)local_2c + (-0x13 - dword_d1108)) * iVar2;
                iVar3 = iVar5 >> 0x1f;
                iVar5 = (int)((iVar5 + iVar3 * -0x20) - (uint)(iVar3 << 4 < 0)) >> 5;
                if (iVar5 < piVar10[2]) {
                  if (iVar5 < 3) {
                    piVar10[2] = 0;
                    piVar10[3] = 5;
                  }
                  else {
LAB_00073257:
                    piVar10[2] = iVar5 + -3;
                    piVar10[3] = iVar5 + 2;
                  }
                }
                else {
                  if (iVar5 <= piVar10[3]) goto LAB_00073395;
                  if (iVar5 + 3 <= iVar2) goto LAB_00073257;
                  piVar10[2] = iVar2 + -6;
                  piVar10[3] = *piVar10 + -1;
                }
                goto LAB_000732a6;
              }
              dword_dd658 = 1;
              dword_dd668 = dword_dd668 & 0xfffffff7;
            }
LAB_00073294:
            local_38 = (undefined4 **)0x73299;
            database_type_menu();
            piVar10 = (int *)(&off_d1184)[dword_dd658];
          }
LAB_000732a6:
          local_38 = (undefined4 **)0x732ad;
          sub_72ac6(piVar10);
        }
      }
    }
  }
  else if ((local_20 != local_2c) || (local_2c != local_24)) {
    local_38 = (undefined4 **)0x72fbf;
    iVar2 = sub_72a5c(local_28,local_2c,&local_34);
    if ((iVar2 == 0) || (local_34 != 8)) {
      iStack_1c = 0;
    }
    else if (iStack_1c == 0) {
      iStack_1c = 1;
    }
    else {
      iVar2 = *piVar10 * ((int)local_24 + (-0x13 - dword_d1108));
      iVar5 = iVar2 >> 0x1f;
      iVar5 = (int)((iVar2 + iVar5 * -0x20) - (uint)(iVar5 << 4 < 0)) >> 5;
      iVar2 = piVar10[3];
      if (((local_24 != local_2c) && (iVar3 = piVar10[2], iVar3 <= iVar5)) && (iVar5 <= iVar2)) {
        if ((int)local_24 < (int)local_2c) {
          iVar5 = ((int)local_2c - (int)local_24) * *piVar10;
          iVar6 = iVar5 >> 0x1f;
          iVar5 = (int)((iVar5 + iVar6 * -0x20) - (uint)(iVar6 << 4 < 0)) >> 5;
          if (iVar5 + iVar2 < *piVar10) {
            piVar10[2] = iVar3 + iVar5;
            piVar10[3] = piVar10[3] + iVar5;
          }
          else {
            piVar10[3] = *piVar10 + -1;
            piVar10[2] = *piVar10 + -6;
          }
        }
        else if ((int)local_2c < (int)local_24) {
          iVar5 = ((int)local_24 - (int)local_2c) * *piVar10;
          iVar6 = iVar5 >> 0x1f;
          iVar5 = (int)((iVar5 + iVar6 * -0x20) - (uint)(iVar6 << 4 < 0)) >> 5;
          iVar3 = iVar3 - iVar5;
          if (iVar3 < 0) {
            piVar10[2] = 0;
            piVar10[3] = 5;
          }
          else {
            piVar10[2] = iVar3;
            piVar10[3] = piVar10[3] - iVar5;
          }
        }
        if (iVar2 != piVar10[3]) goto LAB_000732a6;
      }
    }
  }
LAB_00073395:
  local_38 = (undefined4 **)local_2c;
  grabshape(ppuVar1,local_28 + -1);
  goto LAB_00072f4f;
code_r0x00072ef6:
  if ((local_28 != local_20) || (local_2c != local_24)) {
    local_38 = (undefined4 **)0x72f0f;
    setdefaultscreen();
    local_38 = (undefined4 **)local_24;
    drawshape(ppuVar1,local_20 + -1);
    local_38 = (undefined4 **)local_2c;
    grabshape(ppuVar1,local_28 + -1);
LAB_00072f4f:
    local_38 = (undefined4 **)local_2c;
    drawshape_remap(pointer_shapes,local_28 + -1);
    local_20 = local_28;
    local_24 = local_2c;
  }
  goto LAB_00072ec6;
}


// ================================================================================================
// sub_733c4 @ 0x733c4 [__watcall]
// ================================================================================================

void __watcall sub_733c4(void)

{
  char acStackY_1c [16];
  
  __CHK(0x20);
  acStackY_1c[0] = '\0';
  acStackY_1c[1] = '\0';
  acStackY_1c[2] = '\0';
  acStackY_1c[3] = '\0';
  acStackY_1c[4] = '\0';
  acStackY_1c[5] = '\0';
  acStackY_1c[6] = '\0';
  acStackY_1c[7] = '\0';
  acStackY_1c[8] = '\0';
  acStackY_1c[9] = '\0';
  acStackY_1c[10] = '\0';
  acStackY_1c[0xb] = '\0';
  acStackY_1c[0xc] = 0;
  if (dword_dd658 == 0) {
    unk_ec7c0._0_1_ = aCurrent_c3092[0];
    unk_ec7c0._1_1_ = aCurrent_c3092[1];
    unk_ec7c0._2_1_ = aCurrent_c3092[2];
    unk_ec7c0._3_1_ = aCurrent_c3092[3];
    DAT_000ec7c4._0_1_ = aCurrent_c3092[4];
    DAT_000ec7c4._1_1_ = aCurrent_c3092[5];
    DAT_000ec7c4._2_1_ = aCurrent_c3092[6];
    DAT_000ec7c4._3_1_ = aCurrent_c3092[7];
  }
  else if (dword_dd658 < 2) {
    unk_ec7c0._0_1_ = aOriginal[0];
    unk_ec7c0._1_1_ = aOriginal[1];
    unk_ec7c0._2_1_ = aOriginal[2];
    unk_ec7c0._3_1_ = aOriginal[3];
    DAT_000ec7c4._0_1_ = aOriginal[4];
    DAT_000ec7c4._1_1_ = aOriginal[5];
    DAT_000ec7c4._2_1_ = aOriginal[6];
    DAT_000ec7c4._3_1_ = aOriginal[7];
    DAT_000ec7c8 = aOriginal[8];
  }
  else {
    if (dword_dd658 != 2) {
      return;
    }
    strcpy(acStackY_1c,(char *)(&unk_ec720)[dword_ec714]);
    strcpy((char *)&unk_ec7c0,acStackY_1c);
    strcat(acStackY_1c,(char *)&aDBX_c30c3);
  }
  sub_7345b();
  return;
}


// ================================================================================================
// sub_7345b @ 0x7345b [__cdecl]
// ================================================================================================

void sub_7345b(void)

{
  undefined auStack_30 [32];
  
  __CHK(0x3c);
  sub_6ca8f();
  make_path(auStack_30);
  dword_d07bb = loadfile(auStack_30,0x20);
  dword_d07d3 = filesize(auStack_30);
  make_path(auStack_30);
  dword_d07bf = loadfile(auStack_30,0x20);
  dword_d07d7 = filesize(auStack_30);
  make_path(auStack_30);
  dword_d07c3 = loadfile(auStack_30,0x20);
  dword_d07db = filesize(auStack_30);
  make_path(auStack_30);
  dword_d07c7 = loadfile(auStack_30,0x20);
  dword_d07df = filesize(auStack_30);
  make_path(auStack_30);
  dword_d07cb = loadfile(auStack_30,0x20);
  dword_d07e3 = filesize(auStack_30);
  make_path(auStack_30);
  dword_d07cf = loadfile(auStack_30,0x20);
  dword_d07e7 = filesize(auStack_30);
  dword_ebc68 = 0;
  return;
}


// ================================================================================================
// database_dbx_check @ 0x735c3 [__watcall]
// ================================================================================================

longlong __watcall database_dbx_check(int *param_1,uint unaff_EDX)

{
  int iVar1;
  int iVar2;
  undefined auStack_58 [21];
  byte bStack_43;
  undefined auStack_3a [14];
  char acStack_2c [16];
  undefined4 local_1c;
  undefined4 uStack_18;
  
  __CHK(0x70);
  uStack_18 = 0x140;
  local_1c = 0xf0;
  dword_d11b6 = param_1[param_1[1] + 4];
  iVar2 = message_dialog(0xffffffff,0xffffffff,&off_d11b2,2,&unk_d2b38,2,&uStack_18,&local_1c,
                         0xffffffff);
  if (iVar2 == 1) {
    strcpy(acStack_2c,(char *)param_1[param_1[1] + 4]);
    strcat(acStack_2c,(char *)&aDBX_c30c3);
    iVar2 = _dos_findfirst(acStack_2c,0x10,auStack_58);
    if (iVar2 == 0) {
      if ((bStack_43 & 0x10) != 0) {
        sub_14442(auStack_3a);
      }
      iVar2 = *param_1;
      *param_1 = iVar2 + -1;
      if (iVar2 + -1 == 0) {
        dword_dd668 = dword_dd668 & 0xffffff77;
        if (dword_ec6b8 == 0) {
          if (dword_ec768 == 0) {
            dword_dd658 = 0xffffffff;
            dword_dd668 = 0x10;
          }
          else {
            dword_dd658 = 1;
          }
        }
        else {
          dword_dd658 = 0;
        }
        database_type_menu();
      }
      else {
        for (iVar2 = param_1[1]; iVar1 = *param_1, iVar2 < iVar1; iVar2 = iVar2 + 1) {
          param_1[iVar2 + 4] = param_1[iVar2 + 5];
        }
        if (iVar1 < 6) {
          param_1[3] = iVar1 + -1;
          param_1[2] = 0;
        }
        else if (iVar1 == param_1[3]) {
          param_1[2] = param_1[2] + -1;
          param_1[3] = param_1[3] + -1;
        }
        if (param_1[1] == *param_1) {
          param_1[1] = param_1[1] + -1;
        }
      }
    }
  }
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// sub_73703 @ 0x73703 [__watcall]
// ================================================================================================

void __watcall sub_73703(void)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  byte bVar6;
  undefined4 *puVar7;
  
  bVar6 = 0;
  __CHK(0x2c);
  scan_database_files();
  puVar1 = (undefined4 *)allocmem(&aBuf_c30c8,0xbc03,0x20);
  puVar4 = puVar1 + (uint)bVar6 * -2 + 1;
  puVar7 = pointer_shapes + (uint)bVar6 * -2 + 1;
  *puVar1 = *pointer_shapes;
  puVar5 = puVar4 + (uint)bVar6 * -2 + 1;
  puVar3 = puVar7 + (uint)bVar6 * -2 + 1;
  *puVar4 = *puVar7;
  *puVar5 = *puVar3;
  puVar5[(uint)bVar6 * -2 + 1] = puVar3[(uint)bVar6 * -2 + 1];
  *(undefined *)(puVar5 + (uint)bVar6 * -2 + 1 + (uint)bVar6 * -2 + 1) =
       *(undefined *)(puVar3 + (uint)bVar6 * -2 + 1 + (uint)bVar6 * -2 + 1);
  *(undefined2 *)(puVar1 + 1) = 0xf3;
  *(undefined2 *)((int)puVar1 + 6) = 0xc6;
  puVar7 = puVar1;
  grabshape(puVar1,10,0x13,puVar1);
  database_buttons();
  database_dialog();
  database_type_menu();
  iVar2 = database_select_screen();
  if (iVar2 == 0) {
    drawshape2(puVar1,10,0x13);
  }
  freemem(dword_c6f78);
  dword_c6f78 = 0;
  freemem(puVar7);
  return;
}


// ================================================================================================
// edit_lines_screen_a @ 0x737e1 [__watcall]
// ================================================================================================

void __watcall
edit_lines_screen_a(undefined param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX
                   )

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined *puVar3;
  undefined auStack_3c [32];
  
  __CHK(0x50);
  uVar1 = allocmem(&aPal_c30cc,0x300,0x20);
  getpalette(0,0x100,uVar1);
  fade_palette(1,uVar1,0x10);
  freemem(uVar1);
  if ((sound_enabled != '\0') && (dword_c721d != 0)) {
    sound_fade(dword_d2431,3,0x32);
  }
  sub_479e9();
  setscreen(dword_ea2b4);
  dword_d0b16 = 0xc1;
  dword_d0b1a = 0xc0;
  dword_d0b1e = 0xc1;
  dword_d0b22 = 0xc2;
  dword_d0b26 = 0xc3;
  dword_d0b2a = 0xc2;
  byte_ec7e0 = param_1;
  setmousepos(0x140,0xf0);
  setclip(0,0x280,0,0x1e0);
  puVar3 = install_path;
  if (byte_ed8b4 != '\x01') {
    puVar3 = (undefined *)0x0;
  }
  make_path(auStack_3c,puVar3,aLineditp_c30d0,0);
  uVar1 = loadshapes(auStack_3c,0);
  uVar2 = locateshape(uVar1,&aShrt_c30d9);
  draw_lines_screen(param_1,uVar2,0,unaff_EBX,unaff_ECX);
  wait_sprite_fade();
  setdefaultscreen();
  drawshape_home(*(undefined4 *)(dword_ea2b4 + 0x2c));
  edit_lines_screen(unaff_EDX,uVar2,param_1,0,unaff_EBX,unaff_ECX,uVar1);
  freemem(uVar1);
  dword_d0b16 = 0x41;
  dword_d0b1a = 0x40;
  dword_d0b1e = 0x42;
  dword_d0b22 = 0x41;
  dword_d0b26 = 0x40;
  dword_d0b2a = 0x42;
  return;
}


// ================================================================================================
// sub_739b6 @ 0x739b6 [__watcall]
// ================================================================================================

byte __watcall sub_739b6(char param_1,byte unaff_DL)

{
  byte bVar1;
  byte bVar2;
  byte local_10;
  
  __CHK(0x14);
  bVar1 = 0;
  while (bVar1 < 0x1c) {
    bVar2 = bVar1;
    if ((&unk_ea992)[(uint)bVar1 * 0x1b + (uint)unaff_DL * 0x2f4] == param_1) {
      bVar2 = 0x1c;
      local_10 = bVar1;
    }
    bVar1 = bVar2 + 1;
  }
  return local_10;
}


// ================================================================================================
// edit_lines_screen @ 0x73a18 [__watcall]
// ================================================================================================

undefined4 __watcall
edit_lines_screen(int param_1,int **param_2,byte unaff_BL,undefined4 param_4,int *param_5,
                 undefined4 param_6,undefined4 param_7)

{
  undefined uVar1;
  char cVar2;
  code *pcVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  int iVar8;
  byte bVar9;
  int **ppiVar10;
  int *piVar11;
  int iVar12;
  int *piVar13;
  int **ppiVar14;
  undefined4 *puVar15;
  int iVar16;
  uint uVar17;
  undefined4 uVar18;
  undefined *puVar19;
  undefined *puVar20;
  undefined4 *puVar21;
  int iVar22;
  undefined4 *puVar23;
  undefined4 *puVar24;
  byte bVar25;
  ulonglong uVar26;
  byte abStack_134 [12];
  byte abStack_128 [6];
  byte abStack_122 [10];
  byte abStack_118 [8];
  byte abStack_110 [12];
  int local_104 [8];
  undefined auStack_e4 [32];
  undefined auStack_c4 [32];
  int local_a4 [4];
  int *local_94;
  int local_90;
  undefined4 local_8c;
  undefined4 local_88;
  int local_84 [9];
  int local_60;
  int local_5c;
  int local_58;
  int local_54;
  int local_50;
  int *local_4c;
  int **local_48;
  int local_44;
  undefined4 *local_40;
  void *local_3c;
  int local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  int local_28;
  int local_24;
  undefined4 *local_20;
  int local_1c;
  undefined local_18;
  byte local_14;
  undefined local_10;
  
  bVar25 = 0;
  __CHK(0x158);
  local_1c = 0;
  local_60 = -1;
  local_58 = -1;
  local_30 = 0xc0;
  local_34 = 0xc1;
  local_2c = 0xc2;
  local_14 = unaff_BL;
  local_40 = (undefined4 *)locateshape(param_7,&aPntr_c30de);
  local_94 = param_5;
  local_84[4] = param_6;
  local_88 = 0;
  local_8c = 0;
  local_90 = 0;
  local_84[3] = 0;
  local_84[2] = 0;
  local_84[1] = 0;
  local_84[0] = 0;
  local_a4[3] = 0;
  local_a4[2] = 0;
  local_a4[1] = 0;
  local_a4[0] = 0;
  local_104[1] = 0;
  local_104[0] = 0;
  funcptr_d056c = (undefined *)0x0;
  funcptr_d058c = (undefined *)0x0;
  local_20 = (undefined4 *)
             allocmem(aPointer_c30e3,
                      ((*(int *)((int)local_40 + 2) >> 0x10) + 1) * (((int)local_40[1] >> 0x10) + 1)
                      + 0x11,0x20);
  puVar20 = &stack0xfffffec4;
  puVar23 = local_20 + (uint)bVar25 * -2 + 1;
  puVar15 = local_40 + (uint)bVar25 * -2 + 1;
  *local_20 = *local_40;
  puVar24 = puVar23 + (uint)bVar25 * -2 + 1;
  puVar21 = puVar15 + (uint)bVar25 * -2 + 1;
  *puVar23 = *puVar15;
  *puVar24 = *puVar21;
  puVar24[(uint)bVar25 * -2 + 1] = puVar21[(uint)bVar25 * -2 + 1];
  *(undefined *)(puVar24 + (uint)bVar25 * -2 + 1 + (uint)bVar25 * -2 + 1) =
       *(undefined *)(puVar21 + (uint)bVar25 * -2 + 1 + (uint)bVar25 * -2 + 1);
  *(short *)(local_20 + 1) = *(short *)(local_40 + 1) + 1;
  *(short *)((int)local_20 + 6) = *(short *)((int)local_40 + 6) + 1;
  ppiVar10 = (int **)((*local_94 + local_94[2]) / 2);
  piVar11 = (int *)((local_94[1] + local_94[3]) / 2);
  local_44 = 0;
  local_4c = piVar11;
  local_48 = ppiVar10;
  do {
    bVar9 = *(byte *)(param_1 + local_44);
    if (bVar9 != 100) {
      uVar17 = (uint)local_14;
      bVar9 = sub_739b6(bVar9,uVar17);
      bVar9 = (&unk_ea991)[(uint)bVar9 * 0x1b + uVar17 * 0x2f4];
    }
    abStack_134[local_44] = bVar9;
    local_44 = local_44 + 1;
  } while (local_44 < 0x28);
  local_44 = 0;
  do {
    uVar17 = (uint)local_14;
    bVar9 = sub_739b6(*(undefined *)(param_1 + local_44 + 0x28),uVar17);
    if ((*(char *)(param_1 + local_44 + 0x28) != 'd') &&
       (iVar12 = (uint)bVar9 * 0x1b + uVar17 * 0x2f4, (&unk_ea993)[iVar12] == '\x03')) {
      (&unk_ea993)[iVar12] = 2;
    }
    local_44 = local_44 + 1;
  } while (local_44 < 8);
  local_3c = (void *)allocmem(&aPal_c30cc,0x300,0x20);
  puVar19 = install_path;
  if (byte_ed85a != '\x01') {
    puVar19 = (undefined *)0x0;
  }
  make_path(auStack_e4,puVar19,aEmbpal_c30eb,0);
  local_40 = (undefined4 *)loadshapes(auStack_e4,0);
  iVar12 = locateshape(local_40,&aPal_c30f2);
  memcpy(local_3c,(void *)(iVar12 + 0x10),0x300);
  freemem(local_40);
  uVar17 = (uint)local_14;
  load_homepals(uVar17,param_7,local_3c);
  local_18 = (&unk_d1238)[(byte)(&unk_d11bc)[(uint)(byte)(&byte_d079e)[uVar17] * 4]];
  local_10 = byte_d12de;
  sub_75046(abStack_134,param_2,uVar17);
  puVar19 = install_path;
  if (byte_ed9e7 != '\x01') {
    puVar19 = (undefined *)0x0;
  }
  make_path(auStack_e4,puVar19,aLelogo,0);
  local_40 = (undefined4 *)loadshapes(auStack_e4,0);
  iVar12 = locateshape(local_40,&aPal_c30f2);
  memcpy((void *)((int)local_3c + 0x25e),(void *)(iVar12 + 0x26e),0x93);
  freemem(local_40);
  fade_palette(0,local_3c,0x10);
  if ((int)piVar11 < 0x20) {
    piVar13 = (int *)0x0;
  }
  else {
    piVar13 = piVar11 + -8;
  }
  if ((int)ppiVar10 < 0x1c) {
    ppiVar14 = (int **)0x0;
  }
  else {
    ppiVar14 = ppiVar10 + -7;
  }
  grabshape(dword_ebe9c,ppiVar14,piVar13);
  if ((int)piVar11 < 0x20) {
    piVar13 = (int *)0x0;
  }
  else {
    piVar13 = piVar11 + -8;
  }
  if ((int)ppiVar10 < 0x1c) {
    ppiVar14 = (int **)0x0;
  }
  else {
    ppiVar14 = ppiVar10 + -7;
  }
  grabshape(local_20,ppiVar14,piVar13);
  ppiVar14 = pointer_shapes;
  drawshape_trans(pointer_shapes,(int)ppiVar10 + -3,piVar11);
  setmouselimits(0,0,0x280,0x1e0);
  setmousepos(ppiVar10,piVar11);
  getmouse(&local_44,&local_44,&local_44);
  uVar26 = event_queue_reset();
LAB_00073f22:
  uVar17 = 0;
  do {
    *(undefined4 *)(puVar20 + -4) = 0x73f29;
    uVar26 = event_queue_pop((int)uVar26,(int)(uVar26 >> 0x20),ppiVar14);
    if ((int)uVar26 == 0) break;
    ppiVar14 = &local_4c;
    *(undefined4 *)(puVar20 + -4) = 0x73f39;
    uVar26 = (*ui_poll_callback)();
    uVar17 = (uint)uVar26;
  } while ((uVar26 & 2) == 0);
  if ((uVar17 & 2) == 0) goto code_r0x00073f44;
  *(int **)(puVar20 + -4) = &local_54;
  *(int **)(puVar20 + -8) = &local_50;
  *(int **)(puVar20 + -0xc) = local_104;
  *(int **)(puVar20 + -0x10) = local_84 + 4;
  *(undefined4 *)(puVar20 + -0x14) = 0x73f7f;
  iVar12 = hit_test_menus(local_48,local_4c,&local_94,local_1c);
  piVar13 = piVar11 + -8;
  if (iVar12 == 0) {
    if ((int)piVar11 < 0x20) {
      piVar13 = (int *)0x0;
    }
    *(int **)(puVar20 + -4) = piVar13;
    if ((int)ppiVar10 < 0x1c) {
      ppiVar10 = (int **)0x0;
    }
    else {
      ppiVar10 = ppiVar10 + -7;
    }
    *(int ***)(puVar20 + -8) = ppiVar10;
    *(undefined4 **)(puVar20 + -0xc) = local_20;
    *(undefined4 *)(puVar20 + -0x10) = 0x74404;
    drawshape();
    *(undefined4 *)(puVar20 + -4) = 0x74415;
    iVar12 = sub_77f6f(local_48,local_4c,&local_58);
    if (iVar12 != 0) {
      for (local_44 = 3; -1 < local_44; local_44 = local_44 + -1) {
        iVar12 = local_84[local_44];
        if (iVar12 != 0) {
          *(int *)(puVar20 + -4) = local_104[local_44 * 2 + 1];
          *(int *)(puVar20 + -8) = local_104[local_44 * 2];
          *(int *)(puVar20 + -0xc) = iVar12;
          *(undefined4 *)(puVar20 + -0x10) = 0x74443;
          drawshape();
          iVar12 = local_44;
          local_104[local_44 * 2 + 1] = 0;
          local_104[iVar12 * 2] = 0;
          *(int *)(puVar20 + -4) = local_84[iVar12];
          *(undefined4 *)(puVar20 + -8) = 0x7445d;
          freemem();
        }
      }
      local_1c = 0;
      local_88 = 0;
      local_8c = 0;
      local_90 = 0;
      local_84[2] = 0;
      local_84[1] = 0;
      local_84[0] = 0;
      local_a4[3] = 0;
      local_a4[2] = 0;
      local_a4[1] = 0;
      local_84[7] = 0;
      local_84[6] = 0;
      local_84[5] = 0;
      if (((local_58 < 100) && (local_60 != -1)) &&
         (uVar17 = (uint)local_14, (&unk_ea993)[local_60 * 0x1b + uVar17 * 0x2f4] != '\x02')) {
        *(undefined4 *)(puVar20 + -4) = 0xc1;
        *(undefined4 *)(puVar20 + -8) = 0xc0;
        *(undefined4 *)(puVar20 + -0xc) = 0x744e9;
        settextpos();
        iVar12 = local_60 * 0x1b + uVar17 * 0x2f4;
        if (local_58 < 0xc) {
          cVar2 = (&unk_ea990)[iVar12];
          if (((cVar2 == 'C') || (cVar2 == 'L')) || (cVar2 == 'R')) {
            local_44 = local_58 / 3;
            iVar12 = 0;
            do {
              iVar16 = local_44 * 3 + iVar12;
              if (abStack_134[iVar16] == (&unk_ea991)[(uint)local_14 * 0x2f4 + local_60 * 0x1b]) {
                abStack_134[iVar16] = 100;
              }
              iVar12 = iVar12 + 1;
            } while (iVar12 < 3);
            abStack_134[local_58 % 3 + local_44 * 3] =
                 (&unk_ea991)[(uint)local_14 * 0x2f4 + local_60 * 0x1b];
            iVar12 = 0;
            do {
              iVar16 = local_44 * 3 + iVar12;
              if (abStack_134[iVar16] < 100) {
                bVar9 = abStack_134[iVar16];
                *(undefined4 *)(puVar20 + -4) = 0x7460d;
                sub_7a099(&unk_d1238,bVar9,local_18,local_10);
              }
              else {
                iVar16 = 0;
                do {
                  (&unk_d1238)[iVar16] = local_10;
                  iVar16 = iVar16 + 1;
                } while (iVar16 < 0x90);
                iVar16 = 0xc0;
                do {
                  (&unk_d1238)[iVar16] = local_10;
                  iVar16 = iVar16 + 1;
                } while (iVar16 < 0xf0);
              }
              *(undefined1 **)(puVar20 + -4) = &unk_d1238;
              *(undefined4 *)(puVar20 + -8) = 0x74642;
              setremaptable();
              iVar16 = local_44 * 3 + iVar12;
              *(undefined4 *)(puVar20 + -4) = (&unk_d133c)[iVar16 * 2];
              *(undefined4 *)(puVar20 + -8) = (&unk_d1338)[iVar16 * 2];
              *(int ***)(puVar20 + -0xc) = param_2;
              *(undefined4 *)(puVar20 + -0x10) = 0x7466d;
              drawshape2_trans();
              iVar12 = iVar12 + 1;
            } while (iVar12 < 3);
          }
        }
        else if (local_58 < 0x12) {
          if ((&unk_ea990)[iVar12] == 'D') {
            local_44 = (local_58 + -0xc) / 2;
            iVar12 = 0;
            do {
              iVar16 = local_44 * 2 + iVar12;
              if (abStack_128[iVar16] == (&unk_ea991)[(uint)local_14 * 0x2f4 + local_60 * 0x1b]) {
                abStack_128[iVar16] = 100;
              }
              iVar12 = iVar12 + 1;
            } while (iVar12 < 2);
            abStack_128[(local_58 + -0xc) % 2 + local_44 * 2] =
                 (&unk_ea991)[local_60 * 0x1b + (uint)local_14 * 0x2f4];
            iVar12 = 0;
            do {
              iVar16 = local_44 * 2 + iVar12;
              if (abStack_128[iVar16] < 100) {
                bVar9 = abStack_128[iVar16];
                *(undefined4 *)(puVar20 + -4) = 0x74774;
                sub_7a099(&unk_d1238,bVar9,local_18,local_10);
              }
              else {
                iVar16 = 0;
                do {
                  (&unk_d1238)[iVar16] = local_10;
                  iVar16 = iVar16 + 1;
                } while (iVar16 < 0x90);
                iVar16 = 0xc0;
                do {
                  (&unk_d1238)[iVar16] = local_10;
                  iVar16 = iVar16 + 1;
                } while (iVar16 < 0xf0);
              }
              *(undefined1 **)(puVar20 + -4) = &unk_d1238;
              *(undefined4 *)(puVar20 + -8) = 0x747a9;
              setremaptable();
              iVar16 = local_44 * 2 + iVar12;
              *(undefined4 *)(puVar20 + -4) = *(undefined4 *)(&unk_d139c + iVar16 * 8);
              *(undefined4 *)(puVar20 + -8) = *(undefined4 *)(&unk_d1398 + iVar16 * 8);
              *(int ***)(puVar20 + -0xc) = param_2;
              *(undefined4 *)(puVar20 + -0x10) = 0x747cf;
              drawshape2_trans();
              iVar12 = iVar12 + 1;
            } while (iVar12 < 2);
          }
        }
        else if (local_58 < 0x1c) {
          if ((&unk_ea990)[iVar12] != 'G') {
            local_44 = (local_58 + -0x12) / 5;
            iVar12 = 0;
            do {
              iVar16 = local_44 * 5 + iVar12;
              if (abStack_122[iVar16] == (&unk_ea991)[(uint)local_14 * 0x2f4 + local_60 * 0x1b]) {
                abStack_122[iVar16] = 100;
              }
              iVar12 = iVar12 + 1;
            } while (iVar12 < 5);
            abStack_122[(local_58 + -0x12) % 5 + local_44 * 5] =
                 (&unk_ea991)[(uint)local_14 * 0x2f4 + local_60 * 0x1b];
            iVar12 = 0;
            do {
              iVar16 = local_44 * 5 + iVar12;
              if (abStack_122[iVar16] < 100) {
                bVar9 = abStack_122[iVar16];
                *(undefined4 *)(puVar20 + -4) = 0x748e4;
                sub_7a099(&unk_d1238,bVar9,local_18,local_10);
              }
              else {
                iVar16 = 0;
                do {
                  (&unk_d1238)[iVar16] = local_10;
                  iVar16 = iVar16 + 1;
                } while (iVar16 < 0x90);
                iVar16 = 0xc0;
                do {
                  (&unk_d1238)[iVar16] = local_10;
                  iVar16 = iVar16 + 1;
                } while (iVar16 < 0xf0);
              }
              *(undefined1 **)(puVar20 + -4) = &unk_d1238;
              *(undefined4 *)(puVar20 + -8) = 0x74919;
              setremaptable();
              iVar16 = local_44 * 5 + iVar12;
              *(undefined4 *)(puVar20 + -4) = *(undefined4 *)(&unk_d13cc + iVar16 * 8);
              *(undefined4 *)(puVar20 + -8) = *(undefined4 *)(&unk_d13c8 + iVar16 * 8);
              *(int ***)(puVar20 + -0xc) = param_2;
              *(undefined4 *)(puVar20 + -0x10) = 0x74944;
              drawshape2_trans();
              iVar12 = iVar12 + 1;
            } while (iVar12 < 5);
          }
        }
        else if (local_58 < 0x24) {
          if ((&unk_ea990)[iVar12] != 'G') {
            iVar12 = local_58 + -0x1c >> 0x1f;
            local_44 = (int)((local_58 + -0x1c + iVar12 * -4) - (uint)(iVar12 << 1 < 0)) >> 2;
            iVar12 = 0;
            do {
              iVar16 = local_44 * 4 + iVar12;
              if (abStack_118[iVar16] == (&unk_ea991)[(uint)local_14 * 0x2f4 + local_60 * 0x1b]) {
                abStack_118[iVar16] = 100;
              }
              iVar12 = iVar12 + 1;
            } while (iVar12 < 4);
            abStack_118[(local_58 + -0x1c) % 4 + local_44 * 4] =
                 (&unk_ea991)[local_60 * 0x1b + (uint)local_14 * 0x2f4];
            iVar12 = 0;
            do {
              iVar16 = local_44 * 4 + iVar12;
              if (abStack_118[iVar16] < 100) {
                bVar9 = abStack_118[iVar16];
                *(undefined4 *)(puVar20 + -4) = 0x74a4f;
                sub_7a099(&unk_d1238,bVar9,local_18,local_10);
              }
              else {
                iVar16 = 0;
                do {
                  (&unk_d1238)[iVar16] = local_10;
                  iVar16 = iVar16 + 1;
                } while (iVar16 < 0x90);
                iVar16 = 0xc0;
                do {
                  (&unk_d1238)[iVar16] = local_10;
                  iVar16 = iVar16 + 1;
                } while (iVar16 < 0xf0);
              }
              *(undefined1 **)(puVar20 + -4) = &unk_d1238;
              *(undefined4 *)(puVar20 + -8) = 0x74a84;
              setremaptable();
              iVar16 = local_44 * 4 + iVar12;
              *(undefined4 *)(puVar20 + -4) = *(undefined4 *)(&unk_d141c + iVar16 * 8);
              *(undefined4 *)(puVar20 + -8) = *(undefined4 *)(&unk_d1418 + iVar16 * 8);
              *(int ***)(puVar20 + -0xc) = param_2;
              *(undefined4 *)(puVar20 + -0x10) = 0x74aab;
              drawshape2_trans();
              iVar12 = iVar12 + 1;
            } while (iVar12 < 4);
          }
        }
        else if (local_58 < 0x26) {
          if ((&unk_ea990)[iVar12] == 'G') {
            iVar12 = 0;
            do {
              if (abStack_110[iVar12] == (&unk_ea991)[local_60 * 0x1b + (uint)local_14 * 0x2f4]) {
                abStack_110[iVar12] = 100;
              }
              iVar12 = iVar12 + 1;
            } while (iVar12 < 2);
            abStack_134[local_58] = (&unk_ea991)[local_60 * 0x1b + (uint)local_14 * 0x2f4];
            iVar12 = 0;
            do {
              if (abStack_110[iVar12] < 100) {
                bVar9 = abStack_110[iVar12];
                *(undefined4 *)(puVar20 + -4) = 0x74b7a;
                sub_7a099(&unk_d1238,bVar9,local_18,local_10);
              }
              else {
                iVar16 = 0;
                do {
                  (&unk_d1238)[iVar16] = local_10;
                  iVar16 = iVar16 + 1;
                } while (iVar16 < 0x90);
                iVar16 = 0xc0;
                do {
                  (&unk_d1238)[iVar16] = local_10;
                  iVar16 = iVar16 + 1;
                } while (iVar16 < 0xf0);
              }
              *(undefined1 **)(puVar20 + -4) = &unk_d1238;
              *(undefined4 *)(puVar20 + -8) = 0x74baf;
              setremaptable();
              *(undefined4 *)(puVar20 + -4) = (&unk_d145c)[iVar12 * 2];
              *(undefined4 *)(puVar20 + -8) = (&unk_d1458)[iVar12 * 2];
              *(int ***)(puVar20 + -0xc) = param_2;
              *(undefined4 *)(puVar20 + -0x10) = 0x74bce;
              drawshape2_trans();
              iVar12 = iVar12 + 1;
            } while (iVar12 < 2);
          }
        }
        else if ((&unk_ea990)[iVar12] != 'G') {
          iVar12 = 0;
          do {
            if (abStack_110[iVar12 + 2] == (&unk_ea991)[local_60 * 0x1b + (uint)local_14 * 0x2f4]) {
              abStack_110[iVar12 + 2] = 100;
            }
            iVar12 = iVar12 + 1;
          } while (iVar12 < 2);
          abStack_134[local_58] = (&unk_ea991)[local_60 * 0x1b + (uint)local_14 * 0x2f4];
          iVar12 = 0;
          do {
            if (abStack_110[iVar12 + 2] < 100) {
              bVar9 = abStack_110[iVar12 + 2];
              *(undefined4 *)(puVar20 + -4) = 0x74c95;
              sub_7a099(&unk_d1238,bVar9,local_18,local_10);
            }
            else {
              iVar16 = 0;
              do {
                (&unk_d1238)[iVar16] = local_10;
                iVar16 = iVar16 + 1;
              } while (iVar16 < 0x90);
              iVar16 = 0xc0;
              do {
                (&unk_d1238)[iVar16] = local_10;
                iVar16 = iVar16 + 1;
              } while (iVar16 < 0xf0);
            }
            *(undefined1 **)(puVar20 + -4) = &unk_d1238;
            *(undefined4 *)(puVar20 + -8) = 0x74cca;
            setremaptable();
            *(undefined4 *)(puVar20 + -4) = (&unk_d146c)[iVar12 * 2];
            *(undefined4 *)(puVar20 + -8) = (&unk_d1468)[iVar12 * 2];
            *(int ***)(puVar20 + -0xc) = param_2;
            *(undefined4 *)(puVar20 + -0x10) = 0x74ce9;
            drawshape2_trans();
            iVar12 = iVar12 + 1;
          } while (iVar12 < 2);
        }
      }
      else if (99 < local_58) {
        local_58 = local_58 + -100;
        cVar2 = (&unk_ea993)[local_58 * 0x1b + (uint)local_14 * 0x2f4];
        if ((cVar2 != '\0') && (((cVar2 == '\x04' || (cVar2 == '\x03')) || (cVar2 == '\x02')))) {
          if (local_60 != -1) {
            if ((&unk_ea993)[local_60 * 0x1b + (uint)local_14 * 0x2f4] == '\x02') {
              *(undefined4 *)(puVar20 + -4) = 0xc1;
              *(undefined4 *)(puVar20 + -8) = 0xfc;
            }
            else {
              *(undefined4 *)(puVar20 + -4) = 0xc1;
              *(undefined4 *)(puVar20 + -8) = 0xc3;
            }
            *(undefined4 *)(puVar20 + -0xc) = 0x74da6;
            settextpos();
            iVar16 = (uint)local_14 * 0x2f4;
            iVar12 = local_60 * 0x1b;
            *(int *)(puVar20 + -4) = iVar16 + 0xea998 + iVar12;
            *(uint *)(puVar20 + -8) = (uint)(byte)(&unk_ea991)[iVar12 + iVar16];
            *(uint *)(puVar20 + -0xc) = (uint)(byte)(&unk_ea990)[iVar12 + iVar16];
            *(char **)(puVar20 + -0x10) = aC2dS_c3107;
            *(undefined **)(puVar20 + -0x14) = auStack_c4;
            *(undefined4 *)(puVar20 + -0x18) = 0x74dff;
            sprintf(*(char **)(puVar20 + -0x14),*(char **)(puVar20 + -0x10));
            *(undefined4 *)(puVar20 + -4) = 0x74e21;
            sub_76771(0x1fa,local_60 * 0xd + 0x16,auStack_c4);
          }
          local_60 = local_58;
          funcptr_d056c = sub_75868;
          funcptr_d058c = sub_75770;
          if ((&unk_ea993)[local_58 * 0x1b + (uint)local_14 * 0x2f4] == '\x02') {
            *(undefined4 *)(puVar20 + -4) = 0xc1;
            *(undefined4 *)(puVar20 + -8) = 0xfd;
          }
          else {
            *(undefined4 *)(puVar20 + -4) = 0xc1;
            *(undefined4 *)(puVar20 + -8) = 0xc0;
          }
          *(undefined4 *)(puVar20 + -0xc) = 0x74e85;
          settextpos();
          iVar16 = (uint)local_14 * 0x2f4;
          iVar12 = local_60 * 0x1b;
          *(int *)(puVar20 + -4) = iVar16 + iVar12 + 0xea998;
          *(uint *)(puVar20 + -8) = (uint)(byte)(&unk_ea991)[iVar12 + iVar16];
          *(uint *)(puVar20 + -0xc) = (uint)(byte)(&unk_ea990)[iVar12 + iVar16];
          *(char **)(puVar20 + -0x10) = aC2dS_c3107;
          *(undefined **)(puVar20 + -0x14) = auStack_c4;
          *(undefined4 *)(puVar20 + -0x18) = 0x74edf;
          sprintf(*(char **)(puVar20 + -0x14),*(char **)(puVar20 + -0x10));
          *(undefined4 *)(puVar20 + -4) = 0x74f01;
          sub_76771(0x1fa,local_60 * 0xd + 0x16,auStack_c4);
        }
      }
    }
  }
  else {
    local_38 = local_54 * 0x20;
    if ((&local_94)[local_50][local_54 * 8 + 5] == 0) {
      if ((&local_94)[local_50][local_54 * 8 + 6] == 0) {
        if ((int)piVar11 < 0x20) {
          piVar13 = (int *)0x0;
        }
        *(int **)(puVar20 + -4) = piVar13;
        if ((int)ppiVar10 < 0x1c) {
          ppiVar10 = (int **)0x0;
        }
        else {
          ppiVar10 = ppiVar10 + -7;
        }
        *(int ***)(puVar20 + -8) = ppiVar10;
        *(undefined4 **)(puVar20 + -0xc) = local_20;
        *(undefined4 *)(puVar20 + -0x10) = 0x74395;
        drawshape();
        uVar4 = local_2c;
        uVar18 = local_34;
        *(undefined4 *)(puVar20 + -4) = local_2c;
        *(undefined4 *)(puVar20 + -8) = local_34;
        iVar12 = local_104[local_50 * 2 + 1];
        iVar16 = local_104[local_50 * 2];
        iVar22 = local_a4[local_50];
        piVar11 = (&local_94)[local_50];
        *(undefined4 *)(puVar20 + -0xc) = 0x743c0;
        highlight_menu_item(piVar11 + iVar22 * 8,iVar16,iVar12,local_30);
        iVar22 = local_50;
        local_a4[local_50] = local_54;
        *(undefined4 *)(puVar20 + -4) = uVar4;
        *(undefined4 *)(puVar20 + -8) = uVar18;
        iVar12 = local_104[iVar22 * 2 + 1];
        iVar16 = local_104[iVar22 * 2];
        piVar11 = (&local_94)[iVar22] + local_a4[iVar22] * 8;
        uVar18 = local_30;
      }
      else {
        if ((int)piVar11 < 0x20) {
          piVar13 = (int *)0x0;
        }
        *(int **)(puVar20 + -4) = piVar13;
        if ((int)ppiVar10 < 0x1c) {
          ppiVar10 = (int **)0x0;
        }
        else {
          ppiVar10 = ppiVar10 + -7;
        }
        *(int ***)(puVar20 + -8) = ppiVar10;
        *(undefined4 **)(puVar20 + -0xc) = local_20;
        *(undefined4 *)(puVar20 + -0x10) = 0x7414d;
        drawshape();
        if (local_1c != local_50) {
          for (local_44 = local_1c; iVar12 = local_44, local_50 < local_44; local_44 = local_44 + -1
              ) {
            local_a4[local_44] = 0;
            iVar12 = local_84[iVar12];
            if (iVar12 != 0) {
              *(int *)(puVar20 + -4) = local_104[local_44 * 2 + 1];
              *(int *)(puVar20 + -8) = local_104[local_44 * 2];
              *(int *)(puVar20 + -0xc) = iVar12;
              *(undefined4 *)(puVar20 + -0x10) = 0x74181;
              drawshape();
              iVar12 = local_44;
              local_104[local_44 * 2 + 1] = 0;
              local_104[iVar12 * 2] = 0;
              *(int *)(puVar20 + -4) = local_84[iVar12];
              *(undefined4 *)(puVar20 + -8) = 0x74199;
              freemem();
              iVar12 = local_44;
              local_84[local_44] = 0;
              (&local_94)[iVar12] = (int *)0x0;
              local_84[iVar12 + 4] = 0;
            }
          }
          local_1c = local_50;
        }
        iVar8 = local_1c;
        *(undefined4 *)(puVar20 + -4) = local_2c;
        *(undefined4 *)(puVar20 + -8) = local_34;
        iVar12 = local_104[local_1c * 2 + 1];
        iVar16 = local_104[local_1c * 2];
        iVar22 = local_a4[local_1c];
        local_40 = (undefined4 *)(iVar22 * 0x20);
        piVar11 = (&local_94)[local_1c];
        *(undefined4 *)(puVar20 + -0xc) = 0x741e7;
        highlight_menu_item(piVar11 + iVar22 * 8,iVar16,iVar12,local_30);
        local_a4[iVar8] = local_54;
        *(undefined4 *)(puVar20 + -4) = local_2c;
        *(undefined4 *)(puVar20 + -8) = local_34;
        iVar12 = local_104[iVar8 * 2 + 1];
        iVar16 = local_104[iVar8 * 2];
        piVar11 = (&local_94)[iVar8];
        *(undefined4 *)(puVar20 + -0xc) = 0x74212;
        unhighlight_menu_item(piVar11 + local_54 * 8,iVar16,iVar12,local_30);
        iVar16 = local_50;
        iVar12 = local_54;
        iVar22 = iVar8 + 1;
        local_1c = iVar22;
        (&local_94)[iVar22] = (int *)(&local_94)[local_50][local_54 * 8 + 6];
        piVar11 = (&local_94)[iVar16] + iVar12 * 8;
        local_84[iVar8 + 5] = piVar11[7];
        if (iVar22 == 1) {
          iVar12 = *piVar11;
        }
        else {
          iVar12 = piVar11[2];
        }
        local_104[local_1c * 2] = iVar12 + *(int *)(abStack_110 + local_1c * 8 + 4);
        if (local_1c == 1) {
          iVar12 = (&local_94)[local_50][local_54 * 8 + 3];
        }
        else {
          iVar12 = (&local_94)[local_50][local_54 * 8 + 1];
        }
        local_28 = local_1c * 8;
        local_104[local_1c * 2 + 1] = iVar12 + local_104[local_1c * 2 + -1];
        local_24 = local_1c * 4;
        piVar11 = (&local_94)[local_1c];
        local_84[8] = (piVar11[local_84[local_1c + 4] * 8 + -6] - *piVar11) + 1;
        local_5c = (piVar11[local_84[local_1c + 4] * 8 + -5] - piVar11[1]) + 1;
        *(undefined4 *)(puVar20 + -4) = 0x20;
        *(int *)(puVar20 + -8) = local_84[8] * 4 * local_5c + 0x11;
        *(char **)(puVar20 + -0xc) = aMenubuff_c30fe;
        *(undefined4 *)(puVar20 + -0x10) = 0x742d0;
        puVar15 = (undefined4 *)allocmem();
        iVar12 = local_24;
        *(undefined4 **)((int)local_84 + local_24) = puVar15;
        puVar21 = puVar15 + (uint)bVar25 * -2 + 1;
        ppiVar10 = pointer_shapes + (uint)bVar25 * -2 + 1;
        *puVar15 = *pointer_shapes;
        puVar15 = puVar21 + (uint)bVar25 * -2 + 1;
        ppiVar14 = ppiVar10 + (uint)bVar25 * -2 + 1;
        *puVar21 = *ppiVar10;
        *puVar15 = *ppiVar14;
        puVar15[(uint)bVar25 * -2 + 1] = ppiVar14[(uint)bVar25 * -2 + 1];
        *(undefined *)(puVar15 + (uint)bVar25 * -2 + 1 + (uint)bVar25 * -2 + 1) =
             *(undefined *)(ppiVar14 + (uint)bVar25 * -2 + 1 + (uint)bVar25 * -2 + 1);
        *(short *)(*(int *)((int)local_84 + iVar12) + 4) = (short)local_84[8];
        *(short *)(*(int *)((int)local_84 + local_24) + 6) = (short)local_5c;
        *(undefined4 *)(puVar20 + -4) = *(undefined4 *)((int)local_104 + local_28 + 4);
        *(undefined4 *)(puVar20 + -8) = *(undefined4 *)((int)local_104 + local_28);
        *(undefined4 *)(puVar20 + -0xc) = *(undefined4 *)((int)local_84 + local_24);
        *(undefined4 *)(puVar20 + -0x10) = 0x7431a;
        grabshape();
        uVar18 = local_30;
        *(undefined4 *)(puVar20 + -4) = local_2c;
        *(undefined4 *)(puVar20 + -8) = local_34;
        *(undefined4 *)(puVar20 + -0xc) = local_30;
        uVar4 = *(undefined4 *)((int)local_104 + local_28 + 4);
        uVar5 = *(undefined4 *)((int)local_104 + local_28);
        uVar6 = *(undefined4 *)((int)local_84 + local_24 + 0x10);
        uVar7 = *(undefined4 *)((int)&local_94 + local_24);
        *(undefined4 *)(puVar20 + -0x10) = 0x7434a;
        draw_menu(uVar7,uVar6,uVar5,uVar4);
        *(undefined4 *)((int)local_a4 + local_24) = 0;
        *(undefined4 *)(puVar20 + -4) = local_2c;
        *(undefined4 *)(puVar20 + -8) = local_34;
        iVar12 = *(int *)((int)local_104 + local_28 + 4);
        iVar16 = *(int *)((int)local_104 + local_28);
        piVar11 = *(int **)((int)&local_94 + local_24);
      }
    }
    else {
      if (local_54 == local_a4[local_50]) {
        if ((int)piVar11 < 0x20) {
          piVar13 = (int *)0x0;
        }
        *(int **)(puVar20 + -4) = piVar13;
        if ((int)ppiVar10 < 0x1c) {
          ppiVar10 = (int **)0x0;
        }
        else {
          ppiVar10 = ppiVar10 + -7;
        }
        *(int ***)(puVar20 + -8) = ppiVar10;
        *(undefined4 **)(puVar20 + -0xc) = local_20;
        *(undefined4 *)(puVar20 + -0x10) = 0x73fd5;
        drawshape();
        for (local_44 = 3; -1 < local_44; local_44 = local_44 + -1) {
          iVar12 = local_84[local_44];
          if (iVar12 != 0) {
            *(int *)(puVar20 + -4) = local_104[local_44 * 2 + 1];
            *(int *)(puVar20 + -8) = local_104[local_44 * 2];
            *(int *)(puVar20 + -0xc) = iVar12;
            *(undefined4 *)(puVar20 + -0x10) = 0x73ffe;
            drawshape();
            iVar12 = local_44;
            local_104[local_44 * 2 + 1] = 0;
            local_104[iVar12 * 2] = 0;
            *(int *)(puVar20 + -4) = local_84[iVar12];
            *(undefined4 *)(puVar20 + -8) = 0x74018;
            freemem();
          }
        }
        local_1c = 0;
        piVar11 = (&local_94)[local_50];
        *(int ***)(puVar20 + -4) = &local_4c;
        *(int ****)(puVar20 + -8) = &local_48;
        *(undefined4 *)(puVar20 + -0xc) = param_6;
        *(int **)(puVar20 + -0x10) = param_5;
        *(undefined4 *)(puVar20 + -0x14) = 0;
        *(int ***)(puVar20 + -0x18) = param_2;
        pcVar3 = (code *)piVar11[local_54 * 8 + 5];
        *(undefined4 *)(puVar20 + -0x1c) = 0x7406e;
        iVar12 = (*pcVar3)();
        local_88 = 0;
        local_8c = 0;
        local_90 = 0;
        local_84[2] = 0;
        local_84[1] = 0;
        local_84[0] = 0;
        local_a4[3] = 0;
        local_a4[2] = 0;
        local_a4[1] = 0;
        local_84[7] = 0;
        local_84[6] = 0;
        local_84[5] = 0;
        if (iVar12 == 1) {
          *(undefined4 *)(puVar20 + -0x1c) = 0x75011;
          event_queue_reset();
          *(undefined4 **)(puVar20 + -0x1c) = local_20;
          *(undefined4 *)(puVar20 + -0x20) = 0x7501a;
          freemem();
          *(undefined4 *)(puVar20 + -0x1c) = 0x7502f;
          fade_palette(1,local_3c,0x10);
          *(void **)(puVar20 + -0x1c) = local_3c;
          *(undefined4 *)(puVar20 + -0x20) = 0x75038;
          freemem();
          return 0;
        }
        *(undefined4 *)(puVar20 + -0x1c) = 0x740a2;
        event_queue_reset();
        puVar20 = puVar20 + -0x18;
        goto LAB_00074f01;
      }
      if ((int)piVar11 < 0x20) {
        piVar13 = (int *)0x0;
      }
      *(int **)(puVar20 + -4) = piVar13;
      if ((int)ppiVar10 < 0x1c) {
        ppiVar10 = (int **)0x0;
      }
      else {
        ppiVar10 = ppiVar10 + -7;
      }
      *(int ***)(puVar20 + -8) = ppiVar10;
      *(undefined4 **)(puVar20 + -0xc) = local_20;
      *(undefined4 *)(puVar20 + -0x10) = 0x740c5;
      drawshape();
      uVar18 = local_2c;
      *(undefined4 *)(puVar20 + -4) = local_2c;
      *(undefined4 *)(puVar20 + -8) = local_34;
      iVar12 = local_104[local_50 * 2 + 1];
      iVar16 = local_104[local_50 * 2];
      iVar22 = local_a4[local_50];
      piVar11 = (&local_94)[local_50];
      *(undefined4 *)(puVar20 + -0xc) = 0x740f0;
      highlight_menu_item(piVar11 + iVar22 * 8,iVar16,iVar12,local_30);
      iVar22 = local_50;
      local_a4[local_50] = local_54;
      *(undefined4 *)(puVar20 + -4) = uVar18;
      *(undefined4 *)(puVar20 + -8) = local_34;
      iVar12 = local_104[iVar22 * 2 + 1];
      iVar16 = local_104[iVar22 * 2];
      piVar11 = (&local_94)[iVar22] + local_a4[iVar22] * 8;
      uVar18 = local_30;
    }
    *(undefined4 *)(puVar20 + -0xc) = 0x74120;
    unhighlight_menu_item(piVar11,iVar16,iVar12,uVar18);
  }
LAB_00074f01:
  ppiVar14 = local_48;
  if ((int)local_4c < 0x20) {
    piVar11 = (int *)0x0;
  }
  else {
    piVar11 = local_4c + -8;
  }
  *(int **)(puVar20 + -4) = piVar11;
  if ((int)local_48 < 0x1c) {
    ppiVar10 = (int **)0x0;
  }
  else {
    ppiVar10 = local_48 + -7;
  }
  *(int ***)(puVar20 + -8) = ppiVar10;
  *(undefined4 **)(puVar20 + -0xc) = local_20;
  *(undefined4 *)(puVar20 + -0x10) = 0x74f2a;
  grabshape();
  if (((local_94[3] < (int)local_4c) && ((int)local_48 < 500)) && (local_60 != -1)) {
    if (local_90 != 0) {
      *(int **)(puVar20 + -4) = &local_54;
      *(int **)(puVar20 + -8) = &local_50;
      *(int **)(puVar20 + -0xc) = local_104;
      *(int **)(puVar20 + -0x10) = local_84 + 4;
      ppiVar14 = &local_94;
      *(undefined4 *)(puVar20 + -0x14) = 0x74f7b;
      iVar12 = hit_test_menus(local_48,local_4c,ppiVar14,local_1c);
      if (iVar12 != 0) goto LAB_00074ff5;
    }
    ppiVar14 = (int **)((uint)local_14 * 0x2f4);
    iVar12 = local_60 * 0x1b + (int)ppiVar14;
    if ((&unk_ea993)[iVar12] != '\x02') {
      uVar1 = (&unk_ea991)[iVar12];
      *(undefined4 *)(puVar20 + -4) = 0x74fcb;
      sub_7a099(&unk_d1238,uVar1,local_18,local_10);
      *(undefined1 **)(puVar20 + -4) = &unk_d1238;
      *(undefined4 *)(puVar20 + -8) = 0x74fd5;
      ppiVar14 = param_2;
      setremaptable();
      *(int **)(puVar20 + -4) = local_4c + -8;
      *(int ***)(puVar20 + -8) = local_48 + -7;
      *(int ***)(puVar20 + -0xc) = ppiVar14;
      *(undefined4 *)(puVar20 + -0x10) = 0x74ff2;
      param_2 = ppiVar14;
      drawshape_trans();
    }
  }
LAB_00074ff5:
  *(int **)(puVar20 + -4) = local_4c;
  *(int *)(puVar20 + -8) = (int)local_48 + -3;
  *(int ***)(puVar20 + -0xc) = pointer_shapes;
  goto LAB_00073f14;
code_r0x00073f44:
  if ((ppiVar10 == local_48) && (piVar11 == local_4c)) goto LAB_00073f22;
  if ((int)piVar11 < 0x20) {
    piVar11 = (int *)0x0;
  }
  else {
    piVar11 = piVar11 + -8;
  }
  *(int **)(puVar20 + -4) = piVar11;
  if ((int)ppiVar10 < 0x1c) {
    ppiVar10 = (int **)0x0;
  }
  else {
    ppiVar10 = ppiVar10 + -7;
  }
  *(int ***)(puVar20 + -8) = ppiVar10;
  *(undefined4 **)(puVar20 + -0xc) = local_20;
  *(undefined4 *)(puVar20 + -0x10) = 0x73e0c;
  drawshape();
  if ((int)local_4c < 0x20) {
    piVar11 = (int *)0x0;
  }
  else {
    piVar11 = local_4c + -8;
  }
  *(int **)(puVar20 + -4) = piVar11;
  if ((int)local_48 < 0x1c) {
    ppiVar10 = (int **)0x0;
  }
  else {
    ppiVar10 = local_48 + -7;
  }
  *(int ***)(puVar20 + -8) = ppiVar10;
  *(undefined4 **)(puVar20 + -0xc) = local_20;
  *(undefined4 *)(puVar20 + -0x10) = 0x73e38;
  grabshape();
  if (((local_94[3] < (int)local_4c) && ((int)local_48 < 500)) && (local_60 != -1)) {
    if (local_90 != 0) {
      *(int **)(puVar20 + -4) = &local_54;
      *(int **)(puVar20 + -8) = &local_50;
      *(int **)(puVar20 + -0xc) = local_104;
      *(int **)(puVar20 + -0x10) = local_84 + 4;
      *(undefined4 *)(puVar20 + -0x14) = 0x73e88;
      iVar12 = hit_test_menus(local_48,local_4c,&local_94,local_1c);
      if (iVar12 != 0) goto LAB_00073f02;
    }
    iVar12 = local_60 * 0x1b + (uint)local_14 * 0x2f4;
    if ((&unk_ea993)[iVar12] != '\x02') {
      uVar1 = (&unk_ea991)[iVar12];
      *(undefined4 *)(puVar20 + -4) = 0x73ed8;
      sub_7a099(&unk_d1238,uVar1,local_18,local_10);
      *(undefined1 **)(puVar20 + -4) = &unk_d1238;
      *(undefined4 *)(puVar20 + -8) = 0x73ee2;
      setremaptable();
      *(int **)(puVar20 + -4) = local_4c + -8;
      *(int ***)(puVar20 + -8) = local_48 + -7;
      *(int ***)(puVar20 + -0xc) = param_2;
      *(undefined4 *)(puVar20 + -0x10) = 0x73eff;
      drawshape_trans();
    }
  }
LAB_00073f02:
  *(int **)(puVar20 + -4) = local_4c;
  *(int *)(puVar20 + -8) = (int)local_48 + -3;
  *(int ***)(puVar20 + -0xc) = pointer_shapes;
  ppiVar14 = pointer_shapes;
LAB_00073f14:
  *(undefined4 *)(puVar20 + -0x10) = 0x73f19;
  uVar26 = drawshape_trans();
  ppiVar10 = local_48;
  piVar11 = local_4c;
  goto LAB_00073f22;
}


// ================================================================================================
// sub_75046 @ 0x75046 [__watcall]
// ================================================================================================

void __watcall sub_75046(int param_1,undefined4 unaff_EDX,byte unaff_BL)

{
  undefined uVar1;
  byte bVar2;
  int iVar3;
  undefined uVar4;
  int iVar5;
  int iVar6;
  undefined4 unaff_EDI;
  char acStack_40 [32];
  
  __CHK(0x58);
  uVar4 = byte_d12de;
  uVar1 = (&unk_d1238)[(byte)(&unk_d11bc)[(uint)(byte)(&byte_d079e)[unaff_BL] * 4]];
  iVar6 = 0;
  do {
    if (*(byte *)(iVar6 + param_1) < 100) {
      sub_7a099(&unk_d1238,*(byte *)(iVar6 + param_1),uVar1,uVar4);
    }
    else {
      iVar5 = 0;
      do {
        (&unk_d1238)[iVar5] = uVar4;
        iVar5 = iVar5 + 1;
      } while (iVar5 < 0x90);
      iVar5 = 0xc0;
      do {
        (&unk_d1238)[iVar5] = uVar4;
        iVar5 = iVar5 + 1;
      } while (iVar5 < 0xf0);
    }
    setremaptable(&unk_d1238);
    drawshape2_trans(unaff_EDX,(&unk_d1338)[iVar6 * 2],(&unk_d133c)[iVar6 * 2]);
    iVar6 = iVar6 + 1;
  } while (iVar6 < 0x28);
  iVar6 = 0;
  do {
    bVar2 = (&unk_ea993)[iVar6 * 0x1b + (uint)unaff_BL * 0x2f4];
    if (bVar2 == 0) {
      return;
    }
    if (1 < bVar2) {
      if (bVar2 < 3) {
        unaff_EDI = 0xfc;
      }
      else if (bVar2 == 3) {
        unaff_EDI = 0xc3;
      }
    }
    settextpos(unaff_EDI,0xc1);
    iVar3 = (uint)unaff_BL * 0x2f4;
    iVar5 = iVar6 * 0x1b;
    sprintf(acStack_40,aC2dS_c3107,(uint)(byte)(&unk_ea990)[iVar5 + iVar3],
            (uint)(byte)(&unk_ea991)[iVar5 + iVar3],iVar3 + iVar5 + 0xea998);
    sub_76771(0x1fa,iVar6 * 0xd + 0x16,acStack_40);
    iVar6 = iVar6 + 1;
  } while (iVar6 < 0x1c);
  return;
}


// ================================================================================================
// roster_dress_screen @ 0x751fc [__watcall]
// ================================================================================================

undefined4 __watcall roster_dress_screen(undefined4 param_1,undefined4 unaff_EDX,byte unaff_BL)

{
  int iVar1;
  undefined3 *puVar2;
  char *pcVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  undefined4 *puVar7;
  char acStack_8c [28];
  char acStack_70 [28];
  undefined4 uStack_54;
  char acStack_38 [8];
  undefined4 uStack_30;
  char local_2c [4];
  char acStack_28 [8];
  char acStack_20 [8];
  int local_18;
  byte bStack_14;
  
  __CHK(0xb0);
  iVar6 = 0;
  local_18 = 0;
  pcVar3 = "Your Roster is incomplete.";
  puVar7 = &uStack_54;
  bStack_14 = unaff_BL;
  for (iVar4 = 6; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar7 = *(undefined4 *)pcVar3;
    pcVar3 = pcVar3 + 4;
    puVar7 = puVar7 + 1;
  }
  *(undefined2 *)puVar7 = *(undefined2 *)pcVar3;
  *(char *)((int)puVar7 + 2) = pcVar3[2];
  builtin_strncpy(acStack_38,"Scratch",8);
  builtin_strncpy(acStack_20,"Dress",6);
  builtin_strncpy(acStack_28,"Player",7);
  uStack_30._0_1_ = 'G';
  uStack_30._1_1_ = 'o';
  uStack_30._2_1_ = 'a';
  uStack_30._3_1_ = 'l';
  local_2c[0] = 'i';
  local_2c[1] = 'e';
  local_2c[2] = '\0';
  iVar4 = 0;
  do {
    iVar1 = iVar4 * 0x1b + (uint)bStack_14 * 0x2f4;
    if ((&unk_ea993)[iVar1] == '\x03') {
      if ((&unk_ea990)[iVar1] == 'G') {
        local_18 = local_18 + 1;
      }
      else {
        iVar6 = iVar6 + 1;
      }
    }
    iVar4 = iVar4 + 1;
  } while (iVar4 < 0x1c);
  if ((iVar6 == 0x12) && (local_18 == 2)) {
    return 0;
  }
  if (iVar6 < 0x12) {
    if (iVar6 == 0x11) {
      puVar2 = (undefined3 *)&unk_c311d;
    }
    else {
      puVar2 = &aS_c311f;
    }
    iVar4 = 0x12 - iVar6;
    pcVar3 = acStack_20;
LAB_00075316:
    sprintf(acStack_8c,aS2dSS,pcVar3,iVar4,acStack_28,puVar2);
  }
  else if (0x12 < iVar6) {
    if (iVar6 == 0x13) {
      puVar2 = (undefined3 *)&unk_c311d;
    }
    else {
      puVar2 = &aS_c311f;
    }
    iVar4 = iVar6 + -0x12;
    pcVar3 = acStack_38;
    goto LAB_00075316;
  }
  if (local_18 < 2) {
    if (local_18 == 1) {
      puVar2 = (undefined3 *)&unk_c311d;
    }
    else {
      puVar2 = &aS_c311f;
    }
    iVar4 = 2 - local_18;
    pcVar3 = acStack_20;
  }
  else {
    if (local_18 < 3) goto LAB_0007539e;
    if (local_18 == 3) {
      puVar2 = (undefined3 *)&unk_c311d;
    }
    else {
      puVar2 = &aS_c311f;
    }
    iVar4 = local_18 + -2;
    pcVar3 = acStack_38;
  }
  sprintf(acStack_70,aS2dSS,pcVar3,iVar4,&uStack_30,puVar2);
LAB_0007539e:
  if ((iVar6 == 0x12) || (local_18 == 2)) {
    if (iVar6 == 0x12) {
      dword_ebc78 = acStack_70;
      uVar5 = 2;
    }
    else {
      dword_ebc78 = acStack_8c;
      uVar5 = 2;
    }
  }
  else {
    dword_ebc78 = acStack_8c;
    dword_ebc7c = acStack_70;
    uVar5 = 3;
  }
  dword_ebc74 = &uStack_54;
  message_dialog(0xffffffff,0xffffffff,&dword_ebc74,uVar5,0,0,param_1,unaff_EDX,0xffffffff);
  return 1;
}


// ================================================================================================
// sub_75456 @ 0x75456 [__watcall]
// ================================================================================================

undefined4 __watcall sub_75456(int param_1,int unaff_EDX,byte param_3)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  undefined4 in_stack_00000014;
  undefined4 in_stack_00000018;
  
  __CHK(0x14);
  iVar1 = roster_dress_screen(in_stack_00000014,in_stack_00000018,param_3);
  if (iVar1 == 0) {
    iVar1 = 0;
    do {
      if (*(char *)(param_1 + iVar1) == 'd') {
        *(undefined *)(iVar1 + unaff_EDX) = 100;
      }
      else {
        iVar4 = 0;
        do {
          iVar3 = iVar4 * 0x1b + (uint)param_3 * 0x2f4;
          if (((&unk_ea993)[iVar3] != '\0') && (*(char *)(param_1 + iVar1) == (&unk_ea991)[iVar3]))
          {
            *(undefined1 *)(iVar1 + unaff_EDX) = (&unk_ea992)[iVar3];
            break;
          }
          iVar4 = iVar4 + 1;
        } while (iVar4 < 0x1c);
      }
      iVar1 = iVar1 + 1;
    } while (iVar1 < 0x28);
    iVar1 = 0;
    do {
      *(undefined *)(iVar1 + 0x28 + unaff_EDX) = 100;
      iVar1 = iVar1 + 1;
    } while (iVar1 < 8);
    iVar1 = 0;
    for (iVar4 = 0; iVar4 < 0x1c; iVar4 = iVar4 + 1) {
      iVar3 = iVar4 * 0x1b + (uint)param_3 * 0x2f4;
      if (((&unk_ea993)[iVar3] != '\0') && ((&unk_ea993)[iVar3] != '\x03')) {
        *(undefined1 *)(iVar1 + 0x28 + unaff_EDX) = (&unk_ea992)[iVar3];
        iVar1 = iVar1 + 1;
      }
    }
    puVar5 = (undefined4 *)((&dword_eaf78)[param_3] + 0xbc);
    puVar6 = (undefined4 *)((&dword_eaf78)[param_3] + 0xec);
    for (iVar1 = 0xc; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar6 = *puVar5;
      puVar5 = puVar5 + 1;
      puVar6 = puVar6 + 1;
    }
    uVar2 = 1;
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}


// ================================================================================================
// roster_screen @ 0x7556e [__watcall]
// ================================================================================================

undefined4 __watcall
roster_screen(undefined4 param_1,undefined4 param_2,byte unaff_BL,int *unaff_ECX,undefined4 param_5,
             undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  char acStack_30 [32];
  byte bStack_10;
  
  __CHK(0x48);
  bStack_10 = unaff_BL;
  dword_dd11c = allocmem(&aKeys_c3122,0x5b0,0);
  dword_ebc70 = allocmem(aPstat_c3127,0x497,0);
  dword_ebc6c = allocmem(aGstat_c312d,0x10e,0);
  roster_table(0xc0,0xc1,0xc2,0xc3);
  run_menu(aDisplay + 0xc,2,0xc0,0xc1,0xc2);
  freemem(dword_ebc6c);
  freemem(dword_ebc70);
  freemem(dword_dd11c);
  dword_dd11c = 0;
  dword_ebc6c = 0;
  dword_ebc70 = 0;
  setscreen(dword_ea2b4);
  clearclip(0);
  uVar3 = (uint)bStack_10;
  draw_lines_screen(uVar3,param_5,param_6,param_7,param_8);
  sub_75046(param_1,param_5,uVar3);
  setdefaultscreen();
  drawshape2_home(*(undefined4 *)(dword_ea2b4 + 0x2c));
  if (-1 < *unaff_ECX) {
    if ((&unk_ea993)[*unaff_ECX * 0x1b + uVar3 * 0x2f4] == '\x02') {
      uVar4 = 0x7e;
    }
    else {
      uVar4 = 0xc0;
    }
    settextpos(uVar4,0xc1);
    iVar2 = (uint)bStack_10 * 0x2f4;
    iVar1 = *unaff_ECX * 0x1b;
    sprintf(acStack_30,aC2dS_c3107,(uint)(byte)(&unk_ea990)[iVar2 + iVar1],
            (uint)(byte)(&unk_ea991)[iVar2 + iVar1],iVar2 + iVar1 + 0xea998);
    sub_76771(0x1fa,*unaff_ECX * 0xd + 0x16,acStack_30);
  }
  return 0;
}


// ================================================================================================
// sub_75770 @ 0x75770 [__watcall]
// ================================================================================================

undefined4 __watcall
sub_75770(int param_1,undefined4 param_2,byte unaff_BL,int *unaff_ECX,undefined4 param_5)

{
  int iVar1;
  int iVar2;
  char acStack_30 [32];
  byte bStack_10;
  
  __CHK(0x48);
  iVar2 = 0;
  do {
    if (*(char *)(param_1 + iVar2) == (&unk_ea991)[(uint)unaff_BL * 0x2f4 + *unaff_ECX * 0x1b]) {
      *(char *)(param_1 + iVar2) = 'd';
    }
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0x28);
  iVar1 = (uint)unaff_BL * 0x2f4;
  (&unk_ea993)[iVar1 + *unaff_ECX * 0x1b] = 2;
  bStack_10 = unaff_BL;
  sub_75046(param_1,param_5);
  settextpos(0xfd,0xc1);
  iVar2 = *unaff_ECX * 0x1b;
  sprintf(acStack_30,aC2dS_c3107,(uint)(byte)(&unk_ea990)[iVar1 + iVar2],
          (uint)(byte)(&unk_ea991)[iVar1 + iVar2],iVar1 + 0xea998 + iVar2);
  sub_76771(0x1fa,*unaff_ECX * 0xd + 0x16,acStack_30);
  return 0;
}


// ================================================================================================
// sub_75868 @ 0x75868 [__watcall]
// ================================================================================================

undefined4 __watcall
sub_75868(undefined4 param_1,undefined4 param_2,uint unaff_EBX,int *unaff_ECX,undefined4 param_5)

{
  int iVar1;
  int iVar2;
  char acStack_2c [32];
  
  __CHK(0x44);
  iVar2 = (unaff_EBX & 0xff) * 0x2f4;
  (&unk_ea993)[iVar2 + *unaff_ECX * 0x1b] = 3;
  sub_75046(param_1,param_5);
  settextpos(0xc0,0xc1);
  iVar1 = *unaff_ECX * 0x1b;
  sprintf(acStack_2c,aC2dS_c3107,(uint)(byte)(&unk_ea990)[iVar2 + iVar1],
          (uint)(byte)(&unk_ea991)[iVar2 + iVar1],iVar2 + iVar1 + 0xea998);
  sub_76771(0x1fa,*unaff_ECX * 0xd + 0x16,acStack_2c);
  return 0;
}


// ================================================================================================
// sub_75931 @ 0x75931 [__watcall]
// ================================================================================================

int __watcall sub_75931(int *param_1,int *unaff_EDX)

{
  ushort uVar1;
  ushort uVar2;
  ushort uVar3;
  ushort *puVar4;
  uint uVar6;
  ushort *puVar7;
  uint uVar5;
  
  __CHK(0x14);
  if (dword_c6956 == 0) {
    puVar4 = (ushort *)(dword_ebc70 + *param_1 * 0x28);
    puVar7 = (ushort *)(dword_ebc70 + *unaff_EDX * 0x28);
  }
  else {
    puVar4 = (ushort *)(*param_1 * 0x28 + dword_ebc70 + 0x12);
    puVar7 = (ushort *)(dword_ebc70 + *unaff_EDX * 0x28 + 0x12);
  }
  uVar1 = *puVar4;
  if ((uVar1 == 0) == (*puVar7 == 0)) {
    uVar2 = puVar7[3];
    uVar3 = puVar4[3];
    if (uVar2 == puVar4[3]) {
      if (uVar1 != *puVar7) {
        return (uint)uVar1 - (uint)*puVar7;
      }
      uVar2 = puVar7[1];
      uVar3 = puVar4[1];
      if (uVar2 == uVar3) {
        uVar6 = *(int *)(puVar7 + 7) >> 0x10;
        uVar5 = *(int *)(puVar4 + 7) >> 0x10;
        goto LAB_00075a2e;
      }
    }
  }
  else {
    uVar2 = *puVar7;
    uVar3 = uVar1;
  }
  uVar6 = (uint)uVar2;
  uVar5 = (uint)uVar3;
LAB_00075a2e:
  return uVar6 - uVar5;
}


// ================================================================================================
// sub_75a37 @ 0x75a37 [__watcall]
// ================================================================================================

int __watcall sub_75a37(int *param_1,int *unaff_EDX)

{
  ushort uVar1;
  ushort *puVar2;
  uint uVar3;
  ushort *puVar4;
  ushort uVar5;
  
  __CHK(0x14);
  if (dword_c6956 == 0) {
    puVar2 = (ushort *)(*param_1 * 0x2c + dword_ebc6c);
    puVar4 = (ushort *)(dword_ebc6c + *unaff_EDX * 0x2c);
  }
  else {
    puVar2 = (ushort *)(*param_1 * 0x2c + dword_ebc6c + 0x16);
    puVar4 = (ushort *)(dword_ebc6c + *unaff_EDX * 0x2c + 0x16);
  }
  uVar5 = puVar2[6];
  if ((uVar5 == 0) == (puVar4[6] == 0)) {
    uVar1 = puVar2[8];
    if (puVar4[8] != uVar1) {
      uVar5 = puVar4[8];
LAB_00075b09:
      return (uint)uVar1 - (uint)uVar5;
    }
    uVar1 = puVar4[6];
    if (uVar1 == uVar5) {
      uVar1 = *puVar4;
      uVar5 = *puVar2;
      if (uVar1 == uVar5) {
        if (puVar4[7] != puVar2[7]) {
          return (uint)puVar2[7] - (uint)puVar4[7];
        }
        uVar3 = (uint)puVar4[1];
        uVar5 = puVar2[1];
        if (puVar4[1] == uVar5) {
          uVar1 = puVar2[2];
          if (puVar4[2] != uVar1) {
            uVar5 = puVar4[2];
            goto LAB_00075b09;
          }
          uVar3 = (uint)puVar4[10];
          uVar5 = puVar2[10];
        }
        goto LAB_00075b9c;
      }
    }
  }
  else {
    uVar1 = puVar4[6];
  }
  uVar3 = (uint)uVar1;
LAB_00075b9c:
  return uVar3 - uVar5;
}


// ================================================================================================
// sub_75baa @ 0x75baa [__watcall]
// ================================================================================================

longlong __watcall
sub_75baa(undefined4 param_1,uint unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  __CHK(0x10);
  dword_c6956 = 0;
  roster_table(0xc0,0xc1,0xc2,0xc3,unaff_EDX,unaff_ECX,unaff_EBX);
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// sub_75bde @ 0x75bde [__watcall]
// ================================================================================================

longlong __watcall
sub_75bde(undefined4 param_1,uint unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  __CHK(0x10);
  dword_c6956 = 1;
  roster_table(0xc0,0xc1,0xc2,0xc3,unaff_EDX,unaff_ECX,unaff_EBX);
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// roster_table @ 0x75bf7 [__watcall]
// ================================================================================================

undefined4 __watcall
roster_table(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined *puVar5;
  int iVar6;
  int iVar7;
  undefined4 *puVar8;
  int iVar9;
  undefined2 *puVar10;
  undefined8 uVar11;
  undefined auStack_a4 [64];
  char acStack_64 [40];
  undefined auStack_3c [32];
  undefined2 *local_1c;
  int local_18;
  int local_14;
  int iStack_10;
  
  __CHK(200);
  local_14 = 0;
  for (iVar6 = 0; iVar6 < 0x19; iVar6 = iVar6 + 1) {
    iVar7 = *(int *)(iVar6 * 4 + (&dword_eaf78)[byte_ec7e0] + 0x4c);
    if (iVar7 != -1) {
      puVar2 = (undefined4 *)sub_6cbb7(iVar7);
      puVar1 = puVar2;
      puVar8 = (undefined4 *)(dword_dd11c + iVar6 * 0x34);
      for (iVar7 = 0xd; iVar7 != 0; iVar7 = iVar7 + -1) {
        *puVar8 = *puVar1;
        puVar1 = puVar1 + 1;
        puVar8 = puVar8 + 1;
      }
      puVar1 = (undefined4 *)sub_6cbe8(puVar2[10]);
      puVar8 = (undefined4 *)(dword_ebc70 + local_14 * 0x28);
      for (iVar7 = 10; iVar7 != 0; iVar7 = iVar7 + -1) {
        *puVar8 = *puVar1;
        puVar1 = puVar1 + 1;
        puVar8 = puVar8 + 1;
      }
      *(int *)(&unk_dc754 + local_14 * 4) = iVar6;
      (&unk_dc6bc)[local_14] = local_14;
      local_14 = local_14 + 1;
    }
  }
  iStack_10 = 0;
  for (iVar6 = 0; iVar6 < 3; iVar6 = iVar6 + 1) {
    iVar7 = *(int *)(iVar6 * 4 + (&dword_eaf78)[byte_ec7e0] + 0xb0);
    if (iVar7 != -1) {
      puVar2 = (undefined4 *)sub_6cbb7(iVar7);
      puVar1 = puVar2;
      puVar8 = (undefined4 *)(dword_dd11c + (iVar6 + 0x19) * 0x34);
      for (iVar7 = 0xd; iVar7 != 0; iVar7 = iVar7 + -1) {
        *puVar8 = *puVar1;
        puVar1 = puVar1 + 1;
        puVar8 = puVar8 + 1;
      }
      uVar11 = sub_6cbfd(puVar2[10]);
      puVar1 = (undefined4 *)uVar11;
      puVar8 = (undefined4 *)(dword_ebc6c + iStack_10 * 0x2c);
      for (iVar7 = 0xb; iVar7 != 0; iVar7 = iVar7 + -1) {
        *puVar8 = *puVar1;
        puVar1 = puVar1 + 1;
        puVar8 = puVar8 + 1;
      }
      *(int *)(&unk_dc73c + iStack_10 * 4) = (int)((ulonglong)uVar11 >> 0x20);
      (&unk_dc720)[iStack_10] = iStack_10;
      iStack_10 = iStack_10 + 1;
    }
  }
  sub_9244c(&unk_dc6bc,local_14,4,sub_75931,unaff_ECX,unaff_EBX);
  sub_9244c(&unk_dc720,iStack_10,4,sub_75a37);
  setscreen(dword_ea2b4);
  clearclip(0);
  sprintf(acStack_64,aEmbS_c6935,(&dword_eaf78)[byte_ec7e0]);
  puVar5 = install_path;
  if ((&byte_ed83c)[(byte)(&byte_d079e)[byte_ec7e0]] != '\x01') {
    puVar5 = (undefined *)0x0;
  }
  make_path(auStack_3c,puVar5,acStack_64,0);
  uVar3 = loadshapes(auStack_3c,0);
  uVar4 = locateshape(uVar3,&aBkgd_c693b);
  setclip(0,0x280,0x13,0x1e0);
  drawshape_remap_home(uVar4);
  setclip(0,0x280,0,0x1e0);
  freemem(uVar3);
  getfontstate(auStack_a4);
  setfont(font_main);
  draw_menu_items(aDisplay + 0xc,2,param_1,unaff_EDX,unaff_EBX);
  set_text_colors(param_1,unaff_ECX);
  sprintf(acStack_64,aSRoster,(&dword_eaf78)[byte_ec7e0] + 5);
  sub_17573(0x19,acStack_64);
  print_text_at(0x14,0x30,&aPos_c313f);
  print_text_at(0x42,0x30,&aNo_c3143);
  print_text_at(0x60,0x30,&aName_c3146);
  print_text_at(0x10e,0x30,&aGP_c314b);
  print_text_at(0x136,0x30,&aG_c314e);
  print_text_at(0x15e,0x30,&aA_c3152);
  print_text_at(0x186,0x30,&aPT_c3156);
  print_text_at(0x1ae,0x30,aShots_c315a);
  print_text_at(0x1e8,0x30,&aPIM_c3160);
  print_text_at(0x210,0x30,&unk_c3164);
  iVar7 = 0x40;
  for (iVar6 = 0; iVar6 < local_14; iVar6 = iVar6 + 1) {
    local_18 = (&unk_dc6bc)[iVar6];
    iVar9 = *(int *)(&unk_dc754 + local_18 * 4) * 0x34 + dword_dd11c;
    sprintf(acStack_64,(char *)&aC_c3169,(int)*(char *)(iVar9 + 2));
    print_text_at(0x14,iVar7,acStack_64);
    if (*(byte *)(iVar9 + 1) < 100) {
      sub_176ae(0x42,iVar7,&a2d,*(byte *)(iVar9 + 1));
    }
    sub_29c75(acStack_64,iVar9 + 3,iVar9 + 0x13,0xa6);
    print_text_at(0x60,iVar7,acStack_64);
    if (dword_c6956 == 0) {
      puVar10 = (undefined2 *)(dword_ebc70 + local_18 * 0x28);
    }
    else {
      puVar10 = (undefined2 *)(local_18 * 0x28 + dword_ebc70 + 0x12);
    }
    sub_176ae(0x10e,iVar7,&a2d,*puVar10);
    sub_176ae(0x136,iVar7,&a3d,puVar10[1]);
    sub_176ae(0x15e,iVar7,&a3d,puVar10[2]);
    sub_176ae(0x186,iVar7,&a3d,puVar10[3]);
    sub_176ae(0x1ae,iVar7,&a4d,puVar10[7]);
    sub_176ae(0x1e8,iVar7,&a3d,puVar10[6]);
    sub_176ae(0x210,iVar7,&a4d,*(int *)(puVar10 + 7) >> 0x10);
    iVar7 = iVar7 + 0xd;
  }
  print_text_at(0x14,0x195,&aPos_c313f);
  print_text_at(0x42,0x195,&aNo_c3143);
  print_text_at(0x60,0x195,&aName_c3146);
  print_text_at(0x10e,0x195,&aGP_c314b);
  print_text_at(0x136,0x195,&aMin_c316c);
  print_text_at(0x15e,0x195,aGAA_c3171);
  print_text_at(400,0x195,&aW_c3177);
  print_text_at(0x1ae,0x195,&aL_c317a);
  if (dword_c6956 == 0) {
    print_text_at(0x1cc,0x195,&aT_c317d);
  }
  print_text_at(0x1ea,0x195,&aGA_c3180);
  print_text_at(0x20e,0x195,&aSA_c3184);
  print_text_at(0x240,0x195,aPCT_c3189);
  iVar7 = 0x1a5;
  for (iVar6 = 0; iVar6 < iStack_10; iVar6 = iVar6 + 1) {
    local_18 = (&unk_dc720)[iVar6];
    iVar9 = dword_dd11c + *(int *)(&unk_dc73c + local_18 * 4) * 0x34;
    sprintf(acStack_64,(char *)&aC_c3169,(int)*(char *)(iVar9 + 2));
    print_text_at(0x14,iVar7,acStack_64);
    if (*(byte *)(iVar9 + 1) < 100) {
      sub_176ae(0x42,iVar7,&a2d,*(byte *)(iVar9 + 1));
    }
    sub_29c75(acStack_64,iVar9 + 3,iVar9 + 0x13,0xa6);
    print_text_at(0x60,iVar7,acStack_64);
    if (dword_c6956 == 0) {
      puVar10 = (undefined2 *)(local_18 * 0x2c + dword_ebc6c);
    }
    else {
      puVar10 = (undefined2 *)(local_18 * 0x2c + dword_ebc6c + 0x16);
    }
    local_1c = puVar10;
    sub_176ae(0x10e,iVar7,&a2d,*puVar10);
    sub_176ae(0x136,iVar7,&a4d,puVar10[6]);
    sub_176db(0x15e,iVar7,a2d22d,(ushort)puVar10[8] / 100,(uint)(ushort)puVar10[8] % 100);
    sub_176ae(400,iVar7,&a2d,puVar10[1]);
    sub_176ae(0x1ae,iVar7,&a2d,puVar10[2]);
    if (dword_c6956 == 0) {
      sub_176ae(0x1cc,iVar7,&a2d,puVar10[3]);
    }
    sub_176ae(0x1ea,iVar7,&a3d,local_1c[7]);
    sub_176ae(0x20e,iVar7,&a4d,local_1c[9]);
    sub_176db(0x240,iVar7,a3d1d,(ushort)local_1c[10] / 10,(uint)(ushort)local_1c[10] % 10);
    iVar7 = iVar7 + 0xd;
  }
  setdefaultscreen();
  drawshape2_home(*(undefined4 *)(dword_ea2b4 + 0x2c));
  setfontstate(auStack_a4);
  return 0;
}


// ================================================================================================
// fade_palette @ 0x76429 [__watcall]
// ================================================================================================

void __watcall fade_palette(int param_1,int unaff_EDX,int unaff_EBX)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  __CHK(0x1c);
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
    if (param_1 == 0) {
      sub_76614(unaff_EDX);
    }
    else {
      _memset_fill(&unk_ec7e4,0,unaff_EBX,0x300);
      sub_76614(&unk_ec7e4);
      clearclip(0);
    }
  }
  else {
    byte_d122d = (char)iVar4 + -1;
    byte_d1230 = (char)iVar4 + '\x01';
    for (iVar1 = *(int *)(&unk_d1229 + param_1) >> 0x18;
        iVar1 != *(int *)(&byte_d122d + param_1) >> 0x18;
        iVar1 = iVar1 + (*(int *)(&unk_d122b + param_1) >> 0x18)) {
      iVar3 = 0;
      do {
        iVar2 = *(char *)(unaff_EDX + iVar3) * iVar1;
        (&unk_ec7e4)[iVar3] = (char)(iVar2 / iVar4);
        iVar3 = iVar3 + 1;
      } while (iVar3 < 0x300);
      sub_76614(&unk_ec7e4,iVar2 % iVar4);
    }
  }
  return;
}


// ================================================================================================
// sub_7651b @ 0x7651b [__watcall]
// ================================================================================================

void __watcall sub_7651b(int param_1,int unaff_EDX,int unaff_EBX)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  __CHK(0x1c);
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
    if (param_1 == 0) {
      sub_76614(unaff_EDX);
    }
    else {
      _memset_fill(&unk_ecae4,0,unaff_EBX,0x300);
      sub_76614(&unk_ecae4);
      clearclip(0);
    }
  }
  else {
    byte_d1233 = (char)iVar4 + -1;
    byte_d1236 = (char)iVar4 + '\x01';
    for (iVar1 = *(int *)(&unk_d122f + param_1) >> 0x18;
        iVar1 != *(int *)(&byte_d1233 + param_1) >> 0x18;
        iVar1 = iVar1 + (*(int *)(&unk_d1231 + param_1) >> 0x18)) {
      iVar3 = 0;
      do {
        iVar2 = *(char *)(unaff_EDX + iVar3) * iVar1;
        (&unk_ecae4)[iVar3] = (char)(iVar2 / iVar4);
        iVar3 = iVar3 + 1;
      } while (iVar3 < 0x300);
      sub_96218(0x2d,iVar2 % iVar4);
      sub_76614(&unk_ecae4);
    }
  }
  return;
}


// ================================================================================================
// sub_76614 @ 0x76614 [__watcall]
// ================================================================================================

void __watcall sub_76614(int param_1)

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
// sub_7665e @ 0x7665e [__watcall]
// ================================================================================================

undefined8 __watcall sub_7665e(byte *param_1,undefined4 unaff_EDX)

{
  ushort uVar1;
  byte bVar2;
  
  __CHK(0xc);
  if (*param_1 == 0) {
    *param_1 = 0x2b;
  }
  uVar1 = CONCAT11(*param_1 >> 1,*param_1) & 0xff01;
  bVar2 = (byte)(uVar1 >> 8);
  *param_1 = bVar2;
  if ((char)uVar1 != '\0') {
    *param_1 = bVar2 ^ 0xb8;
  }
  return CONCAT44(unaff_EDX,CONCAT31((int3)((uint)param_1 >> 8),*param_1));
}


// ================================================================================================
// sub_7668d @ 0x7668d [__watcall]
// ================================================================================================

void __watcall sub_7668d(int param_1,int unaff_EDX,int unaff_EBX,int unaff_ECX)

{
  __CHK(0x30);
  unaff_EBX = param_1 + unaff_EBX;
  unaff_ECX = unaff_EDX + unaff_ECX;
  if ((((param_1 < dword_ecde4) && (unaff_EDX < dword_ecde8)) && (dword_ecdf0 <= unaff_EBX)) &&
     (dword_ecdec <= unaff_ECX)) {
    if (param_1 < dword_ecdf0) {
      param_1 = dword_ecdf0;
    }
    if (unaff_EDX < dword_ecdec) {
      unaff_EDX = dword_ecdec;
    }
    if (dword_ecde4 < unaff_EBX) {
      unaff_EBX = dword_ecde4;
    }
    if (dword_ecde8 < unaff_ECX) {
      unaff_ECX = dword_ecde8;
    }
    unaff_EBX = unaff_EBX - param_1;
    unaff_ECX = unaff_ECX - unaff_EDX;
    setdefaultscreen();
    sub_8c218(dword_eda04 == 0,param_1,unaff_EDX,unaff_EBX,unaff_ECX,0);
  }
  return;
}


// ================================================================================================
// sub_76771 @ 0x76771 [__watcall]
// ================================================================================================

void __watcall sub_76771(int param_1,int unaff_EDX,undefined4 unaff_EBX)

{
  int iVar1;
  
  __CHK(0x28);
  iVar1 = textwidth(unaff_EBX);
  if (iVar1 + param_1 < 0x26c) {
    iVar1 = textwidth(unaff_EBX);
  }
  else {
    iVar1 = 0x26b - param_1;
  }
  fillrect(param_1,unaff_EDX + 2,iVar1,0xb,dword_d0b16);
  printstr_at(unaff_EBX,param_1,unaff_EDX);
  return;
}


// ================================================================================================
// edit_lines_screen_b @ 0x767d0 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall edit_lines_screen_b(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined *puVar4;
  int *piVar5;
  int local_58;
  undefined local_54 [32];
  
  __CHK(0x68);
  local_58 = 0x20;
  iVar1 = allocmem(&aPal_c3190,0x300);
  local_58 = iVar1;
  getpalette(0,0x100);
  local_58 = 0x76825;
  fade_palette(1,iVar1,0x10);
  local_58 = iVar1;
  freemem();
  if ((sound_enabled != '\0') && (dword_c721d != 0)) {
    local_58 = 0x76854;
    sound_fade(dword_d2431,3,0x32);
    do {
      local_58 = 0x76866;
      iVar1 = sound_channel_status(ram0x000d242c >> 0x18,3);
    } while (iVar1 == 0);
    local_58 = dword_c721d;
    releasememblock();
    dword_c721d = 0;
  }
  piVar5 = (int *)local_54;
  if ((sound_enabled != '\0') && (piVar5 = (int *)local_54, (option_flags._1_1_ & 1) != 0)) {
    piVar5 = &local_58;
    local_58 = 0x76898;
    sub_8373e();
    do {
      *(undefined4 *)((int)piVar5 + -4) = 0x7689d;
      iVar1 = sub_836e4();
    } while (iVar1 != 0);
  }
  *(undefined4 *)((int)piVar5 + -4) = 0x768a6;
  sub_479e9();
  *(undefined4 *)((int)piVar5 + 0x10) = dword_d0b16;
  *(undefined4 *)((int)piVar5 + 0x38) = dword_d0b1a;
  *(undefined4 *)((int)piVar5 + 0x3c) = dword_d0b1e;
  *(undefined4 *)((int)piVar5 + 0x28) = dword_d0b22;
  *(undefined4 *)((int)piVar5 + 0x24) = dword_d0b26;
  *(undefined4 *)((int)piVar5 + 0x1c) = dword_d0b2a;
  dword_d0b16 = 0xc1;
  dword_d0b1a = 0xc0;
  dword_d0b1e = 0xc1;
  dword_d0b22 = 0xc2;
  dword_d0b26 = 0xc3;
  dword_d0b2a = 0xc2;
  *(undefined4 *)((int)piVar5 + 0x18) = dword_c71cc;
  *(undefined4 *)((int)piVar5 + 0x14) = dword_c71d0;
  *(undefined4 *)((int)piVar5 + 0x34) = dword_c71d4;
  *(undefined4 *)((int)piVar5 + 0x30) = dword_c71d8;
  *(undefined4 *)((int)piVar5 + 0x2c) = dword_c71dc;
  dword_c71cc = 0xc1;
  dword_c71d0 = 0xc0;
  dword_c71d4 = 0xc1;
  dword_c71d8 = 0xc0;
  dword_c71dc = 0xc1;
  *(undefined4 *)((int)piVar5 + -4) = 0x76963;
  setdefaultscreen();
  *(undefined4 *)((int)piVar5 + -4) = 0x1e0;
  *(undefined4 *)((int)piVar5 + -8) = 0;
  *(undefined4 *)((int)piVar5 + -0xc) = 0x280;
  *(undefined4 *)((int)piVar5 + -0x10) = 0;
  *(undefined4 *)((int)piVar5 + -0x14) = 0x76976;
  setclip();
  *(undefined4 *)((int)piVar5 + -4) = 200;
  *(undefined4 *)((int)piVar5 + -8) = 0x140;
  *(undefined4 *)((int)piVar5 + -0xc) = 0x76988;
  setmousepos();
  puVar4 = install_path;
  if (byte_ed8b4 != '\x01') {
    puVar4 = (undefined *)0x0;
  }
  *(undefined4 *)((int)piVar5 + -4) = 0x769ac;
  make_path(piVar5,puVar4,aLineditp_c3194,0);
  *(undefined4 *)((int)piVar5 + -4) = 0;
  *(int **)((int)piVar5 + -8) = piVar5;
  *(undefined4 *)((int)piVar5 + -0xc) = 0x769b8;
  uVar2 = loadshapes();
  *(undefined5 **)((int)piVar5 + -4) = &aShrt_c319d;
  *(undefined4 *)((int)piVar5 + -8) = uVar2;
  *(undefined4 *)((int)piVar5 + -0xc) = 0x769c8;
  uVar3 = locateshape();
  *(undefined4 *)((int)piVar5 + -4) = 0x769d2;
  wait_sprite_fade();
  *(undefined4 *)((int)piVar5 + -4) = *(undefined4 *)((int)piVar5 + 0x40);
  *(undefined4 *)((int)piVar5 + -8) = 0x769e6;
  draw_lines_screen(param_1,uVar3,0,*(undefined4 *)((int)piVar5 + 0x44));
  *(undefined4 *)((int)piVar5 + -4) = 0x769ed;
  edit_lines_keys(param_1);
  *(undefined4 *)((int)piVar5 + -4) = 0x76a06;
  sub_9244c(&unk_ed0f4,0x1c,0x16);
  *(undefined4 *)((int)piVar5 + -4) = uVar2;
  *(undefined4 *)((int)piVar5 + -8) = *(undefined4 *)((int)piVar5 + 0x40);
  *(undefined4 *)((int)piVar5 + -0xc) = *(undefined4 *)((int)piVar5 + 0x44);
  *(undefined4 *)((int)piVar5 + -0x10) = 0x76a20;
  edit_lines_screen2(*(undefined4 *)((int)piVar5 + 0x20),uVar3,param_1,0);
  *(undefined4 *)((int)piVar5 + -4) = uVar2;
  *(undefined4 *)((int)piVar5 + -8) = 0x76a26;
  freemem();
  dword_d0b16 = *(undefined4 *)((int)piVar5 + 0x10);
  dword_d0b1a = *(undefined4 *)((int)piVar5 + 0x38);
  dword_d0b1e = *(undefined4 *)((int)piVar5 + 0x3c);
  dword_d0b22 = *(undefined4 *)((int)piVar5 + 0x28);
  dword_d0b26 = *(undefined4 *)((int)piVar5 + 0x24);
  dword_d0b2a = *(undefined4 *)((int)piVar5 + 0x1c);
  dword_c71cc = *(undefined4 *)((int)piVar5 + 0x18);
  dword_c71d0 = *(undefined4 *)((int)piVar5 + 0x14);
  dword_c71d4 = *(undefined4 *)((int)piVar5 + 0x34);
  dword_c71d8 = *(undefined4 *)((int)piVar5 + 0x30);
  dword_c71dc = *(undefined4 *)((int)piVar5 + 0x2c);
  return;
}


// ================================================================================================
// sub_76a93 @ 0x76a93 [__watcall]
// ================================================================================================

int __watcall sub_76a93(char *param_1,char *unaff_EDX)

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
// edit_lines_screen2 @ 0x76af5 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __watcall
edit_lines_screen2(int param_1,int **param_2,byte unaff_BL,undefined4 param_4,int *param_5,
                  undefined4 param_6,undefined4 param_7)

{
  byte bVar1;
  undefined uVar2;
  char cVar3;
  code *pcVar4;
  int iVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  int iVar10;
  short sVar11;
  int **ppiVar12;
  int *piVar13;
  int iVar14;
  int *piVar15;
  int **ppiVar16;
  undefined4 *puVar17;
  uint uVar18;
  undefined4 uVar19;
  undefined *puVar20;
  int **ppiVar21;
  undefined *puVar22;
  undefined4 *puVar23;
  int iVar24;
  undefined4 *puVar25;
  undefined4 *puVar26;
  byte bVar27;
  ulonglong uVar28;
  char acStack_124 [12];
  char acStack_118 [6];
  char acStack_112 [10];
  char acStack_108 [8];
  char acStack_100 [4];
  int aiStack_fc [10];
  undefined auStack_d4 [32];
  undefined auStack_b4 [16];
  int local_a4 [12];
  int *local_74;
  int local_70;
  undefined4 local_6c;
  undefined4 local_68;
  int local_64;
  int local_60;
  int local_5c;
  int local_58;
  int *local_54;
  int **local_50;
  int local_4c;
  undefined4 *local_48;
  int local_44;
  int local_40;
  int **local_3c;
  int local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 *local_28;
  int local_24;
  int local_20;
  int local_1c;
  undefined local_18;
  undefined local_14;
  byte local_10;
  
  bVar27 = 0;
  __CHK(0x148);
  local_1c = 0;
  local_60 = -1;
  local_64 = -1;
  local_34 = 0xc0;
  local_2c = 0xc1;
  local_30 = 0xc2;
  local_10 = unaff_BL;
  local_48 = (undefined4 *)locateshape(param_7,&aPntr_c31a2);
  local_74 = param_5;
  local_a4[4] = param_6;
  local_68 = 0;
  local_6c = 0;
  local_70 = 0;
  local_a4[3] = 0;
  local_a4[2] = 0;
  local_a4[1] = 0;
  local_a4[0] = 0;
  local_a4[0xb] = 0;
  local_a4[10] = 0;
  local_a4[9] = 0;
  local_a4[8] = 0;
  aiStack_fc[3] = 0;
  aiStack_fc[2] = 0;
  funcptr_cf2c3 = (undefined *)0x0;
  funcptr_cf2a3 = (undefined *)0x0;
  local_28 = (undefined4 *)
             allocmem(aPointer_c31a7,
                      (((int)local_48[1] >> 0x10) + 1) * ((*(int *)((int)local_48 + 2) >> 0x10) + 1)
                      + 0x11,0x20);
  puVar25 = local_28 + (uint)bVar27 * -2 + 1;
  puVar17 = local_48 + (uint)bVar27 * -2 + 1;
  *local_28 = *local_48;
  puVar26 = puVar25 + (uint)bVar27 * -2 + 1;
  puVar23 = puVar17 + (uint)bVar27 * -2 + 1;
  *puVar25 = *puVar17;
  *puVar26 = *puVar23;
  puVar26[(uint)bVar27 * -2 + 1] = puVar23[(uint)bVar27 * -2 + 1];
  *(undefined *)(puVar26 + (uint)bVar27 * -2 + 1 + (uint)bVar27 * -2 + 1) =
       *(undefined *)(puVar23 + (uint)bVar27 * -2 + 1 + (uint)bVar27 * -2 + 1);
  *(short *)(local_28 + 1) = *(short *)(local_48 + 1) + 1;
  *(short *)((int)local_28 + 6) = *(short *)((int)local_48 + 6) + 1;
  ppiVar12 = (int **)((*local_74 + local_74[2]) / 2);
  piVar13 = (int *)((local_74[1] + local_74[3]) / 2);
  funcptr_cf443 = lines_teams_b;
  funcptr_cf363 = sub_79188;
  funcptr_cf223 = sub_79188;
  funcptr_cf3c3 = lines_teams_a;
  funcptr_cf283 = lines_teams_a;
  local_4c = 0;
  do {
    if (*(char *)(param_1 + local_4c) == 'd') {
      funcptr_cf443 = (undefined *)0x0;
      funcptr_cf363 = (undefined *)0x0;
      funcptr_cf223 = (undefined *)0x0;
      funcptr_cf3c3 = (undefined *)0x0;
      funcptr_cf283 = (undefined *)0x0;
      break;
    }
    local_4c = local_4c + 1;
  } while (local_4c < 0x28);
  local_4c = 0;
  local_54 = piVar13;
  local_50 = ppiVar12;
  do {
    if (*(byte *)(param_1 + local_4c) == 100) {
      acStack_124[local_4c] = 'd';
    }
    else {
      acStack_124[local_4c] =
           (&unk_db3ad)[(uint)local_10 * 0x444 + (uint)*(byte *)(param_1 + local_4c) * 0x27];
    }
    local_4c = local_4c + 1;
  } while (local_4c < 0x28);
  if (_period_num < 0) {
    local_4c = 0;
    do {
      bVar1 = *(byte *)(param_1 + local_4c + 0x28);
      if ((bVar1 != 100) &&
         (iVar14 = (uint)local_10 * 0x444 + (uint)bVar1 * 0x27, (&rosters)[iVar14] == '\x03')) {
        (&rosters)[iVar14] = 2;
      }
      local_4c = local_4c + 1;
    } while (local_4c < 8);
  }
  local_3c = (int **)allocmem(&aPal_c3190,0x300,0x20);
  puVar22 = &stack0xfffffed4;
  puVar20 = install_path;
  if (byte_ed85a != '\x01') {
    puVar20 = (undefined *)0x0;
  }
  make_path(auStack_b4,puVar20,aEmbpal_c31af,0);
  local_48 = (undefined4 *)loadshapes(auStack_b4,0);
  iVar14 = locateshape(local_48,&aPal_c31b6);
  memcpy(local_3c,(void *)(iVar14 + 0x10),0x300);
  freemem(local_48);
  load_homepals(local_10,param_7,local_3c);
  sVar11 = user2_team._2_2_;
  if (local_10 != 0) {
    sVar11 = _away_team_id;
  }
  local_14 = (&unk_d1238)[(byte)(&unk_d11bc)[sVar11 * 4]];
  local_18 = byte_d12de;
  sub_78366(acStack_124,param_2,local_10);
  puVar20 = install_path;
  if (byte_ed9e7 != '\x01') {
    puVar20 = (undefined *)0x0;
  }
  make_path(auStack_b4,puVar20,aLelogo_c31bb,0);
  local_48 = (undefined4 *)loadshapes(auStack_b4,0);
  iVar14 = locateshape(local_48,&aPal_c31b6);
  memcpy((void *)((int)local_3c + 0x25e),(void *)(iVar14 + 0x26e),0x93);
  freemem(local_48);
  fade_palette(0,local_3c,0x10);
  ppiVar21 = local_3c;
  freemem(local_3c);
  if ((int)piVar13 < 0x20) {
    piVar15 = (int *)0x0;
  }
  else {
    piVar15 = piVar13 + -8;
  }
  if ((int)ppiVar12 < 0x1c) {
    ppiVar16 = (int **)0x0;
  }
  else {
    ppiVar16 = ppiVar12 + -7;
  }
  grabshape(local_28,ppiVar16,piVar15);
  drawshape_trans(pointer_shapes,(int)ppiVar12 + -3,piVar13);
  setmouselimits(0,0,0x280,0x1e0);
  setmousepos(ppiVar12,piVar13);
  getmouse(&local_4c,&local_4c,&local_4c);
  uVar28 = event_queue_reset();
LAB_0007704c:
  uVar18 = 0;
  do {
    *(undefined4 *)(puVar22 + -4) = 0x77053;
    uVar28 = event_queue_pop((int)uVar28,(int)(uVar28 >> 0x20),ppiVar21);
    if ((int)uVar28 == 0) break;
    ppiVar21 = &local_54;
    *(undefined4 *)(puVar22 + -4) = 0x77063;
    uVar28 = (*ui_poll_callback)();
    uVar18 = (uint)uVar28;
  } while ((uVar28 & 2) == 0);
  if ((uVar18 & 2) == 0) goto code_r0x0007706e;
  *(int **)(puVar22 + -4) = &local_5c;
  *(int **)(puVar22 + -8) = &local_58;
  *(int **)(puVar22 + -0xc) = aiStack_fc + 2;
  *(int **)(puVar22 + -0x10) = local_a4 + 4;
  *(undefined4 *)(puVar22 + -0x14) = 0x770a9;
  iVar14 = hit_test_menus(local_50,local_54,&local_74,local_1c);
  piVar15 = piVar13 + -8;
  if (iVar14 == 0) {
    if ((int)piVar13 < 0x20) {
      piVar15 = (int *)0x0;
    }
    *(int **)(puVar22 + -4) = piVar15;
    if ((int)ppiVar12 < 0x1c) {
      ppiVar12 = (int **)0x0;
    }
    else {
      ppiVar12 = ppiVar12 + -7;
    }
    *(int ***)(puVar22 + -8) = ppiVar12;
    *(undefined4 **)(puVar22 + -0xc) = local_28;
    *(undefined4 *)(puVar22 + -0x10) = 0x77529;
    drawshape();
    for (local_4c = 3; -1 < local_4c; local_4c = local_4c + -1) {
      iVar14 = local_a4[local_4c];
      if (iVar14 != 0) {
        *(int *)(puVar22 + -4) = aiStack_fc[local_4c * 2 + 3];
        *(int *)(puVar22 + -8) = aiStack_fc[local_4c * 2 + 2];
        *(int *)(puVar22 + -0xc) = iVar14;
        *(undefined4 *)(puVar22 + -0x10) = 0x77552;
        drawshape();
        iVar14 = local_4c;
        aiStack_fc[local_4c * 2 + 3] = 0;
        aiStack_fc[iVar14 * 2 + 2] = 0;
        *(int *)(puVar22 + -4) = local_a4[iVar14];
        *(undefined4 *)(puVar22 + -8) = 0x7756c;
        freemem();
      }
    }
    iVar24 = 0;
    local_1c = 0;
    local_68 = 0;
    local_6c = 0;
    local_70 = 0;
    local_a4[2] = 0;
    local_a4[1] = 0;
    local_a4[0] = 0;
    local_a4[0xb] = 0;
    local_a4[10] = 0;
    local_a4[9] = 0;
    local_a4[7] = 0;
    local_a4[6] = 0;
    local_a4[5] = 0;
    *(undefined4 *)(puVar22 + -4) = 0x775b0;
    iVar14 = sub_77f6f(local_50,local_54,&local_64);
    if (iVar14 != 0) {
      if (((local_64 < 100) && (local_60 != -1)) &&
         ((&rosters)[(uint)local_10 * 0x444 + (uint)(byte)(&unk_ed0f6)[local_60 * 0x16] * 0x27] !=
          '\x02')) {
        *(undefined4 *)(puVar22 + -4) = 0xc1;
        *(undefined4 *)(puVar22 + -8) = 0xc0;
        *(undefined4 *)(puVar22 + -0xc) = 0x7761d;
        settextpos();
        iVar14 = local_60 * 0x16;
        if (local_64 < 0xc) {
          cVar3 = (&unk_ed0f4)[iVar14];
          if (((cVar3 == 'C') || (cVar3 == 'L')) || (cVar3 == 'R')) {
            local_4c = local_64 / 3;
            iVar14 = 0;
            do {
              iVar24 = local_4c * 3 + iVar14;
              if (acStack_124[iVar24] == (&unk_ed0f5)[local_60 * 0x16]) {
                acStack_124[iVar24] = 'd';
              }
              iVar14 = iVar14 + 1;
            } while (iVar14 < 3);
            acStack_124[local_64 % 3 + local_4c * 3] = (&unk_ed0f5)[local_60 * 0x16];
            iVar14 = 0;
            do {
              cVar3 = acStack_124[local_4c * 3 + iVar14];
              *(undefined4 *)(puVar22 + -4) = 0x7770a;
              sub_7a099(&unk_d1238,cVar3,local_14,local_18);
              *(undefined1 **)(puVar22 + -4) = &unk_d1238;
              *(undefined4 *)(puVar22 + -8) = 0x77714;
              setremaptable();
              iVar24 = local_4c * 3 + iVar14;
              *(undefined4 *)(puVar22 + -4) = (&unk_d133c)[iVar24 * 2];
              *(undefined4 *)(puVar22 + -8) = (&unk_d1338)[iVar24 * 2];
              *(int ***)(puVar22 + -0xc) = param_2;
              *(undefined4 *)(puVar22 + -0x10) = 0x7773f;
              drawshape2_trans();
              iVar14 = iVar14 + 1;
            } while (iVar14 < 3);
          }
        }
        else if (local_64 < 0x12) {
          if ((&unk_ed0f4)[iVar14] == 'D') {
            local_4c = (local_64 + -0xc) / 2;
            do {
              iVar14 = local_4c * 2 + iVar24;
              if (acStack_118[iVar14] == (&unk_ed0f5)[local_60 * 0x16]) {
                acStack_118[iVar14] = 'd';
              }
              iVar24 = iVar24 + 1;
            } while (iVar24 < 2);
            acStack_118[(local_64 + -0xc) % 2 + local_4c * 2] = (&unk_ed0f5)[local_60 * 0x16];
            iVar14 = 0;
            do {
              cVar3 = acStack_118[local_4c * 2 + iVar14];
              *(undefined4 *)(puVar22 + -4) = 0x77805;
              sub_7a099(&unk_d1238,cVar3,local_14,local_18);
              *(undefined1 **)(puVar22 + -4) = &unk_d1238;
              *(undefined4 *)(puVar22 + -8) = 0x7780f;
              setremaptable();
              iVar24 = local_4c * 2 + iVar14;
              *(undefined4 *)(puVar22 + -4) = *(undefined4 *)(&unk_d139c + iVar24 * 8);
              *(undefined4 *)(puVar22 + -8) = *(undefined4 *)(&unk_d1398 + iVar24 * 8);
              *(int ***)(puVar22 + -0xc) = param_2;
              *(undefined4 *)(puVar22 + -0x10) = 0x77835;
              drawshape2_trans();
              iVar14 = iVar14 + 1;
            } while (iVar14 < 2);
          }
        }
        else if (local_64 < 0x1c) {
          if ((&unk_ed0f4)[iVar14] != 'G') {
            local_4c = (local_64 + -0x12) / 5;
            do {
              iVar14 = local_4c * 5 + iVar24;
              if (acStack_112[iVar14] == (&unk_ed0f5)[local_60 * 0x16]) {
                acStack_112[iVar14] = 'd';
              }
              iVar24 = iVar24 + 1;
            } while (iVar24 < 5);
            acStack_112[(local_64 + -0x12) % 5 + local_4c * 5] = (&unk_ed0f5)[local_60 * 0x16];
            iVar14 = 0;
            do {
              cVar3 = acStack_112[local_4c * 5 + iVar14];
              *(undefined4 *)(puVar22 + -4) = 0x7790f;
              sub_7a099(&unk_d1238,cVar3,local_14,local_18);
              *(undefined1 **)(puVar22 + -4) = &unk_d1238;
              *(undefined4 *)(puVar22 + -8) = 0x77919;
              setremaptable();
              iVar24 = local_4c * 5 + iVar14;
              *(undefined4 *)(puVar22 + -4) = *(undefined4 *)(&unk_d13cc + iVar24 * 8);
              *(undefined4 *)(puVar22 + -8) = *(undefined4 *)(&unk_d13c8 + iVar24 * 8);
              *(int ***)(puVar22 + -0xc) = param_2;
              *(undefined4 *)(puVar22 + -0x10) = 0x77944;
              drawshape2_trans();
              iVar14 = iVar14 + 1;
            } while (iVar14 < 5);
          }
        }
        else if (local_64 < 0x24) {
          if ((&unk_ed0f4)[iVar14] != 'G') {
            iVar14 = local_64 + -0x1c >> 0x1f;
            local_4c = (int)((local_64 + -0x1c + iVar14 * -4) - (uint)(iVar14 << 1 < 0)) >> 2;
            do {
              iVar14 = local_4c * 4 + iVar24;
              if (acStack_108[iVar14] == (&unk_ed0f5)[local_60 * 0x16]) {
                acStack_108[iVar14] = 'd';
              }
              iVar24 = iVar24 + 1;
            } while (iVar24 < 4);
            acStack_108[(local_64 + -0x1c) % 4 + local_4c * 4] = (&unk_ed0f5)[local_60 * 0x16];
            iVar14 = 0;
            do {
              cVar3 = acStack_108[local_4c * 4 + iVar14];
              *(undefined4 *)(puVar22 + -4) = 0x77a11;
              sub_7a099(&unk_d1238,cVar3,local_14,local_18);
              *(undefined1 **)(puVar22 + -4) = &unk_d1238;
              *(undefined4 *)(puVar22 + -8) = 0x77a1b;
              setremaptable();
              iVar24 = local_4c * 4 + iVar14;
              *(undefined4 *)(puVar22 + -4) = *(undefined4 *)(&unk_d141c + iVar24 * 8);
              *(undefined4 *)(puVar22 + -8) = *(undefined4 *)(&unk_d1418 + iVar24 * 8);
              *(int ***)(puVar22 + -0xc) = param_2;
              *(undefined4 *)(puVar22 + -0x10) = 0x77a42;
              drawshape2_trans();
              iVar14 = iVar14 + 1;
            } while (iVar14 < 4);
          }
        }
        else if (local_64 < 0x26) {
          if ((&unk_ed0f4)[iVar14] == 'G') {
            do {
              if (acStack_100[iVar24] == (&unk_ed0f5)[local_60 * 0x16]) {
                acStack_100[iVar24] = 'd';
              }
              iVar24 = iVar24 + 1;
            } while (iVar24 < 2);
            acStack_124[local_64] = (&unk_ed0f5)[local_60 * 0x16];
            iVar14 = 0;
            do {
              cVar3 = acStack_100[iVar14];
              *(undefined4 *)(puVar22 + -4) = 0x77aca;
              sub_7a099(&unk_d1238,cVar3,local_14,local_18);
              *(undefined1 **)(puVar22 + -4) = &unk_d1238;
              *(undefined4 *)(puVar22 + -8) = 0x77ad4;
              setremaptable();
              *(undefined4 *)(puVar22 + -4) = (&unk_d145c)[iVar14 * 2];
              *(undefined4 *)(puVar22 + -8) = (&unk_d1458)[iVar14 * 2];
              *(int ***)(puVar22 + -0xc) = param_2;
              *(undefined4 *)(puVar22 + -0x10) = 0x77af3;
              drawshape2_trans();
              iVar14 = iVar14 + 1;
            } while (iVar14 < 2);
          }
        }
        else if ((&unk_ed0f4)[iVar14] != 'G') {
          do {
            if (acStack_100[iVar24 + 2] == (&unk_ed0f5)[local_60 * 0x16]) {
              acStack_100[iVar24 + 2] = 'd';
            }
            iVar24 = iVar24 + 1;
          } while (iVar24 < 2);
          acStack_124[local_64] = (&unk_ed0f5)[local_60 * 0x16];
          iVar14 = 0;
          do {
            cVar3 = acStack_100[iVar14 + 2];
            *(undefined4 *)(puVar22 + -4) = 0x77b72;
            sub_7a099(&unk_d1238,cVar3,local_14,local_18);
            *(undefined1 **)(puVar22 + -4) = &unk_d1238;
            *(undefined4 *)(puVar22 + -8) = 0x77b7c;
            setremaptable();
            *(undefined4 *)(puVar22 + -4) = (&unk_d146c)[iVar14 * 2];
            *(undefined4 *)(puVar22 + -8) = (&unk_d1468)[iVar14 * 2];
            *(int ***)(puVar22 + -0xc) = param_2;
            *(undefined4 *)(puVar22 + -0x10) = 0x77b9b;
            drawshape2_trans();
            iVar14 = iVar14 + 1;
          } while (iVar14 < 2);
        }
        funcptr_cf443 = lines_teams_b;
        funcptr_cf363 = sub_79188;
        funcptr_cf223 = sub_79188;
        funcptr_cf3c3 = lines_teams_a;
        funcptr_cf283 = lines_teams_a;
        local_4c = 0;
        do {
          if (acStack_124[local_4c] == 'd') {
            funcptr_cf443 = (undefined *)0x0;
            funcptr_cf363 = (undefined *)0x0;
            funcptr_cf223 = (undefined *)0x0;
            funcptr_cf3c3 = (undefined *)0x0;
            funcptr_cf283 = (undefined *)0x0;
            break;
          }
          local_4c = local_4c + 1;
        } while (local_4c < 0x28);
      }
      else if (99 < local_64) {
        local_64 = local_64 + -100;
        cVar3 = (&rosters)
                [(uint)local_10 * 0x444 + (uint)(byte)(&unk_ed0f6)[local_64 * 0x16] * 0x27];
        if ((cVar3 != '\0') &&
           (((cVar3 == '\x04' || (cVar3 == '\x03')) || ((cVar3 == '\x02' && (_period_num < 0)))))) {
          if (local_60 != -1) {
            if ((&rosters)
                [(uint)local_10 * 0x444 + (uint)(byte)(&unk_ed0f6)[local_60 * 0x16] * 0x27] ==
                '\x02') {
              *(undefined4 *)(puVar22 + -4) = 0xc1;
              *(undefined4 *)(puVar22 + -8) = 0xfc;
            }
            else {
              *(undefined4 *)(puVar22 + -4) = 0xc1;
              *(undefined4 *)(puVar22 + -8) = 0xc3;
            }
            *(undefined4 *)(puVar22 + -0xc) = 0x77cf3;
            settextpos();
            iVar14 = local_60 * 0x16;
            *(undefined **)(puVar22 + -4) = &unk_ed0f7 + iVar14;
            *(uint *)(puVar22 + -8) = (uint)(byte)(&unk_ed0f5)[iVar14];
            *(uint *)(puVar22 + -0xc) = (uint)(byte)(&unk_ed0f4)[iVar14];
            *(char **)(puVar22 + -0x10) = aC2dS_c31cb;
            *(undefined **)(puVar22 + -0x14) = auStack_d4;
            *(undefined4 *)(puVar22 + -0x18) = 0x77d35;
            sprintf(*(char **)(puVar22 + -0x14),*(char **)(puVar22 + -0x10));
            *(undefined4 *)(puVar22 + -4) = 0x77d57;
            sub_76771(0x1fa,local_60 * 0xd + 0x16,auStack_d4);
          }
          local_60 = local_64;
          funcptr_cf2a3 = sub_79f41;
          funcptr_cf2c3 = sub_79de1;
          if ((&rosters)[(uint)local_10 * 0x444 + (uint)(byte)(&unk_ed0f6)[local_64 * 0x16] * 0x27]
              == '\x02') {
            *(undefined4 *)(puVar22 + -4) = 0xc1;
            *(undefined4 *)(puVar22 + -8) = 0xfd;
          }
          else {
            *(undefined4 *)(puVar22 + -4) = 0xc1;
            *(undefined4 *)(puVar22 + -8) = 0xc0;
          }
          *(undefined4 *)(puVar22 + -0xc) = 0x77dcb;
          settextpos();
          iVar14 = local_60 * 0x16;
          *(undefined **)(puVar22 + -4) = &unk_ed0f7 + iVar14;
          *(uint *)(puVar22 + -8) = (uint)(byte)(&unk_ed0f5)[iVar14];
          *(uint *)(puVar22 + -0xc) = (uint)(byte)(&unk_ed0f4)[iVar14];
          *(char **)(puVar22 + -0x10) = aC2dS_c31cb;
          *(undefined **)(puVar22 + -0x14) = auStack_d4;
          *(undefined4 *)(puVar22 + -0x18) = 0x77e0d;
          sprintf(*(char **)(puVar22 + -0x14),*(char **)(puVar22 + -0x10));
          *(undefined4 *)(puVar22 + -4) = 0x77e2f;
          sub_76771(0x1fa,local_60 * 0xd + 0x16,auStack_d4);
        }
      }
    }
  }
  else {
    local_38 = local_5c * 0x20;
    if ((&local_74)[local_58][local_5c * 8 + 5] == 0) {
      if ((&local_74)[local_58][local_5c * 8 + 6] == 0) {
        if ((int)piVar13 < 0x20) {
          piVar15 = (int *)0x0;
        }
        *(int **)(puVar22 + -4) = piVar15;
        if ((int)ppiVar12 < 0x1c) {
          ppiVar12 = (int **)0x0;
        }
        else {
          ppiVar12 = ppiVar12 + -7;
        }
        *(int ***)(puVar22 + -8) = ppiVar12;
        *(undefined4 **)(puVar22 + -0xc) = local_28;
        *(undefined4 *)(puVar22 + -0x10) = 0x774b3;
        drawshape();
        uVar6 = local_2c;
        uVar19 = local_30;
        *(undefined4 *)(puVar22 + -4) = local_30;
        *(undefined4 *)(puVar22 + -8) = local_2c;
        iVar14 = aiStack_fc[local_58 * 2 + 3];
        iVar24 = aiStack_fc[local_58 * 2 + 2];
        iVar5 = local_a4[local_58 + 8];
        piVar13 = (&local_74)[local_58];
        *(undefined4 *)(puVar22 + -0xc) = 0x774de;
        highlight_menu_item(piVar13 + iVar5 * 8,iVar24,iVar14,local_34);
        iVar5 = local_58;
        local_a4[local_58 + 8] = local_5c;
        *(undefined4 *)(puVar22 + -4) = uVar19;
        *(undefined4 *)(puVar22 + -8) = uVar6;
        iVar14 = aiStack_fc[iVar5 * 2 + 3];
        iVar24 = aiStack_fc[iVar5 * 2 + 2];
        piVar13 = (&local_74)[iVar5] + local_a4[iVar5 + 8] * 8;
        uVar19 = local_34;
      }
      else {
        if ((int)piVar13 < 0x20) {
          piVar15 = (int *)0x0;
        }
        *(int **)(puVar22 + -4) = piVar15;
        if ((int)ppiVar12 < 0x1c) {
          ppiVar12 = (int **)0x0;
        }
        else {
          ppiVar12 = ppiVar12 + -7;
        }
        *(int ***)(puVar22 + -8) = ppiVar12;
        *(undefined4 **)(puVar22 + -0xc) = local_28;
        *(undefined4 *)(puVar22 + -0x10) = 0x77273;
        drawshape();
        if (local_1c != local_58) {
          for (local_4c = local_1c; iVar14 = local_4c, local_58 < local_4c; local_4c = local_4c + -1
              ) {
            local_a4[local_4c + 8] = 0;
            if (local_a4[iVar14] != 0) {
              *(int *)(puVar22 + -4) = aiStack_fc[local_4c * 2 + 3];
              *(int *)(puVar22 + -8) = aiStack_fc[local_4c * 2 + 2];
              *(int *)(puVar22 + -0xc) = local_a4[iVar14];
              *(undefined4 *)(puVar22 + -0x10) = 0x772aa;
              drawshape();
              iVar14 = local_4c;
              aiStack_fc[local_4c * 2 + 3] = 0;
              aiStack_fc[iVar14 * 2 + 2] = 0;
              *(int *)(puVar22 + -4) = local_a4[iVar14];
              *(undefined4 *)(puVar22 + -8) = 0x772c2;
              freemem();
              iVar14 = local_4c;
              local_a4[local_4c] = 0;
              (&local_74)[iVar14] = (int *)0x0;
              local_a4[iVar14 + 4] = 0;
            }
          }
          local_1c = local_58;
        }
        iVar10 = local_1c;
        *(undefined4 *)(puVar22 + -4) = local_30;
        *(undefined4 *)(puVar22 + -8) = local_2c;
        iVar14 = aiStack_fc[local_1c * 2 + 3];
        iVar24 = aiStack_fc[local_1c * 2 + 2];
        iVar5 = local_a4[local_1c + 8];
        piVar13 = (&local_74)[local_1c];
        *(undefined4 *)(puVar22 + -0xc) = 0x7730c;
        highlight_menu_item(piVar13 + iVar5 * 8,iVar24,iVar14,local_34);
        local_a4[iVar10 + 8] = local_5c;
        *(undefined4 *)(puVar22 + -4) = local_30;
        *(undefined4 *)(puVar22 + -8) = local_2c;
        iVar14 = aiStack_fc[iVar10 * 2 + 3];
        iVar24 = aiStack_fc[iVar10 * 2 + 2];
        piVar13 = (&local_74)[iVar10];
        *(undefined4 *)(puVar22 + -0xc) = 0x77337;
        unhighlight_menu_item(piVar13 + local_5c * 8,iVar24,iVar14,local_34);
        iVar5 = local_58;
        iVar24 = local_5c;
        iVar14 = iVar10 + 1;
        local_1c = iVar14;
        (&local_74)[iVar14] = (int *)(&local_74)[local_58][local_5c * 8 + 6];
        piVar13 = (&local_74)[iVar5] + iVar24 * 8;
        local_a4[iVar10 + 5] = piVar13[7];
        if (iVar14 == 1) {
          iVar14 = *piVar13;
        }
        else {
          iVar14 = piVar13[2];
        }
        aiStack_fc[local_1c * 2 + 2] = iVar14 + *(int *)(acStack_100 + local_1c * 8 + 4);
        if (local_1c == 1) {
          iVar14 = (&local_74)[local_58][local_5c * 8 + 3];
        }
        else {
          iVar14 = (&local_74)[local_58][local_5c * 8 + 1];
        }
        local_24 = local_1c * 8;
        aiStack_fc[local_1c * 2 + 3] = iVar14 + aiStack_fc[local_1c * 2 + 1];
        local_20 = local_1c * 4;
        piVar13 = (&local_74)[local_1c];
        local_40 = (piVar13[local_a4[local_1c + 4] * 8 + -6] - *piVar13) + 1;
        local_44 = (piVar13[local_a4[local_1c + 4] * 8 + -5] - piVar13[1]) + 1;
        *(undefined4 *)(puVar22 + -4) = 0x20;
        *(int *)(puVar22 + -8) = local_40 * local_44 + 0x11;
        *(char **)(puVar22 + -0xc) = aMenubuff_c31c2;
        *(undefined4 *)(puVar22 + -0x10) = 0x773ee;
        puVar17 = (undefined4 *)allocmem();
        iVar14 = local_20;
        *(undefined4 **)((int)local_a4 + local_20) = puVar17;
        puVar23 = puVar17 + (uint)bVar27 * -2 + 1;
        ppiVar12 = pointer_shapes + (uint)bVar27 * -2 + 1;
        *puVar17 = *pointer_shapes;
        puVar17 = puVar23 + (uint)bVar27 * -2 + 1;
        ppiVar21 = ppiVar12 + (uint)bVar27 * -2 + 1;
        *puVar23 = *ppiVar12;
        *puVar17 = *ppiVar21;
        puVar17[(uint)bVar27 * -2 + 1] = ppiVar21[(uint)bVar27 * -2 + 1];
        *(undefined *)(puVar17 + (uint)bVar27 * -2 + 1 + (uint)bVar27 * -2 + 1) =
             *(undefined *)(ppiVar21 + (uint)bVar27 * -2 + 1 + (uint)bVar27 * -2 + 1);
        *(short *)(*(int *)((int)local_a4 + iVar14) + 4) = (short)local_40;
        *(short *)(*(int *)((int)local_a4 + local_20) + 6) = (short)local_44;
        *(undefined4 *)(puVar22 + -4) = *(undefined4 *)((int)aiStack_fc + local_24 + 0xc);
        *(undefined4 *)(puVar22 + -8) = *(undefined4 *)((int)aiStack_fc + local_24 + 8);
        *(undefined4 *)(puVar22 + -0xc) = *(undefined4 *)((int)local_a4 + local_20);
        *(undefined4 *)(puVar22 + -0x10) = 0x77438;
        grabshape();
        uVar19 = local_34;
        *(undefined4 *)(puVar22 + -4) = local_30;
        *(undefined4 *)(puVar22 + -8) = local_2c;
        *(undefined4 *)(puVar22 + -0xc) = local_34;
        uVar6 = *(undefined4 *)((int)aiStack_fc + local_24 + 0xc);
        uVar7 = *(undefined4 *)((int)aiStack_fc + local_24 + 8);
        uVar8 = *(undefined4 *)((int)local_a4 + local_20 + 0x10);
        uVar9 = *(undefined4 *)((int)&local_74 + local_20);
        *(undefined4 *)(puVar22 + -0x10) = 0x77468;
        draw_menu(uVar9,uVar8,uVar7,uVar6);
        *(undefined4 *)((int)local_a4 + local_20 + 0x20) = 0;
        *(undefined4 *)(puVar22 + -4) = local_30;
        *(undefined4 *)(puVar22 + -8) = local_2c;
        iVar14 = *(int *)((int)aiStack_fc + local_24 + 0xc);
        iVar24 = *(int *)((int)aiStack_fc + local_24 + 8);
        piVar13 = *(int **)((int)&local_74 + local_20);
      }
    }
    else {
      if (local_5c == local_a4[local_58 + 8]) {
        if ((int)piVar13 < 0x20) {
          piVar15 = (int *)0x0;
        }
        *(int **)(puVar22 + -4) = piVar15;
        if ((int)ppiVar12 < 0x1c) {
          ppiVar12 = (int **)0x0;
        }
        else {
          ppiVar12 = ppiVar12 + -7;
        }
        *(int ***)(puVar22 + -8) = ppiVar12;
        *(undefined4 **)(puVar22 + -0xc) = local_28;
        *(undefined4 *)(puVar22 + -0x10) = 0x770ff;
        drawshape();
        for (local_4c = 3; -1 < local_4c; local_4c = local_4c + -1) {
          iVar14 = local_a4[local_4c];
          if (iVar14 != 0) {
            *(int *)(puVar22 + -4) = aiStack_fc[local_4c * 2 + 3];
            *(int *)(puVar22 + -8) = aiStack_fc[local_4c * 2 + 2];
            *(int *)(puVar22 + -0xc) = iVar14;
            *(undefined4 *)(puVar22 + -0x10) = 0x77128;
            drawshape();
            iVar14 = local_4c;
            aiStack_fc[local_4c * 2 + 3] = 0;
            aiStack_fc[iVar14 * 2 + 2] = 0;
            *(int *)(puVar22 + -4) = local_a4[iVar14];
            *(undefined4 *)(puVar22 + -8) = 0x77142;
            freemem();
          }
        }
        local_1c = 0;
        piVar13 = (&local_74)[local_58];
        *(int ***)(puVar22 + -4) = &local_54;
        *(int ****)(puVar22 + -8) = &local_50;
        *(undefined4 *)(puVar22 + -0xc) = param_6;
        *(int **)(puVar22 + -0x10) = param_5;
        *(undefined4 *)(puVar22 + -0x14) = 0;
        *(int ***)(puVar22 + -0x18) = param_2;
        pcVar4 = (code *)piVar13[local_5c * 8 + 5];
        *(undefined4 *)(puVar22 + -0x1c) = 0x77198;
        iVar14 = (*pcVar4)();
        local_68 = 0;
        local_6c = 0;
        local_70 = 0;
        local_a4[2] = 0;
        local_a4[1] = 0;
        local_a4[0] = 0;
        local_a4[0xb] = 0;
        local_a4[10] = 0;
        local_a4[9] = 0;
        local_a4[7] = 0;
        local_a4[6] = 0;
        local_a4[5] = 0;
        if (iVar14 == 1) {
          *(undefined4 *)(puVar22 + -0x1c) = 0x77f58;
          event_queue_reset();
          *(undefined4 **)(puVar22 + -0x1c) = local_28;
          *(undefined4 *)(puVar22 + -0x20) = 0x77f61;
          freemem();
          return 0;
        }
        *(undefined4 *)(puVar22 + -0x1c) = 0x771cc;
        event_queue_reset();
        puVar22 = puVar22 + -0x18;
        goto LAB_00077e2f;
      }
      if ((int)piVar13 < 0x20) {
        piVar15 = (int *)0x0;
      }
      *(int **)(puVar22 + -4) = piVar15;
      if ((int)ppiVar12 < 0x1c) {
        ppiVar12 = (int **)0x0;
      }
      else {
        ppiVar12 = ppiVar12 + -7;
      }
      *(int ***)(puVar22 + -8) = ppiVar12;
      *(undefined4 **)(puVar22 + -0xc) = local_28;
      *(undefined4 *)(puVar22 + -0x10) = 0x771ef;
      drawshape();
      uVar19 = local_30;
      *(undefined4 *)(puVar22 + -4) = local_30;
      *(undefined4 *)(puVar22 + -8) = local_2c;
      iVar14 = aiStack_fc[local_58 * 2 + 3];
      iVar24 = aiStack_fc[local_58 * 2 + 2];
      iVar5 = local_a4[local_58 + 8];
      piVar13 = (&local_74)[local_58];
      *(undefined4 *)(puVar22 + -0xc) = 0x7721a;
      highlight_menu_item(piVar13 + iVar5 * 8,iVar24,iVar14,local_34);
      iVar10 = local_58;
      iVar5 = local_5c;
      local_a4[local_58 + 8] = local_5c;
      *(undefined4 *)(puVar22 + -4) = uVar19;
      *(undefined4 *)(puVar22 + -8) = local_2c;
      iVar14 = aiStack_fc[iVar10 * 2 + 3];
      iVar24 = aiStack_fc[iVar10 * 2 + 2];
      piVar13 = (&local_74)[iVar10] + iVar5 * 8;
      uVar19 = local_34;
    }
    *(undefined4 *)(puVar22 + -0xc) = 0x77246;
    unhighlight_menu_item(piVar13,iVar24,iVar14,uVar19);
  }
LAB_00077e2f:
  ppiVar21 = local_50;
  if ((int)local_54 < 0x20) {
    piVar13 = (int *)0x0;
  }
  else {
    piVar13 = local_54 + -8;
  }
  *(int **)(puVar22 + -4) = piVar13;
  if ((int)local_50 < 0x1c) {
    ppiVar12 = (int **)0x0;
  }
  else {
    ppiVar12 = local_50 + -7;
  }
  *(int ***)(puVar22 + -8) = ppiVar12;
  *(undefined4 **)(puVar22 + -0xc) = local_28;
  *(undefined4 *)(puVar22 + -0x10) = 0x77e58;
  grabshape();
  if (((local_74[3] < (int)local_54) && ((int)local_50 < 500)) && (local_60 != -1)) {
    if (local_70 != 0) {
      *(int **)(puVar22 + -4) = &local_5c;
      *(int **)(puVar22 + -8) = &local_58;
      *(int **)(puVar22 + -0xc) = aiStack_fc + 2;
      *(int **)(puVar22 + -0x10) = local_a4 + 4;
      ppiVar21 = &local_74;
      *(undefined4 *)(puVar22 + -0x14) = 0x77ea9;
      iVar14 = hit_test_menus(local_50,local_54,ppiVar21,local_1c);
      if (iVar14 != 0) goto LAB_00077f3c;
    }
    ppiVar21 = (int **)(uint)local_10;
    if ((&rosters)[(int)ppiVar21 * 0x444 + (uint)(byte)(&unk_ed0f6)[local_60 * 0x16] * 0x27] !=
        '\x02') {
      uVar2 = (&unk_ed0f5)[local_60 * 0x16];
      *(undefined4 *)(puVar22 + -4) = 0x77f12;
      sub_7a099(&unk_d1238,uVar2,local_14,local_18);
      *(undefined1 **)(puVar22 + -4) = &unk_d1238;
      *(undefined4 *)(puVar22 + -8) = 0x77f1c;
      ppiVar21 = param_2;
      setremaptable();
      *(int **)(puVar22 + -4) = local_54 + -8;
      *(int ***)(puVar22 + -8) = local_50 + -7;
      *(int ***)(puVar22 + -0xc) = ppiVar21;
      *(undefined4 *)(puVar22 + -0x10) = 0x77f39;
      param_2 = ppiVar21;
      drawshape_trans();
    }
  }
LAB_00077f3c:
  *(int **)(puVar22 + -4) = local_54;
  *(int *)(puVar22 + -8) = (int)local_50 + -3;
  *(int ***)(puVar22 + -0xc) = pointer_shapes;
  goto LAB_0007703e;
code_r0x0007706e:
  if ((ppiVar12 == local_50) && (piVar13 == local_54)) goto LAB_0007704c;
  if ((int)piVar13 < 0x20) {
    piVar13 = (int *)0x0;
  }
  else {
    piVar13 = piVar13 + -8;
  }
  *(int **)(puVar22 + -4) = piVar13;
  if ((int)ppiVar12 < 0x1c) {
    ppiVar12 = (int **)0x0;
  }
  else {
    ppiVar12 = ppiVar12 + -7;
  }
  *(int ***)(puVar22 + -8) = ppiVar12;
  *(undefined4 **)(puVar22 + -0xc) = local_28;
  *(undefined4 *)(puVar22 + -0x10) = 0x76f1d;
  drawshape();
  if ((int)local_54 < 0x20) {
    piVar13 = (int *)0x0;
  }
  else {
    piVar13 = local_54 + -8;
  }
  *(int **)(puVar22 + -4) = piVar13;
  if ((int)local_50 < 0x1c) {
    ppiVar12 = (int **)0x0;
  }
  else {
    ppiVar12 = local_50 + -7;
  }
  *(int ***)(puVar22 + -8) = ppiVar12;
  *(undefined4 **)(puVar22 + -0xc) = local_28;
  *(undefined4 *)(puVar22 + -0x10) = 0x76f49;
  grabshape();
  if (((local_74[3] < (int)local_54) && ((int)local_50 < 500)) && (local_60 != -1)) {
    if (local_70 != 0) {
      *(int **)(puVar22 + -4) = &local_5c;
      *(int **)(puVar22 + -8) = &local_58;
      *(int **)(puVar22 + -0xc) = aiStack_fc + 2;
      *(int **)(puVar22 + -0x10) = local_a4 + 4;
      *(undefined4 *)(puVar22 + -0x14) = 0x76f99;
      iVar14 = hit_test_menus(local_50,local_54,&local_74,local_1c);
      if (iVar14 != 0) goto LAB_0007702c;
    }
    if ((&rosters)[(uint)local_10 * 0x444 + (uint)(byte)(&unk_ed0f6)[local_60 * 0x16] * 0x27] !=
        '\x02') {
      uVar2 = (&unk_ed0f5)[local_60 * 0x16];
      *(undefined4 *)(puVar22 + -4) = 0x77002;
      sub_7a099(&unk_d1238,uVar2,local_14,local_18);
      *(undefined1 **)(puVar22 + -4) = &unk_d1238;
      *(undefined4 *)(puVar22 + -8) = 0x7700c;
      setremaptable();
      *(int **)(puVar22 + -4) = local_54 + -8;
      *(int ***)(puVar22 + -8) = local_50 + -7;
      *(int ***)(puVar22 + -0xc) = param_2;
      *(undefined4 *)(puVar22 + -0x10) = 0x77029;
      drawshape_trans();
    }
  }
LAB_0007702c:
  *(int **)(puVar22 + -4) = local_54;
  *(int *)(puVar22 + -8) = (int)local_50 + -3;
  *(int ***)(puVar22 + -0xc) = pointer_shapes;
  ppiVar21 = pointer_shapes;
LAB_0007703e:
  *(undefined4 *)(puVar22 + -0x10) = 0x77043;
  uVar28 = drawshape_trans();
  ppiVar12 = local_50;
  piVar13 = local_54;
  goto LAB_0007704c;
}


// ================================================================================================
// sub_77f6f @ 0x77f6f [__watcall]
// ================================================================================================

undefined4 __watcall sub_77f6f(int param_1,int unaff_EDX,int *unaff_EBX)

{
  int iVar1;
  
  __CHK(0x14);
  param_1 = param_1 + 4;
  if (param_1 < 500) {
    iVar1 = 0;
    do {
      if (((((int)(&unk_d1338)[iVar1 * 2] <= param_1) && (param_1 < (&unk_d1338)[iVar1 * 2] + 0x3a))
          && ((int)(&unk_d133c)[iVar1 * 2] <= unaff_EDX)) &&
         (unaff_EDX < (&unk_d133c)[iVar1 * 2] + 0x28)) {
        *unaff_EBX = iVar1;
        return 1;
      }
      iVar1 = iVar1 + 1;
    } while (iVar1 < 0x28);
  }
  else if ((0x15 < unaff_EDX) && (unaff_EDX < 0x182)) {
    *unaff_EBX = (unaff_EDX + -0x16) / 0xd + 100;
    return 1;
  }
  return 0;
}


// ================================================================================================
// edit_lines_keys @ 0x77ff5 [__watcall]
// ================================================================================================

void __watcall edit_lines_keys(int param_1)

{
  int iVar1;
  __off_t _Var2;
  ssize_t sVar3;
  int iVar4;
  undefined uStack_9c;
  undefined uStack_9b;
  undefined uStack_9a;
  undefined uStack_99;
  undefined auStack_89 [77];
  char acStack_3c [32];
  int iStack_1c;
  
  __CHK(0xac);
  iStack_1c = 0;
  do {
    (&unk_ed0f6)[iStack_1c * 0x16] = (undefined)iStack_1c;
    iStack_1c = iStack_1c + 1;
  } while (iStack_1c < 0x1c);
  sprintf(acStack_3c,&byte_dd750,&aKey_c31d5);
  iVar1 = _dos_findfirst(acStack_3c,0);
  if (iVar1 != 0) {
    fatalerror(&aA1_c31d9);
  }
  iVar1 = sub_92068(acStack_3c,0x200);
  if (iVar1 < 0) {
    fatalerror(&aA2_c31dc);
  }
  iStack_1c = 0;
  do {
    if (*(int *)(&unk_dbc7c + iStack_1c * 4 + param_1 * 0x2e8) < 0) {
      (&unk_ed0f4)[iStack_1c * 0x16] = 0;
    }
    else {
      _Var2 = lseek(iVar1,0,0);
      if (_Var2 != 0) {
        fatalerror(&aA3);
      }
      _Var2 = lseek(iVar1,*(__off_t *)(&unk_dbc7c + iStack_1c * 4 + param_1 * 0x2e8),0);
      if (_Var2 < 0) {
        fatalerror(&aA4);
      }
      sVar3 = read(iVar1,&uStack_9c,0x34);
      if ((sVar3 < 0) || (sVar3 != 0x34)) {
        fatalerror(&aA5);
      }
      iVar4 = iStack_1c * 0x16;
      (&unk_ed0f4)[iVar4] = uStack_9a;
      (&unk_ed0f5)[iVar4] = uStack_9b;
      (&unk_ed0f7)[iVar4] = uStack_99;
      (&unk_ed0f8)[iVar4] = 0x2e;
      (&unk_ed0f9)[iVar4] = 0x20;
      iVar4 = 0;
      do {
        (&unk_ed0fa)[iStack_1c * 0x16 + iVar4] = auStack_89[iVar4];
        iVar4 = iVar4 + 1;
      } while (iVar4 < 0x10);
    }
    iStack_1c = iStack_1c + 1;
  } while (iStack_1c < 0x19);
  iStack_1c = 0;
  do {
    if (*(int *)(&unk_dbce0 + iStack_1c * 4 + param_1 * 0x2e8) < 0) {
      (&unk_ed0f4)[(iStack_1c + 0x19) * 0x16] = 0;
    }
    else {
      _Var2 = lseek(iVar1,0,0);
      if (_Var2 != 0) {
        fatalerror(&aA6);
      }
      _Var2 = lseek(iVar1,*(__off_t *)(&unk_dbce0 + iStack_1c * 4 + param_1 * 0x2e8),0);
      if (_Var2 < 0) {
        fatalerror(&aA7);
      }
      sVar3 = read(iVar1,&uStack_9c,0x34);
      if ((sVar3 < 0) || (sVar3 != 0x34)) {
        fatalerror(&aA8);
      }
      iVar4 = (iStack_1c + 0x19) * 0x16;
      (&unk_ed0f4)[iVar4] = uStack_9a;
      (&unk_ed0f5)[iVar4] = uStack_9b;
      (&unk_ed0f7)[iVar4] = uStack_99;
      (&unk_ed0f8)[iVar4] = 0x2e;
      (&unk_ed0f9)[iVar4] = 0x20;
      iVar4 = 0;
      do {
        (&unk_ed0fa)[(iStack_1c + 0x19) * 0x16 + iVar4] = auStack_89[iVar4];
        iVar4 = iVar4 + 1;
      } while (iVar4 < 0x10);
    }
    iStack_1c = iStack_1c + 1;
  } while (iStack_1c < 3);
  sub_923c9(iVar1);
  return;
}


// ================================================================================================
// sub_78366 @ 0x78366 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall sub_78366(int param_1,undefined4 unaff_EDX,byte unaff_BL)

{
  int iVar1;
  short sVar2;
  int iVar3;
  undefined4 unaff_EDI;
  char acStack_3c [32];
  byte local_1c;
  undefined local_18;
  undefined uStack_14;
  
  __CHK(0x58);
  sVar2 = user2_team._2_2_;
  if (unaff_BL != 0) {
    sVar2 = _away_team_id;
  }
  uStack_14 = (&unk_d1238)[(byte)(&unk_d11bc)[sVar2 * 4]];
  local_18 = byte_d12de;
  iVar3 = 0;
  local_1c = unaff_BL;
  do {
    sub_7a099(&unk_d1238,*(undefined *)(iVar3 + param_1),uStack_14,local_18);
    setremaptable(&unk_d1238);
    drawshape2_trans(unaff_EDX,(&unk_d1338)[iVar3 * 2],(&unk_d133c)[iVar3 * 2]);
    iVar3 = iVar3 + 1;
  } while (iVar3 < 0x28);
  iVar3 = 0;
  do {
    if ((&rosters)[(uint)local_1c * 0x444 + (uint)(byte)(&unk_ed0f6)[iVar3 * 0x16] * 0x27] == '\0')
    {
      return;
    }
    switch((&rosters)[(uint)local_1c * 0x444 + (uint)(byte)(&unk_ed0f6)[iVar3 * 0x16] * 0x27]) {
    case 1:
    case 5:
    case 6:
    case 8:
      unaff_EDI = 0xc2;
      break;
    case 2:
      if (_period_num < 0) {
        unaff_EDI = 0xfc;
      }
      else {
        unaff_EDI = 0xc2;
      }
      break;
    case 3:
    case 4:
      unaff_EDI = 0xc3;
    }
    settextpos(unaff_EDI,0xc1);
    iVar1 = iVar3 * 0x16;
    sprintf(acStack_3c,aC2dS_c31cb,(uint)(byte)(&unk_ed0f4)[iVar1],(uint)(byte)(&unk_ed0f5)[iVar1],
            &unk_ed0f7 + iVar1);
    sub_76771(0x1fa,iVar3 * 0xd + 0x16,acStack_3c);
    iVar3 = iVar3 + 1;
  } while (iVar3 < 0x1c);
  return;
}


// ================================================================================================
// draw_lines_screen @ 0x78500 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall
draw_lines_screen(int param_1,undefined4 param_2,undefined4 param_3,undefined4 unaff_ECX,
                 undefined4 param_5)

{
  short sVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  undefined *puVar6;
  undefined auStack_168 [256];
  undefined auStack_68 [64];
  char acStack_28 [16];
  undefined4 local_18;
  undefined4 local_14;
  undefined4 uStack_10;
  
  __CHK(0x178);
  local_14 = 0xc0;
  local_18 = 0xc1;
  uStack_10 = 0xc2;
  sprintf(acStack_28,aEmbS,&team_names + param_1 * 0xba);
  puVar6 = install_path;
  if (byte_ed83c != '\x01') {
    puVar6 = (undefined *)0x0;
  }
  make_path(auStack_68,puVar6,acStack_28,0);
  uVar2 = loadshapes(auStack_68,0);
  iVar3 = 0;
  do {
    auStack_168[iVar3] = (char)iVar3;
    iVar3 = iVar3 + 1;
  } while (iVar3 < 0x100);
  puVar6 = install_path;
  if (byte_ed86d != '\x01') {
    puVar6 = (undefined *)0x0;
  }
  make_path(auStack_68,puVar6,aHOMEPALS_c31f7,&aBIN);
  iVar3 = loadfile(auStack_68,0);
  sVar1 = user2_team._2_2_;
  if (param_1 != 0) {
    sVar1 = _away_team_id;
  }
  iVar4 = 0x80;
  do {
    auStack_168[iVar4] = *(undefined *)(iVar3 + 0xc0 + sVar1 * 0x1c0 + iVar4);
    iVar4 = iVar4 + 1;
  } while (iVar4 < 0x100);
  freemem(iVar3);
  setremaptable(auStack_168);
  uVar5 = locateshape(uVar2,&aBkgd_c3200,0xffffffb4,0);
  drawshape_trans(uVar5);
  freemem(uVar2);
  draw_menu_items(unaff_ECX,param_5,local_14,local_18,uStack_10);
  settextpos(0xc0,0xc1);
  sub_78be7(500,0x13,0x27f,0x1df,1);
  puVar6 = install_path;
  if (byte_ed9e7 != '\x01') {
    puVar6 = (undefined *)0x0;
  }
  make_path(auStack_68,puVar6,aLelogo_c31bb,0);
  uVar2 = loadshapes(auStack_68,0);
  sVar1 = user2_team._2_2_;
  if (param_1 != 0) {
    sVar1 = _away_team_id;
  }
  uVar5 = locateshape(uVar2,(&off_c57cc)[sVar1]);
  drawshape_remap(uVar5,0x218,0x191);
  freemem(uVar2);
  sub_78be7(5,0x2c,0x45,0x54,1);
  printstr_at(aForward,0xc,0x33);
  printstr_at(aLine1,0x13,0x40);
  sub_78be7(5,0x5d,0x45,0x85,1);
  printstr_at(aForward,0xc,100);
  printstr_at(aLine2,0x13,0x71);
  sub_78be7(5,0x8e,0x45,0xb6,1);
  printstr_at(aForward,0xc,0x95);
  printstr_at(aLine3,0x13,0xa2);
  sub_78be7(5,0xbf,0x45,0xe7,1);
  printstr_at(aForward,0xc,0xc6);
  printstr_at(aLine4,0x13,0xd3);
  sub_78be7(5,0xfa,0x45,0x122,1);
  printstr_at(aPower,0x10,0x101);
  printstr_at(aPlay1,0x11,0x10e);
  sub_78be7(5,299,0x45,0x153,1);
  printstr_at(aPower,0x10,0x132);
  printstr_at(aPlay2,0x11,0x13f);
  sub_78be7(5,0x166,0x45,0x18e,1);
  printstr_at(aPenalty,0xc,0x16d);
  printstr_at(aKill1,0x13,0x17a);
  sub_78be7(5,0x197,0x45,0x1bf,1);
  printstr_at(aPenalty,0xc,0x19e);
  printstr_at(aKill2,0x13,0x1ab);
  sub_78be7(0x114,0x2c,0x154,0x54,1);
  printstr_at(aDefense_c3253,0x11b,0x33);
  printstr_at(aLine1,0x120,0x40);
  sub_78be7(0x114,0x5d,0x154,0x85,1);
  printstr_at(aDefense_c3253,0x11b,100);
  printstr_at(aLine2,0x120,0x71);
  sub_78be7(0x114,0x8e,0x154,0xb6,1);
  printstr_at(aDefense_c3253,0x11b,0x95);
  printstr_at(aLine3,0x120,0xa2);
  sub_78be7(0x186,200,0x1e4,0xf0,1);
  printstr_at(aGoaltenders,399,0xd5);
  sub_78be7(0x173,0x166,0x1c7,0x18e,1);
  printstr_at(aExtra,0x189,0x16d);
  printstr_at(aAttackers,0x17d,0x17a);
  return;
}


// ================================================================================================
// load_homepals @ 0x78a87 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall load_homepals(int param_1,undefined4 param_2,int unaff_EBX)

{
  int iVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  char cVar5;
  undefined *puVar6;
  undefined auStack_20 [16];
  
  __CHK(0x2c);
  puVar6 = install_path;
  if (byte_ed86d != '\x01') {
    puVar6 = (undefined *)0x0;
  }
  make_path(auStack_20,puVar6,aHOMEPALS_c31f7,&aBIN);
  iVar3 = loadfile(auStack_20,0);
  sVar2 = user2_team._2_2_;
  if (param_1 != 0) {
    sVar2 = _away_team_id;
  }
  iVar1 = sVar2 * 0x1c0 + iVar3;
  iVar4 = 0;
  do {
    *(undefined *)(unaff_EBX + 0xcc + iVar4) = *(undefined *)(iVar1 + iVar4);
    iVar4 = iVar4 + 1;
  } while (iVar4 < 0xb4);
  iVar4 = 0xb4;
  do {
    *(undefined *)(unaff_EBX + 0x198 + iVar4) = *(undefined *)(iVar1 + iVar4);
    iVar4 = iVar4 + 1;
  } while (iVar4 < 0xc0);
  *(undefined *)(unaff_EBX + 0x264) = 0x18;
  *(undefined *)(unaff_EBX + 0x265) = 0;
  *(undefined *)(unaff_EBX + 0x266) = 0;
  *(undefined *)(unaff_EBX + 0x267) = 0x2a;
  *(undefined *)(unaff_EBX + 0x268) = 0;
  *(undefined *)(unaff_EBX + 0x269) = 0;
  *(undefined *)(unaff_EBX + 0x26a) = 0x3b;
  *(undefined *)(unaff_EBX + 0x26b) = 0x12;
  *(undefined *)(unaff_EBX + 0x26c) = 0;
  *(undefined *)(unaff_EBX + 0x26d) = 0x3b;
  *(undefined *)(unaff_EBX + 0x26e) = 0x3b;
  *(undefined *)(unaff_EBX + 0x26f) = 0x3b;
  iVar4 = 0x80;
  do {
    cVar5 = *(char *)(iVar1 + 0xc0 + iVar4);
    if ((cVar5 < -0x80) && (0xbb < cVar5)) {
      cVar5 = cVar5 + '\b';
    }
    else {
      cVar5 = *(char *)(iVar1 + 0xc0 + iVar4) + -0x3c;
    }
    (&unk_d1238)[iVar4] = cVar5;
    iVar4 = iVar4 + 1;
  } while (iVar4 < 0xff);
  byte_d1333 = 0xfb;
  byte_d1334 = 0xfc;
  byte_d1335 = 0xfd;
  byte_d1336 = 0xfe;
  freemem(iVar3);
  setremaptable(&unk_d1238);
  return;
}


// ================================================================================================
// sub_78be7 @ 0x78be7 [__watcall]
// ================================================================================================

void __watcall sub_78be7(int param_1,int unaff_EDX,int unaff_EBX,int unaff_ECX,int param_5)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  __CHK(0x38);
  fillrect(param_1,unaff_EDX,(unaff_EBX - param_1) + 1,(unaff_ECX - unaff_EDX) + 1,dword_d0b16);
  sub_b4fac(param_1,unaff_EDX,unaff_EBX + -1,unaff_EDX,dword_d0b1a);
  sub_b4fac(param_1,unaff_EDX,param_1,unaff_ECX + -1,dword_d0b1a);
  sub_b4fac(unaff_EBX,unaff_EDX + 1,unaff_EBX,unaff_ECX,dword_d0b1e);
  sub_b4fac(param_1 + 1,unaff_ECX,unaff_EBX,unaff_ECX,dword_d0b1e);
  putpixel(param_1,unaff_ECX,dword_d0b22);
  putpixel(unaff_EBX,unaff_EDX,dword_d0b22);
  if (param_5 != 0) {
    iVar1 = unaff_EDX + 2;
    iVar2 = param_1 + 2;
    putpixel(iVar2,iVar1,dword_d0b2a,iVar1,iVar2);
    unaff_EDX = unaff_EDX + 3;
    param_1 = param_1 + 3;
    putpixel(param_1,unaff_EDX,dword_d0b2a,iVar1,iVar2,unaff_EDX);
    putpixel(param_1,iVar1,dword_d0b26);
    putpixel(iVar2,unaff_EDX,dword_d0b26);
    iVar3 = unaff_ECX + -2;
    putpixel(iVar2,iVar3,dword_d0b26);
    unaff_ECX = unaff_ECX + -3;
    putpixel(param_1,unaff_ECX,dword_d0b26);
    putpixel(param_1,iVar3,dword_d0b2a);
    putpixel(iVar2,unaff_ECX,dword_d0b2a);
    iVar2 = unaff_EBX + -3;
    putpixel(iVar2,iVar1,dword_d0b2a);
    unaff_EBX = unaff_EBX + -2;
    putpixel(unaff_EBX,unaff_EDX,dword_d0b2a);
    putpixel(unaff_EBX,iVar1,dword_d0b26);
    putpixel(iVar2,unaff_EDX,dword_d0b26);
    putpixel(iVar2,iVar3,dword_d0b26);
    putpixel(unaff_EBX,unaff_ECX,dword_d0b26);
    putpixel(unaff_EBX,iVar3,dword_d0b2a);
    putpixel(iVar2,unaff_ECX,dword_d0b2a);
  }
  return;
}


// ================================================================================================
// sub_78e29 @ 0x78e29 [__watcall]
// ================================================================================================

void __watcall sub_78e29(void)

{
  __CHK(0x10);
  return;
}


// ================================================================================================
// roster_dress_table @ 0x78e36 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __watcall roster_dress_table(byte param_1,undefined4 unaff_EDX,undefined4 unaff_EBX)

{
  undefined3 *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  char *pcVar6;
  char acStack_a4 [28];
  char acStack_88 [28];
  char acStack_6c [2];
  char acStack_6a [26];
  char *local_50 [3];
  char acStack_44 [8];
  undefined4 uStack_3c;
  char local_38 [4];
  char acStack_34 [8];
  char acStack_2c [8];
  int local_18;
  
  __CHK(0xc0);
  local_18 = 0;
  iVar4 = 0;
  builtin_strncpy(acStack_44,"Scratch",8);
  builtin_strncpy(acStack_2c,"Dress",6);
  builtin_strncpy(acStack_34,"Player",7);
  uStack_3c._0_1_ = 'G';
  uStack_3c._1_1_ = 'o';
  uStack_3c._2_1_ = 'a';
  uStack_3c._3_1_ = 'l';
  local_38[0] = 'i';
  local_38[1] = 'e';
  local_38[2] = '\0';
  pcVar5 = "Your roster is incomplete.";
  pcVar6 = acStack_6c;
  for (iVar2 = 6; iVar2 != 0; iVar2 = iVar2 + -1) {
    *(undefined4 *)pcVar6 = *(undefined4 *)pcVar5;
    pcVar5 = pcVar5 + 4;
    pcVar6 = pcVar6 + 4;
  }
  *(undefined2 *)pcVar6 = *(undefined2 *)pcVar5;
  pcVar6[2] = pcVar5[2];
  local_50[0] = acStack_6c;
  iVar2 = 1;
  if (-1 < _period_num) {
    return 0;
  }
  iVar3 = 0;
  do {
    if ((&rosters)[(uint)param_1 * 0x444 + (uint)(byte)(&unk_ed0f6)[iVar3 * 0x16] * 0x27] == '\x03')
    {
      if ((&unk_ed0f4)[iVar3 * 0x16] == 'G') {
        iVar4 = iVar4 + 1;
      }
      else {
        local_18 = local_18 + 1;
      }
    }
    iVar3 = iVar3 + 1;
  } while (iVar3 < 0x1c);
  if ((local_18 == 0x12) && (iVar4 == 2)) {
    return 0;
  }
  if (local_18 < 0x12) {
    if (local_18 == 0x11) {
      puVar1 = (undefined3 *)&unk_c3283;
    }
    else {
      puVar1 = &aS_c3285;
    }
    local_18 = 0x12 - local_18;
    pcVar5 = acStack_2c;
LAB_00078fc0:
    sprintf(acStack_88,aS2dSS_c3277,pcVar5,local_18,acStack_34,puVar1);
    local_50[1] = acStack_88;
    iVar2 = 2;
  }
  else if (0x12 < local_18) {
    if (local_18 == 0x13) {
      puVar1 = (undefined3 *)&unk_c3283;
    }
    else {
      puVar1 = &aS_c3285;
    }
    local_18 = local_18 + -0x12;
    pcVar5 = acStack_44;
    goto LAB_00078fc0;
  }
  if (iVar4 < 2) {
    if (iVar4 == 1) {
      puVar1 = (undefined3 *)&unk_c3283;
    }
    else {
      puVar1 = &aS_c3285;
    }
    iVar4 = 2 - iVar4;
    pcVar5 = acStack_2c;
  }
  else {
    if (iVar4 < 3) goto LAB_00079054;
    if (iVar4 == 3) {
      puVar1 = (undefined3 *)&unk_c3283;
    }
    else {
      puVar1 = &aS_c3285;
    }
    iVar4 = iVar4 + -2;
    pcVar5 = acStack_44;
  }
  sprintf(acStack_a4,aS2dSS_c3277,pcVar5,iVar4,&uStack_3c,puVar1);
  local_50[iVar2] = acStack_a4;
  iVar2 = iVar2 + 1;
LAB_00079054:
  message_dialog(0xffffffff,0xffffffff,local_50,iVar2,0,0,unaff_EDX,unaff_EBX,0xffffffff);
  return 1;
}


// ================================================================================================
// sub_79090 @ 0x79090 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall sub_79090(byte param_1,int unaff_EDX)

{
  byte *pbVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  
  __CHK(0x18);
  if (_period_num < 0) {
    iVar3 = 0;
    do {
      iVar4 = iVar3 * 0x27 + (uint)param_1 * 0x444;
      if ((&rosters)[iVar4] == '\x02') {
        (&rosters)[iVar4] = 3;
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < 0x1c);
    iVar3 = 0;
    do {
      bVar2 = *(byte *)(unaff_EDX + iVar3 + 0x28);
      if ((bVar2 != 100) &&
         (iVar4 = (uint)param_1 * 0x444 + (uint)bVar2 * 0x27, (&rosters)[iVar4] == '\x03')) {
        (&rosters)[iVar4] = 2;
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < 8);
  }
  else {
    iVar3 = 0;
    do {
      pbVar1 = (byte *)(unaff_EDX + iVar3);
      if (((*pbVar1 != 100) && ((&rosters)[(uint)param_1 * 0x444 + (uint)*pbVar1 * 0x27] != '\x04'))
         && ((&rosters)[(uint)param_1 * 0x444 + (uint)*pbVar1 * 0x27] != '\x03')) {
        *pbVar1 = 100;
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < 0x28);
  }
  return;
}


// ================================================================================================
// sub_79188 @ 0x79188 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __watcall sub_79188(int param_1,int unaff_EDX,byte param_3)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 in_stack_00000014;
  undefined4 in_stack_00000018;
  int local_14;
  
  __CHK(0x18);
  iVar1 = roster_dress_table(param_3,in_stack_00000014,in_stack_00000018);
  if (iVar1 == 0) {
    local_14 = 0;
    do {
      iVar1 = 0;
      do {
        iVar2 = iVar1 * 0x27 + (uint)param_3 * 0x444;
        if (((&rosters)[iVar2] != '\0') && (*(char *)(param_1 + local_14) == (&unk_db3ad)[iVar2])) {
          *(char *)(unaff_EDX + local_14) = (char)iVar1;
          break;
        }
        iVar1 = iVar1 + 1;
      } while (iVar1 < 0x1c);
      local_14 = local_14 + 1;
    } while (local_14 < 0x28);
    if (_period_num < 0) {
      local_14 = 0;
      do {
        *(undefined *)(unaff_EDX + 0x28 + local_14) = 100;
        local_14 = local_14 + 1;
      } while (local_14 < 8);
      iVar1 = 0;
      for (local_14 = 0; local_14 < 0x1c; local_14 = local_14 + 1) {
        if (((&rosters)[local_14 * 0x27 + (uint)param_3 * 0x444] != '\0') &&
           ((&rosters)[local_14 * 0x27 + (uint)param_3 * 0x444] != '\x03')) {
          *(undefined *)(iVar1 + 0x28 + unaff_EDX) = (undefined)local_14;
          iVar1 = iVar1 + 1;
        }
      }
    }
    uVar3 = 1;
  }
  else {
    uVar3 = 0;
  }
  return uVar3;
}


// ================================================================================================
// sub_7928a @ 0x7928a [__watcall]
// ================================================================================================

undefined4 __watcall sub_7928a(void)

{
  __CHK(4);
  return 1;
}


// ================================================================================================
// sub_7929c @ 0x7929c [__watcall]
// ================================================================================================

undefined4 __watcall
sub_7929c(int param_1,undefined4 param_2,byte unaff_BL,undefined4 *unaff_ECX,undefined4 param_5)

{
  int iVar1;
  undefined *puVar2;
  
  __CHK(0x18);
  puVar2 = &unk_dbd1c + (uint)unaff_BL * 0x2e8;
  sub_79090((uint)unaff_BL,puVar2);
  funcptr_cf443 = lines_teams_b;
  funcptr_cf363 = sub_79188;
  funcptr_cf223 = sub_79188;
  funcptr_cf3c3 = lines_teams_a;
  funcptr_cf283 = lines_teams_a;
  iVar1 = 0;
  do {
    if (puVar2[iVar1] == 100) {
      *(undefined *)(param_1 + iVar1) = 100;
      funcptr_cf443 = (undefined *)0x0;
      funcptr_cf363 = (undefined *)0x0;
      funcptr_cf223 = (undefined *)0x0;
      funcptr_cf3c3 = (undefined *)0x0;
      funcptr_cf283 = (undefined *)0x0;
    }
    else {
      *(undefined *)(param_1 + iVar1) =
           (&unk_db3ad)[(uint)unaff_BL * 0x444 + (uint)(byte)puVar2[iVar1] * 0x27];
    }
    iVar1 = iVar1 + 1;
  } while (iVar1 < 0x28);
  sub_78366(param_1,param_5,unaff_BL);
  *unaff_ECX = 0xffffffff;
  funcptr_cf2c3 = (undefined *)0x0;
  funcptr_cf2a3 = (undefined *)0x0;
  return 0;
}


// ================================================================================================
// sub_793a4 @ 0x793a4 [__watcall]
// ================================================================================================

undefined4 __watcall
sub_793a4(int param_1,undefined4 param_2,byte unaff_BL,undefined4 *unaff_ECX,undefined4 param_5)

{
  byte *pbVar1;
  int iVar2;
  
  __CHK(0x18);
  sub_79090((uint)unaff_BL,&unk_dbcec + (uint)unaff_BL * 0xba);
  funcptr_cf443 = lines_teams_b;
  funcptr_cf363 = sub_79188;
  funcptr_cf223 = sub_79188;
  funcptr_cf3c3 = lines_teams_a;
  funcptr_cf283 = lines_teams_a;
  iVar2 = 0;
  do {
    pbVar1 = (byte *)(iVar2 + (int)(&unk_dbcec + (uint)unaff_BL * 0xba));
    if (*pbVar1 == 100) {
      *(undefined *)(param_1 + iVar2) = 100;
      funcptr_cf443 = (undefined *)0x0;
      funcptr_cf363 = (undefined *)0x0;
      funcptr_cf223 = (undefined *)0x0;
      funcptr_cf3c3 = (undefined *)0x0;
      funcptr_cf283 = (undefined *)0x0;
    }
    else {
      *(undefined *)(param_1 + iVar2) = (&unk_db3ad)[(uint)unaff_BL * 0x444 + (uint)*pbVar1 * 0x27];
    }
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0x28);
  sub_78366(param_1,param_5,unaff_BL);
  *unaff_ECX = 0xffffffff;
  funcptr_cf2c3 = (undefined *)0x0;
  funcptr_cf2a3 = (undefined *)0x0;
  return 0;
}


// ================================================================================================
// lines_teams_a @ 0x7947f [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __watcall lines_teams_a(int param_1,undefined4 param_2,byte param_3)

{
  int iVar1;
  __off_t _Var2;
  ssize_t sVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  byte bVar8;
  undefined4 in_stack_00000014;
  char *__format;
  undefined auStack_31c [188];
  undefined4 auStack_260 [10];
  undefined auStack_238 [8];
  undefined4 auStack_230 [127];
  char acStack_34 [32];
  int local_14;
  byte bStack_10;
  
  bVar8 = 0;
  __CHK(0x32c);
  bStack_10 = param_3;
  iVar1 = roster_dress_table(param_3,in_stack_00000014);
  if (iVar1 == 0) {
    if (bStack_10 == 0) {
      __format = &byte_dd750;
    }
    else {
      __format = &byte_dd710;
    }
    sprintf(acStack_34,__format,aTeams_c3288);
    iVar1 = sub_92068(acStack_34,0x202);
    if (iVar1 < 0) {
      settextmode();
      sub_9621d(&aB2);
      waitkey();
                    /* WARNING: Subroutine does not return */
      exit(1);
    }
    _Var2 = lseek(iVar1,0,0);
    if (_Var2 != 0) {
      fatalerror(&aB3_c3292);
    }
    if (bStack_10 == 0) {
      iVar5 = CONCAT22(user2_team._2_2_,(undefined2)user2_team);
    }
    else {
      iVar5 = CONCAT22(_away_team_id,user2_team._2_2_);
    }
    _Var2 = lseek(iVar1,(iVar5 >> 0x10) * 0x2e8,0);
    if (_Var2 < 0) {
      fatalerror(&aB4_c3295);
    }
    sVar3 = read(iVar1,auStack_31c,0x2e8);
    if ((sVar3 < 0) || (sVar3 != 0x2e8)) {
      fatalerror(&aB5_c3298);
    }
    _Var2 = lseek(iVar1,-0x2e8,1);
    if ((_Var2 < 0) &&
       (((_Var2 != user2_team._2_2_ * 0x2e8 && (bStack_10 == 0)) ||
        ((_Var2 != _away_team_id * 0x2e8 && (bStack_10 != 0)))))) {
      fatalerror(&aB6_c329b);
    }
    local_14 = 0;
    do {
      iVar5 = 0;
      do {
        iVar4 = iVar5 * 0x27 + (uint)bStack_10 * 0x444;
        if (((&rosters)[iVar4] != '\0') && (*(char *)(param_1 + local_14) == (&unk_db3ad)[iVar4])) {
          *(char *)((int)auStack_260 + local_14) = (char)iVar5;
          break;
        }
        iVar5 = iVar5 + 1;
      } while (iVar5 < 0x1c);
      local_14 = local_14 + 1;
    } while (local_14 < 0x28);
    if (_period_num < 0) {
      local_14 = 0;
      do {
        auStack_238[local_14] = 100;
        local_14 = local_14 + 1;
      } while (local_14 < 8);
      iVar5 = 0;
      for (local_14 = 0; local_14 < 0x1c; local_14 = local_14 + 1) {
        if (((&rosters)[local_14 * 0x27 + (uint)bStack_10 * 0x444] != '\0') &&
           ((&rosters)[local_14 * 0x27 + (uint)bStack_10 * 0x444] != '\x03')) {
          auStack_238[iVar5] = (undefined)local_14;
          iVar5 = iVar5 + 1;
        }
      }
    }
    iVar5 = sub_96267(iVar1,auStack_31c,0x2e8);
    if ((iVar5 < 0) || (iVar5 != 0x2e8)) {
      fatalerror(&aB7_c329e);
    }
    puVar6 = auStack_260;
    puVar7 = &unk_dbcec + (uint)bStack_10 * 0xba;
    for (iVar5 = 0xc; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar7 = *puVar6;
      puVar6 = puVar6 + (uint)bVar8 * -2 + 1;
      puVar7 = puVar7 + (uint)bVar8 * -2 + 1;
    }
    puVar6 = auStack_230;
    puVar7 = (undefined4 *)(&unk_dbd1c + (uint)bStack_10 * 0x2e8);
    for (iVar5 = 0xc; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar7 = *puVar6;
      puVar6 = puVar6 + (uint)bVar8 * -2 + 1;
      puVar7 = puVar7 + (uint)bVar8 * -2 + 1;
    }
    sub_923c9(iVar1);
  }
  return 0;
}


// ================================================================================================
// lines_teams_b @ 0x797b4 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __watcall lines_teams_b(int param_1,undefined4 param_2,byte param_3)

{
  int iVar1;
  undefined4 uVar2;
  __off_t _Var3;
  ssize_t sVar4;
  int iVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  byte bVar9;
  undefined4 in_stack_00000014;
  char *__format;
  undefined auStack_31c [188];
  undefined4 auStack_260 [10];
  undefined auStack_238 [8];
  undefined4 auStack_230 [127];
  char acStack_34 [32];
  int local_14;
  byte bStack_10;
  
  bVar9 = 0;
  __CHK(0x32c);
  bStack_10 = param_3;
  iVar1 = roster_dress_table(param_3,in_stack_00000014);
  if (iVar1 == 0) {
    if (bStack_10 == 0) {
      __format = &byte_dd750;
    }
    else {
      __format = &byte_dd710;
    }
    sprintf(acStack_34,__format,aTeams_c3288);
    iVar1 = sub_92068(acStack_34,0x202);
    if (iVar1 < 0) {
      fatalerror(&aB2_c32a1);
    }
    _Var3 = lseek(iVar1,0,0);
    if (_Var3 != 0) {
      fatalerror(&aB3_c3292);
    }
    if (bStack_10 == 0) {
      iVar6 = CONCAT22(user2_team._2_2_,(undefined2)user2_team);
    }
    else {
      iVar6 = CONCAT22(_away_team_id,user2_team._2_2_);
    }
    _Var3 = lseek(iVar1,(iVar6 >> 0x10) * 0x2e8,0);
    if (_Var3 < 0) {
      fatalerror(&aB4_c3295);
    }
    sVar4 = read(iVar1,auStack_31c,0x2e8);
    if ((sVar4 < 0) || (sVar4 != 0x2e8)) {
      fatalerror(&aB5_c3298);
    }
    _Var3 = lseek(iVar1,-0x2e8,1);
    if ((_Var3 < 0) &&
       (((_Var3 != user2_team._2_2_ * 0x2e8 && (bStack_10 == 0)) ||
        ((_Var3 != _away_team_id * 0x2e8 && (bStack_10 != 0)))))) {
      fatalerror(&aB6_c329b);
    }
    local_14 = 0;
    do {
      iVar6 = 0;
      do {
        iVar5 = iVar6 * 0x27 + (uint)bStack_10 * 0x444;
        if (((&rosters)[iVar5] != '\0') && (*(char *)(local_14 + param_1) == (&unk_db3ad)[iVar5])) {
          *(char *)((int)auStack_260 + local_14) = (char)iVar6;
          break;
        }
        iVar6 = iVar6 + 1;
      } while (iVar6 < 0x1c);
      local_14 = local_14 + 1;
    } while (local_14 < 0x28);
    local_14 = 0;
    do {
      auStack_238[local_14] = 100;
      local_14 = local_14 + 1;
    } while (local_14 < 8);
    iVar6 = 0;
    for (local_14 = 0; local_14 < 0x1c; local_14 = local_14 + 1) {
      if (((&rosters)[local_14 * 0x27 + (uint)bStack_10 * 0x444] != '\0') &&
         ((&rosters)[local_14 * 0x27 + (uint)bStack_10 * 0x444] != '\x03')) {
        auStack_238[iVar6] = (undefined)local_14;
        iVar6 = iVar6 + 1;
      }
    }
    iVar6 = sub_96267(iVar1,auStack_31c,0x2e8);
    if ((iVar6 < 0) || (iVar6 != 0x2e8)) {
      fatalerror(&aB7_c329e);
    }
    puVar7 = auStack_260;
    puVar8 = &unk_dbcec + (uint)bStack_10 * 0xba;
    for (iVar6 = 0xc; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar8 = *puVar7;
      puVar7 = puVar7 + (uint)bVar9 * -2 + 1;
      puVar8 = puVar8 + (uint)bVar9 * -2 + 1;
    }
    puVar7 = auStack_230;
    puVar8 = (undefined4 *)(&unk_dbd1c + (uint)bStack_10 * 0x2e8);
    for (iVar6 = 0xc; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar8 = *puVar7;
      puVar7 = puVar7 + (uint)bVar9 * -2 + 1;
      puVar8 = puVar8 + (uint)bVar9 * -2 + 1;
    }
    sub_923c9(iVar1);
    uVar2 = 1;
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}


// ================================================================================================
// roster_stats_table @ 0x79ac9 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __watcall
roster_stats_table(undefined4 param_1,undefined4 param_2,byte unaff_BL,int *unaff_ECX,
                  undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined auStack_330 [768];
  char acStack_30 [32];
  byte bStack_10;
  
  __CHK(0x348);
  dword_dc738 = 1;
  dword_dc734 = 1;
  dword_c65b8 = player_stats_screen;
  if (unaff_BL == 0) {
    iVar1 = CONCAT22(user2_team._2_2_,(undefined2)user2_team);
  }
  else {
    iVar1 = CONCAT22(_away_team_id,user2_team._2_2_);
  }
  dword_c65b0 = iVar1 >> 0x10;
  bStack_10 = unaff_BL;
  dword_dd10c = allocmem(aTstat_c32a4,0x2a4,0x20);
  dword_dd11c = allocmem(&aKeys_c32aa,0x5b0,0x20);
  dword_dd110 = allocmem(aPstat_c32af,0x497,0x20);
  dword_dd114 = allocmem(aGstat_c32b5,0x10e,0x20);
  getpalette(0,0x100,&unk_ecdf4);
  iVar1 = 0;
  do {
    auStack_330[iVar1] = (&unk_ecdf4)[iVar1];
    iVar1 = iVar1 + 1;
  } while (iVar1 < 0x300);
  fade_palette(1,auStack_330,0x10);
  if (bStack_10 == 0) {
    iVar1 = CONCAT22(user2_team._2_2_,(undefined2)user2_team);
  }
  else {
    iVar1 = CONCAT22(_away_team_id,user2_team._2_2_);
  }
  player_stats_screen(iVar1 >> 0x10);
  draw_menu_items(&unk_cf48f,2,0xc0,0xc1,0xc2);
  iVar1 = 0;
  do {
    auStack_330[iVar1] = (&unk_ecdf4)[iVar1];
    iVar1 = iVar1 + 1;
  } while (iVar1 < 0x300);
  fade_palette(0,auStack_330,0x10);
  run_menu(&unk_cf48f,2,0xc0,0xc1,0xc2);
  fade_palette(1,auStack_330,0x10);
  iVar1 = 0;
  do {
    auStack_330[iVar1] = (&unk_ecdf4)[iVar1];
    iVar1 = iVar1 + 1;
  } while (iVar1 < 0x300);
  dword_dc738 = 0;
  dword_c65b8 = (code *)0x0;
  freemem(dword_dd10c);
  freemem(dword_dd114);
  freemem(dword_dd110);
  freemem(dword_dd11c);
  dword_dd11c = 0;
  dword_dd10c = 0;
  dword_dd114 = 0;
  dword_dd110 = 0;
  uVar2 = (uint)bStack_10;
  draw_lines_screen(uVar2,param_5,0,param_7,param_8);
  sub_78366(param_1,param_5,uVar2);
  if (-1 < *unaff_ECX) {
    if ((&rosters)[uVar2 * 0x444 + (uint)(byte)(&unk_ed0f6)[*unaff_ECX * 0x16] * 0x27] == '\x02') {
      uVar3 = 0xfd;
    }
    else {
      uVar3 = 0xc0;
    }
    settextpos(uVar3,0xc1);
    iVar1 = *unaff_ECX * 0x16;
    sprintf(acStack_30,aC2dS_c31cb,(uint)(byte)(&unk_ed0f4)[iVar1],(uint)(byte)(&unk_ed0f5)[iVar1],
            &unk_ed0f7 + iVar1);
    sub_76771(0x1fa,*unaff_ECX * 0xd + 0x16,acStack_30);
  }
  fade_palette(0,auStack_330,0x10);
  return 0;
}


// ================================================================================================
// sub_79dd1 @ 0x79dd1 [__watcall]
// ================================================================================================

undefined4 __watcall sub_79dd1(void)

{
  __CHK(4);
  return 1;
}


// ================================================================================================
// sub_79de1 @ 0x79de1 [__watcall]
// ================================================================================================

undefined4 __watcall
sub_79de1(int param_1,undefined4 param_2,byte unaff_BL,int *unaff_ECX,undefined4 param_5)

{
  int iVar1;
  char acStack_30 [32];
  byte bStack_10;
  
  __CHK(0x48);
  iVar1 = 0;
  do {
    if (*(char *)(param_1 + iVar1) == (&unk_ed0f5)[*unaff_ECX * 0x16]) {
      *(char *)(param_1 + iVar1) = 'd';
    }
    iVar1 = iVar1 + 1;
  } while (iVar1 < 0x28);
  funcptr_cf443 = lines_teams_b;
  funcptr_cf363 = sub_79188;
  funcptr_cf223 = sub_79188;
  funcptr_cf3c3 = lines_teams_a;
  funcptr_cf283 = lines_teams_a;
  iVar1 = 0;
  do {
    if (*(char *)(iVar1 + param_1) == 'd') {
      funcptr_cf443 = (undefined *)0x0;
      funcptr_cf363 = (undefined *)0x0;
      funcptr_cf223 = (undefined *)0x0;
      funcptr_cf3c3 = (undefined *)0x0;
      funcptr_cf283 = (undefined *)0x0;
      break;
    }
    iVar1 = iVar1 + 1;
  } while (iVar1 < 0x28);
  (&rosters)[(uint)unaff_BL * 0x444 + (uint)(byte)(&unk_ed0f6)[*unaff_ECX * 0x16] * 0x27] = 2;
  bStack_10 = unaff_BL;
  sub_78366(param_1,param_5);
  settextpos(0xfc,0xc1);
  iVar1 = *unaff_ECX * 0x16;
  sprintf(acStack_30,aC2dS_c31cb,(uint)(byte)(&unk_ed0f4)[iVar1],(uint)(byte)(&unk_ed0f5)[iVar1],
          &unk_ed0f7 + iVar1);
  sub_76771(0x1fa,*unaff_ECX * 0xd + 0x16,acStack_30);
  return 0;
}


// ================================================================================================
// sub_79f41 @ 0x79f41 [__watcall]
// ================================================================================================

undefined4 __watcall
sub_79f41(undefined4 param_1,undefined4 param_2,uint unaff_EBX,int *unaff_ECX,undefined4 param_5)

{
  int iVar1;
  char acStack_28 [32];
  
  __CHK(0x40);
  (&rosters)[(unaff_EBX & 0xff) * 0x444 + (uint)(byte)(&unk_ed0f6)[*unaff_ECX * 0x16] * 0x27] = 3;
  sub_78366(param_1,param_5);
  settextpos(0xc0,0xc1);
  iVar1 = *unaff_ECX * 0x16;
  sprintf(acStack_28,aC2dS_c31cb,(uint)(byte)(&unk_ed0f4)[iVar1],(uint)(byte)(&unk_ed0f5)[iVar1],
          &unk_ed0f7 + iVar1);
  sub_76771(0x1fa,*unaff_ECX * 0xd + 0x16,acStack_28);
  return 0;
}


// ================================================================================================
// sub_7a017 @ 0x7a017 [__watcall]
// ================================================================================================

uint __watcall
sub_7a017(int param_1,int unaff_EDX,undefined unaff_BL,undefined4 param_4,int param_5)

{
  uint uVar1;
  uint uVar2;
  uint local_14;
  
  __CHK(0x18);
  uVar2 = 0;
  do {
    uVar1 = (int)uVar2 / 0x20;
    if ((int)uVar2 % 0x20 == 0) {
      uVar1 = *(uint *)(&unk_d1478 +
                       ((int)((uVar2 + ((int)uVar2 >> 0x1f) * -0x20) -
                             (uint)(((int)uVar2 >> 0x1f) << 4 < 0)) >> 5) * 4 + unaff_EDX * 0xc);
      local_14 = uVar1;
    }
    if ((local_14 & 1) != 0) {
      uVar1 = uVar2;
      if ((param_5 != 0) && (0x23 < (int)uVar2)) {
        uVar1 = uVar2 + 0x30;
      }
      *(undefined *)(param_1 + uVar1) = unaff_BL;
    }
    local_14 = (int)local_14 >> 1;
    uVar2 = uVar2 + 1;
  } while ((int)uVar2 < 0x54);
  return uVar1;
}


// ================================================================================================
// sub_7a099 @ 0x7a099 [__watcall]
// ================================================================================================

void __watcall sub_7a099(int param_1,uint unaff_EDX,undefined unaff_BL,undefined unaff_CL)

{
  short sVar1;
  bool bVar2;
  
  __CHK(0x18);
  for (sVar1 = 0; sVar1 < 0x90; sVar1 = sVar1 + 1) {
    *(undefined *)(sVar1 + param_1) = unaff_CL;
  }
  for (sVar1 = 0xc0; sVar1 < 0xf0; sVar1 = sVar1 + 1) {
    *(undefined *)(sVar1 + param_1) = unaff_CL;
  }
  if (unaff_EDX < 100) {
    bVar2 = 9 < unaff_EDX;
    if (bVar2) {
      sub_7a017(param_1,unaff_EDX / 10,unaff_BL,unaff_CL,0);
      unaff_EDX = unaff_EDX % 10;
      param_1 = param_1 + 0x6c;
    }
    else {
      param_1 = param_1 + 0x30;
    }
    sub_7a017(param_1,unaff_EDX,unaff_BL,unaff_CL,bVar2);
  }
  return;
}


// ================================================================================================
// sub_7a13a @ 0x7a13a [__watcall]
// ================================================================================================

longlong __watcall sub_7a13a(undefined4 param_1,uint unaff_EDX)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  byte bVar7;
  
  bVar7 = 0;
  __CHK(0x2c);
  uVar1 = dword_d29fb;
  dword_d29fb = 0;
  settings_toggles();
  setdefaultscreen();
  puVar2 = (undefined4 *)allocmem(&aBKGD,0x1436b,0x20);
  puVar5 = puVar2 + (uint)bVar7 * -2 + 1;
  puVar3 = pointer_shapes + (uint)bVar7 * -2 + 1;
  *puVar2 = *pointer_shapes;
  puVar6 = puVar5 + (uint)bVar7 * -2 + 1;
  puVar4 = puVar3 + (uint)bVar7 * -2 + 1;
  *puVar5 = *puVar3;
  *puVar6 = *puVar4;
  puVar6[(uint)bVar7 * -2 + 1] = puVar4[(uint)bVar7 * -2 + 1];
  *(undefined *)(puVar6 + (uint)bVar7 * -2 + 1 + (uint)bVar7 * -2 + 1) =
       *(undefined *)(puVar4 + (uint)bVar7 * -2 + 1 + (uint)bVar7 * -2 + 1);
  *(undefined2 *)(puVar2 + 1) = 0xe6;
  *(undefined2 *)((int)puVar2 + 6) = 0x152;
  grabshape(puVar2,10,0x13);
  settings_dialog(0);
  sub_7a88e();
  settings_menu(1);
  drawshape(puVar2,10,0x13);
  freemem(puVar2);
  freemem(dword_d20a8);
  dword_d20a8 = 0;
  dword_d29fb = uVar1;
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// sub_7a1fc @ 0x7a1fc [__watcall]
// ================================================================================================

longlong __watcall sub_7a1fc(undefined4 param_1,uint unaff_EDX)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  byte bVar6;
  
  bVar6 = 0;
  __CHK(0x28);
  settings_toggles();
  setdefaultscreen();
  puVar1 = (undefined4 *)allocmem(&aBKGD,0x1436b,0x20);
  puVar4 = puVar1 + (uint)bVar6 * -2 + 1;
  puVar2 = pointer_shapes + (uint)bVar6 * -2 + 1;
  *puVar1 = *pointer_shapes;
  puVar5 = puVar4 + (uint)bVar6 * -2 + 1;
  puVar3 = puVar2 + (uint)bVar6 * -2 + 1;
  *puVar4 = *puVar2;
  *puVar5 = *puVar3;
  puVar5[(uint)bVar6 * -2 + 1] = puVar3[(uint)bVar6 * -2 + 1];
  *(undefined *)(puVar5 + (uint)bVar6 * -2 + 1 + (uint)bVar6 * -2 + 1) =
       *(undefined *)(puVar3 + (uint)bVar6 * -2 + 1 + (uint)bVar6 * -2 + 1);
  *(undefined2 *)(puVar1 + 1) = 0xe6;
  *(undefined2 *)((int)puVar1 + 6) = 0x152;
  grabshape(puVar1,10,0x13);
  settings_dialog(1);
  sub_7a88e();
  settings_menu(0);
  drawshape(puVar1,10,0x13);
  freemem(puVar1);
  freemem(dword_d20a8);
  dword_d20a8 = 0;
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// sub_7a29c @ 0x7a29c [__watcall]
// ================================================================================================

longlong __watcall sub_7a29c(undefined4 param_1,uint unaff_EDX)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  byte bVar6;
  
  bVar6 = 0;
  __CHK(0x28);
  settings_toggles();
  setdefaultscreen();
  puVar1 = (undefined4 *)allocmem(&aBKGD,0x1436b,0x20);
  puVar4 = puVar1 + (uint)bVar6 * -2 + 1;
  puVar2 = pointer_shapes + (uint)bVar6 * -2 + 1;
  *puVar1 = *pointer_shapes;
  puVar5 = puVar4 + (uint)bVar6 * -2 + 1;
  puVar3 = puVar2 + (uint)bVar6 * -2 + 1;
  *puVar4 = *puVar2;
  *puVar5 = *puVar3;
  puVar5[(uint)bVar6 * -2 + 1] = puVar3[(uint)bVar6 * -2 + 1];
  *(undefined *)(puVar5 + (uint)bVar6 * -2 + 1 + (uint)bVar6 * -2 + 1) =
       *(undefined *)(puVar3 + (uint)bVar6 * -2 + 1 + (uint)bVar6 * -2 + 1);
  *(undefined2 *)(puVar1 + 1) = 0xe6;
  *(undefined2 *)((int)puVar1 + 6) = 0x152;
  grabshape(puVar1,10,0x13);
  save_settings(&settings_exhibition);
  apply_settings(&settings_playoff);
  settings_dialog(0);
  sub_7a88e();
  settings_menu(1);
  load_game_set(&settings_playoff);
  apply_settings(&settings_exhibition);
  drawshape(puVar1,10,0x13);
  freemem(puVar1);
  freemem(dword_d20a8);
  dword_d20a8 = 0;
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// sub_7a335 @ 0x7a335 [__watcall]
// ================================================================================================

longlong __watcall sub_7a335(undefined4 param_1,uint unaff_EDX)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  byte bVar6;
  
  bVar6 = 0;
  __CHK(0x28);
  setdefaultscreen();
  settings_toggles();
  puVar1 = (undefined4 *)allocmem(&aBKGD,0x1436b,0x20);
  puVar4 = puVar1 + (uint)bVar6 * -2 + 1;
  puVar2 = pointer_shapes + (uint)bVar6 * -2 + 1;
  *puVar1 = *pointer_shapes;
  puVar5 = puVar4 + (uint)bVar6 * -2 + 1;
  puVar3 = puVar2 + (uint)bVar6 * -2 + 1;
  *puVar4 = *puVar2;
  *puVar5 = *puVar3;
  puVar5[(uint)bVar6 * -2 + 1] = puVar3[(uint)bVar6 * -2 + 1];
  *(undefined *)(puVar5 + (uint)bVar6 * -2 + 1 + (uint)bVar6 * -2 + 1) =
       *(undefined *)(puVar3 + (uint)bVar6 * -2 + 1 + (uint)bVar6 * -2 + 1);
  *(undefined2 *)(puVar1 + 1) = 0xe6;
  *(undefined2 *)((int)puVar1 + 6) = 0x152;
  grabshape(puVar1,10,0x13);
  settings_screen_b();
  sub_7a88e();
  settings_menu(1);
  drawshape(puVar1,10,0x13);
  freemem(puVar1);
  freemem(dword_d20a8);
  dword_d20a8 = 0;
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// sub_7a39f @ 0x7a39f [__watcall]
// ================================================================================================

longlong __watcall sub_7a39f(undefined4 param_1,uint unaff_EDX)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  byte bVar6;
  
  bVar6 = 0;
  __CHK(0x28);
  settings_toggles();
  puVar1 = (undefined4 *)allocmem(&aBKGD,0x1436b,0x20);
  puVar4 = puVar1 + (uint)bVar6 * -2 + 1;
  puVar2 = pointer_shapes + (uint)bVar6 * -2 + 1;
  *puVar1 = *pointer_shapes;
  puVar5 = puVar4 + (uint)bVar6 * -2 + 1;
  puVar3 = puVar2 + (uint)bVar6 * -2 + 1;
  *puVar4 = *puVar2;
  *puVar5 = *puVar3;
  puVar5[(uint)bVar6 * -2 + 1] = puVar3[(uint)bVar6 * -2 + 1];
  *(undefined *)(puVar5 + (uint)bVar6 * -2 + 1 + (uint)bVar6 * -2 + 1) =
       *(undefined *)(puVar3 + (uint)bVar6 * -2 + 1 + (uint)bVar6 * -2 + 1);
  *(undefined2 *)(puVar1 + 1) = 0xe6;
  *(undefined2 *)((int)puVar1 + 6) = 0x152;
  grabshape(puVar1,10,0x13);
  settings_screen_b();
  sub_7a88e();
  sub_7ac31();
  drawshape(puVar1,10,0x13);
  freemem(puVar1);
  freemem(dword_d20a8);
  dword_d20a8 = 0;
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// settings_screen_a @ 0x7a404 [__watcall]
// ================================================================================================

void __watcall settings_screen_a(void)

{
  undefined4 *puVar1;
  undefined *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  byte bVar7;
  undefined auStack_40 [32];
  undefined4 local_20;
  undefined4 *puStack_1c;
  
  bVar7 = 0;
  __CHK(0x50);
  settings_toggles();
  setdefaultscreen();
  puVar2 = install_path;
  if (byte_ed941 != '\x01') {
    puVar2 = (undefined *)0x0;
  }
  make_path(auStack_40,puVar2,aSetting5,0);
  local_20 = loadshapes(auStack_40,0);
  puVar1 = (undefined4 *)locateshape(local_20,&aDbox_c32ca);
  puStack_1c = (undefined4 *)
               allocmem(&aBKGD,(((int)puVar1[1] >> 0x10) + 1) *
                               ((*(int *)((int)puVar1 + 2) >> 0x10) + 1) + 0x11,0x20);
  puVar5 = puStack_1c + (uint)bVar7 * -2 + 1;
  puVar3 = puVar1 + (uint)bVar7 * -2 + 1;
  *puStack_1c = *puVar1;
  puVar6 = puVar5 + (uint)bVar7 * -2 + 1;
  puVar4 = puVar3 + (uint)bVar7 * -2 + 1;
  *puVar5 = *puVar3;
  *puVar6 = *puVar4;
  puVar6[(uint)bVar7 * -2 + 1] = puVar4[(uint)bVar7 * -2 + 1];
  *(undefined *)(puVar6 + (uint)bVar7 * -2 + 1 + (uint)bVar7 * -2 + 1) =
       *(undefined *)(puVar4 + (uint)bVar7 * -2 + 1 + (uint)bVar7 * -2 + 1);
  grabshape(puStack_1c,10,0x13);
  drawshape_remap(puVar1,10,0x13);
  freemem(local_20);
  settextpos(0xf8,0xff);
  if (dword_c541f == 0x10) {
    printstr_at(aMusic,0x68,0xaa);
    printstr_at(aSound,0x68,0xc0);
  }
  if (sound_enabled == '\0') {
    printstr_at(aDigitizedSpeech,0x68,0xd6);
  }
  sub_8050f(10,0x13,5,dword_c53fb,0xfa);
  sub_7a88e();
  sub_7ac31();
  puVar1 = puStack_1c;
  drawshape(puStack_1c,10,0x13);
  freemem(puVar1);
  freemem(dword_d20a8);
  dword_d20a8 = 0;
  return;
}


// ================================================================================================
// settings_screen_b @ 0x7a57e [__watcall]
// ================================================================================================

longlong __watcall settings_screen_b(undefined4 param_1,uint unaff_EDX)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined *puVar3;
  char *pcVar4;
  undefined auStack_34 [32];
  
  __CHK(0x44);
  setdefaultscreen();
  if (dword_ed35c == 0) {
    pcVar4 = aSetting3;
    puVar3 = (undefined *)0x0;
    if (byte_ed93f == '\x01') {
      puVar3 = install_path;
    }
  }
  else {
    pcVar4 = aSetting5;
    puVar3 = install_path;
    if (byte_ed941 != '\x01') {
      puVar3 = (undefined *)0x0;
    }
  }
  make_path(auStack_34,puVar3,pcVar4,0);
  uVar1 = loadshapes(auStack_34,0);
  uVar2 = locateshape(uVar1,&aDbox_c32ca,10,0x13);
  drawshape2_remap(uVar2);
  freemem(uVar1);
  settextpos(0xf8,0xff);
  if (dword_c541f == 0x10) {
    printstr_at(aMusic,0x68,0xaa);
    printstr_at(aSound,0x68,0xc0);
  }
  if (sound_enabled == '\0') {
    printstr_at(aDigitizedSpeech,0x68,0xd6);
  }
  if (dword_ed35c == 0) {
    uVar1 = 3;
  }
  else {
    uVar1 = 5;
  }
  sub_8050f(10,0x13,uVar1,dword_c53fb,0xfa);
  setdefaultscreen();
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// sub_7a6ad @ 0x7a6ad [__watcall]
// ================================================================================================

void __watcall sub_7a6ad(undefined4 param_1)

{
  __CHK(4);
  dword_ed35c = param_1;
  return;
}


// ================================================================================================
// settings_dialog @ 0x7a6bd [__watcall]
// ================================================================================================

void __watcall settings_dialog(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined *puVar4;
  undefined auStack_134 [256];
  undefined auStack_34 [32];
  
  __CHK(0x144);
  setdefaultscreen();
  iVar1 = 0;
  do {
    auStack_134[iVar1] = (char)iVar1;
    iVar1 = iVar1 + 1;
  } while (iVar1 < 0x100);
  if (param_1 != 0) {
    auStack_134[0xfa] = 0x40;
    auStack_134[0xf9] = 0x41;
    auStack_134[0xf8] = 0x42;
    auStack_134[0xf7] = 0x43;
  }
  setremaptable(auStack_134);
  puVar4 = install_path;
  if (byte_ed93f != '\x01') {
    puVar4 = (undefined *)0x0;
  }
  make_path(auStack_34,puVar4,aSetting3,0);
  uVar2 = loadshapes(auStack_34,0);
  uVar3 = locateshape(uVar2,&aDbox_c32ca,10,0x13);
  drawshape2_trans(uVar3);
  freemem(uVar2);
  if (param_1 == 0) {
    uVar2 = 0xf8;
  }
  else {
    uVar2 = 0x42;
  }
  settextpos(uVar2,0xff);
  if (dword_c541f == 0x10) {
    printstr_at(aMusic,0x68,0xaa);
    printstr_at(aSound,0x68,0xc0);
  }
  if (sound_enabled == '\0') {
    printstr_at(aDigitizedSpeech,0x68,0xd6);
  }
  if ((dword_c53fb == 1) &&
     (((uVar2 = dword_ed76c, 4 < dword_d29fb || (uVar2 = dword_ed778, 2 < dword_d29fb)) ||
      (uVar2 = dword_ed78c, 0 < dword_d29fb)))) {
    drawshape_trans(uVar2,0x85,0x125);
  }
  if (param_1 == 0) {
    uVar2 = 0xfa;
  }
  else {
    uVar2 = 0x40;
  }
  sub_8050f(10,0x13,3,dword_c53fb,uVar2);
  return;
}


// ================================================================================================
// sub_7a88e @ 0x7a88e [__watcall]
// ================================================================================================

/* WARNING: Removing unreachable block (ram,0x0007a96b) */

void __watcall sub_7a88e(void)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
  __CHK(8);
  if (((byte)dword_c541f & 0x10) == 0) {
    uVar1 = ((option_flags << 0x19) >> 0x1f) << 6;
  }
  else {
    uVar1 = 0;
  }
  if (((byte)dword_c541f & 0x10) == 0) {
    uVar2 = ((option_flags << 0x18) >> 0x1f) << 7;
  }
  else {
    uVar2 = 0;
  }
  if (((byte)dword_c541f & 0x22) == 0) {
    uVar3 = 0;
  }
  else {
    uVar3 = ((option_flags << 0x17) >> 0x1f) << 8;
  }
  dword_ed360 = ((int)(option_flags << 0x1e) >> 0x1f) * -2 | option_flags & 1 |
                ((option_flags << 0x1d) >> 0x1f) << 2 | ((option_flags << 0x1c) >> 0x1f) << 3 |
                ((option_flags << 0x1b) >> 0x1f) << 4 | ((option_flags << 0x1a) >> 0x1f) << 5 |
                uVar1 | uVar2 | uVar3;
  uVar1 = (option_flags << 0x14) >> 0x1e;
  if (uVar1 == 0) {
    dword_ed360 = dword_ed360 | 0x800;
  }
  else if (uVar1 < 2) {
    dword_ed360 = dword_ed360 | 0x400;
  }
  else if (uVar1 == 2) {
    dword_ed360 = dword_ed360 | 0x200;
  }
  switch((option_flags << 0x11) >> 0x1d) {
  case 1:
    dword_ed360 = dword_ed360 | 0x1000;
    break;
  case 3:
    dword_ed360 = dword_ed360 | 0x2000;
    break;
  case 5:
    dword_ed360 = dword_ed360 | 0x4000;
    break;
  case 7:
    dword_ed360 = dword_ed360 | 0x8000;
  }
  sub_7aaaa();
  return;
}


// ================================================================================================
// sub_7a9c8 @ 0x7a9c8 [__watcall]
// ================================================================================================

undefined4 __watcall sub_7a9c8(int param_1,int unaff_EDX,uint *unaff_EBX)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  bool bVar4;
  
  __CHK(0x10);
  uVar2 = 0;
  do {
    if (((((int)(&asc_d14f0)[uVar2 * 4] <= param_1 + -6) &&
         (param_1 + -6 <= (int)(&unk_d14f8)[uVar2 * 4])) &&
        ((int)(&unk_d14f4)[uVar2 * 4] <= unaff_EDX + -0x13)) &&
       (unaff_EDX + -0x13 <= (int)(&unk_d14fc)[uVar2 * 4])) break;
    uVar2 = uVar2 + 1;
  } while ((int)uVar2 < 0x1b);
  if (uVar2 == 0x1b) {
LAB_0007aa87:
    uVar3 = 0;
  }
  else {
    if (uVar2 < 0x10) {
      if (9 < uVar2) {
        if (0xb < uVar2) {
          bVar4 = dword_c541f == 0x10;
          goto LAB_0007aa53;
        }
        goto LAB_0007aa87;
      }
    }
    else if (uVar2 < 0x12) {
      bVar4 = sound_enabled == '\0';
LAB_0007aa53:
      if (bVar4) goto LAB_0007aa87;
    }
    else if (uVar2 < 0x16) {
      if (((uVar2 == 0x15) && (dword_c53fb == 1)) && (0 < dword_d29fb)) goto LAB_0007aa87;
    }
    else if (uVar2 < 0x17) {
      if (dword_c53fb == 1) {
        bVar4 = SBORROW4(dword_d29fb,3);
        iVar1 = dword_d29fb + -3;
        goto LAB_0007aa85;
      }
    }
    else if ((uVar2 == 0x17) && (dword_c53fb == 1)) {
      bVar4 = SBORROW4(dword_d29fb,5);
      iVar1 = dword_d29fb + -5;
LAB_0007aa85:
      if (bVar4 == iVar1 < 0) goto LAB_0007aa87;
    }
    *unaff_EBX = uVar2;
    uVar3 = 1;
  }
  return uVar3;
}


